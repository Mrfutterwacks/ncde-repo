# Lelan Research Findings — recovered + topped-up (the synthesis the workflow never wrote)

**Status:** TWO runs, now reconciled. (1) The first workflow `wf_a69f75f2-222` (session `998a1203`)
was **aborted mid-Verify** (operator ran out of usage) — it fully verified only the **hub pattern /
QtDBus**, **audio**, and **GeoClue2** angles (claims 1–22, all 3-0) before the kill; its tray / MPRIS /
daemon sections below were the salvage agent's single-source top-up, **never adversarially verified**.
(2) A second **targeted** run `wf_eaf8d459-0e9` (session `a6d00af7`, 2026-06-22) completed
Scope→Search→Fetch→**Verify+Synthesize** on those gaps: 105 claims extracted, but the verify gate
sampled only the **top 25** → **24 confirmed, 1 killed**. **Verified this run = SNI tray + the X11
SNI/XEmbed-proxy decision (§4), MPRIS (§5), and NetworkManager `NMState`/`NMConnectivityState` enums.**
The other daemon enum details (§6: UPower/UDisks2/logind/portal/PowerProfiles/PackageKit/timedate) and
the prior-art deep-dive (§7) were **fetched from PRIMARY freedesktop specs but did NOT reach the
adversarial gate** — high content-confidence, but a verify pass is still owed (queued in
`SESSION_HANDOFF.md`). **Evidence tags:** ✅ = adversarially 3-vote verified; 📄 = straight from a
primary spec but NOT 3-vote verified; ⚠️ = single-source/inference.

Pairs with `NCDE-LELAN-PLAN.md` (the build plan) and `lelan.md` (the contract). Use this to fill the
research-dependent stubs in `compass (7).zip` correctly.

> **NCDE IS X11 (Qt6 + QML, picom compositor) — NOT Wayland.** Every API below (libpulse audio, SNI
> tray, GeoClue2, MPRIS, all freedesktop D-Bus daemons) is **display-server-agnostic** and behaves
> identically on X11. Where a Wayland shell (Waybar) is cited, it is cited ONLY for its
> display-agnostic backend code (e.g. its libpulse calls), never for anything Wayland-specific. The
> single subsystem where X11 vs Wayland actually changes the design is the **tray** — see §4.

---

## 1. The hub pattern — Qt6 QtDBus best practice ✅
- **Self-heal:** use **`QDBusServiceWatcher`** (wraps `org.freedesktop.DBus` `NameOwnerChanged` into
  `serviceRegistered()/serviceUnregistered()/serviceOwnerChanged()`). More efficient than a manual
  global `NameOwnerChanged` connect — it only fires for watched names. Mutate with
  `addWatchedService()/removeWatchedService()`, NOT `setServicesWatched()`.
  → **compass(7) currently hand-rolls the global `NameOwnerChanged`** (works, but `QDBusServiceWatcher`
  is the idiomatic fix and lets per-service re-subscribe be precise.)
- **Async:** wrap every initial fetch in **`QDBusPendingCallWatcher`** (never block the GUI thread).
- **⚠️ Gotcha (real bug in compass 7):** **`QDBusInterface`'s constructor makes a BLOCKING
  introspection round-trip.** compass(7) uses `new QDBusInterface(...)` in `subscribeToUPower`,
  `subscribeToPortalSettings`, `subscribeToNetworkManager`, `subscribeToPlayers`. Replace with
  `QDBusMessage::createMethodCall(...)` + `QDBusConnection::asyncCall(...)` to avoid the stall.
- **One `QDBusConnection` per bus** (it's implicitly shared); session + system.
- **Closest real-shell analog:** Quickshell's service layer (data-provider services → read-only
  props/signals to declarative QML). Same shape as Lelan→QML.
- Sources: Qt6 `QDBusServiceWatcher`, `QDBusPendingCallWatcher` docs; Quickshell architecture (DeepWiki).

## 2. Audio on pipewire-pulse — THE decision ✅ (replaces compass 7's approach)
**Finding (verified):** `pipewire-pulse` (`libpipewire-module-protocol-pulse`) implements only the
PulseAudio **native socket protocol**, NOT `module-dbus-protocol`. Therefore **`org.PulseAudio.Core1`
D-Bus API does NOT exist on the target.** The `server.dbus-name=org.pulseaudio.Server` is only an
admin server-identity name — it is NOT the Core1 control API (this exact misconception was the one
claim the prior run **refuted 0-3**). Core1 is also peer-to-peer (not on session/system bus) and needs
`ListenForSignal()` registration.
**⟹ compass(7)'s entire `subscribeToAudio()` (Core1 on the session bus) is dead on this system. Rip it out.**

