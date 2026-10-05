// Lelan — audio: one libpulse connection (pipewire-pulse) for volume, balance, mute, output/input
// devices and per-application streams (lelan.md §4: Lelan is the one owner of audio).
//
// Rebuilt from oracle: subscribeToAudio, stopPulse, applyPulseState, applyChannelVolumes,
// setVolume, setBalance, toggleMute, setOutputDevice, setInputDevice, setAppVolume,
// applyOutputDevices/InputDevices/AppStreams/DefaultSource, retryFallbackSink, and the
// anonymous-namespace pa* callbacks.
//
// DEFECTS FIXED vs oracle:
//  A1 setOutputDevice called pa_context_get_server_info after releasing the threaded-mainloop
//     lock (every libpulse call must hold it) — a data race on the context.
//  A2 device/stream lists were accumulated in three GLOBAL lists shared by every in-flight query;
//     whichever query ended first published and cleared them (and a query ending in error, e.g.
//     a sink vanishing mid-list, published a partial list). Now each query owns its list.
//  A3/A4 every server event re-published devices/streams and re-emitted audioChanged/volume/mute
//     even when nothing changed. Now: emit only on change.
//  A5 setAppVolume built a 2-channel volume for every stream; libpulse rejects a mismatched channel
//     count, so mono / surround streams silently ignored the slider. Now each stream's own count.
//  A6 setAppVolume stopped at the first stream with that name; two streams from one app (two
//     browser tabs) only moved one. Now every stream of that app.
#include "Lelan.h"

#include <QMetaObject>
#include <QPointer>

#include <pulse/pulseaudio.h>
#include <cmath>
#include <utility>

