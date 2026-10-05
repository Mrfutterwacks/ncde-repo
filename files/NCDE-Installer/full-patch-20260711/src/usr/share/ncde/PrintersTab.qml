// PrintersTab.qml — CUPS printer list, default printer, add/remove.
// Backend (guarded): lelan.printers (list {name, location, model, status, isDefault}),
//   lelan.setDefaultPrinter(name), lelan.removePrinter(name).
//   cups package must be added to packages.x86_64 before this is live.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: pt; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    readonly property var printers: gv(lelan,"printers",[])
    property int selectedPrinter: printers.length > 0 ? 0 : -1

    // ── Left list panel ───────────────────────────────────────────────
    Rectangle {
        id: listPanel
        anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 188; radius: 6
        color: Qt.rgba(pt.k.wine1.r, pt.k.wine1.g, pt.k.wine1.b, 0.05)
        border.color: pt.k.gilt1; border.width: 1

        Flickable {
            id: listFlick
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: parent.top; anchors.bottom: addRemRow.top
            anchors.margins: 6
            contentHeight: listCol.height; interactive: contentHeight > height
            clip: true

            Column {
                id: listCol; width: parent.width; spacing: 2

                Repeater {
                    model: pt.printers
                    Rectangle {
                        property bool sel: pt.selectedPrinter === index
                        width: listCol.width; height: 48; radius: 6
                        color: sel ? pt.k.gilt4 : (rowHov.hovered ? Qt.rgba(pt.k.gilt4.r, pt.k.gilt4.g, pt.k.gilt4.b, 0.22) : "transparent")
                        border.color: sel ? pt.k.gilt2 : "transparent"; border.width: 1

                        Row {
                            anchors.left: parent.left; anchors.leftMargin: 10
                            anchors.right: parent.right; anchors.rightMargin: 8
                            anchors.verticalCenter: parent.verticalCenter; spacing: 6

                            Column {
                                width: parent.width - 18; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                                Text {
                                    width: parent.width
                                    text: modelData.name; elide: Text.ElideRight
                                    color: sel ? pt.k.wine1 : pt.k.ink
                                    font.family: sel ? pt.k.titles : pt.k.serif; font.pixelSize: k.sm; font.bold: sel
                                }
                                Text {
                                    width: parent.width
                                    text: modelData.status || "Ready"; elide: Text.ElideRight
                                    color: sel ? pt.k.wine2 : pt.k.inkSoft
                                    font.family: pt.k.fell; font.italic: true; font.pixelSize: k.sm
                                }
                            }

                            // Default star
                            Text {
                                visible: modelData.isDefault; text: "★"
                                color: pt.k.gilt2; font.pixelSize: k.sm
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }

                        // Status dot
                        Rectangle {
                            anchors.right: parent.right; anchors.rightMargin: 8; anchors.top: parent.top; anchors.topMargin: 8
                            width: 8; height: 8; radius: 4
                            color: modelData.status === "Error"    ? pt.k.rose  :
                                   modelData.status === "Printing" ? pt.k.amber : pt.k.verd
                        }

                        HoverHandler { id: rowHov }
                        TapHandler { onTapped: pt.selectedPrinter = index }
                    }
                }

                Text {
                    visible: pt.printers.length === 0
                    width: listCol.width; wrapMode: Text.WordWrap
                    text: "No printers installed."; leftPadding: 10; topPadding: 12
                    color: pt.k.inkSoft; font.family: pt.k.fell; font.italic: true; font.pixelSize: k.sm
                }
            }
        }

        // Add / Remove row
        Row {
            id: addRemRow
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            anchors.margins: 6; height: 32; spacing: 6

            Rectangle {
                width: 28; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
                color: Qt.rgba(pt.k.gilt1.r, pt.k.gilt1.g, pt.k.gilt1.b, 0.12)
                border.color: pt.k.gilt1; border.width: 1
                Text { anchors.centerIn: parent; text: "+"; color: pt.k.gilt1; font.pixelSize: k.lg; font.bold: true }
                TapHandler {
                    onTapped: Qt.openUrlExternally("http://localhost:631/admin")
                }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }

            Rectangle {
                width: 28; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
                enabled: pt.selectedPrinter >= 0 && pt.printers.length > 0
                opacity: enabled ? 1.0 : 0.4
                color: Qt.rgba(pt.k.rose.r, pt.k.rose.g, pt.k.rose.b, 0.12)
                border.color: pt.k.rose; border.width: 1
                Text { anchors.centerIn: parent; text: "−"; color: pt.k.rose; font.pixelSize: k.lg; font.bold: true }
                TapHandler {
                    onTapped: {
                        if(pt.selectedPrinter >= 0 && pt.printers.length > pt.selectedPrinter)
                            if(typeof lelan.removePrinter==="function") lelan.removePrinter(pt.printers[pt.selectedPrinter].name)
                    }
                }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }
        }
    }

    // ── Right detail panel ────────────────────────────────────────────
    Item {
        anchors.left: listPanel.right; anchors.leftMargin: 8
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom

        // Empty state
        Column {
            anchors.centerIn: parent; spacing: 10
            visible: pt.selectedPrinter < 0 || pt.printers.length === 0

            Text { anchors.horizontalCenter: parent.horizontalCenter
                   text: "No printers installed."; color: pt.k.gilt1; font.family: pt.k.display; font.bold: true; font.pixelSize: k.md }
            Text { anchors.horizontalCenter: parent.horizontalCenter
                   text: "Click \"+\" to open the printer manager in your browser. You may be asked for an administrator name and password."; color: pt.k.inkSoft; font.family: pt.k.fell; font.italic: true; font.pixelSize: k.sm }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 160; height: 30; radius: 4
                color: Qt.rgba(pt.k.gilt1.r, pt.k.gilt1.g, pt.k.gilt1.b, 0.12)
                border.color: pt.k.gilt1; border.width: 1
                Text { anchors.centerIn: parent; text: "Add Printer"
                       color: pt.k.gilt1; font.family: pt.k.titles; font.pixelSize: k.sm; font.bold: true }
                TapHandler {
                    onTapped: Qt.openUrlExternally("http://localhost:631/admin")
                }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }
        }

        // Detail view
        Flickable {
            anchors.fill: parent; contentHeight: detCol.height; interactive: contentHeight > height
            visible: pt.selectedPrinter >= 0 && pt.printers.length > 0
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: detCol; width: parent.width; spacing: 14

                property var p: (pt.selectedPrinter >= 0 && pt.printers.length > pt.selectedPrinter)
                                ? pt.printers[pt.selectedPrinter] : null

                Text { text: "Printer"; color: pt.k.wine2; font.family: pt.k.display; font.bold: true; font.pixelSize: k.lg }

                // Printer name heading
                Text {
                    text: detCol.p ? (detCol.p.name || "") : ""
                    color: pt.k.ink; font.family: pt.k.titles; font.bold: true; font.pixelSize: k.lg
                }

                // Details grid
                Repeater {
                    model: detCol.p ? [
                        { label: "Location", value: detCol.p.location || "—" },
                        { label: "Model",    value: detCol.p.model    || "—" },
                        { label: "Status",   value: detCol.p.status   || "Ready" }
                    ] : []
                    Item {
                        width: detCol.width; height: 26
                        Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                               text: modelData.label; width: 90
                               color: pt.k.inkSoft; font.family: pt.k.fell; font.italic: true; font.pixelSize: k.sm }
                        Text { anchors.left: parent.left; anchors.leftMargin: 96; anchors.verticalCenter: parent.verticalCenter
                               text: modelData.value
                               color: pt.k.ink; font.family: pt.k.serif; font.pixelSize: k.md }
                    }
                }

                Rectangle { width: parent.width; height: 1; color: pt.k.gilt1; opacity: 0.4 }

                // Set as Default button
                Rectangle {
                    width: 160; height: 30; radius: 4
                    enabled: detCol.p && !detCol.p.isDefault
                    opacity: enabled ? 1.0 : 0.5
                    color: (detCol.p && detCol.p.isDefault)
                           ? Qt.rgba(pt.k.gilt1.r, pt.k.gilt1.g, pt.k.gilt1.b, 0.08)
                           : Qt.rgba(pt.k.gilt1.r, pt.k.gilt1.g, pt.k.gilt1.b, 0.15)
                    border.color: pt.k.gilt1; border.width: 1
                    Text { anchors.centerIn: parent
                           text: (detCol.p && detCol.p.isDefault) ? "★ Default Printer" : "Set as Default"
                           color: pt.k.gilt1; font.family: pt.k.titles; font.pixelSize: k.sm; font.bold: true }
                    TapHandler {
                        onTapped: {
                            if(detCol.p && !detCol.p.isDefault && typeof lelan.setDefaultPrinter==="function")
                                lelan.setDefaultPrinter(detCol.p.name)
                        }
                    }
                    HoverHandler { cursorShape: Qt.PointingHandCursor }
                }

                Item { width: 1; height: 8 }
            }
        }
    }
}
