#!/usr/bin/env python3
"""Compare two frozen confirmation batches without running pi or any model."""
import argparse
from collections import defaultdict
import hashlib
import json
from pathlib import Path
import random
import statistics
from recovery import validate_prefix

ROOT = Path(__file__).resolve().parent
REQUIRED_SOURCES = {"bench.py", "judge.py", "tasks.py", "extra_tasks.py", "pi/benchmark.ts",
                    "analysis.py", "experiments/study.json", "Modelfile", "checkpoints.py",
                    "recovery.py", "experiments/recovery-prefix.json"}

def interval(values):
    values = sorted(values)
    return [values[int(.025*len(values))], values[min(len(values)-1, int(.975*len(values)))]]

def pair_rows(rows):
    pairs = defaultdict(dict)
    for row in rows:
        key = (row["task"], row["repeat"])
        if row["language"] in pairs[key]:
            raise ValueError(f"Duplicate result: {key} {row['language']}")
        pairs[key][row["language"]] = row
    if any(set(pair) != {"c", "go"} for pair in pairs.values()):
        raise ValueError("Incomplete or unexpected language pair.")
    groups = defaultdict(list)
    for (task, _), pair in sorted(pairs.items()):
        groups[task].append(pair)
    return dict(groups)

def posterior(groups, prior, draws, seed):
    """Independent per-task Dirichlet posteriors over four PAIRED outcomes.

    Categories: both fail, Go only passes, C only passes, both pass.
    Task weights are equal. Intervals describe this fixed suite, not unseen tasks.
    """
    counts = []
    for pairs in groups.values():
        c = [prior]*4
        for pair in pairs:
            c[2*int(pair["c"]["success"]) + int(pair["go"]["success"])] += 1
        counts.append(c)
    rng = random.Random(seed)
    differences, c_rates, go_rates = [], [], []
    for _ in range(draws):
        c_rate = go_rate = 0.0
        for parameters in counts:
            values = [rng.gammavariate(a, 1) for a in parameters]
            total = sum(values)
            c_rate += (values[2]+values[3])/total/len(counts)
            go_rate += (values[1]+values[3])/total/len(counts)
        differences.append(go_rate-c_rate)
        c_rates.append(c_rate); go_rates.append(go_rate)
    return {"prior_per_category": prior,
            "go_minus_c_success_95_credible": interval(differences),
            "c_success_95_credible": interval(c_rates),
            "go_success_95_credible": interval(go_rates)}

def token_ratio(pairs):
    success = {lang: sum(pair[lang]["success"] for pair in pairs) for lang in ("c","go")}
    tokens = {lang: sum(pair[lang]["tokens"]["output"] for pair in pairs) for lang in ("c","go")}
    if not all(success.values()) or not all(tokens.values()):
        return None
    return (tokens["go"]/success["go"])/(tokens["c"]/success["c"])

def effort_interval(groups, draws, seed):
    pairs = [p for group in groups.values() for p in group]
    if any(not p[l].get("usage_complete", False) for p in pairs for l in ("c","go")):
        return None
    rng = random.Random(seed)
    ratios = []
    for _ in range(draws):
        sample = [rng.choice(group) for group in groups.values() for _ in group]
        ratio = token_ratio(sample)
        if ratio is None:
            return None  # Do not quietly discard zero-success bootstrap samples.
        ratios.append(ratio)
    return interval(ratios)

def classify(accuracy, effort, observed_rates, policy):
    low, high = accuracy["go_minus_c_success_95_credible"]
    margin = policy["success_margin"]
    if low > margin:
        return "go_accuracy_advantage"
    if high < -margin:
        return "c_accuracy_advantage"
    if not (-margin <= low and high <= margin):
        return "inconclusive"
    if effort is None or min(observed_rates.values()) < policy["minimum_success_rate_for_effort"]:
        return "accuracy_equivalent_effort_inconclusive"
    lower_ratio = 1-policy["effort_improvement"]
    upper_ratio = 1/lower_ratio
    if effort[1] < lower_ratio:
        return "go_effort_advantage"
    if effort[0] > upper_ratio:
        return "c_effort_advantage"
    if lower_ratio <= effort[0] and effort[1] <= upper_ratio:
        return "practical_tie"
    return "accuracy_equivalent_effort_inconclusive"

