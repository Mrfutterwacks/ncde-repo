// Ghidra decompile of LaPivot.oracle — class/namespace IdleInhibitService (11 functions). Raw; not source.

// ==== 0013b56e  IdleInhibitService::qt_static_metacall

/* IdleInhibitService::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void IdleInhibitService::qt_static_metacall
               (IdleInhibitService *param_1,int param_2,int param_3,long *param_4)

{
  long lVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 3) {
      resetIdle(param_1);
    }
    else if (param_3 < 4) {
      if (param_3 == 2) {
        dropOwner(param_1,(QString *)param_4[1]);
      }
      else if (param_3 < 3) {
        if (param_3 == 0) {
          uVar2 = Inhibit(param_1,(QString *)param_4[1],(QString *)param_4[2]);
          if (*param_4 != 0) {
            *(undefined4 *)*param_4 = uVar2;
          }
        }
        else if (param_3 == 1) {
          UnInhibit((uint)param_1);
        }
      }
    }
  }
  if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013b67e  IdleInhibitService::metaObject

/* IdleInhibitService::metaObject() const */

undefined1 * __thiscall IdleInhibitService::metaObject(IdleInhibitService *this)

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



// ==== 0013b6c6  IdleInhibitService::qt_metacast

/* IdleInhibitService::qt_metacast(char const*) */

IdleInhibitService * __thiscall
IdleInhibitService::qt_metacast(IdleInhibitService *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (IdleInhibitService *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"IdleInhibitService");
    if (iVar1 != 0) {
      iVar1 = strcmp(param_1,"QDBusContext");
      if (iVar1 == 0) {
        this = this + 0x10;
      }
      else {
        this = (IdleInhibitService *)QObject::qt_metacast((char *)this);
      }
    }
  }
  return this;
}



// ==== 0013b73e  IdleInhibitService::qt_metacall

/* IdleInhibitService::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
IdleInhibitService::qt_metacall
          (IdleInhibitService *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 4) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -4;
    }
    if (param_2 == 7) {
      if (local_28 < 4) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -4;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015d3ea  IdleInhibitService::IdleInhibitService

/* IdleInhibitService::IdleInhibitService(QObject*) */

void __thiscall IdleInhibitService::IdleInhibitService(IdleInhibitService *this,QObject *param_1)

