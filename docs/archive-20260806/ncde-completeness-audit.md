# NCDE Completeness Audit — what's in the tree vs what's MISSING

> **🔴 TREE UPDATE (2026-07-05, operator): `~/ncde-staging/LaPivot/` is THE production tree — the
> ONLY tree. The old frozen tree this audit was originally run against is DEAD. Every ✅/❌ below
> was verified against the dead tree and is UNVERIFIED against the production tree until re-checked
> there. Also note: the Group-2 Ollama/ChromaDB/vesper-LLM stack below is the ABANDONED architecture
> (superseded 2026-07-01 — Vesper is non-LLM now, see `vesper.md`); do not re-provision it.**
>
> **⚠️ CORRECTED 2026-07-17 — the tree above is gone.** `~/ncde-staging/` (and `LaPivot/` under it)
> no longer exists on this machine or the USB backup; the dev machine that hosted it is gone. There
> is no separate tree to install packages into or verify against anymore — the **live running
> system** (`/usr/local/bin/`, `/usr/share/ncde/`, the installed package DB) is the only copy. Any
> ✅/❌ below should be re-checked against the live system, not a tree path. See `CLAUDE.md` banner
> for the full corrected model.

> **PROGRESS 2026-06-23 (session 6) — flipping ❌→✅:**
> - **Group 1:** ✅ geoclue, power-profiles-daemon, packagekit (daemon `/usr/lib/packagekitd` + dbus
>   activation; CLI is `pkgcli`), nss-mdns — all present. (Wiring: ppd/avahi enabled; nsswitch mdns pending.)
> - **Group 2:** ✅ clamav, rkhunter, fail2ban, unbound, ollama present. ✅ **`kickass-guard.service`**
>   authored + enabled. ✅ **`/var/lib/ncde-kickass`** tmpfiles. ✅ **chromadb 1.5.9** installed via
>   pip-venv `/opt/ncde-chroma` (NOT pacman). Still ❌: **`vesper:latest`** (Qwen3 fine-tune) +
>   **`nomic-embed-text`**, **`mitre-attack`** seed. `chroma.service` authored (telemetry off) — cp+enable pending.
> - Net: the guard can now START (unit+dir+chroma unit ready); the AI brain still needs the model + seed.

File-level verification of `[dead-legacy-tree]` against the full component map (the 5-agent sweep). **This is
the "ship everything or it's broken" gate.** Method: file existence in the tree (NOT the pacman DB —
that query is unreliable here). Date: this session.

---

## ✅ PRESENT — all of NCDE's OWN code is valid and in the tree
- **20/20 NCDE binaries** (ncde-wm, ncde-portal(+helper, lock, lock-xss, screensaver-notify),
  ncde-sentinel, ncde-x11-session, ncde-command, ncde-terminal, orchidee, binnie, verve-text, abacus,
  magpie-talker, dovecote-relay, hummingbird-courier, kickass-guard, ncde-chromium, verdafetch).
- **166 QML** files + `NCDE.Controls` (23 widgets) + `SetTheme` singleton.
- `lelan`/`LElan`, AnimPolicy, NCDEEngine, all 15 host backends — **compiled into the binaries** (so
  present as long as the binaries are).
- Units/services that DO ship: `org.ncde.KickassGuard.service` (dbus activation file),
  `ncde-portal.service`, `ncde-sentinel.service` (user).
- **Source did NOT survive** — DWARF paths (`apps/kickass-guard/src/…`) are compile-time only; no
  `apps/` source dir in the tree. (kickass-guard is unstripped → great for re-spec, not source recovery.)

## ✅ PRESENT — third-party runtime libs/daemons
Qt6 (Core/DBus/Quick/Network), picom, NetworkManager, bluez (`bluetoothd`), udisks2 (`udisksd`),
avahi-daemon, libsecret, gnome-keyring, pipewire, pipewire-pulse, xdg-desktop-portal, nftables (`nft`),
auditd (`auditctl`).

---

## ❌ MISSING — these BREAK features (must be added before ship)

### Group 1 — desktop features go dark
| Missing | Breaks | Needed by |
|---|---|---|
| **geoclue** | weather widget, night-light schedule, Magpie GPS map, ncde-command location | `LElan::subscribeToGeoClue2`, DesktopWidget weather/moon, magpie, ncde-command |
| **power-profiles-daemon** | AnimPolicy power tier, `powerProfileChanged` | `LElan::subscribeToPowerProfiles` (net.hadess.PowerProfiles) |
| **packagekit** | `packageStateChanged` / update notifications via lelan | `LElan::subscribeToPackageKit` |
| **nss-mdns** | `.local` peer name resolution for Magpie | magpie-talker (Avahi) |

### Group 2 — KickassGuard: the AI brain + 3 engines are DEAD
| Missing | Breaks |
|---|---|
| **ollama** server + **`vesper:latest`** (fine-tuned Qwen) + **`nomic-embed-text`** embed model | VesperBrain analysis — the entire AI verdict path |
| **chromadb** server + **`mitre-attack`** collection (seeded) | MITRE ATT&CK RAG (`ChromaClient.queryMitre`) |
| **clamav** (`clamscan`/`clamd`) | ClamEngine (malware scanning) |
| **rkhunter** | RkhunterEngine (rootkit detection) |
| **fail2ban** | Fail2banEngine (brute-force/ban alerts) |
| **`kickass-guard.service`** systemd unit | the daemon can't D-Bus-activate or run as root → **the whole guard never starts** |
| **`/var/lib/ncde-kickass`** data dir (group-writable) | IOC SQLite DB, baseline DB, nft/dns rule files |
> Present for KickassGuard: auditd ✅, nftables ✅. unbound (DnsEngine) — verify separately.

### Group 3 — minor / optional
| Missing | Impact |
|---|---|
| `com.ncde.MagpieTalker.service`, `com.ncde.HummingbirdCourier.service` (dbus files) | only matters if D-Bus *activation* is wanted; both register their name at runtime (single-instance), so low priority |

---

## Remediation plan (operator-sudo — privileged)

1. **Install the missing packages** (Group 1 + 2 tools) — **corrected 2026-07-17: there is no
   `--root <tree>` to install into anymore**, this installs straight onto the live system, e.g.
   `pacman -S geoclue power-profiles-daemon packagekit nss-mdns clamav rkhunter fail2ban unbound`
   (verify each lands at the file level afterward).
2. **AI stack** (the big one — can't just sit in the squashfs as files):
   - Install `ollama` + `chromadb` (or run them as bundled services).
   - Provision models: `ollama pull` the `vesper:latest` (custom Qwen) + `nomic-embed-text`. These are
     multi-GB → decide **bundle in squashfs vs. first-boot pull** (first-boot needs network + a setup
     unit). **[DECISION NEEDED]**
   - Seed the Chroma `mitre-attack` collection (a build/first-boot step).
3. **Add the missing units/dirs:** author `kickass-guard.service` (runs the daemon as root, the
   privilege source for nft/auditctl/kill); pre-create `/var/lib/ncde-kickass` (group-writable);
   enable the security services (clamav/auditd/etc.) in `chrooted_post_install.sh`.
4. **(Optional)** add the two `com.ncde.*` dbus service files if activation is desired.
5. **Re-run this audit** until every ❌ is ✅ — then the §11 build gate.

> Why this matters: ~18 prior builds shipped broken because a layer was missing. The desktop shell +
> apps will run without Group 1/2, but weather/location/updates/power-tiering and the **entire
> security brain** will be silently dead. "No file left out" = these get added first.
