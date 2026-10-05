#include "FontManager.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcessEnvironment>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QElapsedTimer>
#include <QTest>
#include <memory>

class FontsTest final : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<QTemporaryDir> m_scratch;

private slots:
    void initTestCase()
    {
        const QString scratchTemplate = QDir::current().absoluteFilePath(
            QStringLiteral("tests/.fonts-scratch-XXXXXX"));
        m_scratch = std::make_unique<QTemporaryDir>(scratchTemplate);
        QVERIFY(m_scratch->isValid());
        const QString home = m_scratch->path() + QStringLiteral("/home");
        const QString cache = m_scratch->path() + QStringLiteral("/cache");
        QVERIFY(QDir().mkpath(home));
        QVERIFY(QDir().mkpath(cache));
        const QString config = m_scratch->path() + QStringLiteral("/fonts.conf");
        QFile file(config);
        QVERIFY(file.open(QIODevice::WriteOnly));
        const QByteArray xml = QStringLiteral(
            "<?xml version=\"1.0\"?><fontconfig>"
            "<dir>/usr/share/fonts</dir><dir>/usr/local/share/fonts</dir>"
            "<cachedir>%1</cachedir><include ignore_missing=\"yes\">/etc/fonts/conf.d</include>"
            "</fontconfig>").arg(cache).toUtf8();
        QCOMPARE(file.write(xml), qint64(xml.size()));
        file.close();
        qputenv("HOME", home.toUtf8());
        qputenv("XDG_CONFIG_HOME", (home + QStringLiteral("/.config")).toUtf8());
        qputenv("FONTCONFIG_FILE", config.toUtf8());
    }

    void catalogAndScratchFontconfigRefresh()
    {
        FontManager manager;
        QSignalSpy changed(&manager, &FontManager::fontsChanged);
        QCOMPARE(manager.total(), 33);
        const QVariantList rows = manager.fonts();
        QCOMPARE(rows.size(), 33);
        QCOMPARE(rows.first().toMap().value(QStringLiteral("family")).toString(),
                 QStringLiteral("Cormorant Garamond"));
        QCOMPARE(rows.first().toMap().value(QStringLiteral("pkg")).toString(), QString());
        QCOMPARE(rows.first().toMap().value(QStringLiteral("repo")).toString(), QStringLiteral("NCDE"));

        QTRY_VERIFY_WITH_TIMEOUT(!manager.families().isEmpty(), 15000);
        QVERIFY(!changed.isEmpty());
        QVERIFY(manager.installedCount() >= 0);
        QVERIFY(manager.installedCount() <= manager.total());
        QVERIFY(manager.status().contains(QStringLiteral("ready"), Qt::CaseInsensitive));

        QElapsedTimer elapsed;
        elapsed.start();
        manager.refresh();
        QVERIFY2(elapsed.elapsed() < 100, "refresh() must enqueue fontconfig scanning without blocking");
        qInfo().noquote() << "PASS catalogAndScratchFontconfigRefresh:" << manager.total()
                          << "catalog entries," << manager.families().size() << "fontconfig families";
    }

    void missingPackageKitIsGracefulAndUsesNoHostSystemBus()
    {
        FontManager manager;
        QSignalSpy statusChanged(&manager, &FontManager::statusChanged);
        manager.installFont(QStringLiteral("ncde-test-nonexistent-package"));
        QTRY_VERIFY_WITH_TIMEOUT(!manager.busy(), 10000);
        QVERIFY(!statusChanged.isEmpty());
        QVERIFY(manager.status().contains(QStringLiteral("PackageKit"), Qt::CaseInsensitive));
        qInfo() << "PASS missingPackageKitIsGraceful";
    }
};

QTEST_GUILESS_MAIN(FontsTest)
#include "fonts_test.moc"
