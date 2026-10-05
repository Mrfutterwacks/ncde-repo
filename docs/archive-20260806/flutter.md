# Magpie Talker — Group Video Calling: Design & Phased Build Plan

**Status:** Design complete, 2026-07-14. Not yet built — deferred to a dedicated future session,
before the ISO ships. This document is the durable reference for that session; it should not
need to be re-investigated from scratch.

**Authoritative source tree:** `/home/stephen/ncde-wm-rebuild/magpie/src/` (rebuild source),
deploying to `/usr/local/bin/magpie-talker`. QML: the patch-tree copy
`/home/stephen/my-project/files/full-patch-20260711/src/usr/share/ncde/MagpieTalker.qml` (1877
lines) is authoritative — confirmed byte-matching the live file at `/usr/share/ncde/MagpieTalker.qml`.
The copy at `/home/stephen/ncde-ISO/airootfs/usr/share/ncde/MagpieTalker.qml` (1851 lines) is
**stale** (missing later additions — e.g. `rosterOpen` property, a mute-bell comment) and needs
resyncing from the patch tree before it matters for this feature — this is the same kind of gap
already tracked in the `ncde-iso-followup-20260714` memory, not new.

## Why this exists

Magpie Talker is NCDE's P2P chat/video app, purpose-built for churches/synagogues: classroom-
style religious education calls, and — critically — connecting shut-in members (who can't
attend in person) and missionaries (far from the community) into services and classes. It has
been rebuilt from a decompiled oracle binary multiple times by prior agents who repeatedly left
planned work unfinished, so the operator went into this session genuinely unsure what was
actually complete versus abandoned mid-build.

Two real, confirmed bugs were fixed live this session (2026-07-14), both verified against the
running app, both folded into `ncde-full-patch-20260711.sh`:

1. **Roster crash on every launch.** `MessageHub::roster()`'s "me" entry (the logged-in user's
   own row, always first) never called `gradientFor()` to compute avatar colors, unlike every
   peer entry — `MagpieTalker.qml`'s `Ava` component declares `c1`/`c2` as `property string`,
   so binding them to `undefined` threw `"Unable to assign [undefined] to QString"` on every
   single launch. Fixed: `roster()` now calls `gradientFor(m_meUser, meC1, meC2)` for the "me"
   entry too, matching the peer pattern exactly.

2. **Worldwide discovery was completely inert.** Both `m_dht->start()` call sites in
   `MessageHub.cpp` passed `QString()` (empty) for the DHT bootstrap host. `DhtBand::start()`
   only calls `bootstrapInto()` when that string is non-empty — with it empty, the OpenDHT node
   ran fully isolated. It could never discover or be discovered by any other Magpie instance,
   locally or worldwide — the app's entire reason for using OpenDHT (the same library Jami/GNU
   Ring uses) was silently dead. Confirmed via `strings` on both the current and an older
   prebak binary that no bootstrap host was ever compiled in either — this predates the
   rebuild entirely, it isn't a reconstruction loss. Fixed to the standard public OpenDHT entry
   point, `bootstrap.jami.net:4222` (confirmed against Jami's own docs — network ID 0, the
   default public network; third-party apps using their own key namespace, which Magpie
   already does via `"magpie:cs:"`/`"magpie:inbox:"`/`"magpie:geo:"` prefixes, is documented
   supported usage, not a hack). **Live-verified**: `statusChangedCallback` fires `Connected`
   status after a real bootstrap round-trip to the real public server.

Also confirmed **not** a gap: green-screen/virtual-background replacement. `FlutterCall`'s
GStreamer pipeline already does real chroma-keying (the `alpha` element, `method=3`, live
`target-r/g/b` color match via `setKeyColor()`), `MessageHub::videoBackgrounds()` correctly
scans the real `/usr/share/ncde/flutter-backgrounds/` folder (six real images the operator
made, `1.png`–`6.png`, already deployed live), and `MagpieTalker.qml` has a complete picker grid
UI wired to `hub.setVideoBackground()`. This was fully built and working the whole time; it just
needed working calls to actually exercise it, which the DHT fix now provides.

