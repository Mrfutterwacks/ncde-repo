// Ghidra decompile of LaPivot.oracle — class/namespace SniWatcher (16 functions). Raw; not source.

// ==== 0014e47e  SniWatcher::qt_static_metacall

/* SniWatcher::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void SniWatcher::qt_static_metacall
               (SniWatcher *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  bool bVar1;
  
  if (param_2 == 0) {
    if (param_3 == 4) {
      onOwnerLeft(param_1,*(QString **)(param_4 + 8));
    }
    else if (param_3 < 5) {
      if (param_3 == 3) {
        itemsChanged(param_1);
      }
      else if (param_3 < 4) {
        if (param_3 == 2) {
          hostChanged(param_1);
        }
        else if (param_3 < 3) {
          if (param_3 == 0) {
            itemRegistered(param_1,*(QString **)(param_4 + 8));
          }
          else if (param_3 == 1) {
            itemUnregistered(param_1,*(QString **)(param_4 + 8));
          }
        }
      }
    }
  }
  if ((((param_2 == 5) &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(SniWatcher::*)(QString_const&)>
                          (param_4,(void **)itemRegistered,(_func_void_QString_ptr *)0x0,0), !bVar1)
       ) && (bVar1 = QtMocHelpers::indexOfMethod<void(SniWatcher::*)(QString_const&)>
                               (param_4,(void **)itemUnregistered,(_func_void_QString_ptr *)0x0,1),
            !bVar1)) &&
     (bVar1 = QtMocHelpers::indexOfMethod<void(SniWatcher::*)()>
                        (param_4,(void **)hostChanged,(_func_void *)0x0,2), !bVar1)) {
    QtMocHelpers::indexOfMethod<void(SniWatcher::*)()>
              (param_4,(void **)itemsChanged,(_func_void *)0x0,3);
  }
  return;
}



// ==== 0014e634  SniWatcher::metaObject

/* SniWatcher::metaObject() const */

undefined1 * __thiscall SniWatcher::metaObject(SniWatcher *this)

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



// ==== 0014e67c  SniWatcher::qt_metacast

/* SniWatcher::qt_metacast(char const*) */

SniWatcher * __thiscall SniWatcher::qt_metacast(SniWatcher *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (SniWatcher *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"SniWatcher");
    if (iVar1 != 0) {
      iVar1 = strcmp(param_1,"QDBusContext");
      if (iVar1 == 0) {
        this = this + 0x10;
      }
      else {
        this = (SniWatcher *)QObject::qt_metacast((char *)this);
      }
    }
  }
  return this;
}



// ==== 0014e6f4  SniWatcher::qt_metacall

/* SniWatcher::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
SniWatcher::qt_metacall(SniWatcher *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 5) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -5;
    }
    if (param_2 == 7) {
      if (local_28 < 5) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -5;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014e7ae  SniWatcher::itemRegistered

/* SniWatcher::itemRegistered(QString const&) */

void __thiscall SniWatcher::itemRegistered(SniWatcher *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0,(void *)0x0,param_1);
  return;
}



// ==== 0014e7e6  SniWatcher::itemUnregistered

/* SniWatcher::itemUnregistered(QString const&) */

void __thiscall SniWatcher::itemUnregistered(SniWatcher *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,1,(void *)0x0,param_1);
  return;
}



// ==== 0014e81e  SniWatcher::hostChanged

/* SniWatcher::hostChanged() */

void __thiscall SniWatcher::hostChanged(SniWatcher *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 0014e84a  SniWatcher::itemsChanged

/* SniWatcher::itemsChanged() */

void __thiscall SniWatcher::itemsChanged(SniWatcher *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,3,(void **)0x0);
  return;
}



// ==== 001a1cf8  SniWatcher::items

/* SniWatcher::items() const */

QList<QString> * SniWatcher::items(void)

{
  long in_RSI;
  QList<QString> *in_RDI;
  
  QList<QString>::QList(in_RDI,(QList *)(in_RSI + 0x18));
  return in_RDI;
}



// ==== 001a1d26  SniWatcher::hostRegistered

/* SniWatcher::hostRegistered() const */

SniWatcher __thiscall SniWatcher::hostRegistered(SniWatcher *this)

{
  return this[0x31];
}



// ==== 001a1ee2  SniWatcher::~SniWatcher

/* SniWatcher::~SniWatcher() */

