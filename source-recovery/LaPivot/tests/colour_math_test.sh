#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/tests/.colour-math-build"
rm -rf "$BUILD"
mkdir -p "$BUILD"
trap 'rm -rf "$BUILD"' EXIT

QT_FLAGS="$(pkg-config --cflags --libs Qt6Core Qt6Gui)"
g++ -std=c++17 -fPIC -Wall -Wextra -Werror -I"$ROOT/src" \
    "$ROOT/src/ColorMath.cpp" "$ROOT/tests/colour_math_test.cpp" \
    -o "$BUILD/colour_math_test" $QT_FLAGS
"$BUILD/colour_math_test"
