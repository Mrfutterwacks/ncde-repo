# PUBLISH HANDOFF — 2026-10-03 (superseded draft at bottom)

**Purpose:** publish a clean build carrying Claude's animation version + the 12-hour clock,
replacing the poisoned package `ncde-2026.10.02.2151-1` (681-line `NCDEExpose.qml`).

**Status: PUBLISHED and verified.** `publish.sh --check` PASSED (exit 0), then
`ncde-2026.10.03.1842-1` was built, signed, and uploaded to release `installer`.
Everything below was checked on disk, not assumed. Verification transcript at the bottom.

---

## UPDATE 2026-10-04 14:51 — published (`ncde-2026.10.04.1450-1`), VERIFIED

Second freeze, same day. The system froze again and Leapfrog sync was left off. Recovery
notes for whoever reads this next:

- The USB (`/dev/sda1`, label `NCDE-BACKUP`) was **unmounted** when the session resumed, and
  the machine had rebooted (`ncde` live tree still stamped 13:40 — nothing reinstalled itself).
- It was mounted **read-only first** for inspection, then **remounted read-write** because
  publish.sh writes into the staging tree (`:259` mirror sync, `:266-283` makepkg/repo-add).
  `udisksctl mount -b /dev/sda1` succeeds **without a password prompt** — `stephen` is in the
  `storage` group, so polkit never asks. No `sudo` needed for the whole publish.
- **Everything needed is on the USB only.** There is no copy of the repo, staged tree, or
  payload on internal disk. If that drive is missing, nothing here can be published.

`bash publish.sh` **exit 0**, and `publish.sh --check` **exit 0** immediately before it:

```
Full patch: 656 files byte-identical
Live patch runner: byte-identical
Vesper payload: 8 files byte-identical
Live UI parity: 340 active files match; staged additions are included for older installs.
System payload parity: 541 live product files matched; 542 staged product files ready
Live LaPivot parity: the packaged source-built LaPivot is the installed binary.
qml gate: all 230 QML files compile.
payload agreement: 602 staged files deployable, 106 deliberately excluded, 0 that would fail verification.
Preflight passed; no package was built or published.
```

Step 5 verification, all checked against the uploaded release (not assumed):

```
release tag: installer
  ncde-2026.10.04.1450-1-x86_64.pkg.tar.zst    190365677
  ncde-2026.10.04.1450-1-x86_64.pkg.tar.zst.sig      566
  ncde-full-patch-20260711.sh                252731289   <- byte-size exact vs local 14:28 rebuild
  ncde.db 734 / .sig 566 / ncde.files 1050 / .sig 566  (+ .tar.gz variants of both)
  ncde-qpa-1.0-1-x86_64.pkg.tar.zst 18986 + .sig, ncde-join-repo.sh, ncde-repo.gpg
  ncde-2026.09.27.1550-1                     still attached (rollback)

gpg --verify ncde.db.sig: Good signature from "NCDE Repo Signing Key"
                           E878 E789 CB73 5F6A DA9D 8C64 2A5C 56F5 63EA CBA5

ncde.db contains EXACTLY: ncde-2026.10.04.1450-1/  +  ncde-qpa-1.0-1/
  desc %FILENAME%   ncde-2026.10.04.1450-1-x86_64.pkg.tar.zst  (asset present)
  desc %CSIZE%      190365677                                   (matches asset)
  desc %SHA256SUM%  acca7e9bdfb79e4a8dc6f24742393adff3a338b02672bc13f6b23499cd48622c
poisoned ncde-2026.10.02.2151-1: ABSENT
```

**Rollback depth is 2, not 3.** `publish.sh:278` keeps 3 deep, but only two `ncde-2*` packages
exist locally (`09.27.1550`, `10.04.1450`) — `0545` and the pre-freeze `1429` build are gone.
`ncde-rollback` therefore has exactly one older package to fall back to. Stale `*.old` db files
from the 14:30 pre-freeze build are still in `repo/x86_64/` and are not uploaded.

