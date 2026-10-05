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
import "ncde-color.js" as Col

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
    // The standard (2026-09-26): the frame is made of the SAME metal as every
    // socket and bezel — NCDEKit's palette metal (the old hexes' exact Lab
    // lightness/chroma, hue from the palette's gold). Default palette: unchanged.
    NCDEKit { id: mk }
    readonly property color tCame:        mk.metalCame
    readonly property color tCameLip:     mk.metalCameLip
    // Bronze (oxidised → polished)
    readonly property color tBronzeDark:  mk.metalDark
    readonly property color tBronze:      mk.metal
    readonly property color tBronzeMid:   mk.metalMid
    readonly property color tBronzeWarm:  mk.metalWarm
    readonly property color tBronzeShine: mk.metalShine
    // Seeded per-tile jitter (2026-09-25, BEAUTIFY-NEXT #34): real mosaic tiles are
    // each set at a slightly different tilt, so each catches the light a little
    // differently. Mulberry32 on the tile index: fixed per tile, never shimmers.
    function _jit(i, salt) {
        var t = ((i + 1) * 0x6D2B79F5 + (salt | 0)) | 0
        t = Math.imul(t ^ (t >>> 15), t | 1)
        t ^= t + Math.imul(t ^ (t >>> 7), t | 61)
        return ((t ^ (t >>> 14)) >>> 0) / 4294967296
    }
    // Lead came / solder colour: tin-lead catching the shell's one light (ShellLight)
    readonly property color tSolder: Qt.tint(tBronzeShine, ShellLight.lt(0.45))
    // Verdigris (2026-09-25, BEAUTIFY-NEXT #32): bronze patina gathers where polish
    // never reaches — the recesses where rails meet the bars, the sockets under
    // the jewels. The palette's own verd, lifted to the pale blue-green of real
    // copper carbonate (Lab L 62, chroma held to 26), so every preset gets its own.
    readonly property color tPatina: mk.patina
    function patina(a) { return Qt.rgba(tPatina.r, tPatina.g, tPatina.b, a) }
    // Polished-metal read (2026-09-24, operator: "more metal"): a hard specular
    // band + a bright bevel edge are what make bronze read as metal rather than
    // painted wood. Derived from the bronze ramp + gilt4, so Iris still tints it.
    // …lit by the one light's own colour (ShellLight.tone), not a fixed warm white
    readonly property color tMetalHi:     Qt.tint(tBronzeWarm, Qt.rgba(ShellLight.tone.r, ShellLight.tone.g, ShellLight.tone.b, 0.55))
    readonly property color tMetalEdge:   Qt.tint(tBronzeShine, Qt.rgba(ShellLight.tone.r, ShellLight.tone.g, ShellLight.tone.b, 0.35))
    // Jewels — ALL from the Iris palette (2026-09-25; colour is universal).
    // Amber / emerald / ruby are the palette's own gilt2 / verd / wine4, and now
    // their deep and shine tones are too (Lab lightness steps, hue kept). Sapphire
    // and amethyst keep their hue identity — the minimize button stays blue, the
    // unmax button violet — but are re-made in the palette's material: hue pulled
    // 30% toward the accent (Col.harmonize), so they sit IN the palette instead of
    // on it. Lightness of every base/deep/shine matches the old hand-tuned hexes.
    readonly property color _acc: (typeof ncde !== "undefined" && ncde.accent !== undefined) ? ncde.accent : "#8a6cc4"
    // Amber
    readonly property color tAmber:       ncde.gilt2
    readonly property color tAmberDeep:   Col.withL(ncde.gilt2, 24)
    readonly property color tAmberShine:  ncde.gilt4
    // Emerald
    readonly property color tEmerald:     ncde.verd
    readonly property color tEmDeep:      Col.withL(ncde.verd, 21)
    readonly property color tEmShine:     Col.withL(ncde.verd, 78)
    // Ruby
    readonly property color tRuby:        ncde.wine4
    readonly property color tRubyDeep:    Col.withL(ncde.wine4, 10)
    readonly property color tRubyShine:   Col.withL(ncde.wine4, 57)
    // Sapphire
    readonly property color tSapphire:    Col.harmonize("#2c4090", _acc, 30, undefined, 0.3)
    readonly property color tSapphDeep:   Col.withL(tSapphire, 12)
    readonly property color tSapphShine:  Col.withL(tSapphire, 62)
    // Amethyst
    readonly property color tAmethyst:    Col.harmonize("#4f3274", _acc, 27, undefined, 0.3)
    readonly property color tAmethDeep:   Col.withL(tAmethyst, 12)
    readonly property color tAmethShine:  Col.withL(tAmethyst, 53)
    // Opalescent / accents
    readonly property color tHoney:       Col.withL(ncde.gilt3, 72)
    readonly property color tCream:       Col.tone(ncde.gilt4, 92, 16)
    readonly property color tInk:         Col.tone(mk.gilt2, 5.8, 8.4)   // was #1a0e04
    // The title band's ten panes, in order (shared with the light they cast below them)
    readonly property var paneColors: [
        tEmerald,  tAmber,    tRuby,
        tAmethyst, tSapphire, tHoney,
        tAmethyst, tRuby,     tAmber,
        tEmerald
    ]

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
    // (2026-09-26) these WERE fixed teal/green — every window wore a teal ring on
    // every palette. Now the palette's glow and verd, as the comment always said.
    property color glowBase:  mk.glowOrAccent
    property color glowGreen: mk.verd

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
            running: frame.visible && !isMinimized && !isFocused
                     && animPolicy.decorative && animPolicy.idleLoops
                     && !animPolicy.screenIdle
            loops: Animation.Infinite
            NumberAnimation { to: 1.0; duration: 4000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.0; duration: 4000; easing.type: Easing.InOutSine }
            onRunningChanged: if (!running) lampPulse.ember = 0.0
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
            color: mk.shadeA(isFocused ? 0.78 : 0.45)
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

    // ===== STACK HALO (tarot, 2026-09-26) ==================================
    // While this window is a card in the stack: a soft halo in the frame's glow that
    // breathes on the stack's one shared clock (offset by slot, so the breath
    // ripples across the spread), brightening when the card is lifted by hover.
    readonly property bool _tm: typeof tilingManager !== "undefined" && tilingManager !== null
    readonly property real stackBreath: (_tm && isTiled && !maximized) ? tilingManager.breathOf(frame.winId) + 0 * tilingManager.breath : 0
    readonly property bool stackHovered: _tm && isTiled && tilingManager.hoverWin === frame.winId
    Rectangle {
        id: stackHalo
        anchors.fill: decorFrame
        anchors.margins: -7
        radius: frame.cornerRadius + 7
        z: -2
        visible: isTiled && !maximized && animPolicy.decorative
        color: "transparent"
        border.width: 6
        border.color: Qt.rgba(frame.glowBase.r, frame.glowBase.g, frame.glowBase.b, 1)
        property real lifted: frame.stackHovered ? 1 : 0
        Behavior on lifted { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }
        opacity: 0.10 + 0.45 * lifted + 0.20 * frame.stackBreath
        layer.enabled: visible
        layer.effect: MultiEffect { blurEnabled: true; blur: 1.0; blurMax: 16 }
    }

    // ===== GOLD-FOIL SHIMMER (tarot, 2026-09-26) ===========================
    // Operator: windows as tarot cards — "gold foil edge shimmer ... like sunlight
    // hitting the gilt edge of a premium deck" when a window becomes active. A band
    // of the one light, gilded by the frame's own metal, runs once around the brass
    // rails, masked to the rails so it never crosses the glass or the app.
    Item {
        id: foil
        x: frame.glowMargin; y: frame.glowMargin
        width: parent.width - 2 * frame.glowMargin
        height: parent.height - 2 * frame.glowMargin
        z: 455
        visible: foilRun.running
        property real pos: -240
        property int  duration: 1100
        readonly property color gilt: Qt.tint(tBronzeShine, ShellLight.lt(0.55))
        // four clipping strips, one per brass rail — each holds its slice of the same
        // moving band (a mask texture wasn't needed: clipping is exact and cheaper)
        readonly property real railW: frame.frameLeft - 3
        component FoilRail: Item {
            clip: true
            Rectangle {
                width: 200; height: foil.height * 3
                x: foil.pos - parent.x; y: -foil.height - parent.y
                rotation: 24
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.00; color: "transparent" }
                    GradientStop { position: 0.42; color: Qt.rgba(foil.gilt.r, foil.gilt.g, foil.gilt.b, 0.35) }
                    GradientStop { position: 0.50; color: Qt.rgba(foil.gilt.r, foil.gilt.g, foil.gilt.b, 0.90) }
                    GradientStop { position: 0.58; color: Qt.rgba(foil.gilt.r, foil.gilt.g, foil.gilt.b, 0.35) }
                    GradientStop { position: 1.00; color: "transparent" }
                }
            }
        }
        FoilRail { x: 0; y: 0; width: foil.width; height: foil.railW }                               // top
        FoilRail { x: 0; y: foil.height - foil.railW; width: foil.width; height: foil.railW }        // bottom
        FoilRail { x: 0; y: foil.railW; width: foil.railW; height: foil.height - 2 * foil.railW }    // left
        FoilRail { x: foil.width - foil.railW; y: foil.railW; width: foil.railW; height: foil.height - 2 * foil.railW }  // right
        // …and whenever this card comes to rest after a deal or a shuffle
        Connections {
            target: typeof tilingManager !== "undefined" ? tilingManager : null
            ignoreUnknownSignals: true
            function onCardLanded(winId) { if (winId === frame.winId && animPolicy.decorative) foilRun.restart() }
        }
        NumberAnimation {
            id: foilRun
            target: foil; property: "pos"
            from: -240; to: foil.width + 240
            duration: foil.duration; easing.type: Easing.InOutSine
        }
    }

    // ===== INACTIVE DIM ===================================================
    Rectangle {
        anchors.fill: parent
        z: 460
        color: mk.shade
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

        // -- polished bronze: bevel edge, specular band, falloff --
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.00; color: tMetalEdge }
                GradientStop { position: 0.06; color: tBronzeWarm }
                GradientStop { position: 0.28; color: tBronzeMid }
                GradientStop { position: 0.42; color: tMetalHi }
                GradientStop { position: 0.52; color: tBronzeWarm }
                GradientStop { position: 0.78; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        // -- brushed grain: faint alternating pinstripes along the bar --
        Repeater {
            model: Math.floor(titlebar.height / 2)
            Rectangle {
                y: index * 2; width: titlebar.width; height: 1
                color: index % 2 ? mk.shadeA(0.07) : Qt.rgba(1, 1, 1, 0.05)
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
        // verdigris at both ends, where the side rails meet this bar (2026-09-25, #32):
        // a soft patina fading inward, with a few seeded specks of heavier crust
        Repeater {
            model: 2
            Item {
                readonly property bool isLeft: index === 0
                anchors.bottom: parent.bottom; anchors.bottomMargin: 1
                anchors.left:  isLeft ? parent.left  : undefined
                anchors.right: isLeft ? undefined    : parent.right
                width: 30; height: 6
                Rectangle {
                    anchors.fill: parent
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: frame.patina(isLeft ? 0.38 : 0.0) }
                        GradientStop { position: 1.0; color: frame.patina(isLeft ? 0.0 : 0.38) }
                    }
                }
                Repeater {
                    model: 4
                    Rectangle {
                        readonly property real s: frame._jit(index + (parent.isLeft ? 0 : 8) + ("bottom" === "top" ? 16 : 0), 808)
                        readonly property real t: frame._jit(index + (parent.isLeft ? 0 : 8) + ("bottom" === "top" ? 16 : 0), 909)
                        width: s > 0.55 ? 2 : 1; height: width; radius: width / 2
                        x: parent.isLeft ? Math.round(1 + 12 * s) : Math.round(parent.width - 2 - 12 * s)
                        y: Math.round((parent.height - height) * t)
                        color: frame.patina(0.35 + 0.25 * t)
                    }
                }
            }
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
            // inset ring shadow (bezel depth) — matches TiffanyButton's treatment;
            // leftOrnament was the one titlebar button with no depth cue at all.
            Rectangle {
                anchors.centerIn: parent
                width: parent.width - 4
                height: parent.height - 4
                radius: 2
                color: "transparent"
                border.color: tBronzeDark
                border.width: 1
                opacity: 0.7
            }
            // socket shadow — matches TiffanyButton's treatment; leftOrnament was the
            // one titlebar jewel with no socket depth cue at all.
            Rectangle {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 1.5 + (leftOrnament.pressed ? 1 : 0)
                width: 15; height: 15; radius: 7.5
                color: mk.shadeA(0.5)
                layer.enabled: true
                layer.effect: MultiEffect { blurEnabled: true; blur: 0.4; blurMax: 6 }
            }
            // amethyst cabochon (the Unmax jewel)
            Rectangle {
                id: cabochonRect
                anchors.centerIn: parent
                anchors.verticalCenterOffset: leftOrnament.pressed ? 1 : 0
                Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
                width: 14; height: 14
                radius: 7
                // Qt.tint blends a slice of the same lamp color amberWash washes the
                // titlebar with, so the jewel and the titlebar glow read as one lit
                // object rather than a static jewel with an independent glow nearby.
                property color cabochonTop: isFocused
                    ? Qt.tint(tAmethShine, Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, 0.18))
                    : Qt.darker(tAmethShine, 1.4)
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
            Rectangle {   // placed by the shell's one light (ShellLight)
                x: leftOrnament.width / 2 + ShellLight.lx * 5.5 - width / 2
                y: leftOrnament.height / 2 + ShellLight.ly * 5.5 - height / 2 + (leftOrnament.pressed ? 1 : 0)
                width: 4; height: 3
                radius: 1.5
                rotation: ShellLight.gradientTurn
                color: ShellLight.lt(leftOrnament.hovered ? 0.85 : 0.65)
                Behavior on y { NumberAnimation { duration: 90 } }
            }
            // etched glyph — matches TiffanyButton's Min/Max/Close labeling (leftOrnament was the
            // one titlebar button with no label at all). Small square: the semantic opposite of
            // Maximize's "□" (restore-to-grid vs. grow-to-full).
            Text {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 1 + (leftOrnament.pressed ? 1 : 0)
                text: "▫"
                color: mk.shadeA(0.62)
                font.pixelSize: theme.fontSmall
                font.bold: true
                font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
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

            // lead-came backdrop — shows through every 1px gap. Real lead came has a
            // rounded profile that catches a highlight along its length; the seams
            // here are too thin (1px) to carry a separate highlight line of their
            // own, so the catch-light is applied to this one shared backdrop instead
            // — same top-down light logic as the panes' own upper sheen below, so
            // every seam shows a faint bright catch near the top, dark below.
            Rectangle {
                anchors.fill: parent
                radius: 1
                gradient: Gradient {
                    GradientStop { position: 0.00; color: Qt.lighter(tCame, 2.1) }
                    GradientStop { position: 0.15; color: tCame }
                    GradientStop { position: 1.00; color: tCame }
                }
            }

            // 10 jewel panes in a symmetric pattern
            Row {
                id: paneRow
                anchors.fill: parent
                anchors.margins: 1
                // Lead came has a profile (2026-09-25, #31): 3px seams — dark lead
                // either side of a 1px rounded crown that catches the light
                spacing: 3
                Repeater {
                    id: paneRep
                    model: frame.paneColors
                    /* was: [
                        frame.tEmerald,  frame.tAmber,    frame.tRuby,
                        frame.tAmethyst, frame.tSapphire, frame.tHoney,
                        frame.tAmethyst, frame.tRuby,     frame.tAmber,
                        frame.tEmerald
                    ] — same list, now frame.paneColors so the cast light can share it */
                    delegate: Rectangle {
                        width: (paneRow.width - 27) / 10
                        height: paneRow.height
                        gradient: Gradient {
                            GradientStop { position: 0.00; color: Qt.lighter(modelData, 1.35) }
                            GradientStop { position: 0.40; color: modelData }
                            GradientStop { position: 1.00; color: Qt.darker(modelData, 1.55) }
                        }
                        opacity: isFocused ? 0.96 : 0.55
                        Behavior on opacity { NumberAnimation { duration: 240 } }

                        // Cathedral glass (2026-09-25, BEAUTIFY-NEXT #28): rolled glass is
                        // never flat — one side of the sheet rolled a little thicker, faint
                        // rolled streaks, a seed bubble or two of trapped air. Seeded per
                        // pane (frame._jit, Mulberry32), so it never shimmers; clipped to the
                        // pane so the came and solder around it stay crisp. Streak and bubble
                        // highlights come from the shell's one light. Static.
                        Item {
                            id: cath
                            anchors.fill: parent
                            clip: true
                            readonly property int  paneIdx: index
                            readonly property real j0: frame._jit(index, 101)
                            readonly property real j1: frame._jit(index, 202)
                            readonly property real j2: frame._jit(index, 303)
                            readonly property real j3: frame._jit(index, 404)
                            // thickness drift: darker toward the thicker side, fading out
                            Rectangle {
                                anchors.fill: parent
                                gradient: Gradient {
                                    orientation: Gradient.Horizontal
                                    GradientStop { position: 0.0; color: mk.shadeA(cath.j0 < 0.5 ? 0.18 : 0.0) }
                                    GradientStop { position: 0.3 + 0.4 * cath.j1; color: mk.shadeA(0.0) }
                                    GradientStop { position: 1.0; color: mk.shadeA(cath.j0 < 0.5 ? 0.0 : 0.18) }
                                }
                            }
                            // rolled streaks: two hairlines at a slight lean, bright mid-pane only
                            Repeater {
                                model: 2
                                Rectangle {
                                    readonly property real s: frame._jit(cath.paneIdx * 5 + index, 505)
                                    x: cath.width * (0.14 + 0.72 * s)
                                    y: -4; width: 1; height: cath.height + 8
                                    rotation: (s - 0.5) * 18
                                    antialiasing: true
                                    gradient: Gradient {
                                        GradientStop { position: 0.0; color: ShellLight.lt(0.0) }
                                        GradientStop { position: 0.45; color: ShellLight.lt(0.10 + 0.08 * cath.j3) }
                                        GradientStop { position: 1.0; color: ShellLight.lt(0.0) }
                                    }
                                }
                            }
                            // seed bubbles: a faint clear disc with a lit point toward the light
                            Repeater {
                                model: cath.j2 > 0.3 ? (cath.j3 > 0.72 ? 2 : 1) : 0
                                Item {
                                    readonly property real s: frame._jit(cath.paneIdx * 3 + index, 606)
                                    readonly property real t: frame._jit(cath.paneIdx * 3 + index, 707)
                                    readonly property real d: s > 0.6 ? 3 : 2
                                    x: Math.round(cath.width * (0.12 + 0.76 * s))
                                    y: Math.round(cath.height * (0.35 + 0.45 * t))
                                    width: d; height: d
                                    Rectangle {
                                        anchors.fill: parent; radius: width / 2
                                        color: Qt.rgba(1, 1, 1, 0.10)
                                        border.width: 1; border.color: mk.shadeA(0.12)
                                    }
                                    Rectangle {
                                        width: 1; height: 1
                                        x: Math.round(parent.width / 2 + ShellLight.lx * parent.width * 0.3 - 0.5)
                                        y: Math.round(parent.height / 2 + ShellLight.ly * parent.height * 0.3 - 0.5)
                                        color: ShellLight.lt(0.75)
                                    }
                                }
                            }
                        }

                        // upper sheen — wet (2026-09-25): holds, then a soft lip
                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: parent.height * 0.46
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: ShellLight.lt(0.32) }
                                GradientStop { position: 0.6; color: ShellLight.lt(0.20) }
                                GradientStop { position: 1.0; color: ShellLight.lt(0.0) }
                            }
                        }
                        // came crown in the seam to this pane's left: the rounded top
                        // of the lead catches light along its length, brightest up top
                        Rectangle {
                            visible: index > 0
                            x: -2; width: 1; height: parent.height
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(frame.tSolder.r, frame.tSolder.g, frame.tSolder.b, 0.70) }
                                GradientStop { position: 1.0; color: Qt.rgba(frame.tSolder.r, frame.tSolder.g, frame.tSolder.b, 0.18) }
                            }
                        }
                        // solder joints where this seam meets the top and bottom came
                        Rectangle {
                            visible: index > 0
                            x: -3; y: -1; width: 3; height: 3; radius: 1.5
                            color: frame.tSolder
                        }
                        Rectangle {
                            visible: index > 0
                            x: -3; y: parent.height - 2; width: 3; height: 3; radius: 1.5
                            color: Qt.darker(frame.tSolder, 1.35)
                        }
                        // tiny bottom shadow
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 1
                            color: mk.shadeA(0.45)
                        }
                    }
                }
            }

            // ── Wet-glass motion glint on the jewel panes — same physically-derived
            // technique as NCDEGlassSurface.qml's glintSource (Fresnel-Schlick
            // reflectance + Beer-Lambert falloff, epilepsy-safe timing), ported here
            // rather than reinvented. glassBand already has clip:true so, unlike
            // GlassSurface's pill/rounded shapes, no separate mask layer is needed —
            // this band is a plain rect. One-shot sweep on gaining focus: the frame's
            // own "sunlight catches the glass as you focus this window" moment.
            Rectangle {
                id: titlebarGlint
                readonly property real thetaMax: 1.396   // 80° — grazing limit of the sweep
                property real theta: -thetaMax
                readonly property real cosT: Math.cos(theta)
                readonly property real sweepPos: 0.5 + 0.5 * Math.tan(theta) / Math.tan(thetaMax)
                readonly property real stretch: Math.min(2.5, 1 / Math.max(0.18, cosT))
                width: glassBand.width * 0.12 * stretch
                height: glassBand.height * 1.4
                x: -width + sweepPos * (glassBand.width + width)
                y: -glassBand.height * 0.2
                visible: animPolicy.decorative && !animPolicy.screenIdle
                opacity: {
                    var r0 = 0.04
                    var R    = r0 + (1 - r0) * Math.pow(1 - cosT, 5)
                    var rMax = r0 + (1 - r0) * Math.pow(1 - Math.cos(thetaMax), 5)
                    return 0.10 + 0.48 * (R - r0) / (rMax - r0)
                }
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.000; color: Qt.rgba(1,1,1,0.00)  }
                    GradientStop { position: 0.125; color: Qt.rgba(1,1,1,0.05)  }
                    GradientStop { position: 0.250; color: Qt.rgba(1,1,1,0.135) }
                    GradientStop { position: 0.375; color: Qt.rgba(1,1,1,0.368) }
                    GradientStop { position: 0.500; color: Qt.rgba(1,1,1,1.00)  }
                    GradientStop { position: 0.625; color: Qt.rgba(1,1,1,0.368) }
                    GradientStop { position: 0.750; color: Qt.rgba(1,1,1,0.135) }
                    GradientStop { position: 0.875; color: Qt.rgba(1,1,1,0.05)  }
                    GradientStop { position: 1.000; color: Qt.rgba(1,1,1,0.00)  }
                }
            }
            Connections {
                target: frame
                function onIsFocusedChanged() {
                    if (frame.isFocused && animPolicy.decorative) { titlebarGlintSweep.restart(); foilRun.restart() }
                }
            }
            SequentialAnimation {
                id: titlebarGlintSweep
                NumberAnimation { target: titlebarGlint; property: "theta"; from: -titlebarGlint.thetaMax; to: titlebarGlint.thetaMax; duration: 900 }
            }

            // title text — shadow + main
            // Vista caption glow (2026-09-26, operator-approved #3): a soft halo of the
            // palette's shade behind the title, so it reads on any glass — replaces the
            // old hard 1 px black drop shadow.
            Text {
                anchors.centerIn: parent
                text: frame.windowTitle
                color: mk.shade
                font.pixelSize: theme.fontMedium
                font.bold: true
                font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                elide: Text.ElideRight
                width: glassBand.width - 10
                horizontalAlignment: Text.AlignHCenter
                opacity: isFocused ? 0.95 : 0.6
                layer.enabled: true
                layer.effect: MultiEffect { blurEnabled: true; blur: 0.9; blurMax: 14; brightness: -0.1 }
            }
            Text {
                anchors.centerIn: parent
                text: frame.windowTitle
                color: isFocused ? tCream : Qt.rgba(tCream.r, tCream.g, tCream.b, 0.66)
                font.pixelSize: theme.fontMedium
                font.bold: true
                font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                elide: Text.ElideRight
                width: glassBand.width - 10
                horizontalAlignment: Text.AlignHCenter
                Behavior on color { ColorAnimation { duration: 220 } }
            }
        }

        // -- STAINED GLASS CASTS COLOURED LIGHT (2026-09-25, BEAUTIFY-NEXT #29) --
        // Light through each pane lands on the bronze just below it as a soft wash
        // of that pane's colour, fading to nothing before the window's edge. Each
        // wash follows its own pane's lit/unlit opacity (no animation of its own)
        // and the shell's light (warmer/softer at dusk). Rounded top corners, so the
        // wash never ends in a square cut.
        Row {
            id: paneCast
            anchors.left: glassBand.left;   anchors.leftMargin: 1
            anchors.right: glassBand.right; anchors.rightMargin: 1
            anchors.top: glassBand.bottom
            height: 5
            spacing: 3
            z: 1
            Repeater {
                model: frame.paneColors
                delegate: Rectangle {
                    width: (paneCast.width - 27) / 10
                    height: paneCast.height
                    radius: 2
                    readonly property Item pane: paneRep.count > index ? paneRep.itemAt(index) : null
                    opacity: pane ? pane.opacity : 0
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: Qt.rgba(modelData.r, modelData.g, modelData.b, 0.50 * ShellLight.strength) }
                        GradientStop { position: 1.0; color: Qt.rgba(modelData.r, modelData.g, modelData.b, 0.0) }
                    }
                }
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
            // Fluid drag (2026-09-26, operator: "the drag and move could be more fluid"):
            // a mouse reports hundreds of moves a second; each used to become its own
            // window move + stack check, queueing faster than the screen draws. Now the
            // latest cursor position is kept and applied ONCE per frame — still 1:1
            // with the cursor, never behind a backlog.
            property bool pendingMove: false
            onCentroidChanged: { if (active) { pendingMove = true; if (!dragPump.running) dragPump.start() } }
        }
        // once per render-loop frame (anim-policy.md §1), not a 16 ms timer of its own
        FrameAnimation {
            id: dragPump
            onTriggered: {
                if (!titleDrag.active) { stop(); return }
                if (!titleDrag.pendingMove) return
                titleDrag.pendingMove = false
                windowMgr.moveWindow(frame.winId,
                    titleDrag.startWinX + Math.round(windowMgr.mouseX - titleDrag.startGlobalX),
                    titleDrag.startWinY + Math.round(windowMgr.mouseY - titleDrag.startGlobalY))
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
                orientation: Gradient.Horizontal   // a rounded rod: ridge highlight off-centre
                GradientStop { position: 0.00; color: tBronzeDark }
                GradientStop { position: 0.14; color: tBronze }
                GradientStop { position: 0.34; color: tMetalHi }
                GradientStop { position: 0.50; color: tBronzeWarm }
                GradientStop { position: 0.78; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        Repeater {   // brushed grain, running down the rail
            model: Math.floor(leftSide.width / 2)
            Rectangle {
                x: index * 2; width: 1; height: leftSide.height
                color: index % 2 ? mk.shadeA(0.07) : Qt.rgba(1, 1, 1, 0.04)
            }
        }
        // light from the title band's end pane falls down the top of this rail
        // (2026-09-25, #29): a wash of its colour, gone within 40px, lit as the pane is
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right
            height: Math.min(40, parent.height)
            readonly property Item pane: paneRep.count > 0 ? paneRep.itemAt(0) : null
            opacity: pane ? pane.opacity : 0
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(frame.paneColors[0].r, frame.paneColors[0].g, frame.paneColors[0].b, 0.38 * ShellLight.strength) }
                GradientStop { position: 1.0; color: Qt.rgba(frame.paneColors[0].r, frame.paneColors[0].g, frame.paneColors[0].b, 0.0) }
            }
        }
        // verdigris in the recesses where this rail meets the title and bottom bars
        // (2026-09-25, #32): patina gathers at the joint and thins out along the rod
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
            height: Math.min(16, parent.height / 2)
            gradient: Gradient {
                GradientStop { position: 0.0; color: frame.patina(0.42) }
                GradientStop { position: 1.0; color: frame.patina(0.0) }
            }
        }
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            height: Math.min(16, parent.height / 2)
            gradient: Gradient {
                GradientStop { position: 0.0; color: frame.patina(0.0) }
                GradientStop { position: 1.0; color: frame.patina(0.42) }
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
                // 2026-09-25: one light (ShellLight) — this rod catches it on the
                // SAME side as the left rod; it used to be a mirror, as if each rail
                // had its own lamp
                orientation: Gradient.Horizontal
                GradientStop { position: 0.00; color: tBronzeDark }
                GradientStop { position: 0.14; color: tBronze }
                GradientStop { position: 0.34; color: tMetalHi }
                GradientStop { position: 0.50; color: tBronzeWarm }
                GradientStop { position: 0.78; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        Repeater {
            model: Math.floor(rightSide.width / 2)
            Rectangle {
                x: index * 2; width: 1; height: rightSide.height
                color: index % 2 ? mk.shadeA(0.07) : Qt.rgba(1, 1, 1, 0.04)
            }
        }
        // light from the title band's end pane falls down the top of this rail
        // (2026-09-25, #29): a wash of its colour, gone within 40px, lit as the pane is
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right
            height: Math.min(40, parent.height)
            readonly property Item pane: paneRep.count > 9 ? paneRep.itemAt(9) : null
            opacity: pane ? pane.opacity : 0
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(frame.paneColors[9].r, frame.paneColors[9].g, frame.paneColors[9].b, 0.38 * ShellLight.strength) }
                GradientStop { position: 1.0; color: Qt.rgba(frame.paneColors[9].r, frame.paneColors[9].g, frame.paneColors[9].b, 0.0) }
            }
        }
        // verdigris in the recesses where this rail meets the title and bottom bars
        // (2026-09-25, #32): patina gathers at the joint and thins out along the rod
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
            height: Math.min(16, parent.height / 2)
            gradient: Gradient {
                GradientStop { position: 0.0; color: frame.patina(0.42) }
                GradientStop { position: 1.0; color: frame.patina(0.0) }
            }
        }
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            height: Math.min(16, parent.height / 2)
            gradient: Gradient {
                GradientStop { position: 0.0; color: frame.patina(0.0) }
                GradientStop { position: 1.0; color: frame.patina(0.42) }
            }
        }
        Rectangle { anchors.left:  parent.left;  width: 1; height: parent.height; color: tCame }
        Rectangle { anchors.right: parent.right; width: 1; height: parent.height; color: tCame }
        Rectangle { x: 4; width: 1; height: parent.height; color: tBronzeShine; opacity: 0.35 }   // lit edge, as the left rod

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
                GradientStop { position: 0.00; color: tBronze }
                GradientStop { position: 0.10; color: tMetalEdge }
                GradientStop { position: 0.20; color: tBronzeWarm }
                GradientStop { position: 0.38; color: tMetalHi }
                GradientStop { position: 0.55; color: tBronzeMid }
                GradientStop { position: 0.82; color: tBronze }
                GradientStop { position: 1.00; color: tBronzeDark }
            }
        }
        Repeater {   // brushed grain
            model: Math.floor(bottomBar.height / 2)
            Rectangle {
                y: index * 2; width: bottomBar.width; height: 1
                color: index % 2 ? mk.shadeA(0.07) : Qt.rgba(1, 1, 1, 0.05)
            }
        }
        // verdigris at both ends, where the side rails meet this bar (2026-09-25, #32):
        // a soft patina fading inward, with a few seeded specks of heavier crust
        Repeater {
            model: 2
            Item {
                readonly property bool isLeft: index === 0
                anchors.top: parent.top; anchors.topMargin: 1
                anchors.left:  isLeft ? parent.left  : undefined
                anchors.right: isLeft ? undefined    : parent.right
                width: 30; height: 6
                Rectangle {
                    anchors.fill: parent
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: frame.patina(isLeft ? 0.38 : 0.0) }
                        GradientStop { position: 1.0; color: frame.patina(isLeft ? 0.0 : 0.38) }
                    }
                }
                Repeater {
                    model: 4
                    Rectangle {
                        readonly property real s: frame._jit(index + (parent.isLeft ? 0 : 8) + ("top" === "top" ? 16 : 0), 808)
                        readonly property real t: frame._jit(index + (parent.isLeft ? 0 : 8) + ("top" === "top" ? 16 : 0), 909)
                        width: s > 0.55 ? 2 : 1; height: width; radius: width / 2
                        x: parent.isLeft ? Math.round(1 + 12 * s) : Math.round(parent.width - 2 - 12 * s)
                        y: Math.round((parent.height - height) * t)
                        color: frame.patina(0.35 + 0.25 * t)
                    }
                }
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
                spacing: 3   // profiled came, as the title band (2026-09-25)
                Repeater {
                    id: mosaicTiles
                    model: Math.max(0, Math.floor((leadedBand.width - 2) / 19))
                    delegate: Rectangle {
                        readonly property var cycle: [
                            frame.tAmber, frame.tEmerald, frame.tRuby,
                            frame.tSapphire, frame.tAmethyst, frame.tHoney
                        ]
                        // each tile set at its own tilt (#34): a seeded brightness step
                        readonly property real tilt: frame._jit(index, 7)
                        property color cc: Qt.lighter(cycle[index % cycle.length], 0.90 + 0.22 * tilt)
                        // tiles share the leftover width, so the band ends on a tile,
                        // not on a bare strip of lead
                        width: mosaicTiles.count > 0 ? (leadedBand.width - 2 - 3 * (mosaicTiles.count - 1)) / mosaicTiles.count : 16
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
                                // sheen strength follows the tile's tilt, so the band glitters
                                GradientStop { position: 0.0; color: ShellLight.lt(0.24 + 0.30 * frame._jit(index, 19)) }
                                GradientStop { position: 1.0; color: ShellLight.lt(0.0) }
                            }
                        }
                        // came crown + solder joints in the seam to this tile's left
                        Rectangle {
                            visible: index > 0
                            x: -2; width: 1; height: parent.height
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(frame.tSolder.r, frame.tSolder.g, frame.tSolder.b, 0.65) }
                                GradientStop { position: 1.0; color: Qt.rgba(frame.tSolder.r, frame.tSolder.g, frame.tSolder.b, 0.15) }
                            }
                        }
                        Rectangle {
                            visible: index > 0
                            x: -3; y: -1; width: 3; height: 3; radius: 1.5
                            color: frame.tSolder
                        }
                        Rectangle {
                            visible: index > 0
                            x: -3; y: parent.height - 2; width: 3; height: 3; radius: 1.5
                            color: Qt.darker(frame.tSolder, 1.35)
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
            // was an instant snap on focus change — every other glow layer in this
            // frame (outerGlow, crownGlow, cabochonTop, jewelTop) fades; amberWash was
            // the one holdout. Behavior on GradientStop.color IS supported by QtQuick
            // (Qt 5.5+); the old `Behavior on opacity` below was dead code — nothing
            // ever set amberWash.opacity, only these stop colors changed.
            GradientStop { position: 0.0; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, isFocused ? 0.42 : 0.12)
                           Behavior on color { ColorAnimation { duration: 300; easing.type: Easing.InOutCubic } } }
            GradientStop { position: 0.5; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, isFocused ? 0.12 : 0.04)
                           Behavior on color { ColorAnimation { duration: 300; easing.type: Easing.InOutCubic } } }
            GradientStop { position: 1.0; color: Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, 0.0) }
        }
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

        // Vista glow (2026-09-26, operator-approved #2): hovering a caption jewel
        // blooms a soft halo in the jewel's OWN colour behind its bezel — ruby glows
        // red, emerald green, sapphire blue — the way Vista's close button glowed.
        // Fades in 160 ms (the standard's reveal), tightens when pressed.
        Rectangle {
            id: bloom
            anchors.centerIn: parent
            width: btn.pressed ? 26 : 34; height: width; radius: width / 2
            color: Qt.tint(btn.jewelBase, Qt.rgba(btn.jewelShine.r, btn.jewelShine.g, btn.jewelShine.b, 0.45))
            opacity: btn.hovered && isFocused ? (btn.pressed ? 0.95 : 0.8) : 0
            visible: opacity > 0.01
            Behavior on opacity { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }
            Behavior on width { NumberAnimation { duration: 90 } }
            layer.enabled: visible
            layer.effect: MultiEffect { blurEnabled: true; blur: 1.0; blurMax: 12 }
        }

        // brass bezel (a circle: turned so its shine faces the shell's light)
        Rectangle {
            anchors.fill: parent
            radius: width / 2
            rotation: ShellLight.gradientTurn
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
        // verdigris in the socket (2026-09-25, #32): on the side the light never polishes
        Rectangle {
            anchors.centerIn: parent
            width: parent.width - 4; height: parent.height - 4
            radius: width / 2
            rotation: ShellLight.gradientTurn
            gradient: Gradient {
                GradientStop { position: 0.00; color: frame.patina(0.0) }
                GradientStop { position: 0.55; color: frame.patina(0.0) }
                GradientStop { position: 1.00; color: frame.patina(0.50) }
            }
        }

        // socket shadow — reads as a jewel set INTO the bronze rather than sitting
        // flat on top of it. Same small-offset-blur technique as the outer glow
        // layers elsewhere in this file, just tiny and local to one jewel.
        Rectangle {
            anchors.centerIn: parent
            // falls away from the light
            anchors.horizontalCenterOffset: -ShellLight.lx * 1.5
            anchors.verticalCenterOffset: -ShellLight.ly * 1.5
            width: 15; height: 15; radius: 7.5
            color: mk.shadeA(0.5)
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.4; blurMax: 6 }
        }
        // the jewel itself
        // dims on unfocus like every other jewel/glow surface in this frame
        // (leftOrnament's cabochonTop, outerGlow, crownGlow, the lamp pulse) —
        // TiffanyButton was the one holdout that stayed full-brightness.
        // Qt.tint blends a slice of the same lamp color amberWash washes the titlebar
        // with, matching leftOrnament's cabochonTop treatment — the whole titlebar
        // reads as one lit object, not jewels with an independent glow nearby.
        property color jewelTop: isFocused
            ? Qt.tint(btn.jewelShine, Qt.rgba(frame.lampCol.r, frame.lampCol.g, frame.lampCol.b, 0.18))
            : Qt.darker(btn.jewelShine, 1.4)
        Behavior on jewelTop { ColorAnimation { duration: 240 } }
        Rectangle {
            id: jewel
            anchors.centerIn: parent
            anchors.verticalCenterOffset: btn.pressed ? 1 : 0
            Behavior on anchors.verticalCenterOffset { NumberAnimation { duration: 90 } }
            width: 14
            height: 14
            radius: 7
            gradient: Gradient {
                GradientStop { position: 0.00; color: btn.hovered ? Qt.lighter(btn.jewelTop, 1.22) : btn.jewelTop }
                GradientStop { position: 0.45; color: btn.hovered ? Qt.lighter(btn.jewelBase, 1.12) : btn.jewelBase }
                GradientStop { position: 1.00; color: btn.jewelDeep }
            }
            border.color: tBronzeShine
            border.width: 1
            scale: btn.hovered ? 1.08 : 1.0
            Behavior on scale { NumberAnimation { duration: 110; easing.type: Easing.OutCubic } }
        }
        // glint
        Rectangle {   // placed by the shell's one light (ShellLight)
            x: btn.width / 2 + ShellLight.lx * 4.5 - width / 2
            y: btn.height / 2 + ShellLight.ly * 4.5 - height / 2 + (btn.pressed ? 1 : 0)
            width: 4; height: 3
            radius: 1.5
            rotation: ShellLight.gradientTurn
            color: ShellLight.lt(btn.hovered ? 0.85 : 0.62)
            Behavior on y { NumberAnimation { duration: 90 } }
        }
        // etched glyph
        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 1 + (btn.pressed ? 1 : 0)
            text: btn.glyphText
            color: mk.shadeA(0.62)
            font.pixelSize: theme.fontSmall
            font.bold: true
            font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
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
