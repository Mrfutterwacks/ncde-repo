// CalendarBackend.h — the `calBackend` context object: appointments, todos, reminders,
// ICS import/export, and the Hummingbird hand-off.
//
// Rebuilt from oracle: decomp/CalendarBackend.c (40 functions; 27 real + 13 moc/trivial),
// plus the shared helpers uid()/icsEsc()/icsUnesc()/hmFmtTime() from decomp/_global.c.
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2 row "NCDECalendar" (LIVE: renamed to
//       `CalendarBackend`, 330 syms, exposed as `calBackend`; "Rename divergence D4")
//       and its §3 note ("CalendarBackend vs NCDECalendar contract: the QML `calBackend`
//       contract should be validated against the live `CalendarBackend` method set");
//       docs/ncde-architecture.md §2 (NCDECalendar = appointments + todos + reminders);
//       docs/PROJECT.md (dtcm -> NCDECalendar, the CDE app-suite lineage).
// Consumers: CalEditor.qml (upsert/delete, settings.defaultLead), CalReminders.qml
//       (settings, fireReminder "Send test", upcomingReminders), ClockCalendarPopup.qml,
//       GliaLeapFrogBar.qml (composeForHummingbird, exportICSToFile),
//       LeapFrogLedger.qml (importICSFromFile, todos, upsertAppointment for drag/resize,
//       exportICSToFile, Cal.searchAll).
// Storage: ~/.config/ncde/calendar.json — the same file the `cal-reminders` python
//       user unit (usr/lib/systemd/user/cal-reminders.{service,timer}, every 60 s) reads
//       AND writes, so the on-disk format is a contract with that script (see
//       reports/calendar.md for the field list it depends on).
//
// Live reminder delivery is NOT in this class: fireReminder() is the QML "Send test
// button" only; the daemon decides when a reminder is due and then uses the same
// transports (notify-send / msmtp / curl ntfy). This class therefore schedules nothing
// of its own and owns no timer (anim-policy.md §4.4).

#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

class CalendarBackend : public QObject
{
    Q_OBJECT

    // ---- oracle interface (interfaces/LaPivot-metaobjects.h; verified by tests/iface_check.sh) ----
    Q_PROPERTY(QVariantList appointments READ appointments NOTIFY changed)
    Q_PROPERTY(QVariantList todos READ todos NOTIFY changed)
    Q_PROPERTY(QVariantMap settings READ settings NOTIFY settingsChanged)
    // ---- end oracle interface ----

public:
    // oracle: pushUndo appends then `if (size() > 50) removeFirst()` -> 50 deep
    static constexpr int kUndoDepth = 50;

    struct Snapshot {
        QVariantList appointments;
        QVariantList todos;
        QString label;
        Snapshot() = default;
        Snapshot(QVariantList a, QVariantList t, const QString &l)
            : appointments(std::move(a)), todos(std::move(t)), label(l) {}
    };

    explicit CalendarBackend(QObject *parent = nullptr);

    QVariantList appointments() const;
    QVariantList todos() const;
    QVariantMap settings() const;

    Q_INVOKABLE QString upsertAppointment(const QVariantMap &rec);
    Q_INVOKABLE void deleteAppointment(const QString &id);
    Q_INVOKABLE QString upsertTodo(const QVariantMap &rec);
    Q_INVOKABLE void toggleTodo(const QString &id);
    Q_INVOKABLE void deleteTodo(const QString &id);
    Q_INVOKABLE void saveSettings(const QVariantMap &s);
    Q_INVOKABLE QString undo();
    Q_INVOKABLE bool canUndo() const;
    Q_INVOKABLE QString exportICS() const;
    Q_INVOKABLE bool exportICSToFile(const QString &path) const;
    Q_INVOKABLE int importICS(const QString &text);
    Q_INVOKABLE int importICSFromFile(const QString &path);
    Q_INVOKABLE void fireReminder(const QString &title, const QString &body);
    Q_INVOKABLE bool composeForHummingbird(const QString &apptId);
    Q_INVOKABLE bool composeForHummingbirdRec(const QVariantMap &appt);

    // ---- declared additions (see tests/iface_additions/CalendarBackend.txt) ----
    // Re-read calendar.json from disk. NOTE (corrected 2026-10-04): the previous
    // comment here claimed "the cal-reminders unit rewrites it out of process every
    // minute; without this the shell's copy drifts and the next save() would clobber
    // the daemon's appends". That is false — checked against the installed daemon:
    // its docstring says it READS calendar.json (cal-reminders:4) and the only file
    // it ever writes is calendar.fired (cal-reminders:115). It never appends to
    // calendar.json, so there were no appends to clobber. reload() exists for the
    // real case: any other process or an editor touching calendar.json behind the
    // shell's back. It is called from the Ledger when its window becomes active.
    Q_INVOKABLE void reload();
    Q_INVOKABLE QString configFilePath() const;
    // The due rule, shared with the daemon so the popup list and the firing agree.
    Q_INVOKABLE QVariantList dueReminders(int horizonDays = 0) const;
    // True when a delivery method can actually deliver right now. A checkbox that
    // cannot deliver silently is a defect the operator must see (see DEFECT C4).
    Q_INVOKABLE bool canDeliver(const QString &method) const;
    Q_INVOKABLE QString lastDeliveryError() const;
    // ---- end additions ----

signals:
    void changed();
    void settingsChanged();

private:
    QString configPath() const;
    void load();
    void save();                                 // atomic (DEFECT C2)
    void pushUndo(const QString &label);

    // transports (oracle privates sendEmail/sendNtfy)
    void sendEmail(const QString &title, const QString &body);
    void sendNtfy(const QString &body);
    // All three transports, off the GUI thread where they block (DEFECT C5).
    void deliver(const QString &title, const QString &body);

    QList<Snapshot> m_undo;        // oracle field offset +0x10
    QVariantList m_appointments;   // oracle +0x28
    QVariantList m_todos;          // oracle +0x40
    QVariantMap m_settings;        // oracle +0x58

    QString m_lastDeliveryError;
};
