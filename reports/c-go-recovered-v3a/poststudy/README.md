# Post-study analysis and a faster A/B method

2026-10-10. Exploratory analysis of the completed 800 observations. The frozen
result remains **inconclusive under the recovery amendment**. A and B are
reported separately throughout; no pooled test is used to rescue a winner.
No new model runs or changes to the registered harness were made for this analysis.

The practical objective should be a fast, calibrated decision procedure that
can return **better, worse, equivalent, or insufficient evidence**. A procedure
that always names a winner will not be reliable when the actual difference is small.

## What repeated

Each cell below is successes out of 20 generations. These are descriptive task
comparisons, not ten independently confirmed significance claims.

| Task | A C | A Go | B C | B Go |
| --- | ---: | ---: | ---: | ---: |
| CSV fields | 0 | 0 | 0 | 0 |
| Dependency order | 9 | 9 | 8 | 7 |
| Edit distance | 9 | 9 | 16 | 16 |
| Grid distance | 11 | 7 | 8 | 7 |
| Lower bounds | 20 | 7 | 20 | 9 |
| Merge intervals | 12 | 20 | 15 | 16 |
| Rational sum | 10 | 9 | 11 | 7 |
| RPN | 1 | 6 | 1 | 9 |
| Transaction ledger | 15 | 19 | 13 | 18 |
| Word counts | 3 | 8 | 2 | 12 |
| Total | 90 | 94 | 94 | 101 |

The aggregate result hides opposing task effects. Lower bounds favors C strongly
in both batches; word counts, RPN and transaction ledger favor Go in both.
Removing lower bounds raises the observed Go lead to 9.44 points in A and 10.00
in B. Removing word counts reverses it to -0.56 and -1.67 points respectively.
Do not remove either workload after seeing this. Instead define the intended
workload distribution before the next comparison. Twenty repeated generations
of one specification are not twenty independent programming problems.

The original 95% credible intervals for Go minus C were approximately
[-6.11, 9.58] points in A and [-4.27, 10.54] in B (prior 0.5). Both include
zero and practically important effects in either direction. Neither fits inside
the registered equivalence band of +/-5 points. The matching direction of the
point estimates is not a replicated advantage or evidence of equivalence.

## The language-by-controller interaction matters

| Diagnostic (200 trials per cell) | A C | A Go | B C | B Go |
| --- | ---: | ---: | ---: | ---: |
| First source passes hidden tests | 52 | 45 | 53 | 42 |
| Final success after first-source failure | 38 | 49 | 41 | 59 |
| Trials with any compilation failure | 44 | 118 | 44 | 122 |
| Stopped after public pass | 129 | 100 | 124 | 104 |
| Public pass but final hidden failure | 39 | 6 | 30 | 3 |
| Final compilation failure | 4 | 35 | 6 | 31 |
| Mean submissions | 2.49 | 2.94 | 2.52 | 2.93 |

C does better on first-source correctness, Go on final correctness. Thus even
the direction depends on whether we mean initial generation or interactive
repair. Go encountered compilation failures in 59-61% of trials, versus 22%
for C. Compiler diagnostics include unused identifiers/imports and undefined
symbols; substring counts in diagnostics.json overlap and are not causal labels.

About 24-30% of C public passes failed hidden tests, versus 3-6% for Go. The
controller immediately ends the trial at public pass, so these programs receive
no further repair opportunity. This measures the full language/compiler/public
test/controller system, not syntax alone. More development tests might help,
but we cannot infer the counterfactual improvement without a fresh experiment.

Manually inspected failures illustrate several distinct mechanisms:

- Grid distance: returning zero for a blocked start equal to the target.
- RPN: rejecting a valid signed positive integer such as `+2`.
- Word counts: a C solution stops reading at an embedded NUL byte.
- Rational sum: wrong large-number arithmetic or denominator sign.
- Edit distance: treating a transposition as one edit, contrary to the spec.
- Lower bounds: a Go first attempt assumes the header line contains all values,
  despite whitespace-separated input. This example does not establish the cause
  of all Go lower-bound failures.

These are examples from saved diagnostics, not an exhaustive root-cause count.
Hidden judging stops after three failed cases and truncates long diagnostic
inputs; a per-case pass fraction computed from those records would be censored.
Do not promote it to a comparable partial-credit score.

There were only 5 assistant responses ending at the output limit in A and 8
in B, out of 1,091 and 1,100 responses. Raising the token limit is not the first
optimization supported by these data. Zero CSV successes in both languages is
a reason to audit difficulty, specifications and the oracle, not to delete CSV
or assume a judge bug. C lower bounds is at the opposite, ceiling extreme.

## What one hour can and cannot tell us

