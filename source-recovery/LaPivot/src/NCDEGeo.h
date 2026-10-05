// NCDEGeo.h — the `geo` context object: NCDE's place/time surface.
//
// Rebuilt from oracle: decomp/NCDEGeo.c (17 functions; 12 real + 5 moc boilerplate).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2 (NCDEGeo, 55 syms, listed among the
//       "load-bearing live classes"); docs/lepivot-gaps.md §"Architecture notes"
//       ("In the original, `geo` is an ALIAS of the same NCDEEngine instance
//        (ncde==geo). Le Pivot uses a separate NCDEGeo delegating to Lelan");
//       docs/ncde-architecture.md §2.
// Consumers: NCDEGeoChart.qml (documents lat/lon/zone/tzName/offset/localTime/
//       locating/place, and states localTime ticks on "engine ticks — no QML Timer"),
//       WeatherLive.qml:116 (lat/lon for the sun position), WeatherPanel.qml:156
//       (place as the location caption).
//
// The class is a thin façade: Lelan owns the GeoClue2 feed and the timezone, this
// reshapes it for QML and republishes it on Lelan's own signals — it owns no timer
// of its own (docs/anim-policy.md §4.4).

#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QVariantMap>

class Lelan;

class NCDEGeo : public QObject
{
    Q_OBJECT

    // ---- oracle interface (interfaces/LaPivot-metaobjects.h, tools/gen_header.py) ----
    Q_PROPERTY(double latitude READ latitude NOTIFY changed)
    Q_PROPERTY(double longitude READ longitude NOTIFY changed)
    Q_PROPERTY(QString localTime READ localTime NOTIFY changed)
    Q_PROPERTY(bool locating READ locating NOTIFY changed)
    Q_PROPERTY(QString offset READ offset NOTIFY changed)
    Q_PROPERTY(QString place READ place NOTIFY changed)
    Q_PROPERTY(QString tzName READ tzName NOTIFY changed)
    Q_PROPERTY(QString zone READ zone NOTIFY changed)
    // ---- end oracle interface ----

public:
    explicit NCDEGeo(QObject *parent = nullptr);

    double latitude() const;
    double longitude() const;
    QString localTime() const;
    bool locating() const;
    QString offset() const;
    QString place() const;
    QString tzName() const;
    QString zone() const;

    // ---- declared additions (see tests/iface_additions/NCDEGeo.txt) ----
    // Wired from main() right after Lelan is built. In the original shell `geo` WAS
    // the NCDEEngine, so the same GeoClue data reached QML through the engine.
    void setLelan(Lelan *l);
    // The operator's 12/24-hour choice (Settings::hourFormat: "auto"|"12"|"24"),
    // pushed in from main(). The oracle hard-coded "h:mm AP".
    void setHourFormatPref(const QString &hourFormat);
    // Test host only: a location/timezone source with Lelan's exact shape, so the
    // façade logic is testable without linking all of Lelan.
    void setSource(const QVariantMap &location, const QString &place,
                   const QString &tz, const QDateTime &now = QDateTime());
    // Republish (what the Lelan signals are connected to).
    Q_INVOKABLE void publish();
    // ---- end additions ----

signals:
    void changed();

private:
    QString hourFormat() const;  // resolved QDateTime format string
    QString tz() const;          // the raw IANA id (oracle: Lelan::timezone())

    QVariantMap location() const;   // oracle: Lelan::location() / m_source
    QString placeName() const;      // oracle: Lelan::placeName() / m_source
    QString timezone() const;       // oracle: Lelan::timezone() / m_source

    Lelan *m_lelan = nullptr;       // oracle field offset +0x10
    bool m_haveSource = false;      // test-only source override
    QVariantMap m_source;
    QString m_sourcePlace;
    QString m_sourceTz;
    QDateTime m_frozenNow;          // non-null => use it as "now" (tests)
    QString m_hourFormat;            // "", "12" or "24"; "" = auto (locale)
};
