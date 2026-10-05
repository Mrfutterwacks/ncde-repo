# Leap Frog Ledger — polish hand-off (2026-10-04)

**Purpose:** what to polish next in the Leap Frog Ledger, and the exact procedure
for updating the manual when a feature is added.

**Status: PUBLIFIED — `ncde-2026.10.04.1328-1`.** `publish.sh --check` exit 0, then
`bash publish.sh` exit 0 — built, signed, uploaded to
https://github.com/Mrfutterwacks/ncde-repo/releases, repo db re-signed, previous
entry `ncde-2026.10.04.1308-1` replaced. Machines show "NCDE has updates" within
a few hours.

**P1 is done and shipped.** The manual now carries **THE WIDER RIVER** — *My pond
runs into Google's calendar* — 13 sections, 260 lines. Verified in the published
package: the manual inside `ncde-2026.10.04.1328-1` is byte-identical to the staged
tree and contains the new section.

**Installed to live first** (`sudo bash ~/install-leapfrog-sync.sh`, 13:07:34,
backups `~/ncde-install-backups/20261004-130734/`): the five files that carry the
Google Calendar sync — `LeapFrogLedger.qml`, `LeapFrogGoogle.qml` (new),
`CalEditor.qml`, `GliaLeapFrogBar.qml`, `libncdecourier.so`. All five verified
byte-identical to the staged tree after install.

---

## 1. The one gap that matters most

**The manual does not mention Google Calendar at all.** `grep -in "google\|sync"
LeapFrogManual.qml` returns only the Hummingbird letter section. The biggest
feature the Ledger has ever gained — two-way sync with Google Calendar — is
undocumented, along with:

- the **GOOGLE CALENDAR…** rail item, and its dot (gold until the calendar
  permission is granted, leaf afterwards — `LeapFrogLedger.qml`, `gsync.connected`);
- **view-only appointments** (a calendar shared read-only, or someone else's
  meeting): they cannot be moved or resized, and the Ledger says so
  (`app.viewOnly(rec)` → "… is view only — it belongs to …");
- the **invitation attached** to "Send as Hummingbird message…" — the manual's
  letter section says the particulars "travel over to Hummingbird Courier", which
  is true but no longer the whole story: a real `.ics` rides along, so the
  recipient's LeapFrog, Google Calendar, Outlook or Apple Calendar adds it in
  one click.

**This is a spec violation, not a writing task.** The standing rule is
`LEAPFROG-CONFORMANCE-20261004.md`: *the manual is the specification; where code and
manual disagree, the code moves* — except where the operator overrides. A shipped
feature the manual never promised is the same class of defect as P7 (manual
under-documented eight shipped features), which was fixed by writing them in.

---

## 2. How to update the manual

`LeapFrogManual.qml` is **256 lines and data-driven**. The body is one `Repeater`
over a model array (`LeapFrogManual.qml:131-181`). **Adding a section is a data
change — no layout work.**

### The shape of a section

```qml
{ rule: true,
  kicker: "PAPERS AND PASSAGES",          // small caps eyebrow, letterSpacing 3
  h:     "Nothing you entrust to me is trapped here",   // display font, bold
  lead:  "…",                            // optional italic fell intro
  p:     "Body text with <b>bold</b> and <i>italic</i>." },
```

- `rule: true` puts a hairline gradient above the section. Every section has it.
- `kicker`, `h`, `p` are required in practice; `lead` is optional (only the
  WELCOME section uses one).
- `p` is `Text.RichText` — `<b>`, `<i>` work. Do not use raw `&`; write `&amp;`.
- Fields are `|| ""`-guarded and `visible:`-driven, so an omitted field simply
  renders nothing. You cannot break the layout by leaving one out.

### The procedure

