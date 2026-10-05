// Ghidra decompile of LaPivot.oracle — class/namespace CalendarBackend (38 functions). Raw; not source.

// ==== 0014fec2  CalendarBackend::qt_static_metacall

/* CalendarBackend::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void CalendarBackend::qt_static_metacall
               (CalendarBackend *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  undefined1 uVar1;
  bool bVar2;
  long in_FS_OFFSET;
  undefined4 local_48 [6];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0x10) {
      uVar1 = composeForHummingbirdRec(param_1,*(QMap **)(param_4 + 8));
      local_48[0] = CONCAT31(local_48[0]._1_3_,uVar1);
      if (*(long *)param_4 != 0) {
        **(undefined1 **)param_4 = uVar1;
      }
    }
    else if (param_3 < 0x11) {
      if (param_3 == 0xf) {
        uVar1 = composeForHummingbird(param_1,*(QString **)(param_4 + 8));
        local_48[0] = CONCAT31(local_48[0]._1_3_,uVar1);
        if (*(long *)param_4 != 0) {
          **(undefined1 **)param_4 = uVar1;
        }
      }
      else if (param_3 < 0x10) {
        if (param_3 == 0xe) {
          fireReminder(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10));
        }
        else if (param_3 < 0xf) {
          if (param_3 == 0xd) {
            local_48[0] = importICSFromFile(param_1,*(QString **)(param_4 + 8));
            if (*(long *)param_4 != 0) {
              **(undefined4 **)param_4 = local_48[0];
            }
          }
          else if (param_3 < 0xe) {
            if (param_3 == 0xc) {
              local_48[0] = importICS(param_1,*(QString **)(param_4 + 8));
              if (*(long *)param_4 != 0) {
                **(undefined4 **)param_4 = local_48[0];
              }
            }
            else if (param_3 < 0xd) {
              if (param_3 == 0xb) {
                uVar1 = exportICSToFile(param_1,*(QString **)(param_4 + 8));
                local_48[0] = CONCAT31(local_48[0]._1_3_,uVar1);
                if (*(long *)param_4 != 0) {
                  **(undefined1 **)param_4 = uVar1;
                }
              }
              else if (param_3 < 0xc) {
                if (param_3 == 10) {
                  exportICS();
                  if (*(long *)param_4 != 0) {
                    QString::operator=(*(QString **)param_4,(QString *)local_48);
                  }
                  QString::~QString((QString *)local_48);
                }
                else if (param_3 < 0xb) {
                  if (param_3 == 9) {
                    uVar1 = canUndo(param_1);
                    local_48[0] = CONCAT31(local_48[0]._1_3_,uVar1);
                    if (*(long *)param_4 != 0) {
                      **(undefined1 **)param_4 = uVar1;
                    }
                  }
                  else if (param_3 < 10) {
                    if (param_3 == 8) {
                      undo();
                      if (*(long *)param_4 != 0) {
                        QString::operator=(*(QString **)param_4,(QString *)local_48);
                      }
                      QString::~QString((QString *)local_48);
                    }
                    else if (param_3 < 9) {
                      if (param_3 == 7) {
                        saveSettings((QMap *)param_1);
                      }
                      else if (param_3 < 8) {
                        if (param_3 == 6) {
                          deleteTodo(param_1,*(QString **)(param_4 + 8));
                        }
                        else if (param_3 < 7) {
                          if (param_3 == 5) {
                            toggleTodo(param_1,*(QString **)(param_4 + 8));
                          }
                          else if (param_3 < 6) {
                            if (param_3 == 4) {
                              upsertTodo((QMap *)local_48);
                              if (*(long *)param_4 != 0) {
                                QString::operator=(*(QString **)param_4,(QString *)local_48);
                              }
                              QString::~QString((QString *)local_48);
                            }
                            else if (param_3 < 5) {
                              if (param_3 == 3) {
                                deleteAppointment(param_1,*(QString **)(param_4 + 8));
                              }
                              else if (param_3 < 4) {
                                if (param_3 == 2) {
                                  upsertAppointment((QMap *)local_48);
                                  if (*(long *)param_4 != 0) {
                                    QString::operator=(*(QString **)param_4,(QString *)local_48);
                                  }
                                  QString::~QString((QString *)local_48);
                                }
                                else if (param_3 < 3) {
                                  if (param_3 == 0) {
                                    changed(param_1);
                                  }
                                  else if (param_3 == 1) {
                                    settingsChanged(param_1);
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
  }
  if (((param_2 != 5) ||
      ((bVar2 = QtMocHelpers::indexOfMethod<void(CalendarBackend::*)()>
                          (param_4,(void **)changed,(_func_void *)0x0,0), !bVar2 &&
       (bVar2 = QtMocHelpers::indexOfMethod<void(CalendarBackend::*)()>
                          (param_4,(void **)settingsChanged,(_func_void *)0x0,1), !bVar2)))) &&
     (param_2 == 1)) {
    this = *(QList<QVariant> **)param_4;
    if (param_3 == 2) {
      settings();
      QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)this,(QMap *)local_48);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_48);
    }
    else if (param_3 < 3) {
      if (param_3 == 0) {
        appointments();
        QList<QVariant>::operator=(this,(QList *)local_48);
        QList<QVariant>::~QList((QList<QVariant> *)local_48);
      }
      else if (param_3 == 1) {
        todos();
        QList<QVariant>::operator=(this,(QList *)local_48);
        QList<QVariant>::~QList((QList<QVariant> *)local_48);
      }
    }
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0015050c  CalendarBackend::metaObject

/* CalendarBackend::metaObject() const */

undefined1 * __thiscall CalendarBackend::metaObject(CalendarBackend *this)

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



// ==== 00150554  CalendarBackend::qt_metacast

/* CalendarBackend::qt_metacast(char const*) */

CalendarBackend * __thiscall CalendarBackend::qt_metacast(CalendarBackend *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (CalendarBackend *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"CalendarBackend");
    if (iVar1 != 0) {
      this = (CalendarBackend *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 001505a8  CalendarBackend::qt_metacall

/* CalendarBackend::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
CalendarBackend::qt_metacall
          (CalendarBackend *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x11) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x11;
    }
    if (param_2 == 7) {
      if (local_28 < 0x11) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x11;
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



// ==== 0015069e  CalendarBackend::changed

/* CalendarBackend::changed() */

void __thiscall CalendarBackend::changed(CalendarBackend *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 001506ca  CalendarBackend::settingsChanged

/* CalendarBackend::settingsChanged() */

void __thiscall CalendarBackend::settingsChanged(CalendarBackend *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0015e6f4  CalendarBackend::appointments

/* CalendarBackend::appointments() const */

QList<QVariant> * CalendarBackend::appointments(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x28));
  return in_RDI;
}



// ==== 0015e722  CalendarBackend::todos

/* CalendarBackend::todos() const */

QList<QVariant> * CalendarBackend::todos(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x40));
  return in_RDI;
}



// ==== 0015e776  CalendarBackend::settings

/* CalendarBackend::settings() const */

QMap<QString,QVariant> * CalendarBackend::settings(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x58));
  return in_RDI;
}



// ==== 0015e7a4  CalendarBackend::canUndo

/* CalendarBackend::canUndo() const */

uint __thiscall CalendarBackend::canUndo(CalendarBackend *this)

{
  uint uVar1;
  
  uVar1 = QList<CalendarBackend::Snapshot>::isEmpty
                    ((QList<CalendarBackend::Snapshot> *)(this + 0x10));
  return uVar1 ^ 1;
}



// ==== 001a3d0a  CalendarBackend::~CalendarBackend

/* CalendarBackend::~CalendarBackend() */

void __thiscall CalendarBackend::~CalendarBackend(CalendarBackend *this)

{
  *(undefined ***)this = &PTR_metaObject_0032b9a0;
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x58));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x40));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x28));
  QList<CalendarBackend::Snapshot>::~QList((QList<CalendarBackend::Snapshot> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a3d74  CalendarBackend::~CalendarBackend

/* CalendarBackend::~CalendarBackend() */

void __thiscall CalendarBackend::~CalendarBackend(CalendarBackend *this)

{
  ~CalendarBackend(this);
  operator_delete(this,0x60);
  return;
}



// ==== 001d5bb6  CalendarBackend::Snapshot::~Snapshot

/* CalendarBackend::Snapshot::~Snapshot() */

void __thiscall CalendarBackend::Snapshot::~Snapshot(Snapshot *this)

{
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x30));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x18));
  QString::~QString((QString *)this);
  return;
}



// ==== 00264854  CalendarBackend::CalendarBackend

/* CalendarBackend::CalendarBackend(QObject*) */

void __thiscall CalendarBackend::CalendarBackend(CalendarBackend *this,QObject *param_1)

{
  pair<QString,QVariant> *this_00;
  long in_FS_OFFSET;
  bool local_2bc;
  bool local_2bb [3];
  int aiStack_2b8 [2];
  QMap aQStack_2b0 [8];
  pair<QString,QVariant> local_2a8 [56];
  pair<QString,QVariant> local_270 [56];
  undefined1 auStack_238 [56];
  pair<QString,QVariant> apStack_200 [56];
  pair<QString,QVariant> apStack_1c8 [56];
  pair<QString,QVariant> apStack_190 [56];
  pair<QString,QVariant> apStack_158 [56];
  pair<QString,QVariant> apStack_120 [56];
  pair<QString,QVariant> apStack_e8 [56];
  pair<QString,QVariant> apStack_b0 [56];
  pair<QString,QVariant> apStack_78 [56];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032b9a0;
  QList<CalendarBackend::Snapshot>::QList((QList<CalendarBackend::Snapshot> *)(this + 0x10));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x28));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x40));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x58));
  local_2bc = true;
  std::pair<QString,QVariant>::pair<char_const(&)[8],bool,true>(local_2a8,"enabled",&local_2bc);
  local_2bb[0] = true;
  std::pair<QString,QVariant>::pair<char_const(&)[14],bool,true>
            (local_270,"methodDesktop",local_2bb);
  local_2bb[1] = false;
  _ZNSt4pairI7QString8QVariantEC2IRA12_KcbLb1EEEOT_OT0_(auStack_238,"methodEmail",local_2bb + 1);
  local_2bb[2] = false;
  std::pair<QString,QVariant>::pair<char_const(&)[11],bool,true>
            (apStack_200,"methodNtfy",local_2bb + 2);
  std::pair<QString,QVariant>::pair<char_const(&)[6],char_const(&)[1],true>(apStack_1c8,"email","");
  std::pair<QString,QVariant>::pair<char_const(&)[10],char_const(&)[1],true>
            (apStack_190,"ntfyTopic","");
  aiStack_2b8[0] = 0xf;
  std::pair<QString,QVariant>::pair<char_const(&)[12],int,true>
            (apStack_158,"defaultLead",aiStack_2b8);
  std::pair<QString,QVariant>::pair<char_const(&)[9],char_const(&)[1],true>
            (apStack_120,"smtpFrom","");
  std::pair<QString,QVariant>::pair<char_const(&)[9],char_const(&)[15],true>
            (apStack_e8,"smtpHost","smtp.gmail.com");
  aiStack_2b8[1] = 0x24b;
  std::pair<QString,QVariant>::pair<char_const(&)[9],int,true>
            (apStack_b0,"smtpPort",aiStack_2b8 + 1);
  std::pair<QString,QVariant>::pair<char_const(&)[9],char_const(&)[1],true>
            (apStack_78,"smtpUser","");
  QMap<QString,QVariant>::QMap(aQStack_2b0,local_2a8,0xb);
  QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(this + 0x58),aQStack_2b0);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)aQStack_2b0);
  this_00 = (pair<QString,QVariant> *)local_40;
  while (this_00 != local_2a8) {
    this_00 = this_00 + -0x38;
    std::pair<QString,QVariant>::~pair(this_00);
  }
  load(this);
  if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00264c50  CalendarBackend::configPath

/* CalendarBackend::configPath() const */

CalendarBackend * __thiscall CalendarBackend::configPath(CalendarBackend *this)

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



// ==== 00264dc6  CalendarBackend::load

/* CalendarBackend::load() */

void __thiscall CalendarBackend::load(CalendarBackend *this)

