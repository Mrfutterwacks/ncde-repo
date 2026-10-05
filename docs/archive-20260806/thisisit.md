# thisisit.md — THE NCDE-WM REBUILD PLAN (read this right after CLAUDE.md)

**This file is mandatory reading every session, immediately after CLAUDE.md, until the
operator says otherwise.** It is the operator's (Stephen's) own plan. He is the authority
and the living spec. Your job is to EXECUTE it — not re-derive it, not reframe it, not
"improve" it, not re-litigate any fact below. If something here conflicts with an
assumption you're about to make, the doc wins.

---

## 🔴 CURRENT TRUTH (updated 2026-07-17) — SUPERSEDES THE 2026-07-05 SECTION BELOW ON TREE/PATH CLAIMS

**The dev machine that hosted `~/ncde-staging/` is gone.** That whole tree — including
`~/ncde-staging/LaPivot/compass7/lelan/` and every other `~/ncde-staging/...` path in the
2026-07-05 section below — does not exist anymore, on this machine or on the USB backup (checked
both directly, 2026-07-17). The 2026-07-05 section's "`~/ncde-staging/LaPivot/` is THE production
tree — the ONLY tree" claim is no longer true: there is no tree at all now, only the live system.

- **Source of truth now:** the live running system — `/usr/local/bin/LaPivot`, `/usr/share/ncde/`
  — not a staged/buildable tree.
- **Recovery workspace (replaces the old `~/ncde-staging/ncde-wm-rebuild/` path):**
  `~/ncde-wm-rebuild/` — classes reconstructed by Ghidra-decompiling the live LaPivot binary
  (the oracle), not read out of a source tree. Partial; see `docs/lapivot-rebuild.md` for
  per-class status.
- **QML was never lost** — plain text at `/usr/share/ncde/`, unaffected by any of this.
- **Deploy mechanism:** `~/my-project/files/ncde-full-patch-20260711.sh` — every live fix folds
  into this one script.
- Full corrected model: `docs/CLAUDE.md` banner + Hard Constraint 2 + §9-10.

---

## CURRENT TRUTH (updated 2026-07-05, tree/path claims superseded 2026-07-17 above) — SUPERSEDES §2–§8 BELOW WHERE THEY CONFLICT

**LaPivot is the production WM. The old "test vs production" split is dead.**

**`~/ncde-staging/LaPivot/` was THE production tree as of 2026-07-05 — that tree is now gone (see
banner above, 2026-07-17). The separately-dead old frozen backup root tree remains DEAD too
(operator, 2026-07-05: "the old frozen one is dead") and is struck as `[dead-legacy-tree]` below —
history only, never read/grep/diff/build from it either. The live system brands itself "NCDE"
(Identity/Branding rule) but what runs IS LaPivot.**

- **LaPivot** (`/usr/local/bin/LaPivot`) is the one production WM. As of 2026-07-05 you'd build
  from `~/ncde-staging/LaPivot/compass7/lelan/` — that path is gone now; there is no build-from-tree
  step anymore, see the 2026-07-17 banner above. No sudo needed to run the live binary.
- **The old `ncde-wm`** is a backup — never overwrite it.
- **There is no "test host" or "NCDE (test host)" session.** Only LaPivot.
- **There is no "promote to production" step.** What you build IS production.
- **The recovered source** (THE ORACLE) — as of 2026-07-05 this was `~/ncde-staging/ncde-wm-rebuild/src/decompiled/<Class>.c` (153 classes, 9.7M); that path is gone. The current recovery workspace is `~/ncde-wm-rebuild/` (see banner above) — still Ghidra-decompiled from the live LaPivot binary, still partial.
- **§2–§8 below are history for the ARCHITECTURE work only** — Lelan's rebuild (the system-services hub)
  is genuinely done and verified (2,482 real lines, real D-Bus/xcb calls, running). **§7's file
  reconciliation was NOT done** — reconfirmed false twice (2026-06-30 night): the live
  `CMakeLists.txt add_executable(LaPivot ...)` still builds mostly from the HOST's stub file names
  (`Lelan.cpp`+`Lelan_*.cpp`, `NcdeTheme.h`, `WidgetData.h`, `TrayWatcher.*`), not the real 41-file list
  §5 names. `LElan`, `desktopwidget`, `globalmenu`, `NCDEEventFilter`, `thememanager` are absent or
  header-only stubs. Whether this matters is an open operator decision (LaPivot may have deliberately
  diverged and improved past the oracle) — but "that work is done" is false and must not be repeated
  by a future agent as settled fact. Read §2-§8 for context; do not assume §7 was executed.

