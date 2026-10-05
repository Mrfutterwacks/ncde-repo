# NCDE-CALAMARES-PLAN.md — the NCDE Poseidon Calamares set (current state)

> **🔴 TREE UPDATE (2026-07-05, operator): `~/ncde-staging/LaPivot/` is THE production tree — the
> ONLY tree. The old frozen tree is DEAD; its path is struck below as `[dead-legacy-tree]`. Any
> "verified"/file-count claim below that was checked against the dead tree is UNVERIFIED against
> the production tree until re-checked there. The rootfs/overlay source for installer work is
> `~/ncde-staging/LaPivot/`.**
>
> **⚠️ SUPERSEDED (corrected 2026-07-17):** the above is itself now stale — `~/ncde-staging/` does
> not exist anymore either, on this machine or the USB backup; the dev machine that hosted it is
> gone. There is no production tree at all now. The **live running system** (`/usr/local/bin/LaPivot`,
> `/usr/share/ncde/`) is the only copy and the actual rootfs/overlay source for installer work.
> Anything below that names `~/ncde-staging/LaPivot/` as a current location should be read as
> "wherever the file-list/behavior it describes is verified live today" — re-check against the live
> system, not that path, before trusting it.

Status: **describes the existing implementation.** This replaces the earlier "how to adapt
Archcraft" draft — that adaptation now **exists** as a concrete config set.

> **🔄 UPDATE (2026-06-22) — btrfs + consumer install + restore app + boot branding. Read
> SESSION_HANDOFF "LATEST SESSION" first.**
> - **Filesystem: every install is btrfs** (was ext4). `etc/calamares/modules/partition.conf`:
>   `defaultFileSystemType: btrfs`, `allowManualPartitioning: false`, `initialPartitioningChoice: erase`
>   → consumer "Erase disk & install" (no `/dev/sdX`, no mountpoints, nobody can pick ext4). Layout:
>   btrfs root + subvolumes `@` (system), `@home`, `/restore` (RO snapshots for the time machine).
>   **[PENDING edit — root-owned, operator sudo.]**
> - **System Restore "Soundings"** (btrfs time machine) is being rebuilt; if bundled it must install into
>   the tree **before §B** — see `NCDE-RECOVERY-APP.md` / `~/ncde-ISO/ncde-recovery-app/`.
> - **Branding refreshed (compass4):** full `branding/ncde/` incl. premium `slide1-4.png` slideshow +
>   updated `show.qml`/`stylesheet.qss`/art — **[PENDING integration]** into `etc/calamares/branding/ncde`.
> - **Installed-system GRUB:** parchment `grub-theme-ncde` (compass3) — post-install copies it;
>   **[PENDING install]** into the tree `usr/share/grub/themes/`.
> - **Boot menu fully de-Arched** (parchment splash, "Start NCDE Poseidon", consumer help text) — done in
>   `extract/` (NOT the squashfs). §D must author **FROM `extract/`**, not replay-from-base.

> **🔄 BUILD-SESSION UPDATE (2026-06-21, latest):** Calamares set injected into the tree & verified;
> Fixes #1–#4 confirmed in the *installed* scripts. Completeness audit found the §7.5 runtime list was
> incomplete at a higher level — **the entire `/var/lib/flatpak` layer (Steam + runtimes) and the
> system fonts (`noto`/`gsfonts`/…) were absent from the tree** and were rsync'd in from the host.
> NCDE desktop otherwise verified complete (apps, security app, dbus, services, PAM, 265/265 UI).
> Archcraft remnants + `arch-release` excluded from the squashfs; Arch→NCDE rebrand done. See
> SESSION_HANDOFF "⏩ BUILD SESSION UPDATE" and `~/NCDE-BUILD-COMMANDS.md` for the resume commands.
>
> **🔄 UPDATE (2026-06-21, late) — open confirms below are now RESOLVED.** Read SESSION_HANDOFF §0–§5
> and ISO-BUILD-PLAN §10 (Build Manifest) first; they supersede the open items here.
> - **§7.5 missing packages — DONE.** All installed into the rootfs (DB 576→683): qtermwidget,
>   qt6-base, chromium, gimp, libreoffice-fresh, flatpak, spotify.
> - **§7 IM Fell fonts — DONE.** Real TTFs present (`IMFellDWPica*`, `IMFellEnglish*`, `IMFellDWPicaSC`).
> - **§7.6 autologin — CONFIRMED & SHIPPED.** Drop-in `etc/systemd/system/ncde-portal.service.d/
>   autologin.conf` = `--autologin --user live --pam-service ncde-portal-autologin`; the `live` user
>   (uid 1000, zsh, `wheel`) exists in `etc/passwd`; `ncde-portal` is the DM
>   (`display-manager.service` + `graphical.target.wants` symlinks). Removed on install by the script.
> - **Note on the dev host:** the running desktop is NCDE but is launched by **sddm →
>   `ncde-x11-session`** here (a dev-host detail). The product DM is `ncde-portal`, wired as above.
> - **Source tree was lost** from the dev machine (wiped by failed builds; system restored from USB
>   squashfs). **Corrected 2026-07-17:** it is still lost — no copy exists anywhere, including the
>   `compass(7).zip`/`compass7-reference` handoff bundle (its `Lelan.cpp` is a ~500-line stubbed
>   reimplementation attempt, not the real ~4,835-line engine). Recovery is via **Ghidra-decompiling
>   the live `/usr/local/bin/LaPivot` binary**, reconstructed class-by-class in `~/ncde-wm-rebuild/`
>   (the 2026-06-21 `~/ncde-staging/ncde-wm-rebuild/src/decompiled/` path is gone) — **partial**, most
>   classes still raw decompiled output, not clean buildable source (see `docs/lapivot-rebuild.md`).
>   Either way, irrelevant to the build — install runs built artifacts, not a compiler. See
>   SESSION_HANDOFF §1.
> - **`[dead-legacy-tree]` is now the consolidated single source of truth** (verified 398 files, 0 missing;
>   ownership `root:root` / `1000:1000`).

## Where the implementation lives
- **Scaffold (Path B):** `~/Downloads/calamares-ncde/` — the NCDE-ified Calamares config set
  (settings, shellprocess module, branding dir, post-install scripts). **Stephen provided this
  scaffold.** README declares Isla/Tauri abandoned; **the installer IS Calamares.**
- **NCDE runtime tree:** `[dead-legacy-tree]/` — full rootfs overlay with the binaries/assets the installed
  system needs (`usr/bin/ncde-portal`, `usr/local/bin/ncde-wm | ncde-x11-session`, `etc/ncde/`,
  `etc/pam.d/ncde-portal*`, `usr/lib/systemd/system/ncde-portal.service`,
  `usr/share/grub/themes/ncde`, `usr/share/fonts/ncde/`).
- **Archcraft reference (read-only):** `[dead-legacy-tree]/helpwithisla/calamares-reference/`.

## Delivery model
- No online repo / no PKGBUILD — **NCDE is a file-tree overlay** baked into `airootfs.sfs`.
- The live system **is** the installed system. Calamares installs **no packages**; it partitions,
  unpacks the squashfs, creates the user, configures boot, then runs the NCDE post-install.
- **Boot = like Archcraft:** live medium autologins into the full NCDE desktop; the installed
  system shows the **ncde-portal greeter** → login → full desktop.

---

## 1. File layout (scaffold → ISO target paths)
```
calamares-ncde/
├── settings.conf                -> /etc/calamares/settings.conf
├── modules/shellprocess.conf    -> /etc/calamares/modules/shellprocess.conf
├── scripts/post_install.sh          -> /usr/bin/post_install.sh          (chmod +x)
├── scripts/chrooted_post_install.sh -> /usr/bin/chrooted_post_install.sh (chmod +x)
└── branding/ncde/               -> /etc/calamares/branding/ncde/
    ├── branding.desc  show.qml  stylesheet.qss  NCDEMedallion.qml
    ├── logo.png  welcome.png  compass.png  island.png  parchment.png
    └── preview.html             (DEV ARTIFACT — do NOT ship to target)
```

