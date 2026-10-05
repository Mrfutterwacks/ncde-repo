// DateTimeTab.qml — geo auto-timezone (the user never hand-sets the zone).
// Backend — all real as of 2026-07-01:
//   ncde.detectedZone, detectedRegion, detectedOffset, detectedTzName, localTime : string
//   ncde.locating : bool (now real, delegates to Lelan; the visible "Charting…" indicator actually
//     shown in this tab is geo.locating, in NCDEGeoChart.qml — was already correctly wired, separate
//     object, not a stub — see NCDEGeo.h)
//   ncde.refreshLocation(), ncde.setTimezone(zone), ncde.setNtp(bool)
//   settings.timezoneManual, ntpEnabled, hourFormat ("auto"|"12"|"24"), showSeconds, saveDateTime()
//   settings.systemLanguage (read-only display here; change it from the Language tab)
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1 as Platform

Item {
    id: dt; clip: true
    property var k: SetTheme
    function gv(obj, name, dflt) { return (obj && obj[name] !== undefined && obj[name] !== null) ? obj[name] : dflt }
    function saveDT() { if (typeof settings.saveDateTime === "function") settings.saveDateTime() }

    // ── WEATHER LOCATION PIN (2026-07-21) ────────────────────────────────
    // Writes the reserved "_pinned" entry WeatherLive.qml resolves FIRST —
    // the cure for GeoIP wrong-city (a small town's IP often "locates" to
    // the ISP's hub city). User-level file, instant apply, no root; widgets
    // pick it up on their next resolve cycle (≤60 s). Empty = automatic.
    property string pinnedPlace: ""
    property string pinStatus: ""
    function _memPath() {
        var base = Platform.StandardPaths.writableLocation(Platform.StandardPaths.ConfigLocation)
        base = ("" + base).replace(/^file:\/\//, "")
        if (base.length && base[base.length - 1] === "/") base = base.slice(0, -1)
        return base + "/ncde/location-memory.json"
    }
    function _readMem(then) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var j = ({})
            try { var p = JSON.parse(xhr.responseText); if (p && typeof p === "object") j = p } catch (e) { }
            then(j)
        }
        try { xhr.open("GET", "file://" + _memPath()); xhr.send() } catch (e) { then({}) }
    }
    function _writeMem(j) {
        var xhr = new XMLHttpRequest()
        try { xhr.open("PUT", "file://" + _memPath()); xhr.send(JSON.stringify(j, null, 2)) } catch (e) { }
    }
    function clearPin() {
        _readMem(function(j) {
            delete j["_pinned"]; dt._writeMem(j)
            dt.pinnedPlace = ""; dt.pinStatus = "Automatic — the weather finds you"; widget_data.refreshWeather()
        })
    }
    function setPin(query) {
        var q = ("" + query).trim()
        if (!q.length) { clearPin(); return }
        dt.pinStatus = "Looking up \u201C" + q + "\u201D…"
        var url = "https://nominatim.openstreetmap.org/search?format=json&limit=1&addressdetails=1&q=" + encodeURIComponent(q)
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState !== XMLHttpRequest.DONE) return
            var ok = false
            try {
                var r = JSON.parse(xhr.responseText)
                if (r && r.length) {
                    var la = parseFloat(r[0].lat), lo = parseFloat(r[0].lon)
                    var a = r[0].address || {}
                    var town = a.town || a.village || a.city || a.hamlet || a.suburb || a.municipality || ""
                    var zip  = a.postcode || ""
                    var sname = (town && zip) ? (town + " " + zip) : (town || zip || q)
                    if (!isNaN(la) && !isNaN(lo)) {
                        dt._readMem(function(j) {
                            j["_pinned"] = { place: sname, lat: la, lon: lo }
                            dt._writeMem(j)
                            dt.pinnedPlace = sname
                            dt.pinStatus = "Pinned — the weather shows " + sname; widget_data.refreshWeather()
                        })
                        ok = true
                    }
                }
            } catch (e) { }
            if (!ok) dt.pinStatus = "Couldn\u2019t find that — try \u201CTown, State\u201D or a ZIP"
        }
        xhr.open("GET", url)
        try { xhr.setRequestHeader("User-Agent", "NCDE-Weather/1.0 (settings)") } catch (e) { }
        xhr.send()
    }
    Component.onCompleted: _readMem(function(j) {
        var p = j["_pinned"]
        if (p && p.place) { dt.pinnedPlace = p.place; dt.pinStatus = "Pinned — the weather shows " + p.place }
        else dt.pinStatus = "Automatic — the weather finds you"
    })

    readonly property string zone:   gv(ncde, "detectedZone", "America/Chicago")
    readonly property string region: gv(ncde, "detectedRegion", "United States")
    readonly property string offset: gv(ncde, "detectedOffset", "UTC-5")
    readonly property string tzName: gv(ncde, "detectedTzName", "Central Daylight Time")
    readonly property bool   manual: gv(settings, "timezoneManual", "") !== ""

    Flickable {
        anchors.fill: parent; contentHeight: col.height; interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}
        Column {
            id: col; width: parent.width; spacing: 14

            Text { text: "Date & Time"; color: dt.k.wine2; font.family: dt.k.display; font.bold: true; font.pixelSize: k.lg }
            Text { text: "The clock keeps itself — location, zone, and the hour are found for you."
                   color: dt.k.inkSoft; font.family: dt.k.fell; font.italic: true; font.pixelSize: k.md }

            Text { text: "TIMEZONE — FOUND AUTOMATICALLY"; color: dt.k.gilt1
                   font.family: dt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2; topPadding: 4 }

            NCDEGeoChart {
                width: parent.width
                onManualRequested: {
                    if (dt.manual) {
                        settings.timezoneManual = ""
                        lelan.refreshLocation()
                        manualPanel.visible = false
                    } else {
                        manualPanel.visible = !manualPanel.visible
                    }
                    dt.saveDT()
                }
            }

            Rectangle {
                id: manualPanel; visible: false; width: parent.width; radius: 8
                color: Qt.rgba(dt.k.paper0.r, dt.k.paper0.g, dt.k.paper0.b, 0.04); border.color: dt.k.gilt1; border.width: 1
                height: manCol.height + 20
                Column {
                    id: manCol; anchors.left: parent.left; anchors.right: parent.right
                    anchors.top: parent.top; anchors.margins: 11; spacing: 8
                    Text { text: "Choose a zone by hand (turns off auto-locate)"; color: dt.k.wine2
                           font.family: dt.k.titles; font.pixelSize: k.sm }
                    Flow {
                        width: parent.width; spacing: 6
                        Repeater {
                            model: ["America/New_York","America/Chicago","America/Denver","America/Los_Angeles",
                                    "Europe/London","Europe/Paris","Asia/Tokyo","Australia/Sydney","UTC"]
                            Rectangle {
                                height: 26; radius: 13; width: zl.implicitWidth + 20
                                property bool on: dt.gv(settings,"timezoneManual","") === modelData
                                color: on ? dt.k.gilt4 : dt.k.paper0; border.color: on ? dt.k.gilt0 : dt.k.gilt1; border.width: 1
                                Text { id: zl; anchors.centerIn: parent; text: modelData; font.family: dt.k.gar; font.pixelSize: k.sm; color: dt.k.ink }
                                TapHandler { onTapped: { settings.timezoneManual = modelData
                                    lelan.setTimezone(modelData); dt.saveDT() } }
                            }
                        }
                    }
                }
            }

            Rectangle { width: parent.width; height: 1; color: dt.k.gilt1; opacity: 0.4 }
            Text { text: "CLOCK"; color: dt.k.gilt1; font.family: dt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

            Row { width: parent.width; spacing: 12
                Text { text: "Hour format"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                SetSegment { model: ["12-hour","Auto","24-hour"]
                    currentIndex: { var h = dt.gv(settings,"hourFormat","auto"); return h==="12"?0:h==="24"?2:1 }
                    onChose: function(i){ settings.hourFormat = (i===0?"12":i===2?"24":"auto"); dt.saveDT() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: "Auto follows the region found above"; anchors.verticalCenter: parent.verticalCenter
                       font.family: dt.k.fell; font.italic: true; font.pixelSize: k.sm; color: dt.k.inkSoft } }
            Row { width: parent.width; spacing: 12
                Text { text: "Network time (NTP)"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                NCDEToggle { checked: dt.gv(settings,"ntpEnabled",true)
                    onToggled: function(v){ settings.ntpEnabled = v; lelan.setNtp(v); dt.saveDT() }
                    anchors.verticalCenter: parent.verticalCenter }
                Text { text: "Syncs the hour to the second over the internet"; anchors.verticalCenter: parent.verticalCenter
                       font.family: dt.k.fell; font.italic: true; font.pixelSize: k.sm; color: dt.k.inkSoft } }
            Row { width: parent.width; spacing: 12
                Text { text: "Show seconds"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                NCDEToggle { checked: dt.gv(settings,"showSeconds",false)
                    onToggled: function(v){ settings.showSeconds = v; dt.saveDT() }
                    anchors.verticalCenter: parent.verticalCenter } }

            Rectangle { width: parent.width; height: 1; color: dt.k.gilt1; opacity: 0.4 }
            Text { text: "WEATHER"; color: dt.k.gilt1; font.family: dt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
            Row { width: parent.width; spacing: 12
                Text { text: "Location"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                NCDEField { id: pinField; width: 280; anchors.verticalCenter: parent.verticalCenter
                    placeholder: "Town, State — or ZIP"
                    text: dt.pinnedPlace
                    onAccepted: dt.setPin(text) }
                NCDEButton { text: "Set"; variant: "gilt"; anchors.verticalCenter: parent.verticalCenter
                    onClicked: dt.setPin(pinField.text) } }
            Text { text: dt.pinStatus; color: dt.k.inkSoft; font.family: dt.k.fell; font.italic: true; font.pixelSize: k.sm; topPadding: -6 }
            Text { text: "Leave empty for automatic. If the weather ever names the wrong town, type yours — it sticks until you clear it."
                   color: dt.k.inkSoft; font.family: dt.k.fell; font.italic: true; font.pixelSize: k.sm; topPadding: -6 }

            Rectangle { width: parent.width; height: 1; color: dt.k.gilt1; opacity: 0.4 }
            Text { text: "REGION & LANGUAGE"; color: dt.k.gilt1; font.family: dt.k.display; font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }
            Row { width: parent.width; spacing: 12
                Text { text: "Region"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                Rectangle { height: 30; width: 280; radius: 8; color: dt.k.paper0; border.color: dt.k.gilt1; border.width: 1.5; anchors.verticalCenter: parent.verticalCenter
                    Text { anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter
                           text: dt.region + " — found automatically"; font.family: dt.k.gar; font.pixelSize: k.md; color: dt.k.ink } } }
            Row { width: parent.width; spacing: 12
                Text { text: "Language"; width: 150; anchors.verticalCenter: parent.verticalCenter; font.family: dt.k.titles; font.pixelSize: k.md; color: dt.k.ink }
                Rectangle { height: 30; width: 200; radius: 8; color: dt.k.paper0; border.color: dt.k.gilt1; border.width: 1.5; anchors.verticalCenter: parent.verticalCenter
                    Text { anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter
                           text: dt.gv(settings,"systemLanguage","en_US.UTF-8"); font.family: dt.k.gar; font.pixelSize: k.md; color: dt.k.ink } } }
            Text { text: "Change language in the Language tab."; color: dt.k.inkSoft; font.family: dt.k.fell; font.italic: true; font.pixelSize: k.sm; topPadding: -6 }
            Item { width: 1; height: 8 }
        }
    }
}
