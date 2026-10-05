#include "Lelan.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QElapsedTimer>
#include <QFile>
#include <QProcessEnvironment>
#include <QTextStream>
#include <QThread>
#include <QTimer>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

class FakeAccountUser final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Accounts.User")
    Q_PROPERTY(QString UserName READ userName)
    Q_PROPERTY(QString RealName READ realName)
    Q_PROPERTY(uint AccountType READ accountType)
    Q_PROPERTY(uint PasswordMode READ passwordMode)
    Q_PROPERTY(bool AutomaticLogin READ automaticLogin)
    Q_PROPERTY(QString IconFile READ iconFile)
public:
    FakeAccountUser(QString name, uint accountType, QObject *parent = nullptr)
        : QObject(parent), m_name(std::move(name)), m_accountType(accountType) {}
    QString userName() const { return m_name; }
    QString realName() const { return m_realName; }
    uint accountType() const { return m_accountType; }
    uint passwordMode() const { return m_passwordMode; }
    bool automaticLogin() const { return m_autoLogin; }
    QString iconFile() const { return m_iconFile; }
    bool passwordSet = false;
    bool deleted = false;
    bool removeHome = true;
    std::function<void(bool)> deleteRequested;

public slots:
    void SetPassword(const QString &password, const QString &)
    {
        passwordSet = !password.isEmpty();
        m_passwordMode = passwordSet ? 0 : 1;
    }
    void SetAccountType(uint type) { m_accountType = type; }
    void SetAutomaticLogin(bool enabled) { m_autoLogin = enabled; }
    void SetIconFile(const QString &file) { m_iconFile = file; }
    void Delete(bool removeFiles)
    {
        deleted = true;
        removeHome = removeFiles;
        if (deleteRequested)
            deleteRequested(removeFiles);
    }

private:
    QString m_name;
    QString m_realName;
    uint m_accountType = 0;
    uint m_passwordMode = 0;
    bool m_autoLogin = false;
    QString m_iconFile = QStringLiteral("/usr/share/ncde/avatars/01-full-moon.svg");
};

class FakeAccounts final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Accounts")
public:
    explicit FakeAccounts(QDBusConnection bus) : m_bus(std::move(bus))
    {
        const QString name = QString::fromLocal8Bit(qgetenv("USER"));
        addUser(name.isEmpty() ? QStringLiteral("operator") : name, 1000, 1);
    }

public slots:
    QList<QDBusObjectPath> ListCachedUsers() const
    {
        QList<QDBusObjectPath> result;
        for (auto it = m_users.cbegin(); it != m_users.cend(); ++it)
            result.append(it.value().first);
        return result;
    }
    QDBusObjectPath CreateUser(const QString &name, const QString &, uint type)
    {
        return addUser(name, m_nextUid++, type);
    }
    QDBusObjectPath FindUserByName(const QString &name) const
    {
        for (auto it = m_users.cbegin(); it != m_users.cend(); ++it)
            if (it.key() == name)
                return it.value().first;
        return QDBusObjectPath(QStringLiteral("/"));
    }
    FakeAccountUser *user(const QString &name) const { return m_users.value(name).second; }

signals:
    void UserAdded(const QDBusObjectPath &path);
    void UserDeleted(const QDBusObjectPath &path);

private:
    QDBusObjectPath addUser(const QString &name, uint uid, uint type)
    {
        const QDBusObjectPath path(QStringLiteral("/org/freedesktop/Accounts/User%1").arg(uid));
        auto *user = new FakeAccountUser(name, type, this);
        if (!m_bus.registerObject(path.path(), user,
                                  QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllProperties)) {
            delete user;
            return QDBusObjectPath(QStringLiteral("/"));
        }
        m_users.insert(name, qMakePair(path, user));
        user->deleteRequested = [this, name, path](bool) {
            QTimer::singleShot(0, this, [this, name, path] {
                m_bus.unregisterObject(path.path());
                m_users.remove(name);
                emit UserDeleted(path);
            });
        };
        return path;
    }
    QDBusConnection m_bus;
    QMap<QString, QPair<QDBusObjectPath, FakeAccountUser *>> m_users;
    uint m_nextUid = 90001;
};

class FakePackageTransaction final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.PackageKit.Transaction")
public:
    explicit FakePackageTransaction(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    void Cancel() {}
signals:
    void Package(uint info, const QString &packageId, const QString &summary);
    void Finished(uint exit, uint runtime);
};

class FakePackageKit final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.PackageKit")
public:
    explicit FakePackageKit(QDBusConnection bus) : m_bus(std::move(bus))
    {
        m_transaction = new FakePackageTransaction(this);
        m_bus.registerObject(QStringLiteral("/org/freedesktop/PackageKit/transactions/1"), m_transaction,
                             QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);
    }
