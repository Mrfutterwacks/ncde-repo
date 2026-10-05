// Ghidra decompile of LaPivot.oracle — class/namespace NCDEWorkspace (14 functions). Raw; not source.

// ==== 00146e28  NCDEWorkspace::qt_static_metacall

/* NCDEWorkspace::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NCDEWorkspace::qt_static_metacall
               (NCDEWorkspace *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QString> *this;
  bool bVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QList local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0) {
      changed(param_1);
    }
    else if (param_3 == 1) {
      activate(param_1,**(int **)(param_4 + 8));
    }
  }
  if (((param_2 != 5) ||
      (bVar1 = QtMocHelpers::indexOfMethod<void(NCDEWorkspace::*)()>
                         (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1)) && (param_2 == 1))
  {
    this = *(QList<QString> **)param_4;
    if (param_3 == 0) {
      names();
      QList<QString>::operator=(this,local_38);
      QList<QString>::~QList((QList<QString> *)local_38);
    }
    else if (param_3 == 1) {
      uVar2 = current(param_1);
      *(undefined4 *)this = uVar2;
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00146f4c  NCDEWorkspace::metaObject

/* NCDEWorkspace::metaObject() const */

undefined1 * __thiscall NCDEWorkspace::metaObject(NCDEWorkspace *this)

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



// ==== 00146f94  NCDEWorkspace::qt_metacast

/* NCDEWorkspace::qt_metacast(char const*) */

