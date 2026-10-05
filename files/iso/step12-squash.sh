#!/bin/bash
# step12-squash.sh — ISO rebuild PHASE 3 (the ONLY remaining root step).
# 1. pre-flight: refuses to build if the keyring is in the image, the pacman cache
#    isn't empty, or the Phase-2 self-bind is still mounted
# 2. ships both fix packs into the image's /usr/local/share/ncde-fix/ (punchlist §0.19
#    "NEXT ISO REPACK MUST") with md5 verification
# 3. asides the old squashfs, builds the new one (zstd-19, 30-60 min), sha512 sidecar,
#    chowns both to stephen so the agent can author the ISO UNPRIVILEGED afterwards
# Run as root, then WALK AWAY:  sudo bash step12-squash.sh
set -e
A=/home/stephen/ncde-ISO/airootfs
X=/home/stephen/ncde-ISO/extract/arch/x86_64
F=/home/stephen/my-project/files
LOG=/var/log/ncde-iso-phase3.log
exec > >(tee "$LOG") 2>&1

[ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0"; exit 1; }

echo "== ISO Phase 3: pre-flight ($(date '+%F %T')) =="
[ -d "$A/etc/pacman.d/gnupg" ] && { echo "ABORT: keyring still in image — must never ship"; exit 1; }
mountpoint -q "$A" && { echo "ABORT: image still bind-mounted from Phase 2 — umount first"; exit 1; }
LEFT=$(find "$A/var/cache/pacman/pkg" -maxdepth 1 -name '*.pkg.tar*' 2>/dev/null | wc -l)
[ "$LEFT" = 0 ] || { echo "ABORT: $LEFT package files still in image cache"; exit 1; }
echo "  pre-flight OK (no keyring, no cache, not mounted)"

echo "== ship both fix packs in the image fix-kit =="
install -m0755 -o root -g root "$F/ncde-fix-pack-20260709.sh" "$A/usr/local/share/ncde-fix/ncde-fix-pack-20260709.sh"
install -m0755 -o root -g root "$F/ncde-fix-pack-20260710.sh" "$A/usr/local/share/ncde-fix/ncde-fix-pack-20260710.sh"
for p in ncde-fix-pack-20260709.sh ncde-fix-pack-20260710.sh; do
    a=$(md5sum "$F/$p" | cut -d' ' -f1); b=$(md5sum "$A/usr/local/share/ncde-fix/$p" | cut -d' ' -f1)
    [ "$a" = "$b" ] && echo "  OK $p" || { echo "ABORT: md5 mismatch $p"; exit 1; }
done

echo "== mksquashfs zstd-19 (30-60 min — safe to leave) =="
mv -- "$X/airootfs.sfs" "$X/airootfs.sfs.preP2-aside"
mksquashfs "$A" "$X/airootfs.sfs" -comp zstd -Xcompression-level 19 -noappend
cd "$X" && sha512sum airootfs.sfs > airootfs.sha512 && cat airootfs.sha512
chown stephen:stephen "$X/airootfs.sfs" "$X/airootfs.sha512"
ls -lah "$X/airootfs.sfs"
echo "== Phase 3 complete ($(date '+%F %T')) — the agent authors + verifies the ISO next (no sudo needed) =="
