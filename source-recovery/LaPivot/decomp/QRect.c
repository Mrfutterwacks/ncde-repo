// Ghidra decompile of LaPivot.oracle — class/namespace QRect (2 functions). Raw; not source.

// ==== 00156b38  QRect::width

/* QRect::width() const */

void __thiscall QRect::width(QRect *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  undefined4 local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar1 = QtPrivate::QCheckedIntegers::operator-(*(undefined4 *)(this + 8),*(undefined4 *)this);
  local_14 = QtPrivate::QCheckedIntegers::operator+(uVar1,1);
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)&local_14);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00156b9a  QRect::height

/* QRect::height() const */

void __thiscall QRect::height(QRect *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  undefined4 local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar1 = QtPrivate::QCheckedIntegers::operator-
                    (*(undefined4 *)(this + 0xc),*(undefined4 *)(this + 4));
  local_14 = QtPrivate::QCheckedIntegers::operator+(uVar1,1);
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)&local_14);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


