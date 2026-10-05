# ncde-efficiency.md — NCDE resource/animation efficiency (audit + spec + fix plan)

**Created 2026-06-27 (session 16).** Purpose: NCDE must be **ultra-fast and efficient on ANY hardware,
old or new** — that is Lelan's entire reason to exist. This doc is the canonical efficiency reference: the
model NCDE was designed to, the audit of where the code doesn't follow it (spec-vs-code), and the
prioritized fix plan. Pairs with `anim-policy.md` (the governor + Darwin mapping) and `zen.md` (kernel).

> Method note: findings below come from a full read-only audit performed 2026-06-27 against
> `~/ncde-staging/compass7/lelan/` (Lelan + host C++) and `/usr/share/ncde/` (desktop QML), cross-checked
> against the written specs. **Corrected 2026-07-17: `~/ncde-staging/` no longer exists — the dev machine
> that hosted it is gone. The findings below still hold as diagnosis; there is no separate tree to re-run
> this audit against anymore, only the live system and the partial `~/ncde-wm-rebuild/` reconstruction.**
> Discipline applies to every fix: read → backup → one change → diff → rebuild+verify; system paths via
> operator sudo; never edit `[dead-legacy-tree]` directly.

---

## 0. THE MODEL (what NCDE was designed to — its own docs)

- **Moksha / Evas (the X11 lightweight reference):** retained-mode — **redraws/recomputes ONLY the
  portions that actually changed**; work happens **on change, not every frame**; runs in **<100 MB**.
  → NCDE rule: **sample/compute once, cache, redo only on real change.**
- **Open Darwin / macOS (`anim-policy.md §2b`, "NCDE = Linux OSX"):** **App-Nap** (throttle/​pause idle &
  background), **Timer-Coalescing** (one coarse heartbeat, not N pollers), **QoS** (foreground keeps the CPU).
  → NCDE mapping: **Lelan = the coalescing hub; AnimPolicy = the governor; throttle hard when idle.**

NCDE's architecture *implements* this (one 1s coalesced heartbeat, async D-Bus, a governor with idle/level
inputs). The failure is that **the throttle was never connected** (see §1).

---

## 1. ROOT CAUSE — the idle/throttle machinery is built but NEVER triggered (HIGH, systemic)

**`AnimPolicy::setScreenIdle(bool)` and `Lelan::setPulseScale(int)` both exist and have ZERO callers
anywhere in the tree.** Confirmed by all three audits.

- `screenIdle` is therefore **permanently `false`**. The QML gates everything on `!animPolicy.screenIdle`
  (**27 sites**) and `live: !animPolicy.screenIdle` → all constant-`true` → **nothing ever pauses.**
- Lelan **receives** every idle/lock signal it needs — `onScreenSaverActivated` (Lelan.cpp:1770),
  `onSessionLock`/`Unlock` (1194-1195), session `Active==false` (1190-1192) — and **does nothing** with
  them except re-emit a QML signal. The 1s heartbeat + `/sys` thermal/cpu reads keep firing **even when
  locked or VT-switched away.**
- `recomputeAnimLevel()` (Lelan.cpp:1587) pushes a battery/thermal *level* to AnimPolicy but **never calls
  `setPulseScale()`** to actually stretch the heartbeat, and **there is no idle detector at all.**

**Spec-vs-code:** `anim-policy.md` says decorative/idle work degrades under the governor and pauses when
idle; the **idle input was never wired** → the entire App-Nap half is dormant. (`thermalPressure`/`level`
ARE wired — only the **idle** path is dead.)

**The two fixes that revive it:**
- **(A)** Add an X11 idle source — **XSync `IDLETIME` alarm (event-driven, zero poll)** or coarse
  `XScreenSaverQueryInfo` — in Lelan/WM; on idle call `animPolicy.setScreenIdle(true)` + `lelan.setPulseScale(4..8)`;
  reverse on activity. Also call `setPulseScale` on battery from `recomputeAnimLevel`. Instantly activates
  the 27 QML gates, stops the cursor poll, slows stats/clock/heartbeat.