{
  char cVar1;
  QGuiApplication *this_00;
  undefined8 uVar2;
  long in_FS_OFFSET;
  undefined4 local_b4;
  QString local_b0 [8];
  QX11Application *local_a8;
  wchar16 *local_a0;
  undefined *local_98;
  wchar16 *local_90;
  QString local_88 [32];
  code *local_68;
  undefined8 local_60;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  QDBusContext::QDBusContext((QDBusContext *)(this + 0x10));
  *(undefined ***)this = &PTR_metaObject_0032c268;
  *(undefined8 *)(this + 0x18) = 0;
  QDBusServiceWatcher::QDBusServiceWatcher((QDBusServiceWatcher *)(this + 0x20),(QObject *)0x0);
  QTimer::QTimer((QTimer *)(this + 0x30),(QObject *)0x0);
  QHash<unsigned_int,QString>::QHash((QHash<unsigned_int,QString> *)(this + 0x40));
  *(undefined4 *)(this + 0x48) = 1;
  this_00 = (QGuiApplication *)QCoreApplication::instance();
  local_a8 = QGuiApplication::
             nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
                       (this_00);
  if (local_a8 != (QX11Application *)0x0) {
    uVar2 = (**(code **)(*(long *)local_a8 + 0x18))(local_a8);
    *(undefined8 *)(this + 0x18) = uVar2;
  }
  QDBusConnection::sessionBus();
  local_a0 = L"org.freedesktop.ScreenSaver";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_68,(QTypedArrayData *)0x0,
             L"org.freedesktop.ScreenSaver",0x1b);
  QString::QString(local_88,(QArrayDataPointer *)&local_68);
  cVar1 = QDBusConnection::registerService(local_b0);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_68);
  if (cVar1 != '\x01') {
    QMessageLogger::QMessageLogger((QMessageLogger *)&local_68,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning
              ((char *)&local_68,
               "IdleInhibit: could not own org.freedesktop.ScreenSaver (already claimed?)");
  }
  QFlags<QDBusConnection::RegisterOption>::QFlags
            ((QFlags<QDBusConnection::RegisterOption> *)&local_b4,0x110);
  local_98 = &DAT_00293800;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_68,(QTypedArrayData *)0x0,
             L"/org/freedesktop/ScreenSaver",0x1c);
  QString::QString(local_88,(QArrayDataPointer *)&local_68);
  QDBusConnection::registerObject(local_b0,local_88,this,local_b4);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_68);
  QFlags<QDBusConnection::RegisterOption>::QFlags
            ((QFlags<QDBusConnection::RegisterOption> *)&local_b4,0x110);
  local_90 = L"/ScreenSaver";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_68,(QTypedArrayData *)0x0,L"/ScreenSaver",0xc);
  QString::QString(local_88,(QArrayDataPointer *)&local_68);
  QDBusConnection::registerObject(local_b0,local_88,this,local_b4);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_68);
  QDBusServiceWatcher::setConnection((QDBusConnection *)(this + 0x20));
  QFlags<QDBusServiceWatcher::WatchModeFlag>::QFlags
            ((QFlags<QDBusServiceWatcher::WatchModeFlag> *)&local_68,2);
  QDBusServiceWatcher::setWatchMode(this + 0x20,local_68._0_4_);
  local_68 = dropOwner;
  local_60 = 0;
  QObject::
  connect<void(QDBusServiceWatcher::*)(QString_const&),void(IdleInhibitService::*)(QString_const&)>
            (local_88,this + 0x20,QDBusServiceWatcher::serviceUnregistered,0,this,&local_68,0);
  QMetaObject::Connection::~Connection((Connection *)local_88);
  QTimer::setInterval((int)this + 0x30);
  local_68 = resetIdle;
  local_60 = 0;
  QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(IdleInhibitService::*)()>
            (local_88,this + 0x30,QTimer::timeout,0,this,&local_68,0);
  QMetaObject::Connection::~Connection((Connection *)local_88);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_b0);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015d936  IdleInhibitService::Inhibit

/* IdleInhibitService::Inhibit(QString const&, QString const&) */

uint __thiscall
IdleInhibitService::Inhibit(IdleInhibitService *this,QString *param_1,QString *param_2)

