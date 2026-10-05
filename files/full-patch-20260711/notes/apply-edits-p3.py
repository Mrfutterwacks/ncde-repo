#!/usr/bin/env python3
"""Filigree Phase 3 — dedupe. Zero visible change intended.

  A. 12 unrolled Glow/Frame rows (6 widgets x 2)  -> one data-driven Repeater
  B. 6 unrolled per-widget Reset buttons          -> one data-driven Repeater
  C. Section-colour popup merged into the unified colour popup (it only added
     a Reset button); the Sections tap-handler's inline hex->HSV seeding (a
     duplicate of openColorPopup's) goes away with it.

Anchored edits: every anchor must match EXACTLY the expected count or we abort.
Operates on FiligreeTab.qml in this directory (a copy of the live file).
"""
import sys, pathlib

W = pathlib.Path(__file__).parent
fil = (W / "FiligreeTab.qml").read_text()
fails = []

def rep(text, old, new, count, label):
    n = text.count(old)
    if n != count:
        fails.append(f"ANCHOR FAIL [{label}]: expected {count}, found {n}")
        return text
    return text.replace(old, new)

def slice_replace(text, start_marker, end_marker, new, label):
    """Replace from start_marker through end_marker (inclusive). Both unique."""
    for m, which in ((start_marker, "start"), (end_marker, "end")):
        n = text.count(m)
        if n != 1:
            fails.append(f"ANCHOR FAIL [{label}/{which}]: expected 1, found {n}")
            return text
    a = text.index(start_marker)
    b = text.index(end_marker) + len(end_marker)
    if b <= a:
        fails.append(f"ANCHOR FAIL [{label}]: end precedes start")
        return text
    return text[:a] + new + text[b:]

# ═══ E1: widget metadata + shared default-colour lookup ═══════════════════════
fil = rep(fil,
    '    readonly property var widgetFonts:  ["Cinzel","Cormorant Garamond","EB Garamond","IM Fell English"]\n',
    '    readonly property var widgetFonts:  ["Cinzel","Cormorant Garamond","EB Garamond","IM Fell English"]\n'
    '\n'
    '    // Phase 3 dedupe (2026-07-21): one metadata row per widget drives the 12 Glow/Frame\n'
    '    // rows, the 6 Reset buttons, and their popup titles — previously unrolled copies.\n'
    '    // pop = popup display name (La’Ombre’s popups were titled "Ghost", preserved).\n'
    '    readonly property var widgetMeta: [\n'
    '        { k:"clock",   pop:"Clock",   fontDef:"Cinzel",             reset:"Reset Clock" },\n'
    '        { k:"space",   pop:"Space",   fontDef:"Cinzel",             reset:"Reset Space" },\n'
    '        { k:"weather", pop:"Weather", fontDef:"Cinzel",             reset:"Reset Weather" },\n'
    '        { k:"stats",   pop:"Stats",   fontDef:"Cinzel",             reset:"Reset Stats" },\n'
    '        { k:"salon",   pop:"Salon",   fontDef:"Cormorant Garamond", reset:"Reset Salon" },\n'
    '        { k:"laombre", pop:"Ghost",   fontDef:"Cinzel",             reset:"Reset La’Ombre d’Opale" }\n'
    '    ]\n'
    '    // per-widget default accent/glow colour — the same fallbacks the unrolled blocks used\n'
    '    function _widgDefault(key) {\n'
    '        return ({ clock: ncde.gilt3, space: ncde.cer, weather: ncde.verd,\n'
    '                  stats: ncde.wine4, salon: "#6a4a8b", laombre: "#6a4a8b" })[key]\n'
    '    }\n',
    1, "widget-meta")

