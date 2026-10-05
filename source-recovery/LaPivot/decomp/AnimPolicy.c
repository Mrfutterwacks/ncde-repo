// Ghidra decompile of LaPivot.oracle — class/namespace AnimPolicy (33 functions). Raw; not source.

// ==== 00139e2a  AnimPolicy::qt_static_metacall

/* AnimPolicy::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void AnimPolicy::qt_static_metacall
               (AnimPolicy *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    if (param_3 == 0xf) {
      setLowPowerBattery(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
    }
    else if (param_3 < 0x10) {
      if (param_3 == 0xe) {
        setLowPowerMemory(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
      }
      else if (param_3 < 0xf) {
        if (param_3 == 0xd) {
          setLowPowerProfile(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
        }
        else if (param_3 < 0xe) {
          if (param_3 == 0xc) {
            setLowPowerCpu(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
          }
          else if (param_3 < 0xd) {
            if (param_3 == 0xb) {
              onSessionUnlocked(param_1);
            }
            else if (param_3 < 0xc) {
              if (param_3 == 10) {
                onSessionLocked(param_1);
              }
              else if (param_3 < 0xb) {
                if (param_3 == 9) {
                  onVtActiveChanged(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                }
                else if (param_3 < 10) {
                  if (param_3 == 8) {
                    onUserInputIdle(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                  }
                  else if (param_3 < 9) {
                    if (param_3 == 7) {
                      onScreenSaverActivated(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                    }
                    else if (param_3 < 8) {
                      if (param_3 == 6) {
                        setDesktopObscured(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                      }
                      else if (param_3 < 7) {
                        if (param_3 == 5) {
                          setThermalPressure(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                        }
                        else if (param_3 < 6) {
                          if (param_3 == 4) {
                            reevaluate(param_1);
                          }
                          else if (param_3 < 5) {
                            if (param_3 == 3) {
                              setReduceMotion(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                            }
                            else if (param_3 < 4) {
                              if (param_3 == 2) {
                                setLevel(param_1,**(int **)(param_4 + 8));
                              }
                              else if (param_3 < 3) {
                                if (param_3 == 0) {
                                  changed(param_1);
                                }
                                else if (param_3 == 1) {
                                  policyChanged(param_1);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (((param_2 != 5) ||
      ((bVar2 = QtMocHelpers::indexOfMethod<void(AnimPolicy::*)()>
                          (param_4,(void **)changed,(_func_void *)0x0,0), !bVar2 &&
       (bVar2 = QtMocHelpers::indexOfMethod<void(AnimPolicy::*)()>
                          (param_4,(void **)policyChanged,(_func_void *)0x0,1), !bVar2)))) &&
     (param_2 == 1)) {
    puVar1 = *(undefined4 **)param_4;
    if (param_3 == 8) {
      uVar3 = desktopObscured(param_1);
      *(undefined1 *)puVar1 = uVar3;
    }
    else if (param_3 < 9) {
      if (param_3 == 7) {
        uVar3 = lowPower(param_1);
        *(undefined1 *)puVar1 = uVar3;
      }
      else if (param_3 < 8) {
        if (param_3 == 6) {
          uVar3 = thermalPressure(param_1);
          *(undefined1 *)puVar1 = uVar3;
        }
        else if (param_3 < 7) {
          if (param_3 == 5) {
            uVar3 = screenIdle(param_1);
            *(undefined1 *)puVar1 = uVar3;
          }
          else if (param_3 < 6) {
            if (param_3 == 4) {
              uVar3 = instant(param_1);
              *(undefined1 *)puVar1 = uVar3;
            }
            else if (param_3 < 5) {
              if (param_3 == 3) {
                uVar3 = decorative(param_1);
                *(undefined1 *)puVar1 = uVar3;
              }
              else if (param_3 < 4) {
                if (param_3 == 2) {
                  uVar3 = idleLoops(param_1);
                  *(undefined1 *)puVar1 = uVar3;
                }
                else if (param_3 < 3) {
                  if (param_3 == 0) {
                    uVar4 = level(param_1);
                    *puVar1 = uVar4;
                  }
                  else if (param_3 == 1) {
                    uVar3 = reduceMotion(param_1);
                    *(undefined1 *)puVar1 = uVar3;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}



// ==== 0013a322  AnimPolicy::metaObject

/* AnimPolicy::metaObject() const */

undefined1 * __thiscall AnimPolicy::metaObject(AnimPolicy *this)

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



// ==== 0013a36a  AnimPolicy::qt_metacast

/* AnimPolicy::qt_metacast(char const*) */

