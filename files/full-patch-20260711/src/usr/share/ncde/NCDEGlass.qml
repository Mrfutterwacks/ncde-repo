// NCDEGlass.qml — NCDE Tenebrate frosted glass engine
// Samples the wallpaper region behind this window and blurs it.
// Replaces Picom dual_kawase for all panel/frame glass effects.
// Use as first child inside any transparent Window.

import QtQuick
import QtQuick.Effects

Item {
    id: glass

    // Set these from the parent Window's screen position
    property string wallpaperPath: ""
    property real   screenX:       0
    property real   screenY:       0
    property real   wallpaperW:    windowMgr.screenWidth
    property real   wallpaperH:    windowMgr.screenHeight

    // Tuning
    property real blurStrength: 0.8
    property real baseOpacity:  0.50
    property real tintOpacity:  0.15

    // Hidden wallpaper — offset so the visible area matches screen position
    Image {
        id: glassWp
        width:  glass.wallpaperW
        height: glass.wallpaperH
        x: -glass.screenX
        y: -glass.screenY
        source: glass.wallpaperPath !== "" ? "file://" + glass.wallpaperPath : ""
        fillMode: Image.PreserveAspectCrop
        visible: false
        smooth: true
        asynchronous: true
    }

    // Capture the region behind this window
    ShaderEffectSource {
        id: glassSrc
        anchors.fill: parent
        sourceItem: glassWp
        sourceRect: Qt.rect(0, 0, glass.width, glass.height)
        visible: false
        // Moksha redraw-on-change: the wallpaper Image is static — sample it ONCE and cache,
        // instead of re-sampling + re-blurring an unchanging image every frame. Pixel-identical:
        // re-sample only when the sampled pixels can actually change (geometry/position, wallpaper
        // path swap, or the wallpaper finishing a (re)load). [efficiency fix — matches NCDEGlassSurface]
        live: false
        recursive: false      // never sample our own output
        Component.onCompleted: scheduleUpdate()
        Connections {
            target: glass
            function onWidthChanged()        { glassSrc.scheduleUpdate() }
            function onHeightChanged()       { glassSrc.scheduleUpdate() }
            function onScreenXChanged()      { glassSrc.scheduleUpdate() }
            function onScreenYChanged()      { glassSrc.scheduleUpdate() }
            function onWallpaperWChanged()   { glassSrc.scheduleUpdate() }
            function onWallpaperHChanged()   { glassSrc.scheduleUpdate() }
            function onWallpaperPathChanged(){ glassSrc.scheduleUpdate() }
        }
        Connections {
            target: glassWp
            ignoreUnknownSignals: true
            function onStatusChanged() { Qt.callLater(glassSrc.scheduleUpdate) }   // wallpaper finished (re)loading
        }
    }

    // Blur it
    MultiEffect {
        source: glassSrc
        anchors.fill: parent
        blurEnabled: true
        blur: glass.blurStrength
        blurMax: 32
        blurMultiplier: 2.0
        autoPaddingEnabled: false
        opacity: glassWp.status === Image.Ready ? 1.0 : 0.0
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }

    // Frosted base tint
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(ncde.panelBg.r, ncde.panelBg.g, ncde.panelBg.b, glass.baseOpacity)
        Behavior on color { ColorAnimation { duration: 300 } }
    }

    // Accent tint
    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, glass.tintOpacity)
        Behavior on color { ColorAnimation { duration: 300 } }
    }
}
