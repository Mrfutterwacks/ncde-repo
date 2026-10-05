// Ghidra decompile of LaPivot.oracle — class/namespace AppMenuModel (20 functions). Raw; not source.

// ==== 0013a50c  AppMenuModel::qt_static_metacall

/* AppMenuModel::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void AppMenuModel::qt_static_metacall
               (AppMenuModel *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  long in_FS_OFFSET;
  QList local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 3) {
      getApps((AppMenuModel *)local_38,(QString *)param_1,*(QString **)(param_4 + 8));
      if (*(long *)param_4 != 0) {
        QList<QVariant>::operator=(*(QList<QVariant> **)param_4,local_38);
      }
      QList<QVariant>::~QList((QList<QVariant> *)local_38);
    }
    else if (param_3 < 4) {
      if (param_3 == 2) {
        getCategories();
        if (*(long *)param_4 != 0) {
          QList<QString>::operator=(*(QList<QString> **)param_4,local_38);
        }
        QList<QString>::~QList((QList<QString> *)local_38);
      }
      else if (param_3 < 3) {
        if (param_3 == 0) {
          changed(param_1);
        }
        else if (param_3 == 1) {
          reload(param_1);
        }
      }
    }
  }
  if (param_2 == 5) {
    QtMocHelpers::indexOfMethod<void(AppMenuModel::*)()>
              (param_4,(void **)changed,(_func_void *)0x0,0);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013a680  AppMenuModel::metaObject

/* AppMenuModel::metaObject() const */

undefined1 * __thiscall AppMenuModel::metaObject(AppMenuModel *this)

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



// ==== 0013a6c8  AppMenuModel::qt_metacast

/* AppMenuModel::qt_metacast(char const*) */

