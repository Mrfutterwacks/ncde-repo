#!/bin/bash
# rkhunter-scan.sh — root-side rootkit scan for Vesper (run by ncde-rkhunter.service).
# rkhunter ships root-only (mode 0700) so the unprivileged vesper-brain can neither see
# nor run it; root scans here and writes a world-readable report that
# vesper_engines.py reads. Session 86 part 2, 2026-07-09.
set -u
OUT=/var/lib/ncde-vesper
REPORT=$OUT/rkhunter-report
mkdir -p "$OUT"
chmod 755 "$OUT"
# First run on a fresh system: build the file-properties baseline first,
# otherwise --check warns on every binary it has never seen.
[ -f /var/lib/rkhunter/db/rkhunter.dat ] || /usr/bin/rkhunter --propupd --nocolors >/dev/null 2>&1
# stderr goes to its own log, NEVER the report: rkhunter 1.4.6's own grep calls
# spray hundreds of "grep: warning: stray \" lines on new GNU grep, and every
# report line becomes a Vesper finding (439 bogus "rootkit" findings, proven live).
{
  echo "# ncde-rkhunter scan $(date -u +%Y-%m-%dT%H:%M:%SZ)"
  /usr/bin/rkhunter --check --sk --rwo --nocolors 2>"$OUT/rkhunter-scan.err"
  echo "# exit=$?"
} > "$REPORT.new"
chmod 644 "$REPORT.new"
mv -f "$REPORT.new" "$REPORT"
# rkhunter exits 1 when it has warnings — those are findings for Vesper to show,
# not a unit failure.
exit 0
