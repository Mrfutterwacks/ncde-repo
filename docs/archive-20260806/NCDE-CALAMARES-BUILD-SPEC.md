# NCDE Calamares — Complete Build Guide (from scratch, self-contained)

**Audience:** a developer with **no access to the NCDE source tree**. Follow this and you can build the
**real NCDE Poseidon installer** from nothing. It is **Calamares used as the engine** (NCDE's chosen
installer — there is no separate custom installer), configured + branded + scripted to be a genuine NCDE
installer, **not a recolor of stock Calamares** and with **zero Archcraft branding anywhere**.

"Real, not a theme" means: the *branding* (QSS/QML) is the visual skin, but the installer's **behavior** is
fully NCDE — a one-click auto-btrfs install with NCDE's subvolume layout, the System Restore app, and a
post-install that builds the `ncde-portal` greeter system. All of that is specified below in full.

> **If you're improving the EXISTING NCDE installer (not building from zero):** reuse the existing
> `logo.png` / `welcome.png` / `slide1.png`–`slide4.png` art and the NCDE rootfs as-is — you are only
> rewriting `stylesheet.qss`, `show.qml`, and `branding.desc`. The "supply your own art / assumes a rootfs"
> notes below apply only to someone building the whole thing from scratch.

---

## 1. Behavior contract (what the finished installer must do)
1. **One-click auto install** onto real hardware — **no manual partitioning page**.
2. **All btrfs**: auto-erase the target → btrfs with subvolumes `@` (system), `@home`, `@cache`, `@log`,
   `@restore` (recovery snapshots) + a **swapfile** in `@swap`.
3. Installs the **System Restore app ("Soundings")**; recovery invoked only by **Ctrl+Alt+R**.
4. **Looks completely NCDE** — Art Nouveau / Mucha, parchment + ocean + gilt, every pane (no black).
5. Live medium auto-launches the installer; the installed system boots to the **`ncde-portal` greeter**.

## 2. Past failures this guide prevents
- **`-style kvantum`** on the launch command made Kvantum's QStyle override the skin → black body, invisible
  buttons. → Launch with **`pkexec calamares -d`** (no `-style`).
- **Incomplete stylesheet** that only styled `#mainApp`/`#sidebarApp` → content panes + button bar fell
  back to a dark default → black. → Use the **complete** stylesheet in Step 5 (themes every widget class).
- **Archcraft leftovers** (`archcraft-green` icon, `branding/archcraft`). → None. See the checklist (§9).

## 3. Prerequisites
- An Arch-based system or live-ISO build environment.
- Install Calamares + its engine deps:
  ```
  sudo pacman -S calamares
  # engine pulls: kpmcore, qt6 (base/declarative/svg/tools), kconfig, solid, polkit, util-linux, etc.
  # also ensure on the target image: btrfs-progs, dosfstools, grub, efibootmgr, mkinitcpio
  ```
- For testing: `qemu-system-x86_64`, `edk2-ovmf` (UEFI firmware).
- Fonts the skin uses (ship them on the image): **Cormorant Garamond, Cinzel, IM Fell DW Pica / SC,
  JetBrains Mono**. Calamares text falls back to a serif if absent, but ship them for the intended look.

## 4. Directory layout (create exactly this)
```
/etc/calamares/
├── settings.conf                      # Step 4a
├── launch.sh                          # Step 6   (chmod 755)
├── modules/
│   ├── partition.conf                 # Step 4b
│   ├── mount.conf                     # Step 4c
│   ├── shellprocess.conf              # Step 4d
│   └── unpackfs.conf                  # Step 4e  (point at YOUR squashfs/kernel paths)
└── branding/ncde/
    ├── branding.desc                  # Step 5a
    ├── stylesheet.qss                 # Step 5b  ← the centerpiece
    ├── show.qml                       # Step 5c  (slideshow)
    ├── logo.png  welcome.png          # Step 5d  (art — supply from the NCDE design kit)
    ├── slide1.png … slide4.png        # Step 5d
    └── language.svg
/usr/bin/post_install.sh               # Step 7   (chmod 755)
/usr/bin/chrooted_post_install.sh      # Step 7   (chmod 755)
/usr/share/applications/*.desktop      # Step 8
/etc/xdg/mimeapps.list                 # Step 8
```

