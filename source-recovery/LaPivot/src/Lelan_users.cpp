// Lelan — local accounts through AccountsService and polkit's standard authorization path.
// Rebuilt from oracle: users/userName, refreshUsers, updateCurrentUserName, addUser, removeUser,
// setUserAdmin, changePassword, setAutoLogin, setUserAvatar.
// Spec: lelan.md §1/§4 (one shared system-event hub); settings-tabs.md Fix 1 (create then set password).
//
// DEFECTS FIXED vs oracle:
// 1. Account operations use asynchronous AccountsService D-Bus calls; no shell interpolation, blocking
//    wait, or direct edits to passwd/shadow files. AccountsService/polkit performs authorization.
// 2. New-user password updates are held until CreateUser returns, avoiding a race from the existing
//    addUser(name,display,isAdmin) API, which deliberately has no password argument.
// 3. Reject malformed usernames, protect root/current-user deletion, and restrict avatar requests to
//    bundled NCDE avatars; arbitrary paths never reach AccountsService.
#include "Lelan.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QDir>
#include <QRegularExpression>
#include <QSet>
#include <QtLogging>

#include <algorithm>
#include <memory>
#include <pwd.h>
#include <unistd.h>
#include <utility>

namespace {
const QString kAccounts = QStringLiteral("org.freedesktop.Accounts");
const QString kAccountsPath = QStringLiteral("/org/freedesktop/Accounts");
const QString kAccountsIface = QStringLiteral("org.freedesktop.Accounts");
const QString kUserIface = QStringLiteral("org.freedesktop.Accounts.User");
const QString kProps = QStringLiteral("org.freedesktop.DBus.Properties");
const QRegularExpression kUserNamePattern(QStringLiteral("^[a-z_][a-z0-9_-]{0,30}\\$?$"));
const QRegularExpression kAvatarPattern(QStringLiteral("^avatars/[0-9]{2}-[a-z-]+\\.svg$"));

void logDbusFailure(const QString &operation, const QDBusError &error)
{
    qWarning().noquote() << "[lelan] AccountsService" << operation << "failed:"
                         << error.name() << error.message();
}
} // namespace

QVariantList Lelan::users() const { return m_users; }

QString Lelan::userName() const
{
    return m_currentUserName;
}

void Lelan::updateCurrentUserName()
{
    const passwd *entry = getpwuid(getuid());
    const QString current = entry ? QString::fromLocal8Bit(entry->pw_name) : QString{};
    if (current == m_currentUserName)
        return;
    m_currentUserName = current;
    emit userNameChanged();
}

void Lelan::subscribeToAccountsService()
{
    updateCurrentUserName();
    auto bus = QDBusConnection::systemBus();
    bus.connect(kAccounts, kAccountsPath, kAccountsIface, QStringLiteral("UserAdded"),
                this, SLOT(onAccountsUserAdded(QDBusObjectPath)));
    bus.connect(kAccounts, kAccountsPath, kAccountsIface, QStringLiteral("UserDeleted"),
                this, SLOT(onAccountsUserDeleted(QDBusObjectPath)));
    bus.connect(kAccounts, QString(), kProps, QStringLiteral("PropertiesChanged"),
                this, SLOT(onAccountsPropertiesChanged(QString,QVariantMap,QStringList)));
    refreshUsers();
}

