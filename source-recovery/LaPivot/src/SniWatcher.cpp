// SniWatcher.cpp — implementation
// Rebuilt from oracle: decomp/SniWatcher.c (11 oracle functions).
// Spec: docs/lelan-research-findings.md §4 and docs/lelan.md.
// Lelan owns per-item property reads and publishes tray data; SniWatcher owns registration,
// watcher/host names, owner-loss cleanup, and the watcher D-Bus protocol.
//
// DEFECTS FIXED vs oracle:
// 1. Both watcher adaptors are now attached before ExportAdaptors, and relay SniWatcher signals
//    to their exported D-Bus signals.
// 2. Watcher-name acquisition is independent: failure to own the optional freedesktop name does
//    not clear ownership of the primary KDE name or falsely enter client mode.
// 3. If another process owns the watcher, SniForeignWatcherRelay registers this process as a host,
//    snapshots RegisteredStatusNotifierItems asynchronously, and mirrors item add/remove signals.
// 4. Item registrations accept either a bus name or an object path, using the D-Bus caller for
//    object-path-only registrations as required by the SNI protocol.
// 5. Owner exit removes only that owner's items/hosts and emits itemsChanged only on real changes.
// 6. Relay/adaptor lifetimes are QObject-parented; no delete is issued through an incomplete type.

#include "SniWatcher.h"
#include "FdoStatusNotifierWatcherAdaptor.h"
#include "StatusNotifierWatcherAdaptor.h"

#include <QCoreApplication>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusReply>
#include <QDBusVariant>
#include <QDBusServiceWatcher>
#include <QSet>

#include <utility>

namespace {
constexpr auto kObjectPath = "/StatusNotifierWatcher";
constexpr auto kKdeWatcher = "org.kde.StatusNotifierWatcher";
constexpr auto kFdoWatcher = "org.freedesktop.StatusNotifierWatcher";
constexpr auto kKdeInterface = "org.kde.StatusNotifierWatcher";
constexpr auto kFdoInterface = "org.freedesktop.StatusNotifierWatcher";
constexpr auto kPropertiesInterface = "org.freedesktop.DBus.Properties";

QString ownerForKey(const QString &key)
{
    const qsizetype slash = key.indexOf(QLatin1Char('/'));
    return slash > 0 ? key.left(slash) : key;
}
}

SniForeignWatcherRelay::SniForeignWatcherRelay(SniWatcher *watcher, QObject *parent)
    : QObject(parent)
    , m_watcher(watcher)
    , m_bus(QDBusConnection::sessionBus())
{
}

void SniForeignWatcherRelay::watch(const QString &service, const QString &interfaceName)
{
    if (m_service == service && m_interface == interfaceName)
        return;

    stop();
    m_service = service;
    m_interface = interfaceName;
    ++m_generation;

    m_bus.connect(m_service, QString::fromLatin1(kObjectPath), m_interface,
                  QStringLiteral("StatusNotifierItemRegistered"),
                  this, SLOT(onItemRegistered(QString)));
    m_bus.connect(m_service, QString::fromLatin1(kObjectPath), m_interface,
                  QStringLiteral("StatusNotifierItemUnregistered"),
                  this, SLOT(onItemUnregistered(QString)));

    QDBusMessage hostCall = QDBusMessage::createMethodCall(
        m_service, QString::fromLatin1(kObjectPath), m_interface,
        QStringLiteral("RegisterStatusNotifierHost"));
    hostCall << m_bus.baseService();
    m_bus.asyncCall(hostCall);
    requestItems();
}

void SniForeignWatcherRelay::stop()
{
    ++m_generation;
    if (m_service.isEmpty())
        return;

    m_bus.disconnect(m_service, QString::fromLatin1(kObjectPath), m_interface,
                     QStringLiteral("StatusNotifierItemRegistered"),
                     this, SLOT(onItemRegistered(QString)));
    m_bus.disconnect(m_service, QString::fromLatin1(kObjectPath), m_interface,
                     QStringLiteral("StatusNotifierItemUnregistered"),
                     this, SLOT(onItemUnregistered(QString)));
    if (m_watcher && !m_items.isEmpty())
        m_watcher->removeItems(m_items);
    m_items.clear();
    m_service.clear();
    m_interface.clear();
}

