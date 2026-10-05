# CLAUDE.md — Binding Rules for NCDE Poseidon

> 🚩 **CORRECTED 2026-08-06 (operator order): the doc pile is retired as source of truth.**
> `docs/PRODUCTION-PUNCHLIST.md`, `SESSION_HANDOFF.md`, `MEMORY.md`, `commercial.md`, and every
> other plan/audit `.md` that used to live in `docs/` were moved to **`docs/archive-20260806/`**
> on 2026-08-06 because they had gone stale and were actively misleading: `SESSION_HANDOFF.md`
> claimed the 2026-07-21 patch batch was "awaiting deploy" when the live system proved it had
> already been run (self-ship copy mtime, live weather config, live fonts.json all postdated the
> claim); `commercial.md` called things "open" that `PRODUCTION-PUNCHLIST.md` and the live QML
> both confirmed were shipped. **Do not read anything in `docs/archive-20260806/` as current
> truth.** It may be dug up for historical context on request, never trusted by default.
>
> **The live running system is the only source of truth now — for status, not just for code.**
> See `docs/OPEN-ITEMS.md` for the current best-known punch list (short, dated, and explicitly
> "verify against live before trusting" — not a history). See "Session Start" below for how to
> establish state at the start of a task: query the live system directly, don't read a status doc.
>
> **Copilot's binding release instructions:** `.github/copilot-instructions.md` defines the
> live-to-project-to-self-extractor-to-GitHub-pacman-release gate. Never leave an NCDE update live-only.

> **Workspace = `~/my-project/`** (stephen-owned, sudo-free — the organized home for everything):
> - **`docs/`** — this `CLAUDE.md` (the rules) + `OPEN-ITEMS.md` (short live punch list) +
>   working scripts (`check_session.sh`, etc.) + `settings.json`. Everything else historical is in
>   `docs/archive-20260806/` — not canonical, not required reading.
> - **`files/`** — raw materials & build artifacts: the `calamares-ncde/` installer scaffold, the designer
>   kits `compass (N).zip`, `lelan-fixed.zip`, the base Archcraft ISO, helper scripts, and
>   **`ncde-full-patch-20260711.sh`, the actively-maintained deploy mechanism.**
> - `src/`, `.claude/` (hooks + settings).
>
> **⚠️ CORRECTED 2026-07-17 — there is no production source tree anymore.** The dev machine that
> hosted `~/ncde-staging/LaPivot/compass7/` is gone. That path does not exist on this machine or on
> the USB backup — checked both directly, 2026-07-17. The USB's `ncde-staging/` folder is NOT the
> old tree; it's just a backup copy of the same reconstruction workspace described below. **This
> means the whole "production tree" framing below (Hard Constraint 2, the Tree/Live Parity Gate,
> the Build+Deploy `compass7/lelan` build command, rules 9–10) describes a workflow that no longer
> applies.** Do not follow those sections as written — see the corrected model:
>
> - **`/usr/local/bin/LaPivot`** (and the other deployed binaries/QML under `/usr/share/ncde/`) —
>   **the live running system is the actual source of truth now**, not a staged tree.
> - **`~/ncde-wm-rebuild/`** — the reconstruction workspace. Source is recovered by Ghidra-decompiling
>   the live binary (`oracle/LaPivot.oracle`, an md5-verified copy of `/usr/local/bin/LaPivot`), then
>   hand-cleaning individual classes into compile-verified C++. This is **partial and in progress** —
>   most classes (`NCDEWindowManager`, the `LElan` core engine, `ThemeManager`, `NCDEEngine`) are
>   still raw/rough Ghidra output, not clean buildable source. Do not assume a class is safely
>   recompilable just because a `.decompiled.c` file exists for it — check `docs/lapivot-rebuild.md`
>   for what's actually been verified.
> - **`~/my-project/files/ncde-full-patch-20260711.sh`** — the real, actively-maintained deploy
>   mechanism now: every live fix (QML/config text edits, direct binary patches, or a
>   compile-verified reconstructed class) folds into this one script, which the operator runs to
>   apply everything in one pass. This is what "build + deploy" means today, not a `cmake --build`
>   from a production tree.
> - **`~/ncde-ISO/`** — ISO build area, still current, unaffected by the above.
>
> **The operator runs sudo, never the agent** (passwordless retries trip faillock). Read this file,
> then the **Tier-2** doc for your task (§8).

---

## ⛔ STOP. DO NOT PROCEED UNTIL YOU HAVE DONE THIS.

