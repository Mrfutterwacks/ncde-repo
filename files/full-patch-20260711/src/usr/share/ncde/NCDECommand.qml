// ╔════════════════════════════════════════════════════════════════════╗
// ║  NCDECommand.qml — NCDE Software Centre · Mucha theatrical skin       ║
// ║                                                                      ║
// ║  Standalone window loaded by ncde-command/main.cpp.                  ║
// ║  Context properties required (all set before load):                 ║
// ║     pkgMgr   — PackageManager  (installed/updates/results/busy/…)    ║
// ║     ncde     — NCDEEngine      (accent/glow/panelText/border/…)      ║
// ║     theme    — ThemeTokens     (fontSmall/Medium/Large/fontFamily)   ║
// ║     settings — Settings                                              ║
// ║     launcher — Launcher                                              ║
// ║                                                                      ║
// ║  Self-contained: ALL ornament drawn with Canvas (Qt paint).          ║
// ║  No external image/JS dependencies. No MouseArea — TapHandler only.  ║
// ╚════════════════════════════════════════════════════════════════════╝

import QtQuick
import QtQuick.Window
import QtQuick.Controls.Basic
import NCDE.Glia
import "mucha-panels.js" as P

ApplicationWindow {
    id: win
    visible: true
    width: 1200
    height: 780
    minimumWidth: 960
    minimumHeight: 620
    title: "Belle Époque de NCDE"
    color: k.panelBg
    readonly property bool motionEnabled: typeof animPolicy === "undefined" || animPolicy === null
        || animPolicy.decorative
    readonly property bool screenAwake: typeof animPolicy === "undefined" || animPolicy === null
        || !animPolicy.screenIdle
    readonly property bool idleMotionEnabled: typeof animPolicy === "undefined" || animPolicy === null
        || animPolicy.idleLoops
    readonly property real motionDurationScale: typeof animPolicy !== "undefined" && animPolicy !== null
        && (animPolicy.thermalPressure || animPolicy.lowPower) ? 2.0 : 1.0

    // ── palette ────────────────────────────────────────────────────────
    // NCDEKit supplies font names, gilt, and ink; theatrical colors are fixed.
    // paper1/2/3 stay always-light — they are legibility cards on the dark stage.
    // wine1-4 are the crimson curtain identity; they don't map to NCDEKit wine.
    NCDEKit { id: k }
    QtObject {
        id: m
        // theatrical stage constants (Canvas + curtains)
        readonly property color night1:  "#1a1022"
        readonly property color night2:  k.panelBg
        readonly property color night3:  "#060409"
        readonly property color wine1:   k.wine1
        readonly property color wine2:   k.wine2
        readonly property color wine3:   k.wine3
        readonly property color wine4:   k.wine4
        // parchment overlay cards — always light for stage readability
        readonly property color paper1:  k.surface
        readonly property color paper2:  k.surfaceAlt
        readonly property color paper3:  k.surfaceAlt
        // theme-engine tokens
        readonly property color gilt0:   k.gilt0
        readonly property color gilt1:   k.gilt1
        readonly property color gilt2:   k.gilt2
        readonly property color gilt3:   k.gilt3
        readonly property color gilt4:   k.gilt4
        readonly property color gilt5:   k.gilt5
        readonly property color ink:     k.ink
        readonly property string display: k.display
        readonly property string serif:   k.serif
        readonly property string mono:    "monospace"
        // live accent from the engine (footlights, selection glow)
        readonly property color accent:  ncde.accent
        readonly property color glow:    ncde.glow
    }

    // fsSmall/fsMed/fsLarge removed 2026-09-23: declared, never referenced anywhere
    // else in this file (grep-confirmed) — dead duplication of theme.fontSmall/
    // Medium/Large, which every actual font.pixelSize call site here reads via k.fs().
    readonly property string bodyFont: (theme && theme.fontFamily) ? theme.fontFamily : "Noto Sans"

    property int currentTab: 0   // 0 Browse · 1 Installed · 2 Updates · 3 Manual · 4 Fonts
    property string activeCat: "Editors"
    property string activeAuth: ""   // "pkg" or "font" — routes passwordEntered/cancelled
    property int liftedIndex: -1

    // ── GliaTalk global-menu publishing (2026-07-12) ─────────────────────
    // NCDECommand is NCDE's App Store + System Updater. It published NO
    // _NCDE_MENUS (glia half-measure). Publish its real menus via the shared
    // NCDE.Glia plugin so they appear in the top-panel global bar. Every id
    // maps to an EXISTING member: the Store/Updates navigation items set the
    // real `currentTab` property (the 5 store sections); the action items
    // call real pkgMgr methods already invoked by the app's own buttons
    // (checkUpdates() @1013, getInstalled() @914, updateAll() @1005). No new
    // behavior invented. Per-package Install/Remove are NOT published — they
    // require a selected package and cannot be no-arg global-menu actions.
    GliaTalkPublisher { id: glia }
    function handleGliaMenu(id) {
        if      (id === 101) Qt.quit()               // File ▸ Quit
        else if (id === 201) win.currentTab = 0      // Store ▸ Browse Catalog
        else if (id === 202) win.currentTab = 1      // Store ▸ Installed
        else if (id === 203) win.currentTab = 4      // Store ▸ Fonts
        else if (id === 204) win.currentTab = 3      // Store ▸ Operating Manual
        else if (id === 301) win.currentTab = 2      // Updates ▸ View Updates
        else if (id === 302) pkgMgr.checkUpdates()   // Updates ▸ Check for Updates
        else if (id === 303) pkgMgr.updateAll()      // Updates ▸ Update All
        else if (id === 304) pkgMgr.getInstalled()   // Updates ▸ Refresh Installed
    }
    function publishGliaMenus() {
        glia.attach(win)
        glia.menusJson = JSON.stringify([
            { title: "File", items: [
                { label: "Quit",              id: 101 } ] },
            { title: "Store", items: [
                { label: "Browse Catalog",    id: 201 },
                { label: "Installed",         id: 202 },
                { label: "Fonts",             id: 203 },
                { label: "Operating Manual",  id: 204 } ] },
            { title: "Updates", items: [
                { label: "View Updates",      id: 301 },
                { label: "Check for Updates", id: 302 },
                { label: "Update All",        id: 303 },
                { label: "Refresh Installed", id: 304 } ] }
        ])
    }
    Connections {
        target: glia
        function onInvoked(id) { win.handleGliaMenu(id) }
    }

    // ════════════════════════════════════════════════════════════════════
    //  REUSABLE ORNAMENT COMPONENTS (all Canvas-drawn)
    // ════════════════════════════════════════════════════════════════════

    // 8-petal gilt floret medallion
    component Floret: Canvas {
        width: 26; height: 26
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var cx = width/2, cy = height/2, R = Math.min(cx,cy) - 1;
            var g = ctx.createRadialGradient(cx,cy,0,cx,cy,R);
            g.addColorStop(0,k.gilt5); g.addColorStop(0.6,k.gilt3); g.addColorStop(1,k.gilt0);
            ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fillStyle=g; ctx.fill();
            ctx.lineWidth=1; ctx.strokeStyle=k.gilt0; ctx.stroke();
            ctx.fillStyle="rgba(90,58,20,0.85)";
            for (var i=0;i<8;i++){
                ctx.save(); ctx.translate(cx,cy); ctx.rotate(i*Math.PI/4);
                ctx.translate(0,-R*0.58); ctx.scale(0.38,1.0);
                ctx.beginPath(); ctx.arc(0,0,R*0.30,0,2*Math.PI); ctx.fill(); ctx.restore();
            }
            ctx.beginPath(); ctx.arc(cx,cy,R*0.23,0,2*Math.PI); ctx.fillStyle=k.gilt4; ctx.fill();
            ctx.lineWidth=0.7; ctx.strokeStyle=k.gilt0; ctx.stroke();
            ctx.beginPath(); ctx.arc(cx,cy,R*0.085,0,2*Math.PI); ctx.fillStyle=k.gilt0; ctx.fill();
        }
        Component.onCompleted: requestPaint()
    }

    // Square Mucha app-cover frame: parchment card, gilt double border,
    // arched crown, corner florets, name plaque.
    component AppFrame: Canvas {
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var w = width, h = height;
            var r = 12, pad = 4;
            // parchment card
            var pg = ctx.createLinearGradient(0,0,0,h);
            pg.addColorStop(0,k.surface); pg.addColorStop(1,k.surfaceAlt);
            P.roundRectPath(ctx, pad, pad, w-2*pad, h-2*pad, r);
            ctx.fillStyle = pg; ctx.fill();
            // gilt double border
            ctx.lineWidth=2.5; ctx.strokeStyle=k.gilt0; ctx.stroke();
            P.roundRectPath(ctx, pad+4, pad+4, w-2*pad-8, h-2*pad-8, r-3);
            ctx.lineWidth=1; ctx.strokeStyle=k.gilt3; ctx.stroke();
            // top arch crown
            ctx.beginPath();
            ctx.moveTo(w*0.30, pad+14);
            ctx.quadraticCurveTo(w*0.5, pad+2, w*0.70, pad+14);
            ctx.lineWidth=1.4; ctx.strokeStyle=k.gilt1; ctx.stroke();
            // name plaque rule
            ctx.beginPath();
            ctx.moveTo(pad+14, h-h*0.30); ctx.lineTo(w-pad-14, h-h*0.30);
            ctx.lineWidth=1; ctx.strokeStyle=k.gilt1; ctx.globalAlpha=0.7; ctx.stroke(); ctx.globalAlpha=1;
            // corner dots
            ctx.fillStyle=k.gilt3;
            var cd=[[pad+10,pad+10],[w-pad-10,pad+10],[pad+10,h-pad-10],[w-pad-10,h-pad-10]];
            for (var i=0;i<4;i++){ ctx.beginPath(); ctx.arc(cd[i][0],cd[i][1],2.4,0,2*Math.PI); ctx.fill(); }
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
    }

    // Tall arched Mucha portrait frame for the detail panel.
    component PortraitFrame: Canvas {
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var w = width, h = height, pad = 6;
            var archH = w*0.42;
            // arched parchment body
            ctx.beginPath();
            ctx.moveTo(pad, h-pad);
            ctx.lineTo(pad, pad+archH);
            ctx.quadraticCurveTo(pad, pad, w*0.5, pad);
            ctx.quadraticCurveTo(w-pad, pad, w-pad, pad+archH);
            ctx.lineTo(w-pad, h-pad);
            ctx.closePath();
            var pg = ctx.createLinearGradient(0,0,0,h);
            pg.addColorStop(0,k.surface); pg.addColorStop(0.5,k.surfaceAlt); pg.addColorStop(1,k.surfaceAlt);
            ctx.fillStyle = pg; ctx.fill();
            ctx.lineWidth=3; ctx.strokeStyle=k.gilt0; ctx.stroke();
            // inner gilt hairline following the same arch
            ctx.beginPath();
            ctx.moveTo(pad+6, h-pad-6);
            ctx.lineTo(pad+6, pad+archH);
            ctx.quadraticCurveTo(pad+6, pad+6, w*0.5, pad+6);
            ctx.quadraticCurveTo(w-pad-6, pad+6, w-pad-6, pad+archH);
            ctx.lineTo(w-pad-6, h-pad-6);
            ctx.closePath();
            ctx.lineWidth=1; ctx.strokeStyle=k.gilt3; ctx.stroke();
        }
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
    }

    // Gilt section rule with centered Cinzel caption
    component SectionRule: Item {
        property string text: ""
        implicitHeight: 22
        Rectangle { anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    width: (parent.width - lbl.width)/2 - 14; height: 1; color: m.gilt1; opacity: 0.55 }
        Text { id: lbl; anchors.centerIn: parent; text: parent.text
               color: m.gilt3; font.family: m.display; font.bold: true
               font.pixelSize: k.fs(12); font.letterSpacing: 3 }
        Rectangle { anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right
                    width: (parent.width - lbl.width)/2 - 14; height: 1; color: m.gilt1; opacity: 0.55 }
    }

    // Gilt button — kind: "gold" | "wine" | "ghost"
    component GiltButton: Item {
        id: gb
        property string text: ""
        property string kind: "gold"
        property bool enabledState: true
        property bool lit: false
        signal clicked()
        implicitWidth: Math.max(96, lblB.implicitWidth + 36)
        implicitHeight: 32
        opacity: enabledState ? 1.0 : 0.4
        Rectangle {
            anchors.fill: parent; radius: 6
            border.color: gb.lit ? m.gilt5 : (gb.kind === "ghost" ? m.gilt1 : m.gilt0)
            border.width: gb.kind === "ghost" ? 1 : (gb.lit ? 3 : 2)
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop { position: 0; color: gb.kind === "wine" ? (hb.hovered ? m.wine4 : m.wine3)
                                                  : gb.kind === "ghost" ? "transparent"
                                                  : (hb.hovered ? m.gilt5 : m.gilt4) }
                GradientStop { position: 1; color: gb.kind === "wine" ? m.wine1
                                                  : gb.kind === "ghost" ? "transparent"
                                                  : m.gilt3 }
            }
        }
        Text {
            id: lblB; anchors.centerIn: parent; text: gb.text
            color: gb.kind === "wine" ? m.gilt5 : gb.kind === "ghost" ? m.gilt1 : m.wine1
            font.family: m.display; font.bold: true; font.pixelSize: k.fs(12); font.letterSpacing: 1
        }
        HoverHandler { id: hb; enabled: gb.enabledState; cursorShape: Qt.PointingHandCursor }
        TapHandler { enabled: gb.enabledState; onTapped: gb.clicked() }
    }

    // ════════════════════════════════════════════════════════════════════
    //  LAYER 0 — THEATRICAL STAGE BACKDROP
    // ════════════════════════════════════════════════════════════════════
    Canvas {
        id: stage
        anchors.fill: parent
        antialiasing: true
        property color footlight: m.glow
        onFootlightChanged: requestPaint()
        onWidthChanged: requestPaint()
        onHeightChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var w = width, h = height;

            // night sky
            var sky = ctx.createLinearGradient(0,0,0,h);
            sky.addColorStop(0,"#1a1022"); sky.addColorStop(0.55,k.panelBg); sky.addColorStop(1,"#060409");
            ctx.fillStyle = sky; ctx.fillRect(0,0,w,h);

            // stars (deterministic)
            for (var i=0;i<140;i++){
                var sx = (i*97.13) % w;
                var sy = (i*53.77) % (h*0.62);
                var a = 0.15 + ((i*37)%100)/100 * 0.6;
                var rr = 0.4 + ((i*7)%10)/10 * 1.1;
                ctx.globalAlpha = a; ctx.fillStyle = k.gilt5;
                ctx.beginPath(); ctx.arc(sx,sy,rr,0,2*Math.PI); ctx.fill();
            }
            ctx.globalAlpha = 1;

            // moon upper area
            var mx = w*0.50, my = h*0.165, mr = Math.min(60, h*0.085);
            var halo = ctx.createRadialGradient(mx,my,mr*0.4, mx,my,mr*3.2);
            halo.addColorStop(0,"rgba(246,227,176,0.35)"); halo.addColorStop(1,"rgba(246,227,176,0)");
            ctx.fillStyle = halo; ctx.beginPath(); ctx.arc(mx,my,mr*3.2,0,2*Math.PI); ctx.fill();
            var disc = ctx.createRadialGradient(mx-mr*0.3,my-mr*0.3,mr*0.2, mx,my,mr);
            disc.addColorStop(0,"#fbf2cf"); disc.addColorStop(1,"#dcab5e");
            ctx.fillStyle = disc; ctx.beginPath(); ctx.arc(mx,my,mr,0,2*Math.PI); ctx.fill();
            ctx.lineWidth=1.5; ctx.strokeStyle="rgba(201,138,58,0.5)";
            ctx.beginPath(); ctx.arc(mx,my,mr+6,0,2*Math.PI); ctx.stroke();

            // side curtains
            drawCurtain(ctx, 0, 0, w*0.135, h, false);
            drawCurtain(ctx, w*0.865, 0, w*0.135, h, true);

            // top valance with scallops
            drawValance(ctx, w, h*0.092);

            // gilt proscenium arch outline
            ctx.beginPath();
            var ax = w*0.135, aw = w*0.73, atop = h*0.115, aR = aw*0.20;
            ctx.moveTo(ax, h);
            ctx.lineTo(ax, atop + aR);
            ctx.quadraticCurveTo(ax, atop, ax + aR, atop);
            ctx.lineTo(ax + aw - aR, atop);
            ctx.quadraticCurveTo(ax + aw, atop, ax + aw, atop + aR);
            ctx.lineTo(ax + aw, h);
            ctx.lineWidth = 2; ctx.strokeStyle = "rgba(201,138,58,0.45)"; ctx.stroke();

            // footlights along the apron
            var fy = h - 30, n = 11, gap = (w*0.73)/(n-1), fx0 = w*0.135;
            var fc = stage.footlight;
            for (var li=0;li<n;li++){
                var fx = fx0 + li*gap;
                var fg = ctx.createRadialGradient(fx,fy,1, fx,fy,26);
                fg.addColorStop(0, withAlpha(fc,0.55)); fg.addColorStop(1, withAlpha(fc,0));
                ctx.fillStyle = fg; ctx.beginPath(); ctx.arc(fx,fy-6,26,0,2*Math.PI); ctx.fill();
                // brass lamp
                ctx.beginPath(); ctx.arc(fx,fy,5,Math.PI,2*Math.PI);
                ctx.fillStyle=k.gilt4; ctx.fill();
                ctx.lineWidth=1; ctx.strokeStyle=k.gilt0; ctx.stroke();
            }
            // apron rail
            var rail = ctx.createLinearGradient(0,fy+2,0,fy+10);
            rail.addColorStop(0,k.gilt1); rail.addColorStop(1,"#3a2410");
            ctx.fillStyle = rail; ctx.fillRect(w*0.135, fy+4, w*0.73, 7);
        }

        function withAlpha(c, a) {
            return "rgba(" + Math.round(c.r*255) + "," + Math.round(c.g*255) + "," + Math.round(c.b*255) + "," + a + ")";
        }
        function drawCurtain(ctx, x, y, cw, ch, mirror) {
            ctx.save();
            if (mirror) { ctx.translate(x+cw, y); ctx.scale(-1,1); ctx.translate(-x, -y); }
            var g = ctx.createLinearGradient(x,0,x+cw,0);
            g.addColorStop(0,k.wine1); g.addColorStop(0.5,k.wine3); g.addColorStop(1,k.wine2);
            ctx.fillStyle = g; ctx.fillRect(x,y,cw,ch);
            // folds
            for (var i=1;i<5;i++){
                var fx = x + cw*(i/5);
                ctx.beginPath(); ctx.moveTo(fx, y); ctx.lineTo(fx, y+ch);
                ctx.lineWidth=1.5; ctx.strokeStyle="rgba(0,0,0,0.22)"; ctx.stroke();
                ctx.beginPath(); ctx.moveTo(fx+3, y); ctx.lineTo(fx+3, y+ch);
                ctx.lineWidth=1; ctx.strokeStyle="rgba(201,138,58,0.10)"; ctx.stroke();
            }
            // scalloped inner hem
            ctx.beginPath(); ctx.moveTo(x+cw, y);
            var sc=10, sh=ch/sc;
            for (var s=0;s<sc;s++){
                var yy=y+s*sh;
                ctx.quadraticCurveTo(x+cw-14, yy+sh*0.5, x+cw, yy+sh);
            }
            ctx.lineTo(x+cw, y+ch); ctx.lineWidth=2; ctx.strokeStyle=k.gilt3; ctx.stroke();
            ctx.restore();
        }
        function drawValance(ctx, w, vh) {
            var g = ctx.createLinearGradient(0,0,0,vh);
            g.addColorStop(0,k.wine2); g.addColorStop(1,k.wine3);
            ctx.beginPath(); ctx.moveTo(0,0); ctx.lineTo(w,0); ctx.lineTo(w,vh*0.55);
            var sc=Math.max(6, Math.round(w/110)), sw=w/sc;
            for (var s=sc;s>0;s--){
                var xx=s*sw;
                ctx.quadraticCurveTo(xx-sw*0.5, vh*1.15, xx-sw, vh*0.55);
            }
            ctx.lineTo(0,0); ctx.closePath(); ctx.fillStyle=g; ctx.fill();
            // gilt scallop trim + tassels
            ctx.lineWidth=2; ctx.strokeStyle=k.gilt3;
            for (var t=0;t<sc;t++){
                var cxp=t*sw+sw*0.5;
                ctx.beginPath(); ctx.arc(cxp, vh*0.55, 3, 0, 2*Math.PI);
                ctx.fillStyle=k.gilt4; ctx.fill();
                ctx.beginPath(); ctx.moveTo(cxp, vh*0.58); ctx.lineTo(cxp, vh*0.78);
                ctx.stroke();
            }
        }
    }
    // repaint footlights when the engine accent changes
    Connections { target: ncde; function onThemeChanged() { stage.footlight = ncde.glow; stage.requestPaint() } }

    // soft vignette
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 1.0; color: Qt.rgba(0,0,0,0.35) }
        }
    }

    // House lights — washes only the stage opening (between curtains, below valance).
    // Curtains (x < 13.5% and x > 86.5%) and valance (top 9.2%) stay crimson.
    Rectangle {
        x: parent.width  * 0.135
        y: parent.height * 0.092
        width:  parent.width  * 0.730
        height: parent.height * 0.908
        color: Qt.rgba(0.98, 0.91, 0.72, k.dark ? 0.0 : 0.72)
        Behavior on color { ColorAnimation { duration: 320 } }
    }

    // ════════════════════════════════════════════════════════════════════
    //  HEADER — title cartouche
    // ════════════════════════════════════════════════════════════════════
    Item {
        id: header
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        anchors.topMargin: 14
        height: 56

        Floret { width: 24; height: 24; anchors.verticalCenter: parent.verticalCenter; x: parent.width*0.5 - 184 }
        Floret { width: 24; height: 24; anchors.verticalCenter: parent.verticalCenter; x: parent.width*0.5 + 160 }

        Column {
            anchors.centerIn: parent
            spacing: 1
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "BELLE ÉPOQUE"
                color: m.gilt5; font.family: m.display; font.bold: true
                font.pixelSize: k.fs(28); font.letterSpacing: 9
                style: Text.Raised; styleColor: Qt.rgba(0,0,0,0.6)
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "· DE NCDE · SOFTWARE CENTRE ·"
                color: m.gilt3; font.family: m.serif; font.italic: true
                font.pixelSize: k.fs(13); font.letterSpacing: 3
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  TAB BAR — gilt cartouches
    // ════════════════════════════════════════════════════════════════════
    Row {
        id: tabBar
        anchors.top: header.bottom; anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 6
        z: 5
        Repeater {
            model: [
                { label: "BROWSE",          idx: 0 },
                { label: "INSTALLED",       idx: 1 },
                { label: "UPDATES",         idx: 2 },
                { label: "OPERATING MANUAL",idx: 3 },
                { label: "FONTS",           idx: 4 }
            ]
            Rectangle {
                width: tl.implicitWidth + (modelData.idx === 2 && pkgMgr.updateCount > 0 ? 64 : 40)
                height: 34; radius: 8
                property bool sel: win.currentTab === modelData.idx
                border.color: sel ? m.gilt0 : m.gilt1
                border.width: sel ? 2 : 1
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: sel ? m.gilt4 : (th.hovered ? m.wine3 : m.wine2) }
                    GradientStop { position: 1; color: sel ? m.gilt3 : m.wine1 }
                }
                Row {
                    anchors.centerIn: parent; spacing: 8
                    Text {
                        id: tl; text: modelData.label
                        color: sel ? m.wine1 : m.gilt4
                        font.family: m.display; font.bold: true
                        font.pixelSize: k.fs(12); font.letterSpacing: 1.5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    // updates badge
                    Rectangle {
                        visible: modelData.idx === 2 && pkgMgr.updateCount > 0
                        width: 22; height: 18; radius: 9
                        color: m.wine3; border.color: m.gilt4; border.width: 1
                        anchors.verticalCenter: parent.verticalCenter
                        Text { anchors.centerIn: parent; text: pkgMgr.updateCount
                               color: m.gilt5; font.family: m.mono; font.pixelSize: k.fs(10); font.bold: true }
                    }
                }
                HoverHandler { id: th; cursorShape: Qt.PointingHandCursor }
                TapHandler { onTapped: win.currentTab = modelData.idx }
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  CONTENT AREA
    // ════════════════════════════════════════════════════════════════════
    Item {
        id: content
        anchors.top: tabBar.bottom; anchors.topMargin: 14
        anchors.left: parent.left; anchors.right: parent.right
        anchors.leftMargin: parent.width*0.145
        anchors.rightMargin: parent.width*0.145
        anchors.bottom: prompterBox.top; anchors.bottomMargin: 12

        // ─────────────────────────────────────────────────────────────
        //  TAB 0 — BROWSE (Cover Flow)
        // ─────────────────────────────────────────────────────────────
        Item {
            anchors.fill: parent
            visible: win.currentTab === 0

            // search field
            Rectangle {
                id: searchBox
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 38; radius: 19
                border.color: m.gilt0; border.width: 2
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.paper1 }
                    GradientStop { position: 1; color: m.paper2 }
                }
                Text {
                    anchors.left: parent.left; anchors.leftMargin: 18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "⚲"; color: m.gilt1; font.pixelSize: k.fs(18)
                }
                TextInput {
                    id: searchField
                    anchors.left: parent.left; anchors.leftMargin: 44
                    anchors.right: parent.right; anchors.rightMargin: 100
                    anchors.verticalCenter: parent.verticalCenter
                    color: m.wine2; font.family: m.serif; font.pixelSize: k.fs(18)
                    clip: true; selectByMouse: true
                    onAccepted: { if (text.trim() !== "") { pkgMgr.search(text.trim()); win.activeCat = "" } }
                    Text {
                        anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                        text: "Search the repertoire…"; color: m.gilt1
                        font.family: m.serif; font.italic: true; font.pixelSize: k.fs(18)
                        visible: !searchField.text && !searchField.activeFocus
                    }
                }
                GiltButton {
                    anchors.right: parent.right; anchors.rightMargin: 4
                    anchors.verticalCenter: parent.verticalCenter
                    height: 30; text: "SEARCH"
                    onClicked: { if (searchField.text.trim() !== "") { pkgMgr.search(searchField.text.trim()); win.activeCat = "" } }
                }
            }

            // category chips
            Flow {
                id: chips
                anchors.top: searchBox.bottom; anchors.topMargin: 10
                anchors.left: parent.left; anchors.right: parent.right
                spacing: 7
                Repeater {
                    model: [
                        { l: "Browsers",    t: "browser" },
                        { l: "Editors",     t: "editor" },
                        { l: "Graphics",    t: "graphics" },
                        { l: "Audio",       t: "audio" },
                        { l: "Games",       t: "game" },
                        { l: "Development", t: "development" },
                        { l: "System",      t: "system" }
                    ]
                    Rectangle {
                        height: 26; radius: 13
                        width: chl.implicitWidth + 26
                        property bool sel: win.activeCat === modelData.l
                        border.color: sel ? m.gilt0 : m.gilt1; border.width: 1
                        color: sel ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.30) : Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.10)
                        Text { id: chl; anchors.centerIn: parent; text: modelData.l
                               color: sel ? m.gilt5 : m.gilt3; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontMedium : ncde.fontSize_md); font.bold: sel
                               font.letterSpacing: ncde.letterSpacing
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim }
                        HoverHandler { cursorShape: Qt.PointingHandCursor }
                        TapHandler { onTapped: { win.activeCat = modelData.l; searchField.text = ""; pkgMgr.search(modelData.t) } }
                    }
                }
            }

            // cover flow + detail
            Row {
                anchors.top: chips.bottom; anchors.topMargin: 14
                anchors.left: parent.left; anchors.right: parent.right
                anchors.bottom: parent.bottom
                spacing: 18

                // COVER FLOW
                Item {
                    id: flowArea
                    width: parent.width - 304
                    height: parent.height

                    // Frosted Tiffany glass scrim over the carousel band (theatrical stage shows through)
                    Canvas {
                        id: cfScrim
                        anchors.fill: parent
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

                    PathView {
                        id: coverFlow
                        anchors.fill: parent
                        focus: visible
                        model: pkgMgr.results
                        pathItemCount: Math.min(7, pkgMgr.results.length)
                        preferredHighlightBegin: 0.5
                        preferredHighlightEnd: 0.5
                        highlightRangeMode: PathView.StrictlyEnforceRange
                        snapMode: PathView.SnapOneItem
                        highlightMoveDuration: 700
                        interactive:           false
                        clip: true
                        onCurrentIndexChanged: win.liftedIndex = -1

                        path: Path {
                            startX: coverFlow.width * 0.30; startY: coverFlow.height * 0.40
                            PathAttribute { name: "iScale";   value: 0.40 }
                            PathAttribute { name: "iAngle";   value: 55 }
                            PathAttribute { name: "iZ";       value: 0 }
                            PathAttribute { name: "iOpacity"; value: 0.40 }
                            PathLine { x: coverFlow.width * 0.43; y: coverFlow.height * 0.40 }
                            PathPercent { value: 0.42 }
                            PathAttribute { name: "iScale";   value: 0.84 }
                            PathAttribute { name: "iAngle";   value: 55 }
                            PathAttribute { name: "iZ";       value: 1 }
                            PathAttribute { name: "iOpacity"; value: 0.80 }
                            PathLine { x: coverFlow.width * 0.50; y: coverFlow.height * 0.40 }
                            PathPercent { value: 0.50 }
                            PathAttribute { name: "iScale";   value: 1.0 }
                            PathAttribute { name: "iAngle";   value: 0 }
                            PathAttribute { name: "iZ";       value: 10 }
                            PathAttribute { name: "iOpacity"; value: 1.0 }
                            PathLine { x: coverFlow.width * 0.57; y: coverFlow.height * 0.40 }
                            PathPercent { value: 0.58 }
                            PathAttribute { name: "iScale";   value: 0.84 }
                            PathAttribute { name: "iAngle";   value: -55 }
                            PathAttribute { name: "iZ";       value: 1 }
                            PathAttribute { name: "iOpacity"; value: 0.80 }
                            PathLine { x: coverFlow.width * 0.70; y: coverFlow.height * 0.40 }
                            PathAttribute { name: "iScale";   value: 0.40 }
                            PathAttribute { name: "iAngle";   value: -55 }
                            PathAttribute { name: "iZ";       value: 0 }
                            PathAttribute { name: "iOpacity"; value: 0.40 }
                        }

                        delegate: Item {
                            id: cov
                            width: 168; height: 222
                            property bool isCurrent: PathView.isCurrentItem
                            property bool isLifted: win.liftedIndex === index
                            scale:   PathView.iScale === undefined ? 0.84 : PathView.iScale
                            z:       isLifted ? 50 : (PathView.iZ === undefined ? 0 : PathView.iZ)
                            opacity: PathView.iOpacity === undefined ? 0.72 : PathView.iOpacity
                            transform: Rotation {
                                origin.x: cov.width / 2; origin.y: cov.height / 2
                                axis { x: 0; y: 1; z: 0 }
                                angle: PathView.iAngle === undefined ? 0 : PathView.iAngle
                            }
                            // Tiffany jewel glow behind the active cover
                            Canvas {
                                id: covGlow
                                x: -48; y: -48
                                width: parent.width + 96; height: parent.height + 96
                                z: -1
                                renderStrategy: Canvas.Cooperative
                                layer.enabled: true
                                opacity: cov.PathView.isCurrentItem ? 1.0 : 0.0
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
                            // Inner card: lift scale/y live here, NOT on the delegate root
                            // (PathView drives delegate scale via iScale — Behavior there would lag)
                            Item {
                                id: covCard
                                anchors.fill: parent
                                scale: cov.isLifted ? 1.30 : 1.0
                                y:     cov.isLifted ? -12  : 0
                                Behavior on scale { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                                Behavior on y     { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                                AppFrame { anchors.fill: parent }
                                MuchaAppIcon {
                                    appName: modelData.name || ""
                                    appIcon: modelData.name || ""
                                    size: 90
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    y: 18
                                }
                                Text {
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    y: parent.height*0.50
                                    text: (modelData.repo || "").toUpperCase()
                                    color: m.gilt2; font.family: m.display; font.pixelSize: k.fs(9); font.letterSpacing: 2
                                }
                                Text {
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    width: parent.width - 28
                                    y: parent.height*0.74
                                    text: modelData.name || ""
                                    color: m.ink; font.family: m.serif; font.bold: true
                                    font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                                    horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight
                                    style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                                    styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                                }
                                Text {
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    width: parent.width - 28
                                    y: parent.height*0.84
                                    text: modelData.version || ""
                                    color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(10)
                                    horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight
                                }
                                HoverHandler { cursorShape: Qt.PointingHandCursor }
                                TapHandler {
                                    gesturePolicy: TapHandler.WithinBounds
                                    grabPermissions: PointerHandler.CanTakeOverFromHandlersOfSameType
                                    onTapped: {
                                        console.log("CMD onTapped tapCount=" + tapCount + " index=" + index)
                                        if (tapCount >= 2) {
                                            stepDelay.stop(); stepDelay.dir = 0
                                            win.liftedIndex = index
                                            return
                                        }
                                        if (index === coverFlow.currentIndex) return
                                        stepDelay.dir = (cov.x + cov.width/2 < coverFlow.width/2) ? -1 : 1
                                        stepDelay.restart()
                                    }
                                }
                            }
                            // CoverFlow: separator + ShaderEffectSource reflection (gradient-fade; no GraphicalEffects)
                            Rectangle {
                                width: parent.width; height: 1
                                y: parent.height + 1
                                color: Qt.rgba(1, 1, 1, 0.18)
                            }
                            Item {
                                width: parent.width; height: 95
                                y: parent.height + 3
                                clip: true
                                ShaderEffectSource {
                                    width: parent.width
                                    height: cov.height
                                    y: -(cov.height - parent.height)
                                    sourceItem: cov
                                    hideSource: false
                                    // NCDE Command is a standalone process — the shared animPolicy
                                    // singleton only exists in the LaPivot desktop shell's engine, so
                                    // it's never registered here (same guard convention as
                                    // controls/NCDERadio.qml). Idle-based throttling of this reflection
                                    // isn't available in this process; always-live is the honest fallback.
                                    live: !(typeof animPolicy !== "undefined" && animPolicy.screenIdle)
                                    transform: Scale { yScale: -1; origin.y: cov.height / 2 }
                                    opacity: 0.5
                                    layer.enabled: true
                                }
                                Rectangle {
                                    anchors.fill: parent
                                    gradient: Gradient {
                                        GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0.0) }
                                        GradientStop { position: 1.0; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 1.0) }
                                    }
                                }
                            }
                        }

                        // Arms a single deliberate step; held until the double-click window
                        // passes so the first tap of a double-click never moves the carousel
                        Timer {
                            id: stepDelay
                            interval: Qt.styleHints.mouseDoubleClickInterval
                            repeat: false
                            property int dir: 0
                            onTriggered: {
                                if (dir < 0) coverFlow.decrementCurrentIndex()
                                else if (dir > 0) coverFlow.incrementCurrentIndex()
                                dir = 0
                            }
                        }
                        Timer { id: wheelCooldown; interval: 350; repeat: false }
                        WheelHandler {
                            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                            onWheel: function(ev) {
                                if (wheelCooldown.running) return
                                if (ev.angleDelta.y < 0 || ev.angleDelta.x < 0) coverFlow.incrementCurrentIndex()
                                else coverFlow.decrementCurrentIndex()
                                wheelCooldown.restart()
                            }
                        }
                        Keys.onLeftPressed: decrementCurrentIndex()
                        Keys.onRightPressed: incrementCurrentIndex()
                    }

                    // empty state
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        visible: pkgMgr.results.length === 0
                        Floret { width: 40; height: 40; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { anchors.horizontalCenter: parent.horizontalCenter
                               text: "Search the Repertoire"
                               color: m.gilt4; font.family: m.display; font.bold: true; font.pixelSize: k.fs(20); font.letterSpacing: 2 }
                        Text { anchors.horizontalCenter: parent.horizontalCenter
                               text: "Choose a category above, or type a name and press Enter."
                               color: m.gilt2; font.family: m.serif; font.italic: true
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim }
                    }

                    // flow hint
                    Text {
                        anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
                        visible: pkgMgr.results.length > 1
                        text: "‹ click to flip · double-click to select · scroll · ← → ›"
                        color: m.gilt2; font.family: m.serif; font.italic: true
                        font.pixelSize: (theme ? theme.fontMedium : ncde.fontSize_md); font.letterSpacing: ncde.letterSpacing
                        style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                        styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                    }
                }

                // DETAIL — portrait frame
                Item {
                    width: 286
                    height: parent.height
                    // When a cover is lifted, show that package; otherwise track the carousel centre
                    property int _selIdx: win.liftedIndex >= 0 ? win.liftedIndex : coverFlow.currentIndex
                    property var sel: (pkgMgr.results.length > 0 && _selIdx >= 0
                                       && _selIdx < pkgMgr.results.length)
                                      ? pkgMgr.results[_selIdx] : null

                    PortraitFrame { anchors.fill: parent }

                    Column {
                        visible: parent.sel !== null
                        anchors.top: parent.top; anchors.topMargin: parent.width*0.30
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.leftMargin: 26; anchors.rightMargin: 26
                        spacing: 8

                        Text {
                            width: parent.width
                            text: parent.parent.sel ? parent.parent.sel.name : ""
                            color: m.wine2; font.family: m.display; font.bold: true; font.pixelSize: k.fs(22)
                            horizontalAlignment: Text.AlignHCenter; wrapMode: Text.WordWrap
                        }
                        Rectangle { width: parent.width*0.5; height: 1; color: m.gilt2; anchors.horizontalCenter: parent.horizontalCenter }
                        Row {
                            anchors.horizontalCenter: parent.horizontalCenter; spacing: 8
                            Rectangle {
                                height: 20; radius: 10; width: rp.implicitWidth + 18
                                color: Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.22); border.color: m.gilt2; border.width: 1
                                Text { id: rp; anchors.centerIn: parent
                                       text: parent.parent.parent.parent.sel ? (parent.parent.parent.parent.sel.repo || "") : ""
                                       color: m.gilt0; font.family: m.display; font.pixelSize: k.fs(10); font.letterSpacing: 1 }
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: parent.parent.parent.sel ? (parent.parent.parent.sel.version || "") : ""
                                color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(12)
                            }
                        }
                        Text {
                            width: parent.width
                            text: parent.parent.sel ? (parent.parent.sel.desc || "No description available.") : ""
                            color: m.ink; font.family: m.serif
                            font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                            wrapMode: Text.WordWrap; horizontalAlignment: Text.AlignHCenter
                            maximumLineCount: 6; elide: Text.ElideRight
                            style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                            styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                        }
                    }

                    // install button anchored near base of the frame
                    GiltButton {
                        visible: parent.sel !== null
                        anchors.bottom: parent.bottom; anchors.bottomMargin: 26
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 168; height: 36
                        text: pkgMgr.busy ? "WORKING…" : "INSTALL"
                        kind: "wine"
                        lit: win.liftedIndex >= 0
                        enabledState: !pkgMgr.busy && parent.sel !== null
                        onClicked: {
                            if (parent.sel) {
                                pkgMgr.installPackage(parent.sel.name)
                                win.liftedIndex = -1
                            }
                        }
                    }
                }
            }
        }

        // ─────────────────────────────────────────────────────────────
        //  TAB 1 — INSTALLED
        // ─────────────────────────────────────────────────────────────
        Item {
            anchors.fill: parent
            visible: win.currentTab === 1

            Rectangle {
                id: instFilter
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 36; radius: 18
                border.color: m.gilt0; border.width: 2
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.paper1 }
                    GradientStop { position: 1; color: m.paper2 }
                }
                TextInput {
                    id: instFilterField
                    anchors.left: parent.left; anchors.leftMargin: 18
                    anchors.right: parent.right; anchors.rightMargin: 120
                    anchors.verticalCenter: parent.verticalCenter
                    color: m.wine2; font.family: m.serif; font.pixelSize: k.fs(17); clip: true; selectByMouse: true
                    onAccepted: pkgMgr.getInstalled(text.trim())
                    Text {
                        anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                        text: "Filter installed packages…"; color: m.gilt1
                        font.family: m.serif; font.italic: true
                        font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                        visible: !instFilterField.text && !instFilterField.activeFocus
                        style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                        styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                    }
                }
                Text {
                    anchors.right: parent.right; anchors.rightMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                    text: pkgMgr.installed.length + " installed"
                    color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(12)
                }
            }

            Rectangle {
                anchors.top: instFilter.bottom; anchors.topMargin: 10
                anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
                radius: 6; color: Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.10)
                border.color: m.gilt1; border.width: 1
                ListView {
                    anchors.fill: parent; anchors.margins: 6
                    clip: true; spacing: 4
                    model: pkgMgr.installed
                    ScrollBar.vertical: NCDEScrollBar {}
                    delegate: Rectangle {
                        width: ListView.view ? ListView.view.width : 0
                        height: 40; radius: 5
                        color: rh.hovered ? Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.5) : Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.28)
                        border.color: m.gilt1; border.width: 1
                        HoverHandler { id: rh }
                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 14
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.name; color: m.wine2
                            font.family: m.serif; font.bold: true
                            font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                            style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                            styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                        }
                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 14
                            anchors.bottom: parent.bottom; anchors.bottomMargin: 3
                            text: modelData.version; color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(10)
                            visible: false
                        }
                        Text {
                            anchors.right: rmBtn.left; anchors.rightMargin: 14
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.version; color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(12)
                        }
                        GiltButton {
                            id: rmBtn
                            anchors.right: parent.right; anchors.rightMargin: 8
                            anchors.verticalCenter: parent.verticalCenter
                            width: 90; height: 28; text: "REMOVE"; kind: "ghost"
                            enabledState: !pkgMgr.busy
                            onClicked: pkgMgr.removePackage(modelData.name)
                        }
                    }
                }
            }
        }

        // ─────────────────────────────────────────────────────────────
        //  TAB 2 — UPDATES
        // ─────────────────────────────────────────────────────────────
        Item {
            anchors.fill: parent
            visible: win.currentTab === 2

            Item {
                id: updHead
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                height: 40
                Text {
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    text: pkgMgr.updateCount > 0
                          ? (pkgMgr.updateCount + " update" + (pkgMgr.updateCount === 1 ? "" : "s") + " available")
                          : "Everything is up to date"
                    color: m.gilt4; font.family: m.display; font.bold: true; font.pixelSize: k.fs(18); font.letterSpacing: 1
                }
                GiltButton {
                    anchors.right: refreshBtn.left; anchors.rightMargin: 8
                    anchors.verticalCenter: parent.verticalCenter
                    height: 32; text: pkgMgr.busy ? "WORKING…" : "UPDATE ALL"; kind: "wine"
                    enabledState: !pkgMgr.busy && pkgMgr.updateCount > 0
                    onClicked: pkgMgr.updateAll()
                }
                GiltButton {
                    id: refreshBtn
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    height: 32; text: "REFRESH"; kind: "ghost"
                    enabledState: !pkgMgr.busy
                    onClicked: pkgMgr.checkUpdates()
                }
            }

            Rectangle {
                anchors.top: updHead.bottom; anchors.topMargin: 10
                anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
                radius: 6; color: Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.10)
                border.color: m.gilt1; border.width: 1

                ListView {
                    anchors.fill: parent; anchors.margins: 6
                    clip: true; spacing: 4
                    model: pkgMgr.updates
                    ScrollBar.vertical: NCDEScrollBar {}
                    delegate: Rectangle {
                        width: ListView.view ? ListView.view.width : 0
                        height: 44; radius: 5
                        color: Qt.rgba(k.gilt5.r, k.gilt5.g, k.gilt5.b, 0.32)
                        border.color: m.gilt1; border.width: 1
                        Text {
                            anchors.left: parent.left; anchors.leftMargin: 14
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData.name; color: m.wine2
                            font.family: m.serif; font.bold: true
                            font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                            width: parent.width*0.4; elide: Text.ElideRight
                            style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                            styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                        }
                        Row {
                            anchors.right: updBtn.left; anchors.rightMargin: 14
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 8
                            Text { text: modelData.oldVersion; color: m.gilt1; font.family: m.mono; font.pixelSize: k.fs(12)
                                   anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "→"; color: m.gilt3; font.pixelSize: k.fs(14); anchors.verticalCenter: parent.verticalCenter }
                            Text { text: modelData.newVersion; color: m.wine3; font.family: m.mono; font.pixelSize: k.fs(12); font.bold: true
                                   anchors.verticalCenter: parent.verticalCenter }
                        }
                        GiltButton {
                            id: updBtn
                            anchors.right: parent.right; anchors.rightMargin: 8
                            anchors.verticalCenter: parent.verticalCenter
                            width: 92; height: 28; text: "UPDATE"
                            enabledState: !pkgMgr.busy
                            // 2026-09-26: installPackage() is "pacman -S <pkg>" with no -y, so it
                            // reinstalled the version from the stale local list while checkUpdates
                            // (a fresh list) kept offering the new one — update, reappear, forever.
                            // Arch has no single-package update: every row runs the full -Syu.
                            onClicked: pkgMgr.updateAll()
                        }
                    }
                }
                // up-to-date crest
                Column {
                    anchors.centerIn: parent; spacing: 10
                    visible: pkgMgr.updates.length === 0
                    Floret { width: 44; height: 44; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { anchors.horizontalCenter: parent.horizontalCenter
                           text: "All current"; color: m.gilt4
                           font.family: m.display; font.bold: true; font.pixelSize: k.fs(20); font.letterSpacing: 2 }
                }
            }
        }

        // ─────────────────────────────────────────────────────────────
        //  TAB 3 — OPERATING MANUAL
        // ─────────────────────────────────────────────────────────────
        Item {
            anchors.fill: parent
            visible: win.currentTab === 3

            Rectangle {
                anchors.fill: parent; radius: 8
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.paper1 }
                    GradientStop { position: 1; color: m.paper3 }
                }
                border.color: m.gilt1; border.width: 1

                Flickable {
                    anchors.fill: parent; anchors.margins: 24
                    contentHeight: manualCol.height; clip: true
                    ScrollBar.vertical: NCDEScrollBar {}

                    Column {
                        id: manualCol
                        width: parent.width; spacing: 14

                        SectionRule { width: parent.width; text: "OPERATING MANUAL" }

                        Row {
                            spacing: 14; width: parent.width
                            Text {
                                text: "N"; color: m.wine3; font.family: m.display; font.bold: true
                                font.pixelSize: k.fs(64); style: Text.Raised; styleColor: m.gilt4
                            }
                            Text {
                                width: parent.width - 80
                                text: "I am Lord Nigel -- and you have found NCDE Command, the most magnificently "
                                    + "appointed software installation facility on the known desktop. We draw from the "
                                    + "Arch repositories through pacman, dressed in the house Mucha livery. Browse the "
                                    + "catalogue in Cover Flow, attend to your Installed company, and keep every "
                                    + "dispatch current from the Updates ledger. My wife, Lady Lucrezia, tends "
                                    + "La Fonderie -- the type foundry within. One does not choose one's fonts "
                                    + "without consulting her first. I learned this the hard way."
                                color: m.ink; font.family: m.serif
                                font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                                wrapMode: Text.WordWrap
                                style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                                styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                            }
                        }

                        SectionRule { width: parent.width; text: "BROWSE" }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Select a category from the rail above -- Browsers, Editors, Multimedia, the lot -- "
                                   + "or type the name of your quarry directly into the search field and press Enter. "
                                   + "The Cover Flow presents your candidates as framed theatrical portraits. Drag it, "
                                   + "scroll it, or use the arrow keys as one would a lantern through dense undergrowth. "
                                   + "The selected specimen appears in full detail on the right. Press INSTALL to bring "
                                   + "it back from the field. I have personally catalogued over forty thousand packages. "
                                   + "Not all of them are worth installing, but I record them nonetheless." }

                        SectionRule { width: parent.width; text: "INSTALLED" }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Every program currently resident on this machine is catalogued here, with its version "
                                   + "and precise revision. Filter by name if the expedition log runs long -- and it will, "
                                   + "if one has been thorough about bringing things home from the field. REMOVE dismisses "
                                   + "the package from the premises. It will not be given a reference. "
                                   + "It will not be invited back for the season." }

                        SectionRule { width: parent.width; text: "UPDATES" }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Dispatches from the frontier -- outstanding upgrades arrayed old to new. "
                                   + "UPDATE ALL performs a full pacman -Syu: everything, simultaneously, without "
                                   + "further discussion. I recommend it. One does not dally on the veldt. "
                                   + "A single package may be upgraded individually if the expedition requires "
                                   + "a more targeted approach. REFRESH re-reads the ledger should one suspect it "
                                   + "has fallen behind -- which one frequently should." }

                        SectionRule { width: parent.width; text: "A NOTE ON PRIVILEGE" }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Installs, removals, and updates pass through pkexec. Before any change is made, "
                                   + "the footman will appear at the door requesting your authorisation. This is not "
                                   + "optional. One simply does not alter the grounds without the master's signature. "
                                   + "The prompter's box at the foot of the screen narrates each operation as it proceeds. "
                                   + "Lord Nigel considers this transparency entirely in keeping with the best traditions "
                                   + "of the house." }

                        Item { width: parent.width; height: 8 }

                        SectionRule { width: parent.width; text: "LA FONDERIE" }
                        Text { width: parent.width; color: m.wine3; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               font.italic: true; wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Lady Lucrezia speaking." }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "La Fonderie is my domain -- Tab four, if you have been paying attention -- and I "
                                   + "shall thank you to enter it with the appropriate degree of reverence. I maintain "
                                   + "the type foundry within NCDE Command. Every available typeface is presented in its "
                                   + "own hand, precisely as it will appear on your screen. Browse by name. Browse by "
                                   + "style. Take your time. A font chosen in haste is a font one lives to regret. "
                                   + "I have seen it happen. I was not sympathetic." }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "To install a typeface, tap INSTALL. To remove one that has disappointed you -- "
                                   + "and they do disappoint -- tap REMOVE. The font cache is rebuilt automatically "
                                   + "after every change. Your applications will see the new face at once. There is "
                                   + "no need to restart anything. I have arranged it so, because Lord Nigel would "
                                   + "forget entirely and then blame the machine." }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "A word on selection, since I can see you are going to need it: a typeface is "
                                   + "a declaration of character. The serif families are, as a rule, distinguished. "
                                   + "The sans-serifs are perfectly acceptable for everyday use, though one ought "
                                   + "not to make a habit of them in formal correspondence. As for decorative display "
                                   + "fonts -- I maintain a private register of acceptable choices. What is NOT on "
                                   + "that register does not bear mentioning in polite company. You know what you did." }
                        SectionRule { width: parent.width; text: "SCRIPTORIUM DEI" }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "The Scriptorium Dei is a separate matter entirely -- reserved for Biblical, "
                                   + "classical, and academic typefaces. Polytonic Greek from Gentium, Cardo, and the "
                                   + "Greek Font Society. Biblical Hebrew from the Society of Biblical Literature and "
                                   + "Ezra SIL. Coptic, Syriac, cuneiform, medieval Latin, Old Church Slavonic, and "
                                   + "the full phonetic repertoire of the International Phonetic Alphabet. Scholars, "
                                   + "clergy, and those who work with sacred texts have long required faces that honour "
                                   + "the precision of the original tongues. I have arranged them here so you need not "
                                   + "hunt across six repositories in the small hours. Install one and it is available "
                                   + "immediately to every application on the machine. One does not set the Septuagint "
                                   + "in Arial. I have strong opinions about this. They are correct." }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Gentium Plus covers the full polytonic Greek range -- breathings, iota subscripts, "
                                   + "circumflexes -- that the Septuagint and the Church Fathers require without "
                                   + "improvisation. Cardo, from the University of Pennsylvania, handles classical Latin "
                                   + "and Greek with the authority of scholarship. The Greek Font Society issues the "
                                   + "typefaces of the Greek National Library -- Gazis, Theano Didot, Apollonia. They are "
                                   + "not decorative. For Hebrew, the SBL Hebrew face sets the full Tiberian pointing "
                                   + "system and cantillation marks precisely. Ezra SIL extends the repertoire to rarer "
                                   + "traditions. Doulos SIL covers the International Phonetic Alphabet with the precision "
                                   + "the field demands. Junicode is the standard for medieval Latin manuscript study. "
                                   + "Charis SIL addresses the full global academic phonetic inventory. I maintain this "
                                   + "list. It is not exhaustive -- nothing involving Syriac ever is -- but it is a "
                                   + "proper beginning." }
                        Text { width: parent.width; color: m.ink; font.family: m.serif
                               font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                               wrapMode: Text.WordWrap
                               style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                               styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim
                               text: "Clergy, cantor, sacristan, lecturer, graduate student -- install what is needed. "
                                   + "Each face becomes available to every application the instant it is placed. There "
                                   + "is no restart, no cache to clear by hand, no step in between. Lord Nigel once "
                                   + "asked whether all of this was strictly necessary. I reminded him that the Psalms "
                                   + "have survived three thousand years in part because someone cared how they were set. "
                                   + "He did not ask again. One installs the correct face. One does not apologise for it." }

                        Item { width: parent.width; height: 12 }
                    }
                }
            }
        }

        // ─────────────────────────────────────────────────────────────
        //  TAB 4 — FONTS (La Fonderie)
        // ─────────────────────────────────────────────────────────────
        FonderieTab {
            anchors.fill: parent
            visible: win.currentTab === 4
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  CELESTIAL STATUS BAR — star=idle · sun=working · moon=complete
    // ════════════════════════════════════════════════════════════════════
    Rectangle {
        id: prompterBox
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        height: 50
        color: ncde.background

        // ── state ────────────────────────────────────────────────────────
        property string phase: showMoon ? "moon" : (pkgMgr.busy ? "sun" : "star")
        property bool   showMoon: false
        property string narration: ""
        property string doneMessage: ""

        // ── authorisation state ──────────────────────────────────────────────
        property bool   authActive: false
        property string authOp: ""
        property bool   authError: false
        property int    authTriesLeft: 3
        property real   shakeX: 0

        signal passwordEntered(string pw)
        signal cancelled()

        function beginAuth(op) {
            authOp = op; authError = false; authActive = true;
            pwInput.text = "";
            Qt.callLater(function() { pwInput.forceActiveFocus(); });
        }
        function rejectAuth(triesLeft) {
            authError = true; authTriesLeft = triesLeft;
            pwInput.text = ""; pwInput.forceActiveFocus(); shakeAnim.restart();
        }
        function endAuth() {
            authActive = false; authError = false;
            pwInput.text = ""; revealBtn.revealed = false;
        }

        SequentialAnimation {
            id: shakeAnim
            NumberAnimation { target: prompterBox; property: "shakeX"; to: -5; duration: 50 }
            NumberAnimation { target: prompterBox; property: "shakeX"; to:  5; duration: 50 }
            NumberAnimation { target: prompterBox; property: "shakeX"; to: -4; duration: 50 }
            NumberAnimation { target: prompterBox; property: "shakeX"; to:  4; duration: 50 }
            NumberAnimation { target: prompterBox; property: "shakeX"; to:  0; duration: 50 }
        }

        // blend weights (eased each tick) + animation phases
        property real wStar: 1; property real wSun: 0; property real wMoon: 0
        property real spin: 0          // sun ray / ring rotation
        property real twinkle: 0       // star shimmer clock
        property real shootLife: 0; property real shootX: 0; property real shootY: 0
        // eased sky colour channels
        property real skyTop0: 13; property real skyTop1: 9;  property real skyTop2: 19
        property real skyHor0: 42; property real skyHor1: 14; property real skyHor2: 34

        Timer {
            id: moonTimer; interval: 4200; repeat: false
            onTriggered: prompterBox.showMoon = false
        }

        // ── the night sky (tint + stars + rare shooting star) ────────────
        Canvas {
            id: skyCanvas; anchors.fill: parent
            renderStrategy: Canvas.Cooperative; layer.enabled: true
            property var starsX: []; property var starsY: []; property var starsR: []; property var starsP: []
            Component.onCompleted: {
                for (var i = 0; i < 22; i++) {
                    starsX.push(Math.random()); starsY.push(Math.random()*0.7);
                    starsR.push(Math.random()*0.9+0.3); starsP.push(Math.random()*6.28);
                }
                requestPaint();
            }
            onPaint: {
                var ctx = getContext("2d"); ctx.reset();
                var w = width, h = height;
                var g = ctx.createLinearGradient(0,0,0,h);
                g.addColorStop(0, Qt.rgba(prompterBox.skyTop0/255, prompterBox.skyTop1/255, prompterBox.skyTop2/255, 1));
                g.addColorStop(1, Qt.rgba(prompterBox.skyHor0/255, prompterBox.skyHor1/255, prompterBox.skyHor2/255, 1));
                ctx.fillStyle = g; ctx.fillRect(0,0,w,h);
                var day = prompterBox.phase === "sun" ? 1 : (prompterBox.phase === "moon" ? 0.4 : 0.15);
                var hg = ctx.createLinearGradient(0,h*0.5,0,h);
                hg.addColorStop(0,"rgba(233,201,124,0)");
                hg.addColorStop(1,"rgba(233,201,124," + (0.06+0.18*day) + ")");
                ctx.fillStyle = hg; ctx.fillRect(0,h*0.5,w,h*0.5);
                var starA = prompterBox.phase === "star" ? 0.85 : (prompterBox.phase === "moon" ? 0.6 : 0.1);
                if (starA > 0.04) {
                    for (var i = 0; i < starsX.length; i++) {
                        var tw = 0.5 + 0.5*Math.sin(prompterBox.twinkle + starsP[i]);
                        ctx.globalAlpha = starA*tw*0.85; ctx.fillStyle = k.gilt5;
                        ctx.beginPath(); ctx.arc(starsX[i]*w, starsY[i]*h, starsR[i], 0, 6.28); ctx.fill();
                    }
                    ctx.globalAlpha = 1;
                }
                if (prompterBox.shootLife > 0) {
                    var sxp = prompterBox.shootX*w, syp = prompterBox.shootY*h, len = 46;
                    var a = Math.sin(prompterBox.shootLife*Math.PI);
                    var sg = ctx.createLinearGradient(sxp,syp,sxp-len,syp-len*0.5);
                    sg.addColorStop(0,"rgba(246,227,176," + a + ")"); sg.addColorStop(1,"rgba(246,227,176,0)");
                    ctx.strokeStyle = sg; ctx.lineWidth = 1.4; ctx.lineCap = "round";
                    ctx.beginPath(); ctx.moveTo(sxp,syp);
                    ctx.lineTo(sxp-len*(1-prompterBox.shootLife), syp-len*0.5*(1-prompterBox.shootLife)); ctx.stroke();
                }
            }
        }

        // gold Art Nouveau rules top & bottom
        Rectangle { anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right; height: 2
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.12; color: m.gilt1 }
                GradientStop { position: 0.5;  color: m.gilt3 }
                GradientStop { position: 0.88; color: m.gilt1 }
                GradientStop { position: 1.0;  color: "transparent" } } }
        Rectangle { anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right; height: 2; opacity: 0.85
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.12; color: m.gilt1 }
                GradientStop { position: 0.5;  color: m.gilt3 }
                GradientStop { position: 0.88; color: m.gilt1 }
                GradientStop { position: 1.0;  color: "transparent" } } }

        // edge scrims for text legibility over the noon sky
        Rectangle { anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom; width: 150
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop { position: 0; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.72) }
                GradientStop { position: 1; color: "transparent" } } }
        Rectangle { anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: parent.bottom; width: 160
            gradient: Gradient { orientation: Gradient.Horizontal
                GradientStop { position: 0; color: "transparent" }
                GradientStop { position: 1; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.78) } } }

        // ── celestial medallion ─────────────────────────────────────────
        Canvas {
            id: emblemCanvas
            width: 44; height: 44
            anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter
            renderStrategy: Canvas.Cooperative; layer.enabled: true
            opacity: (prompterBox.authActive && !(pkgMgr.authChecking || fontMgr.authChecking)) ? 0 : 1
            Behavior on opacity { NumberAnimation { duration: 380; easing.type: Easing.OutCubic } }
            onPaint: {
                var ctx = getContext("2d"); ctx.reset();
                var cx = width/2, cy = height/2, R = 8, t = prompterBox.spin;
                // ----- star -----
                if (prompterBox.wStar > 0.01) {
                    ctx.save(); ctx.globalAlpha = prompterBox.wStar; ctx.translate(cx,cy);
                    var tw = 0.85 + 0.15*Math.sin(prompterBox.twinkle);
                    var hg = ctx.createRadialGradient(0,0,0,0,0,R*2.4);
                    hg.addColorStop(0,"rgba(246,227,176," + (0.5*tw) + ")"); hg.addColorStop(1,"rgba(246,227,176,0)");
                    ctx.fillStyle = hg; ctx.beginPath(); ctx.arc(0,0,R*2.4,0,6.28); ctx.fill();
                    ctx.rotate(t*0.45); ctx.fillStyle = k.gilt5;
                    for (var s = 0; s < 2; s++) {
                        ctx.save();
                        if (s===1){ ctx.rotate(0.785); ctx.scale(0.6,0.6); ctx.globalAlpha = prompterBox.wStar*0.6; }
                        ctx.beginPath();
                        ctx.moveTo(0,-R*1.5); ctx.quadraticCurveTo(R*0.16,-R*0.16,R*0.5,0);
                        ctx.quadraticCurveTo(R*0.16,R*0.16,0,R*1.5);
                        ctx.quadraticCurveTo(-R*0.16,R*0.16,-R*0.5,0);
                        ctx.quadraticCurveTo(-R*0.16,-R*0.16,0,-R*1.5); ctx.fill();
                        ctx.restore();
                    }
                    ctx.restore();
                }
                // ----- sun + indeterminate ring -----
                if (prompterBox.wSun > 0.01) {
                    ctx.save(); ctx.globalAlpha = prompterBox.wSun; ctx.translate(cx,cy);
                    var halo = ctx.createRadialGradient(0,0,0,0,0,R*2.6);
                    halo.addColorStop(0,"rgba(246,227,176,0.5)"); halo.addColorStop(0.45,"rgba(233,201,124,0.2)"); halo.addColorStop(1,"rgba(233,201,124,0)");
                    ctx.fillStyle = halo; ctx.beginPath(); ctx.arc(0,0,R*2.6,0,6.28); ctx.fill();
                    ctx.save(); ctx.rotate(t*0.9);
                    ctx.strokeStyle = "rgba(246,227,176,0.9)"; ctx.lineWidth = 1.4; ctx.lineCap = "round";
                    for (var i = 0; i < 12; i++) {
                        var ang = i/12*6.28, r1 = R*1.35, r2 = R*1.9 + (i%2 ? R*0.45 : 0);
                        ctx.beginPath(); ctx.moveTo(Math.cos(ang)*r1, Math.sin(ang)*r1);
                        ctx.lineTo(Math.cos(ang)*r2, Math.sin(ang)*r2); ctx.stroke();
                    }
                    ctx.restore();
                    var d = ctx.createRadialGradient(-R*0.3,-R*0.3,0,0,0,R);
                    d.addColorStop(0,"#fff6df"); d.addColorStop(0.5,k.gilt5); d.addColorStop(1,k.gilt3);
                    ctx.fillStyle = d; ctx.beginPath(); ctx.arc(0,0,R,0,6.28); ctx.fill();
                    ctx.strokeStyle = "rgba(90,58,20,0.7)"; ctx.lineWidth = 1; ctx.stroke();
                    // indeterminate progress ring (quarter arc, rotating)
                    ctx.strokeStyle = "rgba(90,58,20,0.5)"; ctx.lineWidth = 2.4;
                    ctx.beginPath(); ctx.arc(0,0,R*1.55,0,6.28); ctx.stroke();
                    ctx.strokeStyle = k.gilt4; ctx.lineWidth = 2.4; ctx.lineCap = "round";
                    ctx.beginPath(); ctx.arc(0,0,R*1.55, t*1.6, t*1.6 + 1.8); ctx.stroke();
                    ctx.restore();
                }
                // ----- moon -----
                if (prompterBox.wMoon > 0.01) {
                    ctx.save(); ctx.globalAlpha = prompterBox.wMoon; ctx.translate(cx,cy);
                    var mh = ctx.createRadialGradient(0,0,0,0,0,R*2.2);
                    mh.addColorStop(0,"rgba(214,203,168,0.42)"); mh.addColorStop(1,"rgba(214,203,168,0)");
                    ctx.fillStyle = mh; ctx.beginPath(); ctx.arc(0,0,R*2.2,0,6.28); ctx.fill();
                    var md = ctx.createRadialGradient(-R*0.3,-R*0.3,0,0,0,R);
                    md.addColorStop(0,k.surface); md.addColorStop(1,k.gilt2);
                    ctx.fillStyle = md; ctx.beginPath(); ctx.arc(0,0,R,0,6.28); ctx.fill();
                    ctx.save(); ctx.globalCompositeOperation = "source-atop"; ctx.fillStyle = "rgba(13,9,19,0.66)";
                    ctx.beginPath(); ctx.arc(R*0.55,-R*0.15,R*0.96,0,6.28); ctx.fill(); ctx.restore();
                    ctx.strokeStyle = "rgba(90,58,20,0.55)"; ctx.lineWidth = 1;
                    ctx.beginPath(); ctx.arc(0,0,R,0,6.28); ctx.stroke();
                    ctx.restore();
                }
            }
        }

        // ── status word + (state) ───────────────────────────────────────
        Column {
            id: statusCol
            anchors.left: emblemCanvas.right; anchors.leftMargin: 13
            anchors.verticalCenter: parent.verticalCenter; spacing: 0
            opacity: (prompterBox.authActive && !(pkgMgr.authChecking || fontMgr.authChecking)) ? 0 : 1
            Behavior on opacity { NumberAnimation { duration: 380; easing.type: Easing.OutCubic } }
            Text {
                text: prompterBox.phase === "sun"
                        ? (pkgMgr.status && pkgMgr.status.length ? pkgMgr.status : "Working…")
                        : prompterBox.phase === "moon"
                            ? (prompterBox.doneMessage.length ? prompterBox.doneMessage : "Complete")
                            : "Ready"
                color: m.gilt5; font.family: m.display; font.pixelSize: k.fs(12); font.letterSpacing: 1.6
                style: Text.Raised; styleColor: "#000000"
            }
        }

        // ── live narration line (centre) — the rolling pacman detail ─────
        Text {
            id: narrText
            anchors.centerIn: parent
            width: parent.width * 0.42
            visible: prompterBox.phase !== "star" && prompterBox.narration.length > 0
            opacity: (prompterBox.authActive && !(pkgMgr.authChecking || fontMgr.authChecking)) ? 0 : 1
            Behavior on opacity { NumberAnimation { duration: 380; easing.type: Easing.OutCubic } }
            text: "❝ " + prompterBox.narration
            color: m.gilt3; font.family: m.mono; font.pixelSize: k.fs(11)
            elide: Text.ElideRight; horizontalAlignment: Text.AlignHCenter
        }

        // ── readouts (right): installed ◆ · updates ▲ ────────────────────
        Row {
            anchors.right: parent.right; anchors.rightMargin: 18
            anchors.verticalCenter: parent.verticalCenter; spacing: 14
            opacity: prompterBox.authActive ? 0 : 1
            Behavior on opacity { NumberAnimation { duration: 380; easing.type: Easing.OutCubic } }
            Row {
                spacing: 7
                Text { anchors.verticalCenter: parent.verticalCenter; text: "◆"; color: m.gilt2; font.pixelSize: k.fs(11) }
                Text { anchors.verticalCenter: parent.verticalCenter; text: pkgMgr.installed.length
                       color: m.gilt5; font.family: m.mono; font.pixelSize: k.fs(12); font.bold: true }
                Text { anchors.verticalCenter: parent.verticalCenter; text: "INSTALLED"; color: m.gilt2
                       font.family: m.display; font.pixelSize: k.fs(10); font.letterSpacing: 1.4 }
            }
            Rectangle { width: 1; height: 18; color: Qt.rgba(0.69,0.48,0.19,0.4); anchors.verticalCenter: parent.verticalCenter }
            Row {
                spacing: 7; visible: pkgMgr.updateCount > 0
                Text { anchors.verticalCenter: parent.verticalCenter; text: "▲"; color: m.gilt3; font.pixelSize: k.fs(11) }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: Math.max(20, updNum.implicitWidth + 10); height: 17; radius: 9
                    color: m.wine3; border.color: m.gilt4; border.width: 1
                    Text { id: updNum; anchors.centerIn: parent; text: pkgMgr.updateCount
                           color: m.gilt5; font.family: m.mono; font.pixelSize: k.fs(10); font.bold: true }
                }
                Text { anchors.verticalCenter: parent.verticalCenter; text: "UPDATES"; color: m.gilt2
                       font.family: m.display; font.pixelSize: k.fs(10); font.letterSpacing: 1.4 }
            }
        }

        FrameAnimation {
            id: motionPump
            property real elapsed: 0
            running: win.visible && win.motionEnabled
                     && ((win.screenAwake && (win.idleMotionEnabled
                                               || Math.abs(prompterBox.wSun - (prompterBox.phase === "sun" ? 1 : 0)) > 0.01
                                               || prompterBox.shootLife > 0))
                         || pkgMgr.busy || prompterBox.showMoon || prompterBox.authActive)
            onRunningChanged: if (!running) elapsed = 0
            onTriggered: {
                var transitioning = pkgMgr.busy || prompterBox.showMoon || prompterBox.authActive
                                   || Math.abs(prompterBox.wSun - (prompterBox.phase === "sun" ? 1 : 0)) > 0.01
                                   || prompterBox.shootLife > 0
                var interval = (transitioning ? 0.033 : 0.12) * win.motionDurationScale
                elapsed += Math.min(frameTime, 0.25)
                var ticks = Math.min(8, Math.floor(elapsed / interval))
                if (ticks < 1) return
                elapsed -= ticks * interval
                for (var i = 0; i < ticks; ++i) {
                    prompterBox.spin += 0.05
                    prompterBox.twinkle += interval * 3
                    prompterBox.wStar += (((prompterBox.phase === "star") ? 1 : 0) - prompterBox.wStar) * 0.12
                    prompterBox.wSun  += (((prompterBox.phase === "sun")  ? 1 : 0) - prompterBox.wSun) * 0.12
                    prompterBox.wMoon += (((prompterBox.phase === "moon") ? 1 : 0) - prompterBox.wMoon) * 0.12

                    var checking = pkgMgr.authChecking || fontMgr.authChecking
                    var topTargets = (prompterBox.authActive && !checking) ? [36,16,30]
                                  : prompterBox.phase === "sun" ? [40,28,20]
                                  : prompterBox.phase === "moon" ? [20,16,34] : [13,9,19]
                    var horizonTargets = (prompterBox.authActive && !checking) ? [90,22,46]
                                       : prompterBox.phase === "sun" ? [140,86,38]
                                       : prompterBox.phase === "moon" ? [58,30,60] : [42,14,34]
                    prompterBox.skyTop0 += (topTargets[0] - prompterBox.skyTop0) * 0.08
                    prompterBox.skyTop1 += (topTargets[1] - prompterBox.skyTop1) * 0.08
                    prompterBox.skyTop2 += (topTargets[2] - prompterBox.skyTop2) * 0.08
                    prompterBox.skyHor0 += (horizonTargets[0] - prompterBox.skyHor0) * 0.08
                    prompterBox.skyHor1 += (horizonTargets[1] - prompterBox.skyHor1) * 0.08
                    prompterBox.skyHor2 += (horizonTargets[2] - prompterBox.skyHor2) * 0.08

                    if (prompterBox.phase !== "sun") {
                        if (prompterBox.shootLife <= 0 && Math.random() < 0.0016) {
                            prompterBox.shootLife = 1
                            prompterBox.shootX = Math.random() * 0.5 + 0.2
                            prompterBox.shootY = Math.random() * 0.3 + 0.05
                        } else if (prompterBox.shootLife > 0) {
                            prompterBox.shootLife -= 0.022
                        }
                    }
                }
                emblemCanvas.requestPaint()
                skyCanvas.requestPaint()
            }
        }

        Item {
            id: authFace
            x: prompterBox.shakeX; y: 0
            width: parent.width; height: parent.height
            opacity: prompterBox.authActive ? 1 : 0
            visible: prompterBox.authActive || opacity > 0.01
            enabled: prompterBox.authActive
            Behavior on opacity { NumberAnimation { duration: 420; easing.type: Easing.OutCubic } }

            Row {
                id: authLeft
                anchors.left: parent.left; anchors.leftMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                spacing: 9
                opacity: (pkgMgr.authChecking || fontMgr.authChecking) ? 0 : 1
                Behavior on opacity { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "⚿"
                    color: m.gilt4; font.pixelSize: k.fs(15)
                    SequentialAnimation on opacity {
                        running: prompterBox.authActive && win.motionEnabled && win.screenAwake
                        loops: Animation.Infinite
                        NumberAnimation { from: 0.7; to: 1.0; duration: 900; easing.type: Easing.InOutSine }
                        NumberAnimation { from: 1.0; to: 0.7; duration: 900; easing.type: Easing.InOutSine }
                    }
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "AUTHORISE"
                    color: m.gilt3; font.family: m.display; font.pixelSize: k.fs(11); font.letterSpacing: 1.7
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: prompterBox.authOp
                    color: m.gilt5; font.family: m.display; font.pixelSize: k.fs(11); font.letterSpacing: 1.0
                }
            }

            Row {
                id: authRight
                anchors.right: parent.right; anchors.rightMargin: 14
                anchors.verticalCenter: parent.verticalCenter
                spacing: 11
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: prompterBox.authError
                    text: "not accepted — " + prompterBox.authTriesLeft + " left"
                    color: m.wine4; font.family: m.serif; font.italic: true; font.pixelSize: k.fs(13)
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: enterTxt.implicitWidth + 14; height: 19; radius: 5
                    color: enterHover.hovered ? Qt.rgba(1,1,1,0.06) : "transparent"
                    border.color: m.gilt0; border.width: 1
                    opacity: (pkgMgr.authChecking || fontMgr.authChecking) ? 0.35 : 1.0
                    Behavior on color { ColorAnimation { duration: 120 } }
                    Behavior on opacity { NumberAnimation { duration: 160 } }
                    Text {
                        id: enterTxt; anchors.centerIn: parent
                        text: (pkgMgr.authChecking || fontMgr.authChecking) ? "CHECKING…" : "↵ ENTER"; color: m.gilt2
                        font.family: m.display; font.pixelSize: k.fs(9); font.letterSpacing: 1.2
                    }
                    HoverHandler { id: enterHover; cursorShape: Qt.PointingHandCursor }
                    TapHandler {
                        enabled: !(pkgMgr.authChecking || fontMgr.authChecking)
                        onTapped: { if (pwInput.text.length) prompterBox.passwordEntered(pwInput.text) }
                    }
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "✕"; color: dismissHover.hovered ? m.gilt4 : m.gilt2; font.pixelSize: k.fs(14)
                    HoverHandler { id: dismissHover; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: { prompterBox.endAuth(); prompterBox.cancelled(); } }
                }
            }

            Item {
                anchors.left: authLeft.right; anchors.right: authRight.left
                anchors.leftMargin: 14; anchors.rightMargin: 14
                anchors.verticalCenter: parent.verticalCenter
                height: 26
                opacity: (pkgMgr.authChecking || fontMgr.authChecking) ? 0 : 1
                Behavior on opacity { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }

                Rectangle {
                    anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
                    height: 1
                    color: prompterBox.authError ? m.wine4
                           : (pwInput.activeFocus ? m.gilt4 : m.gilt1)
                    Behavior on color { ColorAnimation { duration: 160 } }
                }

                TextInput {
                    id: pwInput
                    anchors.left: parent.left; anchors.right: revealBtn.left; anchors.rightMargin: 8
                    anchors.verticalCenter: parent.verticalCenter
                    color: m.gilt5; font.family: m.mono; font.pixelSize: k.fs(14)
                    selectionColor: m.wine3; selectedTextColor: m.gilt5
                    clip: true
                    echoMode: revealBtn.revealed ? TextInput.Normal : TextInput.Password
                    passwordCharacter: "•"
                    passwordMaskDelay: 0
                    onTextChanged: prompterBox.authError = false
                    onAccepted: if (text.length && !(pkgMgr.authChecking || fontMgr.authChecking)) prompterBox.passwordEntered(text)
                    Keys.onEscapePressed: { prompterBox.endAuth(); prompterBox.cancelled(); }

                    Text {
                        anchors.fill: parent; anchors.leftMargin: 1
                        verticalAlignment: Text.AlignVCenter
                        visible: !pwInput.text && !pwInput.activeFocus
                        text: "administrator password"
                        color: Qt.rgba(0.69,0.48,0.19,0.55)
                        font.family: m.serif; font.italic: true; font.pixelSize: k.fs(14)
                    }
                }

                Text {
                    id: revealBtn
                    property bool revealed: false
                    anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                    text: revealed ? "◠" : "◡"
                    color: revealHover.hovered ? m.gilt4 : m.gilt2; font.pixelSize: k.fs(14)
                    HoverHandler { id: revealHover; cursorShape: Qt.PointingHandCursor }
                    TapHandler { onTapped: { revealBtn.revealed = !revealBtn.revealed; pwInput.forceActiveFocus(); } }
                }
            }
        }
    }


    // ════════════════════════════════════════════════════════════════════
    //  TOAST notification
    // ════════════════════════════════════════════════════════════════════
    Rectangle {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        y: prompterBox.y - height - 14
        width: toastText.implicitWidth + 56; height: 40; radius: 20
        opacity: 0; z: 50
        border.color: m.gilt0; border.width: 2
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop { position: 0; color: m.paper1 }
            GradientStop { position: 1; color: m.paper2 }
        }
        property bool ok: true
        Row {
            anchors.centerIn: parent; spacing: 10
            Rectangle { width: 10; height: 10; radius: 5; anchors.verticalCenter: parent.verticalCenter
                        color: toast.ok ? "#3a7a3a" : m.wine4; border.color: m.gilt0; border.width: 1 }
            Text { id: toastText; anchors.verticalCenter: parent.verticalCenter
                   color: m.wine2; font.family: m.serif; font.bold: true
                   font.pixelSize: (theme ? theme.fontLarge : ncde.fontSize_lg); font.letterSpacing: ncde.letterSpacing
                   style: settings.textOutlineEnabled ? Text.Outline : Text.Normal
                   styleColor: settings.textOutlineColor !== "" ? settings.textOutlineColor : k.inkDim }
        }
        function show(message, success) {
            toastText.text = message; toast.ok = success;
            toastAnim.restart();
        }
        SequentialAnimation {
            id: toastAnim
            NumberAnimation { target: toast; property: "opacity"; to: 1; duration: 220 }
            PauseAnimation { duration: 2600 }
            NumberAnimation { target: toast; property: "opacity"; to: 0; duration: 500 }
        }
    }

    // ════════════════════════════════════════════════════════════════════
    //  WIRING
    // ════════════════════════════════════════════════════════════════════
    Connections {
        target: pkgMgr
        function onAuthRequested(opLabel) { win.activeAuth = "pkg"; prompterBox.beginAuth(opLabel); }
        function onAuthFailed(triesLeft)  { prompterBox.rejectAuth(triesLeft); }
        function onAuthAccepted()         { prompterBox.endAuth(); win.activeAuth = ""; }
        function onOutputLine(line) {
            prompterBox.narration = line;
        }
        function onOperationFinished(success, message) {
            toast.show(message, success);
            prompterBox.doneMessage = message;
            prompterBox.showMoon = true;
            moonTimer.restart();
        }
    }
    Connections {
        target: fontMgr
        function onAuthRequested(opLabel) { win.activeAuth = "font"; prompterBox.beginAuth(opLabel); }
        function onAuthFailed(triesLeft)  { prompterBox.rejectAuth(triesLeft); }
        function onAuthAccepted()         { prompterBox.endAuth(); win.activeAuth = ""; }
        function onOutputLine(line)       { prompterBox.narration = line; }
        function onOperationFinished(success, message) {
            toast.show(message, success);
            prompterBox.doneMessage = message;
            prompterBox.showMoon = true;
            moonTimer.restart();
        }
    }
    Connections {
        target: prompterBox
        function onPasswordEntered(pw) {
            if (win.activeAuth === "font") fontMgr.submitPassword(pw);
            else                           pkgMgr.submitPassword(pw);
        }
        function onCancelled() {
            if (win.activeAuth === "font") fontMgr.abortAuth();
            else                           pkgMgr.abortAuth();
        }
    }
    Component.onCompleted: {
        win.publishGliaMenus();    // GliaTalk global-menu bar (merged into the existing onCompleted)
        pkgMgr.getInstalled();
        pkgMgr.checkUpdates();
        pkgMgr.search("editor");   // seed Browse so the stage opens alive
    }
}