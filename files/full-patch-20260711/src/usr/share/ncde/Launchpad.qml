// Launchpad.qml — NCDE Full-Screen App Grid
// Trigger: F1 key or desktop right-click → Launchpad
import QtQuick
import QtQuick.Controls

Item {
    id: launchpad
    visible: false
    anchors.fill: parent
    z: 2000
    readonly property real motionDurationScale: animPolicy.thermalPressure || animPolicy.lowPower ? 2.0 : 1.0

    function show() {
        lpSearch.text = ""
        loadApps("")
        visible = true
        lpSearch.forceActiveFocus()
    }
    function hide() { visible = false }
    function loadApps(query) {
        lpModel.clear()
        var apps = appMenuModel.getApps("All", query)
        for (var i = 0; i < apps.length; i++) lpModel.append(apps[i])
    }

    ListModel { id: lpModel }

    opacity: visible ? 1.0 : 0.0
    scale:   visible ? 1.0 : 0.97
    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }
    Behavior on scale   { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }

    // Backdrop
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, 0.93)
    }
    TapHandler { onTapped: launchpad.hide() }

    // VFD lines
    Rectangle {
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        height: 2; color: ncde.glow; z: 10
    }
    Rectangle {
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        height: 1; color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.3); z: 10
    }

    Column {
        anchors.top: parent.top; anchors.topMargin: 52
        anchors.left: parent.left; anchors.right: parent.right
        spacing: 18

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "LAUNCHPAD"
            color: WallInk.inked(ncde.glow)
            font.pixelSize: theme.fontSmall; font.bold: true
            font.family: ncde.monoFont; font.letterSpacing: 5
        }

        // Search
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 460; height: 36; radius: 18
            color: Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.85)
            border.color: ncde.accent; border.width: 1
            Row {
                anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 16; spacing: 10
                Text { text: "🔍"; font.pixelSize: theme.fontMedium; color: WallInk.inked(ncde.accentMuted); anchors.verticalCenter: parent.verticalCenter }
                TextInput {
                    id: lpSearch
                    width: parent.width - 38
                    color: WallInk.inked(ncde.panelText); font.pixelSize: theme.fontMedium; font.family: settings.fontFamily || "Comfortaa"
                    anchors.verticalCenter: parent.verticalCenter
                    onTextChanged: launchpad.loadApps(text)
                    Keys.onEscapePressed: launchpad.hide()
                    Keys.onReturnPressed: {
                        if (lpGrid.currentIndex >= 0 && lpGrid.currentIndex < lpModel.count) {
                            var _a = lpModel.get(lpGrid.currentIndex); launcher.launchExec(_a.appId ? "gtk-launch " + _a.appId : _a.exec)
                            launchpad.hide()
                        }
                    }
                    Keys.onLeftPressed:  if (lpGrid.currentIndex > 0)               lpGrid.currentIndex--
                    Keys.onRightPressed: if (lpGrid.currentIndex < lpModel.count-1)  lpGrid.currentIndex++
                }
            }
        }

        // App grid
        GridView {
            id: lpGrid
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(launchpad.width - 80, 1080)
            height: launchpad.height - 178
            cellWidth: 128; cellHeight: 120
            clip: true; model: lpModel; currentIndex: -1

            ScrollBar.vertical: NCDEScrollBar {}

            delegate: Item {
                width: 128; height: 120
                Column {
                    anchors.centerIn: parent; spacing: 9

                    Rectangle {
                        id: iconBox
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 64; height: 64; radius: 14
                        color: ih.hovered
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.20)
                            : Qt.rgba(ncde.surface.r, ncde.surface.g, ncde.surface.b, 0.60)
                        border.color: ih.hovered
                            ? Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.60)
                            : Qt.rgba(ncde.border.r,  ncde.border.g,  ncde.border.b,  0.30)
                        border.width: 1
                        Behavior on color { ColorAnimation { duration: 90 } }

                        scale: tp.pressed ? 0.87 : (ih.hovered ? 1.08 : 1.0)
                        Behavior on scale { NumberAnimation { duration: 90; easing.type: Easing.OutExpo } }

                        Image {
                            anchors.centerIn: parent; width: 40; height: 40
                            source: model.icon !== "" ? "image://icon/" + model.icon : ""
                            fillMode: Image.PreserveAspectFit; smooth: true
                            onStatusChanged: if (status === Image.Error) source = ""
                        }

                        // Glow ring
                        Rectangle {
                            anchors.fill: parent; radius: parent.radius; color: "transparent"
                            border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, ih.hovered ? gp.v : 0)
                            border.width: 2
                        }
                        Item {
                            id: gp; property real v: 0.3
                            SequentialAnimation on v {
                                running: launchpad.visible && ih.hovered && animPolicy.decorative && !animPolicy.screenIdle
                                loops: Animation.Infinite
                                NumberAnimation { to: 0.85; duration: 550 * launchpad.motionDurationScale; easing.type: Easing.InOutSine }
                                NumberAnimation { to: 0.30; duration: 550 * launchpad.motionDurationScale; easing.type: Easing.InOutSine }
                                onStopped: gp.v = 0.3
                            }
                        }

                        HoverHandler { id: ih }
                        TapHandler {
                            id: tp
                            onTapped: { launcher.launchExec(model.appId ? "gtk-launch " + model.appId : model.exec); launchpad.hide() }
                        }
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: model.name
                        color: WallInk.inked(ih.hovered ? ncde.accent : ncde.panelText)
                        font.pixelSize: theme.fontSmall; font.family: settings.fontFamily || "Comfortaa"
                        elide: Text.ElideRight; width: 120
                        horizontalAlignment: Text.AlignHCenter
                        Behavior on color { ColorAnimation { duration: 90 } }
                    }
                }
            }
        }
    }

    Keys.onEscapePressed: hide()
}
