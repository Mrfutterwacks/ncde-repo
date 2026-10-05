#!/bin/bash
# step11-register-packages.sh — ISO rebuild PHASE 2: register the adopted packages in the
# IMAGE's pacman DB so every fresh install is born properly package-managed (the permanent
# cure for "exists in filesystem / can't update" — no field patching ever again for this class).
#
# What it does, in order:
#   1. moves the parked keyring (staging/image-gnupg-DO-NOT-SHIP) back into the image
#      (pacman needs it to verify signatures; it is moved OUT again at the end — installs
#      must generate their own master key)
#   2. arch-chroot into the image (arch-chroot mounts /proc /sys /dev /run and binds the
#      host resolv.conf itself — verified against /usr/bin/arch-chroot source)
#   3. refreshes sync DBs + updates archlinux-keyring first (so current package sigs verify)
#   4. installs/registers: the 387 adopted packages (/var/lib/ncde-adopt/candidates.pkglist)
#      + the 6 live-proven fix-pack packages missing from the image DB:
#      gst-libav scx-tools scx-scheds iio-sensor-proxy bluez bluez-utils
#      --needed --overwrite '*' : files already in the image are adopted, missing ones installed
#   5. moves the downloaded package cache ASIDE to staging (never ships, never deleted)
#   6. moves the keyring back OUT to staging
#   7. prints a verification summary (registered count must be 393/393)
#
# Run as root:  sudo bash step11-register-packages.sh
set -u
A=/home/stephen/ncde-ISO/airootfs
G=/home/stephen/ncde-ISO/staging/image-gnupg-DO-NOT-SHIP
LIST=/var/lib/ncde-adopt/candidates.pkglist
EXTRA="gst-libav scx-tools scx-scheds iio-sensor-proxy bluez bluez-utils"
LOG=/var/log/ncde-iso-phase2.log
CACHE_ASIDE=/home/stephen/ncde-ISO/staging/phase2-pkg-cache

[ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0"; exit 1; }
[ -d "$A/usr/share/ncde" ]  || { echo "image tree $A missing"; exit 1; }
[ -f "$LIST" ]              || { echo "candidates list $LIST missing"; exit 1; }
N=$(wc -l < "$LIST")
say(){ echo "$*" | tee -a "$LOG"; }
: > "$LOG"
say "== ISO Phase 2: register packages in image DB ($(date '+%F %T')) =="
say "  candidates: $N   extras: $EXTRA"

# keyring must exist exactly one place
if [ -d "$A/etc/pacman.d/gnupg" ]; then
    say "  keyring already in image (unexpected but usable)"
elif [ -d "$G" ]; then
    mv "$G" "$A/etc/pacman.d/gnupg" && say "  keyring restored into image"
else
    say "FATAL: no keyring in image or staging"; exit 1
fi
# no matter how we exit, park the keyring back out (it must NEVER ship)
park_keyring(){
    if [ -d "$A/etc/pacman.d/gnupg" ]; then
        mv "$A/etc/pacman.d/gnupg" "$G" && say "  keyring parked back out to staging"
    fi
}

# pacman's CheckSpace needs the chroot root to BE a mountpoint (session-85 lesson:
# "could not determine cachedir mount point" in a plain-dir chroot) — bind it onto itself
BOUND=0
if ! mountpoint -q "$A"; then
    mount --bind "$A" "$A" && BOUND=1 && say "  bind-mounted image onto itself (CheckSpace fix)"
fi
cleanup(){
    [ "$BOUND" = 1 ] && { umount "$A" 2>/dev/null || umount -l "$A"; say "  image self-bind unmounted"; }
    park_keyring
}
trap cleanup EXIT

say "[1/4] sync DBs + keyring package first"
arch-chroot "$A" pacman -Sy --needed --noconfirm archlinux-keyring 2>&1 | tee -a "$LOG" | tail -5
rc=${PIPESTATUS[0]}
[ "$rc" = 0 ] || { say "FATAL: keyring refresh failed rc=$rc — see $LOG"; exit 1; }

say "[2/4] install/register $N candidates + extras (pacman will show ONE summary — approve it there)"
# shellcheck disable=SC2046
arch-chroot "$A" pacman -S --needed --overwrite '*' $(tr '\n' ' ' < "$LIST") $EXTRA 2>&1 | tee -a "$LOG" | tail -15
rc=${PIPESTATUS[0]}
[ "$rc" = 0 ] || { say "FATAL: install failed rc=$rc — see $LOG"; exit 1; }

say "[3/4] move package cache aside (never ships)"
mkdir -p "$CACHE_ASIDE"
find "$A/var/cache/pacman/pkg" -maxdepth 1 \( -name '*.pkg.tar*' -o -name 'download-*' -o -name '*.part' \) -exec mv -t "$CACHE_ASIDE" {} + 2>/dev/null
say "  cache files now aside: $(ls "$CACHE_ASIDE" | wc -l); left in image: $(ls "$A/var/cache/pacman/pkg" 2>/dev/null | wc -l)"

say "[4/4] verify registration"
OK=0; MISS=0; MISSING=""
while IFS= read -r p; do
    if pacman -Q --root "$A" --dbpath "$A/var/lib/pacman" "$p" >/dev/null 2>&1; then OK=$((OK+1)); else MISS=$((MISS+1)); MISSING="$MISSING $p"; fi
done < <(cat "$LIST"; printf '%s\n' $EXTRA)
say "  registered: $OK / $((N+6))"
[ -n "$MISSING" ] && say "  STILL MISSING:$MISSING"

cleanup; trap - EXIT
say ""
say "== Phase 2 done. Keyring OUT of image: $([ -d "$A/etc/pacman.d/gnupg" ] && echo 'NO - STILL IN IMAGE, DO NOT BUILD' || echo YES). =="
say "== Next: Phase 3 mksquashfs. Log: $LOG =="
