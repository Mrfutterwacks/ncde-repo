#!/bin/bash
# lelan_test_build.sh <workdir> <output-binary> <test.cpp> [more src/*.cpp ...]
# Builds a Lelan test: moc(Lelan.h + lelan_dbus_relay.h + any moc-needing test .cpp), the given sources,
# and a trap stub (ud2) for every Lelan / Settings method the test does not link — calling one crashes loudly.
# Settings.h is moc'd only when a linked source uses it.
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$1"; OUT="$2"; shift 2
QT="$(pkg-config --cflags --libs Qt6Core Qt6DBus Qt6Gui Qt6Qml Qt6Quick Qt6Test)"
/usr/lib/qt6/moc "$L/src/Lelan.h" -o "$W/moc_Lelan.cpp"
/usr/lib/qt6/moc "$L/src/lelan_dbus_relay.h" -o "$W/moc_lelan_dbus_relay.cpp"
SRCS=("$W/moc_Lelan.cpp" "$W/moc_lelan_dbus_relay.cpp")
if grep -lq 'Settings.h' "$@"; then /usr/lib/qt6/moc "$L/src/Settings.h" -o "$W/moc_Settings.cpp"; SRCS+=("$W/moc_Settings.cpp"); fi
for f in "$@"; do
  SRCS+=("$f")
  if grep -q Q_OBJECT "$f"; then /usr/lib/qt6/moc "$f" -o "$W/$(basename "$f" .cpp).moc"; fi
done
for f in "${SRCS[@]}"; do
  g++ -std=c++17 -fPIC -c -Wno-sfinae-incomplete -Wno-deprecated-declarations -I"$L/src" -I"$W" "$f" -o "$W/$(basename "$f" .cpp).o" $QT
done
nm --defined-only "$W"/*.o | awk '{print $3}' | sort -u > "$W/defined.txt"
{ echo .text; echo 'ncde_stub_trap: ud2'
  nm --undefined-only "$W"/*.o | awk '$2 ~ /^_ZN5Lelan|^_ZNK5Lelan|^_ZN8Settings|^_ZNK8Settings/ {print $2}' | sort -u | grep -vxF -f "$W/defined.txt" \
    | awk '{print ".globl "$1"\n.set "$1", ncde_stub_trap"}'; } > "$W/stubs.s"
as "$W/stubs.s" -o "$W/stubs.o"
g++ -o "$OUT" "$W"/*.o $QT
