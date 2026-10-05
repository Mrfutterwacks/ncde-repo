// Lelan — media: MPRIS players on the session bus, the "now playing" player, its metadata, position and
// transport controls (play/pause, next, previous, seek), and the playing app's pid for App Nap.
//
// Rebuilt from oracle: subscribeToPlayers (+lambda), fetchPlayer (+lambda), applyPlayerProps (+isBrowser
// lambda), removePlayer, onPropertiesChanged, onMprisSeeked, refreshMediaPosition (+lambda),
// refreshActiveMediaPid (+lambda), mediaPlayPause/Next/Previous/Seek, PlayerState, the getters.
// Spec: lelan.md §4/§5 (MPRIS: enumerate org.mpris.MediaPlayer2.*, watch Player PropertiesChanged
// PlaybackStatus/Metadata/Position; QHash<QString, PlayerState>), ncde-efficiency.md (async calls; no
// re-enumeration on micro-signals).
//
// Which player is "now playing" is the oracle's rule, kept: a player that starts playing takes over,
// unless the current one is also playing and only a browser would replace a non-browser.
//
// DEFECTS FIXED vs oracle:
//  M1 a PropertiesChanged from any player re-fetched the full state (GetAll) of EVERY player, because the
//     slot could not tell who sent it. Now the sender is known (MprisRelay) and only its own change is
//     applied — no D-Bus call at all.
//  M2 mediaChanged (plus appName/appIcon/durationChanged) fired on every signal, e.g. a volume change;
//     now only when what the shell shows changed.
//  M3 Seeked from any player was written into the active player's position; now into the sender's.
//  M4 a player appearing later re-listed every player and reset each to an empty state until its
//     GetAll came back (the now-playing title blinked out); now only the new player is added.
//  M5 while playing, the position was fetched over D-Bus every second; now it is computed from the last
//     reported position, the clock and the playback Rate, and re-read on Seeked, status/track changes
//     and every 10 s (players that never send Seeked stay correct).
//  M6 playerctld (a proxy that mirrors the real player) was counted as another player; ignored now.
//  M7 a track change without a Position left the previous track's position running; it now restarts
//     from the player's reported position (re-read), else 0.
//  M8 when the now-playing player paused or stopped while another player was playing, the shell kept
//     showing the paused one until the other happened to send a change; it now switches to the one
//     that plays.
#include "Lelan.h"
#include "lelan_dbus_relay.h"

#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusVariant>
#include <QDateTime>
#include <QElapsedTimer>
#include <QTimer>
#include <QtLogging>

namespace {
const QString kMprisPrefix = QStringLiteral("org.mpris.MediaPlayer2.");
const QString kMprisPath = QStringLiteral("/org/mpris/MediaPlayer2");
const QString kPlayerIface = QStringLiteral("org.mpris.MediaPlayer2.Player");
const QString kFdProps = QStringLiteral("org.freedesktop.DBus.Properties");
constexpr int kPositionResyncPulses = 10;

qint64 nowMs()
{
    static QElapsedTimer clock;
    if (!clock.isValid())
        clock.start();
    return clock.elapsed();
}

// oracle lambda: browsers lose to a real player that is already playing
bool isBrowser(const QString &service)
{
    return service.startsWith(QLatin1String("org.mpris.MediaPlayer2.chromium."))
        || service.startsWith(QLatin1String("org.mpris.MediaPlayer2.firefox."))
        || service.startsWith(QLatin1String("org.mpris.MediaPlayer2.plasma-browser-integration"));
}

void onReply(QObject *ctx, const QDBusMessage &call, std::function<void(QDBusPendingCallWatcher *)> done)
{
    auto *w = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(call), ctx);
    QObject::connect(w, &QDBusPendingCallWatcher::finished, ctx, [done = std::move(done)](QDBusPendingCallWatcher *w) {
        w->deleteLater();
        done(w);
    });
}
} // namespace

// ---- getters (the now-playing player) ----
QVariantMap Lelan::media() const { return m_media; }
bool Lelan::mediaActive() const { return m_mediaActive; }
QString Lelan::mediaTitle() const { return m_players.value(m_activePlayer).title; }
QString Lelan::mediaArtist() const { return m_players.value(m_activePlayer).artist; }
QString Lelan::mediaAlbum() const { return m_players.value(m_activePlayer).album; }
QString Lelan::mediaArtUrl() const { return m_players.value(m_activePlayer).artUrl; }
QString Lelan::mediaTrackId() const { return m_players.value(m_activePlayer).trackId; }
qlonglong Lelan::mediaDuration() const { return m_players.value(m_activePlayer).length; }
bool Lelan::mediaPlaying() const { return m_players.value(m_activePlayer).status == QLatin1String("Playing"); }

