/****************************************************************************
** Meta object code from reading C++ file 'CalendarBackend.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CalendarBackend.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CalendarBackend.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15CalendarBackendE_t {};
} // unnamed namespace

template <> constexpr inline auto CalendarBackend::qt_create_metaobjectdata<qt_meta_tag_ZN15CalendarBackendE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CalendarBackend",
        "changed",
        "",
        "settingsChanged",
        "upsertAppointment",
        "QVariantMap",
        "rec",
        "deleteAppointment",
        "id",
        "upsertTodo",
        "toggleTodo",
        "deleteTodo",
        "saveSettings",
        "s",
        "undo",
        "canUndo",
        "exportICS",
        "exportICSToFile",
        "path",
        "importICS",
        "text",
        "importICSFromFile",
        "fireReminder",
        "title",
        "body",
        "composeForHummingbird",
        "apptId",
        "composeForHummingbirdRec",
        "appt",
        "reload",
        "configFilePath",
        "dueReminders",
        "QVariantList",
        "horizonDays",
        "canDeliver",
        "method",
        "lastDeliveryError",
        "appointments",
        "todos",
        "settings"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changed'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'settingsChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'upsertAppointment'
        QtMocHelpers::MethodData<QString(const QVariantMap &)>(4, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Method 'deleteAppointment'
        QtMocHelpers::MethodData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'upsertTodo'
        QtMocHelpers::MethodData<QString(const QVariantMap &)>(9, 2, QMC::AccessPublic, QMetaType::QString, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Method 'toggleTodo'
        QtMocHelpers::MethodData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'deleteTodo'
        QtMocHelpers::MethodData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'saveSettings'
        QtMocHelpers::MethodData<void(const QVariantMap &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 13 },
        }}),
        // Method 'undo'
        QtMocHelpers::MethodData<QString()>(14, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'canUndo'
        QtMocHelpers::MethodData<bool() const>(15, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'exportICS'
        QtMocHelpers::MethodData<QString() const>(16, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'exportICSToFile'
        QtMocHelpers::MethodData<bool(const QString &) const>(17, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'importICS'
        QtMocHelpers::MethodData<int(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 20 },
        }}),
        // Method 'importICSFromFile'
        QtMocHelpers::MethodData<int(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'fireReminder'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 }, { QMetaType::QString, 24 },
        }}),
        // Method 'composeForHummingbird'
        QtMocHelpers::MethodData<bool(const QString &)>(25, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 26 },
        }}),
        // Method 'composeForHummingbirdRec'
        QtMocHelpers::MethodData<bool(const QVariantMap &)>(27, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 5, 28 },
        }}),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'configFilePath'
        QtMocHelpers::MethodData<QString() const>(30, 2, QMC::AccessPublic, QMetaType::QString),
        // Method 'dueReminders'
        QtMocHelpers::MethodData<QVariantList(int) const>(31, 2, QMC::AccessPublic, 0x80000000 | 32, {{
            { QMetaType::Int, 33 },
        }}),
        // Method 'dueReminders'
        QtMocHelpers::MethodData<QVariantList() const>(31, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 32),
        // Method 'canDeliver'
        QtMocHelpers::MethodData<bool(const QString &) const>(34, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 35 },
        }}),
        // Method 'lastDeliveryError'
        QtMocHelpers::MethodData<QString() const>(36, 2, QMC::AccessPublic, QMetaType::QString),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'appointments'
        QtMocHelpers::PropertyData<QVariantList>(37, 0x80000000 | 32, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'todos'
        QtMocHelpers::PropertyData<QVariantList>(38, 0x80000000 | 32, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'settings'
        QtMocHelpers::PropertyData<QVariantMap>(39, 0x80000000 | 5, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CalendarBackend, qt_meta_tag_ZN15CalendarBackendE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CalendarBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CalendarBackendE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CalendarBackendE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15CalendarBackendE_t>.metaTypes,
    nullptr
} };

void CalendarBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CalendarBackend *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->settingsChanged(); break;
        case 2: { QString _r = _t->upsertAppointment((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->deleteAppointment((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: { QString _r = _t->upsertTodo((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->toggleTodo((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->deleteTodo((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->saveSettings((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 8: { QString _r = _t->undo();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->canUndo();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->exportICS();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->exportICSToFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->importICS((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 13: { int _r = _t->importICSFromFile((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->fireReminder((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: { bool _r = _t->composeForHummingbird((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->composeForHummingbirdRec((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->reload(); break;
        case 18: { QString _r = _t->configFilePath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantList _r = _t->dueReminders((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->dueReminders();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->canDeliver((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->lastDeliveryError();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CalendarBackend::*)()>(_a, &CalendarBackend::changed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CalendarBackend::*)()>(_a, &CalendarBackend::settingsChanged, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->appointments(); break;
        case 1: *reinterpret_cast<QVariantList*>(_v) = _t->todos(); break;
        case 2: *reinterpret_cast<QVariantMap*>(_v) = _t->settings(); break;
        default: break;
        }
    }
}

const QMetaObject *CalendarBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalendarBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15CalendarBackendE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CalendarBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
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
void CalendarBackend::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CalendarBackend::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
