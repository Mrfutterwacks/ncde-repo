#!/bin/bash
# cursor_parity.sh — Kith cursor: oracle LaPivot vs the installed source-built LaPivot, same QML, same harness
# (l2_livebus_shot.sh). Each binary runs from a copy NAMED LaPivot (ncde-kith-tint only arms for comm LaPivot).
# Captures per binary: materialized Kith theme files, X resources + XSETTINGS, the cursor env its children
# get, and the cursor actually on screen over desktop / top panel / dock. Then diffs the two.
#   usage: cursor_parity.sh [out-dir]     env: NEW (default /usr/local/bin/LaPivot)  WAIT (default 15)
set -u
HERE=$(cd "$(dirname "$(readlink -f "$0")")" && pwd)
OUT=${1:-$(mktemp -d "${TMPDIR:-/tmp}/cursorparity.XXXXXX")}
ORACLE=$HERE/../oracle/LaPivot.oracle
NEW=${NEW:-/usr/local/bin/LaPivot}
WAIT=${WAIT:-15}
POINTS="960,600:desktop 960,12:toppanel 960,1185:dock 30,600:leftedge"
for which in oracle new; do
  W=$OUT/$which; mkdir -p "$W/bin"
  # each run gets its own display so the oracle's and the rebuild's X state never mix
  DISP=""; for n in $(seq 70 99); do [ -e /tmp/.X11-unix/X$n ] || [ -e /tmp/.X$n-lock ] || { DISP=:$n; break; }; done
  if [ $which = oracle ]; then cp "$ORACLE" "$W/bin/LaPivot"; else cp "$NEW" "$W/bin/LaPivot"; fi
  chmod +x "$W/bin/LaPivot"
  ACTION="
    cp -a '$W/rt/ncde-cursors' '$W/cursors' 2>/dev/null
    xrdb -query > '$W/xrdb.txt' 2>&1
    xprop -root > '$W/xprop-root.txt' 2>&1
    for p in \$(pgrep -f 'ncde-kith-tint' ); do
      tr '\0' '\n' < /proc/\$p/environ 2>/dev/null | grep -qx 'DISPLAY=$DISP' || continue
      tr '\0' '\n' < /proc/\$p/environ | grep -E '^(XCURSOR|QT_|GDK|GTK)' | sort > '$W/child-env.txt'; break
    done
    python3 '$HERE/cursor_probe.py' $which $POINTS > '$W/probe.txt' 2>&1
    # client windows started with the session's cursor env (what LaPivot hands every app it launches);
    # private D-Bus + config so nothing reaches the operator's own session
    CENV=\$(grep '^XCURSOR' '$W/child-env.txt' | tr '\n' ' ')
    mkdir -p '$W/kitty-cfg'
    env \$CENV KITTY_CONFIG_DIRECTORY='$W/kitty-cfg' dbus-run-session -- kitty --title cursorprobe-kitty >/dev/null 2>&1 &
    env \$CENV dbus-run-session -- thunar '$W' >/dev/null 2>&1 &
    sleep 5
    for t in cursorprobe-kitty thunar; do
      g=\$(xwininfo -root -tree | grep -i \"\$t\" | grep -oE '[0-9]+x[0-9]+\\+[-0-9]+\\+[-0-9]+' | sort -t x -k1 -n | tail -1)
      [ -n \"\$g\" ] || { echo \"$which \$t: no window\" >> '$W/probe.txt'; continue; }
      w=\${g%%x*}; r=\${g#*x}; h=\${r%%+*}; r=\${r#*+}; x=\${r%%+*}; y=\${r#*+}
      python3 '$HERE/cursor_probe.py' $which \"\$((x + w / 2)),\$((y + h / 2)):\${t#cursorprobe-}\" >> '$W/probe.txt' 2>&1
    done
  "
  DISP=$DISP WORK=$W BIN=$W/bin/LaPivot bash "$HERE/l2_livebus_shot.sh" "$W/shot.png" "$WAIT" "$ACTION" > "$W/harness.txt" 2>&1
  grep -a 'kith-tint' "$W/lapivot.log" > "$W/kith-log.txt" 2>/dev/null
done
echo "== on-screen cursor =="; cat "$OUT/oracle/probe.txt" "$OUT/new/probe.txt"
echo "== kith-tint log =="; for w in oracle new; do sed "s/^/$w: /" "$OUT/$w/kith-log.txt"; done
echo "== materialized Kith files (pristine snapshot) =="
for w in oracle new; do (cd "$OUT/$w/cursors" 2>/dev/null && find . -type f -o -type l | sort | while read f; do
  if [ -L "$f" ]; then echo "$f -> $(readlink "$f" | sed "s|$OUT/$w/rt|RT|;s|/run/user/[0-9]*|RT|")"; else echo "$f $(sha256sum < "$f" | cut -c1-12)"; fi; done) > "$OUT/$w/cursor-files.txt"; done
diff "$OUT/oracle/cursor-files.txt" "$OUT/new/cursor-files.txt" | head -40 || true
echo "== X resources =="; diff "$OUT/oracle/xrdb.txt" "$OUT/new/xrdb.txt" || true
echo "== child cursor env =="; diff "$OUT/oracle/child-env.txt" "$OUT/new/child-env.txt" || true
echo "out: $OUT"