void SniForeignWatcherRelay::requestItems()
{
    QDBusMessage message = QDBusMessage::createMethodCall(
        m_service, QString::fromLatin1(kObjectPath), QString::fromLatin1(kPropertiesInterface),
        QStringLiteral("Get"));
    message << m_interface << QStringLiteral("RegisteredStatusNotifierItems");

    auto *call = new QDBusPendingCallWatcher(m_bus.asyncCall(message), this);
    call->setProperty("sniGeneration", QVariant::fromValue<qulonglong>(m_generation));
    connect(call, &QDBusPendingCallWatcher::finished,
            this, &SniForeignWatcherRelay::onInitialItemsReady);
}

void SniForeignWatcherRelay::onInitialItemsReady(QDBusPendingCallWatcher *call)
{
    const quint64 generation = call->property("sniGeneration").toULongLong();
    QDBusPendingReply<QDBusVariant> reply = *call;
    call->deleteLater();
    if (reply.isError() || generation != m_generation)
        return;

    QVariant value = reply.value().variant();
    if (value.canConvert<QStringList>()) {
        const QStringList items = value.toStringList();
        for (const QString &item : items)
            addItem(item);
    }
}

void SniForeignWatcherRelay::onItemRegistered(const QString &service)
{
    addItem(service);
}

void SniForeignWatcherRelay::onItemUnregistered(const QString &service)
{
    removeItem(service);
}

void SniForeignWatcherRelay::addItem(const QString &service)
{
    if (!m_watcher || service.isEmpty() || m_items.contains(service))
        return;
    m_items.append(service);
    m_watcher->addItem(service, ownerForKey(service));
}

void SniForeignWatcherRelay::removeItem(const QString &service)
{
    if (!m_items.removeOne(service))
        return;
    if (m_watcher)
        m_watcher->removeItems({service});
}

