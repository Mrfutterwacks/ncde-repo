# NCDE Open Items — live punch list

Short, dated, and disposable by design. This is not history — history caused the 2026-08-06
doc purge (see `CLAUDE.md` banner). Every item here should be re-verified against the live
system before being trusted if this file is more than a session or two old. Remove items once
confirmed fixed+deployed+verified; don't just annotate them "done" and let them accumulate.

Last verified: 2026-10-03, direct on the live `ncde` machine.

## 2026-10-03 — PUBLISH: `--check` PASSED, `ncde-2026.10.03.1842-1` built + upload launched

Replaces the poisoned `ncde-2026.10.02.2151-1` (681-line `NCDEExpose.qml`) with a clean build
carrying Claude's animations + the 12-hour clock. Full detail in
`docs/PUBLISH-HANDOFF-20261003.md` — read that before touching any of this.

- **`publish.sh --check` PASSED (exit 0)** after two fixes: (a) the embedded archive was stale
  (stamped 13:11 vs 9 newer staged files) → rebuilt 18:27, 661 files, 0 prebak leaked, backup
  `files/ncde-full-patch-20260711.sh.prebak-20261003-182710`; (b) operator installed 8 changed
  files + the new `LaPivot` to live. Verbatim pass: 651 / byte-identical / 8 · Live UI parity
  339 · System payload parity 540 live / 541 staged · LaPivot parity · qml gate 229 compile.
- **Installed by operator 18:37**, backups in `~/ncde-install-backups/20261003-183718/`:
  `CalEditor.qml`, `cal-logic.js`, `DateTimeTab.qml`, `GliaDocPopup.qml`, `MotifFrame.qml`,
  `NCDEHandbook.qml`, `NCDESettingsManual.qml`, `WallpapersTab.qml`, `/usr/local/bin/LaPivot`.
- **PUBLISHED + VERIFIED ✅** — `PUBLISH-TO-GITHUB.sh` exited 0, uploaded 18:46. Release
  `installer` now carries `ncde-2026.10.03.1842-1-x86_64.pkg.tar.zst` (190166995 B) + `.sig`,
  `ncde.db`/`ncde.files` + sigs, and `ncde-full-patch-20260711.sh` at **252474518 B — byte-size
  identical to the 18:27 rebuild**, so the release ships the rebuilt archive, not the stale one.
  `ncde.db` extracted from the release contains **only** `ncde-2026.10.03.1842-1` +
  `ncde-qpa-1.0-1` — the poisoned `2026.10.02.2151` is **not** in the db. `gpg --verify
  ncde.db.sig` → Good signature, fingerprint `E878…63EA CBA5`.
  Old `ncde-2026.09.27.1550-1` stays attached on purpose (rollback depth 3).
  `pacman -Si ncde` still reads `2026.10.01.2102-1` **locally** — that is the cached db, it moves
  on the next `pacman -Sy`. Not a failure.
- **Still needs root (agent has none):** confirm an NCDE machine upgrades via `pacman -Syu` and
  its live files match the released payload. **Operator also still needs to relog** for the QML
  changes to load — test with F1 / Super-tap.

> 🔴 **Two traps, both already bitten once today:**
> 1. **Never leave a backup inside `/usr/share/ncde`** — `publish.sh:171-180` requires every
>    file there to exist in the package, and `.orig-*` is *not* in `is_excluded_artifact`
>    (only `*prebak*`, `*.pyc`, `__pycache__`, `*.reverted-*`, `*.retired-*`, `*.README.md`
>    are). The first draft of the publish handoff instructed writing
>    `NCDEExpose.qml.orig-20261003` next to the original — that would have failed the
>    preflight. Backups go in `~/`.
> 2. **`cp` onto a running binary fails `Text file busy`** — unlink-then-`mv` instead; the
>    running process keeps its old inode. See the handoff for the exact command.

### 🔴 `ncde-apply` false "FAILED verification" on every machine — FIXED, republished

The first post-publish `pacman -Syu` failed in the **background** apply step, not in pacman:

```
Payload verification failed: unapproved staged product path:
  etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules
```
→ `ncde-apply.service` exit 1, desktop notification *"NCDE 2026.10.03.1842-1 … FAILED verification"*.

- **No file damage.** 0 missing/different deployed files; 1 unapproved path. The patch's own gate
  (`ncde-full-patch-20260711.sh:449`, `is_deployable_payload "$rel" || continue`) has **no
  `etc/polkit-1/` entry**, so the rule was **never deployed to any machine** — by design.
- **Root cause: 7 hand-maintained copies of `is_deployable_payload`, nothing compares them.**
  Only `publish.sh` got the polkit entry when the rule was added 10-02. That one is *required* —
  `publish.sh:187` fails on any staged file it doesn't approve. `ncde-apply`'s copy must not try
  to verify it live, because it is never deployed.
- **The rule is live-ISO-only, and that is documented in the build itself:**
  `files/iso/step21-rootless-refresh.sh` strips it from installed systems — *"or an installed
  system silently inherits it and never asks for a password at all."* It stays in
  `files/full-patch-20260711/src` only as the ISO's source (step20/step21 read that tree).
- **Fix:** added it to `ncde-apply`'s *exclusion* case (alongside `90-ncde-static.conf`,
  `hummingbird-google-client.json`) with a comment. `packaging/ncde/ncde-apply` is the
  authoritative file (a PKGBUILD `source=()`); `packaging/ncde/pkg/…` is makepkg output and must
  not be edited.
- **Verified before publishing,** not assumed: replayed the edited file's real approval function +
  real exclusion case over the payload → `checked=601, excluded=105, unapproved=0`. 601 − 4
  (LaPivot + the 3 service/timer files skipped before compare) = **597**, exactly what the real
  run counted — so the harness reproduces ncde-apply's logic faithfully.
- **Why `--check` cannot catch this class:** it validates against `publish.sh`'s own list and
  never exercises the receiving machine's verifier. The defect only fires at runtime on the
  target, in a background unit, surfaced solely as a notification.

- **End-to-end verified on the live machine, not just in a harness.** After `pacman -Syu` pulled
  `ncde-2026.10.03.1906-1` (fix present: `grep -c 49-nopasswd /usr/lib/ncde-update/ncde-apply` → 2),
  `ncde-apply.service` finished **`inactive success 0`** — previously `failed exit-code 1` — and the
  log reads **`Payload verification passed: 597 NCDE system files and 27 per-user wallpaper files
  match the package.`** Same 597 as the failing run, so nothing was skipped; only the false
  failure is gone. `last-apply-summary`: `NCDE 2026.10.03.1906-1: SUCCESS`.
