// Ghidra decompile of LaPivot.oracle — class/namespace QLineF (1 functions). Raw; not source.

// ==== 00289f88  QLineF::QLineF

/* QLineF::QLineF(QPointF const&, QPointF const&) */

void __thiscall QLineF::QLineF(QLineF *this,QPointF *param_1,QPointF *param_2)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_1 + 8);
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = uVar1;
  uVar1 = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(this + 0x10) = *(undefined8 *)param_2;
  *(undefined8 *)(this + 0x18) = uVar1;
  return;
}


