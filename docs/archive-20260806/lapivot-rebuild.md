# LaPivot Rebuild — Status & Method

**Status:** In progress, 2026-07-14. Two real classes reconstructed, compile-verified against
real headers (not just LSP-clean). Not yet deployed/tested live — this is source recovery, not
a live bug fix, since GliaSystemMenus/GliaTalkProto already work correctly as compiled into the
live LaPivot binary. This doc exists so the next session doesn't re-investigate from scratch.

**Working tree:** `/home/stephen/ncde-wm-rebuild/lapivot/`
- `oracle/LaPivot.oracle` — a copy of the live `/usr/local/bin/LaPivot` binary (md5-verified
  match), the reference truth for all decompile work.
- `live-qml/` — a full copy of `/usr/share/ncde/` (414 files, 22MB). QML is plain text loaded
  from disk at runtime, never lost, never needs decompiling — this is already-correct source.
- `ghidra-proj/` — Ghidra project analyzing the live LaPivot binary.
- `src/` — reconstructed, compile-verified C++ (see below).
- `*.decompiled*.c` / `*.java` — raw Ghidra decompiler output and the post-scripts that
  produced it, kept for reference/re-running.

## Corrected assumption (important — don't repeat this mistake)

**LaPivot IS unstripped** (`file` reports "not stripped"), same as `ncde-wm`. A prior session
told the operator otherwise; he knew this was wrong and said so repeatedly, and eventually
stopped correcting it. See memory `lapivot-has-dwarf-trust-operator-claims.md`.

**Precise nuance, confirmed via `readelf -S` and gdb directly:** LaPivot has a real, intact
`.symtab`/`.strtab` (function and class names are readable — `nm -C` works, Ghidra decompiles
with real names) but **no `.debug_info`/`.debug_line` DWARF sections**. gdb itself labels
everything "Non-debugging symbols." So this is symbol-table-assisted decompile (a real, useful
asset — much better than a stripped binary), not DWARF-exact struct-layout recovery like
Hummingbird's oracle binary allowed. Struct layouts here come from Ghidra's own inference from
the disassembly, verified by actually compiling the result against real headers — not asserted
from `gdb ptype`.

**Scale correction:** a full LaPivot rebuild is not blocked by missing debug info — it's a
scale/time constraint. `ncde-wm` alone (a real, valid starting-point binary LaPivot was built
from) has ~79 distinct classes worth of symbols; LaPivot itself is bigger (Lelan alone was 2531
live symbols per earlier session work). This is a long-term, incremental, class-by-class effort,
same shape as tonight's Hummingbird/Magpie work but larger — not a blocked/infeasible project.

## Prior work discovered mid-session (don't redo)

A substantial (14MB, 156 files) prior decompile effort already exists, covering most of
`ncde-wm`'s real classes: `LElan.c` (the core engine), `NCDEEngine.c`, `NCDEWindowManager.c`,
`ThemeManager.c`, `Settings.c`, `Launcher.c`, `AnimPolicy.c`, `DesktopWidget.c`, `NCDEMail.c`,
`LeapFrogPond.c`, `NCDECalendar.c`, `NotificationManager.c`, `NCDEWorkspace.c`,
`NCDEIconManager.c`, `AppMenuModel.c`, `HudManager.c`, `FreedesktopNotificationsAdaptor.c`,
`CursorManager.c`, `TrayWatcher.c`, `NCDEEventFilter.c`, `GliaSystemMenus.c`, `GlobalMenu.c`,
`NCDEMenuBridge.c`, plus dozens of STL/Qt template-instantiation helper files.

