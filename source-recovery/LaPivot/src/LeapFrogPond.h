// LeapFrogPond.h — the `pond` context object: notes + appointments organiser, CSV/.lilypad export.
//
// Rebuilt from oracle: decomp/LeapFrogPond.c (29 functions; 21 real + 8 moc/trivial).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2 (LeapFrogPond = notes + appointments organiser;
//       exports CSV and .lilypad); docs/ncde-architecture.md §2; docs/leapfrog-original/.
// Consumers: LeapFrogLedger.qml (rail items: Stock/Tally/Export/Reconcile/Archive/Season/Manual),
//       GliaLeapFrogBar.qml (menu actions), PondPopup.qml (stock/tally popups).
// Storage: ~/.config/ncde/lilypad.json — { notes: [], notice: "" }.
//       Distinct from CalendarBackend's calendar.json.
//
// DEFECTS FIXED vs oracle (numbered, continue from CalendarBackend):
//  P1. saveNotes() was NOT atomic — same truncation risk as CalendarBackend::save() (C2).
//      Fixed: write .tmp, fsync, rename().
//  P2. loadNotes() called saveNotes() when file missing (like C3).
//      Fixed: silent empty init.
//  P3. exportCsv() wrote CSV WITHOUT QUOTING — fields containing commas, quotes, or newlines
//      broke the CSV. Fixed: RFC 4180 quoting (double quotes escaped as "", field wrapped in "").
//  P4. exportCsv() used a hardcoded format string with positional args — locale-dependent
//      and fragile. Fixed: explicit field ordering, quoted strings.
//  P5. genId() returned QUuid::toString().left(8) — only 8 chars, collision-prone.
//      Fixed: full UUID (36 chars), matching CalendarBackend::newUid().
//  P6. archivePast() deleted appointments from CalendarBackend directly via deleteAppointment()
//      but did NOT emit a signal for the Ledger's appointment views to refresh. Fixed:
//      emits archived(count) after deletion; Ledger connects to it.
//  P7. reconcile() iterated notes from newest to oldest but removed by index while iterating
//      forward — shifting indices caused skips. Fixed: iterate backwards (oracle did this
//      correctly in the decomp but the logic was fragile; we make it explicit).
//  P8. tally() returned a QVariantMap with keys "notes", "appts", "today" but the QML
//      (PondPopup.qml) expects "lilyPads", "appointments", "today". Fixed: keys match QML.
//  P9. The constructor connected to CalendarBackend::changed but never disconnected — if
//      CalendarBackend is destroyed first, a dangling pointer remains. Fixed: destroyed()
//      watcher clears the pointer (like NCDEGeo::setLelan G5).

#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QString>

class CalendarBackend;

class LeapFrogPond : public QObject
{
    Q_OBJECT

    // ---- oracle interface (interfaces/LaPivot-metaobjects.h; verified by tests/iface_check.sh) ----
    Q_PROPERTY(QVariantList notes READ notes NOTIFY notesChanged)
    Q_PROPERTY(int noteCount READ noteCount NOTIFY notesChanged)
    Q_PROPERTY(QString notice READ notice WRITE setNotice NOTIFY noticeChanged)
    Q_PROPERTY(QVariantList appts READ appts NOTIFY notesChanged)
    // ---- end oracle interface ----

public:
    explicit LeapFrogPond(QObject *parent = nullptr, CalendarBackend *calBackend = nullptr);

    QVariantList notes() const;
    int noteCount() const;
    QString notice() const;
    QVariantList appts() const;

    Q_INVOKABLE void addNote(const QString &text);
    Q_INVOKABLE void removeNote(const QString &id);
    Q_INVOKABLE void removeAppt(const QString &id);
    Q_INVOKABLE void setNotice(const QString &t);
    Q_INVOKABLE QVariantMap tally();
    Q_INVOKABLE int reconcile();
    Q_INVOKABLE int archivePast();
    Q_INVOKABLE QString exportCsv(const QString &path = QString());
    Q_INVOKABLE QString exportLilyPad(const QString &path = QString());

    // ---- declared additions (see tests/iface_additions/LeapFrogPond.txt) ----
    // Reload lilypad.json from disk (symmetry with CalendarBackend::reload).
    Q_INVOKABLE void reload();
    // Full path to lilypad.json (for debugging / tests).
    Q_INVOKABLE QString configFilePath() const;
    // ---- end additions ----

signals:
    void notesChanged();
    void noticeChanged();
    void archived(int count);
    void exported(QString path);
    void reconciled(int count);

private:
    QString configPath() const;
    void loadNotes();
    void saveNotes();                                 // atomic (P1)
    QString genId() const;

    QVariantList m_notes;        // oracle field offset +0x18
    QString m_notice;            // oracle +0x30
    CalendarBackend *m_calBackend = nullptr;  // oracle +0x10
};