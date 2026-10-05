# step3-idle-source.md — give `screenIdle` a real trigger (Moksha gap #2 / zen.md "highest-leverage")

**Created session 21, 2026-06-28.** Part of the Lelan conformance work (`lelan-audit.md` §6 step 4 / §7).
Authority order unchanged: **oracle = truth**, host conforms, plan corrected where it disagrees. This step
also goes ONE intentional step beyond the oracle (Part B) — authorized by the operator's standing intent:
*"Moksha's fast/low-resource way was always the plan for Lelan."*

Work tree: `~/ncde-staging/compass7/lelan` (canonical host at the time). (2026-06-30 correction: "Test target:
`/usr/local/bin/ncde-test`" is retired — no separate test binary anymore; verify in the LaPivot tree
itself.) **(Corrected 2026-07-17: `~/ncde-staging/` no longer exists — the dev machine hosting it is
gone. There is no separate work tree anymore; verify directly against the live system —
`/usr/local/bin/LaPivot` and `/usr/share/ncde/` — see `CLAUDE.md` banner.)**

---

## The problem (verified, not assumed)

Host `AnimPolicy::screenIdle = (m_sessionLocked || m_vtInactive)` — this formula is **oracle-faithful**
(decompiled `AnimPolicy::applyScreenIdle`: `screenIdle = sessionLocked || vtInactive`; `m_screenSaverActive`
is tracked but NOT in the formula). But in the host, in practice:

- `m_vtInactive` is **never set** — the VT-active signal isn't wired from Lelan (`grep onVtActiveChanged` in
  `Lelan.cpp` = 0 hits).
- `m_screenSaverActive` is **tracked but unused** in the formula (matches the oracle).
- The host's idle source is a **D-Bus `org.freedesktop.ScreenSaver ActiveChanged`** subscription
  (`Lelan.cpp:1241`) — which on NCDE likely has **no provider**, so it never fires.

→ **`screenIdle` triggers ONLY on an explicit session lock.** Walk away / screen blanks → nothing idles.
The throttle that already keys off `screenIdle` (the WM stops the 16 ms cursor poll — `NCDEWindowManager.h`
gate `if (idle) m_pointerPoll.stop()`; AnimPolicy degrades decorative motion) sits **dormant exactly when it
should engage.** That is the efficiency gap.

## What the oracle really did (and where zen.md was wrong)

- zen.md (pre-recovery inference) guessed the idle source was an **XSync IDLETIME alarm**. The recovered
  source shows it is **X11 XScreenSaver**, not XSync.
- Oracle `NCDEWindowManager::start()`: `xcb_screensaver_select_input(m_conn, m_root, 1)`, stores
  `m_ssEventBase` (decompiled line ~1335).
- Oracle WM native event filter: on `ScreenSaverNotify` (`rt == m_ssEventBase`) →
  `AnimPolicy::onScreenSaverActivated(state == ON)` (decompiled line ~2972; `ev->pad0` byte = the `state`
  field of `xcb_screensaver_notify_event_t`).
- BUT the oracle left `m_screenSaverActive` **out of the `screenIdle` formula** → **half-built intent**: the
  signal is captured, never applied. The host WM dropped even the capture.

Consequence: a *pure* oracle conformance still wouldn't throttle on walk-away (oracle only idles on
lock / VT-switch). Reaching the Moksha goal **requires completing the oracle's own captured-but-unused
screensaver path** (Part B).

---

## Design — 3 parts, smallest-first, each independently testable

### Part A — restore the oracle's X11 XScreenSaver source in the WM  ✅ DONE (session 21)
Pure conformance, **no behavior change** (only feeds `m_screenSaverActive`; formula still ignores it).
- `CMakeLists.txt`: `pkg_check_modules(XCB_SS REQUIRED IMPORTED_TARGET xcb-screensaver)` + link
  `PkgConfig::XCB_SS`. (xcb-screensaver 1.17.0 confirmed available.)
