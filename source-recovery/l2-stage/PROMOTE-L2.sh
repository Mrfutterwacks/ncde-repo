#!/bin/bash
# PROMOTE-L2.sh — make the tested L2 the one LaPivot. Run ONLY by the operator, after testing the "NCDE L2" session:
#   sudo bash <this folder>/PROMOTE-L2.sh
# What it does (everything is backed up first to /var/lib/ncde-update/pre-L2-<time>/, with a ROLLBACK.sh there):
#   1. /usr/local/bin/LaPivot      <- the installed, tested /usr/local/bin/LaPivot-L2 (atomic swap, cap_sys_nice)
#   2. /usr/share/ncde/            <- /usr/share/ncde-l2/ (the QML L2 ran with)
#   3. /usr/local/bin/ncde-x11-session <- ncde-x11-session-promoted from this folder (the full canonical session
#      script; only DISPLAY is kept from the login manager now)
#   4. ncde-automount retired for every user (global mask) (Lelan auto-mounts; StorageTab's toggle drives it)
#   5. the "NCDE L2" session entry and its files removed
#   6. Openbox uninstalled (pacman -Rs openbox; nothing depends on it) — the login screen shows "NCDE" only
# It does NOT touch ncde-portal, /usr/share/xsessions/ncde.desktop, or anything outside the paths above.
# /usr/share/ncde/screensaver (empty, only in the old tree) is kept: the rsync excludes it.
# AFTER promoting, before the next NCDE patch/package update: the payload still carries the OLD LaPivot (raw + 3
# Iris binary transforms) and publish.sh --check still demands live == raw+3. Both must move to the source-built
# LaPivot first, or an update puts the old binary back. (Agents prepare that; the operator publishes.)
set -euo pipefail
[ "$(id -u)" = 0 ] || { echo "run with sudo"; exit 1; }
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
L2_BIN=/usr/local/bin/LaPivot-L2
L2_ASSETS=/usr/share/ncde-l2
REAL_BIN=/usr/local/bin/LaPivot
REAL_ASSETS=/usr/share/ncde
SESSION=/usr/local/bin/ncde-x11-session
NEW_SESSION="$HERE/ncde-x11-session-promoted"
L2_FILES=(/usr/local/bin/ncde-x11-session-l2 /usr/share/xsessions/ncde-l2.desktop)

[ -x "$L2_BIN" ] && [ -f "$L2_ASSETS/main.qml" ] || { echo "L2 is not installed (run INSTALL-L2.sh and test it first)"; exit 1; }
[ -f "$NEW_SESSION" ] && bash -n "$NEW_SESSION" || { echo "missing or broken $NEW_SESSION"; exit 1; }
# the binary being promoted must be the one that was staged (and tested)
STAGED_SHA=$(cut -d' ' -f1 "$HERE/LaPivot-L2.sha256")
[ "$(sha256sum "$L2_BIN" | cut -d' ' -f1)" = "$STAGED_SHA" ] \
    || { echo "$L2_BIN is not the staged LaPivot-L2 (sha256 differs) — re-run INSTALL-L2.sh and test again"; exit 1; }

echo "This makes L2 the only LaPivot (backups + ROLLBACK.sh are kept)."
read -r -p 'Type "promote" to continue: ' answer
[ "$answer" = promote ] || { echo "not promoted"; exit 1; }

TS=$(date +%Y%m%d-%H%M%S)
B=/var/lib/ncde-update/pre-L2-$TS
mkdir -p "$B"
cp -a "$REAL_BIN" "$B/LaPivot"
cp -a "$REAL_ASSETS" "$B/ncde"
cp -a "$SESSION" "$B/ncde-x11-session"
getcap "$REAL_BIN" > "$B/LaPivot.caps" || true
pacman -Q openbox >/dev/null 2>&1 && pacman -Q openbox > "$B/openbox-was-installed"
cat > "$B/ROLLBACK.sh" <<ROLLBACK
#!/bin/bash
# Puts back the LaPivot, /usr/share/ncde and session script from before PROMOTE-L2.sh ($TS).
set -euo pipefail
[ "\$(id -u)" = 0 ] || { echo "run with sudo"; exit 1; }
install -m 755 "$B/LaPivot" "$REAL_BIN.new" && setcap cap_sys_nice+ep "$REAL_BIN.new" && mv -f "$REAL_BIN.new" "$REAL_BIN"
rsync -a --delete "$B/ncde/" "$REAL_ASSETS/"
install -m 755 "$B/ncde-x11-session" "$SESSION"
systemctl --global unmask ncde-automount.service
[ -f "$B/openbox-was-installed" ] && pacman -S --needed --noconfirm openbox
echo "Rolled back. Log out and back in."
ROLLBACK
chmod 755 "$B/ROLLBACK.sh"
echo "Backed up to $B"

# 1. binary: write beside, set the capability, then one rename (safe while LaPivot runs)
install -m 755 "$L2_BIN" "$REAL_BIN.new"
setcap cap_sys_nice+ep "$REAL_BIN.new"
mv -f "$REAL_BIN.new" "$REAL_BIN"
# 2. QML
rsync -a --delete --exclude '*.prebak*' --exclude 'screensaver/' "$L2_ASSETS/" "$REAL_ASSETS/"
# 3. session script
install -m 755 "$NEW_SESSION" "$SESSION.new"
mv -f "$SESSION.new" "$SESSION"
# 4. ncde-automount: Lelan mounts now (S7). It is enabled per user (~/.config/systemd/user/*.wants), which
#    --global disable cannot reach; a global mask in /etc/systemd/user overrides it for every user.
systemctl --global mask ncde-automount.service
# 5. L2 session entry gone
rm -f "${L2_FILES[@]}" "$L2_BIN"
rm -rf "$L2_ASSETS"
# 6. Openbox off the login screen: uninstall it (only the openbox package goes; nothing requires it)
if pacman -Q openbox >/dev/null 2>&1; then pacman -Rs --noconfirm openbox; fi

echo
echo "L2 is now LaPivot:"
getcap "$REAL_BIN"
echo "  QML files: $(find "$REAL_ASSETS" -type f | wc -l)"
echo "  sessions:  $(ls /usr/share/xsessions)"
echo "Log out and log in to \"NCDE\". Undo: sudo bash $B/ROLLBACK.sh"
