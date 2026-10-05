#!/usr/bin/env bash
# check_session.sh
# Runs before every Bash tool call.
# Blocks execution until the session checklist has been completed and logged.

LOGFILE="$HOME/.claude/session_checklist.log"
SESSION_ID="${CLAUDE_SESSION_ID:-unknown}"
TODAY=$(date +%Y-%m-%d)

# Check if checklist was completed this session
if grep -q "CHECKLIST_COMPLETE:${SESSION_ID}" "$LOGFILE" 2>/dev/null; then
    exit 0  # Already done — allow the command
fi

# Also accept a same-day completion if session ID isn't available
if grep -q "CHECKLIST_COMPLETE:${TODAY}" "$LOGFILE" 2>/dev/null; then
    exit 0
fi

# Checklist not done — block the command and explain exactly what is required
cat >&2 <<'EOF'
╔══════════════════════════════════════════════════════════════════════╗
║  BLOCKED — SESSION CHECKLIST NOT COMPLETE                           ║
╠══════════════════════════════════════════════════════════════════════╣
║                                                                      ║
║  You have not completed the required session start ritual.           ║
║  No bash commands may run until you have done ALL of the following:  ║
║                                                                      ║
║  1. Read ~/my-project/docs/CLAUDE.md in full                        ║
║  2. Read ~/my-project/docs/PROJECT.md in full                       ║
║  3. Read ~/my-project/docs/NCDE-CALAMARES-PLAN.md in full           ║
║  4. Read ~/my-project/docs/NCDE-INSTALL-PLAN.md in full             ║
║  5. Read ~/my-project/docs/ISO-BUILD-PLAN.md in full                ║
║  6. Read ~/my-project/docs/SESSION_HANDOFF.md in full               ║
║  7. Read ~/my-project/files/calamares-ncde/README.md in full        ║
║  8. Read the actual source files those docs reference               ║
║  9. Search the web for any procedure or syntax you are not          ║
║     certain of — do not guess, do not proceed on assumption         ║
║  10. Output the SESSION START CHECKLIST block (see CLAUDE.md)       ║
║  11. Run: ~/.claude/scripts/complete_checklist.sh                   ║
║                                                                      ║
║  Do not ask the operator for permission to do this.                  ║
║  Do it now. Then this block will clear.                              ║
╚══════════════════════════════════════════════════════════════════════╝
EOF

exit 1  # Block the command