**Group video calling is the one confirmed, genuine, ground-up gap** — not lost/dormant code.
This was checked against the *original oracle binary's own DWARF struct layout*
(`FlutterCall.ptype.txt`), which is byte-for-byte identical to the current reconstruction (152
bytes, fully accounted for): `m_webrtcbin`, `m_localVideoSink`, `m_remoteVideoSink`,
`m_localVideoTarget`, `m_remoteVideoTarget` are all singular pointers, never arrays or a
participant count. The shipped app was genuinely 2-party-only. Same story in `MessageHub`:
`m_callState`, `m_callPeerId`, `m_callIsCaller` are all singular, matching the oracle exactly.

## Requirements (from the operator)

- No central media server — Magpie is fully P2P/OpenDHT by design; a Zoom-style SFU would mean
  standing up and hosting server infrastructure, which conflicts with the app's whole
  philosophy.
- "A way to do a grid layout of callers" — the actual ask is the UI/engine work to show
  multiple simultaneous video feeds, not literally cloning Zoom's server architecture.
- Realistic scale: classroom/congregation calls, connecting shut-ins and missionaries — not
  hundreds of participants.

## Architecture decision: Mesh

Every participant connects directly to every other participant (multiple pairwise WebRTC
connections) instead of routing through a server. This is the standard approach for small
groups (~5-8 people) — confirmed via research; SFU (what Zoom/Meet/Jitsi use in production) only
wins at larger scale specifically *because* it needs a server, which is the one thing ruled out
here. Mesh is also the smallest possible extension of what already exists: the current 1:1 call
is architecturally "mesh with N=2."

