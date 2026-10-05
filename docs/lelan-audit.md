# lelan-audit.md — Host `Lelan` vs the recovered real `LElan` (the oracle) vs the plan

**Created 2026-06-28 (session 18).** Task (operator): *"do the Lelan audit against the plan — and
Lelan must conform to what we find. That is the whole point of recovering the source."*

> **⚠️ PATH CORRECTION (2026-07-17):** `~/ncde-staging/` — and everything under it referenced below
> (the ORACLE decompile, the HOST `compass7/lelan` tree, the staged QML copy) — no longer exists on
> this machine or the USB backup; the dev machine that hosted it is gone. The paths below record
> where these things lived when this audit was written (2026-06-28) — read them as history, not
> current locations. Current reality: the oracle-recovery work now lives in `~/ncde-wm-rebuild/`
> (Ghidra-decompiled from the live `/usr/local/bin/LaPivot` binary — partial, most classes still raw;
> see `docs/lapivot-rebuild.md`); there is no separate HOST tree anymore, the live running system IS
> the host; shipped QML is live at `/usr/share/ncde/` (never lost). The audit's *findings* (Categories
> A-D, the conformance plan) are unaffected — only the workflow paths below are stale.

**Authority order (operator-set):**
1. **ORACLE = `~/ncde-staging/ncde-wm-rebuild/src/decompiled/LElan.c`** (4835 lines, 145 real methods,
   2026-06-28 location — gone now, see banner above; current equivalent work is in `~/ncde-wm-rebuild/`) —
   the recovered real source. **This is the truth. The host conforms to it.**
2. **HOST = `~/ncde-staging/compass7/lelan/Lelan.{cpp,h}`** (1871 + 456 lines, 2026-06-28 location —
   gone now, see banner above; there is no separate host tree anymore, the live system is it) — the
   reduced reimpl. **Must be brought into conformance with the oracle.**
3. **PLAN = `lelan.md` / `missing.md` / `NCDE-LELAN-PLAN.md`** — written **before** the source was
   recovered (reconstructed by inference from `strings`). **Where it disagrees with the oracle, the plan
   is WRONG and gets corrected — do not conform the code to the plan.**

> Method: mechanical symbol inventories (grep — evidence, not paraphrase) + targeted body reads +
> cross-check against the actual shipped QML (staged then at `~/ncde-staging/LaPivot/usr/share/ncde`,
> gone now — the real live path is `/usr/share/ncde`, never lost). Items I have
> not yet read the *body* of are tagged **[NEEDS BODY READ]** — honest, not asserted.

---

## 0. The single most important structural fact (changes how severe everything else is)

**The shipped QML binds `lelan.*` ZERO times.** (verified: `grep -r 'lelan\.' usr/share/ncde` = 0 hits.)
System data reaches the desktop two ways only:
- **`widget_data.*`** — fed by the C++ feed object (`WidgetData.h` in the host; `DesktopWidget.c` in the
  oracle). 25+ granular keys: `widget_data.batteryLevel`, `.mediaTitle`, `.volume`, `.mountedVolumes`, …
- **`ncde.*`** — **theme/color tokens ONLY** (`ncde.gilt` 295×, `ncde.accent` 263×, `ncde.glow`, fonts).
  Confirms **NCDEEngine = colors only**; it carries no system data. ✅ (matches the architecture rule.)

**Consequence:** Lelan's property *shape* (granular vs map) does **not** break QML directly — the seam that
matters is **Lelan → WidgetData/DesktopWidget**. So conformance is a *code-faithfulness* problem at that
seam, not a QML-rewrite problem. Good news: fixing Lelan to match the oracle won't disturb the QML.

---

## 1. Inventory — oracle 145 methods vs host coverage

- Oracle real methods: **145**. Host defined methods (cpp): **129**. Host Q_PROPERTY: 42; signals: ~63.
- **70 oracle methods have no name-match in the host** — but most are *aliases* or *property-getters the
  host reshaped*, not true gaps. Reconciled below into real categories.

---

## 2. CATEGORY A — Structural divergences (host reshaped the oracle; conform back)

