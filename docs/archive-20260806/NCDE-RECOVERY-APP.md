# NCDE System Restore — "Soundings" — STATUS & REBUILD SPEC (2026-06-22)

NCDE's built-in **time machine**. Always intended to be part of NCDE; the running
binary/backend was lost with the original source FILES. **(Corrected 2026-07-17: those source files
are genuinely lost — no copy exists anywhere, including the `compass7` handoff bundle; see
`CLAUDE.md` §10.)** What's recoverable now comes from Ghidra-decompiling the live binary
(oracle: `~/ncde-wm-rebuild/src/decompiled/`, path corrected — the old `~/ncde-staging/` workspace
it used to live under is gone) and rebuilding class-by-class. The **QML UI survived** (operator-provided,
`compass (5).zip`) and is verified REAL — no hardcoded/demo data; everything comes
from an injected `appBackend`. This doc is the authoritative spec to finish + ship it.

## What it does (operator's description, verbatim intent)
- Makes a **btrfs snapshot of the working system on boot**, keeping **only 7** at a time.
- If something breaks, **Ctrl+Alt+T** behaves like Ctrl+Alt+F2 — switches to a VT — but
  instead of a terminal, **this app appears** (GUI, no shell).
- User picks a snapshot, **enters the admin password**, the system **btrfs-restores** that
  snapshot and **reboots into a fixed system**.
- btrfs only. No rsync. No simulation.

## Status

**Corrected 2026-06-30 night — this table understated actual progress.** `[dead-legacy-tree]/usr/local/bin/
ncde-recovery` is a compiled, non-stripped ELF binary (75632B, dated Jun 23 — later than this table's
last edit), and `ncde-snapshot`/`ncde-rollback` scripts, `etc/pam.d/ncde-restore`, one QML file
(`CelestialBar.qml`), and all three named systemd unit files are already present in the installed
`[dead-legacy-tree]` tree, not just staged in `~/ncde-ISO/ncde-recovery-app/`. **Still genuinely unresolved:**
whether the systemd units are actually *enabled* — no wants-symlinks found for
ncde-recovery-vt/keymap/snapshot, so "files present" is not the same as "wired/enabled." Also not
verified at the time: whether `~/ncde-staging/LaPivot/`'s copy of this matches (it was mirrored there
too, per a `find`, but not diffed against `[dead-legacy-tree]`'s copy). **(Corrected 2026-07-17: that
tree no longer exists, so this open question is moot — there is only the live copy to check now.)**

| Piece | State |
|---|---|
| QML UI (`Main.qml`, `CelestialBar.qml`) | ✅ survived, verified real. Staged in `qml/`, `CelestialBar.qml` also confirmed already in `[dead-legacy-tree]/usr/share/ncde/recovery/` |
| Backend host `appBackend` (C++/Qt) | ✅ compiled binary present in `[dead-legacy-tree]` (`ncde-recovery`, 75632B) — STALE "being rebuilt" below |
| `ncde-snapshot` (boot snapshot + prune to 7 + metadata sidecar) | ✅ present in `[dead-legacy-tree]`, not just draft — STALE below |
| `ncde-rollback` (the actual btrfs restore) | ✅ present in `[dead-legacy-tree]`, not just draft — STALE below |
| systemd units (boot snapshot + recovery VT) | ✅ unit files present in `[dead-legacy-tree]`; ❓ NOT confirmed enabled (no wants-symlinks found) |
| Ctrl+Alt+T → recovery VT binding | ⛔ decision (ncde-wm keybind vs chvt helper) — not independently re-checked this pass |
| btrfs install layout (Calamares) | ⛔ decision — see "Install requirements" — not independently re-checked this pass |

Original (stale) status line kept for history: "Backend host / ncde-snapshot / ncde-rollback / systemd
units" were previously marked ⏳ draft — superseded by the ✅ findings above.

## Backend contract (extracted from Main.qml — match exactly)
Inject as context property **`appBackend`**:
- `listBackups() -> [ {id,date,word,kernel,size,tag,depth}, … ]` — index 0 = synthesized
  "present" `{id:"—",date:"Now",word:"The Present",depth:0,tag:"live"}`; rest read from the real
  btrfs snapshots under `/restore` (+ a `.meta` JSON sidecar each).
- `runRestore(id, password)` — PAM-verify the admin seal, then btrfs-restore, streaming progress.
- `reboot()` — after a successful restore.
- signals: `restoreProgress(real)` `restorePhase(string)` `restoreDone()` `restoreError(string)` `backupsChanged()`.

## Architecture (rebuild)
- **`ncde-recovery`** (new C++/Qt6 binary): QGuiApplication + QQmlApplicationEngine, sets
  `appBackend` = a `RestoreBackend` QObject, loads `Main.qml`. Runs both as a normal desktop app
  AND, via Qt `linuxfb`/`eglfs` platform, **directly on a VT with no X** (so it works when the
  desktop is broken). Source isn't lost — this is new code; Qt6 is in the tree.
- **`RestoreBackend`** = QML bridge only: PAM auth + drives two shell helpers (keeps btrfs logic
  auditable in one place):
  - **`/usr/local/lib/ncde/ncde-snapshot`** — on boot: `btrfs subvolume snapshot -r` the running
    root into `/restore/BAK-<ts>`, write `<id>.meta`, prune to newest 7.
  - **`/usr/local/lib/ncde/ncde-rollback <id>`** — make the chosen RO snapshot the next-boot
    system subvolume (`btrfs subvolume set-default` + reboot); prints `PHASE:`/`PROGRESS:` lines
    the backend turns into signals.

