import QtQuick
import QtQuick.Effects 6.5
import "mucha-clock.js" as Clock

Item {
    id: root
    // no clip here: it cut the glass glow + shadow off at a square box (2026-09-24)
    property Item backgroundSource: null
    property var _surfaceGlass: null
    Component.onCompleted: {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("clock") : null
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            root._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("clock") : null
        }
    }
    width: parent ? parent.width : 316
    // Script Shift (2026-09-24): the one text-size factor, read the same way LaPivot's
    // Theme does (fontSizeScale x uiScale; uiScale is retired and stays 1). The card
    // grows to fit its text; nothing else about it scales.
    readonly property real ts: (typeof settings !== "undefined" && settings.fontSizeScale > 0 ? settings.fontSizeScale : 1)
                             * (typeof settings !== "undefined" && settings.uiScale > 0 ? settings.uiScale : 1)
    // Greeting band (2026-09-25, operator: "give the greeting its own band above the
    // clock"). The greeting used to sit ON the frame's top rail and crowd it; now it
    // has its own ribbon, and the arch starts below it. The band is as tall as the
    // text (Script Shift grows it); the card grows to fit, nothing scales.
    readonly property real bandTop: 8                                   // clear of the brass bezel ring
    readonly property real bandH: greetingText.visible ? Math.ceil(greetingText.implicitHeight + 4) : 0
    readonly property real frameTop: greetingText.visible ? bandTop + bandH + 9 : 11
    // frame (74 + 9*ts) + date ribbon room below it; same bottom margin as before
    height: Math.round(frameTop + 71 + 18 * ts)
    onHeightChanged: clock.repaintAll()
    onBandHChanged: clock.repaintAll()
    NCDEGlass2 {   // Mucha glass: full NCDEGlassSurface layers + palette-driven ornamental frame
        cornerRadius: 14
        // Even rhythm (2026-09-24): same 4/2 glass inset as Space/Weather/Stats/Salon —
        // Clock alone filled edge to edge, 8px wider than its neighbours with 2px-off gaps.
        anchors {
            fill: parent
            leftMargin: 4; rightMargin: 4
            topMargin: 2; bottomMargin: 2
        }
        backgroundSource: root.backgroundSource
        revealPulse: intellihide.widgetRevealed
        glintPulse: intellihide.glintPulse
        // Iris Chroma baseline + Filigree override — resolved inside NCDEGlassSurface.
        surfaceKey: "clock"
        glass: root._surfaceGlass
    }
    Item {
        id: clock
        clip: true   // content clips here instead of at root, so the glass keeps its rounded glow
        width: parent.width
        height: root.height
        z: 1

        property var _widgetStyle: null
        // wallpaper ink: text + lit digits are painted, so repaint when it changes
        Connections { target: WallInk; function onInkSerialChanged() { clock.repaintAll() } }
        Component.onCompleted: {
            _widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("clock") : null
            repaintAll()
        }
        Connections {
            target: ncde
            function onThemeChanged() {
                clock._widgetStyle = typeof ncde.widgetStyle === "function" ? ncde.widgetStyle("clock") : null
                clock.repaintAll()
            }
        }

        // Seven-segment metrics (scaled to the section width)
        readonly property real digitW: 27
        readonly property real digitH: 46
        readonly property real segT:   6
        readonly property real gap:    7
        readonly property real colonW: 11

        // Three layers (2026-09-25): the whole card used to be ONE canvas repainted on
        // every clock tick -- frame, greeting ribbon, date and all, once a second for the
        // colon blink -- and that repaint stalled every other animation on the desktop
        // (measured: the orrery froze ~150 ms each second). Now the frame layer repaints
        // only on theme / size / ink / date changes, the digits once a minute, and the
        // colon on its own few-pixel canvas. Same painters, same order, same pixels.
        function _colors() {
            var ws = clock._widgetStyle
            return {
                accent:  (ws && ws["accent"]  !== "" && ws["accent"]  !== undefined) ? Qt.color(ws["accent"])  : ncde.accent,
                glow:    (ws && ws["glow"]    !== "" && ws["glow"]    !== undefined) ? Qt.color(ws["glow"])    : ncde.glow,
                leading: (ws && ws["leading"] !== "" && ws["leading"] !== undefined) ? ws["leading"] : ncde.gilt4.toString()
            }
        }
        // The card has always been drawn with the glow the lit colon leaves on the
        // context (it sets a shadow the one-canvas version carried into every later
        // repaint). Replaying the colon far off-canvas leaves exactly that state, so
        // the layers keep the card's familiar glow instead of a flatter first paint.
        function _litState(ctx, c) {
            Clock.paintColon(ctx, -10000, -10000, digitH, 3.2, true, c.accent, c.glow, c.leading)
        }
        readonly property real digY: root.frameTop + 14
        readonly property real readoutX: (width - Clock.measureDigits(4, true, digitW, gap, colonW)
                                          - ((widget_data.timeAMPM || "") !== "" ? 22 : 0)) / 2
        readonly property real colonX: readoutX + 2 * (digitW + gap)
        property string _shownTime: ""
        property string _shownDate: ""
        function repaintAll() { clockCanvas.requestPaint(); digitsCanvas.requestPaint(); colonCanvas.requestPaint() }
        onWidthChanged: repaintAll()
        onReadoutXChanged: repaintAll()
        onDigYChanged: repaintAll()

        // Repaint only what the backend clock tick actually changed
        Connections {
            target: widget_data
            function onClockChanged() {
                if (!clock.visible) return
                colonCanvas.requestPaint()
                var t = (widget_data.timeHour || "") + ":" + (widget_data.timeMinute || "") + (widget_data.timeAMPM || "")
                if (t !== clock._shownTime) digitsCanvas.requestPaint()
                if ((widget_data.dateString || "") !== clock._shownDate) clockCanvas.requestPaint()
            }
        }

        // Frame layer: greeting band + cartouche + date banner
        Canvas {
            id: clockCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Cooperative
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                var c = clock._colors(), accent = c.accent, glow = c.glow, leading = c.leading
                clock._litState(ctx, c)

                // Ornate cartouche frame (leaves room for crest above + date below)
                var fx = 8, fy = root.frameTop
                var fw = width - 16
                var fh = 74 + 9 * root.ts   // bottom rail stays 6px under the date ribbon's centre
                // greeting band: ribbon hugs the text, hangs the arch from a came drop
                if (greetingText.visible)
                    Clock.paintGreetingBand(ctx, width / 2, root.bandTop,
                                            Math.min(fw - 60, greetingText.width + 30), root.bandH,
                                            fy, accent, glow, leading)
                Clock.paintClockFrame(ctx, fx, fy, fw, fh, accent, glow, leading,
                                      { noCrest: greetingText.visible })

                // Date ribbon-cartouche drawn into the glass below the digits
                var dateStr = (widget_data.dateString || "").toUpperCase()
                clock._shownDate = widget_data.dateString || ""
                Clock.paintDateBanner(ctx, width / 2, clock.digY + clock.digitH + 8,
                                      Math.min(fw - 60, 200), dateStr,
                                      theme.fontFamily, accent, glow, leading, root.ts)
            }
        }

        // Digits layer: HH  MM  (+ AM/PM column if present) -- once a minute
        Canvas {
            id: digitsCanvas
            anchors.fill: parent
            renderStrategy: Canvas.Cooperative
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                var c = clock._colors(), accent = c.accent, glow = c.glow, leading = c.leading
                clock._litState(ctx, c)
                var hh = widget_data.timeHour   || "  "
                var mm = widget_data.timeMinute || "  "
                var ampm = widget_data.timeAMPM || ""
                clock._shownTime = (widget_data.timeHour || "") + ":" + (widget_data.timeMinute || "") + ampm
                if (hh.length < 2) hh = " " + hh
                var digY = clock.digY
                var cur = clock.readoutX
                Clock.paintDigit(ctx, hh.charAt(0), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow, leading)
                cur += clock.digitW + clock.gap
                Clock.paintDigit(ctx, hh.charAt(1), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow, leading)
                cur += clock.digitW + clock.gap
                cur += clock.colonW + clock.gap                  // the colon has its own layer
                Clock.paintDigit(ctx, mm.charAt(0), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow, leading)
                cur += clock.digitW + clock.gap
                Clock.paintDigit(ctx, mm.charAt(1), cur, digY, clock.digitW, clock.digitH, clock.segT, accent, glow, leading)
                cur += clock.digitW + clock.gap
                if (ampm !== "")
                    Clock.paintAmpm(ctx, cur + 2, digY, clock.digitH, ampm, theme.fontFamily, leading, root.ts)
            }
        }

        // Colon layer: the only thing that changes every second, on a canvas just
        // big enough for its two dots and their glow
        Canvas {
            id: colonCanvas
            readonly property real m: 12
            x: Math.floor(clock.colonX - m); y: Math.floor(clock.digY - m)
            width: Math.ceil(clock.colonW + 2 * m); height: Math.ceil(clock.digitH + 2 * m)
            renderStrategy: Canvas.Cooperative
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                var c = clock._colors()
                ctx.save()
                ctx.translate(-x, -y)                            // paint in card coordinates
                Clock.paintColon(ctx, clock.colonX + clock.colonW / 2, clock.digY, clock.digitH, 3.2,
                                 widget_data.colonOn, c.accent, c.glow, c.leading)
                ctx.restore()
            }
        }

        // Greeting — in its own band above the frame, always bold; cream fallback so it never gets lost in palette changes
        Text {
            id: greetingText
            // 2026-09-25: centred in its own band (root.bandTop/bandH) above the arch.
            // A long name shrinks to the ribbon rather than overflow it.
            anchors.verticalCenter: parent.top
            anchors.verticalCenterOffset: root.bandTop + root.bandH / 2 + 1
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(implicitWidth, parent.width - 92)
            fontSizeMode: Text.HorizontalFit
            minimumPixelSize: 9
            z: 10                                    // above the frame crest (was visually obscured)
            text: (widget_data.greeting || "") + (settings.userName ? " " + settings.userName : "")
            font.family: {
                var ws = clock._widgetStyle
                return (ws && ws["font"] !== "" && ws["font"] !== undefined) ? ws["font"] : theme.fontFamily
            }
            font.italic: true
            font.bold: true                          // bold all the time — holds up over the ornament
            font.pixelSize: theme.fontMedium   // Script Shift: no cap; the band makes room (bandH)
            color: {
                var ws = clock._widgetStyle
                if (ws && ws["fill"] !== "" && ws["fill"] !== undefined)
                    return WallInk.inked(Qt.color(ws["fill"]))      // honour an explicit per-widget fill
                return WallInk.inked(ncde.gilt4)                     // Glass text: fixed-bright, accent-hue-reactive (not adaptive ink)
            }
            visible: text !== ""
            style: theme.textStyle; styleColor: theme.textStyleColor
            layer.enabled: theme.textShadowEnabled
            layer.effect: MultiEffect { shadowEnabled: true; shadowColor: theme.textShadowColor
                shadowBlur: theme.textShadowRadius / 32.0
                shadowHorizontalOffset: theme.textShadowOffsetX; shadowVerticalOffset: theme.textShadowOffsetY }
        }

    }

    // Brass bezel + glass pane over the whole card (2026-09-24), like the dock
    // icons' bezel + glass cap. On top of everything; takes no input.
    NCDEWidgetPane { anchors.fill: parent; z: 50 }
}