{
  char cVar1;
  QVariant *pQVar2;
  QString *pQVar3;
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_98 [8];
  QJsonArray local_90 [8];
  QFile local_88 [16];
  QString local_78 [32];
  undefined8 local_58 [4];
  ulong local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  configPath((CalendarBackend *)local_38);
  QFile::QFile(local_88,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_88,local_38[0] & 0xffffffff);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_58,(QJsonParseError *)local_38);
    QJsonDocument::object();
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_58);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QFileDevice::close();
    QString::QString(local_78,"appointments");
    QJsonObject::value((QString *)local_58);
    QJsonValue::toArray();
    QJsonArray::toVariantList();
    QList<QVariant>::operator=((QList<QVariant> *)(this + 0x28),(QList *)local_38);
    QList<QVariant>::~QList((QList<QVariant> *)local_38);
    QJsonArray::~QJsonArray(local_90);
    QJsonValue::~QJsonValue((QJsonValue *)local_58);
    QString::~QString(local_78);
    QString::QString(local_78,"todos");
    QJsonObject::value((QString *)local_58);
    QJsonValue::toArray();
    QJsonArray::toVariantList();
    QList<QVariant>::operator=((QList<QVariant> *)(this + 0x40),(QList *)local_38);
    QList<QVariant>::~QList((QList<QVariant> *)local_38);
    QJsonArray::~QJsonArray(local_90);
    QJsonValue::~QJsonValue((QJsonValue *)local_58);
    QString::~QString(local_78);
    QString::QString((QString *)local_38,"settings");
    cVar1 = QJsonObject::contains(local_98);
    QString::~QString((QString *)local_38);
    if (cVar1 != '\0') {
      QString::QString((QString *)local_58,"settings");
      QJsonObject::value((QString *)local_38);
      QJsonValue::toObject();
      QJsonObject::toVariantMap();
      QJsonObject::~QJsonObject((QJsonObject *)local_78);
      QJsonValue::~QJsonValue((QJsonValue *)local_38);
      QString::~QString((QString *)local_58);
      local_58[0] = QMap<QString,QVariant>::begin((QMap<QString,QVariant> *)local_90);
      while( true ) {
        local_38[0] = QMap<QString,QVariant>::end((QMap<QString,QVariant> *)local_90);
        cVar1 = ::operator!=((const_iterator *)local_58,(const_iterator *)local_38);
        if (cVar1 == '\0') break;
        pQVar2 = (QVariant *)
                 QMap<QString,QVariant>::const_iterator::value((const_iterator *)local_58);
        pQVar3 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_58);
        this_00 = (QVariant *)
                  QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x58),pQVar3)
        ;
        ::QVariant::operator=(this_00,pQVar2);
        QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_58);
      }
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_90);
    }
    changed(this);
    settingsChanged(this);
    QJsonObject::~QJsonObject((QJsonObject *)local_98);
  }
  else {
    save();
  }
  QFile::~QFile(local_88);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00265334  CalendarBackend::save

/* CalendarBackend::save() */

void CalendarBackend::save(void)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  undefined1 auVar3 [16];
  QJsonObject local_78 [8];
  QList local_70 [8];
  QJsonValueRef local_68 [16];
  QString local_58 [32];
  QJsonValue local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QJsonObject::QJsonObject(local_78);
  QJsonArray::fromVariantList(local_70);
  QJsonValue::QJsonValue(local_38,(QJsonArray *)local_70);
  QString::QString(local_58,"appointments");
  local_68 = (QJsonValueRef  [16])QJsonObject::operator[]((QString *)local_78);
  QJsonValueRef::operator=(local_68,local_38);
  QString::~QString(local_58);
  QJsonValue::~QJsonValue(local_38);
  QJsonArray::~QJsonArray((QJsonArray *)local_70);
  QJsonArray::fromVariantList(local_70);
  QJsonValue::QJsonValue(local_38,(QJsonArray *)local_70);
  QString::QString(local_58,"todos");
  auVar3 = QJsonObject::operator[]((QString *)local_78);
  local_68 = (QJsonValueRef  [16])auVar3;
  QJsonValueRef::operator=(local_68,local_38);
  QString::~QString(local_58);
  QJsonValue::~QJsonValue(local_38);
  QJsonArray::~QJsonArray((QJsonArray *)local_70);
  QJsonObject::fromVariantMap((QMap *)local_70);
  QJsonValue::QJsonValue(local_38,(QJsonObject *)local_70);
  QString::QString(local_58,"settings");
  auVar3 = QJsonObject::operator[]((QString *)local_78);
  local_68 = (QJsonValueRef  [16])auVar3;
  QJsonValueRef::operator=(local_68,local_38);
  QString::~QString(local_58);
  QJsonValue::~QJsonValue(local_38);
  QJsonObject::~QJsonObject((QJsonObject *)local_70);
  configPath((CalendarBackend *)local_38);
  QFile::QFile((QFile *)local_58,(QString *)local_38);
  QString::~QString((QString *)local_38);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_58,uVar2);
  if (cVar1 != '\0') {
    QJsonDocument::QJsonDocument((QJsonDocument *)local_68,local_78);
    QJsonDocument::toJson(local_38,local_68,0);
    QIODevice::write((QByteArray *)local_58);
    QByteArray::~QByteArray((QByteArray *)local_38);
                    /* try { // try from 002655b8 to 00365656 has its CatchHandler @ 0026565c */
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_68);
    QFileDevice::close();
  }
  QFile::~QFile((QFile *)local_58);
  QJsonObject::~QJsonObject(local_78);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00265704  CalendarBackend::upsertAppointment

/* CalendarBackend::upsertAppointment(QMap<QString, QVariant> const&) */

QMap * CalendarBackend::upsertAppointment(QMap *param_1)

{
  bool bVar1;
  char cVar2;
  QVariant *pQVar3;
  long lVar4;
  QMap *in_RDX;
  long lVar5;
  CalendarBackend *in_RSI;
  long in_FS_OFFSET;
  undefined2 local_218;
  undefined2 local_216;
  int local_214;
  QMap<QString,QVariant> local_210 [8];
  QList<QVariant> *local_208;
  undefined8 local_200;
  undefined *local_1f8;
  undefined *local_1f0;
  QArrayDataPointer<char16_t> local_1e8 [32];
  QString local_1c8 [32];
  QString local_1a8 [32];
  QString local_188 [32];
  undefined8 local_168 [4];
  undefined8 local_148 [4];
  QVariant local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QMap<QString,QVariant>::QMap(local_210,in_RDX);
  ::QVariant::QVariant(local_88);
  QString::QString(local_e8,"id");
  QMap<QString,QVariant>::value(local_68,(QVariant *)local_210);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_68);
  QString::~QString(local_e8);
  ::QVariant::~QVariant(local_88);
  bVar1 = false;
                    /* catch() { ... } // from try @ 00264c0e with catch @ 002657d9 */
  cVar2 = QString::isEmpty((QString *)param_1);
  if (cVar2 != '\x01') {
    local_208 = (QList<QVariant> *)(in_RSI + 0x28);
                    /* try { // try from 00265805 to 00365809 has its CatchHandler @ 00264ba4 */
    local_168[0] = QList<QVariant>::begin(local_208);
    local_148[0] = QList<QVariant>::end(local_208);
    while (cVar2 = QList<QVariant>::iterator::operator!=((iterator *)local_168,local_148[0]),
          cVar2 != '\0') {
      local_200 = QList<QVariant>::iterator::operator*((iterator *)local_168);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_88);
      QString::QString(local_108,"id");
      QMap<QString,QVariant>::value(local_68,local_128);
      ::QVariant::toString();
      cVar2 = ::operator==(local_e8,(QString *)param_1);
      QString::~QString(local_e8);
      ::QVariant::~QVariant((QVariant *)local_68);
      QString::~QString(local_108);
      ::QVariant::~QVariant(local_88);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_128);
      if (cVar2 != '\0') {
        bVar1 = true;
        break;
      }
      QList<QVariant>::iterator::operator++((iterator *)local_168);
    }
  }
  if (!bVar1) {
    local_1f0 = &DAT_002ae746;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,L"new “%1”",8);
    QString::QString((QString *)local_148,(QArrayDataPointer *)local_168);
    QChar::QChar<char16_t,true>((QChar *)&local_216,L' ');
    ::QVariant::QVariant(local_88,"appointment");
    QString::QString((QString *)local_128,"title");
    QMap<QString,QVariant>::value(local_68,(QVariant *)local_210);
    ::QVariant::toString();
    QString::arg<QString,true>(local_e8,local_148,local_108,0,local_216);
  }
  else {
    local_1f8 = &DAT_002ae72c;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_1e8,(QTypedArrayData *)0x0,L"edit “%1”",9);
    QString::QString(local_1c8,(QArrayDataPointer *)local_1e8);
    QChar::QChar<char16_t,true>((QChar *)&local_218,L' ');
    ::QVariant::QVariant(local_c8);
    QString::QString(local_1a8,"title");
    QMap<QString,QVariant>::value(local_a8,(QVariant *)local_210);
    ::QVariant::toString();
    QString::arg<QString,true>(local_e8,local_1c8,local_188,0,local_218);
  }
  pushUndo(in_RSI,local_e8);
  QString::~QString(local_e8);
  if (!bVar1) {
    QString::~QString(local_108);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
  }
  else {
    QString::~QString(local_188);
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString(local_1a8);
    ::QVariant::~QVariant(local_c8);
    QString::~QString(local_1c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1e8);
  }
  cVar2 = QString::isEmpty((QString *)param_1);
  if (cVar2 == '\0') {
    bVar1 = false;
    for (local_214 = 0; lVar5 = (long)local_214,
        lVar4 = QList<QVariant>::size((QList<QVariant> *)(in_RSI + 0x28)), lVar5 < lVar4;
        local_214 = local_214 + 1) {
      QList<QVariant>::operator[]((QList<QVariant> *)(in_RSI + 0x28),(long)local_214);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_88);
      QString::QString(local_108,"id");
      QMap<QString,QVariant>::value(local_68,local_128);
      ::QVariant::toString();
      cVar2 = ::operator==(local_e8,(QString *)param_1);
      QString::~QString(local_e8);
      ::QVariant::~QVariant((QVariant *)local_68);
      QString::~QString(local_108);
      ::QVariant::~QVariant(local_88);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_128);
      if (cVar2 != '\0') {
        ::QVariant::QVariant((QVariant *)local_68,(QMap *)local_210);
        pQVar3 = (QVariant *)
                 QList<QVariant>::operator[]((QList<QVariant> *)(in_RSI + 0x28),(long)local_214);
        ::QVariant::operator=(pQVar3,(QVariant *)local_68);
        ::QVariant::~QVariant((QVariant *)local_68);
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      ::QVariant::QVariant((QVariant *)local_68,(QMap *)local_210);
      QList<QVariant>::append((QList<QVariant> *)(in_RSI + 0x28),(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
    }
  }
  else {
    uid();
    QString::operator=((QString *)param_1,local_e8);
    QString::~QString(local_e8);
    ::QVariant::QVariant((QVariant *)local_68,(QString *)param_1);
    QString::QString(local_e8,"id");
    pQVar3 = (QVariant *)QMap<QString,QVariant>::operator[](local_210,local_e8);
    ::QVariant::operator=(pQVar3,(QVariant *)local_68);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QVariant::QVariant((QVariant *)local_68,(QMap *)local_210);
    QList<QVariant>::append((QList<QVariant> *)(in_RSI + 0x28),(QVariant *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
  }
  save();
  changed(in_RSI);
  QMap<QString,QVariant>::~QMap(local_210);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 002662de  CalendarBackend::deleteAppointment

/* CalendarBackend::deleteAppointment(QString const&) */

void __thiscall CalendarBackend::deleteAppointment(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  long lVar2;
  long in_FS_OFFSET;
  int local_114;
  undefined8 local_110;
  ulong local_108;
  QList<QVariant> *local_100;
  undefined8 local_f8;
  undefined *local_f0;
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_e8,"appointment");
  local_100 = (QList<QVariant> *)(this + 0x28);
  local_110 = QList<QVariant>::begin(local_100);
  local_108 = QList<QVariant>::end(local_100);
  while( true ) {
    cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_110,local_108);
    if (cVar1 == '\0') break;
    local_f8 = QList<QVariant>::iterator::operator*((iterator *)&local_110);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"id");
    QMap<QString,QVariant>::value(local_48,local_c8);
    ::QVariant::toString();
    cVar1 = ::operator==(local_88,param_1);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
    if (cVar1 != '\0') {
      ::QVariant::toMap();
      ::QVariant::QVariant(local_68);
      QString::QString(local_a8,"title");
      QMap<QString,QVariant>::value(local_48,local_c8);
      ::QVariant::toString();
      QString::operator=(local_e8,local_88);
      QString::~QString(local_88);
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_a8);
      ::QVariant::~QVariant(local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
      break;
    }
    QList<QVariant>::iterator::operator++((iterator *)&local_110);
  }
  local_f0 = &DAT_002ae764;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"delete “%1”",0xb);
  QString::QString(local_a8,(QArrayDataPointer *)local_c8);
  QChar::QChar<char16_t,true>((QChar *)&local_108,L' ');
  QString::arg<QString,true>(local_88,local_a8,local_e8,0,local_108 & 0xffff);
  pushUndo(this,local_88);
  QString::~QString(local_88);
  QString::~QString(local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  local_114 = 0;
  do {
    lVar2 = QList<QVariant>::size((QList<QVariant> *)(this + 0x28));
    if (lVar2 <= local_114) {
LAB_0026674e:
      save();
      changed(this);
      QString::~QString(local_e8);
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x28),(long)local_114);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"id");
    QMap<QString,QVariant>::value(local_48,local_c8);
    ::QVariant::toString();
    cVar1 = ::operator==(local_88,param_1);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
    if (cVar1 != '\0') {
      QList<QVariant>::removeAt((QList<QVariant> *)(this + 0x28),(long)local_114);
      goto LAB_0026674e;
    }
    local_114 = local_114 + 1;
  } while( true );
}



// ==== 002668d6  CalendarBackend::upsertTodo

/* CalendarBackend::upsertTodo(QMap<QString, QVariant> const&) */

QMap * CalendarBackend::upsertTodo(QMap *param_1)