## 2. `settings.conf` — sequence & branding
- `branding: ncde`. No `packagechooser`, no `contextualprocess` instances (single desktop).
- **show:** welcome → locale → keyboard → partition → users → summary → (exec) → finished.
- **exec:** partition, mount, unpackfs, machineid, fstab, locale, keyboard, localecfg, initcpiocfg,
  initcpio, users, displaymanager, networkcfg, hwclock, services-systemd, **shellprocess**, grubcfg,
  bootloader, preservefiles, umount.
- Behavior: `prompt-install:false`, `dont-chroot:false`, `quit-at-end:false`.

## 3. `modules/shellprocess.conf`
- `dontChroot: true`, `timeout 9999`, runs `/usr/bin/post_install.sh`.
- i18n name = Captain's-Log line: `"Charting the new realm — configuring your system…"`.

## 4. Post-install scripts (verbatim in appendix)
- **`post_install.sh`** — unchanged from Archcraft except branding: GPU detect on the live system,
  then `chroot` (not arch-chroot) into target and run `chrooted_post_install.sh`.
- **`chrooted_post_install.sh`** — Archcraft logic, NCDE-adapted:
  - `sddm.service` → **`ncde-portal.service`** (enable list).
  - **creates the `ncde-portal` greeter user** (`useradd --system …`) — required or the unit loops.
  - grub theme `archcraft` → **`ncde`**.
  - sets the desktop session (writes `/etc/ncde/xsession`) — **see Fix #1**.
  - removes the **live autologin drop-in** (`/etc/systemd/system/ncde-portal.service.d/autologin.conf`).
  - ensures `ncde-x11-session`/`ncde-wm` executable + `/var/cache/ncde/qmlcache` exists.
  - lightdm/lxdm/sddm autologin + `sddm state.conf` blocks **removed**; `archcraft-hooks-runner`
    **removed**. VM/driver/ucode cleanup, package removal, live-file cleanup, journald/pam — kept.

---

## 5. Fixes required before an ISO build

**Fix #1 — `/etc/ncde/xsession` clobber (chrooted_post_install.sh ~lines 289–291). HIGH.**
The script does `echo 'ncde-x11-session' > /etc/ncde/xsession; chmod 644`. But the real
`/etc/ncde/xsession` shipped in the overlay is an **executable `#!/bin/sh` script the portal's PAM
helper `exec`s** (sets X env, sources profiles, `exec "$@"` → `ncde-x11-session`). Overwriting it
with a one-line string at mode 644 replaces a working session entry point with a non-executable
stub → session won't launch. **Action:** remove that write (the squashfs already ships the correct
file); at most `chmod +x` it. Keep the `qmlcache` dir creation.

**Fix #2 — dropped Calamares modules to sanity-check.**
- **`removeuser`** is absent from the sequence → the live ISO user may persist on the installed
  system. Confirm the live user is otherwise removed, or re-add `removeuser` to `exec`.
- **`displaymanager`** is *present*, but Calamares' module only knows a fixed DM list (sddm/lightdm/
  gdm/…) — it won't recognize `ncde-portal`. Since the post-install enables `ncde-portal.service`
  directly, **consider dropping `displaymanager`** to avoid a confusing failure/no-op.
- **`luksbootkeyfile` / `luksopenswaphookcfg`** dropped → **no encrypted-install support** (fine
  for first build; flag if LUKS wanted).

**Fix #3 — placeholder package names** in `_remove_unwanted_packages`
(`ncde-install-scripts`/`ncde-installer`/`ncde-welcome`) are guesses — harmless no-ops if absent,
but confirm the real installer-package names (if any) or leave as no-ops.

**Fix #4 — grub theme wiring.** Script copies `…/themes/ncde` to `/boot/grub/themes`, but the
kept `grubcfg` module must point grub at it (`GRUB_THEME=…/ncde/theme.txt`). Verify
`grubcfg.conf`/default grub config sets the theme.

---

## 6. Appearance (branding/ncde) — matches `preview.html`

`preview.html` is the design source (a 900×560 mock; **dev artifact, not shipped**). The QSS/QML
port it faithfully. Palette & type:

| Token | Value | In QSS/QML |
|---|---|---|
| Parchment body | `#e8d6a9` | qss `#mainApp` |
| Abyss sidebar | `#020608` | qss `#sidebarApp` + branding.desc `sidebarBackground` |
| Gilt accent / progress | `#b88a2c` / `#e2c772` | qss sidebar-select, `QProgressBar::chunk` |
| Burgundy primary | `#6b2018` | qss `QPushButton:default` |
| Ink text | `#2a1a08` | qss `QLabel` |
| Ocean slideshow | `#0c2a3a→#051724→#020608` | show.qml (all slides) |

- **`branding.desc`** — `NCDE Poseidon 14.2 "Trident"`, ncde.io URLs, 900×560 window, `slideshowAPI 2`.
- **`stylesheet.qss`** — skins wizard chrome/buttons/inputs/progress/checkboxes; correct Calamares
  object names. (One inert selector: `[aria-selected="true"]` — not a Qt property; the adjacent
  `:checked` is what styles the current step. Harmless; can remove.)
- **`show.qml`** — 3 Latin-eyebrow slides (text identical to the HTML), ocean gradient, 8s advance,
  correct `onActivate/onLeave` for slideshowAPI 2. Pure QML, no WebEngine.
- **`NCDEMedallion.qml`** — Canvas trident medallion with opacity pulse; **currently unused**
  (nothing imports it). Also an empty `Component { id: slideTemplate }` in show.qml is dead.
  Optional: drop the empty component; consider placing the medallion on slide 1.

## 7. Fonts — shipped locally (no Google Fonts at runtime)
All in `[dead-legacy-tree]/usr/share/fonts/ncde/` (overlaid into squashfs). Status vs the skin's references:

| Family (referenced) | Status |
|---|---|
| **Cinzel** | ✅ family resolves `Cinzel` |
| **JetBrains Mono** | ✅ family resolves `JetBrains Mono` |
| **Cormorant Garamond** | ✅ **added** — variable (wght 300–700) roman+italic; family resolves `Cormorant Garamond` |
| **IM Fell DW Pica / SC** | ⚠️ files present but `fc-scan` returned blank family — **verify** the internal family names match the QSS/QML strings |

Also shipped (NCDE desktop/terminal, not used by the installer skin): Comfortaa, Marcellus,
Cinzel Decorative, IM Fell English, TerminalVector.

---

## 7.5 Runtime dependencies — VERIFIED MISSING from the current NCDE rootfs
Checked against the NCDE pacman DB (`[dead-legacy-tree]/var/lib/pacman/local`, 576 pkgs), the NCDE
`usr/lib`, and the Archcraft base list (`pkglist.x86_64.txt`). These must be added to the squashfs
package set before a build or the dock/terminal break:

| Need | For | Status | Action |
|---|---|---|---|
| **qtermwidget** (Qt6) | `ncde-terminal` (dynamically links `libqtermwidget6.so.2`) | ❌ lib absent, not in DB or base | install `qtermwidget` (Qt6 build) |
| **qt6-base** (+ Qt6 runtime) | qtermwidget6 / any Qt apps; **no `libQt6*` in `usr/lib`** | ❌ not in DB | install `qt6-base` (and the Qt6 modules NCDE needs) |
| **chromium** | dock "Chromium" (`ncde-chromium` wrapper execs `chromium`) | ❌ missing | install `chromium` |
| **gimp** | dock "GIMP" | ❌ missing | install `gimp` |
| **libreoffice** | dock "LibreOffice" | ❌ missing | install `libreoffice-fresh` (or -still) |
| **flatpak** | dock "Steam" (`flatpak run com.valvesoftware.Steam`), likely Spotify | ❌ missing | install `flatpak` (+ pre-add the Steam/Spotify flatpaks, or change the dock entry) |
| **spotify** | dock "Spotify" | ❌ no pacman pkg | AUR `spotify` or a Spotify flatpak |

