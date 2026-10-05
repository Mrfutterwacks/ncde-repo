# Vesper — Wiring Layer (UI ↔ guard ↔ model) — **Spec + skeleton**

**What:** how the delivered QML surface connects to the live system. **Corrected 2026-07-17:**
`~/ncde-staging/vesper/ui/` no longer exists — the dev machine hosting it is gone. The current copy of
this QML lives at `~/ncde-wm-rebuild/lapivot/live-qml/vesper/` (AlertCard/ConsentBar/QuarantinePane/
VesperButton/VesperFace/VesperTokens/VesperBackend/Main/Terminal.qml), with the deploy-staged bundle at
`~/my-project/files/vesper-patch-20260711/`. The
designer's `VesperBackend.qml` is an empty contract; this layer replaces it with a real backend.
Companion to `vesper-interface-brief.md §9` (the seam), `kickass-guard.md §9.3` (the D-Bus surface).
Tags: **[E]** evidence · **[INF]** design.

---

## 1. Architecture — a standalone host, NO ncde-wm recompile
`ncde-vesper` = a small **Qt6 C++ QML host** (new source — like the recovery-app backend; NOT the recovered/rebuilt WM):
- Loads `Main.qml` and injects a **C++ `VesperBridge`** as the context property `backend` (replacing the
  `VesperBackend {}` stub). The QML never changes. **[INF — recovery-app pattern]**
- Runs **as the user (uid 1000) on the session bus**; talks to the guard over D-Bus
  `org.ncde.KickassGuard`. **No dependency on ncde-wm** (the recovered/rebuilt ncde-wm is irrelevant to this path). **[INF]**
- **Launch — tied to the Settings → Security toggle.** The existing `kickassArmed` toggle (SecurityTab.qml)
  is the master switch: **off = nothing runs; on = the guard is armed and the host listens.** When armed:
  (a) the guard signals a threat → host **pops up** the alert; (b) the user opens Vesper to chat.
  Armed-but-quiet = **no window**, just the Security-tab status. (See `vesper.md §6`.)
- **Naming:** every user-facing string says **"Vesper"** — the monarch / Queen's-Guard / sheriff language
  is internal analogy only (`vesper.md §1b`), NEVER shown in the UI.
- **Scope:** Vesper is the **full suite** — firewall (`NftEngine`/`DnsEngine`) + AV (Clam/Rkhunter) +
  the AI brain — surfaced as one presence, not a chatbot.

## 2. ⚠️ CRITICAL constraint — the UI host must NEVER touch Ollama directly
`NftEngine` firewalls `127.0.0.1:11434` so **only the guard's UID** reaches Ollama (`kickass-guard.md §5/§9.7`).
The Vesper UI host runs as the *user*, so it is **blocked from Ollama by design — and that's correct.**
**Therefore ALL model traffic (verdicts, conversation, analyse) goes THROUGH the guard, never around it.**
The host speaks only D-Bus to the guard; the guard owns every Ollama call. This preserves the "only the
guard reaches the brain" guarantee. **[E firewall; INF routing]**

## 3. Backend → UI (host drives these properties; UI renders)
| UI property | Source |
|---|---|
| `armed`, `threatCount`, `lastUpdate` | guard `StatusChanged(b,i)` signal + initial read; `lastUpdate` formatted by host |
| `userName`, `orgName` | injected by host (from the session/system + org config) |
| `finding {id,threat_class,confidence,verdict,recommendation,explanation,mitre[]}` | parsed from guard `ThreatDetected(s)` / `ThreatBlocked(s,s,i)` / `ThreatBehavioral(s,s,s)` (JSON payload) |
| `analysisText` (append) | guard streaming tokens during analyse — see §5 |
| `chatReply` (append) | guard streaming tokens during ask — see §5 |
| `streaming` | true while tokens arrive |
| `quarantine[]` | guard `GetQuarantine()->s` (JSON) |
| `askOnlineConsent`, `askKnowledgeUpdate` | guard signals (consent moments) |

## 4. UI → backend (host turns hooks into D-Bus calls)
| UI hook | Guard call |
|---|---|
| `block(id)` | `Decide(id, "block")` (quarantine) |
| `allow(id)` | `Decide(id, "allow")` |
| `analyse(id)` | guard analyse (§5) → tokens into `analysisText` |
| `ask(text)` | guard conversation (§5) → tokens into `chatReply` |
| `reviewQuarantine()` | `GetQuarantine()` → fill `quarantine[]` |
| `restore(id)` | `RestoreFile(id)` |
| `remove(id)` | `DeleteFile(id)` |
| `dismiss()` | `Dismiss(id)` |
| `updateKnowledge(yes)` / `allowOnline(yes)` | consent replies to the guard |

## 5. ⚠️ Gap — conversation + streaming need NEW guard D-Bus methods
The recovered guard surface (`§9.3`) has **no chat method and no token streaming** — only `Decide`,
`GetLog`, `GetQuarantine`, `RestoreFile`, `DeleteFile`, `DeleteAll`, `Dismiss`, `CheckUrl`, and the
`ThreatAnalysis(s)` signal (a whole-text analysis result, not streamed).

So **verdicts + actions + quarantine wire up against the EXISTING binary today.** But Vesper's two-way
conversation (`ask`) and live streaming `analyse` require the guard to expose, in the **compass7 rebuild**:
- `Ask(s text) ` → runs Ollama (`vesper:latest`) and streams back
- streaming signals `ChatToken(s)` / `AnalysisToken(s)` (+ `ChatDone`/`AnalysisDone`)
- (non-streaming fallback: `ThreatAnalysis(s)` already exists → fill `analysisText` in one shot)

**Decision:** keep Ollama behind the guard (§2) → add these methods to the guard rebuild. Until then, the
host wires status/findings/actions/quarantine fully, and chat/analyse render via the one-shot
`ThreatAnalysis` path. **[E gap; INF the fix]**

## 6. Build / deploy
- Deps: **Qt6 Quick · Qml · DBus** + **cmake** (same toolchain as the recovery app — operator owes
  `pacman -S cmake`). Skeleton: was staged at `~/ncde-staging/vesper/host/` (`VesperBridge.{h,cpp}`,
  `main.cpp`, `CMakeLists.txt`) — **DRAFT, not yet compiled.** **Corrected 2026-07-17: that path and
  its draft skeleton no longer exist anywhere (dev machine gone, checked this machine + USB) — it was
  never compiled or deployed, so nothing was lost from the running system, but the draft itself would
  need to be written again from this spec, not recovered.**
- Ships: `ncde-vesper` → `usr/local/bin/`; QML → `usr/share/ncde/vesper/` (operator sudo to install).
- Test gate: run host against a running guard + `vesper:latest`; verify status, a real finding renders,
  block/allow/quarantine round-trip, consent gates fire. Then the `analyse`/`ask` streaming once the guard
  methods (§5) land.

## 7. Status
- ✅ UI delivered + staged — current copy at `~/ncde-wm-rebuild/lapivot/live-qml/vesper/` (see §What
  above; the original `~/ncde-staging/vesper/ui/` path is gone).
- ✅ Wiring designed (this doc) + host skeleton drafted — **the draft skeleton itself no longer exists
  (see §6); would need to be rewritten from this spec.**
- ⬜ Compile + test (with the model build, after the prompt-injection research lands).
- ⬜ Guard rebuild adds `Ask` + streaming signals (§5) for full conversation/analyse.