We sampled 5,000 subsets without replacement within each task and batch,
retaining C/Go pairs. These are retrospective screening diagnostics, **not
confidence intervals, power estimates, or evidence about new tasks**.

| Trials per subset | Approximate agent time | A middle 95% of observed gaps | B middle 95% |
| ---: | ---: | ---: | ---: |
| 20 | 0.5 h | -30 to +40 points | -30 to +40 points |
| 40 | 1 h | -25 to +25 | -20 to +25 |
| 80 | 2 h | -15 to +17.5 | -12.5 to +20 |
| 200 | 4.8-5 h | -6 to +10 | -4 to +11 |

At 40 trials, Go leads in only 48% of A subsets and 53% of B subsets; there
are also ties. Selecting the point-estimate winner of an hourly run would be
unreliable here. Subsets of the full 400 trials trivially have no variability;
that is a finite-dataset property, not certainty about the true effect.

For scale, define paired D = Go success minus C success. A fixed-suite normal
approximation gives Var(mean D) = mean(within-task Var(D)) / number of pairs,
with equal allocation. Using the observed within-task sample variances:

| Desired approximate 95% half-width | Trials, A estimate | Trials, B estimate | Agent time |
| --- | ---: | ---: | ---: |
| 10 points | 280 | 260 | 6-7 h |
| 5 points | 1,120 | 1,020 | 25-27 h |
| 3 points | 3,080 | 2,820 | 70-73 h |

These are rough **precision calculations, not powered study recommendations**.
They ignore task-population uncertainty, sequential/multiple-comparison costs,
and uncertainty in the variance estimate. Runtime uses recorded agent time,
excludes the one missing A duration, post-generation auditing and downtime.
An interval narrower than +/-5 is also not automatically enough to demonstrate
equivalence when its center is away from zero. A true 2-point gain cannot become
a true gain greater than the registered 5-point superiority margin by sampling
more. More runs may eventually support equivalence instead.

## Recommended method: quick screening, selective confirmation

### 1. Define the question and reduce work per observation

For language-design iteration, start with **function-level generation**:
the agent writes only the function under test, while reviewed adapters provide
input/output, entry points and test execution. Use identical semantic tasks,
standard-library policy and equivalent adapters in both languages. Count all
generated output tokens, including failed repairs; report input tokens separately.

This intentionally measures a different question from end-to-end CLI programs.
Keep a smaller whole-program track for I/O, tooling and integration capability.
It would be misleading to claim adapter-assisted results prove whole-language
superiority. The adapters must not implement the actual task for the model.

Expose first-attempt correctness and final correctness separately. Predeclare
one as primary for each experiment. For syntax/representation changes, use
first-attempt correctness as the initial screen; for coding-agent productivity,
use correctness under a fixed repair budget. Do not call interactive repairs
independent pass@k samples. Measure correctness at common cumulative token
budgets and output tokens per successful result, including failed trials.

A shorter task and response can save inference time. Turning temperature to zero
merely to obtain repeated identical answers does not establish generalization.
Compare decoding choices on development tasks only, then freeze the choice.
Cache trusted test inputs and references; profile compilation versus inference
before optimizing. Avoid simultaneous model workers on this laptop until memory
and throughput have been measured. Reusing a stored baseline is useful for
development, but conditions on those baseline draws and needs fresh baseline
generation for final confirmation.

### 2. Audit and diversify the task bank

Create disjoint development, screening and held-out confirmation problem sets.
The existing ten tasks are now development material. Build a broader bank with
several independent problems per semantic family: parsing, collections, numeric
work, state machines, graphs, strings. Do not select tasks for a preferred winner.
Allocate the early budget to different problems before many repetitions of one.
Data-input variants alone do not replace distinct problem specifications.

Before model evaluation, verify each oracle against an independently written
reference and metamorphic/property tests; run known-correct C and Go solutions
and deliberately faulty mutants through the same judge. Check empty/maximal
inputs, numeric bounds, encodings, duplicate edges, line endings and output
normalization. Inspect floor/ceiling tasks and document any change in a new
benchmark version. Keep legacy results intact.

