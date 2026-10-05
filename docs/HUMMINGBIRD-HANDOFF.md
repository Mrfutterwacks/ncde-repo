# Hummingbird Courier — hand-off for the next agent (2026-09-26)

## Read this first — how the operator wants this done
- The 2026-09-25 attempt was built and "tested" only against a FAKE Google and a
  FAKE Gmail (tests/sandbox). It passed everything and broke on the real account.
  Operator: "it was using fake stuff.. when it could have just had me login and it
  could have looked at hummingbird.. editing software you don't understand is why
  we are in this situation." / "it's like you guys don't know how an email client
  for desktop works."
- So: work against the REAL Hummingbird and the REAL Gmail account, with the
  operator signing in and watching. Understand what the installed program does
  before changing it. A fake server may supplement, never replace, a real check.
- Behave like a normal desktop mail client (Thunderbird): one long-lived IMAP
  connection, the letter vanishes from the list the instant you press Delete, the
  server work happens behind it, no full-folder reloads.
- System files are root-owned: stage + hand the operator a `sudo` command, never
  sudo yourself. No new/changed animations. Never touch portal/lock screen.
- Keep the master patch current everywhere (see "Master" below).

## Research FIRST: how Mozilla Thunderbird and Outlook Express do this
Operator request (2026-09-26): before designing anything, research how real
desktop clients handle each of these, and copy their proven behaviour:
- **Thunderbird** (open source — read the actual code/docs, e.g. comm-central
  mailnews/imap, and its Google OAuth2 setup):
  - Google sign-in: which OAuth scopes it asks for, when, and how it handles the
    consent page (incl. unticked boxes); how it stores/refreshes tokens.
  - Contacts: CardDAV address book for Google (it uses CardDAV, not the People
    API) — how it is set up automatically for a Gmail account and how it syncs.
  - Calendar: CalDAV for Google Calendar (Lightning) — two-way sync, sharing.
  - Delete: "move to Trash" model on Gmail, the letter removed from the list
    instantly, one persistent IMAP connection (+ IDLE), connection caching,
    offline/pending operations, what happens if the server step fails.
  - Spam/Junk folder delete on Gmail.
- **Outlook Express** (closed, historical — manuals/KB articles/behaviour
  descriptions): its simple desktop model — instant delete to Deleted Items,
  address book (WAB), folder sync, what the person sees while the server catches up.
Write down what you found (with sources) in this file before writing code, and
say which behaviour you're copying and why.

## STATUS 2026-09-26 12:55 (read this first)
- Hummingbird fix INSTALLED + operator-confirmed (167 Gmail contacts, live counts, IDLE Inbox).
  Batch ~/Projects/ncde-hb-fix-20260926 (USB files/ncde-batches-20260926). FOLDED as step 7aw,
  master 586cb2f1 (all USB copies + 3 src trees + embedded archive verified). System copy
  /usr/local/share/ncde-fix needs operator sudo cp.
- Engine delete was already correct (COPY to [Gmail]/Trash); the real bug was stale counts.
- Google: Hummingbird's built-in client is project 92324366983 (not the operator's). The
  operator's own project western-stone-464300-t4 (Desktop client) is used via
  ~/.config/ncde/hummingbird/google-client.json; People + Calendar APIs on; consent screen
  PUBLISHED (unverified). The master installs /etc/ncde/hummingbird-google-client.json only if
  the operator puts it in the src tree (agent was blocked from copying the secret).
- LeapFrog typing fix staged ~/Projects/ncde-leapfrog-typing-20260926 (Ledger window never
  took X keyboard focus; proven in xvfb). NEXT: LeapFrog <-> Google Calendar.

## Research findings (2026-09-26 11:50) — read from Thunderbird's real source
Purpose: learn how a proven desktop client does each thing, then fix HUMMINGBIRD
(operator: "we are not recreating thunderbird, we are reading its code to fix mine").
Sources: hg.mozilla.org/comm-central (tip) — mailnews/base/src/OAuth2Providers.sys.mjs,
OAuth2.sys.mjs, mailnews/imap/src/nsImapMailFolder.cpp, mailnews/mailnews.js,
mailnews/addrbook/modules/CardDAVUtils.sys.mjs + CardDAVDirectory.sys.mjs;
support.google.com/mail/answer/78892.
1. Google sign-in (OAuth2Providers.sys.mjs): ONE Google client, scopes
   imap/smtp = https://mail.google.com/, carddav = https://www.googleapis.com/auth/carddav,
   caldav = https://www.googleapis.com/auth/calendar. Comment: "When we add a Google
   mail account, ask for address book and calendar scopes as well. Then we can add an
   address book or calendar without asking again." PKCE, external browser.
   OAuth2.sys.mjs reads the returned `scope`; if it differs from what was asked it
   logs "Scope X was requested, but Y was granted" and stores what was granted.
   → Copy: ask mail+contacts+calendar together, read `scope`, and (improving on TB,
   which only logs) SAY on screen which box was left unticked + offer to retry.