// M5: last reported position + elapsed time x Rate while playing, never past the track's end
qlonglong Lelan::mediaPosition() const
{
    const auto it = m_players.constFind(m_activePlayer);
    if (it == m_players.constEnd())
        return 0;
    return playerPosition(*it);
}

qlonglong Lelan::playerPosition(const PlayerState &p) const
{
    qlonglong pos = p.position;
    if (p.status == QLatin1String("Playing"))
        pos += qlonglong((nowMs() - p.positionAtMs) * 1000.0 * p.rate);
    if (p.length > 0 && pos > p.length)
        pos = p.length;
    return pos < 0 ? 0 : pos;
}

// ---- players ----
void Lelan::subscribeToPlayers()
{
    if (!m_mprisRelay) {
        m_mprisRelay = new MprisRelay(this,
            [this](const QString &sender, const QVariantMap &changed) {
                const QString name = m_playerByOwner.value(sender);
                if (!name.isEmpty())
                    applyPlayerProps(name, changed);                            // M1
            },
            [this](const QString &sender, qlonglong positionUs) {
                const QString name = m_playerByOwner.value(sender);
                auto it = m_players.find(name);
                if (it == m_players.end())
                    return;
                it->position = positionUs;                                      // M3
                it->positionAtMs = nowMs();
                if (name == m_activePlayer) {
                    m_media.insert(QStringLiteral("position"), positionUs);
                    emit mediaPositionChanged();
                }
            });
    }
    QDBusMessage list = QDBusMessage::createMethodCall(QStringLiteral("org.freedesktop.DBus"), QStringLiteral("/org/freedesktop/DBus"),
                                                       QStringLiteral("org.freedesktop.DBus"), QStringLiteral("ListNames"));
    onReply(this, list, [this](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QStringList> reply = *w;
        if (reply.isError()) {
            qWarning() << "[lelan] session ListNames failed:" << reply.error().name() << reply.error().message();
            return;
        }
        for (const QString &name : reply.value())
            if (name.startsWith(kMprisPrefix) && !m_players.contains(name))     // M4: only new ones
                addPlayer(name);
    });
}

void Lelan::addPlayer(const QString &name)
{
    if (name == QLatin1String("org.mpris.MediaPlayer2.playerctld"))
        return;                                                                  // M6
    PlayerState st;
    st.app = name.mid(kMprisPrefix.size());
    m_players.insert(name, st);
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.connect(name, kMprisPath, kFdProps, QStringLiteral("PropertiesChanged"), m_mprisRelay,
                SLOT(propertiesChanged(QString,QVariantMap,QStringList)));
    bus.connect(name, kMprisPath, kPlayerIface, QStringLiteral("Seeked"), m_mprisRelay, SLOT(seeked(qlonglong)));
    QDBusMessage owner = QDBusMessage::createMethodCall(QStringLiteral("org.freedesktop.DBus"), QStringLiteral("/org/freedesktop/DBus"),
                                                        QStringLiteral("org.freedesktop.DBus"), QStringLiteral("GetNameOwner"));
    owner << name;
    onReply(this, owner, [this, name](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QString> reply = *w;
        if (!reply.isError() && m_players.contains(name)) {
            m_players[name].owner = reply.value();
            m_playerByOwner.insert(reply.value(), name);
        }
    });
    fetchPlayer(name);
}

void Lelan::fetchPlayer(const QString &name)
{
    QDBusMessage getAll = QDBusMessage::createMethodCall(name, kMprisPath, kFdProps, QStringLiteral("GetAll"));
    getAll << kPlayerIface;
    onReply(this, getAll, [this, name](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariantMap> reply = *w;
        if (!reply.isError())
            applyPlayerProps(name, reply.value());
    });
}