public slots:
    QDBusObjectPath GetUpdates(const QStringList &filters)
    {
        filtersEmpty = filters.isEmpty();
        QTimer::singleShot(60, m_transaction, [this] {
            emit m_transaction->Package(2, QStringLiteral("test;1.0;x86_64;repo"),
                                        QStringLiteral("Fake package update"));
            emit m_transaction->Finished(0, 1);
        });
        return QDBusObjectPath(QStringLiteral("/org/freedesktop/PackageKit/transactions/1"));
    }
signals:
    void UpdatesChanged();
public:
    bool filtersEmpty = false;
private:
    QDBusConnection m_bus;
    FakePackageTransaction *m_transaction = nullptr;
};

class FakeTrayItem final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierItem")
    Q_PROPERTY(QString Id READ id)
    Q_PROPERTY(QString Title READ title)
    Q_PROPERTY(QString Category READ category)
    Q_PROPERTY(QString Status READ status)
    Q_PROPERTY(QString IconName READ iconName)
    Q_PROPERTY(QString AttentionIconName READ attentionIconName)
    Q_PROPERTY(QDBusObjectPath Menu READ menu)
    Q_PROPERTY(bool ItemIsMenu READ itemIsMenu)
public:
    QString id() const { return QStringLiteral("fake-item"); }
    QString title() const { return QStringLiteral("Fake tray item"); }
    QString category() const { return QStringLiteral("ApplicationStatus"); }
    QString status() const { return QStringLiteral("Active"); }
    QString iconName() const { return QStringLiteral("fake-icon"); }
    QString attentionIconName() const { return {}; }
    QDBusObjectPath menu() const { return QDBusObjectPath(QStringLiteral("/Menu")); }
    bool itemIsMenu() const { return false; }
signals:
    void NewIcon();
    void NewTitle();
    void NewStatus();
    void NewToolTip();
    void NewAttentionIcon();
    void NewOverlayIcon();
    void NewItemIsMenu();
};

class FakeStatusNotifierWatcher final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ registeredItems)
public:
    QStringList registeredItems() const { return {QStringLiteral("org.example.FakeTray/StatusNotifierItem")}; }
signals:
    void StatusNotifierItemRegistered(const QString &item);
    void StatusNotifierItemUnregistered(const QString &item);
};

class FakeNotifications final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
signals:
    void ActionInvoked(uint id, const QString &action);
};

class FakePortal final : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.portal.Settings")
public slots:
    QDBusVariant ReadOne(const QString &, const QString &key) const
    {
        return key == QLatin1String("color-scheme")
            ? QDBusVariant(QVariant::fromValue(uint(1))) : QDBusVariant(QVariant{});
    }
signals:
    void SettingChanged(const QString &nameSpace, const QString &key, const QDBusVariant &value);
};

static bool waitUntil(const std::function<bool()> &condition, int timeoutMs = 3000)
{
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < timeoutMs) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 20);
        if (condition())
            return true;
        QThread::msleep(5);
    }
    return condition();
}

