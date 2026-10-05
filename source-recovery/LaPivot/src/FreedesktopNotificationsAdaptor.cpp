// FreedesktopNotificationsAdaptor.cpp — org.freedesktop.Notifications implementation
// Rebuilt from freedesktop notification spec:
// https://specifications.freedesktop.org/notification-spec/latest/

#include "FreedesktopNotificationsAdaptor.h"
#include "NotificationManager.h"

#include <QDBusMessage>
#include <QVariant>

FreedesktopNotificationsAdaptor::FreedesktopNotificationsAdaptor(NotificationManager *manager)
    : QDBusAbstractAdaptor(manager)
    , m_manager(manager)
{
    setAutoRelaySignals(true); // Relay NotificationClosed, ActionInvoked to D-Bus
}

uint FreedesktopNotificationsAdaptor::Notify(const QString &appName, uint replacesId,
                                             const QString &appIcon, const QString &summary,
                                             const QString &body, const QStringList &actions,
                                             const QVariantMap &hints, int timeout)
{
    Q_UNUSED(actions);
    Q_UNUSED(hints);

    const int id = m_manager->notifyFromDBus(appName, replacesId, appIcon, summary, body, timeout);
    return static_cast<uint>(id);
}

void FreedesktopNotificationsAdaptor::CloseNotification(uint id)
{
    m_manager->removeNotification(static_cast<int>(id), 3);
}

QStringList FreedesktopNotificationsAdaptor::GetCapabilities()
{
   return QStringList() << "body";
}

void FreedesktopNotificationsAdaptor::GetServerInformation(QString &name, QString &vendor,
                                                           QString &version, QString &specVersion)
{
   name = QStringLiteral("NCDE Notification Server");
   vendor = QStringLiteral("NCDE Project");
   version = QStringLiteral("1.0");
   specVersion = QStringLiteral("1.2");
}