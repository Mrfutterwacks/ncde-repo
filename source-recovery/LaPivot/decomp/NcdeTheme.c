// Ghidra decompile of LaPivot.oracle — class/namespace NcdeTheme (75 functions). Raw; not source.

// ==== 0014710a  NcdeTheme::qt_static_metacall

/* NcdeTheme::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NcdeTheme::qt_static_metacall(NcdeTheme *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QString *this;
  bool bVar1;
  QString QVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  undefined1 auVar5 [16];
  NcdeTheme local_68 [32];
  undefined6 local_48;
  undefined2 uStack_42;
  undefined6 local_40;
  undefined2 uStack_3a;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0x1e) {
      setAppVolume(param_1,*(QString **)(param_4 + 8),**(int **)(param_4 + 0x10));
    }
    else if (param_3 < 0x1f) {
      if (param_3 == 0x1d) {
        removePrinter(param_1,*(QString **)(param_4 + 8));
      }
      else if (param_3 < 0x1e) {
        if (param_3 == 0x1c) {
          setDefaultPrinter(param_1,*(QString **)(param_4 + 8));
        }
        else if (param_3 < 0x1d) {
          if (param_3 == 0x1b) {
            setUserAvatar(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10));
          }
          else if (param_3 < 0x1c) {
            if (param_3 == 0x1a) {
              setAutoLogin(param_1,*(QString **)(param_4 + 8));
            }
            else if (param_3 < 0x1b) {
              if (param_3 == 0x19) {
                changePassword((QString *)param_1,*(QString **)(param_4 + 8));
              }
              else if (param_3 < 0x1a) {
                if (param_3 == 0x18) {
                  setUserAdmin(param_1,*(QString **)(param_4 + 8),
                               *(bool *)*(undefined8 *)(param_4 + 0x10));
                }
                else if (param_3 < 0x19) {
                  if (param_3 == 0x17) {
                    removeUser(param_1,*(QString **)(param_4 + 8));
                  }
                  else if (param_3 < 0x18) {
                    if (param_3 == 0x16) {
                      addUser(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10),
                              *(bool *)*(undefined8 *)(param_4 + 0x18));
                    }
                    else if (param_3 < 0x17) {
                      if (param_3 == 0x15) {
                        setNtp(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                      }
                      else if (param_3 < 0x16) {
                        if (param_3 == 0x14) {
                          setTimezone(param_1,*(QString **)(param_4 + 8));
                        }
                        else if (param_3 < 0x15) {
                          if (param_3 == 0x13) {
                            refreshLocation(param_1);
                          }
                          else if (param_3 < 0x14) {
                            if (param_3 == 0x12) {
                              bluetoothScan(param_1);
                            }
                            else if (param_3 < 0x13) {
                              if (param_3 == 0x11) {
                                bluetoothRemove((QString *)param_1);
                              }
                              else if (param_3 < 0x12) {
                                if (param_3 == 0x10) {
                                  bluetoothPair((QString *)param_1);
                                }
                                else if (param_3 < 0x11) {
                                  if (param_3 == 0xf) {
                                    bluetoothDisconnect((QString *)param_1);
                                  }
                                  else if (param_3 < 0x10) {
                                    if (param_3 == 0xe) {
                                      bluetoothConnect((QString *)param_1);
                                    }
                                    else if (param_3 < 0xf) {
                                      if (param_3 == 0xd) {
                                        setBluetoothDiscoverable
                                                  (param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                                      }
                                      else if (param_3 < 0xe) {
                                        if (param_3 == 0xc) {
                                          setBluetoothEnabled(param_1,*(bool *)*(undefined8 *)
                                                                                (param_4 + 8));
                                        }
                                        else if (param_3 < 0xd) {
                                          if (param_3 == 0xb) {
                                            disconnectVpn(param_1,*(QString **)(param_4 + 8));
                                          }
                                          else if (param_3 < 0xc) {
                                            if (param_3 == 10) {
                                              connectVpn((QString *)param_1);
                                            }
                                            else if (param_3 < 0xb) {
                                              if (param_3 == 9) {
                                                disconnectNetwork(param_1);
                                              }
                                              else if (param_3 < 10) {
                                                if (param_3 == 8) {
                                                  connectNetwork(param_1,*(QString **)(param_4 + 8),
                                                                 *(QString **)(param_4 + 0x10));
                                                }
                                                else if (param_3 < 9) {
                                                  if (param_3 == 7) {
                                                    setWifiEnabled(param_1,*(bool *)*(undefined8 *)
                                                                                     (param_4 + 8));
                                                  }
                                                  else if (param_3 < 8) {
                                                    if (param_3 == 6) {
                                                      applyPalette(param_1,*(QMap **)(param_4 + 8));
                                                    }
                                                    else if (param_3 < 7) {
                                                      if (param_3 == 5) {
                                                        soundChanged(param_1);
                                                      }
                                                      else if (param_3 < 6) {
                                                        if (param_3 == 4) {
                                                          printersChanged(param_1);
                                                        }
                                                        else if (param_3 < 5) {
                                                          if (param_3 == 3) {
                                                            usersChanged(param_1);
                                                          }
                                                          else if (param_3 < 4) {
                                                            if (param_3 == 2) {
                                                              dateTimeChanged(param_1);
                                                            }
                                                            else if (param_3 < 3) {
                                                              if (param_3 == 0) {
                                                                changed(param_1);
                                                              }
                                                              else if (param_3 == 1) {
                                                                wifiChanged(param_1);
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
  if (((param_2 != 5) ||
      ((((bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                            (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1 &&
         (bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                            (param_4,(void **)wifiChanged,(_func_void *)0x0,1), !bVar1)) &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                           (param_4,(void **)dateTimeChanged,(_func_void *)0x0,2), !bVar1)) &&
       (((bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                            (param_4,(void **)usersChanged,(_func_void *)0x0,3), !bVar1 &&
         (bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                            (param_4,(void **)printersChanged,(_func_void *)0x0,4), !bVar1)) &&
        (bVar1 = QtMocHelpers::indexOfMethod<void(NcdeTheme::*)()>
                           (param_4,(void **)soundChanged,(_func_void *)0x0,5), !bVar1)))))) &&
     (param_2 == 1)) {
    this = *(QString **)param_4;
    if (param_3 == 0x23) {
      uVar3 = letterSpacing(param_1);
      *(undefined4 *)this = uVar3;
    }
    else if (param_3 < 0x24) {
      if (param_3 == 0x22) {
        appStreams();
        QList<QVariant>::operator=((QList<QVariant> *)this,(QList *)local_68);
        QList<QVariant>::~QList((QList<QVariant> *)local_68);
      }
      else if (param_3 < 0x23) {
        if (param_3 == 0x21) {
          printers();
          QList<QVariant>::operator=((QList<QVariant> *)this,(QList *)local_68);
          QList<QVariant>::~QList((QList<QVariant> *)local_68);
        }
        else if (param_3 < 0x22) {
          if (param_3 == 0x20) {
            users();
            QList<QVariant>::operator=((QList<QVariant> *)this,(QList *)local_68);
            QList<QVariant>::~QList((QList<QVariant> *)local_68);
          }
          else if (param_3 < 0x21) {
            if (param_3 == 0x1f) {
              QVar2 = (QString)locating();
              *this = QVar2;
            }
            else if (param_3 < 0x20) {
              if (param_3 == 0x1e) {
                localTime(local_68);
                QString::operator=(this,(QString *)local_68);
                QString::~QString((QString *)local_68);
              }
              else if (param_3 < 0x1f) {
                if (param_3 == 0x1d) {
                  detectedOffset();
                  QString::operator=(this,(QString *)local_68);
                  QString::~QString((QString *)local_68);
                }
                else if (param_3 < 0x1e) {
                  if (param_3 == 0x1c) {
                    detectedRegion();
                    QString::operator=(this,(QString *)local_68);
                    QString::~QString((QString *)local_68);
                  }
                  else if (param_3 < 0x1d) {
                    if (param_3 == 0x1b) {
                      detectedZone(local_68);
                      QString::operator=(this,(QString *)local_68);
                      QString::~QString((QString *)local_68);
                    }
                    else if (param_3 < 0x1c) {
                      if (param_3 == 0x1a) {
                        detectedTzName();
                        QString::operator=(this,(QString *)local_68);
                        QString::~QString((QString *)local_68);
                      }
                      else if (param_3 < 0x1b) {
                        if (param_3 == 0x19) {
                          bluetoothDevices();
                          QList<QVariant>::operator=((QList<QVariant> *)this,(QList *)local_68);
                          QList<QVariant>::~QList((QList<QVariant> *)local_68);
                        }
                        else if (param_3 < 0x1a) {
                          if (param_3 == 0x18) {
                            QVar2 = (QString)bluetoothDiscoverable(param_1);
                            *this = QVar2;
                          }
                          else if (param_3 < 0x19) {
                            if (param_3 == 0x17) {
                              QVar2 = (QString)bluetoothEnabled(param_1);
                              *this = QVar2;
                            }
                            else if (param_3 < 0x18) {
                              if (param_3 == 0x16) {
                                vpnConnections();
                                QList<QVariant>::operator=
                                          ((QList<QVariant> *)this,(QList *)local_68);
                                QList<QVariant>::~QList((QList<QVariant> *)local_68);
                              }
                              else if (param_3 < 0x17) {
                                if (param_3 == 0x15) {
                                  activeNetwork();
                                  QMap<QString,QVariant>::operator=
                                            ((QMap<QString,QVariant> *)this,(QMap *)local_68);
                                  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
                                }
                                else if (param_3 < 0x16) {
                                  if (param_3 == 0x14) {
                                    wifiNetworks();
                                    QList<QVariant>::operator=
                                              ((QList<QVariant> *)this,(QList *)local_68);
                                    QList<QVariant>::~QList((QList<QVariant> *)local_68);
                                  }
                                  else if (param_3 < 0x15) {
                                    if (param_3 == 0x13) {
                                      QVar2 = (QString)wifiEnabled(param_1);
                                      *this = QVar2;
                                    }
                                    else if (param_3 < 0x14) {
                                      if (param_3 == 0x12) {
                                        uVar4 = kickassGuard(param_1);
                                        *(undefined8 *)this = uVar4;
                                      }
                                      else if (param_3 < 0x13) {
                                        if (param_3 == 0x11) {
                                          auVar5 = wine();
                                          local_48 = auVar5._0_6_;
                                          uStack_42 = auVar5._6_2_;
                                          local_40 = auVar5._8_6_;
                                          uStack_3a = auVar5._14_2_;
                                          *(long *)this = auVar5._0_8_;
                                          *(long *)(this + 6) = auVar5._6_8_;
                                        }
                                        else if (param_3 < 0x12) {
                                          if (param_3 == 0x10) {
                                            widgetStyle();
                                            QString::operator=(this,(QString *)local_68);
                                            QString::~QString((QString *)local_68);
                                          }
                                          else if (param_3 < 0x11) {
                                            if (param_3 == 0xf) {
                                              version(local_68);
                                              QString::operator=(this,(QString *)local_68);
                                              QString::~QString((QString *)local_68);
                                            }
                                            else if (param_3 < 0x10) {
                                              if (param_3 == 0xe) {
                                                auVar5 = verd();
                                                local_48 = auVar5._0_6_;
                                                uStack_42 = auVar5._6_2_;
                                                local_40 = auVar5._8_6_;
                                                uStack_3a = auVar5._14_2_;
                                                *(long *)this = auVar5._0_8_;
                                                *(long *)(this + 6) = auVar5._6_8_;
                                              }
                                              else if (param_3 < 0xf) {
                                                if (param_3 == 0xd) {
                                                  auVar5 = surfaceGlass();
                                                  local_48 = auVar5._0_6_;
                                                  uStack_42 = auVar5._6_2_;
                                                  local_40 = auVar5._8_6_;
                                                  uStack_3a = auVar5._14_2_;
                                                  *(long *)this = auVar5._0_8_;
                                                  *(long *)(this + 6) = auVar5._6_8_;
                                                }
                                                else if (param_3 < 0xe) {
                                                  if (param_3 == 0xc) {
                                                    auVar5 = surfaceAlt();
                                                    local_48 = auVar5._0_6_;
                                                    uStack_42 = auVar5._6_2_;
                                                    local_40 = auVar5._8_6_;
                                                    uStack_3a = auVar5._14_2_;
                                                    *(long *)this = auVar5._0_8_;
                                                    *(long *)(this + 6) = auVar5._6_8_;
                                                  }
                                                  else if (param_3 < 0xd) {
                                                    if (param_3 == 0xb) {
                                                      auVar5 = surface();
                                                      local_48 = auVar5._0_6_;
                                                      uStack_42 = auVar5._6_2_;
                                                      local_40 = auVar5._8_6_;
                                                      uStack_3a = auVar5._14_2_;
                                                      *(long *)this = auVar5._0_8_;
                                                      *(long *)(this + 6) = auVar5._6_8_;
                                                    }
                                                    else if (param_3 < 0xc) {
                                                      if (param_3 == 10) {
                                                        QVar2 = (QString)presetActive(param_1);
                                                        *this = QVar2;
                                                      }
                                                      else if (param_3 < 0xb) {
                                                        if (param_3 == 9) {
                                                          auVar5 = popupBg();
                                                          local_48 = auVar5._0_6_;
                                                          uStack_42 = auVar5._6_2_;
                                                          local_40 = auVar5._8_6_;
                                                          uStack_3a = auVar5._14_2_;
                                                          *(long *)this = auVar5._0_8_;
                                                          *(long *)(this + 6) = auVar5._6_8_;
                                                        }
                                                        else if (param_3 < 10) {
                                                          if (param_3 == 8) {
                                                            auVar5 = panelBg();
                                                            local_48 = auVar5._0_6_;
                                                            uStack_42 = auVar5._6_2_;
                                                            local_40 = auVar5._8_6_;
                                                            uStack_3a = auVar5._14_2_;
                                                            *(long *)this = auVar5._0_8_;
                                                            *(long *)(this + 6) = auVar5._6_8_;
                                                          }
                                                          else if (param_3 < 9) {
                                                            if (param_3 == 7) {
                                                              auVar5 = glow();
                                                              local_48 = auVar5._0_6_;
                                                              uStack_42 = auVar5._6_2_;
                                                              local_40 = auVar5._8_6_;
                                                              uStack_3a = auVar5._14_2_;
                                                              *(long *)this = auVar5._0_8_;
                                                              *(long *)(this + 6) = auVar5._6_8_;
                                                            }
                                                            else if (param_3 < 8) {
                                                              if (param_3 == 6) {
                                                                auVar5 = gilt();
                                                                local_48 = auVar5._0_6_;
                                                                uStack_42 = auVar5._6_2_;
                                                                local_40 = auVar5._8_6_;
                                                                uStack_3a = auVar5._14_2_;
                                                                *(long *)this = auVar5._0_8_;
                                                                *(long *)(this + 6) = auVar5._6_8_;
                                                              }
                                                              else if (param_3 < 7) {
                                                                if (param_3 == 5) {
                                                                  auVar5 = foreground();
                                                                  local_48 = auVar5._0_6_;
                                                                  uStack_42 = auVar5._6_2_;
                                                                  local_40 = auVar5._8_6_;
                                                                  uStack_3a = auVar5._14_2_;
                                                                  *(long *)this = auVar5._0_8_;
                                                                  *(long *)(this + 6) = auVar5._6_8_
                                                                  ;
                                                                }
                                                                else if (param_3 < 6) {
                                                                  if (param_3 == 4) {
                                                                    uVar3 = fontSize(param_1);
                                                                    *(undefined4 *)this = uVar3;
                                                                  }
                                                                  else if (param_3 < 5) {
                                                                    if (param_3 == 3) {
                                                                      QVar2 = (QString)darkMode(
                                                  param_1);
                                                  *this = QVar2;
                                                  }
                                                  else if (param_3 < 4) {
                                                    if (param_3 == 2) {
                                                      auVar5 = border();
                                                      local_48 = auVar5._0_6_;
                                                      uStack_42 = auVar5._6_2_;
                                                      local_40 = auVar5._8_6_;
                                                      uStack_3a = auVar5._14_2_;
                                                      *(long *)this = auVar5._0_8_;
                                                      *(long *)(this + 6) = auVar5._6_8_;
                                                    }
                                                    else if (param_3 < 3) {
                                                      if (param_3 == 0) {
                                                        auVar5 = accent();
                                                        local_48 = auVar5._0_6_;
                                                        uStack_42 = auVar5._6_2_;
                                                        local_40 = auVar5._8_6_;
                                                        uStack_3a = auVar5._14_2_;
                                                        *(long *)this = auVar5._0_8_;
                                                        *(long *)(this + 6) = auVar5._6_8_;
                                                      }
                                                      else if (param_3 == 1) {
                                                        auVar5 = accentMuted();
                                                        local_48 = auVar5._0_6_;
                                                        uStack_42 = auVar5._6_2_;
                                                        local_40 = auVar5._8_6_;
                                                        uStack_3a = auVar5._14_2_;
                                                        *(long *)this = auVar5._0_8_;
                                                        *(long *)(this + 6) = auVar5._6_8_;
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



// ==== 0014821c  NcdeTheme::metaObject

/* NcdeTheme::metaObject() const */

