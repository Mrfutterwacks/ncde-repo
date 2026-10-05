// NCDEGlassSurface.qml — Aero-style frosted pill background (shell-wide glass).
// Full blur pipeline: ShaderEffectSource → MultiEffect blur → [opt dark base]
// → tint → shadow/cavity → specular → border → outer glow halo → rim → drop-shadow lift.
// Shadow/cavity added 2026-09-23: the missing "3rd dimension" layer flagged
// independently three times (operator's stained-glass depth comment, his own
// 5-Layer Glass Framework, and a Windows-7-Aero realism checklist he checked
// against this file) — without it, distinct accent hues read as flat/
// indistinguishable since nothing grounds the surface with real shading.
// NCDEEngine colors (ncde.accent / ncde.glow) drive tint/edge/glow — Theme
// from Wallpaper recolors all surfaces automatically.
//
// Usage:
//   NCDEGlassSurface {
//       anchors.fill: parent
//       backgroundSource: wallpaperItem   // Item in the same Window to blur
//       cornerRadius: height / 2          // full pill
//   }
//
// baseDarkness: 0 = pure glass (panels, dock). Menus opt in (~0.6) for a
// solid "stained glass at night" card that reads opaque, not see-through.
//
// hideSource MUST stay false: it only hides the sampled item, never other
// windows — but flipping it true on a shared source erases content on screen.

import QtQuick
import QtQuick.Effects
import "glass-modes.js" as GlassModes
import "ncde-color.js" as Col

