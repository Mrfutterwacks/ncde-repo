# ISO-BUILD-PLAN.md — NCDE Poseidon: rootfs + calamares-ncde → bootable ISO

Status: **PLAN ONLY. No build executed.** Every privileged step below (`pacman`, mount,
`mkarchiso`, `mksquashfs`, loop devices) requires **per-step approval** per CLAUDE.md rule 5,
and the operator runs the `sudo` parts (Claude cannot supply the password — use `! sudo …`).
Rule 7 governs: nothing user-visible may name Arch.

> **🔴 CORRECTED 2026-07-17 — `~/ncde-staging/` (and `~/ncde-staging/LaPivot/compass7/`) do NOT
> exist anymore.** The dev machine that hosted that tree is gone; checked directly against this
> machine and the USB backup, both absent. Every reference below to `~/ncde-staging/LaPivot/` as
> "the production tree" — including the whole 2026-07-04/2026-07-07 banner block right below,
> §0's "What we have," §3's overlay step, §4's path note, §7's Method B tree references, the §8
> gate table, and the §10 Build Manifest's derivation date — describes a build source that no
> longer exists. **There is no separate production tree to rebuild the ISO from right now.**
> Corrected model (matches `docs/CLAUDE.md`'s top banner and rules 9-10):
> - The **live running system** (`/usr/local/bin/LaPivot`, `/usr/share/ncde/`, etc.) is the actual
>   source of truth now, not a staged tree.
> - **C++ source recovery** is via Ghidra-decompiling the live `LaPivot` binary, reconstructed
>   class-by-class in `~/ncde-wm-rebuild/` — partial, most classes still raw decompiled output, not
>   clean buildable source. See `docs/lapivot-rebuild.md` for current per-class status.
> - **QML** was never lost — plain text at `/usr/share/ncde/`, loaded from disk by LaPivot.
> - **The real deploy mechanism** is `~/my-project/files/ncde-full-patch-20260711.sh` — every live
>   fix folds into this one script.
> - `~/ncde-ISO/` (this plan's own build area) is unaffected and still current.
> Before this plan's Method A/B steps can actually be run, the squashfs source needs to be
> re-established from the live system + patch-script output (there is no `rsync` source tree to
> point §3.2/§7.2 at until that happens) — none of the historical dated entries below are rewritten,
> but treat every "the production tree is `~/ncde-staging/LaPivot/`" statement as **stale** until
> a new build-source location is confirmed.

> **🟡 HISTORICAL — superseded by the 2026-07-17 notice above; kept for the record, not current.**
> **🟢 RE-DERIVED, 2026-07-04 — build source switched to `~/ncde-staging/LaPivot/`.** §0/§3/§7/Build
> Manifest below now reference the real production tree (operator-confirmed 2026-07-03) instead of
> the old frozen tree, which was never kept in sync after the LaPivot pivot and doesn't even contain
> the `LaPivot` binary. This was a straightforward source-path switch, not a re-architecture — the
> tree shape is the same (`usr/ etc/ var/ boot/ home/` + `bin/lib/sbin` symlinks). What DID need
> updating: the exclude list, because LaPivot's tree carries dev-only material the old tree's list
> never had to account for — `compass7/` and `src/` (C++ source + build dirs, not runtime files) and
> a much larger, less predictable set of stale binary variants (`usr/local/bin/*.prebak-<desc>`,
> `*.rebuilt-broken-*`, `*.restored-from-*` — this tree's own ad-hoc backup convention, ~19 stale
> binaries found in `usr/local/bin/` alone as of this pass). §10.1's exact-name whitelist for
> `usr/bin`/`usr/local/bin` is still the real safety net here — it ships only the named canonical
> binaries regardless of what glob excludes catch or miss. Full detail: auto-memory
> `project_ncde_lapivot_punchlist`, `CLAUDE.md` §9. The Build-Readiness Gate (§11) below has NOT been
> re-verified against the new tree — its checkboxes still reflect the old tree's last state.

This document takes the **historical state** — a build-ready rootfs at `[dead-legacy-tree]/` (5.3 GB, version
`2026.06.21`, 683 local pacman pkgs) and the Calamares config set at `[dead-legacy-tree]/calamares-ncde/` —
to a bootable, VM-tested ISO. **See the stale-notice above before acting on anything below.**

> **✅ RESOLVED (2026-06-21, late session, HISTORICAL — superseded by the notice above) — the
> clone-vs-overlay contradiction is gone.** The
> earlier worry was that `[dead-legacy-tree]` was a stale copy while the live `/` held the real files. That was
> resolved at the time: every NCDE file the running system used was traced and **copied into
> `[dead-legacy-tree]`** (mirrored paths; per-user config into both `etc/skel/` and `home/live/`), ownership
> was normalized (`root:root` system, `1000:1000` home/live), and completeness was **verified
> file-by-file (0 missing / 398 files)** — as of 2026-06-21, before LaPivot existed. §3 below ("overlay
> `[dead-legacy-tree]` → airootfs") and the Build Manifest describe that historical state, not the current one.

---

> **🔴 STALE PATHS, 2026-07-17: everything in this Gate-3/2.5/2.6 block below (fix-ownership.sh
> clone source, the `glib-compile-schemas` etc. cache-regen commands, the bwrap install-behavior
> gates) was written against `~/ncde-staging/LaPivot/`, which no longer exists (see the banner at
> the top of this doc). The bugs and fixes documented here are real and still the right process
> **once a new build-source tree/clone is established** from the live system — but the literal
> `~/ncde-staging/LaPivot/...` paths below will not resolve until that happens. Do not run these
> commands against a path that isn't there.**

> **🔴 SUPERSEDED FOR THE LaPivot TREE (2026-07-07 final ISO audit — verified, not assumed):
> the production tree `~/ncde-staging/LaPivot/` is ENTIRELY stephen-owned (1000:1000) and has
> ZERO setuid/setgid files** (`find -perm -4000 -o -perm -2000` = 0; live has the normal set —
> su*o/passwd/pkexec are `rws root` on live, plain 0755 uid-1000 in the tree). That is by
> design (sudo-free staging) and it means §0a's "the tree is already correct" below was true
> only of the dead legacy tree. **Building a squashfs from the raw tree ships broken
> sudo/pkexec/passwd/polkit and uid-1000 system files (pkexec calamares dies in the live
> session).** The cure is the new **Gate-3 step: `sudo bash ~/ncde-ISO/fix-ownership.sh`** —
> clones the tree to `~/ncde-ISO/airootfs-root/`, restores ownership+mode for every path from
> the LIVE system (the installed twin), pins `home/live`=1000:1000 and
> `var/lib/ncde-portal`=961:961, and self-verifies (suid restored, shadow 600, etc.).
> **mksquashfs runs on `airootfs-root/`, never on the raw tree.** After the clone, re-run
> `sudo setcap cap_sys_nice+ep ~/ncde-ISO/airootfs-root/usr/local/bin/LaPivot` (punchlist
> §0.13: cp/rsync drop file capabilities; mksquashfs preserves the xattr, so the installed
> system keeps the WM's SCHED_FIFO/autogroup boost — verify with
> `getcap airootfs-root/usr/local/bin/LaPivot` before building).
>
> **🔴 Gate-2.5 — REGENERATE GENERATED CACHES IN THE TREE BEFORE THE CLONE (added 2026-07-07,
> session 84 — this gap shipped a broken first install).** rsync-vendoring copies package FILES
> but never re-runs the pacman hooks that maintain the generated caches, so the tree's caches
> silently go stale while the dev host's stay current — and the breakage only manifests on an
> installed system. Proven consequence on the first burned ISO: the stale
> `usr/share/glib-2.0/schemas/gschemas.compiled` (Jun 21) predated the vendored
> `org.appmenu.gtk-module` schema while `/etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module.sh`
> loads that module into every session → **every GTK3 app (chromium/gimp/spotify/libreoffice)
> died with a fatal `GLib-GIO-ERROR: Settings schema 'org.appmenu.gtk-module' is not
> installed` SIGABRT** — "dock icons don't open," no browser for Hummingbird's Gmail setup.
> Reproduced and fix-proven inside the actual airootfs via unprivileged bwrap (session 84).
> Before every fix-ownership clone, run ALL of these against the tree (no sudo needed —
> stephen owns the tree; back up each cache as `.prebak-*` first, excludes strip those):
> ```
> glib-compile-schemas  ~/ncde-staging/LaPivot/usr/share/glib-2.0/schemas/
> gtk-update-icon-cache -f -t ~/ncde-staging/LaPivot/usr/share/icons/hicolor
> update-mime-database  ~/ncde-staging/LaPivot/usr/share/mime
> update-desktop-database ~/ncde-staging/LaPivot/usr/share/applications
> gio-querymodules      ~/ncde-staging/LaPivot/usr/lib/gio/modules
> ```
> (`etc/ld.so.cache` staleness self-heals: `ldconfig.service` ships with
> `ConditionNeedsUpdate=|/etc` and rebuilds it on first boot — verified in the unit.)
> All five were run + verified 2026-07-07 (schemas 43,533→80,506 B; hicolor icon cache
> 4,296→60,244 B; gio cache 4→7 modules incl. gvfs). Any future vendoring re-triggers this gate.
>
> **🔴 Gate-2.6 — INSTALL-BEHAVIOR GATE: NO mksquashfs UNTIL IT PASSES (added 2026-07-08,
> session 84 — a 40-min squash was wasted by building first and confirming after).** After
> every fix-ownership clone and BEFORE the squash, the agent runs the bwrap gates against the
> fresh `airootfs-root` (read-only binds, skel-seeded HOME, Xvfb — scripts preserved in the
> session-84 scratchpad, trivially recreatable from SESSION_HANDOFF 84): (a) shipped chromium
> with BOTH GTK module env vars forced — must run 25s with zero GLib/GTK/schema errors;
> (b) a Qt house app (orchidee) — must run clean; (c) fake-root `pacman-key --init/--populate`
> offline — must build the web of trust from the shipped seeds; (d) presence set: keyring
> seeds, fakeroot, alpm user in shipped passwd, mirrorlist, zero archcraft repo refs. The
> dev machine can NEVER catch install-only failures (pacman hooks keep dev's caches current,
> root-only files never enter the tree) — the airootfs container is the installed twin, so
> confirm there FIRST, squash SECOND. Same principle for any future install-side doubt:
> reproduce in the container, don't reason from dev.

## 0a. OWNERSHIP — AUTHORITATIVE (agents have given conflicting info; this is the truth)

Two layers people confuse:

1. **Squashfs content (the one that matters):**
   - System files (`/usr /etc /var /bin …`) = **`root:root` (0:0)**.
   - **`/home/live` and everything under it = `1000:1000`** (the live user owns its home).
   - `mksquashfs` **preserves on-disk ownership by default** — just run it.
   - **NEVER pass `-all-root`** — it flattens `home/live` to root and breaks the live user's
     autologin/session. (This is the usual source of bad advice.)
   - If copying the tree, use `rsync -aHAX --numeric-ids` so `1000` stays `1000`.
2. **ISO9660 layer (xorriso):** does NOT carry in-system uid/gid — the squashfs inside the ISO does.
   Don't conflate "the ISO" with squashfs ownership.

The tree `[dead-legacy-tree]` is already correct (system `root:root`, `home/live` `1000:1000`) — which is
exactly why editing it needs sudo. **Net: system=root:root, home/live=1000:1000, no `-all-root`.**

> **This already bit us — not theoretical (operator-confirmed 2026-06-22):** the FIRST VM test
> black-screened in part because that build's squashfs was **all `root:root`** (home/live flattened →
> the live user couldn't own its session), stacked on the then-missing `ncde-portal` greeter user. That
> build predated the ownership normalization. Both halves are fixed now (greeter user `961:961` present;
> ownership re-verified `1000:1000`). The no-`-all-root` rule is the guard that keeps the ownership half
> fixed — break it and the black screen returns.

---

## 0. Inputs, facts, and the two viable methods

> **🔴 STALE, 2026-07-17: this whole "What we have" list describes `~/ncde-staging/LaPivot/`,
> which no longer exists (dev machine gone, checked this machine + USB, see top-of-doc banner).
> Nothing below can be run as written until a new squashfs source is established from the live
> system + `~/my-project/files/ncde-full-patch-20260711.sh`. Kept below for reference on what the
> tree used to contain, not as a current input.**

### What we have (re-derived 2026-07-04 against the current production tree — STALE, see above)
- **Rootfs / squashfs source:** `~/ncde-staging/LaPivot/` — full system tree (`usr/ etc/ var/ boot/
  home/` + `bin/lib/sbin` symlinks), live `live` user (uid/gid 1000), `ncde-portal` wired as live
  DM, all NCDE binaries/fonts/themes. Package-DB count not re-verified this pass — re-confirm
  against this tree's actual `var/lib/pacman` before building (§3.1's `pacman -Qq --root` command
  below already points at the right tree; just run it and record the real count, don't assume 683).
  Unlike the old tree, LaPivot also carries real C++ SOURCE (`compass7/`, `src/`) and per-app build
  directories alongside the runtime binaries — these must be excluded (§10.2/§10.3), they were never
  a concern in the old tree.
- **Calamares config set:** `~/ncde-staging/LaPivot/calamares-ncde/` (staged source) AND
  `~/ncde-staging/LaPivot/etc/calamares/` (already-injected runtime location — confirmed present:
  `settings.conf`, `modules/*.conf` incl. `shellprocess`/`removeuser`/`partition`/`users`/`bootloader`/
  `grubcfg`/`packagechooser`/`welcome`/`finished`/`mount`/`initcpio`/`preservefiles`/
  `contextualprocess*`, `branding/ncde/` + a leftover `branding/archcraft/` that must be excluded,
  `launch.sh`). §4's injection step may already be largely done in this tree — verify contents match
  the source set in `calamares-ncde/` before assuming injection is still needed.
- **Reference base ISO:** `~/Downloads/archcraft-2026.05.12-x86_64.iso` (3.6 GB) — the proven
  boot/squashfs layout we are cloning. Not re-verified this pass (unaffected by the tree switch).
- **Read-only Calamares reference:** `~/ncde-staging/LaPivot/helpwithisla/calamares-reference/`
  (Archcraft's `/etc/calamares` + `/usr/bin` scripts).
- **Empty mount point:** `~/ncde-ISO/mnt/iso/` (ISO is **not** currently mounted; not re-verified
  this pass).

### Host toolchain (prerequisites — see §1)
- `archiso` is **installed** (`archiso 88-1`); `mkarchiso`, `xorriso`, `mksquashfs`, `mkfs.fat` all
  resolve. **Gate 1 is satisfied** — start at §2.
- Host `pacman.conf` already has the `[archcraft]` repo + `[core] [extra]` — good for pulling
  Archcraft profile packages.

### Two methods (pick one — Method A recommended)

| | **Method A — archiso profile rebuild (RECOMMENDED)** | **Method B — repack the existing ISO** |
|---|---|---|
| Idea | Obtain Archcraft's *archiso profile*, replace its `airootfs` with our `[dead-legacy-tree]`, inject `calamares-ncde`, run `mkarchiso`. | Mount the shipped ISO, rebuild only `airootfs.sfs` from `[dead-legacy-tree]`, re-author the ISO with `xorriso`, reusing Archcraft's exact boot files. |
| Pros | Reproducible; canonical; mkarchiso handles boot/EFI/checksums/uid preservation. | No profile needed; reuses known-good bootloader; fewer moving parts. |
| Cons | Need the profile (Archcraft's `iso`/`mkarchiso` profile dir). | Hand-authoring `xorriso` boot args is fiddly; easy to break UEFI/BIOS boot. |
| When | Default path. Use unless the profile is unobtainable. | Fallback if the profile can't be sourced and the ISO layout is well understood. |

> **⚠️ DECISION (2026-06-21, late): Method A is OUT → use Method B (§7).** There is **no Archcraft
> archiso profile** on this host (only generic `baseline`/`releng` under
> `/usr/share/archiso/configs/`); sourcing it would require Archcraft's published build repo. The
> base ISO is present and all tools resolve, so **Method B (repack the shipped ISO)** is the chosen
> path. §2–§5 below (Method A profile staging) are kept for reference but are **not** the active plan;
> jump to **§7** for the build, using the **§"Build Manifest"** for the squashfs contents/excludes.

The rest of this plan is written for **Method A**, with **§7** capturing Method B (now the chosen path).

---

## 1. Prerequisites (host tooling) — ✅ DONE (Gate 1 satisfied)

The build toolchain is already installed on the dev host (NOT in the rootfs):
```
archiso 88-1 ;  mkarchiso  xorriso  mksquashfs  mkfs.fat  → all resolve
```
(Originally installed via `sudo pacman -S --needed archiso`, which pulls xorriso, libisoburn,
squashfs-tools, dosfstools, mtools, erofs-utils.) **Proceed to §2.**

---

## 2. Stage the archiso profile — APPROVAL GATE 2

Create the working profile **inside the workspace** (`~/ncde-ISO/` is the designated ISO area per
PROJECT.md). The profile is the directory `mkarchiso` consumes.

### 2.1 Obtain Archcraft's profile
Source the Archcraft `iso` / `mkarchiso` profile (the dir containing `profiledef.sh`,
`packages.x86_64`, `pacman.conf`, `airootfs/`, `efiboot/`, `grub/` or `syslinux/`). Options, in
preference order:
1. If the operator already has the Archcraft profile checkout, copy it to `~/ncde-ISO/profile/`.
2. Otherwise extract the profile structure from the shipped ISO + Archcraft's published build repo
   (the ISO contains the *built* artifacts, not the profile sources — the bootloader configs under
   `boot/grub/`, `EFI/`, `loader/` can be mirrored into a hand-made profile if no upstream profile
   is available; this overlaps with Method B).

Target layout:
```
~/ncde-ISO/profile/
├── profiledef.sh           # iso name, label, fs type (squashfs), bootmodes, uid/perm rules
├── pacman.conf             # build-time repos (include [archcraft])
├── packages.x86_64         # packages installed into airootfs by mkarchiso
├── airootfs/               # the live filesystem skeleton  ←  WE REPLACE/OVERLAY THIS (§3)
├── efiboot/                # UEFI boot (systemd-boot/grub)
├── grub/  or  syslinux/    # BIOS boot menu
└── ...
```

### 2.2 Rule-7 sweep of the profile
Before building, grep the profile for Arch-identifying user-visible strings and reconcile to NCDE:
```bash
grep -rniE 'archcraft|arch linux|\barch\b' ~/ncde-ISO/profile/profiledef.sh \
    ~/ncde-ISO/profile/grub ~/ncde-ISO/profile/efiboot ~/ncde-ISO/profile/syslinux 2>/dev/null
```
Fix `iso_name`, `iso_label`, `iso_publisher`, `iso_application`, and boot-menu titles to NCDE
Poseidon. (Boot menu entry text is user-visible → Rule 7.) **Show before/after per file, one at a
time, per CLAUDE.md rule 4.**

---

## 3. Overlay `~/ncde-staging/LaPivot` into airootfs — APPROVAL GATE 3 (the core step)

> **🔴 STALE, 2026-07-17: `~/ncde-staging/LaPivot/` does not exist anymore (see top-of-doc
> banner). Every path in §3 below needs to be re-pointed at whatever the live-system-derived
> build source turns out to be before this gate is actually runnable.**

The live filesystem that becomes `airootfs.sfs` must **be** our rootfs. Two sub-decisions:

### 3.1 Decide: replace vs. overlay
- **Replace (cleanest):** make the profile's `airootfs/` equal to `~/ncde-staging/LaPivot/` content
  (minus workspace-only docs AND dev source/build trees — see 3.3, expanded for this tree). Our
  rootfs is the source of truth, users, services.
- **Overlay (if the profile installs packages itself):** keep `packages.x86_64` authoritative and
  copy only our NCDE overlay files (`usr/bin/ncde-*`, `usr/local/bin/*`, `etc/ncde/`,
  `etc/pam.d/ncde-portal*`, `etc/systemd/system/...`, themes, fonts, `home/live`, the
  `ncde-portal.service` + drop-in) on top. **Risk:** package-set drift from the tree's real DB.

**Recommendation:** **Replace** — our rootfs is the source of truth (PROJECT.md: "the live system
IS the installed system"). Set `packages.x86_64` to a minimal/empty set so mkarchiso does not
re-resolve and perturb the verified package set, OR regenerate `packages.x86_64` from the tree's DB:
```bash
pacman -Qq --root ~/ncde-staging/LaPivot --dbpath ~/ncde-staging/LaPivot/var/lib/pacman \
    > ~/ncde-ISO/profile/packages.x86_64
```

### 3.2 Copy preserving numeric ownership (CRITICAL — SESSION_HANDOFF §6)
Live `home/live` must stay **1000:1000**; system files root-owned. Copy as root, preserving all
metadata, and **never** flatten ownership:
```bash
sudo rsync -aHAX --numeric-ids \
    --exclude-from=/home/stephen/ncde-ISO/airootfs-excludes.txt \
    /home/stephen/ncde-staging/LaPivot/  /home/stephen/ncde-ISO/profile/airootfs/
```
- `-a` preserves perms/owners/symlinks/times; `-H` hardlinks; `-AX` ACLs/xattrs;
  `--numeric-ids` keeps 1000 as 1000 (no host-name remap → no `stephen` leak).
- In `profiledef.sh`, ensure the squashfs/permissions rules do **NOT** force `--all-root`
  (SESSION_HANDOFF §6). Verify the `file_permissions` array and any `mksquashfs` options keep
  `/home/live` at uid 1000.

### 3.3 Exclude workspace-only / virtual paths from the overlay
`~/ncde-ISO/airootfs-excludes.txt` must drop docs, dev artifacts, and pseudo-filesystems that must
never enter the squashfs. Re-derived 2026-07-04 for LaPivot's tree — the `/compass7`, `/src`, and
stale-binary entries are NEW vs. the old tree's list, everything else carries over:
```
/proc/***
/sys/***
/dev/***
/run/***
/tmp/***
/mnt/***
/CLAUDE.md
/PROJECT.md
/NCDE-CALAMARES-PLAN.md
/NCDE-INSTALL-PLAN.md
/SESSION_HANDOFF.md
/ISO-BUILD-PLAN.md
/preview.html
/settings.json
/check_session.sh
/complete_checklist.sh
/install_hooks.sh
/log_command.sh
/require_search_for_uncertainty.sh
/deploy-*.sh              # this tree's ad-hoc per-session deploy/revert scripts, dev-only
/revert-*.sh
/calamares-ncde/***       # staged separately into /etc/calamares (see §4) — not as a top-level dir
/helpwithisla/***         # read-only reference, not for shipping
/wallpapers/***           # ship only if intended; confirm
/version                  # keep ONLY if it is the intended live-system version marker; else exclude
/compass7/***             # C++ SOURCE + per-app build dirs (lelan, ncde-terminal, magpie, etc.) —
                          # dev-only; the compiled binaries this produces already live in
                          # usr/local/bin/ and ship from there, not from source
/src/***                  # older/alternate C++ source layout (has its own build/ + a
                          # CMakeLists.txt.stale) — dev-only, not runtime
/build/***                # top-level build dir
/ncde-wm/***              # a directory (not the binary) sitting at tree root — investigate/confirm
                          # purpose before the actual build; likely dev scratch, not runtime
usr/local/bin/*.prebak*   # this tree's ad-hoc backup convention: LaPivot.prebak-<desc>,
                          # ncde-sentinel.prebak, ncde-wm.prebak, etc. — ~19 stale binary variants
                          # found in usr/local/bin alone as of this pass, growing every session
usr/local/bin/*.rebuilt-broken-*
usr/local/bin/*.restored-from-*
```
**The real safety net for `usr/bin`/`usr/local/bin` stays §10.1's exact-name whitelist**, not these
globs — new stale-binary suffixes get invented ad-hoc each session (see the note in the top banner),
so treat any binary NOT explicitly named in §10.1 as excluded by default, glob match or not.
**[CONFIRM]** whether `etc/arch-release` / `version` should ship (NCDE-INSTALL-PLAN §8 flagged
`/etc/arch-release` as Rule-7-sensitive — handle in a separate review, not this build).

---

## 4. Inject the Calamares config set into airootfs — APPROVAL GATE 4

Map `calamares-ncde/` to its ISO target paths (README/§1 of the master plan):
```bash
# config + modules
sudo install -Dm644 calamares-ncde/settings.conf            airootfs/etc/calamares/settings.conf
sudo install -Dm644 calamares-ncde/modules/shellprocess.conf airootfs/etc/calamares/modules/shellprocess.conf
sudo install -Dm644 calamares-ncde/modules/removeuser.conf   airootfs/etc/calamares/modules/removeuser.conf
# branding (preview.html already removed from source → won't ship)
sudo rsync -aHAX --numeric-ids calamares-ncde/branding/ncde/ airootfs/etc/calamares/branding/ncde/
# post-install scripts → /usr/bin, EXECUTABLE
sudo install -Dm755 calamares-ncde/scripts/post_install.sh          airootfs/usr/bin/post_install.sh
sudo install -Dm755 calamares-ncde/scripts/chrooted_post_install.sh airootfs/usr/bin/chrooted_post_install.sh
```
(paths relative to `~/ncde-staging/LaPivot/` — **STALE 2026-07-17, that tree no longer exists,
see top-of-doc banner; re-point at the current build source once established**; airootfs =
`~/ncde-ISO/profile/airootfs`)

Post-inject checks:
- `calamares` itself must be installed in the airootfs (it is the installer). Confirm
  `pacman -Q --root … calamares calamares-config` or that `packages.x86_64` lists it.
- Branding dir contains NO `preview.html` (verified — moved out in this session).
- Scripts are mode 0755.
- Re-verify the §5 fixes from the master plan are already baked into the scripts (Fix #1 xsession
  no-clobber, #4 grub `ncde`). They were applied last session per SESSION_HANDOFF §0.

---

## 5. Build the ISO — APPROVAL GATE 5 (`mkarchiso`)

Run from a tmpfs-free location with enough disk (ISO + work dir ≈ 12–15 GB free):
```bash
sudo mkarchiso -v \
    -w /home/stephen/ncde-ISO/work \
    -o /home/stephen/ncde-ISO/out \
    /home/stephen/ncde-ISO/profile
```
- `-w` work dir (scratch; large), `-o` output dir (final `.iso`), last arg = profile dir.
- mkarchiso will: install `packages.x86_64` into a fresh airootfs (skip/minimize per §3.1 if we
  replaced airootfs wholesale), apply our overlaid files, run `mksquashfs` → `airootfs.sfs`,
  assemble BIOS+UEFI boot, checksum, and emit the ISO.
- **Show full stdout/stderr + exit code** (rule 6). Expect benign `--root`-style hook noise
  (SESSION_HANDOFF §0) only if package install runs; a wholesale-replace airootfs minimizes it.

Output: `~/ncde-ISO/out/<iso_name>-<version>-x86_64.iso`.

Post-build sanity (no sudo):
```bash
ls -lah ~/ncde-ISO/out/*.iso
# inspect the produced squashfs listing to confirm uid 1000 home + no leaked docs:
xorriso -indev ~/ncde-ISO/out/*.iso -find /arch/x86_64/airootfs.sfs 2>/dev/null || \
  isoinfo -l -i ~/ncde-ISO/out/*.iso | grep -iE 'preview|CLAUDE|calamares' | head
```

---

## 6. VM TEST GATE — APPROVAL GATE 6 (the gate that defines "done")

A build is not "done" until it boots and installs in a VM. Minimum spec: **≥4 GiB RAM, ≥25 GiB
disk**, EFI firmware (OVMF) — test UEFI first, then optionally BIOS.

```bash
# UEFI boot test (OVMF). Adjust OVMF path to host.
qemu-system-x86_64 -enable-kvm -m 4096 -smp 2 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=/tmp/ncde-OVMF_VARS.4m.fd \
    -cdrom ~/ncde-ISO/out/*.iso \
    -drive file=/tmp/ncde-test.qcow2,if=virtio,format=qcow2 \
    -boot d
# create the blank target disk first:
qemu-img create -f qcow2 /tmp/ncde-test.qcow2 25G
# copy writable OVMF vars first:
cp /usr/share/edk2/x64/OVMF_VARS.4m.fd /tmp/ncde-OVMF_VARS.4m.fd
```

### Acceptance checklist (all must pass)
1. **Live boots to full NCDE desktop, no credentials** (ncde-portal `--autologin --user live`).
   No getty/root-autologin conflict on tty1 (Conflicts= is satisfied; getty drop-in neutralized).
2. **Boot menu + GRUB theme** read "NCDE Poseidon" / `ncde` theme — **no Arch strings** (Rule 7).
3. **Calamares launches** with the NCDE branding (parchment/ocean/gilt, Captain's-Log slideshow,
   no broken `preview.html`), runs welcome→…→summary, then exec modules.
4. **Install completes** end to end (partition, unpackfs, users, grubcfg, bootloader, shellprocess
   running `post_install.sh` → chroot `chrooted_post_install.sh`).
5. **Post-install correctness:** `ncde-portal.service` enabled (aliases display-manager); grub theme
   copied; `/etc/ncde/xsession` is the real executable (Fix #1 held, not a 644 stub); live autologin
   removed for the installed system.
6. **Reboot into the installed disk → ncde-portal GREETER** (username+password), log in with the
   account created in the Calamares `users` step → full NCDE desktop. Live `live` user absent
   (removeuser ran).
7. **Dock apps resolve** — terminal (qtermwidget6), Chromium, GIMP, LibreOffice, Spotify/Steam
   (flatpak). (Deferred SESSION_HANDOFF §8 cosmetics — `ncde-command` dock entry, panel sizes —
   do NOT block this gate.)

If any item fails: capture the exact failure + logs (`/var/log/Calamares.log` in the VM), fix the
**single** offending artifact in the workspace (rule 4, before/after, approval), rebuild, retest.

---

## 7. Method B (fallback) — repack the shipped ISO

> **🔴 STALE, 2026-07-17: `fix-ownership.sh`'s clone source was `~/ncde-staging/LaPivot/`, which
> no longer exists (see top-of-doc banner). Before running §7 as written, re-point the clone step
> at whatever the live-system-derived build source turns out to be.**

Use only if a usable archiso profile cannot be sourced.

1. **Mount the base ISO** (APPROVAL — sudo loop mount):
   ```bash
   sudo mount -o loop,ro ~/Downloads/archcraft-2026.05.12-x86_64.iso ~/ncde-ISO/mnt/iso
   ```
2. **Copy the ISO tree** (writable) to `~/ncde-ISO/extract/`, preserving everything **except**
   `arch/x86_64/airootfs.sfs` (and its `.sha512`/`.md5`).
3. **Build a new squashfs** — **NOT from the raw tree** (2026-07-07: the tree is uid-1000 with
   zero suid bits — see the §0a supersede banner). First run `sudo bash ~/ncde-ISO/fix-ownership.sh`
   (clones tree → `~/ncde-ISO/airootfs-root/`, restores ownership/modes from live, self-verifies),
   then `sudo setcap cap_sys_nice+ep ~/ncde-ISO/airootfs-root/usr/local/bin/LaPivot`, then build
   from `airootfs-root/`. The wildcard list below is the SHORT inline version — §10.3 has the full,
   current, authoritative exclude line re-derived for this tree; use that one, not this example:
   ```bash
   sudo mksquashfs /home/stephen/ncde-ISO/airootfs-root ~/ncde-ISO/extract/arch/x86_64/airootfs.sfs \
       -comp zstd -Xcompression-level 19 -noappend \
       -wildcards -e 'proc/*' 'sys/*' 'dev/*' 'run/*' 'tmp/*' 'mnt/*' \
                  'CLAUDE.md' 'PROJECT.md' '*-PLAN.md' 'SESSION_HANDOFF.md' \
                  'preview.html' 'helpwithisla/*' 'calamares-ncde/*' \
                  'compass7/*' 'src/*' 'build/*'
   ```
   **Do NOT pass `-all-root`** (preserve uid 1000 home). Then regenerate the checksum sidecar files
   that the ISO's boot scripts verify.
4. **Re-author the ISO** with `xorriso` reusing Archcraft's El Torito BIOS + UEFI boot images
   (read the exact `-boot` args from the mounted ISO's structure; copy them verbatim — this is the
   error-prone part). Rule-7 sweep boot-menu titles before authoring.
5. Proceed to the **§6 VM gate** identically.

---

## 8. Approval gate summary (per CLAUDE.md rule 5)
| Gate | Action | Privileged? |
|---|---|---|
| 1 | Install `archiso` toolchain on host | ✅ DONE (`archiso 88-1`) |
| 2 | Stage + Rule-7-clean the archiso profile | file ops (+ maybe sudo) |
| 3 | Overlay build source → airootfs (numeric uids, no `--all-root`) — **source path STALE, was `~/ncde-staging/LaPivot`, tree gone as of 2026-07-17, see top-of-doc banner** | `sudo rsync` |
| 4 | Inject `calamares-ncde` config set | `sudo install/rsync` |
| 5 | `mkarchiso` build | `sudo mkarchiso` |
| 6 | VM boot/install/reboot acceptance test | qemu (no sudo if KVM perms ok) |

## 9. Open confirms before building
1. ~~Source of the archiso profile (Method A) vs. Method B repack.~~ **RESOLVED → Method B** (no
   Archcraft profile available; base ISO present). See the §0 decision note.
2. **[CONFIRM]** `version` / `etc/arch-release` shipping decision (Rule-7 review — NCDE-INSTALL §8).
3. **[CONFIRM]** Ship `wallpapers/` (top-level)? The per-user NCDE wallpapers already ship via
   `etc/skel`/`home/live` `Pictures/wallpapers`; decide if the top-level `wallpapers/` is also wanted.
4. **[CONFIRM]** Host OVMF firmware path for the qemu UEFI test (§6).

---

## 10. BUILD MANIFEST — every file NCDE needs on install (authoritative — STALE, needs re-verification, see below)

> **🔴 STALE SOURCE TREE, flagged 2026-07-17: this entire manifest (10.1-10.3) was "re-derived
> against the production tree 2026-07-04 (session 69)" — that tree, `~/ncde-staging/LaPivot/`, does
> not exist anymore (dev machine gone; confirmed absent on this machine and the USB backup; see the
> banner at the top of this doc). The file list below is NOT being rewritten or re-derived here —
> it's the last real derivation we have and is likely still close to correct (binary names, QML
> dir, fonts, and services haven't changed just because the tree is gone), but it must be treated as
> an unverified starting point, not authoritative, until re-checked against the current process.**
> **To actually re-verify it:** re-run the file-by-file trace and the §10.3 mksquashfs dry-run
> against whatever the live system + `~/my-project/files/ncde-full-patch-20260711.sh` currently
> produce as the install-bound tree — there is no `~/ncde-staging/LaPivot/` to point `pacman -Qq
> --root`, the rsync in §3.2, or the mksquashfs source at anymore. Concretely that means: (1)
> establish a fresh clone/snapshot of the live system's relevant paths (`/usr`, `/etc`, `/var`,
> `/boot`, `/home/live` + the deployed binaries) as the new squashfs source, (2) apply
> `ncde-full-patch-20260711.sh` to it so it reflects every folded-in fix, (3) re-run the §10.1
> presence checks and the §10.3 exclude-list dry-run against that fresh tree, not against notes.
> Until that's done, do not trust this manifest for an actual ISO rebuild.

Original file-level trace done 2026-06-21 against the old tree (0 missing / 398 files) — the
CONTENT list below (10.1) is carried over as still-representative of what NCDE needs (binary names,
QML dir, fonts, services haven't changed), but the 398-file count itself was never re-run against
`~/ncde-staging/LaPivot/` — **re-run the file-by-file trace before the next real build, don't trust
the old count.** Build the squashfs from `~/ncde-staging/LaPivot/` (re-derived 2026-07-04, tree now
gone — see the stale-source-tree flag above) and this is a starting-point manifest of the contents,
not a re-verified one. Ownership was correct in that tree (`root:root` system, `1000:1000`
home/live) — whatever tree replaces it, do **not** `--all-root`.

### 10.1 MUST be in the squashfs (all `root:root` unless noted)
**Binaries**
- `usr/bin/` — `ncde-portal`, `ncde-portal-helper`, `ncde-lock`, `ncde-lock-xss`, `ncde-screensaver-notify`
- `usr/local/bin/` — **`LaPivot`** *(the production WM — was missing from this list entirely; the
  old tree pre-dated LaPivot and this manifest was never updated after the pivot)*, `ncde-wm`
  *(kept only as the legacy fallback binary — CLAUDE.md: "never overwrite," not the one that runs)*,
  `ncde-x11-session` *(carries the settings-promote hook)*, `ncde-terminal`, `ncde-command`,
  `ncde-sentinel`, `ncde-chromium`, `ncde-chromium-sync.sh`, `nncde-x11-session`, plus `orchidee`,
  `verve-text`, `binnie`, `magpie-talker` (dock apps). **Explicitly exclude every other file in this
  directory** — as of 2026-07-04 that's ~19 stale `.prebak-*`/`.rebuilt-broken-*`/`.restored-from-*`
  binary variants that must never ship (see §3.3/§10.3).

**Data / assets / UI**
- `usr/share/ncde/` — **265 files** (all `*.qml`, `*.js`, `controls/`, `avatars/`, `shaders/`,
  `chromium/`, assets, `NCDE Settings Manual.html`). This is the whole desktop UI.
- `usr/share/fonts/ncde/` — 19 fonts · `usr/share/icons/NCDE-Poseidon/` — cursor/icon theme
- `usr/share/grub/themes/ncde/` — 20 files (compass3 GRUB theme, used by the installed system; stock `starfield/` also ships via the grub package, unused)
- `usr/local/share/ncde-terminal/` — `qml/`, `shell-integration/` (5 files)
- `usr/share/applications/` — `ncde-chromium.desktop`, `ncde-terminal.desktop`
- `usr/share/xsessions/ncde.desktop` · `usr/share/dbus-1/services/org.ncde.KickassGuard.service`

**System config / services**
- `usr/lib/systemd/system/ncde-portal.service` · `usr/lib/systemd/user/ncde-sentinel.service`
- `etc/systemd/system/ncde-portal.service.d/autologin.conf` *(live autologin → user `live`;
  removed on install by `chrooted_post_install.sh`)*
- `etc/systemd/system/display-manager.service` → `ncde-portal.service` *(symlink)*
- `etc/systemd/system/graphical.target.wants/ncde-portal.service` *(symlink)*
- `etc/pam.d/` — `ncde-portal`, `ncde-portal-autologin`, `ncde-portal-greeter`, `ncde-lock`
- `etc/picom.conf` · `etc/X11/xorg.conf.d/10-ncde.conf`
- `etc/ncde/xsession` *(portal PAM helper execs it; present in tree, absent on live host — keep the tree copy)*
- `var/lib/ncde-portal/` *(greeter user home — ensure dir exists/owned correctly)*

**Per-user config — present in BOTH `etc/skel/` and `home/live/` (`home/live` = `1000:1000`)**
- `.config/ncde/` — the JSON settings set (dock, theme, wallpaper, display, font, input, power,
  privacy, sound, storage, datetime, notifications, color/section/widget colors, session-defaults, …)
- `.config/ncde-terminal/config.json`
- `.themes/NCDE/` (gtk-3.0) · `.local/share/ncde/themes`
- `.config/systemd/user/default.target.wants/ncde-sentinel.service` *(user-service enable symlink)*
- `Pictures/wallpapers/NCDE*.png` — 26 wallpapers

### 10.2 MUST be EXCLUDED from the squashfs
- `**/*.prebak*` — LaPivot's tree has ~210 `.prebak`/`.prebak-<description>` files as of 2026-07-04
  (this project's standing per-session backup convention, far more than the old tree's 50 — count
  will keep growing every session, don't hardcode a number). **Not used; never ship.**
- Stale binary variants in `usr/local/bin/`: `*.prebak-*`, `*.rebuilt-broken-*`, `*.restored-from-*`
  (~19 as of this pass — see §10.1's note; the exact-name whitelist there is the real guarantee).
- **`compass7/**` and `src/**`** — C++ source + per-app build directories (new vs. the old tree,
  which had no source in the rootfs at all). The compiled binaries these produce already live in
  `usr/local/bin/`/`usr/bin/` and ship from there.
- `**/*.tmp` (esp. `.config/ncde/*.json.tmp`) — settings scratch; the promote-hook handles them at runtime.
- `var/cache/ncde/qmlcache/**` — compiled QML cache; **regenerates per-machine** on first login
  (this is also why the bottom-panel/dock fixes "take" on a fresh install).
- Top-level workspace docs: `CLAUDE.md`, `PROJECT.md`, `*-PLAN.md`, `SESSION_HANDOFF.md`, `preview.html`
- Top-level dev shell scripts: `check_session.sh`, `complete_checklist.sh`, `install_hooks.sh`,
  `log_command.sh`, `require_search_for_uncertainty.sh`, `settings.json`, and this tree's newer
  ad-hoc `deploy-*.sh`/`revert-*.sh` per-session scripts (new vs. the old tree's list).
- `calamares-ncde/` as a **top-level dir** — it is injected to `etc/calamares/` separately (§4); do
  not ship it at `/calamares-ncde`.
- `helpwithisla/**` — read-only Archcraft reference.
- Virtual filesystems: `proc/ sys/ dev/ run/ tmp/ mnt/`.
- **[CONFIRM/Rule-7]** `version`, `etc/arch-release` — Arch-identifying; resolve in a separate Rule-7 review.
- **[UNRESOLVED, new this pass]** `/ncde-wm` — a top-level DIRECTORY (not the binary of the same
  name in `usr/local/bin/`) exists at the LaPivot tree root; purpose not confirmed. Exclude by
  default pending confirmation — do not ship an unidentified top-level directory.

### 10.3 mksquashfs exclude line (Method B, §7.3) — drop-in  *(RE-DERIVED 2026-07-04 for LaPivot)*
> **BUG in the original line (fixed 2026-06-21, still holds):** mksquashfs excludes are ANCHORED to
> the source root unless prefixed with `...`. Use non-anchored `'... *.prebak*'` etc. Exclude a
> directory as `dir` (NOT `dir/*` — the latter ships an empty directory stub). Keep
> `proc/sys/dev/run/tmp/mnt/*` and `qmlcache/*` as `/*` (those empty mount/cache dirs MUST exist).
> **New this pass:** `compass7`/`src` (source+build dirs) and a broadened prebak/broken-binary
> pattern — LaPivot's tree carries real dev material the old tree never had in the rootfs at all.
```
-wildcards -e 'proc/*' 'sys/*' 'dev/*' 'run/*' 'tmp/*' 'mnt/*' \
   'var/cache/ncde/qmlcache/*' \
   'helpwithisla' 'calamares-ncde' 'wallpapers' 'compass7' 'src' 'build' 'ncde-wm' \
   'version' \
   'etc/calamares/branding/archcraft' 'var/lib/pacman/sync/archcraft.db' 'etc/arch-release' \
   '... *.prebak*' '... *.tmp' '... *.rebuilt-broken-*' '... *.restored-from-*' \
   '... *.wrong-*' '... *.bak' '... *.orig' '... *.swp' '... *.brokenhtml-*' \
   '... __pycache__' \
   'usr/bin/ollama' 'usr/share/ollama' 'usr/lib/ollama' 'usr/share/licenses/ollama' \
   'var/lib/ollama' 'var/lib/pacman/local/ollama-*' 'opt/ncde-chroma' \
   'usr/local/bin/kickass-guard' 'usr/local/lib/ncde/ncde-vesper-provision.sh' \
   'usr/lib/systemd/system/ollama.service' 'usr/lib/systemd/system/chroma.service' \
   'usr/lib/systemd/system/kickass-guard.service' \
   'usr/lib/systemd/system/ncde-vesper-provision.service' \
   'usr/lib/tmpfiles.d/ncde-kickass.conf' \
   'usr/lib/sysusers.d/ollama.conf' 'usr/lib/tmpfiles.d/ollama.conf' \
   'usr/share/factory/etc/arch-release' \
   'usr/share/dbus-1/services/org.ncde.KickassGuard.service' \
   'usr/local/share/dbus-1/services/org.ncde.KickassGuard.service' \
   'usr/lib/systemd/user/ncde-sentinel.service' \
   'usr/bin/ncde-terminal' \
   'usr/local/bin/ncde-tauri-installer' \
   'usr/share/ncde/GliaDocPopup.' 'usr/share/ncde/MagpieTalker' \
   'usr/share/ncde/NCDESettings' 'usr/share/ncde/SpacePanel.qm' \
   'CLAUDE.md' 'PROJECT.md' 'NCDE-CALAMARES-PLAN.md' 'NCDE-INSTALL-PLAN.md' \
   'ISO-BUILD-PLAN.md' 'SESSION_HANDOFF.md' 'preview.html' \
   'check_session.sh' 'complete_checklist.sh' 'install_hooks.sh' \
   'log_command.sh' 'require_search_for_uncertainty.sh' 'settings.json' \
   '... deploy-*.sh' '... revert-*.sh'
```
> **RE-DERIVED AGAIN 2026-07-07 (final ISO audit) — the additions above close every gap the
> audit found actually present in the tree:** the 4 truncated-name QML fragments (exact names —
> `'usr/share/ncde/MagpieTalker'` in -wildcards mode matches only that exact path, NOT
> `MagpieTalker.qml`); the 3 `*.wrong-20260704-rewire` terminal-QML files; `__pycache__`
> (3 in ship paths + 899 under opt/ncde-chroma); `*.bak/*.orig/*.swp` (ncde-wm.bak 20MB etc.);
> the 5 quarantined `*.ttf.brokenhtml-20260704` HTML-not-font files; the ENTIRE inert LLM
> stack (ollama 34MB + chroma venv + kickass-guard 8.5MB + their 4 system units + the
> KickassGuard D-Bus activation file — Vesper's real non-LLM brain
> `usr/lib/ncde/vesper/brain_server.py` + `vesper-brain.service` + `usr/local/bin/ncde-vesper`
> still SHIP); the stale user-scope `ncde-sentinel.service` (the system unit ships and is
> enabled); the top-level `ncde-wm/` dir and root `version` file (§10.2 flagged both, the old
> line omitted them); the tree-only stale `usr/bin/ncde-terminal` orphan (the real terminal is
> `usr/local/bin/ncde-terminal`, live has no /usr/bin copy); and the old Tauri installer
> binary. `usr/local/bin/{choose-mirror,livecd-sound}` are live-ISO helpers Archcraft ships —
> KEPT (their units are disabled on install by chrooted_post_install.sh);
> `Installation_guide`/`ncde-installer-session`/`cal-reminders` are on the operator-decision
> rm list (punchlist §3.1), not silently excluded — cal-reminders is likely LeapFrog's
> reminder runner, do NOT exclude it without checking.
> **The same list lives in rsync syntax as `~/ncde-ISO/airootfs-excludes.txt`** (consumed by
> `fix-ownership.sh` at the clone step, so junk never even reaches `airootfs-root/`; this
> mksquashfs line is the second net). **Dry-run-proven 2026-07-07**: 0 paths in every junk
> class, 22/22 must-ship spot checks present, the 6 empty mount-point dirs kept, 326,707
> paths shipping. When either list changes, change BOTH and re-run the dry-run proof.
Carried over from the old tree's derivation: the workspace hook scripts + `settings.json` (would
ship to `/`); Archcraft remnants (`branding/archcraft`, `archcraft.db`) + `arch-release` (Rule 7);
`wallpapers` (per-user copies already ship via `home/live`/`etc/skel`). **NOTE, not re-verified this
pass:** `/var/lib/flatpak` (Steam + runtimes) and system fonts were MISSING from the OLD tree and had
to be rsync'd in before building — **re-check whether LaPivot's tree already has these** (it may,
being a newer/different consolidation) before assuming the same manual step is still needed.
**Do NOT pass `-all-root`** (preserve `home/live` uid 1000). Then regenerate the ISO's checksum
sidecars (§7.3) and re-author with `xorriso` (§7.4).

---

## 11. BUILD-READINESS GATE — ALL boxes verified (not assumed) before `mksquashfs`. No partial ships.
**Why this exists:** ~18 prior builds shipped broken because work was shipped before the tree was complete,
and because handoff notes were trusted instead of verified against the tree. **The cure: ONE build, gated
on this list.** Every item is a read-only check. Run the check; build only when ALL pass. (Operator's
directive 2026-06-22: recovery built + everything polished BEFORE ship — get it right once.)

### Boot layer (extract/)
- [~] Plymouth=ncde — RE-OPENED 2026-07-01. The original `[x]` was based on the built
  `initramfs-linux-zen.img` existing at a certain size, not on confirming the splash actually
  renders. Verified against the tree (both LaPivot and `[dead-legacy-tree]` — identical, not a LaPivot
  regression): `/etc/plymouth/plymouthd.conf` sets `Theme=ncde`, `usr/share/plymouth/themes/ncde/`
  exists, and the `plymouth` mkinitcpio hook files ARE present
  (`usr/lib/initcpio/{hooks,install}/plymouth`) — but `etc/mkinitcpio.conf`'s `HOOKS=` line does
  **not** include `plymouth`:
  `HOOKS=(base systemd autodetect microcode modconf kms keyboard sd-vconsole block filesystems fsck)`.
  Without that hook, Plymouth doesn't get pulled into the initramfs regardless of the theme config.
  Not yet build-tested to see what actually happens at boot — this is a static-config finding only.
- [x] BIOS parchment splash — `splash.png` = **410776**; wording "Start NCDE Poseidon"; consumer help; timeout 3
- [ ] Volume label `ARCHCRAFT_202605` → `NCDE_202606` (done during §D authoring)

### Branding / polish in tree
- [x] compass4 Calamares slideshow → `etc/calamares/branding/ncde` — DONE 2026-06-22 (slide1-4 in, root:root, no preview.html)
- [x] compass3 `grub-theme-ncde` → `usr/share/grub/themes/ncde` — DONE (post-install copies `themes/ncde`; `GRUB_THEME` set). Font polish (DejaVu .pf2) deferred — verify look in §E.
- [ ] installer fonts resolve (Cinzel/Cormorant/IM Fell/JetBrains — files present; confirm family names)

### Install experience (Calamares — btrfs + consumer)
- [x] partition.conf: btrfs, `allowManualPartitioning:false`, `initialPartitioningChoice:erase` — DONE (verified)
- [ ] btrfs subvolume layout incl. `@restore` (lands with recovery #9)
- [x] target `/etc/mkinitcpio.conf` includes `btrfs` — DONE (`MODULES=(btrfs)`)

### Recovery "Soundings" (BEFORE ship — the long pole)
- [ ] backend compiled to the contract → `usr/local/bin/ncde-recovery`
- [ ] `ncde-snapshot` (boot snapshot, keep 7) + `ncde-rollback` installed + helpers tested
- [ ] systemd: boot-snapshot service + recovery-VT service enabled
- [ ] Ctrl+Alt+T → recovery VT bound; works with NO X (linuxfb/eglfs)
- [ ] PAM `ncde-restore`; admin-seal verified; full snapshot→restore→reboot tested
- [ ] QML installed → `usr/share/ncde/recovery/`

### Completeness + ownership (the actual 18-build killers)
- [x] ownership: `home/live`=1000:1000, system=root:root; **NEVER `-all-root`**
- [x] greeter user `ncde-portal` present (961:961)
- [ ] re-confirm completeness at FILE level: `/var/lib/flatpak`, system fonts, every NCDE app/dbus/
      service/PAM, `usr/share/ncde`=265, btrfs-progs

### Only when every box above is green:
§B `mksquashfs` (final excludes, no `-all-root`) → §C `sha512` → §D author **FROM `extract/`** + relabel → §E VM test gate.
