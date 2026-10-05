// Ghidra decompile of LaPivot.oracle — class/namespace WidgetData (74 functions). Raw; not source.

// ==== 0014ecf2  WidgetData::qt_static_metacall

/* WidgetData::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void WidgetData::qt_static_metacall
               (WidgetData *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  bool bVar1;
  QList<QVariant> QVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  undefined8 uVar4;
  QList local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0xe) {
      unmountVolume(param_1,*(QString **)(param_4 + 8));
    }
    else if (param_3 < 0xf) {
      if (param_3 == 0xd) {
        mountVolume(param_1,*(QString **)(param_4 + 8));
      }
      else if (param_3 < 0xe) {
        if (param_3 == 0xc) {
          mediaSeek(param_1,**(double **)(param_4 + 8));
        }
        else if (param_3 < 0xd) {
          if (param_3 == 0xb) {
            mediaPrev(param_1);
          }
          else if (param_3 < 0xc) {
            if (param_3 == 10) {
              mediaNext(param_1);
            }
            else if (param_3 < 0xb) {
              if (param_3 == 9) {
                mediaTogglePlay(param_1);
              }
              else if (param_3 < 10) {
                if (param_3 == 8) {
                  toggleMute(param_1);
                }
                else if (param_3 < 9) {
                  if (param_3 == 7) {
                    setVolume(param_1,**(int **)(param_4 + 8));
                  }
                  else if (param_3 < 8) {
                    if (param_3 == 6) {
                      mediaPositionChanged(param_1);
                    }
                    else if (param_3 < 7) {
                      if (param_3 == 5) {
                        mediaChanged(param_1);
                      }
                      else if (param_3 < 6) {
                        if (param_3 == 4) {
                          moonPositionChanged(param_1);
                        }
                        else if (param_3 < 5) {
                          if (param_3 == 3) {
                            weatherChanged(param_1);
                          }
                          else if (param_3 < 4) {
                            if (param_3 == 2) {
                              statsChanged(param_1);
                            }
                            else if (param_3 < 3) {
                              if (param_3 == 0) {
                                changed(param_1);
                              }
                              else if (param_3 == 1) {
                                clockChanged(param_1);
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
      ((((bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1 &&
         (bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)clockChanged,(_func_void *)0x0,1), !bVar1)) &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                           (param_4,(void **)statsChanged,(_func_void *)0x0,2), !bVar1)) &&
       (((bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)weatherChanged,(_func_void *)0x0,3), !bVar1 &&
         (bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)moonPositionChanged,(_func_void *)0x0,4), !bVar1)) &&
        ((bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)mediaChanged,(_func_void *)0x0,5), !bVar1 &&
         (bVar1 = QtMocHelpers::indexOfMethod<void(WidgetData::*)()>
                            (param_4,(void **)mediaPositionChanged,(_func_void *)0x0,6), !bVar1)))))
       ))) && (param_2 == 1)) {
    this = *(QList<QVariant> **)param_4;
    if (param_3 == 0x28) {
      uVar4 = moonElevation(param_1);
      *(undefined8 *)this = uVar4;
    }
    else if (param_3 < 0x29) {
      if (param_3 == 0x27) {
        uVar4 = moonAzimuth(param_1);
        *(undefined8 *)this = uVar4;
      }
      else if (param_3 < 0x28) {
        if (param_3 == 0x26) {
          weatherSunset();
          QString::operator=((QString *)this,(QString *)local_48);
          QString::~QString((QString *)local_48);
        }
        else if (param_3 < 0x27) {
          if (param_3 == 0x25) {
            weatherSunrise();
            QString::operator=((QString *)this,(QString *)local_48);
            QString::~QString((QString *)local_48);
          }
          else if (param_3 < 0x26) {
            if (param_3 == 0x24) {
              weatherWind();
              QString::operator=((QString *)this,(QString *)local_48);
              QString::~QString((QString *)local_48);
            }
            else if (param_3 < 0x25) {
              if (param_3 == 0x23) {
                weatherHumidity();
                QString::operator=((QString *)this,(QString *)local_48);
                QString::~QString((QString *)local_48);
              }
              else if (param_3 < 0x24) {
                if (param_3 == 0x22) {
                  weatherLow();
                  QString::operator=((QString *)this,(QString *)local_48);
                  QString::~QString((QString *)local_48);
                }
                else if (param_3 < 0x23) {
                  if (param_3 == 0x21) {
                    weatherHigh();
                    QString::operator=((QString *)this,(QString *)local_48);
                    QString::~QString((QString *)local_48);
                  }
                  else if (param_3 < 0x22) {
                    if (param_3 == 0x20) {
                      weatherLocation();
                      QString::operator=((QString *)this,(QString *)local_48);
                      QString::~QString((QString *)local_48);
                    }
                    else if (param_3 < 0x21) {
                      if (param_3 == 0x1f) {
                        weatherIcon();
                        QString::operator=((QString *)this,(QString *)local_48);
                        QString::~QString((QString *)local_48);
                      }
                      else if (param_3 < 0x20) {
                        if (param_3 == 0x1e) {
                          weatherTemp();
                          QString::operator=((QString *)this,(QString *)local_48);
                          QString::~QString((QString *)local_48);
                        }
                        else if (param_3 < 0x1f) {
                          if (param_3 == 0x1d) {
                            mountedVolumes();
                            QList<QVariant>::operator=(this,local_48);
                            QList<QVariant>::~QList((QList<QVariant> *)local_48);
                          }
                          else if (param_3 < 0x1e) {
                            if (param_3 == 0x1c) {
                              uptime();
                              QString::operator=((QString *)this,(QString *)local_48);
                              QString::~QString((QString *)local_48);
                            }
                            else if (param_3 < 0x1d) {
                              if (param_3 == 0x1b) {
                                uVar4 = cpuTempF(param_1);
                                *(undefined8 *)this = uVar4;
                              }
                              else if (param_3 < 0x1c) {
                                if (param_3 == 0x1a) {
                                  uVar4 = cpuFreqGHz(param_1);
                                  *(undefined8 *)this = uVar4;
                                }
                                else if (param_3 < 0x1b) {
                                  if (param_3 == 0x19) {
                                    uVar4 = diskPercent(param_1);
                                    *(undefined8 *)this = uVar4;
                                  }
                                  else if (param_3 < 0x1a) {
                                    if (param_3 == 0x18) {
                                      uVar4 = ramPercent(param_1);
                                      *(undefined8 *)this = uVar4;
                                    }
                                    else if (param_3 < 0x19) {
                                      if (param_3 == 0x17) {
                                        uVar4 = cpuTotal(param_1);
                                        *(undefined8 *)this = uVar4;
                                      }
                                      else if (param_3 < 0x18) {
                                        if (param_3 == 0x16) {
                                          dateString((WidgetData *)local_48);
                                          QString::operator=((QString *)this,(QString *)local_48);
                                          QString::~QString((QString *)local_48);
                                        }
                                        else if (param_3 < 0x17) {
                                          if (param_3 == 0x15) {
                                            greeting((WidgetData *)local_48);
                                            QString::operator=((QString *)this,(QString *)local_48);
                                            QString::~QString((QString *)local_48);
                                          }
                                          else if (param_3 < 0x16) {
                                            if (param_3 == 0x14) {
                                              QVar2 = (QList<QVariant>)colonOn(param_1);
                                              *this = QVar2;
                                            }
                                            else if (param_3 < 0x15) {
                                              if (param_3 == 0x13) {
                                                timeAMPM((WidgetData *)local_48);
                                                QString::operator=((QString *)this,
                                                                   (QString *)local_48);
                                                QString::~QString((QString *)local_48);
                                              }
                                              else if (param_3 < 0x14) {
                                                if (param_3 == 0x12) {
                                                  timeMinute((WidgetData *)local_48);
                                                  QString::operator=((QString *)this,
                                                                     (QString *)local_48);
                                                  QString::~QString((QString *)local_48);
                                                }
                                                else if (param_3 < 0x13) {
                                                  if (param_3 == 0x11) {
                                                    timeHour((WidgetData *)local_48);
                                                    QString::operator=((QString *)this,
                                                                       (QString *)local_48);
                                                    QString::~QString((QString *)local_48);
                                                  }
                                                  else if (param_3 < 0x12) {
                                                    if (param_3 == 0x10) {
                                                      uVar4 = mediaDuration(param_1);
                                                      *(undefined8 *)this = uVar4;
                                                    }
                                                    else if (param_3 < 0x11) {
                                                      if (param_3 == 0xf) {
                                                        uVar4 = mediaPosition(param_1);
                                                        *(undefined8 *)this = uVar4;
                                                      }
                                                      else if (param_3 < 0x10) {
                                                        if (param_3 == 0xe) {
                                                          mediaAlbum();
                                                          QString::operator=((QString *)this,
                                                                             (QString *)local_48);
                                                          QString::~QString((QString *)local_48);
                                                        }
                                                        else if (param_3 < 0xf) {
                                                          if (param_3 == 0xd) {
                                                            mediaArtist();
                                                            QString::operator=((QString *)this,
                                                                               (QString *)local_48);
                                                            QString::~QString((QString *)local_48);
                                                          }
                                                          else if (param_3 < 0xe) {
                                                            if (param_3 == 0xc) {
                                                              mediaTitle();
                                                              QString::operator=((QString *)this,
                                                                                 (QString *)local_48
                                                                                );
                                                              QString::~QString((QString *)local_48)
                                                              ;
                                                            }
                                                            else if (param_3 < 0xd) {
                                                              if (param_3 == 0xb) {
                                                                QVar2 = (QList<QVariant>)
                                                                        mediaPlaying(param_1);
                                                                *this = QVar2;
                                                              }
                                                              else if (param_3 < 0xc) {
                                                                if (param_3 == 10) {
                                                                  QVar2 = (QList<QVariant>)
                                                                          mediaActive(param_1);
                                                                  *this = QVar2;
                                                                }
                                                                else if (param_3 < 0xb) {
                                                                  if (param_3 == 9) {
                                                                    netDown();
                                                                    QString::operator=((QString *)
                                                                                       this,(QString
                                                                                             *)
                                                  local_48);
                                                  QString::~QString((QString *)local_48);
                                                  }
                                                  else if (param_3 < 10) {
                                                    if (param_3 == 8) {
                                                      netUp();
                                                      QString::operator=((QString *)this,
                                                                         (QString *)local_48);
                                                      QString::~QString((QString *)local_48);
                                                    }
                                                    else if (param_3 < 9) {
                                                      if (param_3 == 7) {
                                                        QVar2 = (QList<QVariant>)netOnline(param_1);
                                                        *this = QVar2;
                                                      }
                                                      else if (param_3 < 8) {
                                                        if (param_3 == 6) {
                                                          QVar2 = (QList<QVariant>)
                                                                  networkUp(param_1);
                                                          *this = QVar2;
                                                        }
                                                        else if (param_3 < 7) {
                                                          if (param_3 == 5) {
                                                            QVar2 = (QList<QVariant>)
                                                                    batteryCharging(param_1);
                                                            *this = QVar2;
                                                          }
                                                          else if (param_3 < 6) {
                                                            if (param_3 == 4) {
                                                              uVar3 = batteryLevel(param_1);
                                                              *(undefined4 *)this = uVar3;
                                                            }
                                                            else if (param_3 < 5) {
                                                              if (param_3 == 3) {
                                                                QVar2 = (QList<QVariant>)
                                                                        hasBattery(param_1);
                                                                *this = QVar2;
                                                              }
                                                              else if (param_3 < 4) {
                                                                if (param_3 == 2) {
                                                                  QVar2 = (QList<QVariant>)
                                                                          muted(param_1);
                                                                  *this = QVar2;
                                                                }
                                                                else if (param_3 < 3) {
                                                                  if (param_3 == 0) {
                                                                    removableVolumes();
                                                                    QList<QVariant>::operator=
                                                                              (this,local_48);
                                                                    QList<QVariant>::~QList
                                                                              ((QList<QVariant> *)
                                                                               local_48);
                                                                  }
                                                                  else if (param_3 == 1) {
                                                                    uVar3 = volume(param_1);
                                                                    *(undefined4 *)this = uVar3;
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
              }
            }
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



// ==== 0014fb0e  WidgetData::metaObject

/* WidgetData::metaObject() const */

