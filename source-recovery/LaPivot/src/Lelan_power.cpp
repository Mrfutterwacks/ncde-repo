// Lelan — power: battery (UPower DisplayDevice + Sentinel), power profile (power-profiles-daemon).
//
// Rebuilt from oracle: subscribeToUPower (+lambda), onBatteryPropertiesChanged,
// onSentinelBatteryStateChanged, subscribeToPowerProfiles, onPowerProfilesPropertiesChanged,
// battery/powerProfile/batteryPercent/batteryCharging/hasBattery getters.
//
// DEFECTS FIXED vs oracle:
//  Z3 every battery signal re-emitted batteryChanged/powerChanged even when nothing changed.
//     Settings::applyPowerSettings listens to batteryChanged and spawns 2-3 `xset` each time —
//     measured ~60 xset/min on this laptop (2026-09-30). Now: emit only when a value changed;
//     SetPowerProfile only when AC/battery actually flips.
//  Z5 the current power profile was never read at startup (only PropertiesChanged was
//     subscribed), so lelan.powerProfile was "" and power-saver was ignored until the user
//     switched profiles. Now: Get ActiveProfile once when subscribing.
#include "Lelan.h"
#include "AnimPolicy.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QtLogging>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kUPower = QStringLiteral("org.freedesktop.UPower");
const QString kDisplayDevice = QStringLiteral("/org/freedesktop/UPower/devices/DisplayDevice");
const QString kUPowerDevice = QStringLiteral("org.freedesktop.UPower.Device");
const QString kPpd = QStringLiteral("net.hadess.PowerProfiles");
const QString kPpdPath = QStringLiteral("/net/hadess/PowerProfiles");
constexpr uint kUPowerDischarging = 2;
constexpr uint kUPowerCharging = 1;
} // namespace

// ---- getters ----------------------------------------------------------------------------------

QVariantMap Lelan::battery() const { return m_battery; }
QString Lelan::powerProfile() const { return m_powerProfile; }
double Lelan::batteryPercent() const { return m_battery.value(QStringLiteral("percentage")).toDouble(); }
bool Lelan::batteryCharging() const { return m_battery.value(QStringLiteral("state")).toUInt() == kUPowerCharging; }
bool Lelan::hasBattery() const { return !m_battery.isEmpty(); }

// ---- battery ----------------------------------------------------------------------------------

// Merge battery fields (already in Lelan's lower-case keys) and an optional AC/battery verdict;
// emit only on real change.
void Lelan::applyBattery(const QVariantMap &changes, bool fromSentinel)
{
    bool changed = false;
    for (auto it = changes.cbegin(); it != changes.cend(); ++it) {
        if (it.key() == QLatin1String("onBattery"))
            continue;
        if (m_battery.value(it.key()) != it.value()) {
            m_battery.insert(it.key(), it.value());
            changed = true;
        }
    }
    const bool acFlip = changes.contains(QStringLiteral("onBattery"))
                        && changes.value(QStringLiteral("onBattery")).toBool() != m_onBattery;
    if (acFlip)
        m_onBattery = !m_onBattery;
    if (changed || acFlip) {
        emit batteryChanged();
        emit powerChanged();
        recomputeAnimLevel();
    }
    if (fromSentinel)
        requestSentinelPowerProfile();
}

void Lelan::requestSentinelPowerProfile()
{
    // Sentinel applies cpufreq governor / EPP / dirty_ratio and re-asserts GameMode (zen.md: one
    // writer). Only when AC/battery actually changed — the percentage is irrelevant to it.
    if (!m_useSentinel)
        return;
    if (m_sentPowerProfileValid && m_sentPowerProfileOnBattery == m_onBattery)
        return;
    m_sentPowerProfileValid = true;
    m_sentPowerProfileOnBattery = m_onBattery;
    callSentinel(QStringLiteral("SetPowerProfile"), {m_onBattery});
}

void Lelan::subscribeToUPower()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusMessage getAll = QDBusMessage::createMethodCall(kUPower, kDisplayDevice, kFdProps, QStringLiteral("GetAll"));
    getAll << kUPowerDevice;
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(getAll), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] UPower GetAll failed:" << reply.error().name() << reply.error().message();
            return;
        }
        const QVariantMap props = reply.value();
        const uint state = props.value(QStringLiteral("State")).toUInt();
        applyBattery({{QStringLiteral("percentage"), props.value(QStringLiteral("Percentage"))},
                      {QStringLiteral("state"), props.value(QStringLiteral("State"))},
                      {QStringLiteral("timeToEmpty"), props.value(QStringLiteral("TimeToEmpty"))},
                      {QStringLiteral("onBattery"), state == kUPowerDischarging}},
                     false);
    });
    bus.connect(kUPower, kDisplayDevice, kFdProps, QStringLiteral("PropertiesChanged"), this,
                SLOT(onBatteryPropertiesChanged(QString,QVariantMap,QStringList)));
}

void Lelan::onBatteryPropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &)
{
    QVariantMap c;
    if (changed.contains(QStringLiteral("Percentage")))
        c.insert(QStringLiteral("percentage"), changed.value(QStringLiteral("Percentage")));
    if (changed.contains(QStringLiteral("State"))) {
        c.insert(QStringLiteral("state"), changed.value(QStringLiteral("State")));
        c.insert(QStringLiteral("onBattery"), changed.value(QStringLiteral("State")).toUInt() == kUPowerDischarging);
    }
    if (!c.isEmpty())
        applyBattery(c, false);
}

void Lelan::onSentinelBatteryStateChanged(bool onBattery, int percentage)
{
    applyBattery({{QStringLiteral("percentage"), percentage}, {QStringLiteral("onBattery"), onBattery}}, true);
}

// ---- power profile ----------------------------------------------------------------------------

void Lelan::subscribeToPowerProfiles()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect(kPpd, kPpdPath, kFdProps, QStringLiteral("PropertiesChanged"), this,
                SLOT(onPowerProfilesPropertiesChanged(QString,QVariantMap,QStringList)));
    // Z5: read the profile that is active right now, not only future changes.
    QDBusMessage get = QDBusMessage::createMethodCall(kPpd, kPpdPath, kFdProps, QStringLiteral("Get"));
    get << kPpd << QStringLiteral("ActiveProfile");
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(get), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusVariant> reply = *w;
        w->deleteLater();
        if (!reply.isError())
            onPowerProfilesPropertiesChanged(kPpd, {{QStringLiteral("ActiveProfile"), reply.value().variant()}}, {});
    });
}

void Lelan::onPowerProfilesPropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &)
{
    if (!changed.contains(QStringLiteral("ActiveProfile")))
        return;
    const QString profile = changed.value(QStringLiteral("ActiveProfile")).toString();
    if (profile == m_powerProfile)
        return;
    m_powerProfile = profile;
    emit powerProfileChanged();
    emit powerChanged();
    if (m_animPolicy)
        m_animPolicy->setLowPowerProfile(profile == QLatin1String("power-saver"));
}
