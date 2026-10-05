// ZenGovernor — the "brain" half of Lelan (zen.md, anim-policy.md): scheduling self-boost,
// thermal / CPU / memory pressure, and the animation level Lelan hands to AnimPolicy.
//
// Rebuilt 2026-09-30 from LaPivot oracle 3507b4c6… (Lelan::applyZenStartupHints,
// setAnimUtilClamp, checkThermalZones, discoverThermalThresholds, checkCpuFreq, updatePressure,
// onLowMemoryWarning, recomputeAnimLevel). The decision logic is kept in pure functions
// (namespace zen) so it can be tested against the oracle's behaviour without a desktop.
//
// DEFECTS FIXED vs oracle:
//  Z1 SCHED_FIFO leaked into every process LaPivot spawned (no SCHED_RESET_ON_FORK), so apps
//     ignored App Nap cgroup weights and scx_bpfland, and a CPU-bound child (mksquashfs) froze
//     the desktop. Now every FIFO thread is FIFO|RESET_ON_FORK: children and background threads
//     start as SCHED_OTHER; render threads promote themselves (promoteCurrentThread()).
//  Z6 Lelan sensed the hardware itself (thermal zones + cpufreq, on its once-a-minute coalesced tick) instead of
//     listening to Sentinel, and its "CPU pegged" test (every core >= 95% of max FREQUENCY) is
//     true at idle on HWP/amd-pstate machines — measured on the operator's laptop: the oracle
//     ran updatePressure(pegged=1) on AC, cool, idle -> animation level 1 (Reduced) from login.
//     Now Sentinel senses (sentinel/pressure.py: real busy time, CPU temps with hwmon fallback,
//     the machine's own trip point) and ZenGovernor only decides from PressureSensed.
//  Z2 The animation uclamp boost (zen.md §3 layer 2) had no caller, and its sched_setattr used
//     KEEP_POLICY without KEEP_PARAMS -> EINVAL for a SCHED_FIFO thread. Now KEEP_POLICY|
//     KEEP_PARAMS, applied to the render threads, driven by the animation level.
#pragma once

#include <QObject>
#include <QList>
#include <QString>

namespace zen {

// updatePressure: 0 none, 1 elevated, 2 severe.
int pressure(bool thermalHot, bool cpuPegged, int memoryLevel);

// recomputeAnimLevel (anim-policy.md §3): 0 Full, 1 Reduced, 2 Minimal.
int animLevel(bool onBattery, int batteryPct, bool reduceMotion, int pressure, bool lowHardwareTier);

// onLowMemoryWarning: portal level byte -> 0/1/2 (>=100 elevated, >=200 severe).
int memoryLevel(unsigned char portalLevel);

// checkThermalZones hysteresis: hot at >= high, cleared at <= low, unchanged in between.
bool thermalHot(bool wasHot, int maxTempC, double highC, double lowC);

// discoverThermalThresholds: from the lowest "critical"/"hot" trip point (°C).
struct Thresholds { double high; double low; };
Thresholds thresholdsFromTrip(double lowestTripC);   // <= 0 -> fallback 89 / 84 °C


} // namespace zen

class ZenGovernor : public QObject
{
    Q_OBJECT
public:
    explicit ZenGovernor(QObject *parent = nullptr);

    // Process start (Lelan ctor). autogroup nice -5, then SCHED_FIFO 1 | RESET_ON_FORK on the
    // calling (GUI) thread. Best effort: needs CAP_SYS_NICE (set by packaging).
    static void applyStartupHints();
    // Call ON a thread that must never stall (QQuickWindow::sceneGraphInitialized,
    // DirectConnection -> runs on the render thread). Same policy as the GUI thread.
    static bool promoteCurrentThread();
    // uclamp.min 200/1024 on/off for the calling thread, keeping its policy and priority.
    static bool setUtilClampMin(bool boost);

    int pressure() const { return m_pressure; }
    bool thermalHot() const { return m_thermalHot; }
    bool cpuPegged() const { return m_cpuPegged; }
    // Was missing: Lelan needs it to push current memory pressure to AnimPolicy at
    // connect time, the same way cpuPegged() is used. Read-only.
    int memoryLevel() const { return m_memoryLevel; }

public slots:
    // io.ncde.Sentinel PressureSensed(d max_c, b cpu_saturated) — connected by Lelan
    void onPressureSensed(double maxTempC, bool cpuSaturated);
    // io.ncde.Sentinel GetThermalTrip() reply; <= 0 keeps the 89/84 °C fallback
    void setThermalTrip(double tripC);
    void onLowMemoryWarning(uchar level);
    void onSentinelThermalCritical();         // forces hot, same as the oracle

signals:
    void pressureChanged(int pressure);
    void thermalCapNeeded(bool on);           // Lelan -> Sentinel.SetThermalCap
    void cpuPeggedChanged(bool on);           // Lelan -> AnimPolicy::setLowPowerCpu
    void memoryPressureChanged(bool on);      // Lelan -> AnimPolicy::setLowPowerMemory

private:
    void updatePressure();

    zen::Thresholds m_thresholds {89.0, 84.0};
    bool m_thermalHot = false;
    bool m_cpuPegged = false;
    int m_memoryLevel = 0;
    int m_pressure = 0;
};
