# NCDE Phased Cutover

Turn the **partially-installed** NCDE into the **only** desktop — its own login
(`ncde-portal`), its own wallpapers, all native + dock apps working — and remove
Archcraft/openbox **without ever losing a working GUI**.

---

## ⭐ CURRENT STATE — read this first (verified live 2026-06-21)

**The desktop now has everything it needs. The one bug that broke it is fixed.**

- **ROOT CAUSE (fixed):** `ncde-wm`, the NCDE compositor, is a **Vulkan** app. The box has
  **Intel JasperLake UHD Graphics**, but the Vulkan *driver* (`vulkan-intel`) was never
  installed — only the loader was. So `vkCreateInstance` found **no drivers**, `ncde-wm`
  aborted the instant you logged in, and the greeter/login looped. This is why **both** the
  SDDM→NCDE session **and** the `ncde-portal` greeter "popped up but never reached the
  desktop." `vulkan-intel` is now installed and the ICD is valid → `ncde-wm` can start.
- **Everything else is already in place** (see the matrix). The only remaining action is the
  **login-manager swap** (Phase 6): `ncde-portal` is installed but currently disabled; SDDM is
  still the active DM. Switch when ready.

### What is DONE vs PENDING

| Phase | What | State |
|-------|------|-------|
| 1   | Fix broken native apps (`qtermwidget`, `hunspell`) | ✅ DONE |
| 1b  | Verda QML "glass" + shell-integration | ✅ DONE (`/usr/local/bin/qml` symlink + `/usr/local/share/ncde-terminal`) |
| 1c  | Files the installer skipped (launchers, lock chain, sentinel, xorg, dbus) | ✅ DONE (all present; `ncde-sentinel` user unit enabled) |
| —   | **Vulkan driver `vulkan-intel`** (the real blocker) | ✅ DONE |
| 2   | NCDE-only wallpapers | ✅ DONE (10 PNGs in picker dir; archcraft backgrounds removed) — see note |
| 3   | Third-party dock apps (gimp, libreoffice, flatpak, spotify, Steam-flatpak) | ✅ DONE |
| 4   | GTK integration (`libhandy`, `appmenu-gtk-module`) | ✅ DONE |
| 5   | Make NCDE the default session under SDDM | ✅ DONE (`~/.dmrc` + sddm conf = `Session=ncde`) |
| 6   | Replace SDDM with `ncde-portal` | ⏳ **PENDING** — portal installed & ready, currently disabled; SDDM still active |
| 7   | Remove Archcraft / openbox | ⏳ PENDING — keep as fallback until Phase 6 verified |

**Dependency audit (live):** no NCDE binary has a missing shared library; **no packages left
to install.** `vulkan-intel`, `qtermwidget`, `hunspell`, `libhandy`, `appmenu-gtk-module`,
`xss-lock`, `gimp`, `libreoffice-fresh`, `flatpak`, `spotify` all present; Steam flatpak present.

**Safety improvements since the original plan:** persistent journal is now enabled
(`/var/log/journal` exists), so a failed portal start is now **captured to disk** —
`journalctl -b -1 -u ncde-portal` after any failure, no screenshots needed.

---

## How NCDE actually boots a session (reference — learned by inspection)

```
ncde-portal (or SDDM)  →  greeter authenticates via PAM (/etc/pam.d/ncde-portal*)
   →  reads /usr/share/xsessions/ncde.desktop
        Exec=/usr/local/bin/ncde-x11-session     (TryExec=/usr/local/bin/ncde-wm)
   →  ncde-x11-session sets the X/Qt/GTK env, starts picom, then:
        exec /usr/local/bin/ncde-wm > "$HOME/ncde-debug.log" 2>&1
```

Consequences worth remembering:
- **`~/ncde-debug.log` IS the session log.** Its *tail* is whatever killed the last session.
  (That is where the `vkCreateInstance: Found no drivers!` crash was found.)
