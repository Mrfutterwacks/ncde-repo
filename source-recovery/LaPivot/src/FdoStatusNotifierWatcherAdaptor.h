// FdoStatusNotifierWatcherAdaptor — the org.freedesktop.StatusNotifierWatcher D-Bus face of SniWatcher.
// NEW CLASS (not in oracle): the oracle claimed the bus name org.freedesktop.StatusNotifierWatcher
// but exported ONLY the org.kde.StatusNotifierWatcher interface on /StatusNotifierWatcher.
// This class provides the freedesktop interface on the same object path.
// Spec: docs/lelan-research-findings.md §4 (own org.kde.StatusNotifierWatcher AND the
//       org.freedesktop.StatusNotifierWatcher variant).
// DEFECT FIXED vs oracle: freedesktop clients (xfce-style items) now work.

#pragma once

#include <QDBusAbstractAdaptor>
#include <QStringList>

class SniWatcher;

class FdoStatusNotifierWatcherAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.StatusNotifierWatcher")
    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ RegisteredStatusNotifierItems)
    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ IsStatusNotifierHostRegistered)
    Q_PROPERTY(int ProtocolVersion READ ProtocolVersion)

public:
    explicit FdoStatusNotifierWatcherAdaptor(SniWatcher *watcher);

    QStringList RegisteredStatusNotifierItems() const;
    bool IsStatusNotifierHostRegistered() const;
    int ProtocolVersion() const;

signals:
    void StatusNotifierItemRegistered(const QString &service);
    void StatusNotifierItemUnregistered(const QString &service);
    void StatusNotifierHostRegistered();

public slots:
    void RegisterStatusNotifierItem(const QString &service);
    void RegisterStatusNotifierHost(const QString &service);

private:
    SniWatcher *m_watcher;
};