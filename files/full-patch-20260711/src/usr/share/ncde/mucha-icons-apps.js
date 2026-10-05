// mucha-icons-apps.js  —  Master dispatcher for app icons.
//
// Each category file (browsers, terminals, editors, …) defines its own
// detailed draw* functions.  This file routes a normalized app name to the
// right one. Specific apps are matched FIRST; generic category keywords next;
// drawDefault() with a hash-coloured monogram is the final fallback.

.pragma library
.import "mucha-icons-core.js"             as Core
.import "mucha-icons-apps-browsers.js"    as Br
.import "mucha-icons-apps-terminals.js"   as Tr
.import "mucha-icons-apps-editors.js"     as Ed
.import "mucha-icons-apps-files.js"       as Fm
.import "mucha-icons-apps-media.js"       as Me
.import "mucha-icons-apps-graphics.js"    as Gr
.import "mucha-icons-apps-office.js"      as Of
.import "mucha-icons-apps-comm.js"        as Cm
.import "mucha-icons-apps-dev.js"         as Dv
.import "mucha-icons-apps-system.js"      as Sy
.import "mucha-icons-apps-network.js"     as Nw
.import "mucha-icons-apps-misc.js"        as Mi
.import "mucha-icons-apps-house.js"       as Hs

var _accentColor = null;
var _glowColor   = null;

