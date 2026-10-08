# C versus Go: controlled protocol v2

Status: **calibration complete; confirmation execution authorized**.
The [full-suite calibration](../reports/20261008T162135502883Z/README.md) completed
20 trials without timeouts or infrastructure errors. The earlier
[short pilot](../reports/20261008T160452882425Z/README.md) had six timeout-censored
trials. These are separate exploratory batches. See the
[execution/freeze record](execution.md) for the audit, difficulty decision, runtime
estimate, and execution commands. Confirmation has no published conclusion until
the [joint report](../reports/c-go-controlled-v2/README.md) exists.
Historical protocol-v1 results cannot be pooled with these experiments.

## The question

For this pinned local Qwen model and this fixed ten-workload suite, does a
language produce more correct programs within equal generation/repair budgets?
If correctness is practically equivalent, does one language require fewer
generated tokens per verified solution?

A stable tie is a useful result. We cannot guarantee a winner, or remove
training-data familiarity by adding repetitions.

## Preparation and execution

The commands below inspect plans without contacting Ollama or running inference:

```sh
python3 bench.py plan --config experiments/pilot.json
python3 bench.py plan --config experiments/confirm-a.json
python3 bench.py plan --config experiments/confirm-b.json
python3 -m unittest discover -s tests -v
```

Tests run real pi against a **fake local completion server**; they do not call
Ollama or any hosted model. Task-oracle tests and synthetic statistical tests are
also offline.

When execution is wanted, the corresponding commands are:

```sh
python3 bench.py run --config experiments/pilot.json
python3 bench.py run --config experiments/confirm-a.json
python3 bench.py run --config experiments/confirm-b.json
python3 analysis.py runs/BATCH_A runs/BATCH_B
```

Run A and B separately, sequentially on the same laptop. The sequential runner
performs both runs, trace audits, portable exports, and the frozen comparison:

```sh
mkdir -p .local
caffeinate -i python3 -u run_study.py --publish > .local/confirmation.log 2>&1
```

This explicitly runs inference for many hours. `--publish` additionally authorizes
committing and pushing the validated reports; omit it to keep exports local.
`.local/study-run.json` records the active phase, batch IDs, completion, or errors.
Keep the laptop powered and awake; closing its lid or stopping Ollama can interrupt
the experiment. `caffeinate` prevents idle sleep, not every kind of interruption.
The runner refuses an existing execution record and never resumes a partial batch
or retries individual rows. An invalid A batch prevents B from starting. It also
checks that analysis of the portable exports matches analysis of raw artifacts.
Publication stops if tracked files changed or the automated privacy scan flags
an export. Raw traces remain local. A stopped run requires inspection; it is never
silently relabeled complete.

 Do not inspect A and
change B's tasks, budgets, model, thresholds, or sample size. Neither confirmation
profile permits CLI task/repetition overrides.

| Profile | Workloads | Repeats per language/workload | Trials | Purpose |
| --- | --- | --- | --- | --- |
| pilot.json / default config.json | 3 | 2 | 12 | Check the controlled loop and find infrastructure problems |
| calibration-full.json | 10 | 1 | 20 | Assess all workloads at confirmation limits; separate seeds |
| confirm-a.json | 10 | 20 | 400 | First confirmation batch |
| confirm-b.json | Same 10 | 20, different seeds | 400 | Independent generation replication |

The pilot has a 120-second limit per agent trial: at most 24 minutes of agent
time, plus model warmup and post-trial judging. This is not a hard 30-minute
end-to-end limit. Confirmation uses a 600-second safety timeout; it is a
substantial, likely many-hour experiment, not the short pilot. The plan command
prints maximum agent time, excluding warmup/judging. The added full-suite calibration
uses the same 600-second limit, four submissions, and 2,048 output tokens per turn
as confirmation, with schedule seed 31002 and sampling seeds 40,000,000 onward.
It is diagnostic only; it does not change the registered A/B settings or decision rule.

Twenty repeats are a starting sample size, not a power guarantee. Differences
near the decision thresholds may remain unresolved. An inconclusive result means
inconclusive; a larger study needs a new plan, frozen before collecting more data.

## Trial controller

- Only pi generates candidate source. It has one tool, submit_source.
- The controller closes and freezes the submission at the first public-test pass.
  The extension also prevents an extra model request at the next turn boundary.
- Otherwise the controller closes at four saved submissions or four completed
  assistant turns. Extra source/tool calls cannot overwrite a closed trial.
- Each response is capped at 2,048 output tokens. Thinking is disabled.
- Public examples alone guide repairs. Hidden tests are applied after pi exits.
  A public pass can still be a scored failure.
- The first submitted source is scored separately after the trial, for diagnosis.
- A confirmation safety timeout invalidates the batch for comparison. It is not
  evidence that the language is harder. Pilot timeout data are only diagnostic.
