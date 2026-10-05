# NCDE-LELAN-PLAN.md — rebuild Lelan (the nervous system) to ship

Authoritative plan for finishing **Lelan**, NCDE's system nervous system. Lelan is the critical
path: every desktop surface binds to it, so nothing reports real state until it's wired. **Do Lelan
before recovery** (recovery is an independent lifeboat; Lelan is what the whole desktop depends on).

**Deep specs:** `lelan.md` (full backend map + recipes), `missing.md` (exact handler slots + the
`ncde` vs `lelan` split), `anim-policy.md` (the governor it drives), `ncde-architecture.md` (where it
sits). **Concept:** Lelan = a *watcher that watches the watchers* — it subscribes once to every system
daemon, tracks them via D-Bus `NameOwnerChanged`, coalesces, and fans signals out to the QML
(the "mouths"). It is **pure C++**, injected as context properties — **no QML file of its own.**

---

## 1. Current artifact
- **Designer rebuild:** `compass (6).zip` → faithful C++ skeleton (`Lelan.h/.cpp`, `NcdeTheme.h`,
  `main.cpp`, `CMakeLists.txt`). Correctly implements the **two context properties** (`lelan` = event
  hub; `ncde` = theme/appearance/state) and the full signal/property surface.
- **Reviewed + corrected:** `lelan-fixed.zip` (this session) — three build-blockers fixed (below).

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
- **Audio (PulseAudio Core1, PipeWire-pulse)** `/org/pulseaudio/core1`: `NewSink(o)`/`SinkRemoved(o)`,
  `FallbackSink`(o) prop, `Device.VolumeUpdated`/`Device.MuteUpdated`; sink `Volume`(au)/`Mute`(b).
  → `audioChanged/volumeChanged/mutedChanged`. NOTE: needs PA D-Bus module enabled.
  [[PA D-Bus](https://www.freedesktop.org/wiki/Software/PulseAudio/Documentation/Developer/Clients/DBus/Core/)]
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
  for Lelan. Source is C++ added to ncde-wm's build (the original WM source is lost → either rebuild WM
  with Lelan compiled in, or run Lelan as a small companion that the WM's QML context imports — **[DECISION]**).

## 6. Open [VERIFY]
- `ncde` vs `lelan`: one object two names, or two objects? (rebuild assumes **two** — both names exposed.)
- `AudioVolumeArray` exact element type; `accent-color` (ddd)→QColor parse.
- Whether the target ships `pipewire-pulse` + the PA **D-Bus module** (Core1 API needs it) — else use a
  PipeWire-native path instead. **[VERIFY against the tree]**

## 7. Build gate
Fixes (§2) → links. Fill Batch A (§3) → desktop comes alive. Batch B/C → full coverage. Then wire
`AnimPolicy` (anim-policy.md) and integrate into ncde-wm (§5). VM-test the live desktop.
