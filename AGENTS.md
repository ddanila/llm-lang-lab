# Working on llm-lang-lab

Keep model generation inside pi. Python may orchestrate runs and judge programs,
but must not silently replace the model with reference solutions.

Treat success and effort separately. Preserve failed runs, raw event traces,
source revisions, model digests, and all experiment settings. Do not change the
harness or task files during an active batch: judges load them for each submission.

Task or protocol changes require a new batch. Do not pool smoke runs and scored
runs or tune hidden tests to favor observed solutions.

The confirmation study is frozen in experiments/study.json. Keep calibration
results exploratory. Do not change settings, decision thresholds, or analysis
after seeing confirmation results; prepare a new study instead. Never rerun only
failed rows to repair an invalid confirmation batch. Clean sealed checkpoints may
resume the exact remaining schedule after validation. Never resume a running or
invalid batch, discard observed rows, or replay an unfinished trial. Checkpoints
are execution segments, not independent statistical replications.

Run python3 -m unittest discover -s tests -v after harness changes.

The user's pi fork is https://github.com/ddanila/pi. If pi itself needs changes,
use a dedicated custom branch in that fork, never its main branch. Prefer the
existing extension interface when it is sufficient.

Do not commit raw runs/, credentials, model weights, executables, or local pi state.
Publish only reviewed portable reports and selected generated sources. Hourly
checkpoint publication is authorized for the current overnight study; keep raw
traces and local agent state off GitHub. Clearly label interim/invalid evidence.

The user explicitly authorized the JSONL recovery amendment on 2026-10-09:
retain all 320 completed observations, recover trial 321 from existing submissions
with missing timing disclosed, and continue at trial 322. This is implemented as
a new amended batch with a hash-registered imported prefix; the original invalid
batch remains unchanged. Only that registered odd prefix may be sealed/resumed.
Do not generalize this exception to other invalid batches or replay any answers.
Final reports must identify the amendment, original harness provenance and missing
timing; do not describe the result as the original frozen confirmation.
