#!/bin/bash
# INSTALL-L2.sh — add the "NCDE L2" test session BESIDE the normal NCDE session (operator runs it).
#   sudo bash /run/media/<you>/NCDE-BACKUP/my-project/source-recovery/l2-stage/INSTALL-L2.sh
# Installs:  /usr/local/bin/LaPivot-L2 (cap_sys_nice), /usr/share/ncde-l2/ (the new QML tree),
#            /usr/local/bin/ncde-x11-session-l2, /usr/share/xsessions/ncde-l2.desktop
# Does NOT touch /usr/local/bin/LaPivot, /usr/share/ncde, the NCDE session or ncde-portal.
# Undo: UNINSTALL-L2.sh.
set -euo pipefail
[ "$(id -u)" = 0 ] || { echo "run with sudo"; exit 1; }
HERE="$(cd "$(dirname "$0")" && pwd)"
QML="$HERE/../../files/full-patch-20260711/src/usr/share/ncde/"
[ -f "$QML/main.qml" ] || { echo "QML tree not found at $QML"; exit 1; }
(cd "$HERE" && sha256sum -c LaPivot-L2.sha256) || { echo "LaPivot-L2 checksum mismatch — not installing"; exit 1; }

install -m 755 "$HERE/LaPivot-L2" /usr/local/bin/LaPivot-L2.new
setcap cap_sys_nice+ep /usr/local/bin/LaPivot-L2.new
mv -f /usr/local/bin/LaPivot-L2.new /usr/local/bin/LaPivot-L2

mkdir -p /usr/share/ncde-l2
rsync -a --delete --exclude '*.prebak*' --exclude '__pycache__' "$QML" /usr/share/ncde-l2/

install -m 755 "$HERE/ncde-x11-session-l2" /usr/local/bin/ncde-x11-session-l2
install -m 644 "$HERE/ncde-l2.desktop" /usr/share/xsessions/ncde-l2.desktop

echo "NCDE L2 installed:"
getcap /usr/local/bin/LaPivot-L2
echo "  QML files: $(find /usr/share/ncde-l2 -type f | wc -l)"
echo "Log out and pick \"NCDE L2\" at the login screen. Its log: ~/ncde-l2-debug.log"
echo "If it misbehaves, log out and pick \"NCDE\" — that session is untouched."