- Executables have a three-second CPU limit and a ten-second wall-clock guard
  per case. The wider wall guard allows cold macOS executable/Seatbelt startup.
  Compiler or test wall-timeouts also invalidate confirmation: a wall timeout
  cannot reliably distinguish a program hang from a laptop scheduling stall.

The stop rule is mechanical rather than dependent on the model obeying “stop.”
The first public pass is not an oracle for hidden correctness; we intentionally
give no further hidden-guided repair attempts.

## Controls

Temperature stays at 0.7: we measure variability instead of concealing it behind
one deterministic answer. Temperature zero is useful for debugging but does not
make a single answer representative, and it need not give bit-identical Metal
inference.

Each task/repeat block has a unique sampling seed, shared by its C and Go trials.
Language order alternates within each task with a seeded initial order, so each
language goes first equally often across 20 repetitions. Task order is shuffled.
Replication A uses seeds 10,000,000 onward; B uses 20,000,000 onward.

Every trial gets a fresh pi process, private config, and empty working directory.
The model digest includes the local alias parameters and is pinned to the actual
installed Q4_K_M artifact. Context is checked against Ollama's alias, not merely
advertised to pi. The runner checks source hashes between trials and verifies
model/tool versions again at batch completion. A batch completion marker records
the final hashes; interrupted/changed batches are rejected.

The same seeds do not mean identical random draws across different language
prompts. Independence of repeated generation is an assumption, not a guarantee;
backend cache effects and scheduling can still matter. Two batches replicate
generation on the same workload suite, not transfer to unseen problems.

## Decision rule, fixed before confirmation

Primary endpoint: final held-out success within the controlled budget, with each
of the ten workloads weighted equally. A useful correctness advantage is **more
than 5 percentage points**. A practical correctness tie is within **±5 points**.

For each workload, paired C/Go outcomes have four categories: both fail, Go only
passes, C only passes, both pass. We use an independent symmetric Dirichlet prior
over each workload's four probabilities, then add observed counts. Posterior
draws give the equally weighted Go-minus-C success difference.

We report **95% Bayesian credible intervals**, not frequentist confidence
intervals. Unlike a naive bootstrap of all tied observations, these retain
uncertainty when every observed outcome is identical. Decisions must agree using
both 0.5 and 1.0 prior counts per category. The priors and 10,000 draws with a fixed
analysis RNG seed are specified in analysis.py.

Secondary endpoint: total generated output tokens / number of verified successes,
including tokens from failed runs. A useful effort advantage is **more than 15%**.
For Go/C, the ratio boundary is 0.85; for C/Go, the reciprocal is 1/0.85.

We use a paired bootstrap within each fixed workload for the effort ratio.
Undefined zero-success samples or incomplete token accounting disable effort
decisions rather than being silently discarded. Both languages must have at
least 80% observed success before an effort comparison can determine the winner.

In **each** confirmation batch:

1. A correctness winner requires its entire credible interval beyond the
   five-point advantage boundary under both priors.
2. Only if both priors place the correctness interval entirely within ±5 points
   may effort determine the winner. The entire effort interval must cross the
   15% improvement boundary.
3. A practical tie requires correctness equivalence and the entire effort ratio
   interval within [0.85, 1/0.85].
4. A claimed winner must keep its direction when any one workload is omitted.
5. All other outcomes remain inconclusive for declaring a winner or full tie.

The same decision must hold in A and B. analysis.py rejects incomplete,
duplicated, mixed-version, unregistered, overlapping-seed, or infrastructure-broken
batches before it performs inference. It does not pool A and B to rescue a result.
The runner stops a confirmation batch at its first infrastructure error rather
than spending hours on an already invalid comparison. Keep the invalid artifacts;
repair the environment and rerun the whole batch, never just the failed rows.

The posterior assumes independent repeated pairs within a workload and independent
per-workload parameters. The bootstrap and selected practical margins are research
choices, not a universal statistical guarantee. The inference is conditional on
these ten workloads: two graph tasks or two parsing tasks are not evidence of ten
independent domains.

## Afterward

Do not design a new language merely because one small pilot looks favorable.
First establish a repeatable result or useful tie under this protocol. Then
replicate on new workload families and another model, and measure small controlled
language changes. Give a new language an explicit, budgeted documentation/examples
context and compare against similarly supported baselines.

If all models/languages fail, adjust task difficulty or budgets in a new study.
If correctness is saturated, the prespecified effort comparison can still be
informative. Never keep sampling until a preferred winner appears.

References:
[Paired observations (NIST)](https://www.itl.nist.gov/div898/handbook/prc/section3/prc311.htm),
[Dirichlet distribution (Stan)](https://mc-stan.org/docs/2_31/functions-reference/dirichlet-distribution.html),
[Conjugate multinomial inference (Duke)](https://www2.stat.duke.edu/~scs/Courses/Stat340/LectureSlides/Lec11_BayesianStats_Handouts.pdf),
[Agent evaluation and repeated trials (Anthropic)](https://www.anthropic.com/engineering/demystifying-evals-for-ai-agents).