undefined1 * __thiscall WidgetData::metaObject(WidgetData *this)

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



// ==== 0014fb56  WidgetData::qt_metacast

/* WidgetData::qt_metacast(char const*) */

WidgetData * __thiscall WidgetData::qt_metacast(WidgetData *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (WidgetData *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"WidgetData");
    if (iVar1 != 0) {
      this = (WidgetData *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014fbaa  WidgetData::qt_metacall

/* WidgetData::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
WidgetData::qt_metacall(WidgetData *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0xf) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0xf;
    }
    if (param_2 == 7) {
      if (local_28 < 0xf) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0xf;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -0x29;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014fca0  WidgetData::changed

/* WidgetData::changed() */

void __thiscall WidgetData::changed(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0014fccc  WidgetData::clockChanged

/* WidgetData::clockChanged() */

void __thiscall WidgetData::clockChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0014fcf8  WidgetData::statsChanged

/* WidgetData::statsChanged() */

void __thiscall WidgetData::statsChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 0014fd24  WidgetData::weatherChanged

/* WidgetData::weatherChanged() */

void __thiscall WidgetData::weatherChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,3,(void **)0x0);
  return;
}



// ==== 0014fd50  WidgetData::moonPositionChanged

/* WidgetData::moonPositionChanged() */

void __thiscall WidgetData::moonPositionChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,4,(void **)0x0);
  return;
}



// ==== 0014fd7c  WidgetData::mediaChanged

/* WidgetData::mediaChanged() */

void __thiscall WidgetData::mediaChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 0014fda8  WidgetData::mediaPositionChanged

/* WidgetData::mediaPositionChanged() */

void __thiscall WidgetData::mediaPositionChanged(WidgetData *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,6,(void **)0x0);
  return;
}



// ==== 001a2028  WidgetData::WidgetData

/* WidgetData::WidgetData(QObject*) */

void __thiscall WidgetData::WidgetData(WidgetData *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032ba80;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  QNetworkAccessManager::QNetworkAccessManager
            ((QNetworkAccessManager *)(this + 0x20),(QObject *)0x0);
  this[0x30] = (WidgetData)0x1;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  QString::QString((QString *)(this + 0x80));
  QString::QString((QString *)(this + 0x98));
  QString::QString((QString *)(this + 0xb0));
  QString::QString((QString *)(this + 200));
  QString::QString((QString *)(this + 0xe0));
  QString::QString((QString *)(this + 0xf8));
  QString::QString((QString *)(this + 0x110));
  QString::QString((QString *)(this + 0x128));
  QString::QString((QString *)(this + 0x140));
  QString::QString((QString *)(this + 0x158));
  QString::QString((QString *)(this + 0x170));
  QString::QString((QString *)(this + 0x188));
  *(undefined8 *)(this + 0x1a0) = 0;
  *(undefined8 *)(this + 0x1a8) = 0xc056800000000000;
  return;
}



// ==== 001a221c  WidgetData::removableVolumes

/* WidgetData::removableVolumes() const */

QList<QVariant> * WidgetData::removableVolumes(void)

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
    Lelan::removableVolumes();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a2298  WidgetData::volume

/* WidgetData::volume() const */

undefined8 __thiscall WidgetData::volume(WidgetData *this)

