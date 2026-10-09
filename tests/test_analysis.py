import copy
import json
import unittest

from analysis import ROOT, analyze, compare, posterior, pair_rows, effort_interval
from bench import source_hashes, schedule, validate_config

STUDY = json.loads((ROOT/"experiments/study.json").read_text())
# Pure statistical fixtures test the unamended framework; recovery has separate tests.
STUDY["run_settings"].pop("recovery_amendment", None)
POLICY = STUDY["decision_policy"]

def fixture(phase="A", c_success=True, go_success=True, c_tokens=100, go_tokens=100):
    config = json.loads((ROOT/f"experiments/confirm-{phase.lower()}.json").read_text())
    config.pop("recovery_amendment", None)
    rows = []
    for job in schedule(config):
        is_c = job["language"] == "c"
        rows.append({**job, "success": c_success if is_c else go_success,
                     "infrastructure_error": False, "usage_complete": True,
                     "tokens": {"output": c_tokens if is_c else go_tokens}})
    return {"name":"synthetic-"+phase, "config":config, "rows":rows,
            "model_digest":config["model_digest"],
            "status":{"state":"complete", "source_sha256":source_hashes(),"model_digest":config["model_digest"]},
            "environment":{"source_sha256":source_hashes(),
                           **dict.fromkeys(["pi","clang","go","python","ollama","platform","machine","hardware"],"synthetic")}}

class Statistics(unittest.TestCase):
    def test_all_ties_do_not_collapse_accuracy_uncertainty(self):
        groups = pair_rows(fixture()["rows"])
        low,high = posterior(groups,.5,1000,703)["go_minus_c_success_95_credible"]
        self.assertLess(low, 0)
        self.assertGreater(high, 0)
        self.assertGreater(high-low,.01)

    def test_opposite_decisive_effects(self):
        for c,g,expected in [(False,True,"go_accuracy_advantage"), (True,False,"c_accuracy_advantage")]:
            self.assertEqual(analyze(fixture(c_success=c,go_success=g)["rows"], POLICY,500)["decision"],expected)

    def test_effort_requires_equivalent_accuracy(self):
        result = analyze(fixture(c_tokens=200,go_tokens=100)["rows"],POLICY,500)
        self.assertEqual(result["decision"],"go_effort_advantage")
        self.assertEqual(result["go_over_c_tokens_per_success_95_bootstrap"],[.5,.5])

    def test_failures_stay_in_token_cost(self):
        pairs = pair_rows(fixture()["rows"])
        task = next(iter(pairs))
        pairs[task][0]["go"]["success"] = False
        interval = effort_interval(pairs,500,704)
        self.assertGreaterEqual(interval[0],1)
        self.assertGreater(interval[1],1)

    def test_incomplete_token_usage_disables_effort_decision(self):
        data=fixture()
        data["rows"][0]["usage_complete"]=False
        self.assertIsNone(effort_interval(pair_rows(data["rows"]),100,704))
        self.assertEqual(analyze(data["rows"],POLICY,500)["decision"],"accuracy_equivalent_effort_inconclusive")

    def test_tie_can_replicate(self):
        result=compare(fixture("A"),fixture("B"),STUDY,500)
        self.assertEqual(result["status"],"replicated_on_frozen_suite")
        self.assertEqual(result["decision"],"practical_tie")

    def test_opposite_batch_results_are_inconclusive(self):
        result=compare(fixture("A",False,True),fixture("B",True,False),STUDY,500)
        self.assertEqual(result["status"],"inconclusive")

class Validation(unittest.TestCase):
    def test_rejects_incomplete_duplicate_errors_and_pilots(self):
        for kind in ("incomplete","duplicate","error","pilot","seed","source","weights"):
            with self.subTest(kind=kind):
                a,b=fixture("A"),fixture("B")
                if kind=="incomplete": a["rows"].pop()
                if kind=="duplicate": a["rows"][-1]=copy.deepcopy(a["rows"][0])
                if kind=="error": a["rows"][0]["infrastructure_error"]=True
                if kind=="pilot": a["config"]["purpose"]="calibration"
                if kind=="seed": a["rows"][0]["sampling_seed"]+=1
                if kind=="source": a["environment"]["source_sha256"]["bench.py"]="changed"
                if kind=="weights": a["model_digest"]="changed"
                with self.assertRaises(ValueError):
                    compare(a,b,STUDY,100)

    def test_same_batch_cannot_be_its_own_replication(self):
        with self.assertRaises(ValueError):
            compare(fixture("A"),fixture("A"),STUDY,100)

    def test_order_is_balanced_and_seeds_are_unique_per_pair(self):
        config=fixture()["config"]
        jobs=schedule(config)
        first={task:[] for task in config["tasks"]}
        for a,b in zip(jobs[::2],jobs[1::2]):
            first[a["task"]].append(a["language"])
            self.assertEqual(a["sampling_seed"],b["sampling_seed"])
        for order in first.values():
            self.assertEqual(order.count("c"),order.count("go"))
        self.assertEqual(len({j["sampling_seed"] for j in jobs}),len(jobs)//2)

    def test_profiles_validate_without_model_access(self):
        for name in ("pilot","confirm-a","confirm-b"):
            config=json.loads((ROOT/f"experiments/{name}.json").read_text())
            validate_config(config)
        bad=copy.deepcopy(config)
        bad["ollama_url"]="https://example.com"
        with self.assertRaises(ValueError): validate_config(bad)

if __name__ == "__main__":
    unittest.main()