---

## STEP 4 — Calamares configuration

### 4a. `/etc/calamares/settings.conf`
```yaml
# NCDE Poseidon — Calamares settings. branding: ncde, single desktop (no packagechooser).
modules-search: [ local ]
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
  - removeuser
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
branding: ncde
prompt-install: false
dont-chroot: false
oem-setup: false
disable-cancel: false
disable-cancel-during-exec: false
hide-back-and-next-during-exec: false
quit-at-end: false
```

### 4b. `/etc/calamares/modules/partition.conf`
Start from the stock `/usr/share/calamares/modules/partition.conf` and set these keys (leave the rest):
```yaml
efi:
    mountPoint:         "/boot/efi"
    recommendedSize:    512MiB
    minimumSize:        64MiB
    label:              "EFI"
userSwapChoices:
    - none
    - small
    - suspend
    - file
allowManualPartitioning:   false      # one-click — no manual page
initialPartitioningChoice: erase      # auto erase + install
initialSwapChoice:         file       # swapfile (goes in @swap on btrfs)
defaultFileSystemType:     "btrfs"
availableFileSystemTypes:  ["btrfs"]  # btrfs only (System Restore requires it)
```

### 4c. `/etc/calamares/modules/mount.conf` (full)
```yaml
extraMounts:
    - device: proc
      fs: proc
      mountPoint: /proc
    - device: sys
      fs: sysfs
      mountPoint: /sys
    - device: /dev
      mountPoint: /dev
      options: [ bind ]
    - device: tmpfs
      fs: tmpfs
      mountPoint: /run
    - device: /run/udev
      mountPoint: /run/udev
      options: [ bind ]
    - device: efivarfs
      fs: efivarfs
      mountPoint: /sys/firmware/efi/efivars
      efi: true
btrfsSubvolumes:
    - mountPoint: /
      subvolume: /@
    - mountPoint: /home
      subvolume: /@home
    - mountPoint: /var/cache
      subvolume: /@cache
    - mountPoint: /var/log
      subvolume: /@log
    - mountPoint: /restore
      subvolume: /@restore
btrfsSwapSubvol: /@swap
mountOptions:
    - filesystem: default
      options: [ defaults ]
    - filesystem: efi
      options: [ defaults, umask=0077 ]
    - filesystem: btrfs
      options: [ defaults, compress=zstd:1 ]
    - filesystem: btrfs_swap
      options: [ defaults, noatime ]
```

### 4d. `/etc/calamares/modules/shellprocess.conf`
```yaml
dontChroot: true
timeout: 9999
verbose: false
script:
    - command: "/usr/bin/post_install.sh"
i18n:
     name: "Charting the new realm — configuring your system…"
     name[en]: "Charting the new realm — configuring your system…"
```

### 4e. `/etc/calamares/modules/unpackfs.conf`
Copy stock and set the `unpack` source(s) to **your live medium's** squashfs + kernel. Example for an
archiso-style layout shipping the linux-zen kernel:
```yaml
unpack:
    -   source: "/run/archiso/bootmnt/arch/x86_64/airootfs.sfs"
        sourcefs: "squashfs"
        destination: ""
    -   source: "/run/archiso/bootmnt/arch/boot/x86_64/vmlinuz-linux-zen"
        sourcefs: "file"
        destination: "/boot/vmlinuz-linux-zen"
```

---

## STEP 5 — Branding (`/etc/calamares/branding/ncde/`)

