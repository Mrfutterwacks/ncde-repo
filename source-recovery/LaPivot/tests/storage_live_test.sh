#!/bin/bash
# storage_live_test.sh — Lelan_storage.cpp on the real UDisks2. The operator's sticks are only LISTED
# (read-only). Mount / busy-unmount / unlock run on throwaway loop images this script creates; a Format
# happens only after checking the loop device is backed by this script's own image file.
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; FAILS=0
pass() { echo "PASS $*"; }; fail() { echo "FAIL $*"; FAILS=$((FAILS+1)); }
LOOPS=()
cleanup() {
  [ -n "${HOLD:-}" ] && kill "$HOLD" 2>/dev/null   # never "kill 0": that is this script's whole process group
  for d in "${LOOPS[@]}"; do
    for c in $(lsblk -nro NAME "/dev/$d" 2>/dev/null | tail -n +2); do udisksctl unmount -b "/dev/mapper/$c" >/dev/null 2>&1; udisksctl unmount -b "/dev/$c" >/dev/null 2>&1; done
    udisksctl unmount -b "/dev/$d" >/dev/null 2>&1; udisksctl lock -b "/dev/$d" >/dev/null 2>&1; udisksctl loop-delete -b "/dev/$d" >/dev/null 2>&1
  done
  rm -rf "$W"
}
trap cleanup EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/st" "$L/tests/storage_live_test.cpp" "$L/src/Lelan_storage.cpp" || exit 1
T() { "$W/st"; }
obj() { echo "/org/freedesktop/UDisks2/block_devices/$1"; }

echo "== the operator's sticks, listed only"
LIST=$(ST_MODE=list T | sed -n 's/^LIST //p')
python3 - "$LIST" <<'PY' || FAILS=$((FAILS+1))
import json, sys, subprocess
vols = json.loads(sys.argv[1]); ok = True
labels = {v["label"]: v for v in vols}
want = {l.split()[0]: l.split()[1] for l in subprocess.run(["lsblk","-nro","LABEL,MOUNTPOINT","-o","LABEL,MOUNTPOINT"],capture_output=True,text=True).stdout.splitlines() if len(l.split())==2}
for lab in ["NCDE-BACKUP", "NCDE_POSEIDON"]:
    v = labels.get(lab)
    good = bool(v) and v["mounted"] and v["canEject"] and v["mountPoint"].endswith(lab)
    print(("PASS " if good else "FAIL ") + f"{lab} listed, mounted, ejectable ({v and v['mountPoint']})"); ok &= good
hidden = "ARCHISO_EFI" not in labels
print(("PASS " if hidden else "FAIL ") + "ARCHISO_EFI (UDisks HintIgnore) not listed (S5)"); ok &= hidden
sys.exit(0 if ok else 1)
PY

echo "== throwaway loop images"
truncate -s 48M "$W/plain.img"; mkfs.vfat -n NCDETEST "$W/plain.img" >/dev/null
P=$(udisksctl loop-setup -f "$W/plain.img" --no-user-interaction | grep -o 'loop[0-9]*'); LOOPS+=("$P")
[ "$(cat /sys/block/$P/loop/backing_file)" = "$W/plain.img" ] || { echo "FAIL loop device is not ours — stopping"; exit 1; }
udisksctl unmount -b "/dev/$P" >/dev/null 2>&1   # auto-mounters may have grabbed it
sleep 1
ST_MODE=mount ST_PATH=$(obj $P) T | grep -E "FAILED" ; MP=$(findmnt -nro TARGET "/dev/$P")
[ -n "$MP" ] && pass "mountVolume mounted it at $MP" || fail "not mounted"
( cd "$MP" && exec sleep 60 ) & HOLD=$!; sleep 0.5
OUT=$(ST_MODE=unmount ST_PATH=$(obj $P) T)
echo "$OUT" | grep -q "FAILED.*still using" && pass "busy unmount reported: $(echo "$OUT" | sed -n 's/^FAILED [^|]*| //p') (S1)" || fail "busy unmount not reported: $(echo "$OUT" | grep FAILED)"
[ -n "$(findmnt -nro TARGET "/dev/$P")" ] && pass "still mounted after the refused unmount (UI must not say otherwise)" || fail "unmounted?"
kill $HOLD; wait $HOLD 2>/dev/null; HOLD=
OUT=$(ST_MODE=unmount ST_PATH=$(obj $P) T)
echo "$OUT" | grep -q FAILED && fail "unmount failed: $OUT" || { [ -z "$(findmnt -nro TARGET "/dev/$P")" ] && pass "unmount once nothing uses it" || fail "still mounted"; }

