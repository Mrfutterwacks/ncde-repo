// VerdantKit.qml — standalone palette for VerdantFolio (no shell context).
// Standalone outside LaPivot: NCDEKit pulls shell singletons (qmldir)
// SetTheme/WallInk which reference `ncde`/`settings` unguarded, so bare
// `qml6 -I UI UI/Main.qml` exits "Did not load any objects".
// This kit has zero singleton deps: same fallback values as NCDEKit.qml dark base.
import QtQuick 2.15

QtObject {
    id: k
    readonly property color panelBg: "#0c0907"
    readonly property color panelBg2: "#171009"
    readonly property color surface: "#171009"
    readonly property color surface2: "#241a10"
    readonly property color surfaceHi: "#e9c97c"
    readonly property color ink: "#e8dcc8"
    readonly property color inkDim: "#a89a7c"
    readonly property color inkSoft: "#c9bb9a"
    readonly property color gilt0: "#5a3a14"
    readonly property color gilt4: "#e9c97c"
    readonly property color accent: "#3a7a5e"
    readonly property color accentSoft: "#5a9a7e"
    readonly property color shade: "#0a0705"
    readonly property color metal: "#8a5a20"
    readonly property color metalWarm: "#b07a30"
    readonly property color metalShine: "#f6e3b0"
    readonly property color metalCame: "#2a1e0e"
}
