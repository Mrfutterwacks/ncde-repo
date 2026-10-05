# Build the Missing — designer work queue vs. package installs

The completeness audit (`ncde-completeness-audit.md`) found gaps. They split two ways. **Don't ask the
designer to "build" upstream packages** — those are installs. The designer builds the **NCDE-authored
glue + the AI model**. Specs below are grounded in the binary evidence (see `kickass-guard.md`).

---

## A. NOT designer work — just INSTALL these (operator, `pacman -S --root`)
Upstream packages; nothing to build:
`geoclue`, `power-profiles-daemon`, `packagekit`, `nss-mdns`, `clamav`, `rkhunter`, `fail2ban`,
`unbound`, `ollama`, `chromadb`. → verify at file level after install.

---

## B. DESIGNER BUILDS these (missing NCDE-authored artifacts)

### B1. `vesper:latest` — the fine-tuned Qwen security model ⭐ (the brain; biggest build)
The whole AI verdict path is dead without it. It's an **Ollama model** the guard calls via
`OllamaClient.generate(system, prompt, "vesper:latest")`.
- **Base:** a Qwen instruct model, fine-tuned for security triage.
- **Input:** `ThreatContext.toPromptText()` (fields: source_engine, event_type, file_path, sha256,
  entropy, elf_imports, process_name/args, audit_rules_fired, outbound_ips/domains, baseline_deviation,
  actual_files vs baseline_expected_max, …) + retrieved MITRE techniques.
- **Required output: STRICT JSON** matching `ThreatVerdict`:
  ```json
  { "threat_class":"", "confidence":0.0, "mitre_techniques":"",
    "verdict":"", "recommendation":"", "explanation":"" }
  ```
- **Deliverable:** an Ollama `Modelfile` (FROM qwen… + SYSTEM prompt + params) tagged `vesper:latest`,
  plus the training/eval set. Embeddings model is separate: **`nomic-embed-text`** (just `ollama pull`).
- Fallback: the guard logs `vesper:latest not found, using <fallback>` — so ship a graceful default.

### B2. Seed the ChromaDB `mitre-attack` collection
`ChromaClient` queries `http://127.0.0.1:8000`, collection **`mitre-attack`**, with
`query_embeddings` → `{documents, distances, metadatas, ids}` → `TechniqueMatch{id,name,description,distance}`.
- **Build:** a seeding script that pulls the MITRE ATT&CK technique corpus, embeds each with
  `nomic-embed-text`, and upserts into the `mitre-attack` collection (id = technique id e.g. `T1059`,
  metadata = name/tactic). Run at build or first boot.

### B3. `kickass-guard.service` (the missing unit — without it the guard NEVER starts)
The dbus activation file ships (`SystemdService=kickass-guard.service`) but the unit doesn't exist.
- **Build:** a systemd **system** unit running `/usr/local/bin/kickass-guard` **as root** (privilege
  source for nft/auditctl/kill/reading shadow), `After=network-online.target ollama.service`,
  wants ollama + chromadb up. Note: the daemon registers on the **session** bus but needs root — the
  unit reconciles this (root service + session-bus access, or run in the user session with the right
  caps). **[DESIGN DECISION: session-bus-as-root wiring]**

### B4. Provisioning: `/var/lib/ncde-kickass` + first-boot AI setup
- Pre-create `/var/lib/ncde-kickass` group-writable (tmpfiles.d or the unit) — holds IOC SQLite,
  baseline DB, nft/dns rule files.
- A **first-boot setup unit/script**: ensure `ollama.service` + `chromadb` running → `ollama pull
  vesper:latest` + `nomic-embed-text` → seed `mitre-attack` (B2). (Decides the bundle-vs-pull question
  for the multi-GB models.)
- Enable the security daemons in `chrooted_post_install.sh`: clamav (`clamav-clonacc`), auditd,
  fail2ban, unbound, ollama, chromadb, kickass-guard.

### B5. The two app dbus service files (trivial)
`com.ncde.MagpieTalker.service` + `com.ncde.HummingbirdCourier.service`
(`[D-BUS Service] Name=… / Exec=/usr/local/bin/<app>`) — only if D-Bus activation is wanted.

### B6. `lelan` / `Lelan` itself (already speced)
The nervous-system host (see `lelan.md` + `missing.md`) — the C++ hub injected as `lelan`, plus the
`ncde` master backend and the 13 app/host backends. This is the largest QML-adjacent rebuild.

### B7. (verify) Screensaver scene assets
`usr/share/ncde/screensaver/` is empty. Confirm whether the "Saisons" screensaver scenes/assets are
meant to ship there (low-confidence gap) — if so, the designer supplies them.

---

## C. The nftables ruleset & audit rules (reference — guard writes these itself)
Not missing (the guard generates them), but the designer needs them to test/seed. Verbatim from the
binary — see `kickass-guard.md` for `table inet kickass` (C2 set, portscan meter, **Ollama UID guard
on tcp dport 11434**) and the auditd rules (execve/rename/connect/bpf/`/etc` writes/`/etc/shadow` reads).

---

## Priority order
1. **B3 + B4** (unit + provisioning) — without these the guard can't even start.
2. **A installs** (geoclue/power-profiles/packagekit first → restores weather/location/power/updates).
3. **B1 + B2** (vesper model + mitre seed) — lights up the AI brain.
4. **B6** (lelan rebuild) — the nervous system (parallel, large).
5. B5, B7 (polish).

---

## D. Per-package post-install wiring (after the operator installs Group A)
Installing the package is not enough — each needs wiring (do this in `chrooted_post_install.sh`, and
some in the live tree). **[STD]**

| Package | Wiring needed |
|---|---|
| **geoclue** | dbus-activated (no enable). Ensure the NCDE apps are allowed in `/etc/geoclue/geoclue.conf` (`[<app-desktop-id>] allowed=true`), or they get no location. |
| **power-profiles-daemon** | `systemctl enable power-profiles-daemon.service`. |
| **packagekit** | dbus-activated (no enable); confirm `pkcon` works against pacman backend. |
| **nss-mdns** | edit `/etc/nsswitch.conf` `hosts:` line → add `mdns_minimal [NOTFOUND=return]` before `resolve`/`dns`; **enable `avahi-daemon.service`** (Magpie needs it). |
| **clamav** | `freshclam` to fetch the virus DB (or ship it); `systemctl enable clamav-freshclam.timer clamav-clamonacc.service` (on-access scan ClamEngine tails). The `clamav` user comes from the package scriptlet → install via `pacman --root`, not copy. |
| **rkhunter** | `rkhunter --propupd` to seed the baseline; add a timer for periodic scans. |
| **fail2ban** | ship a `jail.local`; `systemctl enable fail2ban.service`. |
| **unbound** | configure as the local resolver for DnsEngine's sinkhole; `systemctl enable unbound.service`; allow `unbound-control`. |
| **ollama** | `systemctl enable ollama.service` (creates the `ollama` user/socket on 11434); then provision models (B1/B4). |
| **chromadb** | run as a service on `:8000` (author a unit if the package has none); seed `mitre-attack` (B2). |
| **kickass-guard** | author + enable `kickass-guard.service` (B3) `After=ollama.service`; pre-create `/var/lib/ncde-kickass` (B4). |

> Re-run `ncde-completeness-audit.md` after wiring; every ❌ must become ✅ before the build gate.
