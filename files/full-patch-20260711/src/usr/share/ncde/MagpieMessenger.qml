// ╔══════════════════════════════════════════════════════════════════════╗
// ║  MagpieMessenger.qml — Facebook Messenger through the Magpie wire      ║
// ║  Magpie is the desktop client for Messenger the way Hummingbird is for ║
// ║  Gmail: the real Messenger web client (every chat, the whole history,  ║
// ║  calls, photos, encrypted chats) runs inside Magpie, re-skinned in     ║
// ║  Magpie's own palette + type (MagpieMessengerWeb.qml). Nothing extra   ║
// ║  to download; Facebook sign-in is remembered in Magpie's own profile.  ║
// ║                                                                        ║
// ║  This file never imports QtWebEngine — the engine lives behind a       ║
// ║  Loader, so a machine without qt6-webengine still gets a working       ║
// ║  Magpie (this pane just says the engine is missing).                   ║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick
import QtQuick.Layouts
import QtCore

Item {
    id: fb

    // set by MagpieTalker.qml
    property var kit                       // NCDEKit
    property color cer1; property color cer2; property color cer3; property color cer4; property color cer5
    property real scale: 1.0               // Script Shift text dial (theme.fontMedium / 13)
    property bool ready: false             // Magpie unlocked (no sign-in face showing)
    property bool showing: false           // the Messenger pane is the one on screen
    property bool windowActive: false

    // read by MagpieTalker.qml
    readonly property bool turnedOn: store.enabled
    readonly property int  unread:   web.item ? web.item.unread : 0
    readonly property bool signedIn: web.item ? web.item.signedIn : false
    readonly property string statusLine: !store.enabled ? "not signed in"
                                       : web.status === Loader.Error ? "web engine missing"
                                       : !web.item ? "waking…"
                                       : web.item.loading ? "fetching the wire…"
                                       : !web.item.signedIn ? "sign in to Facebook"
                                       : unread > 0 ? (unread + " unread") : "all caught up"
    signal messageArrived(string title, string body)

    // cerulean that reads on the paper in both modes (cer1 is near-black in dark mode)
    readonly property color titleInk: kit && kit.dark ? cer4 : cer1
    function px(n) { return Math.round(n * fb.scale) }
    function goHome()  { if (web.item) web.item.goHome() }
    function goBack()  { if (web.item) web.item.goBack() }
    function reload()  { if (web.item) web.item.reload() }

    Settings {
        id: store
        location: StandardPaths.writableLocation(StandardPaths.GenericConfigLocation) + "/ncde/magpie/messenger.conf"
        property bool enabled: false
    }

    // The engine starts a beat after Magpie's own window is up (Magpie opens
    // without a lag) and only once Magpie is unlocked — the password face is
    // decided in MagpieTalker's Component.onCompleted, after this binding
    // would first evaluate, hence the explicit gate.
    property bool _settled: false
    Timer { interval: 1200; running: true; onTriggered: fb._settled = true }

    Loader {
        id: web
        anchors.top: bar.bottom; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        active: store.enabled && fb.ready && fb._settled
        source: "MagpieMessengerWeb.qml"
        onLoaded: {
            item.kit   = Qt.binding(function(){ return fb.kit })
            item.cer   = Qt.binding(function(){ return fb.cer3 })
            item.cerDeep = Qt.binding(function(){ return fb.kit && fb.kit.dark ? fb.cer2 : Qt.darker(fb.cer3, 1.35) })
            item.scale = Qt.binding(function(){ return fb.scale })
            item.messageArrived.connect(fb.messageArrived)
        }
    }

    // ── Magpie header over the Messenger pane ─────────────────────────────
    Rectangle {
        id: bar
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        height: Math.max(px(56), barRow.implicitHeight + px(16))
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: fb.kit ? fb.kit.surface : "white" }
            GradientStop { position: 1; color: fb.kit ? fb.kit.surface2 : "white" } }
        Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: fb.kit ? fb.kit.gilt1 : "gray" }
        RowLayout {
            id: barRow
            anchors.fill: parent; anchors.leftMargin: 18; anchors.rightMargin: 16; spacing: 12
            MessengerMark { Layout.preferredWidth: px(30); Layout.preferredHeight: px(30) }
            Text { text: "Messenger"; font.family: fb.kit.display; font.bold: true; font.pixelSize: px(18)
                   color: fb.titleInk; font.letterSpacing: 0.4 }
            Text { Layout.fillWidth: true; text: "Facebook · " + fb.statusLine
                   font.family: fb.kit.fell; font.italic: true; font.pixelSize: px(13); color: fb.kit.inkSoft
                   elide: Text.ElideRight }
            Repeater {
                model: web.item ? [ { k: "back", t: "‹ Back" }, { k: "home", t: "Chats" }, { k: "reload", t: "Refresh" } ] : []
                Rectangle {
                    Layout.preferredHeight: Math.max(px(32), lbl.implicitHeight + px(10))
                    Layout.preferredWidth: lbl.implicitWidth + px(24); radius: 8
                    border.color: hov.hovered ? fb.cer3 : fb.kit.gilt1; border.width: 1.5; color: fb.kit.surfaceHi
                    Text { id: lbl; anchors.centerIn: parent; text: modelData.t; font.pixelSize: px(13); font.bold: true
                           font.family: fb.kit.gar; color: fb.kit.dark ? fb.kit.gilt0 : fb.cer1 }
                    HoverHandler { id: hov }
                    TapHandler { onTapped: modelData.k === "back" ? fb.goBack() : modelData.k === "home" ? fb.goHome() : fb.reload() }
                }
            }
        }
    }

    // ── first visit: the invitation card ──────────────────────────────────
    Rectangle {
        anchors.top: bar.bottom; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        visible: !store.enabled || web.status === Loader.Error
        color: fb.kit ? fb.kit.surface : "white"
        Rectangle {
            anchors.centerIn: parent
            width: Math.min(parent.width - 60, px(460)); height: card.implicitHeight + px(56)
            radius: 16; border.color: fb.kit.gilt2; border.width: 2
            gradient: Gradient { orientation: Gradient.Vertical
                GradientStop { position: 0; color: fb.kit.surface2 } GradientStop { position: 1; color: fb.kit.panelBg } }
            ColumnLayout {
                id: card
                anchors.left: parent.left; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: px(28); anchors.rightMargin: px(28); spacing: px(14)
                MessengerMark { Layout.alignment: Qt.AlignHCenter; Layout.preferredWidth: px(56); Layout.preferredHeight: px(56) }
                Text { Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                       text: "Facebook Messenger on the Magpie wire"
                       font.family: fb.kit.titles; font.weight: Font.DemiBold; font.pixelSize: px(18); color: fb.titleInk }
                Text { Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                       text: web.status === Loader.Error
                             ? "Messenger needs Qt WebEngine (the qt6-webengine package), which isn't installed on this machine."
                             : "Every chat, your whole history, photos, voice and video calls — all of Messenger, dressed in Magpie. "
                             + "Sign in to Facebook once; Magpie remembers it. New messages pop up even while you're on the Magpie wire."
                       font.family: fb.kit.gar; font.pixelSize: px(15); color: fb.kit.ink; lineHeight: 1.15 }
                Rectangle {
                    visible: web.status !== Loader.Error
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: goLbl.implicitWidth + px(40); Layout.preferredHeight: goLbl.implicitHeight + px(18)
                    radius: 10; color: goHov.hovered ? fb.cer2 : fb.cer1
                    border.color: fb.kit.gilt3; border.width: 1.5
                    Text { id: goLbl; anchors.centerIn: parent; text: "Sign in to Messenger"
                           font.family: fb.kit.titles; font.bold: true; font.pixelSize: px(14); color: "#fbf3de" }
                    HoverHandler { id: goHov }
                    TapHandler { onTapped: store.enabled = true }
                }
            }
        }
    }

    // Messenger's bolt on a cerulean seal — the same seal as the sidebar row
    component MessengerMark: Rectangle {
        radius: width / 2
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: fb.cer3 } GradientStop { position: 1; color: fb.cer1 } }
        border.color: fb.kit ? fb.kit.gilt3 : "gold"; border.width: 1.5
        Text { anchors.centerIn: parent; text: "ϟ"; font.family: fb.kit.titles; font.bold: true
               font.pixelSize: Math.round(parent.height * 0.55); color: "#fbf3de" }
    }
}
