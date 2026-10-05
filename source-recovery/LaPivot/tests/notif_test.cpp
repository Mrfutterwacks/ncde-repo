#include "NotificationManager.h"
#include "FreedesktopNotificationsAdaptor.h"
#include "Settings.h"
#include "Lelan.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#include <QProcess>
#include <QSignalSpy>
#include <QTest>

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_quietHoursOn = false;
}
Settings::~Settings() = default;
bool Settings::dnd() const { return m_dnd; }
void Settings::setDnd(bool value)
{
    if (m_dnd == value)
        return;
    m_dnd = value;
    emit notifsChanged();
}
bool Settings::quietHoursOn() const { return m_quietHoursOn; }
void Settings::setQuietHoursOn(bool value)
{
    if (m_quietHoursOn == value)
        return;
    m_quietHoursOn = value;
    emit notifsChanged();
}
QString Settings::quietFrom() const { return m_quietFrom; }
void Settings::setQuietFrom(const QString &value)
{
    if (m_quietFrom == value)
        return;
    m_quietFrom = value;
    emit notifsChanged();
}
QString Settings::quietTo() const { return m_quietTo; }
void Settings::setQuietTo(const QString &value)
{
    if (m_quietTo == value)
        return;
    m_quietTo = value;
    emit notifsChanged();
}

QVariantMap Lelan::readConfig(const QString &) { return {}; }
bool Lelan::writeConfig(const QString &, const QVariantMap &) { return true; }

class TestNotificationManager : public QObject
{
    Q_OBJECT

private:
    QProcess m_dbusDaemon;

    void asyncReply(const QDBusMessage &message, QDBusMessage *reply)
    {
        QDBusPendingCallWatcher watcher(QDBusConnection::sessionBus().asyncCall(message));
        QTRY_VERIFY_WITH_TIMEOUT(watcher.isFinished(), 3000);
        *reply = watcher.reply();
    }

    QDBusMessage methodCall(const QString &method, const QVariantList &arguments = {})
    {
        QDBusMessage message = QDBusMessage::createMethodCall(
            QStringLiteral("org.freedesktop.Notifications"),
            QStringLiteral("/org/freedesktop/Notifications"),
            QStringLiteral("org.freedesktop.Notifications"), method);
        message.setArguments(arguments);
        QDBusMessage reply;
        asyncReply(message, &reply);
        return reply;
    }

private slots:
    void initTestCase()
    {
        const QString address = QStringLiteral("unix:abstract=ncde-notif-test-%1")
            .arg(QCoreApplication::applicationPid());
        m_dbusDaemon.start(QStringLiteral("dbus-daemon"),
                           {QStringLiteral("--session"), QStringLiteral("--nofork"),
                            QStringLiteral("--print-address=1"),
                            QStringLiteral("--address=%1").arg(address)});
        QVERIFY(m_dbusDaemon.waitForStarted(3000));
        QVERIFY(m_dbusDaemon.waitForReadyRead(3000));
        const QByteArray printedAddress = m_dbusDaemon.readLine().trimmed();
        QVERIFY(printedAddress.startsWith("unix:abstract="));
        qputenv("DBUS_SESSION_BUS_ADDRESS", printedAddress);
        QVERIFY(QDBusConnection::sessionBus().isConnected());
    }

    void cleanupTestCase()
    {
        m_dbusDaemon.terminate();
        if (!m_dbusDaemon.waitForFinished(2000)) {
            m_dbusDaemon.kill();
            m_dbusDaemon.waitForFinished(2000);
        }
        QCOMPARE(m_dbusDaemon.state(), QProcess::NotRunning);
    }

    void doNotDisturbBlocksNotification()
    {
        Settings settings;
        settings.setDnd(true);
        NotificationManager manager;
        manager.setSettings(&settings);

        QCOMPARE(manager.notify(QStringLiteral("App"), QStringLiteral("Quiet"), {}, 5000), 0);
        QVERIFY(manager.notifications().isEmpty());
    }

