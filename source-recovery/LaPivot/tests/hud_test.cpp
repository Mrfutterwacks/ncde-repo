/* HudManager test — validates requestHud/dismissHud signal emission
   Run with: tests/hud_test.sh */

#include "HudManager.h"

#include <QCoreApplication>
#include <QTest>
#include <QSignalSpy>

class TestHudManager : public QObject {
    Q_OBJECT

private slots:
    void testRequestHudEmitsSignal() {
        HudManager mgr;
        QSignalSpy spy(&mgr, &HudManager::hudRequested);

        mgr.requestHud();

        QCOMPARE(spy.count(), 1);
    }

    void testDismissHudEmitsSignal() {
        HudManager mgr;
        QSignalSpy spy(&mgr, &HudManager::hudDismissed);

        mgr.dismissHud();

        QCOMPARE(spy.count(), 1);
    }

    void testMultipleRequests() {
        HudManager mgr;
        QSignalSpy reqSpy(&mgr, &HudManager::hudRequested);
        QSignalSpy disSpy(&mgr, &HudManager::hudDismissed);

        mgr.requestHud();
        mgr.requestHud();
        mgr.dismissHud();
        mgr.dismissHud();

        QCOMPARE(reqSpy.count(), 2);
        QCOMPARE(disSpy.count(), 2);
    }
};

QTEST_MAIN(TestHudManager)
#include "hud_test.moc"