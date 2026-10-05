// SetToggle.qml — brass on/off switch (TapHandler only).
import QtQuick 2.15
Item {
    id: t
    property bool checked: false
    signal toggled(bool value)
    implicitWidth: 46; implicitHeight: 24
    Rectangle {
        anchors.fill: parent; radius: height/2
        border.color: ncde.gilt0; border.width: 1.5
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: t.checked ? ncde.verd : ncde.surfaceAlt }
            GradientStop { position: 1; color: t.checked ? Qt.darker(ncde.verd, 1.6) : ncde.surfaceAlt }
        }
    }
    Rectangle {
        width: 18; height: 18; radius: 9
        anchors.verticalCenter: parent.verticalCenter
        x: t.checked ? parent.width - width - 3 : 3
        border.color: ncde.gilt0; border.width: 1
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0;    color: ncde.gilt5 }
            GradientStop { position: 0.6;  color: ncde.gilt3 }
            GradientStop { position: 1;    color: ncde.gilt0 }
        }
        Behavior on x { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }
    }
    TapHandler { onTapped: { t.checked = !t.checked; t.toggled(t.checked) } }
}
