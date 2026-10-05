# MotifFrame anchor error + game-window frame skip (subagent, 2026-07-11 night)

Companion to `wm-mainqml-games.md` (main agent's notes on the same games work).
This file adds: the MotifFrame.qml:608 fix, the role-constant ground truth, and a
**behavioral** offscreen verification (frame visibility + tile exclusion actually
observed, not just CREATE OK). All work staged only — live system untouched
(live mtimes: MotifFrame.qml Jul 10 23:35, main.qml Jul 6 12:00, TilingManager.qml Jul 6 18:45).

Staged files (mirror of absolute paths):
- `src/usr/share/ncde/MotifFrame.qml`
- `src/usr/share/ncde/main.qml`          (game skip — see wm-mainqml-games.md)
- `src/usr/share/ncde/TilingManager.qml` (game tile exclusion, role corrected to 0x107)

---

## Defect 1 — `MotifFrame.qml:608:13 QML GliaFrameMenu: Cannot anchor to an item that isn't a parent or sibling`

**Cause (confirmed):** the 2026-07-10 framemenu patch (whole diff vs
`MotifFrame.qml.prebak-20260710-framemenu` is exactly this block) placed
`GliaFrameMenu` as a **child of `glassBand`** (id at :543) while anchoring it to
`leftOrnament` (:406) — a sibling of glassBand, not of the menu. Illegal anchor,
warned once per frame instantiation (journal spam, ~23/boot).

**Fix:** move the block up one level so it is a child of `titlebar`, where
`leftOrnament` IS a sibling. The anchors as written become legal; on-screen
position is pixel-identical (`glassBand.left == leftOrnament.right + 8`, and
glassBand/titlebar share the same verticalCenter). Deliberate side benefit: the
menu's dropdown is no longer inside glassBand's `clip: true` + `layer.enabled`
band — inside glassBand the 22px-tall clip made the dropdown invisible, i.e. the
July-10 feature could never actually show its menu. Anchor fix alone (re-pointing
to `parent.left`) would have silenced the warning but left the feature broken.

### Diff hunk (`/usr/share/ncde/MotifFrame.qml`)

```diff
@@ -604,16 +604,6 @@
                 }
             }
 
-            // -- GliaTalk locally-integrated menu (Unity LIM) -------------------
-            GliaFrameMenu {
-                anchors.left: leftOrnament.right
-                anchors.leftMargin: 8
-                anchors.verticalCenter: parent.verticalCenter
-                z: 60
-                menusJson: (typeof windowMgr !== "undefined" && windowMgr.activeAppMenus !== undefined) ? windowMgr.activeAppMenus : ""
-                active: frame.isFocused && !frame.maximized
-                onInvoked: function(id) { if (typeof windowMgr !== "undefined") windowMgr.invokeAppMenu(id) }
-            }
             // title text — shadow + main
             Text {
@@ -642,6 +632,25 @@
             }
         }
 
+        // -- GliaTalk locally-integrated menu (Unity LIM) -------------------
+        // 2026-07-11 fix: this block lived INSIDE glassBand, but anchored to
+        // leftOrnament — a sibling of glassBand, not of the menu — which is an
+        // illegal QML anchor ("Cannot anchor to an item that isn't a parent or
+        // sibling", journal-spammed since the 07-10 framemenu patch). Moved up
+        // one level into `titlebar`, where leftOrnament IS a sibling: the
+        // anchors as written become legal and the on-screen position is
+        // unchanged (glassBand.left == leftOrnament.right + 8 anyway). Bonus:
+        // the dropdown is no longer clipped by glassBand's clip:true band.
+        GliaFrameMenu {
+            anchors.left: leftOrnament.right
+            anchors.leftMargin: 8
+            anchors.verticalCenter: parent.verticalCenter
+            z: 60
+            menusJson: (typeof windowMgr !== "undefined" && windowMgr.activeAppMenus !== undefined) ? windowMgr.activeAppMenus : ""
+            active: frame.isFocused && !frame.maximized
+            onInvoked: function(id) { if (typeof windowMgr !== "undefined") windowMgr.invokeAppMenu(id) }
+        }
+
         // -- drag handler: move window from titlebar ------------------------
```

---

## Defect 2 — game windows framed/ringed/tiled (audit H2/H3)

Staged in `main.qml` (isGame skip: frame overlay never shown → never
scene-graph-initialized → `registerFrameWindowQml` never called → C++ never
shapes an input ring; nothing overlays the client) and `TilingManager.qml`
(games never grid-tiled). Full hunks + rationale in `wm-mainqml-games.md`; the
diffs there and here are the same staged files. Both hunks were re-verified in
this session against the live files (diff shown in session, only intended hunks).

**Role-constant ground truth** (dumped `NCDEWindowManager::roleNames()`,
objdump at 0x77cfc + .rodata strings at 0x19c43e):

```
0x101 winId   0x102 x     0x103 y      0x104 w        0x105 h
0x106 name    0x107 appId 0x108 minimized  0x109 maximized
0x10A title   0x10B tiled
```

- The first draft of the TilingManager guard used `0x103` "because Hud.qml
  reads appId there" — **0x103 is the y-coordinate role**; the guard silently
  never matched (proven below by counterfactual run). Corrected to **0x107**.
- Side finding: live `Hud.qml:77-78` reads title/appId via `Qt.UserRole+2/+3`
  (= x/y) — broken the same way, but Hud.qml has no consumers (dead file).
  Not patched here.

### What QML can and cannot see (task-3 answer, verified)

The model exposes ONLY the roles above — there is **no** `_MOTIF_WM_HINTS` /
decorations, no fullscreen, no override-redirect, no window-type role, and no
such property on `windowMgr` (binary interns no `_NET_WM_STATE_FULLSCREEN` atom
at all, per audit). So "honor _MOTIF_WM_HINTS decorations=0 / fullscreen"
**cannot be implemented literally in QML**; the only live-fixable proxy is the
`appId` (WM_CLASS) match on `steam` / `steam_app_*` (+ `steamwebhelper`,
`gamescope`), which is exactly what the audit's H2 fix prescribes. Reading the
real MOTIF hints in manage() is Ghidra-track (listed below).

Also NOT QML-fixable: the client's own placement at (-17,-21) — that is C++
`manage()`'s fixedSize branch (audit H3). The QML skip neutralizes its damage
(no misplaced ring/chrome on top of the client) but does not move the client.

---

## Verification (offscreen instantiation harness — qmllint is NOT a gate on this project)

Harness: `scratchpad/verify/harness.cpp` + `stubs.h` (this session's scratchpad).
Real `QQmlEngine`/`QQmlComponent`, `QT_QPA_PLATFORM=offscreen`, stub context
properties matching the names the binary registers (`windowMgr settings launcher
notifications animPolicy ncde theme window audio` — from `strings` of LaPivot),
with `windowMgr` a real QAbstractListModel using the EXACT role numbers above and
5 rows: ncde-terminal (maximized), steam_app_1222670, steam @(-17,-21),
orchidee (tiled), steam_app_413150 (tiled).

Build: `/usr/lib/qt6/moc stubs.h -o moc_stubs.cpp && g++ -std=c++17 harness.cpp
moc_stubs.cpp -o harness $(pkg-config --cflags --libs Qt6Quick Qt6Qml Qt6Gui Qt6Core)`

### 1. Baseline — LIVE MotifFrame.qml reproduces the journal error
```
$ ./harness root-live/MotifFrame.qml frame
[W] file://.../root-live/MotifFrame.qml:608:13: QML GliaFrameMenu: Cannot anchor to an item that isn't a parent or sibling.
SUMMARY: anchor_errors=2 target_file_warnings=2 total_messages=2   (counted 2x: handler + engine.warnings)
RESULT: HAS_TARGET_WARNINGS
```

### 2. STAGED MotifFrame.qml — clean instantiation
```
$ ./harness root-staged/MotifFrame.qml frame
-- root object created: MotifFrame_QMLTYPE_6 --
SUMMARY: anchor_errors=0 target_file_warnings=0 total_messages=0
RESULT: CLEAN
```

### 3. FULL main.qml instantiation, LIVE tree (baseline behavior)
```
$ ./harness root-live/main.qml main
FRAME appId=steam_app_413150  winId=5005 frameWinVisible=1 motifItemVisible=1 geom=376,206 688x562
FRAME appId=orchidee          winId=4004 frameWinVisible=1 motifItemVisible=1 geom=276,156 688x562
FRAME appId=steam             winId=3003 frameWinVisible=1 motifItemVisible=1 geom=-41,-65 1328x882
FRAME appId=steam_app_1222670 winId=2002 frameWinVisible=1 motifItemVisible=1 geom=-12,0 1944x1076
FRAME appId=ncde-terminal     winId=1001 frameWinVisible=1 motifItemVisible=1 geom=76,56 848x642
TILEORDER after updateLayout: [4004,5005]
SUMMARY: anchor_errors=10 target_file_warnings=10 total_messages=3712   (5 frames x 1 anchor error, counted 2x)
RESULT: HAS_TARGET_WARNINGS
```
(Steam's overlay at -41,-65 = model(-17,-21) - (24,44): the exact misplaced ring
from the audit. Tiled game 5005 enters the grid.)

### 4. FULL main.qml instantiation, STAGED tree — behavioral proof
```
$ ./harness root-staged/main.qml main
FRAME appId=steam_app_413150  winId=5005 frameWinVisible=0 motifItemVisible=0 geom=376,206 688x562
FRAME appId=orchidee          winId=4004 frameWinVisible=1 motifItemVisible=1 geom=276,156 688x562
FRAME appId=steam             winId=3003 frameWinVisible=0 motifItemVisible=0 geom=-41,-65 1328x882
FRAME appId=steam_app_1222670 winId=2002 frameWinVisible=0 motifItemVisible=0 geom=-12,0 1944x1076
FRAME appId=ncde-terminal     winId=1001 frameWinVisible=1 motifItemVisible=1 geom=76,56 848x642
TILEORDER after updateLayout: [4004]
SUMMARY: anchor_errors=0 target_file_warnings=0 total_messages=3696
RESULT: CLEAN
```
Every game frame window unmapped + Motif item hidden; normal windows unchanged;
tiled game excluded from the grid; zero warnings from MotifFrame.qml /
GliaFrameMenu.qml / main.qml / TilingManager.qml across a 3696-message
full-shell load (remaining messages are stub artifacts from unrelated
components — Dock/TopPanel/etc. probing stubbed context props).

### 5. Counterfactual — the 0x103→0x107 correction was load-bearing
```
$ sed 's/0x107/0x103/' on TilingManager.qml, rerun:
TILEORDER after updateLayout: [4004,5005]    <- tiled game NOT excluded with 0x103
RESULT: CLEAN                                 <- and no warning: silent no-op
```

### What was NOT verified (honest limits)
- `onSceneGraphInitialized` never fires on the offscreen platform, so
  `registerFrameWindowQml`/`destroyFrameWindow` paths executed 0 times in the
  harness (live or staged). The "games never register" claim rests on code
  logic: registration only happens in `onSceneGraphInitialized`, and a window
  that is never `show()`n never initializes a scene graph. Verify live.
- Whether the C++ WM tolerates a managed client with no registered frame —
  low risk (frames are non-reparenting overlays; "ncde settings" already runs
  with an invisible MotifFrame), but confirm on the live session.
- Real Steam/Proton click behavior — needs the game running post-deploy.
- GliaFrameMenu dropdown appearance with a real `_NCDE_MENUS` publisher — the
  harness had `activeAppMenus=""` (menu hidden, as on most apps).

---

## Deploy (operator runs; NOT done by agents)

```
sudo cp /usr/share/ncde/MotifFrame.qml    /usr/share/ncde/MotifFrame.qml.prebak-20260711-fullpatch
sudo cp /usr/share/ncde/main.qml          /usr/share/ncde/main.qml.prebak-20260711-fullpatch
sudo cp /usr/share/ncde/TilingManager.qml /usr/share/ncde/TilingManager.qml.prebak-20260711-fullpatch
sudo cp ~/my-project/files/full-patch-20260711/src/usr/share/ncde/{MotifFrame.qml,main.qml,TilingManager.qml} /usr/share/ncde/
rm -rf ~/.cache/qmlcache ~/.cache/LaPivot/qmlcache 2>/dev/null   # clear stale .qmlc
# then relogin (LaPivot loads QML at session start)
```
Post-deploy checks: journal must show ZERO "Cannot anchor" from MotifFrame.qml;
open Steam → no bronze frame, no input ring, window at its own coordinates,
clicks land on edge UI; normal apps still framed; unmax→tile still works and a
tiled game never appears in the grid.

## Ghidra-track leftovers (out of QML reach; matches wm-mainqml-games.md)
- Real `_MOTIF_WM_HINTS` / `_NET_WM_STATE_FULLSCREEN` / override-redirect
  handling inside C++ `manage()` (0x7c542) — the proper fix for decorations=0.
- The fixedSize-branch client placement (Steam at -17,-21) in `manage()`
  0x7c7a1-0x7c841 — QML skip neutralizes the ring damage but cannot move the client.
- Hud.qml role misuse (dead file) — fix only if Hud is ever revived.
