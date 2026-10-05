// SetTheme.qml — shared NCDE-settings palette + fonts (singleton).
// pragma Singleton; registered in qmldir: singleton SetTheme 1.0 SetTheme.qml
pragma Singleton
import QtQuick 2.15

QtObject {
    // ── Paper tones — parchment backgrounds ──────────────────────────
    // Light: ramp from ncde.surface (wallpaper-warm cream).
    // Dark: ramp from ncde.panelBg (deep shell surface).
    // Lélan: pure bindings — no Timer; re-evaluates on themeChanged.
    readonly property color paper0: ncde.darkMode
        ? Qt.lighter(ncde.panelBg, 1.50) : Qt.lighter(ncde.surface, 1.20)
    readonly property color paper1: ncde.darkMode
        ? Qt.lighter(ncde.panelBg, 1.25) : Qt.lighter(ncde.surface, 1.10)
    readonly property color paper2: ncde.darkMode
        ? Qt.lighter(ncde.panelBg, 1.10) : ncde.surface
    readonly property color paper3: ncde.darkMode
        ? ncde.panelBg : Qt.darker(ncde.surface, 1.08)

    // gilt (FRV-1 — engine-driven, fallback to Belle Époque amber)
    readonly property color gilt0: (typeof ncde !== "undefined" && ncde.gilt0 !== undefined) ? ncde.gilt0 : "#5a3a14"
    readonly property color gilt1: (typeof ncde !== "undefined" && ncde.gilt1 !== undefined) ? ncde.gilt1 : "#8a5a20"
    readonly property color gilt2: (typeof ncde !== "undefined" && ncde.gilt2 !== undefined) ? ncde.gilt2 : "#b07a30"
    readonly property color gilt3: (typeof ncde !== "undefined" && ncde.gilt3 !== undefined) ? ncde.gilt3 : "#c98a3a"
    readonly property color gilt4: (typeof ncde !== "undefined" && ncde.gilt4 !== undefined) ? ncde.gilt4 : "#e9c97c"
    readonly property color gilt5: (typeof ncde !== "undefined" && ncde.gilt5 !== undefined) ? ncde.gilt5 : "#f6e3b0"

    // wine + accent variants (FRV-1 — engine-driven, fallback to Art Nouveau burgundy)
    readonly property color wine1: (typeof ncde !== "undefined" && ncde.wine1 !== undefined) ? ncde.wine1 : "#2a0612"
    readonly property color wine2: (typeof ncde !== "undefined" && ncde.wine2 !== undefined) ? ncde.wine2 : "#4a0e22"
    readonly property color wine3: (typeof ncde !== "undefined" && ncde.wine3 !== undefined) ? ncde.wine3 : "#6e1832"
    readonly property color wine4: (typeof ncde !== "undefined" && ncde.wine4 !== undefined) ? ncde.wine4 : "#8b1e3f"
    readonly property color verd:   (typeof ncde !== "undefined" && ncde.verd !== undefined) ? ncde.verd : "#3a7a5e"
    readonly property color cer:    (typeof ncde !== "undefined" && ncde.cer !== undefined) ? ncde.cer : "#2f8aa0"
    readonly property color amber:  (typeof ncde !== "undefined" && ncde.amber !== undefined) ? ncde.amber : "#d99a3a"
    readonly property color rose:   (typeof ncde !== "undefined" && ncde.rose !== undefined) ? ncde.rose : "#c64b63"

    // ── Ink tones — text colors ────────────────────────────────────
    // ncde.panelText = warm sepia (#2a1e0e) in light, warm parchment (#e8dcc8) in dark.
    readonly property color ink:    ncde.panelText
    readonly property color inkSoft: Qt.rgba(ncde.panelText.r, ncde.panelText.g, ncde.panelText.b, 0.65)
    readonly property color inkDim:  Qt.rgba(ncde.panelText.r, ncde.panelText.g, ncde.panelText.b, 0.40)
    readonly property color inkLabel: ncde.darkMode ? gilt4 : gilt1

    // ── Font sizes — scale-aware, mirror engine so all Settings tabs share one binding ──
    // A11y fix 2026-07-09: the engine's recomputeFontSizes() only multiplies
    // fontSizeScale × uiScale — settings.accessibilityTextScale is saved but never
    // read, so the Accessibility "Text scale" slider did nothing. Fold it in here.
    // Script Shift (2026-09-24): ncde.fontSize_* already carry the one text dial
    // (fontSizeScale; uiScale retired at 1), so multiplying by accessibilityTextScale
    // here too would double it. `acc` stays as the Settings panel's grow-to-fit factor
    // (SettingsPanel.qml sizes its window/rail by it) and now tracks Script Shift.
    readonly property double acc: (typeof settings !== "undefined" && settings.fontSizeScale > 0 ? settings.fontSizeScale : 1.0)
                                * (typeof settings !== "undefined" && settings.uiScale > 0 ? settings.uiScale : 1.0)
    readonly property double sm: ncde.fontSize_sm
    readonly property double md: ncde.fontSize_md
    readonly property double lg: ncde.fontSize_lg

    // font roles (FRV-2 — engine-driven, fallback to NCDE-aesthetic defaults)
    readonly property string display: (typeof ncde !== "undefined" && ncde.displayFont) ? ncde.displayFont : "Cinzel Decorative"
    readonly property string titles:  (typeof ncde !== "undefined" && ncde.titleFont)   ? ncde.titleFont   : "Cinzel"
    readonly property string serif:   (typeof ncde !== "undefined" && ncde.bodyFont)    ? ncde.bodyFont    : "Cormorant Garamond"
    readonly property string fell:    "IM Fell English"
    readonly property string gar:     "EB Garamond"
    readonly property string mono:    (typeof ncde !== "undefined" && ncde.monoFont)    ? ncde.monoFont    : "TerminalVector"
}
