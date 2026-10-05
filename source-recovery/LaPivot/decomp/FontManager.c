// Ghidra decompile of LaPivot.oracle — class/namespace FontManager (31 functions). Raw; not source.

// ==== 0013a8f0  FontManager::qt_static_metacall

/* FontManager::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void FontManager::qt_static_metacall
               (FontManager *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  bool bVar1;
  QList<QVariant> QVar2;
  undefined4 uVar3;
  uint uVar4;
  long in_FS_OFFSET;
  FontManager local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 9) {
      installFont(param_1,*(QString **)(param_4 + 8));
    }
    else if (param_3 < 10) {
      if (param_3 == 8) {
        refresh(param_1);
      }
      else if (param_3 < 9) {
        if (param_3 == 7) {
          families(local_48);
          if (*(long *)param_4 != 0) {
            QList<QString>::operator=(*(QList<QString> **)param_4,(QList *)local_48);
          }
          QList<QString>::~QList((QList<QString> *)local_48);
        }
        else if (param_3 < 8) {
          if (param_3 == 6) {
            onPkError(param_1,**(uint **)(param_4 + 8),*(QString **)(param_4 + 0x10));
          }
          else if (param_3 < 7) {
            uVar4 = (uint)param_1;
            if (param_3 == 5) {
              onInstallFinished(uVar4,**(uint **)(param_4 + 8));
            }
            else if (param_3 < 6) {
              if (param_3 == 4) {
                onResolveFinished(uVar4,**(uint **)(param_4 + 8));
              }
              else if (param_3 < 5) {
                if (param_3 == 3) {
                  onResolvePackage(uVar4,(QString *)(ulong)**(uint **)(param_4 + 8),
                                   *(QString **)(param_4 + 0x10));
                }
                else if (param_3 < 4) {
                  if (param_3 == 2) {
                    statusChanged(param_1);
                  }
                  else if (param_3 < 3) {
                    if (param_3 == 0) {
                      fontsChanged(param_1);
                    }
                    else if (param_3 == 1) {
                      fontInstalled(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10)
                                   );
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
      (((bVar1 = QtMocHelpers::indexOfMethod<void(FontManager::*)()>
                           (param_4,(void **)fontsChanged,(_func_void *)0x0,0), !bVar1 &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(FontManager::*)(QString_const&,QString_const&)>
                           (param_4,(void **)fontInstalled,(_func_void_QString_ptr_QString_ptr *)0x0
                            ,1), !bVar1)) &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(FontManager::*)()>
                          (param_4,(void **)statusChanged,(_func_void *)0x0,2), !bVar1)))) &&
     (param_2 == 1)) {
    this = *(QList<QVariant> **)param_4;
    if (param_3 == 4) {
      uVar3 = total(param_1);
      *(undefined4 *)this = uVar3;
    }
    else if (param_3 < 5) {
      if (param_3 == 3) {
        uVar3 = installedCount(param_1);
        *(undefined4 *)this = uVar3;
      }
      else if (param_3 < 4) {
        if (param_3 == 2) {
          status();
          QString::operator=((QString *)this,(QString *)local_48);
          QString::~QString((QString *)local_48);
        }
        else if (param_3 < 3) {
          if (param_3 == 0) {
            fonts();
            QList<QVariant>::operator=(this,(QList *)local_48);
            QList<QVariant>::~QList((QList<QVariant> *)local_48);
          }
          else if (param_3 == 1) {
            QVar2 = (QList<QVariant>)busy(param_1);
            *this = QVar2;
          }
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



// ==== 0013ad0e  FontManager::metaObject

/* FontManager::metaObject() const */

undefined1 * __thiscall FontManager::metaObject(FontManager *this)

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



// ==== 0013ad56  FontManager::qt_metacast

/* FontManager::qt_metacast(char const*) */