AppMenuModel * __thiscall AppMenuModel::qt_metacast(AppMenuModel *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (AppMenuModel *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"AppMenuModel");
    if (iVar1 != 0) {
      this = (AppMenuModel *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013a71c  AppMenuModel::qt_metacall

/* AppMenuModel::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
AppMenuModel::qt_metacall(AppMenuModel *this,int param_2,undefined4 param_3,undefined8 *param_4)

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



// ==== 0013a7d6  AppMenuModel::changed

/* AppMenuModel::changed() */

void __thiscall AppMenuModel::changed(AppMenuModel *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 00154830  AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}::operator()

/* AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  reload(*(AppMenuModel **)this);
  return;
}



// ==== 0015484e  AppMenuModel::AppMenuModel

/* AppMenuModel::AppMenuModel(QObject*) */

void __thiscall AppMenuModel::AppMenuModel(AppMenuModel *this,QObject *param_1)

{
  long in_FS_OFFSET;
  AppMenuModel *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c498;
  QList<AppMenuModel::AppEntry>::QList((QList<AppMenuModel::AppEntry> *)(this + 0x10));
  local_28 = this;
  QTimer::singleShot<int,AppMenuModel::AppMenuModel(QObject*)::_lambda()_1_>
            (0,(ContextType *)this,(_lambda___1_ *)&local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015497c  AppMenuModel::AppEntry::~AppEntry

/* AppMenuModel::AppEntry::~AppEntry() */

void __thiscall AppMenuModel::AppEntry::~AppEntry(AppEntry *this)

{
  QString::~QString((QString *)(this + 0x48));
  QString::~QString((QString *)(this + 0x30));
  QString::~QString((QString *)(this + 0x18));
  QString::~QString((QString *)this);
  return;
}



// ==== 001549c8  AppMenuModel::reload()::{lambda(AppMenuModel::AppEntry_const&,AppMenuModel::AppEntry_const&)#1}::operator()

/* AppMenuModel::reload()::{lambda(AppMenuModel::AppEntry const&, AppMenuModel::AppEntry
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(AppMenuModel::AppEntry const&, AppMenuModel::AppEntry
   const&) const */

uint __thiscall
AppMenuModel::reload()::{lambda(AppMenuModel::AppEntry_const&,AppMenuModel::AppEntry_const&)#1}::
operator()(_lambda_AppMenuModel__AppEntry_const__AppMenuModel__AppEntry_const___1_ *this,
          AppEntry *param_1,AppEntry *param_2)

{
  uint uVar1;
  
  uVar1 = QString::compare(param_1,param_2,0);
  return uVar1 >> 0x1f;
}



// ==== 001549fa  AppMenuModel::reload

/* AppMenuModel::reload() */

void __thiscall AppMenuModel::reload(AppMenuModel *this)

{
  char cVar1;
  QList<QString> *pQVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  char **ppcVar5;
  QString *this_00;
  long lVar6;
  long in_FS_OFFSET;
  QString *local_198;
  QSet<QString> local_188 [8];
  undefined8 local_180;
  undefined8 local_178;
  ulong local_170;
  QList<QString> *local_168;
  QString *local_160;
  QList<QFileInfo> *local_158;
  undefined8 local_150;
  QList<QString> local_148 [32];
  ulong local_128 [4];
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [16];
  undefined1 local_b8 [16];
  undefined1 local_a8 [16];
  undefined1 local_98 [16];
  undefined1 local_88 [16];
  undefined1 local_78 [16];
  char *local_60;
  QString local_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  QList<AppMenuModel::AppEntry>::clear((QList<AppMenuModel::AppEntry> *)(this + 0x10));
  QStandardPaths::standardLocations(local_148,3);
  QString::QString((QString *)local_128,"/usr/share/applications");
  pQVar2 = (QList<QString> *)QList<QString>::operator<<(local_148,(QString *)local_128);
  QString::QString(local_108,"/usr/local/share/applications");
  pQVar2 = (QList<QString> *)QList<QString>::operator<<(pQVar2,local_108);
  QDir::homePath();
  ::operator+(local_c8,(char *)local_e8);
  QList<QString>::operator<<(pQVar2,local_c8);
  QString::~QString(local_c8);
  QString::~QString(local_e8);
  QString::~QString(local_108);
  QString::~QString((QString *)local_128);
  QListSpecialMethods<QString>::removeDuplicates((QListSpecialMethods<QString> *)local_148);
  QSet<QString>::QSet(local_188);
  local_168 = local_148;
  local_180 = QList<QString>::begin(local_168);
  local_178 = QList<QString>::end(local_168);
  while( true ) {
    cVar1 = QList<QString>::iterator::operator!=((iterator *)&local_180,local_178);
    if (cVar1 == '\0') break;
    local_160 = (QString *)QList<QString>::iterator::operator*((iterator *)&local_180);
    QDir::QDir((QDir *)local_e8,local_160);
    QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_128,0xffffffff);
    QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)&local_170,2);
    local_198 = local_58;
    local_60 = "*.desktop";
    ppcVar5 = &local_60;
    for (lVar6 = 0; -1 < lVar6; lVar6 = lVar6 + -1) {
      QString::QString(local_198,*ppcVar5);
      local_198 = local_198 + 0x18;
      ppcVar5 = ppcVar5 + 1;
    }
    QList<QString>::QList(local_c8,local_58,1);
    QDir::entryInfoList(local_108,local_e8,local_c8,local_170 & 0xffffffff,local_128[0] & 0xffffffff
                       );
    QList<QString>::~QList((QList<QString> *)local_c8);
    this_00 = (QString *)local_40;
    while (this_00 != local_58) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QDir::~QDir((QDir *)local_e8);
    local_158 = (QList<QFileInfo> *)local_108;
    local_170 = QList<QFileInfo>::begin(local_158);
    local_128[0] = QList<QFileInfo>::end(local_158);
    while( true ) {
      cVar1 = QList<QFileInfo>::const_iterator::operator!=
                        ((const_iterator *)&local_170,local_128[0]);
      if (cVar1 == '\0') break;
      local_150 = QList<QFileInfo>::const_iterator::operator*((const_iterator *)&local_170);
      QFileInfo::fileName();
      cVar1 = QSet<QString>::contains(local_188,local_c8);
      QString::~QString(local_c8);
      if (cVar1 == '\0') {
        QFileInfo::fileName();
        QSet<QString>::insert(local_e8);
        QString::~QString(local_c8);
        local_c8[0] = (QString)0x0;
        local_c8[1] = (QString)0x0;
        local_c8[2] = (QString)0x0;
        local_c8[3] = (QString)0x0;
        local_c8[4] = (QString)0x0;
        local_c8[5] = (QString)0x0;
        local_c8[6] = (QString)0x0;
        local_c8[7] = (QString)0x0;
        local_c8[8] = (QString)0x0;
        local_c8[9] = (QString)0x0;
        local_c8[10] = (QString)0x0;
        local_c8[0xb] = (QString)0x0;
        local_c8[0xc] = (QString)0x0;
        local_c8[0xd] = (QString)0x0;
        local_c8[0xe] = (QString)0x0;
        local_c8[0xf] = (QString)0x0;
        local_b8 = (undefined1  [16])0x0;
        local_a8 = (undefined1  [16])0x0;
        local_98 = (undefined1  [16])0x0;
        local_88 = (undefined1  [16])0x0;
        local_78 = (undefined1  [16])0x0;
        QFileInfo::absoluteFilePath();
        cVar1 = parseDesktop(local_e8,(AppEntry *)local_c8);
        QString::~QString(local_e8);
        if (cVar1 != '\0') {
          QList<AppMenuModel::AppEntry>::append
                    ((QList<AppMenuModel::AppEntry> *)(this + 0x10),(AppEntry *)local_c8);
        }
        AppEntry::~AppEntry((AppEntry *)local_c8);
      }
      QList<QFileInfo>::const_iterator::operator++((const_iterator *)&local_170);
    }
    QList<QFileInfo>::~QList((QList<QFileInfo> *)local_108);
    QList<QString>::iterator::operator++((iterator *)&local_180);
  }
  uVar3 = QList<AppMenuModel::AppEntry>::end((QList<AppMenuModel::AppEntry> *)(this + 0x10));
  uVar4 = QList<AppMenuModel::AppEntry>::begin((QList<AppMenuModel::AppEntry> *)(this + 0x10));
  std::
  sort<QList<AppMenuModel::AppEntry>::iterator,AppMenuModel::reload()::_lambda(AppMenuModel::AppEntry_const&,AppMenuModel::AppEntry_const&)_1_>
            (uVar4,uVar3);
  changed(this);
  QSet<QString>::~QSet(local_188);
  QList<QString>::~QList(local_148);
  if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001550d4  AppMenuModel::getCategories

/* AppMenuModel::getCategories() const */

QList<QString> * AppMenuModel::getCategories(void)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  long in_RSI;
  QList<QString> *in_RDI;
  long in_FS_OFFSET;
  undefined8 local_50;
  QList<AppMenuModel::AppEntry> *local_48;
  long local_40;
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
  *(undefined8 *)(in_RDI + 0x10) = 0;
  QString::QString((QString *)local_38,"All");
  QList<QString>::operator<<(in_RDI,(QString *)local_38);
  QString::~QString((QString *)local_38);
  local_48 = (QList<AppMenuModel::AppEntry> *)(in_RSI + 0x10);
  local_50 = QList<AppMenuModel::AppEntry>::begin(local_48);
  local_38[0] = QList<AppMenuModel::AppEntry>::end(local_48);
  while( true ) {
    cVar1 = QList<AppMenuModel::AppEntry>::const_iterator::operator!=
                      ((const_iterator *)&local_50,local_38[0]);
    if (cVar1 == '\0') break;
    local_40 = QList<AppMenuModel::AppEntry>::const_iterator::operator*((const_iterator *)&local_50)
    ;
    cVar1 = QListSpecialMethods<QString>::contains
                      ((QListSpecialMethods<QString> *)in_RDI,local_40 + 0x48,1);
    if (cVar1 != '\x01') {
      QList<QString>::operator<<(in_RDI,(QString *)(local_40 + 0x48));
    }
    QList<AppMenuModel::AppEntry>::const_iterator::operator++((const_iterator *)&local_50);
  }
  uVar2 = QList<QString>::end(in_RDI);
  local_38[0] = QList<QString>::begin(in_RDI);
  uVar3 = QList<QString>::iterator::operator+((iterator *)local_38,1);
  std::sort<QList<QString>::iterator>(uVar3,uVar2);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0015536a  AppMenuModel::getApps

/* AppMenuModel::getApps(QString const&, QString const&) const */

AppMenuModel * __thiscall
AppMenuModel::getApps(AppMenuModel *this,QString *param_1,QString *param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  QVariant *pQVar5;
  long in_FS_OFFSET;
  undefined8 local_d8;
  undefined8 local_d0;
  QList<AppMenuModel::AppEntry> *local_c8;
  QString *local_c0;
  QString local_b8 [32];
  undefined8 local_98 [4];
  char *local_78 [4];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])this = (undefined1  [16])0x0;
  *(undefined8 *)(this + 0x10) = 0;
  QString::trimmed((QString *)local_78);
  QString::toLower(local_b8);
  QString::~QString((QString *)local_78);
  local_c8 = (QList<AppMenuModel::AppEntry> *)(param_1 + 0x10);
  local_d8 = QList<AppMenuModel::AppEntry>::begin(local_c8);
  local_d0 = QList<AppMenuModel::AppEntry>::end(local_c8);
  do {
    cVar4 = QList<AppMenuModel::AppEntry>::const_iterator::operator!=
                      ((const_iterator *)&local_d8,local_d0);
    if (cVar4 == '\0') {
      QString::~QString(local_b8);
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return this;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_c0 = (QString *)
               QList<AppMenuModel::AppEntry>::const_iterator::operator*((const_iterator *)&local_d8)
    ;
    cVar4 = QString::isEmpty(param_2);
    if (cVar4 == '\x01') {
LAB_001554ac:
      bVar1 = false;
    }
    else {
      local_78[0] = "All";
      cVar4 = ::operator!=(param_2,local_78);
      if ((cVar4 == '\0') || (cVar4 = ::operator!=(local_c0 + 0x48,param_2), cVar4 == '\0'))
      goto LAB_001554ac;
      bVar1 = true;
    }
    if (!bVar1) {
      bVar2 = false;
      bVar1 = false;
      cVar4 = QString::isEmpty(local_b8);
      if (cVar4 == '\x01') {
LAB_0015556b:
        bVar3 = false;
      }
      else {
        QString::toLower((QString *)local_98);
        bVar2 = true;
        cVar4 = QString::contains((QString *)local_98,local_b8,1);
        if (cVar4 == '\x01') goto LAB_0015556b;
        QString::toLower((QString *)local_78);
        bVar1 = true;
        cVar4 = QString::contains((QString *)local_78,local_b8,1);
        if (cVar4 == '\x01') goto LAB_0015556b;
        bVar3 = true;
      }
      if (bVar1) {
        QString::~QString((QString *)local_78);
      }
      if (bVar2) {
        QString::~QString((QString *)local_98);
      }
      if (!bVar3) {
        local_98[0] = 0;
        ::QVariant::QVariant(local_58,local_c0);
        QString::QString((QString *)local_78,"name");
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)local_98,(QString *)local_78);
        ::QVariant::operator=(pQVar5,local_58);
        QString::~QString((QString *)local_78);
        ::QVariant::~QVariant(local_58);
        ::QVariant::QVariant(local_58,local_c0 + 0x18);
        QString::QString((QString *)local_78,"exec");
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)local_98,(QString *)local_78);
        ::QVariant::operator=(pQVar5,local_58);
        QString::~QString((QString *)local_78);
        ::QVariant::~QVariant(local_58);
        ::QVariant::QVariant(local_58,local_c0 + 0x30);
        QString::QString((QString *)local_78,"icon");
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)local_98,(QString *)local_78);
        ::QVariant::operator=(pQVar5,local_58);
        QString::~QString((QString *)local_78);
        ::QVariant::~QVariant(local_58);
        ::QVariant::QVariant(local_58,local_c0 + 0x48);
        QString::QString((QString *)local_78,"category");
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)local_98,(QString *)local_78);
        ::QVariant::operator=(pQVar5,local_58);
        QString::~QString((QString *)local_78);
        ::QVariant::~QVariant(local_58);
        ::QVariant::QVariant(local_58,(QMap *)local_98);
        QList<QVariant>::append((QList<QVariant> *)this,local_58);
        ::QVariant::~QVariant(local_58);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_98);
      }
    }
    QList<AppMenuModel::AppEntry>::const_iterator::operator++((const_iterator *)&local_d8);
  } while( true );
}



