#include "Lelan.h"
void dumpMeta(const QMetaObject *);
int main(){ dumpMeta(&Lelan::staticMetaObject); }
