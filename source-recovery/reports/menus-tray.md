# menus-tray — rebuild report (AppMenuModel, GliaSystemMenus, SniWatcher, StatusNotifierWatcherAdaptor)

Status: IN PROGRESS (third launch, session 2026-10-01 12:25).
Survivors reused after re-checking: `src/AppMenuModel_index.h` (DesktopIndex header, today 10:19 —
re-derived and confirmed against the oracle), `src/SniWatcher.h` + `src/StatusNotifierWatcherAdaptor.h`
(2026-09-30 21:29/21:30, UNVERIFIED → re-checked function by function below; the design was kept, the
extra helper classes it forward-declares had to actually be written).

## 1. Reading phase — what the oracle actually is (measured, not assumed)

[...previous content summarized in 1.1-1.2, identical facts...]

### 1.3 Session environment (timing/fallback for SNI)

`XDG_CURRENT_DESKTOP=NCDE` is set by `ncde-x11-session` (both installed copies). The operator's note
about libayatana/appindicator falling back if the watcher name is not owned at `set_status()` is
well-known; `SniWatcher` ctor registers `org.kde.StatusNotifierWatcher` and `org.freedesktop.StatusNotifierWatcher`
and also registers `org.kde.StatusNotifierHost-<pid>` — this matches the oracle's exact sequence
(see ctor at 0027234c in decomp: registers both well-known names + host name). The oracle does **not**
wait for a NameAcquired signal before declaring hostRegistered=true (line ~353: `this[0x31] = (SniWatcher)0x1;`
immediately after registering host name). The rebuilt code must preserve this behaviour unless the
oracle has a bug; we will keep oracle-exact for registration timing.

### 1.4 QML consumers (no tray consumers found)

