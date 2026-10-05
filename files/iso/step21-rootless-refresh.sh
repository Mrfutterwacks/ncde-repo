#!/bin/bash
# step21-rootless-refresh.sh — HOW TO REMAKE THE NCDE_POSEIDON ISO (2026-10-01). No root anywhere.
#
# Continues step20-refresh-poseidon.sh. Its root stages already ran on 2026-09-29 and are NOT repeated:
#   backup  (~/ncde-ISO/poseidon-20260721-stick.img = whole July stick: ISO + appended EFI partition)
#   unpack  (~/ncde-ISO/airootfs = the image tree, owned by root, as unsquashfs-as-root left it)
#   upgrade + drivers (every package current, kernel 7.2.7, DKMS built; keyring + pkg cache parked
#            in ~/ncde-ISO/staging)
# Everything after that runs as the normal user (operator 2026-10-01: "you don't need root to extract and
# resquash"). Root is never needed because the image tree is never written:
#   * mksquashfs reads the root-owned tree as-is and records the REAL uid/gid/mode/xattrs from stat.
#   * Every changed file is excluded from the tree and supplied as a pseudo definition (-pf): content from
#     a file we can read, with the exact owner/mode/mtime it must have. Capabilities via `x`.
#   * The ~100 files the user cannot read (shadow, sudoers, 0600 configs, 4711 binaries, 0700 dirs) come
#     from proven-identical sources: the July image (unchanged since, by size+mtime), the exact package
#     versions from the 09-29 upgrade cache (size+mtime match), or are rebuilt (shadow/gshadow +
#     systemd-imds, size matches byte for byte; the archiso initramfs via mkinitcpio in a user namespace).
#
# Stages, in order (each checks the one before):
#   bash step21-rootless-refresh.sh pkgs        # fetch ncde + ncde-qpa from the release, verify with the pinned key
#   bash step21-rootless-refresh.sh overrides   # build every replacement + the pseudo/exclude lists
#   bash step21-rootless-refresh.sh initramfs   # archiso initramfs for both 7.2.7 kernels (user namespace)
#   bash step21-rootless-refresh.sh squash      # mksquashfs zstd-19 (long; lowest priority)
#   bash step21-rootless-refresh.sh verify-sfs  # owners, suid, caps, overrides, nothing leaked
#   bash step21-rootless-refresh.sh boot        # new EFI partition image (mtools) with the 7.2.7 kernel
#   bash step21-rootless-refresh.sh iso         # xorriso, the stick's own boot records; volume/UUID/sha checks
#   bash step21-rootless-refresh.sh vmtest      # QEMU/OVMF: boot the ISO, screenshot the live desktop
#   then the stick is written (the only step that touches a device; see "write").
#
# What changes vs the 09-29 tree (all measured; see the README RESUME block of 2026-10-01):
#   NCDE = the canonical tree (source-built LaPivot ddb4152c with the Kith fix, Verdantfolio fix, the
#   2026-10-01 QML), ncde-automount retired (global mask), Openbox removed (as on the live machine),
#   geoclue 90-ncde-static.conf removed (patch policy 33: never on a machine without /etc/geolocation —
#   it disabled wifi+ip so installs had NO location), NCDE repo PREINSTALLED: [ncde] in pacman.conf,
#   ncde + ncde-qpa registered in the pacman DB (their alpm hooks were missing, so installs never applied
#   updates), the installer trusts the pinned repo key on the target (fresh keyring).
set -euo pipefail
W=$HOME/ncde-ISO
A=$W/airootfs
B=$W/b21
ORIG=$W/poseidon-20260721-stick.img
CACHE=$W/staging/pkg-cache
PKGS=$W/repo-pkgs
HERE="$(cd "$(dirname "$(readlink -f "$0")")" && pwd)"
SRC="$(cd "$HERE/../full-patch-20260711/src" && pwd)"
NEW=$W/out/poseidon-$(date +%Y%m%d).iso      # the name step20 "write" looks for
REPO_URL=https://github.com/Mrfutterwacks/ncde-repo/releases/download/installer
KEY_FPR=E878E789CB735F6ADA9D8C642A5C56F563EACBA5
NCDE_PKG=ncde-2026.10.01.2102-1-x86_64.pkg.tar.zst
QPA_PKG=ncde-qpa-1.0-1-x86_64.pkg.tar.zst
LOG=$W/step21.log
mkdir -p "$B" "$W/out"
say(){ echo "[$(date +%T)] $*" | tee -a "$LOG"; }
bg(){ chrt --other 0 nice -n 19 ionice -c 2 -n 7 "$@"; }      # rebuilds never compete with the shell
[ "$(id -u)" != 0 ] || { echo "Run as the normal user — this recipe needs no root."; exit 1; }

