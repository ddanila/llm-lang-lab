# Invalid v2 attempt retained

The first v2 confirmation attempt stopped after 5/400 trials; B never started.
The fifth trial, Go RPN, submitted a program whose second revision contains
`for i := 0; i < n; i++` with an unconditional `i--` inside the loop. It repeatedly
appends to a slice and never terminates for the observed initial state. All three
public examples hit the ten-second execution watchdog on that revision. The old
rule classified any candidate wall timeout as infrastructure failure, invalidating
the whole batch. No provider error was recorded. This is not a confirmation result.

All five completed trial records and all their generated source revisions are
retained here. Full raw traces, diagnostics, and local agent state remain in the
original local run directory. Nothing from this invalid attempt enters v3.

V3 is a fresh preregistered study with new disjoint seeds. A candidate's ten-second
execution limit becomes an explicit resource budget: exceeding it fails that
submission/test. Compiler and agent/provider failures still invalidate the batch.
This operational definition can include effects of machine scheduling; it does
not prove a mathematical property of the language. The hardware and tool versions
remain fixed. Tasks, hidden tests, generation budgets, repetition count, and
statistical decision thresholds are unchanged.
