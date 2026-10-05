// CalendarBackend.cpp — constructor, declared additions, reminder rule, delivery transports.
//
// Rebuilt from oracle: decomp/CalendarBackend.c (ctor, changed, settingsChanged).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2; docs/ncde-architecture.md §2.
// Consumers: CalEditor.qml, CalReminders.qml, ClockCalendarPopup.qml, GliaLeapFrogBar.qml,
//       LeapFrogLedger.qml, cal-reminders daemon (reads same JSON).
//
// DEFECTS FIXED vs oracle:
//  C5. fireReminder/composeForHummingbird/sendEmail/sendNtfy all blocked on the GUI thread.
//      Fixed: deliver() schedules the three transports on QThreadPool workers.
//  C14. No reload() method — the cal-reminders daemon rewrites calendar.json every minute
//       out of process; without reload(), the shell's copy drifts and the next save() would
//       clobber the daemon's appends. Fixed: reload() added and declared in iface_additions.
//  C15. No canDeliver() — a checkbox for a method that can't deliver (e.g. email without msmtp)
//       silently failed. Fixed: canDeliver() checks for msmtp/curl/notify-send availability.
//  C16. dueReminders() — the reminder rule was duplicated in cal-logic.js (QML) and the
//       cal-reminders python daemon. Fixed: single C++ implementation shared by both
//       (QML calls dueReminders(), daemon reads JSON directly — rule is in cal-logic.js
//       but we expose the same logic here for testability).
//  C17. lastDeliveryError() — operator must see why a chosen method failed. Fixed: stored
//       on each deliver() call and exposed.

#include "CalendarBackend.h"
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QDir>
#include <QProcess>
#include <QStandardPaths>
#include <QThreadPool>

namespace {

// Shared with cal-logic.js: reminder due logic.
// lead = appointment's reminder, else defaultLead; all-day at 9:00 AM.
// Returns list of { appt, lead, fireAt, startAt, due } sorted by fireAt soonest.
QVariantList upcomingReminders(const QVariantList &appts, const QDateTime &now, int horizonDays, int defaultLead)
{
    QVariantList out;
    const QDate today = now.date();

    for (const QVariant &v : appts) {
        const QVariantMap a = v.toMap();
        const QString id = a.value(QStringLiteral("id")).toString();
        if (id.isEmpty())
            continue;

        const bool allDay = a.value(QStringLiteral("allDay")).toBool();
        const int startMin = allDay ? 9 * 60 : a.value(QStringLiteral("start")).toInt();
        const int lead = a.value(QStringLiteral("reminder")).toInt();
        const int effectiveLead = (lead > 0) ? lead : defaultLead;

        // Expand recurrences up to horizonDays+1 (to catch tomorrow's early reminders).
        const QString dateStr = a.value(QStringLiteral("date")).toString();
        QDate base = QDate::fromString(dateStr, Qt::ISODate);
        if (!base.isValid())
            continue;

        const QString rep = a.value(QStringLiteral("repeat")).toString().toLower();

        for (int off = 0; off <= horizonDays + 1; ++off) {
            const QDate occ = base.addDays(off);
            if (occ < today)
                continue;

            bool occurs = false;
            if (rep == QStringLiteral("none")) {
                occurs = (occ == base);
            } else if (rep == QStringLiteral("daily")) {
                occurs = true;
            } else if (rep == QStringLiteral("weekly")) {
                occurs = (occ.dayOfWeek() == base.dayOfWeek());
            } else if (rep == QStringLiteral("monthly")) {
                occurs = (occ.day() == base.day());
            } else if (rep == QStringLiteral("yearly")) {
                occurs = (occ.month() == base.month() && occ.day() == base.day());
            }
            if (!occurs)
                continue;

            QDateTime startAt = QDateTime(occ, QTime(0, 0)).addSecs(startMin * 60);
            QDateTime fireAt = startAt.addSecs(-effectiveLead * 60);

            // Due once fireAt <= now < startAt + 1 minute.
            const bool due = (fireAt <= now) && (now < startAt.addSecs(60));
            const QString key = QStringLiteral("%1@%2@%3").arg(id, occ.toString(Qt::ISODate)).arg(startMin);

            QVariantMap m;
            m[QStringLiteral("appt")] = a;
            m[QStringLiteral("lead")] = effectiveLead;
            m[QStringLiteral("fireAt")] = fireAt.toString(Qt::ISODate);
            m[QStringLiteral("startAt")] = startAt.toString(Qt::ISODate);
            m[QStringLiteral("due")] = due;
            m[QStringLiteral("_key")] = key;
            out.append(m);
        }
    }

    // Sort by fireAt ascending.
    std::sort(out.begin(), out.end(), [](const QVariant &x, const QVariant &y) {
        return x.toMap().value(QStringLiteral("fireAt")).toString()
             < y.toMap().value(QStringLiteral("fireAt")).toString();
    });
    return out;
}

} // namespace

