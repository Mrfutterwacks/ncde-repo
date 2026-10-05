// StorageTab.qml — removable drives: mount, unmount, eject (safe to remove), unlock encrypted sticks,
// and the auto-mount toggle.
// Backend — Lelan owns storage (lelan.md §4 UDisks2: "removableVolumes = the StorageTab model"); this tab
// read widget_data, a pass-through (rewired 2026-09-30):
//   lelan.removableVolumes (list {path, device, label, drive, size (bytes), fsType, mounted, mountPoint,
//     canUnmount, canEject, locked, encrypted}), lelan.mountVolume(path) / unmountVolume(path),
//   lelan.ejectVolume(path) (unmounts + locks everything on that stick, then powers it off),
//   lelan.unlockVolume(path, passphrase) (then mounts it), lelan.volumeFailed(path, reason),
//   lelan.volumeEjected(label) = safe to remove.
//   settings.autoMountUsb (bool), settings.loadStorage() / saveStorage(); Lelan does the mounting.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: st; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    readonly property var volumes: gv(lelan, "removableVolumes", [])

    // one action at a time per volume: "Working…" until UDisks answers
    property string busyPath: ""
    property string failPath: ""
    property string failReason: ""
    property string ejectedLabel: ""        // "safe to remove" note after an eject
    property string unlockPath: ""          // the locked volume whose passphrase field is open

    function save() { if (typeof settings.saveStorage === "function") settings.saveStorage() }
    Component.onCompleted: { if (typeof settings.loadStorage === "function") settings.loadStorage() }

    function act(path) { st.failPath = ""; st.failReason = ""; st.ejectedLabel = ""; st.busyPath = path; busyGuard.restart() }
    Connections {
        target: (typeof lelan !== "undefined") ? lelan : null
        ignoreUnknownSignals: true
        function onStorageChanged() { st.busyPath = "" }
        function onVolumeFailed(path, reason) { st.busyPath = ""; st.failPath = path; st.failReason = reason }
        function onVolumeEjected(label) { st.busyPath = ""; st.failPath = ""; st.failReason = ""; st.ejectedLabel = label || "The drive" }
    }
    // an action that changes nothing and fails nowhere (e.g. already mounted) must not stay "Working…";
    // Lelan gives UDisks 120 s
    Timer { id: busyGuard; interval: 120000; onTriggered: st.busyPath = "" }

    // bytes -> "31.0 GB" (decimal units, as the drive's box says)
    function humanSize(b) {
        b = Number(b) || 0
        var u = ["bytes", "kB", "MB", "GB", "TB"], i = 0
        while (b >= 1000 && i < u.length - 1) { b /= 1000; i++ }
        return i === 0 ? b + " bytes" : (b < 10 ? b.toFixed(1) : Math.round(b)) + " " + u[i]
    }
    function details(v) {
        var parts = []
        if (v.device) parts.push(v.device.replace("/dev/", ""))
        if (v.locked) parts.push("encrypted")
        else if (v.fsType) parts.push(v.fsType + (v.encrypted ? " (encrypted)" : ""))
        if (v.size) parts.push(st.humanSize(v.size))
        return parts.join(" · ")
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

    // one volume: name / details / state on the left, buttons on the right (the text is elided to the
    // space the buttons leave — no overlap); passphrase field and failure line below the card
    component VolumeRow: Item {
        id: row
        property var vol
        property var tab
        readonly property bool busy: tab.busyPath === vol.path
        readonly property bool unlocking: tab.unlockPath === vol.path && !!vol.locked
        width: parent ? parent.width : 0
        height: card.height + (unlockBox.visible ? unlockBox.height + 8 : 0) + (failLine.visible ? failLine.height + 4 : 0)

        Rectangle {
            id: card
            width: parent.width; height: Math.max(54, info.implicitHeight + 16); radius: 8
            color: Qt.rgba(SetTheme.paper0.r, SetTheme.paper0.g, SetTheme.paper0.b, 0.22); border.color: SetTheme.gilt1; border.width: 1
            Column {
                id: info
                anchors.left: parent.left; anchors.leftMargin: 12; anchors.right: buttons.left; anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter; spacing: 2
                Text { width: parent.width; elide: Text.ElideRight
                       text: row.vol.label || row.vol.drive || row.vol.device
                       color: SetTheme.ink; font.family: SetTheme.titles; font.pixelSize: SetTheme.md; font.bold: true }
                Text { width: parent.width; elide: Text.ElideRight
                       text: row.tab.details(row.vol)
                       color: SetTheme.inkSoft; font.family: SetTheme.fell; font.pixelSize: SetTheme.sm }
                Text { width: parent.width; elide: Text.ElideMiddle
                       text: row.busy ? "Working…"
                           : row.vol.locked ? "Locked"
                           : row.vol.mounted ? "Mounted at " + row.vol.mountPoint : "Not mounted"
                       color: row.vol.mounted && !row.busy ? SetTheme.verd : SetTheme.inkSoft
                       font.family: SetTheme.fell; font.italic: true; font.pixelSize: SetTheme.sm }
            }
            Row {
                id: buttons
                anchors.right: parent.right; anchors.rightMargin: 12; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                PillButton {
                    visible: !!row.vol.locked
                    label: "Unlock"
                    enabledState: !row.busy
                    onClicked: { row.tab.failPath = ""; row.tab.unlockPath = row.unlocking ? "" : row.vol.path }
                }
                PillButton {
                    visible: !row.vol.locked && (!row.vol.mounted || !!row.vol.canUnmount)
                    label: row.vol.mounted ? "Unmount" : "Mount"
                    enabledState: !row.busy
                    onClicked: { row.tab.act(row.vol.path); row.vol.mounted ? lelan.unmountVolume(row.vol.path) : lelan.mountVolume(row.vol.path) }
                }
                PillButton {
                    visible: !!row.vol.canEject
                    label: "Eject"
                    enabledState: !row.busy
                    onClicked: { row.tab.unlockPath = ""; row.tab.act(row.vol.path); lelan.ejectVolume(row.vol.path) }
                }
            }
        }

        // passphrase for a locked (LUKS) stick; the text is cleared as soon as it is sent
        Row {
            id: unlockBox
            anchors.top: card.bottom; anchors.topMargin: 8; x: 12; spacing: 10
            visible: row.unlocking
            onVisibleChanged: if (visible) passInput.forceActiveFocus()
            Rectangle {
                width: 220; height: 30; radius: 4; color: SetTheme.paper0; border.color: SetTheme.gilt1; border.width: 1.5
                TextInput {
                    id: passInput
                    anchors.fill: parent; anchors.margins: 8; verticalAlignment: TextInput.AlignVCenter; clip: true
                    echoMode: TextInput.Password; passwordCharacter: "•"
                    color: SetTheme.ink; font.family: SetTheme.mono; font.pixelSize: SetTheme.md
                    onAccepted: unlockBtn.clicked()
                    Text { anchors.verticalCenter: parent.verticalCenter; visible: !passInput.text
                           text: "Passphrase"; color: SetTheme.inkSoft; font.family: SetTheme.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                }
            }
            PillButton {
                id: unlockBtn
                label: "Unlock"
                enabledState: passInput.text.length > 0 && !row.busy
                onClicked: {
                    if (!enabledState) return
                    row.tab.act(row.vol.path)
                    lelan.unlockVolume(row.vol.path, passInput.text)
                    passInput.text = ""
                }
            }
        }

        Text {
            id: failLine
            anchors.top: unlockBox.visible ? unlockBox.bottom : card.bottom; anchors.topMargin: 4
            x: 12; width: parent.width - 24; wrapMode: Text.WordWrap
            visible: row.tab.failReason !== "" && row.tab.failPath === row.vol.path
            text: row.tab.failReason
            color: SetTheme.wine2; font.family: SetTheme.fell; font.italic: true; font.pixelSize: SetTheme.sm
        }
    }

    Flickable {
        anchors.fill: parent; contentHeight: c.height; interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: c; width: parent.width; spacing: 14

            Text { text: "Storage"; color: st.k.wine2; font.family: st.k.display; font.bold: true; font.pixelSize: st.k.lg }
            Text { text: "Mount, unmount and safely remove drives."; color: st.k.inkSoft; font.family: st.k.fell; font.italic: true; font.pixelSize: st.k.md }

            // Auto-mount toggle
            Item { width: parent.width; height: 30
                Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                       text: "Auto-mount USB on insertion"; color: st.k.ink; font.family: st.k.titles; font.pixelSize: st.k.md }
                NCDEToggle {
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    checked: settings.autoMountUsb
                    onToggled: function(v) { settings.autoMountUsb = v; st.save() }
                }
            }

            Rectangle { width: parent.width; height: 1; color: st.k.gilt1; opacity: 0.4 }
            Text { text: "REMOVABLE DRIVES"; color: st.k.gilt1; font.family: st.k.display; font.bold: true; font.pixelSize: st.k.sm; font.letterSpacing: 2 }

            // "safe to remove" after an eject
            Rectangle {
                visible: st.ejectedLabel !== ""
                width: parent.width; height: ejText.implicitHeight + 20; radius: 8
                color: Qt.rgba(st.k.verd.r, st.k.verd.g, st.k.verd.b, 0.14); border.color: st.k.verd; border.width: 1
                Text {
                    id: ejText
                    anchors.left: parent.left; anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter; anchors.margins: 12
                    wrapMode: Text.WordWrap
                    text: st.ejectedLabel + " can be removed safely."
                    color: st.k.ink; font.family: st.k.titles; font.pixelSize: st.k.md
                }
            }

            Repeater {
                model: st.volumes
                VolumeRow { vol: modelData; tab: st }
            }

            // Empty state
            Text {
                visible: st.volumes.length === 0
                text: "No removable drives detected."
                color: st.k.inkSoft; font.family: st.k.fell; font.italic: true; font.pixelSize: st.k.md
            }

            Item { width: 1; height: 8 }
        }
    }
}
