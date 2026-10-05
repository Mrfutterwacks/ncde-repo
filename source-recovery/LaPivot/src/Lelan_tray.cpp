// Lelan — StatusNotifierItem tray and notification-action events on the session bus.
// Rebuilt from oracle: subscribeTrayOwner, rebuildTray, onTrayItemChanged, onLayoutUpdated,
// onActionInvoked, tray(), notifications().
// Spec: lelan.md §4/§5 SNI watcher and dbusmenu consumer; cache state and emit only on change.
//
// DEFECTS FIXED vs oracle:
// 1. Tray item properties are fetched asynchronously and only the currently registered item set is
//    published; delayed replies from an older watcher snapshot are discarded.
#include "Lelan.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QtLogging>

#include <algorithm>
#include <utility>

namespace {
const QString kProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kWatcher = QStringLiteral("org.kde.StatusNotifierWatcher");
const QString kWatcherPath = QStringLiteral("/StatusNotifierWatcher");
const QString kWatcherIface = QStringLiteral("org.kde.StatusNotifierWatcher");
const QString kItemIface = QStringLiteral("org.kde.StatusNotifierItem");
const QString kMenuIface = QStringLiteral("com.canonical.dbusmenu");
const QString kNotifications = QStringLiteral("org.freedesktop.Notifications");
const QString kNotificationsPath = QStringLiteral("/org/freedesktop/Notifications");

QString itemKey(const QString &service, const QString &path)
{
    return service + QLatin1Char('|') + path;
}

QPair<QString, QString> splitRegisteredItem(const QString &value)
{
    const qsizetype slash = value.indexOf(QLatin1Char('/'));
    if (slash < 0)
        return {value, QStringLiteral("/StatusNotifierItem")};
    return {value.left(slash), value.mid(slash)};
}
} // namespace

QVariantList Lelan::tray() const { return m_tray; }
QVariantList Lelan::notifications() const { return m_notifications; }

void Lelan::subscribeTrayOwner()
{
    auto bus = QDBusConnection::sessionBus();
    bus.connect(kWatcher, kWatcherPath, kWatcherIface, QStringLiteral("StatusNotifierItemRegistered"),
                this, SLOT(onTrayItemChanged()));
    bus.connect(kWatcher, kWatcherPath, kWatcherIface, QStringLiteral("StatusNotifierItemUnregistered"),
                this, SLOT(onTrayItemChanged()));
    bus.connect(kWatcher, kWatcherPath, kProps, QStringLiteral("PropertiesChanged"),
                this, SLOT(onTrayItemChanged()));
    bus.connect(QString(), QString(), kMenuIface, QStringLiteral("LayoutUpdated"),
                this, SLOT(onLayoutUpdated()));
    bus.connect(kNotifications, kNotificationsPath, kNotifications,
                QStringLiteral("ActionInvoked"), this, SLOT(onActionInvoked(uint,QString)));
    rebuildTray();
}

void Lelan::rebuildTray()
{
    const quint64 generation = ++m_trayGeneration;
    QDBusMessage get = QDBusMessage::createMethodCall(kWatcher, kWatcherPath, kProps,
                                                       QStringLiteral("Get"));
    get << kWatcherIface << QStringLiteral("RegisteredStatusNotifierItems");
    auto bus = QDBusConnection::sessionBus();
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(get), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, generation](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusVariant> reply = *w;
        w->deleteLater();
        if (generation != m_trayGeneration)
            return;
        if (reply.isError()) {
            m_trayItems.clear();
            m_registeredTrayItems.clear();
            if (!m_tray.isEmpty()) {
                m_tray.clear();
                emit trayChanged();
            }
            return;
        }
        const QVariant value = reply.value().variant();
        QStringList registered = value.toStringList();
        if (registered.isEmpty() && value.canConvert<QVariantList>()) {
            for (const QVariant &entry : value.toList())
                registered.append(entry.toString());
        }
        QVariantList items;
        for (const QString &entry : std::as_const(registered)) {
            const auto parsed = splitRegisteredItem(entry);
            items.append(QVariantMap{{QStringLiteral("service"), parsed.first},
                                     {QStringLiteral("path"), parsed.second}});
        }
        publishTrayItems(items);
    });
}

