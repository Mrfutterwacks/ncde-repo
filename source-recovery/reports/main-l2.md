# main-l2 — main(), asset base, CMake/resource wiring

**Status: IN PROGRESS; source build/link gate not met.** Updated 2026-10-01 after rereading
`AGENT-BRIEF.md`, `README.md`, `RELEASE-GATE.md`, `_relaunch-preamble.txt`, this assignment, and the
other current reports. Worktree: `/run/media/stephen/NCDE-BACKUP/my-project/source-recovery/LaPivot`.
Owned files only: `src/main.cpp`, `src/ncde_paths.h`, `src/CMakeLists.txt`, `src/resources/*`,
`tests/main_*`, `tests/build_*`, and this report. No QML or other group's source was edited.

## 1. Oracle/spec checks

Measured against `decomp/_global.c:3699-4200`, `decomp/main.c`, `nm -C oracle/LaPivot.oracle`,
`readelf -d oracle/LaPivot.oracle`, and `interfaces/LaPivot-metaobjects.h`:

- Oracle entry point is `main` at `0xf4190`; five callable lambdas are in `decomp/main.c`.
- Startup order in the oracle is QSurfaceFormat/logging, QGuiApplication, Lelan/NCDEEngine/Settings/
  Theme/WidgetData/AnimPolicy and the remaining context objects, `applyZenStartupHints`, WindowTyper,
  WM/IdleInhibit, cursor/XSettings setup, icon theme, QML engine and context properties, QML load,
  window cursor install, `app.exec()`. `main.cpp` follows this order; FontManager is constructed when
  its context property is installed, after the QML engine and before the context uses it.
- The 18 context names in oracle order are `lelan`, `ncde`, `settings`, `theme`, `fontMgr`,
  `widget_data`, `animPolicy`, `launcher`, `notifications`, `windowMgr`, `calBackend`,
  `ncdeWorkspace`, `appMenuModel`, `window`, `pond`, `gliaSystem`, `geo`, `hudManager`.
  `main.cpp` contains these 18 registrations in that order. `window` is `ScreenInfo`; `ncde` is
  `NCDEEngine`. WindowTyper, CursorManager, XSettingsManager and IdleInhibitService are not context
  properties.
- Oracle chooses `/usr/share/ncde-test` only when the executable filename is `ncde-test`, otherwise
  `/usr/share/ncde`; a missing `main.qml` loads `qrc:/Shell.qml`. The rebuild keeps the name-specific
  base rule but removes that fallback: it logs a critical error and returns instead of loading the
  embedded developer harness, which called save methods and exited shortly after startup.
- The oracle application attributes argument is `0x60b01`. Qt's headers decode it as
  `AA_Use96Dpi | AA_DisableNativeVirtualKeyboard | AA_SynthesizeTouchForUnhandledMouseEvents |
  AA_UseSoftwareOpenGL | AA_ShareOpenGLContexts`. The rebuilt code intentionally uses plain
  `QGuiApplication(argc, argv)`: software GL conflicts with the design's threaded render-loop
  requirement (`docs/anim-policy.md`, `docs/ncde-efficiency.md`). This is a deliberate behavior
  difference, not oracle parity; real-GPU rendering still needs the post-link sandbox test.
- `readelf -d` confirms the oracle's direct dependency families: Qt6 Core/Gui/Qml/Quick/OpenGL/DBus/
  Network, XCB (+ render/renderutil/shape/randr/xfixes/screensaver/xinput/icccm), libpulse, libcrypt,
  OpenGL and GLX. CMake requests/links these. This is a link declaration check, not proof of a
  successful full link.
- The oracle's resource initializer is `qInitResources_lelan` (RCC v3); the resource names include
  `Shell.qml` and the color-wheel shader. The canonical `SettingsColorWheel.qml:72` consumes
  `qrc:/shaders/qml/compositor/colorwheel.frag.qsb`. The new `resources/lelan.qrc` embeds that
  existing `.qsb` at that exact URL. It intentionally does not embed the unsafe Shell.qml fallback.

## 2. Owned changes

