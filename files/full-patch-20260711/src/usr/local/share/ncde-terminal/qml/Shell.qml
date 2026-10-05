// Shell.qml — root of the terminal's QML scene (hosted in a QQuickWidget).
//
// wallpaper Image (full-screen, offset by -window position) → sampled and
// blurred by NCDEGlassSurface to form the terminal face → ChromeBar on top.
// The QTermWidget(s) are native children placed over the glass body by C++.
//
// Context properties (set from C++): config, ncde, bridge.

import QtQuick
import QtQuick.Window

Item {
    id: shell

    // ── wallpaper — full screen, offset so the visible slice is the region
    //    of the desktop wallpaper behind this window. Live via bridge.winX/Y.
    Image {
        id: wallpaperImg
        source: (config.wallpaperPath && config.wallpaperPath !== "")
                ? ("file://" + config.wallpaperPath) : ""
        // bridge is injected by the terminal after the first binding pass —
        // guard the startup frame (same idiom as the animPolicy guards here).
        x: bridge ? -bridge.winX : 0
        y: bridge ? -bridge.winY : 0
        width:  Screen.width
        height: Screen.height
        fillMode: config.wallpaperFitMode === "fit"    ? Image.PreserveAspectFit
                : config.wallpaperFitMode === "center" ? Image.Pad
                : config.wallpaperFitMode === "tile"   ? Image.Tile
                :                                        Image.PreserveAspectCrop
        smooth: true
        asynchronous: true
        cache: true
        visible: false
        layer.enabled: true
    }

    // ── glass body — the terminal face ──
    NCDEGlassSurface {
        id: glass
        x: 0
        y: chrome.height
        width:  shell.width
        height: shell.height - chrome.height
        backgroundSource: wallpaperImg
        cornerRadius: 9
        baseDarkness: 0.0
        blurPx: 28
    }

    // ── chrome bar — painted on top of the glass ──
    ChromeBar {
        id: chrome
        width: shell.width
        height: 58
    }

    // ── cols × rows resize badge ─────────────────────────────────────────────
    Item {
        id: sizeBadge
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 30
        width:  badgeLbl.implicitWidth + 32
        height: 30
        opacity: (bridge && bridge.showSizeBadge) ? 1.0 : 0.0
        visible: opacity > 0.01
        Behavior on opacity { NumberAnimation { duration: 220; easing.type: Easing.OutCubic } }

        Rectangle {
            anchors.fill: parent
            radius: 6
            color: Qt.rgba(0xc8/255, 0x80/255, 0x1e/255, 0.88)
            border.color: Qt.rgba(0xf4/255, 0xd9/255, 0xa4/255, 0.55)
            border.width: 1
        }
        Text {
            id: badgeLbl
            anchors.centerIn: parent
            text: bridge ? (bridge.termCols + " × " + bridge.termRows) : ""
            color: "#f4d9a4"
            font.family: "monospace"
            font.pixelSize: 13
            font.weight: Font.Medium
        }
    }
}
