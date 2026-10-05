# Aesthetic Note — 2026-09-28 — Top / Bottom / Dock / Powerlines

## Rule
These panels are intended to look EXACTLY like the reference images.
If this is not exact, we fix it to be exact. No approximations ship.

## Reference images (~/Downloads)
- `Gemini_Generated_Image_6t52sg6t52sg6t52.jpeg` — top bar, bottom band, left dock
- `d18faebb-d720-469f-be05-6e8f053aef0c.jpeg` — powerline enamel arrows
- `1000042561.jpg`, `1000042562.jpg` — live silver المصري photos (secondary check)

## Live files (must match staged, md5 verified 2026-09-28)
- `/usr/share/ncde/TopPanel.qml` = `7597ff2cfd7c8bef69f2ab046ea11572`
  Full-bleed 32px dark bar, gilt hairline + came, cartouche + volutes,
  enamel menu/tray ribbons, popups z:1400 pinned open, null-guarded menu layer.
- `/usr/share/ncde/BottomPanel.qml` = `f882c419b3ddaee3f38f7f89b3b582f1`
  Full-bleed 30px band, acanthus scroll + crystal, enamel launcher/workspace
  ribbons, all launchers/tasks/workspaces kept.
- `/usr/share/ncde/Dock.qml` = `46a1d4e729d379cb9436a269da93a01b`
  Full-height dark ground, gilt volutes + ball + rivets, all 12 dock apps
  kept via settings.dockApps, live windowMgr API, screen-edge reveal.
- `/usr/share/ncde/EnamelPowerRibbon.qml` = `23daeaf2b1341e3dcdb5e5d209975ac6`
  Cobalt + crimson enamel, steel came, gold rails. Already wired in.
  FIX 2026-09-28: background Canvas takes `z:-1` so its opaque plate paints
  behind the Row content. Without it the plate covers every icon, menu,
  tray text, Leap Frog bar and workspace switcher (all four ribbons render
  as empty blue streaks).

## If the operator reports anything not exact
1. Compare live screenshot (unmaximized window, shell revealed) against the
   reference images above.
2. Fix the staged QML in `~/Projects/ncde-gemini-bytes-20260928/` until it
   matches. `qmllint` must be clean. Dock apps must stay settings-driven.
   Popups must stay z:1400 and pin the panel open.
3. Operator copies staged -> live (`sudo cp ... /usr/share/ncde/`), relogin.
4. Fold live -> `files/full-patch-20260711/src/usr/share/ncde/`, rebuild the
   embedded archive per `files/REPO-MAINTENANCE.md`, run
   `files/NCDE-Installer/packaging/publish.sh --check`, then `publish.sh`.
5. Update the md5 list above to the new verified values.

## Post-relogin check (operator logs back in)
1. Agent screenshots the live desktop (`DISPLAY=:0 import -window root`),
   crops top bar, bottom band and dock, and compares each against the
   reference images above.
2. The operator looks at the real screen. The operator's word is final:
   if anything the operator says is wrong, it is wrong, and we fix it.
   No arguing, no "cannot reproduce" — screenshot, fix the staged QML,
   `qmllint`, operator copies to live, relogin, re-screenshot, then
   refold + rebuild + `--check` + `publish`.
