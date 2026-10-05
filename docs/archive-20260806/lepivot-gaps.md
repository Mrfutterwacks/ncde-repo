# lepivot-gaps.md — what Le Pivot (lelan-host) is missing vs the live desktop

> **Created 2026-06-26.** Goal of the effort (operator): Le Pivot is the host we're building — we **add
> what's missing**, we are NOT recreating ncde-wm. The live desktop + the unstripped binary
> `/usr/local/bin/ncde-wm.baseline-20M` are only the *reference* for what each missing piece must do.
>
> **Method:** three-way diff — DEMAND (what the live `/usr/share/ncde/*.qml` calls) ∪ TRUTH (what the
> original binary exposes) − HAVE (what compass7 `~/ncde-staging/compass7/lelan/` provided at the
> time). Every agent finding was **re-verified against the live system** before landing here (agents
> over-flag — operator's standing warning). Build/verify per `CLAUDE.md` discipline:
> read→audit→Xephyr-prove→operator integrates; ncde-wm stays the bootable fallback; **build gate
> holds (no ISO until this is done + audited).**
>
> **⚠️ CORRECTED 2026-07-17 — `~/ncde-staging/` (including `compass7/lelan/`) no longer exists**;
> the dev machine that hosted it is gone, and the original C++ source is genuinely lost (no copy
> anywhere, including the `compass7` handoff bundle — see `CLAUDE.md` §10). The session-progress
> entries below describing that workspace are dated historical records of work actually done at the
> time; leave them as-is. Where this doc points at that path as something to go *read now* (the
> "Current state" section below), that instruction is stale — the current recovery path is
> Ghidra-decompiling the live `/usr/local/bin/LaPivot` binary into `~/ncde-wm-rebuild/`, see
> `docs/lapivot-rebuild.md` for per-class status.

---

## BOTTOM LINE — STALE, see this doc's own later progress notes

**Correction (2026-06-30 night):** this summary predates the doc's own "SESSION PROGRESS" entries below,
which show the gap described here CLOSED — confirmed live: `registerFrameWindowQml`
(`NCDEWindowManager.h:404`), RandR (`xcb_randr_select_input`), and XFixes cursor hide
(`xcb_xfixes_hide_cursor`) are all present and building. Read the progress log below, not this line, for
current state.

~~The window-decoration / reparent layer in `NCDEWindowManager`.~~ Le Pivot renders the desktop surfaces
and provides every context object the QML needs, but it never wraps app windows in a **MotifFrame** (no
container, no reparent, no input shape). Everything else is built and working. The fix is item-by-item below.

---

## SESSION PROGRESS — 2026-06-27 (parity pass: live ncde-wm mined as the baseline)
**Mandate (operator): Le Pivot = the host; the running `ncde-wm` = the work already PERFECTED → Le Pivot must
BEHAVE identically. Mine the live desktop (it's the answer key), don't clone the binary.** Mined `:0` live
(ncde-wm PID 844) with xwininfo/xprop and confirmed: geometry already matches (container=client+24×+58,
glass=+48×+82, offsets −12/−32, −24/−44); focus is set directly on the client (passive, WM_HINTS input=True);
the WM advertises `_NET_SUPPORTED`=4 atoms and does NOT write `_NET_ACTIVE_WINDOW`; container depth24/not-OR,
glass depth32/override-redirect. Fixes staged in `NCDEWindowManager.h` + `CMakeLists.txt` (compiles clean, EXIT=0):
- ✅ **`activateWindow` raises the WHOLE stack** (container carries client; glass restacked above it) instead of
  raising only the client (a no-op inside the container) → fixes **client detaching from MotifFrame** on click.
- ✅ **minimize/unminimize hide+restore the whole stack** (glass+container+client) + re-focus on restore →
  no ghost frame left on minimize.
- ✅ **#3 RandR resolution tracking** — `xcb_randr_select_input(SCREEN_CHANGE)` + `onRandRScreenChange` (adopt
  W/H from the event, re-clamp off-screen windows, emit `screenConfigChanged`) + `m_randrPresent/m_randrFirstEvent`;
  CMake `xcb-randr`. The "real screen res not found" fix → maximize geometry + WM screen size stay correct.
  ⚠️ **Widget placement caveat:** desktop widgets anchor to Qt's `Screen.width/height` (DesktopWidget.qml
  right/top+40/bottom−28), which Qt tracks itself — so if widgets are still misplaced on the test host, mine
  Le Pivot's live `Screen.width` vs the desktop-window geometry (resolution at startup), NOT just the WM.