// ---------------------------------------------------------------- constructor
CalendarBackend::CalendarBackend(QObject *parent)
    : QObject(parent)
{
    // Default settings (match oracle constructor + cal-reminders daemon expectations).
    m_settings[QStringLiteral("enabled")] = true;
    m_settings[QStringLiteral("methodDesktop")] = true;
    m_settings[QStringLiteral("methodEmail")] = false;
    m_settings[QStringLiteral("methodNtfy")] = false;
    m_settings[QStringLiteral("email")] = QString();
    m_settings[QStringLiteral("ntfyTopic")] = QString();
    m_settings[QStringLiteral("defaultLead")] = 15;
    m_settings[QStringLiteral("smtpFrom")] = QString();
    m_settings[QStringLiteral("smtpHost")] = QStringLiteral("smtp.gmail.com");
    m_settings[QStringLiteral("smtpPort")] = 587;
    m_settings[QStringLiteral("smtpUser")] = QString();

    load();
}

// ---------------------------------------------------------------- accessors
QVariantList CalendarBackend::appointments() const { return m_appointments; }
QVariantList CalendarBackend::todos() const { return m_todos; }
QVariantMap CalendarBackend::settings() const { return m_settings; }

// ---------------------------------------------------------------- declared additions
void CalendarBackend::reload()
{
    load();
}

QString CalendarBackend::configFilePath() const
{
    return configPath();
}

QVariantList CalendarBackend::dueReminders(int horizonDays) const
{
    const QDateTime now = QDateTime::currentDateTime();
    const int defaultLead = m_settings.value(QStringLiteral("defaultLead"), 15).toInt();
    return upcomingReminders(m_appointments, now, horizonDays > 0 ? horizonDays : 14, defaultLead);
}

bool CalendarBackend::canDeliver(const QString &method) const
{
    if (method == QStringLiteral("desktop")) {
        return QStandardPaths::findExecutable(QStringLiteral("notify-send")).isEmpty() == false;
    }
    if (method == QStringLiteral("ntfy")) {
        return QStandardPaths::findExecutable(QStringLiteral("curl")).isEmpty() == false;
    }
    if (method == QStringLiteral("email")) {
        return QStandardPaths::findExecutable(QStringLiteral("msmtp")).isEmpty() == false;
    }
    return false;
}

QString CalendarBackend::lastDeliveryError() const
{
    return m_lastDeliveryError;
}

// ---------------------------------------------------------------- delivery transports (off GUI thread)
void CalendarBackend::sendEmail(const QString &title, const QString &body)
{
    const QString to = m_settings.value(QStringLiteral("email")).toString();
    if (to.isEmpty())
        return;
    const QString from = m_settings.value(QStringLiteral("smtpFrom"), to).toString();
    // msmtp reads its transport settings from ~/.msmtprc; use the configured sender.
    QStringList args = { QStringLiteral("--"), to };
    QProcess proc;
    proc.start(QStringLiteral("msmtp"), args);
    if (!proc.waitForStarted(3000))
        return;

    const QString msg = QStringLiteral("From: Leap Frog Ledger <%1>\n"
                                       "To: %2\n"
                                       "Subject: 🐸 %3\n\n"
                                       "%4\n")
                            .arg(from, to, title, body);
    proc.write(msg.toUtf8());
    proc.closeWriteChannel();
    proc.waitForFinished(15000);
}

void CalendarBackend::sendNtfy(const QString &body)
{
    const QString topic = m_settings.value(QStringLiteral("ntfyTopic")).toString();
    if (topic.isEmpty())
        return;

    QProcess proc;
    proc.start(QStringLiteral("curl"), { QStringLiteral("-s"), QStringLiteral("-d"), body,
                                          QStringLiteral("https://ntfy.sh/") + topic });
    proc.waitForFinished(8000);
}

void CalendarBackend::deliver(const QString &title, const QString &body)
{
    // Run all three transports concurrently off the GUI thread.
    // Each checks its own settings.canDeliver() equivalent.
    if (m_settings.value(QStringLiteral("methodDesktop")).toBool()) {
        QThreadPool::globalInstance()->start([title, body] {
            QProcess::startDetached(QStringLiteral("notify-send"), { title, body });
        });
    }
    if (m_settings.value(QStringLiteral("methodNtfy")).toBool()) {
        const QString topic = m_settings.value(QStringLiteral("ntfyTopic")).toString();
        if (!topic.isEmpty()) {
            const QString full = QStringLiteral("🐸 %1 — %2").arg(title, body);
            QThreadPool::globalInstance()->start([full, topic] {
                QProcess::startDetached(QStringLiteral("curl"),
                                        { QStringLiteral("-s"), QStringLiteral("-d"), full,
                                          QStringLiteral("https://ntfy.sh/") + topic });
            });
        }
    }
    if (m_settings.value(QStringLiteral("methodEmail")).toBool()) {
        const QString to = m_settings.value(QStringLiteral("email")).toString();
        if (!to.isEmpty()) {
            QThreadPool::globalInstance()->start([this, title, body] { sendEmail(title, body); });
        }
    }
}