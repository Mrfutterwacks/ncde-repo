// suntimes_diff — preload into the oracle: its own (anonymous)::computeSunTimes (offset 0x14276e)
// vs the rebuilt one in Lelan_time.cpp, over a lat/lon grid; plus lelanIsNight vs the oracle's
// scheduleNightLightEvents condition for every minute of the day. Exits before the oracle's main().
#include <QDateTime>
#include <QTime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <link.h>
bool lelanIsNight(double sunset, double sunrise, double nowHours);
#include "../src/lelan_suntimes.inc"
static uintptr_t base() { uintptr_t b = 0; dl_iterate_phdr([](dl_phdr_info *i, size_t, void *d) { *static_cast<uintptr_t *>(d) = i->dlpi_addr; return 1; }, &b); return b; }
static bool oracleNight(double p1 /*sunset*/, double p2 /*sunrise*/, double t)
{
    if (p1 <= p2) return !((t < p1) || (p2 <= t));
    return (p1 <= t) || (t < p2);
}
__attribute__((constructor)) static void run()
{
    if (!std::getenv("SUNDIFF")) return;
    using Fn = void (*)(double, double, double *, double *);
    Fn oracle = reinterpret_cast<Fn>(base() + 0x14276e);
    int n = 0, bad = 0, polar = 0;
    for (double lat = -89; lat <= 89; lat += 2.5)
        for (double lon = -180; lon <= 180; lon += 7.5, ++n) {
            double orR = -9, orS = -9, nwR = -9, nwS = -9;
            oracle(lat, lon, &orR, &orS);
            sunTimes(lat, lon, nwR, nwS);
            if (orR < 0) ++polar;
            if (std::fabs(orR - nwR) > 1e-9 || std::fabs(orS - nwS) > 1e-9)
                if (bad++ < 5) std::printf("  mismatch lat %g lon %g: oracle %.4f/%.4f new %.4f/%.4f\n", lat, lon, orR, orS, nwR, nwS);
        }
    int nb = 0, nn = 0;
    for (double ss : {18.5, 20.25, 2.0}) for (double sr : {6.0, 5.5, 23.0})
        for (int m = 0; m < 24 * 60; ++m, ++nn)
            if (lelanIsNight(ss, sr, m / 60.0) != oracleNight(ss, sr, m / 60.0)) ++nb;
    std::printf("sun times: %d locations (%d polar), %d mismatches\nnight flag: %d cases, %d mismatches\n%s\n",
                n, polar, bad, nn, nb, (bad || nb) ? "RESULT: FAIL" : "RESULT: PASS");
    std::fflush(stdout);
    std::_Exit(bad || nb);
}
