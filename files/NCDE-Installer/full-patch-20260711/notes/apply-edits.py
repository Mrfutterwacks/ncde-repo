#!/usr/bin/env python3
"""Filigree Phase 1 — instant-apply everywhere, truth fixes, Iris save-UI removal.
Anchored edits: every replacement must match EXACTLY the expected count or we abort.
"""
import sys, re, pathlib

W = pathlib.Path(__file__).parent
fil = (W / "FiligreeTab.qml").read_text()
sld = (W / "NCDESlider.qml").read_text()
fails = []

def rep(text, old, new, count, label):
    n = text.count(old)
    if n != count:
        fails.append(f"ANCHOR FAIL [{label}]: expected {count}, found {n}")
        return text
    return text.replace(old, new)

def rerep(text, pat, repl, count, label):
    matches = re.findall(pat, text)
    if len(matches) != count:
        fails.append(f"REGEX FAIL [{label}]: expected {count}, found {len(matches)}")
        return text
    return re.sub(pat, repl, text)

# ═══ NCDESlider: released() signal (persist-on-release for heavy writers) ═══
sld = rep(sld,
    "    signal moved(real value)",
    "    signal moved(real value)\n    signal released()  // drag ended / tap done — persist-on-release hook",
    1, "slider-signal")
sld = rep(sld,
    "    TapHandler { onTapped: sl._set(point.position.x) }\n"
    "    DragHandler { id: drag; target: null; onCentroidChanged: if (active) sl._set(centroid.position.x) }",
    "    TapHandler { onTapped: { sl._set(point.position.x); sl.released() } }\n"
    "    DragHandler { id: drag; target: null; onCentroidChanged: if (active) sl._set(centroid.position.x)\n"
    "                  onActiveChanged: if (!active) sl.released() }",
    1, "slider-handlers")

# ═══ E1: header — the file must tell the truth ═══
fil = rep(fil,
    "// ║  CONFIRMED engine/settings calls are used directly. NOT-YET-WIRED      ║\n"
    "// ║  hooks (per-surface glass, per-widget colour/type) are GUARDED with    ║\n"
    "// ║  `typeof obj.fn === 'function'` so the tab loads without crashing      ║\n"
    "// ║  before the C++ is added.                                              ║",
    "// ║  Every engine/settings hook used here is live C++ (verified against    ║\n"
    "// ║  the running engine, 2026-07-20; old typeof guards kept as harmless    ║\n"
    "// ║  belt-and-braces). INSTANT-APPLY (operator, 2026-07-20): every         ║\n"
    "// ║  control applies AND persists the moment it changes — no Apply         ║\n"
    "// ║  buttons; sliders preview live while dragging, persist on release.     ║",
    1, "header")

# ═══ E2: mono chips — only fonts that actually exist ═══
fil = rep(fil,
    'model: ["Noto Mono","Liberation Mono","Ubuntu Mono","Fira Mono","DejaVu Sans Mono"]',
    'model: ["Noto Sans Mono","Liberation Mono","Ubuntu Mono","Fira Mono","JetBrains Mono","DejaVu Sans Mono"]',
    1, "mono-chips")

# ═══ E3: body font / weight / italic — instant apply ═══
fil = rep(fil,
    "TapHandler { onTapped: settings.fontFamily = modelData }",
    "TapHandler { onTapped: { settings.fontFamily = modelData; settings.saveFontSettings(); settings.applyFontSettings() } }",
    3, "family-chips")
fil = rep(fil,
    "onEditingFinished: settings.fontFamily = text",
    "onEditingFinished: { settings.fontFamily = text; settings.saveFontSettings(); settings.applyFontSettings() }",
    1, "family-custom")
fil = rep(fil,
    "TapHandler { onTapped: settings.fontWeight = modelData.v }",
    "TapHandler { onTapped: { settings.fontWeight = modelData.v; settings.saveFontSettings(); settings.applyFontSettings() } }",
    1, "weight-chips")
fil = rep(fil,
    "TapHandler { onTapped: settings.fontItalic = !settings.fontItalic }",
    "TapHandler { onTapped: { settings.fontItalic = !settings.fontItalic; settings.saveFontSettings(); settings.applyFontSettings() } }",
    1, "italic-toggle")

