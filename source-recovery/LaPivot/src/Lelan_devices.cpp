// Lelan — Sentinel device events: displays, USB, input, audio, drivers.
// Rebuilt from oracle: onSentinelDisplayConnected/Disconnected, UsbDeviceAdded/Removed,
// InputDeviceAdded/Removed, AudioDeviceChanged, DriverMissing, onWMScreenConfig.
// Spec: lelan.md §4 (Sentinel device events); lelan-prompt.txt MUST-DO #2: ADD signal
// inputDevicesChanged() on real input-device list change (oracle only emitted statsChanged).
//
// DEFECTS FIXED vs oracle:
// 1. onSentinelInputDeviceAdded/Removed only emitted statsChanged, so a mouse plugged in after
//    login kept default speed — Settings could not react. Now emit inputDevicesChanged() there;
//    Settings connects it to applyInput().
// 2. Display connect/disconnect already emits screenConfigChanged (Settings re-reads displays) — kept.
#include "Lelan.h"
#include "lelan_dbus_relay.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QtLogging>

namespace {
const QString kSentinel = QStringLiteral("io.ncde.Sentinel");
const QString kSentinelPath = QStringLiteral("/io/ncde/Sentinel");
} // namespace

// ---- Sentinel display ---------------------------------------------------------------------------

void Lelan::onSentinelDisplayConnected(const QString &name)
{
    qInfo() << "[lelan] display connected:" << name;
    emit screenConfigChanged();
}

void Lelan::onSentinelDisplayDisconnected(const QString &name)
{
    qInfo() << "[lelan] display disconnected:" << name;
    emit screenConfigChanged();
}

// ---- Sentinel USB -------------------------------------------------------------------------------

void Lelan::onSentinelUsbDeviceAdded(const QString &id, const QString &name)
{
    qInfo() << "[lelan] usb added:" << id << name;
    emit statsChanged();                    // oracle compatibility
}

void Lelan::onSentinelUsbDeviceRemoved(const QString &id, const QString &name)
{
    qInfo() << "[lelan] usb removed:" << id << name;
    emit statsChanged();                    // oracle compatibility
}

// ---- Sentinel input (MUST-DO #2: emit inputDevicesChanged) --------------------------------------

void Lelan::onSentinelInputDeviceAdded(const QString &name)
{
    qInfo() << "[lelan] input device added:" << name;
    emit statsChanged();                    // oracle compatibility
    emit inputDevicesChanged();             // ADDED: Settings will connect to applyInput()
}

void Lelan::onSentinelInputDeviceRemoved(const QString &name)
{
    qInfo() << "[lelan] input device removed:" << name;
    emit statsChanged();                    // oracle compatibility
    emit inputDevicesChanged();             // ADDED: Settings will connect to applyInput()
}

// ---- Sentinel audio -----------------------------------------------------------------------------

void Lelan::onSentinelAudioDeviceChanged(const QString &id, const QString &name)
{
    qInfo() << "[lelan] audio device changed:" << id << name;
    emit audioDevicesChanged();             // audio subsystem will re-query
}

// ---- Sentinel driver missing --------------------------------------------------------------------

void Lelan::onSentinelDriverMissing(const QString &device, const QString &modalias, const QString &suggested)
{
    qWarning() << "[lelan] driver missing:" << device << modalias << suggested;
    emit driverMissing(device, modalias, suggested);
}

// ---- WM screen config (from NCDEWindowManager) --------------------------------------------------

void Lelan::onWMScreenConfig(int, int)
{
    // Called by NCDEWindowManager when screen config changes.
    // Oracle just emitted screenConfigChanged.
    emit screenConfigChanged();
}