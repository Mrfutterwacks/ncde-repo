// Ghidra decompile of LaPivot.oracle — class/namespace QJsonValueConstRef (2 functions). Raw; not source.

// ==== 0015e5fa  QJsonValueConstRef::operator.cast.to.QJsonValue

/* QJsonValueConstRef::operator QJsonValue() const */

QJsonValueConstRef * __thiscall
QJsonValueConstRef::operator_cast_to_QJsonValue(QJsonValueConstRef *this)

{
  long lVar1;
  undefined8 *in_RSI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  ::QJsonValueConstRef::concrete(this,*in_RSI,in_RSI[1]);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0015e650  QJsonValueConstRef::QJsonValueConstRef

/* QJsonValueConstRef::QJsonValueConstRef(QJsonArray*, long long) */

void __thiscall
QJsonValueConstRef::QJsonValueConstRef
          (QJsonValueConstRef *this,QJsonArray *param_1,longlong param_2)

{
  *(QJsonArray **)this = param_1;
  this[8] = (QJsonValueConstRef)((byte)this[8] & 0xfe);
  *(ulong *)(this + 8) = (ulong)((uint)*(undefined8 *)(this + 8) & 1) | param_2 * 2;
  return;
}


