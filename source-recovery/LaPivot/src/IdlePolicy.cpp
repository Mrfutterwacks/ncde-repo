// IdlePolicy — see IdlePolicy.h.
#include "IdlePolicy.h"

unsigned IdlePolicy::sample(qint64 idleMs, bool saverRunning)
{
    unsigned out = None;
    // input since the last sample: X idle went down -> a new idle period, everything re-arms (I4)
    if (idleMs < m_lastIdle) {
        reset();
        if (saverRunning)
            out |= StopSaver;           // (the saver quits on a key itself; this covers a mouse move)
    }
    m_lastIdle = idleMs;
    if (out)
        return out;

    const qint64 saverAt = qint64(m_cfg.saverMinutes) * 60000;
    const qint64 suspendAt = qint64(m_cfg.suspendMinutes) * 60000;

    // suspend first: it supersedes the saver and the idle lock (I1: counted in real idle minutes)
    if (m_cfg.suspendMinutes > 0 && idleMs >= suspendAt && !m_suspended) {
        m_suspended = true;
        m_locked = m_locked || m_cfg.requirePassword;   // the lock before sleep is the suspend's own
        return (saverRunning ? unsigned(StopSaver) : 0u) | Suspend;
    }
    if (m_cfg.saverMinutes > 0 && idleMs >= saverAt && !m_saverStarted && !m_suspended) {
        m_saverStarted = true;
        out |= StartSaver;
    }
    // "Require password after ... screensaver begins", after the chosen delay (I3)
    if (m_cfg.requirePassword && m_cfg.saverMinutes > 0 && m_saverStarted && !m_locked
        && idleMs >= saverAt + qint64(m_cfg.passwordDelaySec) * 1000) {
        m_locked = true;
        out = (out & ~unsigned(StartSaver)) | Lock | (saverRunning ? unsigned(StopSaver) : 0u);
    }
    return out;
}

bool IdlePolicy::saverEnded(bool crashed, qint64 idleMsNow)
{
    // a clean exit is the user dismissing it; a crash is relaunched only while nobody has come back
    // (idle still growing since the last sample) and at most 3 times per idle period (oracle: 3 / 60 s)
    if (!crashed || idleMsNow < m_lastIdle || !m_saverStarted || m_locked || m_suspended)
        return false;
    m_lastIdle = idleMsNow;
    return ++m_relaunches <= 3;
}