# ═══ E4: MEASURE specimen shows the user's actual font, not hardcoded serif ═══
fil = rep(fil,
    '                    Text {\n'
    '                        anchors.centerIn: parent\n'
    '                        text: "The quick brown fox jumps — 1234"\n'
    '                        color: fp.ink; font.family: fp.serif; font.pixelSize: SetTheme.md\n'
    '                    }',
    '                    Text {\n'
    '                        anchors.centerIn: parent\n'
    '                        text: "The quick brown fox jumps — 1234"\n'
    '                        color: fp.ink; font.family: settings.fontFamily; font.weight: settings.fontWeight\n'
    '                        font.italic: settings.fontItalic; font.pixelSize: SetTheme.md\n'
    '                    }',
    1, "measure-specimen")

# ═══ E5: Spacing / Leading — live preview on drag, persist on release ═══
fil = rep(fil,
    "NCDESlider { minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)\n"
    "                        onMoved: function(v) { settings.letterSpacing = v * 0.5 - 1.5 } anchors.verticalCenter: parent.verticalCenter }",
    "NCDESlider { minValue: 0; maxValue: 19; value: Math.round((settings.letterSpacing + 1.5) * 2)\n"
    "                        onMoved: function(v) { settings.letterSpacing = v * 0.5 - 1.5 }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "spacing-slider")
fil = rep(fil,
    "NCDESlider { minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)\n"
    "                        onMoved: function(v) { settings.lineHeight = v / 10.0 } anchors.verticalCenter: parent.verticalCenter }",
    "NCDESlider { minValue: 8; maxValue: 25; value: Math.round(settings.lineHeight * 10)\n"
    "                        onMoved: function(v) { settings.lineHeight = v / 10.0 }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "leading-slider")

# ═══ E6–E10: fill / outline / shadow — persist at the moment of change ═══
fil = rep(fil,
    "function(c) { settings.textColor = c }",
    "function(c) { settings.textColor = c; settings.saveTextColor() }",
    1, "fill-color")
fil = rep(fil,
    "function(c) { settings.textOutlineColor = c; settings.textOutlineEnabled = true }",
    "function(c) { settings.textOutlineColor = c; settings.textOutlineEnabled = true; settings.saveFontSettings() }",
    1, "outline-set")
fil = rep(fil,
    "onMoved: function(v){ settings.textOutlineWidth = v / 2.0 } anchors.verticalCenter: parent.verticalCenter }",
    "onMoved: function(v){ settings.textOutlineWidth = v / 2.0 }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "outline-width")
fil = rep(fil,
    "function(c) { settings.textShadowColor = c; settings.textShadowEnabled = true }",
    "function(c) { settings.textShadowColor = c; settings.textShadowEnabled = true; settings.saveFontSettings() }",
    1, "shadow-set")
fil = rep(fil,
    "onMoved: function(v){ settings.textShadowRadius = v } anchors.verticalCenter: parent.verticalCenter }",
    "onMoved: function(v){ settings.textShadowRadius = v }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "shadow-blur")
fil = rep(fil,
    "onMoved: function(v){ settings.textShadowOffsetX = v - 5 } anchors.verticalCenter: parent.verticalCenter }",
    "onMoved: function(v){ settings.textShadowOffsetX = v - 5 }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "shadow-offx")
fil = rep(fil,
    "onMoved: function(v){ settings.textShadowOffsetY = v - 5 } anchors.verticalCenter: parent.verticalCenter }",
    "onMoved: function(v){ settings.textShadowOffsetY = v - 5 }\n"
    "                        onReleased: settings.saveFontSettings() anchors.verticalCenter: parent.verticalCenter }",
    1, "shadow-offy")

# ═══ E11: remove "Apply Type" button ═══
fil = rep(fil,
    '\n                Rectangle {\n'
    '                    width: parent.width; height: 30; radius: 6\n'
    '                    border.color: fp.gilt0; border.width: 2\n'
    '                    gradient: Gradient { GradientStop { position: 0; color: fp.gilt4 } GradientStop { position: 1; color: fp.gilt3 } }\n'
    '                    Text { anchors.centerIn: parent; text: "Apply Type"; color: fp.wine1; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }\n'
    '                    TapHandler { onTapped: {\n'
    '                        settings.saveTextColor()\n'
    '                        settings.saveFontSettings()\n'
    '                        settings.applyFontSettings()\n'
    '                        notifications.notify("Filigree", "Type settings applied", "", 2000)\n'
    '                    } }\n'
    '                }\n',
    '',
    1, "remove-apply-type")

# ═══ E12: Sections — persist inside pushSectionColor; retire Apply button;
#          one caption instead of four ═══
fil = rep(fil,
    '        else if (prop === "leapFrogTextColor")  settings.leapFrogTextColor  = val\n'
    '        // Save deferred to "Apply Sections" button\n'
    '    }',
    '        else if (prop === "leapFrogTextColor")  settings.leapFrogTextColor  = val\n'
    '        settings.saveSectionColors()   // instant persist — no Apply step\n'
    '    }',
    1, "sections-persist")
fil = rep(fil,
    '                            Text { text: "→ falls back to QUILL when cleared"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }\n',
    '',
    1, "sections-row-caption")
fil = rep(fil,
    '\n                Rectangle {\n'
    '                    width: parent.width; height: 30; radius: 6\n'
    '                    border.color: fp.gilt0; border.width: 2\n'
    '                    gradient: Gradient { GradientStop { position: 0; color: fp.gilt4 } GradientStop { position: 1; color: fp.gilt3 } }\n'
    '                    Text { anchors.centerIn: parent; text: "Apply Sections"; color: fp.wine1; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }\n'
    '                    TapHandler { onTapped: { if (typeof settings.saveSectionColors === "function") settings.saveSectionColors(); notifications.notify("Filigree", "Section colours applied", "", 2000) } }\n'
    '                }\n',
    '\n                Text { text: "Changes apply and save instantly. ↺ clears a colour back to QUILL — the engine\'s own ink."\n'
    '                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm\n'
    '                       wrapMode: Text.WordWrap; width: parent.width }\n',
    1, "remove-apply-sections")

# ═══ E13–E15: Glass tab — push on colour pick, push on slider release ═══
for field in ("tint", "border", "glowColor"):
    fil = rep(fil,
        f'function(c) {{ fil._updateSurf(fil.selSurface, "{field}", c) }}',
        f'function(c) {{ fil._updateSurf(fil.selSurface, "{field}", c); fil.pushSurface(fil.selSurface) }}',
        1, f"glass-{field}")
fil = rep(fil,
    'onMoved: function(v){ fil._updateSurf(fil.selSurface, "shine", v/100) } anchors.verticalCenter: parent.verticalCenter } }',
    'onMoved: function(v){ fil._updateSurf(fil.selSurface, "shine", v/100) }\n'
    '                                onReleased: fil.pushSurface(fil.selSurface) anchors.verticalCenter: parent.verticalCenter } }',
    1, "glass-shine")
fil = rep(fil,
    'onMoved: function(v){ fil._updateSurf(fil.selSurface, "glow", v/100) } anchors.verticalCenter: parent.verticalCenter } }',
    'onMoved: function(v){ fil._updateSurf(fil.selSurface, "glow", v/100) }\n'
    '                                onReleased: fil.pushSurface(fil.selSurface) anchors.verticalCenter: parent.verticalCenter } }',
    1, "glass-glowint")
fil = rep(fil,
    '\n                Rectangle {\n'
    '                    width: parent.width; height: 30; radius: 6\n'
    '                    border.color: fp.gilt0; border.width: 2\n'
    '                    gradient: Gradient { GradientStop { position: 0; color: fp.gilt4 } GradientStop { position: 1; color: fp.gilt3 } }\n'
    '                    Text { anchors.centerIn: parent; text: "Apply Glass"; color: fp.wine1; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }\n'
    '                    TapHandler { onTapped: {\n'
    '                        // Only the surface actually being edited — pushing all three unconditionally\n'
    '                        // froze topPanel/bottomPanel/dock to whatever was in memory, defeating live\n'
    '                        // Iris Chroma tracking for surfaces the operator never touched.\n'
    '                        fil.pushSurface(fil.selSurface)\n'
    '                        notifications.notify("Filigree", "Glass settings applied", "", 2000)\n'
    '                    } }\n'
    '                }\n',
    '',
    1, "remove-apply-glass")

# ═══ E16: Widgets tab — every change pushes its own widget immediately ═══
fil = rep(fil,
    'function(c) { fil._updateWidg(fil.selWidget, "accent", c) }',
    'function(c) { fil._updateWidg(fil.selWidget, "accent", c); fil.pushWidget(fil.selWidget) }',
    1, "widg-accent")
fil = rerep(fil,
    r'function\(c\) \{ fil\._updateWidg\("(\w+)", "(glow|leading)", c\) \}',
    r'function(c) { fil._updateWidg("\1", "\2", c); fil.pushWidget("\1") }',
    12, "widg-glow-frame-set")
fil = rerep(fil,
    r'TapHandler \{ onTapped: fil\._updateWidg\("(\w+)", "(glow|leading)", ""\) \}',
    r'TapHandler { onTapped: { fil._updateWidg("\1", "\2", ""); fil.pushWidget("\1") } }',
    12, "widg-glow-frame-clear")
fil = rep(fil,
    'function(c) { fil._updateWidg(fil.selWidget, "fill", c) }',
    'function(c) { fil._updateWidg(fil.selWidget, "fill", c); fil.pushWidget(fil.selWidget) }',
    1, "widg-fill")
fil = rep(fil,
    'TapHandler { onTapped: fil._updateWidg(fil.selWidget, "fill", "") }',
    'TapHandler { onTapped: { fil._updateWidg(fil.selWidget, "fill", ""); fil.pushWidget(fil.selWidget) } }',
    1, "widg-fill-clear")
fil = rep(fil,
    'TapHandler { onTapped: { fil._updateWidg(fil.selWidget, "font", modelData) } }',
    'TapHandler { onTapped: { fil._updateWidg(fil.selWidget, "font", modelData); fil.pushWidget(fil.selWidget) } }',
    1, "widg-font")

# ═══ E17: widget glass block — same instant model as Glass tab ═══
for field in ("tint", "border", "glowColor"):
    fil = rep(fil,
        f'function(c) {{ fil._updateSurf(fil.selWidget, "{field}", c) }}',
        f'function(c) {{ fil._updateSurf(fil.selWidget, "{field}", c); fil.pushSurface(fil.selWidget) }}',
        1, f"widg-glass-{field}")
fil = rep(fil,
    'onMoved: function(v){ fil._updateSurf(fil.selWidget, "shine", v/100) } anchors.verticalCenter: parent.verticalCenter } }',
    'onMoved: function(v){ fil._updateSurf(fil.selWidget, "shine", v/100) }\n'
    '                                onReleased: fil.pushSurface(fil.selWidget) anchors.verticalCenter: parent.verticalCenter } }',
    1, "widg-glass-shine")
fil = rep(fil,
    'onMoved: function(v){ fil._updateSurf(fil.selWidget, "glow", v/100) } anchors.verticalCenter: parent.verticalCenter } }',
    'onMoved: function(v){ fil._updateSurf(fil.selWidget, "glow", v/100) }\n'
    '                                onReleased: fil.pushSurface(fil.selWidget) anchors.verticalCenter: parent.verticalCenter } }',
    1, "widg-glass-glowint")

# ═══ E18: remove "Apply Widgets" button ═══
fil = rep(fil,
    '\n                Rectangle {\n'
    '                    width: parent.width; height: 30; radius: 6\n'
    '                    border.color: fp.gilt0; border.width: 2\n'
    '                    gradient: Gradient { GradientStop { position: 0; color: fp.gilt4 } GradientStop { position: 1; color: fp.gilt3 } }\n'
    '                    Text { anchors.centerIn: parent; text: "Apply Widgets"; color: fp.wine1; font.family: fp.display; font.bold: true; font.pixelSize: SetTheme.sm }\n'
    '                    TapHandler { onTapped: {\n'
    '                        // Only the widget actually being edited — pushing all six unconditionally froze\n'
    '                        // every widget\'s accent/glass to whatever was in memory, defeating live Iris\n'
    '                        // Chroma tracking for widgets the operator never touched.\n'
    '                        fil.pushWidget(fil.selWidget); fil.pushSurface(fil.selWidget)\n'
    '                        notifications.notify("Filigree", "Widget styles applied", "", 2000)\n'
    '                    } }\n'
    '                }\n',
    '',
    1, "remove-apply-widgets")

# ═══ E19: Iris Chroma — remove the palette-authoring UI (curated paint model:
#          NCDE curates the pigments; the user picks, never mixes). Engine
#          save/delete/list API stays for the future. ═══
start = fil.find("                // ── My Palettes — the user's own saved Iris Chroma creations")
end = fil.find('                Text {\n                    leftPadding: 10\n                    text: "IRIS CHROMA — 90 Curated Palettes"')
if start == -1 or end == -1 or end <= start:
    fails.append(f"ANCHOR FAIL [iris-remove-authoring]: start={start} end={end}")
else:
    removed = fil[start:end]
    for must in ("MY PALETTES", "Save Current", "myPalettesRepeater", "deleteBtn"):
        if must not in removed:
            fails.append(f"SANITY FAIL [iris-remove-authoring]: '{must}' not inside removed block")
    fil = fil[:start] + fil[end:]

if fails:
    print("\n".join(fails)); sys.exit(1)

(W / "FiligreeTab.qml").write_text(fil)
(W / "NCDESlider.qml").write_text(sld)
print("ALL EDITS APPLIED CLEANLY")
