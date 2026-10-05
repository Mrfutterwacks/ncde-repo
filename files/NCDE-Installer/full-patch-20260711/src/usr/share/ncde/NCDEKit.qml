// NCDEKit.qml — shared token resolver for the control kit.
// NOT a singleton (QML singletons can't see the `ncde` context property);
// instantiate once per component:  NCDEKit { id: k }  then use k.gilt1 etc.
//
// Every token reads from the live NCDEEngine (`ncde.*`) when present, and
// falls back to the warm dark base palette so a component still renders if a
// token is absent or when previewed standalone. No parallel colour system —
// these ARE ncde's values whenever ncde provides them.
import QtQuick 2.15
import "ncde-color.js" as Col

QtObject {
    id: kit
    property var eng: (typeof ncde !== "undefined") ? ncde : null
    // ── Iris live (2026-09-26): Iris Chroma + Filigree drive the SHELL's engine;
    // every app outside the shell carries its own frozen engine copy (June/July
    // builds, no source) that never hears an Iris click. main.qml publishes the
    // shell engine's live tokens to ~/.config/ncde/iris-live.json; outside the
    // shell NCDEKit reads them first, so Iris is global in every app, light and
    // dark, same as fonts. Inside the shell the engine is read directly (instant).
    // One shared reader per app (IrisLive singleton) — never a poll per kit.
    readonly property bool _inShell: IrisLive.inShell
    readonly property var live: IrisLive.live
    function c(name, fallback){
        if (live && live[name] !== undefined && live[name] !== null) return live[name]
        return (eng && eng[name] !== undefined && eng[name] !== null) ? eng[name] : fallback
    }
    // Contrast follows the ACTUAL filigree-driven palette background, not a separate
    // darkMode flag — so a dark palette gets light ink GLOBALLY (every non-glass widget
    // via NCDEKit) without a manual toggle. Filigree -> ncde engine -> NCDEKit, together.
    // Falls back to eng.darkMode if the engine exposes no panelBg.
    readonly property bool dark: _bgIsDark(c("panelBg", null))
    function _bgIsDark(bg) {
        if (bg === null || bg === undefined || bg === "") return (live && live.darkMode !== undefined) ? live.darkMode : (eng && eng.darkMode !== undefined) ? eng.darkMode : true
        // WCAG definition (2026-09-24): dark = light text reads better on it than dark
        // text does. Same cut as the old luma<0.45 for nearly every palette, but it is
        // the same measure the contrast floor below uses, so the two can't disagree.
        return Col.isDark(bg)
    }

    // ── grounds (invert between modes) ───────────────────────────────────
    // LIGHT = "Concordia day" aged-vellum; DARK = "Belle Époque night" warm-black.
    readonly property color panelBg:  dark ? c("panelBg",  "#0c0907") : c("panelBg",  "#e7d4a6")
    // panelBg2/surface2: the engine does NOT expose these — derive from the REAL palette
    // (panelBg/surface) so a cold Iris Chroma palette gets cold seconds instead of the old
    // hardcoded warm-gold fallback bleeding brown into secondary surfaces. Engine token wins if present.
    // Steps are perceptual Lab-L steps (ncde-color.js, 2026-09-24): Qt.darker/lighter scale HSV
    // value, so across the Iris presets surface2 moved anywhere from 3.9 to 9.1 L and panelBg2
    // as little as 0.4 L (invisible) on the near-black grounds. Fixed L steps = the same
    // separation on every palette, hue and chroma kept.
    readonly property color panelBg2: dark ? c("panelBg2", Col.shade(panelBg, -2.5)) : c("panelBg2", Col.shade(panelBg, 2.5))
    readonly property color surface:    dark ? c("surface",    "#171009") : c("surface",    "#f6efdc")
    readonly property color surfaceAlt: c("surfaceAlt", surface2)
    readonly property color surface2:  dark ? c("surface2",  Col.shade(surface, 7)) : c("surface2",  Col.shade(surface, -5))
    readonly property color surfaceHi: dark ? c("surfaceHi", gilt4) : c("surfaceHi", "#fffaea")
    // scrim (2026-09-26): what a dimmed backdrop behind a dialog is made of — the
    // palette's own ground at L 5, chroma capped at 8 (the same shade the glass uses
    // for shadow), so a green or gold palette never dims to a foreign navy/violet.
    readonly property color scrim: c("scrim", Col.tone(panelBg, 5, 8))

    // ── gilt ramp ────────────────────────────────────────────────────────
    readonly property color gilt0: c("gilt0", "#5a3a14")
    readonly property color gilt1: c("gilt1", "#8a5a20")
    readonly property color gilt2: c("gilt2", "#b07a30")
    readonly property color gilt3: c("gilt3", "#c98a3a")
    readonly property color gilt4: c("gilt4", "#e9c97c")
    readonly property color gilt5: c("gilt5", "#f6e3b0")

    // ── wine ramp ────────────────────────────────────────────────────────
    readonly property color wine1: c("wine1", "#2a0612")
    readonly property color wine2: c("wine2", "#4a0e22")
    readonly property color wine3: c("wine3", "#6e1832")
    readonly property color wine4: c("wine4", "#8b1e3f")

    // ── text (invert between modes) ──────────────────────────────────────
    // LIGHT ink = Concordia warm sepia-brown (not black); DARK = warm ivory.
    // Accessibility: settings.highContrast forces the true WCAG-extreme (pure white/near-black)
    // instead of the softer warm tones — a real contrast-ratio floor, not a cosmetic flag. This was
    // previously a dead, persisted-but-unread toggle (Settings.h's m_highContrast) — this is the fix.
    readonly property bool _hc: (typeof settings !== "undefined" && settings.highContrast === true)
    // Contrast floor (2026-09-24, universal palette): whatever an Iris palette or Woven
    // weave hands us, body ink is kept at WCAG AA (4.5:1) against the panel ground and
    // inkDim at 3:1. Col.readable() returns the palette's own colour untouched when it
    // already passes; otherwise it moves lightness only, so the hue stays the palette's.
    readonly property color ink:     _hc ? (dark ? "#ffffff" : "#000000") : Col.readable(dark ? c("ink", c("panelText", "#f4e9d2")) : c("ink", c("panelText", "#3a2418")), panelBg, 4.5)
    readonly property color inkSoft:  _hc ? (dark ? "#e8e8e8" : "#1a1a1a") : Col.readable(dark ? c("inkSoft", "#b8a07a") : c("inkSoft", "#6b513a"), panelBg, 4.5)
    // inkDim: engine doesn't expose it — derive from inkSoft (which IS palette-driven) as a
    // lower-contrast ink, instead of a fixed warm-gold. Keeps ink hue = the palette's ink hue.
    readonly property color inkDim:   _hc ? (dark ? "#d0d0d0" : "#303030") : Col.readable(dark ? c("inkDim",  Col.shade(inkSoft, -12)) : c("inkDim",  Col.shade(inkSoft, 12)), panelBg, 3.0)
    readonly property color inkLabel: dark ? gilt4 : gilt1

    // ── dynamic / status ─────────────────────────────────────────────────
    readonly property color accent:  c("accent",  "#c98a3a")   // wallpaper-driven
    readonly property color border:  c("border",  gilt1)
    readonly property color verd:    c("verd",    dark ? "#4f9183" : "#3a7a5e")
    readonly property color cer:     c("cer",     dark ? "#5fb4c6" : "#2f8aa0")
    readonly property color rose:    c("rose",    "#c64b63")

    // ── Concordia kingdom-line tones (hand-drawn boundary colours) ───────
    // Use for dividers / selection accents that want the map's muted jewel feel.
    // kingdom-line tones: engine exposes none of these — derive each from its REAL accent-family
    // token (wine/verd/gilt/cer) so they track a cold palette instead of the old fixed warm hexes.
    readonly property color lineWine:  c("lineWine",  dark ? Col.shade(wine4, 10) : wine4)
    readonly property color lineSage:  c("lineSage",  dark ? Col.shade(verd, 4)  : Col.shade(verd, -2))
    readonly property color lineOchre: c("lineOchre", dark ? gilt3 : gilt2)
    readonly property color lineCer:   c("lineCer",   dark ? cer : Col.shade(cer, -4))

    // ══ THE NCDE STANDARD (2026-09-26) ══════════════════════════════════════
    // One rulebook for every surface and every house app, so NCDE reads as one
    // product. Operator: "should not look like one person made this … polished
    // like OS X Aqua / Snow Leopard". Every value derives from the Iris palette.
    //
    // MATERIALS — the operator's three design languages:
    //   GLASS     persistent chrome: dock, panels, widgets (NCDEGlassSurface/Cap)
    //   PARCHMENT everything that pops up: menus, dialogs, Settings, manuals
    //   METAL     the brass that holds things: sockets, bezels, frames
    // All three are lit by ONE light (ShellLight) and shaded by ONE shade.
    //
    // shade — every shadow, cavity and veil: the palette's ground at L 5, chroma
    // capped at 8 (never #000, never a foreign violet). Same as scrim.
    readonly property color shade: scrim
    function shadeA(a) { return Qt.rgba(shade.r, shade.g, shade.b, a) }
    // metal — the old fixed bronze, re-made from the palette's gold: each step keeps
    // its exact Lab lightness and chroma, hue comes from gilt2. On the warm default
    // palette it IS the old bronze; a cold palette gets pewter, a green one brass.
    readonly property color metalCame:    Col.tone(gilt2, 1.8, 1.4)    // lead / came
    readonly property color metalCameLip: Col.tone(gilt2, 6.6, 6.5)
    readonly property color metalDark:    Col.tone(gilt2, 10.9, 13.6)
    readonly property color metal:        Col.tone(gilt2, 27.9, 27.5)
    readonly property color metalMid:     Col.tone(gilt2, 41.8, 38.9)
    readonly property color metalWarm:    Col.tone(gilt2, 55.1, 42.2)
    readonly property color metalShine:   gilt4
    readonly property color patina:       Col.tone(verd, 62, 26)       // verdigris in recesses
    // jewel glass — stained glass lives on rich colour: keep the palette colour's
    // hue, set its lightness, and never let its chroma fall below minC (a greyish
    // palette gold still makes AMBER glass, not a pewter wedge)
    function jewel(c, L, minC) {
        var q = Col.lch(c); if (!q) return c
        return Col.fromLch(L, Math.max(q[1], minC === undefined ? 45 : minC), q[2])
    }
    readonly property color jewelAmber: jewel(gilt2, 60, 48)
    readonly property color jewelRuby:  jewel(wine4, 38, 52)
    readonly property color jewelEmerald: jewel(verd, 50, 40)
    // parchment — paper, its gold leading and its dot-mesh, from the palette
    readonly property color paper:        surface
    readonly property color paperLeading: Col.tone(gilt4, 85, 47.2)
    readonly property color paperMesh:    Col.tone(gilt1, 42.5, 42.4)

    // GEOMETRY — radii and a 4-pt spacing scale
    readonly property int rWindow: 16      // app windows, sheets
    readonly property int rCard:   10      // cards, panes, popovers
    readonly property int rControl: 8      // buttons, fields, list rows
    readonly property int rSmall:  4       // chips' inner parts, badges
    readonly property int s1: 4
    readonly property int s2: 8
    readonly property int s3: 12
    readonly property int s4: 16
    readonly property int s5: 24
    readonly property int s6: 32

    // TYPE — one scale (pixel sizes pass through fs(), so Script Shift moves all)
    //   display (app names)  titles (headings, CAPS labels)  serif (body)  mono
    readonly property int tCaption: 11
    readonly property int tLabel:   12     // CAPS, letterSpacing 2
    readonly property int tBody:    14
    readonly property int tTitle:   18
    readonly property int tHeading: 24
    readonly property int tDisplay: 32

    // STATES — the same feedback everywhere. An app's signature colour (Verve's
    // ink, Magpie's wire, Hummingbird's gilt) marks selection, primary actions
    // and its icon ONLY; every app shares the same ground and chrome.
    readonly property color ground:   panelBg          // window ground
    readonly property color chrome:   surface          // title / tool / status bars
    readonly property color well:     surface2         // fields, lists, wells
    function hoverFill(sig)    { var s = sig === undefined ? accent : sig; return Qt.rgba(s.r, s.g, s.b, 0.10) }
    function selectFill(sig)   { var s = sig === undefined ? accent : sig; return Qt.rgba(s.r, s.g, s.b, 0.20) }
    function selectEdge(sig)   { var s = sig === undefined ? accent : sig; return Qt.rgba(s.r, s.g, s.b, 0.65) }
    readonly property color focusRing: Col.readable(glowOrAccent, panelBg, 3.0)
    readonly property color glowOrAccent: c("glow", accent)
    readonly property real  disabledOpacity: 0.45
    readonly property real  veil: 0.45             // modal backdrop strength (shadeA(veil))
    // MOTION — short, quiet, the same everywhere
    readonly property int mHover:  110
    readonly property int mPress:  0               // presses are instant (weight & touch)
    readonly property int mReveal: 160             // dialogs, popovers, sheets

    // ── fonts ────────────────────────────────────────────────────────────
    readonly property string display: c("displayFont", "Cinzel Decorative")
    readonly property string titles:  c("titleFont",   "Cinzel")
    readonly property string serif:   c("bodyFont",    "Cormorant Garamond")
    readonly property string fell:    c("fellFont", "IM Fell English")
    readonly property string gar:     c("garFont",  "EB Garamond")
    readonly property string mono:    c("monoFont",    "TerminalVector")

    // ── scale ────────────────────────────────────────────────────────────
    // reads the user's UI scale from the `settings` context object (NOT theme).
    property real uiScale: (typeof settings !== "undefined" && settings.uiScale) ? settings.uiScale : 1.0
    // Real bug fix (2026-07-02): fs() only ever multiplied by uiScale, ignoring fontSizeScale
    // entirely — so the Font Size Scale slider (Filigree's Fonts tab) never affected any of the
    // ~40 files' custom-rendered text sized via fs(), only text reading ncde.fontSize_* directly.
    // Mirrors NCDEEngine::recomputeFontSizes()'s own combined factor (k = uiScale * fontSizeScale)
    // exactly, instead of the two scales being tracked independently.
    property real fontSizeScale: (typeof settings !== "undefined" && settings.fontSizeScale) ? settings.fontSizeScale : 1.0
    function fs(base){ return Math.round(base * uiScale * fontSizeScale) }
}
