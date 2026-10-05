// media_live_test — Lelan_media.cpp against two fake MPRIS players (tests/fake_mpris.py: a music player
// "ncdetest" and a browser "chromium.instance4242") on the real session bus. Drives a scripted sequence and
// checks M1-M8 plus the oracle's now-playing rule. No audio is involved.
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDBusArgument>
#include <QDBusMetaType>
#include <QDBusVariant>
#include <QTimer>
#include <cmath>
#include <cstdio>
#include <functional>

#define private public
#include "Lelan.h"
#undef private

Lelan::Lelan(QObject *parent, bool useSentinel) : QObject(parent), m_useSentinel(useSentinel) {}
Lelan::~Lelan() = default;

static const QString A = "org.mpris.MediaPlayer2.ncdetest";
static const QString B = "org.mpris.MediaPlayer2.chromium.instance4242";
static int fails = 0;
static void check(const char *what, bool ok, const QString &detail = {})
{
    std::printf("%s %s%s\n", ok ? "PASS" : "FAIL", what, detail.isEmpty() ? "" : qPrintable("  (" + detail + ")"));
    std::fflush(stdout);
    fails += !ok;
}
static QVariant ctl(const QString &player, const QString &method, const QVariantList &args = {})
{
    QDBusMessage m = QDBusMessage::createMethodCall(player, "/org/mpris/MediaPlayer2", "org.ncde.FakePlayer", method);
    m.setArguments(args);
    const QDBusMessage r = QDBusConnection::sessionBus().call(m);
    return r.arguments().value(0);
}
// SAFETY (2026-09-30: an earlier run seeked the operator's Spotify): the real session bus has the operator's
// players on it. Every real player is dropped from the Lelan under test as soon as it appears, and no
// command is ever sent unless the now-playing player is one of the fakes.
static void dropRealPlayers(Lelan &l)
{
    for (const QString &name : l.m_players.keys())
        if (name != A && name != B) {
            l.m_playerByOwner.remove(l.m_players.value(name).owner);
            l.m_players.remove(name);
            if (l.m_activePlayer == name) l.m_activePlayer.clear();
        }
}
static bool safeToCommand(const Lelan &l) { return l.m_activePlayer == A || l.m_activePlayer == B; }
// Stats() is a{sv}: it arrives as a QDBusArgument, not a QVariantMap (toMap() on it is empty, which made
// "0 == 0" checks pass vacuously in an earlier run) — decode it.
static QVariantMap stats(const QString &player) { return qdbus_cast<QVariantMap>(ctl(player, "Stats")); }
// counts of calls made by THIS process only (other programs on the session bus watch players too —
// the operator's running LaPivot among them)
static int stat(const QString &player, const char *key)
{
    const QVariantMap m = stats(player);
    if (!m.contains(key)) { std::printf("FAIL cannot read fake stats (%s)\n", key); ++fails; }
    return m.value(QString(key) + ":" + QDBusConnection::sessionBus().baseService()).toInt();
}
static QString others(const QString &player, const char *key)
{
    QStringList out;
    const QVariantMap m = stats(player);
    for (auto it = m.cbegin(); it != m.cend(); ++it)
        if (it.key().startsWith(QString(key) + ":") && !it.key().endsWith(QDBusConnection::sessionBus().baseService()))
            out << it.key().mid(int(qstrlen(key)) + 1) + "=" + it.value().toString();
    return out.join(' ');
}
static QString statS(const QString &player, const char *key) { return stats(player).value(key).toString(); }

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    Lelan l(nullptr, false);
    int mediaChanged = 0, posChanged = 0;
    bool titleBlanked = false;
    QObject::connect(&l, &Lelan::mediaChanged, [&] {
        ++mediaChanged;
        if (l.m_activePlayer == A && l.mediaTitle().isEmpty() && l.m_players.value(A).trackId == "/t/3") titleBlanked = true;
    });
    QObject::connect(&l, &Lelan::mediaPositionChanged, [&] { ++posChanged; });
    l.subscribeToPlayers();
    QTimer guard;                                   // keep real players out for the whole run
    QObject::connect(&guard, &QTimer::timeout, [&] { dropRealPlayers(l); });
    guard.start(20);

    QList<std::pair<int, std::function<void()>>> steps;
    int mcBefore = 0, getAllA = 0, getAllB = 0, getPosA = 0;
    steps << std::make_pair(1500, [&] {
        check("both fake players found", l.m_players.contains(A) && l.m_players.contains(B));
        ctl(A, "SetTrack", {"/t/1", "Song One", qlonglong(200000000)});
        ctl(A, "SetStatus", {"Playing", qlonglong(10000000)});
    });
    steps << std::make_pair(600, [&] {
        check("music player is now playing", l.m_activePlayer == A && l.mediaPlaying() && l.mediaTitle() == "Song One",
              l.m_activePlayer + " / " + l.mediaTitle());
        mcBefore = mediaChanged; getAllA = stat(A, "GetAll"); getAllB = stat(B, "GetAll");
        for (double v : {0.9, 0.8, 0.7, 0.6, 0.5}) ctl(A, "SetProp", {"Volume", QVariant::fromValue(QDBusVariant(v))});
    });
    steps << std::make_pair(600, [&] {
        check("volume changes: no mediaChanged (M2)", mediaChanged == mcBefore, QString("%1 extra").arg(mediaChanged - mcBefore));
        check("volume changes: no GetAll on any player (M1)", stat(A, "GetAll") == getAllA && stat(B, "GetAll") == getAllB,
              QString("GetAll so far: A %1, B %2 (1 each = the start-up read)").arg(stat(A, "GetAll")).arg(stat(B, "GetAll")));
        getPosA = stat(A, "GetPosition");
        for (int i = 0; i < 3; ++i) l.refreshMediaPosition();
    });
    steps << std::make_pair(2000, [&] {
        const double s = l.mediaPosition() / 1e6;
        check("position runs on the clock: ~13.2 s after playing from 10 s (M5)", std::fabs(s - 13.2) < 0.5, QString::number(s, 'f', 2) + " s");
        check("pulses did not poll the player (M5)", stat(A, "GetPosition") == getPosA, QString("%1 Get(Position)").arg(stat(A, "GetPosition") - getPosA));
        ctl(B, "SetTrack", {"/t/b", "A Video", qlonglong(0)});
        ctl(B, "SetStatus", {"Playing", qlonglong(0)});
    });
    steps << std::make_pair(600, [&] {
        check("a browser does not take over a playing music player (oracle rule)", l.m_activePlayer == A);
        ctl(B, "EmitSeeked", {qlonglong(99000000)});
    });
    steps << std::make_pair(400, [&] {
        check("browser's Seeked lands on the browser, not the music player (M3)",
              l.m_players.value(B).position == 99000000 && l.mediaPosition() < 20000000, QString::number(l.mediaPosition() / 1e6) + " s");
        ctl(A, "SetStatus", {"Paused", qlonglong(14000000)});
    });
    steps << std::make_pair(600, [&] {
        check("music paused while the browser plays -> browser shown (M8)", l.m_activePlayer == B, l.m_activePlayer);
        ctl(A, "SetStatus", {"Playing", qlonglong(14000000)});
    });
    steps << std::make_pair(600, [&] {
        check("music plays again -> takes over from the browser (oracle rule)", l.m_activePlayer == A);
        ctl(A, "SetTrack", {"/t/3", "Song Three", qlonglong(100000000)});
    });
    steps << std::make_pair(700, [&] {
        const double s = l.mediaPosition() / 1e6;
        check("new track restarts the position (M7)", s < 1.5 && l.mediaTitle() == "Song Three", QString::number(s, 'f', 2) + " s");
        if (safeToCommand(l)) l.mediaSeek(50000000);
        else check("REFUSED to seek: now-playing player is not a fake", false, l.m_activePlayer);
    });
    steps << std::make_pair(700, [&] {
        check("seek sends SetPosition(trackid, µs)", statS(A, "SetPosition") == "/t/3 50000000", statS(A, "SetPosition"));
        getAllA = stat(A, "GetAll");
        l.subscribeToPlayers();
        dropRealPlayers(l);
        check("re-scan: title kept at once (M4)", l.mediaTitle() == "Song Three");
    });
    steps << std::make_pair(700, [&] {
        check("re-scan: known players not reset or re-fetched (M4)", !titleBlanked && stat(A, "GetAll") == getAllA);
        std::printf("INFO other programs' calls to the fakes: GetAll A[%s] B[%s]; Get(Position) A[%s]\n",
                    qPrintable(others(A, "GetAll")), qPrintable(others(B, "GetAll")), qPrintable(others(A, "GetPosition")));
        l.removePlayer(A);
        check("music player gone -> the playing browser is shown", l.m_activePlayer == B && l.mediaTitle() == "A Video");
        std::printf("RESULT %s\n", fails ? qPrintable(QString("FAIL (%1)").arg(fails)) : "PASS");
        app.exit(fails ? 1 : 0);
    });

    int at = 0;
    for (auto &s : steps) { at += s.first; QTimer::singleShot(at, s.second); }
    return app.exec();
}
