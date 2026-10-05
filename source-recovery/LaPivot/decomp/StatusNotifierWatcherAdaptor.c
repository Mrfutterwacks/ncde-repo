// Ghidra decompile of LaPivot.oracle — class/namespace StatusNotifierWatcherAdaptor (15 functions). Raw; not source.

// ==== 0014e876  StatusNotifierWatcherAdaptor::qt_static_metacall

/* StatusNotifierWatcherAdaptor::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void StatusNotifierWatcherAdaptor::qt_static_metacall
               (StatusNotifierWatcherAdaptor *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QString> *this;
  bool bVar1;
  QList<QString> QVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  StatusNotifierWatcherAdaptor local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 4) {
      RegisterStatusNotifierHost((QString *)param_1);
    }
    else if (param_3 < 5) {
      if (param_3 == 3) {
        RegisterStatusNotifierItem(param_1,*(QString **)(param_4 + 8));
      }
      else if (param_3 < 4) {
        if (param_3 == 2) {
          StatusNotifierHostRegistered(param_1);
        }
        else if (param_3 < 3) {
          if (param_3 == 0) {
            StatusNotifierItemRegistered(param_1,*(QString **)(param_4 + 8));
          }
          else if (param_3 == 1) {
            StatusNotifierItemUnregistered(param_1,*(QString **)(param_4 + 8));
          }
        }
      }
    }
  }
  if (((param_2 != 5) ||
      (((bVar1 = QtMocHelpers::indexOfMethod<void(StatusNotifierWatcherAdaptor::*)(QString_const&)>
                           (param_4,(void **)StatusNotifierItemRegistered,
                            (_func_void_QString_ptr *)0x0,0), !bVar1 &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(StatusNotifierWatcherAdaptor::*)(QString_const&)>
                           (param_4,(void **)StatusNotifierItemUnregistered,
                            (_func_void_QString_ptr *)0x0,1), !bVar1)) &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(StatusNotifierWatcherAdaptor::*)()>
                          (param_4,(void **)StatusNotifierHostRegistered,(_func_void *)0x0,2),
       !bVar1)))) && (param_2 == 1)) {
    this = *(QList<QString> **)param_4;
    if (param_3 == 2) {
      uVar3 = ProtocolVersion();
      *(undefined4 *)this = uVar3;
    }
    else if (param_3 < 3) {
      if (param_3 == 0) {
        RegisteredStatusNotifierItems(local_48);
        QList<QString>::operator=(this,(QList *)local_48);
        QList<QString>::~QList((QList<QString> *)local_48);
      }
      else if (param_3 == 1) {
        QVar2 = (QList<QString>)IsStatusNotifierHostRegistered(param_1);
        *this = QVar2;
      }
    }
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014eac4  StatusNotifierWatcherAdaptor::metaObject

/* StatusNotifierWatcherAdaptor::metaObject() const */

undefined1 * __thiscall StatusNotifierWatcherAdaptor::metaObject(StatusNotifierWatcherAdaptor *this)

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



// ==== 0014eb0c  StatusNotifierWatcherAdaptor::qt_metacast

/* StatusNotifierWatcherAdaptor::qt_metacast(char const*) */

StatusNotifierWatcherAdaptor * __thiscall
StatusNotifierWatcherAdaptor::qt_metacast(StatusNotifierWatcherAdaptor *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (StatusNotifierWatcherAdaptor *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"StatusNotifierWatcherAdaptor");
    if (iVar1 != 0) {
      this = (StatusNotifierWatcherAdaptor *)QDBusAbstractAdaptor::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014eb60  StatusNotifierWatcherAdaptor::qt_metacall

/* StatusNotifierWatcherAdaptor::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
StatusNotifierWatcherAdaptor::qt_metacall
          (StatusNotifierWatcherAdaptor *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QDBusAbstractAdaptor::qt_metacall(this,param_2,param_3,param_4);
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
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -3;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014ec56  StatusNotifierWatcherAdaptor::StatusNotifierItemRegistered

/* StatusNotifierWatcherAdaptor::StatusNotifierItemRegistered(QString const&) */

void __thiscall
StatusNotifierWatcherAdaptor::StatusNotifierItemRegistered
          (StatusNotifierWatcherAdaptor *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0,(void *)0x0,param_1);
  return;
}



// ==== 0014ec8e  StatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered

/* StatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered(QString const&) */

void __thiscall
StatusNotifierWatcherAdaptor::StatusNotifierItemUnregistered
          (StatusNotifierWatcherAdaptor *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,1,(void *)0x0,param_1);
  return;
}



