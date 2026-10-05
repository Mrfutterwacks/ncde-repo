// NCDEProgressBar.qml — inset channel, gilt fill. Indeterminate optional.
import QtQuick 2.15

Item {
    id: pb
    property real value: 0.0      // 0..1
    property bool indeterminate: false
    property string accessibleName: ""
    readonly property bool motionAllowed: typeof animPolicy === "undefined" || animPolicy === null
        || (animPolicy.decorative && !animPolicy.screenIdle)
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 2.0 : 1.0
    implicitWidth: 230; implicitHeight: 10
    NCDEKit { id: k }

    Accessible.role: Accessible.ProgressBar
    Accessible.name: pb.accessibleName
    Accessible.description: pb.indeterminate ? "in progress" : Math.round(pb.value * 100) + "%"

    Rectangle {
        anchors.fill: parent; radius: height/2
        color: k.surface2; border.color: k.gilt1; border.width: 1
        Rectangle {  // inset shadow
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: 1 }
            height: 2; radius: 1; color: Qt.rgba(0,0,0,0.5)
        }
        clip: true
        Rectangle {
            id: fill
            height: parent.height - 2; y: 1; x: 1; radius: height/2
            width: pb.indeterminate ? parent.width * 0.34 : Math.max(0, (parent.width - 2) * Math.min(1, pb.value))
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop { position: 0; color: k.gilt2 } GradientStop { position: 1; color: k.gilt4 } }
            Behavior on width { enabled: !pb.indeterminate; NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy.instant) ? 0 : 160 } }
            XAnimator on x {
                running: pb.visible && pb.indeterminate && pb.motionAllowed; loops: Animation.Infinite
                from: -fill.width; to: pb.width; duration: 1100 * pb.motionDurationScale
                onStopped: fill.x = 1
            }
        }
    }
}
