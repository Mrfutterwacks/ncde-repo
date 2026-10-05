# NCDE-BUILD-COMMANDS.md — resume after reboot (updated 2026-06-22)

> ⭐ **2026-06-22 — read `SESSION_HANDOFF.md` "LATEST SESSION" first.** Boot menu fully de-Arched +
> parchment splash DONE (in `extract/`); plymouth = ncde; filesystem decision → **btrfs**; restore app
> ("Soundings") being rebuilt. STEP 1 below is the **finalized** exclude list (adds var/tmp, the 3
> Archcraft remnants, `*.bak/*.orig/*.swp`). **STEP 4 caution:** author the ISO **FROM `extract/`** with
> the `-as mkisofs` recipe — do **NOT** use `replay` from the base Archcraft ISO (that's why the last
> ISO still showed Archcraft boot + plymouth). Pending before §B: btrfs partition.conf, Calamares
> slideshow art (compass4), grub-theme-ncde (compass3), and recovery-app install if bundling now.

Snapshot of the ISO build, with every remaining command **ready to paste**.
All `sudo` lines are **operator-run** (Claude must NOT run sudo — that is what
broke sudo this session: Claude wrongly ran `sudo du`/`sudo ls` directly, likely
tripping `pam_faillock`). After reboot the lockout should clear; if not, as root:
`faillock --user stephen --reset`.

---

## STATE — what is DONE and verified
1. **Calamares set injected into the tree** (`[dead-legacy-tree]/etc/calamares/` + `usr/bin/`), verified:
   - `etc/calamares/settings.conf` == skeleton (NCDE sequence: `removeuser` in, `displaymanager` out, `branding: ncde`).
   - `etc/calamares/modules/shellprocess.conf` + `removeuser.conf` == skeleton.
   - `usr/bin/post_install.sh` + `usr/bin/chrooted_post_install.sh` present, mode **0755**.
   - `etc/calamares/branding/ncde/` present (9 files).
   - Fixes #1–#4 confirmed baked in (xsession no-clobber at chrooted_post_install.sh:289; grub `starfield`; `removeuser`; no placeholder pkg names).
   - `.prebak` backups made of the 3 replaced files (Archcraft May-12 originals).
   - Archcraft engine module configs KEPT (partition/users/bootloader/grubcfg/unpackfs/...). `unpackfs.conf` + `preservefiles.conf` reviewed = fine as-is.
2. **Tree is a complete bootable rootfs:** 683 pacman pkgs (linux 7.0.12, systemd 260.2, glibc, bash, mkinitcpio, calamares), kernel modules `7.0.12-arch1-1`, 6.1 GB. `boot/` empty is OK (kernel ships on ISO at `arch/boot/x86_64/`, install regenerates via initcpio/grubcfg/bootloader).
3. **Base ISO mounted + mapped** (read-only): `~/ncde-ISO/mnt/iso`.
   - squashfs to replace: `arch/x86_64/airootfs.sfs` (2.66 GiB). Sidecar: **`airootfs.sha512` only** (no md5).
   - kernel: `arch/boot/x86_64/vmlinuz-linux` (matches unpackfs.conf).
   - boot: BIOS `boot/syslinux/isolinux.bin` + `boot/grub/`; UEFI `EFI/BOOT/BOOT{x64,IA32}.EFI` + `loader/`.
4. **`~/ncde-ISO/extract/`** = faithful copy of the ISO tree **minus** the two squashfs files (ready to receive the new `airootfs.sfs`).

## NOT done yet