FontManager * __thiscall FontManager::qt_metacast(FontManager *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (FontManager *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"FontManager");
    if (iVar1 != 0) {
      this = (FontManager *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013adaa  FontManager::qt_metacall

/* FontManager::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
FontManager::qt_metacall(FontManager *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 10) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -10;
    }
    if (param_2 == 7) {
      if (local_28 < 10) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -10;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -5;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013aea0  FontManager::fontsChanged

/* FontManager::fontsChanged() */

void __thiscall FontManager::fontsChanged(FontManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0013aecc  FontManager::fontInstalled

/* FontManager::fontInstalled(QString const&, QString const&) */

void __thiscall FontManager::fontInstalled(FontManager *this,QString *param_1,QString *param_2)

{
  QMetaObject::activate<void,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,1,(void *)0x0,param_1,param_2);
  return;
}



// ==== 0013af0e  FontManager::statusChanged

/* FontManager::statusChanged() */

void __thiscall FontManager::statusChanged(FontManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 00157a6e  FontManager::FontManager

/* FontManager::FontManager(QObject*) */

void __thiscall FontManager::FontManager(FontManager *this,QObject *param_1)

{
  long in_FS_OFFSET;
  QString local_48 [32];
  QArrayDataPointer<char16_t> local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c3b8;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x10));
  this[0x28] = (FontManager)0x0;
  QString::QString((QString *)(this + 0x30));
  QString::QString((QString *)(this + 0x48));
  QString::QString((QString *)(this + 0x60));
  QString::QString((QString *)(this + 0x78));
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_28,(QTypedArrayData *)0x0,L"The foundry is ready.",0x15);
  QString::QString(local_48,(QArrayDataPointer *)local_28);
  QString::operator=((QString *)(this + 0x30),local_48);
  QString::~QString(local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00157baa  FontManager::fonts

/* FontManager::fonts() const */

QList<QVariant> * FontManager::fonts(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x10));
  return in_RDI;
}



// ==== 00157bd8  FontManager::busy

/* FontManager::busy() const */

FontManager __thiscall FontManager::busy(FontManager *this)

{
  return this[0x28];
}



// ==== 00157bea  FontManager::status

/* FontManager::status() const */

QString * FontManager::status(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x30));
  return in_RDI;
}



// ==== 00157c18  FontManager::installedCount

/* FontManager::installedCount() const */