SniWatcher::SniWatcher(QObject *parent)
    : QObject(parent)
    , m_bus(QDBusConnection::sessionBus())
{
    m_adaptor = new StatusNotifierWatcherAdaptor(this);
    m_fdoAdaptor = new FdoStatusNotifierWatcherAdaptor(this);

    connect(this, &SniWatcher::itemRegistered, m_adaptor,
            &StatusNotifierWatcherAdaptor::StatusNotifierItemRegistered);
    connect(this, &SniWatcher::itemUnregistered, m_adaptor,
            &StatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered);
    connect(this, &SniWatcher::hostChanged, this, [this] {
        if (m_hostRegistered)
            emit m_adaptor->StatusNotifierHostRegistered();
    });
    connect(this, &SniWatcher::itemRegistered, m_fdoAdaptor,
            &FdoStatusNotifierWatcherAdaptor::StatusNotifierItemRegistered);
    connect(this, &SniWatcher::itemUnregistered, m_fdoAdaptor,
            &FdoStatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered);
    connect(this, &SniWatcher::hostChanged, this, [this] {
        if (m_hostRegistered)
            emit m_fdoAdaptor->StatusNotifierHostRegistered();
    });

    m_bus.registerObject(QString::fromLatin1(kObjectPath), this,
                         QDBusConnection::ExportAdaptors);

    m_serviceWatcher = new QDBusServiceWatcher(this);
    m_serviceWatcher->setConnection(m_bus);
    m_serviceWatcher->setWatchMode(QDBusServiceWatcher::WatchForUnregistration);
    connect(m_serviceWatcher, &QDBusServiceWatcher::serviceUnregistered,
            this, &SniWatcher::onOwnerLeft);

    m_relay = new SniForeignWatcherRelay(this, this);
    m_nameWatcher = new QDBusServiceWatcher(this);
    m_nameWatcher->setConnection(m_bus);
    m_nameWatcher->setWatchedServices({QString::fromLatin1(kKdeWatcher),
                                       QString::fromLatin1(kFdoWatcher)});
    m_nameWatcher->setWatchMode(QDBusServiceWatcher::WatchForOwnerChange);
    connect(m_nameWatcher, &QDBusServiceWatcher::serviceOwnerChanged, this,
            [this](const QString &name, const QString &oldOwner, const QString &newOwner) {
        Q_UNUSED(oldOwner);
        if (m_ownsWatcher)
            return;

        if (name == QString::fromLatin1(kKdeWatcher)) {
            if (!newOwner.isEmpty() && newOwner != m_bus.baseService()) {
                enterClientMode(QString::fromLatin1(kKdeWatcher),
                                QString::fromLatin1(kKdeInterface));
            } else if (newOwner.isEmpty() && m_remoteWatcher == QString::fromLatin1(kKdeWatcher)) {
                leaveClientMode();
                requestName(QString::fromLatin1(kKdeWatcher), true);
                if (m_ownsWatcher)
                    requestName(QString::fromLatin1(kFdoWatcher), false);
            }
            return;
        }

        if (!newOwner.isEmpty() && newOwner != m_bus.baseService()) {
            if (m_remoteWatcher.isEmpty())
                enterClientMode(QString::fromLatin1(kFdoWatcher),
                                QString::fromLatin1(kFdoInterface));
        } else if (newOwner.isEmpty() && m_remoteWatcher == QString::fromLatin1(kFdoWatcher)) {
            leaveClientMode();
            requestName(QString::fromLatin1(kKdeWatcher), true);
            if (m_ownsWatcher)
                requestName(QString::fromLatin1(kFdoWatcher), false);
        }
    });

    requestName(QString::fromLatin1(kKdeWatcher), true);
    if (m_ownsWatcher)
        requestName(QString::fromLatin1(kFdoWatcher), false);

    m_hostName = QStringLiteral("org.kde.StatusNotifierHost-%1")
                     .arg(QCoreApplication::applicationPid());
    const QDBusReply<QDBusConnectionInterface::RegisterServiceReply> hostReply =
        m_bus.interface()->registerService(
            m_hostName, QDBusConnectionInterface::DontQueueService,
            QDBusConnectionInterface::DontAllowReplacement);
    m_ownsHostName = hostReply.isValid()
        && hostReply.value() == QDBusConnectionInterface::ServiceRegistered;
    registerHost(m_ownsHostName ? m_hostName : m_bus.baseService());
}

SniWatcher::~SniWatcher()
{
    m_relay->stop();
    m_bus.unregisterObject(QString::fromLatin1(kObjectPath));
    if (m_ownsWatcher)
        m_bus.unregisterService(QString::fromLatin1(kKdeWatcher));
    if (m_ownsFdoWatcher)
        m_bus.unregisterService(QString::fromLatin1(kFdoWatcher));
    if (m_ownsHostName)
        m_bus.unregisterService(m_hostName);
}

QStringList SniWatcher::items() const
{
    return m_items;
}

bool SniWatcher::hostRegistered() const
{
    return m_hostRegistered;
}

void SniWatcher::registerItem(const QString &serviceOrPath)
{
    QString key = serviceOrPath;
    QString owner = serviceOrPath;

    if (serviceOrPath.startsWith(QLatin1Char('/'))) {
        owner = calledFromDBus() ? message().service() : QString();
        if (owner.isEmpty())
            return;
        key = owner + serviceOrPath;
    } else {
        const qsizetype slash = serviceOrPath.indexOf(QLatin1Char('/'));
        if (slash > 0)
            owner = serviceOrPath.left(slash);
    }

    if (key.isEmpty())
        return;
    addItem(key, owner);
}

void SniWatcher::registerHost(const QString &service)
{
    if (service.isEmpty() || m_hosts.contains(service))
        return;

    m_hosts.insert(service);
    m_serviceWatcher->addWatchedService(service);
    if (!m_hostRegistered) {
        m_hostRegistered = true;
        emit hostChanged();
        emit itemsChanged();
    }
}

