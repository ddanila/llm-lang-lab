# Post-processing failure after trial 321

The driver stopped at 01:21 UTC on 2026-10-09 (04:21 Tallinn), after publishing
320 completed trial records. Replication B did not start. All nine checkpoint
publications succeeded; the last progress commit was `c85a8d0`.

## Root cause and fix

The Go word-count trial `320-word_counts-go-r16` produced U+0085 in diagnostic
output. JavaScript JSON.stringify preserves that character inside a JSON string.
Python str.splitlines treats it as a line boundary. The old reader therefore split
one valid JSON record into several invalid fragments and raised JSONDecodeError.
The original file contains four valid physical JSONL records, not corrupted data.

The shared JSONL reader now iterates physical file lines, preserving U+0085, U+2028,
and U+2029 inside strings. Both the benchmark and audit reader use it. Actually
truncated JSON still raises an error. The runner now saves agent_completion.json
with measured elapsed time, process return code, job identity and stop reason
before post-processing. Checkpoints hash that record when present. This supports
future forensic recovery; it does not automatically authorize replay of a trial.

Validation: all **53 offline tests passed**, including real pi with fake completions
and compiled Unicode-emitting code, an audit regression, corrupted-JSON rejection,
and a simulated reporting failure proving terminal measurements survive. Existing
tests continue to reject changed environments and running/invalid-batch resumes.

## Evidence preserved, without replay

All 320 completed trials reconcile to their raw token-usage events and recorded
submission counts under the corrected reader. Their original results are unchanged.
Trial 321 completed four submissions and reached submission_budget. Its final
submission failed compilation. Its four generated source revisions are now included
under sources/320-word_counts-go-r16/; parser-incident.json records usage and hashes.
No model answer was regenerated, no source was repaired, and no trial was dropped.
The raw run directory and its invalid status remain unchanged.

The old runner crashed before saving its result or running post-trial hidden tests.
Its exact monotonic elapsed time and process return code were held only in memory.
They cannot be reconstructed faithfully from file timestamps. No fabricated values
or guessed formal result have been inserted into the data.

## Recovery boundary

This is not a clean checkpoint: the batch is marked interrupted_or_invalid and
trial 321 has no formal result record. The parser fix also changes pinned runner
fingerprints. The existing registration and AGENTS.md explicitly prohibit resuming
invalid batches or mixing harness versions. Its original manifests are preserved,
not edited to make the new code appear identical. **The job remains stopped.**

A fresh registered confirmation run is compatible with the existing strict rules.
Keeping these 320 observations in a continued experiment instead requires a clearly
labeled recovery amendment, with the incomplete timing and harness change disclosed;
it cannot silently claim to be the originally frozen confirmation. These retained
observations remain useful exploratory evidence either way.
