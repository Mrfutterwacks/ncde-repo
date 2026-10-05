#!/bin/bash
# >>> 2026-10-01: stages squash/boot/iso/vmtest are superseded by step21-rootless-refresh.sh (no root).
# step20-refresh-poseidon.sh — bring the NCDE_POSEIDON install stick (July 21 image) up to the
# current NCDE. Follows the documented, proven method (docs/MEMORY.md "cleanest is -boot_image any
# replay -update …airootfs.sfs against a WORKING prior ISO"; ISO-BUILD-PLAN §0a/§6/§10.3 + Gates
# 2.5/2.6; NCDE-BUILD-COMMANDS STEP 4 traps). Replaces steps 10-13, whose ~/ncde-ISO tree was
# lost in the 2026-09-29 reinstall.
#
# One stage at a time, in order; each checks the one before it. Operator runs every sudo stage.
#   sudo bash step20-refresh-poseidon.sh tools     # arch-chroot, xorriso, qemu + OVMF on this machine
#   sudo bash step20-refresh-poseidon.sh backup    # whole stick (ISO + its EFI partition) -> ~/ncde-ISO
#   sudo bash step20-refresh-poseidon.sh unpack    # system image -> ~/ncde-ISO/airootfs
#   sudo bash step20-refresh-poseidon.sh upgrade   # EVERY package -> current, kernel included (initramfs rebuilt)
#   sudo bash step20-refresh-poseidon.sh ncde      # current NCDE into image + home/live + regen caches (Gate 2.5)
#        bash step20-refresh-poseidon.sh test      # (no sudo) Gate 2.6: start the shell FROM THE IMAGE, screenshot
#   sudo bash step20-refresh-poseidon.sh squash    # §10.3 excludes, zstd-19, no -all-root (30-60 min)
#   sudo bash step20-refresh-poseidon.sh boot      # new EFI partition image carrying the new kernel + initramfs
#   sudo bash step20-refresh-poseidon.sh iso       # session-85 recipe from the stick's own boot records; verify
#        bash step20-refresh-poseidon.sh vmtest    # (no sudo) VM gate: boot, INSTALL, reboot, LOG IN
#   sudo bash step20-refresh-poseidon.sh write     # only after the VM install logged in: dd + read-back
#
# NCDE content = the canonical tree (my-project/files/full-patch-20260711/src — publish.sh --check
# proves it identical to the live system) + the live palette-patched LaPivot + live ncde-update tooling.
# Nothing is deleted; anything replaced is kept aside.
set -euo pipefail
W=/home/stephen/ncde-ISO
A=$W/airootfs
ORIG=$W/poseidon-20260721-stick.img      # whole-stick image: ISO + appended EFI partition
NEW=$W/out/poseidon-$(date +%Y%m%d).iso
# write/vmtest after midnight: use the newest ISO built (step21 names it the same way)
case "${1:-}" in write|vmtest) [ -f "$NEW" ] || NEW="$(ls -t "$W"/out/poseidon-*.iso 2>/dev/null | head -1)" ;; esac
SFS=$W/airootfs.sfs
HERE="$(cd "$(dirname "$0")" && pwd)"
STAGE_SRC="$(cd "$HERE/../full-patch-20260711/src" && pwd)"
LOG=$W/step20.log
mkdir -p "$W/out" 2>/dev/null || true
# ~/ncde-ISO and its log stay stephen's, so the no-sudo stages (test, vmtest) can write there
if [ "$(id -u)" = 0 ]; then touch "$LOG"; chown stephen:stephen "$W" "$W/out" "$LOG"; fi
say(){ echo "[$(date +%T)] $*" | tee -a "$LOG" || true; }
need_root(){ [ "$(id -u)" = 0 ] || { echo "Run as root: sudo bash $0 $1"; exit 1; }; }
stick_disk(){ local p k; p="$(readlink -f /dev/disk/by-label/NCDE_POSEIDON)"
  k="$(lsblk -no PKNAME "$p" 2>/dev/null | head -1)"; [ -n "$k" ] && echo "/dev/$k" || echo "$p"; }

