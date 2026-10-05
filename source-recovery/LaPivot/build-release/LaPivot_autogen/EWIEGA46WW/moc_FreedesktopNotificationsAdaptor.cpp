/****************************************************************************
** Meta object code from reading C++ file 'FreedesktopNotificationsAdaptor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FreedesktopNotificationsAdaptor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FreedesktopNotificationsAdaptor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t {};
} // unnamed namespace

template <> constexpr inline auto FreedesktopNotificationsAdaptor::qt_create_metaobjectdata<qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FreedesktopNotificationsAdaptor",
        "D-Bus Interface",
        "org.freedesktop.Notifications",
        "NotificationClosed",
        "",
        "id",
        "reason",
        "ActionInvoked",
        "actionKey",
        "Notify",
        "appName",
        "replacesId",
        "appIcon",
        "summary",
        "body",
        "actions",
        "QVariantMap",
        "hints",
        "timeout",
        "CloseNotification",
        "GetCapabilities",
        "GetServerInformation",
        "QString&",
        "name",
        "vendor",
        "version",
        "specVersion"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'NotificationClosed'
        QtMocHelpers::SignalData<void(uint, uint)>(3, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 5 }, { QMetaType::UInt, 6 },
        }}),
        // Signal 'ActionInvoked'
        QtMocHelpers::SignalData<void(uint, const QString &)>(7, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 5 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'Notify'
        QtMocHelpers::SlotData<uint(const QString &, uint, const QString &, const QString &, const QString &, const QStringList &, const QVariantMap &, int)>(9, 4, QMC::AccessPublic, QMetaType::UInt, {{
            { QMetaType::QString, 10 }, { QMetaType::UInt, 11 }, { QMetaType::QString, 12 }, { QMetaType::QString, 13 },
            { QMetaType::QString, 14 }, { QMetaType::QStringList, 15 }, { 0x80000000 | 16, 17 }, { QMetaType::Int, 18 },
        }}),
        // Slot 'CloseNotification'
        QtMocHelpers::SlotData<void(uint)>(19, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 5 },
        }}),
        // Slot 'GetCapabilities'
        QtMocHelpers::SlotData<QStringList()>(20, 4, QMC::AccessPublic, QMetaType::QStringList),
        // Slot 'GetServerInformation'
        QtMocHelpers::SlotData<void(QString &, QString &, QString &, QString &)>(21, 4, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 22, 23 }, { 0x80000000 | 22, 24 }, { 0x80000000 | 22, 25 }, { 0x80000000 | 22, 26 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FreedesktopNotificationsAdaptor, qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FreedesktopNotificationsAdaptor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>.metaTypes,
    nullptr
} };

void FreedesktopNotificationsAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FreedesktopNotificationsAdaptor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->NotificationClosed((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[2]))); break;
        case 1: _t->ActionInvoked((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: { uint _r = _t->Notify((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[8])));
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->CloseNotification((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 4: { QStringList _r = _t->GetCapabilities();
            if (_a[0]) *reinterpret_cast<QStringList*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->GetServerInformation((*reinterpret_cast<std::add_pointer_t<QString&>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString&>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString&>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString&>>(_a[4]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FreedesktopNotificationsAdaptor::*)(uint , uint )>(_a, &FreedesktopNotificationsAdaptor::NotificationClosed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FreedesktopNotificationsAdaptor::*)(uint , const QString & )>(_a, &FreedesktopNotificationsAdaptor::ActionInvoked, 1))
            return;
    }
}

const QMetaObject *FreedesktopNotificationsAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FreedesktopNotificationsAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31FreedesktopNotificationsAdaptorE_t>.strings))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int FreedesktopNotificationsAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FreedesktopNotificationsAdaptor::NotificationClosed(uint _t1, uint _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void FreedesktopNotificationsAdaptor::ActionInvoked(uint _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