**STALE — reconfirmed false 2026-06-30 night, this doc (dated 2026-06-22) was never updated past its
own session.** All four items below are actually done: `~/ncde-ISO/extract/arch/x86_64/airootfs.sfs`
exists (4.48GB, dated Jun 26) with a populated `.sha512` sidecar; two finished ISOs exist
(`~/ncde-ISO/out/ncde-poseidon.iso` 5.04GB, `ncde-poseidon-2026.06.21-x86_64.iso` 4.8GB, plus a
top-level `~/ncde-ISO/ncde-poseidon.iso`); VM testing genuinely happened —
`~/ncde-ISO/vmtest/install-test.qcow2` (15GB) and a dated real runbook
`~/ncde-ISO/FIX-installed-boot.md` (2026-06-25) document an actual encountered boot failure
("premature end of file" on the kernel) on an installed disk. Do not re-run these steps assuming
nothing has happened — check `~/ncde-ISO/` state first. Original claims kept below for history:
- Build new `airootfs.sfs` (mksquashfs) — **command below**.
- Regenerate `airootfs.sha512`.
- Re-author the ISO with xorriso.
- VM boot/install test.

---

## STEP 1 — build the new squashfs  (operator runs)
> **🔴 SUPERSEDED 2026-07-07 (final ISO audit): do not run this STEP 1 as written.** Two
> corrections, both mandatory:
> 1. **Never build from the raw tree** — it is uid-1000 throughout with ZERO suid bits
>    (su*o/pkexec/passwd would ship broken). First: `sudo bash ~/ncde-ISO/fix-ownership.sh`
>    (clones tree → `~/ncde-ISO/airootfs-root/`, restores ownership/modes from live,
>    self-verifies), then `sudo setcap cap_sys_nice+ep ~/ncde-ISO/airootfs-root/usr/local/bin/LaPivot`,
>    then point mksquashfs at **`/home/stephen/ncde-ISO/airootfs-root`**.
> 2. **Use ISO-BUILD-PLAN §10.3's exclude line** (re-derived 2026-07-07) — it now also covers
>    the truncated QML fragments, `*.wrong-*`, `__pycache__`, `*.brokenhtml-*`, the inert LLM
>    stack (ollama/chroma/kickass-guard + units), the stale user sentinel unit, top-level
>    `ncde-wm/` + `version`, and the stale `usr/bin/ncde-terminal`. The line below is HISTORY.
> Also stale below: "Kept on purpose: `version`" — `version` is now EXCLUDED per §10.3.

```bash
# HISTORICAL — see the supersede banner above; use ISO-BUILD-PLAN §10.3's line
sudo mksquashfs /home/stephen/ncde-staging/LaPivot \
  /home/stephen/ncde-ISO/extract/arch/x86_64/airootfs.sfs \
  -comp zstd -Xcompression-level 19 -noappend -wildcards \
  -e 'proc/*' 'sys/*' 'dev/*' 'run/*' 'tmp/*' \
     'var/tmp/*' \
     'var/cache/ncde/qmlcache/*' \
     'helpwithisla/*' 'calamares-ncde/*' 'wallpapers/*' 'ncde-docs' \
     'etc/calamares/branding/archcraft' \
     'var/lib/pacman/sync/archcraft.db' \
     'etc/arch-release' \
     '... *.prebak' '... *.tmp' '... *.bak' '... *.orig' '... *.swp' \
     'CLAUDE.md' 'PROJECT.md' 'NCDE-CALAMARES-PLAN.md' 'NCDE-INSTALL-PLAN.md' \
     'ISO-BUILD-PLAN.md' 'SESSION_HANDOFF.md' 'NCDE-RECOVERY-APP.md' 'preview.html' \
     'check_session.sh' 'complete_checklist.sh' 'install_hooks.sh' \
     'log_command.sh' 'require_search_for_uncertainty.sh' 'settings.json'
```

## STEP 2 — verify nothing leaked + uid 1000 preserved  (no sudo)
```bash
SFS=/home/stephen/ncde-ISO/extract/arch/x86_64/airootfs.sfs
ls -lah "$SFS"
unsquashfs -l "$SFS" | grep -iE 'prebak|CLAUDE|PROJECT|-PLAN|SESSION_HANDOFF|preview\.html|calamares-ncde|helpwithisla|ncde-docs|\.tmp$|qmlcache/' || echo "CLEAN: no junk leaked"
unsquashfs -lls "$SFS" | grep ' home/live$' | head    # expect uid/gid 1000
```