# Background QoS (2026-09-30): a rebuild is App-Nap-class work. Terminals launched from LaPivot
# used to inherit its SCHED_FIFO 1, so mksquashfs/pacman ran real-time on every core and froze the
# desktop. Heavy stages re-run themselves as ordinary, lowest-priority work: SCHED_OTHER, nice 19,
# best-effort I/O at the lowest level. The shell and its animations always win the CPU.
case "${1:-}" in upgrade|drivers|ncde|squash|boot|iso)
  if [ -z "${NCDE_BACKGROUND:-}" ]; then
    export NCDE_BACKGROUND=1
    exec chrt --other 0 nice -n 19 ionice -c 2 -n 7 bash "$0" "$@"
  fi ;;
esac
case "${1:-}" in
tools) need_root tools
  # install from the already-synced core/extra databases with the [ncde] repo left out: its database
  # is missing on this machine, and syncing it would pull the NCDE package back onto the build host
  awk '/^\[ncde\]/{skip=1; next} /^\[/{skip=0} !skip' /etc/pacman.conf > "$W/pacman-no-ncde.conf"
  pacman --config "$W/pacman-no-ncde.conf" -S --needed --noconfirm \
    arch-install-scripts libisoburn squashfs-tools qemu-desktop edk2-ovmf xorg-server-xvfb mtools dosfstools
  which arch-chroot xorriso mksquashfs qemu-system-x86_64 | tee -a "$LOG" ;;

backup) need_root backup
  D="$(stick_disk)"; b="$(basename "$D")"; [ -b "$D" ] || { say "stick not found"; exit 1; }
  # end of the LAST partition (the appended ESP) — the stick boots via disk MBR + ESP (session 85)
  END=0; for p in /sys/block/$b/$b*; do e=$(( $(cat $p/start) + $(cat $p/size) )); [ $e -gt $END ] && END=$e; done
  BYTES=$((END * 512)); say "stick $D: image ends at sector $END ($BYTES bytes)"
  [ -f "$ORIG" ] && { say "backup already exists: $ORIG"; exit 0; }
  dd if="$D" of="$ORIG.part" bs=4M iflag=count_bytes count="$BYTES" status=progress
  cmp -n "$BYTES" "$ORIG.part" "$D" && mv "$ORIG.part" "$ORIG" && say "VERIFIED backup: $ORIG"
  xorriso -indev "$ORIG" -pvd_info -report_system_area plain 2>&1 | tee "$W/orig-report.txt" | grep -E 'Volume Id|Modif|Creation|partition' | tee -a "$LOG"
  chown stephen:stephen "$ORIG" "$W/orig-report.txt" ;;

unpack) need_root unpack
  [ -f "$ORIG" ] || { say "run backup first"; exit 1; }
  [ -d "$A" ] && { say "$A already exists — leaving it"; exit 0; }
  M=$W/orig-mnt; mkdir -p "$M"; mount -o loop,ro "$ORIG" "$M"
  unsquashfs -d "$A" "$M/arch/x86_64/airootfs.sfs"         # as root: ownership preserved (§0a)
  umount "$M"; say "unpacked: $(du -sh "$A" | cut -f1); home/live owner: $(stat -c %u:%g "$A/home/live" 2>/dev/null)" ;;

