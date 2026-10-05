// zen_test — proof for src/ZenGovernor.
//
// Part A (no privileges): each zen:: decision function vs a literal transcription of the
// oracle's decompiled conditions (decomp/Lelan.c: recomputeAnimLevel 0024a0fa, updatePressure
// 002487d0, onLowMemoryWarning 0024b3ae, checkThermalZones 00249418, discoverThermalThresholds
// 002488d2, checkCpuFreq 002498fc), over the whole input space.
//
// Part B (needs CAP_SYS_NICE on this binary — `sudo setcap cap_sys_nice+ep zen_test`):
// real syscalls. Z1: a promoted thread is FIFO; threads and processes it creates are OTHER;
// a thread that promotes itself is FIFO. Z2: the oracle's exact sched_setattr (flags 0x28)
// fails with EINVAL on a FIFO thread; the fixed call succeeds and sets util_min 200.
#include "../src/ZenGovernor.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <linux/sched.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

static int failures = 0;
#define CHECK(cond, ...) do { if (!(cond)) { ++failures; std::printf("  FAIL: " __VA_ARGS__); std::printf("\n"); } } while (0)

// ---- oracle transcriptions (kept deliberately close to the decompile) -------------------------
static int oracleLevel(bool onBat /*0x33a*/, int pct, bool reduce /*0x339*/, int press /*0x324*/, int floor_ /*0x358*/)
{
    int l = 0;
    if (onBat || 0 < press) l = 1;
    if ((reduce || 1 < press) || (onBat && pct < 0x10)) l = 2;
    if (l < floor_) l = floor_;
    return l;
}
static int oraclePressure(bool hot /*0x374*/, bool pegged /*0x388*/, int mem /*0x370*/)
{
    int a = hot ? 2 : 0, b = pegged ? 1 : 0;
    int m = a > b ? a : b;           // qMax(&local_1c,&local_18)
    return mem > m ? mem : m;        // qMax(this+0x370, ...)
}
static int oracleMem(unsigned char p) { return p < 200 ? (p < 100 ? 0 : 1) : 2; }
static bool oracleHot(bool was, int t, double hi, double lo)
{
    if (!(0 < t)) return was;
    bool v = was;
    if ((double)t < hi) { if ((double)t <= lo) v = false; }
    else v = true;
    return v;
}

static void partA()
{
    long n = 0;
    for (int b = 0; b < 2; ++b) for (int pct = -1; pct <= 101; ++pct) for (int r = 0; r < 2; ++r)
        for (int p = 0; p <= 2; ++p) for (int t = 0; t < 2; ++t) {
            ++n;
            CHECK(zen::animLevel(b, pct, r, p, t) == oracleLevel(b, pct, r, p, t ? 1 : 0),
                  "animLevel(%d,%d,%d,%d,%d)", b, pct, r, p, t);
        }
    for (int h = 0; h < 2; ++h) for (int c = 0; c < 2; ++c) for (int m = 0; m <= 2; ++m, ++n)
        CHECK(zen::pressure(h, c, m) == oraclePressure(h, c, m), "pressure(%d,%d,%d)", h, c, m);
    for (int v = 0; v < 256; ++v, ++n)
        CHECK(zen::memoryLevel(v) == oracleMem(v), "memoryLevel(%d)", v);
    for (int w = 0; w < 2; ++w) for (int t = -5; t <= 130; ++t)
        for (double hi : {89.0, 76.5, 85.0}) for (double lo : {84.0, 72.0, 80.0}) {
            ++n;
            CHECK(zen::thermalHot(w, t, hi, lo) == oracleHot(w, t, hi, lo), "thermalHot(%d,%d,%g,%g)", w, t, hi, lo);
        }
    // thresholds: oracle fallback bytes 0x4056400000000000 / 0x4055000000000000
    double fh, fl; quint64 bh = 0x4056400000000000ULL, bl = 0x4055000000000000ULL;
    std::memcpy(&fh, &bh, 8); std::memcpy(&fl, &bl, 8);
    auto f = zen::thresholdsFromTrip(-1.0);
    CHECK(f.high == fh && f.low == fl, "fallback thresholds %g/%g vs %g/%g", f.high, f.low, fh, fl);
    auto t = zen::thresholdsFromTrip(100.0);
    CHECK(t.high == 100.0 * 0.85 && t.low == 100.0 * 0.8, "trip thresholds");
    n += 2;
    // Z6: decisions from Sentinel's facts (PressureSensed). Idle + cool + on AC must be level 0.
    {
        ZenGovernor g; int lastPressure = -1, caps = 0;
        QObject::connect(&g, &ZenGovernor::pressureChanged, [&](int p) { lastPressure = p; });
        QObject::connect(&g, &ZenGovernor::thermalCapNeeded, [&](bool) { ++caps; });
        g.setThermalTrip(110.05);                                  // this laptop: hot 93.5, clear 88.04
        g.onPressureSensed(61, false);
        CHECK(g.pressure() == 0 && zen::animLevel(false, 100, false, g.pressure(), false) == 0,
              "idle, 61C, on AC -> pressure 0, level 0 (oracle measured level 1 here)");
        g.onPressureSensed(61, true);  CHECK(g.pressure() == 1 && lastPressure == 1, "saturated -> 1");
        g.onPressureSensed(94, true);  CHECK(g.pressure() == 2 && caps == 1, "94C -> hot, cap on");
        g.onPressureSensed(90, false); CHECK(g.pressure() == 2 && caps == 1, "90C inside hysteresis stays hot");
        g.onPressureSensed(88, false); CHECK(g.pressure() == 0 && caps == 2, "88C clears, cap off");
        n += 5;
    }
    std::printf("part A: %ld cases checked against the oracle transcription\n", n);
}

