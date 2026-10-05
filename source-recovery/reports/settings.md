# Report — group "settings" (Settings + IdleIoScope)

Launch 4 (2026-10-01 12:25). Previous sessions' survivors re-verified from scratch (see each section).

## 1. Starting state, measured 12:25-12:35

### Symbol coverage (measured, not claimed)
Method: `tests/compile_all.sh`-style fresh compile of src/Settings*.cpp + src/IdlePolicy.cpp + moc(Settings.h)
into /tmp/opencode/symwork, `nm --defined-only` vs `nm --undefined-only`.

- decomp/Settings.c: **132** distinct `Settings::` names (128 methods + 4 moc symbols).
- Oracle `nm -C`: 136 names = the same 132 minus... (difference is exactly the 4 moc data symbols
  `qt_staticMetaObjectContent/RelocatingContent/StaticContent/staticMetaObject`, which moc emits).
- Rebuilt sources define: **0 missing** (`comm -23 undefined defined` = 0 lines) and
  **0 extra trap stubs** — every one of the 131 real decomp names is defined by the rebuilt sources
  (the one leftover entry in the diff is the empty match `Settings::` from a decomp regex artefact).
- **src/IdleIoScope.h/.cpp did not exist at all** (only a private copy inside src/Lelan_zen.cpp, which is
  the lelan group's file). Rebuilt here as its own class — see section 2.

### Existing sources re-checked (Sep-30 18:54 / 21:29 files from the dead runs)
Compiled clean: Settings_core, Settings_display, Settings_fonts, Settings_input, Settings_misc, Settings,
Settings_power, Settings_prefs, Settings_props, Settings_theme, IdlePolicy — **all 11 units, 0 warnings**
with `-Wall -Wextra -Wno-unused-parameter` (errors in /tmp/opencode/symwork/*.err: none).