- `src/main.cpp`: retained the oracle's 18 context registrations and construction/wiring order;
  constructs FontManager at QML context setup. Existing approved M1 wiring calls
  `prctl(PR_SET_DUMPABLE, 1)` before Qt setup. Existing storage wiring seeds
  `Lelan::setAutoMountPref(Settings::autoMountUsb())` and follows `storageChanged`. Existing idle
  wiring supplies `Settings::idleMsSource` from `NCDEWindowManager::userIdleMs()` and connects
  `idleSample` to `Settings::onIdleSample()`. Existing `WidgetData::setSettings()` call wires the
  panel clock. Idle/screensaver policy is not duplicated in main; Settings/IdlePolicy owns it.
- `src/ncde_paths.h`: central `assetBase()`/`assetPath()` helpers honor only absolute
  `NCDE_ASSET_BASE`, otherwise use the compiled default; retain the oracle's `ncde-test` fallback.
  Non-absolute compiled values now fall back to `/usr/share/ncde/`, and the CMake cache rejects
  relative values.
- `src/CMakeLists.txt`: replaced the hand-maintained/duplicated source list with configure-aware
  `src/*.cpp` and `src/*.h` collection, `AUTOMOC`/`AUTORCC`, Qt/XCB/Pulse/Crypt/OpenGL dependencies,
  `-Wall -Wextra`, an absolute string cache option `LAPIVOT_ASSET_BASE`, and a `LaPivot-L2` output
  name. The install-time `setcap cap_sys_nice+ep` remains aimed at `/usr/local/bin/LaPivot-L2`.
  Removed the premature CMake rule that attempted to install not-yet-gated stage scripts.
- `src/resources/lelan.qrc`: restores the consumed shader resource under its canonical qrc URL.
- `tests/main_test.cpp`, `tests/main_test.sh`, `tests/build_main_test.sh`: fixed the duplicate `main`
  in the old test by renaming the included entry point; added checks for absolute/trailing-slash asset
  base behavior and ordered context names. The test build now keeps scratch output below `tests/`,
  does not use `mktemp` or `/tmp`, links XCB, and creates trap stubs only for LaPivot classes (not
  Qt/standard-library imports).

### main and oracle-lambda coverage

The oracle has `main()` plus five lambdas (six functions total). Source review confirms:

| Oracle function(s) | Rebuild location | Status |
|---|---|---|
| `main()` | `src/main.cpp::main` | 1/1 reconstructed; the 18 property registrations and startup order are checked above. |
| lambda #3 (install root cursor) | `installRootCursor()` + initial call and cursor-size update | 1/1 behavior represented. |
| lambda #4 (XSETTINGS cursor update) | `Settings::inputChanged` connection in `main()` | 1/1 behavior represented; now bounded-size-change and selection-owner guarded. |
| lambda #1 (screensaver timeout), #2 (screensaver start), `(int,bool)#1` (crash relaunch) | `Settings`/`IdlePolicy`, not duplicated in main | 0/3 direct main callbacks; these behaviors are delegated to the single idle owner. The timeout/blank calculation is still missing from `Settings::applyIdleConfig()` (reported §3); runtime behavior is unverified here. |

Other main-owned wiring changes (source-inspected, not runtime-proven): M1 `prctl` first; M2 initial
and changed auto-mount preference; M3 one idle owner; M4 Settings to WidgetData; M5–M7 cursor-size
change/notification guards; M8 no unsafe embedded-shell fallback; M9 shared asset-base helper; M10
FontManager local lifetime; M11 per-UID cursor fallback directory.

Validation run:

```text
shell syntax: PASS
qrc XML/source: PASS (qrc:/shaders/qml/compositor/colorwheel.frag.qsb)
CMake static contract: PASS (67 current src cpp files; all globbed)
main context list/order: PASS (18)
main quoted headers: PASS (24 present)
```

These checks used `bash -n` and Python static/XML assertions only. **Not run:** main test, CMake
configure, compile, full link, sandbox launch or install. Other workstreams are active and
`src/build/` already existed at entry; no build directory was created or reused. No compiler was
started, preserving the coordinator's no-competing-build rule.

