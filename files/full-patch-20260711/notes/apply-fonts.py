#!/usr/bin/env python3
# Filigree Fonts tab refinement + ThemeTokens lineHeight export (2026-07-21).
# Anchored edits: every anchor must match EXACTLY the expected number of times
# or the whole script aborts without writing (proven Filigree method).
import sys, os

D = os.path.dirname(os.path.abspath(__file__))
edits_done = []

def load(p): return open(p).read()
def save(p, s): open(p, "w").write(s)

def apply(src, anchor, replacement, count=1, label=""):
    n = src.count(anchor)
    if n != count:
        print(f"ABORT: anchor for [{label}] matched {n}x (expected {count})")
        print(f"  anchor: {anchor[:120]!r}")
        sys.exit(1)
    edits_done.append(label)
    return src.replace(anchor, replacement)

# ═════════ ThemeTokens.qml ═════════
tt = load(os.path.join(D, "ThemeTokens.qml"))
# NOTE (post-gate correction): ThemeTokens ALREADY exported lineHeight (fallback
# 1.2, zero consumers). The first cut of this script INSERTED a second export —
# a duplicate-property hard compile error the ThemeTokens create-gate caught.
# Correct edit: replace the existing line, normalising the dead fallback to 1.0.
tt = apply(tt,
    "    readonly property double lineHeight: settings.lineHeight || 1.2",
    "    // Leading (2026-07-21): theme.lineHeight existed but had ZERO consumers — the\n"
    "    // Filigree Leading slider was a shell-wide no-op. Dead fallback normalised\n"
    "    // 1.2 -> 1.0 (neutral = QML default); wired into wrapped body text by the\n"
    "    // same-day sweep.\n"
    "    readonly property double lineHeight: (settings.lineHeight > 0) ? settings.lineHeight : 1.0",
    label="ThemeTokens lineHeight normalise")
save(os.path.join(D, "ThemeTokens.qml"), tt)

# ═════════ FiligreeTab.qml ═════════
f = load(os.path.join(D, "FiligreeTab.qml"))

# (a) installed-font list cached once on the root object (validation + chips)
f = apply(f,
    '    readonly property var widgetFonts:  ["Cinzel","Cormorant Garamond","EB Garamond","IM Fell English"]',
    '    readonly property var widgetFonts:  ["Cinzel","Cormorant Garamond","EB Garamond","IM Fell English"]\n'
    '    // Installed families, read once (Qt.fontFamilies walks fontconfig — do not re-bind)\n'
    '    readonly property var _installedFonts: Qt.fontFamilies()',
    label="root _installedFonts")

# (b) SERIF chip list gains the NCDE-default serif so users can find their way back
f = apply(f,
    'model: ["Noto Serif","Liberation Serif","DejaVu Serif","FreeSerif","EB Garamond"]',
    'model: ["Cormorant Garamond","Noto Serif","Liberation Serif","DejaVu Serif","FreeSerif","EB Garamond"]',
    label="serif list + Cormorant Garamond")

# (c) chips: uniform 26px pill, name in Cinzel + fixed-size "Aa" specimen in the
# font's own face. All three groups (sans bfs1 / serif bfs2 / mono bfs3).
for gid in ("bfs1", "bfs2", "bfs3"):
    f = apply(f,
        f'''                            height: 24; radius: 5; width: {gid}.implicitWidth + 14
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Text {{ id: {gid}; anchors.centerIn: parent; text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }}''',
        f'''                            height: 26; radius: 5; width: {gid}.implicitWidth + 16
                            border.color: on ? fp.gilt0 : fp.gilt1; border.width: 1
                            color: on ? fp.gilt4 : fp.paper0
                            Row {{
                                id: {gid}; anchors.centerIn: parent; spacing: 6
                                Text {{ text: "Aa"; font.family: modelData; font.pixelSize: SetTheme.md; color: fp.gilt3; anchors.verticalCenter: parent.verticalCenter }}
                                Text {{ text: modelData; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink; anchors.verticalCenter: parent.verticalCenter }}
                            }}''',
        label=f"chip specimen {gid}")

# (d) Custom row: align label to the 78px column + not-installed hint below
f = apply(f,
    '''                    Text { text: "Custom"; width: 50; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: parent.width - 60; height: 26; radius: 5''',
    '''                    Text { text: "Custom"; width: 78; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: parent.width - 88; height: 26; radius: 5''',
    label="custom row 78px label")

