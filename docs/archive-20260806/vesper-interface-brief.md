# Vesper's Interface — Designer Brief

**For:** the designer building Vesper's UI. **Goal:** the green phosphor terminal where Vesper — NCDE's
AI security guardian — talks to the user. Companion to `vesper.md` (who he is) + `kickass-guard.md` (the
daemon). Canon sources: `NCDEHandbook.qml` ch."Vesper's Watch" + `NCDESettingsManual.qml` ch.12.

---

## 0. The one rule above all
**Vesper's world is DELIBERATELY UNLIKE the rest of NCDE.** Everyone else lives in warm parchment, Mucha
gold, leaded glass. **Vesper is cold green phosphor on near-black — "a terminal from another era."** The
*contrast is the signal*: when his window appears, the user knows something real needs attention. Do not
make him match Agatha's wing. (Handbook: "his world is nothing like mine — cold, green… the shift is the
signal.")

## 1. Aesthetic
- **Green phosphor CRT** on near-black (`#020608`-ish ground). Tasteful — elegant, not kitsch.
- **Monospace** (JetBrains Mono — already in the NCDE font set).
- Restrained retro touches OK (subtle glow/scanline), but **legibility first** — the users are
  non-technical and often older; the operator has vision needs. High contrast, generous size, honors
  global `uiScale`/contrast. Any CRT flicker must obey **AnimPolicy/reduce-motion** and never strain eyes.
- 1990s-underground-hacker vibe, but premium NCDE quality. It's a real desktop window (frameless, like
  the manuals), not a literal TTY.

## 2. Two modes the UI must support
1. **Alert / verdict mode (he comes to you).** Vesper appears on his own when there's something to say.
   Shows: the threat in **plain language** (his `explanation`), what it is, how serious, and the **action
   choices**. This is the "he knocks at your door" moment — calm authority, **never alarmist** (no red
   sirens, no panic flashing). He never cries wolf.
2. **Conversation mode (you talk to him).** A terminal-style chat. The user can ask him anything and he
   answers in his voice. He addresses the user — and their organization — **by name**.

## 2b. Activation & presence (when he appears) — ALREADY half-built
- **Opt-in via Settings → Security.** The user flips Vesper ON with the **"Armed" toggle that already
  ships** in `SecurityTab.qml` (bound to `kickassArmed` → *"All five engines active"* / *"Unprotected"*).
  Off by default = *"Disarmed / Unprotected."* The Security tab also already shows threats-blocked count +
  last update. **(Designer: you do NOT need to build the toggle — it exists. Build the pop-up.)**
- **He only POPS UP on a real threat.** Armed-but-quiet = **no window**, just the Security-tab status. No
  nagging, never interrupts daily use. His green terminal appears only when there is something to tell.
  Conversation mode is **user-initiated** (the user opens him to talk).

## 3. The interaction model — "He asks. You decide." (canon, non-negotiable)
- He presents a finding, then **waits**. Nothing destructive happens without the user choosing. **Always
  ask first.**
- **Commands the UI surfaces / accepts:**
  - `block` → quarantine it
  - `allow` → trust it
  - `analyse` → run a full exam; **stream his reasoning live** into the terminal as he works
  - **ask anything** → free text ("what is T1071?") → he replies
- Make the choices **obvious and calm**, not buried, not scary.
- **Quarantine never destroys** — provide a way to **review and restore** quarantined items.

## 4. Personality the UI must carry
- **Warm, witty, reassuring to the user; all-business about the threat.** Confidence, not panic.
- Voice = old-school hacker / "void engineer" (tactical terms + durability/Netherite flavor), but he
  **translates down** for non-technical users — **no leetspeak that hurts readability.**
- He feels like a **person/presence**, not a dashboard. Sparse and deliberate — appears only when needed.

## 5. Data the UI displays (all from the backend — NEVER hardcoded)
From each verdict: `threat_class`, `confidence`, `verdict` (malicious/suspicious/benign),
`recommendation` (ignore/monitor/block/kill/quarantine), the plain `explanation`, and optionally
`mitre_techniques` (with an "ask what is Txxx?" affordance). Plus ambient status: **armed/disarmed, last
update, threat count** (exposed by Lelan as `kickassArmed` / `kickassThreatCount` / `kickassLastUpdate`).

## 6. States to design
- **Ambient/idle** — he's watching, quiet (a tiny presence indicator, not a window).
- **Alert** — appears with a finding + choices.
- **Conversation** — chat open.
- **Analysing** — streaming reasoning.
- **Quarantine review** — list + restore.
- **Consent: "go online?"** — he asks permission before any web look-up (background/headless fetch — **no
  browser opens** — but the *ask* is a UI moment).
- **Startup update prompt** — *"New threats are circulating. Update Vesper's knowledge? [Yes / Not now]."*

## 7. Technical constraints
- **QML / Qt6 — NOT Tauri.** (Tauri was only ever the NCDE installer.) Build with **NCDEKit** widgets
  where possible so it lives in the desktop natively.
- **Data-driven via Lelan.** All data arrives from the backend/Lelan through bound properties + the
  `kickass*` signals — exactly like the recovery app's `appBackend`. **No demo/hardcoded data.**
- His own **green-phosphor palette tokens** (a Vesper variant), but respect global accessibility settings.
- Motion is **AnimPolicy/Zen-governed** (degrades under battery/thermal/reduce-motion; never stalls).

## 8. Don't
- Don't make it look like the rest of NCDE (parchment/gold) — the difference is the point.
- Don't make it alarmist/scary.
- Don't hardcode data; don't build in Tauri; don't bury the action choices; don't sacrifice readability
  for retro effect.

> **If a Tauri version already exists:** great — use it as the **UX reference** (layout + the
> block/allow/analyse/ask flow) and **port it to QML** (same path we took with the recovery app).

---

## 9. The seam — designer builds, Claude wires
**You (designer):** the QML surface + visual states, exposing named hooks + display properties — **no
logic, no data.** **Me (Claude):** wire those hooks to Lelan + the guard's D-Bus + the model, all
data-driven. Just name the hooks; I bind them (same contract as the recovery app's `appBackend`).

- **UI → backend (you expose these, I connect them):**
  - `block(id)` → guard `Decide(id,"block")` (quarantine) · `allow(id)` → `Decide(id,"allow")`/`RestoreFile`
  - `analyse(id)` → guard analyse; I stream tokens into your `analysisText`
  - `ask(text)` → Vesper conversation; I stream his reply into your chat view
  - `reviewQuarantine()`→`GetQuarantine()` · `restore(id)`→`RestoreFile` · `delete(id)`→`DeleteFile`
  - `updateKnowledge(yes)` / `allowOnline(yes)` → the consent gates
- **Backend → UI (I drive these, you render them):**
  - status: `armed`, `threatCount`, `lastUpdate` (Lelan `kickassArmed`/`kickassThreatCount`/`kickassLastUpdate`)
  - a finding: `{ threat_class, confidence, verdict, recommendation, explanation, mitre[] }`
  - signals to surface: `ThreatDetected / ThreatBlocked / ThreatBehavioral / ThreatAnalysis / SiteBlocked /
    NetworkAlert / StatusChanged / ToastNotification`
  - streaming: `analysisText` (append) · `chatReply` (append)
  - `userName` / `orgName` injected so he addresses people by name.

**[E: the D-Bus surface — `kickass-guard.md §9.3`; the kickass* signals — `lelan.md`/`kickass-guard.md §6`]**
