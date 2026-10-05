# KickassGuard + VesperBrain + Ollama — NCDE's AI Security Brain — **Manual**

> 🔴 **HISTORICAL — superseded 2026-07-01. Read this before anything else in this file.** Everything
> below describes the OLD C++ `kickass-guard`/`org.ncde.KickassGuard` D-Bus daemon + Ollama/Qwen3
> LLM design. It was never finished (`start()` never actually registers on D-Bus) and it is now
> **replaced, not resurrected** — operator: "we don't use llms for kickass or vesper anymore." The
> REAL, built, tested, non-LLM system is a completely different architecture:
> `usr/lib/ncde/vesper/brain_server.py` (plain Python HTTP on `127.0.0.1:8077`, no LLM, no
> ChromaDB/embeddings — exact/keyword search over the real MITRE ATT&CK JSON) +
> `vesper_engines.py` (real ClamAV/rkhunter/fail2ban/nftables/auditd subprocess orchestration) +
> `usr/share/ncde/vesper/*.qml` (the real UI). Wired 2026-07-01 as the single "Vesper" armed/
> disarmed toggle in `SecurityTab.qml` (`settings.kickassArmed` → `systemctl --user enable/disable
> --now vesper-brain.service`) — nftables/firewall is one of its five engines, not separate. Full
> detail: memory `project-ncde-vesper-real-architecture`, `SESSION_HANDOFF.md` session 44. Read
> this file only for historical context on what was tried before, never as the current spec.

**Audience:** a developer with **no access to the NCDE source.** Companion to `lelan.md` /
`anim-policy.md`. Reconstructed from the compiled binary `[dead-legacy-tree]/usr/local/bin/kickass-guard`
(the original **C++** source FILES are no longer in the tree, but are recoverable from this
unstripped/full-DWARF binary via Ghidra — as the ncde-wm source was, oracle at
`~/ncde-wm-rebuild/` [corrected 2026-07-17: the old `~/ncde-staging/` path this pointed to is
gone; that workspace was rebuilt at this new path]). Tags: **[E]** verified in the binary; **[STD]** a public/standard API
to talk to; **[INF]** operator-intent/inference.

---

## 1. What it is

**KickassGuard** is NCDE's security service: it orchestrates the standard Linux security stack **and**
runs a **local LLM brain** that turns raw detections into reasoned verdicts, learns the system over
time, and acts (kill/block). It exposes itself on D-Bus as **`org.ncde.KickassGuard`** and is
**lelan-compliant** — its events flow into the nervous system. **[E]**

- Binary: `usr/local/bin/kickass-guard` **[E]**
- D-Bus service: `usr/share/dbus-1/services/org.ncde.KickassGuard.service` **[E]**
- The custom model is a **Qwen** LLM served by **local Ollama** **[INF: model name; E: Ollama plumbing]**
- "Controls everything … and guards it" — it both **uses** the local LLM and **firewalls** it so only
  its own UID can reach it. **[E: "block other UIDs from reaching local Ollama"]**

---

## 2. Components (classes in the binary) **[E]**

| Class | Role |
|---|---|
| `KickassGuard` | Orchestrator. Collects engine events, builds a `ThreatContext`, asks the brain, applies a `ThreatVerdict`, `killProcess()`, emits via the adaptor. |
| `KickassAdaptor` | D-Bus adaptor → `org.ncde.KickassGuard` (armed state + threat signals out to lelan). |
| `ClamEngine` | ClamAV malware scanning → `(file, detail, severity:int)`. |
| `RkhunterEngine` | rkhunter rootkit detection. |
| `Fail2banEngine` | fail2ban brute-force/ban events → `(app, detail)`. |
| `NftEngine` | nftables firewall — enforces blocks, **incl. guarding local Ollama**. |
| `DnsEngine` | DNS filtering / blocked-domain events → `(domain, detail)`. |
| `AuditEngine` | auditd events → `(subject, object, action)` `(QString,QString,QString)`. |
| `BaselineEngine` | system baseline = "normal" snapshot → anomaly detection (the learning floor). |
| `OllamaClient` | HTTP client to local Ollama (`generate`/`embed`/`listModels`/`checkAvailability`). |
| `VesperBrain` | The LLM brain — `initModel()`, `onAnalysisReady(id, QJsonObject)`; consumes Ollama output → verdict. |
| `ChromaClient` | ChromaDB vector store client — `queryMitre(embedding, k)` → MITRE ATT&CK technique matches. |
| types | `ThreatContext`, `ThreatVerdict`, `TechniqueMatch`. |

