// WidgetData_weather.cpp — weather (open-meteo) and moon position
// Rebuilt 2026-10-01 from oracle: WidgetData::fetchWeather (+lambda#1), onWeather (+lambda#1),
// wmoToYahooCode, weatherTemp..weatherSunset, moonAzimuth, moonElevation (decomp/WidgetData.c).
// The previous rebuild had no fetch at all (getters read Lelan::location(), which holds no
// weather) -> the desktop weather panel stayed blank.
// DEFECTS FIXED vs oracle:
//  W1 a failed fetch (network not up yet at login, captive portal, DNS hiccup) left the panel
//     blank for 30 min (next fetch at tick 1800). Now retried after 60 s.
//  W2 a place learned after start-up (Lelan placeNameChanged) showed the old/default place's
//     weather until the next half-hour fetch. Now fetched at once (WidgetData.cpp).
//  W3 the user's own Settings pin ("_pinned" in location-memory.json) was ignored by the C++ fetch.
//  W4 no GeoClue -> a hardcoded central-Illinois point for everyone; now the automatic chain in
//     fetchWeather (pin, GeoClue, place learned for this network, IP lookup), never a fixed town.

#include "WidgetData.h"
#include "Lelan.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

QString WidgetData::weatherTemp() const { return m_weatherTemp; }
QString WidgetData::weatherIcon() const { return m_weatherIcon; }
QString WidgetData::weatherLocation() const { return m_weatherLocation; }
QString WidgetData::weatherHigh() const { return m_weatherHigh; }
QString WidgetData::weatherLow() const { return m_weatherLow; }
QString WidgetData::weatherHumidity() const { return m_weatherHumidity; }
QString WidgetData::weatherWind() const { return m_weatherWind; }
QString WidgetData::weatherSunrise() const { return m_weatherSunrise; }
QString WidgetData::weatherSunset() const { return m_weatherSunset; }

// Where is this user? (W4) 1. their own pin from Settings › Date & Time (Town/ZIP lookup);
// 2. GeoClue (Lelan); 3. the place learned for the network they are on (location-memory.json,
// written by WeatherLive.qml); 4. IP geolocation. Never a fixed town: the oracle fell back to a
// hardcoded point in central Illinois, so every user without GeoClue got Illinois weather.
void WidgetData::fetchWeather()
{
    if (!m_lelan)
        return;
    const QVariantMap mem = Lelan::readConfig(QStringLiteral("location-memory"));
    const QVariantMap pin = mem.value(QStringLiteral("_pinned")).toMap();
    if (pin.contains(QStringLiteral("lat")) && pin.contains(QStringLiteral("lon"))) {
        fetchWeatherAt(pin.value(QStringLiteral("lat")).toDouble(), pin.value(QStringLiteral("lon")).toDouble(),
                       pin.value(QStringLiteral("place")).toString());
        return;
    }
    const QVariantMap loc = m_lelan->location();
    if (loc.contains(QStringLiteral("lat")) && loc.contains(QStringLiteral("lon"))) {
        fetchWeatherAt(loc.value(QStringLiteral("lat")).toDouble(), loc.value(QStringLiteral("lon")).toDouble(),
                       m_lelan->placeName());
        return;
    }
    const QString ssid = m_lelan->network().value(QStringLiteral("ssid")).toString();
    const QVariantMap known = mem.value(ssid).toMap();
    if (known.contains(QStringLiteral("lat")) && known.contains(QStringLiteral("lon"))) {
        fetchWeatherAt(known.value(QStringLiteral("lat")).toDouble(), known.value(QStringLiteral("lon")).toDouble(),
                       known.value(QStringLiteral("place")).toString());
        return;
    }
    locateByIp();
}

void WidgetData::refreshWeather()
{
    // DateTimeTab writes location-memory.json with an async XHR PUT just before calling this
    QTimer::singleShot(500, this, &WidgetData::fetchWeather);
}

