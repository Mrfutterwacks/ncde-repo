// LeapFrogPond.cpp — constructor, load/save, note CRUD, CSV/.lilypad export, reconcile, archive.
//
// Rebuilt from oracle: decomp/LeapFrogPond.c (ctor, loadNotes, saveNotes, addNote, removeNote,
// removeAppt, setNotice, tally, reconcile, archivePast, exportCsv, exportLilyPad, genId, path).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2; docs/ncde-architecture.md §2; docs/leapfrog-original/.
// Consumers: LeapFrogLedger.qml, GliaLeapFrogBar.qml, PondPopup.qml.
//
// DEFECTS FIXED vs oracle:
//  P1. saveNotes() used QFile::rename() to replace the JSON, but QFile refuses to overwrite
//      an existing target. Fixed: QSaveFile::commit() atomically replaces new and existing files.
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
//      forward — shifting indices caused skips. Fixed: iterate backwards explicitly.
//  P8. tally() returned keys "notes", "appts", "today" but QML (PondPopup) expects
//      "lilyPads", "appointments", "today". Fixed: keys match QML.
//  P9. Constructor connected to CalendarBackend::changed but never disconnected — if
//      CalendarBackend is destroyed first, a dangling pointer remains. Fixed: destroyed()
//      watcher clears the pointer.

#include "LeapFrogPond.h"
#include "CalendarBackend.h"

#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSaveFile>
#include <QStandardPaths>
#include <QUuid>

namespace {

// RFC 4180 CSV quoting: if field contains comma, quote, or newline, wrap in ""
// and escape internal "" as "".
QString csvQuote(const QString &field)
{
    if (field.contains(QLatin1Char(',')) || field.contains(QLatin1Char('"'))
        || field.contains(QLatin1Char('\n')) || field.contains(QLatin1Char('\r'))) {
        QString escaped = field;
        escaped.replace(QLatin1Char('"'), QStringLiteral("\"\""));
        return QStringLiteral("\"%1\"").arg(escaped);
    }
    return field;
}

} // namespace

// ---------------------------------------------------------------- constructor
LeapFrogPond::LeapFrogPond(QObject *parent, CalendarBackend *calBackend)
    : QObject(parent)
    , m_calBackend(calBackend)
{
    loadNotes();

    if (m_calBackend) {
        // When CalendarBackend changes (appointments added/removed), refresh appts property.
        connect(m_calBackend, &CalendarBackend::changed, this, &LeapFrogPond::notesChanged);
        // If CalendarBackend is destroyed first, clear the pointer (P9).
        connect(m_calBackend, &QObject::destroyed, this, [this] { m_calBackend = nullptr; });
    }
}

// ---------------------------------------------------------------- accessors
QVariantList LeapFrogPond::notes() const { return m_notes; }
int LeapFrogPond::noteCount() const { return m_notes.size(); }
QString LeapFrogPond::notice() const { return m_notice; }
QVariantList LeapFrogPond::appts() const
{
    if (!m_calBackend)
        return QVariantList();
    return m_calBackend->appointments();
}

// ---------------------------------------------------------------- configPath
QString LeapFrogPond::configPath() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                        + QStringLiteral("/ncde");
    QDir().mkpath(dir);
    return dir + QStringLiteral("/lilypad.json");
}

// ---------------------------------------------------------------- loadNotes
void LeapFrogPond::loadNotes()
{
    QFile file(configPath());
    if (!file.open(QIODevice::ReadOnly)) {
        m_notes.clear();
        m_notice.clear();
        return;
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        m_notes.clear();
        m_notice.clear();
        return;
    }

    const QJsonObject root = doc.object();

    if (root.contains(QStringLiteral("notes")) && root[QStringLiteral("notes")].isArray()) {
        m_notes = root[QStringLiteral("notes")].toArray().toVariantList();
    } else {
        m_notes.clear();
    }

    if (root.contains(QStringLiteral("notice"))) {
        m_notice = root[QStringLiteral("notice")].toString();
    } else {
        m_notice.clear();
    }
}

// ---------------------------------------------------------------- saveNotes (atomic)
void LeapFrogPond::saveNotes()
{
    QJsonObject root;
    root[QStringLiteral("notes")] = QJsonArray::fromVariantList(m_notes);
    root[QStringLiteral("notice")] = m_notice;

    QJsonDocument doc(root);
    const QByteArray json = doc.toJson(QJsonDocument::Indented);

    const QString target = configPath();
    QSaveFile file(target);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning("LeapFrogPond::saveNotes: cannot open %s for write", qPrintable(target));
        return;
    }
    if (file.write(json) != json.size()) {
        qWarning("LeapFrogPond::saveNotes: short write to %s", qPrintable(target));
        file.cancelWriting();
        return;
    }
    if (!file.commit()) {
        qWarning("LeapFrogPond::saveNotes: atomic commit failed for %s", qPrintable(target));
    }
}

