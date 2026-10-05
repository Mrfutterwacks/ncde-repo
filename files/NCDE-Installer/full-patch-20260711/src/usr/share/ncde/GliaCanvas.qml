// GliaCanvas.qml — Glia, the fountain-pen governess, as native cel animation.
//
// Frame advance: Image+sourceClipRect slices a 1×4 horizontal sprite strip; a
// self-rescheduling single-shot Timer advances cels with per-cel ms holds.
//
// Why option (a) over AnimatedSprite/SpriteSequence: per-frame durations require
// one Sprite QML object per cel, so N states × 4 cels = 4N objects with no
// benefit over a guarded Timer. The Timer approach is fewer lines and equally
// safe once two Qt6 QML binding pitfalls are removed:
//
//   Pitfall 1 — `running: true` binding:
//     In Qt6's QProperty-backed binding system a constant `true` binding on
//     `running` is owned by the binding observer. When the C++ timer engine sets
//     running=false after firing (repeat:false), the QProperty notifier
//     immediately re-evaluates the binding and restarts the timer BEFORE
//     onTriggered runs its own start() — two active timers, then four, then
//     eight: exponential firings → GUI-thread starvation → hard freeze.
//     Fix: no `running` binding; start imperatively from Component.onCompleted.
//
//   Pitfall 2 — `interval: expr` binding:
//     The binding depends on `cur`. When onTriggered assigns `cur = "idle"`,
//     QML schedules a re-evaluation of the `interval` binding that can race
//     against the explicit `interval = …` JS assignment, producing a stale or
//     doubled interval. Fix: no `interval` binding; compute it only through
//     safeInterval() inside play() and onTriggered.
//
//   GliaCanvas { id: glia; assetBase: settings.assetBase + "/glia/" }
//   glia.react("greet"|"point"|"approve"|"flourish"|"worry"|"talk")
import QtQuick 2.15

Item {
    id: root
    property string assetBase: "gliaanim/"
    implicitWidth: 240
    implicitHeight: 420

    readonly property int celW: 340
    readonly property int celH: 600
    property real speed: 1.0           // global timing multiplier (>1 = slower)

    // state → 1×4 strip + per-cel hold (ms). idle loops; others play once.
    // INVARIANT: timing.length must equal the number of cels on the strip (4 here).
    readonly property var defs: ({
        "idle":     { "loop": true,  "timing": [1600, 900, 1300, 900] },
        "talk":     { "loop": false, "timing": [340, 220, 180, 500] },
        "point":    { "loop": false, "timing": [300, 220, 300, 700] },
        "approve":  { "loop": false, "timing": [340, 300, 340, 600] },
        "flourish": { "loop": false, "timing": [340, 260, 300, 700] },
        "worry":    { "loop": false, "timing": [420, 340, 400, 800] }
    })
    readonly property var route: ({
        "greet":"talk", "talk":"talk", "point":"point", "open":"point",
        "select":"approve", "approve":"approve", "new":"flourish",
        "duplicate":"flourish", "flourish":"flourish", "delete":"worry", "worry":"worry",
        "column":"point", "grid":"flourish", "list":"approve"
    })

    property string cur: "idle"
    property int    frame: 0
    property int    dir: 1             // ping-pong direction for loop:true states

    // Returns a safe timer interval for the given state name and frame index.
    // Guards every failure mode that produces a runaway: bad state, bad index,
    // undefined timing value, non-positive hold, NaN, speed=0.
    function safeInterval(name, f) {
        var cfg = defs[name];
        if (!cfg || !cfg.timing || cfg.timing.length === 0) return 200;
        var idx  = (f >= 0 && f < cfg.timing.length) ? f : 0;
        var sp   = (speed > 0 && isFinite(speed)) ? speed : 1.0;
        var hold = (cfg.timing[idx] || 200) * sp;
        return (hold > 0 && isFinite(hold)) ? Math.round(hold) : 200;
    }

    function play(name) {
        if (!defs[name]) return;
        clock.stop();
        cur = name; frame = 0; dir = 1;
        clock.interval = safeInterval(name, 0);
        clock.start();
    }
    function react(kind) { play(route[kind] ? route[kind] : "point"); }

    Timer {
        id: clock
        // No `running: true` binding and no `interval: expr` binding — see file
        // header for why both are hazardous on a self-rescheduling repeat:false
        // Timer in Qt6. Started imperatively from Component.onCompleted below.
        repeat: false
        onTriggered: {
            var cfg     = defs[cur];
            var nFrames = (cfg && cfg.timing) ? cfg.timing.length : 4;
            if (cfg && cfg.loop) {
                // Ping-pong (2026-07-14, same technique applied to
                // BinnieCanvas — researched: standard for symmetric
                // breathing/idle sprite loops): bounce 0,1,2,3,2,1,0,...
                // instead of hard-wrapping 3 straight back to 0, so the
                // existing 4 cels read as an actual breathing motion.
                var next = frame + dir;
                if (next >= nFrames) { dir = -1; next = nFrames - 2; }
                else if (next < 0)   { dir = 1;  next = 1; }
                frame = next;
            } else {
                var lin = frame + 1;
                if (lin >= nFrames) { cur = "idle"; frame = 0; dir = 1; }
                else { frame = lin; }
            }
            interval = safeInterval(cur, frame);
            start();
        }
    }

    Component.onCompleted: {
        clock.interval = safeInterval(cur, frame);
        clock.start();
    }

    Item {
        width: root.celW; height: root.celH
        anchors.centerIn: parent
        scale: Math.min(root.width / root.celW, root.height / root.celH) * 0.99
        transformOrigin: Item.Center

        Image {
            anchors.fill: parent
            smooth: true; cache: true; fillMode: Image.Stretch
            source: root.assetBase + root.cur + ".png"
            sourceClipRect: Qt.rect(root.frame * root.celW, 0, root.celW, root.celH)
        }
    }
}
