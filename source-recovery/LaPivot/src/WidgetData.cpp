// WidgetData — core: constructor, Lelan/AnimPolicy/Settings wiring, pulse handler
// Rebuilt from oracle: WidgetData::WidgetData, WidgetData::setLelan, WidgetData::setAnimPolicy,
// WidgetData::onPulse, WidgetData::~WidgetData
// Spec: lelan.md (one owner per service), anim-policy.md §4.4 (no forever timers)
// DEFECTS FIXED vs oracle:
// 1. Added setSettings(Settings*) to follow hourFormat/showSeconds for panel clock
// 2. onPulse gated by AnimPolicy (screenIdle/desktopObscured) — no polling when idle
// 3. setVolume/toggleMute/media* forward to Lelan (single owner per service)
// 4. (2026-10-01) mediaPosition/mediaDuration/mediaSeek are in MILLISECONDS, as every Salon QML file
//    documents and computes (interp += dt*1000, formatTime(x/1000), seek(frac*duration)). Lelan keeps MPRIS
//    microseconds. The oracle passed µs through (the ring's ratio still worked; tap-to-seek landed near 0);
//    the first rebuild divided to SECONDS, so the ring ran to the end each frame and snapped back each
//    second ("the progress loops instead of progressing", operator 2026-10-01).

#include "WidgetData.h"
#include "Lelan.h"
#include "AnimPolicy.h"
#include "Settings.h"

WidgetData::WidgetData(QObject *parent)
    : QObject(parent)
{
    m_colonOn = true;
}

WidgetData::~WidgetData() = default;

void WidgetData::setLelan(Lelan *lelan)
{
    if (m_lelan == lelan)
        return;

    if (m_lelan)
        disconnect(m_lelan, nullptr, this, nullptr);
    m_lelan = lelan;
    if (!lelan)
        return;

    // Forward Lelan signals to WidgetData signals (pass-through)
    connect(lelan, &Lelan::storageChanged, this, &WidgetData::changed);
    connect(lelan, &Lelan::onAudioVolumeUpdated, this, &WidgetData::changed);
    connect(lelan, &Lelan::batteryChanged, this, &WidgetData::changed);
    connect(lelan, &Lelan::networkChanged, this, &WidgetData::changed);
    connect(lelan, &Lelan::mediaChanged, this, &WidgetData::mediaChanged);
    connect(lelan, &Lelan::mediaPositionChanged, this, &WidgetData::mediaPositionChanged);
    connect(lelan, &Lelan::weatherChanged, this, &WidgetData::weatherChanged);
    // W2 (weather): a newly learned place gets its own weather now, not up to 30 min later
    connect(lelan, &Lelan::placeNameChanged, this, &WidgetData::fetchWeather);
    connect(lelan, &Lelan::moonPositionChanged, this, &WidgetData::moonPositionChanged);
    connect(lelan, &Lelan::pulse, this, &WidgetData::onPulse);
}

void WidgetData::setAnimPolicy(AnimPolicy *policy)
{
    m_animPolicy = policy;
}

void WidgetData::setSettings(Settings *settings)
{
    if (m_settings == settings)
        return;
    if (m_settings)
        disconnect(m_settings, &Settings::settingsChanged, this, &WidgetData::updateClock);
    m_settings = settings;
    if (settings) {
        connect(settings, &Settings::settingsChanged, this, &WidgetData::updateClock);
        updateClock();
    }
}

void WidgetData::onPulse(qulonglong tick)
{
    // Colon blink (1 Hz)
    m_colonOn = !m_colonOn;
    emit clockChanged();

    // Respect AnimPolicy: skip heavy work when screen idle or desktop obscured
    bool doWork = true;
    if (m_animPolicy) {
        if (m_animPolicy->screenIdle() || m_animPolicy->desktopObscured())
            doWork = false;
    }

    // stats every 3rd tick (~3 s) when active, every 60th when idle/obscured
    if (tick % (doWork ? 3 : 60) == 0)
        readStats();

    // oracle: weather 5 s after start, then every 30 min (1800 ticks), idle or not
    if (tick == 5 || tick % 1800 == 0)
        fetchWeather();

}

// ---- Pass-through getters (forward to Lelan) ----

QVariantList WidgetData::removableVolumes() const
{
    if (!m_lelan)
        return {};
    return m_lelan->removableVolumes();
}

int WidgetData::volume() const
{
    if (!m_lelan)
        return 0;
    return m_lelan->volume();
}

bool WidgetData::muted() const
{
    if (!m_lelan)
        return false;
    return m_lelan->muted();
}

bool WidgetData::hasBattery() const
{
    if (!m_lelan)
        return false;
    return m_lelan->hasBattery();
}

int WidgetData::batteryLevel() const
{
    if (!m_lelan)
        return 0;
    return static_cast<int>(m_lelan->batteryPercent());
}

bool WidgetData::batteryCharging() const
{
    if (!m_lelan)
        return false;
    return m_lelan->batteryCharging();
}

bool WidgetData::networkUp() const
{
    if (!m_lelan)
        return false;
    return m_lelan->networkUp();
}

bool WidgetData::netOnline() const
{
    if (!m_lelan)
        return false;
    return m_lelan->networkOnline();
}

QString WidgetData::netUp() const
{
    return m_netUp;
}

QString WidgetData::netDown() const
{
    return m_netDown;
}

bool WidgetData::mediaActive() const
{
    if (!m_lelan)
        return false;
    return m_lelan->mediaActive();
}

bool WidgetData::mediaPlaying() const
{
    if (!m_lelan)
        return false;
    return m_lelan->mediaPlaying();
}

QString WidgetData::mediaTitle() const
{
    if (!m_lelan)
        return {};
    return m_lelan->mediaTitle();
}

QString WidgetData::mediaArtist() const
{
    if (!m_lelan)
        return {};
    return m_lelan->mediaArtist();
}

QString WidgetData::mediaAlbum() const
{
    if (!m_lelan)
        return {};
    return m_lelan->mediaAlbum();
}

double WidgetData::mediaPosition() const
{
    if (!m_lelan)
        return 0.0;
    return static_cast<double>(m_lelan->mediaPosition()) / 1000.0;     // µs → ms (fix 4)
}

double WidgetData::mediaDuration() const
{
    if (!m_lelan)
        return 0.0;
    return static_cast<double>(m_lelan->mediaDuration()) / 1000.0;     // µs → ms (fix 4)
}

// ---- Invokables (forward to Lelan) ----

void WidgetData::setVolume(int v)
{
    if (m_lelan)
        m_lelan->setVolume(v);
}

void WidgetData::toggleMute()
{
    if (m_lelan)
        m_lelan->toggleMute();
}

void WidgetData::mediaTogglePlay()
{
    if (m_lelan)
        m_lelan->mediaPlayPause();
}

void WidgetData::mediaNext()
{
    if (m_lelan)
        m_lelan->mediaNext();
}

void WidgetData::mediaPrev()
{
    if (m_lelan)
        m_lelan->mediaPrevious();
}

void WidgetData::mediaSeek(double p)
{
    if (m_lelan)
        m_lelan->mediaSeek(static_cast<qlonglong>(p * 1000.0));      // ms → µs (fix 4)
}

void WidgetData::mountVolume(const QString &p)
{
    if (m_lelan)
        m_lelan->mountVolume(p);
}

void WidgetData::unmountVolume(const QString &p)
{
    if (m_lelan)
        m_lelan->unmountVolume(p);
}