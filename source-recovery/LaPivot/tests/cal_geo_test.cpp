// cal_geo_test.cpp — NCDEGeo unit tests (offscreen, isolated source/timezone).

#include <QtTest/QtTest>
#include <QDateTime>
#include <QTimeZone>

#include "NCDEGeo.h"

class CalGeoTest : public QObject
{
    Q_OBJECT

private slots:
    void testSourceProperties();
    void testIanaZoneAndDstOffset();
    void testInvalidZoneUsesLocalOffset();
    void testHourFormatPreference();
};

void CalGeoTest::testSourceProperties()
{
    NCDEGeo geo;
    const QVariantMap location{{"lat", 41.88}, {"lon", -87.63}};
    geo.setSource(location, QStringLiteral("Chicago"), QStringLiteral("America/Chicago"));

    QCOMPARE(geo.latitude(), 41.88);
    QCOMPARE(geo.longitude(), -87.63);
    QCOMPARE(geo.place(), QStringLiteral("Chicago"));
    QVERIFY(!geo.locating());

    geo.setSource({}, QString(), QString(), QDateTime());
    QVERIFY(geo.locating());
}

void CalGeoTest::testIanaZoneAndDstOffset()
{
    const QTimeZone chicago(QByteArrayLiteral("America/Chicago"));
    QVERIFY(chicago.isValid());

    NCDEGeo geo;
    const QDateTime summer(QDate(2026, 7, 1), QTime(13, 5), chicago);
    geo.setSource({}, QStringLiteral("Chicago"), QStringLiteral("America/Chicago"), summer);

    QCOMPARE(geo.zone(), QStringLiteral("America/Chicago"));
    QVERIFY(!geo.tzName().isEmpty());
    QVERIFY(geo.tzName() != geo.zone());
    QCOMPARE(geo.offset(), QStringLiteral("UTC-05:00"));

    const QDateTime winter(QDate(2026, 1, 1), QTime(13, 5), chicago);
    geo.setSource({}, QStringLiteral("Chicago"), QStringLiteral("America/Chicago"), winter);
    QCOMPARE(geo.offset(), QStringLiteral("UTC-06:00"));
    QVERIFY(geo.tzName() != QStringLiteral("America/Chicago"));
}

void CalGeoTest::testInvalidZoneUsesLocalOffset()
{
    const QDateTime localNow = QDateTime::currentDateTime();
    NCDEGeo geo;
    geo.setSource({}, QString(), QStringLiteral("Invalid/Timezone"), localNow);

    const int seconds = localNow.offsetFromUtc();
    const int absolute = qAbs(seconds);
    const QString expected = seconds == 0
        ? QStringLiteral("UTC")
        : QStringLiteral("UTC%1%2:%3")
              .arg(seconds < 0 ? QStringLiteral("-") : QStringLiteral("+"))
              .arg(absolute / 3600, 2, 10, QLatin1Char('0'))
              .arg((absolute % 3600) / 60, 2, 10, QLatin1Char('0'));
    QCOMPARE(geo.offset(), expected);
}

void CalGeoTest::testHourFormatPreference()
{
    const QDateTime chicago(QDate(2026, 7, 1), QTime(13, 5),
                            QTimeZone(QByteArrayLiteral("America/Chicago")));
    NCDEGeo geo;
    geo.setSource({}, QString(), QStringLiteral("America/Chicago"), chicago);

    geo.setHourFormatPref(QStringLiteral("12"));
    QCOMPARE(geo.localTime(), QStringLiteral("1:05 PM"));
    geo.setHourFormatPref(QStringLiteral("24"));
    QCOMPARE(geo.localTime(), QStringLiteral("13:05"));
}

QTEST_GUILESS_MAIN(CalGeoTest)
#include "cal_geo_test.moc"
