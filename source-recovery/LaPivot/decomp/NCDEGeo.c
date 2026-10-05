// Ghidra decompile of LaPivot.oracle — class/namespace NCDEGeo (17 functions). Raw; not source.

// ==== 0014536e  NCDEGeo::qt_static_metacall

/* NCDEGeo::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NCDEGeo::qt_static_metacall(NCDEGeo *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QString *this;
  bool bVar1;
  QString QVar2;
  long in_FS_OFFSET;
  undefined8 uVar3;
  NCDEGeo local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((param_2 == 0) && (param_3 == 0)) {
    changed(param_1);
  }
  if (((param_2 != 5) ||
      (bVar1 = QtMocHelpers::indexOfMethod<void(NCDEGeo::*)()>
                         (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1)) && (param_2 == 1))
  {
    this = *(QString **)param_4;
    if (param_3 == 7) {
      zone(local_38);
      QString::operator=(this,(QString *)local_38);
      QString::~QString((QString *)local_38);
    }
    else if (param_3 < 8) {
      if (param_3 == 6) {
        tzName();
        QString::operator=(this,(QString *)local_38);
        QString::~QString((QString *)local_38);
      }
      else if (param_3 < 7) {
        if (param_3 == 5) {
          place();
          QString::operator=(this,(QString *)local_38);
          QString::~QString((QString *)local_38);
        }
        else if (param_3 < 6) {
          if (param_3 == 4) {
            offset(local_38);
            QString::operator=(this,(QString *)local_38);
            QString::~QString((QString *)local_38);
          }
          else if (param_3 < 5) {
            if (param_3 == 3) {
              QVar2 = (QString)locating(param_1);
              *this = QVar2;
            }
            else if (param_3 < 4) {
              if (param_3 == 2) {
                localTime(local_38);
                QString::operator=(this,(QString *)local_38);
                QString::~QString((QString *)local_38);
              }
              else if (param_3 < 3) {
                if (param_3 == 0) {
                  uVar3 = latitude(param_1);
                  *(undefined8 *)this = uVar3;
                }
                else if (param_3 == 1) {
                  uVar3 = longitude(param_1);
                  *(undefined8 *)this = uVar3;
                }
              }
            }
          }
        }
      }
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00145602  NCDEGeo::metaObject

/* NCDEGeo::metaObject() const */

undefined1 * __thiscall NCDEGeo::metaObject(NCDEGeo *this)

{
  long lVar1;
  undefined1 *puVar2;
  
  lVar1 = QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>>::operator->
                    ((QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>> *)(this + 8));
  if (*(long *)(lVar1 + 0x38) == 0) {
    puVar2 = staticMetaObject;
  }
  else {
    QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>>::operator->
              ((QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>> *)(this + 8));
    puVar2 = (undefined1 *)QObjectData::dynamicMetaObject();
  }
  return puVar2;
}



// ==== 0014564a  NCDEGeo::qt_metacast

/* NCDEGeo::qt_metacast(char const*) */

