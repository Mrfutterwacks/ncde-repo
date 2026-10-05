#!/bin/bash
# check-payload-agreement.sh <stage> <patch> <ncde-apply>
#
# The patch script and ncde-apply each carry their own copy of the payload rules, and nothing
# else reconciles them. The patch's gate (`is_deployable_payload "$rel" || continue`) decides
# what actually lands on a machine; ncde-apply's verification loop decides what it will demand
# to see under /etc and /usr afterwards.
#
# INVARIANT: any staged file the patch does not deploy must be in ncde-apply's exclusion list.
# If it is not, ncde-apply either reports "unapproved staged product path" or "missing or
# different deployed file" — the apply service exits 1 and every machine shows a FAILED
# notification, while pacman itself reports success and publish.sh --check stays green.
#
# 2026-10-03: this exact hole shipped as etc/polkit-1/rules.d/49-nopasswd-ncde-lock-screen.rules
# (live-ISO-only, never deployed by the patch) and failed verification on the first machine to
# run the update. Seven copies of is_deployable_payload exist across the project; this is the
# only thing that checks they still agree with the verifier.
set -u

STAGE="${1:?usage: check-payload-agreement.sh <stage> <patch> <ncde-apply>}"
PATCH="${2:?usage: check-payload-agreement.sh <stage> <patch> <ncde-apply>}"
APPLY="${3:?usage: check-payload-agreement.sh <stage> <patch> <ncde-apply>}"

for f in "$STAGE" "$PATCH" "$APPLY"; do
  [ -e "$f" ] || { echo "check-payload-agreement: missing: $f"; exit 1; }
done

# the patch's real approval gate
eval "$(awk '/^is_deployable_payload\(\) *\{/,/^\}/' "$PATCH")" || {
  echo "check-payload-agreement: could not read is_deployable_payload from $PATCH"; exit 1; }
type is_deployable_payload >/dev/null 2>&1 || {
  echo "check-payload-agreement: no is_deployable_payload in $PATCH"; exit 1; }

# ncde-apply's real exclusion case, complete from `case` to `esac`, with its `continue` rewritten
# to set a flag so it can be exercised outside ncde-apply's own loop.
EXCL="$(awk '/^        case "\$rel" in$/{f=1} f{print} f&&/^ *esac$/{exit}' "$APPLY" \
        | sed 's/continue ;;/skip=1 ;;/')"
[ -n "$EXCL" ] || { echo "check-payload-agreement: could not read the exclusion case from $APPLY"; exit 1; }

violations=0
checked=0
excluded=0
while IFS= read -r -d '' f; do
  rel="${f#"$STAGE"/}"
  skip=0
  eval "$EXCL"
  if [ "$skip" -eq 1 ]; then
    excluded=$((excluded + 1))
    continue
  fi
  checked=$((checked + 1))
  if ! is_deployable_payload "$rel"; then
    echo "  staged file the patch will never deploy, and ncde-apply will not exclude it: $rel"
    violations=$((violations + 1))
  fi
done < <(find "$STAGE/etc" "$STAGE/usr" -type f -print0 2>/dev/null)

if [ "$violations" -gt 0 ]; then
  echo "payload agreement: $violations staged file(s) would fail ncde-apply verification on every machine"
  exit 1
fi
echo "payload agreement: $checked staged files deployable, $excluded deliberately excluded, 0 that would fail verification."
exit 0
