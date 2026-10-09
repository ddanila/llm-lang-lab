"""Validate the specifically authorized JSONL recovery; not a general resume bypass."""
import hashlib
import json
from pathlib import Path

REGISTRY = Path(__file__).resolve().parent / "experiments/recovery-prefix.json"
AMENDMENT = "jsonl-recovery-2026-10-09"
OMIT = {"hidden", "first_hidden", "errors", "tool_errors"}


def portable(row):
    return {k: v for k, v in row.items() if k not in OMIT}


def row_hash(row):
    return hashlib.sha256(json.dumps(portable(row), sort_keys=True,
                                    separators=(",", ":"), allow_nan=False).encode()).hexdigest()


def registry():
    return json.loads(REGISTRY.read_text())


def validate_prefix(config, rows, provenance):
    if not config.get("recovery_amendment"):
        if provenance is not None:
            raise ValueError("Unregistered recovery provenance")
        return
    if config["recovery_amendment"] != AMENDMENT:
        raise ValueError("Unknown recovery amendment")
    registration = registry()
    if config["replication"] == "B":
        if provenance is not None or any(r.get("elapsed_seconds") is None for r in rows):
            raise ValueError("B cannot import recovered rows or missing timing")
        return
    if provenance != registration["provenance"]:
        raise ValueError("Missing or changed recovery provenance")
    imported = registration["rows"]
    if len(rows) < len(imported):
        raise ValueError("Recovery prefix is incomplete")
    for row, registered in zip(rows, imported):
        if row_hash(row) != registered["portable_sha256"]:
            raise ValueError("Imported observation changed: " + registered["trial"])
    if any(r.get("elapsed_seconds") is None for r in rows[len(imported):]):
        raise ValueError("Missing timing outside registered recovery")


def validate_raw_prefix(batch, config, rows):
    path = batch / "recovery.json"
    provenance = json.loads(path.read_text()) if path.exists() else None
    validate_prefix(config, rows, provenance)
    if provenance is None:
        return
    registration = registry()
    metadata_names = {"config.json": "original-config.json", "environment.json": "original-environment.json",
                      "status.json": "original-status.json", "schedule.json": "schedule.json"}
    for name, expected in registration.get("original_metadata_sha256", {}).items():
        if hashlib.sha256((batch / metadata_names[name]).read_bytes()).hexdigest() != expected:
            raise ValueError("Original registration metadata changed: " + name)
    for entry in registration["rows"]:
        for name, expected in entry["evidence_sha256"].items():
            path = batch / entry["trial"] / name
            if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
                raise ValueError("Imported raw evidence changed: " + str(path))


def recovery_boundary(batch, completed):
    config = json.loads((batch / "config.json").read_text())
    if config.get("recovery_amendment") != AMENDMENT or config.get("replication") != "A":
        return False
    if completed != len(registry()["rows"]):
        return False
    rows = [json.loads(p.read_text()) for p in sorted(batch.glob("*/result.json"))]
    validate_raw_prefix(batch, config, rows)
    return len(rows) == completed