function matchAppIcon(ctx, s, name, appId, accentColor, glowColor, kithEmblem) {
    _accentColor = accentColor || null;
    _glowColor   = glowColor   || null;

    var n = Core.normalizeKey(name + " " + appId);

    // -------- BFB (NCDE start / launcher button) — highest priority --------
    if (Core.hasAny(n, ["bfbpanel", "ncdepanel", "panellauncher", "bfbsmall"]))
        return drawBFBPanel(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bfb", "ncdelauncher", "ncdemenu", "startmenu", "launcher", "ncdestart"]))
        return drawBFB(ctx, s, _accentColor, _glowColor);

    // Dock-only kith emblems; other app surfaces keep their familiar motifs.
    if (kithEmblem) {
        if (Core.hasAny(n, ["chromium"]))                         return Hs.drawKithEshu(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["terminal", "shell", "console"]))     return Hs.drawKithNocker(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["steam"]))                            return Hs.drawKithTroll(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["gimp"]))                             return Hs.drawKithSluagh(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["libreoffice"]))                      return Hs.drawKithBoggan(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["spotify"]))                          return Hs.drawKithSatyr(ctx, s, _accentColor, _glowColor);
        if (Core.hasAny(n, ["verve"]))                            return Hs.drawKithPooka(ctx, s, _accentColor, _glowColor);
    }

    // -------- NCDE HOUSE APPS — kith emblems (were letter monograms) --------
    if (Core.hasAny(n, ["ncdecommand"]))                            return Hs.drawKithSidhe(ctx, s, _accentColor, _glowColor);
    // Orchidée: normalizeKey() drops the "é" ("orchid e"), so match the stem
    if (Core.hasAny(n, ["orchid"]))                                 return Hs.drawKithBoggan(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["hummingbird"]))                            return Hs.drawKithEshu(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["magpie"]))                                 return Hs.drawKithPooka(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["binnie"]))                                 return Hs.drawKithRedcap(ctx, s, _accentColor, _glowColor);

    // -------- BROWSERS --------
    if (Core.hasAny(n, ["librewolf"]))                              return Br.drawLibreWolf(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["firefox", "mozilla", "iceweasel"]))        return Br.drawFirefox(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["chromium"]))                               return Br.drawChromium(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["googlechrome", "chrome"]))                 return Br.drawChrome(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["brave"]))                                  return Br.drawBrave(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["vivaldi"]))                                return Br.drawVivaldi(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["opera"]))                                  return Br.drawOpera(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["microsoftedge", "edge"]))                  return Br.drawEdge(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["torbrowser", "tor"]))                      return Br.drawTor(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["falkon"]))                                 return Br.drawFalkon(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["konqueror"]))                              return Br.drawKonqueror(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["qutebrowser", "qutebr"]))                  return Br.drawQutebrowser(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["epiphany", "gnomeweb"]))                   return Br.drawEpiphany(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["midori"]))                                 return Br.drawMidori(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["dillo", "netsurf", "links", "lynx", "w3m"])) return Br.drawTextBrowser(ctx, s, _accentColor, _glowColor);

    // -------- TERMINALS --------
    if (Core.hasAny(n, ["alacritty"]))                              return Tr.drawAlacritty(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kittyterm", "kitty"]))                     return Tr.drawKitty(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["wezterm"]))                                return Tr.drawWezterm(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["konsole"]))                                return Tr.drawKonsole(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnometerminal", "gnometerm"]))             return Tr.drawGnomeTerminal(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["tilix"]))                                  return Tr.drawTilix(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["terminator"]))                             return Tr.drawTerminator(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["yakuake"]))                                return Tr.drawYakuake(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["guake"]))                                  return Tr.drawGuake(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["foot"]))                                   return Tr.drawFoot(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["hyperterm", "hyper"]))                     return Tr.drawHyper(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["xterm", "urxvt", "rxvt", "st"]))           return Tr.drawXterm(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["terminal", "shell", "console"]))           return Tr.drawGenericTerminal(ctx, s, _accentColor, _glowColor);

    // -------- EDITORS / IDEs --------
    if (Core.hasAny(n, ["vscodium", "codium"]))                     return Ed.drawVSCodium(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["vscode", "visualstudiocode", "code"]))     return Ed.drawVSCode(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["cursor"]))                                 return Ed.drawCursor(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["zed"]))                                    return Ed.drawZed(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["lapce"]))                                  return Ed.drawLapce(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["helix"]))                                  return Ed.drawHelix(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["neovim", "nvim"]))                         return Ed.drawNeovim(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gvim", "vim"]))                            return Ed.drawVim(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["emacs"]))                                  return Ed.drawEmacs(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["sublime"]))                                return Ed.drawSublime(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["atom"]))                                   return Ed.drawAtom(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kate", "kwrite"]))                         return Ed.drawKate(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gedit"]))                                  return Ed.drawGedit(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["geany"]))                                  return Ed.drawGeany(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["verve"]))                                  return Ed.drawGedit(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["nano", "pico"]))                           return Ed.drawNano(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["notepadqq", "notepad"]))                   return Ed.drawNotepad(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["intellij", "ideaide", "ideac"]))           return Ed.drawIntelliJ(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pycharm"]))                                return Ed.drawPyCharm(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["webstorm"]))                               return Ed.drawWebStorm(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["clion"]))                                  return Ed.drawCLion(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["goland"]))                                 return Ed.drawGoLand(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["androidstudio", "androidide"]))            return Ed.drawAndroidStudio(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rider"]))                                  return Ed.drawRider(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["datagrip"]))                               return Ed.drawDataGrip(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rubymine"]))                               return Ed.drawRubyMine(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["phpstorm"]))                               return Ed.drawPhpStorm(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["fleet"]))                                  return Ed.drawFleet(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["eclipse"]))                                return Ed.drawEclipse(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["netbeans"]))                               return Ed.drawNetBeans(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["qtcreator"]))                              return Ed.drawQtCreator(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kdevelop"]))                               return Ed.drawKDevelop(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["codeblocks"]))                             return Ed.drawCodeBlocks(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["editor"]))                                 return Ed.drawGenericEditor(ctx, s, _accentColor, _glowColor);

    // -------- FILE MANAGERS --------
    if (Core.hasAny(n, ["thunar"]))                                 return Fm.drawThunar(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["nautilus", "filesgnome"]))                 return Fm.drawNautilus(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["dolphin"]))                                return Fm.drawDolphin(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pcmanfm"]))                                return Fm.drawPCManFM(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["nemo"]))                                   return Fm.drawNemo(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["caja"]))                                   return Fm.drawCaja(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["krusader"]))                               return Fm.drawKrusader(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["ranger"]))                                 return Fm.drawRanger(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["doublecmd", "doublecommander"]))           return Fm.drawDoubleCmd(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["midnightcommander", "mc"]))                return Fm.drawMidnightCmd(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["filemanager", "files"]))                   return Fm.drawGenericFiles(ctx, s, _accentColor, _glowColor);

    // -------- MEDIA --------
    if (Core.hasAny(n, ["vlc"]))                                    return Me.drawVLC(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mpv"]))                                    return Me.drawMPV(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["smplayer"]))                               return Me.drawSMPlayer(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["celluloid", "gnomempv"]))                  return Me.drawCelluloid(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["totem", "gnomevideos"]))                   return Me.drawTotem(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kaffeine"]))                               return Me.drawKaffeine(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["audacious"]))                              return Me.drawAudacious(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rhythmbox"]))                              return Me.drawRhythmbox(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["clementine"]))                             return Me.drawClementine(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["strawberry"]))                             return Me.drawStrawberry(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["spotify"]))                                return Me.drawSpotify(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["deadbeef"]))                               return Me.drawDeadbeef(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["audacity", "tenacity"]))                   return Me.drawAudacity(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["ardour"]))                                 return Me.drawArdour(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["lmms"]))                                   return Me.drawLMMS(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mixxx"]))                                  return Me.drawMixxx(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["hydrogen"]))                               return Me.drawHydrogen(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rosegarden"]))                             return Me.drawRosegarden(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["musescore"]))                              return Me.drawMuseScore(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["reaper"]))                                 return Me.drawReaper(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bitwig"]))                                 return Me.drawBitwig(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kdenlive"]))                               return Me.drawKdenlive(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["openshot"]))                               return Me.drawOpenShot(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["shotcut"]))                                return Me.drawShotcut(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["davinciresolve", "resolve"]))              return Me.drawResolve(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pitivi"]))                                 return Me.drawPitivi(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["flowblade"]))                              return Me.drawFlowblade(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["obs", "obsstudio"]))                       return Me.drawOBS(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["olive"]))                                  return Me.drawOlive(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["handbrake"]))                              return Me.drawHandBrake(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["avidemux"]))                               return Me.drawAvidemux(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["music", "player"]))                        return Me.drawGenericMusic(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["video", "movie", "film"]))                 return Me.drawGenericVideo(ctx, s, _accentColor, _glowColor);

    // -------- GRAPHICS --------
    if (Core.hasAny(n, ["gimp"]))                                   return Gr.drawGimp(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["krita"]))                                  return Gr.drawKrita(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["inkscape"]))                               return Gr.drawInkscape(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pinta"]))                                  return Gr.drawPinta(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["darktable"]))                              return Gr.drawDarktable(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rawtherapee"]))                            return Gr.drawRawTherapee(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["digikam"]))                                return Gr.drawDigikam(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["shotwell"]))                               return Gr.drawShotwell(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gthumb"]))                                 return Gr.drawGthumb(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gwenview"]))                               return Gr.drawGwenview(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["nomacs"]))                                 return Gr.drawNomacs(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["eog", "eyeofgnome"]))                      return Gr.drawEOG(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["feh"]))                                    return Gr.drawFeh(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["blender"]))                                return Gr.drawBlender(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["freecad"]))                                return Gr.drawFreeCAD(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["openscad"]))                               return Gr.drawOpenSCAD(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["librecad"]))                               return Gr.drawLibreCAD(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kicad"]))                                  return Gr.drawKiCad(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["scribus"]))                                return Gr.drawScribus(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mypaint"]))                                return Gr.drawMyPaint(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["synfig"]))                                 return Gr.drawSynfig(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pencil2d", "pencil"]))                     return Gr.drawPencil2D(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["imagemagick"]))                            return Gr.drawImageMagick(ctx, s, _accentColor, _glowColor);

    // -------- OFFICE --------
    if (Core.hasAny(n, ["libreofficewriter", "lowriter", "writer"]))         return Of.drawLOWriter(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreofficecalc", "localc", "calc", "abacus"]))      return Of.drawLOCalc(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreofficeimpress", "loimpress", "impress"]))      return Of.drawLOImpress(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreofficedraw", "lodraw"]))                       return Of.drawLODraw(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreofficemath", "lomath"]))                       return Of.drawLOMath(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreofficebase", "lobase", "base"]))               return Of.drawLOBase(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["libreoffice"]))                                     return Of.drawLOMain(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["onlyoffice"]))                                      return Of.drawOnlyOffice(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["wpsoffice", "wps"]))                                return Of.drawWPS(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["abiword"]))                                         return Of.drawAbiword(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnumeric"]))                                        return Of.drawGnumeric(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["calligra"]))                                        return Of.drawCalligra(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["okular"]))                                          return Of.drawOkular(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["evince"]))                                          return Of.drawEvince(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["foliate"]))                                         return Of.drawFoliate(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["calibre"]))                                         return Of.drawCalibre(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["zathura"]))                                         return Of.drawZathura(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mupdf", "qpdfview", "sioyek"]))                     return Of.drawMuPDF(ctx, s, _accentColor, _glowColor);

    // -------- COMMUNICATION --------
    if (Core.hasAny(n, ["thunderbird"]))                            return Cm.drawThunderbird(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["evolution"]))                              return Cm.drawEvolution(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["geary"]))                                  return Cm.drawGeary(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kmail"]))                                  return Cm.drawKMail(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["clawsmail", "claws"]))                     return Cm.drawClaws(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["slack"]))                                  return Cm.drawSlack(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["discord"]))                                return Cm.drawDiscord(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["telegram"]))                               return Cm.drawTelegram(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["signal"]))                                 return Cm.drawSignal(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["whatsapp"]))                               return Cm.drawWhatsApp(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["element", "riot"]))                        return Cm.drawElement(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["hexchat", "irssi", "weechat"]))            return Cm.drawHexChat(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pidgin"]))                                 return Cm.drawPidgin(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["empathy"]))                                return Cm.drawEmpathy(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["zoom"]))                                   return Cm.drawZoom(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["teams"]))                                  return Cm.drawTeams(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["jami"]))                                   return Cm.drawJami(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mumble"]))                                 return Cm.drawMumble(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["teamspeak"]))                              return Cm.drawTeamSpeak(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["skype"]))                                  return Cm.drawSkype(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["mail", "email"]))                          return Cm.drawGenericMail(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["chat", "messenger"]))                      return Cm.drawGenericChat(ctx, s, _accentColor, _glowColor);

    // -------- DEV TOOLS --------
    if (Core.hasAny(n, ["githubdesktop"]))                          return Dv.drawGitHubDesktop(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gitkraken"]))                              return Dv.drawGitKraken(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["sourcetree"]))                             return Dv.drawSourcetree(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gitg"]))                                   return Dv.drawGitg(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["git"]))                                    return Dv.drawGit(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["meld"]))                                   return Dv.drawMeld(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["postman"]))                                return Dv.drawPostman(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["insomnia"]))                               return Dv.drawInsomnia(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bruno"]))                                  return Dv.drawBruno(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["dbeaver"]))                                return Dv.drawDBeaver(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["docker"]))                                 return Dv.drawDocker(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["podman"]))                                 return Dv.drawPodman(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["virtmanager", "virtviewer"]))              return Dv.drawVirtManager(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["virtualbox"]))                             return Dv.drawVirtualBox(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["vmware"]))                                 return Dv.drawVMware(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnomeboxes", "boxes"]))                    return Dv.drawBoxes(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["wine", "winetricks"]))                     return Dv.drawWine(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["lutris"]))                                 return Dv.drawLutris(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["heroic"]))                                 return Dv.drawHeroic(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bottles"]))                                return Dv.drawBottles(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["steam"]))                                  return Dv.drawSteam(ctx, s, _accentColor, _glowColor);

    // -------- SYSTEM --------
    if (Core.hasAny(n, ["htop"]))                                   return Sy.drawHtop(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["btop", "bpytop", "bashtop"]))              return Sy.drawBtop(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnomesystemmonitor", "systemmonitor"]))    return Sy.drawSystemMonitor(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["ksysguard", "plasmasystemmonitor"]))       return Sy.drawKSysGuard(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["stacer"]))                                 return Sy.drawStacer(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pavucontrol"]))                            return Sy.drawPavucontrol(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["easyeffects"]))                            return Sy.drawEasyEffects(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["synaptic"]))                               return Sy.drawSynaptic(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pamac"]))                                  return Sy.drawPamac(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["octopi"]))                                 return Sy.drawOctopi(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["discover", "plasmadiscover"]))             return Sy.drawDiscover(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnomesoftware", "software"]))              return Sy.drawGnomeSoftware(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["systemsettings", "kcm"]))                  return Sy.drawSystemSettings(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gnomecontrolcenter", "controlcenter", "settings"])) return Sy.drawSettings(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["gparted", "kdepartitionmanager"]))         return Sy.drawGparted(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["timeshift"]))                              return Sy.drawTimeshift(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["dejadup"]))                                return Sy.drawDejaDup(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bleachbit"]))                              return Sy.drawBleachbit(ctx, s, _accentColor, _glowColor);

    // -------- NETWORK --------
    if (Core.hasAny(n, ["qbittorrent"]))                            return Nw.drawQbittorrent(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["transmission"]))                           return Nw.drawTransmission(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["deluge"]))                                 return Nw.drawDeluge(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["wireshark"]))                              return Nw.drawWireshark(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["filezilla"]))                              return Nw.drawFilezilla(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["remmina"]))                                return Nw.drawRemmina(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["krdc"]))                                   return Nw.drawKRDC(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["openvpn", "wireguard"]))                   return Nw.drawVPN(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["protonvpn", "mullvad"]))                   return Nw.drawProtonVPN(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["dropbox"]))                                return Nw.drawDropbox(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["nextcloud", "owncloud"]))                  return Nw.drawNextcloud(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["syncthing"]))                              return Nw.drawSyncthing(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["megasync", "mega"]))                       return Nw.drawMega(ctx, s, _accentColor, _glowColor);

    // -------- MISC (notes, science, security, games, etc.) --------
    if (Core.hasAny(n, ["joplin"]))                                 return Mi.drawJoplin(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["obsidian"]))                               return Mi.drawObsidian(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["logseq"]))                                 return Mi.drawLogseq(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["zim"]))                                    return Mi.drawZim(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["cherrytree"]))                             return Mi.drawCherrytree(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["anki"]))                                   return Mi.drawAnki(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["keepassxc", "keepass"]))                   return Mi.drawKeePass(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["bitwarden"]))                              return Mi.drawBitwarden(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["onepassword", "1password"]))               return Mi.drawOnePassword(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["stellarium"]))                             return Mi.drawStellarium(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["kstars"]))                                 return Mi.drawKStars(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["celestia"]))                               return Mi.drawCelestia(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["geogebra"]))                               return Mi.drawGeoGebra(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["octave"]))                                 return Mi.drawOctave(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["rstudio"]))                                return Mi.drawRStudio(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["jupyter"]))                                return Mi.drawJupyter(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["clamtk", "clamav"]))                       return Mi.drawClamAV(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["pikabackup", "vorta", "borg"]))            return Mi.drawPikaBackup(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["minecraft"]))                              return Mi.drawMinecraft(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["supertux", "supertuxkart"]))               return Mi.drawSuperTux(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["conky"]))                                  return Mi.drawConky(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["redshift", "gammastep", "nightlight"]))    return Mi.drawRedshift(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["flameshot", "spectacle", "screenshot"]))   return Mi.drawScreenshot(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["calculator", "kcalc", "gnomecalc", "qalculate"])) return Mi.drawCalculator(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["clock", "alarm", "kclock"]))               return Mi.drawClock(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["weather"]))                                return Mi.drawWeather(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["maps"]))                                   return Mi.drawMaps(ctx, s, _accentColor, _glowColor);

    // -------- GENERIC FALLBACKS BY KEYWORD --------
    if (Core.hasAny(n, ["browser", "web"]))                         return Br.drawGenericBrowser(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["folder", "directory"]))                    return Fm.drawGenericFiles(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["game", "play"]))                           return Mi.drawGenericGame(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["security", "password", "vault"]))          return Mi.drawGenericVault(ctx, s, _accentColor, _glowColor);
    if (Core.hasAny(n, ["note", "memo"]))                           return Mi.drawGenericNote(ctx, s, _accentColor, _glowColor);

    // -------- DEFAULT --------
    drawDefault(ctx, s, name + " " + appId);
}

