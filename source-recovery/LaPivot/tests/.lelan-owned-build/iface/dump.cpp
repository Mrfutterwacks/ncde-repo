// metadump — LD_PRELOAD into a Qt binary; before its main() runs, ask Qt itself to describe
// every class's staticMetaObject (methods, signals, slots, properties, enums), print it as
// C++-ish declarations, and exit. Nothing of the host program executes.
//
// Symbol offsets come from `nm` (tools/metaobjects.txt: "<hex offset> <mangled symbol>"),
// relocated by the executable's load base. Usage:
//   LD_PRELOAD=./metadump.so METADUMP_LIST=metaobjects.txt ./LaPivot.oracle > interfaces.txt
#include <QtCore/QMetaObject>
#include <QtCore/QMetaMethod>
#include <QtCore/QMetaProperty>
#include <QtCore/QMetaEnum>
#include <cstdio>
#include <cstdlib>
#include <cxxabi.h>
#include <link.h>
#include <fstream>
#include <string>

static uintptr_t exeBase()
{
    uintptr_t base = 0;
    dl_iterate_phdr([](dl_phdr_info *i, size_t, void *d) {
        *static_cast<uintptr_t *>(d) = i->dlpi_addr;   // first entry = the executable
        return 1;
    }, &base);
    return base;
}

static const char *access(QMetaMethod::Access a)
{
    return a == QMetaMethod::Private ? "private" : a == QMetaMethod::Protected ? "protected" : "public";
}

void dumpMeta(const QMetaObject *mo)
{
    std::printf("class %s", mo->className());
    if (mo->superClass()) std::printf(" : public %s", mo->superClass()->className());
    std::printf("\n{\n    Q_OBJECT\n");
    for (int i = 0; i < mo->classInfoCount(); ++i) {
        auto ci = mo->classInfo(i);
        if (i >= mo->classInfoOffset())
            std::printf("    Q_CLASSINFO(\"%s\", \"%s\")\n", ci.name(), ci.value());
    }
    for (int i = mo->enumeratorOffset(); i < mo->enumeratorCount(); ++i) {
        QMetaEnum e = mo->enumerator(i);
        std::printf("    enum %s%s {", e.isScoped() ? "class " : "", e.enumName());
        for (int k = 0; k < e.keyCount(); ++k) std::printf(" %s = %d,", e.key(k), e.value(k));
        std::printf(" };  %s\n", e.isFlag() ? "// Q_FLAG" : "// Q_ENUM");
    }
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        QMetaProperty p = mo->property(i);
        std::printf("    Q_PROPERTY(%s %s READ ?%s%s%s%s)\n", p.typeName(), p.name(),
                    p.isWritable() ? " WRITE ?" : "",
                    p.hasNotifySignal() ? (" NOTIFY " + std::string(p.notifySignal().name().constData())).c_str() : "",
                    p.isConstant() ? " CONSTANT" : "", p.isFinal() ? " FINAL" : "");
    }
    for (int i = mo->constructorCount() - 1; i >= 0; --i)
        std::printf("    Q_INVOKABLE %s;   // constructor\n", mo->constructor(i).methodSignature().constData());
    const char *kinds[] = {"Q_INVOKABLE", "signal:", "slot:", "constructor"};
    for (int i = mo->methodOffset(); i < mo->methodCount(); ++i) {
        QMetaMethod m = mo->method(i);
        std::string params;
        auto names = m.parameterNames();
        for (int k = 0; k < m.parameterCount(); ++k) {
            if (k) params += ", ";
            params += m.parameterTypeName(k).constData();
            if (k < names.size() && !names[k].isEmpty()) { params += " "; params += names[k].constData(); }
        }
        std::printf("    %-11s %s %s %s(%s);\n", kinds[m.methodType()], access(m.access()),
                    m.typeName(), m.name().constData(), params.c_str());
    }
    std::printf("};\n\n");
}

void runUnused()
{
    const char *list = std::getenv("METADUMP_LIST");
    if (!list) return;                       // not asked — behave as a no-op preload
    uintptr_t base = exeBase();
    std::ifstream in(list);
    std::string off, sym;
    while (in >> off >> sym)
        dumpMeta(reinterpret_cast<const QMetaObject *>(base + std::stoull(off, nullptr, 16)));
    std::fflush(stdout);
    std::_Exit(0);                           // never enter the host program
}
