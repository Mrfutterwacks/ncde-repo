import QtQuick 2.15
import "colors.js" as Colors

Item {
    id: wheel

    property real hue: 0
    property real saturation: 0.75
    readonly property color current: Qt.hsla(hue / 360, saturation, 0.5, 1.0)
    readonly property string currentHex: Colors.hslToHex(hue, saturation, 0.5)
    signal picked(real hue, real saturation)

    Canvas {
        id: wheelCanvas
        anchors.fill: parent
        renderStrategy: Canvas.Cooperative
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d");
            if (!ctx) { Qt.callLater(requestPaint); return; }
            var cx = width / 2, cy = height / 2;
            var r = Math.min(cx, cy) - 6;
            ctx.clearRect(0, 0, width, height);

            var img = ctx.createImageData(width, height);
            var data = img.data;
            for (var y = 0; y < height; y++) {
                for (var x = 0; x < width; x++) {
                    var dx = x - cx, dy = y - cy;
                    var dist = Math.sqrt(dx * dx + dy * dy);
                    if (dist > r) continue;
                    var ang = Math.atan2(dy, dx) * 180 / Math.PI;
                    if (ang < 0) ang += 360;
                    var s = Math.min(1, dist / r);
                    var rgb = Colors.hslToRgb(ang, s, 0.5);
                    var i = (y * width + x) * 4;
                    data[i]     = Math.round(rgb.r * 255);
                    data[i + 1] = Math.round(rgb.g * 255);
                    data[i + 2] = Math.round(rgb.b * 255);
                    data[i + 3] = 255;
                }
            }
            ctx.putImageData(img, 0, 0);
        }
        onWidthChanged:  requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
    }

    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: "transparent"
        border.color: ncde.border
        border.width: 2
    }
    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        radius: width / 2
        color: "transparent"
        border.color: ncde.accentMuted
        border.width: 1
    }

    Rectangle {
        id: ind
        width: 18; height: 18; radius: 9
        color: wheel.current
        border.color: theme.textColor
        border.width: 2
        z: 5
        x: {
            var cx = wheel.width / 2;
            var r  = (Math.min(wheel.width, wheel.height) / 2 - 6) * wheel.saturation;
            return cx + r * Math.cos(wheel.hue * Math.PI / 180) - width / 2;
        }
        y: {
            var cy = wheel.height / 2;
            var r  = (Math.min(wheel.width, wheel.height) / 2 - 6) * wheel.saturation;
            return cy + r * Math.sin(wheel.hue * Math.PI / 180) - height / 2;
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: -2
            radius: width / 2
            color: "transparent"
            border.color: ncde.border
            border.width: 1
            z: -1
        }
    }

    function _pickAt(px, py) {
        var cx = width / 2, cy = height / 2;
        var dx = px - cx, dy = py - cy;
        var dist = Math.sqrt(dx * dx + dy * dy);
        var r = Math.min(cx, cy) - 6;
        var rr = Math.min(dist, r);
        var ang = Math.atan2(dy, dx) * 180 / Math.PI;
        if (ang < 0) ang += 360;
        wheel.hue = ang;
        wheel.saturation = Math.max(0.15, Math.min(1, rr / r));
        wheel.picked(wheel.hue, wheel.saturation);
    }

    TapHandler {
        gesturePolicy: TapHandler.ReleaseWithinBounds
        onTapped: wheel._pickAt(point.position.x, point.position.y)
    }
    DragHandler {
        target: null
        onCentroidChanged: {
            if (active) wheel._pickAt(centroid.position.x, centroid.position.y);
        }
    }
}
