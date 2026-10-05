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

import QtQuick
import Qt.labs.animation
import "mucha-space.js" as Space

Item {
    id: space
    width:  parent ? parent.width : 316
    height: 260

    property bool showBorder: true
    property bool showBanner: true
    property string bannerText: "Athelian Engine"

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
    }

    Component.onCompleted: {
        updateAstro()
        spaceSkyCanvas.requestPaint()
        spaceCanvas.requestPaint()
        spaceBorderCanvas.requestPaint()
    }

    Connections {
        target: typeof lelan !== "undefined" && lelan !== null ? lelan : null
        ignoreUnknownSignals: true
        function onClockChanged() { space.updateAstro(); spaceSkyCanvas.requestPaint() }
    }

    Connections {
        target: widget_data
        function onMoonPositionChanged() { space.updateAstro(); spaceSkyCanvas.requestPaint() }
        function onWeatherChanged()      { space.updateAstro(); spaceSkyCanvas.requestPaint() }
    }

    // Vsync-tied animation pump — advances rotations + repaints.
    // NOT space.visible — child Item visibility is unreliable inside NCDE's
    // bottom-desktop Window. Paused on screen idle (screenIdle) because Qt
    // FrameAnimation does NOT auto-idle; it fires every vsync unconditionally.
    FrameAnimation {
        id: spacePump
        running: animPolicy.decorative && !animPolicy.screenIdle && !animPolicy.desktopObscured
        property int _skip: 0
        onTriggered: {
            var dt = spacePump.frameTime
            space.elapsedT  += dt
            space.earthRot   = (space.earthRot  + 3.0  * dt) % 360
            space.cloudRot   = (space.cloudRot  - 2.0  * dt) % 360
            space.zodiacRot  = (space.zodiacRot + 0.35 * dt) % 360
            if (animPolicy.thermalPressure || animPolicy.lowPower) { if (_skip++ % 2 !== 0) return } else _skip = 0
            spaceCanvas.requestPaint()
        }
    }

    // Static background layer (2026-07-14 perf split, matches SpacePanel.qml):
    // sky only changes with brightness (once/minute) or theme, never per-frame.
    Canvas {
        id: spaceSkyCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Threaded
        renderTarget: Canvas.Image
        onPaint: {
            var ctx = getContext("2d")
            Space.paintSky(ctx, width, height, space.brightness, ncde.accent, ncde.glow)
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
                fontFamily:  theme.fontFamily
            }, ncde.accent, ncde.glow)
        }
    }

    // Static foreground layer: the arch border never changes at all.
    Canvas {
        id: spaceBorderCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Threaded
        renderTarget: Canvas.Image
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            if (!space.showBorder) return
            Space.paintArchBorder(ctx, width, height, ncde.accent, ncde.glow)
        }
    }
}
