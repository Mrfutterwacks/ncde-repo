// Ghidra decompile of LaPivot.oracle — class/namespace QCursor (3 functions). Raw; not source.

// ==== 0028a0fc  QCursor::QCursor

/* QCursor::QCursor(QCursor&&) */

void __thiscall QCursor::QCursor(QCursor *this,QCursor *param_1)

{
  QCursorData *pQVar1;
  long in_FS_OFFSET;
  _func_decltype_nullptr *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (_func_decltype_nullptr *)0x0;
  pQVar1 = std::exchange<QCursorData*,decltype(nullptr)>((QCursorData **)param_1,&local_18);
  *(QCursorData **)this = pQVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
                    /* try { // try from 0028a152 to 0038a156 has its CatchHandler @ 0028b332 */
  return;
}



// ==== 0028a154  QCursor::operator=

/* QCursor::TEMPNAMEPLACEHOLDERVALUE(QCursor&&) */

QCursor * __thiscall QCursor::operator=(QCursor *this,QCursor *param_1)

{
  long in_FS_OFFSET;
  QCursor local_30 [8];
  QCursor *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_1;
                    /* try { // try from 0028a185 to 0038a189 has its CatchHandler @ 0028b6d9 */
  QCursor(local_30,param_1);
                    /* try { // try from 0028a19e to 0038a1a2 has its CatchHandler @ 0028b349 */
  swap(this,local_30);
  ::QCursor::~QCursor(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0028a1d0  QCursor::swap

/* QCursor::swap(QCursor&) */

void __thiscall QCursor::swap(QCursor *this,QCursor *param_1)

{
  qt_ptr_swap<QCursorData>((QCursorData **)this,(QCursorData **)param_1);
  return;
}


