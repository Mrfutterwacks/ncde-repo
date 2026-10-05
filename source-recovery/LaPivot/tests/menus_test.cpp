#include <QCoreApplication>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>
#include <QThread>

#include <functional>

#include "../src/AppMenuModel.h"
#include "../src/GliaSystemMenus.h"

namespace {

int failures = 0;

void check(bool condition, const QString &message)
{
    QTextStream out(condition ? stdout : stderr);
    out << (condition ? "PASS: " : "FAIL: ") << message << Qt::endl;
    if (!condition)
        ++failures;
}

bool waitUntil(const std::function<bool()> &predicate, int timeoutMs = 3000)
{
    QElapsedTimer timer;
    timer.start();
    while (!predicate() && timer.elapsed() < timeoutMs) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 25);
        QThread::msleep(5);
    }
    QCoreApplication::processEvents(QEventLoop::AllEvents, 25);
    return predicate();
}

QStringList recordedLines()
{
    QFile file(qEnvironmentVariable("MENU_TEST_RECORD"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    QStringList lines;
    while (!file.atEnd())
        lines.append(QString::fromUtf8(file.readLine()).trimmed());
    return lines;
}

} // namespace

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    AppMenuModel model;
    GliaSystemMenus glia;
    DesktopIndex *index = DesktopIndex::instance();
    int modelChanges = 0;
    int gliaChanges = 0;
    QObject::connect(&model, &AppMenuModel::changed, &app, [&] { ++modelChanges; });
    QObject::connect(&glia, &GliaSystemMenus::changed, &app, [&] { ++gliaChanges; });

    check(waitUntil([&] { return index->ready() && modelChanges > 0; }),
          QStringLiteral("shared desktop scan completes asynchronously"));
    if (!index->ready())
        return 1;

    const QStringList categories = model.getCategories();
    check(categories.contains(QStringLiteral("All")), QStringLiteral("AppMenuModel has All category"));
    check(categories.contains(QStringLiteral("Internet")), QStringLiteral("Network maps to Internet"));
    check(categories.contains(QStringLiteral("System")), QStringLiteral("System category is retained"));
    check(!categories.contains(QStringLiteral("Utilities")),
          QStringLiteral("hidden first XDG override masks the system desktop file"));

    const QVariantList allApps = model.getApps({}, {});
    check(allApps.size() == 2, QStringLiteral("hidden, NoDisplay, Link, TryExec and OnlyShowIn entries are filtered"));
    check(model.getApps(QStringLiteral("Internet"), {}).size() == 1,
          QStringLiteral("AppMenuModel filters by mapped category"));
    const QVariantList search = model.getApps({}, QStringLiteral("term"));
    check(search.size() == 1 && search.first().toMap().value(QStringLiteral("name")).toString()
              == QStringLiteral("Test Terminal"),
          QStringLiteral("AppMenuModel searches name and exec"));
    check(model.getApps({}, QStringLiteral("Utilities")).isEmpty(),
          QStringLiteral("AppMenuModel search does not match category text"));
    check(!allApps.first().toMap().contains(QStringLiteral("id")),
          QStringLiteral("AppMenuModel preserves oracle result map fields"));

    const QVariantList applications = glia.applications();
    check(applications.size() == 2, QStringLiteral("GliaSystemMenus uses the shared filtered app index"));
    bool nestedIdFound = false;
    QString browserId;
    for (const QVariant &value : applications) {
        const QVariantMap entry = value.toMap();
        if (entry.value(QStringLiteral("id")).toString()
            == QStringLiteral("subdir-test-terminal.desktop"))
            nestedIdFound = true;
        if (entry.value(QStringLiteral("name")).toString() == QStringLiteral("Test Browser"))
            browserId = entry.value(QStringLiteral("id")).toString();
    }
    check(nestedIdFound, QStringLiteral("nested desktop files receive XDG desktop-file IDs"));
    check(!browserId.isEmpty(), QStringLiteral("GliaSystemMenus exposes browser id for launch"));
    check(glia.places().size() == 7, QStringLiteral("all configured user places are discovered"));

    const QVariantList recent = glia.recentFiles();
    check(recent.size() == 1
              && recent.first().toMap().value(QStringLiteral("name")).toString()
                     == QStringLiteral("recent.txt"),
          QStringLiteral("XBEL yields existing local recent files only"));

    const quint64 parseCount = index->parseCount();
    const quint64 scanCount = index->scanCount();
    check(!index->scanNow(), QStringLiteral("unchanged synchronous verification scan reports no change"));
    check(index->parseCount() == parseCount, QStringLiteral("unchanged desktop files are not reparsed"));
    check(index->scanCount() == scanCount + 1, QStringLiteral("scan counter records explicit rescans"));

    QFile added(qEnvironmentVariable("MENU_TEST_NEW_APP"));
    check(added.open(QIODevice::WriteOnly | QIODevice::Text),
          QStringLiteral("test can add a desktop entry to the XDG tree"));
    if (added.isOpen()) {
        added.write("[Desktop Entry]\nType=Application\nName=Late App\nExec=record-app late\n"
                    "Categories=Utility;\n");
        added.close();
        const int changesBefore = modelChanges;
        model.reload();
        glia.rescan();
        check(waitUntil([&] {
                  return modelChanges > changesBefore && model.getApps({}, QStringLiteral("Late App")).size() == 1;
              }),
              QStringLiteral("reload/rescan publishes added desktop entries"));
        added.remove();
        const int removeChangesBefore = modelChanges;
        model.reload();
        check(waitUntil([&] {
                  return modelChanges > removeChangesBefore && model.getApps({}, QStringLiteral("Late App")).isEmpty();
              }),
              QStringLiteral("rescan removes deleted desktop entries"));
    }

    glia.launch(browserId);
    glia.openPath(qEnvironmentVariable("MENU_TEST_RECENT_FILE"));
    const bool launchesRecorded = waitUntil([&] {
              const QStringList lines = recordedLines();
              return lines.contains(QStringLiteral("browser ; literal"))
                  && lines.contains(QStringLiteral("OPEN:") + qEnvironmentVariable("MENU_TEST_RECENT_FILE"));
          });
    check(launchesRecorded,
          QStringLiteral("launch/openPath pass quoted argv to private recording executables"));
    check(recordedLines().contains(QStringLiteral("browser ; literal")),
          QStringLiteral("desktop Exec metacharacters remain one literal argument"));

    QTextStream(stdout) << "MENU TEST SUMMARY: " << failures << " failure(s)" << Qt::endl;
    return failures ? 1 : 0;
}
