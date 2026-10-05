#!/bin/bash
# compile_all.sh — fresh compile of every rebuilt LaPivot source (+ moc), -Wall -Wextra. One line per unit.
# -Wno-sfinae-incomplete: GCC 16 fires it inside Qt 6 headers (QChar/QBitArray), not in LaPivot code. The CMake build (real gate) is warning-clean.
L="$(cd "$(dirname "$0")/.." && pwd)"; T="$(mktemp -d)"; trap 'rm -rf "$T"' EXIT; cd "$T"
QT="$(pkg-config --cflags Qt6Core Qt6Gui Qt6DBus Qt6Qml Qt6Quick libpulse)"; fails=0
for f in "$L"/src/*.cpp; do grep -q Q_OBJECT "$f" && /usr/lib/qt6/moc "$f" -o "$T/$(basename "$f" .cpp).moc"; done
for h in "$L"/src/*.h; do grep -q Q_OBJECT "$h" && /usr/lib/qt6/moc "$h" -o "moc_$(basename "$h" .h).cpp"; done
for f in "$L"/src/*.cpp "$T"/moc_*.cpp; do
  b=$(basename "$f" .cpp)
  if g++ -std=c++17 -fPIC -c -Wall -Wextra -Wno-unused-parameter -Wno-sfinae-incomplete -I"$L/src" -I"$T" "$f" -o "$T/$b.o" $QT 2>"$T/$b.err"; then
    w=$(grep -c "warning:" "$T/$b.err"); echo "OK   $b ($w warnings)"; [ "$w" = 0 ] || grep "warning:" "$T/$b.err" | head -3
  else echo "FAIL $b"; grep "error" "$T/$b.err" | head -6; fails=$((fails+1)); fi
done
echo "compile: $([ $fails = 0 ] && echo PASS || echo "FAIL ($fails)")"
