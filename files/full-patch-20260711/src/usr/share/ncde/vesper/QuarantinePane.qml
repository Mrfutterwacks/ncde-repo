import QtQuick

// QuarantinePane — the review surface for what Vesper has sealed away.
// Punchlist §2.8: the backend (/quarantine endpoints) and the terminal commands
// were already real; the window just never had a pane (showQuarantine unused).
// Pure surface over backend.quarantine — RESTORE puts the file back exactly
// where it was; REMOVE destroys it for good, behind a two-tap confirm (the
// binnie EMPTY-veil rule: no one-tap irreversible action).
Item {
    id: pane
    property var tokens
    property var backend
    signal closed()

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0.02, 0.10, 0.07, 0.94)
        border.color: tokens.p; border.width: 1; radius: tokens.radius
    }

    Column {
        id: head
        x: tokens.pad; y: tokens.pad
        width: parent.width - tokens.pad*2
        spacing: tokens.fs(6)
        Item {
            width: parent.width; height: tokens.fs(38)
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "QUARANTINE // " + backend.quarantine.length + " HELD"
                color: tokens.pHi; font.family: tokens.mono
                font.pixelSize: tokens.body; font.letterSpacing: 3
            }
            VesperButton {
                anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                tokens: pane.tokens; label: "CLOSE"; ghost: true
                onClicked: pane.closed()
            }
        }
        Text {
            width: parent.width; wrapMode: Text.WordWrap
            visible: backend.quarantine.length > 0
            text: "Everything here is sealed read-only and fully reversible. Restore puts a file back exactly where it was; remove destroys it for good."
            color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small
        }
    }

    Text {
        anchors.centerIn: parent
        visible: backend.quarantine.length === 0
        text: "Quarantine's empty — nothing held."
        color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.body
    }

    ListView {
        id: list
        x: tokens.pad; width: parent.width - tokens.pad*2
        anchors.top: head.bottom; anchors.topMargin: tokens.fs(10)
        anchors.bottom: parent.bottom; anchors.bottomMargin: tokens.pad
        clip: true; spacing: tokens.fs(8)
        model: backend.quarantine

        delegate: Item {
            width: list.width
            height: rowCol.implicitHeight + tokens.fs(16)
            property bool removeArmed: false    // two-tap confirm; re-created (disarmed) on every refresh

            Rectangle {
                anchors.fill: parent; radius: tokens.radius
                color: Qt.rgba(0, 0, 0, 0.25)
                border.color: removeArmed ? tokens.danger : tokens.pDim; border.width: 1
            }
            Column {
                id: rowCol
                x: tokens.fs(12); y: tokens.fs(8)
                width: parent.width - tokens.fs(24)
                spacing: tokens.fs(2)
                Text {
                    width: parent.width; elide: Text.ElideMiddle
                    text: (modelData.original || "").split("/").pop()
                    color: tokens.pHi; font.family: tokens.mono; font.pixelSize: tokens.body
                }
                Text {
                    width: parent.width; elide: Text.ElideMiddle
                    text: (modelData.signature || modelData.engine || "held")
                          + "  ·  " + (modelData.original || "")
                          + "  ·  sealed " + new Date((modelData.time || 0) * 1000).toLocaleDateString()
                    color: tokens.pDim; font.family: tokens.mono; font.pixelSize: tokens.small
                }
                Row {
                    spacing: tokens.fs(10); topPadding: tokens.fs(6)
                    VesperButton {
                        tokens: pane.tokens; label: "RESTORE"
                        onClicked: backend.restore(modelData.id)
                    }
                    VesperButton {
                        tokens: pane.tokens
                        label: removeArmed ? "REMOVE — SURE?" : "REMOVE"
                        accent: tokens.danger; ghost: !removeArmed
                        onClicked: {
                            if (!removeArmed) { removeArmed = true; return }
                            backend.remove(modelData.id)
                        }
                    }
                    VesperButton {
                        tokens: pane.tokens; label: "KEEP"; ghost: true
                        visible: removeArmed
                        onClicked: removeArmed = false
                    }
                }
            }
        }
    }
}
