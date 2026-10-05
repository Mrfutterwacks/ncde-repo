#!/bin/bash
# bluetooth_qml_test.sh [BluetoothTab.qml] — render BluetoothTab.qml (default: the payload one) with the
# rebuilt Lelan Bluetooth code on live BlueZ (tests/bluetooth_qml_host.cpp). Its QML neighbours come from
# a symlink mirror of the payload directory. PNGs -> $OUT (default tests/out). Exit 1 on any QML warning.
MP=$(cd "$(dirname "$(readlink -f "$0")")/../../.." && pwd)   # my-project/, wherever the USB is mounted
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap "rm -rf \"$W\"" EXIT
P="$MP/files/full-patch-20260711/src/usr/share/ncde"
TAB="${1:-$P/BluetoothTab.qml}"; OUT="${OUT:-$L/tests/out}"; mkdir -p "$OUT"
cp -rs "$P" "$W/ncde"; rm -f "$W/ncde/BluetoothTab.qml"; cp "$TAB" "$W/ncde/BluetoothTab.qml"
bash "$L/tests/lelan_test_build.sh" "$W" "$W/host" "$L/tests/bluetooth_qml_host.cpp" "$L/src/Lelan_bluetooth.cpp"
BLUETOOTH_TAB="$W/ncde/BluetoothTab.qml" OUT="$OUT" "$W/host"