**Recommended replacement = `libpulse`** (the PulseAudio client library — already installed as a
pipewire-pulse dependency; speaks the native protocol over the socket). The qtermwidget
"link-a-proven-lib" model the plan prescribes. Reference code = **Waybar's `audio_backend.cpp`**
(cited for the libpulse calls only — that backend is display-agnostic PA-client code, identical on
X11; Waybar being a Wayland bar is irrelevant to it).

| Need | libpulse call (from Waybar `src/util/audio_backend.cpp`) |
|---|---|
| mainloop | `pa_threaded_mainloop_new/_start/_lock/_unlock`, `pa_context_new`, `pa_context_connect`, `pa_context_set_state_callback` |
| **monitor** changes | `pa_context_set_subscribe_callback` + `pa_context_subscribe` (sink/source/server events) |
| read default sink | `pa_context_get_server_info` → default sink name |
| read volume/mute | `pa_context_get_sink_info_by_index` / `_list`; `pa_cvolume_avg` for the level |
| **set** volume | `pa_context_set_sink_volume_by_index` |
| **set** mute | `pa_context_set_sink_mute_by_index` (`_source_mute_by_index` for input) |

Integration: run the `pa_threaded_mainloop` alongside Qt; marshal callbacks back to the Lelan QObject
(queued connection). Emit `audioChanged/onAudioVolumeUpdated/onAudioMuteUpdated/onFallbackSinkUpdated`.
- **Pragmatic fallback (if libpulse is too heavy short-term):** `wpctl set-volume/set-mute
  @DEFAULT_AUDIO_SINK@` + `pactl subscribe` via `QProcess` — but that's polling/spawn, against the
  no-poll cardinal rule, so **libpulse is the right answer**, fallback only as a stopgap.
- Sources: PipeWire `module-protocol-pulse` docs; PulseAudio D-Bus spec (why Core1 is wrong here);
  Waybar `audio_backend.cpp`; ArchWiki PipeWire.

## 3. GeoClue2 — client registration flow ✅ (compass 7's stub never fires)
compass(7)'s `subscribeToGeoClue()` only `bus.connect(... LocationUpdated ...)` — it never creates a
Client, so **nothing ever fires.** Correct flow:
1. `org.freedesktop.GeoClue2.Manager` `/org/freedesktop/GeoClue2/Manager` → `GetClient()` (per-peer,
   reused) or `CreateClient()` (always new) → returns a Client object path.
2. On the Client: **set `DesktopId`** (signature `s`, required), optionally `DistanceThreshold`/
   `RequestedAccuracyLevel`.
3. **Connect `LocationUpdated(old,new)` BEFORE calling `Start()`** (ordering matters — spec-stated).
4. `Start()`. On first `LocationUpdated`, read the `new` `org.freedesktop.GeoClue2.Location`
   `Latitude`/`Longitude` → drive place/weather/moon + `scheduleNightLightEvents`.
- **⚠️ Gotcha:** `AccessDenied "no agent for UID"` — needs either an authorization agent or the app
  allowed in `/etc/geoclue/geoclue.conf` (`[<desktop-id>] allowed=true`). The completeness audit also
  flags **geoclue is not installed in the tree yet** → operator `pacman -S --root geoclue` first.
- Sources: freedesktop GeoClue2 Manager + Client reference manuals.

## 4. StatusNotifierItem / Watcher / Host — the SNI tray ✅ VERIFIED (decision resolved)
**THE X11 DECISION — now answered with real-shell precedent (run `wf_eaf8d459-0e9`):** every real X11
shell hosts **SNI as the PRIMARY mechanism and bridges legacy XEmbed via a separate proxy** — it does
NOT host SNI-only (would miss XEmbed-only apps) and does NOT run two independent render paths:
- **KDE Plasma:** SNI-only host + **`xembed-sni-proxy`** (extracted from plasma-workspace; C++/CMake/X11
  +D-Bus) that renders `_NET_SYSTEM_TRAY` XEmbed windows offscreen → exports them as SNI items.
- **lxqt-panel (≥1.1.0):** the legacy Tray plugin no longer renders XEmbed directly — it **proxies
  XEmbed icons into StatusNotifierItems** so everything flows through SNI.
