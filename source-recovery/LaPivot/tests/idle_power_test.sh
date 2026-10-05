#!/bin/bash
# idle_power_test.sh — Settings power/idle/screensaver/lid (tests/idle_power_test.cpp). Nothing real is run:
# commands are recorded, the screensaver is a stand-in script.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/t" "$L/tests/idle_power_test.cpp" "$L/src/Settings_power.cpp" "$L/src/Settings_core.cpp" "$L/src/IdlePolicy.cpp" "$L/src/Lelan_config.cpp" || exit 1
printf '#!/bin/sh\n# stand-in screensaver: lives $SAVER_AFTER s then exits $SAVER_EXIT; without SAVER_AFTER it IS the sleep\n# (exec), so stopping the saver leaves nothing behind\n[ -z "$SAVER_AFTER" ] && exec sleep 3600\nsleep "$SAVER_AFTER"\nexit "${SAVER_EXIT:-0}"\n' > "$W/saver"; chmod +x "$W/saver"
SAVER="$W/saver" HOME="$W" "$W/t"; RC=$?
# the stand-in saver must be gone (a stopped screensaver leaves nothing behind)
if pgrep -f "$W/saver" >/dev/null; then echo "FAIL stand-in saver left running"; RC=1; else echo "PASS nothing left running"; fi
exit $RC
