# CLAUDE.md — Binding Rules for NCDE Poseidon

---

## ⛔ STOP. DO NOT PROCEED UNTIL YOU HAVE DONE THIS.

This file must be read **completely** before any other action.  
No exceptions. No "I'll read it as I go." No starting while reading.

**First action of every session — output this block verbatim, filled in:**

```
SESSION START CHECKLIST
=======================
CLAUDE.md read:              YES / [timestamp]
PROJECT.md read:             YES / NO
NCDE-CALAMARES-PLAN.md read: YES / NO
ISO-BUILD-PLAN.md read:      YES / NO
SESSION_HANDOFF.md read:     YES / NO
calamares-ncde/README.md:    YES / NO
Web search available:        YES / NO

Current status (from SESSION_HANDOFF.md, one line):
[write it here]

First planned action:
[write it here]

Any privileged commands needed this session:
[list them here, or NONE]

Any procedures I am uncertain about and must search before acting:
[list them here, or NONE]
```

If you have not output this block, **you have not started.** Do not touch any file. Do not run any command. Output the checklist first.

**Reading the required docs listed in §Session Start is not optional and does not require the operator's permission. Do not ask. Do not wait. Read CLAUDE.md, then immediately read every doc in the list, then read the files and code those docs reference, then output the checklist. The session does not exist until all of that is done.**

---

## Hard Constraints

1. **Never delete files.** No `rm`, no overwriting-to-empty, no destructive moves. If something seems to need removal, stop and ask.

2. **Never work outside `~/ncde-x11/` and `~/ncde-ISO/`.** These are the entire workspace. Do not read, write, or run commands targeting anything outside them without explicit approval.

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
- ✅ "I ran `grep -n 'xsession' ~/ncde-x11/etc/ncde/xsession` and got: [output]"

- ❌ "Calamares is installed in the tree."
- ✅ "I ran `pacman -Q --root ~/ncde-x11 calamares` and got: [output]"

If you cannot show the proof, say "I have not verified this" — not "it's done."

---

## No Invention Rule (new — critical)

**Do not invent file contents, package lists, command outputs, or project state.**

If you don't know whether something exists, check. If you cannot check, say so.  
Guessing and presenting it as fact has caused multiple session failures and system damage on this project. It is not acceptable.

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

## Session Start — Required Reading

8. **Read all required docs at session start before touching anything.** In full, in this order:
   - `CLAUDE.md` — this file (you are reading it now)
   - `PROJECT.md` — project goal, strategy, branding
   - `NCDE-CALAMARES-PLAN.md` — authoritative master plan
   - `NCDE-INSTALL-PLAN.md` — earlier draft, superseded, kept for context
   - `ISO-BUILD-PLAN.md` — step-by-step plan: rootfs → bootable ISO
   - `SESSION_HANDOFF.md` — latest session snapshot, where things stand
   - `calamares-ncde/README.md` — installer scaffold notes

   When a new `.md` is added to the workspace, add it to this list.

   **Do not summarize. Do not skim. Read them.**

---

## Current State (context — not a rule; updated 2026-06-21)

9. **`~/ncde-x11/` is the consolidated single source of truth.** Every file the running NCDE uses was copied into it from the live system and verified complete. The squashfs is built from this tree. The authoritative file list + exclude rules live in **ISO-BUILD-PLAN §10 (Build Manifest)**. Ownership is frozen (`root:root` system, `1000:1000` `home/live`) — **editing the tree requires sudo** (the operator runs it).

10. **The NCDE source tree is permanently lost** (dev machine wiped by failed builds; system restored from a USB squashfs). The built binaries/QML/configs survived. **We cannot recompile** — so never overwrite or clobber the binaries under `usr/bin`, `usr/local/bin`, or `usr/share/ncde`. There is no way to rebuild them. This makes Rule 1 (never delete/overwrite) safety-critical. Fixes go at the runtime layer only (shell session scripts, QML, JSON).

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

---

*These rules are binding. They are not suggestions. If a rule conflicts with completing a task faster, the rule wins.*
