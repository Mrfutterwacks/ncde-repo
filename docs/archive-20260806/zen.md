# Zen — NCDE's Performance Governor — Manual

How NCDE stays smooth-under-load and battery-aware ("zen = the brain"). Reverse-engineered from
`ncde-wm` + `ncde-sentinel`. **[E]** = literal evidence in a binary; **[INF]** = inference.

> **Key correction (operator, 2026-06-30 night):** Zen is the linux-zen kernel NCDE ships and boots on
> — a real, load-bearing technical choice (its scheduler/tuning genuinely affects how the system runs),
> not a class, not "branding." Lelan and Sentinel are the controllers: they drive every aspect of the
> host BY USING Zen's built-in scheduling/power primitives (autogroup nice, SCHED_FIFO, cpufreq
> governors). Zen does not act on its own — it is the substrate Lelan/Sentinel act through. There is no
> `Zen*` class and no kernel detection: tuning is applied unconditionally, assuming `linux-zen`. The
> thing boosted is **the compositor process itself**, not the focused client window. **[E]**

---

## 1. Two actors
- **`ncde-wm`** (C++): self-boosts its own scheduling + monitors CPU-freq/thermal load, feeding
  `AnimPolicy` (animation governor — see `anim-policy.md`).
- **`ncde-sentinel`** (Python, `io.ncde.Sentinel`): the **only writer of cpufreq governor +
  vm.dirty_ratio**, driven by AC/battery udev events.

---

## 2. The knob table **[E]**

| Knob (path / syscall) | Value | When | Who |
|---|---|---|---|
| `sched_setattr(0, util_min)` (UTIL_CLAMP_MIN, keep policy/params) | **200/1024** boost · **0** release | `setAnimUtilClamp(true)` while animations run; `(false)` when idle/low-power | ncde-wm `LElan` |
| `/proc/self/autogroup` ← `"-5\n"` | autogroup nice **−5** | once at WM startup, on its own PID | ncde-wm `main()` |
| `sched_setscheduler(0, SCHED_FIFO, prio=1)` | **SCHED_FIFO prio 1** (lowest RT) | once at startup; best-effort (logs `AR: SCHED_FIFO(1) unavailable` w/o CAP_SYS_NICE) | ncde-wm `main::SchedFifoJob` |
| `ioprio_set(PROCESS, 0, IDLE\|7)` (`0x6007`) | IOPRIO_CLASS_IDLE | when draining deferred-idle work queue | ncde-wm `drainIdleQueue()` |
| `…/cpufreq/scaling_governor` ← | `schedutil` (AC) · `powersave` (battery) | every `power_supply` udev event + startup | **ncde-sentinel** `_apply_zen_hints` |
| `/proc/sys/vm/dirty_ratio` ← | `15` (AC) · `5` (battery) | same | **ncde-sentinel** |
| read `scaling_cur_freq` vs `cpuinfo_max_freq` | all cores pegged ⇒ pressure (debounced) | polling | ncde-wm `checkCpuFreq` |
| read `/sys/class/thermal/thermal_zone*/temp` | hot ≈ **89 °C** / clear ≈ **84 °C** (hysteresis) | polling | ncde-wm `checkThermalZones` |

**NOT present anywhere [E] (ORIGINAL, 2026-06-27 — see corrections below, most of this list is now stale):**
no THP/`transparent_hugepage`, `swappiness`, EPP/`energy_performance_preference`,
`irqbalance`, cgroup `cpu.weight`, `/proc/sys/kernel/sched_*`, BBR/TCP, polkit/pkexec helper, or boot
sysctl.d/systemd tuning unit. `etc/sysctl.d/` is empty; the only NCDE unit is user-scope
`ncde-sentinel.service`.

**Correction (2026-07-02) — re-verified against the real current source, not assumed:**
- **EPP is now real**, not absent. `ncde-zen-power.sh`'s `apply_epp()` sets
  `energy_performance_preference` with a defensive fallback chain, honoring
  `energy_performance_available_preferences`. Confirmed present in the live deployed script.
