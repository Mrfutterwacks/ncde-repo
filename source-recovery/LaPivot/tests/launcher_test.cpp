#include "Launcher.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>
#include <QTest>
#include <QVariantList>

class TestLauncher : public QObject
{
    Q_OBJECT

    QString captureHelper() const
    {
        return QString::fromLocal8Bit(qgetenv("NCDE_CAPTURE_HELPER"));
    }

    QString outputPath() const
    {
        return QString::fromLocal8Bit(qgetenv("NCDE_TEST_OUTPUT"));
    }

    void capture(const QString &command, QJsonObject *result)
    {
        QFile::remove(outputPath());
        Launcher launcher;
        launcher.launchExec(command);
        QTRY_VERIFY_WITH_TIMEOUT(QFile::exists(outputPath()), 3000);

        QFile file(outputPath());
        QVERIFY(file.open(QIODevice::ReadOnly));
        *result = QJsonDocument::fromJson(file.readAll()).object();
        const qint64 pid = result->value(QStringLiteral("pid")).toInteger();
        QVERIFY(pid > 0);
        QTRY_VERIFY_WITH_TIMEOUT(!QFile::exists(QStringLiteral("/proc/%1").arg(pid)), 3000);
    }

private slots:
    void homePathUsesScratchHome()
    {
        Launcher launcher;
        QCOMPARE(launcher.homePath(), QDir::homePath());
        QVERIFY(launcher.homePath().contains(QStringLiteral(".launcher_test.")));
    }

    void launchExecPreservesQuotedAndLiteralArguments()
    {
        const QString command = QStringLiteral("\"%1\" 'two words' \"three words\" \"\" '$HOME;*'")
            .arg(captureHelper());
        QJsonObject result;
        capture(command, &result);
        const QJsonArray args = result.value(QStringLiteral("args")).toArray();

        QCOMPARE(args, QJsonArray({QStringLiteral("two words"), QStringLiteral("three words"),
                                   QString(), QStringLiteral("$HOME;*")}));
    }

    void launchWithFilesKeepsEachPathAsOneArgument()
    {
        QFile::remove(outputPath());
        Launcher launcher;
        QVariantList files {
            QStringLiteral("/scratch/a document.pdf"),
            QStringLiteral("/scratch/second file.pdf")
        };
        launcher.launchWithFiles(QStringLiteral("\"%1\" --open").arg(captureHelper()), files);
        QTRY_VERIFY_WITH_TIMEOUT(QFile::exists(outputPath()), 3000);

        QFile file(outputPath());
        QVERIFY(file.open(QIODevice::ReadOnly));
        const QJsonObject result = QJsonDocument::fromJson(file.readAll()).object();
        const QJsonArray args = result.value(QStringLiteral("args")).toArray();
        QCOMPARE(args, QJsonArray({QStringLiteral("--open"), files.at(0).toString(),
                                   files.at(1).toString()}));
        const qint64 pid = result.value(QStringLiteral("pid")).toInteger();
        QVERIFY(pid > 0);
        QTRY_VERIFY_WITH_TIMEOUT(!QFile::exists(QStringLiteral("/proc/%1").arg(pid)), 3000);
    }

    void emptyCommandsAreNoOps()
    {
        QFile::remove(outputPath());
        Launcher launcher;
        launcher.launchExec({});
        launcher.launch({});
        launcher.systemCommand(QStringLiteral("   "));
        QVERIFY(!QFile::exists(outputPath()));
    }
};

QTEST_MAIN(TestLauncher)
#include "launcher_test.moc"
