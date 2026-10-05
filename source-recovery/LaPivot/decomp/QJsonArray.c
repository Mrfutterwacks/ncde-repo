// Ghidra decompile of LaPivot.oracle — class/namespace QJsonArray (6 functions). Raw; not source.

// ==== 00182b98  QJsonArray::const_iterator::const_iterator

/* QJsonArray::const_iterator::const_iterator(QJsonArray const*, long long) */

void __thiscall
QJsonArray::const_iterator::const_iterator
          (const_iterator *this,QJsonArray *param_1,longlong param_2)

{
  QJsonValueConstRef::QJsonValueConstRef((QJsonValueConstRef *)this,param_1,param_2);
  return;
}



// ==== 00182bc6  QJsonArray::const_iterator::operator*

/* QJsonArray::const_iterator::TEMPNAMEPLACEHOLDERVALUE() const */

undefined1  [16] __thiscall QJsonArray::const_iterator::operator*(const_iterator *this)

{
  return *(undefined1 (*) [16])this;
}



// ==== 00182bdc  QJsonArray::const_iterator::operator++

/* QJsonArray::const_iterator::TEMPNAMEPLACEHOLDERVALUE() */

const_iterator * __thiscall QJsonArray::const_iterator::operator++(const_iterator *this)

{
  *(ulong *)(this + 8) =
       (ulong)((uint)*(undefined8 *)(this + 8) & 1) | ((*(ulong *)(this + 8) >> 1) + 1) * 2;
  return this;
}



// ==== 00182c1c  QJsonArray::const_iterator::comparesEqual_helper

/* QJsonArray::const_iterator::comparesEqual_helper(QJsonArray::const_iterator const&,
   QJsonArray::const_iterator const&) */

undefined8
QJsonArray::const_iterator::comparesEqual_helper(const_iterator *param_1,const_iterator *param_2)

{
  undefined8 uVar1;
  
  if ((*(long *)param_1 == *(long *)param_2) &&
     (*(ulong *)(param_1 + 8) >> 1 == *(ulong *)(param_2 + 8) >> 1)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 00182cb4  QJsonArray::begin

/* QJsonArray::begin() const */

undefined8 __thiscall QJsonArray::begin(QJsonArray *this)

{
  long in_FS_OFFSET;
  undefined8 local_28 [3];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  const_iterator::const_iterator((const_iterator *)local_28,this,0);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28[0];
}



// ==== 00182d06  QJsonArray::end

/* QJsonArray::end() const */

undefined8 __thiscall QJsonArray::end(QJsonArray *this)

{
  longlong lVar1;
  long in_FS_OFFSET;
  undefined8 local_28 [3];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QJsonArray::size();
  const_iterator::const_iterator((const_iterator *)local_28,this,lVar1);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28[0];
}


