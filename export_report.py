#!/usr/bin/env python3
"""Export a completed batch as a portable, reviewable repository report."""
import argparse
import json
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parent

def export(batch, destination):
    summary = json.loads((batch / "summary.json").read_text())
    config = json.loads((batch / "config.json").read_text())
    environment = json.loads((batch / "environment.json").read_text())
    schedule = json.loads((batch / "schedule.json").read_text())
    trials = sorted(batch.glob("*/result.json"))
    if len(trials) != len(schedule):
        raise ValueError("Batch is incomplete; export only a completed batch.")
    status = json.loads((batch/"status.json").read_text()) if (batch/"status.json").exists() else None
    if config.get("protocol_version") == 2 and (not status or status.get("state") != "complete"):
        raise ValueError("Protocol v2 exports require a completed, unchanged batch.")
    destination.mkdir(parents=True, exist_ok=False)
    records = []
    for path in trials:
        result = json.loads(path.read_text())
        # Omit compiler diagnostics and raw traces, which can include local paths.
        records.append({k: v for k, v in result.items()
                        if k not in ("hidden", "first_hidden", "errors", "tool_errors")})
        revisions = path.parent / "work" / "revisions"
        if revisions.exists():
            target = destination / "sources" / path.parent.name
            target.mkdir(parents=True)
            for source in sorted(revisions.iterdir()):
                if source.suffix in (".c", ".go"):
                    shutil.copyfile(source, target / source.name)
    model_id = config["model"] if ":" in config["model"] else config["model"] + ":latest"
    model = next(m for m in environment["model_tags"]["models"] if m["name"] == model_id)
    payload = {
        "batch": batch.name, "config": config, "summary": summary, "runs": records, "batch_status": status,
        "environment": {k: environment[k] for k in
                        ("platform", "machine", "hardware", "python", "pi", "clang", "go", "ollama",
                         "git_commit", "source_sha256") if k in environment},
        "model": {"name": model["name"], "digest": model["digest"],
                  "size_bytes": model["size"], "details": environment["model"]["details"],
                  "parameters": environment["model"]["parameters"]},
    }
    if (batch / "recovery.json").exists():
        payload["recovery"] = json.loads((batch / "recovery.json").read_text())
    (destination / "results.json").write_text(json.dumps(payload, indent=2) + "\n")
    lines = ["# Local C/Go experiment", "",
             f"Batch: {batch.name}. Model: {config['model']}.", "",
             f"Tasks: {', '.join(config['tasks'])}. Repeats per language/task: {config['repeats']}.", "",
             "This is exploratory evidence on a small fixed task suite, not a language ranking.",
             "Only this batch is included. Every generated source revision is included under sources/.",
             "Raw event traces, prompts, and full diagnostics remain in the local batch directory.",
             "", "| Language | Passed | First source passed | Mean submissions | Output tokens / success | Median seconds |",
             "| --- | --- | --- | --- | --- | --- |"]
    for language, stats in summary["languages"].items():
        tokens = stats["output_tokens_per_success"]
        token_text = f"{tokens:.1f}" if tokens is not None else "undefined"
        median = stats["median_seconds"]
        median_text = f"{median:.1f}" if median is not None else "incomplete timing"
        lines.append(f"| {language} | {stats['successes']}/{stats['runs']} | "
                     f"{stats['first_submission_successes']}/{stats['runs']} | "
                     f"{stats['mean_submissions']:.2f} | {token_text} | {median_text} |")
    lines.extend(["", "See results.json for all settings, per-run metrics, model digest, and source hashes.",
                  "First-source scoring is independent of whether the agent later finishes successfully."])
    if config.get("protocol_version") == 2:
        lines.extend(["The controller stopped at the first public pass or submission limit.",
                      "A public pass is not a held-out success. Protocol v1 results cannot be pooled with this batch."])
    else:
        lines.extend(["Effort includes any unnecessary resubmissions after public tests pass.",
                      "This historical protocol asked the agent to stop but did not force it."])
    lines.append("")
    if config.get("recovery_amendment"):
        lines.extend(["This is the amended JSONL recovery study, not the original frozen confirmation.",
                      "A retains 320 original results and one recovered trial with missing timing.",
                      "Timing aggregates affected by that missing value are not presented as complete.", ""])
    (destination / "README.md").write_text("\n".join(lines))
    return destination

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("batch", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    print(export(args.batch, args.output or ROOT / "reports" / args.batch.name))