{
  undefined8 uVar1;
  
  if (*(long *)(this + 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = Lelan::volume(*(Lelan **)(this + 0x10));
  }
  return uVar1;
}



// ==== 001a22ca  WidgetData::muted

/* WidgetData::muted() const */

undefined8 __thiscall WidgetData::muted(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::muted(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a2306  WidgetData::hasBattery

/* WidgetData::hasBattery() const */

undefined8 __thiscall WidgetData::hasBattery(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::hasBattery(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a2342  WidgetData::batteryLevel

/* WidgetData::batteryLevel() const */

int __thiscall WidgetData::batteryLevel(WidgetData *this)

{
  int iVar1;
  double dVar2;
  
  if (*(long *)(this + 0x10) == 0) {
    iVar1 = 0;
  }
  else {
    dVar2 = (double)Lelan::batteryPercent(*(Lelan **)(this + 0x10));
    iVar1 = (int)dVar2;
  }
  return iVar1;
}



// ==== 001a2378  WidgetData::batteryCharging

/* WidgetData::batteryCharging() const */

undefined8 __thiscall WidgetData::batteryCharging(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::batteryCharging(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a23b4  WidgetData::networkUp

/* WidgetData::networkUp() const */

undefined8 __thiscall WidgetData::networkUp(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::networkUp(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a23f0  WidgetData::netOnline

/* WidgetData::netOnline() const */

undefined8 __thiscall WidgetData::netOnline(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::networkOnline(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a242c  WidgetData::netUp

/* WidgetData::netUp() const */

QString * WidgetData::netUp(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x98));
  return in_RDI;
}



// ==== 001a245c  WidgetData::netDown

/* WidgetData::netDown() const */

QString * WidgetData::netDown(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0xb0));
  return in_RDI;
}



// ==== 001a248c  WidgetData::mediaActive

/* WidgetData::mediaActive() const */

undefined8 __thiscall WidgetData::mediaActive(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) &&
     (cVar1 = Lelan::mediaActive(*(Lelan **)(this + 0x10)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a24c8  WidgetData::mediaPlaying

/* WidgetData::mediaPlaying() const */

undefined8 __thiscall WidgetData::mediaPlaying(WidgetData *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x10) != 0) && (cVar1 = Lelan::mediaPlaying(), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 001a2504  WidgetData::mediaTitle

/* WidgetData::mediaTitle() const */

Lelan * WidgetData::mediaTitle(void)

{
  long lVar1;
  long in_RSI;
  Lelan *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString((QString *)in_RDI);
  }
  else {
    Lelan::mediaTitle(in_RDI);
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a2570  WidgetData::mediaArtist

/* WidgetData::mediaArtist() const */

Lelan * WidgetData::mediaArtist(void)

{
  long lVar1;
  long in_RSI;
  Lelan *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString((QString *)in_RDI);
  }
  else {
    Lelan::mediaArtist(in_RDI);
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a25dc  WidgetData::mediaAlbum

/* WidgetData::mediaAlbum() const */

Lelan * WidgetData::mediaAlbum(void)

{
  long lVar1;
  long in_RSI;
  Lelan *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString((QString *)in_RDI);
  }
  else {
    Lelan::mediaAlbum(in_RDI);
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a2648  WidgetData::mediaPosition

/* WidgetData::mediaPosition() const */

double __thiscall WidgetData::mediaPosition(WidgetData *this)

{
  long lVar1;
  double dVar2;
  
  if (*(long *)(this + 0x10) == 0) {
    dVar2 = 0.0;
  }
  else {
    lVar1 = Lelan::mediaPosition();
    dVar2 = (double)lVar1;
  }
  return dVar2;
}



// ==== 001a2682  WidgetData::mediaDuration

/* WidgetData::mediaDuration() const */

double __thiscall WidgetData::mediaDuration(WidgetData *this)

{
  long lVar1;
  double dVar2;
  
  if (*(long *)(this + 0x10) == 0) {
    dVar2 = 0.0;
  }
  else {
    lVar1 = Lelan::mediaDuration();
    dVar2 = (double)lVar1;
  }
  return dVar2;
}



// ==== 001a26bc  WidgetData::timeHour

/* WidgetData::timeHour() const */

WidgetData * __thiscall WidgetData::timeHour(WidgetData *this)

{
  long lVar1;
  int iVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  QTime::currentTime();
  iVar2 = QTime::hour();
  iVar2 = iVar2 + ((iVar2 / 6 + (iVar2 >> 0x1f) >> 1) - (iVar2 >> 0x1f)) * -0xc;
  if (iVar2 == 0) {
    iVar2 = 0xc;
  }
  QString::number((int)this,iVar2);
  if (lVar1 == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a275a  WidgetData::timeMinute

/* WidgetData::timeMinute() const */

WidgetData * __thiscall WidgetData::timeMinute(WidgetData *this)

{
  long in_FS_OFFSET;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QTime::currentTime();
  QString::QString(local_38,"mm");
  QTime::toString((QString *)this);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a280c  WidgetData::timeAMPM

/* WidgetData::timeAMPM() const */

WidgetData * __thiscall WidgetData::timeAMPM(WidgetData *this)

{
  long in_FS_OFFSET;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QTime::currentTime();
  QString::QString(local_38,"AP");
  QTime::toString((QString *)this);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a28be  WidgetData::colonOn

/* WidgetData::colonOn() const */

WidgetData __thiscall WidgetData::colonOn(WidgetData *this)

{
  return this[0x30];
}



// ==== 001a28d0  WidgetData::greeting

/* WidgetData::greeting() const */

WidgetData * __thiscall WidgetData::greeting(WidgetData *this)

{
  long lVar1;
  int iVar2;
  char *pcVar3;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  QTime::currentTime();
  iVar2 = QTime::hour();
  if (iVar2 < 0xc) {
    pcVar3 = "Good morning";
  }
  else if (iVar2 < 0x12) {
    pcVar3 = "Good afternoon";
  }
  else {
    pcVar3 = "Good evening";
  }
  QString::QString((QString *)this,pcVar3);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a2954  WidgetData::dateString

/* WidgetData::dateString() const */

WidgetData * __thiscall WidgetData::dateString(WidgetData *this)

{
  long in_FS_OFFSET;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDate::currentDate();
  QString::QString(local_38,"dddd, MMMM d");
  QDate::toString((QString *)this);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a2a06  WidgetData::cpuTotal

/* WidgetData::cpuTotal() const */

undefined8 __thiscall WidgetData::cpuTotal(WidgetData *this)

{
  return *(undefined8 *)(this + 0x38);
}



// ==== 001a2a1a  WidgetData::ramPercent

/* WidgetData::ramPercent() const */

undefined8 __thiscall WidgetData::ramPercent(WidgetData *this)

{
  return *(undefined8 *)(this + 0x40);
}



// ==== 001a2a2e  WidgetData::diskPercent

/* WidgetData::diskPercent() const */

undefined8 __thiscall WidgetData::diskPercent(WidgetData *this)

{
  return *(undefined8 *)(this + 0x48);
}



// ==== 001a2a42  WidgetData::cpuFreqGHz

/* WidgetData::cpuFreqGHz() const */

undefined8 __thiscall WidgetData::cpuFreqGHz(WidgetData *this)

{
  return *(undefined8 *)(this + 0x50);
}



// ==== 001a2a56  WidgetData::cpuTempF

/* WidgetData::cpuTempF() const */

undefined8 __thiscall WidgetData::cpuTempF(WidgetData *this)

{
  return *(undefined8 *)(this + 0x58);
}



// ==== 001a2a6a  WidgetData::uptime

/* WidgetData::uptime() const */

QString * WidgetData::uptime(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x80));
  return in_RDI;
}



// ==== 001a2a9a  WidgetData::mountedVolumes

/* WidgetData::mountedVolumes() const */

QList<QVariant> * WidgetData::mountedVolumes(void)

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
    Lelan::removableVolumes();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a2b16  WidgetData::weatherTemp

/* WidgetData::weatherTemp() const */

QString * WidgetData::weatherTemp(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 200));
  return in_RDI;
}



// ==== 001a2b46  WidgetData::weatherIcon

/* WidgetData::weatherIcon() const */

QString * WidgetData::weatherIcon(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0xe0));
  return in_RDI;
}



// ==== 001a2b76  WidgetData::weatherLocation

/* WidgetData::weatherLocation() const */

QString * WidgetData::weatherLocation(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0xf8));
  return in_RDI;
}



// ==== 001a2ba6  WidgetData::weatherHigh

/* WidgetData::weatherHigh() const */

QString * WidgetData::weatherHigh(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x110));
  return in_RDI;
}



// ==== 001a2bd6  WidgetData::weatherLow

/* WidgetData::weatherLow() const */

QString * WidgetData::weatherLow(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x128));
  return in_RDI;
}



// ==== 001a2c06  WidgetData::weatherHumidity

/* WidgetData::weatherHumidity() const */

QString * WidgetData::weatherHumidity(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x140));
  return in_RDI;
}



// ==== 001a2c36  WidgetData::weatherWind

/* WidgetData::weatherWind() const */

QString * WidgetData::weatherWind(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x158));
  return in_RDI;
}



// ==== 001a2c66  WidgetData::weatherSunrise

/* WidgetData::weatherSunrise() const */

QString * WidgetData::weatherSunrise(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x170));
  return in_RDI;
}



// ==== 001a2c96  WidgetData::weatherSunset

