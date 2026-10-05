#!/usr/bin/env bash
# require_search_for_uncertainty.sh
# Fires before every Bash tool call.
# If the agent's reasoning contains uncertainty phrases, block and require a web search.
#
# Claude Code passes the tool input as JSON via CLAUDE_TOOL_INPUT.
# We scan it for phrases that indicate the agent is guessing.

TOOL_INPUT="${CLAUDE_TOOL_INPUT:-}"

# Phrases that indicate the agent is guessing rather than knowing
UNCERTAINTY_PATTERNS=(
    "I think the"
    "I believe the"
    "This should work"
    "Typically this"
    "should probably"
    "might work"
    "I'm not sure but"
    "if I recall"
    "I assume"
)

for pattern in "${UNCERTAINTY_PATTERNS[@]}"; do
    if echo "$TOOL_INPUT" | grep -qi "$pattern"; then
        cat >&2 <<EOF
╔══════════════════════════════════════════════════════════════════════╗
║  BLOCKED — UNCERTAINTY DETECTED                                     ║
╠══════════════════════════════════════════════════════════════════════╣
║                                                                      ║
║  The command contains uncertainty language: "$pattern"
║                                                                      ║
║  Per CLAUDE.md Web Search Rule:                                      ║
║  You must search the web to verify the correct syntax/procedure      ║
║  before running any command you are not certain of.                  ║
║                                                                      ║
║  Do not guess. Search first. Show the source. Then act.             ║
╚══════════════════════════════════════════════════════════════════════╝
EOF
        exit 1
    fi
done

exit 0
