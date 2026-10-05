# Report — group "colour" (NCDEEngine, NcdeTheme, Theme, ColorMath)

Status: IN PROGRESS (relaunched 2026-09-30 evening). Updated incrementally.

## Log
- started: read preamble, colour.txt, AGENT-BRIEF.md, digest §1-§5, README resume/work list.
- Iris palettes in source (extra item b): transforms found = files/full-patch-20260711/notes/apply-iris.py
  (iris-palettes.json, 930 slots), apply-iris-contrast.py (iris-contrast-fix.json, 25 accents),
  apply-iris-widen.py (iris-accent-widen-fix.json, 7 accents), chained by deploy_lapivot() in
  files/ncde-full-patch-20260711.sh:367. Measured: raw staged LaPivot + the 3 scripts (run into scratch)
  -> sha256 3507b4c6… == live /usr/local/bin/LaPivot == oracle/LaPivot.oracle (the oracle IS the patched binary).
  src/NCDEEngine_presets.inc (first run) verified: tests/colour_presets_test.py ALL PASS (raw+3 transforms
  semantically == inc, live == inc, 0 differing fields; mutation #ad7c22->#af7e22 => FAIL).

## Third launch (2026-10-01 morning) — log
- Read preamble, colour.txt, AGENT-BRIEF, digest §1-§5, gtk.md, gtk-designer-answers.md, filigree-phase1.
- Found: main() constructs NCDEEngine (context "ncde") and Theme (context "theme"); NcdeTheme is NEVER
  constructed in LaPivot (only its own file references NcdeTheme::NcdeTheme) — dead class in this binary.
- QML still using NCDEEngine system forwarders (KEEP, list for owners): UsersTab.qml:15,151,233,239,329,363,375,434
  (users/addUser/removeUser/changePassword/setUserAvatar/setUserAdmin/setAutoLogin(name,bool));
  MagpieTalker.qml:148-149 (setUserAvatar); PrintersTab.qml:13,121,213 (printers/removePrinter/setDefaultPrinter);
  DateTimeTab.qml:93-96,117,146,167 (detectedZone/Region/Offset/TzName, refreshLocation, setTimezone, setNtp).
- QML using NO-LONGER-EXISTING ncde members (dead bindings, not in oracle NCDEEngine either): FontsPanel.qml
  (uiFont/uiFontSize/uiScale/titleFontSize/smallFont/smallFontSize/setUiFont/setSmallFont) — checking whether loaded.

## FOURTH launch (2026-10-01 ~12:30) — log
- started: read _relaunch-preamble.txt, colour.txt, AGENT-BRIEF.md, RELEASE-GATE.md (stage 1-2 only: build +
  stage, never install), README.md RESUME + work list, and the stub above.
- Recovery check per preamble: `find src tests l2-stage -newermt '2026-09-30 18:50'` shows the ONLY colour-owned
  artefacts are src/NCDEEngine_presets.inc (18:55), tests/colour_extract_presets.py, tests/colour_presets_test.py.
  Nothing else (src/NCDEEngine*.{h,cpp}, NcdeTheme*, Theme*, ColorMath*, tests/colour_*.sh) exists => the two
  dead runs did NOT write any colour engine source. ALL of it must be rebuilt from scratch here.
  The stub's claims are UNVERIFIED until re-measured (see per-class log).
