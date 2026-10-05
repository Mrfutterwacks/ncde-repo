# GliaTalk Fix Plan — make the house apps publish their menus (original-plan item)

## Diagnosis (live-verified 2026-07-11 night)
GliaTalk = no-D-Bus global menu over X11 window properties: an app publishes its menus as UTF-8 JSON in
`_NCDE_MENUS` on its top-level window; receives `_NCDE_MENU_INVOKE` ClientMessage (format 32, data32[0]=id).
LaPivot (WM) READS `_NCDE_MENUS` fine; `GliaSystemMenus` (system menus) is intact.

**Broken:** verve-text, abacus, magpie-talker, ncde-command publish NOTHING (`_NCDE_MENUS` strings=0).
**Working reference:** orchidée (publishes; has a `GliaTalkPublisher` C++ class exposed to its QML as the
`gliaTalk` **context property** via `QQmlContext::setContextProperty`).
`OrchideeApp.qml` wiring (the pattern to replicate):
```
gliaTalk.attach(app)
gliaTalk.menusJson = JSON.stringify([ {title:"File", items:[{label:"New", id:101}, ...]}, ... ])
Connections { target: gliaTalk; function onInvoked(id) { app.handleGliaMenu(id) } }
```
Root cause: the 4 apps' C++ never creates/exposes `gliaTalk`, so `typeof gliaTalk === "undefined"` in their QML.
All 4 app QMLs live ON DISK at `/usr/share/ncde/` (VerveText.qml, Abacus.qml, NCDECommand.qml; magpie is Flutter).

## Fix (NO app recompile — shared QML plugin + on-disk QML edits)
1. **Build a shared QML plugin `NCDE.Glia`** exposing `GliaTalkPublisher` as an INSTANTIABLE QML type
   (`qmlRegisterType`), so any app's QML can `import NCDE.Glia` and create one — no per-app C++/context
   property needed. Reconstruct from the FULLY-DOCUMENTED protocol (gliatalk.md) — small, well-specified:
   - `QObject` + `QAbstractNativeEventFilter`. `Q_INVOKABLE attach(QWindow*)` → stores the window, installs
     the native event filter, sets `_NCDE_MENUS` via `xcb_change_property`/XChangeProperty(UTF8_STRING).
   - `Q_PROPERTY(QString menusJson)` — on set, re-writes `_NCDE_MENUS` on the attached window.
   - `nativeEventFilter`: on `_NCDE_MENU_INVOKE` ClientMessage → `emit invoked(data32[0])`.
   - Toolchain present (g++ 16.1.1, Qt6 6.11.1). Verify it interops with the live WM reader (orchidée proves the WM side).
2. **Edit each broken app's on-disk QML** (VerveText.qml, Abacus.qml, NCDECommand.qml): `import NCDE.Glia`,
   instantiate `GliaTalkPublisher { id: gliaTalk }`, `Component.onCompleted: { gliaTalk.attach(app);
   gliaTalk.menusJson = JSON.stringify([...the app's REAL menus...]) }`, and `onInvoked` → the app's existing
   menu handlers. Recover each app's real menu set from its QML/binary (don't invent menu items).
3. **magpie-talker** (Flutter, no on-disk QML) + **binnie** (no DWARF, no disk QML found) — assess separately;
   likely need their own path. orchidée already works — leave it.

## Verify (anti-regression: live is truth)
Per app after edit: launch it, `xprop -name <win> _NCDE_MENUS` shows the JSON; the menu appears in the
global bar; clicking an item fires the right action (invoked(id) → handler). orchidée must still work.

## Deploy
New plugin .so + qmldir into a QML import path; QML edits via the patch script (backup-first) → live + ISO.
This is a GliaTalk COMPLETION (original-plan half-measure closed), no app binary changes.

## Status: PLUGIN BUILT + VERIFIED (2026-07-12)
- `~/ncde-wm-rebuild/glia-plugin/` — GliaTalkPublisher.{h,cpp} + plugin.cpp + qmldir, built by hand
  (no cmake on box; classic QQmlExtensionPlugin, moc+g++). Module `NCDE.Glia 1.0`, plugin `libncdeglia.so`.
  VERIFIED: offscreen `import NCDE.Glia 1.0; GliaTalkPublisher{}` → exit 0; negative control (bogus module)
  → exit 2. xcb protocol (`_NCDE_MENUS` UTF8 property + `_NCDE_MENU_INVOKE` ClientMessage) matches live atoms.
- REMAINING (next session): (1) recover each app's REAL menu set from VerveText.qml/Abacus.qml/NCDECommand.qml;
  (2) add `import NCDE.Glia 1.0` + `GliaTalkPublisher{ id:glia }` + `Component.onCompleted{ glia.attach(app);
  glia.menusJson=JSON.stringify([...]) }` + `Connections{ target:glia; onInvoked:(id)=>... }` to each;
  (3) stage plugin (.so+qmldir into a QML import path, e.g. /usr/lib/qt6/qml/NCDE/Glia/) + QML edits into the
  patch script (backup-first); (4) LIVE-VERIFY per app: `xprop _NCDE_MENUS` shows JSON, menu appears in global
  bar, click fires action; orchidée still works. magpie(Flutter)/binnie assessed separately.
