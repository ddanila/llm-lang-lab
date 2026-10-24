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
- [Original v3 batch, stopped at 320 trials](c-go-checkpointed-v3/20261008T173711298748Z/README.md)
  with its [parser incident](c-go-checkpointed-v3/20261008T173711298748Z/parser-incident.md)
- Amended v3a batches [A](c-go-recovered-v3a/20261009T113047097658Z/README.md)
  and [B](c-go-recovered-v3a/20261009T134522238478Z/README.md), final snapshots at 400 trials
- [Protocol and recovery instructions](../experiments/README.md)

The last study, **c-go-recovered-v3a**, completed on 2026-10-10 under the authorized
[recovery amendment](../experiments/recovery-amendment.md); its final result is in the
[joint report](../reports/c-go-recovered-v3a/README.md). Original v3 checkpoints
remain unchanged; amended checkpoints live under their own study directory.
No study is currently running.
