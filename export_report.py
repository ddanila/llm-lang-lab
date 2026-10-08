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
        "batch": batch.name, "config": config, "summary": summary, "runs": records,
        "environment": {k: environment[k] for k in
                        ("platform", "machine", "python", "pi", "clang", "go", "ollama",
                         "git_commit", "source_sha256")},
        "model": {"name": model["name"], "digest": model["digest"],
                  "size_bytes": model["size"], "details": environment["model"]["details"],
                  "parameters": environment["model"]["parameters"]},
    }
    (destination / "results.json").write_text(json.dumps(payload, indent=2) + "\n")
    lines = ["# Local C/Go pilot", "",
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
        lines.append(f"| {language} | {stats['successes']}/{stats['runs']} | "
                     f"{stats['first_submission_successes']}/{stats['runs']} | "
                     f"{stats['mean_submissions']:.2f} | {token_text} | {stats['median_seconds']:.1f} |")
    lines.extend(["", "See results.json for all settings, per-run metrics, model digest, and source hashes.",
                  "First-source scoring is independent of whether the agent later finishes successfully.",
                  "Effort includes any unnecessary resubmissions after public tests pass.",
                  "The current runner asks the agent to stop after a public pass but does not force it.",
                  "This behavior must be considered when interpreting effort differences.", ""])
    (destination / "README.md").write_text("\n".join(lines))
    return destination

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("batch", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    print(export(args.batch, args.output or ROOT / "reports" / args.batch.name))
