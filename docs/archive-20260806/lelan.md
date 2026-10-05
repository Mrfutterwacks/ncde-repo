# Lelan — NCDE's System Nervous System — **Rebuild-From-Scratch Manual**

**Audience:** a developer with **no access to the NCDE source**. This document is meant to be
sufficient on its own to re-implement `Lelan` from zero. Companion files (same folder):
`lelan-references.txt` (raw symbol dump), `anim-policy.md` (the animation governor),
`kickass-guard.md` (the AI security brain). Everything here is reconstructed from the **compiled
`ncde-wm`/`LaPivot` binary** + the QML. The **C++** source itself is gone (dev machine lost, no copy
anywhere as of 2026-07-17) — the WM C++ is being **RECOVERED by Ghidra-decompiling the live binary**
(workspace: `~/ncde-wm-rebuild/src/decompiled/`, no `ncde-staging/` prefix — that path no longer
exists), class-by-class. This is **partial** — most classes are still raw decompiler output, not clean
rebuilt source (current status: `docs/lapivot-rebuild.md`). The `.qml` files, by contrast, were never
lost — plain text on disk, editable directly.

**Evidence tags:** **[E]** = verified in the binary/tree (fact). **[STD]** = a public freedesktop
D-Bus API the implementer must talk to (stable, documented — verify on the target with
`busctl introspect`). **[INF]** = inference/operator-intent (a sensible default, not gospel).

---

## 1. What Lelan is

`Lelan` (consumed in QML as the lowercase context property **`lelan`**) is NCDE's **single, shared
system-event hub** — the "nervous system." **Corrected 2026-06-30 night (this claim was wrong and
contradicted `missing.md` §1, which had it right):** Lelan is compiled **in-process** into the one WM
binary (now `LaPivot`) — it does NOT register its own D-Bus service (`grep -rn "registerService\|
io.ncde.Lelan"` across `Lelan.cpp`/`main.cpp` = 0 hits), does NOT run standalone, and is not a separate
companion daemon like `ncde-sentinel`. `ncde-sentinel` genuinely IS a standalone process and DOES feed
Lelan hardware/hotplug events — that part was correct. It runs on the **linux-zen** kernel (as substrate,
see `zen.md`'s correction). (In the original desktop — whose WM C++ is being reconstructed class-by-class
via Ghidra, partial, see `docs/lapivot-rebuild.md` — the same class was compiled into `ncde-wm` **[E]** —
this was, and remains, true for both the original and the current rebuild; there was never a
standalone-daemon phase.)

> **The name** is *l'élan* — French for momentum / vital energy (cf. Bergson's *élan vital*), apt for the
> system's nervous energy; NCDE's naming + look are French / Art Nouveau throughout (`ncde-architecture.md
> §0`). In the operator's family metaphor Lelan is the **mother** — wife of **Zen** (the kernel), sister
> of **Sentinel**, mother of **NCDE**. Lose her and the whole family stops: "if mamma is gone nothing gets
> done." **[INF — operator intent]**

- **The body & skeleton** = the window manager + desktop UI.
- **The nervous system** = `lelan`: it subscribes **once** to every system service (D-Bus, files,
  sockets, timers) and **fans the events out** to all widgets as Qt signals.
- **The brain** = the linux-`zen` kernel + scheduler (priority/optimization). A separate cognitive
  brain (the **Vesper** LLM) lives in KickassGuard — see `kickass-guard.md`. **[INF/E]**

**It is "a switch."** Instead of every widget opening its own D-Bus connection / poller (N watchers →
wasted RAM, redundant GPU repaints, many timer wakeups), `lelan` centralizes them into **one** and
multiplexes. Widgets are pure **consumers**: they `Connections { target: lelan }` and react. Same
backend-coalescing idea as KDE's Solid / LXQt's shared backends. **[INF]**