undefined1 * __thiscall NcdeTheme::metaObject(NcdeTheme *this)

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



// ==== 00148264  NcdeTheme::qt_metacast

/* NcdeTheme::qt_metacast(char const*) */

NcdeTheme * __thiscall NcdeTheme::qt_metacast(NcdeTheme *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NcdeTheme *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NcdeTheme");
    if (iVar1 != 0) {
      this = (NcdeTheme *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 001482b8  NcdeTheme::qt_metacall

/* NcdeTheme::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NcdeTheme::qt_metacall(NcdeTheme *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x1f) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x1f;
    }
    if (param_2 == 7) {
      if (local_28 < 0x1f) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x1f;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -0x24;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001483ae  NcdeTheme::changed

/* NcdeTheme::changed() */

void __thiscall NcdeTheme::changed(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 001483da  NcdeTheme::wifiChanged

/* NcdeTheme::wifiChanged() */

void __thiscall NcdeTheme::wifiChanged(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 00148406  NcdeTheme::dateTimeChanged

/* NcdeTheme::dateTimeChanged() */

void __thiscall NcdeTheme::dateTimeChanged(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 00148432  NcdeTheme::usersChanged

/* NcdeTheme::usersChanged() */

void __thiscall NcdeTheme::usersChanged(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,3,(void **)0x0);
  return;
}



// ==== 0014845e  NcdeTheme::printersChanged

/* NcdeTheme::printersChanged() */

void __thiscall NcdeTheme::printersChanged(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,4,(void **)0x0);
  return;
}



// ==== 0014848a  NcdeTheme::soundChanged

/* NcdeTheme::soundChanged() */

void __thiscall NcdeTheme::soundChanged(NcdeTheme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 0017e5fa  NcdeTheme::NcdeTheme

/* NcdeTheme::NcdeTheme(QObject*) */

void __thiscall NcdeTheme::NcdeTheme(NcdeTheme *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032bd90;
  QColor::QColor((QColor *)(this + 0x10));
  QColor::QColor((QColor *)(this + 0x20));
  QColor::QColor((QColor *)(this + 0x30));
  QColor::QColor((QColor *)(this + 0x40));
  QColor::QColor((QColor *)(this + 0x50));
  QColor::QColor((QColor *)(this + 0x60));
  QColor::QColor((QColor *)(this + 0x70));
  QColor::QColor((QColor *)(this + 0x80));
  QColor::QColor((QColor *)(this + 0x90));
  QColor::QColor((QColor *)(this + 0xa0));
  QColor::QColor((QColor *)(this + 0xb0));
  QColor::QColor((QColor *)(this + 0xc0));
  QColor::QColor((QColor *)(this + 0xd0));
  *(undefined4 *)(this + 0xe0) = 0xb;
  *(undefined4 *)(this + 0xe4) = 0;
  this[0xe8] = (NcdeTheme)0x0;
  this[0xe9] = (NcdeTheme)0x0;
  QString::QString((QString *)(this + 0xf0),"gilt");
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined8 *)(this + 0x110) = 0;
  return;
}



// ==== 0017e794  NcdeTheme::accent

/* NcdeTheme::accent() const */

undefined8 NcdeTheme::accent(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x18));
  }
  return *(undefined8 *)(in_RDI + 0x10);
}



// ==== 0017e7e2  NcdeTheme::accentMuted

/* NcdeTheme::accentMuted() const */

undefined8 NcdeTheme::accentMuted(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x28));
  }
  return *(undefined8 *)(in_RDI + 0x20);
}



