// MotifFrame.qml — Tiffany Studios stained-glass window frame for NCDE.
//
// Replaces the previous Aero/VFD visual treatment with an Art-Nouveau
// leaded-glass aesthetic in the spirit of Louis Comfort Tiffany:
//   • bronze patinated framework with subtle vertical gradients
//   • a stained-glass band of jewel-toned panes across the titlebar
//   • 1-pixel black lead came between every glass piece
//   • four cabochon window buttons set in brass bezels
//       sapphire = minimize, emerald = maximize, ruby = close
//   • a slow amber "lamp-glow" halo when the window is focused
//   • vertical jewel chains along the side rails
//   • a leaded mosaic band along the bottom rail
//
// External contract (unchanged from the previous MotifFrame revision):
//   property int     winId
//   property string  windowTitle
//   property int     windowX, windowY
//   property bool    isFocused
//   readonly int     titleH (32), frameLeft (12), frameRight (12), bottomH (26)
//   windowMgr.{closeWindow,minimizeWindow,moveWindow,resizeWindow,activateWindow,setTiled}
//
// All visual state is driven by QML property bindings, ColorAnimation
// Behaviors and a single SequentialAnimation pulse — no JavaScript timers,
// no Canvas paints, no per-pixel work.  Compatible with Qt 6.5+ (MultiEffect).

import QtQuick
import QtQuick.Effects

