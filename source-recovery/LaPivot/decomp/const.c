// Ghidra decompile of LaPivot.oracle — class/namespace const (40 functions). Raw; not source.

// ==== 00151406  const::{lambda()#1}::operator()

/* QByteArray::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 00151b5c  const::{lambda()#1}::operator()

/* QString::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 0015a996  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()

/* GliaSystemMenus::places() const::{lambda(QStandardPaths::StandardLocation, QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QStandardPaths::StandardLocation, QString const&) const */

_func_places * __thiscall
const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
          (_lambda_QStandardPaths__StandardLocation_QString_const___1_ *this,undefined4 param_2,
          QString *param_3)

{
  QList<QVariant> *this_00;
  bool bVar1;
  bool bVar2;
  char cVar3;
  QVariant *pQVar4;
  long in_FS_OFFSET;
  undefined8 local_90;
  QString local_88 [32];
  QDir local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QStandardPaths::writableLocation(local_88,param_2);
  bVar1 = false;
  cVar3 = QString::isEmpty(local_88);
  if (cVar3 != '\x01') {
    QDir::QDir(local_68,local_88);
    bVar1 = true;
    cVar3 = QDir::exists();
    if (cVar3 != '\0') {
      bVar2 = true;
      goto LAB_0015aa29;
    }
  }
  bVar2 = false;
LAB_0015aa29:
  if (bVar1) {
    QDir::~QDir(local_68);
  }
  if (bVar2) {
    local_90 = 0;
    ::QVariant::QVariant(local_48,param_3);
    QString::QString((QString *)local_68,"name");
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_90,(QString *)local_68);
    ::QVariant::operator=(pQVar4,local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,local_88);
    QString::QString((QString *)local_68,"path");
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_90,(QString *)local_68);
    ::QVariant::operator=(pQVar4,local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::~QVariant(local_48);
    this_00 = *(QList<QVariant> **)this;
    ::QVariant::QVariant(local_48,(QMap *)&local_90);
    QList<QVariant>::append(this_00,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_90);
  }
  QString::~QString(local_88);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_places *)0x0;
}



// ==== 0015aece  const::{lambda()#1}::operator()

/* QList<QVariant>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 0016424e  const::{lambda()#1}::operator()

/* QList<QString>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 00168bd2  const::{lambda()#1}::operator()

/* QList<NCDEEngine::Sample>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 001791b2  const::{lambda()#1}::operator()

/* QList<unsigned int>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 001ab95c  const::{lambda()#1}::operator()

/* QList<NCDEWindowManager::WindowEntry>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 001af068  const::{lambda()#1}::operator()

/* QList<AppMenuModel::AppEntry>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 001b1a2c  const::{lambda()#1}::operator()

/* QList<CalendarBackend::Snapshot>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 001f82a8  const::{lambda(void*)#1}::operator()

/* QtMetaContainerPrivate::Sequence::at(long long)
   const::{lambda(void*)#1}::TEMPNAMEPLACEHOLDERVALUE(void*) const */