void __thiscall SniWatcher::~SniWatcher(SniWatcher *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bb60;
  QList<QString>::~QList((QList<QString> *)(this + 0x18));
  QDBusContext::~QDBusContext((QDBusContext *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a1f2c  SniWatcher::~SniWatcher

/* SniWatcher::~SniWatcher() */

void __thiscall SniWatcher::~SniWatcher(SniWatcher *this)

{
  ~SniWatcher(this);
  operator_delete(this,0x48);
  return;
}



// ==== 0027234c  SniWatcher::SniWatcher

/* WARNING: Removing unreachable block (ram,0x0027243f) */
/* WARNING: Removing unreachable block (ram,0x0027282a) */
/* SniWatcher::SniWatcher(QObject*) */

void __thiscall SniWatcher::SniWatcher(SniWatcher *this,QObject *param_1)

{
  SniWatcher SVar1;
  StatusNotifierWatcherAdaptor *this_00;
  undefined8 uVar2;
  QDBusServiceWatcher *this_01;
  long in_FS_OFFSET;
  undefined2 uStack_c2;
  QString aQStack_c0 [8];
  wchar16 *pwStack_b8;
  wchar16 *pwStack_b0;
  wchar16 *pwStack_a8;
  wchar16 *pwStack_a0;
  undefined4 auStack_98 [8];
  Connection aCStack_78 [32];
  code *pcStack_58;
  undefined8 uStack_50;
  long lStack_40;
  
  lStack_40 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  QDBusContext::QDBusContext((QDBusContext *)(this + 0x10));
  *(undefined ***)this = &PTR_metaObject_0032bb60;
  QList<QString>::QList((QList<QString> *)(this + 0x18));
  this[0x30] = (SniWatcher)0x0;
  this[0x31] = (SniWatcher)0x0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  this_00 = operator_new(0x18);
  StatusNotifierWatcherAdaptor::StatusNotifierWatcherAdaptor(this_00,this);
  *(StatusNotifierWatcherAdaptor **)(this + 0x40) = this_00;
  pcStack_58 = StatusNotifierWatcherAdaptor::StatusNotifierItemRegistered;
  uStack_50 = 0;
  QObject::
  connect<void(SniWatcher::*)(QString_const&),void(StatusNotifierWatcherAdaptor::*)(QString_const&)>
            (aCStack_78,this,itemRegistered,0,*(undefined8 *)(this + 0x40),&pcStack_58,0);
  QMetaObject::Connection::~Connection(aCStack_78);
  pcStack_58 = StatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered;
  uStack_50 = 0;
  QObject::
  connect<void(SniWatcher::*)(QString_const&),void(StatusNotifierWatcherAdaptor::*)(QString_const&)>
            (aCStack_78,this,itemUnregistered,0,*(undefined8 *)(this + 0x40),&pcStack_58,0);
  QMetaObject::Connection::~Connection(aCStack_78);
  pcStack_58 = StatusNotifierWatcherAdaptor::StatusNotifierHostRegistered;
  uStack_50 = 0;
  QObject::connect<void(SniWatcher::*)(),void(StatusNotifierWatcherAdaptor::*)()>
            (aCStack_78,this,hostChanged,0,*(undefined8 *)(this + 0x40),&pcStack_58,0);
  QMetaObject::Connection::~Connection(aCStack_78);
  QDBusConnection::sessionBus();
  QFlags<QDBusConnection::RegisterOption>::QFlags
            ((QFlags<QDBusConnection::RegisterOption> *)auStack_98,1);
  pwStack_b8 = L"/StatusNotifierWatcher";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&pcStack_58,(QTypedArrayData *)0x0,
             L"/StatusNotifierWatcher",0x16);
  QString::QString((QString *)aCStack_78,(QArrayDataPointer *)&pcStack_58);
  QDBusConnection::registerObject(aQStack_c0,aCStack_78,this,auStack_98[0]);
  QString::~QString((QString *)aCStack_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&pcStack_58);
  pwStack_b0 = L"org.kde.StatusNotifierWatcher";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&pcStack_58,(QTypedArrayData *)0x0,
             L"org.kde.StatusNotifierWatcher",0x1d);
  QString::QString((QString *)aCStack_78,(QArrayDataPointer *)&pcStack_58);
  SVar1 = (SniWatcher)QDBusConnection::registerService(aQStack_c0);
  this[0x30] = SVar1;
  QString::~QString((QString *)aCStack_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&pcStack_58);
  pwStack_a8 = L"org.freedesktop.StatusNotifierWatcher";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&pcStack_58,(QTypedArrayData *)0x0,
             L"org.freedesktop.StatusNotifierWatcher",0x25);
  QString::QString((QString *)aCStack_78,(QArrayDataPointer *)&pcStack_58);
  QDBusConnection::registerService(aQStack_c0);
  QString::~QString((QString *)aCStack_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&pcStack_58);
  pwStack_a0 = L"org.kde.StatusNotifierHost-%1";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&pcStack_58,(QTypedArrayData *)0x0,
             L"org.kde.StatusNotifierHost-%1",0x1d);
  QString::QString((QString *)aCStack_78,(QArrayDataPointer *)&pcStack_58);
  QChar::QChar<char16_t,true>((QChar *)&uStack_c2,L' ');
  uVar2 = QCoreApplication::applicationPid();
  QString::arg<long_long,true>(auStack_98,aCStack_78,uVar2,0,10,uStack_c2);
  QDBusConnection::registerService(aQStack_c0);
  QString::~QString((QString *)auStack_98);
  QString::~QString((QString *)aCStack_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&pcStack_58);
  this[0x31] = (SniWatcher)0x1;
  this_01 = operator_new(0x10);
  QDBusServiceWatcher::QDBusServiceWatcher(this_01,(QObject *)this);
  *(QDBusServiceWatcher **)(this + 0x38) = this_01;
  QDBusServiceWatcher::setConnection(*(QDBusConnection **)(this + 0x38));
  uVar2 = *(undefined8 *)(this + 0x38);
  QFlags<QDBusServiceWatcher::WatchModeFlag>::QFlags
            ((QFlags<QDBusServiceWatcher::WatchModeFlag> *)&pcStack_58,2);
  QDBusServiceWatcher::setWatchMode(uVar2,(ulong)pcStack_58 & 0xffffffff);
  pcStack_58 = onOwnerLeft;
  uStack_50 = 0;
  QObject::connect<void(QDBusServiceWatcher::*)(QString_const&),void(SniWatcher::*)(QString_const&)>
            (aCStack_78,*(undefined8 *)(this + 0x38),QDBusServiceWatcher::serviceUnregistered,0,this
             ,&pcStack_58,0);
  QMetaObject::Connection::~Connection(aCStack_78);
  QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_c0);
  if (lStack_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00272a5a  SniWatcher::registerItem

/* SniWatcher::registerItem(QString const&) */

void __thiscall SniWatcher::registerItem(SniWatcher *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  QLatin1Char QStack_99;
  QString local_98 [32];
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined2 auStack_38 [12];
  long local_20;
  
                    /* catch() { ... } // from try @ 00272e3d with catch @ 00272a6b */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QDBusContext::calledFromDBus();
  if (cVar2 == '\0') {
    QString::QString(local_98);
  }
  else {
    QDBusContext::message();
    QDBusMessage::service();
  }
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_58 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  QLatin1Char::QLatin1Char(&QStack_99,'/');
  QChar::QChar<QLatin1Char,true>((QChar *)auStack_38,QStack_99);
  cVar2 = QString::startsWith(param_1,auStack_38[0],1);
  if (cVar2 == '\0') {
    QString::operator=((QString *)&uStack_78,param_1);
    QString::operator=((QString *)&uStack_58,param_1);
  }
  else {
    ::operator+((QString *)auStack_38,local_98);
    QString::operator=((QString *)&uStack_78,(QString *)auStack_38);
    QString::~QString((QString *)auStack_38);
    QString::operator=((QString *)&uStack_58,local_98);
  }
  cVar2 = QString::isEmpty((QString *)&uStack_78);
  if ((cVar2 == '\0') &&
     (cVar2 = QListSpecialMethods<QString>::contains
                        ((QListSpecialMethods<QString> *)(this + 0x18),&uStack_78,1), cVar2 == '\0')
     ) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (!bVar1) {
    QList<QString>::operator<<((QList<QString> *)(this + 0x18),(QString *)&uStack_78);
    cVar2 = QString::isEmpty((QString *)&uStack_58);
    if (cVar2 != '\x01') {
      QDBusServiceWatcher::addWatchedService(*(QString **)(this + 0x38));
    }
    itemRegistered(this,(QString *)&uStack_78);
    itemsChanged(this);
  }
  QString::~QString((QString *)&uStack_58);
  QString::~QString((QString *)&uStack_78);
  QString::~QString(local_98);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00272d36  SniWatcher::registerHost

/* SniWatcher::registerHost(QString const&) */

void SniWatcher::registerHost(QString *param_1)

{
  if (param_1[0x31] != (QString)0x1) {
    param_1[0x31] = (QString)0x1;
    hostChanged((SniWatcher *)param_1);
  }
                    /* try { // try from 00272d6a to 00372d6e has its CatchHandler @ 00272ed3 */
  return;
}



// ==== 00272d6c  SniWatcher::onOwnerLeft

/* SniWatcher::onOwnerLeft(QString const&) */

void __thiscall SniWatcher::onOwnerLeft(SniWatcher *this,QString *param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  long in_FS_OFFSET;
  QLatin1Char QStack_8b;
  undefined2 uStack_8a;
  undefined8 uStack_88;
  undefined8 uStack_80;
  QList<QString> *pQStack_78;
  QList<QString> *pQStack_70;
  QString *pQStack_68;
  QString *pQStack_60;
  QList<QString> aQStack_58 [16];
  undefined8 uStack_48;
  undefined8 auStack_38 [3];
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  aQStack_58[0] = (QList<QString>)0x0;
  aQStack_58[1] = (QList<QString>)0x0;
  aQStack_58[2] = (QList<QString>)0x0;
  aQStack_58[3] = (QList<QString>)0x0;
  aQStack_58[4] = (QList<QString>)0x0;
  aQStack_58[5] = (QList<QString>)0x0;
  aQStack_58[6] = (QList<QString>)0x0;
  aQStack_58[7] = (QList<QString>)0x0;
  aQStack_58[8] = (QList<QString>)0x0;
  aQStack_58[9] = (QList<QString>)0x0;
  aQStack_58[10] = (QList<QString>)0x0;
  aQStack_58[0xb] = (QList<QString>)0x0;
  aQStack_58[0xc] = (QList<QString>)0x0;
  aQStack_58[0xd] = (QList<QString>)0x0;
  aQStack_58[0xe] = (QList<QString>)0x0;
  aQStack_58[0xf] = (QList<QString>)0x0;
  uStack_48 = 0;
  pQStack_78 = (QList<QString> *)(this + 0x18);
  uStack_88 = QList<QString>::begin(pQStack_78);
  uStack_80 = QList<QString>::end(pQStack_78);
  do {
    cVar3 = QList<QString>::iterator::operator!=((iterator *)&uStack_88,uStack_80);
    if (cVar3 == '\0') {
      pQStack_70 = aQStack_58;
      uStack_80 = QList<QString>::begin(pQStack_70);
      auStack_38[0] = QList<QString>::end(pQStack_70);
      while( true ) {
        cVar3 = QList<QString>::iterator::operator!=((iterator *)&uStack_80,auStack_38[0]);
        if (cVar3 == '\0') break;
        pQStack_68 = (QString *)QList<QString>::iterator::operator*((iterator *)&uStack_80);
        QList<QString>::removeAll<QString>((QList<QString> *)(this + 0x18),pQStack_68);
        itemUnregistered(this,pQStack_68);
        QList<QString>::iterator::operator++((iterator *)&uStack_80);
      }
      QDBusServiceWatcher::removeWatchedService(*(QString **)(this + 0x38));
      cVar3 = QList<QString>::isEmpty(aQStack_58);
      if (cVar3 != '\x01') {
        itemsChanged(this);
      }
      QList<QString>::~QList(aQStack_58);
      if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    pQStack_60 = (QString *)QList<QString>::iterator::operator*((iterator *)&uStack_88);
    bVar1 = false;
    cVar3 = ::operator==(pQStack_60,param_1);
    if (cVar3 == '\0') {
      QLatin1Char::QLatin1Char(&QStack_8b,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)&uStack_8a,QStack_8b);
      ::operator+(auStack_38,param_1,uStack_8a);
      bVar1 = true;
      cVar3 = QString::startsWith(pQStack_60,auStack_38,1);
      if (cVar3 != '\0') goto LAB_00272e71;
      bVar2 = false;
    }
    else {
LAB_00272e71:
      bVar2 = true;
    }
    if (bVar1) {
      QString::~QString((QString *)auStack_38);
    }
    if (bVar2) {
      QList<QString>::operator<<(aQStack_58,pQStack_60);
    }
    QList<QString>::iterator::operator++((iterator *)&uStack_88);
  } while( true );
}


