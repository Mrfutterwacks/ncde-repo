# APP-FIXES.md — native-app completeness sweep (started session 50, 2026-07-01)

**Read this before touching any native NCDE app** (`magpie-talker`, `orchidee`, `binnie`, `abacus`,
`verve-text`, and any others audited later). Update this file (don't just append elsewhere) as items close
or new ones surface — same convention as `project_ncde_lapivot_punchlist.md`. This sweep started because
the operator asked for a native video-chat feature ("Flutter") for Magpie, which surfaced that Magpie's
source doesn't exist in the tree — that led to auditing the other native apps too, and real bugs turned up
immediately. **Operator's framing: this is exactly the kind of thing that needs to be found and fixed
before building the ISO — treat this file's contents as part of that gate, not optional side work.**

**Standing quality bar, operator's own words (2026-07-01): "orchidee needs to be a premium file manager
the animations stay..but we need to make it the very best" — then, generalizing it — "same as all apps."**
Every app in this file is held to that bar: premium/best-in-class, not merely "not broken." Any existing
animation/transition/polish found while fixing something must be preserved exactly, never stripped or
"simplified" for expediency (same rule this project already applies to MotifFrame's glow). Don't stop at
the bare-minimum fix for a reported bug without at least flagging whether the surrounding UX meets this bar.

> **⚠️ CORRECTED 2026-07-17 — `~/ncde-staging/` no longer exists.** The dev machine that hosted
> `~/ncde-staging/LaPivot/compass7/` (and every per-app `-rebuild/` dir under `~/ncde-staging/`) is
> gone — confirmed absent on this machine and the USB backup. Every path below starting with
> `~/ncde-staging/`, or naming `compass7/lelan`/`compass7/magpie`, describes where source lived on a
> past date (mostly session 50, 2026-07-01, and session 80, 2026-07-07) — read those as history, not
> as where to go edit today, except where a correction note says otherwise. **Current state:** the live
> system (`/usr/local/bin/LaPivot`, `/usr/local/bin/magpie-talker`, `/usr/share/ncde/`, etc.) is the
> only surviving source of truth; C++ recovery now happens by Ghidra-decompiling live binaries into
> `~/ncde-wm-rebuild/` (partial — see `docs/lapivot-rebuild.md`); deploy folds into
> `~/my-project/files/ncde-full-patch-20260711.sh`. Full framing: `docs/CLAUDE.md` §9-10.

## How to use this file

Each app section has: **source status**, **confirmed real gaps** (things that don't work, verified — not
guessed), and **open/unverified** (things nobody has actually checked yet). Don't mark anything "fixed"
without rebuilding + deploying + the operator confirming in his own words, per this project's standing
confirmation convention (see `feedback_verification_discipline` / `SESSION_HANDOFF.md`'s session-46 note).

---

## magpie-talker (chat client)

**SOURCE FULLY RECOVERED (session 50, 2026-07-01) — builds clean, AND NOW ACTUALLY DEPLOYED+RUNNING**
(corrected 2026-07-01, later same session — every prior note below and elsewhere calling this "not yet
deployed" was stale doc drift, not current fact). Verified directly, not assumed:
`sha256sum /usr/local/bin/magpie-talker` = `66c8e09cb928d6603cc137dd921e2985a4b00ac5cce9f3016fcc23b1b2e69657`,
byte-identical to the recovery build; `magpie-talker.prebak-recovery` (dated Jun 21, the pre-recovery
binary) sits next to it as proof of a real `sudo cp` deploy; `pgrep -a magpie-talker` shows it running,
process start time AFTER the binary's mtime. **This does NOT mean operator-confirmed-working** — per the
session-46 confirmation convention, deployed+running is not the same as the operator having tested it and
said so in his own words. Don't write "confirmed" without that.

Real source lives at `~/ncde-staging/LaPivot/compass7/magpie/`: `Peer.h`, `Contact.h`, `KSSecret.h` (+ D-Bus
marshaling), `BonjourDiscovery.h/.cpp`, `MessageHub.h/.cpp` (all 104 methods), `MagpieSecretStore.h/.cpp`
(freedesktop Secret Service keyring integration), `main.cpp`, `CMakeLists.txt`. Full recovery log:
`~/ncde-staging/magpie-rebuild/RECOVERY-PROGRESS.md` — read it before trusting any specific method's
fidelity. Builds with zero errors against shared `Lelan`/`NCDEEngine`/`Settings`/`Launcher` (needed
adding `Lelan.cpp` + friends + `AnimPolicy.h`/`TrayWatcher.h`/`libcrypt` to the link since `NCDEEngine`
forwards to a `Lelan*` even though magpie never calls those paths).

**⚠️ 2026-07-17: this `~/ncde-staging/...` path no longer exists** — see the corrected "where the
source lives now" note further down this section, and the banner at the top of this file.

**UPDATE (same session, later pass) — GeoClue2 wiring completed for real, was previously non-functional
dead code:** `startGeoClue()` existed but was never called from anywhere (the `start()` deferred
`singleShot(0)` lambda that triggers it — found this pass in the raw decompile, `start()`::<lambda()> in
`anon_struct_8_1_48b15bbc_for_o.c` — also constructs+wires+starts `BonjourDiscovery`, which was likewise
never constructed anywhere before this: `m_bonjour` was permanently null despite several methods having
live `if (m_bonjour)` guards for it). `startGeoClue()`'s `GetClient` reply handler and
`onLocationUpdated()`'s property-fetch reply handler were both bare TODO stubs — now real, ported directly
from the decompile: sets `DesktopId=com.ncde.MagpieTalker` (matches `geoclue.conf`'s allowlist entry, byte-
verified identical between staging and the live `/etc/geoclue/geoclue.conf`) and
`RequestedAccuracyLevel=4`, connects `LocationUpdated`, calls `Start()`; `onLocationUpdated` now actually
assigns `m_location` and emits `presenceChanged()` (location has no dedicated signal — confirmed via
decompile, rides the existing `NOTIFY presenceChanged` on the `location` Q_PROPERTY, do not add a separate
signal). Builds clean, staged sha `5a817394fcfe613dd68552b551cdc184da9fe59742b7c766a143eeaeeaf655fd` —
**not deployed.**

**UPDATE (same session, later pass) — full Filigree→NCDEKit→magpie color-token propagation chain
verified end to end, one more real bug found+fixed along the way (`FiligreeTab.qml`, QML-only, no C++
rebuild needed).** Confirmed by reading the actual code at every hop, not assumed:
`NCDEKit.qml`'s tokens (`k.gilt0`, `k.ink`, `k.panelBg`, etc.) all read live from the `ncde` context
property (`NCDEEngine`) via `Q_PROPERTY(... NOTIFY changed)`, and `MagpieTalker.qml` already uses
`NCDEKit { id: k }` throughout (confirmed — not a hardcoded-color file, contrary to what the "doesn't
change colors" symptom might suggest). `NCDEEngine::recompute()` emits both `changed()` and
`themeChanged()`, so QML bindings do re-evaluate on a live theme update — the `loadTheme()` file-watcher
fix above is sufficient to make that update actually arrive in magpie's process.
**Real bug found: Iris Chroma preset taps (`FiligreeTab.qml`) never called `saveTheme()`** — every other
palette-change path (`AccentsPanel.qml`, `WallpaperPanel.qml`, `WallpapersTab.qml`, Filigree's own
`pushSurface`/`pushWidget`) persists to `~/.config/ncde/active-theme.json` immediately after changing
state; Iris Chroma's `TapHandler` called only `ncde.applyPreset(id)` and stopped — so a preset pick
updated LaPivot's own live in-memory palette but was never written to disk, meaning it wouldn't survive a
LaPivot restart AND (compounding with the now-fixed live-reload) would never reach magpie or any other
process either. Fixed: `TapHandler { onTapped: { ncde.applyPreset(irisCard.pd.id); saveTheme() } }` —
matches the existing pattern exactly. `qmllint` clean. Confirmed path match: `settings.configBase` =
`~/.config/ncde/` (Settings.h), same file magpie's `main.cpp`/the new watcher reads — the loop is closed,
not just plausible.
**Separate, smaller, non-blocking finding (not fixed, out of scope for the token-system ask):** the
message-bubble avatar for non-self senders (`MagpieTalker.qml` ~line 506) hardcodes a fixed purple
(`#5a3a6b`/`#33223e`) instead of using the sender's real per-peer identity gradient the way every other
avatar instance in the file does (roster/DMs/channel-members/contacts all bind `c1`/`c2` to
`modelData.c1`/`c2`, sourced from `MessageHub::gradientFor()`). This is unrelated to Filigree/theme
tokens — it's per-peer identity-color completeness — flagging it, not fixing it here.

**UPDATE (same session) — Filigree theme live-reload added to shared `NCDEEngine::loadTheme()`
(`compass7/lelan/NCDEEngine.h`), fixes "magpie doesn't pick up color changes" (operator-reported this
session, see auto-memory `project-ncde-filigree-global-scope` — his words: "remember filigree is
global").** Root cause, confirmed via decompile: the ORIGINAL binary's `NCDEEngine::loadTheme()` set up a
`QFileSystemWatcher` (`m_themeWatcher`) on `active-theme.json` and reconnected on every change; the
recovered `NCDEEngine.h` never had this at all (magpie's `main.cpp` only ever called `loadTheme()` once at
startup) — a real regression lost in recovery, not a feature that never existed. Fixed in the shared header
so every native app using `NCDEEngine` (not just magpie) picks up live Filigree changes, matching "Filigree
is global." Built clean for BOTH consumers — magpie sha `5a817394...` (includes this + the GeoClue2 fix
above), LaPivot sha `ae66ad17162a006df3dbf6911bbffd262fab63d567841a6ab5596a5103c2d311`. **Neither deployed**
— LaPivot's currently-live binary is still `83ed489d...` (session 50 part 1's touchpad-speed build).

**⚠️ CORRECTED 2026-07-17 — WHERE THE SOURCE ACTUALLY LIVES NOW (read this before doing anything else
with magpie):** the `~/ncde-staging/` tree this section originally pointed to is gone — dev machine
lost, confirmed absent on this machine and the USB backup. There is no surviving copy of the recovered
magpie source (`Peer.h`, `Contact.h`, `MessageHub`, `BonjourDiscovery`, etc.) described below. Corrected
model:
- **Live `/usr/local/bin/magpie-talker`** is the only surviving artifact and the actual source of truth
  for what's running — verify its sha before trusting any deploy-status claim in this doc, including
  older ones above.
- **Recovery**, if source work resumes: Ghidra-decompile the live `magpie-talker` binary as the oracle,
  same method now used for LaPivot in `~/ncde-wm-rebuild/`. Nothing under that tree is confirmed
  re-recovered for magpie specifically as of this correction — check `~/ncde-wm-rebuild/` directly
  before assuming otherwise.
- **Deploy**: `~/my-project/files/ncde-full-patch-20260711.sh` — every fix folds in here now, there is
  no separate build-then-`sudo cp`-from-a-tree step.
- Flutter design plan: canonical copy is now `docs/FLUTTER-PLAN.md` (see `CLAUDE.md`) — the
  `~/ncde-staging/magpie-rebuild/FLUTTER-PLAN.md` copy referenced elsewhere in this file is gone/stale.

Original text preserved for history below (all paths dead, do not follow):
- Real, editable C++ source: `~/ncde-staging/LaPivot/compass7/magpie/` — this is the ONLY place to edit
  going forward, same sudo-free working-tree convention as `~/ncde-staging/LaPivot/compass7/lelan/`.
- Build directory: `~/ncde-staging/LaPivot/compass7/magpie/build/` (cmake + make, same as lelan).
- Raw Ghidra decompile output (reference only, do not edit): `~/ncde-staging/magpie-rebuild/src/decompiled/`
  — still useful for finding the handful of not-yet-confirmed details listed below.
- Recovery log / what's confirmed vs. inferred: `~/ncde-staging/magpie-rebuild/RECOVERY-PROGRESS.md`.
- Flutter design plan (separate, not-started feature): `~/ncde-staging/magpie-rebuild/FLUTTER-PLAN.md`.
- **Live `/usr/local/bin/magpie-talker` IS the recovery build (sha `66c8e09c...`) as of this update** —
  the GeoClue2 + theme-watcher fixes above are staged on top of it but not yet deployed. Always
  `sha256sum` before trusting any doc's deploy-status claim, including this one.

**Also found + fixed a real, unrelated latent bug while wiring `main.cpp`:** `compass7/lelan/Settings.h`
was missing `#include <QColor>` (relied on transitive includes elsewhere; broke immediately in magpie's
leaner `main.cpp`). Fixed directly in the shared header — this could affect LaPivot too under different
include orders, worth a light sanity check next LaPivot rebuild.

**A handful of details are honestly flagged as best-supported-inference, NOT byte-confirmed** — search
`RECOVERY-PROGRESS.md` and the code's own comments for specifics before trusting them as fact:
`gradientFor()`'s 8-color avatar palette (placeholder, real hex values never isolated from the binary's
large pool of unrelated hex-looking strings), the `"invisible"` presence-state literal in
`announce()`/`onRelayConnected()`/`sendRelayHeartbeat()`, `deliverTcp()`/`sendXmpp()`'s
`disconnectFromHost()` call after `bytesWritten` (an unresolved vtable call, inferred not confirmed),
`netSummary()`'s `" online"` suffix. The `start()` deferred `QTimer::singleShot(0, ...)` lambda body
listed here as "never located" in an earlier pass **is now found and wired** — see the GeoClue2 update
above; it constructs `BonjourDiscovery` and calls `startGeoClue()`, exactly the "likely" guess, now
confirmed via the raw decompile rather than inferred.

**UPDATE: the TCP-receive path is now done too** — found `onNewTcpConnection()`'s three scattered lambda
bodies (`readyRead`/`disconnected`/`errorOccurred`, same hunt-across-`anon_struct_16_2_5534837f_for_o.c`
method as everything else) and wired them for real: buffers into `m_tcpBufs[sock]`, splits on newline,
dispatches each parsed JSON line through `handleWireObject()` with the peer's real address. All three of
magpie's receive paths (UDP `hello`, native TCP wire messages, XMPP via Bonjour) are now real, not just
the send side.

**Confirmed real, NOT a stub** (verified via compiled binary symbols + a live launch test): `MessageHub`,
`BonjourDiscovery` are genuine, non-trivial classes — real Avahi/mDNS peer discovery, real direct-TCP
messaging (`deliverTcp`/`onNewTcpConnection`), real independent GeoClue2 client
(`startGeoClue`/`onLocationUpdated`) for GPS-location-share. Matches `ncde-architecture.md`'s spec. The
earlier-session finding that Magpie's `hub` QML context object had "zero backend, never registered" was
about **LaPivot's own `main.cpp`**, not magpie-talker's — magpie-talker is a separate standalone binary
with its own (also-missing) `main.cpp`, which presumably does wire `hub` for real, since the compiled app
runs. Not a contradiction, just two different mains — don't re-flag this as a stub once source is
recovered, it isn't one.

**Confirmed real gap:** calls `NCDEEngine::applyGtkTheme()` (GTK/Chromium theme sync) on every startup —
see the corrected `applyGtkTheme()` section below. Not a stray bug in this app specifically; current
LaPivot's own `NCDEEngine.h` is the one actually missing this feature.

**Not yet a bug — a planned NEW feature:** native video/audio chat, codename **Flutter**. Full design doc:
`docs/FLUTTER-PLAN.md` (canonical location since 2026-07-05 — the `~/ncde-staging/magpie-rebuild/
FLUTTER-PLAN.md` copy this used to point to no longer exists). General-purpose feature (churches/synagogues were one
named real-world example, sizing the scale requirements — not the exclusive audience). Key decisions
already made: UI is a transform of Magpie's existing chat window (not a new window), dual session modes
(broadcast/webinar vs. full symmetric gallery), SFU topology (not full mesh, given real classroom/
congregation scale), GStreamer `webrtcbin` for media, LAN-direct + relay-carried signaling with off-LAN
media relay (`coturn`) flagged explicitly as v1.5. Read the plan doc in full before starting any
implementation — don't re-derive these decisions.

**Minor clutter, low priority:** `usr/share/ncde/MagpieTalker` (no extension) contains
`MagpieTalkerManual.qml`'s actual content under the wrong filename — stray duplicate, not referenced
anywhere as far as checked.

---

## binnie (Trash)

**Source: MISSING from the tree.** DWARF strings confirm the original filenames existed
(`BinnieTrash.cpp`/`.h`). Ghidra recovery was tracked at `~/ncde-staging/binnie-rebuild/` — **that tree
is gone (dev machine lost, confirmed 2026-07-17)**; status of any binnie-specific recovery work is
unverified. Current recovery path if resumed: Ghidra-decompile the live binary into
`~/ncde-wm-rebuild/`, same method now used for LaPivot/magpie.

**CONFIRMED REAL BUG, operator-tested directly (not from a symbol-presence check, which missed this):**
**rewind/recovery does not work at all.** Deleting a file does not hold it recoverable for the configured
`rewindHours` window — it's gone immediately, no way to restore. This is despite every relevant method
(`trash`, `restore`, `purgeExpired`, `rewindHours`/`setRewindHours`) existing as real compiled symbols in
the binary (confirmed via `nm -C`) — proves the methods exist but at least one of them doesn't do what its
name says. Plausible root causes to check once source is recovered (not yet confirmed which):
- `trash()` might be permanently deleting the file (e.g. `QFile::remove()`) instead of moving it into
  `filesDir()`/writing real recovery metadata via `writeInfo()`.
- `purgeExpired()` might be running immediately/too aggressively regardless of the configured
  `rewindHours` value.
- `restore()` itself might be broken even if files genuinely sit in trash storage for the window.
**This is the #1 priority once binnie's source lands** — it's a real, confirmed, user-facing data-loss-risk
bug (someone believes they have a 24h undo window and don't).

**Everything else checked out real:** every method the QML (`BinnieApp.qml`) calls exists as a genuine
compiled `BinnieTrash::` method — no other stub pattern found.

**Confirmed real gap:** calls `NCDEEngine::applyGtkTheme()` (GTK/Chromium theme sync) on every startup —
see the corrected `applyGtkTheme()` section below. Not a stray bug in this app specifically; current
LaPivot's own `NCDEEngine.h` is the one actually missing this feature.

---

## orchidee (file manager)

**Source: MISSING from the tree** (`OrchideeFiles`, `NCDEPalette` — zero `.cpp`/`.h`; `Launcher.h` does
exist, shared with LaPivot). Ghidra recovery was tracked at `~/ncde-staging/orchidee-rebuild/` — **that
tree is gone (dev machine lost, confirmed 2026-07-17)**; status of any orchidee-specific recovery work
is unverified. Current recovery path if resumed: Ghidra-decompile the live binary into
`~/ncde-wm-rebuild/`, same method now used for LaPivot/magpie.

**Status: UNAUDITED beyond confirming the binary is real** (compiled, unstripped, not a stub script). The
QML (`OrchideeApp.qml`/`OrchideeSidebar.qml`) expects a sizeable real backend surface — `home`, `entries`,
`makeFolder`, `duplicate`, `trash`, `saveViewMode`/`loadViewMode`, `parseDesktop`, `addToDock`/
`removeFromDock`, `launchBinnie`, `pathExists`, `baseName` — **none of this has been cross-checked against
real implementations yet**, unlike binnie (where `nm` symbol-matching was possible) or magpie (where
strings/DWARF gave enough to verify). **Do this once source lands**: the same QML-call vs. real-method
cross-check used for the Settings-panel audit and binnie. Given binnie's rewind bug turned out to be real
despite looking fine on a symbol check, don't assume orchidee is fine just because it runs — actually test
core operations (move, duplicate, trash-integration with binnie, dock add/remove) live once source is
available to verify against.

**Real scoped enhancement, operator's own idea (2026-07-01): tighter orchidee↔binnie integration, Thunar
style.** Currently the only bridge is `launchBinnie()` — opens Binnie as a completely separate app window.
Thunar's model (referenced by the operator) is much tighter: Trash is a browsable location right inside the
file manager itself (not a separate app launch), with in-place restore. Once both apps' sources are
recovered, consider whether Binnie's trash contents should be browsable as a location/view inside orchidee
directly, rather than requiring a full separate app switch. This is a design upgrade beyond "fix the rewind
bug" — don't build it without confirming scope/approach first, but keep it in mind while working on either
app so the eventual fix doesn't paint against doing this properly later.

**Confirmed real gap:** stray `ncde-chromium-sync.sh` call fires on every startup (see shared-bug section
below) — same as magpie/binnie/abacus; not yet directly tested on orchidee itself but assume same root
cause given the shared-template theory.

---

## verve-text (text editor)

**Source: MISSING from the tree** (`FileIO` — zero `.cpp`/`.h`). Ghidra recovery was tracked at
`~/ncde-staging/verve-text-rebuild/` — **that tree is gone (dev machine lost, confirmed 2026-07-17)**;
status of any verve-text-specific recovery work is unverified. Current recovery path if resumed:
Ghidra-decompile the live binary into `~/ncde-wm-rebuild/`, same method now used for LaPivot/magpie.

**Design intent, operator's own words (2026-07-01): "verve text is supposed to be like microsofts notepad
but also like geany."** See `project-ncde-verve-text-design-intent` auto-memory. This sets the real
completeness bar — Notepad's simplicity plus Geany's lightweight-IDE conveniences (syntax highlighting,
line numbers, tabs/multiple documents, code folding, a symbol/function list sidebar, basic build/run,
auto-indent) — not just "does open/save work."

**Confirmed real: works well already.** Open/save/save-as (`fileio.read/write/joinDocuments/baseName/
addRecent`), draft auto-save + crash recovery (`fileio.saveDraft`/`loadDraft`/`clearDraft`, genuinely wired
to a timer, not decorative), Find/Replace (`findNext`/`replaceOne`/`replaceAll`, real local functions, not
stubs), unsaved-changes guard — all verified real via the 767-line `VerveText.qml`.

**Confirmed real gap:** **no undo/redo at all** — zero references anywhere in the QML. Qt's `TextEdit`
gives this for free; it's simply never wired to a button/shortcut. Basic expectation for ANY text editor,
let alone one aiming for Notepad+Geany — fix this first once source lands, it's likely a small, contained
addition (`TextEdit` has built-in undo stack; wire `Ctrl+Z`/`Ctrl+Y` and menu items to it).

**Not yet audited against the Notepad+Geany bar:** syntax highlighting, line numbers, tabs/multiple
documents, code folding, symbol/function list, auto-indent, basic run/build of scripts. Check each of
these explicitly once source is available — don't declare verve-text "done" on the undo/redo fix alone.

**Confirmed real gap:** stray `ncde-chromium-sync.sh` call fires on every startup (see shared-bug section
below) — not yet directly tested on verve-text itself but assume same root cause.

---

## abacus (calculator)

**Source: not needed — genuinely pure QML, confirmed by its own header comment** ("Pure QML — no C++
backend; arithmetic is evaluated in JS here"). No recovery gap here; nothing to fix at the architecture
level.

**Confirmed real and complete for its actual scope:** 4-function math, digit entry, decimal, negate,
percent, backspace/clear, division-by-zero handling, full hardware-keyboard support, a real (non-empty)
help manual. Verified via the full 291-line `Abacus.qml` plus a live launch test.

**Not missing/broken — absent by design, not stubbed:** no memory functions (M+/M-/MR/MC), no scientific
mode, no history/tape, no operator precedence (immediate-execution model). If the operator wants any of
these, that's a real scope/feature decision to make explicitly — not a bug to silently "fix."

**Confirmed real gap:** stray `ncde-chromium-sync.sh` call fires on every startup (see shared-bug section
below) — confirmed directly on abacus via a live launch test.

---

## `NCDEEngine::applyGtkTheme()` — a real feature LaPivot's CURRENT engine dropped, not a copy-paste bug in other apps

> **✅ RESTORED 2026-07-07 (session 80) — punchlist §2.2, AWAITING DEPLOY.** All three functions
> (`applyGtkTheme`/`applyGtkAccent`/`seedGtkUserConfig`) translated back into the current
> `compass7/lelan/NCDEEngine.h` from the decompile, wired at the original five call sites
> (setDarkMode/setDarkModeLock/applyPreset/sampleWallpaper/loadTheme); new static GTK2 asset
> `usr/share/themes/NCDE/gtk-2.0/gtkrc`; all four NCDEEngine consumers rebuilt; 16/16 harness
> PASS incl. byte-match against the original binary's own `~/.gtkrc-2.0` output
> (`compass7/lelan/test_gtk_theme.cpp`). Operator context captured: **"this works with NCDEkit
> etc"** — this bridge is the tail of the one Filigree → Iris Chroma → NCDEKit → NCDEEngine
> pipeline; see `ncde-architecture.md` §GTK bridge for the full mechanism.
> **One claim below is CORRECTED by the fuller decompile read:** the "GTK2 — real gap" paragraph
> (struck below) said the recovered code never references GTK2 — FALSE: `applyGtkTheme`'s own
> body writes a complete `~/.gtkrc-2.0` (NCDEEngine.c:4588-4644, style "ncde", dark/light bridge
> palettes, accent on PRELIGHT/SELECTED), byte-identical in shape to the live file on this host.
> Only the static `/usr/share/themes/NCDE/gtk-2.0` asset needed creating from scratch.

**The intended full pipeline, operator's own words (2026-07-01): "it was supposed to be one see they all
change colors with the pallets in iris chroma through ncdekit from filigree" + "through the engine."** One
coherent chain, not fragmented pieces: **Filigree** (the Settings-panel UI where a palette is picked) →
**Iris Chroma** (the 90 preset palettes themselves) → **NCDEKit** (the shared QML-side token resolver — see
its real `_bgIsDark()` luminance logic, already a precedent for the separate dark-parchment/glass
auto-contrast item) → **`NCDEEngine`** (the C++ engine — `recompute()` derives all the tokens NCDEKit and
every widget read) → out to every external surface, including GTK2/3/4 and Chromium, via
`NCDEEngine::applyGtkTheme()`/`ncde-chromium-sync.sh`. The current state (engine missing `applyGtkTheme()`,
no GTK2 asset, other apps on a stale copy) is a broken/incomplete version of this one intended pipeline,
not a case of several unrelated small gaps — keep that framing when actually
fixing it: the goal is restoring ONE working chain end-to-end, not patching each endpoint in isolation.

**CORRECTED, superseding an earlier wrong theory in this same file.** Every native app tested prints
`ncde-chromium: mode=dark theme=/usr/share/ncde/chromium/theme-night` to stdout on startup (confirmed via 3
independent live launches: magpie-talker, binnie, abacus). First guess this session was "a copy-paste bug
in a shared, lost `main.cpp` template" — **wrong**, disproven once magpie-talker's Ghidra decompile
produced real source: the call lives inside a real, clearly-named function, **`NCDEEngine::applyGtkTheme()`**
(`~/ncde-staging/magpie-rebuild/src/decompiled/NCDEEngine.c:4205`), which does real, non-trivial work:
`gsettings set org.gnome.desktop.interface gtk-theme NCDE`; **dynamically WRITES fresh accent-color CSS**
(`@define-color ncde_accent ...`) to both `~/.themes/NCDE/gtk-3.0/_accent.css` (GTK3) and
`~/.config/gtk-4.0/_accent.css` (GTK4) from NCDEEngine's current live color state (not a static file — the
CSS is regenerated, decompiled evidence at `NCDEEngine.c:4699-4735`); and `QProcess::startDetached` on
`/usr/local/bin/ncde-chromium-sync.sh <dark|light>` (Chromium). Real, substantial live-sync work — not
boilerplate cruft.

**Important terminology correction, operator's own words: "these aren't themes per say... because ncde
does not use themes.. it uses filigree to change the shell globally.. but we had to make the gtk stuff so
it would work these are defaults."** NCDE itself has no switchable-theme concept — Filigree recomputes the
whole shell's colors live via `NCDEEngine`. The GTK/Chromium files (`gtk.css`, `_accent.css`) exist only as
a **bridge/compatibility layer**: GTK and Chromium DO work on a traditional pick-a-theme model, so NCDE has
to generate a matching set of files for them to read, kept in sync by `applyGtkTheme()`. Don't call these
"an NCDE theme" as if NCDE conceptually works that way — they're generated defaults for interop, one-way
output of the real pipeline, not a parallel theming system.

**The actual finding: `applyGtkTheme()` does not exist anywhere in LaPivot's CURRENT
`compass7/lelan/NCDEEngine.h`** (confirmed via direct grep — zero hits for `applyGtkTheme`, `gsettings`,
or `org.gnome`). No doc anywhere records this being intentionally removed. So the real story isn't "these
apps have a stray bug" — it's **current LaPivot silently lost real GTK/Chromium theme-sync functionality
at some point, while magpie-talker/binnie/abacus/(presumably orchidee/verve-text) still link an older
compiled copy of `NCDEEngine` that still has it.** This is a live instance of the project's own documented
staging/live and doc-drift failure pattern, just discovered via binary archaeology instead of a doc/tree
diff.

**CONFIRMED real regression, not a deliberate cut — operator confirmed the intent directly (2026-07-01):
"ncdekit works with gtk3 and has a gtk4 also" / "so it is a global light and dark theme."** Cross-checked
against real shipped assets, not taken on words alone:
- A real, non-empty "NCDE" GTK3 theme (`gtk.css` + `_accent.css`) is shipped at THREE locations —
  `home/live/.themes/NCDE/gtk-3.0`, `etc/skel/.themes/NCDE/gtk-3.0` (new-user default), and
  `var/lib/ncde-portal/.themes/NCDE/gtk-3.0` (the login greeter) — currently unused by anything, since
  nothing calls `gsettings set ... gtk-theme NCDE` to activate it anymore.
- `ncde-chromium-sync.sh`'s own header comment confirms the intended calling convention: **"Called by the
  engine whenever `ncde.darkMode` flips (and once at login)"** — exactly what `applyGtkTheme()` did, and
  exactly what current `NCDEEngine.h` no longer does anywhere.
- **CORRECTED — GTK4 also gets a real generated accent file, not just the color-scheme dark/light
  toggle.** `applyGtkTheme()` writes `~/.config/gtk-4.0/_accent.css` directly (decompiled evidence,
  `NCDEEngine.c:4704`), same live-generated `@define-color ncde_accent` pattern as the GTK3 file.
  `ncde-chromium-sync.sh` additionally sets `org.freedesktop.appearance`'s `color-scheme`
  (`prefer-dark`/`prefer-light`) for the dark/light half, which GTK4/libadwaita and modern Chromium both
  read via the portal. Both halves (accent color + dark/light) are real, existing (recovered) code — not
  something to build fresh, just restore.

**Fix: restore `applyGtkTheme()` (or equivalent) into current `NCDEEngine.h`, wired to fire on every
`ncde.darkMode` change and once at login** (matching the sync script's own documented contract), so LaPivot
itself gets real global GTK3+GTK4+Chromium theme sync back. Then rebuild magpie/binnie/abacus/orchidee/
verve-text against the corrected engine so they're no longer running a stale copy — not a one-off patch
removing the call from each app individually.

~~**GTK2 — real gap, not just unverified.** Operator's intent covers GTK2 too ("it also has gtk2 too"), but
**confirmed no "NCDE" GTK2 theme asset exists anywhere in the tree** (only generic pre-existing themes —
Raleigh/Default/Emacs — have `gtk-2.0` folders) and neither `ncde-chromium-sync.sh` nor the recovered
`applyGtkTheme()` code references GTK2 at all.~~ **[x] STRUCK 2026-07-07 — half wrong: the recovered
`applyGtkTheme()` DOES generate GTK2 config (`~/.gtkrc-2.0` writer at NCDEEngine.c:4588-4644 — evidence:
the live `~/.gtkrc-2.0` on this host, which the original binary wrote and the restored code now
byte-matches). The asset half was right and is done: new `usr/share/themes/NCDE/gtk-2.0/gtkrc` (gtkrc-based,
GTK2 predates CSS themes) so `gtk-theme-name="NCDE"` resolves; the engine's live rewrite overrides it
per-user.**

---

## Recovery method reference (for whichever app comes next)

**⚠️ CORRECTED 2026-07-17 — every `~/ncde-staging/` path below is dead** (dev machine gone, confirmed
absent on this machine and the USB backup). The Ghidra decompile toolchain/scripts referenced here now
live under `~/ncde-wm-rebuild/` instead — exact subpaths not re-verified against the current layout,
check there directly rather than trusting the literal paths below. The method itself (Ghidra-decompile
the live binary as oracle, `DecompileByClass.java`, JDK 21 requirement) is still the right general
approach — it's the same method used to reconstruct LaPivot's classes; see `docs/CLAUDE.md` §10.
Original steps preserved below for reference; update the paths before using them:

1. `mkdir -p ~/ncde-staging/<app>-rebuild/{ghidra-proj,scripts,src/decompiled}`
2. Copy `~/ncde-staging/ncde-wm-rebuild/scripts/DecompileByClass.java` (the **Java** version — the `.py`
   version needs PyGhidra, not available in this Ghidra 12.1.2 install, confirmed fails with "Python is
   not available") into the new `scripts/` dir, editing only the `outdir` string inside — keep the
   filename and public class name `DecompileByClass` unchanged (Ghidra requires them to match).
3. Import: `~/ncde-staging/ncde-wm-rebuild/tools/ghidra_12.1.2_PUBLIC/support/analyzeHeadless
   ~/ncde-staging/<app>-rebuild/ghidra-proj <app> -import /usr/local/bin/<app>`
4. Decompile: same `analyzeHeadless` command, but `-process <app> -noanalysis -scriptPath
   ~/ncde-staging/<app>-rebuild/scripts -postScript DecompileByClass.java` instead of `-import`.
5. Requires JDK 21 on the dev host (`sudo pacman -S jdk21-openjdk` if missing — confirmed this host had
   no JDK at all as of session 50).
6. Per the operator's standing permission (2026-07-01): recover source for ANY native app found missing
   it, don't ask each time — see `feedback_standing_ghidra_recovery_permission` auto-memory.
