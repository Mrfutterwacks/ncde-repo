// Ghidra decompile of LaPivot.oracle — class/namespace main (5 functions). Raw; not source.

// ==== 001f3aa0  main::{lambda()#1}::operator()

/* main::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall main::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  int *piVar2;
  long in_FS_OFFSET;
  int local_84;
  int local_80;
  int local_7c;
  QVariant local_78 [32];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::property((char *)local_58);
  local_84 = ::QVariant::toInt((bool *)local_58);
  ::QVariant::~QVariant(local_58);
  cVar1 = Lelan::onBattery(*(Lelan **)(this + 0x10));
  if (cVar1 == '\0') {
    QObject::property((char *)local_58);
    local_80 = ::QVariant::toInt((bool *)local_58);
    ::QVariant::~QVariant(local_58);
  }
  else {
    QObject::property((char *)local_78);
    local_80 = ::QVariant::toInt((bool *)local_78);
    ::QVariant::~QVariant(local_78);
  }
  if ((local_84 < 1) || (local_80 < 1)) {
    piVar2 = qMax<int>(&local_84,&local_80);
    local_7c = *piVar2;
  }
  else {
    piVar2 = qMin<int>(&local_84,&local_80);
    local_7c = *piVar2;
  }
  NCDEWindowManager::setScreensaverTimeoutMs
            (*(NCDEWindowManager **)(this + 8),(long)local_7c * 60000);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f3cba  main::{lambda()#2}::operator()

/* main::{lambda()#2}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall main::{lambda()#2}::operator()(_lambda___2_ *this)

{
  Settings *this_00;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(Settings **)this;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"auto",4);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  Settings::previewScreensaver(this_00,local_38);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f3d94  main::{lambda(int,bool)#1}::operator()

/* main::{lambda(int, bool)#1}::TEMPNAMEPLACEHOLDERVALUE(int, bool) const */

void __thiscall
main::{lambda(int,bool)#1}::operator()(_lambda_int_bool__1_ *this,int param_1,bool param_2)

{
  Settings *this_00;
  bool bVar1;
  char cVar2;
  long lVar3;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_68 [32];
  QMessageLogger local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((param_2) || (param_1 != 0)) {
    cVar2 = NCDEWindowManager::screensaverIdleActive(*(NCDEWindowManager **)(this + 8));
    if (cVar2 != '\x01') goto LAB_001f3dde;
    bVar1 = false;
  }
  else {
LAB_001f3dde:
    bVar1 = true;
  }
  if (bVar1) goto LAB_001f3f45;
  cVar2 = QElapsedTimer::isValid();
  if (cVar2 == '\x01') {
    lVar3 = QElapsedTimer::elapsed();
    if (60000 < lVar3) goto LAB_001f3e1f;
    bVar1 = false;
  }
  else {
LAB_001f3e1f:
    bVar1 = true;
  }
  if (bVar1) {
    QElapsedTimer::restart();
    operator()(int,bool)::relaunches = 0;
  }
  operator()(int,bool)::relaunches = operator()(int,bool)::relaunches + 1;
  if (operator()(int,bool)::relaunches < 4) {
    this_00 = *(Settings **)this;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_68,(QTypedArrayData *)0x0,L"auto",4);
    QString::QString((QString *)local_48,(QArrayDataPointer *)local_68);
    Settings::previewScreensaver(this_00,(QString *)local_48);
    QString::~QString((QString *)local_48);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_68);
  }
  else {
    QMessageLogger::QMessageLogger(local_48,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning
              ((char *)local_48,"screensaver: crash-looping, giving up this idle period");
  }
LAB_001f3f45:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f3f60  main::{lambda()#3}::operator()

/* main::{lambda()#3}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall main::{lambda()#3}::operator()(_lambda___3_ *this)

{
  CursorManager *this_00;
  QGuiApplication *this_01;
  undefined8 uVar1;
  int *piVar2;
  long in_FS_OFFSET;
  int local_6c;
  int local_68 [2];
  QX11Application *local_60;
  xcb_connection_t *local_58;
  uint *local_50;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_01 = (QGuiApplication *)QCoreApplication::instance();
  local_60 = QGuiApplication::
             nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
                       (this_01);
  if (local_60 != (QX11Application *)0x0) {
    local_58 = (xcb_connection_t *)(**(code **)(*(long *)local_60 + 0x18))(local_60);
    if (local_58 != (xcb_connection_t *)0x0) {
      uVar1 = xcb_get_setup(local_58);
      local_50 = (uint *)xcb_setup_roots_iterator(uVar1);
      if (local_50 != (uint *)0x0) {
        this_00 = *(CursorManager **)this;
        local_68[1] = 0x40;
        QObject::property((char *)local_48);
        local_68[0] = ::QVariant::toInt((bool *)local_48);
        local_6c = 0x18;
        piVar2 = qBound<int>(&local_6c,local_68,local_68 + 1);
        CursorManager::installAsRootCursor(this_00,local_58,*local_50,*piVar2);
        ::QVariant::~QVariant(local_48);
      }
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f40b0  main::{lambda()#4}::operator()

/* main::{lambda()#4}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall main::{lambda()#4}::operator()(_lambda___4_ *this)

{
  XSettingsManager *this_00;
  int *piVar1;
  long in_FS_OFFSET;
  int local_54;
  int local_50 [2];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(XSettingsManager **)this;
  local_50[1] = 0x40;
  QObject::property((char *)local_48);
  local_50[0] = ::QVariant::toInt((bool *)local_48);
  local_54 = 0x18;
  piVar1 = qBound<int>(&local_54,local_50,local_50 + 1);
  XSettingsManager::setCursorSize(this_00,*piVar1);
  ::QVariant::~QVariant(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


