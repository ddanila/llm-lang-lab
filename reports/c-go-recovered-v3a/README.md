# Amended C/Go recovery study results

Study: `c-go-recovered-v3a`. Status: **inconclusive_under_recovery_amendment**.

Replicated decision: **none; inconclusive**.

Both batches use the documented recovery amendment and unchanged decision rule.
A imports 320 unchanged results and one recovered trial with missing elapsed time
and process return code. B is newly generated. No model answers were replayed.
No failed rows were selectively rerun and the two batches were not pooled.

| Batch | C successes | Go successes | Decision | Wall hours |
| --- | --- | --- | --- | --- |
| [A](../20261009T113047097658Z/README.md) | 90/200 | 94/200 | inconclusive | 20.14 |
| [B](../20261009T134522238478Z/README.md) | 94/200 | 101/200 | inconclusive | 10.63 |

## Replication A

Go-minus-C correctness difference, 95% Bayesian credible intervals:

- Prior 0.5 per paired category: [-6.11, 9.58] percentage points.
- Prior 1.0 per paired category: [-6.07, 9.11] percentage points.

Effort includes generated tokens from unsuccessful trials.
It can determine a winner only after the registered correctness-equivalence
and minimum-success conditions hold. See analysis.json for its bootstrap
interval, prior sensitivity, and leave-one-workload-out diagnostics.

## Replication B

Go-minus-C correctness difference, 95% Bayesian credible intervals:

- Prior 0.5 per paired category: [-4.27, 10.54] percentage points.
- Prior 1.0 per paired category: [-4.54, 10.35] percentage points.

Effort includes generated tokens from unsuccessful trials.
It can determine a winner only after the registered correctness-equivalence
and minimum-success conditions hold. See analysis.json for its bootstrap
interval, prior sensitivity, and leave-one-workload-out diagnostics.

## Audit and scope

Every trial was checked against its schedule, completed-response usage events,
source revisions, and stopping rule. Batch-end source/model fingerprints and
continuation environments and the imported prefix passed amendment validation. Each batch report includes
audit.json and every generated source revision. Raw traces remain local; their
SHA-256 hashes are in the audit records. Exports passed an automated privacy scan.

Conditional on this fixed workload suite, model, prompt, and budgets; not a universal language ranking. Recovery amendment: A includes 320 retained observations and one recovered trial with missing timing. This is not the original unamended frozen confirmation.

These are generation replications on the same ten workloads and local model,
not evidence of transfer to unseen problems or other models. A stable result
is a baseline for follow-up work, not proof that a new language will help.
If inconclusive, retain that conclusion; a larger experiment needs a new plan.

Reproduce the analysis without inference:

```sh
python3 analysis.py reports/20261009T113047097658Z reports/20261009T134522238478Z
```

Wall hours include the original A start and recovery downtime. They are not active inference hours.