| # | Oracle (truth) | Host (now) | Verdict |
|---|---|---|---|
| A1 | **Granular Q_PROPERTY scalars**: `batteryPercent`(double), `batteryCharging/Full`(bool), `batteryTimeToEmpty/ToFull`, `hasBattery`, `mediaTitle/Artist/Album/ArtUrl/Duration/Position/TrackId/Volume/Playing`, `audioVolume`(int)/`audioMuted`, `networkOnline`, `vpnActive`, `fontScaleFactor`, `screenGeometry` | **Aggregate maps**: `battery`, `media`, `audio`, `network`, `vpn`, `location`, `clock` (+ a `WidgetData` adapter that re-flattens maps → granular `widget_data.*`) | **Conform to oracle granular getters.** The host added a whole adapter layer (`WidgetData` maps→scalars) to undo a reshape the real code never did. The oracle fed `DesktopWidget` granular directly. |
| A2 | **`setSettings(Settings*)`** — config delegated to a separate `Settings` class | Host self-manages config: `readConfig/writeConfig/configDir/configPath/loadConfig/saveConfig` inside Lelan | **Conform:** real LElan does NOT own config I/O — `Settings` does. Move config out of Lelan, wire `setSettings`. (Oracle also has `Settings.c` recovered — use it.) |
| A3 | **`setAnimPolicy(AnimPolicy*)`** on LElan — LElan holds + drives AnimPolicy | Host wires AnimPolicy via `main.cpp`/WM (`setAnimUtilClamp`, `recomputeAnimLevel`, `updatePressure`) but has no `setAnimPolicy` injector on Lelan itself | **Conform:** adopt the oracle's `setAnimPolicy` pointer-injection so Lelan governs AnimPolicy as the real code did. |
| A4 | Subscriptions are **split per service**: `subscribeToHostname1` + `subscribeToLocale1` + `subscribeToTimedate1`; `subscribeToUDisks2` + `subscribeToUDisks2Filesystem`; `subscribeToVpn` + `subscribeToVpnConnection`; `subscribeToSessionLock` + `subscribeToVtActive` separate from `subscribeToLogind`; `subscribeToPlayer(name)` + `unsubscribeFromPlayer` + `subscribeToSink` | Host **merged**: `subscribeToHostnameLocale`, `subscribeToTimeDate`, one `subscribeToUDisks2`, VPN folded into connect/refresh, one `subscribeToScreenSaver`, `subscribeToPlayers`/`fetchPlayer` | **Mostly cosmetic** if behavior matches — but the oracle's split is finer (e.g. separate VT-active + session-lock watches the recovery handoff depends on). Verify each merged one still does everything the two oracle halves did. **[NEEDS BODY READ per pair]** |

---

## 3. CATEGORY B — Host INVENTIONS (in host, not in the oracle) — keep, verify, or drop

Per the directive, anything not in the oracle is an invention that must be **justified as a verified
upgrade** or removed.

### B1 — KEEP (verified upgrades the operator wants; the oracle was read-only here)
- **WiFi control:** `connectWifi/disconnectWifi/setWifiEnabled/subscribeToWifi/onWifiPropertiesChanged/
  rebuildAccessPoints/readActiveNetwork`. The oracle only *reads* NM (`subscribeToNetworkManager/
  onNmPropertiesChanged/scanActiveConnections`). **This is the host's headline good change (WiFi works).**
  Keep — but fold it onto the oracle's NM subscription rather than a parallel stack. **[verify no double-subscribe]**
- **Bluetooth control:** `bluetoothConnect/Disconnect/Pair/Remove/Scan/setBluetoothEnabled/
  setBluetoothDiscoverable/rebuildBluetooth` (oracle BlueZ is read-only). Keep as upgrade.
- **Control-center writes:** users (`addUser/removeUser/setUserAdmin/setUserAvatar/changePassword/
  setAutoLogin`), printers (`refreshPrinters/removePrinter/setDefaultPrinter`), time
  (`setTimezone/setNtp`). **The oracle has NONE of these.** Architecturally consistent with "Lelan owns
  system work," BUT in the real system these writes were **not** in LElan. **DECISION NEEDED (operator):**
  keep in Lelan (convenient, ncde-command needs them) vs. they belonged elsewhere. Likely keep — flag only.