---

## 0. HOW TO BEHAVE ON THIS TASK (read first — prior agents failed exactly here)

- **Do what the operator says, literally.** When he gives an instruction, execute it.
  Do not substitute your own framing or ask him to repeat himself. He has had to repeat
  himself 10+ times because agents kept theorizing instead of acting.
- **(Superseded 2026-07-17.)** This originally said the source was NOT lost/missing and the
  staging tree was complete, and that non-root searches finding nothing meant a permissions
  wall, not absence — true when written (the staging tree existed then, root-protected). It
  is no longer true: the dev machine hosting `~/ncde-staging/` is gone, confirmed absent on
  this machine and the USB backup, and the original C++ source is genuinely lost — no copy
  exists anywhere checked. Do not tell the operator "it's not lost, just permission-walled."
  That said, this is still not license to casually call something unrecoverable: the real
  current recovery path is Ghidra-decompiling the live LaPivot binary as an oracle,
  reconstructed class-by-class in `~/ncde-wm-rebuild/` — partial, not exhausted. Check
  `docs/lapivot-rebuild.md` for actual per-class status before assuming a class is a dead end.
- **`NCDEEngine` handles COLORS ONLY.** WiFi/NetworkManager/BlueZ/audio/printers/users/
  timezone live in **Lelan**. Never put system/process work in the color engine.
- **Never ship the reconstruction. Never run sudo yourself** (hand him `! sudo …`).
  **Never edit `[dead-legacy-tree]` directly** (stage; he applies). **Never delete project files.**

---

## 1. THE GOAL (one sentence)

Rebuild the operator's **full, real `ncde-wm`** — his complete working desktop, every file
intact — **with the Lelan architecture the test host got right** (NCDEEngine = colors only,
Lelan owns system/process work, **WiFi working**). Same destination the stripped "host"
was reaching for, but on the real desktop with nothing thrown away.

His exact framing: **recompile the `.bak` (the correct ncde-wm) after fixing it, by adding
all of his source files (which are in the staging tree) to lelan's CMakeLists** (the only
CMakeLists we have — and the one that already carries the WiFi fix).

---

## 2. WHAT HAPPENED (so you don't repeat the confusion)

- The operator's real `ncde-wm` is a full Qt6/QML desktop: a C++ engine (`ncde-wm`) that
  **draws** the desktop from QML/assets in the tree.
- An AI built a "test host" (`lelan-host`) by compiling **his** source but **stripping it
  down** to a 23-file, mostly header-only shell. That host did ONE thing right — it
  separated WiFi/system work out of `NCDEEngine` into `Lelan`, and WiFi works.
- The same work **overwrote `[dead-legacy-tree]/src` and the staged `ncde-wm` binary** with the
  stripped reconstruction (a directive violation). His real desktop kept running because
  the **binary** `/usr/local/bin/ncde-wm` was untouched, and a backup `.bak` survived.
- So: keep the host's good separation, restore/rebuild the full desktop, drop the stripped
  reconstruction.

---

## 3. THE FACTS (evidence-backed 2026-06-27 — treat as ground truth)

### Real WM / .bak
- Live: `/usr/local/bin/ncde-wm` — **20,703,136 B**, not stripped, full DWARF,
  `BuildID a6aa1df949…`, `sha256 99c7647137a8475e87c50d9a84593a58aee0a0cd8fdb782a4ef1fdb690b24298`,
  built with GCC 16.1.1 `-g`, **comp_dir `[dead-legacy-tree]/build`**.
