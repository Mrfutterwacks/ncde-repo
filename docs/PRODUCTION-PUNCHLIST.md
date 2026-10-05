# PRODUCTION-PUNCHLIST.md — what is left before NCDE is production/ISO-ready

> **🔴 FIRST READ, EVERY SESSION (operator order, 2026-07-05): read this file immediately after
> CLAUDE.md, before SESSION_HANDOFF.md.** It is the single live list of what still blocks the
> squashfs/ISO. Update it the moment an item closes — an item is CLOSED only when built,
> deployed, AND operator-confirmed (see CLAUDE.md's confirmation convention). Full evidence for
> every item: `SESSION_HANDOFF.md` SESSION 71.
>
> `~/ncde-staging/LaPivot/` is THE production tree — the ONLY tree. The old frozen tree is DEAD.
> **🔴 REALITY UPDATE (session 85, 2026-07-08): THE DEV MACHINE NO LONGER EXISTS** (operator:
> "dev machine no longer exists... I don't have the source anymore"). The production tree and
> C++ source are LOST. What remains: the installed nodes' binaries (LaPivot unstripped — symbols
> + disassembly work), the QML on disk (plain text, patchable), the docs USB, the install stick,
> and session 85's repacked master ISO. Tree-path references below are HISTORICAL.
> **⚠️ RE-VERIFIED 2026-07-17: `~/ncde-staging/` (incl. `~/ncde-staging/LaPivot/compass7/`) does
> NOT exist anywhere** — not on this machine, not on the USB backup; checked both directly. The
> original C++ source is confirmed genuinely gone, including in the `compass7-reference`/
> `compass(7).zip` handoff bundle (its own `Lelan.cpp` header says outright: "implementation
> skeleton (new code; original lost)" — a ~500-line 2026-06-22 reimplementation attempt, NOT the
> real ~4,835-line engine). **Current recovery path:** Ghidra-decompile the live
> `/usr/local/bin/LaPivot` binary as oracle, reconstructed class-by-class in `~/ncde-wm-rebuild/`
> (partial — see `docs/lapivot-rebuild.md` for per-class status). QML was never lost (plain text,
> lives at `/usr/share/ncde/`). The live running system is the source of truth now, and
> `~/my-project/files/ncde-full-patch-20260711.sh` is the real deploy mechanism — every live fix
> folds into that one script. Full model: `docs/CLAUDE.md`'s matching 2026-07-17 correction. Any
> `sudo cp ~/ncde-staging/...` command anywhere below this banner is a HISTORICAL record of a
> command a past session ran while that tree still existed — it will not work today; do not run
> it as written.

## 0.19 — SESSION 87 (2026-07-10): FULL DOCS-vs-LIVE AUDIT of installed node "ncde" —
## four parallel audit passes over every doc cluster vs the running system. VERDICT: the
## live system matches the plans on nearly every axis (evidence in MEMORY.md §87 + this
## session's handoff). §0.18(a)'s "REMAINING" items ALL SHIPPED later on 07-09 (step8/step9
## repacks: netfix + vesper cache + rkhunter + sshd hardening + kit v2 in image; stick
## re-dd'd + sha512-verified; ESP refreshed) — that work was never doc-synced, fixed now.
## GAPS → `files/ncde-fix-pack-20260710.sh` (operator runs with sudo; also on stick ESP):
## audio pkgs unregistered/global-disabled · vendored libgstlibav dead vs libjxl 0.12 ·
## sched_ext REGRESSION (scx unowned, polkit action missing → scx-tools/scx-scheds) ·
## iio-sensor-proxy absent · fail2ban/auditd/nftables dry (3 of 5 Vesper engines; kickass
## §9.7 watcher table, policy accept) · pacman-init leftover · timeshift .desktop ·
## pre-update Soundings pacman hook (closes commercial.md's high-impact item) · node kit
## dir missing · dormant controls/ reduce-motion gating. PLUS one op-decision (prompted,
## default keep): cap_sys_nice makes LaPivot non-dumpable → portal Settings leg
## AccessDenied — RT boost vs sandboxed-app dark/light, cannot fix in code (source gone).
## NEXT ISO REPACK MUST: bake the 07-09 fixpack QML into the image (it postdates the final
## repack — fresh installs currently need the pack run from the ESP) + ship both fix packs
## in /usr/local/share/ncde-fix. Doc-stale strikes recorded in MEMORY.md §87 (zen.md BBR/
## unit-path/chain-of-command partially closed; commercial.md B-F2/AutoEnable/B-I2/GRUB/
## recovery-vt/B-S1 closed live).

## 0.20 — SESSION 87 POLISH (2026-07-10): operator reframe — NCDE is NOT sold, small trusted
## group. Commercial/legal items (GPL offer, license browser, Secure Boot, WPA-Enterprise)
## DROPPED as out-of-scope. `files/ncde-polish-20260710.sh` (deep-audited, operator runs sudo)
## closes: (A) lid/power → logind (operator picked logind-handles; §2.3 addressed at config
## level since the WM C++ owner is gone — Settings>Power dropdowns now cosmetic); (B) bluez/
## bluez-utils ownership adopt (BT stack was unowned = un-updatable) + unowned-/usr/bin report;
## (C) update-notification user timer (checkupdates+notify-send); (D) Vesper launcher .desktop
## (front-door gap closed); (E) starfield/NCDE-Poseidon theme clutter aside. **STILL C++-LOCKED,
## CANNOT fix without the lost dev tree (no stubs shipped): §2.13 clipboard Mechanism B, §2.14
## tiling freeze, §2 printer native flow (B-F3), §2.7 verve Geany tier, in-tab BT pairing.**
## font.pixelSize blanket sweep REJECTED (unsafe — 1120 literals/6 files). GliaTalk 4-app
## adoption still deferred.

## 0.17 — SESSION 85 FINALE (2026-07-09, ~01:00): THE REAL #1 KEYRING KILLER FOUND —
## **archiso's `/etc/systemd/system/etc-pacman.d-gnupg.mount` ships onto every installed
## system** (unowned file; `_remove_unwanted_packages`/`disable pacman-init` never touch it).
## While that file exists, pacman's own gpg socket units (pacman-pkg-owned, RequiresMountsFor)
## pull an EMPTY tmpfs over /etc/pacman.d/gnupg at EVERY boot — hiding a fully-populated
## on-disk keyring. PROOF: VM install had "Keyring populated: 180 public keys" in its own
## Calamares.log + 1.36MB pubring.gpg on disk UNDER the tmpfs (btrfs-restore autopsy of the
## VM disk); operator's node had the SAME populated install-time pubring (21:40) under the
## SAME tmpfs — the original "Errors occurred, no packages were upgraded" that started
## session 85 was THIS file, not the guard. (§0.16's guard bug is real but secondary — belt
## and suspenders, both now fixed.) FIXES: mount unit + pacman-init.service added to
## _clean_target_system's removal list (in image); fix 0 in ncde-install-fix.sh (stop mount,
## mv unit aside, daemon-reload) for already-installed nodes; operator node fixed live
## (findmnt clean, real keyring active). Final ISO (round 4, +audio) md5 86611d8f30082a99628083edf8013041,
## descriptors [1,0,2,255] verified. ✅ GATE PASSED (2026-07-09 ~01:45, operator-confirmed):
## fresh VM install from the final ISO → updates AND upgrades succeed, weather populates.
## First install in project history correct at first boot. Remaining: re-dd stick with the
## final ISO; refresh stale fix-kit copy on stick ESP; real-hardware install when convenient.

## 0.18 — NEXT SESSION QUEUE (logged 2026-07-09 ~02:30, session 85 wind-down):
## (a) ✅ FIXED LIVE + OPERATOR-CONFIRMED (session 86, 2026-07-09 ~11:55, "i see the icon
## now"): **network red X — ROOT CAUSE WAS SENTINEL, NOT readActiveNetwork.** Disassembly
## proved readActiveNetwork's lambdas write only ssid/speed/ip (+ clear() on disconnect) —
## they NEVER write "up"; the getter's UTF-16 "up"@0x1941b0 is the binary's ONLY UTF-16
## "up" (1 ref = the getter). Real writer: Lelan::onSentinelNetworkStateChanged(iface,
## up)@0x1634fa (ASCII "iface"/"up" @0x1ae410 — why the UTF-16 hunt missed it); it stores
## the LAST Sentinel event's bool for ANY interface. Sentinel udev_monitor.py emitted
## per-event operstate=="up" for EVERY net iface — lo ("unknown"→false) or mid-reauth wifi
## (dormant/down, and NO further udev event fires when it settles) stuck false in
## m_network["up"] → red X while connected (node + VM, same class). Sentinel is PYTHON ON
## DISK: fix = aggregate "any real iface up" (operstate or carrier, lo excluded) + one-shot
## 3s re-check per event. Deployed /usr/local/bin/sentinel/udev_monitor.py (backup
## .prebak-20260709-netaggregate; staged ~/ncde-ISO/staging/udev_monitor.py + runner
## apply-netfix.sh; live==staged md5 825ba23d). REMAINING for (a): patch same file inside
## the master ISO airootfs + repack (stick dd stopped for this); add as fix 6 to
## ncde-install-fix.sh for already-installed nodes (brother's laptop).
## (b) **kickass via systemctl + vesper** (operator, 2026-07-09: "we need to get kickass working
## with systemctl... vesper") — wire the kickass/vesper service chain properly; note sentinel's
## SetProcessTier D-Bus calls fail "ServiceUnknown: not activatable" (missing tier service) —
## likely same cluster. Read vesper.md/kickass-guard.md/zen.md cluster FIRST per CLAUDE.md §8.
## (c) audio done in ISO round 3 (wireplumber/pipewire-pulse enables + registration; §0.17 class).

## 0.16 — SESSION 85 (2026-07-08, night): §0.15's keyring "FIXED, PROVEN offline" WAS WRONG ON
## REAL INSTALLS — the guard (`[ -f trustdb.gpg ]`) is defeated by the script's own earlier
## `pacman -R*` calls (gpgme auto-creates an empty trustdb) → skipped on EVERY install; the
## operator's fresh node shipped 0 keys, no updates possible. bwrap "proof" never exercised the
## real execution order. THREE more install bugs found the same night on the real node:
## (a) /etc/mkinitcpio.conf.d/archiso.conf ships (unowned) → kernel updates half-fail, 225MB
## initramfs; (b) 4,493 files / 24 toolchain pkgs (gcc/make/fakeroot/git/gdb/yay/libisoburn)
## tree-copied but NOT in pacman DB → audits pass, yay/ncde-command fonts can never build,
## pacman conflicts on adopt; (c) ncde-sentinel enabled as USER unit that doesn't exist (real
## unit is SYSTEM scope) → dies on first reboot. PLUS weather root cause (binary-proven:
## fetch at tick 5 + every 30min only, no retry; geoclue was FINE — §2.12 stays closed).
## ✅ ALL FIXED, session 85: live node repaired; chrooted_post_install.sh corrected (key-count
## guard, _fix_live_initcpio, sentinel in enable list); WeatherPanel.qml QML fallback fetch
## (URL + icon map extracted from binary); toolchain REGISTERED inside the image via
## arch-chroot; field kit ships at /usr/local/share/ncde-fix/ in the image. NEW MASTER:
## ~/ncde-ISO/out/ncde-poseidon-fixed-full.iso on node "ncde" (label NCDE_POSEIDON,
## archisosearchuuid/modification-date preserved 2026-05-12-06-51-54-00 — NEVER change it,
## every boot entry finds the volume by it). Stick rewritten. ⏳ OPEN GATE: VM install test
## (qemu-desktop + edk2-ovmf), then a real-hardware install. Full detail: SESSION_HANDOFF 85.

## 0.15 — SESSION 84 (2026-07-07/08, night): FIRST INSTALLED SYSTEM BROKEN — TWO install-only
## defects ROOT-CAUSED, FIXED IN TREE + PROVEN. (1) GTK crash (below). (2) UPDATES COULD NEVER
## INSTALL: no /etc/pacman.d/gnupg ships or gets created (live keyring lives in the boot
## overlay; unpackfs copies the squashfs; nothing ran pacman-key; SigLevel=Required → every
## -Syu fails) — FIXED via _init_pacman_keyring() in chrooted_post_install.sh, PROVEN offline
## in bwrap fake-root (180 keys, web of trust). Brother's "nothing to do" in NCDE Command =
## failed check displayed as zero — retest on fixed ISO; if it persists with working network,
## Ghidra ncde-command's error display (source lost, standing permission). ✅ FIXED ISO BUILT
## 2026-07-08 01:50: ~/ncde-ISO/ncde-poseidon-2026.07.08-x86_64.iso (Gate-2.6 passed on the
## clone; both fixes verified INSIDE the sfs; xorriso layout verified). Burn + reinstall +
## the two retests (GTK apps launch; NCDE Command shows real updates AND installs them) =
## operator. Full detail: SESSION_HANDOFF 84 + part 2.
**Operator live reports from the installed laptop:** GTK errors typing `chromium` in terminal;
dock icons don't open apps; no browser reachable for Hummingbird Gmail setup. **ROOT CAUSE
(reproduced, not guessed):** the shipped `usr/share/glib-2.0/schemas/gschemas.compiled` was the
STALE Jun-21 blob — vendoring copied schema XMLs into the tree afterwards but never re-ran
`glib-compile-schemas` (the pacman hook dev relies on). `80-appmenu-gtk-module.sh` in
xinitrc.d loads appmenu-gtk-module into every session → g_settings_new on the missing schema →
**fatal GLib-GIO-ERROR SIGABRT in EVERY GTK3 app** (chromium/gimp/spotify/libreoffice = the
"dead" dock icons; Qt house apps unaffected — orchidee ran clean in the same repro). Dev never
broke because pacman hooks keep dev's blob current — the failure class only exists on installs.
**PROOF:** unprivileged bwrap container over the actual `~/ncde-ISO/airootfs-root` bytes:
shipped chromium aborted in ~2s with `GLib-GIO-ERROR: Settings schema 'org.appmenu.gtk-module'
is not installed` (exit 134); with ONLY the recompiled blob overlaid + both GTK module env vars
forced, ran 25s clean, zero GTK/schema errors. **FIXED IN TREE (same stale-generated-cache
class, all with .prebak backups):** gschemas.compiled recompiled (43,533→80,506 B),
hicolor icon-theme.cache regenerated (4,296→60,244 B — NCDE app icons were never indexed),
mime.cache + mimeinfo.cache regenerated, giomodule.cache regenerated (4→7 modules — gvfs
volume-monitor entries were missing = Orchidée automount risk). ld.so.cache self-heals at
first boot (ldconfig.service ConditionNeedsUpdate — unit verified in airootfs).
**NEW BINDING GATE: ISO-BUILD-PLAN "Gate-2.5"** — regenerate all five caches after ANY
vendoring, before every fix-ownership clone. **Chromium GCM `DEPRECATED_ENDPOINT` stderr
lines = standard Arch no-Google-API-keys noise (present with dev libs too), NOT the Gmail
blocker — the blocker was the crash.** Non-blocking flags left open: tree chromium is 149 vs
dev 150 (refresh at next vendor pass); orchidee emitted an `xset unknown option 900` usage
spam (separate small bug, not launch-affecting).
**INSTALLED-LAPTOP REPAIR (run ON THE LAPTOP, then relaunch apps — no reinstall):** see
SESSION_HANDOFF 84 command block. **OPERATOR CHOSE THE REINSTALL PATH instead** (can't run
the commands on the laptop) → full rebuild: fix-ownership re-clone (picks up the fixed
caches) → setcap → mksquashfs (2-proc/nice/nohup, per the freeze-recovery notes) → agent
re-runs the bwrap GTK gate on the NEW airootfs-root BEFORE the squashfs → xorriso re-author
(agent-run, proven recipe) → new ISO `ncde-poseidon-2026.07.08-x86_64.iso` (the 07.07 one
is the broken-install build — kept, not overwritten). The 3 stray-file excludes deferred
last night (ollama sysusers/tmpfiles confs + factory arch-release) are NOW in BOTH exclude
lists (airootfs-excludes.txt + §10.3).

