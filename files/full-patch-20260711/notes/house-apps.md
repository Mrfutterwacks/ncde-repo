# House-apps fix crew — notes (2026-07-11)

Source of findings: scratchpad `dives/Audit-house-apps.md` (audit of all house apps, offscreen-launch-verified).
Scope split honored: MotifFrame.qml (audit #1) and all Settings tabs (incl. FiligreeTab) belong to other crews — untouched here.
Nothing live was modified. All changes staged under `src/` mirroring absolute paths.

---

## FIX 1 — verdantfolio: "Save & Send → Hummingbird" dead hardcoded path (audit #2)

**Defect.** `/usr/lib/ncde/verdantfolio/verdant_server.py:90` hardcoded the old dev-machine path
`/home/stephen/ncde-x11/usr/local/bin/hummingbird-courier`, which does not exist (`~/ncde-x11/` has only `src/`).
The `os.path.exists` guard therefore always failed and the /send flow silently fell through to
"your email is composed and ready to send" — Hummingbird never opened. Real binary: `/usr/local/bin/hummingbird-courier`
(verified present, `-rwxr-xr-x`).

**Also corrected in the same hunk (audit #2 "compounding"):**
- Added `--compose` — a real flag in the binary (`strings`: `--compose --subject --body --attach` are HB's full
  compose vocabulary).
- `--to` is NOT understood by the shipped binary. Proven two ways:
  (a) moc metadata: `ComposeRequest` properties are exactly `pending, subject, body, attachPath` — no recipient;
  (b) offscreen probes: `--to x@y`, `--badflagxyz`, and `--compose --subject --body` all ran healthy (exit 124 =
  alive at kill, no parse error) → unknown flags are silently ignored. `--to` is kept in the argv (harmless,
  future-proof if a rebuilt HB adds it) but the user-facing status message no longer lies about it: it now tells
  the user to type the recipient in the To field.
- The binary-missing fallback message no longer pretends success.

**Staged file:** `src/usr/lib/ncde/verdantfolio/verdant_server.py`

**Diff:**
```diff
--- /usr/lib/ncde/verdantfolio/verdant_server.py
+++ src/usr/lib/ncde/verdantfolio/verdant_server.py
@@ -5,7 +5,7 @@
-import json, os, subprocess, tempfile, urllib.parse
+import json, os, shutil, subprocess, tempfile, urllib.parse
@@ -87,15 +87,21 @@
-            hb = "/home/stephen/ncde-x11/usr/local/bin/hummingbird-courier"
+            # Resolve HB from PATH first (robust across installs), then the known live path.
+            # NOTE: the shipped binary understands --compose/--subject/--body/--attach only;
+            # --to is silently ignored (ComposeRequest has no recipient property) — kept so
+            # the recipient prefills automatically if a future HB build adds it.
+            hb = shutil.which("hummingbird-courier") or "/usr/local/bin/hummingbird-courier"
             if os.path.exists(hb) and os.access(hb, os.X_OK):
                 try:
-                    subprocess.Popen([hb, "--to", to, "--subject", subject, "--body", body, "--attach", attach], env=ENV)
-                    handed = "Opened in Hummingbird Courier with everything filled in — review and hit Send."
+                    subprocess.Popen([hb, "--compose", "--to", to, "--subject", subject,
+                                      "--body", body, "--attach", attach], env=ENV)
+                    handed = ("Opened in Hummingbird Courier — subject, letter, and résumé attached. "
+                              f"Type the recipient ({to or 'their address'}) in the To field and hit Send.")
                 except Exception as ex:
                     handed = f"Email composed (Hummingbird hand-off: {ex})."
             else:
-                handed = "Hummingbird ships on the NCDE system; your email is composed and ready to send."
+                handed = "Couldn't find Hummingbird Courier on this system — your email text is composed above; copy it into your mail app."
```

**Verification (real output).**
1. `python3 -m py_compile <staged file>` → `py_compile OK`.
2. End-to-end /send exercised: staged file copied to scratch with ONLY the port changed 8078→18078
   (diff-proved identical otherwise), run with a PATH-stubbed `hummingbird-courier` + `libreoffice`
   (so nothing touched the live desktop). `curl -X POST /send` with a test résumé returned:
   ```
   {"status": "To: hr@example.com · Subject: Application — Test User · résumé.pdf attached
   "Dear Ms. Reed, … Sincerely, Test User"
   Opened in Hummingbird Courier — subject, letter, and résumé attached. Type the recipient (hr@example.com) in the To field and hit Send."}
   ```
   and the stub HB received exactly:
   ```
   --compose --to hr@example.com --subject "Application — Test User" --body "Dear Ms. Reed, …" --attach .../verdant-resume.pdf
   ```
   i.e. which()-resolution → guard → Popen → honest status, all proven working.
3. Real binary probed offscreen with the exact new flag set (`--compose --subject Probe --body ProbeBody`):
   exit 124 (healthy, alive at kill), no argument errors.
**Not verified:** the visual compose window contents on the live display (would require opening a window on the
operator's session). One eyes-on test after deploy: GiGi → Save & Send → HB compose opens with subject/body/PDF.

**Deploy:** `sudo cp src/usr/lib/ncde/verdantfolio/verdant_server.py /usr/lib/ncde/verdantfolio/verdant_server.py`
**Reload:** `systemctl --user restart verdant-helper.service` (or let the `verdantfolio` launcher restart it).

---

## FIX 2 — ncde-terminal: variable-width font warning / non-fixed-pitch terminal font (audit #7)

**Defect.** `~/.config/ncde-terminal/config.json` had `"fontFamily": "monospace"` (generic alias), consumed by
C++ `TermConfig::fontFamily` and handed to QTermWidget. On this machine fontconfig matches the alias to
**Noto Sans Mono whose pattern has NO spacing property** (`fc-match monospace --format='%{family}|%{spacing}'` →
`Noto Sans Mono | spacing=` — and Noto Sans Mono is absent from `fc-list :spacing=mono`). Qt therefore reports
the font as not fixed-pitch, and libqtermwidget6 warns on every launch (journal ×2/launch) and may misalign
TUI columns.

Note: `Shell.qml:79`'s `font.family: "monospace"` is only the cols×rows resize-badge label, NOT the terminal
widget font — the config.json key is the real seam, so no QML change was needed (and none staged).

**Staged file:** `src/home/stephen/.config/ncde-terminal/config.json`

**Diff:**
```diff
--- /home/stephen/.config/ncde-terminal/config.json
+++ src/home/stephen/.config/ncde-terminal/config.json
@@ -1,7 +1,7 @@
-    "fontFamily": "monospace",
+    "fontFamily": "DejaVu Sans Mono",
```

**Verification (real output).**
1. Compiled a minimal Qt6 probe (QFontInfo — the exact predicate libqtermwidget checks; warning string confirmed
   present in `/usr/lib/libqtermwidget6.so.2`, not the app binary) and ran it under Xvfb (real xcb + fontconfig
   stack, same as the live session):
   ```
   monospace          -> resolves 'Noto Sans Mono'  fixedPitch=0
   Noto Sans Mono     -> resolves 'Noto Sans Mono'  fixedPitch=0
   DejaVu Sans Mono   -> resolves 'DejaVu Sans Mono'  fixedPitch=1
   ```
   fixedPitch=0 is precisely what fires the warning; DejaVu Sans Mono gives fixedPitch=1 → warning cannot fire,
   and the terminal gets a genuinely fixed-pitch face. (`fc-match "DejaVu Sans Mono"` → `spacing=100` = FC_MONO.)
2. `python3 -m json.tool` on the staged config → valid JSON.
3. Real binary A/B: `ncde-terminal` launched with a fake `$HOME` under both offscreen QPA and Xvfb, old vs
   staged config — ran healthy both times (exit 124) but printed nothing either way: standalone runs of this
   binary emit no stderr (0-byte logs), so the warning itself is only observable via the journal of
   session-launched instances. The A/B was therefore inconclusive as a warning-count test; the QFontInfo probe
   above is the decisive evidence.
**Not verified:** absence of the journal warning from a session-launched terminal after deploy — check with
`journalctl --user -f | grep variable-width` after opening a new terminal.

**Deploy (no sudo — user file), IMPORTANT CAVEAT:** ncde-terminal REWRITES config.json on exit (window geometry
keys), so do not blind-copy the staged snapshot over a newer live file. Close all terminal windows, then apply
just the key:
```
python3 - <<'EOF'
import json
p = "/home/stephen/.config/ncde-terminal/config.json"
c = json.load(open(p)); c["fontFamily"] = "DejaVu Sans Mono"
json.dump(c, open(p, "w"), indent=4, sort_keys=True)
EOF
```
**Reload:** open a new ncde-terminal (config read at startup). If the Settings crew ships FiligreeTab's
`ncde.terminalConfig()` font control, this value becomes user-adjustable there afterwards.

---

## FIX 3 — verdantfolio: missing .desktop entry, GiGi invisible in Launchpad/app menu (audit #3)

**Defect.** All 8 other house apps have `/usr/share/applications/*.desktop`; verdantfolio has none — only
reachable via the dock's hardcoded pill (`BottomPanel.qml:123`, `exec: "verdantfolio", name: "Writer"`).
Punchlist §3.7 left naming to the operator; a sane default is staged (trivial to reword before deploy).

**Staged file (new):** `src/usr/share/applications/verdantfolio.desktop`
```ini
[Desktop Entry]
Type=Application
Version=1.0
Name=Verdantfolio
GenericName=Résumé Writer
Comment=Compose a résumé with GiGi and send it on its way
Exec=/usr/local/bin/verdantfolio
Icon=x-office-document
Terminal=false
Categories=Office;WordProcessor;
Keywords=resume;cv;writer;gigi;job;application;
StartupNotify=true
```
Style matches the house entries (compared against abacus.desktop / hummingbird-courier.desktop).
`Exec` target verified: `/usr/local/bin/verdantfolio` exists, executable, starts the helper then `qml6 Main.qml`.

**Verification (real output).** `desktop-file-validate` → clean (no output), echoed `desktop-file-validate OK`.
**Not verified:** appearance in the live Launchpad (needs deploy).

**Deploy:** `sudo cp src/usr/share/applications/verdantfolio.desktop /usr/share/applications/`
**Reload:** none required for most menus; `update-desktop-database` optional (no MimeType declared).

---

## GHIDRA-TRACK (audit items needing C++ / binary work — NOT touched)

- **Audit #5 — hummingbird-courier mailto: parsing absent.** Registered as the x-scheme-handler/mailto default,
  but zero mailto strings in the binary; a mailto click opens HB unparsed. Also Gmail-only (hardcoded
  imap/smtp.gmail.com + GoogleOAuth). Also the cosmetic `[HB] chromium startDetached: true err=Unknown error`
  log on successful OAuth launch. All in the compiled binary.
  - New precise finding for the Ghidra crew (from this session's binary dig): compose hand-off is a
    `ComposeRequest(QList<QString>, QObject*)` object with moc properties exactly `pending, subject, body,
    attachPath` — adding recipient prefill/mailto means extending that class. The compose UI itself is on-disk
    QML (`/usr/share/ncde/HummingbirdCourier.qml`); a QML-side `Qt.application.arguments` parse could prefill
    a recipient on FRESH launches only — it would NOT work when args are forwarded to a running single instance
    through ComposeRequest, so it was not staged (inconsistent behavior is worse than the honest message in Fix 1).
- **Audit #6 — binnie/orchidee/magpie xinput 'libinput Accel Speed' spam ×11 at launch.** Shared compiled engine
  re-applies pointer accel per app start; log-only impact. C++.
- **Audit #4 — verve-text Geany tier.** Syntax highlighting needs C++ (QSyntaxHighlighter). The audit's scoping
  note stands: line numbers / tabs / auto-indent are QML-achievable against existing `fileio.*` symbols — but
  that is new feature work, not a defect fix, so it was not smuggled into this patch.

## SKIPPED (owned by other crews)

- **Audit #1 — MotifFrame.qml:608 GliaFrameMenu anchor** (1-line fix, `anchors.left: parent.left`): MotifFrame
  crew owns it.
- **FiligreeTab.qml / all Settings tabs** (incl. the `ncde.terminalConfig()` seam at FiligreeTab.qml:761):
  Settings crew owns them. Fix 2 deliberately went through the user config file, not the tab.

## VERIFICATION LIMITS (honest summary)

- qmllint was not relied on anywhere; no QML files were changed (the one suspected QML seam, Shell.qml, turned
  out not to be the defect's source and was left alone).
- `bash -n`: no shell scripts were changed, so not applicable.
- Everything stated as verified above shows the actual command result; the three "not verified" lines are the
  only post-deploy checks remaining, and each needs either sudo or the live display.
