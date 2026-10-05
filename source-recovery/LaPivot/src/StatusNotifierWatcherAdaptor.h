// StatusNotifierWatcherAdaptor — the org.kde.StatusNotifierWatcher D-Bus face of SniWatcher.
// Rebuilt from oracle: decomp/StatusNotifierWatcherAdaptor.c (ctor, 3 property getters, 2 slots, 3 signals).
// Spec: docs/lelan-research-findings.md §4 (own org.kde.StatusNotifierWatcher AND the
//       org.freedesktop.StatusNotifierWatcher variant; RegisterStatusNotifierItem/Host, property
//       RegisteredStatusNotifierItems (as), IsStatusNotifierHostRegistered, ProtocolVersion, signals
//       StatusNotifierItemRegistered/Unregistered(s) + StatusNotifierHostRegistered()).
//
// DEFECTS FIXED vs oracle:
//  1. The oracle claimed the bus name org.freedesktop.StatusNotifierWatcher but exported ONLY the
//     org.kde.StatusNotifierWatcher interface on /StatusNotifierWatcher, so a client that talks the
//     freedesktop interface (the spec's own name, used by xfce-style items) got UnknownMethod and
//     never showed. Added FdoStatusNotifierWatcherAdaptor (separate header): the same surface under
//     interface org.freedesktop.StatusNotifierWatcher.

#pragma once

#include <QDBusAbstractAdaptor>
#include <QStringList>

class SniWatcher;

class StatusNotifierWatcherAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ RegisteredStatusNotifierItems)
    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ IsStatusNotifierHostRegistered)
    Q_PROPERTY(int ProtocolVersion READ ProtocolVersion)

public:
    explicit StatusNotifierWatcherAdaptor(SniWatcher *watcher);
    ~StatusNotifierWatcherAdaptor() override;

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
    SniWatcher *m_watcher;   // oracle +0x10
};