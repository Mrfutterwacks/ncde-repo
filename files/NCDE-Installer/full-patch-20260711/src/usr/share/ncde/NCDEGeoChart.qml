// ╔══════════════════════════════════════════════════════════════════════╗
// ║  NCDEGeoChart.qml — reusable "medieval cartographer's chart" surface.   ║
// ║                                                                        ║
// ║  A system-wide skin for ANY place NCDE shows a live geographic         ║
// ║  location: the Date & Time settings tab, the clock/calendar popup,     ║
// ║  the weather widget's locale, the lock screen, the "where am I"        ║
// ║  glance. One component, one look.                                      ║
// ║                                                                        ║
// ║  Everything is drawn with Canvas (aged vellum, ink coastlines,         ║
// ║  graticule, rhumb lines, compass rose, sea-monster + galleon           ║
// ║  flourishes, scorched vignette) — no image assets.                     ║
// ║                                                                        ║
// ║  The location marker is a slowly-turning COMPASS ROSE with an          ║
// ║  expanding ring, placed by normalised x/y (0..1) over the chart.       ║
// ║                                                                        ║
// ║  ── DATA ───────────────────────────────────────────────────────────  ║
// ║  Bind to a single `geo` context property so every instance shows the   ║
// ║  same live fix (see NCDEGeo backend in the README). Falls back to      ║
// ║  demo data when `geo` is absent, so it renders in isolation.           ║
// ║     geo.latitude   : real   (−90..90)                                  ║
// ║     geo.longitude  : real   (−180..180)                                ║
// ║     geo.zone       : string "America/Chicago"                          ║
// ║     geo.tzName     : string "Central Daylight Time"                    ║
// ║     geo.offset     : string "UTC−5"                                    ║
// ║     geo.localTime  : string "2:14 PM"  (engine ticks — no QML Timer)   ║
// ║     geo.locating   : bool                                              ║
// ║     geo.place      : string "America / Chicago" (display)             ║
// ║                                                                        ║
// ║  Lélan: TapHandler only; the only animations are the marker's own      ║
// ║  rose-spin + ring-pulse (decorative, gated on `animate`).              ║
// ╚══════════════════════════════════════════════════════════════════════╝
import QtQuick 2.15
import "chart-art.js" as Art

