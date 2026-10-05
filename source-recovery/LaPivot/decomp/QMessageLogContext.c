// Ghidra decompile of LaPivot.oracle — class/namespace QMessageLogContext (1 functions). Raw; not source.

// ==== 0015073e  QMessageLogContext::QMessageLogContext

/* QMessageLogContext::QMessageLogContext(char const*, int, char const*, char const*) */

void __thiscall
QMessageLogContext::QMessageLogContext
          (QMessageLogContext *this,char *param_1,int param_2,char *param_3,char *param_4)

{
  *(undefined4 *)this = 2;
  *(int *)(this + 4) = param_2;
  *(char **)(this + 8) = param_1;
  *(char **)(this + 0x10) = param_3;
  *(char **)(this + 0x18) = param_4;
  return;
}


