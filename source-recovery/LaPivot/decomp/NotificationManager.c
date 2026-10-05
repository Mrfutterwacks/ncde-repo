// Ghidra decompile of LaPivot.oracle — class/namespace NotificationManager (21 functions). Raw; not source.

// ==== 001484b6  NotificationManager::qt_static_metacall

/* NotificationManager::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NotificationManager::qt_static_metacall
               (NotificationManager *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  bool bVar1;
  QList<QVariant> QVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  undefined4 local_48 [6];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 6) {
      markRead(param_1);
    }
    else if (param_3 < 7) {
      if (param_3 == 5) {
        dismissAll(param_1);
      }
      else if (param_3 < 6) {
        if (param_3 == 4) {
          dismiss(param_1,**(int **)(param_4 + 8));
        }
        else if (param_3 < 5) {
          if (param_3 == 3) {
            local_48[0] = notify(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10),
                                 *(QString **)(param_4 + 0x18),**(int **)(param_4 + 0x20));
            if (*(long *)param_4 != 0) {
              **(undefined4 **)param_4 = local_48[0];
            }
          }
          else if (param_3 < 4) {
            if (param_3 == 2) {
              setAppNotify(param_1,*(QString **)(param_4 + 8),
                           *(bool *)*(undefined8 *)(param_4 + 0x10));
            }
            else if (param_3 < 3) {
              if (param_3 == 0) {
                changed(param_1);
              }
              else if (param_3 == 1) {
                appsChanged(param_1);
              }
            }
          }
        }
      }
    }
  }
  if (((param_2 != 5) ||
      ((bVar1 = QtMocHelpers::indexOfMethod<void(NotificationManager::*)()>
                          (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1 &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(NotificationManager::*)()>
                          (param_4,(void **)appsChanged,(_func_void *)0x0,1), !bVar1)))) &&
     (param_2 == 1)) {
    this = *(QList<QVariant> **)param_4;
    if (param_3 == 3) {
      notifyApps();
      QList<QVariant>::operator=(this,(QList *)local_48);
      QList<QVariant>::~QList((QList<QVariant> *)local_48);
    }
    else if (param_3 < 4) {
      if (param_3 == 2) {
        uVar3 = unreadCount(param_1);
        *(undefined4 *)this = uVar3;
      }
      else if (param_3 < 3) {
        if (param_3 == 0) {
          notifications();
          QList<QVariant>::operator=(this,(QList *)local_48);
          QList<QVariant>::~QList((QList<QVariant> *)local_48);
        }
        else if (param_3 == 1) {
          QVar2 = (QList<QVariant>)hasNotifications(param_1);
          *this = QVar2;
        }
      }
    }
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001487ac  NotificationManager::metaObject

/* NotificationManager::metaObject() const */

undefined1 * __thiscall NotificationManager::metaObject(NotificationManager *this)

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



// ==== 001487f4  NotificationManager::qt_metacast

/* NotificationManager::qt_metacast(char const*) */

NotificationManager * __thiscall
NotificationManager::qt_metacast(NotificationManager *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NotificationManager *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NotificationManager");
    if (iVar1 != 0) {
      this = (NotificationManager *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 00148848  NotificationManager::qt_metacall

/* NotificationManager::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NotificationManager::qt_metacall
          (NotificationManager *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 7) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -7;
    }
    if (param_2 == 7) {
      if (local_28 < 7) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -7;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -4;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014893e  NotificationManager::changed

/* NotificationManager::changed() */

void __thiscall NotificationManager::changed(NotificationManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0014896a  NotificationManager::appsChanged

/* NotificationManager::appsChanged() */

void __thiscall NotificationManager::appsChanged(NotificationManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 00180970  NotificationManager::NotificationManager

/* NotificationManager::NotificationManager(QObject*) */

void __thiscall NotificationManager::NotificationManager(NotificationManager *this,QObject *param_1)

{
  undefined1 uVar1;
  char cVar2;
  QString *pQVar3;
  undefined1 *puVar4;
  long in_FS_OFFSET;
  QString local_68 [8];
  undefined1 *local_60;
  undefined8 local_58 [4];
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032bd20;
  *(undefined8 *)(this + 0x10) = 0;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x18));
  *(undefined4 *)(this + 0x30) = 0;
  QMap<QString,bool>::QMap((QMap<QString,bool> *)(this + 0x38));
  local_60 = &LAB_0029e166;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_38,(QTypedArrayData *)0x0,L"notify-apps",0xb);
  QString::QString((QString *)local_58,(QArrayDataPointer *)local_38);
  Lelan::readConfig(local_68);
  QString::~QString((QString *)local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_38);
  local_58[0] = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)local_68);
  while( true ) {
    local_38[0] = QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)local_68);
    cVar2 = ::operator!=((const_iterator *)local_58,(const_iterator *)local_38);
    if (cVar2 == '\0') break;
    QMap<QString,QVariant>::const_iterator::value((const_iterator *)local_58);
    uVar1 = ::QVariant::toBool();
    pQVar3 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_58);
    puVar4 = (undefined1 *)
             QMap<QString,bool>::operator[]((QMap<QString,bool> *)(this + 0x38),pQVar3);
    *puVar4 = uVar1;
    QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_58);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00180b6c  NotificationManager::notifications

