# NCDE-INSTALL-PLAN.md — Adapting Archcraft's post-install for NCDE Poseidon (v3)

Status: **SUPERSEDED — historical adaptation draft.** The post-install logic it proposed now exists
concretely in `calamares-ncde/scripts/chrooted_post_install.sh` (see NCDE-CALAMARES-PLAN appendix).
Current authoritative state: SESSION_HANDOFF.md + ISO-BUILD-PLAN.md §10.

> **🔄 UPDATE (2026-06-21, late) — §7 confirms resolved:** live autologin drop-in path/user
> **confirmed** (`ncde-portal.service.d/autologin.conf` → user `live`); `live` user **created** in the
> rootfs; portal greeter user handled in the script. Source tree was **lost** from the dev machine but
> has since been **recovered via Ghidra** (oracle: `~/ncde-staging/ncde-wm-rebuild/src/decompiled/`) and
> the WM is being rebuilt — it compiles; either way the install runs built artifacts only.
> `[dead-legacy-tree]` is the consolidated build source (398 files, 0 missing).
>
> **[Corrected 2026-07-17]:** the `~/ncde-staging/` path above no longer exists — the dev machine
> that hosted it is gone, on this machine and the USB backup both. The reconstruction workspace is
> now `~/ncde-wm-rebuild/src/decompiled/`, and "it compiles" overstated things even then — recovery
> is partial, most classes are still raw Ghidra output, not clean buildable source (see
> `docs/lapivot-rebuild.md` for current status). Doesn't change the bottom line: the install runs
> built artifacts only.

## Sources of truth
- Read-only Archcraft reference: `[dead-legacy-tree]/helpwithisla/calamares-reference/` (extracted from ISO).
- **NCDE source tree: `[dead-legacy-tree]/` itself** — a full system rootfs overlay holding all NCDE files
  (`usr/bin/ncde-*`, `usr/local/bin/ncde-wm | ncde-x11-session`, `etc/ncde/`,
  `etc/pam.d/ncde-portal*`, `usr/lib/systemd/system/ncde-portal.service`, themes, wallpapers…).

---

## 0. CORE DESIGN — full desktop on boot, exactly like Archcraft

NCDE must boot the **full NCDE desktop on boot**, the same way Archcraft does:

| | Archcraft | NCDE (this plan) |
|---|---|---|
| **Live medium** | autologin → full desktop, no password | `ncde-portal --autologin` → full NCDE desktop, no password |
| **Installed system** | greeter (SDDM) → login → desktop | `ncde-portal` greeter → login → full NCDE desktop |
| **What flips it** | `chrooted_post_install.sh` disables live autologin on install | install step **removes the `--autologin` drop-in** |

The live-vs-installed difference is therefore a **single artifact**: an autologin drop-in for
`ncde-portal.service` that is **present in the live squashfs** and **removed during install**.

### Two delivery facts that shape everything
1. **No online repo, no `PKGBUILD`. NCDE is not a pacman package** — it is a **file-tree overlay**.
   All NCDE files are **baked into Archcraft's `airootfs.sfs`** at build time. Because *the live
   system IS the installed system* (squashfs cloned to disk), the files are simply present on the
   installed system — nothing is downloaded or `pacman -S`'d.
2. The Calamares "install NCDE" step therefore installs **no packages**. It (a) strips the desktops
   NCDE replaces (Openbox/BSPWM) + old login manager bits, (b) ensures the `ncde-portal` greeter
   user exists and `ncde-portal.service` is enabled, and (c) removes the live autologin drop-in so
   the installed machine boots to the greeter.

---

## 1. NCDE Portal architecture (confirmed from the source tree)

`usr/lib/systemd/system/ncde-portal.service`:
- `Description=NCDE Portal — native X11 login manager`; `Conflicts=getty@tty1.service`.
- `ExecStart=/usr/bin/ncde-portal --daemon --vt vt01 --display :0 --greeter-user ncde-portal`
- `[Install] WantedBy=graphical.target`, **`Alias=display-manager.service`**.
- **Prerequisite:** system user `ncde-portal` MUST exist or the unit restart-loops:
  `useradd --system --home-dir /var/lib/ncde-portal --create-home --shell /usr/sbin/nologin ncde-portal`

