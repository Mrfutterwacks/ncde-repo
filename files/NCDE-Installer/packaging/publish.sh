#!/bin/bash
# publish.sh — ship the current NCDE patch to every NCDE machine.
#   1. update the canonical my-project/files patch from the live NCDE system
#   2. ./publish.sh
# Machines see "NCDE has updates"; NCDE Command's System Update installs it.
set -eu
cd "$(dirname "$(readlink -f "$0")")"
. ./repo.conf
PROJECT_ROOT="$PWD/../../my-project"
PROJECT_FILES="$PROJECT_ROOT/files"
PATCH="$PROJECT_FILES/ncde-full-patch-20260711.sh"
PROJECT_STAGE="$PROJECT_FILES/full-patch-20260711/src"
FIELDKIT_PATCH="$PWD/../ncde-full-patch-20260711.sh"
PROJECT_FIELDKIT_PATCH="$PROJECT_FILES/NCDE-Installer/ncde-full-patch-20260711.sh"
REPO="$PWD/repo/x86_64"
VER="$(date +%Y.%m.%d.%H%M)"
SIGN=(); [ -n "$SIGN_KEY" ] && SIGN=(--sign --key "$SIGN_KEY")
RSIGN=(); [ -n "$SIGN_KEY" ] && RSIGN=(--sign --key "$SIGN_KEY")
CHECK_ONLY=0
if [ "${1:-}" = "--check" ]; then CHECK_ONLY=1; shift; fi
[ "$#" -eq 0 ] || { echo "Usage: $0 [--check]"; exit 2; }

bash -n "$PATCH" || { echo "patch script has a syntax error — not publishing"; exit 1; }
grep -q '^__NCDE_PATCH_ARCHIVE_BELOW__$' "$PATCH" || { echo "patch script has no embedded archive — not publishing"; exit 1; }
MARKER_LINE="$(grep -an -m1 '^__NCDE_PATCH_ARCHIVE_BELOW__$' "$PATCH" | cut -d: -f1)"
# the patch updates the machine, never anyone's login name or password
ACCT_RE='(^|[;&|[:space:]`(])(chpasswd|usermod|useradd|userdel|chfn|chsh|groupmod|newusers|passwd)[[:space:]]|>+[[:space:]]*/etc/(passwd|shadow|group|gshadow)'
# (getent passwd only reads the account list — allowed). Scan executable source,
# not JSON knowledge-base text, and ignore full-line comments.
ACCOUNT_HITS="$(
  find "$PROJECT_STAGE" "$PROJECT_FILES/ncde-live-patch-20260711.sh" "$PROJECT_FILES/vesper-patch-20260711" \
    -type f \( -name '*.sh' -o -name '*.py' -o -name '*.service' -o -name '*.hook' \
      -o -name '*.desktop' -o -name '*.conf' -o -name '*.c' -o -name '*.cpp' \
      -o -name '*.h' -o -name '*.hpp' -o -name '*.qml' -o -name '*.js' \) -print0 2>/dev/null |
  while IFS= read -r -d '' file; do
    sed '/^[[:space:]]*#/d; s/getent passwd//g' "$file" |
      grep -nE "$ACCT_RE" | sed "s|^|$file:|" || true
  done
)"
if sed '/^__NCDE_PATCH_ARCHIVE_BELOW__$/q; s/getent passwd//g' "$PATCH" | grep -nE "$ACCT_RE" \
   || [ -n "$ACCOUNT_HITS" ]; then
  [ -z "$ACCOUNT_HITS" ] || printf '%s\n' "$ACCOUNT_HITS"
  echo "patch touches user accounts or passwords (lines above) — not publishing"; exit 1
fi
# 2026-09-23: enabling ncde-recovery-vt.service hijacked boot into System Restore
# and locked the owner out of their machine — it must ship disabled, always
if sed '/^__NCDE_PATCH_ARCHIVE_BELOW__$/q' "$PATCH" | grep -nE 'systemctl[^#]*[[:space:]](enable|unmask)[[:space:]][^#]*ncde-recovery-vt'; then
  echo "patch turns on ncde-recovery-vt.service (boot lockout) — not publishing"; exit 1
