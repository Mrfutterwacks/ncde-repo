# Hummingbird — Contacts and the Address Book split

**Date:** 2026-10-04. **Status:** built, tested, installed, published
(`publish.sh --check` exit 0 → `publish.sh` exit 0).

**Operator instruction, verbatim:** *"when I said address book it should have just been
emails… phone numbers should be in a separate contacts place above address book."*

---

## 1. What was wrong

Telephone numbers and email addresses were welded into one list.

- `personEntry()` (`courier-src/googlelink.cpp`) flattened each Google person through a
  `pick()` helper that returns **one** value, so a person with three emails and two phones
  was reduced to one email and one phone. The rest were **dropped before reaching the
  cache** — not hidden, gone. No amount of looking in the UI could recover them.
- The delegate rendered `modelData.em || modelData.tel` in a single line
  (`HummingbirdCourier.qml:1138`), so a number appeared in the same slot as an address with
  nothing to distinguish them.
- One search box matched across `nm`/`em`/`tel` together, so you could not search phones
  without emails matching too.
- The name fallback `if (nm.isEmpty()) nm = tel;` used a **phone number as a person's
  name**. Measured on the operator's cache: 2 of 170 contacts had a number in the name
  field, e.g. `+1 646-362-5353`.

Measured distribution of the 170 cached contacts: **147 email-only, 22 phone-only, 1 with
both.** Neither collection is a subset of the other, which is what makes two books correct
rather than merely tidy.

## 2. What it is now

One Contacts view, two stacked sections. **Contacts** (telephone numbers) above,
**Address Book** (email addresses) below.

A person with both appears in **both** sections, once in each. Operator decision.

### `courier-src/googlelink.cpp` — `personEntry()`

- Carries **every** address in new `ems` / `tels` fields. `em` / `tel` remain populated
  (primary first) so every existing consumer keeps working.
- `srt` added as a sort key: a person with no name is `Unnamed` for display but sorts by
  their number, so ~22 unnamed people do not clump under one heading.
- The `nm = tel` fallback is gone. A number is not a name.
- Duplicates and blank values are not carried into the lists.
- **The function was moved out of the file-static anonymous namespace and declared in
  `googlelink.h`** so tests can call it. It is not part of the QML surface. This is a real
  API change and it is the reason none of this was tested before: nothing could reach it.

### `src/usr/share/ncde/HummingbirdCourier.qml`

- `book` unchanged as the source; new `phoneBook` / `emailBook` filter off it.
- `phonesOf()` / `mailsOf()` read `tels` / `ems`, falling back to the single `tel` / `em`
  so **older caches still render**.
- Per-section search via `matches(c, q, kind)` — Contacts searches names and numbers,
  the Address Book searches names and addresses.
- The `ListView` model is now a mixed array of section headers, entries and an empty-state
  row, so selection stays a single index. The detail panel resolves it with
  `m[activeContact].entry` instead of indexing the person list directly — otherwise it
  would have read `nm` off a header object.
- Rail item renamed `Address Book` → `Contacts`; panel heading → `Contacts · Address Book`.

### Manual — the spec, updated in the same change

`LEAPFROG-CONFORMANCE-20261004.md`: *the manual is the specification; where code and
manual disagree, the code moves.* Shipping a split while chapter V still described "The
Registry" as one book would have been a violation in the same commit. Chapter V now
describes two books, the both-books case, and `Unnamed`.

## 3. Tests

New: `tests/test_contacts.cpp` — **27 assertions, all passing.** Drives `personEntry()`
directly: multiple addresses survive, primary ordering, email-only and phone-only
membership, `Unnamed` and the sort key, empty persons dropped, trim/dedupe, local-part
fallback.

Also passing: `test_gcal`, `test_leapfrog`, `cal_pond_test` (16/16).

**Not proven:** nobody has seen this render. `qmllint` and the qml gate (230/230) prove it
compiles, not that the sections read well or that the header/entry index arithmetic selects
the right row. First visual check is the operator's, after a relog and a **Refresh** (the
old cache still holds phone-as-name values until Google re-syncs).

## 4. Not done

- **No editing, no adding, no writing back to Google.** Read-only split, per operator
  decision. No new scopes.
- **`publish.sh --check` still does not run the unit tests.** Recommended and not done —
  see `LEAPFROG-FREEZE-20261004.md` §7. Two checks belong in that preflight: run the
  test suite, and assert no staged file is newer than the embedded archive. Both were
  caught by hand this session; both should be automatic.
- 1707 duplicate calendar appointments and ~1750 probable Google events remain, untouched
  by operator instruction.