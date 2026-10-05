// NetworkTab.qml — WiFi, Ethernet, VPN interface list + proxy settings.
// Backend (guarded) — Lelan owns the network (lelan.md §4); ncde is the colour engine only
// (NCDE-ARCHITECTURE-DIGEST §2), so nothing here goes through ncde (rewired 2026-09-30):
//   lelan.wifiEnabled, lelan.setWifiEnabled(on), lelan.wifiNetworks (list {ssid, signal, secured, connected, saved}),
//   lelan.activeNetwork ({ssid, ip, speed}; {} when not connected), lelan.connectWifi(ssid, pwd),
//   lelan.disconnectWifi(), lelan.wifiConnectFailed(ssid, reason),
//   lelan.wiredNetwork ({present, connected, iface, ip, speed}),
//   lelan.vpnConnections (list {name, type, connected}), lelan.connectVpn(name), lelan.disconnectVpn(name),
//   lelan.importVpn(file) -> vpnImportFinished(ok, message), lelan.removeVpn(name).
//   settings.proxyEnabled, settings.proxyHost, settings.proxyPort, settings.saveNetwork().
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs

Item {
    id: nt; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }
    function save(){ if(typeof settings.saveNetwork==="function") settings.saveNetwork() }

    // Interface selection: 0=WiFi, 1=Ethernet, 2+=VPN
    property int selectedIface: 0

    // WiFi state
    readonly property bool   wifiOn:   gv(lelan,"wifiEnabled",false)
    readonly property var    networks: gv(lelan,"wifiNetworks",[])
    // activeNetwork is {} (not null) when disconnected: an object is always truthy in JS, so the
    // connected card, the "On, not connected" label and the green dot key off the SSID instead.
    readonly property var    activeMap: gv(lelan,"activeNetwork",({}))
    readonly property var    active:   (activeMap && activeMap.ssid) ? activeMap : null

    // Ethernet (the cable, not the Wi-Fi record)
    readonly property var    wired:    gv(lelan,"wiredNetwork",({}))
    readonly property bool   wiredUp:  !!(wired && wired.connected)

    // Last failed Wi-Fi join, shown under that network's password box
    property string joinErrorSsid: ""
    property string joinError: ""
    Connections {
        target: (typeof lelan !== "undefined") ? lelan : null
        ignoreUnknownSignals: true
        function onWifiConnectFailed(ssid, reason) { nt.joinErrorSsid = ssid; nt.joinError = reason }
        function onVpnImportFinished(ok, message) {
            if (typeof notifications !== "undefined")
                notifications.notify(ok ? "VPN Imported" : "VPN Import Failed", message, "", ok ? 4000 : 8000)
        }
    }

    // VPN entries
    readonly property var vpnConns: gv(lelan,"vpnConnections",[])

    // Interface model: WiFi + Ethernet + VPN entries
    function buildIfaces() {
        var list = [
            { label: "Wi-Fi",   type: "wifi" },
            { label: "Ethernet", type: "ethernet" }
        ]
        for (var i = 0; i < nt.vpnConns.length; i++)
            list.push({ label: nt.vpnConns[i].name || ("VPN " + i), type: "vpn", idx: i })
        return list
    }
    readonly property var ifaces: buildIfaces()

    // Selected network in WiFi list
    property int  selectedNet:     -1
    property string connectSsid:   ""
    property string connectPwd:    ""

    // ── Left interface list ───────────────────────────────────────────
    Rectangle {
        id: listPanel
        anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
        width: 188; radius: 6
        color: Qt.rgba(nt.k.wine1.r, nt.k.wine1.g, nt.k.wine1.b, 0.05)
        border.color: nt.k.gilt1; border.width: 1

        Flickable {
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: parent.top; anchors.bottom: addVpnRow.top
            anchors.margins: 6
            contentHeight: ifaceCol.height; interactive: contentHeight > height; clip: true

            Column {
                id: ifaceCol; width: parent.width; spacing: 2

                Repeater {
                    model: nt.ifaces
                    Rectangle {
                        property bool sel: nt.selectedIface === index
                        width: ifaceCol.width; height: 44; radius: 6
                        color: sel ? nt.k.gilt4 : (iHov.hovered ? Qt.rgba(nt.k.gilt4.r, nt.k.gilt4.g, nt.k.gilt4.b, 0.22) : "transparent")
                        border.color: sel ? nt.k.gilt2 : "transparent"; border.width: 1

                        Row {
                            anchors.fill: parent; anchors.margins: 10; spacing: 8

                            // Type icon
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                font.pixelSize: k.lg; color: sel ? nt.k.wine1 : nt.k.gilt1
                                text: modelData.type === "wifi"     ? "⌘" :
                                      modelData.type === "ethernet" ? "⊟" : "⊕"
                            }

                            Column {
                                width: parent.width - 28; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                                Text {
                                    width: parent.width; elide: Text.ElideRight
                                    text: modelData.label
                                    color: sel ? nt.k.wine1 : nt.k.ink
                                    font.family: sel ? nt.k.titles : nt.k.serif; font.pixelSize: k.md; font.bold: sel
                                }
                                Text {
                                    width: parent.width; elide: Text.ElideRight
                                    font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm
                                    color: sel ? nt.k.wine2 : nt.k.inkSoft
                                    text: modelData.type === "wifi" ?
                                              (nt.wifiOn ? (nt.active ? nt.active.ssid : "On, not connected") : "Off") :
                                          modelData.type === "ethernet" ? (!nt.wired.present ? "No Ethernet port" : nt.wiredUp ? "Connected" : "Cable unplugged") :
                                          (nt.vpnConns.length > (modelData.idx||0) && nt.vpnConns[modelData.idx||0].connected ? "Connected" : "Disconnected")
                                }
                            }
                        }

                        // Status dot
                        Rectangle {
                            anchors.right: parent.right; anchors.rightMargin: 8; anchors.top: parent.top; anchors.topMargin: 8
                            width: 8; height: 8; radius: 4
                            color: modelData.type === "wifi"     ? (nt.active ? nt.k.verd : (nt.wifiOn ? nt.k.amber : nt.k.inkSoft)) :
                                   modelData.type === "ethernet" ? (nt.wiredUp ? nt.k.verd : nt.k.inkSoft) :
                                   (nt.vpnConns.length > (modelData.idx||0) && nt.vpnConns[modelData.idx||0].connected ? nt.k.verd : nt.k.inkSoft)
                        }

                        HoverHandler { id: iHov }
                        TapHandler { onTapped: { nt.selectedIface = index; nt.selectedNet = -1 } }
                    }
                }
            }
        }

        // Import VPN — was a hidden nmtui launch (dead: curses app with no terminal). Now native:
        // lelan.importVpn(file) adds an OpenVPN .ovpn or WireGuard .conf; the result arrives as
        // vpnImportFinished (notification above). Imported VPNs never connect by themselves.
        FileDialog {
            id: vpnFileDialog
            title: "Import VPN"
            currentFolder: "file:///home/" + settings.userName
            nameFilters: ["VPN files (*.ovpn *.conf)", "OpenVPN (*.ovpn)", "WireGuard (*.conf)"]
            onAccepted: lelan.importVpn(vpnFileDialog.selectedFile.toString())
        }
        Item {
            id: addVpnRow
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            anchors.margins: 6; height: 34

            Rectangle {
                width: parent.width; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
                color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.1)
                border.color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.4); border.width: 1
                Text { anchors.centerIn: parent; text: "+ Import VPN…"
                       color: nt.k.gilt1; font.family: nt.k.titles; font.pixelSize: k.sm }
                TapHandler { onTapped: vpnFileDialog.open() }
                HoverHandler { cursorShape: Qt.PointingHandCursor }
            }
        }
    }

    // ── Right config panel ────────────────────────────────────────────
    Item {
        anchors.left: listPanel.right; anchors.leftMargin: 8
        anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom

        // ── WiFi panel ────────────────────────────────────────────────
        Flickable {
            anchors.fill: parent; contentHeight: wifiCol.height; interactive: contentHeight > height
            visible: nt.ifaces.length > nt.selectedIface && nt.ifaces[nt.selectedIface].type === "wifi"
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: wifiCol; width: parent.width; spacing: 14

                Text { text: "Wi-Fi"; color: nt.k.wine2; font.family: nt.k.display; font.bold: true; font.pixelSize: k.lg }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Wi-Fi"; color: nt.k.ink; font.family: nt.k.titles; font.pixelSize: k.md }
                    NCDEToggle {
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        checked: nt.wifiOn
                        onToggled: function(v){ lelan.setWifiEnabled(v) }
                    }
                }

                // Active connection info
                Rectangle {
                    visible: nt.wifiOn && nt.active !== null
                    width: parent.width; height: 44; radius: 8
                    color: Qt.rgba(nt.k.verd.r, nt.k.verd.g, nt.k.verd.b, 0.08)
                    border.color: nt.k.verd; border.width: 1
                    Row {
                        anchors.fill: parent; anchors.margins: 12; spacing: 12
                        Rectangle { width: 8; height: 8; radius: 4; color: nt.k.verd; anchors.verticalCenter: parent.verticalCenter }
                        Column { anchors.verticalCenter: parent.verticalCenter; spacing: 2
                            Text { text: nt.active ? nt.active.ssid : ""; color: nt.k.ink; font.family: nt.k.titles; font.bold: true; font.pixelSize: k.md }
                            Text { text: nt.active ? ("IP: " + (nt.active.ip||"")) : ""; color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm }
                        }
                    }
                    // Anchored children are illegal inside a Row (it disabled the
                    // Row's layout, journal-warned every visit) — the button sits
                    // as a card sibling, same place on screen.
                    Rectangle {
                        anchors.right: parent.right; anchors.rightMargin: 12
                        anchors.verticalCenter: parent.verticalCenter
                        width: 90; height: 26; radius: 4
                        color: Qt.rgba(nt.k.wine2.r, nt.k.wine2.g, nt.k.wine2.b, 0.12)
                        border.color: nt.k.wine2; border.width: 1
                        Text { anchors.centerIn: parent; text: "Disconnect"; color: nt.k.wine2; font.family: nt.k.titles; font.pixelSize: k.sm; font.bold: true }
                        TapHandler { onTapped: lelan.disconnectWifi() }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                }

                // Network scan list
                Text {
                    visible: nt.wifiOn
                    text: "AVAILABLE NETWORKS"; color: nt.k.gilt1; font.family: nt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
                }

                Repeater {
                    model: nt.wifiOn ? nt.networks : []
                    Column {
                        id: netRow
                        width: wifiCol.width; spacing: 0
                        // the network this row shows (inside the bars' own Repeater, modelData is the
                        // bar number, so the bars read the network through this)
                        readonly property var net: modelData
                        // a password is asked only when one is needed: secured and not saved, or the
                        // last join of this network failed
                        readonly property bool needsPassword: !!modelData.secured
                            && (!modelData.saved || nt.joinErrorSsid === (modelData.ssid || ""))

                        Rectangle {
                            width: parent.width; height: 44; radius: 8
                            color: nt.selectedNet === index
                                   ? Qt.rgba(nt.k.gilt4.r, nt.k.gilt4.g, nt.k.gilt4.b, 0.25)
                                   : (netHov.hovered ? Qt.rgba(1,1,1,0.18) : Qt.rgba(1,1,1,0.12))
                            border.color: nt.selectedNet === index ? nt.k.gilt2 : Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.35)
                            border.width: 1

                            Row {
                                anchors.fill: parent; anchors.margins: 12; spacing: 10

                                // Signal bars (4 rectangles)
                                Row {
                                    spacing: 2; anchors.verticalCenter: parent.verticalCenter
                                    Repeater {
                                        model: 4
                                        Rectangle {
                                            width: 4; height: 6 + index*4; radius: 1
                                            anchors.bottom: parent.bottom
                                            color: {
                                                var sig = netRow.net.signal || 0
                                                var lit = sig >= 75 ? 4 : sig >= 50 ? 3 : sig >= 25 ? 2 : 1
                                                return (index < lit) ? nt.k.verd : Qt.rgba(nt.k.inkSoft.r, nt.k.inkSoft.g, nt.k.inkSoft.b, 0.4)
                                            }
                                        }
                                    }
                                }

                                // Lock icon — before the name, so the selected row's button never covers it
                                Text {
                                    opacity: modelData.secured ? 1 : 0
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: "🔒"; font.pixelSize: k.sm; color: nt.k.inkSoft
                                }

                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    // bars + lock + spacing ≈ 56; the selected row's button takes 92 more
                                    width: parent.width - 56 - (nt.selectedNet === index ? 92 : 0)
                                    text: modelData.ssid || ""
                                    elide: Text.ElideRight
                                    color: modelData.connected ? nt.k.gilt1 : nt.k.ink
                                    font.family: modelData.connected ? nt.k.titles : nt.k.serif
                                    font.pixelSize: k.md; font.bold: modelData.connected
                                }

                            }

                            // Connect button (selected row only) — anchored to the
                            // row card, not inside its Row (anchors there disable
                            // the Row's layout; same fix as the Disconnect button).
                            Rectangle {
                                visible: nt.selectedNet === index
                                anchors.right: parent.right; anchors.rightMargin: 12
                                anchors.verticalCenter: parent.verticalCenter
                                width: 80; height: 26; radius: 4
                                color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.15)
                                border.color: nt.k.gilt1; border.width: 1
                                Text { anchors.centerIn: parent
                                       text: modelData.connected ? "Disconnect" : "Connect"
                                       font.family: nt.k.titles; font.pixelSize: k.sm; font.bold: true
                                       color: connBtnHov.hovered ? Qt.lighter(nt.k.gilt1, 1.45)
                                                                  : Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.65)
                                       Behavior on color { ColorAnimation { duration: 220 } } }
                                TapHandler {
                                    onTapped: {
                                        if(modelData.connected) {
                                            lelan.disconnectWifi()
                                        } else if (!netRow.needsPassword) {
                                            // open or saved network: join now
                                            nt.joinError = ""; nt.joinErrorSsid = ""
                                            lelan.connectWifi(modelData.ssid || "", "")
                                        } else {
                                            nt.connectSsid = modelData.ssid; nt.connectPwd = ""
                                            pwdInput.forceActiveFocus()
                                        }
                                    }
                                }
                                HoverHandler { id: connBtnHov; cursorShape: Qt.PointingHandCursor }
                            }

                            HoverHandler { id: netHov }
                            TapHandler { onTapped: { nt.selectedNet = index } }
                        }

                        // Inline password field
                        Rectangle {
                            // Show the password box whenever a non-connected network row is selected.
                            // (Was gated on nt.showPwdConnect, set by a separate Connect-button tap that
                            //  was unreliable — the box never appeared. Selecting the row is the reliable trigger.)
                            visible: nt.selectedNet === index && !modelData.connected && netRow.needsPassword
                            width: parent.width; height: 52; radius: 8
                            color: Qt.rgba(nt.k.paper0.r, nt.k.paper0.g, nt.k.paper0.b, 0.9)
                            border.color: nt.k.gilt1; border.width: 1

                            Row {
                                anchors.fill: parent; anchors.margins: 10; spacing: 8
                                Rectangle {
                                    width: parent.width - 86; height: 30; radius: 4; anchors.verticalCenter: parent.verticalCenter
                                    color: nt.k.paper0; border.color: nt.k.gilt1; border.width: 1.5
                                    TextInput {
                                        id: pwdInput
                                        anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                        echoMode: TextInput.Password; text: nt.connectPwd; onTextChanged: nt.connectPwd = text
                                        color: nt.k.ink; font.family: nt.k.serif; font.pixelSize: k.md
                                    }
                                    Text {
                                        anchors.fill: parent; anchors.leftMargin: 8
                                        verticalAlignment: Text.AlignVCenter
                                        text: "Password"
                                        color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.md
                                        visible: pwdInput.text === "" && !pwdInput.activeFocus
                                    }
                                }
                                Rectangle {
                                    id: joinBtn
                                    width: 70; height: 30; radius: 4; anchors.verticalCenter: parent.verticalCenter
                                    // ARMED = ready to connect: hovered, or a password has been entered.
                                    property bool armed: joinHov.hovered || pwdInput.text.length > 0
                                    scale: joinTap.pressed ? 0.90 : 1.0                       // physical click
                                    Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutBack } }
                                    color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, armed ? 0.30 : 0.12)
                                    border.color: nt.k.gilt1; border.width: armed ? 2 : 1
                                    Behavior on color { ColorAnimation { duration: 220 } }
                                    Behavior on border.width { NumberAnimation { duration: 150 } }
                                    // outer glow halo — fades in when armed (the active / non-active text glow)
                                    Rectangle {
                                        anchors.centerIn: parent; z: -1; color: "transparent"
                                        width: parent.width + 12; height: parent.height + 12
                                        radius: parent.radius + 6; border.width: 6
                                        border.color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, joinBtn.armed ? 0.40 : 0.0)
                                        Behavior on border.color { ColorAnimation { duration: 260 } }
                                    }
                                    Text { anchors.centerIn: parent; text: "Join"
                                           font.family: nt.k.titles; font.pixelSize: k.sm; font.bold: true
                                           color: joinBtn.armed ? Qt.lighter(nt.k.gilt1, 1.45)
                                                                : Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.65)
                                           Behavior on color { ColorAnimation { duration: 220 } } }
                                    TapHandler { id: joinTap
                                        onTapped: {
                                            // physical click → connect instantly (D-Bus via Lelan) + collapse the prompt
                                            nt.joinError = ""; nt.joinErrorSsid = ""
                                            lelan.connectWifi(modelData.ssid || "", pwdInput.text || "")
                                        }
                                    }
                                    HoverHandler { id: joinHov; cursorShape: Qt.PointingHandCursor }
                                }
                            }
                        }

                        // Why the last join of this network failed (lelan.wifiConnectFailed)
                        Text {
                            visible: nt.joinError !== "" && nt.joinErrorSsid === (modelData.ssid || "")
                            width: parent.width; leftPadding: 12; topPadding: 4; wrapMode: Text.WordWrap
                            text: nt.joinError
                            color: nt.k.wine2; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm
                        }
                    }
                }

                Text {
                    visible: nt.wifiOn && nt.networks.length === 0
                    text: "Scanning for networks…"; color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.md
                }
                Text {
                    visible: !nt.wifiOn
                    text: "Turn on Wi-Fi to see nearby networks."
                    color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.md
                }

                // ── Proxy ─────────────────────────────────────────────
                Rectangle { width: parent.width; height: 1; color: nt.k.gilt1; opacity: 0.4 }
                Text { text: "PROXY"; color: nt.k.gilt1; font.family: nt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Use proxy"; color: nt.k.ink; font.family: nt.k.titles; font.pixelSize: k.md }
                    NCDEToggle {
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        checked: gv(settings,"proxyEnabled",false)
                        onToggled: function(v){ settings.proxyEnabled = v; nt.save() }
                    }
                }

                Item {
                    width: parent.width; height: 30
                    visible: gv(settings,"proxyEnabled",false)
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 70; text: "Host"; color: nt.k.ink; font.family: nt.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        anchors.left: parent.left; anchors.leftMargin: 76; width: 180; height: 28; radius: 4
                        color: nt.k.paper0; border.color: nt.k.gilt1; border.width: 1.5
                        TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                    text: gv(settings,"proxyHost",""); onEditingFinished: { settings.proxyHost = text; nt.save() }
                                    color: nt.k.ink; font.family: nt.k.serif; font.pixelSize: k.md }
                    }
                    Text { anchors.left: parent.left; anchors.leftMargin: 266; anchors.verticalCenter: parent.verticalCenter
                           text: "Port"; color: nt.k.ink; font.family: nt.k.titles; font.pixelSize: k.md }
                    Rectangle {
                        anchors.left: parent.left; anchors.leftMargin: 302; width: 70; height: 28; radius: 4
                        color: nt.k.paper0; border.color: nt.k.gilt1; border.width: 1.5
                        TextInput { anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                                    text: gv(settings,"proxyPort",8080); onEditingFinished: { settings.proxyPort = parseInt(text)||8080; nt.save() }
                                    color: nt.k.ink; font.family: nt.k.serif; font.pixelSize: k.md
                                    inputMethodHints: Qt.ImhDigitsOnly }
                    }
                }

                Item { width: 1; height: 8 }
            }
        }

        // ── Ethernet panel ────────────────────────────────────────────
        Flickable {
            anchors.fill: parent; contentHeight: ethCol.height; interactive: contentHeight > height
            visible: nt.ifaces.length > nt.selectedIface && nt.ifaces[nt.selectedIface].type === "ethernet"
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: ethCol; width: parent.width; spacing: 14

                Text { text: "Ethernet"; color: nt.k.wine2; font.family: nt.k.display; font.bold: true; font.pixelSize: k.lg }
                Text { text: "Wired network connection."; color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.md }

                Rectangle {
                    // "Connected" was previously shown unconditionally just because this panel is
                    // visible (ethernet interface selected) — now reflects real connection state,
                    // same nt.active !== null check the WiFi panel already uses correctly.
                    width: parent.width; height: 54; radius: 8
                    color: Qt.rgba((nt.wiredUp ? nt.k.verd : nt.k.inkSoft).r, (nt.wiredUp ? nt.k.verd : nt.k.inkSoft).g, (nt.wiredUp ? nt.k.verd : nt.k.inkSoft).b, 0.08)
                    border.color: nt.wiredUp ? nt.k.verd : nt.k.inkSoft; border.width: 1
                    Row {
                        anchors.fill: parent; anchors.margins: 14; spacing: 10
                        Rectangle { width: 8; height: 8; radius: 4; color: nt.wiredUp ? nt.k.verd : nt.k.inkSoft; anchors.verticalCenter: parent.verticalCenter }
                        Column { anchors.verticalCenter: parent.verticalCenter; spacing: 3
                            Text { text: nt.wiredUp ? "Connected" : (nt.wired.present ? "Not connected" : "No Ethernet port"); color: nt.wiredUp ? nt.k.verd : nt.k.inkSoft; font.family: nt.k.titles; font.bold: true; font.pixelSize: k.md }
                            Text { text: nt.wiredUp ? ("IP: " + (nt.wired.ip||"—") + (nt.wired.speed ? "  ·  " + nt.wired.speed + " Mb/s" : ""))
                                                    : (nt.wired.present ? "Plug in a cable to connect" : "This computer has no Ethernet port")
                                   color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm }
                        }
                    }
                }

                Text { visible: !!nt.wired.present; text: "No configuration required for wired connections."
                       color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm; wrapMode: Text.WordWrap; width: parent.width }

                // ── Proxy (always visible) ─────────────────────────────
                Rectangle { width: parent.width; height: 1; color: nt.k.gilt1; opacity: 0.4 }
                Text { text: "PROXY"; color: nt.k.gilt1; font.family: nt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

                Item { width: parent.width; height: 30
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           text: "Use proxy"; color: nt.k.ink; font.family: nt.k.titles; font.pixelSize: k.md }
                    NCDEToggle {
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        checked: gv(settings,"proxyEnabled",false)
                        onToggled: function(v){ settings.proxyEnabled = v; nt.save() }
                    }
                }

                Item { width: 1; height: 8 }
            }
        }

        // ── VPN panel ─────────────────────────────────────────────────
        Flickable {
            anchors.fill: parent; contentHeight: vpnCol.height; interactive: contentHeight > height
            visible: nt.ifaces.length > nt.selectedIface && nt.ifaces[nt.selectedIface].type === "vpn"
            ScrollBar.vertical: NCDEScrollBar {}

            Column {
                id: vpnCol; width: parent.width; spacing: 14

                property var vpn: {
                    var iface = nt.ifaces.length > nt.selectedIface ? nt.ifaces[nt.selectedIface] : null
                    return (iface && iface.type === "vpn" && nt.vpnConns.length > (iface.idx||0))
                           ? nt.vpnConns[iface.idx||0] : null
                }

                Text { text: "VPN"; color: nt.k.wine2; font.family: nt.k.display; font.bold: true; font.pixelSize: k.lg }
                Text { text: vpnCol.vpn ? (vpnCol.vpn.name || "VPN Connection") : "VPN"
                       color: nt.k.ink; font.family: nt.k.titles; font.bold: true; font.pixelSize: k.lg }

                Item { width: parent.width; height: 26
                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                           width: 90; text: "Type"; color: nt.k.inkSoft; font.family: nt.k.fell; font.italic: true; font.pixelSize: k.sm }
                    Text { anchors.left: parent.left; anchors.leftMargin: 96; anchors.verticalCenter: parent.verticalCenter
                           text: vpnCol.vpn ? (vpnCol.vpn.type || "—") : "—"
                           color: nt.k.ink; font.family: nt.k.serif; font.pixelSize: k.md }
                }

                Row { spacing: 10
                    Rectangle {
                        width: 110; height: 30; radius: 4
                        color: Qt.rgba(nt.k.gilt1.r, nt.k.gilt1.g, nt.k.gilt1.b, 0.12)
                        border.color: nt.k.gilt1; border.width: 1
                        Text { anchors.centerIn: parent
                               text: (vpnCol.vpn && vpnCol.vpn.connected) ? "Disconnect" : "Connect"
                               color: nt.k.gilt1; font.family: nt.k.titles; font.pixelSize: k.sm; font.bold: true }
                        TapHandler {
                            onTapped: {
                                if(vpnCol.vpn) {
                                    if(vpnCol.vpn.connected) lelan.disconnectVpn(vpnCol.vpn.name)
                                    else                     lelan.connectVpn(vpnCol.vpn.name)
                                }
                            }
                        }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                    Rectangle {
                        // Was a hidden "Edit…" (dead nmtui launch). Change a VPN = Remove + Import.
                        visible: !!vpnCol.vpn
                        width: 80; height: 30; radius: 4
                        color: "transparent"; border.color: nt.k.wine2; border.width: 1
                        Text { anchors.centerIn: parent; text: "Remove"
                               color: nt.k.wine2; font.family: nt.k.titles; font.pixelSize: k.sm }
                        TapHandler { onTapped: { if (vpnCol.vpn) { lelan.removeVpn(vpnCol.vpn.name); nt.selectedIface = 0 } } }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                    }
                }

                Item { width: 1; height: 8 }
            }
        }
    }
}
