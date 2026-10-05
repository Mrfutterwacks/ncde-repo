#!/bin/bash
# input_test.sh — Settings_input.cpp (tests/input_test.cpp); scratch HOME, nothing applied to the real devices.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/t" "$L/tests/input_test.cpp" "$L/src/Settings_input.cpp" "$L/src/Settings_core.cpp" "$L/src/Lelan_config.cpp" || exit 1
HOME="$W" "$W/t"