### B2 — WRONG invention; REPLACE with the oracle's real model
- **`applyIdleState` / `setPulseScale` / `stopPulse` / `onPulse` / `onCoalescedTick`** = the session-16b
  idle/throttle invention. **The real LElan has none of it.** The oracle's real mechanism is
  **`leanSleeping` / `leanWaking` / `deferWhenIdle` / `drainIdleQueue`** (an idle *work-queue* — defer work
  while idle, drain on wake) + AnimPolicy owning `screenIdle` internally. **This already bit us** (the
  invented `applyIdleState→setScreenIdle` caused the cursor freeze, session-17). **Conform:** rip out the
  invented pulse-scale model; port the oracle's lean/defer-queue. **[NEEDS BODY READ of oracle leanSleeping/
  leanWaking/deferWhenIdle/drainIdleQueue to port faithfully]**

  > **THIS IS THE MOKSHA GOAL (operator, 2026-06-28).** The real goal: make Lelan behave like **Moksha** —
  > NCDE always fast, low-resource, works equally on old and new hardware, *while staying beautiful* — but
  > built as a **Qt6/X11 desktop, NOT Enlightenment**. Moksha's "work-on-change, defer/sleep when idle,
  > stay light" model **IS** the oracle's `leanSleeping/leanWaking/deferWhenIdle/drainIdleQueue`. So
  > conforming to the recovered source here is *exactly* the efficiency mission — the real code already
  > implemented the Moksha behavior the invented `setPulseScale` model only half-faked. Port the real one.
  > (Pairs with `ncde-efficiency.md`; memory [[ncde-moksha-efficiency-benchmark]].)

  > **CORRECTION (session 21, 2026-06-28) — this bullet over-reached.** Only `applyIdleState`/`setPulseScale`
  > were the wrong throttle invention (already removed from the host — `Lelan.cpp` confirms). The
  > **`onPulse`/`onCoalescedTick` 1s coalesced heartbeat is RECLASSIFIED to B1 (KEEP).** It is the
  > timer-coalescing QoS knob (zen.md §2 [E], "one `Qt::CoarseTimer` (leeway/coalescing)") and the Moksha
  > `ecore_poller` pattern (one ticker fanning out at integer multiples, coalesced wakeups — sourced in §7).
  > It is **better than the oracle**, which used ~5 separate DesktopWidget timers (decompiled `clockTimer/
  > statsTimer/weatherTimer/updatesTimer/moonTimer`); the host coalesced them into one. Do NOT strip it.
  > (`stopPulse` is unrelated audio teardown — name collision, not the throttle.)

### B3 — UNVERIFIED invention vs the oracle (flag hard)
- **Sentinel↔Lelan:** host has `subscribeToSentinel` + 9 `onSentinel*` (Audio/Battery/Display×2/Input×2/
  Network/Usb×2). **The recovered LElan has ZERO Sentinel references** (`grep -ic sentinel` = 0). So the
  real shipped LElan did **not** integrate Sentinel. This contradicts `lelan.md §4` (which lists a Sentinel
  row) AND the architecture metaphor (Sentinel = Tía, feeds Lelan). **Possible explanations:** (a) Sentinel
  wiring postdates the prebak binary; (b) it was always intent, never shipped. **DECISION NEEDED:** is
  Sentinel-feeds-Lelan a real intended upgrade to keep, or scope the host never should have added? Do not
  silently keep it just because it compiles.

---

## 4. CATEGORY C — Real functional GAPS (oracle has it, host lacks it; add by porting the oracle)

| Oracle method(s) | What it does | Host status |
|---|---|---|
| `leanSleeping` / `leanWaking` / `deferWhenIdle` / `drainIdleQueue` | the real idle work-queue / App-Nap | **MISSING** (host invented a different one — see B2) |
| `onBacklightEvent` / `brightnessChanged` | screen-brightness handling | **MISSING** entirely |
| `activePlayerService` / `computeActiveService` / `unsubscribeFromPlayer` / `onNewSink` / `onSinkRemoved` / `retryFallbackSink` | robust multi-player + multi-sink audio (pick active player, re-point on default-sink loss) | host has only `fetchPlayer`/`applyPlayerProps`/`onFallbackSinkUpdated` — **robustness gap** |
| `tryGeoClue2` / `onGeoClue2ClientReady` | GeoClue2 client-ready/retry handshake | host `subscribeToGeoClue`/`onGeoClue2Location` only — **partial** |
| `solarEvents` | solar (sun position) computation feeding night-light/sky | host has `scheduleNightLightEvents` but not `solarEvents` — **partial** |
| `timeJumped` | clock-jump detection (resume/NTP step) | **MISSING** |
| `monoRawMs` | monotonic-clock helper (drift-free timing) | **MISSING** (host likely uses QDateTime) |
| `handleVpnStateChanged` / `subscribeToVpn` / `subscribeToVpnConnection` | VPN state subscription model | host reshaped to connect/refresh/markActiveVpns — verify parity |
| `lowMemoryWarning` (signal) | emitted to QML on portal LowMemoryWarning | host has `onLowMemoryWarning` slot — verify it re-emits |

