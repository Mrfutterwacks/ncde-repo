#!/bin/bash
# Read the tool context passed on stdin by Claude Code
INPUT=$(cat)
# Parse out the prompt or argument sent to the sub-agent tool
TOOL_ARGS=$(echo "$INPUT" | grep -o '"prompt":"[^"]*"' | head -n 1)

# Screen the arguments for single file/keyword lookups to prevent token bloat
if echo "$TOOL_ARGS" | grep -Ei "launcher|xcb|find|search|where is" > /dev/null; then
    echo "ERROR: Sub-agent execution blocked by local system rail to prevent token bloat." >&2
    echo "Please use local tools (grep, find, view_file) instead of spawning a new agent." >&2
    exit 2 # Exit code 2 forces Claude to handle the error and switch to a single-agent tool
fi

exit 0
