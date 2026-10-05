// Ghidra decompile of LaPivot.oracle — class/namespace QIcon (3 functions). Raw; not source.

// ==== 001f83f0  QIcon::QIcon

/* QIcon::QIcon(QIcon&&) */

void __thiscall QIcon::QIcon(QIcon *this,QIcon *param_1)

{
  QIconPrivate *pQVar1;
  long in_FS_OFFSET;
  _func_decltype_nullptr *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (_func_decltype_nullptr *)0x0;
  pQVar1 = std::exchange<QIconPrivate*,decltype(nullptr)>((QIconPrivate **)param_1,&local_18);
  *(QIconPrivate **)this = pQVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f8448  QIcon::operator=

/* QIcon::TEMPNAMEPLACEHOLDERVALUE(QIcon&&) */

QIcon * __thiscall QIcon::operator=(QIcon *this,QIcon *param_1)

{
  long in_FS_OFFSET;
  QIcon local_30 [8];
  QIcon *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_1;
  QIcon(local_30,param_1);
  swap(this,local_30);
  ::QIcon::~QIcon(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001f84c4  QIcon::swap

/* QIcon::swap(QIcon&) */

void __thiscall QIcon::swap(QIcon *this,QIcon *param_1)

{
  qt_ptr_swap<QIconPrivate>((QIconPrivate **)this,(QIconPrivate **)param_1);
  return;
}


