/****************************************************************************
** Meta object code from reading C++ file 'Settings.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Settings.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN8SettingsE_t {};
} // unnamed namespace

template <> constexpr inline auto Settings::qt_create_metaobjectdata<qt_meta_tag_ZN8SettingsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Settings",
        "displaysChanged",
        "",
        "settingsChanged",
        "dockPrefsChanged",
        "wallpaperChanged",
        "path",
        "slideshowAdvanced",
        "powerChanged",
        "fontChanged",
        "storageChanged",
        "inputChanged",
        "accessibilityChanged",
        "privacyChanged",
        "securityChanged",
        "dockChanged",
        "localeChanged",
        "sessionChanged",
        "notifsChanged",
        "wallpaperPrefsChanged",
        "soundChanged",
        "screensaverFinished",
        "exitCode",
        "crashed",
        "displayChangePending",
        "seconds",
        "onScreenIdleChanged",
        "refreshDisplays",
        "applyDisplayMode",
        "name",
        "mode",
        "hz",
        "applyDisplayOrientation",
        "orient",
        "applyDisplayScale",
        "pct",
        "saveDisplay",
        "loadDisplay",
        "loadPower",
        "applyPowerSettings",
        "savePower",
        "applyFontSettings",
        "saveFontSettings",
        "saveTextColor",
        "loadStorage",
        "saveStorage",
        "loadFonts",
        "loadInput",
        "saveInput",
        "loadAccessibility",
        "saveAccessibility",
        "loadPrivacy",
        "saveConfPrivacy",
        "loadDock",
        "setDockApps",
        "QVariantList",
        "apps",
        "saveDockPrefs",
        "installedApps",
        "loadLocale",
        "saveLocale",
        "setActiveKbLayout",
        "code",
        "addKbLayout",
        "removeKbLayout",
        "loadDefaults",
        "saveDefaults",
        "loadAutostart",
        "saveAutostart",
        "json",
        "loadNotifications",
        "saveNotifications",
        "getWallpaper",
        "setWallpaper",
        "loadWallpaperPrefs",
        "saveWallpaperPrefs",
        "setSlideshowEnabled",
        "v",
        "setSlideshowInterval",
        "setFitMode",
        "loadSound",
        "saveSound",
        "saveSurfaceGlass",
        "key",
        "QColor",
        "tint",
        "shine",
        "glow",
        "border",
        "glowColor",
        "saveWidgetStyleMap",
        "QVariantMap",
        "map",
        "resetWidgetStyle",
        "saveColorOverrides",
        "saveSectionColors",
        "saveFiligreepalette",
        "hue",
        "sat",
        "palette",
        "setSlideshowPaused",
        "p",
        "saveDateTime",
        "saveNetwork",
        "saveScreensaver",
        "loadScreensaver",
        "previewScreensaver",
        "season",
        "screensaverRunning",
        "savePrivacy",
        "saveSecurity",
        "saveConfig",
        "setKickassArmed",
        "a",
        "loadKickass",
        "initWatcher",
        "confirmDisplayChange",
        "revertDisplayChange",
        "displays",
        "nightLightOn",
        "nightWarmth",
        "nightLightAuto",
        "batBlank",
        "batSuspend",
        "acBlank",
        "acSuspend",
        "lidAction",
        "powerButtonAction",
        "showBatteryPct",
        "fontFamily",
        "dockHoverTextColor",
        "topPanelTextColor",
        "gliaTextColor",
        "leapFrogTextColor",
        "accentOverride",
        "accentMutedOverride",
        "glowOverride",
        "borderOverride",
        "slideshowPaused",
        "fontWeight",
        "fontItalic",
        "fontSizeScale",
        "letterSpacing",
        "lineHeight",
        "uiScale",
        "textColor",
        "textOutlineEnabled",
        "textOutlineColor",
        "textOutlineWidth",
        "textShadowEnabled",
        "textShadowColor",
        "textShadowOffsetX",
        "textShadowOffsetY",
        "textShadowRadius",
        "autoMountUsb",
        "kbRepeatDelay",
        "kbRepeatRate",
        "pointerSpeed",
        "touchpadSpeed",
        "naturalScroll",
        "tapToClick",
        "disableWhileTyping",
        "cursorSize",
        "accessibilityTextScale",
        "highContrast",
        "reduceMotion",
        "largerCursor",
        "locationEnabled",
        "lockScreenNotifPreview",
        "screensaverTimeout",
        "screensaverSeason",
        "screensaverClockVisible",
        "screensaverFps",
        "requirePassword",
        "requirePasswordDelay",
        "kickassArmed",
        "hourFormat",
        "showSeconds",
        "ntpEnabled",
        "timezoneManual",
        "proxyEnabled",
        "proxyHost",
        "proxyPort",
        "dockIconSize",
        "dockSpacing",
        "dockZoomPercent",
        "dockZoomRange",
        "dockAnimSpeed",
        "dockMagSpring",
        "dockMagDamping",
        "dockMagMass",
        "dockApps",
        "assetBase",
        "configBase",
        "systemLanguage",
        "systemLocale",
        "kbLayouts",
        "activeKbLayout",
        "defaultBrowser",
        "defaultMail",
        "defaultFiles",
        "defaultTerminal",
        "dnd",
        "notifPosition",
        "quietHoursOn",
        "quietFrom",
        "quietTo",
        "userName",
        "customWallpapers",
        "slideshowEnabled",
        "slideshowInterval",
        "fitMode",
        "outputVolume",
        "inputVolume",
        "outputDevice",
        "inputDevice",
        "inputLevel"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'displaysChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'settingsChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dockPrefsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'wallpaperChanged'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'slideshowAdvanced'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'powerChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fontChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'storageChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'inputChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'accessibilityChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'privacyChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'securityChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dockChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'localeChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sessionChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'notifsChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'wallpaperPrefsChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'soundChanged'
        QtMocHelpers::SignalData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'screensaverFinished'
        QtMocHelpers::SignalData<void(int, bool)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 22 }, { QMetaType::Bool, 23 },
        }}),
        // Signal 'displayChangePending'
        QtMocHelpers::SignalData<void(int)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 25 },
        }}),
        // Slot 'onScreenIdleChanged'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'refreshDisplays'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'applyDisplayMode'
        QtMocHelpers::SlotData<void(const QString &, const QString &, double)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 }, { QMetaType::QString, 30 }, { QMetaType::Double, 31 },
        }}),
        // Slot 'applyDisplayOrientation'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 }, { QMetaType::QString, 33 },
        }}),
        // Slot 'applyDisplayScale'
        QtMocHelpers::SlotData<void(const QString &, int)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 }, { QMetaType::Int, 35 },
        }}),
        // Slot 'saveDisplay'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadDisplay'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadPower'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'applyPowerSettings'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'savePower'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'applyFontSettings'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveFontSettings'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveTextColor'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadStorage'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveStorage'
        QtMocHelpers::SlotData<void()>(45, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadFonts'
        QtMocHelpers::SlotData<void()>(46, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadInput'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveInput'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadAccessibility'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveAccessibility'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadPrivacy'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveConfPrivacy'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadDock'
        QtMocHelpers::SlotData<void()>(53, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setDockApps'
        QtMocHelpers::SlotData<void(const QVariantList &)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 55, 56 },
        }}),
        // Slot 'saveDockPrefs'
        QtMocHelpers::SlotData<void()>(57, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'installedApps'
        QtMocHelpers::SlotData<QVariantList()>(58, 2, QMC::AccessPublic, 0x80000000 | 55),
        // Slot 'loadLocale'
        QtMocHelpers::SlotData<void()>(59, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveLocale'
        QtMocHelpers::SlotData<void()>(60, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setActiveKbLayout'
        QtMocHelpers::SlotData<void(const QString &)>(61, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 62 },
        }}),
        // Slot 'addKbLayout'
        QtMocHelpers::SlotData<void(const QString &)>(63, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 62 },
        }}),
        // Slot 'removeKbLayout'
        QtMocHelpers::SlotData<void(const QString &)>(64, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 62 },
        }}),
        // Slot 'loadDefaults'
        QtMocHelpers::SlotData<void()>(65, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveDefaults'
        QtMocHelpers::SlotData<void()>(66, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadAutostart'
        QtMocHelpers::SlotData<QString()>(67, 2, QMC::AccessPublic, QMetaType::QString),
        // Slot 'saveAutostart'
        QtMocHelpers::SlotData<void(const QString &)>(68, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 69 },
        }}),
        // Slot 'loadNotifications'
        QtMocHelpers::SlotData<void()>(70, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveNotifications'
        QtMocHelpers::SlotData<void()>(71, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'getWallpaper'
        QtMocHelpers::SlotData<QString()>(72, 2, QMC::AccessPublic, QMetaType::QString),
        // Slot 'setWallpaper'
        QtMocHelpers::SlotData<void(const QString &)>(73, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'loadWallpaperPrefs'
        QtMocHelpers::SlotData<void()>(74, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveWallpaperPrefs'
        QtMocHelpers::SlotData<void()>(75, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setSlideshowEnabled'
        QtMocHelpers::SlotData<void(bool)>(76, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 77 },
        }}),
        // Slot 'setSlideshowInterval'
        QtMocHelpers::SlotData<void(int)>(78, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 77 },
        }}),
        // Slot 'setFitMode'
        QtMocHelpers::SlotData<void(const QString &)>(79, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 77 },
        }}),
        // Slot 'loadSound'
        QtMocHelpers::SlotData<void()>(80, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveSound'
        QtMocHelpers::SlotData<void()>(81, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveSurfaceGlass'
        QtMocHelpers::MethodData<void(const QString &, const QColor &, double, double, const QColor &, const QColor &)>(82, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 83 }, { 0x80000000 | 84, 85 }, { QMetaType::Double, 86 }, { QMetaType::Double, 87 },
            { 0x80000000 | 84, 88 }, { 0x80000000 | 84, 89 },
        }}),
        // Method 'saveWidgetStyleMap'
        QtMocHelpers::MethodData<void(const QString &, const QVariantMap &)>(90, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 83 }, { 0x80000000 | 91, 92 },
        }}),
        // Method 'resetWidgetStyle'
        QtMocHelpers::MethodData<void(const QString &)>(93, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 83 },
        }}),
        // Method 'saveColorOverrides'
        QtMocHelpers::MethodData<void()>(94, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveSectionColors'
        QtMocHelpers::MethodData<void()>(95, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveFiligreepalette'
        QtMocHelpers::MethodData<void(const QString &, double, double, const QVariantList &)>(96, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 29 }, { QMetaType::Double, 97 }, { QMetaType::Double, 98 }, { 0x80000000 | 55, 99 },
        }}),
        // Method 'setSlideshowPaused'
        QtMocHelpers::MethodData<void(bool)>(100, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 101 },
        }}),
        // Method 'saveDateTime'
        QtMocHelpers::MethodData<void()>(102, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveNetwork'
        QtMocHelpers::MethodData<void()>(103, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveScreensaver'
        QtMocHelpers::MethodData<void()>(104, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'loadScreensaver'
        QtMocHelpers::MethodData<void()>(105, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'previewScreensaver'
        QtMocHelpers::MethodData<void(const QString &)>(106, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 107 },
        }}),
        // Method 'previewScreensaver'
        QtMocHelpers::MethodData<void()>(106, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'screensaverRunning'
        QtMocHelpers::MethodData<bool()>(108, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'savePrivacy'
        QtMocHelpers::MethodData<void()>(109, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveSecurity'
        QtMocHelpers::MethodData<void()>(110, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveConfig'
        QtMocHelpers::MethodData<void()>(111, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setKickassArmed'
        QtMocHelpers::MethodData<void(bool)>(112, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 113 },
        }}),
        // Method 'loadKickass'
        QtMocHelpers::MethodData<void()>(114, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'initWatcher'
        QtMocHelpers::MethodData<void()>(115, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'confirmDisplayChange'
        QtMocHelpers::MethodData<void()>(116, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'revertDisplayChange'
        QtMocHelpers::MethodData<void()>(117, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'displays'
        QtMocHelpers::PropertyData<QVariantList>(118, 0x80000000 | 55, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'nightLightOn'
        QtMocHelpers::PropertyData<bool>(119, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'nightWarmth'
        QtMocHelpers::PropertyData<int>(120, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'nightLightAuto'
        QtMocHelpers::PropertyData<bool>(121, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'batBlank'
        QtMocHelpers::PropertyData<int>(122, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'batSuspend'
        QtMocHelpers::PropertyData<int>(123, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'acBlank'
        QtMocHelpers::PropertyData<int>(124, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'acSuspend'
        QtMocHelpers::PropertyData<int>(125, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'lidAction'
        QtMocHelpers::PropertyData<QString>(126, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'powerButtonAction'
        QtMocHelpers::PropertyData<QString>(127, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'showBatteryPct'
        QtMocHelpers::PropertyData<bool>(128, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'fontFamily'
        QtMocHelpers::PropertyData<QString>(129, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'dockHoverTextColor'
        QtMocHelpers::PropertyData<QString>(130, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'topPanelTextColor'
        QtMocHelpers::PropertyData<QString>(131, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'gliaTextColor'
        QtMocHelpers::PropertyData<QString>(132, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'leapFrogTextColor'
        QtMocHelpers::PropertyData<QString>(133, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'accentOverride'
        QtMocHelpers::PropertyData<QString>(134, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'accentMutedOverride'
        QtMocHelpers::PropertyData<QString>(135, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'glowOverride'
        QtMocHelpers::PropertyData<QString>(136, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'borderOverride'
        QtMocHelpers::PropertyData<QString>(137, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'slideshowPaused'
        QtMocHelpers::PropertyData<bool>(138, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'fontWeight'
        QtMocHelpers::PropertyData<int>(139, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'fontItalic'
        QtMocHelpers::PropertyData<bool>(140, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'fontSizeScale'
        QtMocHelpers::PropertyData<double>(141, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'letterSpacing'
        QtMocHelpers::PropertyData<double>(142, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'lineHeight'
        QtMocHelpers::PropertyData<double>(143, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'uiScale'
        QtMocHelpers::PropertyData<double>(144, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textColor'
        QtMocHelpers::PropertyData<QString>(145, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textOutlineEnabled'
        QtMocHelpers::PropertyData<bool>(146, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textOutlineColor'
        QtMocHelpers::PropertyData<QString>(147, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textOutlineWidth'
        QtMocHelpers::PropertyData<double>(148, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textShadowEnabled'
        QtMocHelpers::PropertyData<bool>(149, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textShadowColor'
        QtMocHelpers::PropertyData<QString>(150, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textShadowOffsetX'
        QtMocHelpers::PropertyData<double>(151, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textShadowOffsetY'
        QtMocHelpers::PropertyData<double>(152, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'textShadowRadius'
        QtMocHelpers::PropertyData<double>(153, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'autoMountUsb'
        QtMocHelpers::PropertyData<bool>(154, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'kbRepeatDelay'
        QtMocHelpers::PropertyData<int>(155, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'kbRepeatRate'
        QtMocHelpers::PropertyData<int>(156, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'pointerSpeed'
        QtMocHelpers::PropertyData<int>(157, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'touchpadSpeed'
        QtMocHelpers::PropertyData<int>(158, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'naturalScroll'
        QtMocHelpers::PropertyData<bool>(159, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'tapToClick'
        QtMocHelpers::PropertyData<bool>(160, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'disableWhileTyping'
        QtMocHelpers::PropertyData<bool>(161, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'cursorSize'
        QtMocHelpers::PropertyData<int>(162, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'accessibilityTextScale'
        QtMocHelpers::PropertyData<double>(163, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'highContrast'
        QtMocHelpers::PropertyData<bool>(164, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'reduceMotion'
        QtMocHelpers::PropertyData<bool>(165, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'largerCursor'
        QtMocHelpers::PropertyData<bool>(166, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'locationEnabled'
        QtMocHelpers::PropertyData<bool>(167, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'lockScreenNotifPreview'
        QtMocHelpers::PropertyData<bool>(168, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'screensaverTimeout'
        QtMocHelpers::PropertyData<int>(169, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'screensaverSeason'
        QtMocHelpers::PropertyData<QString>(170, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'screensaverClockVisible'
        QtMocHelpers::PropertyData<bool>(171, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'screensaverFps'
        QtMocHelpers::PropertyData<int>(172, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'requirePassword'
        QtMocHelpers::PropertyData<bool>(173, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'requirePasswordDelay'
        QtMocHelpers::PropertyData<int>(174, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'kickassArmed'
        QtMocHelpers::PropertyData<bool>(175, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'hourFormat'
        QtMocHelpers::PropertyData<QString>(176, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'showSeconds'
        QtMocHelpers::PropertyData<bool>(177, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'ntpEnabled'
        QtMocHelpers::PropertyData<bool>(178, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'timezoneManual'
        QtMocHelpers::PropertyData<QString>(179, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'proxyEnabled'
        QtMocHelpers::PropertyData<bool>(180, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'proxyHost'
        QtMocHelpers::PropertyData<QString>(181, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'proxyPort'
        QtMocHelpers::PropertyData<int>(182, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'dockIconSize'
        QtMocHelpers::PropertyData<int>(183, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockSpacing'
        QtMocHelpers::PropertyData<int>(184, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockZoomPercent'
        QtMocHelpers::PropertyData<double>(185, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockZoomRange'
        QtMocHelpers::PropertyData<int>(186, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockAnimSpeed'
        QtMocHelpers::PropertyData<int>(187, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockMagSpring'
        QtMocHelpers::PropertyData<double>(188, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockMagDamping'
        QtMocHelpers::PropertyData<double>(189, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockMagMass'
        QtMocHelpers::PropertyData<double>(190, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'dockApps'
        QtMocHelpers::PropertyData<QVariantList>(191, 0x80000000 | 55, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 12),
        // property 'assetBase'
        QtMocHelpers::PropertyData<QString>(192, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'configBase'
        QtMocHelpers::PropertyData<QString>(193, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'systemLanguage'
        QtMocHelpers::PropertyData<QString>(194, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'systemLocale'
        QtMocHelpers::PropertyData<QString>(195, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'kbLayouts'
        QtMocHelpers::PropertyData<QStringList>(196, QMetaType::QStringList, QMC::DefaultPropertyFlags, 13),
        // property 'activeKbLayout'
        QtMocHelpers::PropertyData<QString>(197, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'defaultBrowser'
        QtMocHelpers::PropertyData<QString>(198, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'defaultMail'
        QtMocHelpers::PropertyData<QString>(199, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'defaultFiles'
        QtMocHelpers::PropertyData<QString>(200, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'defaultTerminal'
        QtMocHelpers::PropertyData<QString>(201, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'dnd'
        QtMocHelpers::PropertyData<bool>(202, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'notifPosition'
        QtMocHelpers::PropertyData<int>(203, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'quietHoursOn'
        QtMocHelpers::PropertyData<bool>(204, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'quietFrom'
        QtMocHelpers::PropertyData<QString>(205, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'quietTo'
        QtMocHelpers::PropertyData<QString>(206, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'userName'
        QtMocHelpers::PropertyData<QString>(207, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'customWallpapers'
        QtMocHelpers::PropertyData<QStringList>(208, QMetaType::QStringList, QMC::DefaultPropertyFlags, 16),
        // property 'slideshowEnabled'
        QtMocHelpers::PropertyData<bool>(209, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'slideshowInterval'
        QtMocHelpers::PropertyData<int>(210, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'fitMode'
        QtMocHelpers::PropertyData<QString>(211, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'outputVolume'
        QtMocHelpers::PropertyData<int>(212, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'inputVolume'
        QtMocHelpers::PropertyData<int>(213, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'outputDevice'
        QtMocHelpers::PropertyData<QString>(214, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'inputDevice'
        QtMocHelpers::PropertyData<QString>(215, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'inputLevel'
        QtMocHelpers::PropertyData<double>(216, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Settings, qt_meta_tag_ZN8SettingsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Settings::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8SettingsE_t>.metaTypes,
    nullptr
} };

void Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Settings *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->displaysChanged(); break;
        case 1: _t->settingsChanged(); break;
        case 2: _t->dockPrefsChanged(); break;
        case 3: _t->wallpaperChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->slideshowAdvanced((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->powerChanged(); break;
        case 6: _t->fontChanged(); break;
        case 7: _t->storageChanged(); break;
        case 8: _t->inputChanged(); break;
        case 9: _t->accessibilityChanged(); break;
        case 10: _t->privacyChanged(); break;
        case 11: _t->securityChanged(); break;
        case 12: _t->dockChanged(); break;
        case 13: _t->localeChanged(); break;
        case 14: _t->sessionChanged(); break;
        case 15: _t->notifsChanged(); break;
        case 16: _t->wallpaperPrefsChanged(); break;
        case 17: _t->soundChanged(); break;
        case 18: _t->screensaverFinished((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 19: _t->displayChangePending((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->onScreenIdleChanged(); break;
        case 21: _t->refreshDisplays(); break;
        case 22: _t->applyDisplayMode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3]))); break;
        case 23: _t->applyDisplayOrientation((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 24: _t->applyDisplayScale((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 25: _t->saveDisplay(); break;
        case 26: _t->loadDisplay(); break;
        case 27: _t->loadPower(); break;
        case 28: _t->applyPowerSettings(); break;
        case 29: _t->savePower(); break;
        case 30: _t->applyFontSettings(); break;
        case 31: _t->saveFontSettings(); break;
        case 32: _t->saveTextColor(); break;
        case 33: _t->loadStorage(); break;
        case 34: _t->saveStorage(); break;
        case 35: _t->loadFonts(); break;
        case 36: _t->loadInput(); break;
        case 37: _t->saveInput(); break;
        case 38: _t->loadAccessibility(); break;
        case 39: _t->saveAccessibility(); break;
        case 40: _t->loadPrivacy(); break;
        case 41: _t->saveConfPrivacy(); break;
        case 42: _t->loadDock(); break;
        case 43: _t->setDockApps((*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 44: _t->saveDockPrefs(); break;
        case 45: { QVariantList _r = _t->installedApps();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 46: _t->loadLocale(); break;
        case 47: _t->saveLocale(); break;
        case 48: _t->setActiveKbLayout((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 49: _t->addKbLayout((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 50: _t->removeKbLayout((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 51: _t->loadDefaults(); break;
        case 52: _t->saveDefaults(); break;
        case 53: { QString _r = _t->loadAutostart();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 54: _t->saveAutostart((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 55: _t->loadNotifications(); break;
        case 56: _t->saveNotifications(); break;
        case 57: { QString _r = _t->getWallpaper();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->setWallpaper((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 59: _t->loadWallpaperPrefs(); break;
        case 60: _t->saveWallpaperPrefs(); break;
        case 61: _t->setSlideshowEnabled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 62: _t->setSlideshowInterval((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 63: _t->setFitMode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 64: _t->loadSound(); break;
        case 65: _t->saveSound(); break;
        case 66: _t->saveSurfaceGlass((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[6]))); break;
        case 67: _t->saveWidgetStyleMap((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[2]))); break;
        case 68: _t->resetWidgetStyle((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 69: _t->saveColorOverrides(); break;
        case 70: _t->saveSectionColors(); break;
        case 71: _t->saveFiligreepalette((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[4]))); break;
        case 72: _t->setSlideshowPaused((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 73: _t->saveDateTime(); break;
        case 74: _t->saveNetwork(); break;
        case 75: _t->saveScreensaver(); break;
        case 76: _t->loadScreensaver(); break;
        case 77: _t->previewScreensaver((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 78: _t->previewScreensaver(); break;
        case 79: { bool _r = _t->screensaverRunning();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 80: _t->savePrivacy(); break;
        case 81: _t->saveSecurity(); break;
        case 82: _t->saveConfig(); break;
        case 83: _t->setKickassArmed((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 84: _t->loadKickass(); break;
        case 85: _t->initWatcher(); break;
        case 86: _t->confirmDisplayChange(); break;
        case 87: _t->revertDisplayChange(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::displaysChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::settingsChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::dockPrefsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(const QString & )>(_a, &Settings::wallpaperChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(const QString & )>(_a, &Settings::slideshowAdvanced, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::powerChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::fontChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::storageChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::inputChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::accessibilityChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::privacyChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::securityChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::dockChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::localeChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::sessionChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::notifsChanged, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::wallpaperPrefsChanged, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)()>(_a, &Settings::soundChanged, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(int , bool )>(_a, &Settings::screensaverFinished, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (Settings::*)(int )>(_a, &Settings::displayChangePending, 19))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->displays(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->nightLightOn(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->nightWarmth(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->nightLightAuto(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->batBlank(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->batSuspend(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->acBlank(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->acSuspend(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->lidAction(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->powerButtonAction(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->showBatteryPct(); break;
        case 11: *reinterpret_cast<QString*>(_v) = _t->fontFamily(); break;
        case 12: *reinterpret_cast<QString*>(_v) = _t->dockHoverTextColor(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->topPanelTextColor(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->gliaTextColor(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->leapFrogTextColor(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->accentOverride(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->accentMutedOverride(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->glowOverride(); break;
        case 19: *reinterpret_cast<QString*>(_v) = _t->borderOverride(); break;
        case 20: *reinterpret_cast<bool*>(_v) = _t->slideshowPaused(); break;
        case 21: *reinterpret_cast<int*>(_v) = _t->fontWeight(); break;
        case 22: *reinterpret_cast<bool*>(_v) = _t->fontItalic(); break;
        case 23: *reinterpret_cast<double*>(_v) = _t->fontSizeScale(); break;
        case 24: *reinterpret_cast<double*>(_v) = _t->letterSpacing(); break;
        case 25: *reinterpret_cast<double*>(_v) = _t->lineHeight(); break;
        case 26: *reinterpret_cast<double*>(_v) = _t->uiScale(); break;
        case 27: *reinterpret_cast<QString*>(_v) = _t->textColor(); break;
        case 28: *reinterpret_cast<bool*>(_v) = _t->textOutlineEnabled(); break;
        case 29: *reinterpret_cast<QString*>(_v) = _t->textOutlineColor(); break;
        case 30: *reinterpret_cast<double*>(_v) = _t->textOutlineWidth(); break;
        case 31: *reinterpret_cast<bool*>(_v) = _t->textShadowEnabled(); break;
        case 32: *reinterpret_cast<QString*>(_v) = _t->textShadowColor(); break;
        case 33: *reinterpret_cast<double*>(_v) = _t->textShadowOffsetX(); break;
        case 34: *reinterpret_cast<double*>(_v) = _t->textShadowOffsetY(); break;
        case 35: *reinterpret_cast<double*>(_v) = _t->textShadowRadius(); break;
        case 36: *reinterpret_cast<bool*>(_v) = _t->autoMountUsb(); break;
        case 37: *reinterpret_cast<int*>(_v) = _t->kbRepeatDelay(); break;
        case 38: *reinterpret_cast<int*>(_v) = _t->kbRepeatRate(); break;
        case 39: *reinterpret_cast<int*>(_v) = _t->pointerSpeed(); break;
        case 40: *reinterpret_cast<int*>(_v) = _t->touchpadSpeed(); break;
        case 41: *reinterpret_cast<bool*>(_v) = _t->naturalScroll(); break;
        case 42: *reinterpret_cast<bool*>(_v) = _t->tapToClick(); break;
        case 43: *reinterpret_cast<bool*>(_v) = _t->disableWhileTyping(); break;
        case 44: *reinterpret_cast<int*>(_v) = _t->cursorSize(); break;
        case 45: *reinterpret_cast<double*>(_v) = _t->accessibilityTextScale(); break;
        case 46: *reinterpret_cast<bool*>(_v) = _t->highContrast(); break;
        case 47: *reinterpret_cast<bool*>(_v) = _t->reduceMotion(); break;
        case 48: *reinterpret_cast<bool*>(_v) = _t->largerCursor(); break;
        case 49: *reinterpret_cast<bool*>(_v) = _t->locationEnabled(); break;
        case 50: *reinterpret_cast<bool*>(_v) = _t->lockScreenNotifPreview(); break;
        case 51: *reinterpret_cast<int*>(_v) = _t->screensaverTimeout(); break;
        case 52: *reinterpret_cast<QString*>(_v) = _t->screensaverSeason(); break;
        case 53: *reinterpret_cast<bool*>(_v) = _t->screensaverClockVisible(); break;
        case 54: *reinterpret_cast<int*>(_v) = _t->screensaverFps(); break;
        case 55: *reinterpret_cast<bool*>(_v) = _t->requirePassword(); break;
        case 56: *reinterpret_cast<int*>(_v) = _t->requirePasswordDelay(); break;
        case 57: *reinterpret_cast<bool*>(_v) = _t->kickassArmed(); break;
        case 58: *reinterpret_cast<QString*>(_v) = _t->hourFormat(); break;
        case 59: *reinterpret_cast<bool*>(_v) = _t->showSeconds(); break;
        case 60: *reinterpret_cast<bool*>(_v) = _t->ntpEnabled(); break;
        case 61: *reinterpret_cast<QString*>(_v) = _t->timezoneManual(); break;
        case 62: *reinterpret_cast<bool*>(_v) = _t->proxyEnabled(); break;
        case 63: *reinterpret_cast<QString*>(_v) = _t->proxyHost(); break;
        case 64: *reinterpret_cast<int*>(_v) = _t->proxyPort(); break;
        case 65: *reinterpret_cast<int*>(_v) = _t->dockIconSize(); break;
        case 66: *reinterpret_cast<int*>(_v) = _t->dockSpacing(); break;
        case 67: *reinterpret_cast<double*>(_v) = _t->dockZoomPercent(); break;
        case 68: *reinterpret_cast<int*>(_v) = _t->dockZoomRange(); break;
        case 69: *reinterpret_cast<int*>(_v) = _t->dockAnimSpeed(); break;
        case 70: *reinterpret_cast<double*>(_v) = _t->dockMagSpring(); break;
        case 71: *reinterpret_cast<double*>(_v) = _t->dockMagDamping(); break;
        case 72: *reinterpret_cast<double*>(_v) = _t->dockMagMass(); break;
        case 73: *reinterpret_cast<QVariantList*>(_v) = _t->dockApps(); break;
        case 74: *reinterpret_cast<QString*>(_v) = _t->assetBase(); break;
        case 75: *reinterpret_cast<QString*>(_v) = _t->configBase(); break;
        case 76: *reinterpret_cast<QString*>(_v) = _t->systemLanguage(); break;
        case 77: *reinterpret_cast<QString*>(_v) = _t->systemLocale(); break;
        case 78: *reinterpret_cast<QStringList*>(_v) = _t->kbLayouts(); break;
        case 79: *reinterpret_cast<QString*>(_v) = _t->activeKbLayout(); break;
        case 80: *reinterpret_cast<QString*>(_v) = _t->defaultBrowser(); break;
        case 81: *reinterpret_cast<QString*>(_v) = _t->defaultMail(); break;
        case 82: *reinterpret_cast<QString*>(_v) = _t->defaultFiles(); break;
        case 83: *reinterpret_cast<QString*>(_v) = _t->defaultTerminal(); break;
        case 84: *reinterpret_cast<bool*>(_v) = _t->dnd(); break;
        case 85: *reinterpret_cast<int*>(_v) = _t->notifPosition(); break;
        case 86: *reinterpret_cast<bool*>(_v) = _t->quietHoursOn(); break;
        case 87: *reinterpret_cast<QString*>(_v) = _t->quietFrom(); break;
        case 88: *reinterpret_cast<QString*>(_v) = _t->quietTo(); break;
        case 89: *reinterpret_cast<QString*>(_v) = _t->userName(); break;
        case 90: *reinterpret_cast<QStringList*>(_v) = _t->customWallpapers(); break;
        case 91: *reinterpret_cast<bool*>(_v) = _t->slideshowEnabled(); break;
        case 92: *reinterpret_cast<int*>(_v) = _t->slideshowInterval(); break;
        case 93: *reinterpret_cast<QString*>(_v) = _t->fitMode(); break;
        case 94: *reinterpret_cast<int*>(_v) = _t->outputVolume(); break;
        case 95: *reinterpret_cast<int*>(_v) = _t->inputVolume(); break;
        case 96: *reinterpret_cast<QString*>(_v) = _t->outputDevice(); break;
        case 97: *reinterpret_cast<QString*>(_v) = _t->inputDevice(); break;
        case 98: *reinterpret_cast<double*>(_v) = _t->inputLevel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setNightLightOn(*reinterpret_cast<bool*>(_v)); break;
        case 2: _t->setNightWarmth(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setNightLightAuto(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setBatBlank(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setBatSuspend(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setAcBlank(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setAcSuspend(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setLidAction(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setPowerButtonAction(*reinterpret_cast<QString*>(_v)); break;
        case 10: _t->setShowBatteryPct(*reinterpret_cast<bool*>(_v)); break;
        case 11: _t->setFontFamily(*reinterpret_cast<QString*>(_v)); break;
        case 12: _t->setDockHoverTextColor(*reinterpret_cast<QString*>(_v)); break;
        case 13: _t->setTopPanelTextColor(*reinterpret_cast<QString*>(_v)); break;
        case 14: _t->setGliaTextColor(*reinterpret_cast<QString*>(_v)); break;
        case 15: _t->setLeapFrogTextColor(*reinterpret_cast<QString*>(_v)); break;
        case 16: _t->setAccentOverride(*reinterpret_cast<QString*>(_v)); break;
        case 17: _t->setAccentMutedOverride(*reinterpret_cast<QString*>(_v)); break;
        case 18: _t->setGlowOverride(*reinterpret_cast<QString*>(_v)); break;
        case 19: _t->setBorderOverride(*reinterpret_cast<QString*>(_v)); break;
        case 20: _t->setSlideshowPaused(*reinterpret_cast<bool*>(_v)); break;
        case 21: _t->setFontWeight(*reinterpret_cast<int*>(_v)); break;
        case 22: _t->setFontItalic(*reinterpret_cast<bool*>(_v)); break;
        case 23: _t->setFontSizeScale(*reinterpret_cast<double*>(_v)); break;
        case 24: _t->setLetterSpacing(*reinterpret_cast<double*>(_v)); break;
        case 25: _t->setLineHeight(*reinterpret_cast<double*>(_v)); break;
        case 26: _t->setUiScale(*reinterpret_cast<double*>(_v)); break;
        case 27: _t->setTextColor(*reinterpret_cast<QString*>(_v)); break;
        case 28: _t->setTextOutlineEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 29: _t->setTextOutlineColor(*reinterpret_cast<QString*>(_v)); break;
        case 30: _t->setTextOutlineWidth(*reinterpret_cast<double*>(_v)); break;
        case 31: _t->setTextShadowEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 32: _t->setTextShadowColor(*reinterpret_cast<QString*>(_v)); break;
        case 33: _t->setTextShadowOffsetX(*reinterpret_cast<double*>(_v)); break;
        case 34: _t->setTextShadowOffsetY(*reinterpret_cast<double*>(_v)); break;
        case 35: _t->setTextShadowRadius(*reinterpret_cast<double*>(_v)); break;
        case 36: _t->setAutoMountUsb(*reinterpret_cast<bool*>(_v)); break;
        case 37: _t->setKbRepeatDelay(*reinterpret_cast<int*>(_v)); break;
        case 38: _t->setKbRepeatRate(*reinterpret_cast<int*>(_v)); break;
        case 39: _t->setPointerSpeed(*reinterpret_cast<int*>(_v)); break;
        case 40: _t->setTouchpadSpeed(*reinterpret_cast<int*>(_v)); break;
        case 41: _t->setNaturalScroll(*reinterpret_cast<bool*>(_v)); break;
        case 42: _t->setTapToClick(*reinterpret_cast<bool*>(_v)); break;
        case 43: _t->setDisableWhileTyping(*reinterpret_cast<bool*>(_v)); break;
        case 44: _t->setCursorSize(*reinterpret_cast<int*>(_v)); break;
        case 45: _t->setAccessibilityTextScale(*reinterpret_cast<double*>(_v)); break;
        case 46: _t->setHighContrast(*reinterpret_cast<bool*>(_v)); break;
        case 47: _t->setReduceMotion(*reinterpret_cast<bool*>(_v)); break;
        case 48: _t->setLargerCursor(*reinterpret_cast<bool*>(_v)); break;
        case 49: _t->setLocationEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 50: _t->setLockScreenNotifPreview(*reinterpret_cast<bool*>(_v)); break;
        case 51: _t->setScreensaverTimeout(*reinterpret_cast<int*>(_v)); break;
        case 52: _t->setScreensaverSeason(*reinterpret_cast<QString*>(_v)); break;
        case 53: _t->setScreensaverClockVisible(*reinterpret_cast<bool*>(_v)); break;
        case 54: _t->setScreensaverFps(*reinterpret_cast<int*>(_v)); break;
        case 55: _t->setRequirePassword(*reinterpret_cast<bool*>(_v)); break;
        case 56: _t->setRequirePasswordDelay(*reinterpret_cast<int*>(_v)); break;
        case 57: _t->setKickassArmed(*reinterpret_cast<bool*>(_v)); break;
        case 58: _t->setHourFormat(*reinterpret_cast<QString*>(_v)); break;
        case 59: _t->setShowSeconds(*reinterpret_cast<bool*>(_v)); break;
        case 60: _t->setNtpEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 61: _t->setTimezoneManual(*reinterpret_cast<QString*>(_v)); break;
        case 62: _t->setProxyEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 63: _t->setProxyHost(*reinterpret_cast<QString*>(_v)); break;
        case 64: _t->setProxyPort(*reinterpret_cast<int*>(_v)); break;
        case 65: _t->setDockIconSize(*reinterpret_cast<int*>(_v)); break;
        case 66: _t->setDockSpacing(*reinterpret_cast<int*>(_v)); break;
        case 67: _t->setDockZoomPercent(*reinterpret_cast<double*>(_v)); break;
        case 68: _t->setDockZoomRange(*reinterpret_cast<int*>(_v)); break;
        case 69: _t->setDockAnimSpeed(*reinterpret_cast<int*>(_v)); break;
        case 70: _t->setDockMagSpring(*reinterpret_cast<double*>(_v)); break;
        case 71: _t->setDockMagDamping(*reinterpret_cast<double*>(_v)); break;
        case 72: _t->setDockMagMass(*reinterpret_cast<double*>(_v)); break;
        case 76: _t->setSystemLanguage(*reinterpret_cast<QString*>(_v)); break;
        case 77: _t->setSystemLocale(*reinterpret_cast<QString*>(_v)); break;
        case 79: _t->setActiveKbLayout(*reinterpret_cast<QString*>(_v)); break;
        case 80: _t->setDefaultBrowser(*reinterpret_cast<QString*>(_v)); break;
        case 81: _t->setDefaultMail(*reinterpret_cast<QString*>(_v)); break;
        case 82: _t->setDefaultFiles(*reinterpret_cast<QString*>(_v)); break;
        case 83: _t->setDefaultTerminal(*reinterpret_cast<QString*>(_v)); break;
        case 84: _t->setDnd(*reinterpret_cast<bool*>(_v)); break;
        case 85: _t->setNotifPosition(*reinterpret_cast<int*>(_v)); break;
        case 86: _t->setQuietHoursOn(*reinterpret_cast<bool*>(_v)); break;
        case 87: _t->setQuietFrom(*reinterpret_cast<QString*>(_v)); break;
        case 88: _t->setQuietTo(*reinterpret_cast<QString*>(_v)); break;
        case 91: _t->setSlideshowEnabled(*reinterpret_cast<bool*>(_v)); break;
        case 92: _t->setSlideshowInterval(*reinterpret_cast<int*>(_v)); break;
        case 93: _t->setFitMode(*reinterpret_cast<QString*>(_v)); break;
        case 94: _t->setOutputVolume(*reinterpret_cast<int*>(_v)); break;
        case 95: _t->setInputVolume(*reinterpret_cast<int*>(_v)); break;
        case 96: _t->setOutputDevice(*reinterpret_cast<QString*>(_v)); break;
        case 97: _t->setInputDevice(*reinterpret_cast<QString*>(_v)); break;
        case 98: _t->setInputLevel(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SettingsE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 88)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 88;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 88)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 88;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 99;
    }
    return _id;
}

// SIGNAL 0
void Settings::displaysChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Settings::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Settings::dockPrefsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Settings::wallpaperChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Settings::slideshowAdvanced(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Settings::powerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Settings::fontChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Settings::storageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Settings::inputChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Settings::accessibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Settings::privacyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Settings::securityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void Settings::dockChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void Settings::localeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void Settings::sessionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void Settings::notifsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void Settings::wallpaperPrefsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void Settings::soundChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void Settings::screensaverFinished(int _t1, bool _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 18, nullptr, _t1, _t2);
}

// SIGNAL 19
void Settings::displayChangePending(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 19, nullptr, _t1);
}
QT_WARNING_POP
