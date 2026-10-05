#!/usr/bin/env bash
# complete_checklist.sh
# The agent runs this AFTER reading all required docs and outputting the checklist block.
# Logs completion so check_session.sh will allow further commands.

LOGFILE="$HOME/.claude/session_checklist.log"
SESSION_ID="${CLAUDE_SESSION_ID:-unknown}"
TODAY=$(date +%Y-%m-%d)
NOW=$(date '+%Y-%m-%d %H:%M:%S')

# Verify the required docs actually exist before marking complete
REQUIRED_DOCS=(
    "$HOME/my-project/docs/CLAUDE.md"
    "$HOME/my-project/docs/PROJECT.md"
    "$HOME/my-project/docs/NCDE-CALAMARES-PLAN.md"
    "$HOME/my-project/docs/ISO-BUILD-PLAN.md"
    "$HOME/my-project/docs/SESSION_HANDOFF.md"
    "$HOME/my-project/files/calamares-ncde/README.md"
)

MISSING=0
for doc in "${REQUIRED_DOCS[@]}"; do
    if [[ ! -f "$doc" ]]; then
        echo "WARNING: Required doc not found: $doc" >&2
        MISSING=$((MISSING + 1))
    fi
done

if [[ $MISSING -gt 0 ]]; then
    echo "ERROR: $MISSING required doc(s) missing. Cannot mark checklist complete." >&2
    exit 1
fi

# Log the completion
mkdir -p "$(dirname "$LOGFILE")"
echo "CHECKLIST_COMPLETE:${SESSION_ID} DATE:${TODAY} TIME:${NOW}" >> "$LOGFILE"
echo "CHECKLIST_COMPLETE:${TODAY}" >> "$LOGFILE"

echo "✓ Session checklist logged. Commands are now unblocked."
echo "  Session: ${SESSION_ID}"
echo "  Time:    ${NOW}"