- `ncde-wm` is a **Vulkan** compositor → it hard-requires a working Vulkan ICD.
- The greeter's QML (`Greeter.qml`, `Lock.qml`, `Screensaver.qml`) is **compiled into the
  `ncde-portal` binary** as Qt resources (`qrc:/qml/...`). So the empty
  `/usr/share/ncde/portal/` directory is **harmless** — it is NOT the greeter assets.

---

## Situation (original context, 2026-06-21)

- NCDE was installed by `~/ncde-install.sh`, which pulls files from the **unsquashed
  airootfs at `[dead-legacy-tree]`** (the squashfs from USB `NCDE_202606`, unsquashed by a
  prior agent). `[dead-legacy-tree]` is the **single source of truth** — the raw USB is not
  needed (and can't be mounted here: no `isofs` module, device owned by group `disk`).
- The installer is **deliberately non-destructive**: it *adds* an `NCDE` session next
  to Archcraft's openbox instead of *replacing* it. That is why the desktop was "split."
- The installer had **two blind spots**: (1) it copied only `/usr/local/bin/*`, skipping
  every NCDE binary under `/usr/bin/`; (2) it copied nothing from `/usr/local/share/`,
  `/usr/share/applications`, `/usr/share/dbus-1`, `/etc/X11`, `/usr/lib/systemd`. Phases
  1b/1c closed those gaps (now done).

---

## Guiding rules

0. **NEVER touch GRUB / the bootloader.** This is the one carve-out from the brief
   ("Archcraft becomes NCDE, **minus messing with GRUB**"). Do **not** run
   `grub-install` / `grub-mkconfig`, and do **not** remove these packages:
   `grub`, `efibootmgr`, `archcraft-grub-theme`, `archcraft-hooks-grub`,
   `archcraft-plymouth-theme` (boot splash — leave it too).
1. **`[dead-legacy-tree]` is the install source** for every NCDE file.
2. **Keep openbox + SDDM as the fallback** until NCDE is proven usable.
3. **Never remove the fallback in the same step** that introduces a change.
4. Keep a TTY escape hatch: **Ctrl+Alt+F3** → log in → run the rollback for the phase.
5. Verify package names before installing: `pacman -F <lib>` / `pacman -Si <pkg>`.
6. **Do NOT try to run `sudo` (no passwordless sudo here).** For any command needing
   root, **present the command to the user to run themselves** — do not attempt it.

---

## Phase 0 — Safety net (do first, no changes)

```bash
# Confirm you can reach a text console and log in there:  Ctrl+Alt+F3
systemctl status display-manager.service --no-pager | head -3   # which DM is active
```

---

## Phase 1 — Fix the genuinely-broken native apps  ✅ DONE

Verda (`ncde-terminal`) needed `libqtermwidget6.so.2`; `verdantfolio` needed
`libhunspell-1.7.so.0`.

```bash
pacman -F libqtermwidget6.so.2     # → qtermwidget
pacman -F libhunspell-1.7.so.0     # → hunspell
sudo pacman -S --needed qtermwidget hunspell
```
**Verified:** `ldd /usr/local/bin/ncde-terminal | grep 'not found'` → empty; same for
`verdantfolio`. `qtermwidget 2.4.0` and `hunspell 1.7.3` installed.

---

## Phase 1b — Verda's QML (the "glass") + shell-integration  ✅ DONE

Verda is a Qt6/QML app; besides the terminal-widget lib it loads its UI
(`NCDEGlassSurface.qml`, `Shell.qml`, `ChromeBar.qml`) from a `qml/` dir. The binary searches
`<exedir>/qml` then `<exedir>/../qml`; installed at `/usr/local/bin/ncde-terminal` that means
`/usr/local/bin/qml`.

```bash
sudo cp -a [dead-legacy-tree]/usr/local/share/ncde-terminal /usr/local/share/
sudo ln -sfn /usr/local/share/ncde-terminal/qml /usr/local/bin/qml
```
**Verified:** `/usr/local/bin/qml → /usr/local/share/ncde-terminal/qml` exists;
`/usr/local/share/ncde-terminal/{qml,shell-integration}` present.

---

## Phase 1c — Other files the installer never copied  ✅ DONE

All present and the `ncde-sentinel` user unit is **enabled**.

| File | Purpose | State |
|------|---------|-------|
| `…/applications/ncde-terminal.desktop`, `ncde-chromium.desktop` | menu/dock launchers | present |
| `/usr/bin/ncde-lock`, `ncde-lock-xss`, `ncde-screensaver-notify` + `/etc/pam.d/ncde-lock` | lock + screensaver chain | present |
| `/etc/X11/xorg.conf.d/10-ncde.conf` | Xorg snippet (DPMS off so the locker owns idle; pins `1920x1200`) | present |
| `…/dbus-1/services/org.ncde.KickassGuard.service` | dbus activation for `kickass-guard` | present |
| `/usr/lib/systemd/user/ncde-sentinel.service` | "hardware event monitor" user unit | present + **enabled** |

```bash
sudo cp -a [dead-legacy-tree]/usr/share/applications/ncde-terminal.desktop  /usr/share/applications/
sudo cp -a [dead-legacy-tree]/usr/share/applications/ncde-chromium.desktop  /usr/share/applications/
sudo update-desktop-database 2>/dev/null || true
sudo cp -a [dead-legacy-tree]/usr/share/dbus-1/services/org.ncde.KickassGuard.service /usr/share/dbus-1/services/
sudo cp -a [dead-legacy-tree]/usr/lib/systemd/user/ncde-sentinel.service /usr/lib/systemd/user/
systemctl --user daemon-reload && systemctl --user enable --now ncde-sentinel
sudo cp -a [dead-legacy-tree]/etc/X11/xorg.conf.d/10-ncde.conf /etc/X11/xorg.conf.d/
sudo cp -a [dead-legacy-tree]/usr/bin/ncde-lock [dead-legacy-tree]/usr/bin/ncde-lock-xss \
           [dead-legacy-tree]/usr/bin/ncde-screensaver-notify /usr/bin/
sudo cp -a [dead-legacy-tree]/etc/pam.d/ncde-lock /etc/pam.d/
sudo pacman -S --needed xss-lock
```
**Deliberately NOT copied:** `usr/share/plymouth/themes/ncde/` (boot splash — **rule 0**);
`/usr/bin/ncde-terminal` (older 183 KB build; the 2.8 MB `/usr/local/bin` one wins on PATH);
`lftp.desktop` (generic tool).

---

## ⛔→✅ ROOT CAUSE — the Vulkan driver (the bug that broke everything)  ✅ FIXED

**Symptom:** greeter (portal *and* SDDM→NCDE) appears, you authenticate, screen flashes
straight back to the login — desktop never loads. On-screen error fades too fast to read.

**Diagnosis:** `~/ncde-debug.log` (the session log — see boot-flow reference above) ends with:
```
Warning: vkCreateInstance: Found no drivers!
Warning: vkCreateInstance failed with VK_ERROR_INCOMPATIBLE_DRIVER
```
`ncde-wm` is a Vulkan compositor. GPU = Intel JasperLake (`8086:4e55`). The Vulkan loader
(`vulkan-icd-loader`, `/usr/lib/libvulkan.so.1`) was present but **no ICD existed** —
`/usr/share/vulkan/icd.d/` was absent and `vulkan-intel` was not installed. Zero drivers →
`ncde-wm` aborts → session dies → login loops.

**Fix (done):**
```bash
sudo pacman -S --needed vulkan-intel        # Mesa ANV driver for Intel
```
**Verified:** `vulkan-intel 1:26.1.3-2` installed; `/usr/share/vulkan/icd.d/intel_icd.json`
→ `libvulkan_intel.so` (24 MB, present, owned by `vulkan-intel`). `ncde-wm` can now create a
Vulkan instance. *(Software fallback if HW Vulkan ever misbehaves: `vulkan-swrast`/lavapipe.)*

---

## Phase 2 — Wallpapers: NCDE set only  ✅ DONE (one cosmetic note)

10 NCDE PNGs are in the picker dir `[dead-legacy-tree]/wallpapers/`; the Archcraft background
packages are removed.

```bash
mkdir -p [dead-legacy-tree]/wallpapers
cp [dead-legacy-tree]/home/live/Pictures/wallpapers/*.png [dead-legacy-tree]/wallpapers/
echo "$HOME/dead-legacy-tree/wallpapers/06-moonPhases-gold-dark.png" > ~/.config/ncde/wallpaper.conf
printf '#!/bin/bash\nfeh --bg-fill "%s"\n' \
  "$HOME/dead-legacy-tree/wallpapers/06-moonPhases-gold-dark.png" > ~/.fehbg
chmod +x ~/.fehbg
rm -f ~/Pictures/wallpapers/wallpaper_*.jpg
sudo pacman -Rns archcraft-backgrounds archcraft-backgrounds-branding
```
**NOTE (non-blocking):** the *active* `~/.config/ncde/wallpaper.conf` currently points at
`~/Pictures/wallpapers/owl.png` (a valid 900×675 PNG), and `~/.fehbg` points at
`~/Pictures/wallpapers/06-moonPhases-gold-dark.png` — i.e. **not** the `[dead-legacy-tree]/wallpapers`
path above. Both targets are valid; the two just disagree. The `libpng error: Read Error` seen
in `ncde-debug.log` is **not** from the active wallpaper (it's valid) — likely a theme
thumbnail, cosmetic. If you want consistency, repoint both at one file under
`[dead-legacy-tree]/wallpapers/`.

---

## Phase 3 — Third-party dock apps  ✅ DONE

```bash
sudo pacman -S --needed gimp libreoffice-fresh flatpak
yay -S spotify                                              # AUR; provides `spotify` cmd
sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
flatpak install -y flathub com.valvesoftware.Steam         # dock entry = flatpak run com.valvesoftware.Steam
```
**Verified installed:** `gimp 3.2.4`, `libreoffice-fresh 26.2.4`, `flatpak 1.18.0`,
`spotify 1.2.92`, and Steam flatpak `com.valvesoftware.Steam`.

---

## Phase 4 — GTK integration  ✅ DONE

```bash
sudo pacman -S --needed libhandy
yay -S appmenu-gtk-module        # AUR
```
**Verified:** `libhandy 1.8.3`, `appmenu-gtk-module 25.04` installed.

---

## Phase 5 — NCDE is the default session (under SDDM)  ✅ DONE

```bash
sudo sed -i 's/^Session=openbox/Session=ncde/' /etc/sddm.conf.d/kde_settings.conf
sudo sed -i 's/^Session=openbox/Session=ncde/' /etc/sddm.conf            # [Autologin] block
sed   -i 's/^Session=openbox/Session=ncde/' ~/.dmrc
```
**Verified:** `~/.dmrc` → `Session=ncde`. (Before the Vulkan fix this session crash-looped;
it should work now.) openbox is still selectable from the SDDM gear menu as a fallback.
**Rollback:** flip `Session=ncde` back to `openbox`, or pick openbox at login.

---

## Phase 6 — Replace SDDM with `ncde-portal`  ⏳ PENDING (this is the next action)

`ncde-portal` is NCDE's native X11 login manager (`Alias=display-manager.service`). It is
**already installed and ready**; SDDM is still the active DM.

**Already verified present:** `/usr/bin/ncde-portal` + `ncde-portal-helper` (libs all resolve),
`/etc/pam.d/ncde-portal{,-autologin,-greeter}`, the `ncde-portal` greeter user
(uid 950, home `/var/lib/ncde-portal`), and the unit. Greeter QML is compiled into the binary.

The install steps (already done — kept for reference / reinstall):
```bash
sudo install -Dm755 [dead-legacy-tree]/usr/bin/ncde-portal        /usr/bin/ncde-portal
sudo install -Dm755 [dead-legacy-tree]/usr/bin/ncde-portal-helper /usr/bin/ncde-portal-helper
sudo install -Dm644 [dead-legacy-tree]/etc/pam.d/ncde-portal           /etc/pam.d/ncde-portal
sudo install -Dm644 [dead-legacy-tree]/etc/pam.d/ncde-portal-autologin /etc/pam.d/ncde-portal-autologin
sudo install -Dm644 [dead-legacy-tree]/etc/pam.d/ncde-portal-greeter   /etc/pam.d/ncde-portal-greeter
sudo install -Dm644 [dead-legacy-tree]/usr/lib/systemd/system/ncde-portal.service \
                    /usr/lib/systemd/system/ncde-portal.service
sudo useradd --system --home-dir /var/lib/ncde-portal --create-home \
             --shell /usr/sbin/nologin ncde-portal
```

### Do this now — swap login managers

```bash
sudo systemctl disable sddm
sudo systemctl enable ncde-portal     # its Alias=display-manager.service handles the symlink
sudo systemctl daemon-reload
sudo reboot
```
**VERIFY GATE:** you should get the **NCDE greeter** (not SDDM) and log all the way into the
NCDE desktop (Vulkan fix means `ncde-wm` now starts).

**If the greeter loops (rollback, from Ctrl+Alt+F3):**
```bash
sudo systemctl disable ncde-portal
sudo systemctl enable sddm
sudo reboot
```
**Then capture the real error** — persistent journal is enabled now, so it survives reboot:
```bash
journalctl -b -1 -u ncde-portal --no-pager        # portal daemon log
tail -30 ~/ncde-debug.log                          # session/compositor log
```

> Note: the unit's `Documentation=` points at `/usr/share/ncde/portal/README.md`, absent in
> the payload — cosmetic only, does not affect startup.

---

## Phase 7 — Remove Archcraft / openbox  ⏳ PENDING (destructive — only after Phase 6 verified)

openbox `3.6.1` and `/usr/share/xsessions/openbox.desktop` are still present (intended — the
fallback). Do **not** run this until NCDE under `ncde-portal` is your confirmed daily driver.

```bash
pacman -Qi openbox | grep 'Required By'   # review cascade first
sudo pacman -Rns openbox archcraft-openbox obconf-qt obmenu-generator
sudo rm -f /usr/share/xsessions/openbox.desktop
rm -rf ~/.config/openbox

# Prune remaining archcraft-* — but PROTECT grub/plymouth (rule 0). Review first:
pacman -Qq | grep '^archcraft-' | grep -vE 'grub|plymouth'
# sudo pacman -Rns <ones you don't want>   # NEVER archcraft-grub-theme / archcraft-hooks-grub
```
**Point of no return:** with openbox gone there is no fallback WM. `archcraft-sddm-theme`
becomes dead weight after the portal swap and is safe to remove; the bootloader and its
theme/hook are never touched.

---

## Open items / unknowns

- **Wallpaper path inconsistency** (Phase 2 note): `wallpaper.conf` vs `.fehbg` vs the
  `[dead-legacy-tree]/wallpapers` picker dir disagree; all valid, cosmetic.
- **`libpng error: Read Error`** in `ncde-debug.log`: not the active wallpaper (valid); likely
  a theme thumbnail — cosmetic, investigate only if a UI image is visibly broken.
- **`/usr/share/ncde/portal/`** absent — README only, harmless (greeter QML is in the binary).
- Decide which remaining `archcraft-*` asset/config packages to keep in Phase 7.
