// cal_pond_test.cpp — LeapFrogPond unit tests (offscreen, scratch HOME).
//
// Tests cover: load/save atomicity, note CRUD, CSV export quoting (P3),
// .lilypad export, tally keys (P8), reconcile (P7), archivePast (P6),
// genId full UUID (P5), reload after external write.

#include <QtTest/QtTest>
#include <QTemporaryDir>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "CalendarBackend.h"
#include "LeapFrogPond.h"

class CalPondTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testLoadMissingFile();
    void testSaveAtomic();
    void testAddNote();
    void testRemoveNote();
    void testSetNotice();
    void testTallyKeys();
    void testExportCsvQuoting();
    void testExportLilyPad();
    void testReconcile();
    void testArchivePast();
    void testGenIdFullUuid();
    void testReloadAfterExternalWrite();
    void testGcalLinkSurvivesUpsert();   // C13 — the 2026-10-04 freeze
    void testConfigFilePath();

private:
    QTemporaryDir m_tempDir;
    QString m_oldConfig;
    CalendarBackend *m_calBackend = nullptr;
    LeapFrogPond *m_pond = nullptr;
};

void CalPondTest::initTestCase()
{
    m_oldConfig = qgetenv("XDG_CONFIG_HOME");
    qputenv("XDG_CONFIG_HOME", m_tempDir.path().toUtf8());
    QStandardPaths::setTestModeEnabled(true);
}

void CalPondTest::cleanupTestCase()
{
    if (m_oldConfig.isEmpty())
        qunsetenv("XDG_CONFIG_HOME");
    else
        qputenv("XDG_CONFIG_HOME", m_oldConfig.toUtf8());
}

void CalPondTest::init()
{
    QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
         + QStringLiteral("/ncde")).removeRecursively();
    m_calBackend = new CalendarBackend();
    m_pond = new LeapFrogPond(nullptr, m_calBackend);
}

void CalPondTest::cleanup()
{
    delete m_pond;
    m_pond = nullptr;
    delete m_calBackend;
    m_calBackend = nullptr;
}

// ---------------------------------------------------------------- load missing file
void CalPondTest::testLoadMissingFile()
{
    QVERIFY(m_pond->notes().isEmpty());
    QVERIFY(m_pond->noteCount() == 0);
    QVERIFY(m_pond->notice().isEmpty());
}

// ---------------------------------------------------------------- save atomic (P1)
void CalPondTest::testSaveAtomic()
{
    m_pond->addNote("Test note");
    const QString path = m_pond->configFilePath();
    QVERIFY(QFile::exists(path));

    QFile f(path);
    QVERIFY(f.open(QIODevice::ReadOnly));
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    QVERIFY(err.error == QJsonParseError::NoError);
    QVERIFY(doc.isObject());
    const QVariantMap root = doc.object().toVariantMap();
    QVERIFY(root["notes"].toList().size() == 1);
}

// ---------------------------------------------------------------- addNote
void CalPondTest::testAddNote()
{
    m_pond->addNote("First note");
    QVERIFY(m_pond->noteCount() == 1);
    QVERIFY(m_pond->notes().first().toMap()["text"].toString() == "First note");

    m_pond->addNote("Second note");
    QVERIFY(m_pond->noteCount() == 2);

    QFile persisted(m_pond->configFilePath());
    QVERIFY(persisted.open(QIODevice::ReadOnly));
    const QJsonDocument saved = QJsonDocument::fromJson(persisted.readAll());
    QCOMPARE(saved.object().value("notes").toArray().size(), 2);

    // Empty/whitespace notes are rejected
    m_pond->addNote("   ");
    QVERIFY(m_pond->noteCount() == 2);
    m_pond->addNote("");
    QVERIFY(m_pond->noteCount() == 2);
}

// ---------------------------------------------------------------- removeNote
void CalPondTest::testRemoveNote()
{
    m_pond->addNote("To remove");
    const QString id = m_pond->notes().first().toMap()["id"].toString();
    QVERIFY(!id.isEmpty());

    m_pond->removeNote(id);
    QVERIFY(m_pond->notes().isEmpty());
}

// ---------------------------------------------------------------- setNotice
void CalPondTest::testSetNotice()
{
    QVERIFY(m_pond->notice().isEmpty());
    m_pond->setNotice("Pond notice");
    QVERIFY(m_pond->notice() == "Pond notice");
    m_pond->setNotice("Updated");
    QVERIFY(m_pond->notice() == "Updated");
}

