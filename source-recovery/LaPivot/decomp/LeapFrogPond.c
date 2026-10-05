// Ghidra decompile of LaPivot.oracle — class/namespace LeapFrogPond (29 functions). Raw; not source.

// ==== 0013baca  LeapFrogPond::qt_static_metacall

/* LeapFrogPond::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void LeapFrogPond::qt_static_metacall
               (LeapFrogPond *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  bool bVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QString local_78 [32];
  undefined4 local_58 [6];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0xf) {
      QString::QString((QString *)local_58);
      exportLilyPad(local_78);
      QString::~QString((QString *)local_58);
      if (*(long *)param_4 != 0) {
        QString::operator=(*(QString **)param_4,local_78);
      }
      QString::~QString(local_78);
    }
    else if (param_3 < 0x10) {
      if (param_3 == 0xe) {
        exportLilyPad((QString *)local_58);
        if (*(long *)param_4 != 0) {
          QString::operator=(*(QString **)param_4,(QString *)local_58);
        }
        QString::~QString((QString *)local_58);
      }
      else if (param_3 < 0xf) {
        if (param_3 == 0xd) {
          QString::QString((QString *)local_58);
          exportCsv(local_78);
          QString::~QString((QString *)local_58);
          if (*(long *)param_4 != 0) {
            QString::operator=(*(QString **)param_4,local_78);
          }
          QString::~QString(local_78);
        }
        else if (param_3 < 0xe) {
          if (param_3 == 0xc) {
            exportCsv((QString *)local_58);
            if (*(long *)param_4 != 0) {
              QString::operator=(*(QString **)param_4,(QString *)local_58);
            }
            QString::~QString((QString *)local_58);
          }
          else if (param_3 < 0xd) {
            if (param_3 == 0xb) {
              local_58[0] = archivePast(param_1);
              if (*(long *)param_4 != 0) {
                **(undefined4 **)param_4 = local_58[0];
              }
            }
            else if (param_3 < 0xc) {
              if (param_3 == 10) {
                local_58[0] = reconcile(param_1);
                if (*(long *)param_4 != 0) {
                  **(undefined4 **)param_4 = local_58[0];
                }
              }
              else if (param_3 < 0xb) {
                if (param_3 == 9) {
                  tally();
                  if (*(long *)param_4 != 0) {
                    QMap<QString,QVariant>::operator=
                              (*(QMap<QString,QVariant> **)param_4,(QMap *)local_58);
                  }
                  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_58);
                }
                else if (param_3 < 10) {
                  if (param_3 == 8) {
                    setNotice(param_1,*(QString **)(param_4 + 8));
                  }
                  else if (param_3 < 9) {
                    if (param_3 == 7) {
                      removeAppt(param_1,*(QString **)(param_4 + 8));
                    }
                    else if (param_3 < 8) {
                      if (param_3 == 6) {
                        removeNote(param_1,*(QString **)(param_4 + 8));
                      }
                      else if (param_3 < 7) {
                        if (param_3 == 5) {
                          addNote(param_1,*(QString **)(param_4 + 8));
                        }
                        else if (param_3 < 6) {
                          if (param_3 == 4) {
                            reconciled(param_1,**(int **)(param_4 + 8));
                          }
                          else if (param_3 < 5) {
                            if (param_3 == 3) {
                              exported(param_1,*(QString **)(param_4 + 8));
                            }
                            else if (param_3 < 4) {
                              if (param_3 == 2) {
                                archived(param_1,**(int **)(param_4 + 8));
                              }
                              else if (param_3 < 3) {
                                if (param_3 == 0) {
                                  notesChanged(param_1);
                                }
                                else if (param_3 == 1) {
                                  noticeChanged(param_1);
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
  if ((param_2 != 5) ||
     ((((bVar1 = QtMocHelpers::indexOfMethod<void(LeapFrogPond::*)()>
                           (param_4,(void **)notesChanged,(_func_void *)0x0,0), !bVar1 &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(LeapFrogPond::*)()>
                           (param_4,(void **)noticeChanged,(_func_void *)0x0,1), !bVar1)) &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(LeapFrogPond::*)(int)>
                          (param_4,(void **)archived,(_func_void_int *)0x0,2), !bVar1)) &&
      ((bVar1 = QtMocHelpers::indexOfMethod<void(LeapFrogPond::*)(QString_const&)>
                          (param_4,(void **)exported,(_func_void_QString_ptr *)0x0,3), !bVar1 &&
       (bVar1 = QtMocHelpers::indexOfMethod<void(LeapFrogPond::*)(int)>
                          (param_4,(void **)reconciled,(_func_void_int *)0x0,4), !bVar1)))))) {
    if (param_2 == 1) {
      this = *(QList<QVariant> **)param_4;
      if (param_3 == 3) {
        appts();
        QList<QVariant>::operator=(this,(QList *)local_58);
        QList<QVariant>::~QList((QList<QVariant> *)local_58);
      }
      else if (param_3 < 4) {
        if (param_3 == 2) {
          notice();
          QString::operator=((QString *)this,(QString *)local_58);
          QString::~QString((QString *)local_58);
        }
        else if (param_3 < 3) {
          if (param_3 == 0) {
            notes();
            QList<QVariant>::operator=(this,(QList *)local_58);
            QList<QVariant>::~QList((QList<QVariant> *)local_58);
          }
          else if (param_3 == 1) {
            uVar2 = noteCount(param_1);
            *(undefined4 *)this = uVar2;
          }
        }
      }
    }
    if ((param_2 == 2) && (param_3 == 2)) {
      setNotice(param_1,*(QString **)param_4);
    }
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013c354  LeapFrogPond::metaObject

/* LeapFrogPond::metaObject() const */

