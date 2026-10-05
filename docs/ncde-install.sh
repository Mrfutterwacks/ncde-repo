#!/usr/bin/env bash
# ncde-install.sh — install the NCDE X11 desktop from the production tree
# (~/ncde-staging/LaPivot — the ONLY tree; the old frozen tree is DEAD, 2026-07-05).
# CORRECTED 2026-07-17: that tree is gone (dev machine that hosted it is gone; confirmed absent
# on this machine and the USB backup). This script will now fail at the SRC check below — there
# is no separate tree to install from anymore, the live system IS the desktop. Kept for historical
# reference only; do not expect it to run as-is. See CLAUDE.md banner for the corrected model.
# Non-destructive: adds files + an SDDM session entry. Does NOT touch GRUB,
# the bootloader, machine-id, or replace the existing display manager.
# NOTE: SDDM-era legacy script — the ISO uses ncde-portal, not SDDM.
set -euo pipefail

if [[ $EUID -ne 0 ]]; then
  echo "Run as root (writes to /usr, runs pacman):  sudo $0" >&2
  exit 1
fi

REAL_HOME="$(getent passwd "${SUDO_USER:-$USER}" | cut -d: -f6)"
SRC="$REAL_HOME/ncde-staging/LaPivot"
[[ -d "$SRC" ]] || { echo "Source tree not found: $SRC" >&2; exit 1; }

echo "==> 1. Binaries -> /usr/local/bin (mode 755), excluding non-desktop leftovers"
EXCLUDE='ncde-tauri-installer|ncde-tauri-installer\.session.*\.bak|ncde-installer-session|choose-mirror|Installation_guide|livecd-sound'
for f in "$SRC"/usr/local/bin/*; do
  name="$(basename "$f")"
  if [[ "$name" =~ ^($EXCLUDE)$ ]]; then echo "    skip $name"; continue; fi
  install -Dm755 "$f" "/usr/local/bin/$name"
done

echo "==> 2. QML tree -> /usr/share/ncde"
mkdir -p /usr/share/ncde
cp -a "$SRC"/usr/share/ncde/. /usr/share/ncde/

echo "==> 3. Fonts -> /usr/share/fonts/ncde"
mkdir -p /usr/share/fonts/ncde
cp -a "$SRC"/usr/share/fonts/ncde/. /usr/share/fonts/ncde/

echo "==> 3b. picom.conf -> /etc/picom.conf   [required by ncde-x11-session]"
cp -a "$SRC"/etc/picom.conf /etc/picom.conf

echo "==> 3c. Cursor theme -> /usr/share/icons/NCDE-Poseidon   [XCURSOR_THEME]"
mkdir -p /usr/share/icons/NCDE-Poseidon
cp -a "$SRC"/usr/share/icons/NCDE-Poseidon/. /usr/share/icons/NCDE-Poseidon/

echo "==> 3d. QML disk cache dir -> /var/cache/ncde/qmlcache   [QML_DISK_CACHE_PATH]"
install -d -m1777 /var/cache/ncde/qmlcache

chown -R root:root /usr/share/ncde /usr/share/fonts/ncde /usr/share/icons/NCDE-Poseidon /etc/picom.conf

echo "==> 4. Refresh font cache"
fc-cache -f

echo "==> 5. Install Qt6 + picom deps"
pacman -S --needed --noconfirm qt6-base qt6-declarative qt6-svg picom

echo "==> 6. SDDM session entry -> /usr/share/xsessions/ncde.desktop"
install -Dm644 /dev/stdin /usr/share/xsessions/ncde.desktop <<'EOF'
[Desktop Entry]
Name=NCDE
Comment=Neoclassical Desktop Environment
Exec=/usr/local/bin/ncde-x11-session
TryExec=/usr/local/bin/ncde-wm
Type=Application
DesktopNames=NCDE
EOF

echo
echo "Done. Log out, then pick 'NCDE' from the SDDM session menu (top-right gear)."
echo "First-launch debug log: ~/ncde-debug.log"