upgrade) need_root upgrade
  [ -d "$A/usr/share/ncde" ] || { say "run unpack first"; exit 1; }
  KEEP=$W/staging; mkdir -p "$KEEP/pkg-cache"
  mountpoint -q "$A" || mount --bind "$A" "$A"            # pacman CheckSpace needs a mountpoint (session 85)
  trap 'umount "$A" 2>/dev/null || umount -l "$A"' EXIT
  if [ ! -d "$A/etc/pacman.d/gnupg" ]; then
    arch-chroot "$A" pacman-key --init
    arch-chroot "$A" pacman-key --populate archlinux
  fi
  arch-chroot "$A" pacman -Sy --needed --noconfirm archlinux-keyring
  # everything, kernel included — linux-zen's hook rebuilds /boot/initramfs-linux-zen.img with the
  # image's archiso hooks (etc/mkinitcpio.conf.d/archiso.conf); the boot stage puts both on the stick
  # unowned June leftovers of an older imagemagick block its upgrade ("exists in filesystem")
  arch-chroot "$A" pacman -Su --noconfirm --overwrite '/usr/lib/libMagickCore-7.Q16HDRI.so.10*' \
    --overwrite '/usr/lib/libMagickWand-7.Q16HDRI.so.10*'
  KV="$(ls "$A/usr/lib/modules" | sort -V | tail -1)"
  say "kernel in image: $KV; /boot: $(ls -l --time-style=+%F\ %H:%M "$A/boot" | awk 'NR>1{print $6,$7,$8}' | tr '\n' ' ')"
  # packages the live NCDE machine has that the July image lacks (ncde/ncde-qpa come from the NCDE repo later)
  arch-chroot "$A" pacman -S --needed --noconfirm gexiv2-common github-cli hdf5 kitty libaec libmatio \
    libtorrent-rasterbar libtraceevent libtracefs linux-firmware-amd linux-firmware-ti mailcap pdfio thunar
  IQ="$(arch-chroot "$A" pacman -Q qt6-base | cut -d' ' -f2)"; LQ="$(pacman -Q qt6-base | cut -d' ' -f2)"
  say "Qt: image $IQ, live $LQ $([ "$IQ" = "$LQ" ] && echo MATCH || echo 'MISMATCH — NCDE Qt plugins are built for live')"
  say "image now: $(arch-chroot "$A" pacman -Q qt6-base qt6-declarative glibc linux-zen | tr '\n' ' ')"
  # the keyring must NEVER ship — installs generate their own master key (session 85)
  mv "$A/etc/pacman.d/gnupg" "$KEEP/image-gnupg-DO-NOT-SHIP.$(date +%H%M%S)"
  find "$A/var/cache/pacman/pkg" -maxdepth 1 -type f -exec mv -t "$KEEP/pkg-cache" {} +
  say "keyring out of image: $([ -d "$A/etc/pacman.d/gnupg" ] && echo NO || echo YES); pkg cache left: $(ls "$A/var/cache/pacman/pkg" | wc -l)" ;;

drivers) need_root drivers
  # DKMS drivers (broadcom-wl-dkms etc.) can only build with the kernel headers present; without
  # them the upgrade left Broadcom wifi with no driver. Install headers for both kernels, let the
  # DKMS hook build every module, verify, then put the keyring and cache back out.
  [ -d "$A/usr/share/ncde" ] || { say "run unpack first"; exit 1; }
  KEEP=$W/staging; G="$(ls -d "$KEEP"/image-gnupg-DO-NOT-SHIP.* 2>/dev/null | tail -1)"
  [ -d "$A/etc/pacman.d/gnupg" ] || { [ -n "$G" ] && mv "$G" "$A/etc/pacman.d/gnupg"; }
  mountpoint -q "$A" || mount --bind "$A" "$A"
  trap 'umount "$A" 2>/dev/null || umount -l "$A"' EXIT
  arch-chroot "$A" pacman -S --needed --noconfirm linux-headers linux-zen-headers
  arch-chroot "$A" dkms autoinstall -k "$(ls "$A/usr/lib/modules" | grep zen | tail -1)" || true
  arch-chroot "$A" dkms autoinstall -k "$(ls "$A/usr/lib/modules" | grep arch | tail -1)" || true
  DK="$(arch-chroot "$A" dkms status)"; say "dkms: $(echo "$DK" | tr '\n' ';')"
  mv "$A/etc/pacman.d/gnupg" "$KEEP/image-gnupg-DO-NOT-SHIP.$(date +%H%M%S)"
  find "$A/var/cache/pacman/pkg" -maxdepth 1 -type f -exec mv -t "$KEEP/pkg-cache" {} +
  say "keyring out of image: $([ -d "$A/etc/pacman.d/gnupg" ] && echo NO || echo YES)"
  case "$DK" in *installed*) ;; *) say "ABORT: no DKMS module installed"; exit 1 ;; esac ;;