undefined1 * __thiscall LeapFrogPond::metaObject(LeapFrogPond *this)

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



// ==== 0013c39c  LeapFrogPond::qt_metacast

/* LeapFrogPond::qt_metacast(char const*) */

LeapFrogPond * __thiscall LeapFrogPond::qt_metacast(LeapFrogPond *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (LeapFrogPond *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"LeapFrogPond");
    if (iVar1 != 0) {
      this = (LeapFrogPond *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013c3f0  LeapFrogPond::qt_metacall

/* LeapFrogPond::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
LeapFrogPond::qt_metacall(LeapFrogPond *this,int param_2,undefined4 param_3,undefined8 *param_4)

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
      local_28 = local_28 + -4;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0013c4e6  LeapFrogPond::notesChanged

/* LeapFrogPond::notesChanged() */

void __thiscall LeapFrogPond::notesChanged(LeapFrogPond *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0013c512  LeapFrogPond::noticeChanged

/* LeapFrogPond::noticeChanged() */

void __thiscall LeapFrogPond::noticeChanged(LeapFrogPond *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0013c53e  LeapFrogPond::archived

/* LeapFrogPond::archived(int) */

void __thiscall LeapFrogPond::archived(LeapFrogPond *this,int param_1)

{
  int local_14;
  LeapFrogPond *local_10;
  
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,2,(void *)0x0,&local_14);
  return;
}



// ==== 0013c574  LeapFrogPond::exported

/* LeapFrogPond::exported(QString const&) */

void __thiscall LeapFrogPond::exported(LeapFrogPond *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,3,(void *)0x0,param_1);
  return;
}



// ==== 0013c5ac  LeapFrogPond::reconciled

/* LeapFrogPond::reconciled(int) */

void __thiscall LeapFrogPond::reconciled(LeapFrogPond *this,int param_1)

{
  int local_14;
  LeapFrogPond *local_10;
  
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,4,(void *)0x0,&local_14);
  return;
}



// ==== 0015e7c6  LeapFrogPond::LeapFrogPond

/* LeapFrogPond::LeapFrogPond(QObject*, CalendarBackend*) */

void __thiscall
LeapFrogPond::LeapFrogPond(LeapFrogPond *this,QObject *param_1,CalendarBackend *param_2)

{
  long in_FS_OFFSET;
  Connection local_50 [8];
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c188;
  *(CalendarBackend **)(this + 0x10) = param_2;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x18));
  QString::QString((QString *)(this + 0x30));
  loadNotes(this);
  if (param_2 != (CalendarBackend *)0x0) {
    local_48 = notesChanged;
    local_40 = 0;
    QObject::connect<void(CalendarBackend::*)(),void(LeapFrogPond::*)()>
              (local_50,param_2,CalendarBackend::changed,0,this,&local_48,0);
    QMetaObject::Connection::~Connection(local_50);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015e91c  LeapFrogPond::notes

/* LeapFrogPond::notes() const */

QList<QVariant> * LeapFrogPond::notes(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x18));
  return in_RDI;
}