- **cgroup `cpu.weight` is now real**, not absent — see the "Real per-window resource tiering" note
  at the bottom of this file / `SetProcessTier` in `project-ncde-harmony-amiga-mission`. Built session
  49, live-proven 2026-07-02 (a real orphaned-scope bug found and fixed the same night — see that memory).
- `ncde-sentinel.service` is a **root system unit** now (`/etc/systemd/system/`), not user-scope —
  fixed session 46 (bus-mismatch fix). The line above describing it as "user-scope" is stale.
- Still genuinely absent, re-checked 2026-07-02: THP config wasn't re-checked (low priority), BBR/TCP
  still CUBIC-default (not enabled), no polkit/pkexec helper (not needed — root system service model
  replaced that need), no sysctl.d unit (the udev+service actuator replaced this design entirely).

---

## 3. "Foreground boost" = the compositor boosts ITSELF (3 layers) **[E]**
1. **Static at launch:** autogroup nice −5 (more CPU share vs other autogroups) + SCHED_FIFO prio 1.
2. **Dynamic:** `setAnimUtilClamp(true)` raises its own `uclamp.min` to 200/1024 **while animations
   play**, forcing the schedutil governor to ramp clocks instantly; clamps to 0 when idle.
3. **Back-off feedback:** all-cores-pegged (`checkCpuFreq`) or thermal zone > ~89 °C
   (`checkThermalZones`) → `emitThermalPressure()` → `thermalPressureChanged(true)` →
   `AnimPolicy::setThermalPressure(true)` → reduce/disable animations.

> No client process is ever reniced. `NCDEEngine::foreground()`/`FOREGROUND_THRESHOLD` are **theme
> color getters**, not process logic. **[E]**

---

## 4. Power-profile → knob mapping **[E]**
- **Governor/dirty_ratio: AC vs battery only.** `ncde-sentinel`'s own `_apply_zen_hints(on_battery)`
  is user-scope and its writes always EACCES-fail silently (harmless no-op, kept for signal-emission
  timing only). **The actual write happens via a separate root-context udev actuator, deployed
  2026-07-01:** `/etc/udev/rules.d/90-ncde-zen.rules` (`SUBSYSTEM=="power_supply", ACTION=="change"`)
  runs `/usr/local/lib/ncde/ncde-zen-power.sh` as root on every AC/battery transition, plus
  `ncde-zen-power.service` (oneshot, `WantedBy=multi-user.target`) applies it once at boot. Values:
  AC → `schedutil` + `dirty_ratio=15` (falls back through `ondemand`/`conservative`/`performance` per
  `scaling_available_governors` — e.g. this machine only exposes `performance`/`powersave`, so AC
  correctly lands on `performance`); battery → `powersave` + `dirty_ratio=5`. Verified live:
  `systemctl is-active ncde-zen-power.service` → active, `cat .../scaling_governor` → `performance`
  (AC, `ADP1/online`=1), `cat /proc/sys/vm/dirty_ratio` → `15`.
- **Animations: `net.hadess.PowerProfiles` `ActiveProfile`** via `LElan::onPowerProfilesPropertiesChanged`:
  only `"power-saver"` is matched → `AnimPolicy` low-power tier. `balanced`/`performance` collapse to
  the false branch. PowerProfiles is **not** mapped onto cpufreq/EPP — it only gates animations. **[INF]**
- Battery %/charging + thermal feed `AnimPolicy::setBatteryState()`/`setThermalPressure()` for further
  animation scaling. **[E]**

---

## 5. Rebuild notes
- ✅ **RESOLVED 2026-07-01** (was: `ncde-sentinel` needs privilege to write sysfs/proc, ran user-scope
  best-effort only). Fixed via the root-context udev actuator described in §4 above, not a polkit rule
  or capability grant — deployed and verified live.
