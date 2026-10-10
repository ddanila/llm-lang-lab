#!/usr/bin/env python3
"""Descriptive post-study diagnostics; never changes the frozen decision.

Run from any directory. No inference or candidate execution. Public inputs only
unless --local-diagnostics is supplied; that exports aggregate counts only.
"""
import argparse
from collections import Counter
import hashlib
import json
import math
from pathlib import Path
import random
import statistics as st

ROOT = Path(__file__).resolve().parent
BATCHES = {"A": "20261009T113047097658Z", "B": "20261009T134522238478Z"}


def paired(rows):
    groups = {}
    for r in rows:
        key = (r['task'], r['repeat'])
        p = groups.setdefault(key, {})
        assert r['language'] not in p
        p[r['language']] = r
    assert len(groups) == 200 and all(set(p) == {'c', 'go'} for p in groups.values())
    return groups


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--local-diagnostics', action='store_true')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    result = {'scope': 'Exploratory diagnostics, separate A/B; no new winner claim',
              'input_sha256': {}, 'batches': {}}
    for label, batch in BATCHES.items():
        path = ROOT / 'reports' / batch / 'results.json'
        result['input_sha256'][str(path.relative_to(ROOT))] = hashlib.sha256(path.read_bytes()).hexdigest()
        rows = json.loads(path.read_text())['runs']
        assert len(rows) == 400
        pairs = paired(rows)
        tasks = sorted({r['task'] for r in rows})
        assert len(tasks) == 10
        diffs = {t: [int(p['go']['success']) - int(p['c']['success'])
                     for (task, _), p in sorted(pairs.items()) if task == t] for t in tasks}
        assert all(len(d) == 20 for d in diffs.values())
        by_language = {}
        for lang in ['c', 'go']:
            rs = [r for r in rows if r['language'] == lang]
            successes = sum(r['success'] for r in rs)
            by_language[lang] = {
                'trials': len(rs), 'successes': successes,
                'first_successes': sum(r['first_submission_passed'] for r in rs),
                'repair_successes': sum(r['success'] and not r['first_submission_passed'] for r in rs),
                'first_success_final_failure': sum(r['first_submission_passed'] and not r['success'] for r in rs),
                'trials_with_compile_failure': sum(r['compile_failures'] > 0 for r in rs),
                'public_passes': sum(r['stop'] == 'public_pass' for r in rs),
                'public_pass_hidden_fail': sum(r['stop'] == 'public_pass' and not r['success'] for r in rs),
                'output_tokens': sum(r['tokens']['output'] for r in rs),
                'mean_submissions': st.mean(r['submissions'] for r in rs),
                'missing_elapsed': sum(r['elapsed_seconds'] is None for r in rs),
            }
        task_rows = {t: {lang: sum(r['success'] for r in rows if r['task'] == t and r['language'] == lang)
                         for lang in ['c', 'go']} for t in tasks}
        # Fixed-suite, equal allocation normal approximation, for PLANNING only.
        # Var(mean difference) = mean(within-task Var(D)) / total pairs.
        variance = st.mean(st.variance(d) for d in diffs.values())
        elapsed = [r['elapsed_seconds'] for r in rows if r['elapsed_seconds'] is not None]
        pair_seconds = 2 * st.mean(elapsed)
        precision = []
        for halfwidth in [.10, .05, .03]:
            n = math.ceil((1.96 ** 2 * variance / halfwidth ** 2) / 10) * 10
            precision.append({'halfwidth_pp': halfwidth * 100, 'pairs_approx': n,
                              'trials_approx': 2*n, 'agent_hours_approx': n*pair_seconds/3600})
        rng = random.Random(20261010)
        screening = []
        for k in [1, 2, 4, 10, 20]:
            # Subsets without replacement from each observed task, not new draws
            # from the population. Spread collapses to zero at the full dataset.
            samples = sorted(st.mean(x for d in diffs.values() for x in rng.sample(d, k))
                             for _ in range(5000))
            screening.append({'repeats_per_task': k, 'trials': 20*k,
                              'agent_hours_approx': 10*k*pair_seconds/3600,
                              'subset_gap_95_range_pp': [100*samples[125], 100*samples[4875]],
                              'fraction_go_leads': sum(x > 0 for x in samples)/len(samples),
                              'fraction_tied': sum(x == 0 for x in samples)/len(samples)})
        result['batches'][label] = {
            'language': by_language, 'task_successes_out_of_20': task_rows,
            'within_task_pair_variance': variance, 'precision_planning_not_power': precision,
            'subset_screening_not_confidence_intervals': screening,
            'leave_one_task_out_gap_pp': {t: 100*st.mean(x for task, d in diffs.items() if task != t for x in d)
                                        for t in tasks}}
        if args.local_diagnostics:
            local = {'final_failure_kind': {}, 'assistant_stop_reason': {},
                     'compiler_substring_counts_overlapping': {}}
            rawpaths = sorted((ROOT/'runs'/batch).glob('*/result.json'))
            assert len(rawpaths) == 400
            raw = [json.loads(p.read_text()) for p in rawpaths]
            public_map = {(r['task'], r['repeat'], r['language']): r for r in rows}
            for r in raw:
                pub = public_map[(r['task'], r['repeat'], r['language'])]
                assert all(r[k] == v for k, v in pub.items())
            for lang in ['c', 'go']:
                local['final_failure_kind'][lang] = dict(Counter(r['hidden']['kind'] for r in raw
                                                               if r['language'] == lang and not r['success']))
                stops, compiler = Counter(), Counter()
                for p, r in zip(rawpaths, raw):
                    if r['language'] != lang:
                        continue
                    for line in (p.parent/'events.jsonl').open():
                        e = json.loads(line)
                        if e['type'] == 'message_end' and e.get('message', {}).get('role') == 'assistant':
                            stops[e['message'].get('stopReason')] += 1
                    attempt_path = p.parent/'work'/'attempts.jsonl'
                    if attempt_path.exists():
                        for line in attempt_path.open():
                            a = json.loads(line)
                            if a['kind'] == 'compile_error':
                                stderr = a.get('build', {}).get('stderr', '')
                                for pattern in ['not used', 'undefined', 'syntax error', 'expected', 'undeclared']:
                                    compiler[pattern] += int(pattern in stderr)
                local['assistant_stop_reason'][lang] = dict(stops)
                local['compiler_substring_counts_overlapping'][lang] = dict(compiler)
            result['batches'][label]['local_diagnostics'] = local
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2, sort_keys=True) + '\n')


if __name__ == '__main__':
    main()
