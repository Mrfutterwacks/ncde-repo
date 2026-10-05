#include "CursorManager.h"
#include "IconProvider.h"
#include "KithCursors.h"

#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QImage>
#include <QPixmap>
#include <QSaveFile>
#include <QTemporaryDir>
#include <QTest>
#include <QDataStream>
#include <QDateTime>
#include <QFileInfo>
#include <QIcon>
#include <QSet>

namespace {

struct Renderer {
    QString name;
    std::function<void(QImage &, int)> render;
    double hotX;
    double hotY;
};

QList<Renderer> renderers()
{
    return {
        {QStringLiteral("arrow"), KithCursors::renderKithArrow, 0.16, 0.06},
        {QStringLiteral("pointer"), KithCursors::renderKithPointer, 0.40, 0.06},
        {QStringLiteral("text"), KithCursors::renderKithText, 0.50, 0.50},
        {QStringLiteral("wait"), KithCursors::renderKithWait, 0.50, 0.50},
        {QStringLiteral("help"), KithCursors::renderKithHelp, 0.16, 0.06},
        {QStringLiteral("move"), KithCursors::renderKithMove, 0.50, 0.50},
        {QStringLiteral("resize-vertical"), [](QImage &i, int s) { KithCursors::renderKithResize(i, s, 1.57079632679); }, 0.50, 0.50},
        {QStringLiteral("resize-horizontal"), [](QImage &i, int s) { KithCursors::renderKithResize(i, s, 0.0); }, 0.50, 0.50},
        {QStringLiteral("resize-diagonal-a"), [](QImage &i, int s) { KithCursors::renderKithResize(i, s, 0.78539816339); }, 0.50, 0.50},
        {QStringLiteral("resize-diagonal-b"), [](QImage &i, int s) { KithCursors::renderKithResize(i, s, -0.78539816339); }, 0.50, 0.50},
        {QStringLiteral("crosshair"), KithCursors::renderKithCrosshair, 0.50, 0.50},
        {QStringLiteral("not-allowed"), KithCursors::renderKithNotAllowed, 0.50, 0.50},
        {QStringLiteral("openhand"), [](QImage &i, int s) { KithCursors::renderKithHand(i, s, false); }, 0.50, 0.50},
        {QStringLiteral("closedhand"), [](QImage &i, int s) { KithCursors::renderKithHand(i, s, true); }, 0.50, 0.50}
    };
}

QByteArray indexTheme()
{
    return QByteArray("[Icon Theme]\nName=NCDEFixture\nComment=Test theme\nDirectories=32x32/apps\n"
                      "[32x32/apps]\nSize=32\nContext=Applications\nType=Fixed\n");
}

} // namespace

class CursorRenderTest final : public QObject
{
    Q_OBJECT

private slots:
    void renderPngsAndHotspots()
    {
        const QString scratchTemplate = QDir::current().absoluteFilePath(
            QStringLiteral("tests/.cursor-render-scratch-XXXXXX"));
        QTemporaryDir scratch(scratchTemplate);
        QVERIFY(scratch.isValid());
        const QList<int> sizes{24, 32, 48};
        int rendered = 0;
        for (const Renderer &renderer : renderers()) {
            for (const int size : sizes) {
                QImage image;
                renderer.render(image, size);
                QVERIFY2(!image.isNull(), qPrintable(renderer.name));
                QCOMPARE(image.size(), QSize(size + 12, size + 12));
                QCOMPARE(image.format(), QImage::Format_ARGB32_Premultiplied);
                const QPoint hot = KithCursors::hotspotImage(size, renderer.hotX, renderer.hotY);
                QVERIFY(hot.x() >= 0 && hot.x() < image.width());
                QVERIFY(hot.y() >= 0 && hot.y() < image.height());
                QVERIFY(image.pixelColor(hot).alpha() > 0);
                QVERIFY(image.hasAlphaChannel());
                const QString path = scratch.filePath(renderer.name + QLatin1Char('-')
                                                       + QString::number(size) + QStringLiteral(".png"));
                QVERIFY2(image.save(path, "PNG"), qPrintable(path));
                QImage readBack(path);
                QVERIFY(!readBack.isNull());
                QCOMPARE(readBack.size(), image.size());
                ++rendered;
            }
        }
        QCOMPARE(rendered, 42);
        qInfo().noquote() << "PASS renderPngsAndHotspots:" << rendered << "PNG render/read-back cases";
    }

