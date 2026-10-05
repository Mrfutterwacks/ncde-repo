// Lelan — KickassGuard: security status, threats, blocks.
// Rebuilt from oracle: subscribeToKickassGuard, onKickassStatusChanged, onKickassThreatBlocked,
// onKickassThreatBehavioral, onKickassSiteBlocked, onKickassNetworkAlert, kickass() getter.
// Spec: lelan.md §4 (KickassGuard).
#include "Lelan.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QtLogging>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kKickass = QStringLiteral("org.ncde.KickassGuard");
const QString kKickassPath = QStringLiteral("/org/ncde/KickassGuard");
} // namespace

QVariantMap Lelan::kickass() const { return m_kickass; }

void Lelan::subscribeToKickassGuard()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect(kKickass, kKickassPath, kFdProps, QStringLiteral("PropertiesChanged"), this,
                SLOT(onPropertiesChanged(QString,QVariantMap,QStringList)));
    bus.connect(kKickass, kKickassPath, kKickass, QStringLiteral("StatusChanged"), this,
                SLOT(onKickassStatusChanged(bool,int)));
    bus.connect(kKickass, kKickassPath, kKickass, QStringLiteral("ThreatBlocked"), this,
                SLOT(onKickassThreatBlocked(QString,QString,int)));
    bus.connect(kKickass, kKickassPath, kKickass, QStringLiteral("ThreatBehavioral"), this,
                SLOT(onKickassThreatBehavioral(QString,QString,QString)));
    bus.connect(kKickass, kKickassPath, kKickass, QStringLiteral("SiteBlocked"), this,
                SLOT(onKickassSiteBlocked(QString,QString)));
    bus.connect(kKickass, kKickassPath, kKickass, QStringLiteral("NetworkAlert"), this,
                SLOT(onKickassNetworkAlert(QString,QString)));

    // Read initial state
    QDBusMessage getAll = QDBusMessage::createMethodCall(kKickass, kKickassPath, kFdProps, QStringLiteral("GetAll"));
    getAll << kKickass;
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(getAll), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] KickassGuard GetAll failed:" << reply.error().name() << reply.error().message();
            return;
        }
        onPropertiesChanged(kKickass, reply.value(), {});
    });
}

void Lelan::onPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
{
    if (iface == kKickass) {
        if (changed == m_kickass)
            return;
        m_kickass = changed;
        emit kickassChanged();
        emit kickassStatusChanged();            // oracle also emitted this
        return;
    }
    if (iface == QLatin1String("org.mpris.MediaPlayer2.Player") && !m_activePlayer.isEmpty())
        applyPlayerProps(m_activePlayer, changed);
}

void Lelan::onKickassStatusChanged(bool armed, int level)
{
    QVariantMap m{{QStringLiteral("armed"), armed}, {QStringLiteral("level"), level}};
    if (m == m_kickass)
        return;
    m_kickass = m;
    emit kickassChanged();
    emit kickassStatusChanged();
}

void Lelan::onKickassThreatBlocked(const QString &app, const QString &detail, int severity)
{
    emit kickassThreatBlocked(app, detail, severity);
}

void Lelan::onKickassThreatBehavioral(const QString &subject, const QString &detail, const QString &kind)
{
    emit kickassThreatBehavioral(subject, detail, kind);
}

void Lelan::onKickassSiteBlocked(const QString &domain, const QString &detail)
{
    emit kickassSiteBlocked(domain, detail);
}

void Lelan::onKickassNetworkAlert(const QString &src, const QString &detail)
{
    emit kickassNetworkAlert(src, detail);
}