- ✅ **FOUNDATION — Lelan now governs the WM (the reframe; operator: "if a house has no foundation it sinks").**
  Mined ncde-wm's Lelan wiring graph from the binary (memory [[lelan-governs-the-wm]]): `Lelan→AnimPolicy→WM
  cursor timer`, `WM→Lelan` geometry, `Lelan→DesktopWidget ~11 sigs`. Le Pivot's `main.cpp` had the WM as an
  ISLAND (no AnimPolicy, no Lelan). Poured:
  - **`NCDEWindowManager::setAnimPolicy(AnimPolicy*)`** — gates the 16ms cursor-feed timer on
    `AnimPolicy::screenIdle` (run active / stop idle); `main.cpp` calls `windowMgr.setAnimPolicy(&animPolicy)`.
  - **`Lelan::onWMScreenConfig(int,int)`** (new public slot) re-broadcasts `screenConfigChanged()` +
    `screenGeometryChanged()` (mirrors `onSentinelDisplayConnected`); `main.cpp` connects
    `windowMgr.screenConfigChanged → lelan.onWMScreenConfig`.
  - **XFixes `hide_cursor`** in `start()` (CMake `xcb-xfixes`) → kills the **black hardware cursor** so only
    the blue Kith cursor shows (operator: "there should only be one cursor, mine"). Baseline does exactly this.
- ⚠️ **Cursor FREEZE still unexplained by static analysis.** The feed is byte-identical to the baseline
  (disasm of `start()::lambda#2`: `QCursor::pos()`), and the timer runs — yet the operator saw Kith frozen at
  0,0 on the CURRENT binary ("I just came from the test"). XFixes fixes the black 2nd cursor for sure; the
  freeze needs a LIVE diagnosis on the test host (instrument `pollPointer`/`QCursor::pos()` while Le Pivot runs).
- ⏳ **NOT verified on real GL** — operator tests on the next "NCDE (test host)" login. Typing root cause still
  open (stacking fixed; if terminal still won't type, mine Le Pivot's live stack with xwininfo/xprop while it runs).

