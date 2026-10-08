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

from judge import evaluate
from tasks import SPECS, cases

ROOT = Path(__file__).resolve().parent
SYSTEM = """You are solving a programming benchmark. Use only the requested language
and its standard library. Your only tool is submit_source: send the entire source
file to compile and test. Use its feedback to repair failures. When public tests
pass, stop. Do not explain your solution, use Markdown, or call unavailable tools.
Implement the full specification, not just examples. No filesystem access, network,
subprocesses, or environment inspection in the submitted program: stdin/stdout only."""

def dump(path, obj):
    Path(path).write_text(json.dumps(obj, indent=2) + "\n")

def api(base, path, payload=None, timeout=120):
    data = None if payload is None else json.dumps(payload).encode()
    request = urllib.request.Request(base + path, data=data, headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(request, timeout=timeout) as response:
        return json.load(response)

def version(command):
    return subprocess.check_output(command, text=True, stderr=subprocess.STDOUT).splitlines()[0]

def environment(config):
    return {
        "platform": platform.platform(), "machine": platform.machine(),
        "python": platform.python_version(), "pi": version(["pi", "--version"]),
        "clang": version(["clang", "--version"]), "go": version(["go", "version"]),
        "ollama": api(config["ollama_url"], "/api/version"),
        "model": api(config["ollama_url"], "/api/show", {"model": config["model"]}),
        "model_tags": api(config["ollama_url"], "/api/tags"),
        "git_commit": subprocess.run(["git", "rev-parse", "--verify", "HEAD"], cwd=ROOT,
                                     capture_output=True, text=True).stdout.strip() or None,
        "source_sha256": {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest()
                          for p in [ROOT / f for f in
                          ["bench.py", "judge.py", "tasks.py", "pi/benchmark.ts", "config.json", "Modelfile"]]},
    }

def schedule(config):
    rng = random.Random(config["schedule_seed"])
    jobs = []
    for repeat in range(config["repeats"]):
        tasks = list(config["tasks"])
        rng.shuffle(tasks)
        for task in tasks:
            languages = list(config["languages"])
            rng.shuffle(languages)
            for language in languages:
                jobs.append({"task": task, "language": language, "repeat": repeat,
                             "sampling_seed": config["schedule_seed"] + repeat})
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
            missing_usage |= "usage" not in message
            for key in usage:
                usage[key] += message.get("usage", {}).get(key, 0) or 0
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
                    continue
                events.append(event)
                if event["type"] == "turn_end":
                    turns += 1
                    if (turns >= config["max_turns"]
                            and event.get("message", {}).get("stopReason") == "toolUse"):
                        stop = "turn_budget"
                        break
        finally:
            if proc.poll() is None:
                try:
                    os.killpg(proc.pid, signal.SIGTERM)
                    proc.wait(timeout=3)
                except (ProcessLookupError, subprocess.TimeoutExpired):
                    try:
                        os.killpg(proc.pid, signal.SIGKILL)
                    except ProcessLookupError:
                        pass
            proc.wait()
            reader.join(timeout=1)
            proc.stdout.close()
    elapsed = time.monotonic() - started
    metrics = parse_events(events)
    attempts_file = work / "attempts.jsonl"
    attempts = [json.loads(line) for line in attempts_file.read_text().splitlines()] if attempts_file.exists() else []
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
                      or stop == "invalid_event_stream"
                      or any("Judge infrastructure error" in e for e in metrics["tool_errors"]))
    valid_finish = stop == "completed" and proc.returncode == 0 and not infrastructure
    success = valid_finish and hidden["passed"]
    result = {**job, **metrics, "stop": stop, "returncode": proc.returncode,
              "infrastructure_error": infrastructure, "elapsed_seconds": elapsed,
              "submissions": len(list(revisions.glob("*"))) if revisions.exists() else 0,
              "compile_failures": sum(a["kind"] == "compile_error" for a in attempts),
              "success": success, "first_submission_passed": first["passed"],
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
            "median_seconds": statistics.median(r["elapsed_seconds"] for r in rows),
        }
    by_pair = defaultdict(dict)
    for r in results:
        by_pair[(r["task"], r["repeat"])][r["language"]] = r
    by_task = defaultdict(list)
    for (task, _), pair in by_pair.items():
        if "c" in pair and "go" in pair:
            by_task[task].append(int(pair["go"]["success"]) - int(pair["c"]["success"]))
    differences = {task: statistics.mean(diffs) for task, diffs in by_task.items()}
    return {"languages": langs, "go_minus_c_success_by_task": differences,
            "go_minus_c_success_task_bootstrap_95": bootstrap_interval(differences),
            "stability": "exploratory_only",
            "note": "A small task suite cannot establish a general language advantage. "
                    "Repeat a preregistered larger suite in a second independent batch."}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=["doctor", "run", "report"])
    parser.add_argument("--config", default=str(ROOT / "config.json"))
    parser.add_argument("--repeats", type=int)
    parser.add_argument("--tasks", nargs="+", choices=list(SPECS))
    parser.add_argument("--batch", help="Existing run directory for report")
    args = parser.parse_args()
    config = json.loads(Path(args.config).read_text())
    if args.repeats is not None:
        if args.repeats < 1: parser.error("--repeats must be positive")
        config["repeats"] = args.repeats
    if args.tasks: config["tasks"] = args.tasks
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
        batch = ROOT / "runs" / datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S%fZ")
        batch.mkdir(parents=True)
        dump(batch / "config.json", config)
        dump(batch / "environment.json", snapshot)
        jobs = schedule(config)
        dump(batch / "schedule.json", jobs)
        print("Batch:", batch, flush=True)
        print("Warming model (excluded from trial timing)...", flush=True)
        api(config["ollama_url"], "/api/chat", {
            "model": config["model"], "messages": [{"role": "user", "content": "Reply OK."}],
            "think": False, "stream": False, "keep_alive": "30m",
            "options": {"num_predict": 8, "num_ctx": config["context"]}}, timeout=240)
        dump(batch / "loaded_models.json", api(config["ollama_url"], "/api/ps"))
        results = [run_one(batch, config, job, i) for i, job in enumerate(jobs)]
    summary = summarize(results, config)
    dump(batch / "summary.json", summary)
    print(json.dumps(summary, indent=2))

if __name__ == "__main__":
    main()
