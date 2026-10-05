# FLUTTER-PLAN.md — native video chat for Magpie Talker

> **🔴 STATUS UPDATE (2026-07-05, session 71): this copy in `~/my-project/docs/` is now the
> CANONICAL one (was only at `~/ncde-staging/magpie-rebuild/`, unreachable from the doc index —
> the same lockout that hit sentinel-plan.md). §5's "source recovery in progress" is DONE:
> magpie-talker's full C++ source was recovered session 50 and built clean from
> `~/ncde-staging/LaPivot/compass7/magpie/` — **that path is gone now (corrected 2026-07-17, dev
> machine gone); current source lives at `~/ncde-wm-rebuild/magpie/src/`.** NEW ARCHITECTURE
> DECISION (operator, 2026-07-05):
> Magpie's global reachability moves to a serverless DHT band (OpenDHT — the operator's original
> "ham radio/CB, WiFi is the antenna" intent; XMPP was an agent-pushed detour). §4.3's signaling
> assumption ("always rides over dovecote-relay") is therefore superseded where the DHT can carry
> call signaling itself (that is literally how Jami sets up serverless calls on OpenDHT);
> dovecote-relay becomes the fallback band. Everything else here stands.**

Status: planning complete, source recovered, nothing built yet. See
auto-memory `project-ncde-magpie-flutter` for the condensed version; this is the full working doc.

## 0. What this is, in one line

A native (not a Zoom/Meet integration) video/audio chat capability built directly into Magpie Talker,
codenamed **Flutter** (operator's naming — fits Magpie's existing bird theme: Poe voices its messages,
Flutter = wings). General-purpose feature — not built for any single group. Churches/synagogues running
online classes and services were given as one real example use case, useful for sizing scale requirements
(see §3), not the exclusive audience.

## 1. UX concept (operator's own words — this is the spec, don't reinvent it)

Flutter is **not** a separate app, a new window, or a small docked video tile next to the chat. One button
inside Magpie's existing conversation view **transforms the whole interface**: the chat layout swaps out
and a full-viewport video view takes over (operator's comparison: "like cheese" — GNOME's minimal webcam
app — full-frame video, no chrome). A visible hang-up/back control reverses the transform back to the
normal chat layout when the call ends.

**Implementation implication:** this is a QML view/state swap inside the existing `MagpieTalker.qml`
window (e.g. a `StackView` or a top-level `state` property gating which content `Item` is visible), not a
new `Window {}`. Don't build a separate video-call window — that would contradict the stated design.

## 2. Session modes — dual, confirmed

Operator confirmed explicitly: **"both, depending on the event."**

- **Broadcast/webinar mode** — sermons, services, lectures: one or a small number of presenters have
  camera+mic live; everyone else watches/listens, can unmute to ask a question. Cheap by design: only 1-2
  upstream video encodes ever exist, no matter how many watchers.
