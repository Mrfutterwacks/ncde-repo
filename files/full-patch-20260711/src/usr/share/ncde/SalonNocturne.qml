// SalonNocturne.qml — Mucha Art Nouveau music player (NCDE Poseidon).
// Full triptych: left=transport+volume, centre=gramophone+visualizer, right=queue.
// Floating window — place inside a transparent FramelessWindowHint Window in main.qml.
// Uses widget_data (DesktopWidget C++ backend) for Spotify/MPRIS via playerctl.
import QtQuick

Item {
    id: salonRoot

    // Bind to the parent QQuickWindow so the drag handle can reposition it
    property var parentWindow: null

    // ─── Internal palette ──────────────────────────────────────────────────────
    property string paletteName: "twilight"
    readonly property var palettes: ({
        twilight: {
            jewelHi:    "#6b3fc4", jewel:  ncde.wine1, jewelLo:  "#1a0b3a",
            amberHi:    "#f4cc6b", amber:  "#c98a2b", amberLo:  "#5e3c08",
            violetHi:   "#9a64ff", violet: ncde.accent, violetLo: "#1e0d4a",
            leaf:       "#2a4a3a",
            leadBright: "#f0d27a", lead:   "#b88a32", leadDeep: "#4a3208",
            glowHi:     "#b489ff", glowMid:ncde.accent,
            text:       ncde.surfaceAlt, textDim:"#b89cc4"
        },
        cathedral: {
            jewelHi:    "#4fb89c", jewel:  "#1d6b58", jewelLo:  "#082624",
            amberHi:    "#f4b347", amber:  "#b27418", amberLo:  "#4a2e02",
            violetHi:   "#5fa3f4", violet: "#1d4a8a", violetLo: "#0a1a3a",
            leaf:       "#1d4438",
            leadBright: "#f4c14a", lead:   "#b07a1c", leadDeep: "#4a2e02",
            glowHi:     "#87d8c2", glowMid:"#1d6b58",
            text:       ncde.surfaceAlt, textDim:"#9cbfb8"
        },
        seaglass: {
            jewelHi:    "#6ad2c4", jewel:  "#2c8a7a", jewelLo:  "#0e3a3a",
            amberHi:    "#c9e7da", amber:  "#6a9690", amberLo:  "#2a4a48",
            violetHi:   "#87b8d4", violet: "#3a6a8a", violetLo: "#0e2638",
            leaf:       "#2a4a4a",
            leadBright: "#d8d4b8", lead:   "#8a8a6a", leadDeep: "#3a3a28",
            glowHi:     "#a7e7da", glowMid:"#2c8a7a",
            text:       "#e7e0c0", textDim:"#9cbfb8"
        },
        autumn: {
            jewelHi:    "#e87a2c", jewel:  "#a04010", jewelLo:  "#2a0a04",
            amberHi:    "#f4cc5a", amber:  "#b87a18", amberLo:  "#4a2a02",
            violetHi:   "#d44a2c", violet: "#8a2a10", violetLo: "#2a0805",
            leaf:       "#3a2a08",
            leadBright: "#f0c060", lead:   "#b07418", leadDeep: "#3a1f02",
            glowHi:     ncde.amber, glowMid:"#a04010",
            text:       "#f0e0bf", textDim:"#d4a888"
        }
    })
    readonly property var sn: palettes[paletteName]

    // ─── Position interpolation ────────────────────────────────────────────────
    // widget_data polls playerctl every 2s; this timer fills the gaps smoothly.
    property real interpolatedPosition: 0

    Timer {
        interval: 100
        repeat:   true
        running:  widget_data.mediaPlaying
        onTriggered: {
            interpolatedPosition = Math.min(
                interpolatedPosition + 100, widget_data.mediaDuration)
        }
    }

    Connections {
        target: widget_data
        function onMediaChanged() {
            salonRoot.interpolatedPosition = widget_data.mediaPosition
        }
        function onMediaPositionChanged() {
            salonRoot.interpolatedPosition = widget_data.mediaPosition
        }
    }

    function formatTime(seconds) {
        if (!isFinite(seconds) || seconds < 0) seconds = 0
        var m = Math.floor(seconds / 60)
        var s = Math.floor(seconds % 60)
        return m + ":" + (s < 10 ? "0" + s : s)
    }

    // ─── Window drag state ─────────────────────────────────────────────────────
    property real _dwx: 0; property real _dwy: 0
    property real _dgx: 0; property real _dgy: 0

    // ─── Background ────────────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        color: "#07040e"
        opacity: 0.94
        radius: 6
    }

    // ─── Triptych ──────────────────────────────────────────────────────────────
    Row {
        id: triptych
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 20
        spacing: 0

        // ── Left: transport + volume + time ────────────────────────────────────
        SNArchPanel {
            width: 320; height: 660
            archRise: 0.30; accent: "violet"; theme: salonRoot.sn

            Column {
                anchors.top: parent.top
                anchors.topMargin: 90
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 22
                width: parent.width - 60

                Text {
                    text: "TRANSPORT"
                    color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                    font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 4; opacity: 0.75
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Row {
                    spacing: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                    SNTransportButton {
                        glyph: "prev"; size: 52; theme: salonRoot.sn
                        onClicked: widget_data.mediaPrev()
                    }
                    SNTransportButton {
                        glyph: widget_data.mediaPlaying ? "pause" : "play"
                        size: 72; theme: salonRoot.sn
                        onClicked: {
                            if (widget_data.mediaActive)
                                widget_data.mediaTogglePlay()
                            else
                                launcher.launchExec("spotify")
                        }
                    }
                    SNTransportButton {
                        glyph: "next"; size: 52; theme: salonRoot.sn
                        onClicked: widget_data.mediaNext()
                    }
                }

                SNFiligreeDivider {
                    width: 220; theme: salonRoot.sn
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                SNVolumeKnob {
                    width: 96; height: 96
                    theme: salonRoot.sn
                    value: widget_data.volume / 100.0
                    onValueChanged: widget_data.setVolume(Math.round(value * 100))
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                SNFiligreeDivider {
                    width: 220; theme: salonRoot.sn
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Row {
                    spacing: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: salonRoot.formatTime(salonRoot.interpolatedPosition / 1000)
                        color: ncde.gilt4; font.family: theme ? theme.bodyFont : "Cormorant Garamond"
                        font.italic: true; font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg)
                    }
                    Text {
                        text: "/"
                        color: ncde.gilt4; opacity: 0.6
                        font.family: theme ? theme.bodyFont : "Cormorant Garamond"; font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg)
                    }
                    Text {
                        text: salonRoot.formatTime(widget_data.mediaDuration / 1000)
                        color: ncde.gilt4; font.family: theme ? theme.bodyFont : "Cormorant Garamond"
                        font.italic: true; font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg)
                    }
                }
            }

            Text {
                anchors.bottom: parent.bottom; anchors.bottomMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                text: "✦  salon nocturne  ✦"
                color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 3; opacity: 0.55
            }
        }

        // ── Centre: gramophone + petal visualizer + scrubber ───────────────────
        SNArchPanel {
            id: centrePanel
            width: 540; height: 660
            archRise: 0.34; accent: "jewel"; theme: salonRoot.sn

            Text {
                anchors.top: parent.top; anchors.topMargin: 64
                anchors.horizontalCenter: parent.horizontalCenter
                text: "NOW   PLAYING"
                color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 6; opacity: 0.8
            }

            Item {
                id: stage
                anchors.top: parent.top; anchors.topMargin: 90
                anchors.horizontalCenter: parent.horizontalCenter
                width: 420; height: 420

                SNRoseHalo       { anchors.fill: parent; theme: salonRoot.sn }
                SNPetalVisualizer {
                    anchors.fill: parent
                    theme: salonRoot.sn
                    playing: widget_data.mediaPlaying
                }
                SNGramophone {
                    anchors.fill: parent
                    theme: salonRoot.sn
                    spinning:   widget_data.mediaPlaying
                    albumLabel: widget_data.mediaAlbum
                }
            }

            Column {
                anchors.top: stage.bottom; anchors.topMargin: 4
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 4
                width: parent.width - 80

                Text {
                    text: widget_data.mediaActive ? widget_data.mediaTitle : "—"
                    color: ncde.gilt4; font.family: theme ? theme.bodyFont : "Cormorant Garamond"
                    font.italic: true; font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.weight: Font.Medium
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width; elide: Text.ElideRight
                }
                Text {
                    text: widget_data.mediaActive ? widget_data.mediaArtist.toUpperCase() : ""
                    color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                    font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 5; opacity: 0.85
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width; elide: Text.ElideRight
                }
                Text {
                    text: (widget_data.mediaActive && widget_data.mediaAlbum.length > 0)
                          ? "— " + widget_data.mediaAlbum + " —" : ""
                    color: ncde.gilt4; font.family: theme ? theme.bodyFont : "Cormorant Garamond"
                    font.italic: true; font.pixelSize: (theme ? theme.fontMedium : ncde.fontSize_md); opacity: 0.7
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width; elide: Text.ElideRight
                }
                Item { width: 1; height: 14 }
                SNScrubber {
                    width: parent.width; height: 22
                    theme: salonRoot.sn
                    position: salonRoot.interpolatedPosition
                    duration: widget_data.mediaDuration > 0 ? widget_data.mediaDuration : 1
                    onSeek: (ms) => widget_data.mediaSeek(ms)
                }
            }
        }

        // ── Right: queue (current track via MPRIS) ─────────────────────────────
        SNArchPanel {
            width: 360; height: 660
            archRise: 0.30; accent: "amber"; theme: salonRoot.sn

            Text {
                anchors.top: parent.top; anchors.topMargin: 90
                anchors.horizontalCenter: parent.horizontalCenter
                text: "⚜  QUEUE  ⚜"
                color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 5; opacity: 0.85
            }

            SNPlaylist {
                anchors.top: parent.top; anchors.topMargin: 124
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 50
                height: parent.height - 200
                theme: salonRoot.sn
                tracks: widget_data.mediaActive ? [{
                    title:    widget_data.mediaTitle,
                    artist:   widget_data.mediaArtist,
                    album:    widget_data.mediaAlbum,
                    duration: widget_data.mediaDuration / 1000
                }] : []
                currentTrack: 0
                playing: widget_data.mediaPlaying
            }

            Text {
                anchors.bottom: parent.bottom; anchors.bottomMargin: 24
                anchors.horizontalCenter: parent.horizontalCenter
                text: widget_data.mediaActive ? "SPOTIFY · playerctl" : "NO PLAYER ACTIVE"
                color: ncde.gilt4; font.family: theme ? theme.titleFont : "Cinzel"
                font.pixelSize: (theme ? theme.fontSmall : ncde.fontSize_sm); font.letterSpacing: 3; opacity: 0.55
            }
        }
    }

    // ─── Title strip ───────────────────────────────────────────────────────────
    Row {
        anchors.bottom: triptych.top; anchors.bottomMargin: 10
        anchors.horizontalCenter: triptych.horizontalCenter
        spacing: 14
        Rectangle { width:6;height:6;radius:3;color:salonRoot.sn.amberHi; anchors.verticalCenter:parent.verticalCenter }
        Text { text:"SALON   NOCTURNE"; color:ncde.gilt4
               font.family: theme ? theme.titleFont : "Cinzel"; font.pixelSize: Math.round(13 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); font.letterSpacing:8; opacity:0.85
               anchors.verticalCenter:parent.verticalCenter }
        Rectangle { width:6;height:6;radius:3;color:salonRoot.sn.amberHi; anchors.verticalCenter:parent.verticalCenter }
    }

    // ─── Drag zone (transparent strip above triptych, below arch crests) ───────
    Item {
        id: dragZone
        anchors.left:  triptych.left
        anchors.right: triptych.right
        anchors.bottom: triptych.top
        height: 50

        DragHandler {
            target: null
            onActiveChanged: {
                if (active && salonRoot.parentWindow) {
                    var g = dragZone.mapToGlobal(centroid.position.x, centroid.position.y)
                    salonRoot._dwx = salonRoot.parentWindow.x
                    salonRoot._dwy = salonRoot.parentWindow.y
                    salonRoot._dgx = g.x
                    salonRoot._dgy = g.y
                }
            }
            onCentroidChanged: {
                if (active && salonRoot.parentWindow) {
                    var g = dragZone.mapToGlobal(centroid.position.x, centroid.position.y)
                    salonRoot.parentWindow.x = salonRoot._dwx + g.x - salonRoot._dgx
                    salonRoot.parentWindow.y = salonRoot._dwy + g.y - salonRoot._dgy
                }
            }
        }
    }

    // ─── Palette dots + close (top-right corner) ───────────────────────────────
    Row {
        anchors.top:   parent.top; anchors.topMargin:   10
        anchors.right: parent.right; anchors.rightMargin: 14
        spacing: 7

        Repeater {
            model: ["twilight", "cathedral", "seaglass", "autumn"]
            Rectangle {
                width: 10; height: 10; radius: 5
                color: salonRoot.paletteName === modelData
                       ? salonRoot.sn.amberHi : salonRoot.sn.leadDeep
                border.color: salonRoot.sn.lead; border.width: 1
                opacity: salonRoot.paletteName === modelData ? 1.0 : 0.45
                Behavior on opacity { NumberAnimation { duration: 120 } }
                TapHandler  { onTapped: salonRoot.paletteName = modelData }
                HoverHandler{ cursorShape: Qt.PointingHandCursor }
            }
        }

        Rectangle {
            width: 16; height: 16; radius: 8
            anchors.verticalCenter: parent.verticalCenter
            color: xHov.hovered ? "#cc3333" : "#5a1414"
            Behavior on color { ColorAnimation { duration: 100 } }
            Text { anchors.centerIn:parent; text:"✕"; color:"white"; font.pixelSize: Math.round(9 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)) }
            HoverHandler { id: xHov; cursorShape: Qt.PointingHandCursor }
            TapHandler   { onTapped: { if (salonRoot.parentWindow) salonRoot.parentWindow.visible = false } }
        }
    }
}
