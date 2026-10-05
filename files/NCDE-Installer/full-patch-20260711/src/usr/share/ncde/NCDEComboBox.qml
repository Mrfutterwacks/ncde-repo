// NCDEComboBox.qml — cartouche dropdown with a parchment-dark popup.
// Restyles the Qt ComboBox (background/contentItem/indicator/delegate/popup),
// keeping all behaviour but TapHandler-free interaction via the control itself.
import QtQuick 2.15
import QtQuick.Controls 2.15

ComboBox {
    id: cbx
    implicitWidth: 200; implicitHeight: 36
    NCDEKit { id: k }
    font.family: k.serif; font.pixelSize: k.fs(15)

    background: Rectangle {
        radius: k.rControl
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: k.surface } GradientStop { position: 1; color: k.panelBg2 } }
        border.color: cbx.activeFocus ? k.cer : k.gilt1; border.width: 1.5
    }
    contentItem: Text {
        leftPadding: 16; rightPadding: cbx.indicator.width + 8
        text: cbx.displayText; font: cbx.font; color: k.ink
        verticalAlignment: Text.AlignVCenter; elide: Text.ElideRight
    }
    indicator: Canvas {
        x: cbx.width - width - 14; y: (cbx.height - height)/2
        width: 12; height: 8; antialiasing: true
        renderStrategy: Canvas.Cooperative; layer.enabled: true
        Component.onCompleted: requestPaint()
        onPaint: { var ctx=getContext("2d"); ctx.reset(); ctx.fillStyle = k.gilt2;
            ctx.beginPath(); ctx.moveTo(0,0); ctx.lineTo(width,0); ctx.lineTo(width/2,height); ctx.closePath(); ctx.fill(); }
    }
    delegate: ItemDelegate {
        width: cbx.width
        contentItem: Text {
            text: modelData; font.family: k.serif; font.pixelSize: k.fs(15)
            color: highlighted ? k.wine1 : k.ink; verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: highlighted ? k.gilt3 : "transparent"
        }
    }
    popup: Popup {
        y: cbx.height + 4; width: cbx.width
        implicitHeight: Math.min(contentItem.implicitHeight + 4, 280)
        padding: 3
        background: Rectangle {
            radius: k.rControl; color: k.surface; border.color: k.gilt1; border.width: 1.5
        }
        contentItem: ListView {
            clip: true; implicitHeight: contentHeight
            model: cbx.popup.visible ? cbx.delegateModel : null
            currentIndex: cbx.highlightedIndex
            ScrollBar.vertical: NCDEScrollBar {}
        }
    }
}
