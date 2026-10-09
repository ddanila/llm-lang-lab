import copy
import contextlib
import hashlib
import io
import json
from pathlib import Path
import shutil
import tempfile
import unittest
from unittest.mock import patch

import analysis
import bench
import run_study
from bench import summarize
from checkpoints import seal, write, read
import recovery
import test_checkpoints
from test_analysis import fixture, STUDY


class RecoveryTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.registry_path = Path(self.temp.name) / "registry.json"
        self.provenance = {"amendment": recovery.AMENDMENT, "original_batch": "original"}
        self.row = {"task": "example", "success": False, "tokens": {"output": 17},
                    "elapsed_seconds": None, "returncode": None}
        self.config = {"replication": "A", "recovery_amendment": recovery.AMENDMENT}
        write(self.registry_path, {"provenance": self.provenance,
              "rows": [{"trial": "recovered", "portable_sha256": recovery.row_hash(self.row)}]})
        self.patch = patch.object(recovery, "REGISTRY", self.registry_path)
        self.patch.start()
        self.addCleanup(self.patch.stop)

    def test_only_registered_missing_timing_is_accepted(self):
        recovery.validate_prefix(self.config, [self.row], self.provenance)
        with self.assertRaisesRegex(ValueError, "outside registered"):
            recovery.validate_prefix(self.config, [self.row, {"elapsed_seconds": None}], self.provenance)

    def test_changed_recovered_measurement_is_rejected(self):
        changed = copy.deepcopy(self.row)
        changed["tokens"]["output"] += 1
        with self.assertRaisesRegex(ValueError, "observation changed"):
            recovery.validate_prefix(self.config, [changed], self.provenance)

    def test_missing_or_forged_provenance_is_rejected(self):
        for provenance in (None, {"amendment": "different"}):
            with self.assertRaisesRegex(ValueError, "provenance"):
                recovery.validate_prefix(self.config, [self.row], provenance)

    def test_b_cannot_use_recovery_exception(self):
        config = {**self.config, "replication": "B"}
        with self.assertRaises(ValueError):
            recovery.validate_prefix(config, [self.row], None)
        recovery.validate_prefix(config, [{"elapsed_seconds": 1}], None)

    def test_amended_a_cannot_accidentally_regenerate_imported_prefix(self):
        with patch.object(bench.sys, "argv", ["bench.py", "run", "--config", str(bench.ROOT / "experiments/confirm-a.json")]), \
             patch.object(bench, "environment") as environment, contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaises(SystemExit):
                bench.main()
        environment.assert_not_called()

    def test_amended_driver_requires_prepared_resume(self):
        with patch.object(run_study, "STATE", Path(self.temp.name) / "state.json"), \
             patch.object(run_study, "clean_tracked_tree"), \
             patch.object(run_study, "command", return_value="main"), \
             patch.object(run_study.sys, "argv", ["run_study.py"]), \
             patch.object(run_study.subprocess, "Popen") as launch:
            with self.assertRaisesRegex(ValueError, "requires --resume"):
                run_study.main()
        launch.assert_not_called()

    def test_missing_timing_does_not_silently_bias_median(self):
        row = {**self.row, "language": "c", "repeat": 0, "first_submission_passed": False,
               "infrastructure_error": False, "submissions": 1, "par2_seconds": 1200}
        summary = summarize([row, {**row, "repeat": 1, "elapsed_seconds": 2}], {"languages": ["c"]})
        self.assertIsNone(summary["languages"]["c"]["median_seconds"])
        self.assertEqual(summary["languages"]["c"]["missing_timing_runs"], 1)

    def test_amended_result_cannot_claim_unamended_replication(self):
        study = copy.deepcopy(STUDY)
        study["run_settings"]["recovery_amendment"] = recovery.AMENDMENT
        a, b = fixture("A"), fixture("B")
        a["config"]["recovery_amendment"] = b["config"]["recovery_amendment"] = recovery.AMENDMENT
        for row in b["rows"]:
            row["elapsed_seconds"] = 1
        a["recovery"] = self.provenance
        write(self.registry_path, {"provenance": self.provenance, "rows": [
            {"trial": str(i), "portable_sha256": recovery.row_hash(row)} for i, row in enumerate(a["rows"])]})
        result = analysis.compare(a, b, study, draws=100)
        self.assertIn("under_recovery_amendment", result["status"])
        self.assertIn("not the original", result["scope"])

    def test_odd_recovery_checkpoint_continues_partner_without_replaying_prefix(self):
        helper = test_checkpoints.CheckpointTests()
        helper.setUp()
        self.addCleanup(helper.doCleanups)
        batch = helper.run_chunk()
        trials = sorted(p for p in batch.iterdir() if p.is_dir())
        # Construct a one-row synthetic imported prefix in an isolated test directory.
        shutil.rmtree(trials[1])
        helper.config.update(recovery_amendment=recovery.AMENDMENT, replication="A")
        write(helper.config_path, helper.config)
        write(batch / "config.json", helper.config)
        write(batch / "recovery.json", self.provenance)
        row = read(trials[0] / "result.json")
        row["elapsed_seconds"] = None
        write(trials[0] / "result.json", row)
        write(self.registry_path, {"provenance": self.provenance, "rows": [{
            "trial": trials[0].name, "portable_sha256": recovery.row_hash(row),
            "evidence_sha256": {"result.json": hashlib.sha256((trials[0] / "result.json").read_bytes()).hexdigest()}}]})
        seal(batch, 1, helper.snapshot)
        helper.indices.clear()
        helper.run_chunk(batch)
        self.assertEqual(helper.indices, [1])
        self.assertEqual(read(batch / "status.json")["completed_trials"], 2)