# ═══ E2: 12 Glow/Frame rows -> one Repeater ══════════════════════════════════
ROWS_NEW = '''\
                            // Glow + Frame rows for every widget — data-driven (Phase 3).
                            // Same swatch/↺/caption/× behavior as the unrolled originals;
                            // popup default = per-widget accent for Glow, engine amber for Frame.
                            Repeater {
                                model: {
                                    var rows = []
                                    for (var i = 0; i < fil.widgetMeta.length; i++) {
                                        var m = fil.widgetMeta[i]
                                        rows.push({ wk: m.k, pop: m.pop, field: "glow",    label: "Glow",  cap: "engine default" })
                                        rows.push({ wk: m.k, pop: m.pop, field: "leading", label: "Frame", cap: "amber default" })
                                    }
                                    return rows
                                }
                                Row {
                                    visible: fil.selWidget === modelData.wk
                                    spacing: 10; width: parent.width
                                    Text { text: modelData.label; width: 54; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Rectangle {
                                        width: 30; height: 24; radius: 5; anchors.verticalCenter: parent.verticalCenter
                                        border.color: fp.gilt0; border.width: 1.5
                                        color: fil.widg[modelData.wk][modelData.field] !== "" ? fil.widg[modelData.wk][modelData.field] : "transparent"
                                        Text { text: "↺"; visible: fil.widg[modelData.wk][modelData.field] === ""; anchors.centerIn: parent; color: fp.gilt1; font.pixelSize: SetTheme.md }
                                        TapHandler { onTapped: fil.openColorPopup(
                                            modelData.pop + " — " + modelData.label,
                                            fil.widg[modelData.wk][modelData.field] !== "" ? fil.widg[modelData.wk][modelData.field]
                                                                                           : (modelData.field === "glow" ? fil._widgDefault(modelData.wk) : ncde.gilt3),
                                            function(c) { fil._updateWidg(modelData.wk, modelData.field, c); fil.pushWidget(modelData.wk) }
                                        ) }
                                    }
                                    Text { text: "·"; color: fp.inkSoft; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Text { text: modelData.cap; visible: fil.widg[modelData.wk][modelData.field] === ""; color: fp.inkSoft; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                    Text {
                                        visible: fil.widg[modelData.wk][modelData.field] !== ""
                                        text: "×"; color: fp.gilt1; font.pixelSize: SetTheme.md; anchors.verticalCenter: parent.verticalCenter
                                        TapHandler { onTapped: { fil._updateWidg(modelData.wk, modelData.field, ""); fil.pushWidget(modelData.wk) } }
                                    }
                                }
                            }
'''
fil = slice_replace(fil,
    '                            Row { visible: fil.selWidget === "clock"; spacing: 10; width: parent.width\n'
    '                                Text { text: "Glow";',
    'TapHandler { onTapped: { fil._updateWidg("laombre", "leading", ""); fil.pushWidget("laombre") } }\n'
    '                                }\n'
    '                            }\n',
    ROWS_NEW, "glow-frame-rows")

# ═══ E3: 6 Reset buttons -> one Repeater ═════════════════════════════════════
RESET_NEW = '''\
                // Reset buttons — one per widget, data-driven (Phase 3). Same engine+settings
                // reset calls and per-widget accent/font fallbacks as the unrolled originals.
                Repeater {
                    model: fil.widgetMeta
                    Rectangle {
                        visible: fil.selWidget === modelData.k
                        width: parent.width; height: 28; radius: 6
                        border.color: fp.gilt1; border.width: 1.5
                        color: fp.paper1
                        Text { anchors.centerIn: parent; text: modelData.reset; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }
                        TapHandler { onTapped: {
                            settings.resetWidgetStyle(modelData.k)
                            ncde.resetWidgetStyle(modelData.k)
                            var ws = ncde.widgetStyle(modelData.k)
                            var w = { clock: widg.clock, space: widg.space, weather: widg.weather, stats: widg.stats, salon: widg.salon, laombre: widg.laombre }
                            w[modelData.k] = {
                                accent:  (ws && ws["accent"])  ? ws["accent"]  : fil._widgDefault(modelData.k),
                                glow:    (ws && ws["glow"]     !== undefined) ? ws["glow"]    : "",
                                leading: (ws && ws["leading"]  !== undefined) ? ws["leading"] : "",
                                fill:    (ws && ws["fill"])    ? ws["fill"]    : "",
                                font:    (ws && ws["font"])    ? ws["font"]    : modelData.fontDef
                            }
                            widg = w
                        } }
                    }
                }
'''
# end of the la'ombre reset block: locate via its unique label, then slice to its close
_lao = 'text: "Reset La’Ombre d’Opale"'
if fil.count(_lao) != 1:
    fails.append(f"ANCHOR FAIL [reset-buttons/laombre-label]: expected 1, found {fil.count(_lao)}")
else:
    tail = fil[fil.index(_lao):]
    close = '                        widg = w\n                    } }\n                }\n'
    if close not in tail:
        fails.append("ANCHOR FAIL [reset-buttons/close]: not found after la'ombre label")
    else:
        end_abs = fil.index(_lao) + tail.index(close) + len(close)
        start_marker = ('                Rectangle {\n'
                        '                    visible: fil.selWidget === "clock"\n'
                        '                    width: parent.width; height: 28; radius: 6\n')
        if fil.count(start_marker) != 1:
            fails.append(f"ANCHOR FAIL [reset-buttons/start]: expected 1, found {fil.count(start_marker)}")
        else:
            a = fil.index(start_marker)
            if a >= end_abs:
                fails.append("ANCHOR FAIL [reset-buttons]: start after end")
            else:
                fil = fil[:a] + RESET_NEW + fil[end_abs:]

# ═══ E4: merge the Sections colour popup into the unified popup ══════════════
# 4a. retire section-popup state; add the optional reset-callback slot
fil = rep(fil,
    '    property string _sectionTarget: ""\n'
    '    property string _sectionLabel: ""\n'
    '    property bool   _sectionPopupOpen: false\n',
    '', 1, "section-props")
fil = rep(fil,
    '    property var    _colorCallback: null\n',
    '    property var    _colorCallback: null\n'
    '    property var    _colorResetCallback: null   // non-null → popup shows a Reset button (Sections rows)\n',
    1, "reset-callback-prop")

# 4b. openColorPopup grows an optional resetCallback param
fil = rep(fil,
    '    function openColorPopup(title, currentHex, callback) {\n'
    '        _colorPopupTitle = title\n'
    '        _colorCallback = callback\n',
    '    function openColorPopup(title, currentHex, callback, resetCallback) {\n'
    '        _colorPopupTitle = title\n'
    '        _colorCallback = callback\n'
    '        _colorResetCallback = resetCallback || null\n',
    1, "opencolorpopup-sig")

