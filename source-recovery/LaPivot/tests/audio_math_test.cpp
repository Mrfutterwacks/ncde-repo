// audio_math_test — Lelan_audio.cpp volume/balance maths vs the oracle's (decomp Lelan.c:
// applyChannelVolumes 00235370, paSinkInfoCb 00233900), every volume 0..100 x balance 0..100.
#include <pulse/volume.h>
#include <QtGlobal>
#include <cmath>
#include <cstdio>
static int oracleLeft(int vol, int bal) { double f = bal < 0x33 ? 1.0 : (100.0 - bal) / 50.0; return qRound(vol / 100.0 * f * 65536.0); }
static int oracleRight(int vol, int bal) { double f = bal < 0x32 ? bal / 50.0 : 1.0; return qRound(vol / 100.0 * f * 65536.0); }
static int oraclePercent(unsigned v) { return qRound(double(v) * 100.0 / 65536.0); }
// rebuilt (same expressions as Lelan_audio.cpp)
static pa_volume_t fromPercent(double pct) { return pa_volume_t(std::lround(pct / 100.0 * PA_VOLUME_NORM)); }
static int toPercent(pa_volume_t v) { return int(std::lround(double(v) * 100.0 / PA_VOLUME_NORM)); }
int main()
{
    int bad = 0, n = 0;
    for (int vol = 0; vol <= 100; ++vol)
        for (int bal = 0; bal <= 100; ++bal, ++n) {
            const double left = bal <= 50 ? 1.0 : (100.0 - bal) / 50.0;
            const double right = bal >= 50 ? 1.0 : bal / 50.0;
            int l = int(fromPercent(vol * left)), r = int(fromPercent(vol * right));
            if (std::abs(l - oracleLeft(vol, bal)) > 1 || std::abs(r - oracleRight(vol, bal)) > 1) {
                if (bad++ < 5) std::printf("  balance mismatch vol %d bal %d: new %d/%d oracle %d/%d\n", vol, bal, l, r, oracleLeft(vol, bal), oracleRight(vol, bal));
            }
        }
    for (unsigned v = 0; v <= 2 * PA_VOLUME_NORM; v += 7, ++n)
        if (toPercent(v) != oraclePercent(v) && bad++ < 10) std::printf("  percent mismatch %u\n", v);
    std::printf("%d cases, %d mismatches (<=1 LSB rounding tolerance)\n%s\n", n, bad, bad ? "RESULT: FAIL" : "RESULT: PASS");
    return bad != 0;
}
