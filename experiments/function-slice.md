# Function-level development slice

Implemented on 2026-10-10 as follow-up to the 800-trial analysis. This is preparation
for cheaper observations, not a new study result or a demonstrated speedup.

`function_bench.py` provides two development tasks, lower bound and edit distance,
with equivalent C/Go function contracts. Trusted adapters perform only input/output
and invoke the submitted function. The generated function still implements the
entire algorithm. There are no model calls in this module.

The lower-bound oracle uses a linear count and is checked against binary search.
The edit-distance oracle uses a full matrix and is checked against an independent
recursive definition on exhaustive small inputs. Compiled C and Go reference
functions run through the real adapters on public and hidden cases, including
empty inputs, duplicates, signed extremes and maximum lengths. Semantic mutants
(upper bound and free substitution) must fail in both languages; malformed source
must fail compilation. Reference implementations exist only as test fixtures.

The judge compiles once per evaluation and runs every case, without the old
three-failure cutoff. It records source/wrapped-source hashes and full case counts.
It uses the existing restricted process execution and resource limits. These are
local execution guardrails, not a security boundary for hostile source code.
Hidden cases are development tests, not a fresh held-out confirmation bank.

Inspect candidate prompts without inference:

```sh
python3 function_bench.py plan
```

Evaluate a file containing only the requested function and optional helpers:

```sh
python3 function_bench.py judge --task lower_bound --language c --source /tmp/candidate.c
python3 function_bench.py judge --task lower_bound --language c --source /tmp/candidate.c --hidden
```

The judge exits zero only on a pass. The original whole-program harness, its
registered analysis and completed trial evidence are unchanged.

## Pilot draft and remaining integration

`function-slice-pilot.json` specifies eight proposed development trials:
two tasks x two languages x two repetitions. It deliberately retains the current
sampling and submission budgets initially, so adapter scope is the main change.
Eight observations can check execution and estimate rough throughput; they cannot
establish a language ranking or precisely estimate variance.

The draft **is not accepted by bench.py and is not runnable through pi yet**.
The next implementation step is a separate pi submission adapter and runner that:

1. Passes only the function body/helpers through pi; saves every original source
   and wrapped source, adapter hashes, model and compiler provenance.
2. Shows public feedback only; judges first and final sources privately after
   stopping and preserves all unsuccessful outcomes and usage.
3. Separates generation, compilation, testing and wall time; records truncation.
4. Preserves the completion record and clean pair-boundary checkpoints, with
   fake-provider tests before any real model pilot.

Then run the small calibration, compare measured token counts and timings with
the corresponding whole-program tasks descriptively, and decide whether to build
the broader 40-trial screen. A causal claim about speedup requires fresh randomized
whole-program versus function-level trials, not only a historical comparison.
The full screen still requires distinct problems and a fresh confirmation set;
repeating these two tasks twenty times is not a substitute.

Run validation:

```sh
python3 -m unittest discover -s tests -v
```

No new inference was launched during implementation of this slice.

Validation on 2026-10-10: all 68 repository tests passed, including five new
function-benchmark tests exercising both installed compilers and the adapters.
