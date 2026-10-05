#!/bin/bash
# media_live_test.sh — Lelan_media.cpp vs two fake MPRIS players (fake_mpris.py) on the session bus. No audio.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"
for n in ncdetest chromium.instance4242; do        # a leftover fake would answer instead of ours
  busctl --user status "org.mpris.MediaPlayer2.$n" >/dev/null 2>&1 && { echo "FAIL org.mpris.MediaPlayer2.$n already on the bus (leftover fake?)"; exit 1; }
done
python3 "$L/tests/fake_mpris.py" ncdetest chromium.instance4242 > "$W/fake.txt" 2>&1 &
FAKE=$!; trap 'kill $FAKE 2>/dev/null; rm -rf "$W"' EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/media_test" "$L/tests/media_live_test.cpp" "$L/src/Lelan_media.cpp" || exit 1
for i in $(seq 50); do grep -q READY "$W/fake.txt" && break; sleep 0.2; done
grep -q READY "$W/fake.txt" || { echo "FAIL fake players did not start"; cat "$W/fake.txt"; exit 1; }
"$W/media_test"