// ==== 0017e830  NcdeTheme::border

/* NcdeTheme::border() const */

undefined8 NcdeTheme::border(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x38));
  }
  return *(undefined8 *)(in_RDI + 0x30);
}



// ==== 0017e87e  NcdeTheme::darkMode

/* NcdeTheme::darkMode() const */

NcdeTheme __thiscall NcdeTheme::darkMode(NcdeTheme *this)

{
  return this[0xe8];
}



// ==== 0017e894  NcdeTheme::fontSize

/* NcdeTheme::fontSize() const */

undefined4 __thiscall NcdeTheme::fontSize(NcdeTheme *this)

{
  return *(undefined4 *)(this + 0xe0);
}



// ==== 0017e8a8  NcdeTheme::foreground

/* NcdeTheme::foreground() const */

undefined8 NcdeTheme::foreground(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x48));
  }
  return *(undefined8 *)(in_RDI + 0x40);
}



// ==== 0017e8f6  NcdeTheme::gilt

/* NcdeTheme::gilt() const */

undefined8 NcdeTheme::gilt(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x58));
  }
  return *(undefined8 *)(in_RDI + 0x50);
}



// ==== 0017e944  NcdeTheme::glow

/* NcdeTheme::glow() const */

undefined8 NcdeTheme::glow(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x68));
  }
  return *(undefined8 *)(in_RDI + 0x60);
}



