// WidgetData — live desktop-widget feed (CPU/RAM/net/battery, MPRIS, weather, moon, clock).
// Pass-through to Lelan for system data; owns clock/date formatting (respects Settings hourFormat/showSeconds).
//
// Rebuilt from LaPivot oracle 3507b4c6…. The block between GENERATED markers is produced by
// tools/gen_header.py from the oracle's moc metadata — do not edit it by hand; the QML binds
// to exactly these names. Implementation split by area: WidgetData_<area>.cpp.
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantList>

class Lelan;
class AnimPolicy;
class Settings;

class QNetworkAccessManager;
class QNetworkReply;

class WidgetData : public QObject
{
    Q_OBJECT
    Q_MOC_INCLUDE("Settings.h")   // Settings* is a Q_INVOKABLE argument; moc needs the full type
// ---- GENERATED: tools/gen_header.py WidgetData ----
    Q_PROPERTY(QVariantList removableVolumes READ removableVolumes NOTIFY changed)
    Q_PROPERTY(int volume READ volume NOTIFY changed)
    Q_PROPERTY(bool muted READ muted NOTIFY changed)
    Q_PROPERTY(bool hasBattery READ hasBattery NOTIFY changed)
    Q_PROPERTY(int batteryLevel READ batteryLevel NOTIFY changed)
    Q_PROPERTY(bool batteryCharging READ batteryCharging NOTIFY changed)
    Q_PROPERTY(bool networkUp READ networkUp NOTIFY changed)
    Q_PROPERTY(bool netOnline READ netOnline NOTIFY changed)
    Q_PROPERTY(QString netUp READ netUp NOTIFY statsChanged)
    Q_PROPERTY(QString netDown READ netDown NOTIFY statsChanged)
    Q_PROPERTY(bool mediaActive READ mediaActive NOTIFY mediaChanged)
    Q_PROPERTY(bool mediaPlaying READ mediaPlaying NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaTitle READ mediaTitle NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaArtist READ mediaArtist NOTIFY mediaChanged)
    Q_PROPERTY(QString mediaAlbum READ mediaAlbum NOTIFY mediaChanged)
    Q_PROPERTY(double mediaPosition READ mediaPosition NOTIFY mediaChanged)
    Q_PROPERTY(double mediaDuration READ mediaDuration NOTIFY mediaChanged)
    Q_PROPERTY(QString timeHour READ timeHour NOTIFY clockChanged)
    Q_PROPERTY(QString timeMinute READ timeMinute NOTIFY clockChanged)
    Q_PROPERTY(QString timeSecond READ timeSecond NOTIFY clockChanged)
    Q_PROPERTY(QString timeAMPM READ timeAMPM NOTIFY clockChanged)
    Q_PROPERTY(bool colonOn READ colonOn NOTIFY clockChanged)
    Q_PROPERTY(QString greeting READ greeting NOTIFY clockChanged)
    Q_PROPERTY(QString dateString READ dateString NOTIFY clockChanged)
    Q_PROPERTY(double cpuTotal READ cpuTotal NOTIFY statsChanged)
    Q_PROPERTY(double ramPercent READ ramPercent NOTIFY statsChanged)
    Q_PROPERTY(double diskPercent READ diskPercent NOTIFY statsChanged)
    Q_PROPERTY(double cpuFreqGHz READ cpuFreqGHz NOTIFY statsChanged)
    Q_PROPERTY(double cpuTempF READ cpuTempF NOTIFY statsChanged)
    Q_PROPERTY(QString uptime READ uptime NOTIFY statsChanged)
    Q_PROPERTY(QVariantList mountedVolumes READ mountedVolumes NOTIFY statsChanged)
    Q_PROPERTY(QString weatherTemp READ weatherTemp NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherIcon READ weatherIcon NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherLocation READ weatherLocation NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherHigh READ weatherHigh NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherLow READ weatherLow NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherHumidity READ weatherHumidity NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherWind READ weatherWind NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherSunrise READ weatherSunrise NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherSunset READ weatherSunset NOTIFY weatherChanged)
    Q_PROPERTY(double moonAzimuth READ moonAzimuth NOTIFY moonPositionChanged)
    Q_PROPERTY(double moonElevation READ moonElevation NOTIFY moonPositionChanged)

public:
    QVariantList removableVolumes() const;
    int volume() const;
    bool muted() const;
    bool hasBattery() const;
    int batteryLevel() const;
    bool batteryCharging() const;
    bool networkUp() const;
    bool netOnline() const;
    QString netUp() const;
    QString netDown() const;
    bool mediaActive() const;
    bool mediaPlaying() const;
    QString mediaTitle() const;
    QString mediaArtist() const;
    QString mediaAlbum() const;
    double mediaPosition() const;
    double mediaDuration() const;
    QString timeHour() const;
    QString timeMinute() const;
    QString timeSecond() const;
    QString timeAMPM() const;
    bool colonOn() const;
    QString greeting() const;
    QString dateString() const;
    double cpuTotal() const;
    double ramPercent() const;
    double diskPercent() const;
    double cpuFreqGHz() const;
    double cpuTempF() const;
    QString uptime() const;
    QVariantList mountedVolumes() const;
    QString weatherTemp() const;
    QString weatherIcon() const;
    QString weatherLocation() const;
    QString weatherHigh() const;
    QString weatherLow() const;
    QString weatherHumidity() const;
    QString weatherWind() const;
    QString weatherSunrise() const;
    QString weatherSunset() const;
    double moonAzimuth() const;
    double moonElevation() const;