This file must be read **completely** before any other action.  
No exceptions. No "I'll read it as I go." No starting while reading.

**First action of every session — output this block verbatim, filled in:**

```
SESSION START CHECKLIST
=======================
CLAUDE.md read:              YES / [timestamp]
OPEN-ITEMS.md read:          YES / NO
Task this session:           [one line]
Live-system checks run:      [list the actual commands run to establish state, or NONE yet]
Web search available:        YES / NO

Current live status relevant to this task (from commands just run, not from a doc):
[write it here — cite the command + output]

First planned action:
[write it here]

Any privileged commands needed this session:
[list them here, or NONE]

Any procedures I am uncertain about and must search before acting:
[list them here, or NONE]
```

If you have not output this block, **you have not started.** Do not touch any file. Do not run any command. Output the checklist first.

**Establishing state is not optional and does not require the operator's permission. Do not ask. Do not wait. Read CLAUDE.md, then `OPEN-ITEMS.md`, then run the live-system checks relevant to this session's task (systemctl status, file mtimes/hashes, grep the actual QML/config/binary) — not a status doc — then output the checklist. The session does not exist until all of that is done.**

---

## Hard Constraints

1. **Never delete files.** No `rm`, no overwriting-to-empty, no destructive moves. If something seems to need removal, stop and ask.

2. **`~/ncde-staging/` no longer exists (corrected 2026-07-17 — see the banner at the top of this
   file).** The live system is now the workspace for anything already running:
   - `/usr/share/ncde/` — edit QML directly here (or in a staged copy), deploy via `sudo cp`
   - `/usr/local/bin/LaPivot` and other deployed binaries — patched via the reconstruction
     workflow in `~/ncde-wm-rebuild/`, not compiled from a checked-out tree
   - `~/my-project/files/ncde-full-patch-20260711.sh` — every fix folds in here for deploy
   - `~/ncde-ISO/` — ISO build area, still current
   - The old frozen backup root tree is **DEAD** — not workspace, not reference, not anything.

3. **Always read files before editing.** No blind edits. Read current contents first, every time, and show that you read them before making any change.

4. **One change at a time.** Make a single change, show the before/after diff, and **wait for approval** before the next one.

5. **Never run privileged/build commands without explicit per-step approval.** Each of these requires you to write the exact command, explain what it does and why, and wait for the operator to say "run it":
   - `pacman` / `pacman --root`
   - `mksquashfs`
   - `mkarchiso`
   - `grub-install`
   - `arch-chroot`
   - `sgdisk` / `mkfs` / `dd`
   - Any other command that writes outside the workspace or modifies system state
   
   **Do not run these.** Write the command. Explain it. Wait.

6. **Always show actual output.** Show real stdout/stderr and exit code for every command. Never say a command "worked" — show proof. Never say something is "verified" unless you show the command and output that verified it.

---

## Verification Rule (new — critical)

**Never claim something is done. Prove it.**

- ❌ "The fix has been applied." 
- ✅ "I ran `grep -n 'xsession' /usr/local/bin/ncde-x11-session` and got: [output]"

- ❌ "Calamares is installed."
- ✅ "I ran `pacman -Q calamares` and got: [output]"

If you cannot show the proof, say "I have not verified this" — not "it's done."

---

## Build + Deploy Rule (new — critical)

**A source edit is not a fix. Every fix must end with the actual build command (if the file type needs
one) and the actual deploy command — stated explicitly, every time, not left for the operator to infer
or ask for.** This project has repeatedly stalled because agents stopped at "I edited the file" and left
the operator to figure out compiling and shipping it himself — operator called this out directly,
2026-07-03: *"you have to build and give me deploy commands, in fact add that as a rule since you all
never do it."*