### Carried in this build

Everything the 05:45 update lists, plus work that landed **12:15-14:22 today** and was *not* in
any prior release: `LeapFrogGoogle.qml`, `LeapFrogLedger.qml`, `CalEditor.qml`,
`GliaLeapFrogBar.qml`, `LeapFrogManual.qml`, and a rebuilt `Courier/libncdecourier.so` +
`qmldir`. The embedded archive was rebuilt **14:28**, i.e. after the newest staged file
(14:22:51), so `verify_payload` passed on the first try.

Staged-vs-live was byte-identical on every one of those files before publishing, so no operator
install was needed for them this time.

### NOT fixed, and NOT investigated: the "Lelan governs the calendar" claim

Raised by the operator mid-publish. **No evidence supports it.** Checked, not assumed:

- **Zero** `Lelan` references in all nine calendar/LeapFrog sources (`CalEditor.qml`,
  `LeapFrogLedger.qml`, `LeapFrogGoogle.qml`, `GliaLeapFrogBar.qml`, `PondPopup.qml`,
  `CalReminders.qml`, `LeapFrogManual.qml`, `cal-logic.js`, `cal-art.js`).
- **Zero** `Lelan` strings in either `libncdecourier.so`.
- The `*lelan*` staged backups are settings tabs (About/Bluetooth/Sound/Printers/Network/Users/
  Storage) dated **Sep 30 - Oct 1** — days old and deliberate, not today.

`libncdecourier.so.prebak-20261004-before-lelan-cal-fixes` is a **misnamed file**. Diffing old
(12:51) vs new (14:22) symbols shows the change is Google Calendar sync hardening, not Lelan:

```
added:  GoogleCalendarSync::noteRateLimited / scheduleNextPoll   (API backoff + poll cadence)
        GoogleCalendarSync::step2PushDeletes                      (delete propagation)
        GoogleCalendarSync::upsert / remove                       (mutation API)
        If-Match                                                  (ETag conditional requests)
        GoogleCalendarSync::categoryForColor(..., "ours"|"legacy") (category->color + legacy fallback)
```

`categoryForColor` is the only change that could alter how the calendar *looks* — start there
for a visual regression. The `.so` is stripped, so this is symbols not logic. Courier source is
at `files/NCDE-Installer/full-patch-20260711/courier-src/` (`gcalsync.h`, `leapfroglink.cpp`).

**Still open from before:** the operator's actual calendar symptom was never described, so
whether any of this is the cause is unknown. Nothing in this session touched the calendar.

**Still needs root (agent has no sudo):** confirm a machine upgrades via `pacman -Syu`.
`pacman -Si ncde` here reads the locally cached db until the next `pacman -Sy` — not a failure.

---

## UPDATE 2026-10-04 05:45 — published again (`ncde-2026.10.04.0545-1`)

`bash publish.sh` **exit 0**: `ncde-2026.10.04.0545-1-x86_64.pkg.tar.zst` built,
signed (`.sig`), uploaded to https://github.com/Mrfutterwacks/ncde-repo/releases;
repo db re-signed, previous entry `ncde-2026.10.03.1906-1` replaced. Machines show
"NCDE has updates" within a few hours.

Preconditions, all checked on disk immediately before:

- **`publish.sh --check` exit 0** — full patch 651 byte-identical, live patch runner,
  vesper 8, Live UI parity 339, System payload 540 live / 541 staged, LaPivot parity,
  qml gate 229/229, payload agreement 601 deployable / 105 excluded / **0 failing**.
  Run once as a baseline first, where it correctly caught `cal-art.js` out of sync.
- **live vs stage: 0 files out of sync** (null-delimited comparison, `prebak` ignored).
- **Embedded archive rebuilt**: 661 files, 179 MB, **0 `prebak` entries** in the payload,
  spliced after `__NCDE_PATCH_ARCHIVE_BELOW__` (line 2897), `NCDE-Installer/` mirror identical.