Item {
    id: surface

    property real  cornerRadius:     height / 2
    property Item  backgroundSource: null

    // ── Iris Chroma baseline + Filigree override (2026-09-23) ────────────
    // Iris Chroma drives the engine (ncde.accent/glow); Filigree's per-surface
    // glass layers on top. Consumers pass surfaceKey + the ncde.surfaceGlass()
    // map they already refresh on themeChanged; resolution lives HERE instead
    // of being copy-pasted into 8 panels. `custom` comes from glass-modes.js
    // (Filigree's "Follow Iris palette / Custom" choice) — replaces the old
    // !ncde.presetActive gate, which silently disabled Filigree whenever an
    // Iris palette was active (i.e. always, since main.qml reapplies it).
    // Reading `glass` inside the binding makes it re-evaluate on every refresh.
    property string surfaceKey: ""
    property var    glass: null
    readonly property bool custom: { glass; return GlassModes.isCustom(surfaceKey) }
    function _g(field) {
        return (custom && glass && glass[field] !== undefined && glass[field] !== "") ? glass[field] : undefined
    }
    readonly property color resolvedTint: {
        var t = surface._g("tint")
        if (t === undefined) return Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.18)
        var c = Qt.color(t); return Qt.rgba(c.r, c.g, c.b, 0.18)
    }
    readonly property color resolvedEdge: {
        var b = surface._g("border")
        var c = b === undefined ? ncde.glow : Qt.color(b)
        return Qt.rgba(c.r, c.g, c.b, 0.85)
    }
    readonly property color resolvedGlow: { var g = surface._g("glowColor"); return g === undefined ? ncde.glow : Qt.color(g) }

    // ── Palette light and shade (2026-09-24, operator: the palette is universal) ──
    // The shadow/cavity, night base, specular, catch-light, edge hairlines and
    // inner rim used to be fixed: a violet-black rgba(0.07,0.05,0.10) and pure
    // white on every palette, so a green or crimson palette got purple shadows
    // and cold white shine. Now they are the palette's own dark and light:
    //   shadeTone = the panel ground at L 5, chroma capped at 8 (still reads as
    //               neutral shadow, never a second coloured tint; never #000)
    //   lightTone = the glow colour at L 97, chroma capped at 6 (white light
    //               with a breath of the palette in it, like light through the glass)
    // Alphas are unchanged; only the RGB comes from the palette. The moving
    // glint sweep keeps its own colour (no animation changes).
    readonly property color shadeTone: Col.tone((typeof ncde !== "undefined" && ncde.panelBg !== undefined) ? ncde.panelBg : Qt.rgba(0.07, 0.05, 0.10, 1), 5, 8)
    // 2026-09-25: warmed by a low sun / the night lamp, and softened near the horizon (ShellLight)
    readonly property color lightTone: ShellLight.warmed(Col.tone(resolvedGlow, 97, 6))
    function _sh(a) { return Qt.rgba(shadeTone.r, shadeTone.g, shadeTone.b, a) }
    function _lt(a) { return Qt.rgba(lightTone.r, lightTone.g, lightTone.b, a * ShellLight.strength) }

    property color tint:     resolvedTint
    property color edge:     resolvedEdge
    property color glowRim:  resolvedGlow
    property color glowHalo: resolvedGlow
    // Intensity was the one Filigree control that always worked — keep honouring it
    // in both modes so nobody's saved intensity changes under them.
    property real  glowA:    (glass && glass["glow"] !== undefined) ? glass["glow"] : 0.70
    // Shine = specular strength (0.5 = the tuned default look). It used to be
    // wired to tint alpha, so the "Shine" slider never touched the shine.
    property real  shine:    { var s = surface._g("shine"); return s === undefined ? 0.5 : s }
    property real  blurPx:   28
    // ── Aero composition (2026-09-26, operator: "research how my glass should look
    // compared to Aero / Win 7 … I like my glass but it could be polished more").
    // The Windows 7 DWM glass shader (disassembled in DWMBlurGlass #195) is
    //   colour×colourBalance + greyscale(blur)×afterglow×afterglowBalance + blur×blurBalance
    // NCDE had the colour and the blur; the AFTERGLOW term was missing — it is what
    // makes Aero read as coloured glass with light passing through (bright things
    // behind it glow in the glass's colour, dark things stay dark) instead of a
    // tinted film. afterglow 0 = the old look. reflection = Aero's glass-reflection
    // streaks, anchored to the SCREEN (each surface shows its slice of one shared
    // reflection) and laid along the shell's one light instead of a fixed diagonal.
    property real  afterglow:  { var v = surface._g("afterglow");  return v === undefined ? 0.38 : v }
    property real  reflection: { var v = surface._g("reflection"); return v === undefined ? 0.11 : v }
    // 0 = specular spans full width (panels); 0.08 = inset 8% each side (dock pill)
    property real  specularInset: 0.08
    // 0 = pure glass · >0 = solid dark base behind the tint (menus use ~0.6)
    property real  baseDarkness: 0.0
    // true = the moving glint sweeps the vertical axis instead of horizontal —
    // dock's pill is narrow/tall enough that a left-right sweep barely reads.
    property bool  glintVertical: false
    // true = outer glow halo gets the same MultiEffect blur MotifFrame's window-chrome
    // outerGlow layer uses (soft luminous band) instead of the default crisp double-ring
    // border. Opt-in, default false — every existing consumer's look is unchanged; only
    // callers that explicitly want the "ported" MotifFrame glow set this. No animation/
    // pulse added — static blur only (lampPulse-style infinite pulsing is window-chrome-
    // scale risk, not appropriate ported onto full-width/persistent shell furniture).
    property bool  glowBlurred: false
    // Bound by Dock/TopPanel/BottomPanel to their own intellihide *Revealed flag.
    // Dock/panels are intellihide-driven, not cursor-driven: the glint plays one
    // automatic sweep whenever the surface slides into view. (Widgets are the
    // opposite — user-activated by mouse hover — see NCDEGlass2.qml.)
    property bool  revealPulse: false
    onRevealPulseChanged: if (revealPulse && animPolicy.decorative) glintSweep.restart()
    // Operator (2026-07-06): the sweep must ALSO play every time a maximized window
    // is unmaxed, even when the shell never had time to hide (revealPulse only fires
    // on an actual hidden→shown transition — the 2s hide timer means a quick
    // max→unmax produced none, so the glint seemed to play "only once"). Intellihide
    // bumps glintPulse each time coveringCount returns to zero. Still strictly
    // one-shot per event — identical sweep, identical epilepsy math (two grazing
    // flares per 900ms sweep, ≈1.1Hz, peak alpha 0.58).
    property int   glintPulse: 0
    onGlintPulseChanged: if (animPolicy.decorative) glintSweep.restart()
    // Ported from MotifFrame's window-chrome glow (2026-09-23): the same breathing
    // lamp-pulse + amber crown-cap + corner cabochons, opt-in via jewelGlow so the
    // widget panels (Clock/Space/Weather/Stats/Salon) and menus keep today's static
    // halo look unchanged. Dock/TopPanel/BottomPanel set jewelGlow: true.
    property bool  jewelGlow: false
    property color lampCol: (typeof ncde !== "undefined" && ncde.lamp !== undefined)
                             ? ncde.lamp : Qt.rgba(0.96, 0.74, 0.36, 1.0)

    // Shell furniture has no focus/blur state like a window — it's either
    // revealed (breathing) or hidden (intellihide already fades/slides it
    // off, so the pulse just idles at rest while unseen). Same 4s breath
    // MotifFrame uses when isFocused, gated by animPolicy so reduceMotion/
    // thermalPressure/screenIdle stop it exactly like every other ambient
    // NCDE effect (see epilepsy note on the glint sweep above).
    Item {
        id: lampPulse
        property real val: 0.30
        SequentialAnimation on val {
            running: surface.jewelGlow && animPolicy.decorative && !animPolicy.screenIdle
            loops: Animation.Infinite
            NumberAnimation { to: 0.55; duration: 2000; easing.type: Easing.InOutSine }
            NumberAnimation { to: 0.25; duration: 2000; easing.type: Easing.InOutSine }
        }
    }

    // ── Step 1: Sample the background Item into a texture ────────────────
    ShaderEffectSource {
        id: bgSource
        anchors.fill: parent
        sourceItem: surface.backgroundSource
        // Position-aware sourceRect: each surface samples the wallpaper region
        // directly behind it, regardless of where it sits in the window.
        sourceRect: {
            if (!surface.backgroundSource || !surface.backgroundSource.parent)
                return Qt.rect(0, 0, 0, 0)
            var bx = surface.backgroundSource.x
            var by = surface.backgroundSource.y
            var pos = surface.mapToItem(surface.backgroundSource.parent, 0, 0)
            return Qt.rect(pos.x - bx, pos.y - by, surface.width, surface.height)
        }
        // Moksha redraw-on-change: sample the (static) wallpaper ONCE and cache it, instead of
        // re-sampling + re-blurring an unchanging image every frame. Pixel-identical: re-sample only
        // when the sampled pixels can actually change (geometry/position, wallpaper Item swap, or the
        // wallpaper finishing a (re)load). [efficiency fix #2 — VISUALLY VERIFY on panel reveal + wallpaper swap]
        live: false
        recursive: false      // never sample our own output
        hideSource: false     // never hide the source
        visible: false
        Component.onCompleted: scheduleUpdate()
        Connections {
            target: surface
            function onWidthChanged()            { bgSource.scheduleUpdate() }
            function onHeightChanged()           { bgSource.scheduleUpdate() }
            function onXChanged()                { bgSource.scheduleUpdate() }
            function onYChanged()                { bgSource.scheduleUpdate() }
            function onBackgroundSourceChanged() { bgSource.scheduleUpdate() }
        }
        Connections {
            target: surface.backgroundSource
            ignoreUnknownSignals: true
            function onStatusChanged() { Qt.callLater(bgSource.scheduleUpdate) }   // wallpaper finished (re)loading
        }
    }

    // ── Step 2: Blur the sampled texture, masked to the pill shape ───────
    MultiEffect {
        anchors.fill: parent
        source: bgSource
        blurEnabled: true
        blur: 1.0
        blurMax: 64
        blurMultiplier: Math.max(0, Math.min(1.0, surface.blurPx / 64))
        // Dynamic saturation ("Color Intensity", 2026-09-23): heavier blur
        // desaturates/washes out the sampled backdrop more, so punch the
        // saturation back up as blur increases — otherwise more-blurred
        // surfaces (higher blurPx) read progressively milkier/greyer than
        // lightly-blurred ones instead of staying visually consistent.
        saturation: 0.7 + blurMultiplier * 0.5
        maskEnabled: true
        maskSpreadAtMin: 0.0
        maskSource: pillMask
    }

    // ── Step 2b: Aero afterglow — the blurred backdrop's LIGHT, in the glass colour ──
    // greyscale(blur) × glow: MultiEffect colorization maps luminance onto one colour,
    // which is exactly Aero's afterglow term. Static: the backdrop is sampled once.
    MultiEffect {
        anchors.fill: parent
        visible: surface.afterglow > 0.001
        opacity: surface.afterglow
        source: bgSource
        blurEnabled: true
        blur: 1.0
        blurMax: 64
        blurMultiplier: Math.max(0, Math.min(1.0, surface.blurPx / 64))
        saturation: -1.0
        colorization: 1.0
        colorizationColor: Col.tone(surface.glowRim, 72, 60)
        brightness: 0.06
        maskEnabled: true
        maskSpreadAtMin: 0.0
        maskSource: pillMask
    }
    // ── Pill mask — source for blur mask + glow/shadow passes ────────────
    Item {
        id: pillMask
        anchors.fill: parent
        visible: false
        layer.enabled: true
        Rectangle {
            anchors.fill: parent
            radius: surface.cornerRadius
            color: "white"
        }
    }

    // ── One shape for every inner layer (2026-09-24) ─────────────────────
    // Operator: "layers all not being the same shape — I can clearly see a
    // square sharp line outlining the dock, widgets and panels". The top/left
    // edge hairlines are 3px strips whose radius clamps to 1.5, so they ran
    // straight out past the rounded corners and drew a square corner; the
    // specular strip's clamped radius poked past pill ends the same way.
    // Every inner layer now renders into one texture masked by pillMask, the
    // same mask the blur and glint already use, so nothing inside the glass
    // can leave its outline. Static only: no motion added or retuned.
    Item {
        id: interior
        anchors.fill: parent
        layer.enabled: true
        layer.effect: MultiEffect {
            maskEnabled: true
            maskSource: pillMask
            maskThresholdMin: 0.0
            maskSpreadAtMin: 0.0     // same hard edge as the blur mask; a soft spread leaked the strips
        }

        // ── Dark "glass at night" base (opt-in) ──────────────────────────────
        // Sits over the blurred wallpaper, under the tint. Panels/dock leave this
        // off (baseDarkness 0); menus turn it on so the card reads solid.
        Rectangle {
            anchors.fill: parent
            radius: surface.cornerRadius
            visible: surface.baseDarkness > 0
            color: surface._sh(surface.baseDarkness)
        }

        // ── Accent tint over the blurred backdrop — 2-stop gradient, not flat ──
        // Real glass reads brighter near the top (where the specular below
        // catches) and cooler toward the bottom — same top-down light logic the
        // specular highlight already uses, just carried into the tint itself.
        // Same RGB as before at both stops, only the alpha varies, so this stays
        // exactly the color `surface.tint` was set to, just no longer flat.
        Rectangle {
            anchors.fill: parent
            radius: surface.cornerRadius
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: Qt.rgba(surface.tint.r, surface.tint.g, surface.tint.b, Math.min(1.0, surface.tint.a * 1.25))
                    Behavior on color { ColorAnimation { duration: 420; easing.type: Easing.InOutCubic } }
                }
                GradientStop {
                    position: 1.0
                    color: Qt.rgba(surface.tint.r, surface.tint.g, surface.tint.b, surface.tint.a * 0.75)
                    Behavior on color { ColorAnimation { duration: 420; easing.type: Easing.InOutCubic } }
                }
            }
        }

        // ── Aero glass reflection — screen-anchored streaks along the one light ──
        // One wide band and one narrow band per 1100 px, in screen space: a panel
        // at the top and the dock at the side show different slices of the SAME
        // reflection, as Aero's windows did. Repaints only when the surface's
        // screen position, size, the light or the palette change — never animated.
        Canvas {
            id: reflect
            anchors.fill: parent
            visible: surface.reflection > 0.001 && width > 0 && height > 0
            renderStrategy: Canvas.Cooperative
            property point _pos: Qt.point(0, 0)
            readonly property string sig: ShellLight.signature + "/" + surface.reflection + "/" + surface.lightTone
            onSigChanged: requestPaint()
            onWidthChanged: requestPaint()
            onHeightChanged: requestPaint()
            function _track() {
                var p = surface.mapToItem(null, 0, 0)
                if (Math.abs(p.x - _pos.x) > 0.5 || Math.abs(p.y - _pos.y) > 0.5) { _pos = p; requestPaint() }
            }
            Timer { interval: 700; running: reflect.visible && surface.visible; repeat: true; onTriggered: reflect._track() }
            Component.onCompleted: _track()
            onPaint: {
                var ctx = getContext("2d"); ctx.reset()
                var a = surface.reflection
                // streaks run ALONG the light: bands are perpendicular to (lx, ly)
                var ang = Math.atan2(ShellLight.ly, ShellLight.lx) + Math.PI / 2
                var ca = Math.cos(ang), sa = Math.sin(ang)
                var P = 1100, sx = _pos.x, sy = _pos.y
                // project the surface's corners onto the across-band axis (-sa, ca)
                var cs = [[0,0],[width,0],[0,height],[width,height]], lo = 1e9, hi = -1e9
                for (var i = 0; i < 4; i++) {
                    var u = -(cs[i][0] + sx) * sa + (cs[i][1] + sy) * ca
                    lo = Math.min(lo, u); hi = Math.max(hi, u)
                }
                var t = ShellLight.tone
                function col(k) { return "rgba(" + Math.round(t.r*255) + "," + Math.round(t.g*255) + "," + Math.round(t.b*255) + "," + (k * a * ShellLight.strength) + ")" }
                ctx.save()
                ctx.translate(-sx, -sy)
                ctx.rotate(ang)
                // after rotate, local y = across-band coordinate u
                var bands = [[0, 150, 1.0], [210, 34, 0.8]]   // [offset, width, strength]
                for (var n = Math.floor((lo - 400) / P); n * P < hi + 400; n++) {
                    for (var b = 0; b < bands.length; b++) {
                        var y0 = n * P + bands[b][0], w = bands[b][1]
                        if (y0 + w < lo || y0 > hi) continue
                        var g = ctx.createLinearGradient(0, y0, 0, y0 + w)
                        g.addColorStop(0.0, col(0)); g.addColorStop(0.5, col(bands[b][2])); g.addColorStop(1.0, col(0))
                        ctx.fillStyle = g
                        ctx.fillRect(-4000, y0, 8000, w)
                    }
                }
                ctx.restore()
            }
        }
        // ── Shadow/Cavity — bottom-anchored depth grounding, 2026-09-23 ──────
        // The gap behind "why do distinct accent colors all look the same/flat":
        // the tint gradient above only fades the SAME hue's alpha top-to-bottom —
        // it never actually darkens/desaturates toward a shadow tone, so nothing
        // gives the surface real thickness. This is deliberately hue-NEUTRAL (a
        // fixed dark charcoal/navy, matching the existing "glass at night" base's
        // rgba(0.07,0.05,0.10,...) tone — never pure black, per the avoid-pure-
        // black-shapes rule: light can't bounce off #000, it just reads as a
        // hole) so it reads as true cast shadow/depth under ANY accent color,
        // not a second colored tint layer competing with the first.
        // 2026-09-24: the fixed tone is now surface.shadeTone, the palette's own
        // ground at L 5 with chroma capped at 8: still near-neutral and never
        // black, but a green palette's shadow is a green-black, not violet.
        Rectangle {
            anchors.fill: parent
            radius: surface.cornerRadius
            gradient: Gradient {
                GradientStop { position: 0.0;  color: surface._sh(0.0) }
                GradientStop { position: 0.55; color: surface._sh(0.0) }
                GradientStop { position: 1.0;  color: surface._sh(0.28) }
            }
        }

        // ── Aero specular highlight — top "wet glass" strip ──────────────────
        // Peak raised + falloff narrowed vs. the original 0.34/0.60: Blinn-Phong's
        // specular term is (N·H)^shininess — a higher exponent gives a narrower,
        // brighter highlight (glossy/wet), a lower one a wide soft one (matte/dry).
        // Same curve, just pushed toward the "wet" end.
        Rectangle {
            anchors.top:         parent.top
            anchors.left:        parent.left
            anchors.right:       parent.right
            anchors.topMargin:   1
            // shifted toward the shell's one light (ShellLight, 2026-09-25)
            anchors.leftMargin:  parent.width * surface.specularInset * (1 + ShellLight.lx * 0.5)
            anchors.rightMargin: parent.width * surface.specularInset * (1 - ShellLight.lx * 0.5)
            height: parent.height * 0.38
            radius: surface.cornerRadius
            // shine 0.5 → 1.0× (the tuned look above), 0 → matte, 1 → 1.6× wet.
            opacity: Math.min(1.6, surface.shine * 2.0)
            Behavior on opacity { NumberAnimation { duration: 320; easing.type: Easing.InOutCubic } }
            // Wet shine (2026-09-25, operator: "a wet shine to all glass … more of a
            // liquid shine"): a film of liquid gives the reflection a MENISCUS — it
            // stays bright most of the way down, then ends on a crisp edge instead
            // of fading out. Same peak; the soft tail becomes that hard lip.
            gradient: Gradient {
                GradientStop { position: 0.00; color: surface._lt(0.48) }
                GradientStop { position: 0.30; color: surface._lt(0.22) }
                GradientStop { position: 0.50; color: surface._lt(0.14) }
                GradientStop { position: 0.62; color: surface._lt(0.03) }   // a soft lip, not a hard line
                GradientStop { position: 1.00; color: surface._lt(0.00) }
            }
        }

        // ── Wet refraction line — light that entered the lit top bends through the
        // glass's thickness and leaves as a thin bright line just inside the far
        // (bottom) edge: the second tell of liquid glass, after the meniscus.
        // Follows the Shine setting like the strip above. Static.
        // Right shape: the line stays inside the glass's own rounded outline, so the
        // mask never has to cut it (the dock's round foot is narrower near the
        // bottom than its straight sides). It spans 85% of the glass's width at
        // its own height, and fades to nothing at both ends.
        Rectangle {
            readonly property real _r: Math.min(surface.cornerRadius, surface.width / 2, surface.height / 2)
            readonly property real _yb: anchors.bottomMargin + height / 2
            readonly property real _half: surface.width / 2 - _r
                                          + (_yb >= _r ? _r : Math.sqrt(Math.max(0, _r * _r - (_r - _yb) * (_r - _yb))))
            readonly property real _m: Math.max(surface.width * Math.max(0.06, surface.specularInset),
                                                surface.width / 2 - 0.85 * _half)
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin:  _m
            anchors.rightMargin: _m
            anchors.bottomMargin: Math.max(2, Math.min(6, _r * 0.25))
            height: Math.max(2, Math.min(3, parent.height * 0.05))
            radius: height / 2
            opacity: Math.min(1.6, surface.shine * 2.0) * ((typeof settings !== "undefined" && settings.highContrast === true) ? 0.5 : 1.0)
            // fades out along its length: no ends, no corners (operator: no harsh lines)
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.00; color: surface._lt(0.00) }
                GradientStop { position: 0.30; color: surface._lt(0.16) }
                GradientStop { position: 0.70; color: surface._lt(0.16) }
                GradientStop { position: 1.00; color: surface._lt(0.00) }
            }
        }

        // ── Corner catch-light — the small soft highlight point real cut glass/
        // gems show where light concentrates at an edge, same upper-left light
        // source the specular strip above already implies. Same Rectangle +
        // MultiEffect-blur technique already used for the glint layers below,
        // not a new one.
        // 2026-09-25: it sits ON the rim where ShellLight strikes the corner, and
        // stays small. It used to be half the corner radius at 135°, so on the
        // dock's round cap (radius = half the dock's width) it was a 16px white
        // blob floating inside the cap above the first icon.
        Rectangle {
            readonly property real _r: Math.min(surface.cornerRadius, surface.width / 2, surface.height / 2)
            width: Math.max(4, Math.min(8, _r * 0.3))
            height: width
            x: _r + ShellLight.lx * Math.max(0, _r - width * 0.9) - width / 2
            y: _r + ShellLight.ly * Math.max(0, _r - width * 0.9) - height / 2
            radius: width / 2
            color: surface._lt(0.45)
            layer.enabled: true
            layer.effect: MultiEffect { blurEnabled: true; blur: 0.6; blurMax: 12 }
        }


        // ── Angle-aware border brightening — light source implied upper-left,
        // same logic as the specular highlight and corner catch-light above.
        // Rectangle.border.color can't itself carry a gradient, so this is a
        // second, thin rounded-rect hairline layered on top rather than a
        // straight-line overlay — sharing surface.cornerRadius means it renders
        // correctly against any shape here, including a full pill (Dock).
        Rectangle {
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
            height: Math.min(3, surface.cornerRadius)
            radius: surface.cornerRadius
            gradient: Gradient {
                GradientStop { position: 0.0; color: surface._lt(0.44 * ShellLight.facing(0, -1)) }   // 0.38
                GradientStop { position: 1.0; color: surface._lt(0.0) }
            }
        }
        Rectangle {
            anchors.top: parent.top; anchors.left: parent.left; anchors.bottom: parent.bottom
            width: Math.min(3, surface.cornerRadius)
            radius: surface.cornerRadius
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: surface._lt(0.44 * ShellLight.facing(-1, 0)) }  // 0.22
                GradientStop { position: 1.0; color: surface._lt(0.0) }
            }
        }

        // ── Inner rim light — real glass shows a bright thin line just inside
        // the edge from internal reflection. Distinct from the outer glow halo/
        // rim below (which sit OUTSIDE the shape, z:-1/-2) — this sits INSIDE.
        Rectangle {
            anchors.fill: parent
            anchors.margins: (typeof settings !== "undefined" && settings.highContrast === true) ? 3 : 2
            radius: Math.max(0, surface.cornerRadius - 2)
            color: "transparent"
            border.width: 1
            border.color: surface._lt(0.14)
        }
    }

    // ── Wet-glass motion glint — reveal-triggered, physically derived ─────
    // One physical quantity is animated: θ, the angle between the viewer and
    // the glass normal as a light plane pans past the pane, swept LINEARLY
    // (constant angular rate — like a light source panning past a fixed
    // window). Position, brightness, and streak length all DERIVE from θ,
    // no hand-tuned easing anywhere:
    //   position   ∝ tan(θ)  — a reflection projected onto a flat pane moves
    //              with the tangent of the view angle: it glides through
    //              mid-pane and accelerates past the ends. The perceived
    //              motion curve IS the projection, not an easing pick.
    //   brightness R(θ) = R0 + (1-R0)(1-cosθ)^5 — Fresnel-Schlick with the
    //              REAL cosθ (R0 0.04 = uncoated glass at normal incidence):
    //              near-invisible mid-pane (normal incidence reflects ~4%),
    //              flaring toward grazing at either end. This also FIXES the
    //              previous proxy formula, which was inverted vs. its own
    //              comment — it flared at MID-sweep and dimmed at the ends.
    //   length     ∝ 1/cosθ — grazing highlights physically elongate
    //              (anisotropic smear), capped so the streak stays on-pane.
    // Epilepsy safety (load-bearing, see user_accessibility_vision_epilepsy):
    // one 900ms sweep has exactly two grazing flares ~0.9s apart (≈1.1Hz,
    // well under the 3Hz WCAG 2.3.1 line), peak alpha tone-mapped to 0.58 —
    // BELOW the old 0.73 mid-sweep flash. Calmer than before, not hotter.
    // Dock/panels are intellihide surfaces, not hover surfaces — the sweep
    // plays once, automatically, on revealPulse (see the property above),
    // never tracks the cursor (that's the widgets-only interaction, see
    // NCDEGlass2.qml — widgets get NO moving glint, operator order
    // 2026-07-06). Gated by animPolicy.decorative — the same governance
    // flag every other ambient NCDE effect uses (folds in reduceMotion/
    // thermalPressure/low-power).
    // Masked through pillMask (the same mask the blur step uses in Step 2)
    // rather than a bounding-box clip, so the glint's own silhouette always
    // matches the real surface shape (pill/rounded-rect) — never a bare
    // rectangle poking past a rounded corner.
    Item {
        id: glintSource
        anchors.fill: parent
        visible: false
        layer.enabled: true
        Rectangle {
            id: glint
            readonly property real thetaMax: 1.396   // 80° — grazing limit of the sweep
            property real theta: -thetaMax
            readonly property real cosT: Math.cos(theta)
            // tan-projection of the animated angle onto sweep progress 0..1
            readonly property real sweepPos: 0.5 + 0.5 * Math.tan(theta) / Math.tan(thetaMax)
            // 1/cosθ grazing elongation, capped (cos 80° would give 5.8x)
            readonly property real stretch: Math.min(2.5, 1 / Math.max(0.18, cosT))
            width:  surface.glintVertical ? parent.width * 1.4            : parent.width * 0.10 * stretch
            height: surface.glintVertical ? parent.height * 0.10 * stretch : parent.height * 1.4
            x: surface.glintVertical ? -parent.width * 0.2 : -width  + sweepPos * (parent.width  + width)
            y: surface.glintVertical ? -height + sweepPos * (parent.height + height) : -parent.height * 0.2
            opacity: {
                // True Schlick curve, then a fixed linear exposure mapping the
                // physical reflectance range [R0 .. R(80°)] onto a visible
                // 0.10..0.58 alpha band — screens aren't radiometric, so the
                // curve's SHAPE is preserved exactly and only the exposure is
                // chosen (standard tone mapping, not a curve tweak).
                var r0 = 0.04
                var R    = r0 + (1 - r0) * Math.pow(1 - cosT, 5)
                var rMax = r0 + (1 - r0) * Math.pow(1 - Math.cos(thetaMax), 5)
                return 0.10 + 0.48 * (R - r0) / (rMax - r0)
            }
            gradient: Gradient {
                // Beer-Lambert cross-section: I(d) = I0·e^(-αd). Light through
                // an absorbing pane decays exponentially with distance, so the
                // streak is a hot thin core with soft haze wings — not the old
                // linear tent. α chosen so the streak edge lands at e^-4 (≈2%,
                // visually extinguished); each stop below is the exact e^-n.
                orientation: surface.glintVertical ? Gradient.Vertical : Gradient.Horizontal
                GradientStop { position: 0.000; color: Qt.rgba(1,1,1,0.00)  }   // e^-4 → floor
                GradientStop { position: 0.125; color: Qt.rgba(1,1,1,0.05)  }   // e^-3
                GradientStop { position: 0.250; color: Qt.rgba(1,1,1,0.135) }   // e^-2
                GradientStop { position: 0.375; color: Qt.rgba(1,1,1,0.368) }   // e^-1
                GradientStop { position: 0.500; color: Qt.rgba(1,1,1,1.00)  }   // core
                GradientStop { position: 0.625; color: Qt.rgba(1,1,1,0.368) }
                GradientStop { position: 0.750; color: Qt.rgba(1,1,1,0.135) }
                GradientStop { position: 0.875; color: Qt.rgba(1,1,1,0.05)  }
                GradientStop { position: 1.000; color: Qt.rgba(1,1,1,0.00)  }
            }
            SequentialAnimation {
                id: glintSweep
                // Linear on the ANGLE — every visible speed/brightness/length
                // change comes from the tan/Schlick/1-cos physics above.
                NumberAnimation { target: glint; property: "theta"; from: -glint.thetaMax; to: glint.thetaMax; duration: 900 }
            }
        }
    }
    MultiEffect {
        anchors.fill: parent
        source: glintSource
        maskEnabled: true
        maskSource: pillMask
        visible: animPolicy.decorative && !animPolicy.screenIdle
    }

    // ── Pill border ───────────────────────────────────────────────────────
    // Accessibility: settings.highContrast thickens the border — a real, load-bearing change
    // (matches the same contrast-floor fix in NCDEKit.qml's ink derivation), not cosmetic.
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: "transparent"
        border.width: (typeof settings !== "undefined" && settings.highContrast === true) ? 2 : 1
        border.color: surface.edge
        Behavior on border.color { ColorAnimation { duration: 420; easing.type: Easing.InOutCubic } }
    }

    // ── Outer glow halo — expanded Rect with glowing border ──────────────
    // jewelGlow breathes it exactly like MotifFrame's outerGlow (layer A):
    // border.color RGBA held constant, the lampPulse-driven part moves to
    // opacity so the layer.enabled cached blur texture doesn't re-blur every
    // tick.
    Rectangle {
        x: -6; y: -6
        width: parent.width + 12; height: parent.height + 12
        radius: surface.cornerRadius + 6
        color: "transparent"
        border.width: 8
        border.color: Qt.rgba(surface.glowHalo.r, surface.glowHalo.g,
                              surface.glowHalo.b, surface.glowA * 0.55)
        opacity: surface.jewelGlow ? Math.max(0.55, lampPulse.val + 0.45) : 1.0
        z: -1
        layer.enabled: surface.glowBlurred
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.8; blurMax: 20 }
        Behavior on border.color { ColorAnimation { duration: 420 } }
        Behavior on opacity { enabled: surface.jewelGlow; NumberAnimation { duration: 480; easing.type: Easing.InOutCubic } }
    }

    // ── Crown glow — amber cap on the top edge, ported from MotifFrame's
    // crownGlow (layer B). jewelGlow-only (Dock/TopPanel/BottomPanel).
    Rectangle {
        visible: surface.jewelGlow
        anchors.top:    parent.top
        anchors.left:   parent.left
        anchors.right:  parent.right
        anchors.topMargin:   -8
        anchors.leftMargin:  -8
        anchors.rightMargin: -8
        height: Math.min(parent.height * 0.6, 40) + 8
        radius: surface.cornerRadius + 8
        color:  "transparent"
        border.width: 8
        border.color: Qt.rgba(surface.lampCol.r, surface.lampCol.g, surface.lampCol.b, surface.glowA * 0.58)
        opacity: surface.jewelGlow ? Math.max(0.50, lampPulse.val + 0.42) : 0.0
        z: -1
        layer.enabled: surface.jewelGlow
        layer.effect: MultiEffect { blurEnabled: true; blur: 0.65; blurMax: 16 }
        Behavior on opacity { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
    }

    // ── Outer glow rim — tight border at surface edge ────────────────────
    Rectangle {
        anchors.fill: parent
        radius: surface.cornerRadius
        color: "transparent"
        border.width: 2
        border.color: Qt.rgba(surface.glowRim.r, surface.glowRim.g,
                              surface.glowRim.b, surface.glowA * 0.60)
        z: -2
        Behavior on border.color { ColorAnimation { duration: 420 } }
    }

    // ── Drop-shadow lift — soft blurred shadow of the pill shape ─────────
    // Was an unblurred offset black Rect (hard 8px ledge at 0.55) — the one
    // layer that read as a sticker rather than a pane. Same MultiEffect shadow
    // NCDEGlass2 already uses; tone is the cavity's dark aubergine, not #000.
    // MultiEffect also draws its source, so the caster is a dark pill (not the
    // white pillMask) — un-offset it sits hidden under the opaque blur layer.
    Item {
        id: shadowCaster
        anchors.fill: parent
        visible: false
        layer.enabled: true
        Rectangle { anchors.fill: parent; radius: surface.cornerRadius; color: Qt.rgba(0.04, 0.03, 0.06, 0.55) }
    }
    MultiEffect {
        anchors.fill: parent
        source: shadowCaster
        shadowEnabled: true
        shadowColor: Qt.rgba(0.04, 0.03, 0.06, 1.0)
        shadowBlur: 0.9
        shadowVerticalOffset: 6
        z: -3
    }

    Behavior on blurPx { NumberAnimation { duration: 320; easing.type: Easing.InOutCubic } }
}
