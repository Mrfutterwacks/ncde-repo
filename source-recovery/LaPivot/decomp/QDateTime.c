// Ghidra decompile of LaPivot.oracle — class/namespace QDateTime (1 functions). Raw; not source.

// ==== 00154477  QDateTime::fromString

/* QDateTime::fromString(QString const&, Qt::DateFormat) */

QDateTime * __thiscall QDateTime::fromString(QDateTime *this,QString *param_1,undefined4 param_3)

{
  long lVar1;
  long in_FS_OFFSET;
  undefined1 auVar2 [16];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  auVar2 = qToStringViewIgnoringNull<QString,true>(param_1);
  QDateTime::fromString(this,auVar2._0_8_,auVar2._8_8_,param_3);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}


