// NotificationManager.cpp — core implementation
// Rebuilt from oracle: NotificationManager constructor, notify, dismiss, dismissAll, markRead,
// setAppNotify, inQuietHours, saveApps, notifications, hasNotifications, unreadCount, notifyApps
// DEFECTS FIXED vs oracle:
// 1. Added setSettings(Settings*) — wires DND (settings.dnd) and quiet hours
// 2. notify() checks DND + quiet hours before accepting notification
// 3. Registers org.freedesktop.Notifications via FreedesktopNotificationsAdaptor

#include "NotificationManager.h"
#include "FreedesktopNotificationsAdaptor.h"
#include "Settings.h"
#include "Lelan.h" // for config read/write

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDateTime>
#include <QTime>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

NotificationManager::NotificationManager(QObject *parent)
    : QObject(parent)
{
    loadAppsFromConfig();
}

NotificationManager::~NotificationManager()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (m_busObjectRegistered)
        bus.unregisterObject(QStringLiteral("/org/freedesktop/Notifications"));
    if (m_busServiceRegistered)
        bus.unregisterService(QStringLiteral("org.freedesktop.Notifications"));
}

void NotificationManager::setSettings(Settings *settings)
{
    m_settings = settings;
}

void NotificationManager::loadAppsFromConfig()
{
    // Read from Lelan's config (notify-apps)
    QVariantMap config = Lelan::readConfig("notify-apps");
    for (auto it = config.constBegin(); it != config.constEnd(); ++it) {
        m_appEnabled[it.key()] = it.value().toBool();
    }
}

bool NotificationManager::inQuietHours() const
{
    if (!m_settings)
        return false;

    return m_settings->quietHoursOn() && inQuietHoursAt(QTime::currentTime());
}

bool NotificationManager::inQuietHoursAt(const QTime &now) const
{
    if (!m_settings || !m_settings->quietHoursOn())
        return false;
    QString fromStr = m_settings->quietFrom(); // "10:00 PM"
    QString toStr = m_settings->quietTo();     // "7:00 AM"

    QTime from = QTime::fromString(fromStr, "h:mm AP");
    QTime to = QTime::fromString(toStr, "h:mm AP");

    if (!from.isValid() || !to.isValid())
        return false;

    if (from > to) {
        return now >= from || now < to;
    }
    return now >= from && now < to;
}

void NotificationManager::saveApps()
{
    QVariantMap data;
    for (auto it = m_appEnabled.constBegin(); it != m_appEnabled.constEnd(); ++it) {
        data[it.key()] = it.value();
    }
    Lelan::writeConfig("notify-apps", data);
}

QVariantList NotificationManager::notifications() const
{
    QVariantList list;
    for (const auto &n : m_notifications) {
        QVariantMap map;
        map["id"] = n.id;
        map["appName"] = n.appName;
        map["title"] = n.title;
        map["body"] = n.body;
        map["icon"] = n.icon;
        map["timeout"] = n.timeout;
        map["read"] = n.read;
        map["timestamp"] = n.timestamp.toString(Qt::ISODate);
        list.append(map);
    }
    return list;
}

bool NotificationManager::hasNotifications() const
{
    return !m_notifications.isEmpty();
}

int NotificationManager::unreadCount() const
{
    int count = 0;
    for (const auto &n : m_notifications) {
        if (!n.read)
            count++;
    }
    return count;
}

QVariantList NotificationManager::notifyApps() const
{
    QVariantList list;
    for (auto it = m_appEnabled.constBegin(); it != m_appEnabled.constEnd(); ++it) {
        QVariantMap map;
        map["name"] = it.key();
        map["on"] = it.value();
        map["icon"] = QString("🔔"); // Default icon
        map["meta"] = it.value() ? "Notifications on" : "Notifications off";
        list.append(map);
    }
    return list;
}

void NotificationManager::setAppNotify(const QString &name, bool on)
{
    bool current = m_appEnabled.value(name, true);
    if (current != on) {
        m_appEnabled[name] = on;
        saveApps();
        emit appsChanged();
    }
}

int NotificationManager::notify(const QString &title, const QString &body, const QString &icon, int timeoutMs)
{
    return addNotification(title, title, body, icon, timeoutMs, 0, false);
}

int NotificationManager::notifyFromDBus(const QString &appName, uint replacesId, const QString &icon,
                                         const QString &summary, const QString &body, int timeoutMs)
{
    const int qmlTimeout = timeoutMs == -1 ? 0 : (timeoutMs == 0 ? 5000 : timeoutMs);
    return addNotification(appName, summary, body, icon, qmlTimeout,
                           static_cast<int>(replacesId), true);
}

int NotificationManager::addNotification(const QString &appName, const QString &title, const QString &body,
                                           const QString &icon, int timeoutMs, int replacesId, bool fromDBus)
{
    if (m_settings && m_settings->dnd())
        return 0;
    if (inQuietHours())
        return 0;
    if (!m_appEnabled.value(appName, true))
        return 0;

    int id = replacesId;
    Notification *existing = nullptr;
    if (id > 0) {
        for (Notification &n : m_notifications) {
            if (n.id == id) {
                existing = &n;
                break;
            }
        }
    }
    if (!existing)
        id = m_nextId++;

    Notification n;
    n.id = id;
    n.appName = appName;
    n.title = title;
    n.body = body;
    n.icon = icon;
    n.timeout = timeoutMs;
    n.fromDBus = fromDBus;
    n.timestamp = QDateTime::currentDateTime();

    if (existing)
        *existing = n;
    else
        m_notifications.prepend(n);

    const bool newApp = !m_appEnabled.contains(appName);
    if (newApp)
        m_appEnabled.insert(appName, true);

    if (newApp)
        emit appsChanged();
    emit changed();
    return id;
}

void NotificationManager::dismiss(int id)
{
    removeNotification(id, 2);
}

void NotificationManager::dismissAll()
{
    if (!m_notifications.isEmpty()) {
        for (const Notification &n : std::as_const(m_notifications)) {
            if (n.fromDBus && m_adaptor)
                emit m_adaptor->NotificationClosed(static_cast<uint>(n.id), 2);
        }
        m_notifications.clear();
        emit changed();
    }
}

void NotificationManager::markRead()
{
    bool changedAny = false;
    for (auto &n : m_notifications) {
        if (!n.read) {
            n.read = true;
            changedAny = true;
        }
    }
    if (changedAny)
        emit changed();
}

bool NotificationManager::removeNotification(int id, uint closeReason)
{
    for (int i = 0; i < m_notifications.size(); ++i) {
        const Notification notification = m_notifications.at(i);
        if (notification.id != id)
            continue;
        m_notifications.removeAt(i);
        if (notification.fromDBus && m_adaptor)
            emit m_adaptor->NotificationClosed(static_cast<uint>(id), closeReason);
        emit changed();
        return true;
    }
    return false;
}

bool NotificationManager::registerDBusService()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.isConnected())
        return false;

    if (m_busServiceRegistered && m_busObjectRegistered)
        return true;
    if (!bus.registerService(QStringLiteral("org.freedesktop.Notifications")))
        return false;
    m_busServiceRegistered = true;

    if (!m_adaptor)
        m_adaptor = new FreedesktopNotificationsAdaptor(this);
    if (!bus.registerObject(QStringLiteral("/org/freedesktop/Notifications"), this,
                            QDBusConnection::ExportAdaptors)) {
        bus.unregisterService(QStringLiteral("org.freedesktop.Notifications"));
        m_busServiceRegistered = false;
        return false;
    }
    m_busObjectRegistered = true;
    return true;
}