## SESSION PROGRESS — 2026-06-26 (Le Pivot WM build)
Compass7 `NCDEWindowManager.h` — all built + compiling; X-structure-verified in Xephyr :2 (live Verda):
- ✅ **Frame core** (#1 in punch-list) — container/reparent/shape; Verda framed, geometry pixel-exact.
- ✅ **Move** — was dead (raw `xcb_query_pointer` on Qt's shared conn = silent); fixed with **`QCursor::pos()`**.
  Operator dragged Verda → moved. + **lockstep glass** so the Tiffany frame doesn't trail the content.
- ✅ **Placement/size → open MAXIMIZED** — windows open filling the screen (container = full screen).
- ✅ **Window-state foundation (#2 done)** — `WindowEntry.maximized`, `maximized` model role, **`setMaximized(winId,bool)`**
  (mirrors `_NET_WM_STATE_MAXIMIZED_VERT/HORZ`), `isMaximizedForName`/`isMaximized`, atoms. One source of truth.
- 🖥️ **Artifacts diagnosed (black pieces / detached copper / glow-mess) — TWO real bugs + one GL limit:**
  - **BUG (fixed): ARGB container.** `picom.conf:21` says **"ncde-container — opaque, same bbox as frame."**
    My `createContainer` made it ARGB transparent-black → the bronze rails + Tiffany glow rendered over black
    = the "black pieces / detached copper." **Fixed → opaque container** (`argb=false`). Frame (ncde-frame) stays ARGB.
  - **BUG (fixed): BOUNDING shape.** Hard rectangular clip chopped the soft glow ("messing with the motif
    glow"). **Dropped it** — keep INPUT only. The client shows through the frame's ARGB center (picom composites
    it), not via a shape hole.
  - **GL limit (test-only):** the frame's ARGB center needs picom's GL compositing → works on dev's real GL
    ("the hole on dev is perfect" — operator), but nested Xephyr has no GL so the center can't composite there.
    ⟹ **the glass/hole/glow can only be validated on dev**, not Xephyr.
- **picom architecture (operator, confirmed by `picom.conf`):** picom is "just a battery — draws the desktop."
  `shadow=false`; EVERY `ncde-*` window is excluded from shadow/blur/fade/focus. The glass blur + MotifGlow are
  100% the QML engine (filigree = the brain). picom's only real jobs: base compositing + the cursor (no black box).
- **Cruft:** `/usr/share/applications/plank.desktop` = leftover Archcraft dock entry → remove/exclude (NCDE's
  dock is the QML Dock).

**Remaining (need real GL / dev to validate visually):**
- #3 QML wiring (dev-safe, guarded): `main.qml` `isMaximized: model.maximized===true`; MotifFrame emerald button →
  guarded `windowMgr.setMaximized`; **Dock state-dot color** (🟢max 🟡min 🔴close-flash→🔵idle).
- #4 window **titles** (`getWindowTitle`/`onPropertyNotify` → frame shows "Verda" not "Window").
- Maxed windows shouldn't be draggable off-screen (minor); the glass `BOUNDING` shape stays (faithful) unless dev shows it clips.

## The sweep result — what is NOT a gap (preserve; do not re-chase)

### ✅ Already built & working in Le Pivot (live + static verified)
All 17 injected context objects and every property/method the live QML calls:
`lelan · ncde (NCDEEngine) · settings · theme · widget_data · animPolicy · launcher · notifications ·
windowMgr (everything EXCEPT the frame layer) · calBackend · ncdeWorkspace · appMenuModel · window · pond ·
gliaSystem · geo · hudManager`, plus `WindowTyper`. The 8 settings tabs, the senses, the colour engine,
the menu system (`gliaSystem`+`appMenuModel`) — all done.

### ✅ Agent FALSE-POSITIVES (flagged "missing", proven fine on live)
| Flagged | Reality (verified) |
|---|---|
| `desktop` | the **root `Window { id: desktop }`** in `main.qml:8`; `wallpaperPath` = property at `main.qml:16`. QML id, not a C++ object. |
| `kithCursor` | the **`KithCursor { id: kithCursor }`** instance at `main.qml:326`. QML id. |
| `pkgMgr` / `fontMgr` / `prompterBox` | belong to the **`ncde-command`** app (separate binary), not the host. `fontMgr` is even `typeof`-guarded. |

### 🚫 Abandoned design — do NOT restore as a gap (operator, 2026-06-26)
The original binary injects 3 context objects Le Pivot lacks — **`menuBridge` (NCDEMenuBridge), `globalMenu`
(GlobalMenu), `themeManager` (ThemeManager)**. **Live QML references each: 0 files.** The **global/dbus menu
was abandoned long ago** (operator) — the desktop uses `gliaSystem`+`appMenuModel` now. `themeManager`'s
theme/icon/cursor-install job is covered by `settings` + the engine. **Not gaps. Do not add them.**

### ℹ️ Architecture notes (not gaps)
- In the original, **`geo` is an ALIAS of the same `NCDEEngine` instance** (`ncde`==`geo`). Le Pivot uses a
  separate `NCDEGeo` delegating to Lelan — functionally equivalent; all `geo.*` props the QML reads resolve.
- The original does **not** inject `window`; Le Pivot's `window` (ScreenInfo) is an extra, harmless, and the
  live QML doesn't depend on it (`window` data comes via the `windowMgr` model).
- `ncde.decorationPath`/`updateDecorationPath` exist on the original engine (per-theme decoration asset
  folder). The **shipped `MotifFrame.qml` does not read it** (it draws from `ncde.*` colour tokens, which the
  engine already provides). Treat as not-needed unless a live MotifFrame binding proves otherwise.

---

## THE GAP — `NCDEWindowManager` decoration/reparent layer

### Current state of `~/ncde-staging/compass7/lelan/NCDEWindowManager.h` — HISTORICAL, path is gone
**(corrected 2026-07-17: this path no longer exists — see top-of-doc correction. The section below
describes the state of that file as of 2026-06-26/27; for the current recovery status of this class
check `docs/lapivot-rebuild.md` against `~/ncde-wm-rebuild/`.)**
- `registerFrameWindowQml(client, frame)` — **STUB**: `m_qmlFrames.insert(client, frame);` then returns.
  Never creates a container, never reparents, never shapes. ← **proximate cause of "no frames"**
- `manage(w)` — tracks the window + sets event masks + inserts into the model, but **never reparents**;
  `WindowEntry.frame` stays `0`.
- `setTiled(quint32,bool) {}` — **empty stub**.
- `start()` — grabs SubstructureRedirect; **bails (returns false, manages nothing) if another WM holds
  redirect** — this is *by design* (so it never fights the live ncde-wm in Xephyr). Keep.
- Interim cursor poll (`xcb_query_pointer`) is the only frame-related edit staged so far; item 5 replaces it.

### The QML side already drives it (no QML change needed)
`main.qml:214-275` — `Instantiator { model: windowMgr; delegate: Window { … } }` builds one frameless ARGB
`frameWin` per managed window, then on `onSceneGraphInitialized` calls
**`windowMgr.registerFrameWindowQml(model.winId, frameWin)`** (`main.qml:246`) and on destruction
`windowMgr.destroyFrameWindow(model.winId)` (`main.qml:252`). Inside sits the **`MotifFrame`** decoration.
So the QML→C++ seam already exists; the C++ side just has to do the X11 work.

### Naming note (operator, 2026-06-26 — don't confuse name vs look)
**`MotifFrame` = the NAME** (the Motif/CDE window-decoration lineage — WWCDED). **The SKIN is Tiffany
stained-glass**, not literal Motif bevels — bronze rails, leaded jewel panes, sapphire/emerald/ruby
cabochon buttons, amber lamp-glow. It's self-documented in the file text (`MotifFrame.qml:1`: *"Tiffany
Studios stained-glass window frame for NCDE"*). **Do NOT rename it and do NOT restyle it toward generic
Motif.** The host work is pure X11 plumbing; the Tiffany visual lives entirely in `MotifFrame.qml` (untouched).

### MotifFrame contract (what the C++ must satisfy — from `/usr/share/ncde/MotifFrame.qml`)
Reads: `ncde.*` colours, `theme.fontFamily/fontMedium`, `animPolicy.screenIdle` (glow gating).
Calls back: `windowMgr.{minimizeWindow, activateWindow, setTiled, moveWindow, resizeWindow, closeWindow,
screenWidth(), screenHeight(), mouseX, mouseY}`.

### Authoritative frame metrics — LIVE-CONFIRMED this session
Watched on the running desktop (thunar terminal, client `784×456`):
```
client    xfce4-terminal  784×456  @ +12,+32  inside container   (model w,h)
container ncde-container  808×514  @ +307,+414   = w+24 × h+58, at x−12, y−32
glass     ncde-frame      832×538  @ +295,+402   = w+48 × h+82, at x−24, y−44
```
Constants: `titleH=32, frameLeft=12, frameRight=12, frameBottom=26, shadow=12`. (Binary AND MotifFrame.qml
agree; live geometry matches to the pixel.)

---

## PUNCH-LIST (recovery-doc priority order — one change at a time, each Xephyr-verified)

> Full spec for every method is in `~/ncde-docs/ncde-wm-recovery.md`. Verify each rebuilt method against
> `ncde-wm.baseline-20M`. **CMake will need:** `xcb-randr`, `xcb-shape`, `xcb-xfixes`, `xcb-screensaver`.

1. ✅ **DONE + VERIFIED (Xephyr :2, 2026-06-26)** — compiles clean; on :2 a launched xfce4-terminal got the
   full `ncde-frame`(712×538)/`ncde-container`(688×514)/client(664×456 @12,32) stack, client reparented INTO
   the container, geometry pixel-exact. **FRAME CORE (THE fix — brings windows back).**
   `findArgbVisual()` → `createContainer(x,y,w,h,argb)` → `registerFrameWindow(client, glassWinId)` (set the
   4 hashes client↔glass/client↔container, reparent client into container at 12,32, map, place glass, stack
   glass above container, `setFrameInputRegion`) → **fix `registerFrameWindowQml` to actually call
   `registerFrameWindow`** (cast frame→QWindow→winId). + `destroyFrameWindow`.
   **Accept:** an app maps → a MotifFrame appears around it and the client is clickable (center hole shaped).

2. **MOVE/RESIZE move the container+glass, not the client.**
   `moveWindow` → container `{x−12,y−32}` + glass `{x−24,y−44}` (client stays 12,32 inside container).
   `resizeWindow` → client `{w,h}`, container `{w+24,h+58}`, glass `{w+48,h+82}`, then **re-call
   `setFrameInputRegion`**. + `moveTiledWindow` single combined pass. + drop the `setTiled` stub if tiling
   is wired. **Accept:** drag titlebar moves the whole stack; edge/corner resize reshapes; no off-screen drift.

3. **RandR resolution tracking** (the "real screen res not found" fix).
   `xcb_randr_select_input(root, SCREEN_CHANGE)` + `onRandRScreenChange` (update screenW/H **from the
   event**, re-clamp off-screen windows) + emit `screenConfigChanged(W,H)`. **Accept:** resolution change is
   picked up; `windowMgr.screenWidth()/Height()` stay correct (MotifFrame maximize uses them).

4. **Event/EWMH/identity completeness.**
   20 atoms (`internAtoms`), `setupEwmh`, full `handleEvent` (10 cases — fix the UNMAP-deletes-minimized
   bug), `onPropertyNotify`/`getWindowTitle`/`getWindowClass` (titles refresh), the `onMapRequest` filter
   ladder (override_redirect + `_NET_WM_WINDOW_TYPE` undecorated paths). **Accept:** titles update live;
   dialogs/menus/tooltips map undecorated; minimized windows survive unmap.

5. **Cursor — faithful Kith cursor feed.**
   Replace the interim `xcb_query_pointer` poll with **`QCursor::pos()`** (16ms QTimer) + XFixes
   `hide_cursor(root)` + **AnimPolicy idle-gating** (stop the timer when `screenIdle`). The **blue Kith
   cursor** (`KithCursor.qml`) is software-drawn; the HW cursor is hidden so it shows. ⚠️ NOT "NCDE-Poseidon"
   (that's a separate X cursor theme). **Accept:** the blue Kith cursor tracks the pointer; not frozen.

6. **picom + glass.**
   `watchPicomOwner`/`onPicomDied` (restart `picom --config /usr/share/ncde/picom.conf`); `registerGlassWindow`
   / `registerMenuGlassWindow` / destroy (terminal + Glia/LeapFrog menu glass). **Accept:** glass panes
   register; picom auto-restarts if it dies.

---

## Window behaviour — operator intent (2026-06-26, live QA of the Verda test)
- **Windows open FIXED FULLSCREEN by default.** In the max state **everything goes away** — top panel +
  bottom dock fully hide (not just hover-intellihide; the chrome disappears while a window is fullscreen).
  ⟹ the WM's new-window default = FULLSCREEN (not the corner 100,80 I first added).
- **NOT borderless** — MAX is a *framed* fullscreen: the Tiffany frame fills the ENTIRE screen but the
  **titlebar stays visible at the top** (title + the 3 cabochon buttons remain clickable). Only the DESKTOP
  chrome (top panel + dock) disappears, never the window's own frame. This is exactly MotifFrame.qml's
  existing maximize (fill to `screen − frame`, titlebar at top) — visual already correct.
- **Emerald max/min button toggles:** MAX = that framed-fullscreen ⇄ restore ("min") = a **small, DRAGGABLE
  square** window (centered default size, NOT the last-dragged size). The small square is the state you move
  around. (Sapphire button = the separate **minimize-to-dock**.)
- **What hides vs stays when maximized:** top panel + dock HIDE (Intellihide, count-based — verified); desktop
  WIDGETS (clock/weather/stats/Salon, right side) STAY behind the window (desktop-level). Both already work.
- ⟹ implies: window opens with isMaximized=true + a default small saved geometry for the first restore;
  and the panels/dock must hide whenever a window is fullscreen. Verify how the SHARED QML already does this
  before implementing the WM side.
- **Titlebar buttons (Tiffany cabochons), left→right:** ① sapphire = **minimize to dock** · ② emerald =
  **maximize / restore (max-min toggle)** · ③ ruby = **close**. MotifFrame.qml already wires this order — keep it.
- **Busy cursor = a rose** (rose-window shape, KithCursor); verdafetch's logo is a **rose** too (Verda's emblem).

## Dock state-dot — color-coded by window state (operator, 2026-06-26; missing from dev AND tree)
**ONE dot per app medallion** (the existing `indicatorDot` "leaded glass bead" in `Dock.qml`, currently a
single `ncde.glow` blue that pulses on minimize). ⚠️ **Touch ONLY the 6px bead** — the round medallions are
the **Mucha app icons** (Canvas-drawn, final, loved — NEVER touch them; the dot sits *below* the icon). Make it **change COLOR by the window's state** — it is a
**passive INDICATOR, NOT clickable**:
- 🟢 **green** = window maximized
- 🟡 **yellow** = window minimized (to dock)
- 🔴 **red** = on close — a **brief flash only**, NEVER persists → settles to 🔵 **sapphire blue** = idle / no
  window. *Why (operator):* red = **danger**; a steady red dot would be alarming/nagging, so it must calm to
  blue (fits the calm, accessibility-first feel).
Confirmed not present in dev's Jun-14 `Dock.qml` NOR the tree's Jun-25 one (diff = only the `magSpread`
magnification calc differs; the dot is the identical single blue bead in both). So it's a fresh build, not a
recovery. **Depends on the WM exposing per-window MAXIMIZED state** (it exposes min today, not max) — the same
"WM owns window-state" foundation as open-maximized + the emerald button. Earlier "clickable trio" reading was
wrong (corrected by operator).

## ✅ FIXED — window move (2026-06-26)
**Root cause:** the pointer feed was dead. `pollPointer` used raw `xcb_query_pointer` on **Qt's shared xcb
connection** — Qt's event reader owns that connection, so the reply came back silent → `windowMgr.mouseX`
never updated → the titlebar drag computed a **zero delta** → no move. **Fix:** poll **`QCursor::pos()`**
instead (what the original ncde-wm used — recovery doc item 5; operator's "we had a mouseover problem" hint).
**Verified:** operator dragged Verda on :2 and she moved `+76+36 → +62+193` (frame + container in lockstep,
client nested) — a real ~157px move ⟹ the delta was non-zero ⟹ the QCursor feed is live. Debug instrumentation
removed; rebuilds clean.
**Open polish (smoothness):** the Tiffany glass currently follows the container via the QML model binding
(~1 frame behind) → the frame visibly trails the content on a fast drag. The original moved the glass in C++
in lockstep. Optional: in `moveWindow`/`resizeWindow`, also `xcb_configure_window` the glass synchronously so
frame+content move together (smoother). X11 reparent + picom still cap true buttery-smooth.

## SEPARATE QML workstream — MariposaGlow (panel + dock "butterfly glow")
(operator, 2026-06-26 — not host C++; a `/usr/share/ncde` QML task, do it right)
The dormant **standalone `MotifGlow.qml`** was KEPT to become **`MariposaGlow`** ("butterfly glow") =
**pill-shaped outlines on the panels + dock** (`radius = height/2`), using the **same subtle candle/lamp
math** as `MotifFrame.qml`'s `lampPulse`. Task = rename/repurpose `MotifGlow.qml` → `MariposaGlow.qml` and
wire it onto the panel + dock surfaces. **Epileptic-safety: keep it ALMOST imperceptible — NEVER amplify
the motion** (memory `ncde-motif-glow-candle-flicker`). Colours/glow only; do NOT touch Salon MPRIS/scrubber
(`ncde-never-touch-animations-or-mpris`). Live QML edit → dev test → mirror to tree.

## Portal → Le Pivot (verified session-agnostic; proof = logout-pick test)
`ncde-portal` is **not** hardcoded to ncde-wm. Its `SessionManager` scans `/usr/share/xsessions`; the greeter
shows a tappable **session pill** (`onTapped` cycles `sessions[]`); `setSessionCommand` execs the **selected**
`.desktop`'s `Exec`. The entry **`ncde-test.desktop` ("NCDE (test host)") → `ncde-x11-session-test` →
`lelan-host`** already exists; `ncde.desktop` → `ncde-wm` stays the fallback. To test Le Pivot: at the
greeter, **tap the pill to "NCDE (test host)"** (log → `~/ncde-host-test.log`). No `--autologin` drop-in on
dev, so the picker shows. *Not yet proven by a live login — confirm on the next logout test.*

## Verify discipline (every item)
Read the file first → audit the change → **build + Xephyr-test at real res** (`~/test-lelan-host.sh 1920x1200`
+ `DISPLAY=:2 xterm`) → verify method against the binary → operator integrates via sudo →
logout-test. Back up the irreplaceable engine binary OUTSIDE the tree before any risky dev test.