## Install requirements (couples to the ISO build)
- **Root MUST be btrfs.** Calamares decision made this session: `defaultFileSystemType: btrfs` for
  every install, manual partitioning hidden. Subvolumes: `@` (system), `@home`, `/restore` (holds
  the RO snapshots — a **subvolume, not a separate partition**; btrfs snapshots are same-filesystem,
  instant, COW).
- PAM service `ncde-restore` (or reuse `system-login`) for the admin-seal check.

## Install paths (into [dead-legacy-tree], operator sudo)
```
qml/Main.qml, qml/CelestialBar.qml      -> usr/share/ncde/recovery/
build → ncde-recovery binary            -> usr/local/bin/ncde-recovery
system/ncde-snapshot, ncde-rollback     -> usr/local/lib/ncde/        (chmod +x)
system/ncde-snapshot.service            -> usr/lib/systemd/system/    (enable)
system/ncde-recovery-vt.service         -> usr/lib/systemd/system/    (enable; binds the VT)
PAM: etc/pam.d/ncde-restore
```

## Open decisions
1. Recovery VT number (e.g. tty8) + how Ctrl+Alt+T binds to `chvt` (ncde-wm keybinding config vs a
   small always-running X grab helper). Must also work with no X (kernel Ctrl+Alt+F<n> as fallback).
2. Exact btrfs rollback strategy (set-default vs swap-and-reboot) — finalize with the @-subvolume
   layout the installer creates.
3. Build + bundle into THIS ISO, or ship the recovery app as the next milestone after the current
   ISO lands.

═══════════════════════════════════════════════════════════════════════════════
## 2026-06-22 SESSION 2 UPDATE — supersedes the "Status" table and "Open decisions" above

**All open decisions are now RESOLVED and the source-level build is staged** in
`~/ncde-ISO/ncde-recovery-app/` (NOT yet installed into the tree / squashfs).

### Decisions (final)
- **Rollback = swap-@ + set-default.** `ncde-rollback` makes a writable copy of the chosen RO
  snapshot the new `@`, sets it default, exits 0 (backend reboots). The broken `@` is renamed
  `@_old_*` and **deleted on the next boot** by `ncde-snapshot` — the broken state is NOT kept;
  re-restore is possible from the other snapshots.
- **System-only restore.** Subvolumes: `@` (/), `@home`, `@cache`, `@log`, `@restore`. A restore
  swaps `@` only → **/home, logs and caches are preserved** (never rolled back). Set in the staged
  `mount.conf` → install to `/etc/calamares/modules/mount.conf`.
- **7 rolling** boot snapshots, COW, space-pressure valve to a floor of 3. RO snapshots under
  `/restore` named `BAK-NNNN` (monotonic) + a `BAK-NNNN.meta` JSON sidecar.
- **Ctrl+Alt+R = recovery.** Desktop dead → kernel keymap (`Console_8`) switches to the recovery
  VT **tty8** (works with no X). Desktop alive → "System Restore" menu/dock app
  (`ncde-recovery.desktop`, `pkexec`). No sxhkd.
- **"Never see a console."** logind `NAutoVTs=1`; the emergency VT shows a branded **"call support"
  card** (NCDE Support **(217) 219-5415**), never a login. tty1=desktop, tty8=recovery.
- **PAM `ncde-restore`** = verify-secret-only via `system-auth` (modeled on `ncde-lock`).
- GUI runs on the VT with no X via **eglfs** (linuxfb fallback). Backend host = `RestoreBackend`
  (C++/Qt6), drives the two shell helpers, parses `PHASE:`/`PROGRESS:`/`ERROR:` lines into signals.

### Staged files → install targets (operator sudo)
```
src/  (compile first: needs `pacman -S cmake`; Qt6+pam present)
  cmake -S . -B build && cmake --build build  ->  /usr/local/bin/ncde-recovery
qml/Main.qml, qml/CelestialBar.qml            ->  /usr/share/ncde/recovery/
system/ncde-snapshot, ncde-rollback           ->  /usr/local/lib/ncde/            (chmod +x)
system/ncde-support-notice                    ->  /usr/local/lib/ncde/            (chmod +x)
system/ncde-recovery.kmap                     ->  /usr/local/share/ncde/
system/mount.conf                             ->  /etc/calamares/modules/mount.conf
system/ncde-restore                           ->  /etc/pam.d/ncde-restore
system/ncde-console.conf                      ->  /etc/systemd/logind.conf.d/ncde-console.conf
system/ncde-snapshot.service                  ->  /usr/lib/systemd/system/        (enable)
system/ncde-recovery-keymap.service           ->  /usr/lib/systemd/system/        (enable)
system/ncde-recovery.desktop                  ->  /usr/share/applications/
```

### Still TODO (next session)
- `ncde-recovery-vt.service` (DRM/VT handoff, logind seat on tty8) + polkit no-prompt rule for
  `pkexec ncde-recovery` — author + **VM-test** (couples to the binary's eglfs init).
- An icon `ncde-recovery` for the .desktop (reuse an NCDE icon or add one).
- `chrooted_post_install.sh`: enable the units + apply the console policy on the installed system.
- `show.qml`: add a slide teaching **Ctrl+Alt+R**.
- Confirm Calamares creates `@restore` and fstab mounts it; then §B→§E ISO build + VM gate.

(Status table + Open-decisions sections earlier in this file are historical — the above supersedes them.)
