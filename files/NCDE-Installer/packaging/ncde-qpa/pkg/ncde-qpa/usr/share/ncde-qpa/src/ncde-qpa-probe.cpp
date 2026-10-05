// ncde-qpa-probe <path/to/libncde-qpa.so> — exit 0 only if Qt loads that exact
// file as its platform theme and it serves a menu bar (the job it exists for).
// Built by ncde-qpa-rebuild alongside the plugin, against the same Qt.
#include <QGuiApplication>
#include <QByteArray>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <qpa/qplatformtheme.h>
#include <qpa/qplatformmenu.h>
#include <private/qguiapplication_p.h>
#include <cstdio>
#include <cstdlib>
#include <QFile>
#include <unistd.h>
int main(int argc, char **argv)
{
    if (argc < 2) { std::fprintf(stderr, "usage: ncde-qpa-probe <plugin.so>\n"); return 2; }
    QFileInfo so(QString::fromLocal8Bit(argv[1]));
    QDir tmp(QDir::tempPath());
    QString root = tmp.filePath(QStringLiteral("ncde-qpa-probe-%1").arg(getpid()));
    QDir().mkpath(root + QStringLiteral("/platformthemes"));
    QFile::remove(root + QStringLiteral("/platformthemes/libncde-qpa.so"));
    QFile::link(so.absoluteFilePath(), root + QStringLiteral("/platformthemes/libncde-qpa.so"));
    // Only this root is searched, so the machine's installed copy can't answer
    // for the file under test; platforms/ points at the system dir for offscreen.
    QFile::link(QLibraryInfo::path(QLibraryInfo::PluginsPath) + QStringLiteral("/platforms"),
                root + QStringLiteral("/platforms"));
    QCoreApplication::setLibraryPaths({ root });
    qputenv("QT_QPA_PLATFORM", "offscreen");
    qputenv("QT_QPA_PLATFORMTHEME", "ncde");
    int rc = 1;
    {
        int c = 1; char *v[] = { argv[0], nullptr };
        QGuiApplication app(c, v);
        QPlatformTheme *t = QGuiApplicationPrivate::platformTheme();
        QPlatformMenuBar *mb = t ? t->createPlatformMenuBar() : nullptr;
        rc = mb ? 0 : 1;
        delete mb;
    }
    QDir(root).removeRecursively();
    std::puts(rc == 0 ? "ncde-qpa: ok" : "ncde-qpa: NOT loaded");
    return rc;
}