2. Contacts: Thunderbird uses Google CARDDAV (https://www.googleapis.com, well-known
   discovery), not the People API; sync = WebDAV sync-collection with a sync-token
   (updateAllFromServerV2), fallback getctag; first fill = fetchAllFromServer; resync
   every 30 min (carddav.syncinterval), first sync 30 s after start.
   Note: CardDAV only has "My contacts", not Gmail's "Other contacts" (auto-saved
   people you've written to) — the People API has both. Decide with the operator.
3. Delete (nsImapMailFolder.cpp): default delete_model = 1 (move to Trash). A
   user-initiated move/delete on the same server is done "pseudo-offline"
   (CopyMessages → CopyMessagesOffline even when online): the letter is removed from
   the local DB/list IMMEDIATELY, an offline op is queued and played back to the
   server afterwards (MOVE if the server has it, else COPY+STORE \Deleted+EXPUNGE).
   Deleting inside Trash (or with deleteStorage) = STORE \Deleted + EXPUNGE
   (permanent). Spam/Junk is NOT special: delete there = move to Trash.
   Connections are cached and reused; use_idle = true (IDLE on the open folder).
4. Gmail (Google answer 78892): a letter merely expunged from an IMAP folder stays in
   "All Mail" (= archived). Only a move/copy into [Gmail]/Trash deletes it.
   Hummingbird's engine does COPY to its \Trash folder + STORE + EXPUNGE
   (HB-DIAG "delete1 a6(copy-to-trash)" / "a8(expunge)") — whether it really lands
   in Trash on the real account must be checked with the operator (not assumed).

## FINDINGS (2026-10-04) — research done, sources cited, no code written yet

Method: Mozilla `comm-central` source (searchfox + hg.mozilla.org), Google's own
docs on developers.google.com, Mozilla's Thunderbird KB, an archived Microsoft KB.
Sources are inline. A separate "could not verify" list is at the end — do not treat
anything in it as established.