**[All Category C ports NEED BODY READS of the oracle method before writing host code — no guessing.]**

---

## 5. CATEGORY D — Plan-doc (`lelan.md`) corrections (conform the PLAN to the oracle too)

The operator's directive applies to the docs, not just the code. `lelan.md` is pre-recovery inference and is
**wrong** in these places:

- **§1 "ships as `lelan-host`, a standalone D-Bus companion daemon registering `io.ncde.Lelan`, ncde-wm
  connects over D-Bus."** ❌ The oracle confirms LElan was **compiled into ncde-wm** (no standalone daemon,
  no `io.ncde.Lelan` service). The current plan (thisisit.md / unified host) also has Lelan IN-process.
  **Correct §1** to the in-process model.
- **§4/§5 audio = `org.PulseAudio.Core1`.** ❌ Oracle has **0** Core1 references (and 0 obvious `pa_*`
  libpulse symbols — decompiled external calls may be opaque; **[NEEDS BODY READ of oracle `subscribeToSink`/
  `fetchAudioState` to name the real backend]**). Either way the Core1 claim is dead (memory already says so).
- **§4 `subscribeToSentinel` row.** ❌ Not in the oracle (see B3). Mark as intent/unverified, not [E].
- **§10 skeleton uses `QVariantMap battery/media/audio/network`.** ❌ Oracle uses **granular scalars**
  (A1). The host copied the map skeleton from here — this doc *caused* the divergence. **Correct the
  skeleton** to granular getters.

---

## 6. Conformance work plan (ordered; each step = read oracle body → backup → one change → diff → rebuild)

1. **Port the real idle model** (B2/C): oracle `leanSleeping/leanWaking/deferWhenIdle/drainIdleQueue`;
   remove the invented `applyIdleState/setPulseScale`. (Highest value — already caused a real bug.)
2. **Restore granular property getters** (A1) + simplify/retire the WidgetData map→scalar adapter to match
   the oracle's direct granular feed. (Verify `widget_data.*` keys still resolve.)
3. **Move config to `Settings`** (A2) + wire `setSettings`; wire `setAnimPolicy` (A3).
4. **Fill functional gaps** (C): backlight/brightness, audio active-service/multi-sink robustness, GeoClue2
   client-ready, solarEvents, timeJumped, monoRawMs.
5. **Reconcile merged subscriptions** (A4) — confirm each host merge covers both oracle halves.
6. **Decide on inventions** (B1 keep / B3 Sentinel decision) with the operator.
7. **Correct `lelan.md`** (D) to the oracle.

**Discipline:** never conform to the plan; conform to the oracle. Read the oracle method body before porting
(no inference). One change at a time, build-verify each, system files via operator sudo, never edit
`[dead-legacy-tree]` directly. Aesthetic untouched (this is all backend/data).

---

## 7. Conformance PROGRESS + Moksha grounding (session 21, 2026-06-28)

**Work tree (2026-06-28, superseded 2026-07-17 — this tree is gone, the dev machine that hosted it is
gone; no `cmake --build` from a checked-out tree exists anymore).** Current: fixes are ported into
`~/ncde-wm-rebuild/` class-by-class from the Ghidra-decompiled live `/usr/local/bin/LaPivot` (partial,
most classes still raw — see `docs/lapivot-rebuild.md`), and deployed live via
`~/my-project/files/ncde-full-patch-20260711.sh`.

