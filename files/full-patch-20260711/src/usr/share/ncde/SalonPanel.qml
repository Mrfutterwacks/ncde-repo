import QtQuick
import QtQuick.Effects
import "mucha-salon.js" as Salon

Item {
    id: root
    property Item backgroundSource: null
    property var _surfaceGlass: null
    property var _widgetStyle: null
    // La'Ombre d'Opale (idle, nothing playing) and Salon Nocturne (media active) are two states of
    // this ONE widget slot, crossfaded below by widget_data.mediaActive — so the Glass surface itself
    // must follow the same state, not stay pinned to "salon" while La'Ombre is the one actually shown.
    function _refreshSurface() {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass(widget_data.mediaActive ? "salon" : "laombre") : null
        _widgetStyle  = typeof ncde.widgetStyle  === "function" ? ncde.widgetStyle("laombre") : null
    }
    Component.onCompleted: _refreshSurface()
    Connections { target: ncde;        function onThemeChanged()  { root._refreshSurface() } }
    Connections { target: widget_data; function onMediaChanged()  { root._refreshSurface() } }
    width: parent ? parent.width : 316
    // Script Shift (2026-09-24): the card grows by exactly what its two captions
    // grow (theme sizes already follow Script Shift); the art keeps its size.
    readonly property real textGrow: Math.max(0, theme.fontSmall - 11) + Math.max(0, theme.fontMedium - 14)
    height: 284 + textGrow
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
        id: salonGlass
        // Iris Chroma baseline + Filigree override — resolved inside NCDEGlassSurface.
        // La'Ombre (idle) and Salon (media) are two glass keys for this one slot.
        surfaceKey: widget_data.mediaActive ? "salon" : "laombre"
        glass: root._surfaceGlass
        // Widgets tab Frame/Glow colours still win over glass, as before.
        edge: {
            var ws = root._widgetStyle
            if (ws && ws["leading"] !== "" && ws["leading"] !== undefined) { var lc = Qt.color(ws["leading"]); return Qt.rgba(lc.r, lc.g, lc.b, 0.85) }
            return salonGlass.resolvedEdge
        }
        glowRim: {
            var ws = root._widgetStyle
            if (ws && ws["glow"] !== "" && ws["glow"] !== undefined) return Qt.color(ws["glow"])
            return salonGlass.resolvedGlow
        }
        glowHalo: glowRim
    }
    // Idle (2026-09-24): the lone ♪ in bare glass is replaced by the Salon's own
    // instrument at rest — same painters and geometry as SalonNocturneCompact
    // (rose frame, platter, petals closed, parked tonearm), unspun and dimmed, so
    // pressing play reads as the gramophone waking rather than a different widget.
    // Static paint (repaints only on theme change). The breath (below, `breath`)
    // is Opacity/ScaleAnimators on the render thread, per anim-policy.
    // Height is 2*cy so the item's centre IS the rose's centre: scale grows the
    // rose from its heart. Nothing paints below y≈182 (frame r=80 about cy=102).
    Canvas {
        id: restingRose
        width: parent.width
        height: cy * 2
        opacity: 0.45
        z: 0.6          // over its glow (roseGlow, 0.5)
        visible: !widget_data.mediaActive
        readonly property real cx: width / 2
        readonly property real cy: 102          // SalonNocturneCompact topMargin 10 + roseCY 92
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            var ws      = root._widgetStyle
            var accent  = (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent
            var glow    = (ws && ws["glow"]    !== "" && ws["glow"]    !== undefined) ? Qt.color(ws["glow"])    : ncde.glow
            var leading = (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()
            Salon.paintRoseFrame(ctx, cx, cy, 80, accent, glow, leading)
            Salon.paintRecordRing(ctx, cx, cy, 28, 78, 0, accent, glow, leading)
            Salon.paintPetals(ctx, cx, cy, 32, 74, 0, 0, accent, glow, leading)
            Salon.paintDisc(ctx, cx, cy, 28, 0, accent, leading)
            Salon.paintTonearm(ctx, cx, cy, 28, 78, 0, false, accent, glow, leading)
        }
        Connections { target: ncde; function onThemeChanged() { restingRose.requestPaint() } }
        onVisibleChanged: if (visible) requestPaint()
    }
    // The off state glows (2026-09-26, operator: "make Salon Nocturne on the off
    // position glow softly"): a bloom of the palette's glow colour behind the
    // resting rose, made from the rose itself (blurred wide, coloured by the glow),
    // breathing on the same clock — so the sleeping gramophone reads as lit from
    // within instead of merely faded. Sits under the rose; the crisp rose never blurs.
    readonly property color _roseLight: {
        var ws = root._widgetStyle
        var g = (ws && ws["glow"] !== "" && ws["glow"] !== undefined) ? Qt.color(ws["glow"]) : ncde.glow
        return Qt.lighter(Qt.rgba(g.r, g.g, g.b, 1.0), 1.35)    // the glow at full strength (Iris glows are often part-transparent)
    }
    // 1. a soft pool of light behind the rose
    Canvas {
        id: roseLight
        width: 260; height: 260
        x: restingRose.cx - width / 2; y: restingRose.cy - height / 2
        z: 0.5          // above the widget's glass, under the rose (0.6)
        visible: restingRose.visible
        opacity: 0.30
        onPaint: {
            var ctx = getContext("2d"); ctx.clearRect(0, 0, width, height)
            var c = root._roseLight, r = width / 2
            function rgba(a) { return "rgba(" + Math.round(c.r*255) + "," + Math.round(c.g*255) + "," + Math.round(c.b*255) + "," + a + ")" }
            var g = ctx.createRadialGradient(r, r, 0, r, r, r)
            g.addColorStop(0, rgba(0.55)); g.addColorStop(0.55, rgba(0.18)); g.addColorStop(1, rgba(0))
            ctx.fillStyle = g; ctx.fillRect(0, 0, width, height)
        }
        Connections { target: root; function on_RoseLightChanged() { roseLight.requestPaint() } }
    }
    // 2. a tight bloom that makes the rose's own lines luminous
    MultiEffect {
        id: roseGlow
        source: restingRose
        x: restingRose.x; y: restingRose.y
        width: restingRose.width; height: restingRose.height
        z: 0.7          // over the rose: the lines themselves shine
        visible: restingRose.visible
        opacity: 0.30
        autoPaddingEnabled: true
        blurEnabled: true
        blur: 0.6
        blurMax: 10
        brightness: 0.5
        colorization: 0.6
        colorizationColor: root._roseLight
    }
    // One clock for the whole idle state (2026-09-24, operator: "make the off
    // state breathe and the text glow softly"): the rose swells and brightens on
    // the in-breath while both captions' halos rise with it, so it reads as one
    // sleeping instrument, not three pulses drifting apart. All Animators →
    // render thread; the halos are blurred once (static layer), only fade.
    SequentialAnimation {
        id: breath
        loops: Animation.Infinite
        // governed by Lelan (anim-policy.md): still while the screen sleeps or under
        // Reduce Motion, like every other ambient loop (2026-09-26)
        running: !widget_data.mediaActive && root.visible && animPolicy.decorative && !animPolicy.screenIdle
        ParallelAnimation {     // in-breath
            OpacityAnimator { target: restingRose; from: 0.30; to: 0.65; duration: 3800; easing.type: Easing.InOutSine }
            ScaleAnimator   { target: restingRose; from: 0.975; to: 1.025; duration: 3800; easing.type: Easing.InOutSine }
            OpacityAnimator { target: whisperHalo; from: 0.25; to: 1.0; duration: 3800; easing.type: Easing.InOutSine }
            OpacityAnimator { target: titleHalo;   from: 0.25; to: 1.0; duration: 3800; easing.type: Easing.InOutSine }
            OpacityAnimator { target: roseGlow;    from: 0.30; to: 0.80; duration: 3800; easing.type: Easing.InOutSine }
            ScaleAnimator   { target: roseGlow;    from: 0.975; to: 1.025; duration: 3800; easing.type: Easing.InOutSine }
            OpacityAnimator { target: roseLight;   from: 0.20; to: 0.60; duration: 3800; easing.type: Easing.InOutSine }
        }
        ParallelAnimation {     // out-breath, a touch longer, like sleep
            OpacityAnimator { target: restingRose; from: 0.65; to: 0.30; duration: 4600; easing.type: Easing.InOutSine }
            ScaleAnimator   { target: restingRose; from: 1.025; to: 0.975; duration: 4600; easing.type: Easing.InOutSine }
            OpacityAnimator { target: whisperHalo; from: 1.0; to: 0.25; duration: 4600; easing.type: Easing.InOutSine }
            OpacityAnimator { target: titleHalo;   from: 1.0; to: 0.25; duration: 4600; easing.type: Easing.InOutSine }
            OpacityAnimator { target: roseGlow;    from: 0.80; to: 0.30; duration: 4600; easing.type: Easing.InOutSine }
            ScaleAnimator   { target: roseGlow;    from: 1.025; to: 0.975; duration: 4600; easing.type: Easing.InOutSine }
            OpacityAnimator { target: roseLight;   from: 0.60; to: 0.20; duration: 4600; easing.type: Easing.InOutSine }
        }
    }
    // Soft halo behind a caption: a hidden copy of the caption, blurred. Text/font
    // bind to the caption; the light is the rose's (_roseLight: the palette glow,
    // or the Widgets tab Glow override), so caption and rose glow as one instrument.
    // (2026-10-01: the halo used the caption's own dim gilt and peaked at 0.6, so
    // it measured +0.01 brightness and never read as a glow, operator: "the text
    // does not glow".) Declared before the caption so it sits underneath; the crisp
    // text never pulses.
    component CaptionHalo: Item {
        required property Text caption
        anchors.fill: parent
        opacity: 0.25
        // the ghost is drawn bold: the captions are thin (italic small / spaced
        // caps), and a blur of a hairline spreads to nothing
        Text {
            id: ghost
            visible: false
            x: caption.x; y: caption.y
            width: caption.width; height: caption.height
            text: caption.text
            font.family: caption.font.family
            font.italic: caption.font.italic
            font.pixelSize: caption.font.pixelSize
            font.letterSpacing: caption.font.letterSpacing
            font.weight: Font.Bold
            fontSizeMode: caption.fontSizeMode
            minimumPixelSize: caption.minimumPixelSize
            horizontalAlignment: caption.horizontalAlignment
            color: root._roseLight
        }
        // three blurs of the same ghost: a bright bloom hugging the letters, a
        // soft glow, and a wide faint aura — the breath lifts all three together
        MultiEffect {
            source: ghost
            x: ghost.x; y: ghost.y
            width: ghost.width; height: ghost.height
            autoPaddingEnabled: true
            opacity: 0.7
            brightness: 0.25
            blurEnabled: true
            blur: 0.5
            blurMax: 6
        }
        MultiEffect {
            source: ghost
            x: ghost.x; y: ghost.y
            width: ghost.width; height: ghost.height
            autoPaddingEnabled: true
            brightness: 0.3
            blurEnabled: true
            blur: 0.8
            blurMax: 12
        }
        MultiEffect {
            source: ghost
            x: ghost.x; y: ghost.y
            width: ghost.width; height: ghost.height
            autoPaddingEnabled: true
            opacity: 0.8
            blurEnabled: true
            blur: 1.0
            blurMax: 24
        }
    }
    Item {   // "silence in the salon" + its halo; crossfades out when media plays
        anchors.fill: parent
        opacity: widget_data.mediaActive ? 0.0 : 1.0
        Behavior on opacity { NumberAnimation { duration: 500; easing.type: Easing.InOutCubic } }
        CaptionHalo { id: whisperHalo; caption: whisper }
    Text {
        id: whisper
        anchors.horizontalCenter: parent.horizontalCenter
        y: 204
        text: "silence in the salon"
        // Individual override always wins when set — the whole point of this system is letting the
        // user fix a spot a preset made unreadable (accessibility is the user's call, not a default).
        color: {
            var ws = root._widgetStyle
            if (ws && ws["fill"] !== "" && ws["fill"] !== undefined)
                return WallInk.inked(Qt.color(ws["fill"]))
            return WallInk.inked(Qt.rgba(ncde.gilt4.r, ncde.gilt4.g, ncde.gilt4.b, 0.45))
        }
        font.family: theme.fontFamily
        font.italic: true
        font.pixelSize: theme.fontSmall
        font.letterSpacing: 1
        opacity: 0.8
    }
    }
    Item {   // "SALON NOCTURNE" + its halo
        anchors.fill: parent
        opacity: widget_data.mediaActive ? 0.0 : 1.0
        Behavior on opacity { NumberAnimation { duration: 500; easing.type: Easing.InOutCubic } }
        CaptionHalo { id: titleHalo; caption: salonTitle }
    Text {
        id: salonTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 18
        text: "SALON NOCTURNE"
        // letter-spacing gives way first as the title grows, so it stays inside the frame
        width: Math.min(implicitWidth, parent.width - 56)
        fontSizeMode: Text.HorizontalFit
        minimumPixelSize: 9
        horizontalAlignment: Text.AlignHCenter
        // Individual override always wins when set — see the note on the note above.
        color: {
            var ws = root._widgetStyle
            if (ws && ws["fill"] !== "" && ws["fill"] !== undefined)
                return WallInk.inked(Qt.color(ws["fill"]))
            return WallInk.inked(Qt.rgba(ncde.gilt4.r, ncde.gilt4.g, ncde.gilt4.b, 0.30))
        }
        font.family: {
            var ws = root._widgetStyle
            return (ws && ws["font"] !== "" && ws["font"] !== undefined) ? ws["font"] : theme.titleFont
        }
        font.pixelSize: theme.fontMedium
        font.letterSpacing: Math.max(2, 6 - (theme.fontMedium - 14) * 0.6)
    }
    }
    SalonNocturneCompact {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 10
        opacity: widget_data.mediaActive ? 1.0 : 0.0
        Behavior on opacity { NumberAnimation { duration: 500; easing.type: Easing.InOutCubic } }
    }

    // Brass bezel + glass pane over the whole card (2026-09-24), like the dock
    // icons' bezel + glass cap. On top of everything; takes no input.
    NCDEWidgetPane { anchors.fill: parent; z: 50 }
}
