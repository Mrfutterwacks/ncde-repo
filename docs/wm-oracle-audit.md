# wm-oracle-audit.md — Host `NCDEWindowManager` vs the recovered oracle (desktop/window behaviors)

**Created 2026-06-28 (session 19).** Task (operator): *"audit the WM against the oracle while preserving the
NCDEEngine separation from wifi etc. — something is missing in the desktop behaviors: the middle Motif-frame
button does not minimize to a smaller window and the cursor disappears."*

**Sources**

> **⚠️ PATH CORRECTION (2026-07-17):** every `~/ncde-staging/...` path below is gone — the dev machine
> that hosted it is gone, confirmed absent on this machine and the USB backup. Read the paths below as
> where these things lived on 2026-06-28, not current locations. Current reality: oracle-recovery work
> now lives in `~/ncde-wm-rebuild/` (Ghidra-decompiled from the live `/usr/local/bin/LaPivot` binary —
> partial, see `docs/lapivot-rebuild.md`); there is no separate HOST tree anymore, the live system is it;
> shipped QML is live at `/usr/share/ncde/` (never lost — this doc's own installed-path note below was
> already right).

- **ORACLE** = `~/ncde-staging/ncde-wm-rebuild/src/decompiled/NCDEWindowManager.c` (145 KB decompiled,
  2026-06-28 location — gone now, see banner above; current equivalent work is in `~/ncde-wm-rebuild/`).
- **HOST (active)** = `~/ncde-staging/compass7/lelan/NCDEWindowManager.h` (the live-dev WM; cursor-stack fix
  lineage; as of this doc's creation (session 19, 2026-06-28) built to the since-retired `/usr/local/bin/ncde-test`
  path — that binary/tree is retired 2026-06-30; the same source now builds/ships as **LaPivot**. NOT the
  stale `LaPivot/src` 34 KB copy. **2026-07-17: this whole host tree is gone too — the live-running
  `/usr/local/bin/LaPivot` binary is now the only copy.**).
- **QML** = staged then at `~/ncde-staging/LaPivot/usr/share/ncde/` (`MotifFrame.qml`, `main.qml`) —
  that staging path is gone now (2026-07-17); the real, never-lost live copy is `/usr/share/ncde`.

---

## 1. The reported bug — root cause (verified)

The emerald (middle) button = **maximize↔restore toggle**, logic lives in `MotifFrame.qml` (~432), driven by
the local QML bool `frame.isMaximized`.

Windows **open maximized** by operator intent, done in the WM C++:
- `NCDEWindowManager.h:603` — opens at near-fullscreen geometry (`e.w=m_screenW-24, e.h=m_screenH-58`).
- `NCDEWindowManager.h:721` — `setMaximized(client,true)` → model role `maximized=true` + `_NET_WM_STATE`.
- Author comment `:599-601`: *"…marks the entry maximized … so the emerald button opens as 'restore' + the
  dock dot reads green; restore then goes to MotifFrame's small default square (operator's intent)."*

**The gap:** `main.qml` bound `isMinimized` and `isTiled` from the model but **never `isMaximized`** (both the
staging copy AND the installed `/usr/share/ncde/main.qml`). So `frame.isMaximized` stayed at its QML default
`false` regardless of the real state → the button rendered "□" and the **first click took the maximize branch**
(re-grew the already-full window) instead of the restore branch → no shrink. The grow also covered the Kith
cursor overlay → the cursor "disappeared" (trap).

The model role exists and is correct (`NCDEWindowManager.h:165` exposes `MaximizedRole → "maximized"`), so the
fix is purely the missing binding.

---

## 2. WM C++ vs oracle — is anything actually missing? (No.)