- **xfce4-panel (≥4.15):** SNI host merged into the panel's systray; one plugin multiplexes both.
- **`snixembed`:** the minimal-WM bridge (SNI→XEmbed), the inverse direction.
> **⟹ NCDE decision:** Lelan/ncde-wm **owns the SNI watcher+host** (`subscribeTrayOwner()` is SNI per
> the binary) and the existing **`TrayWatcher` (XEmbed, `ncde-architecture.md §2`) feeds a proxy** into
> SNI — the Plasma model. ncde-wm already has both halves, so this is a wiring decision, not new code.

**Critical gotcha (verified):** you must claim `org.kde.StatusNotifierWatcher` **VERY EARLY in session
startup**. libayatana/appindicator apps check whether the watcher name is *owned* at `set_status()`; if
the process is up but hasn't claimed the name yet, they fall back to a GtkStatusIcon (XEmbed). This
fallback is **non-deterministic / scheduler-timing-dependent (reproduced 3 of 5 cold boots)** → late
registration = duplicate/missing icons. Also: some apps gate on **env vars** (`XDG_CURRENT_DESKTOP=KDE`)
not the D-Bus service; once they see the host they speak the **AppIndicator** dialect, so the host must
tolerate AppIndicator semantics.

To host SNI items:
1. **Own `org.kde.StatusNotifierWatcher`** (single session-bus instance) AND watch the
   `org.freedesktop.StatusNotifierWatcher` name too (xfce/spec use the freedesktop variant; most apps
   use `org.kde.*`). Exposes `RegisterStatusNotifierItem(s)`, `RegisterStatusNotifierHost(s)`, property
   `RegisteredStatusNotifierItems` (`as`), signals `StatusNotifierItemRegistered/Unregistered(s)` +
   `StatusNotifierHostRegistered()`.
2. **Register as Host** (`RegisterStatusNotifierHost(<your bus name>)`), then enumerate
   `RegisteredStatusNotifierItems`. **[refuted-claim nuance]** the register argument can be a **bus
   name OR an object path** (KDE `statusnotifierwatcher.cpp` accepts both) — handle both forms.
3. Per item (`org.kde.StatusNotifierItem`/`org.freedesktop.StatusNotifierItem`, name like
   `org.kde.StatusNotifierItem-<PID>-<ID>`): read `Status`, `IconName`/`IconPixmap`, `Title`,
   `ToolTip`, and **`Menu`** (object path → `com.canonical.dbusmenu`). Watch `NewIcon/NewStatus/NewToolTip`.
4. Track item lifecycle with `QDBusServiceWatcher`. Emit `trayChanged/onTrayBadgeChanged/...`.
- **Reference impls to mine:** **`xembed-sni-proxy`** (KDE, the proxy half — directly portable),
  `xfce4-panel` SnBackend/SnItem (C, BOTH protocols in one), `lxqt-panel` Tray plugin (the proxy
  pattern), `snixembed` (host-registration mechanics). All C/C++.
- Sources: freedesktop StatusNotifierWatcher/Item specs; KDE xembed-sni-proxy; lxqt-panel; xfce4-panel;
  snixembed; libayatana-appindicator (the timing/fallback quirk).

## 5. MPRIS — multi-player ✅ VERIFIED (compass 7 partial: Metadata not parsed)
- Enumerate `org.mpris.MediaPlayer2.*` on the session bus (off `NameOwnerChanged`; Quickshell uses a
  `QDBusServiceWatcher` on that prefix). Multiple instances disambiguate via a `.instance<PID>` suffix.
- Per player, watch `org.mpris.MediaPlayer2.Player` `PropertiesChanged`: `PlaybackStatus`(s),
  **`Metadata`(a{sv})** → `mpris:trackid`, `xesam:title`/`xesam:artist`, `mpris:artUrl`,
  `mpris:length`. compass(7) parses PlaybackStatus + Position but **not Metadata** → title/artist/art
  never populate. Fix: parse `Metadata` in `onPropertiesChanged` into `PlayerState`.