case "${1:-}" in
pkgs)
  mkdir -p "$PKGS"; cd "$PKGS"
  for f in "$NCDE_PKG" "$QPA_PKG"; do
    [ -f "$f" ] || curl -fsSL -o "$f" "$REPO_URL/$f"; curl -fsSL -o "$f.sig" "$REPO_URL/$f.sig"
  done
  curl -fsSL -o ncde-repo.gpg "$REPO_URL/ncde-repo.gpg"
  G=$(mktemp -d); trap 'rm -rf "$G"' EXIT
  GNUPGHOME=$G gpg -q --import ncde-repo.gpg
  [ "$(GNUPGHOME=$G gpg --with-colons --fingerprint | awk -F: '/^fpr/{print $10; exit}')" = "$KEY_FPR" ] \
    || { say "ABORT: release key is not $KEY_FPR"; exit 1; }
  for f in "$NCDE_PKG" "$QPA_PKG"; do
    GNUPGHOME=$G gpg --status-fd 1 --verify "$f.sig" "$f" 2>/dev/null | grep -q "VALIDSIG $KEY_FPR" \
      || { say "ABORT: bad signature on $f"; exit 1; }
  done
  say "packages verified with $KEY_FPR: $NCDE_PKG $QPA_PKG" ;;

overrides)
  [ -d "$A/usr/share/ncde" ] || { say "no image tree at $A (step20 unpack/upgrade first)"; exit 1; }
  [ -f "$PKGS/$NCDE_PKG" ] || { say "run pkgs first"; exit 1; }
  cd "$B"; chmod -R u+w ov oldx pkgx pdb 2>/dev/null || true; rm -rf ov oldx pkgx pdb; mkdir -p ov pkgx/ncde pkgx/qpa
  # 1. the July image: source of unreadable items that did not change since (size+mtime proven below)
  [ -f old.sfs ] || xorriso -osirrox on -indev "$ORIG" -extract /arch/x86_64/airootfs.sfs old.sfs 2>/dev/null
  chmod u+w old.sfs 2>/dev/null || true
  unsquashfs -lln old.sfs > old-sfs-list.txt 2>/dev/null
  # 2. unreadable items in the tree (the user cannot read them; mksquashfs could not either)
  (cd "$A" && find . -xdev \( -path ./proc -o -path ./sys -o -path ./dev -o -path ./run -o -path ./tmp \) -prune \
     -o \( ! -type l ! -readable \) -prune -printf '%y\t%p\n' 2>/dev/null) | sed 's|\t\./|\t|' > unreadable.txt
  say "unreadable in tree: $(wc -l < unreadable.txt)"
  # 3. package files for the unreadable package-owned configs/binaries (exact versions of the 09-29 upgrade)
  python3 - "$A" > unreadable-owners.txt <<'PY'
import os,sys,glob
A=sys.argv[1]; want={l.split('\t',1)[1].strip() for l in open('unreadable.txt') if l.startswith('f')}
for d in glob.glob(A+'/var/lib/pacman/local/*/files'):
    pk=os.path.basename(os.path.dirname(d))
    for l in open(d):
        l=l.strip()
        if l in want: print(pk+'\t'+l)
PY
  while IFS=$'\t' read -r pk f; do
    a=$(ls "$CACHE/$pk"-*.pkg.tar.zst 2>/dev/null | grep -v '\.sig$' | head -1) || true
    [ -n "$a" ] && bsdtar -xpf "$a" -C ov --no-same-owner "$f" 2>/dev/null || true
  done < unreadable-owners.txt
  # 4. July image copies (verified against the tree by size+mtime in the generator)
  awk -F'\t' '{print $2}' unreadable.txt > want-old.txt
  unsquashfs -no-xattrs -d oldx -ef want-old.txt old.sfs > /dev/null 2>&1 || true
  # 5. shadow/gshadow: July file + users/groups the upgrade added (sysusers format; size checked)
  python3 - "$A" <<'PY'