truncate -s 48M "$W/crypt.img"
C=$(udisksctl loop-setup -f "$W/crypt.img" --no-user-interaction | grep -o 'loop[0-9]*'); LOOPS+=("$C")
[ "$(cat /sys/block/$C/loop/backing_file)" = "$W/crypt.img" ] || { echo "FAIL loop device is not ours — stopping"; exit 1; }
busctl call org.freedesktop.UDisks2 $(obj $C) org.freedesktop.UDisks2.Block Format 'sa{sv}' vfat 3 \
  encrypt.passphrase s "ncde-test-pass" encrypt.type s luks2 label s NCDECRYPT --timeout=120 >/dev/null || { echo "FAIL format"; exit 1; }
udisksctl lock -b "/dev/$C" >/dev/null 2>&1; sleep 1
OUT=$(ST_MODE=unlock ST_PATH=$(obj $C) ST_PASS=wrong-pass ACT_MS=12000 T)
echo "$OUT" | grep -q "FAILED" && pass "wrong passphrase reported: $(echo "$OUT" | sed -n 's/^FAILED [^|]*| //p')" || fail "wrong passphrase not reported"
OUT=$(ST_MODE=unlock ST_PATH=$(obj $C) ST_PASS=ncde-test-pass ACT_MS=12000 T)
CLR=$(lsblk -nro NAME,TYPE "/dev/$C" | awk '$2=="crypt"{print $1}')
MPC=$([ -n "$CLR" ] && findmnt -nro TARGET "/dev/mapper/$CLR")
[ -n "$MPC" ] && pass "right passphrase: unlocked and mounted at $MPC (S6)" || fail "not unlocked+mounted: $(echo "$OUT" | grep FAILED)"

echo "== burst: GetManagedObjects per UDisks change (S3)"
timeout 25 dbus-monitor --system "type='method_call',member='GetManagedObjects',destination='org.freedesktop.UDisks2'" \
  "type='signal',sender='org.freedesktop.UDisks2'" > "$W/mon.txt" 2>/dev/null &
g++ -std=c++17 -fPIC -shared -o "$W/calllog.so" "$L/tools/dbus_call_log.cpp" $(pkg-config --cflags --libs Qt6DBus) -ldl 2>/dev/null
DBUS_CALL_LOG="$W/calls.txt" LD_PRELOAD="$W/calllog.so" ST_MODE=watch WATCH_MS=14000 T > "$W/watch.txt" &
sleep 3
udisksctl mount -b "/dev/$P" >/dev/null; sleep 1; udisksctl unmount -b "/dev/$P" >/dev/null; sleep 1
udisksctl mount -b "/dev/$P" >/dev/null; sleep 1; udisksctl unmount -b "/dev/$P" >/dev/null
wait
# a normal user cannot eavesdrop other processes' method calls on the system bus, so this process's own
# calls are logged by tools/dbus_call_log.cpp (LD_PRELOAD); UDisks' signals come from dbus-monitor
SIG=$(grep -c "^signal" "$W/mon.txt"); MINE=$(grep -c "^GetManagedObjects " "$W/calls.txt" 2>/dev/null || echo 0)
echo "INFO UDisks signals during 4 mount/unmounts: $SIG; this Lelan's GetManagedObjects calls: $MINE (1 = start-up read)"
[ "$MINE" -ge 1 ] || fail "trace captured no GetManagedObjects at all — the count would be meaningless"
[ "$MINE" -ge 1 ] && [ "$MINE" -le 5 ] && pass "coalesced: $MINE reads for $SIG UDisks signals (S3)" || fail "$MINE reads for $SIG signals"
echo "RESULT $([ $FAILS = 0 ] && echo PASS || echo "FAIL ($FAILS)")"
