# Vesper's Knowledge Base — "All Things Cybersecurity" — **Curriculum & Corpus Spec**

**What this is:** the body of knowledge Vesper must hold to be NCDE's living security brain — and the
concrete plan for how it gets *into* him. Companion to `vesper.md` (the model/character) and
`kickass-guard.md` (the daemon/engines). Tags: **[E]** in a surviving artifact · **[STD]** public
source/standard · **[INF]** operator/design intent.

> **How knowledge reaches Vesper — four layers (see `vesper.md §7`):**
> 1. **Base model** — Qwen3:8b general reasoning.
> 2. **RAG library (ChromaDB)** — this corpus, embedded with `nomic-embed-text`, queried per detection.
> 3. **On-device learning** — `BaselineEngine` learns THIS machine's normal; (B) per-user fine-tune.
> 4. **Live web look-up** — for brand-new threats not yet in the library (privacy-scoped).
>
> **Scope:** breadth = *all things cybersecurity* (so he can reason and converse about anything a user
> asks); depth/priority = **Linux & Arch** (his beat — that is where detections actually come from).

---

## 1. Frameworks & taxonomies (his mental map) **[STD]**
- **MITRE ATT&CK** — tactics → techniques → sub-techniques (the spine; collection `mitre-attack` already
  in the design). Enterprise + Linux matrix + Cloud.
- **MITRE D3FEND** — the *defensive* counter-map (what to do about each technique).
- **MITRE CAPEC** — attack patterns. **CWE** — weakness types. **CVE/NVD + CVSS** — known vulns + scoring.
- **Cyber Kill Chain** (Lockheed) and the **Diamond Model** — for narrating an intrusion.
- **STIX/TAXII** — the data formats threat intel ships in (how to ingest feeds).
- **NIST CSF**, **CIS Controls + CIS Benchmarks (Linux)**, **zero-trust / defense-in-depth / least
  privilege** — the doctrine behind his recommendations.

## 2. Malware knowledge (what rides into town) **[STD/INF]**
- **Classes:** ransomware, rootkits (userland LD_PRELOAD, kernel LKM, **eBPF**), trojans, RATs,
  infostealers (browser creds, SSH keys, wallets — cf. Atomic Arch), cryptominers, worms, botnets,
  droppers/loaders, backdoors, wipers, **fileless / living-off-the-land**.
- **Linux malware families & toolkits** (corpus to study): historical + current ELF malware, common
  cryptominer kits, common botnet agents, the eBPF-rootkit class.
- **Techniques:** packing/obfuscation, entropy (cf. `ContextBuilder::computeEntropy`), ELF import
  analysis (`readElfImports`), process injection, anti-analysis/sandbox-evasion.
- **GTFOBins** — trusted Linux binaries abused for privesc/exfil (essential for LOLBin detection).

## 3. Linux & Arch attack surface (his home ground) **[STD/INF]** ⭐ priority
- **Supply chain:** AUR/`PKGBUILD`/`.install` risks, the **AUR package-adoption attack** (Atomic Arch,
  June 2026 — 1,500+ pkgs, Rust infostealer + eBPF rootkit), pacman/keyring signing, repo trust.
  Cross-ecosystem: npm/PyPI typosquatting, dependency confusion, malicious post-install scripts.
- **Privilege escalation:** SUID/SGID, capabilities, sudo misconfig, **PwnKit (CVE-2021-4034)**,
  **Dirty Pipe (CVE-2022-0847)**, Dirty COW lineage, kernel LPEs, writable cron/systemd/`.service`.
- **Persistence:** systemd units & timers, cron, `~/.bashrc`/profile, `LD_PRELOAD`/`ld.so.preload`,
  udev rules, polkit/pkexec, autostart `.desktop`, kernel modules.
- **Core mechanisms to understand:** systemd, D-Bus, polkit, namespaces/cgroups, ptrace, `/proc`,
  `/etc/passwd`/`shadow`, SSH keys, the keyring.

## 4. Indicators & detection content (what the engines feed him) **[E engines; STD content]**
- **IOC types:** file hashes (SHA-256), IPs, domains, URLs, mutexes, paths, registry-equivalents.
- **Rule formats:** **YARA** (file/memory signatures), **Sigma** (log detections), nftables rules,
  auditd rules (cf. `AuditEngine::writeAuditRules` — execve/rename/connect/bpf/`/etc`/shadow).
- **Behavioral baselining:** fd-count per exe × hour × day (cf. `BaselineEngine`), anomaly deviation.

## 5. Network security **[E NftEngine/DnsEngine; STD]**
- Firewalling with **nftables** (the `table inet kickass` ruleset, C2 blocklist, portscan meter, the
  Ollama-UID guard on `:11434`). DNS sinkholing via **unbound** (`DnsEngine`).
- C2 detection, beaconing, DGA domains, exfiltration patterns, Tor/proxy abuse, TLS/cert anomalies,
  lateral movement, port scanning.

## 6. Host hardening & IR **[STD]**
- Hardening: AppArmor/SELinux (MAC), seccomp, sandboxing (firejail/bubblewrap), secure boot, integrity
  (AIDE/baseline), least-privilege, patching/`pacman -Syu` hygiene.
- Incident response: triage → containment → eradication → recovery; **quarantine (never destroy,
  restorable)**; forensics basics (memory/disk/timeline). Tie to NCDE's recovery app ("Soundings").