---

## 3. The pipeline (how a threat is handled) **[E for parts, INF for the wiring order]**

```
  ┌── ClamEngine ─┐
  ├── RkhunterEngine
  ├── Fail2banEngine     each emits (subject, detail, severity)
  ├── DnsEngine          ───────────────────────────────────►  KickassGuard
  ├── AuditEngine                                                  │  builds
  ├── NftEngine                                                    ▼
  └── BaselineEngine (anomaly vs learned normal)            ThreatContext
                                                                   │
                         ┌─────────────────────────────────────────┤
                         ▼                                          ▼
                 OllamaClient.embed(context)              OllamaClient.generate(prompt, model, system)
                         │  embeddings (QList<float>)               │  analysis (QJsonObject)
                         ▼                                          ▼
            ChromaClient.queryMitre(embedding, k)          VesperBrain.onAnalysisReady(id, json)
                         │  matchesReady(id, [TechniqueMatch])      │
                         └──────────────► VesperBrain ◄─────────────┘
                                              │  produces
                                              ▼
                                        ThreatVerdict
                                              │
                                KickassGuard acts: killProcess(), NftEngine block, …
                                              │
                                   KickassAdaptor → org.ncde.KickassGuard
                                              │
                                   lelan.subscribeToKickassGuard()
                                              ▼
                          desktop signals: kickassThreatBlocked / kickassThreatBehavioral / kickassStatusChanged
```

**Learning [E/INF]:** embeddings of threat context are queried against a **ChromaDB** collection of
**MITRE ATT&CK** techniques (`queryMitre` → `TechniqueMatch`), and `BaselineEngine` tracks the
system's normal state — together that's "it learns the system." **[E: queryMitre/Baseline; INF: framing]**

---

## 4. API surface (evidence) **[E]**

### OllamaClient (talks to local Ollama; HTTP/JSON over QNetwork)
```
void checkAvailability()                                  // is Ollama up?
void generate(const QString &prompt,
              const QString &model,
              const QString &system)                      // /api/generate
void embed(const QString &text)                           // /api/embeddings
void listModels()                                         // /api/tags
// signals:
void ()                                                   // e.g. availability/ready
void (bool)                                               // available(bool)
void (const QList<QString>&)                              // models list
void (quint64 id, const QJsonObject&)                     // generate result
void (quint64 id, const QList<float>&)                    // embedding result
```
Endpoint **[STD]:** Ollama defaults to `http://127.0.0.1:11434` (`/api/generate`, `/api/embeddings`,
`/api/tags`). Model name is **passed in** to `generate()` → the Qwen model is configurable, not
hardcoded. **[E: signature; INF: Qwen]**

### VesperBrain (the brain) **[E]**
```
void initModel()                                          // loads/selects the model (gets model list)
void onAnalysisReady(quint64 id, const QJsonObject&)      // LLM analysis → verdict
// connected to OllamaClient generate(id,QJsonObject) and embed(id,QList<float>)
```

### ChromaClient (vector memory / MITRE matching) **[E]**
```
static kBaseUrl        // Chroma server base URL    (e.g. http://127.0.0.1:8000)  [STD default]
static kCollection     // collection name
bool available()
void checkAvailability()
void queryMitre(const QList<float> &embedding, int k)     // nearest-k technique lookup
// signals:
void matchesReady(quint64 id, const QList<TechniqueMatch>&)
void availabilityChanged(bool)
```

