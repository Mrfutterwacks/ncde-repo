#!/bin/bash
# SniWatcher test on an isolated session bus with fake watcher/item services only.
set -euo pipefail

L=$(cd "$(dirname "$0")/.." && pwd)
BUILD="$L/build"
BIN="$BUILD/tray_test"
BUS_ADDR="$BUILD/tray_test_bus.address"
BUS_LOG="$BUILD/tray_test_bus.log"
BUS_PID=

for path in "$BIN" "$BUS_ADDR" "$BUS_LOG" "$BUILD/tray_test.moc"; do
    if [[ -e "$path" ]]; then
        printf 'Refusing to overwrite existing test artifact: %s\n' "$path" >&2
        exit 1
    fi
done

cleanup() {
    status=$?
    trap - EXIT
    if [[ -n "$BUS_PID" ]]; then
        kill "$BUS_PID" 2>/dev/null || true
        wait "$BUS_PID" 2>/dev/null || true
    fi
    rm -f "$BIN" "$BUILD"/tray_test_moc_*.cpp "$BUILD/tray_test.moc" "$BUS_ADDR" "$BUS_LOG"
    exit "$status"
}
trap cleanup EXIT

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
IFS= read -r DBUS_SESSION_BUS_ADDRESS < "$BUS_ADDR"
export DBUS_SESSION_BUS_ADDRESS

QT_CFLAGS="$(pkg-config --cflags Qt6Core Qt6DBus)"
QT_LIBS="$(pkg-config --libs Qt6Core Qt6DBus)"
/usr/lib/qt6/moc "$L/tests/tray_test.cpp" -o "$BUILD/tray_test.moc"
/usr/lib/qt6/moc "$L/src/SniWatcher.h" -o "$BUILD/tray_test_moc_SniWatcher.cpp"
/usr/lib/qt6/moc "$L/src/StatusNotifierWatcherAdaptor.h" -o "$BUILD/tray_test_moc_StatusNotifierWatcherAdaptor.cpp"
/usr/lib/qt6/moc "$L/src/FdoStatusNotifierWatcherAdaptor.h" -o "$BUILD/tray_test_moc_FdoStatusNotifierWatcherAdaptor.cpp"
g++ -std=c++17 -fPIC -Wall -Wextra -Wno-unused-parameter -Wno-sfinae-incomplete \
    -I"$L/src" -I"$BUILD" $QT_CFLAGS -o "$BIN" \
    "$L/tests/tray_test.cpp" "$L/src/SniWatcher.cpp" \
    "$L/src/StatusNotifierWatcherAdaptor.cpp" "$L/src/FdoStatusNotifierWatcherAdaptor.cpp" \
    "$BUILD/tray_test_moc_SniWatcher.cpp" \
    "$BUILD/tray_test_moc_StatusNotifierWatcherAdaptor.cpp" \
    "$BUILD/tray_test_moc_FdoStatusNotifierWatcherAdaptor.cpp" $QT_LIBS

"$BIN"
