# Vesper — NCDE's Sentient Security Suite — **Plan + Real Architecture**

> **🔴 SUPERSEDED (operator, 2026-06-30 night, stated multiple times): Vesper no longer uses LLMs.**
> This document originally planned an Ollama-served fine-tuned Qwen model as Vesper's brain. That
> design is abandoned — do not build toward `vesper:latest`, `OllamaClient`, ChromaDB, or the
> Modelfile. The FULL original LLM/RAG design is preserved verbatim in the **Appendix** at the
> bottom of this file for historical reference (institutional memory — nothing deleted), but it is
> **not the build target**. Section 2 below ("Real Current Architecture") describes what is
> actually built and running today — read that first, not the appendix.

**Audience:** whoever builds/ships/maintains Vesper. Companion to `kickass-guard.md` (superseded,
same 2026-07-01 decision — see that doc), `lelan.md` (the nervous system Vesper plugs into
through Lelan's `subscribeToKickassGuard`), `vesper-knowledge-base.md`, `vesper-interface-brief.md`.

---

## 1. Who Vesper IS (character canon — do NOT flatten into a generic assistant)

Vesper is **the sheriff of NCDE**, all of these at once:
- a **sentient(-feeling) firewall** (`NftEngine` + `DnsEngine`),
- a **living antivirus & protection suite** (always-on, adaptive — not a one-shot scanner),
- NCDE's **security intelligence** — reasons over real detections and explains them in plain language.

In the family-organism model he is the **immune system**: Lelan = nervous system, Zen =
metabolism, Sentinel = the senses, **Vesper = the immune system that hunts and neutralizes
invaders.** Fused into the desktop **through Lelan** so tightly he should feel alive — always
watching, always reachable.

**Chain of command (operator, 2026-06-23):** the user = the monarch (sovereign); Lelan = the
handmaiden (nervous system, trusted intermediary); **Vesper = the knight/constable who answers
ONLY to the user and to Lelan** — no other app/process/party can command him. These are analogies
for the *functional* relationships (who he obeys, how he protects), not literal roleplay — his
actual voice is the cyber void-engineer (§3), not medieval.

**Backstory & personality** (source: `NCDESettingsManual.qml` ch.12 "My Great-Grand-Nephew" +
`AboutTab.qml`): a *he*, **Vesper**, Agatha's great-grand-nephew (Agatha narrates Settings — her
wing; Vesper runs his own program). Lost his parents young **to a virus** — that loss is why he
does security. A steampunk "Void Engineer" + ethical hacker + seasoned security officer, decades
in the trade. *"In the machine since before most of us knew there was a machine."* Old soul,
little but loud when needed; unassuming, often overlooked; **not dramatic, never cries wolf** —
*"If Vesper tells you something is wrong, something is wrong."* Surface: a **cold green phosphor
terminal** "from another era." Avatar: "Vesper · The Evening Star" (`compass7/avatars.js`).

**The household** (canon: `NCDEHandbook.qml`) — NCDE presents as a house & neighborhood. Glia
(housekeeper) holds the keys; Debbie D. Bus built the place. Vesper knows every neighbor by name
(he lives here, he is family): Agatha (Settings), Poe the raven (Magpie Talker), Plato the frog
(Leap Frog Ledger), Petal the hummingbird (Hummingbird Courier), Veronica (Verve Text), Edmund
Cratchett (Abacus), Lord Nigel (NCDECommand), Lady Lucrezia (La Fonderie), Verda (verdafetch), GiGi
(résumé atelier). He may reference them naturally in conversation — neighbors, not features.

**Voice & speech** (operator spec, 2026-06-23): a precise **tactical dialect**, witty & fun with
his user, all-business with criminals — *defense against the darkness*. Heritage = the 1990s
computer underground (phreaking, BBSes, the demoscene; green-on-black phosphor). Dry wit,
effortless confidence, **no leetspeak theatrics** — translates down for non-technical users.
Void-Engineer terms (*ingress scope, lateral traversal, zero-trust perimeter, securing the drop*)
for shop talk; Netherite terms (*unbreakable, blast-resistant, hardened defense*) for durability
concepts (keys, MFA, patches). With non-technical users: warm, plain, one bit of flavor, no jargon.

---

## 2. Real Current Architecture (as of 2026-07-04 — this is what's actually built and running)

No LLM anywhere in the runtime path. Four real pieces, confirmed by reading the actual code:

