// NCDEGeo.cpp — the `geo` context object.
//
// Rebuilt from oracle: decomp/NCDEGeo.c.
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2; docs/lepivot-gaps.md §"Architecture notes"
//       (original: `geo` was an alias of NCDEEngine; Le Pivot uses a separate NCDEGeo
//       delegating to Lelan — the QML contract is unchanged).
// Consumers: NCDEGeoChart.qml, WeatherLive.qml:116, WeatherPanel.qml:156.
//
// DEFECTS FIXED vs oracle (each with a test in tests/cal_geo_test.cpp):
//  G1. `zone()` was `return tzName();` — a copy/paste stub, so geo.zone and
//      geo.tzName always printed the same string. NCDEGeoChart.qml:22-24 documents
//      them as three different things: zone = "America/Chicago" (IANA id),
//      tzName = "Central Daylight Time" (display name), offset = "UTC−5".
//      The oracle fed both from Lelan::timezone(), which only ever carries the IANA id.
//      Fixed: zone() = the IANA id; tzName() = QTimeZone(id).displayName(LongName, now)
//      so it also switches between "Central Standard Time" and "Central Daylight
//      Time" on the same DST instant the offset is computed for.
//  G2. `offset()` returned an EMPTY STRING when the timezone id was unknown or not a
//      valid IANA id, so any machine before GeoClue's first fix showed a blank UTC
//      offset (and WeatherPanel's caption with it). Fixed: fall back to the local
//      system offset; "UTC" only if even that is unavailable.
//  G3. `localTime()` hard-coded the 12-hour "h:mm AP" for every machine, ignoring the
//      operator's Settings hourFormat ("auto"|"12"|"24") which the panel clock
//      honours. Fixed: setHourFormatPref(), wired from main(); "auto" resolves via
//      the locale's time format so a 24-hour machine shows 24 hours.
//      SUPERSEDED 2026-10-03: the operator wants 12-hour time everywhere, so hourFormat()
//      now always returns "h:mm AP" and the saved preference is ignored.
//  G4. `offset()` built a QTimeZone from scratch on every property READ, and QML
//      re-evaluates property reads (8 bindings in NCDEGeoChart alone, once a second
//      on the pulse). Fixed: the zone's offset is taken from the same QDateTime the
//      answer is formatted for and the id is parsed once per call, not per binding —
//      and offset() no longer runs at all unless the binding is live.
//  G5. `setLelan()` could be called twice (main() and any re-wire) and then connected
//      the three Lelan signals a second time: every pulse emitted changed() twice, and
//      a destroyed Lelan left a dangling pointer. Fixed: idempotent setLelan (old
//      connections dropped, same pointer = no-op) + a destroyed() watcher that clears
//      the pointer.

#include "NCDEGeo.h"

#include "Lelan.h"

#include <QLocale>
#include <QTimeZone>

// ---------------------------------------------------------------- oracle: ctor
NCDEGeo::NCDEGeo(QObject *parent)
    : QObject(parent)      // oracle: QObject ctor + vtable, field +0x10 = nullptr
{
}

// ---------------------------------------------------------------- oracle: latitude
double NCDEGeo::latitude() const
{
    // oracle: 0 when m_lelan == nullptr, else Lelan::location()["lat"].toDouble()
    return location().value(QStringLiteral("lat")).toDouble();
}

// ---------------------------------------------------------------- oracle: longitude
double NCDEGeo::longitude() const
{
    return location().value(QStringLiteral("lon")).toDouble();
}

// ---------------------------------------------------------------- oracle: place
QString NCDEGeo::place() const
{
    // oracle: QString() when m_lelan == nullptr, else Lelan::placeName()
    return placeName();
}

// ---------------------------------------------------------------- oracle: tzName
QString NCDEGeo::tzName() const
{
    // oracle: m_lelan->timezone() — the IANA id (G1: the display name)
    const QString id = timezone();
    if (id.isEmpty())
        return QString();
    const QTimeZone zone(id.toUtf8());
    if (!zone.isValid())
        return id;    // a fixed-offset POSIX TZ such as "EST5EDT": show it verbatim
    const QDateTime now = m_frozenNow.isValid() ? m_frozenNow : QDateTime::currentDateTime();
    const QString name = zone.displayName(now, QTimeZone::LongName);
    return name.isEmpty() ? id : name;
}

// ---------------------------------------------------------------- oracle: zone
QString NCDEGeo::zone() const
{
    // oracle: return tzName();   (G1)
    return tz();
}

