// Ghidra decompile of LaPivot.oracle — class/namespace QSize (4 functions). Raw; not source.

// ==== 00156aac  QSize::QSize

/* QSize::QSize(int, int) */

void __thiscall QSize::QSize(QSize *this,int param_1,int param_2)

{
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::QCheckedInt((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
                 *)this,param_1);
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::QCheckedInt((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
                 *)(this + 4),param_2);
  return;
}



// ==== 00156ae8  QSize::width

/* QSize::width() const */

void __thiscall QSize::width(QSize *this)

{
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)this);
  return;
}



// ==== 00156b02  QSize::height

/* QSize::height() const */

void __thiscall QSize::height(QSize *this)

{
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)(this + 4));
  return;
}



// ==== 001f822a  QSize::isValid

/* QSize::isValid() const */

undefined8 __thiscall QSize::isValid(QSize *this)

{
  bool bVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  int local_18 [2];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18[0] = 0;
  bVar1 = QtPrivate::QCheckedIntegers::operator>=(this,local_18);
  if (bVar1) {
    local_18[1] = 0;
    bVar1 = QtPrivate::QCheckedIntegers::operator>=(this + 4,local_18 + 1);
    if (bVar1) {
      uVar2 = 1;
      goto LAB_001f8291;
    }
  }
  uVar2 = 0;
LAB_001f8291:
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}


