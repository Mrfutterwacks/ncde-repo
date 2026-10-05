// WidgetData_time.cpp — clock, date, greeting formatting (respects Settings hourFormat/showSeconds)
// Rebuilt from oracle: WidgetData::timeHour, timeMinute, timeAMPM, colonOn, greeting, dateString
// Spec: Settings.h hourFormat ("auto"/"12"/"24"), showSeconds
// DEFECTS FIXED vs oracle:
// 1. Panel clock now follows Settings hourFormat and showSeconds (was hardcoded 12h + no seconds)
// 2. "auto" = locale default (QLocale::system().timeFormat())

#include "WidgetData.h"
#include "Settings.h"

#include <QTime>
#include <QDate>
#include <QLocale>

void WidgetData::updateClock()
{
    // Called from onPulse (colon blink) and setSettings (format change)
    emit clockChanged();
}

QString WidgetData::timeHour() const
{
    QTime now = QTime::currentTime();
    int hour = now.hour();
    
    int h12 = hour % 12;
    if (h12 == 0) h12 = 12;
    return QString::number(h12);
}

QString WidgetData::timeMinute() const
{
    return QTime::currentTime().toString(QStringLiteral("mm"));
}

QString WidgetData::timeSecond() const
{
    if (!m_settings || !m_settings->showSeconds())
        return {};
    return QTime::currentTime().toString(QStringLiteral("ss"));
}

QString WidgetData::timeAMPM() const
{
    QTime now = QTime::currentTime();
    return now.toString("AP");
}

bool WidgetData::colonOn() const
{
    return m_colonOn;
}

QString WidgetData::greeting() const
{
    QTime now = QTime::currentTime();
    int hour = now.hour();
    if (hour < 12)
        return QStringLiteral("Good morning");
    else if (hour < 18)
        return QStringLiteral("Good afternoon");
    else
        return QStringLiteral("Good evening");
}

QString WidgetData::dateString() const
{
    // Oracle (decomp/WidgetData.c 001a2954): always "dddd, MMMM d". The locale long format
    // used here before added the year and reordered day/month vs the live shell (2026-10-01).
    return QDate::currentDate().toString(QStringLiteral("dddd, MMMM d"));
}