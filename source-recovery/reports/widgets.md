# Widgets Group Rebuild Report

**Date:** 2026-10-01  
**Agent Group:** widgets  
**Classes:** WidgetData, NotificationManager, Launcher, HudManager

---

## 1. WidgetData

### Oracle Interface (from metaobjects)
- 35 Q_PROPERTYs
- 7 signals: changed, clockChanged, statsChanged, weatherChanged, moonPositionChanged, mediaChanged, mediaPositionChanged
- 8 Q_INVOKABLEs: setVolume, toggleMute, mediaTogglePlay, mediaNext, mediaPrev, mediaSeek, mountVolume, unmountVolume

### DEFECTS TO FIX
1. **Panel clock ignores Settings hourFormat/showSeconds** — `timeHour`/`timeMinute`/`timeAMPM` use hardcoded 12-hour format. Must add `setSettings(Settings*)` and follow `hourFormat` ("auto"/"12"/"24") and `showSeconds`.
2. **setVolume routes to Lelan correctly** — but SoundTab.qml calls `widget_data.setVolume`; must ensure it forwards to `Lelan::setVolume`.
3. **19-22% idle CPU** — `onPulse` runs every tick, `readStats` every 3rd tick (or 60th when screen idle), `fetchWeather` at tick 5 and every 1800. Must gate on visibility/animPolicy per anim-policy.md §4.4.

### Files to Create
- `src/WidgetData.h`
- `src/WidgetData_time.cpp` (clock/date/greeting)
- `src/WidgetData_stats.cpp` (CPU/RAM/disk/net/battery/uptime)
- `src/WidgetData_weather.cpp` (weather/moon)
- `src/WidgetData_media.cpp` (MPRIS pass-through)
- `src/WidgetData_storage.cpp` (volumes)
- `src/WidgetData.cpp` (constructor, setLelan, setAnimPolicy, setSettings, onPulse)

### Tests
- `tests/widget_data_test.cpp` + `tests/widget_data_test.sh`

### QML Changes
- TopPanel.qml: may need AM/PM text handling (report to coordinator)
- SoundTab.qml: already uses widget_data.setVolume (OK if forwarded)

---

## 2. NotificationManager

### Oracle Interface
- 4 Q_PROPERTYs: notifications, hasNotifications, unreadCount, notifyApps
- 2 signals: changed, appsChanged
- 5 Q_INVOKABLEs: setAppNotify, notify, dismiss, dismissAll, markRead

### DEFECTS TO FIX
1. **DND + quiet hours not enforced** — `notify()` reads `inQuietHours()` but `inQuietHours()` reads from a `QObject*` property (Settings) that is set via `setSettings()`. The Settings properties `dnd`, `quietHoursOn`, `quietFrom`, `quietTo` exist but nothing connects them. Must wire `setSettings(Settings*)` and check `dnd` + quiet hours in `notify()`.
2. **Quiet hours cross midnight** — `quietFrom "10:00 PM"`, `quietTo "7:00 AM"` — current `inQuietHours()` logic handles this but is never used because Settings not connected.
3. **org.freedesktop.Notifications ownership** — Oracle LaPivot registers `org.ncde.desktop`, NOT `org.freedesktop.Notifications`. Per ncde-architecture.md §7, LaPivot (ncde-wm) **owns** `org.freedesktop.Notifications`. Must implement the FreedesktopNotificationsAdaptor and register the correct service name.

### Files to Create
- `src/NotificationManager.h`
- `src/NotificationManager.cpp` (core + FreedesktopNotificationsAdaptor)
- `src/FreedesktopNotificationsAdaptor.h/.cpp`

### Tests
- `tests/notif_test.cpp` + `tests/notif_test.sh` (private dbus-daemon)
- `tests/notif_qml_host.cpp` + `tests/notif_qml_test.sh`

### QML Changes
- NotificationsTab.qml: already binds to settings.dnd/quietHours* (OK once backend wired)

---

## 3. Launcher

### Oracle Interface
- 0 Q_PROPERTYs
- 0 signals
- 6 Q_INVOKABLEs: launchExec, launch, systemCommand, launchWithFiles, homePath, logout

### DEFECTS TO FIX
- None identified in decompile; straightforward pass-through to QProcess.

### Files to Create
- `src/Launcher.h`
- `src/Launcher.cpp`

### Tests
- `tests/launcher_test.cpp` + `tests/launcher_test.sh`

---

## 4. HudManager

### Oracle Interface
- 0 Q_PROPERTYs
- 2 signals: hudRequested, hudDismissed
- 2 Q_INVOKABLEs: requestHud, dismissHud

### DEFECTS TO FIX
- None identified; simple signal forwarder.

### Files to Create
- `src/HudManager.h`
- `src/HudManager.cpp`

### Tests
- `tests/hud_test.cpp` + `tests/hud_test.sh`

---

## Build & Integration

### Interface Additions (tests/iface_additions/)
- `WidgetData.txt`: `setSettings(Settings*)` slot
- `NotificationManager.txt`: `setSettings(Settings*)` slot + FreedesktopNotificationsAdaptor registration
- `Launcher.txt`: (none)
- `HudManager.txt`: (none)

### Compile Target
- `bash tests/compile_all.sh` → 0 warnings, full link

### Coordinator Integration Points
- TopPanel.qml: may need AM/PM label handling (WidgetData will emit clockChanged with formatted strings)
- Main.cpp: must instantiate WidgetData, NotificationManager, Launcher, HudManager and set context properties
- Lelan: WidgetData needs Lelan pointer (already has setLelan); NotificationManager needs Settings pointer

---

## Progress Tracker

| Class | Header | Implementation | Tests | iface_check | QML fixes | Compile |
|-------|--------|----------------|-------|-------------|-----------|---------|
| WidgetData | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| NotificationManager | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| Launcher | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |
| HudManager | ☐ | ☐ | ☐ | ☐ | ☐ | ☐ |