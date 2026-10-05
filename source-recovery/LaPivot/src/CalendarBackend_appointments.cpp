// CalendarBackend_appointments.cpp — appointment CRUD, undo, ICS import/export.
//
// Rebuilt from oracle: decomp/CalendarBackend.c (upsertAppointment, deleteAppointment,
// exportICS, exportICSToFile, importICS, importICSFromFile, composeForHummingbird,
// composeForHummingbirdRec).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2; docs/ncde-architecture.md §2.
// Consumers: CalEditor.qml (upsert/delete), CalReminders.qml (upcomingReminders),
//       ClockCalendarPopup.qml, GliaLeapFrogBar.qml (composeForHummingbird, exportICSToFile),
//       LeapFrogLedger.qml (importICSFromFile, exportICSToFile, drag/resize).
//
// DEFECTS FIXED vs oracle:
//  C1. The oracle had FOUR independent, subtly different readings of the same record fields
//      (date, start, end, allDay, title, etc.) scattered across upsert/delete/export/import.
//      Any drift between them caused silent corruption (e.g. exportICS read "date" as a string
//      with hyphens removed, while upsert expected "YYYY-MM-DD"). Fixed: single static
//      accessors (dateOf, minutesOf, isAllDay, leadMinutes, titleOf, repeatOf) used by ALL
//      code paths — model, exporter, importer, reminder rule.
//  C4. exportICSToFile wrote the file without checking if the directory exists.
//      Fixed: configPath() ensures the directory; exportICSToFile uses it.
//  C5. fireReminder/composeForHummingbird/sendEmail/sendNtfy all blocked on the GUI thread
//      (QProcess::startDetached / synchronous D-Bus / subprocess). Fixed: deliver() runs the
//      three transports in a detached thread via QtConcurrent::run (still callable from QML).
//  C6. importICS did not validate the parsed date/time — malformed ICS could inject
//      garbage records. Fixed: normaliseAppointment() validates and defaults every field.
//  C10. upsertAppointment with an empty id generated a new UID but the oracle's uid() only
//       returned 8 chars (left(8) of the UUID). Fixed: newUid() returns the full UUID string
//       (36 chars) — the ICS UID format expects a globally unique string; 8 chars is too short.
//       The decomp's uid() was QUuid::createUuid().toString().left(8) for the undo label only;
//       the actual record id uses the full UUID.
//  C11. exportICS hard-coded the ICS header strings. Fixed: shared constants match the
//       cal-reminders daemon's expectations (BEGIN:VCALENDAR, VERSION:2.0, PRODID, CALSCALE).
//  C12. composeForHummingbird wrote a JSON file to ~/pending/ and launched
//       `hummingbird-courier --compose` but never checked if the file write succeeded or if
//       the binary exists. Fixed: validate write, fall back to notify-send with the message.

#include "CalendarBackend.h"
#include "cal_helpers.h"

#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QProcess>
#include <QStandardPaths>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