import os,sys
A=sys.argv[1]
def names(p): return [l.split(':',1)[0] for l in open(p) if l.strip()]
day=int(os.lstat(A+'/etc/shadow').st_mtime)//86400
for sh,pw,fmt in (('shadow','passwd','%s:!*:'+str(day)+':::::1:\n'),('gshadow','group','%s:!*::\n')):
    old=open('oldx/etc/'+sh).read(); have=set(names('oldx/etc/'+sh))
    add=[n for n in names(A+'/etc/'+pw) if n not in have]
    os.makedirs('ov/etc',exist_ok=True)
    open('ov/etc/'+sh,'w').write(old+''.join(fmt%n for n in add))
    print(sh,'added',add)
PY
  # 6. the NCDE repo: packages unpacked + registered in a COPY of the image's pacman DB (user namespace)
  bsdtar -xpf "$PKGS/$NCDE_PKG" -C pkgx/ncde --no-same-owner; bsdtar -xpf "$PKGS/$QPA_PKG" -C pkgx/qpa --no-same-owner
  mkdir -p pdb/root/var/lib/pacman pdb/root/var/cache/pacman/pkg pdb/gnupg; cp -a "$A/var/lib/pacman/local" pdb/root/var/lib/pacman/
  printf '[options]\nArchitecture = auto\nSigLevel = Never\nHookDir = /nonexistent-hooks\n' > pdb/pacman.conf
  P=$PWD/pdb
  bwrap --unshare-user --uid 0 --gid 0 --ro-bind / / --tmpfs /var/tmp --dev /dev --proc /proc --bind "$P" "$P" \
    pacman -U --dbonly --noconfirm --nodeps --nodeps --noscriptlet --config "$P/pacman.conf" --root "$P/root" \
    --dbpath "$P/root/var/lib/pacman" --cachedir "$P/root/var/cache/pacman/pkg" --logfile "$P/pacman.log" \
    --gpgdir "$P/gnupg" "$PKGS/$NCDE_PKG" "$PKGS/$QPA_PKG" >/dev/null
  for d in pdb/root/var/lib/pacman/local/ncde-*; do sed -i '/^%VALIDATION%$/{n;s/^none$/pgp/}' "$d/desc"; done  # sigs verified in pkgs
  # 7. pacman.conf with the [ncde] stanza (same text the patch writes)
  cp "$A/etc/pacman.conf" ov/etc/pacman.conf
  grep -q '^\[ncde\]' ov/etc/pacman.conf || printf '\n# NCDE updates arrive with the system update (added by ncde-full-patch)\n[ncde]\nSigLevel = Required DatabaseOptional\nServer = %s\n' "$REPO_URL" >> ov/etc/pacman.conf
  mkdir -p ov/usr/local/share/ncde-fix; cp "$PKGS/ncde-repo.gpg" ov/usr/local/share/ncde-fix/ncde-repo.gpg
  # 8. installer: trust the pinned repo key on the target (Calamares unpacks a fresh keyring)
  mkdir -p ov/usr/bin; python3 - "$A/usr/bin/chrooted_post_install.sh" ov/usr/bin/chrooted_post_install.sh "$KEY_FPR" <<'PY'
