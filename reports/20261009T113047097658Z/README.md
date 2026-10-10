# Local C/Go experiment

Batch: 20261009T113047097658Z. Model: llm-lang-lab-qwen35-9b.

Tasks: merge_intervals, word_counts, rpn, lower_bounds, grid_distance, rational_sum, edit_distance, transaction_ledger, dependency_order, csv_fields. Repeats per language/task: 20.

This is exploratory evidence on a small fixed task suite, not a language ranking.
Only this batch is included. Every generated source revision is included under sources/.
Raw event traces, prompts, and full diagnostics remain in the local batch directory.

| Language | Passed | First source passed | Mean submissions | Output tokens / success | Median seconds |
| --- | --- | --- | --- | --- | --- |
| c | 90/200 | 52/200 | 2.49 | 3893.5 | 86.5 |
| go | 94/200 | 45/200 | 2.94 | 3425.2 | incomplete timing |

See results.json for all settings, per-run metrics, model digest, and source hashes.
First-source scoring is independent of whether the agent later finishes successfully.
The controller stopped at the first public pass or submission limit.
A public pass is not a held-out success. Protocol v1 results cannot be pooled with this batch.

This is the amended JSONL recovery study, not the original frozen confirmation.
A retains 320 original results and one recovered trial with missing timing.
Timing aggregates affected by that missing value are not presented as complete.
