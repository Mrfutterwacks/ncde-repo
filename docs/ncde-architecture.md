# NCDE — Master Architecture Map

> **⚠️ CORRECTED 2026-07-17 — no production source tree exists anymore.** `~/ncde-staging/` (and the
> `ncde-wm-rebuild/src/decompiled/` oracle path nested under it) is gone — the dev machine that hosted
> it is gone, confirmed absent on this machine and the USB backup. Recovery now happens directly
> against the live binary: Ghidra-decompile `/usr/local/bin/LaPivot`, reconstruct class-by-class in
> `~/ncde-wm-rebuild/` — **partial**, most classes are still raw Ghidra output, not clean buildable
> source (see `docs/lapivot-rebuild.md`). Every "source is in the tree and compiles" claim below
> describes the pre-2026-07-08 workflow and should be read through that correction. QML was never
> lost — plain text at `/usr/share/ncde`.

Reverse-engineered from the built binaries in `[dead-legacy-tree]` (the C++ source recovery is
partial — the WM C++ was RECOVERED via Ghidra, reconstructed class-by-class in `~/ncde-wm-rebuild/`
(153 classes); the `.qml` files are plain text and editable). This is the whole-system
map — for us and the designer. Companion deep-dives: `lelan.md` (nervous system), `anim-policy.md`
(animation governor), `kickass-guard.md` (AI security), `zen.md` (kernel governor), `missing.md`
(exact wiring). **[E]** = verified in a binary/QML; **[INF]** = inference.

> Reconstructed by a 5-agent sweep of every NCDE binary + all 166 QML files. KickassGuard-deep and
> Zen sections are filled from their dedicated agents; see §11 status.

---

## 0. Anatomy

> **Design north star — WWCDED ("What Would CDE Do?"):** NCDE is CDE reimagined as a modern, coherent
> product (ToolTalk→`lelan`, Style Manager→`ncde`, the `dt*` suite→the NCDE apps, Motif→gilt/filigree/
> glass). macOS is only the polish/performance layer (Darwin internals = the design reference, see
> `anim-policy.md §2b`). It is **not** a GNOME/KDE clone — do the integrated, first-party move. Full
> framing in `PROJECT.md`.

- **Body & skeleton** = `ncde-wm` (the shell/compositor) + the desktop UI (`usr/share/ncde`, 166 QML).
- **Nervous system** = `lelan` (the `LElan` C++ hub in ncde-wm) — a signal-only event bus fanning
  ~80 D-Bus-sourced signals to widgets. **[E]**
- **Central backend** = `ncde` — the master theme + sysadmin object (1954 refs across 102 QML files).
  This, not `lelan`, is the workhorse widgets bind to. **[E]**
- **Brain** = `zen` — linux-zen kernel + the performance governor (see `zen.md`).
- **AI security brain** = `KickassGuard` daemon (Vesper/Ollama/Qwen/Chroma — see `kickass-guard.md`).

> **The operator's family metaphor (the canonical mental model):** **Lelan = mother** — wife of Zen,
> sister of Sentinel, mother of NCDE; the nervous system that controls everything (animations, RAM, GPU);
> all QML references her. **Zen = father/husband** — the linux-zen kernel, NCDE's *only* kernel, chosen
> for its built-in optimization. **Sentinel = Tía/aunt** — `io.ncde.Sentinel`, Lelan's sister; the
> hardware-hotplug feed. **NCDE = the child.** "It's all one thing" — one organism; lose Lelan and Zen
> loses his wife, Sentinel her sister, NCDE his mother — which is why Lelan is THE keystone rebuild.
> The WM C++ is being recovered via Ghidra (reconstruction workspace `~/ncde-wm-rebuild/`, partial —
> see `docs/lapivot-rebuild.md`) and the desktop survives regardless — so the operator is
> **"the living source code."**

**Key correction from the sweep:** the QML depends on **~15 injected context-property backends**, not
just `lelan`/`ncde`. Those host objects' source is being recovered via Ghidra decompilation of the
live binary, reconstructed class-by-class in `~/ncde-wm-rebuild/` (partial); the QML is plain text,
and their contracts are also reconstructed in §5. **[E]**

---

## 1. Binary / process map **[E]**