NCDEWorkspace * __thiscall NCDEWorkspace::qt_metacast(NCDEWorkspace *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NCDEWorkspace *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NCDEWorkspace");
    if (iVar1 != 0) {
      this = (NCDEWorkspace *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 00146fe8  NCDEWorkspace::qt_metacall

/* NCDEWorkspace::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NCDEWorkspace::qt_metacall(NCDEWorkspace *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 2) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -2;
    }
    if (param_2 == 7) {
      if (local_28 < 2) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -2;
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



// ==== 001470de  NCDEWorkspace::changed

/* NCDEWorkspace::changed() */

void __thiscall NCDEWorkspace::changed(NCDEWorkspace *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0017dc0c  NCDEWorkspace::NCDEWorkspace

/* NCDEWorkspace::NCDEWorkspace(QObject*) */

void __thiscall NCDEWorkspace::NCDEWorkspace(NCDEWorkspace *this,QObject *param_1)

{
  undefined4 uVar1;
  QGuiApplication *this_00;
  undefined8 uVar2;
  long in_FS_OFFSET;
  Connection local_60 [8];
  QX11Application *local_58;
  undefined4 *local_50;
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032be00;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  QList<QString>::QList((QList<QString> *)(this + 0x30));
  QTimer::QTimer((QTimer *)(this + 0x48),(QObject *)0x0);
  this_00 = (QGuiApplication *)QCoreApplication::instance();
  local_58 = QGuiApplication::
             nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
                       (this_00);
  if (local_58 != (QX11Application *)0x0) {
    uVar2 = (**(code **)(*(long *)local_58 + 0x18))(local_58);
    *(undefined8 *)(this + 0x10) = uVar2;
  }
  if (*(long *)(this + 0x10) != 0) {
    uVar2 = xcb_get_setup(*(undefined8 *)(this + 0x10));
    local_50 = (undefined4 *)xcb_setup_roots_iterator(uVar2);
    if (local_50 != (undefined4 *)0x0) {
      *(undefined4 *)(this + 0x18) = *local_50;
    }
    uVar1 = intern(this,"_NET_CURRENT_DESKTOP");
    *(undefined4 *)(this + 0x1c) = uVar1;
    uVar1 = intern(this,"_NET_NUMBER_OF_DESKTOPS");
    *(undefined4 *)(this + 0x20) = uVar1;
    uVar1 = intern(this,"_NET_DESKTOP_NAMES");
    *(undefined4 *)(this + 0x24) = uVar1;
  }
  local_48 = refresh;
  local_40 = 0;
  QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(NCDEWorkspace::*)()>
            (local_60,this + 0x48,QTimer::timeout,0,this,&local_48,0);
  QMetaObject::Connection::~Connection(local_60);
  QTimer::start((int)this + 0x48);
  refresh(this);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017dea4  NCDEWorkspace::names

/* NCDEWorkspace::names() const */

QList<QString> * NCDEWorkspace::names(void)

{
  bool bVar1;
  char cVar2;
  undefined8 *puVar3;
  QString *this;
  long in_RSI;
  QList<QString> *in_RDI;
  long lVar4;
  long in_FS_OFFSET;
  QString *local_c8;
  QString local_a8 [96];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QList<QString>::isEmpty((QList<QString> *)(in_RSI + 0x30));
  bVar1 = false;
  if (cVar2 == '\0') {
    QList<QString>::QList(in_RDI,(QList *)(in_RSI + 0x30));
  }
  else {
    local_c8 = local_a8;
    puVar3 = &C_1678_3;
    for (lVar4 = 3; -1 < lVar4; lVar4 = lVar4 + -1) {
      QString::QString(local_c8,(char *)*puVar3);
      local_c8 = local_c8 + 0x18;
      puVar3 = puVar3 + 1;
    }
    bVar1 = true;
    QList<QString>::QList(in_RDI,local_a8,4);
  }
  if (bVar1) {
    this = aQStack_48;
    while (this != local_a8) {
      this = this + -0x18;
      QString::~QString(this);
    }
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017e088  NCDEWorkspace::current

/* NCDEWorkspace::current() const */

undefined4 __thiscall NCDEWorkspace::current(NCDEWorkspace *this)

{
  return *(undefined4 *)(this + 0x28);
}



// ==== 0017e09a  NCDEWorkspace::activate

/* NCDEWorkspace::activate(int) */

void __thiscall NCDEWorkspace::activate(NCDEWorkspace *this,int param_1)

{
  undefined1 auVar1 [16];
  long in_FS_OFFSET;
  undefined1 local_38 [4];
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  undefined1 local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x10) != 0) && (*(int *)(this + 0x1c) != 0)) {
    stack0xffffffffffffffc9 = SUB1615((undefined1  [16])0x0,1);
    local_38._0_2_ = 0x2021;
    uStack_34 = *(undefined4 *)(this + 0x18);
    uStack_30 = *(undefined4 *)(this + 0x1c);
    iStack_2c = param_1;
    local_28._4_12_ = SUB1612((undefined1  [16])0x0,4);
    auVar1._12_4_ = 0;
    auVar1._0_12_ = local_28._4_12_;
    local_28._0_16_ = auVar1 << 0x20;
    xcb_send_event(*(undefined8 *)(this + 0x10),0,*(undefined4 *)(this + 0x18),0x180000,local_38);
    xcb_flush(*(undefined8 *)(this + 0x10));
  }
  *(int *)(this + 0x28) = param_1;
  changed(this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017e172  NCDEWorkspace::intern

/* NCDEWorkspace::intern(char const*) */

undefined4 __thiscall NCDEWorkspace::intern(NCDEWorkspace *this,char *param_1)

{
  long lVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  void *__ptr;
  long in_FS_OFFSET;
  undefined4 local_1c;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = qstrlen(param_1);
  uVar3 = xcb_intern_atom(*(undefined8 *)(this + 0x10),0,uVar2,param_1);
  __ptr = (void *)xcb_intern_atom_reply(*(undefined8 *)(this + 0x10),uVar3,0);
  if (__ptr == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = *(undefined4 *)((long)__ptr + 8);
  }
  free(__ptr);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_1c;
}



// ==== 0017e21c  NCDEWorkspace::readCard

/* NCDEWorkspace::readCard(unsigned int) */

undefined4 __thiscall NCDEWorkspace::readCard(NCDEWorkspace *this,uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *__ptr;
  undefined4 *puVar3;
  undefined4 local_14;
  
  if ((*(long *)(this + 0x10) != 0) && (param_1 != 0)) {
    uVar1 = xcb_get_property(*(undefined8 *)(this + 0x10),0,*(undefined4 *)(this + 0x18),param_1,6,0
                             ,1);
    __ptr = (void *)xcb_get_property_reply(*(undefined8 *)(this + 0x10),uVar1,0);
    if ((__ptr == (void *)0x0) || (iVar2 = xcb_get_property_value_length(__ptr), iVar2 < 4)) {
      local_14 = 0;
    }
    else {
      puVar3 = (undefined4 *)xcb_get_property_value(__ptr);
      local_14 = *puVar3;
    }
    free(__ptr);
    return local_14;
  }
  return 0;
}



// ==== 0017e308  NCDEWorkspace::refresh

/* NCDEWorkspace::refresh() */

void __thiscall NCDEWorkspace::refresh(NCDEWorkspace *this)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long in_FS_OFFSET;
  int local_64;
  QList<QString> local_58 [16];
  undefined8 local_48;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iVar3 = readCard(this,*(uint *)(this + 0x1c));
  iVar4 = readCard(this,*(uint *)(this + 0x20));
  local_58[0] = (QList<QString>)0x0;
  local_58[1] = (QList<QString>)0x0;
  local_58[2] = (QList<QString>)0x0;
  local_58[3] = (QList<QString>)0x0;
  local_58[4] = (QList<QString>)0x0;
  local_58[5] = (QList<QString>)0x0;
  local_58[6] = (QList<QString>)0x0;
  local_58[7] = (QList<QString>)0x0;
  local_58[8] = (QList<QString>)0x0;
  local_58[9] = (QList<QString>)0x0;
  local_58[10] = (QList<QString>)0x0;
  local_58[0xb] = (QList<QString>)0x0;
  local_58[0xc] = (QList<QString>)0x0;
  local_58[0xd] = (QList<QString>)0x0;
  local_58[0xe] = (QList<QString>)0x0;
  local_58[0xf] = (QList<QString>)0x0;
  local_48 = 0;
  local_64 = 0;
  while( true ) {
    iVar5 = iVar4;
    if (iVar4 < 1) {
      iVar5 = 4;
    }
    if (iVar5 <= local_64) break;
    QString::number((int)local_38,local_64 + 1);
    QList<QString>::operator<<(local_58,local_38);
    QString::~QString(local_38);
    local_64 = local_64 + 1;
  }
  if ((iVar3 == *(int *)(this + 0x28)) &&
     (cVar2 = QList<QString>::operator!=(local_58,(QList *)(this + 0x30)), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    *(int *)(this + 0x28) = iVar3;
    QList<QString>::operator=((QList<QString> *)(this + 0x30),(QList *)local_58);
    changed(this);
  }
  QList<QString>::~QList(local_58);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017e55e  NCDEWorkspace::~NCDEWorkspace

/* NCDEWorkspace::~NCDEWorkspace() */

void __thiscall NCDEWorkspace::~NCDEWorkspace(NCDEWorkspace *this)

{
  *(undefined ***)this = &PTR_metaObject_0032be00;
  QTimer::~QTimer((QTimer *)(this + 0x48));
  QList<QString>::~QList((QList<QString> *)(this + 0x30));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0017e5a8  NCDEWorkspace::~NCDEWorkspace

/* NCDEWorkspace::~NCDEWorkspace() */

void __thiscall NCDEWorkspace::~NCDEWorkspace(NCDEWorkspace *this)

{
  ~NCDEWorkspace(this);
  operator_delete(this,0x58);
  return;
}


