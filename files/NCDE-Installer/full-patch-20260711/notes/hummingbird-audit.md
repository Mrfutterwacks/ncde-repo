# Hummingbird Courier — Definitive Root-Cause Audit (binary RE, Ghidra + DWARF)

Binary: `/usr/local/bin/hummingbird-courier` (DWARF intact; all decompiles cited by VA = file offset + 0x100000).
QML front-end: `/usr/share/ncde/HummingbirdCourier.qml`.
Decompiled sources cached in the Ghidra scratchpad (`.../ghidra/out/*.c`).

Every claim below was read out of the decompiled/disassembled binary or the live QML —
addresses and byte offsets are given so it can be re-verified.

---

## 1. The "140,000 emails / downloading 2025" root cause

**Verdict: Hummingbird does NOT full-sync. The earlier hypothesis ("%1 computed as 1 → full-history
fetch") is REFUTED by the decompile.** The real fetch window is the newest **40** messages, hard-coded.

`MailEngine::openFolder` lambda body (`operator()` @ **0x1499e2**, dumped as `fn_001499e2.c`) does, in order:

1. `SELECT "%1"` (tag `b1`, timeout 15 s)
2. regex `(\d+) EXISTS` on the SELECT response → `exists`
3. `startSeq = qMax(exists - 39, 1)` — the subtraction is literally
   `sub $0x27,%eax` at **file offset 0x49da8** (bytes `83 e8 27`), followed by
   `qMax<int>(..., 1)` (`movl $0x1` at 0x49db1, call `qMax` at 0x49dcf).
4. `FETCH %1:* (UID FLAGS BODY.PEEK[HEADER.FIELDS (FROM TO SUBJECT DATE)])` with `%1 = startSeq`
   (tag `b2`, timeout 20 s) → `parseHeaderFetch` → at most 40 headers.
5. `SEARCH UNSEEN` (tag `b3`) → unread count; `LOGOUT` (tag `b9`).

GUI completion lambda @ **0x148bb0** then sets `m_messages = headers` (≤40 rows) and calls
`MailFolderModel::updateCount(folderId, exists)` — **the folder badge is set to the raw IMAP
EXISTS count**. QML renders that badge verbatim (`HummingbirdCourier.qml:504-509`,
`text: modelData.count`).

So what the operator is actually seeing:

- **"140,000 emails"** = the INBOX badge = Gmail's true IMAP `EXISTS` for INBOX. Gmail *web*
  looks "normal" because the web UI shows the Primary tab; over IMAP, `INBOX` contains ALL
  categories (Promotions, Social, Updates) plus everything never archived since the account
  was created. The number is real; nothing is being downloaded.
- **"Downloading emails from 2025"** = the sliding 40-window. The list is filled in IMAP
  sequence order (oldest of the 40 first — `m_messages` is assigned un-reversed at 0x148bb0
  line "operator=(…, in_RDX)"), and after every delete the completion handler re-opens the
  folder (see §2), which refills the view with the next-older 40. Delete a few rounds and the
  window marches backwards into 2025. It *looks* like a historical sync; it is 40 headers per
  round, ~repeated.

There is **no pagination, no date window, no "load more"** anywhere in the engine — the only
fetch primitive is "newest 40 of the selected folder".

## 2. The "delete doesn't stick" root cause

`MailEngine::deleteMessages(QStringList)` @ 0x15877a → background lambda @ **0x157d2e**
(`fn_00157d2e.c`). The exact IMAP sequence, read from the decompile:

```
SELECT "<path>"                                   (tag d1)
if (m_currentFolder == "trash"):                  # verified: operator==(this+0x170, "trash") @ 0x58cee
    UID STORE <uidSet> +FLAGS (\Deleted)          (tag d3)
    EXPUNGE                                       (tag d4)
else:
    UID MOVE <uidSet> "[Gmail]/Trash"             (tag d2)
LOGOUT                                            (tag d9)
```

`deleteMessage` (single, lambda @ **0x156812**) is identical for one UID.
`archiveMessage` (lambda @ **0x159130**): `SELECT` → `UID COPY %1 "[Gmail]/All Mail"` (e2) →
`UID STORE %1 +FLAGS (\Deleted)` (e3) → `EXPUNGE` (e4) → `LOGOUT`. Against Gmail semantics this
is a correct archive: expunging `\Deleted` from a label folder only strips that label; the
message remains in All Mail (the COPY is redundant on Gmail but harmless).

The UID set is genuine: `parseHeaderFetch` @ **0x14ae54** captures `UID (\d+)` from each
`* n FETCH` block and stores id = `"u" + counter + "-" + uid` (literals `"u"` @ 0x112b3e and
`"-"` @ 0x112b40). The delete path re-extracts with `section('-', 1, -1)` — verified in
disassembly @ 0x58bda-0x58c14 (`QChar('-')` = `mov $0x2d`, start=1 `mov $0x1,%ecx`,
end=-1 `mov $-1,%r8`) — and joins with `','` (0x58c78). So `UID MOVE 523456,523441,… "[Gmail]/Trash"`
with real UIDs.

**Verdict: the IMAP delete sequence is CORRECT per Gmail semantics.** `UID MOVE → [Gmail]/Trash`
IS the true Gmail delete (Trash purges in 30 days; delete-inside-Trash correctly does
STORE+EXPUNGE = immediate permanent). The "doesn't stick" symptom comes from three verified
design defects around it:

1. **The 40-window makes deletion invisible.** "Select all" in QML can only select what is
   loaded (`HummingbirdCourier.qml:597-603` iterates `mail.messages` — max 40). Each delete
   removes ≤40 of 140,000. The badge (EXISTS) barely moves.
2. **The completion handler instantly refills the list.** GUI lambda @ **0x157a36**: sets status
   "Deleted %1 message%2", bumps the trash badge, then calls **`MailEngine::openFolder(m_currentFolder)`**
   (line ~80 of `fn_00157a36.c`). The freshly emptied view immediately repopulates with the
   next-older 40 messages — to the operator, "the emails came back". (They did not; different,
   older ones took their place. The deleted ones are in Gmail Trash — verifiable in web UI.)
3. **Zero error checking = genuine silent-failure path.** `imapCommand` @ **0x1454ce** writes
   `tag cmd\r\n` and accumulates the socket until a line starts with `"tag "` or the timeout
   expires — it never parses `OK`/`NO`/`BAD`, and every delete-path caller **discards the return
   value**. If `UID MOVE` fails — OAuth token expiry mid-operation, Gmail account whose display
   language renames the folder away from the hard-coded English `"[Gmail]/Trash"`
   (`gmailFolderPath` @ 0x1424ca is a hard-coded English string map), Trash un-ticked from
   "Show in IMAP" in Gmail settings, or a >15 s timeout — the app STILL shows "Deleted N messages"
   and STILL bumps the trash count. This is the only mechanism by which mail would *truly* never
   leave Gmail, and it is unobservable by design.

Recommended live check to split 2 vs 3: delete one message in Hummingbird, then look at Gmail
web → Trash. If it's there, the deletes work and the symptom is entirely #1/#2. If it isn't,
check Gmail Settings → Labels → Trash "Show in IMAP", and Settings → Language = English.

## 3. The ~40 limit — where it lives

It is **not in QML** (no such constant there; the QML selects/deletes whatever is loaded).
It is engine-side, in two places:

| What | Where | Instruction / bytes |
|---|---|---|
| openFolder fetch window (40) | file offset **0x49da8** (VA 0x149da8) | `83 e8 27` = `sub $0x27,%eax` (unique in the lambda) |
| search result window (last 40 UIDs) | file offset **0x5a82f** (VA 0x15a82f) | `48 83 e8 28` = `sub $0x28,%rax` (then `qMax(...,0)` + `QList::mid`) |

Search path (lambda @ **0x15a2da**): `UID SEARCH TEXT "%1"` → takes only the **last 40** UIDs →
`UID FETCH <uids> (UID FLAGS BODY.PEEK[HEADER.FIELDS (FROM SUBJECT DATE)])`. So search never
downloads history either.

## 4. "Still receive new ones" — IMAP IDLE

`startIdle` @ 0x15d0e6, worker lambda @ **0x15c260**: dedicated connection, `SELECT "INBOX"`,
tagged `IDLE`; re-issues `DONE` + fresh `IDLE` every **1740 s** (`cmp $0x6cb,%rax` @ 0x5c554 —
29 min, inside the RFC-recommended limit); on untagged `\* \d+ (EXISTS|RECENT)` it queues
`MailEngine::refresh()` → `openFolder(m_currentFolder)`. So new-mail notification works while
the IDLE connection lives.

Caveats found in the decompile:
- If the socket drops (loop exits when `QAbstractSocket::state() != 3`), the loop terminates,
  clears the running flag, and **nothing restarts it** — `startIdle` is called exactly once,
  from `connectAccount`'s completion lambda (call site 0x46736). After any network blip, live
  updates stop until the account is reconnected (manual refresh still works).
- `refresh()`/`openFolder` no-op while `m_busy` is set, so an IDLE-triggered refresh landing
  during another operation is silently dropped.

**None of the fixes proposed below touch the IDLE path.** A QML-side change or the 0x27 byte
patch does not interact with `startIdle` at all.

## 5. Fix plan, classified honestly

### 5.1 Fetch window / "see more than 40" — root cause: hard-coded `EXISTS-39`

- **(a) LIVE-FIXABLE (binary patch, small gain only):** flip the imm8 at **file offset 0x49daa**
  from `0x27` (39) to at most `0x7f` (127) → window becomes 128 messages. The instruction is
  `sub imm8` — 127 is the hard ceiling without re-encoding to a 6-byte `sub imm32`, which does
  NOT fit in place. Same for the search window byte at **0x5a832** (`0x28` → ≤ `0x7f`).
  Risk: low (single data byte, instruction length unchanged, verified unique in function;
  patch a COPY, compare `objdump` before/after, keep the original). Gain: honest but modest —
  128-row window, 128-at-a-time bulk delete.
- **(b) NEEDS SOURCE (the real fix):** in `MailEngine::openFolder`'s lambda, replace the
  fixed window with pagination/date-windowing. Precise change, ready for a build env:
  - add `int m_fetchOffset` (reset on folder change) and a `loadOlder()` Q_INVOKABLE;
  - compute `int end = exists - m_fetchOffset; int start = qMax(end - pageSize + 1, 1);`
    and issue `FETCH start:end (...)` instead of `FETCH start:*`;
  - or date-window via `UID SEARCH SINCE <date>` + chunked `UID FETCH`;
  - expose `pageSize` as a QSettings-backed property (default 200).

### 5.2 Delete — root cause: correct IMAP, wrong UX + silent errors

- **(a) LIVE-FIXABLE (verification + operator workflow):** the IMAP commands are right; nothing
  to patch in the command bytes. The QML *could* be given a "sweep" mode today (auto re-select-all
  + `mail.deleteMessages()` chained off `messagesChanged` until the folder count stops falling)
  — it is deployable without source, but at 40/round it needs ~3,500 full
  connect→SELECT→MOVE→LOGOUT cycles for 140k messages (hours, plus token traffic). Honest
  assessment: possible, crude, not the right tool for the backlog (see §6).
- **(b) NEEDS SOURCE:**
  1. `imapCommand` must return/expose the tagged status line; delete/archive lambdas must check
     `d2/d3/d4` for `OK` and surface `NO`/`BAD` via `errorOccurred` instead of unconditionally
     reporting "Deleted N messages".
  2. Resolve special folders via `LIST` + SPECIAL-USE attributes (RFC 6154: `\Trash`, `\All`,
     `\Sent`…) instead of the hard-coded English `gmailFolderPath` map — this removes the
     non-English-locale silent-failure class entirely.
  3. Optional "Empty this folder" feature: loop `UID SEARCH ALL` → chunked
     `UID MOVE <1000-uid chunks> "[Gmail]/Trash"` on one connection — the correct in-app answer
     to a 140k backlog.
  4. After delete, do NOT blind-`openFolder`; reconcile the local list instead (or reopen but
     show "N older messages loaded" so refill isn't mistaken for resurrection).

### 5.3 IDLE robustness — **NEEDS SOURCE** (restart on disconnect; nothing live-fixable, and
current behavior is acceptable while the connection holds).

## 6. Operator options RIGHT NOW (no source, today)

1. **Clear the 140k backlog in Gmail web, not in Hummingbird.** In Gmail web: search
   `in:inbox before:2026/01/01` (or `category:promotions`, `older_than:6m`, etc.) → tick the
   select-all checkbox → click **"Select all conversations that match this search"** → Delete.
   That removes tens of thousands per operation, server-side, in minutes. Then "Empty Trash now".
   This is the only sane bulk path; no IMAP client doing 40-per-round competes with it.
2. **Prove Hummingbird's delete works:** delete one mail in Hummingbird, confirm it appears in
   Gmail web → Trash. Expected: it does (commands verified correct). If it does NOT:
   check Gmail Settings → Labels → "Show in IMAP" is ticked for Trash, and Settings →
   General → Language = English (the binary hard-codes `[Gmail]/Trash` and friends).
3. **Keep receiving mail:** nothing to do — IDLE works; after a network drop, tap the refresh
   button (`mail.refresh()`, QML:389) or reconnect the account to restart live updates.
4. **Optional binary patch** (only if a bigger window matters before a rebuild exists):
   byte 0x49daa `27`→`7f` and byte 0x5a832 `28`→`7f` on a copy of the binary → 128-message
   window and 128-at-a-time bulk delete. Verify with
   `objdump -d --start-address=0x49da0 --stop-address=0x49db0 <copy>`; keep the original binary.
5. Once the 140k is cleared server-side, the existing 40-window app is actually usable day-to-day:
   INBOX stays small, IDLE-triggered refresh shows new mail, and delete works within the window.

---
*Method note: all functions decompiled from the analyzed Ghidra project (`hb.bin`); lambda bodies
located via `nm | c++filt` (openFolder 0x1499e2, deleteMessages 0x157d2e, deleteMessage 0x156812,
archiveMessage 0x159130, search 0x15a2da, startIdle 0x15c260, GUI-side completions 0x148bb0 /
0x157a36) and verified against raw `objdump` where the decompiler garbled argument passing.*
