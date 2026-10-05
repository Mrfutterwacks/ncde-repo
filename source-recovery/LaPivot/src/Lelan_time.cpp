// Lelan — time, place and host: timedate1 (timezone, NTP, clock jumps), hostname1, locale1,
// GeoClue2 location, sunrise/sunset and the "night" flag (night light, Salon sky).
//
// Rebuilt from oracle: subscribeToTimeDate, refreshLocation (+lambda), onTimedate1PropertiesChanged,
// setTimezone, setNtp, subscribeToHostnameLocale, onHostname1PropertiesChanged,
// onLocale1PropertiesChanged, subscribeToGeoClue (+lambda), onGeoClue2Location (+lambda),
// scheduleNightLightEvents (+lambda), (anonymous)::computeSunTimes, and the getters.
//
// DEFECTS FIXED vs oracle:
//  T1 hostname1/locale1 were only subscribed for changes, never read — lelan.hostname and
//     lelan.locale stayed "" for the whole session. Now read once when subscribing.
//  T5 night light: a one-shot timer flipped "night" at the next sunrise/sunset and never scheduled
//     the transition after it (and QTimer does not count time spent suspended). Now the flag is
//     re-derived from the stored sunrise/sunset on every coalesced (once-a-minute) tick.
//  T7 RequestedAccuracyLevel was sent as int32; GeoClue's property is uint32 and REJECTS it
//     (measured 2026-09-30: "Expected type 'u' but got 'i'"), leaving accuracy at NONE, so GeoClue
//     never delivered a location. Now uint32 (4 = city).
#include "Lelan.h"

#include <QDateTime>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QTime>
#include <QtLogging>

#include <cmath>

namespace {
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QString kTimedate = QStringLiteral("org.freedesktop.timedate1");
const QString kTimedatePath = QStringLiteral("/org/freedesktop/timedate1");
const QString kGeoClue = QStringLiteral("org.freedesktop.GeoClue2");
constexpr uint kAccuracyCity = 4;

#include "lelan_suntimes.inc"   // sunTimes(): the oracle's sunrise equation
} // namespace

bool lelanIsNight(double sunset, double sunrise, double nowHours)   // exposed for tests
{
    if (sunset <= sunrise)
        return !(nowHours < sunset || sunrise <= nowHours);
    return sunset <= nowHours || nowHours < sunrise;
}

// ---- getters ----------------------------------------------------------------------------------

QVariantMap Lelan::location() const { return m_location; }
QString Lelan::placeName() const { return m_placeName; }
QVariantMap Lelan::clock() const { return m_clock; }
QString Lelan::timezone() const { return m_timezone; }
bool Lelan::locating() const { return m_locating; }
QString Lelan::hostname() const { return m_hostname; }
QString Lelan::locale() const { return m_locale; }

// ---- timedate1 --------------------------------------------------------------------------------

void Lelan::subscribeToTimeDate()
{
    QDBusConnection::systemBus().connect(kTimedate, kTimedatePath, kFdProps, QStringLiteral("PropertiesChanged"),
        this, SLOT(onTimedate1PropertiesChanged(QString,QVariantMap,QStringList)));
    refreshLocation();
}

void Lelan::refreshLocation()
{
    QDBusMessage get = QDBusMessage::createMethodCall(kTimedate, kTimedatePath, kFdProps, QStringLiteral("Get"));
    get << kTimedate << QStringLiteral("Timezone");
    auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(get), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusVariant> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] timedate1 Get(Timezone) failed:" << reply.error().name() << reply.error().message();
            return;
        }
        setTimezoneValue(reply.value().variant().toString());
    });
}

void Lelan::setTimezoneValue(const QString &tz)
{
    if (tz == m_timezone)
        return;
    m_timezone = tz;
    emit timezoneChanged();
}

void Lelan::onTimedate1PropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &invalidated)
{
    if (changed.contains(QStringLiteral("Timezone")))
        setTimezoneValue(changed.value(QStringLiteral("Timezone")).toString());
    if (changed.contains(QStringLiteral("TimeUSec")) || invalidated.contains(QStringLiteral("TimeUSec"))) {
        emit timeJumped();
        updateClock();
        updateNightFlag();
    }
}

void Lelan::setTimezone(const QString &tz)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kTimedate, kTimedatePath, kTimedate, QStringLiteral("SetTimezone"));
    m << tz << false;                                 // not interactive: polkit allows it in-session
    QDBusConnection::systemBus().asyncCall(m);
}