{
  char cVar1;
  QVariant *pQVar2;
  long lVar3;
  QMap *in_RDX;
  CalendarBackend *in_RSI;
  long in_FS_OFFSET;
  int local_f4;
  QMap<QString,QVariant> local_f0 [8];
  wchar16 *local_e8;
  wchar16 *local_e0;
  QArrayDataPointer<char16_t> local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QVariant local_78 [32];
  QString local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QMap<QString,QVariant>::QMap(local_f0,in_RDX);
  ::QVariant::QVariant(local_78);
  QString::QString(local_98,"id");
  QMap<QString,QVariant>::value(local_58,(QVariant *)local_f0);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_58);
  QString::~QString(local_98);
  ::QVariant::~QVariant(local_78);
  cVar1 = QString::isEmpty((QString *)param_1);
  if (cVar1 == '\0') {
    local_e0 = L"edit task";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_b8,(QTypedArrayData *)0x0,L"edit task",9);
    QString::QString(local_98,(QArrayDataPointer *)local_b8);
  }
  else {
    local_e8 = L"new task";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"new task",8);
    QString::QString(local_98,(QArrayDataPointer *)local_d8);
  }
  pushUndo(in_RSI,local_98);
  QString::~QString(local_98);
  if (cVar1 == '\0') {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  }
  cVar1 = QString::isEmpty((QString *)param_1);
  if (cVar1 == '\0') {
    for (local_f4 = 0; lVar3 = QList<QVariant>::size((QList<QVariant> *)(in_RSI + 0x40)),
        local_f4 < lVar3; local_f4 = local_f4 + 1) {
      QList<QVariant>::operator[]((QList<QVariant> *)(in_RSI + 0x40),(long)local_f4);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_78);
      QString::QString((QString *)local_b8,"id");
      QMap<QString,QVariant>::value(local_58,(QVariant *)local_d8);
      ::QVariant::toString();
      cVar1 = ::operator==(local_98,(QString *)param_1);
      QString::~QString(local_98);
      ::QVariant::~QVariant((QVariant *)local_58);
      QString::~QString((QString *)local_b8);
      ::QVariant::~QVariant(local_78);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_d8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant((QVariant *)local_58,(QMap *)local_f0);
        pQVar2 = (QVariant *)
                 QList<QVariant>::operator[]((QList<QVariant> *)(in_RSI + 0x40),(long)local_f4);
        ::QVariant::operator=(pQVar2,(QVariant *)local_58);
        ::QVariant::~QVariant((QVariant *)local_58);
        break;
      }
    }
  }
  else {
    uid();
    QString::operator=((QString *)param_1,local_98);
    QString::~QString(local_98);
    ::QVariant::QVariant((QVariant *)local_58,(QString *)param_1);
    QString::QString(local_98,"id");
    pQVar2 = (QVariant *)QMap<QString,QVariant>::operator[](local_f0,local_98);
    ::QVariant::operator=(pQVar2,(QVariant *)local_58);
    QString::~QString(local_98);
    ::QVariant::~QVariant((QVariant *)local_58);
    ::QVariant::QVariant((QVariant *)local_58,(QMap *)local_f0);
    QList<QVariant>::append((QList<QVariant> *)(in_RSI + 0x40),(QVariant *)local_58);
    ::QVariant::~QVariant((QVariant *)local_58);
  }
  save();
  changed(in_RSI);
  QMap<QString,QVariant>::~QMap(local_f0);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00266edc  CalendarBackend::toggleTodo

/* CalendarBackend::toggleTodo(QString const&) */

