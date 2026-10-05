# NCDE-LELAN-PLAN.md — rebuild Lelan (the nervous system) to ship

> **✅ STATUS (2026-06-23, session 5): the rebuild is DONE + runtime-verified.** All gaps below are
> filled in `~/ncde-staging/compass7/lelan/`, it compiles clean, and audio(libpulse)/MPRIS/tray(SNI)/
> Zen-watchdog/portal were verified against the LIVE system. Faithfulness confirmed — the real `ncde-wm`
> binary has the same `TrayWatcher` + `scheduleNightLightEvents(double,double)` we rebuilt. Source is
> being restored to `[dead-legacy-tree]/src/` (where it lived). Details: `SESSION_HANDOFF.md §SESSION 5` +
> `~/ncde-staging/compass7/lelan/README.md`. The §3 batch list below is kept as the historical plan.

> **⚠️ CORRECTED 2026-07-17 — `~/ncde-staging/` no longer exists.** The dev machine hosting
> `compass7/lelan/` is gone; confirmed absent on this machine and the USB backup. The 2026-06-23
> status above is historical — it was true then, not now. Current recovery path: Lelan's C++ lives
> inside `/usr/local/bin/LaPivot`, reconstructed class-by-class (partial, most classes still raw
> Ghidra output — see `docs/lapivot-rebuild.md`) in `~/ncde-wm-rebuild/`. The live system is the
> source of truth; fixes deploy via `~/my-project/files/ncde-full-patch-20260711.sh`.

Authoritative plan for finishing **Lelan**, NCDE's system nervous system. Lelan is the critical
path: every desktop surface binds to it, so nothing reports real state until it's wired. **Do Lelan
before recovery** (recovery is an independent lifeboat; Lelan is what the whole desktop depends on).

**Deep specs:** `lelan.md` (full backend map + recipes), `missing.md` (exact handler slots + the
`ncde` vs `lelan` split), `anim-policy.md` (the governor it drives), `ncde-architecture.md` (where it
sits). **Concept:** Lelan = a *watcher that watches the watchers* — it subscribes once to every system
daemon, tracks them via D-Bus `NameOwnerChanged`, coalesces, and fans signals out to the QML
(the "mouths"). It is **pure C++**, injected as context properties — **no QML file of its own.**

---

## 0. Why Lelan + Zen — the point (design rationale)
NCDE is a **heavy** desktop (mail, calendar, organizer, conky-style dashboard w/ weather+moon,
notification server, global menu/HUD, file mgr, P2P messenger, Gmail client, AI security, glass
surfaces, ~15 backends). Lelan + Zen are what let it carry that weight without the "Windows bog":
- **Lelan keeps idle cost LOW (the "switch").** One coalesced D-Bus hub instead of 15 widgets each
  polling → rare wakeups, flat idle RAM/CPU. **Push, don't poll** — the original already did this
  (evidence: all-`subscribeTo*` + ONE coarse timer + `Connections{target:lelan}`). **Cardinal rule:
  never reintroduce per-widget polling** (any stub reaching for a per-service `QTimer` is the
  regression to catch).
- **Lelan = self-preservation watchdog (anti-freeze).** It monitors **RAM** (MemoryMonitor
  `LowMemoryWarning`), **CPU** (`checkCpuFreq` all-cores-pegged), **thermal incl. GPU**
  (`checkThermalZones` ~89/84°C) → `recomputeAnimLevel` → **AnimPolicy sheds decorative load BEFORE
  the system seizes**. Graceful degrade, never hard-lock.
- **Zen makes the quiet pay off.** Because Lelan isn't churning, Zen's `schedutil`/`powersave`
  governor can idle cores (low power/heat); under bursts, `SCHED_FIFO`/uclamp boost the compositor so
  it feels instant. **Codependent:** no-polling is the *precondition* that lets Zen's power tuning
  work; Zen's foreground-boost keeps the rare bursts smooth. Lelan-without-Zen wastes idle headroom;
  Zen-without-Lelan has nothing to tune (polling never lets the CPU rest).
- **Net:** heavy in capability, light in footprint — the macOS "feature-rich but feels light," the
  opposite of bog.

## 0b. Reuse strategy for the last gaps (the qtermwidget model)
Finish audio/tray by **linking a proven library and wrapping it** (like `ncde-terminal` links
`qtermwidget`), NOT hand-rolling raw D-Bus:
- **Audio (PipeWire):** link **`AstalWp`** or **`libwireplumber`** → wrap in Lelan → emit
  `volume/audio/muted`. (GObject lib → integrate its GLib loop alongside Qt — minor glue.)
