// NCDEDialog.qml — modal sheet on a dimmed ground. Parchment-dark, gilt border.
// Put message content as default children; wire buttons via the signals.
import QtQuick 2.15

Item {
    id: dlg
    property string title: ""
    property bool open: false
    default property alias content: holder.data
    anchors.fill: parent
    visible: open
    z: 1000
    NCDEKit { id: k }

    // dim scrim
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.04, 0.02, 0.01, 0.55)
        TapHandler { onTapped: {} }   // swallow taps behind the sheet
    }

    Rectangle {
        id: sheet
        anchors.centerIn: parent
        width: Math.min(parent.width - 80, 420)
        height: head.height + holder.childrenRect.height + 28
        radius: 12
        color: k.panelBg; border.color: k.gilt0; border.width: 2

        // soft blurred drop shadow — same Canvas technique as GliaMenuWindow.qml/
        // MoveToDialog.qml. Sized off parent (sheet), so it tracks the sheet's
        // dynamic height (head.height + holder.childrenRect.height).
        Canvas {
            anchors.fill: parent
            anchors.margins: -16
            z: -1
            renderStrategy: Canvas.Cooperative
            onWidthChanged: requestPaint()
            onHeightChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.save()
                ctx.shadowColor   = "rgba(0,0,0,0.55)"
                ctx.shadowBlur    = 16
                ctx.shadowOffsetY = 6
                ctx.fillStyle     = k.panelBg
                var r = sheet.radius, w = width - 32, h = height - 32
                ctx.translate(16, 16)
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

        // gilt inner hairline
        Rectangle { anchors.fill: parent; anchors.margins: 4; radius: 9
                    color: "transparent"; border.color: k.gilt4; border.width: 1; opacity: 0.7 }

        Rectangle {
            id: head
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: 8 }
            height: 34; radius: 8
            gradient: Gradient { GradientStop { position: 0; color: k.wine3 } GradientStop { position: 1; color: k.wine1 } }
            Text { anchors.centerIn: parent; text: dlg.title
                   font.family: k.display; font.bold: true; font.pixelSize: k.fs(13)
                   font.letterSpacing: 2; color: k.gilt5 }
        }
        Item {
            id: holder
            anchors { left: parent.left; right: parent.right; top: head.bottom; bottom: parent.bottom; margins: 18 }
        }
        scale: dlg.open ? 1.0 : 0.94
        Behavior on scale { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 140; easing.type: Easing.OutCubic } }
    }
}
