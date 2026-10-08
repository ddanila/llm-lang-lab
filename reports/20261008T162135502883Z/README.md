# Local C/Go experiment

Batch: 20261008T162135502883Z. Model: llm-lang-lab-qwen35-9b.

Tasks: merge_intervals, word_counts, rpn, lower_bounds, grid_distance, rational_sum, edit_distance, transaction_ledger, dependency_order, csv_fields. Repeats per language/task: 1.

This is exploratory evidence on a small fixed task suite, not a language ranking.
Only this batch is included. Every generated source revision is included under sources/.
Raw event traces, prompts, and full diagnostics remain in the local batch directory.

| Language | Passed | First source passed | Mean submissions | Output tokens / success | Median seconds |
| --- | --- | --- | --- | --- | --- |
| c | 4/10 | 4/10 | 2.50 | 3835.5 | 73.9 |
| go | 6/10 | 3/10 | 2.70 | 2393.5 | 67.5 |

See results.json for all settings, per-run metrics, model digest, and source hashes.
First-source scoring is independent of whether the agent later finishes successfully.
The controller stopped at the first public pass or submission limit.
A public pass is not a held-out success. Protocol v1 results cannot be pooled with this batch.

## Audit and difficulty decision

All twenty trials passed schedule, usage-event, source-revision, and stop-rule
checks. No agent, compiler, or test wall timeout occurred. Token accounting is
complete in every trial. Model and benchmark source fingerprints were unchanged.
See audit.json for the checks and local raw-trace hashes.

| Workload | C held-out pass | Go held-out pass |
| --- | --- | --- |
| merge_intervals | no | yes |
| word_counts | no | yes |
| rpn | no | yes |
| lower_bounds | yes | yes |
| grid_distance | yes | no |
| rational_sum | no | no |
| edit_distance | yes | yes |
| transaction_ledger | yes | yes |
| dependency_order | no | no |
| csv_fields | no | no |

There is no overall floor or ceiling: half the generated programs succeeded.
Some workloads failed in both languages, while grid distance favored C and three
other workloads favored Go on this single pair. One pair per workload cannot
estimate a stable workload-specific success rate. Keep the frozen suite unchanged.
The observed Go advantage is exploratory and does not establish a language ranking.
The registered effort decision also requires at least 80% success in each language;
these calibration rates would not qualify.

## Runtime estimate

The batch took 1,522 seconds (25.4 minutes), including warmup and post-trial judging.
Agent time totaled 1,495 seconds: mean 74.7 seconds, range 14.9–145.7 seconds.
Multiplying the observed end-to-end average by 400 gives **8.46 hours per batch**,
or **16.91 hours for A and B**. A practical planning allowance is 20–26 hours total.
That allowance is a heuristic, not a confidence or prediction interval. Only one
seed pair per workload was measured; failures, repairs, heat, and competing laptop
work can change the runtime. The configured maximum is 133.3 hours of agent time
for both batches, excluding warmup/judging; this is a guardrail, not a forecast.

The short calibration and this full-suite calibration remain separate exploratory
batches. Neither is used in the confirmation comparison. No task, generation
budget, confirmation seed, sample size, or statistical decision threshold was
changed after calibration. The only addition was this diagnostic calibration
profile and audit/execution/reporting helpers.
