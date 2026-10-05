// IdlePolicy — what an idle desktop does, and when: start the screensaver, require the password, suspend.
// Pure decisions (no X, no processes): the window manager feeds it the X idle time it already polls
// (NCDEWindowManager::pollUserIdle, every 2 s) and Settings carries out the returned actions.
//
// The settings it follows (PowerTab, ScreensaverTab, SecurityTab — the tabs are the spec):
//   screensaverTimeout  "start the screensaver after T minutes"            (0 = never)
//   <ac|bat>Suspend     "Suspend after K minutes" on AC / on battery       (0 = never)
//   requirePassword     "Require password after sleep or screensaver begins"
//   requirePasswordDelay  0 / 5 / 60 / 300 s after the screensaver begins
// Blanking (DPMS) is the X server's own timer (xset dpms), not decided here.
//
// Replaces the oracle's idle handling, which had these defects (measured in the decompile 2026-09-30):
//  I1 Settings::onScreenIdleChanged ran `systemctl suspend` on ANY AnimPolicy change while screenIdle was
//     true and the suspend setting was > 0 — it never counted the minutes. screenIdle turns true after 30 s
//     without input, so on battery ("Suspend after 15 min") the laptop suspended ~30 s after the last input,
//     and xss-lock locked it (the operator's "it locks if idle too long").
//  I2 the X screensaver timeout was set to the SUSPEND minutes (xset s), so xss-lock also locked the session
//     at suspend-minutes + 10 min (cycle 600) even with suspend off on the other power source's value.
//  I3 requirePassword / requirePasswordDelay were saved and loaded but never used: the lock ignored them.
//  I4 a screensaver that exited non-zero was relaunched while the WM's idle flag was still set (re-read only
//     every 2 s), i.e. it could come straight back after the user had just touched a key.
#pragma once

#include <QtGlobal>

class IdlePolicy
{
public:
    struct Config {
        int saverMinutes = 0;           // 0 = no screensaver
        int suspendMinutes = 0;         // for the current power source; 0 = never
        bool requirePassword = true;
        int passwordDelaySec = 0;
    };
    enum Action : unsigned {
        None = 0,
        StartSaver = 1,                 // launch the screensaver
        StopSaver = 2,                  // the user is back (or a lock / suspend takes over)
        Lock = 4,                       // lock the session (password)
        Suspend = 8,                    // suspend; the lock before sleep follows requirePassword
    };

    // one X idle sample (ms since the last user input). `saverRunning` = the screensaver process is up.
    unsigned sample(qint64 idleMs, bool saverRunning);
    // the screensaver process ended by itself; true = start it again (it crashed and nobody is back yet)
    bool saverEnded(bool crashed, qint64 idleMsNow);
    void setConfig(const Config &c) { m_cfg = c; }
    const Config &config() const { return m_cfg; }
    // after a resume or an unlock the user is present: nothing fires again until idle builds up anew
    void userPresent() { reset(); }

private:
    void reset() { m_saverStarted = m_locked = m_suspended = false; m_relaunches = 0; }
    Config m_cfg;
    qint64 m_lastIdle = 0;
    bool m_saverStarted = false;        // latched for this idle period
    bool m_locked = false;
    bool m_suspended = false;
    int m_relaunches = 0;
};