### 5a. `branding.desc`
```yaml
componentName:  ncde
welcomeStyleCalamares:   false
welcomeExpandingLogo:    true
windowExpanding:         normal
windowSize:              900px,560px
windowPlacement:         center
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
style:
    sidebarBackground:    "#020608"
    sidebarText:          "#c9a96b"
    sidebarTextSelect:    "#e2c772"
    sidebarTextCurrent:   "#f3e3b5"
    sidebarTextHighlight: "#b88a2c"
```

### 5b. `stylesheet.qss` — COMPLETE (this is what makes it look NCDE, not black)
> Calamares auto-loads `stylesheet.qss` from the branding dir. Documented top-level IDs are **`mainApp`,
> `sidebarApp`, `logoApp`** (verified — see Sources). The navigation/button bar has **no documented ID**,
> so we paint it via the base `QWidget` rule and style its buttons via `QPushButton`. A background set on
> one widget does **not** cascade to children in Qt, so we theme **every widget class** — that's the fix.
> Palette: parchment `#e8d6a9` · abyss `#020608` · gilt `#b88a2c`/`#e2c772` · burgundy `#6b2018` ·
> ink `#2a1a08` · cream `#f3e3b5` · frame `#6f4f15`.
```css
/* base — no widget may fall back to a dark default */
QWidget {
    background-color: #e8d6a9; color: #2a1a08;
    font-family: "Cormorant Garamond", serif; font-size: 15px;
}
#mainApp { background-color: #e8d6a9; }

/* sidebar (ID beats the QWidget rule, so it stays dark) */
#sidebarApp, #sidebarApp QWidget { background-color: #020608; }
#sidebarMenuApp QPushButton {
    color: #c9a96b; background-color: transparent; border: none;
    font-family: "IM Fell DW Pica SC", "Cinzel", serif;
    font-size: 13px; letter-spacing: 2px; text-align: left; padding: 10px 16px;
}
#sidebarMenuApp QPushButton:checked { color: #f3e3b5; border-left: 3px solid #b88a2c; }

/* buttons (incl. the Back/Next/Install bar — base QWidget paints its container) */
QPushButton {
    background-color: #2a1a08; color: #f3e3b5; border: 1px solid #6f4f15;
    border-radius: 3px; padding: 9px 22px; min-width: 90px;
    font-family: "IM Fell DW Pica SC", serif; font-size: 13px; letter-spacing: 2px;
}
QPushButton:hover    { background-color: #3a2614; }
QPushButton:disabled { background-color: #c9b07c; color: #8a6a3a; border-color: #b88a2c; }
QPushButton:default  { background-color: #6b2018; color: #f3e3b5; border: 1px solid #3a0a06; } /* Install/Next */
QPushButton:default:hover { background-color: #812620; }

/* labels / headings */
QLabel { background: transparent; color: #2a1a08; }
QLabel#titleLabel { font-size: 30px; font-style: italic; font-weight: 600; }

/* inputs + combo dropdown */
QLineEdit, QComboBox, QSpinBox, QPlainTextEdit, QTextEdit {
    background-color: #f3e3b5; color: #2a1a08; border: 1px solid #6f4f15;
    border-radius: 2px; padding: 6px 10px;
    selection-background-color: #b88a2c; selection-color: #1a0f04;
}
QLineEdit:focus, QComboBox:focus, QSpinBox:focus { border: 1px solid #b88a2c; }
QComboBox QAbstractItemView {
    background-color: #f3e3b5; color: #2a1a08; border: 1px solid #6f4f15;
    selection-background-color: #b88a2c; selection-color: #1a0f04;
}

/* item views — partition picker, summary, users list */
QTreeView, QListView, QTableView, QAbstractItemView {
    background-color: #f3e3b5; alternate-background-color: #e8d6a9; color: #2a1a08;
    border: 1px solid #6f4f15;
    selection-background-color: #b88a2c; selection-color: #1a0f04;
}
QHeaderView::section {
    background-color: #2a1a08; color: #f3e3b5; padding: 4px 8px;
    border: none; border-right: 1px solid #6f4f15;
}

/* frames / groups / tabs */
QFrame { background: transparent; }
QGroupBox { background: transparent; border: 1px solid #6f4f15; border-radius: 3px; margin-top: 12px; }
QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 4px; color: #2a1a08; }
QTabWidget::pane { border: 1px solid #6f4f15; }
QTabBar::tab { background: #c9b07c; color: #2a1a08; padding: 6px 14px; }
QTabBar::tab:selected { background: #e8d6a9; border-bottom: 2px solid #b88a2c; }

/* progress (install phase) */
QProgressBar {
    background-color: #1a0f04; border: 1px solid #6f4f15; border-radius: 3px;
    height: 18px; text-align: center; color: #f3e3b5;
    font-family: "JetBrains Mono", monospace; font-size: 11px;
}
QProgressBar::chunk { background-color: #b88a2c; border-radius: 2px; }

/* checks / radios */
QCheckBox, QRadioButton { background: transparent; color: #2a1a08; font-size: 16px; }
QCheckBox::indicator:checked, QRadioButton::indicator:checked {
    background-color: #6b2018; border: 1px solid #6f4f15;
}

/* scroll areas + scrollbars */
QAbstractScrollArea, QScrollArea { background-color: #e8d6a9; border: none; }
QScrollBar:vertical   { background: #e8d6a9; width: 12px; margin: 0; }
QScrollBar:horizontal { background: #e8d6a9; height: 12px; margin: 0; }
QScrollBar::handle { background: #b88a2c; border-radius: 5px; min-height: 24px; min-width: 24px; }
QScrollBar::add-line, QScrollBar::sub-line { height: 0; width: 0; }
```