void Lelan::refreshUsers()
{
    const quint64 generation = ++m_usersGeneration;
    QDBusMessage msg = QDBusMessage::createMethodCall(
        kAccounts, kAccountsPath, kAccountsIface, QStringLiteral("ListCachedUsers"));
    const auto bus = QDBusConnection::systemBus();
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(msg), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, generation, bus](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QList<QDBusObjectPath>> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            logDbusFailure(QStringLiteral("ListCachedUsers"), reply.error());
            return;
        }
        const auto paths = reply.value();
        auto usersByPath = std::make_shared<QHash<QString, QVariantMap>>();
        auto pathsByName = std::make_shared<QHash<QString, QDBusObjectPath>>();
        if (paths.isEmpty()) {
            if (generation != m_usersGeneration)
                return;
            m_userPaths.clear();
            if (!m_users.isEmpty()) {
                m_users.clear();
                emit usersChanged();
            }
            return;
        }

        auto remaining = std::make_shared<int>(paths.size());
        for (const QDBusObjectPath &path : paths) {
            QDBusMessage getAll = QDBusMessage::createMethodCall(
                kAccounts, path.path(), kProps, QStringLiteral("GetAll"));
            getAll << kUserIface;
            auto *userWatcher = new QDBusPendingCallWatcher(bus.asyncCall(getAll), this);
            connect(userWatcher, &QDBusPendingCallWatcher::finished, this,
                    [this, generation, path, usersByPath, pathsByName, remaining]
                    (QDBusPendingCallWatcher *uw) {
                QDBusPendingReply<QVariantMap> userReply = *uw;
                uw->deleteLater();
                if (!userReply.isError()) {
                    const QVariantMap props = userReply.value();
                    const QString name = props.value(QStringLiteral("UserName")).toString();
                    if (!name.isEmpty()) {
                        const QString icon = props.value(QStringLiteral("IconFile")).toString();
                        QString avatar = icon;
                        if (icon.contains(QStringLiteral("/avatars/")))
                            avatar = icon.mid(icon.lastIndexOf(QStringLiteral("/avatars/")) + 1);
                        else if (!icon.isEmpty() && !icon.startsWith(QLatin1String("file:")))
                            avatar.prepend(QStringLiteral("file://"));
                        const int passwordMode = props.value(QStringLiteral("PasswordMode")).toInt();
                        usersByPath->insert(path.path(), {
                            {QStringLiteral("name"), name},
                            {QStringLiteral("displayName"), props.value(QStringLiteral("RealName")).toString()},
                            {QStringLiteral("isAdmin"), props.value(QStringLiteral("AccountType")).toInt() == 1},
                            {QStringLiteral("hasPassword"), passwordMode != 1 && passwordMode != 2},
                            {QStringLiteral("isAutoLogin"), props.value(QStringLiteral("AutomaticLogin")).toBool()},
                            {QStringLiteral("avatar"), avatar.isEmpty()
                                 ? QStringLiteral("avatars/01-full-moon.svg") : avatar}
                        });
                        pathsByName->insert(name, path);
                    }
                } else {
                    logDbusFailure(QStringLiteral("GetAll(User)"), userReply.error());
                }
                if (--*remaining != 0 || generation != m_usersGeneration)
                    return;

                QVariantList next;
                QStringList names = pathsByName->keys();
                std::sort(names.begin(), names.end(), [](const QString &a, const QString &b) {
                    return a.compare(b, Qt::CaseInsensitive) < 0;
                });
                for (const QString &name : std::as_const(names))
                    next.append(usersByPath->value(pathsByName->value(name).path()));
                m_userPaths = *pathsByName;
                if (next != m_users) {
                    m_users = next;
                    emit usersChanged();
                }
            });
        }
    });
}

void Lelan::withUserPath(const QString &name, std::function<void(const QDBusObjectPath &)> ready)
{
    const auto cached = m_userPaths.constFind(name);
    if (cached != m_userPaths.cend()) {
        ready(cached.value());
        return;
    }
    QDBusMessage find = QDBusMessage::createMethodCall(
        kAccounts, kAccountsPath, kAccountsIface, QStringLiteral("FindUserByName"));
    find << name;
    const auto bus = QDBusConnection::systemBus();
    auto *watcher = new QDBusPendingCallWatcher(bus.asyncCall(find), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, name, ready = std::move(ready)](QDBusPendingCallWatcher *w) mutable {
        QDBusPendingReply<QDBusObjectPath> reply = *w;
        w->deleteLater();
        if (reply.isError()) {
            logDbusFailure(QStringLiteral("FindUserByName"), reply.error());
            return;
        }
        m_userPaths.insert(name, reply.value());
        ready(reply.value());
    });
}