- **Gotcha that cost a false alarm mid-run:** `apply-latest.log` only re-points when a run
  *completes*, so while a run is in progress it still shows the previous run's result. During the
  1906 apply, grepping `apply-latest.log` returned the 1842 run's failure. Read
  `ls -t /var/log/ncde/apply-*.log | head -1`, and check `systemctl is-active ncde-apply.service`
  is not still `activating`, before trusting it.

**Guard: written and wired (was "not written").**
- `packaging/check-payload-agreement.sh` encodes the invariant: *any staged file the patch does
  not deploy must be in ncde-apply's exclusion list.* It reads both files' **real** code (the
  approval function and the exclusion `case`), not a copy.
- Proven in both directions: against the live pre-fix `ncde-apply` → **`exit=1`**, naming
  `etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules`; against the fixed copy → `exit=0`.
- Wired into `publish.sh` right after `qml-compile-gate`, so it runs in `--check` too. Current
  preflight output ends:
  `payload agreement: 601 staged files deployable, 105 deliberately excluded, 0 that would fail verification.`
- Remaining exposure: the other **6 copies** of `is_deployable_payload` are still hand-maintained
  and unenforced — the guard only reconciles the patch gate against `ncde-apply`.

**Still open from this session:**
- **Idle CPU is unsolved.** The Xvfb harness cannot give a window real focus, so it never
  reproduced the live load (steady ~5 fps — dead end); the live render-thread sample was
  inconclusive. C++ timers are all reasonable. Only always-on animation found is the
  focused-window **lamp pulse** (4 s breathing glow). Cheaper ⇒ different look ⇒ **operator
  decision, not taken.**
- **`MotifFrame` binding-loop fix not yet observed live** — written and lint-clean, but the
  warning only appeared on the live session (68/session at `main.qml:647`). Confirm it's gone
  after the relog.

## 2026-10-02 — ISO REPACK: two blockers FIXED, VERIFIED, WRITTEN TO THE STICK ✅

Operator's report on the re-authored ISO: *"the wallpaper is black and no calamares starts"* (boot from
the NCDE_POSEIDON stick on a laptop). Both root-caused, both fixed, both proven on the real medium.

**1. Calamares never appeared — NOT an autostart bug.** `ncde-x11-session` fired `launch.sh`
correctly (block byte-identical to the working July image), and `pkexec` authenticated correctly
(journal: `Executing command [USER=root] [COMMAND=/usr/bin/calamares -d]`). `calamares` **died on
`exit=127`**:

    /usr/bin/calamares: error while loading shared libraries: libKF6Crash.so.6 … exit=127

Real cause, found by resolving deps against the image's own lib dirs
(`LD_LIBRARY_PATH=$A/usr/lib:$A/lib ldd $A/usr/bin/calamares | grep "not found"`):
**`libcalamares.so.3.4` requests the exact filename `libboost_python314.so.1.91.0`** (`readelf -d`;
note `/usr/bin/calamares` itself has no boost in `NEEDED` — the dep is transitive via its own engine
lib). The 09-29 `pacman -Su` replaced Boost 1.91.0 → 1.92.0; because `/usr/bin/calamares` is a
**vendored binary owned by no package** (`ls $A/var/lib/pacman/local | grep -ci calamares` → 0, and
it is in no repo — `extra.db` grep → 0), the upgrade bumped the libraries and walked straight past
the binary. ELF resolves `NEEDED` by literal filename with no version negotiation, so the 1.92.0
file cannot satisfy a request for the 1.91.0 name.

* **Fix:** ship the three libraries July had, recovered from `b21/old.sfs` (no build, no repo, no
  sudo): `libboost_python314.so.1.91.0` (259688), `libboost_container.so.1.91.0` (67656),
  `libboost_graph.so.1.91.0` (383616). Each verified against July's own `unsquashfs -lln` listing by
  size **and** mtime. `1.92.0` stays for everything else. `ldd` → **93/93 resolve**.
* **Added to** `files/iso/step21-overrides.py` as a new step 2b, which refuses to ship any `1.91.0`
  file that does not match July's recorded size+mtime.
* **Known limitation (real):** there is **no upgrade path for `/usr/bin/calamares`** — it is in no
  repo and no newer copy exists on this machine or the USB. Any future Calamares change must be
  built from source. Its May-11 binary is currently the only one that has ever worked here.

**2. Black wallpaper — dev-machine path in a shipped config.** `etc/skel/.config/ncde/wallpaper.conf`
and `home/live/.config/ncde/wallpaper.conf` both contained `/home/stephen/Pictures/wallpapers/owl.png`
— the operator's **dev** account, which does not exist on the ISO, so LaPivot resolved nothing and
painted black. July's own `home/live` copy pointed at `/home/live/…`; the 09-29 rebuild overwrote it
with the skel value.

* **Fix:** `home/live/.config/ncde/wallpaper.conf` → `/home/live/Pictures/wallpapers/owl.png`,
  byte-identical to July's (`cmp` clean, no trailing newline). Source of truth: `b21/home-live-wallpaper.conf`.
* `etc/skel` deliberately still ships its own copy (as July did) — `chrooted_post_install.sh`
  rewrites it to `/home/${new_user}/…` on install anyway.
* `files/iso/step21-overrides.py` no longer mirrors the skel wallpaper onto `home/live`.

**Also fixed in passing:** `usr/share/ncde/wallpapers/owl.png` was in the old `pseudo.txt` pointing at
a source that exists nowhere (not on the USB, not in the image tree) — a stale entry that would have
shipped a broken reference. It now falls out of the plan naturally.

**Deliberately NOT changed** (operator decision): the 121 MB wallpaper library (`NCDE-15…30`,
`Owls-01…10`, "ChatGPT Image Sep 23", `owl.png`) in `etc/skel` + `home/live`, and the operator's
`.zshrc` / `.screenrc` in skel — *"the wallpapers from this machine are supposed to be there."* Do
not "clean these up" in a later session.

