// Hud.qml -- NCDE Universal Search
// Searches: Apps - Recent Files - Running Windows
// CDE drawer evolution -- type anything, find everything

import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: hud
    visible: false
    x: 80; y: 32
    width: 580; z: 1500
    height: hudContent.height

    // -- Public interface ------------------------------------------
    // Recent files cache -- loaded once per HUD open, not on every keystroke
    property var recentFiles: []

    function loadRecentFiles() {
        recentFiles = []
        try {
            var xhr = new XMLHttpRequest()
            xhr.open("GET", "file://" + launcher.homePath() +
                     "/.local/share/recently-used.xbel", false)
            xhr.send()
            if (xhr.responseText) {
                var xml   = xhr.responseText
                var hrefs = xml.match(/href="file:\/\/([^"]+)"/g) || []
                var count = 0
                for (var k = 0; k < hrefs.length && count < 30; k++) {
                    var rawPath = hrefs[k].replace('href="file://', '').replace('"', '')
                    var path    = decodeURIComponent(rawPath)
                    var fname   = path.split('/').pop()
                    recentFiles.push({ path: path, fname: fname })
                    count++
                }
            }
        } catch(e) { /* recently-used.xbel not available */ }
    }

    function show() {
        searchField.text = ""
        filteredModel.clear()
        activeCategory = "All"
        loadRecentFiles()           // load once per open -- never on keystrokes
        visible = true
        searchField.forceActiveFocus()
    }

    function hide() {
        visible = false
        resultsList.currentIndex = -1
    }

    property string activeCategory: "All"

    Connections {
        target: hudManager
        function onHudRequested() { hud.show() }
        function onHudDismissed()  { hud.hide() }
    }

    function activate() { hud.show() }

    // -- Universal search ------------------------------------------
    function searchAll(query) {
        filteredModel.clear()
        if (query === "") return

        var q = query.toLowerCase()
        var added = 0

        // 1. Running windows -- always first (most immediate)
        if (activeCategory === "All" || activeCategory === "Windows") {
            for (var i = 0; i < windowMgr.count; i++) {
                var entry = windowMgr.index(i, 0)
                var title = windowMgr.data(entry, Qt.UserRole+2) || ""
                var appId = windowMgr.data(entry, Qt.UserRole+3) || ""
                var winId = windowMgr.data(entry, Qt.UserRole+1) || 0
                var minimized = windowMgr.data(entry, Qt.UserRole+8) || false
                if (title.toLowerCase().indexOf(q) >= 0 || appId.toLowerCase().indexOf(q) >= 0) {
                    filteredModel.append({
                        name:        title || appId || "Window",
                        subtitle:    minimized ? "Minimized" : "Running",
                        action:      "window",
                        exec:        "",
                        windowIndex: i,
                        winId:       winId,
                        badge:       "WIN",
                        badgeColor:  ncde.cer.toString()
                    })
                    added++
                }
            }
        }

        // 2. Apps
        if (activeCategory === "All" || activeCategory === "Apps") {
            var apps = appMenuModel.getApps("All", query)
            for (var j = 0; j < apps.length && (activeCategory !== "All" || added < 12); j++) {
                filteredModel.append({
                    name:        apps[j].name,
                    subtitle:    apps[j].exec,
                    action:      "app",
                    exec:        apps[j].exec,
                    windowIndex: -1,
                    badge:       "APP",
                    badgeColor:  ncde.accent.toString()
                })
                added++
            }
        }

        // 3. Recent files -- search pre-loaded in-memory list (no I/O per keystroke)
        if (activeCategory === "All" || activeCategory === "Files") {
            var fileCount = 0
            for (var k = 0; k < hud.recentFiles.length && fileCount < 8; k++) {
                var rf    = hud.recentFiles[k]
                var rpath = rf.path
                var rfname = rf.fname
                var rdir  = rpath.substring(0, rpath.lastIndexOf('/'))
                if (rfname.toLowerCase().indexOf(q) < 0 &&
                    rpath.toLowerCase().indexOf(q) < 0) continue
                filteredModel.append({
                    name:        rfname,
                    subtitle:    rdir,
                    action:      "file",
                    exec:        rpath,
                    windowIndex: -1,
                    badge:       "FILE",
                    badgeColor:  ncde.verd.toString()
                })
                fileCount++
                added++
            }
        }
    }

    // -- Keyboard handling -----------------------------------------
    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            hide(); event.accepted = true
        } else if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
            if (resultsList.currentIndex >= 0) {
                var item = filteredModel.get(resultsList.currentIndex)
                activate_item(item)
                hide()
            }
            event.accepted = true
        } else if (event.key === Qt.Key_Down) {
            if (resultsList.currentIndex < filteredModel.count - 1)
                resultsList.currentIndex++
            event.accepted = true
        } else if (event.key === Qt.Key_Up) {
            if (resultsList.currentIndex > 0)
                resultsList.currentIndex--
            event.accepted = true
        } else if (event.key === Qt.Key_Tab) {
            // Cycle categories
            var cats = ["All", "Apps", "Files", "Windows"]
            var idx  = cats.indexOf(activeCategory)
            activeCategory = cats[(idx + 1) % cats.length]
            hud.searchAll(searchField.text)
            event.accepted = true
        }
    }

    function activate_item(item) {
        if (item.action === "window") {
            windowMgr.unminimizeWindow(item.winId)
            windowMgr.activateWindow(item.winId)
        } else if (item.action === "file") {
            launcher.launchExec("xdg-open \"" + item.exec + "\"")
        } else {
            launcher.launchExec(item.exec)
        }
    }

    ListModel { id: filteredModel }

    TapHandler { onTapped: hud.hide() }

    opacity: visible ? 1.0 : 0.0
    Behavior on opacity { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
    transform: Translate {
        y: hud.visible ? 0 : -10
        Behavior on y { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
    }

    // -- Main content ----------------------------------------------
    Column {
        id: hudContent
        width: parent.width
        spacing: 0

        // -- Search bar --------------------------------------------
        Rectangle {
            id: searchBar
            width: parent.width; height: 54
            color: ncde.popupBg
            border.color: ncde.accent; border.width: 1
            radius: filteredModel.count > 0 ? 0 : 8
            // Top corners always rounded
            Rectangle {
                anchors.top: parent.top; anchors.left: parent.left
                anchors.right: parent.right; height: 12; color: parent.color
                Rectangle { anchors.top:parent.top; anchors.left:parent.left
                    anchors.right:parent.right; height:8; radius:8; color:ncde.popupBg
                    border.color: ncde.accent; border.width: 1 }
            }

            Row {
                anchors.fill: parent
                anchors.leftMargin: 12; anchors.rightMargin: 10
                anchors.topMargin: 4;   anchors.bottomMargin: 4
                spacing: 8

                // NCDE logo -- matches dock BFB and top panel button
                Item {
                    width: 36; height: 36
                    anchors.verticalCenter: parent.verticalCenter
                    Canvas {
                        anchors.fill: parent
                        property color ac:      ncde.accent
                        property color bgCol:   ncde.activeBg
                        property color glowCol: ncde.glow
                        onAcChanged:      requestPaint()
                        onBgColChanged:   requestPaint()
                        onGlowColChanged: requestPaint()
                        Component.onCompleted: requestPaint()
                        onPaint: {
                            var ctx = getContext("2d"); ctx.clearRect(0,0,width,height)
                            var s=width, r=s*0.16
                            function rrect(x,y,w,h,rad) {
                                ctx.beginPath(); ctx.moveTo(x+rad,y); ctx.lineTo(x+w-rad,y)
                                ctx.arcTo(x+w,y,x+w,y+rad,rad); ctx.lineTo(x+w,y+h-rad)
                                ctx.arcTo(x+w,y+h,x+w-rad,y+h,rad); ctx.lineTo(x+rad,y+h)
                                ctx.arcTo(x,y+h,x,y+h-rad,rad); ctx.lineTo(x,y+rad)
                                ctx.arcTo(x,y,x+rad,y,rad); ctx.closePath()
                            }
                            rrect(0,0,s,s,r)
                            var bg=ctx.createLinearGradient(0,0,0,s)
                            bg.addColorStop(0,Qt.lighter(ac,1.5).toString())
                            bg.addColorStop(1,Qt.darker(ac,1.4).toString())
                            ctx.fillStyle=bg; ctx.fill()
                            var shine=ctx.createLinearGradient(0,0,0,s*0.45)
                            shine.addColorStop(0,"rgba(255,255,255,0.28)")
                            shine.addColorStop(1,"rgba(255,255,255,0.00)")
                            rrect(0,0,s,s,r); ctx.fillStyle=shine; ctx.fill()
                            ctx.beginPath(); ctx.arc(s*0.50,s*1.14,s*0.72,0,Math.PI*2)
                            ctx.fillStyle=Qt.rgba(bgCol.r*0.4,bgCol.g*0.4,bgCol.b*0.4,0.90).toString()
                            ctx.fill()
                            ctx.fillStyle="rgba(255,255,255,0.95)"
                            ctx.font="bold "+Math.round(s*0.52)+"px serif"
                            ctx.textAlign="center"; ctx.textBaseline="middle"
                            ctx.fillText("N",s*0.50,s*0.38)
                            rrect(0,0,s,s,r)
                            ctx.strokeStyle=Qt.rgba(glowCol.r,glowCol.g,glowCol.b,0.55).toString()
                            ctx.lineWidth=1; ctx.stroke()
                        }
                    }
                }

                // Divider
                Rectangle {
                    width: 1; height: 32; color: ncde.accentMuted; opacity: 0.4
                    anchors.verticalCenter: parent.verticalCenter
                }

                // Search input
                Item {
                    width: parent.width - 36 - 8 - 1 - 8 - categoryRow.width - 8
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        anchors.left: parent.left; anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Search apps, files, windows..."
                        color: WallInk.inked(ncde.accentMuted); font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                        visible: searchField.text === ""
                    }

                    TextInput {
                        id: searchField
                        anchors.fill: parent
                        anchors.leftMargin: 10; anchors.rightMargin: 8
                        anchors.topMargin: 6; anchors.bottomMargin: 6
                        color: WallInk.inked(ncde.panelText); font.pixelSize: theme.fontMedium
                        font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing; clip: true; selectByMouse: true
                        onTextChanged: {
                            if (text === "") {
                                filteredModel.clear()
                                resultsList.currentIndex = -1
                            } else {
                                hud.searchAll(text)
                                resultsList.currentIndex = filteredModel.count > 0 ? 0 : -1
                            }
                        }
                    }
                }

                // Category pills
                Row {
                    id: categoryRow
                    spacing: 4
                    anchors.verticalCenter: parent.verticalCenter

                    Repeater {
                        model: ["All", "Apps", "Files", "Windows"]
                        Rectangle {
                            width: catTxt.width + 12; height: 20; radius: 10
                            color: hud.activeCategory === modelData
                                ? Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.25)
                                : Qt.rgba(1,1,1,0.05)
                            border.color: hud.activeCategory === modelData
                                ? ncde.accent : Qt.rgba(1,1,1,0.1)
                            border.width: 1
                            Behavior on color { ColorAnimation { duration: 100 } }
                            Text {
                                id: catTxt
                                anchors.centerIn: parent
                                text: modelData
                                color: WallInk.inked(hud.activeCategory === modelData
                                    ? ncde.accent : ncde.accentMuted)
                                font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                                font.bold: hud.activeCategory === modelData
                            }
                            TapHandler {
                                onTapped: {
                                    hud.activeCategory = modelData
                                    hud.searchAll(searchField.text)
                                }
                            }
                        }
                    }
                }
            }
        }

        // -- Results list ------------------------------------------
        Rectangle {
            width: parent.width
            height: Math.min(filteredModel.count, 8) * 42
            color: ncde.popupBg
            border.color: ncde.accent; border.width: 1
            visible: filteredModel.count > 0

            // Teal LED underglow
            Rectangle {
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 4; z: 1
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0.0; color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.12) }
                    GradientStop { position: 1.0; color: Qt.rgba(ncde.glow.r, ncde.glow.g, ncde.glow.b, 0.0) }
                }
            }

            ListView {
                id: resultsList
                anchors.fill: parent; anchors.margins: 2
                clip: true; model: filteredModel
                currentIndex: filteredModel.count > 0 ? 0 : -1

                delegate: Rectangle {
                    width: resultsList.width; height: 42
                    color: "transparent"

                    Rectangle {
                        anchors.fill: parent; radius: 3
                        color: resultsList.currentIndex === index
                            ? Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.15)
                            : "transparent"
                        border.color: resultsList.currentIndex === index
                            ? Qt.rgba(ncde.accent.r,ncde.accent.g,ncde.accent.b,0.4)
                            : "transparent"
                        border.width: 1
                        Behavior on color { ColorAnimation { duration: 60 } }
                    }

                    HoverHandler {
                        onHoveredChanged: if (hovered) resultsList.currentIndex = index
                    }

                    Row {
                        anchors.left: parent.left; anchors.leftMargin: 12
                        anchors.right: parent.right; anchors.rightMargin: 12
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10

                        // Type badge
                        Rectangle {
                            width: 36; height: 16; radius: 8
                            color: Qt.rgba(0,0,0,0.3)
                            border.color: model.badgeColor || ncde.accent
                            border.width: 1
                            anchors.verticalCenter: parent.verticalCenter
                            Text {
                                anchors.centerIn: parent
                                text: model.badge || "APP"
                                color: WallInk.inked(model.badgeColor || ncde.accent)
                                font.pixelSize: theme.fontSmall; font.bold: true; font.family: "TerminalVector"
                                font.letterSpacing: 0.5
                            }
                        }

                        // Name + subtitle
                        Column {
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 2
                            width: parent.width - 36 - 10 - 50

                            Text {
                                text: model.name
                                color: WallInk.inked(resultsList.currentIndex === index
                                    ? ncde.accent : ncde.panelText)
                                font.pixelSize: theme.fontMedium; font.family: theme.fontFamily; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                                font.bold: resultsList.currentIndex === index
                                elide: Text.ElideRight; width: parent.width
                                Behavior on color { ColorAnimation { duration: 60 } }
                            }
                            Text {
                                text: model.subtitle || ""
                                color: WallInk.inked(ncde.accentMuted); font.pixelSize: theme.fontSmall
                                font.family: "TerminalVector"
                                elide: Text.ElideRight; width: parent.width
                                visible: text !== ""
                            }
                        }

                        // Action hint
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: resultsList.currentIndex === index
                                ? (model.action === "window" ? "[enter] focus"
                                 : model.action === "file"   ? "[enter] open"
                                 : "[enter] launch") : ""
                            color: WallInk.inked(ncde.accentMuted)
                            font.pixelSize: theme.fontSmall; font.family: "TerminalVector"
                        }
                    }

                    TapHandler {
                        onTapped: { hud.activate_item(filteredModel.get(index)); hud.hide() }
                    }
                }
            }
        }

        // -- Empty state -------------------------------------------
        Rectangle {
            width: parent.width; height: 40
            color: ncde.popupBg
            border.color: ncde.accentMuted; border.width: 1
            visible: filteredModel.count === 0 && searchField.text !== ""
            Text {
                anchors.centerIn: parent
                text: "Nothing found for \"" + searchField.text + "\" -- Tab to change category"
                color: WallInk.inked(ncde.accentMuted); font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
            }
        }

        // -- Footer hint (only when empty/idle) --------------------
        Rectangle {
            width: parent.width; height: 28
            color: Qt.rgba(ncde.popupBg.r,ncde.popupBg.g,ncde.popupBg.b,0.85)
            border.color: Qt.rgba(ncde.border.r,ncde.border.g,ncde.border.b,0.5)
            border.width: 1
            radius: 8
            visible: searchField.text === ""

            Row {
                anchors.centerIn: parent; spacing: 16
                Repeater {
                    model: [
                        { key: "^v",  hint: "navigate" },
                        { key: "[enter]",   hint: "activate" },
                        { key: "Tab", hint: "category"  },
                        { key: "Esc", hint: "close"     },
                    ]
                    Row {
                        spacing: 4
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle {
                            width: keyTxt.width + 8; height: 16; radius: 3
                            color: Qt.rgba(1,1,1,0.07)
                            border.color: Qt.rgba(1,1,1,0.15); border.width: 1
                            Text { id: keyTxt; anchors.centerIn: parent
                                   text: modelData.key; color: WallInk.inked(ncde.accentMuted)
                                   font.pixelSize: theme.fontSmall; font.family: "TerminalVector" }
                        }
                        Text { text: modelData.hint; color: WallInk.inked(Qt.rgba(ncde.accentMuted.r,ncde.accentMuted.g,ncde.accentMuted.b,0.7))
                               font.pixelSize: theme.fontSmall; font.family: theme.fontFamily; font.weight: settings.fontWeight; font.italic: settings.fontItalic; font.letterSpacing: theme.letterSpacing
                               anchors.verticalCenter: parent.verticalCenter }
                    }
                }
            }
        }
    }
}
