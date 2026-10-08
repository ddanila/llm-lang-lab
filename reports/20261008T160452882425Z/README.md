# Local C/Go experiment

Batch: 20261008T160452882425Z. Model: llm-lang-lab-qwen35-9b.

Tasks: merge_intervals, word_counts, rpn. Repeats per language/task: 2.

This is exploratory evidence on a small fixed task suite, not a language ranking.
Only this batch is included. Every generated source revision is included under sources/.
Raw event traces, prompts, and full diagnostics remain in the local batch directory.

| Language | Passed | First source passed | Mean submissions | Output tokens / success | Median seconds |
| --- | --- | --- | --- | --- | --- |
| c | 1/6 | 0/6 | 2.33 | 10372.0 | 120.0 |
| go | 4/6 | 2/6 | 1.83 | 1393.2 | 44.4 |

See results.json for all settings, per-run metrics, model digest, and source hashes.
First-source scoring is independent of whether the agent later finishes successfully.
The controller stopped at the first public pass or submission limit.
A public pass is not a held-out success. Protocol v1 results cannot be pooled with this batch.

## Calibration audit

Six of twelve trials reached the 120-second cutoff (C: 5/6, Go: 1/6).
Their unfinished completions have incomplete token accounting. The output-token
figures above are lower bounds, not valid efficiency comparisons. No stable
language ranking is inferred from this calibration batch.

All twelve traces passed checks for schedule alignment, authoritative completed-response
usage totals, revision counts, frozen final source, and no submission after a public
pass. Batch-end model and source checks passed; no provider errors were recorded.
Raw traces remain local; audit.json records their hashes and audit results.

Observed failures include compile errors, reversed subtraction operands, incorrect
interval merging, and word counting that removes newline separators. One Go
word-count solution passed public examples but failed held-out tests. These are
model implementation errors; no task or oracle was changed in response.

A separate full-suite calibration uses the existing confirmation limits and
disjoint calibration seeds to assess runtime and difficulty without short-cutoff
censoring. This batch will not be pooled with that calibration or confirmation.