    void xcursorThemeHasAllSettingsSizesAndAliases()
    {
        const QString scratchTemplate = QDir::current().absoluteFilePath(
            QStringLiteral("tests/.cursor-theme-scratch-XXXXXX"));
        QTemporaryDir scratch(scratchTemplate);
        QVERIFY(scratch.isValid());
        CursorManager manager;
        QVERIFY(manager.writeXcursorTheme(scratch.path(), {24, 32, 48, 64}));

        const QString directory = scratch.path() + QStringLiteral("/Kith/cursors");
        const QStringList canonical{
            QStringLiteral("left_ptr"), QStringLiteral("hand2"), QStringLiteral("xterm"),
            QStringLiteral("watch"), QStringLiteral("question_arrow"), QStringLiteral("fleur"),
            QStringLiteral("ns-resize"), QStringLiteral("ew-resize"), QStringLiteral("nesw-resize"),
            QStringLiteral("nwse-resize"), QStringLiteral("crosshair"), QStringLiteral("not-allowed"),
            QStringLiteral("openhand"), QStringLiteral("closedhand")
        };
        const QSet<int> settingsSizes = [] {
            QSet<int> values;
            for (int size = 16; size <= 128; ++size)
                values.insert(size);
            return values;
        }();

        for (const QString &name : canonical) {
            const QString path = directory + QLatin1Char('/') + name;
            QFile file(path);
            QVERIFY2(file.open(QIODevice::ReadOnly), qPrintable(path));
            QDataStream stream(&file);
            stream.setByteOrder(QDataStream::LittleEndian);
            quint32 magic = 0, header = 0, version = 0, count = 0;
            stream >> magic >> header >> version >> count;
            QCOMPARE(magic, quint32(0x72756358));
            QCOMPARE(header, quint32(16));
            QCOMPARE(version, quint32(0x00010000));
            QCOMPARE(count, quint32(113));
            QSet<int> foundSizes;
            for (quint32 i = 0; i < count; ++i) {
                QVERIFY(file.seek(16 + qint64(i) * 12));
                quint32 type = 0, nominal = 0, position = 0;
                stream >> type >> nominal >> position;
                QCOMPARE(type, quint32(0xfffd0002));
                QVERIFY(settingsSizes.contains(int(nominal)));
                foundSizes.insert(int(nominal));
                QVERIFY(file.seek(position));
                quint32 chunkHeader = 0, chunkType = 0, subtype = 0, chunkVersion = 0;
                quint32 width = 0, height = 0, hotX = 0, hotY = 0, delay = 0;
                stream >> chunkHeader >> chunkType >> subtype >> chunkVersion >> width >> height
                       >> hotX >> hotY >> delay;
                QCOMPARE(chunkHeader, quint32(36));
                QCOMPARE(chunkType, quint32(0xfffd0002));
                QCOMPARE(subtype, nominal);
                QCOMPARE(chunkVersion, quint32(1));
                QCOMPARE(width, nominal + 12);
                QCOMPARE(height, nominal + 12);
                QVERIFY(hotX < width);
                QVERIFY(hotY < height);
                QCOMPARE(delay, quint32(0));
                QVERIFY(file.seek(position + 36 + qint64(width) * height * 4));
            }
            QCOMPARE(foundSizes, settingsSizes);
        }
        int aliases = 0;
        const QFileInfoList entries = QDir(directory).entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        for (const QFileInfo &entry : entries)
            aliases += entry.isSymLink() ? 1 : 0;
        QCOMPARE(aliases, 73);

        const QString unchangedFile = directory + QStringLiteral("/left_ptr");
        const QDateTime firstModified = QFileInfo(unchangedFile).lastModified();
        QVERIFY(manager.writeXcursorTheme(scratch.path(), {24, 32, 48, 64}));
        QCOMPARE(QFileInfo(unchangedFile).lastModified(), firstModified);
        qInfo().noquote() << "PASS xcursorThemeHasAllSettingsSizesAndAliases: 14 files, 113 sizes, 73 aliases";
    }

    void imageProviderUsesThemeAndRejectsPaths()
    {
        const QString scratchTemplate = QDir::current().absoluteFilePath(
            QStringLiteral("tests/.icon-provider-scratch-XXXXXX"));
        QTemporaryDir scratch(scratchTemplate);
        QVERIFY(scratch.isValid());
        const QString iconDir = scratch.path() + QStringLiteral("/NCDEFixture/32x32/apps");
        QVERIFY(QDir().mkpath(iconDir));
        QFile index(scratch.path() + QStringLiteral("/NCDEFixture/index.theme"));
        QVERIFY(index.open(QIODevice::WriteOnly));
        QCOMPARE(index.write(indexTheme()), qint64(indexTheme().size()));
        index.close();
        QImage artwork(32, 32, QImage::Format_ARGB32_Premultiplied);
        artwork.fill(QColor(QStringLiteral("#3a78c8")));
        QVERIFY(artwork.save(iconDir + QStringLiteral("/test-app.png"), "PNG"));
        QIcon::setThemeSearchPaths({scratch.path()});
        QIcon::setThemeName(QStringLiteral("NCDEFixture"));

        IconProvider provider;
        QSize actualSize;
        const QPixmap icon = provider.requestPixmap(QStringLiteral("test-app"), &actualSize, QSize(18, 18));
        QVERIFY(!icon.isNull());
        QCOMPARE(actualSize, QSize(18, 18));
        const QPixmap rejected = provider.requestPixmap(QStringLiteral("../test-app"), &actualSize, QSize(18, 18));
        QVERIFY(rejected.isNull());
        QCOMPARE(actualSize, QSize(18, 18));
        qInfo() << "PASS imageProviderUsesThemeAndRejectsPaths";
    }
};

QTEST_MAIN(CursorRenderTest)
#include "cursor_render_test.moc"
