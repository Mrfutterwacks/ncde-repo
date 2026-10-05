// ScreensaverTab.qml — Les Saisons Nocturnes is ONE living scene that follows the
// season and the time of day. There is nothing to pick — so this tab is just
// start/stop, when to start, and a live test.
//
// Backend: settings.screensaverTimeout (0 = off), screensaverClockVisible, screensaverFps,
//          loadScreensaver(), saveScreensaver() — all real as of 2026-07-01. previewScreensaver()
//          is real too (fixed 2026-07-01) — usr/share/ncde/screensaver/ is empty, but the actual
//          scene lives in ncde-portal itself (qrc:/qml/Screensaver.qml, the seasons/quotes engine
//          shared with the greeter/lock screen) — previewScreensaver() launches it via
//          `ncde-portal --screensaver --season <mode>`.
// System: writes ~/.config/ncde/screensaver.json. Season is always "auto". The idle trigger is
//         real (built 2026-07-05, session 70): the WM's pollUserIdle() watches the user-set
//         timeout (setScreensaverTimeoutMs) and its latched screensaverIdleReached signal is
//         connected in main.cpp to previewScreensaver("auto") — the same path as the Test button.
//         Timeout 0 (toggle off) genuinely disarms.
import QtQuick 2.15
import QtQuick.Controls 2.15
Item {
    id: root; clip: true
    property var k: SetTheme
    function gv(o,n,d){ return (o&&o[n]!==undefined&&o[n]!==null)?o[n]:d }

    property bool enabled:    gv(settings,"screensaverTimeout",5) > 0
    property int  timeoutVal: { var t = gv(settings,"screensaverTimeout",5); return t > 0 ? t : 5 }
    property bool clockOn:    gv(settings,"screensaverClockVisible",true)
    property int  fpsIdx:     gv(settings,"screensaverFps",30) === 60 ? 1 : 0

    // Persist. Debounced so dragging the slider doesn't spam settingsChanged (each save
    // re-applies the WM idle threshold via main.cpp's settingsChanged connection).
    Timer { id: applyDebounce; interval: 500; repeat: false; onTriggered: root.save() }
    function scheduleSave() { applyDebounce.restart() }

    function save() {
        settings.screensaverSeason       = "auto"                    // one auto scene — never fixed
        settings.screensaverTimeout      = root.enabled ? root.timeoutVal : 0
        settings.screensaverClockVisible = root.clockOn
        settings.screensaverFps          = root.fpsIdx === 1 ? 60 : 30
        settings.saveScreensaver()
    }

    Component.onCompleted: {
        var t = gv(settings,"screensaverTimeout",5)
        enabled    = t > 0
        timeoutVal = t > 0 ? t : 5
        clockOn    = gv(settings,"screensaverClockVisible",true)
        fpsIdx     = gv(settings,"screensaverFps",30) === 60 ? 1 : 0
    }

    Flickable {
        anchors.fill: parent
        contentHeight: c.height
        interactive: contentHeight > height
        ScrollBar.vertical: NCDEScrollBar {}

        Column {
            id: c; width: parent.width; spacing: 16

            // ── Header ───────────────────────────────────────────────────────
            Text { text: "Screensaver"; color: root.k.wine2
                   font.family: root.k.display; font.bold: true; font.pixelSize: k.lg }
            Text {
                width: parent.width; wrapMode: Text.WordWrap
                text: "Les Saisons Nocturnes — one living scene that follows the season "
                    + "and the time of day. It changes itself; there is nothing to choose."
                color: root.k.inkSoft; font.family: root.k.fell; font.italic: true; font.pixelSize: k.md
            }

            // ── Start / stop ────────────────────────────────────────────────
            Row {
                width: parent.width; spacing: 12; height: 34
                Text { text: "Screensaver"; width: 158; color: root.k.ink
                       font.family: root.k.titles; font.pixelSize: k.md
                       anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    checked: root.enabled
                    anchors.verticalCenter: parent.verticalCenter
                    onToggled: function(v){ root.enabled = v; root.scheduleSave() }
                }
                Text {
                    text: root.enabled ? "On — starts when the screen is idle" : "Off"
                    color: root.k.inkSoft; font.family: root.k.fell; font.italic: true
                    font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter
                }
            }

            // ── When to start (only meaningful while on) ─────────────────────
            Row {
                width: parent.width; spacing: 12; height: 32
                opacity: root.enabled ? 1.0 : 0.4
                Text { text: "Start after"; width: 158; color: root.k.ink
                       font.family: root.k.titles; font.pixelSize: k.md
                       anchors.verticalCenter: parent.verticalCenter }
                NCDESlider {
                    minValue: 1; maxValue: 60; value: root.timeoutVal
                    anchors.verticalCenter: parent.verticalCenter
                    onMoved: function(v){ root.timeoutVal = Math.round(v); root.scheduleSave() }
                }
                Text {
                    text: root.timeoutVal + (root.timeoutVal === 1 ? " minute" : " minutes")
                    color: root.k.inkSoft; font.family: root.k.fell; font.italic: true
                    font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle { width: parent.width; height: 1; color: root.k.gilt1; opacity: 0.4 }
            Text { text: "OPTIONS"; color: root.k.gilt1; font.family: root.k.display
                   font.bold: true; font.pixelSize: k.sm; font.letterSpacing: 2 }

            // ── Clock ────────────────────────────────────────────────────────
            Row {
                width: parent.width; spacing: 12; height: 32
                Text { text: "Show clock"; width: 158; color: root.k.ink
                       font.family: root.k.titles; font.pixelSize: k.md
                       anchors.verticalCenter: parent.verticalCenter }
                NCDEToggle {
                    checked: root.clockOn
                    anchors.verticalCenter: parent.verticalCenter
                    onToggled: function(v){ root.clockOn = v; root.scheduleSave() }
                }
                Text { text: "Ornamental clock face with Marcellus numerals"
                       color: root.k.inkSoft; font.family: root.k.fell; font.italic: true
                       font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter }
            }

            // ── Frame rate ───────────────────────────────────────────────────
            Row {
                width: parent.width; spacing: 12; height: 32
                Text { text: "Frame rate"; width: 158; color: root.k.ink
                       font.family: root.k.titles; font.pixelSize: k.md
                       anchors.verticalCenter: parent.verticalCenter }
                SetSegment {
                    model: ["30 fps", "60 fps"]; currentIndex: root.fpsIdx
                    anchors.verticalCenter: parent.verticalCenter
                    onChose: function(i){ root.fpsIdx = i; root.scheduleSave() }
                }
                Text { text: "60 fps is smoother at night"
                       color: root.k.inkSoft; font.family: root.k.fell; font.italic: true
                       font.pixelSize: k.sm; anchors.verticalCenter: parent.verticalCenter }
            }

            Item { width: 1; height: 6 }

            // ── Test now (runs the auto scene in a window, no reboot) ────────
            Rectangle {
                width: 130; height: 32; radius: 7
                gradient: Gradient {
                    GradientStop { position: 0; color: root.k.wine3 }
                    GradientStop { position: 1; color: root.k.wine1 }
                }
                border.color: root.k.gilt2; border.width: 1.5
                Text { anchors.centerIn: parent; text: "Test now"
                       color: root.k.gilt4; font.family: root.k.titles
                       font.bold: true; font.pixelSize: k.md }
                HoverHandler { id: testHov }
                opacity: testHov.hovered ? 1.0 : 0.82
                // previewScreensaver() launches ncde-portal's real screensaver scene (fixed 2026-07-01).
                // typeof-guard kept as-is — harmless now that the Q_INVOKABLE is real.
                TapHandler { onTapped: if (typeof settings.previewScreensaver === "function") settings.previewScreensaver("auto") }
            }

            Item { width: 1; height: 14 }
        }
    }
}