void __thiscall CalendarBackend::toggleTodo(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  byte bVar2;
  QVariant *pQVar3;
  long lVar4;
  long in_FS_OFFSET;
  int iStack_dc;
  QVariant aQStack_d8 [8];
  wchar16 *pwStack_d0;
  QArrayDataPointer<char16_t> aQStack_c8 [32];
  QString aQStack_a8 [32];
  QVariant aQStack_88 [32];
  QVariant aQStack_68 [32];
  QString aQStack_48 [40];
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  pwStack_d0 = L"task";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_c8,(QTypedArrayData *)0x0,L"task",4);
  QString::QString(aQStack_a8,(QArrayDataPointer *)aQStack_c8);
  pushUndo(this,aQStack_a8);
  QString::~QString(aQStack_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_c8);
  for (iStack_dc = 0; lVar4 = QList<QVariant>::size((QList<QVariant> *)(this + 0x40)),
      iStack_dc < lVar4; iStack_dc = iStack_dc + 1) {
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x40),(long)iStack_dc);
    ::QVariant::toMap();
    ::QVariant::QVariant(aQStack_68);
    QString::QString((QString *)aQStack_c8,"id");
    QMap<QString,QVariant>::value(aQStack_48,aQStack_d8);
    ::QVariant::toString();
    cVar1 = ::operator==(aQStack_a8,param_1);
    QString::~QString(aQStack_a8);
    ::QVariant::~QVariant((QVariant *)aQStack_48);
    QString::~QString((QString *)aQStack_c8);
    ::QVariant::~QVariant(aQStack_68);
    if (cVar1 != '\0') {
      ::QVariant::QVariant(aQStack_88);
      QString::QString(aQStack_a8,"done");
      QMap<QString,QVariant>::value((QString *)aQStack_68,aQStack_d8);
      bVar2 = ::QVariant::toBool();
      ::QVariant::QVariant((QVariant *)aQStack_48,(bool)(bVar2 ^ 1));
      QString::QString((QString *)aQStack_c8,"done");
      pQVar3 = (QVariant *)
               QMap<QString,QVariant>::operator[]
                         ((QMap<QString,QVariant> *)aQStack_d8,(QString *)aQStack_c8);
      ::QVariant::operator=(pQVar3,(QVariant *)aQStack_48);
      QString::~QString((QString *)aQStack_c8);
      ::QVariant::~QVariant((QVariant *)aQStack_48);
      ::QVariant::~QVariant(aQStack_68);
      QString::~QString(aQStack_a8);
      ::QVariant::~QVariant(aQStack_88);
      ::QVariant::QVariant((QVariant *)aQStack_48,(QMap *)aQStack_d8);
      pQVar3 = (QVariant *)
               QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x40),(long)iStack_dc);
      ::QVariant::operator=(pQVar3,(QVariant *)aQStack_48);
      ::QVariant::~QVariant((QVariant *)aQStack_48);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)aQStack_d8);
    if (cVar1 != '\0') break;
  }
  save();
  changed(this);
  if (lStack_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00267354  CalendarBackend::deleteTodo

/* CalendarBackend::deleteTodo(QString const&) */

void __thiscall CalendarBackend::deleteTodo(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  long lVar2;
  long in_FS_OFFSET;
  int iStack_bc;
  QVariant aQStack_b8 [8];
  wchar16 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString aQStack_88 [32];
  QVariant aQStack_68 [32];
  QString aQStack_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b0 = L"delete task";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"delete task",0xb)
  ;
  QString::QString(aQStack_88,(QArrayDataPointer *)local_a8);
  pushUndo(this,aQStack_88);
  QString::~QString(aQStack_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  iStack_bc = 0;
  do {
    lVar2 = QList<QVariant>::size((QList<QVariant> *)(this + 0x40));
    if (lVar2 <= iStack_bc) {
LAB_00267539:
      save();
      changed(this);
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    QList<QVariant>::operator[]((QList<QVariant> *)(this + 0x40),(long)iStack_bc);
    ::QVariant::toMap();
    ::QVariant::QVariant(aQStack_68);
    QString::QString((QString *)local_a8,"id");
    QMap<QString,QVariant>::value(aQStack_48,aQStack_b8);
    ::QVariant::toString();
    cVar1 = ::operator==(aQStack_88,param_1);
    QString::~QString(aQStack_88);
    ::QVariant::~QVariant((QVariant *)aQStack_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(aQStack_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)aQStack_b8);
    if (cVar1 != '\0') {
      QList<QVariant>::removeAt((QList<QVariant> *)(this + 0x40),(long)iStack_bc);
      goto LAB_00267539;
    }
    iStack_bc = iStack_bc + 1;
  } while( true );
}



// ==== 0026761a  CalendarBackend::pushUndo

/* WARNING: Removing unreachable block (ram,0x002676ba) */
/* WARNING: Removing unreachable block (ram,0x002676ce) */
/* CalendarBackend::pushUndo(QString const&) */

void __thiscall CalendarBackend::pushUndo(CalendarBackend *this,QString *param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  QString local_78 [24];
  QList<QVariant> aQStack_60 [24];
  QList<QVariant> aQStack_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_78,param_1);
  QList<QVariant>::QList(aQStack_60,(QList *)(this + 0x28));
  QList<QVariant>::QList(aQStack_48,(QList *)(this + 0x40));
  QList<CalendarBackend::Snapshot>::append
            ((QList<CalendarBackend::Snapshot> *)(this + 0x10),(Snapshot *)local_78);
  Snapshot::~Snapshot((Snapshot *)local_78);
  lVar1 = QList<CalendarBackend::Snapshot>::size((QList<CalendarBackend::Snapshot> *)(this + 0x10));
  if (0x32 < lVar1) {
    QList<CalendarBackend::Snapshot>::removeFirst((QList<CalendarBackend::Snapshot> *)(this + 0x10))
    ;
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0026777e  CalendarBackend::undo

/* CalendarBackend::undo() */

QString * CalendarBackend::undo(void)

{
  char cVar1;
  CalendarBackend *in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  QString local_68 [24];
  QList aQStack_50 [24];
  QList aQStack_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QList<CalendarBackend::Snapshot>::isEmpty
                    ((QList<CalendarBackend::Snapshot> *)(in_RSI + 0x10));
  if (cVar1 == '\0') {
    QList<CalendarBackend::Snapshot>::takeLast();
    QList<QVariant>::operator=((QList<QVariant> *)(in_RSI + 0x28),aQStack_50);
    QList<QVariant>::operator=((QList<QVariant> *)(in_RSI + 0x40),aQStack_38);
    save();
    changed(in_RSI);
    QString::QString(in_RDI,local_68);
    Snapshot::~Snapshot((Snapshot *)local_68);
  }
  else {
    QString::QString(in_RDI);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 00267ff8  CalendarBackend::exportICS

/* CalendarBackend::exportICS() const */

QString * CalendarBackend::exportICS(void)

{
  bool bVar1;
  char cVar2;
  QList<QString> *pQVar3;
  undefined **ppuVar4;
  QString *pQVar5;
  long in_RSI;
  QString *in_RDI;
  long lVar6;
  long in_FS_OFFSET;
  QString *local_2d0;
  undefined1 local_2b1;
  undefined8 local_2b0;
  undefined8 local_2a8;
  QVariant local_2a0 [8];
  QList<QVariant> *local_298;
  undefined8 local_290;
  QList<QString> local_288 [32];
  QString local_268 [32];
  QString local_248 [32];
  QString local_228 [32];
  QString local_208 [32];
  _lambda_int__1_ local_1e8 [32];
  QString local_1c8 [32];
  QString local_1a8 [32];
  QString local_188 [32];
  undefined2 local_168 [16];
  QString local_148 [32];
  char *local_128 [4];
  QVariant local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [96];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_2d0 = local_a8;
  ppuVar4 = &C_208_0;
  for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
    QString::QString(local_2d0,*ppuVar4);
    local_2d0 = local_2d0 + 0x18;
    ppuVar4 = ppuVar4 + 1;
  }
  QList<QString>::QList(local_288,local_a8,4);
  pQVar5 = aQStack_48;
  while (pQVar5 != local_a8) {
    pQVar5 = pQVar5 + -0x18;
    QString::~QString(pQVar5);
  }
  local_298 = (QList<QVariant> *)(in_RSI + 0x28);
  local_2b0 = QList<QVariant>::begin(local_298);
  local_2a8 = QList<QVariant>::end(local_298);
  do {
    cVar2 = QList<QVariant>::const_iterator::operator!=((const_iterator *)&local_2b0,local_2a8);
    if (cVar2 == '\0') {
      QString::QString((QString *)local_128,"END:VCALENDAR");
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
                    /* try { // try from 00268f91 to 00369077 has its CatchHandler @ 00269f9b */
      QString::QString((QString *)local_128,"\r\n");
      QListSpecialMethods<QString>::join(in_RDI);
      QString::~QString((QString *)local_128);
      QList<QString>::~QList(local_288);
      if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return in_RDI;
    }
    local_290 = QList<QVariant>::const_iterator::operator*((const_iterator *)&local_2b0);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_c8);
    QString::QString(local_148,"date");
    QMap<QString,QVariant>::value(local_a8,local_2a0);
    ::QVariant::toString();
    QChar::QChar<char,true>((QChar *)local_168,'-');
    pQVar5 = (QString *)QString::remove(local_128,local_168[0],1);
    QString::QString(local_268,pQVar5);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString(local_148);
    ::QVariant::~QVariant(local_c8);
    QString::QString(local_1a8,"BEGIN:VEVENT");
    pQVar3 = (QList<QString> *)QList<QString>::operator<<(local_288,local_1a8);
    ::QVariant::QVariant(local_c8);
    QString::QString(local_188,"id");
    QMap<QString,QVariant>::value(local_a8,local_2a0);
    ::QVariant::toString();
    ::operator+((char *)local_148,(QString *)&DAT_002ae7f8);
    ::operator+((QString *)local_128,(char *)local_148);
    QList<QString>::operator<<(pQVar3,(QString *)local_128);
    QString::~QString((QString *)local_128);
    QString::~QString(local_148);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString(local_188);
    ::QVariant::~QVariant(local_c8);
    QString::~QString(local_1a8);
    ::QVariant::QVariant(local_c8);
    QString::QString((QString *)local_128,"allDay");
    QMap<QString,QVariant>::value(local_a8,local_2a0);
    cVar2 = ::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant(local_c8);
    if (cVar2 == '\0') {
      ::QVariant::QVariant(local_108);
      QString::QString(local_208,"start");
      QMap<QString,QVariant>::value(local_e8,local_2a0);
      ::QVariant::toInt((bool *)local_e8);
      const::{lambda(int)#1}::operator()(local_1e8,(int)&local_2b1);
      ::operator+((char *)local_248,(QString *)"DTSTART:");
      ::operator+(local_228,(char *)local_248);
      ::operator+(local_1c8,local_228);
      pQVar3 = (QList<QString> *)QList<QString>::operator<<(local_288,local_1c8);
      ::QVariant::QVariant(local_c8);
      QString::QString((QString *)local_168,"end");
      QMap<QString,QVariant>::value(local_a8,local_2a0);
                    /* catch() { ... } // from try @ 00268b4b with catch @ 00268598 */
      ::QVariant::toInt((bool *)local_a8);
      const::{lambda(int)#1}::operator()((_lambda_int__1_ *)local_148,(int)&local_2b1);
      ::operator+((char *)local_1a8,(QString *)"DTEND:");
                    /* try { // try from 002685e9 to 003685ed has its CatchHandler @ 00268b1f */
      ::operator+(local_188,(char *)local_1a8);
                    /* try { // try from 00268612 to 00368616 has its CatchHandler @ 002689ee */
      ::operator+((QString *)local_128,local_188);
                    /* try { // try from 00268628 to 0036862c has its CatchHandler @ 002689dd */
      QList<QString>::operator<<(pQVar3,(QString *)local_128);
      QString::~QString((QString *)local_128);
      QString::~QString(local_188);
      QString::~QString(local_1a8);
      QString::~QString(local_148);
      ::QVariant::~QVariant((QVariant *)local_a8);
                    /* try { // try from 00268680 to 00368684 has its CatchHandler @ 00268b1f */
      QString::~QString((QString *)local_168);
      ::QVariant::~QVariant(local_c8);
      QString::~QString(local_1c8);
                    /* try { // try from 002686a9 to 003686ad has its CatchHandler @ 00268a1f */
      QString::~QString(local_228);
                    /* try { // try from 002686bf to 003686c3 has its CatchHandler @ 00268a0e */
      QString::~QString(local_248);
      QString::~QString((QString *)local_1e8);
      ::QVariant::~QVariant((QVariant *)local_e8);
      QString::~QString(local_208);
      ::QVariant::~QVariant(local_108);
    }
    else {
      ::operator+((char *)local_128,(QString *)"DTSTART;VALUE=DATE:");
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
    }
    ::QVariant::QVariant(local_c8);
                    /* try { // try from 00268717 to 0036871b has its CatchHandler @ 00268b1f */
    QString::QString(local_188,"title");
                    /* try { // try from 00268740 to 00368744 has its CatchHandler @ 00268a50 */
    QMap<QString,QVariant>::value(local_a8,local_2a0);
                    /* try { // try from 00268756 to 0036875a has its CatchHandler @ 00268a3f */
    ::QVariant::toString();
    icsEsc(local_148);
    ::operator+((char *)local_128,(QString *)"SUMMARY:");
                    /* try { // try from 002687ab to 003687af has its CatchHandler @ 00268b1f */
    QList<QString>::operator<<(local_288,(QString *)local_128);
    QString::~QString((QString *)local_128);
    QString::~QString(local_148);
                    /* try { // try from 002687d4 to 003687d8 has its CatchHandler @ 00268a81 */
    QString::~QString((QString *)local_168);
                    /* try { // try from 002687ea to 003687ee has its CatchHandler @ 00268a70 */
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString(local_188);
    ::QVariant::~QVariant(local_c8);
    ::QVariant::QVariant(local_c8);
    QString::QString(local_148,"location");
                    /* try { // try from 00268842 to 00368846 has its CatchHandler @ 00268b1f */
    QMap<QString,QVariant>::value(local_a8,local_2a0);
                    /* try { // try from 0026886b to 0036886f has its CatchHandler @ 00268ab2 */
    ::QVariant::toString();
                    /* try { // try from 00268881 to 00368885 has its CatchHandler @ 00268aa1 */
    cVar2 = QString::isEmpty((QString *)local_128);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString(local_148);
    ::QVariant::~QVariant(local_c8);
    if (cVar2 != '\x01') {
                    /* try { // try from 002688d9 to 003688dd has its CatchHandler @ 00268b1f */
      ::QVariant::QVariant(local_c8);
      QString::QString(local_188,"location");
                    /* try { // try from 00268902 to 00368906 has its CatchHandler @ 00268ae0 */
                    /* try { // try from 00268918 to 0036891c has its CatchHandler @ 00268acf */
      QMap<QString,QVariant>::value(local_a8,local_2a0);
      ::QVariant::toString();
      icsEsc(local_148);
      ::operator+((char *)local_128,(QString *)"LOCATION:");
                    /* try { // try from 00268980 to 00368984 has its CatchHandler @ 00268b0e */
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
                    /* try { // try from 00268996 to 0036899a has its CatchHandler @ 00268afd */
      QString::~QString(local_148);
      QString::~QString((QString *)local_168);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString(local_188);
                    /* catch() { ... } // from try @ 00268628 with catch @ 002689dd */
      ::QVariant::~QVariant(local_c8);
    }
    ::QVariant::QVariant(local_c8);
                    /* catch() { ... } // from try @ 00268612 with catch @ 002689ee */
    QString::QString(local_148,"notes");
                    /* catch() { ... } // from try @ 002686bf with catch @ 00268a0e */
                    /* catch() { ... } // from try @ 002686a9 with catch @ 00268a1f */
    QMap<QString,QVariant>::value(local_a8,local_2a0);
                    /* catch() { ... } // from try @ 00268756 with catch @ 00268a3f */
    ::QVariant::toString();
                    /* catch() { ... } // from try @ 00268740 with catch @ 00268a50 */
    cVar2 = QString::isEmpty((QString *)local_128);
    QString::~QString((QString *)local_128);
                    /* catch() { ... } // from try @ 002687ea with catch @ 00268a70 */
    ::QVariant::~QVariant((QVariant *)local_a8);
                    /* catch() { ... } // from try @ 002687d4 with catch @ 00268a81 */
    QString::~QString(local_148);
    ::QVariant::~QVariant(local_c8);
    if (cVar2 != '\x01') {
                    /* catch() { ... } // from try @ 00268881 with catch @ 00268aa1 */
      ::QVariant::QVariant(local_c8);
                    /* catch() { ... } // from try @ 0026886b with catch @ 00268ab2 */
      QString::QString(local_188,"notes");
                    /* catch() { ... } // from try @ 00268918 with catch @ 00268acf */
                    /* catch() { ... } // from try @ 00268902 with catch @ 00268ae0 */
      QMap<QString,QVariant>::value(local_a8,local_2a0);
                    /* catch() { ... } // from try @ 00268996 with catch @ 00268afd */
      ::QVariant::toString();
                    /* catch() { ... } // from try @ 00268980 with catch @ 00268b0e */
      icsEsc(local_148);
                    /* catch() { ... } // from try @ 002688d9 with catch @ 00268b1f */
      ::operator+((char *)local_128,(QString *)"DESCRIPTION:");
                    /* try { // try from 00268b4b to 00368b4f has its CatchHandler @ 00268598 */
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
      QString::~QString(local_148);
      QString::~QString((QString *)local_168);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString(local_188);
      ::QVariant::~QVariant(local_c8);
    }
    ::QVariant::QVariant(local_c8);
    QString::QString((QString *)local_128,"repeat");
    QMap<QString,QVariant>::value(local_a8,local_2a0);
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_a8);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant(local_c8);
    cVar2 = QString::isEmpty(local_188);
    if (cVar2 == '\x01') {
LAB_00268c86:
      bVar1 = false;
    }
    else {
      local_128[0] = "none";
                    /* catch() { ... } // from try @ 0026a017 with catch @ 00268c72 */
      cVar2 = ::operator!=(local_188,local_128);
      if (cVar2 == '\0') goto LAB_00268c86;
      bVar1 = true;
    }
    if (bVar1) {
      QString::toUpper(local_148);
                    /* try { // try from 00268cb6 to 00368cba has its CatchHandler @ 00268c72 */
                    /* try { // try from 00268cc5 to 00368ce6 has its CatchHandler @ 00269feb */
      ::operator+((char *)local_128,(QString *)"RRULE:FREQ=");
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
      QString::~QString(local_148);
    }
    ::QVariant::QVariant(local_c8);
                    /* try { // try from 00268d1b to 00368d1f has its CatchHandler @ 00269fd7 */
    QString::QString(local_148,"category");
                    /* try { // try from 00268d2a to 00368d73 has its CatchHandler @ 00269fc3 */
    QMap<QString,QVariant>::value(local_a8,local_2a0);
    ::QVariant::toString();
    cVar2 = QString::isEmpty((QString *)local_128);
    QString::~QString((QString *)local_128);
    ::QVariant::~QVariant((QVariant *)local_a8);
                    /* try { // try from 00268d98 to 00368d9c has its CatchHandler @ 00269f26 */
    QString::~QString(local_148);
    ::QVariant::~QVariant(local_c8);
    if (cVar2 != '\x01') {
      ::QVariant::QVariant(local_c8);
      QString::QString((QString *)local_168,"category");
                    /* try { // try from 00268dfa to 00368ecf has its CatchHandler @ 00269faf */
      QMap<QString,QVariant>::value(local_a8,local_2a0);
      ::QVariant::toString();
      ::operator+((char *)local_128,(QString *)"CATEGORIES:");
      QList<QString>::operator<<(local_288,(QString *)local_128);
      QString::~QString((QString *)local_128);
      QString::~QString(local_148);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString((QString *)local_168);
      ::QVariant::~QVariant(local_c8);
    }
    QString::QString((QString *)local_128,"END:VEVENT");
    QList<QString>::operator<<(local_288,(QString *)local_128);
    QString::~QString((QString *)local_128);
    QString::~QString(local_188);
    QString::~QString(local_268);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_2a0);
    QList<QVariant>::const_iterator::operator++((const_iterator *)&local_2b0);
  } while( true );
}



// ==== 00269682  CalendarBackend::exportICSToFile

/* CalendarBackend::exportICSToFile(QString const&) const */

bool __thiscall CalendarBackend::exportICSToFile(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QFile local_88 [16];
  QString local_78 [32];
  QUrl local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_78,param_1);
  QString::QString(local_38,"file://");
  cVar1 = QString::startsWith(local_78,local_38,1);
  QString::~QString(local_38);
  if (cVar1 != '\0') {
    QUrl::QUrl(local_58,local_78,0);
    QUrl::toLocalFile();
    QString::operator=(local_78,local_38);
    QString::~QString(local_38);
    QUrl::~QUrl(local_58);
  }
  QFile::QFile(local_88,local_78);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_88,uVar2);
  if (cVar1 == '\x01') {
    exportICS();
    QString::toUtf8(local_38);
    QIODevice::write((QByteArray *)local_88);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QString::~QString((QString *)local_58);
    QFileDevice::close();
  }
  QFile::~QFile(local_88);
  QString::~QString(local_78);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return cVar1 == '\x01';
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002698bc  CalendarBackend::importICS(QString_const&)::{lambda(QString_const&,QString&,int&)#1}::operator()

/* CalendarBackend::importICS(QString const&)::{lambda(QString const&, QString&,
   int&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&, QString&, int&) const */

undefined8 __thiscall
CalendarBackend::importICS(QString_const&)::{lambda(QString_const&,QString&,int&)#1}::operator()
          (_lambda_QString_const__QString__int___1_ *this,QString *param_1,QString *param_2,
          int *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  QRegularExpression local_118 [8];
  QRegularExpressionMatch local_110 [8];
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  undefined4 local_68 [8];
  undefined4 local_48 [6];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QFlags<QRegularExpression::PatternOption>::QFlags
            ((QFlags<QRegularExpression::PatternOption> *)local_68,0);
  QString::QString((QString *)local_48,"(\\d{4})(\\d{2})(\\d{2})(?:T(\\d{2})(\\d{2}))?");
  QRegularExpression::QRegularExpression(local_118,local_48,local_68[0]);
  QString::~QString((QString *)local_48);
  QFlags<QRegularExpression::MatchOption>::QFlags
            ((QFlags<QRegularExpression::MatchOption> *)local_48,0);
  QRegularExpression::match(local_110,local_118,param_1,0,0,local_48[0]);
  cVar1 = QRegularExpressionMatch::hasMatch();
  if (cVar1 == '\x01') {
    QRegularExpressionMatch::captured((int)local_68);
    QRegularExpressionMatch::captured((int)local_c8);
    QRegularExpressionMatch::captured((int)local_108);
    ::operator+(local_e8,(char *)local_108);
    ::operator+(local_a8,local_e8);
    ::operator+(local_88,(char *)local_a8);
    ::operator+((QString *)local_48,local_88);
    QString::operator=(param_2,(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_88);
    QString::~QString(local_a8);
    QString::~QString(local_e8);
    QString::~QString(local_108);
    QString::~QString(local_c8);
    QString::~QString((QString *)local_68);
    QRegularExpressionMatch::captured((int)local_88);
    cVar1 = QString::isEmpty(local_88);
    if (cVar1 == '\0') {
      QRegularExpressionMatch::captured((int)local_68);
      iVar2 = QString::toInt((QString *)local_68,(bool *)0x0,10);
      QRegularExpressionMatch::captured((int)local_48);
      iVar3 = QString::toInt((QString *)local_48,(bool *)0x0,10);
      iVar3 = iVar2 * 0x3c + iVar3;
    }
    else {
      iVar3 = -1;
    }
    *param_3 = iVar3;
    if (cVar1 == '\0') {
      QString::~QString((QString *)local_48);
      QString::~QString((QString *)local_68);
    }
    QString::~QString(local_88);
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  QRegularExpressionMatch::~QRegularExpressionMatch(local_110);
  QRegularExpression::~QRegularExpression(local_118);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00269d3a  CalendarBackend::importICS

/* CalendarBackend::importICS(QString const&) */

int __thiscall CalendarBackend::importICS(CalendarBackend *this,QString *param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  char cVar4;
  QString *pQVar5;
  QVariant *pQVar6;
  pair<QString,QVariant> *ppVar7;
  long in_FS_OFFSET;
  _lambda_QString_const__QString__int___1_ _Stack_5b7;
  bool bStack_5b6;
  char cStack_5b5;
  int iStack_5b4;
  int aiStack_5b0 [4];
  undefined8 uStack_5a0;
  undefined8 uStack_598;
  undefined8 uStack_590;
  QMap aQStack_588 [8];
  QList<QString> *pQStack_580;
  QString *pQStack_578;
  wchar16 *local_570;
  QString local_568 [32];
  QList<QString> aQStack_548 [32];
  QString aQStack_528 [32];
  QString aQStack_508 [32];
  QString aQStack_4e8 [32];
  undefined4 local_4c8 [8];
  int local_4a8 [8];
  ulong local_488 [4];
  char *local_468 [4];
  QVariant aQStack_448 [32];
  QString aQStack_428 [32];
  QVariant aQStack_408 [32];
  QString aQStack_3e8 [32];
  QVariant aQStack_3c8 [32];
  QString aQStack_3a8 [32];
  QVariant aQStack_388 [32];
  QString aQStack_368 [32];
  QVariant aQStack_348 [32];
  QString aQStack_328 [32];
  QVariant aQStack_308 [32];
  QString aQStack_2e8 [32];
  QVariant aQStack_2c8 [32];
  pair<QString,QVariant> apStack_2a8 [56];
  pair<QString,QVariant> apStack_270 [56];
  pair<QString,QVariant> apStack_238 [56];
  pair<QString,QVariant> apStack_200 [56];
  pair<QString,QVariant> apStack_1c8 [56];
  pair<QString,QVariant> apStack_190 [56];
  pair<QString,QVariant> apStack_158 [56];
  pair<QString,QVariant> apStack_120 [56];
  pair<QString,QVariant> apStack_e8 [56];
  pair<QString,QVariant> apStack_b0 [56];
  pair<QString,QVariant> apStack_78 [56];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  local_570 = L"import calendar";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_488,(QTypedArrayData *)0x0,L"import calendar",0xf)
  ;
  QString::QString((QString *)local_468,(QArrayDataPointer *)local_488);
  pushUndo(this,(QString *)local_468);
  QString::~QString((QString *)local_468);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_488);
  QString::QString(local_568,param_1);
  QString::QString((QString *)local_468,"");
  QFlags<QRegularExpression::PatternOption>::QFlags
            ((QFlags<QRegularExpression::PatternOption> *)local_4c8,0);
  QString::QString((QString *)local_488,"\\r\\n[ \\t]");
  QRegularExpression::QRegularExpression((QRegularExpression *)local_4a8,local_488,local_4c8[0]);
  QString::replace((QRegularExpression *)local_568,(QString *)local_4a8);
  QRegularExpression::~QRegularExpression((QRegularExpression *)local_4a8);
  QString::~QString((QString *)local_488);
  QString::~QString((QString *)local_468);
  QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_4a8,0);
  QFlags<QRegularExpression::PatternOption>::QFlags
            ((QFlags<QRegularExpression::PatternOption> *)local_4c8,0);
  QString::QString((QString *)local_468,"\\r?\\n");
  QRegularExpression::QRegularExpression((QRegularExpression *)local_488,local_468,local_4c8[0]);
  QString::split(aQStack_548,local_568,local_488,local_4a8[0]);
  QRegularExpression::~QRegularExpression((QRegularExpression *)local_488);
  QString::~QString((QString *)local_468);
  uStack_5a0 = 0;
  cStack_5b5 = '\0';
  aiStack_5b0[2] = 0;
  pQStack_580 = aQStack_548;
  uStack_598 = QList<QString>::begin(pQStack_580);
  uStack_590 = QList<QString>::end(pQStack_580);
  do {
    cVar4 = QList<QString>::const_iterator::operator!=((const_iterator *)&uStack_598,uStack_590);
    if (cVar4 == '\0') {
      if (aiStack_5b0[2] != 0) {
        save();
        changed(this);
      }
      iVar3 = aiStack_5b0[2];
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&uStack_5a0);
      QList<QString>::~QList(aQStack_548);
      QString::~QString(local_568);
      if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return iVar3;
    }
    pQStack_578 = (QString *)
                  QList<QString>::const_iterator::operator*((const_iterator *)&uStack_598);
    local_468[0] = "BEGIN:VEVENT";
    cVar4 = ::operator==(pQStack_578,local_468);
    if (cVar4 == '\0') {
      local_468[0] = "END:VEVENT";
      cVar4 = ::operator==(pQStack_578,local_468);
      if (cVar4 == '\0') {
        if (cStack_5b5 != '\0') {
          QChar::QChar<char,true>((QChar *)local_468,':');
          aiStack_5b0[3] = QString::indexOf(pQStack_578,(ulong)local_468[0] & 0xffff,0,1);
          if (-1 < aiStack_5b0[3]) {
            QString::left((longlong)local_488);
            QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_4a8,0);
            QChar::QChar<char,true>((QChar *)local_4c8,';');
            QString::split(local_468,local_488,(undefined2)local_4c8[0],local_4a8[0],1);
            pQVar5 = (QString *)QList<QString>::first((QList<QString> *)local_468);
            QString::QString(aQStack_4e8,pQVar5);
            QList<QString>::~QList((QList<QString> *)local_468);
            QString::~QString((QString *)local_488);
            QString::mid((longlong)local_4c8,(longlong)pQStack_578);
            local_468[0] = "SUMMARY";
            cVar4 = ::operator==(aQStack_4e8,local_468);
            if (cVar4 == '\0') {
              local_468[0] = "LOCATION";
              cVar4 = ::operator==(aQStack_4e8,local_468);
              if (cVar4 == '\0') {
                local_468[0] = "DESCRIPTION";
                cVar4 = ::operator==(aQStack_4e8,local_468);
                if (cVar4 == '\0') {
                  local_468[0] = "DTSTART";
                  cVar4 = ::operator==(aQStack_4e8,local_468);
                  if (cVar4 == '\0') {
                    local_468[0] = "DTEND";
                    cVar4 = ::operator==(aQStack_4e8,local_468);
                    if (cVar4 == '\0') {
                      local_468[0] = "RRULE";
                      cVar4 = ::operator==(aQStack_4e8,local_468);
                      if (cVar4 == '\0') {
                        local_468[0] = "CATEGORIES";
                        cVar4 = ::operator==(aQStack_4e8,local_468);
                        if (cVar4 != '\0') {
                          ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_4c8);
                          QString::QString((QString *)local_468,"category");
                          pQVar6 = (QVariant *)
                                   QMap<QString,QVariant>::operator[]
                                             ((QMap<QString,QVariant> *)&uStack_5a0,
                                              (QString *)local_468);
                          ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                          QString::~QString((QString *)local_468);
                          ::QVariant::~QVariant((QVariant *)apStack_2a8);
                        }
                      }
                      else {
                        QFlags<QRegularExpression::PatternOption>::QFlags
                                  ((QFlags<QRegularExpression::PatternOption> *)local_488,0);
                        QString::QString((QString *)local_468,"FREQ=(\\w+)");
                        QRegularExpression::QRegularExpression
                                  ((QRegularExpression *)aQStack_528,local_468,
                                   local_488[0] & 0xffffffff);
                        QString::~QString((QString *)local_468);
                        QFlags<QRegularExpression::MatchOption>::QFlags
                                  ((QFlags<QRegularExpression::MatchOption> *)local_468,0);
                        QRegularExpression::match
                                  (aQStack_508,aQStack_528,local_4c8,0,0,
                                   (ulong)local_468[0] & 0xffffffff);
                        cVar4 = QRegularExpressionMatch::hasMatch();
                        if (cVar4 != '\0') {
                          QRegularExpressionMatch::captured((int)local_488);
                          QString::toLower((QString *)local_468);
                          ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_468);
                          QString::QString((QString *)local_4a8,"repeat");
                          pQVar6 = (QVariant *)
                                   QMap<QString,QVariant>::operator[]
                                             ((QMap<QString,QVariant> *)&uStack_5a0,
                                              (QString *)local_4a8);
                          ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                          QString::~QString((QString *)local_4a8);
                          ::QVariant::~QVariant((QVariant *)apStack_2a8);
                          QString::~QString((QString *)local_468);
                          QString::~QString((QString *)local_488);
                        }
                        QRegularExpressionMatch::~QRegularExpressionMatch
                                  ((QRegularExpressionMatch *)aQStack_508);
                        QRegularExpression::~QRegularExpression((QRegularExpression *)aQStack_528);
                      }
                    }
                    else {
                      local_488[0] = 0;
                      local_488[1] = 0;
                      local_488[2] = 0;
                      cVar4 = importICS(QString_const&)::{lambda(QString_const&,QString&,int&)#1}::
                              operator()(&_Stack_5b7,(QString *)local_4c8,(QString *)local_488,
                                         local_4a8);
                      if ((cVar4 == '\0') || (local_4a8[0] < 0)) {
                        bVar1 = false;
                      }
                      else {
                        bVar1 = true;
                      }
                      if (bVar1) {
                        ::QVariant::QVariant((QVariant *)apStack_2a8,local_4a8[0]);
                        QString::QString((QString *)local_468,"end");
                        pQVar6 = (QVariant *)
                                 QMap<QString,QVariant>::operator[]
                                           ((QMap<QString,QVariant> *)&uStack_5a0,
                                            (QString *)local_468);
                        ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                        QString::~QString((QString *)local_468);
                        ::QVariant::~QVariant((QVariant *)apStack_2a8);
                      }
                      QString::~QString((QString *)local_488);
                    }
                  }
                  else {
                    local_488[0] = 0;
                    local_488[1] = 0;
                    local_488[2] = 0;
                    cVar4 = importICS(QString_const&)::{lambda(QString_const&,QString&,int&)#1}::
                            operator()(&_Stack_5b7,(QString *)local_4c8,(QString *)local_488,
                                       local_4a8);
                    if (cVar4 != '\0') {
                      ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_488);
                      QString::QString((QString *)local_468,"date");
                      pQVar6 = (QVariant *)
                               QMap<QString,QVariant>::operator[]
                                         ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_468
                                         );
                      ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                      QString::~QString((QString *)local_468);
                      ::QVariant::~QVariant((QVariant *)apStack_2a8);
                      if (-1 < local_4a8[0]) {
                        ::QVariant::QVariant((QVariant *)apStack_2a8,local_4a8[0]);
                        QString::QString((QString *)local_468,"start");
                        pQVar6 = (QVariant *)
                                 QMap<QString,QVariant>::operator[]
                                           ((QMap<QString,QVariant> *)&uStack_5a0,
                                            (QString *)local_468);
                        ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                        QString::~QString((QString *)local_468);
                        ::QVariant::~QVariant((QVariant *)apStack_2a8);
                      }
                    }
                    QString::~QString((QString *)local_488);
                  }
                }
                else {
                  icsUnesc((QString *)local_468);
                  ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_468);
                  QString::QString((QString *)local_488,"notes");
                  pQVar6 = (QVariant *)
                           QMap<QString,QVariant>::operator[]
                                     ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_488);
                  ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                  QString::~QString((QString *)local_488);
                  ::QVariant::~QVariant((QVariant *)apStack_2a8);
                  QString::~QString((QString *)local_468);
                }
              }
              else {
                icsUnesc((QString *)local_468);
                ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_468);
                QString::QString((QString *)local_488,"location");
                pQVar6 = (QVariant *)
                         QMap<QString,QVariant>::operator[]
                                   ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_488);
                ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
                QString::~QString((QString *)local_488);
                ::QVariant::~QVariant((QVariant *)apStack_2a8);
                QString::~QString((QString *)local_468);
              }
            }
            else {
              icsUnesc((QString *)local_468);
              ::QVariant::QVariant((QVariant *)apStack_2a8,(QString *)local_468);
              QString::QString((QString *)local_488,"title");
              pQVar6 = (QVariant *)
                       QMap<QString,QVariant>::operator[]
                                 ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_488);
              ::QVariant::operator=(pQVar6,(QVariant *)apStack_2a8);
              QString::~QString((QString *)local_488);
              ::QVariant::~QVariant((QVariant *)apStack_2a8);
              QString::~QString((QString *)local_468);
            }
            QString::~QString((QString *)local_4c8);
            QString::~QString(aQStack_4e8);
          }
        }
      }
      else {
        bVar1 = false;
        if (cStack_5b5 == '\0') {
code_r0x0026a1ce:
          bVar2 = false;
        }
        else {
          QString::QString((QString *)local_468,"date");
          bVar1 = true;
          cVar4 = QMap<QString,QVariant>::contains
                            ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_468);
          if (cVar4 == '\0') goto code_r0x0026a1ce;
          bVar2 = true;
        }
        if (bVar1) {
          QString::~QString((QString *)local_468);
        }
        if (bVar2) {
          QString::QString((QString *)local_468,"start");
          bStack_5b6 = (bool)QMap<QString,QVariant>::contains
                                       ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_468);
          bStack_5b6 = (bool)(bStack_5b6 ^ 1);
          QString::~QString((QString *)local_468);
          if (bStack_5b6 == false) {
            ::QVariant::QVariant(aQStack_2c8);
            QString::QString((QString *)local_468,"start");
            QMap<QString,QVariant>::value((QString *)apStack_2a8,(QVariant *)&uStack_5a0);
            iStack_5b4 = ::QVariant::toInt((bool *)apStack_2a8);
            ::QVariant::~QVariant((QVariant *)apStack_2a8);
            QString::~QString((QString *)local_468);
            ::QVariant::~QVariant(aQStack_2c8);
          }
          else {
            iStack_5b4 = 0;
          }
          QString::QString((QString *)local_488,"end");
          cVar4 = QMap<QString,QVariant>::contains
                            ((QMap<QString,QVariant> *)&uStack_5a0,(QString *)local_488);
          if (cVar4 == '\0') {
            aiStack_5b0[0] = iStack_5b4 + 0x3c;
          }
          else {
            ::QVariant::QVariant(aQStack_2c8);
            QString::QString((QString *)local_468,"end");
            QMap<QString,QVariant>::value((QString *)apStack_2a8,(QVariant *)&uStack_5a0);
            aiStack_5b0[0] = ::QVariant::toInt((bool *)apStack_2a8);
            ::QVariant::~QVariant((QVariant *)apStack_2a8);
            QString::~QString((QString *)local_468);
            ::QVariant::~QVariant(aQStack_2c8);
          }
          QString::~QString((QString *)local_488);
          uid();
          std::pair<QString,QVariant>::pair<char_const(&)[3],QString,true>
                    (apStack_2a8,"id",aQStack_528);
          ::QVariant::QVariant(aQStack_448);
          QString::QString(aQStack_508,"date");
          QMap<QString,QVariant>::value(aQStack_428,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[5],QVariant,true>
                    (apStack_270,"date",(QVariant *)aQStack_428);
          ::QVariant::QVariant(aQStack_408,"Untitled");
          QString::QString(aQStack_4e8,"title");
          QMap<QString,QVariant>::value(aQStack_3e8,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[6],QVariant,true>
                    (apStack_238,"title",(QVariant *)aQStack_3e8);
          std::pair<QString,QVariant>::pair<char_const(&)[6],int&,true>
                    (apStack_200,"start",&iStack_5b4);
          std::pair<QString,QVariant>::pair<char_const(&)[4],int&,true>
                    (apStack_1c8,"end",aiStack_5b0);
          std::pair<QString,QVariant>::pair<char_const(&)[7],bool&,true>
                    (apStack_190,"allDay",&bStack_5b6);
          ::QVariant::QVariant(aQStack_3c8);
          QString::QString((QString *)local_4c8,"location");
          QMap<QString,QVariant>::value(aQStack_3a8,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[9],QVariant,true>
                    (apStack_158,"location",(QVariant *)aQStack_3a8);
          ::QVariant::QVariant(aQStack_388);
          QString::QString((QString *)local_4a8,"notes");
          QMap<QString,QVariant>::value(aQStack_368,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[6],QVariant,true>
                    (apStack_120,"notes",(QVariant *)aQStack_368);
          ::QVariant::QVariant(aQStack_348);
          QString::QString((QString *)local_488,"repeat");
          QMap<QString,QVariant>::value(aQStack_328,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[7],QVariant,true>
                    (apStack_e8,"repeat",(QVariant *)aQStack_328);
          aiStack_5b0[1] = 0xf;
          std::pair<QString,QVariant>::pair<char_const(&)[9],int,true>
                    (apStack_b0,"reminder",aiStack_5b0 + 1);
          ::QVariant::QVariant(aQStack_308);
          QString::QString((QString *)local_468,"category");
          QMap<QString,QVariant>::value(aQStack_2e8,(QVariant *)&uStack_5a0);
          std::pair<QString,QVariant>::pair<char_const(&)[9],QVariant,true>
                    (apStack_78,"category",(QVariant *)aQStack_2e8);
          QMap<QString,QVariant>::QMap(aQStack_588,apStack_2a8,0xb);
          ::QVariant::QVariant(aQStack_2c8,aQStack_588);
          QList<QVariant>::append((QList<QVariant> *)(this + 0x28),aQStack_2c8);
          ::QVariant::~QVariant(aQStack_2c8);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)aQStack_588);
          ppVar7 = (pair<QString,QVariant> *)local_40;
          while (ppVar7 != apStack_2a8) {
            ppVar7 = ppVar7 + -0x38;
            std::pair<QString,QVariant>::~pair(ppVar7);
          }
          ::QVariant::~QVariant((QVariant *)aQStack_2e8);
          QString::~QString((QString *)local_468);
          ::QVariant::~QVariant(aQStack_308);
          ::QVariant::~QVariant((QVariant *)aQStack_328);
          QString::~QString((QString *)local_488);
          ::QVariant::~QVariant(aQStack_348);
          ::QVariant::~QVariant((QVariant *)aQStack_368);
          QString::~QString((QString *)local_4a8);
          ::QVariant::~QVariant(aQStack_388);
          ::QVariant::~QVariant((QVariant *)aQStack_3a8);
          QString::~QString((QString *)local_4c8);
          ::QVariant::~QVariant(aQStack_3c8);
          ::QVariant::~QVariant((QVariant *)aQStack_3e8);
          QString::~QString(aQStack_4e8);
          ::QVariant::~QVariant(aQStack_408);
          ::QVariant::~QVariant((QVariant *)aQStack_428);
          QString::~QString(aQStack_508);
          ::QVariant::~QVariant(aQStack_448);
          QString::~QString(aQStack_528);
          aiStack_5b0[2] = aiStack_5b0[2] + 1;
        }
        cStack_5b5 = '\0';
      }
    }
    else {
      std::pair<QString,QVariant>::pair<char_const(&)[9],char_const(&)[6],true>
                (apStack_2a8,"category","azure");
      std::pair<QString,QVariant>::pair<char_const(&)[7],char_const(&)[5],true>
                (apStack_270,"repeat","none");
      local_488[0] = CONCAT44(local_488[0]._4_4_,0xf);
      std::pair<QString,QVariant>::pair<char_const(&)[9],int,true>
                (apStack_238,"reminder",(int *)local_488);
      std::pair<QString,QVariant>::pair<char_const(&)[6],char_const(&)[1],true>
                (apStack_200,"notes","");
      std::pair<QString,QVariant>::pair<char_const(&)[9],char_const(&)[1],true>
                (apStack_1c8,"location","");
      QMap<QString,QVariant>::QMap(local_468,apStack_2a8,5);
      QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)&uStack_5a0,(QMap *)local_468);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_468);
      ppVar7 = apStack_190;
      while (ppVar7 != apStack_2a8) {
        ppVar7 = ppVar7 + -0x38;
        std::pair<QString,QVariant>::~pair(ppVar7);
      }
      cStack_5b5 = '\x01';
    }
    QList<QString>::const_iterator::operator++((const_iterator *)&uStack_598);
  } while( true );
}