int __thiscall FontManager::installedCount(FontManager *this)

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
  local_c0 = (QList<QVariant> *)(this + 0x10);
  local_d8 = QList<QVariant>::begin(local_c0);
  local_d0 = QList<QVariant>::end(local_c0);
  while( true ) {
    cVar1 = QList<QVariant>::const_iterator::operator!=((const_iterator *)&local_d8,local_d0);
    if (cVar1 == '\0') break;
    local_b8 = QList<QVariant>::const_iterator::operator*((const_iterator *)&local_d8);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    local_b0 = &LAB_0029296b_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"installed",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_c8);
    cVar1 = ::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
    if (cVar1 != '\0') {
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



// ==== 00157e38  FontManager::total

/* FontManager::total() const */

void __thiscall FontManager::total(FontManager *this)

{
  QList<QVariant>::size((QList<QVariant> *)(this + 0x10));
  return;
}



// ==== 00157e56  FontManager::families

/* FontManager::families() const */

FontManager * __thiscall FontManager::families(FontManager *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  QFontDatabase::families(this,0);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00157ea0  FontManager::refresh

/* FontManager::refresh() */

void __thiscall FontManager::refresh(FontManager *this)

{
  bool bVar1;
  QVariant *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_138;
  char **local_130;
  undefined1 *local_128;
  char **local_120;
  char **local_118;
  undefined1 *local_110;
  undefined1 *local_108;
  undefined1 *local_100;
  undefined *local_f8;
  undefined *local_f0;
  undefined1 *local_e8;
  undefined1 *local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  QString local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  undefined8 local_68;
  undefined8 local_60;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QList<QVariant>::clear((QList<QVariant> *)(this + 0x10));
  local_128 = refresh()::CATALOG;
  local_120 = (char **)&DAT_00315528;
  for (local_130 = (char **)refresh()::CATALOG; local_130 != local_120; local_130 = local_130 + 5) {
    local_118 = local_130;
    local_138 = 0;
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_68,local_130);
    QString::fromUtf8(local_c8,local_68,local_60);
    ::QVariant::QVariant(local_48,local_c8);
    local_110 = &LAB_00292be9_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"family",6);
    QString::QString((QString *)&local_68,(QArrayDataPointer *)local_88);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)&local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)&local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_d8,local_118 + 1);
    QString::fromUtf8(&local_68,local_d8,local_d0);
    ::QVariant::QVariant(local_48,(QString *)&local_68);
    local_108 = &LAB_00292bf8;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"pkg",3);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)&local_68);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_d8,local_118 + 2);
    QString::fromUtf8(&local_68,local_d8,local_d0);
    ::QVariant::QVariant(local_48,(QString *)&local_68);
    local_100 = &LAB_00292bff_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"category",8);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)&local_68);
    ::QVariant::QVariant(local_48,*(bool *)(local_118 + 3));
    local_f8 = &DAT_00292c12;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"aur",3);
    QString::QString((QString *)&local_68,(QArrayDataPointer *)local_88);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)&local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)&local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_d8,local_118 + 4);
    QString::fromUtf8(&local_68,local_d8,local_d0);
    ::QVariant::QVariant(local_48,(QString *)&local_68);
    local_f0 = &DAT_00292c1a;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"repo",4);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)&local_68);
    bVar1 = (bool)QFontDatabase::hasFamily(local_c8);
    ::QVariant::QVariant(local_48,bVar1);
    local_e8 = &LAB_0029296b_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"installed",9);
    QString::QString((QString *)&local_68,(QArrayDataPointer *)local_88);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_138,(QString *)&local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)&local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,(QMap *)&local_138);
    QList<QVariant>::append((QList<QVariant> *)(this + 0x10),local_48);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_c8);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_138);
  }
  fontsChanged(this);
  local_e0 = &LAB_0029293f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"The foundry is ready.",0x15);
  QString::QString((QString *)&local_68,(QArrayDataPointer *)local_88);
  setStatus(this,(QString *)&local_68);
  QString::~QString((QString *)&local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001586d2  FontManager::installFont(QString_const&)::{lambda(QString_const&)#1}::operator()

/* FontManager::installFont(QString const&)::{lambda(QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&) const */

void __thiscall
FontManager::installFont(QString_const&)::{lambda(QString_const&)#1}::operator()
          (_lambda_QString_const___1_ *this,QString *param_1)

{
  char *pcVar1;
  QDBusMessage *this_00;
  QString *this_01;
  long in_FS_OFFSET;
  QString local_158 [8];
  QString local_150 [8];
  undefined1 *local_148;
  undefined1 *local_140;
  undefined1 *local_138;
  undefined1 *local_130;
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  ulonglong local_e8 [4];
  QString local_c8 [32];
  QString local_a8 [24];
  QString aQStack_90 [8];
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  pcVar1 = *(char **)this;
  local_148 = &LAB_00292c23_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Package",7);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusConnection::connect
            (local_158,(QString *)local_e8,param_1,local_c8,(QObject *)local_108,pcVar1);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  pcVar1 = *(char **)this;
  local_140 = &LAB_00292ca8;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Finished",8);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusConnection::connect
            (local_158,(QString *)local_e8,param_1,local_c8,(QObject *)local_108,pcVar1);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  pcVar1 = *(char **)this;
  local_138 = &LAB_00292cd7_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"ErrorCode",9);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusConnection::connect
            (local_158,(QString *)local_e8,param_1,local_c8,(QObject *)local_108,pcVar1);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_130 = &LAB_00292d00_6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Resolve",7);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusMessage::createMethodCall(local_150,(QString *)local_e8,param_1,local_c8);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_e8[0] = 0;
  ::QVariant::fromValue<unsigned_long_long,true>(local_88,local_e8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_150,local_88);
  QString::QString(local_a8,(QString *)(*(long *)this + 0x48));
  QList<QString>::QList(local_c8,local_a8,1);
  ::QVariant::QVariant(local_68,(QList *)local_c8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QList<QString>::~QList((QList<QString> *)local_c8);
  this_01 = aQStack_90;
  while (this_01 != local_a8) {
    this_01 = this_01 + -0x18;
    QString::~QString(this_01);
  }
  ::QVariant::~QVariant(local_88);
  QDBusConnection::asyncCall((QDBusMessage *)local_c8,(int)local_158);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_150);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_158);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00158e7e  FontManager::installFont

/* FontManager::installFont(QString const&) */

void __thiscall FontManager::installFont(FontManager *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QString local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty(param_1);
  if (cVar1 == '\0') {
    if (this[0x28] == (FontManager)0x0) {
      this[0x28] = (FontManager)0x1;
      QString::operator=((QString *)(this + 0x48),param_1);
      QString::clear((QString *)(this + 0x60));
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"…",1);
      QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
      familyFor(local_b8);
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_f8,(QTypedArrayData *)0x0,L"Sending for ",0xc);
      QString::QString(local_d8,(QArrayDataPointer *)local_f8);
      ::operator+(local_98,local_d8);
      ::operator+(local_38,local_98);
      setStatus(this,local_38);
      QString::~QString(local_38);
      QString::~QString(local_98);
      QString::~QString(local_d8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
      QString::~QString(local_b8);
      QString::~QString((QString *)local_58);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
      newTransaction<FontManager::installFont(QString_const&)::_lambda(QString_const&)_1_>
                (this,this);
    }
    else {
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_58,(QTypedArrayData *)0x0,
                 L"The foundry is already pouring — one face at a time.",0x34);
      QString::QString(local_38,(QArrayDataPointer *)local_58);
      setStatus(this,local_38);
      QString::~QString(local_38);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    }
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,
               L"That face travels with NCDE itself — nothing to fetch.",0x36);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    setStatus(this,local_38);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00159278  FontManager::onResolvePackage

/* FontManager::onResolvePackage(unsigned int, QString const&, QString const&) */

void FontManager::onResolvePackage(uint param_1,QString *param_2,QString *param_3)

{
  undefined4 in_register_0000003c;
  
  QString::operator=((QString *)(CONCAT44(in_register_0000003c,param_1) + 0x60),param_3);
  return;
}



// ==== 001592aa  FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}::operator()

/* FontManager::onResolveFinished(unsigned int, unsigned int)::{lambda(QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&) const */

void __thiscall
FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}::operator()
          (_lambda_QString_const___1_ *this,QString *param_1)

