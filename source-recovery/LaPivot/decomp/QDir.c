// Ghidra decompile of LaPivot.oracle — class/namespace QDir (1 functions). Raw; not source.

// ==== 00154535  QDir::home

/* QDir::home() */

QDir * __thiscall QDir::home(QDir *this)

{
  long in_FS_OFFSET;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDir::homePath();
  QDir::QDir(this,local_38);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}


