// Ghidra decompile of LaPivot.oracle — class/namespace QLatin1Char (3 functions). Raw; not source.

// ==== 00150b32  QLatin1Char::QLatin1Char

/* QLatin1Char::QLatin1Char(char) */

void __thiscall QLatin1Char::QLatin1Char(QLatin1Char *this,char param_1)

{
  *this = (QLatin1Char)param_1;
  return;
}



// ==== 00150b4c  QLatin1Char::unicode

/* QLatin1Char::unicode() const */

QLatin1Char __thiscall QLatin1Char::unicode(QLatin1Char *this)

{
  return *this;
}



// ==== 00150b60  QLatin1Char::operator.cast.to.char16_t

/* QLatin1Char::operator char16_t() const */

wchar16 __thiscall QLatin1Char::operator_cast_to_char16_t(QLatin1Char *this)

{
  wchar16 wVar1;
  
  wVar1 = unicode(this);
  return wVar1;
}


