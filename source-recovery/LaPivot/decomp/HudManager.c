// Ghidra decompile of LaPivot.oracle — class/namespace HudManager (11 functions). Raw; not source.

// ==== 0013b2d2  HudManager::qt_static_metacall

/* HudManager::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void HudManager::qt_static_metacall
               (HudManager *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  bool bVar1;
  
  if (param_2 == 0) {
    if (param_3 == 3) {
      dismissHud(param_1);
    }
    else if (param_3 < 4) {
      if (param_3 == 2) {
        requestHud(param_1);
      }
      else if (param_3 < 3) {
        if (param_3 == 0) {
          hudRequested(param_1);
        }
        else if (param_3 == 1) {
          hudDismissed(param_1);
        }
      }
    }
  }
  if ((param_2 == 5) &&
     (bVar1 = QtMocHelpers::indexOfMethod<void(HudManager::*)()>
                        (param_4,(void **)hudRequested,(_func_void *)0x0,0), !bVar1)) {
    QtMocHelpers::indexOfMethod<void(HudManager::*)()>
              (param_4,(void **)hudDismissed,(_func_void *)0x0,1);
  }
  return;
}



// ==== 0013b3c0  HudManager::metaObject

/* HudManager::metaObject() const */

undefined1 * __thiscall HudManager::metaObject(HudManager *this)

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



// ==== 0013b408  HudManager::qt_metacast

/* HudManager::qt_metacast(char const*) */

HudManager * __thiscall HudManager::qt_metacast(HudManager *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (HudManager *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"HudManager");
    if (iVar1 != 0) {
      this = (HudManager *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013b45c  HudManager::qt_metacall

/* HudManager::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
HudManager::qt_metacall(HudManager *this,int param_2,undefined4 param_3,undefined8 *param_4)

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



// ==== 0013b516  HudManager::hudRequested

/* HudManager::hudRequested() */

void __thiscall HudManager::hudRequested(HudManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0013b542  HudManager::hudDismissed

/* HudManager::hudDismissed() */

void __thiscall HudManager::hudDismissed(HudManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0015d1ee  HudManager::HudManager

/* HudManager::HudManager(QObject*) */

void __thiscall HudManager::HudManager(HudManager *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c2d8;
  return;
}



// ==== 0015d222  HudManager::requestHud

/* HudManager::requestHud() */

void __thiscall HudManager::requestHud(HudManager *this)

{
  hudRequested(this);
  return;
}



// ==== 0015d23e  HudManager::dismissHud

/* HudManager::dismissHud() */

void __thiscall HudManager::dismissHud(HudManager *this)

{
  hudDismissed(this);
  return;
}



// ==== 0015d332  HudManager::~HudManager

/* HudManager::~HudManager() */

void __thiscall HudManager::~HudManager(HudManager *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c2d8;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0015d35c  HudManager::~HudManager

/* HudManager::~HudManager() */

void __thiscall HudManager::~HudManager(HudManager *this)

{
  ~HudManager(this);
  operator_delete(this,0x10);
  return;
}