// ==== 0017e992  NcdeTheme::panelBg

/* NcdeTheme::panelBg() const */

undefined8 NcdeTheme::panelBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x78));
  }
  return *(undefined8 *)(in_RDI + 0x70);
}



// ==== 0017e9e0  NcdeTheme::popupBg

/* NcdeTheme::popupBg() const */

undefined8 NcdeTheme::popupBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x88));
  }
  return *(undefined8 *)(in_RDI + 0x80);
}



// ==== 0017ea34  NcdeTheme::presetActive

/* NcdeTheme::presetActive() const */

NcdeTheme __thiscall NcdeTheme::presetActive(NcdeTheme *this)

{
  return this[0xe9];
}



// ==== 0017ea4a  NcdeTheme::surface

/* NcdeTheme::surface() const */

undefined8 NcdeTheme::surface(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x98));
  }
  return *(undefined8 *)(in_RDI + 0x90);
}



// ==== 0017ea9e  NcdeTheme::surfaceAlt

/* NcdeTheme::surfaceAlt() const */

undefined8 NcdeTheme::surfaceAlt(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xa8));
  }
  return *(undefined8 *)(in_RDI + 0xa0);
}



// ==== 0017eaf2  NcdeTheme::surfaceGlass

/* NcdeTheme::surfaceGlass() const */

