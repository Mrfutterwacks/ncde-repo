#!/bin/bash
# step13-dd-stick.sh — write the verified 2026-07-11 ISO to the install stick (/dev/sdb)
# and PROVE the write by reading it back and comparing byte-for-byte.
# BOTH GATES PASSED before this exists (operator reboot 2026-07-11 + VM install "works").
# Run as root:  sudo bash step13-dd-stick.sh
set -e
ISO=/home/stephen/ncde-ISO/out/ncde-poseidon-20260711.iso
DEV=/dev/sdb

[ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0"; exit 1; }
[ -b "$DEV" ] || { echo "ABORT: $DEV not present"; exit 1; }
mount | grep -q "^$DEV" && { echo "ABORT: $DEV is mounted — unmount first"; exit 1; }
SIZE=$(stat -c%s "$ISO")
echo "== writing $(numfmt --to=iec $SIZE) to $DEV ($(date '+%T')) =="
dd if="$ISO" of="$DEV" bs=4M status=progress conv=fsync
sync
echo "== read-back verify (byte-for-byte, ~5 min) =="
if cmp -n "$SIZE" "$ISO" "$DEV"; then
    echo "== VERIFIED: stick matches the ISO exactly ($(date '+%T')) =="
else
    echo "== MISMATCH — stick is NOT good, do not use it =="; exit 1
fi
