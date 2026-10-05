// FdoStatusNotifierWatcherAdaptor.cpp — implementation
// NEW CLASS (not in oracle): the oracle claimed the bus name org.freedesktop.StatusNotifierWatcher
// but exported ONLY the org.kde.StatusNotifierWatcher interface on /StatusNotifierWatcher.
// This class provides the freedesktop interface on the same object path.
// Spec: docs/lelan-research-findings.md §4 (own org.kde.StatusNotifierWatcher AND the
//       org.freedesktop.StatusNotifierWatcher variant).
// DEFECT FIXED vs oracle: freedesktop clients (xfce-style items) now work.

#include "FdoStatusNotifierWatcherAdaptor.h"
#include "SniWatcher.h"

FdoStatusNotifierWatcherAdaptor::FdoStatusNotifierWatcherAdaptor(SniWatcher *watcher)
    : QDBusAbstractAdaptor(watcher)
    , m_watcher(watcher)
{
}

QStringList FdoStatusNotifierWatcherAdaptor::RegisteredStatusNotifierItems() const
{
    return m_watcher->items();
}

bool FdoStatusNotifierWatcherAdaptor::IsStatusNotifierHostRegistered() const
{
    return m_watcher->hostRegistered();
}

int FdoStatusNotifierWatcherAdaptor::ProtocolVersion() const
{
    return 0;
}

void FdoStatusNotifierWatcherAdaptor::RegisterStatusNotifierItem(const QString &service)
{
    m_watcher->registerItem(service);
}

void FdoStatusNotifierWatcherAdaptor::RegisterStatusNotifierHost(const QString &service)
{
    m_watcher->registerHost(service);
}