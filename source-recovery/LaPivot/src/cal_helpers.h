// cal_helpers.h — shared free helpers for the CalendarBackend / LeapFrogPond translation units.
//
// The decompile put these in each unit's anonymous namespace. CalendarBackend.cpp also exposes them
// to the test host through static wrappers, so they live here in a named namespace instead of being
// duplicated (or, as the previous state had it, referenced across units without a declaration).
//
// Spec: RFC 5545 text escaping; the decomp's uid() -> QUuid string.
#pragma once

#include <QString>
#include <QUuid>

namespace ncde::cal {

// RFC 5545 TEXT value escaping: backslash, semicolon, comma, newline.
inline QString icsEscape(const QString &s)
{
    QString out = s;
    out.replace(QStringLiteral("\\"), QStringLiteral("\\\\"));
    out.replace(QStringLiteral(";"), QStringLiteral("\\;"));
    out.replace(QStringLiteral(","), QStringLiteral("\\,"));
    out.replace(QStringLiteral("\n"), QStringLiteral("\\n"));
    return out;
}

inline QString icsUnescape(const QString &s)
{
    QString out = s;
    out.replace(QStringLiteral("\\n"), QStringLiteral("\n"));
    out.replace(QStringLiteral("\\,"), QStringLiteral(","));
    out.replace(QStringLiteral("\\;"), QStringLiteral(";"));
    out.replace(QStringLiteral("\\\\"), QStringLiteral("\\"));
    return out;
}

// Minutes since midnight -> the calendar row's display string, e.g. 0 -> "12:00 AM",
// 750 -> "12:30 PM", 780 -> "1:00 PM". 12-hour with AM/PM, zero-padded, matching the decomp.
inline QString formatClockMinutes(int minutesOfDay)
{
    if (minutesOfDay < 0)
        minutesOfDay = 0;
    const int h = minutesOfDay / 60;
    const int m = minutesOfDay % 60;
    const QString ap = (h < 12) ? QStringLiteral("AM") : QStringLiteral("PM");
    const int hh = (h % 12 == 0) ? 12 : (h % 12);
    return QStringLiteral("%1:%2 %3").arg(hh, 2, 10, QLatin1Char('0'))
                                       .arg(m, 2, 10, QLatin1Char('0'))
                                       .arg(ap);
}

// The decomp's uid(): a fresh UUID string. The oracle truncated to 8 chars in one place and used the
// full string for ICS UIDs; the rebuild uses the full 36-char string everywhere so an ICS round-trip
// (export -> import) cannot collide.
inline QString newUid()
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

} // namespace ncde::cal
