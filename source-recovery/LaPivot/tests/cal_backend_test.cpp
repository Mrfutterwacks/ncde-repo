// cal_backend_test.cpp — CalendarBackend unit tests (offscreen, scratch HOME).
//
// Tests cover: load/save atomicity, appointment/todo CRUD, undo, ICS round-trip,
// reminder due logic, delivery canDeliver, composeForHummingbirdRec.
// Never touches the operator's real ~/.config/ncde/calendar.json.

#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "CalendarBackend.h"

class CalBackendTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testDefaultSettings();
    void testLoadMissingFile();
    void testSaveAtomic();
    void testUpsertAppointmentNew();
    void testUpsertAppointmentEdit();
    void testDeleteAppointment();
    void testUpsertTodo();
    void testToggleTodo();
    void testDeleteTodo();
    void testUndoStack();
    void testExportICS();
    void testImportICS();
    void testICSIdentityRoundTrip();
    void testReminderDueLogic();
    void testCanDeliver();
    void testComposeForHummingbirdRec();
    void testReloadAfterExternalWrite();
    void testConfigFilePath();

private:
    QTemporaryDir m_tempDir;
    QString m_oldConfig;
    QByteArray m_oldHome;
    CalendarBackend *m_backend = nullptr;
};

void CalBackendTest::initTestCase()
{
    // Redirect QStandardPaths::ConfigLocation to our temp dir.
    m_oldConfig = qgetenv("XDG_CONFIG_HOME");
    m_oldHome = qgetenv("HOME");
    qputenv("XDG_CONFIG_HOME", m_tempDir.path().toUtf8());
    qputenv("HOME", m_tempDir.path().toUtf8());
    QStandardPaths::setTestModeEnabled(true);
    QCOMPARE(QStandardPaths::writableLocation(QStandardPaths::HomeLocation), m_tempDir.path());
}

void CalBackendTest::cleanupTestCase()
{
    if (m_oldConfig.isEmpty())
        qunsetenv("XDG_CONFIG_HOME");
    else
        qputenv("XDG_CONFIG_HOME", m_oldConfig.toUtf8());
    if (m_oldHome.isEmpty())
        qunsetenv("HOME");
    else
        qputenv("HOME", m_oldHome);
}

void CalBackendTest::init()
{
    QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
         + QStringLiteral("/ncde")).removeRecursively();
    m_backend = new CalendarBackend();
}

void CalBackendTest::cleanup()
{
    delete m_backend;
    m_backend = nullptr;
}

// ---------------------------------------------------------------- default settings
void CalBackendTest::testDefaultSettings()
{
    const QVariantMap s = m_backend->settings();
    QVERIFY(s.value("enabled").toBool() == true);
    QVERIFY(s.value("methodDesktop").toBool() == true);
    QVERIFY(s.value("methodEmail").toBool() == false);
    QVERIFY(s.value("methodNtfy").toBool() == false);
    QVERIFY(s.value("defaultLead").toInt() == 15);
    QVERIFY(s.value("smtpHost").toString() == "smtp.gmail.com");
    QVERIFY(s.value("smtpPort").toInt() == 587);
}

// ---------------------------------------------------------------- load missing file
void CalBackendTest::testLoadMissingFile()
{
    // No file exists yet — lists should be empty, no crash.
    QVERIFY(m_backend->appointments().isEmpty());
    QVERIFY(m_backend->todos().isEmpty());
    QVERIFY(m_backend->canUndo() == false);
}

