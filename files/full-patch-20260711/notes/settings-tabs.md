# Settings-tab QML fixes — full-patch-20260711

Source audit: `Audit-Settings-panel-23-tabs` (2026-07-11). Only items the audit marks
**LIVE-FIXABLE pure-QML** are patched. Staged under
`~/my-project/files/full-patch-20260711/src/usr/share/ncde/` — the live system was
**not** touched (read-only). Staged copies were byte-verified identical to live
before editing (`diff -q` → SAME for all).

## Verification method (binding)

qmllint alone is NOT trusted (documented failure: a qmllint-clean file died at
runtime on `font.pixelSize: 12.5`). Instead, an **offscreen runtime load test**
was run with the system's Qt 6.11.1 runtime (`/usr/lib/qt6/bin/qml`,
`QT_QPA_PLATFORM=offscreen`, `QT_ASSUME_STDERR_HAS_CONSOLE=1`):

- Harness: `scratchpad/qml-harness/TabLoadHarness.qml` + `FuncDriver.qml`.
  Each tab is compiled with `Qt.createComponent` and instantiated with
  `createObject` inside a context that stubs every context property the tabs
  resolve unqualified: `ncde`, `settings`, `launcher`, `notifications`, `lelan`
  (grep-derived per file). `fontMgr` is deliberately absent to exercise
  FonderieTab's `typeof` guards. Sibling types (`SetTheme` singleton via
  `qmldir`, `NCDEToggle`, `NCDESlider`, `SetSegment`, `NCDEScrollBar`,
  `SettingsColorWheel`) resolve through a directory of symlinks to
  `/usr/share/ncde/` with the 8 patched files overlaid.
- **Baseline first**: the identical harness was run against the pristine live
  files → `RESULT: ALL 8 TABS PASS`. Then against the patched files →
  `RESULT: ALL 8 TABS PASS`, exit code 0. Normalized stderr diff between the two
  runs shows **zero new warnings** (only a pre-existing NetworkTab Row-anchor
  warning shifts line number 168→173 because a comment block was added above it).

Load-test output (patched run):

```
qml: PASS: AccessibilityTab.qml
qml: PASS: PowerTab.qml
qml: PASS: UsersTab.qml
qml: PASS: NetworkTab.qml
qml: PASS: WallpapersTab.qml
qml: PASS: PrintersTab.qml
qml: PASS: SessionTab.qml
qml: PASS: FonderieTab.qml
qml: RESULT: ALL 8 TABS PASS
PATCHED EXIT CODE: 0
```

Functional driver output (patched run, `FuncDriver.qml` — instantiates each tab,
calls new plumbing directly, and walks the rendered item tree):

```
qml: OK   | WallpapersTab instantiates
qml: OK   | WallpapersTab.savePrefs() calls settings.saveWallpaperPrefs()
qml: OK   | FonderieTab instantiates
qml:      mono specimen is now: "ncde@poseidon ~ $ ls -la ~/Documents"
qml: OK   | mono specimen has no 'stephen'
qml: OK   | mono specimen has no 'pearOS'
qml: OK   | mono specimen is NCDE-branded
qml: OK   | AccessibilityTab instantiates
qml: OK   | 'MOTION' heading present
qml: OK   | 'KEYBOARD' heading gone
qml: OK   | PowerTab instantiates
qml: OK   | cosmetic-dropdown caption present
qml: OK   | NetworkTab instantiates
qml: OK   | '+ Add VPN…' exists in tree but hidden
qml: OK   | VPN 'Edit…' exists in tree but hidden
qml: OK   | 'NetworkManager'/'nmtui' user copy gone
qml: OK   | PrintersTab instantiates
qml: OK   | 'CUPS' user copy gone
qml: OK   | new printer-manager copy present
qml: OK   | SessionTab instantiates
qml: OK   | autostart command rendered
qml: OK   | command field is editable (TextInput)
qml: OK   | empty-command placeholder shown
qml: OK   | UsersTab instantiates
qml: FUNC RESULT: ALL CHECKS PASS
FUNC EXIT CODE: 0
```

Backend symbols re-proven against the live binary before wiring:

```
$ nm -C /usr/local/bin/LaPivot | grep -E 'changePassword|addUser|saveWallpaperPrefs'
NCDEEngine::changePassword(QString const&, QString const&)
NCDEEngine::addUser(QString const&, QString const&, bool)      ← no password param
Settings::saveWallpaperPrefs()                                  ← existed, never called
```

**What was NOT verified:** actual end-to-end behavior against the real backend
(real `ncde`/`settings` objects) — the harness uses stubs, and TapHandler taps
cannot be synthesized in it, so the UsersTab Create-Account handler body was
verified by compile+instantiate+symbol-proof, not by a simulated click. A live
smoke test after deploy (below, per fix) is still required.