## STEP 3 — regenerate the checksum sidecar  (operator runs; path matters)
The `.sha512` stores a bare filename, so generate it from inside that dir.
```bash
cd /home/stephen/ncde-ISO/extract/arch/x86_64
sudo sh -c 'sha512sum airootfs.sfs > airootfs.sha512'
cat airootfs.sha512
```

## STEP 4 — re-author the ISO with xorriso  (operator runs)
Cleanest = replay the original boot setup (reuses El Torito/MBR/ESP verbatim),
just swap in the new squashfs:
```bash
xorriso -indev /home/stephen/Downloads/archcraft-2026.05.12-x86_64.iso \
  -outdev /home/stephen/ncde-ISO/out/ncde-poseidon-2026.06.21-x86_64.iso \
  -boot_image any replay \
  -update /home/stephen/ncde-ISO/extract/arch/x86_64/airootfs.sfs /arch/x86_64/airootfs.sfs \
  -update /home/stephen/ncde-ISO/extract/arch/x86_64/airootfs.sha512 /arch/x86_64/airootfs.sha512 \
  -commit
```
(Create `~/ncde-ISO/out/` first: `mkdir -p /home/stephen/ncde-ISO/out`.)
If `replay` misbehaves, fall back to the explicit `-as mkisofs` recipe captured
below (verbatim from the original ISO's El Torito catalog).

### Captured El Torito recipe (from `xorriso -report_el_torito as_mkisofs`)
> **🔴 TRAP — this recipe is INCOMPLETE BY DESIGN (proven the hard way, session 85):**
> `-report_el_torito as_mkisofs` reports the BOOT equipment ONLY. It does NOT include the
> filesystem options. Authoring with just this recipe produces an ISO with **no Joliet and no
> Rock Ridge** → the initramfs cannot resolve `/arch/x86_64/airootfs.sfs` → **black screen
> forever, no desktop, no VTs** (session 85 shipped exactly this to the install stick; caught
> by the VM boot gate). Every `-as mkisofs` authoring MUST ALSO carry:
> ```
> -iso-level 3 -full-iso9660-filenames -joliet -joliet-long -rational-rock
> ```
> Verify before ever dd'ing: volume descriptors must be `[1, 0, 2, 255]`
> (PVD + El Torito + **Joliet** + terminator) — compare against the previous working ISO.
> Full working command from session 85: SESSION_HANDOFF 85 addendum.
```
-V 'ARCHCRAFT_202605'
-isohybrid-mbr --interval:local_fs:0s-15s:zero_mbrpt,zero_gpt:'<orig.iso>'
-partition_cyl_align off
-partition_offset 16
--mbr-force-bootable
-append_partition 2 0xef --interval:local_fs:6338368d-7112511d::'<orig.iso>'
-iso_mbr_part_type 0x00
-c '/boot/syslinux/boot.cat'
-b '/boot/syslinux/isolinux.bin'
-no-emul-boot -boot-load-size 4 -boot-info-table
-isohybrid-gpt-basdat
-eltorito-alt-boot
-e '--interval:appended_partition_2_start_1584592s_size_774144d:all::'
-no-emul-boot
```
**Rule-7 note:** ISO volume label is `ARCHCRAFT_202605`. Boot configs
(`boot/syslinux/archiso_sys-linux.cfg`, `boot/grub/loopback.cfg`, `loader/entries/*`)
reference it as `archisolabel=ARCHCRAFT_202605` to find the squashfs at boot.
Renaming the label = coordinated edit of all those. KEEP for first working build;
Rule-7 the user-visible boot-menu titles separately.

## STEP 5 — unmount the base ISO when done building  (operator runs)
```bash
sudo umount /home/stephen/ncde-ISO/mnt/iso
```

## STEP 6 — VM test gate (ISO-BUILD-PLAN §6) = definition of "done"
UEFI (OVMF) first, then BIOS. Acceptance checklist in ISO-BUILD-PLAN §6.

---
*Authoritative docs: ~/my-project/docs/{CLAUDE,PROJECT,NCDE-CALAMARES-PLAN,ISO-BUILD-PLAN,SESSION_HANDOFF}.md*