// ==== 0026ba02  CalendarBackend::importICSFromFile

/* CalendarBackend::importICSFromFile(QString const&) */

undefined4 __thiscall CalendarBackend::importICSFromFile(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QFile aQStack_88 [16];
  QString aQStack_78 [32];
  QUrl aQStack_58 [32];
  undefined4 auStack_38 [6];
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(aQStack_78,param_1);
  QString::QString((QString *)auStack_38,"file://");
  cVar1 = QString::startsWith(aQStack_78,auStack_38,1);
  QString::~QString((QString *)auStack_38);
  if (cVar1 != '\0') {
    QUrl::QUrl(aQStack_58,aQStack_78,0);
    QUrl::toLocalFile();
    QString::operator=(aQStack_78,(QString *)auStack_38);
    QString::~QString((QString *)auStack_38);
    QUrl::~QUrl(aQStack_58);
  }
  QFile::QFile(aQStack_88,aQStack_78);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)auStack_38,1);
  cVar1 = QFile::open(aQStack_88,auStack_38[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QString::fromUtf8<void>((QString *)aQStack_58,(QByteArray *)auStack_38);
    QByteArray::~QByteArray((QByteArray *)auStack_38);
    QFileDevice::close();
    uVar2 = importICS(this,(QString *)aQStack_58);
    QString::~QString((QString *)aQStack_58);
  }
  else {
    uVar2 = 0;
  }
  QFile::~QFile(aQStack_88);
  QString::~QString(aQStack_78);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 0026bc3e  CalendarBackend::saveSettings

/* CalendarBackend::saveSettings(QMap<QString, QVariant> const&) */

void CalendarBackend::saveSettings(QMap *param_1)

{
  char cVar1;
  QVariant *pQVar2;
  QString *pQVar3;
  QVariant *this;
  QMap<QString,QVariant> *in_RSI;
  long in_FS_OFFSET;
  undefined8 uStack_30;
  undefined8 uStack_28;
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  uStack_30 = QMap<QString,QVariant>::begin(in_RSI);
  while( true ) {
    uStack_28 = QMap<QString,QVariant>::end(in_RSI);
    cVar1 = ::operator!=((const_iterator *)&uStack_30,(const_iterator *)&uStack_28);
    if (cVar1 == '\0') break;
    pQVar2 = (QVariant *)QMap<QString,QVariant>::const_iterator::value((const_iterator *)&uStack_30)
    ;
    pQVar3 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)&uStack_30);
    this = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(param_1 + 0x58),pQVar3);
    ::QVariant::operator=(this,pQVar2);
    QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)&uStack_30);
  }
  save();
  settingsChanged((CalendarBackend *)param_1);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0026bd14  CalendarBackend::fireReminder