- The self-boost needs `CAP_SYS_NICE` for SCHED_FIFO; degrades gracefully without it.
  **⚠️ LIVE-AUDIT CORRECTION (2026-07-07 session 82): "degrades gracefully" hid that the static
  self-boost tier has been DEAD on live the whole time** — observed on the running WM: autogroup
  `nice 0` (spec −5) and `SCHED_OTHER` (spec FIFO 1); both fail without CAP_SYS_NICE and the binary
  was never granted it. Fix: `sudo setcap cap_sys_nice+ep /usr/local/bin/LaPivot`; file caps are
  DROPPED by cp/mv deploys (re-setcap after every binary deploy) and must be applied in the ISO
  build (mksquashfs keeps xattrs). ALSO found: `ncde-zen-power.service` was disabled live with no
  enablement in the tree (§4's "verified active 2026-07-01" did not survive; live values were riding
  the udev coldplug replay) — tree now ships the multi-user.target.wants symlink; live needs
  `sudo systemctl enable ncde-zen-power.service`. Everything else in §2/§4 re-verified live-good
  same audit: governor performance×4 (AC, correct fallback), EPP performance, dirty_ratio 15,
  ThermalChanged observed on the bus, scx_bpfland running, tiering weights/freeze coherent.
  Full evidence: PRODUCTION-PUNCHLIST §0.13.
- Files: `usr/local/bin/ncde-wm` (LElan/AnimPolicy/SchedFifoJob/main), `usr/local/bin/ncde-sentinel`
  (`_apply_zen_hints`), `usr/lib/systemd/user/ncde-sentinel.service`,
  `etc/skel/.config/ncde/power.json` (blank/suspend timeouts only).

---

## 6. Darwin design-reference — why these knobs, together **[RESEARCH — VERIFIED 2026-06-23]**

The §2 knob table is the **disaggregation of one macOS QoS class**. Verified (run `wf_a632595b-b32`, 25
claims 3-0, 0 killed): a Darwin **QoS class is a single signal** that co-adjusts **CPU-scheduler priority,
I/O priority, the timer-coalescing window, AND a throughput-vs-efficiency CPU mode together** [Apple Energy
Guide; patents US 9,542,230 / 9,582,326]. NCDE splits that one value across:
- CPU priority → `SCHED_FIFO(1)` + autogroup nice −5 + `util_clamp` 200/1024
- I/O → `ioprio_set` IDLE
- timer window → one `Qt::CoarseTimer` (leeway/coalescing)
- CPU mode → `cpufreq` schedutil(AC) / powersave(battery)

**Correction for this doc:** Darwin's "throughput vs efficiency CPU mode" is a DVFS/core-selection *hint*,
so schedutil/powersave is **analogous, not identical**. And because Darwin makes QoS and explicit POSIX
scheduling **mutually exclusive**, NCDE applying all four knobs at once is a **re-implementation of the
behavior, not a port** — which is exactly right for a kernel-delegated design (NCDE, like libdispatch,
hands priority to the kernel rather than managing it in-process). Full mapping + openness/licensing +
the verified App-Nap/notifyd/IOKit analogies: **`anim-policy.md §2b`**.

---

## EFFICIENCY GAPS — spec-vs-code (2026-06-27 audit; full detail in `ncde-efficiency.md`)

This section describes what Lelan/Sentinel currently do and don't yet do with Zen's kernel primitives
(macOS = blueprint, built 100% open-source — no proprietary port). The audit found the self-boost half
present but the idle/throttle half dormant — i.e. Lelan/Sentinel aren't yet controlling everything they
should be:

- **Self-boost (present, verify):** the WM applies autogroup nice −5 + `SCHED_FIFO(1)` at startup and
  `uclamp.min` 200/1024 *while animating* (`applyZenStartupHints`). On the Le Pivot host, confirm these
  actually run (CAP_SYS_NICE) — they're what keeps frames smooth under load (QoS foreground tier).
- **GAP — background work is never demoted.** Spec (anim-policy.md §2 table) calls for Lelan's D-Bus/IO at
  reduced priority (`ionice` IDLE / `SCHED_IDLE` / autogroup) so the compositor always wins a busy CPU.
  Not implemented. ADD: demote Lelan's background subscription/IO threads.
- **GAP — the idle throttle that zen's efficiency depends on is never triggered.** `Lelan::setPulseScale`
  + `AnimPolicy::setScreenIdle` have **zero callers** (see `ncde-efficiency.md §1`), so the heartbeat never
  stretches and the cursor poll/stats never pause when idle — App-Nap is dormant. ADD an X11 idle source
  (XSync `IDLETIME` alarm) to drive them. **This is the highest-leverage efficiency fix and it's open-source
  end-to-end.**

