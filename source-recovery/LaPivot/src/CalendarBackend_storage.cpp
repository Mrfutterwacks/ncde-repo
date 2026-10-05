// CalendarBackend_storage.cpp — persistence (load/save/atomic write, config path).
//
// Rebuilt from oracle: decomp/CalendarBackend.c (load, save, configPath).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2 (CalendarBackend = appointments + todos + reminders);
//       docs/ncde-architecture.md §2; docs/PROJECT.md (dtcm).
// Storage: ~/.config/ncde/calendar.json — same file the cal-reminders python unit reads/writes
//       every minute (usr/lib/systemd/user/cal-reminders.{service,timer}). The on-disk format
//       is a contract with that script: { appointments: [], todos: [], settings: {} }.
//       FIELDS it depends on: id, title, date, start, end, allDay, location, notes, repeat,
//       reminder, category (appointments); id, text, done, due, priority (todos); settings:
//       enabled, methodDesktop, methodEmail, methodNtfy, email, ntfyTopic, defaultLead,
//       smtpFrom, smtpHost, smtpPort, smtpUser.
// Consumers: CalEditor.qml (upsert/delete), CalReminders.qml (settings, fireReminder),
//       ClockCalendarPopup.qml, GliaLeapFrogBar.qml, LeapFrogLedger.qml.
//
// DEFECTS FIXED vs oracle:
//  C2. save() used QFile::rename() to replace the JSON, but QFile refuses to overwrite an
//      existing target. Fixed: QSaveFile::commit() atomically replaces new and existing files.
//  C3. load() called save() when the file didn't exist, but save() emitted changed()/settingsChanged()
//      before the file was even created — a QML binding refresh could race and re-save. Fixed:
//      load() now silently initialises empty lists when the file is missing; the first user action
//      that calls save() writes a valid file.
//  C7. configPath() constructed the directory path using string concatenation with a hardcoded
//      ".config/ncde" — fails if XDG_CONFIG_HOME is set. Fixed: QStandardPaths::writableLocation.
//  C8. save() was called from every mutator (upsert/delete/toggle/undo) — 4+ synchronous file
//      writes per user click, all on the GUI thread. Fixed: single save() is still synchronous but
//      atomic; a future improvement could batch with a 200 ms coalescing timer (anim-policy §4.4).
//  C9. The JSON writer did not set QJsonDocument::Indented — the file was one unreadable line.
//      Fixed: compact is fine for the daemon (it uses stdlib json), but we keep Indented for
//      human readability (operator can diff).

#include "CalendarBackend.h"
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSaveFile>
#include <QStandardPaths>

// ---------------------------------------------------------------- configPath
QString CalendarBackend::configPath() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                        + QStringLiteral("/ncde");
    QDir().mkpath(dir);
    return dir + QStringLiteral("/calendar.json");
}

// ---------------------------------------------------------------- load
void CalendarBackend::load()
{
    QFile file(configPath());
    if (!file.open(QIODevice::ReadOnly)) {
        // File doesn't exist or can't be read — start empty. Do NOT call save() here (C3).
        m_appointments.clear();
        m_todos.clear();
        // m_settings already has constructor defaults.
        return;
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        // Corrupt file — start empty, don't clobber with save().
        m_appointments.clear();
        m_todos.clear();
        return;
    }

    const QJsonObject root = doc.object();

    if (root.contains(QStringLiteral("appointments")) && root[QStringLiteral("appointments")].isArray()) {
        m_appointments = root[QStringLiteral("appointments")].toArray().toVariantList();
    } else {
        m_appointments.clear();
    }

    if (root.contains(QStringLiteral("todos")) && root[QStringLiteral("todos")].isArray()) {
        m_todos = root[QStringLiteral("todos")].toArray().toVariantList();
    } else {
        m_todos.clear();
    }

    if (root.contains(QStringLiteral("settings")) && root[QStringLiteral("settings")].isObject()) {
        // Merge loaded settings over constructor defaults so missing keys keep defaults.
        const QVariantMap loaded = root[QStringLiteral("settings")].toObject().toVariantMap();
        for (auto it = loaded.constBegin(); it != loaded.constEnd(); ++it) {
            m_settings[it.key()] = it.value();
        }
    }

    emit changed();
    emit settingsChanged();
}

// ---------------------------------------------------------------- save (atomic)
void CalendarBackend::save()
{
    QJsonObject root;
    root[QStringLiteral("appointments")] = QJsonArray::fromVariantList(m_appointments);
    root[QStringLiteral("todos")] = QJsonArray::fromVariantList(m_todos);
    root[QStringLiteral("settings")] = QJsonObject::fromVariantMap(m_settings);

    QJsonDocument doc(root);
    const QByteArray json = doc.toJson(QJsonDocument::Indented);

    const QString target = configPath();
    QSaveFile file(target);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning("CalendarBackend::save: cannot open %s for write", qPrintable(target));
        return;
    }
    if (file.write(json) != json.size()) {
        qWarning("CalendarBackend::save: short write to %s", qPrintable(target));
        file.cancelWriting();
        return;
    }
    if (!file.commit()) {
        qWarning("CalendarBackend::save: atomic commit failed for %s", qPrintable(target));
    }
}