void Lelan::setNtp(bool on)
{
    QDBusMessage m = QDBusMessage::createMethodCall(kTimedate, kTimedatePath, kTimedate, QStringLiteral("SetNTP"));
    m << on << false;
    QDBusConnection::systemBus().asyncCall(m);
}

void Lelan::updateClock()
{
    m_clock.insert(QStringLiteral("epoch"), QDateTime::currentSecsSinceEpoch());
    emit clockChanged();
    emit dateTimeChanged();
}

// ---- hostname1 / locale1 ----------------------------------------------------------------------

void Lelan::subscribeToHostnameLocale()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    const struct { const char *service; const char *path; const char *slot; const char *key; } svcs[] = {
        {"org.freedesktop.hostname1", "/org/freedesktop/hostname1",
         SLOT(onHostname1PropertiesChanged(QString,QVariantMap,QStringList)), "Hostname"},
        {"org.freedesktop.locale1", "/org/freedesktop/locale1",
         SLOT(onLocale1PropertiesChanged(QString,QVariantMap,QStringList)), "Locale"},
    };
    for (const auto &s : svcs) {
        const QString service = QString::fromLatin1(s.service), path = QString::fromLatin1(s.path);
        bus.connect(service, path, kFdProps, QStringLiteral("PropertiesChanged"), this, s.slot);
        // T1: the current value, not only later changes
        QDBusMessage get = QDBusMessage::createMethodCall(service, path, kFdProps, QStringLiteral("Get"));
        get << service << QString::fromLatin1(s.key);
        auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(get), this);
        const QString key = QString::fromLatin1(s.key);
        const bool isHost = key == QLatin1String("Hostname");
        connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, key, isHost, service](QDBusPendingCallWatcher *w) {
            QDBusPendingReply<QDBusVariant> reply = *w;
            w->deleteLater();
            if (reply.isError())
                return;
            const QVariantMap changed{{key, reply.value().variant()}};
            isHost ? onHostname1PropertiesChanged(service, changed, {}) : onLocale1PropertiesChanged(service, changed, {});
        });
    }
}

void Lelan::onHostname1PropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &)
{
    if (!changed.contains(QStringLiteral("Hostname")))
        return;
    const QString h = changed.value(QStringLiteral("Hostname")).toString();
    if (h == m_hostname)
        return;
    m_hostname = h;
    emit hostnameChanged();
}

void Lelan::onLocale1PropertiesChanged(const QString &, const QVariantMap &changed, const QStringList &)
{
    if (!changed.contains(QStringLiteral("Locale")))
        return;
    const QString l = changed.value(QStringLiteral("Locale")).toStringList().value(0);
    if (l == m_locale)
        return;
    m_locale = l;
    emit localeChanged();
}

// ---- GeoClue2 ---------------------------------------------------------------------------------

void Lelan::subscribeToGeoClue()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusMessage getClient = QDBusMessage::createMethodCall(kGeoClue, QStringLiteral("/org/freedesktop/GeoClue2/Manager"),
                                                            QStringLiteral("org.freedesktop.GeoClue2.Manager"),
                                                            QStringLiteral("GetClient"));
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(getClient), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusObjectPath> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] GeoClue2 GetClient failed:" << reply.error().name() << reply.error().message();
            setLocating(false);
            return;
        }
        if (!m_locationAllowed) {                     // T8: switched off before GeoClue answered
            QDBusConnection::systemBus().asyncCall(QDBusMessage::createMethodCall(kGeoClue, reply.value().path(),
                QStringLiteral("org.freedesktop.GeoClue2.Client"), QStringLiteral("Stop")));
            return;
        }
        m_geoClient = reply.value().path();
        QDBusConnection bus = QDBusConnection::systemBus();
        const QString clientIface = QStringLiteral("org.freedesktop.GeoClue2.Client");
        auto set = [&](const QString &prop, const QVariant &v) {
            QDBusMessage m = QDBusMessage::createMethodCall(kGeoClue, m_geoClient, kFdProps, QStringLiteral("Set"));
            m << clientIface << prop << QVariant::fromValue(QDBusVariant(v));
            bus.asyncCall(m);
        };
        set(QStringLiteral("DesktopId"), QStringLiteral("org.ncde.desktop"));
        set(QStringLiteral("RequestedAccuracyLevel"), QVariant::fromValue(uint(kAccuracyCity)));   // T7
        bus.connect(kGeoClue, m_geoClient, clientIface, QStringLiteral("LocationUpdated"), this,
                    SLOT(onGeoClue2Location(QDBusObjectPath,QDBusObjectPath)));
        bus.asyncCall(QDBusMessage::createMethodCall(kGeoClue, m_geoClient, clientIface, QStringLiteral("Start")));
    });
}

