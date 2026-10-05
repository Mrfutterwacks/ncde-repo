// RETIRED 2026-06-12 — glow is now built into MotifFrame.qml.
// Included in the resource bundle but never instantiated. Do not delete.
// Do not re-add MotifGlow { } to main.qml or MotifFrame.qml.

// ============================================================================
// MotifGlow.qml — favrile lamp-lit edge glow for MotifFrame windows (NCDE)
// ----------------------------------------------------------------------------
// Self-contained, drop-in QML component. Place it as a child of the frame you
// want lit and give it the frame's bounds:
//
//     MotifGlow {
//         anchors.fill: parent          // the MotifFrame body
//         focused:      isFocused
//         lampPulseVal: lampPulse.val   // 0..1 breathing value
//         cornerRadius: 3
//     }
//
// It draws three perimeter layers + favrile shoulders + corner cabochons, all
// EXPANDED OUTWARD past the frame edge (negative anchors.margins) so the glow
// traces the OUTER perimeter and never lights the inner edges. No picom, no
// shadow pass, no external dependency — it draws itself.
//
// Requires Qt 6.5+ (QtQuick.Effects / MultiEffect).
// ============================================================================

import QtQuick
import QtQuick.Effects

Item {
    id: root
    z: -1

    // ---- inputs ------------------------------------------------------------
    property bool  focused:      true
    property real  lampPulseVal: 0.70     // 0..1, from MotifFrame's lampPulse
    property real  cornerRadius: 3
    property real  glowA:        0.70

    // ---- palette (ncde.* defaults; override from the caller if desired) ----
    property color lampCol:   Qt.rgba(0.96, 0.74, 0.36, 1.0)  // ncde.lamp — amber crown + cabochons
    property color glowBase:  Qt.rgba(0.20, 0.69, 0.77, 1.0)  // peacock teal — Layer A + rim
    property color glowGreen: Qt.rgba(0.54, 0.77, 0.43, 1.0)  // favrile green-gold — shoulders
    // To revert to pure ncde.glow cyan: set glowBase to Qt.rgba(0.37, 0.90, 0.82, 1.0)

    // ========================================================================
    // Layer A — soft peacock glow. 10px band, ~9px outside the edge. Pulses.
    // ========================================================================
    Rectangle {
        id: outerGlow
        anchors.fill: parent
        anchors.margins: -9
        radius: root.cornerRadius + 9
        color:  "transparent"
        border.width: 10
        border.color: Qt.rgba(root.glowBase.r, root.glowBase.g, root.glowBase.b,
                              root.glowA * 0.42
                              * (root.focused ? Math.max(0.55, root.lampPulseVal + 0.45) : 0.08))
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.8; blurMax: 20 }
        Behavior on border.color { ColorAnimation { duration: 380; easing.type: Easing.InOutCubic } }
    }

    // ========================================================================
    // Layer B — amber crown. Caps the upper outer edge; the overlap with Layer
    // A creates the amber→peacock transition (no gradient property needed).
    // ========================================================================
    Rectangle {
        id: crownGlow
        anchors.top:    parent.top
        anchors.left:   parent.left
        anchors.right:  parent.right
        anchors.topMargin:   -8
        anchors.leftMargin:  -8
        anchors.rightMargin: -8
        height: Math.min(parent.height * 0.40, 80) + 8
        radius: root.cornerRadius + 8
        color:  "transparent"
        border.width: 8
        border.color: Qt.rgba(root.lampCol.r, root.lampCol.g, root.lampCol.b,
                              root.glowA * 0.58
                              * (root.focused ? Math.max(0.50, root.lampPulseVal + 0.42) : 0.06))
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.65; blurMax: 16 }
        Behavior on border.color { ColorAnimation { duration: 380; easing.type: Easing.InOutCubic } }
    }

    // ========================================================================
    // Layer C — crisp rim. 1.5px, no blur, hugging the outer edge.
    // ========================================================================
    Rectangle {
        id: glowRim
        anchors.fill: parent
        anchors.margins: -0.5
        radius: root.cornerRadius + 0.5
        color:  "transparent"
        border.width: 1.5
        border.color: Qt.rgba(root.glowBase.r, root.glowBase.g, root.glowBase.b,
                              root.focused ? 0.88 : 0.28)
        Behavior on border.color { ColorAnimation { duration: 280; easing.type: Easing.InOutCubic } }
    }

    // ========================================================================
    // Layer S — favrile green-gold shoulders. Two short bands on the upper-left
    // and upper-right outer edges, bridging the amber crown into the sides.
    // ========================================================================
    Repeater {
        model: 2
        Rectangle {
            property bool isLeft: index === 0
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.18
            height: Math.min(parent.height * 0.30, 110)
            width: 10
            anchors.left:  isLeft ? parent.left  : undefined
            anchors.right: isLeft ? undefined    : parent.right
            anchors.leftMargin:  isLeft ? -9 : 0
            anchors.rightMargin: isLeft ? 0  : -9
            radius: 6
            color:  "transparent"
            border.width: 10
            border.color: Qt.rgba(root.glowGreen.r, root.glowGreen.g, root.glowGreen.b,
                                  root.glowA * 0.50
                                  * (root.focused ? Math.max(0.45, root.lampPulseVal + 0.40) : 0.06))
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.7; blurMax: 16 }
            Behavior on border.color { ColorAnimation { duration: 380; easing.type: Easing.InOutCubic } }
        }
    }

    // ========================================================================
    // Cabochons — soft amber jewels nestled into the two top corners. Kept low
    // alpha + generous blur so they read as a catch of lamp light, not dots.
    // ========================================================================
    Repeater {
        model: 2
        Rectangle {
            property bool isLeft: index === 0
            width: 18; height: 18; radius: 9
            anchors.top: parent.top
            anchors.topMargin: -2
            anchors.left:  isLeft ? parent.left  : undefined
            anchors.right: isLeft ? undefined    : parent.right
            anchors.leftMargin:  isLeft ? -2 : 0
            anchors.rightMargin: isLeft ? 0  : -2
            color: Qt.rgba(root.lampCol.r, root.lampCol.g, root.lampCol.b,
                           root.focused ? Math.max(0.40, root.lampPulseVal * 0.7) : 0.14)
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.85; blurMax: 14 }
            Behavior on color { ColorAnimation { duration: 380; easing.type: Easing.InOutCubic } }
        }
    }
}