namespace {

struct ListQuery {                    // one per in-flight list request (A2)
    Lelan *lelan;
    QVariantList items;
};

int toPercent(pa_volume_t v) { return int(std::lround(double(v) * 100.0 / PA_VOLUME_NORM)); }
pa_volume_t fromPercent(double pct) { return pa_volume_t(std::lround(pct / 100.0 * PA_VOLUME_NORM)); }
QString str(const char *s) { return s ? QString::fromUtf8(s) : QString(); }

template <typename F> void onLelan(Lelan *l, F &&f)
{
    // libpulse callbacks run on the pulse mainloop thread; Lelan state is touched on its own thread
    QMetaObject::invokeMethod(l, std::forward<F>(f), Qt::QueuedConnection);
}

void sinkInfoCb(pa_context *, const pa_sink_info *i, int eol, void *ud)
{
    if (eol || !i)
        return;
    auto *l = static_cast<Lelan *>(ud);
    const int vol = toPercent(pa_cvolume_avg(&i->volume));
    const bool muted = i->mute;
    const QString name = str(i->name);
    const uint index = i->index;
    const int channels = i->volume.channels;
    onLelan(l, [l, vol, muted, name, index, channels] { l->applyPulseStateFromBridge(vol, muted, name, index, channels); });
}

void serverInfoCb(pa_context *c, const pa_server_info *i, void *ud)
{
    if (!i)
        return;
    auto *l = static_cast<Lelan *>(ud);
    if (i->default_source_name) {
        const QString src = str(i->default_source_name);
        onLelan(l, [l, src] { l->applyDefaultSourceFromBridge(src); });
    }
    if (i->default_sink_name)
        if (pa_operation *op = pa_context_get_sink_info_by_name(c, i->default_sink_name, sinkInfoCb, ud))
            pa_operation_unref(op);
}

void sinkInputListCb(pa_context *, const pa_sink_input_info *i, int eol, void *ud)
{
    auto *q = static_cast<ListQuery *>(ud);
    if (eol) {                                       // end (eol > 0) or error (eol < 0)
        if (eol > 0) {
            Lelan *l = q->lelan;
            QVariantList items = std::move(q->items);
            onLelan(l, [l, items] { l->applyAppStreamsFromBridge(items); });
        }
        delete q;
        return;
    }
    const char *app = pa_proplist_gets(i->proplist, PA_PROP_APPLICATION_NAME);
    const char *media = pa_proplist_gets(i->proplist, PA_PROP_MEDIA_NAME);
    q->items.append(QVariantMap{
        {QStringLiteral("name"), app ? str(app) : (i->name ? str(i->name) : QStringLiteral("Audio"))},
        {QStringLiteral("meta"), media ? str(media) : str(i->name)},
        {QStringLiteral("vol"), toPercent(pa_cvolume_avg(&i->volume))},
        {QStringLiteral("index"), i->index},
        {QStringLiteral("channels"), int(i->volume.channels)},       // A5
    });
}

void sinkListCb(pa_context *, const pa_sink_info *i, int eol, void *ud)
{
    auto *q = static_cast<ListQuery *>(ud);
    if (eol) {
        if (eol > 0) {
            Lelan *l = q->lelan;
            QVariantList items = std::move(q->items);
            onLelan(l, [l, items] { l->applyOutputDevicesFromBridge(items); });
        }
        delete q;
        return;
    }
    q->items.append(QVariantMap{{QStringLiteral("name"), str(i->name)},
                                {QStringLiteral("description"), i->description ? str(i->description) : str(i->name)}});
}

void sourceListCb(pa_context *, const pa_source_info *i, int eol, void *ud)
{
    auto *q = static_cast<ListQuery *>(ud);
    if (eol) {
        if (eol > 0) {
            Lelan *l = q->lelan;
            QVariantList items = std::move(q->items);
            onLelan(l, [l, items] { l->applyInputDevicesFromBridge(items); });
        }
        delete q;
        return;
    }
    if (i->monitor_of_sink != PA_INVALID_INDEX)
        return;                                      // monitors are not microphones
    q->items.append(QVariantMap{{QStringLiteral("name"), str(i->name)},
                                {QStringLiteral("description"), i->description ? str(i->description) : str(i->name)}});
}

void requestServerInfo(pa_context *c, void *ud)
{
    if (pa_operation *op = pa_context_get_server_info(c, serverInfoCb, ud))
        pa_operation_unref(op);
}
void requestSinkInputs(pa_context *c, Lelan *l)
{
    if (pa_operation *op = pa_context_get_sink_input_info_list(c, sinkInputListCb, new ListQuery{l, {}}))
        pa_operation_unref(op);
}
void requestSinks(pa_context *c, Lelan *l)
{
    if (pa_operation *op = pa_context_get_sink_info_list(c, sinkListCb, new ListQuery{l, {}}))
        pa_operation_unref(op);
}
void requestSources(pa_context *c, Lelan *l)
{
    if (pa_operation *op = pa_context_get_source_info_list(c, sourceListCb, new ListQuery{l, {}}))
        pa_operation_unref(op);
}

void subscribeCb(pa_context *c, pa_subscription_event_type_t t, uint32_t, void *ud)
{
    auto *l = static_cast<Lelan *>(ud);
    const auto facility = t & PA_SUBSCRIPTION_EVENT_FACILITY_MASK;
    if (facility == PA_SUBSCRIPTION_EVENT_SINK || facility == PA_SUBSCRIPTION_EVENT_SERVER)
        requestServerInfo(c, ud);
    if (facility == PA_SUBSCRIPTION_EVENT_SINK_INPUT)
        requestSinkInputs(c, l);
    if (facility == PA_SUBSCRIPTION_EVENT_SINK)
        requestSinks(c, l);
    if (facility == PA_SUBSCRIPTION_EVENT_SOURCE)
        requestSources(c, l);
}

void stateCb(pa_context *c, void *ud)
{
    if (pa_context_get_state(c) != PA_CONTEXT_READY)
        return;
    auto *l = static_cast<Lelan *>(ud);
    pa_context_set_subscribe_callback(c, subscribeCb, ud);
    const auto mask = pa_subscription_mask_t(PA_SUBSCRIPTION_MASK_SINK | PA_SUBSCRIPTION_MASK_SOURCE
                                             | PA_SUBSCRIPTION_MASK_SINK_INPUT | PA_SUBSCRIPTION_MASK_SERVER);
    if (pa_operation *op = pa_context_subscribe(c, mask, nullptr, nullptr))
        pa_operation_unref(op);
    requestServerInfo(c, ud);
    requestSinkInputs(c, l);
    requestSinks(c, l);
    requestSources(c, l);
}

class PulseLock
{
public:
    explicit PulseLock(pa_threaded_mainloop *m) : m_loop(m) { pa_threaded_mainloop_lock(m_loop); }
    ~PulseLock() { pa_threaded_mainloop_unlock(m_loop); }
    PulseLock(const PulseLock &) = delete;
    PulseLock &operator=(const PulseLock &) = delete;
private:
    pa_threaded_mainloop *m_loop;
};

} // namespace