- The **`.bak` = the correct ncde-wm that needs fixing** (byte-identical copies):
  - `[dead-legacy-tree]/usr/local/bin/ncde-wm.prebak`  (the one in the staging folder)
  - `~/ncde-staging/ncde-wm-work/ref/ncde-wm.LIVE`
  - `~/ncde-staging/ncde-wm-work/ref/ncde-wm.baseline-20M`
  - working copy already in scratch: `~/ncde-staging/scratch/ncde-wm.prebak`

### The desktop the WM draws (complete, present, editable)
- `[dead-legacy-tree]/usr/share/ncde/` = **200 QML + 45 JS** + assets. This is the desktop UI
  source. Nothing here was stripped. The rebuild does not need to touch it.

### His real WM source (in the staging tree, root-protected)
- The `.bak`'s debug info lists the **41 files** it was built from (see §5).
- They live under the **root-protected** part of the staging tree (e.g. `[dead-legacy-tree]/root`,
  `drwxr-x---`). Non-root `find` => "Permission denied" => you can't see them, but they are
  there. Locate with root:
  ```
  sudo find [dead-legacy-tree]/root -type f \( -name '*.cpp' -o -name '*.h' \) 2>/dev/null \
    | grep -iE 'cursormanager|desktopwidget|LElan|globalmenu|NCDEEventFilter|ncde/'
  sudo find [dead-legacy-tree]/root -type f -name CMakeLists.txt 2>/dev/null
  ```

### The reconstruction (do NOT ship)
- `~/ncde-staging/compass7/lelan/` builds `lelan-host` (~2.3 MB). **23** files, mostly
  header-only stubs. **lelan's CMakeLists is the only CMakeLists we have** and it carries
  the WiFi fix (see §6). The stripped reconstruction also sits in `[dead-legacy-tree]/src/`.

---

## 4. THE HOST'S GOOD CHANGE — KEEP THIS ("architecture A")

- **`NCDEEngine` = colors only:** palette tokens, Motif-derived decoration colors,
  fonts/mode/scalars, color-wheel overrides, 90 Iris Chroma presets, `sampleWallpaper`,
  glass tinting. Its system properties are **pure pass-through**, e.g.
  `wifiEnabled(){ return m_lelan ? m_lelan->wifiEnabled() : false; }` — zero system logic.
- **Lelan owns all system services over D-Bus:** WiFi (NetworkManager:
  `subscribeToWifi` / `rebuildAccessPoints`→`GetAllAccessPoints` / `setWifiEnabled`→
  `WirelessEnabled` / `connectWifi`→`AddAndActivateConnection` / `disconnectWifi`), BlueZ,
  VPN, audio (libpulse), UPower, UDisks2, power-profiles, users, printers, timezone, tray
  (SNI), MPRIS.
- **Seam:** `NCDEEngine::setLelan(Lelan*)` stores the pointer and connects Lelan's change
  signals → NCDEEngine notify signals. Flow: **Lelan owns service → emit → NCDEEngine
  re-emit → QML rebinds.**

---

## 5. THE 41 FILES THE REAL ncde-wm USES (authoritative, from the .bak's debug info)