### 5c. `show.qml` — slideshow (slideshowAPI 2)
> API 2 loads async at startup; the root must provide `onActivate()`/`onLeave()` and must **not** use
> `onComplete`. The slideshow plays during the **install (exec)** phase only. The four `slideN.png` plates
> carry the art + text.
```qml
import QtQuick 2.5
import calamares.slideshow 1.0
Presentation {
    id: presentation
    function onActivate() { presentation.startTimer(); }
    function onLeave()    { presentation.stopTimer(); }
    Timer { interval: 9000; running: true; repeat: true; onTriggered: presentation.goToNextSlide() }
    Slide { Rectangle { anchors.fill: parent; color: "#020608" }
        Image { anchors.fill: parent; source: "slide1.png"; fillMode: Image.PreserveAspectFit; smooth: true; mipmap: true } }
    Slide { Rectangle { anchors.fill: parent; color: "#020608" }
        Image { anchors.fill: parent; source: "slide2.png"; fillMode: Image.PreserveAspectFit; smooth: true; mipmap: true } }
    Slide { Rectangle { anchors.fill: parent; color: "#020608" }
        Image { anchors.fill: parent; source: "slide3.png"; fillMode: Image.PreserveAspectFit; smooth: true; mipmap: true } }
    Slide { Rectangle { anchors.fill: parent; color: "#020608" }
        Image { anchors.fill: parent; source: "slide4.png"; fillMode: Image.PreserveAspectFit; smooth: true; mipmap: true } }
}
```
> If the slides never appear: it's almost always because the **install never started** (Install button
> invisible — fixed by 5b). Confirm the install actually runs. Image files must sit beside `show.qml`.

### 5d. Art assets
Supply from the NCDE design kit (Mucha/parchment/ocean plates): `logo.png` (trident), `welcome.png`,
`slide1.png`…`slide4.png` (full-bleed plates), `language.svg`. These are the only raster files. **No
Archcraft art.** Placeholders are fine to test the flow; swap in the real plates for ship.

---

