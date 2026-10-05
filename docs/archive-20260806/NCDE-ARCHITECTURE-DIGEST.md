# NCDE Poseidon — Architecture Digest (Reconstruction Reference)

> Built by reading the full canonical doc set in `~/my-project/docs/` and cross-checking every
> checkable claim against the LIVE binaries (`nm`/`strings` on `/usr/local/bin/LaPivot`,
> `ncde-wm`, helpers) and the live filesystem (`/usr/share/ncde`, `/usr/local/bin`, systemd
> units, running processes). `[E]` = confirmed against a live binary/file this pass. `[DOC]` =
> from the docs, not independently re-verified here. Purpose: guide a faithful C++ reconstruction
> of the LaPivot window manager from the Ghidra decompile — **conform to the live binary, not the
> plan** (the operator's own audit rule: "the plan is WRONG where it disagrees with the oracle").

---

## 1. The system in one page

**NCDE Poseidon** is a first-party Unix desktop OS. **NCDE = the OS name; LaPivot = the window
manager** (`/usr/local/bin/LaPivot`, Qt6/QML + X11 + picom compositor). The old `ncde-wm` binary is
the legacy fallback; LaPivot is the rebuilt production WM (Ghidra-recovered from the unstripped
`ncde-wm`, reconstructed class-by-class in `~/ncde-wm-rebuild/`, 153 classes — **corrected
2026-07-17: partial, not all classes compile-verified**; see `docs/lapivot-rebuild.md`). QML lives
on disk at `/usr/share/ncde` (plain text, runtime-loaded — no compile). **There is no production
source tree** (`~/ncde-staging/` confirmed gone) — the live binary is the source of truth, and the
operator's own account of the design is primary-source spec: the operator is "the living source
code."

**Design north star — WWCDED ("What Would CDE Do?"):** NCDE is the Common Desktop Environment
reimagined as a modern, coherent, integrated product — *not* a GNOME/KDE clone. Lineage is concrete
(`PROJECT.md`): CDE ToolTalk → `lelan`; CDE Style Manager → `ncde`; the CDE `dt*` suite → the NCDE
apps; CDE Front Panel/Workspace → Dock/panels + `NCDEWorkspace`; Motif bevels → gilt/filigree/glass.
**macOS is only the polish/performance layer** (App Nap / Timer Coalescing / QoS → Lelan+Zen; Core
Animation → Qt `Animator`), never the blueprint.

**The chain of command (the operator's canonical mental model, a family AND a command chain):**
- **Zen = father / the linux-zen kernel** — NCDE's *only* kernel, chosen for built-in optimization;
  the passive substrate. Not a class, not branding. *"Zen is the linux-zen kernel NCDE ships and
  boots on… not a class, not 'branding.' Lelan and Sentinel are the controllers: they drive every
  aspect of the host BY USING Zen's built-in scheduling/power primitives… Zen does not act on its
  own."* (`zen.md`)
- **Lelan = mother / the nervous system** — an in-process C++ hub compiled into LaPivot; subscribes
  ONCE to every system service and fans state to the UI. *"Lelan is the thing that controls all that
  Zen has to offer for NCDE/LaPivot."* *"everything goes through lelan; the whole system is governed
  by lelan + zen."* *"if mamma is gone nothing gets done."* (`lelan.md`, `zen.md`)
- **Sentinel = Tía/aunt / the senses** — `io.ncde.Sentinel`, a standalone **Python** udev→D-Bus
  hardware guardian; senses hardware, feeds Lelan, and acts as "Zen's hands" (writes sysfs).
  *"Sentinel is a watcher… it speaks to Lelan who controls that."* (`sentinel-plan.md`, `zen.md`)
- **Vesper = the immune system / knight-constable** — the security suite (see below).
- **NCDE = the child.** *"It's all one thing"* — one organism, a **UNIFIED HOST**, never "a
  federation of components on a peer bus."

**The design system — glass / parchment / metal.** Three material classes (`gtk.md §0`): **Glass**
(panels/dock, tintable/translucent), **Parchment** (native app bodies, ink-adaptive dark/light,
body face **IM Fell English**), **Metal** (static — terminal + window frames only). All driven by
ONE live color pipeline, in the operator's words: **Filigree** (Settings palette-picker UI) →
**Iris Chroma** (90 named preset palettes, six pigments each: accent/border/panelBg/surface/ink/
inkSoft + dark flag) → **NCDEKit** (shared QML token resolver) → **NCDEEngine** (`recompute()`
derives every token) → out to *every* surface incl. GTK2/3/4 + Chromium. One preset click recolors
everything. Operator: *"ncde does not use themes.. it uses filigree to change the shell globally.."*
Accessibility is engineered in: ink contrast ≥ 7:1, dark palettes auto-get light ink, selection
text always `#FFFFFF`, no white flashes.

**GliaTalk — the no-D-Bus global menu (CDE ToolTalk, modern).** The macOS-style global menu bar is
implemented over raw **X11 window properties**, not D-Bus: an app publishes its real menus as UTF-8
JSON on the `_NCDE_MENUS` atom on its own top-level window; the WM reads it at manage-time and on
`PropertyNotify`; invocation is a `_NCDE_MENU_INVOKE` ClientMessage (format 32, `data32[0]`=item id)
back to the window, caught by a `QAbstractNativeEventFilter`. Operator: *"D-Bus would never have
given NCDE the control the way Glia talk does. Think how Lelan controls Zen, so Glia talk controls
all apps… No dbus, ever."* Header `GliaTalk.h` (its `compass7/lelan/` working copy is gone —
corrected 2026-07-17, see §1); shell merge in `GliaGlobalMenus.qml`+
`TopPanel.qml`; reference publisher Orchidée. Non-publishing (foreign) apps keep a static relay
trio. `[E]` — atoms `_NCDE_MENUS`/`_NCDE_MENU_INVOKE` and `activeAppMenus`/`invokeAppMenu` confirmed
in LaPivot; helper `/usr/local/bin/ncde-menu-invoke` present.

**Vesper / KickassGuard — the security brain (NO LLM, live-verified).** The old `kickass-guard`
LLM daemon (Ollama + `vesper:latest` Qwen + ChromaDB RAG, `org.ncde.KickassGuard`) is **SUPERSEDED
and NOT installed live**. The real, running Vesper is a no-LLM suite: a Python `brain_server.py`
HTTP server on `127.0.0.1:8077` (in-memory MITRE ATT&CK STIX lookup — `enterprise-attack.json`,
confirmed live) + `vesper_engines.py` orchestrating five real tools (ClamAV, rkhunter, fail2ban,
nftables, auditd) + a green-phosphor QML UI (`/usr/share/ncde/vesper/`, `VesperBackend.qml` polling
`/findings` every 6s). Launched by `/usr/local/bin/ncde-vesper`; `vesper-brain.service` (user,
enabled). Operator: *"we don't use llms for kickass or vesper anymore"*; *"If Vesper tells you
something is wrong, something is wrong"*; *"He asks. You decide."*; *"Quarantine never destroys."*
`[E]` — no `kickass-guard` binary, no `ollama`, no `chromadb`, no `/var/lib/ncde-kickass` on the
live system; `brain_server.py` + `vesper_engines.py` + `enterprise-attack.json` present under
`/usr/lib/ncde/vesper/`; Sentinel built out as a Python package `/usr/local/bin/sentinel/`
(`hwmon.py`, `drivers.py`, `hw_tier.py`, `pwm_guard.py`, `process_tier.py`).

**The house apps (NCDE's own suite):** file manager **Orchidée** (`orchidee`), trash **Binnie**
(`binnie`), text editor **Verve** (`verve-text`), calculator **Abacus** (`abacus`, pure QML), LAN/
DHT messenger **Magpie Talker** (`magpie-talker`) + its relay `dovecote-relay` + built-in video chat
codename **Flutter**, Gmail client **Hummingbird Courier** (`hummingbird-courier`), terminal
(`ncde-terminal`), Settings/Control-Center (`ncde-command`), themed Chromium (`ncde-chromium`),
recovery app **Soundings** (`ncde-recovery`, btrfs time-machine, Ctrl+Alt+T). Shared blocks:
`NCDEEngine`, `Launcher`, `Settings`, `KSSecret` (libsecret keyring).

**Branding invariant:** NCDE hides its Arch/Archcraft base "like macOS hides BSD" — no user-visible
"Arch/Linux/pacstrap/chroot/partition" text anywhere (CLAUDE.md Rule 7 / gtk.md §9 / commercial.md).

---

## 2. Per-class purpose table (the reconstruction reference)

Live column = symbol count in `/usr/local/bin/LaPivot` this pass (`nm --defined-only | c++filt`).
**Read the divergence notes** — several doc class names do not exist in the live binary.

| Class (as requested) | Purpose | Establishing source / LIVE status |
|---|---|---|
| **NCDEWindowManager** | The WM/compositor core: manage/reparent, focus, tiling, snap, `_NET_WM`, GliaTalk menu read (`activeAppMenus`, `invokeAppMenu`). | `ncde-architecture.md §2`; **LIVE `[E]` 631 syms** |
| **NCDEEngine** | Color/theme engine ONLY (no system data): `recompute()` derives every token; GTK/Chromium bridge (`applyGtkTheme/applyGtkAccent/seedGtkUserConfig`); `loadTheme` on `active-theme.json` watch. | `gtk.md`, `gtk-designer-answers.md`; **LIVE `[E]` 739 syms** |
| **Settings** | Config store/façade, delegated from Lelan via `setSettings(Settings*)`; hot-reload via `QFileSystemWatcher`. Not owned by Lelan. | `lelan-audit.md`; **LIVE `[E]` 382 syms** |
| **LElan / Lelan** | The nervous system: one owner per service, ~80 signals, push-not-poll, one coarse timer; drives AnimPolicy; self-preservation watchdog. | `lelan.md`, `NCDE-LELAN-PLAN.md`; **LIVE `[E]` — but named `Lelan::` (2531 syms), NOT `LElan`** (the oracle decompile is `LElan.c`; the rebuild renamed it) |
| **DesktopWidget** | Conky-style dashboard (CPU/RAM/net/battery, MPRIS, weather, moon phase). | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `DesktopWidget` class in LaPivot** — data is `WidgetData` (154 syms), exposed as `widget_data`; `DesktopWidget.qml` is the frontend. Divergence. |
| **ThemeManager** | Theme/icon/cursor/GTK install-export-apply. | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `ThemeManager` class** — theming is `NcdeTheme` (83) + `Theme` (58) + `NCDEEngine`. Doc abstraction, not a real class. |
| **HudManager** | Unity-style searchable global-menu HUD; signal source to `Hud.qml`. | `ncde-architecture.md §2`; **LIVE `[E]` 19 syms** |
| **Launcher** | App/exec launcher + session save/restore + screenshot + logout. | `ncde-architecture.md §2`; **LIVE `[E]` 19 syms** |
| **CursorManager** | Xcursor/"Kithglass" cursor theme loader (large subsystem). | `ncde-architecture.md §2`; **LIVE `[E]` 692 syms** (bigger than expected) |
| **TrayWatcher** | System tray host. | `ncde-architecture.md §2` says "XEmbed `_NET_SYSTEM_TRAY`" `[DOC]`; **LIVE: NO `TrayWatcher` class** — tray is StatusNotifier: `SniWatcher` (65) + `StatusNotifierWatcherAdaptor` (73). Mechanism AND name diverge (matches `lelan-research-findings.md` SNI recommendation). |
| **AnimPolicy** | Animation governor: 3 tiers, degrade decorative work only, essential transitions always vsync `Animator`. | `anim-policy.md`; **LIVE `[E]` — exact property set confirmed: `level, reduceMotion, idleLoops, decorative, instant, screenIdle, thermalPressure, lowPower, desktopObscured`** |
| **NCDEIconManager** | Per-icon override packs / icon themes (`iconManager` context prop). | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO C++ class** (0 syms) — a QML file (`NCDEIconManager.qml`) backed by NCDEEngine. |
| **AppMenuModel** | The global app-menu model / AppMenu registrar bridge (feeds GliaTalk relay). | `ncde-architecture.md §2`; **LIVE `[E]` 549 syms** (the real global-menu workhorse) |
| **GliaSystemMenus** | XDG `.desktop` scanner/launcher (apps + places). | `ncde-architecture.md §2`, `gliatalk.md`; **LIVE `[E]` 86 syms** |
| **GliaSystemMenus / GlobalMenu** | (GlobalMenu = the AppMenu Registrar in the doc) | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `GlobalMenu` class** — role is `AppMenuModel` + `NCDEWindowManager` GliaTalk + `GliaSystemMenus`. |
| **NCDEMenuBridge** | Reads X11 `_KDE_NET_WM_APPMENU` + dbusmenu. | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `NCDEMenuBridge` class** — superseded by GliaTalk (`_NCDE_MENUS`) + AppMenuModel. |
| **NotificationManager** | Notification server/history/DND/unread. | `ncde-architecture.md §2`; **LIVE `[E]` 28 syms** (but see note on the D-Bus name below) |
| **NCDECalendar** | Appointments + todos + reminders. | `ncde-architecture.md §2`, `PROJECT.md` (dtcm); **LIVE: renamed to `CalendarBackend` (330 syms)** in LaPivot; legacy `ncde-wm` still has `NCDECalendar`. Exposed as `calBackend`. Rename divergence. |
| **NCDEWorkspace** | Virtual desktops (CDE Workspace Manager). | `ncde-architecture.md §2`; **LIVE `[E]` 46 syms** |
| **LeapFrogPond** | Notes + appointments organizer; exports CSV/`.lilypad`. | `ncde-architecture.md §2`; **LIVE `[E]` 65 syms** |
| **NCDEMail** | Embedded IMAP/SMTP mail client. | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `NCDEMail` class in LaPivot OR ncde-wm** — mail is the separate `hummingbird-courier` binary (`MailEngine`). Divergence: mail is not embedded in the WM. |
| **PlayerBridge** | MPRIS media bridge. | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `PlayerBridge` class** — MPRIS folded into `Lelan` (`fetchPlayer`) + `PlayerState` (9) + `WidgetData`. |
| **VpnBridge** | NetworkManager VPN watcher. | `ncde-architecture.md §2` `[DOC]`; **LIVE: NO `VpnBridge` class** — folded into `Lelan` (`disconnectVpn`, `markActiveVpns`, `connectWifi`). |
| **FreedesktopNotificationsAdaptor** | D-Bus adaptor for `org.freedesktop.Notifications`. | `ncde-architecture.md §2/§7` `[DOC]`; **LIVE: NO such adaptor** — only `StatusNotifierWatcherAdaptor` exists; `org.freedesktop.Notifications` string not found in LaPivot (it registers `org.ncde.desktop`). Flag/verify. |

Other high-value live classes a reconstructor will meet (not in the request list but load-bearing):
`CalendarBackend` (330), `FontManager` (194), `WidgetData` (154), `NCDEGeo` (55), `NcdeTheme` (83),
`SniWatcher`/`StatusNotifierWatcherAdaptor` (SNI tray), `IdleInhibitService` (65), `XSettingsManager`
(12), `WindowTyper` (19), `ScreenInfo` (42). GliaTalk is a **header/protocol** (`GliaTalk.h`), not a
class with a symbol footprint.

---

## 3. Design invariants the reconstruction MUST preserve

1. **"No D-Bus, ever" is SCOPED to the app-control plane (GliaTalk), not the whole system.** The
   global-menu / app-command layer uses X11 properties only (`_NCDE_MENUS` JSON + `_NCDE_MENU_INVOKE`
   ClientMessage) — verified live. But **Lelan itself is heavily D-Bus** (system-service consumption:
   NetworkManager, UPower, BlueZ, UDisks2, GeoClue2, login1, portal, PackageKit, Sentinel, MPRIS
   monitor) — `Lelan::onSentinel*`, `onBlueZ*`, `onGeoClue`, `onPortalSettingChanged`, `connectWifi`,
   `disconnectVpn` all present live. Reconstruct GliaTalk with zero D-Bus; keep Lelan's D-Bus
   subscriptions. Lelan registers **NO** D-Bus service of its own (in-process; there is no
   `org.ncde.Lelan`).
2. **Two context properties, never conflated:** `lelan` = event hub (signals only); `ncde` = theme/
   appearance/state object (`NcdeTheme`) that widgets bind to. `NCDEEngine = colors only`, carries no
   system data. Additionally, the shipped QML binds `lelan.*` essentially zero times — system data
   reaches the UI via `widget_data.*` (fed by `WidgetData`) and `ncde.*` (tokens). The real seam is
   **Lelan → WidgetData → `widget_data.*`**, not QML→lelan directly (`lelan-audit.md`, `missing.md`).
3. **Push, never poll — the Moksha goal.** One coalesced `Qt::CoarseTimer` heartbeat; never
   reintroduce per-widget polling. Idle App-Nap = `leanSleeping`/`leanWaking`/`deferWhenIdle`/
   `drainIdleQueue` (all present live), with per-job **BFQ-gated** IDLE ioprio — NOT a global
   process-IDLE pin, and NOT the invented `applyIdleState`/`setPulseScale` throttle (which caused the
   session-17 cursor freeze). `[E]` idle-queue symbols confirmed in LaPivot.
4. **AnimPolicy tiers (degrade quality, never halt):** **0 Full** (AC, cool, active — all loops/
   particles/glows, full FPS) · **1 Reduced** (battery/warm/idle — drop idle shimmer & particle
   loops, cap FPS, cheaper easing) · **2 Minimal** (low-battery/thermal-critical/reduce-motion —
   motion → instant/single cross-fade, no continuous loops). Essential transitions run on Qt
   `Animator` types (render thread) and stay vsync-smooth in ALL tiers. Cuts land only on decorative,
   looping work.
5. **Zen governor behavior:** foreground boost = **the compositor boosts ITSELF** (nice −5,
   SCHED_FIFO 1, uclamp 200/1024 while animating) — **never reniche client processes**.
   `NCDEEngine::foreground()` is a theme color getter, not process logic. Sentinel sets cpufreq
   governor + `vm.dirty_ratio` on AC/battery; optional per-window cgroup-v2 tiering
   (`SetProcessTier`). Codependent: no-polling is the precondition that lets Zen's power tuning work.
6. **Vesper is NON-LLM and deterministic** — `brain_server.py` on `:8077` + five real engine
   subprocess adapters + QML polling. Never re-provision Ollama/Chroma/`vesper:latest`. Quarantine
   never destroys; Vesper always asks, user decides; never a false all-clear; cold green-phosphor UI
   deliberately unlike the rest of NCDE ("the contrast is the signal").
7. **Sentinel stays Python, one daemon, root system service.** Senses hwmon via glob (no hardcoded
   chips); driver detection via `modalias`; MANDATORY thermal fail-safe (restore `pwmN_enable=2` on
   ANY exit/crash/signal). Talks to Lelan over `io.ncde.Sentinel`.
8. **Hide-Arch branding rule** (Rule 7) — no Arch/Linux/toolkit jargon user-visible; parchment/
   nautical theme; "Captain's Log" installer.
9. **`archisosearchuuid` / ISO modification-date `2026-05-12-06-51-54-00` is frozen** — change it and
   nothing boots (ISO/boot invariant, `ISO-BUILD-PLAN.md`/`MEMORY.md`; not a WM concern — correctly
   absent from LaPivot). Volume label must be `NCDE_POSEIDON` (open blocker: still `ARCHCRAFT_202605`).
10. **Aesthetic is sacrosanct** — pixel-identical; change HOW not WHAT; never touch `lampPulse`
    timing or the MPRIS scrubber without sign-off (`commercial.md`). Everything recolors from one
    Iris Chroma click via Filigree→NCDEKit→NCDEEngine; there is no switchable-theme concept.

---

## 4. Doc-vs-live divergences found (with evidence)

| # | Divergence | Evidence |
|---|---|---|
| D1 | Class is **`Lelan`**, not `LElan`. Docs/oracle use `LElan` (the decompile is `LElan.c`); the rebuilt LaPivot renamed it to `Lelan`. | `nm LaPivot` → `LElan::`=0, `Lelan::`=2531. |
| D2 | **No `DesktopWidget` C++ class** in LaPivot. Desktop-widget data is `WidgetData` (`widget_data`). Doc `ncde-architecture.md §2` lists DesktopWidget as an embedded subsystem with `setAnimPolicy` etc. | `nm LaPivot` DesktopWidget=0, WidgetData=154. `anim-policy.md` itself flags `DesktopWidget::setAnimPolicy` as OLD-BINARY-only. |
| D3 | **No `TrayWatcher` / XEmbed tray.** Tray is StatusNotifier (SNI). Doc `§2` says "TrayWatcher — XEmbed `_NET_SYSTEM_TRAY`". | `nm LaPivot`: TrayWatcher=0, `SniWatcher`=65, `StatusNotifierWatcherAdaptor`=73; strings show `org.kde.StatusNotifierItem/Watcher`. |
| D4 | **`NCDECalendar` renamed to `CalendarBackend`** in LaPivot. | `nm LaPivot` NCDECalendar=0, CalendarBackend=330; legacy `ncde-wm` still has NCDECalendar (71). |
| D5 | **`NCDEMail` is not embedded in the WM.** Mail is the separate `hummingbird-courier` binary. Doc `§2` claims NCDEMail (IMAP/SMTP) lives inside ncde-wm. | NCDEMail=0 in BOTH LaPivot and ncde-wm; `hummingbird-courier` present in `/usr/local/bin`. |
| D6 | **`GlobalMenu`, `NCDEMenuBridge`, `PlayerBridge`, `VpnBridge`, `NCDEIconManager`, `ThemeManager` do not exist as classes.** Their roles are absorbed (menus→AppMenuModel+GliaTalk; player/vpn→Lelan; theme→NcdeTheme/NCDEEngine; icons→NCDEEngine). Doc `§2` lists all as C++ subsystems. | `nm LaPivot`: all =0; AppMenuModel=549, `Lelan::fetchPlayer`/`disconnectVpn` present, NcdeTheme=83. |
| D7 | **No `FreedesktopNotificationsAdaptor`; `org.freedesktop.Notifications` string not present** in LaPivot — it registers `org.ncde.desktop`. Docs `§2/§7` say NCDE *is* the freedesktop notification server. `NotificationManager` (28) does exist. Needs live `busctl` confirmation of what actually owns Notifications. | `strings LaPivot` shows `org.ncde.desktop` (+ Sentinel/KickassGuard/StatusNotifier) but no `org.freedesktop.Notifications`; no `*Adaptor` except StatusNotifier. |
| D8 | **The entire LLM KickassGuard stack is absent live** — superseded by no-LLM Vesper. Docs `kickass-guard.md`, `ncde-completeness-audit.md §Group-2` describe Ollama/Chroma/`vesper:latest`/`org.ncde.KickassGuard`/`/var/lib/ncde-kickass`. | No `kickass-guard` binary; `ollama`/`chromadb` not found; no `/var/lib/ncde-kickass`. Live: `/usr/lib/ncde/vesper/brain_server.py` + `vesper_engines.py` + `enterprise-attack.json`, `vesper-brain.service` enabled. |
| D9 | **Zen static self-boost is DEAD on live** — running WM shows nice 0 / SCHED_OTHER (spec: −5 / FIFO 1) because the binary lacks `cap_sys_nice`. | `zen.md` session-82 live-audit; fix = `setcap cap_sys_nice+ep` (dropped by every `cp`). |
| D10 | **Group-1 runtime deps may be missing** (geoclue/power-profiles-daemon/packagekit/nss-mdns) — silently kills weather/location/updates/power-tiering if absent. | `ncde-architecture.md §12`, `ncde-completeness-audit.md §Group-1`; verify per-host. |
| D11 | **"Audio via PulseAudio Core1" is wrong** — pipewire-pulse ships no D-Bus module; use **libpulse**. The recovered `LElan` has 0 `org.PulseAudio.Core1` refs. Old plan text (`lelan.md §10` aggregate-map skeleton) misled the first rebuild. | `lelan-audit.md`, `lelan-research-findings.md §2`, `missing.md §6` (RESOLVED). |

---

## 5. Open questions a reconstructor will hit

1. **What owns `org.freedesktop.Notifications` on the live system?** LaPivot registers `org.ncde.desktop`
   and has `NotificationManager` but no freedesktop-Notifications string/adaptor symbol. Is the fdo
   notification server (a) named differently, (b) in a helper, or (c) dropped? Confirm with
   `busctl --user list | grep -i notif` and introspection before wiring `FreedesktopNotificationsAdaptor`.
2. **`ncde` vs `lelan` object identity:** are they the same QObject under two context-property names,
   or two objects (Lelan feeding a separate `NcdeTheme`)? `missing.md §6` still lists this `[VERIFY]`;
   the live split (`Lelan` 2531 vs `NcdeTheme` 83) suggests two objects, but confirm the
   `setContextProperty` calls in `main.cpp`.
3. **How much Sentinel↔Lelan wiring is real vs intended?** The recovered `LElan` has ZERO Sentinel
   references (`lelan-audit.md`) — Sentinel integration was a post-recovery upgrade. But live LaPivot
   *does* have `Lelan::onSentinel*` handlers and a built-out `/usr/local/bin/sentinel/` package. So
   the rebuild has advanced past the oracle here; reconstruct to the LIVE surface, not the oracle, for
   Sentinel.
4. **CalendarBackend vs NCDECalendar contract:** the rename (D4) means the QML `calBackend` contract
   should be validated against the live `CalendarBackend` method set (`appointments`, `upsertAppointment`,
   `exportICS`, `composeForHummingbird`, `fireReminder` seen live), not the doc's `NCDECalendar`.
5. **Vesper UI autostart gap:** `vesper-brain.service` starts only the HTTP backend; no unit/.desktop
   launches the visible `Main.qml` phosphor window except a threat trigger or manual `ncde-vesper`.
   Is that intended (only-appear-on-threat) or an unfinished build item? (`vesper.md` flags it OPEN.)
6. **Which house apps' C++ is recovered vs still stub?** `APP-FIXES.md`: magpie fully recovered/builds;
   binnie (confirmed rewind bug), orchidee, verve-text source were MISSING and under Ghidra recovery.
   Per operator rule "THERE SHOULD BE NO STUBS" — verify implementation depth, not just file existence.
7. **CursorManager is unexpectedly large (692 syms).** The "Kithglass" cursor system
   (`KithCursor.qml`, `kithglass-cursors.js`) is a bigger subsystem than the docs describe — worth a
   dedicated read before reconstructing it.

---

*Docs read this pass:* `ncde-architecture.md`, `PROJECT.md`, `commercial.md`,
`ncde-completeness-audit.md`, `missing.md`, `build-the-missing.md` (via cluster), `lelan.md`,
`NCDE-LELAN-PLAN.md`, `lelan-audit.md`, `lelan-research-findings.md`, `lelan-references.txt` (skim),
`sentinel-plan.md`, `zen.md`, `vesper.md`, `vesper-knowledge-base.md`, `vesper-wiring.md`,
`vesper-interface-brief.md`, `kickass-guard.md`, `gliatalk.md`, `anim-policy.md`, `APP-FIXES.md`,
`gtk.md`, `gtk-designer-answers.md`, `FLUTTER-PLAN.md`, `lelan-designer-checklist.md`. CLAUDE.md +
`ncde-completeness-audit.md` used for framing. *Not deep-read (session-log/plan skims only, per
instructions):* `SESSION_HANDOFF.md`, `MEMORY.md`, `PRODUCTION-PUNCHLIST.md`, the ISO/Calamares
plans, `ncde-efficiency.md`, `ncde-phased.md`, `thisisit.md`, `lepivot-gaps.md`, `wm-oracle-audit.md`,
`step3-idle-source.md`, `NCDE-RECOVERY-APP.md`, `NCDE-WM-REBUILD-PLAN.md` — none contradict the above
on architecture; flag if a later pass needs them.
```
