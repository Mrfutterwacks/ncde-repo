# PROJECT.md — NCDE Poseidon

## Goal

NCDE Poseidon — a custom OS/desktop (the `lelan`/Qt6/X11 tree) built independently, predating the
Archcraft install. Archcraft was adopted later only as scaffolding for the Calamares **installer**
(ISO packaging, live-boot mechanics) — the installer and the OS/desktop source are two separate
lineages. Never state or imply the OS/desktop itself was "built on" or "based on" Archcraft.

## Design lineage — WWCDED ("What Would CDE Do?")

**NCDE = CDE, reimagined as a modern, coherent product.** The whole system is modeled on what the
Common Desktop Environment would have become if it had survived and evolved — not on GNOME or KDE. When
a design choice is ambiguous, ask **"What Would CDE Do?"** and make the **integrated, first-party,
"it all just works as one thing"** move — never the GNOME-minimalist or KDE-infinite-framework move.

The lineage is concrete:
- **CDE ToolTalk → `lelan`** — one central message/event backbone the whole desktop speaks through (the
  nervous system). This is the single biggest architectural fork from GNOME/KDE (who scatter D-Bus
  per-app/per-service). Prior art that proves the pattern: KDE KSystemStats, Astal/AGS (see
  `lelan-research-findings.md §7`).
- **CDE Style Manager → `ncde`** — the centralized theme/appearance/sysadmin object.
- **The CDE `dt*` app suite → the NCDE apps** — dtmail→Hummingbird/NCDEMail, dtcm→NCDECalendar,
  dtpad→verve-text, dtfile→orchidee, dtterm→ncde-terminal, dtcalc→abacus, dthelp→NCDEHandbook.
- **CDE Front Panel + Workspace Manager → the Dock/panels + NCDEWorkspace** (with a Unity-style side
  dock + auto-hiding top/bottom panels + side widgets — chrome that recedes, info that's glanceable).
- **Motif bevels → gilt / filigree / glass** — the same crafted-depth tradition, modernized (NOT flat).

**macOS is only the polish/performance layer, not the blueprint** — Aqua-grade smoothness and the
"feels light" governor (Core Animation → Qt Animator; App Nap/Timer-Coalescing/QoS → Lelan+Zen; the
real Darwin mechanisms are libdispatch QoS + dispatch-source leeway, see `anim-policy.md §2b`). The
thesis: CDE and macOS are siblings (both Unix), so a surviving CDE would have drifted Mac-ward — NCDE
builds that child. This is *why* a heavy desktop can feel light and never lock up, for its audience
(family/synagogue/Linux-averse users who need one coherent thing that works).

## Strategy

- Use Archcraft's squashfs clone method + Calamares installer, themed as NCDE.
- **The live system IS the installed system** — build it right, then clone it.
- **Calamares handles partitioning, user creation, and GRUB** — do not reinvent these.
- **NCDE desktop replaces Openbox/BSPWM** — same session chain, different window manager.

## Branding

- Parchment / nautical theme.
- "Captain's Log" installer messages.
- No Arch visible anywhere (see CLAUDE.md rule 7).

## Key Directories

- `[dead-legacy-tree]/` — **the consolidated single source of truth**: a full rootfs holding every file NCDE
  uses (copied from the live system, verified 398 files / 0 missing), the `calamares-ncde/` config
  set, and the docs. Ownership normalized (`root:root` system, `1000:1000` `home/live`) — edits need
  sudo. The squashfs is built from this tree (excludes in ISO-BUILD-PLAN §10).
- `~/ncde-ISO/` — the ISO build/work area (Method B repack of the base Archcraft ISO).

## What must ship — completeness standard (2026-06-21)
The installed system = the full working NCDE setup, **nothing left out**: native NCDE apps, GTK apps,
**flatpak apps** (Steam — the whole `/var/lib/flatpak` layer), **Tauri apps** (`verdantfolio`), the
security app (`kickass-guard` / `org.ncde.KickassGuard`), dbus services, systemd units, PAM stacks,
fonts, and the `usr/share/ncde` UI. **Do NOT cherry-pick or call components "optional."** Verify
against the actual running host, at the FILE level (not the pacman DB, not guesses). The ONLY things
excluded are ones explicitly named: Archcraft software (the DE NCDE replaces), the dead **Isla**
installer, and the dev/build toolchain. (~18 prior builds shipped broken because agents trimmed the
DE; the flatpak layer + system fonts had been dropped entirely — found and fixed 2026-06-21.)

## System Restore "Soundings" + btrfs (2026-06-22)
NCDE ships a built-in **time machine** (always intended; backend's WM C++ recovered via Ghidra and being rebuilt — the source is in the tree and compiles —
see `NCDE-RECOVERY-APP.md`). It takes a **btrfs snapshot of the working system on boot, keeps 7**; on
breakage **Ctrl+Alt+T** opens the restore **GUI on a VT** (never a terminal) → pick a snapshot → admin
password → btrfs restore → reboot fixed. Because of it, **every install is btrfs** (not ext4): Calamares
`defaultFileSystemType: btrfs`, manual partitioning hidden (consumer "Erase disk & install"), layout =
btrfs root with subvolumes `@`, `@home`, and a `/restore` subvolume for the snapshots. The QML UI
survived (verified real, no hardcoding); rebuilt = the `appBackend` host + snapshot/rollback helpers +
systemd units + the Ctrl+Alt+T VT wiring.

## Note: NCDE C++ source is in the tree and compiles (WM C++ recovered via Ghidra) — QML is plain text
The **C++** source is in the tree (`[dead-legacy-tree]/src`) and compiles; the WM C++ specifically was
**RECOVERED by Ghidra-decompiling the unstripped,
full-DWARF `ncde-wm` binary** (oracle: `~/ncde-wm-rebuild/src/decompiled/` — no `ncde-staging/` prefix;
that tree no longer exists, dev machine gone as of 2026-07-17 — 153 classes) and the WM is being
rebuilt class-by-class. This is **partial** — most classes are still raw Ghidra output, not clean
buildable source (current status: `docs/lapivot-rebuild.md`). The built binaries, the **`.qml` files**,
and configs also survived. Keep the live binaries as a fallback until a rebuild is tested (don't clobber them); the
**`.qml` files are plain text interpreted at runtime — edit directly, clear `/var/cache/ncde/qmlcache/`,
reload, no compile needed.** This blocks neither the build nor any QML fix — an install runs built
artifacts, never a compiler. Fixes live at the runtime layer (QML, session script, JSON).