{
  char *pcVar1;
  QDBusMessage *this_00;
  QString *this_01;
  long in_FS_OFFSET;
  QString local_150 [8];
  QString local_148 [8];
  undefined1 *local_140;
  undefined1 *local_138;
  undefined1 *local_130;
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  ulonglong local_e8 [4];
  QString local_c8 [32];
  QString local_a8 [24];
  QString aQStack_90 [8];
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  pcVar1 = *(char **)this;
  local_140 = &LAB_00292ca8;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Finished",8);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusConnection::connect
            (local_150,(QString *)local_e8,param_1,local_c8,(QObject *)local_108,pcVar1);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  pcVar1 = *(char **)this;
  local_138 = &LAB_00292cd7_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"ErrorCode",9);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusConnection::connect
            (local_150,(QString *)local_e8,param_1,local_c8,(QObject *)local_108,pcVar1);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_130 = &LAB_00292e2f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_128,(QTypedArrayData *)0x0,L"InstallPackages",0xf);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_c8,"org.freedesktop.PackageKit.Transaction");
  QString::QString((QString *)local_e8,"org.freedesktop.PackageKit");
  QDBusMessage::createMethodCall(local_148,(QString *)local_e8,param_1,local_c8);
  QString::~QString((QString *)local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_e8[0] = 0;
  ::QVariant::fromValue<unsigned_long_long,true>(local_88,local_e8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_148,local_88);
  QString::QString(local_a8,(QString *)(*(long *)this + 0x60));
  QList<QString>::QList(local_c8,local_a8,1);
  ::QVariant::QVariant(local_68,(QList *)local_c8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QList<QString>::~QList((QList<QString> *)local_c8);
  this_01 = aQStack_90;
  while (this_01 != local_a8) {
    this_01 = this_01 + -0x18;
    QString::~QString(this_01);
  }
  ::QVariant::~QVariant(local_88);
  QDBusConnection::asyncCall((QDBusMessage *)local_c8,(int)local_150);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_148);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_150);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015990a  FontManager::onResolveFinished

/* FontManager::onResolveFinished(unsigned int, unsigned int) */