// ---------------------------------------------------------------- save atomic (C2)
void CalBackendTest::testSaveAtomic()
{
    m_backend->upsertAppointment({{"title", "Test"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});
    m_backend->upsertAppointment({{"title", "Second"}, {"date", "2026-10-02"}, {"start", 600}, {"end", 660}});
    const QString path = m_backend->configFilePath();
    QVERIFY(QFile::exists(path));

    // File should be valid JSON.
    QFile f(path);
    QVERIFY(f.open(QIODevice::ReadOnly));
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    QVERIFY(err.error == QJsonParseError::NoError);
    QVERIFY(doc.isObject());
    const QVariantMap root = doc.object().toVariantMap();
    QVERIFY(root["appointments"].toList().size() == 2);
}

// ---------------------------------------------------------------- upsert new appointment
void CalBackendTest::testUpsertAppointmentNew()
{
    QString id = m_backend->upsertAppointment({
        {"title", "New Appt"},
        {"date", "2026-10-01"},
        {"start", 540},
        {"end", 600},
        {"allDay", false},
        {"location", "Office"},
        {"notes", "Bring laptop"},
        {"repeat", "none"},
        {"reminder", 15},
        {"category", "azure"}
    });

    QVERIFY(!id.isEmpty());
    QVERIFY(id.length() == 36); // full UUID (C10)
    QVERIFY(m_backend->appointments().size() == 1);
    const QVariantMap a = m_backend->appointments().first().toMap();
    QVERIFY(a["title"].toString() == "New Appt");
    QVERIFY(a["id"].toString() == id);
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- upsert edit appointment
void CalBackendTest::testUpsertAppointmentEdit()
{
    QString id = m_backend->upsertAppointment({{"title", "Original"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});
    m_backend->upsertAppointment({{"id", id}, {"title", "Edited"}, {"date", "2026-10-01"}, {"start", 600}, {"end", 660}});

    QVERIFY(m_backend->appointments().size() == 1);
    const QVariantMap a = m_backend->appointments().first().toMap();
    QVERIFY(a["title"].toString() == "Edited");
    QVERIFY(a["start"].toInt() == 600);
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- delete appointment
void CalBackendTest::testDeleteAppointment()
{
    QString id = m_backend->upsertAppointment({{"title", "To Delete"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});
    QVERIFY(m_backend->appointments().size() == 1);
    m_backend->deleteAppointment(id);
    QVERIFY(m_backend->appointments().isEmpty());
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- upsert todo
void CalBackendTest::testUpsertTodo()
{
    QString id = m_backend->upsertTodo({{"text", "Buy milk"}, {"done", false}, {"priority", 1}});
    QVERIFY(!id.isEmpty());
    QVERIFY(m_backend->todos().size() == 1);
    const QVariantMap t = m_backend->todos().first().toMap();
    QVERIFY(t["text"].toString() == "Buy milk");
    QVERIFY(t["done"].toBool() == false);
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- toggle todo
void CalBackendTest::testToggleTodo()
{
    QString id = m_backend->upsertTodo({{"text", "Task"}, {"done", false}});
    m_backend->toggleTodo(id);
    QVERIFY(m_backend->todos().first().toMap()["done"].toBool() == true);
    m_backend->toggleTodo(id);
    QVERIFY(m_backend->todos().first().toMap()["done"].toBool() == false);
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- delete todo
void CalBackendTest::testDeleteTodo()
{
    QString id = m_backend->upsertTodo({{"text", "To Delete"}, {"done", false}});
    QVERIFY(m_backend->todos().size() == 1);
    m_backend->deleteTodo(id);
    QVERIFY(m_backend->todos().isEmpty());
    QVERIFY(m_backend->canUndo() == true);
}

// ---------------------------------------------------------------- undo stack
void CalBackendTest::testUndoStack()
{
    QString id1 = m_backend->upsertAppointment({{"title", "A1"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});
    QString id2 = m_backend->upsertAppointment({{"title", "A2"}, {"date", "2026-10-02"}, {"start", 600}, {"end", 660}});
    m_backend->upsertTodo({{"text", "T1"}, {"done", false}});

    QVERIFY(m_backend->appointments().size() == 2);
    QVERIFY(m_backend->todos().size() == 1);

    QString label = m_backend->undo(); // undo todo
    QVERIFY(label == "new task");
    QVERIFY(m_backend->todos().isEmpty());
    QVERIFY(m_backend->appointments().size() == 2);

    label = m_backend->undo(); // undo A2
    QVERIFY(label.contains("new"));
    QVERIFY(m_backend->appointments().size() == 1);
    QVERIFY(m_backend->appointments().first().toMap()["id"].toString() == id1);

    label = m_backend->undo(); // undo A1
    QVERIFY(label.contains("new"));
    QVERIFY(m_backend->appointments().isEmpty());

    QVERIFY(m_backend->canUndo() == false);
    QVERIFY(m_backend->undo().isEmpty()); // undo on empty stack returns empty
}

// ---------------------------------------------------------------- exportICS
void CalBackendTest::testExportICS()
{
    m_backend->upsertAppointment({{"title", "Meeting"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}, {"location", "Room 1"}, {"notes", "Bring slides"}, {"repeat", "weekly"}, {"reminder", 15}, {"category", "garnet"}});
    m_backend->upsertAppointment({{"title", "Birthday"}, {"date", "2026-12-25"}, {"start", 0}, {"end", 0}, {"allDay", true}, {"repeat", "yearly"}, {"reminder", 1440}, {"category", "amethyst"}});

    QString ics = m_backend->exportICS();
    QVERIFY(ics.contains("BEGIN:VCALENDAR"));
    QVERIFY(ics.contains("VERSION:2.0"));
    QVERIFY(ics.contains("PRODID:-//NCDE//Leap Frog Ledger//EN"));
    QVERIFY(ics.contains("CALSCALE:GREGORIAN"));
    QVERIFY(ics.contains("BEGIN:VEVENT"));
    QVERIFY(ics.contains("END:VEVENT"));
    QVERIFY(ics.contains("END:VCALENDAR"));
    QVERIFY(ics.contains("SUMMARY:Meeting"));
    QVERIFY(ics.contains("SUMMARY:Birthday"));
    QVERIFY(ics.contains("RRULE:FREQ=WEEKLY"));
    QVERIFY(ics.contains("RRULE:FREQ=YEARLY"));
    QVERIFY(ics.contains("DTSTART;VALUE=DATE:20261225")); // all-day format
    QVERIFY(ics.contains("CATEGORIES:garnet"));
    QVERIFY(ics.contains("CATEGORIES:amethyst"));
}

// ---------------------------------------------------------------- importICS
void CalBackendTest::testImportICS()
{
    const QString ics = QStringLiteral(
        "BEGIN:VCALENDAR\r\n"
        "VERSION:2.0\r\n"
        "PRODID:-//NCDE//Leap Frog Ledger//EN\r\n"
        "CALSCALE:GREGORIAN\r\n"
        "BEGIN:VEVENT\r\n"
        "UID:test-123@ncde-leapfrog\r\n"
        "DTSTART:20261001T090000\r\n"
        "DTEND:20261001T100000\r\n"
        "SUMMARY:Imported Meeting\r\n"
        "LOCATION:Room A\r\n"
        "DESCRIPTION:Test import\r\n"
        "RRULE:FREQ=DAILY\r\n"
        "CATEGORIES:verdant\r\n"
        "END:VEVENT\r\n"
        "BEGIN:VEVENT\r\n"
        "UID:test-456@ncde-leapfrog\r\n"
        "DTSTART;VALUE=DATE:20261225\r\n"
        "SUMMARY:Christmas\r\n"
        "END:VEVENT\r\n"
        "END:VCALENDAR\r\n");

    int count = m_backend->importICS(ics);
    QVERIFY(count == 2);
    QVERIFY(m_backend->appointments().size() == 2);

    const QVariantMap a1 = m_backend->appointments().first().toMap();
    QVERIFY(a1["title"].toString() == "Imported Meeting");
    QVERIFY(a1["repeat"].toString() == "daily");
    QVERIFY(a1["category"].toString() == "verdant");
    QVERIFY(a1["location"].toString() == "Room A");
    QVERIFY(a1["notes"].toString() == "Test import");

    const QVariantMap a2 = m_backend->appointments().last().toMap();
    QVERIFY(a2["title"].toString() == "Christmas");
    QVERIFY(a2["allDay"].toBool() == true);
    QVERIFY(a2["repeat"].toString() == "none");
}

// ---------------------------------------------------------------- ICS identity round-trip
void CalBackendTest::testICSIdentityRoundTrip()
{
    const QString title = QStringLiteral("Round, Trip; \"draft\"");
    const QString notes = QStringLiteral("Coffee, code; and\\\\tea\nagain");
    m_backend->upsertAppointment({{"title", title}, {"date", "2026-10-15"}, {"start", 480}, {"end", 540}, {"location", "Café"}, {"notes", notes}, {"repeat", "monthly"}, {"reminder", 30}, {"category", "teal"}});

    QString ics = m_backend->exportICS();
    QVERIFY(ics.contains(QStringLiteral("SUMMARY:Round\\, Trip\\; \"draft\"")));
    QVERIFY(ics.contains(QStringLiteral("DESCRIPTION:Coffee\\, code\\; and\\\\\\\\tea\\nagain")));
    QVERIFY(ics.contains(QStringLiteral("TRIGGER:-PT30M")));
    int count = m_backend->importICS(ics);
    QVERIFY(count == 1);
    QVERIFY(m_backend->appointments().size() == 2); // original + imported (different ID)

    const QVariantMap imported = m_backend->appointments().last().toMap();
    QVERIFY(imported["title"].toString() == title);
    QVERIFY(imported["location"].toString() == "Café");
    QVERIFY(imported["notes"].toString() == notes);
    QVERIFY(imported["repeat"].toString() == "monthly");
    QVERIFY(imported["category"].toString() == "teal");
    QVERIFY(imported["reminder"].toInt() == 30);
}

// ---------------------------------------------------------------- reminder due logic
void CalBackendTest::testReminderDueLogic()
{
    const QDateTime now = QDateTime::currentDateTime();
    const int defaultLead = 15;
    const QDateTime firstStart = now.addSecs(defaultLead * 60);
    const QDateTime secondStart = now.addSecs((defaultLead + 45) * 60);

    const auto makeAppointment = [](const QString &id, const QDateTime &start,
                                    int reminder, bool allDay) {
        return QVariantMap{{"id", id},
                           {"title", id},
                           {"date", start.date().toString(Qt::ISODate)},
                           {"start", start.time().hour() * 60 + start.time().minute()},
                           {"end", start.time().hour() * 60 + start.time().minute() + 60},
                           {"allDay", allDay},
                           {"reminder", reminder},
                           {"repeat", "none"}};
    };
    m_backend->upsertAppointment(makeAppointment("appt-1", firstStart, defaultLead, false));
    m_backend->upsertAppointment(makeAppointment("appt-2", secondStart, 30, false));
    const QDate tomorrow = now.date().addDays(1);
    m_backend->upsertAppointment({{"id", "appt-3"}, {"title", "Birthday"},
                                  {"date", tomorrow.toString(Qt::ISODate)}, {"start", 0},
                                  {"end", 0}, {"allDay", true}, {"reminder", 0},
                                  {"repeat", "none"}});

    const QVariantList due = m_backend->dueReminders(14);
    QVERIFY(due.size() == 3);
    QVERIFY(due[0].toMap()["_key"].toString().startsWith("appt-1@"));
    QVERIFY(due[0].toMap()["due"].toBool());           // fireAt is at/before now
    QVERIFY(!due[1].toMap()["due"].toBool());          // fireAt is still in the future
    QVERIFY(due[2].toMap()["due"].toBool() == false);  // tomorrow
}

// ---------------------------------------------------------------- canDeliver
void CalBackendTest::testCanDeliver()
{
    // notify-send should exist on any desktop system
    QVERIFY(m_backend->canDeliver("desktop") == true);
    // curl is standard
    QVERIFY(m_backend->canDeliver("ntfy") == true);
    // msmtp may not be installed — just verify it doesn't crash
    bool emailOk = m_backend->canDeliver("email");
    Q_UNUSED(emailOk);
    // Unknown method
    QVERIFY(m_backend->canDeliver("unknown") == false);
}

// ---------------------------------------------------------------- composeForHummingbirdRec
void CalBackendTest::testComposeForHummingbirdRec()
{
    QVariantMap a;
    a["id"] = "test-1";
    a["title"] = "Test Appt";
    a["date"] = "2026-10-01";
    a["start"] = 540;
    a["end"] = 600;
    a["allDay"] = false;
    a["location"] = "Test Loc";
    a["notes"] = "Test notes";
    a["repeat"] = "none";
    a["reminder"] = 15;
    a["category"] = "azure";

    // Constrain process lookup so this test never starts a real courier.
    const QString binDir = m_tempDir.path() + QStringLiteral("/empty-bin");
    QVERIFY(QDir().mkpath(binDir));
    const QByteArray oldPath = qgetenv("PATH");
    qputenv("PATH", binDir.toUtf8());
    bool ok = m_backend->composeForHummingbirdRec(a);
    qputenv("PATH", oldPath);
    QVERIFY(ok);

    const QDir pending(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                       + QStringLiteral("/pending"));
    const QStringList files = pending.entryList({QStringLiteral("compose_*.json")}, QDir::Files);
    QCOMPARE(files.size(), 1);
    QFile compose(pending.filePath(files.first()));
    QVERIFY(compose.open(QIODevice::ReadOnly));
    const QJsonDocument doc = QJsonDocument::fromJson(compose.readAll());
    QVERIFY(doc.object().value(QStringLiteral("body")).toString()
                .contains(QStringLiteral("from 09:00 AM to 10:00 AM")));
}

// ---------------------------------------------------------------- reload after external write (C14)
void CalBackendTest::testReloadAfterExternalWrite()
{
    // Write a file externally (simulating cal-reminders daemon)
    const QString path = m_backend->configFilePath();
    QDir().mkpath(QFileInfo(path).absolutePath());
    QJsonObject obj;
    obj["appointments"] = QJsonArray::fromVariantList(QVariantList{
        QVariantMap{{"id", "ext-1"}, {"title", "External"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}, {"allDay", false}, {"repeat", "none"}, {"reminder", 15}, {"category", "azure"}}
    });
    obj["todos"] = QJsonArray();
    obj["settings"] = QJsonObject{{"enabled", true}, {"defaultLead", 15}};
    QFile f(path);
    QVERIFY(f.open(QIODevice::WriteOnly));
    f.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    f.close();

    // Before reload, backend still has old data (empty)
    QVERIFY(m_backend->appointments().isEmpty());

    // Reload picks up external changes
    m_backend->reload();
    QVERIFY(m_backend->appointments().size() == 1);
    QVERIFY(m_backend->appointments().first().toMap()["title"].toString() == "External");
}

// ---------------------------------------------------------------- configFilePath
void CalBackendTest::testConfigFilePath()
{
    QString path = m_backend->configFilePath();
    QVERIFY(path.endsWith("/ncde/calendar.json"));
    QVERIFY(QDir(QFileInfo(path).absolutePath()).exists());
}

QTEST_MAIN(CalBackendTest)
#include "cal_backend_test.moc"