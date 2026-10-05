/****************************************************************************
** Meta object code from reading C++ file 'IdleInhibitService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../IdleInhibitService.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IdleInhibitService.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18IdleInhibitServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto IdleInhibitService::qt_create_metaobjectdata<qt_meta_tag_ZN18IdleInhibitServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IdleInhibitService",
        "D-Bus Interface",
        "org.freedesktop.ScreenSaver",
        "Inhibit",
        "",
        "application_name",
        "reason_for_inhibit",
        "UnInhibit",
        "cookie",
        "dropOwner",
        "serviceName",
        "resetIdle"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'Inhibit'
        QtMocHelpers::SlotData<uint(const QString &, const QString &)>(3, 4, QMC::AccessPublic, QMetaType::UInt, {{
            { QMetaType::QString, 5 }, { QMetaType::QString, 6 },
        }}),
        // Slot 'UnInhibit'
        QtMocHelpers::SlotData<void(uint)>(7, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 8 },
        }}),
        // Slot 'dropOwner'
        QtMocHelpers::SlotData<void(const QString &)>(9, 4, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Slot 'resetIdle'
        QtMocHelpers::SlotData<void()>(11, 4, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<IdleInhibitService, qt_meta_tag_ZN18IdleInhibitServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject IdleInhibitService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IdleInhibitServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IdleInhibitServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18IdleInhibitServiceE_t>.metaTypes,
    nullptr
} };

void IdleInhibitService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IdleInhibitService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { uint _r = _t->Inhibit((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->UnInhibit((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 2: _t->dropOwner((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->resetIdle(); break;
        default: ;
        }
    }
}

const QMetaObject *IdleInhibitService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IdleInhibitService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IdleInhibitServiceE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QDBusContext"))
        return static_cast< QDBusContext*>(this);
    return QObject::qt_metacast(_clname);
}

int IdleInhibitService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
