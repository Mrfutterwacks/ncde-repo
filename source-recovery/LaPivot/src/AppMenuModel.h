// AppMenuModel — the global app-menu model / AppMenu registrar bridge feeding the GliaTalk relay.
// Context in QML: `appMenuModel`
// Rebuilt from oracle: decomp/AppMenuModel.c (ctor, dtor, reload, getCategories, getApps, parseDesktop,
//   stripFieldCodes, mapCategory, changed signal + AppEntry struct). Oracle count: 11 functions.
// Spec: ncde-architecture.md §2 (AppMenuModel = global app-menu model / AppMenu registrar bridge),
//   ncde-efficiency.md #7 (defer .desktop scans off load path), DesktopEntry namespace in
//   AppMenuModel_index.h (shared DesktopIndex with GliaSystemMenus).
// DEFECTS FIXED vs oracle:
//  1. Oracle re-parsed every .desktop file on the GUI thread in ctor (QTimer::singleShot 0) and every
//     reload() — blocked first frame + every manual reload. Rebuild uses DesktopIndex (async worker
//     thread, cached, stat-only re-scans, appsChanged only on actual list change).
//  2. Oracle's parseDesktop used QSettings per file (slow, blocking). DesktopIndex uses the same
//     parsing logic but off the GUI thread with mtime/size caching.
//  3. Oracle's stripFieldCodes removed field codes (%f %u %U etc.) but did it per-call; DesktopIndex
//     does it once at parse time and stores cleaned argv.
//  4. Oracle had no change check before emitting changed() — emitted on every reload even if identical.
//     DesktopIndex only emits appsChanged when the app list actually changed; AppMenuModel forwards.
//  5. Oracle's getApps returned QList<QVariant> of QMaps with name/exec/icon/category — correct shape
//     but inefficient. Rebuild uses DesktopIndex's ready apps() and filters by category/search.

#pragma once

#include <QObject>
#include <QStringList>
#include <QVariantList>

#include "AppMenuModel_index.h"

class DesktopIndex;

class AppMenuModel : public QObject
{
    Q_OBJECT

public:
    explicit AppMenuModel(QObject *parent = nullptr);
    ~AppMenuModel() override;

    Q_INVOKABLE void reload();
    Q_INVOKABLE QStringList getCategories() const;
    Q_INVOKABLE QVariantList getApps(const QString &category, const QString &search) const;

signals:
    void changed();

private:
    DesktopIndex *m_index = nullptr;
    QList<DesktopApp> m_cachedApps;
    QStringList m_cachedCategories;
    bool m_ready = false;

    void onIndexReady();
    void rebuildCache();
    QString mapCategory(const QString &categories) const;  // oracle's mapCategory logic
};