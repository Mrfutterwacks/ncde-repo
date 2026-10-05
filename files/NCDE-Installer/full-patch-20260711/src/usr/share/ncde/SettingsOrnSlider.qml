// SettingsOrnSlider.qml — ornate brass-knob slider on a gold track.

import QtQuick
import QtQuick.Layouts

Item {
    id: slider
    height: 32

    property real minValue: 0
    property real maxValue: 100
    property real value: 50
    property int  ticks: 8
    signal moved(real newValue)

    function _setFromX(x) {
        var t = Math.max(0, Math.min(1, x / width));
        var v = Math.round(minValue + t * (maxValue - minValue));
        if (v !== value) { value = v; moved(v); }
    }

    // gold track
    Rectangle {
        id: track
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.right: parent.right
        height: 6; radius: 3
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: ncde.gilt2 }
            GradientStop { position: 1; color: ncde.gilt1 }
        }
        border.width: 1; border.color: ncde.gilt0
    }

    // burgundy fill
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        height: 6; radius: 3
        width: track.width * ((slider.value - slider.minValue) / (slider.maxValue - slider.minValue))
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: ncde.wine4 }
            GradientStop { position: 1; color: ncde.wine2 }
        }
        border.width: 1; border.color: ncde.gilt0
    }

    // tick marks
    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left; anchors.right: parent.right
        spacing: 0; z: -1
        Repeater {
            model: slider.ticks
            Item {
                width: track.width / (slider.ticks - 1); height: 14
                Rectangle { width: 1; height: 14; color: ncde.gilt0; opacity: 0.4; anchors.left: parent.left }
            }
        }
    }

    // brass-knob thumb
    Rectangle {
        id: thumb
        width: 26; height: 26; radius: 13
        x: track.width * ((slider.value - slider.minValue) / (slider.maxValue - slider.minValue)) - width / 2
        anchors.verticalCenter: parent.verticalCenter
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0;    color: ncde.gilt5 }
            GradientStop { position: 0.55; color: ncde.gilt3 }
            GradientStop { position: 1;    color: ncde.gilt0 }
        }
        border.width: 2; border.color: ncde.gilt0
        Rectangle {
            anchors.fill: parent; anchors.margins: -2; radius: width / 2
            color: "transparent"; border.color: ncde.gilt4; border.width: 1; z: -1
        }
        Rectangle {
            anchors.centerIn: parent; width: 6; height: 6; radius: 3
            color: ncde.gilt0; border.color: ncde.gilt4; border.width: 1
        }
    }

    TapHandler {
        onTapped: slider._setFromX(point.position.x)
    }
    DragHandler {
        target: null
        onCentroidChanged: if (active) slider._setFromX(centroid.position.x)
    }
}