/* CalendarBackend::fireReminder(QString const&, QString const&) */

void __thiscall
CalendarBackend::fireReminder(CalendarBackend *this,QString *param_1,QString *param_2)

{
  char cVar1;
  QString *this_00;
  long in_FS_OFFSET;
  QString local_f8 [32];
  QList local_d8 [32];
  QString local_b8 [32];
  QVariant local_98 [32];
  QString local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
                    /* try { // try from 0026bd1a to 0036bd1e has its CatchHandler @ 0026c1a7 */
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_98,true);
  QString::QString(local_b8,"methodDesktop");
                    /* try { // try from 0026bd85 to 0036bd89 has its CatchHandler @ 0026c1ec */
                    /* try { // try from 0026bd9b to 0036bd9f has its CatchHandler @ 0026c1db */
  QMap<QString,QVariant>::value(local_78,(QVariant *)(this + 0x58));
  cVar1 = ::QVariant::toBool();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString(local_b8);
  ::QVariant::~QVariant(local_98);
  if (cVar1 != '\0') {
    QString::QString(local_b8);
                    /* try { // try from 0026bdf8 to 0036bdfc has its CatchHandler @ 0026c211 */
                    /* try { // try from 0026be0e to 0036be12 has its CatchHandler @ 0026c200 */
    ::operator+((char *)local_78,(QString *)&DAT_002ae987);
    QString::QString(local_60,param_2);
    QList<QString>::QList(local_d8,local_78,2);
                    /* try { // try from 0026be6b to 0036be6f has its CatchHandler @ 0026c236 */
    QString::QString(local_f8,"notify-send");
                    /* try { // try from 0026be81 to 0036be85 has its CatchHandler @ 0026c225 */
    QProcess::startDetached(local_f8,local_d8,local_b8,(longlong *)0x0);
    QString::~QString(local_f8);
    QList<QString>::~QList((QList<QString> *)local_d8);
    this_00 = aQStack_48;
    while (this_00 != local_78) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
                    /* try { // try from 0026bede to 0036bee2 has its CatchHandler @ 0026c25b */
    QString::~QString(local_b8);
  }
                    /* try { // try from 0026bef4 to 0036bef8 has its CatchHandler @ 0026c24a */
  ::QVariant::QVariant(local_98,false);
  QString::QString(local_b8,"methodEmail");
  QMap<QString,QVariant>::value(local_78,(QVariant *)(this + 0x58));
  cVar1 = ::QVariant::toBool();
                    /* try { // try from 0026bf51 to 0036bf55 has its CatchHandler @ 0026c27d */
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString(local_b8);
                    /* try { // try from 0026bf67 to 0036bf6b has its CatchHandler @ 0026c26c */
  ::QVariant::~QVariant(local_98);
  if (cVar1 != '\0') {
    ::operator+((char *)local_b8,(QString *)&DAT_002ae987);
    sendEmail((QString *)this,local_b8);
                    /* try { // try from 0026bfc4 to 0036bfc8 has its CatchHandler @ 0026c29f */
    QString::~QString(local_b8);
  }
                    /* try { // try from 0026bfda to 0036bfde has its CatchHandler @ 0026c28e */
  ::QVariant::QVariant(local_98,false);
  QString::QString(local_b8,"methodNtfy");
  QMap<QString,QVariant>::value(local_78,(QVariant *)(this + 0x58));
  cVar1 = ::QVariant::toBool();
  ::QVariant::~QVariant((QVariant *)local_78);
                    /* try { // try from 0026c037 to 0036c03b has its CatchHandler @ 0026c2c1 */
  QString::~QString(local_b8);
                    /* try { // try from 0026c04d to 0036c051 has its CatchHandler @ 0026c2b0 */
  ::QVariant::~QVariant(local_98);
  if (cVar1 != '\0') {
    ::operator+((char *)local_f8,(QString *)&DAT_002ae987);
                    /* catch() { ... } // from try @ 0026b985 with catch @ 0026c094 */
    ::operator+((QString *)local_d8,(char *)local_f8);
    ::operator+(local_b8,(QString *)local_d8);
    sendNtfy(this,local_b8);
    QString::~QString(local_b8);
    QString::~QString((QString *)local_d8);
    QString::~QString(local_f8);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0026c35c to 0036c360 has its CatchHandler @ 0026c31e */
    __stack_chk_fail();
  }
                    /* try { // try from 0026c368 to 0036c36c has its CatchHandler @ 0026c512 */
  return;
}



