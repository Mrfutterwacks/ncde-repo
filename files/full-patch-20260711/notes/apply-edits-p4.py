#!/usr/bin/env python3
"""Filigree Phase 4 (2026-07-21) — full-controls audit refinements.
Anchored edits over the LIVE FiligreeTab.qml (1359 lines) + SettingsColorWheel.qml.
Every anchor must match its expected count exactly or the whole script aborts
(no partial writes). Run from the directory holding the two copied files.

Fixes (audit findings):
  F1  internal keys leaked to UI: "TOPPANEL — GLASS" / "TopPanel — Surface" /
      "Laombre — Accent" -> _dispName() humanises everywhere; laombre stays "Ghost"
      (operator precedent, widgetMeta.pop)
  F2  colour popup never seeded brightness (dark colours opened bright, brightness
      sticky across opens) and greys seeded sat 0.75 -> full HSV decomposition
  F3  widget preview: transparent 2-stop gradient silently overrode the tint
      colour (gradient wins over color in QML) -> gradient removed
  F4  widget preview text bound fill even when unset ("") -> invalid-colour
      warnings + wrong colour; now falls back to gilt4 (widgets' real default,
      ClockPanel.qml:165)
  F5  Reset Typography left Spacing/Leading knobs where they were dragged
  F6  TEXT RENDERING preview never rendered the shadow (Shadow/Blur/Offset
      controls appeared dead) -> layer MultiEffect on the sample, /32 like shell;
      medium+small sample lines also get the outline style like the large one
  F7  Blur/Offset X/Offset Y active while shadow off; "Outline width" active
      while outline off (and label overflowed its 78px column) -> dim+disable
      dependent rows; label renamed "Thickness"
  F8  empty string accepted by Custom font + Terminal font inputs
  F9  Sections swatch popup seeded engine amber instead of the swatch's shown
      colour (the documented P3 delta) -> seeds fPalette[4] (QUILL)
  F10 Solei-Lune segments had all four corners rounded (broken segmented look)
      -> spaced chips, consistent with every other chip row in the tab
  F11 scrim tap did nothing -> tap outside the dialog now cancels (still
      swallows; nothing leaks to the tab beneath)
  F12 "Glow Int." abbreviation -> "Intensity"; Widgets GLASS block gets the
      same "<NAME> — GLASS" heading the Glass tab block has
  W1  SettingsColorWheel: shader status console.log removed (journal noise)
  W2  SettingsColorWheel: saturation clamp 0.15 -> 0 (pure white/grey text
      colours were unreachable from the picker)
"""
import os, sys

W = os.path.dirname(os.path.abspath(__file__))

def edit(path, edits):
    src = open(path, encoding="utf-8").read()
    for i, (old, new, count) in enumerate(edits):
        found = src.count(old)
        if found != count:
            sys.exit(f"ABORT {os.path.basename(path)} edit #{i}: anchor found {found}x, expected {count}\n--- anchor ---\n{old}")
        src = src.replace(old, new)
    return src

