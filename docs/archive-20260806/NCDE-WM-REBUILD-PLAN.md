# NCDE-WM REBUILD PLAN — "make NCDE what the host tried to be"

**Status:** plan + evidence captured 2026-06-27. Ready for execution by an agent with
root access to the staging tree. Operator (Stephen) is the authority; this doc records
HIS plan and the evidence behind it. Do **not** re-litigate any of it.

---

## 🔴 CURRENT TRUTH (2026-07-17) — SUPERSEDES ALL `ncde-staging` REFERENCES BELOW

**The dev machine that hosted `~/ncde-staging/` is gone.** Every `~/ncde-staging/...` path in this
document (the "recovered source" oracle dir, `compass7/lelan/`, `LaPivot/compass7/lelan/`, the
`ncde-wm-work/ref/` and `scratch/` copies) does not exist anymore — checked directly on this
machine and on the USB backup, 2026-07-17. This whole document is now a **historical record** of
the 2026-06-27/28/30 investigation, not an executable plan. Do not follow the EXECUTION STEPS or
KEY PATHS below as written; do not tell the operator the source is "not lost" per Hard Rule 1
below — that claim is now false.

Current model (see `docs/CLAUDE.md` banner + Hard Constraint 2 + §9-10, and `docs/thisisit.md`'s
own 2026-07-17 correction, for the full picture):
- The **live running system** (`/usr/local/bin/LaPivot`, `/usr/share/ncde/`) is the source of
  truth now — there is no separate tree to stage or build from.
- The **original C++ source is genuinely lost** — no copy exists anywhere checked, including the
  `compass(7).zip`/`compass7-reference` handoff bundle (its `Lelan.cpp` is a ~500-line stub
  reimplementation labeled "original lost," not the real ~4,835-line engine).
- Recovery path now: Ghidra-decompiling the live LaPivot binary as the oracle, reconstructed
  class-by-class in `~/ncde-wm-rebuild/` — partial, see `docs/lapivot-rebuild.md`.
- QML was never lost — plain text at `/usr/share/ncde/`.
- Deploy mechanism now: `~/my-project/files/ncde-full-patch-20260711.sh`.

---

## CURRENT TRUTH (2026-06-28, itself superseded 2026-07-17 above) — SUPERSEDES THE "root-protected 41-file source" STEPS BELOW

