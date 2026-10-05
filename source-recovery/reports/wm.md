# Report: group "wm" (NCDEWindowManager, WindowTyper, ScreenInfo, NCDEWorkspace, XSettingsManager, IdleInhibitService, GliaTalkProto)

Status: IN PROGRESS (third launch, 2026-10-01 ~14:25). Updated incrementally.

## USB-tree re-verification (2026-10-01 14:25)
- Writable workspace confirmed at `/run/media/stephen/NCDE-BACKUP/my-project/source-recovery/`.
  NCDE_POSEIDON was not read or modified.
- Current owned files are `ScreenInfo.{h,cpp}`, `GliaTalk.{h,cpp}`, `WindowTyper.{h,cpp}`,
  `NCDEWorkspace.{h,cpp}`, `XSettingsManager.{h,cpp}`, `IdleInhibitService.{h,cpp}`, and
  `NCDEWindowManager.h`. `NCDEWindowManager.cpp` is absent although the interface/header and
  CMake build plan promise it; no `tests/wm_*` exist. The earlier recovery claim that all but
  ScreenInfo/GliaTalk were gone is therefore no longer accurate.
- `ScreenInfo` source contains primary-screen-follow and size-change checks as documented;
  `GliaTalk.cpp` exists. These are source inspection only, not behavior-test evidence.
- `WindowTyper`, `NCDEWorkspace`, `XSettingsManager`, and `IdleInhibitService` sources/headers are
  present, but need correctness review; the current `NCDEWorkspace` uses synchronous X property
  replies on a 1 s GUI timer. `WindowTyper`'s header claims `_NCDE_WINDOW_ROLE` while its source
  writes `_NET_WM_WINDOW_TYPE`; the oracle confirms the latter property and `dock`/`fadecurtain`
  classification.
- `XSettingsManager.cpp` currently claims selection ownership with `XCB_CURRENT_TIME` without
  polling the Qt-shared XCB event queue. The prior `.prebak-20261001-buildfix` used invalid
  `xcb_create_notify_event_t::time` and polled the queue; retain the current no-poll/current-time
  approach and remove its now-inaccurate timeout comments.
- `tests/iface_check.sh NCDEWindowManager` currently fails: public methods/signals print
  `xcb_window_t` instead of oracle `uint`, and the two declared additions are not all represented
  with oracle-exact dumped names/types. Do not treat prior interface status as verified.
- `qmllint` on current `NCDEExpose.qml` and `MotifFrame.qml` returned no diagnostics. Runtime binding
  warning status is not yet independently reproduced.
- Build constraint honored: no `compile_all.sh`, CMake, install, or live-system changes run.
- `find src tests l2-stage -newermt '2026-09-30 18:50'` shows only other groups' files otherwise.

## Interfaces dumped (python3 tools/gen_header.py)
- NCDEWindowManager: QAbstractListModel, 7 props, 12 signals, 28 Q_INVOKABLE + 1 private slot.
- WindowTyper: bare Q_OBJECT (no members) — helper of the WM.
- ScreenInfo: 2 props + changed. NCDEWorkspace: names/current + changed + activate(int).
- IdleInhibitService: org.freedesktop.ScreenSaver Inhibit/UnInhibit + private dropOwner/resetIdle.
- XSettingsManager / GliaTalkProto: NOT QObject (no moc data) — plain C++ classes.

(measurement continues below)