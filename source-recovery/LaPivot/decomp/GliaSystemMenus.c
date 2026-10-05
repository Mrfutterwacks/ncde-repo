// Ghidra decompile of LaPivot.oracle — class/namespace GliaSystemMenus (16 functions). Raw; not source.

// ==== 0013af3a  GliaSystemMenus::qt_static_metacall

/* GliaSystemMenus::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void GliaSystemMenus::qt_static_metacall
               (GliaSystemMenus *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  bool bVar1;
  long in_FS_OFFSET;
  QList local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 3) {
      openPath(param_1,*(QString **)(param_4 + 8));
    }
    else if (param_3 < 4) {
      if (param_3 == 2) {
        launch(param_1,*(QString **)(param_4 + 8));
      }
      else if (param_3 < 3) {
        if (param_3 == 0) {
          changed(param_1);
        }
        else if (param_3 == 1) {
          rescan(param_1);
        }
      }
    }
  }
  if (((param_2 != 5) ||
      (bVar1 = QtMocHelpers::indexOfMethod<void(GliaSystemMenus::*)()>
                         (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1)) && (param_2 == 1))
  {
    this = *(QList<QVariant> **)param_4;
    if (param_3 == 2) {
      recentFiles((GliaSystemMenus *)local_38);
      QList<QVariant>::operator=(this,local_38);
      QList<QVariant>::~QList((QList<QVariant> *)local_38);
    }
    else if (param_3 < 3) {
      if (param_3 == 0) {
        applications();
        QList<QVariant>::operator=(this,local_38);
        QList<QVariant>::~QList((QList<QVariant> *)local_38);
      }
      else if (param_3 == 1) {
        places((GliaSystemMenus *)local_38);
        QList<QVariant>::operator=(this,local_38);
        QList<QVariant>::~QList((QList<QVariant> *)local_38);
      }
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013b114  GliaSystemMenus::metaObject

/* GliaSystemMenus::metaObject() const */

undefined1 * __thiscall GliaSystemMenus::metaObject(GliaSystemMenus *this)

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



// ==== 0013b15c  GliaSystemMenus::qt_metacast

/* GliaSystemMenus::qt_metacast(char const*) */