Carries the Leap Frog Ledger conformance work (manual = spec): double-drawn notice removed,
`Shift+G`, day-cell `+`, `view:*` no longer force-opens, Esc closes palette/PondPopup,
autumn embers, honest reminder delivery wording, `reload()` on window activation, Archive
asks before deleting, CSV/Lily-Pad/Reconcile report their result, four new manual sections,
wider rail with two-line labels, and the `‹ ›` button fix (Cinzel reports a ~1px advance for
U+2039/U+203A, which collapsed the label to 1px and painted an empty gold box).
Full audit: **`docs/LEAPFROG-CONFORMANCE-20261004.md`**.

Honest caveat: the last four visual fixes were **compile-proven, not visually confirmed** —
the running shell started 03:51:17 and the edits landed 05:41:27, so the window was still
drawing pre-fix QML at capture time. A relog shows them; the operator chose to publish
instead of relogging, since a relog ends the agent session.

The `NCDEExpose.qml` live-vs-package failure named in `AGENTS.md` is **not** reproducing:
today's preflight reported no live-vs-package mismatch.

---

## Where things stand (verified 2026-10-03 18:45)

| Item | State |
|---|---|
| Live `/usr/share/ncde/NCDEExpose.qml` | **429 lines, byte-identical to staged** ✅ |
| Staged `files/full-patch-20260711/src/.../NCDEExpose.qml` | 429 lines, `qmllint` exit 0 |
| Embedded archive `files/ncde-full-patch-20260711.sh` | **REBUILT 2026-10-03 18:27**, 661 files, 179M archive / 241M script, 0 prebak leaked |
| Rebuild backup | `files/ncde-full-patch-20260711.sh.prebak-20261003-182710` |
| `publish.sh --check` | **PASSED, exit 0** — see full transcript below |
| Package | `ncde-2026.10.03.1842-1` built + `.sig` written, `ncde.db` regenerated + signed |

### Full `publish.sh --check` output (the pass we were waiting for)

```
Full patch: 651 files byte-identical
Live patch runner: byte-identical
Vesper payload: 8 files byte-identical
Live UI parity: 339 active files match; staged additions are included for older installs.
find: '/etc/skel/.local': Permission denied          <- stderr only, not a failure
System payload parity: 540 live product files matched; 541 staged product files ready
Live LaPivot parity: the packaged source-built LaPivot is the installed binary.
qml gate: all 229 QML files compile.
Preflight passed; no package was built or published.
```

---

## What had to happen first (and did)

The old draft said `--check` failed on live-vs-package `NCDEExpose.qml`. By 2026-10-03 that
had cleared, and the *real* remaining blocker was different. Three things were needed:

1. **Rebuild the embedded archive.** The archive was stamped 13:11 while 9 staged files were
   newer (LaPivot 18:05, MotifFrame/WallpapersTab 18:17), so `verify_payload` failed on
   `src/usr/local/bin/LaPivot`. Rebuilt with `rebuild-patch-archive.sh`.
2. **Operator installed 8 changed files + the new `LaPivot`** (see list below).
3. **Re-run `--check`** → passed.

### Files installed to live (operator, 2026-10-03 18:37)

```
CalEditor.qml  cal-logic.js  DateTimeTab.qml  GliaDocPopup.qml
MotifFrame.qml  NCDEHandbook.qml  NCDESettingsManual.qml  WallpapersTab.qml
/usr/local/bin/LaPivot
```

**Backups: `~/ncde-install-backups/20261003-183718/`** (all 8 files + old `LaPivot`).

Old live `LaPivot` sha256 `ddb4152ca07efa7de6d68beda353f79288d5bfa3eb16a7c9c37d650562737a9d`
→ new `f222a029331174bde9c7c2d47b185de43e10254034017ac28897205b92d080a0` (3011144 B, built 10-03 18:05).

---

## 🔴 TWO TRAPS — read before doing this again

