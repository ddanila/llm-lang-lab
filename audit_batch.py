#!/usr/bin/env python3
"""Audit retained pi traces without inference or changing a batch."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
from checkpoints import read_jsonl
from recovery import validate_raw_prefix


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit(batch):
    batch = Path(batch)
    read = lambda name: json.loads((batch / name).read_text())
    config, schedule, environment, status = [read(name) for name in
        ("config.json", "schedule.json", "environment.json", "status.json")]
    require(status.get("state") == "complete", "Batch is not complete")
    require(status["source_sha256"] == environment["source_sha256"], "Sources changed")
    require(status["model_digest"] == environment["model_digest"], "Model changed")
    paths = sorted(batch.glob("*/result.json"))
    require(len(paths) == len(schedule), "Trial count differs from schedule")
    checks, results = [], []
    for job, path in zip(schedule, paths):
        row = json.loads(path.read_text())
        results.append(row)
        require(all(row[k] == v for k, v in job.items()), "Trial differs from schedule")
        log = path.parent / "events.jsonl"
        events = read_jsonl(log)
        messages = [e["message"] for e in events if e["type"] == "message_end"
                    and e.get("message", {}).get("role") == "assistant"]
        for key, value in row["tokens"].items():
            require(value == sum(m.get("usage", {}).get(key, 0) for m in messages),
                    "Usage differs from authoritative events")
        work = path.parent / "work"
        revisions = sorted((work / "revisions").glob("*"),
                           key=lambda p: int(p.name.split("-", 1)[0]))
        require(len(revisions) == row["submissions"] <= config["max_submissions"],
                "Invalid revision count")
        if revisions:
            source = work / ("main.c" if row["language"] == "c" else "main.go")
            require(source.read_bytes() == revisions[-1].read_bytes(), "Final source changed")
        attempts_path = work / "attempts.jsonl"
        attempts = read_jsonl(attempts_path) if attempts_path.exists() else []
        require(len(attempts) <= len(revisions), "Feedback without saved source")
        if row["stop"] in ("public_pass", "submission_budget"):
            require(len(attempts) == len(revisions), "Missing completed submission feedback")
        require(not any(a["passed"] for a in attempts[:-1]), "Submitted after a public pass")
        if row["stop"] == "public_pass":
            require(bool(attempts) and attempts[-1]["passed"], "Invalid public-pass stop")
        feedback = attempts + [row["hidden"], row["first_hidden"]]
        wall_timeout = any(f.get("build", {}).get("timeout", False)
            or any(case.get("timeout", False) for case in f.get("failures", [])) for f in feedback)
        checks.append({"trial": path.parent.name, "schedule_usage_source_stop_checks": "passed",
                       "compiler_or_case_wall_timeout": wall_timeout,
                       "event_log_sha256": hashlib.sha256(log.read_bytes()).hexdigest()})
    validate_raw_prefix(batch, config, results)
    provenance = json.loads((batch / "recovery.json").read_text()) if (batch / "recovery.json").exists() else None
    start_name = provenance["original_batch"] if provenance else batch.name
    start = datetime.strptime(start_name, "%Y%m%dT%H%M%S%fZ").replace(tzinfo=timezone.utc)
    known_times = [r["elapsed_seconds"] for r in results if r["elapsed_seconds"] is not None]
    return {"batch": batch.name, "trials": len(results), "checks": checks,
            "batch_unchanged": not bool(provenance),
            "recovery": provenance,
            "agent_seconds": sum(known_times) if len(known_times) == len(results) else None,
            "recorded_agent_seconds": sum(known_times),
            "missing_timing_trials": len(results) - len(known_times),
            "wall_seconds_approx": (batch / "summary.json").stat().st_mtime - start.timestamp(),
            "timeouts": sum(r["stop"] == "timeout" for r in results),
            "compiler_or_case_wall_timeout_trials": sum(c["compiler_or_case_wall_timeout"] for c in checks),
            "incomplete_usage_trials": sum(not r["usage_complete"] for r in results),
            "infrastructure_errors": sum(r["infrastructure_error"] for r in results),
            "note": "Usage checks reconcile completed messages only. Wall time uses the original batch start, including recovery downtime if applicable. Missing agent time is not imputed."}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("batch", type=Path)
    args = parser.parse_args()
    print(json.dumps(audit(args.batch), indent=2))