void WidgetData::locateByIp()
{
    if (!m_nam)
        m_nam = new QNetworkAccessManager(this);
    QNetworkRequest req{QUrl(QStringLiteral("https://ipwho.is/?fields=success,latitude,longitude,city"))};
    req.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("ncde/1.0"));
    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        const QJsonObject j = QJsonDocument::fromJson(reply->readAll()).object();
        if (reply->error() != QNetworkReply::NoError || !j.value(QStringLiteral("success")).toBool()) {
            qWarning() << "WidgetData: no location yet (GeoClue, saved place and IP lookup all failed)";
            if (!m_weatherRetryPending) {   // nothing is shown rather than another town's weather
                m_weatherRetryPending = true;
                QTimer::singleShot(60000, this, [this] {
                    m_weatherRetryPending = false;
                    fetchWeather();
                });
            }
            return;
        }
        fetchWeatherAt(j.value(QStringLiteral("latitude")).toDouble(), j.value(QStringLiteral("longitude")).toDouble(),
                       j.value(QStringLiteral("city")).toString());
    });
}

void WidgetData::fetchWeatherAt(double lat, double lon, const QString &place)
{
    const QString url = QStringLiteral(
        "https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2"
        "&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code"
        "&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset"
        "&temperature_unit=fahrenheit&wind_speed_unit=mph&timezone=auto").arg(lat).arg(lon);
    if (!m_nam)
        m_nam = new QNetworkAccessManager(this);
    QNetworkRequest req{QUrl(url)};
    req.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("ncde/1.0"));
    QNetworkReply *reply = m_nam->get(req);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        onWeather(reply);
        reply->deleteLater();
    });
    m_weatherLocation = place;
}

void WidgetData::onWeather(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "WidgetData: weather fetch failed:" << reply->errorString();
        if (!m_weatherRetryPending) {   // W1
            m_weatherRetryPending = true;
            QTimer::singleShot(60000, this, [this] {
                m_weatherRetryPending = false;
                fetchWeather();
            });
        }
        return;
    }
    const QJsonObject root = QJsonDocument::fromJson(reply->readAll()).object();
    const QJsonObject cur = root.value(QStringLiteral("current")).toObject();
    m_weatherTemp = QString::number(qRound(cur.value(QStringLiteral("temperature_2m")).toDouble())) + QStringLiteral("°");
    m_weatherHumidity = QString::number(cur.value(QStringLiteral("relative_humidity_2m")).toInt()) + QStringLiteral("%");
    m_weatherWind = QString::number(qRound(cur.value(QStringLiteral("wind_speed_10m")).toDouble())) + QStringLiteral(" mph");
    m_weatherIcon = QString::number(wmoToYahooCode(cur.value(QStringLiteral("weather_code")).toInt()));

    const QJsonObject daily = root.value(QStringLiteral("daily")).toObject();
    const QJsonArray hi = daily.value(QStringLiteral("temperature_2m_max")).toArray();
    const QJsonArray lo = daily.value(QStringLiteral("temperature_2m_min")).toArray();
    if (!hi.isEmpty())
        m_weatherHigh = QString::number(qRound(hi.first().toDouble())) + QStringLiteral("°");
    if (!lo.isEmpty())
        m_weatherLow = QString::number(qRound(lo.first().toDouble())) + QStringLiteral("°");
    // first entry of a daily array as text, e.g. "2026-10-01T06:52" -> time part "06:52"
    auto firstOf = [&daily](const char *key) {
        const QJsonArray a = daily.value(QLatin1String(key)).toArray();
        return a.isEmpty() ? QString() : a.first().toVariant().toString();
    };
    m_weatherSunrise = firstOf("sunrise").section(QLatin1Char('T'), 1, 1);
    m_weatherSunset = firstOf("sunset").section(QLatin1Char('T'), 1, 1);
    emit weatherChanged();
}

// WMO weather code -> the Yahoo condition code the Mucha weather icons are drawn for
int WidgetData::wmoToYahooCode(int wmo)
{
    switch (wmo) {
    case 0: return 32;                          // clear
    case 1: return 34;                          // mainly clear
    case 2: return 30;                          // partly cloudy
    case 3: return 26;                          // overcast
    case 45: case 48: return 20;                // fog
    case 51: case 53: case 55: return 9;        // drizzle
    case 56: case 57: return 8;                 // freezing drizzle
    case 61: return 11;                         // light rain
    case 63: case 65: return 12;                // rain
    case 66: case 67: return 10;                // freezing rain
    case 71: case 73: case 75: return 16;       // snow
    case 77: return 13;                         // snow grains
    case 80: case 81: case 82: return 40;       // showers
    case 85: case 86: return 46;                // snow showers
    case 95: case 96: case 99: return 4;        // thunderstorm
    default: return 26;
    }
}

double WidgetData::moonAzimuth() const
{
    return m_moonAzimuth;
}

double WidgetData::moonElevation() const
{
    return m_moonElevation;
}
