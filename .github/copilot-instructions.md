# NCDE must never go stale

## What NCDE is and where truth lives

NCDE is the operator's custom Arch Linux desktop environment: the LaPivot shell,
its Qt Quick/QML interface, house applications, and supporting services and
helpers. For the behavior that must ship, the operator's currently running NCDE
machine is the source of truth. Old notes, backups, build snapshots, and an
older GitHub package are evidence only; none override what is actually running.

## Product direction: make NCDE the best NCDE

The goal is not to turn NCDE into a generic operating system or desktop
environment. Make NCDE the best daily driver it can be by understanding and
building on what it already does. For substantial product or polish work,
inventory the relevant NCDE capabilities and workflows, research how other
Linux distributions solve the same problems, then combine the best-fitting
ideas with the operator's imagination. Borrow useful solutions, not another
distribution's identity: preserve NCDE's character, working behavior, and
distinctive visual language, and extend them deliberately.

Before changing NCDE, inspect the live machine directly. Read the relevant
deployed files (especially `/usr/share/ncde`, plus related helpers, services,
configuration, and `/usr/local/bin/LaPivot`), check installed package/version
and hooks with `pacman -Qi ncde` and `pacman -Ql ncde`, and use hashes or byte
comparisons to establish whether project, embedded, and installed copies agree.
For runtime questions, inspect current process/service state and logs rather
than trusting timestamps or old status notes. If live behavior is ahead of the
project or GitHub package, the project/release is stale and must be reconciled
before the task is called complete.

## Non-negotiable requirement

The GitHub Arch repository exists so that `sudo pacman -Syu` makes every NCDE
machine behave and look like the operator's live NCDE system. The repository,
the self-extracting patch, the versioned `ncde` package, and the published
GitHub pacman database must never omit an intentional live update. **No
exceptions:** an NCDE change is unfinished until it is folded into the project
and delivered through a newer package in the GitHub repository.

This applies to all shipped behavior: QML and JavaScript, weather and seasonal
orrery effects, C++ and Python, binaries, fonts, images, configuration,
services, hooks, app launchers, and helper data. Never assume an update is
covered merely because it works on the operator's computer or exists in one
copy of a script.

## Canonical sources and delivery

- Canonical patch: `files/ncde-full-patch-20260711.sh`.
- Canonical staged tree: `files/full-patch-20260711/`.
- The full patch's embedded archive must contain **all three** top-level
  payloads: `full-patch-20260711/`, `ncde-live-patch-20260711.sh`, and
  `vesper-patch-20260711/`. The full patch explicitly expects the latter two;
  omitting them makes standalone/pacman application skip the Vesper component.
- Installer copies under `NCDE-Installer/` are mirrors. The project script is
  the source of truth; never publish a mirror as canonical.
- `NCDE-Installer/packaging/publish.sh` builds a newer `ncde` package, updates
  and signs the Arch repository database, and uploads the package/repository
  assets to GitHub. The package's post-transaction hook applies its embedded
  patch after pacman releases its lock.

`pacman -Syu` cannot deliver a change if the package version and published
repository metadata do not advance. A local script edit, a rebuilt package
that was not uploaded, or a GitHub source edit without the new package/database
does not update other machines.

## Required fold-in and self-extractor procedure

For every live change:

1. Reconcile the intended live behavior with the canonical project tree. Fold
   all related files into the project and patch; never leave part of a
   multi-file change live-only.
2. Rebuild the self-extracting archive from the canonical project payloads.
   `docs/OPEN-ITEMS.md` records the three inputs and tar/base64 splice;
   `files/ncde-batches-20260925/ncde-earth-glass-20260925/FOLD-ME.md` also
   requires excluding backup and Python-cache artifacts. Use a NUL-safe file
   list so those exclusions cannot omit legitimate filenames:

   ```sh
   cd files
   find full-patch-20260711 ncde-live-patch-20260711.sh vesper-patch-20260711 \
     \( -type d -name '__pycache__' -prune \) -o \
     \( -type f \( -name '*.pyc' -o -name '*prebak*' -o -name '*.reverted-*' \) -prune \) -o \
     -type f -print0 > /tmp/ncde-payload-files
   tar --null -T /tmp/ncde-payload-files -czf /tmp/ncde-payload.tar.gz
   base64 /tmp/ncde-payload.tar.gz > /tmp/ncde-payload.b64
   ```

   Replace everything after the **standalone marker line**
   `__NCDE_PATCH_ARCHIVE_BELOW__` in the canonical script with the complete
   base64 output. Locate the exact line, not an earlier comment that mentions
   the marker. Do not append a second archive to an old blob, and do not omit
   companion payloads. Preserve the executable header.
3. Round-trip the embedded data: decode and extract it to a temporary
   directory; compare the full-patch tree, live-patch runner, and Vesper tree
   with their canonical project sources. Run `bash -n` on the script and
   confirm the archive has all three expected roots.
4. Run `NCDE-Installer/packaging/publish.sh --check`. It must pass its staged
   tree, embedded archive, live UI, and transformed LaPivot parity checks.
   Never bypass a failed check to publish.
5. Run `NCDE-Installer/packaging/publish.sh` to bump the package version,
   rebuild/sign the package, regenerate/sign repository metadata, synchronize
   installer mirrors, and publish the release. Verify the new `ncde` package,
   signatures, and database are present in the GitHub `x86_64` release.
6. Verify an NCDE machine upgrades to that version through `pacman -Syu`, its
   post-transaction apply succeeds, and the changed live files match the
   released payload. Do not call the update complete before this release path
   is verified.

Keep active script mirrors synchronized; historical batch snapshots remain
historical and must not be mistaken for the current release source. Never copy
credentials or machine-specific secrets into a public package. Preserve their
behavior through safe generic defaults or documented local configuration.

## Verified audit — 2026-09-27

The prior `ncde-2026.09.27.0043-1` package was missing
`ncde-live-patch-20260711.sh` and `vesper-patch-20260711/` from its embedded
archive, although the full-patch script expects both. The resulting standalone
apply skipped Vesper. The archive was rebuilt with all three payload roots
(423 active files), and the publisher now rejects incomplete or stale payloads.

Version `ncde-2026.09.27.1042-1` is published in the GitHub `x86_64` release;
the remote package digest was verified against the signed local package.
`SpacePanel.qml` and `mucha-weather-window.js` carry the running seasonal
orrery/weather behavior, and all 308 active `/usr/share/ncde` files matched the
embedded UI tree during the release preflight. The live LaPivot binary is
intentionally palette-patched; applying the two embedded palette transforms
reproduced its live SHA-256 exactly.

The operator's current machine was still on package version
`2026.09.27.0043-1` at the time of the audit. Do not claim that machine has
updated until its own pacman transaction and post-transaction apply are
verified.
