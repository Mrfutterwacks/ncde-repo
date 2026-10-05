#!/bin/bash
# settings_preview.sh — build and open the Settings preview window (tests/settings_preview.cpp): the payload's
# Network + Bluetooth tabs on the rebuilt Lelan, live. Nothing is installed; close the window to end it.
MP=$(cd "$(dirname "$(readlink -f "$0")")/../../.." && pwd)   # my-project/, wherever the USB is mounted
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="${PREVIEW_DIR:-$(mktemp -d)}"
P="$MP/files/full-patch-20260711/src/usr/share/ncde"
bash "$L/tests/lelan_test_build.sh" "$W" "$W/settings_preview" "$L/tests/settings_preview.cpp" "$L/src/Lelan_network.cpp" "$L/src/Lelan_bluetooth.cpp"
NCDE_QML_DIR="$P" exec "$W/settings_preview"