### KickassGuard (orchestrator) **[E]**
```
void killProcess(const QString &pidOrName)
// constructor wires engine signals; emits (via KickassAdaptor):
void (bool armed, int level)
void (QString, QString, QString)     // threat behavioral (subject, detail, kind)
void (QString, QString, int)         // threat blocked (app, detail, severity)
void (QString, QString)              // generic event
void (QString)                       // status/notice
```

### Engines → KickassGuard signal shapes **[E]**
- `AuditEngine (QString,QString,QString)` · `ClamEngine (QString,QString,int)`
- `DnsEngine (QString,QString)` · `Fail2banEngine (QString,QString)` · `NftEngine (QString,QString)`

---

## 5. Guarding the LLM **[E]**

`NftEngine` installs an **nftables** rule so that **only KickassGuard's UID** can reach the local
Ollama socket (the binary literally describes "block other UIDs from reaching local Ollama"). This
prevents any other local process (or a compromised app) from prompting/poisoning the system LLM.
**[E]**

**Rebuild guidance [STD]:** with nftables, match the destination `127.0.0.1:11434` and `skuid`
(socket owner UID), `accept` for the guard's UID, `drop`/`reject` otherwise; load it in the guard's
own namespace/table. Verify with `nft list ruleset`.

---

## 6. lelan compliance **[E]**

KickassGuard does **not** make widgets talk to it directly — it publishes on `org.ncde.KickassGuard`
and **`lelan` subscribes** (`LElan::subscribeToKickassGuard()`), fanning out:
`kickassChanged`, `kickassStatusChanged`, `kickassSiteBlocked`, `kickassThreatBlocked`,
`kickassThreatBehavioral` (see `lelan.md` §4/§6). The security UI/widgets read `lelan`. **[E]**

---

## 7. Rebuild checklist (from scratch) **[INF, grounded in §2–§6]**

1. **Engines:** wrap each tool (`clamscan`/`clamd`, `rkhunter`, `fail2ban-client`, `nft`, a DNS
   sinkhole/resolver, `auditd`/`ausearch`) in a `QObject` engine emitting `(subject, detail,
   severity)`. `BaselineEngine` snapshots normal state (pkgs, ports, suid, services) and flags drift.
2. **OllamaClient:** Qt `QNetworkAccessManager` POSTing to `127.0.0.1:11434` `/api/generate` &
   `/api/embeddings`; parse streamed JSON; emit `(id, QJsonObject)` / `(id, QList<float>)`.
3. **ChromaClient:** HTTP to a local Chroma server; seed a collection with MITRE ATT&CK techniques
   (embedded once); `queryMitre(embedding,k)` → nearest techniques as `TechniqueMatch`.
4. **VesperBrain:** on a `ThreatContext`, `embed()` it → `queryMitre()` for context, then `generate()`
   a prompt (context + matched techniques + system prompt) → parse the JSON verdict in
   `onAnalysisReady` → `ThreatVerdict { severity, action, rationale }`.
5. **KickassGuard:** collect engine events → build `ThreatContext` → ask `VesperBrain` → act
   (`killProcess`, `NftEngine` block) → publish on `org.ncde.KickassGuard`.
6. **Guard the LLM:** `NftEngine` rule restricting `:11434` to the guard UID.
7. **lelan:** add `subscribeToKickassGuard()` to the nervous system (already specified in `lelan.md`).
8. **Deps:** Qt6 `Core Network DBus`; a running Ollama (+ the Qwen model) and a Chroma server;
   `clamav`, `rkhunter`, `fail2ban`, `nftables`, `audit`.

---

## 8. How this was reconstructed / verify **[E]**
- Mined from `[dead-legacy-tree]/usr/local/bin/kickass-guard` (`strings` → class/method symbols + the Ollama
  text). Raw evidence also in `lelan-references.txt` (KickassGuard/Ollama appear via the LElan hooks).
