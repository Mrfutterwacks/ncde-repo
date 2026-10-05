#!/bin/bash
set -euo pipefail

L="$(cd "$(dirname "$0")/.." && pwd)"
W="$L/tests/.notif_test.$$"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/home"
export HOME="$W/home"
export XDG_CONFIG_HOME="$HOME/.config"
export QT_QPA_PLATFORM=offscreen
export TMPDIR="$W"

/usr/lib/qt6/moc "$L/src/NotificationManager.h" -o "$W/moc_NotificationManager.cpp"
/usr/lib/qt6/moc "$L/src/FreedesktopNotificationsAdaptor.h" -o "$W/moc_FreedesktopNotificationsAdaptor.cpp"
/usr/lib/qt6/moc "$L/src/Settings.h" -o "$W/moc_Settings.cpp"
/usr/lib/qt6/moc "$L/tests/notif_test.cpp" -o "$W/notif_test.moc"

SRCS=(
    "$W/moc_NotificationManager.cpp"
    "$W/moc_FreedesktopNotificationsAdaptor.cpp"
    "$W/moc_Settings.cpp"
    "$L/src/NotificationManager.cpp"
    "$L/src/FreedesktopNotificationsAdaptor.cpp"
    "$L/tests/notif_test.cpp"
)

for f in "${SRCS[@]}"; do
    g++ -std=c++17 -fPIC -Wall -Wextra -Wno-sfinae-incomplete \
        -I"$L/src" -I"$W" $(pkg-config --cflags Qt6Core Qt6DBus Qt6Gui Qt6Test) \
        -c "$f" -o "$W/$(basename "$f" .cpp).o"
done

nm --defined-only "$W"/*.o | awk '{print $3}' | sort -u > "$W/defined.txt"
{
    echo ".text"
    echo "ncde_stub_trap: ud2"
    nm --undefined-only "$W"/*.o | awk '$2 ~ /^_ZNK?(5Lelan|8Settings|19NotificationManager|31FreedesktopNotificationsAdaptor)/ {print $2}' \
        | sort -u | grep -vxF -f "$W/defined.txt" \
        | awk '{print ".globl "$1"\n.set "$1", ncde_stub_trap"}'
} > "$W/stubs.s"
as "$W/stubs.s" -o "$W/stubs.o"

g++ -o "$W/test" "$W"/*.o $(pkg-config --libs Qt6Core Qt6DBus Qt6Gui Qt6Test)
"$W/test"