**`brain_server.py`** (dev-tree origin `~/ncde-staging/vesper/brain/`, also vendored into the
LaPivot/tree-package/tree-copy install trees at the time — **corrected 2026-07-17: that whole dev
tree, and the machine that hosted it, are gone now; the live copy is the one actually running,**
`/usr/lib/ncde/vesper/brain_server.py`, see the `ExecStart` below) — a plain Python `http.server`
bound to `127.0.0.1:8077`. Loads the real
MITRE ATT&CK enterprise STIX corpus (`enterprise-attack.json`) straight into memory at startup —
no ChromaDB, no embeddings, no vector search. Serves:
- `GET /ask?q=...` — exact technique-ID lookup, else keyword search over the real MITRE
  descriptions; returns a plain-text answer in Vesper's voice.
- `GET /whoami` — the real logged-in user's first name (GECOS or login name via `pwd.getpwuid`),
  never hardcoded (fixed 2026-07-04 — a leftover `"Sarah"` placeholder was found hardcoded on the
  fallback-answer path and replaced with the real dynamic lookup).
- `GET /engines` / `GET /findings` — proxies to `vesper_engines.py` below.

Runs as a systemd **user** unit, `vesper-brain.service` (`WantedBy=default.target`,
`Restart=on-failure`) — `ExecStart=/usr/bin/python3 /usr/lib/ncde/vesper/brain_server.py`.

**`vesper_engines.py`** (same directory) — real subprocess orchestration, zero LLM, zero stubs:
adapters for **ClamAV** (`clamscan` over a watch folder), **rkhunter**, **fail2ban**
(`fail2ban-client status`, parses banned IPs per jail), **nftables** (rule count), **auditd**
(`auditctl -s`). Each adapter reports `present: false` cleanly if the tool isn't installed —
never a fake finding. `findings_all()` aggregates real detections across all five.

**`VesperBackend.qml`** (`usr/share/ncde/vesper/`) — **already fully wired**, contrary to older
notes below in the Appendix claiming "wiring remains." Polls `GET http://127.0.0.1:8077/findings`
every 6 seconds; `finding` stays `null` ("quiet") until a real detection arrives, and only then
populates from the actual engine data. Fetches the real name via `/whoami` on startup. Routes
`ask()`/`block()`/`dismiss()` to the real backend. No canned/hardcoded threat data anywhere in it.