/* WidgetData::weatherSunset() const */

QString * WidgetData::weatherSunset(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x188));
  return in_RDI;
}



// ==== 001a2cc6  WidgetData::moonAzimuth

/* WidgetData::moonAzimuth() const */

undefined8 __thiscall WidgetData::moonAzimuth(WidgetData *this)

{
  return *(undefined8 *)(this + 0x1a0);
}



// ==== 001a2cdc  WidgetData::moonElevation

/* WidgetData::moonElevation() const */

undefined8 __thiscall WidgetData::moonElevation(WidgetData *this)

{
  return *(undefined8 *)(this + 0x1a8);
}



// ==== 001a2cf2  WidgetData::setVolume

/* WidgetData::setVolume(int) */

void __thiscall WidgetData::setVolume(WidgetData *this,int param_1)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::setVolume(*(Lelan **)(this + 0x10),param_1);
  }
  return;
}



// ==== 001a2d26  WidgetData::toggleMute

/* WidgetData::toggleMute() */

void __thiscall WidgetData::toggleMute(WidgetData *this)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::toggleMute(*(Lelan **)(this + 0x10));
  }
  return;
}



// ==== 001a2d52  WidgetData::mediaTogglePlay

/* WidgetData::mediaTogglePlay() */

void __thiscall WidgetData::mediaTogglePlay(WidgetData *this)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::mediaPlayPause(*(Lelan **)(this + 0x10));
  }
  return;
}



// ==== 001a2d7e  WidgetData::mediaNext

/* WidgetData::mediaNext() */

void __thiscall WidgetData::mediaNext(WidgetData *this)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::mediaNext(*(Lelan **)(this + 0x10));
  }
  return;
}



// ==== 001a2daa  WidgetData::mediaPrev

/* WidgetData::mediaPrev() */

void __thiscall WidgetData::mediaPrev(WidgetData *this)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::mediaPrevious(*(Lelan **)(this + 0x10));
  }
  return;
}



// ==== 001a2dd6  WidgetData::mediaSeek

/* WidgetData::mediaSeek(double) */

void __thiscall WidgetData::mediaSeek(WidgetData *this,double param_1)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::mediaSeek(*(Lelan **)(this + 0x10),(long)param_1);
  }
  return;
}



// ==== 001a2e14  WidgetData::mountVolume

/* WidgetData::mountVolume(QString const&) */

void __thiscall WidgetData::mountVolume(WidgetData *this,QString *param_1)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::mountVolume(*(Lelan **)(this + 0x10),param_1);
  }
  return;
}



// ==== 001a2e4c  WidgetData::unmountVolume

/* WidgetData::unmountVolume(QString const&) */

void __thiscall WidgetData::unmountVolume(WidgetData *this,QString *param_1)

{
  if (*(long *)(this + 0x10) != 0) {
    Lelan::unmountVolume(*(Lelan **)(this + 0x10),param_1);
  }
  return;
}



// ==== 001a2f5c  WidgetData::~WidgetData

/* WidgetData::~WidgetData() */

void __thiscall WidgetData::~WidgetData(WidgetData *this)

{
  *(undefined ***)this = &PTR_metaObject_0032ba80;
  QString::~QString((QString *)(this + 0x188));
  QString::~QString((QString *)(this + 0x170));
  QString::~QString((QString *)(this + 0x158));
  QString::~QString((QString *)(this + 0x140));
  QString::~QString((QString *)(this + 0x128));
  QString::~QString((QString *)(this + 0x110));
  QString::~QString((QString *)(this + 0xf8));
  QString::~QString((QString *)(this + 0xe0));
  QString::~QString((QString *)(this + 200));
  QString::~QString((QString *)(this + 0xb0));
  QString::~QString((QString *)(this + 0x98));
  QString::~QString((QString *)(this + 0x80));
  QNetworkAccessManager::~QNetworkAccessManager((QNetworkAccessManager *)(this + 0x20));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a306c  WidgetData::~WidgetData

/* WidgetData::~WidgetData() */

void __thiscall WidgetData::~WidgetData(WidgetData *this)

{
  ~WidgetData(this);
  operator_delete(this,0x1b0);
  return;
}



// ==== 001f909e  WidgetData::setAnimPolicy

/* WidgetData::setAnimPolicy(AnimPolicy*) */

void __thiscall WidgetData::setAnimPolicy(WidgetData *this,AnimPolicy *param_1)

{
  *(AnimPolicy **)(this + 0x18) = param_1;
  return;
}



// ==== 001f90ba  WidgetData::setLelan

/* WidgetData::setLelan(Lelan*) */

void __thiscall WidgetData::setLelan(WidgetData *this,Lelan *param_1)

{
  long in_FS_OFFSET;
  Connection local_60 [8];
  code *local_58;
  undefined8 uStack_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  *(Lelan **)(this + 0x10) = param_1;
  if (param_1 != (Lelan *)0x0) {
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::storageChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::onAudioVolumeUpdated,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::batteryChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = changed;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::networkChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = mediaChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::mediaChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = mediaPositionChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(WidgetData::*)()>
              (local_60,param_1,Lelan::mediaPositionChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = onPulse;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(unsigned_long_long),void(WidgetData::*)(unsigned_long_long)>
              (local_60,param_1,Lelan::pulse,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f9458  WidgetData::onPulse

/* WidgetData::onPulse(unsigned long long) */

void __thiscall WidgetData::onPulse(WidgetData *this,ulonglong param_1)

{
  bool bVar1;
  char cVar2;
  ulong uVar3;
  
  this[0x30] = (WidgetData)((byte)this[0x30] ^ 1);
  clockChanged(this);
  if (*(long *)(this + 0x18) == 0) {
LAB_001f94c3:
    bVar1 = true;
  }
  else {
    cVar2 = AnimPolicy::screenIdle(*(AnimPolicy **)(this + 0x18));
    if (cVar2 != '\x01') {
      cVar2 = AnimPolicy::desktopObscured(*(AnimPolicy **)(this + 0x18));
      if (cVar2 != '\x01') goto LAB_001f94c3;
    }
    bVar1 = false;
  }
  if (bVar1) {
    uVar3 = param_1 % 3;
  }
  else {
    uVar3 = param_1 % 0x3c;
  }
  if (uVar3 == 0) {
    readStats(this);
  }
  if ((param_1 == 5) || (param_1 % 0x708 == 0)) {
    fetchWeather(this);
  }
  return;
}



// ==== 001f9588  WidgetData::readFile

/* WidgetData::readFile(QString const&) */

WidgetData * __thiscall WidgetData::readFile(WidgetData *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined4 local_4c;
  QFile local_48 [16];
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QFile::QFile(local_48,param_1);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)&local_4c,1);
  cVar1 = QFile::open(local_48,local_4c);
  if (cVar1 == '\0') {
    QString::QString((QString *)this);
  }
  else {
    QIODevice::readAll();
    QString::fromUtf8<void>((QString *)this,local_38);
    QByteArray::~QByteArray(local_38);
  }
  QFile::~QFile(local_48);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001f96a8  WidgetData::readStats

/* WidgetData::readStats() */

void __thiscall WidgetData::readStats(WidgetData *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  long lVar9;
  QString *pQVar10;
  bool *pbVar11;
  long lVar12;
  long in_FS_OFFSET;
  double dVar13;
  undefined2 local_264;
  undefined2 local_262;
  undefined4 local_260;
  int local_25c;
  int local_258;
  int local_254;
  int local_250;
  int local_24c;
  int local_248;
  int local_244;
  undefined4 local_240 [2];
  long local_238;
  ulong local_230;
  long local_228;
  double local_220;
  long local_218;
  long local_210;
  long local_208;
  ulong local_200;
  long local_1f8;
  QList<QString> *local_1f0;
  double local_1e8;
  double local_1e0;
  double local_1d8;
  QList<QString> *local_1d0;
  QString *local_1c8;
  undefined8 local_1c0;
  QList<QString> local_1b8 [32];
  undefined4 local_198 [8];
  ulong local_178 [4];
  ulong local_158 [4];
  undefined4 local_138 [8];
  char *local_118 [4];
  char *local_f8 [4];
  char *local_d8 [4];
  statvfs local_b8;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)local_138,"/proc/stat");
  readFile((WidgetData *)local_118,(QString *)local_138);
  QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)local_178,0);
  QChar::QChar<char,true>((QChar *)local_240,'\n');
  QString::section(local_f8,local_118,(undefined2)local_240[0],0,0,(undefined4)local_178[0]);
  QString::simplified((QString *)local_d8);
  QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_158,0);
  QChar::QChar<char,true>((QChar *)local_198,' ');
  QString::split(local_1b8,local_d8,(undefined2)local_198[0],local_158[0] & 0xffffffff,1);
  QString::~QString((QString *)local_d8);
  QString::~QString((QString *)local_f8);
  QString::~QString((QString *)local_118);
  QString::~QString((QString *)local_138);
  lVar9 = QList<QString>::size(local_1b8);
  if (4 < lVar9) {
    local_d8[0] = "cpu";
    pQVar10 = (QString *)QList<QString>::operator[](local_1b8,0);
    cVar7 = ::operator==(pQVar10,local_d8);
    if (cVar7 != '\0') {
      bVar1 = true;
      goto LAB_001f985f;
    }
  }
  bVar1 = false;
