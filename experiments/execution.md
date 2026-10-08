# Calibration, freeze, and confirmation execution

## Completed before confirmation

1. Ran the [12-trial short pilot](../reports/20261008T160452882425Z/README.md).
   C passed 1/6 and Go 4/6, but six trials were cut off at 120 seconds. Its effort
   totals are lower bounds and cannot support an efficiency decision.
2. Audited all traces, then ran a separate [20-trial full-suite calibration](../reports/20261008T162135502883Z/README.md)
   at the already registered confirmation limits. All twenty passed schedule,
   source, usage, and stopping checks. No provider error, agent cutoff, compiler
   timeout, or test wall timeout occurred. All twenty have complete usage.
3. Checked difficulty: C passed 4/10 and Go 6/10, with successes in both languages,
   failures in both, and different workload-specific directions. This is neither
   an overall floor nor ceiling. One pair per workload cannot establish a ranking.
   Keep the original ten workloads and hidden tests unchanged.
4. Estimated runtime from the 25.4-minute complete calibration: 8.46 hours per
   400-trial batch, 16.91 hours total. Allow 20–26 hours operationally; this is a
   heuristic allowance, not a statistical interval. The earlier short pilot is
   unsuitable for runtime extrapolation because half its trials were interrupted.
5. Reaffirmed the frozen A/B protocol and passed all **40 offline tests** before
   confirmation. Tests use fake completions, not extra local-model benchmark data.
   The eight fingerprinted benchmark files and both confirmation profiles remain
   byte-for-byte identical to revision `c6bc841ec62d3657909874d2ec17a7e8ed46f5ad`.
   Added audit/execution/reporting helpers do not change prompts, tasks, budgets,
   sample size, seeds, stopping criteria, or statistical thresholds.

[execution.json](execution.json) records source/helper fingerprints, environment,
model digest, calibration IDs, and the test-log hash. Each confirmation batch
records the exact pre-execution Git commit and repeats source/model checks.
No pi fork customization was needed; generation still runs through installed pi.

## Authorized confirmation workflow

Run A then B, each 10 workloads × 20 repetitions × 2 languages. Keep every trial,
including wrong answers and exhausted submission budgets. Neither calibration
batch enters confirmation analysis. Do not inspect A and alter B. An infrastructure
fault stops the sequence; preserve the invalid batch, diagnose it, and make a new
whole-batch execution plan rather than replacing selected rows.

The sequential runner is:

```sh
mkdir -p .local
caffeinate -i python3 -u run_study.py --publish > .local/confirmation.log 2>&1
```

The actual run is detached from the interactive terminal, with its process-group
ID in `.local/confirmation.pid`. It retains idle-sleep prevention while running.
The laptop was on AC power at launch preparation. Closing the lid, stopping Ollama,
or changing the environment can still interrupt the run.

Inspect progress without inference:

```sh
cat .local/study-run.json
tail -20 .local/confirmation.log
```

Stages are `running_A`, `running_B`, `validating_and_exporting`, `publishing`,
then `complete`, or `stopped_with_error`. A successful exit means both full batches
passed validation, portable reports reproduced the raw analysis, privacy checks
passed, and (with `--publish`) the report commit was pushed. The runner never
silently resumes incomplete data or retries failed rows. The execution record
prevents accidental duplicate launches.

The final [joint report](../reports/c-go-controlled-v2/README.md) and machine-readable
analysis are created only after both batches validate. Until then, no confirmation
conclusion has been published. An inconclusive result is legitimate and will be
published as such. No language design decision follows from calibration alone.

## What follows the result

Use a replicated result or useful tie as a baseline. Then test new workload families
and a second model before making a broad claim about LLM-friendly languages.
For language design, change one feature at a time and budget documentation/examples
explicitly for both the experimental language and existing-language baselines.
If A/B is inconclusive, report that outcome and preregister a new study before
collecting additional confirmation data.