## STEP 6 — Launcher `/etc/calamares/launch.sh` (chmod 755) — **NO `-style kvantum`**
```bash
#!/usr/bin/bash
## NCDE Poseidon — installer launcher
DIR="/etc/calamares"
KERNEL=`uname -r`
if [[ -d "/run/archiso/copytoram" ]]; then
	sudo sed -i -e 's|/run/archiso/bootmnt/arch/x86_64/airootfs.sfs|/run/archiso/copytoram/airootfs.sfs|g' "$DIR"/modules/unpackfs.conf
	sudo sed -i -e "s|/run/archiso/bootmnt/arch/boot/x86_64/vmlinuz-linux-zen|/usr/lib/modules/$KERNEL/vmlinuz|g" "$DIR"/modules/unpackfs.conf
fi
pkexec calamares -d
```
Also ship a passwordless polkit rule so the live user launches it without a prompt — e.g.
`/etc/polkit-1/rules.d/49-nopasswd-calamares.rules` allowing action `io.calamares.calamares.pkexec.run`
for the local active user (the post-install script removes it on the installed system).

---

## STEP 7 — Post-install scripts (verbatim — `/usr/bin/`, both chmod 755)

### 7a. `post_install.sh`
```bash
#!/bin/bash
## NCDE Poseidon — runs on the LIVE system: detect GPU, then chroot into target.
if [[ `pidof calamares` ]]; then
	chroot_path="/tmp/`lsblk | grep 'calamares-root' | awk '{ print $NF }' | sed -e 's/\/tmp\///' -e 's/\/.*$//' | tail -n1`"
else
	chroot_path='/mnt'
fi
if [[ "$chroot_path" == '/tmp/' ]] ; then
	echo "+---------------------->>"; echo "[!] Fatal error: `basename $0`: chroot_path is empty!"
fi
arch_chroot() { chroot "$chroot_path" /bin/bash -c ${1}; }
gpu_file="$chroot_path"/var/log/gpu-card-info.bash
_detect_vga_drivers() {
    local card=no; local driver=no
    if [[ -n "`lspci -k | grep -P 'VGA|3D|Display' | grep -w "${2}"`" ]]; then
        card=yes
        if [[ -n "`lsmod | grep -w ${3}`" ]]; then driver=yes; fi
        if [[ -n "`lspci -k | grep -wA2 "${2}" | grep 'Kernel driver in use: ${3}'`" ]]; then driver=yes; fi
    fi
    echo "${1}_card=$card"     >> ${gpu_file}
    echo "${1}_driver=$driver" >> ${gpu_file}
}
echo "[*] Detecting GPU card & drivers used in live session..."
_detect_vga_drivers 'amd' 'AMD' 'amdgpu'
_detect_vga_drivers 'intel' 'Intel Corporation' 'i915'
_detect_vga_drivers 'nvidia' 'NVIDIA' 'nvidia'
cat ${gpu_file}
if [[ `pidof calamares` ]]; then
	echo "[*] Running chroot post installation script in target system..."
	arch_chroot "/usr/bin/chrooted_post_install.sh"
fi
```

