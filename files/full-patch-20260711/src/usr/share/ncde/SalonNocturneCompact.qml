// SalonNocturneCompact.qml — Mucha rose-window music section.
// Drops into DesktopWidget.qml (or any QML host) as a section.
// Transparent background — NCDEGlassSurface behind it shows through.
// Pure Canvas 2D + theme.* tokens + ncde.* color tokens. TapHandler only.
//
// Bindings (read):
//   widget_data.mediaTitle / mediaArtist / mediaAlbum  — QString
//   widget_data.mediaPlaying / mediaActive             — bool
//   widget_data.mediaPosition / mediaDuration          — qint64 (ms)
//   signal widget_data.mediaChanged
//
// Calls (write):
//   widget_data.mediaPrev() / mediaNext() / mediaTogglePlay()
//   widget_data.mediaSeek(qint64 ms)
//
// Interactions:
//   tap the centre disc           → mediaTogglePlay()
//   tap anywhere on the outer arc → mediaSeek to that angle
//   tap a transport jewel         → mediaPrev / mediaTogglePlay / mediaNext

import QtQuick
import Qt.labs.animation
import "mucha-salon.js" as Salon

Item {
    id: salon
    width:  parent ? parent.width : 316
    height: 248
    visible: widget_data.mediaActive

    // ── Animation state ────────────────────────────────────────
    property real bloomEnv:     0.10  // 0..1 audio-reactive envelope
    property real discRotation: 0
    property real elapsedT:     0
    property var  lastPosition: 0
    // Smoothly-interpolated playback position (ms). widget_data.mediaPosition
    // only updates in ~1s D-Bus steps; advance locally per frame, resync on
    // mediaChanged so a long podcast's ring creeps continuously, not in jumps.
    property real interpPosition: 0
    readonly property bool motionEnabled: animPolicy.decorative && !animPolicy.screenIdle
    readonly property real motionDurationScale: animPolicy.thermalPressure || animPolicy.lowPower ? 2.0 : 1.0

    property var _widgetStyle: null
    Component.onCompleted: {
        _widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("salon") : null
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            salon._widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("salon") : null
        }
    }

    // Rose geometry
    readonly property real roseCX:    width / 2
    readonly property real roseCY:    92
    readonly property real outerR:    80
    readonly property real scrubberR: 88
    readonly property real discR:     28

    // Slow breath when paused
    SequentialAnimation on bloomEnv {
        id: breathAnim
        loops: Animation.Infinite
        running: !widget_data.mediaPlaying && salon.visible && animPolicy.decorative
                 && animPolicy.idleLoops && !animPolicy.screenIdle
        NumberAnimation { to: 0.22; duration: 2400; easing.type: Easing.InOutSine }
        NumberAnimation { to: 0.06; duration: 2600; easing.type: Easing.InOutSine }
    }

    // Bloom pulse on every position tick
    NumberAnimation {
        id: bloomTick
        target: salon
        property: "bloomEnv"
        from: 0.85
        to: 0.25
        duration: 1400 * salon.motionDurationScale
        easing.type: Easing.OutCubic
    }

    Connections {
        target: widget_data
        function onMediaChanged() {
            salon.interpPosition = widget_data.mediaPosition
            if (widget_data.mediaPlaying && widget_data.mediaPosition !== salon.lastPosition) {
                breathAnim.stop()
                if (salon.motionEnabled)
                    bloomTick.restart()
                else
                    salon.bloomEnv = 0.25
                salon.lastPosition = widget_data.mediaPosition
            }
        }
        // Silent ground-truth correction (once per second, from Lelan.refreshMediaPosition —
        // most MPRIS players including Spotify never push Position during normal playback, so
        // without this the +33ms/tick local interpolation below just free-runs and drifts).
        // Deliberately does NOT touch lastPosition/bloomTick — that pulse is reserved for real
        // state changes (track start, explicit seek), not a once-a-second drift correction.
        function onMediaPositionChanged() {
            salon.interpPosition = widget_data.mediaPosition
        }
    }

    // Disc spin when playing
    NumberAnimation on discRotation {
        from: 0; to: 360
        duration: 6000 * salon.motionDurationScale
        loops: Animation.Infinite
        running: widget_data.mediaPlaying && salon.visible && animPolicy.decorative
                 && !animPolicy.screenIdle && !animPolicy.desktopObscured
    }

    // Canvas updates share the render loop; Lelan gates motion and lowers the paint rate.
    FrameAnimation {
        id: salonPump
        running: salon.visible && animPolicy.decorative && !animPolicy.screenIdle
                 && !animPolicy.desktopObscured
                 && (widget_data.mediaPlaying || animPolicy.idleLoops)
        property real paintElapsed: 0
        onRunningChanged: if (!running) paintElapsed = 0
        onTriggered: {
            paintElapsed += frameTime
            var paintInterval = (animPolicy.thermalPressure || animPolicy.lowPower) ? 0.066 : 0.033
            if (paintElapsed < paintInterval) return
            var dt = paintElapsed
            paintElapsed = 0
            salon.elapsedT += dt
            if (widget_data.mediaPlaying && widget_data.mediaDuration > 0) {
                salon.interpPosition = Math.min(salon.interpPosition + dt * 1000,
                                                widget_data.mediaDuration)
            }
            roseCanvas.requestPaint()
        }
    }

    Canvas {
        id: roseCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var ws      = salon._widgetStyle
            var accent  = (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent
            var glow    = (ws && ws["glow"]    !== "" && ws["glow"]    !== undefined) ? Qt.color(ws["glow"])    : ncde.glow
            var leading = (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()

            Salon.paintRoseFrame(ctx, salon.roseCX, salon.roseCY,
                                 salon.outerR, accent, glow, leading)

            var frac = widget_data.mediaDuration > 0
                       ? salon.interpPosition / widget_data.mediaDuration
                       : 0
            Salon.paintScrubberArc(ctx, salon.roseCX, salon.roseCY,
                                   salon.scrubberR, frac, accent, glow, leading)

            // spinning leaded-glass record platter behind the petals
            Salon.paintRecordRing(ctx, salon.roseCX, salon.roseCY,
                                  salon.discR, salon.outerR - 2,
                                  salon.discRotation, accent, glow, leading)

            Salon.paintPetals(ctx, salon.roseCX, salon.roseCY,
                              salon.discR + 4, salon.outerR - 6,
                              salon.elapsedT, salon.bloomEnv, accent, glow, leading)

            Salon.paintDisc(ctx, salon.roseCX, salon.roseCY,
                            salon.discR, salon.discRotation, accent, leading)

            // lily-trumpet tonearm — tracks playback, sweeps inward as frac grows
            Salon.paintTonearm(ctx, salon.roseCX, salon.roseCY,
                               salon.discR, salon.outerR - 2,
                               frac, widget_data.mediaPlaying, accent, glow, leading)
        }
    }

    // Centre disc tap = play/pause · outer arc tap = seek
    TapHandler {
        onTapped: function(eventPoint) {
            var dx = eventPoint.position.x - salon.roseCX
            var dy = eventPoint.position.y - salon.roseCY
            var d = Math.sqrt(dx*dx + dy*dy)
            if (d <= salon.discR + 4) {
                widget_data.mediaTogglePlay()
            } else if (d >= salon.scrubberR - 6 && d <= salon.scrubberR + 6) {
                var angle = Math.atan2(dy, dx) + Math.PI / 2
                if (angle < 0) angle += Math.PI * 2
                var frac = angle / (Math.PI * 2)
                if (widget_data.mediaDuration > 0) {
                    salon.interpPosition = frac * widget_data.mediaDuration
                    widget_data.mediaSeek(Math.round(frac * widget_data.mediaDuration))
                }
            }
        }
    }

    // ── Track title + artist · album ───────────────────────────
    Column {
        id: textCol
        anchors.top: parent.top
        anchors.topMargin: 188
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 24
        spacing: 1

        Text {
            text: widget_data.mediaTitle !== "" ? widget_data.mediaTitle : "— Nothing Playing —"
            font.family: {
                var ws = salon._widgetStyle
                return (ws && ws["font"] !== "" && ws["font"] !== undefined) ? ws["font"] : theme.fontFamily
            }
            font.italic: true
            font.pixelSize: theme.fontMedium
            color: {
                var ws = salon._widgetStyle
                if (ws && ws["fill"] !== "" && ws["fill"] !== undefined) return Qt.color(ws["fill"])
                return ncde.gilt4
            }
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            width: parent.width
        }
        Text {
            text: {
                var parts = []
                if (widget_data.mediaArtist !== "") parts.push(widget_data.mediaArtist)
                if (widget_data.mediaAlbum  !== "") parts.push(widget_data.mediaAlbum)
                return parts.join("  ·  ")
            }
            font.family: {
                var ws = salon._widgetStyle
                return (ws && ws["font"] !== "" && ws["font"] !== undefined) ? ws["font"] : theme.fontFamily
            }
            font.capitalization: Font.AllUppercase
            font.letterSpacing: theme.letterSpacing
            font.pixelSize: theme.fontSmall
            color: {
                var ws = salon._widgetStyle
                if (ws && ws["fill"] !== "" && ws["fill"] !== undefined) {
                    var c = Qt.color(ws["fill"])
                    return Qt.rgba(c.r, c.g, c.b, 0.65)
                }
                return Qt.rgba(ncde.gilt4.r, ncde.gilt4.g, ncde.gilt4.b, 0.65)
            }
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            width: parent.width
        }
    }

    // ── Transport row: prev / play-pause / next ────────────────
    Row {
        anchors.top: textCol.bottom
        anchors.topMargin: 6
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 22

        SNJewel { kind: "prev"; onActivated: widget_data.mediaPrev() }
        SNJewel { kind: widget_data.mediaPlaying ? "pause" : "play"
                  jewelR: 14
                  onActivated: widget_data.mediaTogglePlay() }
        SNJewel { kind: "next"; onActivated: widget_data.mediaNext() }
    }

    // ── Single transport jewel (hover glow + TapHandler) ───────
    component SNJewel: Item {
        id: jewel
        property string kind: "play"
        property real   jewelR: 11
        property bool   jewelHover: false
        signal activated()

        width:  jewelR * 2 + 10
        height: jewelR * 2 + 10

        onJewelHoverChanged: jewelCanvas.requestPaint()
        onKindChanged:       jewelCanvas.requestPaint()

        HoverHandler { onHoveredChanged: jewel.jewelHover = hovered }
        TapHandler   { onTapped:         jewel.activated() }

        Canvas {
            id: jewelCanvas
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                var ws = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("salon") : null
                var jAccent  = (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent
                var jLeading = (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()
                Salon.paintJewel(ctx, width / 2, height / 2,
                                 jewel.jewelR, jewel.kind, jewel.jewelHover,
                                 jAccent, jLeading)
            }
            Component.onCompleted: requestPaint()
            Connections {
                target: ncde
                function onThemeChanged() { jewelCanvas.requestPaint() }
            }
        }
    }
}
