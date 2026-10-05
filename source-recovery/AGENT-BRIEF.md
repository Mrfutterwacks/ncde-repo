# AGENT BRIEF — LaPivot source rebuild (read ALL of this before touching anything)

You are one of several agents rebuilding NCDE's desktop shell binary **LaPivot** from its decompile into real,
correct C++ source, in parallel (relaunched 2026-09-30 evening after the first launch was cut off by a session limit). The operator (NCDE's designer) wants LaPivot finished today and
has been burned by agents that claimed things were done when they were not. Follow this exactly.

## Where things are (all on the USB stick NCDE-BACKUP — never only in ~)
- Workspace: `/run/media/stephen/NCDE-BACKUP/my-project/source-recovery/LaPivot/`
  - `oracle/LaPivot.oracle` — the original binary (the "oracle"). `nm -C`, `objdump -d` work on it.
  - `decomp/<Class>.c` — Ghidra decompile per class; nested lambdas are in `decomp/const.c`; global/shared
    functions in `decomp/_global.c`, `decomp/_anonymous_namespace_.c`.
  - `interfaces/LaPivot-metaobjects.h` — the EXACT Qt interface of every QObject class (props, signals, slots,
    invokables) dumped from the oracle's own moc data. QML binds to these names: they must be preserved.
  - `tools/gen_header.py <Class>` — emits the class's Q_OBJECT interface block from that file.
  - `src/` — rebuilt source. `tests/` — tests. `tests/iface_check.sh <Class>` checks the oracle interface is
    preserved; declared additions go in `tests/iface_additions/<Class>.txt` (see Lelan.txt for the format).
  - Existing rebuilt code to imitate (style, comments, defect lists, tests): `src/Lelan_*.cpp`, `src/Settings_*.cpp`,
    `src/AnimPolicy.cpp`, `src/ZenGovernor.cpp`, `src/IdlePolicy.*`; tests `tests/*_test.sh`, `tests/*_qml_host.cpp`.
  - Helpers (read-only use): `/run/media/stephen/NCDE-BACKUP/my-project/source-recovery/LaPivot/tools/bin/fn`
    (print a decomp function), `.../bin/fnc` (same, noise stripped), `.../bin/sig` (essentials: strings, fields,
    calls). Usage: `fn 'Class::method' /path/to/decomp/Class.c`.
- The live QML shell (what LaPivot loads) — the CANONICAL copy you may edit:
  `/run/media/stephen/NCDE-BACKUP/my-project/files/full-patch-20260711/src/usr/share/ncde/`
- The operator's design docs (THE SPEC): `/run/media/stephen/NCDE-BACKUP/my-project/docs/` — start with
  `NCDE-ARCHITECTURE-DIGEST.md` §2 (per-class purpose table) and read your classes' own docs (e.g. gtk.md,
  gtk-designer-answers.md, filigree-phase1-20260720.md for the colour engine; ncde-architecture.md; lelan.md;
  anim-policy.md; zen.md; ncde-efficiency.md). `grep -il <Class> docs/*.md` to find them.
- Progress log + work list: `source-recovery/README.md` (read the RESUME HERE block and the Work list; do NOT edit
  README — report to the coordinator instead).

## The operator's rules (non-negotiable)
1. **Docs are the spec. The oracle is a reference, never a target.** Anything that doesn't do what the docs / the
   QML consumer promise is a DEFECT. Fix every flaw you find in the same round — including in QML consumers — never
   park one as "not displayed", "pre-existing", "known open", "keeps oracle behaviour". ("why are we keeping bugs?")
2. **Never claim "built / wired / works / done" without measured proof** (a test you ran, observed output,
   numbers). Report status as measured behaviour. Parity with the oracle is worthless if the product is wrong.
3. **Read the digest §2 before judging any class.** NCDEEngine = colour/theme engine ONLY (Filigree -> Iris Chroma ->
   NCDEKit -> NCDEEngine::recompute() -> GTK/Chromium bridge). No system data in NCDEEngine.
4. **HANDS OFF ncde-portal** (login/greeter/lock screen): never rebuild, patch, install, restart or edit it or its
   files. Lelan's xdg-portal read is oracle-exact.
5. **Never touch the live system** unless your assignment says so: do not install anything, do not edit
   /usr, /etc, ~/.config/ncde, do not restart LaPivot or services, do not sudo. Work only on the USB tree.
