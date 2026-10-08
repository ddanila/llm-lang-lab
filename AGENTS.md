# Working on llm-lang-lab

Keep model generation inside pi. Python may orchestrate runs and judge programs,
but must not silently replace the model with reference solutions.

Treat success and effort separately. Preserve failed runs, raw event traces,
source revisions, model digests, and all experiment settings. Do not change the
harness or task files during an active batch: judges load them for each submission.

Task or protocol changes require a new batch. Do not pool smoke runs and scored
runs or tune hidden tests to favor observed solutions.

Run python3 -m unittest discover -s tests -v after harness changes.

The user's pi fork is https://github.com/ddanila/pi. If pi itself needs changes,
use a dedicated custom branch in that fork, never its main branch. Prefer the
existing extension interface when it is sufficient.

Do not commit raw runs/, credentials, model weights, executables, or local pi state.
Publish only reviewed portable reports and selected generated sources.
