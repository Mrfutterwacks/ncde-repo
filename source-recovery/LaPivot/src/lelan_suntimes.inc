// lelan_suntimes.inc — shared by Lelan_time.cpp and tests/suntimes_diff.cpp (one implementation).
#pragma once
#include <QDateTime>
#include <QTime>
#include <cmath>

// Sunrise equation, transcribed constant-for-constant from the oracle ((anonymous)::computeSunTimes).
// Local-time hours of sunrise and sunset for today; both -1 in polar day/night.
inline void sunTimes(double lat, double lon, double &sunrise, double &sunset)
{
    constexpr double rad = 0.017453292519943295;
    auto julianToLocalHours = [](double jd) {
        const QTime t = QDateTime::fromSecsSinceEpoch(qint64((jd - 2440587.5) * 86400.0)).time();
        return t.minute() / 60.0 + t.hour();
    };
    const double jdNow = double(QDateTime::currentSecsSinceEpoch()) / 86400.0 + 2440587.5;
    const double n = std::floor((jdNow - 2451545.0) + 0.0008);
    const double jStar = n - lon / 360.0;
    const double m = std::fmod(jStar * 0.98560028 + 357.5291, 360.0);
    const double c = std::sin(m * 3.0 * rad) * 0.0003 + std::sin((m + m) * rad) * 0.02 + std::sin(m * rad) * 1.9148;
    const double lambda = std::fmod(m + c + 180.0 + 102.9372, 360.0);
    const double jTransit = (std::sin(m * rad) * 0.0053 + (jStar + 2451545.0)) - std::sin((lambda + lambda) * rad) * 0.0069;
    const double sinDecl = std::sin(lambda * rad) * 0.39778850739794974;
    const double cosDecl = std::cos(std::asin(sinDecl));
    const double cosH = (-0.014485726138606464 - std::sin(lat * rad) * sinDecl) / (std::cos(lat * rad) * cosDecl);
    if (cosH < -1.0 || cosH > 1.0) {
        sunrise = sunset = -1.0;
        return;
    }
    const double h = std::acos(cosH) / rad;
    sunrise = julianToLocalHours(jTransit - h / 360.0);
    sunset = julianToLocalHours(h / 360.0 + jTransit);
}