## Deploy (operator, per file — requires sudo, NOT run by this session)

```
sudo cp -n /usr/share/ncde/<F>.qml /usr/share/ncde/<F>.qml.prebak-20260711-settingstabs
sudo cp ~/my-project/files/full-patch-20260711/src/usr/share/ncde/<F>.qml /usr/share/ncde/<F>.qml
```

Files: `UsersTab.qml WallpapersTab.qml AccessibilityTab.qml FonderieTab.qml
NetworkTab.qml PowerTab.qml PrintersTab.qml SessionTab.qml`

**Reload step:** log out and back in (the compositor process loads these QML
files once per session; Qt's QML disk cache auto-invalidates on file change, no
manual cache clearing needed). FonderieTab additionally requires reopening NCDE
Command.

---

## Fix 1 — UsersTab.qml: Add-User password silently discarded (audit #2, Tier 1)

**Defect:** `addUser(name, display, isAdmin)` has no password parameter (binary
signature confirmed). The Add-User form collected `newPassword` and threw it
away — new accounts were created passwordless and could not log in. The backend
call `ncde.changePassword(name, pwd)` already exists and is already used by this
same file's PASSWORD section (line 427).

**Diff:**

```diff
@@ -229,8 +229,15 @@
                         TapHandler {
                             onTapped: {
-                                if(ut.newName.trim() !== "" && typeof ncde.addUser==="function")
+                                if(ut.newName.trim() !== "" && typeof ncde.addUser==="function") {
                                     ncde.addUser(ut.newName.trim(), ut.newDisplay.trim(), ut.newIsAdmin)
+                                    // addUser(name, display, isAdmin) takes no password — the typed
+                                    // password was silently discarded and the new account had none.
+                                    // Set it through the same changePassword backend the PASSWORD
+                                    // section below already uses.
+                                    if(ut.newPassword !== "" && typeof ncde.changePassword==="function")
+                                        ncde.changePassword(ut.newName.trim(), ut.newPassword)
+                                }
                                 ut.addUserMode = false
                             }
                         }
```

**Verification:** offscreen load PASS (baseline-identical); symbols
`NCDEEngine::addUser(QString,QString,bool)` and
`NCDEEngine::changePassword(QString,QString)` proven in binary (nm output above).
Handler tap itself not synthesizable in harness — live smoke: create a user with
a password, log out, log in as that user.
**Deploy:** `/usr/share/ncde/UsersTab.qml` + relog.

## Fix 2 — WallpapersTab.qml: slideshow/fit never persisted + tap log spam (audit #8, #15)

**Defect:** `slideshowEnabled` / `slideshowInterval` / `fitMode` writes had no
save call — settings reverted on relog. `Settings::saveWallpaperPrefs()` exists
in the binary and was never called from any QML. Also the only `console.log` in
any tab fired on every gallery tap (journal spam).

**Diff (4 hunks):**

```diff
@@ -28,6 +28,10 @@
         liftedIndex = -1   // cover settles back into the carousel after Apply
     }
 
+    // Slideshow / fit-mode writes previously persisted nothing across relog —
+    // Settings::saveWallpaperPrefs() exists in the backend but was never called.
+    function savePrefs() { if (typeof settings.saveWallpaperPrefs === "function") settings.saveWallpaperPrefs() }
+
     Timer {
@@ -292,7 +296,7 @@
                         onTapped: {
-                            console.log("WP onTapped tapCount=" + tapCount + " index=" + index)
+                            // (debug console.log removed — fired on every gallery tap, journal spam)
@@ -519,7 +523,7 @@
-            onToggled: function(v) { settings.slideshowEnabled = v }
+            onToggled: function(v) { settings.slideshowEnabled = v; wp.savePrefs() }
@@ -532,7 +536,7 @@
-            onMoved: function(v) { settings.slideshowInterval = Math.round(v) }
+            onMoved: function(v) { settings.slideshowInterval = Math.round(v); wp.savePrefs() }
@@ -557,7 +561,7 @@
-            onChose: function(i) { settings.fitMode = ["fill","fit","center","tile"][i] }
+            onChose: function(i) { settings.fitMode = ["fill","fit","center","tile"][i]; wp.savePrefs() }
```

**Verification:** offscreen load PASS; `FuncDriver` called `wp.savePrefs()`
directly on the instantiated tab and the stub `settings.saveWallpaperPrefs()`
fired (OK line above). Live smoke: toggle slideshow, relog, confirm it stays on.
**Deploy:** `/usr/share/ncde/WallpapersTab.qml` + relog.

## Fix 3 — AccessibilityTab.qml: "Reduce motion" under a "KEYBOARD" header (audit #11)

**Defect:** section header said KEYBOARD; the only control in the section is
Reduce motion, and the tab has no keyboard controls at all.

**Diff:**