Use a stronger fixed development suite for feedback, with a separate locked
hidden suite that never reaches the agent. Specify the stop rule in advance.
Test-suite strength can change apparent model correctness; this concern is also
supported by [EvalPlus](https://arxiv.org/abs/2305.01210). Its result motivates
an audit, not a numerical correction to our scores.

### 3. An approximately one-hour screen

Proposed starting budget: **20 distinct problems x 2 variants x 1 generation =
40 trials**. At the current whole-program pace that is roughly one hour of
agent time; function-level timings must be measured before promising a faster
turnaround. Pair each problem and seed across variants, randomize execution
order, and freeze prompts, runtime, model and compiler digests.

Return per-family effects, first-attempt/final correctness, compilation failures,
tokens and uncertainty. Mark the result **screening only**. Use it to reject
obvious regressions or prioritize promising ideas, not certify a small win.
No marginal leader automatically triggers a full overnight run. Set the maximum
compute and smallest practically useful improvement before launching.

Same integer seeds do not guarantee positively correlated errors across
languages. Measure the variance of paired differences during calibration rather
than assuming a variance reduction. For new language features, a controlled
feature-on/feature-off comparison with the same runtime semantics is more
diagnostic than another broad C-vs-Go ranking. Novel syntax also changes training
familiarity: standardize documentation and examples, and state that limitation.

### 4. Confirm only selected candidates, with valid stopping

Use fresh held-out tasks and fresh seeds for the chosen candidate. For the first
implementation, prefer a **fixed sample size selected by simulation** and one
final analysis. Hourly backups are operational checkpoints, not significance
tests. Choose the budget after calibration against null, equivalent, beneficial,
harmful and heterogeneous scenarios, including the entire candidate-selection
process. Record false-win rate, correct decisions, inconclusive rate and runtime.

If early stopping materially saves time, implement either prespecified group
sequential boundaries with error spending, or a validated confidence sequence
for the paired outcome. Ordinary 95% intervals checked hourly are not a valid
sequential stopping rule. Time-uniform intervals address this issue;
see [Howard et al.](https://arxiv.org/abs/1810.08240). A library or formula still
needs validation for our task clustering and sampling design.

New-task generalization requires task-level uncertainty (for example a
prespecified hierarchical model or task-cluster resampling). Do not treat all
seed repetitions as independent tasks. Few task clusters limit the reliability
of either approach. Retain a fixed-suite analysis as a clearly separate claim.

Proposed decision vocabulary: correctness better, worse, equivalent, or
inconclusive. Separate correctness equivalence from effort equivalence. The
current implementation's 80% success gate prevents an effort winner at our
45-50% success rates; lowering that gate after observing these results would
not validate the old experiment. For a new study, choose any effort/noninferiority
criterion before data collection and simulate its behavior. Do not combine
accuracy, time and tokens into an arbitrarily weighted "hardness" score.

For multiple language ideas, exploratory screens may guide selection, but final
claims need independent confirmation and an explicit multiple-comparison policy.
Never move a previously used confirmation set back into the held-out pool.

### 5. Keep collection robust independently of statistical conclusions

Retain append-only per-trial events, atomic completion records, checksums and
pair-boundary checkpoints. Separate collection from a retryable publication
queue: a network outage should retain a clean local checkpoint without losing
evidence. Record awake inference, compilation/judging, and elapsed wall time
separately; record sleep/resume and thermal/power conditions. Any new recovery
behavior needs predefined rules and tests, not selective replay of failed rows.

Before another scored run, exercise Unicode JSONL, abrupt termination, restart,
offline pushes and sleep/wake with a fake provider. Add inexpensive A/A pipeline
checks and a development-only identical-seed reproducibility check. A/A checks
can expose bugs and drift, but cannot prove the absence of bias. Preserve invalid
attempts and distinguish model failure from provider/judge failure.

## Concrete next work, without another overnight study yet

1. Build and verify function adapters and the independent-oracle/mutation checks.
2. Prepare the disjoint task bank and freeze screen/confirmation definitions.
3. Calibrate the proposed 40-trial screen on development tasks; measure speed,
   truncation, outcome variance and repair yield. This is a proposed future run.
4. Simulate and test the decision rule, including null false-win rates and
   sequential selection if used; register budget and thresholds before scoring.
5. Compare one controlled language feature, then confirm only if worthwhile.

The promising path to **fast and reliable** is cheaper observations, broader
task coverage, and spending confirmation compute selectively. We have no evidence
that an hour can reliably distinguish a 2-3.5-point difference on this laptop.
An hour can still be a useful development cycle if uncertainty is visible and
the result is allowed to remain inconclusive.

## Reproduce these diagnostics

From the repository root, using only published portable results:

```sh
python3 poststudy.py --output /tmp/llm-lang-diagnostics.json
```

With the original raw traces available locally, regenerate the checked-in
aggregate diagnostics (no raw messages or machine paths are exported):

```sh
python3 poststudy.py --local-diagnostics --output reports/c-go-recovered-v3a/poststudy/diagnostics.json
```

The script records input SHA-256 hashes, verifies paired completeness, and checks
local result fields against portable exports before using local diagnostics.
The computational analysis is separate from analysis.py and the frozen decision.