- **(B)** Convert static `live:` samplers to `live:false` + resample-on-change (real Moksha pattern) —
  needed regardless of (A), because the glass sources are static (see §2).

---

## 2. QML — continuous GPU work over STATIC sources (HIGH; biggest single win)

Moksha rule broken: glass re-samples + re-blurs a wallpaper that never changes, every frame, forever.

| file:line | what | sev |
|---|---|---|
| `NCDEGlassSurface.qml:54` | shared shell glass (BottomPanel/TopPanel/Dock) `live:` samples static wallpaper + `MultiEffect` Gaussian blur (blurMax 64) — **3+ full-screen sample+blur passes @60fps** | **HIGH** |
| `NCDEGlass.qml:45` | `live:` ShaderEffectSource over a **static `Image` of the wallpaper PNG** — a static PNG reblurred @60fps | **HIGH** |
| `NCDEGlass2.qml:42` | desktop-widget wallpaper glass, same pattern (+3 MultiEffect shadow passes :119/133/146) | HIGH |
| `NCDETerminalGlass.qml:43` | full terminal glass; **docstring says `live:false` "sample once" but code is `live:!screenIdle`** (comment lies) | HIGH |
| `NCDETerminalMenuGlass.qml:63` | menubar strip (semi-static, moves on drag) | MED |

**Fix:** `live: false` + explicit `bgSource.scheduleUpdate()` on the only real triggers — `width/height`
change, `backgroundSource` change, `ncde.onWallpaperChanged`, panel-move/screen-geometry change. Turns
continuous GPU into one-shot-on-change. **This is the single biggest speedup.**

### 2b. Always-on animations / canvas pumps gated only on the dead `screenIdle`
- `SpacePanel.qml:166` + `SpaceWidget2.qml:99` — `FrameAnimation{ running: !screenIdle }` drives a **full
  Canvas `requestPaint()` every vsync FOREVER, even when the widget is hidden** (comment refuses a
  `visible` gate). **HIGH** → gate on real visibility (`Loader.active`/shown state), not just screenIdle.
- `SalonNocturneCompact.qml:99` — `Timer{ interval:33; running: salon.visible }` repaints a Canvas at 30fps
  **even when nothing is playing**. **MED-HIGH** → add `&& widget_data.mediaPlaying`.
- `SpaceWidget.qml` (4 infinite SequentialAnimations), `StatsPanel/MuchaStats/SNPetalVisualizer`
  FrameAnimations — correct intent (gated on `visible && !screenIdle`) but never pause (screenIdle dead);
  fixed automatically by §1(A).

### 2c. MotifFrame glow re-blurs every frame (MED-HIGH; epilepsy-careful)
`MotifFrame.qml:174-288` — ~7 `layer.enabled + MultiEffect{blur}` glow items whose `border.color` is bound
to `lampPulse.val` (animates every frame while focused) → **each MultiEffect re-renders its offscreen
texture every frame.** Fix that PRESERVES the epilepsy-safe flicker: drive the flicker via **`opacity`**
on a static-colored glow rect (composites the *cached* blur at new alpha — no re-blur). **Do NOT change
`lampPulse` timing/values/curves** (memory [[ncde-motif-glow-candle-flicker]] / [[ncde-never-touch-animations-or-mpris]]).

---

## 3. Lelan — blocking calls + signal storms

- **Blocking D-Bus on the GUI thread (HIGH):** `mediaPlayPause/Next/Previous` (Lelan.cpp:1480/1487/1494)
  use blocking `.call()` → a hung browser stalls the UI on every media key. → `.asyncCall()` (matches
  `mediaSeek` :1508). `refreshPrinters` (Lelan.cpp:930) does `waitForFinished(2500)` → up to **2.5s GUI
  freeze** at startup + on printer changes → parse `lpstat` in `QProcess::finished`.