- **Tray:** link **`AstalTray`** or a Qt SNI host helper.
- **Prior art (the pattern is standard):** KDE Plasma DataEngines/Solid, GNOME Shell, **Quickshell**
  (Pipewire/Mpris/SystemTray services), **Astal/ags** (`libastal`). Don't adopt Quickshell wholesale
  (it's a shell runtime, not a lib; `ncde-wm` is the WM; X11; 166 QML expect `lelan`/`ncde`) — mine its
  approach + link Astal's separable libs.
- **Licensing:** Astal/Quickshell are **LGPL — same as the already-shipped `qtermwidget`**, so
  dynamic link-and-wrap is fine. (Verify exact license before *copying*.)
- ✅ Deep research COMPLETE (two runs: `wf_a69f75f2-222` did pattern/audio/GeoClue2; `wf_eaf8d459-0e9`
  did tray/MPRIS/daemons/prior-art — 105 claims, 44/45 verify votes clean). Findings folded into
  `lelan-research-findings.md` (the synthesis) and this plan. Library picks: **audio = libpulse**
  (WirePlumber alt), **tray = SNI host + xembed-sni-proxy**. Prior art confirms the pattern (KDE
  KSystemStats, Astal/AGS — findings §7).

## 1. Current artifact
- **HISTORICAL — this workspace is gone (corrected 2026-07-17):** `~/ncde-staging/compass7/lelan/`
  (the unpacked `compass (7).zip`) no longer exists; the dev machine that hosted it is gone. This
  §1-§4 gap list is kept as the historical plan (per the banner above). Current editing surface for
  Lelan is the live `/usr/local/bin/LaPivot` binary + the partial reconstruction in
  `~/ncde-wm-rebuild/` — see `docs/lapivot-rebuild.md` for per-class status.
- **Designer rebuild:** `compass (6).zip` → faithful C++ skeleton (`Lelan.h/.cpp`, `NcdeTheme.h`,
  `main.cpp`, `CMakeLists.txt`). Correctly implements the **two context properties** (`lelan` = event
  hub; `ncde` = theme/appearance/state) and the full signal/property surface.
- **Reviewed + corrected:** `lelan-fixed.zip` (session 3) — three build-blockers fixed (below).
- **`compass (7).zip`** (designer, near-final) — **~14 of 15 stubs filled** with real D-Bus wiring;
  links clean (all slots defined); signal/slot collision resolved (audio slots → `handle*`); all 9
  **Sentinel** handlers added; **AnimPolicy** (`AnimPolicy.h`, inline) wired; `qDBusRegisterMetaType`
  done; UPower live-update slot connected. README stale (still says "15 stubs"). CMake is standalone
  (no `install()`, builds in `lelan/build/`) — **does not touch `[dead-legacy-tree]`**.
  **Remaining gaps (research COMPLETE — all resolved, see `lelan-research-findings.md`):** (1) add
  `#include <QDateTime>` (Lelan.cpp); (2) ✅ **audio** — `PulseAudio Core1` does **not exist** on
  pipewire-pulse → **replace `subscribeToAudio()` with `libpulse`** (Waybar model; WirePlumber is the
  documented alternative) [findings §2/§7]; (3) ✅ **tray** — own `org.kde.StatusNotifierWatcher`
  **early** + host SNI, and **bridge ncde-wm's existing XEmbed `TrayWatcher` via an xembed-sni-proxy**
  (the Plasma model — not SNI-only, not two render paths) [findings §4]; (4) ✅ **GeoClue2** —
  `GetClient`→set `DesktopId`→connect `LocationUpdated` **before** `Start()` [findings §3]; (5) ✅ MPRIS
  — parse `Metadata`(a{sv}); `Position` via `Seeked`+interpolation, not PropsChanged [findings §5]; (6)
  📄 accent `(ddd)→QColor`, `removableVolumes` (`Drive.Removable`+`Filesystem.MountPoints` aay), thermal
  sysfs — values from primary specs but **NOT 3-vote verified** (verify gate sampled top-25; only
  NetworkManager enums passed) [findings §6, verify pass owed]. **Also:** switch compass(7)'s blocking
  `QDBusInterface` ctors to async
  `QDBusMessage`/`QDBusServiceWatcher` [findings §1]. Exact enum values (NMState/NMDeviceState/UPower
  State/etc.) are in findings §6.

## 2. Review fixes — APPLIED in `lelan-fixed.zip`
1. **Won't-link blocker:** ~34 declared `private slots` + `NcdeTheme::applyPalette` had no
   definitions; moc's `qt_static_metacall` references every declared method → undefined references at
   link. **Fix:** gave each a body. Trivial/`PropertiesChanged` ones are wired from the verified specs;
   object-enumeration ones (BlueZ/UDisks2/GeoClue/audio) left `TODO(wire)`.
2. **Missing includes:** `<QDateTime>`, `<QDBusMessage>` in `Lelan.cpp`.
3. **Signal/slot name clash:** renamed the property NOTIFY signals →
   `volumeChanged/mutedChanged/fallbackSinkChanged`; kept `on…` as slots only.
> Not compiled here (host lacks `cmake`). Operator: `pacman -S cmake`, then
> `cmake -S lelan -B lelan/build && cmake --build lelan/build`.

## 3. Remaining work — fill the 15 `subscribeTo*` stubs (the bulk)
Each follows the **same five steps**: async `GetAll`/`Read` → `bus.connect(signal→slot)` → cache into
`m_…` → `emit …Changed()` → re-subscribe on `NameOwnerChanged` (global). Order by visibility.

### Batch A (do first — most-visible surfaces) — **D-Bus verified this session**
- **NetworkManager** `org.freedesktop.NetworkManager` `/org/freedesktop/NetworkManager`: signal
  `StateChanged(u)`→`onNetworkStateChanged`; `PrimaryConnection`(o) + `Connectivity` via PropsChanged;
  VPN via `…VPN.Connection.VpnStateChanged(u,u)`. → `networkChanged/vpnStateChanged`.
  [[NM](https://networkmanager.dev/docs/api/latest/gdbus-org.freedesktop.NetworkManager.html)]
- **Audio** — ⚠️ **SUPERSEDED:** `PulseAudio Core1` D-Bus (`/org/pulseaudio/core1`) **does NOT exist on
  pipewire-pulse** (it ships only the native socket, not `module-dbus-protocol`) — verified, `findings
  §2`. **Use `libpulse`** (link-and-wrap, Waybar `audio_backend.cpp` model; WirePlumber is the
  documented alternative — `findings §7`): `pa_threaded_mainloop` + `pa_context_subscribe` for
  sink/source/default-sink changes; `pa_context_get_sink_info_*` to read volume/mute;
  `pa_context_set_sink_{volume,mute}_by_index` to set. Marshal callbacks to the Lelan QObject (queued)
  → still emit `audioChanged/volumeChanged/mutedChanged/onFallbackSinkUpdated`. The handler-slot names
  in `missing.md §2` stay; only the transport changes.
- **MPRIS** `org.mpris.MediaPlayer2.<name>` `/org/mpris/MediaPlayer2` (session): per-player `Player`
  PropsChanged → `PlaybackStatus`(s), `Metadata`(a{sv}: `mpris:trackid`,`xesam:title/artist`,
  `mpris:artUrl`,`mpris:length`); **`Position`(x, µs) has NO PropsChanged — poll it**. Enumerate names
  off `NameOwnerChanged`. → `m_players`, `mediaChanged/mediaPositionChanged`.
  [[MPRIS](https://specifications.freedesktop.org/mpris/latest/Player_Interface.html)]
- **logind** `org.freedesktop.login1`: `Session.Lock`/`Unlock` signals; Session PropsChanged→`Active`(b);
  `Manager.PrepareForSleep(b)`. → `onSessionActiveChanged/vtActiveChanged/screensaverChanged`.
  [[login1](https://www.freedesktop.org/software/systemd/man/latest/org.freedesktop.login1.html)]

### Batch B
- **UPower** DisplayDevice PropsChanged → `Percentage`(d),`State`(u: 2=Discharging),`TimeToEmpty`. *(ref
  impl + live slot done)*
- **PowerProfiles** `net.hadess.PowerProfiles` PropsChanged→`ActiveProfile`(s). *(wired)*
- **portal.Settings** (session) `SettingChanged(ns,key,v)`; `org.freedesktop.appearance` `color-scheme`
  (u 0/1/2) + `accent-color` ((ddd) struct or u0). *(ref impl + color-scheme wired; accent parse TODO)*
  [[Settings](https://flatpak.github.io/xdg-desktop-portal/docs/doc-org.freedesktop.portal.Settings.html)]
- **BlueZ** `org.bluez` ObjectManager `InterfacesAdded/Removed`; `Device1.Connected`(b)/`Name`(s).
- **UDisks2** ObjectManager; removable = `Drive.Removable`(b); mounts = `Filesystem.MountPoints`(aay) →
  build `removableVolumes`.

### Batch C
- **PackageKit** `UpdatesChanged` → count via `GetUpdates`. *(wired: emit packageStateChanged)*
- **GeoClue2** create `Client`(set DesktopId, Start); `LocationUpdated(o,o)`→read `Location`
  lat/lon → place/weather/moon; drives night-light.
- **timedate1/hostname1/locale1** PropsChanged (`Timezone`/`Hostname`). *(wired)*
- **ScreenSaver** `org.freedesktop.ScreenSaver.ActiveChanged(b)`. *(wired via onScreenSaverActivated)*
- **MemoryMonitor** (session) `LowMemoryWarning(y)`→thermal feed. *(wired)*
- **Notifications** monitor `ActionInvoked(u,s)`.
- **KickassGuard-subscribe** `org.ncde.KickassGuard` 5 signals. *(all 5 re-emits wired)*
- **NCDE Sentinel** `io.ncde.Sentinel` `/io/ncde/Sentinel` — NCDE's own Python udev→D-Bus hardware
  bridge (in the tree; its code names "L'élan" as consumer). Add `subscribeToSentinel()`. Signals:
  `DisplayConnected(s)`/`DisplayDisconnected(s)`→`screenConfigChanged`; `UsbDeviceAdded/Removed(ss)`,
  `InputDeviceAdded/Removed(s)`→device refresh; `AudioDeviceChanged(ss)`→`audioDeviceChanged`;
  `BatteryStateChanged(bi)`→`batteryChanged`; `NetworkStateChanged(sb)`→`networkChanged`. It also
  applies the **Zen** cpufreq/dirty_ratio hints on AC↔battery (see `zen.md`).

**Verify every name on the box before coding:** `busctl introspect <svc> <path>` (`--user` for session).

## 4. Custom metatypes (declared in `Lelan.h`; `qDBusRegisterMetaType` them)
`BlueZInterfaceMap = QMap<QString,QVariantMap>` (ObjectManager `a{sa{sv}}`, shared BlueZ+UDisks2);
`AudioVolumeArray` (PA per-channel volume — **[VERIFY]** element type vs `Device.Volume` `au`);
`PlayerState` (per-MPRIS hash).

## 5. Integration
- **Standalone host** (designer's `main.cpp`) injects `lelan` + `ncde` and loads a throwaway test QML —
  good for `busctl`/visual testing.
- **Product:** `Lelan` + `NcdeTheme` get constructed inside **`ncde-wm`** and injected as the `lelan` /
  `ncde` context properties there (Lelan feeds NcdeTheme on portal/audio changes). No QML file ships
  for Lelan. Lelan is C++ compiled into ncde-wm — it is the desktop nervous system (~80 D-Bus signals,
  coordinates with linux-zen kernel and ncde-sentinel). **Corrected 2026-07-17:** the WM C++ is
  recovered via Ghidra decompilation of the live `/usr/local/bin/LaPivot` binary, reconstructed
  class-by-class in `~/ncde-wm-rebuild/` — partial, not all classes compile-verified yet (see
  `docs/lapivot-rebuild.md`). Lelan lives inside the running WM binary today regardless of
  reconstruction status.

## 6. Open [VERIFY]
- `ncde` vs `lelan`: one object two names, or two objects? (rebuild assumes **two** — both names exposed.)
- `AudioVolumeArray` exact element type; `accent-color` (ddd)→QColor parse.
- ✅ RESOLVED: target ships `pipewire-pulse`, which has **no** PA D-Bus module → Core1 is absent. Audio
  path = **libpulse** (WirePlumber alt). See `lelan-research-findings.md §2/§7`. (accent `(ddd)→QColor`
  parse also resolved — `findings §6`.)

## 7. Build gate
Fixes (§2) → links. Fill Batch A (§3) → desktop comes alive. Batch B/C → full coverage. Then wire
`AnimPolicy` (anim-policy.md) and integrate into ncde-wm (§5). VM-test the live desktop.
