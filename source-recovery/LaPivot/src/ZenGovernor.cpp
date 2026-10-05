#include "ZenGovernor.h"

#include <QFile>
#include <QtLogging>

#include <algorithm>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/sched.h>        // SCHED_RESET_ON_FORK, SCHED_FLAG_*

namespace {

// <linux/sched/types.h> layout (SCHED_ATTR_SIZE_VER1, 56 bytes). Declared here because glibc
// does not wrap sched_setattr.
struct SchedAttr {
    quint32 size;
    quint32 sched_policy;
    quint64 sched_flags;
    qint32 sched_nice;
    quint32 sched_priority;
    quint64 sched_runtime;
    quint64 sched_deadline;
    quint64 sched_period;
    quint32 sched_util_min;
    quint32 sched_util_max;
};
static_assert(sizeof(SchedAttr) == 56, "sched_attr VER1 is 56 bytes");

constexpr int kFifoPriority = 1;           // lowest RT priority: beats every normal task, no more
constexpr quint32 kAnimUtilMin = 200;      // of 1024 — zen.md §2

} // namespace

// ---- pure decision logic ----------------------------------------------------------------------

int zen::pressure(bool thermalHot, bool cpuPegged, int memoryLevel)
{
    return std::max({thermalHot ? 2 : 0, cpuPegged ? 1 : 0, memoryLevel});
}

int zen::animLevel(bool onBattery, int batteryPct, bool reduceMotion, int pressure, bool lowHardwareTier)
{
    int level = 0;
    if (onBattery || pressure > 0)
        level = 1;
    if (reduceMotion || pressure > 1 || (onBattery && batteryPct < 16))
        level = 2;
    return std::max(level, lowHardwareTier ? 1 : 0);
}

int zen::memoryLevel(unsigned char portalLevel)
{
    return portalLevel >= 200 ? 2 : portalLevel >= 100 ? 1 : 0;
}

bool zen::thermalHot(bool wasHot, int maxTempC, double highC, double lowC)
{
    if (maxTempC <= 0)
        return wasHot;                      // no reading: keep state
    if (maxTempC >= highC)
        return true;
    if (maxTempC <= lowC)
        return false;
    return wasHot;
}

zen::Thresholds zen::thresholdsFromTrip(double lowestTripC)
{
    if (lowestTripC <= 0.0)
        return {89.0, 84.0};
    return {lowestTripC * 0.85, lowestTripC * 0.80};
}

// ---- scheduling -------------------------------------------------------------------------------

void ZenGovernor::applyStartupHints()
{
    QFile autogroup(QStringLiteral("/proc/self/autogroup"));
    if (autogroup.open(QIODevice::WriteOnly))
        autogroup.write("-5\n");
    if (!promoteCurrentThread())
        qInfo("[lelan] SCHED_FIFO(1) unavailable (no CAP_SYS_NICE)");
}

bool ZenGovernor::promoteCurrentThread()
{
    sched_param p {};
    p.sched_priority = kFifoPriority;
    // RESET_ON_FORK: anything this thread creates — a thread or a whole process — starts as
    // SCHED_OTHER. Only threads that call this function are real-time (Z1).
    return sched_setscheduler(0, SCHED_FIFO | SCHED_RESET_ON_FORK, &p) == 0;
}

bool ZenGovernor::setUtilClampMin(bool boost)
{
    SchedAttr attr {};
    attr.size = sizeof(attr);
    // KEEP_PARAMS as well as KEEP_POLICY: without it the kernel validates sched_priority 0
    // against the thread's SCHED_FIFO policy and rejects the call (Z2).
    attr.sched_flags = SCHED_FLAG_KEEP_POLICY | SCHED_FLAG_KEEP_PARAMS | SCHED_FLAG_UTIL_CLAMP_MIN;
    attr.sched_util_min = boost ? kAnimUtilMin : 0;
    return syscall(SYS_sched_setattr, 0, &attr, 0) == 0;
}

// ---- sensing ----------------------------------------------------------------------------------

ZenGovernor::ZenGovernor(QObject *parent)
    : QObject(parent)
{
}

void ZenGovernor::setThermalTrip(double tripC)
{
    m_thresholds = zen::thresholdsFromTrip(tripC);
}

void ZenGovernor::onPressureSensed(double maxTempC, bool cpuSaturated)
{
    const bool hot = zen::thermalHot(m_thermalHot, int(maxTempC), m_thresholds.high, m_thresholds.low);
    const bool hotChanged = hot != m_thermalHot;
    const bool satChanged = cpuSaturated != m_cpuPegged;
    m_thermalHot = hot;
    m_cpuPegged = cpuSaturated;
    if (hotChanged || satChanged)
        updatePressure();
    if (hotChanged)
        emit thermalCapNeeded(hot);
    if (satChanged)
        emit cpuPeggedChanged(cpuSaturated);
}

void ZenGovernor::onLowMemoryWarning(uchar level)
{
    m_memoryLevel = zen::memoryLevel(level);
    updatePressure();
    emit memoryPressureChanged(m_memoryLevel > 0);
}

void ZenGovernor::onSentinelThermalCritical()
{
    if (m_thermalHot)
        return;
    m_thermalHot = true;
    updatePressure();
    emit thermalCapNeeded(true);
}

void ZenGovernor::updatePressure()
{
    const int p = zen::pressure(m_thermalHot, m_cpuPegged, m_memoryLevel);
    if (p == m_pressure)
        return;
    m_pressure = p;
    emit pressureChanged(p);
}
