#!/bin/bash
# storage_automount_test.sh — S7 auto-mount rules (tests/storage_automount_test.cpp), plus one real mount:
# a throwaway loop image (never the operator's sticks) is presented to Lelan as a freshly inserted stick
# and must end up mounted by UDisks. Cleanup is verified.
MP=$(cd "$(dirname "$(readlink -f "$0")")/../../.." && pwd)   # my-project/, wherever the USB is mounted
set -uo pipefail
L="$(cd "$(dirname "$0")/.." && pwd)"; W="$(mktemp -d)"; LOOP=""
cleanup() {
  if [ -n "$LOOP" ]; then
    udisksctl unmount -b "/dev/$LOOP" >/dev/null 2>&1; udisksctl loop-delete -b "/dev/$LOOP" >/dev/null 2>&1
  fi
  rm -rf "$W"
}
trap cleanup EXIT
bash "$L/tests/lelan_test_build.sh" "$W" "$W/am" "$L/tests/storage_automount_test.cpp" "$L/src/Lelan_storage.cpp" || exit 1
truncate -s 32M "$W/am.img"; mkfs.vfat -n NCDEAUTO "$W/am.img" >/dev/null
LOOP=$(udisksctl loop-setup -f "$W/am.img" --no-user-interaction | grep -o 'loop[0-9]*')
[ "$(cat /sys/block/$LOOP/loop/backing_file)" = "$W/am.img" ] || { echo "FAIL loop device is not ours — stopping"; exit 1; }
udisksctl unmount -b "/dev/$LOOP" >/dev/null 2>&1; sleep 1
[ -z "$(findmnt -nro TARGET "/dev/$LOOP")" ] || { echo "FAIL could not start unmounted"; exit 1; }
AM_MOUNTED_BLOCK=$(basename "$(findmnt -nro SOURCE --target "$MP")") AM_REAL_FS="/org/freedesktop/UDisks2/block_devices/$LOOP" "$W/am"; RC=$?
MP=$(findmnt -nro TARGET "/dev/$LOOP")
if [ -n "$MP" ]; then echo "PASS real image mounted by Lelan at $MP"; else echo "FAIL real image not mounted"; RC=1; fi
L0="$LOOP"; cleanup; LOOP=""
if [ -e "/sys/block/$L0/loop/backing_file" ] || findmnt -rn | grep -q NCDEAUTO; then echo "FAIL leftovers"; RC=1; else echo "PASS cleanup: no loop device or mount left"; fi
echo "RESULT $([ $RC = 0 ] && echo PASS || echo FAIL)"
exit $RC