/* NotificationManager::notifications() const */

QList<QVariant> * NotificationManager::notifications(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x18));
  return in_RDI;
}



// ==== 00180b9a  NotificationManager::hasNotifications

/* NotificationManager::hasNotifications() const */

uint __thiscall NotificationManager::hasNotifications(NotificationManager *this)

{
  uint uVar1;
  
  uVar1 = QList<QVariant>::isEmpty((QList<QVariant> *)(this + 0x18));
  return uVar1 ^ 1;
}



// ==== 00180bbc  NotificationManager::unreadCount

/* NotificationManager::unreadCount() const */

int __thiscall NotificationManager::unreadCount(NotificationManager *this)

{
  char cVar1;
  long in_FS_OFFSET;
  int local_dc;
  undefined8 local_d8;
  undefined8 local_d0;
  QVariant local_c8 [8];
  QList<QVariant> *local_c0;
  undefined8 local_b8;
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_dc = 0;
  local_c0 = (QList<QVariant> *)(this + 0x18);
  local_d8 = QList<QVariant>::begin(local_c0);
  local_d0 = QList<QVariant>::end(local_c0);
  while( true ) {
    cVar1 = QList<QVariant>::const_iterator::operator!=((const_iterator *)&local_d8,local_d0);
    if (cVar1 == '\0') break;
    local_b8 = QList<QVariant>::const_iterator::operator*((const_iterator *)&local_d8);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    local_b0 = &LAB_0029e17e;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"read",4);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_c8);
    cVar1 = ::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
    if (cVar1 != '\x01') {
      local_dc = local_dc + 1;
    }
    QList<QVariant>::const_iterator::operator++((const_iterator *)&local_d8);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_dc;
}



// ==== 00180dde  NotificationManager::notifyApps

/* NotificationManager::notifyApps() const */

QList<QVariant> * NotificationManager::notifyApps(void)

