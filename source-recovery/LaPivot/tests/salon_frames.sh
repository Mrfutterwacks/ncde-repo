#!/bin/bash
# salon_frames.sh: salon_probe.sh + 14 frames of the Salon slot over ~9 s (one breath) as $W/f_NN.png, to compare oracle vs rebuild animation/glow.
# Salon Nocturne / La'Ombre state probe: the oracle and a rebuilt LaPivot run the SAME QML (a probe copy of the
# canonical tree bound over /usr/share/ncde, because the oracle ignores NCDE_ASSET_BASE), real system bus, private
# session bus with a silent fake MPRIS player. main.qml gets a probe Timer that logs, every 2 s, everything the
# Salon widget gates its animations on. Run both binaries and diff the PROBE lines.
#   usage: [ACTION='shell run on the display'] salon_probe.sh <binary> <idle|play> [out.png]
# Nothing is hardcoded: paths from this script's location, user/uid/home from whoever runs it.
set -u
HERE=$(cd "$(dirname "$(readlink -f "$0")")" && pwd)
SR=$(cd "$HERE/../.." && pwd)
QML=${QML:-$(cd "$SR/../files/full-patch-20260711/src/usr/share/ncde" && pwd)}
BIN=$1; MODE=${2:-idle}
W=$(mktemp -d "${TMPDIR:-/tmp}/salonprobe.XXXXXX")
OUT=${3:-$W/shot.png}
U=$(id -un); UID_=$(id -u); H=$HOME; RT=/run/user/$UID_
for n in $(seq 70 99); do [ -e /tmp/.X11-unix/X$n ] || [ -e /tmp/.X$n-lock ] || { DISP=:$n; break; }; done
cp "$BIN" "$W/LaPivot"; cp "$HERE/fake_mpris.py" "$W/"
rsync -a --exclude '*.prebak*' --exclude '__pycache__' "$QML/" "$W/qml/"
python3 - "$W/qml/main.qml" <<'EOF'
import sys, re
p = sys.argv[1]; s = open(p).read()
probe = '''
    Timer { interval: 2000; running: true; repeat: true; onTriggered: console.log("PROBE",
        "level=" + animPolicy.level, "decorative=" + animPolicy.decorative, "idleLoops=" + animPolicy.idleLoops,
        "screenIdle=" + animPolicy.screenIdle, "reduceMotion=" + animPolicy.reduceMotion,
        "lowPower=" + animPolicy.lowPower, "obscured=" + animPolicy.desktopObscured,
        "mediaActive=" + widget_data.mediaActive, "mediaPlaying=" + widget_data.mediaPlaying,
        "title=" + widget_data.mediaTitle, "pos=" + widget_data.mediaPosition, "dur=" + widget_data.mediaDuration) }
'''
# insert right after the first top-level object's opening brace
i = s.index("{", s.index("\n", s.index("import")) if "import" in s else 0)
m = re.search(r"^\S[^\n]*\{\s*$", s, re.M)
i = m.end()
s = s[:i] + probe + s[i:]
open(p, "w").write(s)
EOF
mkdir -p "$W/home/.config" "$W/rt"; chmod 700 "$W/rt"
cp -a "$H/.config/ncde" "$W/home/.config/" 2>/dev/null
cp -a "$H/Pictures" "$W/home/" 2>/dev/null
cat > "$W/inner.sh" <<EOF
#!/bin/bash
if [ "$MODE" = play ]; then
  python3 "$W/fake_mpris.py" probe > "$W/fake.log" 2>&1 &
  for i in \$(seq 50); do grep -q READY "$W/fake.log" 2>/dev/null && break; sleep 0.1; done
  ( sleep 8   # after LaPivot is up: a player that STARTS playing, like pressing play in Spotify
    dbus-send --session --dest=org.mpris.MediaPlayer2.probe /org/mpris/MediaPlayer2 org.ncde.FakePlayer.SetTrack \
        string:/probe/1 string:"Probe Song" int64:240000000
    dbus-send --session --dest=org.mpris.MediaPlayer2.probe /org/mpris/MediaPlayer2 org.ncde.FakePlayer.SetStatus \
        string:Playing int64:30000000 ) &
fi
exec /usr/local/bin/LaPivot
EOF
chmod +x "$W/inner.sh"
Xvfb "$DISP" -screen 0 1920x1200x24 -nolisten tcp >"$W/xvfb.log" 2>&1 & XP=$!
for i in $(seq 30); do [ -e "/tmp/.X11-unix/X${DISP#:}" ] && break; sleep 0.1; done
bwrap --ro-bind / / --dev /dev --proc /proc --tmpfs /tmp \
  --bind "$W/home" "$H" --bind "$W/rt" "$RT" --ro-bind /run/dbus /run/dbus \
  --ro-bind /tmp/.X11-unix /tmp/.X11-unix --bind "$W" "$W" \
  --ro-bind "$W/LaPivot" /usr/local/bin/LaPivot --ro-bind "$W/qml" /usr/share/ncde \
  --die-with-parent --unshare-pid \
  env -i LANG="${LANG:-}" HOME="$H" USER="$U" DISPLAY="$DISP" XDG_RUNTIME_DIR="$RT" \
      PATH=/usr/local/bin:/usr/bin NCDE_ASSET_BASE=/usr/share/ncde/ QT_QPA_PLATFORM=xcb XDG_SESSION_TYPE=x11 XDG_CURRENT_DESKTOP=NCDE GDK_BACKEND=x11 QT_QPA_PLATFORMTHEME=ncde GTK_CSD=0 XCURSOR_THEME=Kith XCURSOR_SIZE=32 QSG_RENDER_LOOP=threaded QML_XHR_ALLOW_FILE_READ=1 QML_XHR_ALLOW_FILE_WRITE=1 \
  dbus-run-session -- "$W/inner.sh" >"$W/lapivot.log" 2>&1 & BP=$!
sleep 10
# optional ACTION (env), run on the sandbox display after start-up, e.g. open/maximize/minimize a window
[ -n "${ACTION:-}" ] && { DISPLAY="$DISP" bash -c "$ACTION" >"$W/action.log" 2>&1; sleep 2; }
sleep 4; for i in $(seq -w 0 13); do DISPLAY="$DISP" import -window root -crop 320x320+1598+820 "$W/f_$i.png" 2>/dev/null; sleep 0.6; done
LP=$(pgrep -f "^/usr/local/bin/LaPivot" | head -1)
c0=$(awk '{print $14+$15}' /proc/$LP/stat); sleep 6; c1=$(awk '{print $14+$15}' /proc/$LP/stat)
echo "cpu: $(( (c1-c0)*100/600 ))% of one core over 6 s"
DISPLAY="$DISP" import -window root "$OUT" 2>/dev/null
sleep 1.5; DISPLAY="$DISP" import -window root "$W/shot2.png" 2>/dev/null
# Salon slot = bottom widget of the right column; how much of it changed in 1.5 s (0 = frozen)
echo "salon motion: $(magick compare -metric AE -fuzz 3% "$OUT[317x255+1600+690]" "$W/shot2.png[317x255+1600+690]" null: 2>&1) px"
kill $BP 2>/dev/null; sleep 1; kill -9 $BP 2>/dev/null; kill $XP 2>/dev/null; wait 2>/dev/null
echo "work: $W"
grep -a "PROBE" "$W/lapivot.log" | tail -2 | sed 's/^.*PROBE/PROBE/'