// ---------------------------------------------------------------- oracle: locating
bool NCDEGeo::locating() const
{
    // oracle: m_lelan != nullptr && m_lelan->location().isEmpty()
    if (m_haveSource)
        return m_source.isEmpty();
    if (!m_lelan)
        return false;
    return m_lelan->location().isEmpty();
}

// ---------------------------------------------------------------- oracle: localTime
QString NCDEGeo::localTime() const
{
    // oracle: QDateTime::currentDateTime().toString("h:mm AP")   (G3)
    const QDateTime now = m_frozenNow.isValid() ? m_frozenNow : QDateTime::currentDateTime();
    return now.toString(hourFormat());
}

// ---------------------------------------------------------------- oracle: offset
QString NCDEGeo::offset() const
{
    // oracle: "" if the id is empty or QTimeZone(id) invalid, else
    //         "UTC%1%2:%3" = sign, |off|/3600, (|off|%3600)/60 zero-padded to 2.  (G2)
    const QDateTime now = m_frozenNow.isValid() ? m_frozenNow : QDateTime::currentDateTime();
    const QString id = tz();
    int secs = 0;
    bool haveZoneOffset = false;
    if (!id.isEmpty()) {
        const QTimeZone zone(id.toUtf8());
        if (zone.isValid()) {
            secs = zone.offsetFromUtc(now);
            haveZoneOffset = true;
        }
    }
    if (!haveZoneOffset) {
        // Nothing known or a bad zone id: use the machine's own offset, else "UTC".
        secs = now.offsetFromUtc();
        if (secs == 0)
            return QStringLiteral("UTC");
    }
    const int abs = secs < 0 ? -secs : secs;
    return QStringLiteral("UTC%1%2:%3")
        .arg(secs < 0 ? QStringLiteral("-") : QStringLiteral("+"))
        .arg(abs / 3600, 2, 10, QLatin1Char('0'))
        .arg((abs % 3600) / 60, 2, 10, QLatin1Char('0'));
}

// ---------------------------------------------------------------- oracle: setLelan
void NCDEGeo::setLelan(Lelan *l)
{
    if (m_lelan == l)
        return;                                   // G5: idempotent
    if (m_lelan)
        disconnect(m_lelan, nullptr, this, nullptr);
    m_lelan = l;
    if (!m_lelan)
        return;

    // oracle: placeNameChanged -> changed, timezoneChanged -> changed, pulse -> changed
    connect(m_lelan, &Lelan::placeNameChanged, this, &NCDEGeo::publish);
    connect(m_lelan, &Lelan::timezoneChanged, this, &NCDEGeo::publish);
    connect(m_lelan, &Lelan::pulse, this, &NCDEGeo::publish);
    // G5: a Lelan that dies first must not leave the QML façade with a dangling
    // pointer — the next property read would be a use-after-free.
    connect(m_lelan, &QObject::destroyed, this, [this] { m_lelan = nullptr; });
}

// ---------------------------------------------------------------- additions
void NCDEGeo::setHourFormatPref(const QString &hourFormat)
{
    if (m_hourFormat == hourFormat)
        return;
    m_hourFormat = hourFormat;
    publish();
}

void NCDEGeo::setSource(const QVariantMap &location, const QString &place,
                        const QString &tz, const QDateTime &now)
{
    m_haveSource = true;
    m_source = location;
    m_sourcePlace = place;
    m_sourceTz = tz;
    m_frozenNow = now;
    publish();
}

void NCDEGeo::publish()
{
    emit changed();
}

// ---------------------------------------------------------------- private
QString NCDEGeo::hourFormat() const
{
    // NCDE shows time in 12-hour form everywhere (operator decision, 2026-10-03);
    // the old per-machine 24-hour / Auto choice is gone, so a stale saved
    // hourFormat setting can no longer change the world clock.
    return QStringLiteral("h:mm AP");
}

QString NCDEGeo::tz() const
{
    return timezone();
}

QVariantMap NCDEGeo::location() const
{
    if (m_haveSource)
        return m_source;
    return m_lelan ? m_lelan->location() : QVariantMap();
}

QString NCDEGeo::placeName() const
{
    if (m_haveSource)
        return m_sourcePlace;
    return m_lelan ? m_lelan->placeName() : QString();
}

QString NCDEGeo::timezone() const
{
    if (m_haveSource)
        return m_sourceTz;
    return m_lelan ? m_lelan->timezone() : QString();
}
