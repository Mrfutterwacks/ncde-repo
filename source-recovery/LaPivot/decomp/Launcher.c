// Ghidra decompile of LaPivot.oracle — class/namespace Launcher (13 functions). Raw; not source.

// ==== 0013b7f8  Launcher::qt_static_metacall

/* Launcher::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void Launcher::qt_static_metacall(Launcher *param_1,int param_2,int param_3,long *param_4)

{
  long in_FS_OFFSET;
  Launcher local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 5) {
      logout();
    }
    else if (param_3 < 6) {
      if (param_3 == 4) {
        homePath(local_28);
        if (*param_4 != 0) {
          QString::operator=((QString *)*param_4,(QString *)local_28);
        }
        QString::~QString((QString *)local_28);
      }
      else if (param_3 < 5) {
        if (param_3 == 3) {
          launchWithFiles(param_1,(QString *)param_4[1],(QList *)param_4[2]);
        }
        else if (param_3 < 4) {
          if (param_3 == 2) {
            systemCommand(param_1,(QString *)param_4[1]);
          }
          else if (param_3 < 3) {
            if (param_3 == 0) {
              launchExec(param_1,(QString *)param_4[1]);
            }
            else if (param_3 == 1) {
              launch(param_1,(QString *)param_4[1]);
            }
          }
        }
      }
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013b974  Launcher::metaObject

/* Launcher::metaObject() const */

undefined1 * __thiscall Launcher::metaObject(Launcher *this)

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



// ==== 0013b9bc  Launcher::qt_metacast

/* Launcher::qt_metacast(char const*) */

Launcher * __thiscall Launcher::qt_metacast(Launcher *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (Launcher *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"Launcher");
    if (iVar1 != 0) {
      this = (Launcher *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013ba10  Launcher::qt_metacall

/* Launcher::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
Launcher::qt_metacall(Launcher *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 6) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -6;
    }
    if (param_2 == 7) {
      if (local_28 < 6) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -6;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015e05a  Launcher::Launcher

/* Launcher::Launcher(QObject*) */

void __thiscall Launcher::Launcher(Launcher *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c1f8;
  return;
}



// ==== 0015e08e  Launcher::launchExec

/* Launcher::launchExec(QString const&) */

void __thiscall Launcher::launchExec(Launcher *this,QString *param_1)

{
  char cVar1;
  QString *pQVar2;
  long in_FS_OFFSET;
  QList<QString> local_78 [32];
  QList local_58 [32];
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::trimmed((QString *)&local_38);
  cVar1 = QString::isEmpty((QString *)&local_38);
  QString::~QString((QString *)&local_38);
  if (cVar1 == '\0') {
    QStringView::QStringView<QString,true>((QStringView *)&local_38,param_1);
    QProcess::splitCommand(local_78,local_38,local_30);
    cVar1 = QList<QString>::isEmpty(local_78);
    if (cVar1 == '\0') {
      QString::QString((QString *)&local_38);
      QList<QString>::mid((longlong)local_58,(longlong)local_78);
      pQVar2 = (QString *)QList<QString>::first(local_78);
      QProcess::startDetached(pQVar2,local_58,(QString *)&local_38,(longlong *)0x0);
      QList<QString>::~QList((QList<QString> *)local_58);
      QString::~QString((QString *)&local_38);
    }
    QList<QString>::~QList(local_78);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015e204  Launcher::launch

/* Launcher::launch(QString const&) */

void __thiscall Launcher::launch(Launcher *this,QString *param_1)

{
  launchExec(this,param_1);
  return;
}



// ==== 0015e22a  Launcher::systemCommand

/* Launcher::systemCommand(QString const&) */

void __thiscall Launcher::systemCommand(Launcher *this,QString *param_1)

{
  launchExec(this,param_1);
  return;
}



// ==== 0015e250  Launcher::launchWithFiles

/* Launcher::launchWithFiles(QString const&, QList<QVariant> const&) */

void __thiscall Launcher::launchWithFiles(Launcher *this,QString *param_1,QList *param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined8 local_98;
  undefined8 local_90;
  QList<QVariant> *local_88;
  undefined8 local_80;
  QList<QString> local_78 [32];
  QString local_58 [32];
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QStringView::QStringView<QString,true>((QStringView *)&local_38,param_1);
  QProcess::splitCommand(local_78,local_38,local_30);
  cVar1 = QList<QString>::isEmpty(local_78);
  if (cVar1 == '\0') {
    QList<QString>::takeFirst();
    local_88 = (QList<QVariant> *)param_2;
    local_98 = QList<QVariant>::begin((QList<QVariant> *)param_2);
    local_90 = QList<QVariant>::end(local_88);
    while (cVar1 = QList<QVariant>::const_iterator::operator!=((const_iterator *)&local_98,local_90)
          , cVar1 != '\0') {
      local_80 = QList<QVariant>::const_iterator::operator*((const_iterator *)&local_98);
      ::QVariant::toString();
      QList<QString>::operator<<(local_78,(QString *)&local_38);
      QString::~QString((QString *)&local_38);
      QList<QVariant>::const_iterator::operator++((const_iterator *)&local_98);
    }
    QString::QString((QString *)&local_38);
    QProcess::startDetached(local_58,(QList *)local_78,(QString *)&local_38,(longlong *)0x0);
    QString::~QString((QString *)&local_38);
    QString::~QString(local_58);
  }
  QList<QString>::~QList(local_78);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015e44c  Launcher::homePath

/* Launcher::homePath() const */

Launcher * __thiscall Launcher::homePath(Launcher *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  QDir::homePath();
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0015e492  Launcher::logout

/* Launcher::logout() */

void Launcher::logout(void)

{
  QCoreApplication::quit();
  return;
}



// ==== 0015e57e  Launcher::~Launcher

/* Launcher::~Launcher() */

void __thiscall Launcher::~Launcher(Launcher *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c1f8;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 0015e5a8  Launcher::~Launcher

/* Launcher::~Launcher() */

void __thiscall Launcher::~Launcher(Launcher *this)

{
  ~Launcher(this);
  operator_delete(this,0x10);
  return;
}