// ---------------------------------------------------------------- genId
QString LeapFrogPond::genId() const
{
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

// ---------------------------------------------------------------- addNote
void LeapFrogPond::addNote(const QString &text)
{
    const QString trimmed = text.trimmed();
    if (trimmed.isEmpty())
        return;

    QVariantMap note;
    note[QStringLiteral("id")] = genId();
    note[QStringLiteral("text")] = trimmed;
    note[QStringLiteral("created")] = QDateTime::currentDateTime().toString(Qt::ISODate);

    m_notes.append(note);
    saveNotes();
    emit notesChanged();
}

// ---------------------------------------------------------------- removeNote
void LeapFrogPond::removeNote(const QString &id)
{
    for (int i = 0; i < m_notes.size(); ++i) {
        const QVariantMap note = m_notes[i].toMap();
        if (note.value(QStringLiteral("id")).toString() == id) {
            m_notes.removeAt(i);
            saveNotes();
            emit notesChanged();
            break;
        }
    }
}

// ---------------------------------------------------------------- removeAppt (delegates to CalendarBackend)
void LeapFrogPond::removeAppt(const QString &id)
{
    if (m_calBackend)
        m_calBackend->deleteAppointment(id);
}

// ---------------------------------------------------------------- setNotice
void LeapFrogPond::setNotice(const QString &t)
{
    if (m_notice != t) {
        m_notice = t;
        saveNotes();
        emit noticeChanged();
    }
}

// ---------------------------------------------------------------- tally
QVariantMap LeapFrogPond::tally()
{
    QVariantMap result;
    result[QStringLiteral("lilyPads")] = m_notes.size();  // P8: QML expects "lilyPads"

    const int apptsCount = m_calBackend ? m_calBackend->appointments().size() : 0;
    result[QStringLiteral("appointments")] = apptsCount;  // P8: QML expects "appointments"

    // Notes created today.
    const QString todayIso = QDate::currentDate().toString(Qt::ISODate);
    int todayCount = 0;
    for (const QVariant &v : m_notes) {
        const QVariantMap note = v.toMap();
        const QString created = note.value(QStringLiteral("created")).toString();
        if (created.startsWith(todayIso))
            ++todayCount;
    }
    result[QStringLiteral("today")] = todayCount;

    return result;
}

// ---------------------------------------------------------------- reconcile
int LeapFrogPond::reconcile()
{
    const QDateTime cutoff = QDateTime::currentDateTime().addDays(-30); // 30 days old
    int removed = 0;

    // Iterate BACKWARDS so removeAt doesn't shift unprocessed indices (P7).
    for (int i = m_notes.size() - 1; i >= 0; --i) {
        const QVariantMap note = m_notes[i].toMap();
        const QString createdStr = note.value(QStringLiteral("created")).toString();
        QDateTime created = QDateTime::fromString(createdStr, Qt::ISODate);
        if (!created.isValid())
            continue;
        if (created < cutoff) {
            m_notes.removeAt(i);
            ++removed;
        }
    }

    if (removed > 0) {
        saveNotes();
        emit notesChanged();
    }
    emit reconciled(removed);
    return removed;
}

// ---------------------------------------------------------------- archivePast
int LeapFrogPond::archivePast()
{
    int removed = 0;
    if (m_calBackend) {
        const QString todayIso = QDate::currentDate().toString(Qt::ISODate);
        const QVariantList appts = m_calBackend->appointments();

        // Iterate a COPY since we're deleting from CalendarBackend.
        for (const QVariant &v : appts) {
            const QVariantMap a = v.toMap();
            const QString date = a.value(QStringLiteral("date")).toString();
            const QString recur = a.value(QStringLiteral("repeat")).toString().toLower();

            // Archive if date < today AND not recurring.
            if (date < todayIso && recur == QStringLiteral("none")) {
                const QString id = a.value(QStringLiteral("id")).toString();
                if (!id.isEmpty()) {
                    m_calBackend->deleteAppointment(id);
                    ++removed;
                }
            }
        }
    }
    emit archived(removed);  // P6: notify Ledger to refresh
    return removed;
}

// ---------------------------------------------------------------- exportCsv
QString LeapFrogPond::exportCsv(const QString &path)
{
    QString outPath = path;
    if (outPath.isEmpty()) {
        outPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                  + QStringLiteral("/leapfrog.csv");
    }

    QFile file(outPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        emit exported(QString());
        return QString();
    }

    const QVariantList appts = this->appts();

    // Header
    file.write("date,time,title,notes\n");

    for (const QVariant &v : appts) {
        const QVariantMap a = v.toMap();
        const bool allDay = a.value(QStringLiteral("allDay")).toBool();

        QString timeCol;
        if (allDay) {
            timeCol = QStringLiteral("all day");
        } else {
            const int start = a.value(QStringLiteral("start")).toInt();
            const int h = start / 60;
            const int m = start % 60;
            timeCol = QStringLiteral("%1:%2").arg(h, 2, 10, QLatin1Char('0'))
                                         .arg(m, 2, 10, QLatin1Char('0'));
        }

        const QString date = a.value(QStringLiteral("date")).toString();
        const QString title = a.value(QStringLiteral("title")).toString();
        const QString notes = a.value(QStringLiteral("notes")).toString();

        QString line = csvQuote(date) + QLatin1Char(',')
                     + csvQuote(timeCol) + QLatin1Char(',')
                     + csvQuote(title) + QLatin1Char(',')
                     + csvQuote(notes) + QLatin1Char('\n');
        file.write(line.toUtf8());
    }

    file.close();
    emit exported(outPath);
    return outPath;
}

// ---------------------------------------------------------------- exportLilyPad
QString LeapFrogPond::exportLilyPad(const QString &path)
{
    QString outPath = path;
    if (outPath.isEmpty()) {
        outPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                  + QStringLiteral("/leapfrog.lilypad");
    }

    QJsonObject root;
    root[QStringLiteral("notes")] = QJsonArray::fromVariantList(m_notes);
    root[QStringLiteral("notice")] = m_notice;
    root[QStringLiteral("appts")] = QJsonArray::fromVariantList(this->appts());

    QJsonDocument doc(root);
    const QByteArray json = doc.toJson(QJsonDocument::Indented);

    QFile file(outPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        emit exported(QString());
        return QString();
    }
    file.write(json);
    file.close();

    emit exported(outPath);
    return outPath;
}

// ---------------------------------------------------------------- declared additions
void LeapFrogPond::reload()
{
    loadNotes();
    emit notesChanged();
    emit noticeChanged();
}

QString LeapFrogPond::configFilePath() const
{
    return configPath();
}