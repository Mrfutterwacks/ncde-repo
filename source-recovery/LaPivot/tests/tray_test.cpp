#include <QCoreApplication>
#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QElapsedTimer>
#include <QTextStream>
#include <QThread>

#include "../src/SniWatcher.h"

#include <functional>

namespace {

constexpr auto watcherService = "org.kde.StatusNotifierWatcher";
constexpr auto watcherPath = "/StatusNotifierWatcher";
constexpr auto kdeInterface = "org.kde.StatusNotifierWatcher";
constexpr auto fdoInterface = "org.freedesktop.StatusNotifierWatcher";

int failures = 0;

void check(bool condition, const QString &message)
{
    QTextStream out(condition ? stdout : stderr);
    out << (condition ? "PASS: " : "FAIL: ") << message << Qt::endl;
    if (!condition)
        ++failures;
}

bool waitUntil(const std::function<bool()> &predicate, int timeoutMs = 3000)
{
    QElapsedTimer timer;
    timer.start();
    while (!predicate() && timer.elapsed() < timeoutMs) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 25);
        QThread::msleep(5);
    }
    QCoreApplication::processEvents(QEventLoop::AllEvents, 25);
    return predicate();
}

class BusSignals : public QObject
{
    Q_OBJECT
public:
    QStringList registered;
    QStringList unregistered;
    int hostSignals = 0;

public slots:
    void onRegistered(const QString &service) { registered.append(service); }
    void onUnregistered(const QString &service) { unregistered.append(service); }
    void onHostRegistered() { ++hostSignals; }
};

class FakeWatcher;

class FakeWatcherAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ registeredItems)
    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ hostRegistered)
    Q_PROPERTY(int ProtocolVersion READ protocolVersion)

public:
    explicit FakeWatcherAdaptor(FakeWatcher *watcher);
    QStringList registeredItems() const;
    bool hostRegistered() const;
    int protocolVersion() const { return 0; }

public slots:
    void RegisterStatusNotifierItem(const QString &service);
    void RegisterStatusNotifierHost(const QString &service);

signals:
    void StatusNotifierItemRegistered(const QString &service);
    void StatusNotifierItemUnregistered(const QString &service);
    void StatusNotifierHostRegistered();

private:
    FakeWatcher *m_watcher = nullptr;
};

class FakeWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FakeWatcher(QObject *parent = nullptr)
        : QObject(parent)
        , adaptor(new FakeWatcherAdaptor(this))
    {
    }

    QStringList items;
    QStringList hosts;
    FakeWatcherAdaptor *adaptor = nullptr;

    void addItem(const QString &service)
    {
        if (items.contains(service))
            return;
        items.append(service);
        emit adaptor->StatusNotifierItemRegistered(service);
    }

    void removeItem(const QString &service)
    {
        if (!items.removeOne(service))
            return;
        emit adaptor->StatusNotifierItemUnregistered(service);
    }
};

FakeWatcherAdaptor::FakeWatcherAdaptor(FakeWatcher *watcher)
    : QDBusAbstractAdaptor(watcher)
    , m_watcher(watcher)
{
}

QStringList FakeWatcherAdaptor::registeredItems() const
{
    return m_watcher->items;
}

bool FakeWatcherAdaptor::hostRegistered() const
{
    return !m_watcher->hosts.isEmpty();
}

void FakeWatcherAdaptor::RegisterStatusNotifierItem(const QString &service)
{
    m_watcher->addItem(service);
}

void FakeWatcherAdaptor::RegisterStatusNotifierHost(const QString &service)
{
    if (m_watcher->hosts.contains(service))
        return;
    m_watcher->hosts.append(service);
    emit StatusNotifierHostRegistered();
}

QDBusMessage asyncMessage(QDBusConnection &bus, const QDBusMessage &message)
{
    auto *call = new QDBusPendingCallWatcher(bus.asyncCall(message), QCoreApplication::instance());
    const bool completed = waitUntil([call] { return call->isFinished(); });
    const QDBusMessage reply = completed ? call->reply() : QDBusMessage();
    call->deleteLater();
    return reply;
}

QVariant property(QDBusConnection &bus, const QString &service, const QString &interface,
                  const QString &name)
{
    QDBusMessage message = QDBusMessage::createMethodCall(
        service, QString::fromLatin1(watcherPath),
        QStringLiteral("org.freedesktop.DBus.Properties"), QStringLiteral("Get"));
    message << interface << name;
    const QDBusMessage reply = asyncMessage(bus, message);
    if (reply.type() != QDBusMessage::ReplyMessage || reply.arguments().isEmpty())
        return {};
    const QVariant value = reply.arguments().constFirst();
    return value.canConvert<QDBusVariant>() ? value.value<QDBusVariant>().variant() : value;
}