| Binary | Role | Registers D-Bus | Key classes |
|---|---|---|---|
| `usr/local/bin/ncde-wm` | The shell: WM/compositor + embedded apps (mail, calendar, notes, dashboard, notifications, global menu/HUD, theming) | `org.freedesktop.Notifications`, AppMenu Registrar `/com/canonical/AppMenu/Registrar` | LElan, AnimPolicy, NCDEEngine, NCDEWindowManager, + §2 |
| `usr/bin/ncde-portal` | Greeter **and** lock **and** screensaver **and** privileged session daemon (flag-selected) | — (client of login1) | portal::Daemon/XServer, Authenticator, GreeterBridge, SessionManager, IdleWatcher, StatusProvider, UserModel |
| `usr/bin/ncde-portal-helper` | Setuid PAM/utmp worker, slave of portal::Daemon over a frame protocol | — | portal::Frame/Reader, `writeUtmp`, PAM `conv` |
| `usr/bin/ncde-lock` → symlink to `ncde-portal` | Locker personality (`--lock`) | — | (ncde-portal) |
| `usr/bin/ncde-lock-xss` | `exec ncde-lock --lock` (xss-lock no-fork) | — | shell |
| `usr/bin/ncde-screensaver-notify` | `exec ncde-portal --screensaver` (xss-lock idle) | — | shell |
| `usr/local/bin/ncde-sentinel` | Python udev→D-Bus hardware bridge **+ applies Zen power hints** | **`io.ncde.Sentinel`** | (pyudev/dbus) |
| `usr/local/bin/ncde-x11-session` | X11 session bootstrap (env, picom, qmlcache, `.tmp` promote) → `exec ncde-wm` | — | shell |
| `usr/local/bin/ncde-command` | System Settings / Control Center | — | NCDEEngine, PackageManager (pacman), FontManager |
| `usr/local/bin/orchidee` | File manager (Miller-column/grid) | — | OrchideeFiles, BinnieTrash, Launcher, NCDEEngine, NCDEPalette |
| `usr/local/bin/binnie` | Trash | — | BinnieTrash |
| `usr/local/bin/verve-text` | Text editor | — | FileIO, Launcher |
| `usr/local/bin/abacus` | Calculator (pure GUI) | — | (shared NCDEEngine/Settings) |
| `usr/local/bin/magpie-talker` | **Serverless LAN messenger** (XEP-0174/Avahi) + **GPS location share** + relay fallback | **`com.ncde.MagpieTalker`** | MessageHub, BonjourDiscovery, Contact, Peer, KSSecret |
| `usr/local/bin/dovecote-relay` | Headless JSON-over-TCP **relay daemon** (off-LAN fallback for magpie) | — (listens on a port) | DovecoteRelay, RelayRecord |
| `usr/local/bin/hummingbird-courier` | **Gmail desktop client** (IMAP/SMTP + Google OAuth2 + IDLE/XOAUTH2); system mail handler | **`com.ncde.HummingbirdCourier`** | MailEngine, GoogleOAuth, MailAccount, MailFolderModel, KSSecret |
| `usr/bin/ncde-terminal` | Thin launcher → QML at `usr/local/share/ncde-terminal/qml` | — | (loads NCDETerminalGlass) |
| `usr/local/bin/ncde-chromium` (+ `-sync.sh`) | Bash: Chromium + NCDE theme extension + dark-mode flags | — | bash |
| `usr/local/bin/verdafetch` | Bash neofetch-style ("Verda", rose ASCII) | — | bash |
| `usr/local/bin/kickass-guard` | AI security daemon (separate manual) | `org.ncde.KickassGuard` | see `kickass-guard.md` |

---

## 2. `ncde-wm` embedded subsystems (beyond LElan/AnimPolicy/NCDEEngine/NCDEWindowManager) **[E]**

The window manager binary is really a full shell. Undocumented C++ classes inside it:

