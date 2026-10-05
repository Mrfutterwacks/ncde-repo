import QtQuick
import Qt.labs.animation
import "mucha-space.js" as Space
import "mucha-weather-window.js" as WxWin

Item {
    id: root
    // no clip here: it cut the glass glow + shadow off at a square box (2026-09-24)
    property Item backgroundSource: null
    property var _surfaceGlass: null
    // Weather window (2026-09-24): the real weather outside, from WeatherLive.sky
    // (DesktopWidget passes the Weather card's). "clear" = the orrery exactly as before.
    property var sky: null
    readonly property bool weatherOn: !!sky && !!sky.kind && sky.kind !== "clear"
    onSkyChanged: spaceWeatherCanvas.requestPaint()
    // ── the season outside (2026-09-26, operator: "falling leaves for autumn?
    // seasonal … spring and summer blossoms, fall, etc") — by the machine's own
    // latitude (WeatherLive: pin / learned place / geolocation / geoclue / IP), so
    // every install gets its own hemisphere. Spring: blossom petals; summer:
    // dandelion seeds by day, fireflies by night; autumn: stained-glass leaves;
    // winter: diamond dust (ice crystals glinting — real on cold dry days); real
    // snow shows only when it really snows. They drift
    // in clear, cloudy, foggy or rainy weather; snow, sleet, hail and storms keep
    // the window to themselves.
    property real latitude: 40
    onLatitudeChanged: space.updateAstro()
    readonly property string driftKind:
        (sky && sky.kind && ["clear", "cloudy", "fog", "rain"].indexOf(sky.kind) < 0) ? ""
        : space.season === "autumn" ? "leaf"
        : space.season === "spring" ? "petal"
        : space.season === "summer" ? (space.brightness < 0.35 ? "firefly" : "seed")
        : space.season === "winter" ? "crystal"
        : ""
    readonly property bool leavesOn: driftKind !== ""
    onDriftKindChanged: if (leavesOn) space.repaintNight()
    Component.onCompleted: {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("space") : null
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            root._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("space") : null
        }
    }
    width: parent ? parent.width : 316
    // Script Shift (2026-09-24): the one text-size factor, read the same way LaPivot's
    // Theme does (fontSizeScale x uiScale; uiScale is retired and stays 1). The card
    // grows to fit its text; nothing else about it scales.
    readonly property real ts: (typeof settings !== "undefined" && settings.fontSizeScale > 0 ? settings.fontSizeScale : 1)
                             * (typeof settings !== "undefined" && settings.uiScale > 0 ? settings.uiScale : 1)
    // only the banner ribbon (22*ts) grows; mucha-space.js keeps the orrery its old size
    height: Math.round(300 + 22 * (ts - 1))
    NCDEGlass2 {   // Mucha glass: full NCDEGlassSurface layers + palette-driven ornamental frame
        cornerRadius: 14
        anchors {
            fill: parent
            leftMargin: 4; rightMargin: 4
            topMargin: 2; bottomMargin: 2
        }
        backgroundSource: root.backgroundSource
        revealPulse: intellihide.widgetRevealed
        glintPulse: intellihide.glintPulse
        // Iris Chroma baseline + Filigree override — resolved inside NCDEGlassSurface.
        surfaceKey: "space"
        glass: root._surfaceGlass
    }
    // SpaceWidget2.qml — Mucha orrery space scene for NCDE.
    // Replaces the old SpaceWidget. Earth globe centred in a turning zodiac
    // orrery ring; sun & moon ride the ring on armatures by real time/phase;
    // twinkling stars, drifting clouds, aurora, shooting stars; Mucha arch
    // border + location/date banner. Pure Canvas 2D via mucha-space.js.
    //
    // Bindings (read, all on widget_data):
    //   weatherLocation, weatherSunrise, weatherSunset,
    //   moonAzimuth, moonElevation   (used when valid, else phase fallback)
    //   signals weatherChanged / moonPositionChanged
    //
    // No C++ changes. No PNG/SVG.
    Item {
        id: space
        clip: true   // content clips here instead of at root, so the glass keeps its rounded glow
        // 2026-09-24: inset INSIDE the glass frame. Full-width, the scene's straight
        // sides ran over the frame's edges + corner ornaments and its bottom stopped
        // 18px short of the frame, drawing a second hard line.
        x: 12
        width: parent.width - 24
        // 2026-09-26 (operator: "the orrery frame could move up a little"): 22 → 14,
        // in line with the 12 px sides/bottom and still clear of the corner ornaments
        y: 14
        height: parent.height - y - 12
        z: 1

        property bool showBorder: true
        property bool showBanner: true
        property string bannerText: "Athelian Engine"
        property var _widgetStyle: null

        // ── Animated state passed to the painter ──
        property real elapsedT:   0
        property real earthRot:   0
        property real cloudRot:   0
        property real zodiacRot:  0
        property real sunAngle:   -90
        property real moonAngle:  90
        property real moonPhase:  0.5
        property real brightness: 0.0
        property real starOpacity:1.0
        property int  activeSign:  -1
        property string season:    ""

        // ── Astronomy ──────────────────────────────────────────────
        function zodiacIndex(mo, day) {
            // mo 1..12. Returns 0..11 (Aries..Pisces)
            var cut = [20,19,21,20,21,21,22,23,23,23,22,22]; // last day of prev sign
            var signByMonth = [9,10,11,0,1,2,3,4,5,6,7,8];   // month→sign if before cut, else +1
            var idx = signByMonth[mo-1];
            if (day > cut[mo-1]) idx = (idx + 1) % 12;
            return idx;
        }

        function updateAstro() {
            var now = new Date()
            var f = (now.getHours()*3600 + now.getMinutes()*60 + now.getSeconds()) / 86400  // 0..1 day

            // Sun rides the ring: noon → top (-90°), midnight → bottom (90°)
            sunAngle = -90 + (f - 0.5) * 360

            // Smooth day/night brightness (noon bright, midnight dark)
            brightness  = (1 + Math.cos((f - 0.5) * Math.PI * 2)) / 2
            starOpacity = Math.max(0.15, 1 - brightness * 1.3)

            // Lunar phase (synodic) + moon angle
            var jd = now.getTime() / 86400000 + 2440587.5
            var daysSinceNew = (jd - 2451549.5) % 29.53058867
            if (daysSinceNew < 0) daysSinceNew += 29.53058867
            var phase = daysSinceNew / 29.53058867   // 0 new → 0.5 full → 1 new
            moonPhase = phase

            // Prefer real Horizons azimuth if the backend provides it
            if (widget_data.moonElevation > -89) {
                // Map azimuth (0=N,90=E,180=S,270=W) onto the ring; S=top
                moonAngle = (widget_data.moonAzimuth - 180) - 90
            } else {
                // Full moon sits opposite the sun; new moon near it
                moonAngle = sunAngle + phase * 360
            }

            // Active zodiac sign by date
            activeSign = zodiacIndex(now.getMonth()+1, now.getDate())

            // The season, by hemisphere (month*100 + day, astronomical dates)
            var md = (now.getMonth() + 1) * 100 + now.getDate()
            var n = md >= 320 && md <= 620 ? "spring" : md >= 621 && md <= 921 ? "summer"
                  : md >= 922 && md <= 1220 ? "autumn" : "winter"
            var flip = { spring: "autumn", summer: "winter", autumn: "spring", winter: "summer" }
            season = root.latitude >= 0 ? n : flip[n]
        }

        // Shared by all three Canvas layers below so the color logic exists
        // in exactly one place instead of three copies.
        function resolveColors() {
            var ws = space._widgetStyle
            return {
                accent:  (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent,
                glow:    (ws && ws["glow"]    !== "" && ws["glow"]    !== undefined) ? Qt.color(ws["glow"])    : ncde.glow,
                leading: (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()
            }
        }

        // wallpaper ink: text + lit digits are painted, so repaint when it changes
        Connections { target: theme; function onInkSerialChanged() { space.repaintAll() } }
        function repaintAll() {
            spaceSkyCanvas.requestPaint(); spaceCanvas.requestPaint(); earthCanvas.requestPaint()
            spaceBorderCanvas.requestPaint(); space.repaintNight()
        }
        // the paint-once night sky: star groups + aurora ribbons (+ the meteor)
        function repaintNight() {
            for (var i = 0; i < starGroups.count; i++) starGroups.itemAt(i).requestPaint()
            for (var j = 0; j < auroraBands.count; j++) auroraBands.itemAt(j).requestPaint()
            for (var k = 0; k < leaves.count; k++) leaves.itemAt(k).children[0].children[0].requestPaint()
        }
        Component.onCompleted: {
            _widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("space") : null
            updateAstro()
            space.repaintAll()
        }

        // the sky follows the time of day on LELAN's minute tick (clockChanged),
        // not a timer of its own (anim-policy.md §4.4)
        Connections {
            target: typeof lelan !== "undefined" ? lelan : null
            ignoreUnknownSignals: true
            function onClockChanged() {
                var so = space.starOpacity
                space.updateAstro()
                spaceSkyCanvas.requestPaint()  // brightness may have just changed
                if (Math.abs(space.starOpacity - so) > 0.004) space.repaintNight()   // stars fade with the day
            }
        }

        Connections {
            target: widget_data
            function onMoonPositionChanged() { space.updateAstro(); spaceSkyCanvas.requestPaint() }
            function onWeatherChanged()      { space.updateAstro(); spaceSkyCanvas.requestPaint() }
        }
        Connections {
            target: ncde
            function onThemeChanged() {
                space._widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("space") : null
                space.repaintAll()
            }
        }

        // ── Motion, the Evas/Moksha way, governed by Lelan (2026-09-26) ──
        // Operator: "these should always animate … look how moksha does it";
        // "it should not run its own clocks at all — Lelan is for all that".
        // anim-policy.md §1: the frames come from Qt's render loop (vsync), never a
        // widget timer; Lelan's level (animPolicy) decides what runs and how richly.
        // Paint the art once, move the painted image: the night sky (stars, aurora,
        // shooting star) is painted ONCE and twinkles / flows / flies by render-thread
        // Animators. The globe and the ring move < 1 px per frame (Earth 3°/s, ring
        // 0.35°/s), so they repaint on every 8th / 30th render-loop frame (every 16th /
        // 60th when Lelan reports heat or low power) — positions from the clock, so
        // the motion is exactly as fast as before. Asleep or hidden desktop → paused
        // (nobody sees it); Reduce Motion → still. The weather window keeps its pump,
        // only while there is weather. Measured on this laptop's GPU: 67% → 12% of a core.
        readonly property bool _awake: !animPolicy.screenIdle && !animPolicy.desktopObscured
        readonly property bool _moving: _awake && animPolicy.decorative
        readonly property bool _easy: animPolicy.thermalPressure || animPolicy.lowPower
        property real _t0: Date.now()
        property int _tick: 0
        function _clock() {
            var s = (Date.now() - space._t0) / 1000
            space.elapsedT  = s
            space.earthRot  = (3.0  * s) % 360
            space.cloudRot  = -((2.0 * s) % 360)
            space.zodiacRot = (0.35 * s) % 360
        }
        FrameAnimation {                         // the render loop's frames, not a clock of our own
            running: space._moving
            onTriggered: {
                var k = ++space._tick
                var e = space._easy ? 16 : 8, r = space._easy ? 60 : 30      // ~4/8 Hz globe, 1/2 Hz ring at 60 Hz
                if (k % e === 0) { space._clock(); earthCanvas.requestPaint() }
                if (k % r === 0) { space._clock(); spaceCanvas.requestPaint() }
            }
        }
        FrameAnimation {                         // weather window only (rain, snow…)
            id: spacePump
            running: space._awake && root.weatherOn
            property int _skip: 0
            onTriggered: {
                space.elapsedT = (Date.now() - space._t0) / 1000
                if (space._easy) { if (_skip++ % 4 !== 0) return } else if (_skip++ % 2 !== 0) return
                spaceWeatherCanvas.requestPaint()
            }
        }

        // Static background layer (2026-07-14 perf split): sky only actually
        // changes with `brightness` (once/minute) or theme — repainted from
        // those triggers above, never from the per-frame animation pump.
        // Confirmed live: this + the border split dropped LaPivot off a
        // sustained ~55% CPU floor with zero change to what's on screen.
        Canvas {
            id: spaceSkyCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            onPaint: {
                var ctx = getContext("2d")
                var c = space.resolveColors()
                Space.paintSky(ctx, width, height, space.brightness, c.accent, c.glow)
            }
        }

        // ── the night sky, painted once ──
        // four twinkle groups of the same 90 stars, each fading on its own rhythm
        Repeater {
            id: starGroups
            model: 4
            Canvas {
                required property int index
                anchors.fill: parent
                renderStrategy: Canvas.Threaded
                renderTarget: Canvas.Image
                onPaint: Space.paintStarGroup(getContext("2d"), width, height, space.starOpacity, index, 4)
                opacity: 0.62
                SequentialAnimation on opacity {
                    running: space._moving
                    loops: Animation.Infinite
                    OpacityAnimator { from: 0.25; to: 1.0; duration: [1600, 2300, 3200, 4400][index]; easing.type: Easing.InOutSine }
                    OpacityAnimator { from: 1.0; to: 0.25; duration: [1600, 2300, 3200, 4400][index]; easing.type: Easing.InOutSine }
                }
            }
        }
        // three aurora ribbons, each a seamless strip sliding west and breathing
        Repeater {
            id: auroraBands
            model: 3
            Canvas {
                required property int index
                width: space.width * 2 + 12; height: space.height
                renderStrategy: Canvas.Threaded
                renderTarget: Canvas.Image
                onPaint: { var c = space.resolveColors(); Space.paintAuroraBand(getContext("2d"), space.width, height, index, c.accent, c.glow) }
                XAnimator on x {
                    running: space._moving
                    loops: Animation.Infinite
                    from: 0; to: -space.width
                    duration: Math.round(1000 * space.width / (20 + index * 7.5))
                }
                opacity: 0.71
                SequentialAnimation on opacity {
                    running: space._moving
                    loops: Animation.Infinite
                    OpacityAnimator { from: 0.43; to: 1.0; duration: 6280 + index * 700; easing.type: Easing.InOutSine }
                    OpacityAnimator { from: 1.0; to: 0.43; duration: 6280 + index * 700; easing.type: Easing.InOutSine }
                }
            }
        }
        // the shooting star: one every ~9 s, streaking over 0.8 s
        Canvas {
            id: meteor
            width: 64; height: 6
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            transformOrigin: Item.Right
            opacity: 0
            property int _beat: 0
            onPaint: Space.paintMeteor(getContext("2d"), 60, height)
            ParallelAnimation {                   // 0.8 s every 9 s — the only full-rate motion
                id: meteorFlight
                XAnimator { id: mx; target: meteor; duration: 800 }
                YAnimator { id: my; target: meteor; duration: 800 }
                OpacityAnimator { target: meteor; from: 1; to: 0; duration: 800 }
            }
            // one every ~9 s on LELAN's 1 Hz pulse, not a timer of its own
            Connections {
                target: (typeof lelan !== "undefined" && space._moving) ? lelan : null
                ignoreUnknownSignals: true
                function onPulse() {
                    if (++meteor._beat % 9 !== 0) return
                    var w = space.width, h = space.height
                    var sx = Math.random() * w * 0.6, sy = Math.random() * h * 0.4
                    var ang = Math.PI * (0.15 + Math.random() * 0.15)
                    meteor.rotation = ang * 180 / Math.PI
                    mx.from = sx - meteor.width; mx.to = sx + Math.cos(ang) * w * 0.5 - meteor.width
                    my.from = sy - meteor.height / 2; my.to = sy + Math.sin(ang) * w * 0.5 - meteor.height / 2
                    meteorFlight.restart()
                }
            }
        }

        Canvas {
            id: spaceCanvas
            anchors.fill: parent
            // Threaded = full double-buffered repaint per frame. Cooperative
            // renders incrementally on the GUI thread and ghosts/stalls under
            // a fast repaint loop (the "duplicating + no animation" bug).
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            onPaint: {
                var ctx = getContext("2d")
                var c = space.resolveColors()
                Space.drawMuchaSpace(ctx, width, height, {
                    t:           space.elapsedT,
                    brightness:  space.brightness,
                    starOpacity: space.starOpacity,
                    earthRot:    space.earthRot,
                    cloudRot:    space.cloudRot,
                    zodiacRot:   space.zodiacRot,
                    sunAngle:    space.sunAngle,
                    moonAngle:   space.moonAngle,
                    moonPhase:   space.moonPhase,
                    activeSign:  space.activeSign,
                    bannerText:  space.bannerText,
                    showBanner:  space.showBanner,
                    fontFamily:  theme.fontFamily,
                    textScale:   root.ts,
                    verd:        ncde.verd,     // Earth's land glass (2026-09-25)
                    gilt3:       ncde.gilt3     // Earth's desert glass
                }, c.accent, c.glow, c.leading, "ring")
            }
        }

        // the globe on its own layer (above the ring's armatures, as before)
        Canvas {
            id: earthCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            onPaint: {
                var c = space.resolveColors()
                Space.drawMuchaSpace(getContext("2d"), width, height, {
                    earthRot: space.earthRot, cloudRot: space.cloudRot, sunAngle: space.sunAngle,
                    showBanner: space.showBanner, textScale: root.ts,
                    verd: ncde.verd, gilt3: ncde.gilt3
                }, c.accent, c.glow, c.leading, "earth")
            }
        }

        // Weather window: between the orrery and the arch border, so the weather is
        // outside the window and the frame stays in front. Paints nothing (and is never
        // asked to) while the sky is clear.
        Canvas {
            id: spaceWeatherCanvas
            anchors.fill: parent
            visible: root.weatherOn
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            onPaint: {
                var ctx = getContext("2d")
                var c = space.resolveColors()
                WxWin.paintWeather(ctx, width, height, space.elapsedT, root.sky, space.brightness, c.accent, c.glow)
            }
        }

        // Autumn leaves: six stained-glass leaves, each painted ONCE, falling on
        // render-thread Animators (drift + fall, a side-to-side rock, a tilt) —
        // pushed by the real wind. A new fall is planned on the GUI thread once
        // per leaf per ~12 s; nothing repaints.
        Repeater {
            id: leaves
            model: 6
            Item {
                id: lf
                required property int index
                width: 26; height: 26
                readonly property bool go: space._moving && root.leavesOn && space.width > 0
                visible: go
                property real x0: 0; property real x1: 0; property real y0: -24; property real y1: 0; property int dur: 12000
                function launch(first) {
                    var w = space.width, h = space.height
                    var k = root.driftKind
                    if (k === "firefly") {                               // wander + rise a little
                        x0 = Math.random() * (w - 20); x1 = x0 + (Math.random() - 0.5) * 60
                        y0 = h * (0.35 + Math.random() * 0.5); y1 = y0 - 20 - Math.random() * 30
                        dur = 5000 + Math.random() * 4000
                        fall.restart(); return
                    }
                    var lift = k === "seed" || k === "crystal" ? 1.6 : k === "petal" ? 1.2 : 1.0   // light things ride the wind
                    var drift = (WxWin.slantOf(root.sky) * h * 0.8 + (Math.random() - 0.5) * 50) * lift
                    x0 = Math.random() * (w + 40) - 20 - drift * 0.5
                    x1 = x0 + drift
                    var full = (k === "seed" || k === "crystal") ? 18000 + Math.random() * 6000
                             : k === "petal" ? 12000 + Math.random() * 5000 : 9000 + Math.random() * 6000
                    y0 = first ? Math.random() * h * 0.7 : -24          // the first fall starts mid-air
                    y1 = h + 4
                    dur = Math.round(full * (y1 - y0) / (h + 28))
                    fall.restart()
                }
                onGoChanged: if (go) launch(true); else fall.stop()
                readonly property string kind: root.driftKind
                onKindChanged: if (go) { leafArt.requestPaint(); launch(true) }
                Component.onCompleted: if (go) launch(true)
                ParallelAnimation {
                    id: fall
                    YAnimator { target: lf; from: lf.y0; to: lf.y1; duration: lf.dur }
                    XAnimator { target: lf; from: lf.x0; to: lf.x1; duration: lf.dur }
                    onFinished: if (lf.go) lf.launch(false)
                }
                Item {
                    id: rock
                    width: lf.width; height: lf.height
                    readonly property int swing: 1300 + lf.index * 170
                    SequentialAnimation {
                        running: lf.go; loops: Animation.Infinite
                        XAnimator { target: rock; from: -9; to: 9; duration: rock.swing; easing.type: Easing.InOutSine }
                        XAnimator { target: rock; from: 9; to: -9; duration: rock.swing; easing.type: Easing.InOutSine }
                    }
                    Canvas {
                        id: leafArt
                        anchors.fill: parent
                        renderStrategy: Canvas.Threaded
                        renderTarget: Canvas.Image
                        onPaint: { var c = space.resolveColors(); WxWin.paintDrift(getContext("2d"), width, lf.kind, lf.index, c.accent, c.leading) }
                        SequentialAnimation {           // a firefly glows and fades; a crystal glints
                            running: lf.go && (lf.kind === "firefly" || lf.kind === "crystal"); loops: Animation.Infinite
                            OpacityAnimator { target: leafArt; from: 0.15; to: 1.0; duration: 900 + lf.index * 130; easing.type: Easing.InOutSine }
                            PauseAnimation { duration: 400 }
                            OpacityAnimator { target: leafArt; from: 1.0; to: 0.15; duration: 1400 + lf.index * 170; easing.type: Easing.InOutSine }
                            PauseAnimation { duration: 700 + lf.index * 240 }
                            onRunningChanged: if (!running) leafArt.opacity = 1
                        }
                        SequentialAnimation {           // tilts into each swing, like a falling leaf rocks
                            running: lf.go; loops: Animation.Infinite
                            RotationAnimator { target: leafArt; from: -38 + lf.index * 11; to: 38 + lf.index * 11; duration: rock.swing; easing.type: Easing.InOutSine }
                            RotationAnimator { target: leafArt; from: 38 + lf.index * 11; to: -38 + lf.index * 11; duration: rock.swing; easing.type: Easing.InOutSine }
                        }
                    }
                }
            }
        }

        // Static foreground layer: the arch border never changes at all —
        // same trigger set as the sky layer (theme changes only).
        Canvas {
            id: spaceBorderCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Threaded
            renderTarget: Canvas.Image
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                if (!space.showBorder) return
                var c = space.resolveColors()
                Space.paintArchBorder(ctx, width, height, c.accent, c.glow, c.leading)
            }
        }
    }

    // Brass bezel + glass pane over the whole card (2026-09-24), like the dock
    // icons' bezel + glass cap. On top of everything; takes no input.
    NCDEWidgetPane { anchors.fill: parent; z: 50 }
}