> **Why it must be rebuilt, not extracted:** `LElan` has **no public header and no shared library** —
> it exists only inside the `ncde-wm` executable, so nothing can link it. A separate program that wants
> `lelan` must **re-implement** it to the contract below — which is exactly what the **`lelan-host`
> companion daemon** does. It is not linked into `ncde-wm`; it runs as its own process and serves the
> contract over D-Bus. **[E]**

---

## 2. How consumers use it (the contract you must preserve)

Only two literal `lelan` references survive in the shipped QML, but they pin the pattern exactly:

```qml
// NCDECommand.qml:1792 — connect to a signal, react.
Connections {
    target: lelan
    function onPackageStateChanged() { pkgMgr.checkUpdates() }
}
```
```qml
// StorageTab.qml:2 — widgets bind to lelan-fed model data.
// Backend: widget_data.removableVolumes (QVariantList, updated on hotplug via LElan).
```

**Rules to keep compatible:**
1. Exposed to QML as context property name **`lelan`** (lowercase). **[E]**
2. Emits Qt signals named `xxxChanged()` / typed variants; widgets connect via `onXxxChanged`. **[E]**
3. Exposes current values as readable `Q_PROPERTY`s (or `QVariantMap`s) widgets bind to. **[INF]**
4. Widgets never poll a backend directly — they only read `lelan`. **[INF]**

---

## 3. Architecture to build from scratch

Implement `Lelan` as a **C++ `QObject` using Qt 6** (Core, DBus, Network, Qml). This matches the
original (the binary is full of `QDBusPendingCallWatcher`, `QFileSystemWatcher`, `QSocketNotifier`,
`QTimer`). A pure-QML implementation is possible but QtDBus from QML is painful — **C++ is the
faithful path.** **[E/INF]**

```
            ┌──────────────────────────── Lelan (QObject) ────────────────────────────┐
            │  one QDBusConnection (system + session)                                  │
 D-Bus  ───►│  subscribeToNetworkManager()  subscribeToUPower()  subscribeToBlueZ() …  │──► signals:
 services   │  each: match a service, watch PropertiesChanged/specific signals,        │    networkChanged()
            │        cache state into a Q_PROPERTY, emit xxxChanged()                  │    batteryChanged()
 files  ───►│  QFileSystemWatcher (settings files) ─► applyProperties()                │    themeChanged() …
 timers ───►│  QTimer (CoarseTimer, coalesced) ─► periodic refresh                     │
            │  onNameOwnerChanged() ─► re-subscribe when a backend restarts            │──► Q_PROPERTYs
            └──────────────────────────────────────────────────────────────────────────┘    (widgets bind)
                         ▲ injected into QML as context property `lelan`
```

**Core responsibilities:**
- **One owner per service.** Open the D-Bus match/subscription a single time; never per-widget.
- **Cache + emit.** Keep the latest value in a property; emit the matching `xxxChanged()`.
- **Coalesce.** Use one `QTimer` (`Qt::CoarseTimer`) for any polled source; batch reads.
- **Self-heal.** Track `org.freedesktop.DBus` `NameOwnerChanged`; when a watched service drops/returns,
  tear down + re-subscribe (`LElan::onNameOwnerChanged(name, old, new)` in the original). **[E]**
- **Stay cheap.** Run blocking/IO work async (`QDBusPendingCallWatcher`), low scheduler priority.

---

## 4. THE BACKEND MAP — every service Lelan talks to **[E: service/interface names]**

Exact D-Bus names are strings in `ncde-wm`. Bus = **system** unless noted. `PropsChanged` =
`org.freedesktop.DBus.Properties.PropertiesChanged` on the relevant interface.

