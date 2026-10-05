// NCDEGlass2.qml — Mucha-styled glass: the FULL NCDEGlassSurface pipeline plus a
// Mucha ornamental frame (leading, corner medallions, top crest) via mucha-glass.js.
//
// Rebuilt 2026-09-23: this used to carry its own private copy of the glass
// pipeline, which had drifted — no shadow/cavity depth, flat tint, no blur-
// compensating saturation, no corner catch-light, no inner rim, no glint. It
// now IS an NCDEGlassSurface (every layer, every future fix) with the frame
// painted on top, so Mucha glass reads as real glass, not a gilded sticker.
// Iris Chroma drives it end to end: tint/edge/glow from ncde.* (or Filigree's
// per-surface override via surfaceKey/glass, same as every other glass), and
// the frame's leading + leaves from the palette's gilt ramp + verd.
//
// BACKGROUND NOTE: only valid where blur samples the right Window (desktop
// widgets) — SettingsPanel/GliaMenu use NCDEParchmentSurface instead.
import QtQuick
import "mucha-glass.js" as MuchaGlass

NCDEGlassSurface {
    id: surface

    // DesktopWidget sections are 14px rounded; everything else — tint, edge,
    // glow + intensity, blur, shine, surfaceKey/glass, glint — is inherited
    // unchanged, so switching a widget to NCDEGlass2 only ADDS the frame.
    cornerRadius: 14

    property bool frameCrest:   true
    property bool frameCorners: true

    // ── Mucha ornamental frame overlay ─────────────────────────────────
    Canvas {
        id: muchaFrame
        anchors.fill: parent
        z: 10
        property bool dirty: true
        onPaint: {
            var ctx = getContext("2d")
            if (!ctx) return
            MuchaGlass.paintMuchaFrame(ctx, width, height, surface.cornerRadius,
                                       surface.glowRim, surface.glowHalo,
                                       { crest: surface.frameCrest, corners: surface.frameCorners, inset: 3,
                                         leading: { bright: ncde.gilt4, mid: ncde.gilt2, deep: ncde.gilt0 },
                                         leaf: ncde.verd,
                                         // the shell's one light (2026-09-25): the came crown catches it
                                         light: { lx: ShellLight.lx, ly: ShellLight.ly, css: ShellLight.css } })
        }
        onDirtyChanged:  if (dirty) { requestPaint(); dirty = false }
        onWidthChanged:  dirty = true
        onHeightChanged: dirty = true
        Connections {
            target: surface
            function onGlowRimChanged()  { muchaFrame.dirty = true }
            function onGlowHaloChanged() { muchaFrame.dirty = true }
        }
        Connections {
            target: ncde
            function onThemeChanged() { muchaFrame.dirty = true }   // Iris palette swap → new gilt/verd
        }
        Connections {
            target: ShellLight   // the light follows the sun (2026-09-25)
            function onSignatureChanged() { muchaFrame.dirty = true }
        }
    }
}
