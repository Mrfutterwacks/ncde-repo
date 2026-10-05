// idle_power_test — Settings_power.cpp + IdlePolicy driven through simulated idle time. Nothing real happens:
// every command Settings would run (systemctl suspend, loginctl lock-session, xset) is recorded instead,
// and the screensaver is a stand-in script ($SAVER, sleeps; exits with $SAVER_EXIT after $SAVER_AFTER s).
// Each case feeds X idle samples every 2 s (as NCDEWindowManager::pollUserIdle does) and checks what fired
// and when, against what the Power / Screensaver / Security tabs promise.
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QProcess>
#include <QTimer>
#include <cstdio>

#define private public
#include "Lelan.h"
#include "Settings.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;
Settings::Settings(QObject *parent) : QObject(parent) {}
Settings::~Settings() = default;
void Settings::applyNightLight() {}
void Settings::followDayNight() {}          // display area not linked here (setLelan calls it)

static int g_fails = 0;
static void check(bool ok, const QString &what)
{
    if (!ok) ++g_fails;
    std::printf("%s %s\n", ok ? "PASS" : "FAIL", qPrintable(what));
}
static void wait(int ms) { QEventLoop l; QTimer::singleShot(ms, &l, &QEventLoop::quit); l.exec(); }

struct Run {
    QStringList log;                         // "t=<s> <program> <args>"
    qint64 now = 0;                          // simulated idle ms of the current sample
};