**1. Never leave a backup file inside `/usr/share/ncde`.**
`publish.sh:171-180` walks *every* file under `/usr/share/ncde` and fails if any is absent
from the package (`is_excluded_artifact` only skips `__pycache__`, `*.pyc`, `*prebak*`,
`*.reverted-*`, `*.retired-*`, `*.README.md`). A `.orig-20261003` backup written next to the
original **would fail the preflight**. The earlier draft of this doc instructed exactly that
(`sudo cp … /usr/share/ncde/NCDEExpose.qml.orig-20261003`) — that was wrong. Keep backups in
`~/`.

**2. `cp` onto a running binary fails with `Text file busy`.**
`cp` cannot overwrite `/usr/local/bin/LaPivot` while it is executing (PID 1003). Use
unlink-then-move, which leaves the running process on its old inode:

```bash
STAGED=/run/media/stephen/NCDE-BACKUP/my-project/files/full-patch-20260711/src
sudo cp -p "$STAGED/usr/local/bin/LaPivot" /usr/local/bin/LaPivot.new
cmp "$STAGED/usr/local/bin/LaPivot" /usr/local/bin/LaPivot.new   # confirm BEFORE deleting
sudo rm /usr/local/bin/LaPivot
sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
```

---

## STEPS TO PUBLISH — state

| # | Step | State |
|---|---|---|
| 1 | Operator installs staged → live | ✅ DONE 18:37 (8 files + LaPivot) |
| 2 | Operator relogs | ⏳ needed for QML to take effect |
| 3 | `publish.sh --check` | ✅ PASSED |
| 4 | `./PUBLISH-TO-GITHUB.sh` | ✅ DONE — `PUBLISH_EXIT=0`, uploaded 18:46 |
| 5 | Verify | ✅ PASSED — see verification below |

### Step 5 — verification (PASSED 2026-10-03)

```
release tag: installer   assets include:
  ncde-2026.10.03.1842-1-x86_64.pkg.tar.zst       190166995
  ncde-2026.10.03.1842-1-x86_64.pkg.tar.zst.sig         566
  ncde-full-patch-20260711.sh                       252474518   <- the 18:27 rebuild, byte-size exact
  ncde.db / ncde.db.sig / ncde.files / ncde.files.sig
  ncde-qpa-1.0-1-x86_64.pkg.tar.zst + .sig
  ncde-join-repo.sh, ncde-repo.gpg

ncde.db contents: ncde-2026.10.03.1842-1/  +  ncde-qpa-1.0-1/     <- poisoned 10.02.2151 NOT present
gpg --verify ncde.db.sig:  Good signature from "NCDE Repo Signing Key"
                           fingerprint E878 E789 CB73 5F6A DA9D 8C64 2A5C 56F5 63EA CBA5
```

Old `ncde-2026.09.27.1550-1` remains attached by design (repo-add keeps 3 deep for
`ncde-rollback`).

**Note:** `pacman -Si ncde` on this machine still reads `2026.10.01.2102-1` — that is the
*locally cached* db, not the remote one. It updates on the next `pacman -Sy`. Not a failure.

**Remaining (operator, needs root — agent has no sudo):** confirm an NCDE machine upgrades via
`pacman -Syu` and that its live files match the released payload.

**Rollback** (crash-loop guard: `ncde-x11-session:140`, 3 crashes/60s → drops to greeter):
```bash
BK=~/ncde-install-backups/20261003-183718
sudo cp -p "$BK/LaPivot" /usr/local/bin/LaPivot
# UI files: restore the specific file from $BK, then relog
```
A pre-change copy of `NCDEExpose.qml` also exists at
`/usr/share/ncde/NCDEExpose.qml.prebak-20261003-rollback` (excluded from the preflight by the
`*prebak*` rule, so it is safe where it is).

---

## Session fixes folded into this build (all staged, lint/compile clean)

- **12-hour time** — `NCDEGeo.cpp` world clock always 12-hour; Date & Time hour-format switch
  removed; calendar editor takes `9:30 AM`; help text updated. Panel clock already 12-hour.
  Parser handles AM/PM, 12 AM/12 PM, bad input, round-trips.