Sources referenced during design: [WebRTC Architecture Explained: P2P vs SFU vs MCU vs XDN](https://www.red5.net/blog/webrtc-architecture-p2p-sfu-mcu-xdn/),
[WebRTC Multiparty Video Alternatives, and Why SFU is the Winning Model](https://bloggeek.me/webrtc-multiparty-video-alternatives/),
[Building the Grid: Dynamic Video Compositing with GStreamer and Python](https://dev.to/deepak_mishra_35863517037/building-the-grid-dynamic-video-compositing-with-gstreamer-and-python-34g5),
[compositor — GStreamer documentation](https://gstreamer.freedesktop.org/documentation/compositor/index.html),
[Jami distributed network — Jami documentation](https://docs.jami.net/en_US/user/jami-distributed-network.html).

## Current architecture, as verified (not guessed)

### Signaling transport (1:1 today)

Bespoke JSON-over-TCP, newline-delimited — **not** routed through `DhtBand` at all today:

1. `MagpieTalker.qml:542` — `hub.startCall(hub.activeId)` on tap.
2. `MessageHub::startCall(peerUuid)` (`MessageHub.cpp:1428-1449`) — sets call state, lazily
   constructs the single `FlutterCall*` via `ensureFlutterCall()` (`MessageHub.cpp:1501-1516`),
   wires `FlutterCall::localSdpReady`/`localIceCandidateReady` to `sendCallSignal()`.
3. `sendCallSignal()` (`MessageHub.cpp:1418-1426`) wraps the payload as
   `{"t":"call_signal","user":m_meUser,"kind":type}` and calls `deliverTcp(m_peers[to], m)`.
4. `deliverTcp()` (`MessageHub.cpp:344-361`) opens a fresh `QTcpSocket` straight to
   `p.ip:p.tcpPort` — the peer's address as cached in the `m_peers` roster (populated by LAN
   multicast beacon `239.255.42.99:45454` and/or Bonjour/Avahi mDNS for LAN peers, or from the
   DHT presence record's self-reported host/ip/port for `DhtBand`-discovered peers).
5. Receive side: `handleWireObject()` (`MessageHub.cpp:366-484`) dispatches on `"t"`/`"kind"`:
   `offer`→ring/`incomingCall`, `answer`→`onRemoteSdp`, `ice`→`onRemoteIceCandidate`,
   `bye`→`stop()`+`callEnded`.

**Known reliability gap (confirmed, not present in either agent's ground-truth summary until
verified against the actual source):** a relay TCP connection already exists (`m_relay`,
`connectRelay()`, `MessageHub.cpp:1837-1849`; `sendRelay()`, `MessageHub.cpp:1851-1863`) whose
**inbound** handler already forwards `call_signal` objects (comment names it explicitly at
`MessageHub.cpp:1947`) — but `sendCallSignal()` never calls `sendRelay()` as an outbound
fallback. For `DhtBand`-sourced (worldwide) peers behind NAT, the self-reported `p.ip` is often
a private LAN address; a direct `deliverTcp()` to it will simply fail with no fallback. **This
likely makes 1:1 worldwide calls unreliable today** — the app's actual stated purpose
(shut-ins/missionaries) — independent of group calling, and group calling would inherit and
amplify this (N−1 unreliable legs per node instead of 1).

A second, related gap: `onDhtInboxMessage()` (`MessageHub.cpp:1193-1220`) has **no `"t"`/`"kind"`
dispatch at all** — every DHT inbox payload is unconditionally treated as chat text. Offline
group invites (the actual shut-in/missionary scenario) need to ride this same DHT
store-and-forward path, so this needs generalizing too.

### FlutterCall (WebRTC engine) — current pipeline

Single `gst_parse_launch()` string (`FlutterCall.cpp:105-122`):
```
webrtcbin name=sendrecv bundle-policy=max-bundle compositor name=comp
background=black sink_0::zorder=0 sink_1::zorder=1 ! videoconvert !
tee name=vtee appsrc name=bgsrc format=time ! imagefreeze name=bgfreeze
allow-replace=true is-live=true ! video/x-raw,framerate=30/1 !
videoconvert ! comp.sink_0 v4l2src name=camsrc ! videoconvert !
videoscale ! video/x-raw,width=1280,height=720 ! alpha name=keyer
method=set alpha=1.0 ! comp.sink_1 vtee. ! queue ! glsinkbin
name=lsinkbin sink="qml6glsink name=localsink" vtee. ! queue ! vp8enc
deadline=1 target-bitrate=1000000 ! rtpvp8pay pt=96 !
application/x-rtp,media=video,encoding-name=VP8,payload=96,
clock-rate=90000 ! sendrecv. pulsesrc ! audioconvert ! audioresample !
queue ! opusenc ! rtpopuspay pt=97 !
application/x-rtp,media=audio,encoding-name=OPUS,payload=97,
clock-rate=48000 ! sendrecv.
```
The `compositor name=comp` here mixes exactly two things: the live camera feed and the
(optional) frozen backdrop image — this is the already-working green-screen feature, and stays
completely untouched by group calling; it's a separate concern (what I *send*) from receiving
and displaying N remote peers (what I *see*).

`webrtcbin` already has STUN configured (`stun://stun.l.google.com:19302`,
`FlutterCall.cpp:134-137`) and an inert TURN hook via `MAGPIE_TURN_SERVER` env var
(`FlutterCall.cpp:140-142`, currently unconfigured — see open questions).

Remote video decode (`onPadAdded`/`onDecodePadAdded`, `FlutterCall.cpp:529-583`) already
dynamically builds a `decodebin → glsinkbin/qml6glsink` chain per incoming pad — it just
hardcodes the sink name `"remotesink"` and writes into the single `m_remoteVideoTarget`.
Generalizing this per-peer is less invasive than it sounds (see Phase 3).

### QML call UI — current

`MagpieTalker.qml:1671-1803` (`flutterLayer`): one full-viewport `GstGLQt6VideoItem`
(`flutterRemote`, bound via `hub.attachRemoteVideoTarget()`), one small postage-stamp local
preview (`flutterLocal`, 216×124, bottom-right), status text, Hang Up, the backdrop/green-screen
picker (already working, untouched by this feature), ringing overlay (`1805+`), consent-gate
overlay (`1841+`). Both video items are explicitly *not* inside a `Loader` (comment at
`1667-1669`) because `FlutterCall` keeps a raw `QQuickItem*`.

The `callable` gate (`MagpieTalker.qml:530`) currently **excludes channels from calling
entirely**: `readonly property bool callable: !hub.activeIsChannel && hub.activeId !== "" &&
hub.callState==="idle"` — a direct signal that calling was designed 1:1-only.

### "Channel" concept — a false lead, confirmed not usable groundwork

`m_channels` (`MessageHub.h:319`) is a flat `QVariantList` of `{id, name, topic, muted, unread}`
— **no membership list field anywhere in the codebase.** `createChannel()`/
`joinExistingChannel()` (`MessageHub.cpp:906-942`) only mutate this local list; nothing is
announced over the network. `sendMessage()` to a channel id falls into the single-recipient
DHT-inbox path (there's no fan-out because there's no membership to fan out to) — channels today
are purely local UI relabeling. Confirmed via `decompiled/MessageHub.ptype.txt` that the
*original* oracle binary had the same bare structure — not a reconstruction loss either.
`isChannel` fields are just a UI discriminator (hash icon vs. avatar), not group infrastructure.
`BonjourDiscovery`'s "group" (`m_groupPath`) is an unrelated Avahi D-Bus `EntryGroup` (mDNS
record-publishing group) — a false-cognate naming collision, not chat/call groups.

## Phased build plan

### Phase 0 — Signaling reliability (prerequisite, build first)

- Extend `sendCallSignal()` (`MessageHub.cpp:1418-1426`) to branch on `Peer::source`
  (`Peer.h:22`): `"lan"`/`"bonjour"` → `deliverTcp()` only (already reliable, same subnet, no
  NAT). `"dht"` (worldwide, NAT status unknown) → `sendRelay()` as the primary path (wrapping
  the identical `call_signal` JSON envelope), with `deliverTcp()` as an opportunistic secondary
  attempt. Both `handleWireObject()` call sites already funnel into one dispatcher and the
  offer/answer/ice/bye handling is idempotent enough that occasional duplicate delivery is
  harmless — no dedup logic needed.
- Generalize `onDhtInboxMessage()` (`MessageHub.cpp:1193-1220`) to dispatch on a `"kind"` field
  in `payload` (mirroring `handleWireObject()`'s `"t"` dispatch at `MessageHub.cpp:368`),
  defaulting to today's `"text"` behavior for backward compatibility. Small, self-contained,
  independently testable — and required groundwork for Phase 1's offline group invites.
- **Testable independently:** two `magpie-talker` instances on genuinely different networks
  (not same LAN), confirmed DHT-discovered, `startCall()` reaches `mediaState == "connected"`
  end-to-end. Verify via journal (relay-fallback log line + `onDhtConnected(true)`) — same
  discipline as the rest of this project.

### Phase 1 — Real group/channel membership model

Add a new `GroupSession` struct (new functionality, not oracle-DWARF-constrained since the
oracle never had this):
```cpp
struct GroupSession {
    QString id;
    QString name;
    QString topic;
    QString ownerUuid;
    QStringList memberUuids;   // includes m_meUuid
    bool muted = false;
    int  unread = 0;
};
```
Store as `QHash<QString, GroupSession> m_groups`, appended to `MessageHub`'s member list
*after* `m_msgSeq` (`MessageHub.h:325`) — not interleaved — so the existing byte-exact-with-
oracle prefix (`MessageHub.h:275-325`, matching `MessageHub.ptype.txt`) stays intact for
auditing purposes.

- `channels()` (backed by `m_channels`) becomes a projection rebuilt from `m_groups` (add
  `"members"` and `"isGroup": true`), so existing QML bindings keep working.
- **Creation:** new slot `createGroup(name, memberUuids)`, reusing existing roster/contacts
  data (`m_contacts`, `Contact.h`, `contactGroups()`/`roster()`) — no new discovery mechanism.
- **Invite fan-out, existing transports only:**
  - Online members → new wire kind `{"t":"group_invite","user":m_meUser,"group":{...}}`
    through the same Phase-0 dual-path (`deliverTcp` for LAN, `sendRelay` for DHT-sourced).
  - Offline members (the actual shut-in/missionary case) → `DhtBand::sendInbox()`
    (`DhtBand.h:70-71`), exactly the mechanism text messages already use, `"kind":"group_invite"`
    in the payload, routed by Phase 0's generalized `onDhtInboxMessage()` dispatch.
  - Receive side: new `t == "group_invite"` branch in `handleWireObject()` upserts into
    `m_groups`, emits existing `channelsChanged()` plus a new
    `groupInviteReceived(QString groupId, QString fromName)` for a QML accept/toast prompt.
  - Add `"member_left"`/`"group_leave"` wire kinds too.
- **Bonus low-risk deliverable, fully independent, zero WebRTC involvement:** once `m_groups`
  has a real member list, loop `deliverTcp`/`sendRelay`/`sendInbox` per `memberUuids` for group
  `sendMessage()` calls — real group *text* chat becomes possible. Good first demo to rebuild
  trust before touching the media pipeline.
- **Testable:** create a 3-person group (2 LAN + 1 simulated offline/DHT peer), confirm correct
  membership and group text chat, verified via journal + QML channel list — zero WebRTC.

**Open question:** does "channel" (existing topic/mute/unread UI) become identical to "group"
for calling purposes, or stay a separate entity? Recommend unifying — avoids two near-identical
concepts — but this is an IA call for the operator, not an engineering one.

### Phase 2 — Signaling fan-out (mesh: every node runs its own N−1 pairwise exchanges)

Generalize call state from strictly-singular to session-scoped, **without changing 1:1
behavior**: keep `m_callState` for lifecycle, add `QString m_activeCallGroupId` (empty ⇒
today's 1:1 path unchanged) and `QSet<QString> m_callParticipants` / `m_callInvited`.

- `sendCallSignal(to, type, payload)` is already parameterized per-peer — the right primitive.
  `startCall()`/`acceptCall()` generalize into a loop: for a group call, each node independently
  performs its own N−1 pairwise offer/answer/ICE exchanges. No node ever computes the full
  C(N,2) — that count (28 pairwise links for N=8) only matters for reasoning about aggregate
  mesh load, not anything any single node handles.
- New `"call_join"`/`"call_leave"` wire kinds alongside `"call_signal"`: existing participants
  answer a join announcement with their own presence, so the joiner's per-peer loop knows who
  to open pairwise connections against. Reuses the Phase-0 dual-delivery path, no new transport.
- Group ringing: initiator sends N individual invites; QML ringing overlay needs a group-aware
  variant ("Group call: `<name>`" instead of one caller). Accepting joins the mesh via this
  node's own `call_join` + N−1 pairwise offers to whoever's already active.
- **Testable independently of Phase 3/4 UI:** 3 real instances, verify via journal/GStreamer
  logging (not rendering) that each node reaches exactly 2 live `webrtcbin`s at Connected state
  — ship as "3-way mesh negotiation works" before any grid rendering exists.

### Phase 3 — FlutterCall engine: single webrtcbin/sink pair → per-peer collection

- `m_webrtcbin` → `QHash<QString, GstElement*> m_webrtcbins`; `m_remoteVideoSink` →
  `QHash<QString, GstElement*> m_remoteVideoSinks`; `m_remoteVideoTarget` →
  `QHash<QString, QQuickItem*> m_remoteVideoTargets`, all keyed by peer uuid.
- Base pipeline (camera/backdrop compositor, local preview tee, audio tee) stays one
  `gst_parse_launch()` string, unchanged, minus the single `webrtcbin`/RTP legs. `addPeer(uuid)`
  dynamically creates a new `webrtcbin`, adds it to the running pipeline, sets
  `stun-server`/`turn-server` per-bin (same logic as today, `FlutterCall.cpp:134-143`), taps the
  existing `vtee`/`pulsesrc` outputs through a new encode branch per peer (same pattern as the
  single existing branch).
- Static GStreamer C callbacks (`onNegotiationNeeded`, `onIceCandidate`, `onOfferCreated`,
  `onAnswerCreated`, `onRemoteSetDone`, `onPadAdded`, `onDecodePadAdded`,
  `FlutterCall.cpp:427-583`) currently assume a single global `FlutterCall*` as `userData` — need
  `(FlutterCall*, QString peerUuid)` context instead (small heap struct or closure).
- `onPadAdded`/`onDecodePadAdded` already dynamically builds a per-pad decode chain; today it
  hardcodes the sink name `"remotesink"` — generalizing to per-peer naming/lookup is less
  invasive than it looks.
- Teardown: `removePeer(uuid)` mirrors `teardownPipeline()`'s unref pattern, scoped to just that
  peer; `stop()` remains the "end the whole call" path.

**Architecture fork — needs explicit operator/engineer sign-off before coding, not a silent
pick:**
- **Option A:** a *second*, separate `compositor` (distinct from the existing camera/backdrop
  one) mixing all received remote streams into one flattened frame server-side, rendered into a
  single `flutterRemote` item. QML stays almost unchanged. Downside: per-tile UI (name labels,
  mute icons, speaking indicator) has to be burned into the compositor via GStreamer overlay
  elements, or tracked externally and drawn as a disconnected QML overlay — awkward.
- **Option B (recommended):** generalize the *already-present* per-peer decode→`qml6glsink`
  pattern so each accepted remote peer gets its own sink, and QML positions them in a
  `Repeater` grid (Phase 4). No second compositor added at all — reuses the existing per-peer
  code path verbatim, and gives essentially free per-tile QML overlays (name, mute, speaking
  indicator) — valuable for a classroom/church UI where knowing who's who matters.
- Recommendation reasoning: "reuse the compositor already in the pipeline, don't add a second
  compositing mechanism" most plausibly means "don't add a server-side SFU/MCU mixing
  component" (the thing actually ruled out) — not "literally route received remote video
  through the same compositor instance that mixes local camera+backdrop for the outbound feed,"
  which would conflate what I *send* with what I *receive and display*.
- **Testable independently:** a dev-only 3-node harness driving `FlutterCall` directly (bypass
  full group-invite UI), confirm 2 simultaneous remote peers render correctly, verified via
  visual check + `GST_DEBUG_DUMP_DOT_DIR` pipeline graph dump.

### Phase 4 — QML grid UI

Replace the single full-viewport `flutterRemote` item (`MagpieTalker.qml:1681-1685`) with, per
Option B, a `Repeater` bound to a new `MessageHub` property `callParticipants` (`QVariantList`
of `{uuid, name, muted}`):
```qml
Grid {
    id: remoteGrid
    anchors.fill: parent
    columns: Math.ceil(Math.sqrt(hub.callParticipants.length || 1))
    Repeater {
        model: hub.callParticipants
        delegate: GstGLQt6VideoItem {
            width: remoteGrid.width / remoteGrid.columns
            height: remoteGrid.height / Math.ceil((hub.callParticipants.length||1)/remoteGrid.columns)
            Component.onCompleted: hub.attachRemoteVideoTarget(modelData.uuid, this)
        }
    }
}
```
Requires an overloaded `attachRemoteVideoTarget(const QString &peerUuid, QObject *item)`
alongside the existing single-arg one — keep the old overload as the 1:1 default so that path
is never broken.

**Preserve unchanged:** local preview, Hang Up (`endCall()` now tears down the whole group
session), the backdrop/green-screen picker (entirely orthogonal, already fully working), the
consent-gate overlay (one-time local camera/mic permission, not per-peer). `flutterLayer`'s
visibility gate is unchanged since `m_callState` stays session-scoped. Ringing overlay needs a
small group-aware variant.

The `callable` predicate (`MagpieTalker.qml:530`) currently excludes channels entirely — must be
revised alongside Phase 1's group model, likely via a distinct "Start Group Call" affordance on
a group's header, parallel to today's per-DM call button.

**Testable:** live N-person (operator-capped) group call, all faces visible in a grid, Hang Up
ends for everyone (each node sends `bye`/`call_leave` independently to its own N−1 peers), a
mid-call joiner triggers live grid reflow on all existing participants' screens.

## Recommended order and why

**Phase 0 → Phase 1 (membership + text fan-out) → Phase 2 (3-person mesh signaling, no UI grid)
→ Phase 3 (FlutterCall engine) → Phase 4 (QML grid).**

1. Phase 0 isn't optional groundwork — it's a correctness bug group calling would otherwise
   inherit and amplify, and it's independently valuable (fixes 1:1 worldwide calling, the app's
   actual stated purpose) even if group calling were cancelled entirely.
2. Given this app's history of unfinished work across prior rebuilds, each phase lands as a
   real, demoable, independently-verifiable increment — nothing in a later phase requires
   guessing at an earlier phase's internals. Phase 1's group text fan-out in particular is a
   complete, useful, low-risk feature shippable with zero WebRTC changes — a good
   trust-rebuilding first deliverable before touching the GStreamer pipeline at all.

## Decisions (operator, 2026-07-14)

1. **Phase 0 timing** — not explicitly confirmed; defaulting to the recommendation (build as
   prerequisite, standalone value for 1:1 worldwide calling too) unless redirected.
2. **Max participants: 8** (revised 2026-07-15, was 12). Hard-cap in Phase 1 (group creation) and
   Phase 2 (join gating). Changed after live web research (see sources below) showed 12 is
   described as "at or beyond the practical limit" for pure mesh, not comfortably inside it —
   most sources put mesh's realistic ceiling around 8-10 and call 2-4 the genuinely comfortable
   range; at N=12 each device encodes/decodes 11 simultaneous streams, called "extreme" client
   load in multiple independent sources. At N=8, full mesh is C(8,2)=28 pairwise links, each node
   handling its own 7 legs — still heavier than the 5-8 "comfortable" case some sources cite, but
   well clear of the 11-leg "extreme" case at 12. Still revisit the CPU spike in point 6 with
   N=7 legs specifically before committing to pure mesh at this cap — may need per-participant
   resolution/bitrate scaling down as N grows regardless.
   Sources: [What is WebRTC P2P mesh and why it can't scale? — BlogGeek.me](https://bloggeek.me/webrtc-p2p-mesh/),
   [WebRTC Network Topology: Complete Guide to Mesh, SFU, and MCU Architecture Selection](https://antmedia.io/webrtc-network-topology/).
3. **Group invite UX: invite-only** (explicit accept per invitee) — confirmed, matches the
   recommendation and the pastoral/privacy context.
4. **Channel/Group unification: confirmed, same thing.** Creating a "classroom" *is* creating
   the channel/group — there is no separate group concept from the channel UI. `createGroup()`
   (Phase 1) and `createChannel()` become the same call; the channel *is* the classroom/room,
   with real membership backing it (Phase 1's `GroupSession`) instead of today's memberless
   local label.
5. **GStreamer architecture: QML side — Option B confirmed** (per-peer `qml6glsink` tiles via
   `Repeater`, not a second server-side compositor). Matches the recommendation.
6. **Resource-friendliness is a hard requirement**, not just a spike-and-see. Given the N=8
   cap (point 2), Phase 3 must treat per-participant encode/decode cost as a first-class design
   constraint, not an afterthought:
   - Lower default resolution/bitrate for group calls vs. today's 1:1 tuning
     (`target-bitrate=1000000` at `FlutterCall.cpp:117`) — e.g. scale bitrate down as
     participant count grows.
   - Consider capping simultaneous *decoded* remote tiles below 8 even if signaling supports
     more (e.g. active-speaker prioritization, pause decode for off-screen/scrolled-out tiles)
     — most classroom UIs don't render every participant at full res simultaneously.
   - The CPU spike (point 2) is not optional — must happen early in Phase 3, before the full
     per-peer engine redesign is considered committed, specifically on hardware representative
     of a shut-in member's setup (not a dev workstation).
7. **TURN server: yes, provision one.** Needed for symmetric-NAT participants (worldwide
   shut-ins/missionaries are exactly the case most likely to sit behind restrictive NAT).
   Doesn't violate "no central media server" — TURN only relays opaque encrypted packets, it
   doesn't decode/mix/participate in the call otherwise. This becomes real infrastructure setup
   work (hosting a `coturn` instance or similar, wiring its address into `MAGPIE_TURN_SERVER`
   or an equivalent Settings-configurable field, since the app currently has zero settings UI
   for this — same "add a config path that doesn't exist yet" work as DHT bootstrap needed
   tonight). Add as an explicit Phase 0 sub-task: provision + wire TURN configuration, don't
   leave it as an inert env var.
8. **QML file sync: resolved.** The patch-tree copy
   (`full-patch-20260711/src/usr/share/ncde/MagpieTalker.qml`) is authoritative and confirmed
   byte-matching live. The ISO-tree copy is stale and needs resyncing before Phase 4 edits.

## Critical files for implementation

- `/home/stephen/ncde-wm-rebuild/magpie/src/MessageHub.cpp` / `.h`
- `/home/stephen/ncde-wm-rebuild/magpie/src/FlutterCall.cpp` / `.h`
- `/home/stephen/ncde-wm-rebuild/magpie/src/DhtBand.h`
- `/home/stephen/ncde-wm-rebuild/magpie/src/Peer.h` (source of `Peer::source`, needed for
  Phase 0's LAN-vs-DHT branch)
- `/home/stephen/my-project/files/full-patch-20260711/src/usr/share/ncde/MagpieTalker.qml`
- Build via `/home/stephen/ncde-wm-rebuild/magpie/build.sh` (raw g++/moc, no cmake on this
  node — same pattern as Hummingbird's rebuild, proven working this session)

## Verification discipline for this project (apply to every phase)

Matches the rest of this session's established method — never trust "compiles clean" or
"qmllint clean" alone:
1. Build via `build.sh`, confirm zero compile/link errors.
2. Test-launch the fresh binary directly (not yet deployed) with real X11 session credentials
   (`DISPLAY`/`XAUTHORITY` read from a live process's own `/proc/PID/environ`, e.g. LaPivot's).
3. Watch the live journal for the specific behavior being fixed — add a temporary `qWarning()`
   diagnostic if the success/failure signal isn't otherwise observable, remove it before final
   deploy.
4. Only after live confirmation: `sudo install` with a `.prebak-<date>-<description>` backup,
   then re-verify live.
5. Immediately fold into `ncde-full-patch-20260711.sh` (staged binary/QML copy + `dep()` call if
   missing + regenerate the embedded self-extracting archive + verify extraction via `diff -rq`
   against the staged tree + sync to the USB mirror) — per the `patch-script-never-goes-stale`
   standing rule established this session. Do this per-fix, not batched at the end.