NCDEGeo * __thiscall NCDEGeo::qt_metacast(NCDEGeo *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NCDEGeo *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NCDEGeo");
    if (iVar1 != 0) {
      this = (NCDEGeo *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014569e  NCDEGeo::qt_metacall

/* NCDEGeo::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NCDEGeo::qt_metacall(NCDEGeo *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 1) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -1;
    }
    if (param_2 == 7) {
      if (local_28 < 1) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -1;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -8;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00145794  NCDEGeo::changed

/* NCDEGeo::changed() */

void __thiscall NCDEGeo::changed(NCDEGeo *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 00176312  NCDEGeo::NCDEGeo

/* NCDEGeo::NCDEGeo(QObject*) */

void __thiscall NCDEGeo::NCDEGeo(NCDEGeo *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c038;
  *(undefined8 *)(this + 0x10) = 0;
  return;
}



// ==== 00176352  NCDEGeo::latitude

/* NCDEGeo::latitude() const */

undefined8 __thiscall NCDEGeo::latitude(NCDEGeo *this)

{
  long in_FS_OFFSET;
  undefined8 uVar1;
  QVariant local_b0 [8];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    Lelan::location();
    ::QVariant::QVariant(local_88);
    QString::QString(local_a8,"lat");
    QMap<QString,QVariant>::value(local_68,local_b0);
    uVar1 = ::QVariant::toDouble((bool *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_88);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b0);
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00176528  NCDEGeo::longitude

/* NCDEGeo::longitude() const */

undefined8 __thiscall NCDEGeo::longitude(NCDEGeo *this)

{
  long in_FS_OFFSET;
  undefined8 uVar1;
  QVariant local_b0 [8];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    Lelan::location();
    ::QVariant::QVariant(local_88);
    QString::QString(local_a8,"lon");
    QMap<QString,QVariant>::value(local_68,local_b0);
    uVar1 = ::QVariant::toDouble((bool *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_88);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b0);
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001766fe  NCDEGeo::place

/* NCDEGeo::place() const */

QString * NCDEGeo::place(void)

{
  long lVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString(in_RDI);
  }
  else {
    Lelan::placeName();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017676a  NCDEGeo::tzName

/* NCDEGeo::tzName() const */

QString * NCDEGeo::tzName(void)

{
  long lVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString(in_RDI);
  }
  else {
    Lelan::timezone();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001767d6  NCDEGeo::zone

/* NCDEGeo::zone() const */

NCDEGeo * __thiscall NCDEGeo::zone(NCDEGeo *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  tzName();
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00176822  NCDEGeo::locating

/* NCDEGeo::locating() const */

undefined8 __thiscall NCDEGeo::locating(NCDEGeo *this)

{
  bool bVar1;
  char cVar2;
  undefined8 uVar3;
  long in_FS_OFFSET;
  QMap<QString,QVariant> local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = false;
  if (*(long *)(this + 0x10) != 0) {
    Lelan::location();
    bVar1 = true;
    cVar2 = QMap<QString,QVariant>::isEmpty(local_28);
    if (cVar2 != '\0') {
      uVar3 = 1;
      goto LAB_0017688c;
    }
  }
  uVar3 = 0;
LAB_0017688c:
  if (bVar1) {
    QMap<QString,QVariant>::~QMap(local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar3;
}



// ==== 001768f0  NCDEGeo::localTime

/* NCDEGeo::localTime() const */

NCDEGeo * __thiscall NCDEGeo::localTime(NCDEGeo *this)

{
  long in_FS_OFFSET;
  QDateTime local_68 [8];
  undefined1 *local_60;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDateTime::currentDateTime();
  local_60 = &LAB_002996eb_3;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"h:mm AP",7);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  QDateTime::toString((QString *)this);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QDateTime::~QDateTime(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001769f8  NCDEGeo::offset

/* NCDEGeo::offset() const */

NCDEGeo * __thiscall NCDEGeo::offset(NCDEGeo *this)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  long in_FS_OFFSET;
  undefined2 local_d2;
  undefined2 local_d0;
  undefined2 local_ce;
  int local_cc;
  QTimeZone local_c8 [8];
  undefined1 *local_c0;
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  tzName();
  cVar1 = QString::isEmpty(local_b8);
  if (cVar1 == '\0') {
    QString::toUtf8(local_38);
    QTimeZone::QTimeZone(local_c8,(QByteArray *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    cVar1 = QTimeZone::isValid();
    if (cVar1 == '\x01') {
      QDateTime::currentDateTime();
      local_cc = QTimeZone::offsetFromUtc((QDateTime *)local_c8);
      QDateTime::~QDateTime((QDateTime *)local_38);
      local_c0 = &LAB_002996d3_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_98,(QTypedArrayData *)0x0,L"UTC%1%2:%3",10);
      QString::QString(local_78,(QArrayDataPointer *)local_98);
      QChar::QChar<char16_t,true>((QChar *)&local_d2,L' ');
      if (local_cc < 0) {
        puVar3 = &LAB_002996eb_1;
      }
      else {
        puVar3 = &LAB_002996e9_1;
      }
      QString::arg<char[2],true>(local_58,local_78,puVar3,0,local_d2);
      QChar::QChar<char,true>((QChar *)&local_d0,'0');
      iVar2 = qAbs<int>(&local_cc);
      QString::arg<int,true>(local_38,local_58,iVar2 / 0xe10,2,10,local_d0);
      QChar::QChar<char,true>((QChar *)&local_ce,'0');
      iVar2 = qAbs<int>(&local_cc);
      QString::arg<int,true>(this,local_38,(iVar2 % 0xe10) / 0x3c,2,10,local_ce);
      QString::~QString(local_38);
      QString::~QString(local_58);
      QString::~QString(local_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    }
    else {
      QString::QString((QString *)this);
    }
    QTimeZone::~QTimeZone(local_c8);
  }
  else {
    QString::QString((QString *)this);
  }
  QString::~QString(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00176e6e  NCDEGeo::~NCDEGeo

/* NCDEGeo::~NCDEGeo() */

void __thiscall NCDEGeo::~NCDEGeo(NCDEGeo *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c038;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 00176e98  NCDEGeo::~NCDEGeo

/* NCDEGeo::~NCDEGeo() */

void __thiscall NCDEGeo::~NCDEGeo(NCDEGeo *this)

{
  ~NCDEGeo(this);
  operator_delete(this,0x18);
  return;
}



// ==== 001fe046  NCDEGeo::setLelan

/* NCDEGeo::setLelan(Lelan*) */

void __thiscall NCDEGeo::setLelan(NCDEGeo *this,Lelan *param_1)

{
  long in_FS_OFFSET;
  Connection local_60 [8];
  code *local_58;
  undefined8 uStack_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  *(Lelan **)(this + 0x10) = param_1;
  if (param_1 != (Lelan *)0x0) {
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEGeo::*)()>
              (local_60,param_1,Lelan::placeNameChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEGeo::*)()>
              (local_60,param_1,Lelan::timezoneChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(unsigned_long_long),void(NCDEGeo::*)()>
              (local_60,param_1,Lelan::pulse,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