# 4c. Sections rows open the unified popup (drops the duplicated hex->HSV math)
fil = rep(fil,
    '                                TapHandler { onTapped: {\n'
    '                                    fil._sectionTarget = modelData.p\n'
    '                                    fil._sectionLabel = modelData.n\n'
    '                                    var cur = sectionColorRow.cur\n'
    '                                    if (cur !== "") {\n'
    '                                        var r2 = parseInt(cur.slice(1,3), 16) / 255\n'
    '                                        var g2 = parseInt(cur.slice(3,5), 16) / 255\n'
    '                                        var b2 = parseInt(cur.slice(5,7), 16) / 255\n'
    '                                        var mx = Math.max(r2,g2,b2), mn = Math.min(r2,g2,b2), d = mx-mn\n'
    '                                        var h = 0, s = 0.75\n'
    '                                        if (d > 0) {\n'
    '                                            if (mx === r2)      h = ((g2-b2)/d) % 6\n'
    '                                            else if (mx === g2) h = (b2-r2)/d + 2\n'
    '                                            else                h = (r2-g2)/d + 4\n'
    '                                            h *= 60; if (h < 0) h += 360\n'
    '                                            s = d / mx\n'
    '                                        }\n'
    '                                        sectionWheel.hue = h; sectionWheel.saturation = s\n'
    '                                    }\n'
    '                                    fil._sectionPopupOpen = true\n'
    '                                } }\n',
    '                                TapHandler { onTapped: fil.openColorPopup(\n'
    '                                    modelData.n + " — Colour",\n'
    '                                    sectionColorRow.cur,\n'
    '                                    function(c) { fil.pushSectionColor(modelData.p, c) },\n'
    '                                    function()  { fil.pushSectionColor(modelData.p, "") }\n'
    '                                ) }\n',
    1, "sections-taphandler")

# 4d. delete the whole Section Colours popup block
fil = slice_replace(fil,
    '    // ── Section Colours colour picker popup',
    '                        TapHandler { onTapped: fil._sectionPopupOpen = false }\n'
    '                    }\n'
    '                }\n'
    '            }\n'
    '        }\n'
    '    }\n',
    '', "section-popup-delete")

# 4e. unified popup header comment now covers Sections too
fil = rep(fil,
    '    // ── Unified colour picker popup (Glass / Widgets / Type tabs) ──────────\n',
    '    // ── Unified colour picker popup (Glass / Widgets / Type / Sections) ────\n',
    1, "unified-comment")

# 4f. optional Reset button between Set Colour and Cancel (styling carried over
#     verbatim from the deleted Sections popup, incl. its text-shadow layer)
fil = rep(fil,
    '                        TapHandler { onTapped: {\n'
    '                            if (fil._colorCallback) fil._colorCallback(colorWheel.currentHex)\n'
    '                            fil._colorPopupOpen = false\n'
    '                        } }\n'
    '                    }\n',
    '                        TapHandler { onTapped: {\n'
    '                            if (fil._colorCallback) fil._colorCallback(colorWheel.currentHex)\n'
    '                            fil._colorPopupOpen = false\n'
    '                        } }\n'
    '                    }\n'
    '\n'
    '                    Rectangle {\n'
    '                        visible: fil._colorResetCallback !== null\n'
    '                        width: 78; height: 28; radius: 6; color: "transparent"\n'
    '                        border.color: fp.gilt1; border.width: 1\n'
    '                        Text {\n'
    '                            anchors.centerIn: parent; text: "Reset"\n'
    '                            color: fp.gilt1; font.family: fp.serif; font.pixelSize: SetTheme.sm\n'
    '                            layer.enabled: settings.textShadowEnabled\n'
    '                            layer.effect: MultiEffect {\n'
    '                                autoPaddingEnabled: true; shadowEnabled: true\n'
    '                                shadowColor: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"\n'
    '                                shadowBlur: Math.max(0.0, Math.min(1.0, settings.textShadowRadius / 20.0))\n'
    '                                shadowHorizontalOffset: settings.textShadowOffsetX\n'
    '                                shadowVerticalOffset: settings.textShadowOffsetY\n'
    '                            }\n'
    '                        }\n'
    '                        TapHandler { onTapped: {\n'
    '                            if (fil._colorResetCallback) fil._colorResetCallback()\n'
    '                            fil._colorPopupOpen = false\n'
    '                        } }\n'
    '                    }\n',
    1, "popup-reset-button")

if fails:
    print("\n".join(fails)); sys.exit(1)

# retired identifiers must be fully gone
for gone in ("_sectionPopupOpen", "_sectionTarget", "_sectionLabel", "sectionWheel"):
    if gone in fil:
        print(f"LEFTOVER [{gone}] still referenced"); sys.exit(1)

(W / "FiligreeTab.qml").write_text(fil)
print(f"ALL EDITS APPLIED — {len(fil.splitlines())} lines")