- **`NCDEMail`** — IMAP/SMTP email client (QSslSocket, `AUTH LOGIN`, threaded fetch/send; `SMTPResult`).
- **`NCDECalendar`** — appointments + todos + reminders.
- **`LeapFrogPond`** — notes + appointments organizer; exports CSV and `.lilypad`.
- **`DesktopWidget`** — conky-style dashboard: CPU/RAM/disk/net/battery/brightness/volume, top procs,
  MPRIS controls, removable-volume mount/unmount, **live weather** (WMO icons), **moon phase via NASA
  JPL Horizons** (`onHorizonsReply`). Has `setLElan`/`setAnimPolicy`/`setNotificationManager`.
- **`NotificationManager` + `FreedesktopNotificationsAdaptor`** — NCDE **is** the notification server
  (`org.freedesktop.Notifications`: Notify/CloseNotification/GetCapabilities + ActionInvoked/Closed),
  plus history/DND/unread.
- **`GlobalMenu` + `NCDEMenuBridge` + `AppMenuModel`** — global menu bar; GlobalMenu is the **AppMenu
  Registrar**; NCDEMenuBridge reads X11 `_KDE_NET_WM_APPMENU` + dbusmenu.
- **`HudManager`** — Unity-style searchable global-menu HUD.
- **`GliaSystemMenus`** — XDG `.desktop` scanner/launcher (apps + places).
- **`ThemeManager`** — theme/icon/cursor/GTK install/export/apply.
- **`NCDEIconManager`** — per-icon override packs.
- **`NCDEWorkspace`** — virtual desktops.
- **`CursorManager`** — Xcursor theme loader. **`TrayWatcher`** — XEmbed `_NET_SYSTEM_TRAY`.
- **`Launcher`** — app/exec launcher + session save/restore + screenshot + logout.
- **`VpnBridge`** — NetworkManager VPN watcher. **`PlayerBridge`** — MPRIS bridge.
- **`Settings`** — enormous config façade (display, dock magnification physics, fonts, power/lid,
  privacy/proxy/firewall, screensaver seasons, slideshow, filigree palettes, surface-glass, **Kickass**
  fields); live file-watch hot-reload (`onConfigFileChanged`).
- `NCDEEngine::setAutoLogin(QString)` spawns a QProcess (auto-login mgmt).

QML modules it registers: **`NCDEKit`/`NCDE.Controls`** (the widget library, §6), compositor QML at
`qrc:///qml/compositor/main.qml` + `ThemeTokens.qml`.

---

## 3. `ncde-portal` family (greeter / lock / screensaver / daemon) **[E]**

- One binary, four personalities via flags; `ncde-lock` is a symlink to it.
- `portal::Daemon` brings up an X server (`portal::XServer`, MIT cookie), spawns the QML greeter, and
  brokers PAM via the setuid `ncde-portal-helper` over a binary **`portal::Frame`** protocol
  (`Reader::getU8/getU32/getStr`). Helper writes utmp (`writeUtmp`).
- Context props to its QML: `Auth` (Authenticator), `Status`, `Users`/`UserModel`, `Sessions`, `Idle`,
  `Greeter` (GreeterBridge). QML: `qrc:/qml/{Greeter,Lock,Screensaver}.qml`.
- Screensaver = French "Saisons" seasonal palettes (hiver/printemps/été/automne + "Le Nocturne"),
  Keats quotes (`.pragma library`), analog clock. Forwards `--season`, `--fps`, etc.
- D-Bus client of `org.freedesktop.login1` (Can*/power actions); honors `org.freedesktop.ScreenSaver`
  + xss-lock (`XSS_SLEEP_LOCK_FD`).

---

## 4. The apps — notable surprises **[E]**

- **magpie-talker + dovecote-relay = a serverless P2P messenger.** XEP-0174 serverless XMPP over
  **Avahi** mDNS, direct `QTcpServer` peer links, file transfer, and **live GeoClue2 GPS sharing on a
  map** (`NCDEGeoChart.qml`). `dovecote-relay` is a headless TCP relay used when peers aren't on the
  LAN. Config: `~/.config/ncde/magpie/{identity,contacts,relay}.json`.
- **hummingbird-courier = a real Gmail client** — `imap.gmail.com`/`smtp.gmail.com`, **Google OAuth2**
  via a loopback redirect (`GoogleOAuth::startFlow/exchangeCode`), IMAP IDLE, XOAUTH2. It's the system
  mail handler (`session-defaults.json: "mail":"hummingbird-courier"`).