**Gate result — every stage passed:** `squash` 5.3G (353 pseudo defs) → `verify-sfs` **VERIFY
PASSED** (368944 image entries, exactly +3 vs the broken 368941) → `boot` (ESP 334 MiB, kernel
7.2.7-zen1-1-zen) → `iso` (volume descriptors `[1, 0, 2, 255]` — Joliet present) → **VM test:
Calamares launched, operator confirmed** → `dd` to `/dev/sda` (5981/5981 MiB) → `cmp` byte-identical.

ISO: `~/ncde-ISO/out/poseidon-20261002.iso`. Sticks rebuilt on `NCDE_POSEIDON`.

> **Lesson, same class as the `ncde`/`ncde-qpa` alpm-hook gap (2026-09-27):** a file owned by no
> package is **invisible to `pacman -Su`**. Any vendored binary in the image must be re-checked
> against the upgraded shared-library set after every image-wide upgrade, or it silently rots while
> everything around it moves. `verify-sfs` should grow a "every unowned binary in the image still
> resolves all its `NEEDED` entries" check — **not yet written, genuinely open.**

## 2026-10-02 (later, same day) — two more live-ISO blockers fixed + a REAL BUILD-SCRIPT BUG

Operator booted the rebuilt stick on a laptop: *"Vesper opens but will not close. If it goes idle it
asks for a password."* Both were **live-medium-only** — neither can reproduce on the dev machine,
which is why they survived until an actual ISO boot.

**3. Idle lock asked for a password the live user cannot possibly have.** `live:!:20625:0:99999:7:::`
— the account ships with a **locked password**, and there was **no polkit rule for
`org.freedesktop.login1.lock-screen`** in the image (the dev machine has none either, but dev's
`stephen` has a password, so the prompt is answerable there and nobody noticed). LaPivot owns the
idle policy → `ncde-lock-xss` → `ncde-portal` → logind `LockScreen` → default `auth_admin` →
**a dialog on the ISO that could never be satisfied. The machine locked with no way back in short
of a reboot.**
* **Fix:** `etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules` — grants `lock-screen`
  unconditionally. `unlock-screen` is deliberately **not** granted, so installed systems (real user,
  real password) still require the password to unlock.
* Same principle already stated in `49-nopasswd-calamares.rules`: the live medium must never put a
  password dialog in front of a user who has no password.

**4. Vesper must never open on the install medium.** `home/live` ships
`vesper-brain.service` in `default.target.wants`, so the brain started every live login and the
shell's threat trigger opened the window over the running installer.
* **Fix:** masked to `/dev/null` on **`home/live` only** — operator decision, so installed systems
  keep Vesper (and its false-alarm suppression, which is already handled: rkhunter dunst/Steam
  `/dev/shm` filtered, telnet inode re-baselined).
* **Do NOT add a close control to `vesper-patch-20260711/Main.qml`.** The operator has buttons on the
  Motif frame already; the window never opens on an install medium once the brain is masked, so
  there is nothing to close. An earlier attempt added one and was reverted.

> ### 🔴 REAL BUILD-SCRIPT BUG — `step21` symlink masks silently fail when the target already exists
>
> `pl.S(path, '/dev/null', …)` **only takes effect where the image tree has NO entry of that name.**
> Where the tree already holds a real symlink, mksquashfs keeps the tree copy and the mask is
> **silently discarded — no warning, no error, and `verify-sfs` still reports PASSED.**
>
> Proven in the 16:30 build: `etc/systemd/user/ncde-automount.service` (no tree entry) masked
> correctly, while `etc/skel/…/ncde-automount.service` and `home/live/…/ncde-automount.service` both
> stayed as `-> /usr/lib/…`. The Vesper mask failed the same way and shipped in two ISOs before it
> was caught by reading the built squashfs.
>
> **Fix:** every mask aimed at a pre-existing symlink must be preceded by `pl.X(path)` to exclude
> the tree copy first. Applied to the Vesper mask in `files/iso/step21-overrides.py`.
>
> **Genuinely still open — do not assume this is caught:** the two `ncde-automount.service` masks
> above are still no-ops, and `verify-sfs` cannot detect a dropped mask. A check that every `S … /dev/null`
> entry in `pseudo.txt` actually reads back as `/dev/null` **in the built squashfs** is
> **not yet written.**

**Also fixed in passing:** the skel→`home/live` mirror in `step21-overrides.py` no longer copies
skel's wallpaper over `home/live`'s (that mirror is what destroyed the good live value).

**Final gate — every stage passed, read back out of the shipped ISO, not the plan:**
`squash` 5.3G (355 pseudo defs) → `verify-sfs` **PASSED** (368945 entries) → `boot` (ESP 334 MiB,
7.2.7-zen1-1-zen) → `iso` (volume descriptors `[1, 0, 2, 255]`) → VM boot → `dd` 6.3 GB to `/dev/sda`
→ **`cmp` VERIFIED: stick matches the new ISO** (17:39).

> **Process lesson, operator-flagged and worth keeping:** for the whole of this fix, changes were
> verified by their presence in `pseudo.txt` and called done. `pseudo.txt` is a **request** to
> mksquashfs, not a result — the only thing that proves a fix shipped is reading the file back out
> of the **built squashfs**, or out of the **ISO itself** (`xorriso -osirrox … -extract
> /arch/x86_64/airootfs.sfs`). Two of the four fixes shipped broken for exactly this reason.
> Read back from the artifact, always.

## RIGHT NOW — 2026-09-23 batch deployed + verified; one live check still needed

