# NCDE source recovery

Goal: real, buildable source for every compiled NCDE component, so fixes go into code instead of
binary patches. Started 2026-09-30 with LaPivot. Lives on NCDE-BACKUP on purpose: the first
attempt (~/ncde-wm-rebuild, see docs/lapivot-rebuild.md) was lost in the 2026-09-29 reinstall.

All 25 compiled NCDE binaries are unstripped (full C++ symbol names, no DWARF).

## LaPivot/ layout
- `oracle/LaPivot.oracle` — the live, palette-patched binary, sha256 3507b4c6… (= raw + 3 Iris
  transforms). The reference truth: rebuilt source must behave identically.
- `interfaces/LaPivot-metaobjects.h` — EXACT class interfaces (24 QObject classes: properties,
  signals, slots, Q_INVOKABLEs, parameter names), dumped by Qt itself via `tools/metadump.cpp`
  (LD_PRELOAD, exits before main). Regenerate:
  `g++ -std=c++17 -fPIC -shared -o metadump.so tools/metadump.cpp $(pkg-config --cflags --libs Qt6Core)`
  then run a cap-free copy of the oracle with `LD_PRELOAD=./metadump.so METADUMP_LIST=tools/metaobjects.txt`.
- `tools/decompile.sh` — headless Ghidra (no sudo) → `decomp/<Class>.c`. Pre-script turns off
  "Non-Returning Functions - Discovered" (it falsely flagged QString ctor/dtor no-return and
  truncated bodies last time). `decomp/_noreturn.txt` lists what is still flagged.
- `src/` — clean, compile-verified C++ (class by class), then CMake.

## Method (per class)
1. Header from interfaces/ (exact) + member layout from the decompile.
2. Body from decomp/<Class>.c, rewritten as readable Qt C++.
3. Compile against real Qt 6.11 headers. Diff behaviour against the oracle (sandbox: bwrap +
   Xvfb, bind payload over /usr/share/ncde; QML errors in journal tag LaPivot).
4. Only when the whole binary builds and matches: replace the binary patches.

## Binary patches that become source (do not lose these)
- Iris Chroma: notes/apply-iris.py, apply-iris-contrast.py, apply-iris-widen.py + their JSON →
  generate `kPresets` from iris-palettes.json at build time.
- cap_sys_nice: set in packaging (install step), not by field scripts.
- RT leak (2026-09-30): Lelan::applyZenStartupHints sets SCHED_FIFO 1 without reset-on-fork, so
  every launched app inherited it (froze the ISO reauthor; bypassed App Nap + scx). Sentinel
  rt_guard.py is the current guard. In source: child processes get SCHED_OTHER at spawn, while the
  shell's own threads (QSGRenderThread) keep FIFO. Do NOT reset-on-fork the main thread; that
  strips FIFO from render threads created later.
- xset polling (LaPivot spawns xset several times a second) → event-driven (xcb-screensaver
  is already linked).
- Frameless Steam/game fix (LaPivot.prebak-20260715-frameless) — already in the oracle.