- **ncde-command** = the Control Center: `NCDEEngine` (theme/wallpaper/network/bluetooth/printers/
  **location**), `PackageManager` (pacman wrapper w/ PolKit-style `submitPassword`), `FontManager`.
- **No second LLM** anywhere — the only AI is the KickassGuard stack. **[E]**
- Shared building blocks across all GUI apps: `NCDEEngine`, `Launcher`, `NCDEPalette`, `Settings`,
  and **`KSSecret`** (libsecret/`org.freedesktop.Secret.*` keyring, used by magpie + hummingbird).

---

## 5. The QML backend contract — ~15 injected context properties **[E]**

The QML binds to these host objects (their source is being recovered via Ghidra decompilation of the
live binary, reconstructed class-by-class in `~/ncde-wm-rebuild/`, partial; contracts below were also
reconstructed from usage):

| Backend | Role | Contract highlights |
|---|---|---|
| **`ncde`** | Master theme + sysadmin (1954 refs/102 files) | tokens `accent, gilt0–5, wine1–4, surface, surfaceGlass, panelBg, fontSize_*, glow, border, darkMode`; methods `saveTheme, applyPreset, setBaseColor, setAccentName, setUiFont, connectNetwork/Vpn, setWifiEnabled/setBluetoothEnabled, addUser/removeUser/setUserAdmin, setTimezone/setNtp/setAutoLogin, setDefaultPrinter`; signals `onThemeChanged`(27×)`, onDarkModeChanged, onWeatherChanged, onStatsChanged, onMediaChanged, onClockChanged` |
| **`settings`** | Config store (read via `gv(settings,key,def)`) | text shadow/outline, fonts, `uiScale`, `screensaver*`; `saveFontSettings, applyFontSettings, saveDockPrefs` |
| **`windowMgr`** | Compositor/WM | `activateWindow, move/resize/minimize/close Window, setTiled, snapZone, systemCommand, winIdForName`; props `data, count, activeIndex, mouseX/Y, screenWidth/Height` |
| **`widget_data`** | Live desktop-widget feed | `mediaActive/Playing/Position/Duration/Title/Artist/Album, volume, mounted/removableVolumes, timeHour/Minute/AMPM, cpuTotal, ramPercent, diskPercent, batteryLevel` |
| **`theme`** | Theme tokens injected into widget contexts | `fontFamily, fontSmall, textColor, textStyle, textShadow*` |
| **`orchidee`** | File-manager backend | `entries, home, makeFolder, moveTo, trash, duplicate, addToDock, loadViewMode/saveViewMode, launchBinnie` |
| **`mail`** | Mail backend (Hummingbird) | sub-object `current`; `messages, folders, contacts, account*, quotaGB, deleteMessage, saveSignature, startOAuthFlow` |
| **`hub`** | Chat backend (Magpie) | `activeId, presence, searchResults, directs, me*, location, openConversation, setTyping, start` |
| **`pkgMgr`** | Package manager (NCDECommand) | `search, getInstalled, checkUpdates, updateAll, install/removePackage, submitPassword`; `updateCount, results, status` |
| **`fontMgr`** | Font manager | `refresh, installFont, submitPassword`; `families, total, fontInstalled` |
| **`iconManager`** | Icon themes | `listIcons, importPack, applyPack, replaceIcon, restoreAll` |
| **`calBackend`** | Calendar/todo | `appointments, todos, upsertAppointment, toggleTodo, fireReminder` |
| **`binnieTrash`** | Trash | `items, restore, remove, emptyAll, rewindHours, launchOrchidee` |
| **`lelan`** | Event bus (signal-only) | `onPackageStateChanged` (1 ref) — see `lelan.md` for the full ~80-signal surface |
| **`hudManager`** | HUD event source (signal-only) | `Hud.qml` `Connections{target:hudManager}` |

---

## 6. NCDE widget library + singleton **[E]**

- **`controls/qmldir` → module `NCDE.Controls`** — 23 reusable controls: `NCDEKit, NCDEButton,
  NCDEField, NCDEPasswordField, NCDEComboBox, NCDECheck, NCDERadio, NCDEToggle, NCDESlider,
  NCDESpinBox, NCDEProgressBar, NCDEBusyIndicator, NCDETabBar/TabButton, NCDEScrollBar/ScrollView,
  NCDEDialog, NCDEMenu, NCDEGroupBox, NCDESeparator, NCDESectionLabel, NCDEVellum, NCDEModeTransition`.