ncde) need_root ncde
  [ -d "$A/usr/share/ncde" ] || { say "run unpack first"; exit 1; }
  n=0; bad=0
  while IFS= read -r -d '' f; do
    rel="${f#"$STAGE_SRC"/}"
    case "$rel" in
      *__pycache__*|*.pyc|*prebak*|*.reverted-*|*.retired-*|*.README.md|home/*|flutter-backgrounds/*|\
      usr/share/ncde/controls/_a11y_test.qml|etc/geoclue/conf.d/90-ncde-static.conf|\
      etc/ncde/hummingbird-google-client.json|usr/local/bin/LaPivot) continue ;;
    esac
    dst="$A/$rel"
    if [ -e "$dst" ] && ! cmp -s "$f" "$dst"; then cp -a "$dst" "$dst.iso-aside-20260721"; fi
    install -D -o root -g root -m "$(stat -c %a "$f")" "$f" "$dst"
    if cmp -s "$f" "$dst"; then n=$((n+1)); else say "MISMATCH $rel"; bad=$((bad+1)); fi
    # per-user config ships in BOTH etc/skel and home/live (1000:1000) — ISO-BUILD-PLAN §10.1
    case "$rel" in etc/skel/*)
      [ -d "$A/home/live" ] && { h="$A/home/live/${rel#etc/skel/}"
        install -D -o 1000 -g 1000 -m "$(stat -c %a "$f")" "$f" "$h"
        chown 1000:1000 "$(dirname "$h")"; } ;;
    esac
  done < <(find "$STAGE_SRC" -type f -print0)
  cp -a /usr/local/bin/LaPivot "$A/usr/local/bin/LaPivot"   # palette-patched (publish --check proves it)
  setcap cap_sys_nice+ep "$A/usr/local/bin/LaPivot"          # cp drops caps; mksquashfs keeps the xattr
  if cmp -s /usr/local/bin/LaPivot "$A/usr/local/bin/LaPivot"; then n=$((n+1)); else bad=$((bad+1)); fi
  # NCDE Qt theme plugin: rebuilt per machine by ncde-apply, not in the payload — take the live one,
  # which is only valid if the image's Qt is exactly the live Qt (Qt private API)
  IQ="$(pacman -Q --root "$A" --dbpath "$A/var/lib/pacman" qt6-base | cut -d' ' -f2)"; LQ="$(pacman -Q qt6-base | cut -d' ' -f2)"
  [ "$IQ" = "$LQ" ] || { say "ABORT: image Qt $IQ != live Qt $LQ — the NCDE Qt plugin would not match"; exit 1; }
  install -D -o root -g root -m 755 /usr/lib/qt6/plugins/platformthemes/libncde-qpa.so \
    "$A/usr/lib/qt6/plugins/platformthemes/libncde-qpa.so" && n=$((n+1))
  [ -d "$A/home/live" ] && chown -R 1000:1000 "$A/home/live"      # §0a: all of home/live is 1000:1000
  for p in /usr/lib/ncde-update /usr/lib/systemd/system/ncde-apply.service \
           /usr/lib/systemd/user/ncde-update-check.service /usr/lib/systemd/user/ncde-update-check.timer; do
    [ -e "$p" ] && { mkdir -p "$A$(dirname "$p")"; cp -a "$p" "$A$(dirname "$p")/"; say "  + $p"; }
  done
  # Gate 2.5: regenerate the caches that vendoring files never refreshes
  mountpoint -q "$A" || mount --bind "$A" "$A"; trap 'umount "$A" 2>/dev/null || umount -l "$A"' EXIT
  arch-chroot "$A" sh -c 'glib-compile-schemas /usr/share/glib-2.0/schemas;
    gtk-update-icon-cache -f -t /usr/share/icons/hicolor; update-mime-database /usr/share/mime;
    update-desktop-database /usr/share/applications; gio-querymodules /usr/lib/gio/modules; fc-cache -s' || true
  say "NCDE files in image: $n verified, $bad mismatched; LaPivot caps: $(getcap "$A/usr/local/bin/LaPivot")"
  [ "$bad" = 0 ] ;;

test)   # Gate 2.6 — no sudo. The image is the installed twin: start the shell from it.
  [ -x "$A/usr/local/bin/LaPivot" ] || { echo "run ncde first"; exit 1; }
  T=$W/gate26; mkdir -p "$T/home"; cp -r "$A/etc/skel/." "$T/home/" 2>/dev/null || true
  Xvfb :79 -screen 0 1920x1200x24 >/dev/null 2>&1 & XP=$!; sleep 1
  bwrap --ro-bind "$A" / --dev /dev --proc /proc --tmpfs /tmp --tmpfs /run \
        --tmpfs /home --bind "$T/home" /home/stephen --ro-bind /tmp/.X11-unix /tmp/.X11-unix \
        --setenv HOME /home/stephen --setenv DISPLAY :79 --setenv QT_QPA_PLATFORM xcb \
        /usr/local/bin/LaPivot > "$T/lapivot.log" 2>&1 & LP=$!
  sleep 20
  if kill -0 $LP 2>/dev/null; then echo "GATE 2.6: LaPivot from the image is RUNNING after 20s"; ok=1
  else wait $LP || true; echo "GATE 2.6 FAILED: LaPivot from the image exited"; ok=0; fi
  DISPLAY=:79 import -window root "$T/gate26.png" 2>/dev/null || true
  kill $LP $XP 2>/dev/null || true
  grep -iE 'qml.*error|is not a type|cannot|failed to load' "$T/lapivot.log" | head -20 || true
  echo "screenshot: $T/gate26.png   log: $T/lapivot.log"; [ "$ok" = 1 ] ;;

squash) need_root squash
  [ -d "$A/etc/pacman.d/gnupg" ] && { say "ABORT: keyring in image"; exit 1; }
  mountpoint -q "$A" && { say "ABORT: image still bind-mounted"; exit 1; }
  L=$(find "$A/var/cache/pacman/pkg" -maxdepth 1 -type f | wc -l); [ "$L" = 0 ] || { say "ABORT: $L files in image pkg cache"; exit 1; }
  [ -f "$SFS" ] && mv "$SFS" "$SFS.aside-$(date +%H%M%S)"
  # ISO-BUILD-PLAN §10.3 exclude line; NEVER -all-root (home/live stays 1000:1000)
  mksquashfs "$A" "$SFS" -comp zstd -Xcompression-level 19 -noappend \
   -processors "$(( $(nproc) > 1 ? $(nproc) - 1 : 1 ))" \
   -wildcards -e 'proc/*' 'sys/*' 'dev/*' 'run/*' 'tmp/*' 'mnt/*' \
   'var/cache/ncde/qmlcache/*' \
   'helpwithisla' 'calamares-ncde' 'wallpapers' 'compass7' 'src' 'build' 'ncde-wm' \
   'version' \
   'etc/calamares/branding/archcraft' 'var/lib/pacman/sync/archcraft.db' 'etc/arch-release' \
   '... *.prebak*' '... *.tmp' '... *.rebuilt-broken-*' '... *.restored-from-*' \
   '... *.wrong-*' '... *.bak' '... *.orig' '... *.swp' '... *.brokenhtml-*' \
   '... __pycache__' '... *.iso-aside-*' \
   'usr/bin/ollama' 'usr/share/ollama' 'usr/lib/ollama' 'usr/share/licenses/ollama' \
   'var/lib/ollama' 'var/lib/pacman/local/ollama-*' 'opt/ncde-chroma' \
   'usr/local/bin/kickass-guard' 'usr/local/lib/ncde/ncde-vesper-provision.sh' \
   'usr/lib/systemd/system/ollama.service' 'usr/lib/systemd/system/chroma.service' \
   'usr/lib/systemd/system/kickass-guard.service' \
   'usr/lib/systemd/system/ncde-vesper-provision.service' \
   'usr/lib/tmpfiles.d/ncde-kickass.conf' \
   'usr/lib/sysusers.d/ollama.conf' 'usr/lib/tmpfiles.d/ollama.conf' \
   'usr/share/factory/etc/arch-release' \
   'usr/share/dbus-1/services/org.ncde.KickassGuard.service' \
   'usr/local/share/dbus-1/services/org.ncde.KickassGuard.service' \
   'usr/lib/systemd/user/ncde-sentinel.service' \
   'usr/bin/ncde-terminal' \
   'usr/local/bin/ncde-tauri-installer' \
   'usr/share/ncde/GliaDocPopup.' 'usr/share/ncde/MagpieTalker' \
   'usr/share/ncde/NCDESettings' 'usr/share/ncde/SpacePanel.qm' \
   'CLAUDE.md' 'PROJECT.md' 'NCDE-CALAMARES-PLAN.md' 'NCDE-INSTALL-PLAN.md' \
   'ISO-BUILD-PLAN.md' 'SESSION_HANDOFF.md' 'preview.html' \
   'check_session.sh' 'complete_checklist.sh' 'install_hooks.sh' \
   'log_command.sh' 'require_search_for_uncertainty.sh' 'settings.json' \
   '... deploy-*.sh' '... revert-*.sh'
  (cd "$W" && sha512sum airootfs.sfs > airootfs.sha512)
  unsquashfs -lls "$SFS" | grep -E ' squashfs-root/home/live$' | tee -a "$LOG"   # expect 1000/1000
  say "squashed: $(ls -lh "$SFS" | awk '{print $5}')" ;;

boot) need_root boot
  [ -f "$ORIG" ] && [ -f "$A/boot/vmlinuz-linux-zen" ] || { say "need backup + upgrade first"; exit 1; }
  KV="$(ls "$A/usr/lib/modules" | sort -V | tail -1)"
  case "$(file -L "$A/boot/vmlinuz-linux-zen")" in *"version ${KV%%-*}"*) ;; *) say "WARNING: /boot kernel does not report $KV — check before continuing" ;; esac
  # the live stick can only find its squashfs if the initramfs carries the archiso hooks
  H="$(lsinitcpio "$A/boot/initramfs-linux-zen.img" | grep -E '^hooks/' | tr '\n' ' ')"
  say "initramfs hooks: $H"
  case "$H" in *hooks/archiso\ *) ;; *) say "ABORT: initramfs has no archiso hook — the stick would not boot"; exit 1 ;; esac
  B=$W/boot; mkdir -p "$B/esp-old"
  # the stick's EFI partition = partition 2 of the whole-stick image
  OFF=$(( $(sfdisk -d "$ORIG" | awk -F'[=,]' '/start=/{i++; if(i==2) print $2}') * 512 ))
  mount -o loop,ro,offset=$OFF "$ORIG" "$B/esp-old"
  OLDSZ=$(du -sb "$B/esp-old" | cut -f1); OLDK=$(du -cb "$B/esp-old/arch/boot/x86_64/"* | tail -1 | cut -f1)
  NEWK=$(du -cb "$A/boot/vmlinuz-linux-zen" "$A/boot/initramfs-linux-zen.img" | tail -1 | cut -f1)
  MB=$(( (OLDSZ - OLDK + NEWK) / 1048576 + 64 ))           # content + 64 MiB headroom
  [ -f "$B/esp.img" ] && mv "$B/esp.img" "$B/esp.img.aside-$(date +%H%M%S)"
  mkfs.fat -C -n ARCHISO_EFI "$B/esp.img" $((MB * 1024)) >/dev/null
  mcopy -s -i "$B/esp.img" "$B/esp-old"/* ::/                # loader, entries, EFI, fix-kit — as on the stick
  mcopy -o -i "$B/esp.img" "$A/boot/vmlinuz-linux-zen"    ::/arch/boot/x86_64/vmlinuz-linux-zen
  mcopy -o -i "$B/esp.img" "$A/boot/initramfs-linux-zen.img" ::/arch/boot/x86_64/initramfs-linux-zen.img
  umount "$B/esp-old"
  mdir -i "$B/esp.img" ::/arch/boot/x86_64 | tee -a "$LOG"
  mcopy -n -i "$B/esp.img" ::/arch/boot/x86_64/vmlinuz-linux-zen "$B/k.chk"; cmp "$B/k.chk" "$A/boot/vmlinuz-linux-zen"
  mv "$B/k.chk" "$B/k.chk.done"
  say "new EFI partition image: $B/esp.img (${MB} MiB, kernel $KV)" ;;

iso) need_root iso
  [ -f "$SFS" ] && [ -f "$ORIG" ] && [ -f "$W/boot/esp.img" ] || { say "need backup, squash and boot first"; exit 1; }
  X=$W/extract
  if [ ! -d "$X/arch" ]; then osirrox -indev "$ORIG" -extract / "$X"; chmod -R u+w "$X"; fi
  mv "$X/arch/x86_64/airootfs.sfs" "$X/arch/x86_64/airootfs.sfs.old-$(date +%H%M%S)" 2>/dev/null || true
  mv "$X"/arch/x86_64/airootfs.sfs.old-* "$W/staging/" 2>/dev/null || true
  cp "$SFS" "$X/arch/x86_64/airootfs.sfs"; cp "$W/airootfs.sha512" "$X/arch/x86_64/airootfs.sha512"
  cp "$A/boot/vmlinuz-linux-zen" "$A/boot/initramfs-linux-zen.img" "$X/arch/boot/x86_64/"
  # the stick's OWN boot records (session 85: never Archcraft's), with the appended partition and its
  # EFI El Torito entry pointed at the new ESP image
  xorriso -indev "$ORIG" -report_el_torito as_mkisofs 2>/dev/null > "$W/orig-eltorito.txt"
  mapfile -t REC < <(sed -E \
      -e "s#^-append_partition 2 0xef .*#-append_partition 2 0xef $W/boot/esp.img#" \
      -e "s#^-e '--interval:appended_partition_2[^']*'#-e '--interval:appended_partition_2:all::'#" \
      -e "s#--interval:local_fs:([^:]*):([^:]*):'[^']*'#--interval:local_fs:\1:\2:'$ORIG'#" \
      -e "s#^-V .*##" "$W/orig-eltorito.txt" | grep -v '^$' | xargs -n1 -d '\n' printf '%s\n')
  printf '%s\n' "${REC[@]}" > "$W/new-eltorito.txt"
  grep -q "^-append_partition 2 0xef $W/boot/esp.img" "$W/new-eltorito.txt" || { say "ABORT: recipe has no appended ESP"; exit 1; }
  [ -f "$NEW" ] && mv "$NEW" "$NEW.aside-$(date +%H%M%S)"
  eval xorriso -as mkisofs -o "'$NEW'" \
    -iso-level 3 -full-iso9660-filenames -joliet -joliet-long -rational-rock \
    -V NCDE_POSEIDON --modification-date=2026051206515400 \
    $(tr '\n' ' ' < "$W/new-eltorito.txt") "'$X'"
  xorriso -indev "$NEW" -pvd_info -report_system_area plain > "$W/new-report.txt" 2>&1
  xorriso -indev "$NEW" -report_el_torito plain >> "$W/new-report.txt" 2>&1
  say "--- original vs new (Volume Id and Modif. Time must be identical) ---"
  grep -E 'Volume Id|Modif' "$W/orig-report.txt" | tee -a "$LOG"
  grep -E 'Volume Id|Modif' "$W/new-report.txt"  | tee -a "$LOG"
  DESC=$(python3 - "$NEW" <<'PYEOF'
import sys
f=open(sys.argv[1],'rb'); out=[]
for i in range(16,40):
    f.seek(i*2048); d=f.read(7)
    if d[1:6]!=b'CD001': break
    out.append(d[0])
    if d[0]==255: break
print(out)
PYEOF
)
  say "volume descriptors: $DESC (must be [1, 0, 2, 255])"
  [ "$DESC" = "[1, 0, 2, 255]" ] || { say "ABORT: no Joliet/El Torito — this ISO would black-screen"; exit 1; }
  [ "$(blkid -s UUID -o value "$NEW")" = "$(blkid -s UUID -o value "$ORIG")" ] \
    || { say "ABORT: ISO UUID changed — archisosearchuuid would not find the stick"; exit 1; }
  M=$W/new-mnt; mkdir -p "$M"; mount -o loop,ro "$NEW" "$M"
  (cd "$M/arch/x86_64" && sha512sum -c airootfs.sha512) | tee -a "$LOG"
  cmp "$M/arch/boot/x86_64/vmlinuz-linux-zen" "$A/boot/vmlinuz-linux-zen" && say "ISO kernel = image kernel"
  umount "$M"
  chown stephen:stephen "$NEW" "$W/new-report.txt"; say "new ISO: $NEW ($(ls -lh "$NEW" | awk '{print $5}'))" ;;

vmtest)   # no sudo. The gate that defines "done": boot, INSTALL, reboot into the install, LOG IN.
  [ -f "$NEW" ] || { echo "run iso first"; exit 1; }
  V=$W/vmtest; mkdir -p "$V"
  [ -f "$V/disk.qcow2" ] || qemu-img create -f qcow2 "$V/disk.qcow2" 40G
  [ -f "$V/OVMF_VARS.4m.fd" ] || cp /usr/share/edk2/x64/OVMF_VARS.4m.fd "$V/"
  BOOT=d; [ "${2:-}" = disk ] && BOOT=c
  qemu-system-x86_64 -enable-kvm -m 6144 -smp 4 -cpu host -vga virtio -display gtk \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file="$V/OVMF_VARS.4m.fd" \
    -cdrom "$NEW" -drive file="$V/disk.qcow2",if=virtio,format=qcow2 -boot "$BOOT" \
    -nic user,model=virtio-net-pci ;;

write) need_root write
  [ -f "$NEW" ] || { say "run iso first"; exit 1; }
  echo "The VM gate must have passed: installed in the VM, rebooted, LOGGED IN. Type YES to write the stick:"
  read -r ans; [ "$ans" = YES ] || { say "not written"; exit 1; }
  D="$(stick_disk)"; [ -b "$D" ] || { say "stick not found"; exit 1; }
  for p in $(lsblk -lnpo NAME "$D"); do umount "$p" 2>/dev/null || true; done
  MP="$(lsblk -no MOUNTPOINTS "$D" | tr -d '[:space:]')"
  [ -n "$MP" ] && { say "ABORT: stick still mounted ($MP)"; exit 1; }
  S=$(stat -c %s "$NEW"); say "writing $NEW to $D"
  dd if="$NEW" of="$D" bs=4M status=progress conv=fsync; sync
  if cmp -n "$S" "$NEW" "$D"; then say "VERIFIED: stick matches the new ISO"; else say "MISMATCH — do not use the stick"; exit 1; fi ;;

*) sed -n 2,20p "$0"; exit 2 ;;
esac