_func_at_long_long * __thiscall
const::{lambda(void*)#1}::operator()(_lambda_void___1_ *this,void *param_1)

{
  void *pvVar1;
  char cVar2;
  longlong lVar3;
  _func_at_long_long *p_Var4;
  void *pvVar5;
  
  cVar2 = QMetaSequence::canGetValueAtIndex();
  if (cVar2 == '\0') {
    QtPrivate::warnSynthesizedIterableAccess(1);
    pvVar5 = *(void **)this;
    QtPrivate::QConstPreservingPointer<void,unsigned_short>::constPointer
              ((QConstPreservingPointer<void,unsigned_short> *)(*(long *)(this + 8) + 8));
    pvVar5 = (void *)QMetaContainer::constBegin(pvVar5);
    QMetaContainer::advanceConstIterator(*(void **)this,(longlong)pvVar5);
    QMetaSequence::valueAtConstIterator(*(void **)this,pvVar5);
    p_Var4 = (_func_at_long_long *)QMetaContainer::destroyConstIterator(*(void **)this);
  }
  else {
    pvVar5 = *(void **)this;
    pvVar1 = (void *)**(undefined8 **)(this + 0x10);
    lVar3 = QIterable<QMetaSequence>::constIterable(*(QIterable<QMetaSequence> **)(this + 8));
    p_Var4 = (_func_at_long_long *)QMetaSequence::valueAtIndex(pvVar5,lVar3,pvVar1);
  }
  return p_Var4;
}



// ==== 00200ce0  const::{lambda()#1}::operator()

/* QList<QObject*>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 0020bdda  const::{lambda()#1}::operator()

/* QList<std::function<void ()> >::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 0021a8c8  const::{lambda()#1}::operator()

/* Lelan::subscribeToWifi()::{lambda()#2}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char *pcVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_120 [8];
  QString local_118 [8];
  QString local_110 [8];
  wchar16 *local_108;
  undefined *local_100;
  wchar16 *local_f8;
  wchar16 *local_f0;
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  undefined8 local_68 [4];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_120,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  bVar2 = false;
  cVar4 = QDBusPendingCall::isValid();
  if (cVar4 == '\x01') {
    QDBusPendingReply<QVariant>::value(local_48);
    bVar2 = true;
    iVar5 = ::QVariant::toUInt((bool *)local_48);
    if (iVar5 == 2) {
      bVar3 = false;
      goto LAB_0021a97a;
    }
  }
  bVar3 = true;
LAB_0021a97a:
  if (bVar2) {
    ::QVariant::~QVariant((QVariant *)local_48);
  }
  if (!bVar3) {
    ::QString::operator=((QString *)(*(long *)this + 0xd0),(QString *)(this + 0x10));
    QDBusConnection::systemBus();
    local_100 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_68,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager",0x1e);
    ::QString::QString(local_e8,(QArrayDataPointer *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_68);
    pcVar1 = *(char **)this;
    local_108 = L"PropertiesChanged";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"PropertiesChanged",0x11);
    ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
    ::QString::QString((QString *)local_68,FDPROPS);
    QDBusConnection::connect
              (local_118,local_e8,(QString *)(this + 0x10),(QString *)local_68,(QObject *)local_88,
               pcVar1);
    ::QString::~QString((QString *)local_68);
    ::QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    local_f0 = L"RequestScan";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"RequestScan",0xb);
    ::QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    local_f8 = L"org.freedesktop.NetworkManager.Device.Wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.Device.Wireless",
               0x2e);
    ::QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QDBusMessage::createMethodCall(local_110,local_e8,(QString *)(this + 0x10),(QString *)local_a8);
    ::QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
    local_68[0] = 0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_68);
    ::QVariant::QVariant((QVariant *)local_48,(QMap *)local_68);
    QDBusMessage::operator<<((QDBusMessage *)local_110,(QVariant *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_118);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    Lelan::rebuildAccessPoints(*(Lelan **)this);
    Lelan::readActiveNetwork(*(Lelan **)this);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_110);
    ::QString::~QString(local_e8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_118);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_120);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0021adee  const::{lambda()#1}::~subscribeToWifi

/* ~subscribeToWifi() */

void __thiscall const::{lambda()#1}::~subscribeToWifi(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 0021bd5c  const::{lambda()#1}::operator()

/* Lelan::rebuildAccessPoints()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QList<QVariant> *this_00;
  long lVar1;
  operator()(_ *this_01;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  char cVar12;
  bool bVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  QVariant *pQVar18;
  QMap *pQVar19;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_208 [8];
  undefined8 local_200;
  undefined8 local_1f8;
  undefined8 local_1f0;
  QVariant local_1e8 [8];
  undefined8 local_1e0;
  undefined8 local_1d8;
  QList<QVariant> *local_1d0;
  undefined8 local_1c8;
  wchar16 *local_1c0;
  wchar16 *local_1b8;
  wchar16 *local_1b0;
  wchar16 *local_1a8;
  wchar16 *local_1a0;
  wchar16 *local_198;
  wchar16 *local_190;
  wchar16 *local_188;
  wchar16 *local_180;
  wchar16 *local_178;
  wchar16 *local_170;
  QVariant local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  undefined8 local_128 [4];
  undefined8 local_108 [4];
  QString local_e8 [16];
  undefined8 local_d8;
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_208,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar12 = QDBusPendingCall::isValid();
  if (cVar12 != '\0') {
    QDBusPendingReply<QMap<QString,QVariant>>::value
              ((QDBusPendingReply<QMap<QString,QVariant>> *)&local_1e0);
    ::QVariant::QVariant(local_88);
    local_1c0 = L"WpaFlags";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"WpaFlags",8);
    ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QMap<QString,QVariant>::value(local_68,(QVariant *)&local_1e0);
    iVar14 = ::QVariant::toUInt((bool *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    ::QVariant::QVariant(local_88);
    local_1b8 = L"RsnFlags";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"RsnFlags",8);
    ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QMap<QString,QVariant>::value(local_68,(QVariant *)&local_1e0);
    iVar15 = ::QVariant::toUInt((bool *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    ::QVariant::QVariant(local_88);
    local_1b0 = L"Ssid";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Ssid",4);
    ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QMap<QString,QVariant>::value(local_68,(QVariant *)&local_1e0);
    ay2str(local_168);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    cVar12 = ::QString::isEmpty((QString *)local_168);
    if (cVar12 != '\x01') {
      local_1d8 = 0;
      ::QVariant::QVariant((QVariant *)local_68,(QString *)local_168);
      local_1a8 = L"ssid";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"ssid",4);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      pQVar18 = (QVariant *)
                QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1d8,local_e8);
      ::QVariant::operator=(pQVar18,(QVariant *)local_68);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QVariant::QVariant(local_a8);
      local_1a0 = L"Strength";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Strength",8);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      QMap<QString,QVariant>::value((QString *)local_88,(QVariant *)&local_1e0);
      uVar16 = ::QVariant::toUInt((bool *)local_88);
      ::QVariant::QVariant((QVariant *)local_68,uVar16);
      local_198 = L"signal";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"signal",6);
      ::QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
      pQVar18 = (QVariant *)
                QMap<QString,QVariant>::operator[]
                          ((QMap<QString,QVariant> *)&local_1d8,(QString *)local_128);
      ::QVariant::operator=(pQVar18,(QVariant *)local_68);
      ::QString::~QString((QString *)local_128);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QVariant::~QVariant(local_88);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant(local_a8);
      ::QVariant::QVariant((QVariant *)local_68,iVar14 != 0 || iVar15 != 0);
      local_190 = L"secured";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"secured",7);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      pQVar18 = (QVariant *)
                QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1d8,local_e8);
      ::QVariant::operator=(pQVar18,(QVariant *)local_68);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant((QVariant *)local_68);
      bVar13 = (bool)::operator==((QString *)(this + 0x10),
                                  (QString *)(*(long *)(this + 0x28) + 0x20));
      ::QVariant::QVariant((QVariant *)local_68,bVar13);
      local_188 = L"connected";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"connected",9);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      pQVar18 = (QVariant *)
                QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1d8,local_e8);
      ::QVariant::operator=(pQVar18,(QVariant *)local_68);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant((QVariant *)local_68);
      this_00 = *(QList<QVariant> **)(this + 0x28);
      ::QVariant::QVariant((QVariant *)local_68,(QMap *)&local_1d8);
      QList<QVariant>::append(this_00,(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1d8);
    }
    ::QString::~QString((QString *)local_168);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1e0);
  }
  lVar1 = *(long *)(this + 0x28);
  *(int *)(lVar1 + 0x18) = *(int *)(lVar1 + 0x18) + -1;
  if (*(int *)(lVar1 + 0x18) == 0) {
    local_200 = 0;
    local_1d0 = *(QList<QVariant> **)(this + 0x28);
    local_1f8 = QList<QVariant>::begin(local_1d0);
    local_1f0 = QList<QVariant>::end(local_1d0);
    while( true ) {
      cVar12 = QList<QVariant>::iterator::operator!=((iterator *)&local_1f8,local_1f0);
      if (cVar12 == '\0') break;
      local_1c8 = QList<QVariant>::iterator::operator*((iterator *)&local_1f8);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_88);
      local_180 = L"ssid";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"ssid",4);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      QMap<QString,QVariant>::value(local_68,local_1e8);
      ::QVariant::toString();
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant(local_88);
      bVar4 = false;
      bVar3 = false;
      bVar2 = false;
      bVar13 = false;
      bVar11 = false;
      bVar10 = false;
      bVar9 = false;
      bVar8 = false;
      bVar7 = false;
      bVar6 = false;
      cVar12 = QMap<QString,QMap<QString,QVariant>>::contains
                         ((QMap<QString,QMap<QString,QVariant>> *)&local_200,(QString *)local_168);
      if (cVar12 == '\x01') {
        ::QVariant::QVariant(local_c8);
        bVar4 = true;
        local_178 = L"signal";
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"signal",6)
        ;
        bVar3 = true;
        ::QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
        bVar2 = true;
        QMap<QString,QVariant>::value((QString *)local_a8,local_1e8);
        bVar13 = true;
        uVar16 = ::QVariant::toUInt((bool *)local_a8);
        local_1e0 = 0;
        QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)&local_1e0);
        bVar11 = true;
        QMap<QString,QMap<QString,QVariant>>::value((QString *)&local_1d8,(QMap *)&local_200);
        bVar10 = true;
        ::QVariant::QVariant(local_88);
        bVar9 = true;
        local_170 = L"signal";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"signal",6);
        bVar8 = true;
        ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
        bVar7 = true;
        QMap<QString,QVariant>::value(local_68,(QVariant *)&local_1d8);
        bVar6 = true;
        uVar17 = ::QVariant::toUInt((bool *)local_68);
        if (uVar17 < uVar16) goto LAB_0021c7bd;
        bVar5 = false;
      }
      else {
LAB_0021c7bd:
        bVar5 = true;
      }
      if (bVar6) {
        ::QVariant::~QVariant((QVariant *)local_68);
      }
      if (bVar7) {
        ::QString::~QString(local_e8);
      }
      if (bVar8) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      }
      if (bVar9) {
        ::QVariant::~QVariant(local_88);
      }
      if (bVar10) {
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1d8);
      }
      if (bVar11) {
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1e0);
      }
      if (bVar13) {
        ::QVariant::~QVariant(local_a8);
      }
      if (bVar2) {
        ::QString::~QString((QString *)local_128);
      }
      if (bVar3) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
      }
      if (bVar4) {
        ::QVariant::~QVariant(local_c8);
      }
      if (bVar5) {
        QMap<QString,QMap<QString,QVariant>>::insert
                  ((QMap<QString,QMap<QString,QVariant>> *)&local_200,(QString *)local_168,
                   (QMap *)local_1e8);
      }
      ::QString::~QString((QString *)local_168);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1e8);
      QList<QVariant>::iterator::operator++((iterator *)&local_1f8);
    }
    local_e8[0] = (QString)0x0;
    local_e8[1] = (QString)0x0;
    local_e8[2] = (QString)0x0;
    local_e8[3] = (QString)0x0;
    local_e8[4] = (QString)0x0;
    local_e8[5] = (QString)0x0;
    local_e8[6] = (QString)0x0;
    local_e8[7] = (QString)0x0;
    local_e8[8] = (QString)0x0;
    local_e8[9] = (QString)0x0;
    local_e8[10] = (QString)0x0;
    local_e8[0xb] = (QString)0x0;
    local_e8[0xc] = (QString)0x0;
    local_e8[0xd] = (QString)0x0;
    local_e8[0xe] = (QString)0x0;
    local_e8[0xf] = (QString)0x0;
    local_d8 = 0;
    local_128[0] = QMap<QString,QMap<QString,QVariant>>::constBegin
                             ((QMap<QString,QMap<QString,QVariant>> *)&local_200);
    while( true ) {
      local_108[0] = QMap<QString,QMap<QString,QVariant>>::constEnd
                               ((QMap<QString,QMap<QString,QVariant>> *)&local_200);
      cVar12 = ::operator!=((const_iterator *)local_128,(const_iterator *)local_108);
      if (cVar12 == '\0') break;
      pQVar19 = (QMap *)QMap<QString,QMap<QString,QVariant>>::const_iterator::value
                                  ((const_iterator *)local_128);
      ::QVariant::QVariant((QVariant *)local_68,pQVar19);
      QList<QVariant>::append((QList<QVariant> *)local_e8,(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
      QMap<QString,QMap<QString,QVariant>>::const_iterator::operator++((const_iterator *)local_128);
    }
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0xa8),(QList *)local_e8);
    this_01 = *(operator()(_ **)(this + 0x28);
    if (this_01 != (operator()(_ *)0x0) {
      Lelan::rebuildAccessPoints()::{lambda()#1}::operator()()::~ApAccum(this_01);
      operator_delete(this_01,0x38);
    }
    Lelan::scheduleWifiChanged(*(Lelan **)this);
    QList<QVariant>::~QList((QList<QVariant> *)local_e8);
    QMap<QString,QMap<QString,QVariant>>::~QMap((QMap<QString,QMap<QString,QVariant>> *)&local_200);
  }
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_208);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 0021ce3c  const::{lambda()#1}::~rebuildAccessPoints

/* ~rebuildAccessPoints() */

void __thiscall const::{lambda()#1}::~rebuildAccessPoints(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x30));
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 0021daa4  const::{lambda()#1}::operator()

/* Lelan::readActiveNetwork()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  QVariant *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_b8 [8];
  wchar16 *local_b0;
  QVariant local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_b8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 != '\0') {
    QDBusPendingReply<QVariant>::value(local_48);
    ay2str(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    ::QVariant::QVariant((QVariant *)local_48,(QString *)local_a8);
    lVar1 = *(long *)this;
    local_b0 = L"ssid";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"ssid",4);
    ::QString::QString(local_68,(QArrayDataPointer *)local_88);
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0xc0),local_68);
    ::QVariant::operator=(this_00,(QVariant *)local_48);
    ::QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    Lelan::scheduleWifiChanged(*(Lelan **)this);
    Lelan::syncWifiConnectedFlag(*(Lelan **)this,(QString *)local_a8);
    ::QString::~QString((QString *)local_a8);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 0021dce0  const::{lambda()#2}::operator()

/* Lelan::readActiveNetwork()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#2}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#2}::operator()(_lambda___2_ *this)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  QVariant *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_b8 [8];
  wchar16 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QDBusPendingReply<QVariant> local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_b8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 != '\0') {
    QDBusPendingReply<QVariant>::value(local_68);
    uVar3 = ::QVariant::toUInt((bool *)local_68);
    ::QVariant::QVariant(local_48,uVar3 / 1000);
    lVar1 = *(long *)this;
    local_b0 = L"speed";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"speed",5);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0xc0),local_88);
    ::QVariant::operator=(this_00,local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    ::QVariant::~QVariant((QVariant *)local_68);
    Lelan::scheduleWifiChanged(*(Lelan **)this);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 0021deea  const::{lambda()#1}::operator()

/* Lelan::readActiveNetwork()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#3}::TEMPNAMEPLACEHOLDERVALUE() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  QVariant *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_110 [8];
  QVariant local_108 [8];
  undefined8 local_100;
  wchar16 *local_f8;
  undefined *local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_110,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QVariant>::value(local_48);
    ::QVariant::value<QDBusArgument>(local_108);
    ::QVariant::~QVariant((QVariant *)local_48);
    local_e8 = 0;
    local_e0 = 0;
    local_d8 = 0;
    QDBusArgument::beginArray();
    cVar2 = QDBusArgument::atEnd();
    if (cVar2 != '\x01') {
      local_100 = 0;
      ::operator>>((QDBusArgument *)local_108,(QMap *)&local_100);
      ::QVariant::QVariant(local_68);
      local_f8 = L"address";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"address",7);
      ::QString::QString(local_a8,(QArrayDataPointer *)local_c8);
      QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)&local_100);
      ::QVariant::toString();
      ::QString::operator=((QString *)&local_e8,local_88);
      ::QString::~QString(local_88);
      ::QVariant::~QVariant((QVariant *)local_48);
      ::QString::~QString(local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
      ::QVariant::~QVariant(local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_100);
    }
    QDBusArgument::endArray();
    cVar2 = ::QString::isEmpty((QString *)&local_e8);
    if (cVar2 != '\x01') {
      ::QVariant::QVariant((QVariant *)local_48,(QString *)&local_e8);
      lVar1 = *(long *)this;
      local_f0 = &DAT_002ab07e;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_a8,(QTypedArrayData *)0x0,L"ip",2);
      ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
      this_00 = (QVariant *)
                QMap<QString,QVariant>::operator[]
                          ((QMap<QString,QVariant> *)(lVar1 + 0xc0),local_88);
      ::QVariant::operator=(this_00,(QVariant *)local_48);
      ::QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_a8);
      ::QVariant::~QVariant((QVariant *)local_48);
      Lelan::scheduleWifiChanged(*(Lelan **)this);
    }
    ::QString::~QString((QString *)&local_e8);
    QDBusArgument::~QDBusArgument((QDBusArgument *)local_108);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_110);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0021e320  const::{lambda()#3}::operator()

/* WARNING: Removing unreachable block (ram,0x0021e6e9) */
/* Lelan::readActiveNetwork()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#3}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#3}::operator()(_lambda___3_ *this)

{
  QObject *pQVar1;
  bool bVar2;
  char cVar3;
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_158 [8];
  QString local_150 [8];
  QDBusPendingCallWatcher *local_148;
  undefined *local_140;
  wchar16 *local_138;
  wchar16 *local_130;
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  undefined8 local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QDBusPendingReply<QVariant> local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_158,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 != '\x01') goto LAB_0021e7a5;
  QDBusPendingReply<QVariant>::value(local_68);
  qvariant_cast<QDBusObjectPath>((QVariant *)&local_a8);
  QDBusObjectPath::path();
  QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)&local_a8);
  ::QVariant::~QVariant((QVariant *)local_68);
  cVar3 = QString::isEmpty(local_128);
  if (cVar3 == '\0') {
    QLatin1String::QLatin1String((QLatin1String *)&local_a8,"/");
    cVar3 = ::operator==(local_128,(QLatin1String *)&local_a8);
    if (cVar3 != '\0') goto LAB_0021e447;
    bVar2 = false;
  }
  else {
LAB_0021e447:
    bVar2 = true;
  }
  if (!bVar2) {
    local_140 = &DAT_002aae2a;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Get",3);
    QString::QString(local_c8,(QArrayDataPointer *)local_e8);
    QString::QString((QString *)&local_a8,FDPROPS);
    QDBusMessage::createMethodCall
              (local_150,(QString *)(this + 0x10),local_128,(QString *)&local_a8);
    QString::~QString((QString *)&local_a8);
    QString::~QString(local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    local_138 = L"org.freedesktop.NetworkManager.IP4Config";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.IP4Config",0x28);
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant(local_88,(QString *)local_e8);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_150,local_88);
    local_130 = L"AddressData";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"AddressData",0xb);
    QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
    ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_a8);
    QDBusMessage::operator<<(this_00,(QVariant *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString((QString *)&local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    this_01 = operator_new(0x18);
    pQVar1 = *(QObject **)this;
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_c8);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher(this_01,(QDBusPendingCall *)&local_a8,pQVar1);
    local_148 = this_01;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_c8);
    local_a8 = *(undefined8 *)this;
    local_a0 = local_148;
    QObject::operator()(local_c8,local_148,QDBusPendingCallWatcher::finished,0,*(undefined8 *)this,
                        &local_a8,0);
    QMetaObject::Connection::~Connection((Connection *)local_c8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_150);
  }
  QString::~QString(local_128);
LAB_0021e7a5:
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_158);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 0021e926  const::{lambda()#3}::~readActiveNetwork

/* ~readActiveNetwork() */

void __thiscall const::{lambda()#3}::~readActiveNetwork(_lambda___3_ *this)

{
  QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 00222812  const::{lambda()#1}::operator()

/* Lelan::refreshVpnConnections()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QList<QVariant> *this_00;
  long lVar1;
  operator()(_ *this_01;
  bool bVar2;
  char cVar3;
  QVariant *pQVar4;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QMap<QString,QVariant>>> local_1d8 [8];
  QDBusPendingReply<QMap<QString,QMap<QString,QVariant>>> local_1d0 [8];
  QString local_1c8 [8];
  undefined8 local_1c0;
  undefined2 local_1b8 [4];
  wchar16 *local_1b0;
  wchar16 *local_1a8;
  undefined *local_1a0;
  undefined *local_198;
  undefined *local_190;
  wchar16 *local_188;
  wchar16 *local_180;
  wchar16 *local_178;
  wchar16 *local_170;
  QString local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  undefined4 local_108 [8];
  undefined8 local_e8 [4];
  undefined8 local_c8 [4];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QMap<QString,QVariant>>>::QDBusPendingReply
            (local_1d8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 == '\0') goto LAB_00223089;
  QDBusPendingReply<QMap<QString,QMap<QString,QVariant>>>::value(local_1d0);
  local_c8[0] = 0;
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_c8);
  local_1b0 = L"connection";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"connection",10);
  ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QMap<QString,QVariant>>::value(local_1c8,(QMap *)local_1d0);
  ::QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
  ::QVariant::QVariant(local_68);
  local_1a8 = L"type";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"type",4);
  ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_1c8);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  QLatin1String::QLatin1String((QLatin1String *)local_a8,"vpn");
  cVar3 = ::operator==(local_168,(QLatin1String *)local_a8);
  if (cVar3 == '\0') {
    QLatin1String::QLatin1String((QLatin1String *)local_88,"wireguard");
    cVar3 = ::operator==(local_168,(QLatin1String *)local_88);
    if (cVar3 != '\0') goto LAB_00222a5b;
    bVar2 = false;
  }
  else {
LAB_00222a5b:
    bVar2 = true;
  }
  if (bVar2) {
    ::QVariant::QVariant(local_68);
    local_1a0 = &DAT_002ab202;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"id",2);
    ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_1c8);
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_48);
    ::QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QString::QString(local_128,local_168);
    local_198 = &DAT_002ab362;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"vpn",3);
    ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
    cVar3 = QMap<QString,QMap<QString,QVariant>>::contains
                      ((QMap<QString,QMap<QString,QVariant>> *)local_1d0,local_88);
    ::QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    if (cVar3 != '\0') {
      local_1c0 = 0;
      QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)&local_1c0);
      local_190 = &DAT_002ab362;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"vpn",3);
      ::QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
      QMap<QString,QMap<QString,QVariant>>::value((QString *)local_1b8,(QMap *)local_1d0);
      ::QVariant::QVariant(local_68);
      local_188 = L"service-type";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"service-type",0xc)
      ;
      ::QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_1b8);
      ::QVariant::toString();
      ::QString::operator=(local_128,local_88);
      ::QString::~QString(local_88);
      ::QVariant::~QVariant((QVariant *)local_48);
      ::QString::~QString((QString *)local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      ::QVariant::~QVariant(local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1b8);
      ::QString::~QString((QString *)local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1c0);
    }
    local_e8[0] = 0;
    ::QVariant::QVariant((QVariant *)local_48,local_148);
    local_180 = L"name";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"name",4);
    ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_e8,local_88);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    ::QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)local_108,0);
    QChar::QChar<char,true>((QChar *)local_1b8,'.');
    ::QString::section(local_88,local_128,local_1b8[0],0xffffffffffffffff,0xffffffffffffffff,
                       local_108[0]);
    ::QVariant::QVariant((QVariant *)local_48,local_88);
    local_178 = L"type";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"type",4);
    ::QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)local_e8,(QString *)local_a8);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    ::QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant((QVariant *)local_48);
    ::QString::~QString(local_88);
    ::QVariant::QVariant((QVariant *)local_48,false);
    local_170 = L"connected";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"connected",9);
    ::QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_e8,local_88);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    ::QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    this_00 = *(QList<QVariant> **)(this + 0x28);
    ::QVariant::QVariant((QVariant *)local_48,(QMap *)local_e8);
    QList<QVariant>::append(this_00,(QVariant *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QHash<QString,QString>::insert
              ((QHash<QString,QString> *)(*(long *)(this + 0x28) + 0x18),local_148,
               (QString *)(this + 0x10));
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_e8);
    ::QString::~QString(local_128);
    ::QString::~QString(local_148);
  }
  ::QString::~QString(local_168);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1c8);
  QMap<QString,QMap<QString,QVariant>>::~QMap((QMap<QString,QMap<QString,QVariant>> *)local_1d0);
LAB_00223089:
  lVar1 = *(long *)(this + 0x28);
  *(int *)(lVar1 + 0x20) = *(int *)(lVar1 + 0x20) + -1;
  if (*(int *)(lVar1 + 0x20) == 0) {
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0x108),*(QList **)(this + 0x28));
    QHash<QString,QString>::operator=
              ((QHash<QString,QString> *)(*(long *)this + 0x120),
               (QHash *)(*(long *)(this + 0x28) + 0x18));
    this_01 = *(operator()(_ **)(this + 0x28);
    if (this_01 != (operator()(_ *)0x0) {
      Lelan::refreshVpnConnections()::{lambda()#1}::operator()()::~VAcc(this_01);
      operator_delete(this_01,0x28);
    }
    Lelan::vpnStateChanged(*(Lelan **)this);
    Lelan::markActiveVpns(*(Lelan **)this);
  }
  QDBusPendingReply<QMap<QString,QMap<QString,QVariant>>>::~QDBusPendingReply(local_1d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 0022340a  const::{lambda()#1}::~refreshVpnConnections

/* ~refreshVpnConnections() */

void __thiscall const::{lambda()#1}::~refreshVpnConnections(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 0022401e  const::{lambda()#1}::operator()

/* Lelan::markActiveVpns()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  QVariant *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_1e8 [8];
  QDBusPendingReply<QMap<QString,QVariant>> local_1e0 [8];
  undefined8 local_1d8;
  undefined8 local_1d0;
  QVariant local_1c8 [8];
  QList<QVariant> *local_1c0;
  QVariant *local_1b8;
  undefined *local_1b0;
  undefined *local_1a8;
  wchar16 *local_1a0;
  wchar16 *local_198;
  wchar16 *local_190;
  QString local_188 [32];
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_1e8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar7 = QDBusPendingCall::isValid();
  if (cVar7 == '\x01') {
    QDBusPendingReply<QMap<QString,QVariant>>::value(local_1e0);
    ::QVariant::QVariant(local_88);
    local_1b0 = &DAT_002ab502;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"Vpn",3);
    ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QMap<QString,QVariant>::value(local_68,(QVariant *)local_1e0);
    cVar7 = ::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    ::QVariant::~QVariant(local_88);
    if (cVar7 == '\x01') {
      ::QVariant::QVariant(local_88);
      local_1a8 = &DAT_002ab50a;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"Id",2);
      ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
      QMap<QString,QVariant>::value(local_68,(QVariant *)local_1e0);
      ::QVariant::toString();
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QString::~QString(local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
      ::QVariant::~QVariant(local_88);
      bVar6 = false;
      local_1c0 = (QList<QVariant> *)(*(long *)this + 0x108);
      local_1d8 = QList<QVariant>::begin(local_1c0);
      local_1d0 = QList<QVariant>::end(local_1c0);
      while (cVar7 = QList<QVariant>::iterator::operator!=((iterator *)&local_1d8,local_1d0),
            cVar7 != '\0') {
        local_1b8 = (QVariant *)QList<QVariant>::iterator::operator*((iterator *)&local_1d8);
        ::QVariant::toMap();
        bVar3 = false;
        bVar2 = false;
        bVar1 = false;
        bVar5 = false;
        ::QVariant::QVariant(local_c8);
        local_1a0 = L"name";
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"name",4);
        ::QString::QString(local_148,(QArrayDataPointer *)local_168);
        QMap<QString,QVariant>::value(local_a8,local_1c8);
        ::QVariant::toString();
        cVar7 = ::operator==(local_128,local_188);
        if (cVar7 == '\0') {
LAB_00224454:
          bVar4 = false;
        }
        else {
          ::QVariant::QVariant(local_88);
          bVar3 = true;
          local_198 = L"connected";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    (local_108,(QTypedArrayData *)0x0,L"connected",9);
          bVar2 = true;
          ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
          bVar1 = true;
          QMap<QString,QVariant>::value(local_68,local_1c8);
          bVar5 = true;
          cVar7 = ::QVariant::toBool();
          if (cVar7 == '\x01') goto LAB_00224454;
          bVar4 = true;
        }
        if (bVar5) {
          ::QVariant::~QVariant((QVariant *)local_68);
        }
        if (bVar1) {
          ::QString::~QString(local_e8);
        }
        if (bVar2) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
        }
        if (bVar3) {
          ::QVariant::~QVariant(local_88);
        }
        ::QString::~QString(local_128);
        ::QVariant::~QVariant((QVariant *)local_a8);
        ::QString::~QString(local_148);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
        ::QVariant::~QVariant(local_c8);
        if (bVar4) {
          ::QVariant::QVariant((QVariant *)local_68,true);
          local_190 = L"connected";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    (local_108,(QTypedArrayData *)0x0,L"connected",9);
          ::QString::QString(local_e8,(QArrayDataPointer *)local_108);
          this_00 = (QVariant *)
                    QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_1c8,local_e8)
          ;
          ::QVariant::operator=(this_00,(QVariant *)local_68);
          ::QString::~QString(local_e8);
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
          ::QVariant::~QVariant((QVariant *)local_68);
          ::QVariant::QVariant((QVariant *)local_68,(QMap *)local_1c8);
          ::QVariant::operator=(local_1b8,(QVariant *)local_68);
          ::QVariant::~QVariant((QVariant *)local_68);
          bVar6 = true;
        }
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1c8);
        QList<QVariant>::iterator::operator++((iterator *)&local_1d8);
      }
      if (bVar6) {
        Lelan::vpnStateChanged(*(Lelan **)this);
      }
      ::QString::~QString(local_188);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1e0);
  }
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_1e8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00225be6  const::{lambda()#1}::operator()

/* Lelan::disconnectVpn(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_188 [8];
  QString local_180 [8];
  undefined *local_178;
  wchar16 *local_170;
  undefined *local_168;
  wchar16 *local_160;
  QArrayDataPointer<char16_t> local_158 [32];
  QString local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QDBusPendingReply<QVariant> local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_188,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  bVar2 = false;
  bVar1 = false;
  cVar4 = QDBusPendingCall::isValid();
  if (cVar4 != '\0') {
    QDBusPendingReply<QVariant>::value(local_58);
    bVar2 = true;
    ::QVariant::toString();
    bVar1 = true;
    cVar4 = ::operator==(local_78,(QString *)(this + 0x28));
    if (cVar4 != '\0') {
      bVar3 = true;
      goto LAB_00225cbe;
    }
  }
  bVar3 = false;
LAB_00225cbe:
  if (bVar1) {
    ::QString::~QString(local_78);
  }
  if (bVar2) {
    ::QVariant::~QVariant((QVariant *)local_58);
  }
  if (bVar3) {
    local_160 = L"DeactivateConnection";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_98,(QTypedArrayData *)0x0,L"DeactivateConnection",0x14);
    ::QString::QString(local_78,(QArrayDataPointer *)local_98);
    local_168 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_d8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    ::QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    local_170 = L"/org/freedesktop/NetworkManager";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_118,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager",0x1f);
    ::QString::QString(local_f8,(QArrayDataPointer *)local_118);
    local_178 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_158,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    ::QString::QString(local_138,(QArrayDataPointer *)local_158);
    QDBusMessage::createMethodCall(local_180,local_138,local_f8,local_b8);
    ::QString::~QString(local_138);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_158);
    ::QString::~QString(local_f8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
    ::QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    ::QString::~QString(local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_78,(QString *)(this + 0x10));
    ::QVariant::fromValue<QDBusObjectPath,true>((QVariant *)local_58,(QDBusObjectPath *)local_78);
    QDBusMessage::operator<<((QDBusMessage *)local_180,(QVariant *)local_58);
    ::QVariant::~QVariant((QVariant *)local_58);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_78);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_78,(int)local_98);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_78);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_98);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_180);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_188);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 002260ae  const::{lambda()#1}::~QString

/* ~QString() */

void __thiscall const::{lambda()#1}::~QString(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x28));
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 00228560  const::{lambda()#1}::subscribeToWifi

/* subscribeToWifi({lambda()#1}&&) */

void __thiscall const::{lambda()#1}::subscribeToWifi(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  return;
}



// ==== 00228658  const::{lambda()#1}::rebuildAccessPoints

/* rebuildAccessPoints({lambda()#1}&&) */

void __thiscall const::{lambda()#1}::rebuildAccessPoints(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  *(undefined8 *)(this + 0x28) = *(undefined8 *)(param_1 + 0x28);
  ::QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  return;
}



// ==== 00228854  const::{lambda()#3}::readActiveNetwork

/* readActiveNetwork({lambda()#3}&&) */

void __thiscall const::{lambda()#3}::readActiveNetwork(_lambda___3_ *this,_lambda___3_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  return;
}



// ==== 00228a54  const::{lambda()#1}::refreshVpnConnections

/* refreshVpnConnections({lambda()#1}&&) */

void __thiscall const::{lambda()#1}::refreshVpnConnections(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  *(undefined8 *)(this + 0x28) = *(undefined8 *)(param_1 + 0x28);
  return;
}



// ==== 00228bec  const::{lambda()#1}::QString

/* QString({lambda()#1}&&) */

void __thiscall const::{lambda()#1}::QString(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  ::QString::QString((QString *)(this + 0x28),(QString *)(param_1 + 0x28));
  return;
}



// ==== 0022adb2  const::{lambda()#1}::operator()

/* QList<QDBusObjectPath>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 00256886  const::{lambda()#1}::operator()

/* Lelan::refreshUsers()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_TEMPNAMEPLACEHOLDERVALUE * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QList<QVariant> *this_00;
  long lVar1;
  operator()(_ *this_01;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  bool bVar7;
  int iVar8;
  QVariant *pQVar9;
  QDebug *pQVar10;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_230 [8];
  QDBusPendingReply<QMap<QString,QVariant>> aQStack_228 [8];
  undefined8 uStack_220;
  wchar16 *pwStack_218;
  wchar16 *pwStack_210;
  wchar16 *pwStack_208;
  wchar16 *pwStack_200;
  wchar16 *pwStack_1f8;
  undefined *puStack_1f0;
  undefined1 *puStack_1e8;
  undefined1 *puStack_1e0;
  undefined *puStack_1d8;
  undefined1 *puStack_1d0;
  undefined1 *puStack_1c8;
  undefined1 *puStack_1c0;
  wchar16 *pwStack_1b8;
  undefined *puStack_1b0;
  QString aQStack_1a8 [32];
  QArrayDataPointer<char16_t> aQStack_188 [32];
  QString aQStack_168 [32];
  ulonglong auStack_148 [4];
  QArrayDataPointer<char16_t> aQStack_128 [64];
  QString aQStack_e8 [64];
  QVariant aQStack_a8 [32];
  QVariant aQStack_88 [32];
  QString aQStack_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
                    /* catch() { ... } // from try @ 0025691b with catch @ 002568aa */
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_230,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar6 = QDBusPendingCall::isValid();
  if (cVar6 == '\0') {
    QMessageLogger::QMessageLogger((QMessageLogger *)auStack_148,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar10 = (QDebug *)
              QDebug::operator<<((QDebug *)aQStack_1a8,"[lelan] Accounts GetAll failed for");
    pQVar10 = (QDebug *)QDebug::operator<<(pQVar10,(QString *)(this + 0x10));
    pQVar10 = (QDebug *)QDebug::operator<<(pQVar10,":");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar10 = (QDebug *)QDebug::operator<<(pQVar10,(QString *)aQStack_188);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar10,aQStack_168);
    ::QString::~QString(aQStack_168);
    QDBusError::~QDBusError((QDBusError *)aQStack_e8);
    ::QString::~QString((QString *)aQStack_188);
    QDBusError::~QDBusError((QDBusError *)aQStack_128);
    QDebug::~QDebug((QDebug *)aQStack_1a8);
    goto LAB_002575f3;
  }
  QDBusPendingReply<QMap<QString,QVariant>>::value(aQStack_228);
  ::QVariant::QVariant(aQStack_88);
  pwStack_218 = L"UserName";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_128,(QTypedArrayData *)0x0,L"UserName",8);
  ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
  QMap<QString,QVariant>::value(aQStack_68,(QVariant *)aQStack_228);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)aQStack_68);
  ::QString::~QString(aQStack_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
  ::QVariant::~QVariant(aQStack_88);
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  bVar7 = false;
  cVar6 = ::QString::isEmpty(aQStack_1a8);
  if (cVar6 == '\x01') {
LAB_00256aa5:
    bVar5 = false;
  }
  else {
    ::QVariant::QVariant(aQStack_88);
    bVar4 = true;
    pwStack_210 = L"SystemAccount";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_128,(QTypedArrayData *)0x0,L"SystemAccount",0xd);
    bVar3 = true;
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    bVar2 = true;
    QMap<QString,QVariant>::value(aQStack_68,(QVariant *)aQStack_228);
    bVar7 = true;
    cVar6 = ::QVariant::toBool();
    if (cVar6 == '\x01') goto LAB_00256aa5;
    bVar5 = true;
  }
  if (bVar7) {
    ::QVariant::~QVariant((QVariant *)aQStack_68);
  }
  if (bVar2) {
    ::QString::~QString(aQStack_e8);
  }
  if (bVar3) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
  }
  if (bVar4) {
    ::QVariant::~QVariant(aQStack_88);
  }
  if (bVar5) {
    uStack_220 = 0;
    ::QVariant::QVariant((QVariant *)aQStack_68,aQStack_1a8);
    pwStack_208 = L"name";
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_128,(QTypedArrayData *)0x0,L"name",4);
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&uStack_220,aQStack_e8);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QVariant::QVariant(aQStack_a8);
    pwStack_200 = L"RealName";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)auStack_148,(QTypedArrayData *)0x0,L"RealName",8);
    ::QString::QString((QString *)aQStack_128,(QArrayDataPointer *)auStack_148);
    QMap<QString,QVariant>::value((QString *)aQStack_88,(QVariant *)aQStack_228);
    ::QVariant::toString();
    ::QVariant::QVariant((QVariant *)aQStack_68,aQStack_e8);
    pwStack_1f8 = L"displayName";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_188,(QTypedArrayData *)0x0,L"displayName",0xb);
    ::QString::QString(aQStack_168,(QArrayDataPointer *)aQStack_188);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&uStack_220,aQStack_168);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString(aQStack_168);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_188);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QString::~QString(aQStack_e8);
    ::QVariant::~QVariant(aQStack_88);
    ::QString::~QString((QString *)aQStack_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_148);
    ::QVariant::~QVariant(aQStack_a8);
    ::QVariant::QVariant(aQStack_a8);
    puStack_1f0 = &DAT_002ad900;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_128,(QTypedArrayData *)0x0,L"AccountType",0xb);
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    QMap<QString,QVariant>::value((QString *)aQStack_88,(QVariant *)aQStack_228);
    iVar8 = ::QVariant::toInt((bool *)aQStack_88);
    ::QVariant::QVariant((QVariant *)aQStack_68,iVar8 == 1);
    puStack_1e8 = &LAB_002ad917_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)aQStack_168,(QTypedArrayData *)0x0,L"isAdmin",7);
    ::QString::QString((QString *)auStack_148,(QArrayDataPointer *)aQStack_168);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&uStack_220,(QString *)auStack_148);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString((QString *)auStack_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aQStack_168);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QVariant::~QVariant(aQStack_88);
    ::QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    ::QVariant::~QVariant(aQStack_a8);
    ::QVariant::QVariant(aQStack_a8);
    puStack_1e0 = &LAB_002ad927_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_128,(QTypedArrayData *)0x0,L"PasswordMode",0xc);
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    QMap<QString,QVariant>::value((QString *)aQStack_88,(QVariant *)aQStack_228);
    iVar8 = ::QVariant::toInt((bool *)aQStack_88);
    ::QVariant::QVariant((QVariant *)aQStack_68,iVar8 == 0);
    puStack_1d8 = &DAT_002ad942;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)aQStack_168,(QTypedArrayData *)0x0,L"hasPassword",0xb)
    ;
    ::QString::QString((QString *)auStack_148,(QArrayDataPointer *)aQStack_168);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&uStack_220,(QString *)auStack_148);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString((QString *)auStack_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aQStack_168);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QVariant::~QVariant(aQStack_88);
    ::QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    ::QVariant::~QVariant(aQStack_a8);
    ::QVariant::QVariant(aQStack_a8);
    puStack_1d0 = &LAB_002ad959_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_128,(QTypedArrayData *)0x0,L"AutomaticLogin",0xe);
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    QMap<QString,QVariant>::value((QString *)aQStack_88,(QVariant *)aQStack_228);
    bVar7 = (bool)::QVariant::toBool();
    ::QVariant::QVariant((QVariant *)aQStack_68,bVar7);
    puStack_1c8 = &LAB_002ad978;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)aQStack_168,(QTypedArrayData *)0x0,L"isAutoLogin",0xb)
    ;
    ::QString::QString((QString *)auStack_148,(QArrayDataPointer *)aQStack_168);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&uStack_220,(QString *)auStack_148);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString((QString *)auStack_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aQStack_168);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QVariant::~QVariant(aQStack_88);
    ::QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    ::QVariant::~QVariant(aQStack_a8);
    ::QVariant::QVariant(aQStack_a8);
    puStack_1c0 = &LAB_002ad990;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)auStack_148,(QTypedArrayData *)0x0,L"IconFile",8);
    ::QString::QString((QString *)aQStack_128,(QArrayDataPointer *)auStack_148);
    QMap<QString,QVariant>::value((QString *)aQStack_88,(QVariant *)aQStack_228);
    ::QVariant::toString();
    ::QVariant::QVariant((QVariant *)aQStack_68,aQStack_e8);
    pwStack_1b8 = L"avatar";
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_188,(QTypedArrayData *)0x0,L"avatar",6);
    ::QString::QString(aQStack_168,(QArrayDataPointer *)aQStack_188);
    pQVar9 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&uStack_220,aQStack_168);
    ::QVariant::operator=(pQVar9,(QVariant *)aQStack_68);
    ::QString::~QString(aQStack_168);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_188);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QString::~QString(aQStack_e8);
    ::QVariant::~QVariant(aQStack_88);
    ::QString::~QString((QString *)aQStack_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_148);
    ::QVariant::~QVariant(aQStack_a8);
    this_00 = *(QList<QVariant> **)(this + 0x28);
    ::QVariant::QVariant((QVariant *)aQStack_68,(QMap *)&uStack_220);
    QList<QVariant>::append(this_00,(QVariant *)aQStack_68);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    QHash<QString,QString>::insert
              ((QHash<QString,QString> *)(*(long *)(this + 0x28) + 0x18),aQStack_1a8,
               (QString *)(this + 0x10));
    lVar1 = *(long *)(this + 0x28);
    ::QVariant::QVariant(aQStack_88);
    puStack_1b0 = &DAT_002ad9b0;
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_128,(QTypedArrayData *)0x0,L"Uid",3);
    ::QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_128);
    QMap<QString,QVariant>::value(aQStack_68,(QVariant *)aQStack_228);
    auStack_148[0] = ::QVariant::toULongLong((bool *)aQStack_68);
    QHash<QString,unsigned_long_long>::insert
              ((QHash<QString,unsigned_long_long> *)(lVar1 + 0x20),aQStack_1a8,auStack_148);
    ::QVariant::~QVariant((QVariant *)aQStack_68);
    ::QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    ::QVariant::~QVariant(aQStack_88);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&uStack_220);
  }
  ::QString::~QString(aQStack_1a8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)aQStack_228);