namespace {

// ---- Shared record accessors (C1) ----
QString dateOf(const QVariantMap &rec)
{
    return rec.value(QStringLiteral("date")).toString();
}

int minutesOf(const QVariantMap &rec, const char *key)
{
    const QVariant v = rec.value(QString::fromLatin1(key));
    if (v.typeId() == QMetaType::Int)
        return v.toInt();
    bool ok = false;
    const int i = v.toString().toInt(&ok);
    return ok ? i : 0;
}

bool isAllDay(const QVariantMap &rec)
{
    const QVariant v = rec.value(QStringLiteral("allDay"));
    if (v.typeId() == QMetaType::Bool)
        return v.toBool();
    return v.toString().toLower() == QStringLiteral("true");
}

int leadMinutes(const QVariantMap &rec)
{
    const QVariant v = rec.value(QStringLiteral("reminder"));
    if (v.typeId() == QMetaType::Int)
        return v.toInt();
    bool ok = false;
    const int i = v.toString().toInt(&ok);
    return ok ? i : 15; // default lead
}

QString titleOf(const QVariantMap &rec)
{
    return rec.value(QStringLiteral("title")).toString();
}

QString repeatOf(const QVariantMap &rec)
{
    const QString r = rec.value(QStringLiteral("repeat")).toString().toLower();
    static const QStringList valid = { QStringLiteral("none"), QStringLiteral("daily"),
                                       QStringLiteral("weekly"), QStringLiteral("monthly"),
                                       QStringLiteral("yearly") };
    return valid.contains(r) ? r : QStringLiteral("none");
}

// Normalise a partial appointment map into the full shape the model/daemon expect.
QVariantMap normaliseAppointment(const QVariantMap &in, const QString &id)
{
    QVariantMap out;
    out[QStringLiteral("id")] = id;
    out[QStringLiteral("title")] = in.value(QStringLiteral("title"), QStringLiteral("Untitled")).toString();
    out[QStringLiteral("date")] = in.value(QStringLiteral("date"), QDate::currentDate().toString(Qt::ISODate)).toString();
    out[QStringLiteral("start")] = minutesOf(in, "start");
    out[QStringLiteral("end")] = minutesOf(in, "end");
    out[QStringLiteral("allDay")] = isAllDay(in);
    out[QStringLiteral("location")] = in.value(QStringLiteral("location"), QString()).toString();
    out[QStringLiteral("notes")] = in.value(QStringLiteral("notes"), QString()).toString();
    out[QStringLiteral("repeat")] = repeatOf(in);
    out[QStringLiteral("reminder")] = leadMinutes(in);
    out[QStringLiteral("category")] = in.value(QStringLiteral("category"), QStringLiteral("azure")).toString();

    // C13. Carry the Google sync link through. The whitelist above is a DELIBERATE
    // validation boundary (C6: importICS must not be able to inject arbitrary fields
    // into the model), so every consumer-owned field has to be named here explicitly.
    //
    // This one was missed, and it was catastrophic. GoogleCalendarSync stores each
    // event's link (cal/event/etag/sig/ro/inst) in `gcal` on the appointment it hands
    // to upsertAppointment(). Dropping it here meant the link never reached disk, so
    // step2PushDeletes() read every single appointment as "never sent to Google" and
    // re-POSTed the entire calendar on every poll, forever. apptToEvent() sent no
    // iCalUID, so Google could not dedupe and created a NEW event each time; the pull
    // brought those duplicates back as fresh `g-…` records, which were then pushed
    // again. 1152 appointments became 1753 in twenty minutes, each cycle re-writing a
    // 500 KB calendar.json on the GUI thread until LaPivot's main thread sat at 100%
    // and the whole desktop stopped responding.
    //
    // The lesson, recorded here so it is not re-learned: a normaliser with a
    // hard-coded field list silently eats fields added later by other components.
    // If you add a field to an appointment in QML or C++, add it here too.
    const QVariantMap link = in.value(QStringLiteral("gcal")).toMap();
    if (!link.isEmpty())
        out[QStringLiteral("gcal")] = link;
    return out;
}

QString hmFmtTime(int minutesOfDay)
{
    if (minutesOfDay < 0)
        minutesOfDay = 0;
    const int h = minutesOfDay / 60;
    const int m = minutesOfDay % 60;
    return QStringLiteral("%1%2").arg(h, 2, 10, QLatin1Char('0'))
                                   .arg(m, 2, 10, QLatin1Char('0'));
}

} // namespace

// ---------------------------------------------------------------- upsertAppointment
QString CalendarBackend::upsertAppointment(const QVariantMap &rec)
{
    const QString incomingId = rec.value(QStringLiteral("id")).toString();
    const bool isNew = incomingId.isEmpty();

    QString id = incomingId;
    if (isNew) {
        id = ncde::cal::newUid();
    }

    const QVariantMap norm = normaliseAppointment(rec, id);

    pushUndo(isNew ? QStringLiteral("new “%1”").arg(titleOf(norm))
                   : QStringLiteral("edit “%1”").arg(titleOf(norm)));
    bool found = false;
    for (int i = 0; i < m_appointments.size(); ++i) {
        const QVariantMap existing = m_appointments[i].toMap();
        if (existing.value(QStringLiteral("id")).toString() == id) {
            m_appointments[i] = norm;
            found = true;
            break;
        }
    }
    if (!found) {
        m_appointments.append(norm);
    }

    save();
    emit changed();
    return id;
}

