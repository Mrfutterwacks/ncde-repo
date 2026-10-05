// NCDEParchmentSurface.qml — ivory "paper" background for NCDE popups.
//
// The shell-wide PARCHMENT surface, counterpart to NCDEGlassSurface. Glass is
// the persistent chrome (dock, panels, widgets); parchment is everything that
// pops up over it — dropdown menus, Settings, Welcome, the Handbook.
//
// Ivory paper + faint dot-mesh + gold double frame + a soft drop-shadow lift.
// Opaque, so it never samples the wallpaper and never reads see-through.
//
// The standard (2026-09-26): every tone comes from the Iris palette through
// NCDEKit — paper = k.paper, the leading and mesh are the palette's gold at the
// original design's lightness/chroma, the lift shadow is k.shade (never #000),
// and the mesh repaints when the palette changes (it used to stay brown). The
// sheet catches the ONE light (ShellLight): a breath of light on the edge that
// faces it, falling to nothing — no line, no gradient wash across the paper
// (the 2026-07-04 "ombre" bug was a wash into a fixed near-black; this is 3%
// of the light's own colour, gone before mid-sheet).
//
// Qt 6.5+ / QtQuick 2.15. MultiEffect from QtQuick.Effects. Canvas uses
// renderStrategy: Canvas.Cooperative.
//
// Usage:
//   NCDEParchmentSurface { anchors.fill: parent; cornerRadius: 14 }
import QtQuick
import QtQuick.Effects
import "ncde-color.js" as Col

Item {
    id: surface

    property real cornerRadius: 14

    NCDEKit { id: k }

    readonly property color gold2:       k.gilt1
    readonly property color goldLeading: k.paperLeading

    // ── the paper, flat and theme-adaptive, lifted by the palette's own shade ──
    Rectangle {
        id: paper
        anchors.fill: parent
        radius: surface.cornerRadius
        antialiasing: true
        color: k.paper
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: k.shadeA(0.55)
            shadowBlur: 0.38
            shadowVerticalOffset: 8
            shadowHorizontalOffset: -ShellLight.lx * 3
            shadowOpacity: 0.5
            autoPaddingEnabled: true
        }
    }

    // ── the light on the paper: a breath on the edge facing ShellLight ─────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        antialiasing: true
        rotation: 0
        gradient: Gradient {
            orientation: Math.abs(ShellLight.lx) > Math.abs(ShellLight.ly) ? Gradient.Horizontal : Gradient.Vertical
            GradientStop { position: 0.0; color: (ShellLight.lx < -0.7 || ShellLight.ly < -0.7) ? ShellLight.lt(0.05) : "transparent" }
            GradientStop { position: 0.35; color: "transparent" }
            GradientStop { position: 0.65; color: "transparent" }
            GradientStop { position: 1.0; color: (ShellLight.lx > 0.7) ? ShellLight.lt(0.05) : "transparent" }
        }
    }

    // ── faint ink dot-mesh (inset so it never touches the rounded corners) ─
    Canvas {
        id: mesh
        anchors.fill: parent
        anchors.margins: surface.cornerRadius * 0.5
        renderStrategy: Canvas.Cooperative
        readonly property string sig: k.paperMesh.toString() + "/" + k.dark
        onSigChanged: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.clearRect(0, 0, width, height)
            ctx.fillStyle = Col.css(Qt.rgba(k.paperMesh.r, k.paperMesh.g, k.paperMesh.b, k.dark ? 0.22 : 0.15))
            var step = 11
            for (var y = 4; y < height; y += step)
                for (var x = 4; x < width; x += step) {
                    ctx.beginPath(); ctx.arc(x, y, 0.7, 0, Math.PI * 2); ctx.fill()
                }
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
    }

    // ── gold double frame ─────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: "transparent"
        antialiasing: true
        border.width: 1
        border.color: surface.goldLeading
    }
    Rectangle {
        anchors.fill: parent
        anchors.margins: 3
        radius: Math.max(2, surface.cornerRadius - 3)
        color: "transparent"
        antialiasing: true
        border.width: 1
        border.color: surface.gold2
        opacity: 0.55
    }
}