// ---- part B -----------------------------------------------------------------------------------
struct SchedAttr { quint32 size, policy; quint64 flags; qint32 nice; quint32 prio;
                   quint64 rt, dl, per; quint32 umin, umax; };

static int policyOf(pid_t tid) { return sched_getscheduler(tid) & ~SCHED_RESET_ON_FORK; }
static bool resetOnFork(pid_t tid) { return sched_getscheduler(tid) & SCHED_RESET_ON_FORK; }

static void partB()
{
    if (!ZenGovernor::promoteCurrentThread()) {
        std::printf("part B: SKIPPED — no CAP_SYS_NICE (sudo setcap cap_sys_nice+ep on this binary)\n");
        return;
    }
    const pid_t self = syscall(SYS_gettid);
    CHECK(policyOf(self) == SCHED_FIFO && resetOnFork(self), "promoted thread is FIFO|RESET_ON_FORK");

    int childThreadPolicy = -1, promotedThreadPolicy = -1;
    std::thread([&] { childThreadPolicy = policyOf(0); }).join();
    std::thread([&] { ZenGovernor::promoteCurrentThread(); promotedThreadPolicy = policyOf(0); }).join();
    CHECK(childThreadPolicy == SCHED_OTHER, "thread created by FIFO thread is OTHER (got %d)", childThreadPolicy);
    CHECK(promotedThreadPolicy == SCHED_FIFO, "render-style thread promotes itself to FIFO");

    pid_t pid = fork();
    if (pid == 0) _exit(policyOf(0) == SCHED_OTHER ? 0 : 1);
    int st = 0; waitpid(pid, &st, 0);
    CHECK(WIFEXITED(st) && WEXITSTATUS(st) == 0, "forked process is OTHER (Z1: no RT leak)");

    // Z2: the oracle's exact request
    SchedAttr a {}; a.size = sizeof(a); a.flags = 0x28; a.umin = 200;
    long r = syscall(SYS_sched_setattr, 0, &a, 0);
    CHECK(r == -1 && errno == EINVAL, "oracle flags 0x28 on a FIFO thread -> EINVAL (got %ld errno %d)", r, errno);
    std::printf("  oracle setAnimUtilClamp request: %s\n", r == -1 ? strerror(errno) : "accepted");

    CHECK(ZenGovernor::setUtilClampMin(true), "fixed uclamp boost accepted on FIFO thread");
    SchedAttr g {};
    syscall(SYS_sched_getattr, 0, &g, sizeof(g), 0);
    CHECK(g.umin == 200 && policyOf(self) == SCHED_FIFO, "util_min 200, still FIFO (got %u)", g.umin);
    CHECK(ZenGovernor::setUtilClampMin(false), "boost release accepted");
    syscall(SYS_sched_getattr, 0, &g, sizeof(g), 0);
    CHECK(g.umin == 0, "util_min back to 0");
    std::printf("part B: kernel checks done\n");
}

int main()
{
    partA();
    partB();
    std::printf(failures ? "RESULT: FAIL (%d)\n" : "RESULT: PASS\n", failures);
    return failures ? 1 : 0;
}
