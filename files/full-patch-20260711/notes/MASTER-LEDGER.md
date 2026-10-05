# NCDE MASTER FIX LEDGER — "nothing left" tracker (2026-07-11, session 89)

Goal: fix EVERYTHING → patch this machine → fold into the one patch script (other 2 nodes) → bake the ISO.
This is the single source of truth for what remains. Every item has a ROUTE. Nothing is "can't" without evidence.

## ⭐ CURRENT STATUS (2026-07-12 — reconciled after the scope correction + glia breakthrough)
Truth model corrected: LIVE is truth, the ncde-wm.prebak decompile is a stale RECOVERY TOOL, binary
recovery serves the ORIGINAL-PLAN fixes. Route changes from the tables below noted inline.

**LIVE UI SOURCE-OF-TRUTH RECONCILIATION (2026-09-26):** a fresh hash comparison found 308 active
files under `/usr/share/ncde`. All 308 are now byte-identical in each of the three USB project
source mirrors. The master installer embeds the reconciled source and step `0a/13` restores only
missing or changed UI files; identical live files are left untouched. This closes the former
117-file source/payload gap without folding rollback copies or development-only files into the
installed product. The rest of this ledger remains historical until re-verified against live state.

**DOCK KITH EMBLEM PASS (2026-09-26):** the live `dock.json` lists 12 launchers. Their existing
`MuchaIcon.qml`/`mucha-icons-apps.js` router was read from `/usr/share/ncde`; the five house-app
emblems already cover Sidhe, Boggan, Eshu, Pooka, and Redcap. The dock now opts into kith artwork
for its launchers only: Chromium/Eshu, Terminal/Nocker, Steam/Troll, GIMP/Sluagh,
LibreOffice/Boggan, Spotify/Satyr, and Verve/Pooka. Four original Mucha medallion painters were
added for Nocker, Satyr, Troll, and Sluagh, completing the nine core kiths represented in the
dock. Other `MuchaIcon` consumers retain their established app motifs; launcher commands and
settings are unchanged. This was staged in the project source and master-patch payload, published in signed NCDE
`2026.09.27.0003-1`, and installed on the live system; all four changed dock sources were
verified byte-identical afterward. Roster references: [Changeling: The Dreaming](https://en.wikipedia.org/wiki/Changeling:_The_Dreaming)
and [White Wolf Wiki](https://whitewolf.fandom.com/wiki/Changeling:_The_Dreaming). These sources
describe the kith archetypes; the new artwork is original NCDE interpretation, not a reproduction
of a purported canonical sigil.

**GROUP 1 — DONE + APPLIED to live (the original full patch, operator ran it, "other stuff applied"):**
Sentinel never-freeze+game-priority (black-window bug), game window framing skip (main.qml/TilingManager),
MotifFrame:608 anchor, chromium dark-mode grep, idle-lock chain, per-user QML cache, 8 Settings tabs
(Add-User password!, wallpaper prefs, MOTION, Fonderie specimen, VPN/Printers/Power copy, Session edit),
Verdantfolio→Hummingbird path, terminal DejaVu font, notifyd + appmenu-gtk-module retirement, Vesper suite.

**GROUP 2 — STAGED, awaiting operator sudo-deploy (in ncde-full-patch-20260711.sh):**
- Hummingbird bulk window 40→128 (guarded byte patch) — A3, DONE (deploy: hb-window-patch.sh or the script).
- GLIA (D1-D4 route CHANGED: not REBUILD — a shared `NCDE.Glia` QML plugin + on-disk QML edits, NO recompile):
  plugin built+verified; verve-text wired+staged; abacus+ncde-command wiring in progress. Deploys plugin +
  wired app QML. Live-verify per app (xprop _NCDE_MENUS + menu in bar) after deploy.

**GROUP 3 — REMAINING (the harder original-plan items), current honest routes:**
- **COLORS (C1) — DONE (staged, in master script §0c).** Understood the Filigree→IrisChroma→NCDEKit→NCDEEngine
  pipeline (ncde-architecture.md §6b). Engine exposes NO surface2/panelBg2/inkDim/line* → NCDEKit fell back to
  hardcoded WARM-GOLD → brown bleed on COLD palettes. FIX: NCDEKit now DERIVES all 7 from real palette tokens
  (panelBg/surface/inkSoft/wine4/verd/gilt2-3/cer via Qt.darker/lighter), still `c("tok", <derived>)` so the
  engine wins if it ever exposes them. `NCDEKit.qml` staged, COMPILE+CREATE OK, only 7 tokens changed vs live.
  Factors are tunable (aesthetic — operator may adjust). Proper engine-side version still possible later but
  this is the correct resolver-level fix (NCDEKit IS the token resolver) and is shell-wide + deployable now.
- Hummingbird real pagination + honest delete-confirm (A1/A2 UX) — REBUILD (has DWARF).
- Hummingbird ComposeRequest recipient + mailto (A4/A5) — REBUILD.
- verve-text syntax highlighting (E1) — REBUILD.
- WM (B) — B1 FULLSCREEN = NOT NEEDED (operator 2026-07-12: "it already has full screen"; works live, games QML
  fix covered the real Steam issue). B2 _NET_CLIENT_LIST / B3 Ctrl+Alt+R grab — LaPivot no DWARF + stale; low
  priority, assess later (not tonight).
- **HUMMINGBIRD REAL FIX = THE PRIORITY (operator 2026-07-12).** Byte-patch(40→128)+QML-UX are band-aids; the
  REAL fix needs the MailEngine (C++, hummingbird HAS DWARF ⇒ rebuildable): (1) real PAGINATION (fetch beyond
  the window / load-more), (2) in-app EMPTY-FOLDER / bulk server-side clear (UID SEARCH all → STORE \Deleted →
  EXPUNGE, no need to load 140k), (3) TAGGED-RESPONSE checking (so a failed op doesn't report success),
  (4) special-use folder resolution. This is a focused hummingbird reconstruction (its own track).
- Engine mic meter / hardware-info / native printer (C2/C3/C4) — likely BLOCKED without live-engine source.
- magpie (Flutter) + binnie glia (D3/D5) — separate path, assess.
- **GLIA GLOBAL MENU — ALL TOOLKITS SOLVED (correction 2026-07-12; I wrongly said GTK4 was blocked — it isn't):**
  - GTK2/GTK3 = `ncde-gtk-module.so` (both), publishes `_NCDE_MENUS`, wired via `GTK_MODULES`
    (`80-ncde-globalmenu.sh`); Canonical appmenu double-loader retired (.so gone). DEPLOYED live.
  - **GTK4 = SOLVED, INDEPENDENTLY RE-VERIFIED 2026-07-12 (not on the prior agent's word — actually tested):**
    `files/globalmenu/ncde-gtk4-preload.{c,so}`. Rebuilds clean from source (gtk4 4.22.4, deprecation warnings
    only). MY Xvfb test with a minimal GtkApplication+menubar: PUBLISH proven (`_NCDE_MENUS` got the real
    GMenuModel JSON, File>New/Quit ids 101/102); INVOKE proven (XSendEvent mask=0 `_NCDE_MENU_INVOKE` id 101 →
    on_xevent fired → GAction fired, "ACTION-FIRED"). Live LaPivot sends invokes via `xcb_send_event` (same
    primitive) so real clicks reach GTK4 apps. CAVEAT found: the standalone `files/globalmenu/ncde-menu-invoke`
    tool did NOT reach the handler in test (its own mask/bug — NOT the production path; don't trust it for QA).
    REMAINING = DEPLOYMENT SCOPING ONLY: never LD_PRELOAD globally (drags gtk4 into every proc) — scope to GTK4
    apps via per-app launcher wrapper / curated list, or lazy-dlopen. `gdk_x11_surface_get_xid` = Xlib Window.
  - Foreign Qt apps = `files/globalmenu/libncde-qpa.so` — **INDEPENDENTLY RE-VERIFIED 2026-07-12 (Xvfb, minimal
    QMainWindow+QMenuBar): PUBLISH fires (`_NCDE_MENUS` = File/Edit) AND INVOKE fires (sent to the menu window →
    QACTION-FIRED). Uses `NcdeInvokeFilter` (QAbstractNativeEventFilter) → registry[cm->window]->invoke(id) →
    QPlatformMenuItem::activated().** DONE+STAGED: plugin → `/usr/lib/qt6/plugins/platformthemes/`, ACTIVATED
    via `QT_QPA_PLATFORMTHEME=ncde` in ncde-x11-session (both in master script). Was NEVER deployed/activated on
    live before (the deploy script had the env line commented out) — real gap now closed.
  - House QML apps = NCDE.Glia plugin + wired QML (verve/abacus/ncde-command) — DONE, in master script.
  - **GTK4 — DONE (lazy-dlopen refactor complete + verified + staged, 2026-07-12).** Rewrote the shim to NOT
    link gtk4: `~/ncde-wm-rebuild/glia-plugin/ncde-gtk4-preload.c` → dlopen("libgtk-4.so.1", RTLD_NOLOAD) on
    first interposed set_menubar + dlsym the 6 gtk4/gdk fns; glib/gio/X11 linked directly. VERIFIED in Xvfb:
    publish (`_NCDE_MENUS`) + invoke (GAction fires) BOTH work; NEEDED = glib/gobject/gio/X11/libc ONLY (no
    gtk-4/pango/cairo/vulkan/graphene); loading it in a non-GTK4 proc (/bin/true) stays inert + exits clean.
    STAGED `src/usr/lib/ncde/ncde-gtk4-preload.so` (+ .c); session-wide `LD_PRELOAD` set in ncde-x11-session
    (safe now); master script installs it + asserts it's gtk4-free. Live-verify a real GTK4 app after deploy.

  **⇒ GLIA GLOBAL MENU IS COMPLETE ACROSS ALL TOOLKITS** — GTK2/3 (module), GTK4 (lazy preload), foreign Qt
  (QPA theme), house QML apps (NCDE.Glia plugin). Every piece built, independently verified, and in the patch.
Everything below is the original per-item detail (routes partially superseded by the status above).

## ROUTE KEY
- **DONE** — already staged in full-patch-20260711/src, real-engine gated. (the QML/Python/shell/config pass)
- **REBUILD** — binary retains DWARF ⇒ reconstruct the affected method(s) from the decompile + recompile with the
  on-box toolchain (g++ 16.1.1, Qt6 6.11.1 — verified present) + deploy. REAL fix, deployable here.
- **PATCH** — surgical in-place binary patch (flip a constant / redirect a branch to an existing code path). Deployable,
  low blast radius, backup-first. For LaPivot (no DWARF) this is the primary lever.
- **CAVE** — needs NEW code in a no-DWARF binary (LaPivot). Possible via code-cave injection but higher risk; each judged individually.
- **BLOCKED** — genuinely needs the lost source; not safely doable in-binary. Named + scoped, not hand-waved.

## BINARY REBUILD-VIABILITY (measured)
| binary | DWARF | route class | holds |
|---|---|---|---|
| hummingbird-courier | ✅ | REBUILD | MailEngine (mail app) |
| verve-text | ✅ | REBUILD | text editor |
| magpie-talker | ✅ | REBUILD | chat/video |
| abacus | ✅ | REBUILD | calc/sheets |
| ncde-command | ✅ | REBUILD | command center |
| LaPivot | ❌ | PATCH/CAVE | **WM + NCDEEngine (color/hw/settings)** |
| binnie | ❌ | PATCH/CAVE | files |
| orchidee | ❌ | PATCH/CAVE | (menu publisher) |

---

## A. HUMMINGBIRD (mail — NCDE's "Outlook") — REBUILD viable
Audit in progress (notes/hummingbird-audit.md). Known/expected items:
- A1. **140k / full-history download** — openFolder lambda `FETCH %1:*` fetches whole folder. ROUTE: REBUILD (bound the range) or PATCH if %1 is a constant window. [audit confirming]
- A2. **Delete doesn't stick** — deleteMessages lambda: does it MOVE→[Gmail]/Trash + EXPUNGE, or only un-label (=Gmail archive → "comes back")? ROUTE: REBUILD or PATCH-redirect to the existing inTrash/expunge path. [audit confirming]
- A3. **~40 bulk cap** — find in QML or engine. ROUTE: likely QML (DONE-class) or REBUILD.
- A4. **ComposeRequest has no recipient field** (Verdantfolio→HB handoff can't prefill To). ROUTE: REBUILD (add member).
- A5. **mailto: unparsed + Gmail-only hardcoded.** ROUTE: REBUILD.
- A6. IMAP IDLE (startIdle) — must keep "receive new mail" working through A1/A2 fixes. ROUTE: verify.

## B. LaPivot WM (no DWARF) — PATCH/CAVE, judged per item
- B1. **No `_NET_WM_STATE_FULLSCREEN` handling in manage()** — games/fullscreen framed. QML game-skip already DONE (main.qml); proper WM honor = CAVE (new atom+branch) or accept the QML proxy as the fix. ROUTE: QML proxy DONE; native = CAVE (assess).
- B2. **`_NET_CLIENT_LIST` never advertised** (confirmed: atom not even interned). Affects Steam overlay/capture tools. ROUTE: CAVE (new EWMH property maintenance — assess feasibility; may be BLOCKED).
- B3. **Global Ctrl+Alt+R grab absent** (confirmed: xcb_grab_key called 0×). ROUTE: CAVE (inject XGrabKey at setup + dispatch) — assess.
- B4. **Client-position inset (-17,-21) for framed/maximized** — geometry constant. ROUTE: PATCH if constant.

## C. NCDEEngine (inside LaPivot, no DWARF) — PATCH/CAVE
- C1. **Missing color tokens** surface2/panelBg2/inkDim/lineWine/lineSage/lineOchre/lineCer → cold palettes render warm-brown secondary surfaces. ROUTE: CAVE (new Q_PROPERTYs) — hard; interim NCDEKit.qml QML-derive fallback is DONE-class (assess).
- C2. **Mic level meter** (SoundTab) needs libpulse feed. ROUTE: CAVE — assess; likely BLOCKED (new subsystem).
- C3. **Hardware-info grid** (AboutTab) — properties don't exist. ROUTE: CAVE — assess; likely BLOCKED.
- C4. **Native printer add/discover** (PrintersTab) — no addPrinter/discoverPrinters symbols. ROUTE: system-config-printer launch already staged (ncde-phase2); native = CAVE/BLOCKED.
- C5. reduceMotion Settings→AnimPolicy C++ handoff — verify acts without relogin. ROUTE: verify, else CAVE.

## D. House-app GliaTalk menu publishers (the 5 that emit 0 _NET_MENUS)
- D1. verve, D2. abacus, D3. magpie, D4. ncde-command — all **DWARF ⇒ REBUILD** (add the _NET_MENUS publisher).
- D5. binnie — **no DWARF ⇒ PATCH/CAVE.**

## E. Other app items (from house-apps audit)
- E1. verve-text syntax highlighting (QSyntaxHighlighter) — DWARF ⇒ REBUILD.
- E2. shared-engine xinput accel spam (binnie/orchidee/magpie) — mixed; assess per binary.

---

## EXECUTION ORDER (proposed)
1. Finish Hummingbird audit → fix A1-A6 (REBUILD/PATCH). Highest operator priority.
2. Reconstruct+recompile the DWARF apps for D1-D4, E1, A4/A5.
3. LaPivot PATCH items (B4, and any C constant) — surgical, backup-first.
4. LaPivot CAVE items (B1-B3, C1) — assess feasibility one-by-one; do the viable, name the BLOCKED with evidence.
5. Everything proven → append to ncde-full-patch-20260711.sh → operator patches all 3 nodes → bake ISO.

## HONEST NOTE
The DWARF apps can be genuinely fixed here. LaPivot (WM+engine) is the hard wall: surgical patches are real,
but items needing whole new subsystems (client-list maintenance, libpulse mic feed, hardware-info) may be
BLOCKED without the lost source — those get named precisely, not pretended. Nothing is closed on a guess.
