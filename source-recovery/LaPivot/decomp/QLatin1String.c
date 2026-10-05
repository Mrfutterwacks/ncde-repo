// Ghidra decompile of LaPivot.oracle — class/namespace QLatin1String (3 functions). Raw; not source.

// ==== 00151a5c  QLatin1String::QLatin1String

/* QLatin1String::QLatin1String(char const*) */

void __thiscall QLatin1String::QLatin1String(QLatin1String *this,char *param_1)

{
  longlong lVar1;
  
  if (param_1 == (char *)0x0) {
    lVar1 = 0;
  }
  else {
    lVar1 = QtPrivate::lengthHelperPointer<char>(param_1);
  }
  *(longlong *)this = lVar1;
  *(char **)(this + 8) = param_1;
  return;
}



// ==== 00151a9c  QLatin1String::size

/* QLatin1String::size() const */

undefined8 __thiscall QLatin1String::size(QLatin1String *this)

{
  return *(undefined8 *)this;
}



// ==== 00289cf8  QLatin1String::data

/* QLatin1String::data() const */

undefined8 __thiscall QLatin1String::data(QLatin1String *this)

{
  return *(undefined8 *)(this + 8);
}


