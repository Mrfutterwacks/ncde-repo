# Leap Frog Ledger — conformance audit vs the manual (2026-10-04)

**Spec: `files/full-patch-20260711/src/usr/share/ncde/LeapFrogManual.qml`.**
The manual is the specification. Where code and manual disagreed, the *code*
moved (operator: "the Leap Frog Ledger should reflect what the manual says it
does"). The single exception is the 12-hour decision below, where the operator
overrode the manual's `14:30` and the manual line was edited instead.

Rules applied throughout: nothing is a fact until checked on disk; every claim
below carries its proof; no deletions; one change at a time; no new or changed
animations.

---

## Ranked findings — status

| # | Finding | Status | Proof |
|---|---------|--------|-------|
| P1 | Manual promised `14:30`; operator requires 12-hour everywhere | **Fixed** | `LeapFrogManual.qml:160` now reads `9:30 AM`; code path `fmtTime(min, h12)` defaults `true` and the editor passes `true` |
| P2 | Esc did not close the command palette or PondPopup | **Fixed** | `LeapFrogLedger.qml` root `Shortcut sequence:"Escape"` includes `cmdPalette`; PondPopup has its own Escape `Shortcut` |
| P3 | Manual promised maple leaves; autumn drew something else | **Fixed** | `cal-art.js` draws embers for autumn; `drawMapleLeaf` still used at `:161` (no dead code). All four seasons executed via pty + Proxy-stub harness (`script -qec "qml6 …"`) |
| P4 | Reminders claimed delivery that could not happen | **Fixed** | `CalReminders.qml` `deliveryReport()` reads `calBackend.canDeliver("desktop"\|"email"\|"ntfy")`; `save()`/`test()` truthful. Proved `fireReminder()` (`CalendarBackend_appointments.cpp:403`) only runs `notify-send` and never checks it exists |
| P5 | `view:*` from the bottom bar force-opened the window | **Fixed** | `raiseIfOpen()` in the Ledger; `GliaLeapFrogBar.qml:62` uses it. Manual: "no need to open the window first" |
| P6 | Suspected: search missed recurring occurrences | **Not a defect** | `cal-logic.js` `inst(a,dateObj)` is a shallow copy of the base record changing only `date`/`_baseId`, so title/place/notes are always the base's. Expanding recurrences in `searchAll` would add nothing but duplicate rows |
| P7 | Manual under-documented eight shipped features | **Fixed** | Four new manual sections added (see below); verified the `Wk` gutter is **Month** view and the hand-off is in the bar's **Ledger** menu before writing |
| P8 | Manual said "Press G"; plain letter only, capital G dead | **Fixed** | Measured on private display: `sequence:"G"` fired on `g`, silent on `Shift+G`; `"G"`/`"g"` are the same sequence. Added `Shortcut { sequence: "Shift+G" }` |
| P9 | One-click unrecoverable deletes (tasks, appointment Delete, Reconcile) | **Closed by operator decision** | Manual promises no undo anywhere → no undo built. Archive separately given a confirmation (below) |
| P10 | External edits to `calendar.json` invisible until restart | **Fixed** | `reload()` existed but nothing called it. Ledger now calls `calBackend.reload()` on window activation; `load()` emits `changed()` + `settingsChanged()` (`CalendarBackend_storage.cpp:97-98`) |
| P10b | `CalendarBackend.h:80-82` gave a false reason for `reload()` | **Fixed (comment)** | Claimed the cal-reminders daemon "rewrites calendar.json every minute". Installed daemon: docstring says it *reads* it (`cal-reminders:4`), its only write is `calendar.fired` (`:115`). Comment now states the real reason |
| P11 | Stale duplicate tree `files/NCDE-Installer/full-patch-20260711/` | **Handled by operator decision** | 669 files / 246 MB / 148 differences from the canonical tree; `publish.sh --check` never references that path. Held the **only** copy of `etc/ncde/hummingbird-google-client.json` → preserved (see below), tree left untouched |

### The one place the manual moved
P1 is the sole edit *to the spec*: the operator requires 12-hour everywhere, so
`14:30` in the manual became `9:30 AM`. Everything else moved the code.

---

## P7 — the four sections added to the manual

Written in the manual's existing voice, describing only what the code does:

1. **PAPERS AND PASSAGES** — `IMPORT ICS…` (FileDialog, reports "N appointments
   imported"), `EXPORT ICS…` (`~/leapfrog.ics`), `EXPORT CSV…` (`~/leapfrog.csv`,
   columns date/time/title/notes), `EXPORT LILY-PAD…` (`~/leapfrog.lilypad` —
   notes + notice + appointments).
2. **KEEPING THE POND TIDY** — `STOCK THE POND`, `TALLY THE LILY PADS`,
   `RECONCILE` (clears lily-pad notes older than 30 days, reports the count),
   `ARCHIVE PAST ENTRIES` (now confirms first).
3. **IF IT MUST GO BY LETTER** — `Ledger` menu → `Send as Hummingbird message…`;
   with no appointment open it opens the window and says so instead of being a
   silent no-op (`GliaLeapFrogBar.qml`, `mail.selected`).
4. **SMALL ENGRAVINGS** — `Wk` ISO week-number gutter (Month view), lore cards
   from the holiday name in Month view and `open the lore ›` in Year view, the
   Day view "On this day" card, and `SEASON CARD…`.

Deliberately **not** documented: task `due`/`priority`. They exist only as
defaults in `addTodo()` (`LeapFrogLedger.qml:404`) — never rendered, never
editable, unread by the daemon. Promising them in the manual would have created
a false promise, so P7 covers them as *unreachable fields*, not features.

---

## Changes made this session (stage tree)

| File | Change |
|------|--------|
| `LeapFrogLedger.qml` | rail duplicate `app._notice` removed (toast only); `Shift+G` shortcut; day-cell `+` affordance; `archiveConfirm` dialog + `askArchive()`; Esc covers it; CSV/Lily-Pad/Reconcile now report; `reload()` on window activation; **rail 168→196 with two-line labels**; **CalBtn `‹ ›` glyph fix** |
| `LeapFrogManual.qml` | P1 time fix; the `+` affordance described; four new sections |
| `GliaLeapFrogBar.qml` | `view:*` uses `raiseIfOpen()`; CSV/Lily-Pad/Reconcile announce their result; `archive` goes through the confirmation |
| `CalReminders.qml` | honest `deliveryReport()` |
| `cal-art.js` | autumn embers (P3) |
| `source-recovery/LaPivot/src/CalendarBackend.h` | false `reload()` comment corrected (documentation only — C++ is not rebuilt) |

---

## Proof gathered this session

- **Compile gate: `qml gate: all 229 QML files compile`** — run twice, absolute
  path only (a relative path yields 229 bogus `type:fileselector: Network error`
  failures), `TMPDIR=/tmp/opencode`.
- **`Shift+G` measured**, three cases on a private display:
  `Shift+G + shift+g → FIRED`, `Shift+G + plain g → silent`,
  `G + plain g → FIRED`. Both keypresses of the manual's "Press G" now work.
- **Live vs stage:** exactly 5 files differ, no live-only files, verified with
  null-delimited `find` (a space-bearing filename `NCDE Settings Manual.html`
  initially defeated a word-splitting loop — a false alarm, file matches).
- **Payload rebuilt:** 661 files, 179 MB tar, **0 `prebak` entries** spliced
  into `ncde-full-patch-20260711.sh` after `__NCDE_PATCH_ARCHIVE_BELOW__`
  (line 2897) and mirrored to `NCDE-Installer/`.
- **Google credentials preserved:** `hummingbird-google-client.json` copied to
  `files/ncde-batches-20260925/ncde-hb-contacts-20260925/`, sha256 match
  `4cc36d1a0f64ab6571e205391c4da656…`, 412 bytes, **outside** the published
  payload (confirmed by grepping the tarball).
- **Handoff doc unified:** `docs/HUMMINGBIRD-HANDOFF.md` and the batch copy had
  diverged (docs held STATUS + the 2026-09-26 research + the resolved spam note;
  the batch held the 2026-10-04 FINDINGS + the operator's API-enabled update).
  Both are now byte-identical supersets, all 20 unique section headers verified
  present, backups `*.prebak-20261004`.

## Not yet proven (stated plainly)

- The **Archive confirmation dialog**, the manual's **four new sections**, the
  **`‹ ›` arrow fix** and the **wider/wrapped rail labels** are compile-proven
  (gate) but **not visually confirmed**: the running shell (LaPivot pid 993)
  started **03:51:17**, while those edits landed at **05:41:27**, so the window
  was still drawing the pre-fix QML when last captured. Confirmed instead by
  measurement on the pre-fix build: arrow buttons were pure `#E89F43` (17
  colours from the button gradient vs 145 inside TODAY) because Cinzel reports
  a ~1px advance for U+2039/U+203A, collapsing `lbl.implicitWidth` to ~1.
  A relog will show it; the operator chose to publish rather than relog, since
  a relog ends this session.
- `reload()` on activation is wired and `load()` provably emits, but the
  end-to-end "edit `calendar.json` externally and watch it appear" was not
  observed live.
- The Google scope grant still cannot be verified without the operator signed
  in at the consent screen (only `openid email profile …/mail.google.com/` ever
  granted; calendar unticked → `403 ACCESS_TOKEN_SCOPE_INSUFFICIENT`).

## Delivered

**`bash publish.sh` — exit 0, package `ncde-2026.10.04.0545-1-x86_64.pkg.tar.zst`
signed and uploaded to https://github.com/Mrfutterwacks/ncde-repo/releases**;
the previous `ncde-2026.10.03.1906-1` entry was replaced in the repo database
and the db/files tarballs re-signed. Machines will show *"NCDE has updates"*
within a few hours.

Preconditions met immediately before publishing:

1. Stage tree — gate **229/229**.
2. Embedded archive rebuilt — 661 files, 179 MB, **0** `prebak` entries,
   spliced after `__NCDE_PATCH_ARCHIVE_BELOW__`, mirror identical.
3. `publish.sh --check` — **exit 0** (full patch 651 byte-identical, runner,
   vesper 8, UI parity 339, system payload 540/541, payload agreement 601
   deployable / 105 excluded / **0** failing). Run **twice**: once as a
   baseline that correctly caught `cal-art.js` out of sync, once after install.
4. `publish.sh` — exit 0.

Operator decisions recorded this session: 12-hour everywhere (manual line 160
edited rather than the code); **no undo** (manual promises none — P9 closed by
decision); **Archive confirms first**; undocumented-but-shipped features
**written into the manual** (P7); orphan tree **preserved with its Google
credentials copied out** (P11).
