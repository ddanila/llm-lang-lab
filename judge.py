"""Trusted compiler and judge; model sees public feedback only."""
import json
import os
from pathlib import Path
import resource
import signal
import subprocess
import sys
import tempfile
from tasks import cases

def limits():
    resource.setrlimit(resource.RLIMIT_CPU, (3, 3))
    resource.setrlimit(resource.RLIMIT_FSIZE, (1024*1024, 1024*1024))
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))

def execute(command, cwd, data="", timeout=30, restricted=False):
    env = {"PATH": os.environ.get("PATH", "/usr/bin:/bin"), "HOME": str(cwd),
           "TMPDIR": tempfile.gettempdir(), "LC_ALL": "C", "GOTOOLCHAIN": "local",
           "GOPROXY": "off", "GOSUMDB": "off", "CGO_ENABLED": "0",
           "GOCACHE": str(Path(tempfile.gettempdir()) / "llm-lang-lab-go-cache")}
    if restricted and sys.platform == "darwin":
        # Local guardrail, not a hostile-code security boundary.
        profile = ('(version 1)(allow default)(deny network*)'
                   '(deny file-read* (subpath "/Users"))(deny file-write*)'
                   f'(allow file-read* file-write* (subpath {json.dumps(str(cwd))}))'
                   '(allow file-write* (literal "/dev/null"))')
        command = ["/usr/bin/sandbox-exec", "-p", profile] + command
    with tempfile.TemporaryFile() as out, tempfile.TemporaryFile() as err:
        proc = subprocess.Popen(command, cwd=cwd, env=env, stdin=subprocess.PIPE,
                                stdout=out, stderr=err, start_new_session=True,
                                preexec_fn=limits if restricted else None)
        timed_out = False
        try:
            proc.communicate(data.encode(), timeout=timeout)
        except subprocess.TimeoutExpired:
            timed_out = True
        finally:
            try:
                os.killpg(proc.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            proc.wait()
        out.seek(0); err.seek(0)
        return {"returncode": proc.returncode, "timeout": timed_out,
                "stdout": out.read(65536).decode(errors="replace"),
                "stderr": err.read(8192).decode(errors="replace")}

def evaluate(work, language, task, hidden=False):
    work = Path(work).resolve()
    source = work / ("main.c" if language == "c" else "main.go")
    if not source.exists():
        return {"passed": False, "kind": "missing_source", "passed_cases": 0}
    binary = work / "program"
    binary.unlink(missing_ok=True)
    command = (["clang", "-std=c17", "-O0", "-Wall", "-Wextra", str(source), "-o", str(binary)]
               if language == "c" else ["go", "build", "-o", str(binary), str(source)])
    build = execute(command, work, timeout=60)
    if build["returncode"] or build["timeout"]:
        return {"passed": False, "kind": "compile_error", "passed_cases": 0, "build": build}
    test_cases = cases(task, hidden)
    count = 0
    failures = []
    for case in test_cases:
        # CPU work is independently capped at 3s by limits(). Leave enough wall
        # time for cold executable/Seatbelt startup and laptop scheduling delays.
        result = execute([str(binary)], work, case["input"], timeout=10, restricted=True)
        ok = (result["returncode"] == 0 and not result["timeout"]
              and result["stdout"].split() == case["expected"].split())
        count += int(ok)
        if not ok:
            failures.append({"input": case["input"][:1200], "expected": case["expected"][:1200],
                             **result})
            if len(failures) >= 3:
                break
    return {"passed": count == len(test_cases), "kind": "tests",
            "passed_cases": count, "total_cases": len(test_cases),
            "stopped_early": len(failures) == 3,
            "failures": failures, "compiler_stderr": build["stderr"]}

if __name__ == "__main__":
    work, language, task, visibility = sys.argv[1:]
    print(json.dumps(evaluate(work, language, task, visibility == "hidden")))
