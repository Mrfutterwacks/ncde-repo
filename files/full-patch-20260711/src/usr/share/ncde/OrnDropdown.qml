import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: dd
    height: 46

    property var  model: []
    property int  currentIndex: 0
    property string currentFontFamily: "serif"
    signal activated(int index, string text)

    property bool _open: false

    Rectangle {
        id: display
        anchors.fill: parent; radius: height / 2
        border.color: ncde.gilt0; border.width: 2
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: ncde.surface }
            GradientStop { position: 1; color: ncde.surfaceAlt }
        }

        Text {
            anchors.left: parent.left; anchors.leftMargin: 24
            anchors.verticalCenter: parent.verticalCenter
            text: dd.model.length ? dd.model[dd.currentIndex] : ""
            font.family: dd.currentFontFamily
            font.pixelSize: theme.fontLarge; font.weight: Font.DemiBold
            color: ncde.panelText; renderType: Text.NativeRendering
        }

        Canvas {
            id: chev
            renderStrategy: Canvas.Cooperative
            width: 14; height: 10
            anchors.right: parent.right; anchors.rightMargin: 22
            anchors.verticalCenter: parent.verticalCenter
            onPaint: {
                var ctx = getContext("2d");
                if (!ctx) { Qt.callLater(requestPaint); return; }
                ctx.clearRect(0, 0, width, height);
                ctx.fillStyle = ncde.gilt0;
                ctx.beginPath();
                ctx.moveTo(0, 1); ctx.lineTo(14, 1);
                ctx.lineTo(7, 9); ctx.closePath();
                ctx.fill();
            }
            Component.onCompleted: requestPaint()
        }

        TapHandler { onTapped: dd._open = !dd._open }
    }

    Rectangle {
        id: menu
        visible: dd._open
        y: display.height + 6
        anchors.left: parent.left; anchors.right: parent.right
        height: contentCol.implicitHeight
        radius: 12; color: ncde.surface
        border.color: ncde.gilt0; border.width: 2; z: 50

        Column {
            id: contentCol
            anchors.fill: parent; spacing: 0
            Repeater {
                model: dd.model
                delegate: Rectangle {
                    width: contentCol.width; height: 38
                    color: itemHov.hovered ? ncde.surfaceAlt : "transparent"
                    Rectangle {
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.bottom: parent.bottom; height: 1
                        color: ncde.gilt0; opacity: 0.18
                        visible: index < dd.model.length - 1
                    }
                    Text {
                        anchors.left: parent.left; anchors.leftMargin: 22
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData
                        font.family: modelData
                        font.pixelSize: theme.fontLarge; color: ncde.panelText
                        renderType: Text.NativeRendering
                    }
                    HoverHandler { id: itemHov }
                    TapHandler { onTapped: { dd.currentIndex = index; dd.currentFontFamily = modelData; dd._open = false; dd.activated(index, modelData) } }
                }
            }
        }
    }
}