- `NCDEWindowManager.h`: `#include <xcb/screensaver.h>`; in `start()` query the extension +
  `xcb_screensaver_select_input(m_conn, m_root, XCB_SCREENSAVER_EVENT_NOTIFY_MASK)`, store
  `m_ssPresent`/`m_ssFirstEvent`; in `nativeEventFilter`, on `rt == m_ssFirstEvent + XCB_SCREENSAVER_NOTIFY`
  call `m_animPolicy->onScreenSaverActivated(se->state == XCB_SCREENSAVER_STATE_ON)`.
- Backups: `NCDEWindowManager.h.prebak8-screensaver`, `CMakeLists.txt.prebak-screensaver`.
- **Builds clean** (xcb-screensaver found). `lelan-host` sha `7c029b7f…`. **Not yet installed (operator sudo).**
- Verify in the LaPivot tree (no separate test host anymore): log that `onScreenSaverActivated` fires when
  X blanks (e.g. `xset s activate`).
  No visible behavior change expected yet — that is correct for Part A.

### Part B — the Moksha completion: add `screenSaverActive` to the formula  ✅ DONE (confirmed in tree 2026-06-30, session 38)
`AnimPolicy.h::applyScreenIdle()` — verified live in source: `idle = m_sessionLocked || m_vtInactive || m_screenSaverActive`. Builds clean.
The ONE intentional step beyond the oracle.
- `AnimPolicy::applyScreenIdle`: `screenIdle = sessionLocked || vtInactive || screenSaverActive`.
- This is what makes walk-away/blank actually throttle (cursor poll pauses, anims degrade). Completes the
  oracle's captured-but-unused data + delivers Moksha gap #2.
- **Risk + mitigation:** if the X screensaver timeout is short, the cursor poll could pause while you are only
  briefly idle → slight lag on return. Resume fires on the first input event (`ScreenSaverNotify` OFF). Set a
  sane timeout (`xset s <secs>`) and verify resume feels instant.

### Part C — stretch the heartbeat when idle  ⬜ SUPERSEDED (confirmed 2026-06-30, session 38)
Original idea (stretch `onPulse` 1s→~4s on idle) was NOT built as such. Instead Lelan grew a proper
`deferWhenIdle()`/`m_idleQueue`/`drainIdleQueue()` work-deferral system (`Lelan.cpp:71-75,211-224`) — heavy
work queues and drains via a 250ms `CoarseTimer` only when the screen is idle/active, rather than slowing
the one shared coalesced heartbeat wholesale. This looks like an intentional, better design (per
`ncde-moksha-efficiency-benchmark`, referenced in `Lelan.h` but not found as an actual doc file — possibly
never written, or lost; flagging as a doc gap) rather than a leftover gap — no action taken here.

### Folded-in oracle-conformance fix — wire the missing VT-active  ✅ DONE (confirmed in tree 2026-06-30, session 38)
`Lelan_System.cpp:449` (`onSessionActiveChangedSlot`) calls `m_animPolicy->onVtActiveChanged(m_sessionActive)`
off the logind `org.freedesktop.login1` session `Active` PropertiesChanged signal. Not in `Lelan.cpp` —
that's why earlier greps of that file alone missed it.

---

## Open decisions
1. **Part B — include `screenSaverActive` in `screenIdle`?** rec: YES (the whole point).
2. **Drop the dead D-Bus `org.freedesktop.ScreenSaver` subscription** once the X source is in, or keep as
   inert fallback? rec: keep (harmless).
3. **Wire the missing VT-active** now? rec: YES (oracle conformance).
4. **Part C heartbeat stretch** — now or defer? rec: defer until A/B verified.

## Sequence (one change at a time, build-verify each)
A (WM XScreenSaver — **done**) → VT wiring → B (formula — the behavior change; test walk-away + cursor
resume) → C (later).

## Build deps
- `xcb-screensaver` 1.17.0 (added to CMakeLists). No others.

## Records / provenance
- Oracle: `~/ncde-wm-rebuild/src/decompiled/{NCDEWindowManager.c,AnimPolicy.c}` (corrected 2026-07-17:
  path moved off the now-gone `~/ncde-staging/`).
- Moksha research (session 21) + sources: `lelan-audit.md` §7.
- zen.md "EFFICIENCY GAPS" still references the removed `setPulseScale`/`setScreenIdle` — owed Category-D
  doc correction; supersede with this idle-source model.
