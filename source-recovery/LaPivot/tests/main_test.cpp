#define main lapivot_entry_for_compile_check
#include "../src/main.cpp"
#undef main

#include <QCoreApplication>
#include <QFile>
#include <QByteArray>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    const QString base = ncde::assetBase();
    if (!QDir::isAbsolutePath(base) || !base.endsWith(QLatin1Char('/')))
        return 1;

    qputenv("NCDE_ASSET_BASE", "/opt/ncde-l2");
    if (ncde::assetBase() != QStringLiteral("/opt/ncde-l2/"))
        return 2;

    qputenv("NCDE_ASSET_BASE", "relative/path");
    if (ncde::assetBase() != QStringLiteral("/usr/share/ncde/"))
        return 3;
    qunsetenv("NCDE_ASSET_BASE");

    QFile source(QStringLiteral("src/main.cpp"));
    if (!source.open(QIODevice::ReadOnly))
        return 4;
    const QByteArray contents = source.readAll();
    const char *const expected[] = {
        "lelan", "ncde", "settings", "theme", "fontMgr", "widget_data",
        "animPolicy", "launcher", "notifications", "windowMgr", "calBackend",
        "ncdeWorkspace", "appMenuModel", "window", "pond", "gliaSystem", "geo", "hudManager"
    };
    qsizetype previous = -1;
    for (const char *name : expected) {
        const QByteArray binding = QByteArray("setContextProperty(QStringLiteral(\"") + name + "\")";
        const qsizetype position = contents.indexOf(binding);
        if (position <= previous)
            return 5;
        previous = position;
    }
    if (contents.contains("qml.load(QUrl(QStringLiteral(\"qrc:/Shell.qml\")))"))
        return 6;

    return 0;
}