- Validate the dbus surface live: `busctl introspect org.ncde.KickassGuard /org/ncde/KickassGuard`
  (when the service is running).
- Note: `magpie-talker` is **not** part of this AI path (it's a text/locale app — no Ollama/LLM
  strings). The LLM lives in `kickass-guard`. **[E]**

---

## 9. DEEP DIVE — full reverse-engineering (the binary is UNSTRIPPED, full DWARF) **[E]**

The binary carries full DWARF debug info (built from `apps/kickass-guard/src/*.cpp`, 15 TUs — the source
FILES did not survive as files, but the full DWARF makes them recoverable via Ghidra, as the ncde-wm source
was). Endpoints/constants/schemas recovered verbatim.

### 9.1 Two classes the earlier spec missed (central — can't rebuild without them)
- **`ContextBuilder`** — turns raw engine events into a `ThreatContext`:
  `fromAuditEvent(s,s,s)`, `fromClamEvent(s,s)`, `computeSha256()`, `computeEntropy()` (Shannon),
  `readElfImports()` (`.so` deps), `queryBaseline(ThreatContext&)`, `setBaselineEngine()`, `setDatabase(QSqlDatabase)`.
- **`ThreatEngine`** — IOC SQLite DB + threat-intel feed downloader; sink for baseline/anomaly writes.
  `addIoc(type,value,source,confidence,desc)`, `lookupIoc()`, `setupDatabase()`, `iocDbPath()`,
  `writeAnomaly()`, `writeBaseline()`, signal `iocDatabaseUpdated()`. `VesperBrain` + `BaselineEngine`
  both `setThreatEngine()` into it.

### 9.2 Endpoints / models / constants (verbatim)
- **Ollama:** `http://127.0.0.1:11434`; model **`vesper:latest`** — **SUPERSEDED (operator, 2026-06-30
  night): Vesper no longer uses LLMs.** This endpoint/model describes the abandoned design; do not build
  toward it. Actual current direction not yet captured — ask the operator, don't infer from
  `brain_nollm.py`/`cards.json`.
- **ChromaDB:** `http://127.0.0.1:8000`; collection **`mitre-attack`** — also tied to the abandoned
  LLM/embedding approach above; re-evaluate once the non-LLM design is captured.
- **Data root:** `/var/lib/ncde-kickass` (group-writable) — IOC DB, baseline DB, nft + dns rule files.
  ✅ CONFIRMED present in the LaPivot tree (tmpfiles.d entry verified 2026-06-30 night) — this line's
  status is independent of the Vesper/LLM correction above.
- HTTP User-Agent `ncde-kickass-guard/1.0`. Registers on the **session bus**. **Corrected (2026-06-30
  night): the activation unit `kickass-guard.service` IS shipped** — confirmed present at
  `~/ncde-staging/LaPivot/usr/lib/systemd/system/kickass-guard.service` (that tree path no longer
  exists as of 2026-07-17 — this was a real, dated finding, re-verify against
  `/usr/lib/systemd/system/kickass-guard.service` on the live system if needed), a real (non-stub) unit with
  root-service + session-bus-wait logic, `After=`/`Wants=ollama.service chroma.service`. Not currently
  *running* on this dev host (`systemctl status` → "could not be found," expected — not installed here),
  but "NOT shipped — must be authored" is false; it exists in the tree that ships.

### 9.3 D-Bus surface `org.ncde.KickassGuard` (embedded introspection XML)
Methods: `Decide(s,s)`, `GetLog(u)->s`, `GetQuarantine()->s`, `RestoreFile(s)`, `DeleteFile(s)`,
`DeleteAll()`, `Dismiss(s)`, `CheckUrl(s)->s`. Signals: `ThreatDetected(s)`, `ThreatBlocked(s,s,i)`,
`ThreatBehavioral(s,s,s)`, `ThreatAnalysis(s)`, `SiteBlocked(s,s)`, `NetworkAlert(s,s)`,
`StatusChanged(b,i)`, `ToastNotification(s)`. (No properties. `killProcess`/`quarantineFile` internal.)

