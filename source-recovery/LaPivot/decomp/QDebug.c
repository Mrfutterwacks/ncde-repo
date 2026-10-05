// Ghidra decompile of LaPivot.oracle — class/namespace QDebug (9 functions). Raw; not source.

// ==== 00153cf2  QDebug::QDebug

/* QDebug::QDebug(QDebug const&) */

void __thiscall QDebug::QDebug(QDebug *this,QDebug *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(int *)(*(long *)this + 0x28) = *(int *)(*(long *)this + 0x28) + 1;
  return;
}



// ==== 00153d20  QDebug::QDebug

/* QDebug::QDebug(QDebug&&) */

void __thiscall QDebug::QDebug(QDebug *this,QDebug *param_1)

{
  Stream *pSVar1;
  long in_FS_OFFSET;
  _func_decltype_nullptr *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (_func_decltype_nullptr *)0x0;
  pSVar1 = std::exchange<QDebug::Stream*,decltype(nullptr)>((Stream **)param_1,&local_18);
  *(Stream **)this = pSVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00153d78  QDebug::nospace

/* QDebug::nospace() */

QDebug * __thiscall QDebug::nospace(QDebug *this)

{
  *(undefined1 *)(*(long *)this + 0x30) = 0;
  return this;
}



// ==== 00153d92  QDebug::maybeSpace

/* QDebug::maybeSpace() */

QDebug * __thiscall QDebug::maybeSpace(QDebug *this)

{
  if (*(char *)(*(long *)this + 0x30) != '\0') {
    QTextStream::operator<<(*(QTextStream **)this,' ');
  }
  return this;
}



// ==== 00153dc8  QDebug::operator<<

/* QDebug::TEMPNAMEPLACEHOLDERVALUE(char) */

void __thiscall QDebug::operator<<(QDebug *this,char param_1)

{
  QTextStream::operator<<(*(QTextStream **)this,param_1);
  maybeSpace(this);
  return;
}



// ==== 00153dfe  QDebug::operator<<

/* QDebug::TEMPNAMEPLACEHOLDERVALUE(unsigned int) */

void __thiscall QDebug::operator<<(QDebug *this,uint param_1)

{
  QTextStream::operator<<(*(QTextStream **)this,param_1);
  maybeSpace(this);
  return;
}



// ==== 00153e32  QDebug::operator<<

/* QDebug::TEMPNAMEPLACEHOLDERVALUE(double) */

void __thiscall QDebug::operator<<(QDebug *this,double param_1)

{
  QTextStream::operator<<(*(QTextStream **)this,param_1);
  maybeSpace(this);
  return;
}



// ==== 00153e6c  QDebug::operator<<

/* QDebug::TEMPNAMEPLACEHOLDERVALUE(char const*) */

void __thiscall QDebug::operator<<(QDebug *this,char *param_1)

{
  QTextStream *this_00;
  long in_FS_OFFSET;
  char *local_58;
  QDebug *local_50;
  undefined8 local_48;
  undefined8 local_40;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QTextStream **)this;
  local_58 = param_1;
  local_50 = this;
  QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_48,&local_58);
  QString::fromUtf8(local_38,local_48,local_40);
  QTextStream::operator<<(this_00,local_38);
  QString::~QString(local_38);
  maybeSpace(local_50);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00153f32  QDebug::operator<<

/* QDebug::TEMPNAMEPLACEHOLDERVALUE(QString const&) */

void __thiscall QDebug::operator<<(QDebug *this,QString *param_1)

{
  ulong uVar1;
  
  QString::size(param_1);
  uVar1 = QString::constData(param_1);
  ::QDebug::putString((QChar *)this,uVar1);
  maybeSpace(this);
  return;
}