LAB_002575f3:
  lVar1 = *(long *)(this + 0x28);
  *(int *)(lVar1 + 0x28) = *(int *)(lVar1 + 0x28) + -1;
  if (*(int *)(lVar1 + 0x28) == 0) {
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0x170),*(QList **)(this + 0x28));
    QHash<QString,QString>::operator=
              ((QHash<QString,QString> *)(*(long *)this + 0x1a0),
               (QHash *)(*(long *)(this + 0x28) + 0x18));
    QHash<QString,unsigned_long_long>::operator=
              ((QHash<QString,unsigned_long_long> *)(*(long *)this + 0x1a8),
               (QHash *)(*(long *)(this + 0x28) + 0x20));
    this_01 = *(operator()(_ **)(this + 0x28);
    if (this_01 != (operator()(_ *)0x0) {
      Lelan::refreshUsers()::{lambda()#1}::operator()()::~UAcc(this_01);
      operator_delete(this_01,0x30);
    }
    Lelan::usersChanged(*(Lelan **)this);
    Lelan::updateCurrentUserName(*(Lelan **)this);
  }
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_230);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_TEMPNAMEPLACEHOLDERVALUE *)0x0;
}



// ==== 00257b6a  const::{lambda()#1}::~refreshUsers

/* ~refreshUsers() */

