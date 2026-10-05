#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/tests/.colour-engine-build"
rm -rf "$BUILD"
mkdir -p "$BUILD/home"
trap 'rm -rf "$BUILD"' EXIT

QT_FLAGS="$(pkg-config --cflags --libs Qt6Core Qt6Gui)"
/usr/lib/qt6/moc "$ROOT/src/NCDEEngine.h" -o "$BUILD/moc_NCDEEngine.cpp"
/usr/lib/qt6/moc "$ROOT/src/NcdeTheme.h" -o "$BUILD/moc_NcdeTheme.cpp"
g++ -std=c++17 -fPIC -Wall -Wextra -Werror -I"$ROOT/src" \
    "$ROOT/src/ColorMath.cpp" "$ROOT/src/NCDEEngine.cpp" "$ROOT/src/NcdeTheme.cpp" \
    "$ROOT/tests/colour_engine_test.cpp" \
    "$BUILD/moc_NCDEEngine.cpp" "$BUILD/moc_NcdeTheme.cpp" \
    -o "$BUILD/colour_engine_test" $QT_FLAGS
HOME="$BUILD/home" XDG_CONFIG_HOME="$BUILD/home/.config" \
    NCDE_NO_EXTERNAL_THEME_COMMANDS=1 "$BUILD/colour_engine_test"