- **Signal storms / full re-enumeration (MED-HIGH):** `onWifiPropertiesChanged` (596) rebuilds **all APs**
  (`GetAll` ×15-30) on every `LastScan`; `readActiveNetwork` emits `wifiChanged` **4×** per refresh;
  `onBlueZPropertiesChanged` (1702) + `onUDisks2FilesystemPropertiesChanged` (1707) do full
  `GetManagedObjects` on every micro property change. → patch the single changed entry; debounce; emit once.
- **LOW:** `recomputeAnimLevel` called unconditionally every 60s (1584); thermal/cpu `/sys` polled on AC+idle;
  9 one-shot timers default PreciseTimer (use `Qt::CoarseTimer`; the multi-hour night-light timer 1683 →
  `VeryCoarseTimer`).
- **Good (keep):** one coalesced 1s `CoarseTimer`, async D-Bus everywhere else, no per-widget pollers.

---

## 4. Host C++ — polling + load-path stalls

- **Cursor poll (HIGH on host path):** `NCDEWindowManager.h:109-116/356-366` — 62 Hz `QCursor::pos()` =
  **blocking `xcb_query_pointer`** every 16ms, forever. → event-driven via XInput2 `XI_RawMotion` through
  the existing `nativeEventFilter`; drop the timer. *(Bails on the dev desktop — `start()` returns false —
  so it only bites on the Le Pivot/host path.)*
- **`WidgetData::readStats` (MED-HIGH):** reads ~7 `/proc`+sysfs files every 3s regardless of panel
  visibility/idle. → gate on `statsVisible` + `!screenIdle`; drop to 30-60s when hidden. (also: static
  regex, break meminfo loop early, skip clock-blink emit when idle.)
- **`NCDEEngine::recompute()` (MED):** full derive + **double signal** (`changed`+`themeChanged`→Canvas
  repaint) on **every** setter → color-wheel drag = N recomputes. → coalesce behind `QTimer::singleShot(0)`;
  hoist constant brand colors (`m_verd/cer/rose/amber`) out of the per-call path.
- **`.desktop` scans on the load path (MED):** `GliaSystemMenus` (ctor) + `AppMenuModel` parse 100-300
  `.desktop` files synchronously **before first paint**. → defer to after first frame / worker thread.
- **LOW:** `manage()` does a discarded `xcb_get_geometry` (skip when maximized); serial atom interns +
  `scanExisting` round-trips (pipeline cookies then read); `NCDECalendar` reminder timer ticks every 60s
  with zero appointments (start only when appts exist; `VeryCoarseTimer`).
- **Note:** `CursorManager` is **not instantiated in `main.cpp`** — currently dead code.

---

## 5. PRIORITIZED FIX PLAN (master list)