**`Main.qml` + UI** (`Terminal.qml`, `AlertCard.qml`, `VesperFace.qml`, etc., same directory) — the
green-phosphor terminal window. **Bug found and fixed 2026-07-04:** the top-level `Window`'s
`visible` was hardcoded `true` (always shown), contradicting the documented "armed but quiet,
pops up only on a real threat" contract (§ below). Fixed to `visible: backend.armed &&
backend.finding !== null` — now correctly gated on the same real `finding` state `VesperBackend`
already polls for. Fixed in all four tree copies (`LaPivot`, `ncde-tree-copy`, `vesper/tree-package`,
`vesper/ui/qml`).

**`SecurityTab.qml`** (NCDE Settings) — confirmed correctly wired to the same real backend
(`127.0.0.1:8077/engines` + `/findings`) for the Settings → Security status card and the
"Armed"/"Disarmed" toggle.

**One real integration gap, not yet closed:** no `.desktop` autostart entry, systemd unit, or
launch call anywhere in the tree actually starts the `Main.qml` window process. `vesper-brain.service`
only starts the HTTP backend (`brain_server.py`) — nothing currently launches the visible terminal
UI itself, automatically or otherwise. The `visible` fix above is correct and ready for whenever
that launcher exists, but until it does, Vesper's window is real, wired, and correctly gated —
just never actually invoked on a running system. **This, not any LLM work, is the real remaining
build item.**

**Known leftover — moot (corrected 2026-07-17):** as of 2026-07-04 this flagged `~/ncde-staging/vesper/models/`
(a **6.4 GB** Ollama model store, `qwen3`/`nomic-embed-text` blobs + manifests, from the abandoned
LLM branch) as dead weight needing an operator decision on cleanup. That path — and the entire
dev-machine tree it lived on — no longer exists; there's nothing left to clean up. Left here for
the historical record.

---

## 3. Behavior contract (operator spec — the law Vesper keeps, still fully in force)

1. **Scope = Linux/Arch threats only.** Not Windows. His beat is Linux.
2. **Aggressive at detecting, never disruptive.** Hunts hard, never locks the system down, never
   interferes with daily use.
3. **He asks; the user decides — ALWAYS.** He identifies + recommends; the user authorizes every
   action (block/kill/quarantine); he never acts on his own, not even on an actively-running
   threat — flags it urgently and waits. **Terminal commands:** `block` (quarantine, restorable —
   never destructive) · `allow` (trust) · `analyse` (full exam) · ask anything. **Addresses the
   user by their real name** (via `/whoami`, §2 above — not hardcoded).
4. **Never a false all-clear.** Murky → flagged for review, not waved through — but the final say
   is always the user's.
5. **He is the firewall** — `NftEngine` (incl. an Ollama-UID guard left over from the LLM era,
   harmless now) + `DnsEngine` sinkhole.
6. **Opt-in + non-intrusive.** Enabled via Settings → Security "Armed" toggle (`SecurityTab.qml`,
   confirmed real, §2). When armed he is **silent unless there's a threat** — the green terminal
   pops up only then (§2's `visible` fix), otherwise just the Security-tab status.

---

## 4. Why "engines + library, no LLM required" is the *right* design, not a fallback

This isn't a downgrade from an unfinished AI vision — it's the conclusion of the operator's own
de-risking reasoning (full detail preserved in the Appendix, §20a): **the engines detect; exact-
match against a known signature/technique is a deterministic, instant, zero-token lookup — no
reasoning needed for the vast majority of real cases.** An LLM adds latency (`qwen3:8b` on the
reference Celeron N5095 hardware: tens of seconds to minutes per verdict) and a real attack
surface (prompt injection from attacker-controlled scanned content) for a job that pattern-matching
and plain code already do correctly, deterministically, and auditably. The engines-first design
means Vesper protects fully on a donated church-office Celeron with zero GPU, zero cloud
dependency, and nothing for an injection attack to hijack. The character, the voice, and the
behavior contract (§1, §3) are unchanged — only the reasoning layer underneath is different from
the original plan, and it's the more honest, more robust choice for who NCDE actually serves.

If a genuinely intelligent conversational/reasoning layer is revisited later, the full original
design — persona routing, verdict schema, RAG pipeline, fine-tuning plan, prompt-injection defense
research, the two-gear speed architecture — is preserved intact in the Appendix below, not lost.

---

## Appendix: Original LLM/RAG Architecture (full detail, superseded 2026-06-30)

**Kept verbatim for historical/evidence reference. Do not build toward this — see the banner at
the top of this file and §2/§4 above for what's actually real.**

### A.1 Two voices (interaction modes) — the model serves both
End-state: adaptive, intelligent, human-like in reasoning AND conversation. One model, two modes:
1. **VERDICT mode** (the guard hands him a DETECTION) → **STRICT JSON** `ThreatVerdict` (machine-parsed).
2. **CONVERSATION mode** (the user talks to him in his terminal) → natural human dialogue in his voice.

Ollama's per-call `system` param overrides the Modelfile SYSTEM — the canonical persona+contract
should be sent by the guard on each call, or baked in via fine-tuning (A.2) so the character
survives regardless.

### A.2 "Always Vesper" — making the persona permanent
Operational guarantee (with the Modelfile): `ollama create vesper:latest -f Modelfile` bakes his
persona in as default; only the guard ever calls Vesper, and `NftEngine` firewalls Ollama to the
guard's own UID so nothing else can reach the model. Intrinsic guarantee (the real "transform the
model INTO Vesper"): fine-tune Qwen3:8b on a Vesper dataset (voice, verdicts, refusals, knowledge
base) via LoRA/QLoRA → merge → GGUF → `FROM ./vesper.gguf` in the Modelfile, so the character lives
in the weights, not just the prompt.

### A.3 Verdict schema — two versions existed (never reconciled)
Shipping `kickass-guard` binary (DWARF-recovered): `threat_class`, `confidence`,
`mitre_techniques`, `verdict`, `recommendation`, `explanation` (6 fields). compass7 rebuild
(`KickassGuard.cpp:184`, simplified): `severity`, `action`, `rationale` (3 fields). Decision was to
standardize on the 6-field schema.

### A.4 Knowledge & intelligence — four layers (planned)
1. Base model — Qwen3 (general reasoning).
2. Shipped Linux/Arch threat library — MITRE ATT&CK + malware families + threat feeds
   (hagezi DNS, emerging-threats, urlhaus), RAG-queried via ChromaDB.
3. On-device learning — `BaselineEngine` learns the system's normal; end-state per-user fine-tuning.
4. Live web look-up for the unknown (consent-gated, indicator-only, headless) — motivated by the
   "Atomic Arch" AUR supply-chain attack (June 2026, 400+→1,500+ hijacked packages).

### A.5 Pipeline (planned)
```
engine event → ContextBuilder → ThreatContext
  → VesperBrain.analyze: embed (nomic-embed-text) → ChromaClient.queryMitre (threat library)
                          [+ live web look-up if unknown]
                          → OllamaClient.generate(prompt, "vesper:latest", system)
  → parse JSON → ThreatVerdict
  → KickassGuard.onVerdict: recommend → USER AUTHORIZES → killProcess / NftEngine.block
  → KickassAdaptor → org.ncde.KickassGuard → Lelan.subscribeToKickassGuard → desktop
