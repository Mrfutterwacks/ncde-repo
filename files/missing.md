# missing.md — the pieces needed to finish Lelan (answers for the designer)

Extracted from `~/ncde-x11/usr/local/bin/ncde-wm`. This fills the gaps in the C++ skeleton: the
**exact dbus handler slot for every stub**, the **custom types** to declare, the **two context
properties**, and answers to the build-order questions. All **[E]** = verified strings in the binary
unless tagged. Pairs with `lelan.md` / `kickass-guard.md`.

---

## 1. TWO context properties, not one — critical **[E]**

Widgets read from **two** injected objects. Don't conflate them:

- **`lelan`** — the **event hub** (signals). `Connections { target: lelan; function onXChanged(){} }`.
  (Confirmed: `NCDECommand.qml:1792 target: lelan`, and the binary logs `[lelan] subscribed to org.ncde.KickassGuard`.)
- **`ncde`** — the **theme / appearance / state** object (properties widgets bind to). Cached QML in
  the binary reads these directly: **[E]**
  ```
  ncde.accent      ncde.accentMuted   ncde.border    ncde.darkMode   ncde.fontSize
  ncde.foreground  ncde.gilt          ncde.glow      ncde.panelBg    ncde.popupBg
  ncde.presetActive ncde.surface      ncde.surfaceAlt ncde.surfaceGlass
  ncde.verd        ncde.version       ncde.widgetStyle ncde.wine     ncde.KickassGuard
  ```
