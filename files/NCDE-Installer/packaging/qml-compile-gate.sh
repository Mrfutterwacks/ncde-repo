#!/bin/bash
# qml-compile-gate.sh <dir> — compile EVERY .qml under <dir> with the real QML engine and fail if any
# file cannot compile. Added 2026-10-01 after Verdantfolio shipped dead for two days: Main.qml set
# `clip: true` twice on one Flickable ("Property value set multiple times"), a hard compile error that
# kills the whole window. qmllint does NOT report it; only the engine does.
#
# Qt.createComponent() compiles and resolves imports but instantiates nothing: no windows, no audio,
# no camera, no D-Bus. Runs offscreen. Backups (*.prebak*, *.reverted-*, ...) are skipped.
#
# Allowed (registered at run time, not on disk): org.freedesktop.gstreamer.* — magpie-talker runs
# gst_init and creates qml6glsink before it loads MagpieTalker.qml, and that registers the module.
set -u
DIR="${1:?usage: qml-compile-gate.sh <dir>}"
T="$(mktemp -d "${TMPDIR:-/tmp}/qml-gate.XXXXXX")"; trap 'rm -rf "$T"' EXIT
find "$DIR" -name '*.qml' ! -name '*prebak*' ! -name '*.reverted-*' ! -name '*.retired-*' \
     ! -name '*.wrong-*' ! -name '*.iso-aside-*' ! -name '*.bak' ! -name '*.orig' \
     ! -path '*/__pycache__/*' | sort > "$T/list"
N=$(wc -l < "$T/list")
[ "$N" -gt 0 ] || { echo "qml gate: no .qml files under $DIR"; exit 1; }
{ printf '%s\n' 'import QtQuick' 'QtObject { Component.onCompleted: { var L = ['
  python3 -c 'import json,sys,urllib.parse
for l in sys.stdin.read().splitlines(): print(json.dumps("file://"+urllib.parse.quote(l))+",")' < "$T/list"
  printf '%s\n' '""]; var n = 0;' \
    'for (var i = 0; i < L.length - 1; i++) { var c = Qt.createComponent(L[i], Component.PreferSynchronous);' \
    '  n++; if (c.status === Component.Error) console.log("QMLGATE-ERR " + c.errorString().split(String.fromCharCode(10)).join(" | ")); }' \
    'console.log("QMLGATE-DONE " + n); Qt.quit() } }'
} > "$T/runner.qml"
QT_QPA_PLATFORM=offscreen QT_FORCE_STDERR_LOGGING=1 timeout 600 qml6 "$T/runner.qml" > "$T/out" 2>&1
DONE=$(sed -n 's/.*QMLGATE-DONE \([0-9]*\).*/\1/p' "$T/out")
[ "$DONE" = "$N" ] || { echo "qml gate: runner did not finish ($DONE of $N):"; head -20 "$T/out"; exit 1; }
grep 'QMLGATE-ERR ' "$T/out" | sed 's/.*QMLGATE-ERR //' \
  | grep -v -E 'module "org\.freedesktop\.gstreamer\.[A-Za-z0-9.]*" is not installed' > "$T/bad" || true
if [ -s "$T/bad" ]; then
  echo "qml gate: $(wc -l < "$T/bad") QML file(s) do not compile:"; sed "s|file://$DIR/||g" "$T/bad"; exit 1
fi
echo "qml gate: all $N QML files compile."
