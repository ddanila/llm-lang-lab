import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import MagicMock, patch

from audit_batch import audit
import run_study
from export_report import export


class ReportingTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.batch = self.root / "20261008T000000000000Z"
        self.trial = self.batch / "000-example-c-r0"
        self.work = self.trial / "work"
        (self.work / "revisions").mkdir(parents=True)
        self.write("config.json", {"max_submissions": 4})
        self.job = {"task": "example", "language": "c", "repeat": 0, "sampling_seed": 1}
        self.write("schedule.json", [self.job])
        env = {"source_sha256": {"example": "hash"}, "model_digest": "digest"}
        self.write("environment.json", env)
        self.write("status.json", {"state": "complete", **env})
        self.write("summary.json", {})
        self.row = {**self.job, "tokens": {"input": 3, "output": 7}, "submissions": 1,
                    "stop": "public_pass", "hidden": {}, "first_hidden": {},
                    "elapsed_seconds": 1, "usage_complete": True, "infrastructure_error": False}
        (self.work / "main.c").write_text("source")
        (self.work / "revisions/1-main.c").write_text("source")
        (self.work / "attempts.jsonl").write_text(json.dumps({"passed": True}) + "\n")
        (self.trial / "events.jsonl").write_text(json.dumps({"type": "message_end",
            "message": {"role": "assistant", "usage": self.row["tokens"]}}) + "\n")
        self.save_row()

    def write(self, name, value):
        (self.batch / name).write_text(json.dumps(value))

    def save_row(self):
        (self.trial / "result.json").write_text(json.dumps(self.row))

    def test_audit_reconciles_and_hashes_raw_evidence(self):
        result = audit(self.batch)
        self.assertEqual(result["trials"], 1)
        self.assertEqual(len(result["checks"][0]["event_log_sha256"]), 64)
        self.assertEqual(result["incomplete_usage_trials"], 0)

    def test_audit_handles_unicode_separators_in_both_jsonl_streams(self):
        log = self.trial / "events.jsonl"
        event = json.loads(log.read_text())
        event["message"]["content"] = "a\u0085b\u2028c\u2029d"
        log.write_text(json.dumps(event, ensure_ascii=False) + "\n")
        (self.work / "attempts.jsonl").write_text(json.dumps(
            {"passed": True, "stdout": "a\u0085b\u2028c\u2029d"}, ensure_ascii=False) + "\n")
        self.assertEqual(audit(self.batch)["trials"], 1)

    def test_export_preserves_missing_timing_and_recovery_disclosure(self):
        self.write("config.json", {"model": "fake", "tasks": ["example"], "repeats": 1,
                                  "recovery_amendment": "test-amendment", "protocol_version": 2})
        self.write("environment.json", {"model_tags": {"models": [{"name": "fake:latest", "digest": "digest", "size": 1}]},
                                       "model": {"details": {}, "parameters": ""}})
        self.row["elapsed_seconds"] = None
        self.save_row()
        self.write("summary.json", {"languages": {"c": {"runs": 1, "successes": 0,
            "first_submission_successes": 0, "mean_submissions": 1,
            "output_tokens_per_success": None, "median_seconds": None}}})
        self.write("recovery.json", {"amendment": "test-amendment"})
        destination = export(self.batch, self.root / "export")
        payload = json.loads((destination / "results.json").read_text())
        self.assertIsNone(payload["runs"][0]["elapsed_seconds"])
        self.assertEqual(payload["recovery"]["amendment"], "test-amendment")
        self.assertIn("incomplete timing", (destination / "README.md").read_text())
        self.assertIn("not the original", (destination / "README.md").read_text())

    def test_audit_rejects_changed_usage(self):
        self.row["tokens"]["output"] += 1
        self.save_row()
        with self.assertRaisesRegex(ValueError, "Usage differs"):
            audit(self.batch)

    def test_audit_rejects_changed_final_source(self):
        (self.work / "main.c").write_text("different")
        with self.assertRaisesRegex(ValueError, "Final source changed"):
            audit(self.batch)

    def test_audit_rejects_submission_after_public_pass(self):
        (self.work / "revisions/2-main.c").write_text("source")
        (self.work / "attempts.jsonl").write_text('{"passed": true}\n{"passed": true}\n')
        self.row["submissions"] = 2
        self.save_row()
        with self.assertRaisesRegex(ValueError, "Submitted after"):
            audit(self.batch)

    def test_audit_exposes_judge_wall_timeouts_in_calibration(self):
        self.row["hidden"] = {"failures": [{"timeout": True}]}
        self.save_row()
        self.assertEqual(audit(self.batch)["compiler_or_case_wall_timeout_trials"], 1)

    def test_publishing_rejects_unrelated_tracked_changes(self):
        with patch.object(run_study, "command", return_value=" M bench.py"):
            with self.assertRaisesRegex(ValueError, "Tracked or staged changes"):
                run_study.clean_tracked_tree()

    def test_privacy_scan_blocks_local_paths(self):
        report = self.root / "report"
        report.mkdir()
        (report / "source.c").write_text('/* /Users/private/example */')
        with patch.object(run_study, "ROOT", self.root):
            with self.assertRaisesRegex(ValueError, "privacy review"):
                run_study.privacy_check(report)

    def test_invalid_a_stops_before_b_and_publication(self):
        experiments = self.root / "experiments"
        experiments.mkdir()
        (experiments / "study.json").write_text('{"study_id": "test", "run_settings": {}}')
        for phase in ("a", "b"):
            (experiments / f"confirm-{phase}.json").write_text(json.dumps({"replication": phase.upper()}))
        state = self.root / ".local/study-run.json"
        process = MagicMock()
        process.__enter__.return_value = process
        process.stdout = ["Batch: " + str(self.batch) + "\n"]
        process.wait.return_value = 0
        def git(args):
            return "" if args[1] == "status" else "main"
        with patch.object(run_study, "ROOT", self.root), \
             patch.object(run_study, "STATE", state), \
             patch.object(run_study, "command", side_effect=git), \
             patch.object(run_study, "source_hashes", return_value={}), \
             patch.object(run_study, "validate_config"), \
             patch.object(run_study.analysis, "load_batch", return_value={}), \
             patch.object(run_study.analysis, "validate_batch", side_effect=ValueError("invalid A")), \
             patch.object(run_study.subprocess, "Popen", return_value=process) as launch, \
             patch.object(run_study, "export") as publish, \
             patch.object(run_study.sys, "argv", ["run_study.py", "--publish"]):
            with self.assertRaisesRegex(ValueError, "invalid A"):
                run_study.main()
        self.assertEqual(launch.call_count, 1)
        publish.assert_not_called()
        self.assertEqual(json.loads(state.read_text())["stage"], "stopped_with_error")


if __name__ == "__main__":
    unittest.main()
