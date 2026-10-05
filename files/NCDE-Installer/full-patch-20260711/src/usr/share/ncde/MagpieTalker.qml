// ╔══════════════════════════════════════════════════════════════════════╗
// ║  MagpieTalker.qml — NCDE LAN chat · Belle Époque "office wire"         ║
// ║  Frameless native NCDE window. Context properties (set by main.cpp):   ║
// ║    hub — MessageHub (peers/channels/messages/presence over the LAN)    ║
// ║    ncde · theme · settings · launcher                                  ║
// ║  Cerulean accent (magpie-wing iridescence). TapHandler/Hover/Drag only.║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Qt.labs.platform
// Flutter call video (GstGLQt6VideoItem) — registered at RUNTIME by the GStreamer qml6 plugin,
// which main.cpp force-loads before this file. qmllint cannot see runtime registrations, so its
// "module not found" warning for this one import is expected and documented, not a break.
import org.freedesktop.gstreamer.Qt6GLVideoItem 1.0

Window {
    id: win
    visible: true
    width: 1180
    height: 760
    minimumWidth: 900
    minimumHeight: 560
    title: "Magpie Talker"
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"
    readonly property bool motionEnabled: win.visible && animPolicy.decorative
        && !animPolicy.screenIdle && !animPolicy.desktopObscured

    // ── palette (NCDEKit — responds to dark/light mode) ──────────────────
    NCDEKit { id: k }
    // Shared helper — was `Math.round(N * (theme.fontMedium / 13.0))` copy-pasted at
    // ~100 call sites. Identical formula, one definition; zero pixel-size change.
    function fpx(n) { return Math.round(n * (theme.fontMedium / 13.0)) }
    // Cerulean ramp: Concordia light = teal-to-midnight; Belle Époque dark = bright cer
    QtObject {
        id: crd
        readonly property color cer1: k.dark ? Qt.darker(k.cer, 3.0)  : k.cer
        readonly property color cer2: k.dark ? Qt.darker(k.cer, 2.0)  : k.cer
        readonly property color cer3: k.dark ? k.cer                   : k.cer
        readonly property color cer4: k.dark ? Qt.lighter(k.cer, 1.3) : k.cer
        readonly property color cer5: k.dark ? Qt.lighter(k.cer, 1.7) : k.cer
    }

    Connections {
        target: hub
        function onDhtLookupResult(cs, found) {
            win.dhtSearching = false
            win.dhtSearchStatus = found ? "" : "No one answered \"" + cs + "\" on the world band"
        }
    }

    function presColor(p){
        return p==="online" ? k.verd : p==="away" ? k.gilt3 : p==="busy" ? k.rose
             : p==="appear_offline" ? Qt.rgba(k.inkSoft.r, k.inkSoft.g, k.inkSoft.b, 0.45) : k.inkSoft
    }

    property bool composerTyping: false
    property bool firstLaunch: false
    property bool loginActive: false
    property bool addContactOpen: false
    property bool browseNearbyOpen: false
    property bool nearbyBrowsing: false
    property bool dhtSearching: false
    property string dhtSearchStatus: ""
    property bool createChanOpen: false
    property bool avatarPickerOpen: false
    property bool emojiOpen: false
    property string reactTargetMsgId: ""   // set = picker adds a reaction to this message; empty = picker inserts into composer
    property bool rosterOpen: true
    // Facebook Messenger pane (MagpieMessenger.qml) is the one on screen
    property bool fbMode: false
    property int  unreadTotal: 0
    property real nudgeX: 0
    property bool editingStatus: false
    property string ctxUuid: ""
    property bool ctxBlocked: false
    property string ctxScreenName: ""
    property bool ctxOpen: false
    property real ctxX: 0
    property real ctxY: 0

    // D-3 (MP-SEC-1): pending link state for link safety overlay
    property string linkPendingUrl:    ""
    property string linkPendingStatus: ""  // "blocked:<cat>" | ""

    // Flutter: friendly name for the call peer (uuid → screenName via the directs roster;
    // falls back to the raw id if the caller isn't a saved contact yet)
    property string callPeerName: {
        var id = hub.callPeerId
        if (!id) return ""
        var d = hub.directs
        for (var i = 0; i < d.length; i++)
            if (d[i].id === id) return d[i].screenName
        return id
    }

    // callMediaError carries a real GStreamer error string but had zero QML
    // listeners -- the "wire dropped" status line only ever showed a generic
    // fallback, never the actual reason. Cleared on the next call attempt.
    property string lastMediaError: ""

    // UTF-8 → base64url, for the magpie-notify: popup link (Messenger → dunst)
    function b64url(str) {
        var bytes = unescape(encodeURIComponent(String(str).slice(0, 400)))
        var T = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_", out = ""
        for (var i = 0; i < bytes.length; i += 3) {
            var a = bytes.charCodeAt(i), b = bytes.charCodeAt(i+1), c = bytes.charCodeAt(i+2)
            var n = (a << 16) | ((b || 0) << 8) | (c || 0)
            out += T[(n >> 18) & 63] + T[(n >> 12) & 63]
                 + (i+1 < bytes.length ? T[(n >> 6) & 63] : "") + (i+2 < bytes.length ? T[n & 63] : "")
        }
        return out
    }

    // Hyperlink plain URLs in message text so onLinkActivated fires.
    function hyperlinkify(text) {
        if (!text) return "";
        return text.replace(/(https?:\/\/[^\s<>"]+)/g,
                            '<a href="$1" style="color:' + crd.cer4 + ';">$1</a>');
    }

    // ── file picker ──────────────────────────────────────────────────────
    FileDialog {
        id: filePicker
        title: "Share a file"
        onAccepted: hub.sendFile(file.toString().replace("file://", ""))
    }
    // ── avatar picker — reuses the SAME 19 round celestial avatars + the SAME
    // ncde.setUserAvatar(name, file) call the Settings panel's Users tab uses (UsersTab.qml), instead of
    // Magpie's own separate arbitrary-photo file picker. Also still calls hub.setMeAvatar() with the
    // same resolved path so existing local display / any wire-transmission-to-peers keeps working
    // unchanged — one identity, fed to both systems, not two divergent avatar concepts.
    readonly property var avatarList: [
        "avatars/01-full-moon.svg",     "avatars/02-star-cluster.svg",
        "avatars/03-crescent-moon.svg", "avatars/04-constellation.svg",
        "avatars/05-north-star.svg",    "avatars/06-galaxy.svg",
        "avatars/07-nebula.svg",        "avatars/08-saturn.svg",
        "avatars/09-zodiac.svg",        "avatars/10-aurora.svg",
        "avatars/11-solar-system.svg",  "avatars/12-comet.svg",
        "avatars/13-eclipse.svg",       "avatars/14-sun.svg",
        "avatars/15-hsien-earth.svg",   "avatars/16-hsien-fire.svg",
        "avatars/17-hsien-metal.svg",   "avatars/18-hsien-water.svg",
        "avatars/19-hsien-wood.svg"
    ]
    function chooseAvatar(relPath) {
        var absPath = settings.assetBase + relPath
        lelan.setUserAvatar(settings.userName, absPath)
        hub.setMeAvatar(absPath)
        win.avatarPickerOpen = false
    }

    // ── nudge signal + shake animation (6-D) ────────────────────────────
    Connections {
        target: hub
        function onNudgeReceived(fromUser) { nudgeAnim.start() }
        function onActiveChanged() { searchBar.visible = false; searchInput.text = ""; win.emojiOpen = false }
        function onIncomingMessage(convId, author, preview, mention) {
            win.unreadTotal += 1
            win.title = "Magpie Talker (" + win.unreadTotal + ")"
            win.raise()
            if (mention) win.requestActivate()
        }
        function onCallMediaError(message) { win.lastMediaError = message }
        function onCallStateChanged() {
            if (hub.callState === "calling" || hub.callState === "ringing")
                win.lastMediaError = ""
        }
    }

    // Reset unread badge when window gains focus
    onActiveFocusItemChanged: {
        if (activeFocusItem) { win.unreadTotal = 0; win.title = "Magpie Talker" }
    }
    SequentialAnimation {
        id: nudgeAnim
        NumberAnimation { target: win; property: "nudgeX"; to: -10; duration: 60 }
        NumberAnimation { target: win; property: "nudgeX"; to:  10; duration: 60 }
        NumberAnimation { target: win; property: "nudgeX"; to:  -7; duration: 50 }
        NumberAnimation { target: win; property: "nudgeX"; to:   7; duration: 50 }
        NumberAnimation { target: win; property: "nudgeX"; to:  -4; duration: 40 }
        NumberAnimation { target: win; property: "nudgeX"; to:   0; duration: 40 }
    }

    // ── magpie crest ────────────────────────────────────────────────────────
    component Magpie: Canvas {
        property color tint: k.gilt4
        renderStrategy: Canvas.Cooperative
        antialiasing:true; onTintChanged:requestPaint(); Component.onCompleted:requestPaint()
        onPaint:{
            var ctx=getContext("2d"); ctx.reset();
            var s=Math.min(width,height)/100.0; ctx.scale(s,s);
            ctx.fillStyle=tint;
            ctx.beginPath(); ctx.arc(62,20,10,0,2*Math.PI); ctx.fill();
            ctx.beginPath(); ctx.moveTo(58,28); ctx.bezierCurveTo(64,40,66,56,56,70);
            ctx.bezierCurveTo(70,64,78,48,74,30); ctx.bezierCurveTo(70,24,64,22,58,28); ctx.closePath(); ctx.fill();
            ctx.beginPath(); ctx.moveTo(56,70); ctx.bezierCurveTo(48,80,34,88,18,92);
            ctx.bezierCurveTo(30,80,40,64,50,54); ctx.bezierCurveTo(54,58,56,64,56,70); ctx.closePath(); ctx.fill();
            ctx.beginPath(); ctx.moveTo(70,18); ctx.lineTo(84,13); ctx.lineTo(71,23); ctx.closePath(); ctx.fill();
            ctx.fillStyle=crd.cer4; ctx.globalAlpha=0.85;
            ctx.beginPath(); ctx.moveTo(58,36); ctx.bezierCurveTo(52,46,52,58,52,58);
            ctx.bezierCurveTo(60,54,64,44,62,36); ctx.closePath(); ctx.fill(); ctx.globalAlpha=1;
            ctx.fillStyle=k.surfaceHi; ctx.beginPath(); ctx.arc(65,18,1.6,0,2*Math.PI); ctx.fill();
        }
    }

    component Icon: Canvas {
        property string name:""; property color tint: k.gilt0
        renderStrategy: Canvas.Cooperative
        antialiasing:true; onTintChanged:requestPaint(); onNameChanged:requestPaint(); Component.onCompleted:requestPaint()
        onPaint:{
            var ctx=getContext("2d"); ctx.reset(); var s=Math.min(width,height)/24.0; ctx.scale(s,s);
            ctx.strokeStyle=tint; ctx.fillStyle=tint; ctx.lineWidth=1.7; ctx.lineCap="round"; ctx.lineJoin="round"; var P=function(){ctx.beginPath();};
            if(name==="search"){ P();ctx.arc(11,11,7,0,2*Math.PI);ctx.stroke(); P();ctx.moveTo(16,16);ctx.lineTo(21,21);ctx.stroke(); }
            else if(name==="bell"){ P();ctx.moveTo(6,10);ctx.bezierCurveTo(6,5,18,5,18,10);ctx.bezierCurveTo(18,15,20,16,20,16);ctx.lineTo(4,16);ctx.bezierCurveTo(4,16,6,15,6,10);ctx.stroke(); P();ctx.moveTo(10,20);ctx.lineTo(14,20);ctx.stroke(); }
            else if(name==="clip"){ P();ctx.moveTo(20,11);ctx.lineTo(12,19);ctx.bezierCurveTo(9,22,4,17,7,14);ctx.lineTo(15,6);ctx.bezierCurveTo(17,4,20,7,18,9);ctx.lineTo(10,17);ctx.stroke(); }
            else if(name==="smile"){ P();ctx.arc(12,12,8.5,0,2*Math.PI);ctx.stroke(); P();ctx.arc(9,10,0.9,0,2*Math.PI);ctx.fill(); P();ctx.arc(15,10,0.9,0,2*Math.PI);ctx.fill(); P();ctx.moveTo(8.5,14.5);ctx.bezierCurveTo(10,17,14,17,15.5,14.5);ctx.stroke(); }
            else if(name==="send"){ P();ctx.moveTo(3,11);ctx.lineTo(21,3);ctx.lineTo(13,21);ctx.lineTo(11,14);ctx.closePath();ctx.fill(); }
            else if(name==="users"){ P();ctx.arc(8,8,3,0,2*Math.PI);ctx.stroke(); P();ctx.moveTo(3,19);ctx.bezierCurveTo(3,15,13,15,13,19);ctx.stroke(); P();ctx.arc(16,8,2.6,0,2*Math.PI);ctx.stroke(); P();ctx.moveTo(14,14);ctx.bezierCurveTo(20,14,21,17,21,19);ctx.stroke(); }
            else if(name==="hash"){ P();ctx.moveTo(8,4);ctx.lineTo(6,20);ctx.stroke(); P();ctx.moveTo(16,4);ctx.lineTo(14,20);ctx.stroke(); P();ctx.moveTo(4,9);ctx.lineTo(20,9);ctx.stroke(); P();ctx.moveTo(3,15);ctx.lineTo(19,15);ctx.stroke(); }
            else if(name==="pin"){ P();ctx.moveTo(12,21);ctx.bezierCurveTo(12,21,5,13.5,5,8.5);ctx.bezierCurveTo(5,4.9,8.1,2,12,2);ctx.bezierCurveTo(15.9,2,19,4.9,19,8.5);ctx.bezierCurveTo(19,13.5,12,21,12,21);ctx.stroke(); P();ctx.arc(12,8.5,2.4,0,2*Math.PI);ctx.stroke(); }
        }
    }

    component Ava: Item {
        id: ava
        property string label:"·"; property string c1: crd.cer3; property string c2: crd.cer2
        property string pres:"online"; property real diameter:40; property int fontPx:16; property bool showPres:true
        property string avatarSrc: ""
        width: diameter; height: diameter
        Rectangle {
            anchors.fill: parent; radius: width/2; border.color: k.gilt0; border.width: 1.5
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop{position:0;color:ava.c1} GradientStop{position:1;color:ava.c2} }
            Image {
                anchors.fill: parent; visible: ava.avatarSrc.length > 0
                source: ava.avatarSrc; fillMode: Image.PreserveAspectCrop
            }
            Text { anchors.centerIn: parent; text: ava.label; color: k.surfaceHi
                   font.family:k.display; font.bold:true; font.pixelSize: ava.fontPx
                   visible: !ava.avatarSrc.length }
        }
        Rectangle { visible: ava.showPres; width: Math.max(11,ava.diameter*0.3); height: width; radius: width/2
            anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: -1
            color: presColor(ava.pres); border.color: k.surface2; border.width: 2 }
    }

    Rectangle {
        anchors.fill: parent; color:"transparent"; radius:16; border.color:k.gilt0; border.width:2
        opacity: win.loginActive ? 0.22 : 1.0
        transform: Translate { x: win.nudgeX }
        Behavior on opacity { NumberAnimation { duration: 380; easing.type: Easing.OutCubic } }

        // Mode-aware ground
        Rectangle { anchors.fill: parent; radius: 16; color: k.panelBg }
        NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

        ColumnLayout {
            anchors.fill: parent; spacing: 0

            // ── titlebar ──────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 46
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:crd.cer2} GradientStop{position:1;color:crd.cer1} }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:2; color:k.gilt4; opacity:.6 }
                DragHandler { target: null; onActiveChanged: if (active) win.startSystemMove() }
                RowLayout {
                    anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 10
                    Magpie { Layout.preferredWidth: 28; Layout.preferredHeight: 28 }
                    ColumnLayout { spacing: 2
                        Text { text:"Magpie Talker"; font.family:k.display; font.bold:true; font.pixelSize: fpx(15)
                               color:k.gilt5; font.letterSpacing:1.4 }
                        Text { text:"LA PIE · THE WIRE"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                               color:crd.cer5; font.letterSpacing:3 } }
                    Item { Layout.fillWidth: true }
                    Rectangle { Layout.preferredHeight: 26; Layout.preferredWidth: netRow.implicitWidth + 24
                        radius: 13; color: Qt.rgba(1,1,1,0.10); border.color: Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.3); border.width: 1
                        Row { id: netRow; anchors.centerIn: parent; spacing: 8
                            Rectangle { width:9;height:9;radius:5; color: hub.networkUp?crd.cer4:k.gilt3
                                anchors.verticalCenter: parent.verticalCenter
                                SequentialAnimation on opacity {
                                    running: win.motionEnabled && hub.networkUp
                                             && (typeof animPolicy === "undefined" || animPolicy === null
                                                 || (animPolicy.decorative && !animPolicy.screenIdle))
                                    loops: Animation.Infinite
                                    NumberAnimation{to:1;duration:(typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 2200 : 1100}
                                    NumberAnimation{to:0.5;duration:(typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 2200 : 1100} } }
                            Text { text: hub.netSummary; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:crd.cer5
                                   anchors.verticalCenter: parent.verticalCenter } } }
                    Item { Layout.preferredWidth: 6 }
                    // ? — Poe's manual
                    Rectangle { Layout.preferredWidth:22; Layout.preferredHeight:22; radius:11; Layout.alignment:Qt.AlignVCenter
                        color: helpHov.hovered ? Qt.rgba(crd.cer4.r,crd.cer4.g,crd.cer4.b,0.28) : Qt.rgba(1,1,1,0.10)
                        border.color: Qt.rgba(k.gilt3.r,k.gilt3.g,k.gilt3.b,0.45); border.width:1
                        Text { anchors.centerIn:parent; text:"?"; font.family:k.display; font.bold:true
                               font.pixelSize: fpx(12); color:crd.cer5; font.letterSpacing:0.5 }
                        HoverHandler { id: helpHov }
                        TapHandler { onTapped: manual.show() } }
                }
            }

            // ── body: sidebar | thread | roster ────────────────────────────
            RowLayout {
                Layout.fillWidth: true; Layout.fillHeight: true; spacing: 0

                // ===== SIDEBAR =====
                Rectangle {
                    Layout.preferredWidth: 252; Layout.fillHeight: true
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                    Rectangle { anchors.right: parent.right; width:2; height: parent.height; color:k.gilt1 }
                    ColumnLayout {
                        anchors.fill: parent; spacing: 0

                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: 64; color:"transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color:k.gilt1 }
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 12; spacing: 11
                                Ava { label: hub.meInitial; c1: crd.cer3; c2: crd.cer2; pres: hub.presence
                                      avatarSrc: hub.meAvatarUrl
                                      TapHandler { onTapped: win.avatarPickerOpen = true } }
                                ColumnLayout { Layout.fillWidth: true; spacing: 1
                                    Text { text: hub.meName; font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: fpx(15); color:k.ink
                                           elide: Text.ElideRight; Layout.fillWidth: true }
                                    Text { text: "● " + (hub.presence==="appear_offline"?"hidden":hub.presence) + (hub.statusText.length ? " · " + hub.statusText : ""); font.family:k.fell; font.italic:true
                                           font.pixelSize: fpx(11); color:k.inkSoft; elide: Text.ElideRight; Layout.fillWidth: true
                                           visible: !win.editingStatus
                                           TapHandler { onTapped: { statusEdit.text = hub.statusText; win.editingStatus = true; statusEdit.forceActiveFocus() } } }
                                    TextInput {
                                        id: statusEdit; Layout.fillWidth: true; visible: win.editingStatus
                                        text: hub.statusText; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:k.inkSoft
                                        Keys.onReturnPressed: { hub.setStatusText(text); win.editingStatus = false }
                                        Keys.onEscapePressed: win.editingStatus = false
                                        onActiveFocusChanged: if (!activeFocus && win.editingStatus) { hub.setStatusText(text); win.editingStatus = false }
                                    }
                                    Text { visible: hub.location.length > 0; text: "⌖ " + hub.location
                                           font.family:k.fell; font.italic:true; font.pixelSize: fpx(10); color:k.gilt2; elide: Text.ElideRight; Layout.fillWidth: true } }
                                Rectangle { Layout.preferredWidth:24; Layout.preferredHeight:24; radius:6
                                    color: presHov.hovered?k.surfaceHi:"transparent"; border.color: presHov.hovered?k.gilt1:"transparent"; border.width:1
                                    Rectangle { anchors.centerIn: parent; width:11;height:11;radius:6; color: presColor(hub.presence); border.color:k.gilt0; border.width:1 }
                                    HoverHandler{id:presHov}
                                    TapHandler{ onTapped: {
                                        var order=["online","away","busy","appear_offline","offline"];
                                        var i=order.indexOf(hub.presence); hub.setPresence(order[(i+1)%order.length]); } }
                                }
                                // The Jabber/XMPP-server account status pill + its whole settings panel
                                // were removed entirely (2026-07-05, operator decision) — global reach
                                // is the DHT world band now (add-by-callsign, see hub.addByCallsign()).
                            }
                        }

                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: sideCol.implicitHeight; clip: true
                            Column {
                                id: sideCol; width: parent.width

                                // ── Facebook Messenger (MagpieMessenger.qml) ──────────────
                                Item { width: parent.width; height: 30
                                    Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 14; spacing: 8
                                        Text { text:"Facebook"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                                               font.letterSpacing:2; color:k.gilt1; anchors.verticalCenter: parent.verticalCenter }
                                        Rectangle { width: parent.width - 96; height:1; color:k.gilt2; opacity:.5; anchors.verticalCenter: parent.verticalCenter } } }
                                Rectangle {
                                    width: sideCol.width; height: Math.max(42, fbRowCol.implicitHeight + 12)
                                    property bool sel: win.fbMode
                                    color: sel ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.18) : (fbRowHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent")
                                    Rectangle { visible: parent.sel; x:0; width:3; height:24; radius:2; anchors.verticalCenter: parent.verticalCenter; color:crd.cer3 }
                                    Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.right: parent.right; anchors.rightMargin: 14
                                          anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                        Rectangle { width:28; height:28; radius:14; anchors.verticalCenter: parent.verticalCenter
                                            gradient: Gradient { orientation: Gradient.Vertical
                                                GradientStop{position:0;color:crd.cer3} GradientStop{position:1;color:crd.cer1} }
                                            border.color:k.gilt3; border.width:1.5
                                            Text { anchors.centerIn: parent; text:"ϟ"; font.family:k.titles; font.bold:true
                                                   font.pixelSize: fpx(15); color:"#fbf3de" } }
                                        Column { id: fbRowCol; anchors.verticalCenter: parent.verticalCenter; spacing: 1
                                            width: parent.width - 38 - (fbPane.unread>0 ? 34 : 0)
                                            Text { text: "Messenger"; font.family:k.serif; font.pixelSize: fpx(16); color:k.ink
                                                   font.weight: fbPane.unread>0 ? Font.DemiBold : Font.Normal
                                                   elide: Text.ElideRight; width: parent.width }
                                            Text { text: fbPane.statusLine; font.family:k.fell; font.italic:true
                                                   font.pixelSize: fpx(9); color:k.gilt2; font.letterSpacing:1
                                                   elide: Text.ElideRight; width: parent.width } } }
                                    Rectangle { visible: fbPane.unread>0
                                        anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
                                        height:20; width: Math.max(20, fbUbT.implicitWidth+12); radius:10; color: crd.cer2
                                        Text { id: fbUbT; anchors.centerIn: parent; text: fbPane.unread
                                               font.family:k.gar; font.pixelSize: fpx(11); font.bold:true; color: k.surfaceHi } }
                                    HoverHandler { id: fbRowHov }
                                    TapHandler { onTapped: { win.fbMode = true; searchBar.visible = false; win.emojiOpen = false } }
                                }

                                Item { width: parent.width; height: 30
                                    Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 14; spacing: 8
                                        Text { text:"Channels"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                                               font.letterSpacing:2; color:k.gilt1; anchors.verticalCenter: parent.verticalCenter }
                                        Rectangle { width: parent.width - 110; height:1; color:k.gilt2; opacity:.5; anchors.verticalCenter: parent.verticalCenter }
                                        Text { text:"+"; font.family:k.titles; font.pixelSize: fpx(15)
                                               color: chanPlusHov.hovered ? k.gilt4 : k.gilt2; anchors.verticalCenter: parent.verticalCenter
                                               HoverHandler { id: chanPlusHov }
                                               TapHandler { onTapped: win.createChanOpen = true } } } }

                                Repeater {
                                    model: hub.channels
                                    Rectangle {
                                        width: sideCol.width; height: 38
                                        property bool sel: hub.activeIsChannel && hub.activeId===modelData.id
                                        color: sel ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.18) : (chHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent")
                                        Rectangle { visible: parent.sel; x:0; width:3; height:24; radius:2; anchors.verticalCenter: parent.verticalCenter; color:crd.cer3 }
                                        Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.right: parent.right; anchors.rightMargin: 14
                                              anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                            Rectangle { width:26;height:26;radius:7; anchors.verticalCenter: parent.verticalCenter
                                                gradient: Gradient { orientation: Gradient.Vertical
                                                    GradientStop{position:0;color:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                                                border.color:k.gilt1; border.width:1.5
                                                Text { anchors.centerIn: parent; text:"#"; font.family:k.titles; font.bold:true; font.pixelSize: fpx(15); color:crd.cer2 } }
                                            Text { width: parent.width - 26 - (modelData.unread>0?34:0) - 20
                                                   text: modelData.name; font.family:k.serif; font.pixelSize: fpx(16)
                                                   font.weight: (modelData.unread>0 && !modelData.muted)?Font.DemiBold:Font.Normal
                                                   color:k.ink; elide: Text.ElideRight; anchors.verticalCenter: parent.verticalCenter } }
                                        Rectangle { visible: modelData.unread>0
                                            anchors.right: parent.right; anchors.rightMargin: 14; anchors.verticalCenter: parent.verticalCenter
                                            height:20; width: Math.max(20, ubT.implicitWidth+12); radius:10
                                            color: modelData.muted ? "transparent" : crd.cer2
                                            Text { id: ubT; anchors.centerIn: parent; text: modelData.unread
                                                   font.family:k.gar; font.pixelSize: fpx(11); font.bold:true
                                                   color: modelData.muted ? k.inkSoft : k.surfaceHi } }
                                        HoverHandler { id: chHov }
                                        TapHandler { onTapped: { win.fbMode = false; hub.openConversation(modelData.id, true) } }
                                    }
                                }

                                // ── DM header with + add-contact button ──────────────────
                                Item { width: parent.width; height: 32
                                    Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 38; spacing: 8
                                        Text { text:"Direct Messages"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(10)
                                               font.letterSpacing:2; color:k.gilt1; anchors.verticalCenter: parent.verticalCenter }
                                        Rectangle { width: parent.width - 172; height:1; color:k.gilt2; opacity:.5; anchors.verticalCenter: parent.verticalCenter } }
                                    Item { anchors.right: parent.right; anchors.rightMargin: 38
                                           anchors.verticalCenter: parent.verticalCenter; width: 16; height: 16
                                        Icon { anchors.fill: parent; name:"pin"
                                               tint: nearbyHov.hovered ? k.gilt4 : k.gilt2 }
                                        HoverHandler { id: nearbyHov }
                                        TapHandler { onTapped: win.browseNearbyOpen = !win.browseNearbyOpen } }
                                    Item { anchors.right: parent.right; anchors.rightMargin: 14
                                           anchors.verticalCenter: parent.verticalCenter; width: 18; height: 18
                                        Text { anchors.centerIn: parent; text:"+"; font.family:k.titles; font.pixelSize: fpx(15)
                                               color: addDmHov.hovered ? k.gilt4 : k.gilt2 }
                                        HoverHandler { id: addDmHov }
                                        TapHandler { onTapped: win.addContactOpen = !win.addContactOpen } } }

                                // ── contacts by group ─────────────────────────────────────
                                Repeater {
                                    model: hub.contactGroups
                                    Column {
                                        width: sideCol.width
                                        Item { width: parent.width; height: 22
                                            Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 14; spacing: 8
                                                Text { text: modelData.name; font.family:k.fell; font.italic:true; font.pixelSize: fpx(9)
                                                       font.letterSpacing:2; color:k.gilt2; anchors.verticalCenter: parent.verticalCenter }
                                                Rectangle { width: parent.width - 80; height:1; color:k.gilt2; opacity:.3; anchors.verticalCenter: parent.verticalCenter } } }
                                        Repeater {
                                            model: modelData.contacts
                                            Rectangle {
                                                width: sideCol.width; height: 42
                                                property bool sel: !hub.activeIsChannel && hub.activeId===modelData.screenName
                                                color: sel ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.18) : (cntHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent")
                                                Rectangle { visible: parent.sel; x:0; width:3; height:24; radius:2; anchors.verticalCenter: parent.verticalCenter; color:crd.cer3 }
                                                Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                                    Ava { diameter:28; fontPx:12; label: modelData.initial; c1: modelData.c1; c2: modelData.c2
                                                          pres: modelData.presence; opacity: modelData.online ? 1.0 : 0.5 }
                                                    Column { anchors.verticalCenter: parent.verticalCenter; spacing: 1
                                                        Text { text: modelData.name; font.family:k.serif; font.pixelSize: fpx(16)
                                                               color: modelData.online ? k.ink : k.inkSoft }
                                                        Text { visible: !modelData.online && modelData.lastSeen.length > 0
                                                               text: "last seen " + modelData.lastSeen
                                                               font.family:k.fell; font.italic:true; font.pixelSize: fpx(9); color:k.inkSoft }
                                                        Text { visible: modelData.blocked
                                                               text: "blocked"; font.family:k.fell; font.italic:true
                                                               font.pixelSize: fpx(9); color:k.wine4; font.letterSpacing:1.5 } } }
                                                HoverHandler { id: cntHov }
                                                TapHandler { acceptedButtons: Qt.LeftButton
                                                    onTapped: { win.fbMode = false; hub.openConversation(modelData.screenName, false) } }
                                                TapHandler { acceptedButtons: Qt.RightButton
                                                    onTapped: function(eventPoint) {
                                                        win.ctxUuid       = modelData.uuid
                                                        win.ctxBlocked    = modelData.blocked
                                                        win.ctxScreenName = modelData.screenName
                                                        win.ctxOpen       = true
                                                        win.ctxX = Math.min(eventPoint.scenePosition.x, win.width  - 175)
                                                        win.ctxY = Math.min(eventPoint.scenePosition.y, win.height - 110)
                                                    } }
                                            }
                                        }
                                    }
                                }

                                // ── live non-contact peers (Also on the wire) ─────────────
                                Item { visible: hub.directs.length > 0; width: parent.width; height: 22
                                    Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 14; spacing: 8
                                        Text { text:"Also on the wire"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(9)
                                               font.letterSpacing:2; color:k.gilt2; anchors.verticalCenter: parent.verticalCenter }
                                        Rectangle { width: parent.width - 144; height:1; color:k.gilt2; opacity:.3; anchors.verticalCenter: parent.verticalCenter } } }
                                Repeater {
                                    model: hub.directs
                                    Rectangle {
                                        width: sideCol.width; height: 42
                                        property bool sel: !hub.activeIsChannel && hub.activeId===modelData.id
                                        color: sel ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.18) : (dmHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent")
                                        Rectangle { visible: parent.sel; x:0; width:3; height:24; radius:2; anchors.verticalCenter: parent.verticalCenter; color:crd.cer3 }
                                        Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                            Ava { diameter:28; fontPx:12; label: modelData.initial; c1: modelData.c1; c2: modelData.c2; pres: modelData.presence }
                                            Column { anchors.verticalCenter: parent.verticalCenter; spacing: 1
                                                Text { text: modelData.name; font.family:k.serif; font.pixelSize: fpx(16); color:k.ink; elide:Text.ElideRight; width:160 }
                                                Text { visible: modelData.source === "bonjour"
                                                       text: "❧ Bonjour"; font.family:k.fell; font.italic:true
                                                       font.pixelSize: fpx(9); color:k.gilt2; font.letterSpacing:1 } } }
                                        HoverHandler { id: dmHov }
                                        TapHandler { onTapped: { win.fbMode = false; hub.openConversation(modelData.id, false) } }
                                    }
                                }
                                Text { visible: hub.directs.length===0 && hub.contactGroups.length===0
                                       width: sideCol.width - 28; x:16; topPadding:6
                                       text:"No one else on the wire yet."; font.family:k.fell; font.italic:true
                                       font.pixelSize: fpx(12); color:k.inkSoft; wrapMode: Text.WordWrap }
                                Item { width:1; height: 12 }
                            }
                        }
                    }
                }

                // ===== THREAD =====
                Rectangle {
                    visible: !win.fbMode
                    Layout.fillWidth: true; Layout.fillHeight: true; color: k.surface

                    ColumnLayout {
                        anchors.fill: parent; spacing: 0

                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: 56
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color:k.surface} GradientStop{position:1;color:k.surface2} }
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color:k.gilt1 }
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 18; anchors.rightMargin: 16; spacing: 12
                                Rectangle { visible: hub.activeIsChannel; Layout.preferredWidth:30; Layout.preferredHeight:30; radius:8
                                    gradient: Gradient { orientation: Gradient.Vertical
                                        GradientStop{position:0;color:k.surfaceHi} GradientStop{position:1;color:k.surface2} }
                                    border.color:k.gilt1; border.width:1.5
                                    Text { anchors.centerIn: parent; text:"#"; font.family:k.titles; font.bold:true; font.pixelSize: fpx(17); color:crd.cer2 } }
                                Text { text: hub.activeTitle; font.family:k.display; font.bold:true; font.pixelSize: fpx(18); color:crd.cer1; font.letterSpacing:0.4 }
                                Text { Layout.fillWidth: true; text: hub.activeTopic; font.family:k.fell; font.italic:true; font.pixelSize: fpx(13); color:k.inkSoft; elide: Text.ElideRight }
                                Repeater {
                                    model: [ "search", "bell", "users" ]
                                    // bell = mute; only channels carry a per-conversation muted flag in the
                                    // model (hub.channels[].muted). DMs have no muted field, so the bell has
                                    // nothing to toggle or reflect there — hide it outside a channel rather
                                    // than leave a dead chip. "users" toggles the roster panel on the right.
                                    Rectangle { Layout.preferredWidth:32; Layout.preferredHeight:32; radius:8
                                        visible: modelData !== "bell" || hub.activeIsChannel
                                        border.color: (modelData==="users" && win.rosterOpen) || thHov.hovered ? crd.cer3 : k.gilt1
                                        border.width:1.5
                                        color: (modelData==="users" && win.rosterOpen) ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.12) : k.surfaceHi
                                        Icon { anchors.centerIn: parent; width:17; height:17; name: modelData }
                                        HoverHandler { id: thHov }
                                        TapHandler { onTapped: {
                                            if (modelData==="search") searchBar.visible = !searchBar.visible
                                            else if (modelData==="bell" && hub.activeIsChannel) {
                                                // toggle mute on the active channel
                                                hub.toggleMute(hub.activeId)
                                            }
                                            else if (modelData==="users") win.rosterOpen = !win.rosterOpen
                                        } } } }
                                // Nudge button — DM conversations only (6-D)
                                Rectangle { visible: !hub.activeIsChannel
                                    Layout.preferredWidth:32; Layout.preferredHeight:32; radius:8
                                    border.color: nudgeBtnHov.hovered?crd.cer3:k.gilt1; border.width:1.5; color: k.surfaceHi
                                    Text { anchors.centerIn: parent; text:"≋"; font.pixelSize: fpx(17); color:crd.cer3 }
                                    HoverHandler { id: nudgeBtnHov }
                                    TapHandler { onTapped: hub.nudge(hub.activeId) } }
                                // Flutter — native video call (FLUTTER-PLAN §1: one button transforms
                                // the whole interface into the call view below). LABELED, not a bare
                                // glyph. ALWAYS VISIBLE (operator, 2026-07-06, second report: "Magpie
                                // still does not show the Flutter Button" — it was gated on an open DM,
                                // and with no DM open — activeIsChannel defaults true — it could never
                                // appear at all). Now the pill always sits in the header: gilt and
                                // tappable in an open DM, ink-toned otherwise (calls are person-to-
                                // person — a channel or an empty pane has no one to ring).
                                // 2026-07-07 third report ("still isn't in magpie talker"): the pill WAS
                                // rendering — its label was invisible on its own chip. Dark-mode surfaceHi
                                // is gilt4 (#e9c97c, light gold); inkSoft (#b8a07a) on it = 1.57:1 and
                                // crd.cer3 (#5fb4c6) = 1.48:1 — below perceptible, let alone the 7:1 bar.
                                // The sibling header icons survive because Icon's default tint is k.gilt0
                                // (6.4:1 dark / 9.8:1 light). Label now uses the same dark-legible tokens:
                                // crd.cer1 when callable (7.3:1 dark — the ramp's own dark-adapted step;
                                // = k.cer in light, the app-wide accent), k.gilt0 otherwise.
                                Rectangle { id: flutterBtn
                                    readonly property bool callable: !hub.activeIsChannel && hub.activeId !== "" && hub.callState==="idle"
                                    Layout.preferredWidth: callLbl.implicitWidth + 24; Layout.preferredHeight:32; radius:8
                                    border.color: flutterBtn.callable && flutterBtnHov.hovered ? crd.cer3 : k.gilt1
                                    border.width:1.5; color: k.surfaceHi
                                    Row { id: callLbl; anchors.centerIn: parent; spacing: 6
                                        Text { text:"✆"; font.pixelSize: fpx(16)
                                               color: flutterBtn.callable ? crd.cer1 : k.gilt0 }
                                        Text { text: hub.callState==="idle" ? "Video Call" : "In Call"
                                               font.pixelSize: fpx(13); font.bold: true
                                               anchors.verticalCenter: parent.verticalCenter
                                               color: flutterBtn.callable ? crd.cer1 : k.gilt0 } }
                                    HoverHandler { id: flutterBtnHov }
                                    TapHandler { onTapped: if (flutterBtn.callable) hub.startCall(hub.activeId) } }
                            }
                        }

                        Rectangle {
                            id: searchBar; visible: false
                            Layout.fillWidth: true; Layout.preferredHeight: 44; color: k.surface2
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color:k.gilt1 }
                            Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                anchors.leftMargin: 18; anchors.rightMargin: 18; height: 30; radius: 15; color: k.surfaceHi
                                border.color: k.gilt1; border.width: 1.5
                                Row { anchors.fill: parent; anchors.leftMargin: 12; anchors.rightMargin: 12; spacing: 8
                                    Icon { width:15;height:15; name:"search"; tint:k.inkSoft; anchors.verticalCenter: parent.verticalCenter }
                                    TextInput { id: searchInput; width: parent.width - 26; anchors.verticalCenter: parent.verticalCenter
                                        font.family:k.serif; font.pixelSize: fpx(15); color:k.ink; clip:true; selectByMouse:true
                                        onTextChanged: hub.search(text)
                                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter; text:"Search this conversation…"
                                               font.family:k.serif; font.italic:true; font.pixelSize: fpx(15); color:k.inkSoft; opacity:.55
                                               visible: !searchInput.text.length && !searchInput.activeFocus } } } }
                        }

                        // ── empty state — no conversation selected ────────────
                        Item {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            visible: hub.activeId === ""
                            Column {
                                anchors.centerIn: parent; spacing: 14
                                Magpie { width: 52; height: 52; anchors.horizontalCenter: parent.horizontalCenter }
                                Text { anchors.horizontalCenter: parent.horizontalCenter
                                       text: "La Pie — The Wire"
                                       font.family:k.display; font.bold:true; font.pixelSize: fpx(17); color:crd.cer2; font.letterSpacing:1.2 }
                                Text { anchors.horizontalCenter: parent.horizontalCenter
                                       text: "Select a conversation or open a channel to begin."
                                       font.family:k.fell; font.italic:true; font.pixelSize: fpx(13); color:k.inkSoft }
                            }
                        }

                        Flickable {
                            id: msgFlick
                            Layout.fillWidth: true; Layout.fillHeight: true
                            visible: hub.activeId !== ""
                            contentHeight: msgCol.implicitHeight + 24; clip: true
                            Column {
                                id: msgCol; width: parent.width
                                topPadding: 14; bottomPadding: 10; spacing: 16
                                leftPadding: 22; rightPadding: 22

                                Repeater {
                                    model: hub.messages
                                    Item {
                                        id: msgItem
                                        width: msgCol.width - 44
                                        height: msgRow.implicitHeight
                                        property bool mine: modelData.who==="me"
                                        Row {
                                            id: msgRow; width: parent.width; spacing: 12
                                            Ava { diameter:28; fontPx:12; showPres:false
                                                  label: msgItem.mine ? hub.meInitial : hub.initialsOf(modelData.name)
                                                  c1: msgItem.mine ? crd.cer3 : hub.gradientC1(modelData.who)
                                                  c2: msgItem.mine ? crd.cer2 : hub.gradientC2(modelData.who)
                                                  avatarSrc: msgItem.mine ? hub.meAvatarUrl : hub.peerAvatarUrl(modelData.who) }
                                            Column {
                                                width: parent.width - 40; spacing: 3
                                                Row { spacing: 9
                                                    Text { text: msgItem.mine ? hub.meName : modelData.name
                                                           font.family:k.titles; font.weight:Font.DemiBold; font.pixelSize: fpx(15); color:crd.cer1 }
                                                    Text { text: modelData.tm; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11)
                                                           color:k.inkSoft; anchors.verticalCenter: parent.verticalCenter } }
                                                // D-3 (MP-SEC-1): URLs are hyperlinked; onLinkActivated checks KickassGuard.
                                                Text { width: parent.width
                                                       text: {
                                                           var t = modelData.text ? modelData.text : "";
                                                           t = t.replace(/@([\w]+)/g, '<span style="color:' + crd.cer2 + '; background:rgba(47,138,160,0.12); font-weight:600;">@$1</span>');
                                                           return win.hyperlinkify(t);
                                                       }
                                                       textFormat: Text.RichText
                                                       font.family:k.gar; font.pixelSize: fpx(16); color:k.ink
                                                       wrapMode: Text.WordWrap; lineHeight: 1.35
                                                       visible: modelData.text && modelData.text.length>0
                                                       onLinkActivated: function(url) {
                                                           var result = hub.checkLink(url);
                                                           if (result.startsWith("blocked")) {
                                                               win.linkPendingUrl    = url;
                                                               win.linkPendingStatus = result;
                                                           } else {
                                                               launcher.systemCommand("ncde-chromium " + url);
                                                           }
                                                       } }
                                                // D-3 (MP-SEC-2): received file badge with explicit Save & Scan.
                                                Rectangle { visible: modelData.img !== undefined; width: 240; height: 84; radius: 8
                                                    border.color:k.gilt1; border.width:2
                                                    gradient: Gradient { orientation: Gradient.Vertical
                                                        GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                                                    Column { anchors.centerIn: parent; spacing: 6
                                                        Text { id: fnT; anchors.horizontalCenter: parent.horizontalCenter
                                                               text:"📎 " + (modelData.img||"")
                                                               font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.ink
                                                               elide: Text.ElideMiddle; width: 200 }
                                                        Rectangle { anchors.horizontalCenter: parent.horizontalCenter
                                                            height: 24; width: scanLbl.implicitWidth + 20; radius: 12
                                                            color: crd.cer3; border.width: 0
                                                            Text { id: scanLbl; anchors.centerIn: parent
                                                                   text: "Save & Scan"; font.family:k.fell; font.pixelSize: fpx(11); color:k.surfaceHi }
                                                            TapHandler { onTapped: hub.saveFile(modelData.id || "", modelData.img || "") }
                                                        }
                                                    }
                                                }
                                                Row { spacing: 6; visible: modelData.react ? modelData.react.length > 0 : false
                                                    Repeater { model: modelData.react ? modelData.react : []
                                                        Rectangle { height:24; width: rcRow.implicitWidth+16; radius:11
                                                            border.color: msgItem.mine?crd.cer3:k.gilt1; border.width:1.5
                                                            color: msgItem.mine ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.14) : k.surfaceHi
                                                            Row { id: rcRow; anchors.centerIn: parent; spacing: 4
                                                                Text { text: modelData.e; font.pixelSize: fpx(13) }
                                                                Text { text: modelData.c; font.family:k.gar; font.pixelSize: fpx(11); color:k.inkSoft
                                                                       anchors.verticalCenter: parent.verticalCenter } } } } }
                                            }
                                        }

                                        // Reaction pills displayed above had no way to ever be
                                        // added -- nothing in the app called hub.react(). Long-
                                        // press any bubble to open the same emoji panel the
                                        // composer uses, targeted at this message instead.
                                        TapHandler {
                                            onLongPressed: {
                                                win.reactTargetMsgId = modelData.id || ""
                                                win.emojiOpen = true
                                            }
                                        }
                                    }
                                }
                            }
                            onContentHeightChanged: contentY = Math.max(0, contentHeight - height)
                        }

                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: 22; color:"transparent"
                            visible: hub.typingText.length > 0
                            Row { anchors.left: parent.left; anchors.leftMargin: 22; anchors.verticalCenter: parent.verticalCenter; spacing: 9
                                Row { spacing: 3; anchors.verticalCenter: parent.verticalCenter
                                    Repeater { model: 3
                                        Rectangle { width:6;height:6;radius:3; color:crd.cer3
                                            SequentialAnimation on opacity {
                                                running: win.motionEnabled && hub.typingText.length > 0
                                                         && (typeof animPolicy === "undefined" || animPolicy === null
                                                             || (animPolicy.decorative && !animPolicy.screenIdle))
                                                loops:Animation.Infinite
                                                PauseAnimation{duration: index*150*((typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 2 : 1)}
                                                NumberAnimation{to:1;duration:(typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 600 : 300}
                                                NumberAnimation{to:0.3;duration:(typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 1200 : 600} } } } }
                                Text { text: hub.typingText; font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft } }
                        }

                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: composerCol.implicitHeight + 24
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                            Rectangle { anchors.top: parent.top; width: parent.width; height:1; color:k.gilt1 }
                            Column { id: composerCol; anchors.fill: parent; anchors.margins: 12
                                Rectangle {
                                    width: parent.width; height: Math.max(44, inputEdit.implicitHeight + 18); radius: 12
                                    color: k.surfaceHi; border.width: 1.5
                                    border.color: inputEdit.activeFocus ? crd.cer3 : k.gilt1
                                    Row {
                                        anchors.fill: parent; anchors.leftMargin: 12; anchors.rightMargin: 8
                                        anchors.topMargin: 6; anchors.bottomMargin: 6; spacing: 9
                                        Rectangle { width:32;height:32;radius:8; border.color:k.gilt1; border.width:1.5; color:k.surface
                                            anchors.bottom: parent.bottom
                                            Icon { anchors.centerIn: parent; width:16;height:16; name:"clip" }
                                            TapHandler { onTapped: filePicker.open() } }
                                        Flickable { width: parent.width - 32 - 32 - 44 - 27; height: Math.min(96, inputEdit.implicitHeight)
                                            anchors.verticalCenter: parent.verticalCenter
                                            contentHeight: inputEdit.implicitHeight; clip:true
                                            TextEdit { id: inputEdit; width: parent.width
                                                font.family:k.gar; font.pixelSize: fpx(16); color:k.ink; wrapMode: TextEdit.Wrap; selectByMouse:true
                                                onTextChanged: { if (text.length && !win.composerTyping){ win.composerTyping=true; hub.setTyping(true);} else if (!text.length && win.composerTyping){ win.composerTyping=false; hub.setTyping(false);} }
                                                Keys.onReturnPressed: function(e){ if (e.modifiers & Qt.ShiftModifier) e.accepted=false; else { win.doSend(); e.accepted=true; } }
                                                Text { anchors.fill: parent; text:"Message " + (hub.activeIsChannel?("#"+hub.activeTitle):hub.activeTitle) + "…"
                                                       font.family:k.gar; font.pixelSize: fpx(16); color:k.inkSoft; opacity:.55
                                                       visible: !inputEdit.text.length && !inputEdit.activeFocus } } }
                                        Rectangle { id: emojiBtn; width:32;height:32;radius:8; anchors.bottom: parent.bottom
                                            border.color: win.emojiOpen ? crd.cer3 : k.gilt1; border.width:1.5
                                            color: win.emojiOpen ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.12) : k.surface
                                            Icon { anchors.centerIn: parent; width:16;height:16; name:"smile" }
                                            HoverHandler { id: emojiBtnHov }
                                            TapHandler { onTapped: win.emojiOpen = !win.emojiOpen } }
                                        Rectangle { width:40;height:40;radius:10; anchors.bottom: parent.bottom
                                            border.color:crd.cer1; border.width:2
                                            gradient: Gradient { orientation: Gradient.Vertical
                                                GradientStop{position:0;color: sendHov.hovered?crd.cer4:crd.cer3} GradientStop{position:1;color:crd.cer2} }
                                            Icon { anchors.centerIn: parent; width:19;height:19; name:"send"; tint:k.surfaceHi }
                                            HoverHandler { id: sendHov }
                                            TapHandler { onTapped: win.doSend() } }
                                    }
                                }
                            }
                        }
                    }
                }

                // ===== ROSTER =====
                Rectangle {
                    visible: win.rosterOpen && !win.fbMode
                    Layout.preferredWidth: 222; Layout.fillHeight: true
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:k.surface2} GradientStop{position:1;color:k.panelBg} }
                    Rectangle { anchors.left: parent.left; width:2; height: parent.height; color:k.gilt1 }
                    ColumnLayout {
                        anchors.fill: parent; spacing: 0
                        Item { Layout.fillWidth: true; Layout.preferredHeight: 30
                            Row { anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 14; spacing: 8
                                Text { text: hub.activeIsChannel ? ("In #"+hub.activeTitle) : "Conversation"
                                       font.family:k.fell; font.italic:true; font.pixelSize: fpx(10); font.letterSpacing:2; color:k.gilt1
                                       anchors.verticalCenter: parent.verticalCenter }
                                Rectangle { width: 40; height:1; color:k.gilt2; opacity:.5; anchors.verticalCenter: parent.verticalCenter } } }
                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: rosterCol.implicitHeight; clip: true
                            Column { id: rosterCol; width: parent.width
                                Repeater {
                                    model: hub.roster
                                    Rectangle { width: rosterCol.width; height: 44; color:"transparent"
                                        Row { anchors.left: parent.left; anchors.leftMargin: 14; anchors.right: parent.right; anchors.rightMargin: 12
                                              anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                            Ava { diameter:30; fontPx:13; label: modelData.initial; c1: modelData.c1; c2: modelData.c2; pres: modelData.presence }
                                            Column { width: parent.width - 42; anchors.verticalCenter: parent.verticalCenter
                                                Text { text: modelData.name + (modelData.me?" (you)":""); font.family:k.serif; font.pixelSize: fpx(15)
                                                       color:k.ink; elide: Text.ElideRight; width: parent.width }
                                                Text { text: modelData.status; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11)
                                                       color:k.inkSoft; elide: Text.ElideRight; width: parent.width } } } }
                                }
                            }
                        }
                    }
                }

                // ===== MESSENGER ===== (stays alive while hidden so messages keep arriving)
                MagpieMessenger {
                    id: fbPane
                    visible: win.fbMode
                    Layout.fillWidth: true; Layout.fillHeight: true
                    kit: k
                    cer1: crd.cer1; cer2: crd.cer2; cer3: crd.cer3; cer4: crd.cer4; cer5: crd.cer5
                    scale: theme.fontMedium / 13.0
                    ready: !win.loginActive && !win.firstLaunch
                    showing: win.fbMode
                    windowActive: win.active
                    onMessageArrived: function(title, body) {
                        if (win.active && win.fbMode) return
                        // → /usr/local/bin/magpie-notify (x-scheme-handler) → dunst, Mucha style.
                        // base64url only: nothing a sender writes can reach a shell.
                        Qt.openUrlExternally("magpie-notify:" + win.b64url(title || "Messenger") + "." + win.b64url(body || ""))
                    }
                }
            }

            // ── statusbar ───────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 26
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:crd.cer2} GradientStop{position:1;color:crd.cer1} }
                Rectangle { anchors.top: parent.top; width: parent.width; height:1.5; color:k.gilt3 }
                Row { anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 14
                    Text { text: win.fbMode ? "Facebook Messenger · on the Magpie wire" : "Peer-to-peer · mDNS discovery"
                           font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:crd.cer5 }
                    Text { visible: !win.fbMode; text: hub.peerCount + " peers seen"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:crd.cer5 } }
                Row { anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 14
                    Text { text: win.fbMode ? "History kept by Facebook" : "History saved locally"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:crd.cer5 }
                    Text { text:"Magpie Talker v1.0"; font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:crd.cer5 } }
            }
        }
    }

    // ── contact context menu (right-click on a contact row) ─────────────────────
    Rectangle {
        anchors.fill: parent; z: 49; color: "transparent"; radius: 16
        visible: win.ctxOpen
        TapHandler { onTapped: win.ctxOpen = false }
    }
    Rectangle {
        id: ctxMenu; z: 50
        visible: win.ctxOpen
        x: win.ctxX; y: win.ctxY
        width: 172; radius: 8
        height: ctxCol.implicitHeight + 16
        color: k.panelBg
        border.color: k.gilt2; border.width: 1.5
        Column {
            id: ctxCol
            anchors.top: parent.top; anchors.topMargin: 8
            width: parent.width
            Rectangle { width: parent.width - 8; x: 4; height: 30; radius: 6
                color: ctxOpenHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent"
                Text { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12
                       text:"Open conversation"; font.family:k.serif; font.pixelSize: fpx(13); color:k.ink }
                HoverHandler { id: ctxOpenHov }
                TapHandler { onTapped: { hub.openConversation(win.ctxScreenName, false); win.ctxOpen = false } } }
            Rectangle { width: parent.width - 8; x: 4; height: 30; radius: 6
                color: ctxBlockHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : "transparent"
                Text { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12
                       text: win.ctxBlocked ? "Unblock" : "Block"
                       font.family:k.serif; font.pixelSize: fpx(13); color: win.ctxBlocked ? k.ink : k.wine4 }
                HoverHandler { id: ctxBlockHov }
                TapHandler { onTapped: {
                    if (win.ctxBlocked) hub.unblockContact(win.ctxUuid)
                    else hub.blockContact(win.ctxUuid)
                    win.ctxOpen = false } } }
            Rectangle { width: parent.width - 28; x: 14; height: 1; color: k.gilt1; opacity: 0.5 }
            Rectangle { width: parent.width - 8; x: 4; height: 30; radius: 6
                color: ctxRemHov.hovered ? Qt.rgba(k.wine4.r, k.wine4.g, k.wine4.b, 0.08) : "transparent"
                Text { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 12
                       text:"Remove from contacts"; font.family:k.serif; font.pixelSize: fpx(13); color:k.wine4 }
                HoverHandler { id: ctxRemHov }
                TapHandler { onTapped: { hub.removeContact(win.ctxUuid); win.ctxOpen = false } } }
            Item { width:1; height: 8 }
        }
    }

    // ── add-contact search panel ─────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent; z: 59; radius: 16
        color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.45)
        visible: win.addContactOpen
        TapHandler { onTapped: { win.addContactOpen = false; addSrchInput.text = "" } }
    }
    Rectangle {
        id: addContactPanel; z: 60
        visible: win.addContactOpen
        width: 350; radius: 12
        height: addCntCol.implicitHeight + 40
        x: (parent.width  - width)  / 2
        y: 80
        color: k.panelBg
        border.color: k.gilt2; border.width: 1.5
        Rectangle { anchors.centerIn: parent; width: parent.width + 20; height: parent.height + 20
            radius: parent.radius + 10; color:"transparent"
            border.color: Qt.rgba(k.gilt4.r,k.gilt4.g,k.gilt4.b,0.08); border.width:8; z:-1 }
        Column {
            id: addCntCol
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: 22
            spacing: 10
            Text { text:"Add contact"; font.family:k.display; font.bold:true; font.pixelSize: fpx(16)
                   color:crd.cer4; font.letterSpacing:0.8; anchors.horizontalCenter: parent.horizontalCenter }
            Rectangle { width: parent.width; height: 38; radius: 8; color: k.surfaceHi
                border.color: addSrchInput.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                Row { anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10; spacing: 8
                    Icon { width:15;height:15; name:"search"; tint:k.inkSoft; anchors.verticalCenter: parent.verticalCenter }
                    TextInput { id: addSrchInput; width: parent.width - 30; anchors.verticalCenter: parent.verticalCenter
                        font.family:k.gar; font.pixelSize: fpx(15); color:k.ink; clip:true; selectByMouse:true
                        onTextChanged: { hub.relaySearch(text.trim()); win.dhtSearchStatus = "" }
                        Keys.onReturnPressed: {
                            var cs = text.trim()
                            if (cs.length === 0) return
                            win.dhtSearching = true; win.dhtSearchStatus = ""
                            hub.addByCallsign(cs)
                        }
                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                               text:"screen name…"; font.family:k.gar; font.italic:true; font.pixelSize: fpx(15)
                               color:k.inkSoft; opacity:.45; visible:!addSrchInput.text.length&&!addSrchInput.activeFocus } } } }
            // Search results
            Column { width: parent.width; spacing: 4; visible: hub.searchResults.length > 0
                Repeater { model: hub.searchResults
                    Rectangle { width: parent.width; height: 50; radius: 8
                        color: srchHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : k.surface
                        border.color: k.gilt1; border.width: 1
                        Row { anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right
                              anchors.rightMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                            Ava { diameter:32; fontPx:14; label: hub.initialsOf(modelData.displayName || modelData.screenName)
                                  c1: crd.cer3; c2: crd.cer2; pres: modelData.presence || "offline" }
                            Column { width: parent.width - 90; anchors.verticalCenter: parent.verticalCenter; spacing: 2
                                Text { text: modelData.displayName || modelData.screenName
                                       font.family:k.serif; font.pixelSize: fpx(14); color:k.ink; elide:Text.ElideRight; width:parent.width }
                                Text { text: modelData.location || modelData.presence || "offline"
                                       font.family:k.fell; font.italic:true; font.pixelSize: fpx(11); color:k.inkSoft } }
                            Rectangle { anchors.verticalCenter: parent.verticalCenter
                                width: addBtnTxt.implicitWidth + 18; height: 26; radius: 7
                                color: modelData.alreadyAdded ? k.surface2 : crd.cer2
                                border.color: modelData.alreadyAdded ? k.gilt1 : crd.cer1; border.width:1
                                Text { id: addBtnTxt; anchors.centerIn: parent
                                       text: modelData.alreadyAdded ? "Added" : "Add"
                                       font.family:k.titles; font.pixelSize: fpx(12)
                                       color: modelData.alreadyAdded ? k.inkSoft : k.surfaceHi }
                                TapHandler { enabled: !modelData.alreadyAdded
                                    onTapped: hub.addContact(modelData.screenName, modelData.uuid,
                                                             modelData.displayName || modelData.screenName, "Contacts") } } }
                        HoverHandler { id: srchHov } } } }
            // Status messages
            Text { visible: win.dhtSearching
                   width: parent.width; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                   text: "Calling out on the world band…"
                   font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft }
            Text { visible: !win.dhtSearching && win.dhtSearchStatus.length > 0
                   width: parent.width; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                   text: win.dhtSearchStatus
                   font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft }
            Text { visible: !win.dhtSearching && win.dhtSearchStatus.length===0 && hub.searchResults.length===0 && addSrchInput.text.length > 0
                   width: parent.width; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                   text: hub.relayConnected ? "No results on the LAN — press Enter to call them on the world band"
                                             : "Not on the LAN — press Enter to call them on the world band"
                   font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft }
            // Close button
            Rectangle { anchors.horizontalCenter: parent.horizontalCenter
                width: closeCntTxt.implicitWidth + 24; height: 30; radius: 8
                color: closeCntHov.hovered ? k.surface2 : k.surface; border.color:k.gilt1; border.width:1
                Text { id: closeCntTxt; anchors.centerIn: parent; text:"Close"
                       font.family:k.titles; font.pixelSize: fpx(13); color:k.inkSoft }
                HoverHandler { id: closeCntHov }
                TapHandler { onTapped: { win.addContactOpen = false; addSrchInput.text = "" } } }
            Item { width:1; height:4 }
        }
    }

    // ── nearby (opt-in geo-presence) panel ───────────────────────────────────────
    Timer { id: nearbyBrowseTimer; interval: 4000; onTriggered: win.nearbyBrowsing = false }
    Rectangle {
        anchors.fill: parent; z: 59; radius: 16
        color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.45)
        visible: win.browseNearbyOpen
        TapHandler { onTapped: win.browseNearbyOpen = false }
    }
    Rectangle {
        id: nearbyPanel; z: 60
        visible: win.browseNearbyOpen
        width: 350; radius: 12
        height: nearbyCol.implicitHeight + 40
        x: (parent.width  - width)  / 2
        y: 80
        color: k.panelBg
        border.color: k.gilt2; border.width: 1.5
        Rectangle { anchors.centerIn: parent; width: parent.width + 20; height: parent.height + 20
            radius: parent.radius + 10; color:"transparent"
            border.color: Qt.rgba(k.gilt4.r,k.gilt4.g,k.gilt4.b,0.08); border.width:8; z:-1 }
        Column {
            id: nearbyCol
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: 22
            spacing: 10
            Text { text:"Nearby"; font.family:k.display; font.bold:true; font.pixelSize: fpx(16)
                   color:crd.cer4; font.letterSpacing:0.8; anchors.horizontalCenter: parent.horizontalCenter }
            // Opted out — explain, offer to opt in
            Column { width: parent.width; spacing: 10; visible: !hub.shareLocation
                Text { width: parent.width; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                       text: "See who else nearby has opted into sharing their rough neighborhood on the world band. Off by default — turning it on shares only a coarse ~11km area, never a precise fix."
                       font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft }
                Rectangle { anchors.horizontalCenter: parent.horizontalCenter
                    width: shareBtnTxt.implicitWidth + 24; height: 32; radius: 8
                    color: shareBtnHov.hovered ? crd.cer3 : crd.cer2
                    border.color: crd.cer1; border.width: 1
                    Text { id: shareBtnTxt; anchors.centerIn: parent; text:"Share my location"
                           font.family:k.titles; font.pixelSize: fpx(13); color:k.surfaceHi }
                    HoverHandler { id: shareBtnHov }
                    TapHandler { onTapped: hub.setShareLocation(true) } } }
            // Opted in — browse + results
            Column { width: parent.width; spacing: 10; visible: hub.shareLocation
                Rectangle { anchors.horizontalCenter: parent.horizontalCenter
                    width: browseBtnTxt.implicitWidth + 24; height: 32; radius: 8
                    color: browseBtnHov.hovered ? k.surface2 : k.surface
                    border.color: k.gilt1; border.width: 1
                    Text { id: browseBtnTxt; anchors.centerIn: parent
                           text: win.nearbyBrowsing ? "Listening…" : "Browse nearby"
                           font.family:k.titles; font.pixelSize: fpx(13); color:k.ink }
                    HoverHandler { id: browseBtnHov }
                    TapHandler { onTapped: { win.nearbyBrowsing = true; nearbyBrowseTimer.restart(); hub.browseNearby() } } }
                // Cartographer's chart of nearby stations. Fed by the coarse
                // per-peer lat/lon now carried through Magpie's geo band (fix G6):
                // hub.nearbyResults entries gained lat/lon keys, so NCDEGeoChart
                // can place a pin per peer. Compact chrome; the self "you are here"
                // marker is hidden (the hub exposes no self fix to plot).
                NCDEGeoChart {
                    width: parent.width; height: 172
                    visible: hub.nearbyResults.length > 0
                    peers: hub.nearbyResults
                    showSelf: false
                    showPlate: false
                    showFoot: false
                    showBadge: false
                    showBanner: false
                    markerScale: 0.85
                    onPeerActivated: (callsign) => { if (callsign.length) hub.addByCallsign(callsign) }
                }
                Column { width: parent.width; spacing: 4; visible: hub.nearbyResults.length > 0
                    Repeater { model: hub.nearbyResults
                        Rectangle { width: parent.width; height: 50; radius: 8
                            color: nearbyHovR.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.10) : k.surface
                            border.color: k.gilt1; border.width: 1
                            Row { anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right
                                  anchors.rightMargin: 10; anchors.verticalCenter: parent.verticalCenter; spacing: 10
                                Ava { diameter:32; fontPx:14; label: hub.initialsOf(modelData.callsign)
                                      c1: crd.cer3; c2: crd.cer2; pres: modelData.presence || "offline" }
                                Text { width: parent.width - 90; text: modelData.callsign
                                       font.family:k.serif; font.pixelSize: fpx(14); color:k.ink
                                       elide:Text.ElideRight; anchors.verticalCenter: parent.verticalCenter }
                                Rectangle { anchors.verticalCenter: parent.verticalCenter
                                    width: nearAddTxt.implicitWidth + 18; height: 26; radius: 7
                                    color: crd.cer2; border.color: crd.cer1; border.width:1
                                    Text { id: nearAddTxt; anchors.centerIn: parent; text:"Add"
                                           font.family:k.titles; font.pixelSize: fpx(12); color:k.surfaceHi }
                                    TapHandler { onTapped: hub.addByCallsign(modelData.callsign) } } }
                            HoverHandler { id: nearbyHovR } } } }
                Text { visible: !win.nearbyBrowsing && hub.nearbyResults.length === 0
                       width: parent.width; wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                       text: "No one nearby has shared their location yet."
                       font.family:k.fell; font.italic:true; font.pixelSize: fpx(12); color:k.inkSoft }
                Text { anchors.horizontalCenter: parent.horizontalCenter
                       text: "stop sharing my location"; font.family:k.fell; font.italic:true
                       font.pixelSize: fpx(11); font.underline: stopShareHov.hovered; color:k.inkSoft
                       TapHandler { onTapped: hub.setShareLocation(false) }
                       HoverHandler { id: stopShareHov } } }
            // Close button
            Rectangle { anchors.horizontalCenter: parent.horizontalCenter
                width: closeNearTxt.implicitWidth + 24; height: 30; radius: 8
                color: closeNearHov.hovered ? k.surface2 : k.surface; border.color:k.gilt1; border.width:1
                Text { id: closeNearTxt; anchors.centerIn: parent; text:"Close"
                       font.family:k.titles; font.pixelSize: fpx(13); color:k.inkSoft }
                HoverHandler { id: closeNearHov }
                TapHandler { onTapped: win.browseNearbyOpen = false } }
            Item { width:1; height:4 }
        }
    }

    // ── emoji quickpick panel (floats above composer) ───────────────────────────
    Rectangle {
        id: emojiPanel; z: 30
        visible: win.emojiOpen
        width: 272; radius: 10
        height: emojiGrid.implicitHeight + 22
        x: win.width - 252 - 252  // sidebar(252) + roster(222) + send(40) + margins ≈ right of thread composer
        y: win.height - height - 86
        color: k.panelBg; border.color: k.gilt2; border.width: 1.5
        Column {
            id: emojiGrid
            anchors.top: parent.top; anchors.topMargin: 12
            anchors.left: parent.left; anchors.leftMargin: 10
            width: parent.width - 20; spacing: 4
            property var rows: [
                ["😊","😂","❤️","👍","😎","🙏","🎉","✨"],
                ["😅","🤔","😍","😭","🙈","🤦","🥰","🔥"],
                ["👋","💪","🌟","💯","✅","🕊️","📖","🎵"],
                ["🌿","⚜️","🕊️","🌅","🌙","❄️","🌸","🦅"]
            ]
            Repeater {
                model: emojiGrid.rows
                Row {
                    spacing: 4
                    Repeater {
                        model: modelData
                        Rectangle {
                            width: 28; height: 28; radius: 6
                            color: eHov.hovered ? Qt.rgba(k.cer.r, k.cer.g, k.cer.b, 0.15) : "transparent"
                            Text { anchors.centerIn: parent; text: modelData; font.pixelSize: fpx(16) }
                            HoverHandler { id: eHov }
                            TapHandler { onTapped: {
                                if (win.reactTargetMsgId !== "") {
                                    hub.react(win.reactTargetMsgId, modelData)
                                    win.reactTargetMsgId = ""
                                } else {
                                    inputEdit.insert(inputEdit.cursorPosition, modelData)
                                }
                                win.emojiOpen = false
                            } }
                        }
                    }
                }
            }
        }
    }
    // close emoji panel when tapping outside
    Rectangle {
        anchors.fill: parent; z: 29; color: "transparent"
        visible: win.emojiOpen
        TapHandler { onTapped: { win.emojiOpen = false; win.reactTargetMsgId = "" } }
    }

    // ── create-channel overlay ───────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent; z: 59; radius: 16
        color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.45)
        visible: win.createChanOpen
        TapHandler { onTapped: { win.createChanOpen = false; chanNameInput.text = ""; chanTopicInput.text = "" } }
    }
    Rectangle {
        id: createChanPanel; z: 60
        visible: win.createChanOpen
        width: 340; radius: 12
        height: createChanCol.implicitHeight + 40
        x: (parent.width  - width)  / 2
        y: 70
        color: k.panelBg; border.color: k.gilt2; border.width: 1.5
        Column {
            id: createChanCol
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: 22
            spacing: 10
            Text { text:"New Channel"; font.family:k.display; font.bold:true; font.pixelSize: fpx(16)
                   color:crd.cer4; font.letterSpacing:0.8; anchors.horizontalCenter: parent.horizontalCenter }
            Rectangle { width: parent.width; height: 38; radius: 8; color: k.surfaceHi
                border.color: chanNameInput.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                Row { anchors.fill: parent; anchors.leftMargin: 12; anchors.rightMargin: 12; spacing: 8
                    Text { anchors.verticalCenter: parent.verticalCenter; text: "#"
                           font.family:k.titles; font.bold:true; font.pixelSize: fpx(15); color:crd.cer2 }
                    TextInput { id: chanNameInput; width: parent.width - 24; anchors.verticalCenter: parent.verticalCenter
                        font.family:k.gar; font.pixelSize: fpx(15); color:k.ink; clip:true; selectByMouse:true
                        maximumLength: 32
                        Keys.onReturnPressed: chanTopicInput.forceActiveFocus()
                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                               text:"channel-name"; font.family:k.gar; font.italic:true
                               font.pixelSize: fpx(15); color:k.inkSoft; opacity:.45
                               visible:!chanNameInput.text.length&&!chanNameInput.activeFocus } } } }
            Rectangle { width: parent.width; height: 38; radius: 8; color: k.surfaceHi
                border.color: chanTopicInput.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                TextInput { id: chanTopicInput; width: parent.width - 24
                    anchors { fill: parent; leftMargin: 12; rightMargin: 12 }
                    verticalAlignment: TextInput.AlignVCenter
                    font.family:k.gar; font.pixelSize: fpx(15); color:k.ink; clip:true; selectByMouse:true
                    Keys.onReturnPressed: {
                        var n = chanNameInput.text.trim()
                        if (n.length > 0) { hub.createChannel(n, chanTopicInput.text.trim()); win.createChanOpen = false; chanNameInput.text = ""; chanTopicInput.text = "" }
                    }
                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                           text:"topic (optional)"; font.family:k.gar; font.italic:true
                           font.pixelSize: fpx(15); color:k.inkSoft; opacity:.45
                           visible:!chanTopicInput.text.length&&!chanTopicInput.activeFocus } } }
            Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 10
                Rectangle { width: closeCCTxt.implicitWidth + 24; height: 30; radius: 8
                    color: closeCCHov.hovered ? k.surface2 : k.surface; border.color:k.gilt1; border.width:1
                    Text { id: closeCCTxt; anchors.centerIn: parent; text:"Cancel"
                           font.family:k.titles; font.pixelSize: fpx(13); color:k.inkSoft }
                    HoverHandler { id: closeCCHov }
                    TapHandler { onTapped: { win.createChanOpen = false; chanNameInput.text = ""; chanTopicInput.text = "" } } }
                Rectangle { width: createChanTxt.implicitWidth + 24; height: 30; radius: 8
                    color: createChanHov.hovered ? crd.cer4 : crd.cer3; border.color:crd.cer2; border.width:1
                    enabled: chanNameInput.text.trim().length > 0
                    opacity: enabled ? 1.0 : 0.45
                    Text { id: createChanTxt; anchors.centerIn: parent; text:"Create"
                           font.family:k.titles; font.pixelSize: fpx(13); color:k.surfaceHi }
                    HoverHandler { id: createChanHov }
                    TapHandler { onTapped: {
                        var n = chanNameInput.text.trim()
                        if (n.length > 0) { hub.createChannel(n, chanTopicInput.text.trim()); win.createChanOpen = false; chanNameInput.text = ""; chanTopicInput.text = "" }
                    } } }
            }
            Item { width:1; height:4 }
        }
    }

    // ── first-launch setup overlay (step 1: screen name · step 2: password) ────
    Rectangle {
        id: firstLaunchOverlay
        anchors.fill: parent
        visible: win.firstLaunch
        color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.97)
        radius: 16
        property int setupStep: 1

        function submitName() {
            var n = nameInput.text.trim()
            if (n.length < 3 || !/^[a-zA-Z0-9_-]+$/.test(n)) {
                nameHint.text = "3-24 characters: letters, numbers, _ and - only"
                nameHint.color = k.wine4
                shakeAnim.start()
                return
            }
            hub.saveScreenName(n)
            firstLaunchOverlay.setupStep = 2
            pw1Input.forceActiveFocus()
        }

        function submitPassword() {
            var p1 = pw1Input.text
            var p2 = pw2Input.text
            if (p1.length < 6) {
                pwHint.text = "Minimum 6 characters"
                pwHint.color = k.wine4
                shakeAnim.start()
                return
            }
            if (p1 !== p2) {
                pwHint.text = "Passwords do not match"
                pwHint.color = k.wine4
                shakeAnim.start()
                return
            }
            // Global reach is the DHT world band now, not a Jabber account (removed 2026-07-05) —
            // savePassword() just stores the local credential; add-by-callsign is how anyone anywhere
            // is reached.
            hub.savePassword(p1)
            firstLaunchOverlay.finishSetup()
        }

        function finishSetup() {
            win.firstLaunch = false
            hub.start()
        }

        SequentialAnimation {
            id: shakeAnim
            NumberAnimation { target: setupCard; property: "shakeX"; to: -9; duration: 55 }
            NumberAnimation { target: setupCard; property: "shakeX"; to:  9; duration: 55 }
            NumberAnimation { target: setupCard; property: "shakeX"; to: -5; duration: 45 }
            NumberAnimation { target: setupCard; property: "shakeX"; to:  5; duration: 45 }
            NumberAnimation { target: setupCard; property: "shakeX"; to:  0; duration: 40 }
        }

        Rectangle {
            id: setupCard
            property real shakeX: 0
            width: 400
            height: setupCol.implicitHeight + 56
            radius: 14
            x: (parent.width  - width)  / 2 + shakeX
            y: (parent.height - height) / 2
            color: k.panelBg
            border.color: k.gilt2; border.width: 1.5

            Rectangle {
                anchors.centerIn: parent
                width: setupCard.width + 20; height: setupCard.height + 20
                radius: setupCard.radius + 10; color: "transparent"
                border.color: Qt.rgba(k.gilt4.r, k.gilt4.g, k.gilt4.b, 0.10); border.width: 8
                z: -1
            }

            Column {
                id: setupCol
                width: parent.width - 56
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top; anchors.topMargin: 28
                spacing: 0

                // ── shared header ──────────────────────────────────────────
                Magpie { width: 40; height: 40; anchors.horizontalCenter: parent.horizontalCenter }
                Item { width: 1; height: 14 }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Magpie Talker"
                    font.family: k.display; font.bold: true; font.pixelSize: k.fs(22)
                    color: crd.cer4; font.letterSpacing: 1.2
                }
                Item { width: 1; height: 5 }

                // ── step 1: screen name ────────────────────────────────────
                Column {
                    visible: firstLaunchOverlay.setupStep === 1
                    height: visible ? implicitHeight : 0
                    width: parent.width; spacing: 0

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Choose your screen name"
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(14); color: k.inkSoft
                    }
                    Item { width: 1; height: 26 }
                    Rectangle {
                        width: parent.width; height: 42; radius: 8; color: k.surfaceHi
                        border.color: nameInput.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                        TextInput {
                            id: nameInput
                            anchors { fill: parent; leftMargin: 14; rightMargin: 14 }
                            verticalAlignment: TextInput.AlignVCenter
                            font.family: k.gar; font.pixelSize: k.fs(16); color: k.ink
                            maximumLength: 24; clip: true; selectByMouse: true
                            onTextChanged: { nameHint.text = "3-24 characters: letters, numbers, _ and - only"; nameHint.color = k.inkSoft }
                            Keys.onReturnPressed: firstLaunchOverlay.submitName()
                            Text {
                                anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                text: "your_screen_name"; font.family: k.gar; font.italic: true
                                font.pixelSize: k.fs(16); color: k.inkSoft; opacity: 0.45
                                visible: !nameInput.text.length && !nameInput.activeFocus
                            }
                        }
                    }
                    Item { width: 1; height: 7 }
                    Text {
                        id: nameHint; width: parent.width
                        text: "3-24 characters: letters, numbers, _ and - only"
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(11)
                        color: k.inkSoft; horizontalAlignment: Text.AlignHCenter; opacity: 0.7
                    }
                    Item { width: 1; height: 18 }
                    Text {
                        width: parent.width
                        text: "This is how people will find you.\nYour screen name is permanent."
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(12)
                        color: k.inkSoft; horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap; lineHeight: 1.5
                    }
                    Item { width: 1; height: 22 }
                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: contTxt.implicitWidth + 48; height: 38; radius: 10
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop { position: 0; color: contHov.hovered ? crd.cer4 : crd.cer3 }
                            GradientStop { position: 1; color: crd.cer2 }
                        }
                        border.color: k.gilt1; border.width: 1.5
                        Text { id: contTxt; anchors.centerIn: parent; text: "Continue  →"
                               font.family: k.titles; font.pixelSize: k.fs(14); font.letterSpacing: 1; color: k.surfaceHi }
                        HoverHandler { id: contHov; cursorShape: Qt.PointingHandCursor }
                        TapHandler { onTapped: firstLaunchOverlay.submitName() }
                    }
                    Item { width: 1; height: 28 }
                }

                // ── step 2: password ───────────────────────────────────────
                Column {
                    visible: firstLaunchOverlay.setupStep === 2
                    height: visible ? implicitHeight : 0
                    width: parent.width; spacing: 0

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Set a password for \"" + hub.meUser + "\""
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(14); color: k.inkSoft
                    }
                    Item { width: 1; height: 22 }
                    Rectangle {
                        width: parent.width; height: 42; radius: 8; color: k.surfaceHi
                        border.color: pw1Input.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                        TextInput {
                            id: pw1Input
                            anchors { fill: parent; leftMargin: 14; rightMargin: 14 }
                            verticalAlignment: TextInput.AlignVCenter
                            font.family: k.gar; font.pixelSize: k.fs(16); color: k.ink
                            echoMode: TextInput.Password; clip: true; selectByMouse: true
                            onTextChanged: { pwHint.text = "Min. 6 characters"; pwHint.color = k.inkSoft }
                            Keys.onReturnPressed: pw2Input.forceActiveFocus()
                            Text {
                                anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                text: "password"; font.family: k.gar; font.italic: true
                                font.pixelSize: k.fs(16); color: k.inkSoft; opacity: 0.45
                                visible: !pw1Input.text.length && !pw1Input.activeFocus
                            }
                        }
                    }
                    Item { width: 1; height: 10 }
                    Rectangle {
                        width: parent.width; height: 42; radius: 8; color: k.surfaceHi
                        border.color: pw2Input.activeFocus ? crd.cer3 : k.gilt1; border.width: 1.5
                        TextInput {
                            id: pw2Input
                            anchors { fill: parent; leftMargin: 14; rightMargin: 14 }
                            verticalAlignment: TextInput.AlignVCenter
                            font.family: k.gar; font.pixelSize: k.fs(16); color: k.ink
                            echoMode: TextInput.Password; clip: true; selectByMouse: true
                            onTextChanged: { pwHint.text = "Min. 6 characters"; pwHint.color = k.inkSoft }
                            Keys.onReturnPressed: firstLaunchOverlay.submitPassword()
                            Text {
                                anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                text: "confirm password"; font.family: k.gar; font.italic: true
                                font.pixelSize: k.fs(16); color: k.inkSoft; opacity: 0.45
                                visible: !pw2Input.text.length && !pw2Input.activeFocus
                            }
                        }
                    }
                    Item { width: 1; height: 7 }
                    Text {
                        id: pwHint; width: parent.width
                        text: "Min. 6 characters"
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(11)
                        color: k.inkSoft; horizontalAlignment: Text.AlignHCenter; opacity: 0.7
                    }
                    Item { width: 1; height: 16 }
                    Text {
                        width: parent.width
                        text: "Stored securely in your keyring.\nYou will not be asked again."
                        font.family: k.fell; font.italic: true; font.pixelSize: k.fs(12)
                        color: k.inkSoft; horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap; lineHeight: 1.5
                    }
                    Item { width: 1; height: 22 }
                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: doneTxt.implicitWidth + 48; height: 38; radius: 10
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop { position: 0; color: doneHov.hovered ? crd.cer4 : crd.cer3 }
                            GradientStop { position: 1; color: crd.cer2 }
                        }
                        border.color: k.gilt1; border.width: 1.5
                        Text { id: doneTxt; anchors.centerIn: parent; text: "Done"
                               font.family: k.titles; font.pixelSize: k.fs(14); font.letterSpacing: 1; color: k.surfaceHi }
                        HoverHandler { id: doneHov; cursorShape: Qt.PointingHandCursor }
                        TapHandler { onTapped: firstLaunchOverlay.submitPassword() }
                    }
                    Item { width: 1; height: 28 }
                }
            }
        }
    }

    // ── avatar picker overlay — the same 19 round celestial avatars UsersTab.qml offers ──────
    Rectangle {
        id: avatarPickerOverlay
        anchors.fill: parent
        visible: win.avatarPickerOpen
        color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.97)
        radius: 16

        Rectangle {
            anchors.centerIn: parent
            width: 360; height: avatarPickCol.implicitHeight + 56
            radius: 14; color: k.panelBg
            border.color: k.gilt2; border.width: 1.5

            Column {
                id: avatarPickCol
                width: parent.width - 48
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top; anchors.topMargin: 24
                spacing: 0

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Choose your avatar"
                    font.family: k.display; font.bold: true; font.pixelSize: k.fs(18)
                    color: crd.cer4; font.letterSpacing: 1
                }
                Item { width: 1; height: 18 }

                Flow {
                    width: parent.width; spacing: 8
                    Repeater {
                        model: win.avatarList
                        Rectangle {
                            property bool isCurrent: hub.meAvatarUrl.indexOf(modelData) >= 0
                            width: 48; height: 48; radius: 24; clip: true
                            color: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, isCurrent ? 0.3 : 0.1)
                            border.color: isCurrent ? k.gilt2 : Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, 0.4)
                            border.width: isCurrent ? 2 : 1
                            Image {
                                anchors.fill: parent
                                source: settings.assetBase + modelData
                                fillMode: Image.PreserveAspectFit; smooth: true; asynchronous: true
                            }
                            HoverHandler { id: avPickHov; cursorShape: Qt.PointingHandCursor }
                            TapHandler { onTapped: win.chooseAvatar(modelData) }
                        }
                    }
                }
                Item { width: 1; height: 20 }
                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: closeAvPickTxt.implicitWidth + 24; height: 34; radius: 8
                    color: closeAvPickHov.hovered ? k.surface2 : k.surface
                    border.color: k.gilt1; border.width: 1
                    Text { id: closeAvPickTxt; anchors.centerIn: parent; text: "Close"
                           font.family: k.titles; font.pixelSize: k.fs(13); color: k.inkSoft }
                    HoverHandler { id: closeAvPickHov; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: win.avatarPickerOpen = false }
                }
                Item { width: 1; height: 24 }
            }
        }
    }

    // ── login panel (keyring unavailable — NCDECommand authFace pattern) ────────
    Item {
        id: loginFace
        anchors.fill: parent
        opacity: win.loginActive ? 1 : 0
        visible: opacity > 0.01
        enabled: win.loginActive
        onEnabledChanged: if (enabled) loginPwInput.forceActiveFocus()
        Behavior on opacity { NumberAnimation { duration: 420; easing.type: Easing.OutCubic } }

        property int  triesLeft: 3
        property bool locked: false
        property real shakeX: 0

        function submitLogin() {
            if (loginFace.locked || !loginPwInput.text.length) return
            if (hub.verifyPassword(loginPwInput.text)) {
                win.loginActive = false
                loginPwInput.text = ""
                loginFace.triesLeft = 3
                hub.start()
            } else {
                loginFace.triesLeft -= 1
                loginPwInput.text = ""
                loginShake.start()
                if (loginFace.triesLeft <= 0) loginFace.locked = true
            }
        }

        SequentialAnimation {
            id: loginShake
            NumberAnimation { target: loginFace; property: "shakeX"; to: -9; duration: 55 }
            NumberAnimation { target: loginFace; property: "shakeX"; to:  9; duration: 55 }
            NumberAnimation { target: loginFace; property: "shakeX"; to: -5; duration: 45 }
            NumberAnimation { target: loginFace; property: "shakeX"; to:  5; duration: 45 }
            NumberAnimation { target: loginFace; property: "shakeX"; to:  0; duration: 40 }
        }

        // dim veil over app content
        Rectangle {
            anchors.fill: parent; radius: 16
            color: Qt.rgba(crd.cer1.r, crd.cer1.g, crd.cer1.b, 0.60)
        }

        // login strip at bottom — same height as statusbar area
        Rectangle {
            id: loginStrip
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: parent.bottom; height: 46
            transform: Translate { x: loginFace.shakeX }
            gradient: Gradient { orientation: Gradient.Vertical
                GradientStop { position: 0; color: crd.cer2 }
                GradientStop { position: 1; color: crd.cer1 }
            }
            Rectangle { anchors.top: parent.top; width: parent.width; height: 1.5; color: k.gilt3 }

            // Left: pulsing lock + SIGN IN + screen name
            Row {
                id: loginLeft
                anchors.left: parent.left; anchors.leftMargin: 16
                anchors.verticalCenter: parent.verticalCenter; spacing: 9
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "⚿"; color: k.gilt4; font.pixelSize: k.fs(15)
                    SequentialAnimation on opacity {
                        running: win.loginActive && win.motionEnabled
                                 && (typeof animPolicy === "undefined" || animPolicy === null
                                     || (animPolicy.decorative && !animPolicy.screenIdle))
                        loops: Animation.Infinite
                        NumberAnimation { from: 0.7; to: 1.0; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 1800 : 900; easing.type: Easing.InOutSine }
                        NumberAnimation { from: 1.0; to: 0.7; duration: (typeof animPolicy !== "undefined" && animPolicy !== null && (animPolicy.lowPower || animPolicy.thermalPressure)) ? 1800 : 900; easing.type: Easing.InOutSine }
                    }
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "SIGN IN"
                    color: k.gilt3; font.family: k.display; font.pixelSize: k.fs(11); font.letterSpacing: 1.7
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: hub.meUser
                    color: k.gilt5; font.family: k.display; font.pixelSize: k.fs(11); font.letterSpacing: 1.0
                }
            }

            // Right: error · ENTER pill · dismiss
            Row {
                id: loginRight
                anchors.right: parent.right; anchors.rightMargin: 14
                anchors.verticalCenter: parent.verticalCenter; spacing: 11
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: loginFace.triesLeft < 3 && !loginFace.locked
                    text: "not accepted — " + loginFace.triesLeft + " left"
                    color: k.wine4; font.family: k.fell; font.italic: true; font.pixelSize: k.fs(13)
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: loginFace.locked
                    text: "locked — restart to try again"
                    color: k.wine4; font.family: k.fell; font.italic: true; font.pixelSize: k.fs(13)
                }
                Rectangle {
                    visible: !loginFace.locked
                    anchors.verticalCenter: parent.verticalCenter
                    width: enterLbl.implicitWidth + 14; height: 19; radius: 5
                    color: enterHov.hovered ? Qt.rgba(1,1,1,0.06) : "transparent"
                    border.color: k.gilt0; border.width: 1
                    Behavior on color { ColorAnimation { duration: 120 } }
                    Text {
                        id: enterLbl; anchors.centerIn: parent
                        text: "↵ ENTER"; color: k.gilt2
                        font.family: k.display; font.pixelSize: k.fs(9); font.letterSpacing: 1.2
                    }
                    HoverHandler { id: enterHov; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: loginFace.submitLogin() }
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "✕"; color: dismissLoginHov.hovered ? k.gilt4 : k.gilt2; font.pixelSize: k.fs(14)
                    HoverHandler { id: dismissLoginHov; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: win.loginActive = false }
                }
            }

            // Centre: password TextInput with gilt underline
            Item {
                anchors.left: loginLeft.right; anchors.right: loginRight.left
                anchors.leftMargin: 14; anchors.rightMargin: 14
                anchors.verticalCenter: parent.verticalCenter; height: 26
                Rectangle {
                    anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
                    height: 1
                    color: loginFace.triesLeft < 3 ? k.wine4 : k.gilt1
                    Behavior on color { ColorAnimation { duration: 180 } }
                }
                TextInput {
                    id: loginPwInput
                    anchors.fill: parent; anchors.bottomMargin: 4
                    verticalAlignment: TextInput.AlignVCenter
                    font.family: k.fell; font.italic: true; font.pixelSize: k.fs(14); color: k.gilt5
                    echoMode: TextInput.Password; clip: true; selectByMouse: true
                    enabled: !loginFace.locked
                    Keys.onReturnPressed: loginFace.submitLogin()
                    Text {
                        anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                        text: "enter password"; font.family: k.fell; font.italic: true
                        font.pixelSize: k.fs(14); color: k.gilt2; opacity: 0.45
                        visible: !loginPwInput.text.length && !loginPwInput.activeFocus
                    }
                }
            }
        }
    }

    function doSend(){
        var t = inputEdit.text;
        if (!t || t.trim().length===0) return;
        hub.sendMessage(t);
        inputEdit.text = "";
        win.composerTyping = false; hub.setTyping(false);
    }

    Component.onCompleted: {
        if (!hub.hasIdentity())            win.firstLaunch = true
        else if (!hub.hasStoredPassword()) win.loginActive = true
        else                               hub.start()
    }

    MagpieTalkerManual { id: manual }

    // D-3 (MP-SEC-1): link safety overlay — appears when a flagged URL is tapped.
    Rectangle {
        id: mpLinkBanner
        visible: win.linkPendingStatus !== ""
        anchors { left: parent.left; right: parent.right; bottom: parent.bottom; bottomMargin: 80 }
        height: mpLinkCol.implicitHeight + 20; z: 20
        color: Qt.rgba(k.rose.r, k.rose.g, k.rose.b, 0.94)
        Column {
            id: mpLinkCol
            anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; margins: 16 }
            spacing: 8
            Text {
                width: parent.width
                text: "Vesper: " + win.linkPendingStatus.replace("blocked:","").replace(/_/g," ") + " — this domain is on the block list."
                font.family: k.fell; font.italic: true; font.pixelSize: fpx(13); color: k.surfaceHi
                wrapMode: Text.WordWrap
            }
            Row {
                spacing: 10
                Rectangle {
                    height: 28; width: mpOpenLbl.implicitWidth + 20; radius: 14
                    color: Qt.rgba(1, 1, 1, 0.2); border.width: 1; border.color: k.surfaceHi
                    Text { id: mpOpenLbl; anchors.centerIn: parent; text: "Open Anyway"
                           font.family: k.fell; font.pixelSize: fpx(12); color: k.surfaceHi }
                    TapHandler { onTapped: {
                        launcher.systemCommand("ncde-chromium " + win.linkPendingUrl);
                        win.linkPendingUrl = ""; win.linkPendingStatus = "";
                    } }
                }
                Rectangle {
                    height: 28; width: mpCancelLbl.implicitWidth + 20; radius: 14
                    color: "transparent"; border.width: 1; border.color: k.surfaceHi
                    Text { id: mpCancelLbl; anchors.centerIn: parent; text: "Cancel"
                           font.family: k.fell; font.pixelSize: fpx(12); color: k.surfaceHi }
                    TapHandler { onTapped: { win.linkPendingUrl = ""; win.linkPendingStatus = ""; } }
                }
            }
        }
    }

    // ═════ FLUTTER — the call view (FLUTTER-PLAN §1: the ONE button above transforms the whole
    // interface — chat swaps out, full-viewport video takes over "like cheese", the visible
    // Hang Up control reverses it). The two video items are PERMANENT scene members, never inside
    // a Loader: FlutterCall (C++) keeps raw QQuickItem pointers from hub.attach*VideoTarget, and a
    // Loader tearing them down would leave those dangling. Hidden they cost nothing — the GL path
    // only exists while a sink renders into them. ═════
    Rectangle {
        id: flutterLayer
        anchors.fill: parent
        z: 40
        visible: hub.callState === "calling" || hub.callState === "active"
        // Solid black behind all video, ALWAYS — never Qt's default white (epilepsy safety; same
        // class of hazard as the terminal white-screen regression).
        color: "black"

        // Full-frame remote stream — the video IS the interface.
        GstGLQt6VideoItem {
            id: flutterRemote
            anchors.fill: parent
            Component.onCompleted: hub.attachRemoteVideoTarget(flutterRemote)
        }

        // Honest status line — "starting" is pipeline-up-but-not-yet-confirmed; "active" only
        // comes from the pipeline actually reaching PLAYING (FlutterCall bus watch).
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: 26
            text: hub.callState === "calling" ? "Calling " + win.callPeerName + " on the wing…"
                : hub.mediaState === "starting" ? "On the wire — opening the camera…"
                : hub.mediaState === "failed"   ? "The wire dropped — hang up and try again."
                    + (win.lastMediaError !== "" ? " (" + win.lastMediaError + ")" : "")
                : ""
            visible: text !== ""
            font.family: k.fell; font.italic: true; font.pixelSize: fpx(15); color: k.surfaceHi
        }

        // Local preview — postage stamp, bottom-right, only once media is really up.
        Rectangle {
            anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 18
            width: 216; height: 124; radius: 6; color: "black"
            border.color: k.gilt1; border.width: 1.5
            visible: hub.mediaState === "starting" || hub.mediaState === "active"
            GstGLQt6VideoItem {
                id: flutterLocal
                anchors.fill: parent; anchors.margins: 2
                Component.onCompleted: hub.attachLocalVideoTarget(flutterLocal)
            }
        }

        // Hang Up — the visible control that reverses the transform (operator spec, §1).
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom; anchors.bottomMargin: 22
            width: hangLbl.implicitWidth + 44; height: 40; radius: 20
            color: Qt.rgba(k.rose.r, k.rose.g, k.rose.b, hangHov.hovered ? 1.0 : 0.88)
            border.color: k.gilt1; border.width: 1.5
            Text { id: hangLbl; anchors.centerIn: parent; text: "Hang Up"
                   font.family: k.display; font.bold: true; font.pixelSize: fpx(15); color: k.surfaceHi }
            HoverHandler { id: hangHov }
            TapHandler { onTapped: hub.endCall() }
        }

        // Backdrop — green-screen background replacement (operator spec 2026-07-06, "like Zoom").
        // Scenes come from hub.videoBackgrounds() (/usr/share/ncde/flutter-backgrounds/) and apply
        // LIVE mid-call: hub.setVideoBackground swaps the frozen compositor frame, no re-call
        // needed. The choice persists (flutter.json) and holds for future calls until changed.
        Rectangle {
            id: backdropBtn
            anchors.left: parent.left; anchors.bottom: parent.bottom
            anchors.leftMargin: 22; anchors.bottomMargin: 22
            width: bdLbl.implicitWidth + 44; height: 40; radius: 20
            color: Qt.rgba(0, 0, 0, bdHov.hovered ? 0.9 : 0.65)
            border.color: k.gilt1; border.width: 1.5
            visible: hub.mediaState === "starting" || hub.mediaState === "active"
            Text { id: bdLbl; anchors.centerIn: parent; text: "Backdrop"
                   font.family: k.display; font.bold: true; font.pixelSize: fpx(15); color: k.surfaceHi }
            HoverHandler { id: bdHov }
            TapHandler { onTapped: backdropPanel.visible = !backdropPanel.visible }
        }
        Rectangle {
            id: backdropPanel
            visible: false
            anchors.left: parent.left; anchors.bottom: backdropBtn.top
            anchors.leftMargin: 22; anchors.bottomMargin: 12
            width: bdCol.implicitWidth + 36; height: bdCol.implicitHeight + 32; radius: 12
            color: k.surface; border.color: k.gilt1; border.width: 1.5
            Column {
                id: bdCol; anchors.centerIn: parent; spacing: 10
                Text { text: "Choose a backdrop"; font.family: k.display; font.bold: true
                       font.pixelSize: fpx(14); color: crd.cer1 }
                Text { text: "Hang a plain green sheet behind you, then pick a scene."
                       font.family: k.fell; font.italic: true; font.pixelSize: fpx(12); color: k.inkSoft }
                Grid {
                    columns: 4; spacing: 8
                    // "None" — the honest camera, no replacement.
                    Rectangle {
                        width: 88; height: 52; radius: 6; color: "black"
                        border.width: hub.videoBackground === "" ? 2.5 : 1
                        border.color: hub.videoBackground === "" ? k.gilt1 : k.inkSoft
                        Text { anchors.centerIn: parent; text: "None"
                               font.family: k.fell; font.pixelSize: fpx(12); color: k.surfaceHi }
                        TapHandler { onTapped: hub.setVideoBackground("") }
                    }
                    Repeater {
                        model: hub.videoBackgrounds()
                        delegate: Rectangle {
                            width: 88; height: 52; radius: 6; color: "black"; clip: true
                            border.width: hub.videoBackground === modelData ? 2.5 : 1
                            border.color: hub.videoBackground === modelData ? k.gilt1 : k.inkSoft
                            Image {
                                anchors.fill: parent; anchors.margins: 1
                                source: "file://" + modelData
                                fillMode: Image.PreserveAspectCrop
                                asynchronous: true
                                sourceSize.width: 176   // thumbnail decode, never the full image
                            }
                            TapHandler { onTapped: hub.setVideoBackground(modelData) }
                        }
                    }
                }
                Row {
                    spacing: 10
                    Text { text: "Sheet color:"; anchors.verticalCenter: parent.verticalCenter
                           font.family: k.fell; font.italic: true; font.pixelSize: fpx(12); color: k.inkSoft }
                    Repeater {
                        model: [ { c: "#00ff00", n: "Green" }, { c: "#0000ff", n: "Blue" } ]
                        delegate: Rectangle {
                            width: 64; height: 26; radius: 13; color: modelData.c
                            anchors.verticalCenter: parent.verticalCenter
                            border.width: hub.videoKeyColor === modelData.c ? 2.5 : 1
                            border.color: hub.videoKeyColor === modelData.c ? k.gilt1 : k.inkSoft
                            Text { anchors.centerIn: parent; text: modelData.n
                                   font.family: k.fell; font.pixelSize: fpx(11); color: "black" }
                            TapHandler { onTapped: hub.setVideoKeyColor(modelData.c) }
                        }
                    }
                }
            }
        }
    }

    // Incoming ring — over the chat (the full transform happens on Answer).
    Rectangle {
        anchors.fill: parent; z: 50; color: Qt.rgba(0, 0, 0, 0.45)
        visible: hub.callState === "ringing"
        TapHandler { onTapped: {} }   // swallow taps under the ring panel
        Rectangle {
            anchors.centerIn: parent; width: 380; height: ringCol.implicitHeight + 44; radius: 12
            color: k.surface; border.color: k.gilt1; border.width: 1.5
            Column { id: ringCol; anchors.centerIn: parent; spacing: 14; width: parent.width - 48
                Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                       text: win.callPeerName + " is calling"; font.family: k.display; font.bold: true
                       font.pixelSize: fpx(18); color: crd.cer1; wrapMode: Text.WordWrap }
                Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                       text: "A Flutter call — answering turns this whole window into the call."
                       font.family: k.fell; font.italic: true; font.pixelSize: fpx(13); color: k.inkSoft
                       wrapMode: Text.WordWrap }
                Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 14
                    Rectangle { width: 120; height: 36; radius: 18
                        color: Qt.rgba(k.verd.r, k.verd.g, k.verd.b, accHov.hovered ? 1.0 : 0.85)
                        border.color: k.gilt1; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "Answer"; font.family: k.display
                               font.bold: true; font.pixelSize: fpx(14); color: k.surfaceHi }
                        HoverHandler { id: accHov }
                        TapHandler { onTapped: hub.acceptCall() } }
                    Rectangle { width: 120; height: 36; radius: 18
                        color: Qt.rgba(k.rose.r, k.rose.g, k.rose.b, decHov.hovered ? 1.0 : 0.85)
                        border.color: k.gilt1; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "Decline"; font.family: k.display
                               font.bold: true; font.pixelSize: fpx(14); color: k.surfaceHi }
                        HoverHandler { id: decHov }
                        TapHandler { onTapped: hub.declineCall() } }
                }
            }
        }
    }

    // Consent gate — the camera/mic NEVER open before an explicit Allow (FlutterCall enforces
    // that in C++; this is the prompt it waits on). Sits above the call layer.
    Rectangle {
        anchors.fill: parent; z: 60; color: Qt.rgba(0, 0, 0, 0.45)
        visible: hub.mediaState === "awaitingConsent"
        TapHandler { onTapped: {} }
        Rectangle {
            anchors.centerIn: parent; width: 400; height: consCol.implicitHeight + 44; radius: 12
            color: k.surface; border.color: k.gilt1; border.width: 1.5
            Column { id: consCol; anchors.centerIn: parent; spacing: 14; width: parent.width - 48
                Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                       text: "Use the camera and microphone?"; font.family: k.display; font.bold: true
                       font.pixelSize: fpx(17); color: crd.cer1; wrapMode: Text.WordWrap }
                Text { width: parent.width; horizontalAlignment: Text.AlignHCenter
                       text: "Nothing opens until you allow it. Denying ends the call."
                       font.family: k.fell; font.italic: true; font.pixelSize: fpx(13); color: k.inkSoft
                       wrapMode: Text.WordWrap }
                Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 14
                    Rectangle { width: 120; height: 36; radius: 18
                        color: Qt.rgba(k.verd.r, k.verd.g, k.verd.b, alwHov.hovered ? 1.0 : 0.85)
                        border.color: k.gilt1; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "Allow"; font.family: k.display
                               font.bold: true; font.pixelSize: fpx(14); color: k.surfaceHi }
                        HoverHandler { id: alwHov }
                        TapHandler { onTapped: hub.setMediaConsent(true) } }
                    Rectangle { width: 120; height: 36; radius: 18
                        color: Qt.rgba(k.rose.r, k.rose.g, k.rose.b, dnyHov.hovered ? 1.0 : 0.85)
                        border.color: k.gilt1; border.width: 1.5
                        Text { anchors.centerIn: parent; text: "Deny"; font.family: k.display
                               font.bold: true; font.pixelSize: fpx(14); color: k.surfaceHi }
                        HoverHandler { id: dnyHov }
                        TapHandler { onTapped: { hub.setMediaConsent(false); hub.endCall() } } }
                }
            }
        }
    }
}