The "**locate the 41 real source files under `[dead-legacy-tree]/root` (root-protected)**" steps below are **DEAD**.
Those `.cpp` files are **GONE as files** (verified — `[dead-legacy-tree]/root` is just root's `.ssh`/`.gnupg`). The
real source was **recovered by Ghidra-decompiling the unstripped+DWARF binary**:

- **Recovered source (THE ORACLE) → `~/ncde-staging/ncde-wm-rebuild/src/decompiled/<Class>.c`** (153 classes).
  Ghidra C = readable answer-key, not a direct cmake target. Exact headers via `gdb ... ptype /o <Class>`.
- **PLAN (operator-confirmed):** make **the host (`~/ncde-staging/compass7/lelan/`) INTO `ncde-wm`, WITH its
  upgrades** — base = recovered REAL behavior, graft only upgrades **verified vs the live binary**, then
  transfer to `[dead-legacy-tree]/src` (operator sudo) → ISO.
- **TEST (RETIRED 2026-06-30 — see `thisisit.md` CURRENT TRUTH / `SESSION_HANDOFF.md` session 39):** this
  bullet originally said to install builds to a separate `/usr/local/bin/ncde-test` + `"NCDE (test host)"`
  session. That parallel-test-tree model is retired — do not recreate it. The host build (now named
  **LaPivot**) lives and is verified directly in `~/ncde-staging/LaPivot/compass7/lelan/`; there is no
  separate install-to-test step anymore.

The GOAL section below still stands; only the "where the source is / how to install-to-test" mechanics are superseded.

---

## THE GOAL (operator's words, made concrete)

Rebuild the operator's **full, real `ncde-wm`** — his complete working desktop, every
file intact — **with the Lelan architecture the test host got right**: `NCDEEngine` =
colors only, Lelan owns all system/process work, **WiFi working**. Keep the good
separation; throw away nothing. End result = what the stripped "host" was *trying* to be,
but on the real desktop.

> Recompile the `.bak` (the correct ncde-wm) **after fixing it**, by adding all of the
> operator's source files (which are in the staging tree) to **lelan's CMakeLists** (the
> only CMakeLists we have, and the one that carries the WiFi fix).

---

## HARD RULES (do not break — these caused the whole mess)

1. **(2026-06-28, superseded 2026-07-17)** At the time this rule was written, the source
   was NOT lost/missing and the staging tree was complete — lelan compiling proved it. That
   is no longer true: the staging tree is gone (see the 2026-07-17 banner at the top of this
   doc) and the original C++ source is genuinely lost. Don't reassert this rule's original
   claim as current fact. It's also still not license to casually call a class "unrecoverable"
   — the Ghidra-oracle recovery path in `~/ncde-wm-rebuild/` is real, just partial; check
   `docs/lapivot-rebuild.md` before assuming a class can't be reconstructed.
2. **`NCDEEngine` handles COLORS ONLY** (filigree palettes → all colors/fonts/glass).
   WiFi / NetworkManager / BlueZ / audio / printers / users / timezone = **Lelan's** job.
3. **Never ship the reconstruction.** The `.bak` (20.7 MB) is the correct binary.
4. **Work in the staging folder** `[dead-legacy-tree]`. The operator's real source lives there,
   **root-protected** (so a non-root agent cannot read it — that is NOT "missing").
5. Don't run `sudo` on the operator's behalf without handing him the command; never
   delete project files.

---

## ESTABLISHED FACTS (all evidence-backed this session)

### The real working WM
- Running live: `/usr/local/bin/ncde-wm` — **20,703,136 bytes**, NOT stripped, full DWARF
  debug info, `BuildID a6aa1df949e864be212db2973ae938a034a54a8e`,
  `sha256 99c7647137a8475e87c50d9a84593a58aee0a0cd8fdb782a4ef1fdb690b24298`.
- Compiled with GCC 16.1.1 `-g`, **comp_dir `[dead-legacy-tree]/build`**.

### The `.bak` (the correct ncde-wm to fix) — byte-identical copies
- `[dead-legacy-tree]/usr/local/bin/ncde-wm.prebak`  ← the .bak in the staging folder
- `~/ncde-staging/ncde-wm-work/ref/ncde-wm.LIVE`
- `~/ncde-staging/ncde-wm-work/ref/ncde-wm.baseline-20M`
- Working copy staged at: **`~/ncde-staging/scratch/ncde-wm.prebak`**
- All sha256-match the live binary.

### What the WM DRAWS FROM (the desktop) — complete in the staging tree
- `[dead-legacy-tree]/usr/share/ncde/` = **200 QML + 45 JS** + assets. The whole desktop UI.
  This is the operator's source for the desktop and it is 100% present/editable.

### The operator's real WM SOURCE — in the staging tree, root-protected
- The `.bak`'s own debug info lists **41 source files** it was built from (authoritative).
- They are under the **root-protected** part of the staging tree (e.g. `[dead-legacy-tree]/root`,
  mode `drwxr-x---`). A non-root agent gets "Permission denied" — this is why every
  readable search came up empty. **The files are there; locate them with root.**
- Layout: flat `src/*.cpp/.h` **plus a `src/ncde/` subdir**.
- Locate exactly (operator runs):
  ```
  sudo find [dead-legacy-tree]/root -type f \( -name '*.cpp' -o -name '*.h' \) \
       \( -path '*ncde*' -o -name 'cursormanager*' -o -name 'LElan*' \) 2>/dev/null
  sudo find [dead-legacy-tree]/root -type f -name CMakeLists.txt 2>/dev/null
  ```

### The test host (the reconstruction) — what NOT to ship
- `~/ncde-staging/compass7/lelan/` → builds `lelan-host` (~2.3 MB).
- Only **23 source files**, mostly **header-only stubs**. An AI built it from the
  operator's source but **stripped the desktop down**. It ALSO overwrote `[dead-legacy-tree]/src`
  and the staged `ncde-wm` binary with this reconstruction (a directive violation).
- It did one thing RIGHT (keep this): the NCDEEngine/Lelan separation + working WiFi.

---

## THE HOST'S GOOD CHANGE (the part we keep) — "architecture A"

- **`NCDEEngine` = colors only.** palette tokens, Motif-derived decoration colors,
  fonts/mode/scalars, color-wheel overrides, 90 Iris Chroma presets, `sampleWallpaper`,
  glass tinting. It also *lists* system properties (`wifiEnabled`, `bluetoothEnabled`…)
  but they are **pure pass-through**: `wifiEnabled(){ return m_lelan ? m_lelan->wifiEnabled() : false; }`.
  Zero system state, zero system logic in the engine.
- **Lelan owns every system/process service over D-Bus:** WiFi (NetworkManager —
  `subscribeToWifi`, `rebuildAccessPoints`→`GetAllAccessPoints`, `setWifiEnabled`→
  `WirelessEnabled`, `connectWifi`→`AddAndActivateConnection`, `disconnectWifi`), Bluetooth
  (BlueZ), VPN, audio (libpulse), UPower, UDisks2, power profiles, users, printers,
  timezone, tray (SNI), MPRIS.
- **The seam:** `NCDEEngine::setLelan(Lelan*)` stores the pointer and connects Lelan's
  change signals → NCDEEngine notify signals (`wifiChanged`, `dateTimeChanged`,
  `usersChanged`, `printersChanged`, `soundChanged`). Data flows
  **Lelan (owns service) → emit → NCDEEngine re-emit → QML rebinds.**

---

## THE 41 SOURCE FILES THE REAL ncde-wm USES (from the .bak's debug info)

Flat in `src/`:
```
main.cpp
LElan.cpp  LElan.h                 (capital-E — the real Lelan)
cursormanager.cpp  cursormanager.h
desktopwidget.cpp  desktopwidget.h
globalmenu.cpp  globalmenu.h
NCDEEventFilter.cpp  NCDEEventFilter.h
NCDEMenuBridge.cpp                  (+ .h if present)
NCDEWindowManager.cpp  NCDEWindowManager.h
AnimPolicy.cpp  AnimPolicy.h
AppMenuModel.cpp  AppMenuModel.h
GliaSystemMenus.cpp  GliaSystemMenus.h
hudmanager.cpp  hudmanager.h
Launcher.cpp  Launcher.h
LeapFrogPond.cpp  LeapFrogPond.h
Settings.cpp  Settings.h
notificationmanager.cpp  notificationmanager.h  notificationadaptor.h
thememanager.cpp  thememanager.h
```
In `src/ncde/`:
```
ncde/NCDECalendar.cpp  ncde/NCDECalendar.h
ncde/NCDEEngine.cpp    ncde/NCDEEngine.h
ncde/NCDEIconManager.cpp   (+ .h if present)
ncde/NCDEMail.cpp          (+ .h if present)
ncde/NCDEWorkspace.cpp ncde/NCDEWorkspace.h
```
Plus the Qt resource: `lelan.qrc` (and the shaders/ it references).

**NOTE — naming:** the real WM uses `LElan`, `thememanager`, `notificationmanager`+
`notificationadaptor`. The host's stubs `Lelan.h`, `NcdeTheme.h`, `NotificationManager.h`
are the STRIPPED replacements — do **not** mix them in. The host also added
`WindowTyper`, `TrayWatcher`, `ScreenInfo`, `NCDEGeo`, `Theme`, `WidgetData`, `NcdeTheme`,
`NotificationManager` which the real `.bak` does **not** use — verify against the actual
files in the staging tree before including.

---

## THE 30 FILES MISSING FROM LELAN'S CMakeLists

**Partially stale — reconfirmed 2026-06-30 night, even this doc's own same-day (22:59) edit didn't
catch it:** `cursormanager` is NO LONGER missing — `CursorManager.cpp`/`.h` were added to LaPivot's
CMakeLists (comment: "Recreated from the live ncde-wm .bak"). Its `loadCursor()` body is still a TODO
stub (returns hardcoded `QCursor(Qt::ArrowCursor)` for every theme) — so "present in the build" is true,
"fully implemented" is not. The rest of this list was reconfirmed still accurate 2026-06-30 night: the
live `CMakeLists.txt` still does not include `LElan`, `desktopwidget`, `globalmenu`, `NCDEEventFilter`,
`NCDEMenuBridge`, `notificationmanager`+`notificationadaptor`, `thememanager`, or the `ncde/` subdir's
`.cpp` files by these names — it uses the host's stub-named equivalents instead (`Lelan.cpp`+
`Lelan_*.cpp`, `NcdeTheme.h`, etc.). Whole classes the host dropped (status as of 2026-06-30 night,
`cursormanager` struck since it's now present):

~~`cursormanager`~~ (now present, see correction above), `desktopwidget`, `globalmenu`, `LElan`,
`NCDEEventFilter`, `NCDEMenuBridge`, `notificationmanager`+`notificationadaptor`,
`thememanager`, and the entire `ncde/` subdir (`NCDECalendar.cpp`, `NCDEEngine.cpp`,
`NCDEIconManager.cpp`, `NCDEMail.cpp`, `NCDEWorkspace.cpp`).

The `.cpp` halves the host flattened to header-only: `AnimPolicy.cpp`, `AppMenuModel.cpp`,
`GliaSystemMenus.cpp`, `hudmanager.cpp`, `Launcher.cpp`, `LeapFrogPond.cpp`, `Settings.cpp`,
`NCDEWindowManager.cpp`.

---

## THE BUILD CONFIG WE KEEP (from lelan's CMakeLists — it carries the WiFi fix)

```
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick DBus Network)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PULSE      REQUIRED IMPORTED_TARGET libpulse)     # audio
pkg_check_modules(XCB        REQUIRED IMPORTED_TARGET xcb)          # WindowTyper
pkg_check_modules(XCB_SHAPE  REQUIRED IMPORTED_TARGET xcb-shape)    # MotifFrame click-through
pkg_check_modules(XCB_RANDR  REQUIRED IMPORTED_TARGET xcb-randr)    # "real res not found" fix
pkg_check_modules(XCB_XFIXES REQUIRED IMPORTED_TARGET xcb-xfixes)   # hide HW cursor
# link: Qt6::Core Gui Qml Quick DBus Network  PkgConfig::PULSE/XCB/XCB_SHAPE/XCB_RANDR/XCB_XFIXES  crypt
```
(All five xcb/pulse modules confirmed installed: 1.17.0.)

---

## EXECUTION STEPS (for the next agent, with root) — SUPERSEDED 2026-07-17, historical only; the `~/ncde-staging` tree these steps reference is gone

1. **Locate** the operator's 41-file source under `[dead-legacy-tree]/root/...` (sudo find above).
2. **Stage** into a scratch build dir (e.g. `~/ncde-staging/scratch/src/`): copy the real
   source (flat `*.cpp/.h` + `ncde/` subdir) + `lelan.qrc` + `shaders/`. Do NOT include the
   host's stub files (`Lelan.h`, `NcdeTheme.h`, `NotificationManager.h`, `WindowTyper.*`,
   `TrayWatcher.*`) unless the real `.bak` actually uses them — reconcile to the 41-file
   list.