- **Full symmetric gallery mode** — smaller classes/study groups/social calls: any participant's camera
  can be live at once, Zoom-style grid (operator: "multi screen layout like zoom... for class rooms
  online").

**Implication:** the host picks a mode per session (or it's inferred from participant count — TBD, needs a
UI decision later, not blocking the architecture). The SFU (§4) needs to know which mode it's in, since
that changes how many upstream feeds it accepts/forwards. The QML layout needs two real layouts: a
spotlight-plus-strip view (broadcast) and a full gallery grid (symmetric) — not one layout doing both
badly.

## 3. Scale reality (why this isn't a toy 1:1 call feature)

Real use cases named (congregation/classroom-size groups) mean this has to work for double-digit, possibly
larger, participant counts — not just 2-4 friends. That rules out naive full mesh (where every participant
sends a stream directly to every other participant) once the group gets past a handful of people — mesh
cost grows with the *square* of participant count, so it gets unworkable on both bandwidth and per-client
encode load well before real class/service sizes are reached.

## 4. Architecture decisions

### 4.1 Topology: SFU (Selective Forwarding Unit), not full mesh

Plan around a relay component that receives each participant's stream once and forwards it to whoever
needs it, rather than every client connecting directly to every other client. This is what makes both
session modes (§2) actually work at real scale:
- Broadcast mode: SFU accepts 1-2 upstream feeds, fans out to N watchers — trivial for it.
- Gallery mode: SFU accepts up to N upstream feeds, forwards each to the other N-1 — still one encode per
  sender, not one-per-recipient-pair like mesh would require.

### 4.2 Media pipeline: GStreamer `webrtcbin`

Chosen over hand-rolling raw/lightly-compressed frames over Magpie's existing TCP socket. `webrtcbin` gives
real RTP, jitter buffering, adaptive bitrate, and standard codec negotiation (VP8/H.264) for free — Magpie's
existing direct-TCP messaging channel is not media-grade (no framing/backpressure/loss-recovery designed
for continuous real-time streams) and hand-rolling that ourselves would be reinventing a well-solved
problem badly.

### 4.3 Connectivity: LAN-first, blended with relay

- **Signaling** (call offer/accept/decline/hang-up, session/mode negotiation) always rides over
  `dovecote-relay`'s existing JSON-over-TCP relay (extended with new message types for call setup) — so a
  call can always be *initiated* between any two Magpie users regardless of whether they're on the same
  LAN. This reuses real, already-shipped infrastructure rather than building a parallel mechanism.
- **Media** prefers direct P2P when both peers/the SFU are reachable on the same LAN (ICE host candidates,
  webrtcbin's normal behavior, near-zero latency, the common case for the LAN-first design Magpie already
  has via `BonjourDiscovery`/Avahi).
- **Off-LAN media relay is real additional scope, not free** — carrying actual audio/video bytes between
  parties that can't reach each other directly needs a genuine TURN-capable relay (e.g. `coturn`), which is
  a different, heavier thing than `dovecote-relay`'s JSON message forwarding. **Flagged explicitly as v1.5,
  not silently bundled into v1** — don't let a future pass quietly skip this distinction.

### 4.4 Reuse of Magpie's existing real infrastructure

Don't build parallel discovery/connection mechanisms. Once source is recovered (§5), hook into:
- `BonjourDiscovery` — existing Avahi/mDNS LAN peer discovery.
- `MessageHub::deliverTcp`/`onNewTcpConnection` — existing direct peer TCP channel (candidate carrier for
  the LAN-direct signaling/media-negotiation path, separate from the relay path in §4.3).
- The existing `hub` QML context object (`activeId, presence, searchResults, directs, ...` — see
  `ncde-architecture.md`'s backend contract table) — Flutter's call state should extend this contract
  (e.g. `hub.callState`, `hub.startCall(peerId)`, `hub.acceptCall()`, `hub.endCall()`), not introduce a
  second unrelated context object for call state.

## 5. Prerequisite: source recovery (blocking, in progress)

> **HISTORICAL — superseded (corrected 2026-07-17):** this section describes the session-50 recovery
> process. It's DONE (see banner above), and the workspace paths below (`~/ncde-staging/magpie-rebuild/`,
> the `ncde-wm-rebuild/tools/` copy nested under it) no longer exist — that dev machine is gone. Current
> source lives at `~/ncde-wm-rebuild/magpie/src/`. Left as-is below for the historical record of method.

Magpie-talker's C++ source (`MessageHub.cpp/h`, `BonjourDiscovery.cpp/h`, `KSSecret.cpp/h`, `Peer`,
`Contact`) does not exist anywhere in the tree — confirmed via full-tree grep. The compiled binary
(`/usr/local/bin/magpie-talker`) is unstripped (`file` confirms `with debug_info, not stripped`), so
DWARF-assisted Ghidra decompilation (the same method that recovered `ncde-wm`'s source) is the path.

- Reused `~/ncde-staging/ncde-wm-rebuild/tools/ghidra_12.1.2_PUBLIC` + adapted
  `scripts/DecompileByClass.py` into a parallel workspace: `~/ncde-staging/magpie-rebuild/`
  (`ghidra-proj/`, `scripts/`, `src/decompiled/`).
- **Blocked on JDK 21** (Ghidra 12.1.2's documented minimum) — this dev host had no JDK installed at all.
  Operator ran `sudo pacman -S jdk21-openjdk`; confirmed installed (`java -version` → 21.0.11).
- Headless import (`analyzeHeadless ... -import /usr/local/bin/magpie-talker`) running as of this doc's
  last edit — check `~/ncde-staging/magpie-rebuild/ghidra-import.log` for status. Next step once import +
  auto-analysis complete: run the `-process magpietalker -postScript DecompileByClass.py` pass (mirrors the
  exact ncde-wm precedent) to produce per-class decompiled `.c` files in `src/decompiled/`, then hand-clean
  those into real compilable C++ the same way `ncde-wm`'s recovery did.

## 6. Open items not yet decided (don't guess these — ask or design when reached)

- Exact UI trigger placement for the Flutter button in `MagpieTalker.qml`.
- How session mode (broadcast vs. gallery) gets chosen — host toggle, inferred from participant count, or
  both.
- Whether/how screen-sharing fits in (came up implicitly via the classroom/presentation use case, never
  explicitly requested — do not build this without asking first).
- SFU implementation specifics (a GStreamer-based custom SFU vs. an existing open-source SFU component) —
  needs research once source recovery gives a clear picture of what Magpie's process model can host.
- Where the SFU process actually runs (inside `magpie-talker` itself vs. a separate daemon, analogous to
  `dovecote-relay`'s existing separate-process pattern for relay).

## 7. Explicit non-scope for now

- Off-LAN media relay (`coturn` or equivalent) — v1.5, see §4.3.
- Anything specific to any particular organization/group — this is a general Magpie feature.

---

## SESSION 71 UPDATE (2026-07-05) — DHT WORLD BAND BUILT + PROVEN

**Magpie's serverless global "add anyone by callsign" band is built, compiled, and functionally
proven** (operator chose the callsign-lookup / MSN-ICQ model; XMPP retired to dormant code).

- **New class `DhtBand` (`compass7/magpie/DhtBand.{h,cpp}`)** owns an OpenDHT node. Announces
  `{callsign→uuid,host,ip,port,presence,status,loc}` at `hash("magpie:cs:"+callsign)`;
  `lookupCallsign()` resolves it; `watchCallsign()` gives the buddy-list presence heartbeat.
- **Wired into MessageHub** as `m_dht` beside `m_bonjour`: `addByCallsign()` Q_INVOKABLE,
  `onDhtPeerFound` upserts a `source="dht"` peer (existing `deliverTcp` reaches it), presence
  changes re-announce, `onAir()`/`myFingerprint()` for the UI. CMakeLists links `PkgConfig::OPENDHT`.
- **Identity/anti-impersonation:** each device has a persisted RSA-4096 keypair; the announce
  payload is SELF-SIGNED (record wrapped `{r,s,k}`, plain `put`) and the reader verifies the
  signature + derives fingerprint = hash(pubkey). Trust-on-first-use, like SSH known_hosts.
- **Two real OpenDHT findings (both worked around, documented in code):** (1) `putSigned` stalls
  in a small/fresh swarm (cert-store propagation) → use plain `put` + self-signed payload.
  (2) **This gnutls build's EC sign/verify is BROKEN** — a fresh EC key fails to verify its own
  signature; RSA verifies correctly. Proven via a sign/verify self-test (ecFresh=0, rsaFresh=1).
  Hence `generateIdentity` (RSA), NOT `generateEcIdentity`. Do not "optimize" back to EC.
- **PROVEN:** two-node loopback test (`compass7/magpie/test_dht.cpp` — scaffolding, not in
  CMakeLists, won't ship) against a local dhtnode swarm: node B resolved node A's callsign across
  the swarm with correct ip/port AND `verified=1`. OpenDHT + libsimdutf + dhtnode + msgpack headers
  vendored into `usr/`. `magpie-talker` rebuilt (sha 3d949959…), tree binary refreshed.

**AWAITING DEPLOY:** `usr/local/bin/magpie-talker` (mv-then-cp), the vendored OpenDHT libs
(`usr/lib/libopendht.so*`, `usr/lib/libsimdutf.so*`, `usr/bin/dhtnode`). Then a Magpie relaunch.

**NEXT (task #13 — Lelan integration + delivery decision):**
1. Gate the DHT node on Lelan's real `networkOnline` (don't bootstrap with no internet; re-bootstrap
   on reconnect). Currently DhtBand bootstraps unconditionally.
2. Opt-in geo-presence using Lelan's `placeName`/`location` (the operator's "who's near me" idea).
3. **Off-LAN DELIVERY is the open architecture decision** (NOT a Lelan gap): the announce carries
   the LAN ip, which is useless across NAT. Real serverless options — (a) DHT inbox store-and-
   forward (encrypt msg to recipient, `put` at their inbox key, they `listen`), (b) OpenDHT ICE
   direct connection, (c) dovecote-relay fallback. Discovery/presence work globally today;
   delivery across two home routers with no server needs one of these.

---

## SESSION 71 UPDATE 2 (2026-07-05) — Lelan wiring (task #13) DONE + a real architecture
## fix that came out of it (Lelan actuator/observer split)

**1. Network gating (built + verified):** `MessageHub::setLelan(Lelan*)` wires
`Lelan::networkChanged` → `onLelanNetworkChanged()`, which starts the DHT node the first time
`networkOnline()` is real (not unconditionally on app launch) and calls the new
`DhtBand::reconnect()` (re-seeds the bootstrap) if the node was already running and the network
flapped back. `main.cpp` now constructs `Lelan lelan;` (previously NEVER constructed at all —
confirmed via full-file read: only `Settings`/`Launcher`/`MessageHub`/`NCDEEngine` existed) and
calls `hub.setLelan(&lelan)` + `ncde->setLelan(&lelan)` (the latter fixes CMakeLists' own
documented dead-pointer note — NCDEEngine's wifi/bluetooth forwarding now actually works in Magpie).

**2. Opt-in geo-presence (built + verified):** `MessageHub::shareLocation`/`setShareLocation(bool)`
(persisted in identity.json, default OFF), `browseNearby()`/`nearbyResults` (QML-ready, no button
built yet — same status as callsign-add). Publishes `{callsign,uuid,presence}` to a coarse geocell
key (`DhtBand::announceGeo`, ~0.1°/~11km, never precise) derived from Lelan's real `location()`
lat/lon; re-announces on `Lelan::placeNameChanged`. This is the operator's original "who's on the
air near me" idea, done for real.

**3. Real correctness fix found + closed along the way — a stable `dht::Value::Id`:** without this,
every re-announce (5min timer) would have created a NEW distinct value at the same DHT key instead
of refreshing the existing one — silent duplicate-entry accumulation forever. Fixed: an FNV-1a hash
of the packed public key, stable across restarts, set on every `announce()`/`clearAnnounce()`/
`announceGeo()`/`clearGeo()` put.

**4. Bigger finding, fixed at the operator's direction — `Lelan` was never actually "one thing."**
Wiring a real `Lelan` into Magpie (the SECOND process ever to construct one) exposed that `Lelan`'s
constructor unconditionally subscribes to Sentinel's signals, runs its own 60s thermal/cpu-freq
poller, and independently calls back `SetPowerProfile`/`SetThermalCap`/`SetProcessTier` — i.e. a
second instance would silently double-actuate Sentinel for the same real hardware event. Operator's
own standing architecture ("Lelan is one thing... it controls the whole host... Sentinel is a
watcher") was never actually enforced in code because there was only ever one instance until now.
**Fixed:** `Lelan` gained a constructor `actuator` flag (default `false`=observer). Only
`actuator=true` subscribes to Sentinel / runs the hardware pollers / reaches the four real
actuation call sites (all four ALSO individually guarded — defense in depth, not just gated at the
subscription point). LaPivot's WM `main.cpp` now explicitly passes `actuator=true` — the ONE
controller on the host. Magpie's `Lelan lelan;` correctly defaults to observer. Full detail + the
exact chain-of-command quote: auto-memory `project_ncde_harmony_amiga_mission` (updated, now the
mandatory first-read block for any future Lelan/Sentinel/Zen work). **Standing rule for every
future native app that ever constructs a `Lelan`:** default (observer) unless you are building a
second real WM, which should never happen.

**Build/deploy status:** Both `LaPivot` (sha `824d052fff…`) and `magpie-talker` (sha
`ecb28fb5a8…`) rebuilt clean, `nm`-confirmed the new `Lelan::Lelan(QObject*, bool)` ctor in both,
tree binary copies refreshed and byte-identical to the fresh builds. **AWAITING DEPLOY to
/usr/local/bin/** (mv-then-cp both, same ETXTBSY pattern), then a relog.

**Still open (not done this session, real remaining work):** the off-LAN message DELIVERY decision
(announce carries the LAN ip, useless across NAT — DHT inbox store-and-forward vs. OpenDHT ICE vs.
dovecote-relay fallback); the add-by-callsign + browse-nearby QML UI (backend is fully ready);
Flutter itself (native video, SFU, GStreamer webrtcbin) — nothing started yet.

---

## SESSION 71 UPDATE 2 (2026-07-05) — off-LAN message DELIVERY built + proven

**The delivery decision above is now made and built: DHT inbox store-and-forward.** Every message
to a `source=="dht"` peer is end-to-end encrypted to their real RSA public key (captured on the
peer record during `lookupCallsign()`/presence, stored on `Peer::pubKey`), signed with the sender's
identity, and published to the recipient's own inbox key (`magpie:inbox:<callsign>`); the recipient
decrypts+verifies on receipt via `watchOwnInbox()`. Needs only OUTBOUND reachability to the swarm
on either side — no port forwarding, no hole-punching, no relay. Honest limits, disclosed in code:
text only (OpenDHT caps a value at 64KB), and "recently-offline-tolerant" not full store-and-forward
(a value expires ~10min).

**Proven functionally, not just compiled:** a second real two-node test (node A resolves node B's
callsign, encrypts+sends, node B decrypts+verifies) — `verified=1`, exact plaintext recovered.
`onDhtPeerFound`'s search-result map was also extended with `location`/`alreadyAdded` (mirroring
`relaySearch()`'s own result shape exactly) so the ALREADY-EXISTING "Add contact" search panel in
MagpieTalker.qml renders DHT results with zero QML changes — the callsign lookup is reachable via
the search box's existing UI today (fuzzy relay search and exact DHT lookup share one results list).

**Build:** clean, `nm`-confirmed `DhtBand::sendInbox`/`watchOwnInbox`/`MessageHub::onDhtInboxMessage`
present. Tree binary refreshed.

---

## SESSION 71 UPDATE 3 (2026-07-05) — XMPP/JABBER REMOVED ENTIRELY

**Operator's explicit instruction: "make sure all the jabbar stuff gets removed too."** The real
XMPP-server client (roster, 1:1 messages, XEP-0045 MUC group chat, XEP-0077 in-band registration,
the "@"/Jabber status pill, the embedded WebEngineView registration flow) was NOT deprecated or
left dormant — it was fully removed from the tree. This was an agent-pushed detour from the
operator's original ham-radio/no-server intent (see the updates above); the DHT world band is the
one real global-reach mechanism now.

**Removed:**
- `compass7/magpie/MessageHub.h`/`.cpp`: every QXmppClient/QXmppMucManager/
  QXmppRegistrationManager member, property, getter, signal, slot, and private method —
  ensureXmppClient/connectXmpp/registerXmppAccount/persistXmppConfig/discoverMucService/
  joinMucRoom/joinRoomByJid/refreshMucMembers/updateXmppPeerPresence/sendMucJson/
  onXmppConnected/onXmppDisconnected/onXmppRegistrationSucceeded/onXmppServerMessageReceived/
  onXmppRosterReceived/onXmppRosterItemRemoved/onXmppPresenceChanged/onMucRoomJoined/
  onMucParticipantsChanged/onMucMessageReceived/setupXmppAccount/retryXmppRegistration/
  openXmppSignupPage/copyUsernameToClipboard/copyMagpiePasswordToClipboard/
  autofillRegistrationScript/confirmWebRegistration/onPasswordVerified — all gone. sendMessage()/
  sendFile()/react()'s channel branches now log an honest "no backing group-chat mechanism"
  instead of routing to a MUC room. **Real capability loss, disclosed, not silently dropped: group
  chat ("channels") has no replacement yet** — it only ever worked via XMPP MUC. createChannel()/
  joinExistingChannel() still work as local-list-only entries (kept — they had real non-XMPP
  value even before), just with no live room behind them.
- **NOT touched, correctly**: BonjourDiscovery's own xmppMessageReceived/sendXmpp/
  onXmppMessageReceived — this is XEP-0174 LAN/mDNS peer messaging (Bonjour's own internal wire
  format), unrelated to any real Jabber server. Comments updated so this isn't confused with the
  removed feature again.
- CMakeLists.txt: dropped find_package(QXmppQt6) + QXmpp::QXmpp link + the WebEngineQuick Qt
  component + Qt6::WebEngineQuick link (the WebEngineView was ONLY ever used for the removed
  registration page — confirmed via a full grep, zero other use in the QML). main.cpp: dropped
  QtWebEngineQuick::initialize() + its include. MagpieTalker.qml: dropped import QtWebEngine,
  the "Jabber" status pill, the entire xmppSettingsOverlay/xmppWebRegOverlay panels (~340 lines),
  xmppSettingsOpen/xmppWebRegOpen properties, the dangling hub.onPasswordVerified() login-flow
  call. qmllint clean.
- **Verified zero remaining linkage**: ldd on the rebuilt binary shows no qxmpp/webengine entries.
  Full rebuild clean, tree binary + QML refreshed.

**AWAITING DEPLOY:** usr/local/bin/magpie-talker (mv-then-cp) + usr/share/ncde/MagpieTalker.qml
(sudo cp), then relog/relaunch. The vendored qxmpp/WebEngineQuick packages are now unused by
Magpie — left in place per the never-delete rule; the operator can decide whether to retire them
from the tree/host himself (nothing else in NCDE depends on them — not independently re-verified
this pass).

---

## SESSION 73 UPDATE (2026-07-06) — qml6glsink DEADLOCK FIXED + PROVEN; CALL UI BUILT

**The session-72 blocker is closed.** Root cause verified against GStreamer's own qt6 qmlsink
example (upstream `tests/examples/qt6/qmlsink/main.cpp`): `qml6glsink` blocks its state change on
the scene graph's GL context, so a synchronous main-thread `set_state(PLAYING)` deadlocks the Qt
event loop. Fix, exactly upstream's pattern: PLAYING runs as a QRunnable on the QML window's
render thread (`QQuickWindow::scheduleRenderJob`, BeforeSynchronizingStage) —
`FlutterCall::schedulePlaying()`; new honest "starting" mediaState, "active" only when the bus
reports PLAYING actually reached. **Proven:** in-tree harness
`compass7/magpie/test_flutter_pipeline.cpp` (scaffolding, not in CMakeLists) — event loop alive,
PLAYING reached, 178 real frames through qml6glsink, PASS exit 0.

Also fixed en route: QML side REQUIRES `GstGLQt6VideoItem`
(`import org.freedesktop.gstreamer.Qt6GLVideoItem 1.0`) — FlutterCall.h's "any plain Item" note
was wrong, corrected; magpie main.cpp now gst_init + preloads the qml6 plugin BEFORE QML load so
the import resolves; remote sink's "widget" set before its state comes up. Safety rule from a real
operator report: never a Qt-default-white window — harness + call layer are black-backed.

**Call UI built per §1 (the transform, not a tile):** DM-header ✆ button → full-viewport black
call view (remote full-frame, local postage stamp, visible Hang Up), incoming-ring overlay
(Answer/Decline), consent gate (camera/mic never open pre-Allow; Deny ends the call). qmllint ✓;
rebuilt binary ran 12s with zero QML errors. sha `8bd3b12f…`. AWAITING DEPLOY + operator test
(solo camera-preview test possible on this laptop — /dev/video0 confirmed; full call needs a
second node).

**NEW SPEC (operator, 2026-07-06): green-screen background replacement, "like Zoom."** Real
chroma-key (no ML, offline): `alpha` + `compositor` + `imagefreeze` — all verified present,
libgstalpha.so already vendored. Operator supplies a solid backdrop (any color; configurable key)
+ background images. Next Flutter task after the two-party call path is operator-confirmed.
Zoom-style AI no-screen segmentation: separate, heavier, explicitly later.

---

## SESSION 74 UPDATE (2026-07-06) — GREEN-SCREEN BUILT + PIXEL-PROVEN, AWAITING DEPLOY

Operator supplied 6 backdrops, live at `/usr/share/ncde/flutter-backgrounds/{1..6}.png`.
Pipeline (in `FlutterCall::buildPipeline()`): camera → videoscale to fixed 1280x720 (any webcam,
nothing dev-box-specific) → `alpha name=keyer` → `compositor background=black` over
`appsrc → imagefreeze allow-replace=true` → the existing tee (preview + vp8enc). Off = keyer
method=set alpha=1.0, opaque camera covers the black layer — output identical to before. On =
push the backdrop frame (QImage → RGBA 1280x720) into appsrc + keyer method=custom
target-r/g/b = sheet color. Live mid-call switching = just another push; NO pipeline surgery.

**Empirical finding (the one real bug this build):** `prefer-passthrough=true` on alpha BREAKS
runtime keying — it negotiates caps without an alpha channel and method flips then do nothing.
Found by `test_greenscreen.cpp` (in-tree scaffolding harness, same pattern as
test_flutter_pipeline.cpp): runs the exact shipped pipeline with videotestsrc pattern=green as
the camera, reads output pixels in code — 4/4 PASS without prefer-passthrough (keying off =
camera, on = backdrop 1.png pixel-exact, live swap to 2.png pixel-exact, off = camera again).

API (one-hub contract, §4.4): `hub.videoBackground` / `hub.videoKeyColor` (properties),
`hub.videoBackgrounds()` / `hub.setVideoBackground(path)` / `hub.setVideoKeyColor(color)`.
Persisted to `~/.config/ncde/magpie/flutter.json`; ensureFlutterCall() hands prefs to the media
layer so a choice made between calls applies on the next call. Choosing a backdrop NEVER opens
the camera (consent gate untouched). QML: "Backdrop" button bottom-left of the call view
(visible once media is up) → panel with None + 6 thumbnails + green/blue sheet swatches
(backend accepts any color). qmllint ✓; binary sha `eb49267c…`, tree copy refreshed; backups
`*.prebak-20260706-greenscreen`. CMake: + `gstreamer-app-1.0`. **AWAITING DEPLOY** (binary via
cp+mv, MagpieTalker.qml via cp — commands in PRODUCTION-PUNCHLIST §1) **+ operator click-test
with a real green sheet.**

**Post-deploy same-day: magpie wouldn't open — SESSION 73's `font.pixelSize: 12.5` (ring +
consent overlays) is a fatal QML load error ("int expected") that had never actually been loaded
live before this deploy.** qmllint and qmlcachegen both pass it; the binary hardcodes the live
QML path so pre-deploy binary launches never test the tree file. Fixed (12.5 → 13) + new gate:
`test_qml_load.cpp` loads the tree QML in a real offscreen engine — run it before every
MagpieTalker.qml deploy. Full detail: PRODUCTION-PUNCHLIST §1.

**Still open for Flutter v1:** two-party end-to-end call proof (signaling was proven session 72;
media path now proven locally; the two together over a real LAN between two nodes is the remaining
proof), speaker output device selection, and the §2 broadcast/gallery multi-party modes (SFU) —
which remain the larger post-v1 architecture per §4.1.
