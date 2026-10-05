# menus-tray Agent Report — LaPivot Source Rebuild

**Agent Group:** menus-tray  
**Classes Owned:** AppMenuModel, GliaSystemMenus, SniWatcher, StatusNotifierWatcherAdaptor  
**Start Time:** 2026-10-01

---

## Progress Summary

| Class | Functions (Oracle vs Rebuilt) | Files Created | Defects Fixed | Tests Pass | Iface Check | Compile Warnings |
|-------|-------------------------------|---------------|---------------|------------|-------------|------------------|
| AppMenuModel | | | | | | |
| GliaSystemMenus | | | | | | |
| SniWatcher | | | | | | |
| StatusNotifierWatcherAdaptor | | | | | | |

---

## Doc-Promise Checklist

| # | Promise (from docs/spec) | Class::Function | Test Result |
|---|--------------------------|-----------------|-------------|
| P1 | AppMenuModel scans .desktop files and provides app categories + apps list | AppMenuModel::reload, getCategories, getApps | |
| P2 | AppMenuModel strips Exec field codes per freedesktop spec | AppMenuModel::stripFieldCodes | |
| P3 | AppMenuModel maps Categories to menu labels | AppMenuModel::mapCategory | |
| P4 | GliaSystemMenus provides applications/places/recentFiles | GliaSystemMenus::rescan, applications, places, recentFiles | |
| P5 | GliaSystemMenus launches apps via QProcess::startDetached | GliaSystemMenus::launch, openPath | |
| P6 | SniWatcher owns org.kde.StatusNotifierWatcher + org.freedesktop.StatusNotifierWatcher | SniWatcher::ctor | |
| P7 | SniWatcher tracks item lifecycle via QDBusServiceWatcher | SniWatcher::onOwnerLeft | |
| P8 | SniWatcher emits itemRegistered/itemUnregistered/hostChanged/itemsChanged | SniWatcher signals | |
| P9 | StatusNotifierWatcherAdaptor exposes RegisterStatusNotifierItem/Host, RegisteredStatusNotifierItems, IsStatusNotifierHostRegistered, ProtocolVersion | StatusNotifierWatcherAdaptor methods | |

---

## DEFECTS FIXED (to be filled)

### AppMenuModel
1. 
2. 

### GliaSystemMenus
1. 
2. 

### SniWatcher
1. 
2. 

### StatusNotifierWatcherAdaptor
1. 
2. 

---

## Test Results (to be filled)

### menus_test.sh
```
```

### tray_test.sh
```
```

---

## iface_check.sh Results (to be filled)

```
```

---

## Compile Results (to be filled)

```
```

---

## QML Files Changed (to be filled)

| File | Prebak | Reason |
|------|--------|--------|
| | | |

---

## Dependencies / Needs from Other Agents

| Class | Needed Declaration | From Agent |
|-------|-------------------|------------|
| | | |

---

## Not Done / Operator Action Needed

| Item | Details |
|------|---------|
| | |