Flat in `src/`:
```
main.cpp
LElan.cpp  LElan.h                  (capital-E — the REAL Lelan; NOT the host's Lelan.h stub)
cursormanager.cpp  cursormanager.h
desktopwidget.cpp  desktopwidget.h
globalmenu.cpp  globalmenu.h
NCDEEventFilter.cpp  NCDEEventFilter.h
NCDEMenuBridge.cpp                   (+ .h if present on disk)
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
Plus `lelan.qrc` + its `shaders/`.

**Naming traps:** the real WM uses `LElan`, `thememanager`, `notificationmanager`+
`notificationadaptor`. The host's `Lelan.h`, `NcdeTheme.h`, `NotificationManager.h` are the
STRIPPED replacements — don't mix them in. The host also added `WindowTyper`, `TrayWatcher`,
`ScreenInfo`, `NCDEGeo`, `Theme`, `WidgetData` which the real `.bak` does **not** use.
**Always reconcile this list against the actual files found in the staging tree (§3) before
finalizing the CMakeLists.**

---

## 6. THE BUILD CONFIG TO KEEP (from lelan's CMakeLists — carries the WiFi fix)

```cmake
cmake_minimum_required(VERSION 3.16)
project(ncde-wm LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick DBus Network)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PULSE      REQUIRED IMPORTED_TARGET libpulse)
pkg_check_modules(XCB        REQUIRED IMPORTED_TARGET xcb)
pkg_check_modules(XCB_SHAPE  REQUIRED IMPORTED_TARGET xcb-shape)   # MotifFrame click-through
pkg_check_modules(XCB_RANDR  REQUIRED IMPORTED_TARGET xcb-randr)   # "real res not found" fix
pkg_check_modules(XCB_XFIXES REQUIRED IMPORTED_TARGET xcb-xfixes)  # hide HW cursor

add_executable(ncde-wm
    # ← ALL 41 files from §5 here, with the ncde/ paths
)
target_link_libraries(ncde-wm PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::DBus Qt6::Network
    PkgConfig::PULSE PkgConfig::XCB PkgConfig::XCB_SHAPE PkgConfig::XCB_RANDR PkgConfig::XCB_XFIXES
    crypt)
```
(libpulse + all four xcb modules confirmed installed, 1.17.0.)

---

## 7. EXECUTION STEPS

1. **Locate** the operator's 41-file source under `[dead-legacy-tree]/root/...` (sudo find, §3).
2. **Stage** to a readable scratch build dir (e.g. `~/ncde-staging/scratch/src/`): the real
   `src/*.cpp/.h` + `src/ncde/` + `lelan.qrc` + `shaders/`. Exclude host stubs (`Lelan.h`,
   `NcdeTheme.h`, `NotificationManager.h`, `WindowTyper.*`, `TrayWatcher.*`) unless the
   `.bak` actually uses them. Copying out as root makes the source readable for a normal
   compile.
3. **Write the CMakeLists** (§6) with the full 41-file `add_executable`. Reconcile names to
   what's actually on disk.
4. **Compile:** `cmake -S src -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j$(nproc)`.
   (Do not `rm -rf` project dirs — use a fresh build dir or let cmake reconfigure.)
5. **Verify vs the `.bak`:** classes present (`cursormanager`, `desktopwidget`, `globalmenu`,
   `LElan`, `ncde/*`), WiFi symbols present, and it runs nested/safely.
6. **Install** as `ncde-wm` only after verification (desktop QML in `[dead-legacy-tree]/usr/share/ncde`
   is unchanged). Keep `.bak`/`.LIVE` as the safety reference. The live
   `/usr/local/bin/ncde-wm` is overwritten only on the operator's go.

---

## 8. KEY PATHS
| what | path |
|---|---|
| live WM (real) | `/usr/local/bin/ncde-wm` |
| .bak (staging folder) | `[dead-legacy-tree]/usr/local/bin/ncde-wm.prebak` |
| .bak (scratch copy) | `~/ncde-staging/scratch/ncde-wm.prebak` |
| real 41-file source | `[dead-legacy-tree]/root/...` (root-protected — sudo to read) |
| desktop QML/JS (200/45) | `[dead-legacy-tree]/usr/share/ncde/` |
| test host + lelan CMakeLists | `~/ncde-staging/compass7/lelan/` |
| reconstruction that overwrote src | `[dead-legacy-tree]/src/` (23 stub files) |

Supporting detail also in `NCDE-WM-REBUILD-PLAN.md` (same findings). Memory:
`real-ncde-wm-is-live-binary` in the auto-memory index.
