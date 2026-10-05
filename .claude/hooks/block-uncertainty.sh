#!/usr/bin/env bash
# block-uncertainty.sh — PreToolUse (Bash|Edit|Write)
# Reads real hook JSON from stdin (NOT an env var — that was the bug in the
# original require_search_for_uncertainty.sh, which read $CLAUDE_TOOL_INPUT,
# an env var Claude Code never sets; this is why it silently did nothing).
set -euo pipefail

INPUT=$(cat)
TEXT=$(echo "$INPUT" | jq -r '
  [.tool_input.command, .tool_input.content, .tool_input.new_string]
  | map(select(. != null))
  | join("\n")
' 2>/dev/null || echo "")

if [ -z "$TEXT" ]; then
  exit 0
fi

PATTERNS='I think the|I believe the|this should work|typically this is done|should probably|might work|I am not sure but|if I recall|I assume|presumably|most likely'

if echo "$TEXT" | grep -Eqi "$PATTERNS"; then
  MATCH=$(echo "$TEXT" | grep -Eoi "$PATTERNS" | head -n1)
  cat <<EOF
{
  "hookSpecificOutput": {
    "hookEventName": "PreToolUse",
    "permissionDecision": "ask",
    "permissionDecisionReason": "Uncertainty language detected (\"$MATCH\"). Per CLAUDE.md's Web Search Rule and No Invention Rule: search the web or ask the operator before proceeding — do not guess or write speculative framing into project files."
  }
}
EOF
  exit 0
fi

exit 0