import sys
src,dst,fpr=sys.argv[1:]; s=open(src).read()
fn='''## -------- Trust the NCDE update repo (preinstalled [ncde]) --------
# (2026-10-01) The image ships the [ncde] repo with SigLevel=Required and the ncde package registered,
# so the target updates NCDE with every plain 'pacman -Syu'. The keyring is created fresh above, so the
# pinned NCDE key must be added + locally signed here, or every -Syu fails on the [ncde] database.
_trust_ncde_repo_key() {
	local _key=/usr/local/share/ncde-fix/ncde-repo.gpg _fpr=%s _got
	echo "+---------------------->>"
	echo "[*] Trusting the NCDE repo key..."
	[[ -f "$_key" ]] || { echo "[!] $_key missing — NCDE updates will not verify"; return 0; }
	_got=$(gpg --show-keys --with-colons "$_key" 2>/dev/null | awk -F: '/^fpr:/{print $10; exit}')
	if [[ "$_got" != "$_fpr" ]]; then echo "[!] NCDE key fingerprint mismatch ($_got) — not trusted"; return 0; fi
	pacman-key --add "$_key" && pacman-key --lsign-key "$_fpr" && echo "[*] NCDE repo key $_fpr trusted"
}

''' % fpr
anchor='## -------- Remove live-ISO initcpio drop-in ------'
# (2026-10-02) The lock rule is live-medium-only: the `live` account has no password, so an idle-lock
# prompt is a dead end there — but an installed system's user DOES have one and must still be asked.
# The Calamares rule is already stripped here in _clean_target_system; strip ours the same way, or an
# installed system silently inherits it and never asks for a password at all.
strip='        /etc/polkit-1/rules.d/49-nopasswd-calamares.rules\n'
assert s.count(strip)==1, 'anchor missing: '+strip
s=s.replace(strip, strip+'        /etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules\n')
assert s.count(anchor)==1 and s.count('\n_init_pacman_keyring\n')==1
s=s.replace(anchor, fn+anchor).replace('\n_init_pacman_keyring\n','\n_init_pacman_keyring\n_trust_ncde_repo_key\n')
open(dst,'w').write(s)
PY
  # copies keep their original modes (e.g. 4110 dbus-daemon-launch-helper = not even owner-readable); the
  # pseudo definitions carry the real mode, so make every source copy readable for `cat`
  chmod -R u+rw ov oldx pkgx pdb
  # 9. generate the pseudo definitions + excludes (all metadata decisions live here)
  python3 "$HERE/step21-overrides.py" "$A" "$SRC" "$B" > overrides.log
  tail -15 overrides.log | tee -a "$LOG" ;;

initramfs)
  cd "$B"; mkdir -p initramfs nsbin
  # mkinitcpio copies with --preserve=ownership; in a user namespace root files show as nobody, cp returns
  # non-zero and add_binary then skips the library scan (plymouth/curl libs went missing). The cpio is
  # written 0:0 regardless, so drop only the ownership part. mount.nfs (4711, unreadable) comes from ov/.
  printf '#!/bin/bash\na=(); for x in "$@"; do [ "$x" = "--preserve=mode,ownership" ] && x="--preserve=mode"; a+=("$x"); done\nexec /tmp/realcp "${a[@]}"\n' > nsbin/cp
  chmod +x nsbin/cp
  for k in $(ls "$A/usr/lib/modules"); do
    case "$k" in *zen*) n=linux-zen ;; *) n=linux ;; esac
    bg bwrap --unshare-user --uid 0 --gid 0 --ro-bind "$A" / --ro-bind "$B/ov/usr/bin/mount.nfs" /usr/bin/mount.nfs \
      --dev /dev --proc /proc --tmpfs /tmp --ro-bind "$A/usr/bin/cp" /tmp/realcp --ro-bind "$B/nsbin/cp" /usr/bin/cp \
      --tmpfs /run --tmpfs /var/tmp --bind "$B/initramfs" /mnt --setenv LANG C \
      mkinitcpio -k "$k" -g "/mnt/initramfs-$n.img" > "initramfs/$n.log" 2>&1 \
      || { say "ABORT: mkinitcpio $k failed — see $B/initramfs/$n.log"; exit 1; }
    H="$(lsinitcpio -a "initramfs/initramfs-$n.img" 2>/dev/null | tr '\n' ' ')"
    case "$H" in *archiso*) ;; *) say "ABORT: initramfs-$n has no archiso hook"; exit 1 ;; esac
    for b in plymouthd curl mount.nfs; do lsinitcpio "initramfs/initramfs-$n.img" | grep -q "usr/bin/$b$" || { say "ABORT: $b missing in $n"; exit 1; }; done
    lsinitcpio "initramfs/initramfs-$n.img" | grep -q 'libply.so' || { say "ABORT: plymouth libraries missing in $n"; exit 1; }
    say "initramfs-$n ($k): $(stat -c %s "initramfs/initramfs-$n.img") bytes, archiso + plymouth + pxe hooks complete"
  done ;;