Session chain (no DM session selector, no `.desktop`):
- PAM helper execs **`/etc/ncde/xsession`** as the authenticated user → defaults to
  **`/usr/local/bin/ncde-x11-session`** → sets `XDG_CURRENT_DESKTOP=NCDE`, starts picom,
  `exec /usr/local/bin/ncde-wm`.

PAM stacks: `etc/pam.d/ncde-portal` (full `system-login`), `ncde-portal-autologin` (pam_permit —
the live/kiosk path), `ncde-portal-greeter`.

**Autologin = the `--autologin` daemon flag** (uses the `ncde-portal-autologin` PAM stack). It is
configured via the service ExecStart / a systemd drop-in — NOT an SDDM-style config file.

### The autologin drop-in (the live/installed switch)
- **Live squashfs ships:** `/etc/systemd/system/ncde-portal.service.d/autologin.conf` with an
  ExecStart override that appends `--autologin <liveuser>`. → live boots to full desktop.
- **Install removes** that drop-in (or the whole `.d` dir) → installed boots to greeter.
- **[CONFIRM]** exact drop-in path/filename and the live username it autologins.

---

## 2. Script changes — file by file

### 2.1 `post_install.sh` (host-side: GPU detect → chroot → calls chrooted_post_install.sh)
- Generic. **No logic change.** Optional Rule-7 comment swap on line 5 (`Archcraft`→`NCDE`).
- Uses `chroot` (not `arch-chroot`) — Rule-7 clean. Line 69 keeps calling
  `/usr/bin/chrooted_post_install.sh`. **Leave.**

### 2.2 `chrooted_post_install.sh` (target system — main worker)

**2.2a `_manage_systemd_services()`**
- **Line 39:** `'sddm.service'` → `'ncde-portal.service'`  *(aliases display-manager.service)*.
- Remainder of enable list + `disable multi-user.target` (line 69): keep.

**2.2b `_remove_unwanted_packages()` (209–226)**
- Keep removing Archcraft installer/welcome + generic live tooling by their real names.
- Add **no** `ncde-*` removals (overlay model — nothing to remove).
- Leave WM stripping to `chrooted_desktop.sh` (§2.3) to avoid double-listing.

**2.2c `_clean_target_system()` (243–269):** generic live cleanup. **No change.**

**2.2d `_perform_various_stuff()` (273–327) — main rework**
- **Line 283 grub theme:** `…/themes/archcraft` → `…/themes/ncde`  *(confirmed dir = `ncde`)*.
- **Lines 285–308 (lightdm/lxdm/sddm autologin-disable):** NCDE uses none of these DMs → dead
  branches. **Remove all three** (also clears Rule-7 strings `openbox`/`sddm`).
- **Lines 310–315 (`/var/lib/sddm/state.conf`, `Session=openbox.desktop`):** inapplicable —
  NCDE has no session selector. **Remove.**
- **NCDE autologin-off on install (replaces the removed blocks):** remove the live autologin
  drop-in so the installed system boots to the greeter:
  ```bash
  # Installed system boots to the NCDE Portal greeter (no live autologin)
  rm -rf /etc/systemd/system/ncde-portal.service.d/autologin.conf
  rmdir  /etc/systemd/system/ncde-portal.service.d 2>/dev/null || true
  ```
  (Note: `rm` of a generated drop-in is acceptable inside the *target system during install*;
  CLAUDE.md "never delete files" governs our authoring workspace, not the installer's runtime
  actions. Will flag this explicitly at approval time.)  **[CONFIRM]** drop-in path.
- **Line 320 hooks-runner:** `archcraft-hooks-runner` does **not** exist → **remove the line**.
- Lines 321–326 (`xdg-user-dirs-update`, journald volatile→auto, pam_wheel mask): keep.

**2.2e Execution order (330–338):** add the portal-user step (§3) before service enable, else unchanged.

### 2.3 `chrooted_desktop.sh` ("install NCDE" = strip the WMs it replaces)
- Keep `remove_openbox()` (44–60) and `remove_bspwm()` (62–67) — their package lists are exactly
  what NCDE wants gone. **[CONFIRM]** these package names exist on the base.