// ==== 0014ecc6  StatusNotifierWatcherAdaptor::StatusNotifierHostRegistered

/* StatusNotifierWatcherAdaptor::StatusNotifierHostRegistered() */

void __thiscall
StatusNotifierWatcherAdaptor::StatusNotifierHostRegistered(StatusNotifierWatcherAdaptor *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 001a1d38  StatusNotifierWatcherAdaptor::RegisteredStatusNotifierItems

/* StatusNotifierWatcherAdaptor::RegisteredStatusNotifierItems() const */

StatusNotifierWatcherAdaptor * __thiscall
StatusNotifierWatcherAdaptor::RegisteredStatusNotifierItems(StatusNotifierWatcherAdaptor *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  SniWatcher::items();
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a1d88  StatusNotifierWatcherAdaptor::IsStatusNotifierHostRegistered

/* StatusNotifierWatcherAdaptor::IsStatusNotifierHostRegistered() const */

void __thiscall
StatusNotifierWatcherAdaptor::IsStatusNotifierHostRegistered(StatusNotifierWatcherAdaptor *this)

{
  SniWatcher::hostRegistered(*(SniWatcher **)(this + 0x10));
  return;
}



// ==== 001a1da6  StatusNotifierWatcherAdaptor::ProtocolVersion

/* StatusNotifierWatcherAdaptor::ProtocolVersion() const */

undefined8 StatusNotifierWatcherAdaptor::ProtocolVersion(void)

{
  return 0;
}



// ==== 001a1db6  StatusNotifierWatcherAdaptor::RegisterStatusNotifierItem

/* StatusNotifierWatcherAdaptor::RegisterStatusNotifierItem(QString const&) */

void __thiscall
StatusNotifierWatcherAdaptor::RegisterStatusNotifierItem
          (StatusNotifierWatcherAdaptor *this,QString *param_1)

{
  SniWatcher::registerItem(*(SniWatcher **)(this + 0x10),param_1);
  return;
}



// ==== 001a1de0  StatusNotifierWatcherAdaptor::RegisterStatusNotifierHost

/* StatusNotifierWatcherAdaptor::RegisterStatusNotifierHost(QString const&) */

void StatusNotifierWatcherAdaptor::RegisterStatusNotifierHost(QString *param_1)

{
  SniWatcher::registerHost(*(QString **)(param_1 + 0x10));
  return;
}



// ==== 001a1fac  StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor

/* StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor() */

void __thiscall
StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor(StatusNotifierWatcherAdaptor *this)

{
  *(undefined ***)this = &PTR_metaObject_0032baf0;
  QDBusAbstractAdaptor::~QDBusAbstractAdaptor((QDBusAbstractAdaptor *)this);
  return;
}



// ==== 001a1fd6  StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor

/* StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor() */

void __thiscall
StatusNotifierWatcherAdaptor::~StatusNotifierWatcherAdaptor(StatusNotifierWatcherAdaptor *this)

{
  ~StatusNotifierWatcherAdaptor(this);
  operator_delete(this,0x18);
  return;
}



// ==== 0027300e  StatusNotifierWatcherAdaptor::StatusNotifierWatcherAdaptor

/* StatusNotifierWatcherAdaptor::StatusNotifierWatcherAdaptor(SniWatcher*) */

void __thiscall
StatusNotifierWatcherAdaptor::StatusNotifierWatcherAdaptor
          (StatusNotifierWatcherAdaptor *this,SniWatcher *param_1)

{
                    /* catch() { ... } // from try @ 00272fd4 with catch @ 0027300f */
                    /* catch() { ... } // from try @ 00272fba with catch @ 00273020 */
  QDBusAbstractAdaptor::QDBusAbstractAdaptor((QDBusAbstractAdaptor *)this,(QObject *)param_1);
  *(undefined ***)this = &PTR_metaObject_0032baf0;
  *(SniWatcher **)(this + 0x10) = param_1;
  return;
}


