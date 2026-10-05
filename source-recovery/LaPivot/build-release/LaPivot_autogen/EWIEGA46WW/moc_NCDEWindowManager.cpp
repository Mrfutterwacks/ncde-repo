/****************************************************************************
** Meta object code from reading C++ file 'NCDEWindowManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/NCDEWindowManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NCDEWindowManager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17NCDEWindowManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto NCDEWindowManager::qt_create_metaobjectdata<qt_meta_tag_ZN17NCDEWindowManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NCDEWindowManager",
        "countChanged",
        "",
        "mousePosChanged",
        "activeIndexChanged",
        "activeAppMenusChanged",
        "snapZoneChanged",
        "anyWindowMapped",
        "windowAdded",
        "win",
        "x",
        "y",
        "w",
        "h",
        "name",
        "appId",
        "windowRemoved",
        "windowStateChanged",
        "coveringCountChanged",
        "screenConfigChanged",
        "windowTierNeeded",
        "pid",
        "tier",
        "windowClosed",
        "screensaverIdleReached",
        "idleSample",
        "idleMs",
        "exposeToggleRequested",
        "switchDesktop",
        "target",
        "invokeAppMenu",
        "id",
        "setSnapZone",
        "z",
        "screenWidth",
        "screenHeight",
        "atomNetWmWindowType",
        "atomNetWmWindowTypeDesktop",
        "atomNetWmWindowTypeDock",
        "atomNetWmWindowTypePopupMenu",
        "atomNetWmWindowTypeTooltip",
        "setWindowType",
        "typeAtom",
        "rowForClient",
        "c",
        "winIdForName",
        "n",
        "hasWindowForName",
        "isMinimizedForName",
        "isActiveForName",
        "isMaximizedForName",
        "activateWindow",
        "minimizeWindow",
        "unminimizeWindow",
        "moveWindow",
        "resizeWindow",
        "wid",
        "hgt",
        "moveTiledWindow",
        "setTiled",
        "t",
        "isMaximized",
        "setMaximized",
        "client",
        "maximized",
        "closeWindow",
        "systemCommand",
        "cmd",
        "registerFrameWindowQml",
        "frame",
        "destroyFrameWindow",
        "userIdleMs",
        "count",
        "coveringCount",
        "mouseX",
        "mouseY",
        "activeIndex",
        "activeAppMenus",
        "snapZone"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'countChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mousePosChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'activeIndexChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'activeAppMenusChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'snapZoneChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'anyWindowMapped'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'windowAdded'
        QtMocHelpers::SignalData<void(uint, int, int, int, int, const QString &, const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 9 }, { QMetaType::Int, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
            { QMetaType::Int, 13 }, { QMetaType::QString, 14 }, { QMetaType::QString, 15 },
        }}),
        // Signal 'windowRemoved'
        QtMocHelpers::SignalData<void(uint)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 9 },
        }}),
        // Signal 'windowStateChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'coveringCountChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'screenConfigChanged'
        QtMocHelpers::SignalData<void(int, int)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Int, 13 },
        }}),
        // Signal 'windowTierNeeded'
        QtMocHelpers::SignalData<void(uint, const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 21 }, { QMetaType::QString, 22 },
        }}),
        // Signal 'windowClosed'
        QtMocHelpers::SignalData<void(uint)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 21 },
        }}),
        // Signal 'screensaverIdleReached'
        QtMocHelpers::SignalData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'idleSample'
        QtMocHelpers::SignalData<void(qint64)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 26 },
        }}),
        // Signal 'exposeToggleRequested'
        QtMocHelpers::SignalData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'switchDesktop'
        QtMocHelpers::SlotData<void(int)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 29 },
        }}),
        // Method 'invokeAppMenu'
        QtMocHelpers::MethodData<void(int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 31 },
        }}),
        // Method 'setSnapZone'
        QtMocHelpers::MethodData<void(int)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 33 },
        }}),
        // Method 'screenWidth'
        QtMocHelpers::MethodData<int() const>(34, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'screenHeight'
        QtMocHelpers::MethodData<int() const>(35, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'atomNetWmWindowType'
        QtMocHelpers::MethodData<uint() const>(36, 2, QMC::AccessPublic, QMetaType::UInt),
        // Method 'atomNetWmWindowTypeDesktop'
        QtMocHelpers::MethodData<uint() const>(37, 2, QMC::AccessPublic, QMetaType::UInt),
        // Method 'atomNetWmWindowTypeDock'
        QtMocHelpers::MethodData<uint() const>(38, 2, QMC::AccessPublic, QMetaType::UInt),
        // Method 'atomNetWmWindowTypePopupMenu'
        QtMocHelpers::MethodData<uint() const>(39, 2, QMC::AccessPublic, QMetaType::UInt),
        // Method 'atomNetWmWindowTypeTooltip'
        QtMocHelpers::MethodData<uint() const>(40, 2, QMC::AccessPublic, QMetaType::UInt),
        // Method 'setWindowType'
        QtMocHelpers::MethodData<void(uint, uint)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 9 }, { QMetaType::UInt, 42 },
        }}),
        // Method 'rowForClient'
        QtMocHelpers::MethodData<int(uint) const>(43, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::UInt, 44 },
        }}),
        // Method 'winIdForName'
        QtMocHelpers::MethodData<uint(const QString &) const>(45, 2, QMC::AccessPublic, QMetaType::UInt, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'hasWindowForName'
        QtMocHelpers::MethodData<bool(const QString &) const>(47, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'isMinimizedForName'
        QtMocHelpers::MethodData<bool(const QString &) const>(48, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'isActiveForName'
        QtMocHelpers::MethodData<bool(const QString &) const>(49, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'isMaximizedForName'
        QtMocHelpers::MethodData<bool(const QString &) const>(50, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 46 },
        }}),
        // Method 'activateWindow'
        QtMocHelpers::MethodData<void(uint)>(51, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 },
        }}),
        // Method 'minimizeWindow'
        QtMocHelpers::MethodData<void(uint)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 },
        }}),
        // Method 'unminimizeWindow'
        QtMocHelpers::MethodData<void(uint)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 },
        }}),
        // Method 'moveWindow'
        QtMocHelpers::MethodData<void(uint, int, int)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 }, { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Method 'resizeWindow'
        QtMocHelpers::MethodData<void(uint, int, int)>(55, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 }, { QMetaType::Int, 56 }, { QMetaType::Int, 57 },
        }}),
        // Method 'moveTiledWindow'
        QtMocHelpers::MethodData<void(uint, int, int, int, int)>(58, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 }, { QMetaType::Int, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 56 },
            { QMetaType::Int, 57 },
        }}),
        // Method 'setTiled'
        QtMocHelpers::MethodData<void(uint, bool)>(59, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 }, { QMetaType::Bool, 60 },
        }}),
        // Method 'isMaximized'
        QtMocHelpers::MethodData<bool(uint) const>(61, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::UInt, 12 },
        }}),
        // Method 'setMaximized'
        QtMocHelpers::MethodData<void(uint, bool)>(62, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 63 }, { QMetaType::Bool, 64 },
        }}),
        // Method 'closeWindow'
        QtMocHelpers::MethodData<void(uint)>(65, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 12 },
        }}),
        // Method 'systemCommand'
        QtMocHelpers::MethodData<void(const QString &)>(66, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 67 },
        }}),
        // Method 'registerFrameWindowQml'
        QtMocHelpers::MethodData<void(uint, QObject *)>(68, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 63 }, { QMetaType::QObjectStar, 69 },
        }}),
        // Method 'destroyFrameWindow'
        QtMocHelpers::MethodData<void(uint)>(70, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 63 },
        }}),
        // Method 'userIdleMs'
        QtMocHelpers::MethodData<qint64() const>(71, 2, QMC::AccessPublic, QMetaType::LongLong),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'count'
        QtMocHelpers::PropertyData<int>(72, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'coveringCount'
        QtMocHelpers::PropertyData<int>(73, QMetaType::Int, QMC::DefaultPropertyFlags, 9),
        // property 'mouseX'
        QtMocHelpers::PropertyData<int>(74, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'mouseY'
        QtMocHelpers::PropertyData<int>(75, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'activeIndex'
        QtMocHelpers::PropertyData<int>(76, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'activeAppMenus'
        QtMocHelpers::PropertyData<QString>(77, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'snapZone'
        QtMocHelpers::PropertyData<int>(78, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NCDEWindowManager, qt_meta_tag_ZN17NCDEWindowManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NCDEWindowManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NCDEWindowManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NCDEWindowManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17NCDEWindowManagerE_t>.metaTypes,
    nullptr
} };

void NCDEWindowManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NCDEWindowManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->mousePosChanged(); break;
        case 2: _t->activeIndexChanged(); break;
        case 3: _t->activeAppMenusChanged(); break;
        case 4: _t->snapZoneChanged(); break;
        case 5: _t->anyWindowMapped(); break;
        case 6: _t->windowAdded((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[7]))); break;
        case 7: _t->windowRemoved((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 8: _t->windowStateChanged(); break;
        case 9: _t->coveringCountChanged(); break;
        case 10: _t->screenConfigChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->windowTierNeeded((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->windowClosed((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 13: _t->screensaverIdleReached(); break;
        case 14: _t->idleSample((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 15: _t->exposeToggleRequested(); break;
        case 16: _t->switchDesktop((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->invokeAppMenu((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->setSnapZone((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 19: { int _r = _t->screenWidth();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->screenHeight();
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 21: { uint _r = _t->atomNetWmWindowType();
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 22: { uint _r = _t->atomNetWmWindowTypeDesktop();
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 23: { uint _r = _t->atomNetWmWindowTypeDock();
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 24: { uint _r = _t->atomNetWmWindowTypePopupMenu();
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 25: { uint _r = _t->atomNetWmWindowTypeTooltip();
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->setWindowType((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[2]))); break;
        case 27: { int _r = _t->rowForClient((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 28: { uint _r = _t->winIdForName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<uint*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->hasWindowForName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->isMinimizedForName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->isActiveForName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->isMaximizedForName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->activateWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 34: _t->minimizeWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 35: _t->unminimizeWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 36: _t->moveWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 37: _t->resizeWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 38: _t->moveTiledWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5]))); break;
        case 39: _t->setTiled((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 40: { bool _r = _t->isMaximized((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 41: _t->setMaximized((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 42: _t->closeWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 43: _t->systemCommand((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 44: _t->registerFrameWindowQml((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QObject*>>(_a[2]))); break;
        case 45: _t->destroyFrameWindow((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 46: { qint64 _r = _t->userIdleMs();
            if (_a[0]) *reinterpret_cast<qint64*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::countChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::mousePosChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::activeIndexChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::activeAppMenusChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::snapZoneChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::anyWindowMapped, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(uint , int , int , int , int , const QString & , const QString & )>(_a, &NCDEWindowManager::windowAdded, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(uint )>(_a, &NCDEWindowManager::windowRemoved, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::windowStateChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::coveringCountChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(int , int )>(_a, &NCDEWindowManager::screenConfigChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(uint , const QString & )>(_a, &NCDEWindowManager::windowTierNeeded, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(uint )>(_a, &NCDEWindowManager::windowClosed, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::screensaverIdleReached, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)(qint64 )>(_a, &NCDEWindowManager::idleSample, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (NCDEWindowManager::*)()>(_a, &NCDEWindowManager::exposeToggleRequested, 15))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->count(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->coveringCount(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->mouseX(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->mouseY(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->activeIndex(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->activeAppMenus(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->snapZone(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 6: _t->setSnapZone(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *NCDEWindowManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NCDEWindowManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NCDEWindowManagerE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QAbstractNativeEventFilter"))
        return static_cast< QAbstractNativeEventFilter*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int NCDEWindowManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 47)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 47;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 47)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 47;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void NCDEWindowManager::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NCDEWindowManager::mousePosChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NCDEWindowManager::activeIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NCDEWindowManager::activeAppMenusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NCDEWindowManager::snapZoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NCDEWindowManager::anyWindowMapped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void NCDEWindowManager::windowAdded(uint _t1, int _t2, int _t3, int _t4, int _t5, const QString & _t6, const QString & _t7)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}

// SIGNAL 7
void NCDEWindowManager::windowRemoved(uint _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void NCDEWindowManager::windowStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void NCDEWindowManager::coveringCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void NCDEWindowManager::screenConfigChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2);
}

// SIGNAL 11
void NCDEWindowManager::windowTierNeeded(uint _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2);
}

// SIGNAL 12
void NCDEWindowManager::windowClosed(uint _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void NCDEWindowManager::screensaverIdleReached()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void NCDEWindowManager::idleSample(qint64 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void NCDEWindowManager::exposeToggleRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}
QT_WARNING_POP
