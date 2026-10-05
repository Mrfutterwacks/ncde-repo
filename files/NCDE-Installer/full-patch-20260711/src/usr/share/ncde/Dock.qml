// Dock.qml — NCDE HUD (Left Dock) · Tiffany stained-glass animation set
// Spec: Launchers ONLY — never shows running windows (Hard Rule)
// Auto-hide with 5px hover-trigger zone · OutExpo hydraulic reveal
//
// Animation language (to match the leaded-glass / Tiffany icon theme):
//   • Cursor-driven NEIGHBOUR MAGNIFICATION with a soft SpringAnimation —
//     icons swell and slide apart like glass beads strung on a wire, the
//     effect tapering across `dockZoomRange` neighbours.
//   • LAMP-GLOW KINDLE — a warm radial halo behind the hovered medallion
//     that fades up as the icon grows, like a Tiffany shade lit from behind.
//   • GLASS SHIMMER on launch — a diagonal light-sweep across the medallion
//     plus the existing bounce.
// All magnification is interruptible: sweeping across the dock never leaves a
// half-finished step because every scale is a continuous spring, not a chain.

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Effects

Item {
    id: dock

    readonly property int dockWidth:  64
    readonly property int glowWidth:  16

    property int   iconSize:     settings.dockIconSize
    property int   dockSpacing:  settings.dockSpacing
    property real  zoomPercent:  settings.dockZoomPercent
    property real  zoomRangeVal: settings.dockZoomRange
    property int   animSpeedVal: settings.dockAnimSpeed

    property Item wallpaperSource: null

    // ── Magnification state ────────────────────────────────────────────────
    // hoverIndex: -1 none, 0 = BFB, 1..N = pinned app slots.
    property int  hoverIndex: -1
    // neighbour spread (how many icons each side react), from zoomRangeVal.
    // dockZoomRange is a PIXEL influence radius (DockPrefs slider 48..200,
    // labelled Tight/Medium/Wide) — convert it to a neighbour COUNT using the
    // per-icon pitch (iconSize + spacing). The old code fed the raw pixel value
    // straight into Math.round(), so magSpread was 48..200 "neighbours": every
    // icon magnified at once and the whole dock ballooned. Divide by the pitch.
    property int  magSpread: Math.max(1, Math.round(zoomRangeVal / Math.max(1, (iconSize + dockSpacing + 8))))
    readonly property bool motionEnabled: dock.visible && animPolicy.decorative && !animPolicy.screenIdle
    readonly property real motionDurationScale: animPolicy.thermalPressure || animPolicy.lowPower ? 2.0 : 1.0

    // Whimsy knobs — driven by settings so FiligreeTab sliders adjust them live.
    property real magSpring:  settings.dockMagSpring
    property real magDamping: settings.dockMagDamping
    property real magMass:    settings.dockMagMass

    property var _surfaceGlass: null
    Component.onCompleted: {
        _surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("dock") : null
        reloadApps()
    }
    Connections {
        target: ncde
        function onThemeChanged() {
            dock._surfaceGlass = typeof ncde.surfaceGlass === "function" ? ncde.surfaceGlass("dock") : null
        }
    }

    // Falloff: hovered icon → zoomPercent, neighbours taper with a smooth
    // quadratic so the row reads as one flexing strand of glass beads.
    function magFor(idx) {
        if (hoverIndex < 0) return 1.0
        var d = Math.abs(idx - hoverIndex)
        if (d === 0) return zoomPercent
        if (d > magSpread) return 1.0
        var t = 1.0 - d / (magSpread + 1)
        return 1.0 + (zoomPercent - 1.0) * t * t
    }
    // 0..1 "lit" amount used to drive the lamp-glow halo opacity.
    function litFor(idx) {
        if (zoomPercent <= 1.0) return 0.0
        return Math.max(0, Math.min(1, (magFor(idx) - 1.0) / (zoomPercent - 1.0)))
    }

    // Nothing may intersect (operator, 2026-09-29): the framed dock lives in
    // the clear zone between the top panel's "this" band (30px bar + 36px band
    // at -2 overlap; its art ends at y 62) and the bottom panel's band (art
    // starts 1024px on a 1080 screen = 56px up), with a 4px gap each side.
    // Centred in that zone; if dock + frame crowns won't fit, the whole dock
    // scales down (about its left edge) instead of touching a band.
    readonly property int zoneTop: 66
    readonly property int zoneBottom: parent.height - 60
    readonly property int frameTall: height + 41 + 42      // dockFrame topOut + bottomOut
    readonly property real fitScale: Math.min(1.0, (zoneBottom - zoneTop) / frameTall)
    x: 0
    y: Math.round((zoneTop + zoneBottom) / 2 - height / 2 + (41 - 42) / 2)
    width:  dockWidth
    height: dockCol.implicitHeight + 64
    scale: fitScale
    transformOrigin: Item.Left
    z: 600

    // revealed at 27 (was 8) so the frame's left carving (23px) stays on
    // screen; hidden far enough that the frame's right carving clears too
    property real targetX: intellihide.dockRevealed ? 27 : -(dockWidth + 70)
    Behavior on targetX {
        NumberAnimation { duration: animSpeedVal * 3; easing.type: Easing.OutExpo }
    }
    transform: Translate { x: dock.targetX }

    opacity: intellihide.dockRevealed ? 1.0 : 0.0
    Behavior on opacity {
        NumberAnimation { duration: animSpeedVal * 2; easing.type: Easing.OutExpo }
    }

    // 5px hover-trigger zone — always at x:0 even when dock hidden
    Item {
        id: hoverTrigger
        width: 5; height: parent.height
        parent: dock.parent
        x: 0; y: dock.y
        z: dock.z + 1
        HoverHandler {
            onHoveredChanged: {
                intellihide.dockHovered = hovered
                if (hovered) intellihide.revealAll()
                else intellihide.scheduleHide()
            }
        }
    }

    HoverHandler {
        id: dockHover
        onHoveredChanged: {
            intellihide.dockHovered = hovered
            if (hovered) {
                intellihide.revealAll()
            } else {
                dock.hoverIndex = -1          // relax all magnification
                intellihide.scheduleHide()
            }
        }
    }

    // ── Aero glass pill — via shared NCDEGlassSurface ───────────────────────
    NCDEGlassSurface {
        x: 0; y: 0
        width: dockWidth; height: parent.height
        backgroundSource: dock.wallpaperSource
        cornerRadius: dockWidth / 2
        specularInset: 0.08
        glowBlurred: true
        jewelGlow: true
        glintVertical: true
        revealPulse: intellihide.dockRevealed
        glintPulse: intellihide.glintPulse
        // Iris Chroma baseline + Filigree override — resolved inside NCDEGlassSurface.
        surfaceKey: "dock"
        glass: dock._surfaceGlass
    }

    // ── Carved bronze frame hugging the pill (2026-09-29, operator art
    // ~/Downloads/dock-right-Photoroom.png; source kept in my-project/files).
    // dock-frame.png = the art's bbox (67,62)-(445,1476) scaled by 64/221 so
    // the opening between its straight rails (src x 146..366 = 221px) is
    // exactly dockWidth: the rails sit on the glass edges. The inner arch
    // apexes (src y 205 / 1330) land on the pill's top/bottom, so the shell
    // crowns cap its rounded ends. 9-slice: the carved ends (121 / 126 px)
    // never stretch, only the straight rails do, so it hugs at any icon
    // count. Child of dock: intellihide hides it with the dock.
    BorderImage {
        id: dockFrame
        readonly property int sideOut: 23      // frame art left of the pill
        readonly property int topOut: 41       // crown above the pill
        readonly property int bottomOut: 42    // crown below the pill
        x: -sideOut
        y: -topOut
        width: 109
        height: dock.height + topOut + bottomOut
        source: "dock-frame.png"
        border { left: 0; right: 0; top: 121; bottom: 126 }
        horizontalTileMode: BorderImage.Stretch
        verticalTileMode: BorderImage.Stretch
        smooth: true
        z: 1
    }

    ListModel { id: dockAppsModel }

    function reloadApps() {
        dockAppsModel.clear()
        var apps = settings.dockApps
        for (var i = 0; i < apps.length; i++)
            dockAppsModel.append(apps[i])
    }
    Connections {
        target: settings
        function onDockPrefsChanged() { dock.reloadApps() }
    }

    Column {
        id: dockCol
        x: 0; y: 32
        width: dockWidth
        spacing: dockSpacing
        clip: false
        z: 2

        // ─── BFB — ncde logo button ────────────────────────────────────────
        Item {
            id: bfbSlot
            width: dockWidth
            height: ((dock.iconSize + 6) * bfbImg.kindle)      // slot grows so neighbours slide apart; scales with iconSize
            Behavior on height { SpringAnimation { spring: dock.magSpring; damping: dock.magDamping; mass: dock.magMass; epsilon: 0.005 } }

            Item {
                id: bfbImg
                anchors.centerIn: parent
                width: dock.iconSize; height: dock.iconSize   // BFB now tracks iconSize (was fixed 54)

                // continuous spring magnification (index 0)
                property real kindle: 1.0
                property real targetMag: dock.magFor(0)
                scale: kindle
                Behavior on kindle { SpringAnimation { spring: dock.magSpring; damping: dock.magDamping; mass: dock.magMass; epsilon: 0.005 } }
                onTargetMagChanged: kindle = targetMag

                // lamp-glow halo (kindles behind the medallion)
                Rectangle {
                    id: bfbLampGlow
                    anchors.centerIn: parent
                    width: parent.width * 1.7; height: parent.height * 1.7
                    radius: width / 2
                    z: -1
                    property real flick: 1.0
                    opacity: dock.litFor(0) * 0.9 * flick
                    SequentialAnimation on flick {
                        running: dock.litFor(0) > 0.05 && dock.motionEnabled
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.82; duration: 140 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0;  duration: 90 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 0.9;  duration: 170 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0;  duration: 110 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        onStopped: bfbLampGlow.flick = 1.0
                    }
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.55) }
                        GradientStop { position: 0.55; color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18) }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                    layer.enabled: true
                    layer.effect: MultiEffect { blurEnabled: true; blur: 0.6; blurMax: 24 }
                }

                // Weight & touch (2026-09-24): held down, the medallion + dome sink
                // 1px into the bezel socket — instant, no new animation.
                NCDEIconBezel {
                    anchors.centerIn: parent
                    bezelSize: dock.iconSize
                    hovered: dock.hoverIndex === 0
                    pressed: bfbTap.pressed
                }

                MuchaIcon {
                    anchors.fill: parent
                    transform: Translate { y: bfbTap.pressed ? 1 : 0 }
                    size: dock.iconSize
                    renderScale: dock.zoomPercent
                    appName: "bfb"
                    accentColor: ncde.accent
                    glowColor:   ncde.glow
                }

                // Glass dome over the medallion — reads as a glass button in its bezel.
                NCDEGlassCap {
                    anchors.centerIn: parent
                    capSize: dock.iconSize
                    hovered: dock.hoverIndex === 0
                    pressed: bfbTap.pressed
                    transform: Translate { y: bfbTap.pressed ? 1 : 0 }
                }

                // VFD pulse when HUD active
                Rectangle {
                    anchors.fill: parent; radius: 6
                    color: "transparent"
                    border.color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, bfbPulse.val)
                    border.width: 2
                    visible: exposeOverlay.visible
                }
                Item {
                    id: bfbPulse; property real val: 0
                    SequentialAnimation on val {
                        running: exposeOverlay.visible && dock.motionEnabled && animPolicy.idleLoops; loops: Animation.Infinite
                        NumberAnimation { to: 0.8; duration: 500 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 0.2; duration: 500 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        onStopped: bfbPulse.val = 0.8
                    }
                }

                HoverHandler {
                    onHoveredChanged: dock.hoverIndex = hovered ? 0 : (dock.hoverIndex === 0 ? -1 : dock.hoverIndex)
                }
                TapHandler { id: bfbTap; onTapped: exposeOverlay.visible = !exposeOverlay.visible }
            }

            DockTooltip { visible: bfbTip.hovered; label: "NCDExpose" }
            HoverHandler { id: bfbTip }
        }

        // Divider
        Item {
            width: dockWidth; height: 8
            Rectangle {
                anchors.centerIn: parent
                width: dockWidth - 16; height: 1
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 0.5; color: Qt.rgba(ncde.glow.r,ncde.glow.g,ncde.glow.b,0.40) }
                    GradientStop { position: 1.0; color: "transparent" }
                }
            }
        }

        // ─── Pinned app launchers ───────────────────────────────────────────
        Repeater {
            id: pinnedRepeater
            model: dockAppsModel

            Item {
                id: pinnedSlot
                width: dockWidth
                // 1-based index so BFB can own index 0 in the falloff
                property int slotIndex: index + 1

                // continuous spring magnification driven by cursor falloff
                property real targetMag: dock.magFor(slotIndex)
                property real magScale: 1.0
                Behavior on magScale { SpringAnimation { spring: dock.magSpring; damping: dock.magDamping; mass: dock.magMass; epsilon: 0.005 } }
                onTargetMagChanged: magScale = targetMag

                // slot height tracks the spring so neighbours physically slide apart
                height: (dock.iconSize * magScale) + 8 + dock.dockSpacing

                property int stateVersion: 0
                Connections {
                    target: windowMgr
                    function onWindowStateChanged() { pinnedSlot.stateVersion++ }
                    function onCountChanged()        { pinnedSlot.stateVersion++ }
                }
                property bool hasWindow:   { var _v = stateVersion; return windowMgr.hasWindowForName(model.name) }
                property bool isMinimized: { var _v = stateVersion; return windowMgr.isMinimizedForName(model.name) }
                property bool isActive:    { var _v = stateVersion; return windowMgr.isActiveForName(model.name) }

                // lamp-glow halo — kindles behind the medallion as it grows
                Rectangle {
                    id: appLampGlow
                    anchors.centerIn: appIco
                    width: dock.iconSize * 1.8 * pinnedSlot.magScale
                    height: width
                    radius: width / 2
                    z: -1
                    property real flick: 1.0
                    opacity: dock.litFor(pinnedSlot.slotIndex) * 0.9 * flick
                    SequentialAnimation on flick {
                        running: dock.litFor(pinnedSlot.slotIndex) > 0.05 && dock.motionEnabled
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.82; duration: 140 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0;  duration: 90 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 0.9;  duration: 170 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0;  duration: 110 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        onStopped: appLampGlow.flick = 1.0
                    }
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.55) }
                        GradientStop { position: 0.55; color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18) }
                        GradientStop { position: 1.0; color: "transparent" }
                    }
                    layer.enabled: true
                    layer.effect: MultiEffect { blurEnabled: true; blur: 0.6; blurMax: 22 }
                }

                NCDEIconBezel {
                    anchors.centerIn: parent
                    bezelSize: dock.iconSize
                    hovered: dock.hoverIndex === pinnedSlot.slotIndex
                    pressed: appTap.pressed
                    scale: pinnedSlot.magScale
                }

                // Weight & touch (2026-09-24): held down, the medallion + dome sink
                // 1px into the socket. A Translate, not `y` — `y` belongs to the
                // launch-hop animation, which is left exactly as it was.
                MuchaIcon {
                    id: appIco
                    transform: Translate { y: appTap.pressed ? 1 : 0 }
                    anchors.centerIn: parent
                    size: dock.iconSize
                    renderScale: dock.zoomPercent
                    appName: model.name
                    appIcon: model.icon !== undefined ? model.icon : ""
                    kithEmblem: true
                    accentColor: ncde.accent
                    glowColor:   ncde.glow
                    scale: pinnedSlot.magScale

                    // whimsical wobble-tilt — a quick cheeky jiggle on hover/launch
                    property real wobble: 0
                    rotation: wobble
                    SequentialAnimation {
                        id: wobbleAnim
                        NumberAnimation { target: appIco; property: "wobble"; to:  7; duration: 90;  easing.type: Easing.OutQuad }
                        NumberAnimation { target: appIco; property: "wobble"; to: -5; duration: 110; easing.type: Easing.InOutSine }
                        NumberAnimation { target: appIco; property: "wobble"; to:  3; duration: 90;  easing.type: Easing.InOutSine }
                        NumberAnimation { target: appIco; property: "wobble"; to:  0; duration: 160; easing.type: Easing.OutBack }
                    }

                    HoverHandler {
                        onHoveredChanged: {
                            if (hovered) { dock.hoverIndex = pinnedSlot.slotIndex; wobbleAnim.restart() }
                            else if (dock.hoverIndex === pinnedSlot.slotIndex) dock.hoverIndex = -1
                        }
                    }

                    // ── GLASS SHIMMER sweep (plays on launch) ───────────────
                    Item {
                        id: shimmer
                        anchors.fill: parent
                        clip: true
                        visible: shimmerAnim.running
                        Rectangle {
                            id: shimmerBar
                            width: parent.width * 0.5
                            height: parent.height * 2
                            y: -parent.height * 0.5
                            x: -parent.width
                            rotation: 22
                            gradient: Gradient {
                                orientation: Gradient.Horizontal
                                GradientStop { position: 0.0; color: "transparent" }
                                GradientStop { position: 0.5; color: ShellLight.lt(0.55) }
                                GradientStop { position: 1.0; color: "transparent" }
                            }
                        }
                    }
                    NumberAnimation {
                        id: shimmerAnim
                        target: shimmerBar; property: "x"
                        from: -appIco.width; to: appIco.width
                        duration: 480; easing.type: Easing.OutCubic
                    }

                    // exuberant launch hop + a happy wobble + glass shimmer
                    SequentialAnimation on y {
                        id: appBounce; running: false
                        NumberAnimation { to: -22; duration: 120; easing.type: Easing.OutExpo }
                        NumberAnimation { to: 0;   duration: 240; easing.type: Easing.OutBounce }
                        NumberAnimation { to: -8;  duration: 90;  easing.type: Easing.OutExpo }
                        NumberAnimation { to: 0;   duration: 200; easing.type: Easing.OutBounce }
                    }

                    function fireLaunchFx() { appBounce.restart(); shimmerAnim.restart(); wobbleAnim.restart() }

                    TapHandler {
                        id: appTap
                        onTapped: {
                            var wid = windowMgr.winIdForName(model.name)
                            if (wid > 0) {
                                windowMgr.unminimizeWindow(wid)
                                windowMgr.activateWindow(wid)
                            } else {
                                appIco.fireLaunchFx()
                                launcher.launchExec(model.exec)
                            }
                        }
                    }

                    NCDEDropZone {
                        anchors.fill: parent
                        exec:         model.exec
                        iconTarget:   appIco
                        onFileDropped: (paths) => appIco.fireLaunchFx()
                    }
                }

                // Glass dome over the medallion — reads as a glass button in its bezel.
                NCDEGlassCap {
                    anchors.centerIn: parent
                    capSize: dock.iconSize
                    hovered: dock.hoverIndex === pinnedSlot.slotIndex
                    pressed: appTap.pressed
                    transform: Translate { y: appTap.pressed ? 1 : 0 }
                    scale: pinnedSlot.magScale
                }

                // Active/running indicator — leaded glass bead
                Canvas {
                    id: indicatorDot
                    width: 6; height: 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 1
                    enabled: false
                    property real pulse: 1.0
                    property bool dotHasWindow: pinnedSlot.hasWindow
                    property bool dotMinimized: pinnedSlot.isMinimized

                    SequentialAnimation on pulse {
                        running: indicatorDot.dotHasWindow && indicatorDot.dotMinimized
                                 && dock.motionEnabled && animPolicy.idleLoops
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.4; duration: 750 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0; duration: 750 * dock.motionDurationScale; easing.type: Easing.InOutSine }
                        onStopped: { indicatorDot.pulse = 1.0; indicatorDot.requestPaint() }
                    }

                    onPulseChanged: requestPaint()
                    onDotHasWindowChanged: requestPaint()

                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        if (!dotHasWindow) return
                        ctx.beginPath()
                        ctx.arc(width/2, height/2, width/2, 0, Math.PI*2)
                        var g = ncde.glow
                        ctx.fillStyle = Qt.rgba(g.r, g.g, g.b, pulse)
                        ctx.fill()
                    }
                }
                DockTooltip { visible: appTip.hovered; label: model.name }
                HoverHandler { id: appTip }
            }
        }
    }

    // IconBezel extracted 2026-09-23 to the shared NCDEIconBezel.qml component
    // (same directory, auto-imported by filename) so BottomPanel's workspace
    // switcher can reuse the exact same brass-bezel treatment. Both call sites
    // below now reference NCDEIconBezel instead of this former inline type.

    component DockTooltip: Rectangle {
        property string label: ""
        anchors.left:           parent ? parent.right : undefined
        anchors.leftMargin:     8
        anchors.verticalCenter: parent ? parent.verticalCenter : undefined
        width: tipTxt.width + 14; height: 26; radius: 4
        color: ncde.popupBg
        border.color: ncde.border; border.width: 1
        z: 900
        property bool shown: false
        opacity: shown ? 1.0 : 0.0
        visible: opacity > 0
        Behavior on opacity { NumberAnimation { duration: 120; easing.type: Easing.OutExpo } }
        onVisibleChanged: shown = visible

        Rectangle {
            anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom
            width: 2; color: ncde.glow
        }
        Text {
            id: tipTxt
            anchors.centerIn: parent; anchors.leftMargin: 6
            text: parent.label
            color: WallInk.inked(settings.dockHoverTextColor !== "" ? settings.dockHoverTextColor : ncde.gilt4)
            font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
        }
    }
}
