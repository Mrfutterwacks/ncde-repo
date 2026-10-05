import QtQuick
import QtQuick.Effects 6.5

// NCDEGlassCap — a domed glass lens laid OVER an icon medallion, so dock /
// bottom-panel icons read as glass buttons set in their brass bezel rather
// than flat paintings behind it. Same layer vocabulary as NCDEGlassSurface,
// re-derived for a convex dome instead of a flat pane:
//   1. lens tint      — palette-tinted body, lighter at the top, thicker/darker
//                       toward the bottom (light travels through more glass)
//   2. bottom caustic — a dome FOCUSES light that enters its top into a soft
//                       bright pool near the bottom: the single strongest
//                       "this is a glass bead" cue (the Aqua-button tell)
//   3. top specular   — broad wet crescent reflecting the implied upper-left
//                       light, brightening on hover
//   4. catch-light    — small hot point where that light concentrates
//   5. rim            — Fresnel edge: glass reflects more at grazing angles,
//                       so the rim reads brighter than the centre; darker
//                       lower lip grounds it in the bezel socket
// Iris Chroma drives it: tint = ncde.accent, caustic = ncde.glow. Static — no
// animation beyond a hover crossfade, so animPolicy has nothing to gate.
// Place it AFTER the icon, centred on the bezel, with the icon's scale.
// Weight & touch (2026-09-24): `pressed` = the dome sunk 1px into its socket —
// less light reaches it, so specular, catch-light and caustic all dim. Callers
// shift the cap 1px down alongside NCDEIconBezel.pressed.
// One light (2026-09-25): tint, crescent, catch-light and rim read ShellLight; the
// caustic pools on the side AWAY from the light, where a lens focuses it.
Item {
    id: cap
    property real  capSize: 48          // = the bezel's bezelSize (the socket)
    property bool  hovered: false
    property bool  pressed: false
    NCDEKit { id: ck }   // the standard (2026-09-26): shade from the palette, never violet-black
    property color tintColor: ncde.accent
    property color causticColor: ncde.glow
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)

    width: capSize; height: capSize

    // 0. cast light (2026-09-25, BEAUTIFY-NEXT #29) — light through a coloured
    //    glass bead lands on the bed beside it as a faint pool of the bead's own
    //    tint, thrown AWAY from the shell's one light. A soft ellipse that fades
    //    to nothing on its outer side (no harsh line); cut away under the socket.
    //    Static; repainted only when the light, palette or size changes.
    Canvas {
        id: castLight
        z: -1
        readonly property real throwK: 0.30
        width: cap.capSize * 1.5; height: cap.capSize * 1.5
        x: (cap.width - width) / 2 - ShellLight.lx * cap.capSize * throwK
        y: (cap.height - height) / 2 - ShellLight.ly * cap.capSize * throwK
        visible: !cap._hc
        opacity: cap.pressed ? 0.6 : 1.0
        renderStrategy: Canvas.Cooperative
        onWidthChanged: requestPaint()
        onXChanged: requestPaint()
        onYChanged: requestPaint()
        Connections { target: ShellLight; function onSignatureChanged() { castLight.requestPaint() } }
        Connections { target: cap; function onTintColorChanged() { castLight.requestPaint() } }
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var c = cap.tintColor, s = ShellLight.strength
            var g = ctx.createRadialGradient(width / 2, height / 2, 0, width / 2, height / 2, width / 2)
            function st(t, a) {
                g.addColorStop(t, "rgba(" + Math.round(c.r * 255) + "," + Math.round(c.g * 255) + ","
                                          + Math.round(c.b * 255) + "," + (a * s) + ")")
            }
            st(0.0, 0.20); st(0.35, 0.14); st(0.65, 0.05); st(1.0, 0)
            ctx.fillStyle = g
            ctx.fillRect(0, 0, width, height)
            // only the bed takes the light: nothing is laid over the medallion or the
            // brass socket (the cap is exactly the socket), which keep their own colour
            ctx.globalCompositeOperation = "destination-out"
            ctx.fillStyle = "rgba(0,0,0,1)"
            ctx.beginPath()
            ctx.arc(cap.width / 2 - x, cap.height / 2 - y, cap.capSize / 2, 0, 2 * Math.PI)
            ctx.fill()
            ctx.globalCompositeOperation = "source-over"
        }
    }

    // 1. lens tint (thin side toward the light)
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        rotation: ShellLight.gradientTurn
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(cap.tintColor.r, cap.tintColor.g, cap.tintColor.b, 0.04) }
            GradientStop { position: 0.6; color: Qt.rgba(cap.tintColor.r, cap.tintColor.g, cap.tintColor.b, 0.10) }
            GradientStop { position: 1.0; color: ck.shadeA(0.22) }
        }
    }

    // 2. bottom caustic — offset away from the light
    Rectangle {
        x: parent.width * (0.23 - ShellLight.lx * 0.08)
        y: parent.height * 0.62
        width: parent.width * 0.54
        height: parent.height * 0.26
        radius: height / 2
        color: Qt.rgba(cap.causticColor.r, cap.causticColor.g, cap.causticColor.b, cap.pressed ? 0.28 : (cap.hovered ? 0.55 : 0.40))
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.7; blurMax: Math.max(4, cap.capSize * 0.25) }
        Behavior on color { ColorAnimation { duration: 140 } }
    }

    // 3. top specular — wet shine (2026-09-25): an ELLIPSE, not a bar, so the
    //    liquid meniscus (its crisp lower edge) curves with the dome instead of
    //    cutting a straight line across it. Nudged toward the light. The ellipse
    //    (a circle squashed by a Scale) stays inside the dome — no clip needed.
    Rectangle {
        readonly property real d: parent.width * 0.68
        x: parent.width * (0.16 + ShellLight.lx * 0.08)
        y: parent.height * 0.05
        width: d; height: d
        radius: d / 2
        transform: Scale { yScale: 0.62 }
        opacity: cap.pressed ? 0.55 : (cap.hovered ? 1.0 : 0.80)
        Behavior on opacity { NumberAnimation { duration: 140 } }
        gradient: Gradient {
            GradientStop { position: 0.00; color: ShellLight.lt(0.62) }
            GradientStop { position: 0.45; color: ShellLight.lt(0.28) }
            GradientStop { position: 1.00; color: ShellLight.lt(0.12) }
        }
    }

    // 3b. wet refraction arc — the light bent through the bead leaves as a thin
    //     bright arc just inside the rim, on the side away from the light. It
    //     fades to nothing at both ends (no cut ends). Painted once; repainted
    //     only on resize or a palette change.
    Canvas {
        id: refraction
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        opacity: cap.pressed ? 0.6 : 1.0
        onWidthChanged: requestPaint()
        Connections { target: ShellLight; function onSignatureChanged() { refraction.requestPaint() } }
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            var bw = Math.max(1, cap.capSize * 0.035)
            var r = width / 2 - Math.max(1.5, cap.capSize * 0.05) - bw / 2
            if (r <= 2) return
            var far = Math.atan2(-ShellLight.ly, -ShellLight.lx)   // away from the light
            var span = 1.15                                          // ±66°
            // one continuous stroke; a conical gradient fades it to nothing at
            // both ends (segments beaded where their caps overlapped)
            var g = ctx.createConicalGradient(width / 2, height / 2, -far)
            var f = span / (2 * Math.PI)
            g.addColorStop(0.0, ShellLight.css(0.40))
            for (var k = 1; k <= 6; k++) {
                var t = Math.cos(k / 6 * Math.PI / 2)
                g.addColorStop(f * k / 6, ShellLight.css(0.40 * t * t))
                g.addColorStop(1 - f * k / 6, ShellLight.css(0.40 * t * t))
            }
            g.addColorStop(1.0, ShellLight.css(0.40))
            ctx.lineWidth = bw
            ctx.strokeStyle = g
            ctx.beginPath()
            ctx.arc(width / 2, height / 2, r, far - span, far + span, false)
            ctx.stroke()
        }
    }

    // 4. catch-light — where the light concentrates, laid along the rim
    Rectangle {
        width: Math.max(2, parent.width * 0.12)
        height: width * 0.72
        x: parent.width * ShellLight.hx(0.36) - width / 2
        y: parent.height * ShellLight.hy(0.36) - height / 2
        radius: height / 2
        rotation: ShellLight.gradientTurn
        color: ShellLight.lt(cap.pressed ? 0.55 : (cap.hovered ? 0.95 : 0.80))
    }

    // 5. rim — bright Fresnel hairline + darker lower lip
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border.width: cap._hc ? 2 : 1
        border.color: ShellLight.lt(cap._hc ? 0.60 : 0.30)
    }
    Rectangle {   // darker lip on the side away from the light
        anchors.fill: parent
        anchors.margins: 1
        radius: width / 2
        rotation: ShellLight.gradientTurn
        color: "transparent"
        gradient: Gradient {
            GradientStop { position: 0.0;  color: "transparent" }
            GradientStop { position: 0.80; color: "transparent" }
            GradientStop { position: 1.0;  color: ck.shadeA(0.30) }
        }
    }
}
