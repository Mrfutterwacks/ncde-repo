#!/bin/bash
# Like l2_sandbox_shot.sh but with the REAL system bus (Sentinel, logind, NM, BlueZ, UDisks): the login crash 2026-10-01 18:43 (unregistered a{ss} reply from Sentinel) only shows with it.
# Nothing is hardcoded: paths come from this script's location, the user/uid/home from whoever runs it.
#   usage: l2_sandbox_shot.sh [out.png] [wait-seconds] [action run on the sandbox display]
#   env:   BIN (default: <source-recovery>/l2-stage/LaPivot-L2)  WORK (default: a fresh mktemp dir)
#          DISP (default: first free :70..:99)
set -u
HERE=$(cd "$(dirname "$(readlink -f "$0")")" && pwd)
SR=$(cd "$HERE/../.." && pwd)                                   # source-recovery/
QML=${QML:-$(cd "$SR/../files/full-patch-20260711/src/usr/share/ncde" && pwd)}
BIN=${BIN:-$SR/l2-stage/LaPivot-L2}
W=${WORK:-$(mktemp -d "${TMPDIR:-/tmp}/l2shot.XXXXXX")}
U=$(id -un); UID_=$(id -u); H=$HOME; RT=/run/user/$UID_
if [ -z "${DISP:-}" ]; then
  for n in $(seq 70 99); do [ -e /tmp/.X11-unix/X$n ] || [ -e /tmp/.X$n-lock ] || { DISP=:$n; break; }; done
fi
OUT=${1:-$W/l2.png}; WAIT=${2:-12}; ACTION=${3:-}
[ -x "$BIN" ] || { echo "no binary: $BIN" >&2; exit 1; }
rm -rf "$W/home" "$W/rt"; mkdir -p "$W/home/.config" "$W/rt"; chmod 700 "$W/rt"
cp -a "$H/.config/ncde" "$W/home/.config/" 2>/dev/null
cp -a "$H/Pictures" "$W/home/" 2>/dev/null
Xvfb "$DISP" -screen 0 1920x1200x24 -nolisten tcp >"$W/xvfb.log" 2>&1 & XP=$!
for i in $(seq 30); do [ -e "/tmp/.X11-unix/X${DISP#:}" ] && break; sleep 0.1; done
bwrap --ro-bind / / --dev /dev --proc /proc --tmpfs /tmp \
  --bind "$W/home" "$H" --bind "$W/rt" "$RT" --ro-bind /run/dbus /run/dbus \
  --ro-bind /tmp/.X11-unix /tmp/.X11-unix --bind "$W" "$W" --die-with-parent --unshare-pid \
  env -i LANG="${LANG:-}" LC_ALL="${LC_ALL:-}" LC_TIME="${LC_TIME:-}" HOME="$H" USER="$U" DISPLAY="$DISP" XDG_RUNTIME_DIR="$RT" \
      PATH=/usr/local/bin:/usr/bin NCDE_ASSET_BASE="$QML/" QT_QPA_PLATFORM=xcb XDG_SESSION_TYPE=x11 XDG_CURRENT_DESKTOP=NCDE GDK_BACKEND=x11 QT_QPA_PLATFORMTHEME=ncde GTK_CSD=0 XCURSOR_THEME=Kith XCURSOR_SIZE=32 QSG_RENDER_LOOP=threaded QML_XHR_ALLOW_FILE_READ=1 QML_XHR_ALLOW_FILE_WRITE=1 \
  dbus-run-session -- "$BIN" >"$W/lapivot.log" 2>&1 & BP=$!
sleep "$WAIT"
if [ -n "$ACTION" ]; then DISPLAY="$DISP" bash -c "$ACTION"; sleep 2; fi
DISPLAY="$DISP" import -window root "$OUT" 2>/dev/null || DISPLAY="$DISP" xwd -root -silent | magick xwd:- "$OUT"
kill $BP 2>/dev/null; sleep 1; kill -9 $BP 2>/dev/null; kill $XP 2>/dev/null
wait 2>/dev/null
echo "work: $W"; echo "shot: $OUT"; ls -la "$OUT"
