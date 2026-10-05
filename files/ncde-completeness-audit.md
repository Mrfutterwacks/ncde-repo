# NCDE Completeness Audit — what's in the tree vs what's MISSING

File-level verification of `~/ncde-x11` against the full component map (the 5-agent sweep). **This is
the "ship everything or it's broken" gate.** Method: file existence in the tree (NOT the pacman DB —
that query is unreliable here). Date: this session.

## 2026-09-26 — live UI source-of-truth reconciliation

The counts and dependency findings below are a historical audit of `~/ncde-x11`; they are not a
current comparison of the installed UI against the USB project. A fresh hash comparison against
`/usr/share/ncde` found 308 active installed files. All 308 are now present byte-for-byte in each
of the three USB `full-patch-20260711/src/usr/share/ncde` mirrors. Two additional source-tree files
are documentation/test artifacts and are deliberately excluded from installation.

The master installer now embeds the complete active source and has step `0a/13` to install only
missing or changed UI files (byte-identical live files are skipped). Rollback copies, reverted or
retired files, Python caches, READMEs, and the accessibility test are not deployed as product files.
This reconciles the UI payload only; runtime dependencies, compiled backends, and service behavior
still require their own live verification.

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

1. **Install the missing packages into the tree** (Group 1 + 2 tools), e.g.
   `pacman -S --root /home/stephen/ncde-x11 …` :
   `geoclue power-profiles-daemon packagekit nss-mdns clamav rkhunter fail2ban unbound`
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
