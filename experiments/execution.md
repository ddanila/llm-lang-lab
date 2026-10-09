# Amended study execution

The user authorized the [JSONL recovery amendment](recovery-amendment.md).
A new batch contains 320 unchanged observations and one recovered failed trial
with missing elapsed time and return code. The original invalid batch stays intact.
The next model call is trial 322, then the remaining A schedule and all 400 B trials.
No prior model answer is regenerated. The original 800-trial schedule is retained.

The imported prefix and original raw evidence are pinned in recovery-prefix.json.
Current code fingerprints are recorded in execution.json and each new environment
snapshot, alongside explicit imported-harness provenance. The original registration
is preserved under history/v3/. Do not modify either registration during execution.

The amended batch starts at its registered recovery checkpoint. A short first
segment finishes trial 322 and publishes that complete pair, then the standard
hourly runner continues. Its process group is recorded in .local/confirmation.pid;
status and log are .local/study-run.json and .local/confirmation.log. The old driver's
state and log are retained under .local/archive/.

```sh
caffeinate -i python3 -u run_study.py --resume --publish --checkpoint-seconds 3600 >> .local/confirmation.log 2>&1
```

Hourly backups, failure stops, privacy checks and final publication still apply.
Keep the laptop powered and open. A future interrupted or invalid batch does not
inherit this recovery exception automatically. Only the registered imported prefix
has special handling. Final output must disclose the amendment and missing timing.