    void quietHoursWrapAcrossMidnight()
    {
        Settings settings;
        settings.setQuietHoursOn(true);
        settings.setQuietFrom(QStringLiteral("10:00 PM"));
        settings.setQuietTo(QStringLiteral("7:00 AM"));
        NotificationManager manager;
        manager.setSettings(&settings);

        QVERIFY(manager.inQuietHoursAt(QTime(22, 0)));
        QVERIFY(manager.inQuietHoursAt(QTime(23, 0)));
        QVERIFY(manager.inQuietHoursAt(QTime(3, 0)));
        QVERIFY(!manager.inQuietHoursAt(QTime(7, 0)));
        QVERIFY(!manager.inQuietHoursAt(QTime(8, 0)));
        QVERIFY(!manager.inQuietHoursAt(QTime(17, 0)));
    }

    void quietHoursCanBeChangedAfterWiring()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);

        QVERIFY(manager.notify(QStringLiteral("App"), QStringLiteral("Allowed"), {}, 5000) > 0);
        settings.setQuietHoursOn(true);
        settings.setQuietFrom(QStringLiteral("12:00 AM"));
        settings.setQuietTo(QStringLiteral("11:59 PM"));
        QCOMPARE(manager.notify(QStringLiteral("App"), QStringLiteral("Blocked"), {}, 5000), 0);
    }

    void invalidQuietHoursFailOpen()
    {
        Settings settings;
        settings.setQuietHoursOn(true);
        settings.setQuietFrom(QStringLiteral("not a time"));
        settings.setQuietTo(QStringLiteral("7:00 AM"));
        NotificationManager manager;
        manager.setSettings(&settings);

        QVERIFY(!manager.inQuietHoursAt(QTime(3, 0)));
        QVERIFY(manager.notify(QStringLiteral("App"), QStringLiteral("Allowed"), {}, 5000) > 0);
    }

    void historyUnreadAndDismissStayConsistent()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);
        const int first = manager.notify(QStringLiteral("App A"), QStringLiteral("One"), {}, 5000);
        const int second = manager.notify(QStringLiteral("App B"), QStringLiteral("Two"), {}, 5000);
        QVERIFY(first > 0);
        QVERIFY(second > first);
        QCOMPARE(manager.unreadCount(), 2);

        manager.markRead();
        QCOMPARE(manager.unreadCount(), 0);
        QSignalSpy changedSpy(&manager, &NotificationManager::changed);
        manager.markRead();
        QCOMPARE(changedSpy.count(), 0);

        manager.dismiss(first);
        QCOMPARE(manager.notifications().size(), 1);
        manager.dismissAll();
        QVERIFY(manager.notifications().isEmpty());
    }

    void perAppPreferenceUsesApplicationName()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);

        const int firstId = manager.notifyFromDBus(
            QStringLiteral("org.example.App"), 0, {}, QStringLiteral("First title"),
            QStringLiteral("body"), 5000);
        QVERIFY(firstId > 0);
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("title")).toString(),
                 QStringLiteral("First title"));
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("appName")).toString(),
                 QStringLiteral("org.example.App"));
        QVERIFY(manager.notifyApps().first().toMap().contains(QStringLiteral("name")));

        manager.setAppNotify(QStringLiteral("org.example.App"), false);
        QCOMPARE(manager.notifyFromDBus(QStringLiteral("org.example.App"), 0, {},
                                        QStringLiteral("Second title"), {}, 5000), 0);
    }

    void fdoNotifyPreservesSummaryAndReplacesExistingId()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);
        QVERIFY(manager.registerDBusService());

        const QDBusMessage first = methodCall(
            QStringLiteral("Notify"),
            {QStringLiteral("org.example.App"), uint(0), QString(), QStringLiteral("Summary"),
             QStringLiteral("Body"), QStringList(), QVariantMap(), 5000});
        QVERIFY(first.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(first.arguments().size(), 1);
        const uint id = first.arguments().first().toUInt();
        QVERIFY(id > 0);
        QCOMPARE(manager.notifications().size(), 1);
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("appName")).toString(),
                 QStringLiteral("org.example.App"));
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("title")).toString(),
                 QStringLiteral("Summary"));

        const QDBusMessage replacement = methodCall(
            QStringLiteral("Notify"),
            {QStringLiteral("org.example.App"), id, QString(), QStringLiteral("Updated summary"),
             QStringLiteral("Updated body"), QStringList(), QVariantMap(), 5000});
        QVERIFY(replacement.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(replacement.arguments().first().toUInt(), id);
        QCOMPARE(manager.notifications().size(), 1);
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("title")).toString(),
                 QStringLiteral("Updated summary"));
    }

    void freedesktopTimeoutValuesMapToWidgetTimeoutConvention()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);
        QVERIFY(manager.registerDBusService());

        const QDBusMessage defaultTimeout = methodCall(
            QStringLiteral("Notify"),
            {QStringLiteral("org.example.App"), uint(0), QString(), QStringLiteral("Default"),
             QStringLiteral("Body"), QStringList(), QVariantMap(), 0});
        QVERIFY(defaultTimeout.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("timeout")).toInt(), 5000);

        const QDBusMessage neverTimeout = methodCall(
            QStringLiteral("Notify"),
            {QStringLiteral("org.example.App"), uint(0), QString(), QStringLiteral("Never"),
             QStringLiteral("Body"), QStringList(), QVariantMap(), -1});
        QVERIFY(neverTimeout.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(manager.notifications().first().toMap().value(QStringLiteral("timeout")).toInt(), 0);
    }

    void freedesktopNameAndMethodSignaturesAreRegistered()
    {
        NotificationManager manager;
        QVERIFY(manager.registerDBusService());
        const QDBusConnection bus = QDBusConnection::sessionBus();
        QVERIFY(bus.interface()->isServiceRegistered(QStringLiteral("org.freedesktop.Notifications")));

        const QDBusMessage capabilities = methodCall(QStringLiteral("GetCapabilities"));
        QVERIFY(capabilities.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(capabilities.arguments().size(), 1);
        QVERIFY(capabilities.arguments().first().toStringList().contains(QStringLiteral("body")));

        const QDBusMessage information = methodCall(QStringLiteral("GetServerInformation"));
        QVERIFY(information.type() != QDBusMessage::ErrorMessage);
        QCOMPARE(information.arguments().size(), 4);
        QCOMPARE(information.arguments().at(0).toString(), QStringLiteral("NCDE Notification Server"));
        QCOMPARE(information.arguments().at(3).toString(), QStringLiteral("1.2"));
    }

    void closeNotificationEmitsFreedesktopReason()
    {
        Settings settings;
        NotificationManager manager;
        manager.setSettings(&settings);
        QVERIFY(manager.registerDBusService());
        QSignalSpy closedSpy(manager.m_adaptor, &FreedesktopNotificationsAdaptor::NotificationClosed);

        const QDBusMessage created = methodCall(
            QStringLiteral("Notify"),
            {QStringLiteral("org.example.App"), uint(0), QString(), QStringLiteral("Title"),
             QStringLiteral("Body"), QStringList(), QVariantMap(), 5000});
        QVERIFY(created.type() != QDBusMessage::ErrorMessage);
        const uint id = created.arguments().first().toUInt();

        const QDBusMessage closed = methodCall(QStringLiteral("CloseNotification"), {id});
        QVERIFY(closed.type() != QDBusMessage::ErrorMessage);
        QTRY_COMPARE(closedSpy.count(), 1);
        QCOMPARE(closedSpy.at(0).at(0).toUInt(), id);
        QCOMPARE(closedSpy.at(0).at(1).toUInt(), uint(3));
        QVERIFY(manager.notifications().isEmpty());
    }

    void serviceIsReleasedWhenManagerIsDestroyed()
    {
        {
            NotificationManager manager;
            QVERIFY(manager.registerDBusService());
            QVERIFY(QDBusConnection::sessionBus().interface()->isServiceRegistered(
                QStringLiteral("org.freedesktop.Notifications")));
        }
        QVERIFY(!QDBusConnection::sessionBus().interface()->isServiceRegistered(
            QStringLiteral("org.freedesktop.Notifications")));
    }
};

QTEST_MAIN(TestNotificationManager)
#include "notif_test.moc"