The full pillar map (render-thread / App-Nap / work-on-change / coalescing / QoS / GPU compositor) and the
prioritized fix plan live in **`ncde-efficiency.md §6`**.

### EFFICIENCY GAPS — UPDATE (2026-07-01, sharper findings, don't re-derive)

The 2026-06-27 gap above about `setPulseScale`/`setScreenIdle` having zero callers was itself superseded
by session 38 (`ncde-efficiency.md §5`, "STATUS session 38") — that idle path is real and wired
(`sessionLocked || vtInactive || screenSaverActive`), not still-dormant. Don't re-flag it.

**A separate, distinct, still-genuinely-open gap was found 2026-07-01** — the chain-of-command Zen/Lelan/
Sentinel are supposed to form (operator: *"Sentinel is a watcher... it speaks to Lelan who controls
that... Lelan is the thing that controls all that Zen has to offer for NCDE/LaPivot"*) is not real yet:

- ~~**Sentinel emits `ThermalChanged`/`FanChanged`/`ThermalCritical`/`DriverMissing` — Lelan subscribes to
  none of them**~~ **FIXED 2026-07-02** (this session) — all 4 now subscribed in `Lelan_Bridges.cpp`.
  `ThermalCritical` feeds `m_thermalHot`→`updatePressure()`, the SAME path `checkThermalZones()`'s
  hardcoded 89°C/84°C poll already drives (additive, not a replacement — that poll still runs and still
  clears the flag on its own hysteresis). `ThermalChanged`/`FanChanged` populate new
  `sentinelTemps`/`sentinelFans` `Q_PROPERTY`s (real data, no QML surface built yet — separate follow-up).
  **Built + deployed to `/usr/local/bin/LaPivot` (sha `17a5f4db...`), confirmed on disk, NOT yet
  running/relogged as of this edit — verify the live pid before citing this as active.**
  **`AnimPolicy::setThermalPressure()` itself is STILL dead (zero callers)** — this fix routes through
  Lelan's own `m_thermalHot`/`recomputeAnimLevel()`→`setLevel()` path instead, deliberately, since that's
  the path `checkThermalZones()` already proved works; it does not touch the separate
  `AnimPolicy::setThermalPressure()` setter. Don't conflate the two — that setter is a distinct,
  still-genuinely-dead entry point.
- **Sentinel STILL violates the stated chain of command for governor/`dirty_ratio`** (re-verified
  2026-07-02, unchanged): `zen_hints.py`'s `apply()` is triggered by Sentinel's OWN AC/battery udev
  event, not by Lelan. Sentinel's D-Bus interface now HAS 2 real methods (`SetProcessTier`/
  `ClearProcessTier`, added for the tiering work below) but neither triggers `apply()` — governor/
  dirty_ratio is still Sentinel sensing+deciding+acting alone, Lelan never in the loop. Still open.
- **`AnimPolicy`'s `lowPower` oracle (`setLowPowerCpu/Profile/Memory/Battery`) STILL has zero callers
  anywhere** (re-verified 2026-07-02, unchanged) — its only reader (`Lelan.cpp:227` `drainIdleQueue()`)
  only ever fires from `screenIdle`, never from `lowPower`. Permanently `false`. Still open.
