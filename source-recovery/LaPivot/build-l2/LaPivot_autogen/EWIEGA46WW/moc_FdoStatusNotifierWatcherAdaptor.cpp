/****************************************************************************
** Meta object code from reading C++ file 'FdoStatusNotifierWatcherAdaptor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FdoStatusNotifierWatcherAdaptor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FdoStatusNotifierWatcherAdaptor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t {};
} // unnamed namespace

template <> constexpr inline auto FdoStatusNotifierWatcherAdaptor::qt_create_metaobjectdata<qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FdoStatusNotifierWatcherAdaptor",
        "D-Bus Interface",
        "org.freedesktop.StatusNotifierWatcher",
        "StatusNotifierItemRegistered",
        "",
        "service",
        "StatusNotifierItemUnregistered",
        "StatusNotifierHostRegistered",
        "RegisterStatusNotifierItem",
        "RegisterStatusNotifierHost",
        "RegisteredStatusNotifierItems",
        "IsStatusNotifierHostRegistered",
        "ProtocolVersion"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'StatusNotifierItemRegistered'
        QtMocHelpers::SignalData<void(const QString &)>(3, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'StatusNotifierItemUnregistered'
        QtMocHelpers::SignalData<void(const QString &)>(6, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'StatusNotifierHostRegistered'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Slot 'RegisterStatusNotifierItem'
        QtMocHelpers::SlotData<void(const QString &)>(8, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'RegisterStatusNotifierHost'
        QtMocHelpers::SlotData<void(const QString &)>(9, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'RegisteredStatusNotifierItems'
        QtMocHelpers::PropertyData<QStringList>(10, QMetaType::QStringList, QMC::DefaultPropertyFlags),
        // property 'IsStatusNotifierHostRegistered'
        QtMocHelpers::PropertyData<bool>(11, QMetaType::Bool, QMC::DefaultPropertyFlags),
        // property 'ProtocolVersion'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FdoStatusNotifierWatcherAdaptor, qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FdoStatusNotifierWatcherAdaptor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>.metaTypes,
    nullptr
} };

void FdoStatusNotifierWatcherAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FdoStatusNotifierWatcherAdaptor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->StatusNotifierItemRegistered((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->StatusNotifierItemUnregistered((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->StatusNotifierHostRegistered(); break;
        case 3: _t->RegisterStatusNotifierItem((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->RegisterStatusNotifierHost((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FdoStatusNotifierWatcherAdaptor::*)(const QString & )>(_a, &FdoStatusNotifierWatcherAdaptor::StatusNotifierItemRegistered, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FdoStatusNotifierWatcherAdaptor::*)(const QString & )>(_a, &FdoStatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FdoStatusNotifierWatcherAdaptor::*)()>(_a, &FdoStatusNotifierWatcherAdaptor::StatusNotifierHostRegistered, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->RegisteredStatusNotifierItems(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->IsStatusNotifierHostRegistered(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->ProtocolVersion(); break;
        default: break;
        }
    }
}

const QMetaObject *FdoStatusNotifierWatcherAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FdoStatusNotifierWatcherAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FdoStatusNotifierWatcherAdaptorE_t>.strings))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int FdoStatusNotifierWatcherAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FdoStatusNotifierWatcherAdaptor::StatusNotifierItemRegistered(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void FdoStatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void FdoStatusNotifierWatcherAdaptor::StatusNotifierHostRegistered()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