3. **Write the CMakeLists**: take lelan's build config (section above) and set
   `add_executable(ncde-wm <all 41 files, with ncde/ paths>)` + the link libs. Reconcile the
   exact file list against what's actually on disk in the staging tree.
4. **Compile** in scratch (no sudo needed for the compile itself if source is copied to a
   readable scratch; otherwise build as root): `cmake -S src -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j`.
5. **Verify** against the `.bak`: same classes present (`cursormanager`, `desktopwidget`,
   `globalmenu`, `LElan`, `ncde/*`), WiFi symbols present, and it runs.
6. **Install** the new binary as `ncde-wm` (the desktop draws its UI from the 200 QML in
   `[dead-legacy-tree]/usr/share/ncde`, which is unchanged). Keep `.bak`/`.LIVE` as the safety
   reference. Only overwrite `/usr/local/bin/ncde-wm` after verification.

---

## KEY PATHS QUICK-REF — SUPERSEDED 2026-07-17, historical only; none of the `~/ncde-staging` paths below still exist
| what | path |
|---|---|
| live WM (real) | `/usr/local/bin/ncde-wm` |
| .bak (staging) | `[dead-legacy-tree]/usr/local/bin/ncde-wm.prebak` |
| .bak (scratch copy) | `~/ncde-staging/scratch/ncde-wm.prebak` |
| real source | `[dead-legacy-tree]/root/...` (root-protected — locate w/ sudo) |
| desktop QML (200) | `[dead-legacy-tree]/usr/share/ncde/` |
| LaPivot build source (formerly "test host / reconstruction" — that name + the separate test tree are retired) | `~/ncde-staging/compass7/lelan/` (lelan's CMakeLists here) |
| reconstruction in tree (overwrote real) | `[dead-legacy-tree]/src/` (23 stub files) |
