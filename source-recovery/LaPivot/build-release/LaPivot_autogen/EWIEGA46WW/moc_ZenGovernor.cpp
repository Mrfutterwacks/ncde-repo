/****************************************************************************
** Meta object code from reading C++ file 'ZenGovernor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ZenGovernor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZenGovernor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11ZenGovernorE_t {};
} // unnamed namespace

template <> constexpr inline auto ZenGovernor::qt_create_metaobjectdata<qt_meta_tag_ZN11ZenGovernorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ZenGovernor",
        "pressureChanged",
        "",
        "pressure",
        "thermalCapNeeded",
        "on",
        "cpuPeggedChanged",
        "memoryPressureChanged",
        "onPressureSensed",
        "maxTempC",
        "cpuSaturated",
        "setThermalTrip",
        "tripC",
        "onLowMemoryWarning",
        "level",
        "onSentinelThermalCritical"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'pressureChanged'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'thermalCapNeeded'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Signal 'cpuPeggedChanged'
        QtMocHelpers::SignalData<void(bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Signal 'memoryPressureChanged'
        QtMocHelpers::SignalData<void(bool)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'onPressureSensed'
        QtMocHelpers::SlotData<void(double, bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 9 }, { QMetaType::Bool, 10 },
        }}),
        // Slot 'setThermalTrip'
        QtMocHelpers::SlotData<void(double)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 12 },
        }}),
        // Slot 'onLowMemoryWarning'
        QtMocHelpers::SlotData<void(uchar)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 14 },
        }}),
        // Slot 'onSentinelThermalCritical'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ZenGovernor, qt_meta_tag_ZN11ZenGovernorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ZenGovernor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ZenGovernorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ZenGovernorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ZenGovernorE_t>.metaTypes,
    nullptr
} };

void ZenGovernor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ZenGovernor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->pressureChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->thermalCapNeeded((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->cpuPeggedChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->memoryPressureChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->onPressureSensed((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 5: _t->setThermalTrip((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 6: _t->onLowMemoryWarning((*reinterpret_cast<std::add_pointer_t<uchar>>(_a[1]))); break;
        case 7: _t->onSentinelThermalCritical(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ZenGovernor::*)(int )>(_a, &ZenGovernor::pressureChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZenGovernor::*)(bool )>(_a, &ZenGovernor::thermalCapNeeded, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZenGovernor::*)(bool )>(_a, &ZenGovernor::cpuPeggedChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZenGovernor::*)(bool )>(_a, &ZenGovernor::memoryPressureChanged, 3))
            return;
    }
}

const QMetaObject *ZenGovernor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZenGovernor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ZenGovernorE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ZenGovernor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ZenGovernor::pressureChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ZenGovernor::thermalCapNeeded(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ZenGovernor::cpuPeggedChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ZenGovernor::memoryPressureChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