def analyze(rows, policy, draws=10000):
    groups = pair_rows(rows)
    pairs = [p for group in groups.values() for p in group]
    rates = {lang: statistics.mean(p[lang]["success"] for p in pairs) for lang in ("c","go")}
    differences = {task: statistics.mean(int(p["go"]["success"])-int(p["c"]["success"]) for p in group)
                   for task, group in groups.items()}
    credible = [posterior(groups, prior, draws, 703) for prior in (.5, 1.0)]
    effort = effort_interval(groups, draws, 704)
    decisions = [classify(p, effort, rates, policy) for p in credible]
    decision = decisions[0] if len(set(decisions)) == 1 else "prior_sensitive_inconclusive"
    # A claimed advantage must not be entirely carried by one workload.
    leave_one_out = {}
    if len(groups) > 1:
        for omitted in groups:
            rest = [p for task, group in groups.items() if task != omitted for p in group]
            leave_one_out[omitted] = {
                "go_minus_c_success": statistics.mean(int(p["go"]["success"])-int(p["c"]["success"]) for p in rest),
                "go_over_c_tokens_per_success": token_ratio(rest)}
    for values in leave_one_out.values():
        d, ratio = values["go_minus_c_success"], values["go_over_c_tokens_per_success"]
        if ((decision == "go_accuracy_advantage" and d <= 0)
            or (decision == "c_accuracy_advantage" and d >= 0)
            or (decision == "go_effort_advantage" and (ratio is None or ratio >= 1))
            or (decision == "c_effort_advantage" and (ratio is None or ratio <= 1))):
            decision = "task_sensitive_inconclusive"
    return {"decision": decision, "observed_success": rates,
            "go_minus_c_success_by_task": differences,
            "success_posteriors": credible,
            "go_over_c_tokens_per_success": token_ratio(pairs),
            "go_over_c_tokens_per_success_95_bootstrap": effort,
            "leave_one_task_out": leave_one_out,
            "tasks": len(groups), "pairs": len(pairs)}

def load_batch(path):
    path = Path(path)
    if path.is_file() or (path/"results.json").exists():
        payload = json.loads((path if path.is_file() else path/"results.json").read_text())
        return {"name": payload["batch"], "config": payload["config"], "rows": payload["runs"],
                "environment": payload["environment"], "model_digest": payload["model"]["digest"],
                "status": payload.get("batch_status"), "recovery": payload.get("recovery")}
    env = json.loads((path/"environment.json").read_text())
    return {"name": path.name, "config": json.loads((path/"config.json").read_text()),
            "environment": env, "model_digest": env.get("model_digest"),
            "status": json.loads((path/"status.json").read_text()) if (path/"status.json").exists() else None,
            "recovery": json.loads((path/"recovery.json").read_text()) if (path/"recovery.json").exists() else None,
            "rows": [json.loads(p.read_text()) for p in sorted(path.glob("*/result.json"))]}