// ==== 0015e94a  LeapFrogPond::noteCount

/* LeapFrogPond::noteCount() const */

void __thiscall LeapFrogPond::noteCount(LeapFrogPond *this)

{
  QList<QVariant>::size((QList<QVariant> *)(this + 0x18));
  return;
}



// ==== 0015e968  LeapFrogPond::notice

/* LeapFrogPond::notice() const */

QString * LeapFrogPond::notice(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x30));
  return in_RDI;
}



// ==== 0015e996  LeapFrogPond::appts

/* LeapFrogPond::appts() const */

QList<QVariant> * LeapFrogPond::appts(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    CalendarBackend::appointments();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0015ea12  LeapFrogPond::addNote

/* LeapFrogPond::addNote(QString const&) */

void __thiscall LeapFrogPond::addNote(LeapFrogPond *this,QString *param_1)

{
  char cVar1;
  QVariant *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_98;
  QDateTime local_90 [8];
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::trimmed(local_68);
  cVar1 = QString::isEmpty(local_68);
  QString::~QString(local_68);
  if (cVar1 == '\0') {
    local_98 = 0;
    genId((LeapFrogPond *)local_68);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"id");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    ::QVariant::QVariant(local_48,param_1);
    QString::QString(local_68,"text");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
    QDateTime::currentDateTime();
    QDateTime::toString(local_68,local_90,1);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"created");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    QDateTime::~QDateTime(local_90);
    ::QVariant::QVariant(local_48,(QMap *)&local_98);
    QList<QVariant>::append((QList<QVariant> *)(this + 0x18),local_48);
    ::QVariant::~QVariant(local_48);
    saveNotes(this);
    notesChanged(this);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015ed82  LeapFrogPond::removeNote

/* LeapFrogPond::removeNote(QString const&) */

void __thiscall LeapFrogPond::removeNote(LeapFrogPond *this,QString *param_1)

{
  char cVar1;
  long lVar2;
  long in_FS_OFFSET;
  int local_b4;
  QVariant local_b0 [8];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b4 = 0;
  do {
    lVar2 = QList<QVariant>::size((QList<QVariant> *)(this + 0x18));
    if (lVar2 <= local_b4) {
LAB_0015eef2:
      saveNotes(this);
      notesChanged(this);
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    ::QVariant::QVariant(local_48,param_1);
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x18),(long)local_b4);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_88);
    QString::QString(local_a8,"id");
    QMap<QString,QVariant>::value(local_68,local_b0);
    cVar1 = ::operator==((QVariant *)local_68,local_48);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_88);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b0);
    ::QVariant::~QVariant(local_48);
    if (cVar1 != '\0') {
      QList<QVariant>::removeAt((QList<QVariant> *)(this + 0x18),(long)local_b4);
      goto LAB_0015eef2;
    }
    local_b4 = local_b4 + 1;
  } while( true );
}



// ==== 0015efa0  LeapFrogPond::removeAppt

/* LeapFrogPond::removeAppt(QString const&) */

void __thiscall LeapFrogPond::removeAppt(LeapFrogPond *this,QString *param_1)