```diff
@@ -43,7 +43,7 @@
-            Text { text:"KEYBOARD"; color:ac.k.gilt1; font.family:ac.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
+            Text { text:"MOTION"; color:ac.k.gilt1; font.family:ac.k.display; font.bold:true; font.pixelSize:k.sm; font.letterSpacing:2 }
```

**Verification:** offscreen load PASS; item-tree walk finds "MOTION", finds no
"KEYBOARD".
**Deploy:** `/usr/share/ncde/AccessibilityTab.qml` + relog.

## Fix 4 — FonderieTab.qml: identity/foreign-OS leak in mono specimen (audit #12)

**Defect:** mono pangram `stephen@pearOS ~ $ ls -la /atelier` leaked the
operator's name and a foreign OS name to every user previewing a monospace font
(branding rule).

**Diff:**

```diff
@@ -50,7 +50,7 @@
-        mono:"stephen@pearOS ~ $ ls -la /atelier",
+        mono:"ncde@poseidon ~ $ ls -la ~/Documents",
```

**Verification:** offscreen load PASS; `obj.pangram("mono")` on the instantiated
tab returned `ncde@poseidon ~ $ ls -la ~/Documents` (no "stephen", no "pearOS").
**Deploy:** `/usr/share/ncde/FonderieTab.qml` + relog (tab lives in NCDE
Command, `NCDECommand.qml:1272`).

## Fix 5 — NetworkTab.qml: dead nmtui buttons + copy leak (audit #4)

**Defect:** "+ Add VPN…" and VPN "Edit…" ran `launcher.systemCommand("nmtui")` —
a curses app detached with no terminal exits instantly, so both buttons did
nothing. Ethernet copy also named "NetworkManager (nmtui)" (branding rule).
The audit's minimal option (`ncde-terminal -e nmtui`) was checked and is **not
viable**: `strings`/`nm` on `/usr/local/bin/ncde-terminal` show no `-e` literal
and no command-argument handling — so the audit's sanctioned alternative
(hide + reword) was applied. Buttons are hidden (`visible: false`, code kept),
not deleted; a native VPN flow remains C++ work.

**Diff (3 hunks):**

```diff
@@ -113,13 +113,18 @@
-        // Add VPN button
+        // Add VPN button — hidden: it ran `nmtui` via QProcess::startDetached, and a
+        // curses app detached with no terminal exits instantly (dead button that would
+        // also surface a foreign tool). ncde-terminal takes no command argument
+        // (verified: no -e/exec handling in the binary), so a native VPN-import flow
+        // is C++ work; until then the entry point is withheld rather than left dead.
         Item {
             id: addVpnRow
             anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
-            anchors.margins: 6; height: 32
+            anchors.margins: 6; height: 0
 
             Rectangle {
+                visible: false
                 width: parent.width; height: 28; radius: 4; anchors.verticalCenter: parent.verticalCenter
@@ -418,7 +423,7 @@
-                Text { text: "No configuration required for wired connections. Use NetworkManager (nmtui) for advanced settings."
+                Text { text: "No configuration required for wired connections."
@@ -485,6 +490,9 @@
                     Rectangle {
+                        // Hidden for the same reason as "+ Add VPN…": the detached nmtui
+                        // launch does nothing visible (no terminal), so the button was dead.
+                        visible: false
                         width: 70; height: 30; radius: 4
                         ...  (VPN "Edit…" button)
```

**Verification:** offscreen load PASS; item-tree walk confirms both button texts
still exist in the tree but their parents are `visible === false`, and no
"NetworkManager"/"nmtui" string remains in any rendered text.
**Deploy:** `/usr/share/ncde/NetworkTab.qml` + relog.

## Fix 6 — PowerTab.qml: cosmetic lid/power dropdowns caption (audit #7)

**Defect:** `settings.lidAction` / `powerButtonAction` persist but nothing reads
them (punchlist: "Settings>Power dropdowns now cosmetic"; enforcement needs the
logind-inhibitor C++ task). User sets "When lid closes: Nothing", lid still
suspends — the UI silently lied. Audit options: hide or caption honestly;
captioned (less destructive, values still persist for when C++ lands).

**Diff:**

```diff
@@ -103,6 +103,14 @@
                     onChose: function(i) { settings.powerButtonAction = pw.pwrOpts[i]; pw.save() }
                 }
             }
+            // Honest caption: lidAction/powerButtonAction persist but nothing enforces them
+            // yet (needs the inhibitor-lock C++ task) — without this note the dropdowns
+            // silently lie ("Nothing" set, lid still suspends).
+            Text {
+                width: parent.width; wrapMode: Text.WordWrap
+                text: "Lid and power-button choices are saved, but this release still follows the system's built-in behaviour for them."
+                color: pw.k.inkSoft; font.family: pw.k.fell; font.italic: true; font.pixelSize: k.sm
+            }
             Item { width: parent.width; height: 30
```