### 7b. `chrooted_post_install.sh`
```bash
#!/bin/bash
## NCDE Poseidon — runs in the TARGET. sddm->ncde-portal, grub theme ncde, create greeter user,
## remove live autologin, ensure /etc/ncde/xsession executable (do NOT clobber it), drop stock kernel.
new_user=`cat /etc/passwd | grep "/home" | cut -d: -f1 | head -1`
_is_pkg_installed() { pacman -Q "$1" >& /dev/null; }
_remove_a_pkg() { pacman -Rsn --noconfirm "$1"; }
_remove_pkgs_if_installed() { for p in "$@"; do _is_pkg_installed "$p" && _remove_a_pkg "$p"; done; }

_manage_systemd_services() {
	local _enable_services=('NetworkManager.service' 'bluetooth.service' 'cups.service'
		'avahi-daemon.service' 'systemd-timesyncd.service' 'ncde-portal.service'
		'apparmor.service' 'ufw.service')
	echo "[*] Creating ncde-portal greeter user..."
	useradd --system --home-dir /var/lib/ncde-portal --create-home --shell /usr/sbin/nologin ncde-portal 2>/dev/null || true
	[[ `lspci | grep -i virtualbox` ]] && systemctl enable -f vboxservice.service
	[[ `lspci -k | grep -i qemu` ]] && systemctl enable -f qemu-guest-agent.service
	for srv in "${_enable_services[@]}"; do echo "[*] Enabling $srv..."; systemctl enable -f ${srv}; done
	systemctl disable -f multi-user.target
}
_remove_vbox_pkgs() {
	local vbox_pkg='virtualbox-guest-utils'; local vsrvfile='/etc/systemd/system/multi-user.target.wants/vboxservice.service'
	lspci | grep -i "virtualbox" >/dev/null
	if [[ "$?" != 0 ]]; then
		test -n "`pacman -Q $vbox_pkg 2>/dev/null`" && pacman -Rnsdd ${vbox_pkg} --noconfirm
		[[ -L "$vsrvfile" ]] && rm -f "$vsrvfile"
	fi
}
_remove_vmware_pkgs() {
	local vmware_pkgs=('open-vm-tools' 'xf86-input-vmmouse' 'xf86-video-vmware')
	lspci | grep -i "VMware" >/dev/null
	if [[ "$?" != 0 ]]; then for p in "${vmware_pkgs[@]}"; do
		test -n "`pacman -Q ${p} 2>/dev/null`" && pacman -Rnsdd ${p} --noconfirm; done
	fi
}
_remove_qemu_pkgs() {
	local qemu_pkg='qemu-guest-agent'; local qsrvfile='/etc/systemd/system/multi-user.target.wants/qemu-guest-agent.service'
	lspci -k | grep -i "qemu" >/dev/null
	if [[ "$?" != 0 ]]; then
		test -n "`pacman -Q $qemu_pkg 2>/dev/null`" && pacman -Rnsdd ${qemu_pkg} --noconfirm
		[[ -L "$qsrvfile" ]] && rm -f "$qsrvfile"
	fi
}
_remove_unwanted_graphics_drivers() {
	local gpu_file='/var/log/gpu-card-info.bash'
	local amd_card='' intel_card='' nvidia_card='' nvidia_driver=''
	[[ -r "$gpu_file" ]] && source ${gpu_file}
	if   [[ -n "`lspci -k | grep 'Advanced Micro Devices'`" ]]; then amd_card=yes
	elif [[ -n "`lspci -k | grep 'AMD/ATI'`" ]]; then amd_card=yes
	elif [[ -n "`lspci -k | grep 'Radeon'`" ]]; then amd_card=yes; fi
	[[ "$amd_card" == 'no' ]] && _remove_pkgs_if_installed xf86-video-amdgpu xf86-video-ati
	[[ "$intel_card" == 'no' ]] && _remove_pkgs_if_installed xf86-video-intel
	[[ "$nvidia_card" == 'no' ]] && _remove_pkgs_if_installed xf86-video-nouveau nvidia-open nvidia-settings nvidia-utils
	[[ "$nvidia_driver" == 'no' ]] && _remove_pkgs_if_installed nvidia-open nvidia-settings nvidia-utils
	[[ "$nvidia_driver" == 'yes' ]] && _remove_pkgs_if_installed xf86-video-nouveau
}
_remove_unwanted_ucode() {
	cpu="`grep -w "^vendor_id" /proc/cpuinfo | head -n 1 | awk '{print $3}'`"
	case "$cpu" in
		GenuineIntel) _remove_pkgs_if_installed amd-ucode ;;
		*)            _remove_pkgs_if_installed intel-ucode ;;
	esac
}
_remove_unwanted_packages() {
    # NCDE is zen-only: drop stock 'linux' (+ broadcom-wl built against it) so 'pacman -Syu'
    # can't resurrect a second kernel. Also drop the Calamares engine + live-only tools.
    local _packages_to_remove=('calamares-config' 'linux' 'broadcom-wl'
        'calamares' 'archinstall' 'arch-install-scripts' 'ckbcomp' 'boost'
        'mkinitcpio-archiso' 'darkhttpd' 'irssi' 'lftp' 'lynx' 'mc' 'ddrescue' 'testdisk' 'syslinux')
    for rpkg in "${_packages_to_remove[@]}"; do
        pacman -Q ${rpkg} &>/dev/null && pacman -Rnsc ${rpkg} --noconfirm
    done
}
_clean_target_system() {
    local _files_to_remove=(
        /etc/sudoers.d/02_g_wheel /etc/systemd/system/getty@tty1.service.d
        /etc/initcpio /etc/mkinitcpio-archiso.conf
        /etc/polkit-1/rules.d/49-nopasswd-calamares.rules
        /etc/{group-,gshadow-,passwd-,shadow-} /etc/udev/rules.d/81-dhcpcd.rules
        /etc/skel/{.xinitrc,.xsession,.xprofile}
        /home/"$new_user"/{.xinitrc,.xsession,.xprofile,.wget-hsts,.screenrc,.ICEauthority}
        /root/{.automated_script.sh,.zlogin} /root/{.xinitrc,.xsession,.xprofile}
        /usr/local/bin/{Installation_guide} /usr/share/applications/xfce4-about.desktop
        /usr/share/calamares /{gpg.conf,gpg-agent.conf,pubring.gpg,secring.gpg}
        /var/lib/NetworkManager/NetworkManager.state )
    for dfile in "${_files_to_remove[@]}"; do rm -rf ${dfile}; done
    find /usr/lib/initcpio -name archiso* -type f -exec rm '{}' \;
}
_perform_various_stuff() {
	echo "[*] Copying grub theme..."; mkdir -p /boot/grub/themes; cp -rf /usr/share/grub/themes/ncde /boot/grub/themes
	# /etc/ncde/xsession ships as the executable PAM session entry point. Do NOT overwrite it.
	mkdir -p /etc/ncde
	chmod +x /etc/ncde/xsession 2>/dev/null
	chmod +x /usr/local/bin/ncde-x11-session /usr/local/bin/ncde-wm 2>/dev/null
	install -d -m0755 /var/cache/ncde/qmlcache
	echo "[*] Removing live autologin drop-in..."
	rm -rf /etc/systemd/system/ncde-portal.service.d/autologin.conf
	rmdir  /etc/systemd/system/ncde-portal.service.d 2>/dev/null || true
	runuser -l ${new_user} -c 'xdg-user-dirs-update'
	runuser -l ${new_user} -c 'xdg-user-dirs-gtk-update'
	sed -i 's/volatile/auto/g' /etc/systemd/journald.conf 2>>/tmp/.errlog
	sed -i 's/.*pam_wheel\.so/#&/' /etc/pam.d/su
}
_manage_systemd_services
_remove_vbox_pkgs
_remove_vmware_pkgs
_remove_qemu_pkgs
_remove_unwanted_graphics_drivers
_remove_unwanted_ucode
_remove_unwanted_packages
_clean_target_system
_perform_various_stuff
```
> These assume the NCDE rootfs already ships: `ncde-portal.service`, `/etc/ncde/xsession` (executable),
> `usr/local/bin/{ncde-x11-session,ncde-wm}`, and the grub theme `usr/share/grub/themes/ncde`.