    // declared addition: Settings › Date & Time calls this after the weather pin changes
    Q_INVOKABLE void refreshWeather();
    Q_INVOKABLE void setVolume(int v);
    Q_INVOKABLE void toggleMute();
    Q_INVOKABLE void mediaTogglePlay();
    Q_INVOKABLE void mediaNext();
    Q_INVOKABLE void mediaPrev();
    Q_INVOKABLE void mediaSeek(double p);
    Q_INVOKABLE void mountVolume(const QString &p);
    Q_INVOKABLE void unmountVolume(const QString &p);

signals:
    void changed();
    void clockChanged();
    void statsChanged();
    void weatherChanged();
    void moonPositionChanged();
    void mediaChanged();
    void mediaPositionChanged();
// ---- END GENERATED ----

public:
    // ---- additions beyond the oracle ----
    // Settings for clock formatting (hourFormat: "auto"/"12"/"24", showSeconds)
    Q_INVOKABLE void setSettings(Settings *settings);

public:
    explicit WidgetData(QObject *parent = nullptr);
    ~WidgetData() override;

    void setLelan(Lelan *lelan);
    void setAnimPolicy(AnimPolicy *policy);

private:
    // ---- clock/date/greeting (WidgetData_time.cpp) ----
    void updateClock();
    QString formatHour(int hour) const;
    QString formatMinute(int minute) const;
    QString formatAMPM(int hour) const;
    QString formatDate() const;
    QString formatGreeting(int hour) const;

    // ---- stats (WidgetData_stats.cpp) ----
    void readStats();
    void readNetSpeed();
    void readUptime();

    // ---- weather/moon (WidgetData_weather.cpp) ----
    void fetchWeather();
    void fetchWeatherAt(double lat, double lon, const QString &place);
    void locateByIp();
    void onWeather(QNetworkReply *reply);
    static int wmoToYahooCode(int wmo);
    // ---- pulse handler (WidgetData.cpp) ----
    void onPulse(qulonglong tick);

    // ---- members ----
    Lelan *m_lelan = nullptr;
    AnimPolicy *m_animPolicy = nullptr;
    Settings *m_settings = nullptr;

    // Cached values for stats/weather/moon (emitted via NOTIFY signals)
    double m_cpuTotal = 0.0;
    double m_ramPercent = 0.0;
    double m_diskPercent = 0.0;
    double m_cpuFreqGHz = 0.0;
    double m_cpuTempF = 0.0;
    QString m_uptime;
    QString m_netUp;
    QString m_netDown;
    QString m_weatherTemp;
    QString m_weatherIcon;
    QString m_weatherLocation;
    QString m_weatherHigh;
    QString m_weatherLow;
    QString m_weatherHumidity;
    QString m_weatherWind;
    QString m_weatherSunrise;
    QString m_weatherSunset;
    QNetworkAccessManager *m_nam = nullptr;
    bool m_weatherRetryPending = false;
    double m_moonAzimuth = 0.0;
    double m_moonElevation = 0.0;

    bool m_colonOn = false;
    qulonglong m_lastCpuTotal = 0;
    qulonglong m_lastCpuBusy = 0;
};