`sudo bash ~/my-project/files/ncde-full-patch-20260711.sh` finished (process gone from `ps -ef`,
field-kit self-copy at `/usr/local/share/ncde-fix/...` refreshed to 11:49:42). File/binary/
service-level verification, all real checks against the live system, all passed:
- Thunar SEGV: `ncde-gtk-module.so` redeployed 11:49:33, `on_window_unrealize` symbol present
  (`nm`, not `nm -D` — it's a local symbol), md5 matches the staged copy exactly.
- fontsync crash-loop: `ncde-fontsync.path` has only `PathChanged=` now (no `PathExists=`), unit
  is `active`, `systemctl --user --failed` / `systemctl --failed` both show 0 units.
- Soundings recovery: `ncde-recovery-vt.service` → `enabled`; `ncde-recovery.desktop` →
  `Exec=sudo -n /usr/local/bin/ncde-recovery`, `Icon=document-revert`; `main.qml` has the new
  shortcut line. Could not read `/etc/sudoers.d/ncde-recovery` directly (root-only, no sudo
  access available to verify with) — **operator should confirm** with
  `! sudo cat /etc/sudoers.d/ncde-recovery`.
- `bak()` dated-tag fix: a fresh `/usr/share/ncde/main.qml.prebak-20260923` now exists (the old
  bug would never have created this, since `main.qml.prebak-20260711-fullpatch` already existed).
- Iris Chroma contrast: LaPivot binary swapped, `cap_sys_nice` re-granted (only happens on the
  successful-swap code path in step 7w).
- Filigree Phase 4 + NCDEKit controls parity: fresh mtimes this run; `NCDETabBar.qml` top-level
  and `controls/` twins are md5-identical (parity fix landed).
- Hummingbird rebuild: binary md5 exact match to the documented
  `a0ec0e8f4262e8206de9e0b46ddffe55`.
- **Not checked this pass:** NCDE Command sudoers (step 0d, `exec_background`) — same root-read
  problem, ask operator to confirm; Dock icon bezel extension to BottomPanel/Expose/TopPanel —
  confirmed NOT part of this deploy (only `Dock.qml` has `IconBezel`), still genuinely open, see
  below.

**One real functional gap, not file-checkable:** tried to confirm the Ctrl+Alt+R fix (no more
double password prompt) via `xdotool key ctrl+alt+r`, but the active window was this terminal,
not the LaPivot desktop shell, and `xdotool windowactivate` against LaPivot's window didn't take
(it's the WM itself). Headless key-injection isn't reliable for this on this system — same
false-alarm risk already documented for GIMP. **Needs the operator to actually press Ctrl+Alt+R
at the desktop** and confirm: recovery window opens with only the in-app "confirm the descent"
seal, no separate polkit password dialog first. Separately, the console/tty8 half
(`ncde-recovery-vt.service`) has never been visually confirmed rendering — service is `enabled`
now, but nobody has watched it actually paint the screen on tty8 yet.

**Next, per operator direction 2026-09-23** ("polishing all the other things, the native apps,
the look and feel... Iris Chroma could be better as well as Filigree"): live design audit of the
Iris Chroma palette picker and Filigree typography tab as they actually render post-deploy — find
concrete remaining rough edges from what's on screen, not from old notes.

## 2026-09-24 — wallpaper ink DONE ✅ (operator: "wallink is perfect now")

Ink-fix installed 13:38 and confirmed live: all 23 files match the staged `new/`, LaPivot journal
has 0 TypeErrors, `~/.config/ncde/wallpaper-ink.json` is valid (`on: true`). All four 09-24 batches
(beautify, expose, wallpaper-ink, ink-fix; each with install.sh/revert.sh/orig/new) are backed up
in `files/ncde-batches-20260924/`. Not yet folded into `ncde-full-patch-20260711.sh`.

## 2026-09-24 late — wallpaper-ink FIX (history) (`~/Projects/ncde-ink-fix-20260924`)

Operator: text "too dark with the wallpaper palette picker" and "does not change with new themes".
Cause (journal, 1,394 errors): `TypeError: Property 'inked' of object Theme is not a function`.
The global `theme` is LaPivot's **C++ Theme object** — `ThemeTokens.qml` is never instantiated, so
everything the ink batch hung on it was dead; each `color: theme.inked(...)` binding threw → Qt drew the
text black and it never re-bound on theme change. The wallpaper-card tap also threw mid-handler, so
`saveTheme()` never ran. Fix: new qmldir singleton `WallInk.qml` (inked/setInk/inkOn/inkSerial), 20
call sites repointed, ThemeTokens.qml restored to pre-ink. Also fixed: XHR PUT doesn't truncate →
padded write (otherwise a stray `}` corrupts wallpaper-ink.json). Verified in a real Qt 6 engine.
Lesson: never add API to `theme` — it's C++. Harness mocks hid this.
Install: `sudo bash ~/Projects/ncde-ink-fix-20260924/install.sh`, then relog.

## 2026-09-24 afternoon — Expose + wallpaper-ink batches INSTALLED 13:30, awaiting relog

1. **Expose** `~/Projects/ncde-expose-apps-20260924`: Expose icons use the dock's exact stack
   (NCDEIconBezel + MuchaIcon + NCDEGlassCap); Expose calls `appMenuModel.reload()` on open so
   new installs appear without a relog; AppImages dropped in `~/Applications` get launchers
   (`ncde-appimage-gen` + user path unit — enable with `systemctl --user enable --now
   ncde-appimage-gen.path`). No pacman .desktop generator: every real app already ships one;
   the scan only found ~45 dev tools/helpers.
2. **Wallpaper ink** `~/Projects/ncde-wallpaper-ink-20260924` (operator: "all fonts on the shell
   will turn that color when this theme is picked"): new `ncde-ink.js` + `theme.inked(c)` keep
   each text colour's lightness and turn its hue to the wallpaper's strongest hue (purple).
   On when a card in Iris "From your wallpaper" or ✦ Woven is tapped, off on a main-grid card;
   persisted in `~/.config/ncde/wallpaper-ink.json`. Text only — gold trim stays gold. Covers
   panels, dock, Expose, Launchpad, menus, Glia, HUD, calendar, widgets + canvas text/digits.
   Offscreen-rendered: ink-off is pixel-identical to live. Not covered: settings apps,
   Hummingbird/Orchidée/calendar apps, main.qml's small dialog text.

Both installed 13:30 by operator; AppImage path unit enabled + tested (create/sweep in 0.2 s).
Awaiting relog, then re-tap the Iris "From your wallpaper" card to turn the ink on.

**All beautification ideas (24, incl. round 3): `docs/BEAUTIFY-NEXT.md`** (copy of
`~/Projects/ncde-beautify-20260924/NEXT.md`).

The morning batch below IS installed (13:07) — awaiting relog + the NEXT.md checklist.

## 2026-09-24 beautify batch — installed 13:07, awaiting relog; next ideas noted

15 files staged in `~/Projects/ncde-beautify-20260924` (install.sh / revert.sh, drift-checked):
clock + weather seven-segment ghost fix, weather town name (Germantown Hills, nearest OSM
settlement), Stats whole-row fit, Salon idle resting rose, Iris-tinted icon medallions, kith
emblems for the 5 house apps (Changeling: The Dreaming), Iris "From your wallpaper" + Woven
palette, metal MotifFrame, clock greeting, Athelian Engine inset. Offscreen-rendered and
warning-free; NOT yet seen live. Operator: `sudo bash ~/Projects/ncde-beautify-20260924/install.sh` + relog.
**Next beautification ideas + post-install checklist: `~/Projects/ncde-beautify-20260924/NEXT.md`.**

## Confirmed broken right now

(none open right now)

## Live UI audit — build the best NCDE daily driver

The product goal is to strengthen NCDE's existing workflows and identity, not
turn it into a generic OS or desktop. Continue the live visual audit alongside
research into how other Linux distributions solve comparable user workflows;
use those ideas selectively and combine them with the operator's imagination.

- **Staged QML corrections:** the running journal showed a stale `Connections`
  target in `SpacePanel.qml` (wallpaper ink belongs to the `WallInk` singleton),
  plus repeated undefined `theme.fontWeight`, `theme.fontItalic`, and
  `theme.letterSpacing` bindings. The C++ `theme` context does not expose those
  settings; all staged QML references now read them from `settings`. `qmllint`
  passed across the staged QML tree.
- **Not live or released:** the staged UI differs from root-owned
  `/usr/share/ncde`; no privileged changes were made. Fold these changes into
  the self-extracting patch, then require the operator's live deployment and a
  passing `publish.sh --check` before publishing a package.

## Staged, awaiting operator deploy

- **`thunar.service` SEGV — root-caused + fixed 2026-09-23 (real bug in OUR code, not
  upstream GTK/Thunar).** `coredumpctl info Thunar` gave a full backtrace: crash was inside
  `gdk_window_remove_filter`, called from `ncde_glia_win_data_free` in
  `/usr/lib/gtk-3.0/modules/ncde-gtk-module.so` (NCDE's own GliaTalk GTK3 global-menu
  publisher) — `SEGV_MAPERR`, a dangling-pointer dereference, not an upstream Thunar/GDK bug.
  - **Root cause:** source is `~/ncde-wm-rebuild/glia-plugin/ncde-gtk3-module.c`. It caches a
    `GdkWindow*` once at realize time (`wd->gdkwin`) and only ever released its X11 event
    filter (`gdk_window_remove_filter`) from the GObject-data destroy-notify, which fires at
    the window's *finalize*. GTK's own dispose sequence destroys the GdkWindow well before
    finalize runs, so by the time the destroy-notify fired, `wd->gdkwin` was already a
    dangling pointer.
  - **Fix:** added an `"unrealize"` handler via plain `g_signal_connect()` (not `_after`) —
    GObject guarantees plain-connected handlers run *before* the default class handler that
    destroys the GdkWindow, so the filter is removed while the pointer is still live. The old
    finalize-time removal is kept only as a defensive no-op fallback (it'll now always find
    `filter_installed == FALSE` in practice).
  - **Build:** `gcc -shared -fPIC -o ncde-gtk-module.so ncde-gtk3-module.c $(pkg-config
    --cflags --libs gtk+-3.0 x11)` — the exact command already documented in the source
    file's own header. Built clean (one pre-existing, unrelated deprecation warning on
    `gtk_stock_lookup`). Symbol table diffed against the live `.so` via `nm`: all 4 original
    functions present unchanged, plus the new `on_window_unrealize` — nothing else moved.
  - **Deploy coverage gap found + fixed:** this module had **zero** build/dep coverage
    anywhere in `ncde-full-patch-20260711.sh` despite being live since 2026-07-17 — same
    "zero deploy coverage" class of gap as `NCDEGlassSurface.qml` before it. Staged the built
    `.so` at
    `~/my-project/files/full-patch-20260711/src/usr/lib/gtk-3.0/modules/ncde-gtk-module.so`
    and added a `dep` line (~line 888, right before the existing step `7d3` symlink-fixup
    step, which needed the file to already exist live and previously had nothing shipping
    it). Embedded self-extracting archive regenerated + round-trip-verified byte-identical
    (`diff -rq`, md5) same as the fontsync fix below. Old script backed up as
    `.prebak-20260923-thunarfix`.
  - **NOT YET DEPLOYED.** Deploy: `sudo bash ~/my-project/files/ncde-full-patch-20260711.sh`,
    then relaunch Thunar and confirm `systemctl --user status thunar.service` / `coredumpctl
    list` show no new crash after normal use (opening/closing windows, browsing folders with
    the GTK global-menu publisher active).
  - **Out of scope, not touched:** `/usr/lib/gtk-2.0/2.10.0/modules/ncde-gtk-module.so` is a
    **different, older** binary (md5 differs, mtime 2026-07-10 vs the GTK3 copy's 2026-07-17)
    — not known to be affected (Thunar is GTK3), not audited this session.

- **`ncde-fontsync.service` / `.path` start-limit-hit crash loop — root-caused + fixed
  2026-09-23.** `ncde-fontsync.path` carried both `PathChanged=` and `PathExists=` on the same
  file (`~/.config/ncde/fonts.json`). `PathExists=` is level-triggered: every time the oneshot
  service exits, systemd re-checks the path, finds `fonts.json` still there (the script only
  reads it, mirrors to `font.json`, never touches the watched file), and re-fires immediately —
  a known systemd footgun ([systemd/systemd#16669](https://github.com/systemd/systemd/issues/16669)).
  Journal confirmed exactly this: 5 successful oneshot runs in ~230ms, then `start-limit-hit`
  (`StartLimitBurst=5`).
  - **Fix:** dropped `PathExists=`, kept only the edge-triggered `PathChanged=`, in
    `~/my-project/files/full-patch-20260711/src/usr/lib/systemd/user/ncde-fontsync.path` (also
    synced to the `NCDE-Installer/` mirror copy — byte-identical, confirmed via `diff`).
  - **Also fixed:** `systemctl start` alone does **not** clear a start-limit-hit failure —
    confirmed via [systemd/systemd#10529](https://github.com/systemd/systemd/issues/10529),
    `reset-failed` is required first. The patch script's fontsync step (`step "7u/10"`, ~line
    1465) never called it, so even a fixed unit file would've stayed stuck failed forever on
    this machine. Added `ustart reset-failed ncde-fontsync.path` + `.service` right before the
    existing `ustart start` call.
  - **Archive regenerated:** script content changed (new lines + shifted marker), so the
    embedded self-extracting archive was rebuilt from the sibling tree
    (`tar -C ~/my-project/files -czf - full-patch-20260711 ncde-live-patch-20260711.sh
    vesper-patch-20260711 | base64`, spliced in after `__NCDE_PATCH_ARCHIVE_BELOW__`) and
    verified byte-identical on re-extraction (`diff -rq` against the sibling tree, exit 0)
    before replacing the live script. Old script backed up as
    `.prebak-20260923-fontsyncfix`. `bash -n` syntax-checked clean before and after.
  - **NOT YET DEPLOYED.** Deploy: `sudo bash ~/my-project/files/ncde-full-patch-20260711.sh`,
    then confirm `systemctl --user --failed` no longer lists `ncde-fontsync.path`/`.service`.
  - **Pacman self-extractor Vesper omission fixed and published 2026-09-27.** Audit found the
    package archive contained `full-patch-20260711/` only, while the script explicitly expects
    `ncde-live-patch-20260711.sh` and `vesper-patch-20260711/` too; standalone package
    application therefore skipped Vesper. The canonical archive now contains all three roots
    (423 active files), round-trip verified. `publish.sh --check` verifies the archive against
    all staged files, all 308 active live UI files, and the transformed LaPivot binary. The
    publisher builds from the canonical `my-project/files/` script and synchronizes both
    installer mirrors. Version `ncde-2026.09.27.1042-1` is published and the remote package
    digest/signature were verified. The operator's machine remains at `0043-1` until its next
    `pacman -Syu` and successful post-transaction apply.

## Staged, awaiting operator deploy

- **Soundings recovery ("Ctrl+Alt+R" system restore) — two real bugs fixed 2026-09-23,
  operator asked directly "does the recovery software work."** The boot-snapshotter half is
  solid and confirmed working as designed: `ncde-snapshot.service` (enabled, fires once per
  boot + once per pacman transaction via `00-ncde-snapshot.hook`) takes real read-only btrfs
  snapshots into `/restore`, rolling window of 7 (`KEEP=7`, floor 3 under space pressure) —
  3 currently on disk, real `.meta` sidecars, matches the Handbook's documented "seven rolling
  snapshots" claim exactly. But the actual recovery/restore UI had two real, verified bugs:
  1. **`ncde-recovery-vt.service` (console-level recovery — works even when X/the desktop is
     dead, the console keymap `Ctrl+Alt+R` → tty8 binding) was disabled.** The keymap binding
     itself (`ncde-recovery-keymap.service`) is enabled and switches to tty8 correctly, but
     nothing was listening there — this is the half of the "no recovery disc, no USB, no
     technician to call" promise that matters most (when the desktop itself is broken), and it
     silently didn't work. Fix: `systemctl enable ncde-recovery-vt.service`.
  2. **Live-desktop `Ctrl+Alt+R` double-password-prompts.** `main.qml`'s shortcut and
     `ncde-recovery.desktop` both launched via `pkexec /usr/local/bin/ncde-recovery` with no
     matching polkit rule anywhere on the system (confirmed via `/etc/polkit-1/rules.d/` —
     grepped, nothing) — falls through to the default `org.freedesktop.policykit.pkexec.run`
     action and prompts once for polkit auth, then the app's own PAM `ncde-restore` admin-seal
     (the parchment "confirm the descent" veil) prompts a *second* time. The `.desktop` file's
     own header comment always documented "the in-app seal is the only password asked" as the
     design — it just was never actually true. Fix: switched to a `%wheel` NOPASSWD sudoers
     entry scoped to that one binary (`/etc/sudoers.d/ncde-recovery`, written+`visudo -cf`
     validated by the patch script before install), `pkexec` → `sudo -n` in both `main.qml` and
     `ncde-recovery.desktop`.
  - **Also fixed in the same pass:** `Icon=ncde-recovery` resolved to nothing in any installed
    icon theme (Adwaita/AdwaitaLegacy/breeze/breeze-dark/HighContrast/elementary/hicolor/Tango/
    locolor/gnome all checked) — every sibling house-app `.desktop` (Abacus, Magpie Talker,
    Vesper, Command, Terminal) uses a real resolvable stock name; this one was the outlier.
    Changed to `Icon=document-revert`, confirmed present in this system's actual theme files.
  - **Staged as step `7x/10`** in `ncde-full-patch-20260711.sh` (deps updated `main.qml` +
    new `ncde-recovery.desktop`, enables the VT service, writes the sudoers drop-in). Embedded
    self-extracting archive regenerated and round-trip-verified byte-identical against the
    sibling `~/my-project/files` tree before replacing the live script. Old script backed up as
    `.prebak-20260923-soundingsfix`. `bash -n` syntax-checked clean before and after.
  - **NOT YET DEPLOYED.** Deploy: `sudo bash ~/my-project/files/ncde-full-patch-20260711.sh`,
    then verify: `systemctl is-enabled ncde-recovery-vt.service` → `enabled`; `grep Exec
    /usr/share/applications/ncde-recovery.desktop` → `sudo -n ...`; `sudo -n -l -U <user>` shows
    the new NOPASSWD line; and a real functional test — press Ctrl+Alt+R on the live desktop and
    confirm the recovery window opens with **no polkit password dialog at all**, only the app's
    own parchment "confirm the descent" seal when RESTORE is clicked. **Not independently
    tested this session:** actually switching to tty8 and confirming the eglfs/KMS recovery UI
    renders there (needs a live VT switch + operator eyes on real hardware, not safely
    scriptable headlessly) — enabling the service is confirmed, but nobody has watched it
    actually paint the screen on tty8 yet.
  - **Correction to this doc:** the "Net-new, never queued" list below previously listed
    "pre-update snapshot hook" as never built — wrong, checked live 2026-09-23:
    `/etc/pacman.d/hooks/00-ncde-snapshot.hook` exists, is a real `PreTransaction` pacman hook,
    and correctly retags the snapshot `"tag":"update"`. Removed from that list.

- **Dock icon bezel — extend `IconBezel` shell-wide (2026-09-23 follow-on, operator-approved
  plan, not yet started).** Base bezel treatment on `Dock.qml` is confirmed working (see
  "Confirmed fixed" below). Remaining steps from that pass:
  1. Extend the same `IconBezel` pattern to the other 3 places `MuchaIcon` renders —
     `BottomPanel.qml`, `NCDEExpose.qml`, `TopPanel.qml` (tray) — for shell-wide consistency.
  2. Touch-target sizes — `NCDESlider` knob 18×18, `NCDECheck` box 20×20, both under the 24px
     accessibility floor (also listed separately below).
  3. Check `DockTooltip`'s styling against the rest of the shell now that the dock icons
     themselves are more ornate.
  - **Separately flagged, not started:** `MuchaIcon.qml` and its 18
    `mucha-icons-*.js` drawing libraries (~370KB, the actual Canvas2D icon artwork every
    medallion in Dock/BottomPanel/Expose/TopPanel renders through) exist **only live**
    (`/usr/share/ncde/`), root-owned, with zero copy anywhere in `~/my-project` and zero
    `dep` line in the patch script — same "zero deploy coverage" class of gap as
    `NCDEGlassSurface.qml` before it was fixed 2026-09-23. Not urgent (nothing here touches
    those files), but should get staged into the patch script before anyone edits the icon
    artwork itself.

- **NCDE Command System Update fix — sudoers `exec_background` (step 0d, 2026-09-22).** Operator
  reported "the ncdecommand on my partners machine does not update like mine." Root cause: this
  exact fix was applied live on THIS machine 2026-07-14 via a standalone script
  (`~/ncde-wm-rebuild/DEPLOY-20260714-ncde-command-fix.sh`) but was **never folded into the master
  patch** — confirmed via a full parity audit that the script had zero sudoers handling anywhere.
  Any other machine never got it. Now step 0d, using the exact proven `SUDO_EDITOR=... visudo`
  command (visudo validates before saving, can't corrupt sudoers). Deploy: `sudo bash
  ~/my-project/files/ncde-full-patch-20260711.sh`, then on that machine open NCDE Command → Update
  All → confirm packages actually install (check `pacman -Qu` before/after).
- **NCDEKit controls library — top-level/controls split, 22 files (2026-09-22 parity audit).**
  Every one of the 23 qmldir-listed shared widgets (NCDEButton, NCDECheck, NCDESlider, NCDEKit,
  etc.) has a same-named twin at `/usr/share/ncde/$f.qml` — the implicit-import fallback any app
  that doesn't `import NCDE.Controls` resolves to (7 real apps incl. Hummingbird do exactly this
  for NCDEVellum specifically). 18 of these 22 pairs had functionally diverged — real, independent
  fixes on each side (controls/ carried Accessible.* AT-SPI wiring + defensive animPolicy guards;
  the top-level twins separately picked up NCDECheck/NCDESlider's WCAG touch-target height fix,
  NCDESlider's released()/snapValues, and NCDEKit's own real palette-derivation fix that step
  0c/10's comment already claimed shipped "shell-wide" but never actually did). Hand-merged so both
  copies of every file carry every real fix from either side; 16 of the top-level twins were never
  dep'd by this script at all (added now). Verified: qmllint clean on all 22, Hummingbird QML-load-
  tested clean against the merged tree. Not independently verified: the other 6 real consumers
  (Abacus, BinnieApp, MagpieTalker, OrchideeApp, SettingsPanel, VerveText) — no compiled test
  harness for those exists yet, only static/lint-level confidence for them.

- **Iris Chroma accent-contrast fix (step 7w).** 25 of the 90 live palettes had accent color under
  WCAG AA 3:1 against their own panel background — accent drives buttons/borders/highlights/focus
  throughout NCDEKit. Minimal hue-preserving nudge computed for each, tested against a copy of live
  LaPivot (75 slots patched, byte-verified, offscreen launch confirmed clean), folded into
  `ncde-full-patch-20260711.sh` as step 7w using the same one-off dedicated-backup pattern as 7t
  (not the buggy global `bak()` — that's still unfixed, see below). Deploy: `sudo bash
  /home/stephen/my-project/files/ncde-full-patch-20260711.sh`, then relogin (or reselect the active
  preset) so LaPivot picks up the patched `kPresets`. Per the documented Filigree→Iris Chroma→
  NCDEKit→NCDEEngine→GTK-bridge pipeline (`applyPreset` is one of the five bridge trigger sites),
  the fix should propagate to GTK/Chromium apps too without a separate patch.
- ~~Follow-up: the script's self-extracting embedded archive wasn't regenerated after adding step
  7w's `notes/apply-iris-contrast.py` + `notes/iris-contrast-fix.json`~~ — **fixed 2026-09-22**:
  regenerated (`tar -C ~/my-project/files -czf - full-patch-20260711 ncde-live-patch-20260711.sh
  vesper-patch-20260711 | base64`, spliced in after `__NCDE_PATCH_ARCHIVE_BELOW__`), self-extraction
  verified byte-identical to the live sibling tree (md5-checked), old script backed up as
  `.prebak-20260922-hummingbird-attachments`. The embedded archive now also carries every
  Hummingbird change below, so a standalone copy of the script (no sibling folder — e.g. the USB
  field kit) installs identically to this machine.

- **Hummingbird Courier — attachments, persistent connection, spam, rules, Plain stationery
  (2026-09-22, operator: "make Hummingbird the best mail client, no bugs").** Rebuilt from
  `~/ncde-wm-rebuild/hummingbird/rebuild/src` (`build.sh` exit 0, offscreen smoke test clean,
  QML load-tested against a full live `/usr/share/ncde` tree — QQmlComponent reached Ready, zero
  QML errors). Ships as an update to step 7f (binary) + the existing QML `dep` loop (no new dep
  lines needed — `HummingbirdCourier.qml`/`HBWritingDesk.qml`/`HBReadingDesk.qml`/
  `hb-stationery.js` were already staged, this just updates their content):
  - Real file attachments, send + receive (MIME multipart/mixed out, BODYSTRUCTURE-parsed
    save-to-disk in; message-list attachment clip icon is now real, was always-empty before).
  - Persistent IMAP connection for delete/archive/spam/flag/emptyTrash — was reconnecting fresh
    per call (operator-reported slowness); now one connection, reused, self-healing.
  - HB-DIAG diagnostics added to delete/archive (not a guessed fix) for the operator-reported
    "delete lands in Archive" symptom — **needs one live delete + `journalctl --user -b | grep
    HB-DIAG`** to actually root-cause; the IMAP recipe read correct end-to-end in the source.
  - reportSpam(), a simple rules/filters engine (rules.json, applied to fresh Inbox loads), a
    13th "Plain" (no-letterhead) stationery option, undo-send (6s cancellable countdown), and a
    sidebar text-clipping fix ("Iron Orchid Station" was overrunning the sidebar).
  - Deploy: `sudo bash /home/stephen/my-project/files/ncde-full-patch-20260711.sh`, then relogin
    Hummingbird. Post-deploy: `md5sum /usr/local/bin/hummingbird-courier` should read
    `a0ec0e8f4262e8206de9e0b46ddffe55`. USB mirror (`NCDE-BACKUP`) already updated + synced.

## Confirmed fixed (contradicts the old archived docs — trust this, not them)

- **Dock icon bezel (2026-09-23).** Operator relogged; `LaPivot` (pid 188480) now started
  2026-09-23 01:04:24, after the Dock.qml copy (01:00:19) — live md5 matches staged. Verified
  visually: hover-reveal screenshot (`xdotool mousemove 2 600` then `2 601`, `maim`), zoom-cropped
  the BFB icon and all four visible pinned icons. Bronze bezel ring + dark socket-shadow render
  clearly behind every medallion, and the glass pill's top "came highlight" glint is visible above
  the BFB icon. No QML errors relevant. Follow-on extension work moved to a new entry above.
- WM crash-respawn (old B-F2): `ncde-x11-session` has a real respawn loop with a rapid-crash
  giveup guard (grep `rapid_crashes` in `/usr/local/bin/ncde-x11-session`). Live, working.
- `reduceMotion` / `animPolicy.instant` consumption: present in all live `/usr/share/ncde/controls/*.qml`
  (NCDEField, NCDERadio, NCDEScrollBar, NCDEButton, NCDEProgressBar, NCDEDialog, NCDECheck, NCDESlider, NCDEToggle).
- Weather location pinned correctly (`~/.config/ncde/fonts.json`... er, `~/.config/ncde/weather*`
  config shows Germantown Hills IL 61548, correct lat/lon, `"source": "install-set"`).
- Fonts/Filigree tab wiring: `~/.config/ncde/fonts.json` holds real curated values, not defaults;
  `/usr/share/ncde/FiligreeTab.qml` mtime matches the 2026-07-21 17:37 full-patch run.
- GIMP window-maximize/snap fix: operator-confirmed live-working 2026-08-06 (don't re-test via
  headless xdotool launches — that path crashes GIMP for unrelated reasons, false alarm risk).

## Known bug class, fixed 2026-09-23 (staged, awaiting deploy with everything else above)

- **`bak()` in `ncde-full-patch-20260711.sh` used one global one-shot `TAG` ("prebak-20260711-
  fullpatch") for the script's entire life.** A file already backed up once under that tag never
  got backed up again on any later run — this is what silently destroyed the GIMP snap fix during
  the 2026-07-21 01:31 deploy, and would have swallowed today's Soundings `main.qml` change too
  (already backed up once, 2026-07-11, under the old hardcoded tag). Fixed per the operator's
  2026-08-06 decision: `TAG="prebak-$(date +%Y%m%d)"` — dated per calendar day, so every day's
  first run captures a fresh pre-change snapshot of whatever is actually live, without piling up
  a new backup on every re-run of the same day. `bash -n` clean, embedded archive regenerated +
  round-trip-verified byte-identical. Old script backup for this change is folded into the same
  `.prebak-20260923-soundingsfix` copy made just before it (both edits landed in the same
  pre-deploy session, one archive regen covers both).

## False alarm, corrected 2026-08-06 (operator caught it — own it, don't re-flag)

- ~~`FirewallTab.qml` orphaned / no way to arm Vesper~~ — **wrong.** The real Armed/Disarmed
  toggle for Vesper lives in `SecurityTab.qml` (registered, reachable, header comment literally
  says "it lives in security tab" per operator, 2026-07-01), wired to `settings.kickassArmed`,
  actually starts/stops `vesper-brain.service`. `FirewallTab.qml` is a separate, genuinely-dead
  leftover file superseded by `SecurityTab.qml` — not the control surface, never was. The prior
  survey flagged the dead file without checking whether the same function existed elsewhere.
  Lesson: when a file looks orphaned, grep for the *functionality* elsewhere before calling it a
  gap — a superseding file with the same feature is a normal, expected pattern in this project
  (see also: `FontsTab.qml` retired in favor of `FiligreeTab.qml`, same shape of non-issue).
- Note: Vesper is **not an AI** — it's a deterministic, no-LLM security suite (real MITRE ATT&CK
  library + rule-based engine orchestration over ClamAV/rkhunter/fail2ban). Don't describe it as
  "AI" in docs or conversation going forward.

## Unconfirmed / needs a live re-check (carried over from the archived punchlist, not yet re-verified in 2026-08)

- Clipboard "Mechanism B" — ~50% paste failure in non-frozen windows, never root-caused.
- Tiling 8-window blink/freeze — never root-caused (GLX decoration-burst theory).
- Soundings recovery UI's `backend.listBackups()` object — real snapshots exist on disk
  (`/restore/BAK-0100/101/102`), but whether the QML restore UI actually has a live backend wired
  in, or restore is still manual/script-only, is unconfirmed — needs a direct functional test.
- Magpie: the operator-decided pivot to an open-oscar-server/TOC model (~2026-07-22) exists only
  as a decision — zero `oscar`/`toc` strings in the live binary. Still running the original
  OpenDHT "ham radio" model today.
- verve-text: line numbers may already work (weak string-scan signal); syntax highlighting does
  not appear to exist (`QSyntaxHighlighter` absent) — needs a direct feature test, not inference.
- Xorg "client bug: event processing lagging behind... system too slow" warnings for mouse/keyboard
  in the first 1-2 minutes of boot (`journalctl -u ncde-portal.service`) — new lead, not previously
  logged anywhere; unclear if one-off or recurring input-latency issue.
- `SettingsPanel.qml`'s own header comment lists a "GTK Apps" tab group that doesn't actually exist
  in the tab array — either dead documentation or a removed/unfinished tab; ask the operator.
- Printer "Add" opens raw CUPS web admin instead of a native flow.
- Touch targets <24px in some NCDE controls (NCDESlider knob 18×18, NCDECheck box 20×20) —
  file/line-confirmed 2026-08-06, still open.
- 204+ hardcoded `font.pixelSize` literals not routed through `theme.scale()` — a blanket sweep
  was previously rejected as unsafe; needs a scoped approach.
- ISO volume label still `ARCHCRAFT_202605`, not `NCDE_POSEIDON`.
- Calamares `removeuser` module not wired (phantom "live" account at greeter).
- GRUB theme path in Calamares post-install still points at `starfield`, not the NCDE theme.
- Net-new, never queued: auto update-notifications, Bluetooth pairing agent, WPA-Enterprise +
  captive portal, license browser in About panel.
