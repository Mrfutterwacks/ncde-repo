#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
WORK="$ROOT/tests/.cursor-fonts-build"
OUT="$WORK/cursor_render_test"
mkdir -p "$WORK"
trap 'rm -rf "$WORK"' EXIT

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6Gui Qt6DBus Qt6Qml Qt6Quick Qt6Test xcb xcb-render)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6Gui Qt6DBus Qt6Qml Qt6Quick Qt6Test xcb xcb-render)"
/usr/lib/qt6/moc "$ROOT/src/CursorManager.h" -o "$WORK/moc_CursorManager.cpp"
/usr/lib/qt6/moc "$ROOT/tests/cursor_render_test.cpp" -o "$WORK/cursor_render_test.moc"
g++ -std=c++17 -fPIC -Wall -Wextra -I"$ROOT/src" $QT_CFLAGS \
    "$ROOT/tests/cursor_render_test.cpp" "$ROOT/src/CursorManager.cpp" "$ROOT/src/KithCursors.cpp" \
    "$ROOT/src/IconProvider.cpp" "$WORK/moc_CursorManager.cpp" $QT_LIBS -o "$OUT"
QT_QPA_PLATFORM="${QT_QPA_PLATFORM:-offscreen}" "$OUT"