squash)
  cd "$B"; [ -s pseudo.txt ] && [ -s excludes.txt ] || { say "run overrides first"; exit 1; }
  [ -s initramfs/initramfs-linux-zen.img ] || { say "run initramfs first"; exit 1; }
  [ -d "$A/etc/pacman.d/gnupg" ] && { say "ABORT: keyring in image"; exit 1; }
  [ -f airootfs.sfs ] && mv airootfs.sfs "airootfs.sfs.aside-$(date +%H%M%S)"
  say "mksquashfs start ($(wc -l < pseudo.txt) pseudo definitions, $(wc -l < excludes.txt) excludes)"
  bg mksquashfs "$A" airootfs.sfs -comp zstd -Xcompression-level 19 -noappend -no-progress \
    -processors "$(( $(nproc) > 1 ? $(nproc) - 1 : 1 ))" -pd 'd 755 0 0' -pf pseudo.txt \
    -wildcards -ef excludes.txt > squash.log 2>&1 || { say "ABORT: mksquashfs failed — $B/squash.log"; tail -20 squash.log; exit 1; }
  grep -i -E 'fail|cannot|error|skipp|denied' squash.log && { say "ABORT: mksquashfs reported problems (squash.log)"; exit 1; } || true
  sha512sum airootfs.sfs | sed 's|  .*|  airootfs.sfs|' > airootfs.sha512
  say "squashed: $(ls -lh airootfs.sfs | awk '{print $5}')" ;;

verify-sfs)
  cd "$B"; python3 "$HERE/step21-overrides.py" --verify "$A" "$SRC" "$B" | tee -a "$LOG" ;;

