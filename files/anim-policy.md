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

AI / LLM layer — **present in this build, inside KickassGuard** **[EVIDENCE]**:
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
Governor vocabulary present in the binary: `reduceMotion`, `thermal`, `battery`, `onBattery`,
`vsync`, `refresh`, `idle`, `coalesce`, `pause`, `resume`, `presetActive`, `animActive`. **[EVIDENCE]**

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