void Lelan::callUser(const QString &name, const QString &method, const QVariantList &args,
                     std::function<void()> done)
{
    withUserPath(name, [this, method, args, done = std::move(done)](const QDBusObjectPath &path) mutable {
        QDBusMessage call = QDBusMessage::createMethodCall(kAccounts, path.path(), kUserIface, method);
        call.setArguments(args);
        auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(call), this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this,
                [this, method, done = std::move(done)](QDBusPendingCallWatcher *w) mutable {
            QDBusPendingReply<> reply = *w;
            w->deleteLater();
            if (reply.isError()) {
                logDbusFailure(method, reply.error());
                return;
            }
            if (done)
                done();
            refreshUsers();
        });
    });
}

void Lelan::addUser(const QString &name, const QString &displayName, bool isAdmin)
{
    if (!kUserNamePattern.match(name).hasMatch() || displayName.contains(QChar::Null)) {
        qWarning() << "[lelan] refused invalid account name";
        return;
    }
    if (m_usersBeingCreated.contains(name)) {
        qWarning() << "[lelan] account creation is already pending";
        return;
    }
    QDBusMessage create = QDBusMessage::createMethodCall(
        kAccounts, kAccountsPath, kAccountsIface, QStringLiteral("CreateUser"));
    create << name << displayName << uint(isAdmin ? 1 : 0);
    m_usersBeingCreated.insert(name);
    auto *watcher = new QDBusPendingCallWatcher(QDBusConnection::systemBus().asyncCall(create), this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this,
            [this, name](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QDBusObjectPath> reply = *w;
        w->deleteLater();
        m_usersBeingCreated.remove(name);
        if (reply.isError()) {
            m_pendingUserPasswords.remove(name);
            logDbusFailure(QStringLiteral("CreateUser"), reply.error());
            return;
        }
        m_userPaths.insert(name, reply.value());
        const QString password = m_pendingUserPasswords.take(name);
        if (!password.isNull())
            callUser(name, QStringLiteral("SetPassword"), {password, QString{}});
        refreshUsers();
    });
}

void Lelan::removeUser(const QString &name)
{
    if (name == QLatin1String("root") || name == userName()) {
        qWarning() << "[lelan] refused removal of root or the current account";
        return;
    }
    callUser(name, QStringLiteral("Delete"), {false});
}

void Lelan::setUserAdmin(const QString &name, bool admin)
{
    callUser(name, QStringLiteral("SetAccountType"), {uint(admin ? 1 : 0)});
}

void Lelan::changePassword(const QString &name, const QString &pwd)
{
    if (pwd.isEmpty()) {
        qWarning() << "[lelan] refused empty account password";
        return;
    }
    if (m_usersBeingCreated.contains(name)) {
        m_pendingUserPasswords.insert(name, pwd);
        return;
    }
    callUser(name, QStringLiteral("SetPassword"), {pwd, QString{}});
}

void Lelan::setAutoLogin(const QString &name, bool on)
{
    callUser(name, QStringLiteral("SetAutomaticLogin"), {on});
}

void Lelan::setUserAvatar(const QString &name, const QString &file)
{
    if (!kAvatarPattern.match(file).hasMatch()) {
        qWarning() << "[lelan] refused non-bundled account avatar";
        return;
    }
    const QString base = qEnvironmentVariable("NCDE_ASSET_BASE", QStringLiteral("/usr/share/ncde"));
    const QString iconPath = QDir(base).filePath(file);
    callUser(name, QStringLiteral("SetIconFile"), {iconPath});
}

void Lelan::onAccountsPropertiesChanged(const QString &iface, const QVariantMap &changed, const QStringList &)
{
    if (iface == kUserIface && !changed.isEmpty())
        refreshUsers();
}

void Lelan::onAccountsUserAdded(const QDBusObjectPath &)
{
    refreshUsers();
}

void Lelan::onAccountsUserDeleted(const QDBusObjectPath &path)
{
    for (auto it = m_userPaths.begin(); it != m_userPaths.end();) {
        if (it.value() == path)
            it = m_userPaths.erase(it);
        else
            ++it;
    }
    refreshUsers();
}