- **`Position`(x, µs) is EXCLUDED from `PropertiesChanged`** — use the **`Seeked`** signal + a coalesced
  poll (the shared CoarseTimer) for the scrubber. (compass 7 reads Position from PropsChanged, which
  won't update — wire `Seeked` + the 60s tick instead.)
- **Types (verified):** `mpris:trackid` is `o` (object path), `mpris:length` is `x` (int64 µs),
  `PlaybackStatus` is exactly `Playing`/`Paused`/`Stopped`. Detect a track change when `trackid`/url/
  title changes. Read capability props `CanGoNext/CanGoPrevious/CanPlay/CanPause/CanSeek/CanControl`
  and only expose controls they allow. Root `org.mpris.MediaPlayer2` adds `Raise()/Quit()`, `Identity`,
  `DesktopEntry` (→ app icon), `CanRaise/CanQuit`.
- **Smooth scrubber:** since Position is sparse, interpolate locally (last D-Bus position + report
  timestamp + rate + state) between updates rather than polling fast — Quickshell's approach.
- Controls: `Play/Pause/PlayPause/Next/Previous/Stop/Seek(offset_us)` on the active player.
- Sources: MPRIS `MediaPlayer2`/`MediaPlayer2.Player` specs; Quickshell Mpris service.

## 6. Standard daemons — exact signals + enum values 📄 PRIMARY-SOURCED (only NM 3-vote verified)
All freedesktop-standard; compass(7) implements these acceptably — listed so the parse can be finished.
> **Verification status:** only **NetworkManager `NMState`/`NMConnectivityState`** (below) passed the
> adversarial 3-vote gate this run. The rest (UPower/UDisks2/logind/portal/PowerProfiles/PackageKit/
> timedate) are taken **verbatim from primary freedesktop reference manuals** but the verify stage
> (top-25 sample) never reached them — trust the values, but a 3-vote pass is queued.
- **NetworkManager** `org.freedesktop.NetworkManager`: `StateChanged(u)` (NMState enum), PropsChanged
  `PrimaryConnection`/`Connectivity`; per-device `StateChanged(new,old,reason)`; VPN via
  `…VPN.Connection.VpnStateChanged(u,u)`.
- **UPower** composite `…/devices/DisplayDevice`: `Percentage`/`State`/`TimeToEmpty` via Device
  PropsChanged (single object — don't poll each battery).
- **UDisks2** root implements **ObjectManager**: `InterfacesAdded/Removed`; removable =
  `Drive.Removable==true`; mounts = `Filesystem.MountPoints`(aay) → build `removableVolumes`
  (compass 7 leaves this TODO).
- **logind** `…/session/self`: `Lock`/`Unlock`, PropsChanged `Active`/`LockedHint`;
  Manager `PrepareForSleep(b)`. (compass 7 ✓.)
- **xdg portal Settings**: `SettingChanged(ns,key,v)`; `org.freedesktop.appearance` `color-scheme`
  (u 0 none/1 dark/2 light) + `accent-color` **(ddd) struct → QColor** (compass 7 leaves accent TODO).
- **PowerProfiles** `net.hadess.PowerProfiles` PropsChanged `ActiveProfile` (compass 7 ✓).
- **PackageKit** `UpdatesChanged` → call **`GetUpdates`** for the count (compass 7 emits but never
  fetches the count).
- **timedate1/hostname1/locale1** PropsChanged (compass 7 ✓).

**Verified enum / type values (so the parse is exact):**
- **NMState** (`Manager.StateChanged(u)`): 0 unknown · 10 asleep/disabled · 20 disconnected ·
  30 disconnecting · 40 connecting · 50 connected-local · 60 connected-site · 70 connected-global.
- **NMConnectivityState** (`Connectivity`): 0 unknown · 1 none · 2 portal(captive) · 3 limited · 4 full.
- **NMDeviceState** (`Device.StateChanged(new,old,reason)`): 0/10/20/30/40/50/60/70/80/90 →
  100 ACTIVATED · 110 deactivating · 120 failed. **NMActiveConnectionState** (active/VPN): 0/1
  activating/2 activated/3 deactivating/4 deactivated.
- **UPower `Device.State`** (u): 0 unknown · 1 charging · 2 discharging · 3 empty · 4 fully-charged ·
  5 pending-charge · 6 pending-discharge. Props `Percentage`(d 0-100), `TimeToEmpty`(x s), `Type`(u);
  observed via the **standard** `PropertiesChanged` (not a custom signal).
- **portal Settings** `org.freedesktop.appearance`: `color-scheme`(u) 0 none/1 dark/2 light;
  `accent-color`(ddd) sRGB each in [0,1], out-of-range = unset → parse to `QColor`; `contrast`(u) 0/1.
  Read via `ReadOne(ns,key)→v` (v2; `ReadAll(as)→a{sa{sv}}`; old `Read` double-wraps the variant).
- **UDisks2**: root is an **ObjectManager**; `Drive.Removable`(b) (+ `Ejectable`/`MediaRemovable`/
  `ConnectionBus` e.g. "usb"); `Filesystem.MountPoints`(aay = array of NUL-terminated byte-array paths)
  → decode to build `removableVolumes`; `Filesystem.Mount/Unmount`.
- **logind**: `Session.Lock()`/`Unlock()` (no args) + `LockedHint`(b)/`Active`(b)/`SetLockedHint(b)`;
  `Manager.PrepareForSleep(b)` (+ `PrepareForShutdown(b)`, `SessionNew/SessionRemoved`).
- Sources (all PRIMARY reference manuals): NetworkManager nm-dbus-types (**3-vote verified**); UPower
  Device.html; UDisks2 storaged.org; freedesktop portal.Settings; systemd login1 — the last four are
  primary-spec values **not yet 3-vote verified**. NM note: `NM_STATE_DISABLED=10` (NM 1.56) is the
  current name for the old `NM_STATE_ASLEEP=10` (same value). NM per-device `StateChanged`/VPN/
  `PrimaryConnection` were NOT verified — still open.

---

## 7. Prior art — the centralized hub is a proven pattern 📄 SOURCED, NOT 3-vote verified (OPEN)
Lelan is not novel; it mirrors two production designs (this is the "has it been done in Linux? yes, and
how" answer). **Caveat:** these came from the fetch stage (Astal primary docs + a KSystemStats blog)
but produced **no surviving verified claims** — the synthesis explicitly lists "how Plasma/Astal
centralize AND coalesce high-frequency state, and what Lelan should mirror" as an **open question**.
The *existence* of the pattern is well-attested; the *coalescing-technique* deep-dive is the queued
follow-up (see the OpenDarwin/prior-art research item in `SESSION_HANDOFF.md`).
- **KDE `KSystemStats`** — a **standalone D-Bus service** that centralizes system-monitoring data
  collection, replacing per-app `ksysguardd` instances with **one** collector all clients query over
  D-Bus. Sensors are **plugins** (modular), and each sensor carries metadata (name/description/unit/max)
  organized hierarchically. ⟹ exactly Lelan's "one owner, many consumers" thesis, in KDE's own stack.
- **Astal / AGS (`libastal`, GLib/GObject)** — each subsystem is a **singleton GObject service** that
  emits a `changed` signal; widgets connect reactively (`connect`/`bind`/hook) instead of polling, and
  the singletons are shared across the whole UI. Astal ships **per-daemon wrapper libs** that map 1:1
  onto Lelan's backends: Network (NetworkManager), Battery (UPower), PowerProfiles, Mpris, Bluetooth,
  **WirePlumber (audio)**, Tray (**SNI over D-Bus**), and **Notifd** (it even acts as the notification
  server, like ncde-wm does). ⟹ validates Lelan's signal-hub-feeding-declarative-UI design end-to-end.
- **Audio note:** Astal picks **WirePlumber** for audio, whereas §2 here recommended **libpulse**
  (Waybar's model). Both are legitimate "link-a-proven-lib" choices for pipewire-pulse on X11 — libpulse
  is lighter to integrate into a Qt event loop; WirePlumber is the PipeWire-native object model. **Pick
  one at implementation time** (libpulse remains the §2 recommendation; WirePlumber is the documented
  alternative). NOT a blocker, NOT Core1.
- Sources: KDE KSystemStats (invent.kde.org / KDE docs); Astal/AGS docs (aylur.github.io, libastal).

## What this changes in the compass (7) fix list
| Subsystem | compass 7 state | Action from this research |
|---|---|---|
| Audio | PA Core1 D-Bus (DEAD on pipewire-pulse) | **Replace with libpulse** (§2) — biggest single change |
| Tray | empty `{}` | Own `org.kde.StatusNotifierWatcher` EARLY + host SNI; bridge ncde-wm's XEmbed `TrayWatcher` via an xembed-sni-proxy (§4) |
| GeoClue2 | connect-only stub | Add Client `GetClient`+`DesktopId`+`Start`, connect-before-Start (§3) |
| MPRIS | Position from PropsChanged, no Metadata | Parse `Metadata`; Position via `Seeked`+poll (§5) |
| portal accent | TODO | parse `(ddd)`→QColor (§6) |
| UDisks2 `removableVolumes` | TODO | walk `Drive.Removable`+`MountPoints` (§6) |
| PackageKit count | not fetched | call `GetUpdates` (§6) |
| QDBusInterface blocking ctor | present | switch to async `QDBusMessage` (§1) |

**Build-host caveat (from `ncde-completeness-audit.md`):** geoclue / power-profiles-daemon /
packagekit are **not installed in the tree** — those subsystems can't be live-tested until the
operator `pacman -S --root`s them. logind / UPower / NM / portal / MPRIS / Sentinel / **audio
(pipewire-pulse is present)** can be tested now.
