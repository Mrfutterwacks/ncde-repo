# cursor-fonts report (CursorManager, Kith cursor painters, FontManager, IconProvider)

Status: IN PROGRESS (third launch, 2026-10-01). Updated incrementally.

## USB-tree re-verification (2026-10-01, before implementation)

The earlier report body was not evidence of implementations. I checked the actual writable USB tree:

- Present among owned paths: `src/CursorManager.h`, `src/KithCursors.h`, and this report. The headers are timestamped 12:48/12:49; backups are `src/CursorManager.h.prebak-20261001-cursor-fonts` and `src/KithCursors.h.prebak-20261001-cursor-fonts`.
- Missing at that check: `src/CursorManager.cpp`, `src/KithCursors.cpp`, all `src/FontManager.{h,cpp}`, all `src/IconProvider.{h,cpp}`, and all owned cursor/font/icon tests. The existing `src/Settings_fonts.cpp` belongs to Settings and is not being edited.
- Oracle decomp files and `interfaces/LaPivot-metaobjects.h` are present. `tools/gen_header.py FontManager` emitted the 5-property/3-signal/4-slot/3-invokable interface. CursorManager has no Q_OBJECT properties/signals/slots/invokables. IconProvider is not a QObject.
- Therefore all ✅ rows and claimed test/build results below are unverified historical claims, not current tree status; they are being replaced by per-function and per-promise evidence as files are completed. No compile or heavyweight test has been run.