// ==== 00155952  AppMenuModel::mapCategory

/* AppMenuModel::mapCategory(QString const&) */

AppMenuModel * __thiscall AppMenuModel::mapCategory(AppMenuModel *this,QString *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QString local_68 [32];
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_a8,param_1);
  bVar2 = false;
  bVar1 = false;
  QString::QString(local_88,"AudioVideo");
  cVar4 = QString::contains(local_a8,local_88,1);
  if (cVar4 == '\0') {
    QString::QString(local_68,"Audio");
    bVar2 = true;
    cVar4 = QString::contains(local_a8,local_68,1);
    if (cVar4 == '\0') {
      QString::QString(local_48,"Video");
      bVar1 = true;
      cVar4 = QString::contains(local_a8,local_48,1);
      if (cVar4 == '\0') {
        bVar3 = false;
        goto LAB_00155a69;
      }
    }
  }
  bVar3 = true;
LAB_00155a69:
  if (bVar1) {
    QString::~QString(local_48);
  }
  if (bVar2) {
    QString::~QString(local_68);
  }
  QString::~QString(local_88);
  if (bVar3) {
    QString::QString((QString *)this,"Sound & Video");
  }
  else {
    QString::QString(local_48,"Development");
    cVar4 = QString::contains(local_a8,local_48,1);
    QString::~QString(local_48);
    if (cVar4 == '\0') {
      QString::QString(local_48,"Graphics");
      cVar4 = QString::contains(local_a8,local_48,1);
      QString::~QString(local_48);
      if (cVar4 == '\0') {
        QString::QString(local_48,"Network");
        cVar4 = QString::contains(local_a8,local_48,1);
        QString::~QString(local_48);
        if (cVar4 == '\0') {
          QString::QString(local_48,"Office");
          cVar4 = QString::contains(local_a8,local_48,1);
          QString::~QString(local_48);
          if (cVar4 == '\0') {
            QString::QString(local_48,"Game");
            cVar4 = QString::contains(local_a8,local_48,1);
            QString::~QString(local_48);
            if (cVar4 == '\0') {
              QString::QString(local_48,"Accessibility");
              cVar4 = QString::contains(local_a8,local_48,1);
              QString::~QString(local_48);
              if (cVar4 == '\0') {
                QString::QString(local_48,"Settings");
                cVar4 = QString::contains(local_a8,local_48,1);
                QString::~QString(local_48);
                if (cVar4 == '\0') {
                  QString::QString(local_48,"System");
                  cVar4 = QString::contains(local_a8,local_48,1);
                  QString::~QString(local_48);
                  if (cVar4 == '\0') {
                    QString::QString(local_48,"Science");
                    cVar4 = QString::contains(local_a8,local_48,1);
                    QString::~QString(local_48);
                    if (cVar4 == '\0') {
                      QString::QString(local_48,"Education");
                      cVar4 = QString::contains(local_a8,local_48,1);
                      QString::~QString(local_48);
                      if (cVar4 == '\0') {
                        QString::QString(local_48,"Utility");
                        cVar4 = QString::contains(local_a8,local_48,1);
                        QString::~QString(local_48);
                        if (cVar4 == '\0') {
                          QString::QString((QString *)this,"Other");
                        }
                        else {
                          QString::QString((QString *)this,"Utilities");
                        }
                      }
                      else {
                        QString::QString((QString *)this,"Education");
                      }
                    }
                    else {
                      QString::QString((QString *)this,"Science & Math");
                    }
                  }
                  else {
                    QString::QString((QString *)this,"System");
                  }
                }
                else {
                  QString::QString((QString *)this,"Settings");
                }
              }
              else {
                QString::QString((QString *)this,"Accessibility");
              }
            }
            else {
              QString::QString((QString *)this,"Games");
            }
          }
          else {
            QString::QString((QString *)this,"Office");
          }
        }
        else {
          QString::QString((QString *)this,"Internet");
        }
      }
      else {
        QString::QString((QString *)this,"Graphics");
      }
    }
    else {
      QString::QString((QString *)this,"Development");
    }
  }
  QString::~QString(local_a8);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00156077  AppMenuModel::stripFieldCodes