LAB_001f985f:
  if (bVar1) {
    pQVar10 = (QString *)QList<QString>::operator[](local_1b8,4);
    local_208 = QString::toULongLong(pQVar10,(bool *)0x0,10);
    local_238 = 0;
    for (local_25c = 1; lVar12 = (long)local_25c, lVar9 = QList<QString>::size(local_1b8),
        lVar12 < lVar9; local_25c = local_25c + 1) {
      pQVar10 = (QString *)QList<QString>::operator[](local_1b8,(long)local_25c);
      lVar9 = QString::toULongLong(pQVar10,(bool *)0x0,10);
      local_238 = local_238 + lVar9;
    }
    local_200 = local_238 - *(long *)(this + 0x60);
    local_1f8 = local_208 - *(long *)(this + 0x68);
    if ((local_200 != 0) && (*(long *)(this + 0x60) != 0)) {
      *(double *)(this + 0x38) = ((double)(local_200 - local_1f8) * 100.0) / (double)local_200;
    }
    *(long *)(this + 0x60) = local_238;
    *(long *)(this + 0x68) = local_208;
  }
  local_230 = 0;
  local_228 = 0;
  QString::QString((QString *)local_f8,"/proc/meminfo");
  readFile((WidgetData *)local_d8,(QString *)local_f8);
  QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_138,0);
  QChar::QChar<char,true>((QChar *)local_158,'\n');
  QString::split(local_118,local_d8,local_158[0] & 0xffff,local_138[0],1);
  local_1f0 = (QList<QString> *)local_118;
  QString::~QString((QString *)local_d8);
  QString::~QString((QString *)local_f8);
  local_178[0] = QList<QString>::begin(local_1f0);
  local_158[0] = QList<QString>::end(local_1f0);
  while (cVar7 = QList<QString>::iterator::operator!=((iterator *)local_178,local_158[0]),
        cVar7 != '\0') {
    local_1c0 = QList<QString>::iterator::operator*((iterator *)local_178);
    QString::QString((QString *)local_d8,"MemTotal:");
    cVar7 = QString::startsWith(local_1c0,local_d8,1);
    QString::~QString((QString *)local_d8);
    if (cVar7 != '\0') {
      QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_198,0);
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_240,0);
      QString::QString((QString *)local_f8,"\\s+");
      QRegularExpression::QRegularExpression((QRegularExpression *)local_138,local_f8,local_240[0]);
      QString::split(local_d8,local_1c0,local_138,local_198[0]);
      pQVar10 = (QString *)QList<QString>::operator[]((QList<QString> *)local_d8,1);
      local_230 = QString::toULongLong(pQVar10,(bool *)0x0,10);
      QList<QString>::~QList((QList<QString> *)local_d8);
      QRegularExpression::~QRegularExpression((QRegularExpression *)local_138);
      QString::~QString((QString *)local_f8);
    }
    QString::QString((QString *)local_d8,"MemAvailable:");
    cVar7 = QString::startsWith(local_1c0,local_d8,1);
    QString::~QString((QString *)local_d8);
    if (cVar7 != '\0') {
      QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_198,0);
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_240,0);
      QString::QString((QString *)local_f8,"\\s+");
      QRegularExpression::QRegularExpression((QRegularExpression *)local_138,local_f8,local_240[0]);
      QString::split(local_d8,local_1c0,local_138,local_198[0]);
      pQVar10 = (QString *)QList<QString>::operator[]((QList<QString> *)local_d8,1);
      local_228 = QString::toULongLong(pQVar10,(bool *)0x0,10);
      QList<QString>::~QList((QList<QString> *)local_d8);
      QRegularExpression::~QRegularExpression((QRegularExpression *)local_138);
      QString::~QString((QString *)local_f8);
    }
    QList<QString>::iterator::operator++((iterator *)local_178);
  }
  QList<QString>::~QList((QList<QString> *)local_118);
  if (local_230 != 0) {
    *(double *)(this + 0x40) = ((double)(local_230 - local_228) * 100.0) / (double)local_230;
  }
  iVar8 = statvfs("/",&local_b8);
  if ((iVar8 == 0) && (local_b8.f_blocks != 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    *(double *)(this + 0x48) =
         ((double)(local_b8.f_blocks - local_b8.f_bfree) * 100.0) / (double)local_b8.f_blocks;
  }
  QString::QString((QString *)local_f8,"/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
  readFile((WidgetData *)local_d8,(QString *)local_f8);
  QString::trimmed((QString *)local_198);
  QString::~QString((QString *)local_d8);
  QString::~QString((QString *)local_f8);
  cVar7 = QString::isEmpty((QString *)local_198);
  if (cVar7 != '\0') {
    QString::QString((QString *)local_118,"/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq");
    readFile((WidgetData *)local_f8,(QString *)local_118);
    QString::trimmed((QString *)local_d8);
    QString::operator=((QString *)local_198,(QString *)local_d8);
    QString::~QString((QString *)local_d8);
    QString::~QString((QString *)local_f8);
    QString::~QString((QString *)local_118);
  }
  cVar7 = QString::isEmpty((QString *)local_198);
  if (cVar7 != '\x01') {
    dVar13 = (double)QString::toDouble((bool *)local_198);
    *(double *)(this + 0x50) = dVar13 / 1000000.0;
  }
  local_220 = -1000000000.0;
  if (*(long *)(this + 0x10) != 0) {
    Lelan::sentinelTemps();
    local_178[0] = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)local_240);
    while( true ) {
      local_d8[0] = (char *)QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)local_240);
      cVar7 = ::operator!=((const_iterator *)local_178,(const_iterator *)local_d8);
      if (cVar7 == '\0') break;
      QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_178);
      QString::toLower((QString *)local_158);
      bVar2 = false;
      bVar1 = false;
      QString::QString((QString *)local_118,"package");
      cVar7 = QString::contains((QString *)local_158,local_118,1);
      if (cVar7 == '\0') {
        QString::QString((QString *)local_f8,"tctl");
        bVar2 = true;
        cVar7 = QString::contains((QString *)local_158,local_f8,1);
        if (cVar7 != '\0') goto LAB_001fa1b6;
        QString::QString((QString *)local_d8,"tdie");
        bVar1 = true;
        cVar7 = QString::contains((QString *)local_158,local_d8,1);
        if (cVar7 != '\0') goto LAB_001fa1b6;
        bVar5 = false;
      }
      else {
LAB_001fa1b6:
        bVar5 = true;
      }
      if (bVar1) {
        QString::~QString((QString *)local_d8);
      }
      if (bVar2) {
        QString::~QString((QString *)local_f8);
      }
      QString::~QString((QString *)local_118);
      bVar4 = false;
      bVar3 = false;
      bVar2 = false;
      bVar1 = false;
      if (bVar5) {
LAB_001fa332:
        bVar6 = true;
      }
      else {
        QString::QString((QString *)local_138,"coretemp");
        bVar4 = true;
        cVar7 = QString::startsWith(local_158,local_138,1);
        if (cVar7 != '\0') goto LAB_001fa332;
        QString::QString((QString *)local_118,"k10temp");
        bVar3 = true;
        cVar7 = QString::startsWith(local_158,local_118,1);
        if (cVar7 != '\0') goto LAB_001fa332;
        QString::QString((QString *)local_f8,"zenpower");
        bVar2 = true;
        cVar7 = QString::startsWith(local_158,local_f8,1);
        if (cVar7 != '\0') goto LAB_001fa332;
        QString::QString((QString *)local_d8,"cpu");
        bVar1 = true;
        cVar7 = QString::contains((QString *)local_158,local_d8,1);
        if (cVar7 != '\0') goto LAB_001fa332;
        bVar6 = false;
      }
      if (bVar1) {
        QString::~QString((QString *)local_d8);
      }
      if (bVar2) {
        QString::~QString((QString *)local_f8);
      }
      if (bVar3) {
        QString::~QString((QString *)local_118);
      }
      if (bVar4) {
        QString::~QString((QString *)local_138);
      }
      if (bVar6) {
        pbVar11 = (bool *)QMap<QString,QVariant>::const_iterator::value((const_iterator *)local_178)
        ;
        local_1e8 = (double)::QVariant::toDouble(pbVar11);
        if (0.0 < local_1e8) {
          if (bVar5) {
            iVar8 = 1;
            local_220 = local_1e8;
          }
          else {
            if (local_220 < local_1e8) {
              local_220 = local_1e8;
            }
            iVar8 = 2;
          }
        }
        else {
          iVar8 = 0;
        }
      }
      else {
        iVar8 = 0;
      }
      QString::~QString((QString *)local_158);
      if ((iVar8 != 0) && (iVar8 != 2)) break;
      QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_178);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_240);
  }
  if (local_220 < -100000000.0) {
    local_258 = -1;
    for (local_254 = 0; local_254 < 0x10; local_254 = local_254 + 1) {
      QString::QString((QString *)local_d8,"/sys/class/thermal/thermal_zone%1/");
      QChar::QChar<char16_t,true>((QChar *)local_f8,L' ');
      QString::arg<int,true>(local_178,local_d8,local_254,0,10,(ulong)local_f8[0] & 0xffff);
      QString::~QString((QString *)local_d8);
      ::operator+((QString *)local_f8,(char *)local_178);
      readFile((WidgetData *)local_d8,(QString *)local_f8);
      QString::trimmed((QString *)local_158);
      QString::~QString((QString *)local_d8);
      QString::~QString((QString *)local_f8);
      cVar7 = QString::isEmpty((QString *)local_158);
      if (cVar7 == '\0') {
        local_1e0 = (double)QString::toDouble((bool *)local_158);
        local_1e0 = local_1e0 / 1000.0;
        if (0.0 < local_1e0) {
          ::operator+((QString *)local_118,(char *)local_178);
          readFile((WidgetData *)local_f8,(QString *)local_118);
          QString::trimmed((QString *)local_d8);
          QString::toLower((QString *)local_138);
          QString::~QString((QString *)local_d8);
          QString::~QString((QString *)local_f8);
          QString::~QString((QString *)local_118);
          bVar1 = false;
          local_118[0] = "x86_pkg_temp";
          cVar7 = ::operator==((QString *)local_138,local_118);
          if (cVar7 == '\x01') {
LAB_001fa764:
            local_250 = 2;
          }
          else {
            local_f8[0] = "tcpu";
            cVar7 = ::operator==((QString *)local_138,local_f8);
            if (cVar7 == '\x01') goto LAB_001fa764;
            QString::QString((QString *)local_d8,"cpu");
            bVar1 = true;
            cVar7 = QString::contains((QString *)local_138,local_d8,1);
            if (cVar7 == '\0') {
              local_250 = 0;
            }
            else {
              local_250 = 1;
            }
          }
          if (bVar1) {
            QString::~QString((QString *)local_d8);
          }
          if (local_258 < local_250) {
            local_258 = local_250;
            local_220 = local_1e0;
            if (local_250 != 2) goto LAB_001fa7bb;
            bVar1 = false;
          }
          else {
LAB_001fa7bb:
            bVar1 = true;
          }
          QString::~QString((QString *)local_138);
          if (bVar1) {
            iVar8 = 2;
          }
          else {
            iVar8 = 1;
          }
        }
        else {
          iVar8 = 0;
        }
      }
      else {
        iVar8 = 0;
      }
      QString::~QString((QString *)local_158);
      if (iVar8 == 0) {
        iVar8 = 0;
      }
      else if (iVar8 == 2) {
        iVar8 = 2;
      }
      else {
        iVar8 = 1;
      }
      QString::~QString((QString *)local_178);
      if ((iVar8 != 0) && (iVar8 != 2)) break;
    }
  }
  if (-100000000.0 < local_220) {
    *(double *)(this + 0x58) = (local_220 * 9.0) / 5.0 + 32.0;
  }
  QString::QString((QString *)local_118,"/proc/uptime");
  readFile((WidgetData *)local_f8,(QString *)local_118);
  QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)local_138,0);
  QChar::QChar<char,true>((QChar *)local_158,' ');
  QString::section(local_d8,local_f8,local_158[0] & 0xffff,0,0,local_138[0]);
  local_1d8 = (double)QString::toDouble((bool *)local_d8);
  QString::~QString((QString *)local_d8);
  QString::~QString((QString *)local_f8);
  QString::~QString((QString *)local_118);
  if (0.0 < local_1d8) {
    local_24c = (int)local_1d8 / 0x15180;
    local_248 = ((int)local_1d8 % 0x15180) / 0xe10;
    local_244 = ((int)local_1d8 % 0xe10) / 0x3c;
    bVar1 = local_24c < 1;
    if (bVar1) {
      QString::QString((QString *)local_118,"%1h %2m");
      QChar::QChar<char16_t,true>((QChar *)local_240,L' ');
      QString::arg<int,true>(local_f8,local_118,local_248,0,10,(undefined2)local_240[0]);
      QChar::QChar<char16_t,true>((QChar *)local_178,L' ');
      QString::arg<int,true>(local_d8,local_f8,local_244,0,10,local_178[0] & 0xffff);
    }
    else {
      QString::QString((QString *)local_158,"%1d %2h");
      QChar::QChar<char16_t,true>((QChar *)&local_262,L' ');
      QString::arg<int,true>(local_138,local_158,local_24c,0,10,local_262);
      QChar::QChar<char16_t,true>((QChar *)&local_260,L' ');
      QString::arg<int,true>(local_d8,local_138,local_248,0,10,(undefined2)local_260);
    }
    QString::operator=((QString *)(this + 0x80),(QString *)local_d8);
    QString::~QString((QString *)local_d8);
    if (bVar1) {
      QString::~QString((QString *)local_f8);
      QString::~QString((QString *)local_118);
    }
    else {
      QString::~QString((QString *)local_138);
      QString::~QString((QString *)local_158);
    }
  }
  local_218 = 0;
  local_210 = 0;
  QString::QString((QString *)local_f8,"/proc/net/dev");
  readFile((WidgetData *)local_d8,(QString *)local_f8);
  QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_118,0);
  QChar::QChar<char,true>((QChar *)local_158,'\n');
  QString::split(local_138,local_d8,local_158[0] & 0xffff,(ulong)local_118[0] & 0xffffffff,1);
  local_1d0 = (QList<QString> *)local_138;
  QString::~QString((QString *)local_d8);
  QString::~QString((QString *)local_f8);
  local_178[0] = QList<QString>::begin(local_1d0);
  local_158[0] = QList<QString>::end(local_1d0);
  do {
    cVar7 = QList<QString>::iterator::operator!=((iterator *)local_178,local_158[0]);
    if (cVar7 == '\0') {
      QList<QString>::~QList((QList<QString> *)local_138);
      if (*(long *)(this + 0x70) != 0) {
        fmtRate((WidgetData *)local_d8,(double)(ulong)(local_218 - *(long *)(this + 0x70)) / 3.0);
        QString::operator=((QString *)(this + 0xb0),(QString *)local_d8);
        QString::~QString((QString *)local_d8);
        fmtRate((WidgetData *)local_d8,(double)(ulong)(local_210 - *(long *)(this + 0x78)) / 3.0);
        QString::operator=((QString *)(this + 0x98),(QString *)local_d8);
        QString::~QString((QString *)local_d8);
      }
      *(long *)(this + 0x70) = local_218;
      *(long *)(this + 0x78) = local_210;
      statsChanged(this);
      QString::~QString((QString *)local_198);
      QList<QString>::~QList(local_1b8);
      if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_1c8 = (QString *)QList<QString>::iterator::operator*((iterator *)local_178);
    bVar1 = false;
    QChar::QChar<char,true>((QChar *)local_f8,':');
    cVar7 = QString::contains(local_1c8,(ulong)local_f8[0] & 0xffff,1);
    if (cVar7 == '\x01') {
      QString::QString((QString *)local_d8,"lo:");
      bVar1 = true;
      cVar7 = QString::contains(local_1c8,local_d8,1);
      if (cVar7 != '\0') goto LAB_001fadce;
      bVar2 = false;
    }
    else {
LAB_001fadce:
      bVar2 = true;
    }
    if (bVar1) {
      QString::~QString((QString *)local_d8);
    }
    if (!bVar2) {
      QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)&local_260,0);
      QChar::QChar<char,true>((QChar *)&local_264,':');
      QString::section(local_f8,local_1c8,local_264,1,0xffffffffffffffff,local_260);
      QString::simplified((QString *)local_d8);
      QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_240,0);
      QChar::QChar<char,true>((QChar *)&local_262,' ');
      QString::split(local_118,local_d8,local_262,local_240[0],1);
      QString::~QString((QString *)local_d8);
      QString::~QString((QString *)local_f8);
      lVar9 = QList<QString>::size((QList<QString> *)local_118);
      if (8 < lVar9) {
        pQVar10 = (QString *)QList<QString>::operator[]((QList<QString> *)local_118,0);
        lVar9 = QString::toULongLong(pQVar10,(bool *)0x0,10);
        local_218 = local_218 + lVar9;
        pQVar10 = (QString *)QList<QString>::operator[]((QList<QString> *)local_118,8);
        lVar9 = QString::toULongLong(pQVar10,(bool *)0x0,10);
        local_210 = local_210 + lVar9;
      }
      QList<QString>::~QList((QList<QString> *)local_118);
    }
    QList<QString>::iterator::operator++((iterator *)local_178);
  } while( true );
}