Location: `/home/stephen/ncde-wm-rebuild/src/decompiled/` (confirmed present on the live system
already, byte-identical to the USB mirror at
`/run/media/*/ncde-staging/ncde-wm-rebuild/src/decompiled/` — no copying needed, it was already
here, just hadn't been looked at before tonight). Also `/home/stephen/ncde-wm-rebuild/audit/` —
one `live-<ClassName>.txt` summary file per class.

**Important correction confirmed live this session: `NCDEMenuBridge.c` is DEAD/WRONG.** It's
entirely D-Bus based (`QDBusInterface`, `QDBusConnection::sessionBus()`, `kDBusMenuIface`,
`QDBusPendingCall`). Operator confirmed directly: *"we don't use ncdebridge glia does not use
dbus"* / *"we use glia talk."* The real, live mechanism is `GliaTalkProto` — raw X11
atoms/properties/ClientMessage events, no daemon, no D-Bus — and it was **not** in this prior
decompile batch at all (either decompiled before `GliaTalkProto` existed, or excluded from
whatever class list that pass targeted). Don't waste time trying to fix up `NCDEMenuBridge.c`;
it's not what's live.

Quality note: this prior batch is a rougher decompile than Hummingbird/Magpie's oracle-DWARF
work — several functions in `GliaSystemMenus.c` were visibly truncated by a Ghidra decompiler
issue (see below), and the file's own header says "Recovered source — clean up + edit," i.e. an
acknowledged first pass, not finished.

## Real architecture confirmed tonight (operator-provided + decompile-verified)

**GliaTalk is NCDE's in-house global menu system — an updated take on CDE's ToolTalk, with
Amiga and classic Mac OS influences (operator, verbatim). Deliberately not D-Bus.** Two classes:

- **`GliaTalkProto`** — the wire transport. `internAtom`/`readMenus`/`sendInvoke`, all three
  decompiled *cleanly and completely* (no truncation issues at all, high-confidence faithful
  translation): menu content is published as the literal X11 window property `_NCDE_MENUS`
  (read via chunked `xcb_get_property`); invocation is a raw `xcb_client_message_event_t`
  (format 32) carrying an item id, sent to `_NCDE_MENU_INVOKE` via `xcb_send_event`+`xcb_flush`.
  No socket, no daemon — the X11 display server itself is the transport, same pattern as
  EWMH/ICCCM window properties already use for everything else in this ecosystem.
- **`GliaSystemMenus`** — the menu *content* provider (scanned `.desktop` entries, places,
  recent files) that presumably feeds what `GliaTalkProto` publishes. Confirmed via decompile:
  constructor defers its first scan via `QTimer::singleShot(0, ...)`; `rescan()` consults both
  `QStandardPaths::ApplicationsLocation` and a hardcoded `/usr/share/applications`;
  `applications()` returns a cached `QList<QVariant>`, not recomputed per call; `launch(id)`
  matches an entry by `"id"` and shells out via `sh -c`; `openPath(path)` hands off to
  `xdg-open`. `recentFiles()`/`places()` bodies were not fully resolved by the decompiler (see
  below) — `places()` is confirmed to start with `"Home"` as its first entry.

## Known Ghidra decompiler issue (worth remembering for future classes)

`QString::QString` (both overloads) and `QString::~QString` were **incorrectly flagged
`NoReturn`** by Ghidra's auto-analysis on the live LaPivot binary. Since virtually every
non-trivial C++ function uses local `QString`s, this silently truncated the decompiler's output
right after the first `QString` construction/destruction in several `GliaSystemMenus` methods
(`launch`, `openPath`, `rescan`, `places`, `recentFiles`) — Ghidra printed a "Subroutine does
not return" warning and simply stopped there, hiding all subsequent real logic.

**Fix that worked:** a Ghidra post-script (`FixNoReturnAndRedecompile.java`, in the `lapivot/`
working tree) iterates functions named `QString::QString`/`QString::~QString`,
calls `fn.setNoReturn(false)` on any flagged as no-return, then redecompiles. This resolved the
truncation (`return;` now appears where the fake warning used to cut off the function) but did
**not** fully resolve every function body — some (`places`, `recentFiles` beyond their first
confirmed value) still have logic the decompiler can't cleanly reconstruct into readable C,
even with the flow now correct. That class of remaining issue needs Ghidra's interactive GUI
for manual disassembly review, not further headless scripting — diminishing returns past this
point for a single automated pass.

**Apply this fix proactively** at the start of any future LaPivot class reconstruction — check
`DiagnoseNoReturn.java`'s output (or rerun it) before spending time on a truncated function body,
since this is a binary-wide Ghidra analysis artifact, not specific to `GliaSystemMenus`.

## Reconstructed source (compile-verified against real Qt6/XCB headers, not just LSP)

`/home/stephen/ncde-wm-rebuild/lapivot/src/`:
- `GliaTalkProto.h`/`.cpp` — high-confidence, faithful translation (source functions decompiled
  completely, no gaps to fill in).
- `GliaSystemMenus.h`/`.cpp` — confirmed structure/call-patterns as above; `places()`,
  `recentFiles()`, `parseDesktopFile()`'s exact field set, and `folderFor()`'s category mapping
  are **reasonable reconstructions matching standard freedesktop.org/XDG conventions and this
  project's own established patterns elsewhere**, not byte-exact confirmed for LaPivot
  specifically — marked inline in the file's own comments. Verify against a real live
  GliaTalk menu (launch LaPivot's menu, compare against this implementation's output) before
  treating as final, same discipline as every other fix tonight.

Both compile clean: `g++ -std=c++17 -fPIC -c` against real `/usr/include/qt6/QtCore` and system
XCB headers, exit 0. Not yet linked into a full LaPivot build (would need the rest of LElan/
NCDEWindowManager/etc. wired together) or deployed anywhere live.

## Next steps for a future session

1. Continue class-by-class: `NCDEWindowManager`, `LElan` (the core engine, 4835 decompiled
   lines already exist from the older ncde-wm.prebak pass — cross-check against a live LaPivot
   redecompile the same way `GliaSystemMenus` was), `ThemeManager`, `NCDEEngine`.
2. For each: redecompile fresh from live LaPivot (not just trust the older ncde-wm.prebak
   batch — LaPivot has evolved since, confirmed by `recentFiles()` existing in LaPivot but not
   in the older decompile), apply the NoReturn fix proactively, write clean compile-verified
   C++, cross-reference the older batch only for structural hints, not as ground truth.
3. Eventually: assemble a real `CMakeLists.txt`/`build.sh` (matching Hummingbird/Magpie's raw
   g++/moc pattern, since cmake isn't installed on this node) once enough classes exist to link
   a meaningful subset, and verify against live LaPivot's actual runtime behavior before
   considering any piece "done" — same discipline as everything else this project has done.
4. `GliaSystemMenus`'s uncertain bits (`places()`/`recentFiles()`/`folderFor()`'s exact
   category list) should get a live verification pass — open the real GliaTalk menu, compare
   actual entries shown against what this reconstruction would produce.