Present and fine: **gtk3** runtime; all custom NCDE binaries (`ncde-terminal`, `orchidee`,
`verve-text`, `binnie`, `magpie-talker`, `ncde-chromium`). Note `ncde-chromium` is a 1 KB wrapper —
it still needs `chromium` itself installed.

> Caveat: `[dead-legacy-tree]` may be an in-progress rootfs; if these are intended to be pulled in at
> ISO-build time (airootfs `packages.x86_64`), confirm that list includes the above. As captured
> now, none are satisfied.

## 7.6 Autologin — "full desktop on boot" (design + correction)

### Correction to the earlier autologin assumption
Earlier notes (and the scaffold) assumed live→installed autologin toggles via
`/etc/systemd/system/ncde-portal.service.d/autologin.conf`. **That file does not exist** — not in
the rootfs, not on the host. The autologin that actually ships is a **getty** drop-in,
`[dead-legacy-tree]/etc/systemd/system/getty@tty1.service.d/autologin.conf`:
```ini
[Service]
ExecStart=
ExecStart=-/usr/bin/agetty --noreset --noclear --autologin root - ${TERM}
```
→ getty autologins **root** on tty1 (live-medium style). Consequences:
- The scaffold's `chrooted_post_install.sh` line
  `rm -rf /etc/systemd/system/ncde-portal.service.d/autologin.conf` is currently a **no-op**.
- The real live→installed switch is already handled by `_clean_target_system`, which deletes
  `/etc/systemd/system/getty@tty1.service.d`.

### Portal facts (verified)
- `ncde-portal.service` exists (host + rootfs). On **this dev host** the active DM is **sddm**
  (`display-manager.service → sddm.service`); ncde-portal is **disabled/inactive** here.
- `ncde-portal` binary flags include: `--autologin`, `--user`, `--pam-service`, `--greeter-user`,
  `--daemon`, `--vt`, `--display`, `--lock`, `--screensaver`, `--season`; permissive PAM stack
  `ncde-portal-autologin` exists.
- Baseline ExecStart: `/usr/bin/ncde-portal --daemon --vt vt01 --display :0 --greeter-user ncde-portal`.
- **No uid≥1000 user** in the rootfs `etc/passwd`, yet `home/live` exists → intended autologin user
  is presumably **`live`**, but that account isn't created yet. **[CONFIRM]**

