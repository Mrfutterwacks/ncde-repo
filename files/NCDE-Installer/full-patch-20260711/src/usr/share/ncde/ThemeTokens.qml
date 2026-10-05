import QtQuick 2.15

QtObject {
    // ── Font families ─────────────────────────────────────────────
    readonly property string fontFamily: settings.fontFamily || "Noto Sans"
    readonly property string titleFont:  ncde.titleFont      || "Cinzel"
    readonly property string fixedFont:  ncde.monoFont       || "TerminalVector"
    readonly property double fontSizeScale: settings.fontSizeScale || 1.0
    readonly property double uiScale: settings.uiScale || 1.0

    // ── A11y scale (unified: matches SetTheme.acc = fontSizeScale × uiScale) ──
    readonly property double acc: (typeof settings !== "undefined" && settings.fontSizeScale > 0 ? settings.fontSizeScale : 1.0)
                                * (typeof settings !== "undefined" && settings.uiScale > 0 ? settings.uiScale : 1.0)
    readonly property double fontSmall:  Math.round(ncde.fontSize_sm * acc)
    readonly property double fontMedium: Math.round(ncde.fontSize_md * acc)
    readonly property double fontLarge:  Math.round(ncde.fontSize_lg * acc)

    // ── Typography ────────────────────────────────────────────────
    readonly property double letterSpacing: (settings.letterSpacing || 0.0) * uiScale
    readonly property double lineHeight: (settings.lineHeight > 0) ? settings.lineHeight : 1.0

    // When a preset is active, its ink (ncde.panelText) overrides any saved text color
    // so that palette changes propagate system-wide. Custom text color only applies
    // in free-form (no preset) mode.
    readonly property color textColor: (!ncde.presetActive && settings.textColor) ? settings.textColor : ncde.panelText

    // ── Font weight & style ───────────────────────────────────────
    readonly property int  fontWeight:  settings.fontWeight  || 400
    readonly property bool fontItalic:  settings.fontItalic  || false

    // ── Text outline ─────────────────────────────────────────────
    readonly property bool   textOutlineEnabled: settings.textOutlineEnabled || false
    readonly property color  textOutlineColor:   settings.textOutlineColor ? settings.textOutlineColor : ncde.panelBg
    readonly property real   textOutlineWidth:   settings.textOutlineWidth  || 1.0

    // ── Text shadow / depth ──────────────────────────────────────
    readonly property bool   textShadowEnabled:  settings.textShadowEnabled  || false
    readonly property color  textShadowColor:    settings.textShadowColor ? settings.textShadowColor : Qt.rgba(0, 0, 0, 0.8)
    readonly property real   textShadowRadius:   settings.textShadowRadius  || 4.0
    readonly property real   textShadowOffsetX:  settings.textShadowOffsetX || 1.0
    readonly property real   textShadowOffsetY:  settings.textShadowOffsetY || 1.0

    // ── Computed helpers ─────────────────────────────────────────
    readonly property int    textStyle:      textOutlineEnabled ? Text.Outline : Text.Normal
    readonly property color  textStyleColor: textOutlineColor

    function scale(v) { return v * uiScale; }
}