undefined8 NcdeTheme::surfaceGlass(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xb8));
  }
  return *(undefined8 *)(in_RDI + 0xb0);
}



// ==== 0017eb46  NcdeTheme::verd

/* NcdeTheme::verd() const */

undefined8 NcdeTheme::verd(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 200));
  }
  return *(undefined8 *)(in_RDI + 0xc0);
}



// ==== 0017eb9a  NcdeTheme::version

/* NcdeTheme::version() const */

NcdeTheme * __thiscall NcdeTheme::version(NcdeTheme *this)

{
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_28,(QTypedArrayData *)0x0,L"Poseidon 14.2",0xd);
  QString::QString((QString *)this,(QArrayDataPointer *)local_28);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017ec18  NcdeTheme::widgetStyle

/* NcdeTheme::widgetStyle() const */

QString * NcdeTheme::widgetStyle(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0xf0));
  return in_RDI;
}



// ==== 0017ec48  NcdeTheme::wine

/* NcdeTheme::wine() const */

undefined8 NcdeTheme::wine(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xd8));
  }
  return *(undefined8 *)(in_RDI + 0xd0);
}



// ==== 0017ec9c  NcdeTheme::kickassGuard

/* NcdeTheme::kickassGuard() const */

undefined8 __thiscall NcdeTheme::kickassGuard(NcdeTheme *this)

{
  return *(undefined8 *)(this + 0x108);
}



// ==== 0017ecb2  NcdeTheme::wifiEnabled

/* NcdeTheme::wifiEnabled() const */