{
  char cVar1;
  QString *pQVar2;
  QVariant *pQVar3;
  char *pcVar4;
  undefined8 uVar5;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  undefined8 local_140;
  undefined8 local_138;
  undefined1 *local_130;
  wchar16 *local_128;
  undefined *local_120;
  wchar16 *local_118;
  wchar16 *local_110;
  wchar16 *local_108;
  undefined *local_100;
  QArrayDataPointer<char16_t> local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  undefined8 local_78 [4];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
  *(undefined8 *)(in_RDI + 0x10) = 0;
  local_140 = QMap<QString,bool>::constBegin((QMap<QString,bool> *)(in_RSI + 0x38));
  while( true ) {
    local_78[0] = QMap<QString,bool>::constEnd((QMap<QString,bool> *)(in_RSI + 0x38));
    cVar1 = ::operator!=((const_iterator *)&local_140,(const_iterator *)local_78);
    if (cVar1 == '\0') break;
    local_138 = 0;
    pQVar2 = (QString *)QMap<QString,bool>::const_iterator::key((const_iterator *)&local_140);
    ::QVariant::QVariant(local_58,pQVar2);
    local_130 = &LAB_0029e187_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_98,(QTypedArrayData *)0x0,L"name",4);
    QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_78);
    ::QVariant::operator=(pQVar3,local_58);
    QString::~QString((QString *)local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    ::QVariant::~QVariant(local_58);
    local_120 = &DAT_0029e192;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_98,(QTypedArrayData *)0x0,L"🔔",2);
    QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
    ::QVariant::QVariant(local_58,(QString *)local_78);
    local_128 = L"icon";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"icon",4);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_138,local_b8);
    ::QVariant::operator=(pQVar3,local_58);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    ::QVariant::~QVariant(local_58);
    QString::~QString((QString *)local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    pcVar4 = (char *)QMap<QString,bool>::const_iterator::value((const_iterator *)&local_140);
    cVar1 = *pcVar4;
    if (cVar1 == '\0') {
      local_110 = L"Notifications off";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_98,(QTypedArrayData *)0x0,L"Notifications off",0x11);
      QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
    }
    else {
      local_118 = L"Notifications on";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"Notifications on",
                 0x10);
      QString::QString((QString *)local_78,(QArrayDataPointer *)local_b8);
    }
    ::QVariant::QVariant(local_58,(QString *)local_78);
    local_108 = L"meta";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"meta",4);
    QString::QString((QString *)local_d8,(QArrayDataPointer *)local_f8);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_d8);
    ::QVariant::operator=(pQVar3,local_58);
    QString::~QString((QString *)local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
    ::QVariant::~QVariant(local_58);
    QString::~QString((QString *)local_78);
    if (cVar1 == '\0') {
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    }
    else {
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
    }
    uVar5 = QMap<QString,bool>::const_iterator::value((const_iterator *)&local_140);
    ::QVariant::QVariant(local_58,*(bool *)uVar5);
    local_100 = &DAT_0029e1fe;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_98,(QTypedArrayData *)0x0,L"on",2);
    QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_78);
    ::QVariant::operator=(pQVar3,local_58);
    QString::~QString((QString *)local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    ::QVariant::~QVariant(local_58);
    ::QVariant::QVariant(local_58,(QMap *)&local_138);
    QList<QVariant>::append(in_RDI,local_58);
    ::QVariant::~QVariant(local_58);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_138);
    QMap<QString,bool>::const_iterator::operator++((const_iterator *)&local_140);
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return in_RDI;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00181476  NotificationManager::setAppNotify

/* NotificationManager::setAppNotify(QString const&, bool) */

void __thiscall
NotificationManager::setAppNotify(NotificationManager *this,QString *param_1,bool param_2)

