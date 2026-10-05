// animpolicy_diff — differential test: the ORIGINAL AnimPolicy (called inside the oracle binary)
// vs the rebuilt one (src/AnimPolicy.cpp), same random inputs, compared after every step.
//
// Build as a preload .so together with src/AnimPolicy.cpp, run against a cap-free copy of the
// oracle:  LD_PRELOAD=./animpolicy_diff.so ANIMDIFF=1 ./LaPivot.run
// Exits before the oracle's main(). Offsets are the oracle's `nm` values (sha256 3507b4c6…).
//
// Two phases:
//   1. faithful — no low-power inputs: every property and every changed() emission must match.
//   2. fixed    — all inputs: must equal the oracle with the spec fix applied
//                 (effective level = max(base, lowPower ? 1 : 0)), derived flags from that.
#include "../src/AnimPolicy.h"
#include <QtCore/QObject>
#include <cstdio>
#include <cstdlib>
#include <link.h>
#include <random>

namespace {
uintptr_t base()
{
    uintptr_t b = 0;
    dl_iterate_phdr([](dl_phdr_info *i, size_t, void *d) { *static_cast<uintptr_t *>(d) = i->dlpi_addr; return 1; }, &b);
    return b;
}
template <typename F> F at(uintptr_t off) { return reinterpret_cast<F>(base() + off); }

using Ctor = void (*)(void *, QObject *);
using GetB = bool (*)(void *);
using GetI = int (*)(void *);
using SetB = void (*)(void *, bool);
using SetI = void (*)(void *, int);
using Act = void (*)(void *);

struct Oracle {
    alignas(16) unsigned char mem[0x100] = {};
    void *o = mem;
    Oracle() { at<Ctor>(0x53596)(o, nullptr); }
    int level() { return at<GetI>(0x536f0)(o); }
    bool reduceMotion() { return at<GetB>(0x53702)(o); }
    bool idleLoops() { return at<GetB>(0x53714)(o); }
    bool decorative() { return at<GetB>(0x5372a)(o); }
    bool instant() { return at<GetB>(0x53742)(o); }
    bool screenIdle() { return at<GetB>(0x5375a)(o); }
    bool thermalPressure() { return at<GetB>(0x5376c)(o); }
    bool lowPower() { return at<GetB>(0x5377e)(o); }
    bool desktopObscured() { return at<GetB>(0x537c4)(o); }
    QObject *qobj() { return reinterpret_cast<QObject *>(o); }
};

// op table: index -> (oracle offset, kind). kind 0 = bool setter, 1 = int setter, 2 = no-arg.
struct Op { const char *name; uintptr_t off; int kind; bool lowPower; };
const Op kOps[] = {
    {"setLevel", 0x537d6, 1, false},          {"setReduceMotion", 0x5380a, 0, false},
    {"reevaluate", 0x53842, 2, false},        {"setThermalPressure", 0x5385e, 0, false},
    {"setDesktopObscured", 0x53896, 0, false}, {"onScreenSaverActivated", 0x538ce, 0, false},
    {"onUserInputIdle", 0x538f8, 0, false},   {"onVtActiveChanged", 0x53922, 0, false},
    {"onSessionLocked", 0x53952, 2, false},   {"onSessionUnlocked", 0x53976, 2, false},
    {"setLowPowerCpu", 0x5399a, 0, true},     {"setLowPowerProfile", 0x539d2, 0, true},
    {"setLowPowerMemory", 0x53a0a, 0, true},  {"setLowPowerBattery", 0x53a42, 0, true},
};

void applyNew(AnimPolicy &n, const char *name, int iv, bool bv)
{
    if (!strcmp(name, "setLevel")) QMetaObject::invokeMethod(&n, name, Q_ARG(int, iv));
    else if (!strcmp(name, "reevaluate") || !strcmp(name, "onSessionLocked") || !strcmp(name, "onSessionUnlocked"))
        QMetaObject::invokeMethod(&n, name);
    else QMetaObject::invokeMethod(&n, name, Q_ARG(bool, bv));
}

int run(bool withLowPower, int steps, unsigned seed)
{
    Oracle o;
    AnimPolicy n;
    int oEmits = 0, nEmits = 0, oPol = 0, nPol = 0;
    auto om = o.qobj()->metaObject();
    int fail = 0;
    std::mt19937 rng(seed);
    const int nOps = sizeof(kOps) / sizeof(kOps[0]);
    QMetaObject::Connection c1 = QObject::connect(&n, &AnimPolicy::changed, [&] { nEmits++; });
    QMetaObject::Connection c2 = QObject::connect(&n, &AnimPolicy::policyChanged, [&] { nPol++; });
    // the oracle's signals: a receiver whose qt_metacall counts the two slots it is connected to
    struct Rx : QObject {
        int *a, *b;
        int qt_metacall(QMetaObject::Call c, int id, void **v) override {
            id = QObject::qt_metacall(c, id, v);
            if (id < 0 || c != QMetaObject::InvokeMetaMethod) return id;
            (id == 0 ? *a : *b)++;
            return -1;
        }
    } rx;
    rx.a = &oEmits; rx.b = &oPol;
    int base_ = QObject::staticMetaObject.methodCount();
    QMetaObject::connect(o.qobj(), om->indexOfSignal("changed()"), &rx, base_ + 0);
    QMetaObject::connect(o.qobj(), om->indexOfSignal("policyChanged()"), &rx, base_ + 1);

    for (int s = 0; s < steps && fail < 10; ++s) {
        const Op &op = kOps[rng() % nOps];
        if (op.lowPower && !withLowPower) { --s; continue; }
        int iv = int(rng() % 3);
        bool bv = rng() & 1;
        switch (op.kind) {
        case 0: at<SetB>(op.off)(o.o, bv); break;
        case 1: at<SetI>(op.off)(o.o, iv); break;
        default: at<Act>(op.off)(o.o); break;
        }
        applyNew(n, op.name, iv, bv);

        int want = o.level();
        if (withLowPower && o.lowPower() && want < 1) want = 1;       // the spec fix
        bool ok = n.level() == want && n.idleLoops() == (want == 0) && n.decorative() == (want < 2)
               && n.instant() == (want >= 2) && n.reduceMotion() == o.reduceMotion()
               && n.screenIdle() == o.screenIdle() && n.thermalPressure() == o.thermalPressure()
               && n.lowPower() == o.lowPower() && n.desktopObscured() == o.desktopObscured()
               && nEmits == oEmits && nPol == oPol;
        if (!withLowPower)
            ok = ok && n.level() == o.level() && n.idleLoops() == o.idleLoops()
                    && n.decorative() == o.decorative() && n.instant() == o.instant();
        if (!ok) {
            fail++;
            std::printf("  MISMATCH step %d after %s(%d/%d): level new %d oracle %d (want %d) lowPower %d/%d "
                        "emits %d/%d policy %d/%d\n", s, op.name, iv, bv, n.level(), o.level(), want,
                        n.lowPower(), o.lowPower(), nEmits, oEmits, nPol, oPol);
        }
    }
    std::printf("%s: %d steps, %d mismatches, changed() emitted %d (new) / %d (oracle)\n",
                withLowPower ? "phase 2 fixed   " : "phase 1 faithful", steps, fail, nEmits, oEmits);
    return fail;
}
} // namespace

__attribute__((constructor)) static void runDiff()
{
    if (!std::getenv("ANIMDIFF")) return;
    int f = run(false, 200000, 1) + run(true, 200000, 2);
    std::printf(f ? "RESULT: FAIL\n" : "RESULT: PASS\n");
    std::fflush(stdout);
    std::_Exit(f ? 1 : 0);
}
