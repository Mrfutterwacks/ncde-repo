// BinnieCanvas.qml — Binnie the NCDE mascot, native cel player.
//
// Single hardware Image layer performs discrete cel swaps (source/
// sourceClipRect updated directly on each frame-advance tick) — the same
// technique classic sprite-based animated characters (e.g. Microsoft Agent /
// Clippy) used: hard cuts between drawn cels, not a cross-dissolve blend.
// 2026-07-14 (operator: "looks like two images superimposed... 4 arms
// between animations"): the previous two-layer opacity-crossfade design
// blended between DISTINCT hand-drawn poses (not a lighting/colour change),
// which has no valid in-between and reads as ghosting/double limbs instead
// of motion — researched (see chat) and confirmed this is exactly why
// traditional cel/sprite animation always hard-cuts between frames instead.
// Replaced with a single Image layer; the crossfade mechanism (the
// `dissolve` NumberAnimation, the second `fadeLayer` Image, the `next`
// property) is removed entirely, not just hidden.
// Frame advance is a self-rescheduling single-shot Timer with per-cel ms
// holds. Idle LOOPS (4 cels, ~1.1s holds — Binnie breathes at rest, same as
// GliaCanvas's loop:true idle); actions play once then fall back into the
// idle loop. "Alive" impact squash via an OutElastic spring, unrelated to
// and unaffected by this change.
// 2026-07-06 (session 79, operator: "his animations are gone"): the earlier
// defensive rewrite of this player never STARTED the idle loop — nothing played
// "idle" at load and finished actions stopped dead, so Binnie stood frozen
// unless poked, while Glia kept looping. Restored: Component.onCompleted plays
// idle; action-finished falls back into play("idle"). Every safeInterval guard
// below is untouched — the tight-loop freeze that rewrite defended against
// remains impossible.
//
// Defensive pattern (safeInterval):
//   The frame-advance Timer computes: hold = timing[frame] * speed. Any path
//   that yields hold ≤ 0, NaN, or undefined makes the Timer fire in a tight
//   loop and freeze the GUI thread. safeInterval() guards every call site:
//   bad state name → 200 ms; out-of-range frame → clamp to index 0; falsy
//   timing entry → 200 ms; speed ≤ 0 or non-finite → 1.0; non-positive or
//   non-finite result → 200 ms. 200 ms is the minimum safe floor.
//
//   BinnieCanvas { id: binnie; assetBase: settings.assetBase + "/binnie/" }
//   binnie.react("poke")   // wave   binnie.react("restore") // cheer
//   binnie.react("empty")  // dizzy  binnie.react("toss")    // gulp
import QtQuick 2.15