static bool check(bool condition, const char *description)
{
    std::cout << (condition ? "PASS: " : "FAIL: ") << description << '\n';
    return condition;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    const QByteArray sessionAddress = qgetenv("DBUS_SESSION_BUS_ADDRESS");
    if (sessionAddress.isEmpty()) {
        std::cerr << "FAIL: private dbus-run-session address missing\n";
        return 1;
    }
    qputenv("DBUS_SYSTEM_BUS_ADDRESS", sessionAddress);
    QDBusConnection bus = QDBusConnection::sessionBus();

    FakeAccounts accounts(bus);
    FakePackageKit packageKit(bus);
    FakeTrayItem trayItem;
    FakeStatusNotifierWatcher trayWatcher;
    FakeNotifications notifications;
    FakePortal portal;
    bool servicesRegistered = bus.registerService(QStringLiteral("org.freedesktop.Accounts"))
        && bus.registerObject(QStringLiteral("/org/freedesktop/Accounts"), &accounts,
                              QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals)
        && bus.registerService(QStringLiteral("org.freedesktop.PackageKit"))
        && bus.registerObject(QStringLiteral("/org/freedesktop/PackageKit"), &packageKit,
                              QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals)
        && bus.registerService(QStringLiteral("org.kde.StatusNotifierWatcher"))
        && bus.registerObject(QStringLiteral("/StatusNotifierWatcher"), &trayWatcher,
                              QDBusConnection::ExportAllProperties | QDBusConnection::ExportAllSignals)
        && bus.registerService(QStringLiteral("org.example.FakeTray"))
        && bus.registerObject(QStringLiteral("/StatusNotifierItem"), &trayItem,
                              QDBusConnection::ExportAllProperties | QDBusConnection::ExportAllSignals)
        && bus.registerService(QStringLiteral("org.freedesktop.Notifications"))
        && bus.registerObject(QStringLiteral("/org/freedesktop/Notifications"), &notifications,
                              QDBusConnection::ExportAllSignals)
        && bus.registerService(QStringLiteral("org.freedesktop.portal.Desktop"))
        && bus.registerObject(QStringLiteral("/org/freedesktop/portal/desktop"), &portal,
                              QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals);
    if (!check(servicesRegistered, "fake AccountsService, PackageKit, SNI, notifications registered"))
        return 1;

    Lelan lelan(nullptr, false);
    auto userRecord = [&lelan](const QString &name) {
        for (const QVariant &entry : lelan.users())
            if (entry.toMap().value(QStringLiteral("name")).toString() == name)
                return entry.toMap();
        return QVariantMap{};
    };
    bool ok = true;
    ok &= check(waitUntil([&] { return lelan.users().size() == 1; }), "AccountsService user list loaded");
    ok &= check(userRecord(lelan.userName()).value(QStringLiteral("name")).toString() == lelan.userName(),
                "current account mapped to QML user record");

    lelan.setUserAdmin(lelan.userName(), false);
    ok &= check(waitUntil([&] { return !userRecord(lelan.userName()).value(QStringLiteral("isAdmin")).toBool(); }),
                "SetAccountType updates cached user");
    lelan.setAutoLogin(lelan.userName(), false);
    ok &= check(waitUntil([&] { return !userRecord(lelan.userName()).value(QStringLiteral("isAutoLogin")).toBool(); }),
                "SetAutomaticLogin accepts false");
    lelan.changePassword(lelan.userName(), QStringLiteral("fake-password"));
    lelan.setUserAvatar(lelan.userName(), QStringLiteral("avatars/02-star-cluster.svg"));
    lelan.setUserAvatar(lelan.userName(), QStringLiteral("../../etc/passwd"));
    ok &= check(waitUntil([&] {
        return userRecord(lelan.userName()).value(QStringLiteral("avatar")).toString()
            == QStringLiteral("avatars/02-star-cluster.svg");
    }), "bundled avatar selected and unsafe path rejected");
    lelan.removeUser(lelan.userName());
    ok &= check(accounts.user(lelan.userName()) && !accounts.user(lelan.userName())->deleted,
                "current account remains cached after removal refusal");

    lelan.addUser(QStringLiteral("testuser"), QStringLiteral("Test User"), false);
    lelan.changePassword(QStringLiteral("testuser"), QStringLiteral("deferred-password"));
    ok &= check(waitUntil([&] {
        return userRecord(QStringLiteral("testuser")).value(QStringLiteral("name")).toString() == QStringLiteral("testuser");
    }), "CreateUser publishes the new user");
    ok &= check(waitUntil([&] {
        return accounts.user(QStringLiteral("testuser")) && accounts.user(QStringLiteral("testuser"))->passwordSet;
    }), "password requested during creation runs after CreateUser returns");
    lelan.setUserAdmin(QStringLiteral("testuser"), true);
    lelan.setAutoLogin(QStringLiteral("testuser"), true);
    ok &= check(waitUntil([&] {
        const QVariantMap user = userRecord(QStringLiteral("testuser"));
        return user.value(QStringLiteral("isAdmin")).toBool() && user.value(QStringLiteral("isAutoLogin")).toBool();
    }), "new user admin and auto-login operations complete");

    ok &= check(waitUntil([&] {
        return lelan.updates().value(QStringLiteral("count")).toInt() == 1;
    }), "PackageKit GetUpdates package and Finished signals collected");
    ok &= check(packageKit.filtersEmpty, "PackageKit called with empty filters array");
    ok &= check(waitUntil([&] {
        return lelan.tray().size() == 1
            && lelan.tray().first().toMap().value(QStringLiteral("title")).toString()
                == QStringLiteral("Fake tray item");
    }), "StatusNotifierItem properties reach tray QML model");
    emit notifications.ActionInvoked(41, QStringLiteral("open"));
    ok &= check(waitUntil([&] { return !lelan.notifications().isEmpty(); }),
                "notification action event is published");

    const QString recordPath = QString::fromLocal8Bit(qgetenv("NCDE_PRINTER_RECORD"));
    lelan.setDefaultPrinter(QStringLiteral("Safe_Printer"));
    lelan.removePrinter(QStringLiteral("Another-Printer"));
    lelan.removePrinter(QStringLiteral("bad;queue"));
    ok &= check(waitUntil([&] {
        QFile record(recordPath);
        if (!record.open(QIODevice::ReadOnly))
            return false;
        const QByteArray text = record.readAll();
        return text.contains("-d Safe_Printer") && text.contains("-x Another-Printer")
            && !text.contains("bad;queue");
    }), "printer mutations use fake lpadmin with validated argv");
    ok &= check(waitUntil([&] {
        return lelan.printers().size() == 2
            && lelan.printers().first().toMap().value(QStringLiteral("isDefault")).toBool()
            && lelan.printers().first().toMap().value(QStringLiteral("location")).toString()
                == QStringLiteral("Lab");
    }), "asynchronous lpstat output maps status, default, and location");

    lelan.removeUser(QStringLiteral("testuser"));
    ok &= check(waitUntil([&] {
        return lelan.users().size() == 1;
    }), "Delete removes only the requested fake user");
    return ok ? 0 : 1;
}

#include "lelan_services_test.moc"
