# llm-lang-lab

An experiment toward a programming language that is easier for LLM agents to use.

First establish whether a local, repeatable harness can detect differences between
existing languages. Only then design a language and measure it against the same
baselines. No new language is implemented yet.

The first comparison is C17 versus Go, using **pi** as the agent and a local
**Qwen3.5 9B Q4_K_M** model through Ollama. Python orchestrates the experiment; it
does not generate the candidate solutions.

The [first six-run pilot](reports/20261008T085856492366Z/README.md) is published
with metrics and generated source revisions: Go passed 3/3 interval-merging trials,
C passed 2/3. This is exploratory evidence, not a stable language ranking.

**Protocol v2 is prepared, not run.** It enforces stopping and adds a frozen
[replication study](experiments/README.md). Historical v1 results cannot be
pooled with v2.

## Run locally

Requirements: Python 3.9+, pi 1.1.0 with extension support, Ollama, Clang, Go.
No Python packages are required. The current adapter targets
[@earendil-works/pi-coding-agent](https://github.com/earendil-works/pi); older
@badlogic builds may require changes to extension imports and CLI flags.

Start Ollama in another terminal if it is not already running:

```sh
ollama serve
```

Then:

```sh
ollama pull qwen3.5:9b                # skip if already installed
ollama create llm-lang-lab-qwen35-9b -f Modelfile
python3 bench.py doctor
python3 -m unittest discover -s tests -v
python3 bench.py plan                # inspect the 12-trial pilot without inference
python3 bench.py run                 # explicitly launch that pilot
```

Model selection is intentionally modest: the initial machine is an Apple M3 Pro
with 36 GiB unified RAM. The existing model occupies about 6.6 GB on disk.
The smoke test reported about 6 GB loaded, 100% GPU, with a 16,384-token context.
This leaves room for the OS, compiler, and agent. The local alias fixes context
and sampling defaults without copying the model weights. Each batch records the
actual model digest, quantization, parameters, versions, and source hashes;
the upstream model tag itself is mutable.

## What the agent does

A fresh pi process receives one language-neutral task, the target language, and
public examples. Its only tool is `submit_source`, which saves a complete source
file and returns compiler/public-test feedback. It can repair and resubmit up to
four times. The controller stops at the first public pass or submission limit
and freezes the source, including when the model emits multiple tool calls.
Bash, file-reading tools, personal settings, credentials, context
files, MCP, skills, and other extensions are not loaded.

The runner then compiles and checks the last submission against separate
held-out cases, and independently scores the first submission. Hidden feedback
never returns to the agent. All tasks use stdin/stdout and the standard library;
output comparison ignores whitespace differences.

Included task families:

| Task | Exercises |
| --- | --- |
| Interval merging | sorting, boundaries, state updates |
| Word counts | ASCII parsing, case folding, maps/dynamic storage, ordering |
| RPN calculator | token validation, stacks, signed arithmetic, invalid inputs |
| Lower bounds | binary search, duplicates, empty arrays |
| Grid distance | breadth-first search, blocked and unreachable cells |
| Rational sum | exact arithmetic and fraction normalization |
| Edit distance | dynamic programming and empty strings |
| Transaction ledger | nested state, commit, rollback, invalid transitions |
| Dependency order | directed graphs, ordering, duplicates, cycles |
| CSV fields | quoting, escaping, empty fields, significant spaces |

The pilot uses the original three tasks; confirmation uses all ten workloads.

This is a **constrained pi agent benchmark**, not a benchmark of unrestricted
repository editing. Whole-file submission has a token cost; it is deliberate,
equal across languages, and part of the protocol.

## Measuring difficulty

Correctness is the primary result. There is no opaque blended score.

| Metric | Interpretation |
| --- | --- |
| Held-out success rate | Fraction of trials whose final source passes public and hidden cases within budget |
| First-submission successes | First saved source passes public and hidden cases, before repairs |
| Output tokens per verified success | All run output tokens, including failures, divided by successful runs |
| Mean submissions / compile failures | Repair burden |
| PAR-2 seconds | Successful elapsed time; unsuccessful runs cost twice the time budget |
| Input/cache/output tokens | Separate provider-reported usage, retained per run |

If there are no successes, tokens per success is undefined, recorded as null.
Token accounting uses only authoritative pi `message_end` events, avoiding
double counting their copies in turn and session events. Unfinished responses
may have unreported tokens: token totals on interrupted runs are lower bounds.
PAR-2 is a budget-sensitive operational metric, not a measure of reasoning ability.

Defaults: temperature 0.7, top-p 0.8, top-k 20, thinking disabled,
2,048 maximum output tokens per turn, four turns and four submissions.
The calibration pilot has a 120-second per-trial time limit; confirmation has
a generous 600-second safety timeout, which invalidates a confirmation batch
instead of becoming evidence of language difficulty. These limits apply equally
to both languages. Model warmup is outside timing.
Task order is seeded and shuffled. Language order is balanced within each task.
Each task/repeat pair gets a unique seed shared by its two languages; this does
not imply equivalent random draws or bit-for-bit reproducibility on Metal.

## When is the comparison stable?

A small pilot checks the plumbing and failure modes; it cannot establish a winner.
The prepared [study](experiments/README.md) has two separate confirmation batches,
each containing 10 workloads × 20 repetitions × 2 languages (400 trials).
They use disjoint seeds and identical pinned settings.

The prespecified meaningful differences are five percentage points in correctness
and 15% in output tokens per verified success. Correctness takes priority; effort
can decide only after correctness is practically equivalent. Paired Bayesian
credible intervals, prior-sensitivity checks, paired effort bootstraps, and
leave-one-workload-out diagnostics feed the decision. The same conclusion must
hold in both complete batches. A practical tie and an inconclusive result are
both legitimate outcomes; nothing guarantees that 20 repetitions will suffice.

```sh
python3 bench.py plan --config experiments/confirm-a.json
python3 bench.py plan --config experiments/confirm-b.json
# After separately running both complete confirmation batches:
python3 analysis.py runs/BATCH_A runs/BATCH_B
```

Planning and analysis do not run inference. Confirmation is a many-hour experiment,
not the short pilot. The comparison rejects incomplete, duplicated, mixed-protocol,
changed-model, or infrastructure-broken batches. Do not repeatedly sample until
a preferred winner appears.

A result is conditional on model, quantization, task distribution, tools, prompt,
and budget. Training familiarity, standard libraries, compiler diagnostics, and
boilerplate all contribute. For a new language, give equally budgeted language
documentation/examples and separate zero-shot from few-shot experiments.
The next experiments should isolate syntax, type system, diagnostics, and
library design rather than change everything at once. Validate promising
results on a second model before claiming general LLM friendliness.

## Artifacts and reproducibility

Each batch under ignored `runs/` contains:

- Frozen config, paired schedule, environment/model snapshot, source hashes.
- Completion status with final model/source checks.
- Per-trial prompts, isolated pi config, raw JSONL events, stderr.
- Every source revision, public feedback, and first/final hidden evaluation.
- Per-run metrics and `summary.json`.

Recompute an existing summary with:

```sh
python3 bench.py report --batch runs/YOUR_BATCH
```

Export a completed batch into a new portable report directory, then review it
before committing:

```sh
python3 export_report.py runs/YOUR_BATCH
```

The export includes metrics, model metadata, and generated source revisions.
It omits raw traces and compiler diagnostics containing local paths.

Raw traces and local environment details stay local by default. Reviewed,
portable reports can be committed under `reports/`. Do not pool batches with
different harness revisions or configurations.

The model has no general shell tool, but the harness compiles and executes its
code. On macOS the executable gets CPU/output/time limits and a Seatbelt policy
that denies network and user-directory reads outside its work directory.
This is a local research guardrail, not a hardened adversarial sandbox; compilation
is not sandboxed. On other Unix systems only process limits apply. Use a disposable
VM/container before evaluating untrusted models or sources.

## Layout

`bench.py` orchestrates pi and reports; `pi/benchmark.ts` supplies its tool;
`judge.py` owns compilation and testing; `tasks.py` owns specifications and oracles.
`extra_tasks.py` extends the workload suite; `analysis.py` checks replication.
`config.json` and `Modelfile` specify the pilot; `experiments/` freezes confirmation.

References:
[Pi custom models](https://github.com/earendil-works/pi/blob/main/packages/coding-agent/docs/models.md),
[Pi JSON events](https://github.com/earendil-works/pi/blob/main/packages/coding-agent/docs/json.md),
[Ollama local API compatibility](https://docs.ollama.com/api/openai-compatibility),
[Qwen3.5 model family](https://ollama.com/library/qwen3.5).

MIT licensed. Model weights have their own upstream license.