GliaSystemMenus * __thiscall GliaSystemMenus::qt_metacast(GliaSystemMenus *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (GliaSystemMenus *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"GliaSystemMenus");
    if (iVar1 != 0) {
      this = (GliaSystemMenus *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013b1b0  GliaSystemMenus::qt_metacall

/* GliaSystemMenus::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
GliaSystemMenus::qt_metacall
          (GliaSystemMenus *this,int param_2,undefined4 param_3,undefined8 *param_4)

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



// ==== 0013b2a6  GliaSystemMenus::changed

/* GliaSystemMenus::changed() */

void __thiscall GliaSystemMenus::changed(GliaSystemMenus *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0015a882  GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}::operator()

/* GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  rescan(*(GliaSystemMenus **)this);
  return;
}



// ==== 0015a8a0  GliaSystemMenus::GliaSystemMenus

/* GliaSystemMenus::GliaSystemMenus(QObject*) */

void __thiscall GliaSystemMenus::GliaSystemMenus(GliaSystemMenus *this,QObject *param_1)

{
  long in_FS_OFFSET;
  GliaSystemMenus *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c348;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x10));
  local_28 = this;
  QTimer::singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::_lambda()_1_>
            (0,(ContextType *)this,(_lambda___1_ *)&local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015a968  GliaSystemMenus::applications

/* GliaSystemMenus::applications() const */

QList<QVariant> * GliaSystemMenus::applications(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x10));
  return in_RDI;
}



// ==== 0015ac48  GliaSystemMenus::places

/* GliaSystemMenus::places() const */

GliaSystemMenus * __thiscall GliaSystemMenus::places(GliaSystemMenus *this)

{
  long in_FS_OFFSET;
  GliaSystemMenus *local_40;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])this = (undefined1  [16])0x0;
  *(undefined8 *)(this + 0x10) = 0;
  local_40 = this;
  QString::QString(local_38,"Home");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,8,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Desktop");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,0,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Documents");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,1,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Downloads");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,0xe,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Pictures");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,6,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Music");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,4,local_38);
  QString::~QString(local_38);
  QString::QString(local_38,"Videos");
  const::{lambda(QStandardPaths::StandardLocation,QString_const&)#1}::operator()
            ((_lambda_QStandardPaths__StandardLocation_QString_const___1_ *)&local_40,5,local_38);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0015af36  GliaSystemMenus::recentFiles

/* GliaSystemMenus::recentFiles() const */

GliaSystemMenus * __thiscall GliaSystemMenus::recentFiles(GliaSystemMenus *this)

{
  bool bVar1;
  char cVar2;
  QVariant *pQVar3;
  long lVar4;
  long in_FS_OFFSET;
  undefined4 local_d4;
  int local_d0;
  int local_cc;
  QUrl local_c8 [8];
  undefined8 local_c0;
  QFile local_b8 [16];
  QString local_a8 [32];
  QString local_88 [32];
  undefined4 local_68 [8];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])this = (undefined1  [16])0x0;
  *(undefined8 *)(this + 0x10) = 0;
  QDir::homePath();
  ::operator+((QString *)local_68,(char *)local_88);
  QFile::QFile(local_b8,(QString *)local_68);
  QString::~QString((QString *)local_68);
  QString::~QString(local_88);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_68,1);
  cVar2 = QFile::open(local_b8,local_68[0]);
  if (cVar2 != '\0') {
    QIODevice::readAll();
    QString::fromUtf8<void>(local_a8,(QByteArray *)local_68);
    QByteArray::~QByteArray((QByteArray *)local_68);
    local_d0 = 0;
    while( true ) {
      lVar4 = (long)local_d0;
      QString::QString((QString *)local_68,"href=\"");
      local_d0 = QString::indexOf(local_a8,local_68,lVar4,1);
      if ((local_d0 < 0) || (lVar4 = QList<QVariant>::size((QList<QVariant> *)this), 0xe < lVar4)) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      QString::~QString((QString *)local_68);
      if (!bVar1) break;
      local_d0 = local_d0 + 6;
      lVar4 = (long)local_d0;
      QChar::QChar<char,true>((QChar *)local_68,'\"');
      local_cc = QString::indexOf(local_a8,(undefined2)local_68[0],lVar4,1);
      if (local_cc < 0) break;
      QString::mid((longlong)local_68,(longlong)local_a8);
      QUrl::QUrl(local_c8,local_68,0);
      QString::~QString((QString *)local_68);
      local_d0 = local_cc;
      cVar2 = QUrl::isLocalFile();
      if (cVar2 != '\0') {
        local_c0 = 0;
        QFlags<QUrl::ComponentFormattingOption>::QFlags
                  ((QFlags<QUrl::ComponentFormattingOption> *)&local_d4,0x7f00000);
        QUrl::fileName(local_68,local_c8,local_d4);
        ::QVariant::QVariant(local_48,(QString *)local_68);
        QString::QString(local_88,"name");
        pQVar3 = (QVariant *)
                 QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
        ::QVariant::operator=(pQVar3,local_48);
        QString::~QString(local_88);
        ::QVariant::~QVariant(local_48);
        QString::~QString((QString *)local_68);
        QUrl::toLocalFile();
        ::QVariant::QVariant(local_48,(QString *)local_68);
        QString::QString(local_88,"path");
        pQVar3 = (QVariant *)
                 QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
        ::QVariant::operator=(pQVar3,local_48);
        QString::~QString(local_88);
        ::QVariant::~QVariant(local_48);
        QString::~QString((QString *)local_68);
        ::QVariant::QVariant(local_48,(QMap *)&local_c0);
        QList<QVariant>::append((QList<QVariant> *)this,local_48);
        ::QVariant::~QVariant(local_48);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
      }
      QUrl::~QUrl(local_c8);
    }
    QString::~QString(local_a8);
  }
  QFile::~QFile(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0015b4c6  GliaSystemMenus::rescan()::{lambda(QVariant_const&,QVariant_const&)#1}::operator()

/* GliaSystemMenus::rescan()::{lambda(QVariant const&, QVariant
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QVariant const&, QVariant const&) const */

uint GliaSystemMenus::rescan()::{lambda(QVariant_const&,QVariant_const&)#1}::operator()
               (QVariant *param_1,QVariant *param_2)

{
  uint uVar1;
  long in_FS_OFFSET;
  QVariant local_138 [8];
  QVariant local_130 [8];
  QString local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  QVariant local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::toMap();
  ::QVariant::QVariant(local_a8);
  QString::QString(local_128,"name");
  QMap<QString,QVariant>::value(local_88,local_138);
  ::QVariant::toString();
  ::QVariant::toMap();
  ::QVariant::QVariant(local_68);
  QString::QString(local_e8,"name");
  QMap<QString,QVariant>::value(local_48,local_130);
  ::QVariant::toString();
  uVar1 = QString::compare(local_108,local_c8,0);
  QString::~QString(local_c8);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_e8);
  ::QVariant::~QVariant(local_68);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_130);
  QString::~QString(local_108);
  ::QVariant::~QVariant((QVariant *)local_88);
  QString::~QString(local_128);
  ::QVariant::~QVariant(local_a8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_138);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1 >> 0x1f;
}



// ==== 0015b774  GliaSystemMenus::rescan

/* GliaSystemMenus::rescan() */

void __thiscall GliaSystemMenus::rescan(GliaSystemMenus *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  QList<QString> *pQVar5;
  longlong lVar6;
  QVariant *pQVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  char **ppcVar10;
  QString *this_00;
  long lVar11;
  long in_FS_OFFSET;
  QString *local_248;
  QSet<QString> local_238 [8];
  undefined8 local_230;
  undefined8 local_228;
  undefined8 local_220;
  undefined8 local_218;
  undefined8 local_210;
  ulong *local_208;
  QList<QString> *local_200;
  QString *local_1f8;
  QString *local_1f0;
  undefined8 local_1e8;
  initializer_list<char_const*> *local_1e0;
  ulong *local_1d8;
  undefined *local_1d0;
  undefined1 *local_1c8;
  undefined1 *local_1c0;
  undefined1 *local_1b8;
  undefined1 *local_1b0;
  undefined1 *local_1a8;
  undefined1 *local_1a0;
  QSettings local_198 [16];
  QList<QString> local_188 [32];
  QString local_168 [32];
  char *local_148 [4];
  char *local_128;
  undefined8 local_120;
  undefined1 *local_108;
  undefined8 local_100;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_c8;
  undefined8 local_c0;
  QVariant local_a8 [32];
  char *local_88 [4];
  QString local_68 [24];
  QString aQStack_50 [16];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QList<QVariant>::clear((QList<QVariant> *)(this + 0x10));
  QStandardPaths::standardLocations(local_188,3);
  QString::QString(local_168,"/usr/share/applications");
  pQVar5 = (QList<QString> *)QList<QString>::operator<<(local_188,local_168);
  QDir::homePath();
  ::operator+((QString *)&local_128,(char *)local_148);
  pQVar5 = (QList<QString> *)QList<QString>::operator<<(pQVar5,(QString *)&local_128);
  QString::QString((QString *)&local_108,"/var/lib/flatpak/exports/share/applications");
  pQVar5 = (QList<QString> *)QList<QString>::operator<<(pQVar5,(QString *)&local_108);
  QDir::homePath();
  ::operator+((QString *)&local_c8,(char *)&local_e8);
  QList<QString>::operator<<(pQVar5,(QString *)&local_c8);
  QString::~QString((QString *)&local_c8);
  QString::~QString((QString *)&local_e8);
  QString::~QString((QString *)&local_108);
  QString::~QString((QString *)&local_128);
  QString::~QString((QString *)local_148);
  QString::~QString(local_168);
  QListSpecialMethods<QString>::removeDuplicates((QListSpecialMethods<QString> *)local_188);
  QSet<QString>::QSet(local_238);
  local_200 = local_188;
  local_230 = QList<QString>::begin(local_200);
  local_228 = QList<QString>::end(local_200);
  do {
    cVar4 = QList<QString>::iterator::operator!=((iterator *)&local_230,local_228);
    if (cVar4 == '\0') {
      uVar8 = QList<QVariant>::end((QList<QVariant> *)(this + 0x10));
      uVar9 = QList<QVariant>::begin((QList<QVariant> *)(this + 0x10));
      std::
      sort<QList<QVariant>::iterator,GliaSystemMenus::rescan()::_lambda(QVariant_const&,QVariant_const&)_1_>
                (uVar9,uVar8);
      changed(this);
      QSet<QString>::~QSet(local_238);
      QList<QString>::~QList(local_188);
      if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    local_1f8 = (QString *)QList<QString>::iterator::operator*((iterator *)&local_230);
    QDir::QDir((QDir *)&local_e8,local_1f8);
    QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)&local_108,0xffffffff);
    QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)&local_128,2);
    local_248 = local_68;
    local_88[0] = "*.desktop";
    ppcVar10 = local_88;
    for (lVar11 = 0; -1 < lVar11; lVar11 = lVar11 + -1) {
      QString::QString(local_248,*ppcVar10);
      local_248 = local_248 + 0x18;
      ppcVar10 = ppcVar10 + 1;
    }
    QList<QString>::QList(&local_c8,local_68,1);
    QDir::entryInfoList(local_168,&local_e8,&local_c8,(ulong)local_128 & 0xffffffff,
                        (ulong)local_108 & 0xffffffff);
    local_1f0 = local_168;
    QList<QString>::~QList((QList<QString> *)&local_c8);
    this_00 = aQStack_50;
    while (this_00 != local_68) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QDir::~QDir((QDir *)&local_e8);
    local_220 = QList<QFileInfo>::begin((QList<QFileInfo> *)local_1f0);
    local_218 = QList<QFileInfo>::end((QList<QFileInfo> *)local_1f0);
    while (cVar4 = QList<QFileInfo>::iterator::operator!=((iterator *)&local_220,local_218),
          cVar4 != '\0') {
      local_1e8 = QList<QFileInfo>::iterator::operator*((iterator *)&local_220);
      QFileInfo::fileName();
      cVar4 = QSet<QString>::contains(local_238,(QString *)&local_c8);
      QString::~QString((QString *)&local_c8);
      if (cVar4 == '\0') {
        QFileInfo::fileName();
        QSet<QString>::insert((QString *)&local_e8);
        QString::~QString((QString *)&local_c8);
        QFileInfo::absoluteFilePath();
        QSettings::QSettings(local_198,&local_c8,1,0);
        QString::~QString((QString *)&local_c8);
        lVar6 = QtPrivate::lengthHelperContainer<char,14ul>("Desktop Entry");
        local_1d0 = &LAB_00292714;
        QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_c8,"Desktop Entry",lVar6)
        ;
        QSettings::beginGroup(local_198,local_c8,local_c0);
        bVar1 = false;
        bVar2 = false;
        local_148[0] = "Application";
        lVar6 = QtPrivate::lengthHelperContainer<char,5ul>("Type");
        local_1c8 = &LAB_0029272d_1;
        QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_128,"Type",lVar6);
        QSettings::value(local_a8,local_198,local_128,local_120);
        ::QVariant::toString();
        cVar4 = ::operator!=((QString *)&local_c8,local_148);
        if (cVar4 == '\0') {
          lVar6 = QtPrivate::lengthHelperContainer<char,10ul>("NoDisplay");
          local_1c0 = &LAB_00292731_2;
          QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_108,"NoDisplay",lVar6);
          QSettings::value(local_88,local_198,local_108,local_100);
          bVar1 = true;
          cVar4 = ::QVariant::toBool();
          if (cVar4 != '\0') goto LAB_0015bdd7;
          lVar6 = QtPrivate::lengthHelperContainer<char,7ul>("Hidden");
          local_1b8 = &LAB_0029273d;
          QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_e8,"Hidden",lVar6);
          QSettings::value(local_68,local_198,local_e8,local_e0);
          bVar2 = true;
          cVar4 = ::QVariant::toBool();
          if (cVar4 != '\0') goto LAB_0015bdd7;
          bVar3 = false;
        }
        else {
LAB_0015bdd7:
          bVar3 = true;
        }
        if (bVar2) {
          ::QVariant::~QVariant((QVariant *)local_68);
        }
        if (bVar1) {
          ::QVariant::~QVariant((QVariant *)local_88);
        }
        QString::~QString((QString *)&local_c8);
        ::QVariant::~QVariant(local_a8);
        if (!bVar3) {
          local_210 = 0;
          lVar6 = QtPrivate::lengthHelperContainer<char,5ul>("Name");
          local_1b0 = &LAB_0029273d_7;
          QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_108,"Name",lVar6);
          QSettings::value(local_88,local_198,local_108,local_100);
          ::QVariant::toString();
          ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
          QString::QString((QString *)&local_e8,"name");
          pQVar7 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_210,(QString *)&local_e8);
          ::QVariant::operator=(pQVar7,(QVariant *)local_68);
          QString::~QString((QString *)&local_e8);
          ::QVariant::~QVariant((QVariant *)local_68);
          QString::~QString((QString *)&local_c8);
          ::QVariant::~QVariant((QVariant *)local_88);
          lVar6 = QtPrivate::lengthHelperContainer<char,5ul>("Icon");
          local_1a8 = &LAB_0029274e;
          QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_108,"Icon",lVar6);
          QSettings::value(local_88,local_198,local_108,local_100);
          ::QVariant::toString();
          ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
          QString::QString((QString *)&local_e8,"icon");
          pQVar7 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_210,(QString *)&local_e8);
          ::QVariant::operator=(pQVar7,(QVariant *)local_68);
          QString::~QString((QString *)&local_e8);
          ::QVariant::~QVariant((QVariant *)local_68);
          QString::~QString((QString *)&local_c8);
          ::QVariant::~QVariant((QVariant *)local_88);
          lVar6 = QtPrivate::lengthHelperContainer<char,5ul>("Exec");
          local_1a0 = &LAB_00292747_2;
          QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_c8,"Exec",lVar6);
          QSettings::value(local_68,local_198,local_c8,local_c0);
          ::QVariant::toString();
          ::QVariant::~QVariant((QVariant *)local_68);
          local_100 = 7;
          local_108 = C_380_1;
          local_1e0 = (initializer_list<char_const*> *)&local_108;
          local_208 = (ulong *)std::initializer_list<char_const*>::begin(local_1e0);
          local_1d8 = (ulong *)std::initializer_list<char_const*>::end(local_1e0);
          for (; local_208 != local_1d8; local_208 = local_208 + 1) {
            local_128 = (char *)*local_208;
            QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_e8,&local_128)
            ;
            QString::fromLatin1(&local_c8,local_e8,local_e0);
            QString::remove(local_148,&local_c8,1);
            QString::~QString((QString *)&local_c8);
          }
          QString::simplified((QString *)&local_c8);
          ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
          QString::QString((QString *)&local_e8,"exec");
          pQVar7 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_210,(QString *)&local_e8);
          ::QVariant::operator=(pQVar7,(QVariant *)local_68);
          QString::~QString((QString *)&local_e8);
          ::QVariant::~QVariant((QVariant *)local_68);
          QString::~QString((QString *)&local_c8);
          QFileInfo::fileName();
          ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
          QString::QString((QString *)&local_e8,"id");
          pQVar7 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_210,(QString *)&local_e8);
          ::QVariant::operator=(pQVar7,(QVariant *)local_68);
          QString::~QString((QString *)&local_e8);
          ::QVariant::~QVariant((QVariant *)local_68);
          QString::~QString((QString *)&local_c8);
          bVar1 = false;
          bVar2 = false;
          QString::QString((QString *)&local_128,"name");
          QMap<QString,QVariant>::operator[]
                    ((QMap<QString,QVariant> *)&local_210,(QString *)&local_128);
          ::QVariant::toString();
          cVar4 = QString::isEmpty((QString *)&local_108);
          if (cVar4 == '\x01') {
LAB_0015c405:
            bVar3 = false;
          }
          else {
            QString::QString((QString *)&local_e8,"exec");
            bVar1 = true;
            QMap<QString,QVariant>::operator[]
                      ((QMap<QString,QVariant> *)&local_210,(QString *)&local_e8);
            ::QVariant::toString();
            bVar2 = true;
            cVar4 = QString::isEmpty((QString *)&local_c8);
            if (cVar4 == '\x01') goto LAB_0015c405;
            bVar3 = true;
          }
          if (bVar2) {
            QString::~QString((QString *)&local_c8);
          }
          if (bVar1) {
            QString::~QString((QString *)&local_e8);
          }
          QString::~QString((QString *)&local_108);
          QString::~QString((QString *)&local_128);
          if (bVar3) {
            ::QVariant::QVariant((QVariant *)local_68,(QMap *)&local_210);
            QList<QVariant>::append((QList<QVariant> *)(this + 0x10),(QVariant *)local_68);
            ::QVariant::~QVariant((QVariant *)local_68);
          }
          QString::~QString((QString *)local_148);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_210);
        }
        QSettings::~QSettings(local_198);
      }
      QList<QFileInfo>::iterator::operator++((iterator *)&local_220);
    }
    QList<QFileInfo>::~QList((QList<QFileInfo> *)local_168);
    QList<QString>::iterator::operator++((iterator *)&local_230);
  } while( true );
}



