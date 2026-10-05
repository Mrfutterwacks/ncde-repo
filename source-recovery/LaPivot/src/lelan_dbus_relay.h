// lelan_dbus_relay.h — small receivers for D-Bus signals whose slots must stay off Lelan's QML-facing
// interface (Lelan's metaobject is the oracle's plus declared additions only).
#pragma once

#include <QDBusContext>
#include <QDBusMessage>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <functional>

// PropertiesChanged with the sender's object path (access points, BlueZ devices): one match rule
// covers every object of a kind, and only a QDBusContext slot sees which object sent it.
class PropsRelay : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    using Fn = std::function<void(const QString &path, const QString &iface, const QVariantMap &changed)>;
    explicit PropsRelay(QObject *parent, Fn fn) : QObject(parent), m_fn(std::move(fn)) {}
public slots:
    void propertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
    {
        m_fn(message().path(), iface, changed);
    }
private:
    Fn m_fn;
};

// Any D-Bus signal -> a callback (signal arguments ignored), also kept off Lelan's interface.
class DBusSignalRelay : public QObject
{
    Q_OBJECT
public:
    explicit DBusSignalRelay(QObject *parent, std::function<void()> fn) : QObject(parent), m_fn(std::move(fn)) {}
public slots:
    void fire() { m_fn(); }
private:
    std::function<void()> m_fn;
};


// MPRIS players: PropertiesChanged and Seeked with the sender's unique bus name, so a signal is applied to
// the player that sent it (the oracle's slots could not tell players apart).
class MprisRelay : public QObject, protected QDBusContext
{
    Q_OBJECT
public:
    using PropsFn = std::function<void(const QString &sender, const QVariantMap &changed)>;
    using SeekFn = std::function<void(const QString &sender, qlonglong positionUs)>;
    MprisRelay(QObject *parent, PropsFn props, SeekFn seek) : QObject(parent), m_props(std::move(props)), m_seek(std::move(seek)) {}
public slots:
    void propertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
    {
        if (iface == QLatin1String("org.mpris.MediaPlayer2.Player"))
            m_props(message().service(), changed);
    }
    void seeked(qlonglong positionUs) { m_seek(message().service(), positionUs); }
private:
    PropsFn m_props;
    SeekFn m_seek;
};
