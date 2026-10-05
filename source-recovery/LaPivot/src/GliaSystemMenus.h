// GliaSystemMenus — XDG .desktop scanner/launcher (apps + places + recent files).
// Context in QML: `gliaSystem`
// Rebuilt from oracle: decomp/GliaSystemMenus.c (ctor, dtor, changed, applications, places,
//   recentFiles, rescan, launch, openPath + 3 properties). Oracle count: 10 functions.
// Spec: ncde-architecture.md §2 (GliaSystemMenus = XDG .desktop scanner/launcher),
//   ncde-efficiency.md #7 (defer .desktop scans off load path), gliatalk.md (file-based actions),
//   DesktopEntry namespace in AppMenuModel_index.h (shared DesktopIndex with AppMenuModel).
// DEFECTS FIXED vs oracle:
//  1. Oracle re-parsed every .desktop file on the GUI thread in ctor (QTimer::singleShot 0) and every
//     rescan() — blocked first frame + every manual rescan. Rebuild uses DesktopIndex (async worker
//     thread, cached, stat-only re-scans, appsChanged only on actual list change).
//  2. Oracle's rescan() used QSettings per file (slow, blocking). DesktopIndex uses the same
//     parsing logic but off the GUI thread with mtime/size caching.
//  3. Oracle had no change check before emitting changed() — emitted on every rescan even if identical.
//     DesktopIndex only emits appsChanged when the app list actually changed; GliaSystemMenus forwards.
//  4. Oracle's recentFiles() parsed ~/.local/share/recently-used.xbel on every access (blocking I/O on
//     GUI thread). Rebuild caches the parsed result and only re-reads when the file mtime changes.
//  5. Oracle's launch() did linear search through applications list on every call. Rebuild uses
//     DesktopIndex's apps() which is already in memory; search is O(n) but n is small and in-memory.

#pragma once

#include <QObject>
#include <QVariantList>

class DesktopIndex;
class QFileSystemWatcher;
class QTimer;

class GliaSystemMenus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList applications READ applications NOTIFY changed)
    Q_PROPERTY(QVariantList places READ places NOTIFY changed)
    Q_PROPERTY(QVariantList recentFiles READ recentFiles NOTIFY changed)

public:
    explicit GliaSystemMenus(QObject *parent = nullptr);
    ~GliaSystemMenus() override;

    QVariantList applications() const;
    QVariantList places() const;
    QVariantList recentFiles() const;

    Q_INVOKABLE void rescan();
    Q_INVOKABLE void launch(const QString &execOrId);
    Q_INVOKABLE void openPath(const QString &path);

signals:
    void changed();

private:
    DesktopIndex *m_index = nullptr;
    QVariantList m_cachedApplications;
    QVariantList m_cachedPlaces;
    QVariantList m_cachedRecentFiles;
    bool m_ready = false;

    QFileSystemWatcher *m_recentWatcher = nullptr;
    QTimer *m_recentDebounce = nullptr;
    QString m_recentPath;
    QString m_recentDirectory;

    void onIndexReady();
    void rebuildApplications();
    void rebuildPlaces();
    void rebuildRecentFiles();
    void onRecentFileChanged(const QString &path);
};