For every change, state both of these explicitly, even when the answer is "none":
1. **Build:** for a compiled class, the reconstruction-and-compile-verify workflow in
   `~/ncde-wm-rebuild/` (see `docs/lapivot-rebuild.md` for the current per-class status — there is
   no `cmake --build` from a checked-out production tree anymore, that tree is gone) — OR an explicit
   "no build needed" with the reason (e.g. QML/JSON/shell are loaded from disk as plain text at
   runtime, not compiled/embedded — verify this claim against the actual loading code/docs before
   asserting it, don't assume every file type is safe to skip).
2. **Deploy:** the exact command(s) to get the edited/reconstructed artifact into the path the
   running system actually reads from (`sudo cp` to `/usr/local/bin/LaPivot`, `/usr/share/ncde/`,
   etc.), plus whatever reload step makes it take effect (qmlcache clear, relogin, service restart) —
   AND fold the same fix into `~/my-project/files/ncde-full-patch-20260711.sh` so it isn't lost again.

Never mark something "fixed" on source edit alone — see [[Verification Rule]] above: it isn't done until
built (if applicable), deployed, and proven running.

### Tree/Live Parity Gate — SUPERSEDED (corrected 2026-07-17)

**This section originally (2026-07-03) required treating `~/ncde-staging/LaPivot/` as the always-
up-to-date source of truth and diffing it against live before every session end. That tree does not
exist anymore — checked directly, 2026-07-17, on this machine and the USB backup; see the banner at
the top of this file.** The operator's quoted intent below is preserved as history — the underlying
principle (nothing silently lags behind live) is still binding, it just has no tree to compare
against anymore. Original text, for the record:

> *"the production tree is always up to date.. and the live has to have the [new] code so it can be
> tested.. that was always the way this is supposed to be done.. I don't even know how agents drifted
> from this workflow."*

**Corrected, binding version of the same principle:**
- The **live running system** (`/usr/local/bin/LaPivot`, `/usr/share/ncde/`, etc.) is the only source
  of truth now — there is no separate tree it could lag behind.
- What *can* still drift is `~/my-project/files/ncde-full-patch-20260711.sh` vs. live: before ending
  any session, confirm every fix made this session is folded into that patch script, not just applied
  live by hand. A fix that's live but not in the patch script will be lost the next time the ISO is
  rebuilt from it.
- Log anything intentionally not yet folded into the patch script under an explicit, greppable
  **"AWAITING PATCH-SCRIPT"** heading in `SESSION_HANDOFF.md` — not buried inside prose. The next
  session that touches that doc cluster checks that list first.

---

## Pre-Apply Audit Rule (new — critical)

**Every change runs through the same loop — never apply blind.**

1. **Read** the target file first (Hard Constraint 3).
2. **Audit-as-you-go** — show what was found and exactly what will change.
3. **Final pre-apply audit** — for anything previewable without privilege (`sed` to
   stdout, `diff`, `bash -n`, `--dry-run`), run it read-only and show the *resulting*
   output plus a change-count and anchor-match check, so both sides see it is correct
   BEFORE it is applied. For un-dry-runnable privileged steps (`mksquashfs`, `xorriso`),
   the audit is: the exact command, what each flag does, the expected output/size, and
   the read-only checks to run afterward.
4. **Apply** — the operator runs privileged commands via `! sudo …` (Claude never runs
   sudo); Claude applies only non-privileged, owner-permitted edits.
5. **Post-apply verification** — re-read/grep to prove it landed and nothing else moved.

One change at a time (Hard Constraint 4). The point is to make sure nothing breaks —
this project shipped ~18 broken builds from blind/unverified changes, so verify everything.

---

## No Invention Rule (new — critical)

**Do not invent file contents, package lists, command outputs, or project state.**

If you don't know whether something exists, check. If you cannot check, say so.  
Guessing and presenting it as fact has caused multiple session failures and system damage on this project. It is not acceptable.

---

## Operator Intent Is the Spec — Capture It Continuously (new — critical)

**The operator BUILT NCDE. The original source tree is gone (corrected 2026-07-17 — see §9-10 and
the banner at the top of this file); what's recoverable now comes from decompiling the live binary,
plus whatever the operator remembers and states directly. The desktop runs and the operator knows how
it works regardless of whether the tree survives. In the operator's words: "I am the living source
code… the CMakes of NCDE," and "the tree is the source, the code IS source"** — which, with the tree
now gone, makes the operator's own account of the design *more* load-bearing, not less.
So what the operator says about how the system works is **primary-source specification, not chit-chat —
and it OVERRIDES any note (including this doc) that contradicts him.**

Every agent MUST **continuously document operator intent in real time**: when the operator explains
architecture, naming, behavior, relationships, or history, write it down immediately — update/create the
right project memory AND mirror it into `~/my-project/docs/MEMORY.md` — instead of only acknowledging it in
chat. Distinguish operator intent from binary evidence (`[INF]` vs `[E]`) but record both. This is how the
rebuild stays faithful and how future agents stop re-deriving — or wrongly dismissing — the design.

**Project-memory failsafe:** `~/my-project/docs/MEMORY.md` is a sudo-free backup of the agent auto-memory,
kept with the canonical docs so the memories survive even if the `~/.claude` store is lost.
**Read it first every session** (Tier-1) and **re-mirror it at session end.**
**`~/ncde-docs/MEMORY.md` is a STALE, DRIFTED duplicate — never read or write it.**

---

## Web Search Rule (critical)

**When uncertain about any code, procedure, command syntax, package behavior, or how to edit a file — search the web before proceeding. Do not guess.**

This applies to:
- pacman flags and `--root` install behavior
- mksquashfs / xorriso / osirrox options and syntax
- Calamares module config syntax and behavior
- GRUB / syslinux / El Torito boot authoring
- Any Arch / Archcraft packaging detail
- Any QML, Qt6, or systemd behavior you are not certain of
- Any file format or config syntax you have not read the actual spec for

**The rule:** If you are not certain — not "pretty sure," not "I believe" — search first, then act. Show the source. Do not present a guess as a known fact because it sounds plausible.

Uncertainty phrases that require a web search before proceeding:
- "I think the flag is..."
- "This should work..."
- "Typically this is done by..."
- "I believe the syntax is..."

If you catch yourself about to write any of those, stop and search instead.

---

## Identity / Branding Rule

7. **NCDE hides Arch like macOS hides BSD.** No user-visible text may mention Arch, Linux, pacstrap, chroot, hostname, or partition names. The underlying base is an implementation detail, never surfaced to the user.

---

## Session Start — Establish State From the Live System (rewritten 2026-08-06)

8. **Read `CLAUDE.md` and `OPEN-ITEMS.md` in full. Then establish state for THIS session's work
   area by querying the live system directly — not by reading a status doc.** The old model (read
   a dozen-doc Tier-2 cluster per subsystem) is retired: those docs are what went stale and
   misled sessions (see the banner at the top of this file). The doc pile is archived at
   `docs/archive-20260806/` and may be pulled up for historical *design intent* (operator
   quotes, naming decisions, why something was built a certain way) — never for current status.

   **What "querying the live system" means, per subsystem:**
   - **Binaries:** `/usr/local/bin/LaPivot` and friends — `md5sum` against known `.prebak-*`
     checkpoints to see what's actually deployed, `strings`/`nm` to inspect, `ps`/`systemctl` to
     confirm what's actually running.
   - **QML/config:** `/usr/share/ncde/**/*.qml`, `~/.config/ncde/*.json` — read them directly;
     `.prebak-*` siblings show you the pre-fix state for comparison.
   - **Services:** `systemctl --user list-units` / `systemctl list-units` / `systemctl --failed` /
     `journalctl -u <unit>` — this is the fastest way to find what's actually broken right now
     (this is how the `ncde-fontsync` crash-loop was found on 2026-08-06 — it was in nobody's docs).
   - **The patch script:** `~/my-project/files/ncde-full-patch-20260711.sh` — `grep -n '^step '`
     lists every staged fix by name; that plus live file mtimes tells you what's landed.
   - **Design intent / why something works the way it does:** ask the operator directly (per
     "Operator Intent Is the Spec" below) rather than trusting an old doc's account of it.

   If you genuinely need historical rationale a live check can't answer, it's fine to grep
   `docs/archive-20260806/` for it — just don't trust anything from there about current status,
   and say explicitly that it's an archived/unverified source when you cite it.

---

## Session End — Keep OPEN-ITEMS.md Honest (rewritten 2026-08-06)

**At session end, update `docs/OPEN-ITEMS.md`** — add anything newly discovered broken/open, remove
anything confirmed fixed+deployed+verified this session, and correct anything the session proved
wrong. Keep it short (this is a live punch list, not a narrative log — that's what made the old
docs unmanageable). The agent auto-memory system is where durable project context (operator
decisions, "why" behind design choices, standing feedback) belongs — no more mirrored `MEMORY.md`
doc to keep in sync by hand. Anything that drifted in `docs/archive-20260806/` can stay drifted —
next session's docs match reality — not what a prior note claimed. Documented failure mode: trusting stale docs.
Concrete example (2026-06-22): docs / Fix #4 / scaffold called the stock grub `starfield`
theme "the NCDE theme dir" while the tree correctly uses the compass3 `ncde` theme. Apply
every such edit through the Pre-Apply Audit Rule.

---

## Current State (context — not a rule; corrected 2026-07-17, previously stale since ~2026-07-08
when the dev machine hosting the tree went away and nothing updated this section)

9. **There is no production tree anymore. The live system IS the only copy.** `~/ncde-staging/`
   does not exist — confirmed absent on this machine and on the USB backup, 2026-07-17. The old
   frozen backup root tree is still separately DEAD (operator, 2026-07-05: "the old frozen one is
   dead") — that finding stands, unrelated to this correction. Do not re-litigate either.
   - **Binary:** `/usr/local/bin/LaPivot` — the one production WM, and now the only surviving copy
     of it. No sudo needed to run.
   - **QML:** `/usr/share/ncde/` — this is where LaPivot loads QML from on disk; edit it directly (or
     a staged copy) and deploy via `sudo cp`. There is no separate tree copy to edit first.
   - **The live system's login/branding says "NCDE" but what runs IS LaPivot** — NCDE is the OS name,
     LaPivot is the WM (Identity/Branding rule; implementation details are never surfaced).
   - **Old `ncde-wm`** — legacy backup at `/usr/local/bin/ncde-wm`. Never overwrite (kept as fallback).
   - The ISO/squashfs source is now whatever `~/my-project/files/ncde-full-patch-20260711.sh` applies
     on top of the base ISO — **`ISO-BUILD-PLAN §10 (Build Manifest)`'s file list was derived against
     the now-gone production tree (2026-07-04, session 69) and needs re-verification against the
     current patch-script-based process before being trusted for a rebuild.**

10. **The NCDE source IS lost — correcting the 2026-06-27 correction.** That entry said the C++
    source was safely in the production tree and compiled clean, which was true *then*. It is not
    true now: the tree is gone (see §9), and no copy of it exists anywhere checked (this machine,
    the USB backup, or the old `compass(7).zip`/`compass7-reference` handoff bundle — that bundle's
    own `Lelan.cpp` header literally says "implementation skeleton (new code; original lost)" and is
    ~500 mostly-stubbed lines, not the real ~4,835-line engine).
    - **Current recovery path:** Ghidra-decompiling the live `/usr/local/bin/LaPivot` binary
      (oracle-verified against it), reconstructed class-by-class in `~/ncde-wm-rebuild/`. This is
      **partial** — check `docs/lapivot-rebuild.md` for which classes are actually clean,
      compile-verified reconstructions vs. still-raw Ghidra output before trusting any of it as
      buildable source.
    - **QML** (`usr/share/ncde/*.qml`) is plain text and was never lost — LaPivot loads it from
      `/usr/share/ncde` on disk, unaffected by the C++ source situation.
    - **Safety (still holds):** don't overwrite `/usr/local/bin/ncde-wm` — it's the fallback backup.

---

## Mid-Session Behavior

These apply throughout the session, not just at the start:

- If you are about to run a command not listed in the session-start checklist — **stop and ask first.**
- If you discover something that contradicts what a prior session claimed was "done" — **say so immediately.** Do not quietly work around it.
- If you are uncertain about the state of any file — **read it before assuming.**
- If a step is taking more than one command — **pause and confirm direction before continuing.**

---

## What Has Caused Failures on This Project

Documented, repeated failures — do not repeat them:

- Claiming things were "verified" or "fixed" based on doc contents instead of reading actual files
- Installing packages, building ISOs, or running `grub-install` without per-step approval
- Pushing ISO builds before the tree was confirmed build-ready
- Adding editorial commentary instead of doing the work
- Treating SESSION_HANDOFF.md as ground truth without verifying against the actual tree
- **Fixing one thing and breaking another because the NEW artifact was only verified on the
  dimension just fixed** (session 85: post-install script fixed, then the re-authored ISO
  shipped to the install stick with no Joliet/Rock Ridge — black screen — because only boot
  records and UUID were compared against the original, not the filesystem descriptors).
  A rebuilt artifact is verified by comparing it to the last WORKING artifact on EVERY layer,
  not just the layer that motivated the rebuild.
- **Deflecting when the operator flags a mistake** — softening an admission with "but here's
  why it's different/better this time" is deflection. Own it flat, fix it, record it. The
  operator has had to fight this exact reflex across many agents; do not add to that pile.
- **Asking the operator whether stubs/incomplete architecture are "deliberate design" — he has said
  this plainly, more than once, to multiple agents, and it kept not getting captured: THERE SHOULD BE
  NO STUBS. This was and is supposed to be a complete system. A stub anywhere means a prior agent
  failed to finish the work, never a design choice. Do not re-ask this question. When auditing
  completeness, check implementation depth (TODO comments, header-only classes with no real body,
  placeholder functions) — not just file existence.**

---

*These rules are binding. They are not suggestions. If a rule conflicts with completing a task faster, the rule wins.*
