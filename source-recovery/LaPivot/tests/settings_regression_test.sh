#!/bin/bash
set -euo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"
: "${WORK_DIR:?Set WORK_DIR to a scratch directory inside the project tree}"
W="$WORK_DIR"
mkdir -p "$W/home"
mkdir -p "$W/home/.config/ncde"
rm -f "$W"/*.o "$W"/moc_Lelan.cpp "$W"/moc_lelan_dbus_relay.cpp "$W"/moc_Settings.cpp \
  "$W"/stubs.s "$W"/defined.txt "$W"/settings_regression_test
if ! bash "$L/tests/lelan_test_build.sh" "$W" "$W/settings_regression_test" "$L/tests/settings_regression_test.cpp" \
  "$L/src/Settings_core.cpp" "$L/src/Settings_display.cpp" "$L/src/Settings_fonts.cpp" \
  "$L/src/Settings_input.cpp" "$L/src/Settings_misc.cpp" "$L/src/Settings_power.cpp" \
  "$L/src/Settings_prefs.cpp" "$L/src/Settings_props.cpp" "$L/src/Settings_theme.cpp" \
  "$L/src/IdlePolicy.cpp" "$L/src/Lelan_config.cpp"; then
  for unit in settings_regression_test moc_Lelan moc_lelan_dbus_relay moc_Settings Settings_core Settings_display \
              Settings_fonts Settings_input Settings_misc Settings_power Settings_prefs Settings_props Settings_theme \
              IdlePolicy Lelan_config stubs; do
    [ -f "$W/$unit.o" ] || { echo "FAIL test build stopped before producing $unit.o"; exit 1; }
  done
  QT="$(pkg-config --cflags --libs Qt6Core Qt6DBus Qt6Gui Qt6Qml Qt6Quick Qt6Test)"
  g++ -o "$W/settings_regression_test" "$W"/*.o $QT
fi
HOME="$W/home" XDG_CONFIG_HOME="$W/home/.config" QT_QPA_PLATFORM=offscreen "$W/settings_regression_test"
g++ -std=c++17 -Wall -Wextra -Werror -I"$L/src" "$L/tests/idle_io_scope_test.cpp" -o "$W/idle_io_scope_test"
"$W/idle_io_scope_test"