{
  if (*(long *)(this + 0x10) != 0) {
    CalendarBackend::deleteAppointment(*(CalendarBackend **)(this + 0x10),param_1);
  }
  return;
}



// ==== 0015efd8  LeapFrogPond::setNotice

/* LeapFrogPond::setNotice(QString const&) */

void __thiscall LeapFrogPond::setNotice(LeapFrogPond *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator!=(param_1,(QString *)(this + 0x30));
  if (cVar1 != '\0') {
    QString::operator=((QString *)(this + 0x30),param_1);
    saveNotes(this);
    noticeChanged(this);
  }
  return;
}



// ==== 0015f05c  LeapFrogPond::tally

/* LeapFrogPond::tally() const */

QMap<QString,QVariant> * LeapFrogPond::tally(void)

{
  char cVar1;
  int iVar2;
  QVariant *pQVar3;
  LeapFrogPond *in_RSI;
  QMap<QString,QVariant> *in_RDI;
  long in_FS_OFFSET;
  int local_134;
  undefined8 local_130;
  undefined8 local_128;
  QVariant local_120 [8];
  QList<QVariant> *local_118;
  undefined8 local_110;
  QList<QVariant> local_108 [32];
  QString local_e8 [32];
  QList<QVariant> local_c8 [32];
  QString local_a8 [32];
  undefined8 local_88 [4];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined8 *)in_RDI = 0;
  iVar2 = noteCount(in_RSI);
  ::QVariant::QVariant(local_48,iVar2);
  QString::QString((QString *)local_88,"notes");
  pQVar3 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,(QString *)local_88);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  appts();
  iVar2 = QList<QVariant>::size(local_108);
  ::QVariant::QVariant(local_48,iVar2);
  QString::QString((QString *)local_88,"appts");
  pQVar3 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,(QString *)local_88);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  local_134 = 0;
  local_88[0] = QDate::currentDate();
  QDate::toString(local_e8,local_88,1);
  if (*(long *)(in_RSI + 0x10) != 0) {
    CalendarBackend::appointments();
    local_118 = local_c8;
    local_130 = QList<QVariant>::begin(local_118);
    local_128 = QList<QVariant>::end(local_118);
    while( true ) {
      cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_130,local_128);
      if (cVar1 == '\0') break;
      local_110 = QList<QVariant>::iterator::operator*((iterator *)&local_130);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_68);
      QString::QString(local_a8,"date");
      QMap<QString,QVariant>::value((QString *)local_48,local_120);
      ::QVariant::toString();
      cVar1 = ::operator==((QString *)local_88,local_e8);
      QString::~QString((QString *)local_88);
      ::QVariant::~QVariant(local_48);
      QString::~QString(local_a8);
      ::QVariant::~QVariant(local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_120);
      if (cVar1 != '\0') {
        local_134 = local_134 + 1;
      }
      QList<QVariant>::iterator::operator++((iterator *)&local_130);
    }
    QList<QVariant>::~QList(local_c8);
  }
  ::QVariant::QVariant(local_48,local_134);
  QString::QString((QString *)local_88,"today");
  pQVar3 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,(QString *)local_88);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_e8);
  QList<QVariant>::~QList(local_108);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0015f524  LeapFrogPond::reconcile

/* LeapFrogPond::reconcile() */