void __thiscall const::{lambda()#1}::~refreshUsers(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 0025bb42  const::{lambda()#1}::refreshUsers

/* refreshUsers({lambda()#1}&&) */

void __thiscall const::{lambda()#1}::refreshUsers(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
                    /* try { // try from 0025bb6c to 0035bb70 has its CatchHandler @ 0025c6bf */
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
                    /* try { // try from 0025bb94 to 0035bb98 has its CatchHandler @ 0025c91f */
  *(undefined8 *)(this + 0x28) = *(undefined8 *)(param_1 + 0x28);
  return;
}



// ==== 00267e52  const::{lambda(int)#1}::operator()

/* CalendarBackend::exportICS() const::{lambda(int)#1}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_func_exportICS * __thiscall const::{lambda(int)#1}::operator()(_lambda_int__1_ *this,int param_1)

{
  int in_EDX;
  long in_FS_OFFSET;
  undefined2 local_7c;
  undefined2 local_7a;
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_78,"%1%2");
  QChar::QChar<char,true>((QChar *)&local_7c,'0');
  QString::arg<int,true>(local_58,local_78,in_EDX / 0x3c,2,10,local_7c);
  QChar::QChar<char,true>((QChar *)&local_7a,'0');
  QString::arg<int,true>(local_38,local_58,in_EDX % 0x3c,2,10,local_7a);
  ::operator+((QString *)this,(char *)local_38);
  QString::~QString(local_38);
  QString::~QString(local_58);
  QString::~QString(local_78);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (_func_exportICS *)this;
}



// ==== 0027dee4  const::{lambda()#1}::operator()

/* QList<writeXcursorFile(QString const&, QList<int> const&, std::function<QImage (int)> const&,
   double, double)::Frame>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}



// ==== 0028a8e6  const::{lambda()#1}::operator()

/* QList<QPointF>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
                    /* try { // try from 0028a8f0 to 0038a8f4 has its CatchHandler @ 0028b6d9 */
  return in_RAX;
}



// ==== 0028ccf4  const::{lambda()#1}::operator()

/* QList<QWindow*>::size() const::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

_func_size * __thiscall const::{lambda()#1}::operator()(_lambda___1_ *this)

{
  _func_size *in_RAX;
  
  return in_RAX;
}