**Verification:** offscreen load PASS; item-tree walk finds the caption text.
**Deploy:** `/usr/share/ncde/PowerTab.qml` + relog.

## Fix 7 — PrintersTab.qml: CUPS copy leak (audit #1, cosmetic part only)

**Defect:** empty-state copy literally said *"Click "+" to open the CUPS printer
manager."* — foreign-tool name surfaced to the user. The native add-printer flow
is C++-locked (no `addPrinter`/`discoverPrinters` symbols), so per the audit only
the copy is fixable in QML; the button behavior (opens the web admin page) is
unchanged but the copy is now honest about what happens.

**Diff:**

```diff
@@ -139,7 +139,7 @@
-                   text: "Click \"+\" to open the CUPS printer manager."; ...
+                   text: "Click \"+\" to open the printer manager in your browser. You may be asked for an administrator name and password."; ...
```

**Verification:** offscreen load PASS; item-tree walk finds no "CUPS" and finds
the new copy.
**Deploy:** `/usr/share/ncde/PrintersTab.qml` + relog.

## Fix 8 — SessionTab.qml: autostart rows uneditable (audit #9, first half)

**Defect:** "+ Add a program" appended `{name:"New Program", command:"",
enabled:true}` but the delegate rendered name/command as read-only `Text` — the
entry's command could never be typed in, so it autostarted nothing and could
only be deleted.

**Diff:**

```diff
@@ -51,8 +51,19 @@
                             Column { anchors.verticalCenter: parent.verticalCenter
-                                Text { text: model.name; color:ss.k.ink; font.family:ss.k.serif; font.pixelSize:k.lg; font.bold:true }
-                                Text { text: model.command; color:ss.k.inkSoft; font.family:ss.k.mono; font.pixelSize:k.sm } } }
+                                // Was read-only Text — "+ Add a program" appended an entry whose
+                                // command could never be typed in, so it autostarted nothing.
+                                // Inline TextInputs, written back to the model + saved on edit end.
+                                TextInput { width: 320; clip: true; selectByMouse: true
+                                    text: model.name; color:ss.k.ink; font.family:ss.k.serif; font.pixelSize:k.lg; font.bold:true
+                                    onEditingFinished: if (text !== model.name) { autostartModel.setProperty(index,"name",text); ss.saveAutostart() } }
+                                TextInput { id: cmdIn; width: 320; clip: true; selectByMouse: true
+                                    text: model.command; color:ss.k.inkSoft; font.family:ss.k.mono; font.pixelSize:k.sm
+                                    onEditingFinished: if (text !== model.command) { autostartModel.setProperty(index,"command",text); ss.saveAutostart() }
+                                    Text { anchors.fill: parent; verticalAlignment: Text.AlignVCenter
+                                        text: "click to type the command to run"
+                                        color:ss.k.inkSoft; opacity: 0.6; font.family:ss.k.fell; font.italic:true; font.pixelSize:k.sm
+                                        visible: cmdIn.text === "" && !cmdIn.activeFocus } } } }
```

**Verification:** offscreen load PASS; item-tree walk confirms the command
renders through a live `TextInput` (`readOnly === false`, has `editingFinished`)
and the empty-command placeholder appears for a blank entry. Live smoke: add a
program, type a command, relog, confirm it persists and runs.
**Note:** the second half of audit #9 (single-option Default Applications
dropdowns) was NOT changed — see skipped items.
**Deploy:** `/usr/share/ncde/SessionTab.qml` + relog.

---

## Skipped (with reasons)

- **AboutTab hardware grid (audit #3)** — needs C++ (properties don't exist in
  binary); brief explicitly excludes hardware-info.
- **SoundTab mic level meter (audit #5)** — needs C++ (libpulse feed); brief
  explicitly excludes.
- **BluetoothTab scan/pair (audit #6)** — C++-locked per punchlist; audit itself
  says display-fix "needs a live check".
- **NetworkTab Ethernet wrong-signal "Connected" (audit #10)** — audit: only
  partially fixable in QML (backend exposes no per-type interface state); hiding
  the whole Ethernet panel is a product decision, left for the C++ `type` field.
- **SessionTab Default Applications single-option dropdowns (audit #9b)** —
  adding options requires knowing which alternative apps are actually installed;
  inventing entries would create broken defaults. Needs an operator-supplied
  app list or a C++ enumerator.
- **FirewallTab (audit #13)** — orphaned/parked, out of scope per brief.
- **FontsTab (audit #14)** — retired, out of scope per brief.
- **DisplayTab (#16), DockAppsTab (#18)** — tagged [VERIFY] by the audit.
- **DateTimeTab 9-zone picker (#17)** — tagged polish.
- **PrintersTab native add flow (#1)** — C++-locked; only the copy was fixable.