// =================================================================
// drawDefault — Mucha-style monogram on a hash-coloured medallion
// =================================================================
function drawDefault(ctx, s, name) {
    var key  = Core.normalizeKey(name);
    var disc = Core.hashColor(key, [
        Core.PALETTE.sage, Core.PALETTE.terra, Core.PALETTE.plum,
        Core.PALETTE.teal, Core.PALETTE.roseDeep, Core.PALETTE.sageDeep,
        Core.PALETTE.indigo, Core.PALETTE.goldDark
    ]);
    var initial = (name && name.replace(/[^A-Za-z]/g, '').charAt(0)) || '·';
    Core.drawTile(ctx, s, null, {
        shape: "medallion",
        accent: _accentColor || Core.PALETTE.gold,
        glow:   _glowColor   || Core.PALETTE.glow,
        ornament: true, halo: true, rim: true
    });
    // halo behind monogram
    Core.drawHalo(ctx, s, _glowColor || Core.PALETTE.goldShine);
    // inner medallion in hash color
    Core.drawInnerDisc(ctx, s, disc, 0.30);
    Core.stipple(ctx, s * 0.22, s * 0.22, s * 0.56, s * 0.56, 0.18, "rgba(58,43,24,0.10)");
    // monogram letter
    Core.drawMonogram(ctx, s, initial, Core.PALETTE.bgCreamHi, null);
    // tiny corner florals
    Core.drawFloralStem(ctx, s * 0.13, s * 0.86, s * 0.18,
        Core.PALETTE.sageDeep, _accentColor || Core.PALETTE.gold);
    Core.drawFloralStem(ctx, s * 0.87, s * 0.86, -s * 0.18,
        Core.PALETTE.sageDeep, _accentColor || Core.PALETTE.gold);
    // theme-aware outer stroke (CONTRACT: _accentColor or PALETTE.border)
    var cx = s * 0.5, cy = s * 0.5;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.30, 0, Math.PI * 2);
    Core.setStroke(ctx, _accentColor || Core.PALETTE.border, Math.max(0.6, s * 0.014));
    ctx.stroke();
}