## 3. Cross-group integration status (exact unresolved work)

These are declarations/implementations from other owners; not edited here.

| Owner | Current evidence | Exact remaining integration |
|---|---|---|
| widgets | `WidgetData.h` and `WidgetData.cpp` now declare/implement `Q_INVOKABLE void setSettings(Settings *)`; `main.cpp` calls it. | None for this connection. Implementation/test is not certified by this report. |
| lelan + settings | `Lelan.h` declares `inputDevicesChanged()`; `Lelan_devices.cpp` emits it. `Settings_power.cpp::setLelan()` now connects it to private `Settings::applyInput()`. | None for input hotplug wiring; still needs the group's tests/interface check. |
| wm | `NCDEWindowManager.cpp` currently defines `userIdleMs()` and emits `idleSample(idleMs)`; matching declarations and Settings callback exist. | No main wiring request remains. This new implementation has not been compiled/tested here. |
| settings | `Settings_power.cpp::applyIdleConfig()` still sets `c.saverMinutes = m_screensaverTimeout`. | Must apply the oracle's timeout/blank rule: `minutes = (timeout < 1 || blank < 1) ? max(timeout, blank) : min(timeout, blank)`, with blank selected by AC/battery. Keep the fix in Settings, not main. |
| settings | `Settings.cpp` reads `NCDE_ASSET_BASE` independently with `/usr/share/ncde/` default; `Settings.h` also initializes `m_assetBase` to that literal. | Make `Settings::assetBase` derive from `ncde::assetBase()` so QML and main use one resolved base, including compiled custom defaults and relative-env fallback. |
| lelan | `Lelan_users.cpp::setUserAvatar()` independently reads `NCDE_ASSET_BASE` and joins it to the avatar name. | Replace the duplicate base with `ncde::assetBase()` so L2 account avatars resolve under `/usr/share/ncde-l2/`. |
| cursor-fonts / colour / wm | Current tree contains `NCDEEngine.cpp`, `Theme.cpp`, `KithCursors.cpp`, `CursorManager.cpp`, `FontManager.h/.cpp`, `IconProvider.h/.cpp`, `NCDEWindowManager.cpp`, and `XSettingsManager.cpp`; required headers are present. | No main-owned declaration gap remains. These parallel implementations and the full main translation unit still need the serialized warning-clean compile and full link; none was run here. Recheck this moving source tree before build. |
| QML owner/coordinator | Canonical QML still has executable hardcoded asset paths: `main.qml:134,167`; `MagpieTalker.qml:147,1549`. | Change these consumers to `settings.assetBase + relativePath`; do not edit QML in main-l2. Other `/usr/share/ncde` matches found in comments are not executable paths. |

The old report's “needs WidgetData method”, “needs WM declarations”, “Settings has no
`inputDevicesChanged` connection”, and missing FontManager/IconProvider notes are stale: those
declarations/implementations and required headers now appear in the current tree. None of those
parallel changes is build-verified by this report.

## 4. Asset references and shared settings

Oracle decompilation has three asset-base literals:

1. `_global.c:4174,4182` in main (`/usr/share/ncde`, `/usr/share/ncde-test`) — routed through
   `ncde::assetBase()` here.
2. `Settings.c:2538` — request to Settings owner above.
3. `Lelan.c:17161` in `Lelan::setUserAvatar()` — request to Lelan owner above.

The canonical QML's four executable absolute asset references and owners are listed in §3.

Observed rebuilt config locations include:

- Settings area files under `~/.config/ncde/`: `accessibility.json`, `autostart.json`,
  `color-overrides.json`, `datetime.json`, `display.json`, `dock.json`, `filigree-palettes.json`,
  `fonts.json`, `glass-surfaces.json`, `input.json`, `locale.json`, `network.json`,
  `notifications.json`, `power.json`, `privacy.json`, `screensaver.json`, `section-colors.json`,
  `security.json`, `session-defaults.json`, `sound.json`, `storage.json`,
  `wallpaper-slideshow.json`, `widget-styles.json`; plus `wallpaper.conf`.
