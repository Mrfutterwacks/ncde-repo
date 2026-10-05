import QtQuick
import QtQuick.Layouts
import "hb-stationery.js" as Sta

Item {
    id: gallery
    property var pal
    property var win

    ColumnLayout {
        anchors.fill: parent; spacing: 0

        // identity bar — set your display name, signature, and stationery here
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: galRoleEdit.implicitHeight + 30; color: pal.paper2
            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: pal.gilt1 }
            RowLayout {
                anchors.fill: parent; anchors.leftMargin: 20; anchors.rightMargin: 18
                anchors.topMargin: 8; anchors.bottomMargin: 8; spacing: 10
                Text { text: "NAME"; font.family: pal.fell; font.pixelSize: theme.fontSmall; font.letterSpacing: 2
                       color: pal.gilt1; Layout.alignment: Qt.AlignVCenter }
                Rectangle {
                    Layout.preferredWidth: Math.max(180, galRoleEdit.contentWidth + 20); Layout.maximumWidth: 320
                    Layout.preferredHeight: galRoleEdit.implicitHeight + 12; radius: 5
                    color: pal.paper1; border.color: pal.gilt2; border.width: 1
                    TextInput { id: galRoleEdit; anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8
                                verticalAlignment: TextInput.AlignVCenter
                                text: mail.accountRole; color: pal.ink
                                font.family: pal.fell; font.italic: true; font.pixelSize: theme.fontMedium
                                onAccepted: mail.saveRole(text) }
                }
                Text { text: "SIGNATURE"; font.family: pal.fell; font.pixelSize: theme.fontSmall; font.letterSpacing: 2
                       color: pal.gilt1; Layout.alignment: Qt.AlignVCenter }
                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: galRoleEdit.implicitHeight + 12; radius: 5
                    color: pal.paper1; border.color: pal.gilt2; border.width: 1
                    TextInput { id: galSigEdit; anchors.fill: parent; anchors.leftMargin: 8; anchors.rightMargin: 8
                                verticalAlignment: TextInput.AlignVCenter
                                text: mail.accountSignature; color: pal.ink
                                font.family: pal.garamond; font.pixelSize: theme.fontMedium
                                onAccepted: mail.saveSignature(text) }
                }
                Rectangle {
                    Layout.preferredWidth: galSavT.implicitWidth + 32; Layout.preferredHeight: galRoleEdit.implicitHeight + 12
                    radius: height/2
                    color: pal.verd2; border.color: pal.verd1; border.width: 1
                    Text { id: galSavT; text: "Save"; font.family: pal.titles; font.pixelSize: theme.fontMedium
                           color: pal.paper0; anchors.centerIn: parent }
                    // capture both before saving: saveRole's accountChanged resets these fields
                    TapHandler { onTapped: { var r = galRoleEdit.text; var s = galSigEdit.text; mail.saveRole(r); mail.saveSignature(s) } }
                }
            }
        }

        // stationery card grid
        Flickable {
            Layout.fillWidth: true; Layout.fillHeight: true; clip: true
            contentHeight: galFlow.implicitHeight + 32; contentWidth: width

            Flow {
                id: galFlow; padding: 16; spacing: 16
                readonly property int cols: Math.max(1, Math.floor((parent.width - 32 + spacing) / (180 + spacing)))
                width: cols * 180 + (cols - 1) * spacing + 32
                x: Math.max(0, (parent.width - width) / 2)

                Repeater {
                    model: Sta.SETS.length
                    delegate: Column {
                        id: galCard
                        property var  set:      Sta.SETS[index]
                        property bool selected: set.key === win.composeStationery
                        width: 180; spacing: 5

                        Rectangle {
                            width: 180; height: 234; radius: 3; clip: true
                            border.width: galCard.selected ? 2.5 : 1
                            border.color: galCard.selected ? pal.gilt3 : pal.gilt2

                            Canvas {
                                anchors.fill: parent; renderStrategy: Canvas.Cooperative
                                Component.onCompleted: requestPaint()
                                onPaint: { var c = getContext("2d"); c.reset(); galCard.set.paint(c, width, height) }
                            }
                            Column {
                                anchors.fill: parent; anchors.topMargin: 14
                                anchors.leftMargin: 180 * (galCard.set.bodyL || 0.2) + 8
                                anchors.rightMargin: 12; anchors.bottomMargin: 10; spacing: 2
                                Canvas {
                                    width: 48; height: 30; renderStrategy: Canvas.Cooperative
                                    Component.onCompleted: requestPaint()
                                    onPaint: { var c = getContext("2d"); c.reset(); Sta.crestMark(c, width, height, galCard.set.nameC) }
                                }
                                Text { width: parent.width; elide: Text.ElideRight
                                       text: mail.accountRole.length > 0 ? mail.accountRole : (mail.accountName.length ? mail.accountName : "Your Name")
                                       color: galCard.set.nameC; font.family: pal.serif; font.bold: true; font.pixelSize: theme.fontMedium }
                                Text { width: parent.width; text: galCard.set.sal
                                       color: galCard.set.bodyC
                                       font.family: pal.garamond; font.italic: true; font.pixelSize: theme.fontSmall }
                                Text { width: parent.width; wrapMode: Text.WordWrap; maximumLineCount: 3
                                       elide: Text.ElideRight; text: "Your letter here…"
                                       color: galCard.set.bodyC; opacity: 0.75
                                       font.family: pal.garamond; font.pixelSize: theme.fontSmall }
                            }
                            TapHandler { onTapped: win.composeStationery = galCard.set.key }
                            HoverHandler { id: galHov }
                            Rectangle { anchors.fill: parent; radius: parent.radius; color: "transparent"
                                        border.width: galHov.hovered && !galCard.selected ? 1.5 : 0
                                        border.color: pal.gilt3 }
                        }
                        Text { width: parent.width; elide: Text.ElideRight
                               text: galCard.set.name + "  ·  <i>" + galCard.set.group + "</i>"
                               textFormat: Text.StyledText
                               color: galCard.selected ? pal.gilt3 : pal.inkLabel
                               font.family: pal.fell; font.pixelSize: theme.fontSmall }
                    }
                }
            }
        }
    }

    Connections {
        target: mail
        function onAccountChanged() {
            galRoleEdit.text = mail.accountRole
            galSigEdit.text  = mail.accountSignature
        }
    }
}
