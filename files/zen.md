# Zen — NCDE's Performance Governor — Manual

How NCDE stays smooth-under-load and battery-aware ("zen = the brain"). Reverse-engineered from
`ncde-wm` + `ncde-sentinel`. **[E]** = literal evidence in a binary; **[INF]** = inference.

> **Key correction:** there is **no `Zen*` class and no kernel detection.** "zen" survives only as
> branding (the Python `_apply_zen_hints()` in ncde-sentinel + the `linux-zen.preset` mkinitcpio file).
> No `uname`/`/proc/version`/`.zen` check exists — tuning is applied **unconditionally**, assuming NCDE
> ships `linux-zen`. The governor is a **distributed self-tuning system** across two actors, and the
> thing it boosts is **the compositor process itself**, not the focused client window. **[E]**

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

**NOT present anywhere [E]:** no THP/`transparent_hugepage`, `swappiness`, EPP/`energy_performance_preference`,
`irqbalance`, cgroup `cpu.weight`, `/proc/sys/kernel/sched_*`, BBR/TCP, polkit/pkexec helper, or boot
sysctl.d/systemd tuning unit. `etc/sysctl.d/` is empty; the only NCDE unit is user-scope
`ncde-sentinel.service`.

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
- **Governor/dirty_ratio: AC vs battery only**, via udev → `_apply_zen_hints(on_battery)`:
  AC → `schedutil` + `dirty_ratio=15`; battery → `powersave` + `dirty_ratio=5`. Best-effort (skipped
  on EACCES if not root).
- **Animations: `net.hadess.PowerProfiles` `ActiveProfile`** via `LElan::onPowerProfilesPropertiesChanged`:
  only `"power-saver"` is matched → `AnimPolicy` low-power tier. `balanced`/`performance` collapse to
  the false branch. PowerProfiles is **not** mapped onto cpufreq/EPP — it only gates animations. **[INF]**
- Battery %/charging + thermal feed `AnimPolicy::setBatteryState()`/`setThermalPressure()` for further
  animation scaling. **[E]**

---

## 5. Rebuild notes
- `ncde-sentinel` needs privilege to write sysfs (`scaling_governor`) and `/proc/sys/vm/dirty_ratio`.
  It currently runs **user-scope** and writes best-effort — to make the governor switch actually take,
  run it (or a small helper) with the needed caps, or grant the sysfs paths. **[INF — current gap]**
- The self-boost needs `CAP_SYS_NICE` for SCHED_FIFO; degrades gracefully without it.
- Files: `usr/local/bin/ncde-wm` (LElan/AnimPolicy/SchedFifoJob/main), `usr/local/bin/ncde-sentinel`
  (`_apply_zen_hints`), `usr/lib/systemd/user/ncde-sentinel.service`,
  `etc/skel/.config/ncde/power.json` (blank/suspend timeouts only).
