# NCDE-SENTINEL-PLAN.md — the hardware guardian (rebuild/expand plan)

**Phase:** AFTER Lelan is finished (operator's order, 2026-06-26). This doc is the spec to work from then.
**Companions:** `zen.md` (the tuning Sentinel drives), `lelan.md`/`NCDE-LELAN-PLAN.md` (the hub it feeds),
`ncde-architecture.md`. **Evidence tags:** **[E]** verified in tree/binary · **[STD]** public Linux API ·
**[INF]** operator intent.

---

## 0. What Sentinel is — and is meant to become

**Operator intent (2026-06-26):** Sentinel **governs ALL the hardware** on the machine — the third
guardian beside **Lelan** (nervous system) and **Vesper** (security). The ethos: NCDE for
family/synagogue/Linux-averse users who **cannot troubleshoot** → the hardware must *just work*. "Linux
always promised plug-and-play; NCDE actually delivers it." Plug a device in → driver found/loaded; machine
heats up → fan responds; nobody ever opens a terminal. **[INF]**

**Family metaphor:** Sentinel = Lelan's **sister**, the child's **Tía/aunt** — the senses. **[INF]**

**Current artifact [E]:** `usr/local/bin/ncde-sentinel` (6.8 KB Python). It is a thin **udev→D-Bus bridge**
(`io.ncde.Sentinel`, session bus) emitting hotplug signals (Audio/Display/Battery/Network/Usb/Input) **+**
writing Zen's `cpufreq` governor + `vm.dirty_ratio` on AC/battery. **No temp reading, no fan control, no
hwmon, no driver detection, no periodic sensing.** That is the gap this plan closes.

**Architecture (confirmed):** Sentinel **senses** hardware → **informs Lelan** (`io.ncde.Sentinel`
signals Lelan's `subscribeToSentinel` fans out) **and acts as Zen's hands** (writes sysfs tuning). It does
NOT render UI; the tabs/widgets consume via Lelan. **[E/INF]**

---

## 1. The four capabilities → real mechanisms (all buildable)

### A. Sense everything — "lm_sensors, but it acts and is hardware-specific"
- **Auto-discover** every hwmon chip on *this* machine: glob `/sys/class/hwmon/hwmon*/` — **no hardcoded
  chip names** (adapts to whatever hardware it runs on). Match/label by the chip `name` file (hwmon
  numbers shuffle across reboots). **[STD]**
- Read: `tempN_input` (m°C → °C), `fanN_input` (RPM), `inN_input` (mV), `tempN_label`/`fanN_label`. **[STD]**
- **Periodic, coalesced poll** (Sentinel currently is event-only; sensors need polling) — one timer,低 rate
  (~2–5 s), so it stays light (matches Lelan's no-bog principle).
- Emit new signals → Lelan: `ThermalChanged(a{sd})` (label→°C), `FanChanged(a{su})` (label→RPM).
- Refs: [hwmon sysfs-interface](https://docs.kernel.org/hwmon/sysfs-interface.html).

### B. Find missing drivers (the novel, plug-and-play piece)
- Enumerate `/sys/bus/{pci,usb}/devices/*`. Each device has a **`modalias`**; it has a **`driver`
  symlink ONLY if a driver is bound**. **No `driver` symlink ⇒ driverless hardware.** **[STD]**
- For a driverless device: read `vendor`/`device` (PCI) or `idVendor`/`idProduct` (USB) + `modalias`;
  `modprobe --resolve-alias <modalias>` (or `/lib/modules/$(uname -r)/modules.alias`) → the module that
  *should* bind. Emit `DriverMissing(device, modalias, suggested_module)`.
- **Detect = safe + easy (do first).** **Auto-fix:** try `modprobe <module>` (privileged); if no module
  exists in-kernel, map to a package (the harder, networked step — pacman/AUR) → **later phase**, consent-gated.
- Ref: [Linux device model](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html).

### C. Thermal guardian — trigger fans when it heats up (the SAFE framing)
- **Not** a full custom fan curve. **Leave firmware/driver fan control in charge normally**
  (`pwmN_enable = 2`). **Only intervene** when a temp crosses *critical* AND the fan isn't already ramping:
  take manual control (`pwmN_enable = 1`), drive `pwmN` up, hold until cool, then **return to auto**.
- **MANDATORY fail-safe (the #1 hazard):** restore `pwmN_enable = 2` on **ANY** exit/crash/signal
  (SIGTERM/SIGINT/exception). A daemon that dies holding a fan low → overheat. Also a **never-off floor**
  (never write `pwm=0`). Match pwm to its chip by `name`. **[STD — this is exactly what fancontrol/thinkfan guard against]**
- Active custom curves = **opt-in only** (most firmware already manages fans fine; for the NCDE audience the
  guardian/backstop is the right default, not aggressive control).
- Refs: [ArchWiki Fan speed control](https://wiki.archlinux.org/title/Fan_speed_control),
  [kernel pwm-fan](https://docs.kernel.org/hwmon/pwm-fan.html).

### D. Keep the existing hotplug + Zen hints
- Retain the current udev signals (Audio/Display/Battery/Network/Usb/Input) and `_apply_zen_hints`
  (governor + dirty_ratio). These already work [E]; fold into the expanded daemon.

---

## 2. Run-model — the real upgrade ("more than a small script")
- **Privileged root system service.** Writing fans (`pwm*`), the cpufreq governor, and loading modules
  (`modprobe`) all need root — the current best-effort *user* service silently fails these (zen.md flags it).
- Bridge to the desktop the way `kickass-guard` does: **root system service**, exposing `io.ncde.Sentinel`
  where **Lelan (user session) can reach it** — either keep it on the session bus via
  `DBUS_SESSION_BUS_ADDRESS` bridging (kickass-guard model), or move to the **system bus** and have Lelan
  subscribe there (Lelan already self-heals both buses via `onSystemNameOwnerChanged`). **[DECISION]**
- Alternative for the read/zen-only parts: a udev rule + `tmpfiles`/polkit granting the specific sysfs
  nodes to the user service — lighter, but doesn't cover `modprobe`. Root service is cleaner for the full vision.

---

## 3. D-Bus surface — additions (Lelan subscribes)
Keep the 9 existing signals; add:
- `ThermalChanged(a{sd})` — sensor label → °C (package/core/GPU/…).
- `FanChanged(a{su})` — fan label → RPM.
- `DriverMissing(s device, s modalias, s suggestedModule)` — driverless hardware found.
- (optional) `ThermalCritical(s sensor, d tempC)` — crossed critical; guardian engaging.
- Lelan side: extend `subscribeToSentinel` (already wired for the 9 hotplug signals) with handlers for the
  above → fold thermal into `m_thermalPressure`/AnimPolicy (replacing Lelan's own `checkThermalZones` peek
  with Sentinel's richer feed), surface fans/driver-missing to the relevant widgets. **[INF]**

---

## 4. Phases (safe-first; same edit→audit→harness-test loop as Lelan)
1. **Phase 1 — sensing (SAFE):** hwmon temp/fan/voltage auto-discovery + coalesced poll + `ThermalChanged`/
   `FanChanged`. Test against `sensors`/`/sys/class/hwmon`. Zero risk.
2. **Phase 2 — driver detection (SAFE):** enumerate driverless devices + `DriverMissing`. Test vs `lspci -k`/`lsusb`.
3. **Phase 3 — thermal guardian (RISK):** pwm backstop with fail-safe + never-off floor. Test carefully on
   real hardware; verify auto restored on exit. Opt-in for custom curves.
4. **Phase 4 — auto-fix drivers (LATER, networked):** `modprobe` the suggested module; map to package +
   consent-gated install. Needs network + pacman + care.
5. **Run-model:** convert to privileged root service; wire Lelan to the new signals.

## 4b. Language — Python, one daemon (operator Q, 2026-06-26)
**Keep Sentinel in Python; do NOT rewrite to C++ or split C++/Python.** Its whole job — udev
(`pyudev`), sysfs read/write, `modprobe`, shelling to `pacman`/`yay` — is Python's sweet spot, and it's a
background daemon (no perf-critical path, so the "feels light"/C++ argument doesn't apply). It talks to
Lelan (C++) over D-Bus regardless of language. (kickass-guard is C++ only because it embeds the LLM
engines.) "C++ + Python scripts" = worst of both.

## 4c. Auto-driver provisioning (operator vision, 2026-06-26) — the plug-and-play concierge
Goal: on install AND on hotplug, the right driver is present — like `ncde-command` finds/installs software,
but hardware-triggered. **Honest reframe so it's built right:**
- **Linux already auto-loads MOST drivers** — the kernel ships them as modules and udev `modprobe`s them by
  `modalias` when hardware appears. USB mouse/keyboard/most devices **need zero install** — already plug-and-play.
- **Sentinel fills the GAPS:** out-of-tree/DKMS drivers + **firmware** (some Wi-Fi/GPU/fingerprint/printer).
  Flow: detect driverless device (§1.B: modalias + no `driver` symlink) → map device→package → **install via
  `pacman` (consent-gated)**; `linux-firmware` covers most firmware.
- **Driver priority (operator, 2026-06-26):** (1) the **specific in-kernel module** (udev auto-loads — already chip-specific, e.g. `i915`/`iwlwifi`), (2) the **specific Arch package** for that exact device (`pacman`: firmware/DKMS), (3) a **generic driver ONLY as last resort** when Arch has no specific package (e.g. `modesetting`/`vesa`). **Never settle for generic if a proper Arch driver exists.**
- **Install-time pass:** scan all hardware, ensure driver/firmware packages present (first-boot unit).
- **Prior art:** Manjaro **`mhwd`** does exactly auto-detect+install — mine it. The hard part = the
  device→package map (research when building this phase).
- **Caveat (Vesper's turf):** `yay`/AUR = untrusted builds → prefer official repos; AUR auto-install stays
  consent-gated. Shares `ncde-command`'s pacman/polkit install path.

## 4d. EC fan control for EC-only laptops — research + plan (operator request, 2026-06-26)

**Trigger — live evidence [E] (dev machine, 2026-06-26):** the dev laptop is a **Jumper J1 16"**,
**Intel Jasper Lake** (`pinctrl_jasperlake`), DMI `product_name="Default string"` (whitebox BIOS). A deep
probe found **NO Linux-visible fan interface**: no `fan*`/`pwm*` in any hwmon chip; thermal cooling devices
are only `Processor` (passive throttle) + `intel_powerclamp`, **no `Fan` cooling device**; nothing under
platform/ACPI. The fan is real but the **EC owns it entirely** — the kernel has zero handle on it. Cooling
today = firmware + passive CPU throttling + Intel DPTF (`INT3400 Thermal`). So Sentinel's hwmon path
(§1.A/§1.C) correctly reports **0 fans** here and pwm control is impossible via sysfs. **Goal (operator):**
add an EC-fan path so NCDE delivers working fan read/control on *this exact model*, with a per-model
framework that generalizes to other EC-only laptops.

**Mechanism (researched — NBFC-Linux model):** poke the **embedded controller (EC) registers** directly.
- **Kernel access**, pick one: `ec_sys` (needs kernel param `ec_sys.write_support=1`) [preferred] ·
  `acpi_ec` (DKMS; works under Secure Boot / Lockdown) · `dev_port` (`/dev/port` fallback). Selectable via
  nbfc `--embedded-controller=` or `/etc/nbfc/nbfc.json`.
- **Config = JSON** with: the EC **read** register (fan RPM), the **write** register (fan speed),
  `ReadWriteWords` (data width), `FanSpeedPercentageOverrides` (%→raw map), `TemperatureThresholds`
  (`UpThreshold`→`FanSpeed` steps), and `CriticalTemperature` (hard safety cutoff). nbfc-linux applies the
  *next* threshold's FanSpeed once temp exceeds the current `UpThreshold`.

**Reverse-engineering THIS model's config (the real work — no existing config for a whitebox):**
1. Load the EC backend (`ec_sys.write_support=1`).
2. `ec-probe dump` → baseline the 256 EC bytes. *(confirm exact `ec-probe` subcommand syntax against the
   tool's `--help` when building — README was light on specifics; treat dump/monitor/read/write as the
   conceptual workflow, not verified flags. [SEARCH])*
3. `ec-probe monitor` while toggling load (`stress`) vs idle → find the byte that **tracks RPM** (read reg)
   and the byte(s) that **change fan state** (write reg).
4. Map fan-speed % → raw values → `FanSpeedPercentageOverrides`.
5. Write the JSON; test **read-only first** (`nbfc restart -r`, `nbfc status` shows RPM), then write mode,
   then `nbfc set -s <speed>` / `nbfc set --auto`. Verify RPM reporting + auto curve responds to temp.

**Safety — MANDATORY (the #1 hazard, same as §1.C):**
- Always start **read-only**; never write a register blind.
- **Fail-safe:** on ANY exit/crash/signal, return the fan to **firmware/auto** — never leave it forced
  low/off (overheat). Plus a **never-off floor**. nbfc helps (preallocates memory, `oom_score_adj=-1000`);
  NCDE must still guarantee the restore-to-auto on stop.
- Keep firmware + DPTF as the **default** cooler; EC fan control is **opt-in**. `CriticalTemperature` in the
  config as a hard backstop.

**Shipping it "for others with this exact laptop":**
- Once verified, **bundle the config** in NCDE keyed to the model. **Problem:** DMI = `"Default string"`
  (whitebox) → can't fingerprint on `product_name`. Need another key (board/EC signature, or match the
  discovered register layout, or first-boot detection). **[SEARCH]** the device→config map; mine **Manjaro
  `mhwd`** + the **nbfc `Configs/`** set as prior art.

**Sentinel integration (decision deferred):** (a) fold the verified EC read/write into Sentinel's own
thermal guardian (one guardian, our code), or (b) have Sentinel **manage `nbfc-linux` as a backend**
(install/enable/supervise it, read its RPM). Either way: `FanChanged` then reports the EC-read RPM, the
§1.C fail-safe rules bind, and it stays opt-in. Run-model = the privileged root service (§2).

**Research TODO (added to the Sentinel list):** exact `ec-probe` syntax · any existing nbfc config matching
this Jasper Lake whitebox · reliable model fingerprint for `"Default string"` BIOS · `ec_sys` vs `acpi_ec`
for NCDE's Secure-Boot stance · Manjaro `mhwd`/nbfc `Configs` as the device→package/config map.
Refs: [nbfc-linux](https://github.com/nbfc-linux/nbfc-linux), [ArchWiki Fan speed control](https://wiki.archlinux.org/title/Fan_speed_control).

## 4e. Reference-device enablement matrix — Jumper J1 16" (Jasper Lake whitebox) (operator, 2026-06-26)

**Why:** the dev machine is becoming NCDE's **budget-hardware reference device**. Several of its devices
"never worked on Linux" (operator; documented online for the Jumper J1). Sentinel's mission (§0: hardware
*just works*) → ship the enablement so anyone with this exact machine gets a working NCDE. **Live probe [E]
2026-06-26:**

| Device | Probed identity [E] | Status | Likely fix (to verify [SEARCH/STD]) |
|---|---|---|---|
| **Touchscreen** | `MSSL1680` = **Silead**, on I²C + ACPI (`i2c-MSSL1680:00`) | **detected, NOT working** — no touchscreen input device created (only the touchpad) | `silead` driver + **firmware** `silead/mssl1680.fw` (MISSING in `/lib/firmware/silead`) + device props (touchscreen-size-x/y, max-fingers). Whitebox DMI=`"Default string"` blocks the kernel `touchscreen_dmi.c` quirk → must supply props via DMI/ACPI quirk or shipped config. |
| **Auto-rotation** | dual **Kionix** accels `KIOX010A`+`KIOX020A` → `iio:device0/1` **bound** | accels WORK in kernel; **no auto-rotate** | install **`iio-sensor-proxy`** + compositor rotation; mount-matrix per panel orientation. |
| **Tablet/flip mode** | dual-accel (base+lid) convertible; `BOSC0200` also in ACPI (no iio) | no `SW_TABLET_MODE` seen | hinge-angle from the two accels, or a tablet-mode quirk — research dual-accel handling. |
| **Camera(s)** | `OVTI9234` (OV IR) + `OVTID858` MIPI sensors | likely **not working** (MIPI/**IPU6**) | Intel IPU6 stack + libcamera + softisp — known hard gap; later phase. |
| **Fan** | EC-only, no hwmon/pwm | see §4d | nbfc/EC reverse-engineer (§4d) |
| **Touchpad** | `HTIX5288` (Himax) | **works** (input device present) | — |

> **Confirmed [INF] (operator, 2026-06-26): the touchscreen WORKED under Windows.** So the panel + Silead
> controller are good and the firmware/config ship in the Windows driver → this is purely a **software
> enablement gap**, and the firmware is **extractable** (mount the machine's Windows partition / pull the
> Silead `.fw` + the INF/registry props). Not dead hardware.

**Touchscreen plan (headline — Silead MSSL1680):**
1. Confirm `silead` module loads + the controller addr (`i2c-MSSL1680:00`).
2. Source the **firmware** (`mssl1680.fw` / `silead_ts.fw`) — usually extracted from the Windows driver →
   `/lib/firmware/silead/`. **[SEARCH the exact name + a redistribution-safe source.]**
3. Supply **device properties** (X/Y max, finger count, axis inversion). Whitebox can't DMI-match → options:
   (a) kernel DMI quirk on a stabler field, (b) **ACPI `_DSD` override** (SSDT overlay via `acpi_override`
   in initramfs), or (c) a shipped silead config.
4. Verify a touchscreen input device appears + `evtest` shows touches; calibrate axes.
5. **Ship for others:** bundle firmware + props/quirk in NCDE keyed to the J1 (same whitebox-fingerprint
   problem as §4d).

**Sentinel integration:** this is §1.B/§4c driver-enablement at its fullest — Sentinel detects "device
present on I²C/ACPI but no input/driver bound" → maps to an **enablement bundle** (firmware + props +
package) → applies consent-gated. **The Jumper J1 becomes the first entry in Sentinel's device→enablement
map.** Auto-rotation = also a Sentinel concern (install/enable iio-sensor-proxy + drive rotation).

**Research TODO (Sentinel list):** Silead `mssl1680.fw` exact name + lawful source · the J1 touchscreen
X/Y/finger params (online reports exist — operator) · `_DSD` override vs DMI-quirk vs config on whitebox ·
`iio-sensor-proxy` packaging in NCDE · dual-accel tablet-mode handling · IPU6 camera stack (later).
Refs: ArchWiki Touchscreen, kernel `touchscreen_dmi.c`, linux-surface / Silead community configs.

## 5. Build / test
- Expand the Python `ncde-sentinel` (develop/test sudo-free first; fold into
  `~/my-project/files/ncde-full-patch-20260711.sh` for the operator to apply — there is no separate
  staging tree anymore, the live system is the source of truth). Deps already present: `pyudev`,
  `dbus`, `glib`. hwmon/pwm = plain sysfs reads/writes (no new deps).
- **Test each phase against live hardware** (this machine has real hwmon — `sensors` is the ground truth),
  exactly like Lelan was verified against `nmcli`/`bluetoothctl`/`wpctl`.

## 6. Open decisions
- Session-bus-bridge vs system-bus for the root service (§2).
- Critical-temp thresholds + hysteresis (reuse zen.md's 89/84 °C, or per-sensor crit from `tempN_crit`).
- Fan control default: guardian-only (recommended) vs opt-in custom curve.
- Auto-install drivers: how far to go (modprobe-only vs package install) + consent UX.
