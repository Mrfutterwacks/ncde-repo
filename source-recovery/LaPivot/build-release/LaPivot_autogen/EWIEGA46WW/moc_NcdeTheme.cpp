/****************************************************************************
** Meta object code from reading C++ file 'NcdeTheme.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/NcdeTheme.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NcdeTheme.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9NcdeThemeE_t {};
} // unnamed namespace

template <> constexpr inline auto NcdeTheme::qt_create_metaobjectdata<qt_meta_tag_ZN9NcdeThemeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NcdeTheme",
        "changed",
        "",
        "applyPalette",
        "QVariantMap",
        "p",
        "setDarkMode",
        "dark",
        "setAccentName",
        "name",
        "setDarkModeLock",
        "lock",
        "setBaseColor",
        "QColor",
        "base",
        "accent",
        "panelText",
        "clearCustomBase",
        "accentMuted",
        "border",
        "darkMode",
        "fontSize",
        "foreground",
        "gilt",
        "glow",
        "panelBg",
        "popupBg",
        "presetActive",
        "surface",
        "surfaceAlt",
        "surfaceGlass",
        "verd",
        "version",
        "widgetStyle",
        "wine",
        "KickassGuard",
        "letterSpacing"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'applyPalette'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'setDarkMode'
        QtMocHelpers::SlotData<void(bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'setAccentName'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'setDarkModeLock'
        QtMocHelpers::SlotData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Slot 'setBaseColor'
        QtMocHelpers::SlotData<void(const QColor &, const QColor &, const QColor &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 }, { 0x80000000 | 13, 15 }, { 0x80000000 | 13, 16 },
        }}),
        // Slot 'clearCustomBase'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'accent'
        QtMocHelpers::PropertyData<QColor>(15, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'accentMuted'
        QtMocHelpers::PropertyData<QColor>(18, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'border'
        QtMocHelpers::PropertyData<QColor>(19, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'darkMode'
        QtMocHelpers::PropertyData<bool>(20, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'fontSize'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'foreground'
        QtMocHelpers::PropertyData<QColor>(22, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'gilt'
        QtMocHelpers::PropertyData<QColor>(23, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'glow'
        QtMocHelpers::PropertyData<QColor>(24, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'panelBg'
        QtMocHelpers::PropertyData<QColor>(25, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'popupBg'
        QtMocHelpers::PropertyData<QColor>(26, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'presetActive'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'surface'
        QtMocHelpers::PropertyData<QColor>(28, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'surfaceAlt'
        QtMocHelpers::PropertyData<QColor>(29, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'surfaceGlass'
        QtMocHelpers::PropertyData<QColor>(30, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'verd'
        QtMocHelpers::PropertyData<QColor>(31, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'version'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'widgetStyle'
        QtMocHelpers::PropertyData<QString>(33, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'wine'
        QtMocHelpers::PropertyData<QColor>(34, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'KickassGuard'
        QtMocHelpers::PropertyData<QObject*>(35, QMetaType::QObjectStar, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'letterSpacing'
        QtMocHelpers::PropertyData<int>(36, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NcdeTheme, qt_meta_tag_ZN9NcdeThemeE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NcdeTheme::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9NcdeThemeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9NcdeThemeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9NcdeThemeE_t>.metaTypes,
    nullptr
} };

void NcdeTheme::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NcdeTheme *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->applyPalette((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 2: _t->setDarkMode((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->setAccentName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->setDarkModeLock((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->setBaseColor((*reinterpret_cast<std::add_pointer_t<QColor>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[3]))); break;
        case 6: _t->clearCustomBase(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NcdeTheme::*)()>(_a, &NcdeTheme::changed, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QColor*>(_v) = _t->accent(); break;
        case 1: *reinterpret_cast<QColor*>(_v) = _t->accentMuted(); break;
        case 2: *reinterpret_cast<QColor*>(_v) = _t->border(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->darkMode(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->fontSize(); break;
        case 5: *reinterpret_cast<QColor*>(_v) = _t->foreground(); break;
        case 6: *reinterpret_cast<QColor*>(_v) = _t->gilt(); break;
        case 7: *reinterpret_cast<QColor*>(_v) = _t->glow(); break;
        case 8: *reinterpret_cast<QColor*>(_v) = _t->panelBg(); break;
        case 9: *reinterpret_cast<QColor*>(_v) = _t->popupBg(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->presetActive(); break;
        case 11: *reinterpret_cast<QColor*>(_v) = _t->surface(); break;
        case 12: *reinterpret_cast<QColor*>(_v) = _t->surfaceAlt(); break;
        case 13: *reinterpret_cast<QColor*>(_v) = _t->surfaceGlass(); break;
        case 14: *reinterpret_cast<QColor*>(_v) = _t->verd(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->version(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->widgetStyle(); break;
        case 17: *reinterpret_cast<QColor*>(_v) = _t->wine(); break;
        case 18: *reinterpret_cast<QObject**>(_v) = _t->KickassGuard(); break;
        case 19: *reinterpret_cast<int*>(_v) = _t->letterSpacing(); break;
        default: break;
        }
    }
}

const QMetaObject *NcdeTheme::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NcdeTheme::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9NcdeThemeE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NcdeTheme::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void NcdeTheme::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