Item {
    id: frame

    // ===== EXTERNAL CONTRACT ==============================================
    property int    winId: 0
    property string windowTitle: ""
    property int    windowX: 0
    property int    windowY: 0
    property bool   isFocused: false

    // Properties assigned by main.qml — kept for binding compatibility
    property string windowAppId:  ""
    property bool   isMinimized:  false
    property bool   isTiled:      false
    property int    frameIndex:   0
    property int    windowW:      800
    property int    windowH:      560
    property Item   wallpaperRef: null
    property real   dragOffX:     0
    property real   dragOffY:     0

    // Explicit maximize state — set directly by the Green (maximize) and Amethyst (unmax)
    // buttons. NOT computed from geometry: geometry comparison flapped with X11 configure
    // sequences (the "rapid fire unmax↔max" bug — s28). The old geometry-based isMaximized
    // caused the guard to re-evaluate mid-resize and trigger the wrong button path.
    property bool maximized: true
    readonly property bool isMaximized: maximized    // backward-compat for console.log
    property int  savedX: 100
    property int  savedY: 100
    property int  savedW: 800
    property int  savedH: 560
    // Initial maximized state — set ONCE from model.maximized via main.qml
    // Component.onCompleted. NOT a binding (avoids dataChanged re-assert, s28).
    // When true: Amethyst unmax restores to savedW/savedH defaults (800×560).
    // When false: saves windowed geometry so unmax returns to original position.
    property bool initialMaximized: true
    onInitialMaximizedChanged: {
        if (windowW <= 200) return
        if (initialMaximized) {
            maximized = true
        } else {
            savedX = windowX; savedY = windowY
            savedW = windowW; savedH = windowH
        }
    }
    Component.onCompleted: {
        if (windowW > 200 && initialMaximized) maximized = true
    }

    readonly property int titleH:     32
    readonly property int frameLeft:  12
    readonly property int frameRight: 12
    readonly property int bottomH:    26
    readonly property int minW:       220
    readonly property int minH:       80

    // ── GIMP maximized-geometry snap-back (2026-07-17 live fix; reconstructed and
    // FOLDED INTO THE PATCH 2026-07-21 — the original was deployed live-only, never
    // folded, and the 2026-07-21 patch deploy overwrote it with this file's fix-less
    // copy; see docs/SESSION_HANDOFF.md 2026-07-17 entry #2 for the root-cause).
    // GIMP is the only common app that restores its own "was maximized" session
    // state at startup: it repositions its client window to (0,0) at content size,
    // pushing the titlebar into negative Y where min/max/close are unreachable.
    // Fix: when a maximized window's live geometry drifts from the enforced
    // placement, snap it straight back with the exact same math the Green maximize
    // button uses. Driven by the windowX/Y/W/H bindings — never a poll/timer — and
    // it compares against the target before acting, so it fires once per actual
    // drift: no repeated movement, no flicker (flashing is a seizure-safety hazard
    // on this system, never cosmetic).
    // Guards:
    //   !visible    — frameless game windows + Settings: this frame is inert for
    //                 them and main.qml's snapNoFrameFullscreen() owns their
    //                 geometry; snapping here too would fight it in a move loop.
    //   isTiled     — TilingManager owns tiled geometry; same fight risk.
    //   isMinimized / windowW<=200 — unmapped or placeholder geometry, same
    //                 validity guard as initialMaximized handling above.
    // DO NOT replace with _NET_FRAME_EXTENTS — live-tested 2026-07-17, it made
    // GIMP land at (-12,-32); wrong model for this WM (no real reparenting).
    function snapMaximizedGeometry() {
        if (!maximized || !visible || isTiled || isMinimized) return
        if (windowW <= 200) return
        var sw = windowMgr.screenWidth()
        var sh = windowMgr.screenHeight()
        var mw = sw - frameLeft - frameRight
        var mh = sh - titleH - bottomH
        if (windowX !== frameLeft || windowY !== titleH
                || windowW !== mw || windowH !== mh) {
            windowMgr.moveWindow(winId, frameLeft, titleH)
            windowMgr.resizeWindow(winId, mw, mh)
        }
    }
    onWindowXChanged: snapMaximizedGeometry()
    onWindowYChanged: snapMaximizedGeometry()
    onWindowWChanged: snapMaximizedGeometry()
    onWindowHChanged: snapMaximizedGeometry()

    // ===== TIFFANY PALETTE =================================================
    // Leadwork
    readonly property color tCame:        "#0a0604"
    readonly property color tCameLip:     "#1c130a"
    // Bronze (oxidised → polished)
    readonly property color tBronzeDark:  "#2a1a0a"
    readonly property color tBronze:      "#5d3a1c"
    readonly property color tBronzeMid:   "#8a5728"
    readonly property color tBronzeWarm:  "#b07840"
    readonly property color tBronzeShine: ncde.gilt4
    // Amber
    readonly property color tAmberDeep:   "#5e3308"
    readonly property color tAmber:       ncde.gilt2
    readonly property color tAmberShine:  ncde.gilt4
    // Emerald
    readonly property color tEmDeep:      "#0b3a2a"
    readonly property color tEmerald:     ncde.verd
    readonly property color tEmShine:     "#62d8a8"
    // Ruby
    readonly property color tRubyDeep:    "#3a0a14"
    readonly property color tRuby:        ncde.wine4
    readonly property color tRubyShine:   "#ee4d63"
    // Sapphire
    readonly property color tSapphDeep:   "#0e1948"
    readonly property color tSapphire:    "#2c4090"
    readonly property color tSapphShine:  "#7596ec"
    // Amethyst
    readonly property color tAmethDeep:   "#28184a"
    readonly property color tAmethyst:    "#4f3274"
    readonly property color tAmethShine:  "#9573c4"
    // Opalescent / accents
    readonly property color tHoney:       "#dba869"
    readonly property color tCream:       "#f3e6c2"
    readonly property color tInk:         "#1a0e04"

    // ===== GLOW PROPERTIES — same interface as NCDEGlassSurface ===================
    // These track ncde.* colours automatically. Filigree can override them once
    // FIL-MGL wires the frame surface key into setSurfaceGlass.
    property color glowHalo: (typeof ncde !== "undefined") ? ncde.glow
                             : Qt.rgba(0.37, 0.90, 0.82, 1.0)
    property color glowRim:  (typeof ncde !== "undefined") ? ncde.glow
                             : Qt.rgba(0.37, 0.90, 0.82, 1.0)
    property color lampCol:  (typeof ncde !== "undefined" && ncde.lamp !== undefined)
                             ? ncde.lamp : Qt.rgba(0.96, 0.74, 0.36, 1.0)
    property color edge:     (typeof ncde !== "undefined")
                             ? Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.85)
                             : Qt.rgba(0.37, 0.90, 0.82, 0.85)
    property real  glowA:        0.70
    property real  cornerRadius: 3

    // must equal C++ glowM in all six NCDEWindowManager.cpp functions
    readonly property int glowMargin: 12

    // Tiffany favrile tones — derived from ncde.*
    property color glowBase:  Qt.rgba(0.20, 0.69, 0.77, 1.0)
    property color glowGreen: Qt.rgba(0.54, 0.77, 0.43, 1.0)

    // ===== LAMP-GLOW PULSE (warm amber, like a Tiffany shade in lamplight) ======
    Item {
        id: lampPulse
        property real val: 0.30
        property bool isDragging: false

        // Candle flame period: T proportional to windowW^(-0.49), T0=990ms at 600px.
        readonly property real flickerPeriod:
            990 * Math.pow(Math.max(frame.windowW, 100) / 600.0, 0.49)

        // Normal breath — slow 4s sine when focused and not dragging.
        SequentialAnimation on val {
            running: isFocused && !animPolicy.screenIdle && !lampPulse.isDragging
            loops: Animation.Infinite
            NumberAnimation { to: 0.55; duration: 2000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.25; duration: 2000; easing.type: Easing.InOutSine }
        }

        // Candle-in-motion flicker — runs while the window is being dragged.
        SequentialAnimation on val {
            running: lampPulse.isDragging && isFocused
            loops: Animation.Infinite
            NumberAnimation { to: 0.28; duration: lampPulse.flickerPeriod * 0.182; easing.type: Easing.InSine  }
            NumberAnimation { to: 0.44; duration: lampPulse.flickerPeriod * 0.152; easing.type: Easing.OutSine }
            NumberAnimation { to: 0.22; duration: lampPulse.flickerPeriod * 0.141; easing.type: Easing.InQuad  }
            NumberAnimation { to: 0.46; duration: lampPulse.flickerPeriod * 0.131; easing.type: Easing.OutQuad }
            NumberAnimation { to: 0.35; duration: lampPulse.flickerPeriod * 0.222; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.42; duration: lampPulse.flickerPeriod * 0.172; easing.type: Easing.OutSine }
        }

        property real ember: 0.0
        SequentialAnimation on ember {
            running: !isFocused && !animPolicy.screenIdle
            loops: Animation.Infinite
            NumberAnimation { to: 1.0; duration: 4000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.0; duration: 4000; easing.type: Easing.InOutSine }
        }
    }
    readonly property real lampPulseVal: lampPulse.val

    // ===== GLOW LAYERS — anchored to decorFrame, peers of it (NOT children) =====

    // Layer A: soft peacock glow. 10px band ~9px outside the decoration edge. Pulses.
    Rectangle {
        id: outerGlow
        anchors.fill: decorFrame
        anchors.margins: -9
        radius: frame.cornerRadius + 9
        color:  "transparent"
        border.width: 10
        // border.color RGBA held constant; the lampPulse-driven part moves to `opacity` below —
        // same rendered alpha (colorAlpha * opacity == the old single alpha expression), but a
        // constant border.color means layer.enabled's cached texture doesn't need a re-blur every
        // tick, only opacity (a cheap post-render composite) changes. See ncde-efficiency.md §2c.
        border.color: Qt.rgba(frame.glowBase.r, frame.glowBase.g, frame.glowBase.b, frame.glowA * 0.42)
        opacity: isFocused ? Math.max(0.55, lampPulse.val + 0.45) : 0.08
        z: -1
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.8; blurMax: 20 }
        // filament stagger: cool peacock settles after the warm crown
        Behavior on opacity { enabled: !lampPulse.isDragging; NumberAnimation { duration: 480; easing.type: Easing.InOutCubic } }
    }

    // Layer B: amber crown. Caps the upper outer edge; overlap with A makes the colour shift.
    Rectangle {
        id: crownGlow
        anchors.top:    decorFrame.top
        anchors.left:   decorFrame.left
        anchors.right:  decorFrame.right
        anchors.topMargin:   -8
        anchors.leftMargin:  -8
        anchors.rightMargin: -8
        height: Math.min(decorFrame.height * 0.40, 80) + 8
        radius: frame.cornerRadius + 8
        color:  "transparent"
        border.width: 8
        // see outerGlow above: border.color RGBA held constant, pulse moved to `opacity`.
        border.color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, frame.glowA * 0.58)
        opacity: isFocused ? Math.max(0.50, lampPulse.val + 0.42)
                            : 0.06 + lampPulse.ember * 0.05
        z: -1
        layer.enabled: true
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.65; blurMax: 16 }
        // filament stagger: warm crown catches first
        Behavior on opacity { enabled: !lampPulse.isDragging; NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
    }

    // Layer C: crisp rim. 1.5px, no blur, hugging the outer edge.
    Rectangle {
        id: crispRim
        anchors.fill: decorFrame
        anchors.margins: -0.5
        radius: frame.cornerRadius + 0.5
        color:  "transparent"
        border.width: 1.5
        border.color: Qt.rgba(frame.glowBase.r, frame.glowBase.g, frame.glowBase.b,
                              isFocused ? 0.88 : 0.28)
        z: -1
        Behavior on border.color { ColorAnimation { duration: 360; easing.type: Easing.InOutCubic } }
    }

    // Layer S: favrile green-gold shoulders. Two short bands bridging crown to peacock sides.
    Repeater {
        model: 2
        Rectangle {
            property bool isLeft: index === 0
            anchors.top: decorFrame.top
            anchors.topMargin: decorFrame.height * 0.18
            height: Math.min(decorFrame.height * 0.30, 110)
            width: 10
            anchors.left:  isLeft ? decorFrame.left  : undefined
            anchors.right: isLeft ? undefined         : decorFrame.right
            anchors.leftMargin:  isLeft ? -9 : 0
            anchors.rightMargin: isLeft ? 0  : -9
            radius: 6
            color:  "transparent"
            border.width: 10
            // see outerGlow above: border.color RGBA held constant, pulse moved to `opacity`.
            border.color: Qt.rgba(frame.glowGreen.r, frame.glowGreen.g, frame.glowGreen.b, frame.glowA * 0.50)
            opacity: isFocused ? Math.max(0.45, lampPulse.val + 0.40) : 0.06
            z: -1
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.7; blurMax: 16 }
            Behavior on opacity { enabled: !lampPulse.isDragging; NumberAnimation { duration: 460; easing.type: Easing.InOutCubic } }
        }
    }

    // Cabochons: soft amber jewels at the top corners.
    Repeater {
        model: 2
        Item {
            property bool isLeft: index === 0
            width: 18; height: 18
            anchors.top: decorFrame.top
            anchors.topMargin: -2
            anchors.left:  isLeft ? decorFrame.left  : undefined
            anchors.right: isLeft ? undefined         : decorFrame.right
            anchors.leftMargin:  isLeft ? -2 : 0
            anchors.rightMargin: isLeft ? 0  : -2
            z: -1
            Rectangle {
                anchors.fill: parent
                radius: 9
                // see outerGlow above: color RGB+alpha held constant, pulse moved to `opacity` —
                // split onto its own Rectangle (not the shared parent Item) so the highlight dot
                // below, a sibling, keeps its own constant (non-pulsing) rendered alpha.
                color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, 1.0)
                opacity: isFocused ? Math.max(0.40, lampPulse.val * 0.7) : 0.14
                layer.enabled: true
                layer.effect: MultiEffect { blurEnabled: true; blur: 0.85; blurMax: 14 }
                Behavior on opacity { enabled: !lampPulse.isDragging; NumberAnimation { duration: 300; easing.type: Easing.OutCubic } }
            }
            Rectangle {
                width: 4; height: 4; radius: 2
                x: 4; y: 3
                color: Qt.rgba(1.0, 0.96, 0.87, isFocused ? 0.9 : 0.0)
                Behavior on color { ColorAnimation { duration: 300 } }
            }
        }
    }

    // Lead came seams: dark breaks at hue transitions (leaded-panel reading).
    Repeater {
        model: 4
        Rectangle {
            property bool isLeft: (index % 2) === 0
            property bool isTop:  index < 2
            width: 5; height: 11; radius: 3
            anchors.left:  isLeft ? decorFrame.left  : undefined
            anchors.right: isLeft ? undefined         : decorFrame.right
            anchors.leftMargin:  isLeft ? -7 : 0
            anchors.rightMargin: isLeft ? 0  : -7
            anchors.top: decorFrame.top
            anchors.topMargin: isTop ? decorFrame.height * 0.14
                                      : decorFrame.height * 0.46
            color: Qt.rgba(0.024, 0.063, 0.063, isFocused ? 0.78 : 0.45)
            z: -1
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.5; blurMax: 3 }
        }
    }

    // ===== DECOR FRAME — inset by glowMargin so the ARGB glow band exists =======
    Item {
        id: decorFrame
        x: frame.glowMargin
        y: frame.glowMargin
        width:  parent.width  - 2*frame.glowMargin
        height: parent.height - 2*frame.glowMargin

    // ===== INACTIVE DIM ===================================================
    Rectangle {
        anchors.fill: parent
        z: 460
        color: "#000000"
        opacity: 0.20
        visible: !isFocused
        enabled: false
        Behavior on opacity { NumberAnimation { duration: 220 } }
    }

    // ===== OUTER BRONZE RIM (lead came outline + bronze fillet) ===========
    Rectangle {
        anchors.fill: parent
        z: 458
        color: "transparent"
        border.color: tCame
        border.width: 1
    }
    Rectangle {
        anchors.fill: parent
        anchors.margins: 1
        z: 457
        color: "transparent"
        border.color: tBronzeMid
        border.width: 1
        opacity: 0.85
    }

    // ===================================================================
    // TITLE BAR
    // ===================================================================
    Item {
        id: titlebar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: titleH
        z: 100

        // -- bronze base gradient --
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.00; color: tBronzeWarm }
                GradientStop { position: 0.40; color: tBronzeMid }
                GradientStop { position: 0.70; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        // -- top hairline shine
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: tBronzeShine
            opacity: 0.80
        }
        // -- bottom lead-came seam
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1
            color: tCame
        }

        // -- LEFT AMETHYST UNMAX BUTTON (was the emerald cabochon ornament) ----------
        // operator 2026-06-28: dedicated "unmax / restore" button, AMETHYST so it is never confused
        // with the green Maximize button on the right. Same plaque shape/position/width as before so
        // the title-bar layout does not shift (pixel-identical at rest); recolored emerald→amethyst
        // and made interactive with the same hover/press feel as the TiffanyButtons.
        Item {
            id: leftOrnament
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            width: 28
            height: titleH - 8

            property bool hovered: false
            property bool pressed: false

            Rectangle {
                anchors.fill: parent
                radius: 3
                gradient: Gradient {
                    GradientStop { position: 0.0; color: tBronzeWarm }
                    GradientStop { position: 0.5; color: tBronze }
                    GradientStop { position: 1.0; color: tBronzeDark }
                }
                border.color: tCame
                border.width: 1
            }
            // amethyst cabochon (the Unmax jewel)
            Rectangle {
                id: cabochonRect
                anchors.centerIn: parent
                anchors.verticalCenterOffset: leftOrnament.pressed ? 1 : 0
                Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
                width: 14; height: 14
                radius: 7
                property color cabochonTop: isFocused ? tAmethShine : Qt.darker(tAmethShine, 1.4)
                Behavior on cabochonTop { ColorAnimation { duration: 240 } }
                gradient: Gradient {
                    GradientStop { position: 0.0; color: leftOrnament.hovered ? Qt.lighter(cabochonRect.cabochonTop, 1.10) : cabochonRect.cabochonTop }
                    GradientStop { position: 0.55; color: tAmethyst }
                    GradientStop { position: 1.0; color: tAmethDeep }
                }
                border.color: tBronzeShine
                border.width: 1
                scale: leftOrnament.hovered ? 1.08 : 1.0
                Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
            }
            // upper-left glint
            Rectangle {
                x: leftOrnament.width / 2 - 6
                y: leftOrnament.height / 2 - 5 + (leftOrnament.pressed ? 1 : 0)
                width: 4; height: 3
                radius: 1.5
                color: Qt.rgba(1, 1, 1, leftOrnament.hovered ? 0.85 : 0.65)
                Behavior on y { NumberAnimation { duration: 90 } }
            }
            // click → UNMAX / restore (guarded: only when maximized). Mirrors the maximize button's
            // restore path: return to the saved windowed geometry, then re-raise the Kith cursor.
            // Uses HoverHandler + TapHandler (identical to the working TiffanyButtons) — a legacy
            // MouseArea here loses its click to the titlebar DragHandler's grab, so it never fired.
            HoverHandler {
                onHoveredChanged: leftOrnament.hovered = hovered
                cursorShape: Qt.PointingHandCursor
            }
            TapHandler {
                onPressedChanged: leftOrnament.pressed = pressed
                onTapped: {
                    // Unmax = snap INTO the tile grid (operator definitive intent 2026-07-06:
                    // "only unmax makes them small so each window unmaxed up to 8 will snap to
                    // a tile grid.. 4 on top 4 on bottom"). Windows OPEN maximized+untiled now
                    // (manage() — tiled starts false); Amethyst moves this one from the max
                    // slot into the grid and TilingManager.updateLayout() places it — no
                    // saved-geometry restore here, the grid owns unmaxed geometry.
                    if (!frame.maximized || frame.isTiled) return
                    // Grid cap (operator 2026-07-06: "we just do eight at a time"):
                    // with 8 windows already tiled (the full 4+4), a further unmax is
                    // refused — Green-max one out of the grid first to free a slot.
                    if (tilingManager.tileOrder.length >= 8) return
                    windowMgr.activateWindow(frame.winId)
                    windowMgr.setMaximized(frame.winId, false)
                    windowMgr.setTiled(frame.winId, true)
                    frame.maximized = false
                }
            }
        }

        // -- WINDOW BUTTON ROW (rightmost) ------------------------------
        Row {
            id: buttonRow
            anchors.right: parent.right
            anchors.rightMargin: 6
            anchors.verticalCenter: parent.verticalCenter
            spacing: 6

            TiffanyButton {
                jewelBase: tSapphire
                jewelDeep: tSapphDeep
                jewelShine: tSapphShine
                glyphText: "–"
                onClicked: windowMgr.minimizeWindow(frame.winId)
            }
            // GREEN = dedicated MAXIMIZE (operator 2026-06-28: each button one fixed job, for
            // accessibility — no hidden toggle state to perceive). Unmax is the separate amethyst
            // button on the LEFT. Guarded: no-op when already maximized, so it can never re-capture
            // the maximized size into saved*/poison the restore geometry.
            TiffanyButton {
                jewelBase: tEmerald
                jewelDeep: tEmDeep
                jewelShine: tEmShine
                glyphText: "□"
                onClicked: {
                    if (frame.maximized) return
                    windowMgr.activateWindow(frame.winId)
                    windowMgr.setTiled(frame.winId, false)
                    // Save windowed geometry only if not already near-full-screen
                    // (prevents poisoning saved* with maximized coords so Amethyst unmax works).
                    var sw = windowMgr.screenWidth()
                    var sh = windowMgr.screenHeight()
                    var mw = sw - frame.frameLeft - frame.frameRight
                    var mh = sh - frame.titleH - frame.bottomH
                    if (frame.windowW < mw - 20 || frame.windowH < mh - 20) {
                        frame.savedX = frame.windowX
                        frame.savedY = frame.windowY
                        frame.savedW = frame.windowW
                        frame.savedH = frame.windowH
                    }
                    windowMgr.setMaximized(frame.winId, true)
                    windowMgr.moveWindow(frame.winId, frame.frameLeft, frame.titleH)
                    windowMgr.resizeWindow(frame.winId, mw, mh)
                    frame.maximized = true
                }
            }
            TiffanyButton {
                jewelBase: tRuby
                jewelDeep: tRubyDeep
                jewelShine: tRubyShine
                glyphText: "✕"
                onClicked: windowMgr.closeWindow(frame.winId)
            }
        }

        // -- STAINED-GLASS BAND (with title text overlaid) -------------
        Item {
            id: glassBand
            layer.enabled: true
            anchors.left: leftOrnament.right
            anchors.leftMargin: 8
            anchors.right: buttonRow.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height - 10
            clip: true

            // lead-came backdrop — shows through every 1px gap
            Rectangle {
                anchors.fill: parent
                color: tCame
                radius: 1
            }

            // 10 jewel panes in a symmetric pattern
            Row {
                id: paneRow
                anchors.fill: parent
                anchors.margins: 1
                spacing: 1
                Repeater {
                    model: [
                        frame.tEmerald,  frame.tAmber,    frame.tRuby,
                        frame.tAmethyst, frame.tSapphire, frame.tHoney,
                        frame.tAmethyst, frame.tRuby,     frame.tAmber,
                        frame.tEmerald
                    ]
                    delegate: Rectangle {
                        width: (paneRow.width - 9) / 10
                        height: paneRow.height
                        gradient: Gradient {
                            GradientStop { position: 0.00; color: Qt.lighter(modelData, 1.35) }
                            GradientStop { position: 0.40; color: modelData }
                            GradientStop { position: 1.00; color: Qt.darker(modelData, 1.55) }
                        }
                        opacity: isFocused ? 0.96 : 0.55
                        Behavior on opacity { NumberAnimation { duration: 240 } }

                        // upper sheen
                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: parent.height * 0.42
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.32) }
                                GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.0) }
                            }
                        }
                        // tiny bottom shadow
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 1
                            color: Qt.rgba(0, 0, 0, 0.45)
                        }
                    }
                }
            }

            // title text — shadow + main
            Text {
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 1
                anchors.verticalCenterOffset: 1
                text: frame.windowTitle
                color: Qt.rgba(0, 0, 0, 0.78)
                font.pixelSize: theme.fontMedium
                font.bold: true
                font.family: theme.fontFamily; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
                elide: Text.ElideRight
                width: glassBand.width - 10
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                anchors.centerIn: parent
                text: frame.windowTitle
                color: isFocused ? tCream : Qt.rgba(0.86, 0.80, 0.62, 0.72)
                font.pixelSize: theme.fontMedium
                font.bold: true
                font.family: theme.fontFamily; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
                elide: Text.ElideRight
                width: glassBand.width - 10
                horizontalAlignment: Text.AlignHCenter
                Behavior on color { ColorAnimation { duration: 220 } }
            }
        }

        // -- GliaTalk locally-integrated menu (Unity LIM) -------------------
        // 2026-07-11 fix: this block lived INSIDE glassBand, but anchored to
        // leftOrnament — a sibling of glassBand, not of the menu — which is an
        // illegal QML anchor ("Cannot anchor to an item that isn't a parent or
        // sibling", journal-spammed since the 07-10 framemenu patch). Moved up
        // one level into `titlebar`, where leftOrnament IS a sibling: the
        // anchors as written become legal and the on-screen position is
        // unchanged (glassBand.left == leftOrnament.right + 8 anyway). Bonus:
        // the dropdown is no longer clipped by glassBand's clip:true band.
        GliaFrameMenu {
            anchors.left: leftOrnament.right
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            z: 60
            menusJson: (typeof windowMgr !== "undefined" && windowMgr.activeAppMenus !== undefined) ? windowMgr.activeAppMenus : ""
            active: frame.isFocused && !frame.maximized
            onInvoked: function(id) { if (typeof windowMgr !== "undefined") windowMgr.invokeAppMenu(id) }
        }

        // -- drag handler: move window from titlebar ------------------------
        DragHandler {
            id: titleDrag
            target: null
            property int  startWinX
            property int  startWinY
            property real startGlobalX
            property real startGlobalY
            onActiveChanged: {
                if (active) {
                    lampPulse.isDragging = true
                    startWinX    = frame.windowX
                    startWinY    = frame.windowY
                    startGlobalX = windowMgr.mouseX
                    startGlobalY = windowMgr.mouseY
                    windowMgr.activateWindow(frame.winId)
                    // Tiled window grabbed: tell the grid to hold this one's slot open
                    // (grab-and-reorder, operator/test-group 2026-07-06).
                    if (frame.isTiled) tilingManager.beginTileDrag(frame.winId)
                } else {
                    lampPulse.isDragging = false
                    // Drop: commit the hovered slot (or snap home if released off-grid).
                    if (frame.isTiled) tilingManager.endTileDrag(frame.winId,
                                                                 windowMgr.mouseX,
                                                                 windowMgr.mouseY)
                }
            }
            onCentroidChanged: {
                if (!active) return
                windowMgr.moveWindow(frame.winId,
                    startWinX + Math.round(windowMgr.mouseX - startGlobalX),
                    startWinY + Math.round(windowMgr.mouseY - startGlobalY))
                // Live shuffle: the other tiles re-flow around the cursor's slot.
                if (frame.isTiled) tilingManager.tileDragHover(frame.winId,
                                                               windowMgr.mouseX,
                                                               windowMgr.mouseY)
            }
        }
        TapHandler {
            onTapped: windowMgr.activateWindow(frame.winId)
        }
    }

    // ===================================================================
    // LEFT SIDE RAIL — bronze with vertical jewel chain
    // ===================================================================
    Item {
        id: leftSide
        anchors.top: titlebar.bottom
        anchors.bottom: bottomBar.top
        anchors.left: parent.left
        width: frameLeft
        z: 95

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.00; color: tBronzeDark }
                GradientStop { position: 0.35; color: tBronze }
                GradientStop { position: 0.65; color: tBronzeMid }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        // lead-came lines on both edges
        Rectangle { anchors.left:  parent.left;  width: 1; height: parent.height; color: tCame }
        Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: tCame }
        // soft inner highlight
        Rectangle { x: 4; width: 1; height: parent.height; color: tBronzeShine; opacity: 0.35 }

        // vertical jewel chain
        Column {
            anchors.fill: parent
            anchors.topMargin: 14
            anchors.bottomMargin: 14
            spacing: 14
            Repeater {
                model: Math.max(0, Math.floor((leftSide.height - 28) / 18))
                delegate: Item {
                    width: leftSide.width
                    height: 6
                    Rectangle {
                        id: leftJewelRect
                        anchors.centerIn: parent
                        width: 6; height: 6
                        radius: 3
                        readonly property var cycle: [
                            frame.tAmber, frame.tRuby, frame.tEmerald,
                            frame.tSapphire, frame.tAmethyst
                        ]
                        property color baseCol: cycle[index % cycle.length]
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.lighter(leftJewelRect.baseCol, 1.45) }
                            GradientStop { position: 0.5; color: leftJewelRect.baseCol }
                            GradientStop { position: 1.0; color: Qt.darker(leftJewelRect.baseCol, 1.4) }
                        }
                        border.color: tBronzeShine
                        border.width: 0.5
                        opacity: isFocused ? 1.0 : 0.55
                        Behavior on opacity { NumberAnimation { duration: 240 } }
                    }
                }
            }
        }

        TapHandler { onTapped: windowMgr.activateWindow(frame.winId) }
    }

    // ===================================================================
    // RIGHT SIDE RAIL — mirror of left, palette rotated
    // ===================================================================
    Item {
        id: rightSide
        anchors.top: titlebar.bottom
        anchors.bottom: bottomBar.top
        anchors.right: parent.right
        width: frameRight
        z: 95

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.00; color: tBronzeDark }
                GradientStop { position: 0.30; color: tBronzeMid }
                GradientStop { position: 0.60; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        Rectangle { anchors.left:  parent.left;  width: 1; height: parent.height; color: tCame }
        Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: tCame }
        Rectangle { x: rightSide.width - 5; width: 1; height: parent.height; color: tBronzeShine; opacity: 0.35 }

        Column {
            anchors.fill: parent
            anchors.topMargin: 14
            anchors.bottomMargin: 14
            spacing: 14
            Repeater {
                model: Math.max(0, Math.floor((rightSide.height - 28) / 18))
                delegate: Item {
                    width: rightSide.width
                    height: 6
                    Rectangle {
                        id: rightJewelRect
                        anchors.centerIn: parent
                        width: 6; height: 6
                        radius: 3
                        readonly property var cycle: [
                            frame.tAmethyst, frame.tSapphire, frame.tEmerald,
                            frame.tRuby, frame.tAmber
                        ]
                        property color baseCol: cycle[index % cycle.length]
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.lighter(rightJewelRect.baseCol, 1.45) }
                            GradientStop { position: 0.5; color: rightJewelRect.baseCol }
                            GradientStop { position: 1.0; color: Qt.darker(rightJewelRect.baseCol, 1.4) }
                        }
                        border.color: tBronzeShine
                        border.width: 0.5
                        opacity: isFocused ? 1.0 : 0.55
                        Behavior on opacity { NumberAnimation { duration: 240 } }
                    }
                }
            }
        }

        TapHandler { onTapped: windowMgr.activateWindow(frame.winId) }
    }

    // ===================================================================
    // BOTTOM BAR — bronze with a leaded mosaic band + corner grip
    // ===================================================================
    Item {
        id: bottomBar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: bottomH
        z: 100

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.00; color: tBronzeDark }
                GradientStop { position: 0.30; color: tBronze }
                GradientStop { position: 0.65; color: tBronzeMid }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        // top lead-came seam
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: tCame
        }
        // bottom lead-came seam
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1
            color: tCame
        }

        // leaded mosaic band — chain of small jewel lozenges
        Item {
            id: leadedBand
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 38
            anchors.right: parent.right
            anchors.rightMargin: 38
            height: 12

            Rectangle { anchors.fill: parent; color: tCame; radius: 1 }

            Row {
                anchors.fill: parent
                anchors.margins: 1
                spacing: 1
                Repeater {
                    model: Math.max(0, Math.floor((leadedBand.width - 2) / 17))
                    delegate: Rectangle {
                        readonly property var cycle: [
                            frame.tAmber, frame.tEmerald, frame.tRuby,
                            frame.tSapphire, frame.tAmethyst, frame.tHoney
                        ]
                        property color cc: cycle[index % cycle.length]
                        width: 16
                        height: leadedBand.height - 2
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.lighter(cc, 1.35) }
                            GradientStop { position: 0.5; color: cc }
                            GradientStop { position: 1.0; color: Qt.darker(cc, 1.55) }
                        }
                        opacity: isFocused ? 0.92 : 0.50
                        Behavior on opacity { NumberAnimation { duration: 240 } }

                        // tiny upper sheen
                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 3
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(1,1,1, 0.4) }
                                GradientStop { position: 1.0; color: Qt.rgba(1,1,1, 0.0) }
                            }
                        }
                    }
                }
            }
        }

        // bottom-right resize grip (3 diagonal bronze lines)
        Item {
            id: resizeBR
            width: 18; height: 18
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            HoverHandler { cursorShape: Qt.SizeFDiagCursor }
            DragHandler {
                target: null
                property int  startW
                property int  startH
                property real startGX
                property real startGY
                onActiveChanged: {
                    if (active) {
                        startW  = frame.windowW
                        startH  = frame.windowH
                        startGX = windowMgr.mouseX
                        startGY = windowMgr.mouseY
                    }
                }
                onCentroidChanged: {
                    if (!active) return
                    var dx = windowMgr.mouseX - startGX
                    var dy = windowMgr.mouseY - startGY
                    windowMgr.resizeWindow(frame.winId,
                        Math.max(frame.minW, startW + dx),
                        Math.max(frame.minH, startH + dy))
                }
            }
            // three diagonal grip lines
            Rectangle { x: 10; y: 10; width: 5; height: 1; color: tBronzeShine }
            Rectangle { x:  7; y: 12; width: 8; height: 1; color: tBronzeShine; opacity: 0.7 }
            Rectangle { x:  4; y: 14; width:11; height: 1; color: tBronzeShine; opacity: 0.4 }
        }
    }

    // ===================================================================
    // EDGE RESIZE HANDLERS (thin invisible strips with cursor + drag)
    // ===================================================================
    Item {                                                    // right edge
        anchors.right: parent.right
        anchors.top: titlebar.bottom
        anchors.bottom: bottomBar.top
        width: 4
        HoverHandler { cursorShape: Qt.SizeHorCursor }
        DragHandler {
            target: null
            property int  startW
            property real startGX
            onActiveChanged: {
                if (active) { startW = frame.windowW; startGX = windowMgr.mouseX }
            }
            onCentroidChanged: {
                if (!active) return
                windowMgr.resizeWindow(frame.winId,
                    Math.max(frame.minW, startW + windowMgr.mouseX - startGX),
                    frame.windowH)
            }
        }
    }
    Item {                                                    // left edge
        anchors.left: parent.left
        anchors.top: titlebar.bottom
        anchors.bottom: bottomBar.top
        width: 4
        HoverHandler { cursorShape: Qt.SizeHorCursor }
        DragHandler {
            target: null
            property int  startW
            property int  startX
            property real startGX
            onActiveChanged: {
                if (active) {
                    startW  = frame.windowW
                    startX  = frame.windowX
                    startGX = windowMgr.mouseX
                }
            }
            onCentroidChanged: {
                if (!active) return
                var dx = windowMgr.mouseX - startGX
                windowMgr.resizeWindow(frame.winId, Math.max(frame.minW, startW - dx), frame.windowH)
                windowMgr.moveWindow(frame.winId, startX + dx, frame.windowY)
            }
        }
    }

    // ===== AMBER WASH — lampglass casts warm light onto the top of the titlebar =
    Rectangle {
        id: amberWash
        anchors.top:   parent.top
        anchors.left:  parent.left
        anchors.right: parent.right
        height: 22
        z: 101
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, isFocused ? 0.42 : 0.12) }
            GradientStop { position: 0.5; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, isFocused ? 0.12 : 0.04) }
            GradientStop { position: 1.0; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, 0.0) }
        }
        Behavior on opacity { NumberAnimation { duration: 380 } }
    }

    } // end decorFrame

    // ===================================================================
    // TIFFANY JEWELLED BUTTON (inline component, Qt 6.3+)
    // ===================================================================
    component TiffanyButton: Item {
        id: btn
        property color jewelBase
        property color jewelDeep
        property color jewelShine
        property string glyphText: ""
        signal clicked()

        property bool hovered: false
        property bool pressed: false

        width: 22
        height: 22

        // brass bezel
        Rectangle {
            anchors.fill: parent
            radius: width / 2
            gradient: Gradient {
                GradientStop { position: 0.00; color: tBronzeShine }
                GradientStop { position: 0.45; color: tBronzeMid }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
            border.color: tCame
            border.width: 1
        }
        // inset ring shadow (gives the bezel depth)
        Rectangle {
            anchors.centerIn: parent
            width: parent.width - 4
            height: parent.height - 4
            radius: width / 2
            color: "transparent"
            border.color: tBronzeDark
            border.width: 1
            opacity: 0.7
        }

        // the jewel itself
        Rectangle {
            id: jewel
            anchors.centerIn: parent
            anchors.verticalCenterOffset: btn.pressed ? 1 : 0
            Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
            width: 14
            height: 14
            radius: 7
            gradient: Gradient {
                GradientStop { position: 0.00; color: btn.hovered ? Qt.lighter(btn.jewelShine, 1.10) : btn.jewelShine }
                GradientStop { position: 0.45; color: btn.jewelBase }
                GradientStop { position: 1.00; color: btn.jewelDeep }
            }
            border.color: tBronzeShine
            border.width: 1
            scale: btn.hovered ? 1.08 : 1.0
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        // glint
        Rectangle {
            x: 7
            y: 5 + (btn.pressed ? 1 : 0)
            width: 4; height: 3
            radius: 1.5
            color: Qt.rgba(1, 1, 1, btn.hovered ? 0.85 : 0.62)
            Behavior on y { NumberAnimation { duration: 90 } }
        }
        // etched glyph
        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 1 + (btn.pressed ? 1 : 0)
            text: btn.glyphText
            color: Qt.rgba(0, 0, 0, 0.62)
            font.pixelSize: theme.fontSmall
            font.bold: true
            font.family: theme.fontFamily; font.italic: theme.fontItalic; font.letterSpacing: theme.letterSpacing
            Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
        }

        HoverHandler {
            onHoveredChanged: btn.hovered = hovered
            cursorShape: Qt.PointingHandCursor
        }
        TapHandler {
            // WithinBounds takes an exclusive grab (unlike the default DragThreshold, which is only
            // passive and lets ancestor handlers also react to the same tap). Without this, the
            // titlebar's own blanket `TapHandler { onTapped: windowMgr.activateWindow(...) }` (below,
            // in `titlebar`) ALSO fires on every button tap — harmless for Amethyst/Green/Close since
            // they call activateWindow() themselves first anyway, but for Minimize it fires AFTER
            // minimizeWindow() and silently clears `minimized` in the model (the "glass stays behind"
            // bug — confirmed via ncde-minimize-debug.log, session 55/56).
            gesturePolicy: TapHandler.WithinBounds
            onPressedChanged: btn.pressed = pressed
            onTapped: btn.clicked()
        }
    }
}
