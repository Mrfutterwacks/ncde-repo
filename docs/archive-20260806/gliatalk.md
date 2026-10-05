# GliaTalk — NCDE's ToolTalk, Modern (the unified-host message layer)

**Operator identity statement (2026-07-07, verbatim, primary-source spec):** *"Glia already hides
the menu on N click, so that is Amiga DNA. The Glia talk is CDE DNA, but the in-house global menu
modeled after tool talks is OSX-like. That is what this is—not done in Linux before. D-Bus would
never have given NCDE the control the way Glia talk does. Think how Lelan controls Zen, so Glia
talk controls all apps, etc., on Lapivot, the WM."* And the organizing term: **NCDE is a UNIFIED
HOST** — one organism, one chain of command: Zen(kernel)←Lelan · hardware←Sentinel→Lelan ·
**apps←GliaTalk→LaPivot**. Never a federation of components on a peer bus. **No dbus, ever.**

## The mechanism trio (operator: "Tool talk messaging service. file based actions.. server side x11 properties")

| CDE original | NCDE modern (v1, shipped session 81) |
|---|---|
| ToolTalk session = the X display (`tt_X_session`) | the X display IS the session; **LaPivot (the WM) is the session manager** — no ttsession daemon |
| ptype/pattern registration in ttsession | **`_NCDE_MENUS`** — an app publishes its real menus as UTF-8 JSON on its own top-level window (Amiga menu-strip registration, reborn) |
| `TT_REQUEST` + named ops, delivered via `tt_fd()`/`XtAppAddInput` | **`_NCDE_MENU_INVOKE`** ClientMessage (format 32, `data32[0]` = item id) — arrives in the app's normal Qt xcb event loop via a native event filter |
| file-based actions (`.dt`) | Glia's existing gliaSystem `.desktop`/action reads (unchanged in v1) |

Reference: the operator supplied real CDE ToolTalk source (ttinit.c / tt_util.c, 1996 OSF/HP/DEC/
IBM/Novell) — its patterns are credited inline in `GliaTalk.h`.

## The pieces (all in the production tree)

- **`compass7/lelan/GliaTalk.h`** — ONE shared header (NCDEEngine.h pattern):
  `GliaTalkProto::{readMenus, writeMenus, sendInvoke, internAtom}` + `GliaTalkPublisher`
  (QObject + QAbstractNativeEventFilter; `attach(window)`, `menusJson`, signal `invoked(int)`).
- **WM side** (`NCDEWindowManager.h`): reads `_NCDE_MENUS` at manage-time + on PropertyNotify
  (PROPERTY_CHANGE was already selected on every client); `Q_PROPERTY activeAppMenus` (the
  FOCUSED window's JSON, "" when none); `Q_INVOKABLE invokeAppMenu(id)`;
  `activeAppMenusChanged` fires on focus change and re-publish.
- **Shell merge** (`GliaGlobalMenus.qml` + `TopPanel.qml`): when the focused app publishes,
  its menus **replace the static File/Edit/View relay trio** in Glia's bar; items carry
  `actionId "gliatalk:<id>"` → `route()` → `windowMgr.invokeAppMenu`. Apps that publish
  nothing (all foreign apps) keep the relay trio — nothing is lost.
- **Reference publisher: Orchidée** (`main.cpp` context property `gliaTalk`;
  `OrchideeApp.qml` `publishGliaMenus()` + `handleGliaMenu(id)`): File (New Folder 101,
  Duplicate 102, Rename 105, Toss 103, Close 104), Edit (Undo 120, Cut 121, Copy 122,
  Paste 123), View (Column 110, Grid 111, List 112, Show Hidden 113, The Bin 114) — every
  id lands on a real verb.

**Menu JSON shape:** `[{ "title": "File", "items": [ { "label": "New Folder", "id": 101,
"shortcut": "Ctrl+Shift+N" }, { "separator": true }, ... ] }, ...]` — ids are ints > 0, unique
per window; re-publish replaces wholesale; empty string clears (property deleted).

**PROOF (session 81):** `compass7/lelan/test_gliatalk.cpp` (scaffolding, NOT in CMakeLists) on
the real display — 5/5 PASS: publish→read byte-exact · wholesale replace · invoke round-trip
through a real Qt event loop · clear deletes · unpublished window reads "" (relay fallback).

## Adopting GliaTalk in another house app (the dozen lines)

1. `#include "../lelan/GliaTalk.h"`, add `PkgConfig::XCB` to the app's CMake, instantiate
   `GliaTalkPublisher` and set it as context property `gliaTalk`.
2. In the root Window: `Component.onCompleted: { gliaTalk.attach(app); gliaTalk.menusJson =
   JSON.stringify([...]) }` + `Connections { target: gliaTalk; function onInvoked(id) {...} }`.
3. Publish only REAL verbs. Re-publish whenever the verb set changes (it replaces wholesale).

## Menu identities (operator, fixed)

File fronts **Orchidée** · Edit fronts **Verve** · Places open in **Orchidée** · Save/Save As
stay in the static File menu as focused-app relays. Zoom relays Ctrl+= / Ctrl+− / Ctrl+0 —
"browser text and document text genuinely grow." The Leap Frog Ledger is the shell's own pond,
never a menu launcher entry.

## v2 growth path (designed, not yet built)

- **Named-op requests** (`Get_Environment` parity): `_NCDE_REQUEST`/`_NCDE_REPLY` property pair
  on the requester's window — same carrier, typed args, replies.
- **"Compose yourself"**: GliaTalk asks an app to save state before Sentinel freezes/tiers it —
  the resource governor and the message layer acting as one machine.
- **GTK3 capture without dbus**: an `ncde-gtk-module` (loaded via the `gtk-modules` settings.ini
  key NCDE now controls) that reads the app's GtkMenuBar in-process and publishes `_NCDE_MENUS`
  on its own window. GTK4 dropped modules → GTK4 stays relay.
- **File-based actions v2**: CDE-`.dt`-style verb files (Open With / Convert / Print per type)
  resolved through the gliaSystem registry.
