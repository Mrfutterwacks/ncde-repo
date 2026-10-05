/****************************************************************************
** Meta object code from reading C++ file 'WidgetData.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WidgetData.h"
#include "Settings.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetData.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10WidgetDataE_t {};
} // unnamed namespace

template <> constexpr inline auto WidgetData::qt_create_metaobjectdata<qt_meta_tag_ZN10WidgetDataE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WidgetData",
        "changed",
        "",
        "clockChanged",
        "statsChanged",
        "weatherChanged",
        "moonPositionChanged",
        "mediaChanged",
        "mediaPositionChanged",
        "refreshWeather",
        "setVolume",
        "v",
        "toggleMute",
        "mediaTogglePlay",
        "mediaNext",
        "mediaPrev",
        "mediaSeek",
        "p",
        "mountVolume",
        "unmountVolume",
        "setSettings",
        "Settings*",
        "settings",
        "removableVolumes",
        "QVariantList",
        "volume",
        "muted",
        "hasBattery",
        "batteryLevel",
        "batteryCharging",
        "networkUp",
        "netOnline",
        "netUp",
        "netDown",
        "mediaActive",
        "mediaPlaying",
        "mediaTitle",
        "mediaArtist",
        "mediaAlbum",
        "mediaPosition",
        "mediaDuration",
        "timeHour",
        "timeMinute",
        "timeSecond",
        "timeAMPM",
        "colonOn",
        "greeting",
        "dateString",
        "cpuTotal",
        "ramPercent",
        "diskPercent",
        "cpuFreqGHz",
        "cpuTempF",
        "uptime",
        "mountedVolumes",
        "weatherTemp",
        "weatherIcon",
        "weatherLocation",
        "weatherHigh",
        "weatherLow",
        "weatherHumidity",
        "weatherWind",
        "weatherSunrise",
        "weatherSunset",
        "moonAzimuth",
        "moonElevation"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'clockChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'weatherChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'moonPositionChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mediaChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mediaPositionChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'refreshWeather'
        QtMocHelpers::MethodData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setVolume'
        QtMocHelpers::MethodData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 },
        }}),
        // Method 'toggleMute'
        QtMocHelpers::MethodData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'mediaTogglePlay'
        QtMocHelpers::MethodData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'mediaNext'
        QtMocHelpers::MethodData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'mediaPrev'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'mediaSeek'
        QtMocHelpers::MethodData<void(double)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 17 },
        }}),
        // Method 'mountVolume'
        QtMocHelpers::MethodData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Method 'unmountVolume'
        QtMocHelpers::MethodData<void(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Method 'setSettings'
        QtMocHelpers::MethodData<void(Settings *)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'removableVolumes'
        QtMocHelpers::PropertyData<QVariantList>(23, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'volume'
        QtMocHelpers::PropertyData<int>(25, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'muted'
        QtMocHelpers::PropertyData<bool>(26, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'hasBattery'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'batteryLevel'
        QtMocHelpers::PropertyData<int>(28, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'batteryCharging'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'networkUp'
        QtMocHelpers::PropertyData<bool>(30, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'netOnline'
        QtMocHelpers::PropertyData<bool>(31, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'netUp'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'netDown'
        QtMocHelpers::PropertyData<QString>(33, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'mediaActive'
        QtMocHelpers::PropertyData<bool>(34, QMetaType::Bool, QMC::DefaultPropertyFlags, 5),
        // property 'mediaPlaying'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags, 5),
        // property 'mediaTitle'
        QtMocHelpers::PropertyData<QString>(36, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'mediaArtist'
        QtMocHelpers::PropertyData<QString>(37, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'mediaAlbum'
        QtMocHelpers::PropertyData<QString>(38, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'mediaPosition'
        QtMocHelpers::PropertyData<double>(39, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'mediaDuration'
        QtMocHelpers::PropertyData<double>(40, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'timeHour'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'timeMinute'
        QtMocHelpers::PropertyData<QString>(42, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'timeSecond'
        QtMocHelpers::PropertyData<QString>(43, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'timeAMPM'
        QtMocHelpers::PropertyData<QString>(44, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'colonOn'
        QtMocHelpers::PropertyData<bool>(45, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'greeting'
        QtMocHelpers::PropertyData<QString>(46, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'dateString'
        QtMocHelpers::PropertyData<QString>(47, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'cpuTotal'
        QtMocHelpers::PropertyData<double>(48, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'ramPercent'
        QtMocHelpers::PropertyData<double>(49, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'diskPercent'
        QtMocHelpers::PropertyData<double>(50, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'cpuFreqGHz'
        QtMocHelpers::PropertyData<double>(51, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'cpuTempF'
        QtMocHelpers::PropertyData<double>(52, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'uptime'
        QtMocHelpers::PropertyData<QString>(53, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'mountedVolumes'
        QtMocHelpers::PropertyData<QVariantList>(54, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
        // property 'weatherTemp'
        QtMocHelpers::PropertyData<QString>(55, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherIcon'
        QtMocHelpers::PropertyData<QString>(56, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherLocation'
        QtMocHelpers::PropertyData<QString>(57, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherHigh'
        QtMocHelpers::PropertyData<QString>(58, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherLow'
        QtMocHelpers::PropertyData<QString>(59, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherHumidity'
        QtMocHelpers::PropertyData<QString>(60, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherWind'
        QtMocHelpers::PropertyData<QString>(61, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherSunrise'
        QtMocHelpers::PropertyData<QString>(62, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'weatherSunset'
        QtMocHelpers::PropertyData<QString>(63, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'moonAzimuth'
        QtMocHelpers::PropertyData<double>(64, QMetaType::Double, QMC::DefaultPropertyFlags, 4),
        // property 'moonElevation'
        QtMocHelpers::PropertyData<double>(65, QMetaType::Double, QMC::DefaultPropertyFlags, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WidgetData, qt_meta_tag_ZN10WidgetDataE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WidgetData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10WidgetDataE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10WidgetDataE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10WidgetDataE_t>.metaTypes,
    nullptr
} };

void WidgetData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WidgetData *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->clockChanged(); break;
        case 2: _t->statsChanged(); break;
        case 3: _t->weatherChanged(); break;
        case 4: _t->moonPositionChanged(); break;
        case 5: _t->mediaChanged(); break;
        case 6: _t->mediaPositionChanged(); break;
        case 7: _t->refreshWeather(); break;
        case 8: _t->setVolume((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->toggleMute(); break;
        case 10: _t->mediaTogglePlay(); break;
        case 11: _t->mediaNext(); break;
        case 12: _t->mediaPrev(); break;
        case 13: _t->mediaSeek((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 14: _t->mountVolume((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->unmountVolume((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->setSettings((*reinterpret_cast<std::add_pointer_t<Settings*>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::changed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::clockChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::statsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::weatherChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::moonPositionChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::mediaChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (WidgetData::*)()>(_a, &WidgetData::mediaPositionChanged, 6))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->removableVolumes(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->volume(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->muted(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->hasBattery(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->batteryLevel(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->batteryCharging(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->networkUp(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->netOnline(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->netUp(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->netDown(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->mediaActive(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->mediaPlaying(); break;
        case 12: *reinterpret_cast<QString*>(_v) = _t->mediaTitle(); break;
        case 13: *reinterpret_cast<QString*>(_v) = _t->mediaArtist(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->mediaAlbum(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->mediaPosition(); break;
        case 16: *reinterpret_cast<double*>(_v) = _t->mediaDuration(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->timeHour(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->timeMinute(); break;
        case 19: *reinterpret_cast<QString*>(_v) = _t->timeSecond(); break;
        case 20: *reinterpret_cast<QString*>(_v) = _t->timeAMPM(); break;
        case 21: *reinterpret_cast<bool*>(_v) = _t->colonOn(); break;
        case 22: *reinterpret_cast<QString*>(_v) = _t->greeting(); break;
        case 23: *reinterpret_cast<QString*>(_v) = _t->dateString(); break;
        case 24: *reinterpret_cast<double*>(_v) = _t->cpuTotal(); break;
        case 25: *reinterpret_cast<double*>(_v) = _t->ramPercent(); break;
        case 26: *reinterpret_cast<double*>(_v) = _t->diskPercent(); break;
        case 27: *reinterpret_cast<double*>(_v) = _t->cpuFreqGHz(); break;
        case 28: *reinterpret_cast<double*>(_v) = _t->cpuTempF(); break;
        case 29: *reinterpret_cast<QString*>(_v) = _t->uptime(); break;
        case 30: *reinterpret_cast<QVariantList*>(_v) = _t->mountedVolumes(); break;
        case 31: *reinterpret_cast<QString*>(_v) = _t->weatherTemp(); break;
        case 32: *reinterpret_cast<QString*>(_v) = _t->weatherIcon(); break;
        case 33: *reinterpret_cast<QString*>(_v) = _t->weatherLocation(); break;
        case 34: *reinterpret_cast<QString*>(_v) = _t->weatherHigh(); break;
        case 35: *reinterpret_cast<QString*>(_v) = _t->weatherLow(); break;
        case 36: *reinterpret_cast<QString*>(_v) = _t->weatherHumidity(); break;
        case 37: *reinterpret_cast<QString*>(_v) = _t->weatherWind(); break;
        case 38: *reinterpret_cast<QString*>(_v) = _t->weatherSunrise(); break;
        case 39: *reinterpret_cast<QString*>(_v) = _t->weatherSunset(); break;
        case 40: *reinterpret_cast<double*>(_v) = _t->moonAzimuth(); break;
        case 41: *reinterpret_cast<double*>(_v) = _t->moonElevation(); break;
        default: break;
        }
    }
}

const QMetaObject *WidgetData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidgetData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10WidgetDataE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WidgetData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    return _id;
}

// SIGNAL 0
void WidgetData::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WidgetData::clockChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WidgetData::statsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WidgetData::weatherChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WidgetData::moonPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WidgetData::mediaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void WidgetData::mediaPositionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
