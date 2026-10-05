#!/bin/bash
set -euo pipefail

L="$(cd "$(dirname "$0")/.." && pwd)"
W="$L/tests/.launcher_test.$$"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/home"
export HOME="$W/home"
export XDG_CONFIG_HOME="$HOME/.config"
export QT_QPA_PLATFORM=offscreen
export TMPDIR="$W"
export NCDE_TEST_OUTPUT="$W/argv.json"
export NCDE_CAPTURE_HELPER="$W/capture"

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6Test)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6Test)"
/usr/lib/qt6/moc "$L/tests/launcher_test.cpp" -o "$W/launcher_test.moc"
/usr/lib/qt6/moc "$L/src/Launcher.h" -o "$W/moc_Launcher.cpp"
g++ -std=c++17 -fPIC -Wall -Wextra $QT_CFLAGS "$L/tests/launcher_capture.cpp" \
    -o "$NCDE_CAPTURE_HELPER" $QT_LIBS
g++ -std=c++17 -fPIC -Wall -Wextra -Wno-sfinae-incomplete $QT_CFLAGS -I"$L/src" -I"$W" \
    "$W/moc_Launcher.cpp" "$L/src/Launcher.cpp" "$L/tests/launcher_test.cpp" \
    -o "$W/test" $QT_LIBS
"$W/test"
