// IdleInhibitService — see IdleInhibitService.h for the spec and the defect list.
// Rebuilt from oracle: decomp/IdleInhibitService.c (ctor 0x15d3ea, Inhibit 0x15d936,
// UnInhibit 0x15dbea, dropOwner 0x15dd48, resetIdle 0x15de74).
#include "IdleInhibitService.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QGuiApplication>
#include <QMessageLogger>
#include <QtLogging>

#include <xcb/xcb.h>
#include <xcb/screensaver.h>

IdleInhibitService::IdleInhibitService(QObject *parent) : QObject(parent), QDBusContext()
{
    // Get XCB connection
    QGuiApplication *guiApp = qobject_cast<QGuiApplication *>(QCoreApplication::instance());
    if (guiApp) {
        auto *x11 = guiApp->nativeInterface<QNativeInterface::QX11Application>();
        if (x11) {
            m_xcb = x11->connection();
        }
    }

    // Register D-Bus service
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService("org.freedesktop.ScreenSaver")) {
        qWarning("IdleInhibit: could not own org.freedesktop.ScreenSaver (already claimed?)");
    }

    // Register object at two paths (oracle parity)
    const QDBusConnection::RegisterOptions opts =
        QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportScriptableInvokables;
    bus.registerObject("/org/freedesktop/ScreenSaver", this, opts);
    bus.registerObject("/ScreenSaver", this, opts);

    // Service watcher for owner disappearance
    m_watcher = new QDBusServiceWatcher(this);
    m_watcher->setConnection(bus);
    m_watcher->setWatchedServices(QStringList() << "org.freedesktop.ScreenSaver");
    m_watcher->setWatchMode(QDBusServiceWatcher::WatchForUnregistration);
    connect(m_watcher, &QDBusServiceWatcher::serviceUnregistered,
            this, &IdleInhibitService::dropOwner);

    // Timer for periodic idle reset (II1: 10 s interval)
    m_timer = new QTimer(this);
    m_timer->setInterval(10000);
    connect(m_timer, &QTimer::timeout, this, &IdleInhibitService::resetIdle);
}

IdleInhibitService::~IdleInhibitService() = default;

uint IdleInhibitService::Inhibit(const QString &application_name, const QString &reason_for_inhibit)
{
    // Only allow D-Bus callers
    if (!calledFromDBus()) {
        return 0;
    }

    QString sender = message().service();

    uint cookie = m_nextCookie++;
    m_cookies[cookie] = sender;
    m_ownerMap[sender].append(cookie);

    // Watch the sender's bus name
    m_watcher->addWatchedService(sender);

    // Log the inhibit
    QMessageLogger().info("IdleInhibit: cookie %u from %s (%s: %s)",
                          cookie, sender.toUtf8().constData(),
                          application_name.toUtf8().constData(),
                          reason_for_inhibit.toUtf8().constData());

    // Reset idle timer (only if we have an X connection)
    resetIdle();

    // Start the periodic timer
    m_timer->start();

    return cookie;
}

void IdleInhibitService::UnInhibit(uint cookie)
{
    QString sender = m_cookies.take(cookie);
    if (sender.isEmpty())
        return;

    // Remove from owner map
    auto it = m_ownerMap.find(sender);
    if (it != m_ownerMap.end()) {
        it->removeAll(cookie);
        if (it->isEmpty()) {
            m_ownerMap.erase(it);
            m_watcher->removeWatchedService(sender);
        }
    }

    // If no more inhibits, stop the timer
    if (m_cookies.isEmpty()) {
        m_timer->stop();
    }
}

void IdleInhibitService::dropOwner(const QString &serviceName)
{
    // Called when a service vanishes from the bus
    auto it = m_ownerMap.find(serviceName);
    if (it == m_ownerMap.end())
        return;

    // Remove all cookies for this owner
    for (uint cookie : *it) {
        m_cookies.remove(cookie);
    }
    m_ownerMap.erase(it);
    m_watcher->removeWatchedService(serviceName);

    // If no more inhibits, stop the timer
    if (m_cookies.isEmpty()) {
        m_timer->stop();
    }
}

void IdleInhibitService::resetIdle()
{
    // II2: only reset if we have active inhibits and a valid X connection
    if (m_cookies.isEmpty() || !m_xcb)
        return;

    xcb_force_screen_saver(m_xcb, XCB_SCREEN_SAVER_RESET);
    xcb_flush(m_xcb);
}