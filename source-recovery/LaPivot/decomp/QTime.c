// Ghidra decompile of LaPivot.oracle — class/namespace QTime (2 functions). Raw; not source.

// ==== 0015430c  QTime::toString

/* QTime::toString(QString const&) const */

QString * QTime::toString(QString *param_1)

{
  long lVar1;
  QString *in_RDX;
  undefined8 in_RSI;
  long in_FS_OFFSET;
  undefined1 auVar2 [16];
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  auVar2 = qToStringViewIgnoringNull<QString,true>(in_RDX);
  QTime::toString(param_1,in_RSI,auVar2._0_8_,auVar2._8_8_);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00154368  QTime::fromString

/* QTime::fromString(QString const&, QString const&) */

void QTime::fromString(QString *param_1,QString *param_2)

{
  undefined8 uVar1;
  
  uVar1 = qToStringViewIgnoringNull<QString,true>(param_2);
  QTime::fromString(param_1,uVar1);
  return;
}


