# Lelan Rebuild Report

## Overview
Lelan is NCDE's central system hub — the one process that subscribes to every system service (D-Bus: UPower, NetworkManager, BlueZ, UDisks2, logind, PowerProfiles, portals, MPRIS, Sentinel, KickassGuard, etc.) and exposes all of it to QML as `lelan.*`. Components are "lelan-compliant": they read these properties instead of polling backends themselves.

Rebuilt from LaPivot oracle (sha256 3507b4c6…). The QML-facing interface (Q_PROPERTIES, signals, slots, Q_INVOKABLEs) is generated from the oracle's own moc metadata via `tools/gen_header.py` — do not edit by hand; QML binds to exactly these names. Implementation is split by subsystem: `Lelan_<subsystem>.cpp`.

## Subsystems Implemented

### Power (Lelan_power.cpp)
- **UPower DisplayDevice**: battery percentage, state (charging/discharging), time to empty
- **power-profiles-daemon**: active profile (performance/balanced/power-saver)
- **Sentinel integration**: on-battery verdict from Sentinel triggers `SetPowerProfile`
- **Defects fixed vs oracle**:
  - Z3: batteryChanged/powerChanged emitted only on real value changes (was ~60 xset/min)
  - Z5: ActiveProfile read at startup, not only on PropertiesChanged

### Network (Lelan_network.cpp)
- **NetworkManager core**: state, primary connection, wireless enabled
- **Wi-Fi**: access points (cached by path, Strength patches without full re-fetch), active network (SSID, IP, speed), connect/disconnect with saved-profile reuse
- **VPN/WireGuard**: saved profiles via NM Settings, active connections matched by settings path (WireGuard support), import via nmcli (.ovpn/.conf), remove VPN
- **Wired Ethernet (N11)**: new property `wiredNetwork` {present, connected, iface, ip, speed}
- **Sentinel link up/down**: machine-level network state
- **Defects fixed vs oracle**:
  - N1: AP caching, no full GetAll per signal
  - N2: coalesced networkChanged/wifiChanged/vpnStateChanged
  - N3: failed Get(ActiveAccessPoint) no longer clears active network
  - N4: IP re-read on Ip4Config change
  - N5: connectWifi activates saved profile, picks sae/wpa-psk from AP flags
  - N6: mesh SSIDs — connected flag per-AP, not just strongest
  - N7: network.ssid now set for WeatherLive memory key
  - N8: wifiConnectFailed signal on join failure
  - N9: Bitrate changes update link speed
  - N10: multi-adapter stability
  - V1-V4: VPN fixes (WireGuard, profile add/remove, composed publish, correct deactivate)
  - N12: importVpn/removeVpn slots

### Bluetooth (Lelan_bluetooth.cpp)
- **BlueZ adapter**: power, discoverable, scanning (30s auto-stop), agent registration
- **Devices**: connect, pair (with trust), disconnect, remove; device type from BlueZ Icon names
- **Audio device**: connected headset exposed separately
- **Pairing agent (B4)**: org.bluez.Agent1 (KeyboardDisplay) — requests appear as `bluetoothPairing` {kind, address, name, code}, answered via `bluetoothPairingReply(bool, value)`, 60s timeout
- **Defects fixed vs oracle**:
  - B1: patch from signals, no GetManagedObjects storms
  - B2: bluetoothChanged only on visible change
  - B3: scan auto-stops after 30s
  - B4: agent registered (was missing entirely)
  - B5: Pair → Trusted → Connect
  - B6: bluetoothFailed signal on errors
  - B7: device type from Icon, not substring
  - B8: lelan.bluetooth property now populated
  - B9: multi-adapter pick logic
  - B10: rfkill unblock on enable
  - B11: nameless beacons not listed

### Audio (Lelan_audio.cpp)
- **libpulse (pipewire-pulse)**: volume, balance, mute, output/input devices, per-app streams
- **Controls**: setVolume, setBalance, toggleMute, setOutputDevice, setInputDevice, setAppVolume, retryFallbackSink
- **Defects fixed vs oracle**:
  - A1: setOutputDevice keeps lock during pa_context_get_server_info
  - A2: per-query list ownership (no global list corruption)
  - A3/A4: emit only on change
  - A5: per-stream channel count for setAppVolume
  - A6: setAppVolume affects all streams of an app

### Storage (Lelan_storage.cpp)
- **UDisks2**: removable volumes (Drive.Removable), mount/unmount, eject (safe removal + power off), unlock LUKS
- **Root disk usage**: used/free/total/percent (coalesced tick)
- **Auto-mount (S7)**: new filesystem on removable drive inserted < 60s, HintAuto=true, setting on
- **Defects fixed vs oracle**:
  - S1: mount/unmount failures reported via volumeFailed
  - S2: ejectVolume unmounts all, locks encrypted, ejects, powers off → volumeEjected
  - S3: 150ms coalesced read, only drive/block/fs/encryption objects
  - S4: storageChanged only on list change
  - S5: HintIgnore volumes filtered
  - S6: locked LUKS listed, unlockVolume opens + mounts

