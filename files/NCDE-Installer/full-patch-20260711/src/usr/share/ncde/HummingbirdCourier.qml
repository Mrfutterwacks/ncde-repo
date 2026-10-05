// ╔════════════════════════════════════════════════════════════════════════╗
// ║  HummingbirdCourier.qml — NCDE mail client · Belle Époque "post office"  ║
// ║                                                                          ║
// ║  Standalone window loaded by hummingbird/main.cpp.                       ║
// ║  Context properties (all set before load):                              ║
// ║     mail     — MailEngine  (folders/messages/contacts/current/…)         ║
// ║     ncde     — NCDEEngine  (accent/glow — used for the live accent)      ║
// ║     theme    — ThemeTokens (fontSmall/Medium/Large/fontFamily)           ║
// ║     settings — Settings ·  launcher — Launcher                           ║
// ║                                                                          ║
// ║  Self-contained: all ornament drawn with Canvas. No MouseArea —          ║
// ║  TapHandler / HoverHandler / DragHandler only.                           ║
// ╚════════════════════════════════════════════════════════════════════════╝

import QtQuick
import QtQuick.Window
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Effects
import "hb-stationery.js" as Sta
import NCDE.Courier

Window {
    id: win
    visible: true
    width: 1320
    height: 848
    minimumWidth: 1040
    minimumHeight: 660
    title: "Hummingbird Courier"
    flags: Qt.Window | Qt.FramelessWindowHint
    color: "transparent"

    // ── palette (NCDEKit proxy — responds to dark/light mode) ─────────────
    // Keeping id:m so pal:m passed to HBGallery/HBReadingDesk/HBWritingDesk
    // continues to work; all properties forward through NCDEKit.
    NCDEKit { id: k }
    QtObject {
        id: m
        readonly property color paper0:  k.surfaceHi
        readonly property color paper1:  k.surface
        readonly property color paper2:  k.surface2
        readonly property color paper3:  k.panelBg
        readonly property color panel:   k.surface2
        readonly property color gilt0:   k.gilt0
        readonly property color gilt1:   k.gilt1
        readonly property color gilt2:   k.gilt2
        readonly property color gilt3:   k.gilt3
        readonly property color gilt4:   k.gilt4
        readonly property color gilt5:   k.gilt5
        readonly property color wine1:   k.wine1
        readonly property color wine2:   k.wine2
        readonly property color wine3:   k.wine3
        readonly property color wine4:   k.wine4
        // Dark-mode-safe variants for text/label use (2026-07-14): raw wine2/
        // wine3 are near-black burgundy (#4a0e22/#6e1832) -- fine as an accent
        // against light paper, but measured ~1.2-1.7:1 contrast against the
        // dark surface (#171009), far under WCAG AA's 4.5:1 floor, i.e.
        // genuinely unreadable, not just "a bit dark." Orchidee/NCDEKit never
        // use the wine ramp as text at all -- they route through k.ink, which
        // is already dark/light-adaptive -- so match that instead of trying
        // to lighten wine into something both readable and still recognizably
        // "wine" (measured: needs ~3x lightening to clear AA, which mostly
        // just turns it hot pink). Light mode is untouched.
        readonly property color wineText2: k.dark ? k.ink : wine2
        readonly property color wineText3: k.dark ? k.inkLabel : wine3
        readonly property color verd1:   Qt.darker(k.verd, 2.5)
        readonly property color verd2:   Qt.darker(k.verd, 1.5)
        readonly property color verd3:   k.verd
        readonly property color verd4:   Qt.lighter(k.verd, 1.5)
        readonly property color rose:    k.rose
        readonly property color ink:     k.ink
        readonly property color inkSoft: k.inkSoft
        readonly property color inkLabel: k.inkLabel
        readonly property string display:  k.display
        readonly property string titles:   k.titles
        readonly property string serif:    k.serif
        readonly property string fell:     k.fell
        readonly property string garamond: k.gar
    }

    // fsSmall/fsMed/fsLarge removed 2026-09-23: declared, never referenced anywhere
    // else in this file (grep-confirmed) — dead duplication of theme.fontSmall/
    // Medium/Large, which every actual font.pixelSize call site here reads via k.fs().

    // ── chrome sizing (2026-09-26) ──────────────────────────────────────────
    // Bars, rows and panes grow with the text dial (Script Shift) instead of
    // staying at their 1.0x pixel sizes while the words inside them grow —
    // that is what made titles spill over bars and labels clip at 1.5x.
    readonly property real zs: k.uiScale * k.fontSizeScale
    function px(n) { return Math.round(n * zs) }
    TextMetrics { id: sideMeasure; font.family: m.titles; font.pixelSize: k.fs(13); text: "Operating Manual" }
    readonly property int sideW: Math.max(236, Math.ceil(sideMeasure.advanceWidth) + px(19) + 11 + 60)

    // ── view state ──────────────────────────────────────────────────────────
    property string activeFolder: "inbox"
    property string activeFilter: "all"
    property string activeMsgId: ""
    property string mailPaneView: "gallery"
    property var    selectedIds: ({})
    property int    activeContact: 0
    property string contactFilter: ""
    // Address Book: your Gmail contacts (saved + "Other contacts") when Google is
    // connected, plus anyone the engine knows who isn't among them.
    readonly property var book: {
        var g = link.contacts || [], e = mail.contacts || [];
        if (g.length === 0) return e;
        var seen = {}, out = g.slice();
        for (var i = 0; i < g.length; i++) if (g[i].em) seen[g[i].em.toLowerCase()] = true;
        for (var j = 0; j < e.length; j++)
            if (!e[j].em || !seen[e[j].em.toLowerCase()]) out.push(e[j]);
        return out;
    }
    readonly property var shownBook: {
        var q = contactFilter.trim().toLowerCase();
        if (q === "") return book;
        return book.filter(function(c) {
            return (c.nm || "").toLowerCase().indexOf(q) >= 0 || (c.em || "").toLowerCase().indexOf(q) >= 0
                || (c.tel || "").indexOf(q) >= 0;
        });
    }
    // Folder badge: Gmail's own unread number (kept current by the courier link),
    // the engine's number until the first answer arrives.
    function badge(id, engineCount) {
        var c = link.counts[id];
        return (c && c.unseen !== undefined) ? c.unseen : engineCount;
    }
    // Every change to mail goes through here: the numbers move at once, the way
    // Thunderbird's do, and Gmail's true numbers follow a few seconds later.
    function noteChange(kind, ids) {
        var rows = (mail.messages || []).filter(function(v) { return ids.indexOf(v.id) >= 0 });
        var n = rows.length, u = 0, st = 0;
        for (var i = 0; i < rows.length; i++) { if (rows[i].unread) u++; if (rows[i].flagged) st++; }
        var f = win.activeFolder;
        if (kind === "delete" || kind === "archive" || kind === "spam") {
            link.adjustCount(f, -u, -n);
            if (kind === "delete" && !win.inTrash()) link.adjustCount("trash", u, n);
            if (kind === "spam") link.adjustCount("spam", u, n);
        } else if (kind === "read") {
            link.adjustCount(f, -u, 0);
        } else if (kind === "unread") {
            link.adjustCount(f, n - u, 0);
        }
        link.countsSoon(kind === "open" ? 4000 : 12000);
    }
    property string viewMode: "mail"      // "mail" | "contacts" | "manual"
    property string composeStationery: "damask"
    property string composeStationeryImage: ""   // base64 PNG set by HBWritingDesk before send

    // seal-avatar gradient pairs (deterministic by string)
    function sealPair(key) {
        var pairs = [["#2f6f63","#1d3f38"],[k.wine4,k.wine2],[k.gilt2,k.gilt0],
                     ["#4f6f8b","#27384a"],["#7a5a8b","#3a2a4a"],["#a85a3a","#5a2a18"]];
        var h = 0; for (var i=0;i<key.length;i++) h = (h*31 + key.charCodeAt(i)) & 0xffff;
        return pairs[h % pairs.length];
    }
    function initials(name) {
        if (!name) return "·";
        var parts = name.split(/\s+/).filter(function(x){return x.length;});
        return parts.slice(0,2).map(function(w){return w[0];}).join("").toUpperCase();
    }
    function richBody(html) {
        if (!html) return "";
        var s = html;
        s = s.replace(/<img[^>]*>/gi, "");
        s = s.replace(/<script[\s\S]*?<\/script>/gi, "");
        s = s.replace(/<link[^>]*>/gi, "");
        s = s.replace(/<div class='greeting'>/g, "<div style='color:" + m.wine2 + "; font-size:19px; font-weight:600;'>");
        s = s.replace(/<div class='sign'>/g, "<div style='color:" + m.inkSoft + "; font-style:italic; font-size:17px; margin-top:14px;'>");
        s = s.replace(/<blockquote>/g, "<blockquote style='color:" + m.inkSoft + ";'>");
        s = s.replace(/<a /g, "<a style='color:" + m.verd2 + ";' ");
        return "<style>p{margin:0 0 12px 0;} b{color:" + m.ink + ";}</style>" + s;
    }

    // ── honest-count helpers ──────────────────────────────────────────────
    // grp: group digits with thin commas so 140000 reads "140,000".
    function grp(n) {
        if (n === undefined || n === null || isNaN(n)) return "0";
        var s = Math.round(n).toString(), out = "", c = 0;
        for (var i = s.length - 1; i >= 0; i--) {
            out = s[i] + out;
            if (++c % 3 === 0 && i > 0) out = "," + out;
        }
        return out;
    }
    // folderTotal: the raw IMAP EXISTS count for the active folder (the badge value).
    // The engine only ever loads the newest window (≤128); this is the true server total.
    function folderTotal() {
        var c = link.counts[win.activeFolder];
        if (c && c.total !== undefined) return c.total;
        var f = mail.folders.folderById(win.activeFolder);
        return (f && f.count !== undefined && f.count !== null) ? f.count : 0;
    }
    // filteredLoaded: how many of the loaded rows the current filter actually shows —
    // this is the exact set that "select all" can cover.
    function filteredLoaded() {
        return mail.messages.filter(function(v){
            return win.activeFilter==="all"
                || (win.activeFilter==="unread"  && v.unread)
                || (win.activeFilter==="flagged" && v.flagged);
        }).length;
    }

    // ── Trash sweep: delete 200 letters at a time ────────────────────────────
    // The engine's deleteMessages() moves one whole UID set per connection and
    // then reloads the folder, sliding the next-older letters up to refill the
    // gallery. The sweep rides exactly that rhythm: select-all + Delete keeps
    // handing the engine each refill until 200 letters have been swept (or the
    // folder/filter runs dry). Guards: a round that makes no progress aborts
    // (a MOVE the server refused would otherwise spin), a folder change aborts,
    // and the sweep never runs inside Trash itself — there a delete is a
    // permanent expunge, one deliberate tap per batch.
    property int    sweepRemaining: 0
    property int    sweepDeleted:   0
    property int    sweepRounds:    0
    property var    sweepLastIds:   []
    property string sweepFolder:    ""
    function inTrash() {
        var f = String(win.activeFolder).toLowerCase();
        var c = String(mail.currentFolder || "").toLowerCase();
        return f.indexOf("trash") >= 0 || c.indexOf("trash") >= 0;
    }
    function filteredIdList() {
        var out = [], msgs = mail.messages;
        for (var i = 0; i < msgs.length; i++) {
            var v = msgs[i];
            if (win.activeFilter==="all"
                || (win.activeFilter==="unread"  && v.unread)
                || (win.activeFilter==="flagged" && v.flagged)) out.push(v.id);
        }
        return out;
    }
    function sweepStart() {
        sweepRemaining = 200; sweepDeleted = 0; sweepRounds = 0;
        sweepLastIds = []; sweepFolder = mail.currentFolder;
        sweepRound();
    }
    function sweepRound() {
        if (sweepRemaining <= 0 || sweepRounds >= 8
            || mail.currentFolder !== sweepFolder) { sweepFinish(); return; }
        if (String(mail.status).indexOf("Delete failed") === 0) {
            sweepAbort("the post office refused the last batch"); return;
        }
        var ids = filteredIdList();
        if (ids.length === 0) { sweepFinish(); return; }
        // no-progress guard: the engine reported done but the same letters are
        // still on the desk — the MOVE did not land; stop rather than spin.
        for (var i = 0; i < ids.length; i++)
            if (sweepLastIds.indexOf(ids[i]) >= 0) {
                sweepDeleted -= sweepLastIds.length;
                sweepAbort("some letters would not move"); return;
            }
        if (ids.length > sweepRemaining) ids = ids.slice(0, sweepRemaining);
        sweepLastIds = ids;
        sweepRounds += 1;
        sweepRemaining -= ids.length;
        sweepDeleted  += ids.length;
        win.noteChange("delete", ids);
        mail.deleteMessages(ids);
        toastTxt.text = "Sweeping to Trash — " + sweepDeleted + " of 200 letters…";
        toast.toastShown = true; toastTimer.restart();
    }
    function sweepFinish() {
        if (sweepDeleted > 0) {
            toastTxt.text = "Swept " + sweepDeleted
                + (sweepDeleted === 1 ? " letter" : " letters") + " to Trash";
            toast.toastShown = true; toastTimer.restart();
        }
        sweepRemaining = 0; sweepDeleted = 0; sweepRounds = 0;
        sweepLastIds = []; sweepFolder = "";
    }
    function sweepAbort(reason) {
        toastTxt.text = "Sweep stopped — " + reason + " ("
            + Math.max(sweepDeleted, 0) + " swept)";
        toast.toastShown = true; toastTimer.restart();
        sweepRemaining = 0; sweepDeleted = 0; sweepRounds = 0;
        sweepLastIds = []; sweepFolder = "";
    }
    Connections {
        target: mail
        function onMessagesChanged() { if (win.sweepRemaining > 0) sweepSettle.restart(); }
    }
    GoogleLink {
        id: link
        mailEngine: mail
        property bool listLoaded: false
        onMessage: function(text) {
            toastTxt.text = text
            toast.toastShown = true; toastTimer.restart()
        }
        // Gmail changed the folder on screen (new letter, one removed elsewhere):
        // reload it, the way a desktop client keeps its list live.
        onFolderChanged: function(folderId) {
            if (win.viewMode === "mail" && folderId === win.activeFolder && !mail.busy && win.sweepRemaining === 0)
                mail.refresh()
        }
        // The engine opens no folder on its own: show the Inbox as soon as Gmail answers.
        onCountsChanged: win.openFirstFolder()
    }
    // …or as soon as the engine's own connection has its folder list, whichever
    // comes first — the courier's separate count connection is seconds slower,
    // and waiting on it left the list empty at startup.
    function openFirstFolder() {
        if (link.listLoaded) return
        link.listLoaded = true
        if (win.viewMode === "mail" && (mail.messages || []).length === 0) mail.openFolder(win.activeFolder)
    }
    Connections {
        target: mail
        ignoreUnknownSignals: true
        function onFoldersChanged() { if (mail.online) win.openFirstFolder() }
        function onOnlineChanged()  { if (mail.online) win.openFirstFolder() }
    }
    // Empty Trash: the sweep only ever reaches the loaded window (pageSize), so a
    // Trash folder bigger than that never actually got emptied from the app. This
    // calls the engine's real emptyTrash() (UID SEARCH ALL, not just what's loaded).
    // Two-tap confirm (matches this app's toast idiom — no dialog component exists
    // here) since it's a permanent, unrecoverable purge.
    property bool emptyTrashArmed: false
    function emptyTrashTap() {
        if (!win.emptyTrashArmed) {
            win.emptyTrashArmed = true;
            emptyTrashDisarm.restart();
            toastTxt.text = "Tap again to permanently empty Trash — " + win.grp(win.folderTotal())
                + " message" + (win.folderTotal() === 1 ? "" : "s") + ", cannot be undone";
            toast.toastShown = true; toastTimer.restart();
            return;
        }
        win.emptyTrashArmed = false;
        emptyTrashDisarm.stop();
        mail.emptyTrash();
        link.countsSoon(8000);
    }
    Timer { id: emptyTrashDisarm; interval: 4000; repeat: false; onTriggered: win.emptyTrashArmed = false }
    Timer {
        id: sweepSettle
        interval: 700; repeat: false
        onTriggered: {
            if (win.sweepRemaining <= 0) return;
            if (mail.busy) { sweepSettle.restart(); return; }
            win.sweepRound();
        }
    }

    // ════════════════════════════════════════════════════════════════════════
    //  REUSABLE CANVAS ORNAMENT
    // ════════════════════════════════════════════════════════════════════════

    // Hummingbird glyph (used in crest, send button, and the flier)
    component Hummingbird: Canvas {
        property color tint: k.gilt4
        property real  wingPhase: 0.0      // 0..1 drives wing angle when animating
        antialiasing: true
        onTintChanged: requestPaint()
        onWingPhaseChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var s = Math.min(width, height) / 100.0;
            ctx.scale(s, s);
            ctx.fillStyle = tint;
            // tail
            ctx.beginPath();
            ctx.moveTo(14,30); ctx.bezierCurveTo(26,40,34,46,44,52);
            ctx.bezierCurveTo(36,50,22,50,10,54); ctx.bezierCurveTo(18,46,14,38,14,30);
            ctx.closePath(); ctx.fill();
            // body
            ctx.beginPath();
            ctx.moveTo(40,50); ctx.bezierCurveTo(50,40,64,36,76,40);
            ctx.bezierCurveTo(70,48,60,56,50,60); ctx.bezierCurveTo(46,58,42,55,40,50);
            ctx.closePath(); ctx.fill();
            // head
            ctx.beginPath(); ctx.arc(76,40,8,0,2*Math.PI); ctx.fill();
            // beak
            ctx.beginPath(); ctx.moveTo(83,39); ctx.lineTo(99,33); ctx.lineTo(84,43); ctx.closePath(); ctx.fill();
            // wing (rotates with wingPhase around ~60,52)
            var ang = (-26 + wingPhase * 46) * Math.PI/180;
            ctx.save(); ctx.translate(50,50); ctx.rotate(ang); ctx.translate(-50,-50);
            ctx.beginPath();
            ctx.moveTo(50,50); ctx.bezierCurveTo(44,30,40,16,30,8);
            ctx.bezierCurveTo(46,14,58,30,60,48); ctx.bezierCurveTo(57,50,53,51,50,50);
            ctx.closePath(); ctx.globalAlpha = 0.92; ctx.fill(); ctx.globalAlpha = 1;
            ctx.restore();
            // throat
            ctx.fillStyle = "#c64b63";
            ctx.beginPath(); ctx.arc(70,46,3.2,0,2*Math.PI); ctx.fill();
        }
    }

    // wax seal disc
    component WaxSeal: Canvas {
        property real glyph: 0    // 0 feather · 1 bird · 2 star
        antialiasing: true
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx = getContext("2d"); ctx.reset();
            var cx=width/2, cy=height/2, R=Math.min(cx,cy)-1;
            var g = ctx.createRadialGradient(cx-R*0.3,cy-R*0.3,1,cx,cy,R);
            g.addColorStop(0,"#7aaa8a"); g.addColorStop(0.55,"#4a6650"); g.addColorStop(1,"#1b2e20");
            ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fillStyle=g; ctx.fill();
            ctx.lineWidth=1; ctx.strokeStyle="#1b2e20"; ctx.stroke();
            // scalloped rim
            ctx.strokeStyle="rgba(246,227,176,0.5)"; ctx.lineWidth=0.8;
            ctx.beginPath(); ctx.arc(cx,cy,R*0.8,0,2*Math.PI); ctx.stroke();
        }
    }

    // 8-petal gilt floret
    component Floret: Canvas {
        antialiasing: true
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx=getContext("2d"); ctx.reset();
            var cx=width/2, cy=height/2, R=Math.min(cx,cy)-1;
            var g=ctx.createRadialGradient(cx,cy,0,cx,cy,R);
            g.addColorStop(0,k.gilt5); g.addColorStop(0.6,k.gilt3); g.addColorStop(1,k.gilt0);
            ctx.beginPath(); ctx.arc(cx,cy,R,0,2*Math.PI); ctx.fillStyle=g; ctx.fill();
            ctx.lineWidth=1; ctx.strokeStyle=k.gilt0; ctx.stroke();
            ctx.fillStyle="rgba(90,58,20,0.85)";
            for (var i=0;i<8;i++){ ctx.save(); ctx.translate(cx,cy); ctx.rotate(i*Math.PI/4);
                ctx.translate(0,-R*0.58); ctx.scale(0.38,1.0);
                ctx.beginPath(); ctx.arc(0,0,R*0.30,0,2*Math.PI); ctx.fill(); ctx.restore(); }
            ctx.beginPath(); ctx.arc(cx,cy,R*0.22,0,2*Math.PI); ctx.fillStyle=k.gilt4; ctx.fill();
        }
    }

    // guilloché barber band (top of the stationery sheet)
    component GiltBand: Canvas {
        antialiasing: true
        Component.onCompleted: requestPaint()
        onWidthChanged: requestPaint()
        onPaint: {
            var ctx=getContext("2d"); ctx.reset();
            for (var x=-height; x<width; x+=20) {
                ctx.beginPath();
                ctx.moveTo(x,0); ctx.lineTo(x+height,height);
                ctx.lineTo(x+height+10,height); ctx.lineTo(x+10,0); ctx.closePath();
                ctx.fillStyle = (Math.floor(x/10)%2===0) ? "rgba(201,138,58,0.55)" : "rgba(233,201,124,0.55)";
                ctx.fill();
            }
        }
    }

    // line-art icon set (folders + toolbar)
    component Icon: Canvas {
        property string name: ""
        property color  tint: k.gilt1
        antialiasing: true
        onTintChanged: requestPaint()
        onNameChanged: requestPaint()
        Component.onCompleted: requestPaint()
        onPaint: {
            var ctx=getContext("2d"); ctx.reset();
            var s=Math.min(width,height)/24.0; ctx.scale(s,s);
            ctx.strokeStyle=tint; ctx.fillStyle=tint;
            ctx.lineWidth=1.7; ctx.lineCap="round"; ctx.lineJoin="round";
            var P=function(){ ctx.beginPath(); };
            if (name==="i-inbox"){ P(); ctx.moveTo(3,13);ctx.lineTo(6,5);ctx.lineTo(18,5);ctx.lineTo(21,13);ctx.lineTo(21,19);ctx.lineTo(3,19);ctx.closePath();ctx.stroke();
                P(); ctx.moveTo(3,13);ctx.lineTo(8,13);ctx.lineTo(10,16);ctx.lineTo(14,16);ctx.lineTo(16,13);ctx.lineTo(21,13);ctx.stroke(); }
            else if (name==="i-star"){ P(); ctx.moveTo(12,3);ctx.lineTo(14.7,8.7);ctx.lineTo(21,9.5);ctx.lineTo(16.4,13.8);ctx.lineTo(17.6,20);ctx.lineTo(12,17.1);ctx.lineTo(6.4,20);ctx.lineTo(7.6,13.8);ctx.lineTo(3,9.5);ctx.lineTo(9.3,8.7);ctx.closePath(); ctx.fill(); }
            else if (name==="i-sent"){ P(); ctx.moveTo(21,4);ctx.lineTo(3,11);ctx.lineTo(9,13);ctx.lineTo(11,19);ctx.lineTo(14,14);ctx.lineTo(18,18);ctx.lineTo(21,4);ctx.closePath(); ctx.stroke(); }
            else if (name==="i-draft"){ P(); ctx.moveTo(5,19);ctx.lineTo(6,15);ctx.lineTo(17,4);ctx.lineTo(20,7);ctx.lineTo(9,18);ctx.closePath(); ctx.stroke(); P(); ctx.moveTo(14,7);ctx.lineTo(17,10);ctx.stroke(); }
            else if (name==="i-archive"){ P(); ctx.rect(3,7,18,3); ctx.stroke(); P(); ctx.moveTo(5,10);ctx.lineTo(5,19);ctx.lineTo(19,19);ctx.lineTo(19,10);ctx.stroke(); P(); ctx.moveTo(10,14);ctx.lineTo(14,14);ctx.stroke(); }
            else if (name==="i-spam"){ P(); ctx.moveTo(12,3);ctx.lineTo(21,8);ctx.lineTo(21,14);ctx.bezierCurveTo(21,18,17,20,12,21);ctx.bezierCurveTo(7,20,3,18,3,14);ctx.lineTo(3,8);ctx.closePath();ctx.stroke(); P(); ctx.moveTo(12,8);ctx.lineTo(12,13);ctx.stroke(); P(); ctx.arc(12,16,0.6,0,2*Math.PI); ctx.fill(); }
            else if (name==="i-trash"){ P(); ctx.moveTo(4,7);ctx.lineTo(20,7);ctx.stroke(); P(); ctx.moveTo(9,7);ctx.lineTo(9,5);ctx.lineTo(15,5);ctx.lineTo(15,7);ctx.stroke(); P(); ctx.moveTo(6,7);ctx.lineTo(7,20);ctx.lineTo(17,20);ctx.lineTo(18,7);ctx.stroke(); }
            else if (name==="i-contacts"){ P(); ctx.rect(4,5,16,14); ctx.stroke(); P(); ctx.arc(12,10,2.6,0,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(8,17);ctx.bezierCurveTo(8,14,10,13,12,13);ctx.bezierCurveTo(14,13,16,14,16,17);ctx.stroke(); }
            else if (name==="i-reply"){ P(); ctx.moveTo(9,7);ctx.lineTo(4,12);ctx.lineTo(9,17);ctx.stroke(); P(); ctx.moveTo(4,12);ctx.lineTo(13,12);ctx.bezierCurveTo(17,12,20,14,20,18);ctx.stroke(); }
            else if (name==="i-reply-all"){ P(); ctx.moveTo(8,7);ctx.lineTo(3,12);ctx.lineTo(8,17);ctx.stroke(); P(); ctx.moveTo(13,7);ctx.lineTo(10,12);ctx.lineTo(13,17);ctx.stroke(); P(); ctx.moveTo(10,12);ctx.lineTo(16,12);ctx.bezierCurveTo(19,12,21,14,21,17);ctx.stroke(); }
            else if (name==="i-forward"){ P(); ctx.moveTo(15,7);ctx.lineTo(20,12);ctx.lineTo(15,17);ctx.stroke(); P(); ctx.moveTo(20,12);ctx.lineTo(11,12);ctx.bezierCurveTo(7,12,4,14,4,18);ctx.stroke(); }
            else if (name==="i-search"){ P(); ctx.arc(11,11,7,0,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(16,16);ctx.lineTo(21,21);ctx.stroke(); }
            else if (name==="i-clip"){ P(); ctx.moveTo(20,11);ctx.lineTo(12,19);ctx.bezierCurveTo(9,22,4,17,7,14);ctx.lineTo(15,6);ctx.bezierCurveTo(17,4,20,7,18,9);ctx.lineTo(10,17);ctx.stroke(); }
            else if (name==="i-thread"){ P(); ctx.moveTo(4,6);ctx.lineTo(17,6);ctx.stroke(); P(); ctx.moveTo(4,10);ctx.lineTo(17,10);ctx.stroke(); P(); ctx.moveTo(7,14);ctx.lineTo(17,14);ctx.stroke(); }
            else if (name==="i-feather"){ P(); ctx.moveTo(20,4);ctx.bezierCurveTo(10,4,5,9,5,16);ctx.lineTo(4,20);ctx.lineTo(9,18);ctx.bezierCurveTo(16,18,20,12,20,4);ctx.closePath(); ctx.fill(); }
            else if (name==="i-book"){ P(); ctx.moveTo(4,5);ctx.lineTo(11,5);ctx.bezierCurveTo(12,5,12,6,12,6);ctx.lineTo(12,19);ctx.bezierCurveTo(12,18,11,18,11,18);ctx.lineTo(4,18);ctx.closePath(); ctx.stroke(); P(); ctx.moveTo(20,5);ctx.lineTo(13,5);ctx.bezierCurveTo(12,5,12,6,12,6);ctx.lineTo(12,19);ctx.bezierCurveTo(12,18,13,18,13,18);ctx.lineTo(20,18);ctx.closePath(); ctx.stroke(); }
            else if (name==="i-refresh"){ P(); ctx.arc(12,12,7,0.6,2*Math.PI); ctx.stroke(); P(); ctx.moveTo(17,5);ctx.lineTo(19,8);ctx.lineTo(15.5,8.5);ctx.stroke(); }
        }
    }

    // seal avatar with monogram
    component SealAva: Item {
        property string label: "·"
        property string seedKey: "x"
        property real   diameter: 42
        property int    fontPx: 16
        width: diameter; height: diameter
        Rectangle {
            anchors.fill: parent; radius: width/2
            border.color: m.gilt0; border.width: 1.5
            gradient: Gradient {
                orientation: Gradient.Vertical   // diagonal is not a QQuickGradient orientation (only Horizontal/Vertical); the old enum was undefined and fell back to vertical anyway — this is pixel-identical and stops the journal flood (1,244 errors/session, 2026-07-07)
                GradientStop { position: 0.0; color: sealPair(seedKey)[0] }
                GradientStop { position: 1.0; color: sealPair(seedKey)[1] }
            }
            Text {
                anchors.centerIn: parent; text: label
                font.family: m.display; font.bold: true; font.pixelSize: fontPx
                color: m.paper0
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════════
    //  ROOT FRAME
    // ════════════════════════════════════════════════════════════════════════
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: m.gilt0; border.width: 2
        radius: 16

        // ── Mode-aware ground ─────────────────────────────────────────
        Rectangle { anchors.fill: parent; radius: 16; color: k.panelBg }
        NCDEVellum { anchors.fill: parent; base: "transparent"; intensity: 0.85 }

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            // ── Titlebar ── removed 2026-09-26: the NCDE window frame already
            // shows "Hummingbird Courier"; a second bar under it read as clutter
            // and its motto line was cut off by the toolbar.

            // ── Toolbar ───────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: Math.max(win.px(38), acctRow.implicitHeight + 10) + 18
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop { position: 0; color: m.paper2 }
                    GradientStop { position: 1; color: m.paper3 }
                }
                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: m.gilt1 }
                DragHandler { target: null; onActiveChanged: if (active) win.startSystemMove() }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16; anchors.rightMargin: 16
                    spacing: 12

                    // Compose (wax-seal pill)
                    Rectangle {
                        Layout.preferredHeight: win.px(36); Layout.preferredWidth: composeRow.implicitWidth + 28
                        radius: height/2; border.color: m.gilt0; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop { position: 0; color: composeHov.hovered ? m.wine4 : m.wine3 }
                            GradientStop { position: 1; color: m.wine1 } }
                        Row {
                            id: composeRow
                            anchors.centerIn: parent; spacing: 10
                            WaxSeal { width: win.px(22); height: win.px(22); anchors.verticalCenter: parent.verticalCenter
                                Icon { anchors.centerIn: parent; width: win.px(13); height: win.px(13); name: "i-feather"; tint: m.gilt5 } }
                            Text { text: "Compose"; font.family: m.titles; font.weight: Font.DemiBold
                                   font.pixelSize: k.fs(13); color: m.gilt5; font.letterSpacing: 1
                                   anchors.verticalCenter: parent.verticalCenter }
                        }
                        HoverHandler { id: composeHov }
                        TapHandler { onTapped: win.mailPaneView = "writing" }
                    }

                    Rectangle { Layout.preferredWidth: 1; Layout.preferredHeight: win.px(26); color: m.gilt1; opacity: 0.45 }

                    // delete (bulk or single)
                    Rectangle {
                        Layout.preferredHeight: win.px(34)
                        Layout.preferredWidth: delRow.implicitWidth + 22
                        radius: 8
                        color: delHov.hovered ? m.paper1 : "transparent"
                        border.color: delHov.hovered ? m.gilt2 : "transparent"; border.width: 1.5
                        Row { id: delRow; anchors.centerIn: parent; spacing: 7
                            Icon { width: win.px(16); height: win.px(16); name:"i-trash"; tint: m.gilt0
                                   anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "Delete"; font.family: m.titles; font.pixelSize: k.fs(12)
                                   color: m.inkLabel; anchors.verticalCenter: parent.verticalCenter
                                   visible: win.width > win.px(1000) } }
                        HoverHandler { id: delHov }
                        TapHandler { onTapped: {
                            var bulkIds = Object.keys(win.selectedIds)
                            if (bulkIds.length > 0 && bulkIds.length >= win.filteredLoaded()
                                && !win.inTrash()) {
                                // Select-all outside Trash = a 200-letter sweep: the
                                // engine deletes each loaded window, reloads, and the
                                // sweep hands it the next refill until 200 are gone.
                                win.selectedIds = {}; win.activeMsgId = ""; win.mailPaneView = "gallery"
                                win.sweepStart()
                            } else if (bulkIds.length > 0) {
                                win.noteChange("delete", bulkIds)
                                mail.deleteMessages(bulkIds)
                                // Honest, pending-tense confirmation. The engine reloads the folder
                                // right after a delete, so the next-older letters slide up to refill
                                // the view — pre-explaining that stops it reading as "they came back".
                                toastTxt.text = "Moving " + bulkIds.length + (bulkIds.length === 1 ? " letter" : " letters")
                                    + " to Trash — older letters slide up to fill the view"
                                toast.toastShown = true; toastTimer.restart()
                                win.selectedIds = {}; win.activeMsgId = ""; win.mailPaneView = "gallery"
                            } else if (win.activeMsgId !== "") {
                                win.noteChange("delete", [win.activeMsgId])
                                mail.deleteMessage(win.activeMsgId)
                                toastTxt.text = "Moving 1 letter to Trash"
                                toast.toastShown = true; toastTimer.restart()
                                win.activeMsgId = ""; win.mailPaneView = "gallery"
                            }
                        } }
                    }

                    // check mail
                    Rectangle {
                        Layout.preferredHeight: win.px(34)
                        Layout.preferredWidth: checkRow.implicitWidth + 22
                        radius: 8; opacity: mail.busy ? 0.45 : 1.0
                        color: checkHov.hovered ? m.paper1 : "transparent"
                        border.color: checkHov.hovered ? m.gilt2 : "transparent"; border.width: 1.5
                        Row { id: checkRow; anchors.centerIn: parent; spacing: 7
                            Icon { width: win.px(16); height: win.px(16); name:"i-refresh"; tint: m.gilt0
                                   anchors.verticalCenter: parent.verticalCenter }
                            Text { text: "Check Mail"; font.family: m.titles; font.pixelSize: k.fs(12)
                                   color: m.inkLabel; anchors.verticalCenter: parent.verticalCenter
                                   visible: win.width > win.px(1000) } }
                        HoverHandler { id: checkHov }
                        TapHandler { enabled: !mail.busy; onTapped: { mail.refresh(); link.countsSoon(0) } }
                    }

                    Rectangle { Layout.preferredWidth: 1; Layout.preferredHeight: win.px(26); color: m.gilt1; opacity: 0.45 }

                    // search
                    Rectangle {
                        Layout.preferredHeight: win.px(34); Layout.fillWidth: true; Layout.maximumWidth: win.px(380)
                        radius: height/2; color: m.paper1
                        border.color: searchInput.activeFocus ? m.gilt3 : m.gilt1; border.width: 1.5
                        Row { anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 8
                            Icon { width: win.px(15); height: win.px(15); name:"i-search"; tint: m.inkSoft; opacity: 0.7
                                   anchors.verticalCenter: parent.verticalCenter }
                            TextInput {
                                id: searchInput
                                width: parent.width - win.px(15) - 8
                                anchors.verticalCenter: parent.verticalCenter
                                font.family: m.serif; font.pixelSize: k.fs(14); color: m.ink
                                clip: true; selectByMouse: true
                                onAccepted: if (text.length) mail.search(text)
                                Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                       text: "Search the post…"; font.family: m.serif; font.italic: true
                                       font.pixelSize: k.fs(14); color: m.inkSoft; opacity: 0.7
                                       visible: !searchInput.text.length && !searchInput.activeFocus } }
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // account chip
                    Rectangle {
                        Layout.preferredHeight: acctRow.implicitHeight + 10
                        Layout.preferredWidth: acctRow.implicitWidth + 30
                        radius: height/2; color: m.paper1
                        border.color: acctChipHov.hovered ? m.gilt3 : m.gilt1; border.width: 1.5
                        Row { id: acctRow; anchors.centerIn: parent; spacing: 9
                            SealAva { diameter: win.px(28); fontPx: k.fs(13); label: mail.accountInitial
                                      seedKey: mail.accountEmail; anchors.verticalCenter: parent.verticalCenter }
                            Column { anchors.verticalCenter: parent.verticalCenter; spacing: 0
                                Text { text: mail.accountName; font.family: m.titles; font.weight: Font.DemiBold
                                       font.pixelSize: k.fs(12); color: m.ink; lineHeight: 0.95 }
                                Text { text: mail.accountEmail.length ? mail.accountEmail : "tap to connect"
                                       font.family: m.fell; font.italic: true
                                       font.pixelSize: k.fs(10); color: mail.accountEmail.length ? m.inkSoft : m.inkLabel } } }
                        HoverHandler { id: acctChipHov }
                        TapHandler { onTapped: win.accountSetupOpen = true }
                    }
                }
            }

            // ── Panes ─────────────────────────────────────────────────────
            RowLayout {
                Layout.fillWidth: true; Layout.fillHeight: true
                spacing: 0

                // ----- SIDEBAR -----
                Rectangle {
                    Layout.preferredWidth: win.sideW; Layout.fillHeight: true
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: m.paper2 }
                        GradientStop { position: 1; color: m.paper3 } }
                    Rectangle { anchors.right: parent.right; width: 2; height: parent.height; color: m.gilt1 }

                    ColumnLayout {
                        anchors.fill: parent; spacing: 0

                        // crest
                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: crestCol.implicitHeight + 22
                            color: "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: m.gilt1 }
                            Column {
                                id: crestCol
                                anchors.centerIn: parent; spacing: 4
                                Text { text: "BUREAU DE POSTE"; font.family: m.fell; font.italic: true
                                       font.pixelSize: k.fs(11); color: m.inkLabel; font.letterSpacing: 3
                                       anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: mail.postOffice.length ? mail.postOffice : mail.accountName
                                       font.family: m.display; font.bold: true
                                       font.pixelSize: k.fs(13); color: m.wineText2; font.letterSpacing: 1
                                       anchors.horizontalCenter: parent.horizontalCenter
                                       // Was getting clipped at the sidebar edge (operator-reported,
                                       // "Iron Orchid Station" at 15px overran the 246px sidebar) —
                                       // shrink one step, cap to the available width, elide instead
                                       // of overflowing/clipping if a longer postOffice name is ever set.
                                       width: Math.min(implicitWidth, win.sideW - 28)
                                       horizontalAlignment: Text.AlignHCenter
                                       elide: Text.ElideRight
                                       visible: text.length > 0 }
                                Row { spacing: 10; anchors.horizontalCenter: parent.horizontalCenter
                                    Rectangle { width:42; height:1; color:m.gilt2; anchors.verticalCenter: parent.verticalCenter }
                                    Hummingbird { width: win.px(16); height: win.px(16); tint:m.gilt3 }
                                    Rectangle { width:42; height:1; color:m.gilt2; anchors.verticalCenter: parent.verticalCenter } }
                            }
                        }

                        // folders
                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: folderCol.implicitHeight; clip: true
                            Column {
                                id: folderCol
                                width: parent.width
                                padding: 10; spacing: 2

                                Repeater {
                                    model: mail.folders
                                    Rectangle {
                                        width: folderCol.width - 20; height: win.px(34); radius: 8
                                        property bool sel: win.viewMode==="mail" && win.activeFolder===modelData.id
                                        color: sel ? m.paper0 : (fHov.hovered ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.14) : "transparent")
                                        border.color: sel ? m.gilt3 : "transparent"; border.width: sel ? 1.5 : 0
                                        Rectangle { visible: parent.sel; width:4; height:22; radius:2
                                                    anchors.verticalCenter: parent.verticalCenter; x:-6
                                                    gradient: Gradient { GradientStop{position:0;color:m.gilt4} GradientStop{position:1;color:m.gilt2} } }
                                        Row { anchors.left: parent.left; anchors.leftMargin: 12
                                              anchors.verticalCenter: parent.verticalCenter; spacing: 11
                                            Icon { width: win.px(18); height: win.px(18); name: modelData.icon
                                                   tint: parent.parent.sel ? m.wine3 : m.gilt1
                                                   anchors.verticalCenter: parent.verticalCenter }
                                            Text { text: modelData.name; font.family: m.titles
                                                   font.pixelSize: k.fs(13); font.weight: parent.parent.sel?Font.DemiBold:Font.Medium
                                                   color: parent.parent.sel ? m.wine2 : m.ink
                                                   anchors.verticalCenter: parent.verticalCenter } }
                                        Rectangle {
                                            readonly property int shown: win.badge(modelData.id, modelData.count)
                                            visible: shown > 0
                                            anchors.right: parent.right; anchors.rightMargin: 12
                                            anchors.verticalCenter: parent.verticalCenter
                                            height: cntT.implicitHeight + 2; width: Math.max(height + 4, cntT.implicitWidth+12); radius: height/2
                                            color: modelData.muted ? "transparent" : m.verd2
                                            Text { id: cntT; anchors.centerIn: parent; text: parent.shown
                                                   font.family: m.garamond; font.pixelSize: k.fs(11); font.bold: true
                                                   color: modelData.muted ? m.inkSoft : m.paper0 } }
                                        HoverHandler { id: fHov }
                                        TapHandler { onTapped: {
                                            win.viewMode="mail"; win.activeFolder=modelData.id;
                                            win.selectedIds = {}
                                            mail.openFolder(modelData.id) } }
                                    }
                                }

                                Text { text: "REGISTRY"; font.family: m.fell; font.italic: true
                                       font.pixelSize: k.fs(11); color: m.inkLabel; font.letterSpacing: 3
                                       leftPadding: 4; topPadding: 12; bottomPadding: 4 }

                                // contacts + manual rows
                                Repeater {
                                    model: [ { id:"contacts", ic:"i-contacts", name:"Address Book" },
                                             { id:"manual",   ic:"i-book",     name:"Operating Manual" } ]
                                    Rectangle {
                                        width: folderCol.width - 20; height: win.px(34); radius: 8
                                        property bool sel: win.viewMode===modelData.id
                                        color: sel ? m.paper0 : (rHov.hovered ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.14) : "transparent")
                                        border.color: sel ? m.gilt3 : "transparent"; border.width: sel ? 1.5 : 0
                                        Row { anchors.left: parent.left; anchors.leftMargin: 12
                                              anchors.verticalCenter: parent.verticalCenter; spacing: 11
                                            Icon { width: win.px(18); height: win.px(18); name: modelData.ic
                                                   tint: parent.parent.sel ? m.wine3 : m.gilt1
                                                   anchors.verticalCenter: parent.verticalCenter }
                                            Text { text: modelData.name; font.family: m.titles
                                                   font.pixelSize: k.fs(13); color: parent.parent.sel?m.wineText2:m.ink
                                                   anchors.verticalCenter: parent.verticalCenter } }
                                        HoverHandler { id: rHov }
                                        TapHandler { onTapped: { win.selectedIds = {}; win.viewMode = modelData.id } }
                                    }
                                }
                            }
                        }

                        // storage meter — hidden until server quota is fetched
                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: 64
                            Layout.margins: 14
                            visible: mail.quotaGB > 0
                            radius: 8; color: Qt.rgba(1,1,1,0.28); border.color: m.gilt1; border.width: 1
                            Column { anchors.fill: parent; anchors.margins: 12; spacing: 7
                                Item { width: parent.width; height: 14
                                    Text { anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                                           text:"Postbox"; font.family:m.fell; font.italic:true; font.pixelSize: Math.round(11 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); color:m.inkSoft }
                                    Text { anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                                           text: mail.usedGB.toFixed(1)+" / "+mail.quotaGB.toFixed(0)+" GB"
                                           font.family:m.fell; font.italic:true; font.pixelSize: Math.round(11 * ((theme ? theme.fontMedium : ncde.fontSize_md) / 13.0)); color:m.inkSoft } }
                                Rectangle { width: parent.width; height: 7; radius: 4; color: m.paper3
                                            border.color: m.gilt1; border.width: 1; clip: true
                                    Rectangle { height: parent.height-2; y:1; x:1
                                        width: (parent.width-2) * Math.min(1, mail.usedGB/mail.quotaGB)
                                        radius: 3
                                        gradient: Gradient { orientation: Gradient.Horizontal
                                            GradientStop{position:0;color:m.verd3} GradientStop{position:1;color:m.verd2} } } }
                            }
                        }
                    }
                }

                // ----- MIDDLE + RIGHT depend on viewMode -----
                // MAIL: message list
                Rectangle {
                    visible: win.viewMode==="mail"
                    Layout.preferredWidth: Math.max(392, win.px(300)); Layout.fillHeight: true
                    color: m.paper1
                    Rectangle { anchors.right: parent.right; width: 2; height: parent.height; color: m.gilt1 }

                    ColumnLayout {
                        anchors.fill: parent; spacing: 0
                        // list head — two tidy lines that size to their text:
                        //   [☐] Inbox ·············· 3 messages   [N selected]
                        //   (Empty Trash) (All) (Unread) (Flagged)
                        // (was a fixed 84 px box where the count sat under the chips)
                        Rectangle {
                            Layout.fillWidth: true; Layout.preferredHeight: headCol.implicitHeight + 20; color: "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color: m.gilt1 }
                            Column {
                                id: headCol
                                anchors.left: parent.left; anchors.right: parent.right
                                anchors.leftMargin: 14; anchors.rightMargin: 14
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 8
                                RowLayout {
                                    width: parent.width; spacing: 10
                                    // select-all checkbox
                                    Rectangle { id: selectAllBox; implicitWidth: win.px(16); implicitHeight: win.px(16); radius: 3
                                        Layout.alignment: Qt.AlignVCenter
                                        color: "transparent"; border.color: m.gilt2; border.width: 1
                                        property bool allSelected: mail.messages.length > 0 &&
                                            Object.keys(win.selectedIds).length === mail.messages.filter(function(v){
                                                return win.activeFilter==="all" || (win.activeFilter==="unread"&&v.unread) || (win.activeFilter==="flagged"&&v.flagged)}).length
                                        Rectangle { visible: selectAllBox.allSelected; anchors.fill: parent; anchors.margins: 3; radius: 1; color: m.wine3 }
                                        Rectangle { visible: !selectAllBox.allSelected && Object.keys(win.selectedIds).length > 0
                                                    anchors.centerIn: parent; width: parent.width/2; height: 2; color: m.wine3 }
                                        TapHandler { onTapped: {
                                            var msgs = mail.messages.filter(function(v){
                                                return win.activeFilter==="all" || (win.activeFilter==="unread"&&v.unread) || (win.activeFilter==="flagged"&&v.flagged)})
                                            var ids = {}
                                            if (!selectAllBox.allSelected) { for (var i=0;i<msgs.length;i++) ids[msgs[i].id]=true }
                                            win.selectedIds = ids
                                        } }
                                    }
                                    Text { id: headTitle
                                           text: mail.folders.folderById(win.activeFolder)["name"] || "Inbox"
                                           font.family: m.display; font.bold: true; font.pixelSize: k.fs(16)
                                           color: m.wineText2; font.letterSpacing: 1
                                           elide: Text.ElideRight; Layout.fillWidth: true }
                                    // Honest load status: the engine loads only the newest window
                                    // (≤128). When the folder holds more than is loaded, say so
                                    // plainly instead of implying the badge count is what's here.
                                    Text {
                                        visible: Object.keys(win.selectedIds).length === 0
                                        readonly property int loaded: win.filteredLoaded()
                                        readonly property int total:  win.folderTotal()
                                        text: (total > loaded)
                                              ? (win.grp(loaded) + " of " + win.grp(total) + " loaded")
                                              : (win.grp(loaded) + (loaded === 1 ? " message" : " messages"))
                                        font.family: m.fell; font.italic: true
                                        font.pixelSize: k.fs(12); color: m.inkSoft
                                        Layout.alignment: Qt.AlignVCenter
                                    }
                                    // selection counter — visual only; toolbar Delete handles the delete
                                    Rectangle { visible: Object.keys(win.selectedIds).length > 0
                                        Layout.alignment: Qt.AlignVCenter
                                        implicitHeight: delBulkT.implicitHeight + 6; implicitWidth: delBulkT.implicitWidth+18
                                        radius: height/2
                                        color: m.wine3; border.color: m.wine1; border.width:1
                                        Text { id: delBulkT; anchors.centerIn: parent
                                               // "N selected"; when the selection covers every loaded row,
                                               // say "· all loaded" so the operator knows select-all reaches
                                               // the loaded window (≤128), not the whole folder.
                                               text: {
                                                   var n = Object.keys(win.selectedIds).length
                                                   return n + " selected" + (n > 0 && n >= win.filteredLoaded() ? " · all loaded" : "")
                                               }
                                               font.family: m.titles; font.pixelSize: k.fs(11); color: m.gilt5 }
                                    }
                                }
                                Row { spacing: 6
                                    Rectangle {
                                        visible: win.activeFolder === "trash"
                                        height: emptyTrashT.implicitHeight + 8; width: emptyTrashT.implicitWidth+22; radius: height/2
                                        color: win.emptyTrashArmed ? m.wine1 : m.paper2
                                        border.color: win.emptyTrashArmed ? m.wine1 : m.gilt1; border.width: 1
                                        Text { id: emptyTrashT; anchors.centerIn: parent
                                               text: win.emptyTrashArmed ? "Tap again to confirm" : "Empty Trash"
                                               font.family: m.titles; font.pixelSize: k.fs(11)
                                               color: win.emptyTrashArmed ? m.gilt5 : m.inkLabel }
                                        TapHandler { onTapped: win.emptyTrashTap() }
                                    }
                                    Repeater { model: [ {f:"all",t:"All"}, {f:"unread",t:"Unread"}, {f:"flagged",t:"Flagged"} ]
                                        Rectangle { height: chipT.implicitHeight + 8; width: chipT.implicitWidth+22; radius: height/2
                                            property bool sel: win.activeFilter===modelData.f
                                            color: sel ? m.wine3 : m.paper2; border.color: sel ? m.wine1 : m.gilt1; border.width:1
                                            Text { id: chipT; anchors.centerIn: parent; text: modelData.t
                                                   font.family: m.titles; font.pixelSize: k.fs(11); color: sel?m.gilt5:m.inkLabel }
                                            TapHandler { onTapped: win.activeFilter = modelData.f } } }
                                }
                            }
                        }
                        // rows
                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: rowsCol.implicitHeight; clip: true
                            Column {
                                id: rowsCol; width: parent.width
                                Repeater {
                                    model: mail.messages
                                    Rectangle {
                                        width: rowsCol.width
                                        visible: win.activeFilter==="all"
                                                 || (win.activeFilter==="unread" && modelData.unread)
                                                 || (win.activeFilter==="flagged" && modelData.flagged)
                                        height: visible ? rowGrid.implicitHeight + 26 : 0
                                        property bool sel: win.activeMsgId===modelData.id
                                        color: sel ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.18)
                                                   : (mrHov.hovered ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.09) : "transparent")
                                        Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, 0.22) }
                                        Rectangle { visible: parent.sel; width:3; height: parent.height; color: m.gilt3 }
                                        Rectangle { visible: modelData.unread; width:7; height:7; radius:4; color: m.verd2
                                                    anchors.left: parent.left; anchors.leftMargin: 5; anchors.verticalCenter: parent.verticalCenter }

                                        RowLayout {
                                            id: rowGrid
                                            anchors.fill: parent
                                            anchors.leftMargin: 16; anchors.rightMargin: 16
                                            anchors.topMargin: 13; anchors.bottomMargin: 13
                                            spacing: 11
                                            Rectangle { id: rowChk; implicitWidth: 16; implicitHeight: 16; radius: 3
                                                Layout.alignment: Qt.AlignVCenter
                                                color: "transparent"; border.color: m.gilt2; border.width: 1
                                                property bool checked: win.selectedIds[modelData.id] === true
                                                Rectangle { visible: rowChk.checked; anchors.fill: parent; anchors.margins: 3; radius: 1; color: m.wine3 }
                                                TapHandler { onTapped: {
                                                    var ids = Object.assign({}, win.selectedIds)
                                                    if (ids[modelData.id]) delete ids[modelData.id]
                                                    else ids[modelData.id] = true
                                                    win.selectedIds = ids
                                                } }
                                            }
                                            SealAva { diameter: 42; label: initials(modelData.from); seedKey: modelData.id
                                                      Layout.alignment: Qt.AlignTop }
                                            ColumnLayout {
                                                Layout.fillWidth: true; spacing: 2
                                                RowLayout {
                                                    Layout.fillWidth: true; spacing: 8
                                                    Text { text: modelData.from; font.family: m.serif; font.pixelSize: k.fs(16)
                                                           font.bold: modelData.unread; color: m.ink; elide: Text.ElideRight
                                                           Layout.fillWidth: true }
                                                    Text { text: modelData.time; font.family: m.fell; font.italic: true
                                                           font.pixelSize: k.fs(11); color: m.inkSoft }
                                                }
                                                Text { text: modelData.subj; font.family: m.serif; font.pixelSize: k.fs(15)
                                                       font.bold: modelData.unread; color: m.wineText2; elide: Text.ElideRight
                                                       Layout.fillWidth: true }
                                                Text { text: modelData.snippet; font.family: m.garamond; font.pixelSize: k.fs(13)
                                                       color: m.inkSoft; wrapMode: Text.WordWrap; maximumLineCount: 2
                                                       elide: Text.ElideRight; Layout.fillWidth: true
                                                       visible: modelData.snippet && modelData.snippet.length > 0 }
                                                RowLayout {
                                                    spacing: 8; Layout.topMargin: 4
                                                    Rectangle { visible: modelData.thread>1; implicitHeight:18; radius:9
                                                        implicitWidth: thr.implicitWidth+16; color: m.paper2; border.color: m.gilt2; border.width:1
                                                        Row { anchors.centerIn: parent; spacing:4
                                                            Icon { width:11; height:11; name:"i-thread"; tint: m.wine3; anchors.verticalCenter: parent.verticalCenter }
                                                            Text { id: thr; text: modelData.thread; font.family: m.garamond
                                                                   font.pixelSize: k.fs(11); font.bold: true; color: m.wineText3
                                                                   anchors.verticalCenter: parent.verticalCenter } } }
                                                    Icon { visible: modelData.attach && modelData.attach.length>0
                                                           Layout.preferredWidth:14; Layout.preferredHeight:14; name:"i-clip"; tint: m.gilt1 }
                                                    Item { Layout.fillWidth: true }
                                                    Icon { id: starIcon; Layout.preferredWidth:16; Layout.preferredHeight:16; name:"i-star"
                                                           tint: modelData.flagged ? m.gilt3 : m.paper3
                                                           TapHandler { onTapped: { mail.setFlag(modelData.id, !modelData.flagged); link.countsSoon(6000) } } }
                                                }
                                            }
                                        }
                                        HoverHandler { id: mrHov }
                                        TapHandler { onTapped: (eventPoint) => {
                                            var p = starIcon.mapFromItem(parent, eventPoint.position.x, eventPoint.position.y)
                                            if (!starIcon.contains(p)) { win.activeMsgId = modelData.id; if (modelData.unread) win.noteChange("read", [modelData.id]); mail.openMessage(modelData.id); win.mailPaneView = "reading" }
                                        } }
                                    }
                                }
                            }
                        }
                    }
                }

                // MAIL: reading pane
                Rectangle {
                    visible: win.viewMode==="mail"
                    Layout.fillWidth: true; Layout.fillHeight: true
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:m.paper1} GradientStop{position:1;color:m.paper2} }

                    // stationery gallery — full page, always accessible
                    HBGallery {
                        anchors.fill: parent
                        opacity: win.mailPaneView === "gallery" ? 1 : 0
                        visible: opacity > 0
                        Behavior on opacity { NumberAnimation { duration: 180; easing.type: Easing.InOutQuad } }
                        pal: m; win: win
                    }

                    // reading desk — shown when a message is open
                    HBReadingDesk {
                        anchors.fill: parent
                        opacity: win.mailPaneView === "reading" ? 1 : 0
                        visible: opacity > 0
                        Behavior on opacity { NumberAnimation { duration: 180; easing.type: Easing.InOutQuad } }
                        pal: m; win: win
                    }

                    // writing desk — compose on stationery, send returns to gallery
                    HBWritingDesk {
                        anchors.fill: parent
                        opacity: win.mailPaneView === "writing" ? 1 : 0
                        visible: opacity > 0
                        Behavior on opacity { NumberAnimation { duration: 180; easing.type: Easing.InOutQuad } }
                        pal: m; win: win
                    }
                }

                // ----- CONTACTS VIEW -----
                Rectangle {
                    visible: win.viewMode==="contacts"
                    Layout.fillWidth: true; Layout.fillHeight: true
                    color: m.paper1
                    RowLayout {
                        anchors.fill: parent; spacing: 0
                        Rectangle {
                            Layout.preferredWidth: Math.max(392, win.px(300)); Layout.fillHeight: true; color: m.paper1
                            Rectangle { anchors.right: parent.right; width: 2; height: parent.height; color: m.gilt1 }
                            ColumnLayout { anchors.fill: parent; spacing: 0
                                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: Math.max(abHead.implicitHeight, gBtn.height) + 20; color: "transparent"
                                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color: m.gilt1 }
                                    Column { id: abHead; anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: gBtn.left; anchors.rightMargin: 10
                                        spacing: 1
                                        Text { text: "Address Book"; font.family: m.display; font.bold: true
                                               font.pixelSize: k.fs(16); color: m.wineText2 }
                                        Text { font.family: m.fell; font.italic: true; font.pixelSize: k.fs(11); color: m.inkSoft
                                               text: link.busy ? link.status
                                                     : (link.contactCount > 0
                                                        ? win.grp(win.book.length) + " names · Gmail" + (link.lastSync ? ", " + link.lastSync : "")
                                                        : win.grp(win.book.length) + (win.book.length === 1 ? " name" : " names")) }
                                    }
                                    // Connect Google / Try again / Refresh
                                    Rectangle {
                                        id: gBtn
                                        readonly property bool needs: !link.connected || link.missing.length > 0
                                        anchors.right: parent.right; anchors.rightMargin: 12; anchors.verticalCenter: parent.verticalCenter
                                        height: gBtnT.implicitHeight + 8; width: gBtnT.implicitWidth + 22; radius: height/2
                                        opacity: link.busy ? 0.5 : 1.0
                                        color: needs ? m.verd2 : (gHov.hovered ? m.paper0 : "transparent")
                                        border.color: needs ? m.verd1 : m.gilt1; border.width: 1
                                        Text { id: gBtnT; anchors.centerIn: parent
                                               text: !link.connected ? "Connect Google"
                                                     : (link.missing.length > 0 ? "Try again" : "Refresh")
                                               font.family: m.titles; font.pixelSize: k.fs(11)
                                               color: gBtn.needs ? m.paper0 : m.inkLabel }
                                        HoverHandler { id: gHov }
                                        TapHandler { enabled: !link.busy
                                            onTapped: gBtn.needs ? link.signIn() : link.syncContacts() }
                                    }
                                }
                                // What Google left out, said plainly (a box left unticked on its page)
                                Rectangle {
                                    visible: link.connected && link.missing.length > 0 && !link.busy
                                    Layout.fillWidth: true; Layout.preferredHeight: visible ? missT.implicitHeight + 16 : 0
                                    color: Qt.rgba(k.wine4.r, k.wine4.g, k.wine4.b, 0.10)
                                    Text { id: missT; anchors.left: parent.left; anchors.right: parent.right
                                           anchors.margins: 14; anchors.verticalCenter: parent.verticalCenter
                                           wrapMode: Text.WordWrap; font.family: m.serif; font.pixelSize: k.fs(13); color: m.ink
                                           text: "Google didn't give Hummingbird: " + link.missing.join(", ")
                                                 + ". On Google's page, tick every box, then Continue. Tap “Try again”." }
                                }
                                Rectangle {
                                    visible: !link.busy && link.connected && link.missing.length === 0
                                             && link.status !== "" && link.status.indexOf("Connected as") !== 0
                                    Layout.fillWidth: true; Layout.preferredHeight: visible ? statT.implicitHeight + 16 : 0
                                    color: Qt.rgba(k.wine4.r, k.wine4.g, k.wine4.b, 0.10)
                                    Text { id: statT; anchors.left: parent.left; anchors.right: parent.right
                                           anchors.margins: 14; anchors.verticalCenter: parent.verticalCenter
                                           wrapMode: Text.WordWrap; font.family: m.serif; font.pixelSize: k.fs(13); color: m.ink
                                           text: link.status }
                                }
                                // find a name
                                Rectangle {
                                    Layout.fillWidth: true; Layout.preferredHeight: win.px(34)
                                    Layout.leftMargin: 12; Layout.rightMargin: 14; Layout.topMargin: 8; Layout.bottomMargin: 6
                                    radius: height/2; color: m.paper1
                                    border.color: contactSearch.activeFocus ? m.gilt3 : m.gilt1; border.width: 1.5
                                    Row { anchors.fill: parent; anchors.leftMargin: 14; anchors.rightMargin: 14; spacing: 8
                                        Icon { width:15; height:15; name:"i-search"; tint: m.inkSoft; opacity: 0.7
                                               anchors.verticalCenter: parent.verticalCenter }
                                        TextInput {
                                            id: contactSearch
                                            width: parent.width - 26
                                            anchors.verticalCenter: parent.verticalCenter
                                            font.family: m.serif; font.pixelSize: k.fs(15); color: m.ink
                                            clip: true; selectByMouse: true
                                            onTextChanged: { win.contactFilter = text; win.activeContact = 0 }
                                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                                   text: "Find a name…"; font.family: m.serif; font.italic: true
                                                   font.pixelSize: k.fs(15); color: m.inkSoft; opacity: 0.6
                                                   visible: !contactSearch.text.length && !contactSearch.activeFocus } }
                                    }
                                }
                                ListView { id: cList
                                    Layout.fillWidth: true; Layout.fillHeight: true
                                    clip: true; model: win.shownBook
                                    delegate: Rectangle { width: cList.width; height: Math.max(60, win.px(52))
                                                property bool sel: win.activeContact===index
                                                color: sel ? Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.18) : (cHov.hovered?Qt.rgba(k.gilt3.r, k.gilt3.g, k.gilt3.b, 0.09):"transparent")
                                                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color: Qt.rgba(k.gilt1.r, k.gilt1.g, k.gilt1.b, 0.18) }
                                                Row { anchors.left: parent.left; anchors.leftMargin: 18
                                                      anchors.verticalCenter: parent.verticalCenter; spacing: 12
                                                    SealAva { diameter: 40; label: initials(modelData.nm); seedKey: modelData.em || modelData.nm }
                                                    Column { anchors.verticalCenter: parent.verticalCenter
                                                        Text { text: modelData.nm; font.family: m.serif; font.pixelSize: k.fs(16)
                                                               font.bold: true; color: m.ink; width: cList.width - 90; elide: Text.ElideRight }
                                                        Text { text: modelData.em || modelData.tel || ""; font.family: m.fell; font.italic: true
                                                               font.pixelSize: k.fs(12); color: m.inkSoft; width: cList.width - 90; elide: Text.ElideRight } } }
                                                HoverHandler { id: cHov }
                                                TapHandler { onTapped: win.activeContact = index }
                                            }
                                }
                            }
                        }
                        // contact card
                        Rectangle {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            gradient: Gradient { orientation: Gradient.Vertical
                                GradientStop{position:0;color:m.paper1} GradientStop{position:1;color:m.paper2} }
                            property var c: (win.shownBook.length > win.activeContact) ? win.shownBook[win.activeContact] : null
                            Column {
                                anchors.top: parent.top; anchors.topMargin: 48
                                anchors.horizontalCenter: parent.horizontalCenter; spacing: 10
                                visible: parent.c !== null
                                SealAva { diameter: 110; fontPx: 40; label: parent.parent.c ? initials(parent.parent.c.nm) : "·"
                                          seedKey: parent.parent.c ? parent.parent.c.em : "x"
                                          anchors.horizontalCenter: parent.horizontalCenter }
                                Text { text: parent.parent.c ? parent.parent.c.nm : ""
                                       font.family: m.display; font.pixelSize: k.fs(26); color: m.wineText2
                                       anchors.horizontalCenter: parent.horizontalCenter; topPadding: 8 }
                                Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 8
                                    Text { text:"POST"; font.family: m.fell; font.italic: true; color: m.inkLabel; font.pixelSize: k.fs(14) }
                                    Text { text: parent.parent.c ? parent.parent.c.em : ""; font.family: m.garamond; font.pixelSize: k.fs(15); color: m.ink } }
                                Row { anchors.horizontalCenter: parent.horizontalCenter; spacing: 8
                                    Text { text:"OF"; font.family: m.fell; font.italic: true; color: m.inkLabel; font.pixelSize: k.fs(14) }
                                    Text { text: parent.parent.c ? parent.parent.c.tel : ""; font.family: m.garamond; font.pixelSize: k.fs(15); color: m.ink } }
                                Rectangle { width: 160; height: 36; radius: 18
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    gradient: Gradient { orientation: Gradient.Vertical
                                        GradientStop{position:0;color:m.verd3} GradientStop{position:1;color:m.verd2} }
                                    border.color: m.verd1; border.width: 1.5
                                    Text { anchors.centerIn: parent; text:"Write a Letter"; font.family: m.titles
                                           font.pixelSize: k.fs(12); color: m.paper0 }
                                    // Write to this person: their address in To, on the writing desk.
                                    TapHandler { onTapped: {
                                        var c = parent.parent.parent.c
                                        if (c && c.em) win.composeTo = c.em
                                        win.viewMode = "mail"; win.mailPaneView = "writing" } } }
                            }
                        }
                    }
                }

                // ----- OPERATING MANUAL -----
                Rectangle {
                    visible: win.viewMode==="manual"
                    Layout.fillWidth: true; Layout.fillHeight: true
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:m.paper1} GradientStop{position:1;color:m.paper2} }
                    Flickable {
                        anchors.fill: parent; contentHeight: manCol.implicitHeight + 60; clip: true
                        Column {
                            id: manCol
                            x: 48; y: 34; width: Math.min(760, parent.width - 96); spacing: 18

                            Row { spacing: 14
                                Hummingbird { width: 40; height: 40; tint: m.gilt3; anchors.verticalCenter: parent.verticalCenter }
                                Column {
                                    Text { text: "Operating Manual"; font.family: m.display; font.bold: true
                                           font.pixelSize: k.fs(28); color: m.wineText2 }
                                    Text { text: "Petal shows you around -- she won't take long"; font.family: m.fell
                                           font.italic: true; font.pixelSize: k.fs(14); color: m.inkSoft } }
                            }
                            Rectangle { width: parent.width; height: 2; color: m.gilt2; opacity: 0.6 }

                            Repeater {
                                model: [
                                    { h:"I · Meet Petal",
                                      b:"Hi! I'm Petal. I'm a hummingbird and I carry your post and I am <b>very fast</b>, so let's keep this brief. There are three rooms. The <b>Gallery</b> is your stationery and your identity and it's the prettiest room and I love it. The <b>Writing Desk</b> is where you write letters -- obviously. The <b>Reading Desk</b> opens when you tap a letter -- plain and quiet so the words are what matter. Your folders live in the <b>Bureau</b> on the left. That's it! You can stop reading now. Are you still reading? Fine." },
                                    { h:"II · The Gallery",
                                      b:"OK THIS IS THE BEST PART. Look at the stationery -- <b>twelve sets</b>, Garden and Formal and Professional -- tap one and it gets a gold border and that means it's yours now, congratulations. At the top is your <b>identity bar</b>: put in your Role and a Signature, tap <b>Save</b>, and from now on every letter you send has your name at the bottom in the accent colour of your stationery. This is actually very elegant and I had very strong opinions about the colours. Anyway. Moving on." },
                                    { h:"III · Writing a Letter",
                                      b:"Tap <b>Compose</b>. The desk opens and your stationery is already there and I put a little greeting at the top because I thought it would be nice. Fill in <b>To</b>, <b>CC</b> if there is a CC (there usually isn't, be honest with yourself), and a proper <b>Subject</b> -- not just 'hi'. Write your letter. When you're done, tap the wax-sealed <b>Send</b> button in the corner. I take flight. A notice says: <i>Despatch sent -- 1 letter on the wing.</i> That's me, flying away with your letter. It's very dramatic. I enjoy it enormously." },
                                    { h:"IV · Connecting Your Account",
                                      b:"Tap the <b>account chip</b> in the toolbar. This part is a little fiddly but it's just the once, I promise. Enter your name, your email address, and an <b>App Password</b> -- a special 16-character one you make at myaccount.google.com under <i>Security, then App Passwords</i>, with 2-Step Verification on first. OR tap <b>Sign in with Google</b> and let the browser sort it out, which is honestly what most people do. Press <b>Connect</b>. Then your mail starts arriving and I have somewhere to fly to, which is the whole point." },
                                    { h:"V · The Registry",
                                      b:"The <b>Registry</b> holds your correspondents. I collect them automatically from your sent and received post -- the book fills itself in, you don't have to do anything. I know. You're welcome. Open a contact card to write to them directly. That is the whole chapter." },
                                    { h:"VI · A Note on Privacy",
                                      b:"I speak only to your mail server. Nobody else. No third houses, no middlemen, nothing. Your password lives in your own config, readable only by you. I take post very seriously. The entire reason letters exist is because they're private. I carry yours with care and I do not stop for anyone." },
                                ]
                                Column {
                                    width: manCol.width; spacing: 7
                                    Text { text: modelData.h; font.family: m.titles; font.weight: Font.DemiBold
                                           font.pixelSize: k.fs(18); color: m.wineText3 }
                                    Text { text: modelData.b; textFormat: Text.RichText
                                           font.family: m.garamond; font.pixelSize: k.fs(16); color: m.ink
                                           width: parent.width; wrapMode: Text.WordWrap; lineHeight: 1.35 }
                                    Rectangle { width: 60; height: 1; color: m.gilt2; opacity: 0.5 }
                                }
                            }
                            Item { width: 1; height: 20 }
                        }
                    }
                }
            }

            // ── Statusbar ─────────────────────────────────────────────────
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: statusTxt.implicitHeight + 8
                gradient: Gradient { orientation: Gradient.Vertical
                    GradientStop{position:0;color:m.wine2} GradientStop{position:1;color:m.wine1} }
                Rectangle { anchors.top: parent.top; width: parent.width; height: 1.5; color: m.gilt3 }
                Row { anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 12
                    Rectangle { width:7; height:7; radius:4; color: mail.online ? m.verd3 : m.gilt3
                                anchors.verticalCenter: parent.verticalCenter }
                    Text { id: statusTxt; text: mail.status; font.family: m.fell; font.italic: true; font.pixelSize: k.fs(12)
                           color: m.gilt4; anchors.verticalCenter: parent.verticalCenter } }
                Row { anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter; spacing: 14
                    Text { // Honest tally: loaded count, plus the true server total when the
                           // folder holds more than the loaded window shows.
                           text: {
                               var loaded = mail.messages.length
                               var total = (win.viewMode === "mail") ? win.folderTotal() : 0
                               return (total > loaded)
                                   ? (win.grp(loaded) + " of " + win.grp(total) + " loaded")
                                   : (win.grp(loaded) + " conversations")
                           }
                           font.family: m.fell; font.italic: true
                           font.pixelSize: k.fs(12); color: m.gilt4 }
                    Text { text: "·"; color: m.gilt3; font.pixelSize: k.fs(12) }
                    Text { text: "Hummingbird Courier v1.0"; font.family: m.fell; font.italic: true
                           font.pixelSize: k.fs(12); color: m.gilt4 } }
            }
        }
    }

    // ════════════════════════════════════════════════════════════════════════
    //  COMPOSE OVERLAY — removed; compose is now HBWritingDesk (mailPaneView="writing")
    // ════════════════════════════════════════════════════════════════════════
    /* REMOVED Rectangle {
        anchors.fill: parent; color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.42)
        visible: win.composeOpen; z: 50
        TapHandler { onTapped: win.composeOpen = false }

        Rectangle {
            id: composeSheet
            width: Math.min(720, win.width - 80); height: 560
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom; anchors.bottomMargin: 26
            color: m.paper0; radius: 10; border.color: m.gilt0; border.width: 2
            // swallow taps so clicking the sheet doesn't close it
            TapHandler { }
            Connections { target: win; function onComposeOpenChanged() {
                if (win.composeOpen) {
                    bodyEdit.text = ""
                    composeCanvas.requestPaint()
                    crestCanvas.requestPaint()
                } else {
                    bodyEdit.text = ""
                    composeTo = ""; composeCc = ""; composeBcc = ""; composeSubj = ""; composeBody = ""
                }
            } }

            transform: Translate { id: riseT; y: win.composeOpen ? 0 : 30 }
            Behavior on opacity { NumberAnimation { duration: 200 } }

            ColumnLayout {
                anchors.fill: parent; spacing: 0
                // head
                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: 46
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop{position:0;color:m.wine3} GradientStop{position:1;color:m.wine1} }
                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:2; color: m.gilt3 }
                    Text { anchors.left: parent.left; anchors.leftMargin: 16; anchors.verticalCenter: parent.verticalCenter
                           text:"A New Despatch"; font.family: m.display; font.bold: true; font.pixelSize: k.fs(14)
                           color: m.gilt5; font.letterSpacing: 1.5 }
                    Text { anchors.right: parent.right; anchors.rightMargin: 16; anchors.verticalCenter: parent.verticalCenter
                           text:"✕"; color: m.gilt4; font.pixelSize: k.fs(18)
                           TapHandler { onTapped: win.composeOpen = false } }
                }
                // fields
                Column {
                    Layout.fillWidth: true; Layout.leftMargin: 20; Layout.rightMargin: 20; Layout.topMargin: 6
                    Repeater {
                        model: [ {k:"To",ph:"recipient@example.com",id:"to"},
                                 {k:"Cc",ph:"—",id:"cc"},
                                 {k:"Subject",ph:"Regarding…",id:"subj"} ]
                        Rectangle { width: parent.width; height: 46; color: "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height:1; color: m.gilt1 }
                            Row { anchors.fill: parent; spacing: 12
                                Text { text: modelData.k.toUpperCase(); font.family: m.fell; font.italic: true
                                       font.pixelSize: k.fs(13); color: m.inkLabel; font.letterSpacing: 1.5; width: 64
                                       anchors.verticalCenter: parent.verticalCenter }
                                TextInput { id: fieldInput
                                    width: parent.width - 80; anchors.verticalCenter: parent.verticalCenter
                                    font.family: m.serif; font.pixelSize: k.fs(16); color: m.ink
                                    clip: true; selectByMouse: true
                                    property string fieldId: modelData.id
                                    onTextChanged: {
                                        if (fieldId==="to") composeTo = text
                                        else if (fieldId==="cc") composeCc = text
                                        else composeSubj = text
                                    }
                                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                           text: modelData.ph; font.family: m.serif; font.pixelSize: k.fs(16)
                                           color: m.inkSoft; opacity: 0.55
                                           visible: !fieldInput.text.length && !fieldInput.activeFocus } }
                            }
                            Connections { target: win; function onComposeOpenChanged() {
                                if (win.composeOpen) {
                                    if (fieldInput.fieldId === "to") fieldInput.text = win.composeTo
                                    else if (fieldInput.fieldId === "cc") fieldInput.text = win.composeCc
                                    else if (fieldInput.fieldId === "subj") fieldInput.text = win.composeSubj
                                } else { fieldInput.text = "" }
                            } }
                        }
                    }
                }
                // body — stationery letterhead canvas with pad overlay
                Rectangle {
                    id: composeBodyRect
                    Layout.fillWidth: true; Layout.fillHeight: true
                    Layout.margins: 14
                    color: "transparent"; radius: 5; clip: true
                    border.color: m.gilt2; border.width: 1

                    Canvas {
                        id: composeCanvas
                        anchors.fill: parent
                        renderStrategy: Canvas.Cooperative
                        onWidthChanged: if (width > 0 && height > 0) requestPaint()
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.reset()
                            Sta.setByKey(win.composeStationery).paint(ctx, width, height)
                        }
                    }

                    Connections {
                        target: win
                        function onComposeStationeryChanged() {
                            composeCanvas.requestPaint()
                            crestCanvas.requestPaint()
                            stationeryThumb.requestPaint()
                        }
                    }

                    // the pad — positioned past the left band
                    ColumnLayout {
                        anchors.top: parent.top; anchors.bottom: parent.bottom
                        anchors.left: parent.left; anchors.right: parent.right
                        anchors.leftMargin: Math.max(14, composeBodyRect.width * (Sta.setByKey(win.composeStationery).bodyL || 0.2)) + 6
                        anchors.rightMargin: 16
                        anchors.topMargin: 12; anchors.bottomMargin: 12
                        spacing: 0

                        // masthead
                        Column {
                            Layout.fillWidth: true
                            spacing: 3
                            Canvas {
                                id: crestCanvas
                                width: 54; height: 28
                                renderStrategy: Canvas.Cooperative
                                onPaint: {
                                    var ctx = getContext("2d")
                                    ctx.reset()
                                    Sta.crestMark(ctx, width, height, Sta.setByKey(win.composeStationery).nameC)
                                }
                            }
                            Text {
                                text: mail.accountRole.length > 0 ? mail.accountRole : mail.accountName
                                color: Sta.setByKey(win.composeStationery).nameC
                                font.family: m.display; font.bold: true; font.pixelSize: k.fs(14)
                            }
                            Text {
                                width: parent.width; horizontalAlignment: Text.AlignRight
                                text: Qt.formatDate(new Date(), "MMMM d, yyyy")
                                color: Sta.setByKey(win.composeStationery).dark ? k.gilt5 : k.gilt1
                                font.family: m.garamond; font.italic: true; font.pixelSize: k.fs(11)
                            }
                            Item { width: 1; height: 4 }
                            Text {
                                text: Sta.setByKey(win.composeStationery).sal || "My dear friend,"
                                color: Sta.setByKey(win.composeStationery).dark ? k.surfaceAlt : m.ink
                                font.family: m.garamond; font.italic: true; font.pixelSize: k.fs(13)
                            }
                            Item { width: 1; height: 6 }
                        }

                        // body — user types here
                        Flickable {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            contentHeight: bodyEdit.implicitHeight; clip: true
                            TextEdit {
                                id: bodyEdit
                                width: parent.width
                                text: ""
                                font.family: m.garamond; font.pixelSize: k.fs(15)
                                color: Sta.setByKey(win.composeStationery).dark ? k.surfaceAlt : m.ink
                                wrapMode: TextEdit.Wrap; selectByMouse: true
                                onTextChanged: composeBody = text
                            }
                        }

                        // footer — signoff + script signature
                        Column {
                            Layout.fillWidth: true
                            spacing: 1
                            Item { width: 1; height: 8 }
                            Text {
                                text: Sta.setByKey(win.composeStationery).signoff || "Yours sincerely,"
                                color: Sta.setByKey(win.composeStationery).dark ? k.surfaceAlt : m.ink
                                font.family: m.garamond; font.italic: true; font.pixelSize: k.fs(13)
                            }
                            Text {
                                text: mail.accountRole.length > 0 ? mail.accountRole : mail.accountName
                                color: Sta.setByKey(win.composeStationery).nameC
                                font.family: m.serif; font.italic: true; font.pixelSize: k.fs(26)
                            }
                            Text {
                                visible: mail.accountSignature.length > 0
                                text: mail.accountSignature
                                color: Sta.setByKey(win.composeStationery).dark ? k.surfaceAlt : m.inkSoft
                                font.family: m.fell; font.italic: true; font.pixelSize: k.fs(12)
                            }
                        }
                    }
                }
                // foot
                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: 64; color: m.paper2
                    Rectangle { anchors.top: parent.top; width: parent.width; height:1; color: m.gilt1 }
                    Row { anchors.left: parent.left; anchors.leftMargin: 20; anchors.verticalCenter: parent.verticalCenter; spacing: 8
                        Text { text: Sta.setByKey(win.composeStationery).name || "Stationery"
                               font.family: m.fell; font.italic: true; font.pixelSize: k.fs(12); color: m.inkSoft
                               anchors.verticalCenter: parent.verticalCenter }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            width: 34; height: 26; radius: 4; clip: true
                            border.color: m.gilt1; border.width: 1
                            Canvas {
                                id: stationeryThumb
                                anchors.fill: parent; renderStrategy: Canvas.Cooperative
                                Component.onCompleted: requestPaint()
                                onPaint: { var c=getContext("2d"); c.reset(); Sta.setByKey(win.composeStationery).paint(c,width,height) }
                            }
                        }
                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            height: 26; width: stnLbl.implicitWidth + 16; radius: 6
                            border.color: stnHov.hovered ? m.gilt3 : m.gilt1; border.width: 1.5
                            color: Qt.rgba(0,0,0,0.06)
                            Text { id: stnLbl; text: "Choose…"; font.family: m.titles; font.pixelSize: k.fs(11)
                                   color: m.inkLabel; anchors.centerIn: parent }
                            HoverHandler { id: stnHov }
                            TapHandler { onTapped: stationeryDrawer.open() }
                        }
                    }
                    // send
                    Rectangle {
                        anchors.right: parent.right; anchors.rightMargin: 20; anchors.verticalCenter: parent.verticalCenter
                        height: 42; width: sendRow.implicitWidth + 30; radius: 21
                        border.color: m.gilt0; border.width: 2
                        gradient: Gradient { orientation: Gradient.Vertical
                            GradientStop{position:0;color: sendHov.hovered ? m.verd3 : m.verd2} GradientStop{position:1;color:m.verd1} }
                        Row { id: sendRow; anchors.centerIn: parent; spacing: 11
                            Text { text:"Send"; font.family: m.titles; font.weight: Font.DemiBold
                                   font.pixelSize: k.fs(14); color: m.gilt5; font.letterSpacing: 1
                                   anchors.verticalCenter: parent.verticalCenter }
                            WaxSeal { width: 28; height: 28; anchors.verticalCenter: parent.verticalCenter
                                Hummingbird { anchors.centerIn: parent; width: 17; height: 17; tint: m.gilt5 } } }
                        HoverHandler { id: sendHov }
                        TapHandler { onTapped: win.despatch() }
                    }
                }
            }

    */ // END REMOVED compose overlay

    // compose field bindings
    property string composeTo: ""
    property string composeCc: ""
    property string composeBcc: ""
    property string composeSubj: ""
    property string composeBody: ""
    // Step C/Task #8/#9: [{path, name, inline, risky, confirmed}], built by
    // HBWritingDesk's Attach button / drag-drop / paste; sent to
    // MailEngine::sendMessage's new `attachments` param as {path, inline} pairs.
    property var    composeAttachments: []
    // Task #7: undo-send — despatch() is only the actual dispatch call; Send
    // starts a countdown in HBWritingDesk and calls this after it elapses
    // uncancelled.

    // ════════════════════════════════════════════════════════════════════════
    //  ACCOUNT SETUP OVERLAY
    // ════════════════════════════════════════════════════════════════════════
    property bool accountSetupOpen: false

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(k.scrim.r, k.scrim.g, k.scrim.b, 0.62)
        visible: win.accountSetupOpen
        z: 60

        Rectangle {
            id: setupSheet
            width: Math.min(540, win.width - 80)
            height: setupCol.implicitHeight + 48
            anchors.centerIn: parent
            color: m.paper0; radius: 10; border.color: m.gilt0; border.width: 2

            ColumnLayout {
                id: setupCol
                anchors.top: parent.top
                anchors.left: parent.left; anchors.right: parent.right
                anchors.margins: 0
                spacing: 0

                // header
                Rectangle {
                    Layout.fillWidth: true; Layout.preferredHeight: 52
                    radius: 10
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: m.wine3 }
                        GradientStop { position: 1; color: m.wine1 } }
                    Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 2; color: m.gilt3 }
                    Rectangle { anchors.bottom: parent.bottom; anchors.left: parent.left
                                anchors.right: parent.right; height: 10; color: m.wine1 }
                    RowLayout {
                        anchors.fill: parent; anchors.leftMargin: 18; anchors.rightMargin: 18
                        Hummingbird { Layout.preferredWidth: 26; Layout.preferredHeight: 26; tint: m.gilt4 }
                        Item { Layout.preferredWidth: 10 }
                        Column {
                            spacing: 2
                            Text { text: "Account Setup"; font.family: m.display; font.bold: true
                                   font.pixelSize: k.fs(15); color: m.gilt5; font.letterSpacing: 1.5 }
                            Text { text: "Connect your post office"; font.family: m.fell; font.italic: true
                                   font.pixelSize: k.fs(10); color: m.gilt3; font.letterSpacing: 2 }
                        }
                        Item { Layout.fillWidth: true }
                        Text { text: "✕"; color: m.gilt4; font.pixelSize: k.fs(18)
                               visible: mail.accountEmail.length > 0
                               TapHandler { onTapped: win.accountSetupOpen = false } }
                    }
                }

                // form fields
                Column {
                    Layout.fillWidth: true
                    Layout.leftMargin: 24; Layout.rightMargin: 24; Layout.topMargin: 6

                    Repeater {
                        model: [
                            { k: "Name",    ph: "Your Name",               id: "acName"    },
                            { k: "Email",   ph: "you@gmail.com",           id: "acEmail"   },
                            { k: "Station", ph: "e.g. Iron Orchid Station", id: "acStation" },
                            { k: "Password",ph: "App password — 16 chars", id: "acPass"    }
                        ]
                        Rectangle {
                            width: parent.width; height: 50; color: "transparent"
                            Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: m.gilt1 }
                            Row { anchors.fill: parent; spacing: 12
                                Text { text: modelData.k.toUpperCase()
                                       font.family: m.fell; font.italic: true
                                       font.pixelSize: k.fs(12); color: m.inkLabel; font.letterSpacing: 1.5
                                       width: 78; anchors.verticalCenter: parent.verticalCenter }
                                TextInput {
                                    id: setupField
                                    width: parent.width - 94
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.family: m.serif; font.pixelSize: k.fs(16); color: m.ink
                                    clip: true; selectByMouse: true
                                    echoMode: modelData.id === "acPass" ? TextInput.Password : TextInput.Normal
                                    property string fieldId: modelData.id
                                    onTextChanged: {
                                        if (fieldId === "acName")        acSetupName    = text
                                        else if (fieldId === "acEmail")  acSetupEmail   = text
                                        else if (fieldId === "acStation") acSetupStation = text
                                        else                             acSetupPass    = text
                                    }
                                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                           text: modelData.ph; font.family: m.serif; font.pixelSize: k.fs(16)
                                           color: m.inkSoft; opacity: 0.55
                                           visible: !setupField.text.length && !setupField.activeFocus }
                                }
                            }
                        }
                    }

                    // advanced toggle
                    Item { width: parent.width; height: 10 }
                    Rectangle {
                        width: parent.width; height: 34; color: "transparent"
                        Row { anchors.verticalCenter: parent.verticalCenter; spacing: 8
                            Text { text: win.acSetupAdvanced ? "▾ Advanced" : "▸ Advanced (IMAP / SMTP)"
                                   font.family: m.fell; font.italic: true; font.pixelSize: k.fs(13)
                                   color: m.inkLabel; font.letterSpacing: 1 }
                            TapHandler { onTapped: win.acSetupAdvanced = !win.acSetupAdvanced }
                        }
                        Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: m.gilt1; opacity: 0.4 }
                    }

                    // advanced fields
                    Column {
                        width: parent.width
                        visible: win.acSetupAdvanced
                        spacing: 0
                        Repeater {
                            model: [
                                { k: "IMAP Host", ph: "imap.gmail.com", id: "imapHost" },
                                { k: "IMAP Port", ph: "993",            id: "imapPort" },
                                { k: "SMTP Host", ph: "smtp.gmail.com", id: "smtpHost" },
                                { k: "SMTP Port", ph: "465",            id: "smtpPort" }
                            ]
                            Rectangle {
                                width: parent.width; height: 46; color: "transparent"
                                Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: m.gilt1; opacity: 0.5 }
                                Row { anchors.fill: parent; spacing: 12
                                    Text { text: modelData.k.toUpperCase()
                                           font.family: m.fell; font.italic: true
                                           font.pixelSize: k.fs(11); color: m.inkSoft; font.letterSpacing: 1
                                           width: 78; anchors.verticalCenter: parent.verticalCenter }
                                    TextInput {
                                        id: advField
                                        width: parent.width - 94
                                        anchors.verticalCenter: parent.verticalCenter
                                        font.family: m.serif; font.pixelSize: k.fs(15); color: m.ink
                                        clip: true; selectByMouse: true
                                        property string fieldId: modelData.id
                                        onTextChanged: {
                                            if (fieldId === "imapHost") acSetupImapHost = text
                                            else if (fieldId === "imapPort") acSetupImapPort = parseInt(text) || 993
                                            else if (fieldId === "smtpHost") acSetupSmtpHost = text
                                            else acSetupSmtpPort = parseInt(text) || 465
                                        }
                                        Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                               text: modelData.ph; font.family: m.serif; font.pixelSize: k.fs(15)
                                               color: m.inkSoft; opacity: 0.5
                                               visible: !advField.text.length && !advField.activeFocus }
                                    }
                                }
                            }
                        }
                    }
                    Item { width: parent.width; height: 6 }
                }

                // ── or sign in with Google ──────────────────────────────
                RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: 24; Layout.rightMargin: 24
                    Layout.preferredHeight: 30
                    Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: m.gilt1; opacity: 0.4 }
                    Text { text: " or "; font.family: m.fell; font.italic: true; font.pixelSize: k.fs(13)
                           color: m.inkSoft }
                    Rectangle { Layout.fillWidth: true; implicitHeight: 1; color: m.gilt1; opacity: 0.4 }
                }
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: 4
                    implicitHeight: 44; implicitWidth: googleRow.implicitWidth + 40; radius: 22
                    border.color: oauthHov.hovered ? m.gilt3 : m.gilt1; border.width: 2
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: oauthHov.hovered ? m.paper0 : m.paper1 }
                        GradientStop { position: 1; color: m.paper2 } }
                    Row { id: googleRow; anchors.centerIn: parent; spacing: 11
                        Text { text: "Sign in with Google"; font.family: m.titles
                               font.weight: Font.DemiBold; font.pixelSize: k.fs(14)
                               color: m.ink; font.letterSpacing: 0.5
                               anchors.verticalCenter: parent.verticalCenter }
                        WaxSeal { width: 26; height: 26; anchors.verticalCenter: parent.verticalCenter
                            Hummingbird { anchors.centerIn: parent; width: 15; height: 15; tint: m.gilt5 } } }
                    HoverHandler { id: oauthHov }
                    TapHandler { onTapped: { win.accountSetupOpen = false; mail.startOAuthFlow() } }
                }

                // connect button
                Item { Layout.fillWidth: true; Layout.preferredHeight: 24 }
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: 24
                    implicitHeight: 44; implicitWidth: connectRow.implicitWidth + 40; radius: 22
                    border.color: m.gilt0; border.width: 2
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: cnHov.hovered ? m.verd3 : m.verd2 }
                        GradientStop { position: 1; color: m.verd1 } }
                    Row { id: connectRow; anchors.centerIn: parent; spacing: 11
                        Text { text: "Connect"; font.family: m.titles; font.weight: Font.DemiBold
                               font.pixelSize: k.fs(14); color: m.gilt5; font.letterSpacing: 1
                               anchors.verticalCenter: parent.verticalCenter }
                        WaxSeal { width: 26; height: 26; anchors.verticalCenter: parent.verticalCenter
                            Hummingbird { anchors.centerIn: parent; width: 15; height: 15; tint: m.gilt5 } }
                    }
                    HoverHandler { id: cnHov }
                    TapHandler {
                        onTapped: {
                            var ih = win.acSetupImapHost.length ? win.acSetupImapHost : "imap.gmail.com"
                            var sh = win.acSetupSmtpHost.length ? win.acSetupSmtpHost : "smtp.gmail.com"
                            mail.saveAccount(win.acSetupName, win.acSetupEmail, win.acSetupPass,
                                             ih, win.acSetupImapPort, sh, win.acSetupSmtpPort,
                                             win.acSetupStation)
                            win.accountSetupOpen = false
                        }
                    }
                }

                // ── Role / Title ───────────────────────────────────────
                Item { Layout.fillWidth: true; Layout.preferredHeight: 12 }
                Rectangle { Layout.fillWidth: true; Layout.leftMargin: 24; Layout.rightMargin: 24
                            implicitHeight: 1; color: m.gilt1; opacity: 0.35 }
                Item { Layout.fillWidth: true; Layout.preferredHeight: 8 }

                Column {
                    Layout.fillWidth: true
                    Layout.leftMargin: 24; Layout.rightMargin: 24
                    spacing: 8
                    Text { text: "ROLE / TITLE"; font.family: m.fell; font.italic: true
                           font.pixelSize: k.fs(11); color: m.inkLabel; font.letterSpacing: 2 }
                    Rectangle {
                        width: parent.width; height: 38
                        color: m.paper0; radius: 4; border.color: m.gilt1; border.width: 1
                        TextInput {
                            id: roleEdit
                            anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10
                            verticalAlignment: TextInput.AlignVCenter
                            text: win.acSetupRole
                            font.family: m.serif; font.pixelSize: k.fs(13); color: m.ink
                            selectByMouse: true
                            onTextChanged: win.acSetupRole = text
                            Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
                                   text: "Your title or house (optional)…"
                                   font.family: m.serif; font.pixelSize: k.fs(13)
                                   color: m.inkSoft; opacity: 0.5
                                   visible: !roleEdit.text.length && !roleEdit.activeFocus }
                        }
                    }
                }

                // ── Signature ──────────────────────────────────────────
                Item { Layout.fillWidth: true; Layout.preferredHeight: 12 }
                Rectangle { Layout.fillWidth: true; Layout.leftMargin: 24; Layout.rightMargin: 24
                            implicitHeight: 1; color: m.gilt1; opacity: 0.35 }
                Item { Layout.fillWidth: true; Layout.preferredHeight: 8 }

                Column {
                    Layout.fillWidth: true
                    Layout.leftMargin: 24; Layout.rightMargin: 24
                    spacing: 8
                    Text { text: "SIGNATURE"; font.family: m.fell; font.italic: true
                           font.pixelSize: k.fs(11); color: m.inkLabel; font.letterSpacing: 2 }
                    Rectangle {
                        width: parent.width; height: 72
                        color: m.paper0; radius: 4; border.color: m.gilt1; border.width: 1
                        Flickable {
                            anchors.fill: parent; anchors.margins: 8
                            contentHeight: sigEdit.implicitHeight; clip: true
                            TextEdit {
                                id: sigEdit
                                width: parent.width
                                text: win.acSetupSignature
                                font.family: m.serif; font.pixelSize: k.fs(13); color: m.ink
                                wrapMode: TextEdit.Wrap; selectByMouse: true
                                onTextChanged: win.acSetupSignature = text
                                Text { anchors.fill: parent; verticalAlignment: Text.AlignTop
                                       topPadding: 2
                                       text: "Your name, title, or closing words…"
                                       font.family: m.serif; font.pixelSize: k.fs(13)
                                       color: m.inkSoft; opacity: 0.5
                                       visible: !sigEdit.text.length && !sigEdit.activeFocus }
                            }
                        }
                    }
                }

                Item { Layout.fillWidth: true; Layout.preferredHeight: 10 }
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.bottomMargin: 28
                    implicitHeight: 38; implicitWidth: sigBtnRow.implicitWidth + 32; radius: 19
                    border.color: sigBtnHov.hovered ? m.gilt3 : m.gilt1; border.width: 1.5
                    gradient: Gradient { orientation: Gradient.Vertical
                        GradientStop { position: 0; color: sigBtnHov.hovered ? m.paper0 : m.paper1 }
                        GradientStop { position: 1; color: m.paper2 } }
                    Row { id: sigBtnRow; anchors.centerIn: parent; spacing: 8
                        Text { text: "Save"; font.family: m.titles
                               font.weight: Font.DemiBold; font.pixelSize: k.fs(13)
                               color: m.inkLabel; font.letterSpacing: 0.5
                               anchors.verticalCenter: parent.verticalCenter } }
                    HoverHandler { id: sigBtnHov }
                    TapHandler { onTapped: {
                        mail.saveRole(win.acSetupRole)
                        mail.saveSignature(win.acSetupSignature)
                        toastTxt.text = "Saved"
                        toast.toastShown = true; toastTimer.restart()
                    } }
                }

                Connections { target: win; function onAccountSetupOpenChanged() {
                    if (win.accountSetupOpen) {
                        win.acSetupRole = mail.accountRole
                        roleEdit.text = mail.accountRole
                        win.acSetupSignature = mail.accountSignature
                        sigEdit.text = mail.accountSignature
                    }
                } }
            }
        }
    }

    // account setup field state
    property string acSetupName: ""
    property string acSetupEmail: ""
    property string acSetupStation: ""
    property string acSetupPass: ""
    property string acSetupRole: ""
    property string acSetupSignature: ""
    property bool   acSetupAdvanced: false
    property string acSetupImapHost: ""
    property int    acSetupImapPort: 993
    property string acSetupSmtpHost: ""
    property int    acSetupSmtpPort: 465

    function despatch() {
        if (composeTo.trim() === "") return
        win.mailPaneView = "gallery"
        flier.launch()
        // Attachments go over the wire as {path,inline} — strip the QML-only
        // bookkeeping fields (name/risky/confirmed) before handing to the engine.
        var wireAttachments = []
        for (var i = 0; i < composeAttachments.length; i++) {
            wireAttachments.push({ path: composeAttachments[i].path, inline: !!composeAttachments[i].inline })
        }
        mail.sendMessage(composeTo, composeCc, composeBcc, composeSubj, composeBody,
                         composeStationery, composeStationeryImage, wireAttachments)
        composeStationeryImage = ""
        composeAttachments = []
    }

    // ════════════════════════════════════════════════════════════════════════
    //  FLYING HUMMINGBIRD
    // ════════════════════════════════════════════════════════════════════════
    Item {
        id: flier
        width: 48; height: 48; z: 80; visible: false
        property real t: 0     // 0..1 flight progress
        function launch() {
            visible = true; flightAnim.restart(); wingTimer.running = true
        }
        // path: start bottom-centre (near send), arc up to top-left, shrink+fade
        x: win.width*0.5 - 24 + (-(win.width*0.5)+ -20) * (1 - Math.pow(1-t,2))
        y: win.height - 120 + (-(win.height) + 40) * (1 - Math.pow(1-t,2)) - Math.sin(t*Math.PI)*140
        opacity: t > 0.8 ? (1 - t)/0.2 : 1
        scale: 1 - 0.4*t
        rotation: -12 - t*16
        Hummingbird { id: flierBird; anchors.fill: parent; tint: m.gilt3 }
        Timer { id: wingTimer; interval: 80; repeat: true; running: false
                onTriggered: flierBird.wingPhase = flierBird.wingPhase > 0.5 ? 0 : 1 }
        NumberAnimation { id: flightAnim; target: flier; property: "t"; from: 0; to: 1
            duration: 1150; easing.type: Easing.OutQuad
            onFinished: { flier.visible = false; flier.t = 0; wingTimer.running = false } }
    }

    // toast on send finish
    Rectangle {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        y: toastShown ? win.height - 90 : win.height + 20
        width: toastTxt.implicitWidth + 44 + win.px(20); height: toastTxt.implicitHeight + 20; radius: height/2; z: 90
        color: m.wine2; border.color: m.gilt3; border.width: 1.5
        property bool toastShown: false
        Behavior on y { NumberAnimation { duration: 280; easing.type: Easing.OutCubic } }
        Row { anchors.centerIn: parent; spacing: 10
            Hummingbird { width: 20; height: 20; tint: m.gilt4; anchors.verticalCenter: parent.verticalCenter }
            Text { id: toastTxt; text: ""; font.family: m.serif; font.pixelSize: k.fs(15); color: m.gilt5
                   anchors.verticalCenter: parent.verticalCenter } }
        Timer { id: toastTimer; interval: 3000; onTriggered: toast.toastShown = false }
    }

    Connections {
        target: mail
        function onSendFinished(ok, message) {
            toastTxt.text = ok ? message : ("⚠ " + message)
            toast.toastShown = true; toastTimer.restart()
        }
        function onErrorOccurred(message) {
            toastTxt.text = "⚠ " + message
            toast.toastShown = true; toastTimer.restart()
        }
        function onOauthFlowStarted() {
            toastTxt.text = "Opening browser for Google sign-in…"
            toast.toastShown = true; toastTimer.restart()
        }
        function onOauthFlowFinished(ok, email) {
            if (ok) {
                win.accountSetupOpen = false
                toastTxt.text = "Connected as " + email
                toast.toastShown = true; toastTimer.restart()
            } else {
                toastTxt.text = "Sign-in failed — see status bar"
                toast.toastShown = true; toastTimer.restart()
            }
        }
        function onNeedsReauthorization() {
            toastTxt.text = "Gmail rejected access — please sign in with Google again"
            toast.toastShown = true; toastTimer.restart()
            win.accountSetupOpen = true
        }
    }

    // ── Petal welcome toast ──────────────────────────────────────────────
    Item {
        id: petalCard
        anchors.bottom: parent.bottom; anchors.bottomMargin: 90
        anchors.horizontalCenter: parent.horizontalCenter
        width: 340; height: 120; z: 95
        opacity: 0; visible: opacity > 0

        Rectangle {
            anchors.fill: parent; radius: 14
            color: m.paper1; border.color: m.gilt2; border.width: 1.5
            layer.enabled: true
            layer.effect: MultiEffect { shadowEnabled: true; shadowBlur: 0.4; shadowColor: Qt.rgba(0,0,0,0.45) }

            Row {
                anchors.fill: parent; anchors.margins: 16; spacing: 12
                Hummingbird { width: 44; height: 44; tint: m.wine3; anchors.verticalCenter: parent.verticalCenter }
                Column {
                    anchors.verticalCenter: parent.verticalCenter; spacing: 4; width: parent.width - 56
                    Text { text: "Hello, Neighbor!"; font.family: m.display; font.bold: true
                           font.pixelSize: k.fs(15); color: m.wineText2; font.letterSpacing: 1 }
                    Text { text: "Follow Petal — she'll find your messages,\ndeliveries, and surprises in your mailbox."
                           font.family: m.garamond; font.pixelSize: k.fs(12); color: m.ink
                           wrapMode: Text.WordWrap; width: parent.width }
                    Text { text: "Don’t show again"; font.family: m.fell; font.italic: true
                           font.pixelSize: k.fs(11); color: m.inkLabel
                           TapHandler { onTapped: { mail.setShowWelcome(false); petalHide.restart() } } }
                }
            }
        }

        NumberAnimation { id: petalShow; target: petalCard; property: "opacity"; to: 1; duration: 400; easing.type: Easing.OutCubic
            onFinished: petalHoldTimer.restart() }
        NumberAnimation { id: petalHide; target: petalCard; property: "opacity"; to: 0; duration: 600; easing.type: Easing.InCubic }
        Timer { id: petalHoldTimer; interval: 5000; onTriggered: petalHide.restart() }
    }

    Component.onCompleted: {
        if (!mail.accountEmail.length) {
            win.accountSetupOpen = true
        }
        if (mail.showWelcome) Qt.callLater(function() { petalShow.start() })
        // --compose CLI: pre-fill subject/body and open the writing desk.
        // composeRequest is only set when launched from another NCDE app (e.g. VerdantFolio).
        if (typeof composeRequest !== "undefined" && composeRequest.pending) {
            win.composeSubj = composeRequest.subject
            win.composeBody = composeRequest.body
                + (composeRequest.attachPath.length
                   ? "\n\n— Résumé attached:\n" + composeRequest.attachPath
                   : "")
            Qt.callLater(function() { win.mailPaneView = "writing" })
        }
    }
}