void Lelan::applyPlayerProps(const QString &name, const QVariantMap &props)
{
    auto it = m_players.find(name);
    if (it == m_players.end())
        return;
    PlayerState &p = *it;
    const qlonglong before = playerPosition(p);
    bool resync = false;
    if (props.contains(QStringLiteral("PlaybackStatus"))) {
        const QString status = props.value(QStringLiteral("PlaybackStatus")).toString();
        if (status != p.status) {
            p.position = before;                                                 // freeze/restart the clock here
            p.positionAtMs = nowMs();
            p.status = status;
            resync = true;
        }
    }
    if (props.contains(QStringLiteral("Rate"))) {
        p.position = before;
        p.positionAtMs = nowMs();
        p.rate = props.value(QStringLiteral("Rate")).toDouble();
    }
    if (props.contains(QStringLiteral("Metadata"))) {
        QVariantMap md;
        const QVariant raw = props.value(QStringLiteral("Metadata"));
        if (raw.canConvert<QDBusArgument>())
            raw.value<QDBusArgument>() >> md;
        else
            md = raw.toMap();
        p.title = md.value(QStringLiteral("xesam:title")).toString();
        p.artist = md.value(QStringLiteral("xesam:artist")).toStringList().join(QStringLiteral(", "));
        p.album = md.value(QStringLiteral("xesam:album")).toString();
        p.artUrl = md.value(QStringLiteral("mpris:artUrl")).toString();
        const QVariant tid = md.value(QStringLiteral("mpris:trackid"));
        const QString trackId = tid.canConvert<QDBusObjectPath>() ? tid.value<QDBusObjectPath>().path() : tid.toString();
        p.length = md.value(QStringLiteral("mpris:length")).toLongLong();
        if (trackId != p.trackId && !props.contains(QStringLiteral("Position"))) {   // M7
            p.position = 0;
            p.positionAtMs = nowMs();
            resync = true;
        }
        p.trackId = trackId;
    }
    if (props.contains(QStringLiteral("Position"))) {
        p.position = props.value(QStringLiteral("Position")).toLongLong();
        p.positionAtMs = nowMs();
        resync = false;
    }

    // oracle: who is "now playing"
    if (m_activePlayer.isEmpty())
        m_activePlayer = name;
    if (p.status == QLatin1String("Playing") && m_activePlayer != name) {
        const bool activePlaying = m_players.value(m_activePlayer).status == QLatin1String("Playing");
        if (!activePlaying || (isBrowser(m_activePlayer) && !isBrowser(name)))
            m_activePlayer = name;
    }
    // M8: the now-playing player stopped while another plays -> show the one that plays (a non-browser first)
    if (name == m_activePlayer && p.status != QLatin1String("Playing")) {
        QString best;
        for (auto o = m_players.cbegin(); o != m_players.cend(); ++o)
            if (o.key() != name && o->status == QLatin1String("Playing") && (best.isEmpty() || (isBrowser(best) && !isBrowser(o.key()))))
                best = o.key();
        if (!best.isEmpty())
            m_activePlayer = best;
    }
    if (resync)
        readPlayerPosition(name);
    publishMedia();
}

// one Get(Position) for one player (M5/M7 resync)
void Lelan::readPlayerPosition(const QString &name)
{
    QDBusMessage get = QDBusMessage::createMethodCall(name, kMprisPath, kFdProps, QStringLiteral("Get"));
    get << kPlayerIface << QStringLiteral("Position");
    onReply(this, get, [this, name](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<QVariant> reply = *w;
        auto it = m_players.find(name);
        if (reply.isError() || it == m_players.end())
            return;
        it->position = reply.value().toLongLong();
        it->positionAtMs = nowMs();
        if (name == m_activePlayer) {
            m_media.insert(QStringLiteral("position"), mediaPosition());
            emit mediaPositionChanged();
        }
    });
}

void Lelan::removePlayer(const QString &name)
{
    auto it = m_players.find(name);
    if (it == m_players.end())
        return;
    m_playerByOwner.remove(it->owner);
    m_players.erase(it);
    if (m_activePlayer == name) {                                               // oracle: a playing one, else any
        m_activePlayer.clear();
        for (auto p = m_players.cbegin(); p != m_players.cend(); ++p)
            if (p->status == QLatin1String("Playing")) { m_activePlayer = p.key(); break; }
        if (m_activePlayer.isEmpty() && !m_players.isEmpty())
            m_activePlayer = m_players.cbegin().key();
    }
    publishMedia();
}

