// DesktopIndex — the ONE XDG .desktop index LaPivot keeps, shared by AppMenuModel (launcher / Launchpad /
// Exposé / HUD / AppMenu) and GliaSystemMenus (Glia's Applications menu).
// New in the rebuild (no oracle counterpart): the oracle had each class parse every .desktop file
// itself, both on the GUI thread before the first frame (ncde-efficiency.md "`.desktop` scans on the
// load path (MED)" + fix #7 "defer .desktop scans"), and re-parse every file on every reload().
// Spec: freedesktop Desktop Entry Specification 1.5 (Type, Name[locale], Exec field codes and quoting,
//   TryExec, Hidden, NoDisplay, OnlyShowIn/NotShowIn, Terminal, Path, desktop-file ids from subdirs),
//   XDG Base Directory spec (XDG_DATA_HOME first, then XDG_DATA_DIRS — first id found wins),
//   gliatalk.md ("Glia's gliaSystem .desktop/action reads").
#pragma once

#include <QDateTime>
#include <QHash>
#include <QList>
#include <QObject>
#include <QStringList>
#include <QThreadPool>

class QFileSystemWatcher;
class QTimer;

struct DesktopApp {
    QString id;          // desktop-file id ("org.gnome.Foo.desktop", "kde4-foo.desktop" for subdirs)
    QString file;        // absolute path
    QString name;        // localized Name
    QString icon;
    QString exec;        // the command line without field codes, QProcess::splitCommand-compatible
    QStringList argv;    // the same, as argv (terminal-wrapped when Terminal=true and a terminal exists)
    QString workDir;     // Path=
    QString category;    // the menu category (AppMenuModel::mapCategory labels)
    bool terminal = false;
    bool operator==(const DesktopApp &o) const {
        return id == o.id && file == o.file && name == o.name && icon == o.icon && exec == o.exec &&
               argv == o.argv && workDir == o.workDir && category == o.category && terminal == o.terminal;
    }
};

namespace DesktopEntry {
// Parse one file. Returns false when the entry must not be shown (not an Application, Hidden,
// NoDisplay, not for this desktop, TryExec missing, no Name/Exec). Shown or not, the first file
// found for an id owns it (a user's Hidden=true copy hides the system app — spec "Hidden").
bool parse(const QString &path, const QString &id, DesktopApp &out, const QStringList &terminal);
QStringList splitExec(const QString &exec, bool *ok = nullptr);   // spec quoting -> argv (no field codes)
QString joinForSplitCommand(const QStringList &argv);             // argv -> QProcess::splitCommand form
QString mapCategory(const QString &categories);                   // Categories= -> menu label
QStringList applicationDirs();                                    // precedence order
QStringList terminalCommand();                                    // e.g. {kitty,-e}; empty if none
}

class DesktopIndex : public QObject
{
    Q_OBJECT
public:
    static DesktopIndex *instance();       // created on first use, parented to QCoreApplication
    explicit DesktopIndex(QObject *parent = nullptr, const QStringList &dirs = {});
    ~DesktopIndex() override;

    const QList<DesktopApp> &apps() const { return m_apps; }
    bool ready() const { return m_ready; }
    quint64 parseCount() const { return m_parses; }   // files actually parsed (test/efficiency proof)
    quint64 scanCount() const { return m_scans; }

    void requestScan();   // async (worker thread), coalesced; appsChanged() only if the list changed
    bool scanNow();       // synchronous, stat-only for unchanged files; returns true if the list changed

signals:
    void appsChanged();

private:
    struct CacheEntry { QDateTime mtime; qint64 size = -1; bool show = false; DesktopApp app; };
    struct ScanResult { QList<DesktopApp> apps; QHash<QString, CacheEntry> cache; quint64 parses = 0; QStringList watchDirs; };
    static ScanResult scan(const QStringList &dirs, QHash<QString, CacheEntry> cache);
    bool install(ScanResult r);
    void rewatch(const QStringList &dirs);

    QStringList m_dirs;
    QList<DesktopApp> m_apps;
    QHash<QString, CacheEntry> m_cache;
    QFileSystemWatcher *m_watcher = nullptr;
    QTimer *m_debounce = nullptr;
    QThreadPool m_pool;
    quint64 m_gen = 0;          // bumped by every scan start; stale async results are dropped
    bool m_ready = false;
    bool m_asyncRunning = false;
    bool m_asyncAgain = false;
    quint64 m_parses = 0, m_scans = 0;
};