1. **Write the code first.** The manual describes what the code does — never the
   reverse (P7's rule). A feature that is not in `calendar.json`'s world yet has
   no business being in the manual.
2. **Append the object** to the model array at `LeapFrogManual.qml:132-180`.
   Keep the array's existing order: the sections read as a tour of the pond, and
   the sign-off ("There is no finer pond in all the world…") is hardcoded after
   the `Repeater` at `:245` — new sections go *before* it, not after.
3. **Match the voice.** Plato the frog, first person, present tense, warm and
   slightly pompous, no exclamation marks in kickers, British-inflected
   ("marshalled", "inscribes"). Read the existing twelve before writing a
   thirteenth; the voice is the whole charm of the thing.
4. **Run the gate** — the manual is QML and must compile:
   `bash files/NCDE-Installer/packaging/qml-compile-gate.sh <abs path to src>`
   with `TMPDIR=/tmp/opencode`. Absolute path only (a relative path yields bogus
   `type:fileselector: Network error` failures).
5. **Look at it.** `qmllint` proves it compiles, not that it reads well. The
   about panel is opened from the Ledger's rail (`aboutPanel` Loader).
6. **Then publish** — `bash files/NCDE-Installer/packaging/publish.sh --check`
   (never bypass it), then `bash publish.sh`.

### What not to write

- **No false promises.** P7's precedent: task `due`/`priority` exist only as
  defaults in `addTodo()` (`LeapFrogLedger.qml:404`) — never rendered, never
  editable, unread by the daemon. They are documented as *unreachable fields*,
  not features. Same discipline applies to anything half-built.
- **No undo.** The operator decided P9: the manual promises no undo anywhere, so
  none was built. Do not imply one.
- **No new or changed animations.** Standing rule from the Hummingbird work.

---

## 3. Ranked polish list

Evidence is `courier-src/gcalsync.cpp` unless noted. Line numbers are from the
staged tree.

| # | Finding | State | Proof |
|---|---------|-------|-------|
| **P1** | Google Calendar sync is entirely absent from the manual | **Not done** | `grep -in "google\|sync" LeapFrogManual.qml` → only the Hummingbird letter section |
| **P2** | No `If-Match` on update/delete, no `412` handling | **Not implemented** | `grep -nE "If-Match\|If-None-Match\|412" gcalsync.cpp` → no matches. Updates go out as `POST`/`PATCH` (`:407`) and `DELETE` (`:364`) with the etag stored (`:416`, `:818`) but never sent back. `HUMMINGBIRD-HANDOFF.md` #5: update/delete `If-Match`, `412` → re-fetch and merge, never blind-overwrite |
| **P3** | Polling is a flat 5 minutes, no jitter, no backoff | **Not implemented** | `gcalsync.cpp:66` `setInterval(5 * 60 * 1000)`; no `jitter`/`backoff` anywhere. Doc #5: jitter each interval ±25%, exponential backoff on 403/429, never a full sync at midnight |
| **P4** | No `colors.get` — Google's colour ids are stored, not mapped to gems | **Not implemented** | `grep -n "colors" gcalsync.cpp` → no matches; `colorId` is carried on the event (`test_gcal` asserts `colorId == "3"`) but nothing maps it to the six gems |
| **P5** | Sync core is **REST v3**, not CalDAV | **Shipped — needs your decision** | `gcalsync.cpp:27` `kApi = "https://www.googleapis.com/calendar/v3"`. `HUMMINGBIRD-HANDOFF.md` #5 says CalDAV. REST was chosen; it does have `syncToken` (`:437`, `:427`, `:527`) and per-item `etag` (`:499-500`) and `sig` (`:376`, `:512`), which covers the cheap-incremental and loop-avoidance halves. What REST cannot do is single-instance overrides cleanly — it needs `status:"cancelled"` exceptions kept for the parent's lifetime |
| **P6** | View-only appointments are enforced but undocumented | **Code done, manual silent** | `app.viewOnly(rec)` blocks `commitMove`/`commitResize` with a notice; `test_gcal` covers `ro` and `(busy)` |
| **P7** | Task `due`/`priority` are unreachable fields | **Closed by decision** | Defaults in `addTodo()` only — never rendered, never editable, unread by the daemon. Documented as *unreachable*, not as features |

### Already shipped and verified (do not redo)

- **Shared-calendar subscription** — `calendarList` is read (`:289`) and
  `calendarList.insert` is used (`:689`), which is the doc's #6 requirement that
  sharing does not auto-insert.
- **ACL** — read (`:637`), insert (`:667`), delete (`:677`).
- **Single scope** — `openid email profile …/auth/calendar`
  (`googlelink.cpp:542`), PKCE S256, loopback `127.0.0.1:<random port>`
  (`:521`, `:554-555`), and the granted scope is diffed and surfaced
  (`googlelink.cpp:135`, `gcalsync.cpp:267`) — the exact failure mode of the
  2026-09-25 rollback is now impossible by construction.
- **Debounce** — local edits coalesce through a 4 s single-shot timer (`:71`),
  so typing does not hammer the API.
- **Tests** — `test_gcal` and `test_leapfrog` both ALL PASSED. Run them from
  `/tmp/opencode/gt/build` **with `PATH=/tmp/opencode/gt/fakebin:$PATH`** —
  without it, `test_leapfrog` resolves the *real* `hummingbird-courier` and
  launches your mail client. (An agent did exactly that on 2026-10-04 and was
  rightly shouted at.)

---

## 4. Not yet proven — stated plainly

- **End-to-end sync against the real account has not been observed.** The unit
  tests prove the conversion logic (Google ↔ LeapFrog, all-day, repeats,
  cancellations, view-only, `(busy)`). They do not prove your Google project
  answers. That needs the operator signed in at the consent screen.
- **The calendar scope has not been granted yet.** `HUMMINGBIRD-HANDOFF.md`
  precondition (b): one live token whose `scope` contains `auth/calendar`. Until
  the operator consents, `gsync.connected` stays false and the rail dot stays
  gold. This is expected, not a fault.
- **P2/P3/P4 are compile-known, not behaviour-known.** Nothing here has been
  exercised against the live API.
- **The manual's new section (P1) has not been written** — see §2 for the
  procedure.

---

## 5. Standing rules that still apply

- **The manual is the specification.** Code moves to match it, unless the
  operator overrides (the one exception so far: 12-hour time, where the manual
  line was edited instead).
- **Nothing is a fact until it is checked on disk.** Every claim above carries
  its proof; anything unverified is labelled as such.
- **Never bypass `publish.sh --check`.** `docs/.github/copilot-instructions.md`
  requires all checks to pass before publishing.
- **No new or changed animations.** No undo. No deletions without a
  confirmation the manual already promises.
- **Hands off `ncde-portal`, PAM, `logind`, and the login manager.**
- **Backups go to `~/ncde-install-backups/<timestamp>/`** — never inside
  `/usr/share/ncde`, where a stray file fails the preflight (Trap #1).
- **The live system at `/usr/share/ncde` is known-good** — it is now
  `ncde-2026.10.04.1308-1`. Rollback for the five files:
  `sudo cp -p ~/ncde-install-backups/20261004-130734/<rel> /<rel>`, then relog.
