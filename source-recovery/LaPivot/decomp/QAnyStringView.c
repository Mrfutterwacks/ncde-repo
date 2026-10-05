// Ghidra decompile of LaPivot.oracle — class/namespace QAnyStringView (10 functions). Raw; not source.

// ==== 00151aae  QAnyStringView::QAnyStringView

/* QAnyStringView::QAnyStringView(QStringView) */

void __thiscall
QAnyStringView::QAnyStringView(QAnyStringView *this,undefined8 param_2,undefined8 param_3)

{
  longlong lVar1;
  QChar *pQVar2;
  undefined8 local_38;
  undefined8 local_30;
  QAnyStringView *local_20;
  
  local_38 = param_2;
  local_30 = param_3;
  local_20 = this;
  lVar1 = QtPrivate::lengthHelperContainer<QStringView>((QStringView *)&local_38);
  pQVar2 = (QChar *)QStringView::data((QStringView *)&local_38);
  QAnyStringView<QChar,true>(local_20,pQVar2,lVar1);
  return;
}



// ==== 0015271a  QAnyStringView::QAnyStringView

/* QAnyStringView::QAnyStringView(QString const&) */

void __thiscall QAnyStringView::QAnyStringView(QAnyStringView *this,QString *param_1)

{
  QChar *pQVar1;
  longlong lVar2;
  
  pQVar1 = (QChar *)QString::begin(param_1);
  lVar2 = QString::size(param_1);
  QAnyStringView<QChar,true>(this,pQVar1,lVar2);
  return;
}



// ==== 001a450e  QAnyStringView::QAnyStringView<QChar,true>

/* QAnyStringView::QAnyStringView<QChar, true>(QChar const*, long long) */

void __thiscall
QAnyStringView::QAnyStringView<QChar,true>(QAnyStringView *this,QChar *param_1,longlong param_2)

{
  ulong uVar1;
  
  *(QChar **)this = param_1;
  uVar1 = encodeType<QChar>(param_1,param_2);
  *(ulong *)(this + 8) = uVar1;
  return;
}



// ==== 001a47e0  QAnyStringView::QAnyStringView<char_const*,true>

/* QAnyStringView::QAnyStringView<char const*, true>(char const* const&) */

void __thiscall
QAnyStringView::QAnyStringView<char_const*,true>(QAnyStringView *this,char **param_1)

{
  char *pcVar1;
  longlong lVar2;
  
  pcVar1 = *param_1;
  if (*param_1 == (char *)0x0) {
    lVar2 = 0;
  }
  else {
    lVar2 = lengthHelperPointer<char>(*param_1);
  }
  QAnyStringView<char,true>(this,pcVar1,lVar2);
  return;
}



// ==== 001a4888  QAnyStringView::QAnyStringView<char,true>

/* QAnyStringView::QAnyStringView<char, true>(char const*, long long) */

void __thiscall
QAnyStringView::QAnyStringView<char,true>(QAnyStringView *this,char *param_1,longlong param_2)

{
  ulong uVar1;
  
  *(char **)this = param_1;
  uVar1 = encodeType<char>(param_1,param_2);
  *(ulong *)(this + 8) = uVar1;
  return;
}



// ==== 001ae9a2  QAnyStringView::encodeType<QChar>

/* unsigned long QAnyStringView::encodeType<QChar>(QChar const*, long long) */

ulong QAnyStringView::encodeType<QChar>(QChar *param_1,longlong param_2)

{
  bool bVar1;
  
  bVar1 = isAsciiOnlyCharsAtCompileTime<QChar_const>(param_1,param_2);
  return (ulong)bVar1 << 0x3e | param_2 | 0x8000000000000000;
}



// ==== 001aeb2c  QAnyStringView::lengthHelperPointer<char>

/* long long QAnyStringView::lengthHelperPointer<char>(char const*) */

longlong QAnyStringView::lengthHelperPointer<char>(char *param_1)

{
  char cVar1;
  size_t sVar2;
  
  cVar1 = q20::is_constant_evaluated();
  if (cVar1 == '\0') {
    sVar2 = strlen(param_1);
  }
  else {
    sVar2 = QtPrivate::lengthHelperPointer<char>(param_1);
  }
  return sVar2;
}



// ==== 001aeb5d  QAnyStringView::encodeType<char>

/* unsigned long QAnyStringView::encodeType<char>(char const*, long long) */

ulong QAnyStringView::encodeType<char>(char *param_1,longlong param_2)

{
  bool bVar1;
  
  bVar1 = isAsciiOnlyCharsAtCompileTime<char_const>(param_1,param_2);
  return param_2 | (ulong)bVar1 << 0x3e;
}



// ==== 001b5d0c  QAnyStringView::isAsciiOnlyCharsAtCompileTime<QChar_const>

/* bool QAnyStringView::isAsciiOnlyCharsAtCompileTime<QChar const>(QChar const*, long long) */

bool QAnyStringView::isAsciiOnlyCharsAtCompileTime<QChar_const>(QChar *param_1,longlong param_2)

{
  q20::is_constant_evaluated();
  return false;
}



// ==== 001b5da6  QAnyStringView::isAsciiOnlyCharsAtCompileTime<char_const>

/* bool QAnyStringView::isAsciiOnlyCharsAtCompileTime<char const>(char const*, long long) */

bool QAnyStringView::isAsciiOnlyCharsAtCompileTime<char_const>(char *param_1,longlong param_2)

{
  char cVar1;
  bool bVar2;
  long local_10;
  
  cVar1 = q20::is_constant_evaluated();
  if (cVar1 == '\x01') {
    for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
      if (param_1[local_10] < '\0') {
        return false;
      }
    }
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}


