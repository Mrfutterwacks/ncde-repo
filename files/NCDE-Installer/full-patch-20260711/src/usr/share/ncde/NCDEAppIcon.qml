// NCDEAppIcon.qml — NCDE QML App Icon Library
// Covers ~50 common Linux desktop apps drawn in Canvas.
// Unknown apps get a consistent hash-color initial tile.
// Matched on appName substring (case-insensitive).

import QtQuick 2.15

Canvas {
    id: root
    renderStrategy: Canvas.Cooperative
    property string appName: ""
    property string appIcon: ""
    property int    size:    48
    property color  accentColor: ncde.accent
    property color  glowColor:   ncde.glow

    width: size; height: size

    onAppNameChanged:    requestPaint()
    onAppIconChanged:    requestPaint()
    onSizeChanged:       requestPaint()
    onAccentColorChanged: requestPaint()
    onGlowColorChanged:  requestPaint()
    Component.onCompleted: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.clearRect(0, 0, width, height)
        var s = Math.min(width, height)
        // Combine name + icon field so reverse-DNS apps match correctly
        var n = (appName + " " + appIcon).toLowerCase()

        // ── Browsers ─────────────────────────────────────────────
        if      (n.indexOf("firefox") >= 0)                    drawFirefox(ctx,s)
        else if (n.indexOf("chrom") >= 0)                      drawChromium(ctx,s)
        else if (n.indexOf("brave") >= 0)                      drawBrave(ctx,s)
        else if (n.indexOf("opera") >= 0)                      drawOpera(ctx,s)
        else if (n.indexOf("epiphany") >= 0 ||
                 n.indexOf("gnome web") >= 0)                  drawEpiphany(ctx,s)
        // ── Terminals ─────────────────────────────────────────────
        else if (n.indexOf("terminal") >= 0 ||
                 n.indexOf("alacritty") >= 0 ||
                 n.indexOf("konsole") >= 0 ||
                 n.indexOf("kitty") >= 0 ||
                 n.indexOf("tilix") >= 0)                      drawTerminal(ctx,s)
        // ── File managers ─────────────────────────────────────────
        else if (n.indexOf("orchid") >= 0)                     drawFiles(ctx,s)
        // ── Text editors ──────────────────────────────────────────
        else if (n.indexOf("geany") >= 0)                      drawGeany(ctx,s)
        else if (n.indexOf("vscode") >= 0 ||
                 n.indexOf("code") >= 0 ||
                 n.indexOf("vscodium") >= 0)                   drawVSCode(ctx,s)
        else if (n.indexOf("verve") >= 0 ||
                 n.indexOf("kate") >= 0 ||
                 n.indexOf("gedit") >= 0 ||
                 n.indexOf("mousepad") >= 0 ||
                 n.indexOf("text editor") >= 0)                drawTextEditor(ctx,s)
        else if (n.indexOf("sublime") >= 0)                    drawSublime(ctx,s)
        // ── Media players ─────────────────────────────────────────
        else if (n.indexOf("spotify") >= 0)                    drawSpotify(ctx,s)
        else if (n.indexOf("vlc") >= 0)                        drawVLC(ctx,s)
        else if (n.indexOf("mpv") >= 0)                        drawMPV(ctx,s)
        else if (n.indexOf("rhythmbox") >= 0 ||
                 n.indexOf("clementine") >= 0 ||
                 n.indexOf("amarok") >= 0 ||
                 n.indexOf("strawberry") >= 0)                 drawMusicPlayer(ctx,s)
        else if (n.indexOf("audacity") >= 0)                   drawAudacity(ctx,s)
        // ── Graphics ─────────────────────────────────────────────
        else if (n.indexOf("gimp") >= 0)                       drawGIMP(ctx,s)
        else if (n.indexOf("inkscape") >= 0)                   drawInkscape(ctx,s)
        else if (n.indexOf("krita") >= 0)                      drawKrita(ctx,s)
        else if (n.indexOf("shotwell") >= 0 ||
                 n.indexOf("gthumb") >= 0 ||
                 n.indexOf("eog") >= 0 ||
                 n.indexOf("image viewer") >= 0)               drawImageViewer(ctx,s)
        // ── LibreOffice ───────────────────────────────────────────
        else if (n.indexOf("writer") >= 0)                     drawLOWriter(ctx,s)
        else if (n.indexOf("calc") >= 0 ||
                 n.indexOf("kcalc") >= 0 ||
                 n.indexOf("abacus") >= 0)                     drawLOCalc(ctx,s)
        else if (n.indexOf("impress") >= 0)                    drawLOImpress(ctx,s)
        else if (n.indexOf("draw") >= 0 &&
                 n.indexOf("libre") >= 0)                      drawLODraw(ctx,s)
        else if (n.indexOf("libreoffice") >= 0)                drawLibreOffice(ctx,s)
        // ── PDF / Docs ────────────────────────────────────────────
        else if (n.indexOf("okular") >= 0 ||
                 n.indexOf("evince") >= 0 ||
                 n.indexOf("pdf") >= 0 ||
                 n.indexOf("document viewer") >= 0)            drawPDFViewer(ctx,s)
        // ── System tools ─────────────────────────────────────────
        else if (n.indexOf("system monitor") >= 0 ||
                 n.indexOf("htop") >= 0 ||
                 n.indexOf("task manager") >= 0)               drawSysMon(ctx,s)
        else if (n.indexOf("settings") >= 0 ||
                 n.indexOf("control") >= 0 ||
                 n.indexOf("preferences") >= 0)                drawSettings(ctx,s)
        else if (n.indexOf("bluetooth") >= 0)                  drawBluetooth(ctx,s)
        else if (n.indexOf("network") >= 0)                    drawNetwork(ctx,s)
        else if (n.indexOf("software") >= 0 ||
                 n.indexOf("package") >= 0 ||
                 n.indexOf("discover") >= 0 ||
                 n.indexOf("synaptic") >= 0)                   drawSoftware(ctx,s)
        else if (n.indexOf("disk") >= 0 ||
                 n.indexOf("gparted") >= 0 ||
                 n.indexOf("partition") >= 0)                  drawDisk(ctx,s)
        else if (n.indexOf("archive") >= 0 ||
                 n.indexOf("ark") >= 0 ||
                 n.indexOf("file-roller") >= 0)                drawArchive(ctx,s)
        // ── Games / Gaming ────────────────────────────────────────
        else if (n.indexOf("steam") >= 0)                      drawSteam(ctx,s)
        else if (n.indexOf("lutris") >= 0)                     drawLutris(ctx,s)
        else if (n.indexOf("heroic") >= 0)                     drawHeroic(ctx,s)
        else if (n.indexOf("protonup") >= 0 ||
                 n.indexOf("pupgui") >= 0)                     drawProtonUp(ctx,s)
        // ── Communication ─────────────────────────────────────────
        else if (n.indexOf("discord") >= 0)                    drawDiscord(ctx,s)
        else if (n.indexOf("telegram") >= 0)                   drawTelegram(ctx,s)
        else if (n.indexOf("signal") >= 0)                     drawSignal(ctx,s)
        else if (n.indexOf("slack") >= 0)                      drawSlack(ctx,s)
        else if (n.indexOf("zoom") >= 0)                       drawZoom(ctx,s)
        else if (n.indexOf("thunderbird") >= 0 ||
                 n.indexOf("mail") >= 0 ||
                 n.indexOf("kmail") >= 0)                      drawMail(ctx,s)
        // ── Dev tools ─────────────────────────────────────────────
        else if (n.indexOf("git") >= 0 ||
                 n.indexOf("gitg") >= 0 ||
                 n.indexOf("gitkraken") >= 0)                  drawGit(ctx,s)
        else if (n.indexOf("docker") >= 0 ||
                 n.indexOf("podman") >= 0)                     drawDocker(ctx,s)
        else if (n.indexOf("database") >= 0 ||
                 n.indexOf("dbeaver") >= 0 ||
                 n.indexOf("beekeeper") >= 0)                  drawDB(ctx,s)
        // ── Misc ──────────────────────────────────────────────────
        else if (n.indexOf("flatseal") >= 0)                   drawFlatseal(ctx,s)
        else if (n.indexOf("calculator") >= 0)                 drawLOCalc(ctx,s)
        else if (n.indexOf("calendar") >= 0)                   drawCalendar(ctx,s)
        else if (n.indexOf("trash") >= 0)                      drawTrash(ctx,s)
        // ── Screenshot tools ──────────────────────────────────────
        else if (n.indexOf("flameshot") >= 0 || n.indexOf("screengrab") >= 0 ||
                 n.indexOf("screenshot") >= 0 || n.indexOf("screenshooter") >= 0 ||
                 n.indexOf("spectacle") >= 0 || n.indexOf("shutter") >= 0)
                                                               drawScreenshot(ctx,s)
        // ── Screen recording ──────────────────────────────────────
        else if (n.indexOf("kooha") >= 0 || n.indexOf("recorder") >= 0 ||
                 n.indexOf("obs") >= 0 || n.indexOf("recordmydesktop") >= 0)
                                                               drawScreenRecord(ctx,s)
        // ── Audio / volume ────────────────────────────────────────
        else if (n.indexOf("pavucontrol") >= 0 || n.indexOf("pulseaudio") >= 0 ||
                 n.indexOf("pasystray") >= 0 || n.indexOf("volume control") >= 0)
                                                               drawPavucontrol(ctx,s)
        // ── Video editing ─────────────────────────────────────────
        else if (n.indexOf("kdenlive") >= 0 || n.indexOf("openshot") >= 0 ||
                 n.indexOf("pitivi") >= 0 || n.indexOf("video edit") >= 0)
                                                               drawKdenlive(ctx,s)
        // ── Colour picking ────────────────────────────────────────
        else if (n.indexOf("color") >= 0 || n.indexOf("colour") >= 0 ||
                 n.indexOf("kcolorscheme") >= 0 || n.indexOf("colorselector") >= 0)
                                                               drawColourPicker(ctx,s)
        // ── Virtualisation ────────────────────────────────────────
        else if (n.indexOf("virt-manager") >= 0 || n.indexOf("virtmanager") >= 0 ||
                 n.indexOf("virtual machine") >= 0 || n.indexOf("virtualbox") >= 0 ||
                 n.indexOf("qemu") >= 0 || n.indexOf("remote-viewer") >= 0)
                                                               drawVirtManager(ctx,s)
        // ── Wine ──────────────────────────────────────────────────
        else if (n.indexOf("wine") >= 0)                       drawWine(ctx,s)
        // ── Notes / stickies ──────────────────────────────────────
        else if (n.indexOf("notes") >= 0 || n.indexOf("sticky") >= 0 ||
                 n.indexOf("xfce4-notes") >= 0)                drawNotes(ctx,s)
        // ── Clipboard ─────────────────────────────────────────────
        else if (n.indexOf("clipman") >= 0 || n.indexOf("clipboard") >= 0 ||
                 n.indexOf("copyq") >= 0)                      drawClipboard(ctx,s)
        // ── Disc burning ──────────────────────────────────────────
        else if (n.indexOf("xfburn") >= 0 || n.indexOf("brasero") >= 0 ||
                 n.indexOf("burner") >= 0 || n.indexOf("k3b") >= 0)
                                                               drawXfburn(ctx,s)
        // ── Wallpaper manager ─────────────────────────────────────
        else if (n.indexOf("nitrogen") >= 0 || n.indexOf("waytrogen") >= 0 ||
                 n.indexOf("wallpaper") >= 0 || n.indexOf("feh") >= 0)
                                                               drawNitrogen(ctx,s)
        // ── Dock ──────────────────────────────────────────────────
        else if (n.indexOf("cairo-dock") >= 0 || n.indexOf("plank") >= 0 ||
                 n.indexOf("novabar") >= 0)                    drawDock(ctx,s)
        // ── About / info ──────────────────────────────────────────
        else if (n.indexOf("about") >= 0 || n.indexOf("lxqt-about") >= 0 ||
                 n.indexOf("mate-about") >= 0 || n.indexOf("xfce4-about") >= 0)
                                                               drawAbout(ctx,s)
        // ── Accessibility ─────────────────────────────────────────
        else if (n.indexOf("access") >= 0 || n.indexOf("a11y") >= 0)
                                                               drawAccessibility(ctx,s)
        // ── Scribus DTP ───────────────────────────────────────────
        else if (n.indexOf("scribus") >= 0)                    drawScribus(ctx,s)
        // ── Extended image viewers ────────────────────────────────
        else if (n.indexOf("gwenview") >= 0 || n.indexOf("ristretto") >= 0 ||
                 n.indexOf("lximage") >= 0 || n.indexOf("viewnior") >= 0 ||
                 n.indexOf("nomacs") >= 0 || n.indexOf("geeqie") >= 0 ||
                 n.indexOf("image viewer") >= 0)               drawImageViewer(ctx,s)
        // ── Extended text editors ─────────────────────────────────
        else if (n.indexOf("featherpad") >= 0 || n.indexOf("xfce4-dict") >= 0 ||
                 n.indexOf("mousepad") >= 0 || n.indexOf("kwrite") >= 0)
                                                               drawTextEditor(ctx,s)
        // ── Extended music ────────────────────────────────────────
        else if (n.indexOf("elisa") >= 0 || n.indexOf("lollypop") >= 0 ||
                 n.indexOf("parole") >= 0)                     drawMusicPlayer(ctx,s)
        // ── Extended system monitor ───────────────────────────────
        else if (n.indexOf("qps") >= 0 || n.indexOf("conky") >= 0 ||
                 n.indexOf("taskmanager") >= 0 || n.indexOf("xfce4-task") >= 0 ||
                 n.indexOf("plasma-system") >= 0)              drawSysMon(ctx,s)
        // ── All settings/config/appearance catch-all ──────────────
        else if (n.indexOf("kcm_") >= 0 || n.indexOf("budgie-") >= 0 ||
                 n.indexOf("lxqt-config") >= 0 || n.indexOf("xfce4-settings") >= 0 ||
                 n.indexOf("xfce4-accessibility") >= 0 || n.indexOf("xfce-") >= 0 ||
                 n.indexOf("mate-") >= 0 || n.indexOf("systemsettings") >= 0 ||
                 n.indexOf("kdesystemsettings") >= 0 || n.indexOf("appearance") >= 0 ||
                 n.indexOf("kvantum") >= 0 || n.indexOf("obconf") >= 0 ||
                 n.indexOf("lxappearance") >= 0 || n.indexOf("qt5ct") >= 0 ||
                 n.indexOf("qt6ct") >= 0)                      drawSettings(ctx,s)
        // ── Extended file managers ────────────────────────────────
        else if (n.indexOf("pcmanfm") >= 0 || n.indexOf("caja") >= 0 ||
                 n.indexOf("rox") >= 0)                        drawFiles(ctx,s)
        // ── Extended archives ─────────────────────────────────────
        else if (n.indexOf("lxqt-archiver") >= 0 || n.indexOf("engrampa") >= 0 ||
                 n.indexOf("xarchiver") >= 0)                  drawArchive(ctx,s)
        // ── Extended terminals ────────────────────────────────────
        else if (n.indexOf("uxterm") >= 0 || n.indexOf("xterm") >= 0 ||
                 n.indexOf("qterminal") >= 0 || n.indexOf("lxterminal") >= 0)
                                                               drawTerminal(ctx,s)
        // ── IDE / dev ─────────────────────────────────────────────
        else if (n.indexOf("gambas") >= 0 || n.indexOf("glade") >= 0 ||
                 n.indexOf("cmake-gui") >= 0 || n.indexOf("eric") >= 0)
                                                               drawVSCode(ctx,s)
        else                                                   drawDefault(ctx,s)
    }

    // ══════════════════════════════════════════════════════════════
    // HELPERS
    // ══════════════════════════════════════════════════════════════
    function rrect(ctx,x,y,w,h,r) {
        ctx.beginPath()
        ctx.moveTo(x+r,y); ctx.lineTo(x+w-r,y); ctx.arcTo(x+w,y,x+w,y+r,r)
        ctx.lineTo(x+w,y+h-r); ctx.arcTo(x+w,y+h,x+w-r,y+h,r)
        ctx.lineTo(x+r,y+h); ctx.arcTo(x,y+h,x,y+h-r,r)
        ctx.lineTo(x,y+r); ctx.arcTo(x,y,x+r,y,r); ctx.closePath()
    }
    function tile(ctx,s,color) { rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle=color; ctx.fill() }
    function motifBevel(ctx,s,ts,bs) {
        ctx.fillStyle=ts; ctx.fillRect(0,0,s,s*.04)
        ctx.fillStyle=bs; ctx.fillRect(0,s*.96,s,s*.04)
    }

    // ══════════════════════════════════════════════════════════════
    // BROWSERS
    // ══════════════════════════════════════════════════════════════
    function drawFirefox(ctx,s) {
        // Orange circle base
        ctx.beginPath(); ctx.arc(s/2,s/2,s/2,0,Math.PI*2)
        ctx.fillStyle="#FF6600"; ctx.fill()
        // Purple/blue earth
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.34,0,Math.PI*2)
        ctx.fillStyle="#0060DF"; ctx.fill()
        // Orange flame wrap
        ctx.strokeStyle="#FF9500"; ctx.lineWidth=s*.10; ctx.lineCap="round"
        ctx.beginPath()
        ctx.arc(s/2,s/2,s*.34,-Math.PI*.6,Math.PI*.4)
        ctx.stroke()
        ctx.beginPath(); ctx.arc(s*.72,s*.28,s*.12,0,Math.PI*2)
        ctx.fillStyle="#FF6600"; ctx.fill()
    }
    function drawChromium(ctx,s) {
        var cx=s/2,cy=s/2,r=s*.46
        var segs=[{s:-Math.PI/2,e:Math.PI/6,c:"#EA4335"},{s:Math.PI/6,e:Math.PI*5/6,c:"#FBBC05"},{s:Math.PI*5/6,e:Math.PI*3/2,c:"#34A853"}]
        for(var i=0;i<3;i++){ctx.beginPath();ctx.moveTo(cx,cy);ctx.arc(cx,cy,r,segs[i].s,segs[i].e);ctx.closePath();ctx.fillStyle=segs[i].c;ctx.fill()}
        ctx.beginPath();ctx.arc(cx,cy,r*.58,0,Math.PI*2);ctx.fillStyle="#4285F4";ctx.fill()
        ctx.beginPath();ctx.arc(cx,cy,r*.36,0,Math.PI*2);ctx.fillStyle="white";ctx.fill()
        ctx.beginPath();ctx.arc(cx,cy,r*.22,0,Math.PI*2);ctx.fillStyle="#4285F4";ctx.fill()
    }
    function drawBrave(ctx,s) {
        tile(ctx,s,"#FB542B")
        ctx.fillStyle="white"
        ctx.beginPath()
        ctx.moveTo(s*.50,s*.14)
        ctx.lineTo(s*.78,s*.26); ctx.lineTo(s*.72,s*.62)
        ctx.lineTo(s*.50,s*.82); ctx.lineTo(s*.28,s*.62)
        ctx.lineTo(s*.22,s*.26); ctx.closePath(); ctx.fill()
        ctx.fillStyle="#FB542B"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.30); ctx.lineTo(s*.62,s*.36)
        ctx.lineTo(s*.60,s*.58); ctx.lineTo(s*.50,s*.66)
        ctx.lineTo(s*.40,s*.58); ctx.lineTo(s*.38,s*.36); ctx.closePath(); ctx.fill()
    }
    function drawOpera(ctx,s) {
        ctx.beginPath(); ctx.arc(s/2,s/2,s/2,0,Math.PI*2)
        ctx.fillStyle="#FF1B2D"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.08
        ctx.beginPath(); ctx.ellipse(s/2,s/2,s*.22,s*.30,0,0,Math.PI*2); ctx.stroke()
    }
    function drawEpiphany(ctx,s) {
        tile(ctx,s,"#3A86C8")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.07
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.32,0,Math.PI*2); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.18,s*.50); ctx.lineTo(s*.82,s*.50); ctx.stroke()
        ctx.beginPath(); ctx.ellipse(s/2,s/2,s*.14,s*.32,0,0,Math.PI*2); ctx.stroke()
    }

    // ══════════════════════════════════════════════════════════════
    // TERMINAL
    // ══════════════════════════════════════════════════════════════
    function drawTerminal(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#0D1117"; ctx.fill()
        ctx.strokeStyle="#00FF41"; ctx.lineWidth=s*.07; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath(); ctx.moveTo(s*.20,s*.37); ctx.lineTo(s*.40,s*.50); ctx.lineTo(s*.20,s*.63); ctx.stroke()
        ctx.fillStyle="#00FF41"; ctx.fillRect(s*.45,s*.62,s*.36,s*.07)
    }

    // ══════════════════════════════════════════════════════════════
    // FILE MANAGER
    // ══════════════════════════════════════════════════════════════
    function drawFiles(ctx,s) {
        var ac=accentColor, tab=Qt.darker(ac,1.25).toString(), body=ac.toString()
        var shine=Qt.rgba(glowColor.r,glowColor.g,glowColor.b,0.55).toString()
        ctx.beginPath(); ctx.moveTo(s*.10,s*.38); ctx.lineTo(s*.10,s*.28)
        ctx.arcTo(s*.10,s*.22,s*.16,s*.22,s*.06); ctx.lineTo(s*.40,s*.22)
        ctx.arcTo(s*.48,s*.22,s*.50,s*.30,s*.07); ctx.lineTo(s*.52,s*.38)
        ctx.closePath(); ctx.fillStyle=tab; ctx.fill()
        rrect(ctx,s*.10,s*.34,s*.80,s*.50,s*.08); ctx.fillStyle=body; ctx.fill()
        rrect(ctx,s*.18,s*.44,s*.64,s*.32,s*.06); ctx.fillStyle=shine; ctx.fill()
    }

    // ══════════════════════════════════════════════════════════════
    // TEXT EDITORS
    // ══════════════════════════════════════════════════════════════
    function drawGeany(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#1E3A5F"; ctx.fill()
        ctx.strokeStyle="#7EC8E3"; ctx.lineWidth=s*.07; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath(); ctx.moveTo(s*.38,s*.25); ctx.lineTo(s*.30,s*.30)
        ctx.arcTo(s*.24,s*.35,s*.24,s*.42,s*.08); ctx.lineTo(s*.24,s*.45)
        ctx.lineTo(s*.18,s*.50); ctx.lineTo(s*.24,s*.55); ctx.lineTo(s*.24,s*.58)
        ctx.arcTo(s*.24,s*.65,s*.30,s*.70,s*.08); ctx.lineTo(s*.38,s*.75); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.62,s*.25); ctx.lineTo(s*.70,s*.30)
        ctx.arcTo(s*.76,s*.35,s*.76,s*.42,s*.08); ctx.lineTo(s*.76,s*.45)
        ctx.lineTo(s*.82,s*.50); ctx.lineTo(s*.76,s*.55); ctx.lineTo(s*.76,s*.58)
        ctx.arcTo(s*.76,s*.65,s*.70,s*.70,s*.08); ctx.lineTo(s*.62,s*.75); ctx.stroke()
    }
    function drawVSCode(ctx,s) {
        tile(ctx,s,"#0066B8")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.07; ctx.lineCap="round"; ctx.lineJoin="round"
        // < > brackets
        ctx.beginPath(); ctx.moveTo(s*.38,s*.32); ctx.lineTo(s*.22,s*.50); ctx.lineTo(s*.38,s*.68); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.62,s*.32); ctx.lineTo(s*.78,s*.50); ctx.lineTo(s*.62,s*.68); ctx.stroke()
        // slash
        ctx.strokeStyle="rgba(255,255,255,0.6)"
        ctx.beginPath(); ctx.moveTo(s*.55,s*.28); ctx.lineTo(s*.45,s*.72); ctx.stroke()
    }
    function drawTextEditor(ctx,s) {
        tile(ctx,s,"#2D4A7A")
        var fold=s*.16
        ctx.beginPath(); ctx.moveTo(s*.14,s*.08); ctx.lineTo(s*.82-fold,s*.08)
        ctx.lineTo(s*.82,s*.08+fold); ctx.lineTo(s*.82,s*.92); ctx.lineTo(s*.14,s*.92); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.82-fold,s*.08); ctx.lineTo(s*.82-fold,s*.08+fold)
        ctx.lineTo(s*.82,s*.08+fold); ctx.closePath(); ctx.fillStyle="#A8C4F0"; ctx.fill()
        ctx.fillStyle="#2D4A7A"
        var ls=[.28,.40,.52,.64,.74]
        for(var i=0;i<ls.length;i++) ctx.fillRect(s*.22,s*ls[i],s*(i===4?.36:.52),s*.055)
    }
    function drawSublime(ctx,s) {
        tile(ctx,s,"#FF6900")
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.52)+"px sans-serif"
        ctx.textAlign="center"; ctx.textBaseline="middle"
        ctx.fillText("S",s/2,s*.52)
    }

    // ══════════════════════════════════════════════════════════════
    // MEDIA
    // ══════════════════════════════════════════════════════════════
    function drawSpotify(ctx,s) {
        ctx.beginPath(); ctx.arc(s/2,s/2,s/2,0,Math.PI*2); ctx.fillStyle="#1DB954"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineCap="round"
        var cx=s/2,cy=s*.54
        var arcs=[[s*.34,s*.09],[s*.24,s*.07],[s*.14,s*.055]]
        for(var i=0;i<3;i++){ctx.lineWidth=arcs[i][1];ctx.beginPath();ctx.arc(cx,cy,arcs[i][0],-Math.PI*.72,-Math.PI*.28);ctx.stroke()}
    }
    function drawVLC(ctx,s) {
        // Orange cone
        ctx.beginPath(); ctx.moveTo(s*.50,s*.08); ctx.lineTo(s*.88,s*.88); ctx.lineTo(s*.12,s*.88); ctx.closePath()
        ctx.fillStyle="#FF8800"; ctx.fill()
        // White stripes
        ctx.fillStyle="white"
        ctx.fillRect(s*.26,s*.56,s*.48,s*.07)
        ctx.fillRect(s*.34,s*.68,s*.32,s*.07)
        // Cone tip cap
        ctx.beginPath(); ctx.arc(s*.50,s*.88,s*.12,0,Math.PI*2)
        ctx.fillStyle="#FF8800"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.04; ctx.stroke()
    }
    function drawMPV(ctx,s) {
        tile(ctx,s,"#552266")
        ctx.beginPath(); ctx.moveTo(s*.32,s*.26); ctx.lineTo(s*.32,s*.74); ctx.lineTo(s*.78,s*.50); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
    }
    function drawMusicPlayer(ctx,s) {
        tile(ctx,s,"#E91E8C")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.07; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.55,s*.24); ctx.lineTo(s*.55,s*.58); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.55,s*.24); ctx.bezierCurveTo(s*.75,s*.27,s*.78,s*.42,s*.58,s*.44); ctx.stroke()
        ctx.beginPath(); ctx.ellipse(s*.38,s*.60,s*.16,s*.12,-0.4,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
    }
    function drawAudacity(ctx,s) {
        tile(ctx,s,"#0000CC")
        ctx.strokeStyle="#FFCC00"; ctx.lineWidth=s*.07; ctx.lineCap="round"
        // Waveform
        var pts=[.20,.18,.22,.28,.16,.36,.32,.26,.34,.22,.28]
        ctx.beginPath(); ctx.moveTo(s*.10,s*.50)
        for(var i=0;i<pts.length;i++) ctx.lineTo(s*(.10+i*.08),s*.50+s*(i%2===0?-pts[i]:pts[i]))
        ctx.lineTo(s*.90,s*.50); ctx.stroke()
    }

    // ══════════════════════════════════════════════════════════════
    // GRAPHICS
    // ══════════════════════════════════════════════════════════════
    function drawGIMP(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#C84B11"; ctx.fill()
        ctx.strokeStyle="#FFD580"; ctx.lineWidth=s*.10; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.68,s*.18); ctx.lineTo(s*.38,s*.68); ctx.stroke()
        ctx.strokeStyle="#CCCCCC"; ctx.lineWidth=s*.08
        ctx.beginPath(); ctx.moveTo(s*.58,s*.36); ctx.lineTo(s*.48,s*.56); ctx.stroke()
        ctx.fillStyle="white"; ctx.beginPath(); ctx.arc(s*.34,s*.74,s*.09,0,Math.PI*2); ctx.fill()
        ctx.fillStyle="#FFD580"; ctx.beginPath(); ctx.arc(s*.62,s*.64,s*.08,0,Math.PI*2); ctx.fill()
    }
    function drawInkscape(ctx,s) {
        tile(ctx,s,"#000000")
        // Pen nib
        ctx.fillStyle="white"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.10); ctx.lineTo(s*.74,s*.60)
        ctx.lineTo(s*.50,s*.52); ctx.lineTo(s*.26,s*.60); ctx.closePath(); ctx.fill()
        ctx.fillStyle="#000000"; ctx.beginPath(); ctx.arc(s*.50,s*.56,s*.07,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle="#CC4400"; ctx.lineWidth=s*.06; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.60); ctx.lineTo(s*.50,s*.86); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.36,s*.80); ctx.lineTo(s*.64,s*.80); ctx.stroke()
    }
    function drawKrita(ctx,s) {
        tile(ctx,s,"#16A085")
        // K letter with brush
        ctx.fillStyle="white"
        ctx.fillRect(s*.26,s*.22,s*.09,s*.56)
        ctx.beginPath(); ctx.moveTo(s*.35,s*.50); ctx.lineTo(s*.68,s*.22); ctx.lineTo(s*.76,s*.30)
        ctx.lineTo(s*.46,s*.52); ctx.lineTo(s*.76,s*.74); ctx.lineTo(s*.68,s*.82); ctx.closePath(); ctx.fill()
    }
    function drawImageViewer(ctx,s) {
        tile(ctx,s,"#5E81AC")
        rrect(ctx,s*.10,s*.16,s*.80,s*.68,s*.06); ctx.fillStyle="white"; ctx.fill()
        // Mountain
        ctx.fillStyle="#5E81AC"
        ctx.beginPath(); ctx.moveTo(s*.10,s*.84); ctx.lineTo(s*.34,s*.44)
        ctx.lineTo(s*.54,s*.64); ctx.lineTo(s*.70,s*.48); ctx.lineTo(s*.90,s*.84); ctx.closePath(); ctx.fill()
        // Sun
        ctx.beginPath(); ctx.arc(s*.74,s*.30,s*.10,0,Math.PI*2); ctx.fillStyle="#EBCB8B"; ctx.fill()
    }

    // ══════════════════════════════════════════════════════════════
    // LIBREOFFICE
    // ══════════════════════════════════════════════════════════════
    function drawLibreOffice(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#1A7A3A"; ctx.fill()
        var dx=s*.20,dy=s*.12,dw=s*.52,dh=s*.66,fold=s*.16
        ctx.beginPath(); ctx.moveTo(dx,dy); ctx.lineTo(dx+dw-fold,dy)
        ctx.lineTo(dx+dw,dy+fold); ctx.lineTo(dx+dw,dy+dh)
        ctx.lineTo(dx,dy+dh); ctx.closePath(); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(dx+dw-fold,dy); ctx.lineTo(dx+dw-fold,dy+fold)
        ctx.lineTo(dx+dw,dy+fold); ctx.closePath(); ctx.fillStyle="#A8D5B5"; ctx.fill()
        ctx.fillStyle="#1A7A3A"
        for(var r=0;r<4;r++) ctx.fillRect(dx+s*.07,dy+fold+s*.06+r*(s*.055+s*.055),r===3?(dw-s*.10)*.65:dw-s*.10,s*.055)
    }
    function drawLOWriter(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#2A5DB0"; ctx.fill()
        var dx=s*.16,dy=s*.10,dw=s*.52,dh=s*.68,fold=s*.14
        ctx.beginPath(); ctx.moveTo(dx,dy); ctx.lineTo(dx+dw-fold,dy)
        ctx.lineTo(dx+dw,dy+fold); ctx.lineTo(dx+dw,dy+dh); ctx.lineTo(dx,dy+dh); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(dx+dw-fold,dy); ctx.lineTo(dx+dw-fold,dy+fold)
        ctx.lineTo(dx+dw,dy+fold); ctx.closePath(); ctx.fillStyle="#A8C4F0"; ctx.fill()
        ctx.fillStyle="#2A5DB0"
        for(var i=0;i<4;i++) ctx.fillRect(dx+s*.06,dy+fold+s*.06+i*(s*.10),i===3?(dw-s*.08)*.55:dw-s*.08,s*.05)
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.18)+"px sans-serif"
        ctx.textAlign="left"; ctx.textBaseline="middle"; ctx.fillText("W",s*.68,s*.76)
    }
    function drawLOCalc(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#1A7A3A"; ctx.fill()
        var gx=s*.10,gy=s*.12,gw=s*.68,gh=s*.62,cols=3,rows=4,cw=gw/cols,rh=gh/rows
        ctx.fillStyle="white"; ctx.fillRect(gx,gy,gw,gh)
        ctx.fillStyle="#1A7A3A"; ctx.fillRect(gx,gy,gw,rh)
        ctx.strokeStyle="#1A7A3A"; ctx.lineWidth=s*.025
        for(var c=0;c<=cols;c++){ctx.beginPath();ctx.moveTo(gx+c*cw,gy);ctx.lineTo(gx+c*cw,gy+gh);ctx.stroke()}
        for(var r=0;r<=rows;r++){ctx.beginPath();ctx.moveTo(gx,gy+r*rh);ctx.lineTo(gx+gw,gy+r*rh);ctx.stroke()}
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.18)+"px sans-serif"
        ctx.textAlign="left"; ctx.textBaseline="middle"; ctx.fillText("C",s*.68,s*.76)
    }
    function drawLOImpress(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#B03A2A"; ctx.fill()
        rrect(ctx,s*.10,s*.16,s*.68,s*.52,s*.05); ctx.fillStyle="white"; ctx.fill()
        ctx.fillStyle="#B03A2A"; ctx.fillRect(s*.14,s*.22,s*.36,s*.08)
        ctx.fillStyle="#DDDDDD"
        ctx.fillRect(s*.14,s*.34,s*.52,s*.05); ctx.fillRect(s*.14,s*.42,s*.44,s*.05)
        ctx.fillRect(s*.14,s*.50,s*.36,s*.05)
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.18)+"px sans-serif"
        ctx.textAlign="left"; ctx.textBaseline="middle"; ctx.fillText("I",s*.68,s*.76)
    }
    function drawLODraw(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#C8860A"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.40,s*.44,s*.22,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.28,s*.74); ctx.lineTo(s*.52,s*.26); ctx.lineTo(s*.76,s*.74); ctx.closePath()
        ctx.fillStyle="rgba(255,255,255,0.7)"; ctx.fill()
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.18)+"px sans-serif"
        ctx.textAlign="left"; ctx.textBaseline="middle"; ctx.fillText("D",s*.68,s*.22)
    }

    // ══════════════════════════════════════════════════════════════
    // PDF / DOCS
    // ══════════════════════════════════════════════════════════════
    function drawPDFViewer(ctx,s) {
        var fold=s*.16
        ctx.beginPath(); ctx.moveTo(s*.12,s*.06); ctx.lineTo(s*.84-fold,s*.06)
        ctx.lineTo(s*.84,s*.06+fold); ctx.lineTo(s*.84,s*.94); ctx.lineTo(s*.12,s*.94); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
        ctx.fillStyle="#CC2222"; ctx.fillRect(s*.12,s*.06,s*.72-fold,s*.26); ctx.fillRect(s*.12,s*.06+fold,s*.72,s*.26-fold)
        ctx.beginPath(); ctx.moveTo(s*.84-fold,s*.06); ctx.lineTo(s*.84-fold,s*.06+fold)
        ctx.lineTo(s*.84,s*.06+fold); ctx.closePath(); ctx.fillStyle="#FF6666"; ctx.fill()
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.18)+"px sans-serif"
        ctx.textAlign="center"; ctx.textBaseline="middle"; ctx.fillText("PDF",s*.46,s*.19)
        ctx.fillStyle="#CCCCCC"
        for(var i=0;i<3;i++) ctx.fillRect(s*.20,s*(.44+i*.13),i===2?s*.34:s*.52,s*.05)
    }

    // ══════════════════════════════════════════════════════════════
    // SYSTEM TOOLS
    // ══════════════════════════════════════════════════════════════
    function drawSysMon(ctx,s) {
        tile(ctx,s,"#2E4057")
        ctx.strokeStyle="#4CAF50"; ctx.lineWidth=s*.05; ctx.lineCap="round"
        var pts=[.14,.72,.22,.40,.30,.62,.38,.28,.46,.58,.54,.22,.62,.48,.70,.36,.78,.54,.86,.30]
        ctx.beginPath(); ctx.moveTo(s*pts[0],s*pts[1])
        for(var i=2;i<pts.length;i+=2) ctx.lineTo(s*pts[i],s*pts[i+1])
        ctx.stroke()
    }
    function drawSettings(ctx,s) {
        tile(ctx,s,"#607D8B")
        ctx.fillStyle="white"
        for(var t=0;t<8;t++){
            var ang=t*Math.PI*2/8
            ctx.save(); ctx.translate(s/2,s/2); ctx.rotate(ang)
            ctx.fillRect(-s*.06,-s*.42,s*.12,s*.10); ctx.restore()
        }
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.30,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.16,0,Math.PI*2); ctx.fillStyle="#607D8B"; ctx.fill()
    }
    function drawBluetooth(ctx,s) {
        tile(ctx,s,"#0082FC")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.07; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath()
        ctx.moveTo(s*.36,s*.30); ctx.lineTo(s*.64,s*.58); ctx.lineTo(s*.42,s*.76)
        ctx.lineTo(s*.42,s*.24); ctx.lineTo(s*.64,s*.42); ctx.lineTo(s*.36,s*.70)
        ctx.stroke()
    }
    function drawNetwork(ctx,s) {
        tile(ctx,s,"#1565C0")
        ctx.strokeStyle="white"; ctx.lineCap="round"
        var rs=[s*.36,s*.24,s*.12],ws=[s*.07,s*.06,s*.055]
        for(var i=0;i<3;i++){
            ctx.strokeStyle="white"; ctx.lineWidth=ws[i]
            ctx.beginPath(); ctx.arc(s/2,s*.68,rs[i],-Math.PI*.75,-Math.PI*.25); ctx.stroke()
        }
        ctx.beginPath(); ctx.arc(s/2,s*.78,s*.06,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
    }
    function drawSoftware(ctx,s) {
        tile(ctx,s,"#4A90D9")
        ctx.fillStyle="white"
        rrect(ctx,s*.18,s*.20,s*.26,s*.26,s*.04); ctx.fill()
        rrect(ctx,s*.56,s*.20,s*.26,s*.26,s*.04); ctx.fill()
        rrect(ctx,s*.18,s*.54,s*.26,s*.26,s*.04); ctx.fill()
        rrect(ctx,s*.56,s*.54,s*.26,s*.26,s*.04); ctx.fill()
    }
    function drawDisk(ctx,s) {
        tile(ctx,s,"#37474F")
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.36,0,Math.PI*2); ctx.fillStyle="#78909C"; ctx.fill()
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.14,0,Math.PI*2); ctx.fillStyle="#37474F"; ctx.fill()
        ctx.beginPath(); ctx.arc(s/2,s/2,s*.06,0,Math.PI*2); ctx.fillStyle="#78909C"; ctx.fill()
        ctx.fillStyle="#90A4AE"; ctx.fillRect(s*.62,s*.44,s*.20,s*.12)
    }
    function drawArchive(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle=Qt.rgba(.55,.40,.20,.99).toString(); ctx.fill()
        rrect(ctx,s*.18,s*.28,s*.64,s*.62,s*.06); ctx.fillStyle=Qt.rgba(.65,.48,.28,.99).toString(); ctx.fill()
        rrect(ctx,s*.14,s*.20,s*.72,s*.14,s*.04); ctx.fillStyle=Qt.rgba(.75,.56,.34,.99).toString(); ctx.fill()
        ctx.fillStyle=accentColor.toString(); ctx.fillRect(s*.44,s*.28,s*.12,s*.62)
        ctx.fillStyle=Qt.lighter(accentColor,1.3).toString()
        for(var i=0;i<4;i++) ctx.fillRect(s*.44,s*(.34+i*.13),s*.12,s*.06)
    }

    // ══════════════════════════════════════════════════════════════
    // GAMES
    // ══════════════════════════════════════════════════════════════
    function drawSteam(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#1B2838"; ctx.fill()
        ctx.strokeStyle="#C7D5E0"; ctx.lineCap="round"
        var cx=s*.50,cy=s*.44,r=s*.28
        ctx.lineWidth=s*.07; ctx.beginPath(); ctx.arc(cx,cy,r,Math.PI*.75,Math.PI*2.25); ctx.stroke()
        ctx.lineWidth=s*.05; ctx.beginPath(); ctx.arc(cx+s*.05,cy+s*.08,r*.65,Math.PI*.75,Math.PI*2.25); ctx.stroke()
        ctx.lineWidth=s*.04; ctx.beginPath(); ctx.arc(cx+s*.09,cy+s*.16,r*.40,Math.PI*.75,Math.PI*2.25); ctx.stroke()
        ctx.fillStyle="#C7D5E0"; ctx.beginPath(); ctx.arc(cx+s*.12,cy+s*.24,s*.06,0,Math.PI*2); ctx.fill()
    }
    function drawLutris(ctx,s) {
        tile(ctx,s,"#F4831F")
        // Stylized L
        ctx.fillStyle="white"
        ctx.fillRect(s*.28,s*.20,s*.12,s*.52)
        ctx.fillRect(s*.28,s*.60,s*.44,s*.12)
    }
    function drawHeroic(ctx,s) {
        tile(ctx,s,"#F5350C")
        // H letter
        ctx.fillStyle="white"
        ctx.fillRect(s*.22,s*.22,s*.12,s*.56)
        ctx.fillRect(s*.66,s*.22,s*.12,s*.56)
        ctx.fillRect(s*.22,s*.46,s*.56,s*.08)
    }
    function drawProtonUp(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#7B2FBE"; ctx.fill()
        ctx.fillStyle="white"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.10)
        ctx.bezierCurveTo(s*.34,s*.20,s*.28,s*.40,s*.30,s*.62)
        ctx.lineTo(s*.70,s*.62)
        ctx.bezierCurveTo(s*.72,s*.40,s*.66,s*.20,s*.50,s*.10)
        ctx.closePath(); ctx.fill()
        ctx.fillStyle="#E0C0FF"
        ctx.beginPath(); ctx.moveTo(s*.30,s*.62); ctx.lineTo(s*.18,s*.78); ctx.lineTo(s*.36,s*.68); ctx.closePath(); ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.70,s*.62); ctx.lineTo(s*.82,s*.78); ctx.lineTo(s*.64,s*.68); ctx.closePath(); ctx.fill()
        ctx.fillStyle="#7B2FBE"; ctx.beginPath(); ctx.arc(s*.50,s*.40,s*.10,0,Math.PI*2); ctx.fill()
        ctx.fillStyle="#FFB347"; ctx.beginPath(); ctx.moveTo(s*.38,s*.68); ctx.lineTo(s*.50,s*.84); ctx.lineTo(s*.62,s*.68); ctx.closePath(); ctx.fill()
    }

    // ══════════════════════════════════════════════════════════════
    // COMMUNICATION
    // ══════════════════════════════════════════════════════════════
    function drawDiscord(ctx,s) {
        tile(ctx,s,"#5865F2")
        ctx.fillStyle="white"
        // Controller / headset shape
        ctx.beginPath()
        ctx.moveTo(s*.20,s*.42)
        ctx.bezierCurveTo(s*.20,s*.24,s*.36,s*.18,s*.50,s*.18)
        ctx.bezierCurveTo(s*.64,s*.18,s*.80,s*.24,s*.80,s*.42)
        ctx.lineTo(s*.80,s*.60)
        ctx.bezierCurveTo(s*.80,s*.72,s*.68,s*.78,s*.58,s*.74)
        ctx.lineTo(s*.52,s*.68); ctx.lineTo(s*.48,s*.68); ctx.lineTo(s*.42,s*.74)
        ctx.bezierCurveTo(s*.32,s*.78,s*.20,s*.72,s*.20,s*.60)
        ctx.closePath(); ctx.fill()
        ctx.fillStyle="#5865F2"
        ctx.beginPath(); ctx.arc(s*.37,s*.50,s*.09,0,Math.PI*2); ctx.fill()
        ctx.beginPath(); ctx.arc(s*.63,s*.50,s*.09,0,Math.PI*2); ctx.fill()
    }
    function drawTelegram(ctx,s) {
        ctx.beginPath(); ctx.arc(s/2,s/2,s/2,0,Math.PI*2); ctx.fillStyle="#2AABEE"; ctx.fill()
        ctx.fillStyle="white"
        ctx.beginPath(); ctx.moveTo(s*.18,s*.46); ctx.lineTo(s*.82,s*.24); ctx.lineTo(s*.58,s*.74)
        ctx.lineTo(s*.46,s*.60); ctx.lineTo(s*.34,s*.68); ctx.closePath(); ctx.fill()
        ctx.fillStyle="#2AABEE"
        ctx.beginPath(); ctx.moveTo(s*.46,s*.60); ctx.lineTo(s*.82,s*.24); ctx.lineTo(s*.58,s*.74); ctx.closePath(); ctx.fill()
    }
    function drawSignal(ctx,s) {
        ctx.beginPath(); ctx.arc(s/2,s/2,s/2,0,Math.PI*2); ctx.fillStyle="#3A76F0"; ctx.fill()
        ctx.beginPath()
        ctx.arc(s/2,s*.46,s*.28,0,Math.PI*2)
        ctx.fillStyle="white"; ctx.fill()
        // Tail
        ctx.beginPath(); ctx.moveTo(s*.36,s*.68); ctx.lineTo(s*.26,s*.82); ctx.lineTo(s*.50,s*.72); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
    }
    function drawSlack(ctx,s) {
        tile(ctx,s,"#4A154B")
        var colors=["#E01E5A","#36C5F0","#2EB67D","#ECB22E"]
        var positions=[[s*.28,s*.24],[s*.52,s*.24],[s*.52,s*.52],[s*.28,s*.52]]
        for(var i=0;i<4;i++){
            ctx.fillStyle=colors[i]
            rrect(ctx,positions[i][0],positions[i][1],s*.16,s*.16,s*.04); ctx.fill()
        }
    }
    function drawZoom(ctx,s) {
        tile(ctx,s,"#2D8CFF")
        // Camera icon
        rrect(ctx,s*.14,s*.28,s*.50,s*.44,s*.06); ctx.fillStyle="white"; ctx.fill()
        ctx.fillStyle="white"
        ctx.beginPath(); ctx.moveTo(s*.64,s*.36); ctx.lineTo(s*.84,s*.26); ctx.lineTo(s*.84,s*.74)
        ctx.lineTo(s*.64,s*.64); ctx.closePath(); ctx.fill()
    }
    function drawMail(ctx,s) {
        tile(ctx,s,"#1565C0")
        rrect(ctx,s*.12,s*.24,s*.76,s*.52,s*.06); ctx.fillStyle="white"; ctx.fill()
        ctx.strokeStyle="#1565C0"; ctx.lineWidth=s*.06; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath(); ctx.moveTo(s*.12,s*.28); ctx.lineTo(s*.50,s*.54); ctx.lineTo(s*.88,s*.28); ctx.stroke()
    }

    // ══════════════════════════════════════════════════════════════
    // DEV TOOLS
    // ══════════════════════════════════════════════════════════════
    function drawGit(ctx,s) {
        tile(ctx,s,"#F05032")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.08; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.18); ctx.lineTo(s*.50,s*.50); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.50,s*.50); ctx.lineTo(s*.72,s*.72); ctx.stroke()
        ctx.beginPath(); ctx.arc(s*.50,s*.18,s*.09,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.50,s*.09,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.72,s*.72,s*.09,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
    }
    function drawDocker(ctx,s) {
        tile(ctx,s,"#2496ED")
        ctx.fillStyle="white"
        // Stack of containers
        for(var i=0;i<3;i++){
            for(var j=0;j<(3-i);j++){
                rrect(ctx,s*(.18+j*.22),s*(.58-i*.18),s*.18,s*.14,s*.02); ctx.fill()
            }
        }
    }
    function drawDB(ctx,s) {
        tile(ctx,s,"#4CAF50")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.06
        // Database cylinders
        ctx.beginPath(); ctx.ellipse(s*.50,s*.28,s*.28,s*.08,0,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.ellipse(s*.50,s*.50,s*.28,s*.08,0,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.ellipse(s*.50,s*.72,s*.28,s*.08,0,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.055
        ctx.beginPath(); ctx.moveTo(s*.22,s*.28); ctx.lineTo(s*.22,s*.72); ctx.stroke()
        ctx.beginPath(); ctx.moveTo(s*.78,s*.28); ctx.lineTo(s*.78,s*.72); ctx.stroke()
    }

    // ══════════════════════════════════════════════════════════════
    // MISC
    // ══════════════════════════════════════════════════════════════
    function drawFlatseal(ctx,s) {
        tile(ctx,s,"#3584E4")
        rrect(ctx,s*.22,s*.44,s*.56,s*.42,s*.08); ctx.fillStyle="white"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.09; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.33,s*.44); ctx.lineTo(s*.33,s*.28)
        ctx.arc(s*.50,s*.28,s*.17,Math.PI,0); ctx.lineTo(s*.67,s*.44); ctx.stroke()
        ctx.fillStyle="#3584E4"; ctx.beginPath(); ctx.arc(s*.50,s*.61,s*.08,0,Math.PI*2); ctx.fill()
        ctx.fillRect(s*.46,s*.61,s*.08,s*.12)
    }
    function drawCalendar(ctx,s) {
        tile(ctx,s,"#E53935")
        rrect(ctx,s*.12,s*.20,s*.76,s*.68,s*.06); ctx.fillStyle="white"; ctx.fill()
        ctx.fillStyle="#E53935"; ctx.fillRect(s*.12,s*.20,s*.76,s*.22)
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.28)+"px sans-serif"
        ctx.textAlign="center"; ctx.textBaseline="middle"
        var d=new Date(); ctx.fillText(d.getDate().toString(),s*.50,s*.64)
        // Calendar hooks
        ctx.fillStyle="#E53935"; ctx.fillRect(s*.30,s*.14,s*.08,s*.14)
        ctx.fillRect(s*.62,s*.14,s*.08,s*.14)
    }
    function drawTrash(ctx,s) {
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle="#2A2A3A"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.24,s*.36); ctx.lineTo(s*.30,s*.82)
        ctx.lineTo(s*.70,s*.82); ctx.lineTo(s*.76,s*.36); ctx.closePath()
        ctx.fillStyle="#7A7A9A"; ctx.fill()
        ctx.fillStyle="#AAAACC"
        rrect(ctx,s*.16,s*.28,s*.68,s*.09,s*.03); ctx.fill()
        rrect(ctx,s*.36,s*.18,s*.28,s*.11,s*.04); ctx.fill()
        ctx.fillStyle="#2A2A3A"; rrect(ctx,s*.42,s*.20,s*.16,s*.07,s*.03); ctx.fill()
        ctx.strokeStyle="#2A2A3A"; ctx.lineWidth=s*.045; ctx.lineCap="round"
        for(var ln=0;ln<3;ln++){
            var lx=s*(.37+ln*.13)
            ctx.beginPath(); ctx.moveTo(lx,s*.42); ctx.lineTo(lx+(ln-1)*s*.02,s*.76); ctx.stroke()
        }
    }

    // ══════════════════════════════════════════════════════════════
    // DEFAULT — hash-color unique per app name
    // ══════════════════════════════════════════════════════════════
    function drawDefault(ctx,s) {
        var hash=0
        for(var i=0;i<appName.length;i++)
            hash=(hash*31+appName.charCodeAt(i))&0xFFFFFF
        var palette=[
            ncde.verd,"#5E81AC","#A3BE8C","#EBCB8B",
            "#D08770","#BF616A","#B48EAD","#C77E9E",
            "#4CAF50","#FF7043","#42A5F5","#AB47BC",
            "#26C6DA","#FFA726","#66BB6A","#EC407A"
        ]
        var bg=palette[hash%palette.length]
        rrect(ctx,0,0,s,s,s*.18)
        ctx.fillStyle=bg; ctx.fill()
        // Subtle top sheen
        var grad=ctx.createLinearGradient(0,0,0,s*.4)
        grad.addColorStop(0,"rgba(255,255,255,0.25)")
        grad.addColorStop(1,"rgba(255,255,255,0.00)")
        rrect(ctx,0,0,s,s,s*.18); ctx.fillStyle=grad; ctx.fill()
        // Initial letter
        ctx.fillStyle="rgba(255,255,255,0.95)"
        ctx.font="bold "+Math.round(s*.46)+"px 'Noto Sans'"
        ctx.textAlign="center"; ctx.textBaseline="middle"
        ctx.fillText(appName.charAt(0).toUpperCase(),s/2,s*.52)
    }

    function drawScreenshot(ctx,s) {
        tile(ctx,s,"#263238")
        rrect(ctx,s*.12,s*.28,s*.76,s*.52,s*.08); ctx.fillStyle="#ECEFF1"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.54,s*.18,0,Math.PI*2); ctx.fillStyle="#37474F"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.54,s*.11,0,Math.PI*2); ctx.fillStyle="#263238"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.54,s*.05,0,Math.PI*2); ctx.fillStyle=accentColor.toString(); ctx.fill()
        rrect(ctx,s*.36,s*.20,s*.18,s*.10,s*.04); ctx.fillStyle="#ECEFF1"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.74,s*.34,s*.05,0,Math.PI*2); ctx.fillStyle="#FFEE58"; ctx.fill()
    }
    function drawScreenRecord(ctx,s) {
        tile(ctx,s,"#B71C1C")
        ctx.beginPath(); ctx.arc(s*.50,s*.46,s*.24,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.46,s*.15,0,Math.PI*2); ctx.fillStyle="#B71C1C"; ctx.fill()
        ctx.fillStyle="#B71C1C"; ctx.fillRect(s*.38,s*.72,s*.24,s*.06)
        ctx.fillRect(s*.30,s*.76,s*.40,s*.06)
    }
    function drawPavucontrol(ctx,s) {
        tile(ctx,s,"#1A237E")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.05; ctx.lineCap="round"
        var bars=[[s*.16,s*.62,s*.38],[s*.30,s*.46,s*.52],[s*.44,s*.30,s*.68],[s*.58,s*.52,s*.52],[s*.72,s*.42,s*.62]]
        for(var i=0;i<bars.length;i++){
            ctx.beginPath(); ctx.moveTo(s*bars[i][0],s*bars[i][1]); ctx.lineTo(s*bars[i][0],s*bars[i][2]); ctx.stroke()
        }
        ctx.fillStyle=accentColor.toString()
        for(var j=0;j<bars.length;j++){
            ctx.fillRect(s*(bars[j][0]-.04),s*bars[j][1]-s*.03,s*.08,s*.06)
        }
    }
    function drawKdenlive(ctx,s) {
        tile(ctx,s,"#527BB5")
        var g=ctx.createLinearGradient(0,s*.16,0,s*.84)
        g.addColorStop(0,"#83CBDD"); g.addColorStop(1,"#1A6380")
        rrect(ctx,s*.10,s*.16,s*.80,s*.68,s*.06); ctx.fillStyle=g; ctx.fill()
        ctx.fillStyle="white"; ctx.globalAlpha=0.9
        ctx.fillRect(s*.16,s*.26,s*.14,s*.28)
        ctx.fillRect(s*.34,s*.32,s*.14,s*.22)
        ctx.fillRect(s*.52,s*.22,s*.14,s*.32)
        ctx.fillRect(s*.70,s*.30,s*.14,s*.24)
        ctx.globalAlpha=1.0
        ctx.fillStyle=accentColor.toString()
        ctx.fillRect(s*.10,s*.68,s*.80,s*.04)
        ctx.beginPath(); ctx.moveTo(s*.32,s*.76); ctx.lineTo(s*.50,s*.86); ctx.lineTo(s*.68,s*.76); ctx.closePath(); ctx.fill()
    }
    function drawColourPicker(ctx,s) {
        tile(ctx,s,"#37474F")
        var segs=[["#EF5350",-1.57,-0.47],["#FF9800",-0.47,0.63],["#FFEE58",0.63,1.73],
                  ["#66BB6A",1.73,2.83],["#42A5F5",2.83,3.93],["#AB47BC",3.93,5.23]]
        for(var i=0;i<segs.length;i++){
            ctx.beginPath(); ctx.moveTo(s/2,s*.48)
            ctx.arc(s/2,s*.48,s*.32,segs[i][1],segs[i][2]); ctx.closePath()
            ctx.fillStyle=segs[i][0]; ctx.fill()
        }
        ctx.beginPath(); ctx.arc(s/2,s*.48,s*.12,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.05; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.56,s*.58); ctx.lineTo(s*.78,s*.80); ctx.stroke()
        ctx.beginPath(); ctx.arc(s*.78,s*.80,s*.06,0,Math.PI*2); ctx.fillStyle="white"; ctx.fill()
    }
    function drawVirtManager(ctx,s) {
        tile(ctx,s,"#1B5E20")
        ctx.strokeStyle="white"; ctx.lineWidth=s*.05
        rrect(ctx,s*.12,s*.14,s*.76,s*.52,s*.06); ctx.fillStyle="#2E7D32"; ctx.fill()
        ctx.strokeStyle=accentColor.toString(); ctx.lineWidth=s*.04
        ctx.strokeRect(s*.18,s*.20,s*.64,s*.40)
        ctx.fillStyle=accentColor.toString()
        ctx.fillRect(s*.36,s*.66,s*.28,s*.08)
        ctx.fillRect(s*.24,s*.72,s*.52,s*.06)
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.22)+"px 'Noto Sans'"
        ctx.textAlign="center"; ctx.textBaseline="middle"
        ctx.fillText("VM",s*.50,s*.40)
    }
    function drawWine(ctx,s) {
        tile(ctx,s,"#7B1FA2")
        ctx.strokeStyle="#F8BBD9"; ctx.lineWidth=s*.07; ctx.lineCap="round"
        ctx.beginPath()
        ctx.moveTo(s*.28,s*.18); ctx.lineTo(s*.28,s*.36)
        ctx.bezierCurveTo(s*.28,s*.58,s*.20,s*.66,s*.20,s*.74)
        ctx.lineTo(s*.80,s*.74)
        ctx.bezierCurveTo(s*.80,s*.66,s*.72,s*.58,s*.72,s*.36)
        ctx.lineTo(s*.72,s*.18)
        ctx.stroke()
        ctx.strokeStyle="#F8BBD9"; ctx.lineWidth=s*.05
        ctx.beginPath(); ctx.moveTo(s*.22,s*.24); ctx.lineTo(s*.78,s*.24); ctx.stroke()
        ctx.fillStyle="#F8BBD9"
        ctx.fillRect(s*.46,s*.74,s*.08,s*.12)
        ctx.fillRect(s*.34,s*.84,s*.32,s*.06)
    }
    function drawNotes(ctx,s) {
        tile(ctx,s,"#F57F17")
        rrect(ctx,s*.12,s*.10,s*.76,s*.80,s*.06)
        var g=ctx.createLinearGradient(0,s*.10,0,s*.90)
        g.addColorStop(0,"#FFF9C4"); g.addColorStop(1,"#FFF176")
        ctx.fillStyle=g; ctx.fill()
        ctx.fillStyle="#F57F17"
        ctx.fillRect(s*.22,s*.28,s*.56,s*.05)
        ctx.fillRect(s*.22,s*.40,s*.56,s*.05)
        ctx.fillRect(s*.22,s*.52,s*.56,s*.05)
        ctx.fillRect(s*.22,s*.64,s*.40,s*.05)
        ctx.fillStyle="#F57F17"; ctx.fillRect(s*.12,s*.10,s*.76,s*.14)
        ctx.strokeStyle="#E65100"; ctx.lineWidth=s*.03
        ctx.strokeRect(s*.12,s*.10,s*.76,s*.80)
    }
    function drawClipboard(ctx,s) {
        tile(ctx,s,"#00838F")
        var fold=s*.14
        ctx.beginPath(); ctx.moveTo(s*.22,s*.20); ctx.lineTo(s*.78-fold,s*.20)
        ctx.lineTo(s*.78,s*.20+fold); ctx.lineTo(s*.78,s*.86)
        ctx.lineTo(s*.22,s*.86); ctx.closePath(); ctx.fillStyle="#E0F7FA"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.78-fold,s*.20); ctx.lineTo(s*.78-fold,s*.20+fold)
        ctx.lineTo(s*.78,s*.20+fold); ctx.closePath(); ctx.fillStyle="#B2EBF2"; ctx.fill()
        rrect(ctx,s*.34,s*.12,s*.32,s*.16,s*.06); ctx.fillStyle="#00838F"; ctx.fill()
        ctx.fillStyle="#00838F"
        ctx.fillRect(s*.30,s*.38,s*.40,s*.05)
        ctx.fillRect(s*.30,s*.50,s*.40,s*.05)
        ctx.fillRect(s*.30,s*.62,s*.28,s*.05)
        ctx.strokeStyle=accentColor.toString(); ctx.lineWidth=s*.05; ctx.lineCap="round"
        ctx.beginPath(); ctx.moveTo(s*.28,s*.72); ctx.lineTo(s*.38,s*.82); ctx.lineTo(s*.58,s*.60); ctx.stroke()
    }
    function drawXfburn(ctx,s) {
        tile(ctx,s,"#880E4F")
        ctx.beginPath(); ctx.arc(s*.50,s*.50,s*.34,0,Math.PI*2); ctx.fillStyle="#F48FB1"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.50,s*.20,0,Math.PI*2); ctx.fillStyle="#880E4F"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.50,s*.50,s*.07,0,Math.PI*2); ctx.fillStyle="#F48FB1"; ctx.fill()
        ctx.strokeStyle="#F48FB1"; ctx.lineWidth=s*.03
        ctx.beginPath(); ctx.moveTo(s*.50,s*.16); ctx.lineTo(s*.50,s*.30); ctx.stroke()
        ctx.fillStyle="#FF6F00"
        ctx.beginPath(); ctx.moveTo(s*.50,s*.06); ctx.bezierCurveTo(s*.40,s*.14,s*.36,s*.22,s*.42,s*.28)
        ctx.bezierCurveTo(s*.44,s*.22,s*.48,s*.18,s*.50,s*.14)
        ctx.bezierCurveTo(s*.52,s*.18,s*.56,s*.22,s*.58,s*.28)
        ctx.bezierCurveTo(s*.64,s*.22,s*.60,s*.14,s*.50,s*.06); ctx.fill()
    }
    function drawNitrogen(ctx,s) {
        tile(ctx,s,"#1565C0")
        rrect(ctx,s*.10,s*.16,s*.80,s*.56,s*.06); ctx.fillStyle="#90CAF9"; ctx.fill()
        ctx.beginPath(); ctx.arc(s*.72,s*.30,s*.10,0,Math.PI*2); ctx.fillStyle="#FFF176"; ctx.fill()
        ctx.fillStyle="#1565C0"
        ctx.beginPath(); ctx.moveTo(s*.10,s*.72); ctx.lineTo(s*.34,s*.44); ctx.lineTo(s*.52,s*.58)
        ctx.lineTo(s*.68,s*.42); ctx.lineTo(s*.90,s*.60); ctx.lineTo(s*.90,s*.72); ctx.closePath(); ctx.fill()
        ctx.fillStyle="#42A5F5"
        ctx.beginPath(); ctx.moveTo(s*.10,s*.72); ctx.bezierCurveTo(s*.20,s*.64,s*.24,s*.68,s*.34,s*.64)
        ctx.bezierCurveTo(s*.44,s*.60,s*.48,s*.68,s*.58,s*.64)
        ctx.bezierCurveTo(s*.68,s*.60,s*.72,s*.66,s*.90,s*.60)
        ctx.lineTo(s*.90,s*.72); ctx.lineTo(s*.10,s*.72); ctx.fill()
        ctx.fillStyle="white"; ctx.font="bold "+Math.round(s*.14)+"px 'Noto Sans'"
        ctx.textAlign="center"; ctx.textBaseline="top"
        ctx.fillText("WALLPAPER",s*.50,s*.76)
    }
    function drawDock(ctx,s) {
        tile(ctx,s,"#212121")
        rrect(ctx,s*.08,s*.62,s*.84,s*.28,s*.08); ctx.fillStyle="#424242"; ctx.fill()
        var colors=["#EF5350","#42A5F5","#66BB6A","#FFEE58"]
        for(var i=0;i<4;i++){
            rrect(ctx,s*(.14+i*.22),s*.64,s*.16,s*.24,s*.04)
            ctx.fillStyle=colors[i]; ctx.fill()
        }
        ctx.fillStyle="white"; ctx.fillRect(s*.43,s*.52,s*.14,s*.12)
        ctx.beginPath(); ctx.moveTo(s*.38,s*.52); ctx.lineTo(s*.62,s*.52); ctx.lineTo(s*.50,s*.36); ctx.closePath()
        ctx.fillStyle="rgba(255,255,255,0.6)"; ctx.fill()
    }
    function drawAbout(ctx,s) {
        tile(ctx,s,"#1565C0")
        ctx.fillStyle="white"
        ctx.font="bold "+Math.round(s*.52)+"px 'Noto Sans'"
        ctx.textAlign="center"; ctx.textBaseline="middle"
        ctx.fillText("i",s*.50,s*.56)
        ctx.beginPath(); ctx.arc(s*.50,s*.24,s*.07,0,Math.PI*2); ctx.fill()
        ctx.fillRect(s*.28,s*.78,s*.44,s*.05)
    }
    function drawAccessibility(ctx,s) {
        tile(ctx,s,"#1B5E20")
        ctx.fillStyle="white"
        ctx.beginPath(); ctx.arc(s*.50,s*.22,s*.10,0,Math.PI*2); ctx.fill()
        ctx.strokeStyle="white"; ctx.lineWidth=s*.09; ctx.lineCap="round"; ctx.lineJoin="round"
        ctx.beginPath()
        ctx.moveTo(s*.50,s*.32); ctx.lineTo(s*.50,s*.60)
        ctx.moveTo(s*.18,s*.40); ctx.lineTo(s*.82,s*.40)
        ctx.moveTo(s*.50,s*.60); ctx.lineTo(s*.30,s*.84)
        ctx.moveTo(s*.50,s*.60); ctx.lineTo(s*.70,s*.84)
        ctx.stroke()
    }
    function drawScribus(ctx,s) {
        tile(ctx,s,"#1565C0")
        var fold=s*.14
        ctx.beginPath(); ctx.moveTo(s*.16,s*.10); ctx.lineTo(s*.80-fold,s*.10)
        ctx.lineTo(s*.80,s*.10+fold); ctx.lineTo(s*.80,s*.90); ctx.lineTo(s*.16,s*.90); ctx.closePath()
        ctx.fillStyle="white"; ctx.fill()
        ctx.beginPath(); ctx.moveTo(s*.80-fold,s*.10); ctx.lineTo(s*.80-fold,s*.10+fold)
        ctx.lineTo(s*.80,s*.10+fold); ctx.closePath(); ctx.fillStyle="#BBDEFB"; ctx.fill()
        ctx.fillStyle="#1565C0"
        ctx.fillRect(s*.24,s*.26,s*.44,s*.06); ctx.fillRect(s*.24,s*.36,s*.38,s*.05)
        rrect(ctx,s*.24,s*.46,s*.40,s*.26,s*.03); ctx.fillStyle="#BBDEFB"; ctx.fill()
        ctx.fillStyle="#1565C0"
        ctx.beginPath(); ctx.moveTo(s*.24,s*.72); ctx.lineTo(s*.36,s*.56)
        ctx.lineTo(s*.46,s*.66); ctx.lineTo(s*.54,s*.58); ctx.lineTo(s*.64,s*.72); ctx.closePath(); ctx.fill()
    }
}