## 0.14 — SESSION 83 (2026-07-07, night): FINAL ISO-READY AUDIT — RUN + ALL GAPS FIXED.
## Full detail + deploy dump + verify list: SESSION_HANDOFF.md SESSION 83 (single source).
**Status:** §0.12 dump verified LANDED+ACTIVE (ed667c19 was live; stats widget
OPERATOR-CONFIRMED working). Cursor "still not fixed" root-caused → **LaPivot is now the
session XSETTINGS manager** (new XSettingsManager.h, 13/13 Xvfb+real-GTK harness incl. live
size change seen by a running GTK app) + gsettings channel pins Kith (dconf still had
Qogirr/0). FINAL binary `45af643c…` AWAITING the session-83 dump + relog (8-point retest
applies). Gradient.TopLeftBottomRight journal flood (1,244/session) fixed pixel-identical.
Calamares audited: Fixes #1–#4 verified real; launch.sh copytoram zen-kernel sed bug fixed.
**THE ISO BLOCKER FOUND+SOLVED:** tree is uid-1000 with ZERO suid files → NEW
`~/ncde-ISO/fix-ownership.sh` (clone→restore ownership/modes from live→self-verify) + NEW
`~/ncde-ISO/airootfs-excludes.txt` (dry-run-proven: 0 junk, 22/22 must-ship). mksquashfs runs
on `~/ncde-ISO/airootfs-root/`, never the raw tree. §3 status: **3.2 CLOSED** (excludes
proven, §10.3 re-derived), **3.3 CLOSED** (plymouth hook present in mkinitcpio HOOKS —
re-verified), **3.5 CLOSED** (installer fonts fc-scan-verified vs stylesheet.qss), **3.7
CLOSED** (verdantfolio answered s77; abacus.desktop BUILT), **3.8 CLOSED** (completeness
gate re-run vs production tree — PASS, evidence in handoff 83), **3.1 now optional hygiene**
(excludes strip all of it at clone; rm remains operator's call), **3.4 OPEN** (volume label
at xorriso authoring), **3.6 OPEN** (recovery VM pass — needs the VM gate anyway).

