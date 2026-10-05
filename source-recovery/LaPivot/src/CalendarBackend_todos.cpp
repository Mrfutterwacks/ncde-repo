// CalendarBackend_todos.cpp — todo CRUD, undo, settings.
//
// Rebuilt from oracle: decomp/CalendarBackend.c (upsertTodo, toggleTodo, deleteTodo,
// pushUndo, undo, saveSettings).
// Spec: docs/NCDE-ARCHITECTURE-DIGEST.md §2; docs/ncde-architecture.md §2.
// Consumers: LeapFrogLedger.qml (todo panel, add/toggle/delete).
//
// DEFECTS FIXED vs oracle:
//  C1 (cont.): The oracle's upsertTodo/toggleTodo/deleteTodo each had their own field
//      reading logic. Fixed: shared accessors (not needed here, todos are simpler).
//  C8 (cont.): Each mutator called save() synchronously on the GUI thread.
//      Still true but atomic now; a future improvement could coalesce.
//  C13. undo() returned the label string but the oracle also expected the model to be
//       restored. Fixed: undo() restores both appointments and todos from the snapshot
//       and returns the label (matching the oracle interface).

#include "CalendarBackend.h"
#include "cal_helpers.h"

#include <QDateTime>

// ---------------------------------------------------------------- upsertTodo
QString CalendarBackend::upsertTodo(const QVariantMap &rec)
{
    const QString incomingId = rec.value(QStringLiteral("id")).toString();
    const bool isNew = incomingId.isEmpty();

    QString id = incomingId;
    if (isNew) {
        id = ncde::cal::newUid();
    }

    QVariantMap norm;
    norm[QStringLiteral("id")] = id;
    norm[QStringLiteral("text")] = rec.value(QStringLiteral("text"), QStringLiteral("")).toString();
    norm[QStringLiteral("done")] = rec.value(QStringLiteral("done"), false).toBool();
    norm[QStringLiteral("due")] = rec.value(QStringLiteral("due"), QVariant());
    norm[QStringLiteral("priority")] = rec.value(QStringLiteral("priority"), 0).toInt();

    pushUndo(isNew ? QStringLiteral("new task") : QStringLiteral("edit task"));
    bool found = false;
    for (int i = 0; i < m_todos.size(); ++i) {
        const QVariantMap existing = m_todos[i].toMap();
        if (existing.value(QStringLiteral("id")).toString() == id) {
            m_todos[i] = norm;
            found = true;
            break;
        }
    }
    if (!found) {
        m_todos.append(norm);
    }

    save();
    emit changed();
    return id;
}

// ---------------------------------------------------------------- toggleTodo
void CalendarBackend::toggleTodo(const QString &id)
{
    for (int i = 0; i < m_todos.size(); ++i) {
        QVariantMap todo = m_todos[i].toMap();
        if (todo.value(QStringLiteral("id")).toString() == id) {
        pushUndo(QStringLiteral("task"));
        const bool done = todo.value(QStringLiteral("done")).toBool();
        todo[QStringLiteral("done")] = !done;
        m_todos[i] = todo;

            save();
            emit changed();
            break;
        }
    }
}

// ---------------------------------------------------------------- deleteTodo
void CalendarBackend::deleteTodo(const QString &id)
{
    for (int i = 0; i < m_todos.size(); ++i) {
        const QVariantMap todo = m_todos[i].toMap();
        if (todo.value(QStringLiteral("id")).toString() == id) {
            pushUndo(QStringLiteral("delete task"));
            m_todos.removeAt(i);
            save();
            emit changed();
            break;
        }
    }
}

// ---------------------------------------------------------------- pushUndo
void CalendarBackend::pushUndo(const QString &label)
{
    Snapshot snap(m_appointments, m_todos, label);
    m_undo.append(snap);
    if (m_undo.size() > kUndoDepth)
        m_undo.removeFirst();
}

// ---------------------------------------------------------------- undo
QString CalendarBackend::undo()
{
    if (m_undo.isEmpty())
        return QString();

    const Snapshot snap = m_undo.takeLast();
    m_appointments = snap.appointments;
    m_todos = snap.todos;
    save();
    emit changed();
    return snap.label;
}

// ---------------------------------------------------------------- canUndo
bool CalendarBackend::canUndo() const
{
    return !m_undo.isEmpty();
}

// ---------------------------------------------------------------- saveSettings
void CalendarBackend::saveSettings(const QVariantMap &s)
{
    // Merge provided keys over existing settings (partial update).
    for (auto it = s.constBegin(); it != s.constEnd(); ++it) {
        m_settings[it.key()] = it.value();
    }
    save();
    emit settingsChanged();
}