boot)
  cd "$B"; K="$A/boot/vmlinuz-linux-zen"; I="$B/initramfs/initramfs-linux-zen.img"
  [ -f "$I" ] || { say "run initramfs first"; exit 1; }
  OFF=$(( $(sfdisk -d "$ORIG" | awk -F'[=,]' '/start=/{i++; if(i==2) print $2}') * 512 ))
  rm -rf esp-old; mkdir esp-old; mcopy -s -n -i "$ORIG@@$OFF" '::/*' esp-old/
  OLDSZ=$(du -sb esp-old | cut -f1); OLDK=$(du -cb esp-old/arch/boot/x86_64/* | tail -1 | cut -f1)
  NEWK=$(du -cb "$K" "$I" | tail -1 | cut -f1); MB=$(( (OLDSZ - OLDK + NEWK) / 1048576 + 64 ))
  rm -f esp.img; mkfs.fat -C -n ARCHISO_EFI esp.img $((MB * 1024)) >/dev/null
  mcopy -s -i esp.img esp-old/* ::/
  mcopy -o -i esp.img "$K" ::/arch/boot/x86_64/vmlinuz-linux-zen
  mcopy -o -i esp.img "$I" ::/arch/boot/x86_64/initramfs-linux-zen.img
  mcopy -n -i esp.img ::/arch/boot/x86_64/vmlinuz-linux-zen k.chk && cmp k.chk "$K" && rm k.chk
  mcopy -n -i esp.img ::/arch/boot/x86_64/initramfs-linux-zen.img i.chk && cmp i.chk "$I" && rm i.chk
  say "EFI partition image: $B/esp.img (${MB} MiB, kernel $(file -bL "$K" | grep -o 'version [^ ]*'))" ;;

iso)
  cd "$B"; [ -f airootfs.sfs ] && [ -f esp.img ] || { say "need squash and boot first"; exit 1; }
  X=$B/extract
  if [ ! -d "$X/arch" ]; then osirrox -indev "$ORIG" -extract / "$X" 2>/dev/null; chmod -R u+w "$X"; fi
  cp airootfs.sfs "$X/arch/x86_64/airootfs.sfs"; cp airootfs.sha512 "$X/arch/x86_64/airootfs.sha512"
  cp "$A/boot/vmlinuz-linux-zen" "$X/arch/boot/x86_64/vmlinuz-linux-zen"
  cp initramfs/initramfs-linux-zen.img "$X/arch/boot/x86_64/initramfs-linux-zen.img"
  # the package list on the ISO describes what is in the image: the pacman DB as it ships (pdb copy)
  pacman -Q --dbpath "$B/pdb/root/var/lib/pacman" 2>/dev/null | grep -v '^openbox ' > "$X/arch/pkglist.x86_64.txt"
  xorriso -indev "$ORIG" -report_el_torito as_mkisofs 2>/dev/null > orig-eltorito.txt
  sed -E -e "s#^-append_partition 2 0xef .*#-append_partition 2 0xef $B/esp.img#" \
         -e "s#^-e '--interval:appended_partition_2[^']*'#-e '--interval:appended_partition_2:all::'#" \
         -e "s#--interval:local_fs:([^:]*):([^:]*):'[^']*'#--interval:local_fs:\1:\2:'$ORIG'#" \
         -e "s#^-V .*##" orig-eltorito.txt | grep -v '^$' > new-eltorito.txt
  grep -q "^-append_partition 2 0xef $B/esp.img" new-eltorito.txt || { say "ABORT: recipe has no appended ESP"; exit 1; }
  [ -f "$NEW" ] && mv "$NEW" "$NEW.aside-$(date +%H%M%S)"
  # session-85 trap: -as mkisofs MUST carry the filesystem options or the initramfs cannot find the sfs
  eval bg xorriso -as mkisofs -o "'$NEW'" -iso-level 3 -full-iso9660-filenames -joliet -joliet-long -rational-rock \
    -V NCDE_POSEIDON --modification-date=2026051206515400 $(tr '\n' ' ' < new-eltorito.txt) "'$X'" > xorriso.log 2>&1 \
    || { say "ABORT: xorriso failed — $B/xorriso.log"; exit 1; }
  DESC=$(python3 -c "
import sys
f=open('$NEW','rb'); out=[]
for i in range(16,40):
    f.seek(i*2048); d=f.read(7)
    if d[1:6]!=b'CD001': break
    out.append(d[0])
    if d[0]==255: break
print(out)")
  say "volume descriptors: $DESC (must be [1, 0, 2, 255])"
  [ "$DESC" = "[1, 0, 2, 255]" ] || { say "ABORT: no Joliet/El Torito — this ISO would black-screen"; exit 1; }
  [ "$(blkid -s UUID -o value "$NEW")" = "$(blkid -s UUID -o value "$ORIG")" ] \
    || { say "ABORT: ISO UUID changed — archisosearchuuid would not find the stick"; exit 1; }
  [ "$(blkid -s LABEL -o value "$NEW")" = NCDE_POSEIDON ] || { say "ABORT: label changed"; exit 1; }
  rm -f chk.sfs chk.k; xorriso -osirrox on -indev "$NEW" -extract /arch/x86_64/airootfs.sfs chk.sfs \
    -extract /arch/boot/x86_64/vmlinuz-linux-zen chk.k >/dev/null 2>&1
  cmp chk.sfs airootfs.sfs && cmp chk.k "$A/boot/vmlinuz-linux-zen" && rm -f chk.sfs chk.k \
    || { say "ABORT: ISO contents differ from what was built"; exit 1; }
  say "new ISO: $NEW ($(ls -lh "$NEW" | awk '{print $5}')); sfs + kernel read back identical" ;;

vmtest)   # boot the ISO in QEMU (UEFI), let it reach the live desktop, screenshot over QMP
  [ -f "${2:-$NEW}" ] || { echo "run iso first"; exit 1; }
  ISO=${2:-$NEW}; V=$B/vm; mkdir -p "$V"; cp -n /usr/share/edk2/x64/OVMF_VARS.4m.fd "$V/" 2>/dev/null || true
  rm -f "$V/qmp.sock"
  bg qemu-system-x86_64 -enable-kvm -m 6144 -smp 4 -cpu host -vga virtio -display none \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file="$V/OVMF_VARS.4m.fd" -cdrom "$ISO" -boot d \
    -nic user,model=virtio-net-pci -qmp unix:"$V/qmp.sock",server,nowait -serial file:"$V/serial.log" &
  QP=$!; echo "$QP" > "$V/qemu.pid"; say "VM started (pid $QP); screenshots via: python3 $HERE/step21-overrides.py --shot $V/qmp.sock <png>" ;;

write)
  echo "Writing the stick is the one step that needs a block device (root). After vmtest passes, run step20's"
  echo "write stage (same day, it finds $NEW, unmounts the stick, writes, verifies by read-back):"
  echo "  sudo bash $HERE/step20-refresh-poseidon.sh write" ;;

*) sed -n 2,40p "$0"; exit 2 ;;
esac