int __thiscall LeapFrogPond::reconcile(LeapFrogPond *this)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  int local_c8;
  int local_c4;
  QDateTime local_c0 [8];
  QDateTime local_b8 [8];
  QVariant local_b0 [8];
  QString local_a8 [32];
  QDateTime local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_c8 = 0;
  QDateTime::currentDateTime();
  QDateTime::addDays((longlong)local_c0);
  QDateTime::~QDateTime(local_88);
  local_c4 = QList<QVariant>::size((QList<QVariant> *)(this + 0x18));
  do {
    local_c4 = local_c4 + -1;
    if (local_c4 < 0) {
      if (local_c8 != 0) {
        saveNotes(this);
        notesChanged(this);
      }
      reconciled(this,local_c8);
      QDateTime::~QDateTime(local_c0);
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return local_c8;
    }
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x18),(long)local_c4);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"created");
    QMap<QString,QVariant>::value(local_48,local_b0);
    ::QVariant::toString();
    QDateTime::fromString(local_b8,local_88,1);
    QString::~QString((QString *)local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b0);
    cVar2 = QDateTime::isValid();
    if (cVar2 == '\0') {
LAB_0015f6c3:
      bVar1 = false;
    }
    else {
      cVar2 = ::operator<(local_b8,local_c0);
      if (cVar2 == '\0') goto LAB_0015f6c3;
      bVar1 = true;
    }
    if (bVar1) {
      QList<QVariant>::removeAt((QList<QVariant> *)(this + 0x18),(long)local_c4);
      local_c8 = local_c8 + 1;
    }
    QDateTime::~QDateTime(local_b8);
  } while( true );
}



// ==== 0015f856  LeapFrogPond::archivePast

/* LeapFrogPond::archivePast() */

int __thiscall LeapFrogPond::archivePast(LeapFrogPond *this)

{
  CalendarBackend *this_00;
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  long in_FS_OFFSET;
  int local_1b4;
  undefined8 local_1b0;
  undefined8 local_1a8;
  QVariant local_1a0 [8];
  QList<QVariant> *local_198;
  undefined8 local_190;
  QString local_188 [32];
  QList<QVariant> local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QString local_108 [32];
  undefined8 local_e8 [4];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_1b4 = 0;
  if (*(long *)(this + 0x10) != 0) {
    local_e8[0] = QDate::currentDate();
    QDate::toString(local_188,local_e8,1);
    CalendarBackend::appointments();
    local_198 = local_168;
    local_1b0 = QList<QVariant>::begin(local_198);
    local_1a8 = QList<QVariant>::end(local_198);
    while (cVar6 = QList<QVariant>::iterator::operator!=((iterator *)&local_1b0,local_1a8),
          cVar6 != '\0') {
      local_190 = QList<QVariant>::iterator::operator*((iterator *)&local_1b0);
      ::QVariant::toMap();
      bVar2 = false;
      bVar1 = false;
      bVar5 = false;
      bVar4 = false;
      ::QVariant::QVariant(local_c8);
      QString::QString(local_148,"date");
      QMap<QString,QVariant>::value(local_a8,local_1a0);
      ::QVariant::toString();
      cVar6 = ::operator<(local_128,local_188);
      if (cVar6 == '\0') {
LAB_0015faab:
        bVar3 = false;
      }
      else {
        ::QVariant::QVariant(local_88);
        bVar2 = true;
        QString::QString(local_108,"recurrence");
        bVar1 = true;
        QMap<QString,QVariant>::value(local_68,local_1a0);
        bVar5 = true;
        ::QVariant::toString();
        bVar4 = true;
        cVar6 = QString::isEmpty((QString *)local_e8);
        if (cVar6 == '\0') goto LAB_0015faab;
        bVar3 = true;
      }
      if (bVar4) {
        QString::~QString((QString *)local_e8);
      }
      if (bVar5) {
        ::QVariant::~QVariant((QVariant *)local_68);
      }
      if (bVar1) {
        QString::~QString(local_108);
      }
      if (bVar2) {
        ::QVariant::~QVariant(local_88);
      }
      QString::~QString(local_128);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString(local_148);
      ::QVariant::~QVariant(local_c8);
      if (bVar3) {
        this_00 = *(CalendarBackend **)(this + 0x10);
        ::QVariant::QVariant(local_88);
        QString::QString(local_108,"id");
        QMap<QString,QVariant>::value(local_68,local_1a0);
        ::QVariant::toString();
        CalendarBackend::deleteAppointment(this_00,(QString *)local_e8);
        QString::~QString((QString *)local_e8);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString(local_108);
        ::QVariant::~QVariant(local_88);
        local_1b4 = local_1b4 + 1;
      }
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1a0);
      QList<QVariant>::iterator::operator++((iterator *)&local_1b0);
    }
    QList<QVariant>::~QList(local_168);
    QString::~QString(local_188);
  }
  archived(this,local_1b4);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_1b4;
}