## >>> RESUME HERE (2026-10-01 ~21:40 — ISO reauthor in progress; 2 more regressions found + fixed) <<<
Operator said "go" (fix the ISO). Found on the way, both MEASURED fixed:
 R8 FIXED  Kith cursor size+colour jump between app windows and desktop. Cause 1: the rebuilt
           KithCursors::writeXcursorFile mixed QDataStream with direct QByteArray appends -> 2nd frame header
           overwrote frame 1, size check failed, NO Kith file written -> no XCURSOR_PATH -> apps drew another
           cursor (control run of 83d0ca3d: desktop 44x44 untinted, kitty/Thunar 60x60 untinted). Cause 2:
           12 of 14 Kith renderers were REDRAWN (hand drawn as arrow, other I-beam, move/resize/crosshair/
           not-allowed/grab art), sb_v/sb_h angles swapped, invented 113-size sweep + manifest. All re-translated
           line for line from decomp. tests/cursor_parity.sh: 14/14 Kith files byte-identical to the oracle,
           on-screen cursor identical over desktop/panel/dock/kitty/Thunar, same env, tint rebinds 2 like oracle.
           Build ddb4152c… = canonical payload LaPivot; old 83d0ca3d kept as oracle/LaPivot.83d0ca3d-kith-broken.
           OPERATOR RUNS: sudo bash /run/media/*/NCDE-BACKUP/INSTALL-LAPIVOT-KITH-FIX.sh, then relogin.
 R9 FIXED  Verdantfolio would not open: Main.qml:292 `clip: true` set twice ("Property value set multiple
           times" = QML compile error). Fixed canonical + live. NEW GATE: NCDE-Installer/packaging/
           qml-compile-gate.sh (real engine, Qt.createComponent, offscreen) runs in publish.sh --check on the
           embedded payload; qmllint does NOT catch this class. 229/229 payload QML compile.
 Patch repacked twice (verdantfolio, then LaPivot ddb4152c): canonical patch f9fd6d02…; publish = operator.
 ISO: recipe is files/iso/step20-refresh-poseidon.sh (stages tools..drivers done 09-29); remaining stages done
 ROOTLESS (operator: no root needed) — see files/iso/step21 when written.

## >>> (previous) RESUME HERE (2026-10-01 ~21:45 — L2 PROMOTED; WAITING FOR OPERATOR "go" → ISO REAUTHOR) <<<
**OPERATOR NOTE: when the operator comes back and types "go", reauthor the ISO.** Nothing else first.
State, MEASURED 2026-10-01 ~21:45:
 - PROMOTE-L2.sh run by the operator (backup + ROLLBACK.sh: /var/lib/ncde-update/pre-L2-20261001-204944/).
   /usr/local/bin/LaPivot = source-built sha 83d0ca3d… (cap_sys_nice=ep). /usr/share/xsessions = ncde.desktop only.
   Openbox uninstalled by the operator. /usr/share/ncde == canonical src/usr/share/ncde (screensaver/ kept, empty).
 - Ledger R1-R7 closed (R7 caption glow = QML fix, SalonPanel.qml sha 5bd89592…).
 - ONLY the new binary ships: canonical ncde-full-patch-20260711.sh repacked (sha d75909e5…, payload LaPivot 83d0ca3d,
   no prebaks); same file copied to NCDE-Installer/ (both copies) and as DOUBLE-CLICK-TO-INSTALL.sh (the old one
   carried the old payload + Iris transforms → OLD-PATCHES/). Old raw binary moved to LaPivot/oracle/LaPivot.raw-51d10a2c.
 - publish.sh --check: Iris raw+3 check replaced by "payload LaPivot == installed LaPivot, never 51d10a2c/3507b4c6".
   ~22:00: operator installed ncde-lock-xss → publish.sh --check PASSED (539 live files, LaPivot parity). Publish = operator.
   PUBLISHED by operator: NCDE 2026.10.01.2102 (release "installer"); its usr/lib/ncde-update/ncde-full-patch.sh = d75909e5… (LaPivot 83d0ca3d).
 - Before "go": operator logs out/in to the promoted LaPivot (was still running LaPivot-L2 pid 138023 at 21:45).
 - Old LaPivot.prebak-* moved into the pre-L2 backup dir by the operator (~22:00): /usr/local/bin has only LaPivot.

## >>> (previous) RESUME HERE (2026-10-01 ~20:40 — operator testing L2 live; PARITY AUDIT before promote) <<<
Operator: L2 is beautiful, "make L2 the real LaPivot", name is just "LaPivot" (L2 = test label), original removed,
then ISO. BUT: "we were only improving LaPivot" — every non-requested behaviour change is a defect. Promote ONLY
when the ledger below is empty and the operator says so. Staged: l2-stage/LaPivot-L2 sha 83d0ca3d… (= build-release/LaPivot
= canonical files/.../usr/local/bin/LaPivot). Operator installs with INSTALL-L2.sh, tests, then PROMOTE-L2.sh.
REGRESSION LEDGER (operator-found + found by me), status MEASURED:
 R1 FIXED  XSETTINGS: no byte-order header + string/int type codes swapped -> GTK "Invalid XSETTINGS" (bytes now == oracle).
 R2 FIXED  ncde-notify.so: offset fallback into wrong code after rename -> NotificationManager::notify exported (CMake);
           tests/l2_notify_test.sh PASS (dlsym, toast forwarded, LaPivot alive).
 R3 FIXED  Salon progress ring LOOPED: WidgetData media units were SECONDS, QML is ms -> now ms (seek ms->µs). NOT yet
           seen by operator (in b48c22ca).
 R4 CAUSE  Kith cursor blue + size jump terminal<->desktop: ncde-kith-tint only arms for comm=="LaPivot"; under
           "LaPivot-L2" it quit. Verified it tints when named LaPivot; tint now also accepts LaPivot-L2 (canonical QML).
 R6 FIXED  Salon stuck "playing" after Spotify closed: NameOwnerChanged was subscribed on org.freedesktop.DBus.Properties
           (never matches) -> oracle service/path/iface org.freedesktop.DBus (Lelan_core.cpp). Staged sha 83d0ca3d….
           Likely also why players started after login were never seen/removed. Operator has NOT run it yet.
 R5 FIXED  Salon "off" animations: operator confirmed working 2026-10-01 (~21:00) on LaPivot-L2 sha 83d0ca3d… (running
           since 20:34). Most likely cause: R6. With R6 broken, Salon never left "playing", so the off state could not show.
           No separate R5 code change was made. Open harness bug: tests/salon_probe.sh fake MPRIS is not detected by either binary.
 R7 FIXED  Salon off-state caption glow. NOT an L2 regression: oracle and L2 measured identical (tests/salon_frames.sh);
           the halo rendered but in the caption's own dim gilt peaking at 0.6 = +0.01 brightness, invisible. Fix (QML,
           canonical + /usr/share/ncde-l2 SalonPanel.qml sha 5bd89592…): halo in _roseLight (palette glow / Widgets Glow
           override), bold ghost, 3 blooms, breath 0.25->1.0. Title strip now breathes 0.161->0.213 (was 0.141->0.152).
           Operator to see it after PROMOTE-L2 + relogin. PROMOTE-L2.sh now also keeps screensaver/ and drops Openbox
           (operator already removed openbox ~21:30).
 R3 LIVE   ~21:10 operator: "outer ring not progressing". Measured live L2 + Spotify: track 2904 s, pos 1005->1025 s;
           arc end at ~125 deg (= 34.6 %), end dot moved ~3.6 px in 20 s (expected 2.5 deg = 3.8 px at r=88). The ring
           IS correct; a 48-min track sweeps 0.12 deg/s. Explained to the operator, awaiting their call.
 Engine fixes today (NCDEEngine.h fixes 6-10): no-op reselect, 7:1 ink floor everywhere, atomic saveTheme, preview
 valid/text keys, live gtkrc-2.0. Design kept: Solei-Lune lock — a palette pick sets its own mode, only the user locks.
PATCH (not yet repacked/published): deploy_lapivot installs source-built binary (refuses raw 51d10a2c…), automount retired
(global mask), L2 test files removed, session = l2-stage/ncde-x11-session-promoted. publish.sh still has the old
raw+3-transforms parity check -> must become live==payload before publish. REPO-MAINTENANCE.md LaPivot line to update.

## >>> 2026-10-01 19:15 — L2 login bounce was L2 (not Xorg): fixed + engine rebuilt to oracle <<<
 - 18:43 bounce = qFatal in Lelan::fetchSystemInfo (QDBusPendingReply<QMap<QString,QString>> for Sentinel a{ss},
   never qDBusRegisterMetaType'd). The 18:29 aborts (exit 134) look the same. Sandbox missed it: l2_sandbox_shot.sh
   hides the system bus. USE tests/l2_livebus_shot.sh (real system bus + host LANG) and diff against the oracle
   (/usr/local/bin/LaPivot + /usr/share/ncde) in the same harness.
 - Fixed vs live: a{ss} registered; PackageKit = oracle CreateTransaction -> Transaction.GetUpdates(t 0); /proc
   meminfo/cpuinfo/net/dev read whole (RAM was 0); dateString = oracle "dddd, MMMM d"; Theme font sizes =
   oracle int(base*fontSizeScale*uiScale); NCDEEngine rebuilt function-by-function from decomp (colour state,
   presets, wallpaper k-means, filigree store, theme json, GTK bridge, terminal config path).
 - Proof: all 32 engine colours + darkMode + accentName + version identical oracle vs L2 (on-screen probe,
   same QML); side-by-side screenshots match except the operator-requested panel frames.
 - QML untouched (panel frames, panel-frame.png, ExposeBackdrop, muchaexpose kept).

## >>> RESUME HERE (2026-10-01 18:40 — L2 login bounce = Xorg crash, NOT L2) <<<
 - Operator logged out of LaPivot 18:29:23 and into NCDE L2 18:29:33. Xorg (modesetting, Intel JasperLake, xorg-server 21.1.24)
   SIGSEGV at 18:29:35 in dispatch_dirty_region: screen pixmap refcnt 0 / freed while present_flipping on the composite
   overlay window. LaPivot-L2 then aborted ("X11 connection broke"), the portal restarted X, relaunches got "Authorization required".
 - Same crash with the ORACLE on 2026-09-30 19:43 and 21:11 (~/ncde-debug.log: exit 0 logout, relogin, exit 1 -> 134 x3).
 - Fix: Option "PageFlip" "false" in files/full-patch-20260711/src/etc/X11/xorg.conf.d/10-ncde.conf (prebak: none, live copy was identical).
   Operator installs it + reboots, then logs into L2 on real Xorg. L2 is still UNTESTED on real Xorg until then.

## (previous) RESUME HERE (2026-10-01 16:20 — L2 STAGED, operator installing) <<<
 - l2-stage/ rewritten (old wrong INSTALL in l2-stage/old/): LaPivot-L2 (+sha256), INSTALL-L2.sh (QML from the canonical
   tree -> /usr/share/ncde-l2, setcap, session script, ncde-l2.desktop), UNINSTALL-L2.sh. ncde-x11-session-l2 = exact
   copy of the live session script except LaPivot-L2 / NCDE_ASSET_BASE / qmlcache-l2 / ncde-l2-debug.log / pauses
   ncde-automount for the session. PROMOTE-L2.sh NOT reviewed yet (12:45 agent version) — review before any promote.
 - Weather: WidgetData had no fetch at all -> rebuilt from oracle (open-meteo) + W1 retry 60 s, W2 refetch on place,
   W3 Settings pin honoured, W4 automatic chain pin > GeoClue > place learned for this network > IP, NO fixed town
   (operator: location must adjust to every user). widget_data.refreshWeather() called by DateTimeTab after pin change.
 - QML rewired off removed ncde.* forwarders: DateTimeTab (refreshLocation/setTimezone/setNtp -> lelan.*),
   MagpieTalker (setUserAvatar -> lelan, asset paths -> settings.assetBase); main.qml helper paths -> settings.assetBase.
 - Sandbox script now uses the real session env (QML_XHR_ALLOW_FILE_READ etc.) — earlier shots lacked it.
 - Still open: items 2-4 below (iconify poll removal, Expose translucent+wallpaper+black labels, xset "900").

## (previous) RESUME HERE (2026-10-01 ~16:00 — operator left; finishing L2) <<<
DONE + MEASURED this session:
 - LaPivot compile fixed: FontManager (const QDBusConnection), KithCursors (missing <QFile>), main.cpp (called the
   removed NCDEEngine::setLelan), Q_MOC_INCLUDE("Settings.h") in NotificationManager.h/WidgetData.h.
   compile_all.sh PASS 0 warnings; CMake full link of LaPivot-L2 OK, 0 warnings (scratch build).
 - Panels, canonical QML TopPanel/BottomPanel.qml (backups *.prebak-20261001-frame-flag): glass inset 26->47 px so
   the pill end nests inside panel-frame.png's C-caps (measured: no ink overlap on any row); pennant (flag)
   restored under the N logo, hangs from the frame's bottom rail, fades when the Glia drawer opens (sandbox shots).
FOUND: src/NCDEWindowManager.{h,cpp} by another agent was NOT the oracle: no container/reparent, no `title` role,
   shifted role numbers -> L2 showed a black full-screen frame titled "Window" over dock/panels/glass. The oracle
   binary in the same sandbox frames the same window correctly (title "Notes", ncde-container + ncde-frame).
UPDATE 16:02: WM .cpp REWRITTEN (1401 lines) + CMake build OK 0 warnings; sandbox: yad window framed exactly like
   the oracle (title "Notes", ncde-container + ncde-frame in xwininfo); desktop shot: dock icons + all glass present.
   Shots: ~/Downloads/NCDE-PNGs/previews-20261001-L2/. Sandbox script: LaPivot/tests/l2_sandbox_shot.sh.
   Still to do from the list below: compile_all.sh rerun, items 2-6, Expose test (open via F1/dock with no
   maximized window covering the dock), minimize/restore + close test.
(was) IN PROGRESS: oracle-faithful WM rewrite. New header DONE: src/NCDEWindowManager.h (lists fixes W1..W13).
   If src/NCDEWindowManager.cpp still begins "// Rebuilt from oracle: decomp/NCDEWindowManager.c." it is the OLD
   file: write the new .cpp from decomp/NCDEWindowManager.c lines 736-5126 + decomp/_global.c FUN_00291390 (game
   path: appId steam/steamwebhelper/gamescope/steam_app_* -> no container, frame shaped empty). Old pair kept as
   *.prebak-20261001-oracle-rebuild. Key oracle facts: manage() does NOT map; registerFrameWindow() makes the
   container (x-12,y-32,w+24,h+58), reparents client at (12,32), maps, stacks frame above, input shape = 4 ring
   rects; roles 0x101 winId..0x10a title(name or appId)..0x10b tiled.
NEXT, in order:
 1. Finish WM .cpp -> compile_all + CMake link -> sandbox test against the oracle (Xvfb :77 + bwrap, private dbus,
    no system bus, NCDE_ASSET_BASE=canonical QML; script pattern in the session's scratchpad shot/run.sh): open a
    yad window, check title/reparent (xwininfo -root -children), minimize/restore, Expose, dock icons, all glass.
 2. main.qml: delete the 250 ms _pollIconify XHR timer + the ncde-iconify-bridge launch (the WM now handles
    WM_CHANGE_STATE / _NET_WM_STATE_HIDDEN directly, W5).
 3. Expose (operator 2026-10-01): background stays TRANSLUCENT (muchaexpose alpha 143) with the WALLPAPER under it,
    never black; each icon's label text gets a black background.
 4. Log bug: "xset: unknown option 900" — a bad xset call somewhere in src (grep xset).
 5. l2-stage/INSTALL-L2.sh is WRONG: takes the binary from /usr/local/bin/LaPivot (the live one) and QML from
    /usr/share/ncde (old). It must install the built LaPivot-L2 and the canonical QML tree into /usr/share/ncde-l2.
 6. LaPivot/sys = 42 MB ImageMagick screenshot made by a python script run with bash (`import sys`). Ask operator
    before deleting.
 7. Operator installs + tests L2. Only on the operator's word does L2 replace the LaPivot session; then ISO; then
    the other machine.
NOT DONE (honest): _NET_WM_STATE_FULLSCREEN for framed windows (browser/video F11); the oracle never had it either.

## (previous) RESUME HERE (2026-10-01 10:15 — THIRD LAUNCH, 10 PARALLEL AGENTS RUNNING) <<<
The 21:25 relaunch also died at ~21:30 (session limit): every reports/*.md was a stub, a few Settings/Sni/test files
changed 21:29-21:30 (UNVERIFIED). Relaunched all 10 groups 2026-10-01 ~10:15 with an updated
agent-prompts/_relaunch-preamble.txt (old copy .prebak-20261001). Same recovery rule: read reports/, relaunch only
unfinished groups. NCDE_POSEIDON stick mounted read-only for agents.

## (previous) RESUME HERE (2026-09-30 21:25 — 10 PARALLEL AGENTS RUNNING) <<<
The 18:52 launch of 7 agents died 7 min later (session limit); nothing survived. Relaunched 21:25 as 10 groups:
lelan, colour, wm, calendar, cursor-fonts, widgets, menus-tray (original assignments) + settings (rest of Settings,
IdleIoScope), main-l2 (main(), CMake, asset base, l2-stage/ INSTALL/UNINSTALL/PROMOTE-L2.sh — staged, not run),
art (panel.png 9-slice frames on top+bottom panels matching the dock; Mucha Expose backdrop). Assignments:
agent-prompts/*.txt (+ _relaunch-preamble.txt). Each agent writes reports/<group>.md incrementally — if a session
dies, read reports/ and relaunch only unfinished groups from agent-prompts/. Helpers: LaPivot/tools/bin/{fn,fnc,sig}.
Then: coordinator integrates (main.qml/TopPanel changes reported by agents, NCDEExpose backdrop), full build,
sandbox test, operator installs L2 -> tests -> "make L2 the real LaPivot" -> PROMOTE-L2 -> ISO reauthor -> repo publish.

## (previous) RESUME HERE (handoff 2026-09-30, operator had to go)
Lelan subsystems DONE (source + live tests): power, zen, session, time, audio, network (+NetworkTab),
bluetooth (+BluetoothTab), media, storage (+StorageTab, S7 auto-mount). All units: `bash LaPivot/tests/compile_all.sh` (0 warnings),
`bash LaPivot/tests/iface_check.sh Lelan` (oracle + 17 declared additions).
NEXT, in order:
 1. DONE 2026-09-30 (later session): StorageTab.qml → lelan.*, sizes readable, Eject + "safe to remove", Unlock row,
    failure line, "Working…"; Lelan S7 auto-mount (replaces the ncde-automount daemon). See the Storage rows below.
 2. Remaining Lelan: portal settings (ORACLE-EXACT, no changes — operator rule, never touch ncde-portal),
    KickassGuard, PackageKit updates, users, printers, tray, Sentinel device events, config, then the core
    (constructor, onPulse/onCoalescedTick heartbeat, NameOwnerChanged wiring, _GLOBAL__sub_I).
 3. Other LaPivot classes (Settings, NCDEWindowManager, NCDEEngine [drop network/bt forwarders],
    WidgetData, CursorManager, theme classes, Launcher, NotificationManager, calendar, menus, tray watcher)
    and main(); CMake; sandbox test; then ship with the new NetworkTab/BluetoothTab/StorageTab QML.
    main() MUST: lelan->setAutoMountPref(settings->autoMountUsb()) at start + on Settings::storageChanged (S7).
 4. SHIP AS A TEST SESSION "L2" FIRST (operator 2026-09-30: "a different session in case it crashes"): the rebuilt
    LaPivot installs BESIDE the current one — /usr/local/bin/LaPivot-L2, its QML in /usr/share/ncde-l2/ (the new
    NetworkTab/BluetoothTab/StorageTab/DisplayTab need the new LaPivot; the old one keeps /usr/share/ncde), a session
    script ncde-x11-session-l2 and /usr/share/xsessions/ncde-l2.desktop (Name=NCDE L2). ncde-portal already lists
    /usr/share/xsessions/*.desktop — nothing in ncde-portal changes. Rebuild needs the asset base configurable
    (NCDE_ASSET_BASE, default /usr/share/ncde/). Same ~/.config/ncde files: keep formats compatible both ways.
    Only after the operator has run L2 and says so does it replace the main session.
 5. After LaPivot: Orchidée seal password (spec in work list).
Test SAFETY rules learned this session: media tests use fake players only (a test seeked the operator's
Spotify); test scripts never `kill ${VAR:-0}` (kill 0 = own process group → cleanup aborted, loop devices
left); anything network-facing uses NM BLOCK_AUTOCONNECT; always verify cleanup (losetup/mount/mapper/busctl).
Owed live tests needing the operator: Wi-Fi wrong-password/SAE join (drops Wi-Fi ~20 s), cable, real
Bluetooth pairing, real-stick eject.

## Progress (measured, not claimed)
| Class | Status | Proof |
|---|---|---|
| AnimPolicy | rebuilt + defect fixed (low-power reasons now raise level to ≥1, zen.md §4) | tests/animpolicy_diff.cpp: 200k faithful steps + 200k fixed steps vs oracle, 0 mismatches, identical changed() counts; mutation check (fix removed) fails as it must — 2026-09-30 |
| ZenGovernor (Lelan governor core: startup hints, uclamp, thermal/CPU/memory pressure, anim level) | rebuilt + Z1 (RT leak → FIFO\|RESET_ON_FORK, render threads self-promote) + Z2 (uclamp boost: KEEP_PARAMS; oracle call measured EINVAL) fixed | tests/zen_test.cpp: part A 5196 cases vs oracle transcription; part B real syscalls with cap_sys_nice: child thread/process OTHER, promoted thread FIFO, oracle flags 0x28 → EINVAL, fixed call util_min 200; mutation (16→15%) fails — 2026-09-30 |
| Lelan (interface + power + governor glue) | header generated from oracle metadata; power (Z3 change checks, Z5 initial power profile) + governor glue (Z6 Sentinel senses / Lelan decides) written, compiles | tests/iface_check.sh Lelan: INTERFACE IDENTICAL (65 props, 70 signals, 105 slots, 3 invokables); oracle under gdb on this laptop: updatePressure(pegged=1) at idle/AC → setLevel(1) — the Z6 defect, measured; zen_test Z6 cases: idle/61 °C/AC → level 0 — 2026-09-30 |
| Sentinel pressure.py (new) | Sentinel now senses CPU saturation (real busy time, /proc/stat, 90 % × 2 polls) + CPU temp (thermal zones → hwmon CPU chip fallback) + machine's own trip point; PressureSensed / GetThermalTrip | live: idle 3/3 polls not saturated, full load saturated after 2 polls; simulated no-thermal-zone machine → coretemp + temp_crit 105 °C; synthetic cases pass — 2026-09-30 |
| Sentinel App Nap → per-process priority (operator decision) | LIVE. Tiers = nice +0/+5/+10 + I/O BE 4/6/7 on every thread + descendants; apps never leave the login session; old ncde-nap scopes migrated back via cgroupfs (systemd refuses AttachProcessesToUnit on session scopes). Pending install: loginuid fix for sudo'd processes in the one-shot migration | live 2026-09-30: terminal back in session-3.scope, logind GetSessionByPID OK, pkcheck power-off + inhibit-block-sleep = yes (were auth_admin_keep); Thunar recorded: focused nice 0 / visible 5 / minimized 10 (I/O 7), all 8 threads; wake-up latency with 4 cores saturated at nice 0 in-session: median 0.58 ms, p99 1.6 ms, max 3.2 ms (< 16.7 ms frame) — no "nothing clickable" regression |
| QML ↔ C++ binding audit (tests/qml_binding_audit.py) | 33 dead bindings in shell QML (after false-positive removal; closure = 85 files LaPivot loads) → 0. SoundTab audio → lelan (device pickers, balance, per-app volume were dead since forever: ncde = colour engine only); 165 theme.fontWeight/fontItalic → settings (23 files; OPEN-ITEMS' documented fix, never landed); AboutTab → lelan.hostname + lelan.systemInfo (Sentinel GetSystemInfo, new; declared Lelan addition) | audit: TOTAL missing bindings 0; qmllint clean on all edited files; Settings::fontWeight/fontItalic confirmed real props; no app has Theme::fontWeight (checked 8 binaries); Sentinel system_info live output: CPU/mem/GPU/disk+model/release in 36 ms — 2026-09-30 |
| Lelan audio / session / time | Lelan_audio.cpp (A1 lock race, A2 shared global lists, A3/A4 no change checks, A5 2-channel per-app volume, A6 first-match only); Lelan_session.cpp (S2 Active/LockedHint never read, S3 change checks); Lelan_time.cpp (T1 hostname/locale never read, T5 night light flipped once, T7 GeoClue accuracy int32 rejected → no location ever) | audio_math_test 28926 cases 0 mismatches; suntimes_diff (oracle's own computeSunTimes in-process) 3528 locations 0 mismatches + night flag 12960 cases 0 mismatches, mutation fails; T7 proven live: GeoClue "Expected type 'u' but got 'i'" for int32, uint32 accepted; all units fresh-compile, 0 warnings (re-checked in a new session incl. Qt6 moc); iface_check Lelan: oracle interface preserved + 2 declared additions — 2026-09-30. Live read-only audio test pending the Lelan constructor |
| Lelan network (Lelan_network.cpp) + Settings › Network tab | N1 AP list re-fetched every AP on each scan and signal minutes old → cached, Strength patched live, published only on a visible change; N2 change checks; N3 failed read ≠ disconnected; N4 IP after DHCP + no stale ip/speed; N5 connectWifi made a new profile every time + wpa-psk only → saved profile reused/updated, SAE; N6 mesh "connected" flag; N7 network.ssid for WeatherLive (never set); N8 failed join silent → wifiConnectFailed; N9 link speed frozen; N10 two adapters: last reply won; N11 no wired record (tab showed Wi-Fi under Ethernet) → wiredNetwork; N12 no way to add/remove VPNs → importVpn (WireGuard parsed + AddConnection2 autoconnect off + BLOCK_AUTOCONNECT; OpenVPN via nmcli then autoconnect off) + removeVpn; V1 WireGuard never "connected"; V2 profile add/remove never listed; V3 double emit, first wrong; V4 disconnect by Id. NetworkTab.qml: ncde.* → lelan.* (digest: ncde = colours only), signal bars always 1 (inner Repeater modelData), Connect button dead / overlapped the lock, disconnected shown as connected ({} truthy), Ethernet panel showed Wi-Fi, import/remove VPN | tests/network_live_test.sh vs nmcli/ip: 20+ checks PASS, strength cache = NM's last broadcast (mutation fails, 7 stale APs), N9 speed = NM Bitrate, 0 networkChanged/wifiChanged at steady state vs 10-25 NM AP signals/40 s; vpn_live_test.sh: NM Active.Vpn=false for WireGuard (V1 proven), connect/disconnect via Lelan one emit each; wg_import_live_test.sh 19 PASS (full-tunnel file never activated per journal, all 15 stored fields incl. keys = file, refusals readable, removeVpn); vpn_import_live_test.sh OpenVPN 7 PASS; network_qml_test.sh renders the real NetworkTab.qml on live NM, 0 QML warnings, screenshots checked; iface: oracle preserved + 7 declared additions — 2026-09-30. NOT yet exercised live (would drop Wi-Fi or needs hardware): wrong-password join → message, saved-profile password update, WPA3-SAE join, cable plug/unplug |
| Lelan Bluetooth (Lelan_bluetooth.cpp) — backend | B1 full GetManagedObjects on every device/GATT signal → patched; B2 change checks; B3 scan never stopped → 30 s; B4 no pairing agent → org.bluez.Agent1 (KeyboardDisplay, default) → lelan.bluetoothPairing / bluetoothPairingReply; B5 Pair → Trusted → Connect; B6 silent failures → bluetoothFailed; B7 mouse/gamepad typed "keyboard"; B8 lelan.bluetooth never written → adapter summary; B9 multi-adapter; B10 rfkill soft block → unblock + power; B11 nameless beacons hidden. Shared test build tests/lelan_test_build.sh; relays in lelan_dbus_relay.h | tests/bluetooth_live_test.sh on this BlueZ: state == bluetoothctl (5 PASS); 40 s scan: 0 GetManagedObjects, Discovering false by itself at ~30 s; BlueZ accepted RegisterAgent + RequestDefaultAgent; confirm/reject/passkey 123456/unpaired AuthorizeService refused (stand-in on session bus — system bus lets only root call agents); rfkill: BlueZ answers a blocked Powered=true with "Failed" (oracle's call), Lelan unblocked + powered; iface: oracle preserved + 12 declared additions — 2026-09-30. BluetoothTab.qml DONE in payload (backup .prebak-20260930-lelan-bluetooth): ncde.* → lelan.*, My Devices (paired) / Nearby (scan) split, Pair button (never called before), pairing prompt card (confirm/display/pin/passkey/authorize), "Scanning…", failure under the device; tests/bluetooth_qml_test.sh renders it on live BlueZ, 0 QML warnings, screenshots checked. Ships with the rebuilt LaPivot (needs the new members). Real-device pairing owed (operator's phone/headphones) |
| Lelan media (Lelan_media.cpp) | M1 any player's PropertiesChanged re-fetched EVERY player (GetAll) → sender-aware MprisRelay, no call; M2 change checks; M3 Seeked applied to the wrong player; M4 re-scan reset all players (title blink); M5 1 s D-Bus position poll → clock × Rate, resync on Seeked/status/track + every 10 s; M6 playerctld proxy ignored; M7 track change kept old position; M8 paused now-playing kept over a playing player. Oracle now-playing rule kept (browser never replaces a playing non-browser) | tests/media_live_test.sh vs 2 fake MPRIS players (fake_mpris.py, per-sender call counts): 15 PASS; rebuilt Lelan 1 GetAll per player total vs the LIVE oracle LaPivot (:1.11) 14+13 GetAll on the same fakes in the same 20 s (M1 measured live); 0 Get(Position) on pulses. Test safety: real players (Spotify) dropped from the object under test, commands only to fakes, stale-fake guard (an earlier run seeked the operator's Spotify 33:34→0:50 — restored with their OK) — 2026-09-30 |
| Lelan storage (Lelan_storage.cpp) — backend | S1 mount/unmount failures silent + fixed 600 ms re-read → volumeFailed; S2 no eject → ejectVolume (unmount all, lock, eject, power off) + volumeEjected; S3 whole UDisks tree re-read per signal (jobs too) → filtered + 150 ms coalesced; S4 change check; S5 HintIgnore volumes shown (ARCHISO_EFI); S6 LUKS sticks invisible → listed locked + unlockVolume | tests/storage_live_test.sh: operator's sticks LISTED only (NCDE-BACKUP, NCDE_POSEIDON correct, ARCHISO_EFI hidden); throwaway loop images: mount, busy unmount reported + still mounted, unmount, wrong/right LUKS passphrase; 5 GetManagedObjects for 33 UDisks signals (4 mount/unmount cycles; counted with tools/dbus_call_log.cpp LD_PRELOAD — system bus forbids eavesdropping); cleanup verified 0 leftovers; iface: oracle + 16 declared additions — 2026-09-30. NOT tested: ejectVolume on a real stick (would power off a stick — ask operator). StorageTab.qml NOT done yet |
| Settings › Storage tab (StorageTab.qml) + Lelan S7 auto-mount | StorageTab: widget_data.* (pass-through) → lelan.*; raw bytes → "62 GB"/"7.9 MB"; nameless stick shown by drive name; Eject (ejectVolume) + "X can be removed safely."; locked LUKS row: Unlock → passphrase field (Password echo, cleared on send, Enter works) → unlockVolume; volumeFailed shown under the row; "Working…" per row (cleared by storageChanged/volumeFailed/volumeEjected, 120 s one-shot guard); eject success clears an old failure. Backend: S7 auto-mount on insertion moved into Lelan (setAutoMountPref slot) — the ncde-automount daemon mounted anything with a filesystem on USB incl. HintIgnore/HintAuto=false partitions and after reformat; Lelan mounts only a filesystem NEW since the last read, on a removable drive whose media arrived < 60 s ago (Drive.TimeMediaDetected), HintAuto true, not mounted, not LUKS cleartext (unlockVolume mounts that), never on the first read (plugged in before login). Eject/mount of a vanished volume: was silent / raw "Object does not exist" → "This drive is no longer connected" | tests/storage_automount_test.sh: 12 synthetic cases PASS + a real loop image presented as an inserted stick got mounted by Lelan, cleanup verified; mutation (insertion-time rule removed) → reformat case FAILS as it must. tests/storage_qml_test.sh (storage_qml_host.cpp): real sticks displayed only (NCDE_POSEIDON, NCDE-BACKUP with mount points, ARCHISO_EFI hidden), invented rows CLICKED for real (Mount/Unlock+typed passphrase+Enter/Eject each reached Lelan → UDisks answer → failure line), 20 checks PASS, 0 QML warnings, screenshots checked (no overlap, long names elided); storage_live_test.sh re-run after the refactor: all PASS, 5 reads / 33 signals; qml_binding_audit 0 missing; qmllint: only the lelan/settings context-property notices (was 55 unqualified, now 19); iface: oracle + 17 declared additions (setAutoMountPref) — 2026-09-30 |
| Settings power / idle / screensaver / screen lock (Settings_power.cpp, IdlePolicy, Settings.h) + Lelan lid (S4) + Lelan config (Lelan_config.cpp) | Settings.h generated from oracle metadata (99 props; field defaults = oracle constructor). Fixed: I1 suspend ~30 s after last input on battery (onScreenIdleChanged on any AnimPolicy change) -> IdlePolicy counts real idle minutes; I2 X saver timer set to the suspend minutes (+ session script xset s) armed a 2nd saver + xss-lock lock -> X saver off, LaPivot sole idle owner (ncde-x11-session: xset s off); I3 requirePassword/delay never used -> idle lock follows them, ncde-lock-xss skips the SLEEP lock when off; I4 saver relaunched right after a key press -> only after a crash while nobody is back, 3 max; P1 3 x xset per batteryChanged -> only on change; P2 saver stdout pipe never read -> forwarded; P3 lid action did nothing (logind HandleLidSwitch=ignore, no listener) -> Lelan lidClosedChanged -> suspend/lock/nothing; P4 saver default 300 min. Lelan config C1 "../" names from QML -> refused; C2 saveConfig result returned | tests/idle_power_test.sh: 23 PASS (simulated idle, commands recorded, stand-in saver; suspend once at 15:00 on battery vs oracle ~0:30; lock at 5:00 / 6:00 with delay 60 s; no lock with the switch off; re-arm after input; no repeat after resume; lid; relaunch rules); ncde-lock-xss 4 cases vs a stand-in ncde-lock (sleep lock skipped only when requirePassword=false); iface Lelan: oracle + 19 declared additions; compile_all 0 warnings — 2026-09-30. main() must: settings->idleMsSource = WM xcb idle query; WM pollUserIdle -> settings->onIdleSample(ms) |

## Work list (found by measurement 2026-09-30, not yet fixed unless marked)
- [x] Sentinel re-sent BatteryStateChanged on every battery uevent (~every 3 s, nothing new) →
      Lelan → Settings::applyPowerSettings → 2-3 `xset` per event (~60/min). Sentinel now emits
      only on change (installed + verified: 0 signals / 30 s).
- [ ] Lelan::onSentinelBatteryStateChanged emits batteryChanged without a change check (rebuild).
- [x] (FIXED in source 2026-09-30, ships with LaPivot — see Settings power row) IDLE SUSPEND/LOCK DEFECT (operator report 2026-09-30 "it makes the system lock if it is idle too long"; measured in
      the oracle): Settings::onScreenIdleChanged is connected to AnimPolicy::changed() (ANY policy change) and runs
      `systemctl suspend` whenever animPolicy.screenIdle is true and the current suspend setting is > 0 — it never
      counts the minutes. screenIdle includes AnimPolicy::onUserInputIdle, which NCDEWindowManager::pollUserIdle (2 s
      poll) sets after 30 s without input (29999 < ms_since_user_input). So on battery with batSuspend=15 the laptop
      suspends ~30 s after the last input, and xss-lock --transfer-sleep-lock locks it -> password on wake. On AC
      (acSuspend=0) it never suspends. FIX in the Settings/NCDEWindowManager rebuild: suspend only when X idle
      >= <ac|bat>Suspend minutes (WM idle ms, not the 30 s flag), only on the idle edge, respect IdleInhibit (it
      resets X idle via ForceScreenSaver — keep), re-arm after wake; never on any unrelated AnimPolicy change.
      Test with a fake idle clock (no real suspend) + one real check with the operator's OK.
- [ ] Screensaver dismiss (operator report 2026-09-30): standalone `ncde-portal --screensaver` quits on a key
      (confirmed live: the operator's key closed a test saver; X idle 768 ms). Ignores input for its first 500 ms
      (armed timer, ncde-portal — hands off). LaPivot side to keep correct in the rebuild: Settings::previewScreensaver
      QProcess + main() relaunch-on-crash lambda (relaunch only if exit!=0 AND WM idle flag still set; the flag is only
      re-polled every 2 s) — relaunch must also require that no input happened since the saver started.
- [ ] (APPROVED by operator 2026-09-30 "as long as you don't break the portal"; CONFIRMED: /proc/<LaPivot>/root owned by root,
      unreadable to the user, CapEff 0x800000 = cap_sys_nice) main() must call prctl(PR_SET_DUMPABLE, 1) at start. Safe: ptrace still
      needs the tracer to hold LaPivot's capabilities. Nothing in ncde-portal changes. Portal reads refused live: "[lelan] portal ReadOne failed ... AccessDenied: Unable to open /proc/<LaPivot>/root"
      (xdg-desktop-portal cannot inspect a process with file capabilities — cap_sys_nice makes it non-dumpable), so
      darkMode/accentColor never arrive. Lelan_portal.cpp itself is oracle-exact (operator rule); the fix belongs where
      the process is set up (main(): prctl(PR_SET_DUMPABLE,1) after start, or read via a helper) — ask the operator
      before changing, since it touches what the portal sees.
- [ ] journald is volatile (/etc/systemd/journald.conf.d/volatile-storage.conf): freezes/locks from earlier boots
      leave no log. Ask the operator whether to make it persistent (size-capped).
- [ ] Settings::applyPowerSettings runs xset on every batteryChanged; screen-blank only depends
      on AC vs battery → apply only when that changes (rebuild).
- [x] (tree) 90-ncde-zen.rules retired: root bash every 3 s, and it rewrote the governor/EPP behind
      GameMode's back (gamemode.py pin undone within ~3 s — by code; not yet tested with a game).
- [ ] NCDEExpose.qml: ~90 "Unable to assign [undefined] to int/bool" per minute (MotifFrame.qml
      ~9/min too) — broken bindings re-evaluating in LaPivot.
- [ ] AFTER LAPIVOT IS FINISHED (operator 2026-09-30, repeated): make ~/Downloads/NCDE-PNGs/shell-art/muchaexpose-1920x1200.png
      (Claude's padded version "with the black outline"; same image as pending-art/ below) NCDE-Expose's background, as planned.
- [ ] AFTER LAPIVOT (operator 2026-09-30, REVISED same day): PANEL FRAMING — reuse the DOCK'S FRAME for the top and
      bottom panels so all three match and look intentional; the separate ornaments (top-ornament.png /
      bottom-ornament.png) are dropped. ART: ~/Downloads/NCDE-PNGs/shell-art/panel.png (operator 2026-09-30, ONE image
      for BOTH panels; 2172x724 RGBA, content bbox y 23..724): amethyst end caps + straight double rails between them
      -> stretch horizontally as a 9-slice (caps fixed, only the straight rails stretch), panel content inside the
      frame's measured inner clear zone. Panels float and can be moved up and down freely, like the dock; the frame
      fits each panel and moves with it. No-overlap rule (nothing intersects; frames hug; measured clear zones);
      sandbox-render-test before shipping.
- [ ] NCDE-Expose background = pending-art/muchaexpose-1920x1200.png (operator's stained-glass
      Mucha "MUSA", resized by operator to 1920x1073; Claude padded 63/64 px top/bottom with the
      art's own edge colour rgba(0,0,0,143) to fill the 1920x1200 screen, no stretch). Unpadded
      original kept as pending-art/muchaexpose.png.
- [ ] anim-policy.md §4.4 violated: 29 repeating QML Timers in 21 files. Worst: main.qml:238 polls a
      file via XHR every 250 ms forever (_pollIconify <- ncde-iconify-bridge) — must become an
      event (X11 property / D-Bus signal through Lelan). Audit each remaining timer: gate on
      visibility + animPolicy, or move the source into Lelan's coalesced tick.
- [ ] anim-policy.md §1 violated: 420 GUI-thread animations vs 33 render-thread Animators. Identify
      the must-not-stall ones (panel reveals, glass transitions, dock, Expose, recovery bar) and
      convert them to Animators.
- [x] anim-policy.md checked OK (measured 2026-09-30): §3 level table (Lelan::recomputeAnimLevel),
      §4.1 picom vsync=true, §4.2 threaded render loop (4 QSGRenderThreads), §4.4 Lelan: one 1000 ms Qt::CoarseTimer = onPulse
      heartbeat (QML pulse(tick) + media position while playing); the coalesced system tick
      (clock, disk, weather, thermal) runs every 60th pulse = once a minute, matching lelan.md
      (CORRECTED 2026-09-30: earlier claim 'clock ticks every second vs spec' was wrong), idle queue 250 ms only while non-empty, reduce-motion reaches the
      level via Settings::applyAccessibility -> Lelan::setReduceMotionPref.
- [ ] cal-reminders.service stuck "activating" (timer fires every minute).
- [ ] Thunar SIGSEGV 04:30:38 (coredump present) — check whether NCDE's GTK module is in the stack.
- [ ] LaPivot 19-22% CPU at idle — profile once the above noise is gone.
- [ ] SHIP TOGETHER with the rebuilt LaPivot (not before) — Wi-Fi/network changes 1-21 APPROVED by the
      operator 2026-09-30 (list given in session): payload NetworkTab.qml (backup
      NetworkTab.qml.prebak-20260930-lelan-network) needs Lelan wiredNetwork/importVpn/removeVpn/
      wifiConnectFailed; on today's LaPivot Import/Remove would throw.
- [ ] NCDEEngine rebuild: drop its network/bluetooth forwarders (wifiEnabled … connectVpn) — NetworkTab no
      longer calls them; check BluetoothTab first (same ncde.* pattern likely) and declare the removals.
- [ ] Live tests still owed (drop Wi-Fi ~20 s or need hardware): wrong-password join, saved-profile password
      update, WPA3-SAE join, Ethernet cable plug/unplug. Operator: run them only when they say so.
- [ ] SHIP TOGETHER with the rebuilt LaPivot: payload StorageTab.qml (backup StorageTab.qml.prebak-20260930-lelan-storage)
      needs Lelan ejectVolume/unlockVolume/volumeFailed/volumeEjected; at the same time RETIRE ncde-automount
      (usr/local/bin/ncde-automount + usr/lib/systemd/user/ncde-automount.service, disable the user unit) —
      Lelan S7 does it, and two mounters would race. main() wires Settings::autoMountUsb → Lelan::setAutoMountPref.
- [ ] WidgetData rebuild: the panel clock (TopPanel: widget_data.timeHour/timeMinute) must follow Settings hourFormat
      ("auto" = locale, "12", "24") and showSeconds — today only DateTimeTab reads them, so the choice changes nothing.
- [ ] Oracle LaPivot logs "QDBusArgument: write from a read-only object" ×6 at start (journal 16:25:14,
      2026-09-30 boot). Source not yet identified; the rebuilt storage/bluetooth/network hosts count all Qt
      warnings and log none — find the oracle subsystem when rebuilding the Lelan core, confirm it's gone.
- [ ] Owed live test (operator's say-so): ejectVolume on a real stick → powered off + "safe to remove"; plug a
      stick in with auto-mount on (needs the rebuilt LaPivot + main() wiring).
- [ ] BLUETOOTH PAIRING (operator 2026-09-30): Lelan owns the org.bluez Agent1 (prompt in NCDE's
      Bluetooth tab, per docs). blueman (installed 2026-09-30 12:27, autostart
      /etc/xdg/autostart/blueman.desktop) is the stopgap until the rebuilt LaPivot ships; at ship time
      disable blueman's autostart (packaging) so there is exactly one agent.
- [ ] ORCHIDÉE (operator 2026-09-30; do right after LaPivot is finished, their order): the ⚜ Sovereign
      Seal and hidden files must sit behind a password so nobody can reveal and delete things. Today the
      seal toggles sealOpen with no password, and Ctrl+H / "Show Hidden Files" need none. Measured in a
      bwrap probe: sealOpen alone does not change entries() (17 entries, 0 dotfiles either way). Build in
      recovered OrchideeFiles source: an async unlockSeal() that asks polkit (new action, auth_admin =
      ask EVERY time the seal is opened, operator's choice), sets sealOpen only on success; hidden files
      shown only while the seal is open; shutting the seal hides them again; Ctrl+H/menu with the seal
      shut = the same password prompt. QML-only is impossible: nothing in orchidee returns a process
      result (Launcher: launchExec/launch/systemCommand/launchWithFiles only).

## Operator design decisions (2026-09-30)
- HANDS OFF ncde-portal (login/greeter/autologin): not rebuilt, patched or installed — "you break it all
  the time". Lelan's xdg-portal Settings read (dark mode/accent) is rebuilt ORACLE-EXACT, no changes.
- App Nap = PER-PROCESS PRIORITY (CPU nice + I/O priority per tier), apps stay in the logind
  session. Replaces cgroup scopes, which removed napped apps from the session (measured: pkcheck
  power-off / inhibit-block-sleep -> auth_admin_keep for a napped pid, yes for an in-session pid).
- Built-in speakers: EQ (laptop-speaker curve) + compressor + limiter, internal speakers only;
  headphones / HDMI / Bluetooth untouched; must adapt to every machine.
- Sentinel senses, Lelan decides, Zen (via Sentinel) acts — and sensing must be valid on ANY
  machine, not tuned to one.
