# RELEASE GATE — LaPivot -> L2 -> ISO (operator's rules, restated 2026-10-01)

Coordinator-owned. This file is the gate; no agent may run an install step.
Agents: read this, but do NOT act on stage 2+ on your own. Report instead.

Source: README.md item 4 + operator's restatement 2026-10-01. Both agree.

## The pipeline, in order. Do not reorder, do not skip forward.

1. **BUILD** — all rebuilt LaPivot source compiles and links
   (`bash LaPivot/tests/compile_all.sh` 0 warnings; full link). The source
   must exist and build BEFORE any L2 session is created. Reason: the L2
   session exists to run a *working* binary; creating it earlier ships a
   broken L2 and makes the operator's test meaningless.
2. **STAGE ONLY** — `source-recovery/l2-stage/` holds INSTALL / UNINSTALL /
   PROMOTE-L2 scripts. They are **written, never run** by any agent.
   No installs, no `/usr`, no `~/.config/ncde`, no service restarts, no sudo
   (AGENT-BRIEF.md rule 5). NCDE_POSEIDON is read-only.
3. **OPERATOR INSTALLS L2** — out of band, by the operator, after the build
   links. L2 installs BESIDE the current LaPivot, never over it:
   - `/usr/local/bin/LaPivot-L2` (current `/usr/local/bin/LaPivot` untouched)
   - QML/assets in `/usr/share/ncde-l2/` (current LaPivot keeps `/usr/share/ncde/`)
   - session script `ncde-x11-session-l2`
   - `/usr/share/xsessions/ncde-l2.desktop` with `Name=NCDE L2`
   - ncde-portal already lists it; portal itself is HANDS OFF.
   Rationale (operator 2026-09-30): "a different session in case it crashes".
4. **OPERATOR TESTS L2** — the operator runs it and says whether it works.
   **No agent, and no coordinator, decides this. Nothing is promoted on our
   say-so.**
5. **PROMOTE — only after the operator says it all works.** "make L2 the real
   LaPivot" -> run PROMOTE-L2 (operator-run). Only now does L2 *become*
   LaPivot: `/usr/local/bin/LaPivot-L2` -> `LaPivot`, `/usr/share/ncde-l2` ->
   `/usr/share/ncde`, session -> main session.
   **If the operator has not said it works, this step does not happen. Ever.**
6. **ISO REAUTHOR** — only after step 5. Rebuild/republish the NCDE ISO from
   the promoted LaPivot, then repo publish.

## Reporting rule that gates all of the above
Agent reports feed stages 1-2 only. A report claiming "built / wired / works
/ done" must carry measured evidence (a test run, observed output, numbers) —
AGENT-BRIEF.md rule 2. Parity with the oracle binary is worthless if the
product is wrong. Never round up.

## Notes
- Stage 5 requires the rebuilt LaPivot to have the new Settings storage/idle
  behaviour; the old live LaPivot must stay working throughout stages 2-4 so
  the operator can fall back to it.
- README item 5 places the ORCHIDÉE seal-password work "right after LaPivot is
  finished" (operator's order). Whether that lands before or after the ISO
  reauthor is the operator's call — ask, don't assume.