- ~~**No mechanism exists anywhere in the tree to control any process except LaPivot's own**~~
  **PARTIALLY FIXED — real per-window cgroup tiering now exists and is live-proven.** Built session 49
  (`SetProcessTier(pid,tier)`, root-side `StartTransientUnit`/`CPUWeight`/`cgroup.freeze` via Sentinel,
  called from Lelan on focus/minimize change via `_NET_WM_PID`). **Real bug found + fixed 2026-07-02**
  (this session): a Sentinel restart orphaned every already-tiered pid's scope (`_known` cache is
  in-memory only, doesn't survive restart), causing an infinite `UnitExists` retry-failure loop for
  every affected window — confirmed live in the journal (57 failures/2h), root-caused, fixed
  (`process_tier.py`'s `_create_or_adopt_scope`), redeployed, re-verified live with zero failures across
  a real restart + real focus/minimize events. Full detail: `project-ncde-harmony-amiga-mission`.
  Hardware-tier/capability detection (GPU vendor, "what kind of machine is this") — still genuinely
  absent, re-checked 2026-07-02, zero hits anywhere in the tree.

**Feasibility verdict (researched 2026-07-01, builds on the verified Darwin/App-Nap research above, does
not contradict it):** buildable, no architectural blocker. Root-privileged Sentinel can move any PID into a
cgroup v2 transient systemd scope (`CPUWeight=`/`cgroup.freeze`) on Lelan's request — the standard
`StartTransientUnit`/cgroup-delegation pattern (systemd.io/CGROUP_DELEGATION). Confirmed live: this host's
`/sys/fs/cgroup` is unified cgroup v2, systemd 261, all needed controllers present. **The one concrete
missing prerequisite:** Lelan never captures a client's PID at all (`_NET_WM_PID` unread anywhere — confirmed
by grep). Minimal build order: (1) Lelan reads `_NET_WM_PID` at `manage()`; (2) Sentinel gains real D-Bus
**methods** (currently zero) — e.g. `SetProcessTier(pid, tier)` — root-side, calls systemd's transient-scope
API; (3) Lelan calls it on occlusion/focus-change (state it already tracks in `AnimPolicy`).

Full technical detail, file:line citations, and the linux-zen kernel-capability research: auto-memory
`project-ncde-harmony-amiga-mission` (mirrored in `MEMORY.md`). Corrects the two dead `[[ncde-guardians-
are-the-amiga-chipset]]`/`[[ncde-per-app-resource-governor]]` links in `ncde-efficiency.md §5` — those
memories were referenced (session 25) but never actually written; `project-ncde-harmony-amiga-mission` is
the real one, use that.

### Real kernel-config ground truth (2026-07-01) — read directly off the live machine, corrects §2's table

NCDE ships ONLY `linux-zen` on the ISO, so what matters is this exact kernel's real, live config — pulled
from `/proc/config.gz` + live `/sys` state, not general web research about "zen vs stock." Corrections to
§2's knob table and new findings:

- **The §2 table's `scaling_governor ← schedutil (AC)` is the INTENT, not always the reality.** The real
  deployed actuator (`/usr/local/lib/ncde/ncde-zen-power.sh`) is already written defensively — it checks
  `scaling_available_governors` before writing and falls back (`schedutil → ondemand → conservative →
  performance`). **On `intel_pstate`-active-mode hardware (confirmed live on a test machine, an Intel
  Celeron N5095 — genuinely low-end, exactly the case the mission targets), `schedutil` isn't even an
  available governor** (`scaling_available_governors` = only `performance powersave`) — the actuator
  correctly falls back to `performance` for AC. Not a bug. But it means on this whole class of hardware,
  the governor knob barely does anything, and the REAL lever nothing currently touches is
  **`energy_performance_preference`** (`performance`/`balance_performance`/`balance_power`/`power` —
  currently sitting at `balance_performance`, never adjusted by Sentinel/Zen). New scope item.
- **BFQ is not a forced/hardcoded default** — live-checked: `[bfq]` active on eMMC/SD, `[kyber]` active
  on NVMe. Generic Linux block-layer per-device-queue-count heuristic, confirmed no NCDE/udev rule
  involved. Don't describe BFQ as "the zen I/O scheduler" in future docs.
- **THP: confirmed ON, mode `always`.** BBR: available as a module but **CUBIC is the real default** —
  BBR is not automatic, would need Sentinel to set it explicitly if wanted. zswap: on by default,
  compressor is zstd (not LZ4). CPU mitigations: ON, not stripped. MGLRU + futex2 + ntsync: all present
  and active.
- **Confirmed present, relevant to the build plan:** `CGROUP_FREEZER`, `UCLAMP_TASK`,
  `UCLAMP_TASK_GROUP`, `FAIR_GROUP_SCHED` — independently corroborates the cgroups-v2 feasibility
  verdict from the kernel config itself, not just systemd docs.
- **Also present, not proposed for use yet:** `SCHED_CLASS_EXT` (sched_ext, pluggable eBPF custom
  schedulers) — real capability, much bigger undertaking than the scoped cgroup plan, noted for
  awareness only.
