// Lelan — session: logind (active, lock, sleep/wake, VT), org.freedesktop.ScreenSaver, and the
// service-restart dispatcher that re-arms every subscription when its owner comes back.
//
// Rebuilt from oracle: subscribeToLogind (+lambda), onSessionActiveChangedSlot, onSessionLock,
// onSessionUnlock, onPrepareForSleep, subscribeToScreenSaver, onScreenSaverActivated,
// onNameOwnerChanged, onSystemNameOwnerChanged, sessionActive/vtActive/screensaver getters.
// Spec: lelan.md §4 (logind Active/LockedHint, Lock/Unlock, VT for the recovery handoff,
// PrepareForSleep re-arms watchers on resume).
//
// DEFECTS FIXED vs oracle:
//  S2 at startup only VTNr was read; the session's current Active and LockedHint were never
//     fetched, so lelan.sessionActive started false and a login into an already-locked session
//     was not seen until the next change. Now GetAll on the session once when subscribing.
//  S3 lock/active/screensaver re-emitted on every signal even when nothing changed.
#include "Lelan.h"
#include "lelan_dbus_relay.h"
#include "AnimPolicy.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QtLogging>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kLogin1 = QStringLiteral("org.freedesktop.login1");
const QString kSelf = QStringLiteral("/org/freedesktop/login1/session/self");
const QString kSessionIface = QStringLiteral("org.freedesktop.login1.Session");
} // namespace

bool Lelan::sessionActive() const { return m_sessionActive; }
int Lelan::vtActive() const { return m_vtActive; }
bool Lelan::screensaver() const { return m_screensaver; }

void Lelan::subscribeToLogind()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect(kLogin1, kSelf, kFdProps, QStringLiteral("PropertiesChanged"), this,
                SLOT(onSessionActiveChangedSlot(QString,QVariantMap,QStringList)));
    bus.connect(kLogin1, kSelf, kSessionIface, QStringLiteral("Lock"), this, SLOT(onSessionLock()));
    bus.connect(kLogin1, kSelf, kSessionIface, QStringLiteral("Unlock"), this, SLOT(onSessionUnlock()));
    bus.connect(kLogin1, QStringLiteral("/org/freedesktop/login1"), QStringLiteral("org.freedesktop.login1.Manager"),
                QStringLiteral("PrepareForSleep"), this, SLOT(onPrepareForSleep(bool)));

    // S4: the lid. logind is told to ignore it (logind.conf.d HandleLidSwitch=ignore) so that the Power tab's
    // "When the lid closes" choice decides — but nothing listened, so closing the lid did nothing at all.
    // LidClosed emits change on the Manager; Settings acts on lidClosedChanged.
    if (!m_lidRelay) {
        m_lidRelay = new PropsRelay(this, [this](const QString &, const QString &iface, const QVariantMap &changed) {
            if (iface == QLatin1String("org.freedesktop.login1.Manager") && changed.contains(QStringLiteral("LidClosed")))
                setLidClosed(changed.value(QStringLiteral("LidClosed")).toBool());
        });
        bus.connect(kLogin1, QStringLiteral("/org/freedesktop/login1"), kFdProps, QStringLiteral("PropertiesChanged"),
                    m_lidRelay, SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    }
    QDBusMessage lid = QDBusMessage::createMethodCall(kLogin1, QStringLiteral("/org/freedesktop/login1"), kFdProps, QStringLiteral("Get"));
    lid << QStringLiteral("org.freedesktop.login1.Manager") << QStringLiteral("LidClosed");
    auto *lidWatch = new QDBusPendingCallWatcher(bus.asyncCall(lid), this);
    connect(lidWatch, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusVariant> reply = *w;
        w->deleteLater();
        if (!reply.isError())
            m_lidClosed = reply.value().variant().toBool();              // the state at start: no action
    });

    // S2: the session's state now, not only future changes (VTNr, Active, LockedHint in one call)
    QDBusMessage getAll = QDBusMessage::createMethodCall(kLogin1, kSelf, kFdProps, QStringLiteral("GetAll"));
    getAll << kSessionIface;
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(getAll), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] logind session GetAll failed:" << reply.error().name() << reply.error().message();
            return;
        }
        const QVariantMap props = reply.value();
        const int vt = props.value(QStringLiteral("VTNr")).toInt();
        if (vt != m_vtActive) {
            m_vtActive = vt;
            emit vtActiveChanged();
        }
        onSessionActiveChangedSlot(kSessionIface, props, {});
    });
}

void Lelan::onSessionActiveChangedSlot(const QString &, const QVariantMap &changed, const QStringList &)
{
    if (changed.contains(QStringLiteral("Active"))) {
        const bool active = changed.value(QStringLiteral("Active")).toBool();
        if (active != m_sessionActive) {
            m_sessionActive = active;
            emit onSessionActiveChanged();
        }
        if (m_animPolicy)
            m_animPolicy->onVtActiveChanged(m_sessionActive);
    }
    if (changed.contains(QStringLiteral("LockedHint")))
        setLocked(changed.value(QStringLiteral("LockedHint")).toBool());
}

