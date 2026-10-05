#!/bin/bash
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"
B="$L/build/wm_model_test"
trap 'rm -f "$B" "$B.moc.cpp" "$B.animpolicy.moc.cpp"' EXIT
QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6Gui Qt6DBus)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6Gui Qt6DBus)"
XCB_CFLAGS="$(pkg-config --cflags xcb xcb-icccm xcb-screensaver xcb-randr)"
XCB_LIBS="$(pkg-config --libs xcb xcb-icccm xcb-screensaver xcb-randr)"
/usr/lib/qt6/moc "$L/src/NCDEWindowManager.h" -o "$B.moc.cpp"
/usr/lib/qt6/moc "$L/src/AnimPolicy.h" -o "$B.animpolicy.moc.cpp"
g++ -std=c++17 -fPIC -Wall -Wextra -I"$L/src" \
    $QT_CFLAGS $XCB_CFLAGS \
    "$L/tests/wm_model_test.cpp" "$L/src/NCDEWindowManager.cpp" \
    "$L/src/GliaTalk.cpp" "$L/src/AnimPolicy.cpp" "$B.moc.cpp" "$B.animpolicy.moc.cpp" \
    -o "$B" $QT_LIBS $XCB_LIBS
QT_QPA_PLATFORM=offscreen "$B"