f = apply(f,
    '''                            onEditingFinished: { settings.fontFamily = text; settings.saveFontSettings(); settings.applyFontSettings() }
                        }
                    }
                }''',
    '''                            onEditingFinished: { settings.fontFamily = text; settings.saveFontSettings(); settings.applyFontSettings() }
                        }
                    }
                }
                Text {
                    visible: fil._installedFonts.indexOf(settings.fontFamily) === -1
                    text: "\\u201C" + settings.fontFamily + "\\u201D isn\\u2019t installed \\u2014 the closest installed face is shown instead."
                    color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm
                    wrapMode: Text.WordWrap; width: parent.width
                }''',
    label="custom font validation hint")

# (e) Reset Typography pill after the Italic row
f = apply(f,
    '''                        Text { anchors.centerIn: parent; text: parent.on ? "On" : "Off"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                        TapHandler { onTapped: { settings.fontItalic = !settings.fontItalic; settings.saveFontSettings(); settings.applyFontSettings() } }
                    }
                }''',
    '''                        Text { anchors.centerIn: parent; text: parent.on ? "On" : "Off"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.ink }
                        TapHandler { onTapped: { settings.fontItalic = !settings.fontItalic; settings.saveFontSettings(); settings.applyFontSettings() } }
                    }
                }
                Row {
                    width: parent.width; spacing: 10
                    Item { width: 78; height: 1 }
                    Rectangle {
                        property bool atDefault: settings.fontFamily === "Noto Sans" && settings.fontWeight === 400
                                                 && !settings.fontItalic && Math.abs(settings.letterSpacing) < 0.05
                                                 && Math.abs((settings.lineHeight > 0 ? settings.lineHeight : 1.0) - 1.0) < 0.05
                        height: 26; radius: 13; width: rstTypo.implicitWidth + 22
                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5
                        opacity: atDefault ? 0.45 : 1.0
                        Text { id: rstTypo; anchors.centerIn: parent; text: "Reset Typography"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }
                        TapHandler { onTapped: {
                            settings.fontFamily = "Noto Sans"; settings.fontWeight = 400; settings.fontItalic = false
                            settings.letterSpacing = 0.0; settings.lineHeight = 1.0
                            settings.saveFontSettings(); settings.applyFontSettings()
                        } }
                    }
                    Text { text: "Family, weight, italic, spacing, leading \\u2014 back to NCDE defaults."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }''',
    label="reset typography pill")

# (f) MEASURE sample: two lines, live letterSpacing + lineHeight feedback
f = apply(f,
    '''                Rectangle {
                    width: parent.width; height: 44; radius: 6; clip: true
                    color: Qt.rgba(0,0,0,0.03); border.color: fp.gilt1; border.width: 1
                    Text {
                        anchors.centerIn: parent
                        text: "The quick brown fox jumps — 1234"
                        color: fp.ink; font.family: settings.fontFamily; font.weight: settings.fontWeight
                        font.italic: settings.fontItalic; font.pixelSize: SetTheme.md
                    }
                }''',
    '''                Rectangle {
                    width: parent.width; height: 72; radius: 6; clip: true
                    color: Qt.rgba(0,0,0,0.03); border.color: fp.gilt1; border.width: 1
                    Text {
                        anchors.centerIn: parent; horizontalAlignment: Text.AlignHCenter
                        text: "The quick brown fox jumps over the lazy dog\\n1234567890 \\u2014 AaBbCcDdEe"
                        color: fp.ink; font.family: settings.fontFamily; font.weight: settings.fontWeight
                        font.italic: settings.fontItalic; font.pixelSize: SetTheme.md
                        font.letterSpacing: settings.letterSpacing
                        lineHeight: settings.lineHeight > 0 ? settings.lineHeight : 1.0
                    }
                }''',
    label="measure sample live spacing/leading")

# (g) TEXT RENDERING preview lines also honour letterSpacing (3 lines)
f = apply(f,
    "font.weight: settings.fontWeight; font.italic: settings.fontItalic; color: settings.textColor",
    "font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: settings.letterSpacing; color: settings.textColor",
    count=3, label="render preview letterSpacing x3")

# (h) Terminal FONT row moves from the Glass tab into the Fonts tab. The tint
# slider (and termRow with cfg/refresh) stays in Glass; QML ids are
# document-scoped so refresh() still reaches the moved input.
f = apply(f,
    '''                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Font"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: 220; height: 30; radius: 6; color: fp.paper0; border.color: fp.gilt1; border.width: 1
                        anchors.verticalCenter: parent.verticalCenter
                        TextInput {
                            id: termFontInput
                            anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                            color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm
                            text: termRow.cfg.fontFamily !== undefined ? termRow.cfg.fontFamily : "monospace"
                            onEditingFinished: ncde.setTerminalFont(text)
                        }
                    }
                    Text { text: "e.g. JetBrains Mono"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                Item { width: 1; height: 8 }
            }
''',
    '''                Item { width: 1; height: 8 }
            }
''',
    label="terminal font row removed from Glass")

