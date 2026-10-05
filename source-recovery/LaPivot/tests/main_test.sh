#!/bin/bash
set -euo pipefail

L="$(cd "$(dirname "$0")/.." && pwd)"
W="$L/tests/.build-main-test-$$"
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/home"

bash "$L/tests/build_main_test.sh" "$W" "$W/main_test" "$L/tests/main_test.cpp"
(cd "$L" && QT_QPA_PLATFORM=offscreen HOME="$W/home" "$W/main_test")
echo "main_test: PASS (main compiles/links, asset base and context names verified)"