// ==== 001fb61d  WidgetData::fmtRate

/* WidgetData::fmtRate(double) */

WidgetData * __thiscall WidgetData::fmtRate(WidgetData *this,double param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  long in_FS_OFFSET;
  QString local_88 [32];
  QString local_68 [32];
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  bVar3 = false;
  bVar2 = false;
  bVar1 = false;
  if (param_1 <= 1000000.0) {
    if (param_1 <= 1000.0) {
      QString::number(param_1,(char)local_48,0x66);
      bVar1 = true;
      ::operator+((QString *)this,(char *)local_48);
    }
    else {
      QString::number(param_1 / 1000.0,(char)local_68,0x66);
      bVar2 = true;
      ::operator+((QString *)this,(char *)local_68);
    }
  }
  else {
    QString::number(param_1 / 1000000.0,(char)local_88,0x66);
    bVar3 = true;
    ::operator+((QString *)this,(char *)local_88);
  }
  if (bVar1) {
    QString::~QString(local_48);
  }
  if (bVar2) {
    QString::~QString(local_68);
  }
  if (bVar3) {
    QString::~QString(local_88);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001fb830  WidgetData::fetchWeather()::{lambda()#1}::operator()

/* WidgetData::fetchWeather()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall WidgetData::fetchWeather()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  onWeather(*(QNetworkReply **)this);
  QObject::deleteLater();
  return;
}



// ==== 001fb86a  WidgetData::fetchWeather

/* WidgetData::fetchWeather() */

void __thiscall WidgetData::fetchWeather(WidgetData *this)

{
  long in_FS_OFFSET;
  undefined2 local_102;
  QVariant local_100 [8];
  undefined2 local_f8 [4];
  double local_f0;
  double local_e8;
  undefined8 local_e0;
  QString local_d8 [32];
  QString local_b8 [32];
  WidgetData *local_98;
  undefined8 local_90;
  QVariant local_78 [32];
  QString local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    Lelan::location();
    ::QVariant::QVariant(local_78);
    QString::QString((QString *)&local_98,"lat");
    QMap<QString,QVariant>::value(local_58,local_100);
    local_f0 = (double)::QVariant::toDouble((bool *)local_58);
    ::QVariant::~QVariant((QVariant *)local_58);
    QString::~QString((QString *)&local_98);
    ::QVariant::~QVariant(local_78);
    ::QVariant::QVariant(local_78);
    QString::QString((QString *)&local_98,"lon");
    QMap<QString,QVariant>::value(local_58,local_100);
    local_e8 = (double)::QVariant::toDouble((bool *)local_58);
    ::QVariant::~QVariant((QVariant *)local_58);
    QString::~QString((QString *)&local_98);
    ::QVariant::~QVariant(local_78);
    if ((local_f0 == 0.0) && (local_e8 == 0.0)) {
      local_f0 = 40.1;
      local_e8 = -89.2;
    }
    QString::QString(local_b8,
                     "https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset&temperature_unit=fahrenheit&wind_speed_unit=mph&timezone=auto"
                    );
    QChar::QChar<char16_t,true>((QChar *)&local_102,L' ');
    QString::arg<double,true>(local_f0,&local_98,local_b8,0,0x67,0xffffffff,local_102);
    QChar::QChar<char16_t,true>((QChar *)local_f8,L' ');
    QString::arg<double,true>(local_e8,local_d8,&local_98,0,0x67,0xffffffff,local_f8[0]);
    QString::~QString((QString *)&local_98);
    QString::~QString(local_b8);
    QUrl::QUrl((QUrl *)&local_98,local_d8,0);
    QNetworkRequest::QNetworkRequest((QNetworkRequest *)local_f8,(QUrl *)&local_98);
    QUrl::~QUrl((QUrl *)&local_98);
    ::QVariant::QVariant((QVariant *)local_58,"ncde/1.0");
    QNetworkRequest::setHeader(local_f8,7,local_58);
    ::QVariant::~QVariant((QVariant *)local_58);
    local_e0 = QNetworkAccessManager::get((QNetworkRequest *)(this + 0x20));
    local_98 = this;
    local_90 = local_e0;
    QObject::connect<void(QNetworkReply::*)(),WidgetData::fetchWeather()::_lambda()_1_>
              (local_b8,local_e0,QNetworkReply::finished,0,this,&local_98,0);
    QMetaObject::Connection::~Connection((Connection *)local_b8);
    Lelan::placeName();
    QString::operator=((QString *)(this + 0xf8),(QString *)&local_98);
    QString::~QString((QString *)&local_98);
    QNetworkRequest::~QNetworkRequest((QNetworkRequest *)local_f8);
    QString::~QString(local_d8);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_100);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fbdcb  WidgetData::wmoToYahooCode

/* WidgetData::wmoToYahooCode(int) */

undefined8 WidgetData::wmoToYahooCode(int param_1)

{
  undefined8 uVar1;
  
  if (param_1 == 99) {
LAB_001fbfba:
    uVar1 = 4;
  }
  else {
    if ((param_1 < 100) && (param_1 < 0x61)) {
      if (0x5e < param_1) goto LAB_001fbfba;
      if (param_1 < 0x57) {
        if (0x54 < param_1) {
          return 0x2e;
        }
        if (param_1 < 0x53) {
          if (0x4f < param_1) {
            return 0x28;
          }
          if (param_1 == 0x4d) {
            return 0xd;
          }
          if (param_1 < 0x4e) {
            if (param_1 == 0x4b) {
              return 0x10;
            }
            if (param_1 < 0x4c) {
              if (param_1 == 0x49) {
                return 0x10;
              }
              if (param_1 < 0x4a) {
                if (param_1 == 0x47) {
                  return 0x10;
                }
                if ((param_1 < 0x48) && (param_1 < 0x44)) {
                  if (0x41 < param_1) {
                    return 10;
                  }
                  if (param_1 == 0x41) {
                    return 0xc;
                  }
                  if (param_1 < 0x42) {
                    if (param_1 == 0x3f) {
                      return 0xc;
                    }
                    if (param_1 < 0x40) {
                      if (param_1 == 0x3d) {
                        return 0xb;
                      }
                      if ((param_1 < 0x3e) && (param_1 < 0x3a)) {
                        if (0x37 < param_1) {
                          return 8;
                        }
                        if (param_1 == 0x37) {
                          return 9;
                        }
                        if (param_1 < 0x38) {
                          if (param_1 == 0x35) {
                            return 9;
                          }
                          if (param_1 < 0x36) {
                            if (param_1 == 0x33) {
                              return 9;
                            }
                            if (param_1 < 0x34) {
                              if (param_1 == 0x30) {
                                return 0x14;
                              }
                              if (param_1 < 0x31) {
                                if (param_1 == 0x2d) {
                                  return 0x14;
                                }
                                if (param_1 < 0x2e) {
                                  if (param_1 == 3) {
                                    return 0x1a;
                                  }
                                  if (param_1 < 4) {
                                    if (param_1 == 2) {
                                      return 0x1e;
                                    }
                                    if (param_1 < 3) {
                                      if (param_1 == 0) {
                                        return 0x20;
                                      }
                                      if (param_1 == 1) {
                                        return 0x22;
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
    }
    uVar1 = 0x1a;
  }
  return uVar1;
}



// ==== 001fbfc8  WidgetData::onWeather(QNetworkReply*)::{lambda(char_const*)#1}::operator()

/* WidgetData::onWeather(QNetworkReply*)::{lambda(char const*)#1}::TEMPNAMEPLACEHOLDERVALUE(char
   const*) const */

_lambda_char_const___1_ * __thiscall
WidgetData::onWeather(QNetworkReply*)::{lambda(char_const*)#1}::operator()
          (_lambda_char_const___1_ *this,char *param_1)

{
  char cVar1;
  char *in_RDX;
  long in_FS_OFFSET;
  QJsonArray local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_98,in_RDX);
  QJsonObject::value(local_78);
  QJsonValue::toArray();
  QJsonValue::~QJsonValue((QJsonValue *)local_78);
  QString::~QString(local_98);
  cVar1 = QJsonArray::isEmpty();
  if (cVar1 == '\0') {
    QJsonArray::first();
    QJsonValue::toVariant();
    ::QVariant::toString();
    ::QVariant::~QVariant(local_58);
    QJsonValue::~QJsonValue((QJsonValue *)local_78);
  }
  else {
    QString::QString((QString *)this);
  }
  QJsonArray::~QJsonArray(local_a0);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001fc1e2  WidgetData::onWeather

/* WidgetData::onWeather(QNetworkReply*) */

void WidgetData::onWeather(QNetworkReply *param_1)

{
  char cVar1;
  int iVar2;
  QDebug *this;
  long in_FS_OFFSET;
  double dVar3;
  undefined2 local_d2;
  QJsonObject local_d0 [8];
  QJsonObject local_c8 [8];
  QJsonObject local_c0 [8];
  QJsonObject *local_b8;
  QJsonArray local_b0 [8];
  QString local_a8 [32];
  undefined4 local_88 [8];
  QString local_68 [32];
  QMessageLogger local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iVar2 = QNetworkReply::error();
  if (iVar2 == 0) {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_68,(QJsonParseError *)local_48);
    QJsonDocument::object();
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_68);
    QByteArray::~QByteArray((QByteArray *)local_48);
    QString::QString(local_68,"current");
    QJsonObject::value((QString *)local_48);
    QJsonValue::toObject();
    QJsonValue::~QJsonValue((QJsonValue *)local_48);
    QString::~QString(local_68);
    QString::QString(local_a8,"temperature_2m");
    QJsonObject::value((QString *)local_88);
    dVar3 = (double)QJsonValue::toDouble(0.0);
    iVar2 = qRound(dVar3);
    QString::number((int)local_68,iVar2);
    ::operator+((QString *)local_48,(char *)local_68);
    QString::operator=((QString *)(param_1 + 200),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_68);
    QJsonValue::~QJsonValue((QJsonValue *)local_88);
    QString::~QString(local_a8);
    QString::QString(local_a8,"relative_humidity_2m");
    QJsonObject::value((QString *)local_88);
    iVar2 = QJsonValue::toInt((int)local_88);
    QString::number((int)local_68,iVar2);
    ::operator+((QString *)local_48,(char *)local_68);
    QString::operator=((QString *)(param_1 + 0x140),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_68);
    QJsonValue::~QJsonValue((QJsonValue *)local_88);
    QString::~QString(local_a8);
    QString::QString(local_a8,"wind_speed_10m");
    QJsonObject::value((QString *)local_88);
    dVar3 = (double)QJsonValue::toDouble(0.0);
    iVar2 = qRound(dVar3);
    QString::number((int)local_68,iVar2);
    ::operator+((QString *)local_48,(char *)local_68);
    QString::operator=((QString *)(param_1 + 0x158),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_68);
    QJsonValue::~QJsonValue((QJsonValue *)local_88);
    QString::~QString(local_a8);
    QString::QString((QString *)local_88,"weather_code");
    QJsonObject::value(local_68);
    iVar2 = QJsonValue::toInt((int)local_68);
    iVar2 = wmoToYahooCode(iVar2);
    QString::number((int)local_48,iVar2);
    QString::operator=((QString *)(param_1 + 0xe0),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QJsonValue::~QJsonValue((QJsonValue *)local_68);
    QString::~QString((QString *)local_88);
    QString::QString(local_68,"daily");
    QJsonObject::value((QString *)local_48);
    QJsonValue::toObject();
    QJsonValue::~QJsonValue((QJsonValue *)local_48);
    QString::~QString(local_68);
    local_b8 = local_c0;
    QString::QString(local_68,"temperature_2m_max");
    QJsonObject::value((QString *)local_48);
    QJsonValue::toArray();
    QJsonValue::~QJsonValue((QJsonValue *)local_48);
    QString::~QString(local_68);
    QString::QString(local_68,"temperature_2m_min");
    QJsonObject::value((QString *)local_48);
    QJsonValue::toArray();
    QJsonValue::~QJsonValue((QJsonValue *)local_48);
    QString::~QString(local_68);
    cVar1 = QJsonArray::isEmpty();
    if (cVar1 != '\x01') {
      QJsonArray::first();
      dVar3 = (double)QJsonValue::toDouble(0.0);
      iVar2 = qRound(dVar3);
      QString::number((int)local_68,iVar2);
      ::operator+((QString *)local_48,(char *)local_68);
      QString::operator=((QString *)(param_1 + 0x110),(QString *)local_48);
      QString::~QString((QString *)local_48);
      QString::~QString(local_68);
      QJsonValue::~QJsonValue((QJsonValue *)local_88);
    }
    cVar1 = QJsonArray::isEmpty();
    if (cVar1 != '\x01') {
      QJsonArray::first();
      dVar3 = (double)QJsonValue::toDouble(0.0);
      iVar2 = qRound(dVar3);
      QString::number((int)local_68,iVar2);
      ::operator+((QString *)local_48,(char *)local_68);
      QString::operator=((QString *)(param_1 + 0x128),(QString *)local_48);
      QString::~QString((QString *)local_48);
      QString::~QString(local_68);
      QJsonValue::~QJsonValue((QJsonValue *)local_88);
    }
    onWeather(QNetworkReply*)::{lambda(char_const*)#1}::operator()
              ((_lambda_char_const___1_ *)local_68,(char *)&local_b8);
    QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)local_88,0);
    QChar::QChar<char,true>((QChar *)&local_d2,'T');
    QString::section(local_48,local_68,local_d2,1,1,local_88[0]);
    QString::operator=((QString *)(param_1 + 0x170),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_68);
    onWeather(QNetworkReply*)::{lambda(char_const*)#1}::operator()
              ((_lambda_char_const___1_ *)local_68,(char *)&local_b8);
    QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)local_88,0);
    QChar::QChar<char,true>((QChar *)&local_d2,'T');
    QString::section(local_48,local_68,local_d2,1,1,local_88[0]);
    QString::operator=((QString *)(param_1 + 0x188),(QString *)local_48);
    QString::~QString((QString *)local_48);
    QString::~QString(local_68);
    weatherChanged((WidgetData *)param_1);
    QJsonArray::~QJsonArray((QJsonArray *)local_a8);
    QJsonArray::~QJsonArray(local_b0);
    QJsonObject::~QJsonObject(local_c0);
    QJsonObject::~QJsonObject(local_c8);
    QJsonObject::~QJsonObject(local_d0);
  }
  else {
    QMessageLogger::QMessageLogger(local_48,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    this = (QDebug *)QDebug::operator<<((QDebug *)local_88,"WidgetData: weather fetch failed:");
    QIODevice::errorString();
    QDebug::operator<<(this,local_68);
    QString::~QString(local_68);
    QDebug::~QDebug((QDebug *)local_88);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