## 7. Threat intelligence — the live feeds & sources to ingest **[E feeds; STD sources]**
Already in `ThreatEngine`/`DnsEngine` FeedSpec:
- `hagezi/dns-blocklists` · `tweedge/emerging-threats-pihole` · `urlhaus.abuse.ch` hostfile.
Add for the library (Linux-prioritized):
- **abuse.ch**: URLhaus, **MalwareBazaar** (samples/hashes), **ThreatFox** (IOCs), Feodo Tracker (C2).
- **MITRE ATT&CK STIX** bundle; **CWE/CAPEC**; **NVD CVE** JSON feed (filter Linux/Arch-relevant).
- **YARA** rule repos (e.g. community/large rulesets); **Sigma** rules; **GTFOBins** dataset.
- **MISP** galaxies/feeds (STIX/TAXII). Reputation look-ups: VirusTotal, abuse.ch (live layer, §9).
- **Arch-specific (his home turf — prioritize):** the **Arch Linux Security Tracker**
  (security.archlinux.org) + **ASA advisories**, **`arch-audit`** (CVE ↔ installed packages),
  arch-announce/AUR notices, **PKGBUILD/`.install` heuristics**, pacman keyring/signing, and the **Atomic
  Arch** AUR-adoption pattern.

## 8. User-facing security literacy (for CONVERSATION mode) **[INF]**
So he can talk to non-technical family/synagogue users: phishing & social engineering, scams, safe
browsing, password hygiene + MFA, updates, "is this email/link safe?", "what do I do now?" — explained
plainly, in his voice. He is also a teacher, not just a sentry.

---

## 9. Building the corpus → ChromaDB (the concrete work) **[INF/roadmap]**
> We pull from **authoritative, structured sources** (§7) — NOT by scraping the whole web. That is how you
> get "all Linux cybersecurity" in a usable, deduplicated, **bounded** form (raw web-scraping is noisy,
> unbounded, and a legal/quality mess). Footprint stays small — see **§9b**.

1. **Collect** the sources in §7 (download, Linux-filter where huge — e.g. NVD).
2. **Normalize** each into short documents: `{ id, text, metadata{source, type, platform, severity,
   mitre_ids, refs} }` — e.g. one doc per ATT&CK technique, per CWE, per malware family, per YARA rule.
3. **Embed** each with `nomic-embed-text`; **upsert** into ChromaDB. MITRE → collection `mitre-attack`
   (the binary's name); the rest → additional collections (e.g. `iocs`, `cve`, `malware`, `rules`) or a
   unified `threat-library`. **[DECISION: collection layout]**
4. **Refresh** via **consent-gated deltas**, not silent re-downloads (§9b: the startup "Update Vesper?"
   prompt). Respects privacy (no user data leaves).
5. **Live fallback** (§ `vesper.md §7.4`): on a low-confidence/empty match, query reputation APIs with
   **indicators only** (hashes/IPs/domains) — never user data.

## 9b. Don't bloat the machine — bounded local store + consent-gated live updates **[INF operator]**
Two pulls, split so the disk footprint stays small and nothing goes online without the user's say-so:

- **Local (durable, bounded):** the *foundational* knowledge that doesn't churn — MITRE ATT&CK, CWE/CAPEC,
  malware-family profiles, YARA/Sigma rules, GTFOBins, hardening doctrine. Stored as **embeddings + compact
  metadata in ChromaDB** (vectors, not raw documents) + the **IOC SQLite DB** (`ThreatEngine`). We
  **normalize → embed → discard the source** — no raw corpus dumps kept as files. This set is bounded.
- **Live, consent-gated (ephemeral, never hoarded):** the *fast-moving* stuff — newest IOCs, brand-new
  CVEs, emerging campaigns. **Vesper ASKS the user before going online** (sovereignty + privacy); the fetch
  is **background & headless — NO browser opens**, a silent API call that pulls only indicators
  (hashes/IPs/domains, never user data), uses them, and **prunes stale/expired entries** (feeds have TTLs)
  so the store never balloons.
- **Startup update prompt:** on machine start, if new threat data exists, the user sees a simple prompt —
  *"New threats are circulating. Update Vesper's knowledge? [Yes / Not now]"* — and only on **Yes** does he
  pull **deltas** (not full re-downloads), then prune. **No silent background scraping, ever.**

**Net:** foundational knowledge is small + local; the long tail lives online and is fetched on demand with
consent — the machine never fills with "tons of docs," and Vesper still stays current.

---

## 10. Faithfulness / use
- Engines & endpoints are **[E]** (`kickass-guard.md §9`); the corpus *content* is standard public
  security knowledge **[STD]**; the breadth/scope and "teacher too" framing are operator intent **[INF]**.
- This doc is **what Vesper knows**; `vesper.md` is **who Vesper is**; `kickass-guard.md` is **how the
  daemon runs**. Keep the three in sync.

## 11. Next steps
- [ ] Operator: confirm the domain list here is complete (add anything missing).
- [ ] Decide collection layout (§9.3): one `threat-library` vs several collections.
- [ ] Pick the concrete source set + licenses to ingest (some rule repos have licenses).
- [ ] Write the seed script (download → normalize → embed → upsert) = expanded **B2**.
- [ ] Decide what ships bundled vs refreshed on first boot/timer (mirrors the model bundle decision).
- [ ] (B) Use the same corpus to build the on-device fine-tune dataset.
