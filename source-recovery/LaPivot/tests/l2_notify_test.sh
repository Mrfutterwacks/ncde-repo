#!/bin/bash
# ncde-notify.so companion against a LaPivot build, the way the promoted session runs it:
# the binary is mounted AS /usr/local/bin/LaPivot (the companion only arms for that exe) and
# LD_PRELOAD=/usr/lib/ncde/ncde-notify.so, real system bus, host locale (like l2_livebus_shot.sh).
# Then a toast is sent over $XDG_RUNTIME_DIR/ncde-notify.sock exactly as ncde-news does.
# PASS = companion resolved notify via dlsym (never the old-binary offset), LaPivot still alive
# after the toast, toast visible in the shot.
#   usage: l2_notify_test.sh [out.png]     env: BIN (default <source-recovery>/LaPivot/build-l2/LaPivot-L2)
set -u
HERE=$(cd "$(dirname "$(readlink -f "$0")")" && pwd)
SR=$(cd "$HERE/../.." && pwd)
QML=${QML:-$(cd "$SR/../files/full-patch-20260711/src/usr/share/ncde" && pwd)}
BIN=${BIN:-$SR/LaPivot/build-l2/LaPivot-L2}
PRELOAD=${PRELOAD:-/usr/lib/ncde/ncde-notify.so}
W=$(mktemp -d "${TMPDIR:-/tmp}/l2notify.XXXXXX")
U=$(id -un); UID_=$(id -u); H=$HOME; RT=/run/user/$UID_
for n in $(seq 70 99); do [ -e /tmp/.X11-unix/X$n ] || [ -e /tmp/.X$n-lock ] || { DISP=:$n; break; }; done
OUT=${1:-$W/notify.png}
[ -x "$BIN" ] || { echo "no binary: $BIN" >&2; exit 1; }
[ -f "$PRELOAD" ] || { echo "no companion: $PRELOAD" >&2; exit 1; }
cp "$BIN" "$W/LaPivot"                      # inside $W: bwrap's private /tmp hides other temp paths
mkdir -p "$W/home/.config" "$W/rt"; chmod 700 "$W/rt"
cp -a "$H/.config/ncde" "$W/home/.config/" 2>/dev/null
cp -a "$H/Pictures" "$W/home/" 2>/dev/null
Xvfb "$DISP" -screen 0 1920x1200x24 -nolisten tcp >"$W/xvfb.log" 2>&1 & XP=$!
for i in $(seq 30); do [ -e "/tmp/.X11-unix/X${DISP#:}" ] && break; sleep 0.1; done
bwrap --ro-bind / / --dev /dev --proc /proc --tmpfs /tmp \
  --bind "$W/home" "$H" --bind "$W/rt" "$RT" --ro-bind /run/dbus /run/dbus \
  --ro-bind /tmp/.X11-unix /tmp/.X11-unix --bind "$W" "$W" --ro-bind "$W/LaPivot" /usr/local/bin/LaPivot \
  --die-with-parent --unshare-pid \
  env -i LANG="${LANG:-}" HOME="$H" USER="$U" DISPLAY="$DISP" XDG_RUNTIME_DIR="$RT" \
      PATH=/usr/local/bin:/usr/bin NCDE_ASSET_BASE="$QML/" QT_QPA_PLATFORM=xcb XDG_SESSION_TYPE=x11 XDG_CURRENT_DESKTOP=NCDE GDK_BACKEND=x11 QT_QPA_PLATFORMTHEME=ncde GTK_CSD=0 XCURSOR_THEME=Kith XCURSOR_SIZE=32 QSG_RENDER_LOOP=threaded QML_XHR_ALLOW_FILE_READ=1 QML_XHR_ALLOW_FILE_WRITE=1 \
      NCDE_NOTIFY_DEBUG=1 \
  dbus-run-session -- env LD_PRELOAD="$PRELOAD" /usr/local/bin/LaPivot >"$W/lapivot.log" 2>&1 & BP=$!
sleep 14
python3 - "$W/rt/ncde-notify.sock" <<'EOF'
import json, socket, sys
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM); s.settimeout(2.0); s.connect(sys.argv[1])
s.sendall(json.dumps({"category": "notification", "app_name": "l2-notify-test", "summary": "L2 notify test",
                      "body": "sent over ncde-notify.sock", "icon": "emblem-web", "timeout": 8000}).encode())
s.shutdown(socket.SHUT_WR); s.close(); print("sent")
EOF
sleep 2
DISPLAY="$DISP" import -window root "$OUT" 2>/dev/null
ALIVE=no; kill -0 $BP 2>/dev/null && pgrep -f "^/usr/local/bin/LaPivot" >/dev/null && ALIVE=yes
kill $BP 2>/dev/null; sleep 1; kill -9 $BP 2>/dev/null; kill $XP 2>/dev/null; wait 2>/dev/null
echo "work: $W"; echo "shot: $OUT"
grep -a "ncde-notify" "$W/lapivot.log" | head -20
echo "LaPivot alive after toast: $ALIVE"
grep -aq "resolved via dlsym" "$W/lapivot.log" && [ $ALIVE = yes ] && echo PASS || echo FAIL