### 1. Which protocol: CalDAV (Thunderbird core) — copy this
- Core Thunderbird syncs Google Calendar over **CalDAV**; the REST/GData path is a
  *separate third-party add-on*, not in the core tree. Thunderbird's own docs:
  *"Provider for Google Calendar … talks to Google Calendar using Google's
  proprietary APIs … unavailable using CalDAV"* —
  https://source-docs.thunderbird.net/en/latest/calendar/calendars.html
  (https://searchfox.org/comm-central/source/calendar/docs/calendars.md)
- Google CalDAV: start point `https://apidata.googleusercontent.com/caldav/v2/<id>/events`
  over **HTTPS + OAuth 2.0 only** — *"Attempting to connect over HTTP or using Basic
  Authentication results in an HTTP 401"*, and the old `/calendar/dav` endpoint is
  *"deprecated and is no longer supported"* — https://developers.google.com/calendar/caldav
  (App passwords are dead: https://support.google.com/accounts/answer/6010255)
- Google's CalDAV supports **only `If-Match`** among conditional headers, mandates
  **RFC6578 collection sync after the first sync**, supports `ctag`, has **no
  RFC3744 ACL, no VTODO/VJOURNAL**, and shares the Calendar API's quota.

### 2. The OAuth flow, and the exact bug that bit us
- Thunderbird = **installed app + loopback redirect + PKCE S256**: default
  `http://127.0.0.1`, listener opened on a *random free port*, that exact URI sent as
  `redirect_uri`; `usePKCE: true`, `useExternalBrowser: true` —
  https://searchfox.org/comm-central/source/mailnews/base/src/OAuth2Providers.sys.mjs
  and https://searchfox.org/comm-central/source/mailnews/base/src/OAuth2.sys.mjs
  Matches Google's documented desktop option (loopback, `code_challenge` "Recommended")
  — https://developers.google.com/identity/protocols/oauth2/native-app
- Its calendar scope is `https://www.googleapis.com/auth/calendar`
  (OAuth2Providers.sys.mjs lines 15-21, 74-77).
- **Why we got an unticked box:** granular consent appears when you request *more
  than one* non-sign-in scope, and *"the application must check what scopes are
  granted … can't assume users grant all requested scopes."* Requesting **only one**
  non-sign-in scope → *"there is no checkbox … users either approve or deny the
  entire request."* — https://developers.google.com/identity/protocols/oauth2/resources/granular-permissions
- **Our rollback** = `openid email profile …/mail.google.com/ …/auth/calendar` ⇒
  >1 non-sign-in scope ⇒ checkbox screen ⇒ calendar unticked ⇒
  `403 ACCESS_TOKEN_SCOPE_INSUFFICIENT`.
- Installed apps cannot use incremental auth ("not supported … the client cannot
  keep the client_secret confidential"), and refresh tokens are **always** returned
  for installed apps — so no `access_type=offline` is needed.
  https://developers.google.com/identity/protocols/oauth2/native-app

### 3. The two 403s are disjoint diagnostics
| Error | Means | Fix |
|---|---|---|
| `ACCESS_TOKEN_SCOPE_INSUFFICIENT` | API answered; **the token lacks the scope** (box unticked / scope never requested) | re-consent for `auth/calendar`, then read back `scope` |
| `accessNotConfigured` / `ACCESS_NOT_CONFIGURED` | **API not enabled on this project** | API Library → Enable |

Every API must be enabled per project
(https://developers.google.com/identity/protocols/oauth2/web-server#enableapi).
Confirm with a probe `GET https://www.googleapis.com/calendar/v3/users/me/calendarList`.
→ **Operator has enabled the Calendar API (2026-10-04). The scope half is what remains.**

### 4. Verification status / the 7-day trap
- "Testing" publishing status ⇒ refresh token **expires in 7 days** (unless only
  name/email/profile) — https://developers.google.com/identity/protocols/oauth2
- Sensitive scopes: verification is *not* required during development (click through
  Advanced → unsafe); published-but-unverified caps at 100 users; verification 3-5
  days — https://developers.google.com/calendar/api/troubleshoot-authentication-authorization
  and https://developers.google.com/identity/protocols/oauth2/production-readiness/overview
- Working config for us: **External + "In production" (unverified) + one calendar
  scope.**

### 5. Sync mechanics to copy
- **Conflicts:** optimistic concurrency, per-item etag. Create `If-None-Match: *`,
  update/delete `If-Match`, `412` → re-fetch and merge, never blind-overwrite
  (https://developers.google.com/calendar/api/guides/version-resources; Thunderbird:
  https://searchfox.org/comm-central/source/calendar/providers/caldav/modules/CalDavRequest.sys.mjs)
- **Deletes:** CalDAV/RFC6578 reports them as `404` in `sync-collection` (or absent on
  full sync) — no synthetic cancelled records to retain. REST instead requires keeping
  `status:"cancelled"` exceptions for the parent's lifetime
  (https://developers.google.com/calendar/api/v3/reference/events).
- **Recurring single instances:** CalDAV = one resource per `RECURRENCE-ID` override;
  REST needs `singleEvents=true` or `events.instances`.
- **Loop avoidance:** content-hash of the last server object per id (`sig` — the
  rolled-back design already had this) → skip the PUT when unchanged, debounce local
  edits. Never echo an inbound change back out.
- **Polling:** push/`watch` needs a **public HTTPS webhook** — impractical desktop, so
  poll. Thunderbird's default is **30 min**; Google calls repeated polling an
  anti-pattern but prescribes: jitter each interval **±25%**, never a full sync at
  midnight, exponential backoff `min(2^n + rand(≤1000ms), max)` (max 32-64 s) on
  403/429 — https://developers.google.com/calendar/api/guides/quota
- **Cheapness:** CalDAV `ctag`/sync-token probe first, fetch only on change; a 4xx
  invalidates the token → full refresh.
- **Quota (changed 2026-05-01):** 10,000 req/min/project, 600/min/user, 1,000,000/day.
  Old per-endpoint tables are stale. CalDAV = same quota.

### 6. CalDAV can't do three things → REST with the *same single* scope
`calendarList.list` (has its own `syncToken`; **subscribe with `CalendarList.insert()`** —
sharing does *not* auto-insert) · `colors.get` for the gem mapping · `acl.insert` for
share-by-email (CalDAV has no ACL).
https://developers.google.com/calendar/api/v3/reference/calendarList/list ,
https://developers.google.com/calendar/api/v3/reference/colors/get ,
https://developers.google.com/calendar/api/concepts/sharing

### 7. Outlook Express — the UX contract
**OE had no calendar at all**: *"Choose Outlook if: You require integrated personal
calendars…"* (Microsoft KB 257824,
http://web.archive.org/web/20041022015541/http://support.microsoft.com:80/kb/257824/EN-US/).
Everything was local first — `.dbx` per folder, `.wab` address book — and the server
was a background "Synchronize" step. **Copy: the desktop object is real and local;
the network reconciles behind it and is never in the critical path of a user action.**
(This matches how Leap Frog already works: the local `calendar.json` write happens
first and `gcalsync` goes through `calBackend`.)

### WHAT TO COPY — instructions for the next engineer
1. Request **exactly one** scope, `https://www.googleapis.com/auth/calendar`. Never
   concatenate a second into the same token request — one non-sign-in scope ⇒ no
   checkbox screen ⇒ the rollback's failure mode becomes impossible.
2. After **every** token response, parse `scope` and diff against what was requested.
   If `calendar` is missing, fail loudly in the UI ("Google did not grant calendar
   access — sign in again"). Thunderbird only *logs* this; we must surface it.
3. Installed-app flow: own client id/secret (do **not** copy Thunderbird's — its source
   says so), Desktop app type, PKCE S256, loopback `http://127.0.0.1:<random port>`.
4. Consent screen: **External + "In production"**, not "Testing" (7-day tokens).
5. Sync core = **CalDAV** `…/caldav/v2/<calendarId>/events` over HTTPS+OAuth. Persist
   `(uid, recurrenceId, href, etag, contentHash)`; `If-None-Match: *` / `If-Match`;
   `412` → re-fetch + merge.
6. Poll cheaply (ctag first, then fetch), jitter ±25%, backoff on 403/429. No push.
7. Never write back what you just pulled: keep `sig`, skip unchanged PUTs, debounce
   local edits; combine with `If-Match` for lost-update safety.
8. Local store is the product — user actions complete locally, sync reconciles.
9. Keep REST only for calendarList / colours / ACL, using the same one scope.
10. Before any code, verify both preconditions: (a) API enabled — **done by operator
    2026-10-04**; (b) one live token whose `scope` contains `auth/calendar`. Those two
    checks would have caught the entire rollback.

### Could NOT verify (do not treat as established)
Google's CalDAV behaviour for single-instance overrides and for per-event colours
(undocumented, untested) · whether Thunderbird's own consent screen really shows
tick-boxes for a calendar-only request (derived from code) · whether its client id
has completed verification · which Linux credential store backs its login store ·
the exact API-Library entry name to enable for CalDAV · whether Google evaluates
"API enabled" before or after "token scope" · `include_granted_scopes` behaviour for
installed apps · OE's exact sync cadence (inferred from the local-`.dbx` architecture).


## Current state (11:45 2026-09-26)
- Operator ROLLED BACK the batch (`revert.sh`). Live /usr/share/ncde Hummingbird +
  LeapFrog QML == the pre-batch originals (sha-checked); the NCDE.Courier module is
  set aside as /usr/lib/qt6/qml/NCDE/Courier/*.reverted-hbcontacts-20260925-222746.
- The master was un-folded: master sha256 7f32f2b6 = previous master + 7at
  (smooth orrery/weather) + 7au (hardware discovery), WITHOUT 7av (Hummingbird).
  All 5 USB copies + 3 full-patch-20260711/ src trees updated and verified.
  Local copy: ~/Projects/ncde-master-7f32f2b6.sh. The system copy
  /usr/local/share/ncde-fix/ncde-full-patch-20260711.sh needs the operator's
  `sudo cp` (it was at the 13:35 09-25 version = before 7at/7au).
- The old batch (~/Projects/ncde-hb-contacts-20260925, USB
  files/ncde-batches-20260925/ncde-hb-contacts-20260925) is RETIRED — its
  fieldkit master renamed *.RETIRED-broken-hb-20260926, DO-NOT-INSTALL.txt added.
  Its src/ is still useful reading (mimetext decoder, UID MOVE logic, People API
  parsing), but do not reinstall it as-is.
- Leftovers, harmless, left in place: keyring item "Hummingbird Courier — Google
  (papishijo123@gmail.com)" (schema com.ncde.Courier.GoogleLink) and
  ~/.config/ncde/hummingbird/google-link.json. The engine's accounts.json was
  re-saved by last night's sign-in (same client, mail scope) — confirm with the
  operator that mail still loads after the rollback.

## Verified facts about the REAL account (not the fakes)
Measured 2026-09-26 with read-only diagnostic builds (scratchpad, not kept):
1. Google granted ONLY: `openid email profile https://mail.google.com/`.
   Contacts (contacts.readonly, contacts.other.readonly) and calendar were NOT
   granted — Google's consent page shows them as separate tick-boxes and nothing
   told the operator to tick them. People + Calendar APIs → 403
   ACCESS_TOKEN_SCOPE_INSUFFICIENT. (So whether the People/Calendar APIs are even
   enabled on Hummingbird's Google project is still UNKNOWN.) The code then set
   autoPrompted=true and never asked again.
   Fix direction: a separate, clearly explained incremental consent for just
   contacts + calendar, done with the operator at the screen; check the returned
   `scope` and if a box was left unticked, SAY so on screen and offer to retry.
2. Delete timing on real Gmail (one fresh connection per delete, as the old code
   did): TLS 0.3 s, XOAUTH2 login 1.5 s, `LIST "" "*"` 5.2 s (only 10 labels!),
   SELECT 0.8–2.8 s, subject FETCH ~1 s, then MOVE, LOGOUT, then the QML reloaded
   the whole folder. ≈10 s with nothing changing on screen = the "hang". A second
   delete during that was dropped ("Still moving…").
   Fix direction: remove the row immediately (optimistic), one persistent
   connection, cache SPECIAL-USE folder names, no openFolder() reload.
3. Gmail capabilities: MOVE supported. SPECIAL-USE: "[Gmail]/All Mail" \All,
   "[Gmail]/Spam" \Junk, "[Gmail]/Trash" \Trash. Spam had 23 letters; some spam
   subjects are RFC 2047 UTF-8 made entirely of mathematical-bold letters
   (e.g. =?UTF-8?B?8J2Xl...), which the old ASCII-only subject check reduces to "".
   UPDATE 2026-10-04 — operator, stated directly: **the Google Calendar API is
   enabled on the project** (he enabled it himself). Keep enablement and scope
   distinct when diagnosing: `API not enabled` / `access_not_configured` is a
   console setting; `ACCESS_TOKEN_SCOPE_INSUFFICIENT` means the *token* lacks the
   calendar scope because that consent tick-box was left unticked. So the console
   half of this is now answered, and the only open question on this point is
   whether the consent flow will actually grant the calendar scope — settled only
   with the operator signed in at the screen.

4. Operator report: "spam does not delete at all". 2026-09-26 11:47: operator
   re-tested with the ORIGINAL Hummingbird → Spam delete WORKS. So the failure was
   the 09-25 batch's code, not the engine. (Old note:) Cause NOT found. First step:
   now that the original Hummingbird is back, ask the operator to delete one Spam
   letter and read the exact status/toast text — that tells you whether it's the
   engine itself or was last night's code.
5. Operator report: "it is really slow now" — that is LaPivot, not Hummingbird:
   the orrery (SpacePanel.qml spaceCanvas, FrameAnimation → requestPaint ~30 fps,
   Earth-glass coastlines from the 09-25 13:35 batch) holds ~50–60% CPU in the
   QQuickCanvas thread. Fix must keep the look/motion identical (no animation
   changes rule) — e.g. pre-render the static coastline glass once, blit it.

## Known facts about Hummingbird (from the installed binary; source is gone)
See memory ncde-hb-google-link-20260925 for the full list: engine
/usr/local/bin/hummingbird-courier, OAuth scope mail-only, delete =
COPY+STORE+EXPUNGE (lands in Archive), markRead local-only, no RFC 2047 decoder,
messages oldest-first, loadOlder never called from QML, saveOAuthAccount(name,
email, access, refresh, expiresIn) exists. Folder ids: inbox starred sent drafts
archive spam trash. Message ids end in "-<UID>".
Do NOT retry (blocked before): extracting the OAuth client secret into files,
reading the engine's tokens in accounts.json, keyring attribute exploration.

## Operator's goals (unchanged)
Address Book = Gmail contacts; LeapFrog Ledger ↔ Google Calendar; delete works in
every folder (incl. Spam) and feels instant; "open it and everything just works"
on every laptop the master reaches.

## Master
Rule: every change → update + sha256-verify ALL copies: USB NCDE-Installer/
(ncde-full-patch-20260711.sh + DOUBLE-CLICK-TO-INSTALL.sh — also a full copy! +
full-patch-20260711/), USB my-project/files/ (script + full-patch-20260711/), USB
my-project/files/NCDE-Installer/ (same three), the embedded base64 tar.gz after
__NCDE_PATCH_ARCHIVE_BELOW__ (extract and diff -r against the src tree), and
/usr/local/share/ncde-fix/ via the operator's sudo cp.
