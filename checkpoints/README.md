# Intermediate study backups

The overnight runner commits and pushes a cumulative snapshot approximately hourly,
at a complete C/Go pair boundary. The first pair gets an early checkpoint to verify
publication. Snapshots contain every completed trial's portable metrics, all source
revisions, configuration, environment fingerprints, and raw-trace hashes. Earlier
snapshots are preserved in Git history. Raw traces, binaries, weights, and local pi
state remain local and are not backed up to GitHub.

These are **progress records, not confirmation results**. An invalid or incomplete
batch cannot establish a language ranking. Failed trials are retained, never
selectively rerun. The final A/B analysis requires two full valid 400-trial batches.

- [Invalid v2 attempt and diagnosis](c-go-controlled-v2/20261008T165022880692Z/diagnosis.md)
- V3 snapshots appear under `c-go-checkpointed-v3/BATCH_ID/` as checkpoints are reached.
- [Protocol and recovery instructions](../experiments/README.md)

The current study is **c-go-recovered-v3a**, using the authorized
[recovery amendment](../experiments/recovery-amendment.md). Original v3 checkpoints
remain unchanged; amended checkpoints live under their own study directory.