**(2026-06-30 correction: "Test target = `/usr/local/bin/ncde-test`" is retired — no separate test binary.
The build IS LaPivot; verify in the tree itself, don't install to a parallel test path.)**

### Step 1 (idle model, B2/C) — AUDITED + first fix DONE
Verified against the oracle bodies (`LElan.c`) — the host had ALREADY ported most of step 1:
- ✅ `deferWhenIdle` (enqueue + start timer) — conformant (`Lelan.cpp:1613`).
- ✅ `leanSleeping`/`leanWaking` — present (`Lelan.h:262-263`), triggered by `onPrepareForSleep(goingToSleep)`
  exactly like the oracle (stop media timer + `leanSleeping` on sleep; re-subscribe + `leanWaking` on wake).
- ✅ `applyIdleState`/`setPulseScale` — already removed.
- ✅ **1s heartbeat** (`onPulse`/`onCoalescedTick`) — **KEEP** (see B2 correction; Moksha `ecore_poller`).
- 🔧 **DONE — ioprio conformance fix (session 21).** Oracle `drainIdleQueue` wraps each deferred job in
  `ioprio_set` IDLE-class (`0x6007` enter / `0x4004` restore), gated on BFQ (`m_bfqActive`); zen.md §2 [E]
  agrees ("ioprio IDLE … when draining deferred-idle work queue"). The host had it WRONG — it pinned the
  WHOLE process to IDLE I/O at startup (`applyZenStartupHints`), which can starve Lelan's own sysfs/config
  reads. **Fix (staged, builds clean):** removed the startup pin; added a BFQ-gated `IdleIoScope` RAII guard
  around the job in `drainIdleQueue` (restores best-effort even if the job throws). Files: `Lelan.cpp`
  (`detectBfqScheduler`+`IdleIoScope`, ctor detect, `drainIdleQueue` wrap, `applyZenStartupHints` note),
  `Lelan.h` (`m_bfqActive`). Backups `*.prebak-ioprio`. Build sha `a9d9deca…`. **Not yet installed (operator sudo).**

### Moksha research (delegated web research, session 21) — sources for the efficiency decisions
Moksha = Bodhi's Enlightenment-E17/EFL fork. Verified mechanisms (URLs in the research record):
- **`ecore_poller`** — one base ticker (`ECORE_POLLER_CORE`, 1/8 s) drives many pollers at integer
  power-of-2 multiples; "share a single timer per type… main loop woken once… CPU sleeps longer." → our
  heartbeat IS this pattern. (Refinement available: power-of-2 tick buckets vs our arbitrary K.)
  `https://docs.enlightenment.org/auto/group__Ecore__Poller__Group.html`
- **`ecore_animator`** rides one `frametime` tick (1/30 s); `ecore_animator_frametime_set()` = the global
  throttle knob.
- **`e_powersave`** — 6 levels NONE→FREEZE; deeper level *lengthens* poller/animator intervals (doesn't kill
  features); `Efl.Loop.throttle` injects per-iteration sleep for deeper C-states.
  `https://raw.githubusercontent.com/efl-dev/enlightenment/master/src/bin/e_powersave.h`
- **Suspend/resume** via logind (libsystemd/elogind) — matches our `leanSleeping/leanWaking`.
- **Evas** = retained-mode scene graph (skips obscured/unchanged, partial updates, GL/SW selectable).
- **I/O niceness:** **no** evidence EFL/Moksha use `ioprio`/`nice`/autogroup — our zen ioprio/SCHED_FIFO is a
  macOS-QoS-derived addition (zen.md §6), beyond Moksha but sound; BFQ-only gate is technically correct
  (`https://docs.kernel.org/block/ioprio.html`).

**Verdicts:** heartbeat (a) KEEP · idle work-queue (b) KEEP, polarity correct (run when awake+powered) ·
per-job IDLE-I/O (c) KEEP (beyond Moksha; BFQ gate sound) · lean sleep/wake (d) KEEP · AnimPolicy levels (e) KEEP.

### Top-3 Moksha gaps to ADD (step 3+ — beyond the oracle, operator-approved direction "Moksha was always the plan")
1. **Throttle the base tick + render frametime per powersave level** (not just anim quality): in EXTREME/FREEZE
   stretch the 1s heartbeat (→2-4 s) and raise QML render frametime so the CPU genuinely wakes less.
2. **Enter FREEZE on DPMS/screen-blank, not only logind suspend** — stop heartbeat/animators while the box is
   awake-but-dark. ⇐ converges with zen.md "ADD an X11 idle source (XSync IDLETIME alarm) — highest-leverage."
3. **Be event-driven where we poll** — clock = one-shot aligned timer; battery/thermal/cpufreq via
   udev/upower change events, not unconditional 1s sampling (E moved battery to event + coarse 10 s).

→ **NEXT (with operator): step 3 = the idle/DPMS source** (gaps #2 + zen.md highest-leverage), designed together.

### Doc corrections still owed (Category D)
- `zen.md` "EFFICIENCY GAPS" still references the removed `setPulseScale`/`setScreenIdle` — stale; rewrite to
  the leanSleeping/deferQueue model + the idle-source plan.
- `lelan.md` §1/§4/§5/§10 corrections (D) — unchanged, still owed.
