// WallpapersTab.qml — wallpaper gallery from ~/Pictures/wallpapers/
// Emits wallpaperApplyRequested(path) — SettingsPanel forwards this signal to main.qml.
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.folderlistmodel 2.15
import QtQuick.Dialogs

Item {
    id: wp
    property var k: SetTheme
    property string selectedPath: (typeof settings.getWallpaper === "function") ? settings.getWallpaper() : ""
    signal wallpaperApplyRequested(string path)
    property var    previewColors: null
    property string _pendingPath:  ""
    property bool   _nudgeOpen:     false
    property bool   _nudgePickBase: false
    // Double-click lifts the tapped cover in place toward the viewer; cleared on flip or Apply
    property int    liftedIndex:    -1

    // Shared by the Apply button and the Enter key — one path, one behavior
    function applySelected() {
        if (selectedPath === "") return
        wallpaperApplyRequested(selectedPath)
        settings.setWallpaper(selectedPath)
        var ok = ncde.sampleWallpaper(selectedPath)
        if (ok) ncde.saveTheme(settings.configBase + "active-theme.json")
        notifications.notify("Wallpaper Applied", selectedPath.split("/").pop(), "", 3000)
        liftedIndex = -1   // cover settles back into the carousel after Apply
    }

    Timer {
        id: hoverDebounce
        interval: 120; repeat: false
        onTriggered: if (wp._pendingPath !== "") ncde.previewWallpaperAsync(wp._pendingPath)
    }
    Connections {
        target: ncde
        function onPreviewReady(colors) { wp.previewColors = colors }
    }

    FileDialog {
        id: fileDialog
        title: "Select Wallpaper"
        currentFolder: "file:///home/" + settings.userName + "/Pictures/wallpapers"
        nameFilters: ["Image files (*.jpg *.jpeg *.png *.webp *.bmp *.gif *.tiff *.tif)", "All files (*)"]
        onAccepted: {
            var path = fileDialog.selectedFile.toString().slice(7)
            wp.selectedPath = path
            settings.setWallpaper(path)
            ncde.sampleWallpaper(path)
            notifications.notify("Wallpaper Applied", path.split("/").pop(), "", 3000)
        }
    }

    FolderListModel {
        id: folderModel
        folder:        "file:///home/" + settings.userName + "/Pictures/wallpapers"
        showDirs:      false; showFiles: true; showHidden: false
        nameFilters:   ["*.jpg","*.jpeg","*.png","*.webp","*.bmp","*.gif","*.tiff","*.tif"]
        sortField:     FolderListModel.Name; sortCaseSensitive: false
    }

    // Title
    Row {
        id: titleRow
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter
        spacing: 12
        Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 60; height: 1; color: wp.k.gilt1 }
        Text { text: "WALLPAPER GALLERY"; color: wp.k.gilt1; font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 3 }
        Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 60; height: 1; color: wp.k.gilt1 }
    }

    // Custom (non-bundled) wallpapers strip — shown only when the list is non-empty
    Item {
        id: customStrip
        anchors.top: titleRow.bottom; anchors.topMargin: customList.count > 0 ? 6 : 0
        anchors.left: parent.left; anchors.right: parent.right
        height: customList.count > 0 ? 82 : 0
        clip: true

        ListView {
            id: customList
            anchors.fill: parent
            orientation: ListView.Horizontal
            spacing: 6; clip: true
            model: settings.customWallpapers
            delegate: Item {
                width: 120; height: 80
                property string cPath: modelData
                property bool isSel: wp.selectedPath === cPath
                Rectangle {
                    anchors.fill: parent; anchors.margins: 2; radius: 3; color: ncde.panelBg
                    border.color: isSel ? wp.k.gilt4 : wp.k.gilt1; border.width: isSel ? 3 : 1; clip: true
                    Image {
                        anchors.fill: parent; anchors.margins: isSel ? 3 : 1
                        source: "file://" + cPath; fillMode: Image.PreserveAspectCrop
                        asynchronous: true; smooth: true; cache: true
                        sourceSize.width: 240; sourceSize.height: 160
                    }
                    Rectangle {
                        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
                        height: 16; anchors.leftMargin: 1; anchors.rightMargin: 1; anchors.bottomMargin: 1
                        gradient: Gradient { GradientStop{position:0;color:"transparent"} GradientStop{position:1;color:Qt.rgba(0,0,0,0.78)} }
                        Text { anchors.fill: parent; anchors.margins: 2; verticalAlignment: Text.AlignVCenter
                               text: cPath.split("/").pop(); color: wp.k.gilt5
                               font.family: wp.k.serif; font.pixelSize: k.sm; elide: Text.ElideRight }
                    }
                    HoverHandler {
                        id: cHov
                        onHoveredChanged: {
                            if (hovered) { wp._pendingPath = cPath; hoverDebounce.restart() }
                            else { wp._pendingPath = ""; hoverDebounce.stop(); wp.previewColors = null }
                        }
                    }
                    Rectangle { anchors.fill: parent; radius: 3; color: wp.k.gilt5; opacity: cHov.hovered && !isSel ? 0.12 : 0 }
                    TapHandler { onTapped: wp.selectedPath = cPath }
                }
            }
        }
    }

    // Gallery — fills all space between custom strip and path bar
    Rectangle {
        id: galleryFrame
        anchors.top: customStrip.bottom; anchors.topMargin: 8
        anchors.bottom: pathBar.top; anchors.bottomMargin: 6
        anchors.left: parent.left; anchors.right: parent.right
        radius: 4; clip: true; color: "transparent"; border.color: wp.k.gilt1; border.width: 1

        property bool _hintGone: false
        Timer { id: hintTimer; interval: 2500; repeat: false; running: true; onTriggered: galleryFrame._hintGone = true }

        // Translucent frosted Tiffany glass stage (smoked glass + iridescent jewel sheen)
        Canvas {
            id: wpStage
            anchors.fill: parent
            renderStrategy: Canvas.Cooperative
            layer.enabled: true
            onPaint: {
                var ctx = getContext("2d"); ctx.reset()
                var w = width, h = height
                // 1. smoked translucent glass body — lets the panel behind glow through faintly
                ctx.fillStyle = "rgba(18,22,26,0.62)"; ctx.fillRect(0, 0, w, h)
                // 2. frost: soft diagonal milky wash (top-left), the bloom of frosted glass
                var fr = ctx.createLinearGradient(0, 0, w, h)
                fr.addColorStop(0.0, "rgba(255,255,255,0.10)")
                fr.addColorStop(0.35, "rgba(255,255,255,0.03)")
                fr.addColorStop(1.0, "rgba(255,255,255,0.0)")
                ctx.fillStyle = fr; ctx.fillRect(0, 0, w, h)
                // 3. Tiffany iridescence — jewel tints pooled in the corners
                function tint(cx, cy, r, col){ var g = ctx.createRadialGradient(cx,cy,0,cx,cy,r); g.addColorStop(0,col); g.addColorStop(1,"rgba(0,0,0,0)"); ctx.fillStyle=g; ctx.fillRect(0,0,w,h) }
                tint(w*0.12, h*0.18, Math.max(w,h)*0.5, "rgba(86,176,150,0.10)")   // peacock green
                tint(w*0.88, h*0.20, Math.max(w,h)*0.5, "rgba(120,150,210,0.09)")  // favrile blue
                tint(w*0.80, h*0.92, Math.max(w,h)*0.5, "rgba(210,150,180,0.07)")  // rose
                tint(w*0.20, h*0.95, Math.max(w,h)*0.5, "rgba(233,201,124,0.08)")  // gilt
                // 4. top sheen — glass edge catching the light
                var sh = ctx.createLinearGradient(0, 0, 0, h*0.16)
                sh.addColorStop(0.0, "rgba(255,255,255,0.14)")
                sh.addColorStop(1.0, "rgba(255,255,255,0.0)")
                ctx.fillStyle = sh; ctx.fillRect(0, 0, w, h*0.16)
                // 5. floor vignette to seat the covers
                var vg = ctx.createRadialGradient(w*0.5, h*0.42, Math.min(w,h)*0.2, w*0.5, h*0.5, Math.max(w,h)*0.82)
                vg.addColorStop(0.0, "rgba(0,0,0,0.0)")
                vg.addColorStop(1.0, "rgba(0,0,0,0.45)")
                ctx.fillStyle = vg; ctx.fillRect(0, 0, w, h)
            }
            Component.onCompleted: requestPaint()
            onWidthChanged: requestPaint()
            onHeightChanged: requestPaint()
        }

        PathView {
            id: wpFlow
            anchors.fill: parent; anchors.margins: 8
            focus: visible
            model: folderModel
            pathItemCount: Math.min(7, folderModel.count)
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            highlightRangeMode: PathView.StrictlyEnforceRange
            snapMode: PathView.SnapOneItem
            highlightMoveDuration: 700
            interactive:           false
            clip: true
            onCurrentIndexChanged: wp.liftedIndex = -1

            path: Path {
                startX: wpFlow.width*0.30; startY: wpFlow.height*0.40
                PathAttribute { name: "iScale";   value: 0.40 }
                PathAttribute { name: "iAngle";   value: 55 }
                PathAttribute { name: "iZ";       value: 0 }
                PathAttribute { name: "iOpacity"; value: 0.40 }
                PathLine { x: wpFlow.width*0.43; y: wpFlow.height*0.40 }
                PathPercent { value: 0.42 }
                PathAttribute { name: "iScale";   value: 0.84 }
                PathAttribute { name: "iAngle";   value: 55 }
                PathAttribute { name: "iZ";       value: 1 }
                PathAttribute { name: "iOpacity"; value: 0.80 }
                PathLine { x: wpFlow.width*0.50; y: wpFlow.height*0.40 }
                PathPercent { value: 0.50 }
                PathAttribute { name: "iScale";   value: 1.0 }
                PathAttribute { name: "iAngle";   value: 0 }
                PathAttribute { name: "iZ";       value: 10 }
                PathAttribute { name: "iOpacity"; value: 1.0 }
                PathLine { x: wpFlow.width*0.57; y: wpFlow.height*0.40 }
                PathPercent { value: 0.58 }
                PathAttribute { name: "iScale";   value: 0.84 }
                PathAttribute { name: "iAngle";   value: -55 }
                PathAttribute { name: "iZ";       value: 1 }
                PathAttribute { name: "iOpacity"; value: 0.80 }
                PathLine { x: wpFlow.width*0.70; y: wpFlow.height*0.40 }
                PathAttribute { name: "iScale";   value: 0.40 }
                PathAttribute { name: "iAngle";   value: -55 }
                PathAttribute { name: "iZ";       value: 0 }
                PathAttribute { name: "iOpacity"; value: 0.40 }
            }

            delegate: Item {
                id: tile
                width: 300; height: 188
                property bool isCurrent: PathView.isCurrentItem
                property bool isLifted: wp.liftedIndex === index
                scale:   PathView.iScale === undefined ? 0.74 : PathView.iScale
                z:       isLifted ? 50 : (PathView.iZ === undefined ? 0 : PathView.iZ)
                opacity: PathView.iOpacity === undefined ? 0.72 : PathView.iOpacity
                property bool isSel: wp.selectedPath === model.filePath
                transform: Rotation {
                    origin.x: tile.width/2; origin.y: tile.height/2
                    axis { x: 0; y: 1; z: 0 }
                    angle: PathView.iAngle === undefined ? 0 : PathView.iAngle
                }
                // Volumetric gilt glow behind the active cover (Tiffany lamplight)
                Canvas {
                    id: tileGlow
                    x: -40; y: -40
                    width: parent.width + 80; height: parent.height + 80
                    z: -1
                    renderStrategy: Canvas.Cooperative
                    layer.enabled: true
                    opacity: tile.PathView.isCurrentItem ? 1.0 : 0.0
                    Behavior on opacity { NumberAnimation { duration: 420; easing.type: Easing.OutCubic } }
                    onPaint: {
                        var ctx = getContext("2d"); ctx.reset()
                        var cx = width/2, cy = height*0.46, R = Math.max(width, height)*0.44
                        var g = ctx.createRadialGradient(cx, cy, 0, cx, cy, R)
                        g.addColorStop(0.00, "rgba(246,227,176,0.30)")
                        g.addColorStop(0.42, "rgba(233,201,124,0.12)")
                        g.addColorStop(0.72, "rgba(233,201,124,0.0)")
                        ctx.fillStyle = g; ctx.fillRect(0, 0, width, height)
                    }
                    Component.onCompleted: requestPaint()
                    onWidthChanged: requestPaint()
                    onHeightChanged: requestPaint()
                }
                Rectangle {
                    width: parent.width; height: parent.height; radius: 3; color: ncde.panelBg
                    // Lift: the cover detaches and comes toward the viewer; frame glows bright
                    scale: tile.isLifted ? 1.30 : 1.0
                    y:     tile.isLifted ? -12  : 0
                    Behavior on scale { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                    Behavior on y     { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                    border.color: tile.isLifted ? wp.k.gilt5 : (isSel ? wp.k.gilt4 : wp.k.gilt0)
                    border.width: (tile.isLifted || isSel) ? 3 : 2; clip: true
                    Image {
                        anchors.fill: parent; anchors.margins: isSel ? 3 : 2
                        source: "file://" + model.filePath; fillMode: Image.PreserveAspectCrop
                        asynchronous: true; smooth: true; cache: true
                        sourceSize.width: 320; sourceSize.height: 220
                    }
                    Rectangle { anchors.fill: parent; anchors.margins: 2; color: "transparent"; border.color: wp.k.gilt3; border.width: 1; opacity: 0.5 }
                    Rectangle {
                        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 2; height: 18
                        gradient: Gradient { GradientStop{position:0;color:"transparent"} GradientStop{position:1;color:Qt.rgba(0,0,0,0.78)} }
                        Text { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 4
                               text: model.fileName; color: wp.k.gilt5; font.family: wp.k.serif; font.pixelSize: k.sm; elide: Text.ElideRight }
                    }
                    HoverHandler {
                        id: cellHov
                        onHoveredChanged: {
                            if (hovered) {
                                wp._pendingPath = model.filePath
                                hoverDebounce.restart()
                            } else {
                                wp._pendingPath = ""
                                hoverDebounce.stop()
                                wp.previewColors = null
                            }
                        }
                    }
                    Rectangle { anchors.fill: parent; color: wp.k.gilt5; opacity: cellHov.hovered && !isSel ? 0.12 : 0 }
                    TapHandler {
                        gesturePolicy: TapHandler.WithinBounds
                        grabPermissions: PointerHandler.CanTakeOverFromHandlersOfSameType
                        onTapped: {
                            // (debug console.log removed — fired on every gallery tap, journal spam)
                            // double-click -> STOP + LIFT IN PLACE: cancels the pending step, the
                            // tapped cover detaches where it stands, frame glows; it becomes the
                            // selection Apply uses. NEVER assign currentIndex here — a PathView
                            // index jump animates across every intervening cover (the fast spin)
                            if (tapCount >= 2) {
                                stepDelay.stop(); stepDelay.dir = 0
                                wp.selectedPath = model.filePath
                                wp.liftedIndex = index
                                return
                            }
                            // single click -> arm ONE deliberate step toward the clicked side;
                            // held until the double-click window passes so the carousel never
                            // moves out from under the second tap of a double-click
                            if (index === wpFlow.currentIndex) return
                            stepDelay.dir = (tile.x + tile.width/2 < wpFlow.width/2) ? -1 : 1
                            stepDelay.restart()
                        }
                    }
                }
                // CoverFlow: separator line + Canvas reflection (iTunes Snow Leopard)
                Rectangle {
                    width: parent.width; height: 1
                    y: parent.height + 1
                    color: Qt.rgba(wp.k.inkSoft.r, wp.k.inkSoft.g, wp.k.inkSoft.b, 0.18)
                }
                Canvas {
                    id: reflCanvas
                    width: parent.width; height: 95
                    y: parent.height + 3
                    renderStrategy: Canvas.Cooperative
                    layer.enabled: true

                    property string imgPath: model.filePath
                    property string _lastLoaded: ""

                    onImgPathChanged: {
                        if (imgPath !== "" && imgPath !== _lastLoaded)
                            loadImage("file://" + imgPath)
                    }
                    onImageLoaded: { _lastLoaded = imgPath; requestPaint() }

                    onPaint: {
                        var ctx = getContext("2d")
                        if (!isImageLoaded("file://" + imgPath)) { ctx.clearRect(0, 0, width, height); return }
                        ctx.clearRect(0, 0, width, height)
                        ctx.save()
                        ctx.translate(0, height)
                        ctx.scale(1, -1)
                        ctx.drawImage("file://" + imgPath, 0, 0, width, height)
                        ctx.restore()
                        ctx.globalCompositeOperation = "destination-in"
                        var g = ctx.createLinearGradient(0, 0, 0, height)
                        g.addColorStop(0.0, "rgba(0,0,0,0.58)")
                        g.addColorStop(1.0, "rgba(0,0,0,0.0)")
                        ctx.fillStyle = g
                        ctx.fillRect(0, 0, width, height)
                        ctx.globalCompositeOperation = "source-over"
                    }

                    Component.onCompleted: { if (imgPath !== "") loadImage("file://" + imgPath) }
                }
            }

            // Holds a single-click step until the double-click window passes, so the
            // first tap of a double-click never starts the carousel moving
            Timer {
                id: stepDelay
                interval: Qt.styleHints.mouseDoubleClickInterval
                repeat: false
                property int dir: 0
                onTriggered: {
                    if (dir < 0) wpFlow.decrementCurrentIndex()
                    else if (dir > 0) wpFlow.incrementCurrentIndex()
                    dir = 0
                }
            }
            Timer { id: wheelCooldown; interval: 350; repeat: false }
            WheelHandler {
                acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                onWheel: function(ev) {
                    if (wheelCooldown.running) return
                    if (ev.angleDelta.y < 0 || ev.angleDelta.x < 0) wpFlow.incrementCurrentIndex()
                    else wpFlow.decrementCurrentIndex()
                    wheelCooldown.restart()
                }
            }
            Keys.onLeftPressed: decrementCurrentIndex()
            Keys.onRightPressed: incrementCurrentIndex()
            // Enter applies the CENTERED wallpaper — centered == applied, always
            Keys.onReturnPressed: {
                wp.selectedPath = folderModel.get(wpFlow.currentIndex, "filePath")
                wp.applySelected()
            }
            Keys.onEnterPressed: {
                wp.selectedPath = folderModel.get(wpFlow.currentIndex, "filePath")
                wp.applySelected()
            }
            // Type-to-jump: type "ow" → jumps to owl.png (iTunes behavior)
            property string typeBuf: ""
            Timer { id: typeBufClear; interval: 1000; repeat: false; onTriggered: wpFlow.typeBuf = "" }
            Keys.onPressed: function(ev) {
                if (ev.text && ev.text.length === 1 && ev.text >= " ") {
                    wpFlow.typeBuf += ev.text.toLowerCase()
                    typeBufClear.restart()
                    for (var i = 0; i < folderModel.count; i++) {
                        var n = ("" + folderModel.get(i, "fileName")).toLowerCase()
                        if (n.indexOf(wpFlow.typeBuf) === 0) { wpFlow.currentIndex = i; break }
                    }
                    ev.accepted = true
                }
            }

        }

        // iTunes scrubber — drag or click the gilt rail to jump anywhere in the gallery
        Item {
            id: scrubber
            anchors.left: parent.left; anchors.right: parent.right
            anchors.bottom: swatchStrip.top; anchors.bottomMargin: 8
            anchors.leftMargin: 90; anchors.rightMargin: 90
            height: 16; z: 3
            visible: folderModel.count > 1

            function jumpTo(px) {
                var t = Math.max(0, Math.min(1, px / width))
                wpFlow.currentIndex = Math.round(t * (folderModel.count - 1))
            }

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width; height: 3; radius: 1.5
                color: wp.k.gilt1; opacity: 0.45
            }
            Rectangle {
                id: scrubHandle
                anchors.verticalCenter: parent.verticalCenter
                width: Math.max(28, scrubber.width / Math.max(1, folderModel.count))
                height: 11; radius: 5.5
                x: (scrubber.width - width) * (folderModel.count > 1 ? wpFlow.currentIndex / (folderModel.count - 1) : 0)
                Behavior on x { NumberAnimation { duration: 120; easing.type: Easing.OutCubic } }
                border.color: wp.k.gilt0; border.width: 1
                gradient: Gradient {
                    GradientStop { position: 0; color: scrubHov.hovered ? wp.k.gilt5 : wp.k.gilt4 }
                    GradientStop { position: 1; color: wp.k.gilt3 }
                }
            }
            HoverHandler { id: scrubHov }
            TapHandler { onTapped: function(ev) { scrubber.jumpTo(ev.position.x) } }
            DragHandler {
                target: null
                onCentroidChanged: if (active) scrubber.jumpTo(centroid.position.x)
            }
        }

        Text {
            id: swipeHint
            anchors.bottom: parent.bottom; anchors.bottomMargin: 44
            anchors.horizontalCenter: parent.horizontalCenter
            text: "‹ click to flip · double-click to lift · Apply ›"
            color: wp.k.gilt3; font.family: wp.k.serif; font.italic: true; font.pixelSize: k.sm
            opacity: galleryFrame._hintGone ? 0 : 0.7
            visible: opacity > 0
            Behavior on opacity { NumberAnimation { duration: 800 } }
            z: 3
        }
        Text {
            anchors.centerIn: parent; visible: folderModel.count === 0
            text: "No wallpapers found in\n~/Pictures/wallpapers"
            horizontalAlignment: Text.AlignHCenter; color: wp.k.gilt1
            font.family: wp.k.serif; font.italic: true; font.pixelSize: k.md
        }

        Rectangle {
            id: swatchStrip
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            height: (wp.previewColors && wp.previewColors.valid) ? 32 : 0
            visible: height > 0; clip: true; z: 2
            color: Qt.rgba(0,0,0,0.82)
            Row {
                anchors.centerIn: parent; spacing: 18
                Row { spacing: 5
                    Rectangle { width:14;height:14;radius:7;anchors.verticalCenter:parent.verticalCenter
                        color:wp.previewColors?wp.previewColors["panelBg"]:"transparent"
                        border.color:wp.k.gilt0;border.width:1 }
                    Text { anchors.verticalCenter:parent.verticalCenter;text:"Panel"
                        color:wp.k.gilt4;font.family:wp.k.serif;font.pixelSize:k.sm }
                }
                Row { spacing: 5
                    Rectangle { width:14;height:14;radius:7;anchors.verticalCenter:parent.verticalCenter
                        color:wp.previewColors?wp.previewColors["accent"]:"transparent"
                        border.color:wp.k.gilt0;border.width:1 }
                    Text { anchors.verticalCenter:parent.verticalCenter;text:"Accent"
                        color:wp.k.gilt4;font.family:wp.k.serif;font.pixelSize:k.sm }
                }
                Row { spacing: 5
                    Rectangle { width:14;height:14;radius:7;anchors.verticalCenter:parent.verticalCenter
                        color:wp.previewColors?wp.previewColors["surface"]:"transparent"
                        border.color:wp.k.gilt0;border.width:1 }
                    Text { anchors.verticalCenter:parent.verticalCenter;text:"Surface"
                        color:wp.k.gilt4;font.family:wp.k.serif;font.pixelSize:k.sm }
                }
                Row { spacing: 5
                    Rectangle { width:14;height:14;radius:7;anchors.verticalCenter:parent.verticalCenter
                        color:wp.previewColors?wp.previewColors["text"]:"transparent"
                        border.color:wp.k.gilt0;border.width:1 }
                    Text { anchors.verticalCenter:parent.verticalCenter;text:"Text"
                        color:wp.k.gilt4;font.family:wp.k.serif;font.pixelSize:k.sm }
                }
            }
        }
    }

    // Slideshow controls
    Row {
        id: slideshowRow
        anchors.bottom: nudgeStrip.top; anchors.bottomMargin: 6
        anchors.left: parent.left
        spacing: 10
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "SLIDESHOW"; color: wp.k.gilt1
            font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
        }
        NCDEToggle {
            anchors.verticalCenter: parent.verticalCenter
            checked: settings.slideshowEnabled
            onToggled: function(v) { settings.slideshowEnabled = v }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "every"; color: wp.k.gilt1
            font.family: wp.k.serif; font.pixelSize: k.sm
            opacity: settings.slideshowEnabled ? 1.0 : 0.35
        }
        NCDESlider {
            anchors.verticalCenter: parent.verticalCenter
            width: 160; minValue: 1; maxValue: 60
            value: settings.slideshowInterval
            opacity: settings.slideshowEnabled ? 1.0 : 0.35
            onMoved: function(v) { settings.slideshowInterval = Math.round(v) }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: settings.slideshowInterval + " min"; color: wp.k.gilt1
            font.family: wp.k.serif; font.pixelSize: k.sm
            opacity: settings.slideshowEnabled ? 1.0 : 0.35
        }
    }

    // Fit mode selector
    Row {
        id: fitRow
        anchors.bottom: slideshowRow.top; anchors.bottomMargin: 6
        anchors.left: parent.left
        spacing: 10
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "FIT"; color: wp.k.gilt1
            font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
        }
        SetSegment {
            anchors.verticalCenter: parent.verticalCenter
            model: ["Fill", "Fit", "Center", "Tile"]
            currentIndex: { var m=["fill","fit","center","tile"]; var i=m.indexOf(settings.fitMode); return i>=0?i:0 }
            onChose: function(i) { settings.fitMode = ["fill","fit","center","tile"][i] }
        }
    }

    // Selected path
    Rectangle {
        id: pathBar
        anchors.bottom: fitRow.top; anchors.bottomMargin: 6
        anchors.left: parent.left; anchors.right: parent.right
        height: 24; radius: 4
        color: Qt.rgba(wp.k.paper0.r, wp.k.paper0.g, wp.k.paper0.b, 0.05); border.color: wp.k.gilt1; border.width: 1
        Text {
            anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10
            verticalAlignment: Text.AlignVCenter
            text: wp.selectedPath !== "" ? wp.selectedPath : "No wallpaper selected"
            color: wp.selectedPath !== "" ? wp.k.ink : wp.k.gilt1
            font.pixelSize: k.sm; font.family: wp.k.mono; elide: Text.ElideLeft
        }
    }

    // Colour nudge strip — appears after wallpaper theme is applied
    Item {
        id: nudgeStrip
        anchors.bottom: actRow.top; anchors.bottomMargin: 0
        anchors.left: parent.left; anchors.right: parent.right
        height: ncde.usingCustomBase ? 36 : 0; clip: true

        Row {
            anchors.verticalCenter: parent.verticalCenter; spacing: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "NUDGE"; color: wp.k.gilt1
                font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 70; height: 24; radius: 4
                border.color: wp.k.gilt1; border.width: 1; color: "transparent"
                Row { anchors.centerIn: parent; spacing: 5
                    Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 14; height: 14; radius: 7
                                color: ncde.background; border.color: wp.k.gilt0; border.width: 1 }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: "Base"
                           color: wp.k.gilt4; font.family: wp.k.serif; font.pixelSize: k.sm }
                }
                HoverHandler { id: baseWellHov }
                Rectangle { anchors.fill: parent; radius: 4; color: wp.k.gilt5; opacity: baseWellHov.hovered ? 0.10 : 0 }
                TapHandler { onTapped: { wp._nudgePickBase = true; wp._nudgeOpen = true } }
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 80; height: 24; radius: 4
                border.color: wp.k.gilt1; border.width: 1; color: "transparent"
                Row { anchors.centerIn: parent; spacing: 5
                    Rectangle { anchors.verticalCenter: parent.verticalCenter; width: 14; height: 14; radius: 7
                                color: ncde.accent; border.color: wp.k.gilt0; border.width: 1 }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: "Accent"
                           color: wp.k.gilt4; font.family: wp.k.serif; font.pixelSize: k.sm }
                }
                HoverHandler { id: accentWellHov }
                Rectangle { anchors.fill: parent; radius: 4; color: wp.k.gilt5; opacity: accentWellHov.hovered ? 0.10 : 0 }
                TapHandler { onTapped: { wp._nudgePickBase = false; wp._nudgeOpen = true } }
            }
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 136; height: 24; radius: 4; visible: wp.selectedPath !== ""
                color: "transparent"; border.color: wp.k.gilt1; border.width: 1
                Text { anchors.centerIn: parent; text: "Reset to Wallpaper"
                       color: wp.k.gilt1; font.family: wp.k.serif; font.pixelSize: k.sm }
                HoverHandler { id: rstWallHov }
                Rectangle { anchors.fill: parent; radius: 4; color: wp.k.gilt5; opacity: rstWallHov.hovered ? 0.08 : 0 }
                TapHandler { onTapped: {
                    ncde.sampleWallpaper(wp.selectedPath)
                    ncde.saveTheme(settings.configBase + "active-theme.json")
                }}
            }
        }
    }

    // Action buttons — pinned to bottom
    Row {
        id: actRow
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        spacing: 10
        Rectangle {
            id: applyBtn; width: 140; height: 30; radius: 6
            property bool sampling: false
            // Lights up while a cover is lifted (the existing button, nothing new)
            border.color: wp.liftedIndex >= 0 ? wp.k.gilt5 : wp.k.gilt0; border.width: 2
            opacity: wp.selectedPath !== "" ? 1.0 : 0.4
            gradient: Gradient { GradientStop{position:0;color:applyHov.hovered?wp.k.gilt5:wp.k.gilt4} GradientStop{position:1;color:wp.k.gilt3} }
            Text { anchors.centerIn: parent
                   text: applyBtn.sampling ? "Applying..." : "Apply"
                   color: wp.k.wine1; font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm }
            HoverHandler { id: applyHov }
            TapHandler { enabled: wp.selectedPath !== ""
                onTapped: {
                    applyBtn.sampling = true
                    wp.applySelected()
                    applyBtn.sampling = false
                }
            }
        }
        Rectangle {
            width: 78; height: 30; radius: 6; color: "transparent"; border.color: wp.k.gilt1; border.width: 1
            visible: ncde.usingCustomBase
            Text { anchors.centerIn: parent; text: "Reset"; color: wp.k.gilt1; font.family: wp.k.serif; font.pixelSize: k.sm }
            TapHandler { onTapped: { ncde.clearCustomBase(); ncde.saveTheme(settings.configBase + "active-theme.json") } }
        }
        Rectangle {
            width: 92; height: 30; radius: 6; color: "transparent"; border.color: wp.k.gilt1; border.width: 1
            Text { anchors.centerIn: parent; text: "Browse…"; color: wp.k.gilt1; font.family: wp.k.serif; font.pixelSize: k.sm }
            HoverHandler { id: brHov }
            Rectangle { anchors.fill: parent; radius: 6; color: wp.k.gilt5; opacity: brHov.hovered ? 0.08 : 0 }
            TapHandler { onTapped: fileDialog.open() }
        }
    }

    // Colour picker popup — seeded from the nudge strip wells
    Rectangle {
        id: nudgePopup
        anchors.fill: parent; z: 20; visible: wp._nudgeOpen
        color: Qt.rgba(0, 0, 0, 0.82)

        onVisibleChanged: {
            if (!visible) return
            var c = wp._nudgePickBase ? ncde.background : ncde.accent
            var r = c.r, g = c.g, b = c.b
            var mx = Math.max(r,g,b), mn = Math.min(r,g,b), d = mx - mn
            var h = 0, s = 0
            if (d > 0) {
                var l = (mx + mn) / 2
                s = l > 0.5 ? d / (2 - mx - mn) : d / (mx + mn)
                if      (mx === r) h = ((g - b) / d + (g < b ? 6 : 0)) / 6
                else if (mx === g) h = ((b - r) / d + 2) / 6
                else               h = ((r - g) / d + 4) / 6
                h *= 360
            }
            nudgeWheel.hue        = h
            nudgeWheel.saturation = Math.max(0.15, s)
        }

        Rectangle {
            anchors.centerIn: parent
            width: 380; height: 440; radius: 8; clip: true
            color: ncde.panelBg; border.color: wp.k.gilt1; border.width: 2

            Text {
                anchors.top: parent.top; anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                text: wp._nudgePickBase ? "ADJUST BASE" : "ADJUST ACCENT"
                color: wp.k.gilt1; font.family: wp.k.display; font.bold: true
                font.pixelSize: k.sm; font.letterSpacing: 3
            }
            Rectangle {
                anchors.left: parent.left; anchors.right: parent.right
                anchors.leftMargin: 16; anchors.rightMargin: 16
                y: 36; height: 1; color: wp.k.gilt0; opacity: 0.4
            }

            SettingsColorWheel {
                id: nudgeWheel
                anchors.top: parent.top; anchors.topMargin: 44
                anchors.horizontalCenter: parent.horizontalCenter
                width: 300; height: 300
            }

            Row {
                anchors.top: nudgeWheel.bottom; anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 30; height: 30; radius: 4
                    color: nudgeWheel.current; border.color: wp.k.gilt1; border.width: 1
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: nudgeWheel.currentHex; color: wp.k.gilt4
                    font.family: wp.k.mono; font.pixelSize: k.sm
                }
            }

            Row {
                anchors.bottom: parent.bottom; anchors.bottomMargin: 16
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 12
                Rectangle {
                    width: 100; height: 30; radius: 6
                    border.color: wp.k.gilt0; border.width: 2
                    gradient: Gradient { GradientStop{position:0;color:apNHov.hovered?wp.k.gilt5:wp.k.gilt4} GradientStop{position:1;color:wp.k.gilt3} }
                    Text { anchors.centerIn: parent; text: "Apply"
                           color: wp.k.wine1; font.family: wp.k.display; font.bold: true; font.pixelSize: k.sm }
                    HoverHandler { id: apNHov }
                    TapHandler {
                        onTapped: {
                            if (wp._nudgePickBase)
                                ncde.setBaseColor(nudgeWheel.current, ncde.accent, ncde.panelText)
                            else
                                ncde.setBaseColor(ncde.background, nudgeWheel.current, ncde.panelText)
                            ncde.saveTheme(settings.configBase + "active-theme.json")
                            wp._nudgeOpen = false
                        }
                    }
                }
                Rectangle {
                    width: 80; height: 30; radius: 6
                    color: "transparent"; border.color: wp.k.gilt1; border.width: 1
                    Text { anchors.centerIn: parent; text: "Cancel"
                           color: wp.k.gilt1; font.family: wp.k.serif; font.pixelSize: k.sm }
                    TapHandler { onTapped: wp._nudgeOpen = false }
                }
            }
        }
    }
}