---

## STEP 8 — App launchers + mime defaults
`/usr/share/applications/calamares.desktop`:
```ini
[Desktop Entry]
Type=Application
Name=Install NCDE Poseidon
GenericName=System Installer
Exec=sh -c "/etc/calamares/launch.sh"
Icon=/etc/calamares/branding/ncde/logo.png
Terminal=false
Categories=Qt;System;
X-AppStream-Ignore=true
```
Native-app launchers (NCDE draws canvas icons; `Icon=` here is only a freedesktop fallback):
```ini
# orchidee.desktop      Exec=/usr/local/bin/orchidee %U          MimeType=inode/directory;
# verve-text.desktop    Exec=/usr/local/bin/verve-text %F        MimeType=text/plain;
# binnie.desktop        Exec=/usr/local/bin/binnie
# magpie-talker.desktop Exec=/usr/local/bin/magpie-talker
# hummingbird-courier.desktop Exec=/usr/local/bin/hummingbird-courier %U  MimeType=x-scheme-handler/mailto;
# ncde-command.desktop  Exec=/usr/local/bin/ncde-command
```
`/etc/xdg/mimeapps.list`:
```ini
[Default Applications]
inode/directory=orchidee.desktop
x-scheme-handler/mailto=hummingbird-courier.desktop
text/plain=verve-text.desktop
```