6. **Test safety** (learned the hard way today):
   - Tests never change the operator's live state. Record commands instead of running them (see
     `Settings::runDetached` pattern), use scratch `HOME=$(mktemp -d)`, offscreen Qt (`QT_QPA_PLATFORM=offscreen`).
   - Read-only queries of the real system are fine (xrandr --query, xinput list, busctl get-property, ...).
   - No audio tests (the operator is listening). Media tests use fake MPRIS players only — never command Spotify.
   - Nothing network-facing that could drop Wi-Fi. No real Bluetooth pairing. No suspend/lock/logout.
   - Never `kill 0` / `kill ${VAR:-0}`; never `pkill -f <pattern>` that can match your own shell. Always verify
     cleanup (no leftover processes, loop devices, mounts, temp dirs you created).
   - A child you start must not outlive the test (use `exec` in stand-in scripts).
7. **The shell is zsh** — `for f in $var` does not word-split. Use `bash -c '...'`, a script file, or Python.
   zsh also aborts a whole command on an unmatched glob (`rm $W/*.moc` with no match does nothing).
8. **QML art:** decorative art must never overlap other elements; frames hug; verify by measuring a sandbox render,
   not by eye. Operator screen 1920x1200.
9. Any shell command you hand to the operator must be self-contained with absolute paths (no `$VAR` from a prior
   line). You shouldn't need to hand any.

## Method (per class)
1. Read the digest row + the class's docs + every QML consumer (`grep -rn '<contextName>\.' .../usr/share/ncde/*.qml`)
   — context names: lelan, ncde (NCDEEngine), settings, theme, fontMgr, widget_data, animPolicy, launcher,
   notifications, windowMgr, calBackend, ncdeWorkspace, appMenuModel, window, pond, gliaSystem, geo, hudManager.
2. Generate the interface: `python3 tools/gen_header.py <Class>`; build `src/<Class>.h` around it (private members
   from the decompile's field offsets / constructor). Keep the oracle interface exactly; additions go in a clearly
   commented block AND in `tests/iface_additions/<Class>.txt`.
3. Rebuild each function from the decompile (use sig/fnc for the essentials, read the full decomp where logic
   matters). Split big classes into `src/<Class>_<area>.cpp`. Header comment per file: "Rebuilt from oracle: ...",
   "Spec: ...", "DEFECTS FIXED vs oracle:" numbered list (see Lelan_storage.cpp / Settings_display.cpp).
4. Look actively for defects: blocking calls on the GUI thread (waitForFinished, synchronous D-Bus), signals never
   emitted / emitted without change checks, polling where events exist (anim-policy.md §4.4: no repeating timers
   that run forever — gate on visibility/animPolicy or use events), settings stored but never applied, QML calling
   methods that don't exist / bindings to props that don't exist, races, leaks, wrong units, hardcoded paths/user.
5. Tests: write `tests/<class>_test.cpp` + `.sh` (build with a copy of `tests/lelan_test_build.sh` adapted to your
   classes — it moc's headers, links your sources and a `ud2` trap stub for everything not linked). Test real
   behaviour against the spec; include at least one mutation check for important fixes (remove the fix -> test fails).
   For QML-facing classes, render the real QML offscreen with your rebuilt object (see tests/storage_qml_host.cpp,
   tests/display_qml_host.cpp) and look at the screenshots.
6. Compile your own files with `-Wall -Wextra` to 0 warnings. At the end run `bash tests/compile_all.sh` — if a
   file you do NOT own fails (another agent mid-work), just report it; do not touch it.
7. `bash tests/iface_check.sh <Class>` must print ORACLE INTERFACE PRESERVED (+ your declared additions).

## File ownership (parallel agents — avoid collisions)
- Only create/edit the src/test files of YOUR assigned classes (names listed in your assignment), your own
  `tests/iface_additions/<Class>.txt`, and your own report. Do not edit `src/Lelan.h`, `src/Settings.h` or other
  agents' files; if you need something from them, say so in your report (exact declaration wanted).
- QML: edit only the QML files your assignment lists (or that ONLY your classes' context object uses). Before
  editing a QML file, copy it to `<file>.prebak-20260930-<yourgroup>` next to it (once). Verify with qmllint and an
  offscreen render.
- `tests/compile_all.sh`, `tests/lelan_test_build.sh`, `tools/*` — do not modify; copy and adapt.

## Your report (the deliverable)
Write `source-recovery/reports/<group>.md` and make your final message a short summary of it:
- per class: functions rebuilt (count vs oracle count), files, DEFECTS FIXED (numbered, one line each, with the
  evidence), tests run + results (paste the PASS/FAIL lines), iface_check line, compile warnings.
- QML files changed (+ prebak names) and why.
- Anything NOT done, anything you need from another class (exact declaration), anything that needs the operator
  (live tests owed). Be precise; never round up.
