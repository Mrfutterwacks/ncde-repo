/****************************************************************************
** Meta object code from reading C++ file 'NCDEEngine.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/NCDEEngine.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NCDEEngine.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10NCDEEngineE_t {};
} // unnamed namespace

template <> constexpr inline auto NCDEEngine::qt_create_metaobjectdata<qt_meta_tag_ZN10NCDEEngineE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NCDEEngine",
        "changed",
        "",
        "themeChanged",
        "darkModeChanged",
        "previewReady",
        "QVariantMap",
        "palette",
        "filigreePalettesChanged",
        "presets",
        "QVariantList",
        "applyPreset",
        "id",
        "currentBasePalette",
        "sampleWallpaper",
        "path",
        "previewWallpaper",
        "previewWallpaperAsync",
        "setSurfaceGlass",
        "key",
        "QColor",
        "tint",
        "shine",
        "glow",
        "border",
        "glowColor",
        "surfaceGlass",
        "setWidgetStyleMap",
        "map",
        "setWidgetStyle",
        "accent",
        "fill",
        "font",
        "widgetStyle",
        "resetWidgetStyle",
        "setOverrideAccent",
        "hex",
        "setOverrideAccentMuted",
        "setOverrideBorder",
        "setOverrideGlow",
        "setBodyFont",
        "f",
        "setTitleFont",
        "setMonoFont",
        "setDisplayFont",
        "setFellFont",
        "setGarFont",
        "setUiScale",
        "s",
        "setFontSizeScale",
        "setLetterSpacing",
        "v",
        "setLineHeight",
        "recomputeFontSizes",
        "toJson",
        "saveTheme",
        "loadTheme",
        "setTerminalFont",
        "setTerminalGlassTint",
        "terminalConfig",
        "saveFiligreepalette",
        "name",
        "colors",
        "deleteFiligreepalette",
        "setActiveFiligreepalette",
        "accentMuted",
        "background",
        "surface",
        "surfaceAlt",
        "surfaceHi",
        "panelBg",
        "panelText",
        "popupBg",
        "ink",
        "inkSoft",
        "verd",
        "cer",
        "rose",
        "amber",
        "clockColor",
        "lamp",
        "gilt0",
        "gilt1",
        "gilt2",
        "gilt3",
        "gilt4",
        "gilt5",
        "wine1",
        "wine2",
        "wine3",
        "wine4",
        "widgetC0",
        "widgetC1",
        "widgetC2",
        "widgetC3",
        "widgetC4",
        "widgetC5",
        "foreground",
        "topShadow",
        "bottomShadow",
        "selectColor",
        "activeBg",
        "activeFg",
        "activeTs",
        "activeBs",
        "inactiveBg",
        "inactiveFg",
        "inactiveTs",
        "inactiveBs",
        "darkMode",
        "activeFiligreePaletteName",
        "activeFiligreePalette",
        "filigreePalettes",
        "presetActive",
        "usingCustomBase",
        "fontSize_sm",
        "fontSize_md",
        "fontSize_lg",
        "letterSpacing",
        "lineHeight",
        "themeName",
        "accentName",
        "darkModeLock",
        "overrideAccent",
        "overrideAccentMuted",
        "overrideBorder",
        "overrideGlow",
        "bodyFont",
        "titleFont",
        "monoFont",
        "displayFont",
        "fellFont",
        "garFont",
        "version"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'themeChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'darkModeChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'previewReady'
        QtMocHelpers::SignalData<void(const QVariantMap &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'filigreePalettesChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'presets'
        QtMocHelpers::MethodData<QVariantList()>(9, 2, QMC::AccessPublic, 0x80000000 | 10),
        // Method 'applyPreset'
        QtMocHelpers::MethodData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Method 'currentBasePalette'
        QtMocHelpers::MethodData<QVariantMap()>(13, 2, QMC::AccessPublic, 0x80000000 | 6),
        // Method 'sampleWallpaper'
        QtMocHelpers::MethodData<bool(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'previewWallpaper'
        QtMocHelpers::MethodData<QVariantMap(const QString &)>(16, 2, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'previewWallpaperAsync'
        QtMocHelpers::MethodData<void(const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'setSurfaceGlass'
        QtMocHelpers::MethodData<void(const QString &, const QColor &, double, double, const QColor &, const QColor &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { 0x80000000 | 20, 21 }, { QMetaType::Double, 22 }, { QMetaType::Double, 23 },
            { 0x80000000 | 20, 24 }, { 0x80000000 | 20, 25 },
        }}),
        // Method 'surfaceGlass'
        QtMocHelpers::MethodData<QVariantMap(const QString &)>(26, 2, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'setWidgetStyleMap'
        QtMocHelpers::MethodData<void(const QString &, const QVariantMap &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { 0x80000000 | 6, 28 },
        }}),
        // Method 'setWidgetStyle'
        QtMocHelpers::MethodData<void(const QString &, const QColor &, const QColor &, const QString &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { 0x80000000 | 20, 30 }, { 0x80000000 | 20, 31 }, { QMetaType::QString, 32 },
        }}),
        // Method 'widgetStyle'
        QtMocHelpers::MethodData<QVariantMap(const QString &)>(33, 2, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'resetWidgetStyle'
        QtMocHelpers::MethodData<void(const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Method 'setOverrideAccent'
        QtMocHelpers::MethodData<void(const QString &)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'setOverrideAccentMuted'
        QtMocHelpers::MethodData<void(const QString &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'setOverrideBorder'
        QtMocHelpers::MethodData<void(const QString &)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'setOverrideGlow'
        QtMocHelpers::MethodData<void(const QString &)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Method 'setBodyFont'
        QtMocHelpers::MethodData<void(const QString &)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setTitleFont'
        QtMocHelpers::MethodData<void(const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setMonoFont'
        QtMocHelpers::MethodData<void(const QString &)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setDisplayFont'
        QtMocHelpers::MethodData<void(const QString &)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setFellFont'
        QtMocHelpers::MethodData<void(const QString &)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setGarFont'
        QtMocHelpers::MethodData<void(const QString &)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 41 },
        }}),
        // Method 'setUiScale'
        QtMocHelpers::MethodData<void(double)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 48 },
        }}),
        // Method 'setFontSizeScale'
        QtMocHelpers::MethodData<void(double)>(49, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 48 },
        }}),
        // Method 'setLetterSpacing'
        QtMocHelpers::MethodData<void(double)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 51 },
        }}),
        // Method 'setLineHeight'
        QtMocHelpers::MethodData<void(double)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 51 },
        }}),
        // Method 'recomputeFontSizes'
        QtMocHelpers::MethodData<void()>(53, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'toJson'
        QtMocHelpers::MethodData<QVariantMap()>(54, 2, QMC::AccessPublic, 0x80000000 | 6),
        // Method 'saveTheme'
        QtMocHelpers::MethodData<bool(const QString &)>(55, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'loadTheme'
        QtMocHelpers::MethodData<bool(const QString &)>(56, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'setTerminalFont'
        QtMocHelpers::MethodData<void(const QString &)>(57, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 32 },
        }}),
        // Method 'setTerminalGlassTint'
        QtMocHelpers::MethodData<void(double)>(58, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 21 },
        }}),
        // Method 'terminalConfig'
        QtMocHelpers::MethodData<QVariantMap()>(59, 2, QMC::AccessPublic, 0x80000000 | 6),
        // Method 'saveFiligreepalette'
        QtMocHelpers::MethodData<bool(const QString &, const QVariantMap &)>(60, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 61 }, { 0x80000000 | 6, 62 },
        }}),
        // Method 'deleteFiligreepalette'
        QtMocHelpers::MethodData<bool(const QString &)>(63, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 61 },
        }}),
        // Method 'setActiveFiligreepalette'
        QtMocHelpers::MethodData<bool(const QString &)>(64, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 61 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'accent'
        QtMocHelpers::PropertyData<QColor>(30, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'accentMuted'
        QtMocHelpers::PropertyData<QColor>(65, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'background'
        QtMocHelpers::PropertyData<QColor>(66, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'surface'
        QtMocHelpers::PropertyData<QColor>(67, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'surfaceAlt'
        QtMocHelpers::PropertyData<QColor>(68, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'surfaceHi'
        QtMocHelpers::PropertyData<QColor>(69, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'panelBg'
        QtMocHelpers::PropertyData<QColor>(70, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'panelText'
        QtMocHelpers::PropertyData<QColor>(71, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'popupBg'
        QtMocHelpers::PropertyData<QColor>(72, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'border'
        QtMocHelpers::PropertyData<QColor>(24, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'glow'
        QtMocHelpers::PropertyData<QColor>(23, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'ink'
        QtMocHelpers::PropertyData<QColor>(73, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'inkSoft'
        QtMocHelpers::PropertyData<QColor>(74, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'verd'
        QtMocHelpers::PropertyData<QColor>(75, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'cer'
        QtMocHelpers::PropertyData<QColor>(76, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'rose'
        QtMocHelpers::PropertyData<QColor>(77, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'amber'
        QtMocHelpers::PropertyData<QColor>(78, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'clockColor'
        QtMocHelpers::PropertyData<QColor>(79, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'lamp'
        QtMocHelpers::PropertyData<QColor>(80, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt0'
        QtMocHelpers::PropertyData<QColor>(81, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt1'
        QtMocHelpers::PropertyData<QColor>(82, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt2'
        QtMocHelpers::PropertyData<QColor>(83, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt3'
        QtMocHelpers::PropertyData<QColor>(84, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt4'
        QtMocHelpers::PropertyData<QColor>(85, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt5'
        QtMocHelpers::PropertyData<QColor>(86, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'wine1'
        QtMocHelpers::PropertyData<QColor>(87, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'wine2'
        QtMocHelpers::PropertyData<QColor>(88, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'wine3'
        QtMocHelpers::PropertyData<QColor>(89, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'wine4'
        QtMocHelpers::PropertyData<QColor>(90, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC0'
        QtMocHelpers::PropertyData<QColor>(91, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC1'
        QtMocHelpers::PropertyData<QColor>(92, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC2'
        QtMocHelpers::PropertyData<QColor>(93, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC3'
        QtMocHelpers::PropertyData<QColor>(94, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC4'
        QtMocHelpers::PropertyData<QColor>(95, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'widgetC5'
        QtMocHelpers::PropertyData<QColor>(96, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'foreground'
        QtMocHelpers::PropertyData<QColor>(97, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'topShadow'
        QtMocHelpers::PropertyData<QColor>(98, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'bottomShadow'
        QtMocHelpers::PropertyData<QColor>(99, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'selectColor'
        QtMocHelpers::PropertyData<QColor>(100, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'activeBg'
        QtMocHelpers::PropertyData<QColor>(101, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'activeFg'
        QtMocHelpers::PropertyData<QColor>(102, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'activeTs'
        QtMocHelpers::PropertyData<QColor>(103, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'activeBs'
        QtMocHelpers::PropertyData<QColor>(104, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'inactiveBg'
        QtMocHelpers::PropertyData<QColor>(105, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'inactiveFg'
        QtMocHelpers::PropertyData<QColor>(106, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'inactiveTs'
        QtMocHelpers::PropertyData<QColor>(107, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'inactiveBs'
        QtMocHelpers::PropertyData<QColor>(108, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'darkMode'
        QtMocHelpers::PropertyData<bool>(109, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'activeFiligreePaletteName'
        QtMocHelpers::PropertyData<QString>(110, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'activeFiligreePalette'
        QtMocHelpers::PropertyData<QVariantMap>(111, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'filigreePalettes'
        QtMocHelpers::PropertyData<QVariantMap>(112, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'presetActive'
        QtMocHelpers::PropertyData<bool>(113, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'usingCustomBase'
        QtMocHelpers::PropertyData<bool>(114, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'fontSize_sm'
        QtMocHelpers::PropertyData<int>(115, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'fontSize_md'
        QtMocHelpers::PropertyData<int>(116, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'fontSize_lg'
        QtMocHelpers::PropertyData<int>(117, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'letterSpacing'
        QtMocHelpers::PropertyData<int>(118, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'lineHeight'
        QtMocHelpers::PropertyData<double>(119, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'themeName'
        QtMocHelpers::PropertyData<QString>(120, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'accentName'
        QtMocHelpers::PropertyData<QString>(121, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'darkModeLock'
        QtMocHelpers::PropertyData<QString>(122, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'overrideAccent'
        QtMocHelpers::PropertyData<QString>(123, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'overrideAccentMuted'
        QtMocHelpers::PropertyData<QString>(124, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'overrideBorder'
        QtMocHelpers::PropertyData<QString>(125, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'overrideGlow'
        QtMocHelpers::PropertyData<QString>(126, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'bodyFont'
        QtMocHelpers::PropertyData<QString>(127, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'titleFont'
        QtMocHelpers::PropertyData<QString>(128, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'monoFont'
        QtMocHelpers::PropertyData<QString>(129, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'displayFont'
        QtMocHelpers::PropertyData<QString>(130, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'fellFont'
        QtMocHelpers::PropertyData<QString>(131, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'garFont'
        QtMocHelpers::PropertyData<QString>(132, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'version'
        QtMocHelpers::PropertyData<QString>(133, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NCDEEngine, qt_meta_tag_ZN10NCDEEngineE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NCDEEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10NCDEEngineE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10NCDEEngineE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10NCDEEngineE_t>.metaTypes,
    nullptr
} };

void NCDEEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NCDEEngine *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->themeChanged(); break;
        case 2: _t->darkModeChanged(); break;
        case 3: _t->previewReady((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 4: _t->filigreePalettesChanged(); break;
        case 5: { QVariantList _r = _t->presets();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->applyPreset((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: { QVariantMap _r = _t->currentBasePalette();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->sampleWallpaper((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantMap _r = _t->previewWallpaper((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->previewWallpaperAsync((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->setSurfaceGlass((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[6]))); break;
        case 12: { QVariantMap _r = _t->surfaceGlass((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setWidgetStyleMap((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[2]))); break;
        case 14: _t->setWidgetStyle((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 15: { QVariantMap _r = _t->widgetStyle((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->resetWidgetStyle((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->setOverrideAccent((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->setOverrideAccentMuted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->setOverrideBorder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setOverrideGlow((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->setBodyFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->setTitleFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->setMonoFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 24: _t->setDisplayFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->setFellFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->setGarFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->setUiScale((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 28: _t->setFontSizeScale((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 29: _t->setLetterSpacing((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 30: _t->setLineHeight((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 31: _t->recomputeFontSizes(); break;
        case 32: { QVariantMap _r = _t->toJson();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->saveTheme((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->loadTheme((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->setTerminalFont((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 36: _t->setTerminalGlassTint((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 37: { QVariantMap _r = _t->terminalConfig();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 38: { bool _r = _t->saveFiligreepalette((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 39: { bool _r = _t->deleteFiligreepalette((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 40: { bool _r = _t->setActiveFiligreepalette((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NCDEEngine::*)()>(_a, &NCDEEngine::changed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEEngine::*)()>(_a, &NCDEEngine::themeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEEngine::*)()>(_a, &NCDEEngine::darkModeChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEEngine::*)(const QVariantMap & )>(_a, &NCDEEngine::previewReady, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEEngine::*)()>(_a, &NCDEEngine::filigreePalettesChanged, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QColor*>(_v) = _t->accent(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->accentMuted(); break;
        case 2: *reinterpret_cast<QColor*>(_v) = _t->background(); break;
        case 3: *reinterpret_cast<QColor*>(_v) = _t->surface(); break;
        case 4: *reinterpret_cast<QColor*>(_v) = _t->surfaceAlt(); break;
        case 5: *reinterpret_cast<QColor*>(_v) = _t->surfaceHi(); break;
        case 6: *reinterpret_cast<QColor*>(_v) = _t->panelBg(); break;
        case 7: *reinterpret_cast<QColor*>(_v) = _t->panelText(); break;
        case 8: *reinterpret_cast<QColor*>(_v) = _t->popupBg(); break;
        case 9: *reinterpret_cast<QColor*>(_v) = _t->border(); break;
        case 10: *reinterpret_cast<QColor*>(_v) = _t->glow(); break;
        case 11: *reinterpret_cast<QColor*>(_v) = _t->ink(); break;
        case 12: *reinterpret_cast<QColor*>(_v) = _t->inkSoft(); break;
        case 13: *reinterpret_cast<QColor*>(_v) = _t->verd(); break;
        case 14: *reinterpret_cast<QColor*>(_v) = _t->cer(); break;
        case 15: *reinterpret_cast<QColor*>(_v) = _t->rose(); break;
        case 16: *reinterpret_cast<QColor*>(_v) = _t->amber(); break;
        case 17: *reinterpret_cast<QColor*>(_v) = _t->clockColor(); break;
        case 18: *reinterpret_cast<QColor*>(_v) = _t->lamp(); break;
        case 19: *reinterpret_cast<QColor*>(_v) = _t->gilt0(); break;
        case 20: *reinterpret_cast<QColor*>(_v) = _t->gilt1(); break;
        case 21: *reinterpret_cast<QColor*>(_v) = _t->gilt2(); break;
        case 22: *reinterpret_cast<QColor*>(_v) = _t->gilt3(); break;
        case 23: *reinterpret_cast<QColor*>(_v) = _t->gilt4(); break;
        case 24: *reinterpret_cast<QColor*>(_v) = _t->gilt5(); break;
        case 25: *reinterpret_cast<QColor*>(_v) = _t->wine1(); break;
        case 26: *reinterpret_cast<QColor*>(_v) = _t->wine2(); break;
        case 27: *reinterpret_cast<QColor*>(_v) = _t->wine3(); break;
        case 28: *reinterpret_cast<QColor*>(_v) = _t->wine4(); break;
        case 29: *reinterpret_cast<QColor*>(_v) = _t->widgetC0(); break;
        case 30: *reinterpret_cast<QColor*>(_v) = _t->widgetC1(); break;
        case 31: *reinterpret_cast<QColor*>(_v) = _t->widgetC2(); break;
        case 32: *reinterpret_cast<QColor*>(_v) = _t->widgetC3(); break;
        case 33: *reinterpret_cast<QColor*>(_v) = _t->widgetC4(); break;
        case 34: *reinterpret_cast<QColor*>(_v) = _t->widgetC5(); break;
        case 35: *reinterpret_cast<QColor*>(_v) = _t->foreground(); break;
        case 36: *reinterpret_cast<QColor*>(_v) = _t->topShadow(); break;
        case 37: *reinterpret_cast<QColor*>(_v) = _t->bottomShadow(); break;
        case 38: *reinterpret_cast<QColor*>(_v) = _t->selectColor(); break;
        case 39: *reinterpret_cast<QColor*>(_v) = _t->activeBg(); break;
        case 40: *reinterpret_cast<QColor*>(_v) = _t->activeFg(); break;
        case 41: *reinterpret_cast<QColor*>(_v) = _t->activeTs(); break;
        case 42: *reinterpret_cast<QColor*>(_v) = _t->activeBs(); break;
        case 43: *reinterpret_cast<QColor*>(_v) = _t->inactiveBg(); break;
        case 44: *reinterpret_cast<QColor*>(_v) = _t->inactiveFg(); break;
        case 45: *reinterpret_cast<QColor*>(_v) = _t->inactiveTs(); break;
        case 46: *reinterpret_cast<QColor*>(_v) = _t->inactiveBs(); break;
        case 47: *reinterpret_cast<bool*>(_v) = _t->darkMode(); break;
        case 48: *reinterpret_cast<QString*>(_v) = _t->activeFiligreePaletteName(); break;
        case 49: *reinterpret_cast<QVariantMap*>(_v) = _t->activeFiligreePalette(); break;
        case 50: *reinterpret_cast<QVariantMap*>(_v) = _t->filigreePalettes(); break;
        case 51: *reinterpret_cast<bool*>(_v) = _t->presetActive(); break;
        case 52: *reinterpret_cast<bool*>(_v) = _t->usingCustomBase(); break;
        case 53: *reinterpret_cast<int*>(_v) = _t->fontSize_sm(); break;
        case 54: *reinterpret_cast<int*>(_v) = _t->fontSize_md(); break;
        case 55: *reinterpret_cast<int*>(_v) = _t->fontSize_lg(); break;
        case 56: *reinterpret_cast<int*>(_v) = _t->letterSpacing(); break;
        case 57: *reinterpret_cast<double*>(_v) = _t->lineHeight(); break;
        case 58: *reinterpret_cast<QString*>(_v) = _t->themeName(); break;
        case 59: *reinterpret_cast<QString*>(_v) = _t->accentName(); break;
        case 60: *reinterpret_cast<QString*>(_v) = _t->darkModeLock(); break;
        case 61: *reinterpret_cast<QString*>(_v) = _t->overrideAccent(); break;
        case 62: *reinterpret_cast<QString*>(_v) = _t->overrideAccentMuted(); break;
        case 63: *reinterpret_cast<QString*>(_v) = _t->overrideBorder(); break;
        case 64: *reinterpret_cast<QString*>(_v) = _t->overrideGlow(); break;
        case 65: *reinterpret_cast<QString*>(_v) = _t->bodyFont(); break;
        case 66: *reinterpret_cast<QString*>(_v) = _t->titleFont(); break;
        case 67: *reinterpret_cast<QString*>(_v) = _t->monoFont(); break;
        case 68: *reinterpret_cast<QString*>(_v) = _t->displayFont(); break;
        case 69: *reinterpret_cast<QString*>(_v) = _t->fellFont(); break;
        case 70: *reinterpret_cast<QString*>(_v) = _t->garFont(); break;
        case 71: *reinterpret_cast<QString*>(_v) = _t->version(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 47: _t->setDarkMode(*reinterpret_cast<bool*>(_v)); break;
        case 59: _t->setAccentName(*reinterpret_cast<QString*>(_v)); break;
        case 60: _t->setDarkModeLock(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *NCDEEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NCDEEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10NCDEEngineE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NCDEEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 41;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 72;
    }
    return _id;
}

// SIGNAL 0
void NCDEEngine::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NCDEEngine::themeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NCDEEngine::darkModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NCDEEngine::previewReady(const QVariantMap & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void NCDEEngine::filigreePalettesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
