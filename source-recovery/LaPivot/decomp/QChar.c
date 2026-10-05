// Ghidra decompile of LaPivot.oracle — class/namespace QChar (4 functions). Raw; not source.

// ==== 00150b7a  QChar::unicode

/* QChar::unicode() */

QChar * __thiscall QChar::unicode(QChar *this)

{
  return this;
}



// ==== 001a3ee6  QChar::QChar<char16_t,true>

/* QChar::QChar<char16_t, true>(char16_t) */

void __thiscall QChar::QChar<char16_t,true>(QChar *this,wchar16 param_1)

{
  *(wchar16 *)this = param_1;
  return;
}



// ==== 001a3f00  QChar::QChar<QLatin1Char,true>

/* QChar::QChar<QLatin1Char, true>(QLatin1Char) */

void __thiscall QChar::QChar<QLatin1Char,true>(QChar *this,QLatin1Char param_2)

{
  wchar16 wVar1;
  QLatin1Char local_11;
  QChar *local_10;
  
  local_11 = param_2;
  local_10 = this;
  wVar1 = QLatin1Char::operator_cast_to_char16_t(&local_11);
  *(wchar16 *)local_10 = wVar1;
  return;
}



// ==== 001a76fa  QChar::QChar<char,true>

/* QChar::QChar<char, true>(char) */

void __thiscall QChar::QChar<char,true>(QChar *this,char param_1)

{
  *(ushort *)this = (ushort)(byte)param_1;
  return;
}