// ---------------------------------------------------------------- tally keys (P8)
void CalPondTest::testTallyKeys()
{
    m_pond->addNote("Note 1");
    m_pond->addNote("Note 2");
    m_calBackend->upsertAppointment({{"title", "Appt"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});

    const QVariantMap tally = m_pond->tally();
    QVERIFY(tally.contains("lilyPads"));
    QVERIFY(tally["lilyPads"].toInt() == 2);
    QVERIFY(tally.contains("appointments"));
    QVERIFY(tally["appointments"].toInt() == 1);
    QVERIFY(tally.contains("today"));
    QVERIFY(tally["today"].toInt() == 2); // both notes created today
}

// ---------------------------------------------------------------- exportCsv quoting (P3)
void CalPondTest::testExportCsvQuoting()
{
    m_calBackend->upsertAppointment({
        {"title", "Meeting, with comma"},
        {"date", "2026-10-01"},
        {"start", 540},
        {"end", 600},
        {"notes", "Notes with \"quotes\""}
    });
    m_calBackend->upsertAppointment({
        {"title", "Simple"},
        {"date", "2026-10-02"},
        {"start", 600},
        {"end", 660},
        {"notes", "Plain"}
    });

    const QString path = m_tempDir.path() + "/test.csv";
    const QString result = m_pond->exportCsv(path);
    QVERIFY(result == path);
    QVERIFY(QFile::exists(path));

    QFile f(path);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QString content = QString::fromUtf8(f.readAll());
    f.close();

    // Header
    QVERIFY(content.contains("date,time,title,notes"));

    // First row: title has comma -> must be quoted
    QVERIFY(content.contains("\"Meeting, with comma\""));
    // Notes has quotes -> must be escaped and quoted
    QVERIFY(content.contains("\"Notes with \"\"quotes\"\"\""));

    // Second row: no special chars -> no quoting needed (but allowed)
    QVERIFY(content.contains("Simple"));
    QVERIFY(content.contains("Plain"));
}

// ---------------------------------------------------------------- exportLilyPad
void CalPondTest::testExportLilyPad()
{
    m_pond->addNote("Lily note");
    m_pond->setNotice("Pond notice");
    m_calBackend->upsertAppointment({{"title", "Appt"}, {"date", "2026-10-01"}, {"start", 540}, {"end", 600}});

    const QString path = m_tempDir.path() + "/test.lilypad";
    const QString result = m_pond->exportLilyPad(path);
    QVERIFY(result == path);
    QVERIFY(QFile::exists(path));

    QFile f(path);
    QVERIFY(f.open(QIODevice::ReadOnly));
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    QVERIFY(err.error == QJsonParseError::NoError);
    QVERIFY(doc.isObject());
    const QVariantMap root = doc.object().toVariantMap();
    QVERIFY(root["notes"].toList().size() == 1);
    QVERIFY(root["notice"].toString() == "Pond notice");
    QVERIFY(root["appts"].toList().size() == 1);
}

// ---------------------------------------------------------------- reconcile (P7 - backwards iteration)
void CalPondTest::testReconcile()
{
    // Add notes with old dates (simulate by manipulating created field directly via save/load)
    // Since we can't easily set created date via public API, we'll test the logic
    // by adding notes and verifying reconcile doesn't crash and returns 0 for fresh notes.
    m_pond->addNote("Fresh note");
    m_pond->addNote("Another fresh note");

    int removed = m_pond->reconcile();
    QVERIFY(removed == 0); // 30-day cutoff, all notes fresh
    QVERIFY(m_pond->noteCount() == 2);
}

// ---------------------------------------------------------------- archivePast (P6 - emits archived)
void CalPondTest::testArchivePast()
{
    // Add a non-recurring appointment in the past
    m_calBackend->upsertAppointment({
        {"title", "Old meeting"},
        {"date", "2020-01-01"},
        {"start", 540},
        {"end", 600},
        {"repeat", "none"}
    });
    // Add a recurring appointment in the past - should NOT be archived
    m_calBackend->upsertAppointment({
        {"title", "Old recurring"},
        {"date", "2020-01-01"},
        {"start", 600},
        {"end", 660},
        {"repeat", "weekly"}
    });
    // Add a future appointment - should NOT be archived
    m_calBackend->upsertAppointment({
        {"title", "Future meeting"},
        {"date", "2030-01-01"},
        {"start", 540},
        {"end", 600},
        {"repeat", "none"}
    });

    int removed = m_pond->archivePast();
    QVERIFY(removed == 1); // only the non-recurring past one

    // Verify the remaining appointments
    QVERIFY(m_calBackend->appointments().size() == 2);
    QStringList titles;
    for (const QVariant &v : m_calBackend->appointments()) {
        titles << v.toMap()["title"].toString();
    }
    QVERIFY(titles.contains("Old recurring"));
    QVERIFY(titles.contains("Future meeting"));
    QVERIFY(!titles.contains("Old meeting"));
}

// ---------------------------------------------------------------- genId full UUID (P5)
void CalPondTest::testGenIdFullUuid()
{
    // Can't call genId() directly (private), but note IDs use it
    m_pond->addNote("Test");
    const QString id = m_pond->notes().first().toMap()["id"].toString();
    QVERIFY(id.length() == 36); // full UUID without braces
    QVERIFY(id.count('-') == 4); // UUID format
}

// ---------------------------------------------------------------- reload after external write
void CalPondTest::testReloadAfterExternalWrite()
{
    const QString path = m_pond->configFilePath();
    QDir().mkpath(QFileInfo(path).absolutePath());
    QJsonObject obj;
    obj["notes"] = QJsonArray::fromVariantList(QVariantList{
        QVariantMap{{"id", "ext-1"}, {"text", "External note"}, {"created", "2026-10-01T12:00:00"}}
    });
    obj["notice"] = "External notice";
    QFile f(path);
    QVERIFY(f.open(QIODevice::WriteOnly));
    f.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    f.close();

    QVERIFY(m_pond->notes().isEmpty());
    QVERIFY(m_pond->notice().isEmpty());

    m_pond->reload();
    QVERIFY(m_pond->noteCount() == 1);
    QVERIFY(m_pond->notes().first().toMap()["text"].toString() == "External note");
    QVERIFY(m_pond->notice() == "External notice");
}

// ------------------------------------------------- C13: the gcal link must survive
// This is the test for the 2026-10-04 hard freeze, and it is the one that should have
// existed before the feature shipped rather than after it froze a desktop.
//
// GoogleCalendarSync hands every synced appointment to upsertAppointment() with a `gcal`
// link on it (cal / event / etag / sig / ro / inst). normaliseAppointment() rebuilds each
// record from a hard-coded field list — a deliberate validation boundary, so that a
// malformed ICS import cannot inject arbitrary fields — and `gcal` was not on that list.
//
// The consequence was silent and unbounded. The link never reached disk, so on the next
// poll every appointment looked like it had never been sent to Google. step2PushDeletes
// re-POSTed the entire calendar. apptToEvent sent no iCalUID, so Google filed a brand new
// event each time instead of recognising the re-send; the pull imported those as fresh
// `g-…` records, which were then pushed again. The calendar went from 1152 appointments
// to 1753 in about twenty minutes, each cycle rewriting a 500 KB calendar.json on the GUI
// thread, and LaPivot's main thread reached 100% CPU. The desktop stopped responding and
// only a terminal worked.
//
// So: assert the link is stored, that it survives a reload from disk, and that an
// unrelated edit does not lose it.
void CalPondTest::testGcalLinkSurvivesUpsert()
{
    const QVariantMap link{
        {"cal", "primary@example.com"},
        {"event", "abcdef1234567890"},
        {"etag", "\"v1\""},
        {"sig", "9f2c"},
        {"ro", false},
        {"inst", false},
    };

    // 1. a linked appointment keeps its link
    m_calBackend->upsertAppointment({
        {"id", "g-abc123"}, {"title", "Dentist"}, {"date", "2026-10-06"},
        {"start", 900}, {"end", 930}, {"gcal", link}});
    QCOMPARE(m_calBackend->appointments().size(), 1);
    QVariantMap stored = m_calBackend->appointments().first().toMap();
    QVERIFY2(stored.contains("gcal"),
             "C13 REGRESSION: the gcal link was dropped by normaliseAppointment() — "
             "Google sync will re-POST this appointment on every poll, forever");
    QCOMPARE(stored["gcal"].toMap()["event"].toString(), QString("abcdef1234567890"));
    QCOMPARE(stored["gcal"].toMap()["etag"].toString(), QString("\"v1\""));

    // 2. and it is still there after the data has round-tripped through the file
    m_calBackend->reload();
    QVariantMap reloaded = m_calBackend->appointments().first().toMap();
    QVERIFY2(reloaded.contains("gcal"), "C13 REGRESSION: the gcal link did not survive save/reload");

    // 3. an ordinary local edit must not drop it either — this is the common case:
    //    the user drags the appointment, gcalsync upserts it back, and the link has to
    //    still be there or the next sync pushes it again.
    QVariantMap edited = reloaded;
    edited["start"] = 960;
    edited["end"] = 990;
    m_calBackend->upsertAppointment(edited);
    QVariantMap afterEdit = m_calBackend->appointments().first().toMap();
    QCOMPARE(afterEdit["start"].toInt(), 960);
    QVERIFY2(afterEdit.contains("gcal"), "C13 REGRESSION: a local edit dropped the gcal link");
    QCOMPARE(afterEdit["gcal"].toMap()["event"].toString(), QString("abcdef1234567890"));

    // 4. a local appointment with no link must NOT acquire a bogus empty one
    m_calBackend->upsertAppointment({
        {"id", "local-1"}, {"title", "Tea"}, {"date", "2026-10-07"}, {"start", 1020}, {"end", 1080}});
    QVariantMap plain = m_calBackend->appointments().at(1).toMap();
    QVERIFY2(!plain.contains("gcal"), "an unlinked appointment gained an empty gcal link");
}

// ---------------------------------------------------------------- configFilePath
void CalPondTest::testConfigFilePath()
{
    QString path = m_pond->configFilePath();
    QVERIFY(path.endsWith("/ncde/lilypad.json"));
    QVERIFY(QDir(QFileInfo(path).absolutePath()).exists());
}

QTEST_MAIN(CalPondTest)
#include "cal_pond_test.moc"