FT = os.path.join(W, "FiligreeTab.qml")
ft_edits = [

# ── F1a: _dispName helper, appended after _widgDefault ─────────────────────
(
"""    function _widgDefault(key) {
        return ({ clock: ncde.gilt3, space: ncde.cer, weather: ncde.verd,
                  stats: ncde.wine4, salon: "#6a4a8b", laombre: "#6a4a8b" })[key]
    }
""",
"""    function _widgDefault(key) {
        return ({ clock: ncde.gilt3, space: ncde.cer, weather: ncde.verd,
                  stats: ncde.wine4, salon: "#6a4a8b", laombre: "#6a4a8b" })[key]
    }
    // Human display names for surface/widget keys — internal keys (topPanel,
    // laombre) must never leak into headings or popup titles. La’Ombre popups
    // stay "Ghost" (operator precedent, widgetMeta.pop).
    function _dispName(key) {
        return ({ topPanel:"Top Panel", bottomPanel:"Bottom Panel", dock:"Dock",
                  clock:"Clock", space:"Space", weather:"Weather", stats:"Stats",
                  salon:"Salon", laombre:"Ghost" })[key] || key
    }
""", 1),

# ── F2: full HSV seed in openColorPopup (brightness + grey saturation) ─────
(
"""        var r2 = parseInt(hex.slice(1,3),16)/255, g2 = parseInt(hex.slice(3,5),16)/255, b2 = parseInt(hex.slice(5,7),16)/255
        var mx = Math.max(r2,g2,b2), mn = Math.min(r2,g2,b2), d = mx-mn
        var h = 0, sv = 0.75
        if (d > 0) {
            if (mx===r2) h = ((g2-b2)/d)%6
            else if (mx===g2) h = (b2-r2)/d+2
            else h = (r2-g2)/d+4
            h *= 60; if (h<0) h += 360; sv = d/mx
        }
        colorWheel.hue = h; colorWheel.saturation = sv""",
"""        var r2 = parseInt(hex.slice(1,3),16)/255, g2 = parseInt(hex.slice(3,5),16)/255, b2 = parseInt(hex.slice(5,7),16)/255
        var mx = Math.max(r2,g2,b2), mn = Math.min(r2,g2,b2), d = mx-mn
        // Full HSV decomposition — hue AND saturation AND brightness, so the wheel
        // always opens showing the colour the swatch shows (greys seed sat 0, not
        // 0.75; dark colours no longer open bright; brightness no longer sticks
        // at wherever the strip was last dragged).
        var h = 0, sv = 0
        if (d > 0) {
            if (mx===r2) h = ((g2-b2)/d)%6
            else if (mx===g2) h = (b2-r2)/d+2
            else h = (r2-g2)/d+4
            h *= 60; if (h<0) h += 360; sv = d/mx
        }
        colorWheel.hue = h; colorWheel.saturation = sv; colorWheel.value = mx""", 1),

# ── F5: Reset Typography resyncs the Spacing/Leading knobs ─────────────────
(
"""                        TapHandler { onTapped: {
                            settings.fontFamily = "Noto Sans"; settings.fontWeight = 400; settings.fontItalic = false
                            settings.letterSpacing = 0.0; settings.lineHeight = 1.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                        } }""",
"""                        TapHandler { onTapped: {
                            settings.fontFamily = "Noto Sans"; settings.fontWeight = 400; settings.fontItalic = false
                            settings.letterSpacing = 0.0; settings.lineHeight = 1.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                            // sliders hold their own value once dragged — resync the knobs
                            spacingSlider.value = 3; leadingSlider.value = 10
                        } }""", 1),

(
"""                    NCDESlider { minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)""",
"""                    NCDESlider { id: spacingSlider; minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)""", 1),

(
"""                    NCDESlider { minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)""",
"""                    NCDESlider { id: leadingSlider; minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)""", 1),

# ── F8a: Custom font input — reject empty/whitespace ───────────────────────
(
"""                            onEditingFinished: { settings.fontFamily = text; settings.saveFontSettings(); settings.applyFontSettings() }""",
"""                            onEditingFinished: {
                                var t = text.trim()
                                if (t === "") { text = settings.fontFamily; return }
                                settings.fontFamily = t; settings.saveFontSettings(); settings.applyFontSettings()
                            }""", 1),

# ── F8b: Terminal font input — reject empty/whitespace ─────────────────────
(
"""                            onEditingFinished: ncde.setTerminalFont(text)""",
"""                            onEditingFinished: {
                                var t = text.trim()
                                if (t === "") { text = termRow.cfg.fontFamily !== undefined ? termRow.cfg.fontFamily : "monospace"; return }
                                ncde.setTerminalFont(t)
                            }""", 1),

# ── F6a: TEXT RENDERING sample renders the shadow (same /32 as shell text) ─
(
"""                    Column {
                        anchors.centerIn: parent; spacing: 2
                        Text { text: "The quick brown fox jumps — 1234";""",
"""                    Column {
                        anchors.centerIn: parent; spacing: 2
                        // the shadow the controls below configure must be visible HERE,
                        // else Shadow/Blur/Offset appear to do nothing (shell blur is /32)
                        layer.enabled: settings.textShadowEnabled
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowColor: settings.textShadowColor !== "" ? settings.textShadowColor : "#000000"
                            shadowBlur: Math.max(0.0, Math.min(1.0, settings.textShadowRadius / 32.0))
                            shadowHorizontalOffset: settings.textShadowOffsetX
                            shadowVerticalOffset: settings.textShadowOffsetY
                        }
                        Text { text: "The quick brown fox jumps — 1234";""", 1),

# ── F6b: medium + small sample lines get the outline style too ─────────────
(
"""font.pixelSize: theme.fontMedium; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; anchors.horizontalCenter: parent.horizontalCenter }""",
"""font.pixelSize: theme.fontMedium; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }""", 1),
(
"""font.pixelSize: theme.fontSmall; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; anchors.horizontalCenter: parent.horizontalCenter }""",
"""font.pixelSize: theme.fontSmall; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor !== "" ? settings.textColor : fp.gilt3; style: settings.textOutlineEnabled ? Text.Outline : Text.Normal; styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : fp.gilt0; anchors.horizontalCenter: parent.horizontalCenter }""", 1),

# ── F7a: "Outline width" -> "Thickness", row dims while outline off ────────
(
"""                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Outline width"; width: 78;""",
"""                Row {
                    width: parent.width; spacing: 10
                    // inert until an outline colour is set — dimmed so the dependency reads
                    opacity: settings.textOutlineEnabled ? 1.0 : 0.45
                    enabled: settings.textOutlineEnabled
                    Text { text: "Thickness"; width: 78;""", 1),

# ── F7b-d: Blur / Offset X / Offset Y dim while shadow off ─────────────────
(
"""                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Blur"; width: 78;""",
"""                Row {
                    width: parent.width; spacing: 10
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Blur"; width: 78;""", 1),
(
"""                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Offset X"; width: 78;""",
"""                Row {
                    width: parent.width; spacing: 10
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Offset X"; width: 78;""", 1),
(
"""                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Offset Y"; width: 78;""",
"""                Row {
                    width: parent.width; spacing: 10
                    opacity: settings.textShadowEnabled ? 1.0 : 0.45
                    enabled: settings.textShadowEnabled
                    Text { text: "Offset Y"; width: 78;""", 1),

# ── F9: Sections popup seeds the colour the swatch actually shows ──────────
(
"""                                TapHandler { onTapped: fil.openColorPopup(
                                    modelData.n + " — Colour",
                                    sectionColorRow.cur,""",
"""                                TapHandler { onTapped: fil.openColorPopup(
                                    modelData.n + " — Colour",
                                    sectionColorRow.cur !== "" ? sectionColorRow.cur : fil.fPalette[4],""", 1),

# ── F10: Solei-Lune — spaced chips, same language as every other chip row ──
(
"""                Row {
                    spacing: 0
                    Repeater {
                        model: [
                            {k:"auto",  n:"Auto",  i:0},""",
"""                Row {
                    spacing: 6
                    Repeater {
                        model: [
                            {k:"auto",  n:"Auto",  i:0},""", 1),
(
"""                            radius: (modelData.i === 0 || modelData.i === 2) ? 10 : 0""",
"""                            radius: 16""", 1),
(
"""                            color: sel ? fp.gilt4 : "transparent\"""",
"""                            color: sel ? fp.gilt4 : fp.paper0""", 1),

# ── F1b: Glass tab heading + popup titles humanised ────────────────────────
(
"""                        Text { text: fil.selSurface.toUpperCase() + " — GLASS";""",
"""                        Text { text: fil._dispName(fil.selSurface).toUpperCase() + " — GLASS";""", 1),
(
"""fil.selSurface.charAt(0).toUpperCase() + fil.selSurface.slice(1) + """,
"""fil._dispName(fil.selSurface) + """, 3),
(
"""fil.selWidget.charAt(0).toUpperCase() + fil.selWidget.slice(1) + """,
"""fil._dispName(fil.selWidget) + """, 5),

# ── F3: kill the transparent gradient that overrode the preview tint ───────
(
"""                            width: 150; height: 96; radius: 8; border.color: widgPreview.o.accent; border.width: 1
                            gradient: Gradient { GradientStop { position: 0; color: Qt.rgba(0,0,0,0) } GradientStop { position: 1; color: Qt.rgba(0,0,0,0) } }
                            color: Qt.lighter(widgPreview.o.accent, 1.9)""",
"""                            width: 150; height: 96; radius: 8; border.color: widgPreview.o.accent; border.width: 1
                            // (a gradient overrides `color` in QML — the old fully-transparent
                            // two-stop gradient meant this tint never painted)
                            color: Qt.lighter(widgPreview.o.accent, 1.9)""", 1),

# ── F4: preview text falls back to the widgets' real default ink ───────────
(
"""                                Text { text: widgPreview.sample[0]; color: widgPreview.o.fill;""",
"""                                Text { text: widgPreview.sample[0]; color: widgPreview.o.fill !== "" ? widgPreview.o.fill : ncde.gilt4;""", 1),
(
"""                                Text { text: widgPreview.sample[1]; color: widgPreview.o.fill;""",
"""                                Text { text: widgPreview.sample[1]; color: widgPreview.o.fill !== "" ? widgPreview.o.fill : ncde.gilt4;""", 1),

# ── F12a: Widgets GLASS block gets the same heading the Glass tab block has ─
(
"""                        anchors.margins: 11; spacing: 7
                        property var o: fil.surf[fil.selWidget]
                        Row { spacing: 10; width: parent.width""",
"""                        anchors.margins: 11; spacing: 7
                        property var o: fil.surf[fil.selWidget]
                        Text { text: fil._dispName(fil.selWidget).toUpperCase() + " — GLASS"; color: fp.ink; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm; font.letterSpacing: 2 }
                        Row { spacing: 10; width: parent.width""", 1),

# ── F12b: "Glow Int." -> "Intensity" (glass tab + widgets tab) ─────────────
(
"""Text { text: "Glow Int.";""",
"""Text { text: "Intensity";""", 2),

# ── F11: scrim tap outside the dialog cancels (still swallows everything) ──
(
"""    Rectangle {
        z: 20
        anchors.fill: parent
        visible: fil._colorPopupOpen
        color: Qt.rgba(0, 0, 0, 0.55)
        TapHandler {}

        Rectangle {
            anchors.centerIn: parent
            width: 280; height: colorPopupCol.height + 28""",
"""    Rectangle {
        id: popScrim
        z: 20
        anchors.fill: parent
        visible: fil._colorPopupOpen
        color: Qt.rgba(0, 0, 0, 0.55)
        // still swallows every tap (nothing reaches the tab beneath); a tap that
        // lands outside the dialog card dismisses — same as Cancel
        TapHandler { onTapped: function(ep) {
            var p = popDialog.mapFromItem(popScrim, ep.position.x, ep.position.y)
            if (p.x < 0 || p.y < 0 || p.x > popDialog.width || p.y > popDialog.height)
                fil._colorPopupOpen = false
        } }

        Rectangle {
            id: popDialog
            anchors.centerIn: parent
            width: 280; height: colorPopupCol.height + 28""", 1),
]