// feeds idle samples 0..untilMs every 2 s; `inputAtMs` (if >= 0) = the user touches something then
static void feed(Settings &s, Run &r, qint64 untilMs, qint64 inputAtMs = -1, qint64 start = 0)
{
    qint64 idle = start;
    for (qint64 t = start; t <= untilMs; t += 2000) {
        if (inputAtMs >= 0 && t >= inputAtMs && t - 2000 < inputAtMs)
            idle = 0;
        r.now = t;
        s.onIdleSample(idle);
        idle += 2000;
    }
}
static int count(const Run &r, const QString &needle)
{
    int n = 0;
    for (const QString &l : r.log) n += l.contains(needle);
    return n;
}
static qint64 firstAt(const Run &r, const QString &needle)
{
    for (const QString &l : r.log)
        if (l.contains(needle)) return l.section(' ', 0, 0).mid(2).toLongLong();
    return -1;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Lelan lelan(nullptr, false);
    auto make = [&](Run &r, bool battery, int saver, int bat, int ac, bool pwd, int delay) {
        auto *s = new Settings;
        s->runDetached = [&r](const QString &p, const QStringList &a) {
            r.log << QStringLiteral("t=%1 %2 %3").arg(r.now).arg(p, a.join(' '));
        };
        s->saverProgram = qEnvironmentVariable("SAVER");
        lelan.m_onBattery = battery;
        s->m_screensaverTimeout = saver; s->m_batSuspend = bat; s->m_acSuspend = ac;
        s->m_requirePassword = pwd; s->m_requirePasswordDelay = delay;
        s->setLelan(&lelan);
        return s;
    };
    const qint64 MIN = 60000;

    { Run r; Settings *s = make(r, true, 5, 15, 0, true, 0);
      feed(*s, r, 16 * MIN);
      check(count(r, "systemctl suspend") == 1 && firstAt(r, "systemctl suspend") == 15 * MIN,
            "battery, suspend 15 min: suspends once, at 15:00 (oracle: ~0:30) — got " + r.log.filter("suspend").join(";"));
      check(count(r, "lock-session") == 1 && firstAt(r, "lock-session") == 5 * MIN,
            "require password, delay 0: locked when the screensaver would begin (5:00)");
      delete s; }

    { Run r; Settings *s = make(r, true, 5, 15, 0, false, 0);
      feed(*s, r, 14 * MIN);
      wait(300);
      check(s->screensaverRunning(), "require password OFF: the screensaver runs from 5:00");
      feed(*s, r, 16 * MIN, -1, 14 * MIN + 2000);
      wait(300);
      check(count(r, "lock-session") == 0, "require password OFF: never locks on idle");
      check(count(r, "systemctl suspend") == 1, "require password OFF: still suspends at 15:00");
      check(s->screensaverRunning() == false, "saver stopped before suspend");
      delete s; }

    { Run r; Settings *s = make(r, false, 5, 15, 0, true, 60);
      feed(*s, r, 5 * MIN);
      wait(300);
      check(s->screensaverRunning(), "screensaver started at 5:00 (delay 60 s: no lock yet)");
      feed(*s, r, 7 * MIN, -1, 5 * MIN + 2000);
      check(count(r, "lock-session") == 1 && firstAt(r, "lock-session") == 6 * MIN, "locked at 6:00 = 5 min + 60 s delay");
      wait(300);
      check(!s->screensaverRunning(), "saver stopped when the lock took over");
      check(count(r, "systemctl suspend") == 0, "on AC with suspend Never: no suspend");
      delete s; }

    { Run r; Settings *s = make(r, false, 5, 15, 0, false, 0);
      feed(*s, r, 6 * MIN);
      wait(300);
      check(s->screensaverRunning(), "saver running at 6:00");
      // (the samples are fed with pauses where a stopped saver needs a moment to exit, as 2 s polls give it)
      feed(*s, r, 7 * MIN, 7 * MIN, 6 * MIN + 2000);
      wait(300);
      check(!s->screensaverRunning(), "input at 7:00 stopped the screensaver");
      for (qint64 idle = 2000; idle < 5 * MIN; idle += 2000) s->onIdleSample(idle);   // 7:02 .. 11:58
      check(!s->screensaverRunning(), "not back before 12:00");
      s->onIdleSample(5 * MIN);
      wait(300);
      check(s->screensaverRunning(), "started again 5 min after the input (12:00)");
      s->stopSaver(); wait(300);
      delete s; }

    { Run r; Settings *s = make(r, true, 0, 15, 0, true, 0);
      feed(*s, r, 40 * MIN);
      check(count(r, "systemctl suspend") == 1, "idle continues after resume (40 min): suspended once, not again");
      feed(*s, r, 60 * MIN, 41 * MIN, 40 * MIN + 2000);
      check(count(r, "systemctl suspend") == 2 && firstAt(r, "t=" + QString::number(56 * MIN) + " systemctl") >= 0,
            "input at 41:00 re-arms: next suspend at 56:00");
      check(count(r, "lock-session") == 0, "screensaver off: no idle lock (the sleep lock is xss-lock's)");
      delete s; }

    // P1: xset only when the blank time changes
    { Run r; Settings *s = make(r, false, 5, 15, 0, true, 0);
      const int before = count(r, "xset");
      for (int i = 0; i < 10; ++i) emit lelan.batteryChanged();
      check(count(r, "xset") == before, "10 x batteryChanged on AC: no xset (oracle: 30)");
      lelan.m_onBattery = true; emit lelan.batteryChanged();
      check(count(r, "xset dpms 600 600 600") == 1 && count(r, "xset s off") == 2, "to battery: dpms 10 min once, X saver kept off");
      delete s; }

    // P3: the lid
    { Run r; Settings *s = make(r, false, 5, 15, 0, true, 0);
      s->m_lidAction = "suspend"; emit lelan.lidClosedChanged(true); emit lelan.lidClosedChanged(false);
      s->m_lidAction = "lock"; emit lelan.lidClosedChanged(true);
      s->m_lidAction = "nothing"; emit lelan.lidClosedChanged(true);
      check(count(r, "systemctl suspend") == 1 && count(r, "lock-session") == 1, "lid: suspend / lock / nothing each did exactly that; opening did nothing");
      delete s; }

    // I4: screensaver exits
    auto saverCase = [&](const char *exitCode, bool inputAfter, int wantRelaunches, const QString &what) {
        qputenv("SAVER_EXIT", exitCode); qputenv("SAVER_AFTER", "0.3");
        Run r; Settings *s = make(r, false, 5, 0, 0, false, 0);
        qint64 idle = 5 * MIN;
        s->idleMsSource = [&] { return idle; };
        feed(*s, r, 5 * MIN);
        int exits = 0;
        QObject::connect(s, &Settings::screensaverFinished, [&](int code, bool crash) {
            ++exits;
            idle += inputAfter ? -idle : 400;
            std::printf("  (saver exited %d%s, idle now %lld)\n", code, crash ? " crash" : "", idle); });
        wait(3000);
        check(exits - 1 == wantRelaunches && !s->screensaverRunning(),
              what + " (relaunches " + QString::number(exits - 1) + ")");
        s->stopSaver(); wait(300); delete s;
    };
    saverCase("0", false, 0, "saver exits 0 (dismissed): not relaunched");
    saverCase("1", false, 3, "saver fails while nobody is back: relaunched, at most 3 times");
    saverCase("1", true, 0, "saver fails after the user came back: not relaunched (oracle: relaunched)");

    std::printf("RESULT %s\n", g_fails ? "FAIL" : "PASS");
    return g_fails ? 1 : 0;
}