undefined8 __thiscall NcdeTheme::wifiEnabled(NcdeTheme *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x110) != 0) &&
     (cVar1 = Lelan::wifiEnabled(*(Lelan **)(this + 0x110)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 0017ecf6  NcdeTheme::wifiNetworks

/* NcdeTheme::wifiNetworks() const */

QList<QVariant> * NcdeTheme::wifiNetworks(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::wifiNetworks();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017ed78  NcdeTheme::activeNetwork

/* NcdeTheme::activeNetwork() const */

QMap<QString,QVariant> * NcdeTheme::activeNetwork(void)

{
  long lVar1;
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined8 *)in_RDI = 0;
    QMap<QString,QVariant>::QMap(in_RDI);
  }
  else {
    Lelan::activeNetwork();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017edf6  NcdeTheme::vpnConnections

/* NcdeTheme::vpnConnections() const */

QList<QVariant> * NcdeTheme::vpnConnections(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::vpnConnections();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017ee78  NcdeTheme::bluetoothEnabled

/* NcdeTheme::bluetoothEnabled() const */

undefined8 __thiscall NcdeTheme::bluetoothEnabled(NcdeTheme *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x110) != 0) &&
     (cVar1 = Lelan::bluetoothEnabled(*(Lelan **)(this + 0x110)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 0017eebc  NcdeTheme::bluetoothDiscoverable

/* NcdeTheme::bluetoothDiscoverable() const */

undefined8 __thiscall NcdeTheme::bluetoothDiscoverable(NcdeTheme *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x110) != 0) &&
     (cVar1 = Lelan::bluetoothDiscoverable(*(Lelan **)(this + 0x110)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 0017ef00  NcdeTheme::bluetoothDevices

/* NcdeTheme::bluetoothDevices() const */

QList<QVariant> * NcdeTheme::bluetoothDevices(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::bluetoothDevices();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017ef82  NcdeTheme::detectedTzName

/* NcdeTheme::detectedTzName() const */

QString * NcdeTheme::detectedTzName(void)

{
  long lVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    QString::QString(in_RDI);
  }
  else {
    Lelan::timezone();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017eff4  NcdeTheme::detectedZone

/* NcdeTheme::detectedZone() const */

NcdeTheme * __thiscall NcdeTheme::detectedZone(NcdeTheme *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  detectedTzName();
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017f040  NcdeTheme::detectedRegion

/* NcdeTheme::detectedRegion() const */

undefined8 NcdeTheme::detectedRegion(void)

{
  undefined8 in_RDI;
  long in_FS_OFFSET;
  undefined2 local_3e;
  undefined4 local_3c;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  detectedTzName();
  QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)&local_3c,0);
  QChar::QChar<char,true>((QChar *)&local_3e,'/');
  QString::section(in_RDI,local_38,local_3e,0,0,local_3c);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017f116  NcdeTheme::detectedOffset

/* NcdeTheme::detectedOffset() const */

QString * NcdeTheme::detectedOffset(void)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  undefined2 local_b2;
  undefined2 local_b0;
  undefined2 local_ae;
  int local_ac;
  QTimeZone local_a8 [8];
  undefined1 *local_a0;
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    QString::QString(in_RDI);
  }
  else {
    Lelan::timezone();
    QString::toUtf8(local_38);
    QTimeZone::QTimeZone(local_a8,(QByteArray *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QString::~QString(local_58);
    cVar1 = QTimeZone::isValid();
    if (cVar1 == '\x01') {
      QDateTime::currentDateTime();
      local_ac = QTimeZone::offsetFromUtc((QDateTime *)local_a8);
      QDateTime::~QDateTime((QDateTime *)local_38);
      local_a0 = &LAB_002996d3_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_98,(QTypedArrayData *)0x0,L"UTC%1%2:%3",10);
      QString::QString(local_78,(QArrayDataPointer *)local_98);
      QChar::QChar<char16_t,true>((QChar *)&local_b2,L' ');
      if (local_ac < 0) {
        puVar3 = &LAB_002996eb_1;
      }
      else {
        puVar3 = &LAB_002996e9_1;
      }
      QString::arg<char[2],true>(local_58,local_78,puVar3,0,local_b2);
      QChar::QChar<char,true>((QChar *)&local_b0,'0');
      iVar2 = qAbs<int>(&local_ac);
      QString::arg<int,true>(local_38,local_58,iVar2 / 0xe10,2,10,local_b0);
      QChar::QChar<char,true>((QChar *)&local_ae,'0');
      iVar2 = qAbs<int>(&local_ac);
      QString::arg<int,true>(in_RDI,local_38,(iVar2 % 0xe10) / 0x3c,2,10,local_ae);
      QString::~QString(local_38);
      QString::~QString(local_58);
      QString::~QString(local_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    }
    else {
      QString::QString(in_RDI);
    }
    QTimeZone::~QTimeZone(local_a8);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017f4c8  NcdeTheme::localTime

/* NcdeTheme::localTime() const */

NcdeTheme * __thiscall NcdeTheme::localTime(NcdeTheme *this)

{
  long in_FS_OFFSET;
  QDateTime local_68 [8];
  undefined1 *local_60;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDateTime::currentDateTime();
  local_60 = &LAB_002996eb_3;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"h:mm AP",7);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  QDateTime::toString((QString *)this);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QDateTime::~QDateTime(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017f5d0  NcdeTheme::locating

/* NcdeTheme::locating() const */

undefined8 NcdeTheme::locating(void)

{
  return 0;
}



// ==== 0017f5e0  NcdeTheme::users

/* NcdeTheme::users() const */

QList<QVariant> * NcdeTheme::users(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::users();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017f662  NcdeTheme::printers

/* NcdeTheme::printers() const */

QList<QVariant> * NcdeTheme::printers(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::printers();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017f6e4  NcdeTheme::letterSpacing

/* NcdeTheme::letterSpacing() const */

undefined4 __thiscall NcdeTheme::letterSpacing(NcdeTheme *this)

{
  return *(undefined4 *)(this + 0xe4);
}



// ==== 0017f6f8  NcdeTheme::setWifiEnabled

/* NcdeTheme::setWifiEnabled(bool) */

void __thiscall NcdeTheme::setWifiEnabled(NcdeTheme *this,bool param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setWifiEnabled(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017f734  NcdeTheme::connectNetwork

/* NcdeTheme::connectNetwork(QString const&, QString const&) */

void __thiscall NcdeTheme::connectNetwork(NcdeTheme *this,QString *param_1,QString *param_2)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::connectWifi(*(Lelan **)(this + 0x110),param_1,param_2);
  }
  return;
}



// ==== 0017f77a  NcdeTheme::disconnectNetwork

/* NcdeTheme::disconnectNetwork() */

void __thiscall NcdeTheme::disconnectNetwork(NcdeTheme *this)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::disconnectWifi(*(Lelan **)(this + 0x110));
  }
  return;
}



// ==== 0017f7ac  NcdeTheme::connectVpn

/* NcdeTheme::connectVpn(QString const&) */

void NcdeTheme::connectVpn(QString *param_1)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::connectVpn(*(QString **)(param_1 + 0x110));
  }
  return;
}



// ==== 0017f7ea  NcdeTheme::disconnectVpn

/* NcdeTheme::disconnectVpn(QString const&) */

void __thiscall NcdeTheme::disconnectVpn(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::disconnectVpn(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017f828  NcdeTheme::setBluetoothEnabled

/* NcdeTheme::setBluetoothEnabled(bool) */

void __thiscall NcdeTheme::setBluetoothEnabled(NcdeTheme *this,bool param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setBluetoothEnabled(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017f864  NcdeTheme::setBluetoothDiscoverable

/* NcdeTheme::setBluetoothDiscoverable(bool) */

void __thiscall NcdeTheme::setBluetoothDiscoverable(NcdeTheme *this,bool param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setBluetoothDiscoverable(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017f8a0  NcdeTheme::bluetoothConnect

/* NcdeTheme::bluetoothConnect(QString const&) */

void NcdeTheme::bluetoothConnect(QString *param_1)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::bluetoothConnect(*(QString **)(param_1 + 0x110));
  }
  return;
}



// ==== 0017f8de  NcdeTheme::bluetoothDisconnect

/* NcdeTheme::bluetoothDisconnect(QString const&) */

void NcdeTheme::bluetoothDisconnect(QString *param_1)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::bluetoothDisconnect(*(QString **)(param_1 + 0x110));
  }
  return;
}



// ==== 0017f91c  NcdeTheme::bluetoothPair

/* NcdeTheme::bluetoothPair(QString const&) */

void NcdeTheme::bluetoothPair(QString *param_1)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::bluetoothPair(*(QString **)(param_1 + 0x110));
  }
  return;
}



// ==== 0017f95a  NcdeTheme::bluetoothRemove

/* NcdeTheme::bluetoothRemove(QString const&) */

void NcdeTheme::bluetoothRemove(QString *param_1)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::bluetoothRemove(*(QString **)(param_1 + 0x110));
  }
  return;
}



// ==== 0017f998  NcdeTheme::bluetoothScan

/* NcdeTheme::bluetoothScan() */

void __thiscall NcdeTheme::bluetoothScan(NcdeTheme *this)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::bluetoothScan(*(Lelan **)(this + 0x110));
  }
  return;
}



// ==== 0017f9ca  NcdeTheme::refreshLocation

/* NcdeTheme::refreshLocation() */

void __thiscall NcdeTheme::refreshLocation(NcdeTheme *this)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::refreshLocation(*(Lelan **)(this + 0x110));
  }
  return;
}



// ==== 0017f9fc  NcdeTheme::setTimezone

/* NcdeTheme::setTimezone(QString const&) */

void __thiscall NcdeTheme::setTimezone(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setTimezone(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017fa3a  NcdeTheme::setNtp

/* NcdeTheme::setNtp(bool) */

void __thiscall NcdeTheme::setNtp(NcdeTheme *this,bool param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setNtp(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017fa76  NcdeTheme::addUser

/* NcdeTheme::addUser(QString const&, QString const&, bool) */

void __thiscall NcdeTheme::addUser(NcdeTheme *this,QString *param_1,QString *param_2,bool param_3)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::addUser(*(Lelan **)(this + 0x110),param_1,param_2,param_3);
  }
  return;
}



// ==== 0017fac0  NcdeTheme::removeUser

/* NcdeTheme::removeUser(QString const&) */

void __thiscall NcdeTheme::removeUser(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::removeUser(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017fafe  NcdeTheme::setUserAdmin

/* NcdeTheme::setUserAdmin(QString const&, bool) */

void __thiscall NcdeTheme::setUserAdmin(NcdeTheme *this,QString *param_1,bool param_2)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setUserAdmin(*(Lelan **)(this + 0x110),param_1,param_2);
  }
  return;
}



// ==== 0017fb42  NcdeTheme::changePassword

/* NcdeTheme::changePassword(QString const&, QString const&) */

void NcdeTheme::changePassword(QString *param_1,QString *param_2)

{
  if (*(long *)(param_1 + 0x110) != 0) {
    Lelan::changePassword(*(QString **)(param_1 + 0x110),param_2);
  }
  return;
}



// ==== 0017fb88  NcdeTheme::setAutoLogin

/* NcdeTheme::setAutoLogin(QString const&) */

void __thiscall NcdeTheme::setAutoLogin(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setAutoLogin(*(Lelan **)(this + 0x110),param_1,true);
  }
  return;
}



// ==== 0017fbca  NcdeTheme::setUserAvatar

/* NcdeTheme::setUserAvatar(QString const&, QString const&) */

void __thiscall NcdeTheme::setUserAvatar(NcdeTheme *this,QString *param_1,QString *param_2)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setUserAvatar(*(Lelan **)(this + 0x110),param_1,param_2);
  }
  return;
}



// ==== 0017fc10  NcdeTheme::setDefaultPrinter

/* NcdeTheme::setDefaultPrinter(QString const&) */

void __thiscall NcdeTheme::setDefaultPrinter(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setDefaultPrinter(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017fc4e  NcdeTheme::removePrinter

/* NcdeTheme::removePrinter(QString const&) */

void __thiscall NcdeTheme::removePrinter(NcdeTheme *this,QString *param_1)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::removePrinter(*(Lelan **)(this + 0x110),param_1);
  }
  return;
}



// ==== 0017fc8c  NcdeTheme::appStreams

/* NcdeTheme::appStreams() const */

QList<QVariant> * NcdeTheme::appStreams(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x110) == 0) {
    *(undefined1 (*) [16])in_RDI = (undefined1  [16])0x0;
    *(undefined8 *)(in_RDI + 0x10) = 0;
    QList<QVariant>::QList(in_RDI);
  }
  else {
    Lelan::appStreams();
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 0017fd0e  NcdeTheme::setAppVolume

/* NcdeTheme::setAppVolume(QString const&, int) */

void __thiscall NcdeTheme::setAppVolume(NcdeTheme *this,QString *param_1,int param_2)

{
  if (*(long *)(this + 0x110) != 0) {
    Lelan::setAppVolume(*(Lelan **)(this + 0x110),param_1,param_2);
  }
  return;
}



// ==== 0017fd52  NcdeTheme::applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()

/* NcdeTheme::applyPalette(QMap<QString, QVariant> const&)::{lambda(char const*,
   QColor&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*, QColor&) const */

void __thiscall
NcdeTheme::applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
          (_lambda_char_const__QColor___1_ *this,char *param_1,QColor *param_2)

{
  QMap<QString,QVariant> *this_00;
  QVariant *pQVar1;
  char cVar2;
  long in_FS_OFFSET;
  QString local_b8 [32];
  QString local_98 [32];
  undefined6 local_78;
  undefined2 uStack_72;
  undefined6 uStack_70;
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QMap<QString,QVariant> **)this;
  QString::QString(local_98,param_1);
  cVar2 = QMap<QString,QVariant>::contains(this_00,local_98);
  QString::~QString(local_98);
  if (cVar2 != '\0') {
    pQVar1 = *(QVariant **)this;
    ::QVariant::QVariant(local_68);
    QString::QString(local_b8,param_1);
    QMap<QString,QVariant>::value(local_48,pQVar1);
    ::QVariant::toString();
    QColor::QColor((QColor *)&local_78,local_98);
    *(ulong *)param_2 = CONCAT26(uStack_72,local_78);
    *(ulong *)(param_2 + 6) = CONCAT62(uStack_70,uStack_72);
    QString::~QString(local_98);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_b8);
    ::QVariant::~QVariant(local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017ff36  NcdeTheme::applyPalette

/* NcdeTheme::applyPalette(QMap<QString, QVariant> const&) */

void __thiscall NcdeTheme::applyPalette(NcdeTheme *this,QMap *param_1)

{
  char cVar1;
  NcdeTheme NVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QMap *local_b0;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b0 = param_1;
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"accent",(QColor *)(this + 0x10));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"accentMuted",(QColor *)(this + 0x20));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"border",(QColor *)(this + 0x30));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"foreground",(QColor *)(this + 0x40));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"gilt",(QColor *)(this + 0x50));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"glow",(QColor *)(this + 0x60));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"panelBg",(QColor *)(this + 0x70));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"popupBg",(QColor *)(this + 0x80));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"surface",(QColor *)(this + 0x90));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"surfaceAlt",(QColor *)(this + 0xa0));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"surfaceGlass",(QColor *)(this + 0xb0));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"verd",(QColor *)(this + 0xc0));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_b0,"wine",(QColor *)(this + 0xd0));
  QString::QString(local_88,"darkMode");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"darkMode");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    NVar2 = (NcdeTheme)::QVariant::toBool();
    this[0xe8] = NVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"presetActive");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"presetActive");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    NVar2 = (NcdeTheme)::QVariant::toBool();
    this[0xe9] = NVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"fontSize");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"fontSize");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0xe0) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"letterSpacing");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"letterSpacing");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0xe4) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"widgetStyle");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"widgetStyle");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0xf0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
  }
  changed(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001808aa  NcdeTheme::~NcdeTheme

/* NcdeTheme::~NcdeTheme() */

void __thiscall NcdeTheme::~NcdeTheme(NcdeTheme *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bd90;
  QString::~QString((QString *)(this + 0xf0));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001808e6  NcdeTheme::~NcdeTheme

/* NcdeTheme::~NcdeTheme() */

void __thiscall NcdeTheme::~NcdeTheme(NcdeTheme *this)

{
  ~NcdeTheme(this);
  operator_delete(this,0x118);
  return;
}