// ==== 0015fe36  LeapFrogPond::exportCsv

/* LeapFrogPond::exportCsv(QString const&) */

QString * LeapFrogPond::exportCsv(QString *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  QString *in_RDX;
  LeapFrogPond *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_2c8;
  undefined8 local_2c0;
  QVariant local_2b8 [8];
  QList<QVariant> *local_2b0;
  undefined8 local_2a8;
  undefined *local_2a0;
  QFile local_298 [16];
  QString local_288 [32];
  QList<QVariant> local_268 [32];
  QString local_248 [32];
  QString local_228 [32];
  undefined2 local_208 [16];
  undefined2 local_1e8 [16];
  QString local_1c8 [32];
  QArrayDataPointer<char16_t> local_1a8 [32];
  QString local_188 [32];
  QString local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QVariant local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty(in_RDX);
  if (cVar1 == '\0') {
    QString::QString(local_288,in_RDX);
  }
  else {
    QDir::homePath();
    ::operator+(local_288,(char *)local_128);
    QString::~QString(local_128);
  }
  QFile::QFile(local_298,local_288);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_298,uVar2);
  if (cVar1 == '\x01') {
    QIODevice::write((char *)local_298);
    appts();
    local_2b0 = local_268;
    local_2c8 = QList<QVariant>::begin(local_2b0);
    local_2c0 = QList<QVariant>::end(local_2b0);
    while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_2c8,local_2c0),
          cVar1 != '\0') {
      local_2a8 = QList<QVariant>::iterator::operator*((iterator *)&local_2c8);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_108);
      QString::QString(local_1c8,"allDay");
      QMap<QString,QVariant>::value(local_e8,local_2b8);
      cVar1 = ::QVariant::toBool();
      if (cVar1 == '\0') {
        QString::QString(local_188,"%1:%2");
        QChar::QChar<char16_t,true>((QChar *)local_208,L' ');
        ::QVariant::QVariant(local_c8);
        QString::QString(local_168,"start");
        QMap<QString,QVariant>::value(local_a8,local_2b8);
        iVar3 = ::QVariant::toInt((bool *)local_a8);
        QString::arg<int,true>(local_148,local_188,iVar3 / 0x3c,0,10,local_208[0]);
        QChar::QChar<char,true>((QChar *)local_1e8,'0');
        ::QVariant::QVariant(local_88);
        QString::QString(local_128,"start");
        QMap<QString,QVariant>::value(local_68,local_2b8);
        iVar3 = ::QVariant::toInt((bool *)local_68);
        QString::arg<int,true>(local_248,local_148,iVar3 % 0x3c,2,10,local_1e8[0]);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString(local_128);
        ::QVariant::~QVariant(local_88);
        QString::~QString(local_148);
        ::QVariant::~QVariant((QVariant *)local_a8);
        QString::~QString(local_168);
        ::QVariant::~QVariant(local_c8);
        QString::~QString(local_188);
      }
      else {
        local_2a0 = &DAT_00293c90;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  (local_1a8,(QTypedArrayData *)0x0,L"all day",7);
        QString::QString(local_248,(QArrayDataPointer *)local_1a8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1a8);
      }
      ::QVariant::~QVariant((QVariant *)local_e8);
      QString::~QString(local_1c8);
      ::QVariant::~QVariant(local_108);
      QString::QString(local_228,"%1,%2,\"%3\",\"%4\"\n");
      ::QVariant::QVariant(local_88);
      QString::QString(local_188,"notes");
      QMap<QString,QVariant>::value(local_68,local_2b8);
      ::QVariant::toString();
      ::QVariant::QVariant(local_c8);
      QString::QString(local_1c8,"title");
      QMap<QString,QVariant>::value(local_a8,local_2b8);
      ::QVariant::toString();
      ::QVariant::QVariant(local_108);
      QString::QString((QString *)local_208,"date");
      QMap<QString,QVariant>::value(local_e8,local_2b8);
      ::QVariant::toString();
      QString::arg<QString,QString_const&,QString,QString>
                (local_148,local_228,(QString *)local_1e8,local_248);
      QString::toUtf8(local_128);
      QIODevice::write((QByteArray *)local_298);
      QByteArray::~QByteArray((QByteArray *)local_128);
      QString::~QString(local_148);
      QString::~QString((QString *)local_1e8);
      ::QVariant::~QVariant((QVariant *)local_e8);
      QString::~QString((QString *)local_208);
      ::QVariant::~QVariant(local_108);
      QString::~QString((QString *)local_1a8);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString(local_1c8);
      ::QVariant::~QVariant(local_c8);
      QString::~QString(local_168);
      ::QVariant::~QVariant((QVariant *)local_68);
      QString::~QString(local_188);
      ::QVariant::~QVariant(local_88);
      QString::~QString(local_228);
      QString::~QString(local_248);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_2b8);
      QList<QVariant>::iterator::operator++((iterator *)&local_2c8);
    }
    QList<QVariant>::~QList(local_268);
    QFileDevice::close();
    exported(in_RSI,local_288);
    QString::QString(param_1,local_288);
  }
  else {
    QString::QString(param_1);
  }
  QFile::~QFile(local_298);
  QString::~QString(local_288);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001609ae  LeapFrogPond::exportLilyPad

