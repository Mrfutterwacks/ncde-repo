// DockAppsTab.qml — Dock pin manager.
// Carousel (left): click flips to a card; double-click adds it to the dock.
// Drag strip (bottom-left): drag rightward into dock panel to add.
// Dock list (right): swipe left or tap × to remove. Apply Dock saves.
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    clip: false
    property var k: SetTheme
    property int liftedIndex: -1

    // ── parchment app-cover card ──────────────────────────────────────────
    component AppCard: Canvas {
        renderStrategy: Canvas.Cooperative
        layer.enabled: true
        property bool pinned: false
        antialiasing: true
        onPinnedChanged: requestPaint()
        onWidthChanged:  requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset()
            var w = width, h = height
            function rr(x, y, rw, rh, r) {
                r = Math.min(r, rh/2, rw/2)
                ctx.beginPath()
                ctx.moveTo(x+r, y); ctx.lineTo(x+rw-r, y)
                ctx.quadraticCurveTo(x+rw, y, x+rw, y+r)
                ctx.lineTo(x+rw, y+rh-r)
                ctx.quadraticCurveTo(x+rw, y+rh, x+rw-r, y+rh)
                ctx.lineTo(x+r, y+rh)
                ctx.quadraticCurveTo(x, y+rh, x, y+rh-r)
                ctx.lineTo(x, y+r)
                ctx.quadraticCurveTo(x, y, x+r, y)
                ctx.closePath()
            }
            var pad = 3
            var pg = ctx.createLinearGradient(0, 0, 0, h)
            if (pinned) {
                pg.addColorStop(0, "#f0e8c4"); pg.addColorStop(1, "#c8b870")
            } else {
                pg.addColorStop(0, ncde.surface); pg.addColorStop(1, ncde.surfaceAlt)
            }
            rr(pad, pad, w-2*pad, h-2*pad, 10)
            ctx.fillStyle = pg; ctx.fill()
            ctx.lineWidth = pinned ? 2.8 : 2; ctx.strokeStyle = ncde.gilt0; ctx.stroke()
            rr(pad+4, pad+4, w-2*pad-8, h-2*pad-8, 7)
            ctx.lineWidth = 1; ctx.strokeStyle = pinned ? ncde.gilt3 : ncde.gilt1; ctx.stroke()
            ctx.beginPath()
            ctx.moveTo(w*0.28, pad+12)
            ctx.quadraticCurveTo(w*0.5, pad+1, w*0.72, pad+12)
            ctx.lineWidth = 1.4; ctx.strokeStyle = ncde.gilt1; ctx.stroke()
            ctx.beginPath()
            ctx.moveTo(pad+12, h-h*0.29); ctx.lineTo(w-pad-12, h-h*0.29)
            ctx.lineWidth = 1; ctx.strokeStyle = ncde.gilt1; ctx.globalAlpha = 0.65; ctx.stroke(); ctx.globalAlpha = 1
            ctx.fillStyle = ncde.gilt3
            var cd = [[pad+8,pad+8],[w-pad-8,pad+8],[pad+8,h-pad-8],[w-pad-8,h-pad-8]]
            for (var i = 0; i < 4; i++) {
                ctx.beginPath(); ctx.arc(cd[i][0], cd[i][1], 2.2, 0, 2*Math.PI); ctx.fill()
            }
            if (pinned) {
                ctx.beginPath(); ctx.arc(w-pad-10, pad+10, 6, 0, 2*Math.PI)
                ctx.fillStyle = ncde.verd; ctx.fill()
                ctx.fillStyle = "#fff"; ctx.font = "bold 8px sans-serif"
                ctx.textAlign = "center"; ctx.textBaseline = "middle"
                ctx.fillText("✓", w-pad-10, pad+10)
            }
        }
    }

    // ── installed apps (loaded once at startup) ───────────────────────────
    property var _appsModel: []
    Component.onCompleted: {
        _appsModel = settings.installedApps()
        var src = settings.dockApps
        for (var i = 0; i < src.length; i++) dockModel.append(src[i])
    }

    // ── local dock model ──────────────────────────────────────────────────
    ListModel { id: dockModel }

    function _inDock(exec) {
        for (var i = 0; i < dockModel.count; i++)
            if (dockModel.get(i).exec === exec) return true
        return false
    }
    function addToDock(app) {
        if (app && !_inDock(app.exec)) dockModel.append({ name: app.name, exec: app.exec, icon: app.icon || "" })
    }
    function _applyToDock() {
        var arr = []
        for (var i = 0; i < dockModel.count; i++) {
            var o = dockModel.get(i)
            arr.push({ name: o.name, exec: o.exec, icon: o.icon || "" })
        }
        settings.setDockApps(arr)
        settings.saveDockPrefs()
    }

    // ── ghost card (follows pointer during drag from dragStrip) ───────────
    Item {
        id: ghost
        parent: root
        z: 200; visible: false; opacity: 0.92
        width: 78; height: 100
        property string appName: ""
        property var    appData: null

        AppCard { anchors.fill: parent; pinned: false }
        MuchaAppIcon {
            appName: ghost.appName; appIcon: ghost.appName; size: 44
            anchors.horizontalCenter: parent.horizontalCenter; y: 10
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height - 24
            text: ghost.appName; font.family: root.k.titles; font.pixelSize: k.sm
            color: root.k.ink; width: 72; horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight
        }
    }

    // ── header ────────────────────────────────────────────────────────────
    Item {
        id: hdr; anchors.top: parent.top; height: 44; width: parent.width
        Text {
            anchors.left: parent.left; anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            text: "DOCK APPS"; color: root.k.wine2
            font.family: root.k.display; font.bold: true; font.pixelSize: k.lg
        }
        Text {
            anchors.right: parent.right; anchors.rightMargin: 2
            anchors.verticalCenter: parent.verticalCenter
            text: "Click to flip · double-click → dock  ·  swipe left or × to remove"
            color: root.k.inkSoft; font.family: root.k.fell; font.italic: true; font.pixelSize: k.sm
        }
    }

    // ── main row ──────────────────────────────────────────────────────────
    Row {
        id: mainRow
        anchors.top: hdr.bottom; anchors.bottom: footer.top; anchors.bottomMargin: 8
        anchors.left: parent.left; anchors.right: parent.right
        spacing: 12

        // ── LEFT: carousel + drag strip ───────────────────────────────────
        Item {
            id: gridPanel
            width: parent.width * 0.56; height: parent.height

            // True when ghost center is over the dock panel
            property bool ghostOverDock: ghost.visible &&
                (ghost.x + ghost.width / 2) > (gridPanel.x + gridPanel.width + mainRow.spacing)

            Text {
                id: carouselHdr
                anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter
                text: "ALL APPS"; color: root.k.gilt1; font.family: root.k.display
                font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2
            }
            Rectangle {
                id: carouselDiv
                anchors.top: carouselHdr.bottom; anchors.topMargin: 2
                height: 1; width: parent.width; color: root.k.gilt1; opacity: 0.35
            }

            // Frosted Tiffany glass scrim over the carousel band
            Canvas {
                id: appScrim
                anchors.top: carouselDiv.bottom; anchors.topMargin: 6
                anchors.left: parent.left; anchors.right: parent.right
                anchors.bottom: dragStrip.top; anchors.bottomMargin: 4
                renderStrategy: Canvas.Cooperative
                layer.enabled: true
                    onPaint: {
                        var ctx = getContext("2d"); ctx.reset()
                        var w = width, h = height
                        ctx.fillStyle = "rgba(16,20,26,0.45)"; ctx.fillRect(0, 0, w, h)
                        var fr = ctx.createLinearGradient(0, 0, w, h)
                        fr.addColorStop(0.0, "rgba(255,255,255,0.08)")
                        fr.addColorStop(0.4, "rgba(255,255,255,0.02)")
                        fr.addColorStop(1.0, "rgba(255,255,255,0.0)")
                        ctx.fillStyle = fr; ctx.fillRect(0, 0, w, h)
                        function tint(cx, cy, r, col){ var g = ctx.createRadialGradient(cx,cy,0,cx,cy,r); g.addColorStop(0,col); g.addColorStop(1,"rgba(0,0,0,0)"); ctx.fillStyle=g; ctx.fillRect(0,0,w,h) }
                        tint(w*0.14, h*0.16, Math.max(w,h)*0.55, "rgba(86,176,150,0.09)")
                        tint(w*0.86, h*0.18, Math.max(w,h)*0.55, "rgba(120,150,210,0.08)")
                        tint(w*0.50, h*0.96, Math.max(w,h)*0.55, "rgba(233,201,124,0.07)")
                        var sh = ctx.createLinearGradient(0, 0, 0, h*0.14)
                        sh.addColorStop(0.0, "rgba(255,255,255,0.12)")
                        sh.addColorStop(1.0, "rgba(255,255,255,0.0)")
                        ctx.fillStyle = sh; ctx.fillRect(0, 0, w, h*0.14)
                    }
                Component.onCompleted: requestPaint()
                onWidthChanged: requestPaint()
                onHeightChanged: requestPaint()
            }
            // PathView — click flips, double-click adds. Same pattern as WallpapersTab.
            PathView {
                id: appFlow
                anchors.top: carouselDiv.bottom; anchors.topMargin: 6
                anchors.left: parent.left; anchors.right: parent.right
                anchors.bottom: dragStrip.top; anchors.bottomMargin: 4
                model: root._appsModel
                pathItemCount: Math.min(7, root._appsModel.length)
                preferredHighlightBegin: 0.5; preferredHighlightEnd: 0.5
                highlightRangeMode: PathView.StrictlyEnforceRange
                snapMode: PathView.SnapOneItem
                highlightMoveDuration: 700
                clip: true
                interactive: false
                onCurrentIndexChanged: root.liftedIndex = -1

                path: Path {
                    startX: appFlow.width * 0.30; startY: appFlow.height * 0.40
                    PathAttribute { name: "iScale";   value: 0.40 }
                    PathAttribute { name: "iAngle";   value: 55 }
                    PathAttribute { name: "iZ";       value: 0 }
                    PathAttribute { name: "iOpacity"; value: 0.40 }
                    PathLine { x: appFlow.width * 0.43; y: appFlow.height * 0.40 }
                    PathPercent { value: 0.42 }
                    PathAttribute { name: "iScale";   value: 0.84 }
                    PathAttribute { name: "iAngle";   value: 55 }
                    PathAttribute { name: "iZ";       value: 1 }
                    PathAttribute { name: "iOpacity"; value: 0.80 }
                    PathLine { x: appFlow.width * 0.50; y: appFlow.height * 0.40 }
                    PathPercent { value: 0.50 }
                    PathAttribute { name: "iScale";   value: 1.0 }
                    PathAttribute { name: "iAngle";   value: 0 }
                    PathAttribute { name: "iZ";       value: 10 }
                    PathAttribute { name: "iOpacity"; value: 1.0 }
                    PathLine { x: appFlow.width * 0.57; y: appFlow.height * 0.40 }
                    PathPercent { value: 0.58 }
                    PathAttribute { name: "iScale";   value: 0.84 }
                    PathAttribute { name: "iAngle";   value: -55 }
                    PathAttribute { name: "iZ";       value: 1 }
                    PathAttribute { name: "iOpacity"; value: 0.80 }
                    PathLine { x: appFlow.width * 0.70; y: appFlow.height * 0.40 }
                    PathAttribute { name: "iScale";   value: 0.40 }
                    PathAttribute { name: "iAngle";   value: -55 }
                    PathAttribute { name: "iZ";       value: 0 }
                    PathAttribute { name: "iOpacity"; value: 0.40 }
                }

                delegate: Item {
                    id: appTile
                    width: 168; height: 222
                    scale:   PathView.iScale === undefined ? 0.84 : PathView.iScale
                    z:       isLifted ? 50 : (PathView.iZ === undefined ? 0 : PathView.iZ)
                    opacity: PathView.iOpacity === undefined ? 0.72 : PathView.iOpacity
                    property bool isCurrent: PathView.isCurrentItem
                    property bool isLifted: root.liftedIndex === index
                    // dockModel.count in the expression makes QML re-evaluate when dock changes
                    property bool pinned: { var _c = dockModel.count; return root._inDock(modelData.exec) }

                    transform: Rotation {
                        origin.x: appTile.width / 2; origin.y: appTile.height / 2
                        axis { x: 0; y: 1; z: 0 }
                        angle: PathView.iAngle === undefined ? 0 : PathView.iAngle
                    }

                    // Tiffany jewel glow behind the active cover
                    Canvas {
                        id: appGlow
                        x: -48; y: -48
                        width: parent.width + 96; height: parent.height + 96
                        z: -1
                        renderStrategy: Canvas.Cooperative
                        layer.enabled: true
                        opacity: appTile.PathView.isCurrentItem ? 1.0 : 0.0
                        Behavior on opacity { NumberAnimation { duration: 440; easing.type: Easing.OutCubic } }
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
                    Item {
                        id: appCard
                        anchors.fill: parent
                        scale: appTile.isLifted ? 1.30 : 1.0
                        y:     appTile.isLifted ? -12  : 0
                        Behavior on scale { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                        Behavior on y     { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                        AppCard { anchors.fill: parent; pinned: appTile.pinned }
                        MuchaAppIcon {
                            appName: modelData.name; appIcon: modelData.name; size: 90
                            anchors.horizontalCenter: parent.horizontalCenter; y: 18
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width - 28; y: parent.height * 0.75
                            text: modelData.name
                            color: root.k.ink; font.family: root.k.serif; font.bold: true; font.pixelSize: k.md
                            horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight
                        }
                        // "ADD" pill — always on non-pinned cards; tap logic handles navigate vs add
                        Rectangle {
                            visible: !appTile.pinned
                            anchors.horizontalCenter: parent.horizontalCenter
                            y: parent.height - 32
                            width: 72; height: 20; radius: 10
                            color: root.k.wine2; opacity: 0.88
                            Text {
                                anchors.centerIn: parent
                                text: "▶  ADD TO DOCK"; color: root.k.gilt5
                                font.family: root.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 1
                            }
                        }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                        TapHandler {
                            gesturePolicy: TapHandler.WithinBounds
                            grabPermissions: PointerHandler.CanTakeOverFromHandlersOfSameType
                            onTapped: {
                                if (tapCount >= 2) {
                                    stepDelay.stop(); stepDelay.dir = 0
                                    root.addToDock(modelData)
                                    root.liftedIndex = index
                                    return
                                }
                                if (index === appFlow.currentIndex) return
                                stepDelay.dir = (appTile.x + appTile.width/2 < appFlow.width/2) ? -1 : 1
                                stepDelay.restart()
                            }
                        }
                    }
                    // No DragHandler here — PathView owns all swipe/drag for carousel scrolling
                    // CoverFlow: separator + ShaderEffectSource reflection (gradient-fade; no GraphicalEffects)
                    Rectangle {
                        width: parent.width; height: 1
                        y: parent.height + 1
                        color: Qt.rgba(root.k.inkSoft.r, root.k.inkSoft.g, root.k.inkSoft.b, 0.18)
                    }
                    Item {
                        width: parent.width; height: 95
                        y: parent.height + 3
                        clip: true
                        ShaderEffectSource {
                            width: parent.width
                            height: appTile.height
                            y: -(appTile.height - parent.height)
                            sourceItem: appTile
                            hideSource: false
                            live: !animPolicy.screenIdle
                            transform: Scale { yScale: -1; origin.y: appTile.height / 2 }
                            opacity: 0.5
                            layer.enabled: true
                        }
                        Rectangle {
                            anchors.fill: parent
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: Qt.rgba(root.k.paper3.r, root.k.paper3.g, root.k.paper3.b, 0.0) }
                                GradientStop { position: 1.0; color: root.k.paper3 }
                            }
                        }
                    }
                }

                Timer {
                    id: stepDelay
                    interval: Qt.styleHints.mouseDoubleClickInterval
                    repeat: false
                    property int dir: 0
                    onTriggered: {
                        if (dir < 0) appFlow.decrementCurrentIndex()
                        else if (dir > 0) appFlow.incrementCurrentIndex()
                        dir = 0
                    }
                }
                Timer { id: wheelCooldown; interval: 350; repeat: false }
                WheelHandler {
                    acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                    onWheel: function(ev) {
                        if (wheelCooldown.running) return
                        if (ev.angleDelta.y < 0 || ev.angleDelta.x < 0) appFlow.incrementCurrentIndex()
                        else appFlow.decrementCurrentIndex()
                        wheelCooldown.restart()
                    }
                }
                Keys.onLeftPressed:  decrementCurrentIndex()
                Keys.onRightPressed: incrementCurrentIndex()
            }

            // ── drag strip — drag this bar rightward into the dock panel ──
            Item {
                id: dragStrip
                anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                height: 38

                property var currentApp: {
                    var idx = appFlow.currentIndex
                    if (root._appsModel && idx >= 0 && idx < root._appsModel.length)
                        return root._appsModel[idx]
                    return null
                }
                property point _lastRootPos: Qt.point(0, 0)

                Rectangle {
                    anchors.fill: parent; radius: 7
                    color: Qt.rgba(root.k.wine2.r, root.k.wine2.g, root.k.wine2.b, 0.08)
                    border.color: gridPanel.ghostOverDock ? root.k.gilt3 : root.k.gilt1
                    border.width: gridPanel.ghostOverDock ? 2 : 1
                    Behavior on border.color { ColorAnimation { duration: 140 } }
                }

                // Drag handle glyph
                Text {
                    anchors.left: parent.left; anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: "⠿"; color: root.k.gilt2; font.pixelSize: k.lg
                }

                MuchaAppIcon {
                    id: stripIcon
                    appName: dragStrip.currentApp ? dragStrip.currentApp.name : ""
                    appIcon: dragStrip.currentApp ? dragStrip.currentApp.name : ""
                    size: 26
                    anchors.left: parent.left; anchors.leftMargin: 34
                    anchors.verticalCenter: parent.verticalCenter
                    visible: dragStrip.currentApp !== null
                }

                Text {
                    anchors.left: parent.left; anchors.leftMargin: 68
                    anchors.right: stripArrow.left; anchors.rightMargin: 4
                    anchors.verticalCenter: parent.verticalCenter
                    text: dragStrip.currentApp ? dragStrip.currentApp.name : "—"
                    color: root.k.ink; font.family: root.k.serif; font.bold: true; font.pixelSize: k.sm
                    elide: Text.ElideRight
                }

                Text {
                    id: stripArrow
                    anchors.right: parent.right; anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: "drag → dock"; color: root.k.gilt2
                    font.family: root.k.fell; font.italic: true; font.pixelSize: k.sm
                }

                HoverHandler { cursorShape: Qt.SizeHorCursor }

                DragHandler {
                    id: stripDrag
                    target: null
                    enabled: dragStrip.currentApp !== null

                    onActiveChanged: {
                        if (active) {
                            var app = dragStrip.currentApp
                            ghost.appName = app ? app.name : ""
                            ghost.appData = app
                            ghost.visible = app !== null
                        } else {
                            ghost.visible = false
                            if (ghost.appData && dragStrip._lastRootPos.x > gridPanel.width + mainRow.spacing)
                                root.addToDock(ghost.appData)
                            ghost.appData = null
                        }
                    }

                    onCentroidChanged: {
                        if (active) {
                            var lp = dragStrip.mapToItem(root, centroid.position.x, centroid.position.y)
                            ghost.x = lp.x - ghost.width / 2
                            ghost.y = lp.y - ghost.height / 2
                            dragStrip._lastRootPos = lp
                        }
                    }
                }
            }
        }

        // ── RIGHT: dock pin list ──────────────────────────────────────────
        Item {
            id: dockPanel
            width: parent.width - gridPanel.width - mainRow.spacing; height: parent.height

            Rectangle {
                anchors.fill: parent; radius: 8
                color: Qt.rgba(root.k.paper0.r, root.k.paper0.g, root.k.paper0.b, 0.04)
                border.color: gridPanel.ghostOverDock ? root.k.gilt3 : root.k.gilt1
                border.width: gridPanel.ghostOverDock ? 2 : 1
                Behavior on border.color { ColorAnimation { duration: 140 } }
            }

            Text {
                id: dockHdr2
                anchors.top: parent.top; anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                text: "YOUR DOCK  —  " + dockModel.count + " pins"
                color: root.k.gilt1; font.family: root.k.display; font.bold: true
                font.pixelSize: k.sm; font.letterSpacing: 2
            }

            Text {
                anchors.top: dockHdr2.bottom; anchors.topMargin: 6
                anchors.horizontalCenter: parent.horizontalCenter
                visible: dockModel.count === 0
                text: "Drag an app here to pin it"
                color: root.k.inkSoft; font.family: root.k.fell; font.italic: true; font.pixelSize: k.sm
            }

            Flickable {
                anchors.top: dockHdr2.bottom; anchors.topMargin: 8
                anchors.left: parent.left; anchors.leftMargin: 8
                anchors.right: parent.right; anchors.rightMargin: 8
                anchors.bottom: parent.bottom; anchors.bottomMargin: 8
                contentHeight: pinCol.height
                interactive: contentHeight > height
                clip: true
                // VerticalFlick only — lets horizontal DragHandler on rows reach events
                flickableDirection: Flickable.VerticalFlick
                ScrollBar.vertical: NCDEScrollBar {}

                Column {
                    id: pinCol; width: parent.width; spacing: 4

                    Repeater {
                        model: dockModel
                        delegate: Item {
                            id: pinRow
                            width: pinCol.width; height: 44
                            clip: false

                            Behavior on x {
                                enabled: !pinDrag.active
                                SpringAnimation { spring: 9; damping: 0.8 }
                            }

                            // Parchment row background + red reveal as row slides left
                            Rectangle {
                                anchors.fill: parent; radius: 6
                                color: Qt.rgba(root.k.paper0.r, root.k.paper0.g, root.k.paper0.b, 0.92)
                                border.color: root.k.gilt1; border.width: 1
                                Rectangle {
                                    anchors.fill: parent; radius: 6; color: ncde.rose
                                    opacity: Math.max(0, Math.min(0.32, -(pinRow.x + 40) / 180))
                                }
                            }

                            // "⟵ remove" hint fades in as row slides left
                            Text {
                                anchors.right: removeBtn.left; anchors.rightMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                                text: "⟵ remove"; color: ncde.rose
                                font.family: root.k.fell; font.italic: true; font.pixelSize: k.sm
                                opacity: Math.max(0, Math.min(1, -(pinRow.x + 20) / 60))
                            }

                            // Index badge
                            Rectangle {
                                width: 20; height: 20; radius: 10
                                anchors.left: parent.left; anchors.leftMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                color: root.k.wine2; opacity: 0.75
                                Text {
                                    anchors.centerIn: parent; text: index + 1
                                    color: root.k.gilt5; font.family: root.k.mono; font.pixelSize: k.sm
                                }
                            }

                            MuchaAppIcon {
                                appName: name; appIcon: name; size: 30
                                anchors.left: parent.left; anchors.leftMargin: 34
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Text {
                                anchors.left: parent.left; anchors.leftMargin: 74
                                anchors.right: reorderCol.left; anchors.rightMargin: 4
                                anchors.verticalCenter: parent.verticalCenter
                                text: name; font.family: root.k.serif; font.pixelSize: k.md
                                color: root.k.ink; elide: Text.ElideRight
                            }

                            Column {
                                id: reorderCol
                                anchors.right: removeBtn.left; anchors.rightMargin: 6
                                anchors.verticalCenter: parent.verticalCenter; spacing: 1
                                Text {
                                    text: "▲"; font.pixelSize: k.sm
                                    color: index > 0 ? root.k.gilt2 : root.k.gilt0
                                    opacity: upHov.hovered ? 1 : 0.6
                                    HoverHandler { id: upHov }
                                    TapHandler { onTapped: if (index > 0) dockModel.move(index, index-1, 1) }
                                }
                                Text {
                                    text: "▼"; font.pixelSize: k.sm
                                    color: index < dockModel.count-1 ? root.k.gilt2 : root.k.gilt0
                                    opacity: dnHov.hovered ? 1 : 0.6
                                    HoverHandler { id: dnHov }
                                    TapHandler { onTapped: if (index < dockModel.count-1) dockModel.move(index, index+1, 1) }
                                }
                            }

                            // × remove button (direct removal — no deferred animation)
                            Item {
                                id: removeBtn; width: 28; height: 28
                                anchors.right: parent.right; anchors.rightMargin: 6
                                anchors.verticalCenter: parent.verticalCenter
                                HoverHandler { id: rmHov }
                                Rectangle {
                                    anchors.fill: parent; radius: 14
                                    color: rmHov.hovered ? ncde.rose : "transparent"; opacity: 0.85
                                }
                                Text {
                                    anchors.centerIn: parent; text: "×"
                                    color: rmHov.hovered ? "#fff" : root.k.gilt1
                                    font.pixelSize: k.lg; font.family: root.k.serif
                                }
                                TapHandler {
                                    onTapped: dockModel.remove(index)
                                }
                            }

                            // Swipe left to remove — yAxis disabled so only horizontal gesture fires
                            DragHandler {
                                id: pinDrag
                                target: pinRow
                                yAxis.enabled: false
                                onActiveChanged: {
                                    if (!active) {
                                        if (pinRow.x < -80) {
                                            dockModel.remove(index)
                                        } else {
                                            pinRow.x = 0
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // ── footer ────────────────────────────────────────────────────────────
    Row {
        id: footer
        anchors.bottom: parent.bottom; anchors.right: parent.right
        spacing: 10; height: 34

        Rectangle {
            width: 100; height: 32; radius: 6; color: "transparent"
            border.color: root.k.gilt1; border.width: 1
            Text {
                anchors.centerIn: parent; text: "Reset"
                color: root.k.gilt1; font.family: root.k.serif; font.pixelSize: k.md
            }
            TapHandler {
                onTapped: {
                    root.liftedIndex = -1
                    dockModel.clear()
                    var src = settings.dockApps
                    for (var i = 0; i < src.length; i++) dockModel.append(src[i])
                }
            }
        }

        Rectangle {
            width: 120; height: 32; radius: 6
            border.color: root.liftedIndex >= 0 ? root.k.gilt5 : root.k.gilt0
            border.width: root.liftedIndex >= 0 ? 3 : 2
            Behavior on border.color { ColorAnimation { duration: 180 } }
            gradient: Gradient {
                GradientStop { position: 0; color: root.k.gilt4 }
                GradientStop { position: 1; color: root.k.gilt3 }
            }
            Text {
                anchors.centerIn: parent; text: "Apply Dock"
                color: root.k.wine1; font.family: root.k.display; font.bold: true; font.pixelSize: k.sm
            }
            TapHandler {
                onTapped: {
                    root._applyToDock()
                    root.liftedIndex = -1
                    notifications.notify("Dock", "Dock updated — reload to see changes", "", 3000)
                }
            }
        }
    }
}