bool Lelan::lidClosed() const { return m_lidClosed; }

void Lelan::setLidClosed(bool closed)
{
    if (closed == m_lidClosed)
        return;
    m_lidClosed = closed;
    emit lidClosedChanged(closed);
}

void Lelan::onSessionLock() { setLocked(true); }
void Lelan::onSessionUnlock() { setLocked(false); }

void Lelan::setLocked(bool locked)
{
    if (m_animPolicy)
        locked ? m_animPolicy->onSessionLocked() : m_animPolicy->onSessionUnlocked();
    if (locked == m_screensaver)
        return;                                      // S3
    m_screensaver = locked;
    emit screensaverChanged();
}

void Lelan::onPrepareForSleep(bool before)
{
    if (before) {
        emit leanSleeping();
        return;
    }
    // resume: sockets and players may have gone away while suspended — re-arm them
    subscribeToNetworkManager();
    subscribeToAudio();
    subscribeToPlayers();
    retryFallbackSink();
    emit leanWaking();
}

void Lelan::subscribeToScreenSaver()
{
    QDBusConnection::sessionBus().connect(QStringLiteral("org.freedesktop.ScreenSaver"),
        QStringLiteral("/org/freedesktop/ScreenSaver"), QStringLiteral("org.freedesktop.ScreenSaver"),
        QStringLiteral("ActiveChanged"), this, SLOT(onScreenSaverActivated(bool)));
}

void Lelan::onScreenSaverActivated(bool active)
{
    if (m_animPolicy)
        m_animPolicy->onScreenSaverActivated(active);
    if (active == m_screensaver)
        return;
    m_screensaver = active;
    emit screensaverChanged();
}

// A service (re)appeared or vanished on a bus: re-arm the one subscription it owns.
void Lelan::onNameOwnerChanged(const QString &name, const QString &, const QString &newOwner)
{
    static const QString mpris = QStringLiteral("org.mpris.MediaPlayer2.");
    if (name == QLatin1String("org.kde.StatusNotifierWatcher")) {
        if (!newOwner.isEmpty())
            subscribeTrayOwner();
        else {
            m_trayItems.clear();
            m_registeredTrayItems.clear();
            if (!m_tray.isEmpty()) {
                m_tray.clear();
                emit trayChanged();
            }
        }
        return;
    }
    if (name == QLatin1String("org.freedesktop.Accounts") && newOwner.isEmpty()) {
        ++m_usersGeneration;
        m_userPaths.clear();
        m_usersBeingCreated.clear();
        m_pendingUserPasswords.clear();
        if (!m_users.isEmpty()) {
            m_users.clear();
            emit usersChanged();
        }
        return;
    }
    if (newOwner.isEmpty()) {
        if (name.startsWith(mpris))
            removePlayer(name);
        return;
    }
    if (name.startsWith(mpris)) { subscribeToPlayers(); return; }
    const struct { const char *service; void (Lelan::*resubscribe)(); } table[] = {
        {"org.freedesktop.UPower", &Lelan::subscribeToUPower},
        {"org.freedesktop.portal.Desktop", &Lelan::subscribeToPortalSettings},
        {"org.ncde.KickassGuard", &Lelan::subscribeToKickassGuard},
        {"org.freedesktop.NetworkManager", &Lelan::subscribeToNetworkManager},
        {"org.bluez", &Lelan::subscribeToBlueZ},
        {"org.freedesktop.UDisks2", &Lelan::subscribeToUDisks2},
        {"org.freedesktop.GeoClue2", &Lelan::subscribeToGeoClue},
        {"org.freedesktop.timedate1", &Lelan::subscribeToTimeDate},
        {"org.freedesktop.hostname1", &Lelan::subscribeToHostnameLocale},
        {"org.freedesktop.locale1", &Lelan::subscribeToHostnameLocale},
        {"io.ncde.Sentinel", &Lelan::subscribeToSentinel},
        {"org.freedesktop.login1", &Lelan::subscribeToLogind},
        {"org.freedesktop.ScreenSaver", &Lelan::subscribeToScreenSaver},
        {"org.freedesktop.PackageKit", &Lelan::subscribeToPackageKit},
        {"org.freedesktop.Accounts", &Lelan::subscribeToAccountsService},
        {"net.hadess.PowerProfiles", &Lelan::subscribeToPowerProfiles},
    };
    for (const auto &e : table) {
        if (name == QLatin1String(e.service)) {
            (this->*e.resubscribe)();
            if (name == QLatin1String("org.freedesktop.NetworkManager"))
                subscribeToWifi();
            return;
        }
    }
}

void Lelan::onSystemNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOwner)
{
    onNameOwnerChanged(name, oldOwner, newOwner);
}