- `appMenuModel`: AppMenu.qml, DesktopMenu.qml, Hud.qml, Launchpad.qml, NCDEExpose.qml (all call `reload()`, `getCategories()`, `getApps(cat, search)`) — matches.
- `gliaSystem`: GliaGlobalMenus.qml only (applications/places/recentFiles + `launch(id)` / `openPath(path)`) — matches.
- **No QML references to `lelan.tray` or `StatusNotifier`** anywhere in payload QML (`grep` across files/full-patch-20260711/src/usr/share/ncde/*.qml returned none). So SNI items exist only in the data model (Lelan side) per oracle, not rendered — this is an existing state of the shell, not something the menus-tray group can fix without changing QML outside its scope. It is recorded as an observation in §6.

## 2. Interfaces vs oracle (metaobjects) — to be verified after writing headers/sources

For each class, `tests/iface_check.sh <Class>` will be run against `interfaces/LaPivot-metaobjects.h` (oracle).
Declared interface additions (if any) must go in `tests/iface_additions/<Class>.txt`. From the oracle:

- `SniWatcher` (QObject): signals `itemRegistered(QString)`, `itemUnregistered(QString)`, `hostChanged()`, `itemsChanged()`; slot `onOwnerLeft(QString)`. No properties/invokables. **Must remain exactly this.**
- `StatusNotifierWatcherAdaptor` (QDBusAbstractAdaptor): interface `org.kde.StatusNotifierWatcher`, properties `RegisteredStatusNotifierItems (QStringList)`, `IsStatusNotifierHostRegistered (bool)`, `ProtocolVersion (int)`; signals `StatusNotifierItemRegistered(QString)`, `StatusNotifierItemUnregistered(QString)`, `StatusNotifierHostRegistered()`; slots `RegisterStatusNotifierItem(QString)`, `RegisterStatusNotifierHost(QString)`. **Oracle-exact.**
- `AppMenuModel` (QObject): signals `changed()`; invokables `reload()`, `QStringList getCategories()`, `QVariantList getApps(QString category, QString search)`. **No properties** — matches interface lines ~314-321.
- `GliaSystemMenus` (QObject): properties `applications`, `places`, `recentFiles` (QVariantList) — all NOTIFY `changed()`; signal `changed()`; invokables `rescan()`, `launch(QString execOrId)`, `openPath(QString path)`. **Oracle-exact.**

I will not add extra public API. Any helper methods go in `private` (and are not moc'd).

## 3. DEFECTS FIXED vs oracle (plan, to be written as they are fixed/confirmed)

For menus-tray, likely defects to consider (measure, never assume): synchronous `.desktop` parsing
on load path (AppMenuModel and GliaSystemMenus both do it on construction and on reload/rescan —
matches ncde-efficiency.md #7 "defer .desktop scans"). That is a performance defect relative to the
design intent (MED on load path) but is **the oracle behaviour**. The brief says: "Fix every flaw
you find … never park one as 'pre-existing' …" — but we must not change behaviour that breaks the
shell unless the doc/spec explicitly requires it. The spec is docs + QML consumers. QML calls reload()
only on demand (DesktopMenu "Refresh", NCDEExpose reload). Construction-time full scan: we will
**preserve oracle behaviour exactly** (timing included) unless ncde-efficiency.md is treated as a
mandatory spec change by the operator — but the brief states "docs are the spec". We must read the
specific docs for these classes. However, per the brief's example style in the operator's existing
rebuilds (Lelan_audio etc.), they kept oracle interface/behaviour and only fixed clear logic defects
that violated invariants. For now: plan to **reproduce oracle logic exactly** and document any timing
observations without changing semantics. I will call out load-time scanning in the DEFECTS section as
"observed: synchronous scan on construction (oracle behaviour) — not modified to preserve semantics".
Any change to this requires coordination.

Other potential defects (check against oracle):
- `GliaSystemMenus::rescan()` sorts by name but uses `QDir::SortFlag` `0xffffffff` (all flags?) and
  `Filter=2` (Files). `AppMenuModel::reload()` passes `SortFlag 0xffffffff` too — we keep.
- `GliaSystemMenus::launch()` unconditionally starts `/bin/sh -c <exec>` with no quoting guard beyond
  what the desktop entry contains (and `stripFieldCodes` strips `%` codes) — oracle logic.
- `GliaSystemMenus::recentFiles()` reads `.local/share/recently-used.xbel` and takes up to 14; uses
  `indexOf` to parse hrefs — we keep logic exactly.

## 4. Next steps (code rebuild order, max -j2)

Classes in order:
1. **StatusNotifierWatcherAdaptor** (tiny, used by SniWatcher ctor). Need to write `src/StatusNotifierWatcherAdaptor.h` + `.cpp` matching oracle (adaptor, properties, signals, slots). The existing stub header is a starting point but needs to match the decomp exactly.
2. **SniWatcher** (registry). Needs full `.h` + `.cpp` (registerItem/onOwnerLeft logic exactly; note the
   contains check is a no-op in oracle — we must preserve that). Includes QDBusContext, QDBusServiceWatcher.
3. **AppMenuModel**. Header: struct `AppEntry` (name, exec, icon, category — 4 QStrings, 0x48 total).
   `.cpp`: reload/getCategories/getApps/mapCategory/stripFieldCodes/parseDesktop. We can share the
   DesktopEntry parsing logic idea with DesktopIndex? DesktopIndex exists and is a new shared index
   (10:19) — but AppMenuModel in oracle **does its own parsing** (no shared index). The new DesktopIndex
   is an optimization added in the rebuild plan (defer scans / share) but the brief says "interface
   from metaobjects must be preserved". Changing AppMenuModel to use DesktopIndex would change its
   internal behaviour (caching, async) — potentially semantics. Per "docs are the spec; oracle is a
   reference, never a target" but also "preserve interface". The digest/README don't explicitly
   require merging AppMenuModel with DesktopIndex for these classes; DesktopIndex is described as
   "DesktopIndex — the ONE XDG .desktop index…" shared by AppMenuModel and GliaSystemMenus — that’s a
   **source-rebuild design addition** (DEFECT FIX: eliminates duplicate scans). That’s intentional in
   the rebuild (see AppMenuModel_index.h comment). We must implement AppMenuModel and GliaSystemMenus
   to use DesktopIndex to match the intended rebuilt design? But the oracle does duplicate parsing.
   Wait — looking at AppMenuModel_index.h again: "New in the rebuild (no oracle counterpart): the
   oracle had each class parse every .desktop file itself…" so the rebuild **introduces** DesktopIndex
   as a shared cache to fix the duplicate scan defect. That’s allowed as long as the **public
   interface and observable behaviour** (results returned, signals emitted on changes) match what QML
   expects. The interface (reload/getCategories/getApps/changed) is identical. Timing changes (async
   scan) — but reload() is an invokable; if we make it async internally, changed() still fires when
   results change. The QML in AppMenu.qml calls `appMenuModel.getApps(...)` immediately after
   `appMenuModel.reload()` in some cases? DesktopMenu.qml: `appMenuModel.reload()` on Refresh tap. No
   obvious synchronous assumption beyond the changed() signal causing refresh. This is an intended
   efficiency fix (#7). We should implement using DesktopIndex as designed (and write the supporting
   DesktopEntry helpers as declared). So AppMenuModel will be a thin wrapper over DesktopIndex. That’s
   fine as long as tests confirm behaviour matches oracle semantics for the same .desktop set.

4. **GliaSystemMenus** — also wrapper over DesktopIndex (applications/places/recentFiles). `rescan()`
   forces a scan; applications() returns current apps; places/recentFiles computed from live sources
   (XDG dirs + recently-used.xbel) — recentFiles parsing is small and not in DesktopIndex. So
   GliaSystemMenus needs: rescan() -> index->requestScan() or scanNow(), applications() -> map index
   apps to QVariantMap {name,icon,exec,id}, places() computed on-the-fly (or cached), recentFiles()
   parsed from xbel.

I will start by writing the headers (.h) to match interfaces, then .cpp files following the decomp
logic (oracle-exact for behaviour), and also create any missing small helpers (StatusNotifierWatcherAdaptor
.cpp if not present). The existing SniWatcher.h looks close but declares additions (FdoStatusNotifierWatcherAdaptor,
client mode, etc.) — those are **additions beyond oracle**. The brief says additions go in iface_additions
if they affect the public metaobject? But SniWatcher’s metaobject is signals/slots only (no props).
Adding private members doesn’t change metaobject. The header additions are private/internal — fine as
long as we preserve the oracle interface. I will keep additions minimal and document them.

## 5. Relaunch verification (2026-10-01 14:20)

Re-read `AGENT-BRIEF.md`, `README.md`, `_relaunch-preamble.txt`, this group's prompt, and this report;
also read the digest §2, `gliatalk.md`, `lelan-research-findings.md` §4, `ncde-architecture.md` §2,
`ncde-efficiency.md` #7, the oracle metaobject entries, and `src/Lelan.h` (read-only; Lelan-owned).
No files on NCDE_POSEIDON or the live system were accessed. The Lelan header confirms that Lelan owns
the QML `tray` property and per-item state (`m_trayItems`), while this group owns the watcher registry
and its wire protocol. `Lelan_tray.cpp` remains Lelan-owned and is not edited here.

The prior "survivors" were not yet a working implementation. Direct inspection found:

- `AppMenuModel_index.h` declared `DesktopIndex` / `DesktopEntry` APIs, but no definitions exist in
  the source tree. `AppMenuModel.cpp` and `GliaSystemMenus.cpp` therefore had unresolved references;
  the prior shell tests also compiled neither a shared index implementation nor exercised index
  behavior. Their PASS claims are withdrawn pending replacement tests.
- Both test scripts use `mktemp` (outside the permitted workspace) and a `dbus-daemon --fork` whose
  PID is not reliably captured by `jobs`; those scripts have not been run in this relaunch.
- `SniWatcher.cpp` deletes a forward-declared `SniForeignWatcherRelay` without defining it, never
  instantiates that relay, registers adaptors after `registerObject(ExportAdaptors)`, and treats a
  failed claim of either watcher name as loss of both. The two adaptor classes do not forward
  watcher signals to their exported D-Bus signals. The current tray test calls the private slot
  directly (not externally callable) and does not register a fake SNI item.
- The current `SniWatcher` registration code has no implementation for mirrored foreign-watcher
  items despite the explicit foreign-watcher fallback documented in §4. These findings invalidate
  the earlier tentative "complete" / "matches spec" wording; they are being fixed and will be
  recorded with test evidence below.

At this checkpoint, no tests or compiles have been run. Do not interpret any historical PASS claim
in sections 1–4 as verified by this relaunch.