#!/usr/bin/env python3
"""Run frozen A then B, audit/export/analyze, and optionally commit/push reports.

This is an explicit many-hour inference command. It never resumes partial batches
or retries failed rows. Progress and errors are retained in .local/study-run.json.
"""
import argparse
from datetime import datetime, timezone
import json
from pathlib import Path
import re
import subprocess
import sys

import analysis
from audit_batch import audit
from bench import dump, source_hashes, validate_config
from export_report import export

ROOT = Path(__file__).resolve().parent
STATE = ROOT / ".local/study-run.json"


def command(args):
    return subprocess.check_output(args, cwd=ROOT, text=True, stderr=subprocess.STDOUT).strip()


def clean_tracked_tree():
    if command(["git", "status", "--porcelain", "--untracked-files=no"]):
        raise ValueError("Tracked or staged changes exist; refusing automatic publication")


def privacy_check(destination):
    # Deliberately conservative: a flagged export requires human review.
    pattern = re.compile(r"/Users/|/home/|-----BEGIN .*PRIVATE KEY-----|"
                         r"\b(?:ghp_|github_pat_|sk-proj-)[A-Za-z0-9_]{12,}|"
                         r"\bBearer\s+[A-Za-z0-9_.-]{16,}")
    for path in destination.rglob("*"):
        if path.is_file() and pattern.search(path.read_text()):
            raise ValueError("Export requires privacy review: " + str(path.relative_to(ROOT)))