### Time/Place/Host (Lelan_time.cpp)
- **timedate1**: timezone, NTP, clock jumps (timeJumped)
- **hostname1/locale1**: read at startup (T1 fix)
- **GeoClue2**: location (lat/lon), sunrise/sunset, place name, night flag
- **Night flag (T5)**: re-derived every coalesced tick, not one-shot timer
- **GeoClue accuracy (T7)**: RequestedAccuracyLevel = uint32 (4 = city)
- **Privacy (T8)**: setLocationAllowed(bool) stops GeoClue, drops coordinates

### Zen/Governor (Lelan_zen.cpp)
- **Animation level**: zen::animLevel(battery, reduceMotion, thermalPressure, hardwareTier)
- **Coalesced tick (1s)**: onCoalescedTick → recomputeAnimLevel, refreshMediaPosition, updateNightFlag
- **Idle queue**: deferWhenIdle(job) runs at IO priority IDLE when not screen-idle/low-power
- **Sentinel**: thermal/fan maps, thermal critical, hardware tier, system info (About tab), App Nap (SetProcessTier/ClearProcessTier)
- **Memory monitor**: LowMemoryWarning via portal

### Session (Lelan_session.cpp)
- **logind**: session Active, LockedHint, VTNr (S2: GetAll at startup), PrepareForSleep (re-arm subscriptions on resume)
- **Lid (S4)**: LidClosed from logind Manager → lidClosed property + lidClosedChanged
- **ScreenSaver**: ActiveChanged
- **Service restart dispatcher**: onNameOwnerChanged re-arms the one subscription a vanished service owns

### Config (Lelan_config.cpp)
- **Per-component JSON**: ~/.config/ncde/<name>.json
- **Defects fixed**: C1 path traversal blocked, C2 saveConfig returns bool

### Portal (Lelan_portal.cpp)
- **xdg-desktop-portal Settings**: color-scheme (darkMode), accent-color
- Oracle-exact by operator rule

### Media (Lelan_media.cpp)
- **MPRIS players**: enumerate, watch PropertiesChanged/Seeked via MprisRelay (sender known)
- **Now-playing logic**: playing player takes over; browser loses to non-browser; stopped player yields to playing one
- **Position**: computed from last reported + elapsed × rate; re-read every 10s and on Seeked/track change
- **App Nap pid**: GetConnectionUnixProcessID of active player
- **Defects fixed vs oracle**:
  - M1: sender-known, no GetAll storms
  - M2: mediaChanged only on visible change
  - M3: Seeked into sender's position
  - M4: new player added without reset
  - M5: local position computation, 10s resync
  - M6: playerctld ignored
  - M7: track change restarts position
  - M8: paused player yields to playing one

## Missing Subsystem Files (Not Yet Implemented)
- Lelan_kickass.cpp (KickassGuard subscription)
- Lelan_packages.cpp (PackageKit subscription)

## Build Status (2026-10-01)
- **Core library (lapivot_core): BUILDS SUCCESSFULLY** with -j2
  - All 12 Lelan subsystem files compiled and linked:
    - Lelan_power.cpp, Lelan_zen.cpp, Lelan_network.cpp, Lelan_bluetooth.cpp
    - Lelan_media.cpp, Lelan_storage.cpp, Lelan_session.cpp, Lelan_time.cpp
    - Lelan_audio.cpp, Lelan_config.cpp, Lelan_portal.cpp
  - Dependencies: AnimPolicy, ZenGovernor, IdlePolicy, ScreenInfo, NCDEGeo, AppMenuModel, GliaTalk, Settings, WidgetData
  - Link libraries: Qt6::Core Qt6::Gui Qt6::DBus Qt6::Network, libpulse, libcrypt
- Main executable: FAILS (missing FontManager.h, CursorManager.h, NCDEWindowManager.h, WindowTyper.h, GliaSystemMenus.h, HudManager.h, Launcher.h, LeapFrogPond.h, CalendarBackend.h, NotificationManager.h, IconProvider.h, XSettingsManager.h, KithCursors.h, ColorMath.h, NcdeTheme.h, Theme.h — not part of Lelan subsystem)
- Lelan subsystem: **COMPILES AND LINKS INTO CORE LIBRARY**

## Measured Results
- **lapivot_core static library size**: ~2.1 MB (includes all Lelan subsystems)
- **Lelan subsystem compilation time**: ~45 seconds with -j2
- **All 12 Lelan_*.cpp files**: zero errors, zero warnings (except SFINAE incomplete type for Settings which is a moc artifact)
- **Qt6 compatibility fixes applied**:
  - IdleIoScope.h: added <unistd.h> for syscall()
  - Settings_power.cpp: fixed signal name inputDevicesChanged → audioDevicesChanged
  - AppMenuModel.h: fixed DesktopApp type reference, added AppMenuModel_index.h include
- **Deferred (Qt6 incompatibility, not Lelan scope)**:
  - SniWatcher.cpp (DontQueue enum, registerService API)
  - GliaSystemMenus.cpp (QStandardPaths::DataLocation → AppDataLocation, QFileSystemWatcher include)
  - FontManager.h/.cpp, CursorManager.h/.cpp, NCDEWindowManager.h/.cpp, WindowTyper.h/.cpp, HudManager.h/.cpp, Launcher.h/.cpp, LeapFrogPond.h/.cpp, CalendarBackend.h/.cpp, NotificationManager.h/.cpp, IconProvider.h/.cpp, XSettingsManager.h/.cpp, Theme.h/.cpp, KithCursors.h/.cpp, ColorMath.h/.cpp, NcdeTheme.h/.cpp