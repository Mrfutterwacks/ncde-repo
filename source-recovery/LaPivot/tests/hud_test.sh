#!/bin/bash
set -euo pipefail

L="$(cd "$(dirname "$0")/.." && pwd)"
W="$L/tests/.hud_test.$$"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/home"
export HOME="$W/home"
export XDG_CONFIG_HOME="$HOME/.config"
export QT_QPA_PLATFORM=offscreen
export TMPDIR="$W"

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6Test)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6Test)"
/usr/lib/qt6/moc "$L/src/HudManager.h" -o "$W/moc_HudManager.cpp"
/usr/lib/qt6/moc "$L/tests/hud_test.cpp" -o "$W/hud_test.moc"
g++ -std=c++17 -fPIC -Wall -Wextra -Wno-sfinae-incomplete $QT_CFLAGS -I"$L/src" -I"$W" \
    "$W/moc_HudManager.cpp" "$L/src/HudManager.cpp" "$L/tests/hud_test.cpp" \
    -o "$W/test" $QT_LIBS
"$W/test"