void Lelan::publishTrayItems(const QVariantList &items)
{
    QSet<QString> wanted;
    for (const QVariant &value : items) {
        const QVariantMap item = value.toMap();
        const QString service = item.value(QStringLiteral("service")).toString();
        const QString path = item.value(QStringLiteral("path")).toString();
        if (service.isEmpty() || !path.startsWith(QLatin1Char('/')))
            continue;
        wanted.insert(itemKey(service, path));
        readTrayItem(service, path, m_trayGeneration);
        auto bus = QDBusConnection::sessionBus();
        for (const QString &signal : {QStringLiteral("NewIcon"), QStringLiteral("NewTitle"),
                                      QStringLiteral("NewStatus"), QStringLiteral("NewToolTip"),
                                      QStringLiteral("NewAttentionIcon"), QStringLiteral("NewOverlayIcon"),
                                      QStringLiteral("NewItemIsMenu")})
            bus.connect(service, path, kItemIface, signal, this, SLOT(onTrayItemChanged()));
        const QString menu = m_trayItems.value(itemKey(service, path))
                                 .value(QStringLiteral("menu")).toString();
        if (!menu.isEmpty() && menu.startsWith(QLatin1Char('/')))
            bus.connect(service, menu, kMenuIface, QStringLiteral("LayoutUpdated"),
                         this, SLOT(onLayoutUpdated()));
    }
    m_registeredTrayItems = wanted;
    for (auto it = m_trayItems.begin(); it != m_trayItems.end();) {
        if (!wanted.contains(it.key()))
            it = m_trayItems.erase(it);
        else
            ++it;
    }
}

void Lelan::readTrayItem(const QString &service, const QString &path, quint64 generation)
{
    QDBusMessage getAll = QDBusMessage::createMethodCall(service, path, kProps, QStringLiteral("GetAll"));
    getAll << kItemIface;
    const auto bus = QDBusConnection::sessionBus();
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(getAll), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, service, path, generation](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        w->deleteLater();
        if (reply.isError() || generation != m_trayGeneration
            || !m_registeredTrayItems.contains(itemKey(service, path)))
            return;
        const QVariantMap props = reply.value();
        QVariantMap item{{QStringLiteral("service"), service},
                         {QStringLiteral("path"), path},
                         {QStringLiteral("id"), props.value(QStringLiteral("Id")).toString()},
                         {QStringLiteral("title"), props.value(QStringLiteral("Title")).toString()},
                         {QStringLiteral("category"), props.value(QStringLiteral("Category")).toString()},
                         {QStringLiteral("status"), props.value(QStringLiteral("Status")).toString()},
                         {QStringLiteral("iconName"), props.value(QStringLiteral("IconName")).toString()},
                         {QStringLiteral("attentionIconName"),
                          props.value(QStringLiteral("AttentionIconName")).toString()},
                         {QStringLiteral("menu"), props.value(QStringLiteral("Menu")).toString()},
                         {QStringLiteral("itemIsMenu"), props.value(QStringLiteral("ItemIsMenu")).toBool()}};
        const QString key = itemKey(service, path);
        if (item == m_trayItems.value(key))
            return;
        m_trayItems.insert(key, item);
        QStringList keys = m_trayItems.keys();
        std::sort(keys.begin(), keys.end());
        QVariantList next;
        for (const QString &entry : std::as_const(keys))
            next.append(m_trayItems.value(entry));
        if (next != m_tray) {
            m_tray = next;
            emit trayChanged();
        }
    });
}

void Lelan::onTrayItemChanged()
{
    rebuildTray();
}

void Lelan::onLayoutUpdated()
{
    emit trayChanged();
}

void Lelan::onActionInvoked(uint id, const QString &action)
{
    QVariantList next = m_notifications;
    next.prepend(QVariantMap{{QStringLiteral("id"), id}, {QStringLiteral("action"), action}});
    while (next.size() > 20)
        next.removeLast();
    if (next == m_notifications)
        return;
    m_notifications = next;
    publishNotifications();
}

void Lelan::publishNotifications()
{
    emit notificationsChanged();
}