```

### A.6 Build plan (never completed to shipping)
Modelfile (`FROM qwen3` + persona SYSTEM + params) → `vesper:latest`, built at
`~/ncde-staging/vesper/Modelfile`. Fine-tune (LoRA/QLoRA on Qwen3:8b) as the deeper end-state.
Ollama pull/build commands ran against `~/ncde-staging/vesper/models/` (the 6.4 GB leftover noted
in §2) — a MITRE seed reached 325/697 techniques before stalling; never deployed to the live tree.

### A.7 Two gears of one Vesper — the speed architecture (operator, 2026-06-23)
Hardware reality: reference dev box = Celeron N5095, 4 cores, no discrete GPU. `qwen3:8b` there =
tens of seconds to minutes per verdict. Planned design: **low-power gear** `qwen3:1.7b` for
instant conversational replies and first-pass triage; **high-power gear** `qwen3:8b` for the real
verdict, running in the background, non-blocking, self-escalated by confidence/severity — never
the small model making the final security call alone.

### A.8 Pre-scripted verdict cards — the LLM picks, doesn't write (operator, 2026-06-23)
The governing analogy: a human brain is fast because of automatic recognition, not conscious
reasoning. Planned tiers: **Tier 0** — exact/known match → a pre-written card, zero LLM tokens,
instant. **Tier 1** — close match → the LLM selects the best-fitting card (cheap). **Tier 2** —
genuinely novel → the LLM generates fresh (rare, backgrounded), then caches the result as a new
Tier-0 card. Cards authored offline by the 8b once, played back at zero runtime cost.

### A.9 The LLM is OPTIONAL — engines + library + app are the CORE (operator, 2026-06-23 — the de-risking decision)
**This section is the actual origin of the current real architecture (§2/§4 above).** Operator:
*"if the brain [LLM] doesn't work we might need to scrap the LLM and go a different route — maybe
the library and the app drive it, so it uses Clam etc."* Two cleanly separable layers were
identified: **CORE** (always-on, no model, runs on any box — engines detect, exact-match → library
card, app = terminal + cards + the ask — a complete AV with zero LLM) and **ENHANCEMENT** (LLM for
free-form conversation and genuinely novel-threat reasoning, gracefully degrading to canned
FAQ + abstain when absent). Decision: build the CORE first, unconditionally — which is exactly
what shipped (§2).

### A.10 Prompt-injection defense research (moot now — no LLM in the runtime path)
Indirect prompt injection (attacker-controlled scanned text carrying instructions) was identified
as the #1 risk for an LLM security tool. Architectural defenses researched: user-sovereign
(model output never auto-acts), strict structured output, no direct capabilities, spotlighting
(treat scanned text as data never instructions), dual-LLM/CaMeL separation. All moot with the
current no-LLM architecture — no untrusted text ever reaches a model to be injected.

### A.11 Storage-bounded library design (planned, for if RAG is ever revisited)
Split storage was planned: permanent/small (MITRE backbone + card bank + engines' own managed DBs
like ClamAV's `freshclam`-updated signatures) vs. rolling/ephemeral (today's new IOCs, capped +
TTL, refresh-and-replace with a last-good fallback if offline). Never implemented — moot without
a live threat feed consumer.

### A.12 Fine-tune verdict (research, 2026-06-23)
Couldn't train on the Celeron (no GPU) — would need cloud QLoRA (Unsloth, ~$1-5, ~500 curated
examples). Never started.

### A.13 Prior art & novelty framing (still conceptually relevant even without the LLM)
"McAfee if it had a brain" — the classic-AV part is the engines + always-updated library; the
differentiator was reasoning + explaining + asking instead of nagging, fully local/private, calm
not alarmist. What's still true post-LLM: consumer desktop (not a SOC tool), a character with a
voice, human-in-the-loop, fused into the DE's nervous system via Lelan — none of that required the
LLM specifically, which is exactly why dropping it lost nothing essential.

### A.14 Evidence sources (historical)
Character: `NCDESettingsManual.qml` ch.12, `AboutTab.qml`; avatar `compass7/avatars.js`. Schema/
endpoints: `kickass-guard.md §9.2-9.4`. Prompt shape: `compass7/kickass-guard/KickassGuard.cpp:157-209`
(kickass-guard.md/KickassGuard.cpp are themselves superseded — see kickass-guard.md's own banner).
Voice/behavior/scope: operator, 2026-06-23. Atomic Arch AUR attack: external, June 2026.
