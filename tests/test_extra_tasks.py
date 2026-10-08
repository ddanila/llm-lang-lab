import csv
import io
import random
import unittest

from tasks import cases, oracle

class ExtraTasks(unittest.TestCase):
    def test_known_answers(self):
        examples = [
            ("lower_bounds", "5 4\n1 2 2 4 9\n0 2 3 10\n", "0 1 3 5"),
            ("grid_distance", "2 3 0 0 1 2\n...\n.#.\n", "3"),
            ("grid_distance", "1 1 0 0 0 0\n#\n", "-1"),
            ("rational_sum", "3\n1 2\n-1 3\n1 6\n", "1 3"),
            ("rational_sum", "2\n-2 3\n2 3\n", "0 1"),
            ("edit_distance", "kitten\nsitting\n", "3"),
            ("edit_distance", "\n\n", "0"),
            ("transaction_ledger", "10\nBEGIN\nADD 1\nBEGIN\nADD 2\nCOMMIT\nPRINT\nROLLBACK\nPRINT\nROLLBACK\nPRINT\n", "3 0 ERROR 0"),
            ("dependency_order", "4 1\n3 0\n", "1 2 3 0"),
            ("dependency_order", "2 2\n0 1\n1 0\n", "ERROR"),
            ("dependency_order", "2 2\n0 1\n0 1\n", "0 1"),
            ("csv_fields", '"a""b","x,y",\r\n', "3 3 3 0"),
        ]
        for task, source, answer in examples:
            with self.subTest(task=task, source=source):
                self.assertEqual(oracle(task, source).split(), answer.split())

    def test_binary_search_against_linear_count(self):
        for case in cases("lower_bounds", True):
            nums = list(map(int, case["input"].split()))
            n,q = nums[:2]
            expected = [sum(a < x for a in nums[2:2+n]) for x in nums[2+n:]]
            self.assertEqual(list(map(int, case["expected"].split())), expected)

    def test_open_grid_manhattan_distance(self):
        for h in range(1,6):
            for w in range(1,6):
                source = f"{h} {w} 0 0 {h-1} {w-1}\n"+("."+("."*(w-1))+"\n")*h
                self.assertEqual(int(oracle("grid_distance",source)), h+w-2)

    def test_csv_round_trip_with_known_field_lengths(self):
        rng = random.Random(73)
        for _ in range(40):
            fields = ["".join(rng.choice('abc ,"') for _ in range(rng.randrange(10)))
                      for _ in range(rng.randrange(1,10))]
            output = io.StringIO()
            csv.writer(output).writerow(fields)
            self.assertEqual(list(map(int,oracle("csv_fields",output.getvalue()).split())),
                             [len(fields)]+list(map(len,fields)))

    def test_topological_output_obeys_edges_and_is_complete(self):
        for case in cases("dependency_order", True):
            if case["expected"].strip()=="ERROR":
                continue
            data = list(map(int,case["input"].split()))
            ordering = list(map(int,case["expected"].split()))
            self.assertEqual(sorted(ordering),list(range(data[0])))
            positions = {node:i for i,node in enumerate(ordering)}
            for u,v in zip(data[2::2],data[3::2]):
                self.assertLess(positions[u],positions[v])

    def test_edit_distance_symmetry_and_bounds(self):
        for case in cases("edit_distance", True):
            a,b = case["input"].splitlines()
            distance = int(case["expected"])
            self.assertEqual(distance, int(oracle("edit_distance", b+"\n"+a+"\n")))
            self.assertLessEqual(distance,max(len(a),len(b)))
            self.assertGreaterEqual(distance,abs(len(a)-len(b)))

if __name__ == "__main__":
    unittest.main()
