// NCDEWeatherIcon.qml — Mucha weather icons
import QtQuick 2.15
import "mucha-weather.js" as MuchaWeather

Canvas {
    id: root
    property string code:   "32"
    property color  glow:   ncde.glow
    property color  accent: ncde.accent
    property int    sz:     64
    width: sz; height: sz

    onCodeChanged:   requestPaint()
    onGlowChanged:   requestPaint()
    onAccentChanged: requestPaint()
    onSzChanged:     requestPaint()
    Component.onCompleted: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        MuchaWeather.drawMuchaWeather(ctx, width, height, parseInt(code) || 32)
    }
}
