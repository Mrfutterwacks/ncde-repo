// Post-script: decompile every function of LaPivot's own classes, one .cpp-ish file per class
// (decomp/<Class>.c), each function headed by its address and demangled signature. Free
// functions in no namespace go to decomp/_global.c. Qt/std template instantiations are skipped.
// Also writes decomp/_noreturn.txt: any function still flagged no-return, for review.
//@category NCDE
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ExportByClass extends GhidraScript {
    static final Set<String> SKIP_ROOTS = new HashSet<>(Arrays.asList(
        "std", "QtPrivate", "QtMocHelpers", "QtMetaContainerPrivate", "QtStringBuilder",
        "QMetaTypeId", "QMetaTypeIdQObject", "QtMetaTypePrivate", "QArrayDataPointer", "QList",
        "QMap", "QHash", "QHashPrivate", "QMapData", "QSharedDataPointer", "QExplicitlySharedDataPointerV2",
        "QPodArrayOps", "QGenericArrayOps", "QMovableArrayOps", "QCommonArrayOps", "QArrayData",
        "QTypedArrayData", "__gnu_cxx", "QScopeGuard", "QMetaType", "QVariant", "QString",
        "QByteArray", "QDBusArgument", "QDBusReply", "QDBusPendingReply", "QFlags", "QPointer",
        "QSet", "QMultiHash", "QStringView", "QObject", "QMetaObject", "QtQml", "QQmlPrivate"));

    @Override public void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : "decomp";
        new File(outDir).mkdirs();
        DecompInterface ifc = new DecompInterface();
        DecompileOptions opt = new DecompileOptions();
        ifc.setOptions(opt);
        ifc.toggleCCode(true);
        ifc.toggleSyntaxTree(false);
        ifc.openProgram(currentProgram);

        Map<String, List<Function>> byClass = new TreeMap<>();
        PrintWriter nr = new PrintWriter(new FileWriter(new File(outDir, "_noreturn.txt")));
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (f.isExternal() || f.isThunk()) continue;
            if (f.hasNoReturn()) nr.println(f.getEntryPoint() + " " + f.getName(true));
            Namespace ns = f.getParentNamespace();
            List<String> path = new ArrayList<>();
            for (Namespace n = ns; n != null && !n.isGlobal(); n = n.getParentNamespace()) path.add(0, n.getName());
            String cls = path.isEmpty() ? "_global" : path.get(0);
            if (SKIP_ROOTS.contains(cls) || cls.contains("<") || cls.startsWith("_")) {
                if (!cls.equals("_global")) continue;
            }
            byClass.computeIfAbsent(cls.replaceAll("[^A-Za-z0-9_]", "_"), k -> new ArrayList<>()).add(f);
        }
        nr.close();

        int total = 0, failed = 0;
        for (Map.Entry<String, List<Function>> e : byClass.entrySet()) {
            if (monitor.isCancelled()) break;
            try (PrintWriter w = new PrintWriter(new FileWriter(new File(outDir, e.getKey() + ".c")))) {
                w.println("// Ghidra decompile of LaPivot.oracle — class/namespace " + e.getKey()
                          + " (" + e.getValue().size() + " functions). Raw; not source.");
                for (Function f : e.getValue()) {
                    total++;
                    w.println("\n// ==== " + f.getEntryPoint() + "  " + f.getName(true));
                    DecompileResults r = ifc.decompileFunction(f, 120, monitor);
                    if (r != null && r.decompileCompleted() && r.getDecompiledFunction() != null) {
                        w.println(r.getDecompiledFunction().getC());
                    } else {
                        failed++;
                        w.println("// DECOMPILE FAILED: " + (r == null ? "null" : r.getErrorMessage()));
                    }
                }
            }
            println("NCDE: " + e.getKey() + " -> " + e.getValue().size() + " functions");
        }
        println("NCDE: decompiled " + total + " functions, " + failed + " failed, " + byClass.size() + " files");
    }
}
