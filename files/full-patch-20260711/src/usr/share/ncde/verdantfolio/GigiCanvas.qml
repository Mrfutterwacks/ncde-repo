// GigiCanvas.qml — GiGi, VerdantFolio's host (a white peacock in a pink fur
// pillbox hat and muff), native cel player. 2026-09-29, operator: "animate as
// smooth as Binnie but for GiGi".
//
// Same player as BinnieCanvas.qml, on purpose:
//  - ONE Image layer, hard cut between drawn cels (sourceClipRect into 4-cel
//    strips). No cross-dissolve — blending distinct poses reads as ghost limbs.
//  - Self-rescheduling single-shot Timer with a per-cel hold in ms, every
//    interval passed through safeInterval() (≤0 / NaN / bad state → 200 ms),
//    so the frame clock can never spin the GUI thread.
//  - Idle ping-pongs its 4 breathing cels; actions play once, then fall back
//    into idle. Every action's last cel is the idle neutral pose, byte-for-byte,
//    so the return is seamless.
//  - frame is reset BEFORE cur changes in play() (see BinnieCanvas for why).
//
// Art: gigi/<sheet>.png, 4 cels of celW×celH each, cropped from the delivered
// 1024² cels to their common bounding box, so her feet sit on one baseline.
//
//   GigiCanvas { id: gigi }
//   gigi.play("fan")    // polish display   gigi.play("tilt")  // found a slip
//   gigi.play("cheer")  // all clear         gigi.say()         // talk if resting
import QtQuick

Item {
    id: root
    property string assetBase: Qt.resolvedUrl("gigi/")
    implicitWidth: 180
    implicitHeight: Math.round(180 * celH / celW)

    readonly property int celW: 402
    readonly property int celH: 463
    property real speed: 1.0          // global timing multiplier (>1 = slower)

    // state → ordered strips (4 cels each) + per-cel hold in MILLISECONDS.
    // INVARIANT: timing.length === 4 × sheets.length.
    readonly property var defs: ({
        "idle":  { "sheets": ["idle"],
                   "timing": [1400, 1000, 1400, 1000] },
        "talk":  { "sheets": ["talk_a", "talk_b"],
                   "timing": [140, 110, 130, 170, 150, 110, 150, 240] },
        "fan":   { "sheets": ["fan_a", "fan_b", "fan_c"],
                   "timing": [260, 140, 120, 150, 260, 160, 160, 220, 150, 140, 220, 320] },
        "tilt":  { "sheets": ["tilt_a", "tilt_b"],
                   "timing": [180, 220, 280, 520, 200, 260, 340, 260] },
        "cheer": { "sheets": ["cheer"],
                   "timing": [200, 180, 240, 460] }
    })

    property string cur: "idle"
    property int    frame: 0
    property int    dir: 1            // idle ping-pong direction
    readonly property bool resting: cur === "idle"

    signal tapped()

    Component.onCompleted: play("idle")

    function _src(f)  { var c = defs[cur]; return assetBase + c.sheets[Math.floor(f / 4)] + ".png"; }
    function _clip(f) { return Qt.rect((f % 4) * celW, 0, celW, celH); }

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
        frame = 0;                    // before cur — keeps every binding in-bounds
        dir = 1;
        cur = name;
        clock.interval = safeInterval(name, 0); clock.start();
    }
    // chatter only when she isn't already mid-gesture (a fan or tilt wins)
    function say() { if (resting) play("talk"); }

    Timer {
        id: clock
        repeat: false
        onTriggered: {
            var cfg = root.defs[root.cur];
            if (!cfg) { root.cur = "idle"; root.frame = 0; return; }
            var nFrames = cfg.timing.length;
            var incoming;
            if (root.cur === "idle") {
                incoming = root.frame + root.dir;
                if (incoming >= nFrames) { root.dir = -1; incoming = nFrames - 2; }
                else if (incoming < 0)   { root.dir = 1;  incoming = 1; }
            } else {
                incoming = (root.frame + 1) % nFrames;
                if (incoming === 0) { root.play("idle"); return; }
            }
            root.frame = incoming;
            if (root.cur === "cheer" && root.frame === 2) impact.restart();   // lands from the hop
            interval = root.safeInterval(root.cur, root.frame); start();
        }
    }

    // ── scale-to-fit + feet-anchored landing squash ─────────────────────
    Item {
        id: rig
        width: root.celW; height: root.celH
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        scale: Math.min(root.width / root.celW, root.height / root.celH)
        transformOrigin: Item.Bottom

        property real sx: 1.0
        property real sy: 1.0
        transform: Scale { origin.x: rig.width / 2; origin.y: rig.height; xScale: rig.sx; yScale: rig.sy }
        ParallelAnimation {
            id: impact
            SequentialAnimation {
                NumberAnimation { target: rig; property: "sy"; from: 1.0; to: 0.9;  duration: 70;  easing.type: Easing.OutQuad }
                NumberAnimation { target: rig; property: "sy"; to: 1.05; duration: 120; easing.type: Easing.InOutQuad }
                NumberAnimation { target: rig; property: "sy"; to: 1.0;  duration: 320; easing.type: Easing.OutElastic }
            }
            SequentialAnimation {
                NumberAnimation { target: rig; property: "sx"; from: 1.0; to: 1.08; duration: 70;  easing.type: Easing.OutQuad }
                NumberAnimation { target: rig; property: "sx"; to: 0.97; duration: 120; easing.type: Easing.InOutQuad }
                NumberAnimation { target: rig; property: "sx"; to: 1.0;  duration: 320; easing.type: Easing.OutElastic }
            }
        }

        Image {
            id: cel
            anchors.fill: parent
            smooth: true; mipmap: true; cache: true; fillMode: Image.Stretch
            source: root._src(root.frame)
            sourceClipRect: root._clip(root.frame)
        }
    }

    // poke her and she shows off
    TapHandler { onTapped: { root.tapped(); root.play("fan"); } }
    HoverHandler { cursorShape: Qt.PointingHandCursor }
}
