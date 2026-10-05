#!/bin/bash
# display_test.sh — Settings_display.cpp (tests/display_test.cpp). xrandr is only QUERIED; changes are recorded.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/t" "$L/tests/display_test.cpp" "$L/src/Settings_display.cpp" "$L/src/Settings_core.cpp" "$L/src/Lelan_config.cpp" "$L/src/Lelan_time.cpp" || exit 1
HOME="$W" "$W/t"