// ---- getters ----------------------------------------------------------------------------------

QVariantMap Lelan::audio() const { return m_audio; }
int Lelan::volume() const { return m_volume; }
int Lelan::balance() const { return m_balance; }
bool Lelan::muted() const { return m_muted; }
QVariantList Lelan::appStreams() const { return m_appStreams; }
QVariantList Lelan::outputDevices() const { return m_outputDevices; }
QVariantList Lelan::inputDevices() const { return m_inputDevices; }
QString Lelan::defaultSourceName() const { return m_defaultSourceName; }

// ---- connection -------------------------------------------------------------------------------

void Lelan::subscribeToAudio()
{
    if (m_pulseLoop)
        return;                                      // already connected (re-armed on wake)
    m_pulseLoop = pa_threaded_mainloop_new();
    if (!m_pulseLoop)
        return;
    m_pulseCtx = pa_context_new(pa_threaded_mainloop_get_api(m_pulseLoop), "ncde-lelan");
    pa_context_set_state_callback(m_pulseCtx, stateCb, this);
    pa_threaded_mainloop_lock(m_pulseLoop);
    const bool failed = pa_context_connect(m_pulseCtx, nullptr, PA_CONTEXT_NOFAIL, nullptr) < 0
                        || pa_threaded_mainloop_start(m_pulseLoop) < 0;
    pa_threaded_mainloop_unlock(m_pulseLoop);
    if (failed)
        stopPulse();
}

void Lelan::stopPulse()
{
    if (!m_pulseLoop)
        return;
    pa_threaded_mainloop_stop(m_pulseLoop);
    if (m_pulseCtx) {
        pa_context_disconnect(m_pulseCtx);
        pa_context_unref(m_pulseCtx);
        m_pulseCtx = nullptr;
    }
    pa_threaded_mainloop_free(m_pulseLoop);
    m_pulseLoop = nullptr;
}

void Lelan::retryFallbackSink()
{
    if (!m_pulseLoop || !m_pulseCtx)
        return;
    PulseLock lock(m_pulseLoop);
    requestServerInfo(m_pulseCtx, this);
}

// ---- state from the pulse thread (queued onto Lelan's thread) --------------------------------

void Lelan::applyPulseStateFromBridge(int volume, bool muted, const QString &sink, uint sinkIndex, int channels)
{
    applyPulseState(volume, muted, sink, sinkIndex, channels);
}

void Lelan::applyPulseState(int volume, bool muted, const QString &sink, uint sinkIndex, int channels)
{
    m_sinkIndex = sinkIndex;
    m_sinkChannels = channels > 0 ? channels : 2;
    const bool sinkChanged = sink != m_sinkName;
    const bool volChanged = volume != m_volume;
    const bool muteChanged = muted != m_muted;
    m_sinkName = sink;
    m_volume = volume;
    m_muted = muted;
    if (!(sinkChanged || volChanged || muteChanged))
        return;                                      // A4
    m_audio.insert(QStringLiteral("volume"), volume);
    m_audio.insert(QStringLiteral("muted"), muted);
    m_audio.insert(QStringLiteral("sink"), sink);
    if (volChanged)
        emit onAudioVolumeUpdated();
    if (muteChanged)
        emit onAudioMuteUpdated();
    emit audioChanged();
    if (sinkChanged) {
        emit audioDeviceChanged();
        emit onFallbackSinkUpdated();
    }
}

void Lelan::applyOutputDevicesFromBridge(const QVariantList &devs) { applyOutputDevices(devs); }
void Lelan::applyOutputDevices(const QVariantList &devs)
{
    if (devs == m_outputDevices)
        return;                                      // A3
    m_outputDevices = devs;
    emit audioDevicesChanged();
}

void Lelan::applyInputDevicesFromBridge(const QVariantList &devs) { applyInputDevices(devs); }
void Lelan::applyInputDevices(const QVariantList &devs)
{
    if (devs == m_inputDevices)
        return;
    m_inputDevices = devs;
    emit audioDevicesChanged();
}

void Lelan::applyAppStreamsFromBridge(const QVariantList &streams) { applyAppStreams(streams); }
void Lelan::applyAppStreams(const QVariantList &streams)
{
    if (streams == m_appStreams)
        return;
    m_appStreams = streams;
    emit appStreamsChanged();
}

