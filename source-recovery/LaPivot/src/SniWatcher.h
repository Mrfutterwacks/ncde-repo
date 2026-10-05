// SniWatcher — NCDE's StatusNotifierWatcher (the SNI tray registry) + LaPivot's own host registration.
// Rebuilt from oracle: decomp/SniWatcher.c (ctor, dtor, items, hostRegistered, registerItem,
//   registerHost, onOwnerLeft + 4 signals). Created by Lelan::subscribeTrayOwner (Lelan ctor);
//   Lelan (src/Lelan_tray.cpp, lelan group) owns per-item reading/rendering: it reads items() on
//   itemsChanged and GetAll's each org.kde.StatusNotifierItem. SniWatcher owns ONLY the registry:
//   who is registered, who left, which host exists. One owner per service (lelan.md).
// Spec: docs/lelan-research-findings.md §4, docs/lelan.md (subscribeTrayOwner = SNI), digest §2
//   (TrayWatcher -> SniWatcher + StatusNotifierWatcherAdaptor, D3).
// See SniWatcher.cpp for the DEFECTS FIXED list.
#pragma once

#include <QDBusConnection>
#include <QDBusContext>
#include <QHash>
#include <QObject>
#include <QSet>
#include <QStringList>

class QDBusServiceWatcher;
class StatusNotifierWatcherAdaptor;
class FdoStatusNotifierWatcherAdaptor;
class QDBusPendingCallWatcher;

class SniWatcher;

class SniForeignWatcherRelay : public QObject
{
    Q_OBJECT

public:
    explicit SniForeignWatcherRelay(SniWatcher *watcher, QObject *parent = nullptr);
    void watch(const QString &service, const QString &interfaceName);
    void stop();

private slots:
    void onItemRegistered(const QString &service);
    void onItemUnregistered(const QString &service);
    void onInitialItemsReady(QDBusPendingCallWatcher *call);

private:
    void addItem(const QString &service);
    void removeItem(const QString &service);
    void requestItems();

    SniWatcher *m_watcher = nullptr;
    QDBusConnection m_bus;
    QString m_service;
    QString m_interface;
    QStringList m_items;
    quint64 m_generation = 0;
};

class SniWatcher : public QObject, protected QDBusContext
{
    Q_OBJECT

public:
    explicit SniWatcher(QObject *parent = nullptr);
    ~SniWatcher() override;

    QStringList items() const;           // "service" or "service/object/path" (oracle form)
    bool hostRegistered() const;
    void registerItem(const QString &service);   // adaptor RegisterStatusNotifierItem
    void registerHost(const QString &service);   // adaptor RegisterStatusNotifierHost

    // ---- additions (plain C++, not in the metaobject) ----
    bool ownsWatcherName() const { return m_ownsWatcher; }   // we hold org.kde.StatusNotifierWatcher
    QString hostServiceName() const { return m_hostName; }

signals:
    void itemRegistered(const QString &service);
    void itemUnregistered(const QString &service);
    void hostChanged();
    void itemsChanged();

private slots:
    void onOwnerLeft(const QString &service);

private:
    friend class SniForeignWatcherRelay;
    void requestName(const QString &name, bool isWatcherName);
    void becameOwner();
    void enterClientMode(const QString &service, const QString &interfaceName);
    void leaveClientMode();
    void reconcileWatcherOwner();
    void addItem(const QString &key, const QString &owner);
    bool removeItems(const QStringList &keys, bool notify = true);

    QDBusConnection m_bus;
    QStringList m_items;                              // oracle +0x18
    bool m_ownsWatcher = false;                       // oracle +0x30
    bool m_hostRegistered = false;                    // oracle +0x31 (LaPivot itself hosts)
    QDBusServiceWatcher *m_serviceWatcher = nullptr;  // oracle +0x38 (item/host owners)
    StatusNotifierWatcherAdaptor *m_adaptor = nullptr;// oracle +0x40
    FdoStatusNotifierWatcherAdaptor *m_fdoAdaptor = nullptr;
    QDBusServiceWatcher *m_nameWatcher = nullptr;     // watcher name owners
    SniForeignWatcherRelay *m_relay = nullptr;        // parent-owned client-mode item mirror
    QSet<QString> m_hosts;                            // external hosts that registered
    QHash<QString, QString> m_itemOwners;             // registered key -> unique bus owner
    QString m_hostName;                               // org.kde.StatusNotifierHost-<pid>
    QString m_remoteWatcher;
    bool m_ownsFdoWatcher = false;
    bool m_ownsHostName = false;
    bool m_clientMode = false;
};
