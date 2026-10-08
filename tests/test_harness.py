import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from bench import parse_events, schedule, summarize, bootstrap_interval
from judge import evaluate, execute
from tasks import oracle, cases, SPECS

class Tasks(unittest.TestCase):
    def test_boundaries(self):
        self.assertEqual(oracle("merge_intervals", "3\n1 2\n2 3\n4 5"), "2\n1 3\n4 5\n")
        self.assertEqual(oracle("merge_intervals", "0"), "0\n")
        self.assertEqual(oracle("word_counts", "A\x00a b_B42"), "a 2\nb 2\n")
        for text in ("", "2x", "1 2", "1 +", "++2", "2 3 /"):
            self.assertEqual(oracle("rpn", text), "ERROR\n")
        self.assertEqual(oracle("rpn", "-3 +2 *"), "-6\n")
        self.assertEqual(oracle("rpn", "3 10 -"), "-7\n")

    def test_cases_are_reproducible_and_held_out(self):
        for task in SPECS:
            self.assertEqual(cases(task, True), cases(task, True))
            self.assertGreater(len(cases(task, True)), 30)
            public = {c["input"] for c in cases(task)}
            self.assertTrue(any(c["input"] not in public for c in cases(task, True)))

class Metrics(unittest.TestCase):
    def test_only_authoritative_messages_count(self):
        message = {"role": "assistant", "usage": {"input": 10, "output": 4}, "stopReason": "stop"}
        events = [{"type": "message_update", "usage": message["usage"]},
                  {"type": "message_end", "message": message},
                  {"type": "turn_end", "message": message},
                  {"type": "agent_end", "messages": [message]}]
        metrics = parse_events(events)
        self.assertEqual(metrics["tokens"]["output"], 4)
        self.assertEqual(metrics["assistant_turns"], 1)

    def test_schedule_has_every_pair_once(self):
        cfg = {"schedule_seed": 42, "repeats": 3, "tasks": list(SPECS), "languages": ["c", "go"]}
        jobs = schedule(cfg)
        self.assertEqual(len(jobs), 18)
        self.assertEqual(jobs, schedule(cfg))
        self.assertEqual(len({(j["task"], j["repeat"], j["language"]) for j in jobs}), 18)
        for a,b in zip(jobs[::2], jobs[1::2]):
            self.assertEqual((a["task"],a["repeat"],a["sampling_seed"]),
                             (b["task"],b["repeat"],b["sampling_seed"]))
            self.assertNotEqual(a["language"], b["language"])

    def test_failure_cost_is_not_dropped(self):
        base = {"language": "c", "task": "rpn", "tokens": {"output": 100},
                "first_submission_passed": False, "infrastructure_error": False,
                "elapsed_seconds": 5, "submissions": 1}
        rows = [{**base, "repeat": 0, "success": True, "par2_seconds": 5},
                {**base, "repeat": 1, "success": False, "par2_seconds": 480}]
        stats = summarize(rows, {"languages": ["c"]})["languages"]["c"]
        self.assertEqual(stats["success_rate"], .5)
        self.assertEqual(stats["output_tokens_per_success"], 200)
        self.assertEqual(stats["mean_par2_seconds"], 242.5)
        self.assertIsNone(bootstrap_interval({"one": 1}))

class Judge(unittest.TestCase):
    def test_missing_and_invalid_source(self):
        with tempfile.TemporaryDirectory() as d:
            self.assertEqual(evaluate(d, "c", "rpn")["kind"], "missing_source")
            Path(d, "main.c").write_text("this is not C")
            self.assertEqual(evaluate(d, "c", "rpn")["kind"], "compile_error")

    def test_public_examples_do_not_imply_hidden_success(self):
        # A deliberately overfit submission passes public tests but fails held-out tests.
        source = '#include <stdio.h>\nint main(void){int n;scanf("%d",&n);if(n==3)puts("2\\n1 4\\n7 9");else if(n==0)puts("0");else puts("2\\n1 2\\n3 4");}'
        with tempfile.TemporaryDirectory() as d:
            Path(d, "main.c").write_text(source)
            self.assertTrue(evaluate(d, "c", "merge_intervals")["passed"])
            self.assertFalse(evaluate(d, "c", "merge_intervals", True)["passed"])

    def test_both_compilers_and_runtime(self):
        sources = {
            "c": '#include <stdio.h>\nint main(void){long long x; if(scanf("%lld",&x)==1)printf("%lld\\n",x);}',
            "go": 'package main\nimport("fmt";"os";"bufio")\nfunc main(){var x int64;fmt.Fscan(bufio.NewReader(os.Stdin), &x);fmt.Println(x)}',
        }
        for lang, source in sources.items():
            with self.subTest(language=lang), tempfile.TemporaryDirectory() as d:
                p = Path(d)
                (p / ("main.c" if lang == "c" else "main.go")).write_text(source)
                result = evaluate(p, lang, "rpn")
                self.assertEqual(result["kind"], "tests")
                run = execute([str(p / "program")], p, "-9223372036854775808", restricted=True)
                self.assertEqual(run["returncode"], 0, run)
                self.assertEqual(run["stdout"].strip(), "-9223372036854775808")

    def test_infinite_program_times_out(self):
        with tempfile.TemporaryDirectory() as d:
            result = execute([sys.executable, "-c", "while True: pass"], Path(d),
                             timeout=.1)
            self.assertTrue(result["timeout"])

if __name__ == "__main__":
    unittest.main()
