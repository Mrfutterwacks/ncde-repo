import QtQuick 2.15

// Preserve the operator's black-edged, translucent source image unchanged.
Image {
    id: exposeBackdrop
    anchors.fill: parent
    source: "muchaexpose-1920x1200.png"
    fillMode: Image.PreserveAspectCrop
    smooth: true
    mipmap: true
}