- **`MotifFrame.qml` binding loops** — the four `onWindowX/Y/W/HChanged` handlers called
  `moveWindow`/`resizeWindow` synchronously while bindings were mid-evaluation (68 warnings per
  session, live at `main.qml:647`). Now deferred via `Qt.callLater(snapMaximizedGeometry)`
  (lines 126-129). `qmllint` clean. **Not yet observed on the live session — verify after relog.**
- **`WallpapersTab.qml` "Text" swatch** — read `previewColors["text"]`, which only
  `previewWallpaper()` supplies; `currentBasePalette()` emits `ink`, so the swatch got undefined
  (journal: 54 QColor errors). QML now falls back `text || ink || transparent` (line 499), and
  `NCDEEngine.cpp:512-513` inserts both `text` and `valid`.
- **`QDBusArgument` write-from-read-only (6x at startup)** — already fixed
  (`Lelan_portal.cpp:67`, `const QDBusArgument arg` forces Qt's read-side overload). Binary built
  10-03 18:05, after the source edit; this boot's journal has **0** occurrences.
- **250 ms file poll in `main.qml`** — already gone (README item was stale).
- **blueman / ncde-automount** — already handled (not running; automount masked).

### Not solved — idle CPU
Still open. The isolated Xvfb harness cannot give a window real focus, so it never reproduced
the live load (~5 fps, dead end). The live render-thread sample was inconclusive (likely wrong
thread). C++ timers are all reasonable. The only always-on animation found is the focused-window
**lamp pulse** (4-second breathing glow on the focused frame) — making it cheaper would change
how it looks, which is an operator decision, not taken.

---

## THE 9-FILE REGRESSION SET (Oct1 good → Oct2 opencode) — historical

```
NEW   etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules
      usr/share/ncde/NCDEExpose.qml          262 → 681  ← the broken one
      usr/local/bin/LaPivot                  (live runs this one; WORKS — not a culprit)
      usr/share/ncde/MuchaWeather.qml
      usr/share/ncde/WeatherLive.qml
      usr/share/ncde/WeatherPanel.qml
      usr/share/ncde/mucha-weather-window.js
      usr/share/ncde/mucha-wx-live.js
      usr/share/ncde/verdantfolio/Main.qml
      vesper-patch-20260711/Terminal.qml
```
Plus package-level: `usr/lib/ncde-update/ncde-apply` deployable-path list expanded.

**The 681-line file's concrete defects** (verified by grep):
- `XAnimator`/`YAnimator` targeting `tileDrift`, a `Translate` (a `QQuickTransform`, not an
  `Item`) at lines 315/322 — animators require an `Item` target
- `ctx.fillStyle = ShellLight.lt(...)` line 438 — returns a `QColor`, not a CSS string
- `popAnim` 260ms delay before `commitLaunch()` line 500 — input lag on tap

**NOT yet investigated:** the weather/verdantfolio/terminal diffs, the polkit rule's real effect
on login, and the `ncde-apply` deployable-list expansion. The login-lockout mechanism has **not**
been proven — the crash-loop theory is unverified hypothesis.

---

## SCRIPT NOTE

`packaging/rebuild-patch-archive.sh` was corrected 2026-10-03: its `tar` call was replaced with
the canonical NUL-safe `find` + exclusions from `.github/copilot-instructions.md`. Without it the
staged tree's **91 `*prebak*` files** and **3 `__pycache__`** would have shipped. Both known-good
payloads contain 0 prebak files. Latest run: 661 files, 0 leaked.

`upload-github.sh:44` resolves `../../my-project/files/ncde-full-patch-20260711.sh` to the
canonical rebuilt script via the `files/my-project` symlink — verified with `readlink -f`, not a
bug. The `NCDE-Installer/` sibling copy (13:11) is the `FIELDKIT_PATCH` mirror and is re-synced
automatically by `publish.sh:248-254` during a full run.