{
  char cVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  bool local_21;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_21 = true;
  cVar1 = QMap<QString,bool>::value((QMap<QString,bool> *)(this + 0x38),param_1,&local_21);
  if (param_2 != (bool)cVar1) {
    uVar2 = QMap<QString,bool>::operator[]((QMap<QString,bool> *)(this + 0x38),param_1);
    *(bool *)uVar2 = param_2;
    saveApps(this);
    appsChanged(this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00181514  NotificationManager::inQuietHours

/* NotificationManager::inQuietHours() const */

undefined8 __thiscall NotificationManager::inQuietHours(NotificationManager *this)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined1 *local_b8;
  undefined1 *local_b0;
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  undefined4 local_68 [8];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = false;
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_48);
    bVar1 = true;
    cVar3 = ::QVariant::toBool();
    if (cVar3 == '\x01') {
      bVar2 = false;
      goto LAB_00181594;
    }
  }
  bVar2 = true;
LAB_00181594:
  if (bVar1) {
    ::QVariant::~QVariant(local_48);
  }
  if (bVar2) {
    uVar4 = 0;
  }
  else {
    local_b8 = &LAB_002996eb_3;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"h:mm AP",7);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    QObject::property((char *)local_48);
    ::QVariant::toString();
    local_c0 = QTime::fromString(local_a8,(QString *)local_68);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    local_b0 = &LAB_002996eb_3;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"h:mm AP",7);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    QObject::property((char *)local_48);
    ::QVariant::toString();
    local_bc = QTime::fromString(local_a8,(QString *)local_68);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    cVar3 = QTime::isValid();
    if ((cVar3 == '\x01') && (cVar3 = QTime::isValid(), cVar3 == '\x01')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      uVar4 = 0;
    }
    else {
      local_68[0] = QTime::currentTime();
      cVar3 = operator>((QTime *)&local_c0,(QTime *)&local_bc);
      if (cVar3 == '\0') {
        cVar3 = operator>=((QTime *)local_68,(QTime *)&local_c0);
        if ((cVar3 == '\0') ||
           (cVar3 = ::operator<((QTime *)local_68,(QTime *)&local_bc), cVar3 == '\0')) {
          uVar4 = 0;
        }
        else {
          uVar4 = 1;
        }
      }
      else {
        cVar3 = operator>=((QTime *)local_68,(QTime *)&local_c0);
        if ((cVar3 == '\0') &&
           (cVar3 = ::operator<((QTime *)local_68,(QTime *)&local_bc), cVar3 == '\0')) {
          uVar4 = 0;
        }
        else {
          uVar4 = 1;
        }
      }
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00181942  NotificationManager::notify

/* NotificationManager::notify(QString const&, QString const&, QString const&, int) */

int __thiscall
NotificationManager::notify
          (NotificationManager *this,QString *param_1,QString *param_2,QString *param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  undefined1 *puVar4;
  QVariant *pQVar5;
  int iVar6;
  long in_FS_OFFSET;
  undefined8 local_c0;
  undefined1 *local_b8;
  undefined1 *local_b0;
  undefined1 *local_a8;
  wchar16 *local_a0;
  undefined1 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = false;
  if (*(long *)(this + 0x10) == 0) {
LAB_001819d5:
    bVar2 = false;
  }
  else {
    QObject::property((char *)local_48);
    bVar1 = true;
    cVar3 = ::QVariant::toBool();
    if (cVar3 == '\0') goto LAB_001819d5;
    bVar2 = true;
  }
  if (bVar1) {
    ::QVariant::~QVariant(local_48);
  }
  if (bVar2) {
    iVar6 = 0;
  }
  else {
    cVar3 = inQuietHours(this);
    if (cVar3 == '\0') {
      cVar3 = QMap<QString,bool>::contains((QMap<QString,bool> *)(this + 0x38),param_1);
      if (cVar3 == '\x01') {
        local_68[0] = (QString)0x0;
        cVar3 = QMap<QString,bool>::value
                          ((QMap<QString,bool> *)(this + 0x38),param_1,(bool *)local_68);
        if (cVar3 != '\x01') {
          iVar6 = 0;
          goto LAB_00181efa;
        }
      }
      else {
        puVar4 = (undefined1 *)
                 QMap<QString,bool>::operator[]((QMap<QString,bool> *)(this + 0x38),param_1);
        *puVar4 = 1;
        saveApps(this);
        appsChanged(this);
      }
      *(int *)(this + 0x30) = *(int *)(this + 0x30) + 1;
      iVar6 = *(int *)(this + 0x30);
      local_c0 = 0;
      ::QVariant::QVariant(local_48,iVar6);
      local_b8 = &LAB_0029e228;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"id",2);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,param_1);
      local_b0 = &LAB_0029e22e;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"title",5);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,param_2);
      local_a8 = &LAB_0029e239_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"body",4);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,param_3);
      local_a0 = L"icon";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"icon",4);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,param_4);
      local_98 = &LAB_0029e243_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"timeout",7);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,false);
      local_90 = &LAB_0029e17e;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"read",4);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      pQVar5 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
      ::QVariant::operator=(pQVar5,local_48);
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      ::QVariant::~QVariant(local_48);
      ::QVariant::QVariant(local_48,(QMap *)&local_c0);
      QList<QVariant>::prepend((QList<QVariant> *)(this + 0x18),local_48);
      ::QVariant::~QVariant(local_48);
      changed(this);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
    }
    else {
      iVar6 = 0;
    }
  }
LAB_00181efa:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar6;
}



// ==== 00182098  NotificationManager::dismiss

/* NotificationManager::dismiss(int) */

void __thiscall NotificationManager::dismiss(NotificationManager *this,int param_1)