# (i) NCDE SIGNATURE FONTS: cut from between BODY FONT and MEASURE...
sig_block = '''                // ── NCDE SIGNATURE FONTS ──────────────────────────────────
                Rule { text: "NCDE SIGNATURE FONTS" }
                Rectangle {
                    width: parent.width; radius: 7; border.color: fp.gilt1; border.width: 1
                    color: Qt.rgba(0,0,0,0.03)
                    height: sigCol.height + 18
                    Column {
                        id: sigCol
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.top: parent.top; anchors.margins: 10; spacing: 6
                        Text { text: "NCDE's visual identity — not user-configurable."; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                        Repeater {
                            model: [
                                {role:"Display",    f:"Cinzel Decorative"},
                                {role:"Titles",     f:"Cinzel"},
                                {role:"Serif",      f:"Cormorant Garamond"},
                                {role:"Body Serif", f:"EB Garamond"},
                                {role:"Accent",     f:"IM Fell English"},
                                {role:"Mono",       f:"TerminalVector"}
                            ]
                            Row {
                                spacing: 10
                                Text { text: modelData.role; width: 80; color: fp.gilt1; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                                Text { text: modelData.f; color: fp.ink; font.family: modelData.f; font.pixelSize: SetTheme.md }
                            }
                        }
                    }
                }

'''
f = apply(f, sig_block, "", label="signature block cut")

# ...and re-insert at the end of the Fonts tab, after a new TERMINAL section
# holding the relocated font row. The type tab currently ends with the shadow
# Offset Y row followed by its closing spacer.
f = apply(f,
    '''                    Text { text: settings.textShadowOffsetY.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                Item { width: 1; height: 8 }
            }
''',
    '''                    Text { text: settings.textShadowOffsetY.toFixed(1) + "px"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

                // ── TERMINAL ──────────────────────────────────────────────
                // Relocated from the Glass tab 2026-07-21 so every font on the
                // system is controlled from this one tab. The glass-tint slider
                // stays in Glass (it is a material control, not a font one).
                Rule { text: "TERMINAL" }
                Text { text: "ncde-terminal\\u2019s own face \\u2014 separate from the shell body font above."
                       color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm }
                Row {
                    width: parent.width; spacing: 10
                    Text { text: "Font"; width: 78; color: fp.ink; font.family: fp.titles; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                    Rectangle {
                        width: 220; height: 30; radius: 6; color: fp.paper0; border.color: fp.gilt1; border.width: 1
                        anchors.verticalCenter: parent.verticalCenter
                        TextInput {
                            id: termFontInput
                            anchors.fill: parent; anchors.margins: 6; verticalAlignment: TextInput.AlignVCenter
                            color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm
                            text: termRow.cfg.fontFamily !== undefined ? termRow.cfg.fontFamily : "monospace"
                            onEditingFinished: ncde.setTerminalFont(text)
                        }
                    }
                    Text { text: "e.g. JetBrains Mono"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; anchors.verticalCenter: parent.verticalCenter }
                }

''' + sig_block + '''                Item { width: 1; height: 8 }
            }
''',
    label="terminal + signature re-inserted in Fonts tab")

# (j) Glass tab explainer no longer describes two controls
f = apply(f,
    'Text { text: "ncde-terminal is its own material — tintable, but never light/dark-adaptive. These two are manual accessibility overrides."',
    'Text { text: "ncde-terminal is its own material — tintable, but never light/dark-adaptive. This brightness override is a manual accessibility control; its font moved to the Fonts tab."',
    label="glass explainer reworded")

# (k) Glass tab also refreshes terminal cfg when it becomes visible (the old
# hook only fired on the Fonts tab, so Glass showed stale tint after external
# config changes)
f = apply(f,
    '''            Column {
                visible: fil._activeTab === "glass"
                width: parent.width; spacing: 14
''',
    '''            Column {
                visible: fil._activeTab === "glass"
                onVisibleChanged: if (visible) termRow.refresh()
                width: parent.width; spacing: 14
''',
    label="glass tab refresh hook")

save(os.path.join(D, "FiligreeTab.qml"), f)
print("ALL EDITS APPLIED:")
for e in edits_done: print(" ✓", e)
