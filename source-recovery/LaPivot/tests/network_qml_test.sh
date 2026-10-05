#!/bin/bash
# network_qml_test.sh [NetworkTab.qml] — build tests/network_qml_host.cpp with the rebuilt Lelan network
# code and render the payload's NetworkTab.qml against live NetworkManager (read-only). PNGs -> $OUT.
MP=$(cd "$(dirname "$(readlink -f "$0")")/../../.." && pwd)   # my-project/, wherever the USB is mounted
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
TAB="${1:-$MP/files/full-patch-20260711/src/usr/share/ncde/NetworkTab.qml}"
OUT="${OUT:-$L/tests/out}"; mkdir -p "$OUT"
bash "$L/tests/lelan_test_build.sh" "$W" "$W/host" "$L/tests/network_qml_host.cpp" "$L/src/Lelan_network.cpp"
NETWORK_TAB="$TAB" OUT="$OUT" "$W/host"