Oracle invokable window verbs (from the `qt_static_metacall` table in `NCDEWindowManager.c` lines ~20-210):
`screenWidth/Height`, `register/destroyFrameWindow`, `register/destroyGlassWindow`,
`register/destroyMenuGlassWindow`, `ncdeStackBelow`, `unminimizeWindow`, **`syncX11`**, `setTiled`,
`moveTiledWindow`, `resizeWindow`, `moveWindow`, `activateWindow`, `minimizeWindow`, `closeWindow`,
`setSnapZone`, `winIdForName`/`isActiveForName`/`isMinimizedForName`/`hasWindowForName`, `screenConfigChanged`,
`windowRemoved`/`windowAdded`/`countChanged`/`windowStateChanged`, `mouseX`/`mouseY`/`snapZone`/`activeIndex`.

| Item | Oracle | Host | Verdict |
|---|---|---|---|
| Core verbs (move/resize/activate/min/unmin/close) | ✅ | ✅ | parity |
| `setMaximized` / `isMaximized` / maximize state | **absent** | present (invention) | **KEEP** — host upgrade backing operator "open full screen"; oracle did maximize purely in QML |
| `setTiled` | real body | **no-op stub** | **CORRECT** — operator confirmed tiling abandoned, floating kept |
| `moveTiledWindow` | ✅ | ✅ (used only by dormant TilingManager.qml) | fine |
| `setSnapZone`/`snapZone` | ✅ | ✅ | parity (edge-snap floating) |
| **`syncX11(win,x,y,w,h)`** | ✅ (atomic `xcb_configure_window`, mask 0xf, +flush) | **MISSING** | shipped QML does NOT call it → harmless today. Add only if a future QML path needs one-shot geometry. |

**Conclusion:** the WM is not missing desktop-behavior code. The bug was a one-line QML wiring omission. The
host's maximize layer is an intentional, kept upgrade over the oracle.

**NCDEEngine separation preserved:** this audit touched only the WM/QML window path; engine remains colors-only
(no wifi/system data), per the architecture rule.

---

## 3. Fix (staged, qmllint exit=0, NOT yet installed — see SESSION_HANDOFF §19)

**SUPERSEDED (2026-06-30 night) — this fix was installed and then explicitly REVERTED at session 28,
not just left pending.** Current `main.qml:271-274` has the operator's own reversal comment in place:
"isMaximized is OWNED LOCALLY by MotifFrame's… buttons. The real ncde-wm never sets the `maximized`
model role (setMaximized was removed)." Do not re-apply item 1 below — it was tried and rejected.

1. ~~`main.qml` — add (between `isMinimized` and `isTiled`): `isMaximized: model.maximized === true`.~~
   REVERTED session 28 — see correction above.
2. `MotifFrame.qml` — emerald handler toggles via `windowMgr.setMaximized(frame.winId, false/true)` instead of
   local `frame.isMaximized = …` (keeps the binding live; `_NET_WM_STATE` + dock dot stay in sync).

Backups: `*.prebak-maxrestore` in `LaPivot/usr/share/ncde/`. Apply = `sudo install` both → `/usr/share/ncde`
then relog (qmlcache).

---

## 4. Still open (next session — untested, do not claim fixed)

1. **Cursor behind frame on the maximize-GROW click.** Session-18 fixed re-*activate* re-raise (unconditional
   `activeIndexChanged`), but the emerald handler activates BEFORE it grows the glass, so the grown frame ends
   over the cursor. Planned: re-raise after resize — add `windowMgr.activateWindow(frame.winId)` as the LAST
   line of the emerald `onClicked`. Verify before shipping.
2. **"Weird circle behind the mouse" (NEW, unexplained).** Overlay `cursorName` is hardcoded `"arrow"`;
   `drawArrow` draws no large circle (only `drawWait`'s rose-window does, and it's animated). Investigate:
   hardware-cursor leak (XFixes), non-transparent overlay bg, or oversized glow. ⚠ epilepsy risk if it's the
   animated wait spinner.

## 5. Live un-trap (no relog)
Agent shell can reach `DISPLAY=:0`. Cursor overlay = the 32×32 window class `ncde-test` (as of session 19 —
now `LaPivot` since the rename/retirement, verify current class with `xprop` before relying on this). Raise it:
`DISPLAY=:0 xdotool windowraise <id>`. Operator alt: mapping any new window re-raises it
(`main.qml onAnyWindowMapped`).
