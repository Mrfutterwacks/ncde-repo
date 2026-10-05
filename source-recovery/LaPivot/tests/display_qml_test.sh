#!/bin/bash
# display_qml_test.sh [DisplayTab.qml] — render DisplayTab.qml (default: the payload one) with the
# rebuilt Lelan Settings display code (xrandr queried, changes recorded) (tests/display_qml_host.cpp). Its QML neighbours come from
# a symlink mirror of the payload directory. PNGs -> $OUT (default tests/out). Exit 1 on any QML warning.
MP=$(cd "$(dirname "$(readlink -f "$0")")/../../.." && pwd)   # my-project/, wherever the USB is mounted
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap "rm -rf \"$W\"" EXIT
P="$MP/files/full-patch-20260711/src/usr/share/ncde"
TAB="${1:-$P/DisplayTab.qml}"; OUT="${OUT:-$L/tests/out}"; mkdir -p "$OUT"
cp -rs "$P" "$W/ncde"; rm -f "$W/ncde/DisplayTab.qml"; cp "$TAB" "$W/ncde/DisplayTab.qml"
bash "$L/tests/lelan_test_build.sh" "$W" "$W/host" "$L/tests/display_qml_host.cpp" "$L/src/Settings_display.cpp" "$L/src/Settings_core.cpp" "$L/src/Lelan_config.cpp" "$L/src/Lelan_time.cpp"
DISPLAY_TAB="$W/ncde/DisplayTab.qml" OUT="$OUT" ${DBG:-} "$W/host"