- **Root `qmldir` → `singleton SetTheme 1.0 SetTheme.qml`** — used by ~10 settings tabs.
- Heavily-reused top-level types: `NCDEIcon, MotifFrame, GliaBar/GliaMenu*, Dock, BottomPanel,
  NCDEGlassSurface, NCDEParchmentSurface, NCDEHandbook, DesktopWidget`, the `Mucha*` / `SN*`
  (SalonNocturne) / `HB*` (Hummingbird) / `Cal*` / `Orchidee*` families. Many small types are Qt6
  inline `component X:` defs, not separate files.

---

## 6b. The GTK/Chromium bridge — how Filigree reaches non-Qt apps **[E]** (restored 2026-07-07, punchlist §2.2)

**The one pipeline (operator, 2026-07-01 + 2026-07-07 "this works with NCDEkit etc"):**
**Filigree** (Settings palette-picker UI) → **Iris Chroma** (the 90 preset palettes,
`kPresets.inc`) → **NCDEKit** (the shared QML token resolver) → **`NCDEEngine`** (C++ —
`recompute()` derives every token the QML reads) → **out to every non-Qt surface** via three
engine methods (recovered from the original binary; `NCDEEngine.h`'s `compass7/lelan/` working
copy no longer exists — corrected 2026-07-17, see the banner above — current recovery target is
`~/ncde-wm-rebuild/`):

- **`applyGtkTheme(bool dark)`** — writes `~/.themes/NCDE/gtk-3.0/gtk.css` (imports
  `_palette-dark|light.css` + `_accent.css` + `_rules.css`); swaps the palette `@import` inside
  `~/.config/gtk-4.0/gtk.css` in place; replace-or-appends `gtk-theme-name=NCDE` +
  `gtk-application-prefer-dark-theme` in `~/.config/gtk-4.0/settings.ini`; runs
  `gsettings set org.gnome.desktop.interface color-scheme|gtk-theme` (GTK3 apps + the portal
  react live); runs `/usr/local/bin/ncde-chromium-sync.sh dark|light`; regenerates
  **`~/.gtkrc-2.0` (GTK2)** with the live accent.
- **`applyGtkAccent()`** — regenerates `_accent.css` (GTK3 + GTK4 copies) from the engine's
  CURRENT accent (`@define-color ncde_accent …; theme_selected_bg_color @ncde_accent`).
- **`seedGtkUserConfig()`** — first-run copy of the palette/rules seeds from
  `/usr/share/themes/NCDE/gtk-{3,4}.0` into the user config, never clobbering user files.

