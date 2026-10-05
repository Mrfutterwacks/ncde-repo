# commercial.md — NCDE Poseidon: Production-ISO Readiness Fix Plan

> **🔴 SESSION 71 SPOT-CHECK (2026-07-05, operator: "make sure it is correct.. since agents made
> it"):** this doc was UNREACHABLE from CLAUDE.md's Tier-2 index (same lockout that hit
> sentinel-plan.md/FLUTTER-PLAN.md this session) — now indexed, see CLAUDE.md. A representative
> sample was re-verified against the CURRENT production tree, not trusted from the doc: **B-F5
> (Sentinel/Lelan bus mismatch) is STALE — already fixed 2026-07-01** (Sentinel's own `__main__.py`
> comment: "Confirmed 2026-07-01: this was SessionBus() here... now `dbus.SystemBus()`", matching
> Lelan's `systemBus()` subscription exactly); this session's own full Lelan/Sentinel/Zen audit
> independently found NO blockers in this chain. **B-F4 (stale 6.8KB Sentinel binary) describes an
> ARCHITECTURE THAT NO LONGER EXISTS** — `usr/local/bin/ncde-sentinel` is now a 394-byte thin
> launcher (`from sentinel.__main__ import main`) into the real `usr/local/bin/sentinel/` package
> this session extensively audited/patched (hw_tier, pwm_guard, UID guards, shutdown handler — all
> real). **B-F1 (5 IMFell fonts are HTML saves) is STALE — fixed session 57**, confirmed via `file`:
> all 5 are genuine TrueType data. **The "wire dead highContrast" quick-win is STALE — fixed
> session 67**, confirmed live in `NCDEKit.qml`. **CONFIRMED STILL OPEN, real:** B-S1 (no QML
> control consumes `animPolicy.instant`/`reduceMotion` — `NCDEToggle.qml` etc. grep clean, zero
> hits) and B-F2 (`ncde-x11-session` runs LaPivot once in the foreground with zero respawn loop —
> confirmed by reading the actual script; any crash, not just clean logout, ends the session with
> no distinction). **Everything else below (B-S2/B-S3/B-I1/B-I2/B-F3 and the full quick-win/
> high-impact/strategic lists) was NOT independently re-verified this pass — treat as unconfirmed,
> not as either true or stale, until checked against the tree.** Merged into the master list:
> `PRODUCTION-PUNCHLIST.md`.
>
> **"Commercial" = the QUALITY BAR, not a product for sale.** NCDE should be *as good as a commercial OS*
> (macOS/Windows-grade), distributed to family/synagogue. So legal items are **license-compliance / Rule-7 /
> credibility**, not sales obligations.
>
> **Source:** final pre-production-ISO audit — 3 workflows, ~70 agents (organism `wjl2r7p9c`, commercial
> follow-up `wspulr0y9`, ISO web `a9312598`). Verdict: **NOT-YET**. Every item below is evidence-backed,
> conforms to NCDE as-built, and was adversarially verified or self-corrected — AT THE TIME IT WAS
> WRITTEN. See the session-71 spot-check banner above before trusting any specific item.

## Binding constraints on every fix
- **Aesthetic is SACROSANCT** — pixel-identical; change HOW not WHAT. Never touch lampPulse timing or the MPRIS scrubber without sign-off.
- **Conformance gate** — only fixes that fit NCDE's real stack (Qt6/QML/X11/picom, Lelan C++, NCDEEngine=colors-only, **Calamares** installer — *Isla is abandoned*, GUI-only/no-terminal, offline/local). No invented APIs/files; NCDE components are bespoke.
- **Process** — read → back up → ONE change → diff → rebuild/verify. Never sudo (hand operator `! sudo …`). Never edit `[dead-legacy-tree]` directly (stage; operator applies). Accessibility + epilepsy-safety = SAFETY.
- **Vesper = NON-LLM** (deterministic `brain_server.py`); branded **GRUB+Plymouth boot = sacrosanct** (harden for Secure Boot, never strip).

---

## 🔴 RELEASE BLOCKERS

### Safety (the point of NCDE)
- [ ] **B-S1 · Reduce-motion does nothing desktop-wide.** No QML consumes `animPolicy.instant`/`reduceMotion`; controls animate unconditionally (NCDEToggle.qml:19,32; NCDEButton.qml:32; NCDESlider.qml:38; NCDEField.qml:32; NCDECheck.qml:28; NCDEProgressBar.qml:25). **Fix:** gate `Behavior`/`loops:Infinite` on `!animPolicy.instant` (pixel-identical when off). Toggle already reaches engine (AccessibilityTab.qml:50 → Lelan.cpp:1631). *Risk: wide but additive.*
- [ ] **B-S2 · First-run never surfaces accessibility.** A blind user can't enlarge text before reaching Settings. **Fix:** first-login accessibility step writing existing keys (`accessibilityTextScale`, `reduceMotion`, `highContrast`, `largerCursor`) with the live "Sample Ag" preview AccessibilityTab.qml already has; consider `reduceMotion=true` default. **Launch via `ncde-x11-session` + flag-file — NOT an autostart `.desktop` (ncde-wm ignores /etc/xdg/autostart).** *Risk: med.*
- [ ] **B-S3 · lampPulse can exceed 3 flashes/sec on <~600px windows** (WCAG 2.3.1; MotifFrame.qml:126-127, period ∝ windowW^-0.49). **Fix:** lower-bound period clamp (normal windows unchanged). **⚠ REQUIRES operator sign-off + side-by-side visual** (lampPulse rule). *Risk: governance.*

### Identity / hide-Arch (Rule-7)
- [ ] **B-I1 · ISO volume label still `ARCHCRAFT`.** NCDE-BUILD-COMMANDS.md:70-71,114,129-131 (`-V 'ARCHCRAFT_202605'`, archcraft branding dir + archcraft.db). **Fix:** re-author volid `NCDE_POSEIDON`; purge archcraft branding/db; fix `archisolabel`. (Caused prior boot/plymouth leaks.) *Risk: low-med.*
- [x] ~~**B-I2 · Firefox leaks "for Arch Linux."** `usr/lib/firefox/distribution/distribution.ini` (`about=Mozilla Firefox for Arch Linux`, `id=archlinux`, `app.partner.archlinux`). **Fix:** ship unbranded build / strip partner config.~~
      **CLOSED — fixed + deployed live, 2026-07-17:** `distribution.ini` rebranded (`id=ncde`,
      `about=NCDE`, distributor keys dropped). Made durable with a pacman hook
      (`/etc/pacman.d/hooks/01-ncde-firefox-debrand.hook`) that reapplies it after every future
      Firefox update, since the file isn't in firefox's `backup=()` array and would otherwise
      silently revert. Folded into `ncde-full-patch-20260711.sh` as step 11/11.

### Function / quality
- [x] ~~**B-F1 · 5 bundled fonts are saved HTML pages, not TTF.**~~ **CLOSED — fixed session 57,
      re-confirmed 2026-07-05:** `file` on all 5 shows genuine TrueType data, correct family names.
- [ ] **B-F2 · WM crash ejects the whole session** (`ncde-x11-session:89`, foreground, no loop). Any ncde-wm segfault drops the user to login + loses work. **Fix:** CRASH-ONLY guarded respawn (distinguish clean logout rc 0 from crash; never a naive `while true`). *Risk: low / impact high.*
- [ ] **B-F3 · Printer "Add" opens the CUPS web admin** (PrintersTab.qml:106,152 `Qt.openUrlExternally("http://localhost:631/admin")`) — unstyled tech page, admin auth, driver choice = breaks no-terminal promise. **Fix:** native "Nearby printers" via new `Lelan discoverPrinters()` (browse `_ipp._tcp` over enabled Avahi) + `lpadmin -p <name> -E -v <uri> -m everywhere` (driverless) using Lelan's existing QProcess. *Risk: med / impact high.*
- [x] ~~**B-F4 · ISO ships the STALE Sentinel.**~~ **OBSOLETE — the monolithic-binary architecture
      this describes no longer exists.** `usr/local/bin/ncde-sentinel` is now a 394-byte launcher
      into the real `usr/local/bin/sentinel/` Python package (hw_tier/pwm_guard/UID-guards/shutdown
      handler, all built and verified this session). Nothing to fix here.
- [x] ~~**B-F5 · Sentinel→Lelan BUS MISMATCH.**~~ **CLOSED — fixed 2026-07-01, re-confirmed
      2026-07-05.** Both sides on `SystemBus`/`systemBus()`; Sentinel's own code comments the exact
      prior bug and its fix. All 4 sensing handlers (ThermalChanged/FanChanged/ThermalCritical/
      DriverMissing) confirmed wired in this session's own full Lelan/Sentinel/Zen audit — NO
      BLOCKERS found. `checkThermalZones()` local watchdog confirmed still in place, unchanged.

---

## 🟢 QUICK WINS (one-file, low risk)
- [ ] ~~Battery "charging" enum bug — Lelan.cpp:1654 (`state.toUInt()==1`; oracle LElan.c:4306). 1 line.~~
      **WRONG CITATION (found 2026-06-30 night) — line 1654 in `[dead-legacy-tree]/src/Lelan.cpp` is unrelated
      CPU sched code; `grep -n "toUInt"` finds the real battery-state logic at lines 247/1697, both
      using `==2` for Discharging, no `==1` charging-bug pattern anywhere in the file. Either already
      fixed or the citation was wrong from the start — do not "fix" this without re-locating the actual
      bug first.
- [x] ~~**X save-set** on reparented clients — NCDEWindowManager.h:738 insert + DELETE in `destroyFrameWindow` (~:367). Else a WM crash kills every open app.~~
      **CLOSED — re-verified live, 2026-07-17:** the deployed `/usr/local/bin/LaPivot` binary genuinely
      imports and calls `xcb_change_save_set` alongside `xcb_reparent_window` (confirmed via `objdump -T`).
      A prior false negative came from searching for the Xlib name (`XAddToSaveSet`) on a binary that
      actually links XCB, not Xlib, for this call.
- [ ] 204 hardcoded `font.pixelSize` → route through existing `theme.scale()` (ThemeTokens.qml:50). Pixel-identical until scaled = global text scaling.
- [x] ~~Wire dead `highContrast` toggle (Settings.h:86/410/420) into NCDEKit.qml ink/bg.~~
      **CLOSED — fixed session 67, re-confirmed 2026-07-05:** live in `NCDEKit.qml`'s ink derivation.
- [ ] Touch targets ≥24px — NCDECheck.qml (20×20/22px), NCDESlider knob 18×18.
- [x] ~~**Bluetooth `AutoEnable=true`** — uncomment etc/bluetooth/main.conf:365 (radio off at boot otherwise).~~
      **CLOSED — re-verified live, 2026-07-17:** `AutoEnable=true` confirmed uncommented and active in
      the live `/etc/bluetooth/main.conf`.
- [x] ~~Respawn **picom + polkit** in `ncde-x11-session` (lines 42,49) — `( while :; do …; sleep 1; done ) &`. **Preserve the GL-renderer `--backend` probe** (static ExecStart reintroduces the GLX freeze). picom death = silent loss of all glass.~~
      **CLOSED — re-verified live, 2026-07-17:** the deployed `/usr/local/bin/ncde-x11-session` has a real
      `ncde_respawn` crash-recovery loop (respawn on nonzero exit only, `kill -0` session guard, gives up
      after 5 rapid failures) wrapping both `picom --backend "$picom_backend"` (with the GL-renderer probe
      intact) and `xfce-polkit`. Confirmed both processes live via `pgrep`.
- [x] ~~Drop misconfigured **Timeshift** `.desktop` (rsync-mode, schedules off) — Soundings is the single restore path.~~
      **CLOSED — fixed + deployed live, 2026-07-17:** the 2026-07-10 attempt made a byte-identical
      decoy copy (`.ncde-hidden-20260710`) that never actually hid anything — files not ending in
      `.desktop` aren't scanned by XDG menus either way, and the real file was untouched. Real fix
      this time: `NoDisplay=true` added to the actual live `timeshift-gtk.desktop`, decoy renamed
      aside (not deleted), made durable with a pacman hook
      (`/etc/pacman.d/hooks/02-ncde-timeshift-hide.hook`) since the file isn't in timeshift's
      `backup=()` array. Folded into `ncde-full-patch-20260711.sh` as step 12/12.
- [ ] Calamares `removeuser` module — kill the phantom "live" account at greeter (NCDE-CALAMARES-PLAN.md:117-120).
- [ ] GRUB theme path `starfield → ncde` in the Calamares post-install (chrooted_post_install.sh:282 vs tree).
- [ ] Disable stale `ncde-recovery-vt.service WantedBy=multi-user.target` (use autovt@tty8 on-demand).

---

## 🟡 HIGH-IMPACT (extend existing patterns)
- [ ] **Auto update-notifications** — `ncde-check-updates.timer`+`.service` (daily → org.freedesktop.Notifications + panel badge). Backend already in ncde-command. (Keep repo labels out of text — Rule-7.) Else a non-tech user never updates.
- [ ] **Pre-update real SNAPSHOT** (not just a mark). *Isla abandoned → Calamares `ncde-snapshot` (btrfs, /restore/@restore) is the canonical snapshotter; ignore the dead isla rsync path.* Wire a libalpm PreTransaction hook to take a fresh pre-update snapshot.
- [ ] **Bluetooth pairing** — register `org.bluez.Agent1` in Lelan (passkey → QML confirm dialog; needed for keyboards/braille/hearing aids) + branch BluetoothTab.qml:101 on `paired` to call existing `Lelan.cpp:770 bluetoothPair`.
- [ ] **Lelan self-heal** — `onNameOwnerChanged` (Lelan.cpp:1590-1600) re-subscribes only 4 of ~18 services (oracle LElan.c:2204-2302). Restore the oracle-conforming selective set (NM/offline, BlueZ, UDisks2, PackageKit, PowerProfiles, audio).
- [ ] **WiFi** — NetworkTab.qml:288 is password-only. Add WPA-Enterprise identity + captive-portal auto-open (extend Lelan.cpp:441+ NM code).
- [ ] **Harden the branded GRUB theme for Secure Boot** — sign/ensure theme fonts+modules load under SB; test SB-ON; keep a known-good fallback entry. **KEEP the theme (sacrosanct).** Plymouth complements the chain.
- [ ] **License browser in About** — AboutTab.qml only prints "Qt 6 · X11/XCB"; add a "Licenses / Open-Source Credits" view bundling Qt LGPL + the 551 `usr/share/licenses` texts (GUI-only). Add a master `COPYING.NCDE` + NCDE copyright line.

---

## 🔵 STRATEGIC / post-1.0
- [ ] Atomic update + auto-rollback (greenboot-style boot-counter; staged-subvolume set-default) — the one failure a blind user can't reach Ctrl+Alt+R for. Uses btrfs NCDE already has. (Today's pacman updater WORKS — enhancement, not a gap.)
- [ ] GitHub/overlay update repo (operator roadmap; pacman functional now).
- [ ] Scanners — `sane-airscan` (driverless eSCL over the same Avahi) + a Scanners section in PrintersTab.
- [ ] Reproducible squashfs — `SOURCE_DATE_EPOCH` + `mksquashfs -repro` (verifiable release hash).
- [ ] Retire the stale **LLM** `kickass-guard` binary + correct `vesper.md` to the non-LLM `brain_server.py` design.
- [ ] OEM first-run mode (Calamares) if NCDE is ever pre-imaged onto hardware.
- [ ] GPL source-offer note (light, since not-for-sale: license texts already present at usr/share/licenses; a simple offer/source snapshot in the build pipeline is good practice, not a hard gate).

---

## ▶️ ORDERED PATH
1. **Zero-risk one-file batch:** B-F1 fonts · B-F4 Sentinel install · BT AutoEnable · picom/polkit + WM respawn (B-F2) · X save-set.
2. **Safety wiring:** B-S1 reduce-motion · B-S2 first-run accessibility.
3. **Revive the nervous system:** B-F5 Sentinel↔Lelan bus + 4 handlers.
4. **Identity:** B-I1 ARCHCRAFT volid · B-I2 Firefox de-brand.
5. **Humans-first:** B-F3 native printer flow.
6. **B-S3 lampPulse** — only on operator go (sign-off + visual).
Then high-impact, then strategic. One change at a time; rebuild+verify each; aesthetic untouched.