AnimPolicy * __thiscall AnimPolicy::qt_metacast(AnimPolicy *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (AnimPolicy *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"AnimPolicy");
    if (iVar1 != 0) {
      this = (AnimPolicy *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013a3be  AnimPolicy::qt_metacall

/* AnimPolicy::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
AnimPolicy::qt_metacall(AnimPolicy *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x10) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x10;
    }
    if (param_2 == 7) {
      if (local_28 < 0x10) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x10;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -9;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013a4b4  AnimPolicy::changed

/* AnimPolicy::changed() */

void __thiscall AnimPolicy::changed(AnimPolicy *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0013a4e0  AnimPolicy::policyChanged

/* AnimPolicy::policyChanged() */

void __thiscall AnimPolicy::policyChanged(AnimPolicy *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 00153596  AnimPolicy::AnimPolicy

/* AnimPolicy::AnimPolicy(QObject*) */

void __thiscall AnimPolicy::AnimPolicy(AnimPolicy *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_50 [8];
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c508;
  *(undefined4 *)(this + 0x10) = 0;
  this[0x14] = (AnimPolicy)0x0;
  this[0x15] = (AnimPolicy)0x0;
  this[0x16] = (AnimPolicy)0x0;
  this[0x17] = (AnimPolicy)0x0;
  this[0x18] = (AnimPolicy)0x0;
  this[0x19] = (AnimPolicy)0x0;
  this[0x1a] = (AnimPolicy)0x0;
  this[0x1b] = (AnimPolicy)0x0;
  this[0x1c] = (AnimPolicy)0x0;
  this[0x1d] = (AnimPolicy)0x0;
  this[0x1e] = (AnimPolicy)0x0;
  this[0x1f] = (AnimPolicy)0x0;
  local_48 = policyChanged;
  local_40 = 0;
  QObject::connect<void(AnimPolicy::*)(),void(AnimPolicy::*)()>
            (local_50,this,changed,0,this,&local_48,0);
  QMetaObject::Connection::~Connection(local_50);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001536f0  AnimPolicy::level

/* AnimPolicy::level() const */

undefined4 __thiscall AnimPolicy::level(AnimPolicy *this)

{
  return *(undefined4 *)(this + 0x10);
}



// ==== 00153702  AnimPolicy::reduceMotion

/* AnimPolicy::reduceMotion() const */

AnimPolicy __thiscall AnimPolicy::reduceMotion(AnimPolicy *this)

{
  return this[0x14];
}



// ==== 00153714  AnimPolicy::idleLoops

/* AnimPolicy::idleLoops() const */

undefined4 __thiscall AnimPolicy::idleLoops(AnimPolicy *this)

{
  return CONCAT31((int3)((uint)*(int *)(this + 0x10) >> 8),*(int *)(this + 0x10) == 0);
}



// ==== 0015372a  AnimPolicy::decorative

/* AnimPolicy::decorative() const */

undefined4 __thiscall AnimPolicy::decorative(AnimPolicy *this)

{
  return CONCAT31((int3)((uint)*(int *)(this + 0x10) >> 8),*(int *)(this + 0x10) < 2);
}



// ==== 00153742  AnimPolicy::instant

/* AnimPolicy::instant() const */

undefined4 __thiscall AnimPolicy::instant(AnimPolicy *this)

{
  return CONCAT31((int3)((uint)*(int *)(this + 0x10) >> 8),1 < *(int *)(this + 0x10));
}



// ==== 0015375a  AnimPolicy::screenIdle

/* AnimPolicy::screenIdle() const */

AnimPolicy __thiscall AnimPolicy::screenIdle(AnimPolicy *this)

{
  return this[0x15];
}



// ==== 0015376c  AnimPolicy::thermalPressure

/* AnimPolicy::thermalPressure() const */

AnimPolicy __thiscall AnimPolicy::thermalPressure(AnimPolicy *this)

{
  return this[0x16];
}



// ==== 0015377e  AnimPolicy::lowPower

/* AnimPolicy::lowPower() const */

undefined8 __thiscall AnimPolicy::lowPower(AnimPolicy *this)

{
  undefined8 uVar1;
  
  if ((((this[0x1c] == (AnimPolicy)0x0) && (this[0x1d] == (AnimPolicy)0x0)) &&
      (this[0x1e] == (AnimPolicy)0x0)) && (this[0x1f] == (AnimPolicy)0x0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 001537c4  AnimPolicy::desktopObscured

/* AnimPolicy::desktopObscured() const */

AnimPolicy __thiscall AnimPolicy::desktopObscured(AnimPolicy *this)

{
  return this[0x17];
}



// ==== 001537d6  AnimPolicy::setLevel

/* AnimPolicy::setLevel(int) */

void __thiscall AnimPolicy::setLevel(AnimPolicy *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x10)) {
    *(int *)(this + 0x10) = param_1;
    changed(this);
  }
  return;
}



// ==== 0015380a  AnimPolicy::setReduceMotion

/* AnimPolicy::setReduceMotion(bool) */

void __thiscall AnimPolicy::setReduceMotion(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x14]) {
    this[0x14] = (AnimPolicy)param_1;
    reevaluate(this);
  }
  return;
}



// ==== 00153842  AnimPolicy::reevaluate

/* AnimPolicy::reevaluate() */

void __thiscall AnimPolicy::reevaluate(AnimPolicy *this)

{
  changed(this);
  return;
}



// ==== 0015385e  AnimPolicy::setThermalPressure

/* AnimPolicy::setThermalPressure(bool) */

void __thiscall AnimPolicy::setThermalPressure(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x16]) {
    this[0x16] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 00153896  AnimPolicy::setDesktopObscured

/* AnimPolicy::setDesktopObscured(bool) */

void __thiscall AnimPolicy::setDesktopObscured(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x17]) {
    this[0x17] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 001538ce  AnimPolicy::onScreenSaverActivated

/* AnimPolicy::onScreenSaverActivated(bool) */

void __thiscall AnimPolicy::onScreenSaverActivated(AnimPolicy *this,bool param_1)

{
  this[0x1a] = (AnimPolicy)param_1;
  applyScreenIdle(this);
  return;
}



// ==== 001538f8  AnimPolicy::onUserInputIdle

/* AnimPolicy::onUserInputIdle(bool) */

void __thiscall AnimPolicy::onUserInputIdle(AnimPolicy *this,bool param_1)

{
  this[0x1b] = (AnimPolicy)param_1;
  applyScreenIdle(this);
  return;
}



// ==== 00153922  AnimPolicy::onVtActiveChanged

/* AnimPolicy::onVtActiveChanged(bool) */

void __thiscall AnimPolicy::onVtActiveChanged(AnimPolicy *this,bool param_1)

{
  this[0x19] = (AnimPolicy)!param_1;
  applyScreenIdle(this);
  return;
}



// ==== 00153952  AnimPolicy::onSessionLocked

/* AnimPolicy::onSessionLocked() */

void __thiscall AnimPolicy::onSessionLocked(AnimPolicy *this)

{
  this[0x18] = (AnimPolicy)0x1;
  applyScreenIdle(this);
  return;
}



// ==== 00153976  AnimPolicy::onSessionUnlocked

/* AnimPolicy::onSessionUnlocked() */

void __thiscall AnimPolicy::onSessionUnlocked(AnimPolicy *this)

{
  this[0x18] = (AnimPolicy)0x0;
  applyScreenIdle(this);
  return;
}



// ==== 0015399a  AnimPolicy::setLowPowerCpu

/* AnimPolicy::setLowPowerCpu(bool) */

void __thiscall AnimPolicy::setLowPowerCpu(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x1c]) {
    this[0x1c] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 001539d2  AnimPolicy::setLowPowerProfile

/* AnimPolicy::setLowPowerProfile(bool) */

void __thiscall AnimPolicy::setLowPowerProfile(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x1d]) {
    this[0x1d] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 00153a0a  AnimPolicy::setLowPowerMemory

/* AnimPolicy::setLowPowerMemory(bool) */

void __thiscall AnimPolicy::setLowPowerMemory(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x1e]) {
    this[0x1e] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 00153a42  AnimPolicy::setLowPowerBattery

/* AnimPolicy::setLowPowerBattery(bool) */

void __thiscall AnimPolicy::setLowPowerBattery(AnimPolicy *this,bool param_1)

{
  if ((AnimPolicy)param_1 != this[0x1f]) {
    this[0x1f] = (AnimPolicy)param_1;
    changed(this);
  }
  return;
}



// ==== 00153a7a  AnimPolicy::applyScreenIdle

/* AnimPolicy::applyScreenIdle() */

void __thiscall AnimPolicy::applyScreenIdle(AnimPolicy *this)

{
  AnimPolicy AVar1;
  
  if ((((this[0x18] == (AnimPolicy)0x0) && (this[0x19] == (AnimPolicy)0x0)) &&
      (this[0x1a] == (AnimPolicy)0x0)) && (this[0x1b] == (AnimPolicy)0x0)) {
    AVar1 = (AnimPolicy)0x0;
  }
  else {
    AVar1 = (AnimPolicy)0x1;
  }
  if (AVar1 != this[0x15]) {
    this[0x15] = AVar1;
    changed(this);
  }
  return;
}



// ==== 00153bc4  AnimPolicy::~AnimPolicy

/* AnimPolicy::~AnimPolicy() */

void __thiscall AnimPolicy::~AnimPolicy(AnimPolicy *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c508;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 00153bee  AnimPolicy::~AnimPolicy

/* AnimPolicy::~AnimPolicy() */

void __thiscall AnimPolicy::~AnimPolicy(AnimPolicy *this)

{
  ~AnimPolicy(this);
  operator_delete(this,0x20);
  return;
}


