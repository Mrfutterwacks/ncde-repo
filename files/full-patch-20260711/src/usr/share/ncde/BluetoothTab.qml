// BluetoothTab.qml — Bluetooth on/off, discoverable, my (paired) devices, nearby devices, pairing.
// Backend — Lelan owns Bluetooth (lelan.md §4); ncde is the colour engine only
// (NCDE-ARCHITECTURE-DIGEST §2), so nothing here goes through ncde (rewired 2026-09-30):
//   lelan.bluetoothEnabled, lelan.setBluetoothEnabled(on), lelan.bluetoothDiscoverable,
//   lelan.setBluetoothDiscoverable(on), lelan.bluetoothDevices (list {name, address, type, paired, connected}),
//   lelan.bluetoothConnect/Disconnect/Pair/Remove(address), lelan.bluetoothScan() (stops by itself after 30 s),
//   lelan.bluetoothScanning, lelan.bluetoothFailed(address, reason),
//   lelan.bluetoothPairing ({kind: confirm|pin|passkey|authorize|display, address, name, code}; {} = none),
//   lelan.bluetoothPairingReply(accept, value) — NCDE's own pairing agent (org.bluez.Agent1).
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: bt; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    readonly property bool btOn:     gv(lelan,"bluetoothEnabled",false)
    readonly property bool diskov:   gv(lelan,"bluetoothDiscoverable",false)
    readonly property bool scanning: gv(lelan,"bluetoothScanning",false)
    readonly property var  devices:  gv(lelan,"bluetoothDevices",[])
    readonly property var  pairing:  gv(lelan,"bluetoothPairing",({}))
    readonly property var  mine:     devices.filter(function(d){ return d.paired })
    readonly property var  nearby:   devices.filter(function(d){ return !d.paired })

    // last failure: address "" = the adapter itself (power, scan)
    property string failAddress: ""
    property string failReason: ""
    Connections {
        target: (typeof lelan !== "undefined") ? lelan : null
        ignoreUnknownSignals: true
        function onBluetoothFailed(address, reason) { bt.failAddress = address; bt.failReason = reason }
    }
    function clearFail() { bt.failAddress = ""; bt.failReason = "" }

    function glyph(type) {
        return type === "headset"  ? "♪" : type === "keyboard" ? "⌨" : type === "mouse"   ? "◔" :
               type === "gamepad"  ? "✚" : type === "phone"    ? "☎" : type === "computer" ? "▭" :
               type === "tablet"   ? "▯" : "●"
    }

    // a small bordered button, text centred; `danger` = rose
    component PillButton: Rectangle {
        id: pill
        property string label
        property bool danger: false
        property bool enabledState: true
        signal clicked()
        width: Math.max(84, pillText.implicitWidth + 24); height: 26; radius: 4
        opacity: enabledState ? 1.0 : 0.45
        color: Qt.rgba((danger ? SetTheme.rose : SetTheme.gilt1).r, (danger ? SetTheme.rose : SetTheme.gilt1).g, (danger ? SetTheme.rose : SetTheme.gilt1).b, pillHov.hovered && enabledState ? 0.22 : 0.12)
        border.color: danger ? SetTheme.rose : SetTheme.gilt1; border.width: 1
        Text { id: pillText; anchors.centerIn: parent; text: pill.label
               font.family: SetTheme.titles; font.pixelSize: SetTheme.sm; font.bold: true; color: pill.danger ? SetTheme.rose : SetTheme.gilt1 }
        HoverHandler { id: pillHov; cursorShape: pill.enabledState ? Qt.PointingHandCursor : Qt.ArrowCursor }
        TapHandler { enabled: pill.enabledState; onTapped: pill.clicked() }
    }

    // one device row: glyph + name/status on the left, buttons on the right; the name is elided to the
    // space the buttons leave (no overlap)
    component DeviceRow: Item {
        id: row
        property var dev
        property var tab                          // the BluetoothTab (failure state, clearFail, glyph)
        width: parent ? parent.width : 0; height: 44 + (failLine.visible ? failLine.height + 4 : 0)
        Rectangle {
            id: card
            width: parent.width; height: 44; radius: 8
            color: Qt.rgba(SetTheme.paper0.r, SetTheme.paper0.g, SetTheme.paper0.b, 0.22); border.color: SetTheme.gilt1; border.width: 1
            Rectangle {
                id: badge
                anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter
                width: 28; height: 28; radius: 14
                color: Qt.rgba(SetTheme.gilt1.r, SetTheme.gilt1.g, SetTheme.gilt1.b, 0.15); border.color: SetTheme.gilt1; border.width: 1
                Text { anchors.centerIn: parent; font.pixelSize: SetTheme.sm; color: SetTheme.gilt1; text: row.tab.glyph(row.dev.type) }
            }
            Column {
                anchors.left: badge.right; anchors.leftMargin: 10; anchors.right: buttons.left; anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter; spacing: 2
                Text { width: parent.width; elide: Text.ElideRight
                       text: row.dev.name || row.dev.address
                       color: SetTheme.ink; font.family: SetTheme.titles; font.pixelSize: SetTheme.md; font.bold: true }
                Text { visible: !!row.dev.connected; text: "Connected"
                       color: SetTheme.verd; font.family: SetTheme.fell; font.italic: true; font.pixelSize: SetTheme.sm }
            }
            Row {
                id: buttons
                anchors.right: parent.right; anchors.rightMargin: 12; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                PillButton {
                    visible: !!row.dev.paired
                    label: row.dev.connected ? "Disconnect" : "Connect"
                    onClicked: { row.tab.clearFail(); row.dev.connected ? lelan.bluetoothDisconnect(row.dev.address) : lelan.bluetoothConnect(row.dev.address) }
                }
                PillButton {
                    visible: !row.dev.paired
                    label: "Pair"
                    onClicked: { row.tab.clearFail(); lelan.bluetoothPair(row.dev.address) }
                }
                PillButton {
                    visible: !!row.dev.paired
                    width: 26; label: "×"; danger: true
                    onClicked: { row.tab.clearFail(); lelan.bluetoothRemove(row.dev.address) }
                }
            }
        }
        Text {
            id: failLine
            anchors.top: card.bottom; anchors.topMargin: 4; x: 12; width: parent.width - 24; wrapMode: Text.WordWrap
            visible: row.tab.failReason !== "" && row.tab.failAddress === row.dev.address
            text: row.tab.failReason
            color: SetTheme.wine2; font.family: SetTheme.fell; font.italic: true; font.pixelSize: SetTheme.sm
        }
    }

    Flickable {
        anchors.fill: parent; contentHeight: col.height; interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: col; width: parent.width; spacing: 14

            Text { text: "Bluetooth"; color: bt.k.wine2; font.family: bt.k.display; font.bold: true; font.pixelSize: k.lg }
            Text { text: "Pair and connect Bluetooth devices."; color: bt.k.inkSoft; font.family: bt.k.fell; font.italic: true; font.pixelSize: k.md }

            // ── Pairing prompt (NCDE's pairing agent asks here) ──────
            Rectangle {
                id: prompt
                readonly property string kind: bt.pairing.kind || ""
                visible: kind !== ""
                width: parent.width; height: promptCol.height + 24; radius: 8
                color: Qt.rgba(bt.k.gilt4.r, bt.k.gilt4.g, bt.k.gilt4.b, 0.30); border.color: bt.k.gilt2; border.width: 1.5
                onKindChanged: { codeInput.text = ""; if (kind === "pin" || kind === "passkey") codeInput.forceActiveFocus() }
                Column {
                    id: promptCol
                    anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.margins: 12; spacing: 10
                    Text {
                        width: parent.width; wrapMode: Text.WordWrap
                        color: bt.k.ink; font.family: bt.k.titles; font.pixelSize: k.md; font.bold: true
                        text: {
                            var n = bt.pairing.name || bt.pairing.address || "the device"
                            return prompt.kind === "confirm"   ? "Pairing with " + n + ". Does it show this code?" :
                                   prompt.kind === "display"   ? "Type this code on " + n + ", then press Enter there." :
                                   prompt.kind === "pin"       ? "Enter the PIN for " + n + "." :
                                   prompt.kind === "passkey"   ? "Enter the 6-digit code shown on " + n + "." :
                                   prompt.kind === "authorize" ? "Allow " + n + " to pair with this computer?" : ""
                        }
                    }
                    Text {
                        visible: prompt.kind === "confirm" || prompt.kind === "display"
                        text: bt.pairing.code || ""
                        color: bt.k.wine2; font.family: bt.k.mono; font.pixelSize: k.lg * 1.4; font.letterSpacing: 4
                    }
                    Rectangle {
                        visible: prompt.kind === "pin" || prompt.kind === "passkey"
                        width: 180; height: 30; radius: 4; color: bt.k.paper0; border.color: bt.k.gilt1; border.width: 1.5
                        TextInput {
                            id: codeInput
                            anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                            maximumLength: prompt.kind === "passkey" ? 6 : 16
                            inputMethodHints: prompt.kind === "passkey" ? Qt.ImhDigitsOnly : Qt.ImhNone
                            validator: RegularExpressionValidator { regularExpression: prompt.kind === "passkey" ? /[0-9]{0,6}/ : /.{0,16}/ }
                            color: bt.k.ink; font.family: bt.k.mono; font.pixelSize: k.md
                            onAccepted: lelan.bluetoothPairingReply(true, text)
                        }
                    }
                    Row {
                        spacing: 10
                        PillButton {
                            visible: prompt.kind !== "display"
                            label: prompt.kind === "confirm" ? "Yes, it matches" : prompt.kind === "authorize" ? "Allow" : "Pair"
                            enabledState: prompt.kind !== "passkey" || codeInput.text.length === 6
                            onClicked: lelan.bluetoothPairingReply(true, codeInput.text)
                        }
                        PillButton {
                            label: prompt.kind === "display" ? "Cancel pairing" : prompt.kind === "confirm" ? "No" : "Cancel"
                            danger: true
                            onClicked: lelan.bluetoothPairingReply(false, "")
                        }
                    }
                }
            }

            // ── On/Off ────────────────────────────────────────────────
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Bluetooth"; color: bt.k.ink; font.family: bt.k.titles; font.pixelSize: k.md }
                NCDEToggle {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    checked: bt.btOn
                    onToggled: function(v){ bt.clearFail(); lelan.setBluetoothEnabled(v) }
                }
            }

            Item {
                width: parent.width; height: 30; visible: bt.btOn
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Discoverable"; color: bt.k.ink; font.family: bt.k.titles; font.pixelSize: k.md }
                NCDEToggle {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    checked: bt.diskov
                    onToggled: function(v){ bt.clearFail(); lelan.setBluetoothDiscoverable(v) }
                }
            }

            // adapter-level failure (power, scan): no device address
            Text {
                visible: bt.failReason !== "" && bt.failAddress === ""
                width: parent.width; wrapMode: Text.WordWrap; text: bt.failReason
                color: bt.k.wine2; font.family: bt.k.fell; font.italic: true; font.pixelSize: k.sm
            }

            // ── My Devices (paired) ───────────────────────────────────
            Rectangle { width: parent.width; height: 1; color: bt.k.gilt1; opacity: 0.4; visible: bt.btOn }
            Text {
                visible: bt.btOn
                text: "MY DEVICES"; color: bt.k.gilt1; font.family: bt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
            }
            Repeater {
                model: bt.btOn ? bt.mine : []
                DeviceRow { dev: modelData; tab: bt }
            }
            Text {
                visible: bt.btOn && bt.mine.length === 0
                text: "No paired devices."; color: bt.k.inkSoft; font.family: bt.k.fell; font.italic: true; font.pixelSize: k.md
            }

            // ── Nearby (found by a scan, not paired) ─────────────────
            Rectangle { width: parent.width; height: 1; color: bt.k.gilt1; opacity: 0.4; visible: bt.btOn }
            Item {
                visible: bt.btOn; width: parent.width; height: 30
                Text {
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    text: "NEARBY DEVICES"; color: bt.k.gilt1; font.family: bt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
                }
                PillButton {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    width: 150
                    label: bt.scanning ? "Scanning…" : "Scan for Devices"
                    enabledState: !bt.scanning
                    onClicked: { bt.clearFail(); lelan.bluetoothScan() }
                }
            }
            Repeater {
                model: bt.btOn ? bt.nearby : []
                DeviceRow { dev: modelData; tab: bt }
            }
            Text {
                visible: bt.btOn && bt.nearby.length === 0
                text: bt.scanning ? "Looking for devices… put yours in pairing mode."
                                  : "Press Scan to find devices in pairing mode."
                color: bt.k.inkSoft; font.family: bt.k.fell; font.italic: true; font.pixelSize: k.md
            }

            // ── Off state ─────────────────────────────────────────────
            Text {
                visible: !bt.btOn
                text: "Turn on Bluetooth to connect devices."
                color: bt.k.inkSoft; font.family: bt.k.fell; font.italic: true; font.pixelSize: k.md
            }

            Item { width: 1; height: 8 }
        }
    }
}