## 0.13 — SESSION 82 part 2 (2026-07-07, night): LIVE LELAN/SENTINEL/ZEN ENDPOINT AUDIT
## (operator: "check all the process right now… so we know everything is working") — every leg
## observed against zen.md's knob table + sentinel-plan.md, values read off the RUNNING system.
**VERIFIED WORKING, live-observed (not code-read):** cpufreq governor `performance` ×4 on AC
(correct intel_pstate fallback per the actuator's own chain) · EPP `performance` · dirty_ratio
15 (AC, ADP1 online=1) · Sentinel restarted 19:22:30 with **9 temp sensors** (coretemp now
loaded — was 1 chip/0 CPU sensors before the §0.12 dump) · **ThermalChanged CAUGHT LIVE on the
system bus** during an agent CPU-load spike (dbus-monitor, a{sd} payload) · sched_ext: Sentinel
selected scx_bpfland and the kernel confirms `enabled` + `bpfland_1.1.2` running NOW ·
process tiering coherent: ncde-terminal cpu.weight=10000 unfrozen (foreground), background
Chromium frozen at weight 25 (App-Nap doing its job), SetProcessTier scope adopted across the
Sentinel restart · driver detection: MSSL1680 touchscreen gap detected+logged with plan
reference (§4e, known firmware-sourcing item) · pwm_guard honest no-op (EC-only laptop, §4d
known) · udev monitor active.
**TWO REAL GAPS FOUND + CLOSED (tree) / HANDED (live):**
1. **The WM's static self-boost tier is DEAD on live** — autogroup nice **0** (spec −5) and
   SCHED_OTHER (spec SCHED_FIFO 1): the shipped binary has no CAP_SYS_NICE (journal's own
   "SCHED_FIFO(1) unavailable" line at every login; both knobs share that root cause). zen.md
   documented "degrades gracefully" and nobody ever granted the capability. **Operator:**
   `sudo setcap cap_sys_nice+ep /usr/local/bin/LaPivot` — and NOTE: cp/mv deploys DROP file
   capabilities, so re-run setcap after EVERY LaPivot binary deploy, and the ISO build must
   apply it to the squashfs copy (mksquashfs preserves xattrs — add to ISO-BUILD-PLAN §10).
   Verify after relog: `cat /proc/$(pgrep -x LaPivot)/autogroup` → "nice -5"; `chrt -p <pid>`
   → SCHED_FIFO 1.
2. **ncde-zen-power.service was DISABLED live and the tree shipped no enablement** (unit file
   was in tree usr/lib/systemd/system, wants-symlink absent both sides; zero journal entries
   this boot — the correct live values came from the udev rule's coldplug replay, not the
   designed boot oneshot). Tree FIXED: wants-symlink added
   (`etc/systemd/system/multi-user.target.wants/ncde-zen-power.service` → absolute unit path).
   **Operator:** `sudo systemctl enable ncde-zen-power.service`.
**Not end-to-end exercisable tonight, honestly:** AC↔battery transition (machine on AC),
hotplug events (nothing to plug), ThermalCritical/back-off (won't overheat the machine —
wiring code-verified, subscribed since 07-02), uclamp anim-boost mid-animation (needs operator
interaction — after relog, `grep uclamp /proc/<pid>/sched` during a dock slide should read
min 200; observed 0 at idle, which IS the spec'd release value). Widget temp display becomes
the standing visible proof of the Sentinel→Lelan feed after the §0.12 relog.
**Known-opens per zen.md's own list, re-confirmed still open, NOT regressions:**
`AnimPolicy::setThermalPressure` dead entry point (thermal routes via m_thermalHot instead,
deliberately) · lowPower oracle zero callers · governor/dirty_ratio chain-of-command
(Sentinel senses+acts alone, Lelan not in that loop — operator design call pending).

## 0.12 — SESSION 82 (2026-07-07, evening): THREE LIVE OPERATOR REPORTS ON THE RUNNING
## `07bbfb75` (he relogged 17:44:52 — session 81 IS active) — ALL ROOT-CAUSED + FIXED + BUILT,
## AWAITING ONE DEPLOY DUMP (below). FINAL LaPivot sha `ed667c19…` (SUPERSEDES 07bbfb75, same
## tree + these fixes). WM binary changed → the standing 8-point frame retest applies.
**(a) FLUTTER "Video Call" BUTTON invisible (3rd report) — the session-79 fix was live and the
pill WAS rendering; its label was invisible ON ITS OWN CHIP.** Dark-mode `surfaceHi` = gilt4
(#e9c97c, light gold); the label drew inkSoft (#b8a07a) = **1.57:1** when idle and crd.cer3
(#5fb4c6) = **1.48:1** when callable — below perceptible for anyone, let alone the operator.
The sibling search/bell/users icons survive because Icon's default tint is k.gilt0 (6.4:1).
Fix (MagpieTalker.qml, tree): label = crd.cer1 when callable (7.3:1 dark — the crd ramp's own
dark-adapted step; = k.cer in light, the app-wide accent) / k.gilt0 otherwise (9.8:1 light).
qmllint ✓ + test_qml_load gate PASS. Backup `.prebak-20260707-flutterpillcontrast`. QML only,
no magpie rebuild. NOTE same-class flag, NOT fixed (don't widen unasked): the DM Nudge "≋"
glyph is also crd.cer3-on-surfaceHi (1.48:1 dark) — invisible in dark mode; operator to rule.
**(b) STATS WIDGET "0 MHz · 32°F" — two real reader bugs in WidgetData::readStats(), + the
Sentinel chain was never consumed:** (1) freq read `cpuinfo_cur_freq`, which modern pstate
drivers don't expose (empty → 0 GHz forever) — now `scaling_cur_freq` first, old path as
fallback; (2) temp took the FIRST non-empty thermal zone — zone0 here is an acpitz stub
reporting exactly 0 → permanent 32°F while the real sensor (x86_pkg_temp 58°C) sat in zone3 —
now **Sentinel-first** (Lelan.sentinelTemps, package sensor preferred — the chain of command
finally has a visible consumer) with a type-aware zone fallback that never accepts a 0-reading
zone. **PROOF: harness `compass7/lelan/test_widget_stats.cpp` drives the real shipped path
(onPulse(3)→readStats) — cpuFreqGHz 2.800 / cpuTempF 143.6, PASS exit 0** (the operator's own
live "0 MHz · 32°F" report is the failing baseline). ALSO: Sentinel on this host discovered NO
CPU sensor (only hwmon0=ADP1) because `coretemp` was never loaded — the temps feed was running
on empty. NEW tree file `etc/modules-load.d/ncde-sensors.conf` (coretemp + k10temp; non-matching
driver fails to bind harmlessly) so every ISO install feeds Sentinel real CPU temps. Backup
`WidgetData.h.prebak-20260707-cpustats`.
**(c) CURSOR-SIZE "kinda crashes" — LITERAL WM SEGFAULTS, root-caused + fixed:** journal
17:44:35–:51 shows TWO LaPivot coredumps in `CursorManager::installAsRootCursor` inside
libxcb-render-util, fired via Settings::inputChanged (the cursor-size apply); ncde-x11-session's
session-77 respawn guard relaunched the WM each time, masking it as a flicker. Root cause:
`xcb_render_util_query_formats()` returns a reply **CACHED on the connection** (const return;
freed only by xcb_render_util_disconnect) and the code const_cast+free'd it — first call fine,
every later call walked freed memory (the "no ARGB32 PictFormat advertised" warning at :35 was
the garbage parse, then SIGSEGV). Both frees removed. **PROOF: harness
`compass7/lelan/test_root_cursor.cpp` calls the real function 5× against a headless Xvfb —
fixed code 5/5 clean with the cache still parseable; NEGATIVE CONTROL on the prebak code ABORTS
("double free or corruption", exit 134).** Backup `CursorManager.cpp.prebak-20260707-formatscache`.
HONEST REMAINDER on "size not uniform desktop→windows": already-RUNNING clients read cursor
size once at their startup (no XSETTINGS daemon ships — Settings.h's own comment); after this
fix the apply completes, the WM/desktop and every NEWLY launched app are uniform, but existing
windows update on app relaunch. Real live-retheme fix = a minimal XSETTINGS manager in LaPivot —
operator decision, not silently built.
**(d) TREE dovecote-relay WAS STALE (ISO-blocking find):** `usr/local/bin/dovecote-relay` in the
tree was the Jun-15 pre-Flutter binary with ZERO `call_signal` support — the ISO would have
shipped a relay that can't signal Flutter calls. Live and `compass7/dovecote-relay/build/` both
have `a15a5322…`; tree copy refreshed to match (backup `.prebak-20260707-precallsignal`).
Flutter itself verified fully built: FlutterCall compiled into live magpie-talker `f88f5f05`
(all call/consent/backdrop symbols), qml6glsink+opus vendored tree+live, 6 backdrops live.
**THE SESSION-82 DEPLOY DUMP (run all, then ONE relog):**
```
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml /usr/share/ncde/MagpieTalker.qml
sudo cp ~/ncde-staging/LaPivot/etc/modules-load.d/ncde-sensors.conf /etc/modules-load.d/ncde-sensors.conf
sudo modprobe coretemp
sudo systemctl restart ncde-sentinel
rm -rf ~/.cache/LaPivot/qmlcache
```
**Verify after the relog:** (1) 8-point frame retest (standing rule); (2) Magpie: "✆ Video
Call" visible top-right IMMEDIATELY at launch, gilt-bright inside an open DM; (3) stats widget
shows real GHz + a real temperature within ~3s; (4) Settings → Input: flip cursor size
Small/Medium/Large repeatedly — no flicker/black-out, and `journalctl -b | grep -c segfault`
stays 0 for the new session; (5) new-launched windows match the chosen cursor size (existing
windows update when relaunched — known X11 limit, see (c)); (6) the session-81 7-part verify
list in SESSION_HANDOFF 81 still stands.

## 0.11 — SESSION 81 (2026-07-07): THE BIG PRE-ISO PASS — ALL BUILT + PROVEN. **OPERATOR RAN
## THE FULL DUMP same session ("all applied") — ON DISK ONLY; the relog had not happened when
## the session ended. NEXT AGENT: verify the running LaPivot is `07bbfb75…` via /proc/<pid>/exe
## BEFORE trusting anything active (session-77 lesson: applied ≠ active), then walk the 7-part
## verify list in SESSION_HANDOFF 81 with the operator — 8-point frame retest FIRST. He will
## report misbehaviors; diff against the .prebak-20260707-* chains, never layer guesses.**
## Contents:
## (a) designer GTK kit landed (§2.2 part 3); (b) Orchidée Ctrl+H + root protection (§2-6b);
## (c) BLACK CLIENT CURSOR root-caused (Archcraft Qogirr leftovers in xrdb + gtk settings.ini;
## GTK never reads XCURSOR_THEME) + cursor SIZE control made real on every channel — 13/13
## harness; ALSO fixes GTK3 apps never activating the NCDE theme on live (settings.ini said
## Arc-Dark) + new skel gtk settings.ini kill the trap for end users; (d) GLIATALK v1 — the
## unified-host message layer (docs/gliatalk.md = canonical spec + operator identity words):
## _NCDE_MENUS/_NCDE_MENU_INVOKE over X, WM = the session, published app menus replace Glia's
## relay trio, Orchidée = reference publisher — 5/5 real-display harness; (e) Glia menu no-dead-
## functions pass (System→Settings tabs via openSection, Help→Handbook, house-app launches,
## Places→Orchidée, zoom=ctrl+equal, relay tool + libxdo VENDORED into tree — was dev-host-only
## = dead menus on a fresh ISO); (f) Orchidée UX pack (undo/Delete/F2/cut-copy-paste/type-ahead/
## free-space/drag-out-of-Bin restore) — 46-check harness ALL PASS + binnie 44/44 re-PASS;
## (g) SOVEREIGN SEAL Ctrl+Alt+E (pkexec valet usr/lib/ncde/ncde-file-helper, polkit
## auth_admin_keep, no delete verb, root-protection even as root) — valet 6/6; (h) Handbook
## updated (GliaTalk bar, tiling story, Files & Bin chapter, world-band Magpie, Quick Keys).
## FINAL binaries: LaPivot 07bbfb75 (supersedes b9d0bf1f), magpie f88f5f05, binnie 82d3a710,
## orchidee 182edcf0, ncde-file-helper d610ae71 (new). WM changed → 8-point frame retest.
## OPEN AFTER THIS: operator click-tests (verify list), LaPivot-as-polkit-agent (unified-host
## follow-up for the in-bar password field), GliaTalk v2 (named ops, GTK3 module, .dt actions),
## other house apps adopt the publisher (Verve/Abacus/Magpie/Binnie — dozen lines each,
## docs/gliatalk.md §Adopting).

## 0.10 ✅ DEPLOYED + ACTIVE (verified session 79, 2026-07-06 22:31): the FINAL `d7db2d72…`
## dump IS LIVE AND RUNNING — pid 395271 (relog 22:31:38) is that exact binary (/proc sha
## match; live == tree == build), tree↔live /usr/share/ncde parity CLEAN (only the 4 §3 junk
## files). What remains here is the 8-point OPERATOR VERIFY LIST at the end of this section.
## History below:
## SESSION 78 (2026-07-06, late): DEPLOY-STATE VERIFIED + two new live-bug fixes.
**A. The session-77 ONE DEPLOY DUMP (§0.8/§0.9) IS LIVE AND ACTIVE — agent-verified, not
assumed:** running LaPivot pid 311006 (started 21:17:30, a real post-dump relog) IS the FINAL
`53c8829c…` binary (`/proc/311006/exe` sha match; live == tree == build). magpie-talker
`4f5c43e4` live == tree; ncde-x11-session byte-identical; verdantfolio QML app + helper + unit
all deployed (launcher starts the helper on demand — inactive unit is by design); tree↔live
`/usr/share/ncde` parity CLEAN (only diffs = the 4 truncated-name junk files on the §3 rm
list). **Session-71 §E is ALSO fully deployed:** Cormorant Garamond fonts live, all 6 .desktop
entries live, vesper brain RUNNING (697 MITRE techniques, port 8077), sentinel files identical
+ running proc (12:42) postdates them, picom.conf identical, recovery subsystem + pam live
(polkit rules file in a root-only dir — unverifiable without sudo, everything around it
landed). `xset q` confirms the §0.9 blank/saver fix active ("prefer blanking: no"). What
remains on §0/§0.6/§0.7/§0.8/§0.9 is OPERATOR VERIFICATION ONLY (the verify lists already
written in those sections).
**B. NEW — 84 live QML binding errors root-caused + FIXED, AWAITING DEPLOY:** `Theme.h` (the
C++ `theme` context object) never had `textShadowRadius`/`textShadowOffsetX`/`textShadowOffsetY`
even though its own header comment promises `theme.textShadow*` and 7 QML files bind them
(TopPanel/GliaBar/ClockPanel/MuchaClock/AppMenu/DesktopMenu/GliaDropMenu) — every binding was
undefined ("Unable to assign [undefined] to double" ×84 at startup), and the Fonts tab's shadow
radius/offset controls silently did nothing on theme-bound widgets. Fix: 3 Q_PROPERTYs + getters
reading settings via the same pattern as the existing props, unset-falls-back-to-smart-default
semantics copied from ThemeTokens.qml:46-48 (4.0/1.0/1.0). Built clean, nm-confirmed, tree
binary copy refreshed. Backup `Theme.h.prebak-20260706-themeshadow`. Interim shas `e8b25c91…`/`6af543f3…`/`8b99f059…`
SUPERSEDED same session by **FINAL session-78 sha `caed0d3a…`** (adds §2.9's screensaver
double-launch guard + crash-relaunch AND §2.5's idle-inhibit provider; supersedes `53c8829c` —
same tree, contains everything in it). Touches NCDEWindowManager.h (one read-only accessor) —
the standing 8-point frame retest rule applies after the relog.
**C. NEW — LeapFrogLedger.qml:935/941 Shortcut guard never worked:** `Shortcut` is not an Item,
so its `Window.window` attached property never attached (Qt warned at every load) — the
"don't fire `/`/`G` while typing in a text field" guard was permanently disengaged. Fix: read
the attached property through the root `app` Item (`app.Window.window`). qmllint exit 0. Backup
`LeapFrogLedger.qml.prebak-20260706-shortcutguard`.
**D. NEW — PowerTab timeout display lie fixed (the §0.9 item -1 known-minor):** a stored value
outside [0,5,15,30] (e.g. the 10/20 C++ defaults) displayed as "5 min" (timeIdx i<0→1 fallback);
now it renders as its own honest extra segment ("10 min") that disappears once a preset is
picked; presets store exactly as before. qmllint exit 0. Backup
`PowerTab.qml.prebak-20260706-timeidx`.
**E. §2.9 screensaver double-launch guard + crash-relaunch built (see §2.9) — in the same
binary.**
**F. §2.5 org.freedesktop.ScreenSaver inhibit provider BUILT + PROVEN 5/5 on the real bus (see
§2.5) — in the same binary.**
**NOTE: the operator applied the interim `caed0d3a` dump (B-F) same session, disk verified, NOT
yet relogged — then part 2 below superseded the binary again. The FINAL dump at the bottom of
this section covers everything.**

## 0.10 part 2 — SESSION 78 continued: Ledger year-view bug (operator-reported live) + holiday
## lore feature (operator ask) + §2.1 FontManager + §2.8 Vesper quarantine pane — ALL BUILT.
**G. LEDGER YEAR VIEW (operator: "numbers not lining up under the month and spilling off the
screen") — ROOT-CAUSED + FIXED:** the mini-month day cells were hardcoded 22×17px inside
responsive columns — a large accessibility font scale overflowed the cells (the misalignment)
and a small unmaxed window (possible since §0.7's lone-window change) pushed the fixed 154px
grids off screen (the spill). Now: cells derive from the real column width, day-number font
clamps to the cell, month titles elide, and the whole year page scrolls (Flickable).
**H. HOLIDAY LORE (operator: "holidays are listed and one could click and open lore") — BUILT:**
the Year view now lists "Feasts & Holy Days of <year>" beneath the grid (every entry from
cal-logic.js's HOLIDAYS almanac, sorted, hover shows "open the lore ›"); tapping opens a new
lore card (scrim + gilt card in the command-palette language, holiday seal + burgundy stripe
from the Day-view card); Month-view holiday names are now tappable too (underline on hover) and
open the same card. **Load-gate PROVEN:** new scaffolding harness
`compass7/lelan/test_qml_load_lapivot.cpp` (NOT in CMakeLists — stub context properties, real
engine, the magpie-lesson gate for LaPivot QML) — PASS on the edited file, and verified to FAIL
on a deliberately-broken copy. qmllint ✓. Backup `LeapFrogLedger.qml.prebak-20260706-yearview`.
**I. §2.1 FONTMANAGER BACKEND — BUILT + PROVEN (FonderieTab was fully dead):** new
`compass7/lelan/FontManager.h` (+CMakeLists +main.cpp `fontMgr` context registration) serves the
tab's full contract (fonts/busy/status/installedCount/total, families()/refresh()/installFont(),
fontsChanged/fontInstalled). Catalog: 33 faces, EVERY family name read back from the vendored
font files with fc-scan (No Invention), house faces marked repo "NCDE" with pkg "" (they ship
with the system), repo faces carry the session-67-verified package names. Install path =
PackageKit over the system bus (the same stack Lelan's update check uses; PackageKit is vendored
in the tree — packagekitd + policy verified present), signatures verified against the SHIPPED
interface XML, polkit handles privilege (xfce-polkit). **Harness
`compass7/lelan/test_font_manager.cpp`: 7/7 PASS exit 0** — incl. FAMILY HONESTY (every catalog
family resolves against the tree's real font files; first run caught my wrong oracle, not wrong
names) and graceful no-PackageKit failure. HONEST GAP: the dev host does not run PackageKit
("name not activatable") — the install leg needs an ISO/VM pass; FonderieTab.qml passes the
load gate with fontMgr registered.
**J. §2.8 VESPER QUARANTINE PANE — BUILT:** new `usr/share/ncde/vesper/QuarantinePane.qml`
(phosphor language, VesperButton/tokens), listing backend.quarantine with per-row RESTORE and
two-tap-confirm REMOVE (+KEEP disarm — the binnie veil rule); header gains a clickable
"N held" that toggles the pane; new silent `refreshQuarantine()` in VesperBackend (the voiced
reviewQuarantine() stays for the terminal); count refreshes whenever the window shows. qmllint
✓ ×3, Main.qml composition passes the load gate, live brain endpoint returns the exact bound
shape (`{"quarantine": []}`). Backups `*.prebak-20260706-quarpane` ×2.
**THE ONE SESSION-78 DEPLOY DUMP (FINAL binary sha
`d7db2d72d66e441c467476440db28b532a906f551bfd688ec33122ba424ad8a8` — supersedes `caed0d3a` (on
disk, never ran)/`e8b25c91`/`6af543f3`/`8b99f059` and the running `53c8829c`; contains
theme-shadow + saver guards + idle-inhibit + FontManager):**
```
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/LeapFrogLedger.qml /usr/share/ncde/LeapFrogLedger.qml
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/PowerTab.qml /usr/share/ncde/PowerTab.qml
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/vesper/Main.qml /usr/share/ncde/vesper/Main.qml
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/vesper/VesperBackend.qml /usr/share/ncde/vesper/VesperBackend.qml
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/vesper/QuarantinePane.qml /usr/share/ncde/vesper/QuarantinePane.qml
rm -rf ~/.cache/LaPivot/qmlcache   # then ONE relog
```
**Verify after the relog:** (1) 8-point frame retest (standing rule); (2) `journalctl -b |
grep -c "Unable to assign"` ≈ 0 for the new session; (3) Ledger → Year: numbers sit under each
month at any window size, feast list below, tap a feast → lore card, tap a Month-view holiday
name → same card, `/` while typing in a field does NOT open the palette; (4) NCDE Command → La
Fonderie: real catalog with previews, "N of 33 installed"; (5) Fonts-tab shadow knobs move
widget shadows; (6) PowerTab never lies "5 min"; (7) saver: Test twice = one saver; Firefox
video holds the saver off; (8) Vesper (on a real EICAR pop): "N held" in the header opens the
quarantine pane, RESTORE/REMOVE work, REMOVE needs the second tap.

## 0.4 ✅ CLOSED (2026-07-06, session 76) — open-max / unmax-to-grid tiling fix
**OPERATOR-CONFIRMED in his own words: "all window stacking and max are fixed."** Deploy proven
by agent, not assumed: live `/usr/local/bin/LaPivot` == tree == build sha `ac7cafee…`; running
pid 163299 IS that binary (`/proc/<pid>/exe` sha match), started 16:46:57 (real post-deploy
relog); MotifFrame.qml + TilingManager.qml + main.qml byte-identical staging↔live. Closes §0.5's
regression too (same binary carries the focus-heal fix). Original entry kept below for history:
Windows were opening snapped to tile, not maximized. Operator spec (definitive, 2026-07-06):
open = always maximized (one max at a time); ONLY Amethyst-unmax puts a window into the tile
grid (up to 8, 4 top/4 bottom); Green pulls it back to max. Fixed: `tiled` default false +
max-atoms gate (NCDEWindowManager.h), Amethyst = setTiled(true) not float-restore
(MotifFrame.qml), grid filter excludes maximized (TilingManager.qml). Binary sha `ac7cafee…`
SUPERSEDES session-74's `761676db…` (contains that FocusIn fix too). Deploy commands + 8-point
retest checklist (incl. ALL previously-fixed frame behaviors): SESSION_HANDOFF.md SESSION 75.
Backups `*.prebak-20260706-unmaxtile`. CLOSES only on operator confirmation.

## 0.6 GATE — SESSION 76 (2026-07-06): IRIS CHROMA 90-palette redesign — ✅ DEPLOYED + ACTIVE
## (operator relogged 18:49 on `cec90cb8`; current live `53c8829c` contains it, verified §0.10
## — awaiting operator/test-group VISUAL confirmation only, verify text below)
Operator order (production pass, human-test-group report): all 90 palettes looked like the same
shades. Measured true: 404 accent pairs + 2,245 dark-background pairs below visible-difference
(CIELAB), 4 accent pairs byte-identical. NCDEEngine.h's own recovered comment confirms the
presets were ALWAYS the operator's White Wolf/World of Darkness faction colour boards — so each
palette was redesigned as its faction's house color (web-researched canon: Brujah scarlet,
Ventrue sapphire, balefire green, Zeal-fire Avenger, Ananasi widow-silk per operator, etc.).
`compass7/lelan/kPresets.inc` colors rewritten — ids/names/order/dark flags UNTOUCHED (the
DO-NOT-trim rule stands); backup `kPresets.inc.prebak-20260706-irischroma90`.
**PROOF (on the exact shipped bytes):** 0 accent pairs under deltaE 10 (was 404 under 20);
0 dark-background pairs under deltaE 4.5 (was 2,245); 0 ink-contrast failures under 7:1.
Design tools kept at `~/my-project/files/iris-chroma-tools/` (gen_palettes.py authors the house
specs + enforces separation; palette_distinct.py is the prover — rerun it on kPresets.inc after
any future palette edit). Built: LaPivot sha `cec90cb8…`, magpie-talker sha `4f5c43e4…` (magpie
compiles the same NCDEEngine — this build SUPERSEDES the pending §1 magpie binaries `208edc74…`/
`eb49267c…` and contains those fixes too). Tree binary copies refreshed. **Deploy:**
```
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
sudo cp ~/ncde-staging/LaPivot/compass7/magpie/build/magpie-talker /usr/local/bin/magpie-talker.new && sudo mv /usr/local/bin/magpie-talker.new /usr/local/bin/magpie-talker
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml /usr/share/ncde/MagpieTalker.qml   # §1's pending QML rides along (gate already run, see §1)
rm -rf ~/.cache/LaPivot/qmlcache   # then relog
```
Test-group verify after relog: Settings → Filigree → Iris Chroma — switching palettes must now
visibly change the shell (different reds/greens/blues/golds AND different-tinted backgrounds);
the 5-dot preview rows on the cards should all look different per card. ALSO re-run the 8-point
frame retest from SESSION 75 (standing rule: any new WM binary re-tests all previously-fixed
frame behaviors — this binary only changes palette data, but the rule is the rule).

## 0.7 — SESSION 76 (2026-07-06): tiling refinements from the sighted test group — ✅ DEPLOYED
## + ACTIVE (QML parity clean + 21:17 relog, verified §0.10 — operator click-test still open)
Operator's words: "1. the first window when unmaxed should be small 2. the tiled windows that
stack? One should be able to grab them and reposition them in the stack." + Tiling Shell /
Snap Assist as the interaction reference (drag → hover a slot → stack responds → drop) +
"we just do eight at a time" (grid cap 8 confirmed, not unlimited stacking).
**Built (qmllint ✓ both, backups `*.prebak-20260706-tilerefine`):**
1. Lone unmaxed window = SMALL centered window (52%×56% of work area, min 420×300) — a 1-cell
   grid used to fill the work area, indistinguishable from max. 2+ windows: normal grid,
   unchanged (4 cols, 8 = 4+4).
2. Grab-and-reorder: TilingManager now keeps a user-arranged `tileOrder` (new tiles append);
   drag a tiled window by its titlebar → its slot is held open (`dragHoldWin` skipped in
   layout, no snap-back fight); when the cursor settles on another slot for 140ms the OTHER
   tiles shuffle live around it (the windows are the drop preview — no overlay; the settle
   timer throttles GLX relayout bursts, see §2-14); release commits the hovered slot, release
   off-grid snaps home. Closed-mid-drag windows self-clean (dragHoldWin reset in layout).
3. Amethyst refuses a 9th unmax while 8 are gridded (operator cap; Green a window out first).
Does NOT reopen open-max policy (open = maximized stands). NOTE: TilingManager's snapIndicator/
snapPreview children were found to be dead visuals (root Item is visible:false — children never
render); not touched, flagging for a future pass since snapPreview binds windowMgr.snapZone.
Extends [[project_ncde_tiling_open_max_policy]].

## 0.9 — SESSION 77 (2026-07-06) SWEEP, part 2: everything below BUILT + VERIFIED, all in the
## ONE deploy dump at the end of §0.8. FINAL binary sha `30a1bd3159f5394c…` (supersedes interim
## `cb7a327e…`/`cb667eff…` AND live `cec90cb8…`; contains Iris Chroma + Kith cursor + save-set
## + the weather-icon fix). Magpie §0.6/§1 deploys CONFIRMED ALREADY LIVE this session
## (magpie-talker `4f5c43e4` live, MagpieTalker.qml byte-identical) — magpie is NOT in this
## dump; WidgetData is lelan-only (grep-verified), no magpie rebuild needed.
-1. **IDLE/BLANK → SCREENSAVER (operator, late session: "blank screen is not saving user prefs..
   idle and blank screen should all trigger the screen saver") — FIXED, in FINAL binary
   `53c8829cfc18c19e…` (supersedes every sha below).** Verified first: power prefs DO save +
   apply (power.json written today with his 30s, xset q shows 1800s across the board — the
   persistence half was already working; if a control still displays wrong after this relog,
   report WHICH control). The real bugs were interplay: (a) X's native blanker ("prefer
   blanking: yes") fires on the `xset s` timer NCDE repurposes as the SUSPEND trigger — X
   blacked the screen itself, over/instead of the saver; now permanently `xset s noblank`
   (Settings.h applyPowerSettings — DPMS owns panel-off). (b) Nothing tied the blank timeout to
   the saver: blank < saver-timeout killed the panel before the saver appeared. Now the WM saver
   threshold = EARLIER of screensaverTimeout and the active power source's blank timeout
   (0 = never per knob), re-applied on settingsChanged + powerChanged + batteryChanged (main.cpp)
   — idle AND blank both end in Saisons Nocturnes; a DPMS-slept panel wakes INTO the saver.
   Backups `*.prebak-20260706-blanksaver`. Verify after relog: set saver 1 min / blank 5 min →
   saver at 1 min; set saver 0 / blank 1 min → saver at 1 min; screen never goes bare-black
   while the saver should be up. KNOWN MINOR left for next agent: PowerTab timeVals=[0,5,15,30]
   displays any other stored value (e.g. the 10/20 C++ defaults) as "5 minutes" (timeIdx
   fallback i<0→1) — display-only lie, values themselves save correctly.
0. **WEATHER ICONS WRONG (operator: thunderstorm shown, none till Thursday) — ROOT-CAUSED +
   FIXED + EMPIRICALLY PROVEN.** open-meteo emits WMO codes; the ENTIRE icon stack
   (mucha-weather.js, mucha-wx-icons.js, MuchaWeather.qml nightIcon map) is the operator's
   recovered YAHOO-code art (0..47) — under Yahoo semantics WMO 0-3 (clear→overcast) land in
   the thunder/tornado branches. Live API proof at fix time: current WMO code = 2 (partly
   cloudy) → rendered "thunder"; Thursday 07-09 daily code = 95 (the real storm) — the
   operator's report was exact. Fix: `wmoToYahooCode()` conversion ONCE at the source
   (WidgetData.h onWeather; full WMO group table in the code comment); all QML/JS consumers +
   night-swap untouched. Backup `WidgetData.h.prebak-20260706-wmoyahoo`. Verify after relog:
   weather widget shows partly-cloudy today; storm icon only when a storm is actually current.
   BONUS finding: api.open-meteo.com is REACHABLE from this machine again (real reply above) —
   §2.16's "host unreachable" is stale for this network.
1. **Glint per unmax (operator order this session):** sweep now plays EVERY time a maximized
   window unmaxes. Root cause of "only does it once": the 2s hide timer — quick max→unmax never
   flipped the *Revealed flags, so revealPulse had no transition. New `Intellihide.glintPulse`
   counter bumps on coveringCount→0; NCDEGlassSurface restarts the same one-shot sweep on it
   (identical epilepsy math, two flares/900ms). Intellihide/NCDEGlassSurface/TopPanel/
   BottomPanel/Dock, qmllint ✓ all 5, backups `*.prebak-20260706-glintperunmax`.
2. **B-F2 FIXED — WM crash no longer ejects the session:** ncde-x11-session now relaunches
   LaPivot on nonzero exit (clean logout = exit 0 via Launcher::logout), 3-rapid-crash guard.
3. **X save-set FIXED (B-F2's companion):** ChangeSaveSet INSERT on frame / DELETE on unframe in
   NCDEWindowManager.h — a WM crash now leaves clients alive for the respawned WM to re-manage
   (previously they were destroyed with their containers). Web-verified semantics. Backup
   `NCDEWindowManager.h.prebak-20260706-saveset`.
4. **B-S1 FIXED — reduce-motion now real desktop-wide:** all six NCDE controls (Toggle/Button/
   Slider/Field/Check/ProgressBar) gate their Behaviors on `animPolicy.instant ? 0 : N` (same
   pattern NCDECommand.qml already used). Indeterminate progress sweep intentionally kept
   (essential feedback per AnimPolicy's own "never stall essentials" contract). qmllint ✓ ×6,
   backups `*.prebak-20260706-reducemotion`.
5. **Touch targets FIXED:** NCDECheck/NCDESlider implicitHeight 22→26 (handlers live on the root
   item, so that IS the hit height; art unchanged). WCAG 2.5.8 ≥24px. qmllint ✓.
6. **Bluetooth AutoEnable pinned true** (etc/bluetooth/main.conf:365 uncommented; BlueZ default
   is version-dependent — pinned for arbitrary end-user installs).
7. **B-I2 FIXED — Firefox Arch branding neutralized:** distribution.ini now "Mozilla Firefox for
   NCDE", archlinux ids/partner keys removed. Backup `.prebak-20260706-ncdebrand`.
8. **picom/xfce-polkit/xembedsniproxy crash respawn:** ncde_respawn() in ncde-x11-session —
   nonzero-exit respawn, session-lifetime-bounded (kill -0 guard), 5-rapid-failure giveup. A
   picom crash = opaque glass (epilepsy-class hazard) — no longer permanent. bash -n ✓.
9. **VERDANTFOLIO — operator report confirmed: live runs an OLD BINARY, not the QML app.** Tree
   `usr/local/bin/verdantfolio` is the QML launcher (GiGi résumé atelier: qml6 Main.qml + python
   helper on :8078 + verdant-helper.service); live `/usr/local/bin/verdantfolio` is a stale
   compiled binary, and live is MISSING /usr/share/ncde/verdantfolio/, /usr/lib/ncde/
   verdantfolio/, and the user unit entirely. Verified shippable: Main.qml qmllint 0,
   verdant_server.py py_compile 0, professions.json valid JSON, port 8078 free live. Deploy in
   the dump below. (Punchlist §3.7's "operator to say what verdantfolio is" — answered.)
**Verified STALE this session (per §1c method, evidence in SESSION_HANDOFF 77):** GRUB theme
path (already ncde), Calamares removeuser (already `live`), ncde-recovery-vt (correctly
disabled), Lelan onNameOwnerChanged self-heal (full superset already wired — re-subscribes
NM/BlueZ/UPower/Sentinel/PackageKit + 10 more), §2.15 PackageKit GetUpdates (fully implemented:
subscribeToPackageKit + fetchPackageKitUpdates + UpdatesChanged consumer — STRUCK below).
**Verified CONFIRMED-OPEN, not fixed this session (real work, honest list):** B-S2 first-run
accessibility (needs operator design input); ~~B-S3 lampPulse drag-flicker~~ **CLOSED BY OPERATOR (2026-07-06, his words: "b-S3 is fine it
is fixed already")** — his own epilepsy-safety animation, his call is final; do NOT re-open,
re-measure, or "fix" it (the session-77 math report stands as history only); B-I1 ISO volume label
(ARCHCRAFT_202605 inherited by the xorriso replay — fix at next ISO build, add -V NCDE label);
B-F3 printers Add = raw CUPS web URL (needs Lelan discoverPrinters/addPrinter build);
247 hardcoded font.pixelSize literals (mechanical sweep, deferred); Timeshift .desktop still
user-visible (→ operator rm list §3, alongside now-inert /usr/share/icons/NCDE-Poseidon).

## 0.8 — SESSION 77 (2026-07-06): KITH CURSOR ON CLIENT WINDOWS — ✅ DEPLOYED + ACTIVE
## (verified session 78, §0.10: pid 311006 runs `53c8829c`, relog 21:17:30 — awaiting
## operator behavior confirmation only, verify list at the dump below)
Operator: cursor "is still Kith on desktop and default black on windows" + "kith cursor is the
default cursor theme.. unless it got renamed." He was right — it WAS renamed, effectively:
`ncde-x11-session` exported `XCURSOR_THEME=NCDE-Poseidon` (the retired pre-Kith gilt/ocean disk
theme, Jun 21) since before Kith existed. Root's Kith cursor (installAsRootCursor) only covers
windows that never call XDefineCursor; every real client resolves cursors via libXcursor against
XCURSOR_THEME — the name "Kith" was never resolvable, so clients fell to the core black arrow.
X11 has NO in-server way to retheme another client's unnamed cursor (web-verified: XFixes
ChangeCursorByName only matches SetCursorName-named cursors; core-font fallbacks are unnamed —
fixesproto + xserver xfixes/cursor.c). **Fix (Kith stays procedural — no disk theme ships):**
`CursorManager::writeXcursorTheme()` materializes the renderKith* art as a real Xcursor theme in
`$XDG_RUNTIME_DIR/ncde-cursors` (tmpfs, regenerated every login) — 14 canonical cursors × sizes
24/32/48/64 + 73 alias symlinks (X11 core, CSS, GTK2-hash names), hand-written Xcursor binary
format (spec-verified, little-endian, premultiplied ARGB). main.cpp writes it at startup +
qputenv's XCURSOR_THEME=Kith/SIZE=32/XCURSOR_PATH for every app LaPivot spawns;
ncde-x11-session exports the same three + imports them into systemd --user & the D-Bus
activation env (flatpak Steam class). **PROOF (no operator eyes needed): scaffolding harness
`compass7/lelan/test_cursor_theme.cpp` (NOT in CMakeLists) loads all 87 names × 4 sizes back
through the REAL libXcursor — 348/348 resolve, dims/hotspots exact (left_ptr@32 = 11,8, same
math as loadCursor), premultiplied-valid, Kith glass-blue confirmed in pixels. PASS, exit 0.**
`bash -n` ✓ on the session script. Backups `*.prebak-20260706-kithcursor` (CursorManager.h/.cpp,
main.cpp, ncde-x11-session). NCDE-Poseidon theme in tree+live is now INERT — candidate for the
operator rm list (§3), do not delete unasked.

**THE ONE DEPLOY DUMP — session 77, everything (§0.8 cursor + §0.9 items -1 to 9). FINAL binary
sha `53c8829cfc18c19e…` (== tree == build, verified; supersedes 30a1bd31/cb7a327e/cb667eff and
live cec90cb8). Run in order, then ONE relog:**
```
# LaPivot binary (Kith cursor writer + X save-set; contains live cec90cb8's Iris Chroma)
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
# session script (Kith env + WM crash respawn + helper respawn)
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/ncde-x11-session /usr/local/bin/ncde-x11-session
# shell QML (glint-per-unmax + reduce-motion controls + touch targets)
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/{Intellihide,NCDEGlassSurface,TopPanel,BottomPanel,Dock,NCDEToggle,NCDEButton,NCDESlider,NCDEField,NCDECheck,NCDEProgressBar}.qml /usr/share/ncde/
# bluetooth + firefox branding
sudo cp ~/ncde-staging/LaPivot/etc/bluetooth/main.conf /etc/bluetooth/main.conf
sudo cp ~/ncde-staging/LaPivot/usr/lib/firefox/distribution/distribution.ini /usr/lib/firefox/distribution/distribution.ini
# verdantfolio — the QML app live never got (old binary parked as .prebak, not overwritten)
sudo cp -p /usr/local/bin/verdantfolio /usr/local/bin/verdantfolio.prebak-oldbinary
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/verdantfolio /usr/local/bin/verdantfolio.new && sudo mv /usr/local/bin/verdantfolio.new /usr/local/bin/verdantfolio
sudo mkdir -p /usr/share/ncde/verdantfolio /usr/lib/ncde/verdantfolio
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/verdantfolio/Main.qml /usr/share/ncde/verdantfolio/
sudo cp ~/ncde-staging/LaPivot/usr/lib/ncde/verdantfolio/verdant_server.py ~/ncde-staging/LaPivot/usr/lib/ncde/verdantfolio/professions.json /usr/lib/ncde/verdantfolio/
sudo cp ~/ncde-staging/LaPivot/usr/lib/systemd/user/verdant-helper.service /usr/lib/systemd/user/verdant-helper.service
systemctl --user daemon-reload
rm -rf ~/.cache/LaPivot/qmlcache
# then relog
```
**Verify after relog, in this order:** (1) the 8-point frame retest from SESSION 75 (standing
rule — this binary changes WM code: save-set); (2) cursor over ANY app window — terminal text =
glass I-beam, links = glass hand, edges = glass double-arrows, all matching the desktop's Kith;
(3) max→unmax a window repeatedly — glint sweeps EVERY unmax; (4) Settings → Accessibility →
reduce motion ON → toggles/buttons snap instantly; (5) dock "Writer" opens the QML GiGi atelier
(not the old binary app); (6) session-71 §E items remain separately pending (SESSION_HANDOFF 71).

## 0. GATE — session-71 fixes ✅ DEPLOYED (verified session 78, §0.10 — fonts/.desktop/vesper/
## sentinel/picom/recovery all confirmed live) — operator VERIFY still open per item:
The 16 audit fixes of 2026-07-05 are live. After the (already-done) relog, verify per item —
especially: Ctrl+Alt+R opens Soundings; auto-login toggles OFF;
display scale/orientation survive a relog; Filigree section colours survive a relog; binnie
EMPTY asks first; Vesper pops on a real EICAR test in /tmp/vesper-watch and Block actually
moves the file into ~/.local/share/ncde-vesper/quarantine.
Also awaiting operator confirmation (already live, built earlier): Kith cursor everywhere +
the "1234" pager — code is running, needs his word it behaves.

**Magpie deploy (2026-07-06):** QML (MagpieTalker.qml, add-by-callsign + Nearby panel) and
MagpieTalkerManual.qml (channels/Foreign-Correspondents corrections) both confirmed deployed
(diffed byte-identical staging vs live). Binary has been rebuilt multiple times since — verify
current `sha256sum` of `/usr/local/bin/magpie-talker` against
`~/ncde-staging/LaPivot/compass7/magpie/build/magpie-talker` before assuming the latest lands;
don't trust this note's own claim, re-check. **[2026-07-17: that staging path is gone — see
top-of-file banner. There is nothing left to diff the live binary against; the live
`/usr/local/bin/magpie-talker` itself is the source of truth now.]**

**Glass glint physics rewrite (2026-07-06) — AWAITING DEPLOY (QML only, no build).** Operator asked
for the moving glint on the top panel / bottom panel / dock to be physically real (Beer-Lambert +
Fresnel). Rewrote the glint block in `NCDEGlassSurface.qml` (staging): the sweep now animates the
view ANGLE θ linearly and derives position (tan θ projection), brightness (true Schlick
R = R0+(1−R0)(1−cosθ)^5, R0=0.04 — this also fixed the old formula being INVERTED vs its own
comment: it flared mid-sweep instead of at grazing), and streak length (1/cosθ elongation, capped
2.5x); cross-profile is now Beer-Lambert e^−αd stops instead of a linear tent. Scope confirmed by
grep: revealPulse bound ONLY by TopPanel/BottomPanel/Dock — widgets get NO moving glint (operator
order 2026-07-06). Epilepsy-checked: two flares per 900ms one-shot sweep ≈1.1Hz (<3Hz), peak alpha
0.58 < old 0.73. qmllint exit 0. Backup `NCDEGlassSurface.qml.prebak-20260706-glintphysics`. Deploy:
```
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/NCDEGlassSurface.qml /usr/share/ncde/NCDEGlassSurface.qml
```
then relog (QML cached per-process). Verify: slide dock/panels in and out — glint should be dim
gliding mid-pane, flare + stretch at each end, hot-core/soft-haze streak shape.

**Intellihide redesigned to the operator's stated design (2026-07-06) — BUILT, AWAITING DEPLOY
(binary sha `940e7a68…` + Intellihide.qml).** Operator, same day: *"max is what makes everything
go away… that is the design"* — the shell hides only while a maximized window covers the desktop;
unmax to a small window, minimize everything to the bottom panel, or close everything must bring
dock+panels back automatically (he reported all three NOT doing so live: empty-looking desktop
stayed shell-less unless hovered). Root causes found by reading the code, not guessed:
(a) `Intellihide.qml` gated hides on raw `windowMgr.count`, which counts minimized rows;
(b) nothing re-evaluated on minimize/restore (no windowStateChanged consumer);
(c) `XCB_UNMAP_NOTIFY` is deliberately unhandled, so an app unmapping to tray without
DestroyNotify leaves a stale row keeping `count` > 0 forever — the close-all symptom.
The fix uses the WM's own existing desktop-covered criterion (`recomputeDesktopObscured()`,
maximized && !minimized — the widget-pump gate): new `Q_PROPERTY int coveringCount` =
maximized + non-minimized + REALLY-viewable rows (GetWindowAttributes map-state check, same
trust-the-server discipline as the FocusIn heal — self-heals the stale-tray-row case), recounted
deferred/coalesced (singleShot 0) off `windowStateChanged`+`countChanged` because
`unminimizeWindow()` fires windowStateChanged BEFORE its xcb_map calls (sync recount would race
the map; deferred query serializes behind the maps on the same X connection).
`Intellihide.qml`: `scheduleHide()` guard + `onCoveringCountChanged` now use coveringCount;
hover behavior unchanged. qmllint ✓. Known scope note: TILED windows are not maximized, so
tiling leaves the shell visible — flag to operator if that's wrong, don't silently widen.
Backups: `NCDEWindowManager.h.prebak-20260706-visiblecount`,
`Intellihide.qml.prebak-20260706-visiblecount`. Binary contains the §0.5 focus-heal fix
(supersedes `761676db`). **Deploy (one relog covers §0.5 + this + the glint above):**
```
sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/Intellihide.qml /usr/share/ncde/Intellihide.qml
sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/NCDEGlassSurface.qml /usr/share/ncde/NCDEGlassSurface.qml
```
Then relog and verify, in this order: the FOUR §0.5 frame behaviors (listed there), THEN
(5) maximize a window → shell hides after ~2s; (6) unmax it to a small window → dock+panels
return; (7) minimize everything to the bottom panel → they return; (8) close everything → they
return with no hover; (9) windows open full-screen without needing unmax→max; (10) glint reads
as dim mid-pane glide with end flares.

## 0.5 ✅ CLOSED (2026-07-06, session 76) — MotifFrame blank-window bug AND its same-day
## regression (freezes + unmax→max). **OPERATOR-CONFIRMED: "all window stacking and max are
## fixed."** The focus-heal fix rode in the live `ac7cafee…` binary (proof under §0.4).
## History below:

**Both session-72 causes in `NCDEWindowManager.h` were real and are the fix that shipped:**
(1) `XCB_FOCUS_IN` no longer activates minimized rows (a stray focus-revert after minimizing the
focused window was resurrecting an untouched minimized window — glass up, client unmapped);
(2) `onDestroy()` focus-next now walks back to the last NON-minimized entry. The
`activateWindow()` full-remap stays as a safety net.
- **Deploy + repro verified by agent 2026-07-06:** live `/usr/local/bin/LaPivot` == tree == build
  (sha `de1c91da…`), relog at 11:52, repro ran 11:52:56–11:53:02 — untouched window STAYED
  minimized, zero `registerFrameWindowQml GUARD HIT` lines, so the delegate-recreation hypothesis
  never fired; the two fixed causes were the live ones.
- **Log-path correction for future sessions:** the `[wmdebug]` qWarning lines landed in the
  SYSTEM JOURNAL (`journalctl -b | grep wmdebug`), NOT `~/ncde-debug.log` — Qt routed logging to
  journald despite ncde-x11-session's stderr redirect. Session 72's note about the log path was
  wrong in practice; diagnose WM logging via journalctl from now on.
- **Temp `[wmdebug]` diagnostics REMOVED (session 73, per this section's own close-out step):**
  all 7 C++ sites + main.qml's delegate `onVisibleChanged`. Rebuilt clean, sha `1623b248…`, tree
  binary copy refreshed, qmllint ✓. Backups: `*.prebak-20260706-wmdebugremoval`.
- Cleanup build `1623b248` was deployed (verified live == tree == build, 2026-07-06 afternoon);
  main.qml + MotifFrame.qml verified byte-identical staging↔live same day.

**🔴 REGRESSION (operator-reported 2026-07-06, same day): frames freezing client windows +
unmax→max no longer resizing clients. ROOT-CAUSED + FIXED + BUILT — AWAITING DEPLOY.**
- Cleanup build proven diagnostics-only by diffing its `.prebak-20260706-wmdebugremoval` backups —
  NOT the cause. The cause is the session-72 FocusIn guard itself (in `de1c91da` onward): it
  blocked activateWindow() for ALL minimized-flagged rows, which re-broke the 2026-07-02
  stale-flag fix documented in activateWindow()'s own comment — a window whose `minimized` flag
  goes stale-true while in use is tiered "hidden" and **Sentinel cgroup-freezes it** (the freeze;
  and a frozen client can't repaint at its new size on Green re-max — the "not resizing"). The
  guard also recorded refused windows into `m_lastFocusedWin`, making the dedup swallow the next
  legitimate FocusIn. Web-verified against real X11 docs (XSetInputFocus revert semantics;
  map_state VIEWABLE = window AND all ancestors mapped).
- **The fix (one change, XCB_FOCUS_IN case, `NCDEWindowManager.h`):** a minimized-flagged row now
  checks the client's REAL map state — not VIEWABLE (genuine minimize spray) → skip AND don't
  record m_lastFocusedWin; VIEWABLE (stale flag, the freeze case) → activateWindow() heals it
  (clears flag, Sentinel thaws, focuses). Blank-window protection fully retained — unviewable
  windows still never resurrect. Backup: `NCDEWindowManager.h.prebak-20260706-focusheal`.
- Built clean, sha `761676db…`, tree binary copy refreshed. QML untouched this fix.
- **SUPERSEDED BY sha `940e7a68…` (2026-07-06, later same day, still AWAITING DEPLOY):** the
  intellihide coveringCount feature (next section) was built on top; the focus-heal fix is fully
  contained in the new binary. Deploy commands + combined verify list in that section — the four
  frame behaviors below STILL must all be verified after the relog:
  (1) no client freezes during normal use; (2) unmax→max resizes the client content again;
  (3) the ORIGINAL blank-window repro (minimize 2+ → restore one → re-minimize it) — untouched
  window must STAY minimized; (4) close-a-window focus lands on a non-minimized window. If any
  fail, the fix is wrong — do not layer another fix on top; diff against the prebak chain.
- **Operator-reported same day, likely SAME root cause (verify after deploy, do not pre-fix):**
  windows opening not-full-screen until unmax→max; windows "jumping" showing the dock beside
  them, partially maximizing on hover. Both match the frozen-client-can't-repaint mechanism this
  fix closes (hover → focus → tier foreground → Sentinel thaw → deferred resize completes). If
  they persist on `940e7a68…`, root-cause fresh against the prebak chain — separate bug.
- May also bear on punchlist §2 item 13 (clipboard ~50% paste failure, race-shaped, never
  root-caused): the 07-02 incident notes stale-flag cgroup freezes "breaking clipboard paste
  system-wide" — same mechanism, intermittent. Re-observe after this deploys; do not claim closed.

## 1. ACTIVE (2026-07-05 → 2026-07-06, PAUSED for the item above): MAGPIE + FLUTTER

- **FLUTTER CALL BUTTON — REAL root cause found session 79 (the session-78 label fix was
  deployed and he STILL couldn't see it), FIXED, AWAITING DEPLOY (QML only).**
  Session-78's labeled pill WAS live when he looked (sudo cp 22:31:03; his launches 22:31:07 +
  22:31:43, journal-proven) — §1's own "different bug" clause fired. The REAL bug: the pill was
  `visible: !hub.activeIsChannel` and `MessageHub.h:380` defaults `m_activeIsChannel = true`,
  so at startup (nothing selected) the button is hidden and only ever appears AFTER opening a
  DM by clicking a contact — and his directs list is EMPTY (two-party proof open), so it could
  NEVER appear on his machine. Fixed session 79: the "✆ Video Call" pill is now ALWAYS in the
  thread header — gilt + tappable in an open idle DM (`flutterBtn.callable`), ink-toned but
  fully legible otherwise (no opacity fade); calling stays DM-only. ALSO fixed in the same
  file: the sidebar presence-dot cycler assigned read-only `hub.presence=` (live TypeError at
  22:31:20, line 310) → `hub.setPresence(...)` — it had never worked. qmllint ✓ +
  test_qml_load gate PASS on the tree file. Backup `.prebak-20260706-flutteralways`.
  Deploy (no build, no relog — magpie not running, next launch reads it):
  ```
  sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml /usr/share/ncde/MagpieTalker.qml
  ```
  Then launch Magpie: "✆ Video Call" must be visible top-right IMMEDIATELY, before selecting
  anything (ink-toned); it goes gilt inside an open DM. The presence dot by your own name now
  actually cycles when clicked.
- **Magpie's serverless "world band" (OpenDHT) — BUILT, PROVEN.** Callsign discovery/lookup,
  opt-in geo-presence, and off-LAN encrypted message delivery (DHT inbox store-and-forward) all
  built and functionally proven via real two-node tests (not just compiled). Real Lelan wiring
  added (networkOnline gating, geo-presence from real GPS) — which surfaced and closed a real
  architecture gap: `Lelan` gained an actuator/observer split so only the WM drives Sentinel, not
  every process that links it. **XMPP/Jabber (the agent-pushed detour from the operator's
  original ham-radio intent) REMOVED ENTIRELY** — not deprecated, not left dormant: every
  QXmpp/MUC class, property, method, and the WebEngineView registration UI is gone, confirmed zero
  linkage. Full detail: FLUTTER-PLAN.md session-71 updates 1-3.
- **Add-by-callsign UI — WIRED AND LIVE (2026-07-06).** The "Add contact" box's Enter key now
  calls `hub.addByCallsign()` (a real DHT lookup), with "Calling out on the world band…" /
  "No one answered" status text. Previously the box only hit the old dovecote-relay search —
  the DHT backend existed but nothing in the UI could trigger it. Fixed, deployed, confirmed live
  (operator: "it opens now").
- **Channels — REAL GROUP DELIVERY BUILT (2026-07-06), not a stub.** Channels had zero backing
  after the MUC removal (`sendMessage`'s channel branch just logged a warning and dropped the
  message, while still locally echoing it — looked sent, wasn't). Fixed for real: a channel is
  now "every peer currently on the wire" — `sendMessage`/`sendFile`/`react`'s channel branches
  fan out to all known peers over whichever transport reaches them (bonjour/dht/deliverTcp), and
  the receiving side auto-creates the local channel entry the first time it gets a message for
  one it hasn't joined (previously: message landed in history with nothing in the sidebar
  pointing at it). **Proven end-to-end twice** with two real headless MessageHub instances
  (Avahi/UDP discovery, real TCP delivery, on-disk history file as evidence) — not just compiled.
- **CRITICAL PRE-EXISTING BUG FOUND + FIXED (2026-07-06): `deliverTcp()` was serializing
  pretty-printed (multi-line) JSON while the receiver framed messages by splitting on `\n`, one
  compact JSON object per line.** This silently shredded EVERY multi-key message ever sent over
  native LAN TCP — both 1:1 DMs and channels — predating today's channel work entirely. This is
  the most likely reason two real Magpie users messaging each other over LAN never actually
  worked, even before today. Found by literally watching the byte stream arrive corrupted during
  the channel-fanout proof test; fixed with `QJsonDocument::Compact`; re-proven twice after the
  fix on a clean rebuild. Also added real error logging to `deliverTcp()` (previously any
  connection failure was silently swallowed — a dropped message looked identical to a sent one).
- **AVAHI AddService BUG — FIXED + BUILT, AWAITING DEPLOY (2026-07-06).** Three real, independently
  confirmed defects in `BonjourDiscovery.cpp`'s presence-publish path, found by actually exercising
  the real class against the running `avahi-daemon` (not just reading code), fixed one at a time
  with an empirical proof after each:
  1. `QByteArrayList` (the TXT record list) was never registered with D-Bus — fixed with
     `qDBusRegisterMetaType<QByteArrayList>()` in the constructor.
  2. `AddService`'s port arg was cast `uint(m_xmppPort)` — Avahi's real signature needs UInt16
     ('q'); the daemon rejected the whole call and logged "Error parsing EntryGroup::AddService
     message" (confirmed by reading avahi's own `dbus-entry-group.c`: on this parse failure it
     never sends an error reply, so the call just hangs unanswered — this is why it looked like
     nothing was happening).
  3. Even after fixing the cast, a bare `quint16` passed through `QDBusMessage::operator<<`
     silently promotes to `int` — confirmed by printing each argument's actual `QVariant`
     type-name; the fix is `QVariant::fromValue(m_xmppPort)`, which is the only form that
     preserves 'q' on the wire.
  4. Separately, `commitGroup()` never called `EntryGroup.Commit()` at all — `AddService` only
     *stages* a service; Avahi never announces anything until `Commit()` runs. Missing from the
     original Ghidra recovery. Added: `commitGroup()` now issues `Commit()` after a successful
     `AddService` reply, with real error logging on both calls (previously silently swallowed).
  **Proven end-to-end** via a throwaway harness (`compass7/magpie/test_bonjour.cpp`, NOT in
  CMakeLists, same pattern as `test_dht.cpp`) that runs the actual `BonjourDiscovery` class and
  confirms via `avahi-browse` that our real TXT record (screen name, jid, status, node) is visible
  on all interfaces (wlan0 IPv4/IPv6, lo), with zero `avahi-daemon` journal errors. Built into
  `~/ncde-staging/LaPivot/compass7/magpie/build/magpie-talker` (sha256
  `208edc7436a46474cf8111e4a94c9e05c72cea1378a36876fee2341080e27cc4`), **not yet copied to
  `/usr/local/bin/magpie-talker`** (still sha `36745733...`, the pre-fix binary) — deploy command
  handed to the operator this session. Foreign Correspondents (Pidgin/Kopete/macOS Messages
  discovering us via Bonjour) should now actually work once deployed — not yet re-verified against
  a real third-party client, only against `avahi-browse`.
- **NOT INDEPENDENTLY VERIFIED THIS SESSION:** the dovecote-relay protocol (`sendRelay`/
  `connectRelay`/`onRelayReadyRead`) may have the same newline-framing assumption as the native
  TCP path did — check whether `sendRelay()`'s `.toJson() + "\n"` (MessageHub.cpp ~line 1169)
  needs the same `QJsonDocument::Compact` fix, but ONLY after confirming what the actual relay
  server on the other end expects (it's an external service, not something in this tree — don't
  guess, find its real protocol first).
- **Manual updated ("On the Wire," Poe's voice)** to describe the World Band honestly instead of
  Jabber, and to stop overclaiming channels worked before they actually did. Deployed, confirmed
  live.
- **Browse-nearby QML UI — BUILT, AWAITING DEPLOY + OPERATOR CLICK-TEST (2026-07-06).** Added a
  "Nearby" panel (pin icon next to the DM header's "+", mirrors the existing add-contact panel's
  shape per the reference-existing-pattern rule): opted-out state explains the feature + a "Share
  my location" button (`hub.setShareLocation(true)`); opted-in state has a "Browse nearby" button
  (`hub.browseNearby()`) and lists `hub.nearbyResults` with an "Add" button per result
  (`hub.addByCallsign(modelData.callsign)` — geo records carry no connection info, so adding still
  goes through the normal world-band lookup, per `MessageHub.h`'s own comment on `browseNearby()`).
  All bindings verified against the real `MessageHub.h` Q_PROPERTY/Q_INVOKABLE signatures before
  writing the QML, not guessed. Verified: `qmllint` passes clean (sanity-checked the tool itself
  catches real syntax errors first); a real launch of the rebuilt `/usr/local/bin/magpie-talker`
  produced zero QML errors (only unrelated pre-existing `libinput Accel Speed` warnings). **Not yet
  click-tested** — GUI interaction is off-limits to the agent (no synthetic input), so the actual
  click-through (share location → browse → see a result → Add) needs the operator. QML edited only
  in staging (`~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml`); live
  `/usr/share/ncde/MagpieTalker.qml` is 105 diff lines behind — deploy command handed to operator.
  Group-chat is no longer a stub but has no persistent membership/roster
  (it's "whoever's currently online," not a joinable room with history for latecomers) — that's
  a real design constraint to know about, not a bug to silently fix bigger. Two throwaway proof
  harnesses (`compass7/magpie/test_channel_a.cpp` / `test_channel_b.cpp`, NOT in CMakeLists, same
  pattern as `test_dht.cpp`) are left in the tree as scaffolding/evidence — safe to delete once the
  next agent trusts this section, not required reading.

  **Flutter (native video chat) — STARTED 2026-07-06, real progress, one confirmed real bug still
  blocking it. §0.5 closed + operator green-light same day ("lets finish flutter") — ACTIVE again.**
  - **Tasks 1+2 (ringing signaling) — DONE, PROVEN, DEPLOYED.** `dovecote-relay` got a new targeted
    `call_signal` command (offer/answer/decline/hangup/media_offer/media_answer/media_candidate).
    Real pre-existing bug found+fixed along the way: `MessageHub::sendRelay()` sent multi-line JSON
    to a server that frames on a single `\n` — same bug class as the earlier `deliverTcp()` fix,
    just never caught on this leg before. `MessageHub` got a real `callState` state machine
    (idle/calling/ringing/active) with busy-guard and peer-offline cleanup. Proven via two real TCP
    clients through a real running `dovecote-relay` process — full offer→answer→hangup round trip.
  - **Task 3 (GStreamer `webrtcbin` media class) — IN PROGRESS, NOT working yet.** `FlutterCall.h/
    .cpp` built: real consent-gated (camera/mic never opens before explicit Allow) pipeline
    construction, SDP offer/answer via `create-offer`/`create-answer`/`set-local/remote-description`
    (signal signatures verified live against this system's actual installed `webrtcbin`, not
    assumed), ICE candidate exchange wired through the new `media_candidate` signal type, ringing→
    media handoff wired into `MessageHub`. Two real dependency gaps found and fixed by testing the
    actual pipeline (not just compiling): (a) `qml6glsink` wasn't installed at all — now is,
    vendored into `usr/lib/gstreamer-1.0/libgstqml6.so`; (b) `avenc_opus` looked like a fine
    substitute for the missing native `opusenc` but is NOT — its output isn't real RTP-payloadable
    `audio/x-opus` at all ("can't handle caps audio/x-opus"), confirmed by testing, not assumed;
    native `opusenc`/`opusdec` (`gst-plugins-base`) is now installed + vendored
    (`libgstopus.so`). `qml6glsink` also needs `glsinkbin` wrapping (raw link fails — confirmed) and
    reading its "widget"-holding sink back via the bin's own property, not `gst_bin_get_by_name`
    (confirmed: name-lookup can't see an element nested inside another element's property, only its
    own `gst_bin_add()`-ed children).
  - **✅ THE DEADLOCK IS FIXED + PROVEN (2026-07-06, session 73).** Root cause confirmed against
    GStreamer's own qt6 qmlsink example (tests/examples/qt6/qmlsink/main.cpp, fetched upstream):
    `qml6glsink` blocks its state change waiting for the scene graph's GL context, so a synchronous
    main-thread `gst_element_set_state(PLAYING)` (what `buildPipeline()` did) freezes the whole
    event loop. The upstream-verified fix: run PLAYING as a QRunnable on the QML window's render
    thread via `QQuickWindow::scheduleRenderJob(BeforeSynchronizingStage)` — now implemented as
    `FlutterCall::schedulePlaying()` (+ new honest "starting" mediaState; "active" only when the
    bus actually reports PLAYING reached). **Proven** by a rewritten harness
    (`compass7/magpie/test_flutter_pipeline.cpp`, in-tree scaffolding, NOT in CMakeLists): event
    loop alive 12/12 ticks, pipeline reached PLAYING, 178 real frames rendered through qml6glsink —
    PASS, exit 0; operator incidentally saw the SMPTE bars render live. Also fixed en route:
    (a) the QML side REQUIRES `GstGLQt6VideoItem` (import org.freedesktop.gstreamer.Qt6GLVideoItem
    1.0) — FlutterCall.h's old "any plain Item works" note was WRONG, corrected; (b) magpie
    main.cpp now does gst_init + a throwaway qml6glsink BEFORE the QML engine loads (upstream's own
    trick) so that import resolves; (c) remote sink's "widget" now set BEFORE its state comes up.
    HARNESS SAFETY RULE (operator-reported): never leave a Window on Qt's default WHITE background —
    harness + call UI are black-backed; treat white flashes as the terminal-white-screen hazard class.
  - **Call UI BUILT in MagpieTalker.qml (2026-07-06, session 73), per FLUTTER-PLAN §1:** ✆ header
    button (DM-only, next to Nudge, same pattern) → whole-window transform to a black full-viewport
    call view ("like cheese"): full-frame remote GstGLQt6VideoItem, postage-stamp local preview,
    visible Hang Up reversing the transform; incoming-ring overlay (Answer/Decline →
    hub.acceptCall/declineCall); consent gate overlay (camera/mic never open before Allow →
    hub.setMediaConsent; Deny also ends the call). Video items are PERMANENT scene members (never
    Loader-managed — FlutterCall holds raw QQuickItem pointers). qmllint ✓ (0 exit, the gst import
    resolves); real launch of the rebuilt binary: 12s, ZERO QML errors. Binary sha `8bd3b12f…`,
    tree copy refreshed. **AWAITING DEPLOY + operator click-test** (agent cannot click — the full
    two-party call needs a second Magpie node; single-machine consent→camera-preview test is
    possible here, /dev/video0 present).
  - **✅ GREEN-SCREEN BACKGROUND REPLACEMENT — BUILT + PIXEL-PROVEN (2026-07-06, session 74).
    🔴 AWAITING DEPLOY (binary + QML, commands below).** Operator supplied 6 backdrop images —
    deployed live at `/usr/share/ncde/flutter-backgrounds/{1..6}.png` (1672x941 RGB, confirmed).
    The build, exactly the planned shape: camera → videoscale to fixed 1280x720 (works on ANY
    webcam, nothing dev-box-specific) → `alpha` (the keyer) → `compositor background=black` over a
    background layer fed by `appsrc → imagefreeze allow-replace=true` → existing tee. Backdrop
    swaps LIVE mid-call by pushing a new frozen frame — no pipeline surgery; keyer method/target-*
    are runtime-writable (gst-inspect-verified). API stays one-hub (FLUTTER-PLAN §4.4):
    `hub.videoBackground`/`videoKeyColor` properties, `hub.videoBackgrounds()`/
    `setVideoBackground()`/`setVideoKeyColor()`; persisted to `~/.config/ncde/magpie/flutter.json`,
    applied automatically on the next call when chosen between calls. QML: "Backdrop" button in
    the call view → thumbnail picker (None + the 6 scenes) + sheet-color swatches (green/blue
    presets; backend takes any color). **REAL BUG FOUND EN ROUTE, empirically:**
    `prefer-passthrough=true` on the keyer silently BREAKS runtime keying (it negotiates caps with
    no alpha channel; flipping method mid-stream then does nothing) — shipped without it.
    **Proof:** `compass7/magpie/test_greenscreen.cpp` (in-tree scaffolding, NOT in CMakeLists,
    same pattern as test_flutter_pipeline.cpp) runs the exact shipped pipeline shape with a
    pure-green videotestsrc as the camera and reads output pixels in code — 4/4 PASS: keying off
    = camera; keying on = backdrop 1.png pixel-exact; live swap to 2.png pixel-exact; off again =
    camera. No display, no camera, no operator eyes needed. Also: qmllint ✓ (exit 0); rebuilt
    binary ran 8s against live QML with ZERO errors; sha `eb49267c…`, tree copy refreshed
    (`usr/local/bin/magpie-talker`). Backups: `*.prebak-20260706-greenscreen` (FlutterCall.h/.cpp,
    MessageHub.h/.cpp, CMakeLists.txt, MagpieTalker.qml). CMake note: `gstreamer-app-1.0` added
    for appsrc. **Deploy:**
    ```
    sudo cp ~/ncde-staging/LaPivot/compass7/magpie/build/magpie-talker /usr/local/bin/magpie-talker.new && sudo mv /usr/local/bin/magpie-talker.new /usr/local/bin/magpie-talker
    sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml /usr/share/ncde/MagpieTalker.qml
    ```
    Then operator click-test in a call: Backdrop button → pick a scene → own preview swaps live
    (needs the real green sheet to look right; without one the keyer eats whatever is
    green-ish on camera). Zoom's no-screen AI segmentation = explicitly separate, heavier, later.
    **POST-DEPLOY REGRESSION, SAME DAY — MAGPIE WOULDN'T OPEN. ROOT-CAUSED + FIXED (QML redeploy
    pending):** live error (journald, NOT the app's stderr — same lesson as the WM):
    `MagpieTalker.qml:1772: Invalid property assignment: int expected` = `font.pixelSize: 12.5`
    — **session 73's ring/consent overlay code, not the session-74 picker.** It shipped broken to
    the tree and nobody could see it: the binary hardcodes `/usr/share/ncde/MagpieTalker.qml`, so
    every pre-deploy "launched the rebuilt binary, zero QML errors" check (sessions 73 AND 74)
    silently exercised the OLD live QML. qmllint AND qmlcachegen both PASS the broken file —
    neither is a gate for this class. **New real gate:** `compass7/magpie/test_qml_load.cpp`
    (scaffolding harness) loads the TREE file in a real offscreen QQmlApplicationEngine with the
    gst qml6 preload — proven to FAIL on the broken backup and PASS on the fixed file. Fix: the
    two `12.5` → `13` (rounded UP — accessibility). **Run this gate on the tree QML before every
    future MagpieTalker.qml deploy.**
  - GStreamer webrtc API is intentionally unstable upstream (`gst-plugins-bad`) — `FlutterCall.h`
    already defines `GST_USE_UNSTABLE_API` to silence the expected compiler warning, not suppressing
    a real one.

## 1b. Merged from commercial.md (a large prior multi-agent audit — spot-checked 2026-07-05, see
## its own banner). CONFIRMED STALE items already removed from its list below; these are what
## survived verification or weren't re-checked yet.

**Confirmed STILL OPEN (verified against the current tree, 2026-07-05):**
1. **B-S1 — reduce-motion does nothing desktop-wide.** No QML control (`NCDEToggle`/`NCDEButton`/
   `NCDESlider`/`NCDEField`/`NCDECheck`/`NCDEProgressBar`) consumes `animPolicy.instant`/
   `reduceMotion` — confirmed via grep, zero hits. The engine-level toggle works
   (AccessibilityTab→Lelan); the widgets just never check it. Real accessibility/epilepsy item.
2. **B-F2 — a WM crash ejects the whole session, no respawn.** Confirmed by reading
   `usr/local/bin/ncde-x11-session` directly: LaPivot runs once in the foreground, exit code
   logged, then the script just falls through — no loop distinguishing a clean logout from a
   crash, no auto-respawn. Any segfault = dropped to login, work lost.

## 1c. NEXT AGENT — commercial.md verification queue (do these IN THIS ORDER, one at a time)

**Method for every item below** (this is not optional — three of commercial.md's own "blockers"
were already stale on the 2026-07-05 pass, so its file:line citations are a lead, not a fact):
1. Open the EXACT file:line commercial.md cites. **[2026-07-17: `~/ncde-staging/LaPivot/` no
   longer exists — dev machine gone, source lost, see top-of-file banner.]** Instead: check the
   live system (`/usr/local/bin/LaPivot` via nm/Ghidra, or the QML directly under
   `/usr/share/ncde/`) and cross-check `~/ncde-wm-rebuild/` for any already-reconstructed class
   covering that file (see `docs/lapivot-rebuild.md` for status).
2. Confirm the described code/behavior is still there (architecture can have moved since the
   citation was written — B-F4's whole premise, a monolithic Sentinel binary, no longer exists).
3. If confirmed real: fix it following CLAUDE.md's Pre-Apply Audit Rule (read→backup→one change→
   diff→rebuild→verify), same discipline as every fix this session.
4. If stale/already-fixed/wrong: mark it `[x] ~~struck~~` in `commercial.md` with the evidence
   (file:line + what you actually found), one line, matching the style of the B-F1/B-F4/B-F5
   entries already there. Mirror the one-line outcome into this punchlist section.
5. Never mark an item done from reading commercial.md alone — only from reading the tree.

**Queue, in the doc's own priority order:**

1. **B-S2** — first-run accessibility. Check: does anything launch on first login besides the
   normal desktop? (grep `ncde-x11-session` for a first-run flag-file check; grep
   AccessibilityTab.qml for the "Sample Ag" preview commercial.md says already exists.)
2. ~~**B-S3** — lampPulse flash rate.~~ **CLOSED BY OPERATOR (session 77, 2026-07-06: "b-S3 is
   fine it is fixed already").** The math was computed and reported (SESSION_HANDOFF 77); the
   operator — who built this animation for his own epilepsy safety — ruled it fine/already
   handled. Standing: do NOT re-open, re-measure, or touch the lampPulse/candle-flicker
   animation (see memory `project_ncde_motif_glow_candle_flicker`).
3. **B-I1** — ISO volume label. Check `NCDE-BUILD-COMMANDS.md`'s cited lines AND the real
   `profiledef.sh`/build script in the tree for `ARCHCRAFT_202605` — commercial.md's own citation
   is to a DOC, not the actual build script; find and check the real one.
4. **B-I2** — Firefox branding. Check whether `usr/lib/firefox/distribution/distribution.ini`
   even exists in the current tree (Firefox packaging may have changed since this was written).
5. **B-F3** — printer Add flow. Check `PrintersTab.qml`'s cited lines for the raw
   `Qt.openUrlExternally("http://localhost:631/admin")` call; confirm no native flow was built
   since (unlikely, but check `Lelan.h` for a `discoverPrinters()`-shaped method first).
6. **Quick wins** — X save-set (`NCDEWindowManager.h` cited lines), 204 hardcoded
   `font.pixelSize` (spot-check a handful, don't assume the count is still accurate),
   touch-target sizes, Bluetooth `AutoEnable`, picom/polkit respawn loop in
   `usr/local/bin/ncde-x11-session`, stale Timeshift `.desktop`, Calamares `removeuser` module,
   GRUB theme path, `ncde-recovery-vt.service` enablement (**note: session 71 already found this
   masked/handled correctly for networkd-class concerns — check this doesn't overlap/contradict**).
7. **High-impact** — update notifications, pre-update snapshot hook, Bluetooth pairing agent,
   WPA-Enterprise, **Lelan self-heal `onNameOwnerChanged` re-subscribe set** (cross-check against
   this session's own full Sentinel/Lelan audit — task #6 found the chain fully wired with no
   blockers, so this item may already be stale too, same pattern as B-F5), Secure Boot GRUB
   signing, license browser.
8. **Strategic/post-1.0** — atomic update+rollback, update repo, scanners, reproducible squashfs,
   **retire stale LLM kickass-guard** (near-certainly ALREADY DONE — session 69 confirmed
   KickassGuard C++ removed as an abandoned Ollama/ChromaDB duplicate, and `vesper.md` was
   restructured session 69 to the non-LLM design; verify then strike this one first, it's
   probably a two-minute close), OEM mode, GPL source-offer note.

Do not skip to fixing items before verifying them — that's exactly how commercial.md accumulated
stale entries in the first place (agents acted on claims instead of the tree).

## 2. Remaining build items (from the session-71 audit, §G — real work, honest list)
1. ~~**FonderieTab is dead**~~ **BUILT + PROVEN session 78 (2026-07-06), in binary `d7db2d72…`,
   AWAITING the §0.10 part-2 deploy** — full detail §0.10-I (FontManager.h, PackageKit install
   path, 7/7 harness PASS incl. family-name honesty; install leg needs an ISO/VM pass since the
   dev host doesn't run PackageKit).
2. ~~**applyGtkTheme() regression**~~ **RESTORED + PROVEN session 80 (2026-07-07), AWAITING
   THE §2.2 DEPLOY DUMP BELOW.** All three recovered functions translated back into the current
   `NCDEEngine.h` from the original binary's DWARF decompile (magpie-rebuild NCDEEngine.c:
   `applyGtkTheme` @001cb9f8, `applyGtkAccent` @001cdda0, `seedGtkUserConfig` @001cab6c), wired
   at the SAME five call sites the original had: setDarkMode, setDarkModeLock, applyPreset,
   sampleWallpaper, loadTheme (= the "once at login" leg — native-app mains call loadTheme at
   startup — AND the live-resync leg via the active-theme.json watcher). This is the tail of the
   ONE NCDEKit pipeline (operator 2026-07-07: "this works with NCDEkit etc"): Filigree → Iris
   Chroma → NCDEKit → NCDEEngine → GTK2/3/4 + Chromium. **CORRECTION en route: GTK2 sync WAS in
   the recovered code** (the decompile writes a full `~/.gtkrc-2.0` — APP-FIXES's "no GTK2
   anywhere" claim was stale, now struck there); what needed building from scratch was only the
   static theme asset: NEW `usr/share/themes/NCDE/gtk-2.0/gtkrc` (dark bridge palette + skel
   default accent #6774bd; the engine's live `~/.gtkrc-2.0` rewrite overrides it per-user).
   **PROOF: harness `compass7/lelan/test_gtk_theme.cpp` (scaffolding, NOT in CMakeLists) ran the
   REAL engine in an isolated HOME — 16/16 PASS incl. a BYTE-MATCH of the generated ~/.gtkrc-2.0
   against the file the ORIGINAL binary wrote on this host (accent-normalized), settings.ini
   replace-not-append, GTK4 import swap both directions, and end-to-end applyPreset()/
   setDarkMode() reaching the GTK files with no extra calls; gate proven to FAIL on a corrupted
   oracle.**
   **PART 2 (same session, operator: "a gtk3-4 theme was made for NCDE and it was to be used by
   all GTK apps so they appear native"): the made GTK3/4 theme's styling files were LOST — now
   REBUILT + PROVEN IN REAL GTK.** Search was exhaustive before declaring loss: tree, live
   (`~/.themes/NCDE/gtk-3.0` has only gtk.css+_accent.css; no `/usr/share/themes/NCDE` ever on
   this host), every zip in Downloads/files, ~/ncde-ISO, no snapshots, and the old ncde-wm
   binary (its only hits are the writers' format strings — the theme files were on-disk assets).
   Rebuilt faithfully to the recovered skeleton (filenames from seedGtkUserConfig + the gtk.css
   writer; colors = the binary's canonical bridge palettes): `usr/share/themes/NCDE/gtk-3.0/
   {_palette-dark,_palette-light,_rules}.css` (+ gtk.css/_accent.css defaults) and
   `usr/share/themes/NCDE/gtk-4.0/{gtk.css,_palette-dark,_palette-light,_accent}.css`; the same
   three GTK3 files completed into all three shipped `.themes/NCDE/gtk-3.0` locations
   (etc/skel, home/live, var/lib/ncde-portal — their gtk.css imports had been DANGLING).
   Mechanism (empirically established, not guessed): palettes `@import` GTK3's EMBEDDED Adwaita
   resource (`resource:///org/gtk/libgtk/theme/Adwaita/gtk-contained[-dark].css` — verified
   present + parseable on this exact GTK3) so every widget stays fully styled, then define the
   NCDE named colors; **Adwaita bakes literal hexes into its rules (verified: zero named-color
   references in the compiled css), so the shared `_rules.css` is what re-grounds the widget
   surfaces — which is exactly why the original structure was per-mode palettes + ONE shared
   rules file.** GTK4 palettes are DEFINES-ONLY, deliberately: the seed copies gtk.css into
   `~/.config/gtk-4.0/` where GTK4 stacks it on EVERY app incl. libadwaita — importing a full
   theme there would corrupt libadwaita apps (flagged for operator; plain-GTK4 apps ride
   settings.ini prefer-dark + color-scheme instead). **PROOF (real GTK, offscreen, tree files):
   GTK3 6/6 PASS — full import chain parses AND computed widget colors read back as NCDE
   (window #263033, entry base #1E2527, selection = accent #6774BD, light variants) — plus GTK4
   chain parse PASS.** Harnesses in scratchpad (session-throwaway; the C++ harness
   `test_gtk_theme.cpp` stays in-tree).
   Honest remainders: LaPivot itself never calls loadTheme at startup (pre-existing, native
   apps do — flagged, not silently widened); visual confirmation in a real GTK app on the live
   desktop needs operator eyes; after deploy+relog the engine's seedGtkUserConfig auto-copies
   the palettes/rules into `~/.themes/NCDE/gtk-3.0` (never clobbers existing files).
   **PART 3 (session 81, 2026-07-07): THE DESIGNER'S REAL THEME KIT LANDED — supersedes part 2's
   agent reconstruction.** Operator delivered `qt canvas music player for linux (4).zip`
   (archived: `~/my-project/files/gtk-theme-designer-kit.zip`): complete NCDEgtk GTK2/3/4 theme
   — full 334-line `_rules.css` (every widget, named-colors only, NO Adwaita import per operator
   order in gtk-designer-answers.md Q4), palettes with tooltip/warning/error/success names, GTK4
   defines + libadwaita accent compat, preview HTML. **All 25 tree files replaced byte-identical**
   (usr/share/themes/NCDE ×10 + etc/skel + home/live + var/lib/ncde-portal .themes ×5 each;
   backups `*.prebak-20260707-designerkit`). Live `~/.themes/NCDE/gtk-3.0` had ALREADY seeded the
   old agent palettes (engine ran at 11:47+) — refreshed in place by agent (user-owned, no sudo;
   same backup suffix), gtk.css/_accent.css left to the engine. **PROOF on the tree files, real
   GTK 3.24.52: dark 15/15 + light 15/15 (every named color resolves to the designer palette AND
   real widget computed colors re-ground: window/entry/menu/button-shade); GTK4 22.4 chain parses
   0 errors both modes; negative control (corrupted palette) FAILS the harness as required.**
   Harnesses: scratchpad gtk3_proof.py / gtk4_proof.py (session-throwaway). gtk.md corrected
   (Adwaita mechanism struck, banner added). Engine untouched — same binaries. **Deploy: the
   theme-file lines of the §2.2 dump above, re-run (files changed, paths identical); no relog
   needed (GTK reads at app launch; engine reseeds users on next apply).**
   Backup `NCDEEngine.h.prebak-20260707-gtkbridge`. Rebuilt all four NCDEEngine consumers:
   **LaPivot `b9d0bf1f…` (SUPERSEDES live d7db2d72 — same tree + bridge), magpie-talker
   `20664ade…` (supersedes live 4f5c43e4), binnie `fd1dd547…` / orchidee `295198d7…` (SUPERSEDE
   §2.6's pending 7ebc56b1/00cca01a — contain those recoveries + bridge)**; tree binary copies
   refreshed. **THE §2.2 DEPLOY DUMP (run §2.6's QML lines too if not yet done — its binaries
   are replaced by these):**
   ```
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/LaPivot /usr/local/bin/LaPivot.new && sudo mv /usr/local/bin/LaPivot.new /usr/local/bin/LaPivot
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/magpie-talker /usr/local/bin/magpie-talker.new && sudo mv /usr/local/bin/magpie-talker.new /usr/local/bin/magpie-talker
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/binnie /usr/local/bin/binnie.new && sudo mv /usr/local/bin/binnie.new /usr/local/bin/binnie
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/orchidee /usr/local/bin/orchidee.new && sudo mv /usr/local/bin/orchidee.new /usr/local/bin/orchidee
   sudo mkdir -p /usr/share/themes/NCDE/gtk-2.0 /usr/share/themes/NCDE/gtk-3.0 /usr/share/themes/NCDE/gtk-4.0
   sudo cp ~/ncde-staging/LaPivot/usr/share/themes/NCDE/gtk-2.0/gtkrc /usr/share/themes/NCDE/gtk-2.0/gtkrc
   sudo cp ~/ncde-staging/LaPivot/usr/share/themes/NCDE/gtk-3.0/{gtk.css,_accent.css,_palette-dark.css,_palette-light.css,_rules.css} /usr/share/themes/NCDE/gtk-3.0/
   sudo cp ~/ncde-staging/LaPivot/usr/share/themes/NCDE/gtk-4.0/{gtk.css,_accent.css,_palette-dark.css,_palette-light.css} /usr/share/themes/NCDE/gtk-4.0/
   sudo mkdir -p /etc/skel/.themes/NCDE/gtk-3.0 /var/lib/ncde-portal/.themes/NCDE/gtk-3.0
   sudo cp ~/ncde-staging/LaPivot/etc/skel/.themes/NCDE/gtk-3.0/{gtk.css,_accent.css,_palette-dark.css,_palette-light.css,_rules.css} /etc/skel/.themes/NCDE/gtk-3.0/
   sudo cp ~/ncde-staging/LaPivot/var/lib/ncde-portal/.themes/NCDE/gtk-3.0/{gtk.css,_accent.css,_palette-dark.css,_palette-light.css,_rules.css} /var/lib/ncde-portal/.themes/NCDE/gtk-3.0/
   # (corrected 2026-07-07: live /etc/skel/.themes never existed — the shipped theme was
   # tree-only; /var/lib/ncde-portal contents are root-only-readable, full set copied)
   rm -rf ~/.cache/LaPivot/qmlcache   # then ONE relog
   ```
   **Verify after relog:** (1) the standing 8-point frame retest (new WM binary, rule is the
   rule — this build changes NO WM code, only the shared engine); (2) Filigree → pick a
   different Iris Chroma palette → `cat ~/.gtkrc-2.0` shows the new accent hex,
   `gsettings get org.gnome.desktop.interface gtk-theme` says 'NCDE', and
   `ls ~/.themes/NCDE/gtk-3.0/` now includes the seeded _palette-*/_rules files; (3) open a
   GTK3 app (Timeshift's window is the one user-visible GTK3 app on the rm-list, or any GTK3
   tool) → it renders in NCDE's ground/ink with the accent on selections — "appears native";
   (4) toggle dark/light → `~/.config/gtk-4.0/settings.ini` prefer-dark flips, the GTK3 app
   follows on next launch; (5) Chromium follows dark/light (the sync script runs on every
   theme change).
3. **PowerTab lid/power-button enforcement** — values persist but nothing reads them; needs a
   logind Inhibit lock held for the session (deliberate careful task — hardware behavior).
4. **Recovery backend C++ source absent** — ncde-recovery binary ships but cannot be rebuilt
   from the tree (no RestoreBackend.cpp/main.cpp/CMakeLists). Ghidra-recover (standing
   permission). Also: ncde-recovery icon asset + Calamares show.qml Ctrl+Alt+R slide (spec TODOs).
5. ~~**org.freedesktop.ScreenSaver D-Bus inhibit provider**~~ **BUILT + PROVEN session 78
   (2026-07-06), in binary `caed0d3a…`, AWAITING the §0.10 deploy:** new
   `IdleInhibitService.h` (registered in main.cpp) owns org.freedesktop.ScreenSaver on the
   session bus, serves Inhibit(app,reason)→cookie / UnInhibit(cookie) on BOTH the spec path
   /org/freedesktop/ScreenSaver AND the legacy /ScreenSaver most players call
   (spec: specifications.freedesktop.org/idle-inhibit/0.1/), and drops a hold when its owner
   disconnects from the bus (QDBusServiceWatcher — browsers crash/quit without UnInhibit).
   Mechanism: while ≥1 cookie held, ForceScreenSaver(Reset) pokes the X idle counter every 30s —
   the exact mechanism mpv already proves works here, so saver launch + DPMS blank + suspend
   timer are ALL uniformly held off with zero WM coupling. **PROOF: scaffolding harness
   `compass7/lelan/test_idle_inhibit.cpp` (NOT in CMakeLists) ran the real service on the real
   session bus against real external python3-dbus client processes — 5/5 PASS exit 0 (legacy
   path held; bus-disconnect dropped the hold; spec path held; UnInhibit released while the
   client stayed connected).** Gotcha for future D-Bus services: without
   `Q_CLASSINFO("D-Bus Interface", …)` Qt exports slots under an auto-generated local interface
   name and every caller gets UnknownInterface — found empirically, fixed. Verify after deploy:
   play a video in Firefox → saver/blank must NOT fire; close the tab → idle behavior returns.
6b. **SESSION 81 (2026-07-07): Orchidée Ctrl+H + root-folder protection — BUILT + PROVEN,
   AWAITING DEPLOY (operator confirmed both needed: "Orchidee needs ctrl H and root folder
   protection").** (a) Ctrl+H (Thunar model): new `app.showHidden` + Shortcut in OrchideeApp.qml,
   wired through all 3 views + the sidebar tree (backend `entries(path,showHidden)` always
   supported it — no QML ever passed true); Glia announces both states in character.
   (b) Root protection: new `BinnieTrash::protectedPath()` (family-wide — "/",$HOME, first-level
   system dirs, mount points) guards `BinnieTrash::trash()`; `OrchideeFiles::isProtected()`
   exposed to QML + guards its `trash()`/`moveTo()` (also: own-subtree dest, unwritable dest);
   Glia refuses protected tosses in character (new forbidden quips) at leaf-TOSS, bin-view drop,
   and sidebar-bin drop. **PROOF: new scaffolding harness `compass7/orchidee/test_root_guard.cpp`
   22/22 PASS (truth table incl. every real mount point, behavior incl. trash($HOME) refused,
   normal toss/move still work); the 44/44 binnie harness re-run on the GUARDED class: ALL PASS;
   qmllint ×5 exit 0; real-engine load gate PASS on tree OrchideeApp.qml. Binaries binnie
   `f3789f6e…` / orchidee `df17743a…` — SUPERSEDE §2.2's fd1dd547/295198d7 (same tree: GTK bridge
   + recoveries + guards), tree copies refreshed.** Backups `*.prebak-20260707-rootguard` (C++),
   `*.prebak-20260707-ctrlh-rootguard` (QML ×5). Deploy in the ONE session-81 dump (SESSION_HANDOFF 81).
6. ~~**binnie/orchidee backend C++ recovery**~~ **DONE session 79 (2026-07-06, operator order:
   "the only thing keeping us from making the ISO") — BUILT + PROVEN. §2.6 DEPLOY CONFIRMED
   LANDED (verified session 80, 2026-07-07: live binnie=7ebc56b1/orchidee=00cca01a shas matched
   + /usr/share/ncde parity clean incl. MagpieTalker.qml) — those two binaries are now
   SUPERSEDED by §2.2's GTK-bridge rebuilds (fd1dd547/295198d7, same recoveries + bridge);
   operator click-test of the §2.6 verify list still open.** Both apps' full C++ recovered from the Jul-1 Ghidra decompiles (both live binaries
   are unstripped with debug_info) into REAL buildable source: `compass7/binnie/`
   (BinnieTrash.h + main.cpp + CMakeLists, binary `7ebc56b1…`) and `compass7/orchidee/`
   (OrchideeFiles.h + main.cpp + CMakeLists, binary `00cca01a…`), tree binary copies refreshed
   (old shipped binaries parked `.prebak-20260706-recovery`). **CHARACTERS PRESERVED (operator:
   "the animations are what sell the whole house ecosystem"):** Binnie's 14 cel strips +
   Glia's 6 were extracted from the shipped binaries' qt_resource_data and vendored into the
   source (`resources/` + .qrc, AUTORCC) — PROVEN byte-identical by re-extracting from the
   rebuilt binaries and diffing. **BINNIE REWIND PROVEN WORKING — 44/44 harness PASS**
   (`compass7/binnie/test_binnie_trash.cpp`, isolated XDG_DATA_HOME: toss→hold→ring math→
   restore files AND dirs→24h expiry purge→unique names→emptyAll; also proves trash(nonexistent)
   returns false — the pre-session-71 demo-TOSS button "tossed" invented /tmp paths while the
   QML played the animation anyway, which is exactly the operator's "gone immediately, no way
   to restore" experience; the backend was always correct, session 71's real picker closed the
   illusion). **"HIS ANIMATIONS ARE GONE" ROOT-CAUSED + FIXED (operator report tonight):** the
   Jun-9 defensive rewrite of `BinnieCanvas.qml` never STARTED the idle loop — nothing played
   "idle" at load and finished actions stopped dead ("static rest"), so Binnie stood frozen
   while GliaCanvas kept its `loop:true` idle. Fixed: `Component.onCompleted: play("idle")` +
   action-finished falls back into the idle loop; every safeInterval freeze guard untouched.
   Backup `.prebak-20260706-idleloop`. **ORCHIDÉE DRAG-AND-DROP BUILT (operator: "you need to
   be able to drag files" — Thunar model):** every row/tile in all 3 views drags (parchment
   ghost pill follows the cursor); folder rows/tiles, every sidebar place, and every tree
   folder accept drops → the real `orchidee.moveTo()` (was compiled in the binary, never wired
   in QML); guards refuse self/same-dir/into-own-child drops. **THUNAR-STYLE BIN BUILT
   (operator: "think how Thunar and Thunar trash work" + the lore: Binnie is Glia's FATHER —
   one family, one bin):** new "Bin (N)" place in the sidebar — TAP browses Binnie's bin
   in-place (hours-left pill per item, in-place REWIND restore with Glia's rescue quips,
   ✕ delete-forever, "Visit Binnie" opens Papa's app), DROP a dragged file on it to toss
   (shared freedesktop ~/.local/share/Trash — both apps read the same store, already proven).
   Gates: qmllint PASS ×5 + real-engine load gate PASS on the tree OrchideeApp/BinnieApp.
   Backups `*.prebak-20260706-dndbin` ×5. NOT operator-click-tested (agent cannot drag).
   **THE §2.6 DEPLOY DUMP (also carries tonight's Magpie flutter-button fix from §1 — no
   relog needed, these apps load QML per launch; just relaunch Magpie/Binnie/Orchidée):**
   ```
   sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/MagpieTalker.qml /usr/share/ncde/MagpieTalker.qml
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/binnie /usr/local/bin/binnie.new && sudo mv /usr/local/bin/binnie.new /usr/local/bin/binnie
   sudo cp ~/ncde-staging/LaPivot/usr/local/bin/orchidee /usr/local/bin/orchidee.new && sudo mv /usr/local/bin/orchidee.new /usr/local/bin/orchidee
   sudo cp ~/ncde-staging/LaPivot/usr/share/ncde/{BinnieCanvas,MillerColumn,FolderGrid,FolderList,OrchideeSidebar,OrchideeApp}.qml /usr/share/ncde/
   ```
   **Verify after deploy:** (1) launch Magpie — "✆ Video Call" visible top-right IMMEDIATELY
   (ink-toned; gilt inside an open DM); (2) launch Binnie — he BREATHES at rest now, cycling
   his idle cels, and reacts then returns to breathing; (3) toss a real file via TOSS → it
   lists with a ring → REWIND puts it back; (4) Orchidée: drag a file onto a folder / a
   sidebar place / the tree → it moves, Glia reacts; (5) drag a file onto "Bin" → it's tossed;
   tap "Bin" → browse it, REWIND in place; (6) both characters still animate on every action.
7. **verve-text Geany tier** — syntax highlighting, line numbers, tabs/multi-doc, folding,
   symbol list, auto-indent (undo/redo done session 71).
8. ~~**Vesper quarantine-review UI pane**~~ **BUILT session 78 (2026-07-06), AWAITING the
   §0.10 part-2 deploy** — full detail §0.10-J (QuarantinePane.qml, clickable "N held" header
   toggle, two-tap REMOVE confirm, silent refreshQuarantine(), load-gate + live-endpoint
   verified).
9. ~~**Screensaver minors**~~ **FIXED session 78 (2026-07-06), in binary `caed0d3a…`, AWAITING
   the §0.10 deploy:** (a) double-launch guard — previewScreensaver() now tracks its portal
   child (QProcess member, not startDetached) and refuses to stack a second (Settings.h);
   (b) crash-relaunch — new Settings::screensaverFinished(code,crashed) signal + WM
   screensaverIdleActive() accessor; main.cpp relaunches the saver if it died abnormally while
   the idle latch is still active (clean exits never relaunch — user input already reset the
   latch), bounded to 3 relaunches/60s against crash-loops. Backups
   `*.prebak-20260706-saverguard` (Settings.h, NCDEWindowManager.h, main.cpp).
10. **ncde-terminal source reconstruction** still doesn't build (shipping binary is the original,
    unaffected); AbuelaHelp's 10 [[UNRECOVERED]] strings need the real Ghidra project reopened.
11. ~~**Magpie MUC edges**~~ **STRUCK (session 79):** XMPP/MUC was removed entirely in the
    session-71 rearchitecture (world band replaced it) — the item's own "if XMPP survives"
    condition failed; moot.
12. ~~**geoclue DesktopId authorization**~~ **CLOSED — runtime-confirmed session 79
    (2026-07-06, fresh 22:31 session):** GeoClue2 `Client/17` exists WITH a delivered
    `Location/0` child (a Location object only materializes after an authorized Start() and a
    real fix), zero denial lines in geoclue's full boot journal. The client DesktopId property
    is root-readable-only (Access denied to the agent) — but behavior proves the allowlist
    authorizes us; magpie wasn't running, so the client is LaPivot/Lelan's. The recurring
    "WiFi scan failed" journal lines are the positioning source, not authorization.
13. **Clipboard "Mechanism B"** — ~50% paste failure in non-frozen windows, race-shaped, never
    root-caused (punchlist session 51/52). Operator-visible when it strikes.
14. **Tiling 8-window blink/freeze** — reported, not root-caused (GLX decoration-burst theory,
    needs live profiling).
15. ~~**PackageKit GetUpdates()**~~ **STRUCK (session 77, verified against tree):** fully
    implemented — `Lelan_System.cpp:172` subscribeToPackageKit() connects UpdatesChanged →
    onPackageKitUpdatesChanged, `:183` fetchPackageKitUpdates() does real CreateTransaction +
    GetUpdates with Package/Finished accumulation, re-subscribed on service restart via
    onNameOwnerChanged (Lelan.cpp:220). Not open.
16. **Weather host unreachable** — api.open-meteo.com times out from this machine (network, not
    code); failures now logged (session 71). Re-test on another network before ship.

## 3. ISO-gate items (before squashfs/mkarchiso)
1. Operator rm of tree junk (he does this himself): the 4 truncated-name QML files,
   usr/local/bin/__pycache__/, the 3 *.wrong-20260704-rewire terminal-qml files, the inert
   LLM stack (usr/bin/ollama, opt/ncde-chroma/, usr/local/bin/kickass-guard, their 4 units,
   ncde-vesper-provision.sh, empty usr/share/ollama), the stale user-scope
   usr/lib/systemd/user/ncde-sentinel.service. Then re-run the parity diff.
2. Confirm ISO exclude list covers: compass7/, all *.prebak*/*.bak/*.wrong-*/*.rebuilt-*/
   *.restored-*, __pycache__, /ncde-wm (tree-root dir: original ncde-wm.bak — operator to
   confirm exclusion), build dirs.
3. Plymouth hook missing from mkinitcpio.conf HOOKS= (splash likely dead) — never build-tested.
4. Volume label ARCHCRAFT_202605 → NCDE label in profiledef.sh.
5. Installer font family-name resolution in Calamares unconfirmed.
6. Recovery runtime test end-to-end (VT switch, admin seal, snapshot→restore→reboot) — file-level
   verified only; needs a VM pass.
7. `verdantfolio/` (tree-only QML dir) + missing abacus/.desktop entries — operator to say what
   verdantfolio is and whether abacus needs a launcher entry.
8. Re-run ncde-completeness-audit.md's gate AGAINST THE PRODUCTION TREE (its ✅s were verified
   against the dead tree; its Group-2 LLM section is obsolete — see its banner).

## 4. Standing rules that bite here (do not re-learn these the hard way)
- Tree and live are saved SIMULTANEOUSLY; a live-only patch is as much a violation as an
  undeployed tree fix (operator, session 71).
- THERE SHOULD BE NO STUBS. No visual-only debug tools. Never blame a stale build on the
  operator. Metal (terminal) does not change. NCDEGlass2 stays out of the widgets.
  Leap Frog bottom bar stays 4-title. Kith cursors are procedural — no disk themes.
