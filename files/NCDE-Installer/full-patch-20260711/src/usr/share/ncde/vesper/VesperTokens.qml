import QtQuick

// VesperTokens — Vesper's COLD GREEN PHOSPHOR identity. Deliberately unlike the
// rest of NCDE (parchment/gold); the contrast is the signal. Respects global
// accessibility: pass uiScale / highContrast from Lelan and sizes follow.
QtObject {
    id: t
    // global a11y inputs (bound from Lelan by the wiring layer)
    property real uiScale: 1.0
    property bool highContrast: false

    // --- green phosphor palette ---
    readonly property color ground:  "#020608"            // near-black CRT ground
    readonly property color ground2: "#04100c"
    readonly property color p:        highContrast ? "#86ffce" : "#5fffba"   // phosphor
    readonly property color pHi:      "#c4ffe6"            // bright text
    readonly property color pDim:     highContrast ? "#3fae86" : "#1f8a5e"   // labels/rules
    readonly property color glow:     Qt.rgba(0.37, 1.0, 0.73, 0.5)
    readonly property color amber:    "#ffd789"            // sparingly: warnings only
    readonly property color danger:   "#ff8f6a"            // serious threat accent (calm, not siren red)

    // --- type --- (JetBrains Mono is in the NCDE font set)
    readonly property string mono: "JetBrains Mono"
    function fs(px){ return Math.round(px * uiScale); }    // accessible sizing helper
    readonly property int  body:   fs(18)
    readonly property int  small:  fs(12)
    readonly property int  title:  fs(34)

    // --- spacing ---
    readonly property int  pad:    fs(22)
    readonly property real radius: 12
}
