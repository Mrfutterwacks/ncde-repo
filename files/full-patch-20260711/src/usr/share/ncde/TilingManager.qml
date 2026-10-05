import QtQuick 2.15
import QtQuick as Q6   // FrameAnimation (Qt 6.4+) without unpinning the 2.15 import

Item {
    id: tilingRoot
    visible: false; width: 0; height: 0

    property int gap: 10
    property int topMargin: intellihide.topRevealed ? 40 : 10
    property int bottomMargin: intellihide.btmRevealed ? 50 : 10
    property int leftMargin: intellihide.dockRevealed ? 80 : 10
    property int rightMargin: 10

    onTopMarginChanged: tilingDebounce.restart()
    onBottomMarginChanged: tilingDebounce.restart()
    onLeftMarginChanged: tilingDebounce.restart()

    // User-arranged grid order (winIds). Windows keep the slot the user gave them;
    // newly-unmaxed windows append at the end. (Test-group item 2, operator 2026-07-06:
    // "One should be able to grab them and reposition them in the stack.")
    property var tileOrder: []
    // winId the user is currently drag-reordering — layout leaves it under the cursor.
    property int dragHoldWin: 0
    // Cell rects of the last layout (pre-inset, root coords) for drop-slot hit testing.
    property var lastCells: []

    // ── The deal (tarot stacking, 2026-09-26) ────────────────────────────────
    // Operator: "an animation for when they stack … like tarot cards, magical".
    // When the stack re-lays out, tiles no longer jump: each is DEALT to its new
    // cell — it takes its new size at once (resizing every frame would make apps
    // re-render each frame), then glides from where it was along a slight arc,
    // lifting off the table mid-flight and settling with a hair of overshoot. Cards
    // go down one after another in slot order, 45 ms apart. Driven by one 60 Hz
    // timer that moves the real windows (the frames follow the model). Reduce
    // Motion / idle / thermal (animPolicy.decorative false) = the old instant jump.
    property var _pos: ({})
    property var _glides: ({})
    readonly property int dealMs: 340
    readonly property int dealStagger: 45
    function _animate() {
        return typeof animPolicy !== "undefined" && animPolicy !== null && animPolicy.decorative === true
    }
    function deal(id, slot, x, y, w, h) {
        var g0 = _glides[id]
        // our own glide moves make the model change, which re-runs the layout: a card
        // already in flight to this same cell is left to finish its flight
        if (g0 && Math.abs(g0.x - x) < 2 && Math.abs(g0.y - y) < 2 && g0.w === w && g0.h === h) return
        var from = _pos[id]
        if (!_animate() || !from || (!g0 && Math.abs(from.x - x) < 2 && Math.abs(from.y - y) < 2)) {
            delete _glides[id]
            windowMgr.moveTiledWindow(id, x, y, w, h)
            return
        }
        var g = _glides[id]
        var sx = from.x, sy = from.y
        if (g) { var cur = _glidePoint(g, Date.now()); sx = cur.x; sy = cur.y }   // re-deal mid-flight: start where it is
        windowMgr.moveTiledWindow(id, Math.round(sx), Math.round(sy), w, h)       // new size at once, old place
        _glides[id] = { sx: sx, sy: sy, x: x, y: y, w: w, h: h, t0: Date.now() + slot * dealStagger,
                        arc: Math.min(14, Math.sqrt((x - sx) * (x - sx) + (y - sy) * (y - sy)) * 0.2) }
        dealTimer.start()
    }
    // easeOutBack with a gentle 1.2 overshoot; the arc lifts the card 14 px at mid-flight
    function _glidePoint(g, now) {
        var t = Math.max(0, Math.min(1, (now - g.t0) / dealMs))
        var c1 = 1.2, c3 = c1 + 1
        var e = 1 + c3 * Math.pow(t - 1, 3) + c1 * Math.pow(t - 1, 2)
        var lift = (g.arc === undefined ? 14 : g.arc) * Math.sin(Math.PI * Math.min(1, t * 1.1))
        return { x: g.sx + (g.x - g.sx) * e, y: g.sy + (g.y - g.sy) * e - lift, done: t >= 1 }
    }
    // the glide advances on the render loop's frames (anim-policy.md §1), not a 16 ms timer
    Q6.FrameAnimation {
        id: dealTimer
        onTriggered: {
            var now = Date.now(), live = 0
            for (var id in tilingRoot._glides) {
                var g = tilingRoot._glides[id]
                if (now < g.t0) { live++; continue }
                var q = tilingRoot._glidePoint(g, now)
                if (q.done) {
                    windowMgr.moveTiledWindow(Number(id), g.x, g.y, g.w, g.h)
                    delete tilingRoot._glides[id]
                    if (!tilingRoot.shuffling) tilingRoot.cardLanded(Number(id))
                } else {
                    windowMgr.moveTiledWindow(Number(id), Math.round(q.x), Math.round(q.y), g.w, g.h)
                    live++
                }
            }
            if (live === 0) stop()
        }
    }

    // ── Hover and breath (tarot, 2026-09-26) ──────────────────────────────────
    // Operator: "could sort of hover too … and breathe when stacked". The card
    // under the cursor LIFTS 6 px off the table (a small deal, no hop) and settles
    // back when the cursor leaves; its frame's halo brightens. The whole spread
    // breathes on ONE clock, each card offset by its slot, so the breath ripples
    // across the cards instead of eight glows pulsing at random. The windows
    // themselves stay still (moving eight apps continuously would cost battery).
    readonly property int hoverLift: 6
    property int hoverWin: 0
    readonly property bool _alive: tileOrder.length > 0 && _animate()
                                   && !(typeof animPolicy !== "undefined" && animPolicy.screenIdle)
    Timer {
        interval: 90; repeat: true; running: tilingRoot._alive
        onTriggered: {
            var w = 0
            if (!tilingRoot.shuffling && tilingRoot.dragHoldWin === 0) {
                var s = tilingRoot.slotIndexAt(windowMgr.mouseX, windowMgr.mouseY)
                if (s >= 0 && s < tilingRoot.tileOrder.length) w = tilingRoot.tileOrder[s]
            }
            if (w !== tilingRoot.hoverWin) { tilingRoot.hoverWin = w; tilingRoot.updateLayout() }
        }
    }
    property real breath: 0
    NumberAnimation on breath {
        running: tilingRoot._alive
        from: 0; to: 1; duration: 6000; loops: Animation.Infinite
    }
    // 0..1 for a card: the shared breath, offset by its slot
    function breathOf(winId) {
        var i = tileOrder.indexOf(winId); if (i < 0) return 0
        return 0.5 + 0.5 * Math.sin(2 * Math.PI * (breath - i / Math.max(1, tileOrder.length)))
    }

    // a card came to rest in its place (the frame answers with a gold-foil glint)
    signal cardLanded(int winId)

    // ── Shuffle the Spread (tarot, 2026-09-26) ───────────────────────────────
    // Operator: "they could deal and move once eight are open and stacked … and
    // shuffle … then rest in their places". Gather: every card glides into a fanned
    // deck at the centre of the work area, one after another. A beat. The order is
    // shuffled (never the same as before), then the cards are dealt back out to the
    // grid — the deal above — and each glints as it comes to rest. While shuffling,
    // the stack holds still (our own moves would otherwise re-lay it out mid-gather).
    property bool shuffling: false
    function _scanPos() {
        var m = {}
        for (var i = 0; i < windowMgr.count; i++) {
            var e = windowMgr.index(i, 0)
            m[windowMgr.data(e, 0x101)] = { x: windowMgr.data(e, 0x102), y: windowMgr.data(e, 0x103),
                                            w: windowMgr.data(e, 0x104), h: windowMgr.data(e, 0x105) }
        }
        return m
    }
    function shuffleSpread() {
        if (shuffling || tileOrder.length < 2 || dragHoldWin !== 0) return
        var n = tileOrder.length
        if (!_animate()) { _reorder(); updateLayout(); return }
        shuffling = true
        var now = _scanPos()
        var cx = leftMargin + (window.width - leftMargin - rightMargin) / 2
        var cy = topMargin + (window.height - topMargin - bottomMargin) / 2
        for (var i = 0; i < n; i++) {
            var id = tileOrder[i], s = now[id]
            if (!s) continue
            var fan = (i - (n - 1) / 2)
            var tx = cx - s.w / 2 + fan * 16, ty = cy - s.h / 2 + Math.abs(fan) * 3
            _pos[id] = { x: s.x, y: s.y }
            delete _glides[id]
            deal(id, i, tx, ty, s.w, s.h)
        }
        gatherDone.interval = dealMs + n * dealStagger + 280
        gatherDone.restart()
    }
    function _reorder() {
        var a = tileOrder.slice(), before = a.join(",")
        for (var tries = 0; tries < 6 && a.join(",") === before; tries++)
            for (var i = a.length - 1; i > 0; i--) { var j = Math.floor(Math.random() * (i + 1)); var t = a[i]; a[i] = a[j]; a[j] = t }
        tileOrder = a
    }
    Timer {
        id: gatherDone; repeat: false
        onTriggered: { tilingRoot._reorder(); tilingRoot.shuffling = false; tilingRoot.updateLayout() }
    }

    function updateLayout() {
        if (shuffling) return
        _pos = ({})
        var present = {}
        var ids = []
        for (var i = 0; i < windowMgr.count; i++) {
            var entry = windowMgr.index(i, 0)
            // 0x10A was TitleRole (a non-empty string, always truthy) — every window
            // silently matched "tiled" no matter its real state. 0x10B = the real
            // TiledRole added to NCDEWindowManager.h (2026-06-30).
            var tiled = windowMgr.data(entry, 0x10B)
            var minimized = windowMgr.data(entry, 0x108)
            // 0x109 = MaximizedRole. A maximized window is NEVER in the grid (operator
            // 2026-07-06: windows open max; "only unmax makes them small" — one window at
            // a time holds the max slot). Amethyst/Green keep tiled+maximized consistent,
            // but GliaGlobalMenus' maximize toggle flips `maximized` without touching
            // `tiled` — without this guard the next dataChanged would snap that window
            // straight back into the grid.
            var maximized = windowMgr.data(entry, 0x109)
            // 0x107 = AppIdRole — verified against NCDEWindowManager::roleNames()
            // (disasm 0x77cfc: 0x101 winId, 0x102 x, 0x103 y, 0x104 w, 0x105 h,
            // 0x106 name, 0x107 appId, 0x108 minimized, 0x109 maximized,
            // 0x10A title, 0x10B tiled). NOTE: 0x103 is the Y-COORDINATE role,
            // and Hud.qml's UserRole+2/+3 title/appId reads are wrong the same
            // way — do not copy role numbers from Hud.qml. Games are never
            // grid-tiled (patch 2026-07-11): a Steam/Proton game owns its own
            // geometry; snapping it into the tile grid resized/insetted it like
            // a text editor. Keep this appId list in sync with main.qml's isGame.
            var gAppId = String(windowMgr.data(entry, 0x107) || "").toLowerCase()
            // ONLY actual game surfaces — NOT the Steam client UI (steam/steamwebhelper).
            // Keep in sync with main.qml isGame. Regression fix 2026-07-12.
            var isGame = gAppId.indexOf("steam_app_") === 0 || gAppId === "gamescope"
            if (tiled && !minimized && !maximized && !isGame) {
                var wid = windowMgr.data(entry, 0x101)
                _pos[wid] = { x: windowMgr.data(entry, 0x102), y: windowMgr.data(entry, 0x103) }
                present[wid] = true
                ids.push(wid)
            }
        }

        // Stable user order: keep the prior arrangement, append newly-tiled at the end.
        var ordered = []
        for (var k = 0; k < tileOrder.length; k++)
            if (present[tileOrder[k]] === true) { ordered.push(tileOrder[k]); present[tileOrder[k]] = false }
        for (var m = 0; m < ids.length; m++)
            if (present[ids[m]] === true) ordered.push(ids[m])
        tileOrder = ordered

        // A held window that vanished mid-drag (closed/minimized) must not stall layout.
        if (dragHoldWin !== 0 && ordered.indexOf(dragHoldWin) < 0) dragHoldWin = 0

        var n = ordered.length
        if (n === 0) { lastCells = []; return }

        var availX = leftMargin
        var availY = topMargin
        var availW = window.width - leftMargin - rightMargin
        var availH = window.height - topMargin - bottomMargin

        var cells = []
        if (n === 1) {
            // Test-group item 1 (operator 2026-07-06): "the first window when unmaxed
            // should be small." A 1-cell grid filled the whole work area and looked
            // identical to maximized — a lone tiled window is now a small centered
            // window instead. 2+ windows use the normal grid below, unchanged.
            var sw = Math.max(420, availW * 0.52)
            var sh = Math.max(300, availH * 0.56)
            cells.push({ x: availX + (availW - sw) / 2,
                         y: availY + (availH - sh) / 2,
                         w: sw, h: sh })
        } else {
            var cols = Math.min(4, n)
            var rows = Math.ceil(n / cols)
            var cellW = (availW - (cols + 1)*gap) / cols
            var cellH = (availH - (rows + 1)*gap) / rows
            for (var j = 0; j < n; j++) {
                var col = j % cols
                var row = Math.floor(j / cols)
                cells.push({ x: availX + gap + (col * (cellW + gap)),
                             y: availY + gap + (row * (cellH + gap)),
                             w: cellW, h: cellH })
            }
        }
        lastCells = cells

        for (var p = 0; p < n; p++) {
            // The window the user is holding stays under the cursor; its slot stays open.
            if (ordered[p] === dragHoldWin) continue
            var c = cells[p]
            // Inset the CLIENT by the real glass-frame overhang (24px left/right, 44 top,
            // 38 bottom - see NCDEWindowManager.h registerFrameWindow + main.qml's frameWin
            // x/y/width/height bindings) so the GLASS FRAME itself fills the tile cell
            // edge-to-edge, leaving exactly `gap` between neighboring frames. The old inset
            // (10/31, tw-20/th-53) was smaller than the real overhang, so adjacent glass
            // frames overlapped by ~18-19px on both axes - confirmed by the numbers, not a
            // guess. Worst at 8 windows (a full 4x2 grid) since both row and column overlaps
            // stack at once.
            tilingRoot.deal(ordered[p], p,
                c.x + 24, c.y + 44 - (ordered[p] === hoverWin ? hoverLift : 0),
                Math.max(160, c.w - 48),
                Math.max(80, c.h - 82))
        }
    }

    // ── Grab-and-reorder (test-group item 2; flow modeled on the operator's
    // Tiling Shell / Snap Assist reference: grab a tile, hover a slot, the stack
    // responds live, drop commits) ─────────────────────────────────
    property int hoverSlot: -1

    function slotIndexAt(gx, gy) {
        for (var i = 0; i < lastCells.length; i++) {
            var c = lastCells[i]
            if (gx >= c.x && gx <= c.x + c.w && gy >= c.y && gy <= c.y + c.h) return i
        }
        return -1
    }
    function beginTileDrag(winId) { dragHoldWin = winId; hoverSlot = -1 }
    // Called on every drag move: when the cursor settles over a different slot for
    // 140ms, the other tiles shuffle live around the held window (the windows
    // themselves are the drop preview — no overlay needed). The settle timer keeps
    // fast sweeps across the grid from relayout-thrashing the GLX frame windows.
    function tileDragHover(winId, gx, gy) {
        if (winId !== dragHoldWin) return
        var s = slotIndexAt(gx, gy)
        if (s === hoverSlot) return
        hoverSlot = s
        if (s >= 0 && s !== tileOrder.indexOf(winId)) hoverCommit.restart()
        else hoverCommit.stop()
    }
    Timer {
        id: hoverCommit
        interval: 140; repeat: false
        onTriggered: {
            if (tilingRoot.dragHoldWin === 0 || tilingRoot.hoverSlot < 0) return
            var from = tilingRoot.tileOrder.indexOf(tilingRoot.dragHoldWin)
            if (from < 0 || tilingRoot.hoverSlot === from) return
            var arr = tilingRoot.tileOrder.slice()
            arr.splice(from, 1)
            arr.splice(tilingRoot.hoverSlot, 0, tilingRoot.dragHoldWin)
            tilingRoot.tileOrder = arr
            tilingRoot.updateLayout()   // held window is skipped — the rest shuffle live
        }
    }
    function endTileDrag(winId, gx, gy) {
        hoverCommit.stop()
        hoverSlot = -1
        dragHoldWin = 0
        var slot = slotIndexAt(gx, gy)
        var from = tileOrder.indexOf(winId)
        if (slot >= 0 && from >= 0 && slot !== from) {
            var arr = tileOrder.slice()
            arr.splice(from, 1)
            arr.splice(slot, 0, winId)
            tileOrder = arr
        }
        // Always relayout: either the new order applies, or the held window snaps home.
        updateLayout()
    }

    Timer {
        id: tilingDebounce; interval: 1; repeat: false
        onTriggered: tilingRoot.updateLayout()
    }

    Connections {
        target: windowMgr
        function onDataChanged() { tilingDebounce.restart() }
        function onCountChanged() { tilingDebounce.restart() }
    }

    // ── Snap indicator ────────────────────────────────────────────
    Rectangle {
        id: snapIndicator; visible: false; z: 299
        color: Qt.rgba(ncde.glow.r,ncde.glow.g,ncde.glow.b,0.08)
        border.color: Qt.rgba(ncde.glow.r,ncde.glow.g,ncde.glow.b,0.6); border.width:2;radius:4
        Behavior on x{NumberAnimation{duration:80}} Behavior on y{NumberAnimation{duration:80}}
        Behavior on width{NumberAnimation{duration:80}} Behavior on height{NumberAnimation{duration:80}}
    }

    // ── Snap preview overlay ──────────────────────────────────────
    Rectangle {
        id: snapPreview
        z: 850
        visible: windowMgr.snapZone !== 0
        opacity: visible ? 1.0 : 0.0

        readonly property int gap: 8
        x: windowMgr.snapZone === 2 ? window.width / 2 + gap / 2 : gap
        y: windowMgr.snapZone === 3 ? 0 : gap
        width:  windowMgr.snapZone === 3 ? window.width
                                         : window.width / 2 - gap * 1.5
        height: windowMgr.snapZone === 3 ? window.height : window.height - gap * 2

        color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.13)
        border.color: Qt.rgba(ncde.accent.r, ncde.accent.g, ncde.accent.b, 0.72)
        border.width: 2
        radius: 14

        Rectangle {
            anchors.fill: parent; anchors.margins: 1
            radius: parent.radius - 1
            color: "transparent"
            border.color: Qt.rgba(1, 1, 1, 0.10)
            border.width: 1
        }

        Behavior on x      { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
        Behavior on y      { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
        Behavior on width  { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
        Behavior on height { NumberAnimation { duration: 140; easing.type: Easing.OutCubic } }
        Behavior on opacity { NumberAnimation { duration: 100 } }
    }
}
