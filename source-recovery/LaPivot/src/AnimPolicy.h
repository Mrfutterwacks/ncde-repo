// AnimPolicy — NCDE's animation governor, as QML sees it (`animPolicy.*`).
//
// Spec: my-project/files/anim-policy.md §3 (levels) + zen.md §4 (power profile). Rebuilt
// 2026-09-30 from LaPivot oracle 3507b4c6…; interface is the oracle's exact moc metadata.
//
// Lelan computes the base level (battery, thermal, reduce-motion, hardware-tier floor —
// Lelan::recomputeAnimLevel) and pushes it in with setLevel(). AnimPolicy holds it and the
// individual signals QML also reads directly.
//
// DEFECT FIXED vs oracle: the power-saver profile, all-cores-pegged CPU, memory pressure and
// low battery only set `lowPower`; they never lowered the level, so everything gated on
// `decorative`/`idleLoops`/`instant` ignored them. zen.md §4: power-saver → low-power tier.
// Now any low-power reason raises the effective level to at least 1 (Reduced).
#pragma once

#include <QObject>

class AnimPolicy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int level READ level NOTIFY changed)
    Q_PROPERTY(bool reduceMotion READ reduceMotion NOTIFY changed)
    Q_PROPERTY(bool idleLoops READ idleLoops NOTIFY changed)
    Q_PROPERTY(bool decorative READ decorative NOTIFY changed)
    Q_PROPERTY(bool instant READ instant NOTIFY changed)
    Q_PROPERTY(bool screenIdle READ screenIdle NOTIFY changed)
    Q_PROPERTY(bool thermalPressure READ thermalPressure NOTIFY changed)
    Q_PROPERTY(bool lowPower READ lowPower NOTIFY changed)
    Q_PROPERTY(bool desktopObscured READ desktopObscured NOTIFY changed)

public:
    // anim-policy.md §3
    enum Level { Full = 0, Reduced = 1, Minimal = 2 };

    explicit AnimPolicy(QObject *parent = nullptr);

    int level() const;                       // effective level: max(base, low-power floor)
    bool reduceMotion() const { return m_reduceMotion; }
    bool idleLoops() const { return level() == Full; }     // continuous decorative loops
    bool decorative() const { return level() < Minimal; }  // shimmer, glows, particles
    bool instant() const { return level() >= Minimal; }    // motion → instant / one cross-fade
    bool screenIdle() const { return m_screenIdle; }
    bool thermalPressure() const { return m_thermalPressure; }
    bool lowPower() const;
    bool desktopObscured() const { return m_desktopObscured; }

signals:
    void changed();
    void policyChanged();

public slots:
    void setLevel(int lvl);
    void setReduceMotion(bool on);
    void reevaluate();
    void setThermalPressure(bool on);
    void setDesktopObscured(bool on);
    void onScreenSaverActivated(bool active);
    void onUserInputIdle(bool idle);
    void onVtActiveChanged(bool active);
    void onSessionLocked();
    void onSessionUnlocked();
    void setLowPowerCpu(bool on);
    void setLowPowerProfile(bool on);
    void setLowPowerMemory(bool on);
    void setLowPowerBattery(bool on);

private:
    void setFlag(bool &flag, bool on);
    void applyScreenIdle();

    int m_baseLevel = Full;                  // from Lelan::recomputeAnimLevel
    bool m_reduceMotion = false;
    bool m_screenIdle = false;               // any of the four idle reasons below
    bool m_thermalPressure = false;
    bool m_desktopObscured = false;

    // screen-idle reasons
    bool m_sessionLocked = false;
    bool m_vtInactive = false;
    bool m_screenSaverActive = false;
    bool m_userInputIdle = false;

    // low-power reasons
    bool m_lowPowerCpu = false;              // all cores pegged
    bool m_lowPowerProfile = false;          // net.hadess.PowerProfiles "power-saver"
    bool m_lowPowerMemory = false;           // memory pressure
    bool m_lowPowerBattery = false;          // on battery and below 16%
};
