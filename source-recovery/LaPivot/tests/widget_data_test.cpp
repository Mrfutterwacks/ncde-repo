#include "WidgetData.h"
#include "Settings.h"
#include "Lelan.h"

#include <QCoreApplication>
#include <QLocale>
#include <QSignalSpy>
#include <QTest>
#include <QTime>
#include <QTimer>

namespace {
int forwardedVolume = -1;

bool localeUses24HourClock()
{
    const QString format = QLocale::system().timeFormat(QLocale::ShortFormat);
    return format.contains(QLatin1Char('H')) || format.contains(QLatin1Char('k'));
}
}

Settings::Settings(QObject *parent) : QObject(parent) {}
Settings::~Settings() = default;
QString Settings::hourFormat() const { return m_hourFormat; }
void Settings::setHourFormat(const QString &value)
{
    if (m_hourFormat == value)
        return;
    m_hourFormat = value;
    emit settingsChanged();
}
bool Settings::showSeconds() const { return m_showSeconds; }
void Settings::setShowSeconds(bool value)
{
    if (m_showSeconds == value)
        return;
    m_showSeconds = value;
    emit settingsChanged();
}

Lelan::Lelan(QObject *parent, bool) : QObject(parent) {}
Lelan::~Lelan() = default;
void Lelan::setVolume(int value) { forwardedVolume = value; }
QVariantMap Lelan::sentinelTemps() const { return {}; }

class TestWidgetData : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        qputenv("QT_QPA_PLATFORM", "offscreen");
    }

    void clockFollows12HourSetting()
    {
        Settings settings;
        settings.setHourFormat(QStringLiteral("12"));
        WidgetData data;
        data.setSettings(&settings);

        const QTime now = QTime::currentTime();
        const int expected = now.hour() % 12 == 0 ? 12 : now.hour() % 12;
        QCOMPARE(data.timeHour(), QString::number(expected));
        QCOMPARE(data.timeAMPM(), now.toString(QStringLiteral("AP")));
    }

    void clockFollows24HourSetting()
    {
        Settings settings;
        settings.setHourFormat(QStringLiteral("24"));
        WidgetData data;
        data.setSettings(&settings);

        QCOMPARE(data.timeHour(), QString::number(QTime::currentTime().hour()));
        QVERIFY(data.timeAMPM().isEmpty());
    }

    void autoClockFollowsSystemLocale()
    {
        Settings settings;
        settings.setHourFormat(QStringLiteral("auto"));
        WidgetData data;
        data.setSettings(&settings);

        const QTime now = QTime::currentTime();
        const int expected = localeUses24HourClock()
            ? now.hour()
            : (now.hour() % 12 == 0 ? 12 : now.hour() % 12);
        QCOMPARE(data.timeHour(), QString::number(expected));
        QCOMPARE(data.timeAMPM().isEmpty(), localeUses24HourClock());
    }

    void showSecondsControlsSecondValueAndNotifies()
    {
        Settings settings;
        WidgetData data;
        data.setSettings(&settings);
        QVERIFY(data.timeSecond().isEmpty());

        QSignalSpy clockSpy(&data, &WidgetData::clockChanged);
        settings.setShowSeconds(true);
        QCOMPARE(clockSpy.count(), 1);
        QCOMPARE(data.timeSecond(), QTime::currentTime().toString(QStringLiteral("ss")));
        QVERIFY(data.metaObject()->indexOfProperty("timeSecond") >= 0);

        settings.setShowSeconds(false);
        QVERIFY(data.timeSecond().isEmpty());
    }

    void setVolumeForwardsToLelanWithoutAudioBackend()
    {
        Lelan lelan(nullptr, false);
        WidgetData data;
        data.setLelan(&lelan);
        forwardedVolume = -1;

        data.setVolume(83);

        QCOMPARE(forwardedVolume, 83);
    }

    void pulseIsSharedAndNoWidgetTimerIsCreated()
    {
        Lelan lelan(nullptr, false);
        WidgetData data;
        data.setLelan(&lelan);
        QSignalSpy clockSpy(&data, &WidgetData::clockChanged);

        QVERIFY(data.findChildren<QTimer *>().isEmpty());
        lelan.pulse(1);
        QCOMPARE(clockSpy.count(), 1);
    }

    void statsAreReadOnlyOnTheSharedStatsPulse()
    {
        Lelan lelan(nullptr, false);
        WidgetData data;
        data.setLelan(&lelan);
        QSignalSpy statsSpy(&data, &WidgetData::statsChanged);

        lelan.pulse(3);

        QCOMPARE(statsSpy.count(), 1);
        QVERIFY(data.ramPercent() >= 0.0 && data.ramPercent() <= 100.0);
        QVERIFY(data.diskPercent() >= 0.0 && data.diskPercent() <= 100.0);
    }
};

QTEST_MAIN(TestWidgetData)
#include "widget_data_test.moc"
