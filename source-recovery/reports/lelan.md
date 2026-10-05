# reports/lelan.md — group "lelan" (third launch 2026-10-01)

Status: IN PROGRESS (written incrementally).

Survivors from the dead runs: none of mine (find -newermt '2026-09-30 18:50' showed only Settings/colour/display files).

## Missing Lelan symbols at start (measured: all src/Lelan_*.cpp + ZenGovernor + AnimPolicy + moc compiled, undefined _ZN5Lelan*)
47 undefined: ctor/dtor, onPulse, onCoalescedTick, applyProperties, fetchAndApply, systemFont, filigreePalette,
users/userName/addUser/removeUser/changePassword/setUserAdmin/setAutoLogin/setUserAvatar, printers/setDefaultPrinter/
removePrinter, tray/notifications/rebuildTray/onTrayItemChanged/onLayoutUpdated/onActionInvoked, kickass +
5 onKickass*, updates + subscribeToPackageKit + 3 onPackageKit*, 9 onSentinel* device slots, onWMScreenConfig.
(Private oracle helpers not in Lelan.h: setEngine, refreshUsers, refreshPrinters, updateCurrentUserName,
subscribeTrayOwner, fetchPackageKitUpdates.)

## Work-list item: "QDBusArgument: write from a read-only object" x6 at oracle start — SOURCE FOUND
objdump of the oracle's Lelan::applyPortalAppearance: it calls the NON-const `QDBusArgument::beginStructure()@plt`
and `QDBusArgument::endStructure()@plt` (write side) on the demarshalling argument of accent-color, then
`operator>>(double&) const` x3. Each accent-color apply = 2 warnings (begin + end); 3 applies = 6. The rebuilt
Lelan_portal.cpp uses `const QDBusArgument arg` -> the const (read) begin/endStructure: no warning (test below).

## Third-launch implementation progress (2026-10-01)

Independently checked the decompile's 306 unique top-level `Lelan::` entries against `src/Lelan_*.cpp`,
`Lelan.h`, and moc-generated members. The initial 47 undefined methods listed above now have owned
implementations across `Lelan_core.cpp`, `Lelan_kickass.cpp`, `Lelan_packages.cpp`, `Lelan_users.cpp`,
`Lelan_printers.cpp`, `Lelan_tray.cpp`, and `Lelan_devices.cpp`. Also restored the omitted
`syncWifiConnectedFlag` and `applyZenStartupHints` entry points. The remaining name-only mismatches are
compiler/moc-generated methods, methods moved to `ZenGovernor` (`checkCpuFreq`, `checkThermalZones`,
`discoverThermalThresholds`, `updatePressure`), and the recurring `scheduleNightLightEvents` replaced by
the coalesced `updateNightFlag`; no source promise is intentionally left without an implementation path.

Incremental edits:
- `Lelan_core.cpp`: constructor member initializer list follows declaration order (removes `-Wreorder`);
  wires account/printer/SNI subscriptions; the 1 s coarse timer now calls `onPulse`, which emits pulse,
  advances media position, and calls `onCoalescedTick` each 60 ticks.
- `Lelan_packages.cpp`: fixes `GetUpdates(as)` arguments; collects asynchronous transaction package/finish
  signals and drops old transaction signal subscriptions when refreshes supersede it.
- `Lelan_users.cpp`: new async AccountsService CRUD/property backend; queues a newly created user's
  password until `CreateUser` finishes, protects root/current-user deletion, validates names/avatar paths.
- `Lelan_printers.cpp`: new asynchronous `lpstat` inventory and argv-only `lpadmin` writes; no shell,
  GUI-thread wait, or write runs except on an explicit QML action.
- `Lelan_tray.cpp`: new SNI watcher/property and menu-layout subscriptions, plus notification action events.
- `Lelan_devices.cpp`: input hotplug addition signal was already present and retained.
- `UsersTab.qml`, `PrintersTab.qml`: backed up as `.prebak-20261001-lelan` before edits; account/printer
  bindings now target `lelan.*`. AboutTab already targets `lelan.systemInfo`; no edit needed.
- `tests/iface_additions/Lelan.txt`: lists three new private AccountsService D-Bus slots.

First measured validation: direct `g++ -Wall -Wextra -Wreorder` object compilation passed for the changed
core, Kickass, PackageKit, users, printers, tray, devices, session, and power translation units (no warnings).
This is targeted source validation, not `compile_all.sh` or CMake. Next: private-bus service fakes, interface
check, QML lint, and final symbol coverage report.