def report_markdown(result, batches, audits):
    lines = ["# Frozen C/Go confirmation results", "",
             f"Study: `{result['study_id']}`. Status: **{result['status']}**.", "",
             f"Replicated decision: **{result['decision'] or 'none; inconclusive'}**.", "",
             "Both complete batches used the preregistered settings and decision rule.",
             "No failed rows were selectively rerun and the two batches were not pooled.", "",
             "| Batch | C successes | Go successes | Decision | Wall hours |",
             "| --- | --- | --- | --- | --- |"]
    for batch, report, evidence in zip(batches, result["reports"], audits):
        rows = batch["rows"]
        rates = []
        for lang in ("c", "go"):
            selected = [r for r in rows if r["language"] == lang]
            rates.append(f"{sum(r['success'] for r in selected)}/{len(selected)}")
        lines.append(f"| [{batch['config']['replication']}](../{batch['name']}/README.md) | "
                     f"{rates[0]} | {rates[1]} | {report['decision']} | {evidence['wall_seconds_approx']/3600:.2f} |")
    for batch, report in zip(batches, result["reports"]):
        lines += ["", "## Replication " + batch["config"]["replication"], "",
                  "Go-minus-C correctness difference, 95% Bayesian credible intervals:", ""]
        for posterior in report["success_posteriors"]:
            low, high = posterior["go_minus_c_success_95_credible"]
            lines.append(f"- Prior {posterior['prior_per_category']} per paired category: "
                         f"[{100*low:.2f}, {100*high:.2f}] percentage points.")
        lines += ["", "Effort includes generated tokens from unsuccessful trials.",
                  "It can determine a winner only after the registered correctness-equivalence",
                  "and minimum-success conditions hold. See analysis.json for its bootstrap",
                  "interval, prior sensitivity, and leave-one-workload-out diagnostics."]
    lines += ["", "## Audit and scope", "",
              "Every trial was checked against its schedule, completed-response usage events,",
              "source revisions, and stopping rule. Batch-end source/model fingerprints and",
              "cross-batch environments passed the frozen validator. Each batch report includes",
              "audit.json and every generated source revision. Raw traces remain local; their",
              "SHA-256 hashes are in the audit records. Exports passed an automated privacy scan.", "",
              result["scope"], "",
              "These are generation replications on the same ten workloads and local model,",
              "not evidence of transfer to unseen problems or other models. A stable result",
              "is a baseline for follow-up work, not proof that a new language will help.",
              "If inconclusive, retain that conclusion; a larger experiment needs a new plan.", "",
              "Reproduce the analysis without inference:", "", "```sh",
              f"python3 analysis.py reports/{batches[0]['name']} reports/{batches[1]['name']}",
              "```", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--publish", action="store_true", help="Commit and push only validated portable reports")
    args = parser.parse_args()
    STATE.parent.mkdir(exist_ok=True)
    if STATE.exists():
        raise ValueError("An execution record already exists; inspect/archive it before starting a new full study")
    clean_tracked_tree()
    branch = command(["git", "branch", "--show-current"])
    if not branch:
        raise ValueError("A named branch is required")
    frozen = source_hashes()
    study = json.loads((ROOT / "experiments/study.json").read_text())
    profiles = [ROOT / "experiments" / f"confirm-{phase}.json" for phase in ("a", "b")]
    configs = [json.loads(p.read_text()) for p in profiles]
    for config in configs:
        validate_config(config)
    destination = ROOT / "reports" / study["study_id"]
    if destination.exists():
        raise ValueError("Study report destination already exists; refusing to overwrite evidence")
    state = {"stage": "starting", "started_utc": datetime.now(timezone.utc).isoformat(),
             "registration_commit": command(["git", "rev-parse", "HEAD"]), "batches": [],
             "publish_requested": args.publish}

    def update(stage):
        state["stage"] = stage
        state["updated_utc"] = datetime.now(timezone.utc).isoformat()
        dump(STATE, state)
        print(stage, flush=True)

    try:
        batches, audits = [], []
        for profile, config in zip(profiles, configs):
            if source_hashes() != frozen or json.loads(profile.read_text()) != config:
                raise ValueError("Protocol/profile changed before replication")
            update("running_" + config["replication"])
            batch_path = None
            with subprocess.Popen([sys.executable, "-u", "bench.py", "run", "--config", str(profile)],
                                  cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True) as process:
                for line in process.stdout:
                    print(line, end="", flush=True)
                    if line.startswith("Batch: "):
                        batch_path = Path(line[7:].strip())
                        state["batches"].append(batch_path.name)
                        dump(STATE, state)
                code = process.wait()
            if code or batch_path is None:
                raise RuntimeError("Replication failed; artifacts retained, no automatic retry")
            batch = analysis.load_batch(batch_path)
            analysis.validate_batch(batch, study)
            evidence = audit(batch_path)
            if evidence["compiler_or_case_wall_timeout_trials"]:
                raise ValueError("Wall-timeout evidence invalidates confirmation")
            batches.append(batch)
            audits.append(evidence)
        update("validating_and_exporting")
        if source_hashes() != frozen:
            raise ValueError("Protocol changed")
        result = analysis.compare(*batches, study)
        clean_tracked_tree()
        destinations = []
        for batch, evidence in zip(batches, audits):
            target = export(ROOT / "runs" / batch["name"], ROOT / "reports" / batch["name"])
            dump(target / "audit.json", evidence)
            privacy_check(target)
            destinations.append(target)
        destination.mkdir()
        dump(destination / "analysis.json", result)
        dump(destination / "execution.json", {**state, "stage": "validated", "source_sha256": frozen})
        (destination / "README.md").write_text(report_markdown(result, batches, audits))
        privacy_check(destination)
        destinations.append(destination)
        # Verify portable evidence gives the identical answer before publication.
        portable = analysis.compare(*(analysis.load_batch(p) for p in destinations[:2]), study)
        if portable != result:
            raise ValueError("Portable analysis differs from raw analysis")
        state["result"] = {"status": result["status"], "decision": result["decision"]}
        state["report"] = str(destination.relative_to(ROOT))
        if args.publish:
            update("publishing")
            clean_tracked_tree()
            if command(["git", "branch", "--show-current"]) != branch:
                raise ValueError("Branch changed during execution")
            command(["git", "add", "--"] + [str(p.relative_to(ROOT)) for p in destinations])
            command(["git", "diff", "--cached", "--check"])
            print(command(["git", "commit", "-m", "Publish audited frozen C/Go confirmation results"]), flush=True)
            state["results_commit"] = command(["git", "rev-parse", "HEAD"])
            print(command(["git", "push", "origin", branch]), flush=True)
            if command(["git", "rev-parse", "HEAD"]) != command(["git", "rev-parse", "origin/" + branch]):
                raise RuntimeError("Remote-tracking revision does not match published commit")
        update("complete")
    except BaseException as error:
        state["error"] = str(error)
        update("stopped_with_error")
        raise


if __name__ == "__main__":
    main()
