# Plan after the C versus Go study — 2026-10-24

Status: **proposal, nothing registered**. The frozen result stays
[inconclusive under the recovery amendment](../reports/c-go-recovered-v3a/README.md).
This document orders the next work and adds two changes to the
[post-study recommendations](../reports/c-go-recovered-v3a/poststudy/README.md);
it does not alter them, and no new batch may start until a study file is
frozen for it.

## What the completed study actually established

- The harness works end to end: 800 trials, hourly sealed checkpoints, audited
  provenance, one honest recovery amendment, reproducible analysis from GitHub.
- It cannot yet resolve a language difference of the size that would matter.
  With 400 trials per batch the credible interval was about 16 points wide; the
  registered 5-point margin needs roughly 1,100 trials, about 25 hours.
- Most of the signal is between tasks, not between repetitions. One workload
  (lower bounds) reverses the aggregate on its own; CSV sits at floor for both
  languages and C lower bounds at ceiling. More repeats of the same ten
  specifications do not fix this.
- The direction depends on the endpoint. C is better on first submission, Go
  after repair. Go trials hit compile errors about 60% of the time, mostly
  unused imports and identifiers, and then recovered; C public passes failed
  hidden tests four to eight times as often as Go's.

## Priorities, in order

1. **Task bank before harness.** Author distinct problems across parsing,
   collections, numeric work, state machines, graphs and strings, each with an
   independent oracle, known-good C and Go solutions and failing mutants, as
   `function_bench.py` already does for two tasks. Split them into development,
   screening and held-out confirmation sets before any model sees them.
   This is slow work and it is the bottleneck; harness changes are not.
2. **A second model early, not last.** Everything so far is conditional on one
   9B model at 4-bit quantization and its particular failure modes. Add a
   hosted model slice to the screening stage under the same pi tool, prompt,
   budgets and judge, with cost recorded per trial. A language effect that
   appears only for the local model is a finding about that model.
3. **Controlled variants before a new language.** A language with no training
   data cannot be compared fairly with C or Go on this harness; familiarity
   would dominate design. Feature-on versus feature-off variants of an
   existing language, with the same runtime semantics and the same
   documentation budget, isolate one design choice at a time. A from-scratch
   language is a later step that needs its own zero-shot and few-shot protocol.
4. **Decision rule by simulation.** Fix the primary endpoint (first-submission
   or final correctness) per experiment, choose the effort criterion so it can
   actually fire at realistic success rates, and record false-win and
   inconclusive rates under null, equivalent, beneficial and heterogeneous
   scenarios before registering thresholds. The old 80% success gate for the
   effort endpoint could never be met at 45-50% success.

## First feature experiment: compile-time strictness

The completed study suggests a testable hypothesis: stricter compile-time
rejection lowers first-submission success and raises final success within a
repair budget. It can be isolated inside one language without new syntax.

- Variant off: C compiled with `-Wall -Wextra`, warnings only, as today.
- Variant on: the same C sources compiled with `-Werror` plus a fixed, documented
  warning set, so the categories Go rejects (unused variables, implicit
  conversions, unused results) become errors with the same diagnostics text.
- Same tasks, seeds, prompts, budgets and judge; only the compile command and
  one sentence of the prompt differ. Pair every trial across variants.
- Primary endpoint: final held-out correctness within budget. Secondary:
  first-submission correctness, compile failures, submissions, output tokens.

A Go mirror (tolerating unused imports by rewriting sources before the build)
is possible but lets the adapter edit the model's code; if used, record it as
a separate, weaker comparison.

Run it as a screen on development tasks first, with the sample size chosen by
simulation. Confirm only if the screen is clearly worth the compute.

## What stays unchanged

Completed batches, their registrations, the recovery amendment and the
decision rule they were analysed under are frozen. New work gets new study
files, new seeds and a fresh confirmation set; the ten existing workloads are
development material only.
