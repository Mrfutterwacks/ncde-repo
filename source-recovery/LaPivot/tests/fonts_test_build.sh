#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
WORK="$ROOT/tests/.fonts-build"
OUT="$WORK/fonts_test"
mkdir -p "$WORK"
trap 'rm -rf "$WORK"' EXIT

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6DBus Qt6Test)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6DBus Qt6Test)"
/usr/lib/qt6/moc "$ROOT/src/FontManager.h" -o "$WORK/moc_FontManager.cpp"
/usr/lib/qt6/moc "$ROOT/tests/fonts_test.cpp" -o "$WORK/fonts_test.moc"
g++ -std=c++17 -fPIC -Wall -Wextra -I"$ROOT/src" $QT_CFLAGS \
    "$ROOT/tests/fonts_test.cpp" "$ROOT/src/FontManager.cpp" "$WORK/moc_FontManager.cpp" \
    $QT_LIBS -o "$OUT"

dbus-run-session -- bash -c \
    'export DBUS_SYSTEM_BUS_ADDRESS="$DBUS_SESSION_BUS_ADDRESS"; exec "$1"' \
    bash "$OUT"
