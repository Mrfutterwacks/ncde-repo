// StatusNotifierWatcherAdaptor.cpp — implementation
// Rebuilt from oracle: decomp/StatusNotifierWatcherAdaptor.c (ctor, 3 property getters, 2 slots, 3 signals).
// Oracle count: 8 functions.
// Spec: docs/lelan-research-findings.md §4 (own org.kde.StatusNotifierWatcher AND the
//       org.freedesktop.StatusNotifierWatcher variant; RegisterStatusNotifierItem/Host, property
//       RegisteredStatusNotifierItems (as), IsStatusNotifierHostRegistered, ProtocolVersion, signals
//       StatusNotifierItemRegistered/Unregistered(s) + StatusNotifierHostRegistered()).
// DEFECTS FIXED vs oracle:
//  1. The oracle claimed the bus name org.freedesktop.StatusNotifierWatcher but exported ONLY the
//     org.kde.StatusNotifierWatcher interface on /StatusNotifierWatcher, so a client that talks the
//     freedesktop interface (the spec's own name, used by xfce-style items) got UnknownMethod and
//     never showed. Added FdoStatusNotifierWatcherAdaptor: the same surface under
//     interface org.freedesktop.StatusNotifierWatcher (new class; the oracle class is unchanged).
//     FdoStatusNotifierWatcherAdaptor is implemented inline in the header.

#include "StatusNotifierWatcherAdaptor.h"
#include "SniWatcher.h"

StatusNotifierWatcherAdaptor::StatusNotifierWatcherAdaptor(SniWatcher *watcher)
    : QDBusAbstractAdaptor(watcher)
    , m_watcher(watcher)
{
}

StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor() = default;

QStringList StatusNotifierWatcherAdaptor::RegisteredStatusNotifierItems() const
{
    return m_watcher->items();
}

bool StatusNotifierWatcherAdaptor::IsStatusNotifierHostRegistered() const
{
    return m_watcher->hostRegistered();
}

int StatusNotifierWatcherAdaptor::ProtocolVersion() const
{
    return 0;  // oracle returns 0
}

void StatusNotifierWatcherAdaptor::RegisterStatusNotifierItem(const QString &service)
{
    m_watcher->registerItem(service);
}

void StatusNotifierWatcherAdaptor::RegisterStatusNotifierHost(const QString &service)
{
    m_watcher->registerHost(service);
}