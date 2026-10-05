// NCDEBusyIndicator.qml — gilt arc spinner (Canvas, NumberAnimation drive).
import QtQuick 2.15

Item {
    id: bi
    property bool running: true
    property string accessibleName: ""
    implicitWidth: 28; implicitHeight: 28
    readonly property bool motionAllowed: typeof animPolicy === "undefined" || animPolicy === null
        || (animPolicy.decorative && !animPolicy.screenIdle)
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 2.0 : 1.0
    NCDEKit { id: k }

    Accessible.role: Accessible.Indicator
    Accessible.name: bi.accessibleName
    Accessible.description: bi.running ? "busy" : ""

    Canvas {
        id: cv; anchors.fill: parent; antialiasing: true
        renderStrategy: Canvas.Cooperative; layer.enabled: true
        property real phase: 0
        visible: bi.running
        onPhaseChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var cx = width/2, cy = height/2, r = Math.min(cx,cy) - 3;
            // faint full ring
            ctx.beginPath(); ctx.arc(cx,cy,r,0,2*Math.PI);
            ctx.strokeStyle = Qt.rgba(k.gilt1.r,k.gilt1.g,k.gilt1.b,0.3); ctx.lineWidth = 3; ctx.stroke();
            // bright sweeping arc
            ctx.beginPath(); ctx.arc(cx,cy,r, phase, phase + Math.PI*0.6);
            ctx.strokeStyle = k.gilt4; ctx.lineWidth = 3; ctx.lineCap = "round"; ctx.stroke();
        }
        // phase is radians, not degrees → NumberAnimation (per NCDE rules)
        NumberAnimation on phase {
            from: 0; to: 6.2832; duration: 900 * bi.motionDurationScale
            loops: Animation.Infinite; running: bi.running && bi.visible && bi.motionAllowed
            onStopped: cv.phase = 0
        }
    }
}
