// Ghidra decompile of LaPivot.oracle — class/namespace renderKithWait_int_ (1 functions). Raw; not source.

// ==== 00275e82  renderKithWait(int)::{lambda(double,double)#1}::operator()

/* renderKithWait(int)::{lambda(double, double)#1}::TEMPNAMEPLACEHOLDERVALUE(double, double) const
    */

undefined1  [16] __thiscall
renderKithWait(int)::{lambda(double,double)#1}::operator()
          (_lambda_double_double__1_ *this,double param_1,double param_2)

{
  double dVar1;
  double dVar2;
  undefined1 auVar3 [16];
  long in_FS_OFFSET;
  double dVar4;
  double dVar5;
  undefined8 uStack_28;
  undefined8 uStack_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  dVar1 = **(double **)(this + 8);
  dVar4 = sin(param_2);
  dVar2 = **(double **)this;
  dVar5 = cos(param_2);
  QPointF::QPointF((QPointF *)&uStack_28,dVar5 * param_1 + dVar2,dVar4 * param_1 + dVar1);
  auVar3._8_8_ = uStack_20;
  auVar3._0_8_ = uStack_28;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return auVar3;
}


