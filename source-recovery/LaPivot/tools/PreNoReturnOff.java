// Pre-script: Ghidra's "Non-Returning Functions - Discovered" analyzer wrongly marks
// QString::QString / ~QString as no-return in LaPivot, which cuts every function body short
// after its first QString (see docs/lapivot-rebuild.md). Turn it off before analysis runs;
// the name-based "Known" analyzer (abort, exit, __cxa_throw, ...) stays on.
//@category NCDE
import ghidra.app.script.GhidraScript;
public class PreNoReturnOff extends GhidraScript {
    @Override public void run() throws Exception {
        setAnalysisOption(currentProgram, "Non-Returning Functions - Discovered", "false");
        println("NCDE: discovered-noreturn analysis disabled");
    }
}
