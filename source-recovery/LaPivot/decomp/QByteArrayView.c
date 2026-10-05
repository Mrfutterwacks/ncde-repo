// Ghidra decompile of LaPivot.oracle — class/namespace QByteArrayView (16 functions). Raw; not source.

// ==== 00150f5d  QByteArrayView::lengthHelperCharArray

/* QByteArrayView::lengthHelperCharArray(char const*, unsigned long) */

long QByteArrayView::lengthHelperCharArray(char *param_1,ulong param_2)

{
  long in_FS_OFFSET;
  char *local_60;
  char *local_58;
  char *local_50;
  ulong local_48;
  ulong local_40;
  ulong local_38;
  char **local_30;
  char *local_28;
  char *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_60 = (char *)((ulong)local_60 & 0xffffffffffffff00);
  local_58 = (char *)std::char_traits<char>::find(param_1,param_2,(char *)&local_60);
  local_50 = local_58;
  if (local_58 == (char *)0x0) {
    local_30 = &local_60;
    local_60 = param_1;
    local_48 = param_2;
    local_40 = param_2;
    local_38 = param_2;
    std::__advance<char_const*,long>(&local_60,param_2);
    local_58 = local_60;
  }
  local_28 = local_58;
  local_18 = local_58;
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return (long)local_58 - (long)param_1;
  }
  local_60 = param_1;
  local_20 = param_1;
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00151030  QByteArrayView::castHelper

/* QByteArrayView::castHelper(char const*) */

char * QByteArrayView::castHelper(char *param_1)

{
  return param_1;
}



// ==== 0015103e  QByteArrayView::size

/* QByteArrayView::size() const */

undefined8 __thiscall QByteArrayView::size(QByteArrayView *this)

{
  return *(undefined8 *)this;
}



// ==== 00151050  QByteArrayView::data

/* QByteArrayView::data() const */

undefined8 __thiscall QByteArrayView::data(QByteArrayView *this)

{
  return *(undefined8 *)(this + 8);
}



// ==== 00151062  QByteArrayView::constData

/* QByteArrayView::constData() const */

void __thiscall QByteArrayView::constData(QByteArrayView *this)

{
  data(this);
  return;
}



// ==== 0015107c  QByteArrayView::indexOf

/* QByteArrayView::indexOf(char, long long) const */

void __thiscall QByteArrayView::indexOf(QByteArrayView *this,char param_1,longlong param_2)

{
  QtPrivate::findByteArray(*(QtPrivate **)this,*(undefined8 *)(this + 8),param_2,(int)param_1);
  return;
}



// ==== 001a402c  QByteArrayView::QByteArrayView<char,true>

/* QByteArrayView::QByteArrayView<char, true>(char const*, long long) */

void __thiscall
QByteArrayView::QByteArrayView<char,true>(QByteArrayView *this,char *param_1,longlong param_2)

{
  undefined8 uVar1;
  
  *(longlong *)this = param_2;
  uVar1 = castHelper(param_1);
  *(undefined8 *)(this + 8) = uVar1;
  return;
}



// ==== 001a4284  QByteArrayView::QByteArrayView<char_const*,true>

/* QByteArrayView::QByteArrayView<char const*, true>(char const* const&) */

void __thiscall
QByteArrayView::QByteArrayView<char_const*,true>(QByteArrayView *this,char **param_1)

{
  longlong lVar1;
  
  if (*param_1 == (char *)0x0) {
    lVar1 = 0;
  }
  else {
    lVar1 = QtPrivate::lengthHelperPointer<char>(*param_1);
  }
  QByteArrayView<char,true>(this,*param_1,lVar1);
  return;
}



// ==== 001a42d2  QByteArrayView::QByteArrayView<QByteArray,true>

/* QByteArrayView::QByteArrayView<QByteArray, true>(QByteArray const&) */

void __thiscall
QByteArrayView::QByteArrayView<QByteArray,true>(QByteArrayView *this,QByteArray *param_1)

{
  char *pcVar1;
  longlong lVar2;
  
  pcVar1 = (char *)QByteArray::begin(param_1);
  lVar2 = QByteArray::size(param_1);
  QByteArrayView<char,true>(this,pcVar1,lVar2);
  return;
}



// ==== 001a4f32  QByteArrayView::QByteArrayView<15ul>

/* QByteArrayView::QByteArrayView<15ul>(char const (&) [15ul]) */

void __thiscall QByteArrayView::QByteArrayView<15ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0xf);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 001a62ce  QByteArrayView::QByteArrayView<13ul>

/* QByteArrayView::QByteArrayView<13ul>(char const (&) [13ul]) */

void __thiscall QByteArrayView::QByteArrayView<13ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0xd);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 001a639e  QByteArrayView::QByteArrayView<16ul>

/* QByteArrayView::QByteArrayView<16ul>(char const (&) [16ul]) */

void __thiscall QByteArrayView::QByteArrayView<16ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0x10);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 001a646e  QByteArrayView::QByteArrayView<14ul>

/* QByteArrayView::QByteArrayView<14ul>(char const (&) [14ul]) */

void __thiscall QByteArrayView::QByteArrayView<14ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0xe);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 001a8cd0  QByteArrayView::QByteArrayView<18ul>

/* QByteArrayView::QByteArrayView<18ul>(char const (&) [18ul]) */

void __thiscall QByteArrayView::QByteArrayView<18ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0x12);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 002096f6  QByteArrayView::QByteArrayView<17ul>

/* QByteArrayView::QByteArrayView<17ul>(char const (&) [17ul]) */

void __thiscall QByteArrayView::QByteArrayView<17ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,0x11);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}



// ==== 00209a62  QByteArrayView::QByteArrayView<6ul>

/* QByteArrayView::QByteArrayView<6ul>(char const (&) [6ul]) */

void __thiscall QByteArrayView::QByteArrayView<6ul>(QByteArrayView *this,char *param_1)

{
  longlong lVar1;
  
  lVar1 = lengthHelperCharArray(param_1,6);
  QByteArrayView<char,true>(this,param_1,lVar1);
  return;
}