/* LeapFrogPond::exportLilyPad(QString const&) */

QString * LeapFrogPond::exportLilyPad(QString *param_1)

{
  char cVar1;
  undefined4 uVar2;
  QVariant *pQVar3;
  QString *in_RDX;
  LeapFrogPond *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_c0;
  QMap local_b8 [8];
  QJsonDocument local_b0 [8];
  QString local_a8 [32];
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty(in_RDX);
  if (cVar1 == '\0') {
    QString::QString(local_a8,in_RDX);
  }
  else {
    QDir::homePath();
    ::operator+(local_a8,(char *)local_68);
    QString::~QString(local_68);
  }
  local_c0 = 0;
  ::QVariant::QVariant(local_48,(QList *)(in_RSI + 0x18));
  QString::QString(local_68,"notes");
  pQVar3 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(in_RSI + 0x30));
  QString::QString(local_68,"notice");
  pQVar3 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  appts();
  ::QVariant::QVariant(local_48,(QList *)local_68);
  QString::QString(local_88,"appts");
  pQVar3 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QList<QVariant>::~QList((QList<QVariant> *)local_68);
  QFile::QFile((QFile *)local_88,local_a8);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_88,uVar2);
  if (cVar1 == '\x01') {
    QJsonObject::fromVariantMap(local_b8);
    QJsonDocument::QJsonDocument(local_b0,(QJsonObject *)local_b8);
    QJsonDocument::toJson(local_68,local_b0,0);
    QIODevice::write((QByteArray *)local_88);
    QByteArray::~QByteArray((QByteArray *)local_68);
    QJsonDocument::~QJsonDocument(local_b0);
    QJsonObject::~QJsonObject((QJsonObject *)local_b8);
    QFileDevice::close();
    exported(in_RSI,local_a8);
    QString::QString(param_1,local_a8);
  }
  else {
    QString::QString(param_1);
  }
  QFile::~QFile((QFile *)local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
  QString::~QString(local_a8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00160e6a  LeapFrogPond::genId

/* LeapFrogPond::genId() const */

LeapFrogPond * __thiscall LeapFrogPond::genId(LeapFrogPond *this)

{
  long in_FS_OFFSET;
  QString local_58 [32];
  undefined1 local_38 [16];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = QUuid::createUuid();
  QUuid::toString(local_58,local_38,1);
  QString::left((longlong)this);
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00160f24  LeapFrogPond::path

/* LeapFrogPond::path() const */

LeapFrogPond * __thiscall LeapFrogPond::path(LeapFrogPond *this)

{
  long in_FS_OFFSET;
  QDir local_68 [8];
  undefined8 local_60;
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDir::homePath();
  ::operator+(local_58,(char *)local_38);
  QString::~QString(local_38);
  QString::QString(local_38);
  QDir::QDir(local_68,local_38);
  std::optional<QFlags<QFileDevice::Permission>>::optional(&local_60);
  QDir::mkpath(local_68,local_58,local_60);
  QDir::~QDir(local_68);
  QString::~QString(local_38);
  ::operator+((QString *)this,(char *)local_58);
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0016109a  LeapFrogPond::loadNotes

/* LeapFrogPond::loadNotes() */

void __thiscall LeapFrogPond::loadNotes(LeapFrogPond *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QVariant local_c8 [8];
  QByteArray local_c0 [8];
  QFile local_b8 [16];
  QJsonObject local_a8 [32];
  undefined4 local_88 [8];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  path((LeapFrogPond *)local_88);
  QFile::QFile(local_b8,(QString *)local_88);
  QString::~QString((QString *)local_88);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_88,1);
  cVar1 = QFile::open(local_b8,local_88[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson(local_c0,(QJsonParseError *)local_88);
    QJsonDocument::object();
    QJsonObject::toVariantMap();
    QJsonObject::~QJsonObject(local_a8);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_c0);
    QByteArray::~QByteArray((QByteArray *)local_88);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_a8,"notes");
    QMap<QString,QVariant>::value(local_48,local_c8);
    ::QVariant::toList();
    QList<QVariant>::operator=((QList<QVariant> *)(this + 0x18),(QList *)local_88);
    QList<QVariant>::~QList((QList<QVariant> *)local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_a8,"notice");
    QMap<QString,QVariant>::value(local_48,local_c8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x30),(QString *)local_88);
    QString::~QString((QString *)local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
  }
  QFile::~QFile(local_b8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0016145a  LeapFrogPond::saveNotes

/* LeapFrogPond::saveNotes() const */

void __thiscall LeapFrogPond::saveNotes(LeapFrogPond *this)

{
  char cVar1;
  undefined4 uVar2;
  QVariant *pQVar3;
  long in_FS_OFFSET;
  undefined8 local_90;
  QMap local_88 [8];
  QJsonDocument local_80 [8];
  QFile local_78 [16];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_90 = 0;
  ::QVariant::QVariant(local_48,(QList *)(this + 0x18));
  QString::QString(local_68,"notes");
  pQVar3 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x30));
  QString::QString(local_68,"notice");
  pQVar3 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
  ::QVariant::operator=(pQVar3,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  path((LeapFrogPond *)local_68);
  QFile::QFile(local_78,local_68);
  QString::~QString(local_68);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_78,uVar2);
  if (cVar1 != '\0') {
    QJsonObject::fromVariantMap(local_88);
    QJsonDocument::QJsonDocument(local_80,(QJsonObject *)local_88);
    QJsonDocument::toJson(local_68,local_80,0);
    QIODevice::write((QByteArray *)local_78);
    QByteArray::~QByteArray((QByteArray *)local_68);
    QJsonDocument::~QJsonDocument(local_80);
    QJsonObject::~QJsonObject((QJsonObject *)local_88);
  }
  QFile::~QFile(local_78);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_90);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016181e  LeapFrogPond::~LeapFrogPond

/* LeapFrogPond::~LeapFrogPond() */

void __thiscall LeapFrogPond::~LeapFrogPond(LeapFrogPond *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c188;
  QString::~QString((QString *)(this + 0x30));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x18));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 00161868  LeapFrogPond::~LeapFrogPond

/* LeapFrogPond::~LeapFrogPond() */

void __thiscall LeapFrogPond::~LeapFrogPond(LeapFrogPond *this)

{
  ~LeapFrogPond(this);
  operator_delete(this,0x48);
  return;
}


