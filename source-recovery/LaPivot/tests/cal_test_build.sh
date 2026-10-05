#!/bin/bash
# cal_test_build.sh <workdir> <output-binary> <test.cpp> [more src/*.cpp ...]
# Builds a Calendar/LeapFrogPond/NCDEGeo test: moc headers, the given sources,
# and a trap stub (ud2) for every method the test does not link — calling one crashes loudly.
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$1"; OUT="$2"; shift 2
QT="$(pkg-config --cflags --libs Qt6Core Qt6DBus Qt6Gui Qt6Qml Qt6Quick Qt6Test)"
for h in "$L"/src/CalendarBackend.h "$L"/src/LeapFrogPond.h "$L"/src/NCDEGeo.h "$L"/src/Lelan.h; do
  /usr/lib/qt6/moc "$h" -o "$W/moc_$(basename "$h" .h).cpp"
done
SRCS=("$W"/moc_*.cpp)
for f in "$@"; do
  SRCS+=("$f")
  if grep -q Q_OBJECT "$f"; then /usr/lib/qt6/moc "$f" -o "$W/$(basename "$f" .cpp).moc"; fi
done
for f in "${SRCS[@]}"; do
  g++ -std=c++17 -fPIC -c -Wno-sfinae-incomplete -Wno-deprecated-declarations -I"$L/src" -I"$W" "$f" -o "$W/$(basename "$f" .cpp).o" $QT
done
nm --defined-only "$W"/*.o | awk '{print $3}' | sort -u > "$W/defined.txt"
{ echo .text; echo 'ncde_stub_trap: ud2'
  nm --undefined-only "$W"/*.o | awk '$2 ~ /^_ZNK?(15CalendarBackend|12LeapFrogPond|7NCDEGeo|5Lelan)/ {print $2}' | sort -u | grep -vxF -f "$W/defined.txt" \
    | awk '{print ".globl "$1"\n.set "$1", ncde_stub_trap"}'; } > "$W/stubs.s"
as "$W/stubs.s" -o "$W/stubs.o"
g++ -o "$OUT" "$W"/*.o $QT