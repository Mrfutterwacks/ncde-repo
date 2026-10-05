// NotificationManager — notification server, history, DND, quiet hours
// Rebuilt from oracle: NotificationManager::NotificationManager, notify, dismiss, dismissAll,
// markRead, setAppNotify, inQuietHours, saveApps, appsChanged, notifications, hasNotifications,
// unreadCount, notifyApps
// Spec: ncde-architecture.md §7 (LaPivot owns org.freedesktop.Notifications)
// DEFECTS FIXED vs oracle:
// 1. Added setSettings(Settings*) to wire DND (settings.dnd) and quiet hours (quietHoursOn,
//    quietFrom "10:00 PM", quietTo "7:00 AM" crossing midnight)
// 2. notify() now honours DND + quiet hours before showing
// 3. Registers org.freedesktop.Notifications (not org.ncde.desktop) via FreedesktopNotificationsAdaptor

#pragma once

class FreedesktopNotificationsAdaptor;

#include <QDateTime>
#include <QDBusConnection>
#include <QObject>
#include <QDBusAbstractAdaptor>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QString>

class Settings;
class QTime;

class NotificationManager : public QObject
{
    Q_OBJECT
    Q_MOC_INCLUDE("Settings.h")   // Settings* is a Q_INVOKABLE argument; moc needs the full type
// ---- GENERATED: tools/gen_header.py NotificationManager ----
    Q_PROPERTY(QVariantList notifications READ notifications NOTIFY changed)
    Q_PROPERTY(bool hasNotifications READ hasNotifications NOTIFY changed)
    Q_PROPERTY(int unreadCount READ unreadCount NOTIFY changed)
    Q_PROPERTY(QVariantList notifyApps READ notifyApps NOTIFY appsChanged)

public:
    QVariantList notifications() const;
    bool hasNotifications() const;
    int unreadCount() const;
    QVariantList notifyApps() const;

    Q_INVOKABLE void setAppNotify(const QString &name, bool on);
    Q_INVOKABLE int notify(const QString &title, const QString &body, const QString &icon, int timeoutMs);
    Q_INVOKABLE void dismiss(int id);
    Q_INVOKABLE void dismissAll();
    Q_INVOKABLE void markRead();

signals:
    void changed();
    void appsChanged();
// ---- END GENERATED ----

public:
    // ---- additions beyond the oracle ----
    Q_INVOKABLE void setSettings(Settings *settings);

public:
    explicit NotificationManager(QObject *parent = nullptr);
    ~NotificationManager() override;

    // D-Bus service registration (called from main.cpp)
    bool registerDBusService();

private:
    friend class FreedesktopNotificationsAdaptor;
    friend class TestNotificationManager;

    struct Notification {
        int id;
        QString appName;
        QString title;
        QString body;
        QString icon;
        int timeout;
        bool read = false;
        bool fromDBus = false;
        QDateTime timestamp;
    };

    int addNotification(const QString &appName, const QString &title, const QString &body,
                        const QString &icon, int timeoutMs, int replacesId, bool fromDBus);
    int notifyFromDBus(const QString &appName, uint replacesId, const QString &icon,
                       const QString &summary, const QString &body, int timeoutMs);
    bool removeNotification(int id, uint closeReason);
    void saveApps();
    bool inQuietHours() const;
    bool inQuietHoursAt(const QTime &now) const;
    void loadAppsFromConfig();

    Settings *m_settings = nullptr;
    QList<Notification> m_notifications;
    QMap<QString, bool> m_appEnabled; // app name -> notifications enabled
    int m_nextId = 1;

    ::FreedesktopNotificationsAdaptor *m_adaptor = nullptr;
    bool m_busObjectRegistered = false;
    bool m_busServiceRegistered = false;
};