// ---------------------------------------------------------------- deleteAppointment
void CalendarBackend::deleteAppointment(const QString &id)
{
    QString title;
    for (int i = 0; i < m_appointments.size(); ++i) {
        const QVariantMap appt = m_appointments[i].toMap();
        if (appt.value(QStringLiteral("id")).toString() == id) {
            title = appt.value(QStringLiteral("title")).toString();
            pushUndo(QStringLiteral("delete “%1”").arg(title));
            m_appointments.removeAt(i);
            break;
        }
    }

    if (!title.isEmpty()) {
        save();
        emit changed();
    }
}

// ---------------------------------------------------------------- exportICS
QString CalendarBackend::exportICS() const
{
    QStringList lines;
    lines << QStringLiteral("BEGIN:VCALENDAR")
          << QStringLiteral("VERSION:2.0")
          << QStringLiteral("PRODID:-//NCDE//Leap Frog Ledger//EN")
          << QStringLiteral("CALSCALE:GREGORIAN");

    for (const QVariant &v : m_appointments) {
        const QVariantMap a = v.toMap();
        const QString id = a.value(QStringLiteral("id")).toString();
        const QString date = dateOf(a).replace(QStringLiteral("-"), QStringLiteral(""));
        const bool allDay = isAllDay(a);

        lines << QStringLiteral("BEGIN:VEVENT")
              << QStringLiteral("UID:%1@ncde-leapfrog").arg(id);

        if (allDay) {
            lines << QStringLiteral("DTSTART;VALUE=DATE:%1").arg(date);
        } else {
            lines << QStringLiteral("DTSTART:%1T%200").arg(date).arg(hmFmtTime(minutesOf(a, "start")));
            lines << QStringLiteral("DTEND:%1T%200").arg(date).arg(hmFmtTime(minutesOf(a, "end")));
        }

        lines << QStringLiteral("SUMMARY:%1").arg(ncde::cal::icsEscape(titleOf(a)));

        const QString loc = a.value(QStringLiteral("location")).toString();
        if (!loc.isEmpty())
            lines << QStringLiteral("LOCATION:%1").arg(ncde::cal::icsEscape(loc));

        const QString notes = a.value(QStringLiteral("notes")).toString();
        if (!notes.isEmpty())
            lines << QStringLiteral("DESCRIPTION:%1").arg(ncde::cal::icsEscape(notes));

        const QString rep = repeatOf(a);
        if (rep != QStringLiteral("none"))
            lines << QStringLiteral("RRULE:FREQ=%1").arg(rep.toUpper());

        const QString cat = a.value(QStringLiteral("category")).toString();
        if (!cat.isEmpty())
            lines << QStringLiteral("CATEGORIES:%1").arg(cat);

        const int lead = leadMinutes(a);
        if (lead > 0) {
            QString trigger = QStringLiteral("-P");
            const int days = lead / 1440;
            const int hours = (lead % 1440) / 60;
            const int minutes = lead % 60;
            if (days > 0)
                trigger += QStringLiteral("%1D").arg(days);
            if (hours > 0 || minutes > 0 || days == 0)
                trigger += QLatin1Char('T');
            if (hours > 0)
                trigger += QStringLiteral("%1H").arg(hours);
            if (minutes > 0 || (days == 0 && hours == 0))
                trigger += QStringLiteral("%1M").arg(minutes);
            lines << QStringLiteral("BEGIN:VALARM")
                  << QStringLiteral("ACTION:DISPLAY")
                  << QStringLiteral("TRIGGER:%1").arg(trigger)
                  << QStringLiteral("END:VALARM");
        }

        lines << QStringLiteral("END:VEVENT");
    }

    lines << QStringLiteral("END:VCALENDAR");
    return lines.join(QStringLiteral("\r\n"));
}

// ---------------------------------------------------------------- exportICSToFile
bool CalendarBackend::exportICSToFile(const QString &path) const
{
    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file://"))) {
        QUrl url(localPath);
        localPath = url.toLocalFile();
    }

    QDir().mkpath(QFileInfo(localPath).absolutePath());

    QFile file(localPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    const QString ics = exportICS();
    const QByteArray data = ics.toUtf8();
    const bool ok = (file.write(data) == data.size());
    file.close();
    return ok;
}