{
  uint uVar1;
  char cVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long in_FS_OFFSET;
  uint local_cc;
  QString local_c8 [32];
  QByteArray local_a8 [32];
  QByteArray local_88 [32];
  QByteArray local_68 [32];
  QMessageLogger local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QDBusContext::calledFromDBus();
  if (cVar2 == '\0') {
    QString::QString(local_c8);
  }
  else {
    QDBusContext::message();
    QDBusMessage::service();
  }
  local_cc = *(uint *)(this + 0x48);
  *(uint *)(this + 0x48) = local_cc + 1;
  QHash<unsigned_int,QString>::insert
            ((QHash<unsigned_int,QString> *)(this + 0x40),&local_cc,local_c8);
  cVar2 = QString::isEmpty(local_c8);
  if (cVar2 != '\x01') {
    QDBusServiceWatcher::addWatchedService((QString *)(this + 0x20));
  }
  QMessageLogger::QMessageLogger(local_48,(char *)0x0,0,(char *)0x0);
  QtPrivate::asString(param_2);
  QString::toLocal8Bit();
  uVar3 = QByteArray::constData(local_68);
  QtPrivate::asString(param_1);
  QString::toLocal8Bit();
  uVar4 = QByteArray::constData(local_88);
  QtPrivate::asString(local_c8);
  QString::toLocal8Bit();
  uVar5 = QByteArray::constData(local_a8);
  QMessageLogger::info((char *)local_48,&DAT_00293858,(ulong)local_cc,uVar5,uVar4,uVar3);
  QByteArray::~QByteArray(local_a8);
  QByteArray::~QByteArray(local_88);
  QByteArray::~QByteArray(local_68);
  resetIdle(this);
  QTimer::start();
  uVar1 = local_cc;
  QString::~QString(local_c8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 0015dbea  IdleInhibitService::UnInhibit

/* IdleInhibitService::UnInhibit(unsigned int) */

void IdleInhibitService::UnInhibit(uint param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  undefined4 in_register_0000003c;
  long in_FS_OFFSET;
  QString local_58 [32];
  QListSpecialMethods<QString> local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<unsigned_int,QString>::take((uint *)local_58);
  bVar1 = false;
  cVar3 = QString::isEmpty(local_58);
  if (cVar3 != '\x01') {
    QHash<unsigned_int,QString>::values();
    bVar1 = true;
    cVar3 = QListSpecialMethods<QString>::contains(local_38,local_58,1);
    if (cVar3 != '\x01') {
      bVar2 = true;
      goto LAB_0015dc87;
    }
  }
  bVar2 = false;
LAB_0015dc87:
  if (bVar1) {
    QList<QString>::~QList((QList<QString> *)local_38);
  }
  if (bVar2) {
    QDBusServiceWatcher::removeWatchedService
              ((QString *)(CONCAT44(in_register_0000003c,param_1) + 0x20));
  }
  cVar3 = QHash<unsigned_int,QString>::isEmpty
                    ((QHash<unsigned_int,QString> *)(CONCAT44(in_register_0000003c,param_1) + 0x40))
  ;
  if (cVar3 != '\0') {
    QTimer::stop();
  }
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015dd48  IdleInhibitService::dropOwner

/* IdleInhibitService::dropOwner(QString const&) */

void __thiscall IdleInhibitService::dropOwner(IdleInhibitService *this,QString *param_1)

{
  char cVar1;
  QString *pQVar2;
  long in_FS_OFFSET;
  undefined1 auVar3 [16];
  iterator local_48 [16];
  undefined1 local_38 [16];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = (iterator  [16])
             QHash<unsigned_int,QString>::begin((QHash<unsigned_int,QString> *)(this + 0x40));
  while( true ) {
    auVar3 = QHash<unsigned_int,QString>::end();
    local_38 = auVar3;
    cVar1 = QHash<unsigned_int,QString>::iterator::operator!=(local_48,(iterator *)local_38);
    if (cVar1 == '\0') break;
    pQVar2 = (QString *)QHash<unsigned_int,QString>::iterator::value(local_48);
    cVar1 = ::operator==(pQVar2,param_1);
    if (cVar1 == '\0') {
      QHash<unsigned_int,QString>::iterator::operator++(local_48);
    }
    else {
      QHash<unsigned_int,QString>::const_iterator::const_iterator
                ((const_iterator *)local_38,local_48);
      auVar3 = QHash<unsigned_int,QString>::erase(this + 0x40,local_38._0_8_,local_38._8_8_);
      local_48 = (iterator  [16])auVar3;
    }
  }
  QDBusServiceWatcher::removeWatchedService((QString *)(this + 0x20));
  cVar1 = QHash<unsigned_int,QString>::isEmpty((QHash<unsigned_int,QString> *)(this + 0x40));
  if (cVar1 != '\0') {
    QTimer::stop();
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015de74  IdleInhibitService::resetIdle

/* IdleInhibitService::resetIdle() */

void __thiscall IdleInhibitService::resetIdle(IdleInhibitService *this)

{
  if (*(long *)(this + 0x18) != 0) {
    xcb_force_screen_saver(*(undefined8 *)(this + 0x18),0);
    xcb_flush(*(undefined8 *)(this + 0x18));
  }
  return;
}



// ==== 0015df9e  IdleInhibitService::~IdleInhibitService

/* IdleInhibitService::~IdleInhibitService() */

void __thiscall IdleInhibitService::~IdleInhibitService(IdleInhibitService *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c268;
  QHash<unsigned_int,QString>::~QHash((QHash<unsigned_int,QString> *)(this + 0x40));
  QTimer::~QTimer((QTimer *)(this + 0x30));
  QDBusServiceWatcher::~QDBusServiceWatcher((QDBusServiceWatcher *)(this + 0x20));
  QDBusContext::~QDBusContext((QDBusContext *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0015e008  IdleInhibitService::~IdleInhibitService

/* IdleInhibitService::~IdleInhibitService() */

void __thiscall IdleInhibitService::~IdleInhibitService(IdleInhibitService *this)

{
  ~IdleInhibitService(this);
  operator_delete(this,0x50);
  return;
}


