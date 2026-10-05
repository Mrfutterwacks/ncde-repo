// SetSlider.qml — gilt-track / brass-knob slider (TapHandler + DragHandler).
import QtQuick 2.15
Item {
    id: s
    property real minValue: 0
    property real maxValue: 100
    property real value: 50
    signal moved(real value)
    width: 230; height: 26
    function _set(x){ var t=Math.max(0,Math.min(1,x/width)); var v=minValue+t*(maxValue-minValue); if(v!==value){value=v; moved(v)} }
    Rectangle {
        id: track; anchors.verticalCenter: parent.verticalCenter; width: parent.width; height: 6; radius: 3
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop{position:0;color:ncde.gilt2} GradientStop{position:1;color:ncde.gilt1} }
        border.color:ncde.gilt0; border.width:1
    }
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter; height:6; radius:3
        width: track.width*((s.value-s.minValue)/(s.maxValue-s.minValue))
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop{position:0;color:ncde.wine4} GradientStop{position:1;color:ncde.wine2} }
        border.color:ncde.gilt0; border.width:1
    }
    Rectangle {
        width:18; height:18; radius:9; anchors.verticalCenter: parent.verticalCenter
        x: track.width*((s.value-s.minValue)/(s.maxValue-s.minValue)) - width/2
        gradient: Gradient { orientation: Gradient.Vertical
            GradientStop{position:0;color:ncde.gilt5} GradientStop{position:0.6;color:ncde.gilt3} GradientStop{position:1;color:ncde.gilt0} }
        border.color:ncde.gilt0; border.width:1.5
    }
    TapHandler { onTapped: s._set(point.position.x) }
    DragHandler { target: null; onCentroidChanged: if (active) s._set(centroid.position.x) }
}
