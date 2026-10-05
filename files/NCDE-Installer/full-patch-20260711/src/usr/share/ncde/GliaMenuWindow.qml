// GliaMenuWindow.qml — dark glass dropdown.
// Parchment scroll replaced with a plain dark rounded rectangle.
// Positioning, signals, and GliaMenuItem rendering unchanged.
import QtQuick

Window {
    id: win

    property var  items: []
    property real screenX: 0
    property real screenY: 0
    property bool openUpward: false
    property int  depth: 0
    property bool active: false

    signal activated(var actionId)
    signal dismissAll()
    signal requestSubmenu(int depth, var subItems, real sx, real sy, bool toLeft)
    signal pruneBelow(int depth)

    flags: Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
           | Qt.WindowStaysOnTopHint | Qt.WindowDoesNotAcceptFocus
    color: "transparent"
    visible: active

    readonly property int padV:  6
    readonly property int padH:  6
    readonly property int minW:  180
    readonly property int shad:  12

    readonly property real bodyW: Math.max(minW, column.implicitWidth + padH * 2)
    readonly property real bodyH: column.implicitHeight + padV * 2

    width:  Math.round(bodyW + shad * 2)
    height: Math.round(bodyH + shad * 2)

    // ── latched position — computed once after size settles, never re-jumps ──
    property real placedX: 0
    property real placedY: 0
    x: Math.round(placedX)
    y: Math.round(placedY)

    // screenX = title centre (depth 0) or desired card-body left edge (depth > 0)
    // screenY = title bottom edge / top (depth 0) or row global top (depth > 0)
    function place() {
        if (win.depth > 0) {
            // submenu: anchor card-body left at screenX, top at screenY
            placedX = Math.max(4, Math.min(screenX - shad, Screen.width - width - 4))
            placedY = Math.max(4, Math.min(screenY - shad, Screen.height - height - 4))
        } else {
            placedX = Math.max(4, Math.min(
                screenX - shad - bodyW / 2,
                Screen.width - width - 4))
            placedY = openUpward
                ? Math.max(4, screenY - shad - bodyH)
                : Math.min(screenY - shad, Screen.height - height - 4)
        }
    }
    onActiveChanged:  if (active) Qt.callLater(place)
    onScreenXChanged: if (active) Qt.callLater(place)
    onScreenYChanged: if (active) Qt.callLater(place)
    onWidthChanged:   if (active) Qt.callLater(place)
    onHeightChanged:  if (active) Qt.callLater(place)

    readonly property color goldLeading: Qt.rgba(240/255, 210/255, 122/255, 1.0)

    opacity: 0
    Behavior on opacity { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
    onVisibleChanged: { if (visible) { opacity = 0; raise(); opacity = 1 } }

    Item {
        x: win.shad; y: win.shad
        width: win.bodyW; height: win.bodyH

        // soft drop shadow
        Canvas {
            anchors.fill: parent
            renderStrategy: Canvas.Cooperative
            onWidthChanged:  requestPaint()
            onHeightChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                ctx.save()
                ctx.shadowColor   = "rgba(0,0,0,0.55)"
                ctx.shadowBlur    = win.shad
                ctx.shadowOffsetY = 6
                ctx.fillStyle     = "rgba(20,14,24,1)"
                var r = 8, w = width, h = height
                ctx.beginPath()
                ctx.moveTo(r, 0)
                ctx.arcTo(w, 0, w, h, r)
                ctx.arcTo(w, h, 0, h, r)
                ctx.arcTo(0, h, 0, 0, r)
                ctx.arcTo(0, 0, w, 0, r)
                ctx.closePath()
                ctx.fill()
                ctx.restore()
            }
        }

        // dark glass card
        Rectangle {
            anchors.fill: parent
            radius: 8
            color: Qt.rgba(20/255, 14/255, 24/255, 0.94)
            border.color: win.goldLeading
            border.width: 1
        }

        Column {
            id: column
            x: win.padH; y: win.padV
            width: win.bodyW - win.padH * 2
            spacing: 0

            Repeater {
                model: win.items
                delegate: GliaMenuItem {
                    id: row
                    width: column.width
                    label:      modelData.label     || ""
                    shortcut:   modelData.shortcut  || ""
                    separator:  modelData.separator === true
                    enabled:    modelData.enabled   !== false
                    checkable:  modelData.checkable === true
                    checked:    modelData.checked   === true
                    hasSubmenu: (modelData.submenu && modelData.submenu.length > 0)

                    onHoveredChanged: function(inside) {
                        if (!inside) return
                        if (hasSubmenu) {
                            var overlap     = 6
                            var parentRight = win.x + win.shad + win.bodyW
                            var parentLeft  = win.x + win.shad
                            var toLeft = (parentRight - overlap + win.minW) > Screen.width - 4
                            var sx = toLeft
                                ? (parentLeft + overlap - win.minW)
                                : (parentRight - overlap)
                            var globalPos = row.mapToGlobal(0, 0)
                            win.requestSubmenu(win.depth, modelData.submenu,
                                               sx, globalPos.y, toLeft)
                        } else {
                            win.pruneBelow(win.depth)
                        }
                    }
                    onActivated: {
                        win.activated(modelData.actionId)
                        win.dismissAll()
                    }
                }
            }
        }
    }
}