---

## STEP 9 — Permissions
```
chmod 755 /etc/calamares/launch.sh /usr/bin/post_install.sh /usr/bin/chrooted_post_install.sh
chmod 644 /etc/calamares/branding/ncde/* /etc/calamares/*.conf /etc/calamares/modules/*.conf
```

## STEP 10 — Test
1. Quick UI/theme check on any machine: `pkexec calamares -d` → the window must paint **parchment body +
   visible burgundy Install button**, no black panes. (Don't click through to a real install here.)
2. Full install test in a VM **with a blank target disk + GL**:
   ```
   qemu-img create -f qcow2 test-disk.qcow2 40G
   qemu-system-x86_64 -enable-kvm -m 4096 -smp 4 -machine q35 \
     -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
     -drive if=pflash,format=raw,file=OVMF_VARS.4m.fd \
     -device virtio-vga-gl -display gtk,gl=on \
     -drive file=test-disk.qcow2,if=virtio,format=qcow2 \
     -cdrom your-ncde.iso -boot d
   ```
3. Run it end to end: auto-partition (no manual page) → install → slideshow plays → reboots to the
   `ncde-portal` greeter.

## STEP 11 — Troubleshooting (if any pane is still dark)
Run `calamares -d`, open the **Debug** window → **Widget Tree** (dumps every widget's object name to the
log) → match `stylesheet.qss` IDs to the real names. Use **Reload stylesheet** to iterate live. `mainApp`,
`sidebarApp`, `logoApp` are standard; the base `QWidget` rule covers anything unnamed.

---

## 9. Acceptance / NO-ARCHCRAFT checklist
- [ ] Window paints full parchment/ocean/gilt — no black panes
- [ ] **Install button visible** (burgundy) and advances Summary → install
- [ ] One-click auto-partition, all-btrfs, subvolumes `@/@home/@cache/@log/@restore` + swapfile, no manual page
- [ ] Slideshow (slide1-4) plays during install
- [ ] Completes → reboots to the `ncde-portal` greeter
- [ ] Ctrl+Alt+R opens the recovery app
- [ ] No `branding/archcraft`; installer icon = NCDE logo (not `archcraft-green`)
- [ ] No `archcraft` strings in any `.desktop`/`.qss`/`.qml`/`.desc`
- [ ] `launch.sh` = `pkexec calamares -d` (no `-style kvantum`)
- [ ] Greeter offers only the NCDE session (no `openbox.desktop` xsession)

## Sources (verified)
- Calamares Deploy Guide — branding, stylesheet IDs (`mainApp`/`sidebarApp`/`logoApp`), debug widget tree:
  https://calamares.euroquis.nl/docs/deploy-guide and https://github.com/calamares/calamares/wiki/Deploy-Guide
- Branding README + slideshow API 2 (`onActivate`/`onLeave`, async load):
  https://github.com/calamares/calamares/blob/calamares/src/branding/README.md
- partition.conf / mount.conf module references:
  https://github.com/calamares/calamares/blob/calamares/src/modules/partition/partition.conf ·
  https://github.com/calamares/calamares/blob/calamares/src/modules/mount/mount.conf