void Lelan::applyDefaultSourceFromBridge(const QString &name) { applyDefaultSource(name); }
void Lelan::applyDefaultSource(const QString &name)
{
    if (name == m_defaultSourceName)
        return;
    m_defaultSourceName = name;
    emit audioDeviceChanged();
}

// ---- controls ---------------------------------------------------------------------------------

void Lelan::applyChannelVolumes()
{
    if (!m_pulseLoop || !m_pulseCtx || m_sinkIndex == PA_INVALID_INDEX)
        return;
    pa_cvolume cv;
    pa_cvolume_set(&cv, uint8_t(m_sinkChannels), fromPercent(m_volume));
    if (m_sinkChannels > 1) {
        // balance 0..100, 50 = centre: the far side is attenuated, the near side stays full
        const double left = m_balance <= 50 ? 1.0 : (100.0 - m_balance) / 50.0;
        const double right = m_balance >= 50 ? 1.0 : m_balance / 50.0;
        cv.values[0] = fromPercent(m_volume * left);
        cv.values[1] = fromPercent(m_volume * right);
    }
    PulseLock lock(m_pulseLoop);
    if (pa_operation *op = pa_context_set_sink_volume_by_index(m_pulseCtx, m_sinkIndex, &cv, nullptr, nullptr))
        pa_operation_unref(op);
}

void Lelan::setVolume(int v)
{
    m_volume = qBound(0, v, 100);
    applyChannelVolumes();
    emit onAudioVolumeUpdated();
}

void Lelan::setBalance(int v)
{
    v = qBound(0, v, 100);
    if (v == m_balance)
        return;
    m_balance = v;
    applyChannelVolumes();
    emit audioChanged();
}

void Lelan::toggleMute()
{
    m_muted = !m_muted;
    if (m_pulseLoop && m_pulseCtx && m_sinkIndex != PA_INVALID_INDEX) {
        PulseLock lock(m_pulseLoop);
        if (pa_operation *op = pa_context_set_sink_mute_by_index(m_pulseCtx, m_sinkIndex, m_muted, nullptr, nullptr))
            pa_operation_unref(op);
    }
    emit onAudioMuteUpdated();
}

void Lelan::setOutputDevice(const QString &name)
{
    if (!m_pulseLoop || !m_pulseCtx || name.isEmpty())
        return;
    const QByteArray sink = name.toUtf8();
    PulseLock lock(m_pulseLoop);
    if (pa_operation *op = pa_context_set_default_sink(m_pulseCtx, sink.constData(), nullptr, nullptr))
        pa_operation_unref(op);
    for (const QVariant &s : std::as_const(m_appStreams)) {     // move what is playing now, too
        const uint idx = s.toMap().value(QStringLiteral("index")).toUInt();
        if (pa_operation *op = pa_context_move_sink_input_by_name(m_pulseCtx, idx, sink.constData(), nullptr, nullptr))
            pa_operation_unref(op);
    }
    requestServerInfo(m_pulseCtx, this);                         // A1: still under the lock
}

void Lelan::setInputDevice(const QString &name)
{
    if (!m_pulseLoop || !m_pulseCtx || name.isEmpty())
        return;
    const QByteArray src = name.toUtf8();
    PulseLock lock(m_pulseLoop);
    if (pa_operation *op = pa_context_set_default_source(m_pulseCtx, src.constData(), nullptr, nullptr))
        pa_operation_unref(op);
}

void Lelan::setAppVolume(const QString &name, int volumePct)
{
    if (!m_pulseLoop || !m_pulseCtx)
        return;
    const pa_volume_t v = fromPercent(qBound(0, volumePct, 100));
    PulseLock lock(m_pulseLoop);
    for (const QVariant &s : std::as_const(m_appStreams)) {     // A6: every stream of that app
        const QVariantMap m = s.toMap();
        if (m.value(QStringLiteral("name")).toString() != name)
            continue;
        pa_cvolume cv;
        pa_cvolume_set(&cv, uint8_t(qMax(1, m.value(QStringLiteral("channels"), 2).toInt())), v);   // A5
        if (pa_operation *op = pa_context_set_sink_input_volume(m_pulseCtx, m.value(QStringLiteral("index")).toUInt(),
                                                                &cv, nullptr, nullptr))
            pa_operation_unref(op);
    }
}
