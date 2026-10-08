# Local C/Go pilot

Batch: 20261008T085856492366Z. Model: llm-lang-lab-qwen35-9b.

Tasks: merge_intervals. Repeats per language/task: 3.

This is exploratory evidence on a small fixed task suite, not a language ranking.
Only this batch is included. Every generated source revision is included under sources/.
Raw event traces, prompts, and full diagnostics remain in the local batch directory.

| Language | Passed | First source passed | Mean submissions | Output tokens / success | Median seconds |
| --- | --- | --- | --- | --- | --- |
| c | 2/3 | 0/3 | 3.67 | 4428.5 | 132.1 |
| go | 3/3 | 2/3 | 2.00 | 1683.0 | 109.0 |

See results.json for all settings, per-run metrics, model digest, and source hashes.
First-source scoring is independent of whether the agent later finishes successfully.
Effort includes any unnecessary resubmissions after public tests pass.
The current runner asks the agent to stop after a public pass but does not force it.
This behavior must be considered when interpreting effort differences.

The preceding two smoke runs are excluded. There were no provider/judge
infrastructure errors in this scored batch. The C failure exhausted its submission
budget and continued requesting submissions until the turn limit; its final
source also failed held-out tests. One Go run rewrote a passing first source,
temporarily regressed, and ultimately recovered.

The recorded source commit is dacbec8. After the batch completed, the runner's
stdout cleanup and final-turn completion boundary were corrected and covered by
the offline integration test. None of these six results was affected: the sole
eight-turn run was still requesting tools and had incorrect final source.

Go looks better here, but one task family and three repeats do not establish a
stable advantage. Next, freeze the stopping policy and expand task families and
repetitions before starting language design.