void SniWatcher::onOwnerLeft(const QString &service)
{
    QStringList remove;
    for (const QString &key : std::as_const(m_items)) {
        if (m_itemOwners.value(key) == service || key == service || key.startsWith(service + QLatin1Char('/')))
            remove.append(key);
    }
    const bool hadItemsChanged = removeItems(remove, false);

    const bool hostRemoved = m_hosts.remove(service) > 0;
    if (hostRemoved) {
        m_hostRegistered = !m_hosts.isEmpty();
        emit hostChanged();
    }
    if (hadItemsChanged || hostRemoved)
        emit itemsChanged();

    bool stillWatched = m_hosts.contains(service);
    if (!stillWatched) {
        for (auto it = m_itemOwners.cbegin(); it != m_itemOwners.cend(); ++it) {
            if (it.value() == service) {
                stillWatched = true;
                break;
            }
        }
    }
    if (!stillWatched)
        m_serviceWatcher->removeWatchedService(service);
}

void SniWatcher::requestName(const QString &name, bool isWatcherName)
{
    if (!m_bus.isConnected() || !m_bus.interface()) {
        if (name == QString::fromLatin1(kKdeWatcher))
            m_ownsWatcher = false;
        else if (name == QString::fromLatin1(kFdoWatcher))
            m_ownsFdoWatcher = false;
        return;
    }

    const QDBusReply<QDBusConnectionInterface::RegisterServiceReply> reply =
        m_bus.interface()->registerService(
            name, QDBusConnectionInterface::DontQueueService,
            QDBusConnectionInterface::DontAllowReplacement);
    const bool primary = reply.isValid()
        && reply.value() == QDBusConnectionInterface::ServiceRegistered;

    if (name == QString::fromLatin1(kKdeWatcher))
        m_ownsWatcher = primary;
    else if (name == QString::fromLatin1(kFdoWatcher))
        m_ownsFdoWatcher = primary;

    if (primary && isWatcherName)
        becameOwner();
    else if (!primary && name == QString::fromLatin1(kKdeWatcher))
        enterClientMode(QString::fromLatin1(kKdeWatcher), QString::fromLatin1(kKdeInterface));
}

void SniWatcher::becameOwner()
{
    leaveClientMode();
}

void SniWatcher::enterClientMode(const QString &service, const QString &interfaceName)
{
    if (m_ownsWatcher || !m_relay)
        return;
    if (m_remoteWatcher == service && m_clientMode)
        return;

    leaveClientMode();
    m_remoteWatcher = service;
    m_clientMode = true;
    m_relay->watch(service, interfaceName);
}

void SniWatcher::leaveClientMode()
{
    if (m_relay)
        m_relay->stop();
    m_remoteWatcher.clear();
    m_clientMode = false;
}

void SniWatcher::reconcileWatcherOwner()
{
    if (m_ownsWatcher)
        return;
    enterClientMode(QString::fromLatin1(kKdeWatcher), QString::fromLatin1(kKdeInterface));
}

void SniWatcher::addItem(const QString &key, const QString &owner)
{
    if (key.isEmpty() || m_items.contains(key))
        return;

    m_items.append(key);
    m_itemOwners.insert(key, owner);
    if (!owner.isEmpty())
        m_serviceWatcher->addWatchedService(owner);
    emit itemRegistered(key);
    emit itemsChanged();
}

bool SniWatcher::removeItems(const QStringList &keys, bool notify)
{
    bool changed = false;
    for (const QString &key : keys) {
        if (!m_items.removeOne(key))
            continue;
        const QString owner = m_itemOwners.take(key);
        if (!owner.isEmpty()) {
            bool stillWatched = m_hosts.contains(owner);
            if (!stillWatched) {
                for (auto it = m_itemOwners.cbegin(); it != m_itemOwners.cend(); ++it) {
                    if (it.value() == owner) {
                        stillWatched = true;
                        break;
                    }
                }
            }
            if (!stillWatched)
                m_serviceWatcher->removeWatchedService(owner);
        }
        emit itemUnregistered(key);
        changed = true;
    }
    if (changed && notify)
        emit itemsChanged();
    return changed;
}
