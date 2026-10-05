// Ghidra decompile of LaPivot.oracle — class/namespace QFont (1 functions). Raw; not source.

// ==== 0028a1f6  QFont::setBold

/* QFont::setBold(bool) */

void __thiscall QFont::setBold(QFont *this,bool param_1)

{
  undefined8 uVar1;
  
  if (param_1) {
    uVar1 = 700;
  }
  else {
    uVar1 = 400;
  }
  QFont::setWeight(this,uVar1);
  return;
}