- `NCDEEngine`: `active-theme.json`, `terminal.json`, `filigree-palettes.json`,
  `glass-surfaces.json`, `widget-styles.json`; writes GTK bridge/theme files under
  `~/.themes/NCDE/gtk-3.0/`, `~/.config/gtk-4.0/`, `~/.gtkrc-2.0`, and `~/.config/gtk-4.0/`.
- `Settings`: rewrites `~/.config/autostart/ncde-auto-*.desktop`, and its cursor application updates
  `~/.config/gtk-3.0/settings.ini` and `~/.config/gtk-4.0/settings.ini`; Settings can also operate
  an existing `vesper-brain.service` through `systemctl --user enable/disable --now`.
- `NCDEEngine`: writes the generated GTK palette/theme CSS files under
  `~/.themes/NCDE/gtk-3.0/` and `~/.config/gtk-4.0/`, and `~/.gtkrc-2.0`.
- `CalendarBackend`: `calendar.json` (shared with `cal-reminders`).
- `LeapFrogPond`: `lilypad.json`.
- Lelan's config helpers read/write dynamic `~/.config/ncde/<name>.json` component files.
- `CalendarBackend` also writes transient `~/pending/compose_<uuid>.json` files for the mail client.
- `main.cpp` reads `active-theme.json` and may create `~/.local/share/icons/Kith` as a symlink;
  this code does not write the JSON file. CursorManager writes generated cursors under
  `$XDG_RUNTIME_DIR/ncde-cursors`.

The JSON area/component file names remain in `~/.config/ncde`; writers use JSON objects and
`QSaveFile`/indented JSON in the rebuilt helpers. `calendar.json` keeps the documented daemon
contract `{appointments, todos, settings}`; `lilypad.json` keeps `{notes, notice}`. GTK/autostart
files retain their existing names and key formats. This source inspection shows no deliberate
schema-version or filename migration, but **does not establish full old-session compatibility**:
there was no oracle-vs-rebuild schema diff and no file was read/written in this task. Verify against
the class reports and a copied scratch HOME before offering L2.

## 5. Deployment transforms and source equivalents

`deploy_lapivot()` in `files/NCDE-Installer/ncde-full-patch-20260711.sh:367-385` runs three same-length
palette edits in sequence and then sets the file capability. `reports/colour.md` independently
identifies their intended source replacement. These must be implemented/tested in NCDEEngine source:

1. `apply-iris.py`: populates approved values for accent, border, panelBg and surface across all 90
   palette entries in three table copies.
2. `apply-iris-contrast.py`: changes the specified 25 accent entries to the WCAG-contrast values.
3. `apply-iris-widen.py`: widens the specified seven accent pairs to the approved perceptual values.

The coordinator/colour source work owns the generated palette data and rebuild equivalent; no
binary patcher was run or copied here. `cap_sys_nice` remains an install-time `setcap` operation in
CMake. The separate README source fixes for RT child priorities and xset polling are class-owned
work, not binary palette transforms; they are not implemented by `main.cpp`.

## 6. Release/build sequence and gate

1. Finish the missing owner source and cross-group integrations above; update their reports/tests.
2. After other groups stop editing, run each relevant interface and focused test, then the serialized
   `bash LaPivot/tests/compile_all.sh` gate with **zero warnings**.
3. Configure/build the CMake `LaPivot` target from all `src/*.cpp`, verify a **complete full link** and
   dependency set, then run the isolated Xvfb/bwrap QML smoke test. Record measured outputs.
4. Only after steps 2–3 pass may the coordinator stage L2 files. An operator installs and tests L2;
   only explicit operator approval permits promotion and then ISO reauthoring.

At entry, `source-recovery/l2-stage/INSTALL-L2.sh`, `UNINSTALL-L2.sh`, and `PROMOTE-L2.sh` already
existed (mtime 12:45). I did not create, edit, stage, inspect by execution, or run them. They remain
untouched; the source build/full-link gate is still pending, so this report makes no claim that L2 is
ready or staged by this work.
