# Leap Frog Ledger / Google Calendar — hard freeze, root cause and fix

**Date:** 2026-10-04. **Severity:** the desktop became unusable; only a terminal
responded. **Cause:** an unbounded write loop inside LeapFrog's Google Calendar sync.

**Status: fixed, built, installed, published** (`publish.sh --check` exit 0, then
`publish.sh` exit 0).

---

## 1. What happened

Between roughly 14:57 and 15:13 the LeapFrog calendar grew from ~1152 to **1753
appointments** in about sixteen minutes. `~/.config/ncde/calendar.json` was being
rewritten every few seconds. LaPivot's **main thread reached 100% CPU** and the desktop
froze solid. Chrome froze with it — not a Chrome fault; the whole UI thread was
occupied.

Final tally: **1753 appointments, of which 46 are real. 1707 are redundant copies.**

## 2. Root cause

Two independent defects. Either alone is survivable; together they are a fork bomb.

### 2.1 The sync link was silently discarded (the fatal one)

`source-recovery/LaPivot/src/CalendarBackend_appointments.cpp` —
`normaliseAppointment()` rebuilds every appointment from a hard-coded list of eleven
fields. That list is a *deliberate* validation boundary (C6: a malformed ICS import must
not be able to inject arbitrary fields into the model), so any field a consumer adds has
to be named explicitly.

`gcal` was not on the list.

`GoogleCalendarSync` stores each event's link — `cal`, `event`, `etag`, `sig`, `ro`,
`inst` — in a `gcal` map on the appointment, and hands it to `upsertAppointment()` after
a successful push. That link was thrown away. It never reached disk.

So on the next poll, every appointment in the calendar looked like it had **never been
sent to Google**. `step2PushDeletes()` queued the lot. Again. Every five minutes,
indefinitely.

Verified rather than inferred: the installed LaPivot binary contained **zero**
UTF-16 `gcal` literals before the fix and **exactly one** after
(`d.count('gcal'.encode('utf-16-le'))`).

### 2.2 Google was given no way to recognise a re-send

`courier-src/gcalsync.cpp` — `apptToEvent()` sent no `iCalUID`. Google's Calendar API
deduplicates on `iCalUID`, not on content, so a re-POST of an existing event is not
recognised as the same event; it files a **new** one.

The pull then imported each of those as a fresh `g-…` record — which was unlinked, so it
was pushed again. Each cycle roughly doubled the set. That is the 46 → 1753 curve.

## 3. Why it was allowed to run

Nothing bounded the outbound work. `step2PushDeletes()` built its queue from every
appointment in the pond with no cap, no window, and no memory of which records Google had
already refused. On the GUI thread, each queued event is a network round trip plus a full
rewrite of a 500 KB JSON file.

The deeper reason is that nothing tested any of it. See §7.

## 4. The fixes

### LaPivot — `CalendarBackend_appointments.cpp` (C13)

```cpp
const QVariantMap link = in.value(QStringLiteral("gcal")).toMap();
if (!link.isEmpty())
    out[QStringLiteral("gcal")] = link;
```

### `gcalsync.cpp` — `apptToEvent()`

Every outbound event now carries a stable identity, so a re-push is idempotent on
Google's side:

```cpp
if (!uid.isEmpty() && !forInstance)
    ev.insert("iCalUID", uid + "@leapfrog.ncde");
```

An instance does not mint its own UID — it belongs to its series' identity.

### `gcalsync.cpp` — `step2PushDeletes()`, three bounds

1. **Window.** Only appointments inside `-kPastDays .. +kFutureDays` (−30 / +366 days) are
   pushed. That is the same span we pull. An appointment from years ago is not new, it is
   old.
2. **Cap.** `kMaxPushPerSync = 50`. One sync is bounded work; the remainder carry to the
   next poll, which is what a queue is for.
3. **Failure memory.** `m_pushFailed` records what Google refused this session, cleared in
   `done()`. A permanently-bad record cannot retry forever.

## 5. Tests

New regression: `source-recovery/LaPivot/tests/cal_pond_test.cpp::testGcalLinkSurvivesUpsert`
— the link survives upsert, survives save/reload, survives an ordinary local edit, and an
unlinked appointment does not acquire a bogus empty one.

**Verified to bite.** With the fix removed: `15 passed, 1 failed`, failing on
`'stored.contains("gcal")' returned FALSE`. With it restored: `16 passed, 0 failed`.

Four assertions added to `test_gcal` for `iCalUID` (present on a push, absent on an
instance, stable across calls, absent when there is no id).

Also repaired a **stale test**, not a regression of mine: `test_gcal` asserted
`colorId == "3"` (a Google palette index) but P4 had changed `colorForCategory` to emit
an explicit hex. Proven by diffing `colorForCategory` between the 20260925 batch source
and the staged source — the change is P4's, not mine. The test had been failing since P4
landed. It now asserts against `colorForCategory()` directly so it cannot rot again.

## 6. Containment, and what was touched

The running desktop could not be reached any other way: the tokens are held **in memory**
inside LaPivot, so no file edit could disarm it. `ncde-x11-session` relaunches LaPivot on
a non-zero exit, so `kill -TERM` was safe and reversible. Confirmed at
`/usr/local/bin/ncde-x11-session:128-147` before acting. Loop confirmed dead: file mtime
frozen, CPU 103% → 19%.

**Collateral, and it was my error.** `google-link.json` is the **shared** Google sign-in —
Hummingbird's mail and contacts read it too. Moving it aside to disarm the calendar also
disconnected the address book. `gcalsync.h` had said outright "the same one Hummingbird
uses"; I had not read it. Repaired by restoring the file with **only**
`https://www.googleapis.com/auth/calendar` removed — mail and contacts scopes intact,
address book untouched (170 contacts). The `hasCalendarScope()` gate is what makes this
surgical: `connected()` is merely `!m_email.isEmpty()`, so the calendar scope is the only
thing distinguishing LeapFrog's sync from Hummingbird's mail.

Also: `test_leapfrog` launched a real `hummingbird-courier --compose` (the trap recorded
in `LEAPFROG-POLISH-HANDOFF-20261004.md` §3 — the fake `PATH` was incomplete). Process
killed; `fakebin/` now stubs `hummingbird-courier`, `xdg-open`, `chromium`, `firefox`.

**Calendar permission is deliberately left disarmed.** Re-arming pushes all 46
appointments at Google again on top of the junk already there. Re-arm only after the
duplicates are cleaned up.

## 7. The reason this was possible

`publish.sh --check` does not run the unit tests. A red test does not block a release.
`test_gcal` had been failing since the P4 colour change and publishing stayed green
throughout — that is the clearest evidence that NCDE has no net under it.

**Standing recommendation:** wire the test suite into `publish.sh --check` so a failing
test fails the preflight. Every other fix tonight is four assertions; this is the one that
stops the pattern rather than the instance.

## 8. Not done

- **End-to-end sync against the real account has never been observed.** Everything here is
  compile-proven and unit-proven. Nothing has touched a live Google Calendar with the fix
  in place, deliberately — see §6.
- **1707 local duplicates and ~1750 probable events in Google remain.** Reported, not
  touched, per instruction.
- **Hummingbird Address Book (email) vs Contacts (phone numbers)** — parked by operator
  decision until the freeze fix shipped. Not investigated; no claim is made about whether
  it is a data-model change or a presentation split.