#!/bin/bash
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"
W="$L/tests/.lelan-services-run"
trap 'rm -rf "$W"' EXIT
rm -rf "$W"
mkdir -p "$W/bin"
QT="$(pkg-config --cflags --libs Qt6Core Qt6DBus Qt6Gui Qt6Qml Qt6Quick Qt6Network)"
PULSE="$(pkg-config --cflags --libs libpulse)"

cat > "$W/bin/lpstat" <<'SCRIPT'
#!/bin/sh
if [ "$1" = "-d" ]; then
    printf '%s\n' 'system default destination: Safe_Printer'
    exit 0
fi
cat <<'OUTPUT'
printer Safe_Printer is idle. enabled since Thu Oct  1 10:00:00 2026
  Description: Test printer
  Location: Lab
printer Another-Printer is printing job 1. enabled since Thu Oct  1 10:00:00 2026
  Description: Second printer
  Location: Office
OUTPUT
SCRIPT
cat > "$W/bin/lpadmin" <<'SCRIPT'
#!/bin/sh
printf '%s\n' "$*" >> "$NCDE_PRINTER_RECORD"
SCRIPT
chmod +x "$W/bin/lpstat" "$W/bin/lpadmin"

/usr/lib/qt6/moc "$L/src/Lelan.h" -o "$W/moc_Lelan.cpp"
/usr/lib/qt6/moc "$L/src/lelan_dbus_relay.h" -o "$W/moc_lelan_dbus_relay.cpp"
/usr/lib/qt6/moc "$L/src/AnimPolicy.h" -o "$W/moc_AnimPolicy.cpp"
/usr/lib/qt6/moc "$L/src/ZenGovernor.h" -o "$W/moc_ZenGovernor.cpp"
/usr/lib/qt6/moc "$L/src/Lelan_bluetooth.cpp" -o "$W/Lelan_bluetooth.moc"
/usr/lib/qt6/moc "$L/tests/lelan_services_test.cpp" -o "$W/lelan_services_test.moc"
FLAGS=(-std=c++17 -fPIC -Wall -Wextra -Wreorder -Wno-sfinae-incomplete -Wno-deprecated-declarations
       -I"$L/src" -I"$W" $(pkg-config --cflags Qt6Core Qt6DBus Qt6Gui Qt6Qml Qt6Quick Qt6Network libpulse))
SOURCES=(
    "$W/moc_Lelan.cpp" "$W/moc_lelan_dbus_relay.cpp" "$W/moc_AnimPolicy.cpp" "$W/moc_ZenGovernor.cpp"
    "$L/tests/lelan_services_test.cpp"
    "$L/src/Lelan_core.cpp" "$L/src/Lelan_kickass.cpp" "$L/src/Lelan_packages.cpp"
    "$L/src/Lelan_users.cpp" "$L/src/Lelan_printers.cpp" "$L/src/Lelan_tray.cpp"
    "$L/src/Lelan_devices.cpp" "$L/src/Lelan_audio.cpp" "$L/src/Lelan_bluetooth.cpp"
    "$L/src/Lelan_config.cpp" "$L/src/Lelan_media.cpp" "$L/src/Lelan_network.cpp"
    "$L/src/Lelan_portal.cpp" "$L/src/Lelan_power.cpp" "$L/src/Lelan_session.cpp"
    "$L/src/Lelan_storage.cpp" "$L/src/Lelan_time.cpp" "$L/src/Lelan_zen.cpp"
    "$L/src/AnimPolicy.cpp" "$L/src/ZenGovernor.cpp" "$L/src/IdleIoScope.cpp"
)
OBJECTS=()
for source in "${SOURCES[@]}"; do
    object="$W/$(basename "${source%.cpp}").o"
    g++ "${FLAGS[@]}" -c "$source" -o "$object"
    OBJECTS+=("$object")
done
g++ -o "$W/lelan_services_test" "${OBJECTS[@]}" $QT $PULSE

export PATH="$W/bin:$PATH"
export NCDE_PRINTER_RECORD="$W/lpadmin-calls.txt"
export PULSE_SERVER="unix:$W/no-pulse-server.sock"
dbus-run-session -- "$W/lelan_services_test"