// ==== 0015c990  GliaSystemMenus::launch

/* GliaSystemMenus::launch(QString const&) */

void __thiscall GliaSystemMenus::launch(GliaSystemMenus *this,QString *param_1)

{
  char cVar1;
  QString *this_00;
  long in_FS_OFFSET;
  undefined8 local_158;
  undefined8 local_150;
  QList<QVariant> *local_148;
  undefined8 local_140;
  QString local_138 [32];
  QVariant local_118 [32];
  QString local_f8 [32];
  QString local_d8 [32];
  QVariant local_b8 [32];
  QString local_98 [32];
  QVariant local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_138,param_1);
  local_148 = (QList<QVariant> *)(this + 0x10);
  local_158 = QList<QVariant>::begin(local_148);
  local_150 = QList<QVariant>::end(local_148);
  while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_158,local_150),
        cVar1 != '\0') {
    local_140 = QList<QVariant>::iterator::operator*((iterator *)&local_158);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_78,param_1);
    ::QVariant::QVariant(local_b8);
    QString::QString(local_d8,"id");
    QMap<QString,QVariant>::value(local_98,local_118);
    cVar1 = ::operator==((QVariant *)local_98,local_78);
    ::QVariant::~QVariant((QVariant *)local_98);
    QString::~QString(local_d8);
    ::QVariant::~QVariant(local_b8);
    ::QVariant::~QVariant(local_78);
    if (cVar1 != '\0') {
      ::QVariant::QVariant((QVariant *)local_98);
      QString::QString(local_f8,"exec");
      QMap<QString,QVariant>::value((QString *)local_78,local_118);
      ::QVariant::toString();
      QString::operator=(local_138,local_d8);
      QString::~QString(local_d8);
      ::QVariant::~QVariant(local_78);
      QString::~QString(local_f8);
      ::QVariant::~QVariant((QVariant *)local_98);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_118);
    if (cVar1 != '\0') break;
    QList<QVariant>::iterator::operator++((iterator *)&local_158);
  }
  QString::QString(local_d8);
  QString::QString((QString *)local_78,"-c");
  QString::QString(local_60,local_138);
  QList<QString>::QList(local_f8,local_78,2);
  QString::QString((QString *)local_118,"/bin/sh");
  QProcess::startDetached((QString *)local_118,(QList *)local_f8,local_d8,(longlong *)0x0);
  QString::~QString((QString *)local_118);
  QList<QString>::~QList((QList<QString> *)local_f8);
  this_00 = aQStack_48;
  while (this_00 != (QString *)local_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QString::~QString(local_d8);
  QString::~QString(local_138);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015ce9e  GliaSystemMenus::openPath

/* GliaSystemMenus::openPath(QString const&) */

void __thiscall GliaSystemMenus::openPath(GliaSystemMenus *this,QString *param_1)

{
  QString *this_00;
  long in_FS_OFFSET;
  QString local_b8 [32];
  QList local_98 [32];
  QString local_78 [32];
  QString local_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_78);
  QString::QString(local_58,param_1);
  QList<QString>::QList(local_98,local_58,1);
  QString::QString(local_b8,"xdg-open");
  QProcess::startDetached(local_b8,local_98,local_78,(longlong *)0x0);
  QString::~QString(local_b8);
  QList<QString>::~QList((QList<QString> *)local_98);
  this_00 = (QString *)local_40;
  while (this_00 != local_58) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QString::~QString(local_78);
  if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015d162  GliaSystemMenus::~GliaSystemMenus

/* GliaSystemMenus::~GliaSystemMenus() */

void __thiscall GliaSystemMenus::~GliaSystemMenus(GliaSystemMenus *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c348;
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0015d19c  GliaSystemMenus::~GliaSystemMenus

/* GliaSystemMenus::~GliaSystemMenus() */

void __thiscall GliaSystemMenus::~GliaSystemMenus(GliaSystemMenus *this)

{
  ~GliaSystemMenus(this);
  operator_delete(this,0x28);
  return;
}


