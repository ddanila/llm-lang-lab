"""Sealed pair-boundary checkpoints and portable, explicitly partial backups."""
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import shutil

ENV_KEYS = ("source_sha256", "model_digest", "pi", "clang", "go", "python",
            "ollama", "hardware", "platform", "machine")


def read(path):
    return json.loads(Path(path).read_text())


def write(path, value):
    path = Path(path)
    temporary = path.with_name(path.name + ".tmp")
    temporary.write_text(json.dumps(value, indent=2) + "\n")
    temporary.replace(path)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def evidence_hashes(batch):
    paths = [batch / name for name in ("config.json", "environment.json", "schedule.json")]
    for trial in sorted(p for p in batch.iterdir() if p.is_dir()):
        if not (trial / "result.json").exists():
            raise ValueError("Unfinished trial exists; refusing to replay it")
        paths += [trial / name for name in ("result.json", "events.jsonl", "prompt.txt", "system.txt")]
        paths += list((trial / "work/revisions").glob("*"))
        paths += [p for p in (trial / "work/attempts.jsonl", trial / "work/main.c",
                              trial / "work/main.go") if p.exists()]
    return {str(p.relative_to(batch)): digest(p) for p in sorted(paths)}


def check_environment(original, current):
    for key in ENV_KEYS:
        if original.get(key) != current.get(key):
            raise ValueError("Checkpoint environment changed: " + key)


def seal(batch, completed, snapshot):
    if completed <= 0 or completed % 2:
        raise ValueError("Checkpoint requires complete C/Go pairs")
    write(batch / "checkpoint.json", {"completed_trials": completed,
          "evidence_sha256": evidence_hashes(batch)})
    write(batch / "status.json", {"state": "checkpoint", "completed_trials": completed,
          "checkpoint_sha256": digest(batch / "checkpoint.json"),
          "source_sha256": snapshot["source_sha256"], "model_digest": snapshot["model_digest"]})


def resume_rows(batch, config, current, jobs):
    status = read(batch / "status.json")
    if status.get("state") != "checkpoint":
        raise ValueError("Resume requires a clean checkpoint, not a running/invalid batch")
    if read(batch / "config.json") != config or read(batch / "schedule.json") != jobs:
        raise ValueError("Checkpoint config/schedule changed")
    check_environment(read(batch / "environment.json"), current)
    if status["checkpoint_sha256"] != digest(batch / "checkpoint.json"):
        raise ValueError("Checkpoint manifest changed")
    manifest = read(batch / "checkpoint.json")
    if manifest["evidence_sha256"] != evidence_hashes(batch):
        raise ValueError("Checkpoint evidence changed")
    paths = sorted(batch.glob("*/result.json"))
    count = len(paths)
    if count != status["completed_trials"] or count != manifest["completed_trials"] or count % 2 or not 0 < count < len(jobs):
        raise ValueError("Invalid checkpoint prefix")
    rows = []
    for i, path in enumerate(paths):
        row, job = read(path), jobs[i]
        expected = f"{i:03d}-{job['task']}-{job['language']}-r{job['repeat']}"
        if path.parent.name != expected or any(row[k] != v for k, v in job.items()) or row["infrastructure_error"]:
            raise ValueError("Invalid checkpoint trial")
        rows.append(row)
    return rows


def export_progress(batch, destination):
    """Never mark partial/invalid evidence as a completed confirmation report."""
    config, environment, status = [read(batch / name) for name in
                                  ("config.json", "environment.json", "status.json")]
    jobs = read(batch / "schedule.json")
    destination.mkdir(parents=True, exist_ok=True)
    rows, hashes = [], {}
    for path in sorted(batch.glob("*/result.json")):
        row = read(path)
        rows.append({k: v for k, v in row.items() if k not in
                     ("hidden", "first_hidden", "errors", "tool_errors")})
        log = path.parent / "events.jsonl"
        hashes[path.parent.name] = digest(log)
        for source in sorted((path.parent / "work/revisions").glob("*")):
            if source.suffix not in (".c", ".go"):
                continue
            target = destination / "sources" / path.parent.name / source.name
            target.parent.mkdir(parents=True, exist_ok=True)
            if target.exists() and target.read_bytes() != source.read_bytes():
                raise ValueError("Previously published source changed")
            if not target.exists():
                shutil.copyfile(source, target)
    payload = {"batch": batch.name, "config": config, "runs": rows,
               "batch_status": {"state": "checkpoint_only_not_confirmation",
                                "local_batch_state": status["state"]},
               "completed_trials": len(rows), "planned_trials": len(jobs),
               "updated_utc": datetime.now(timezone.utc).isoformat(),
               "environment": {k: environment[k] for k in ENV_KEYS + ("git_commit",) if k in environment},
               "event_log_sha256": hashes,
               "note": "Progress backup only; incomplete/invalid data cannot establish a language ranking. Raw traces remain local."}
    write(destination / "progress.json", payload)
    (destination / "README.md").write_text(
        f"# Study progress: {batch.name}\n\n"
        f"Study: `{config['study_id']}`; replication: {config.get('replication', 'calibration')}.\n\n"
        f"**{len(rows)}/{len(jobs)} trials recorded. Local state: {status['state']}.**\n\n"
        "This is a progress backup, not a confirmation result or language ranking.\n"
        "Every completed trial is retained, including failures. Generated source revisions\n"
        "and portable metrics are backed up here; raw traces and local agent state remain\n"
        "on the laptop. Raw-trace hashes allow later integrity checks. Each Git commit\n"
        "preserves the previous checkpoint. No individual failed trials are rerun.\n")
    return destination