Item {
    id: chart
    implicitWidth: 560
    implicitHeight: 300

    // ── inputs (override directly, or leave to read `geo`) ───────────────
    property real latitude:  _gv("latitude",  41.88)
    property real longitude: _gv("longitude", -87.63)
    property string place:   _gv("place",   "America / Chicago")
    property string tzName:  _gv("tzName",  "Central Daylight Time")
    property string offset:  _gv("offset",  "UTC−5")
    property string localTime: _gv("localTime", "")
    property bool   locating:  _gv("locating", false)

    // chrome options so the same chart fits a big settings panel OR a small popup
    property bool   showPlate:   true      // the zone/time strip beneath the map
    property bool   showFoot:    true      // the "set manually" foot
    property bool   showBadge:   true      // the "Charted automatically" ribbon
    property bool   showBanner:  true      // "Vous êtes ici" over the marker
    property bool   showSelf:    true      // the "you are here" compass marker
    property bool   animate:     true
    readonly property bool motionAllowed: chart.visible && chart.animate
        && (typeof animPolicy === "undefined" || animPolicy === null
            || (animPolicy.decorative && animPolicy.idleLoops && !animPolicy.screenIdle))
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 1.5 : 1.0
    property real   markerScale: 1.0
    signal manualRequested()

    // ── multi-peer plotting ──────────────────────────────────────────────
    // A list of OTHER stations to plot alongside (or instead of) the self
    // marker. Each entry is a plain object carrying the coarse lat/lon that
    // Magpie's geo band now hands through per peer (fix G6):
    //     { lat: real, lon: real, callsign: string, presence: string }
    // Entries without usable coordinates are skipped by peerMarkers.
    property var peers: []
    // peer marker tapped (callsign passed through) — lets a host panel wire "Add".
    signal peerActivated(string callsign)

    // Filter to only peers that actually carry coordinates, so the Repeater
    // never tries to place a marker for a coordinate-less record.
    readonly property var peerMarkers: {
        var out = [];
        var src = chart.peers;
        if (src === undefined || src === null) return out;
        for (var i = 0; i < src.length; ++i) {
            var p = src[i];
            if (p === undefined || p === null) continue;
            if (p.lat === undefined || p.lon === undefined || p.lat === null || p.lon === null) continue;
            out.push(p);
        }
        return out;
    }

    function _gv(name, dflt) {
        return (typeof geo !== "undefined" && geo && geo[name] !== undefined && geo[name] !== null)
               ? geo[name] : dflt
    }
    // normalised marker position from lat/long (equirectangular over the map band)
    readonly property real markX: (longitude + 180) / 360
    readonly property real markY: (90 - latitude) / 180
    // same projection for an arbitrary lat/lon (used for peer markers)
    function projX(lon) { return (lon + 180) / 360 }
    function projY(lat) { return (90 - lat) / 180 }

    // ── simplified real-world coastlines, [lon,lat] in equirectangular ───
    // Recognisable, not survey-grade — drawn in the inked-parchment style.
    readonly property var continents: [[[-157,71],[-156,71],[-141,70],[-128,70],[-115,68],[-105,69],[-95,70],[-82,73],[-78,68],[-85,66],[-87,63],[-94,59],[-95,52],[-92,57],[-87,55],[-82,55],[-79,51],[-83,46],[-79,43],[-76,44],[-70,47],[-66,49],[-60,47],[-64,45],[-70,42],[-74,40],[-75,37],[-76,34],[-81,31],[-81,25],[-80,27],[-83,29],[-85,30],[-90,29],[-94,29],[-97,28],[-97,23],[-105,22],[-106,24],[-110,24],[-112,30],[-114,31],[-117,33],[-121,35],[-124,40],[-124,46],[-124,48],[-130,54],[-135,58],[-141,60],[-150,59],[-153,57],[-158,56],[-162,55],[-165,60],[-164,66],[-161,64],[-156,71]],[[-46,60],[-43,60],[-40,64],[-37,66],[-32,68],[-25,70],[-22,72],[-31,76],[-40,78],[-50,77],[-58,76],[-62,73],[-55,69],[-53,66],[-50,63],[-46,60]],[[-81,6],[-77,8],[-76,11],[-72,12],[-66,11],[-62,10],[-60,5],[-51,4],[-50,0],[-44,-3],[-39,-3],[-35,-5],[-35,-8],[-39,-13],[-39,-18],[-41,-22],[-48,-25],[-48,-28],[-54,-34],[-58,-39],[-62,-39],[-63,-42],[-65,-45],[-68,-50],[-70,-53],[-74,-52],[-72,-47],[-74,-44],[-73,-40],[-73,-37],[-72,-30],[-71,-24],[-70,-18],[-76,-15],[-78,-8],[-81,-6],[-81,1],[-81,6]],[[-16,15],[-17,21],[-13,28],[-9,30],[-1,36],[10,37],[11,34],[15,32],[20,31],[25,32],[30,31],[32,31],[34,28],[35,24],[37,22],[39,18],[41,15],[43,12],[44,10],[48,8],[51,12],[51,8],[48,5],[44,2],[42,-2],[40,-8],[39,-13],[35,-18],[33,-26],[28,-32],[25,-34],[20,-35],[18,-33],[16,-29],[13,-23],[12,-17],[9,-5],[8,2],[3,6],[-4,5],[-8,4],[-12,8],[-16,12],[-16,15]],[[-10,37],[-9,39],[-9,43],[-2,44],[-2,48],[2,48],[0,50],[-5,49],[-4,53],[2,51],[8,54],[6,58],[11,59],[10,64],[15,68],[22,70],[28,71],[31,70],[33,69],[40,67],[42,66],[48,68],[55,68],[60,70],[69,73],[76,73],[90,75],[100,77],[105,78],[113,74],[125,73],[130,71],[140,73],[148,70],[160,70],[170,69],[172,66],[163,62],[160,59],[163,56],[156,51],[156,46],[150,46],[143,46],[142,54],[138,54],[135,48],[131,43],[130,39],[125,39],[122,40],[121,37],[119,35],[121,31],[122,28],[118,24],[115,22],[110,21],[108,16],[106,10],[104,8],[100,8],[100,13],[98,16],[94,16],[91,22],[87,21],[84,19],[80,15],[77,8],[76,12],[73,16],[70,21],[67,24],[64,25],[61,25],[57,25],[56,27],[52,30],[48,30],[48,25],[43,13],[40,15],[36,28],[35,32],[33,36],[28,41],[27,37],[23,40],[19,40],[17,41],[20,43],[13,46],[13,41],[16,38],[12,38],[10,44],[4,43],[3,42],[-2,37],[-6,36],[-10,37]],[[-5,50],[-1,51],[1,52],[-1,54],[-3,55],[-2,57],[-5,58],[-7,57],[-6,55],[-8,54],[-10,53],[-9,51],[-6,51],[-5,50]],[[-10,52],[-6,52],[-6,55],[-10,55],[-10,52]],[[130,31],[132,34],[135,34],[137,37],[140,38],[142,40],[141,42],[143,44],[140,42],[138,37],[136,35],[133,35],[131,33],[130,31]],[[114,-22],[114,-26],[115,-34],[118,-35],[123,-34],[129,-32],[131,-31],[135,-35],[138,-35],[140,-38],[143,-39],[147,-38],[150,-37],[153,-31],[153,-25],[149,-21],[146,-19],[143,-12],[136,-12],[132,-11],[130,-13],[127,-14],[122,-18],[114,-22]],[[44,-16],[47,-16],[50,-19],[48,-23],[45,-25],[44,-21],[43,-18],[44,-16]],[[173,-35],[175,-37],[178,-38],[177,-40],[174,-41],[171,-44],[167,-46],[170,-44],[173,-40],[173,-35]],[[-24,65],[-19,66],[-14,65],[-18,64],[-22,64],[-24,65]]]
    readonly property var mapLabels: [{"text":"AMERICA SEPTENTRIONALIS","lon":-100,"lat":48,"size":11,"track":1,"font":"Cinzel"},{"text":"AMERICA MERIDIONALIS","lon":-62,"lat":-15,"size":10,"track":1,"font":"Cinzel"},{"text":"AFRICA","lon":21,"lat":8,"size":14,"track":4,"font":"Cinzel"},{"text":"EUROPA","lon":18,"lat":52,"size":11,"track":3,"font":"Cinzel"},{"text":"ASIA","lon":95,"lat":50,"size":16,"track":5,"font":"Cinzel"},{"text":"NOVA HOLLANDIA","lon":134,"lat":-25,"size":10,"track":1,"font":"Cinzel"},{"text":"MARE PACIFICUM","lon":-150,"lat":5,"size":12,"italic":true,"sea":true,"track":3,"font":"Cormorant Garamond"},{"text":"OCEANVS ATLANTICVS","lon":-30,"lat":25,"size":11,"italic":true,"sea":true,"track":2,"font":"Cormorant Garamond"},{"text":"MARE INDICUM","lon":75,"lat":-25,"size":11,"italic":true,"sea":true,"track":2,"font":"Cormorant Garamond"},{"text":"Hic sunt dracones","lon":-12,"lat":-38,"size":10,"italic":true,"track":1,"font":"Cormorant Garamond"}]
    property string mapTitle: "MAPPA MUNDI"
    property string mapSubtitle: "the kingdoms of the world, as charted by NCDE"

    // ── palette ──────────────────────────────────────────────────────────
    readonly property color vellum1: "#e7d6ac"
    readonly property color vellum2: "#d8c089"
    readonly property color vellum3: "#c9a96a"
    readonly property color sepia:   "#6b4a26"
    readonly property color sepiaDeep:"#3e2a13"
    readonly property color gilt3:   ncde.gilt3
    readonly property color gilt4:   ncde.gilt4
    readonly property color gilt5:   ncde.gilt5
    readonly property color wine1:   ncde.wine1
    readonly property color wine2:   ncde.wine2
    readonly property color wine3:   ncde.wine3
    readonly property color wine4:   ncde.wine4
    readonly property color verd:    ncde.verd
    readonly property color cer:     ncde.cer
    readonly property color ink:     ncde.panelText
    readonly property color inkSoft: Qt.rgba(ncde.panelText.r, ncde.panelText.g, ncde.panelText.b, 0.65)
    readonly property color paper0:  ncde.surface
    readonly property color paper2:  ncde.surfaceAlt
    readonly property string display:(typeof ncde !== "undefined" && ncde.displayFont) ? ncde.displayFont : "Cinzel Decorative"
    readonly property string titles: (typeof ncde !== "undefined" && ncde.titleFont)   ? ncde.titleFont   : "Cinzel"
    readonly property string fell:   "IM Fell English"
    readonly property string gar:    "EB Garamond"
    readonly property string black:  "UnifrakturCook"

    // palette object handed to the painting library (hex strings)
    readonly property var palette: ({
        vellum0: ncde.panelBg, vellum1: "#e7d6ac", vellum2: "#d8c089", vellum3: "#c9a96a",
        land0: "#cfa569", land1: "#b98c4e", sepia: "#6b4a26", sepiaDeep: "#3e2a13",
        gilt1: ncde.gilt1, gilt2: ncde.gilt2, gilt3: ncde.gilt3, gilt4: ncde.gilt4, gilt5: ncde.gilt5,
        wine1: ncde.wine1, wine3: ncde.wine3, wine4: ncde.wine4
    })

    Rectangle {
        anchors.fill: parent; radius: 8; clip: true
        color: "transparent"
        border.color: chart.sepiaDeep; border.width: 2

        Column {
            anchors.fill: parent; spacing: 0

            // ── the chart band ───────────────────────────────────────────
            Item {
                id: band
                width: parent.width
                height: parent.height - (chart.showPlate ? plate.height : 0) - (chart.showFoot ? foot.height : 0)

                // aged vellum + ink cartography, all on one Canvas
                Canvas {
                    id: vellum
                    anchors.fill: parent
                    renderStrategy: Canvas.Cooperative
                    antialiasing: true
                    onWidthChanged: requestPaint()
                    onHeightChanged: requestPaint()
                    Component.onCompleted: requestPaint()
                    onPaint: {
                        var ctx = getContext("2d");
                        Art.paint(ctx, width, height, { continents: chart.continents, palette: chart.palette, labels: chart.mapLabels, title: chart.mapTitle, subtitle: chart.mapSubtitle });
                    }
                }

                // ── auto badge ribbon ────────────────────────────────────
                Rectangle {
                    visible: chart.showBadge
                    anchors.top: parent.top; anchors.left: parent.left; anchors.margins: 11
                    width: badgeRow.implicitWidth + 22; height: 26; radius: 4
                    gradient: Gradient { GradientStop { position: 0; color: chart.wine3 } GradientStop { position: 1; color: chart.wine1 } }
                    border.color: chart.gilt3; border.width: 1
                    Row {
                        id: badgeRow; anchors.centerIn: parent; spacing: 7
                        Rectangle { width: 8; height: 8; radius: 4; anchors.verticalCenter: parent.verticalCenter
                            color: chart.locating ? chart.gilt4 : chart.verd }
                        Text { text: chart.locating ? "Charting…" : "Charted automatically"
                               color: chart.gilt5; font.family: chart.fell; font.italic: true; font.pixelSize: theme.fontSmall
                               anchors.verticalCenter: parent.verticalCenter }
                    }
                }

                // ── plotted peers (fix G6: coarse per-peer lat/lon) ──────
                Repeater {
                    id: peerRep
                    model: chart.peerMarkers
                    delegate: Item {
                        id: peerMk
                        readonly property real pmX: chart.projX(modelData.lon)
                        readonly property real pmY: chart.projY(modelData.lat)
                        readonly property string pmCall: modelData.callsign !== undefined ? modelData.callsign : ""
                        readonly property string pmPres: modelData.presence !== undefined ? modelData.presence : "offline"
                        width: 14 * chart.markerScale; height: 14 * chart.markerScale
                        x: Math.max(6, Math.min(band.width  - width  - 6, band.width  * pmX - width/2))
                        y: Math.max(18, Math.min(band.height - height - 6, band.height * pmY - height/2))
                        Behavior on x { NumberAnimation { duration: 900; easing.type: Easing.InOutCubic } }
                        Behavior on y { NumberAnimation { duration: 900; easing.type: Easing.InOutCubic } }
                        // callsign label above the pin
                        Text {
                            visible: peerMk.pmCall.length > 0
                            anchors.bottom: parent.top; anchors.bottomMargin: 1
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: peerMk.pmCall; font.family: chart.titles; font.pixelSize: theme.fontSmall
                            color: chart.sepiaDeep; style: Text.Raised; styleColor: Qt.rgba(1,0.97,0.87,0.55)
                        }
                        // the peer pin — a wine dot ringed in gilt, presence-tinted core
                        Rectangle {
                            anchors.centerIn: parent
                            width: 11 * chart.markerScale; height: 11 * chart.markerScale; radius: width/2
                            border.color: chart.gilt3; border.width: 1
                            color: peerMk.pmPres === "online" ? chart.verd
                                 : peerMk.pmPres === "away"   ? chart.gilt4
                                 : chart.wine2
                        }
                        TapHandler { onTapped: chart.peerActivated(peerMk.pmCall) }
                    }
                }

                // ── the glowing location dot ─────────────────────────────
                Item {
                    id: marker
                    visible: chart.showSelf
                    width: 18 * chart.markerScale; height: 18 * chart.markerScale
                    x: Math.max(6, Math.min(band.width  - width  - 6, band.width  * chart.markX - width/2))
                    y: Math.max(18, Math.min(band.height - height - 6, band.height * chart.markY - height/2))
                    Behavior on x { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 1100 * chart.motionDurationScale; easing.type: Easing.InOutCubic } }
                    Behavior on y { NumberAnimation { duration: (typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.instant) ? 0 : 1100 * chart.motionDurationScale; easing.type: Easing.InOutCubic } }

                    // banner
                    Text {
                        visible: chart.showBanner
                        anchors.bottom: parent.top; anchors.bottomMargin: 2; anchors.horizontalCenter: parent.horizontalCenter
                        text: "Vous êtes ici"; font.family: chart.black; font.pixelSize: theme.fontMedium; color: chart.sepiaDeep
                        style: Text.Raised; styleColor: Qt.rgba(1,0.97,0.87,0.55)
                    }
                    // expanding ring
                    Rectangle {
                        id: markerRing
                        anchors.centerIn: parent; width: parent.width; height: parent.height; radius: width/2
                        opacity: 0.75
                        color: "transparent"; border.color: Qt.rgba(0.79,0.54,0.23,0.6); border.width: 2
                        SequentialAnimation on scale {
                            running: chart.motionAllowed; loops: Animation.Infinite
                            NumberAnimation { from: 0.7; to: 3.4; duration: 2800 * chart.motionDurationScale; easing.type: Easing.OutQuad }
                            PauseAnimation { duration: 80 }
                            onStopped: markerRing.scale = 1.0
                        }
                        SequentialAnimation on opacity {
                            running: chart.motionAllowed; loops: Animation.Infinite
                            NumberAnimation { from: 0.75; to: 0; duration: 2800 * chart.motionDurationScale }
                            PauseAnimation { duration: 80 }
                            onStopped: markerRing.opacity = 0.75
                        }
                    }
                    // soft breathing glow
                    Rectangle {
                        id: markerGlow
                        anchors.centerIn: parent; width: parent.width * 1.6; height: width; radius: width/2
                        opacity: 0.35
                        color: Qt.rgba(0.91,0.79,0.49,0.45)
                        SequentialAnimation on scale {
                            running: chart.motionAllowed; loops: Animation.Infinite
                            NumberAnimation { from: 0.7; to: 1.15; duration: 2400 * chart.motionDurationScale; easing.type: Easing.InOutSine }
                            NumberAnimation { from: 1.15; to: 0.7; duration: 2400 * chart.motionDurationScale; easing.type: Easing.InOutSine }
                            onStopped: markerGlow.scale = 1.0
                        }
                        SequentialAnimation on opacity {
                            running: chart.motionAllowed; loops: Animation.Infinite
                            NumberAnimation { from: 0.35; to: 0.8; duration: 2400 * chart.motionDurationScale; easing.type: Easing.InOutSine }
                            NumberAnimation { from: 0.8; to: 0.35; duration: 2400 * chart.motionDurationScale; easing.type: Easing.InOutSine }
                            onStopped: markerGlow.opacity = 0.35
                        }
                    }
                    // the gilt dot
                    Rectangle {
                        anchors.centerIn: parent; width: 12 * chart.markerScale; height: 12 * chart.markerScale; radius: width/2
                        border.color: chart.wine1; border.width: 1
                        gradient: Gradient {
                            GradientStop { position: 0; color: chart.gilt5 }
                            GradientStop { position: 0.55; color: chart.gilt3 }
                            GradientStop { position: 1; color: chart.wine4 }
                        }
                    }
                }
            }

            // ── plate: zone + clock ──────────────────────────────────────
            Rectangle {
                id: plate
                visible: chart.showPlate
                width: parent.width; height: 60
                gradient: Gradient { GradientStop { position: 0; color: chart.paper0 } GradientStop { position: 1; color: chart.paper2 } }
                Rectangle { anchors.top: parent.top; width: parent.width; height: 2; color: chart.sepiaDeep }
                Column {
                    anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - 150; spacing: 2
                    Text { text: chart.place; color: chart.wine2; font.family: chart.display; font.bold: true; font.pixelSize: theme.fontLarge; elide: Text.ElideRight; width: parent.width }
                    Text { text: chart.tzName + " · " + chart.offset + " · found by your network location"
                           color: chart.inkSoft; font.family: chart.fell; font.italic: true; font.pixelSize: theme.fontSmall; elide: Text.ElideRight; width: parent.width }
                }
                Text {
                    anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter
                    text: chart.localTime; color: chart.cer; font.family: chart.titles; font.pixelSize: theme.fontLarge
                }
            }

            // ── foot: manual escape hatch ────────────────────────────────
            Rectangle {
                id: foot
                visible: chart.showFoot
                width: parent.width; height: 40
                color: Qt.rgba(0,0,0,0.03)
                Rectangle { anchors.top: parent.top; width: parent.width; height: 1; color: chart.gilt3; opacity: 0.6 }
                Text {
                    anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter
                    text: "The chart redraws itself when you travel — you never set this by hand."
                    color: chart.inkSoft; font.family: chart.gar; font.pixelSize: theme.fontSmall
                }
                Rectangle {
                    anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter
                    width: manT.implicitWidth + 22; height: 26; radius: 6
                    color: chart.paper0; border.color: chart.gilt3; border.width: 1
                    Text { id: manT; anchors.centerIn: parent; text: "Set manually instead ▾"
                           font.family: chart.titles; font.pixelSize: theme.fontSmall; color: chart.wine3 }
                    TapHandler { onTapped: chart.manualRequested() }
                }
            }
        }
    }
}
