# Overnight study v3: execution and recovery

## Why this is a new study

The v2 confirmation attempt `20261008T165022880692Z` stopped after 5/400 trials,
when a generated Go RPN program entered an infinite allocation loop and exhausted
its ten-second test watchdog. The v2 rule treated any candidate wall timeout as
infrastructure failure. [Evidence and diagnosis](../checkpoints/c-go-controlled-v2/20261008T165022880692Z/diagnosis.md)
are preserved; v2 B never started and no valid A/B conclusion exists.

V3 registers a new operational endpoint: candidate code must pass each case within
its execution budget. A candidate wall timeout fails that test/submission; it is
ordinary repair feedback, not a reason to invalidate the whole study. Compiler
wall timeouts, provider errors, and the 600-second agent watchdog still stop the
batch. Machine scheduling can affect this operational endpoint. No hidden tests
were changed and no observed solution was patched into a benchmark candidate.

This change follows a diagnosed execution failure, not a search for a language
winner. V3 starts both replications anew with disjoint sampling seeds 50,000,000
and 60,000,000, and schedule seeds 51001 and 51002. No v2 rows are reused. The ten
workloads, 20 repeats per language/workload, model, sampling parameters, generation
budgets, accuracy margins, statistical methods, and decision thresholds remain
unchanged. Historical registration files are preserved under `history/v2/` and in
Git commit `c4b5866ae9e01c81f4b3776f8bce3c4459cfb70d`.

## Hourly execution segments

A and B each still require 400 trials. Execution is split at a complete C/Go pair
boundary after roughly 3,600 seconds, including model warmup and post-trial judging.
The first pair gets an early checkpoint to verify end-to-end publication. No trial
is interrupted to meet the clock. Normal overshoot is a few minutes; the configured
pair budget permits up to 20 minutes of agent time plus judging. Checkpoint segments
are not new independent replications and are not analyzed to select a winner.

At each boundary the runner:

1. Checks source/model/tool fingerprints and seals the complete evidence prefix.
2. Exports every recorded trial, failures included, and every saved source revision.
3. Scans the portable export, commits it, and pushes it to GitHub. Git history
   retains earlier snapshots. Raw logs, agent configuration, binaries, and weights
   remain local; raw-log hashes are included in the portable backup.
4. Starts a fresh runner process for the next exact scheduled pair, verifying
   config, schedule, model, compiler/tool versions, and sealed evidence first.

A push failure gets two retries, then stops execution at the checkpoint. An
infrastructure failure gets an explicitly invalid progress snapshot before stopping.
No failed row is selectively rerun. All 800 trials and final integrity checks are
required before the usual analysis, final report commit, and push.

## Runtime and validation

Historical full-suite calibration completed twenty trials in 25.4 minutes, with
C 4/10 and Go 6/10; it was neither an overall floor nor ceiling. Its extrapolation
is 16.9 hours for 800 trials. Plan for 20–26 hours, not a guaranteed overnight finish.
The changed timeout policy and hourly warmups/publication mean this is an estimate,
not a measured v3 duration or statistical prediction interval.

The pre-launch validation suite has **48 offline tests**. It includes a two-segment
run proving that failed rows are preserved and not replayed, rejection of tampered
source, changed environments and incomplete trials, portable checkpoint labeling,
and real pi with fake completions checking candidate versus compiler timeouts.
No model inference is used by these tests. `execution.json` records fingerprints
and validation evidence before the new confirmation launch.

## Operate and recover

The actual overnight run is detached, with idle-sleep prevention and its process
group in `.local/confirmation.pid`. Equivalent foreground invocation:

```sh
mkdir -p .local
caffeinate -i python3 -u run_study.py --publish --checkpoint-seconds 3600 --first-checkpoint-seconds 1 > .local/confirmation.log 2>&1
```

The first checkpoint occurs after the first pair; later ones target an hour.
Keep the laptop powered and open. Inspect `.local/study-run.json` and
`.local/confirmation.log` for progress and the latest pushed checkpoint commit.
Only a clean sealed checkpoint may resume:

```sh
caffeinate -i python3 -u run_study.py --resume --publish --checkpoint-seconds 3600 >> .local/confirmation.log 2>&1
```

An unfinished/running/invalid batch is rejected rather than replayed. A crash
mid-segment requires inspection and can require a new whole batch. Existing commits
and local evidence are never discarded or rewritten to rescue a comparison. Do not
edit tracked files during execution: unrelated modifications block publication.

[Intermediate backups](../checkpoints/README.md) are explicitly not final results.
The [joint report](../reports/c-go-checkpointed-v3/README.md) appears only after both
complete replications validate. Publish an inconclusive outcome as inconclusive;
do not keep sampling until a preferred winner appears.

For deliberate one-segment execution, add `--pause-after-checkpoint`. It exits
cleanly after publishing that segment; a later `--resume` continues without
replaying trials. The overnight invocation omits this flag after startup validation.