// M2: announce only what changed. Position is not part of the comparison (it moves every second and
// has its own signal, mediaPositionChanged).
void Lelan::publishMedia()
{
    const PlayerState p = m_players.value(m_activePlayer);
    const bool playing = p.status == QLatin1String("Playing");
    QVariantMap next{
        {QStringLiteral("status"), p.status}, {QStringLiteral("title"), p.title}, {QStringLiteral("artist"), p.artist},
        {QStringLiteral("album"), p.album}, {QStringLiteral("artUrl"), p.artUrl}, {QStringLiteral("duration"), p.length},
        {QStringLiteral("player"), p.app},
    };
    QVariantMap prev = m_media;
    prev.remove(QStringLiteral("position"));
    const bool changed = next != prev;
    const bool playerChanged = m_media.value(QStringLiteral("player")) != p.app;
    const bool durationChanged_ = m_media.value(QStringLiteral("duration")) != p.length;
    next.insert(QStringLiteral("position"), mediaPosition());
    if (m_publishedPlayer != m_activePlayer) {
        m_publishedPlayer = m_activePlayer;
        refreshActiveMediaPid();
    }
    const bool activeChanged = playing != m_mediaActive;
    m_media = next;
    m_mediaActive = playing;
    if (changed || activeChanged)
        emit mediaChanged();
    if (playerChanged) {
        emit appNameChanged();
        emit appIconChanged();
    }
    if (durationChanged_)
        emit durationChanged();
}

// Called on Lelan's 1 s heartbeat while something plays: the bar moves without a D-Bus call; every
// 10th beat the position is re-read in case the player skipped without a Seeked (M5).
void Lelan::refreshMediaPosition()
{
    if (m_activePlayer.isEmpty() || !mediaPlaying())
        return;
    if (++m_positionPulses >= kPositionResyncPulses) {
        m_positionPulses = 0;
        readPlayerPosition(m_activePlayer);
        return;
    }
    m_media.insert(QStringLiteral("position"), mediaPosition());
    emit mediaPositionChanged();
}

// App Nap never naps the app that is playing (Lelan_zen reads m_mediaPid).
void Lelan::refreshActiveMediaPid()
{
    if (m_activePlayer.isEmpty()) {
        m_mediaPid = 0;
        return;
    }
    QDBusMessage call = QDBusMessage::createMethodCall(QStringLiteral("org.freedesktop.DBus"), QStringLiteral("/org/freedesktop/DBus"),
                                                       QStringLiteral("org.freedesktop.DBus"), QStringLiteral("GetConnectionUnixProcessID"));
    call << m_activePlayer;
    const QString name = m_activePlayer;
    onReply(this, call, [this, name](QDBusPendingCallWatcher *w) {
        QDBusPendingReply<uint> reply = *w;
        if (!reply.isError() && name == m_activePlayer)
            m_mediaPid = reply.value();
    });
}

void Lelan::onMprisSeeked(qlonglong positionUs)
{
    auto it = m_players.find(m_activePlayer);
    if (it == m_players.end())
        return;
    it->position = positionUs;
    it->positionAtMs = nowMs();
    m_media.insert(QStringLiteral("position"), positionUs);
    emit mediaPositionChanged();
}

// ---- transport ----
void Lelan::callActivePlayer(const QString &method, const QVariantList &args)
{
    if (m_activePlayer.isEmpty())
        return;
    QDBusMessage m = QDBusMessage::createMethodCall(m_activePlayer, kMprisPath, kPlayerIface, method);
    m.setArguments(args);
    QDBusConnection::sessionBus().asyncCall(m);
}

void Lelan::mediaPlayPause() { callActivePlayer(QStringLiteral("PlayPause"), {}); }
void Lelan::mediaNext() { callActivePlayer(QStringLiteral("Next"), {}); }
void Lelan::mediaPrevious() { callActivePlayer(QStringLiteral("Previous"), {}); }

void Lelan::mediaSeek(qlonglong positionUs)
{
    const QString trackId = mediaTrackId();
    if (m_activePlayer.isEmpty() || trackId.isEmpty())
        return;
    callActivePlayer(QStringLiteral("SetPosition"), {QVariant::fromValue(QDBusObjectPath(trackId)), positionUs});
    const QString name = m_activePlayer;                                         // players that send no Seeked:
    QTimer::singleShot(300, this, [this, name] { readPlayerPosition(name); });   // read back once it landed
}