Item {
    id: root
    property string assetBase: "anim/"
    implicitWidth: 280
    implicitHeight: 420

    readonly property int celW: 451
    readonly property int celH: 681
    property real speed: 2.4          // global timing multiplier (>1 = slower)

    // state → ordered strips (4 cels each) + per-cel hold in MILLISECONDS.
    // INVARIANT: timing.length must equal frames (verified below; used as the
    // authoritative frame count via cfg.timing.length in onTriggered).
    readonly property var defs: ({
        "idle":  { "sheets": ["idle"],                        "frames": 4,
                   "timing": [1100, 1100, 1100, 1100] },
        "wave":  { "sheets": ["wave","wave_b"],               "frames": 8,
                   "timing": [160, 90, 70, 70, 70, 70, 110, 420] },
        "cheer": { "sheets": ["cheer_a","cheer_b","cheer_c"], "frames": 12,
                   "timing": [260, 200, 150, 50, 50, 60, 130, 130, 60, 50, 110, 400] },
        "dizzy": { "sheets": ["dizzy_a","dizzy_b"],           "frames": 8,
                   "timing": [90, 90, 90, 90, 90, 90, 100, 400] },
        "cry":   { "sheets": ["cry","cry_b"],                 "frames": 8,
                   "timing": [340, 100, 100, 240, 100, 100, 140, 400] },
        "gulp":  { "sheets": ["gulp_a","gulp_b"],             "frames": 8,
                   "timing": [420, 320, 60, 60, 70, 120, 170, 420] },
        "talk":  { "sheets": ["talk","talk_b"],               "frames": 8,
                   "timing": [140, 80, 200, 100, 140, 70, 170, 120] }
    })

    property string cur: "idle"      // "idle" = resting (loops — Binnie breathes)
    property int    frame: 0         // the single displayed cel
    property int    dir: 1           // idle ping-pong direction (+1/-1); unused by other states
    readonly property bool resting: cur === "idle"

    Component.onCompleted: play("idle")   // start the idle loop — he is alive at rest

    function _src(f)  { var c = defs[cur]; return assetBase + c.sheets[Math.floor(f / 4)] + ".png"; }
    function _clip(f) { return Qt.rect((f % 4) * celW, 0, celW, celH); }

    // Returns a safe timer interval. Guards every failure mode that produces a
    // runaway: bad state, out-of-range frame, falsy timing entry, speed ≤ 0.
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
        // Order matters (2026-07-14, root-caused live via journal: "qrc:/anim/
        // undefined.png"): QML re-evaluates dependent bindings synchronously
        // after EACH property write, not after the whole function returns. If
        // `cur` changed first, `source: root._src(root.frame)` would briefly
        // run with the NEW state's (possibly shorter) sheets array but the
        // OLD, stale frame value, indexing past the end. frame=0 always maps
        // to sheets[0], which every state has at least one of, so resetting
        // it BEFORE cur changes keeps every intermediate binding evaluation
        // in-bounds regardless of which state is "current" at that instant.
        frame = 0;
        dir = 1;
        cur = name;
        clock.interval = safeInterval(name, 0); clock.start();
    }
    function react(kind) {
        var m = { "poke":"wave","wave":"wave","restore":"cheer","cheer":"cheer",
                  "empty":"dizzy","dizzy":"dizzy","toss":"gulp","gulp":"gulp",
                  "cry":"cry","talk":"talk" };
        play(m[kind] ? m[kind] : "wave");
        if (kind === "restore" || kind === "cheer" || kind === "toss" || kind === "gulp")
            impact.restart();
    }

    // ── self-rescheduling single-shot clock (X11-safe) ──────────────────
    Timer {
        id: clock
        repeat: false
        onTriggered: {
            var cfg = root.defs[root.cur];
            if (!cfg) {                                   // defensive: unknown state → rest
                root.cur = "idle"; root.frame = 0;
                return;
            }
            // Use timing.length as authoritative frame count (guards against frames
            // field being out of sync with the timing array after future edits).
            var nFrames  = cfg.timing.length;
            var incoming;
            if (root.cur === "idle") {
                // Ping-pong (2026-07-14, researched: this is the standard
                // technique for symmetric breathing/idle sprite loops --
                // action sequences stay linear below, ping-pong only suits
                // back-and-forth motion, not one-shot narrative poses).
                // Hard-wrapping straight from the last frame back to the
                // first snapped visibly since idle's 4 cels are a breathe-in
                // arc, not a seamless 360 loop; bouncing 0,1,2,3,2,1,0...
                // reads as actual breathing using the exact same 4 drawings.
                incoming = root.frame + root.dir;
                if (incoming >= nFrames) { root.dir = -1; incoming = nFrames - 2; }
                else if (incoming < 0)   { root.dir = 1;  incoming = 1; }
            } else {
                incoming = (root.frame + 1) % nFrames;
                if (incoming === 0) {                     // action finished → back to the idle loop
                    root.play("idle");
                    return;
                }
            }
            root.frame = incoming;                        // hard cut to the next cel
            if (root.cur === "cheer" && root.frame === 3) impact.restart();
            interval = root.safeInterval(root.cur, root.frame); start();
        }
    }

    // ── scale-to-fit + feet-anchored impact squash ──────────────────────
    Item {
        id: rig
        width: root.celW; height: root.celH
        anchors.centerIn: parent
        scale: Math.min(root.width / root.celW, root.height / root.celH) * 0.99
        transformOrigin: Item.Bottom

        property real sx: 1.0
        property real sy: 1.0
        transform: Scale { origin.x: rig.width / 2; origin.y: rig.height; xScale: rig.sx; yScale: rig.sy }
        ParallelAnimation {
            id: impact
            SequentialAnimation {
                NumberAnimation { target: rig; property: "sy"; from: 1.0; to: 0.8;  duration: 80;  easing.type: Easing.OutQuad }
                NumberAnimation { target: rig; property: "sy"; to: 1.12; duration: 140; easing.type: Easing.InOutQuad }
                NumberAnimation { target: rig; property: "sy"; to: 1.0;  duration: 360; easing.type: Easing.OutElastic }
            }
            SequentialAnimation {
                NumberAnimation { target: rig; property: "sx"; from: 1.0; to: 1.2;  duration: 80;  easing.type: Easing.OutQuad }
                NumberAnimation { target: rig; property: "sx"; to: 0.9;  duration: 140; easing.type: Easing.InOutQuad }
                NumberAnimation { target: rig; property: "sx"; to: 1.0;  duration: 360; easing.type: Easing.OutElastic }
            }
        }

        // single cel layer — hard cut on each frame advance, no cross-dissolve
        Image {
            id: cel
            anchors.fill: parent
            smooth: true; cache: true; fillMode: Image.Stretch
            source: root._src(root.frame)
            sourceClipRect: root._clip(root.frame)
        }
    }
}