- **[VERIFY]** whether `ncde` and `lelan` are the **same QObject under two context-property names**,
  or **two objects** (likely: `lelan` = the dbus hub, `ncde` = a theme/palette/settings object the hub
  feeds, e.g. `ncde.accentMuted` is set from `lelan`'s `onAudioMuteUpdated`). Either way the rebuild
  must expose **both names** so existing QML resolves. Confirm by checking the WM's
  `setContextProperty` calls / how the desktop QML imports them.

- **Lelan registers NO dbus service** — there is no `org.ncde.Lelan`. It is in-process only. Do **not**
  expose a Lelan dbus interface (the first QML draft's `register org.ncde.Lelan` was wrong). **[E]**

---

## 2. The 15 stubs → exact handler slots **[E: every signature is a literal moc string]**

Each `subscribeTo…()` wires the dbus signal(s) to these exact slots. (`PropsChanged` =
`org.freedesktop.DBus.Properties.PropertiesChanged(QString iface, QVariantMap changed, QStringList inval)`.)

| Subsystem | Service / path | Handler slot(s) — exact signatures |
|---|---|---|
| **NetworkManager** | `org.freedesktop.NetworkManager` `/org/freedesktop/NetworkManager` | `onNetworkStateChanged(uint)` ← `StateChanged(u)`; `onNmPropertiesChanged(QString,QVariantMap,QStringList)`; `onVpnStateChanged(uint,uint)` ← `…VPN.Connection.VpnStateChanged`; helper `scanActiveConnections()` |
| **UPower (battery)** | `org.freedesktop.UPower` `…/devices/DisplayDevice` | `onBatteryPropertiesChanged(QString,QVariantMap,QStringList)` ← Device PropsChanged |
| **BlueZ** | `org.bluez` (ObjectManager) | `onBlueZInterfacesAdded(QDBusObjectPath,BlueZInterfaceMap)`; `onBlueZInterfacesRemoved(QDBusObjectPath,QStringList)`; + `Device1` PropsChanged |
| **UDisks2** | `org.freedesktop.UDisks2` (`Drive`/`Filesystem`/`Manager`) | `onUDisks2InterfacesAdded(QDBusObjectPath,BlueZInterfaceMap)`; `onUDisks2InterfacesRemoved(QDBusObjectPath,QStringList)`; `onUDisks2FilesystemPropertiesChanged(QString,QVariantMap,QStringList)` |
| **Audio** (PulseAudio Core1 / PipeWire) | `org.PulseAudio.Core1` `/org/pulseaudio/core1` | `onAudioVolumeUpdated(AudioVolumeArray)`; `onAudioMuteUpdated(bool)`; `onNewSink(QDBusObjectPath)`; `onSinkRemoved(QDBusObjectPath)`; `onFallbackSinkUpdated(QDBusObjectPath)` |
| **PowerProfiles** | `net.hadess.PowerProfiles` `/net/hadess/PowerProfiles` | `onPowerProfilesPropertiesChanged(QString,QVariantMap,QStringList)` |
| **PackageKit** | `org.freedesktop.PackageKit` `/org/freedesktop/PackageKit` | `onPackageKitTransactionListChanged(QStringList)` → emits `packageStateChanged` |
| **Portal Settings** | `org.freedesktop.portal.Desktop` (session) | `onPortalSettingChanged(QString ns,QString key,QDBusVariant)` ← `Settings.SettingChanged` |
| **MemoryMonitor** | `org.freedesktop.portal.MemoryMonitor` (session) | `onLowMemoryWarning(uchar)` ← `LowMemoryWarning(y)` |
| **GeoClue2** | `org.freedesktop.GeoClue2` `Client`/`Location` | `onGeoClue2Location(QDBusObjectPath old,QDBusObjectPath new)` ← `Client.LocationUpdated` |
| **timedate1** | `org.freedesktop.timedate1` | `onTimedate1PropertiesChanged(QString,QVariantMap,QStringList)` |
| **hostname1** | `org.freedesktop.hostname1` | `onHostname1PropertiesChanged(QString,QVariantMap,QStringList)` |
| **locale1** | `org.freedesktop.locale1` | `onLocale1PropertiesChanged(QString,QVariantMap,QStringList)` |
| **logind** | `org.freedesktop.login1` `/login1` + `/session/self` | `onSessionActiveChanged(QString,QVariantMap,QStringList)`; `onSessionLock()` ← `Session.Lock`; `onSessionUnlock()` ← `Session.Unlock`; `onPrepareForSleep(bool)` ← `Manager.PrepareForSleep(b)` |
| **ScreenSaver** | `org.freedesktop.ScreenSaver` | `onScreenSaverActivated(bool)` ← `ActiveChanged(b)` |
| **MPRIS** | `org.mpris.MediaPlayer2.<name>` `/org/mpris/MediaPlayer2` (session) | `Player` PropsChanged → into `PlayerState` per player; enumerate names off NameOwnerChanged |
| **Notifications** | `org.freedesktop.Notifications` | `onActionInvoked(uint,QString)` (monitor) |
| **KickassGuard** | subscribe `org.ncde.KickassGuard` | see §4 |
| **(name tracking)** | `org.freedesktop.DBus` | `onNameOwnerChanged(QString,QString,QString)` (session) + `onSystemNameOwnerChanged(QString,QString,QString)` (system) → re-subscribe |
| **(generic)** | — | `onPropertiesChanged(QString,QVariantMap,QStringList)`; `onLayoutUpdated()` |

---

## 3. Custom types to declare + register **[E]**

The slots use non-stdlib payload types — declare them and `qDBusRegisterMetaType<>()`:

- **`AudioVolumeArray`** — the per-channel volume payload (`onAudioVolumeUpdated`). Also drives the
  icon-level enums seen in the binary: `AudioVolumeMuted/Low/Medium/High`.
- **`BlueZInterfaceMap`** — the ObjectManager `InterfacesAdded` map type
  (`a{sa{sv}}` → `QMap<QString,QVariantMap>`); **reused for UDisks2** `InterfacesAdded` (same shape).
- **`PlayerState`** — per-MPRIS-player state, stored `QHash<QString, PlayerState>` (from `lelan.md`).

---

## 4. KickassGuard → lelan surface is bigger than first documented **[E]**

`subscribeToKickassGuard()` wires **five** handlers (not two):
```
onKickassStatusChanged(bool armed, int level)
onKickassThreatBlocked(QString app, QString detail, int severity)
onKickassThreatBehavioral(QString subject, QString detail, QString kind)
onKickassSiteBlocked(QString site, QString detail)
onKickassNetworkAlert(QString src, QString detail)
```
(KickassGuard itself = the separate AI daemon; see `kickass-guard.md`. Lelan only subscribes.)

---

## 5. Build-order answers (designer's two questions)

1. **Fill the 15 Lelan stubs FIRST** — Lelan is the dependency every surface binds to; the desktop
   isn't alive until it reports real state. **Batch order by visibility:**
   - **Batch A (first):** NetworkManager, Audio, MPRIS, **logind** (logind is tiny and the lock/VT +
     recovery handoff need it).
   - **Batch B:** UPower, PowerProfiles, PortalSettings, BlueZ, UDisks2.
   - **Batch C:** PackageKit, GeoClue2, timedate1/hostname1/locale1, ScreenSaver, Notifications,
     MemoryMonitor, KickassGuard-subscribe.
   Every stub is the **same 5-step pattern** (match → async fetch → connect signal → cache property →
   emit `…Changed`); §2 gives the exact slot to land in. Verify each with
   `busctl introspect <service> <path>`.
2. **KickassGuard skeleton = a separate, later track.** It's its own daemon/process
   (`org.ncde.KickassGuard`, `OllamaClient`/`VesperBrain`/`ChromaClient` + 7 engines, `kickass-guard.md`).
   Lelan only needs the one `subscribeToKickassGuard()` stub (§4) to light up the security surface, so
   the desktop can come alive **without** the full guard rebuild. Do the guard after Batch A–C.

---

## 6. Still open / to verify **[VERIFY]**

- `ncde` vs `lelan`: same object (two names) or two objects? (§1) — decides whether theme properties
  live on the hub or a separate object. Check the WM's context-property registration.
- `AudioVolumeArray` / `BlueZInterfaceMap` exact D-Bus signatures — confirm with `busctl introspect`
  on PulseAudio Core1 and `org.bluez` before declaring the metatypes.
- MPRIS `PlayerState` field set — confirm against `org.mpris.MediaPlayer2.Player` introspection.
- Audio backend is PulseAudio **Core1** API (works against PipeWire's pulse server) — confirm the
  target ships `pipewire-pulse`.
