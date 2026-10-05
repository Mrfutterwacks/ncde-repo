#!/bin/bash
# decompile.sh — headless Ghidra pass over the LaPivot oracle -> decomp/<Class>.c
# Usage: bash decompile.sh     (no sudo; the Ghidra project lives next to the oracle on NCDE-BACKUP)
set -euo pipefail
R="$(cd "$(dirname "$0")/.." && pwd)"
G=/opt/ghidra/support/analyzeHeadless
export JAVA_HOME=/usr/lib/jvm/java-21-openjdk PATH=/usr/lib/jvm/java-21-openjdk/bin:$PATH
[ -x "$G" ] || { echo "Ghidra not installed: $G"; exit 1; }
mkdir -p "$R/ghidra-proj" "$R/decomp"
nice -n 19 "$G" "$R/ghidra-proj" LaPivot \
  -import "$R/oracle/LaPivot.oracle" -overwrite \
  -scriptPath "$R/tools" -preScript PreNoReturnOff.java \
  -postScript ExportByClass.java "$R/decomp" \
  -analysisTimeoutPerFile 7200 -max-cpu 2 2>&1 | tee "$R/decomp/ghidra.log" | grep -E 'NCDE:|ERROR|Exception' || true