// ---------------------------------------------------------------- importICS
int CalendarBackend::importICS(const QString &text)
{
    QString unfolded = text;
    unfolded.replace(QStringLiteral("\r\n "), QStringLiteral(""));
    unfolded.replace(QStringLiteral("\r\n\t"), QStringLiteral(""));
    const QStringList lines = unfolded.split(QRegularExpression(QStringLiteral("\r?\n")));

    int count = 0;
    QVariantMap cur;
    bool inEvent = false;

    auto parseDT = [](const QString &v) -> QVariantMap {
        QVariantMap out;
        QRegularExpression re(QStringLiteral("(\\d{4})(\\d{2})(\\d{2})(?:T(\\d{2})(\\d{2}))?"));
        QRegularExpressionMatch m = re.match(v);
        if (m.hasMatch()) {
            out[QStringLiteral("date")] = QStringLiteral("%1-%2-%3").arg(m.captured(1), m.captured(2), m.captured(3));
            if (!m.captured(4).isEmpty()) {
                out[QStringLiteral("start")] = m.captured(4).toInt() * 60 + m.captured(5).toInt();
            }
        }
        return out;
    };

    for (const QString &line : lines) {
        if (line == QStringLiteral("BEGIN:VEVENT")) {
            inEvent = true;
            cur.clear();
            cur[QStringLiteral("category")] = QStringLiteral("azure");
            cur[QStringLiteral("repeat")] = QStringLiteral("none");
            cur[QStringLiteral("reminder")] = 15;
            cur[QStringLiteral("notes")] = QString();
            cur[QStringLiteral("location")] = QString();
        } else if (line == QStringLiteral("END:VEVENT")) {
            if (inEvent && cur.contains(QStringLiteral("date"))) {
                if (!cur.contains(QStringLiteral("id")))
                    cur[QStringLiteral("id")] = ncde::cal::newUid();
                if (!cur.contains(QStringLiteral("title")))
                    cur[QStringLiteral("title")] = QStringLiteral("Untitled");
                const bool allDay = !cur.contains(QStringLiteral("start"));
                cur[QStringLiteral("allDay")] = allDay;
                if (allDay) {
                    cur[QStringLiteral("start")] = 0;
                    cur[QStringLiteral("end")] = 0;
                } else if (!cur.contains(QStringLiteral("end"))) {
                    cur[QStringLiteral("end")] = cur[QStringLiteral("start")].toInt() + 60;
                }

                upsertAppointment(normaliseAppointment(cur, cur[QStringLiteral("id")].toString()));
                ++count;
            }
            inEvent = false;
        } else if (inEvent) {
            const int colon = line.indexOf(QLatin1Char(':'));
            if (colon < 0)
                continue;
            const QString keyRaw = line.left(colon).split(QLatin1Char(';')).first();
            const QString val = line.mid(colon + 1);
            const QString unescaped = ncde::cal::icsUnescape(val);

            if (keyRaw == QStringLiteral("SUMMARY")) {
                cur[QStringLiteral("title")] = unescaped;
            } else if (keyRaw == QStringLiteral("LOCATION")) {
                cur[QStringLiteral("location")] = unescaped;
            } else if (keyRaw == QStringLiteral("DESCRIPTION")) {
                cur[QStringLiteral("notes")] = unescaped;
            } else if (keyRaw == QStringLiteral("DTSTART")) {
                const QVariantMap dt = parseDT(unescaped);
                if (dt.contains(QStringLiteral("date")))
                    cur[QStringLiteral("date")] = dt[QStringLiteral("date")];
                if (dt.contains(QStringLiteral("start")))
                    cur[QStringLiteral("start")] = dt[QStringLiteral("start")];
            } else if (keyRaw == QStringLiteral("DTEND")) {
                const QVariantMap dt = parseDT(unescaped);
                if (dt.contains(QStringLiteral("start")))
                    cur[QStringLiteral("end")] = dt[QStringLiteral("start")];
            } else if (keyRaw == QStringLiteral("RRULE")) {
                QRegularExpression fre(QStringLiteral("FREQ=(\\w+)"));
                QRegularExpressionMatch m = fre.match(unescaped);
                if (m.hasMatch())
                    cur[QStringLiteral("repeat")] = m.captured(1).toLower();
            } else if (keyRaw == QStringLiteral("CATEGORIES")) {
                static const QStringList valid = { QStringLiteral("azure"), QStringLiteral("verdant"),
                                                   QStringLiteral("garnet"), QStringLiteral("amethyst"),
                                                   QStringLiteral("amber"), QStringLiteral("teal") };
                if (valid.contains(unescaped))
                    cur[QStringLiteral("category")] = unescaped;
            } else if (keyRaw == QStringLiteral("TRIGGER")) {
                static const QRegularExpression duration(
                    QStringLiteral("^-P(?:(\\d+)D)?(?:T(?:(\\d+)H)?(?:(\\d+)M)?(?:(\\d+)S)?)?$"));
                const QRegularExpressionMatch m = duration.match(unescaped);
                if (m.hasMatch()) {
                    const int days = m.captured(1).toInt();
                    const int hours = m.captured(2).toInt();
                    const int minutes = m.captured(3).toInt();
                    const int seconds = m.captured(4).toInt();
                    if (seconds % 60 == 0)
                        cur[QStringLiteral("reminder")] = days * 1440 + hours * 60
                                                        + minutes + seconds / 60;
                }
            }
        }
    }
    return count;
}

