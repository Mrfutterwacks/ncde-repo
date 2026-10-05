// FreedesktopNotificationsAdaptor — org.freedesktop.Notifications D-Bus interface
// Implements the standard freedesktop notification spec:
//   Notify, CloseNotification, GetCapabilities, GetServerInformation
// LaPivot (ncde-wm) owns this service per ncde-architecture.md §7

#pragma once

#include <QDBusAbstractAdaptor>
#include <QString>
#include <QStringList>
#include <QVariantMap>

class NotificationManager;

class FreedesktopNotificationsAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")

public:
    explicit FreedesktopNotificationsAdaptor(NotificationManager *manager);
    ~FreedesktopNotificationsAdaptor() override = default;

public slots: // D-Bus methods
    // Notify(app_name, replaces_id, app_icon, summary, body, actions, hints, timeout) -> id
    uint Notify(const QString &appName, uint replacesId, const QString &appIcon,
                const QString &summary, const QString &body,
                const QStringList &actions, const QVariantMap &hints, int timeout);

    // CloseNotification(id)
    void CloseNotification(uint id);

    // GetCapabilities() -> [capabilities]
    QStringList GetCapabilities();

    // GetServerInformation() -> (name, vendor, version, spec_version)
    void GetServerInformation(QString &name, QString &vendor, QString &version, QString &specVersion);

signals: // D-Bus signals
    // NotificationClosed(id, reason)
    void NotificationClosed(uint id, uint reason);

    // ActionInvoked(id, action_key)
    void ActionInvoked(uint id, const QString &actionKey);

private:
    friend class NotificationManager;

    NotificationManager *m_manager = nullptr;
};