/* AppMenuModel::stripFieldCodes(QString) */

AppMenuModel * __thiscall AppMenuModel::stripFieldCodes(AppMenuModel *this,undefined8 param_2)

{
  long in_FS_OFFSET;
  char *local_78;
  undefined8 *local_70;
  initializer_list<char_const*> *local_68;
  undefined8 *local_60;
  undefined1 *local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_50 = 0x12;
  local_58 = C_103_0;
  local_68 = (initializer_list<char_const*> *)&local_58;
  local_70 = (undefined8 *)std::initializer_list<char_const*>::begin(local_68);
  local_60 = (undefined8 *)std::initializer_list<char_const*>::end(local_68);
  for (; local_70 != local_60; local_70 = local_70 + 1) {
    local_78 = (char *)*local_70;
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_48,&local_78);
    QString::fromLatin1(local_38,local_48,local_40);
    QString::remove(param_2,local_38,1);
    QString::~QString(local_38);
  }
  QString::simplified((QString *)this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001561ad  AppMenuModel::parseDesktop

/* AppMenuModel::parseDesktop(QString const&, AppMenuModel::AppEntry&) */

undefined8 AppMenuModel::parseDesktop(QString *param_1,AppEntry *param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  long in_FS_OFFSET;
  QSettings local_d8 [16];
  char *local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined8 local_98;
  undefined8 local_90;
  QVariant local_78 [32];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QSettings::QSettings(local_d8,param_1,1,0);
  lVar4 = QtPrivate::lengthHelperContainer<char,14ul>("Desktop Entry");
  QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_98,"Desktop Entry",lVar4);
  QSettings::beginGroup(local_d8,local_98,local_90);
  local_c8 = "Application";
  lVar4 = QtPrivate::lengthHelperContainer<char,5ul>("Type");
  QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_b8,"Type",lVar4);
  QSettings::value(local_58,local_d8,local_b8,local_b0);
  ::QVariant::toString();
  cVar3 = ::operator!=((QString *)&local_98,&local_c8);
  QString::~QString((QString *)&local_98);
  ::QVariant::~QVariant(local_58);
  if (cVar3 != '\0') {
    uVar5 = 0;
    goto LAB_00156783;
  }
  bVar1 = false;
  lVar4 = QtPrivate::lengthHelperContainer<char,10ul>("NoDisplay");
  QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_b8,"NoDisplay",lVar4);
  QSettings::value(local_78,local_d8,local_b8,local_b0);
  cVar3 = ::QVariant::toBool();
  if (cVar3 == '\0') {
    lVar4 = QtPrivate::lengthHelperContainer<char,7ul>("Hidden");
    QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_98,"Hidden",lVar4);
    QSettings::value(local_58,local_d8,local_98,local_90);
    bVar1 = true;
    cVar3 = ::QVariant::toBool();
    if (cVar3 != '\0') goto LAB_0015640c;
    bVar2 = false;
  }
  else {
LAB_0015640c:
    bVar2 = true;
  }
  if (bVar1) {
    ::QVariant::~QVariant(local_58);
  }
  ::QVariant::~QVariant(local_78);
  if (bVar2) {
    uVar5 = 0;
  }
  else {
    lVar4 = QtPrivate::lengthHelperContainer<char,5ul>("Name");
    QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_b8,"Name",lVar4);
    QSettings::value(local_58,local_d8,local_b8,local_b0);
    ::QVariant::toString();
    QString::operator=((QString *)param_2,(QString *)&local_98);
    QString::~QString((QString *)&local_98);
    ::QVariant::~QVariant(local_58);
    lVar4 = QtPrivate::lengthHelperContainer<char,5ul>("Exec");
    QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_c8,"Exec",lVar4);
    QSettings::value(local_58,local_d8,local_c8,local_c0);
    ::QVariant::toString();
    stripFieldCodes((AppMenuModel *)&local_98,&local_b8);
    QString::operator=((QString *)(param_2 + 0x18),(QString *)&local_98);
    QString::~QString((QString *)&local_98);
    QString::~QString((QString *)&local_b8);
    ::QVariant::~QVariant(local_58);
    lVar4 = QtPrivate::lengthHelperContainer<char,5ul>("Icon");
    QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_b8,"Icon",lVar4);
    QSettings::value(local_58,local_d8,local_b8,local_b0);
    ::QVariant::toString();
    QString::operator=((QString *)(param_2 + 0x30),(QString *)&local_98);
    QString::~QString((QString *)&local_98);
    ::QVariant::~QVariant(local_58);
    lVar4 = QtPrivate::lengthHelperContainer<char,11ul>("Categories");
    QAnyStringView::QAnyStringView<char,true>((QAnyStringView *)&local_c8,"Categories",lVar4);
    QSettings::value(local_58,local_d8,local_c8,local_c0);
    ::QVariant::toString();
    mapCategory((AppMenuModel *)&local_98,(QString *)&local_b8);
    QString::operator=((QString *)(param_2 + 0x48),(QString *)&local_98);
    QString::~QString((QString *)&local_98);
    QString::~QString((QString *)&local_b8);
    ::QVariant::~QVariant(local_58);
    cVar3 = QString::isEmpty((QString *)param_2);
    if ((cVar3 == '\x01') ||
       (cVar3 = QString::isEmpty((QString *)(param_2 + 0x18)), cVar3 == '\x01')) {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
  }