### Plan: make ncde-portal autologin (preferred — graphical-native)
Ship a drop-in in the **live squashfs** overriding ExecStart to add autologin; the installer then
removes it (which finally makes the scaffold's removal line meaningful). Proposed
`[dead-legacy-tree]/etc/systemd/system/ncde-portal.service.d/autologin.conf`:
```ini
[Service]
ExecStart=
ExecStart=/usr/bin/ncde-portal --daemon --vt vt01 --display :0 \
          --greeter-user ncde-portal --autologin --user live \
          --pam-service ncde-portal-autologin
```
**[CONFIRM] exact flag spec** — `--autologin` looks like a boolean paired with `--user <name>` and
`--pam-service ncde-portal-autologin`; verify via `ncde-portal --help` before shipping.

Result (confirmed by Stephen — "just like Archcraft"):
- **Live boot:** ncde-portal autologins the live user → full NCDE desktop, **no credentials**
  (matches Archcraft's "desktop on boot").
- **After install:** autologin is gone. The installed system **requires username + password** at
  the ncde-portal greeter — and that account is the one **created during the Calamares `users`
  step**. Identical to Archcraft (live = passwordless desktop; installed = real login).
- Mechanism: `chrooted_post_install.sh` removes the live autologin drop-in on install → greeter.

### Required companion steps
1. **One live autologin path, not both.** `ncde-portal.service` has `Conflicts=getty@tty1.service`;
   if ncde-portal is the live DM, remove/disable the getty root-autologin drop-in in the live env
   so two mechanisms don't fight for tty1.
2. **Create the `live` user** in the live squashfs (uid≥1000, home `/home/live`), and **enable**
   `ncde-portal.service` in the live env (`WantedBy=graphical.target`, `Alias=display-manager.service`).
3. Keep autologin **off the installed system** (greeter) — handled by removing the drop-in on install.
4. Do **not** autologin `root` graphically (the current getty drop-in logs in root — fine for a
   console live shell, wrong for a desktop session).

### Open decisions
- [CONFIRM] autologin user = `live`? create that account in the live squashfs.
- [CONFIRM] `--autologin`/`--user`/`--pam-service` exact syntax via `ncde-portal --help`.
- [DECIDE] live DM = ncde-portal (recommended) vs. keep getty-autologin-root + startx.

## 8. Build order (working-first, per README)
1. Overlay scaffold files to the ISO paths in §1 (`chmod +x` the scripts); overlay `[dead-legacy-tree]` tree.
2. Apply Fixes #1–#4; verify IM Fell family names (§7).
3. Ship Calamares + these configs → build ISO.
4. Install on a VM; confirm it completes and boots to the **ncde-portal greeter**, then desktop.
5. Polish appearance (medallion, slide art) once functional.

## 9. Open confirms / decisions
1. Live autologin drop-in exact path/name (script assumes
   `/etc/systemd/system/ncde-portal.service.d/autologin.conf`) — confirm the live squashfs ships it there.
2. Re-add `removeuser`? Drop `displaymanager`? (Fix #2)
3. Real `_remove_unwanted_packages` names (Fix #3).
4. IM Fell family-name verification (§7).
5. Should this scaffold be **copied into the workspace** (`[dead-legacy-tree]/` + `~/ncde-ISO/`) as the
   working source? It currently lives in `~/Downloads/calamares-ncde/` (outside the workspace).

---

# APPENDIX — Full verbatim NCDE Calamares source

Exact contents of the `calamares-ncde` scaffold (`~/Downloads/calamares-ncde/`). Unmodified.

## settings.conf

~~~~yaml
# SPDX-FileCopyrightText: no
# SPDX-License-Identifier: CC0-1.0
#
# NCDE Poseidon — Calamares settings.
# Single desktop (no WM packagechooser), ncde-portal greeter,
# branding: ncde. Engine = Calamares core modules; the post-install
# shellprocess runs the NCDE adaptation of Archcraft's scripts.

## Modules
modules-search: [ local ]

## Instances
# (No autologin contextualprocess — NCDE autologin is a drop-in removed
#  by chrooted_post_install.sh, not an SDDM config edit.)

## Sequence
sequence:
- show:
  - welcome
  - locale
  - keyboard
  - partition
  - users
  - summary
- exec:
  - partition
  - mount
  - unpackfs
  - machineid
  - fstab
  - locale
  - keyboard
  - localecfg
  - initcpiocfg
  - initcpio
  - users
  - displaymanager
  - networkcfg
  - hwclock
  - services-systemd
  - shellprocess
  - grubcfg
  - bootloader
  - preservefiles
  - umount
- show:
  - finished

## Branding
branding: ncde

## Behavior
prompt-install: false
dont-chroot: false
oem-setup: false
disable-cancel: false
disable-cancel-during-exec: false
hide-back-and-next-during-exec: false
quit-at-end: false
~~~~

## modules/shellprocess.conf

~~~~yaml
# SPDX-FileCopyrightText: no
# SPDX-License-Identifier: CC0-1.0
#
# NCDE Poseidon — Calamares shellprocess (live-system post-install).
# Runs /usr/bin/post_install.sh on the LIVE system (dontChroot: true);
# that script detects the GPU, then chroots into the target and runs
# /usr/bin/chrooted_post_install.sh.
---
dontChroot: true
timeout: 9999
verbose: false
script:
    - command: "/usr/bin/post_install.sh"
i18n:
     name: "Charting the new realm — configuring your system…"
     name[en]: "Charting the new realm — configuring your system…"
~~~~

## scripts/post_install.sh

~~~~bash
#!/bin/bash

## NCDE Poseidon
##
## Post installation script (Executes on live system, only to detect drivers in use).
## Adapted from Archcraft's post_install.sh — kept as-is except branding.

##--------------------------------------------------------------------------------

## Get mount points of target system according to installer being used (calamares or abif)
if [[ `pidof calamares` ]]; then
	chroot_path="/tmp/`lsblk | grep 'calamares-root' | awk '{ print $NF }' | sed -e 's/\/tmp\///' -e 's/\/.*$//' | tail -n1`"
else
	chroot_path='/mnt'
fi

if [[ "$chroot_path" == '/tmp/' ]] ; then
	echo "+---------------------->>"
    echo "[!] Fatal error: `basename $0`: chroot_path is empty!"
fi

## Use chroot not arch-chroot
arch_chroot() {
    chroot "$chroot_path" /bin/bash -c ${1}
}

## Detect drivers in use in live session
gpu_file="$chroot_path"/var/log/gpu-card-info.bash

_detect_vga_drivers() {
    local card=no
    local driver=no

    if [[ -n "`lspci -k | grep -P 'VGA|3D|Display' | grep -w "${2}"`" ]]; then
        card=yes
        if [[ -n "`lsmod | grep -w ${3}`" ]]; then
			driver=yes
		fi
        if [[ -n "`lspci -k | grep -wA2 "${2}" | grep 'Kernel driver in use: ${3}'`" ]]; then
			driver=yes
		fi
    fi
    echo "${1}_card=$card"     >> ${gpu_file}
    echo "${1}_driver=$driver" >> ${gpu_file}
}

echo "+---------------------->>"
echo "[*] Detecting GPU card & drivers used in live session..."

# Detect AMD
_detect_vga_drivers 'amd' 'AMD' 'amdgpu'

# Detect Intel
_detect_vga_drivers 'intel' 'Intel Corporation' 'i915'

# Detect Nvidia
_detect_vga_drivers 'nvidia' 'NVIDIA' 'nvidia'

# For logs
echo "+---------------------->>"
echo "[*] Content of $gpu_file :"
cat ${gpu_file}

##--------------------------------------------------------------------------------

## Run the final script inside calamares chroot (target system)
if [[ `pidof calamares` ]]; then
	echo "+---------------------->>"
	echo "[*] Running chroot post installation script in target system..."
	arch_chroot "/usr/bin/chrooted_post_install.sh"
fi
~~~~

## scripts/chrooted_post_install.sh

~~~~bash
#!/bin/bash

## NCDE Poseidon
##
## Post installation script (Executes on target system to perform various operations).
## Adapted from Archcraft's chrooted_post_install.sh.
##   - sddm.service          -> ncde-portal.service
##   - grub theme archcraft  -> ncde (NCDE theme dir)
##   - openbox default sess. -> /etc/ncde/xsession (ncde-x11-session)
##   - archcraft-hooks-runner -> removed (no such tool in NCDE)
##   - lightdm/lxdm/sddm autologin + sddm state.conf blocks -> removed
##   + NEW: create ncde-portal greeter user, remove live autologin drop-in,
##          ensure ncde-x11-session is executable + qml cache dir exists.
## Everything else kept exactly as Archcraft does.

## -----------------------------------------------

# Get new user's username
new_user=`cat /etc/passwd | grep "/home" | cut -d: -f1 | head -1`

# Check if package installed (0) or not (1)
_is_pkg_installed() {
    local pkgname="$1"
    pacman -Q "$pkgname" >& /dev/null
}

# Remove a package
_remove_a_pkg() {
    local pkgname="$1"
    pacman -Rsn --noconfirm "$pkgname"
}

# Remove package(s) if installed
_remove_pkgs_if_installed() {
    local pkgname
    for pkgname in "$@" ; do
        _is_pkg_installed "$pkgname" && _remove_a_pkg "$pkgname"
    done
}

## -------- Enable/Disable services/targets ------
_manage_systemd_services() {
	local _enable_services=('NetworkManager.service'
							'bluetooth.service'
							'cups.service'
							'avahi-daemon.service'
							'systemd-timesyncd.service'
							'ncde-portal.service'
							'apparmor.service'
							'ufw.service')
    local srv

	# NCDE: create the greeter system user (required, or ncde-portal.service
	# restart-loops). Harmless if it already exists in the squashfs passwd.
	echo "+---------------------->>"
	echo "[*] Creating ncde-portal greeter user..."
	useradd --system --home-dir /var/lib/ncde-portal --create-home \
			--shell /usr/sbin/nologin ncde-portal 2>/dev/null || true

	# Enable hypervisors services if installed on it
	[[ `lspci | grep -i virtualbox` ]] && echo "+---------------------->>" && echo "[*] Enabling vbox service..." && systemctl enable -f vboxservice.service
	[[ `lspci -k | grep -i qemu` ]] && echo "+---------------------->>" && echo "[*] Enabling qemu service..." && systemctl enable -f qemu-guest-agent.service

	# Manage services on target system
	for srv in "${_enable_services[@]}"; do
		echo "+---------------------->>"
		echo "[*] Enabling $srv for target system..."
		systemctl enable -f ${srv}
	done

	# Manage targets on target system
	systemctl disable -f multi-user.target
}

## -------- Remove VM Drivers --------------------

# Remove virtualbox pkgs if not running in vbox
_remove_vbox_pkgs() {
	local vbox_pkg='virtualbox-guest-utils'
	local vsrvfile='/etc/systemd/system/multi-user.target.wants/vboxservice.service'

    lspci | grep -i "virtualbox" >/dev/null
    if [[ "$?" != 0 ]] ; then
		echo "+---------------------->>"
		echo "[*] Removing $vbox_pkg from target system..."
		test -n "`pacman -Q $vbox_pkg 2>/dev/null`" && pacman -Rnsdd ${vbox_pkg} --noconfirm
		if [[ -L "$vsrvfile" ]] ; then
			rm -f "$vsrvfile"
		fi
    fi
}

# Remove vmware pkgs if not running in vmware
_remove_vmware_pkgs() {
    local vmware_pkgs=('open-vm-tools' 'xf86-input-vmmouse' 'xf86-video-vmware')
    local _vw_pkg

    lspci | grep -i "VMware" >/dev/null
    if [[ "$?" != 0 ]] ; then
		for _vw_pkg in "${vmware_pkgs[@]}" ; do
			echo "+---------------------->>"
			echo "[*] Removing ${_vw_pkg} from target system..."
			test -n "`pacman -Q ${_vw_pkg} 2>/dev/null`" && pacman -Rnsdd ${_vw_pkg} --noconfirm
		done
    fi
}

# Remove qemu guest pkg if not running in Qemu
_remove_qemu_pkgs() {
	local qemu_pkg='qemu-guest-agent'
	local qsrvfile='/etc/systemd/system/multi-user.target.wants/qemu-guest-agent.service'

    lspci -k | grep -i "qemu" >/dev/null
    if [[ "$?" != 0 ]] ; then
		echo "+---------------------->>"
		echo "[*] Removing $qemu_pkg from target system..."
		test -n "`pacman -Q $qemu_pkg 2>/dev/null`" && pacman -Rnsdd ${qemu_pkg} --noconfirm
		if [[ -L "$qsrvfile" ]] ; then
			rm -f "$qsrvfile"
		fi
    fi
}

## -------- Remove Un-wanted Drivers -------------
_remove_unwanted_graphics_drivers() {
	local gpu_file='/var/log/gpu-card-info.bash'

	local amd_card=''
	local amd_driver=''
	local intel_card=''
	local intel_driver=''
	local nvidia_card=''
	local nvidia_driver=''

	if [[ -r "$gpu_file" ]] ; then
		echo "+---------------------->>"
		echo "[*] Getting drivers info from $gpu_file file..."
		source ${gpu_file}
	else
		echo "+---------------------->>"
		echo "[!] Warning: file $gpu_file does not exist!"
	fi

	# Remove AMD drivers
    if [[ -n "`lspci -k | grep 'Advanced Micro Devices'`" ]] ; then
        amd_card=yes
    elif [[ -n "`lspci -k | grep 'AMD/ATI'`" ]] ; then
        amd_card=yes
    elif [[ -n "`lspci -k | grep 'Radeon'`" ]] ; then
        amd_card=yes
    fi
    echo "+---------------------->>"
    echo "[*] AMD Card : $amd_card"
	if [[ "$amd_card" == 'no' ]] ; then
		echo "[*] Removing AMD drivers from target system..."
        _remove_pkgs_if_installed xf86-video-amdgpu xf86-video-ati
	fi

	# Remove intel drivers
	echo "+---------------------->>"
    echo "[*] Intel Card : $intel_card"
	if [[ "$intel_card" == 'no' ]] ; then
		echo "[*] Removing Intel drivers from target system..."
        _remove_pkgs_if_installed xf86-video-intel
	fi

	# Remove All nvidia drivers
	echo "+---------------------->>"
    echo "[*] Nvidia Card : $nvidia_card"
	if [[ "$nvidia_card" == 'no' ]] ; then
		echo "[*] Removing All Nvidia drivers from target system..."
        _remove_pkgs_if_installed xf86-video-nouveau nvidia-open nvidia-settings nvidia-utils
	fi

	# Remove nvidia drivers
	echo "+---------------------->>"
    echo "[*] Nvidia Drivers : $nvidia_driver"
	if [[ "$nvidia_driver" == 'no' ]] ; then
		echo "[*] Removing Nvidia drivers from target system..."
        _remove_pkgs_if_installed nvidia-open nvidia-settings nvidia-utils
	fi

	# Remove nouveau drivers
	echo "+---------------------->>"
    echo "[*] Free Nvidia Drivers : $nvidia_driver"
	if [[ "$nvidia_driver" == 'yes' ]] ; then
		echo "[*] Removing open-source Nvidia drivers from target system..."
        _remove_pkgs_if_installed xf86-video-nouveau
	fi
}

## -------- Remove Un-wanted Ucode ---------------

# Remove un-wanted ucode package
_remove_unwanted_ucode() {
	cpu="`grep -w "^vendor_id" /proc/cpuinfo | head -n 1 | awk '{print $3}'`"

	case "$cpu" in
		GenuineIntel)	echo "+---------------------->>" && echo "[*] Removing amd-ucode from target system..."
						_remove_pkgs_if_installed amd-ucode
						;;
		*)            	echo "+---------------------->>" && echo "[*] Removing intel-ucode from target system..."
						_remove_pkgs_if_installed intel-ucode
						;;
	esac
}

## -------- Remove Packages/Installer ------------

# Remove unnecessary packages
_remove_unwanted_packages() {
    local _packages_to_remove=('ncde-install-scripts'
							   'ncde-installer'
							   'ncde-welcome'
							   'calamares-config'
							   'calamares'
							   'archinstall'
							   'arch-install-scripts'
							   'ckbcomp'
							   'boost'
							   'mkinitcpio-archiso'
							   'darkhttpd'
							   'irssi'
							   'lftp'
							   'lynx'
							   'mc'
							   'ddrescue'
							   'testdisk'
							   'syslinux')
    local rpkg

	echo "+---------------------->>"
	echo "[*] Removing unnecessary packages..."
    for rpkg in "${_packages_to_remove[@]}"; do
		pacman -Q ${rpkg} &>/dev/null
		if [[ "$?" == 0 ]]; then
			pacman -Rnsc ${rpkg} --noconfirm
		fi
	done
}

## -------- Delete Unnecessary Files -------------

# Clean live ISO stuff from target system
_clean_target_system() {
    local _files_to_remove=(
        /etc/sudoers.d/02_g_wheel
        /etc/systemd/system/getty@tty1.service.d
        /etc/initcpio
        /etc/mkinitcpio-archiso.conf
        /etc/polkit-1/rules.d/49-nopasswd-calamares.rules
        /etc/{group-,gshadow-,passwd-,shadow-}
        /etc/udev/rules.d/81-dhcpcd.rules
        /etc/skel/{.xinitrc,.xsession,.xprofile}
        /home/"$new_user"/{.xinitrc,.xsession,.xprofile,.wget-hsts,.screenrc,.ICEauthority}
        /root/{.automated_script.sh,.zlogin}
        /root/{.xinitrc,.xsession,.xprofile}
		/usr/local/bin/{Installation_guide}
		/usr/share/applications/xfce4-about.desktop
		/usr/share/calamares
        /{gpg.conf,gpg-agent.conf,pubring.gpg,secring.gpg}
        /var/lib/NetworkManager/NetworkManager.state
    )
    local dfile

	echo "+---------------------->>"
	echo "[*] Deleting live ISO files..."
    for dfile in "${_files_to_remove[@]}"; do
		rm -rf ${dfile}
	done
    find /usr/lib/initcpio -name archiso* -type f -exec rm '{}' \;
}

## -------- Perform Misc Operations --------------

_perform_various_stuff() {

	# Copy grub theme to boot directory
	echo "+---------------------->>"
	echo "[*] Copying grub theme to boot directory..."
	mkdir -p /boot/grub/themes
	cp -rf /usr/share/grub/themes/ncde /boot/grub/themes

	# NCDE: set the desktop session for ncde-portal. There is no .desktop
	# session selector and no display-manager state file — the PAM helper
	# execs /etc/ncde/xsession, which runs ncde-x11-session -> ncde-wm.
	echo "+---------------------->>"
	echo "[*] Setting NCDE as the desktop session..."
	mkdir -p /etc/ncde
	echo 'ncde-x11-session' > /etc/ncde/xsession
	chmod 644 /etc/ncde/xsession
	chmod +x /usr/local/bin/ncde-x11-session /usr/local/bin/ncde-wm 2>/dev/null
	install -d -m0755 /var/cache/ncde/qmlcache

	# NCDE: switch live->installed boot. Remove the live autologin drop-in so
	# the installed system shows the greeter instead of auto-entering desktop.
	echo "+---------------------->>"
	echo "[*] Removing live autologin drop-in..."
	rm -rf /etc/systemd/system/ncde-portal.service.d/autologin.conf
	rmdir  /etc/systemd/system/ncde-portal.service.d 2>/dev/null || true

	# Perform various operations
	echo "+---------------------->>"
	echo "[*] Running operations as new user : ${new_user}..."
	runuser -l ${new_user} -c 'xdg-user-dirs-update'
	runuser -l ${new_user} -c 'xdg-user-dirs-gtk-update'

    # Journal stuff
    sed -i 's/volatile/auto/g' /etc/systemd/journald.conf 2>>/tmp/.errlog
    sed -i 's/.*pam_wheel\.so/#&/' /etc/pam.d/su
}

## -------- ## Execute Script ## -----------------
_manage_systemd_services
_remove_vbox_pkgs
_remove_vmware_pkgs
_remove_qemu_pkgs
_remove_unwanted_graphics_drivers
_remove_unwanted_ucode
_remove_unwanted_packages
_clean_target_system
_perform_various_stuff
~~~~

## branding/ncde/branding.desc

~~~~yaml
# SPDX-FileCopyrightText: no
# SPDX-License-Identifier: CC0-1.0
#
# NCDE Poseidon — Calamares branding.
# Install to: /etc/calamares/branding/ncde/
#   branding.desc, show.qml, stylesheet.qss, + images (logo.png, welcome.png)
---
componentName:  ncde

# Window
welcomeStyleCalamares:   false
welcomeExpandingLogo:    true
windowExpanding:         normal
windowSize:              900px,560px
windowPlacement:         center

# Navigation / sidebar
sidebar:    widget
navigation: widget

strings:
    productName:         NCDE Poseidon
    shortProductName:    NCDE
    version:             14.2
    shortVersion:        14.2
    versionedName:       NCDE Poseidon 14.2 "Trident"
    shortVersionedName:  NCDE 14.2
    bootloaderEntryName: NCDE Poseidon
    productUrl:          https://ncde.io/
    supportUrl:          https://ncde.io/support
    knownIssuesUrl:      https://ncde.io/issues
    releaseNotesUrl:     https://ncde.io/notes
    productLogo:         "logo.png"
    productIcon:         "logo.png"
    productWelcome:      "welcome.png"

images:
    productLogo:    "logo.png"
    productIcon:    "logo.png"
    productWelcome: "welcome.png"

slideshow:    "show.qml"
slideshowAPI: 2

# Wizard chrome colors — the ocean/gilt palette.
style:
    sidebarBackground:    "#020608"
    sidebarText:          "#c9a96b"
    sidebarTextSelect:    "#e2c772"
    sidebarTextCurrent:   "#f3e3b5"
    sidebarTextHighlight: "#b88a2c"
~~~~

## branding/ncde/stylesheet.qss

~~~~css
/* SPDX-License-Identifier: CC0-1.0
 *
 * NCDE Poseidon — Calamares wizard skin.
 * Install to: /etc/calamares/branding/ncde/stylesheet.qss
 * Skins the Qt wizard chrome in the ocean/gilt palette. Fonts resolve
 * from the system-installed families (same set the HTML used).
 */

/* ---- overall wizard ---- */
#mainApp {
    background-color: #e8d6a9;            /* parchment body */
}

/* ---- left sidebar (step list) ---- */
#sidebarApp {
    background-color: #020608;            /* abyss-deep */
}
#sidebarMenuApp QPushButton {
    color: #c9a96b;
    background-color: transparent;
    font-family: "IM Fell DW Pica SC", "Cinzel", serif;
    font-size: 13px;
    letter-spacing: 2px;
    text-align: left;
    padding: 10px 16px;
    border: none;
}
#sidebarMenuApp QPushButton:checked,
#sidebarMenuApp QPushButton[aria-selected="true"] {
    color: #f3e3b5;
    border-left: 3px solid #b88a2c;
}