CW = os.path.join(W, "SettingsColorWheel.qml")
cw_edits = [
# ── W1: journal noise — shader status logged on every settings open ────────
(
"""            fragmentShader: "qrc:/shaders/qml/compositor/colorwheel.frag.qsb"
            Component.onCompleted: console.log("ColorWheel shader status:", status, "| log:", log)""",
"""            fragmentShader: "qrc:/shaders/qml/compositor/colorwheel.frag.qsb\"""", 1),

# ── W2: saturation clamp 0.15 -> 0 so true neutrals are pickable ───────────
(
"""            wheel.saturation = Math.max(0.15, Math.min(1, dist / r))""",
"""            // no minimum clamp (was 0.15) — the wheel centre must reach true
            // neutrals, else pure white/grey text colours are unpickable
            wheel.saturation = Math.min(1, dist / r)""", 1),
]

ft_out = edit(FT, ft_edits)
cw_out = edit(CW, cw_edits)

# post-conditions: the charAt title hack must be fully gone
if ".charAt(0).toUpperCase()" in ft_out:
    sys.exit("ABORT: charAt title hack still present after edits")
if "Math.max(0.15" in cw_out:
    sys.exit("ABORT: saturation clamp still present in wheel")

open(FT, "w", encoding="utf-8").write(ft_out)
open(CW, "w", encoding="utf-8").write(cw_out)
print("OK: FiligreeTab.qml ->", len(ft_out.splitlines()), "lines;",
      "SettingsColorWheel.qml ->", len(cw_out.splitlines()), "lines")
