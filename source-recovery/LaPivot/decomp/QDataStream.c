// Ghidra decompile of LaPivot.oracle — class/namespace QDataStream (7 functions). Raw; not source.

// ==== 00152fb4  QDataStream::operator.cast.to.bool

/* QDataStream::operator bool() const */

bool __thiscall QDataStream::operator_cast_to_bool(QDataStream *this)

{
  int iVar1;
  
  iVar1 = status(this);
  return iVar1 == 0;
}



// ==== 0015306c  QDataStream::status

/* QDataStream::status() const */

QDataStream __thiscall QDataStream::status(QDataStream *this)

{
  return this[0x13];
}



// ==== 00153082  QDataStream::version

/* QDataStream::version() const */

undefined4 __thiscall QDataStream::version(QDataStream *this)

{
  return *(undefined4 *)(this + 0x18);
}



// ==== 00153094  QDataStream::readQSizeType

/* QDataStream::readQSizeType(QDataStream&) */

ulong QDataStream::readQSizeType(QDataStream *param_1)

{
  bool bVar1;
  int iVar2;
  long in_FS_OFFSET;
  uint local_1c;
  ulong local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  operator>>(param_1,&local_1c);
  if (local_1c == 0xffffffff) {
    local_18 = 0xffffffffffffffff;
    goto LAB_0015311a;
  }
  if (local_1c < 0xfffffffe) {
LAB_001530ec:
    bVar1 = true;
  }
  else {
    iVar2 = version(param_1);
    if (iVar2 < 0x16) goto LAB_001530ec;
    bVar1 = false;
  }
  if (bVar1) {
    local_18 = (ulong)local_1c;
  }
  else {
    QDataStream::operator>>(param_1,(longlong *)&local_18);
  }
LAB_0015311a:
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 00153130  QDataStream::writeQSizeType

/* QDataStream::writeQSizeType(QDataStream&, long long) */

undefined8 QDataStream::writeQSizeType(QDataStream *param_1,longlong param_2)

{
  int iVar1;
  QDataStream *this;
  
  if (param_2 < 0xfffffffe) {
    operator<<(param_1,(uint)param_2);
  }
  else {
    iVar1 = version(param_1);
    if (iVar1 < 0x16) {
      if (param_2 != 0xfffffffe) {
        QDataStream::setStatus(param_1,4);
        return 0;
      }
      operator<<(param_1,0xfffffffe);
    }
    else {
      this = (QDataStream *)operator<<(param_1,0xfffffffe);
      QDataStream::operator<<(this,param_2);
    }
  }
  return 1;
}



// ==== 001531da  QDataStream::operator>>

/* QDataStream::TEMPNAMEPLACEHOLDERVALUE(unsigned int&) */

void __thiscall QDataStream::operator>>(QDataStream *this,uint *param_1)

{
  QDataStream::operator>>(this,(int *)param_1);
  return;
}



// ==== 00153200  QDataStream::operator<<

/* QDataStream::TEMPNAMEPLACEHOLDERVALUE(unsigned int) */

void __thiscall QDataStream::operator<<(QDataStream *this,uint param_1)

{
  QDataStream::operator<<(this,param_1);
  return;
}


