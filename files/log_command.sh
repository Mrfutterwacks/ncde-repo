#!/usr/bin/env bash
# log_command.sh
# Runs after every Bash tool call.
# Keeps an audit trail of every command run this session.

LOGFILE="$HOME/.claude/command_audit.log"
NOW=$(date '+%Y-%m-%d %H:%M:%S')
SESSION_ID="${CLAUDE_SESSION_ID:-unknown}"

mkdir -p "$(dirname "$LOGFILE")"

# Log the command (passed via environment by Claude Code)
echo "[$NOW] SESSION:$SESSION_ID CMD:$CLAUDE_TOOL_INPUT" >> "$LOGFILE"