**Fires at five sites** (same as the original binary): `setDarkMode`, `setDarkModeLock`,
`applyPreset` (Iris Chroma), `sampleWallpaper`, and `loadTheme` — loadTheme is both the
**once-at-login leg** (every native app's `main()` loads `active-theme.json` at startup) and the
**live-resync leg** (the `QFileSystemWatcher` on `active-theme.json` re-enters `loadTheme` in
every running NCDEEngine process whenever Filigree saves — this is how "Filigree is global"
reaches GTK).

**These are NOT themes** (operator: "ncde does not use themes.. it uses filigree to change the
shell globally.. but we had to make the gtk stuff so it would work — these are defaults") — the
GTK/Chromium files are one-way **generated bridge output**; never hand-edit them, never treat
them as a parallel theming system. Static shipped defaults: `etc/skel/.themes/NCDE/gtk-3.0`
(+ `home/live` and `var/lib/ncde-portal` copies) and `usr/share/themes/NCDE/gtk-2.0/gtkrc`
(created 2026-07-07 so `gtk-theme-name="NCDE"` resolves for GTK2; the engine's per-user
`~/.gtkrc-2.0` rewrite overrides it live). Proof harness (historical — its `compass7/lelan/`
location is gone, see banner above): `test_gtk_theme.cpp` (16/16, byte-matches the original
binary's own gtkrc output).

---

## 7. D-Bus surface **[E]**

- **NCDE registers/owns:** `org.freedesktop.Notifications` (ncde-wm), AppMenu Registrar
  `/com/canonical/AppMenu/Registrar` (ncde-wm), `io.ncde.Sentinel` (ncde-sentinel),
  `com.ncde.MagpieTalker`, `com.ncde.HummingbirdCourier`, `org.ncde.KickassGuard` (the guard daemon).
- **NCDE subscribes/consumes:** login1, UPower, UDisks2, NetworkManager (+VPN), BlueZ, GeoClue2,
  net.hadess.PowerProfiles, PackageKit, timedate1/locale1/hostname1, portal.{Desktop,Settings,
  MemoryMonitor}, org.gnome.desktop.interface, MPRIS players (+ app watches: Spotify/Discord/Steam),
  `com.canonical.dbusmenu`, `org.freedesktop.Secret.*`, `org.freedesktop.Avahi.*`,
  and `org.ncde.KickassGuard` (via lelan).

---

## 8. System dependencies **[E]**
GeoClue2 (used by ncde-wm weather/nightlight, magpie GPS, ncde-command location); libsecret keyring
(`KSSecret`); Avahi (magpie); PipeWire/Pulse Core1 (audio); picom (compositor/glass); pacman + PolKit
(ncde-command); a running Ollama + Chroma (KickassGuard); NASA JPL Horizons + a weather API (network,
DesktopWidget).

---

## 9. Dedicated manuals (cross-ref)
- `lelan.md` — the nervous system (full backend map + per-subsystem D-Bus recipes + rebuild).
- `missing.md` — exact handler-slot wiring for the 15 lelan subscriptions + the `ncde` vs `lelan` split.
- `anim-policy.md` — the animation governor (never-stall) + macOS-mapped optimization.
- `kickass-guard.md` — the AI security daemon (Vesper/Ollama/Qwen/Chroma + 7 engines).
- `zen.md` — the kernel performance governor.
- `lelan-references.txt` — raw symbol dump.

---

## 10. Recovered-source map & packaging gaps **[E]**
- **All 15 QML backends + every ncde-wm subsystem are host C++.** Recovery is via Ghidra decompilation
  of the live `/usr/local/bin/LaPivot` binary, reconstructed class-by-class in `~/ncde-wm-rebuild/`
  (153 classes) — **partial**, most classes still raw decompiled output, not clean buildable source
  (see `docs/lapivot-rebuild.md`); the QML is plain text, never lost.
  Header comments in many QML files also document the intended backend contracts.
- `usr/share/ncde/screensaver/` is **empty** (low-confidence packaging gap — no QML Loader reads it;
  the screensaver scene runtime may live in the binary or be unshipped). **[VERIFY]**
- `qrc:/shaders/...colorwheel.frag.qsb` is compiled into the host binary (not a tree miss).
- No missing QML component files — every custom type resolves to a file or a Qt6 inline component.

---

## 11. Sweep status — COMPLETE (all 5 agents)
- ✅ Core/session binaries · ✅ App binaries · ✅ All QML · ✅ KickassGuard deep-dive · ✅ Zen governor.
- KickassGuard deep findings → `kickass-guard.md` §9 (ContextBuilder/ThreatEngine, dbus introspection
  XML, ThreatContext/Verdict schemas, vesper:latest/nomic-embed-text/mitre-attack, nft + audit rules).
- Zen governor → `zen.md` (self-boost via autogroup/SCHED_FIFO/uclamp; sentinel cpufreq+dirty_ratio;
  no kernel detection; no THP/EPP/cgroup).

## 12. Completeness verdict (see `ncde-completeness-audit.md`)
All NCDE's own code is present (20/20 binaries, 166 QML, lelan in ncde-wm). **Missing runtime deps that
break features:** geoclue, power-profiles-daemon, packagekit, nss-mdns (desktop features); clamav,
rkhunter, fail2ban, ollama, chromadb + the `vesper:latest`/`nomic-embed-text` models + `mitre-attack`
seed, the `kickass-guard.service` unit, and `/var/lib/ncde-kickass` (the entire security brain).
Remediation split (install vs designer-build) is in `build-the-missing.md`.
