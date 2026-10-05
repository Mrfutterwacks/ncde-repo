// NCDESlider.qml — gilt channel, wine fill, brass knob (Tap + Drag).
import QtQuick 2.15

Item {
    id: sl
    property real minValue: 0
    property real maxValue: 100
    property real value: 50
    property string accessibleName: ""
    property real stepSize: (maxValue - minValue) / 20
    property var snapValues: []  // optional; when non-empty, drag/tap snap to the nearest listed value
    signal moved(real value)
    signal released()  // drag ended / tap done — persist-on-release hook
    // height 26 (was 22): Tap/DragHandlers live on this root item, so implicitHeight
    // IS the hit-target height — 22px sat under the 24px WCAG 2.5.8 floor. Track and
    // 18px knob unchanged (vertically centered); only the grabbable strip grew.
    implicitWidth: 230; implicitHeight: 26
    activeFocusOnTab: true
    NCDEKit { id: k }

    function _nearest(v) {
        if (snapValues.length === 0) return v
        var best = snapValues[0], bestD = Math.abs(v - best)
        for (var i = 1; i < snapValues.length; i++) {
            var d = Math.abs(v - snapValues[i])
            if (d < bestD) { bestD = d; best = snapValues[i] }
        }
        return best
    }
    function _set(x){ var t = Math.max(0, Math.min(1, x / width));
        var v = _nearest(minValue + t * (maxValue - minValue)); if (v !== value) { value = v; moved(v) } }
    function _step(delta){ var v = Math.max(minValue, Math.min(maxValue, sl.value + delta));
        if (v !== sl.value) { sl.value = v; sl.moved(v) } }
    readonly property real frac: (value - minValue) / (maxValue - minValue)

    Accessible.role: Accessible.Slider
    Accessible.name: sl.accessibleName
    Accessible.description: sl.value.toFixed(0)
    Accessible.focusable: true
    Accessible.onIncreaseAction: sl._step(sl.stepSize)
    Accessible.onDecreaseAction: sl._step(-sl.stepSize)

    Rectangle {
        id: track; anchors.verticalCenter: parent.verticalCenter
        width: parent.width; height: 6; radius: 3
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: Qt.darker(k.gilt2, 1.1) } GradientStop { position: 1; color: Qt.darker(k.gilt1, 1.2) } }
        border.color: k.gilt0; border.width: 1
    }
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter; height: 6; radius: 3
        width: track.width * sl.frac
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: k.wine4 } GradientStop { position: 1; color: k.wine2 } }
        border.color: k.gilt0; border.width: 1
    }
    Rectangle {
        width: 18; height: 18; radius: 9; anchors.verticalCenter: parent.verticalCenter
        x: track.width * sl.frac - width/2
        border.color: k.gilt0; border.width: 1.5
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop { position: 0; color: k.gilt5 } GradientStop { position: 0.6; color: k.gilt3 } GradientStop { position: 1; color: k.gilt0 } }
        scale: drag.active ? 1.12 : 1.0
        Behavior on scale { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 90; easing.type: Easing.OutCubic } }
    }
    Rectangle {  // keyboard focus ring — same treatment as NCDEField/NCDEButton
        anchors.fill: parent; anchors.margins: -2; radius: 5
        color: "transparent"; border.color: k.cer; border.width: 2
        opacity: sl.activeFocus ? 0.28 : 0
        Behavior on opacity { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 120 } }
    }
    TapHandler { onTapped: { sl._set(point.position.x); sl.released() } }
    DragHandler { id: drag; target: null; onCentroidChanged: if (active) sl._set(centroid.position.x)
                  onActiveChanged: if (!active) sl.released() }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Left || event.key === Qt.Key_Down) { sl._step(-sl.stepSize); sl.released(); event.accepted = true }
        else if (event.key === Qt.Key_Right || event.key === Qt.Key_Up) { sl._step(sl.stepSize); sl.released(); event.accepted = true }
        else if (event.key === Qt.Key_Home) { sl.value = sl.minValue; sl.moved(sl.value); sl.released(); event.accepted = true }
        else if (event.key === Qt.Key_End) { sl.value = sl.maxValue; sl.moved(sl.value); sl.released(); event.accepted = true }
    }
}