fi

AUDIT_DIR="$(mktemp -d /tmp/ncde-release-audit.XXXXXX)"
trap 'rm -rf "$AUDIT_DIR"' EXIT
if ! tail -n "+$((MARKER_LINE + 1))" "$PATCH" | base64 -d | tar xzf - -C "$AUDIT_DIR"; then
  echo "embedded patch archive cannot be extracted — not publishing"; exit 1
fi

is_excluded_artifact() {
  case "$1" in
    *__pycache__*|*.pyc|*prebak*|*.reverted-*|*.retired-*|*.README.md|\
    usr/share/ncde/controls/_a11y_test.qml|usr/local/bin/LaPivot|\
    usr/lib/systemd/system/ncde-apply.service|\
    usr/lib/systemd/user/ncde-update-check.service|\
    usr/lib/systemd/user/ncde-update-check.timer|\
    etc/geoclue/conf.d/90-ncde-static.conf|\
    etc/ncde/hummingbird-google-client.json|\
    home/stephen/.config/ncde-terminal/config.json|\
    usr/lib/systemd/system/mpd.service.d/00-arch.conf|\
    usr/lib/systemd/system/systemd-udevd.service.d/50-rc_keymap.conf|\
    usr/lib/systemd/system/user-.slice.d/10-defaults.conf|\
    usr/lib/systemd/system/user@.service.d/10-login-barrier.conf|\
    usr/lib/systemd/system/user@0.service.d/10-login-barrier.conf|\
    usr/lib/systemd/user/portable/profile/*/service.conf|\
    usr/lib/systemd/user/vte-spawn-.scope.d/defaults.conf|\
    usr/lib/systemd/system/mpd.service.d/00-arch.conf|\
    usr/lib/systemd/system/systemd-udevd.service.d/50-rc_keymap.conf|\
    usr/lib/systemd/system/user-.slice.d/10-defaults.conf|\
    usr/lib/systemd/system/user@.service.d/10-login-barrier.conf|\
    usr/lib/systemd/system/user@0.service.d/10-login-barrier.conf|\
    usr/lib/systemd/user/portable/profile/*/service.conf|\
    usr/lib/systemd/user/vte-spawn-.scope.d/defaults.conf|\
    usr/local/bin/hummingbird-courier.QUARANTINED-NOT-A-DROPIN-20260713|\
    usr/local/bin/hummingbird-courier.QUARANTINED-NOT-A-DROPIN-20260713|\
    usr/lib/qt6/plugins/platformthemes/libncde-qpa.so|\
    flutter-backgrounds/*|etc/skel/*)
      return 0 ;;
    *) return 1 ;;
  esac
}

is_deployable_payload() {
  case "$1" in
    etc/picom.conf|etc/pacman.d/hooks/*ncde*|etc/udev/rules.d/90-ncde-*|\
    etc/X11/xinit/xinitrc.d/*ncde*|\
    etc/X11/xorg.conf.d/10-ncde.conf|\
    etc/dbus-1/system.d/io.ncde.Sentinel.conf|\
    etc/fail2ban/jail.d/ncde-sshd.local|\
    etc/geoclue/conf.d/90-ncde-static.conf|\
    etc/ld.so.conf.d/ncde-compat.conf|\
    etc/modules-load.d/ncde-*.conf|\
    etc/pam.d/ncde-*|\
    etc/polkit-1/rules.d/*ncde*.rules|\
    etc/ncde/xsession|\
    etc/sysctl.d/99-ncde-zen.conf|\
    etc/systemd/logind.conf.d/ncde-console.conf|\
    etc/systemd/logind.conf.d/do-not-suspend.conf|\
    etc/systemd/user/ncde-*|\
    etc/ncde-release|\
    etc/skel/.config/gtk-3.0/settings.ini|etc/skel/.config/gtk-4.0/settings.ini|\
    etc/skel/.config/ncde/*|etc/skel/.config/ncde-terminal/*|\
    etc/skel/.themes/NCDE/*|etc/skel/.themes/NCDE/gtk-3.0/*|etc/skel/Pictures/wallpapers/*.png|etc/skel/.zshrc.local|\
    usr/lib/gtk-2.0/2.10.0/modules/ncde-gtk-module.so|\
    usr/lib/gtk-3.0/modules/ncde-gtk-module.so|usr/lib/ncde/*|usr/lib/qt6/qml/NCDE/*|\
    usr/lib/systemd/system/ncde-*|usr/lib/systemd/user/ncde-*|\
    usr/lib/systemd/user/vesper-*|usr/lib/systemd/user/verdant-helper*|\
    usr/lib/systemd/user/cal-reminders*|usr/bin/ncde-*|usr/local/bin/ncde-*|\
    usr/local/bin/sentinel/*|\
    usr/local/bin/LaPivot|usr/local/bin/abacus|usr/local/bin/binnie|\
    usr/local/bin/cal-reminders|usr/local/bin/dovecote-relay|\
    usr/local/bin/hummingbird-courier|usr/local/bin/xinput|\
    usr/local/bin/magpie-notify|usr/local/bin/magpie-talker|\
    usr/local/bin/orchidee|usr/local/bin/verdantfolio|usr/local/bin/verve-text|\
    usr/local/bin/verda|usr/local/bin/verdafetch|\
    usr/local/lib/ncde/*|usr/local/share/ncde-fix/ncde-hw-report.sh|\
    usr/local/share/ncde-terminal/*|\
    usr/share/applications/ncde-*.desktop|usr/share/applications/abacus.desktop|\
    usr/share/applications/binnie.desktop|usr/share/applications/cal-reminders.desktop|\
    usr/share/applications/magpie-*.desktop|usr/share/applications/orchidee.desktop|\
    usr/share/applications/verdantfolio.desktop|usr/share/applications/verve-text.desktop|\
    usr/share/fonts/ncde/*|usr/share/fonts/ncde-firamono/*|usr/share/themes/NCDE/*|\
    usr/share/ncde/*|\
    usr/share/polkit-1/actions/org.ncde.*)
      return 0 ;;
    *) return 1 ;;
  esac
}

verify_payload() {
  local source="$1" embedded="$2" label="$3" file rel count=0
  if [ -f "$source" ]; then
    [ -f "$embedded" ] && cmp -s "$source" "$embedded" \
      || { echo "$label is missing or differs in the embedded archive"; return 1; }
    echo "$label: byte-identical"
    return 0
  fi
  [ -d "$source" ] && [ -d "$embedded" ] \
    || { echo "$label is missing from the project or embedded archive"; return 1; }
  while IFS= read -r -d '' file; do
    rel="${file#"$source"/}"
    is_excluded_artifact "$rel" && continue
    [ -f "$embedded/$rel" ] \
      || { echo "$label file is absent from the embedded archive: $rel"; return 1; }
    cmp -s "$file" "$embedded/$rel" \
      || { echo "$label file differs from the embedded archive: $rel"; return 1; }
    count=$((count + 1))
  done < <(find "$source" -type f -print0)
  while IFS= read -r -d '' file; do
    rel="${file#"$embedded"/}"
    is_excluded_artifact "$rel" && continue
    [ -f "$source/$rel" ] \
      || { echo "$label archive file is absent from the project: $rel"; return 1; }
    cmp -s "$source/$rel" "$file" \
      || { echo "$label archive file differs from the project: $rel"; return 1; }
  done < <(find "$embedded" -type f -print0)
  echo "$label: $count files byte-identical"
}

verify_payload "$PROJECT_FILES/full-patch-20260711" "$AUDIT_DIR/full-patch-20260711" "Full patch"
verify_payload "$PROJECT_FILES/ncde-live-patch-20260711.sh" "$AUDIT_DIR/ncde-live-patch-20260711.sh" "Live patch runner"
verify_payload "$PROJECT_FILES/vesper-patch-20260711" "$AUDIT_DIR/vesper-patch-20260711" "Vesper payload"

[ -d /usr/share/ncde ] || { echo "live NCDE UI tree is missing; publish must be checked against the running system"; exit 1; }
ui_count=0
while IFS= read -r -d '' live; do
  rel="${live#/usr/share/ncde/}"
  is_excluded_artifact "$rel" && continue
  embedded="$AUDIT_DIR/full-patch-20260711/src/usr/share/ncde/$rel"
  [ -f "$embedded" ] || { echo "live NCDE UI file is absent from the package: $rel"; exit 1; }
  cmp -s "$live" "$embedded" || { echo "live NCDE UI file differs from the package: $rel"; exit 1; }
  ui_count=$((ui_count + 1))
done < <(find /usr/share/ncde -type f -print0)
echo "Live UI parity: $ui_count active files match; staged additions are included for older installs."

payload_count=0
while IFS= read -r -d '' staged; do
  rel="${staged#"$PROJECT_STAGE"/}"
  is_excluded_artifact "$rel" && continue
  is_deployable_payload "$rel" \
    || { echo "staged payload contains a non-NCDE or unapproved path: $rel"; exit 1; }
  payload_count=$((payload_count + 1))
done < <(find "$PROJECT_STAGE" -type f -print0)

live_payload_count=0
LIVE_ROOTS=(/etc/picom.conf /etc/pacman.d/hooks /etc/udev/rules.d \
  /etc/X11/xinit/xinitrc.d /etc/X11/xorg.conf.d/10-ncde.conf \
  /etc/dbus-1/system.d/io.ncde.Sentinel.conf \
  /etc/fail2ban/jail.d/ncde-sshd.local \
  /etc/geoclue/conf.d/90-ncde-static.conf \
  /etc/ld.so.conf.d/ncde-compat.conf \
  /etc/modules-load.d /etc/pam.d /etc/sysctl.d/99-ncde-zen.conf \
  /etc/systemd/logind.conf.d/ncde-console.conf \
  /etc/systemd/logind.conf.d/do-not-suspend.conf \
  /etc/ncde/xsession \
  /etc/systemd/user/ncde-update-check.service /etc/systemd/user/ncde-update-check.timer \
  /etc/ncde-release \
  /etc/skel /usr/lib/gtk-2.0/2.10.0/modules \
  /usr/lib/gtk-3.0/modules /usr/lib/ncde /usr/lib/qt6/qml/NCDE \
  /usr/lib/systemd/system /usr/lib/systemd/user /usr/bin/ncde-lock /usr/bin/ncde-lock-xss /usr/bin/ncde-portal /usr/bin/ncde-portal-helper /usr/bin/ncde-screensaver-notify /usr/local/bin \
  /usr/local/lib/ncde /usr/local/share/ncde-fix /usr/local/share/ncde-terminal \
  /usr/share/applications /usr/share/fonts/ncde /usr/share/fonts/ncde-firamono /usr/share/themes/NCDE \
  /usr/share/ncde /usr/share/polkit-1/actions)
for root in "${LIVE_ROOTS[@]}"; do
  [ -e "$root" ] || continue
  while IFS= read -r -d '' live; do
    rel="${live#/}"
    is_deployable_payload "$rel" || continue
    is_excluded_artifact "$rel" && continue
    embedded="$AUDIT_DIR/full-patch-20260711/src/$rel"
    [ -f "$embedded" ] || { echo "active NCDE system file is absent from the package: $rel"; exit 1; }
    cmp -s "$live" "$embedded" || { echo "active NCDE system file differs from staged payload: $rel"; exit 1; }
    live_payload_count=$((live_payload_count + 1))
  done < <(find "$root" -type f -print0)
done
echo "System payload parity: $live_payload_count live product files matched; $payload_count staged product files ready (including new-install and existing-machine additions)."

# LaPivot is built from source (2026-10-01, my-project/source-recovery/LaPivot); the Iris palettes are in the
# source, so nothing is transformed any more. The payload must carry exactly the binary that runs here, and
# never one of the old ones: 51d10a2c… (raw oracle, needed 3 Iris byte transforms) / 3507b4c6… (raw + transforms).
EMB_LP="$AUDIT_DIR/full-patch-20260711/src/usr/local/bin/LaPivot"
[ -f "$EMB_LP" ] || { echo "packaged LaPivot is missing — not publishing"; exit 1; }
case "$(sha256sum "$EMB_LP" | cut -d' ' -f1)" in
  51d10a2c97ed1c109bedf39e2be6e8e23fbcecfcb2423850cafd585323a621f1|3507b4c6addd37321c02d3e7033bd15f5a21890700c39cadb05cee4c60339371)
    echo "packaged LaPivot is an OLD pre-source-build binary — not publishing"; exit 1 ;;
esac
cmp -s "$EMB_LP" /usr/local/bin/LaPivot \
  || { echo "packaged LaPivot is not the installed source-built LaPivot — not publishing"; exit 1; }
echo "Live LaPivot parity: the packaged source-built LaPivot is the installed binary."

# 2026-10-01: Verdantfolio shipped dead (duplicate property = QML compile error). Every QML file in the
# payload that ships must compile in the real engine.
bash ./qml-compile-gate.sh "$AUDIT_DIR/full-patch-20260711/src" || { echo "payload QML does not compile — not publishing"; exit 1; }

# 2026-10-03: the patch's deploy gate and ncde-apply's verification rules are SEPARATE copies of
# is_deployable_payload, and nothing else reconciles them. A staged file the patch never deploys
# but that ncde-apply does not exclude fails verification on every receiving machine — while
# this preflight stays green, because it only ever consults its own list. Hit for real by
# etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules. See check-payload-agreement.sh.
bash ./check-payload-agreement.sh "$PROJECT_STAGE" "$PATCH" ./ncde/ncde-apply \
  || { echo "patch deploy gate and ncde-apply verifier disagree — not publishing"; exit 1; }

if [ "$CHECK_ONLY" -eq 1 ]; then
  echo "Preflight passed; no package was built or published."
  exit 0
fi

# The project copy is canonical; synchronize field-kit mirrors before packaging.
for mirror in "$FIELDKIT_PATCH" "$PROJECT_FIELDKIT_PATCH"; do
  [ -d "$(dirname "$mirror")" ] || { echo "patch mirror directory is missing: $(dirname "$mirror")"; exit 1; }
  if ! cmp -s "$PATCH" "$mirror"; then
    cp -p "$PATCH" "$mirror"
    echo "synchronized patch mirror: $mirror"
  fi
done

mkdir -p "$REPO"
# ncde: the patch, versioned by publish time
cp "$PATCH" ncde/ncde-full-patch.sh
sed -i "s/^pkgver=.*/pkgver=$VER/; s/^pkgrel=.*/pkgrel=1/" ncde/PKGBUILD
(cd ncde && PKGDEST="$REPO" makepkg -f -d --cleanbuild --noconfirm "${SIGN[@]}")
rm -f ncde/ncde-full-patch.sh

# ncde-qpa: only when its version isn't in the repo yet
QV="$(. ncde-qpa/PKGBUILD; echo "$pkgver-$pkgrel")"
ls "$REPO"/ncde-qpa-"$QV"-*.pkg.tar.zst >/dev/null 2>&1 \
  || (cd ncde-qpa && PKGDEST="$REPO" makepkg -f -d --cleanbuild --noconfirm "${SIGN[@]}")

# database: newest of each package; old ncde files kept 3 deep for ncde-rollback
repo-add -R -n "${RSIGN[@]}" "$REPO/ncde.db.tar.gz" "$REPO"/ncde-"$VER"-*.pkg.tar.zst "$REPO"/ncde-qpa-"$QV"-*.pkg.tar.zst
ls -1 "$REPO"/ncde-2*.pkg.tar.zst | sort -V | head -n -3 | while read -r old; do rm -f "$old" "$old.sig"; done

# join kit (ships in the installer folder too)
FPR=""; [ -n "$SIGN_KEY" ] && { FPR="$(gpg --with-colons --fingerprint "$SIGN_KEY" | awk -F: '/^fpr/{print $10; exit}')"; gpg --export "$SIGN_KEY" > ../ncde-repo.gpg; }
sed "s|@REPO_URL@|$REPO_URL|; s|@KEY_FPR@|$FPR|" ncde-join-repo.sh > ../ncde-join-repo.sh
chmod 755 ../ncde-join-repo.sh

echo "Built NCDE $VER. Uploading..."
./upload-github.sh "$REPO"
echo "Published NCDE $VER — machines will show 'NCDE has updates' within a few hours."