// ============================================================================
// drawBFB — NCDE main launcher button.
// Circular medallion with an ornate illuminated drop-cap "N" (Mucha + manuscript).
//   - Layered gilded rings (outer beaded, middle plain, inner laurel)
//   - Sage-deep field with stippled aged texture
//   - Tall serif "N" with floral flourish on the diagonal
//   - Whiplash vines flanking the letter
//   - Small rosette in the upper-left and lower-right of the field
// ============================================================================
function drawBFB(ctx, s, accent, glow) {
    var cx = s * 0.5, cy = s * 0.5;
    accent = accent || Core.PALETTE.gold;
    glow   = glow   || Core.PALETTE.glow;

    // --- OUTER FIELD --------------------------------------------------------
    // base disc (cream → gilt edge)
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.48, 0, Math.PI * 2);
    ctx.fillStyle = Core.radial(ctx, cx, cy, s * 0.05, s * 0.48,
        [[0, Core.PALETTE.bgCreamHi], [0.7, Core.PALETTE.bgPaper], [1, Core.PALETTE.goldDark]]);
    ctx.fill();

    // outer gilt rim
    Core.setStroke(ctx, accent, s * 0.024);
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.475, 0, Math.PI * 2);
    ctx.stroke();
    // dark hairline (engraved)
    Core.setStroke(ctx, Core.PALETTE.ink, s * 0.008);
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.46, 0, Math.PI * 2);
    ctx.stroke();

    // beaded ring (24 pearls) just inside rim
    Core.ringDots(ctx, cx, cy, s * 0.435, 32, s * 0.014, Core.PALETTE.goldHi);
    // alternating dark beads for "twisted-rope" effect
    for (var b = 0; b < 32; b++) {
        if (b % 2 === 0) continue;
        var aa = b / 32 * Math.PI * 2 - Math.PI / 2;
        ctx.beginPath();
        ctx.arc(cx + Math.cos(aa) * s * 0.435,
                cy + Math.sin(aa) * s * 0.435,
                s * 0.008, 0, Math.PI * 2);
        ctx.fillStyle = Core.PALETTE.ink;
        ctx.fill();
    }

    // --- INNER FIELD (palette glass with stipple) --------------------------
    // 2026-09-25: was a fixed sage green — the one green medallion on a violet
    // dock. Now hued from the Iris accent like every other tile's field (drawTile),
    // kept mid-dark so the gilt laurel and monogram keep their contrast.
    // Unparseable accent -> the original sage.
    var fHi = Core._mixHex(accent, "#000000", 0.30) || "#7a9485";
    var fMd = Core._mixHex(accent, "#000000", 0.55) || Core.PALETTE.sageDeep;
    var fDk = Core._mixHex(accent, "#000000", 0.72) || Core.PALETTE.sageDark;
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.385, 0, Math.PI * 2);
    ctx.fillStyle = Core.radial(ctx, cx - s * 0.06, cy - s * 0.08, s * 0.02, s * 0.40,
        [[0, fHi], [0.6, fMd], [1, fDk]]);
    ctx.fill();
    Core.setStroke(ctx, Core.PALETTE.goldDark, s * 0.014);
    ctx.stroke();

    // halo arc upper
    ctx.save();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.385, 0, Math.PI * 2);
    ctx.clip();
    ctx.fillStyle = Core.radial(ctx, cx, cy * 0.55, s * 0.05, s * 0.40,
        [[0, glow], [0.8, "rgba(255,235,180,0)"], [1, "rgba(255,235,180,0)"]]);
    ctx.fillRect(0, 0, s, s);
    ctx.restore();

    // stippled paper texture on field
    ctx.save();
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.385, 0, Math.PI * 2);
    ctx.clip();
    Core.stipple(ctx, cx - s * 0.40, cy - s * 0.40, s * 0.80, s * 0.80, 0.20, "rgba(255,235,180,0.12)");
    Core.stipple(ctx, cx - s * 0.40, cy - s * 0.40, s * 0.80, s * 0.80, 0.12, "rgba(58,43,24,0.10)");
    ctx.restore();

    // inner laurel ring — small leaves, 16 around
    for (var i = 0; i < 16; i++) {
        var a = i / 16 * Math.PI * 2 - Math.PI / 2;
        Core.leafBead(ctx,
            cx + Math.cos(a) * s * 0.34,
            cy + Math.sin(a) * s * 0.34,
            s * 0.08, a + Math.PI / 2,
            i % 2 ? Core.PALETTE.goldHi : Core.PALETTE.gold);
    }

    // --- FLANKING WHIPLASH VINES -------------------------------------------
    ctx.save();
    Core.setStroke(ctx, Core.PALETTE.goldHi, s * 0.014);
    // left vine
    ctx.beginPath();
    ctx.moveTo(cx - s * 0.24, cy - s * 0.20);
    ctx.bezierCurveTo(cx - s * 0.32, cy - s * 0.05, cx - s * 0.30, cy + s * 0.12, cx - s * 0.22, cy + s * 0.22);
    ctx.stroke();
    // right vine
    ctx.beginPath();
    ctx.moveTo(cx + s * 0.24, cy + s * 0.20);
    ctx.bezierCurveTo(cx + s * 0.32, cy + s * 0.05, cx + s * 0.30, cy - s * 0.12, cx + s * 0.22, cy - s * 0.22);
    ctx.stroke();
    ctx.restore();

    // vine leaves
    Core.leafBead(ctx, cx - s * 0.30, cy - s * 0.02, s * 0.10, -0.5, Core.PALETTE.sageMist);
    Core.leafBead(ctx, cx - s * 0.27, cy + s * 0.18, s * 0.09,  0.4, Core.PALETTE.sageMist);
    Core.leafBead(ctx, cx + s * 0.30, cy + s * 0.02, s * 0.10,  2.6, Core.PALETTE.sageMist);
    Core.leafBead(ctx, cx + s * 0.27, cy - s * 0.18, s * 0.09, -2.7, Core.PALETTE.sageMist);

    // small rosettes in the corners of the inner field
    Core.drawRosette(ctx, cx - s * 0.22, cy - s * 0.24, s * 0.045, 6, Core.PALETTE.roseDeep, Core.PALETTE.goldHi);
    Core.drawRosette(ctx, cx + s * 0.22, cy + s * 0.24, s * 0.045, 6, Core.PALETTE.roseDeep, Core.PALETTE.goldHi);

    // --- THE DROP CAP N -----------------------------------------------------
    // shadow behind letter for relief
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "rgba(20,12,5,0.40)";
    drawNGlyph(ctx, s, 0, s * 0.014);
    ctx.restore();

    // gilded body of the N
    ctx.save();
    ctx.translate(cx, cy);
    var gN = ctx.createLinearGradient(0, -s * 0.22, 0, s * 0.22);
    gN.addColorStop(0,    Core.PALETTE.goldHi);
    gN.addColorStop(0.45, accent);
    gN.addColorStop(0.55, Core.PALETTE.goldDark);
    gN.addColorStop(1,    Core.PALETTE.goldHi);
    ctx.fillStyle = gN;
    drawNGlyph(ctx, s, 0, 0);
    Core.setStroke(ctx, Core.PALETTE.ink, s * 0.010);
    drawNGlyph(ctx, s, 0, 0, true);
    ctx.restore();

    // highlight cap on top-left of N
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "rgba(255,245,210,0.55)";
    ctx.beginPath();
    ctx.moveTo(-s * 0.16, -s * 0.21);
    ctx.lineTo(-s * 0.10, -s * 0.21);
    ctx.lineTo(-s * 0.10, -s * 0.15);
    ctx.lineTo(-s * 0.16, -s * 0.15);
    ctx.closePath();
    ctx.fill();
    ctx.restore();

    // floral flourish on the diagonal stroke of the N
    ctx.save();
    ctx.translate(cx - s * 0.02, cy + s * 0.02);
    ctx.rotate(0.55); // along the diagonal
    // tiny vine with two leaves and a bud
    Core.setStroke(ctx, Core.PALETTE.sageDeep, s * 0.010);
    ctx.beginPath();
    ctx.moveTo(0, 0);
    ctx.quadraticCurveTo(s * 0.04, -s * 0.06, s * 0.10, -s * 0.04);
    ctx.stroke();
    Core.leafBead(ctx,  s * 0.03, -s * 0.04, s * 0.06,  0.6, Core.PALETTE.sageMist);
    Core.leafBead(ctx,  s * 0.08, -s * 0.07, s * 0.05, -0.4, Core.PALETTE.sageMist);
    // bud
    ctx.beginPath();
    ctx.arc(s * 0.11, -s * 0.05, s * 0.022, 0, Math.PI * 2);
    ctx.fillStyle = Core.PALETTE.roseDeep;
    ctx.fill();
    ctx.beginPath();
    ctx.arc(s * 0.11, -s * 0.05, s * 0.010, 0, Math.PI * 2);
    ctx.fillStyle = Core.PALETTE.goldHi;
    ctx.fill();
    ctx.restore();

    // tiny serif tips highlighted in gold
    // (drawn within drawNGlyph via stroke; nothing extra needed)

    // --- THEME-AWARE OUTER STROKE (contract) -------------------------------
    Core.setStroke(ctx, accent, Math.max(0.8, s * 0.018));
    ctx.beginPath();
    ctx.arc(cx, cy, s * 0.475, 0, Math.PI * 2);
    ctx.stroke();
}