/* ---- headings / body text ---- */
QLabel {
    color: #2a1a08;
    font-family: "Cormorant Garamond", serif;
}
QLabel[id="titleLabel"], QLabel#titleLabel {
    color: #2a1a08;
    font-family: "Cormorant Garamond", serif;
    font-size: 30px;
    font-style: italic;
    font-weight: 600;
}

/* ---- primary / secondary buttons ---- */
QPushButton {
    background-color: #2a1a08;
    color: #f3e3b5;
    border: 1px solid #6f4f15;
    border-radius: 3px;
    padding: 9px 22px;
    font-family: "IM Fell DW Pica SC", serif;
    font-size: 13px;
    letter-spacing: 2px;
}
QPushButton:hover { background-color: #3a2614; }
QPushButton:disabled {
    background-color: #c9b07c;
    color: #8a6a3a;
    border-color: #b88a2c;
}
QPushButton:default {
    background-color: #6b2018;          /* burgundy = primary action */
    border: 1px solid #3a0a06;
}
QPushButton:default:hover { background-color: #812620; }

/* ---- inputs ---- */
QLineEdit, QComboBox, QSpinBox {
    background-color: #f3e3b5;
    color: #2a1a08;
    border: 1px solid #6f4f15;
    border-radius: 2px;
    padding: 6px 10px;
    font-family: "Cormorant Garamond", serif;
    font-size: 16px;
    selection-background-color: #b88a2c;
    selection-color: #1a0f04;
}
QLineEdit:focus, QComboBox:focus, QSpinBox:focus {
    border: 1px solid #b88a2c;
}

/* ---- progress bar (install phase) ---- */
QProgressBar {
    background-color: #1a0f04;
    border: 1px solid #6f4f15;
    border-radius: 3px;
    height: 18px;
    text-align: center;
    color: #f3e3b5;
    font-family: "JetBrains Mono", monospace;
    font-size: 11px;
}
QProgressBar::chunk {
    background-color: #b88a2c;          /* gilt fill */
    border-radius: 2px;
}

/* ---- checkboxes / radios ---- */
QCheckBox, QRadioButton {
    color: #2a1a08;
    font-family: "Cormorant Garamond", serif;
    font-size: 16px;
}
QCheckBox::indicator:checked, QRadioButton::indicator:checked {
    background-color: #6b2018;
    border: 1px solid #6f4f15;
}
~~~~

## branding/ncde/show.qml

~~~~qml
/* SPDX-License-Identifier: CC0-1.0
 *
 * NCDE Poseidon — Calamares install-phase slideshow.
 * Pure QML (no WebEngine). Ocean-deep field, gilt text, slow crossfade.
 * Install to: /etc/calamares/branding/ncde/show.qml
 */
import QtQuick 2.5
import calamares.slideshow 1.0

Presentation {
    id: presentation

    function onActivate()   { presentation.startTimer(); }
    function onLeave()      { presentation.stopTimer(); }

    Timer {
        id: advanceTimer
        interval: 8000
        running: true
        repeat: true
        onTriggered: presentation.goToNextSlide()
    }

    // ---- shared slide scaffold ----
    // Each slide: ocean background, a Latin eyebrow, a title, a line of prose.
    Component {
        id: slideTemplate
    }

    Slide {
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0c2a3a" }
                GradientStop { position: 0.55; color: "#051724" }
                GradientStop { position: 1.0; color: "#020608" }
            }
        }
        Column {
            anchors.centerIn: parent
            spacing: 14
            width: parent.width * 0.7
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "· TERRA · NOVA ·"
                color: "#b88a2c"; font.pixelSize: 16; font.letterSpacing: 6
                font.family: "Cinzel"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Welcome to NCDE Poseidon"
                color: "#f3e3b5"; font.pixelSize: 42; font.italic: true
                font.family: "Cormorant Garamond"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                wrapMode: Text.WordWrap
                text: "Your new desktop is being charted to disk. A realm that hides its machinery — so you need only sail."
                color: "#c9a96b"; font.pixelSize: 20; font.italic: true
                font.family: "IM Fell DW Pica"; horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Slide {
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0c2a3a" }
                GradientStop { position: 0.55; color: "#051724" }
                GradientStop { position: 1.0; color: "#020608" }
            }
        }
        Column {
            anchors.centerIn: parent
            spacing: 14
            width: parent.width * 0.7
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "· INSTRVMENTA ·"
                color: "#b88a2c"; font.pixelSize: 16; font.letterSpacing: 6
                font.family: "Cinzel"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Everything, already aboard"
                color: "#f3e3b5"; font.pixelSize: 42; font.italic: true
                font.family: "Cormorant Garamond"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                wrapMode: Text.WordWrap
                text: "A graphical software harbor, a guarded shield, recovery snapshots, and tools for daily work — fitted from the first voyage."
                color: "#c9a96b"; font.pixelSize: 20; font.italic: true
                font.family: "IM Fell DW Pica"; horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Slide {
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0c2a3a" }
                GradientStop { position: 0.55; color: "#051724" }
                GradientStop { position: 1.0; color: "#020608" }
            }
        }
        Column {
            anchors.centerIn: parent
            spacing: 14
            width: parent.width * 0.7
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "· MARE · APERTVM ·"
                color: "#b88a2c"; font.pixelSize: 16; font.letterSpacing: 6
                font.family: "Cinzel"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "The island awaits"
                color: "#f3e3b5"; font.pixelSize: 42; font.italic: true
                font.family: "Cormorant Garamond"; horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                wrapMode: Text.WordWrap
                text: "In a moment, restart and step ashore. Your system will greet you by name."
                color: "#c9a96b"; font.pixelSize: 20; font.italic: true
                font.family: "IM Fell DW Pica"; horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
~~~~

## branding/ncde/NCDEMedallion.qml

~~~~qml
// NCDEMedallion.qml — proof that the HTML canvas art ports to QML.
// The draw code is the SAME 2D-context logic as the HTML/icons.js version;
// only the wrapper is QML. Use anywhere in Calamares QML (slideshow or a
// QML view module). Pulses like the original.
import QtQuick 2.5

Item {
    id: root
    width: 280; height: 280
    property real pulse: 1.0

    // gentle opacity pulse, same 4.5s feel as the CSS medallion
    SequentialAnimation on pulse {
        loops: Animation.Infinite
        NumberAnimation { from: 0.62; to: 1.0; duration: 2250; easing.type: Easing.InOutSine }
        NumberAnimation { from: 1.0; to: 0.62; duration: 2250; easing.type: Easing.InOutSine }
    }

    Canvas {
        id: cv
        anchors.fill: parent
        opacity: root.pulse
        onPaint: {
            var x = getContext("2d");
            var W = width, H = height, cx = W/2, cy = H/2, R = Math.min(W,H)/2 - 6;
            x.clearRect(0,0,W,H);

            // gilt gradient helper (same stops as the HTML)
            function gilt() {
                var g = x.createLinearGradient(cx-R, cy-R, cx+R, cy+R);
                g.addColorStop(0, "#fff6d2"); g.addColorStop(0.4, "#e2c772"); g.addColorStop(1, "#6f4f15");
                return g;
            }

            // outer ring
            x.strokeStyle = gilt(); x.lineWidth = 4;
            x.beginPath(); x.arc(cx, cy, R, 0, Math.PI*2); x.stroke();
            // bead halo
            for (var i = 0; i < 48; i++) {
                var a = i/48 * Math.PI*2;
                x.beginPath();
                x.arc(cx + Math.cos(a)*(R-14), cy + Math.sin(a)*(R-14), (i%6===0)?3:1.6, 0, Math.PI*2);
                x.fillStyle = (i%6===0) ? "#e2c772" : "#b88a2c"; x.fill();
            }
            // inner sea disc
            var sea = x.createRadialGradient(cx, cy-18, 8, cx, cy, R-30);
            sea.addColorStop(0, "#2f6e80"); sea.addColorStop(0.6, "#1a4a5a"); sea.addColorStop(1, "#04101a");
            x.beginPath(); x.arc(cx, cy, R-30, 0, Math.PI*2); x.fillStyle = sea; x.fill();

            // trident (same path as the HTML)
            x.save(); x.translate(cx, cy - R*0.30); x.scale(R/90, R/90);
            x.strokeStyle = gilt(); x.fillStyle = gilt(); x.lineCap = "round"; x.lineJoin = "round";
            x.lineWidth = 4; x.beginPath(); x.moveTo(0,-12); x.lineTo(0,52); x.stroke();
            x.lineWidth = 3.4; x.beginPath(); x.moveTo(-13,-4); x.lineTo(13,-4); x.stroke();
            x.beginPath(); x.moveTo(-3.4,-12); x.lineTo(-3.4,-30); x.quadraticCurveTo(0,-37,3.4,-30); x.lineTo(3.4,-12); x.closePath(); x.fill();
            x.lineWidth = 3.4;
            x.beginPath(); x.moveTo(-11,-12); x.lineTo(-13,-30); x.quadraticCurveTo(-19,-39,-22,-33); x.stroke();
            x.beginPath(); x.moveTo(11,-12); x.lineTo(13,-30); x.quadraticCurveTo(19,-39,22,-33); x.stroke();
            x.restore();
        }
        // repaint as the pulse animates the opacity (opacity alone needs no repaint,
        // but if you animate colors, call cv.requestPaint() from an onPulseChanged).
    }
}
~~~~

## branding/ncde/preview.html

~~~~html
<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8" />
<meta name="viewport" content="width=device-width, initial-scale=1" />
<title>NCDE Calamares — Skin Preview</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Cormorant+Garamond:ital,wght@0,500;0,600;1,500;1,600&family=IM+Fell+DW+Pica:ital@0;1&family=IM+Fell+DW+Pica+SC&family=Cinzel:wght@600;700&family=JetBrains+Mono&display=swap');
  *{ box-sizing:border-box; margin:0; padding:0; }
  body{ background:#1a120a; min-height:100vh; display:grid; place-items:center; padding:24px; font-family:'Cormorant Garamond',serif; }
  .note{ position:fixed; top:10px; left:0; right:0; text-align:center; font-family:'IM Fell DW Pica SC',serif; letter-spacing:.2em; font-size:11px; color:#8a6a3a; }
  /* the Calamares window */
  .cal{ width:900px; height:560px; display:grid; grid-template-columns:230px 1fr; grid-template-rows:1fr 64px;
    box-shadow:0 30px 80px #000a, 0 0 0 1px #6f4f15; border-radius:4px; overflow:hidden; }
  /* sidebar */
  .side{ grid-row:1/3; background:#020608; padding:26px 0; display:flex; flex-direction:column; }
  .side .brand{ display:flex; flex-direction:column; align-items:center; gap:10px; padding:0 16px 22px; border-bottom:1px solid #ffffff10; }
  .side .brand img{ width:84px; height:84px; }
  .side .brand .nm{ font-family:'Cinzel',serif; font-weight:700; letter-spacing:.22em; font-size:13px; color:#e2c772; }
  .side .steps{ list-style:none; margin-top:14px; }
  .side .steps li{ font-family:'IM Fell DW Pica SC',serif; letter-spacing:.16em; font-size:12.5px; color:#c9a96b; padding:11px 22px; }
  .side .steps li.cur{ color:#f3e3b5; border-left:3px solid #b88a2c; background:#ffffff08; }
  .side .steps li.done{ color:#8a6a3a; }
  .side .steps li.done::before{ content:"✓ "; color:#6f4f15; }
  /* main body — parchment OR slideshow */
  .body{ background:#e8d6a9; position:relative; overflow:hidden;
    background-image:radial-gradient(600px 300px at 25% 0%, #f3e3b5, transparent 60%); }
  .body.pane{ padding:34px 40px; }
  .body .eyebrow{ font-family:'IM Fell DW Pica SC',serif; letter-spacing:.22em; font-size:11px; color:#6f4f15; }
  .body h1{ font-family:'Cormorant Garamond',serif; font-style:italic; font-weight:600; font-size:34px; color:#2a1a08; margin:4px 0 14px; }
  .body p{ font-family:'IM Fell DW Pica',serif; font-style:italic; font-size:16px; color:#5a3a18; max-width:80%; line-height:1.6; }
  .field{ margin-top:18px; }
  .field label{ display:block; font-family:'IM Fell DW Pica SC',serif; letter-spacing:.12em; font-size:10px; color:#6f4f15; margin-bottom:5px; }
  .field input{ width:340px; background:#f3e3b5; color:#2a1a08; border:1px solid #6f4f15; border-radius:2px; padding:8px 12px; font-family:'Cormorant Garamond',serif; font-size:16px; }
  /* slideshow overlay (install phase) */
  .slideshow{ position:absolute; inset:0; background:linear-gradient(180deg,#0c2a3a,#051724 55%,#020608); display:grid; place-items:center; }
  .slide{ width:70%; text-align:center; }
  .slide .ey{ font-family:'Cinzel',serif; letter-spacing:.4em; font-size:15px; color:#b88a2c; }
  .slide .ti{ font-family:'Cormorant Garamond',serif; font-style:italic; font-weight:600; font-size:42px; color:#f3e3b5; margin:10px 0 12px; }
  .slide .pr{ font-family:'IM Fell DW Pica',serif; font-style:italic; font-size:20px; color:#c9a96b; line-height:1.55; }
  /* footer / nav */
  .foot{ background:#e8d6a9; border-top:1px solid #6f4f15; display:flex; align-items:center; padding:0 24px; gap:12px; }
  .bar{ flex:1; height:16px; background:#1a0f04; border:1px solid #6f4f15; border-radius:3px; overflow:hidden; }
  .bar > i{ display:block; height:100%; width:62%; background:#b88a2c; }
  .btn{ font-family:'IM Fell DW Pica SC',serif; letter-spacing:.16em; font-size:12px; padding:9px 22px; border-radius:3px; border:1px solid #6f4f15; background:#2a1a08; color:#f3e3b5; cursor:pointer; }
  .btn.pri{ background:#6b2018; border-color:#3a0a06; }
</style>
</head>
<body>
<template id="__bundler_thumbnail"><svg viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg"><rect width="100" height="100" fill="#020608"/><rect x="14" y="20" width="22" height="60" fill="#020608" stroke="#b88a2c"/><rect x="40" y="30" width="46" height="10" fill="#e2c772"/><rect x="40" y="46" width="46" height="8" fill="#b88a2c"/><rect x="40" y="60" width="30" height="8" fill="#6f4f15"/></svg></template>
  <div class="note">CALAMARES WIZARD — NCDE SKIN MOCKUP (Qt at runtime; this shows the palette + slideshow)</div>

  <div class="cal" id="cal">
    <div class="side">
      <div class="brand">
        <img src="logo.png" alt="" />
        <div class="nm">NCDE POSEIDON</div>
      </div>
      <ul class="steps">
        <li class="done">WELCOME</li>
        <li class="done">LANGUAGE</li>
        <li class="done">KEYBOARD</li>
        <li class="cur">DISKS</li>
        <li>ACCOUNT</li>
        <li>SUMMARY</li>
        <li>INSTALL</li>
        <li>FINISH</li>
      </ul>
    </div>

    <div class="body pane" id="body">
      <div class="eyebrow">· ELIGE · DISCVM ·</div>
      <h1>Select a Disk</h1>
      <p>NCDE will be charted onto the drive you choose. This is the Qt wizard, skinned by <b>stylesheet.qss</b> — parchment body, ocean sidebar, gilt and burgundy controls.</p>
      <div class="field"><label>TARGET DRIVE</label><input value="Samsung SSD 980 PRO — 1 TiB" readonly /></div>
    </div>

    <div class="foot">
      <button class="btn">◀ Back</button>
      <div class="bar"><i></i></div>
      <button class="btn pri">Next ▶</button>
    </div>
  </div>

  <script>
    // toggle: click the window to swap between a wizard pane and the install slideshow
    const slides = [
      { ey:'· TERRA · NOVA ·', ti:'Welcome to NCDE Poseidon', pr:'Your new desktop is being charted to disk — a realm that hides its machinery, so you need only sail.' },
      { ey:'· INSTRVMENTA ·', ti:'Everything, already aboard', pr:'A graphical software harbor, a guarded shield, recovery snapshots, and tools for daily work — fitted from the first voyage.' },
      { ey:'· MARE · APERTVM ·', ti:'The island awaits', pr:'In a moment, restart and step ashore. Your system will greet you by name.' }
    ];
    let on = false, idx = 0, timer = null;
    const body = document.getElementById('body');
    function showSlides(){
      on = true; body.className = 'body';
      const render = () => { const s = slides[idx];
        body.innerHTML = '<div class="slideshow"><div class="slide"><div class="ey">'+s.ey+'</div><div class="ti">'+s.ti+'</div><div class="pr">'+s.pr+'</div></div></div>'; };
      render(); timer = setInterval(()=>{ idx=(idx+1)%slides.length; render(); }, 3000);
    }
    function showPane(){
      on = false; clearInterval(timer); body.className = 'body pane';
      body.innerHTML = '<div class="eyebrow">· ELIGE · DISCVM ·</div><h1>Select a Disk</h1><p>NCDE will be charted onto the drive you choose. This is the Qt wizard, skinned by <b>stylesheet.qss</b> — parchment body, ocean sidebar, gilt and burgundy controls.</p><div class="field"><label>TARGET DRIVE</label><input value="Samsung SSD 980 PRO — 1 TiB" readonly /></div>';
    }
    document.getElementById('cal').addEventListener('click', ()=> on ? showPane() : showSlides());
  </script>
</body>
</html>
~~~~

## README.md

~~~~markdown
# NCDE Poseidon — Calamares config set (Path B)

NCDE's installer **is Calamares**. Isla/Tauri are abandoned. These files adapt
Archcraft's Calamares chain for NCDE: one desktop (no WM chooser), `ncde-portal`
greeter, NCDE branding. The post-install shell logic lives in `scripts/`.

## Files & where they go in the ISO

```
calamares-ncde/
├── settings.conf                  -> /etc/calamares/settings.conf
├── modules/
│   └── shellprocess.conf          -> /etc/calamares/modules/shellprocess.conf
└── scripts/
    ├── post_install.sh            -> /usr/bin/post_install.sh         (chmod +x)
    └── chrooted_post_install.sh   -> /usr/bin/chrooted_post_install.sh (chmod +x)
```

## What changed vs Archcraft (and why)

- **No `packagechooser`** in the sequence, and **no `contextualprocess`** instances.
  NCDE has one desktop, so the WM selector + `chrooted_desktop.sh` +
  `chrooted_autologin.sh` are all dropped.
- **`branding: ncde`** (was `archcraft`). You must ship a branding dir at
  `/etc/calamares/branding/ncde/` (`branding.desc`, `stylesheet.qss`, `show.qml`,
  slideshow) — that's the beautify step, done later.
- **shellprocess** still runs `/usr/bin/post_install.sh`; the i18n name is a
  Captain's-Log line instead of the Archcraft string.
- The exec sequence keeps Calamares' real engine modules (`partition`, `mount`,
  `unpackfs`, `users`, `locale`, `keyboard`, `grubcfg`, `bootloader`, …). These
  replace everything Isla used to do.

## Post-install scripts (in `scripts/`)
- `post_install.sh` — **unchanged from Archcraft** except branding (GPU detect +
  chroot handoff; uses plain `chroot`).
- `chrooted_post_install.sh` — Archcraft logic, with: `sddm.service` →
  `ncde-portal.service`; grub theme `archcraft` → `ncde`; lightdm/lxdm/sddm
  autologin + sddm state.conf blocks removed; `archcraft-hooks-runner` removed;
  **added** ncde-portal user creation, live autologin drop-in removal, and
  `ncde-x11-session` setup (writes `/etc/ncde/xsession`).

## Open confirms before an ISO build (from the plan)
1. Live autologin drop-in exact path/name (script assumes
   `/etc/systemd/system/ncde-portal.service.d/autologin.conf`).
2. `_remove_unwanted_packages` list — NCDE installer package names
   (`ncde-install-scripts`/`ncde-installer`/`ncde-welcome`) are placeholders;
   confirm the real names or they're harmless no-ops.
3. Branding dir `ncde` must exist or Calamares falls back to default theme
   (fine for the first working build).

## Build order (working-first)
1. Drop these files into the airootfs at the paths above; `chmod +x` the scripts.
2. Ship stock Calamares + these configs (default theme) → build ISO.
3. Install on a ≥? GiB VM, confirm it completes and boots to the NCDE greeter.
4. Only then: add the `ncde` branding dir (QSS skin + HTML slideshow).
~~~~

