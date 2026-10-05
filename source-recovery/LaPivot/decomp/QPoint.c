// Ghidra decompile of LaPivot.oracle — class/namespace QPoint (2 functions). Raw; not source.

// ==== 00156a74  QPoint::x

/* QPoint::x() const */

void __thiscall QPoint::x(QPoint *this)

{
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)this);
  return;
}



// ==== 00156a8e  QPoint::y

/* QPoint::y() const */

void __thiscall QPoint::y(QPoint *this)

{
  QtPrivate::QCheckedIntegers::
  QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
  ::value((QCheckedInt<int,QtPrivate::QCheckedIntegers::SafeCheckImpl<int>,QtPrivate::QCheckedIntegers::AssertReportPolicy>
           *)(this + 4));
  return;
}


