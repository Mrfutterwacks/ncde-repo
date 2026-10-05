# main.qml + TilingManager.qml — game-window handling (done by main agent, 2026-07-11 evening)

Source findings: dives/Audit-game-fullscreen-window-handling.md + Root-cause-window-close-black-screen.md
(recovered from the crashed 14:29 session; saved in this session's scratchpad dives/).

## Defects fixed
1. **Every window — including Steam/Proton games — got a MotifFrame overlay** whose
   shape-punched input ring (12px sides / 44px titlebar band) overlays the client's edge
   UI, and the frame math shoved Steam's client to (-17,-21). Games explicitly ask for no
   decorations (_MOTIF_WM_HINTS decorations=0). Result: "hard to click things" in Sims 4
   build-a-sim / marketplace.
2. **Games were subject to the tile grid** (TilingManager resizes/insets them like editors).

## Changes (staged only — src/usr/share/ncde/)
- `main.qml` delegate: new `isGame` property (appId `steam_app_*`, `steam`,
  `steamwebhelper`, `gamescope`); game frames are never shown or registered
  (staggerTimer returns early → `registered` stays false → window never maps →
  `registerFrameWindowQml` never called → C++ never shapes an input ring);
  `destroyFrameWindow` now guarded by `frameRegistered`; MotifFrame also hidden
  (`visible: !isSettings && !isGame`, belt and braces).
- `TilingManager.qml` `updateLayout()`: same game test via role **0x107 = AppIdRole**,
  verified against NCDEWindowManager::roleNames() disasm (0x77cfc: 0x101 winId, 0x102 x,
  0x103 y, 0x104 w, 0x105 h, 0x106 name, 0x107 appId, 0x108 minimized, 0x109 maximized,
  0x10A title, 0x10B tiled) — games excluded from the grid.
  CORRECTION LOG: the first draft used 0x103 copied from Hud.qml — WRONG (0x103 is the
  Y-coordinate role; the exclusion would have silently never matched). Hud.qml's own
  UserRole+2/+3 title/appId reads are broken the same way, but Hud.qml has ZERO consumers
  (grep of all live QML) — dead file, not a live defect. Never copy role numbers from it.

## Verification (real output shown in session)
- Harness: scratchpad/qmlgate/qmlgate.cpp — QQmlEngine + QQmlComponent, offscreen, stub
  context props (pattern of session 86's frametest; qmllint alone is banned as a gate).
- `qmlgate farm/TilingManager.qml --create` → COMPILE OK + CREATE OK, exit 0.
- `qmlgate farm/main.qml` → COMPILE OK (full dependency tree); `--create` → CREATE OK, exit 0.
  (Farm = symlinks to live /usr/share/ncde with the two staged files overriding.)
- `diff` vs live: only the intended hunks (isGame block, staggerTimer guard,
  destroy guard, MotifFrame visible, tiling exclusion).

## NOT verifiable offscreen — live test required after deploy
- That an unframed Steam window gets correct clicks (needs Steam running post-relog).
- That the WM C++ tolerates a client with no registered frame. Precedent: audit read of
  manage()/registerFrameWindow disasm says frames are optional overlays (client is not
  reparented for framing); "ncde settings" already ships with an invisible MotifFrame.
  Risk is low but REAL — test plan: relog, open Steam, open a steam_app window, confirm
  (a) no ring/frame, (b) window at its own coordinates, (c) close/minimize via Steam's
  own chrome works, (d) normal apps still framed.

## Deploy (goes into the master patch script)
- Build: none (QML loaded from disk at runtime).
- Deploy: `sudo cp src/usr/share/ncde/main.qml src/usr/share/ncde/TilingManager.qml /usr/share/ncde/`
  (with .prebak-20260711-fullpatch backups first) + clear qmlcache + relogin.

## REGRESSION FOUND ON LIVE TEST — 2026-07-12 (Steam client never appeared)
The "risk low but REAL" item above bit: with this patch deployed, launching Steam showed
**nothing at all**. Root cause, confirmed from the binary (NCDEWindowManager.cpp decompile):
`registerFrameWindow` (@001b0e82) is the **only** path that `xcb_map_window()`s a newly-added
client (lines 2252 and 2302). The window-add/`start`/`data` paths never map a client themselves.
So "isGame → skip registerFrameWindowQml" doesn't just skip the *frame overlay* — it skips the
*only thing that maps the client*, so any isGame window is created but never mapped (invisible).
`xlsclients` confirmed `ncde steamwebhelper` was a live X client with no mapped window.
The isGame list included `steam` + `steamwebhelper`, which are the **Steam CLIENT UI window**,
not games — so the client itself was suppressed.

FIX (2026-07-12, QML-only): dropped `steam`/`steamwebhelper` from isGame in main.qml +
TilingManager.qml (kept `steam_app_*`, `gamescope`). Steam client now frames + maps normally
again (its pre-patch, known-good behavior).

STILL OPEN — actual game windows: `steam_app_*`/`gamescope` remain isGame, so by the SAME
coupling they will also never map (invisible) once a game is launched. QML alone can't give
"map without a frame" — registerFrameWindow always reparents+offsets+shapes. The correct fix
is the C++ **map-without-frame** path the `"ncde settings"` branch already uses (decompile
2248-2263: map client, NO reparent, empty shape = no ring, no offset). Routing games through
that branch is keyed on a literal appId in C++ → a LaPivot rebuild/Ghidra change, NOT QML.
Interim alternative if games are needed before that: remove `steam_app_*`/`gamescope` from
isGame too → games go back to framed+visible (the pre-patch ring/click annoyance returns, but
visible beats invisible).

## Ghidra-track leftovers (not in this patch)
- Proper `_NET_WM_STATE_FULLSCREEN` / override-redirect / no-decor handling inside C++ manage().
- `_NET_CLIENT_LIST` EWMH advertising (Steam overlay / capture tools).
- Global Ctrl+Alt+R grab (main.qml:69 handler only works with bare desktop focused —
  no XGrabKey in the binary; C++ change).
- Client-position inset (12,44) applied by C++ geometry paths for maximized windows —
  unframed games should now keep their own geometry, verify live.