{
  int iVar1;
  long lVar2;
  long in_FS_OFFSET;
  int local_bc;
  QVariant local_b8 [8];
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_bc = 0;
  do {
    lVar2 = QList<QVariant>::size((QList<QVariant> *)(this + 0x18));
    if (lVar2 <= local_bc) {
LAB_0018229b:
      if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x18),(long)local_bc);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    local_b0 = &LAB_0029e228;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"id",2);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_b8);
    iVar1 = ::QVariant::toInt((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b8);
    if (param_1 == iVar1) {
      QList<QVariant>::removeAt((QList<QVariant> *)(this + 0x18),(long)local_bc);
      changed(this);
      goto LAB_0018229b;
    }
    local_bc = local_bc + 1;
  } while( true );
}



// ==== 001822b6  NotificationManager::dismissAll

/* NotificationManager::dismissAll() */

void __thiscall NotificationManager::dismissAll(NotificationManager *this)

{
  char cVar1;
  
  cVar1 = QList<QVariant>::isEmpty((QList<QVariant> *)(this + 0x18));
  if (cVar1 != '\x01') {
    QList<QVariant>::clear((QList<QVariant> *)(this + 0x18));
    changed(this);
  }
  return;
}



// ==== 001822f8  NotificationManager::markRead

/* NotificationManager::markRead() */

void __thiscall NotificationManager::markRead(NotificationManager *this)

{
  char cVar1;
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined8 local_b8;
  undefined8 local_b0;
  QMap<QString,QVariant> local_a8 [8];
  QList<QVariant> *local_a0;
  QVariant *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a0 = (QList<QVariant> *)(this + 0x18);
  local_b8 = QList<QVariant>::begin(local_a0);
  local_b0 = QList<QVariant>::end(local_a0);
  while( true ) {
    cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_b8,local_b0);
    if (cVar1 == '\0') break;
    local_98 = (QVariant *)QList<QVariant>::iterator::operator*((iterator *)&local_b8);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_48,true);
    local_90 = &LAB_0029e17e;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"read",4);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    this_00 = (QVariant *)QMap<QString,QVariant>::operator[](local_a8,local_68);
    ::QVariant::operator=(this_00,local_48);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,(QMap *)local_a8);
    ::QVariant::operator=(local_98,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap(local_a8);
    QList<QVariant>::iterator::operator++((iterator *)&local_b8);
  }
  changed(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00182520  NotificationManager::saveApps

/* NotificationManager::saveApps() const */

void __thiscall NotificationManager::saveApps(NotificationManager *this)

{
  char cVar1;
  undefined8 uVar2;
  QString *pQVar3;
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined8 local_98;
  undefined1 *local_90;
  undefined8 local_88 [4];
  undefined8 local_68 [4];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 0;
  local_88[0] = QMap<QString,bool>::constBegin((QMap<QString,bool> *)(this + 0x38));
  while( true ) {
    local_68[0] = QMap<QString,bool>::constEnd((QMap<QString,bool> *)(this + 0x38));
    cVar1 = ::operator!=((const_iterator *)local_88,(const_iterator *)local_68);
    if (cVar1 == '\0') break;
    uVar2 = QMap<QString,bool>::const_iterator::value((const_iterator *)local_88);
    ::QVariant::QVariant(local_48,*(bool *)uVar2);
    pQVar3 = (QString *)QMap<QString,bool>::const_iterator::key((const_iterator *)local_88);
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,pQVar3);
    ::QVariant::operator=(this_00,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,bool>::const_iterator::operator++((const_iterator *)local_88);
  }
  local_90 = &LAB_0029e166;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"notify-apps",0xb);
  QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig((QString *)local_68,(QMap *)&local_98);
  QString::~QString((QString *)local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001827d2  NotificationManager::~NotificationManager

/* NotificationManager::~NotificationManager() */

void __thiscall NotificationManager::~NotificationManager(NotificationManager *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bd20;
  QMap<QString,bool>::~QMap((QMap<QString,bool> *)(this + 0x38));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x18));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0018281c  NotificationManager::~NotificationManager

/* NotificationManager::~NotificationManager() */

void __thiscall NotificationManager::~NotificationManager(NotificationManager *this)

{
  ~NotificationManager(this);
  operator_delete(this,0x40);
  return;
}



// ==== 001fcdba  NotificationManager::setSettings

/* NotificationManager::setSettings(QObject*) */

void __thiscall NotificationManager::setSettings(NotificationManager *this,QObject *param_1)

{
  *(QObject **)(this + 0x10) = param_1;
  return;
}