// T8 Settings > Privacy "Location" was saved and never used: GeoClue kept locating with the switch off.
// Off = stop the GeoClue client and forget the coordinates (sunrise/sunset times stay, so automatic night
// light keeps working); on = locate again. The Lelan constructor starts GeoClue only while allowed.
void Lelan::setLocationAllowed(bool on)
{
    if (on == m_locationAllowed)
        return;
    m_locationAllowed = on;
    if (on) {
        if (m_geoClient.isEmpty()) {
            setLocating(true);
            subscribeToGeoClue();
        }
        return;
    }
    if (!m_geoClient.isEmpty()) {
        QDBusConnection bus = QDBusConnection::systemBus();
        const QString clientIface = QStringLiteral("org.freedesktop.GeoClue2.Client");
        bus.disconnect(kGeoClue, m_geoClient, clientIface, QStringLiteral("LocationUpdated"), this,
                       SLOT(onGeoClue2Location(QDBusObjectPath,QDBusObjectPath)));
        bus.asyncCall(QDBusMessage::createMethodCall(kGeoClue, m_geoClient, clientIface, QStringLiteral("Stop")));
        m_geoClient.clear();
    }
    m_location.remove(QStringLiteral("lat"));
    m_location.remove(QStringLiteral("lon"));
    m_placeName.clear();
    m_locating = false;
    emit placeNameChanged();
    emit weatherChanged();
    emit timezoneChanged();
}

void Lelan::setLocating(bool on)
{
    if (on == m_locating)
        return;
    m_locating = on;
    emit timezoneChanged();                           // the `locating` property's NOTIFY signal
    emit placeNameChanged();                          // oracle also re-emitted this on failure
}

void Lelan::onGeoClue2Location(const QDBusObjectPath &, const QDBusObjectPath &newLocation)
{
    QDBusMessage getAll = QDBusMessage::createMethodCall(kGeoClue, newLocation.path(), kFdProps, QStringLiteral("GetAll"));
    getAll << QStringLiteral("org.freedesktop.GeoClue2.Location");
    auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(getAll), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            qWarning() << "[lelan] GeoClue2 Location GetAll failed:" << reply.error().name() << reply.error().message();
            setLocating(false);
            return;
        }
        if (!m_locationAllowed)
            return;                                   // T8: switched off while the answer was on its way
        const double lat = reply.value().value(QStringLiteral("Latitude")).toDouble();
        const double lon = reply.value().value(QStringLiteral("Longitude")).toDouble();
        m_location.insert(QStringLiteral("lat"), lat);
        m_location.insert(QStringLiteral("lon"), lon);
        m_locating = false;
        emit placeNameChanged();
        emit weatherChanged();
        emit moonPositionChanged();
        emit timezoneChanged();
        double sunrise = -1.0, sunset = -1.0;
        sunTimes(lat, lon, sunrise, sunset);
        if (sunrise >= 0.0 && sunset >= 0.0) {
            m_location.insert(QStringLiteral("sunrise"), sunrise);
            m_location.insert(QStringLiteral("sunset"), sunset);
        }
        updateNightFlag(true);
    });
}

// T5: "night" follows the clock — re-derived every coalesced tick, emitted only when it flips.
void Lelan::updateNightFlag(bool force)
{
    if (!m_location.contains(QStringLiteral("sunrise")) || !m_location.contains(QStringLiteral("sunset")))
        return;
    const QTime now = QTime::currentTime();
    const bool night = lelanIsNight(m_location.value(QStringLiteral("sunset")).toDouble(),
                                  m_location.value(QStringLiteral("sunrise")).toDouble(),
                                  now.minute() / 60.0 + now.hour());
    if (!force && m_location.value(QStringLiteral("night")).toBool() == night && m_location.contains(QStringLiteral("night")))
        return;
    m_location.insert(QStringLiteral("night"), night);
    emit placeNameChanged();
}