### 9.4 Data structures (DWARF `ptype`)
- **`ThreatVerdict`** (LLM output): `threat_class`(s), `confidence`(double), `mitre_techniques`(s),
  `verdict`(s), `recommendation`(s), `explanation`(s).
- **`ThreatContext`**: source_engine, event_type, timestamp, file_path, file_size, sha256, entropy,
  elf_imports, process_name, process_args, audit_rules_fired, outbound_ips, outbound_domains,
  event_count, window_secs, baseline_expected_max, actual_files, baseline_deviation; `toJson()`,
  `toPromptText()` (the LLM prompt body — built at runtime, not a literal).
- **`TechniqueMatch`**: id, name, description, distance.
- Plus `ExecObservation`, `BaselineBinKey`/`BaselineBinData`, `*Engine::FeedSpec`,
  `ThreatEngine::DownloadSpec`, `VesperBrain::PendingAnalysis{ctx, mitreMatches, iocHit}`.

### 9.5 The pipeline (precise)
engine → `ContextBuilder` (enrich → `ThreatContext`) → `VesperBrain::analyse` →
`OllamaClient::embed` → `ChromaClient::queryMitre` (MITRE RAG) → `OllamaClient::generate(vesper)` →
`VesperBrain::parseVerdict` → `ThreatVerdict` → `verdictReady` → `ThreatAnalysis`/`ThreatBlocked` dbus.

### 9.6 Per-engine triggers
- `ClamEngine` tails `clamav-clamonacc/daemon` journal for "FOUND".
- `RkhunterEngine` periodic `runScan()`.
- `Fail2banEngine` tails `fail2ban.service` journal for bans.
- `AuditEngine` writes audit rules + tails `/var/log/audit/audit.log`.
- `BaselineEngine` fd-count baselining per exe × hour × day-of-week bins; anomaly → ThreatEngine.
- `NftEngine` installs the ruleset + downloads C2 IP feeds. `DnsEngine` deploys an unbound sinkhole.

### 9.7 nftables ruleset (`table inet kickass`, regenerated on start)
```
table inet kickass {
  set c2_blocklist { type ipv4_addr; flags interval; }
  chain input  { type filter hook input  priority 0; policy accept;
                 # portscan meter (>10/s new SYN) -> log "KICKASS_PORTSCAN: " drop }
  chain output { type filter hook output priority 0; policy accept;
                 ip daddr 127.0.0.1 tcp dport 11434 meta skuid != <uid> log prefix "KICKASS_OLLAMA_GUARD: " drop
                 ip daddr @c2_blocklist log prefix "KICKASS_C2_BLOCK: " drop }
}
```
(The Ollama UID guard = "block other UIDs from reaching local Ollama".) Dynamic: flush/add the
`c2_blocklist` set.

### 9.8 auditd rules (`writeAuditRules`)
execve (b64/b32, key `exec_track`); rename/renameat/renameat2 (`file_rename`, ransomware mass-rename);
connect (`outbound_new`, C2); bpf a0=5 (`ebpf_load`, eBPF rootkit); `-w /etc -p w` (`write_etc`
persistence); `-w /etc/shadow -p r` + `-w /root/.ssh -p r` (`sensitive_read` credential harvest).

### 9.9 Threat-intel / DNS feed URLs (FeedSpec)
- `https://raw.githubusercontent.com/hagezi/dns-blocklists/main/hosts/pro.txt`
- `https://raw.githubusercontent.com/tweedge/emerging-threats-pihole/main/emerging-threats.txt`
- `https://urlhaus.abuse.ch/downloads/hostfile/`

### 9.10 Not recoverable as literals (build at runtime)
Exact DB/blocklist/nft filenames under `/var/lib/ncde-kickass`, the LLM system-prompt body +
`toPromptText()` format, and the SQL DDL/DML. These the designer must (re)design to the schemas above.