> **STATUS (session 25, 2026-06-28) — MEASURED ON THE LIVE HOST + the design model locked:**
> Live `top`/`ps -L` of the running `ncde-test` (mouse stationary): **~155% CPU**, and it is **NOT the cursor
> poll** — it's the **orrery `Canvas` repainting every vsync**: main thread 77.6% + QQuickContext2D 44.7% ≈
> **122% wasted** on pixel-identical frames (SpaceWidget2.qml:99 + SpacePanel.qml:168, `FrameAnimation` with
> NO visibility gate). The cursor 16ms `QCursor::pos()` poll (NCDEWindowManager.h:134) is secondary (latency).
> **DESIGN MODEL (operator):** Lelan/Zen/Sentinel = NCDE's **Amiga custom chipset**; vision = **per-app/per-window
> App-Nap** (only OPEN+VISIBLE things use resources: WM occlusion → Lelan/AnimPolicy pause, Zen cgroup CPU/RAM,
> Sentinel thermal). **Acceptance test = "seamless, no visible change."**
> *(Correction 2026-07-01: the two memory links this line used to point to — `[[ncde-guardians-are-the-
> amiga-chipset]]`/`[[ncde-per-app-resource-governor]]` — were referenced here since session 25 but never
> actually written anywhere; they were dead links. The real memory is auto-memory
> `project-ncde-harmony-amiga-mission`, written 2026-07-01. Use that one.)*
>
> **STATUS (2026-07-01) — WHAT IS ACTUALLY DONE vs. NOT DONE on this vision, verified against the live
> tree, not notes (full file:line detail + sources in `project-ncde-harmony-amiga-mission`):**
> - ✅ **DONE — WM occlusion pause for the orrery.** `recomputeDesktopObscured` → `AnimPolicy::
>   setDesktopObscured` (session 25, this file's step 1) — the one piece of "only open+visible uses
>   resources" that's real today.
> - ✅ **DONE — Sentinel senses real hardware well**, generically, no dev-machine hardcoding: hwmon
>   auto-discovery, udev hotplug (6 subsystems), driverless-device detection.
> - ❌ **NOT DONE — "Zen cgroup CPU/RAM."** Zero cgroup usage anywhere in the tree. No per-window/per-app
>   resource differentiation exists at all — every real kernel-level call in Lelan only ever targets its
>   own process (self, pid 0).
> - ❌ **NOT DONE — "Sentinel thermal" reaching Lelan.** Sentinel emits `ThermalChanged`/`FanChanged`/
>   `ThermalCritical`/`DriverMissing`; Lelan subscribes to none of them (`Lelan_Bridges.cpp:36-51`) and
>   runs its own separate, cruder, hardcoded-89°C/84°C poll instead.
> - ❌ **NOT DONE — the `AnimPolicy` low-power oracle has no callers.** `setLowPowerCpu/Profile/Memory/
>   Battery()` exist, fully built, never invoked anywhere. Permanently inert.
> - 🔴 **ACTIVE VIOLATION, not just a gap — Sentinel currently decides+acts on its own** for governor/
>   `dirty_ratio` (its own AC/battery udev trigger), bypassing Lelan entirely; it also has no D-Bus
>   *methods* at all, so it structurally cannot take a command from Lelan yet either way.
> - 🟢 **RESEARCHED, NOT YET BUILT — the fix is fully scoped and feasibility-confirmed** (2026-07-01):
>   (1) Lelan needs to read `_NET_WM_PID` per client at `manage()` (confirmed absent, zero hits); (2)
>   Sentinel needs real D-Bus methods (e.g. `SetProcessTier(pid, tier)`) to receive commands, using
>   systemd's standard `StartTransientUnit`/cgroup-v2-delegation pattern (`CPUWeight=`/`cgroup.freeze`) —
>   confirmed this host's `/sys/fs/cgroup` is unified v2, systemd 261, no architectural blocker; (3) Lelan
>   calls that method on occlusion/focus-change, state it already tracks. **Not started — no code written
>   yet for any of these three.**
> **STEP 1 SHIPPED TO ncde-test (built `6cfeed52`, sha-verified on disk, PENDING relog-proof):** orrery
> `desktopObscured` gate — WM (`recomputeDesktopObscured` → `AnimPolicy::setDesktopObscured`) tells the
> governor when a maximized window covers the desktop; the pump gates `!screenIdle && !desktopObscured`.
> Keeps the operator's defensive `!screenIdle` gate; pixel-identical (a covered widget can't be seen).
> Cursor → HARDWARE Xcursor next (via `CursorManager`, currently dead/stubbed) — "merge Kith into the X11
> cursor, don't mask"; moots the tip-clip + the poll. Then Zen per-app cgroups + Sentinel thermal.
>
> **STATUS (session 16, superseded — see session 38 below):** ~~✅ DONE+build-verified: idle throttle (Lelan
> `applyIdleState` → setScreenIdle/setPulseScale on lock/screensaver/VT/battery)~~ — this description is
> WRONG per `step3-idle-source.md` session 21: `setScreenIdle`/`applyIdleState`/`setPulseScale` were all
> later found to be session-16b **inventions**, not real oracle behavior, and were REMOVED and replaced
> (see below). · **async media transport** · **async printers** (no GUI stalls) — these two still stand.
> 🟡 STAGED+lint-clean, needs operator visual verify: **shell glass `NCDEGlassSurface.qml` → `live:false`**
> — superseded, see below (this is now fully DONE + matches live).
>
> **STATUS (2026-06-30, session 38) — items #1 and #2 re-verified against actual current source, not notes:**
> - **#1 Glass live:false** — 4 of 5 files done (`NCDEGlassSurface.qml` live+staging match; `NCDEGlass.qml`
>   staged; `NCDEGlass2.qml`/`NCDETerminalGlass.qml` fixed this session). `NCDETerminalMenuGlass.qml` left
>   alone — it's unwired/dead code (not instantiated anywhere in the tree; superseded by Verda Terminae's
>   own built-in terminal glass, per operator).
> - **#2 idle throttle — DONE**, but via a real, different, better-designed system than this doc's plan
>   described (`setScreenIdle`/`setPulseScale` never actually existed as real oracle behavior — see
>   `step3-idle-source.md`). Current: `AnimPolicy::screenIdle = sessionLocked || vtInactive ||
>   screenSaverActive` (all 3 inputs wired — XScreenSaver via WM native filter, VT via logind session
>   `Active` in `Lelan_System.cpp:449`, lock via D-Bus). Heartbeat-stretch (Part C) was superseded by a
>   `deferWhenIdle()`/idle-work-queue system instead of slowing the shared coalesced timer. Builds clean.
> - **Correction (2026-06-30 night):** #3 and #10 are DONE, verified against current source — remove from
>   REMAINING. #3: `NCDEWindowManager.h:129,450-453` implements XI_RawMotion event-driven cursor feed
>   (poll is fallback-only now). #10: `SalonNocturneCompact.qml:95` already gates
>   `running: widget_data.mediaPlaying && salon.visible && !animPolicy.screenIdle`.
> - ⬜ REMAINING (verified still open 2026-06-30 night): readStats visibility-gate (#4 —
>   `WidgetData.h:100` calls `readStats()` unconditionally every 3s, no gate), signal-storm patches (#6),
>   defer .desktop scans (#7), coalesce NCDEEngine.recompute (#8 — `NCDEEngine.h:230` etc. still called
>   directly on every setter, no `singleShot` coalescing), vsync-pump visibility gates (#9 — partially
>   done, `SpacePanel.qml`/`SpaceWidget2.qml` desktopObscured gate synced staging==live this session),
>   MotifFrame glow→opacity (#11, epilepsy-careful), LOW sweep (#12).


1. **Glass → `live:false` + resample-on-change** (NCDEGlassSurface, NCDEGlass, NCDEGlass2,
   NCDETerminalGlass[+Menu]). *Biggest GPU win; touches no animation/MPRIS.* [QML, root tree → operator sudo]
2. **Wire the idle throttle** — X11 idle source → `AnimPolicy.setScreenIdle` + `Lelan.setPulseScale`
   (+ battery in `recomputeAnimLevel`). *Activates all 27 QML gates, stops cursor poll, slows heartbeat/stats.*
3. **Cursor feed event-driven** (XI_RawMotion) — host path only. [NCDEWindowManager.h]
4. **`readStats` gate on visible+idle**, slow when hidden. [WidgetData.h]
5. **Async the blocking Lelan calls** — media transport `.asyncCall`; printers drop `waitForFinished`.
6. **Stop full re-enumeration on micro-signals** (WiFi/BlueZ/UDisks2); coalesce `wifiChanged`.
7. **Defer `.desktop` scans** off load path (GliaSystemMenus, AppMenuModel).
8. **Coalesce `NCDEEngine::recompute()`**; hoist constant brand colors.
9. **Gate the always-on vsync pumps on real visibility** (SpacePanel/SpaceWidget2 FrameAnimation).
10. **SalonNocturneCompact** repaint Timer `&& widget_data.mediaPlaying`.
11. **MotifFrame glow via `opacity`** (cached blur) — preserve lampPulse timing exactly (epilepsy).
12. **LOW sweep:** CoarseTimer on one-shots, skip discarded geometry, pipeline interns, calendar timer
    start-when-appts, static regex.

**HARD CONSTRAINTS (project rules — non-negotiable):**
- **AESTHETIC IS SACROSANCT — it is NCDE's whole identity; NEVER changed.** Every efficiency fix must be
  **pixel-identical**: change *how* the same image is produced (cache vs recompute, throttle only when the
  user isn't looking), never *what* is shown. If a fix can't be proven visually identical, it is skipped.
- **Epilepsy:** never alter `lampPulse` timing/curves (only what property it drives, and only if pixel-identical).
- **MPRIS:** never touch the Salon scrubber/position path.

**Fixes #1-#3 are pixel-identical by construction** (cache/throttle/plumbing) and deliver the large majority
of the speedup with no change to a single visible pixel and no animation/MPRIS code touched.

**Where fixes land (corrected 2026-07-17 — the staging tree below is gone):** QML lives in
`/usr/share/ncde` — edit directly (or a staged copy) + operator `sudo cp` to apply, OR embed in the
host qrc; C++ fixes go through the Ghidra-reconstruction workflow in `~/ncde-wm-rebuild/` (per-class
status in `docs/lapivot-rebuild.md`), not a `~/ncde-staging/compass7/lelan/` checkout. Every fix folds
into `~/my-project/files/ncde-full-patch-20260711.sh` for deploy. Build gate holds: no ISO until host
done + audited.

---

## 6. THE EFFICIENCY RECIPE — macOS as blueprint, built 100% open-source

**NCDE is a Linux desktop. macOS is the *blueprint*, never the target and never a copy.** macOS feels fast
because of *how* it spends cycles, not raw speed — so NCDE re-implements that **behavior** using **only
open-source Linux/Qt/X11 primitives** (XSync, Qt's render thread, picom, `sched_setattr`/cgroups,
XScreenSaver). **No Apple/proprietary code is ported — only the proven pattern, rebuilt the open way**
(zen.md: "re-implements the behavior, not a port"). End-result bar: **clean and commercial-grade** — a
polished, shippable product with Linux invisible underneath. Six pillars:

| # | macOS mechanism | NCDE / Linux implementation | status |
|---|---|---|---|
| 1 | Core Animation off-main-thread, vsync | Qt Quick **threaded render loop + `Animator`** (render-thread, vsync) — motion never stalls under CPU load | **HAVE** — enforce Animator rule (`anim-policy.md §1`) |
| 2 | **App-Nap** (do nothing when idle) | X11 **idle detector** (XSync `IDLETIME` alarm = event-driven) → `AnimPolicy.setScreenIdle` + `Lelan.setPulseScale`: pause glass sampling, stop cursor poll, stretch heartbeat 4-8s, slow stats | **DISCONNECTED → fix #2** |
| 3 | Repaint only the dirty region | **work-on-change**: `live:false` glass + resample-on-change, cached blurs, coalesced recompute (Moksha/Evas retained-mode) | **→ fix #1 (biggest GPU win)** |
| 4 | Timer-Coalescing | **one coarse 1s heartbeat** + `CoarseTimer`/`VeryCoarseTimer` + `setPulseScale` stretch on idle/battery | **mostly HAVE; wire stretch + fix PreciseTimers** |
| 5 | **QoS** (foreground gets CPU) | **zen**: compositor self-boost (autogroup −5, `SCHED_FIFO`, `uclamp.min` while animating); background (Lelan D-Bus/IO) demoted (`ionice`/`SCHED_IDLE`) | **partly HAVE (`applyZenStartupHints`) — verify + add bg demotion** |
| 6 | WindowServer/Quartz GPU compositor | **picom** + GPU scene graph, effects on GPU, vsync | **HAVE** (picom-watch added; ensure GL backend) |

**Punchline:** pillars 1/4/6 are largely in place. The two that actually make NCDE *feel* like macOS —
**App-Nap idle governor (2)** and **work-on-change glass (3)** — are this audit's top-2 fixes. zen (5) is the
QoS layer beneath. So "make NCDE OSX-on-Linux efficient" == ship fix #1 + #2 (+ verify zen).