// ==== 0026c370  CalendarBackend::sendEmail

/* WARNING: Removing unreachable block (ram,0x0026c585) */
/* CalendarBackend::sendEmail(QString const&, QString const&) */

void CalendarBackend::sendEmail(QString *param_1,QString *param_2)

{
  char cVar1;
  QProcess *pQVar2;
  QString *this;
  long in_FS_OFFSET;
  undefined1 auVar3 [16];
  undefined4 local_144;
  QProcess *local_140;
  QString local_138 [32];
  QString local_118 [32];
  QString local_f8 [32];
  Connection local_d8 [32];
  code *local_b8;
  undefined8 uStack_b0;
  QVariant local_98 [32];
  QString local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
                    /* try { // try from 0026c38c to 0036c3a8 has its CatchHandler @ 0026c4fa */
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_98);
  QString::QString((QString *)&local_b8,"email");
                    /* try { // try from 0026c3eb to 0036c3ef has its CatchHandler @ 0026c595 */
  QMap<QString,QVariant>::value(local_78,(QVariant *)(param_1 + 0x58));
                    /* try { // try from 0026c40a to 0036c435 has its CatchHandler @ 0026c584 */
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString((QString *)&local_b8);
  ::QVariant::~QVariant(local_98);
                    /* try { // try from 0026c444 to 0036c448 has its CatchHandler @ 0026c573 */
  cVar1 = QString::isEmpty(local_138);
  if (cVar1 == '\0') {
                    /* try { // try from 0026c457 to 0036c45b has its CatchHandler @ 0026c562 */
                    /* try { // try from 0026c46f to 0036c473 has its CatchHandler @ 0026c551 */
    ::QVariant::QVariant(local_98,local_138);
                    /* try { // try from 0026c482 to 0036c486 has its CatchHandler @ 0026c540 */
    QString::QString((QString *)&local_b8,"smtpFrom");
    QMap<QString,QVariant>::value(local_78,(QVariant *)(param_1 + 0x58));
                    /* try { // try from 0026c4be to 0036c4c2 has its CatchHandler @ 0026c584 */
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_78);
    QString::~QString((QString *)&local_b8);
    ::QVariant::~QVariant(local_98);
                    /* catch() { ... } // from try @ 0026c38c with catch @ 0026c4fa */
    QString::QString((QString *)&local_b8,"From: Leap Frog Ledger <%1>\nTo: %2\nSubject: %3\n\n%4\n"
                    );
                    /* catch() { ... } // from try @ 0026c368 with catch @ 0026c512 */
                    /* try { // try from 0026c53b to 0036c5c2 has its CatchHandler @ 0026c31e */
    QString::arg<QString_const&,QString_const&,QString_const&,QString_const&>
              (local_f8,(QString *)&local_b8,local_118,local_138);
                    /* catch() { ... } // from try @ 0026c482 with catch @ 0026c540 */
    QString::~QString((QString *)&local_b8);
                    /* catch() { ... } // from try @ 0026c46f with catch @ 0026c551 */
    pQVar2 = operator_new(0x10);
                    /* catch() { ... } // from try @ 0026c457 with catch @ 0026c562 */
                    /* catch() { ... } // from try @ 0026c444 with catch @ 0026c573 */
    QProcess::QProcess(pQVar2,(QObject *)param_1);
                    /* catch() { ... } // from try @ 0026c4be with catch @ 0026c584 */
                    /* catch() { ... } // from try @ 0026c3eb with catch @ 0026c595 */
    local_b8 = QObject::deleteLater;
    uStack_b0 = 0;
    local_140 = pQVar2;
    auVar3 = QNonConstOverload<int,QProcess::ExitStatus>::of<void,QProcess>
                       ((QNonConstOverload<int,QProcess::ExitStatus> *)QProcess::finished,
                        (_func_void_int_ExitStatus *)0x0);
    QObject::connect<void(QProcess::*)(int,QProcess::ExitStatus),void(QObject::*)()>
              (local_d8,local_140,auVar3._0_8_,auVar3._8_8_,local_140,&local_b8,0);
    QMetaObject::Connection::~Connection(local_d8);
    pQVar2 = local_140;
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)&local_144,3)
    ;
    QString::QString(local_78,"--");
    QString::QString(local_60,local_138);
                    /* catch() { ... } // from try @ 0026d754 with catch @ 0026c684 */
    QList<QString>::QList(&local_b8,local_78,2);
    QString::QString((QString *)local_d8,"msmtp");
                    /* try { // try from 0026c6cc to 0036c6d0 has its CatchHandler @ 0026c684 */
    QProcess::start(pQVar2,local_d8,&local_b8,local_144);
                    /* try { // try from 0026c6db to 0036c6df has its CatchHandler @ 0026d728 */
    QString::~QString((QString *)local_d8);
    QList<QString>::~QList((QList<QString> *)&local_b8);
    this = aQStack_48;
                    /* try { // try from 0026c702 to 0036c724 has its CatchHandler @ 0026d70d */
    while (this != local_78) {
      this = this + -0x18;
      QString::~QString(this);
    }
    cVar1 = QProcess::waitForStarted((int)local_140);
    pQVar2 = local_140;
    if (cVar1 != '\0') {
      QString::toUtf8((QString *)&local_b8);
      QIODevice::write((QByteArray *)pQVar2);
      QByteArray::~QByteArray((QByteArray *)&local_b8);
                    /* try { // try from 0026c776 to 0036c77a has its CatchHandler @ 0026db89 */
      QProcess::closeWriteChannel();
    }
    QString::~QString(local_f8);
    QString::~QString(local_118);
                    /* try { // try from 0026c7a1 to 0036c7cf has its CatchHandler @ 0026db75 */
  }
  QString::~QString(local_138);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0026c99c  CalendarBackend::sendNtfy

/* CalendarBackend::sendNtfy(QString const&) */

void __thiscall CalendarBackend::sendNtfy(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  QString *this_00;
  long in_FS_OFFSET;
  QString local_148 [32];
  QString local_128 [32];
  QList local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [24];
  QString local_90 [24];
  QString aQStack_78 [24];
  char local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_c8);
  QString::QString(local_e8,"ntfyTopic");
                    /* try { // try from 0026ca15 to 0036ca19 has its CatchHandler @ 0026d81e */
  QMap<QString,QVariant>::value(local_a8,(QVariant *)(this + 0x58));
                    /* try { // try from 0026ca33 to 0036ca37 has its CatchHandler @ 0026d80a */
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_a8);
                    /* try { // try from 0026ca49 to 0036ca4d has its CatchHandler @ 0026d7f9 */
  QString::~QString(local_e8);
  ::QVariant::~QVariant(local_c8);
  cVar1 = QString::isEmpty(local_148);
  if (cVar1 == '\0') {
    QString::QString(local_e8);
    QString::QString(local_a8,"-s");
                    /* try { // try from 0026cac7 to 0036cacb has its CatchHandler @ 0026d857 */
    QString::QString(local_90,"-d");
    QString::QString(aQStack_78,param_1);
                    /* try { // try from 0026cae5 to 0036cae9 has its CatchHandler @ 0026d843 */
                    /* try { // try from 0026caf1 to 0036caf5 has its CatchHandler @ 0026d832 */
    ::operator+(local_60,(QString *)"https://ntfy.sh/");
    QList<QString>::QList(local_108,local_a8,4);
    QString::QString(local_128,"curl");
                    /* try { // try from 0026cb55 to 0036cb59 has its CatchHandler @ 0026db4d */
                    /* try { // try from 0026cb6e to 0036cb72 has its CatchHandler @ 0026d86b */
    QProcess::startDetached(local_128,local_108,local_e8,(longlong *)0x0);
    QString::~QString(local_128);
    QList<QString>::~QList((QList<QString> *)local_108);
    this_00 = aQStack_48;
    while (this_00 != local_a8) {
      this_00 = this_00 + -0x18;
                    /* try { // try from 0026cbac to 0036cbb0 has its CatchHandler @ 0026d8a7 */
      QString::~QString(this_00);
    }
    QString::~QString(local_e8);
  }
                    /* try { // try from 0026cbca to 0036cbce has its CatchHandler @ 0026d893 */
  QString::~QString(local_148);
                    /* try { // try from 0026cbe0 to 0036cbe4 has its CatchHandler @ 0026d882 */
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0026cfa6  CalendarBackend::composeForHummingbird

/* CalendarBackend::composeForHummingbird(QString const&) */

undefined4 __thiscall CalendarBackend::composeForHummingbird(CalendarBackend *this,QString *param_1)

{
  char cVar1;
  undefined4 unaff_R12D;
  long in_FS_OFFSET;
  undefined8 local_d0;
  undefined8 local_c8;
  QVariant local_c0 [8];
  QList<QVariant> *local_b8;
  undefined8 local_b0;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
                    /* try { // try from 0026cfb8 to 0036cfbc has its CatchHandler @ 0026db4d */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 0026cfd1 to 0036cfd5 has its CatchHandler @ 0026d9ab */
  local_b8 = (QList<QVariant> *)(this + 0x28);
  local_d0 = QList<QVariant>::begin(local_b8);
  local_c8 = QList<QVariant>::end(local_b8);
                    /* try { // try from 0026d00f to 0036d013 has its CatchHandler @ 0026d9e7 */
                    /* try { // try from 0026d13d to 0036d141 has its CatchHandler @ 0026da12 */
  while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_d0,local_c8),
        cVar1 != '\0') {
    local_b0 = QList<QVariant>::iterator::operator*((iterator *)&local_d0);
                    /* try { // try from 0026d02d to 0036d031 has its CatchHandler @ 0026d9d3 */
    ::QVariant::toMap();
                    /* try { // try from 0026d043 to 0036d047 has its CatchHandler @ 0026d9c2 */
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"id");
    QMap<QString,QVariant>::value(local_48,local_c0);
    ::QVariant::toString();
    cVar1 = ::operator==(local_88,param_1);
                    /* try { // try from 0026d0b2 to 0036d0b6 has its CatchHandler @ 0026db4d */
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
                    /* try { // try from 0026d0cb to 0036d0cf has its CatchHandler @ 0026d9fb */
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    if (cVar1 != '\0') {
      unaff_R12D = composeForHummingbirdRec(this,(QMap *)local_c0);
                    /* try { // try from 0026d109 to 0036d10d has its CatchHandler @ 0026da37 */
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c0);
    if (cVar1 != '\0') goto LAB_0026d15a;
                    /* try { // try from 0026d127 to 0036d12b has its CatchHandler @ 0026da23 */
    QList<QVariant>::iterator::operator++((iterator *)&local_d0);
  }
  unaff_R12D = 0;
LAB_0026d15a:
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return unaff_R12D;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0026d1e6  CalendarBackend::composeForHummingbirdRec

/* CalendarBackend::composeForHummingbirdRec(QMap<QString, QVariant> const&) */