bool asyncMethodCall(QDBusConnection &bus, const QString &service, const QString &interface,
                     const QString &method, const QVariantList &arguments = {})
{
    QDBusMessage message = QDBusMessage::createMethodCall(
        service, QString::fromLatin1(watcherPath), interface, method);
    message.setArguments(arguments);
    return asyncMessage(bus, message).type() == QDBusMessage::ReplyMessage;
}

} // namespace

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QDBusConnection client = QDBusConnection::connectToBus(
        QDBusConnection::SessionBus, QStringLiteral("tray-test-client"));
    check(client.isConnected(), QStringLiteral("separate private-bus client connects"));
    if (!client.isConnected())
        return 1;

    {
        SniWatcher watcher;
        BusSignals busSignals;
        client.connect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                       QString::fromLatin1(kdeInterface),
                       QStringLiteral("StatusNotifierItemRegistered"),
                       &busSignals, SLOT(onRegistered(QString)));
        client.connect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                       QString::fromLatin1(kdeInterface),
                       QStringLiteral("StatusNotifierItemUnregistered"),
                       &busSignals, SLOT(onUnregistered(QString)));
        client.connect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                       QString::fromLatin1(kdeInterface),
                       QStringLiteral("StatusNotifierHostRegistered"),
                       &busSignals, SLOT(onHostRegistered()));
        client.connect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                       QString::fromLatin1(fdoInterface),
                       QStringLiteral("StatusNotifierItemRegistered"),
                       &busSignals, SLOT(onRegistered(QString)));
        client.connect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                       QString::fromLatin1(fdoInterface),
                       QStringLiteral("StatusNotifierItemUnregistered"),
                       &busSignals, SLOT(onUnregistered(QString)));

        check(watcher.ownsWatcherName(), QStringLiteral("watcher owns the primary KDE name on the private bus"));
        check(waitUntil([&] { return watcher.hostRegistered(); }),
              QStringLiteral("watcher registers its own host service"));
        check(property(client, QString::fromLatin1(watcherService), QString::fromLatin1(kdeInterface),
                       QStringLiteral("ProtocolVersion")).toInt() == 0,
              QStringLiteral("KDE adaptor exposes oracle ProtocolVersion"));
        QDBusMessage introspect = QDBusMessage::createMethodCall(
            QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
            QStringLiteral("org.freedesktop.DBus.Introspectable"), QStringLiteral("Introspect"));
        const QDBusMessage introspection = asyncMessage(client, introspect);
        check(introspection.type() == QDBusMessage::ReplyMessage
                  && introspection.arguments().constFirst().toString().contains(QString::fromLatin1(fdoInterface)),
              QStringLiteral("freedesktop adaptor appears in private-bus introspection"));
        check(property(client, QString::fromLatin1(watcherService), QString::fromLatin1(fdoInterface),
                       QStringLiteral("IsStatusNotifierHostRegistered")).toBool(),
              QStringLiteral("freedesktop adaptor exposes host property"));

        const QString itemService = QStringLiteral("org.example.TestStatusNotifierItem");
        check(client.interface()->registerService(
                  itemService, QDBusConnectionInterface::DontQueueService,
                  QDBusConnectionInterface::DontAllowReplacement).value()
                  == QDBusConnectionInterface::ServiceRegistered,
              QStringLiteral("fake item owns a private-bus service name"));

        check(asyncMethodCall(client, QString::fromLatin1(watcherService),
                              QString::fromLatin1(kdeInterface),
                              QStringLiteral("RegisterStatusNotifierItem"), {itemService}),
              QStringLiteral("KDE D-Bus RegisterStatusNotifierItem succeeds"));
        check(waitUntil([&] { return watcher.items().contains(itemService); }),
              QStringLiteral("registered SNI item reaches watcher registry"));
        check(busSignals.registered.contains(itemService),
              QStringLiteral("itemRegistered is forwarded as a KDE D-Bus signal"));
        check(property(client, QString::fromLatin1(watcherService), QString::fromLatin1(kdeInterface),
                       QStringLiteral("RegisteredStatusNotifierItems")).toStringList()
                  .contains(itemService),
              QStringLiteral("KDE property returns the registered item list"));

        QDBusConnection pathClient = QDBusConnection::connectToBus(
            QDBusConnection::SessionBus, QStringLiteral("tray-test-path-client"));
        const QString pathService = QStringLiteral("org.example.PathStatusNotifierItem");
        pathClient.interface()->registerService(
            pathService, QDBusConnectionInterface::DontQueueService,
            QDBusConnectionInterface::DontAllowReplacement);
        check(asyncMethodCall(pathClient, QString::fromLatin1(watcherService),
                              QString::fromLatin1(fdoInterface),
                              QStringLiteral("RegisterStatusNotifierItem"),
                              {QStringLiteral("/StatusNotifierItem")}),
              QStringLiteral("freedesktop object-path registration succeeds"));
        const QString pathKey = pathClient.baseService() + QStringLiteral("/StatusNotifierItem");
        check(waitUntil([&] { return watcher.items().contains(pathKey); }),
              QStringLiteral("path-only registration is qualified with the D-Bus caller"));
        check(busSignals.registered.contains(pathKey),
              QStringLiteral("freedesktop registration also forwards watcher signals"));

        client.interface()->unregisterService(itemService);
        pathClient.interface()->unregisterService(pathService);
        QDBusConnection::disconnectFromBus(QStringLiteral("tray-test-path-client"));
        check(waitUntil([&] { return watcher.items().isEmpty(); }),
              QStringLiteral("NameOwnerChanged removes every item owned by an exiting service"));
        check(busSignals.unregistered.contains(itemService)
                  && busSignals.unregistered.contains(pathKey),
              QStringLiteral("item removal is forwarded as D-Bus unregistration signals"));

        client.disconnect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                          QString::fromLatin1(kdeInterface),
                          QStringLiteral("StatusNotifierItemRegistered"),
                          &busSignals, SLOT(onRegistered(QString)));
        client.disconnect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                          QString::fromLatin1(kdeInterface),
                          QStringLiteral("StatusNotifierItemUnregistered"),
                          &busSignals, SLOT(onUnregistered(QString)));
        client.disconnect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                          QString::fromLatin1(kdeInterface),
                          QStringLiteral("StatusNotifierHostRegistered"),
                          &busSignals, SLOT(onHostRegistered()));
        client.disconnect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                          QString::fromLatin1(fdoInterface),
                          QStringLiteral("StatusNotifierItemRegistered"),
                          &busSignals, SLOT(onRegistered(QString)));
        client.disconnect(QString::fromLatin1(watcherService), QString::fromLatin1(watcherPath),
                          QString::fromLatin1(fdoInterface),
                          QStringLiteral("StatusNotifierItemUnregistered"),
                          &busSignals, SLOT(onUnregistered(QString)));
    }

    {
        FakeWatcher foreign;
        foreign.items = {QStringLiteral("org.example.RemoteItem")};
        check(client.registerObject(QString::fromLatin1(watcherPath), &foreign,
                                   QDBusConnection::ExportAdaptors),
              QStringLiteral("fake foreign watcher object exports on the private bus"));
        check(client.interface()->registerService(
                  QString::fromLatin1(watcherService), QDBusConnectionInterface::DontQueueService,
                  QDBusConnectionInterface::DontAllowReplacement).value()
                  == QDBusConnectionInterface::ServiceRegistered,
              QStringLiteral("fake foreign watcher owns only the private KDE watcher name"));

        SniWatcher relayWatcher;
        check(waitUntil([&] {
                  return relayWatcher.items().contains(QStringLiteral("org.example.RemoteItem"));
              }),
              QStringLiteral("foreign-watcher relay asynchronously imports existing items"));
        foreign.addItem(QStringLiteral("org.example.LateRemoteItem"));
        check(waitUntil([&] {
                  return relayWatcher.items().contains(QStringLiteral("org.example.LateRemoteItem"));
              }),
              QStringLiteral("foreign-watcher relay follows item registration signals"));
        foreign.removeItem(QStringLiteral("org.example.RemoteItem"));
        check(waitUntil([&] {
                  return !relayWatcher.items().contains(QStringLiteral("org.example.RemoteItem"));
              }),
              QStringLiteral("foreign-watcher relay follows item unregistration signals"));

        client.interface()->unregisterService(QString::fromLatin1(watcherService));
        check(waitUntil([&] { return relayWatcher.ownsWatcherName(); }),
              QStringLiteral("watcher reclaims its primary name when the foreign watcher exits"));
        check(relayWatcher.items().isEmpty(),
              QStringLiteral("foreign items are removed when the foreign watcher disappears"));
        client.unregisterObject(QString::fromLatin1(watcherPath));
    }

    QDBusConnection::disconnectFromBus(QStringLiteral("tray-test-client"));
    QTextStream(stdout) << "TRAY TEST SUMMARY: " << failures << " failure(s)" << Qt::endl;
    return failures ? 1 : 0;
}

#include "tray_test.moc"
