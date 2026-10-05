# art — panel frames (panel.png 9-slice) + NCDE-Expose Mucha backdrop

Status: IN PROGRESS (started 2026-09-30 relaunch). Updated incrementally.

## Log
- Read AGENT-BRIEF, art.txt, preamble, README work items. No surviving files from the first launch.
- Coordinator note: Expose art = operator's muchaexpose.png (1920x1073, alpha 143 everywhere); padded 1200 version = same pixels centred y=63.

## 2026-10-01 (third launch) — log
- Re-read preamble, art.txt, AGENT-BRIEF, README work items, AESTHETIC-NOTE, no-overlap memory. No files of mine changed since 2026-09-30 18:50 (canonical TopPanel/BottomPanel/Dock/main/NCDEExpose = live, md5-identical).
- Finding: top-ornament.png / bottom-ornament.png are NOT referenced by any QML (canonical or live). The panels' current ornaments are the "this" bands (this-rail-tile.png + this-center.png medallion, flush outside each panel) + pennant.png under the top medallion. A frame around each panel occupies exactly where those bands sit (flush against the panel edge) -> they must go (they would intersect the frame's rails/caps).
- panel.png measured (2172x724, alpha bbox y 25..723): straight double rails at mid column: top rail opaque rows 131..183, bottom rail rows 534..577 -> rail opening rows 184..533 = 350 px. Straight (column-invariant) section x 600..1567 (column diff < 1500 vs centre). Inner C of each cap: apex x 257 (left) / 1912 (right) at y ~355; scroll volutes intrude into the rail band near the junctions. Opening contains 9191 stray pixels of alpha 1 (invisible).

### 2026-10-01 pass 2 — panel.png re-measured properly (earlier numbers came from a mis-indexed row scan; THESE are verified)
Source 2172x724 RGBA, pending-art/panel.png.
- alpha>=8 ink bbox: **x 3..2169, y 56..667** (2167 x 612). 56 transparent rows top AND bottom (alpha>0 bbox y 25..723 = faint halo only).
- Straight (column-invariant) rails: **x 599..1568** (diff<=8 vs mid column), 974 px wide.
- Mid column x=1086 opaque runs: top rail **y 129..185 (57 px)**, bottom rail **y 531..579 (49 px)**.
- **INNER CLEAR ZONE = x 258..1911, y 186..531** (1654 x 346). At the caps' widest inward point (y~355) the left cap ink ends at x=257 and the right cap ink starts at x=1912.
- Cap blocks: left x 3..~597, right ~1570..2169 (each ~600 x 611, near-square C-shapes opening inboard).
- Ink above the opening = rows 56..185 (130 px; cap crowns 56..128); ink below = rows 532..667 (136 px; cap tails 580..667).
- Stray alpha 1..7 pixels inside the opening: 20335 (invisible; I zero them in the pre-scaled asset).
- NOTE: this model has NO image input — I cannot eyeball PNGs myself. Every visual claim below is from pixel measurement only; the operator must eyeball the previews.

### 2026-10-01 — implementation and sandbox renders
- Canonical payload edited only under `files/full-patch-20260711/src/usr/share/ncde/`. Created `.prebak-20260930-art` backups before edits to `TopPanel.qml`, `BottomPanel.qml`, `NCDEExpose.qml`, `main.qml`, and `ExposeBackdrop.qml`.
- Added `panel-frame.png` beside the panel QML: 216x72 RGBA, prepared from `pending-art/panel.png` using the measured 60 px end caps and 19 px top/bottom 9-slice borders. Only alpha below 8 in the measured clear opening was removed before resampling. The rendered frame bounds are x=0..1919, y=0..71 at top and y=1128..1199 at bottom. Panel content remains within x=26..1893; top content is y=20..51 and bottom content y=1148..1177. The artwork's measured clear zone scales to the same 26 px side insets; no panel content enters the frame caps or rails.
- Removed the old `this` rail/medallion bands and the top pennant from the panel QML; no such references remain in `TopPanel.qml` or `BottomPanel.qml`. The existing glass surfaces are retained. `panel-frame.png` alpha>=8 bounds are x=0..215, y=6..65.
- Added `muchaexpose-1920x1200.png` byte-for-byte from `pending-art/muchaexpose-1920x1200.png` (SHA-256 `1e4b7fe8f341a33fd345b34eb4e524b3a4fda413f555d5f13624cdd8af9172ca`; 1920x1200, alpha 143 throughout). `ExposeBackdrop.qml` displays it with `PreserveAspectCrop`; removed the former extra vignette. `NCDEExpose.qml` uses this as its bottom-most backdrop. `main.qml` has an 8 px top-edge reveal strip for the offset panel.
- `qmllint` passed for all five changed QML files. Sandbox renders used the installed LaPivot as renderer in an isolated Xvfb/bubblewrap environment, with the canonical QML mounted read-only. No QML warnings/errors appeared in the filtered logs; the deliberately absent system bus produced a DBus diagnostic.
- Previews: `~/Downloads/NCDE-PNGs/previews-20260930/panel-frames-20261001-r2.png` and `expose-mucha-20261001-r2.png`. A further 1920x1200 screenshot after moving the pointer to screen center is `panels-after-center-move-20261001.png`; both panels remained visible. This verifies the content/frame remain together in that state, but is not a drag or hidden-state test.
- Movement policy (earlier conclusion superseded): the report's `fixed_intellihide` choice contradicted the README/art spec and was unnecessary. On 2026-10-01, `TopPanel.qml` and `BottomPanel.qml` gained vertical left-button dragging while revealed; drag changes the panel's stored-in-memory y position, clamps the full 72 px frame within the parent, and leaves the existing intellihide reveal/hide animation intact. `BorderImage` and `NCDEGlassSurface` remain children of each moving panel, so frame and glass travel with it. Child clicks remain available unless pointer movement crosses the drag threshold. The position resets to the documented default when LaPivot is recreated; no persistence was requested or added.
- Before editing, made `TopPanel.qml.prebak-20261001-movable-art` and `BottomPanel.qml.prebak-20261001-movable-art` beside the canonical files. `qmllint` passed on both edited QML files. Static 1920x1200 geometry check passed: top frame y=0..71, bottom frame y=1128..1199, with 1056 px vertical clear gap between frames at rest. No sandbox render was run for this follow-up, per coordinator's serialized-verification restriction.
- Still owed to coordinator's serialized verification: sandbox-render both panels after dragging each to several vertical positions and test their hide/reveal at those positions; measure frame-to-content gaps and check frame/panel/dock clearances at default and moved positions; inspect the resulting 1920x1200 screenshots and confirm zero new QML warnings. Drag/persistence behavior has not been visually or interactively tested yet.