undefined4 __thiscall CalendarBackend::composeForHummingbirdRec(CalendarBackend *this,QMap *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  QString *this_00;
  long in_FS_OFFSET;
  undefined1 auVar6 [16];
  undefined8 local_280;
  QJsonObject aQStack_278 [8];
  wchar16 *local_270;
  QJsonValueRef aQStack_268 [16];
  QString local_258 [32];
  QString local_238 [32];
  QString local_218 [32];
  QString local_1f8 [32];
  QString local_1d8 [32];
  QString aQStack_1b8 [32];
  QString aQStack_198 [32];
  QString aQStack_178 [32];
  QString local_158 [32];
  undefined1 local_138 [2] [16];
  undefined8 local_118 [4];
  undefined4 local_f8 [8];
  QVariant local_d8 [32];
  QString local_b8 [32];
  QVariant local_98 [32];
  QString local_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
                    /* try { // try from 0026d203 to 0036d207 has its CatchHandler @ 0026da87 */
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 0026d221 to 0036d225 has its CatchHandler @ 0026da73 */
  ::QVariant::QVariant(local_d8);
                    /* try { // try from 0026d237 to 0036d23b has its CatchHandler @ 0026da62 */
  QString::QString(local_158,"title");
  QMap<QString,QVariant>::value(local_b8,(QVariant *)param_1);
  ::QVariant::toString();
  cVar1 = QString::isEmpty((QString *)local_138);
                    /* try { // try from 0026d2a6 to 0036d2aa has its CatchHandler @ 0026db4d */
  if (cVar1 == '\0') {
                    /* try { // try from 0026d2fd to 0036d301 has its CatchHandler @ 0026dad7 */
    ::QVariant::QVariant(local_98);
                    /* try { // try from 0026d31b to 0036d31f has its CatchHandler @ 0026dac3 */
    QString::QString((QString *)local_f8,"title");
                    /* try { // try from 0026d331 to 0036d335 has its CatchHandler @ 0026dab2 */
    QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_78);
    QString::~QString((QString *)local_f8);
                    /* try { // try from 0026d3a0 to 0036d3a4 has its CatchHandler @ 0026db4d */
    ::QVariant::~QVariant(local_98);
  }
  else {
    local_270 = L"Appointment";
                    /* try { // try from 0026d2bf to 0036d2c3 has its CatchHandler @ 0026da9b */
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"Appointment",0xb);
    QString::QString(local_258,(QArrayDataPointer *)local_118);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
  }
                    /* try { // try from 0026d3b9 to 0036d3bd has its CatchHandler @ 0026dae8 */
  QString::~QString((QString *)local_138);
  ::QVariant::~QVariant((QVariant *)local_b8);
  QString::~QString(local_158);
  ::QVariant::~QVariant(local_d8);
                    /* try { // try from 0026d3f7 to 0036d3fb has its CatchHandler @ 0026db21 */
  ::QVariant::QVariant(local_98);
                    /* try { // try from 0026d415 to 0036d419 has its CatchHandler @ 0026db0d */
  QString::QString((QString *)local_f8,"date");
                    /* try { // try from 0026d42b to 0036d42f has its CatchHandler @ 0026dafc */
  QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString((QString *)local_f8);
  ::QVariant::~QVariant(local_98);
  ::QVariant::QVariant(local_98);
  QString::QString((QString *)local_f8,"allDay");
  QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
  cVar1 = ::QVariant::toBool();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString((QString *)local_f8);
  ::QVariant::~QVariant(local_98);
  ::QVariant::QVariant(local_98);
                    /* try { // try from 0026d515 to 0036d599 has its CatchHandler @ 0026db4d */
  QString::QString((QString *)local_f8,"location");
  QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString((QString *)local_f8);
  ::QVariant::~QVariant(local_98);
  ::QVariant::QVariant(local_98);
                    /* try { // try from 0026d5b0 to 0036d5b4 has its CatchHandler @ 0026db32 */
  QString::QString((QString *)local_f8,"notes");
  QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
  ::QVariant::toString();
  ::QVariant::~QVariant((QVariant *)local_78);
  QString::~QString((QString *)local_f8);
  ::QVariant::~QVariant(local_98);
                    /* try { // try from 0026d62a to 0036d6b1 has its CatchHandler @ 0026db4d */
  QString::QString(local_1d8,local_238);
  QString::QString((QString *)local_f8,"yyyy-MM-dd");
  local_280 = QDate::fromString(local_238,(QString *)local_f8,0x76c);
  QString::~QString((QString *)local_f8);
  cVar2 = QDate::isValid((QDate *)&local_280);
  if (cVar2 != '\0') {
    QString::QString((QString *)local_118,"dddd, MMMM d, yyyy");
    QDate::toString((QString *)local_f8);
    QString::operator=(local_1d8,(QString *)local_f8);
    QString::~QString((QString *)local_f8);
    QString::~QString((QString *)local_118);
  }
  if (cVar1 == '\x01') {
    QString::operator+=(local_1d8,&UNK_002aea4b);
  }
  else {
    ::QVariant::QVariant(local_98);
    QString::QString((QString *)local_f8,"start");
    QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
    iVar3 = ::QVariant::toInt((bool *)local_78);
    ::QVariant::~QVariant((QVariant *)local_78);
    QString::~QString((QString *)local_f8);
    ::QVariant::~QVariant(local_98);
    ::QVariant::QVariant(local_98,iVar3);
    QString::QString((QString *)local_f8,"end");
    QMap<QString,QVariant>::value(local_78,(QVariant *)param_1);
    iVar4 = ::QVariant::toInt((bool *)local_78);
    ::QVariant::~QVariant((QVariant *)local_78);
    QString::~QString((QString *)local_f8);
    ::QVariant::~QVariant(local_98);
    if (iVar3 < iVar4) {
      hmFmtTime((int)local_138);
      ::operator+((char *)local_118,(QString *)&DAT_002aea3e);
    }
    else {
      QString::QString((QString *)local_118,"");
    }
    hmFmtTime((int)aQStack_178);
    ::operator+((char *)local_158,(QString *)&DAT_002aea44);
    ::operator+((QString *)local_f8,local_158);
    QString::operator+=(local_1d8,(QString *)local_f8);
    QString::~QString((QString *)local_f8);
    QString::~QString(local_158);
    QString::~QString(aQStack_178);
    QString::~QString((QString *)local_118);
    if (iVar3 < iVar4) {
      QString::~QString((QString *)local_138);
    }
  }
  QString::QString((QString *)local_138,&DAT_002aea59);
  cVar1 = QDate::isValid((QDate *)&local_280);
  if (cVar1 == '\0') {
    QString::QString((QString *)local_f8,local_238);
  }
  else {
    QString::QString((QString *)local_118,"MMM d");
    QDate::toString((QString *)local_f8);
  }
  QString::arg<QString_const&,QString_const>(aQStack_1b8,(QString *)local_138);
  QString::~QString((QString *)local_f8);
  if (cVar1 != '\0') {
    QString::~QString((QString *)local_118);
  }
  QString::~QString((QString *)local_138);
  QString::QString((QString *)local_f8,
                   "You have an appointment from the Leap Frog Ledger:\n\n  %1\n  %2\n");
  QString::arg<QString_const&,QString&>(aQStack_198,(QString *)local_f8);
  QString::~QString((QString *)local_f8);
  cVar1 = QString::isEmpty(local_218);
  if (cVar1 != '\x01') {
    QString::QString((QString *)local_118,"  Where: %1\n");
    QChar::QChar<char16_t,true>((QChar *)local_138,L' ');
    QString::arg<QString,true>(local_f8,local_118,local_218,0,local_138[0]._0_8_ & 0xffff);
    QString::operator+=(aQStack_198,(QString *)local_f8);
    QString::~QString((QString *)local_f8);
    QString::~QString((QString *)local_118);
  }
  cVar1 = QString::isEmpty(local_1f8);
  if (cVar1 != '\x01') {
    QString::QString((QString *)local_118,"\n%1\n");
    QChar::QChar<char16_t,true>((QChar *)local_138,L' ');
    QString::arg<QString,true>(local_f8,local_118,local_1f8,0,local_138[0]._0_2_);
    QString::operator+=(aQStack_198,(QString *)local_f8);
    QString::~QString((QString *)local_f8);
    QString::~QString((QString *)local_118);
  }
  QString::operator+=(aQStack_198,&DAT_002aeac8);
  QDir::homePath();
  ::operator+(aQStack_178,(char *)local_f8);
  QString::~QString((QString *)local_f8);
  QString::QString((QString *)local_f8);
  QDir::QDir((QDir *)local_138,(QString *)local_f8);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_118);
  QDir::mkpath(local_138,aQStack_178,local_118[0]);
  QDir::~QDir((QDir *)local_138);
  QString::~QString((QString *)local_f8);
  ::operator+(local_158,(char *)aQStack_178);
  QJsonObject::QJsonObject(aQStack_278);
  QJsonValue::QJsonValue((QJsonValue *)local_f8,true);
  QString::QString((QString *)local_118,"pending");
  local_138[0] = QJsonObject::operator[]((QString *)aQStack_278);
  QJsonValueRef::operator=((QJsonValueRef *)local_138,(QJsonValue *)local_f8);
  QString::~QString((QString *)local_118);
  QJsonValue::~QJsonValue((QJsonValue *)local_f8);
  QJsonValue::QJsonValue((QJsonValue *)local_f8,aQStack_1b8);
  QString::QString((QString *)local_118,"subject");
  auVar6 = QJsonObject::operator[]((QString *)aQStack_278);
  local_138[0] = auVar6;
  QJsonValueRef::operator=((QJsonValueRef *)local_138,(QJsonValue *)local_f8);
  QString::~QString((QString *)local_118);
  QJsonValue::~QJsonValue((QJsonValue *)local_f8);
  QJsonValue::QJsonValue((QJsonValue *)local_f8,aQStack_198);
  QString::QString((QString *)local_118,"body");
  auVar6 = QJsonObject::operator[]((QString *)aQStack_278);
  local_138[0] = auVar6;
  QJsonValueRef::operator=((QJsonValueRef *)local_138,(QJsonValue *)local_f8);
  QString::~QString((QString *)local_118);
  QJsonValue::~QJsonValue((QJsonValue *)local_f8);
  QString::QString((QString *)local_118);
  QJsonValue::QJsonValue((QJsonValue *)local_f8,(QString *)local_118);
  QString::QString((QString *)local_138,"attachPath");
  aQStack_268 = (QJsonValueRef  [16])QJsonObject::operator[]((QString *)aQStack_278);
  QJsonValueRef::operator=(aQStack_268,(QJsonValue *)local_f8);
  QString::~QString((QString *)local_138);
  QJsonValue::~QJsonValue((QJsonValue *)local_f8);
  QString::~QString((QString *)local_118);
  QFile::QFile((QFile *)aQStack_268,local_158);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_f8,2);
  cVar1 = QFile::open(aQStack_268,local_f8[0]);
  if (cVar1 == '\x01') {
    QJsonDocument::QJsonDocument((QJsonDocument *)local_118,aQStack_278);
    QJsonDocument::toJson(local_f8,local_118,1);
    QIODevice::write((QByteArray *)aQStack_268);
    QByteArray::~QByteArray((QByteArray *)local_f8);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_118);
    QFileDevice::close();
    QString::QString((QString *)local_f8);
    QString::QString(local_78,"--compose");
    QString::QString(aQStack_60,local_158);
    QList<QString>::QList(local_118,local_78,2);
    QString::QString((QString *)local_138,"hummingbird-courier");
    uVar5 = QProcess::startDetached
                      ((QString *)local_138,(QList *)local_118,(QString *)local_f8,(longlong *)0x0);
    QString::~QString((QString *)local_138);
    QList<QString>::~QList((QList<QString> *)local_118);
    this_00 = aQStack_48;
    while (this_00 != local_78) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QString::~QString((QString *)local_f8);
  }
  else {
    uVar5 = 0;
  }
  QFile::~QFile((QFile *)aQStack_268);
  QJsonObject::~QJsonObject(aQStack_278);
  QString::~QString(local_158);
  QString::~QString(aQStack_178);
  QString::~QString(aQStack_198);
  QString::~QString(aQStack_1b8);
  QString::~QString(local_1d8);
  QString::~QString(local_1f8);
  QString::~QString(local_218);
  QString::~QString(local_238);
  QString::~QString(local_258);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar5;
}



// ==== 0026f1ac  CalendarBackend::Snapshot::Snapshot

/* CalendarBackend::Snapshot::Snapshot(CalendarBackend::Snapshot&&) */

void __thiscall CalendarBackend::Snapshot::Snapshot(Snapshot *this,Snapshot *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
                    /* try { // try from 0026f1e8 to 0036f1ec has its CatchHandler @ 00270932 */
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x18),(QList *)(param_1 + 0x18));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x30),(QList *)(param_1 + 0x30));
  return;
}



// ==== 0027062a  CalendarBackend::Snapshot::operator=

/* CalendarBackend::Snapshot::TEMPNAMEPLACEHOLDERVALUE(CalendarBackend::Snapshot&&) */

Snapshot * __thiscall CalendarBackend::Snapshot::operator=(Snapshot *this,Snapshot *param_1)

{
  QString::operator=((QString *)this,(QString *)param_1);
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0x18),(QList *)(param_1 + 0x18));
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0x30),(QList *)(param_1 + 0x30));
  return this;
}



// ==== 00270aea  CalendarBackend::Snapshot::Snapshot

/* CalendarBackend::Snapshot::Snapshot(CalendarBackend::Snapshot const&) */

void __thiscall CalendarBackend::Snapshot::Snapshot(Snapshot *this,Snapshot *param_1)

{
                    /* catch() { ... } // from try @ 0026f798 with catch @ 00270b07 */
  QString::QString((QString *)this,(QString *)param_1);
                    /* catch() { ... } // from try @ 0026f762 with catch @ 00270b1b */
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x18),(QList *)(param_1 + 0x18));
                    /* catch() { ... } // from try @ 0026f41f with catch @ 00270b3e */
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x30),(QList *)(param_1 + 0x30));
  return;
}


