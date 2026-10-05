// KithCursor.qml — NCDE stained-glass cursor renderer (Qt Canvas, no png/svg).
//
// Render the compositor's software cursor in the Kith Glass style. Mirror the
// system cursor shape into `cursorName`; for the busy/wait shape the rose-window
// rotates via a single NumberAnimation feeding the paint phase.
//
// Usage in the compositor cursor layer:
//   KithCursor {
//       cursorName: seat.cursorShape      // "arrow","pointer","wait","ns-resize"…
//       size: 32
//       accentColor: ncde.accent
//       glowColor:   ncde.glow
//       // position so the hotspot sits under the device point:
//       x: pointer.x - hotspotX
//       y: pointer.y - hotspotY
//   }

import QtQuick 2.15
import "kithglass-cursors.js" as Cursors

Canvas {
    id: cur

    property string cursorName: "arrow"
    property int    size: 32
    // Transparent breathing room around the drawn cursor so the antialiased arrow tip can't be
    // clipped by the window edge. The cursor is still drawn at `size` (pixel-identical), just inset
    // by `pad`; `pad` is folded into hotspotX/Y so the point lands true under the device.
    property int    pad: 6
    property color  accentColor: (typeof ncde !== 'undefined' && ncde.accent) ? ncde.accent : "#e6c785"
    property color  glowColor:   (typeof ncde !== 'undefined' && ncde.glow)   ? ncde.glow   : "#7fd0f0"

    // Resolved metadata for the current shape
    readonly property var  _meta: Cursors.CURSORS[Cursors.normalizeCursor(cursorName)] || Cursors.CURSORS.arrow
    readonly property bool animated: _meta.animated === true
    readonly property bool motionAllowed: typeof animPolicy === "undefined" || animPolicy === null
        || (cur.visible && animPolicy.decorative && !animPolicy.screenIdle)
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 2.0 : 1.0
    // Hotspot in pixels — offset the item by these so the point lands true (incl. the pad inset).
    readonly property real hotspotX: _meta.hot[0] * size + pad
    readonly property real hotspotY: _meta.hot[1] * size + pad

    width: size + 2 * pad
    height: size + 2 * pad
    antialiasing: true
    renderStrategy: Canvas.Cooperative

    // animation phase (0..1) for the wait spinner
    property real phase: 0
    NumberAnimation on phase {
        running: cur.animated && cur.motionAllowed
        from: 0; to: 1
        duration: 1100 * cur.motionDurationScale
        loops: Animation.Infinite
        onStopped: cur.phase = 0
    }

    onPhaseChanged:       if (animated) requestPaint()
    onCursorNameChanged:  requestPaint()
    onSizeChanged:        requestPaint()
    onAccentColorChanged: requestPaint()
    onGlowColorChanged:   requestPaint()
    Component.onCompleted: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        if (!ctx) { Qt.callLater(requestPaint); return }
        ctx.clearRect(0, 0, width, height)
        ctx.save()
        ctx.translate(pad, pad)                 // inset by the transparent margin; draw at `size`
        Cursors.matchCursor(ctx, size,
                            cursorName, "" + accentColor, "" + glowColor, phase)
        ctx.restore()
    }
}
