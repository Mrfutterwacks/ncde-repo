#!/usr/bin/env python3
"""Filigree Phase 2 — active-palette indicator, full-opacity cards, reset-to-100% chips,
accessibility-multiplier notice, real inkSoft, terminal-row refresh.
Anchored edits: every replacement must match EXACTLY the expected count or we abort.
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

# ═══ E-e: real inkSoft — captions actually read soft (SetTheme pattern, 0.65 alpha) ═══
fil = rep(fil,
    "        readonly property color ink:ncde.foreground; readonly property color inkSoft:ncde.foreground",
    "        readonly property color ink:ncde.foreground\n"
    "        // soft captions for real (was === ink): SetTheme.inkSoft pattern, 0.65 alpha\n"
    "        readonly property color inkSoft:Qt.rgba(ncde.foreground.r, ncde.foreground.g, ncde.foreground.b, 0.65)",
    1, "inkSoft")

# ═══ E-a1: irisCol tracks the active palette name (updates on themeChanged) ═══
fil = rep(fil,
    "            Column {\n"
    "                id: irisCol\n"
    "                visible: fil._activeTab === \"iris\"\n"
    "                width: parent.width\n"
    "                spacing: 0\n",
    "            Column {\n"
    "                id: irisCol\n"
    "                visible: fil._activeTab === \"iris\"\n"
    "                width: parent.width\n"
    "                spacing: 0\n"
    "\n"
    "                // active palette = engine accentName (same identity Style Manager and\n"
    "                // main.qml's reapplyActivePreset use); kept fresh via themeChanged so\n"
    "                // changes made elsewhere (Style Manager) reflect here too.\n"
    "                property string activeName: ncde.accentName\n"
    "                Connections { target: ncde; function onThemeChanged() { irisCol.activeName = ncde.accentName } }\n",
    1, "iris-activename")

# ═══ E-a2/E-b: card — active border + full-opacity idle, hover = border highlight ═══
fil = rep(fil,
    "                                    color: irisCardTap.pressed ? fp.gilt3 : fp.paper1\n"
    "                                    border.color: fp.gilt1; border.width: 1\n"
    "                                    opacity: irisCardHover.hovered ? 1.0 : 0.65\n",
    "                                    readonly property bool isActive: irisCol.activeName === pd.name\n"
    "                                    color: irisCardTap.pressed ? fp.gilt3 : fp.paper1\n"
    "                                    border.color: isActive ? fp.gilt4 : (irisCardHover.hovered ? fp.gilt3 : fp.gilt1)\n"
    "                                    border.width: isActive ? 2 : 1\n",
    1, "iris-card")

# ═══ E-a3: active badge + instant activeName update on tap ═══
fil = rep(fil,
    "                                    TapHandler { id: irisCardTap; onTapped: { ncde.applyPreset(irisCard.pd.id); saveTheme(); notifications.notify(\"Filigree\", \"Theme changed: \" + irisCard.pd.name, \"\", 2000) } }\n",
    "                                    Rectangle {\n"
    "                                        visible: irisCard.isActive\n"
    "                                        width: 16; height: 16; radius: 8\n"
    "                                        anchors.top: parent.top; anchors.right: parent.right\n"
    "                                        anchors.topMargin: 4; anchors.rightMargin: 4\n"
    "                                        color: fp.gilt4; border.color: fp.wine2; border.width: 1\n"
    "                                        Text { anchors.centerIn: parent; text: \"\\u2713\"; color: fp.wine1; font.bold: true; font.pixelSize: SetTheme.sm - 1 }\n"
    "                                    }\n"
    "                                    TapHandler { id: irisCardTap; onTapped: { ncde.applyPreset(irisCard.pd.id); saveTheme(); irisCol.activeName = irisCard.pd.name; notifications.notify(\"Filigree\", \"Theme changed: \" + irisCard.pd.name, \"\", 2000) } }\n",
    1, "iris-badge")

# ═══ E-c1: Reset-to-100% chip — Text Size ═══
fil = rep(fil,
    "                    Text { text: Math.round(settings.fontSizeScale * 100) + \"%\"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }\n",
    "                    Text { text: Math.round(settings.fontSizeScale * 100) + \"%\"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }\n"
    "                    Rectangle {\n"
    "                        height: 26; radius: 13; width: rstText.implicitWidth + 22\n"
    "                        anchors.verticalCenter: parent.verticalCenter\n"
    "                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5\n"
    "                        opacity: Math.round(settings.fontSizeScale * 100) === 100 ? 0.45 : 1.0\n"
    "                        Text { id: rstText; anchors.centerIn: parent; text: \"Reset to 100%\"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }\n"
    "                        TapHandler { onTapped: { settings.fontSizeScale = 1.0; settings.saveFontSettings(); settings.applyFontSettings(); textSizeSlider.value = 100 } }\n"
    "                    }\n",
    1, "reset-textsize")

# ═══ E-c2: Reset-to-100% chip — Interface Scale ═══
fil = rep(fil,
    "                    Text { text: Math.round(settings.uiScale * 100) + \"%\"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }\n",
    "                    Text { text: Math.round(settings.uiScale * 100) + \"%\"; color: fp.ink; font.family: fp.mono; font.pixelSize: SetTheme.sm; width: 44; anchors.verticalCenter: parent.verticalCenter }\n"
    "                    Rectangle {\n"
    "                        height: 26; radius: 13; width: rstUi.implicitWidth + 22\n"
    "                        anchors.verticalCenter: parent.verticalCenter\n"
    "                        color: fp.paper0; border.color: fp.gilt1; border.width: 1.5\n"
    "                        opacity: Math.round(settings.uiScale * 100) === 100 ? 0.45 : 1.0\n"
    "                        Text { id: rstUi; anchors.centerIn: parent; text: \"Reset to 100%\"; font.family: fp.titles; font.pixelSize: SetTheme.sm; color: fp.inkSoft }\n"
    "                        TapHandler { onTapped: { settings.uiScale = 1.0; settings.saveFontSettings(); settings.applyFontSettings(); uiScaleSlider.value = 100 } }\n"
    "                    }\n",
    1, "reset-uiscale")

# ═══ E-d: accessibility-multiplier notice (third stacked multiplier, else invisible here) ═══
fil = rep(fil,
    "                Text { text: \"Resizes the whole interface, including text — layers on top of Text Size above.\"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; wrapMode: Text.WordWrap; width: parent.width\n"
    "                }\n",
    "                Text { text: \"Resizes the whole interface, including text — layers on top of Text Size above.\"; color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm; wrapMode: Text.WordWrap; width: parent.width\n"
    "                }\n"
    "                Text {\n"
    "                    visible: settings.accessibilityTextScale > 0 && Math.abs(settings.accessibilityTextScale - 1.0) > 0.001\n"
    "                    text: \"Note: an Accessibility text scale of \" + Math.round(settings.accessibilityTextScale * 100) + \"% is also active (Settings \\u2192 Accessibility). It multiplies on top of both sliders here.\"\n"
    "                    color: fp.inkSoft; font.family: fp.fell; font.italic: true; font.pixelSize: SetTheme.sm\n"
    "                    wrapMode: Text.WordWrap; width: parent.width\n"
    "                }\n",
    1, "acc-notice")

# ═══ E-f1: terminal row — refresh() re-reads config + resyncs controls ═══
fil = rep(fil,
    "                Row {\n"
    "                    id: termRow\n"
    "                    width: parent.width; spacing: 10\n"
    "                    property var cfg: ncde.terminalConfig()\n",
    "                Row {\n"
    "                    id: termRow\n"
    "                    width: parent.width; spacing: 10\n"
    "                    property var cfg: ncde.terminalConfig()\n"
    "                    // one-shot binding goes stale if ncde-terminal's config changes while\n"
    "                    // another tab is up — re-read every time the Type tab becomes visible\n"
    "                    function refresh() {\n"
    "                        cfg = ncde.terminalConfig()\n"
    "                        termTintSlider.value = (cfg.glassTint !== undefined ? cfg.glassTint : 0) * 100\n"
    "                        termFontInput.text = cfg.fontFamily !== undefined ? cfg.fontFamily : \"monospace\"\n"
    "                    }\n",
    1, "term-refresh")

# ═══ E-f2: tint slider gets an id so refresh() can resync a broken-by-drag binding ═══
fil = rep(fil,
    "                    NCDESlider {\n"
    "                        minValue: 0; maxValue: 100\n"
    "                        value: (termRow.cfg.glassTint !== undefined ? termRow.cfg.glassTint : 0) * 100\n",
    "                    NCDESlider {\n"
    "                        id: termTintSlider\n"
    "                        minValue: 0; maxValue: 100\n"
    "                        value: (termRow.cfg.glassTint !== undefined ? termRow.cfg.glassTint : 0) * 100\n",
    1, "term-slider-id")

# ═══ E-f3: Type tab re-entry triggers the refresh ═══
fil = rep(fil,
    "                visible: fil._activeTab === \"type\"\n",
    "                visible: fil._activeTab === \"type\"\n"
    "                onVisibleChanged: if (visible) termRow.refresh()\n",
    1, "type-visible")

if fails:
    print("\n".join(fails)); sys.exit(1)
(W / "FiligreeTab.qml").write_text(fil)
print("ALL PHASE-2 EDITS APPLIED:", len(fil.splitlines()), "lines")
