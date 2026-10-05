# Calendar group — CalendarBackend, LeapFrogPond, NCDEGeo

Updated 2026-10-01 14:17 local. Work and tests were confined to the writable
NCDE-BACKUP source/payload tree and project-local scratch folders. No operator
calendar/notes, network service, real system service, or NCDE_POSEIDON was touched.
No `compile_all.sh`, CMake, installation, or commit was run.

## CalendarBackend

**Functions/files.** `CalendarBackend.cpp`, `_appointments.cpp`, `_todos.cpp`,
`_storage.cpp`, `CalendarBackend.h`, and the shared `cal_helpers.h`. There are
31 class method definitions across those translation units, including the
declared additions; `nm -C` found 38 oracle member-prefixed symbols, including
Qt metadata and compiler-generated symbols (not a 1:1 behavior-method count).
The existing 15 invokables and three properties remain unchanged.

**Warnings fixed at source.**
- Removed the duplicate static helper wrappers from the header and
  `CalendarBackend.cpp`; actual appointment/todo paths now call the single
  `ncde::cal` helpers directly (ICS escape/unescape on export/import, time
  formatting on compose, UUID generation on appointment/todo creation/import).
  `cal_backend_test.cpp` exercises those real call paths; an isolated mutation
  removing comma escaping makes `testICSIdentityRoundTrip` fail as expected.
- Removed unused `dayStart` and unused SMTP host/port/user locals. SMTP delivery
  still uses the existing `msmtp` command and configured sender/message path;
  those locals previously had no effect.
- Replaced ignored `QtConcurrent::run()` futures with `QThreadPool::start()`,
  the Qt-recommended fire-and-forget API. The desktop, ntfy, and email jobs
  remain dispatched to worker threads; no diagnostics were suppressed.

**Additional defects found by changed-path tests and fixed.**
- Save-over-existing was broken: `QFile::rename()` will not replace an existing
  target. Changed persistence to `QSaveFile::commit()`; the atomic-save test
  now writes twice and validates both appointments in the resulting JSON.
- Undo snapshots were captured after edits/deletes, so undo restored the
  changed state. Snapshot before each appointment/todo mutation; `testUndoStack`
  now verifies restoring appointments and todos.
- ICS dropped reminder lead times. Export/import now round-trip VALARM duration;
  identity test checks an actual `TRIGGER:-PT30M` and reminder value.
- Test due-reminder evidence now anchors appointments to the current local
  datetime, rather than a fixed date/time that becomes stale.

**Promise → function → test evidence.**
- Appointment/todo CRUD and undo → `upsertAppointment`/`deleteAppointment`,
  todo mutators, `pushUndo`/`undo` → `cal_backend_test`: CRUD and undo PASS.
- Shared calendar JSON persistence/reload → `configPath`/`load`/`save`/`reload`
  → `testSaveAtomic` (two writes), `testReloadAfterExternalWrite` PASS in
  scratch `HOME`/`XDG_CONFIG_HOME`.
- ICS import/export including escaping, reminder, recurrence → `exportICS`,
  `importICS` → `testExportICS`, `testImportICS`,
  `testICSIdentityRoundTrip` PASS; comma-escape mutation fails the test.
- Hummingbird hand-off → `composeForHummingbirdRec` → test asserts generated
  compose JSON/time text with an empty scratch `PATH`; no courier is run.
- Reminder calculation → `upcomingReminders`/`dueReminders` → dynamic-current-
  time `testReminderDueLogic` PASS. **QML currently calls
  `Cal.upcomingReminders(...)` in `CalReminders.qml`, not this C++ method; the
  implementation is not yet a unified QML/daemon rule.**

**Test result:** `CalBackendTest` — `Totals: 20 passed, 0 failed, 0 skipped,
0 blacklisted`. Interface check: `CalendarBackend: ORACLE INTERFACE PRESERVED
(3 props, 2 signals, 0 slots, 15 invokables) + 6 declared addition(s)`.

## LeapFrogPond

**Functions/files.** `LeapFrogPond.cpp`, `LeapFrogPond.h`; 20 class method
definitions in the implementation. Oracle `nm -C` yielded 27 member-prefixed
symbols including metadata/signals/generated symbols. No QML files changed.

**Promise → function → test evidence.**
- Notes and notice persist/reload → `addNote`, `removeNote`, `setNotice`,
  `loadNotes`, `saveNotes`, `reload` → `testAddNote` checks persisted JSON,
  plus add/remove/notice/reload tests PASS. `QSaveFile` provides atomic
  replacement for repeated saves.
- CSV export handles RFC 4180 comma/quote fields → `exportCsv`/`csvQuote` →
  `testExportCsvQuoting` PASS.
- `.lilypad` contains notes, notice, and appointments → `exportLilyPad` →
  `testExportLilyPad` PASS.
- Appointments can be archived while recurring/future entries remain →
  `archivePast` → `testArchivePast` PASS.
- Pond tally keys match the QML consumer → `tally` → `testTallyKeys` PASS.

Test result: `CalPondTest` — `Totals: 15 passed, 0 failed, 0 skipped,
0 blacklisted`. Interface check: `LeapFrogPond: ORACLE INTERFACE PRESERVED
(4 props, 5 signals, 0 slots, 11 invokables) + 2 declared addition(s)`.

## NCDEGeo

**Functions/files.** `NCDEGeo.cpp`, `NCDEGeo.h`; 18 class method definitions.
Oracle `nm -C` yielded 15 member-prefixed symbols; the source also has the
declared source/hour-format support methods.

**Promise → function → test evidence.**
- Location/place/locating façade → `latitude`, `longitude`, `place`, `locating`
  → `testSourceProperties` PASS.
- IANA zone vs localized display name and DST-correct offset → `zone`,
  `tzName`, `offset` → `testIanaZoneAndDstOffset` checks Chicago summer UTC−5
  and winter UTC−6 PASS.
- Invalid timezone falls back to system-local offset (or UTC) →
  `offset` → `testInvalidZoneUsesLocalOffset` PASS.
- Locale/user 12/24-hour clock presentation → `setHourFormatPref`, `localTime`
  → `testHourFormatPreference` PASS.

Test result: `CalGeoTest` — `Totals: 6 passed, 0 failed, 0 skipped,
0 blacklisted`. Interface check: `NCDEGeo: ORACLE INTERFACE PRESERVED
(8 props, 1 signal, 0 slots, 0 invokables) + 1 declared addition(s)`.

## Compilation and remaining work

The owned six C++ translation units were checked with `-Wall -Wextra
-Wno-unused-parameter -Wno-sfinae-incomplete` and produced no diagnostics
(exit 0). No warning-suppression option was added. The three targeted test
builds/tests above completed serially with scratch `HOME`, `TMPDIR`, and
offscreen Qt; temporary project-local build directories were removed.

Still not demonstrated/fixed in this pass: no full rebuild/`compile_all.sh`
or CMake link (per coordinator's parallel-work restriction); no QML host render;
no validation of DST behavior in the Python reminder unit; `lastDeliveryError`
is exposed but not populated, and `dueReminders` is not the current QML path.
The payload `cal-reminders.service` remains `Type=oneshot` with no explicit
timeout; its “activating” report was not reproduced by starting systemd or a
real reminder service. Its timer/service were inspected read-only. Do not start
the service or use live calendar data as a follow-up test.
