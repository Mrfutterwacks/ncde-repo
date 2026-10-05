// Ghidra decompile of LaPivot.oracle — class/namespace ScreenInfo (10 functions). Raw; not source.

// ==== 00148996  ScreenInfo::qt_static_metacall

/* ScreenInfo::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void ScreenInfo::qt_static_metacall
               (ScreenInfo *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  undefined4 *puVar1;
  bool bVar2;
  undefined4 uVar3;
  
  if ((param_2 == 0) && (param_3 == 0)) {
    changed(param_1);
  }
  if (((param_2 != 5) ||
      (bVar2 = QtMocHelpers::indexOfMethod<void(ScreenInfo::*)()>
                         (param_4,(void **)changed,(_func_void *)0x0,0), !bVar2)) && (param_2 == 1))
  {
    puVar1 = *(undefined4 **)param_4;
    if (param_3 == 0) {
      uVar3 = width();
      *puVar1 = uVar3;
    }
    else if (param_3 == 1) {
      uVar3 = height();
      *puVar1 = uVar3;
    }
  }
  return;
}



// ==== 00148a52  ScreenInfo::metaObject

/* ScreenInfo::metaObject() const */

undefined1 * __thiscall ScreenInfo::metaObject(ScreenInfo *this)

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



// ==== 00148a9a  ScreenInfo::qt_metacast

/* ScreenInfo::qt_metacast(char const*) */

ScreenInfo * __thiscall ScreenInfo::qt_metacast(ScreenInfo *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (ScreenInfo *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"ScreenInfo");
    if (iVar1 != 0) {
      this = (ScreenInfo *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 00148aee  ScreenInfo::qt_metacall

/* ScreenInfo::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
ScreenInfo::qt_metacall(ScreenInfo *this,int param_2,undefined4 param_3,undefined8 *param_4)

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
      local_28 = local_28 + -2;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00148be4  ScreenInfo::changed

/* ScreenInfo::changed() */

void __thiscall ScreenInfo::changed(ScreenInfo *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0018286e  ScreenInfo::ScreenInfo

/* ScreenInfo::ScreenInfo(QObject*) */

void __thiscall ScreenInfo::ScreenInfo(ScreenInfo *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_58 [8];
  long local_50;
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032bcb0;
  local_50 = QGuiApplication::primaryScreen();
  if (local_50 != 0) {
    local_48 = changed;
    local_40 = 0;
    QObject::connect<void(QScreen::*)(QRect_const&),void(ScreenInfo::*)()>
              (local_58,local_50,QScreen::geometryChanged,0,this,&local_48,0);
    QMetaObject::Connection::~Connection(local_58);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00182974  ScreenInfo::width

/* ScreenInfo::width() const */

undefined8 ScreenInfo::width(void)

{
  long lVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  undefined1 local_28 [16];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QGuiApplication::primaryScreen();
  if (lVar1 == 0) {
    uVar2 = 0;
  }
  else {
    local_28 = QScreen::geometry();
    uVar2 = QRect::width((QRect *)local_28);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 001829dc  ScreenInfo::height

/* ScreenInfo::height() const */

undefined8 ScreenInfo::height(void)

{
  long lVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  undefined1 local_28 [16];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QGuiApplication::primaryScreen();
  if (lVar1 == 0) {
    uVar2 = 0;
  }
  else {
    local_28 = QScreen::geometry();
    uVar2 = QRect::height((QRect *)local_28);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 00182b1c  ScreenInfo::~ScreenInfo

/* ScreenInfo::~ScreenInfo() */

void __thiscall ScreenInfo::~ScreenInfo(ScreenInfo *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bcb0;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 00182b46  ScreenInfo::~ScreenInfo

/* ScreenInfo::~ScreenInfo() */

void __thiscall ScreenInfo::~ScreenInfo(ScreenInfo *this)

{
  ~ScreenInfo(this);
  operator_delete(this,0x10);
  return;
}