- Replace `install_openbox/bspwm/everything` (71–86) with:
  ```bash
  install_ncde() {
      echo "[*] Setting up NCDE desktop..."
      remove_openbox
      remove_bspwm
  }
  ```
- Replace dispatcher (90–97) with:
  ```bash
  if [[ "$1" == '--ncde' ]]; then
      install_ncde
  fi
  ```

### 2.4 `chrooted_autologin.sh` (was SDDM `[Autologin]`/`Session=` editor)
- **Inapplicable** to NCDE (no SDDM, no session selector). The installed-system autologin-off is
  handled in §2.2d by removing the drop-in. → **Drop this script from the chain.**
- (Alternative if you want it kept as the single autologin authority: rewrite its body to
  add/remove the `ncde-portal.service.d/autologin.conf` drop-in, `--ncde` = greeter on install.)
  **[DECISION]** drop (recommended) vs repurpose.

---

## 3. NEW required step — create the portal greeter user (no Archcraft equivalent)
`ncde-portal.service` restart-loops unless the `ncde-portal` user exists. In the target system,
before enabling the service:
```bash
useradd --system --home-dir /var/lib/ncde-portal --create-home \
        --shell /usr/sbin/nologin ncde-portal 2>/dev/null || true
```
**[DECISION]** runtime `useradd` in `_manage_systemd_services()` (rec.) vs bake into squashfs
`/etc/passwd` at build time.

---

## 4. Companion config edits (`/etc/calamares/`, separate approvals)
- `modules/contextualprocess.conf` (55–63): replace `openbox/bspwm/everything` with a single
  `ncde:` branch → `chrooted_desktop.sh --ncde`.
- `modules/contextualprocess_autologin.conf`: drop (per §2.4) or align to `--ncde`.
- `modules/packagechooser.conf` + `branding/archcraft/desktop/*.png`: collapse to NCDE-only
  (or remove the chooser if NCDE is the sole desktop).
- `settings.conf` line 60 `branding: archcraft` → `branding: ncde`; rename branding dir.
- `shellprocess.conf` line 139 i18n name → a Captain's-Log message.

## 5. Build-time tasks (ISO profile, not these scripts)
- Overlay the `[dead-legacy-tree]` tree into `airootfs` so NCDE files ship in the squashfs.
- Ship the live autologin drop-in (`ncde-portal.service.d/autologin.conf`) in the live squashfs.
- Ensure `ncde-portal` user exists in the live env (greeter runs on the live medium too).

## 6. Edit summary
| File | Functional edits | Verdict |
|---|---|---|
| `post_install.sh` | none (opt. comment) | trivial |
| `chrooted_post_install.sh` | L39 service; L283 grub→`ncde`; remove 285–315; add drop-in removal; remove L320; add portal-user (§3) | **main work** |
| `chrooted_desktop.sh` | L71–97 → `install_ncde` + `--ncde` | rework |
| `chrooted_autologin.sh` | drop from chain (or repurpose) | remove |

## 7. Remaining confirms / decisions
1. **[CONFIRM]** Live autologin drop-in path/filename + live username.
2. **[CONFIRM]** WM package names to strip exist on the base (`archcraft-openbox`, `openbox`,
   `archcraft-bspwm`, …).
3. **[DECISION]** Portal user: runtime `useradd` (rec.) vs baked into squashfs.
4. **[DECISION]** `chrooted_autologin.sh`: drop (rec.) vs repurpose as drop-in manager.
5. **Working location for edits:** the adapted worker scripts must live at `[dead-legacy-tree]/usr/bin/…`
   (so they overlay into the squashfs). They don't exist there yet — only the Archcraft originals
   are in the read-only reference. **Confirm we author the NCDE versions into `[dead-legacy-tree]/usr/bin/`**
   (and `usr/local/bin/`) before any edit.

## 8. Rule-7 note (Arch-visibility in the tree)
- `[dead-legacy-tree]/etc/arch-release` exists; `[dead-legacy-tree]/version` = `2026.06.21`. `/etc/arch-release`
  is Arch-identifying — flag for separate review (rename/replace); not part of these script edits.
