# Lelan — what the designer needs to deliver in the next zip

**OBSOLETE (2026-06-30 night audit) — everything this checklist lists as "MUST fill" is already done
in the current `~/ncde-staging/LaPivot/compass7/lelan/` tree.** (That path is a description of what
was true on 2026-06-30 — the tree, and the dev machine that hosted it, no longer exist as of
2026-07-17. Kept as-written for historical accuracy; don't go looking for that path today.) All 18
`subscribeTo*()` bodies are
implemented (verified via `grep -n "void Lelan::subscribeTo"` across `Lelan_{Network,Media,Devices,
System,Bridges}.cpp`), Sentinel wiring is done (`Lelan_Bridges.cpp:36-64`), and the `ncde`/`lelan`
object-split decision (§B.1 below) is resolved — `main.cpp` injects both as separate context properties.
**Do not use this doc to plan new work — it describes a pre-fix snapshot (`lelan-fixed.zip`) that
predates the current tree. Redoing or reverting anything here would undo working code.** Kept for
historical reference only; the one still-genuinely-open item from this era is PackageKit's `GetUpdates()`
call (see `lelan-research-findings.md` §6).

**Start from `lelan-fixed.zip`** (build-blockers already fixed: link-blocker slot bodies, missing
includes, signal/slot rename — don't redo those). Full detail: `NCDE-LELAN-PLAN.md`, `lelan.md`,
`missing.md`. Lelan is **pure C++**, no QML file of its own; injected as `lelan` + `ncde`.

## A. MUST fill — the 15 `subscribeTo*()` bodies (the real work)
Each = the 5-step pattern (async fetch → `bus.connect(signal→slot)` → cache `m_…` → `emit …Changed()`
→ re-sub). Exact D-Bus names are **verified** in the plan §3 / lelan.md §4–5. Order:
- **Batch A (first):** NetworkManager · Audio (**libpulse**, NOT PulseAudio Core1 — Core1 is absent on
  pipewire-pulse; `lelan-research-findings.md §2`) · MPRIS (per-player `PlayerState`, `Position` via
  `Seeked`+interpolation) · logind (Lock/Unlock, Active, PrepareForSleep).
- **Batch B:** UPower (finish the live slot) · PowerProfiles · portal.Settings (accent parse) · BlueZ
  (ObjectManager) · UDisks2 (`Drive.Removable` → `removableVolumes`).
- **Batch C:** PackageKit · GeoClue2 (Location→place/weather/moon) · timedate1/hostname1/locale1 ·
  ScreenSaver · MemoryMonitor · Notifications · KickassGuard-subscribe.
- **NCDE Sentinel** (NCDE's OWN service — add `subscribeToSentinel()`): `io.ncde.Sentinel`,
  path `/io/ncde/Sentinel`, iface `io.ncde.Sentinel` — a udev→D-Bus hardware bridge already shipping
  in the tree (its code names "L'élan" as consumer). Signals → Lelan mapping:
  `DisplayConnected(s)`/`DisplayDisconnected(s)`→`screenConfigChanged`; `UsbDeviceAdded/Removed(ss)`
  + `InputDeviceAdded/Removed(s)`→device/storage refresh; `AudioDeviceChanged(ss)`→`audioDeviceChanged`;
  `BatteryStateChanged(bi)`→`batteryChanged`; `NetworkStateChanged(sb)`→`networkChanged`. (Complements
  the freedesktop daemons with NCDE's own hotplug feed.)
- **Also:** point each service's `PropertiesChanged` at its REAL handler slot (the 2 reference impls
  currently connect to a placeholder).

## B. DECISIONS to make and tell us (these change the build)
1. **`ncde` vs `lelan`** — one object under two names, or two separate objects? (rebuild assumes TWO.)
2. **Integration** — ship Lelan as a small standalone companion, or compile it **into `ncde-wm`**?
3. ✅ **Audio path — RESOLVED:** target runs pipewire-pulse (no D-Bus module) → Core1 absent. Use
   **libpulse** (Waybar `audio_backend.cpp` model; WirePlumber is the documented alternative). See
   `lelan-research-findings.md §2/§7`.
4. **`AudioVolumeArray`** element type (vs sink `Volume` `au`) + **`accent-color`** `(ddd)`→QColor parse.

## C. INCLUDE in the zip
- Updated `Lelan.h` / `Lelan.cpp` (+ `NcdeTheme.h` if `ncde` tokens change).
- A one-line note of which `busctl introspect` outputs you verified against (so we can spot drift).
- *(optional)* a tiny `Shell.qml` that prints `lelan.*` / `ncde.*` for eyeball testing.

## D. Build note
Needs `cmake` (operator installs once): `cmake -S lelan -B build && cmake --build build`. Qt6 +
headers are present in the tree.

## Not in scope here (separate tracks)
KickassGuard daemon (its own manual `kickass-guard.md` + the `vesper:latest` model) and the missing
runtime packages (`build-the-missing.md`) — Lelan only *subscribes* to KickassGuard.