LAB_00156783:
  QSettings::~QSettings(local_d8);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar5;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00156982  AppMenuModel::~AppMenuModel

/* AppMenuModel::~AppMenuModel() */

void __thiscall AppMenuModel::~AppMenuModel(AppMenuModel *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c498;
  QList<AppMenuModel::AppEntry>::~QList((QList<AppMenuModel::AppEntry> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001569bc  AppMenuModel::~AppMenuModel

/* AppMenuModel::~AppMenuModel() */

void __thiscall AppMenuModel::~AppMenuModel(AppMenuModel *this)

{
  ~AppMenuModel(this);
  operator_delete(this,0x28);
  return;
}



// ==== 001b659a  AppMenuModel::AppEntry::AppEntry

/* AppMenuModel::AppEntry::AppEntry(AppMenuModel::AppEntry const&) */

void __thiscall AppMenuModel::AppEntry::AppEntry(AppEntry *this,AppEntry *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  return;
}



// ==== 001b6612  AppMenuModel::AppEntry::AppEntry

/* AppMenuModel::AppEntry::AppEntry(AppMenuModel::AppEntry&&) */

void __thiscall AppMenuModel::AppEntry::AppEntry(AppEntry *this,AppEntry *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  return;
}



// ==== 001bfb90  AppMenuModel::AppEntry::operator=

/* AppMenuModel::AppEntry::TEMPNAMEPLACEHOLDERVALUE(AppMenuModel::AppEntry&&) */

AppEntry * __thiscall AppMenuModel::AppEntry::operator=(AppEntry *this,AppEntry *param_1)

{
  QString::operator=((QString *)this,(QString *)param_1);
  QString::operator=((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::operator=((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::operator=((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  return this;
}


