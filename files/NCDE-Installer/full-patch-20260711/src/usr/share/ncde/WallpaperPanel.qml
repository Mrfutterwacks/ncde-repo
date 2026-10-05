import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Qt.labs.folderlistmodel 2.15

Item {
    id: panel

    property string selectedPath: ""
    signal wallpaperApplyRequested(string path)

    FolderListModel {
        id: folderModel
        folder: "file:///home/" + settings.userName + "/ncde-x11/wallpapers"
        showDirs: false; showFiles: true; showHidden: false
        nameFilters: ["*.jpg","*.jpeg","*.png","*.webp","*.bmp","*.gif"]
        sortField: FolderListModel.Name
    }

    RowLayout {
        anchors.left: parent.left; anchors.right: parent.right
        anchors.top: parent.top; anchors.bottom: engine.top
        anchors.margins: 22; anchors.bottomMargin: 0
        spacing: 28

        // big preview
        Rectangle {
            Layout.fillWidth: true; Layout.fillHeight: true; Layout.preferredWidth: 1
            color: ncde.panelBg; border.color: ncde.gilt0; border.width: 3

            Rectangle {
                anchors.fill: parent; anchors.margins: 5
                color: "transparent"; border.color: ncde.gilt3; border.width: 1
            }

            Image {
                anchors.fill: parent; anchors.margins: 7
                fillMode: Image.PreserveAspectCrop
                source: panel.selectedPath !== "" ? "file://" + panel.selectedPath : ""
                sourceSize.width: 800; sourceSize.height: 500; smooth: true
            }

            Text {
                anchors.centerIn: parent
                text: "Select a wallpaper"
                color: ncde.gilt0; font.pixelSize: theme.fontSmall; font.family: ncde.bodyFont
                visible: panel.selectedPath === ""
            }

            // corner brackets
            Repeater {
                model: [{a:"top",b:"left"},{a:"top",b:"right"},{a:"bottom",b:"left"},{a:"bottom",b:"right"}]
                delegate: Rectangle {
                    width: 16; height: 16; color: "transparent"
                    border.color: ncde.gilt4; border.width: 2
                    anchors.top:    modelData.a === "top"    ? parent.top    : undefined
                    anchors.bottom: modelData.a === "bottom" ? parent.bottom : undefined
                    anchors.left:   modelData.b === "left"   ? parent.left   : undefined
                    anchors.right:  modelData.b === "right"  ? parent.right  : undefined
                }
            }
        }

        // scenes column
        ColumnLayout {
            Layout.fillWidth: true; Layout.fillHeight: true; Layout.preferredWidth: 1
            spacing: 12

            Item {
                Layout.fillWidth: true; implicitHeight: 24
                Rectangle { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter; width: 40; height: 1; color: ncde.gilt1 }
                Text { anchors.centerIn: parent; text: "SCENES"; font.family: ncde.titleFont; font.weight: Font.Bold; font.pixelSize: theme.fontMedium; font.letterSpacing: 3; color: ncde.gilt0 }
                Rectangle { anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter; width: 40; height: 1; color: ncde.gilt1 }
            }

            Rectangle {
                id: scenesRect
                Layout.fillWidth: true; Layout.fillHeight: true
                color: ncde.panelBg; border.color: ncde.gilt0; border.width: 1; clip: true

                GridView {
                    id: scenesGrid
                    anchors.fill: parent; anchors.margins: 4
                    model: folderModel
                    cellWidth: Math.floor((scenesRect.width - 8) / 3)
                    cellHeight: Math.floor(cellWidth * 0.65) + 22
                    delegate: Rectangle {
                        width: scenesGrid.cellWidth - 8
                        height: scenesGrid.cellHeight - 8
                        color: ncde.panelBg
                        border.color: panel.selectedPath === model.filePath ? ncde.gilt4 : ncde.gilt0
                        border.width: panel.selectedPath === model.filePath ? 2 : 1

                        Image {
                            anchors.fill: parent; anchors.margins: 2
                            fillMode: Image.PreserveAspectCrop
                            source: "file://" + model.filePath
                            sourceSize.width: 200; sourceSize.height: 130; smooth: true
                        }

                        // selection glow ring
                        Rectangle {
                            anchors.fill: parent; anchors.margins: -3
                            color: "transparent"; border.color: ncde.gilt3; border.width: 2
                            visible: panel.selectedPath === model.filePath; z: -1
                        }

                        // label strip
                        Rectangle {
                            anchors.left: parent.left; anchors.right: parent.right
                            anchors.bottom: parent.bottom; anchors.margins: 2
                            height: 22
                            gradient: Gradient {
                                GradientStop { position: 0; color: "transparent" }
                                GradientStop { position: 1; color: Qt.rgba(0,0,0,0.75) }
                            }
                            Text {
                                anchors.centerIn: parent; anchors.verticalCenterOffset: 4
                                text: model.fileName.replace(/\.[^/.]+$/, "")
                                color: ncde.gilt5; font.family: ncde.bodyFont; font.pixelSize: theme.fontSmall; font.letterSpacing: 2.5
                                elide: Text.ElideRight
                            }
                        }

                        TapHandler { onTapped: panel.selectedPath = model.filePath }
                    }

                    ScrollBar.vertical: NCDEScrollBar {}
                }
            }

            // action buttons
            Row {
                spacing: 8
                Rectangle {
                    width: 72; height: 24; radius: 2
                    color: panel.selectedPath !== "" ? ncde.wine2 : ncde.panelBg
                    border.color: panel.selectedPath !== "" ? ncde.gilt3 : ncde.gilt0; border.width: 1
                    Behavior on color { ColorAnimation { duration: 180 } }
                    Behavior on border.color { ColorAnimation { duration: 180 } }
                    Text { anchors.centerIn: parent; text: "Apply"; color: panel.selectedPath !== "" ? ncde.gilt5 : ncde.gilt0; font.pixelSize: theme.fontSmall; font.bold: true }
                    TapHandler {
                        onTapped: {
                            if (panel.selectedPath === "") return;
                            settings.setWallpaper(panel.selectedPath);
                            panel.wallpaperApplyRequested(panel.selectedPath);
                        }
                    }
                }
                Rectangle {
                    width: 74; height: 24; radius: 2
                    color: panel.selectedPath !== "" ? ncde.wine2 : ncde.panelBg
                    border.color: panel.selectedPath !== "" ? ncde.gilt3 : ncde.gilt0; border.width: 1
                    Behavior on color { ColorAnimation { duration: 180 } }
                    Behavior on border.color { ColorAnimation { duration: 180 } }
                    Text { anchors.centerIn: parent; text: "Sample"; color: panel.selectedPath !== "" ? ncde.gilt5 : ncde.gilt0; font.pixelSize: theme.fontSmall; font.bold: true }
                    TapHandler {
                        onTapped: {
                            if (panel.selectedPath === "") return;
                            var ok = ncde.sampleWallpaper(panel.selectedPath);
                            if (ok) {
                                ncde.saveTheme(settings.configBase + "active-theme.json");
                            }
                        }
                    }
                }
                Rectangle {
                    width: 64; height: 24; radius: 2
                    color: "transparent"; border.color: ncde.gilt0; border.width: 1
                    visible: ncde.usingCustomBase
                    Text { anchors.centerIn: parent; text: "Reset"; color: ncde.gilt0; font.pixelSize: theme.fontSmall; font.family: ncde.bodyFont }
                    TapHandler {
                        onTapped: {
                            ncde.clearCustomBase();
                            ncde.saveTheme(settings.configBase + "active-theme.json");
                        }
                    }
                }
            }
        }
    }

    // ── NCDE ENGINE · SHELL SAMPLING ──
    Item {
        id: engine
        anchors.left: parent.left; anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 36; anchors.rightMargin: 36
        anchors.bottomMargin: 22; height: 105

        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: parent.top; height: 1
            color: ncde.gilt0; opacity: 0.3
        }

        RowLayout {
            anchors.top: parent.top; anchors.topMargin: 12
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 14
            Rectangle {
                Layout.preferredWidth: 8; implicitHeight: 8; radius: 4
                color: ncde.gilt3; border.color: ncde.gilt0; border.width: 1
                SequentialAnimation on opacity {
                    running: panel.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
                    loops: Animation.Infinite
                    NumberAnimation { to: 1; duration: 1100 }
                    NumberAnimation { to: 0.5; duration: 1100 }
                }
            }
            Text {
                text: "NCDE ENGINE \u00B7 SHELL SAMPLING"
                font.family: ncde.titleFont; font.weight: Font.Bold
                font.pixelSize: theme.fontMedium; font.letterSpacing: 3.5; color: ncde.gilt0
            }
            Rectangle {
                Layout.preferredWidth: 8; implicitHeight: 8; radius: 4
                color: ncde.gilt3; border.color: ncde.gilt0; border.width: 1
                SequentialAnimation on opacity {
                    running: panel.visible && animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle
                    loops: Animation.Infinite
                    NumberAnimation { to: 1; duration: 1100 }
                    NumberAnimation { to: 0.5; duration: 1100 }
                }
            }
        }

        RowLayout {
            anchors.bottom: parent.bottom; anchors.bottomMargin: 4
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 26

            Repeater {
                model: [
                    { role: "bg",        label: "GROUND"    },
                    { role: "surface",   label: "SURFACE"   },
                    { role: "accent",    label: "ACCENT"    },
                    { role: "highlight", label: "HIGHLIGHT" },
                    { role: "text",      label: "QUILL"     }
                ]
                delegate: ColumnLayout {
                    spacing: 4
                    Rectangle {
                        Layout.preferredWidth: 56; Layout.preferredHeight: 56
                        color: modelData.role === "bg" ? ncde.panelBg :
                               modelData.role === "surface" ? ncde.surface :
                               modelData.role === "accent" ? ncde.accent :
                               modelData.role === "highlight" ? ncde.border :
                               theme.textColor
                        border.color: ncde.gilt0; border.width: 2
                        Rectangle {
                            anchors.fill: parent; anchors.margins: 4
                            color: "transparent"; border.color: ncde.gilt3; border.width: 1
                        }
                        Behavior on color { ColorAnimation { duration: 350 } }
                    }
                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: modelData.label; font.family: ncde.titleFont
                        font.pixelSize: theme.fontSmall; font.letterSpacing: 2; color: ncde.gilt0
                    }
                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: {
                            var c = modelData.role === "bg" ? ncde.panelBg :
                                    modelData.role === "surface" ? ncde.surface :
                                    modelData.role === "accent" ? ncde.accent :
                                    modelData.role === "highlight" ? ncde.border :
                                    theme.textColor;
                            function hex(v) { return Math.round(v * 255).toString(16).padStart(2,"0"); }
                            return "#" + hex(c.r) + hex(c.g) + hex(c.b);
                        }
                        font.family: ncde.bodyFont; font.italic: true; font.pixelSize: theme.fontSmall; color: ncde.wine2
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        var current = settings.getWallpaper ? settings.getWallpaper() : "";
        if (current) {
            if (current.indexOf("file://") === 0) current = current.substring(7);
            selectedPath = current;
        }
    }
}
