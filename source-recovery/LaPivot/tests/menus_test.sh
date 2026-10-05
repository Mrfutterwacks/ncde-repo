#!/bin/bash
# AppMenuModel / GliaSystemMenus tests: scratch XDG fixtures and a private session bus only.
set -euo pipefail

L=$(cd "$(dirname "$0")/.." && pwd)
FIX="$L/tests/menus-fixtures"
BUILD="$L/build"
BIN="$BUILD/menus_test"
BUS_ADDR="$BUILD/menus_test_bus.address"
BUS_LOG="$BUILD/menus_test_bus.log"
RECORD="$BUILD/menus_test_launch.log"
NEW_APP="$FIX/system-data/applications/late-test.desktop"
XBEL="$FIX/data-home/recently-used.xbel"
RECENT_FILE="$FIX/recent.txt"
BUS_PID=

for path in "$BIN" "$BUS_ADDR" "$BUS_LOG" "$RECORD" "$NEW_APP" "$XBEL"; do
    if [[ -e "$path" ]]; then
        printf 'Refusing to overwrite existing test artifact: %s\n' "$path" >&2
        exit 1
    fi
done

cleanup() {
    status=$?
    if [[ -n "$BUS_PID" ]]; then
        kill "$BUS_PID" 2>/dev/null || true
        wait "$BUS_PID" 2>/dev/null || true
    fi
    rm -f "$BIN" "$BUILD"/menus_test_moc_*.cpp "$BUS_ADDR" "$BUS_LOG" "$RECORD" "$NEW_APP" "$XBEL"
    exit "$status"
}
trap cleanup EXIT

chmod +x "$FIX/bin/record-app" "$FIX/bin/xdg-open"
printf '<xbel version="1.0"><bookmark href="file://%s"/></xbel>\n' "$RECENT_FILE" > "$XBEL"

dbus-daemon --session --nofork --print-address=1 > "$BUS_ADDR" 2> "$BUS_LOG" &
BUS_PID=$!
for _ in {1..100}; do
    [[ -s "$BUS_ADDR" ]] && break
    sleep 0.02
done
if [[ ! -s "$BUS_ADDR" ]]; then
    cat "$BUS_LOG" >&2
    exit 1
fi

export DBUS_SESSION_BUS_ADDRESS
IFS= read -r DBUS_SESSION_BUS_ADDRESS < "$BUS_ADDR"
export HOME="$FIX/home"
export XDG_CONFIG_HOME="$HOME/.config"
export XDG_DATA_HOME="$FIX/data-home"
export XDG_DATA_DIRS="$FIX/system-data"
export XDG_CURRENT_DESKTOP=NCDE
export PATH="$FIX/bin:/usr/bin:/bin"
export MENU_TEST_RECORD="$RECORD"
export MENU_TEST_NEW_APP="$NEW_APP"
export MENU_TEST_RECENT_FILE="$RECENT_FILE"

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6DBus)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6DBus)"
/usr/lib/qt6/moc "$L/src/AppMenuModel.h" -o "$BUILD/menus_test_moc_AppMenuModel.cpp"
/usr/lib/qt6/moc "$L/src/GliaSystemMenus.h" -o "$BUILD/menus_test_moc_GliaSystemMenus.cpp"
/usr/lib/qt6/moc "$L/src/AppMenuModel_index.h" -o "$BUILD/menus_test_moc_DesktopIndex.cpp"
g++ -std=c++17 -fPIC -Wall -Wextra -Wno-unused-parameter -Wno-sfinae-incomplete \
    -I"$L/src" $QT_CFLAGS -o "$BIN" \
    "$L/tests/menus_test.cpp" "$L/src/AppMenuModel.cpp" "$L/src/GliaSystemMenus.cpp" \
    "$BUILD/menus_test_moc_AppMenuModel.cpp" "$BUILD/menus_test_moc_GliaSystemMenus.cpp" \
    "$BUILD/menus_test_moc_DesktopIndex.cpp" $QT_LIBS

"$BIN"