| `subscribeTo…` | Service / object path | Interface(s) | Watch | Emit (NCDE) |
|---|---|---|---|---|
| `NetworkManager()` | `org.freedesktop.NetworkManager` `/org/freedesktop/NetworkManager` | `…NetworkManager`, `…Connection.Active`, `…VPN.Connection` | `StateChanged`, PropsChanged | `networkChanged`, `vpnStateChanged` |
| (battery) | `org.freedesktop.UPower` `/org/freedesktop/UPower` | `…UPower`, `…UPower.Device` | `DeviceAdded/Removed`, Device PropsChanged | `batteryChanged` |
| `BlueZ()` | `org.bluez` (ObjectManager) | `org.bluez.Device1`, `…Adapter1` | `InterfacesAdded/Removed`, PropsChanged | `bluetoothChanged`, `bluetoothAudioDeviceChanged` |
| `UDisks2()` | `org.freedesktop.UDisks2` `/org/freedesktop/UDisks2` | `…Manager`, `…Drive`, `…Filesystem`, ObjectManager | `InterfacesAdded/Removed`, `MountPoints` PropsChanged | `storageChanged`, `diskMountChanged`, → `removableVolumes` |
| `PowerProfiles()` | `net.hadess.PowerProfiles` `/net/hadess/PowerProfiles` | `net.hadess.PowerProfiles` | `PropsChanged(ActiveProfile)` | `powerProfileChanged` |
| `PackageKit()` | `org.freedesktop.PackageKit` `/org/freedesktop/PackageKit` | `…PackageKit` | `UpdatesChanged`, `TransactionListChanged` | `packageStateChanged`, `updatesChanged` |
| `PortalSettings()` | `org.freedesktop.portal.Desktop` `/org/freedesktop/portal/desktop` (**session bus**) | `org.freedesktop.portal.Settings` | `SettingChanged` (namespaces `org.freedesktop.appearance` color-scheme/accent; `org.gnome.desktop.interface`) | `themeChanged`, `darkModeChanged`, `onAccentColorChanged`, `systemFontChanged` |
| `MemoryMonitor()` | `org.freedesktop.portal.MemoryMonitor` (session) | same | `LowMemoryWarning` | `thermalPressureChanged`/mem (see note) |
| (geo) night light | `org.freedesktop.GeoClue2` `…/Client`, `…/Location` | GeoClue2 Client/Location | `LocationUpdated` | `placeNameChanged`, `weatherChanged`, `moonPositionChanged` (drives `scheduleNightLightEvents`) |
| (time) | `org.freedesktop.timedate1` `/org/freedesktop/timedate1` | `…timedate1` | PropsChanged(Timezone) + a 1-min tick | `clockChanged`, `dateTimeChanged`, `timezoneChanged` |
| (identity) | `org.freedesktop.hostname1`, `org.freedesktop.locale1` | resp. | PropsChanged | `hostnameChanged`, `localeChanged` |
| `SessionLock()` / `VtActive()` | `org.freedesktop.login1` `/org/freedesktop/login1` + `/session/self` | `…login1.Manager`, `…login1.Session` | `Lock`/`Unlock`, `PropsChanged(Active, LockedHint)`, `PrepareForSleep` | `onSessionActiveChanged`, `vtActiveChanged`, `screensaverChanged` |
| (screensaver) | `org.freedesktop.ScreenSaver` `/org/freedesktop/ScreenSaver` (session) | `…ScreenSaver` | `ActiveChanged` | `screensaverChanged` |
| `subscribeToPlayer(name)` | `org.mpris.MediaPlayer2.<name>` `/org/mpris/MediaPlayer2` (session) | `org.mpris.MediaPlayer2.Player` | PropsChanged(PlaybackStatus, Metadata, Position) | `mediaChanged`, `mediaPositionChanged`, `appNameChanged`, `durationChanged` (stored in `QHash<QString, PlayerState>`) |
| `subscribeTrayOwner()` | `org.kde.StatusNotifierWatcher` + `com.canonical.AppMenu.Registrar`/`com.canonical.dbusmenu` (session) | SNI + dbusmenu | item registered/removed, PropsChanged | `trayChanged`, `onTrayBadgeChanged`, `onTrayPercentChanged`, … |
| (audio) `retryFallbackSink()` | `org.PulseAudio.Core1` `/org/pulseaudio/core1` (PipeWire's pulse) | PulseAudio Core1 / Device | sink add/remove/default change | `audioChanged`, `audioDeviceChanged`, `onAudioVolumeUpdated`, `onAudioMuteUpdated`, `onFallbackSinkUpdated` |
| `KickassGuard()` | `org.ncde.KickassGuard` (see `kickass-guard.md`) | NCDE adaptor | armed/threat signals | `kickassChanged`, `kickassStatusChanged`, `kickassThreatBlocked`, `kickassThreatBehavioral` |
| (notifications) | `org.freedesktop.Notifications` `/org/freedesktop/Notifications` (session) | `…Notifications` | Notify/CloseNotification (monitor) | `notificationsChanged` |
| `subscribeToSentinel()` | `io.ncde.Sentinel` (system — the hardware bridge, see `zen.md §1`) | NCDE adaptor | USB/input/display/network/battery/audio hotplug signals **+ ThermalChanged/FanChanged/ThermalCritical/DriverMissing (added 2026-07-02 — Sentinel emitted these from the start, Lelan subscribed to none of them until this fix; built+staged, not yet deployed live as of this edit — verify sha before trusting this row as "live")** | `storageChanged`, `networkChanged`, `screenConfigChanged`, `audioDeviceChanged`, `batteryChanged`, `sentinelTempsChanged`, `sentinelFansChanged`, `driverMissing`; `ThermalCritical` also feeds `m_thermalHot`→`thermalPressureChanged` alongside the existing `checkThermalZones()` poll |

> **Apps detected by name [E]:** `com.spotify.Client`, `com.discordapp.Discord`,
> `com.valvesoftware.Steam` appear in `ncde-wm` — i.e. lelan recognizes these as MPRIS players /
> known apps for the media + dock surfaces.

**MemoryMonitor note [STD]:** `org.freedesktop.portal.MemoryMonitor` emits `LowMemoryWarning(byte
level)` (50/100/200/255). Thermal proper is read from sysfs/`UPower`/`thermal_zone`; the binary
carries `thermal`(29)/`thermalPressureChanged`, so combine portal mem-pressure + a thermal sysfs poll
(coalesced) into the level fed to `AnimPolicy`. **[E for names, STD for mechanism]**

---

## 5. Per-subsystem implementation recipe (the from-scratch meat)

Each watcher follows the **same five steps** — do this for every row in §4:

```cpp
// PATTERN (Qt6 / QtDBus). Repeat per service.
void Lelan::subscribeToUPower() {
    auto bus = QDBusConnection::systemBus();
    // 1. async initial fetch (never block the UI thread)
    auto *probe = new QDBusInterface("org.freedesktop.UPower",
        "/org/freedesktop/UPower/devices/DisplayDevice",
        "org.freedesktop.DBus.Properties", bus, this);
    // 2. subscribe to change signal
    bus.connect("org.freedesktop.UPower",
        "/org/freedesktop/UPower/devices/DisplayDevice",
        "org.freedesktop.DBus.Properties", "PropertiesChanged",
        this, SLOT(onUPowerProps(QString,QVariantMap,QStringList)));
    // 3. on signal: cache into a Q_PROPERTY   m_battery = …;
    // 4. emit the NCDE signal                 emit batteryChanged();
    // 5. (covered globally) re-subscribe on NameOwnerChanged
}
```

Concrete notes the implementer needs per service (all **[STD]** unless tagged):

- **NetworkManager:** read `State` (enum) + active connection; signal `StateChanged(u)`; VPN via
  `…VPN.Connection` `VpnStateChanged`. Property `PrimaryConnection`.
- **UPower:** `DisplayDevice` gives aggregate `Percentage`, `State`, `TimeToEmpty`. On-battery =
  UPower `OnBattery`. Feed on-battery → `AnimPolicy(bool)`.
- **BlueZ:** use `ObjectManager.GetManagedObjects`; watch `InterfacesAdded/Removed`; per-`Device1`
  `Connected`/`Name`; BT audio = device with audio UUIDs.
- **UDisks2:** `ObjectManager`; a **removable** volume = `Drive.Removable == true`; mount state from
  `Filesystem.MountPoints`. Build `removableVolumes` (the `StorageTab` model). **[E: that model name]**
- **power-profiles-daemon:** `net.hadess.PowerProfiles` property `ActiveProfile`
  (`power-saver`/`balanced`/`performance`); watch its `PropertiesChanged`. **[E: exact name]**
- **PackageKit:** `UpdatesChanged` + `GetUpdates` count → `packageStateChanged` (this is the one the
  surviving QML connects to). **[E]**
- **portal.Settings (session bus):** `Read`/`ReadAll` + `SettingChanged(namespace, key, variant)`.
  Dark mode = `org.freedesktop.appearance` `color-scheme` (0 none/1 dark/2 light); accent =
  `accent-color`. This is how NCDE follows the system theme. **[STD]**
- **GeoClue2:** create a `Client`, set `DesktopId`, `Start`; `LocationUpdated(old,new)` → read
  `Location` (lat/lon) → derive place/weather/sun-moon; drives `scheduleNightLightEvents(sunset,
  sunrise)`. **[E: GeoClue2 + the method name]**
- **logind (`login1`):** session `Active`/`LockedHint`, signals `Lock`/`Unlock`; **active VT** from
  the seat/session — `vtActiveChanged` matters to the recovery handoff. `PrepareForSleep(b)` to
  re-arm watchers on resume. **[E: VtActive + SessionLock]**
- **MPRIS:** enumerate `org.mpris.MediaPlayer2.*` names on the session bus; per player watch
  `Player` PropsChanged (`PlaybackStatus`, `Metadata` → title/artist/art, `Position`). Keep a
  `QHash<QString, PlayerState>` (the `LElan::PlayerState` type). **[E: PlayerState]**
- **Tray (SNI):** own/monitor `org.kde.StatusNotifierWatcher`; track registered items; per item read
  `Status`, `IconName`, `Title`, tooltip; AppMenu via `com.canonical.dbusmenu`. **[E: AppMenu/dbusmenu]**
- **Audio (PulseAudio Core1 / PipeWire-pulse):** subscribe to sink/source/default-sink change; on
  default-sink loss call the equivalent of `retryFallbackSink()` to re-point output. **[E: that method]**

---

## 6. Full signal / property catalog **[E: names from the binary]**

Group these into `Q_PROPERTY` + matching `…Changed()` signals. (Raw list: `lelan-references.txt` §D.)

- **Network/VPN:** `networkChanged`, `vpnStateChanged`
- **Audio/media:** `audioChanged`, `audioDeviceChanged`, `bluetoothAudioDeviceChanged`,
  `onAudioVolumeUpdated`, `onAudioMuteUpdated`, `onFallbackSinkUpdated`, `mediaChanged`,
  `mediaPositionChanged`, `mediaActive`, `appNameChanged`, `appIconChanged`, `durationChanged`
- **Power/battery/thermal:** `batteryChanged`, `powerProfileChanged`, `powerChanged`,
  `thermalPressureChanged`, `statsChanged`
- **Bluetooth:** `bluetoothChanged`
- **Storage:** `diskChanged`, `diskDeviceChanged`, `diskMountChanged`, `storageChanged`
- **Security (KickassGuard):** `kickassChanged`, `kickassStatusChanged`, `kickassSiteBlocked`,
  `kickassThreatBlocked`, `kickassThreatBehavioral`
- **Updates:** `packageStateChanged`, `updatesChanged`
- **Time/weather/sky (geoclue):** `clockChanged`, `dateTimeChanged`, `timezoneChanged`,
  `weatherChanged`, `placeNameChanged`, `moonPositionChanged`
- **Tray:** `trayChanged`, `trayActive`, `trayOwnerChanged`, `onTrayBadgeChanged`,
  `onTrayPercentChanged`, `onTrayChargingChanged`, `onTraySubTypeChanged`, `onTrayBarsChanged`
- **Theme/appearance/portal:** `themeChanged`, `darkModeChanged`, `onAccentColorChanged`,
  `wallpaperChanged`, `systemFontChanged`, `slideshowChanged`
- **Session/VT/lock/screen:** `onSessionActiveChanged`, `vtActiveChanged`, `screensaverChanged`,
  `screenConfigChanged`, `screenGeometryChanged`
- **Identity:** `hostnameChanged`, `localeChanged`, `userNameChanged`, `usersChanged`
- **Misc widgets:** `notificationsChanged`, `notesChanged`, `printersChanged`, `weatherChanged`

**Two known method shapes [E]:** `applyProperties(QVariantMap)` (push a settings map → apply + emit
the right `…Changed`), `fetchAndApply(QString)` (read one setting/namespace then apply).

---

## 7. The "switch": optimization hooks (see `anim-policy.md` for detail)

- **Coalesce:** one `QTimer` (CoarseTimer) for polled sources; give timers tolerance so wakeups
  batch (macOS Timer Coalescing equivalent).
- **Priority:** run lelan's IO/dbus at reduced scheduler priority (zen kernel) so the compositor/UI
  always wins a busy CPU.
- **Drive `AnimPolicy`:** lelan emits `(bool)` on-battery/reduce-motion and `(int)` a level
  (full/reduced/minimal) → the animation governor degrades **decorative** motion gracefully but never
  stalls essential transitions. Wire `DesktopWidget::setAnimPolicy` / `NCDEWindowManager::setAnimPolicy`
  equivalents. **[E: those connects exist]**

---

## 7b. Glass surfaces, filigree & the NCDE engine — also governed by lelan/AnimPolicy **[E]**

The compositor/visual layer belongs to the body, but its **animation and palette data are governed
centrally** — "everything goes through lelan; the whole system is governed by lelan + zen."

- **`NCDEEngine`** — the core engine class inside `ncde-wm`. **[E]**
- **Glass surfaces** — `NCDEGlassSurface` / `NCDEGlass` / `GlassWater`; the WM registers per-window
  glass (`registerGlassWindow`, `registerMenuGlassWindow`), loads/saves/sets it (`loadSurfaceGlass`,
  `saveSurfaceGlass`, `setSurfaceGlass`), maps clients (`clientToGlass`, `clientToMenuGlass`); the
  terminal has its own `NCDETerminalGlass` / `NCDETerminalMenuGlass`. picom does the blur; the WM owns
  the glass-window registration. **[E]**
- **Filigree** — the gilt decorative trim (`SNCornerFiligree`, `SNFiligreeDivider`); palettes are data
  managed by the engine (`saveFiligreepalette` / `deleteFiligreepalette`) and **broadcast via the
  `filigreepalettesChanged()` signal** — a palette change fans out like any other lelan state, so all
  surfaces restyle together. **[E]**
- **Governed for performance** — glass/filigree animation runs under **`AnimPolicy`**, which is driven
  by **`LElan`** (`LElan(bool/int/void) → AnimPolicy` connects confirmed). Under battery/thermal/
  reduce-motion, decorative glass shimmer + filigree motion **down-shift** while surfaces stay
  vsync-smooth (see `anim-policy.md`). **[E]**

**Rebuild implication:** expose `filigreepalettesChanged` + an active-palette property on `lelan`; let
glass surfaces read the active filigree palette from `lelan` and bind their animation richness to
`lelan.animLevel`.

## 8. Exposing to QML (both ways)

```cpp
// Faithful to the original: a context property named "lelan".
Lelan lelan;                                   // your QObject from §3
engine.rootContext()->setContextProperty("lelan", &lelan);   // [E: name "lelan"]

// Or, for a reusable singleton importable by type:
qmlRegisterSingletonInstance("NCDE.System", 1, 0, "Lelan", &lelan);
```
Consumers then use `Connections { target: lelan; function onXChanged(){…} }` and bind to
`lelan.<property>`. **Do not** reintroduce per-widget polling — lelan is the single source.

---

## 9. Build / dependencies

- **Qt 6** modules: `Core Gui Qml Quick DBus Network` (all present in the NCDE tree). **[E]**
- CMake sketch:
```cmake
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick DBus Network)
add_executable(lelan-host main.cpp Lelan.cpp Lelan.h)
target_link_libraries(lelan-host PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::DBus Qt6::Network)
```
- Runtime services the recipes assume: NetworkManager, UPower, BlueZ, UDisks2,
  power-profiles-daemon, PackageKit, xdg-desktop-portal, GeoClue2, systemd-logind, a PipeWire/Pulse
  audio server, a StatusNotifier host.

---

## 10. Minimal C++ skeleton (starting point — NEW code; the original was recovered via Ghidra) **[INF]**

```cpp
// Lelan.h
#pragma once
#include <QObject>
#include <QVariantMap>
class Lelan : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap network     READ network     NOTIFY networkChanged)
    Q_PROPERTY(QVariantMap battery     READ battery     NOTIFY batteryChanged)
    Q_PROPERTY(QVariantMap audio       READ audio       NOTIFY audioChanged)
    Q_PROPERTY(QVariantMap media       READ media       NOTIFY mediaChanged)
    Q_PROPERTY(QVariantList removableVolumes READ removableVolumes NOTIFY storageChanged)
    Q_PROPERTY(bool darkMode           READ darkMode    NOTIFY themeChanged)
    Q_PROPERTY(int  animLevel          READ animLevel   NOTIFY animLevelChanged)
public:
    explicit Lelan(QObject *parent=nullptr);
    // getters … 
public slots:
    void applyProperties(const QVariantMap &m);   // [E]
    void fetchAndApply(const QString &key);        // [E]
signals:
    void networkChanged(); void vpnStateChanged();
    void batteryChanged(); void powerProfileChanged(); void thermalPressureChanged();
    void audioChanged();   void mediaChanged();    void mediaPositionChanged();
    void storageChanged(); void diskMountChanged();
    void packageStateChanged(); void updatesChanged();
    void themeChanged();   void darkModeChanged(); void systemFontChanged();
    void weatherChanged(); void clockChanged();    void timezoneChanged();
    void trayChanged();    void vtActiveChanged(); void screensaverChanged();
    void kickassStatusChanged(); void kickassThreatBlocked(QString app, QString detail, int sev);
    void animLevelChanged();
private slots:
    void onNameOwnerChanged(const QString&, const QString&, const QString&); // re-subscribe [E]
private:
    void subscribeToNetworkManager(); void subscribeToUPower(); void subscribeToBlueZ();
    void subscribeToUDisks2(); void subscribeToPowerProfiles(); void subscribeToPackageKit();
    void subscribeToPortalSettings(); void subscribeToMemoryMonitor(); void subscribeToGeoClue();
    void subscribeToLogind(); void subscribeToPlayers(); void subscribeTrayOwner();
    void subscribeToAudio(); void subscribeToKickassGuard();
};
```
In the constructor: open the buses, call every `subscribeTo…()`, wire the global
`NameOwnerChanged`, start one coalesced `QTimer`. Each `subscribeTo…` follows the §5 five-step
pattern. Expand signals/properties to the full §6 catalog.

---

## 11. How this was reconstructed / how to verify **[E]**

- API surface mined from `[dead-legacy-tree]/usr/local/bin/ncde-wm` (`strings` → `LElan::*` /
  `void (LElan::*)(…)` / D-Bus service strings). Full raw dump: `lelan-references.txt`.
- The shipped QML consuming `lelan`: `usr/share/ncde/NCDECommand.qml:1792`, `StorageTab.qml:2`.
- **To validate any recipe on a real system:** `busctl introspect <service> <path>` (system or
  `--user`) — confirms the exact interface/signal/property names before you code them. The §4 service
  names are exact strings from the binary; the per-service signal/property names in §5 are the public
  freedesktop APIs those services expose.
```
busctl introspect org.freedesktop.UPower /org/freedesktop/UPower/devices/DisplayDevice
busctl --user introspect org.freedesktop.portal.Desktop /org/freedesktop/portal/desktop
```

---

## EFFICIENCY GAPS — spec-vs-code (2026-06-27 audit; full detail in `ncde-efficiency.md`)

**Correction (2026-07-02) — two more of the bullets below are ALSO stale, re-verified against the
real current source, not assumed:**
- **"Blocking calls on the GUI thread" — FIXED.** `mediaPlayPause/Next/Previous` (`Lelan_Media.cpp`)
  all use `QDBusConnection::sessionBus().asyncCall(...)`, not blocking `.call()`. Not a current gap.
- **"Signal storms / full re-enumeration" — FIXED for WiFi and BlueZ** (session 46-48's efficiency
  pass, `ncde-efficiency.md §5` #6). `onWifiPropertiesChanged` (`Lelan_Network.cpp:261`) only calls
  `rebuildAccessPoints()` on `LastScan`/`AccessPoints`; `ActiveAccessPoint` changes patch in place via
  `readActiveNetwork()`. `onBlueZPropertiesChanged` (`Lelan_Devices.cpp:408`) filters to an explicit
  `kRelevant` property set before rebuilding, instead of rebuilding on every RSSI/TxPower tick. UDisks2
  was checked separately and found already narrowly-subscribed — never actually a signal storm.
  Not current gaps. `refreshPrinters`'s `waitForFinished(2500)` blocking call was NOT re-checked this
  pass — status unknown, don't assume either way.

**Correction (2026-06-30 night):** the item below ("idle throttle dormant") is STALE — verified fixed
in current LaPivot source. `Lelan.cpp:71,211,217` implements `deferWhenIdle`/`drainIdleQueue` (an oracle
work-queue model that explicitly replaced the `setPulseScale` approach — `Lelan.h:134`'s own comment
calls the old approach "invented" and says this "REPLACES" it), wired to a real `QTimer`.
`AnimPolicy::applyScreenIdle` (`AnimPolicy.h:86`) is driven by `onVtActiveChanged`/`onSessionLocked`/
`onScreenSaverActivated`, all connected. Kept below for history — do not treat as a current gap.

Lelan's purpose is to make NCDE ultra-fast on ANY hardware (Moksha-light + macOS App-Nap). The architecture
is right (one 1s coalesced `CoarseTimer`, async D-Bus, no per-widget pollers) but key efficiency spec items
were **not followed** in `Lelan.cpp`:

- **[STALE — see correction above] The idle throttle is dormant (HIGH).** `Lelan::setPulseScale()` and
  `AnimPolicy::setScreenIdle()` have **zero callers.** Lelan RECEIVES every idle/lock/screensaver/inactive
  signal (`onScreenSaverActivated` 1770, `onSessionLock/Unlock` 1194-95, `Active==false` 1190-92) and
  **does nothing** with them. So the heartbeat never stretches and idle never pauses — the App-Nap half
  of the spec is disconnected. **FIX:** add an X11 idle source (XSync `IDLETIME` alarm /
  `XScreenSaverQueryInfo`) → on idle/lock call `setPulseScale(4..8)` + `m_animPolicy->setScreenIdle(true)`;
  reverse on activity; `setPulseScale` on battery from `recomputeAnimLevel`.
- **Blocking calls on the GUI thread (HIGH).** `mediaPlayPause/Next/Previous` (1480/1487/1494) use blocking
  `.call()` → `.asyncCall()`. `refreshPrinters` (930) `waitForFinished(2500)` → parse `lpstat` in
  `QProcess::finished` (no blocking).
- **Signal storms / full re-enumeration (MED-HIGH).** `onWifiPropertiesChanged` (596) rebuilds all APs on
  every `LastScan`; `readActiveNetwork` emits `wifiChanged` 4×; `onBlueZ/UDisks2…Changed` (1702/1707) do full
  `GetManagedObjects` on every micro-change. FIX: patch the single changed entry; debounce; emit once.
- **LOW:** one-shot timers default `PreciseTimer` (use `CoarseTimer`; night-light 1683 → `VeryCoarseTimer`);
  thermal/cpu `/sys` polled on AC+idle.
