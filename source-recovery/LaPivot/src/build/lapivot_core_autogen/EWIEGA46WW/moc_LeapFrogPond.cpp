/****************************************************************************
** Meta object code from reading C++ file 'LeapFrogPond.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../LeapFrogPond.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LeapFrogPond.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12LeapFrogPondE_t {};
} // unnamed namespace

template <> constexpr inline auto LeapFrogPond::qt_create_metaobjectdata<qt_meta_tag_ZN12LeapFrogPondE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LeapFrogPond",
        "notesChanged",
        "",
        "noticeChanged",
        "archived",
        "count",
        "exported",
        "path",
        "reconciled",
        "addNote",
        "text",
        "removeNote",
        "id",
        "removeAppt",
        "setNotice",
        "t",
        "tally",
        "QVariantMap",
        "reconcile",
        "archivePast",
        "exportCsv",
        "exportLilyPad",
        "reload",
        "configFilePath",
        "notes",
        "QVariantList",
        "noteCount",
        "notice",
        "appts"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'notesChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'noticeChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'archived'
        QtMocHelpers::SignalData<void(int)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Signal 'exported'
        QtMocHelpers::SignalData<void(QString)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'reconciled'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'addNote'
        QtMocHelpers::MethodData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'removeNote'
        QtMocHelpers::MethodData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Method 'removeAppt'
        QtMocHelpers::MethodData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Method 'setNotice'
        QtMocHelpers::MethodData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Method 'tally'
        QtMocHelpers::MethodData<QVariantMap()>(16, 2, QMC::AccessPublic, 0x80000000 | 17),
        // Method 'reconcile'
        QtMocHelpers::MethodData<int()>(18, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'archivePast'
        QtMocHelpers::MethodData<int()>(19, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'exportCsv'
        QtMocHelpers::MethodData<QString(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'exportCsv'
        QtMocHelpers::MethodData<QString()>(20, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString),
        // Method 'exportLilyPad'
        QtMocHelpers::MethodData<QString(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'exportLilyPad'
        QtMocHelpers::MethodData<QString()>(21, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'configFilePath'
        QtMocHelpers::MethodData<QString() const>(23, 2, QMC::AccessPublic, QMetaType::QString),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'notes'
        QtMocHelpers::PropertyData<QVariantList>(24, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'noteCount'
        QtMocHelpers::PropertyData<int>(26, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'notice'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'appts'
        QtMocHelpers::PropertyData<QVariantList>(28, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LeapFrogPond, qt_meta_tag_ZN12LeapFrogPondE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LeapFrogPond::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12LeapFrogPondE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12LeapFrogPondE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12LeapFrogPondE_t>.metaTypes,
    nullptr
} };

void LeapFrogPond::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LeapFrogPond *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->notesChanged(); break;
        case 1: _t->noticeChanged(); break;
        case 2: _t->archived((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->exported((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->reconciled((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->addNote((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->removeNote((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->removeAppt((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->setNotice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: { QVariantMap _r = _t->tally();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->reconcile();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->archivePast();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->exportCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->exportCsv();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->exportLilyPad((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { QString _r = _t->exportLilyPad();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->reload(); break;
        case 17: { QString _r = _t->configFilePath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LeapFrogPond::*)()>(_a, &LeapFrogPond::notesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LeapFrogPond::*)()>(_a, &LeapFrogPond::noticeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LeapFrogPond::*)(int )>(_a, &LeapFrogPond::archived, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LeapFrogPond::*)(QString )>(_a, &LeapFrogPond::exported, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LeapFrogPond::*)(int )>(_a, &LeapFrogPond::reconciled, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->notes(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->noteCount(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->notice(); break;
        case 3: *reinterpret_cast<QVariantList*>(_v) = _t->appts(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setNotice(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *LeapFrogPond::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LeapFrogPond::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12LeapFrogPondE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LeapFrogPond::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 18;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LeapFrogPond::notesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LeapFrogPond::noticeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LeapFrogPond::archived(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void LeapFrogPond::exported(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void LeapFrogPond::reconciled(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