void FontManager::onResolveFinished(uint param_1,uint param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 in_register_0000003c;
  FontManager *this;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QString local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  this = (FontManager *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 1) {
    cVar2 = QString::isEmpty((QString *)(this + 0x60));
    if (cVar2 == '\0') {
      bVar1 = false;
      goto LAB_00159964;
    }
  }
  bVar1 = true;
LAB_00159964:
  if (bVar1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,L"The foundry couldn\'t find that face in the cases."
               ,0x31);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    finishInstall(this,false,local_38);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"…",1);
    QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
    familyFor(local_b8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"Pouring ",8);
    QString::QString(local_d8,(QArrayDataPointer *)local_f8);
    ::operator+(local_98,local_d8);
    ::operator+(local_38,local_98);
    setStatus(this,local_38);
    QString::~QString(local_38);
    QString::~QString(local_98);
    QString::~QString(local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
    QString::~QString(local_b8);
    QString::~QString((QString *)local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
    newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::_lambda(QString_const&)_1_>
              (this,this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00159c38  FontManager::onInstallFinished

/* FontManager::onInstallFinished(unsigned int, unsigned int) */

void FontManager::onInstallFinished(uint param_1,uint param_2)

{
  undefined4 in_register_0000003c;
  FontManager *this;
  long in_FS_OFFSET;
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  this = (FontManager *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 1) {
    familyFor(local_98);
    refresh(this);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_78,(QTypedArrayData *)0x0,L" is ready — set before every app.",0x21);
    QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
    ::operator+(local_38,local_98);
    finishInstall(this,true,local_38);
    QString::~QString(local_38);
    QString::~QString((QString *)local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
    fontInstalled(this,(QString *)(this + 0x48),local_98);
    QString::~QString(local_98);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,
               L"The pour didn\'t take — the face was not installed.",0x32);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    finishInstall(this,false,local_38);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00159e94  FontManager::onPkError

/* FontManager::onPkError(unsigned int, QString const&) */

void __thiscall FontManager::onPkError(FontManager *this,uint param_1,QString *param_2)

{
  undefined8 uVar1;
  long in_FS_OFFSET;
  QByteArray local_68 [32];
  QMessageLogger local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::operator=((QString *)(this + 0x78),param_2);
  QMessageLogger::QMessageLogger(local_48,(char *)0x0,0,(char *)0x0);
  QtPrivate::asString(param_2);
  QString::toLocal8Bit();
  uVar1 = QByteArray::constData(local_68);
  QMessageLogger::warning((char *)local_48,"FontManager: PackageKit error: %s",uVar1);
  QByteArray::~QByteArray(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00159f88  FontManager::familyFor

/* FontManager::familyFor(QString const&) const */

QString * FontManager::familyFor(QString *param_1)

{
  char cVar1;
  QString *in_RDX;
  long in_RSI;
  long in_FS_OFFSET;
  undefined8 local_100;
  undefined8 local_f8;
  QVariant local_f0 [8];
  QList<QVariant> *local_e8;
  undefined8 local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_e8 = (QList<QVariant> *)(in_RSI + 0x10);
  local_100 = QList<QVariant>::begin(local_e8);
  local_f8 = QList<QVariant>::end(local_e8);
  while (cVar1 = QList<QVariant>::const_iterator::operator!=((const_iterator *)&local_100,local_f8),
        cVar1 != '\0') {
    local_e0 = QList<QVariant>::const_iterator::operator*((const_iterator *)&local_100);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    local_d8 = &LAB_00292bf8;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"pkg",3);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,local_f0);
    ::QVariant::toString();
    cVar1 = ::operator==(local_88,in_RDX);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    if (cVar1 != '\0') {
      ::QVariant::QVariant(local_68);
      local_d0 = &LAB_00292be9_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_a8,(QTypedArrayData *)0x0,L"family",6);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,local_f0);
      ::QVariant::toString();
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_a8);
      ::QVariant::~QVariant(local_68);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f0);
    if (cVar1 != '\0') goto LAB_0015a2e0;
    QList<QVariant>::const_iterator::operator++((const_iterator *)&local_100);
  }
  QString::QString(param_1,in_RDX);
LAB_0015a2e0:
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015a302  FontManager::finishInstall

/* FontManager::finishInstall(bool, QString const&) */

void __thiscall FontManager::finishInstall(FontManager *this,bool param_1,QString *param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QString local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QString local_58 [24];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  this[0x28] = (FontManager)0x0;
  bVar5 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  bVar1 = false;
  bVar6 = false;
  if (!param_1) {
    cVar7 = QString::isEmpty((QString *)(this + 0x78));
    if (cVar7 != '\x01') {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_98,(QTypedArrayData *)0x0,L")",1);
      bVar5 = true;
      QString::QString(local_78,(QArrayDataPointer *)local_98);
      bVar4 = true;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L" (",2);
      bVar3 = true;
      QString::QString(local_f8,(QArrayDataPointer *)local_118);
      bVar2 = true;
      ::operator+(local_d8,param_2);
      bVar1 = true;
      ::operator+(local_b8,local_d8);
      bVar6 = true;
      ::operator+(local_58,local_b8);
      goto LAB_0015a4cc;
    }
  }
  QString::QString(local_58,param_2);
LAB_0015a4cc:
  setStatus(this,local_58);
  QString::~QString(local_58);
  if (bVar6) {
    QString::~QString(local_b8);
  }
  if (bVar1) {
    QString::~QString(local_d8);
  }
  if (bVar2) {
    QString::~QString(local_f8);
  }
  if (bVar3) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  }
  if (bVar4) {
    QString::~QString(local_78);
  }
  if (bVar5) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
  }
  QString::clear((QString *)(this + 0x78));
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015a688  FontManager::setStatus