// ============================================================================
// drawBFBPanel — compact BFB for the NCDE panel.
// Same leaded medallion + gilded serif N, but stripped of the laurel ring,
// whiplash vines and corner rosettes that turn to mud below ~28px. Tuned to
// stay crisp at small panel sizes; pair with Core.KithGlass(ctx, s) after.
// ============================================================================
function drawBFBPanel(ctx, s, accent, glow) {
    var cx = s * 0.5, cy = s * 0.5;
    accent = accent || Core.PALETTE.gold;
    glow   = glow   || Core.PALETTE.glow;

    // Leaded stained-glass medallion frame (segmented bezel + blue field)
    Core.drawTile(ctx, s, null, { accent: accent, glow: glow });

    // N shadow for relief
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "rgba(8,8,20,0.45)";
    drawNGlyph(ctx, s, 0, s * 0.018);
    ctx.restore();

    // gilded N body (slightly heavier weight so it reads when tiny)
    ctx.save();
    ctx.translate(cx, cy);
    var gN = ctx.createLinearGradient(0, -s * 0.24, 0, s * 0.24);
    gN.addColorStop(0,    Core.PALETTE.goldHi);
    gN.addColorStop(0.45, accent);
    gN.addColorStop(0.55, Core.PALETTE.goldDark);
    gN.addColorStop(1,    Core.PALETTE.goldHi);
    ctx.fillStyle = gN;
    drawNGlyph(ctx, s, 0, 0);
    // black came outline (thicker, for legibility on the blue field)
    Core.setStroke(ctx, Core.PALETTE.came, Math.max(0.8, s * 0.018));
    drawNGlyph(ctx, s, 0, 0, true);
    ctx.restore();

    // single top-left glint on the N
    ctx.save();
    ctx.translate(cx, cy);
    ctx.fillStyle = "rgba(255,245,210,0.6)";
    ctx.beginPath();
    ctx.ellipse(-s * 0.13, -s * 0.16, s * 0.05, s * 0.022, -0.6, 0, Math.PI * 2);
    ctx.fill();
    ctx.restore();
}

// Helper: draw an ornate serif capital "N" centred at the current origin.
// Uses Canvas text so the glyph is unambiguous; fillStyle (incl. gradients)
// applies through fillText, and strokeText paints the ink outline.
function drawNGlyph(ctx, s, ox, oy, strokeOnly) {
    ctx.save();
    var px = Math.round(s * 0.48);
    ctx.font = "900 " + px + "px 'Cinzel','Trajan Pro','Times New Roman','Liberation Serif',serif";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    // Optical: Cinzel's baseline sits slightly above true centre — nudge down.
    var y = oy + s * 0.03;
    if (strokeOnly) {
        ctx.strokeText("N", ox, y);
    } else {
        ctx.fillText("N", ox, y);
    }
    ctx.restore();
}
