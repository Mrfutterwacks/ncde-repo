// Lelan — PackageKit: asynchronous update discovery and an immutable QML snapshot.
// Rebuilt from oracle: subscribeToPackageKit, fetchPackageKitUpdates, onPackageKitUpdatesChanged,
// onPackageKitUpdatesPackage, onPackageKitUpdatesFinished, updates().
// Spec: lelan.md §4/§5: UpdatesChanged -> GetUpdates(as) -> transaction Package signals -> updates.
//
// DEFECTS FIXED vs oracle:
// 1. The transaction's Package and Finished signals are collected into lelan.updates. Flow is the
//    oracle's: CreateTransaction -> Transaction.GetUpdates(t 0). An earlier rebuild called a
//    non-existent root GetUpdates(as) and always failed; corrected 2026-10-01.
// 2. Repeated UpdatesChanged requests supersede older transactions; stale async replies cannot
//    publish an obsolete package list.
#include "Lelan.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QtLogging>

#include <utility>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kPackageKit = QStringLiteral("org.freedesktop.PackageKit");
const QString kPackageKitPath = QStringLiteral("/org/freedesktop/PackageKit");
const QString kPackageKitIface = QStringLiteral("org.freedesktop.PackageKit");
const QString kTransactionIface = QStringLiteral("org.freedesktop.PackageKit.Transaction");
} // namespace

QVariantMap Lelan::updates() const { return m_updates; }

void Lelan::subscribeToPackageKit()
{
    auto bus = QDBusConnection::systemBus();
    bus.connect(kPackageKit, kPackageKitPath, kPackageKitIface, QStringLiteral("UpdatesChanged"),
                this, SLOT(onPackageKitUpdatesChanged()));
    fetchPackageKitUpdates();
}

void Lelan::fetchPackageKitUpdates()
{
    const quint64 generation = ++m_updatesGeneration;
    m_updatePackages.clear();
    if (!m_updateTransaction.isEmpty()) {
        auto bus = QDBusConnection::systemBus();
        bus.disconnect(kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("Package"),
                       this, SLOT(onPackageKitUpdatesPackage(uint,QString,QString)));
        bus.disconnect(kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("Finished"),
                       this, SLOT(onPackageKitUpdatesFinished(uint,uint)));
        QDBusMessage cancel = QDBusMessage::createMethodCall(
            kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("Cancel"));
        bus.asyncCall(cancel);
        m_updateTransaction.clear();
    }

    // Oracle flow (decomp/Lelan.c fetchPackageKitUpdates + its lambda): CreateTransaction on the
    // root object, connect Package/Finished on the new transaction, then Transaction.GetUpdates(t 0).
    // The root interface has no GetUpdates: calling it there failed with UnknownMethod every time.
    QDBusMessage create = QDBusMessage::createMethodCall(
        kPackageKit, kPackageKitPath, kPackageKitIface, QStringLiteral("CreateTransaction"));
    auto bus = QDBusConnection::systemBus();
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(create), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, generation, bus](QDBusPendingCallWatcher *w) mutable {
        QDBusPendingReply<QDBusObjectPath> reply = *w;
        w->deleteLater();
        if (generation != m_updatesGeneration)
            return;
        if (reply.isError()) {
            qWarning() << "[lelan] PackageKit CreateTransaction failed:"
                       << reply.error().name() << reply.error().message();
            const QVariantMap next{{QStringLiteral("packages"), QVariantList{}},
                                   {QStringLiteral("count"), 0},
                                   {QStringLiteral("error"), reply.error().message()}};
            if (next != m_updates) {
                m_updates = next;
                emit packageStateChanged();
                emit updatesChanged();
            }
            return;
        }

        m_updateTransaction = reply.value().path();
        bus.connect(kPackageKit, m_updateTransaction, kTransactionIface,
                    QStringLiteral("Package"), this,
                    SLOT(onPackageKitUpdatesPackage(uint,QString,QString)));
        bus.connect(kPackageKit, m_updateTransaction, kTransactionIface,
                    QStringLiteral("Finished"), this,
                    SLOT(onPackageKitUpdatesFinished(uint,uint)));
        QDBusMessage getUpdates = QDBusMessage::createMethodCall(
            kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("GetUpdates"));
        getUpdates << QVariant::fromValue<qulonglong>(0);      // filter bitfield: none
        bus.asyncCall(getUpdates);
    });
}

void Lelan::onPackageKitUpdatesChanged()
{
    fetchPackageKitUpdates();
}

void Lelan::onPackageKitUpdatesPackage(uint info, const QString &packageId, const QString &summary)
{
    QVariantMap package{{QStringLiteral("id"), packageId},
                        {QStringLiteral("summary"), summary},
                        {QStringLiteral("info"), info}};
    for (const QVariant &existing : std::as_const(m_updatePackages)) {
        if (existing.toMap().value(QStringLiteral("id")).toString() == packageId)
            return;
    }
    m_updatePackages.append(package);
}

void Lelan::onPackageKitUpdatesFinished(uint exit, uint runtime)
{
    Q_UNUSED(runtime);
    auto bus = QDBusConnection::systemBus();
    if (!m_updateTransaction.isEmpty()) {
        bus.disconnect(kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("Package"),
                       this, SLOT(onPackageKitUpdatesPackage(uint,QString,QString)));
        bus.disconnect(kPackageKit, m_updateTransaction, kTransactionIface, QStringLiteral("Finished"),
                       this, SLOT(onPackageKitUpdatesFinished(uint,uint)));
    }
    m_updateTransaction.clear();
    const QVariantMap next{{QStringLiteral("packages"), m_updatePackages},
                           {QStringLiteral("count"), m_updatePackages.size()},
                           {QStringLiteral("error"), QString{}}};
    if (next == m_updates)
        return;
    m_updates = next;
    if (exit != 0)
        m_updates.insert(QStringLiteral("exit"), exit);
    emit packageStateChanged();
    emit updatesChanged();
}
