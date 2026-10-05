#!/usr/bin/env bash
# install_hooks.sh
# Run this once on the dev machine to install the Claude Code enforcement hooks.
# Does NOT need sudo — everything goes into ~/.claude/

set -e

echo "Installing NCDE Claude Code enforcement hooks..."

# Create directories
mkdir -p ~/.claude/scripts

# Copy scripts
cp .claude/scripts/check_session.sh    ~/.claude/scripts/
cp .claude/scripts/complete_checklist.sh ~/.claude/scripts/
cp .claude/scripts/log_command.sh      ~/.claude/scripts/
cp .claude/scripts/require_search_for_uncertainty.sh ~/.claude/scripts/

# Make scripts executable
chmod +x ~/.claude/scripts/check_session.sh
chmod +x ~/.claude/scripts/complete_checklist.sh
chmod +x ~/.claude/scripts/log_command.sh
chmod +x ~/.claude/scripts/require_search_for_uncertainty.sh

# Install settings.json (merge if one already exists)
if [[ -f ~/.claude/settings.json ]]; then
    echo "WARNING: ~/.claude/settings.json already exists."
    echo "Backing it up to ~/.claude/settings.json.bak"
    cp ~/.claude/settings.json ~/.claude/settings.json.bak
fi
cp .claude/settings.json ~/.claude/settings.json

# Create log files
touch ~/.claude/session_checklist.log
touch ~/.claude/command_audit.log

echo ""
echo "Done. Hooks installed at ~/.claude/"
echo ""
echo "How it works:"
echo "  - Every bash command is BLOCKED until the agent runs complete_checklist.sh"
echo "  - The agent can only run that after reading all required docs"
echo "  - Every command is logged to ~/.claude/command_audit.log"
echo ""
echo "To reset the checklist at the start of a new session:"
echo "  truncate -s 0 ~/.claude/session_checklist.log"
echo ""
echo "To view the command audit log:"
echo "  cat ~/.claude/command_audit.log"