def validate_batch(batch, study):
    config, env, rows = batch["config"], batch["environment"], batch["rows"]
    if config.get("purpose") != "confirmation" or config.get("study_id") != study["study_id"]:
        raise ValueError("Only this study's confirmation batches can establish replication; pilots are exploratory.")
    for name in ("pi", "clang", "go", "python", "ollama", "platform", "machine", "hardware"):
        if not env.get(name):
            raise ValueError("Missing environment evidence: " + name)
    phase = config.get("replication")
    if phase not in study["replications"]:
        raise ValueError("Unregistered replication.")
    expected = {**study["run_settings"], **study["replications"][phase],
                "replication": phase, "purpose": "confirmation", "study_id": study["study_id"]}
    if config != expected:
        raise ValueError("Configuration differs from the preregistered confirmation profile.")
    if batch["model_digest"] != config["model_digest"]:
        raise ValueError("Model digest differs from the pinned model.")
    status = batch.get("status") or {}
    if (status.get("state") != "complete" or status.get("source_sha256") != env.get("source_sha256")
            or status.get("model_digest") != batch["model_digest"]):
        raise ValueError("Batch did not finish with unchanged model and protocol snapshots.")
    fingerprints = env.get("source_sha256", {})
    if set(fingerprints) != REQUIRED_SOURCES:
        raise ValueError("Missing/unexpected protocol source hashes.")
    for name in ("analysis.py", "experiments/study.json", "recovery.py", "experiments/recovery-prefix.json"):
        if fingerprints[name] != hashlib.sha256((ROOT/name).read_bytes()).hexdigest():
            raise ValueError("Use the frozen analysis/study revision for these batches.")
    expected_keys = {(task, repeat, language) for task in config["tasks"]
                     for repeat in range(config["repeats"]) for language in config["languages"]}
    actual_keys = [(r["task"], r["repeat"], r["language"]) for r in rows]
    if len(actual_keys) != len(expected_keys) or set(actual_keys) != expected_keys:
        raise ValueError("Missing, duplicate, or unexpected trials; do not cherry-pick or stop early.")
    for row in rows:
        if type(row["success"]) is not bool or type(row["tokens"]["output"]) is not int or row["tokens"]["output"] < 0:
            raise ValueError("Invalid success or token measurement.")
        if row["infrastructure_error"] or row.get("errors"):
            raise ValueError("Infrastructure/provider errors invalidate a confirmation batch.")
        expected_seed = config["sampling_seed"] + config["tasks"].index(row["task"])*config["repeats"] + row["repeat"]
        if row["sampling_seed"] != expected_seed:
            raise ValueError("Unexpected sampling seed.")
    pair_rows(rows)
    validate_prefix(config, rows, batch.get("recovery"))

def compare(a, b, study, draws=10000):
    validate_batch(a, study); validate_batch(b, study)
    if a["config"]["replication"] == b["config"]["replication"]:
        raise ValueError("Need separate A and B replications, not the same batch twice.")
    if {r["sampling_seed"] for r in a["rows"]} & {r["sampling_seed"] for r in b["rows"]}:
        raise ValueError("Replication seed sets overlap.")
    for key in ("source_sha256", "pi", "clang", "go", "python", "ollama", "platform", "machine", "hardware"):
        if a["environment"].get(key) != b["environment"].get(key):
            raise ValueError("Batch environments/protocols differ: " + key)
    reports = [analyze(batch["rows"], study["decision_policy"], draws) for batch in (a,b)]
    decisions = [r["decision"] for r in reports]
    replicated = decisions[0] == decisions[1] and decisions[0] in {
        "go_accuracy_advantage", "c_accuracy_advantage", "go_effort_advantage",
        "c_effort_advantage", "practical_tie"}
    result = {"study_id": study["study_id"], "batches": [a["name"],b["name"]],
            "status": "replicated_on_frozen_suite" if replicated else "inconclusive",
            "decision": decisions[0] if replicated else None, "reports": reports,
            "scope": "Conditional on this fixed workload suite, model, prompt, and budgets; not a universal language ranking."}
    if study["run_settings"].get("recovery_amendment"):
        result["status"] = "replicated_under_recovery_amendment" if replicated else "inconclusive_under_recovery_amendment"
        result["recovery_amendment"] = study["run_settings"]["recovery_amendment"]
        result["scope"] += " Recovery amendment: A includes 320 retained observations and one recovered trial with missing timing. This is not the original unamended frozen confirmation."
    return result

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("batch_a", type=Path)
    parser.add_argument("batch_b", type=Path)
    args = parser.parse_args()
    study = json.loads((ROOT/"experiments/study.json").read_text())
    try:
        report = compare(load_batch(args.batch_a), load_batch(args.batch_b), study)
    except (ValueError, KeyError, FileNotFoundError) as error:
        parser.exit(2, f"Comparison rejected: {error}\n")
    print(json.dumps(report, indent=2, allow_nan=False))