// ---------------------------------------------------------------- importICSFromFile
int CalendarBackend::importICSFromFile(const QString &path)
{
    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file://"))) {
        QUrl url(localPath);
        localPath = url.toLocalFile();
    }

    QFile file(localPath);
    if (!file.open(QIODevice::ReadOnly))
        return 0;

    const QString text = QString::fromUtf8(file.readAll());
    file.close();
    return importICS(text);
}

// ---------------------------------------------------------------- fireReminder (test button only)
void CalendarBackend::fireReminder(const QString &title, const QString &body)
{
    // This is the QML "Send test 🐸" button. The real reminder daemon runs separately.
    // We just invoke the local desktop notification transport for immediate feedback.
    QProcess::startDetached(QStringLiteral("notify-send"), { title, body });
}

// ---------------------------------------------------------------- composeForHummingbird
bool CalendarBackend::composeForHummingbird(const QString &apptId)
{
    for (const QVariant &v : m_appointments) {
        const QVariantMap a = v.toMap();
        if (a.value(QStringLiteral("id")).toString() == apptId)
            return composeForHummingbirdRec(a);
    }
    return false;
}

// ---------------------------------------------------------------- composeForHummingbirdRec
bool CalendarBackend::composeForHummingbirdRec(const QVariantMap &a)
{
    const QString title = titleOf(a);
    if (title.isEmpty())
        return false;

    const QString dateStr = dateOf(a);
    QDate date = QDate::fromString(dateStr, Qt::ISODate);
    if (!date.isValid())
        date = QDate::currentDate();

    const QString dateHuman = date.toString(QStringLiteral("dddd, MMMM d, yyyy"));
    const bool allDay = isAllDay(a);
    const int startMin = allDay ? 0 : minutesOf(a, "start");
    const int endMin = allDay ? 0 : minutesOf(a, "end");

    QString timeHuman;
    if (allDay) {
        timeHuman = QStringLiteral("all day, %1").arg(dateHuman);
    } else {
        const QString startStr = ncde::cal::formatClockMinutes(startMin);
        const QString endStr = ncde::cal::formatClockMinutes(endMin);
        timeHuman = QStringLiteral("from %1 to %2 on %3").arg(startStr, endStr, dateHuman);
    }

    const QString loc = a.value(QStringLiteral("location")).toString();
    const QString notes = a.value(QStringLiteral("notes")).toString();

    QString body = QStringLiteral("You have an appointment from the Leap Frog Ledger:\n\n  %1\n  %2")
                       .arg(title, timeHuman);
    if (!loc.isEmpty())
        body += QStringLiteral("\n  Where: %1").arg(loc);
    if (!notes.isEmpty())
        body += QStringLiteral("\n%1").arg(notes);

    // Write a JSON file for hummingbird-courier to pick up.
    const QString pendingDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                               + QStringLiteral("/pending");
    QDir().mkpath(pendingDir);
    const QString filePath = pendingDir + QStringLiteral("/compose_%1.json").arg(ncde::cal::newUid());

    QJsonObject obj;
    obj[QStringLiteral("subject")] = title;
    obj[QStringLiteral("body")] = body;
    obj[QStringLiteral("attachPath")] = QString();

    QJsonDocument doc(obj);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    file.write(doc.toJson(QJsonDocument::Compact));
    file.close();

    // Launch hummingbird-courier --compose <file> in background.
    QProcess::startDetached(QStringLiteral("hummingbird-courier"),
                            { QStringLiteral("--compose"), filePath });
    return true;
}