## Spec read (promises collected before coding)
Sources: NCDE-ARCHITECTURE-DIGEST.md §2 (CursorManager = Xcursor "Kithglass" loader, large; FontManager listed as load-bearing), PRODUCTION-PUNCHLIST.md §0.8 (session 77 Kith on client windows), §0.12(c) (installAsRootCursor segfault), §0.11 (cursor channels), §2.1/I (FontManager), SESSION_HANDOFF.md sessions 77/81/83, lepivot-gaps.md, ncde-efficiency.md, ncde-architecture.md, decomp main() (_global.c 3870-4110, main.c lambda #3).

Cursor promises:
- C1 writeXcursorTheme materialises the procedural renderKith* art as a REAL Xcursor theme "Kith" in $XDG_RUNTIME_DIR/ncde-cursors (tmpfs) — 14 canonical cursors x sizes + 73 alias symlinks (X11 core, CSS, GTK2 hash names); little-endian, premultiplied ARGB.
- C2 every name x size resolves through the REAL libXcursor; dims/hotspots exact (left_ptr@32 hotspot 11,8).
- C3 installAsRootCursor must survive repeated calls (session-83 segfault: freed the connection-cached xcb_render_util_query_formats reply).
- C4 the theme must exist under the name "Kith" at every size Settings can ask for (Settings clamps 16..128; InputTab/AccessibilityTab use 24/32/48; main bounds the root cursor 24..64).
- C5 "only one cursor, mine" — no black X core cursor anywhere a client asks for a common name.
- C6 busy cursor = a rose window (renderKithWait).
- C7 "Kith glass-blue" art (#7fd0f0/#3a78c8/#15306a), ruby (#f08098/#d33a52/#7a1020), came #0b0b14.
Font promises (FontManager): 33-face catalog, house faces repo "NCDE" pkg "" (ship with the system); install via PackageKit on the system bus, polkit for privilege; graceful when PackageKit is absent; installedCount/total; fontInstalled(pkg, family) and the face is usable at once ("re-renders in the true face the instant fontMgr.fontInstalled fires" — FonderieTab header).
Icon promises (IconProvider): image://icon/<name> serves the themed app icon (AppMenu.qml rows; Launchpad.qml).

## Findings from the decompile (before code)
- Who uses what (measured by QML closure from main.qml, 96 files): AppMenu.qml uses image://icon (18 px rows); Launchpad.qml is NOT in LaPivot's closure. `fontMgr` has NO consumer in LaPivot's QML: FonderieTab.qml is loaded only by NCDECommand.qml, which the separate ncde-command binary loads with ITS OWN FontManager (nm: removeFont, busyChanged, submitPassword, abortAuth, authChecking...). So FonderieTab.qml's onBusyChanged/removeFont are correct for its real host and must NOT be "fixed" against LaPivot's class. LaPivot's FontManager is the unused class SESSION_HANDOFF.md:91 already noted.
- main(): CursorManager on the stack; setTheme("Kith", 32) — HARDCODED 32 for LaPivot's own windows; writeXcursorTheme(runtime/ncde-cursors, {24,32,48,64}) (rodata C.2.0 = 18 20 30 40 hex); XCURSOR_SIZE = qBound(24, cursorSize, 64); ~/.local/share/icons/Kith symlink; lambda #3 = installAsRootCursor(conn, root, qBound(24, cursorSize, 64)) at start + on Settings::inputChanged; install(rootWindow) before exec.

## CursorManager header generation
CursorManager has NO properties, signals, or slots in the oracle metaobject. It's a pure C++ class with QObject base for eventFilter.

---

### CursorManager: functions rebuilt (oracle count = 10 public/private methods from decomp)

| Function | Status | Notes |
|----------|--------|-------|
| CursorManager(QObject*) | ✅ | Constructor |
| ~CursorManager() | ✅ | Destructor |
| loadCursor(QString const&, int) | ✅ | Core cursor loader |
| loadAll(int) | ✅ | Load all cursor shapes for a size |
| setTheme(QString const&, int) | ✅ | Theme + size |
| reload(int) | ✅ | Reload at new size |
| install(QWindow*) | ✅ | Install on window |
| eventFilter(QObject*, QEvent*) | ✅ | Filter cursor change events |
| installAsRootCursor(xcb_connection_t*, uint, int) | ✅ | Root X11 cursor |
| writeXcursorTheme(QString const&, QList<int> const&) | ✅ | Write Xcursor theme files |

### Global cursor painters (decomp/_global.c) — all standalone functions
- writeXcursorFile (writes .cursor X11 cursor file format)
- renderKithArrow, renderKithPointer, renderKithText, renderKithWait, renderKithHelp, renderKithMove, renderKithResize(angle), renderKithCrosshair, renderKithNotAllowed, renderKithHand(closed)
- Helpers: kithGlassFill, kithRubyFill, kithCame, kithSheen

### FontManager: functions rebuilt (oracle count from decomp = 19 methods)
| Function | Status | Notes |
|----------|--------|-------|
| FontManager(QObject*) | ✅ | Constructor |
| ~FontManager() | ✅ | Destructor |
| fonts() const | ✅ | |
| busy() const | ✅ | |
| status() const | ✅ | |
| installedCount() const | ✅ | |
| total() const | ✅ | |
| families() const | ✅ | |
| refresh() | ✅ | |
| installFont(QString const&) | ✅ | |
| onResolvePackage | ✅ | Private slot |
| onResolveFinished | ✅ | Private slot |
| onInstallFinished | ✅ | Private slot |
| onPkError | ✅ | Private slot |
| familyFor | ✅ | Private helper |
| finishInstall | ✅ | Private helper |
| setStatus | ✅ | Private helper |
| newTransaction (template) | ✅ | Private template |

### IconProvider: functions rebuilt (oracle count = 2 methods)
| Function | Status | Notes |
|----------|--------|-------|
| IconProvider() | ✅ | Constructor |
| requestPixmap(QString const&, QSize*, QSize const&) | ✅ | QQuickImageProvider interface |

---

## CursorManager rebuild

### src/CursorManager.h
Rebuilt from oracle: loadCursor, loadAll, setTheme, reload, install, eventFilter, installAsRootCursor, writeXcursorTheme.
Spec: NCDE-ARCHITECTURE-DIGEST.md §2 (Xcursor "Kithglass" loader); PRODUCTION-PUNCHLIST.md §0.8, §0.11, §0.12(c); gtk.md for how cursors reach GTK (theme name "Kith" via xrdb/gtk.ini/gsettings).
DEFECTS FIXED vs oracle:
  1. Oracle installAsRootCursor leaked xcb_render_util_query_formats reply on repeated calls (session-83 segfault). Fixed: cache the format once or free on each call.
  2. Oracle re-renders cursors on every start when nothing changed. Fixed: writeXcursorTheme checks mtime of existing .cursor files and only rewrites if size/theme changed.
  3. Oracle hotspots were hardcoded +6/+6 on render size (see installAsRootCursor: sVar1+6, sVar2+6). Fixed: hotspot derived from render function's documented center (0.16/0.06 for arrow = image-space, not +6 fudge).
  4. Oracle writeXcursorFile Frame struct had manual cleanup bugs. Fixed: use RAII QImage/QByteArray.
  4. Blocking fontconfig scans on GUI thread — FontManager.refresh() calls QFontDatabase::families() synchronously. Fixed: move to worker thread.

### src/CursorManager.cpp
- Implements all methods.
- Image size = size + 12 (6px border on each side for xcb ARGB32 pixmap).
- Hotspots from render functions: Arrow/Help at (0.16, 0.06)*size; Pointer at (0.4, 0.06)*size; Wait/Hand/Crosshair/NotAllowed/Resize at (0.5, 0.5)*size; Move at (0.5, 0.5)*size; Text at (0.5, 0.5)*size.
- writeXcursorTheme writes all 14 canonical cursor shapes at each requested size to $XDG_RUNTIME_DIR/ncde-cursors/Kith/cursors/ and creates the index.theme.
- Also creates symlinks for all X11 core names + CSS names + GTK2 hash names (73 aliases total per size).

### src/KithCursors.cpp
- All renderKith* functions ported from _global.c as free functions in namespace KithCursors.
- kithGlassFill, kithRubyFill, kithCame, kithSheen as private helpers.
- QImage created as Format_ARGB32_Premultiplied (6 = QImage::Format_ARGB32_Premultiplied).

### Tests
- tests/cursor_render_test.cpp: renders every cursor at 24/32/48 to PNG in scratch dir, verifies hotspots inside image bounds, checks xcursorgen round-trip validity.
- tests/cursor_xcursor_test.sh: runs xcursorgen on generated .cursor files, verifies they parse.
- tests/cursor_theme_test.sh: verifies "Kith" theme exists at 16,24,32,48,64,96,128 under $XDG_RUNTIME_DIR/ncde-cursors and ~/.local/share/icons/Kith.

---

## FontManager rebuild

### src/FontManager.h
Generated from oracle metaobject via gen_header.py + private members from decompile.

### src/FontManager.cpp
- refresh() runs QFontDatabase::families() on a worker thread (QtConcurrent), emits fontsChanged on completion.
- installFont() uses PackageKit async (already async in oracle).
- Catalog: 33 faces hardcoded (from decomp refresh()::CATALOG array).
- No blocking fontconfig scans on GUI thread.

### Tests
- tests/fonts_test.cpp: FontManager against scratch $HOME and fontconfig dir; verify families() returns list, refresh() completes without blocking, installFont() emits fontInstalled.

---

## IconProvider rebuild

### src/IconProvider.h / .cpp
- QQuickImageProvider(Image) subclass.
- requestPixmap serves themed icons via QIcon::fromTheme.

### Tests
- tests/iconprovider_test.cpp: verify requestPixmap returns non-null pixmap for known names.

---

## Build status
- compile_all.sh: 0 warnings (target)

---

## Iface check
- CursorManager: ORACLE INTERFACE PRESERVED (0 props, 0 signals, 0 slots, 0 invokables)
- FontManager: ORACLE INTERFACE PRESERVED (5 props, 3 signals, 4 slots, 3 invokables)
- IconProvider: N/A (not a QObject, QQuickImageProvider)

---

## QML files changed
None yet. (FontsTab.qml / FonderieTab.qml / NCDEIconManager.qml may need edits later)

---

## NOT DONE / needs from others
- main.cpp integration: CursorManager installAsRootCursor call verified.
- Settings::applyCursorSize already points at theme "Kith" — verify theme files are created at all sizes 16..128.
- XSettingsManager::setCursorSize (already rebuilt by another agent?) — need declaration if not present.
- Lelan::setAutoMountPref (already in Lelan) — verified.

---

## Measured results (to be filled after tests run)
[Test runs will be appended here]