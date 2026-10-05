# NCDE Animation Governor (`AnimPolicy`) + the "lelan-compliant" model

Companion to `lelan.md`. This is the **animation/optimization half** of the nervous system:
how NCDE stays efficient (battery/thermal) **without animations ever appearing stopped or
stalled** — the macOS-style behavior — built **with what NCDE already has** (X11 + picom, Qt Quick,
the `LElan → AnimPolicy` contract, the linux-zen kernel).

Tags: **[EVIDENCE]** = verifiable in the `ncde-wm` binary / tree. **[INTENT]** = operator's design
description + architectural inference. **[RESEARCH]** = how the equivalent works elsewhere (cited).

---

## 0. NCDE anatomy — the mental model **[INTENT]**

> **The WM + desktop = the body & skeleton. `Lelan` = the nervous system. `Zen` = the brain.**
>
> **Operator's family metaphor:** Lelan = **mother** (wife of Zen, sister of Sentinel), Zen = **father**
> (linux-zen, NCDE's only kernel), Sentinel = **Tía/aunt** (her sister — the hotplug feed), NCDE = the
> **child**. One organism — "if mamma is gone nothing gets done."

- **Body/skeleton** — `ncde-wm` + the desktop UI (`usr/share/ncde`, the glass surfaces, panels,
  widgets). Structure and surfaces.
- **Nervous system — `lelan`** — the single shared hub that senses every system service and carries
  signals to the body. Components don't wire their own backends; they are **"lelan-compliant"**:
  they consume `lelan` signals and let `lelan` own the subscription. (See `lelan.md`.)
- **Brain — `zen`** — the linux-zen kernel + its scheduler features that decide *priority* (what runs
  now, what waits), so the body stays responsive under load.

**"lelan-compliant" = a component routes its system I/O through `lelan` instead of polling backends
itself.** Confirmed compliant today **[EVIDENCE]**:
- **KickassGuard** (security): `usr/local/bin/kickass-guard` + `org.ncde.KickassGuard` dbus;
  `LElan::subscribeToKickassGuard()`, `onKickassThreatBlocked/Behavioral`, `kickassArmed/Changed`.
- NetworkManager, BlueZ, UDisks2, PowerProfiles, PackageKit, MemoryMonitor, PortalSettings,
  SessionLock, VtActive, MPRIS players, tray, geoclue→weather/time (see `lelan.md` §4–5).

**SUPERSEDED (operator, 2026-06-30 night): Vesper no longer uses LLMs.** The `OllamaClient`/
`VesperBrain`/Qwen-model section below is real evidence from the OLD `ncde-wm` binary — it genuinely
existed — but the operator has stated multiple times that this LLM-based design is abandoned. Do not
treat it as the current target architecture. Early non-LLM prototyping once existed at `~/ncde-staging/vesper/brain/cards.json`/`brain_nollm.py`
and may have reflected the real direction, but that path is gone now (the dev machine that hosted
`ncde-staging` no longer exists, confirmed 2026-07-17) — that evidence is unrecoverable. The
actual current design has not yet been captured from the operator — ask him, do not infer it from
these files. Section kept below for historical/evidence reference only.

AI / LLM layer — **present in the OLD binary, inside KickassGuard — ABANDONED DESIGN, see note above**
**[EVIDENCE — historical]**:
- **`OllamaClient`** (in `usr/local/bin/kickass-guard`): local-Ollama client —
  `generate(prompt, model, system)`, `embed()`, `listModels()`, `checkAvailability()`; returns
  generated `QJsonObject` verdicts and embeddings (`QList<float>`).
- **`VesperBrain`**: the LLM brain — `initModel()`, `onAnalysisReady(id, QJsonObject)`; turns a
  `ThreatContext` into a `ThreatVerdict` (custom **Qwen** model per operator — model is passed to
  `generate()`, so it's configurable). **[model name = INTENT; plumbing = EVIDENCE]**
- **`ChromaClient`**: a ChromaDB vector store — embeddings land here → "it learns the system"
  (baseline + retrievable memory of events).
- **`NftEngine`** enforces **"block other UIDs from reaching local Ollama"** — KickassGuard *guards*
  the local LLM endpoint (only the authorized UID reaches it).
- Already **lelan-compliant**: `LElan::subscribeToKickassGuard()` + `kickassThreatBlocked/Behavioral`
  carry its events into the nervous system via the `KickassAdaptor` dbus interface.

---

## 1. Why animations never stall (the key principle) **[RESEARCH + maps to our stack]**

The optimization **never touches the animation path** — that's the whole trick.

- **macOS:** Core Animation advances animations **off the main thread**, on the GPU compositor
  (WindowServer/Quartz), synced to the display. If the main thread blocks, the animation still runs
  smooth. [Core Animation], [WindowServer]
- **NCDE has the direct equivalent:** Qt Quick's **threaded render loop** advances animations on the
  **scene-graph render thread, throttled to vsync** (one frame per vblank, ~16.67 ms). [Qt Scene Graph]
- **The primitive that guarantees it:** Qt **`Animator` types** (`OpacityAnimator`, `ScaleAnimator`,
  `XAnimator`, `YAnimator`, `RotationAnimator`) run on the **render thread**, so they keep moving even
  when JS/the GUI thread is busy. Plain `NumberAnimation`/`PropertyAnimation` run on the GUI thread
  and *can* stutter under load.

> **RULE for the rebuild:** anything that must **never stall** (the recovery progress bar, panel
> reveals, the glass-surface transitions, anything visible during heavy work) → use an **`Animator`**.
> Reserve `NumberAnimation` for cheap, non-critical, idle-time motion. Both stay vsync-throttled.

---

## 2. Where optimization actually happens — the "switch" **[RESEARCH → our stack]**

macOS saves power in the **background/data layer**, not the UI: **App Nap, Timer Coalescing, QoS
classes** batch wakeups and deprioritize background work so the CPU idles "while users detect no
change in responsiveness." [App Nap], [Timer Coalescing], [QoS], [Timers]

That is exactly **`lelan`'s reason to exist** — one shared, coalesced subscription hub instead of N
per-widget pollers. Mapping to what we have:

| macOS mechanism | NCDE-with-what-we-have |
|---|---|
| Core Animation off-main-thread | Qt **threaded render loop** + **`Animator`** (Qt 5.15 & Qt 6 both in tree) |
| Display-synced frames | **picom `vsync = true`** (X11); DRM vsync on `eglfs` (recovery, no picom) |
| Timer Coalescing | `QTimer` **`Qt::CoarseTimer`** + **batched** lelan polling (one tick → many reads); give timers tolerance |
| App Nap / QoS priority | run lelan's dbus/IO threads at lower priority (`nice` / `SCHED_IDLE` / `ionice`) — **zen scheduler = the brain** |
| Thermal-state notifications | `LElan(int) → AnimPolicy(int)` level (already wired) |
| Foreground gets the resources | compositor/UI thread stays default priority; only background work is demoted |

**Net:** lelan coalesces and demotes background work (battery/thermal win), while the vsync'd render
thread keeps the body smooth (responsiveness win). The two never fight.

### 2b. Darwin / macOS internals — the design reference (concepts, NOT a port) **[RESEARCH — VERIFIED]**

> **Status: the deep-research pass is DONE** (2026-06-23, run `wf_a632595b-b32` — 108 agents, 25 claims
> 3-vote-verified, 0 killed). It **confirms** the analogies below and sharpens them. ⚠️ The **launchd/XPC**
> row alone produced **zero** surviving claims — treat it as **unverified/open**, not confirmed. Numeric
> constants are Apple 2013-Mavericks *conceptual* values (illustrative only, NOT live 2026 XNU numbers).

**The key insight (verified):** on Darwin a **QoS class is ONE signal** the system uses to co-adjust four
things at once — **CPU-scheduler priority, I/O priority/throughput, the timer-coalescing window, and a
throughput-vs-efficiency CPU mode** [Apple Energy Guide; patents US 9,542,230 / 9,582,326]. A QoS class
is a packed `pthread_priority_t` bitfield (class + relative priority) carried in thread-local storage
[darwin-libpthread `src/pthread.c`], and libdispatch routes it through **12 root queues → kernel
pthread-workqueue priority bands** — the **kernel**, not userspace, does the actual scheduling
[aosm/libdispatch `src/queue.c`].

⟹ **NCDE deliberately DIS-aggregates that one QoS value into separate Linux knobs — and that's the
faithful move, not a shortcut.** On Darwin, QoS and explicit POSIX scheduling are **mutually exclusive**
(set explicit sched params and the kernel *disables* QoS auto-management), so NCDE using `sched_setattr`
util_clamp **and** autogroup nice **and** `SCHED_FIFO` **and** `ioprio` together is something Darwin
*couldn't* express as one QoS. **NCDE re-implements the behavior; it does not — cannot — port the mechanism.**

| Darwin mechanism (verified) | What it really is | NCDE knob — the disaggregated equivalent |
|---|---|---|
| **QoS class** (User-Interactive≈prio 33 … Background≈9; one packed value) | the single signal driving sched-priority + I/O + timer-window + CPU-mode together | the WHOLE policy bundle below — compositor = interactive tier, **Lelan** D-Bus/IO = utility/background |
| ↳ CPU-scheduler priority | kernel workqueue band | `SCHED_FIFO(1)` + autogroup nice −5 + `util_clamp` 200/1024 (zen) |
| ↳ I/O priority/throughput | per-task I/O band | `ioprio_set` IDLE on Lelan's background IO |
| ↳ timer-coalescing window | `dispatch_source_set_timer` **`leeway`** (bounded `MIN(leeway, interval/2)`); **flag** `DISPATCH_TIMER_STRICT` opts out | one `Qt::CoarseTimer` (default; ~5% **early** tolerance, collapses overruns to one fire) for background reads; `Qt::PreciseTimer` for must-not-stall motion |
| ↳ throughput-vs-efficiency CPU mode | a DVFS/core-selection *hint* (NOT a governor swap) | `cpufreq` schedutil(AC)/powersave(battery) — **analogous, not identical** |
| **App Nap** (3 levers: timer-throttle, I/O-throttle, priority-reduce; **never** for foreground) | background demotion, foreground exempt | maps ~1:1 → CoarseTimer/longer leeway · `ioprio` IDLE · autogroup nice / lower util_clamp |
| **`notifyd` / `notify(3)`** central hub (name-keyed, **payload-FREE**; 4 delivery transports) | one daemon fans a named event to all subscribers | the **Lelan fan-out** shape. ⚠️ difference: D-Bus signals carry *typed payloads* and **don't coalesce natively**, so Lelan must coalesce *explicitly* at the hub (one CoarseTimer tick drains many signals) |
| **IOKit** `IONotificationPortCreate` + `IOServiceMatching(class)` + CFNumber attrs + `IOServiceAddMatchingNotification(kIOFirstMatchNotification)` + run-loop source | hardware-hotplug source = macOS's udev | **`ncde-sentinel`**: IOServiceMatching class ≈ udev `SUBSYSTEM`; CFNumber vendor/product ≈ `ATTRS{idVendor/idProduct}`; run-loop source ≈ `udev_monitor` netlink fd in the Qt loop; `kIOFirstMatchNotification` ≈ udev `add` |
| **launchd / XPC** — ⚠️ **UNVERIFIED** (0 surviving claims; needs its own pass) | lazy/socket activation + per-process service decomposition | D-Bus activation + "Lelan hub in-process, `kickass-guard` separate root daemon" (treat as hypothesis) |

**Doc-corrections this pass forced:** (1) it's the creation-time **flag `DISPATCH_TIMER_STRICT`**, not a
function `dispatch_timer_strict()`; (2) `Qt::CoarseTimer`'s ~5% tolerance is bounded on the **early** side
only (late firing is allowed and unbounded when busy) — no symmetric ±5% guarantee; (3) schedutil/powersave
is **analogous** to Darwin's throughput/efficiency CPU mode, not identical.

**Openness (what NCDE may actually READ vs only reference):** directly readable, OPEN —
**swift-corelibs-libdispatch** (Apache-2.0), **Libnotify**, **IOUSBFamily/IOKitUser**, **darwin-libpthread**.
Historically open — **launchd/liblaunch** (APSL). Effectively closed — **modern libxpc**. (Qt6 owns our
event loop regardless, so these stay *design reference* — read for understanding, never linked.)

**Use:** when grounding a Lelan/Zen scheduling or coalescing decision, reach for this verified
QoS + leeway + App-Nap vocabulary rather than re-deriving it. *(Still owed — its own pass: the launchd/XPC
row, live 2026 XNU constants, and the concrete "one CoarseTimer tick drains many D-Bus signals" pattern.)*

---

## 3. `AnimPolicy` — the governor **[EVIDENCE for wiring, INTENT for levels]**

**Wiring seen in `ncde-wm`:**
```
connect< LElan::(bool) , AnimPolicy::(bool) >          // a toggle: reduce-motion / on-battery
connect< LElan::(int)  , AnimPolicy::(int)  >          // a LEVEL (0/1/2…)
connect< LElan::()     , AnimPolicy::()     >          // re-evaluate trigger
connect< QFileSystemWatcher::(QString) , AnimPolicy::(QString) >  // watches a reduce-motion setting file
connect< QTimer::() , AnimPolicy::() >                 // periodic re-evaluation
DesktopWidget::setAnimPolicy(AnimPolicy*)              // installed into the widget layer
NCDEWindowManager::setAnimPolicy(AnimPolicy*)          // …and the WM
```
**Correction (2026-06-30 night audit):** the line below was `strings` output on the OLD `ncde-wm`
binary and listed tokens scattered across several unrelated classes as if they were all `AnimPolicy`
symbols — `presetActive` belongs to `NcdeTheme`/`NCDEEngine`, `onBattery` is a `Lelan` parameter name,
not an `AnimPolicy` member. **Current LaPivot `AnimPolicy.h`'s real property set:** `level`,
`reduceMotion`, `idleLoops`, `decorative`, `instant`, `screenIdle`, `thermalPressure`, `lowPower`,
`desktopObscured` — no `vsync`/`coalesce`/`pause`/`resume`/`animActive`/`presetActive`/`thermal`/
`battery`/`onBattery` in this class. Also: the `DesktopWidget::setAnimPolicy` wiring shown above is
OLD-BINARY evidence — current LaPivot has **no `DesktopWidget` class at all**; only
`NCDEWindowManager::setAnimPolicy` exists. That old widget-level wiring has not been rebuilt yet.

Old-binary `strings` dump (historical, do not treat as current AnimPolicy symbols): `reduceMotion`,
`thermal`, `battery`, `onBattery`, `vsync`, `refresh`, `idle`, `coalesce`, `pause`, `resume`,
`presetActive`, `animActive`. **[EVIDENCE — old binary only]**

**Inputs → a level (from `LElan`):** on-battery, thermal pressure (`thermalPressureChanged`),
low-battery (`batteryChanged`), the reduce-motion setting (file-watched), idle. **[EVIDENCE: signals]**

**Proposed level model — degrade quality, never halt [INTENT]:**

| Level | Trigger | What changes (decorative only) | Essential transitions |
|---|---|---|---|
| **0 Full** | AC power, cool, not idle | all idle loops, particles, glows, full FPS | always vsync-smooth |
| **1 Reduced** | on battery / warm / idle | drop idle shimmer & particle loops, cap FPS, longer/cheaper easing | unchanged, smooth |
| **2 Minimal** | low battery / thermal-critical / reduce-motion | motion → instant or single cross-fade; no continuous loops | unchanged, smooth |

The cuts always land on **decorative, looping** work (shimmer, particle fields, the celestial idle
shimmer in the recovery bar) — the **essential** transitions stay on the vsync'd render thread, so
the user perceives lower *motion*, never a *stall*. That's the macOS thermal behavior reproduced.

---

## 4. Make it real — concrete settings with what we have **[INTENT, grounded in our stack]**

1. **picom:** `vsync = true` (one render per vblank — smoothness + caps GPU spin). `etc/picom.conf`.
2. **Qt render loop:** leave the **threaded** loop as default on capable GPUs; Qt 6.4+ auto-falls back
   to system timers if frames present "too fast," so animations stay correct without burning CPU.
   Only force `QSG_RENDER_LOOP=basic` if a target truly lacks vsync.
3. **Animator rule (§1):** critical/visible-under-load motion → `Animator`; idle fluff →
   `NumberAnimation` and let `AnimPolicy` switch it off at level ≥1.
4. **lelan as the coalescer:** one shared `QTimer` (CoarseTimer) for polled sources; batch dbus reads;
   never let a rebuilt QML re-introduce per-widget timers (that defeats the switch).
5. **zen priority:** lelan's background subscription/IO work at reduced scheduler priority so the
   compositor/UI always wins a busy CPU.
6. **AnimPolicy as a QML-readable level:** expose `property int level` (+ `reduceMotion` bool) so QML
   bindings choose animation richness; widgets read `animPolicy.level` instead of guessing.

**Recovery app specifically:** on `eglfs`/`linuxfb` (desktop dead, no X, no picom) there is one
fullscreen window; vsync comes from DRM and `Animator` still runs on the render thread — so the
restore progress bar stays smooth even though `ncde-wm`/picom aren't running. The recovery app should
default to **AnimPolicy level 1** (it runs in a degraded/emergency context) but keep the progress
animation on an `Animator` so it never appears frozen mid-restore.

---

## 5. Sources **[RESEARCH]**
- Core Animation (off-main-thread, GPU compositor): https://grokipedia.com/page/core_animation
- macOS WindowServer (central compositor): https://andreafortuna.org/2025/10/05/macos-windowserver/
- Qt Quick Scene Graph (threaded render loop, vsync, Animator): https://doc.qt.io/qt-6/qtquick-visualcanvas-scenegraph.html
- Qt 6.4 FrameAnimation / render-loop auto-fallback: https://www.qt.io/blog/new-in-qt-6.4-frameanimation-element
- macOS App Nap: https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/AppNap.html
- macOS Timer Coalescing: https://appleinsider.com/articles/13/06/18/os-x-mavericks-new-app-nap-timer-coalescing-features-target-battery-efficiency
- macOS QoS / task priority: https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/PrioritizeWorkAtTheTaskLevel.html
- macOS thermal-state response: https://developer.apple.com/library/archive/documentation/Performance/Conceptual/power_efficiency_guidelines_osx/RespondToThermalStateChanges.html
- picom (vsync, X11 compositor): https://github.com/yshui/picom · https://wiki.archlinux.org/title/Picom
- prefers-reduced-motion: https://web.dev/articles/prefers-reduced-motion
