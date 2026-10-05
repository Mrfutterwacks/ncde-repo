// IdleInhibitService — implements the org.freedesktop.ScreenSaver D-Bus interface to allow
// applications to inhibit the screensaver and idle detection. Also resets the X idle timer
// via XCB ForceScreenSaver(Reset) when an inhibit cookie is active.
//
// Rebuilt from oracle: decomp/IdleInhibitService.c (11 functions: ctor, Inhibit, UnInhibit,
// dropOwner, resetIdle, dtor). Spec: freedesktop.org ScreenSaver interface, docs/wm-oracle-audit.md.
// The oracle interface (interfaces/LaPivot-metaobjects.h) has:
//   - Q_CLASSINFO("D-Bus Interface", "org.freedesktop.ScreenSaver")
//   - slots: Inhibit(QString app, QString reason) -> uint, UnInhibit(uint cookie)
//   - private slots: dropOwner(QString name), resetIdle()
//
// The oracle stores: xcb_connection_t*, QDBusServiceWatcher, QTimer (periodic resetIdle),
// QHash<uint, QString> cookies (cookie -> app name), nextCookie (starts at 1).
//
// DEFECTS FIXED vs oracle:
//  II1 the oracle's QTimer had no interval set (QTimer::setInterval called with no arg).
//     The interval was left at 0, causing a busy loop. Now set to 10000 ms (10 s) as the
//     spec suggests periodic reset.
//  II2 resetIdle() was called on every Inhibit() and on timer timeout, but also on
//     UnInhibit() when the hash became empty — this caused XCB round-trips even when no
//     inhibits were active. Now resetIdle() is only called when the cookie hash is non-empty.
//  II3 dropOwner(QString) iterated the entire hash to find matching app names (O(n)).
//     Now we keep a reverse mapping (app name -> list of cookies) for O(1) lookup.
//  II4 the oracle registered the D-Bus object at two paths (/org/freedesktop/ScreenSaver and
//     /ScreenSaver) with QDBusConnection::RegisterOption::ExportScriptableSlots. Kept for
//     compatibility but documented.
#pragma once

#include <QChar>
#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusServiceWatcher>
#include <QHash>
#include <QObject>
#include <QTimer>
#include <xcb/xcb.h>

class IdleInhibitService : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.ScreenSaver")

public:
    explicit IdleInhibitService(QObject *parent = nullptr);
    ~IdleInhibitService() override;

public slots:
    // D-Bus method: Inhibit(application_name, reason_for_inhibit) -> cookie
    uint Inhibit(const QString &application_name, const QString &reason_for_inhibit);

    // D-Bus method: UnInhibit(cookie)
    void UnInhibit(uint cookie);

private slots:
    // Called when a watched service disappears (owner dropped the bus)
    void dropOwner(const QString &serviceName);

    // Periodic reset of X idle timer while inhibits are active
    void resetIdle();

private:
    xcb_connection_t *m_xcb = nullptr;
    QDBusServiceWatcher *m_watcher = nullptr;
    QTimer *m_timer = nullptr;
    QHash<uint, QString> m_cookies;           // cookie -> app name
    QHash<QString, QList<uint>> m_ownerMap;   // app name -> list of cookies
    uint m_nextCookie = 1;
};