/* FontManager::setStatus(QString const&) */

void __thiscall FontManager::setStatus(FontManager *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x30),param_1);
  statusChanged(this);
  return;
}



// ==== 0015a796  FontManager::~FontManager

/* FontManager::~FontManager() */

void __thiscall FontManager::~FontManager(FontManager *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c3b8;
  QString::~QString((QString *)(this + 0x78));
  QString::~QString((QString *)(this + 0x60));
  QString::~QString((QString *)(this + 0x48));
  QString::~QString((QString *)(this + 0x30));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0015a810  FontManager::~FontManager

/* FontManager::~FontManager() */

void __thiscall FontManager::~FontManager(FontManager *this)

{
  ~FontManager(this);
  operator_delete(this,0x90);
  return;
}



// ==== 001a697c  FontManager::newTransaction<FontManager::installFont(QString_const&)::{lambda(QString_const&)#1}>(FontManager::installFont(QString_const&)::{lambda(QString_const&)#1})::{lambda()#1}::operator()

/* FontManager::newTransaction<FontManager::installFont(QString const&)::{lambda(QString
   const&)#1}>(FontManager::installFont(QString const&)::{lambda(QString
   const&)#1})::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
FontManager::
newTransaction<FontManager::installFont(QString_const&)::{lambda(QString_const&)#1}>(FontManager::installFont(QString_const&)::{lambda(QString_const&)#1})
::{lambda()#1}::operator()(_lambda___1_ *this)

{
  FontManager *this_00;
  char cVar1;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusObjectPath> local_68 [8];
  undefined1 *local_60;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusObjectPath>::QDBusPendingReply
            (local_68,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\x01') {
    QDBusPendingReply<QDBusObjectPath>::value((QDBusPendingReply<QDBusObjectPath> *)local_58);
    QDBusObjectPath::path();
    installFont(QString_const&)::{lambda(QString_const&)#1}::operator()
              ((_lambda_QString_const___1_ *)(this + 0x10),local_38);
    QString::~QString(local_38);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_58);
  }
  else {
    this_00 = *(FontManager **)this;
    local_60 = &LAB_002a3ae0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,L"The foundry\'s furnace isn\'t lit on this machine."
               ,0x30);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    finishInstall(this_00,false,local_38);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  }
  QDBusPendingReply<QDBusObjectPath>::~QDBusPendingReply(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a6b52  FontManager::newTransaction<FontManager::installFont(QString_const&)::{lambda(QString_const&)#1}>

/* WARNING: Removing unreachable block (ram,0x001a6d74) */
/* void FontManager::newTransaction<FontManager::installFont(QString const&)::{lambda(QString
   const&)#1}>(FontManager::installFont(QString const&)::{lambda(QString const&)#1}) */

void __thiscall
FontManager::newTransaction<FontManager::installFont(QString_const&)::_lambda(QString_const&)_1_>
          (FontManager *this,undefined8 param_2)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QString local_140 [8];
  QDBusPendingCallWatcher *local_138;
  wchar16 *local_130;
  wchar16 *local_128;
  undefined1 *local_120;
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  FontManager *local_58;
  QDBusPendingCallWatcher *local_50;
  undefined8 local_48;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = &LAB_002a3b47_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_98,(QTypedArrayData *)0x0,L"CreateTransaction",0x11);
  QString::QString(local_78,(QArrayDataPointer *)local_98);
  local_128 = L"org.freedesktop.PackageKit";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_d8,(QTypedArrayData *)0x0,L"org.freedesktop.PackageKit",0x1a);
  QString::QString(local_b8,(QArrayDataPointer *)local_d8);
  local_130 = L"/org/freedesktop/PackageKit";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_118,(QTypedArrayData *)0x0,L"/org/freedesktop/PackageKit",0x1b);
  QString::QString(local_f8,(QArrayDataPointer *)local_118);
  QString::QString((QString *)&local_58,"org.freedesktop.PackageKit");
  QDBusMessage::createMethodCall(local_140,(QString *)&local_58,local_f8,local_b8);
  QString::~QString((QString *)&local_58);
  QString::~QString(local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QString::~QString(local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  QString::~QString(local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
  this_00 = operator_new(0x18);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_78);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_138 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_78);
  local_50 = local_138;
  local_58 = this;
  local_48 = param_2;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),FontManager::newTransaction<FontManager::installFont(QString_const&)::_lambda(QString_const&)_1_>(FontManager::installFont(QString_const&)::_lambda(QString_const&)_1_)::_lambda()_1_>
            (local_78,local_138,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_140);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a6f26  FontManager::newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}>(FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1})::{lambda()#1}::operator()

/* FontManager::newTransaction<FontManager::onResolveFinished(unsigned int, unsigned
   int)::{lambda(QString const&)#1}>(FontManager::onResolveFinished(unsigned int, unsigned
   int)::{lambda(QString const&)#1})::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
FontManager::
newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}>(FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1})
::{lambda()#1}::operator()(_lambda___1_ *this)

{
  FontManager *this_00;
  char cVar1;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusObjectPath> local_68 [8];
  undefined1 *local_60;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusObjectPath>::QDBusPendingReply
            (local_68,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\x01') {
    QDBusPendingReply<QDBusObjectPath>::value((QDBusPendingReply<QDBusObjectPath> *)local_58);
    QDBusObjectPath::path();
    onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}::operator()
              ((_lambda_QString_const___1_ *)(this + 0x10),local_38);
    QString::~QString(local_38);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_58);
  }
  else {
    this_00 = *(FontManager **)this;
    local_60 = &LAB_002a3ae0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,L"The foundry\'s furnace isn\'t lit on this machine."
               ,0x30);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    finishInstall(this_00,false,local_38);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  }
  QDBusPendingReply<QDBusObjectPath>::~QDBusPendingReply(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a70e0  FontManager::newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::{lambda(QString_const&)#1}>

/* WARNING: Removing unreachable block (ram,0x001a7302) */
/* void FontManager::newTransaction<FontManager::onResolveFinished(unsigned int, unsigned
   int)::{lambda(QString const&)#1}>(FontManager::onResolveFinished(unsigned int, unsigned
   int)::{lambda(QString const&)#1}) */

void __thiscall
FontManager::
newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::_lambda(QString_const&)_1_>
          (FontManager *this,undefined8 param_2)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QString local_140 [8];
  QDBusPendingCallWatcher *local_138;
  wchar16 *local_130;
  wchar16 *local_128;
  undefined1 *local_120;
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  FontManager *local_58;
  QDBusPendingCallWatcher *local_50;
  undefined8 local_48;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = &LAB_002a3b47_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_98,(QTypedArrayData *)0x0,L"CreateTransaction",0x11);
  QString::QString(local_78,(QArrayDataPointer *)local_98);
  local_128 = L"org.freedesktop.PackageKit";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_d8,(QTypedArrayData *)0x0,L"org.freedesktop.PackageKit",0x1a);
  QString::QString(local_b8,(QArrayDataPointer *)local_d8);
  local_130 = L"/org/freedesktop/PackageKit";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_118,(QTypedArrayData *)0x0,L"/org/freedesktop/PackageKit",0x1b);
  QString::QString(local_f8,(QArrayDataPointer *)local_118);
  QString::QString((QString *)&local_58,"org.freedesktop.PackageKit");
  QDBusMessage::createMethodCall(local_140,(QString *)&local_58,local_f8,local_b8);
  QString::~QString((QString *)&local_58);
  QString::~QString(local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QString::~QString(local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  QString::~QString(local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
  this_00 = operator_new(0x18);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_78);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_138 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_78);
  local_50 = local_138;
  local_58 = this;
  local_48 = param_2;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),FontManager::newTransaction<FontManager::onResolveFinished(unsigned_int,unsigned_int)::_lambda(QString_const&)_1_>(FontManager::onResolveFinished(unsigned_int,unsigned_int)::_lambda(QString_const&)_1_)::_lambda()_1_>
            (local_78,local_138,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_140);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}


