# Authorized JSONL recovery amendment — 2026-10-09

Study: **c-go-recovered-v3a**. Amendment: **jsonl-recovery-2026-10-09**.
The user explicitly authorized retaining the 320 completed results, recovering
trial 321 from existing submissions with missing timing marked, and continuing at
trial 322. This supersedes the no-resume rule only for this documented recovery.
The original invalid batch remains unchanged; continuation uses a new batch.

## Original evidence and retained observations

Original A: `20261008T173711298748Z`, generated under commit
`c25122721195e3a34cde3a09a1c25d28007c12df`. The 320 existing result.json files and
all raw/source evidence were copied byte-for-byte into the amended batch. Its
original environment, config and invalid status are preserved separately. The
original schedule is unchanged. No model generation was replayed, dropped, or
selected based on success. `recovery-prefix.json` registers hashes of every
imported observation and its raw evidence, plus the old metadata and harness hashes.
Each checkpoint revalidates the imported prefix. Final analysis also verifies
portable observation hashes against this registration.

The runtime environment and model were checked against the original snapshot.
Prompts, pi extension, tasks, hidden tests, judge limits, sampling settings, seed
schedule, repetitions and statistical thresholds are unchanged. The parser fix was
committed as `fef6a20`; amended reporting/checkpoint validation is separately recorded
in the continuation environment. New source fingerprints describe continuation
code, not retroactively the code used to generate the imported observations.

## Trial 321 recovery

The original `320-word_counts-go-r16` trace contains four complete submissions and
the controller's submission_budget stop. The corrected physical-line JSONL reader
recovers all four feedback records. Authoritative response events supply full token
usage: 2,278 output tokens. No provider error or missing usage field was recorded.
The fourth saved source matches the final source and failed compilation. The first
submission also failed public tests. Therefore final and first-submission success
are both false. Post-trial hidden checks were completed on the unchanged first and
last sources using the same judge; these never go back to the agent.

The recovered result records elapsed_seconds and returncode as **null**. Exact
measurements were lost by the old post-processing crash and are not imputed from
file timestamps. PAR-2 remains 1,200 seconds, the existing rule for a failed trial;
it is a derived penalty, not reconstructed elapsed time. Only this registered row
may have missing timing. Its tokens count fully toward effort, and its failed
outcome counts fully toward correctness. All source revisions and public feedback
are retained. The new runner saves terminal facts before post-processing.

## Continue exactly the remaining schedule

A has 321 retained/recovered observations. Trial 322 is its original C word-count
partner at repeat 16, sampling seed 50,000,036. Continue the remaining 79 A trials,
then all 400 B trials with the original B seeds. Total remains 800, not 801.
No trial is regenerated to fill a gap. A's first resume boundary is exceptionally
odd (321), allowed only when the registered prefix and provenance match exactly.
Subsequent checkpoints follow normal complete-pair boundaries.

Hourly commit/push behavior remains enabled. A startup checkpoint after trial 322
verifies the resumed path before the regular hourly driver continues. The old local
driver state/log are archived; the amended driver state names the new A batch.
Unrelated invalid batches and altered evidence are still rejected.

## Analysis and disclosure

The registered correctness and token-effort calculations and thresholds are
unchanged. Missing latency affects neither endpoint, but this is an operational
recovery amendment made after partial outcomes were seen. It is **not the original
unamended frozen confirmation**, and should not be presented as one.

Final output statuses are replicated_under_recovery_amendment or
inconclusive_under_recovery_amendment. The same A/B agreement and prior-sensitivity
rules still apply. Portable exports carry recovery provenance so replaying analysis
from GitHub gives the same qualified conclusion as the local raw batches.

The affected language's full-sample median and A's total agent seconds are marked
incomplete, rather than silently omitting the missing observation. The audit also
reports known agent seconds and the number of missing values. End-to-end wall time
for A starts at the original A batch and includes the recovery downtime, so it is
not an active inference duration. B cannot use the missing-timing exception.

Historical v3 registration files remain under history/v3/ and in Git history.
No old source fingerprint, invalid status, or original result has been rewritten.
