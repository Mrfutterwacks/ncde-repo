// Ghidra decompile of LaPivot.oracle — class/namespace WindowTyper (13 functions). Raw; not source.

// ==== 0014fdd4  WindowTyper::qt_static_metacall

/* WindowTyper::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void WindowTyper::qt_static_metacall(void)

{
  return;
}



// ==== 0014fdf2  WindowTyper::metaObject

/* WindowTyper::metaObject() const */

undefined1 * __thiscall WindowTyper::metaObject(WindowTyper *this)

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



// ==== 0014fe3a  WindowTyper::qt_metacast

/* WindowTyper::qt_metacast(char const*) */

WindowTyper * __thiscall WindowTyper::qt_metacast(WindowTyper *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (WindowTyper *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"WindowTyper");
    if (iVar1 != 0) {
      this = (WindowTyper *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014fe8e  WindowTyper::qt_metacall

/* WindowTyper::qt_metacall(QMetaObject::Call, int, void**) */

undefined4 __thiscall
WindowTyper::qt_metacall(WindowTyper *this,undefined4 param_2,undefined4 param_3,undefined8 param_4)

{
  undefined4 uVar1;
  
  uVar1 = QObject::qt_metacall(this,param_2,param_3,param_4);
  return uVar1;
}



// ==== 001a30ea  WindowTyper::WindowTyper

/* WindowTyper::WindowTyper(QObject*) */

void __thiscall WindowTyper::WindowTyper(WindowTyper *this,QObject *param_1)

{
  QGuiApplication *this_00;
  QX11Application *pQVar1;
  undefined8 uVar2;
  QObject *pQVar3;
  
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032ba10;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  QHash<QString,unsigned_int>::QHash((QHash<QString,unsigned_int> *)(this + 0x20));
  QHash<QWindow*,unsigned_int>::QHash((QHash<QWindow*,unsigned_int> *)(this + 0x28));
  this_00 = (QGuiApplication *)QCoreApplication::instance();
  pQVar1 = QGuiApplication::
           nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
                     (this_00);
  if (pQVar1 != (QX11Application *)0x0) {
    uVar2 = (**(code **)(*(long *)pQVar1 + 0x18))(pQVar1);
    *(undefined8 *)(this + 0x10) = uVar2;
  }
  if (*(long *)(this + 0x10) != 0) {
    internAtoms(this);
  }
  pQVar3 = (QObject *)QCoreApplication::instance();
  QObject::installEventFilter(pQVar3);
  return;
}



// ==== 001a31fc  WindowTyper::eventFilter

/* WindowTyper::eventFilter(QObject*, QEvent*) */

void __thiscall WindowTyper::eventFilter(WindowTyper *this,QObject *param_1,QEvent *param_2)

{
  char cVar1;
  int iVar2;
  QWindow *pQVar3;
  
  iVar2 = QEvent::type(param_2);
  if (iVar2 == 0xce) {
    pQVar3 = qobject_cast<QWindow*>(param_1);
    if (pQVar3 != (QWindow *)0x0) {
      cVar1 = QWindow::isTopLevel();
      if (cVar1 != '\0') {
        stamp(this,pQVar3);
      }
    }
  }
  QObject::eventFilter((QObject *)this,(QEvent *)param_1);
  return;
}



// ==== 001a327c  WindowTyper::internAtoms()::{lambda(char_const*,char_const*)#1}::operator()

/* WindowTyper::internAtoms()::{lambda(char const*, char const*)#1}::TEMPNAMEPLACEHOLDERVALUE(char
   const*, char const*) const */

void __thiscall
WindowTyper::internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
          (_lambda_char_const__char_const___1_ *this,char *param_1,char *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  char *local_68;
  _lambda_char_const__char_const___1_ *local_60;
  uint local_4c;
  undefined8 local_48;
  undefined8 local_40;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = *(long *)this;
  local_68 = param_1;
  local_60 = this;
  local_4c = intern(*(WindowTyper **)this,param_2);
  QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_48,&local_68);
  QString::fromLatin1(local_38,local_48,local_40);
  QHash<QString,unsigned_int>::insert
            ((QHash<QString,unsigned_int> *)(lVar1 + 0x20),local_38,&local_4c);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a3358  WindowTyper::internAtoms

/* WindowTyper::internAtoms() */

void __thiscall WindowTyper::internAtoms(WindowTyper *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  WindowTyper *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar1 = intern(this,"_NET_WM_WINDOW_TYPE");
  *(undefined4 *)(this + 0x18) = uVar1;
  local_18 = this;
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"desktop",
             "_NET_WM_WINDOW_TYPE_DESKTOP");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"toppanel","_NET_WM_WINDOW_TYPE_DOCK")
  ;
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"bottompanel",
             "_NET_WM_WINDOW_TYPE_DOCK");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"dock","_NET_WM_WINDOW_TYPE_DOCK");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"expose","_NET_WM_WINDOW_TYPE_UTILITY"
            );
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"fadecurtain",
             "_NET_WM_WINDOW_TYPE_SPLASH");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"notification",
             "_NET_WM_WINDOW_TYPE_NOTIFICATION");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"tooltip",
             "_NET_WM_WINDOW_TYPE_TOOLTIP");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"menu",
             "_NET_WM_WINDOW_TYPE_POPUP_MENU");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"toolbar",
             "_NET_WM_WINDOW_TYPE_TOOLBAR");
  internAtoms()::{lambda(char_const*,char_const*)#1}::operator()
            ((_lambda_char_const__char_const___1_ *)&local_18,"dialog","_NET_WM_WINDOW_TYPE_DIALOG")
  ;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a34ee  WindowTyper::intern

/* WindowTyper::intern(char const*) */

undefined4 __thiscall WindowTyper::intern(WindowTyper *this,char *param_1)

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



// ==== 001a3630  WindowTyper::roleOf

/* WindowTyper::roleOf(QWindow*) const */

QWindow * WindowTyper::roleOf(QWindow *param_1)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  char *pcVar8;
  long *in_RDX;
  long in_RSI;
  long in_FS_OFFSET;
  undefined4 local_64;
  undefined8 local_60;
  QString local_58 [32];
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::objectName();
  QString::toLower(local_58);
  QString::~QString((QString *)local_38);
  cVar2 = QString::isEmpty(local_58);
  if (cVar2 == '\x01') {
LAB_001a36bb:
    bVar1 = false;
  }
  else {
    cVar2 = QHash<QString,unsigned_int>::contains
                      ((QHash<QString,unsigned_int> *)(in_RSI + 0x20),local_58);
    if (cVar2 == '\0') goto LAB_001a36bb;
    bVar1 = true;
  }
  if (bVar1) {
    QString::QString((QString *)param_1,local_58);
    goto LAB_001a3898;
  }
  local_64 = QWindow::flags();
  uVar3 = QFlags<Qt::WindowType>::operator&((QFlags<Qt::WindowType> *)&local_64,0x4000000);
  local_38[0] = CONCAT44(local_38[0]._4_4_,uVar3);
  uVar4 = QFlags::operator_cast_to_unsigned_int((QFlags *)local_38);
  if (uVar4 != 0) {
    QString::QString((QString *)param_1,"desktop");
    goto LAB_001a3898;
  }
  uVar3 = QFlags<Qt::WindowType>::operator&((QFlags<Qt::WindowType> *)&local_64,0x80000);
  local_38[0] = CONCAT44(local_38[0]._4_4_,uVar3);
  uVar4 = QFlags::operator_cast_to_unsigned_int((QFlags *)local_38);
  if (uVar4 != 0) {
    QString::QString((QString *)param_1,"expose");
    goto LAB_001a3898;
  }
  uVar3 = QFlags<Qt::WindowType>::operator&((QFlags<Qt::WindowType> *)&local_64,0x40000);
  local_38[0] = CONCAT44(local_38[0]._4_4_,uVar3);
  uVar4 = QFlags::operator_cast_to_unsigned_int((QFlags *)local_38);
  if (uVar4 == 0) {
    QString::QString((QString *)param_1);
    goto LAB_001a3898;
  }
  local_60 = (**(code **)(*in_RDX + 0x70))(in_RDX);
  lVar7 = QWindow::screen();
  if (lVar7 == 0) {
    local_38[0] = local_60;
  }
  else {
    QWindow::screen();
    local_38[0] = QScreen::size();
  }
  iVar5 = QSize::height((QSize *)&local_60);
  iVar6 = QSize::height((QSize *)local_38);
  if (iVar5 < iVar6 / 3) {
LAB_001a3856:
    bVar1 = true;
  }
  else {
    iVar5 = QSize::width((QSize *)&local_60);
    iVar6 = QSize::width((QSize *)local_38);
    if (iVar5 < iVar6 / 3) goto LAB_001a3856;
    bVar1 = false;
  }
  if (bVar1) {
    pcVar8 = "dock";
  }
  else {
    pcVar8 = "fadecurtain";
  }
  QString::QString((QString *)param_1,pcVar8);
LAB_001a3898:
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001a3920  WindowTyper::stamp

/* WindowTyper::stamp(QWindow*) */

void __thiscall WindowTyper::stamp(WindowTyper *this,QWindow *param_1)

{
  uint uVar1;
  long in_FS_OFFSET;
  QWindow *local_58;
  WindowTyper *local_50;
  uint local_44 [3];
  QWindow local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_58 = param_1;
  local_50 = this;
  roleOf(local_38);
  local_44[1] = 0;
  local_44[0] = QHash<QString,unsigned_int>::value
                          ((QHash<QString,unsigned_int> *)(local_50 + 0x20),(QString *)local_38,
                           local_44 + 1);
  if ((((local_44[0] != 0) && (*(int *)(local_50 + 0x18) != 0)) &&
      (uVar1 = QHash<QWindow*,unsigned_int>::value
                         ((QHash<QWindow*,unsigned_int> *)(local_50 + 0x28),&local_58),
      uVar1 != local_44[0])) && (local_44[2] = QWindow::winId(), local_44[2] != 0)) {
    xcb_change_property(*(undefined8 *)(local_50 + 0x10),0,local_44[2],
                        *(undefined4 *)(local_50 + 0x18),4,0x20,1,local_44);
    xcb_flush(*(undefined8 *)(local_50 + 0x10));
    QHash<QWindow*,unsigned_int>::insert
              ((QHash<QWindow*,unsigned_int> *)(local_50 + 0x28),&local_58,local_44);
  }
  QString::~QString((QString *)local_38);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a3b7a  WindowTyper::~WindowTyper

/* WindowTyper::~WindowTyper() */

void __thiscall WindowTyper::~WindowTyper(WindowTyper *this)

{
  *(undefined ***)this = &PTR_metaObject_0032ba10;
  QHash<QWindow*,unsigned_int>::~QHash((QHash<QWindow*,unsigned_int> *)(this + 0x28));
  QHash<QString,unsigned_int>::~QHash((QHash<QString,unsigned_int> *)(this + 0x20));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a3bc4  WindowTyper::~WindowTyper

/* WindowTyper::~WindowTyper() */

void __thiscall WindowTyper::~WindowTyper(WindowTyper *this)

{
  ~WindowTyper(this);
  operator_delete(this,0x30);
  return;
}


