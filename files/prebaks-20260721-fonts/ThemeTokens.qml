import QtQuick 2.15

QtObject {
    // Expose computed theme tokens derived from settings
    readonly property string fontFamily: settings.fontFamily || "Noto Sans"
    readonly property string titleFont:  ncde.titleFont      || "Cinzel"
    readonly property string fixedFont:  ncde.monoFont       || "TerminalVector"
    readonly property double fontSizeScale: settings.fontSizeScale || 1.0
    readonly property double uiScale: settings.uiScale || 1.0

    // Base sizes in points
    readonly property double baseSmall: 11
    readonly property double baseMedium: 13
    readonly property double baseLarge: 16

    // A11y fix 2026-07-19: mirror SetTheme.qml's acc fold-in — this is the global
    // `theme` context property every non-Settings QML file reads fonts from, and it
    // was skipping settings.accessibilityTextScale entirely (SetTheme.qml only fixed
    // the Settings-tab copy). See ncde-power-menu-font-fix session notes.
    readonly property double acc: (typeof settings !== "undefined" && settings.accessibilityTextScale > 0) ? settings.accessibilityTextScale : 1.0
    readonly property double fontSmall:  Math.round(ncde.fontSize_sm * acc)
    readonly property double fontMedium: Math.round(ncde.fontSize_md * acc)
    readonly property double fontLarge:  Math.round(ncde.fontSize_lg * acc)

    readonly property double letterSpacing: (settings.letterSpacing || 0.0) * uiScale
    readonly property double lineHeight: settings.lineHeight || 1.2

    // When a preset is active, its ink (ncde.panelText) overrides any saved text color
    // so that palette changes propagate system-wide. Custom text color only applies
    // in free-form (no preset) mode.
    readonly property color textColor: (!ncde.presetActive && settings.textColor) ? settings.textColor : ncde.panelText

    // ── Font weight & style ───────────────────────────────────────
    readonly property int  fontWeight:  settings.fontWeight  || 400
    readonly property bool fontItalic:  settings.fontItalic  || false

    // ── Text outline ─────────────────────────────────────────────
    // Smart default: outline color = panel background (contrasts with text on any surface)
    readonly property bool   textOutlineEnabled: settings.textOutlineEnabled || false
    readonly property color  textOutlineColor:   settings.textOutlineColor ? settings.textOutlineColor : ncde.panelBg
    readonly property real   textOutlineWidth:   settings.textOutlineWidth  || 1.0

    // Computed helpers — bind style: theme.textStyle; styleColor: theme.textStyleColor on any Text
    readonly property int    textStyle:      textOutlineEnabled ? Text.Outline : Text.Normal
    readonly property color  textStyleColor: textOutlineColor

    // ── Text shadow / depth ──────────────────────────────────────
    // Smart default: 80% black — legible on light and dark glass
    readonly property bool   textShadowEnabled:  settings.textShadowEnabled  || false
    readonly property color  textShadowColor:    settings.textShadowColor ? settings.textShadowColor : Qt.rgba(0, 0, 0, 0.8)
    readonly property real   textShadowRadius:   settings.textShadowRadius  || 4.0
    readonly property real   textShadowOffsetX:  settings.textShadowOffsetX || 1.0
    readonly property real   textShadowOffsetY:  settings.textShadowOffsetY || 1.0

    function scale(v) { return v * uiScale; }
}
