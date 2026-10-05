// NCDEGlassSurface.qml — Aero-style frosted pill background (shell-wide glass).
// Full blur pipeline: ShaderEffectSource → MultiEffect blur → [opt dark base]
// → tint → specular → border → outer glow halo → rim → drop-shadow lift.
// NCDEEngine colors (ncde.accent / ncde.glow) drive tint/edge/glow.
//
// Used directly as the terminal face. DO NOT MODIFY.

import QtQuick
import QtQuick.Effects

Item {
    id: surface

    property real  cornerRadius:     height / 2
    property Item  backgroundSource: null
    property color tint:     Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
    property color edge:     Qt.rgba(ncde.glow.r,   ncde.glow.g,   ncde.glow.b,  0.85)
    property color glowRim:  ncde.glow
    property color glowHalo: ncde.glow
    property real  glowA:    0.70
    property real  blurPx:   28
    property real  specularInset: 0.08
    property real  baseDarkness: 0.0

    // ── Step 1: Sample the background Item into a texture ────────────────
    ShaderEffectSource {
        id: bgSource
        anchors.fill: parent
        sourceItem: surface.backgroundSource
        sourceRect: {
            if (!surface.backgroundSource || !surface.backgroundSource.parent)
                return Qt.rect(0, 0, 0, 0)
            var bx = surface.backgroundSource.x
            var by = surface.backgroundSource.y
            var pos = surface.mapToItem(surface.backgroundSource.parent, 0, 0)
            return Qt.rect(pos.x - bx, pos.y - by, surface.width, surface.height)
        }
        live: !ncde.screenIdle
        recursive: false
        hideSource: false
        visible: false
    }

    // ── Step 2: Blur the sampled texture, masked to the pill shape ───────
    MultiEffect {
        anchors.fill: parent
        source: bgSource
        blurEnabled: true
        blur: 1.0
        blurMax: 64
        blurMultiplier: Math.max(0, Math.min(1.0, surface.blurPx / 64))
        saturation: 0.7
        maskEnabled: true
        maskSpreadAtMin: 0.0
        maskSource: pillMask
    }

    // ── Pill mask ─────────────────────────────────────────────────────────
    Item {
        id: pillMask
        anchors.fill: parent
        visible: false
        layer.enabled: true
        Rectangle {
            anchors.fill: parent
            radius: surface.cornerRadius
            color: "white"
        }
    }

    // ── Dark base (opt-in for menus) ──────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        visible: surface.baseDarkness > 0
        color: Qt.rgba(0.07, 0.05, 0.10, surface.baseDarkness)
    }

    // ── Accent tint ───────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: surface.tint
        Behavior on color { ColorAnimation { duration: 420; easing.type: Easing.InOutCubic } }
    }

    // ── Specular highlight ────────────────────────────────────────────────
    Rectangle {
        anchors.top:         parent.top
        anchors.left:        parent.left
        anchors.right:       parent.right
        anchors.topMargin:   1
        anchors.leftMargin:  parent.width * surface.specularInset
        anchors.rightMargin: parent.width * surface.specularInset
        height: parent.height * 0.38
        radius: surface.cornerRadius
        gradient: Gradient {
            GradientStop { position: 0.00; color: Qt.rgba(1,1,1,0.34) }
            GradientStop { position: 0.60; color: Qt.rgba(1,1,1,0.06) }
            GradientStop { position: 1.00; color: Qt.rgba(1,1,1,0.00) }
        }
    }

    // ── Border ────────────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: "transparent"
        border.width: 1
        border.color: surface.edge
        Behavior on border.color { ColorAnimation { duration: 420; easing.type: Easing.InOutCubic } }
    }

    // ── Outer glow halo ───────────────────────────────────────────────────
    Rectangle {
        x: -6; y: -6
        width: parent.width + 12; height: parent.height + 12
        radius: surface.cornerRadius + 6
        color: "transparent"
        border.width: 8
        border.color: Qt.rgba(surface.glowHalo.r, surface.glowHalo.g,
                              surface.glowHalo.b, surface.glowA * 0.55)
        z: -1
        Behavior on border.color { ColorAnimation { duration: 420 } }
    }

    // ── Outer glow rim ────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: "transparent"
        border.width: 2
        border.color: Qt.rgba(surface.glowRim.r, surface.glowRim.g,
                              surface.glowRim.b, surface.glowA * 0.60)
        z: -2
        Behavior on border.color { ColorAnimation { duration: 420 } }
    }

    // ── Drop-shadow lift ──────────────────────────────────────────────────
    Rectangle {
        x: 0; y: 8
        width: parent.width; height: parent.height
        radius: surface.cornerRadius
        color: Qt.rgba(0, 0, 0, 0.55)
        z: -3
    }

    Behavior on blurPx { NumberAnimation { duration: 320; easing.type: Easing.InOutCubic } }
}
