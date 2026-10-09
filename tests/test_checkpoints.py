import contextlib
import copy
import io
import itertools
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import bench
from checkpoints import ENV_KEYS, export_progress, read, read_jsonl, resume_rows, write


class CheckpointTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.config = read(bench.ROOT / "experiments/pilot.json")
        self.config.update(tasks=["rpn", "merge_intervals"], repeats=1)
        self.config_path = self.root / "config.json"
        write(self.config_path, self.config)
        self.snapshot = {k: "fixed" for k in ENV_KEYS}
        self.snapshot["source_sha256"] = {"test": "unchanged"}
        self.indices = []

    def fake_trial(self, batch, config, job, i):
        self.indices.append(i)
        trial = batch / f"{i:03d}-{job['task']}-{job['language']}-r{job['repeat']}"
        work = trial / "work"
        (work / "revisions").mkdir(parents=True)
        for name in ("events.jsonl", "prompt.txt", "system.txt"):
            (trial / name).write_text("")
        filename = "main.c" if job["language"] == "c" else "main.go"
        (work / filename).write_text("source")
        (work / "revisions" / ("1-" + filename)).write_text("source")
        (work / "attempts.jsonl").write_text('{"passed": false}\n')
        row = {**job, "success": False, "infrastructure_error": False,
               "tokens": {"output": 100}, "first_submission_passed": False,
               "elapsed_seconds": 1, "submissions": 1, "par2_seconds": 1200}
        write(trial / "result.json", row)
        return row

    def run_chunk(self, batch=None):
        argv = ["bench.py", "run", "--config", str(self.config_path), "--chunk-seconds", "1"]
        if batch:
            argv += ["--batch", str(batch)]
        with patch.object(bench, "ROOT", self.root), \
             patch.object(bench, "environment", return_value=copy.deepcopy(self.snapshot)), \
             patch.object(bench, "source_hashes", return_value=self.snapshot["source_sha256"]), \
             patch.object(bench, "api", return_value={}), \
             patch.object(bench, "run_one", side_effect=self.fake_trial), \
             patch.object(bench.time, "monotonic", side_effect=itertools.count(step=2)), \
             patch.object(bench.sys, "argv", argv), contextlib.redirect_stdout(io.StringIO()):
            bench.main()
        return next((self.root / "runs").iterdir())

    def test_chunk_resume_preserves_failed_rows_and_finishes_exact_schedule(self):
        batch = self.run_chunk()
        self.assertEqual(self.indices, [0, 1])
        self.assertEqual(read(batch / "status.json")["state"], "checkpoint")
        hashes = read(batch / "checkpoint.json")["evidence_sha256"]
        self.run_chunk(batch)
        self.assertEqual(self.indices, [0, 1, 2, 3])
        self.assertEqual(read(batch / "status.json")["state"], "complete")
        self.assertEqual(len(list(batch.glob("*/result.json"))), 4)
        from checkpoints import digest
        self.assertTrue(all(digest(batch / name) == value for name, value in hashes.items()))

    def test_resume_rejects_tampered_source(self):
        batch = self.run_chunk()
        next(batch.glob("*/work/revisions/*")).write_text("tampered")
        with self.assertRaisesRegex(ValueError, "evidence changed"):
            self.run_chunk(batch)
        self.assertEqual(self.indices, [0, 1])

    def test_resume_rejects_incomplete_trial_and_never_replays_it(self):
        batch = self.run_chunk()
        (batch / "002-unfinished-trial").mkdir()
        with self.assertRaisesRegex(ValueError, "Unfinished trial"):
            self.run_chunk(batch)
        self.assertEqual(self.indices, [0, 1])

    def test_resume_rejects_changed_environment(self):
        batch = self.run_chunk()
        self.snapshot["go"] = "changed"
        with self.assertRaisesRegex(ValueError, "environment changed"):
            self.run_chunk(batch)

    def test_resume_rejects_running_status_even_with_a_previous_checkpoint(self):
        batch = self.run_chunk()
        write(batch / "status.json", {"state": "running"})
        with self.assertRaisesRegex(ValueError, "clean checkpoint"):
            self.run_chunk(batch)

    def test_progress_export_is_explicitly_not_confirmation_and_retains_sources(self):
        batch = self.run_chunk()
        target = self.root / "checkpoint"
        export_progress(batch, target)
        payload = read(target / "progress.json")
        self.assertEqual(payload["completed_trials"], 2)
        self.assertEqual(payload["planned_trials"], 4)
        self.assertEqual(payload["batch_status"]["state"], "checkpoint_only_not_confirmation")
        self.assertFalse(any(row["success"] for row in payload["runs"]))
        self.assertEqual(len(list(target.glob("sources/*/*"))), 2)

    def test_jsonl_preserves_unicode_separators_and_crlf_records(self):
        rows = [{"stdout": "a\u0085b\u2028c\u2029d"}, {"stdout": "escaped\nnewline"}]
        path = self.root / "events.jsonl"
        path.write_bytes(("\r\n".join(json.dumps(r, ensure_ascii=False) for r in rows) + "\r\n").encode())
        self.assertEqual(read_jsonl(path), rows)

    def test_jsonl_still_rejects_actual_corruption(self):
        path = self.root / "events.jsonl"
        path.write_text('{"ok": true}\n{"truncated": "value')
        with self.assertRaises(json.JSONDecodeError):
            read_jsonl(path)


if __name__ == "__main__":
    unittest.main()
