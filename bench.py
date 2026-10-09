#!/usr/bin/env python3
"""Local pi language comparison. Python 3.9+, no pip dependencies."""
import argparse
from collections import defaultdict
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import queue
import random
import shutil
import signal
import statistics
import subprocess
import sys
import threading
import time
import urllib.request
from urllib.parse import urlparse

from judge import evaluate
from tasks import SPECS, cases
from checkpoints import check_environment, read_jsonl, resume_rows, seal, write as atomic_write

ROOT = Path(__file__).resolve().parent
SOURCE_FILES = ["bench.py", "judge.py", "tasks.py", "extra_tasks.py", "pi/benchmark.ts",
                "analysis.py", "experiments/study.json", "Modelfile", "checkpoints.py",
                "recovery.py", "experiments/recovery-prefix.json"]
SYSTEM = """You are solving a programming benchmark. Use only the requested language
and its standard library. Your only tool is submit_source: send the entire source
file to compile and test. Use its feedback to repair failures. When public tests
pass, stop. Do not explain your solution, use Markdown, or call unavailable tools.
Implement the full specification, not just examples. No filesystem access, network,
subprocesses, or environment inspection in the submitted program: stdin/stdout only."""

def dump(path, obj):
    atomic_write(path, obj)

def api(base, path, payload=None, timeout=120):
    data = None if payload is None else json.dumps(payload).encode()
    request = urllib.request.Request(base + path, data=data, headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(request, timeout=timeout) as response:
        return json.load(response)

def version(command):
    return subprocess.check_output(command, text=True, stderr=subprocess.STDOUT).splitlines()[0]

def source_hashes():
    return {name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest() for name in SOURCE_FILES}

def validate_config(config):
    if config.get("protocol_version") != 2:
        raise ValueError("New runs require protocol_version 2; historical batches remain reportable.")
    if config.get("languages") != ["c", "go"]:
        raise ValueError("This comparison requires languages ['c', 'go'].")
    if not config.get("tasks") or len(set(config["tasks"])) != len(config["tasks"]):
        raise ValueError("Task list must be nonempty and unique.")
    if set(config["tasks"]) - SPECS.keys():
        raise ValueError("Unknown task in config.")
    for key in ("repeats", "max_turns", "max_submissions", "max_seconds", "max_output_per_turn", "context"):
        if type(config[key]) is not int or config[key] < 1:
            raise ValueError(key + " must be a positive integer.")
    for key in ("sampling_seed", "schedule_seed"):
        if type(config[key]) is not int or config[key] < 0:
            raise ValueError(key + " must be a nonnegative integer.")
    if config["sampling_seed"] + len(config["tasks"]) * config["repeats"] >= 2**31:
        raise ValueError("Sampling seed range must fit signed 32-bit integers.")
    if not 0 <= config["temperature"] <= 2 or not 0 < config["top_p"] <= 1:
        raise ValueError("Invalid sampling parameters.")
    url = urlparse(config["ollama_url"])
    if url.scheme != "http" or url.hostname not in ("localhost", "127.0.0.1", "::1"):
        raise ValueError("This local experiment requires a loopback HTTP Ollama endpoint.")
    if config.get("purpose") == "confirmation":
        study = json.loads((ROOT / "experiments/study.json").read_text())
        phase = config.get("replication")
        if phase not in study["replications"]:
            raise ValueError("Unregistered replication.")
        expected = {**study["run_settings"], **study["replications"][phase],
                    "replication": phase, "purpose": "confirmation", "study_id": study["study_id"]}
        if config != expected:
            raise ValueError("Confirmation config differs from the frozen study; prepare a new study for changes.")

def environment(config):
    hardware = {"cpu": platform.processor() or platform.machine(), "logical_cpus": os.cpu_count()}
    if sys.platform == "darwin":
        hardware.update(cpu=version(["sysctl", "-n", "machdep.cpu.brand_string"]),
                        memory_bytes=int(version(["sysctl", "-n", "hw.memsize"])))
    snapshot = {
        "platform": platform.platform(), "machine": platform.machine(),
        "hardware": hardware,
        "python": platform.python_version(), "pi": version(["pi", "--version"]),
        "clang": version(["clang", "--version"]), "go": version(["go", "version"]),
        "ollama": api(config["ollama_url"], "/api/version"),
        "model": api(config["ollama_url"], "/api/show", {"model": config["model"]}),
        "model_tags": api(config["ollama_url"], "/api/tags"),
        "git_commit": subprocess.run(["git", "rev-parse", "--verify", "HEAD"], cwd=ROOT,
                                     capture_output=True, text=True).stdout.strip() or None,
        "source_sha256": source_hashes(),
    }
    model_id = config["model"] if ":" in config["model"] else config["model"] + ":latest"
    model = next(m for m in snapshot["model_tags"]["models"] if m["name"] == model_id)
    snapshot["model_digest"] = model["digest"]
    if config.get("model_digest") and model["digest"] != config["model_digest"]:
        raise ValueError("Model digest changed. Freeze a new protocol instead of silently replacing weights/settings.")
    parameters = snapshot["model"].get("parameters", "")
    import re
    context = re.search(r"^num_ctx\s+(\d+)", parameters, re.MULTILINE)
    if not context or int(context[1]) != config["context"]:
        raise ValueError("The model alias num_ctx must match the configured context.")
    return snapshot

def schedule(config):
    rng = random.Random(config["schedule_seed"])
    first_languages = {task: rng.randrange(2) for task in config["tasks"]}
    task_indices = {task: i for i, task in enumerate(config["tasks"])}
    jobs = []
    for repeat in range(config["repeats"]):
        tasks = list(config["tasks"])
        rng.shuffle(tasks)
        for task in tasks:
            languages = list(config["languages"])
            if (first_languages[task] + repeat) % 2:
                languages.reverse()
            for language in languages:
                jobs.append({"task": task, "language": language, "repeat": repeat,
                             "sampling_seed": config.get("sampling_seed", config["schedule_seed"])
                             + task_indices[task] * config["repeats"] + repeat})
    return jobs

def prompt_for(task, language, max_submissions):
    name = "C17 (main.c)" if language == "c" else "Go (main.go)"
    examples = "\n".join("Input: " + json.dumps(c["input"]) + "\nOutput: " + json.dumps(c["expected"])
                         for c in cases(task))
    return (f"Implement a standalone stdin/stdout program in {name}.\n{SPECS[task]}\n"
            f"Output is compared as whitespace-separated tokens.\nPublic examples:\n{examples}\n"
            f"You have at most {max_submissions} source submissions. Call submit_source now.")

def parse_events(events):
    usage = {"input": 0, "output": 0, "cacheRead": 0, "cacheWrite": 0}
    turns, tools, errors, missing_usage = 0, 0, [], False
    tool_errors = []
    for event in events:
        if event["type"] == "message_end" and event.get("message", {}).get("role") == "assistant":
            message = event["message"]
            turns += 1
            reported = message.get("usage") or {}
            missing_usage |= any(type(reported.get(key)) is not int or reported[key] < 0
                                 for key in ("input", "output"))
            for key in usage:
                value = reported.get(key, 0)
                if type(value) is int and value >= 0:
                    usage[key] += value
                else:
                    missing_usage = True
            if message.get("stopReason") in ("error", "aborted"):
                errors.append(message.get("errorMessage", message["stopReason"]))
        if event["type"] == "tool_execution_start":
            tools += 1
        if event["type"] == "tool_execution_end" and event.get("isError"):
            tool_errors.append(str(event.get("result", {}))[:2000])
    return {"tokens": usage, "assistant_turns": turns, "tool_calls": tools,
            "errors": errors, "tool_errors": tool_errors, "usage_missing": missing_usage}

def run_one(batch, config, job, index):
    trial = batch / f"{index:03d}-{job['task']}-{job['language']}-r{job['repeat']}"
    work, agent = trial / "work", trial / "agent"
    work.mkdir(parents=True); agent.mkdir()
    model = {"id": config["model"], "reasoning": False, "input": ["text"],
             "contextWindow": config["context"], "maxTokens": config["max_output_per_turn"],
             "samplingParams": {"temperature": config["temperature"], "top_p": config["top_p"],
                                "seed": job["sampling_seed"], "reasoning_effort": "none",
                                "max_tokens": config["max_output_per_turn"]}}
    dump(agent / "models.json", {"providers": {"local-bench": {
        "baseUrl": config["ollama_url"] + "/v1", "api": "openai-completions",
        "apiKey": "local-only", "models": [model]}}})
    dump(agent / "settings.json", {"compaction": {"enabled": False},
                                   "retry": {"enabled": False, "provider": {"maxRetries": 0}}})
    prompt = prompt_for(job["task"], job["language"], config["max_submissions"])
    (trial / "prompt.txt").write_text(prompt)
    (trial / "system.txt").write_text(SYSTEM)
    env = {"PATH": os.environ["PATH"], "HOME": str(agent), "LANG": "en_US.UTF-8",
           "PI_CODING_AGENT_DIR": str(agent), "PI_OFFLINE": "1", "PI_TELEMETRY": "0",
           "BENCH_WORK": str(work), "BENCH_ROOT": str(ROOT), "BENCH_LANGUAGE": job["language"],
           "BENCH_TASK": job["task"], "BENCH_ATTEMPTS": str(config["max_submissions"]),
           "BENCH_PYTHON": sys.executable}
    command = ["pi", "--print", "--mode", "json", "--provider", "local-bench",
               "--model", config["model"], "--thinking", "off",
               "--no-session", "--no-extensions", "--no-skills", "--no-mcp",
               "--no-context-files", "--no-prompt-templates", "--no-themes", "--no-approve",
               "--no-builtin-tools", "--extension", str(ROOT / "pi/benchmark.ts"),
               "--system-prompt", SYSTEM, "--offline", prompt]
    events, stop = [], "completed"
    started = time.monotonic()
    with (trial / "stderr.txt").open("w") as err, (trial / "events.jsonl").open("w") as log:
        proc = subprocess.Popen(command, cwd=work, env=env, stdout=subprocess.PIPE,
                                stderr=err, text=True, start_new_session=True)
        records = queue.Queue()
        def read():
            for line in proc.stdout:
                records.put(line)
            records.put(None)
        reader = threading.Thread(target=read, daemon=True)
        reader.start()
        turns = 0
        try:
            while True:
                remaining = config["max_seconds"] - (time.monotonic() - started)
                if remaining <= 0:
                    stop = "timeout"
                    break
                try:
                    line = records.get(timeout=min(remaining, 0.25))
                except queue.Empty:
                    continue
                if line is None:
                    break
                log.write(line); log.flush()
                try:
                    event = json.loads(line)
                except json.JSONDecodeError:
                    stop = "invalid_event_stream"
                    break
                events.append(event)
                if event["type"] == "tool_execution_end" and event.get("toolName") == "submit_source":
                    details = event.get("result", {}).get("details", {})
                    reason = details.get("controller_stop")
                    if reason in ("public_pass", "submission_budget"):
                        stop = reason
                        break
                    if event.get("isError") and "Judge infrastructure error" in str(event.get("result")):
                        stop = "infrastructure_error"
                        break
                if event["type"] == "turn_end":
                    turns += 1
                    if (turns >= config["max_turns"]
                            and event.get("message", {}).get("stopReason") == "toolUse"):
                        stop = "turn_budget"
                        break
        finally:
            if stop == "completed":
                # EOF may precede process exit by a few milliseconds. Do not turn
                # a normal completion into SIGTERM/error, or race a disappearing group.
                try:
                    proc.wait(timeout=3)
                except subprocess.TimeoutExpired:
                    stop = "shutdown_timeout"
            if proc.poll() is None:
                try:
                    try:
                        os.killpg(proc.pid, signal.SIGTERM)
                    except PermissionError:
                        proc.terminate()
                    proc.wait(timeout=3)
                except (ProcessLookupError, subprocess.TimeoutExpired):
                    try:
                        os.killpg(proc.pid, signal.SIGKILL)
                    except PermissionError:
                        proc.kill()
                    except ProcessLookupError:
                        pass
            proc.wait()
            reader.join(timeout=1)
            proc.stdout.close()
    elapsed = time.monotonic() - started
    # Preserve measured terminal facts before any fallible post-processing/judging.
    # This record is evidence, not permission to replay or auto-resume an invalid trial.
    dump(trial / "agent_completion.json", {**job, "stop": stop,
         "returncode": proc.returncode, "elapsed_seconds": elapsed})
    metrics = parse_events(events)
    attempts_file = work / "attempts.jsonl"
    attempts = read_jsonl(attempts_file) if attempts_file.exists() else []
    # Held-out tests are never returned to pi and run only after its process exits.
    hidden = evaluate(work, job["language"], job["task"], hidden=True)
    first = {"passed": False}
    revisions = work / "revisions"
    filename = "main.c" if job["language"] == "c" else "main.go"
    revision = revisions / ("1-" + filename)
    if revision.exists():
        first_work = trial / "first_submission"
        first_work.mkdir()
        shutil.copyfile(revision, first_work / filename)
        first = evaluate(first_work, job["language"], job["task"], hidden=True)
    infrastructure = ((proc.returncode != 0 and stop == "completed") or bool(metrics["errors"])
                      or stop in ("invalid_event_stream", "infrastructure_error", "shutdown_timeout")
                      or (stop == "timeout" and config.get("purpose") == "confirmation")
                      or any("Judge infrastructure error" in e for e in metrics["tool_errors"]))
    if config.get("purpose") == "confirmation":
        # V3 defines candidate execution limits as part of correctness within budget.
        # Compiler, provider and agent timeouts remain infrastructure failures.
        for feedback in attempts + [hidden, first]:
            infrastructure |= bool(feedback.get("build", {}).get("timeout"))
            if config.get("case_timeout_policy") != "candidate_failure":
                infrastructure |= any(f.get("timeout", False) for f in feedback.get("failures", []))
    controlled = stop in ("public_pass", "submission_budget")
    valid_finish = (controlled or (stop == "completed" and proc.returncode == 0)) and not infrastructure
    success = valid_finish and bool(attempts and attempts[-1]["passed"]) and hidden["passed"]
    result = {**job, **metrics, "stop": stop, "returncode": proc.returncode,
              "infrastructure_error": infrastructure, "elapsed_seconds": elapsed,
              "submissions": len(list(revisions.glob("*"))) if revisions.exists() else 0,
              "compile_failures": sum(a["kind"] == "compile_error" for a in attempts),
              "success": success, "first_submission_passed": bool(attempts and attempts[0]["passed"] and first["passed"]),
              "usage_complete": not metrics["usage_missing"] and stop not in
                  ("timeout", "invalid_event_stream", "infrastructure_error", "shutdown_timeout") and not metrics["errors"],
              "hidden": hidden, "first_hidden": first,
              "par2_seconds": elapsed if success else 2 * config["max_seconds"]}
    dump(trial / "result.json", result)
    print(f"{index+1:2d}: {job['task']:16s} {job['language']:2s} "
          f"{'PASS' if success else 'FAIL':4s} {elapsed:6.1f}s "
          f"{metrics['tokens']['output']:5d} output tokens ({stop})", flush=True)
    return result

def bootstrap_interval(groups, seed=17, draws=5000):
    """Resample task clusters; repeats within a task are not independent tasks."""
    if len(groups) < 2:
        return None
    rng = random.Random(seed)
    vals = list(groups.values())
    samples = sorted(statistics.mean(rng.choice(vals) for _ in vals) for _ in range(draws))
    return [samples[int(draws*.025)], samples[int(draws*.975)]]

def summarize(results, config):
    langs = {}
    for language in config["languages"]:
        rows = [r for r in results if r["language"] == language]
        correct = sum(r["success"] for r in rows)
        langs[language] = {
            "runs": len(rows), "successes": correct, "success_rate": correct / len(rows),
            "first_submission_successes": sum(r["first_submission_passed"] for r in rows),
            "mean_par2_seconds": statistics.mean(r["par2_seconds"] for r in rows),
            "output_tokens_per_success": sum(r["tokens"]["output"] for r in rows) / correct if correct else None,
            "mean_output_tokens": statistics.mean(r["tokens"]["output"] for r in rows),
            "mean_submissions": statistics.mean(r["submissions"] for r in rows),
            "infrastructure_errors": sum(r["infrastructure_error"] for r in rows),
            "median_seconds": (statistics.median(r["elapsed_seconds"] for r in rows)
                               if all(r["elapsed_seconds"] is not None for r in rows) else None),
            "missing_timing_runs": sum(r["elapsed_seconds"] is None for r in rows),
        }
    by_pair = defaultdict(dict)
    for r in results:
        by_pair[(r["task"], r["repeat"])][r["language"]] = r
    by_task = defaultdict(list)
    for (task, _), pair in by_pair.items():
        if "c" in pair and "go" in pair:
            by_task[task].append(int(pair["go"]["success"]) - int(pair["c"]["success"]))
    differences = {task: statistics.mean(diffs) for task, diffs in by_task.items()}
    summary = {"languages": langs, "go_minus_c_success_by_task": differences,
            "go_minus_c_success_task_bootstrap_95": bootstrap_interval(differences),
            "stability": "exploratory_only",
            "note": "A small task suite cannot establish a general language advantage. "
                    "Repeat a preregistered larger suite in a second independent batch."}
    if config.get("protocol_version") == 2:
        summary.pop("go_minus_c_success_task_bootstrap_95")
        summary["note"] = "Single-batch descriptive results. Use analysis.py on frozen A/B confirmation batches for a decision."
    return summary

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=["plan", "doctor", "run", "report"])
    parser.add_argument("--config", default=str(ROOT / "config.json"))
    parser.add_argument("--repeats", type=int)
    parser.add_argument("--tasks", nargs="+", choices=list(SPECS))
    parser.add_argument("--batch", help="Existing directory for report, or clean checkpoint to resume")
    parser.add_argument("--chunk-seconds", type=int, default=0,
                        help="Stop at a C/Go pair boundary after this duration (0 = uninterrupted)")
    args = parser.parse_args()
    if args.chunk_seconds < 0:
        parser.error("--chunk-seconds must be nonnegative")
    config = json.loads(Path(args.config).read_text())
    if args.repeats is not None:
        if args.repeats < 1: parser.error("--repeats must be positive")
        config["repeats"] = args.repeats
    if args.tasks: config["tasks"] = args.tasks
    if args.command != "report":
        validate_config(config)
    if config.get("purpose") == "confirmation" and (args.tasks or args.repeats is not None):
        parser.error("Confirmation profiles are fixed; create a new preregistered study to change them.")
    if (args.command == "run" and config.get("recovery_amendment")
            and config.get("replication") == "A" and not args.batch):
        parser.error("Amended A requires the prepared recovery checkpoint via --batch; never regenerate its prefix.")
    if args.command == "plan":
        jobs = schedule(config)
        print(json.dumps({"config": config, "trials": len(jobs), "pairs": len(jobs)//2,
                          "maximum_agent_minutes": len(jobs)*config["max_seconds"]/60,
                          "note": "Excludes warmup and post-trial judging; no inference has been run.",
                          "source_sha256": source_hashes(), "schedule": jobs}, indent=2))
        return
    if args.command == "doctor":
        snapshot = environment(config)
        print(json.dumps({k:v for k,v in snapshot.items() if k not in ("model", "model_tags")}, indent=2))
        print("Model:", config["model"], snapshot["model"].get("details"))
        return
    if args.command == "report":
        if not args.batch: parser.error("--batch is required for report")
        batch = Path(args.batch)
        config = json.loads((batch / "config.json").read_text())
        results = [json.loads(p.read_text()) for p in sorted(batch.glob("*/result.json"))]
    else:
        snapshot = environment(config)
        jobs = schedule(config)
        if args.batch:
            batch = Path(args.batch).resolve()
            results = resume_rows(batch, config, snapshot, jobs)
            snapshot = json.loads((batch / "environment.json").read_text())
        else:
            batch = ROOT / "runs" / datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
            batch.mkdir(parents=True)
            dump(batch / "config.json", config)
            dump(batch / "environment.json", snapshot)
            dump(batch / "schedule.json", jobs)
            results = []
        dump(batch / "status.json", {"state": "running", "completed_trials": len(results)})
        print("Batch:", batch, flush=True)
        chunk_started = time.monotonic()
        checkpoint_due = False
        try:
            print("Warming model (excluded from trial timing)...", flush=True)
            api(config["ollama_url"], "/api/chat", {
                "model": config["model"], "messages": [{"role": "user", "content": "Reply OK."}],
                "think": False, "stream": False, "keep_alive": "30m",
                "options": {"num_predict": 8, "num_ctx": config["context"]}}, timeout=240)
            dump(batch / "loaded_models.json", api(config["ollama_url"], "/api/ps"))
            for i in range(len(results), len(jobs)):
                job = jobs[i]
                if source_hashes() != snapshot["source_sha256"]:
                    raise RuntimeError("Harness changed during the batch; refusing to mix protocols.")
                results.append(run_one(batch, config, job, i))
                if config.get("purpose") == "confirmation" and results[-1]["infrastructure_error"]:
                    raise RuntimeError("Confirmation invalidated by an infrastructure error; retained artifacts, stopped remaining trials.")
                if source_hashes() != snapshot["source_sha256"]:
                    raise RuntimeError("Harness changed during a trial; this batch is invalid.")
                if (args.chunk_seconds and (i + 1) % 2 == 0 and i + 1 < len(jobs)
                        and time.monotonic() - chunk_started >= args.chunk_seconds):
                    checkpoint_due = True
                    break
            final_snapshot = environment(config)
            check_environment(snapshot, final_snapshot)
            if checkpoint_due:
                dump(batch / "summary.json", summarize(results, config))
                seal(batch, len(results), snapshot)
                print(f"Checkpoint: {len(results)}/{len(jobs)} trials; resume with --batch {batch}", flush=True)
                return
            else:
                dump(batch / "status.json", {"state": "complete", "source_sha256": source_hashes(),
                                             "model_digest": snapshot["model_digest"]})
        except BaseException as error:
            dump(batch / "status.json", {"state": "interrupted_or_invalid", "reason": str(error)})
            raise
    summary = summarize(results, config)
    dump(batch / "summary.json", summary)
    print(json.dumps(summary, indent=2))

if __name__ == "__main__":
    main()
