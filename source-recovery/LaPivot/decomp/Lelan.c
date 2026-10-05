// Ghidra decompile of LaPivot.oracle — class/namespace Lelan (378 functions). Raw; not source.

// ==== 0013c5e2  Lelan::qt_static_metacall

/* Lelan::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void Lelan::qt_static_metacall(Lelan *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  undefined8 *puVar1;
  QMap<QString,QVariant> *this;
  undefined1 uVar2;
  bool bVar3;
  QMap<QString,QVariant> QVar4;
  undefined4 uVar5;
  uint uVar6;
  long in_FS_OFFSET;
  undefined8 uVar7;
  undefined8 local_58 [3];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0xb1) {
      local_58[0] = monoRawMs();
      if (*(long *)param_4 != 0) {
        **(undefined8 **)param_4 = local_58[0];
      }
    }
    else if (param_3 < 0xb2) {
      if (param_3 == 0xb0) {
        uVar2 = saveConfig(param_1,*(QString **)(param_4 + 8),*(QMap **)(param_4 + 0x10));
        local_58[0] = CONCAT71(local_58[0]._1_7_,uVar2);
        if (*(long *)param_4 != 0) {
          **(undefined1 **)param_4 = uVar2;
        }
      }
      else if (param_3 < 0xb1) {
        if (param_3 == 0xaf) {
          loadConfig((QString *)local_58);
          if (*(long *)param_4 != 0) {
            QMap<QString,QVariant>::operator=(*(QMap<QString,QVariant> **)param_4,(QMap *)local_58);
          }
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_58);
        }
        else if (param_3 < 0xb0) {
          if (param_3 == 0xae) {
            onKickassNetworkAlert(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10));
          }
          else if (param_3 < 0xaf) {
            if (param_3 == 0xad) {
              onKickassSiteBlocked((QString *)param_1,*(QString **)(param_4 + 8));
            }
            else if (param_3 < 0xae) {
              if (param_3 == 0xac) {
                onKickassThreatBehavioral
                          (param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10),
                           *(QString **)(param_4 + 0x18));
              }
              else if (param_3 < 0xad) {
                if (param_3 == 0xab) {
                  onKickassThreatBlocked
                            ((QString *)param_1,*(QString **)(param_4 + 8),
                             (int)*(undefined8 *)(param_4 + 0x10));
                }
                else if (param_3 < 0xac) {
                  if (param_3 == 0xaa) {
                    onKickassStatusChanged
                              (param_1,*(bool *)*(undefined8 *)(param_4 + 8),
                               **(int **)(param_4 + 0x10));
                  }
                  else if (param_3 < 0xab) {
                    if (param_3 == 0xa9) {
                      onSentinelDriverMissing
                                (param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10),
                                 *(QString **)(param_4 + 0x18));
                    }
                    else if (param_3 < 0xaa) {
                      if (param_3 == 0xa8) {
                        onSentinelThermalCritical
                                  (param_1,*(QString **)(param_4 + 8),**(double **)(param_4 + 0x10))
                        ;
                      }
                      else if (param_3 < 0xa9) {
                        if (param_3 == 0xa7) {
                          onSentinelFanChanged(param_1,*(QMap **)(param_4 + 8));
                        }
                        else if (param_3 < 0xa8) {
                          if (param_3 == 0xa6) {
                            onSentinelThermalChanged(param_1,*(QMap **)(param_4 + 8));
                          }
                          else if (param_3 < 0xa7) {
                            if (param_3 == 0xa5) {
                              onSentinelNetworkStateChanged
                                        (param_1,*(QString **)(param_4 + 8),
                                         *(bool *)*(undefined8 *)(param_4 + 0x10));
                            }
                            else if (param_3 < 0xa6) {
                              if (param_3 == 0xa4) {
                                onSentinelBatteryStateChanged
                                          (param_1,*(bool *)*(undefined8 *)(param_4 + 8),
                                           **(int **)(param_4 + 0x10));
                              }
                              else if (param_3 < 0xa5) {
                                if (param_3 == 0xa3) {
                                  onSentinelAudioDeviceChanged
                                            ((QString *)param_1,*(QString **)(param_4 + 8));
                                }
                                else if (param_3 < 0xa4) {
                                  if (param_3 == 0xa2) {
                                    onSentinelInputDeviceRemoved((QString *)param_1);
                                  }
                                  else if (param_3 < 0xa3) {
                                    if (param_3 == 0xa1) {
                                      onSentinelInputDeviceAdded((QString *)param_1);
                                    }
                                    else if (param_3 < 0xa2) {
                                      if (param_3 == 0xa0) {
                                        onSentinelUsbDeviceRemoved
                                                  ((QString *)param_1,*(QString **)(param_4 + 8));
                                      }
                                      else if (param_3 < 0xa1) {
                                        if (param_3 == 0x9f) {
                                          onSentinelUsbDeviceAdded
                                                    ((QString *)param_1,*(QString **)(param_4 + 8));
                                        }
                                        else if (param_3 < 0xa0) {
                                          if (param_3 == 0x9e) {
                                            onSentinelDisplayDisconnected((QString *)param_1);
                                          }
                                          else if (param_3 < 0x9f) {
                                            if (param_3 == 0x9d) {
                                              onSentinelDisplayConnected((QString *)param_1);
                                            }
                                            else if (param_3 < 0x9e) {
                                              if (param_3 == 0x9c) {
                                                onTrayItemChanged(param_1);
                                              }
                                              else if (param_3 < 0x9d) {
                                                if (param_3 == 0x9b) {
                                                  rebuildTray(param_1);
                                                }
                                                else if (param_3 < 0x9c) {
                                                  if (param_3 == 0x9a) {
                                                    onLayoutUpdated(param_1);
                                                  }
                                                  else if (param_3 < 0x9b) {
                                                    if (param_3 == 0x99) {
                                                      onMprisSeeked(param_1,**(longlong **)
                                                                              (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x9a) {
                                                      if (param_3 == 0x98) {
                                                        onPropertiesChanged((QString *)param_1,
                                                                            *(QMap **)(param_4 + 8),
                                                                            *(QList **)
                                                                             (param_4 + 0x10));
                                                      }
                                                      else if (param_3 < 0x99) {
                                                        uVar6 = (uint)param_1;
                                                        if (param_3 == 0x97) {
                                                          onActionInvoked(uVar6,(QString *)
                                                                                (ulong)**(uint **)(
                                                  param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x98) {
                                                    if (param_3 == 0x96) {
                                                      onScreenSaverActivated
                                                                (param_1,*(bool *)*(undefined8 *)
                                                                                   (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x97) {
                                                      if (param_3 == 0x95) {
                                                        onPrepareForSleep(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x96) {
                                                    if (param_3 == 0x94) {
                                                      onSessionUnlock(param_1);
                                                    }
                                                    else if (param_3 < 0x95) {
                                                      if (param_3 == 0x93) {
                                                        onSessionLock(param_1);
                                                      }
                                                      else if (param_3 < 0x94) {
                                                        if (param_3 == 0x92) {
                                                          onSessionActiveChangedSlot
                                                                    ((QString *)param_1,
                                                                     *(QMap **)(param_4 + 8),
                                                                     *(QList **)(param_4 + 0x10));
                                                        }
                                                        else if (param_3 < 0x93) {
                                                          if (param_3 == 0x91) {
                                                            onLocale1PropertiesChanged
                                                                      ((QString *)param_1,
                                                                       *(QMap **)(param_4 + 8),
                                                                       *(QList **)(param_4 + 0x10));
                                                          }
                                                          else if (param_3 < 0x92) {
                                                            if (param_3 == 0x90) {
                                                              onHostname1PropertiesChanged
                                                                        ((QString *)param_1,
                                                                         *(QMap **)(param_4 + 8),
                                                                         *(QList **)(param_4 + 0x10)
                                                                        );
                                                            }
                                                            else if (param_3 < 0x91) {
                                                              if (param_3 == 0x8f) {
                                                                onTimedate1PropertiesChanged
                                                                          ((QString *)param_1,
                                                                           *(QMap **)(param_4 + 8),
                                                                           *(QList **)
                                                                            (param_4 + 0x10));
                                                              }
                                                              else if (param_3 < 0x90) {
                                                                if (param_3 == 0x8e) {
                                                                  onGeoClue2Location((
                                                  QDBusObjectPath *)param_1,
                                                  *(QDBusObjectPath **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x8f) {
                                                    if (param_3 == 0x8d) {
                                                      onLowMemoryWarning(param_1,**(uchar **)
                                                                                   (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x8e) {
                                                      if (param_3 == 0x8c) {
                                                        onPortalSettingChanged
                                                                  ((QString *)param_1,
                                                                   *(QString **)(param_4 + 8),
                                                                   *(QDBusVariant **)
                                                                    (param_4 + 0x10));
                                                      }
                                                      else if (param_3 < 0x8d) {
                                                        if (param_3 == 0x8b) {
                                                          onPackageKitUpdatesFinished
                                                                    (uVar6,**(uint **)(param_4 + 8))
                                                          ;
                                                        }
                                                        else if (param_3 < 0x8c) {
                                                          if (param_3 == 0x8a) {
                                                            onPackageKitUpdatesPackage
                                                                      (param_1,**(uint **)(param_4 +
                                                                                          8),
                                                                       *(QString **)(param_4 + 0x10)
                                                                       ,*(QString **)
                                                                         (param_4 + 0x18));
                                                          }
                                                          else if (param_3 < 0x8b) {
                                                            if (param_3 == 0x89) {
                                                              onPackageKitUpdatesChanged(param_1);
                                                            }
                                                            else if (param_3 < 0x8a) {
                                                              if (param_3 == 0x88) {
                                                                onPowerProfilesPropertiesChanged
                                                                          ((QString *)param_1,
                                                                           *(QMap **)(param_4 + 8),
                                                                           *(QList **)
                                                                            (param_4 + 0x10));
                                                              }
                                                              else if (param_3 < 0x89) {
                                                                if (param_3 == 0x87) {
                                                                  applyDefaultSource(param_1,*(
                                                  QString **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x88) {
                                                    if (param_3 == 0x86) {
                                                      applyInputDevices(param_1,*(QList **)
                                                                                 (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x87) {
                                                      if (param_3 == 0x85) {
                                                        applyOutputDevices(param_1,*(QList **)
                                                                                    (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x86) {
                                                        if (param_3 == 0x84) {
                                                          applyAppStreams(param_1,*(QList **)
                                                                                   (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x85) {
                                                          if (param_3 == 0x83) {
                                                            applyPulseState(param_1,**(int **)(
                                                  param_4 + 8),
                                                  *(bool *)*(undefined8 *)(param_4 + 0x10),
                                                  *(QString **)(param_4 + 0x18),
                                                  **(uint **)(param_4 + 0x20),
                                                  **(int **)(param_4 + 0x28));
                                                  }
                                                  else if (param_3 < 0x84) {
                                                    if (param_3 == 0x82) {
                                                      onUDisks2FilesystemPropertiesChanged
                                                                ((QString *)param_1,
                                                                 *(QMap **)(param_4 + 8),
                                                                 *(QList **)(param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x83) {
                                                      if (param_3 == 0x81) {
                                                        onUDisks2InterfacesRemoved
                                                                  ((QDBusObjectPath *)param_1,
                                                                   *(QList **)(param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x82) {
                                                        if (param_3 == 0x80) {
                                                          onUDisks2InterfacesAdded
                                                                    ((QDBusObjectPath *)param_1,
                                                                     *(QMap **)(param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x81) {
                                                          if (param_3 == 0x7f) {
                                                            onBlueZPropertiesChanged
                                                                      ((QString *)param_1,
                                                                       *(QMap **)(param_4 + 8),
                                                                       *(QList **)(param_4 + 0x10));
                                                          }
                                                          else if (param_3 < 0x80) {
                                                            if (param_3 == 0x7e) {
                                                              onBlueZInterfacesRemoved
                                                                        ((QDBusObjectPath *)param_1,
                                                                         *(QList **)(param_4 + 8));
                                                            }
                                                            else if (param_3 < 0x7f) {
                                                              if (param_3 == 0x7d) {
                                                                onBlueZInterfacesAdded
                                                                          ((QDBusObjectPath *)
                                                                           param_1,*(QMap **)(
                                                  param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x7e) {
                                                    if (param_3 == 0x7c) {
                                                      onBatteryPropertiesChanged
                                                                ((QString *)param_1,
                                                                 *(QMap **)(param_4 + 8),
                                                                 *(QList **)(param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x7d) {
                                                      if (param_3 == 0x7b) {
                                                        onWifiPropertiesChanged
                                                                  ((QString *)param_1,
                                                                   *(QMap **)(param_4 + 8),
                                                                   *(QList **)(param_4 + 0x10));
                                                      }
                                                      else if (param_3 < 0x7c) {
                                                        if (param_3 == 0x7a) {
                                                          onVpnStateChanged(param_1,**(uint **)(
                                                  param_4 + 8),**(uint **)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0x7b) {
                                                    if (param_3 == 0x79) {
                                                      onNmPropertiesChanged
                                                                ((QString *)param_1,
                                                                 *(QMap **)(param_4 + 8),
                                                                 *(QList **)(param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x7a) {
                                                      if (param_3 == 0x78) {
                                                        onNetworkStateChanged
                                                                  (param_1,**(uint **)(param_4 + 8))
                                                        ;
                                                      }
                                                      else if (param_3 < 0x79) {
                                                        if (param_3 == 0x77) {
                                                          drainIdleQueue(param_1);
                                                        }
                                                        else if (param_3 < 0x78) {
                                                          if (param_3 == 0x76) {
                                                            recomputeAnimLevel(param_1);
                                                          }
                                                          else if (param_3 < 0x77) {
                                                            if (param_3 == 0x75) {
                                                              onPulse(param_1);
                                                            }
                                                            else if (param_3 < 0x76) {
                                                              if (param_3 == 0x74) {
                                                                onCoalescedTick(param_1);
                                                              }
                                                              else if (param_3 < 0x75) {
                                                                if (param_3 == 0x73) {
                                                                  onSystemNameOwnerChanged
                                                                            (param_1,*(QString **)
                                                                                      (param_4 + 8),
                                                                             *(QString **)
                                                                              (param_4 + 0x10),
                                                                             *(QString **)
                                                                              (param_4 + 0x18));
                                                                }
                                                                else if (param_3 < 0x74) {
                                                                  if (param_3 == 0x72) {
                                                                    onNameOwnerChanged(param_1,*(
                                                  QString **)(param_4 + 8),
                                                  *(QString **)(param_4 + 0x10),
                                                  *(QString **)(param_4 + 0x18));
                                                  }
                                                  else if (param_3 < 0x73) {
                                                    if (param_3 == 0x71) {
                                                      retryFallbackSink(param_1);
                                                    }
                                                    else if (param_3 < 0x72) {
                                                      if (param_3 == 0x70) {
                                                        setReduceMotionPref(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x71) {
                                                    if (param_3 == 0x6f) {
                                                      setAnimUtilClamp(param_1,*(bool *)*(undefined8
                                                                                          *)(param_4
                                                                                            + 8));
                                                    }
                                                    else if (param_3 < 0x70) {
                                                      if (param_3 == 0x6e) {
                                                        unmountVolume(param_1,*(QString **)
                                                                               (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x6f) {
                                                        if (param_3 == 0x6d) {
                                                          mountVolume(param_1,*(QString **)
                                                                               (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x6e) {
                                                          if (param_3 == 0x6c) {
                                                            removePrinter(param_1,*(QString **)
                                                                                   (param_4 + 8));
                                                          }
                                                          else if (param_3 < 0x6d) {
                                                            if (param_3 == 0x6b) {
                                                              setDefaultPrinter(param_1,*(QString **
                                                                                         )(param_4 +
                                                                                          8));
                                                            }
                                                            else if (param_3 < 0x6c) {
                                                              if (param_3 == 0x6a) {
                                                                setUserAvatar(param_1,*(QString **)
                                                                                       (param_4 + 8)
                                                                              ,*(QString **)
                                                                                (param_4 + 0x10));
                                                              }
                                                              else if (param_3 < 0x6b) {
                                                                if (param_3 == 0x69) {
                                                                  setAutoLogin(param_1,*(QString **)
                                                                                        (param_4 + 8
                                                                                        ),true);
                                                                }
                                                                else if (param_3 < 0x6a) {
                                                                  if (param_3 == 0x68) {
                                                                    setAutoLogin(param_1,*(QString *
                                                  *)(param_4 + 8),
                                                  *(bool *)*(undefined8 *)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0x69) {
                                                    if (param_3 == 0x67) {
                                                      changePassword((QString *)param_1,
                                                                     *(QString **)(param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x68) {
                                                      if (param_3 == 0x66) {
                                                        setUserAdmin(param_1,*(QString **)
                                                                              (param_4 + 8),
                                                                     *(bool *)*(undefined8 *)
                                                                               (param_4 + 0x10));
                                                      }
                                                      else if (param_3 < 0x67) {
                                                        if (param_3 == 0x65) {
                                                          removeUser(param_1,*(QString **)
                                                                              (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x66) {
                                                          if (param_3 == 100) {
                                                            addUser(param_1,*(QString **)
                                                                             (param_4 + 8),
                                                                    *(QString **)(param_4 + 0x10),
                                                                    *(bool *)*(undefined8 *)
                                                                              (param_4 + 0x18));
                                                          }
                                                          else if (param_3 < 0x65) {
                                                            if (param_3 == 99) {
                                                              refreshLocation(param_1);
                                                            }
                                                            else if (param_3 < 100) {
                                                              if (param_3 == 0x62) {
                                                                setNtp(param_1,*(bool *)*(undefined8
                                                                                          *)(param_4
                                                                                            + 8));
                                                              }
                                                              else if (param_3 < 99) {
                                                                if (param_3 == 0x61) {
                                                                  setTimezone(param_1,*(QString **)
                                                                                       (param_4 + 8)
                                                                             );
                                                                }
                                                                else if (param_3 < 0x62) {
                                                                  if (param_3 == 0x60) {
                                                                    bluetoothScan(param_1);
                                                                  }
                                                                  else if (param_3 < 0x61) {
                                                                    if (param_3 == 0x5f) {
                                                                      bluetoothRemove((QString *)
                                                                                      param_1);
                                                                    }
                                                                    else if (param_3 < 0x60) {
                                                                      if (param_3 == 0x5e) {
                                                                        bluetoothPair((QString *)
                                                                                      param_1);
                                                                      }
                                                                      else if (param_3 < 0x5f) {
                                                                        if (param_3 == 0x5d) {
                                                                          bluetoothDisconnect((
                                                  QString *)param_1);
                                                  }
                                                  else if (param_3 < 0x5e) {
                                                    if (param_3 == 0x5c) {
                                                      bluetoothConnect((QString *)param_1);
                                                    }
                                                    else if (param_3 < 0x5d) {
                                                      if (param_3 == 0x5b) {
                                                        setBluetoothDiscoverable
                                                                  (param_1,*(bool *)*(undefined8 *)
                                                                                     (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x5c) {
                                                        if (param_3 == 0x5a) {
                                                          setBluetoothEnabled(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x5b) {
                                                    if (param_3 == 0x59) {
                                                      disconnectVpn(param_1,*(QString **)
                                                                             (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x5a) {
                                                      if (param_3 == 0x58) {
                                                        connectVpn((QString *)param_1);
                                                      }
                                                      else if (param_3 < 0x59) {
                                                        if (param_3 == 0x57) {
                                                          disconnectWifi(param_1);
                                                        }
                                                        else if (param_3 < 0x58) {
                                                          if (param_3 == 0x56) {
                                                            connectWifi(param_1,*(QString **)
                                                                                 (param_4 + 8),
                                                                        *(QString **)
                                                                         (param_4 + 0x10));
                                                          }
                                                          else if (param_3 < 0x57) {
                                                            if (param_3 == 0x55) {
                                                              setWifiEnabled(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x56) {
                                                    if (param_3 == 0x54) {
                                                      setInputDevice(param_1,*(QString **)
                                                                              (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x55) {
                                                      if (param_3 == 0x53) {
                                                        setOutputDevice(param_1,*(QString **)
                                                                                 (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x54) {
                                                        if (param_3 == 0x52) {
                                                          setAppVolume(param_1,*(QString **)
                                                                                (param_4 + 8),
                                                                       **(int **)(param_4 + 0x10));
                                                        }
                                                        else if (param_3 < 0x53) {
                                                          if (param_3 == 0x51) {
                                                            setBalance(param_1,**(int **)(param_4 +
                                                                                         8));
                                                          }
                                                          else if (param_3 < 0x52) {
                                                            if (param_3 == 0x50) {
                                                              toggleMute(param_1);
                                                            }
                                                            else if (param_3 < 0x51) {
                                                              if (param_3 == 0x4f) {
                                                                setVolume(param_1,**(int **)(param_4
                                                                                            + 8));
                                                              }
                                                              else if (param_3 < 0x50) {
                                                                if (param_3 == 0x4e) {
                                                                  mediaSeek(param_1,**(longlong **)
                                                                                      (param_4 + 8))
                                                                  ;
                                                                }
                                                                else if (param_3 < 0x4f) {
                                                                  if (param_3 == 0x4d) {
                                                                    mediaPrevious(param_1);
                                                                  }
                                                                  else if (param_3 < 0x4e) {
                                                                    if (param_3 == 0x4c) {
                                                                      mediaNext(param_1);
                                                                    }
                                                                    else if (param_3 < 0x4d) {
                                                                      if (param_3 == 0x4b) {
                                                                        mediaPlayPause(param_1);
                                                                      }
                                                                      else if (param_3 < 0x4c) {
                                                                        if (param_3 == 0x4a) {
                                                                          fetchAndApply(param_1,*(
                                                  QString **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x4b) {
                                                    if (param_3 == 0x49) {
                                                      applyProperties(param_1,*(QMap **)(param_4 + 8
                                                                                        ));
                                                    }
                                                    else if (param_3 < 0x4a) {
                                                      if (param_3 == 0x48) {
                                                        onWindowClosed(param_1,**(uint **)(param_4 +
                                                                                          8));
                                                      }
                                                      else if (param_3 < 0x49) {
                                                        if (param_3 == 0x47) {
                                                          QString::QString((QString *)local_58,
                                                                           *(QString **)
                                                                            (param_4 + 0x10));
                                                          onWindowTierNeeded(param_1,**(undefined4
                                                                                        **)(param_4 
                                                  + 8),local_58);
                                                  QString::~QString((QString *)local_58);
                                                  }
                                                  else if (param_3 < 0x48) {
                                                    if (param_3 == 0x46) {
                                                      onWMScreenConfig(uVar6,**(int **)(param_4 + 8)
                                                                      );
                                                    }
                                                    else if (param_3 < 0x47) {
                                                      if (param_3 == 0x45) {
                                                        hardwareTierChanged(param_1);
                                                      }
                                                      else if (param_3 < 0x46) {
                                                        if (param_3 == 0x44) {
                                                          animLevelChanged(param_1);
                                                        }
                                                        else if (param_3 < 0x45) {
                                                          if (param_3 == 0x43) {
                                                            notificationsChanged(param_1);
                                                          }
                                                          else if (param_3 < 0x44) {
                                                            if (param_3 == 0x42) {
                                                              printersChanged(param_1);
                                                            }
                                                            else if (param_3 < 0x43) {
                                                              if (param_3 == 0x41) {
                                                                usersChanged(param_1);
                                                              }
                                                              else if (param_3 < 0x42) {
                                                                if (param_3 == 0x40) {
                                                                  userNameChanged(param_1);
                                                                }
                                                                else if (param_3 < 0x41) {
                                                                  if (param_3 == 0x3f) {
                                                                    localeChanged(param_1);
                                                                  }
                                                                  else if (param_3 < 0x40) {
                                                                    if (param_3 == 0x3e) {
                                                                      hostnameChanged(param_1);
                                                                    }
                                                                    else if (param_3 < 0x3f) {
                                                                      if (param_3 == 0x3d) {
                                                                        screenGeometryChanged
                                                                                  (param_1);
                                                                      }
                                                                      else if (param_3 < 0x3e) {
                                                                        if (param_3 == 0x3c) {
                                                                          screenConfigChanged(
                                                  param_1);
                                                  }
                                                  else if (param_3 < 0x3d) {
                                                    if (param_3 == 0x3b) {
                                                      screensaverChanged(param_1);
                                                    }
                                                    else if (param_3 < 0x3c) {
                                                      if (param_3 == 0x3a) {
                                                        vtActiveChanged(param_1);
                                                      }
                                                      else if (param_3 < 0x3b) {
                                                        if (param_3 == 0x39) {
                                                          onSessionActiveChanged(param_1);
                                                        }
                                                        else if (param_3 < 0x3a) {
                                                          if (param_3 == 0x38) {
                                                            filigreePalettesChanged(param_1);
                                                          }
                                                          else if (param_3 < 0x39) {
                                                            if (param_3 == 0x37) {
                                                              slideshowChanged(param_1);
                                                            }
                                                            else if (param_3 < 0x38) {
                                                              if (param_3 == 0x36) {
                                                                systemFontChanged(param_1);
                                                              }
                                                              else if (param_3 < 0x37) {
                                                                if (param_3 == 0x35) {
                                                                  wallpaperChanged(param_1);
                                                                }
                                                                else if (param_3 < 0x36) {
                                                                  if (param_3 == 0x34) {
                                                                    onAccentColorChanged(param_1);
                                                                  }
                                                                  else if (param_3 < 0x35) {
                                                                    if (param_3 == 0x33) {
                                                                      darkModeChanged(param_1);
                                                                    }
                                                                    else if (param_3 < 0x34) {
                                                                      if (param_3 == 0x32) {
                                                                        themeChanged(param_1);
                                                                      }
                                                                      else if (param_3 < 0x33) {
                                                                        if (param_3 == 0x31) {
                                                                          onTrayPercentChanged
                                                                                    (param_1);
                                                                        }
                                                                        else if (param_3 < 0x32) {
                                                                          if (param_3 == 0x30) {
                                                                            onTrayBadgeChanged(
                                                  param_1);
                                                  }
                                                  else if (param_3 < 0x31) {
                                                    if (param_3 == 0x2f) {
                                                      trayChanged(param_1);
                                                    }
                                                    else if (param_3 < 0x30) {
                                                      if (param_3 == 0x2e) {
                                                        moonPositionChanged(param_1);
                                                      }
                                                      else if (param_3 < 0x2f) {
                                                        if (param_3 == 0x2d) {
                                                          placeNameChanged(param_1);
                                                        }
                                                        else if (param_3 < 0x2e) {
                                                          if (param_3 == 0x2c) {
                                                            weatherChanged(param_1);
                                                          }
                                                          else if (param_3 < 0x2d) {
                                                            if (param_3 == 0x2b) {
                                                              timezoneChanged(param_1);
                                                            }
                                                            else if (param_3 < 0x2c) {
                                                              if (param_3 == 0x2a) {
                                                                dateTimeChanged(param_1);
                                                              }
                                                              else if (param_3 < 0x2b) {
                                                                if (param_3 == 0x29) {
                                                                  leanWaking(param_1);
                                                                }
                                                                else if (param_3 < 0x2a) {
                                                                  if (param_3 == 0x28) {
                                                                    leanSleeping(param_1);
                                                                  }
                                                                  else if (param_3 < 0x29) {
                                                                    if (param_3 == 0x27) {
                                                                      pulse(param_1,**(ulonglong **)
                                                                                      (param_4 + 8))
                                                                      ;
                                                                    }
                                                                    else if (param_3 < 0x28) {
                                                                      if (param_3 == 0x26) {
                                                                        timeJumped(param_1);
                                                                      }
                                                                      else if (param_3 < 0x27) {
                                                                        if (param_3 == 0x25) {
                                                                          clockChanged(param_1);
                                                                        }
                                                                        else if (param_3 < 0x26) {
                                                                          if (param_3 == 0x24) {
                                                                            updatesChanged(param_1);
                                                                          }
                                                                          else if (param_3 < 0x25) {
                                                                            if (param_3 == 0x23) {
                                                                              packageStateChanged(
                                                  param_1);
                                                  }
                                                  else if (param_3 < 0x24) {
                                                    if (param_3 == 0x22) {
                                                      kickassNetworkAlert(param_1,*(QString **)
                                                                                   (param_4 + 8),
                                                                          *(QString **)
                                                                           (param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x23) {
                                                      if (param_3 == 0x21) {
                                                        kickassThreatBehavioral
                                                                  (param_1,*(QString **)
                                                                            (param_4 + 8),
                                                                   *(QString **)(param_4 + 0x10),
                                                                   *(QString **)(param_4 + 0x18));
                                                      }
                                                      else if (param_3 < 0x22) {
                                                        if (param_3 == 0x20) {
                                                          kickassThreatBlocked
                                                                    (param_1,*(QString **)
                                                                              (param_4 + 8),
                                                                     *(QString **)(param_4 + 0x10),
                                                                     **(int **)(param_4 + 0x18));
                                                        }
                                                        else if (param_3 < 0x21) {
                                                          if (param_3 == 0x1f) {
                                                            kickassSiteBlocked(param_1,*(QString **)
                                                                                        (param_4 + 8
                                                                                        ),
                                                                               *(QString **)
                                                                                (param_4 + 0x10));
                                                          }
                                                          else if (param_3 < 0x20) {
                                                            if (param_3 == 0x1e) {
                                                              kickassStatusChanged(param_1);
                                                            }
                                                            else if (param_3 < 0x1f) {
                                                              if (param_3 == 0x1d) {
                                                                kickassChanged(param_1);
                                                              }
                                                              else if (param_3 < 0x1e) {
                                                                if (param_3 == 0x1c) {
                                                                  storageChanged(param_1);
                                                                }
                                                                else if (param_3 < 0x1d) {
                                                                  if (param_3 == 0x1b) {
                                                                    diskMountChanged(param_1);
                                                                  }
                                                                  else if (param_3 < 0x1c) {
                                                                    if (param_3 == 0x1a) {
                                                                      diskDeviceChanged(param_1);
                                                                    }
                                                                    else if (param_3 < 0x1b) {
                                                                      if (param_3 == 0x19) {
                                                                        diskChanged(param_1);
                                                                      }
                                                                      else if (param_3 < 0x1a) {
                                                                        if (param_3 == 0x18) {
                                                                          bluetoothChanged(param_1);
                                                                        }
                                                                        else if (param_3 < 0x19) {
                                                                          if (param_3 == 0x17) {
                                                                            durationChanged(param_1)
                                                                            ;
                                                                          }
                                                                          else if (param_3 < 0x18) {
                                                                            if (param_3 == 0x16) {
                                                                              appIconChanged(param_1
                                                  );
                                                  }
                                                  else if (param_3 < 0x17) {
                                                    if (param_3 == 0x15) {
                                                      appNameChanged(param_1);
                                                    }
                                                    else if (param_3 < 0x16) {
                                                      if (param_3 == 0x14) {
                                                        mediaPositionChanged(param_1);
                                                      }
                                                      else if (param_3 < 0x15) {
                                                        if (param_3 == 0x13) {
                                                          mediaChanged(param_1);
                                                        }
                                                        else if (param_3 < 0x14) {
                                                          if (param_3 == 0x12) {
                                                            appStreamsChanged(param_1);
                                                          }
                                                          else if (param_3 < 0x13) {
                                                            if (param_3 == 0x11) {
                                                              onFallbackSinkUpdated(param_1);
                                                            }
                                                            else if (param_3 < 0x12) {
                                                              if (param_3 == 0x10) {
                                                                onAudioMuteUpdated(param_1);
                                                              }
                                                              else if (param_3 < 0x11) {
                                                                if (param_3 == 0xf) {
                                                                  onAudioVolumeUpdated(param_1);
                                                                }
                                                                else if (param_3 < 0x10) {
                                                                  if (param_3 == 0xe) {
                                                                    bluetoothAudioDeviceChanged
                                                                              (param_1);
                                                                  }
                                                                  else if (param_3 < 0xf) {
                                                                    if (param_3 == 0xd) {
                                                                      audioDevicesChanged(param_1);
                                                                    }
                                                                    else if (param_3 < 0xe) {
                                                                      if (param_3 == 0xc) {
                                                                        audioDeviceChanged(param_1);
                                                                      }
                                                                      else if (param_3 < 0xd) {
                                                                        if (param_3 == 0xb) {
                                                                          audioChanged(param_1);
                                                                        }
                                                                        else if (param_3 < 0xc) {
                                                                          if (param_3 == 10) {
                                                                            statsChanged(param_1);
                                                                          }
                                                                          else if (param_3 < 0xb) {
                                                                            if (param_3 == 9) {
                                                                              driverMissing(param_1,
                                                  *(QString **)(param_4 + 8),
                                                  *(QString **)(param_4 + 0x10),
                                                  *(QString **)(param_4 + 0x18));
                                                  }
                                                  else if (param_3 < 10) {
                                                    if (param_3 == 8) {
                                                      sentinelFansChanged(param_1);
                                                    }
                                                    else if (param_3 < 9) {
                                                      if (param_3 == 7) {
                                                        sentinelTempsChanged(param_1);
                                                      }
                                                      else if (param_3 < 8) {
                                                        if (param_3 == 6) {
                                                          thermalPressureChanged(param_1);
                                                        }
                                                        else if (param_3 < 7) {
                                                          if (param_3 == 5) {
                                                            powerChanged(param_1);
                                                          }
                                                          else if (param_3 < 6) {
                                                            if (param_3 == 4) {
                                                              powerProfileChanged(param_1);
                                                            }
                                                            else if (param_3 < 5) {
                                                              if (param_3 == 3) {
                                                                batteryChanged(param_1);
                                                              }
                                                              else if (param_3 < 4) {
                                                                if (param_3 == 2) {
                                                                  wifiChanged(param_1);
                                                                }
                                                                else if (param_3 < 3) {
                                                                  if (param_3 == 0) {
                                                                    networkChanged(param_1);
                                                                  }
                                                                  else if (param_3 == 1) {
                                                                    vpnStateChanged(param_1);
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
  if (param_2 == 7) {
    if (param_3 == 0xa7) {
      if (**(int **)(param_4 + 8) == 0) {
        puVar1 = *(undefined8 **)param_4;
        uVar7 = QMetaType::fromType<QMap<QString,unsigned_int>>();
        *puVar1 = uVar7;
      }
      else {
        local_58[0] = 0;
        QMetaType::QMetaType((QMetaType *)local_58);
        **(undefined8 **)param_4 = local_58[0];
      }
    }
    else {
      if (param_3 < 0xa8) {
        if (param_3 == 0xa6) {
          if (**(int **)(param_4 + 8) == 0) {
            puVar1 = *(undefined8 **)param_4;
            uVar7 = QMetaType::fromType<QMap<QString,double>>();
            *puVar1 = uVar7;
          }
          else {
            local_58[0] = 0;
            QMetaType::QMetaType((QMetaType *)local_58);
            **(undefined8 **)param_4 = local_58[0];
          }
          goto LAB_0013ed6d;
        }
        if (param_3 < 0xa7) {
          if (param_3 == 0x8e) {
            if (**(uint **)(param_4 + 8) < 2) {
              puVar1 = *(undefined8 **)param_4;
              uVar7 = QMetaType::fromType<QDBusObjectPath>();
              *puVar1 = uVar7;
            }
            else {
              local_58[0] = 0;
              QMetaType::QMetaType((QMetaType *)local_58);
              **(undefined8 **)param_4 = local_58[0];
            }
            goto LAB_0013ed6d;
          }
          if (param_3 < 0x8f) {
            if (param_3 == 0x8c) {
              if (**(int **)(param_4 + 8) == 2) {
                puVar1 = *(undefined8 **)param_4;
                uVar7 = QMetaType::fromType<QDBusVariant>();
                *puVar1 = uVar7;
              }
              else {
                local_58[0] = 0;
                QMetaType::QMetaType((QMetaType *)local_58);
                **(undefined8 **)param_4 = local_58[0];
              }
              goto LAB_0013ed6d;
            }
            if (param_3 < 0x8d) {
              if (param_3 == 0x81) {
                if (**(int **)(param_4 + 8) == 0) {
                  puVar1 = *(undefined8 **)param_4;
                  uVar7 = QMetaType::fromType<QDBusObjectPath>();
                  *puVar1 = uVar7;
                }
                else {
                  local_58[0] = 0;
                  QMetaType::QMetaType((QMetaType *)local_58);
                  **(undefined8 **)param_4 = local_58[0];
                }
                goto LAB_0013ed6d;
              }
              if (param_3 < 0x82) {
                if (param_3 == 0x80) {
                  if (**(int **)(param_4 + 8) == 0) {
                    puVar1 = *(undefined8 **)param_4;
                    uVar7 = QMetaType::fromType<QDBusObjectPath>();
                    *puVar1 = uVar7;
                  }
                  else if (**(int **)(param_4 + 8) == 1) {
                    puVar1 = *(undefined8 **)param_4;
                    uVar7 = QMetaType::fromType<QMap<QString,QMap<QString,QVariant>>>();
                    *puVar1 = uVar7;
                  }
                  else {
                    local_58[0] = 0;
                    QMetaType::QMetaType((QMetaType *)local_58);
                    **(undefined8 **)param_4 = local_58[0];
                  }
                  goto LAB_0013ed6d;
                }
                if (param_3 < 0x81) {
                  if (param_3 == 0x7d) {
                    if (**(int **)(param_4 + 8) == 0) {
                      puVar1 = *(undefined8 **)param_4;
                      uVar7 = QMetaType::fromType<QDBusObjectPath>();
                      *puVar1 = uVar7;
                    }
                    else if (**(int **)(param_4 + 8) == 1) {
                      puVar1 = *(undefined8 **)param_4;
                      uVar7 = QMetaType::fromType<QMap<QString,QMap<QString,QVariant>>>();
                      *puVar1 = uVar7;
                    }
                    else {
                      local_58[0] = 0;
                      QMetaType::QMetaType((QMetaType *)local_58);
                      **(undefined8 **)param_4 = local_58[0];
                    }
                    goto LAB_0013ed6d;
                  }
                  if (param_3 == 0x7e) {
                    if (**(int **)(param_4 + 8) == 0) {
                      puVar1 = *(undefined8 **)param_4;
                      uVar7 = QMetaType::fromType<QDBusObjectPath>();
                      *puVar1 = uVar7;
                    }
                    else {
                      local_58[0] = 0;
                      QMetaType::QMetaType((QMetaType *)local_58);
                      **(undefined8 **)param_4 = local_58[0];
                    }
                    goto LAB_0013ed6d;
                  }
                }
              }
            }
          }
        }
      }
      local_58[0] = 0;
      QMetaType::QMetaType((QMetaType *)local_58);
      **(undefined8 **)param_4 = local_58[0];
    }
  }
LAB_0013ed6d:
  if (((param_2 != 5) ||
      (((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                             (param_4,(void **)networkChanged,(_func_void *)0x0,0), !bVar3 &&
          (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                             (param_4,(void **)vpnStateChanged,(_func_void *)0x0,1), !bVar3)) &&
         (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                            (param_4,(void **)wifiChanged,(_func_void *)0x0,2), !bVar3)) &&
        (((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)batteryChanged,(_func_void *)0x0,3), !bVar3 &&
            (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)powerProfileChanged,(_func_void *)0x0,4), !bVar3))
           && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                  (param_4,(void **)powerChanged,(_func_void *)0x0,5), !bVar3 &&
               ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                   (param_4,(void **)thermalPressureChanged,(_func_void *)0x0,6),
                !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                             (param_4,(void **)sentinelTempsChanged,
                                              (_func_void *)0x0,7), !bVar3)))))) &&
          (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                             (param_4,(void **)sentinelFansChanged,(_func_void *)0x0,8), !bVar3)) &&
         ((((bVar3 = QtMocHelpers::
                     indexOfMethod<void(Lelan::*)(QString_const&,QString_const&,QString_const&)>
                               (param_4,(void **)driverMissing,
                                (_func_void_QString_ptr_QString_ptr_QString_ptr *)0x0,9), !bVar3 &&
            (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)statsChanged,(_func_void *)0x0,10), !bVar3)) &&
           (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                              (param_4,(void **)audioChanged,(_func_void *)0x0,0xb), !bVar3)) &&
          ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                              (param_4,(void **)audioDeviceChanged,(_func_void *)0x0,0xc), !bVar3 &&
           (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                              (param_4,(void **)audioDevicesChanged,(_func_void *)0x0,0xd), !bVar3))
          )))))) &&
       ((((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)bluetoothAudioDeviceChanged,(_func_void *)0x0,0xe),
            !bVar3 && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                          (param_4,(void **)onAudioVolumeUpdated,(_func_void *)0x0,
                                           0xf), !bVar3 &&
                       (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                          (param_4,(void **)onAudioMuteUpdated,(_func_void *)0x0,
                                           0x10), !bVar3)))) &&
           (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                              (param_4,(void **)onFallbackSinkUpdated,(_func_void *)0x0,0x11),
           !bVar3)) &&
          (((((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                   (param_4,(void **)appStreamsChanged,(_func_void *)0x0,0x12),
                !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                             (param_4,(void **)mediaChanged,(_func_void *)0x0,0x13),
                          !bVar3)) &&
               (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                  (param_4,(void **)mediaPositionChanged,(_func_void *)0x0,0x14),
               !bVar3)) &&
              ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                  (param_4,(void **)appNameChanged,(_func_void *)0x0,0x15), !bVar3
               && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                     (param_4,(void **)appIconChanged,(_func_void *)0x0,0x16),
                  !bVar3)))) &&
             ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                 (param_4,(void **)durationChanged,(_func_void *)0x0,0x17), !bVar3
              && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                     (param_4,(void **)bluetoothChanged,(_func_void *)0x0,0x18),
                  !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                               (param_4,(void **)diskChanged,(_func_void *)0x0,0x19)
                            , !bVar3)))))) &&
            (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                 (param_4,(void **)diskDeviceChanged,(_func_void *)0x0,0x1a), !bVar3
              && (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                      (param_4,(void **)diskMountChanged,(_func_void *)0x0,0x1b),
                   !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                (param_4,(void **)storageChanged,(_func_void *)0x0,
                                                 0x1c), !bVar3)) &&
                  (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                     (param_4,(void **)kickassChanged,(_func_void *)0x0,0x1d),
                  !bVar3)))) &&
             (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                  (param_4,(void **)kickassStatusChanged,(_func_void *)0x0,0x1e),
               !bVar3 && (bVar3 = QtMocHelpers::
                                  indexOfMethod<void(Lelan::*)(QString_const&,QString_const&)>
                                            (param_4,(void **)kickassSiteBlocked,
                                             (_func_void_QString_ptr_QString_ptr *)0x0,0x1f), !bVar3
                         )) &&
              ((bVar3 = QtMocHelpers::
                        indexOfMethod<void(Lelan::*)(QString_const&,QString_const&,int)>
                                  (param_4,(void **)kickassThreatBlocked,
                                   (_func_void_QString_ptr_QString_ptr_int *)0x0,0x20), !bVar3 &&
               ((bVar3 = QtMocHelpers::
                         indexOfMethod<void(Lelan::*)(QString_const&,QString_const&,QString_const&)>
                                   (param_4,(void **)kickassThreatBehavioral,
                                    (_func_void_QString_ptr_QString_ptr_QString_ptr *)0x0,0x21),
                !bVar3 && (bVar3 = QtMocHelpers::
                                   indexOfMethod<void(Lelan::*)(QString_const&,QString_const&)>
                                             (param_4,(void **)kickassNetworkAlert,
                                              (_func_void_QString_ptr_QString_ptr *)0x0,0x22),
                          !bVar3)))))))))) &&
           (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                              (param_4,(void **)packageStateChanged,(_func_void *)0x0,0x23), !bVar3)
           ))) && (((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                         (param_4,(void **)updatesChanged,(_func_void *)0x0,0x24),
                      !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                   (param_4,(void **)clockChanged,(_func_void *)0x0,
                                                    0x25), !bVar3)) &&
                     (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                        (param_4,(void **)timeJumped,(_func_void *)0x0,0x26), !bVar3
                     )) && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)(unsigned_long_long)>
                                               (param_4,(void **)pulse,(_func_void_ulonglong *)0x0,
                                                0x27), !bVar3 &&
                            (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                               (param_4,(void **)leanSleeping,(_func_void *)0x0,0x28
                                               ), !bVar3)))) &&
                   ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                       (param_4,(void **)leanWaking,(_func_void *)0x0,0x29), !bVar3
                    && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                           (param_4,(void **)dateTimeChanged,(_func_void *)0x0,0x2a)
                        , !bVar3 &&
                        (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                           (param_4,(void **)timezoneChanged,(_func_void *)0x0,0x2b)
                        , !bVar3)))))))) &&
        (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                             (param_4,(void **)weatherChanged,(_func_void *)0x0,0x2c), !bVar3 &&
          (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)placeNameChanged,(_func_void *)0x0,0x2d), !bVar3 &&
            (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                               (param_4,(void **)moonPositionChanged,(_func_void *)0x0,0x2e), !bVar3
            )) && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                     (param_4,(void **)trayChanged,(_func_void *)0x0,0x2f), !bVar3))
          )) && ((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                      (param_4,(void **)onTrayBadgeChanged,(_func_void *)0x0,0x30),
                   !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                (param_4,(void **)onTrayPercentChanged,
                                                 (_func_void *)0x0,0x31), !bVar3)) &&
                  ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                      (param_4,(void **)themeChanged,(_func_void *)0x0,0x32), !bVar3
                   && ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                          (param_4,(void **)darkModeChanged,(_func_void *)0x0,0x33),
                       !bVar3 && (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)onAccentColorChanged,
                                                     (_func_void *)0x0,0x34), !bVar3)))))) &&
                 ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                     (param_4,(void **)wallpaperChanged,(_func_void *)0x0,0x35),
                  !bVar3 && ((((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)systemFontChanged,
                                                     (_func_void *)0x0,0x36), !bVar3 &&
                                 (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)slideshowChanged,
                                                     (_func_void *)0x0,0x37), !bVar3)) &&
                                (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                   (param_4,(void **)filigreePalettesChanged,
                                                    (_func_void *)0x0,0x38), !bVar3)) &&
                               (((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)onSessionActiveChanged,
                                                     (_func_void *)0x0,0x39), !bVar3 &&
                                 (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)vtActiveChanged,
                                                     (_func_void *)0x0,0x3a), !bVar3)) &&
                                ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)screensaverChanged,
                                                     (_func_void *)0x0,0x3b), !bVar3 &&
                                 ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                     (param_4,(void **)screenConfigChanged,
                                                      (_func_void *)0x0,0x3c), !bVar3 &&
                                  (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                     (param_4,(void **)screenGeometryChanged,
                                                      (_func_void *)0x0,0x3d), !bVar3)))))))) &&
                              (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                 (param_4,(void **)hostnameChanged,(_func_void *)0x0
                                                  ,0x3e), !bVar3)) &&
                             ((((((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                     (param_4,(void **)localeChanged,
                                                      (_func_void *)0x0,0x3f), !bVar3 &&
                                  (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                     (param_4,(void **)userNameChanged,
                                                      (_func_void *)0x0,0x40), !bVar3)) &&
                                 (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)usersChanged,(_func_void *)0x0
                                                     ,0x41), !bVar3)) &&
                                ((bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)printersChanged,
                                                     (_func_void *)0x0,0x42), !bVar3 &&
                                 (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                    (param_4,(void **)notificationsChanged,
                                                     (_func_void *)0x0,0x43), !bVar3)))) &&
                               (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                  (param_4,(void **)animLevelChanged,
                                                   (_func_void *)0x0,0x44), !bVar3)) &&
                              (bVar3 = QtMocHelpers::indexOfMethod<void(Lelan::*)()>
                                                 (param_4,(void **)hardwareTierChanged,
                                                  (_func_void *)0x0,0x45), !bVar3)))))))))))))))) &&
     (param_2 == 1)) {
    this = *(QMap<QString,QVariant> **)param_4;
    if (param_3 == 0x40) {
      QVar4 = (QMap<QString,QVariant>)mediaPlaying();
      *this = QVar4;
    }
    else if (param_3 < 0x41) {
      if (param_3 == 0x3f) {
        uVar7 = mediaPosition();
        *(undefined8 *)this = uVar7;
      }
      else if (param_3 < 0x40) {
        if (param_3 == 0x3e) {
          uVar7 = mediaDuration();
          *(undefined8 *)this = uVar7;
        }
        else if (param_3 < 0x3f) {
          if (param_3 == 0x3d) {
            mediaTrackId((Lelan *)local_58);
            QString::operator=((QString *)this,(QString *)local_58);
            QString::~QString((QString *)local_58);
          }
          else if (param_3 < 0x3e) {
            if (param_3 == 0x3c) {
              mediaArtUrl((Lelan *)local_58);
              QString::operator=((QString *)this,(QString *)local_58);
              QString::~QString((QString *)local_58);
            }
            else if (param_3 < 0x3d) {
              if (param_3 == 0x3b) {
                mediaAlbum((Lelan *)local_58);
                QString::operator=((QString *)this,(QString *)local_58);
                QString::~QString((QString *)local_58);
              }
              else if (param_3 < 0x3c) {
                if (param_3 == 0x3a) {
                  mediaArtist((Lelan *)local_58);
                  QString::operator=((QString *)this,(QString *)local_58);
                  QString::~QString((QString *)local_58);
                }
                else if (param_3 < 0x3b) {
                  if (param_3 == 0x39) {
                    mediaTitle((Lelan *)local_58);
                    QString::operator=((QString *)this,(QString *)local_58);
                    QString::~QString((QString *)local_58);
                  }
                  else if (param_3 < 0x3a) {
                    if (param_3 == 0x38) {
                      QVar4 = (QMap<QString,QVariant>)networkUp(param_1);
                      *this = QVar4;
                    }
                    else if (param_3 < 0x39) {
                      if (param_3 == 0x37) {
                        QVar4 = (QMap<QString,QVariant>)networkOnline(param_1);
                        *this = QVar4;
                      }
                      else if (param_3 < 0x38) {
                        if (param_3 == 0x36) {
                          QVar4 = (QMap<QString,QVariant>)hasBattery(param_1);
                          *this = QVar4;
                        }
                        else if (param_3 < 0x37) {
                          if (param_3 == 0x35) {
                            QVar4 = (QMap<QString,QVariant>)batteryCharging(param_1);
                            *this = QVar4;
                          }
                          else if (param_3 < 0x36) {
                            if (param_3 == 0x34) {
                              uVar7 = batteryPercent(param_1);
                              *(undefined8 *)this = uVar7;
                            }
                            else if (param_3 < 0x35) {
                              if (param_3 == 0x33) {
                                hardwareTier();
                                QString::operator=((QString *)this,(QString *)local_58);
                                QString::~QString((QString *)local_58);
                              }
                              else if (param_3 < 0x34) {
                                if (param_3 == 0x32) {
                                  QVar4 = (QMap<QString,QVariant>)reduceMotion(param_1);
                                  *this = QVar4;
                                }
                                else if (param_3 < 0x33) {
                                  if (param_3 == 0x31) {
                                    uVar5 = animLevel(param_1);
                                    *(undefined4 *)this = uVar5;
                                  }
                                  else if (param_3 < 0x32) {
                                    if (param_3 == 0x30) {
                                      notifications();
                                      QList<QVariant>::operator=
                                                ((QList<QVariant> *)this,(QList *)local_58);
                                      QList<QVariant>::~QList((QList<QVariant> *)local_58);
                                    }
                                    else if (param_3 < 0x31) {
                                      if (param_3 == 0x2f) {
                                        kickass();
                                        QMap<QString,QVariant>::operator=(this,(QMap *)local_58);
                                        QMap<QString,QVariant>::~QMap
                                                  ((QMap<QString,QVariant> *)local_58);
                                      }
                                      else if (param_3 < 0x30) {
                                        if (param_3 == 0x2e) {
                                          locale();
                                          QString::operator=((QString *)this,(QString *)local_58);
                                          QString::~QString((QString *)local_58);
                                        }
                                        else if (param_3 < 0x2f) {
                                          if (param_3 == 0x2d) {
                                            hostname();
                                            QString::operator=((QString *)this,(QString *)local_58);
                                            QString::~QString((QString *)local_58);
                                          }
                                          else if (param_3 < 0x2e) {
                                            if (param_3 == 0x2c) {
                                              QVar4 = (QMap<QString,QVariant>)screensaver(param_1);
                                              *this = QVar4;
                                            }
                                            else if (param_3 < 0x2d) {
                                              if (param_3 == 0x2b) {
                                                uVar5 = vtActive(param_1);
                                                *(undefined4 *)this = uVar5;
                                              }
                                              else if (param_3 < 0x2c) {
                                                if (param_3 == 0x2a) {
                                                  QVar4 = (QMap<QString,QVariant>)
                                                          sessionActive(param_1);
                                                  *this = QVar4;
                                                }
                                                else if (param_3 < 0x2b) {
                                                  if (param_3 == 0x29) {
                                                    tray();
                                                    QList<QVariant>::operator=
                                                              ((QList<QVariant> *)this,
                                                               (QList *)local_58);
                                                    QList<QVariant>::~QList
                                                              ((QList<QVariant> *)local_58);
                                                  }
                                                  else if (param_3 < 0x2a) {
                                                    if (param_3 == 0x28) {
                                                      QVar4 = (QMap<QString,QVariant>)
                                                              locating(param_1);
                                                      *this = QVar4;
                                                    }
                                                    else if (param_3 < 0x29) {
                                                      if (param_3 == 0x27) {
                                                        timezone();
                                                        QString::operator=((QString *)this,
                                                                           (QString *)local_58);
                                                        QString::~QString((QString *)local_58);
                                                      }
                                                      else if (param_3 < 0x28) {
                                                        if (param_3 == 0x26) {
                                                          clock();
                                                          QMap<QString,QVariant>::operator=
                                                                    (this,(QMap *)local_58);
                                                          QMap<QString,QVariant>::~QMap
                                                                    ((QMap<QString,QVariant> *)
                                                                     local_58);
                                                        }
                                                        else if (param_3 < 0x27) {
                                                          if (param_3 == 0x25) {
                                                            placeName();
                                                            QString::operator=((QString *)this,
                                                                               (QString *)local_58);
                                                            QString::~QString((QString *)local_58);
                                                          }
                                                          else if (param_3 < 0x26) {
                                                            if (param_3 == 0x24) {
                                                              location();
                                                              QMap<QString,QVariant>::operator=
                                                                        (this,(QMap *)local_58);
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_58);
                                                            }
                                                            else if (param_3 < 0x25) {
                                                              if (param_3 == 0x23) {
                                                                filigreePalette();
                                                                QMap<QString,QVariant>::operator=
                                                                          (this,(QMap *)local_58);
                                                                QMap<QString,QVariant>::~QMap
                                                                          ((QMap<QString,QVariant> *
                                                                           )local_58);
                                                              }
                                                              else if (param_3 < 0x24) {
                                                                if (param_3 == 0x22) {
                                                                  systemFont();
                                                                  QString::operator=((QString *)this
                                                                                     ,(QString *)
                                                                                      local_58);
                                                                  QString::~QString((QString *)
                                                                                    local_58);
                                                                }
                                                                else if (param_3 < 0x23) {
                                                                  if (param_3 == 0x21) {
                                                                    accentColor();
                                                                    QString::operator=((QString *)
                                                                                       this,(QString
                                                                                             *)
                                                  local_58);
                                                  QString::~QString((QString *)local_58);
                                                  }
                                                  else if (param_3 < 0x22) {
                                                    if (param_3 == 0x20) {
                                                      QVar4 = (QMap<QString,QVariant>)
                                                              darkMode(param_1);
                                                      *this = QVar4;
                                                    }
                                                    else if (param_3 < 0x21) {
                                                      if (param_3 == 0x1f) {
                                                        updates();
                                                        QMap<QString,QVariant>::operator=
                                                                  (this,(QMap *)local_58);
                                                        QMap<QString,QVariant>::~QMap
                                                                  ((QMap<QString,QVariant> *)
                                                                   local_58);
                                                      }
                                                      else if (param_3 < 0x20) {
                                                        if (param_3 == 0x1e) {
                                                          disk();
                                                          QMap<QString,QVariant>::operator=
                                                                    (this,(QMap *)local_58);
                                                          QMap<QString,QVariant>::~QMap
                                                                    ((QMap<QString,QVariant> *)
                                                                     local_58);
                                                        }
                                                        else if (param_3 < 0x1f) {
                                                          if (param_3 == 0x1d) {
                                                            removableVolumes();
                                                            QList<QVariant>::operator=
                                                                      ((QList<QVariant> *)this,
                                                                       (QList *)local_58);
                                                            QList<QVariant>::~QList
                                                                      ((QList<QVariant> *)local_58);
                                                          }
                                                          else if (param_3 < 0x1e) {
                                                            if (param_3 == 0x1c) {
                                                              bluetoothAudioDevice();
                                                              QMap<QString,QVariant>::operator=
                                                                        (this,(QMap *)local_58);
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_58);
                                                            }
                                                            else if (param_3 < 0x1d) {
                                                              if (param_3 == 0x1b) {
                                                                bluetoothDevices();
                                                                QList<QVariant>::operator=
                                                                          ((QList<QVariant> *)this,
                                                                           (QList *)local_58);
                                                                QList<QVariant>::~QList
                                                                          ((QList<QVariant> *)
                                                                           local_58);
                                                              }
                                                              else if (param_3 < 0x1c) {
                                                                if (param_3 == 0x1a) {
                                                                  QVar4 = (QMap<QString,QVariant>)
                                                                          bluetoothDiscoverable
                                                                                    (param_1);
                                                                  *this = QVar4;
                                                                }
                                                                else if (param_3 < 0x1b) {
                                                                  if (param_3 == 0x19) {
                                                                    QVar4 = (QMap<QString,QVariant>)
                                                                            bluetoothEnabled(param_1
                                                  );
                                                  *this = QVar4;
                                                  }
                                                  else if (param_3 < 0x1a) {
                                                    if (param_3 == 0x18) {
                                                      bluetooth();
                                                      QMap<QString,QVariant>::operator=
                                                                (this,(QMap *)local_58);
                                                      QMap<QString,QVariant>::~QMap
                                                                ((QMap<QString,QVariant> *)local_58)
                                                      ;
                                                    }
                                                    else if (param_3 < 0x19) {
                                                      if (param_3 == 0x17) {
                                                        QVar4 = (QMap<QString,QVariant>)
                                                                mediaActive(param_1);
                                                        *this = QVar4;
                                                      }
                                                      else if (param_3 < 0x18) {
                                                        if (param_3 == 0x16) {
                                                          media();
                                                          QMap<QString,QVariant>::operator=
                                                                    (this,(QMap *)local_58);
                                                          QMap<QString,QVariant>::~QMap
                                                                    ((QMap<QString,QVariant> *)
                                                                     local_58);
                                                        }
                                                        else if (param_3 < 0x17) {
                                                          if (param_3 == 0x15) {
                                                            defaultSourceName();
                                                            QString::operator=((QString *)this,
                                                                               (QString *)local_58);
                                                            QString::~QString((QString *)local_58);
                                                          }
                                                          else if (param_3 < 0x16) {
                                                            if (param_3 == 0x14) {
                                                              inputDevices();
                                                              QList<QVariant>::operator=
                                                                        ((QList<QVariant> *)this,
                                                                         (QList *)local_58);
                                                              QList<QVariant>::~QList
                                                                        ((QList<QVariant> *)local_58
                                                                        );
                                                            }
                                                            else if (param_3 < 0x15) {
                                                              if (param_3 == 0x13) {
                                                                outputDevices();
                                                                QList<QVariant>::operator=
                                                                          ((QList<QVariant> *)this,
                                                                           (QList *)local_58);
                                                                QList<QVariant>::~QList
                                                                          ((QList<QVariant> *)
                                                                           local_58);
                                                              }
                                                              else if (param_3 < 0x14) {
                                                                if (param_3 == 0x12) {
                                                                  appStreams();
                                                                  QList<QVariant>::operator=
                                                                            ((QList<QVariant> *)this
                                                                             ,(QList *)local_58);
                                                                  QList<QVariant>::~QList
                                                                            ((QList<QVariant> *)
                                                                             local_58);
                                                                }
                                                                else if (param_3 < 0x13) {
                                                                  if (param_3 == 0x11) {
                                                                    QVar4 = (QMap<QString,QVariant>)
                                                                            muted(param_1);
                                                                    *this = QVar4;
                                                                  }
                                                                  else if (param_3 < 0x12) {
                                                                    if (param_3 == 0x10) {
                                                                      uVar5 = balance(param_1);
                                                                      *(undefined4 *)this = uVar5;
                                                                    }
                                                                    else if (param_3 < 0x11) {
                                                                      if (param_3 == 0xf) {
                                                                        uVar5 = volume(param_1);
                                                                        *(undefined4 *)this = uVar5;
                                                                      }
                                                                      else if (param_3 < 0x10) {
                                                                        if (param_3 == 0xe) {
                                                                          audio();
                                                                          QMap<QString,QVariant>::
                                                                          operator=(this,(QMap *)
                                                  local_58);
                                                  QMap<QString,QVariant>::~QMap
                                                            ((QMap<QString,QVariant> *)local_58);
                                                  }
                                                  else if (param_3 < 0xf) {
                                                    if (param_3 == 0xd) {
                                                      sentinelFans();
                                                      QMap<QString,QVariant>::operator=
                                                                (this,(QMap *)local_58);
                                                      QMap<QString,QVariant>::~QMap
                                                                ((QMap<QString,QVariant> *)local_58)
                                                      ;
                                                    }
                                                    else if (param_3 < 0xe) {
                                                      if (param_3 == 0xc) {
                                                        sentinelTemps();
                                                        QMap<QString,QVariant>::operator=
                                                                  (this,(QMap *)local_58);
                                                        QMap<QString,QVariant>::~QMap
                                                                  ((QMap<QString,QVariant> *)
                                                                   local_58);
                                                      }
                                                      else if (param_3 < 0xd) {
                                                        if (param_3 == 0xb) {
                                                          uVar5 = thermalPressure(param_1);
                                                          *(undefined4 *)this = uVar5;
                                                        }
                                                        else if (param_3 < 0xc) {
                                                          if (param_3 == 10) {
                                                            powerProfile();
                                                            QString::operator=((QString *)this,
                                                                               (QString *)local_58);
                                                            QString::~QString((QString *)local_58);
                                                          }
                                                          else if (param_3 < 0xb) {
                                                            if (param_3 == 9) {
                                                              battery();
                                                              QMap<QString,QVariant>::operator=
                                                                        (this,(QMap *)local_58);
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_58);
                                                            }
                                                            else if (param_3 < 10) {
                                                              if (param_3 == 8) {
                                                                printers();
                                                                QList<QVariant>::operator=
                                                                          ((QList<QVariant> *)this,
                                                                           (QList *)local_58);
                                                                QList<QVariant>::~QList
                                                                          ((QList<QVariant> *)
                                                                           local_58);
                                                              }
                                                              else if (param_3 < 9) {
                                                                if (param_3 == 7) {
                                                                  userName();
                                                                  QString::operator=((QString *)this
                                                                                     ,(QString *)
                                                                                      local_58);
                                                                  QString::~QString((QString *)
                                                                                    local_58);
                                                                }
                                                                else if (param_3 < 8) {
                                                                  if (param_3 == 6) {
                                                                    users();
                                                                    QList<QVariant>::operator=
                                                                              ((QList<QVariant> *)
                                                                               this,(QList *)
                                                  local_58);
                                                  QList<QVariant>::~QList
                                                            ((QList<QVariant> *)local_58);
                                                  }
                                                  else if (param_3 < 7) {
                                                    if (param_3 == 5) {
                                                      vpnConnections();
                                                      QList<QVariant>::operator=
                                                                ((QList<QVariant> *)this,
                                                                 (QList *)local_58);
                                                      QList<QVariant>::~QList
                                                                ((QList<QVariant> *)local_58);
                                                    }
                                                    else if (param_3 < 6) {
                                                      if (param_3 == 4) {
                                                        activeNetwork();
                                                        QMap<QString,QVariant>::operator=
                                                                  (this,(QMap *)local_58);
                                                        QMap<QString,QVariant>::~QMap
                                                                  ((QMap<QString,QVariant> *)
                                                                   local_58);
                                                      }
                                                      else if (param_3 < 5) {
                                                        if (param_3 == 3) {
                                                          wifiNetworks();
                                                          QList<QVariant>::operator=
                                                                    ((QList<QVariant> *)this,
                                                                     (QList *)local_58);
                                                          QList<QVariant>::~QList
                                                                    ((QList<QVariant> *)local_58);
                                                        }
                                                        else if (param_3 < 4) {
                                                          if (param_3 == 2) {
                                                            QVar4 = (QMap<QString,QVariant>)
                                                                    wifiEnabled(param_1);
                                                            *this = QVar4;
                                                          }
                                                          else if (param_3 < 3) {
                                                            if (param_3 == 0) {
                                                              network();
                                                              QMap<QString,QVariant>::operator=
                                                                        (this,(QMap *)local_58);
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_58);
                                                            }
                                                            else if (param_3 == 1) {
                                                              vpn();
                                                              QMap<QString,QVariant>::operator=
                                                                        (this,(QMap *)local_58);
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_58);
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
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00141148  Lelan::metaObject

/* Lelan::metaObject() const */

undefined1 * __thiscall Lelan::metaObject(Lelan *this)

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



// ==== 00141190  Lelan::qt_metacast

/* Lelan::qt_metacast(char const*) */

Lelan * __thiscall Lelan::qt_metacast(Lelan *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (Lelan *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"Lelan");
    if (iVar1 != 0) {
      this = (Lelan *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 001411e4  Lelan::qt_metacall

/* Lelan::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall Lelan::qt_metacall(Lelan *this,int param_2,undefined4 param_3,undefined8 param_4)

{
  undefined4 local_18;
  
  local_18 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_18) {
    if (param_2 == 0) {
      if (local_18 < 0xb2) {
        qt_static_metacall(this,0,local_18,param_4);
      }
      local_18 = local_18 + -0xb2;
    }
    if (param_2 == 7) {
      if (local_18 < 0xb2) {
        qt_static_metacall(this,7,local_18,param_4);
      }
      local_18 = local_18 + -0xb2;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_18,param_4);
      local_18 = local_18 + -0x41;
    }
  }
  return local_18;
}



// ==== 001412b6  Lelan::networkChanged

/* Lelan::networkChanged() */

void __thiscall Lelan::networkChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 001412e2  Lelan::vpnStateChanged

/* Lelan::vpnStateChanged() */

void __thiscall Lelan::vpnStateChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0014130e  Lelan::wifiChanged

/* Lelan::wifiChanged() */

void __thiscall Lelan::wifiChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 0014133a  Lelan::batteryChanged

/* Lelan::batteryChanged() */

void __thiscall Lelan::batteryChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,3,(void **)0x0);
  return;
}



// ==== 00141366  Lelan::powerProfileChanged

/* Lelan::powerProfileChanged() */

void __thiscall Lelan::powerProfileChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,4,(void **)0x0);
  return;
}



// ==== 00141392  Lelan::powerChanged

/* Lelan::powerChanged() */

void __thiscall Lelan::powerChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 001413be  Lelan::thermalPressureChanged

/* Lelan::thermalPressureChanged() */

void __thiscall Lelan::thermalPressureChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,6,(void **)0x0);
  return;
}



// ==== 001413ea  Lelan::sentinelTempsChanged

/* Lelan::sentinelTempsChanged() */

void __thiscall Lelan::sentinelTempsChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,7,(void **)0x0);
  return;
}



// ==== 00141416  Lelan::sentinelFansChanged

/* Lelan::sentinelFansChanged() */

void __thiscall Lelan::sentinelFansChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,8,(void **)0x0);
  return;
}



// ==== 00141442  Lelan::driverMissing

/* Lelan::driverMissing(QString const&, QString const&, QString const&) */

void __thiscall Lelan::driverMissing(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
  QMetaObject::activate<void,QString,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,9,(void *)0x0,param_1,param_2,param_3);
  return;
}



// ==== 00141494  Lelan::statsChanged

/* Lelan::statsChanged() */

void __thiscall Lelan::statsChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,10,(void **)0x0);
  return;
}



// ==== 001414c0  Lelan::audioChanged

/* Lelan::audioChanged() */

void __thiscall Lelan::audioChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xb,(void **)0x0);
  return;
}



// ==== 001414ec  Lelan::audioDeviceChanged

/* Lelan::audioDeviceChanged() */

void __thiscall Lelan::audioDeviceChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xc,(void **)0x0);
  return;
}



// ==== 00141518  Lelan::audioDevicesChanged

/* Lelan::audioDevicesChanged() */

void __thiscall Lelan::audioDevicesChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xd,(void **)0x0);
  return;
}



// ==== 00141544  Lelan::bluetoothAudioDeviceChanged

/* Lelan::bluetoothAudioDeviceChanged() */

void __thiscall Lelan::bluetoothAudioDeviceChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xe,(void **)0x0);
  return;
}



// ==== 00141570  Lelan::onAudioVolumeUpdated

/* Lelan::onAudioVolumeUpdated() */

void __thiscall Lelan::onAudioVolumeUpdated(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xf,(void **)0x0);
  return;
}



// ==== 0014159c  Lelan::onAudioMuteUpdated

/* Lelan::onAudioMuteUpdated() */

void __thiscall Lelan::onAudioMuteUpdated(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x10,(void **)0x0);
  return;
}



// ==== 001415c8  Lelan::onFallbackSinkUpdated

/* Lelan::onFallbackSinkUpdated() */

void __thiscall Lelan::onFallbackSinkUpdated(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x11,(void **)0x0);
  return;
}



// ==== 001415f4  Lelan::appStreamsChanged

/* Lelan::appStreamsChanged() */

void __thiscall Lelan::appStreamsChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x12,(void **)0x0);
  return;
}



// ==== 00141620  Lelan::mediaChanged

/* Lelan::mediaChanged() */

void __thiscall Lelan::mediaChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x13,(void **)0x0);
  return;
}



// ==== 0014164c  Lelan::mediaPositionChanged

/* Lelan::mediaPositionChanged() */

void __thiscall Lelan::mediaPositionChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x14,(void **)0x0);
  return;
}



// ==== 00141678  Lelan::appNameChanged

/* Lelan::appNameChanged() */

void __thiscall Lelan::appNameChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x15,(void **)0x0);
  return;
}



// ==== 001416a4  Lelan::appIconChanged

/* Lelan::appIconChanged() */

void __thiscall Lelan::appIconChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x16,(void **)0x0);
  return;
}



// ==== 001416d0  Lelan::durationChanged

/* Lelan::durationChanged() */

void __thiscall Lelan::durationChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x17,(void **)0x0);
  return;
}



// ==== 001416fc  Lelan::bluetoothChanged

/* Lelan::bluetoothChanged() */

void __thiscall Lelan::bluetoothChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x18,(void **)0x0);
  return;
}



// ==== 00141728  Lelan::diskChanged

/* Lelan::diskChanged() */

void __thiscall Lelan::diskChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x19,(void **)0x0);
  return;
}



// ==== 00141754  Lelan::diskDeviceChanged

/* Lelan::diskDeviceChanged() */

void __thiscall Lelan::diskDeviceChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x1a,(void **)0x0);
  return;
}



// ==== 00141780  Lelan::diskMountChanged

/* Lelan::diskMountChanged() */

void __thiscall Lelan::diskMountChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x1b,(void **)0x0);
  return;
}



// ==== 001417ac  Lelan::storageChanged

/* Lelan::storageChanged() */

void __thiscall Lelan::storageChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x1c,(void **)0x0);
  return;
}



// ==== 001417d8  Lelan::kickassChanged

/* Lelan::kickassChanged() */

void __thiscall Lelan::kickassChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x1d,(void **)0x0);
  return;
}



// ==== 00141804  Lelan::kickassStatusChanged

/* Lelan::kickassStatusChanged() */

void __thiscall Lelan::kickassStatusChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x1e,(void **)0x0);
  return;
}



// ==== 00141830  Lelan::kickassSiteBlocked

/* Lelan::kickassSiteBlocked(QString const&, QString const&) */

void __thiscall Lelan::kickassSiteBlocked(Lelan *this,QString *param_1,QString *param_2)

{
  QMetaObject::activate<void,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x1f,(void *)0x0,param_1,param_2);
  return;
}



// ==== 00141872  Lelan::kickassThreatBlocked

/* Lelan::kickassThreatBlocked(QString const&, QString const&, int) */

void __thiscall
Lelan::kickassThreatBlocked(Lelan *this,QString *param_1,QString *param_2,int param_3)

{
  int local_24;
  QString *local_20;
  QString *local_18;
  Lelan *local_10;
  
  local_24 = param_3;
  local_20 = param_2;
  local_18 = param_1;
  local_10 = this;
  QMetaObject::activate<void,QString,QString,int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x20,(void *)0x0,param_1,param_2,
             &local_24);
  return;
}



// ==== 001418c4  Lelan::kickassThreatBehavioral

/* Lelan::kickassThreatBehavioral(QString const&, QString const&, QString const&) */

void __thiscall
Lelan::kickassThreatBehavioral(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
  QMetaObject::activate<void,QString,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x21,(void *)0x0,param_1,param_2,
             param_3);
  return;
}



// ==== 00141916  Lelan::kickassNetworkAlert

/* Lelan::kickassNetworkAlert(QString const&, QString const&) */

void __thiscall Lelan::kickassNetworkAlert(Lelan *this,QString *param_1,QString *param_2)

{
  QMetaObject::activate<void,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x22,(void *)0x0,param_1,param_2);
  return;
}



// ==== 00141958  Lelan::packageStateChanged

/* Lelan::packageStateChanged() */

void __thiscall Lelan::packageStateChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x23,(void **)0x0);
  return;
}



// ==== 00141984  Lelan::updatesChanged

/* Lelan::updatesChanged() */

void __thiscall Lelan::updatesChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x24,(void **)0x0);
  return;
}



// ==== 001419b0  Lelan::clockChanged

/* Lelan::clockChanged() */

void __thiscall Lelan::clockChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x25,(void **)0x0);
  return;
}



// ==== 001419dc  Lelan::timeJumped

/* Lelan::timeJumped() */

void __thiscall Lelan::timeJumped(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x26,(void **)0x0);
  return;
}



// ==== 00141a08  Lelan::pulse

/* Lelan::pulse(unsigned long long) */

void __thiscall Lelan::pulse(Lelan *this,ulonglong param_1)

{
  ulonglong local_18;
  Lelan *local_10;
  
  local_18 = param_1;
  local_10 = this;
  QMetaObject::activate<void,unsigned_long_long>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x27,(void *)0x0,&local_18);
  return;
}



// ==== 00141a40  Lelan::leanSleeping

/* Lelan::leanSleeping() */

void __thiscall Lelan::leanSleeping(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x28,(void **)0x0);
  return;
}



// ==== 00141a6c  Lelan::leanWaking

/* Lelan::leanWaking() */

void __thiscall Lelan::leanWaking(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x29,(void **)0x0);
  return;
}



// ==== 00141a98  Lelan::dateTimeChanged

/* Lelan::dateTimeChanged() */

void __thiscall Lelan::dateTimeChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2a,(void **)0x0);
  return;
}



// ==== 00141ac4  Lelan::timezoneChanged

/* Lelan::timezoneChanged() */

void __thiscall Lelan::timezoneChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2b,(void **)0x0);
  return;
}



// ==== 00141af0  Lelan::weatherChanged

/* Lelan::weatherChanged() */

void __thiscall Lelan::weatherChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2c,(void **)0x0);
  return;
}



// ==== 00141b1c  Lelan::placeNameChanged

/* Lelan::placeNameChanged() */

void __thiscall Lelan::placeNameChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2d,(void **)0x0);
  return;
}



// ==== 00141b48  Lelan::moonPositionChanged

/* Lelan::moonPositionChanged() */

void __thiscall Lelan::moonPositionChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2e,(void **)0x0);
  return;
}



// ==== 00141b74  Lelan::trayChanged

/* Lelan::trayChanged() */

void __thiscall Lelan::trayChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x2f,(void **)0x0);
  return;
}



// ==== 00141ba0  Lelan::onTrayBadgeChanged

/* Lelan::onTrayBadgeChanged() */

void __thiscall Lelan::onTrayBadgeChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x30,(void **)0x0);
  return;
}



// ==== 00141bcc  Lelan::onTrayPercentChanged

/* Lelan::onTrayPercentChanged() */

void __thiscall Lelan::onTrayPercentChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x31,(void **)0x0);
  return;
}



// ==== 00141bf8  Lelan::themeChanged

/* Lelan::themeChanged() */

void __thiscall Lelan::themeChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x32,(void **)0x0);
  return;
}



// ==== 00141c24  Lelan::darkModeChanged

/* Lelan::darkModeChanged() */

void __thiscall Lelan::darkModeChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x33,(void **)0x0);
  return;
}



// ==== 00141c50  Lelan::onAccentColorChanged

/* Lelan::onAccentColorChanged() */

void __thiscall Lelan::onAccentColorChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x34,(void **)0x0);
  return;
}



// ==== 00141c7c  Lelan::wallpaperChanged

/* Lelan::wallpaperChanged() */

void __thiscall Lelan::wallpaperChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x35,(void **)0x0);
  return;
}



// ==== 00141ca8  Lelan::systemFontChanged

/* Lelan::systemFontChanged() */

void __thiscall Lelan::systemFontChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x36,(void **)0x0);
  return;
}



// ==== 00141cd4  Lelan::slideshowChanged

/* Lelan::slideshowChanged() */

void __thiscall Lelan::slideshowChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x37,(void **)0x0);
  return;
}



// ==== 00141d00  Lelan::filigreePalettesChanged

/* Lelan::filigreePalettesChanged() */

void __thiscall Lelan::filigreePalettesChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x38,(void **)0x0);
  return;
}



// ==== 00141d2c  Lelan::onSessionActiveChanged

/* Lelan::onSessionActiveChanged() */

void __thiscall Lelan::onSessionActiveChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x39,(void **)0x0);
  return;
}



// ==== 00141d58  Lelan::vtActiveChanged

/* Lelan::vtActiveChanged() */

void __thiscall Lelan::vtActiveChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3a,(void **)0x0);
  return;
}



// ==== 00141d84  Lelan::screensaverChanged

/* Lelan::screensaverChanged() */

void __thiscall Lelan::screensaverChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3b,(void **)0x0);
  return;
}



// ==== 00141db0  Lelan::screenConfigChanged

/* Lelan::screenConfigChanged() */

void __thiscall Lelan::screenConfigChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3c,(void **)0x0);
  return;
}



// ==== 00141ddc  Lelan::screenGeometryChanged

/* Lelan::screenGeometryChanged() */

void __thiscall Lelan::screenGeometryChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3d,(void **)0x0);
  return;
}



// ==== 00141e08  Lelan::hostnameChanged

/* Lelan::hostnameChanged() */

void __thiscall Lelan::hostnameChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3e,(void **)0x0);
  return;
}



// ==== 00141e34  Lelan::localeChanged

/* Lelan::localeChanged() */

void __thiscall Lelan::localeChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x3f,(void **)0x0);
  return;
}



// ==== 00141e60  Lelan::userNameChanged

/* Lelan::userNameChanged() */

void __thiscall Lelan::userNameChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x40,(void **)0x0);
  return;
}



// ==== 00141e8c  Lelan::usersChanged

/* Lelan::usersChanged() */

void __thiscall Lelan::usersChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x41,(void **)0x0);
  return;
}



// ==== 00141eb8  Lelan::printersChanged

/* Lelan::printersChanged() */

void __thiscall Lelan::printersChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x42,(void **)0x0);
  return;
}



// ==== 00141ee4  Lelan::notificationsChanged

/* Lelan::notificationsChanged() */

void __thiscall Lelan::notificationsChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x43,(void **)0x0);
  return;
}



// ==== 00141f10  Lelan::animLevelChanged

/* Lelan::animLevelChanged() */

void __thiscall Lelan::animLevelChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x44,(void **)0x0);
  return;
}



// ==== 00141f3c  Lelan::hardwareTierChanged

/* Lelan::hardwareTierChanged() */

void __thiscall Lelan::hardwareTierChanged(Lelan *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x45,(void **)0x0);
  return;
}



// ==== 00161e5c  Lelan::loadConfig

/* Lelan::loadConfig(QString const&) const */

QString * Lelan::loadConfig(QString *param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  readConfig(param_1);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00161eac  Lelan::saveConfig

/* Lelan::saveConfig(QString const&, QMap<QString, QVariant> const&) */

void __thiscall Lelan::saveConfig(Lelan *this,QString *param_1,QMap *param_2)

{
  writeConfig(param_1,param_2);
  return;
}



// ==== 00161ed6  Lelan::network

/* Lelan::network() const */

QMap<QString,QVariant> * Lelan::network(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x78));
  return in_RDI;
}



// ==== 00161f04  Lelan::vpn

/* Lelan::vpn() const */

QMap<QString,QVariant> * Lelan::vpn(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x80));
  return in_RDI;
}



// ==== 00161f34  Lelan::wifiEnabled

/* Lelan::wifiEnabled() const */

Lelan __thiscall Lelan::wifiEnabled(Lelan *this)

{
  return this[200];
}



// ==== 00161f4a  Lelan::wifiNetworks

/* Lelan::wifiNetworks() const */

QList<QVariant> * Lelan::wifiNetworks(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0xa8));
  return in_RDI;
}



// ==== 00161f7a  Lelan::activeNetwork

/* Lelan::activeNetwork() const */

QMap<QString,QVariant> * Lelan::activeNetwork(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0xc0));
  return in_RDI;
}



// ==== 00161faa  Lelan::vpnConnections

/* Lelan::vpnConnections() const */

QList<QVariant> * Lelan::vpnConnections(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x108));
  return in_RDI;
}



// ==== 00161fda  Lelan::users

/* Lelan::users() const */

QList<QVariant> * Lelan::users(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x170));
  return in_RDI;
}



// ==== 0016200a  Lelan::userName

/* Lelan::userName() const */

QString * Lelan::userName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x188));
  return in_RDI;
}



// ==== 0016203a  Lelan::printers

/* Lelan::printers() const */

QList<QVariant> * Lelan::printers(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x1b0));
  return in_RDI;
}



// ==== 0016206a  Lelan::battery

/* Lelan::battery() const */

QMap<QString,QVariant> * Lelan::battery(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x88));
  return in_RDI;
}



// ==== 0016209a  Lelan::powerProfile

/* Lelan::powerProfile() const */

QString * Lelan::powerProfile(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x260));
  return in_RDI;
}



// ==== 001620ca  Lelan::thermalPressure

/* Lelan::thermalPressure() const */

undefined4 __thiscall Lelan::thermalPressure(Lelan *this)

{
  return *(undefined4 *)(this + 0x324);
}



// ==== 001620de  Lelan::sentinelTemps

/* Lelan::sentinelTemps() const */

QMap<QString,QVariant> * Lelan::sentinelTemps(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x378));
  return in_RDI;
}



// ==== 0016210e  Lelan::sentinelFans

/* Lelan::sentinelFans() const */

QMap<QString,QVariant> * Lelan::sentinelFans(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x380));
  return in_RDI;
}



// ==== 0016213e  Lelan::audio

/* Lelan::audio() const */

QMap<QString,QVariant> * Lelan::audio(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x90));
  return in_RDI;
}



// ==== 0016216e  Lelan::volume

/* Lelan::volume() const */

undefined4 __thiscall Lelan::volume(Lelan *this)

{
  return *(undefined4 *)(this + 0x328);
}



// ==== 00162182  Lelan::balance

/* Lelan::balance() const */

undefined4 __thiscall Lelan::balance(Lelan *this)

{
  return *(undefined4 *)(this + 0x3c0);
}



// ==== 00162196  Lelan::muted

/* Lelan::muted() const */

Lelan __thiscall Lelan::muted(Lelan *this)

{
  return this[0x334];
}



// ==== 001621ac  Lelan::appStreams

/* Lelan::appStreams() const */

QList<QVariant> * Lelan::appStreams(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x3c8));
  return in_RDI;
}



// ==== 001621dc  Lelan::outputDevices

/* Lelan::outputDevices() const */

QList<QVariant> * Lelan::outputDevices(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x3e0));
  return in_RDI;
}



// ==== 0016220c  Lelan::inputDevices

/* Lelan::inputDevices() const */

QList<QVariant> * Lelan::inputDevices(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x3f8));
  return in_RDI;
}



// ==== 0016223c  Lelan::defaultSourceName

/* Lelan::defaultSourceName() const */

QString * Lelan::defaultSourceName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x410));
  return in_RDI;
}



// ==== 0016226c  Lelan::media

/* Lelan::media() const */

QMap<QString,QVariant> * Lelan::media(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x98));
  return in_RDI;
}



// ==== 0016229c  Lelan::mediaActive

/* Lelan::mediaActive() const */

Lelan __thiscall Lelan::mediaActive(Lelan *this)

{
  return this[0x335];
}



// ==== 001622b2  Lelan::batteryPercent

/* Lelan::batteryPercent() const */

void __thiscall Lelan::batteryPercent(Lelan *this)

{
  long in_FS_OFFSET;
  undefined8 uVar1;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_68);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"percentage",10);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)(this + 0x88));
  uVar1 = ::QVariant::toDouble((bool *)local_48);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar1);
  }
  return;
}



// ==== 00162414  Lelan::batteryCharging

/* Lelan::batteryCharging() const */

ulong __thiscall Lelan::batteryCharging(Lelan *this)

{
  int iVar1;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_68);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"state",5);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)(this + 0x88));
  iVar1 = ::QVariant::toUInt((bool *)local_48);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return CONCAT71((int7)((ulong)(this + 0x88) >> 8),iVar1 == 1) & 0xffffffff;
}



// ==== 0016256e  Lelan::hasBattery

/* Lelan::hasBattery() const */

uint __thiscall Lelan::hasBattery(Lelan *this)

{
  uint uVar1;
  
  uVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)(this + 0x88));
  return uVar1 ^ 1;
}



// ==== 00162592  Lelan::onBattery

/* Lelan::onBattery() const */

Lelan __thiscall Lelan::onBattery(Lelan *this)

{
  return this[0x33a];
}



// ==== 001625a8  Lelan::networkOnline

/* Lelan::networkOnline() const */

ulong __thiscall Lelan::networkOnline(Lelan *this)

{
  int iVar1;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_68);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"state",5);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)(this + 0x78));
  iVar1 = ::QVariant::toUInt((bool *)local_48);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return CONCAT71((int7)((ulong)(this + 0x78) >> 8),iVar1 == 0x46) & 0xffffffff;
}



// ==== 001626fe  Lelan::networkUp

/* Lelan::networkUp() const */

undefined4 __thiscall Lelan::networkUp(Lelan *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_68,true);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"up",2);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)(this + 0x78));
  uVar1 = ::QVariant::toBool();
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 00162852  Lelan::PlayerState::~PlayerState

/* Lelan::PlayerState::~PlayerState() */

void __thiscall Lelan::PlayerState::~PlayerState(PlayerState *this)

{
  QString::~QString((QString *)(this + 0xa0));
  QString::~QString((QString *)(this + 0x78));
  QString::~QString((QString *)(this + 0x60));
  QString::~QString((QString *)(this + 0x48));
  QString::~QString((QString *)(this + 0x30));
  QString::~QString((QString *)(this + 0x18));
  QString::~QString((QString *)this);
  return;
}



// ==== 001628d0  Lelan::mediaTitle

/* Lelan::mediaTitle() const */

Lelan * __thiscall Lelan::mediaTitle(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_c8 [24];
  QString local_b0 [160];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_c8);
  QString::QString((QString *)this,local_b0);
  PlayerState::~PlayerState((PlayerState *)local_c8);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0016296a  Lelan::mediaArtist

/* Lelan::mediaArtist() const */

Lelan * __thiscall Lelan::mediaArtist(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_c8 [48];
  QString local_98 [136];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_c8);
  QString::QString((QString *)this,local_98);
  PlayerState::~PlayerState((PlayerState *)local_c8);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00162a04  Lelan::mediaAlbum

/* Lelan::mediaAlbum() const */

Lelan * __thiscall Lelan::mediaAlbum(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_c8 [72];
  QString local_80 [112];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_c8);
  QString::QString((QString *)this,local_80);
  PlayerState::~PlayerState((PlayerState *)local_c8);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00162a9e  Lelan::mediaArtUrl

/* Lelan::mediaArtUrl() const */

Lelan * __thiscall Lelan::mediaArtUrl(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_c8 [96];
  QString local_68 [88];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_c8);
  QString::QString((QString *)this,local_68);
  PlayerState::~PlayerState((PlayerState *)local_c8);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00162b38  Lelan::mediaTrackId

/* Lelan::mediaTrackId() const */

Lelan * __thiscall Lelan::mediaTrackId(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_c8 [120];
  QString local_50 [64];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_c8);
  QString::QString((QString *)this,local_50);
  PlayerState::~PlayerState((PlayerState *)local_c8);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00162bd2  Lelan::mediaDuration

/* Lelan::mediaDuration() const */

undefined8 Lelan::mediaDuration(void)

{
  long in_FS_OFFSET;
  QString local_d8 [152];
  undefined8 local_40;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_d8);
  PlayerState::~PlayerState((PlayerState *)local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}



// ==== 00162c4c  Lelan::mediaPosition

/* Lelan::mediaPosition() const */

undefined8 Lelan::mediaPosition(void)

{
  long in_FS_OFFSET;
  QString local_d8 [144];
  undefined8 local_48;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,Lelan::PlayerState>::value(local_d8);
  PlayerState::~PlayerState((PlayerState *)local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_48;
}



// ==== 00162cc6  Lelan::mediaPlaying

/* Lelan::mediaPlaying() const */

undefined4 Lelan::mediaPlaying(void)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  QLatin1String local_e8 [16];
  QString local_d8 [184];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QLatin1String::QLatin1String(local_e8,"Playing");
  QHash<QString,Lelan::PlayerState>::value(local_d8);
  uVar1 = ::operator==(local_d8,local_e8);
  PlayerState::~PlayerState((PlayerState *)local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 00162d70  Lelan::bluetooth

/* Lelan::bluetooth() const */

QMap<QString,QVariant> * Lelan::bluetooth(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0xa0));
  return in_RDI;
}



// ==== 00162da0  Lelan::bluetoothEnabled

/* Lelan::bluetoothEnabled() const */

Lelan __thiscall Lelan::bluetoothEnabled(Lelan *this)

{
  return this[0x148];
}



// ==== 00162db6  Lelan::bluetoothDiscoverable

/* Lelan::bluetoothDiscoverable() const */

Lelan __thiscall Lelan::bluetoothDiscoverable(Lelan *this)

{
  return this[0x149];
}



// ==== 00162dcc  Lelan::bluetoothDevices

/* Lelan::bluetoothDevices() const */

QList<QVariant> * Lelan::bluetoothDevices(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x128));
  return in_RDI;
}



// ==== 00162dfc  Lelan::bluetoothAudioDevice

/* Lelan::bluetoothAudioDevice() const */

QMap<QString,QVariant> * Lelan::bluetoothAudioDevice(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x140));
  return in_RDI;
}



// ==== 00162e2c  Lelan::removableVolumes

/* Lelan::removableVolumes() const */

QList<QVariant> * Lelan::removableVolumes(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x218));
  return in_RDI;
}



// ==== 00162e5c  Lelan::disk

/* Lelan::disk() const */

QMap<QString,QVariant> * Lelan::disk(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1f0));
  return in_RDI;
}



// ==== 00162e8c  Lelan::updates

/* Lelan::updates() const */

QMap<QString,QVariant> * Lelan::updates(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1c8));
  return in_RDI;
}



// ==== 00162ebc  Lelan::darkMode

/* Lelan::darkMode() const */

Lelan __thiscall Lelan::darkMode(Lelan *this)

{
  return this[0x336];
}



// ==== 00162ed2  Lelan::accentColor

/* Lelan::accentColor() const */

QString * Lelan::accentColor(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x278));
  return in_RDI;
}



// ==== 00162f02  Lelan::systemFont

/* Lelan::systemFont() const */

QString * Lelan::systemFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x290));
  return in_RDI;
}



// ==== 00162f32  Lelan::filigreePalette

/* Lelan::filigreePalette() const */

QMap<QString,QVariant> * Lelan::filigreePalette(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1d0));
  return in_RDI;
}



// ==== 00162f62  Lelan::location

/* Lelan::location() const */

QMap<QString,QVariant> * Lelan::location(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1d8));
  return in_RDI;
}



// ==== 00162f92  Lelan::placeName

/* Lelan::placeName() const */

QString * Lelan::placeName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2a8));
  return in_RDI;
}



// ==== 00162fc2  Lelan::clock

/* Lelan::clock() const */

QMap<QString,QVariant> * Lelan::clock(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1e0));
  return in_RDI;
}



// ==== 00162ff2  Lelan::timezone

/* Lelan::timezone() const */

QString * Lelan::timezone(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2c0));
  return in_RDI;
}



// ==== 00163022  Lelan::locating

/* Lelan::locating() const */

Lelan __thiscall Lelan::locating(Lelan *this)

{
  return this[800];
}



// ==== 00163038  Lelan::tray

/* Lelan::tray() const */

QList<QVariant> * Lelan::tray(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x230));
  return in_RDI;
}



// ==== 00163068  Lelan::sessionActive

/* Lelan::sessionActive() const */

Lelan __thiscall Lelan::sessionActive(Lelan *this)

{
  return this[0x337];
}



// ==== 0016307e  Lelan::vtActive

/* Lelan::vtActive() const */

undefined4 __thiscall Lelan::vtActive(Lelan *this)

{
  return *(undefined4 *)(this + 0x32c);
}



// ==== 00163092  Lelan::screensaver

/* Lelan::screensaver() const */

Lelan __thiscall Lelan::screensaver(Lelan *this)

{
  return this[0x338];
}



// ==== 001630a8  Lelan::hostname

/* Lelan::hostname() const */

QString * Lelan::hostname(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2d8));
  return in_RDI;
}



// ==== 001630d8  Lelan::locale

/* Lelan::locale() const */

QString * Lelan::locale(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2f0));
  return in_RDI;
}



// ==== 00163108  Lelan::kickass

/* Lelan::kickass() const */

QMap<QString,QVariant> * Lelan::kickass(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x1e8));
  return in_RDI;
}



// ==== 00163138  Lelan::notifications

/* Lelan::notifications() const */

QList<QVariant> * Lelan::notifications(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x248));
  return in_RDI;
}



// ==== 00163168  Lelan::animLevel

/* Lelan::animLevel() const */

undefined4 __thiscall Lelan::animLevel(Lelan *this)

{
  return *(undefined4 *)(this + 0x330);
}



// ==== 0016317c  Lelan::reduceMotion

/* Lelan::reduceMotion() const */

Lelan __thiscall Lelan::reduceMotion(Lelan *this)

{
  return this[0x339];
}



// ==== 00163192  Lelan::hardwareTier

/* Lelan::hardwareTier() const */

QString * Lelan::hardwareTier(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x340));
  return in_RDI;
}



// ==== 001631c2  Lelan::onWMScreenConfig

/* Lelan::onWMScreenConfig(int, int) */

void Lelan::onWMScreenConfig(int param_1,int param_2)

{
  undefined4 in_register_0000003c;
  
  screenConfigChanged((Lelan *)CONCAT44(in_register_0000003c,param_1));
  screenGeometryChanged((Lelan *)CONCAT44(in_register_0000003c,param_1));
  return;
}



// ==== 001a8f60  Lelan::PlayerState::PlayerState

/* Lelan::PlayerState::PlayerState(Lelan::PlayerState const&) */

void __thiscall Lelan::PlayerState::PlayerState(PlayerState *this,PlayerState *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  QString::QString((QString *)(this + 0x60),(QString *)(param_1 + 0x60));
  QString::QString((QString *)(this + 0x78),(QString *)(param_1 + 0x78));
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(param_1 + 0x90);
  *(undefined8 *)(this + 0x98) = *(undefined8 *)(param_1 + 0x98);
  QString::QString((QString *)(this + 0xa0),(QString *)(param_1 + 0xa0));
  return;
}



// ==== 001a905a  Lelan::PlayerState::PlayerState

/* Lelan::PlayerState::PlayerState() */

void __thiscall Lelan::PlayerState::PlayerState(PlayerState *this)

{
  QString::QString((QString *)this);
  QString::QString((QString *)(this + 0x18));
  QString::QString((QString *)(this + 0x30));
  QString::QString((QString *)(this + 0x48));
  QString::QString((QString *)(this + 0x60));
  QString::QString((QString *)(this + 0x78));
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  QString::QString((QString *)(this + 0xa0));
  return;
}



// ==== 001f876c  Lelan::setAnimPolicy

/* Lelan::setAnimPolicy(AnimPolicy*) */

void __thiscall Lelan::setAnimPolicy(Lelan *this,AnimPolicy *param_1)

{
  *(AnimPolicy **)(this + 0x440) = param_1;
  recomputeAnimLevel(this);
  return;
}



// ==== 002046a0  Lelan::Lelan(QObject*,bool)::{lambda()#1}::operator()

/* Lelan::Lelan(QObject*, bool)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::Lelan(QObject*,bool)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  undefined1 uVar2;
  long in_FS_OFFSET;
  QString local_100 [8];
  wchar16 *local_f8;
  wchar16 *local_f0;
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f8 = L"accessibility";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_e8,(QTypedArrayData *)0x0,L"accessibility",0xd);
  QString::QString(local_c8,(QArrayDataPointer *)local_e8);
  readConfig(local_100);
  ::QVariant::QVariant(local_68,*(bool *)(*(long *)this + 0x339));
  local_f0 = L"reduceMotion";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"reduceMotion",0xc);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
  lVar1 = *(long *)this;
  uVar2 = ::QVariant::toBool();
  *(undefined1 *)(lVar1 + 0x339) = uVar2;
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_100);
  QString::~QString(local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  recomputeAnimLevel(*(Lelan **)this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002048e2  Lelan::Lelan(QObject*,bool)::{lambda(QString_const&)#1}::operator()

/* Lelan::Lelan(QObject*, bool)::{lambda(QString const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString
   const&) const */

void __thiscall
Lelan::Lelan(QObject*,bool)::{lambda(QString_const&)#1}::operator()
          (_lambda_QString_const___1_ *this,QString *param_1)

{
  Lelan(QObject*,bool)::{lambda()#1}::operator()((_lambda___1_ *)this);
  return;
}



// ==== 00204902  Lelan::Lelan(QObject*,bool)::{lambda(QString_const&)#2}::operator()

/* Lelan::Lelan(QObject*, bool)::{lambda(QString const&)#2}::TEMPNAMEPLACEHOLDERVALUE(QString
   const&) const */

void __thiscall
Lelan::Lelan(QObject*,bool)::{lambda(QString_const&)#2}::operator()
          (_lambda_QString_const___2_ *this,QString *param_1)

{
  Lelan(QObject*,bool)::{lambda()#1}::operator()((_lambda___1_ *)this);
  return;
}



// ==== 00204922  Lelan::Lelan

/* WARNING: Removing unreachable block (ram,0x002051fa) */
/* WARNING: Removing unreachable block (ram,0x002050e8) */
/* WARNING: Removing unreachable block (ram,0x00205308) */
/* Lelan::Lelan(QObject*, bool) */

void __thiscall Lelan::Lelan(Lelan *this,QObject *param_1,bool param_2)

{
  Lelan LVar1;
  char cVar2;
  QTimer *pQVar3;
  QFileSystemWatcher *this_00;
  longlong lVar4;
  QVariant *this_01;
  long in_FS_OFFSET;
  QString local_148 [8];
  undefined *local_140;
  wchar16 *local_138;
  wchar16 *local_130;
  QString local_128 [32];
  QString local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  Connection local_c8 [32];
  Lelan *local_a8;
  undefined8 local_a0;
  QString local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c118;
  QHash<QString,Lelan::PlayerState>::QHash((QHash<QString,Lelan::PlayerState> *)(this + 0x10));
  QString::QString((QString *)(this + 0x18));
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  QQueue<std::function<void()>>::QQueue((QQueue<std::function<void()>> *)(this + 0x50));
  this[0x68] = (Lelan)0x0;
  *(undefined8 *)(this + 0x70) = 0;
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x78));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x80));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x88));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x90));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x98));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0xa0));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0xa8));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0xc0));
  this[200] = (Lelan)0x0;
  QString::QString((QString *)(this + 0xd0));
  QString::QString((QString *)(this + 0xe8));
  this[0x100] = (Lelan)0x0;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x108));
  QHash<QString,QString>::QHash((QHash<QString,QString> *)(this + 0x120));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x128));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x140));
  this[0x148] = (Lelan)0x0;
  this[0x149] = (Lelan)0x0;
  QString::QString((QString *)(this + 0x150));
  QHash<QString,QString>::QHash((QHash<QString,QString> *)(this + 0x168));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x170));
  QString::QString((QString *)(this + 0x188));
  QHash<QString,QString>::QHash((QHash<QString,QString> *)(this + 0x1a0));
  QHash<QString,unsigned_long_long>::QHash((QHash<QString,unsigned_long_long> *)(this + 0x1a8));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x1b0));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1c8));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1d0));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1d8));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1e0));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1e8));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1f0));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x1f8));
  QString::QString((QString *)(this + 0x200));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x218));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x230));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x248));
  QString::QString((QString *)(this + 0x260),"balanced");
  QString::QString((QString *)(this + 0x278));
  QString::QString((QString *)(this + 0x290));
  QString::QString((QString *)(this + 0x2a8));
  QString::QString((QString *)(this + 0x2c0));
  QString::QString((QString *)(this + 0x2d8));
  QString::QString((QString *)(this + 0x2f0));
  QString::QString((QString *)(this + 0x308));
  this[800] = (Lelan)0x1;
  *(undefined4 *)(this + 0x324) = 0;
  *(undefined4 *)(this + 0x328) = 0;
  *(undefined4 *)(this + 0x32c) = 0;
  *(undefined4 *)(this + 0x330) = 0;
  this[0x334] = (Lelan)0x0;
  this[0x335] = (Lelan)0x0;
  this[0x336] = (Lelan)0x0;
  this[0x337] = (Lelan)0x1;
  this[0x338] = (Lelan)0x0;
  this[0x339] = (Lelan)0x0;
  this[0x33a] = (Lelan)0x0;
  local_140 = &DAT_002aa332;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"mid",3);
  QString::QString((QString *)(this + 0x340),(QArrayDataPointer *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  *(undefined4 *)(this + 0x358) = 0;
  this[0x35c] = (Lelan)0x0;
  *(undefined8 *)(this + 0x360) = 0x4056400000000000;
  *(undefined8 *)(this + 0x368) = 0x4055000000000000;
  *(undefined4 *)(this + 0x370) = 0;
  this[0x374] = (Lelan)0x0;
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x378));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x380));
  this[0x388] = (Lelan)0x0;
  *(undefined4 *)(this + 0x38c) = 0;
  *(undefined8 *)(this + 0x390) = 0;
  *(undefined8 *)(this + 0x398) = 0;
  *(undefined4 *)(this + 0x3a0) = 0xffffffff;
  *(undefined4 *)(this + 0x3a4) = 2;
  QString::QString((QString *)(this + 0x3a8));
  *(undefined4 *)(this + 0x3c0) = 0x32;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x3c8));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x3e0));
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x3f8));
  QString::QString((QString *)(this + 0x410));
  *(undefined8 *)(this + 0x428) = 0;
  QHash<QString,QMap<QString,QVariant>>::QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x430));
  QSet<QString>::QSet((QSet<QString> *)(this + 0x438));
  *(undefined8 *)(this + 0x440) = 0;
  *(undefined8 *)(this + 0x448) = 0;
  this[0x450] = (Lelan)param_2;
  qDBusRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>();
  qDBusRegisterMetaType<QList<unsigned_int>>();
  qDBusRegisterMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>();
  qDBusRegisterMetaType<QMap<QString,double>>();
  qDBusRegisterMetaType<QMap<QString,unsigned_int>>();
  pQVar3 = operator_new(0x10);
  QTimer::QTimer(pQVar3,(QObject *)this);
  *(QTimer **)(this + 0x38) = pQVar3;
  QTimer::setTimerType(*(undefined8 *)(this + 0x38),1);
  QTimer::setInterval((int)*(undefined8 *)(this + 0x38));
  local_a8 = (Lelan *)onPulse;
  local_a0 = 0;
  QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(Lelan::*)()>
            (local_c8,*(undefined8 *)(this + 0x38),QTimer::timeout,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection(local_c8);
  QTimer::start();
  pQVar3 = operator_new(0x10);
  QTimer::QTimer(pQVar3,(QObject *)this);
  *(QTimer **)(this + 0x48) = pQVar3;
  QTimer::setTimerType(*(undefined8 *)(this + 0x48),1);
  QTimer::setInterval((int)*(undefined8 *)(this + 0x48));
  local_a8 = (Lelan *)drainIdleQueue;
  local_a0 = 0;
  QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(Lelan::*)()>
            (local_c8,*(undefined8 *)(this + 0x48),QTimer::timeout,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection(local_c8);
  LVar1 = (Lelan)detectBfqScheduler();
  this[0x68] = LVar1;
  this_00 = operator_new(0x10);
  QFileSystemWatcher::QFileSystemWatcher(this_00,(QObject *)this);
  *(QFileSystemWatcher **)(this + 0x70) = this_00;
  QStandardPaths::writableLocation(&local_a8,0xd);
  ::operator+(local_128,(char *)&local_a8);
  QString::~QString((QString *)&local_a8);
  QDir::QDir((QDir *)&local_a8,local_128);
  cVar2 = QDir::exists();
  QDir::~QDir((QDir *)&local_a8);
  if (cVar2 != '\0') {
    QFileSystemWatcher::addPath(*(QString **)(this + 0x70));
  }
  local_138 = L"accessibility";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_e8,(QTypedArrayData *)0x0,L"accessibility",0xd);
  QString::QString(local_108,(QArrayDataPointer *)local_e8);
  readConfig(local_148);
  ::QVariant::QVariant(local_68,false);
  local_130 = L"reduceMotion";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"reduceMotion",0xc);
  QString::QString((QString *)local_c8,(QArrayDataPointer *)&local_a8);
  QMap<QString,QVariant>::value(local_88,(QVariant *)local_148);
  LVar1 = (Lelan)::QVariant::toBool();
  this[0x339] = LVar1;
  ::QVariant::~QVariant((QVariant *)local_88);
  QString::~QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  ::QVariant::~QVariant(local_68);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_148);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  local_a8 = this;
  QObject::
  connect<void(QFileSystemWatcher::*)(QString_const&,QFileSystemWatcher::QPrivateSignal),Lelan::Lelan(QObject*,bool)::_lambda(QString_const&)_1_>
            (local_c8,*(undefined8 *)(this + 0x70),QFileSystemWatcher::fileChanged,0,this,&local_a8,
             0);
  QMetaObject::Connection::~Connection(local_c8);
  local_a8 = this;
  QObject::
  connect<void(QFileSystemWatcher::*)(QString_const&,QFileSystemWatcher::QPrivateSignal),Lelan::Lelan(QObject*,bool)::_lambda(QString_const&)_2_>
            (local_c8,*(undefined8 *)(this + 0x70),QFileSystemWatcher::directoryChanged,0,this,
             &local_a8,0);
  QMetaObject::Connection::~Connection(local_c8);
  QDBusConnection::sessionBus();
  QString::QString((QString *)&local_a8,"NameOwnerChanged");
  QString::QString((QString *)local_c8,"org.freedesktop.DBus");
  QString::QString((QString *)local_e8,"/org/freedesktop/DBus");
  QString::QString(local_108,"org.freedesktop.DBus");
  QDBusConnection::connect
            (local_148,local_108,(QString *)local_e8,(QString *)local_c8,(QObject *)&local_a8,
             (char *)this);
  QString::~QString(local_108);
  QString::~QString((QString *)local_e8);
  QString::~QString((QString *)local_c8);
  QString::~QString((QString *)&local_a8);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_148);
  QDBusConnection::systemBus();
  QString::QString((QString *)&local_a8,"NameOwnerChanged");
  QString::QString((QString *)local_c8,"org.freedesktop.DBus");
  QString::QString((QString *)local_e8,"/org/freedesktop/DBus");
  QString::QString(local_108,"org.freedesktop.DBus");
  QDBusConnection::connect
            (local_148,local_108,(QString *)local_e8,(QString *)local_c8,(QObject *)&local_a8,
             (char *)this);
  QString::~QString(local_108);
  QString::~QString((QString *)local_e8);
  QString::~QString((QString *)local_c8);
  QString::~QString((QString *)&local_a8);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_148);
  subscribeToNetworkManager(this);
  subscribeToWifi(this);
  subscribeToUPower(this);
  subscribeToBlueZ(this);
  subscribeToUDisks2(this);
  subscribeToPowerProfiles(this);
  subscribeToPackageKit(this);
  subscribeToPortalSettings(this);
  subscribeToMemoryMonitor(this);
  subscribeToGeoClue(this);
  subscribeToTimeDate(this);
  subscribeToHostnameLocale(this);
  subscribeToLogind(this);
  subscribeToScreenSaver(this);
  subscribeToPlayers(this);
  subscribeTrayOwner(this);
  subscribeToAudio(this);
  subscribeToKickassGuard(this);
  if (this[0x450] != (Lelan)0x0) {
    subscribeToSentinel(this);
  }
  refreshUsers(this);
  refreshPrinters(this);
  refreshDiskUsage(this);
  lVar4 = QDateTime::currentSecsSinceEpoch();
  ::QVariant::QVariant(local_68,lVar4);
  QString::QString((QString *)&local_a8,"epoch");
  this_01 = (QVariant *)
            QMap<QString,QVariant>::operator[]
                      ((QMap<QString,QVariant> *)(this + 0x1e0),(QString *)&local_a8);
  ::QVariant::operator=(this_01,local_68);
  QString::~QString((QString *)&local_a8);
  ::QVariant::~QVariant(local_68);
  clockChanged(this);
  dateTimeChanged(this);
  if (this[0x450] != (Lelan)0x0) {
    checkThermalZones(this);
    checkCpuFreq(this);
  }
  recomputeAnimLevel(this);
  QString::~QString(local_128);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002060f4  Lelan::~Lelan

/* Lelan::~Lelan() */

void __thiscall Lelan::~Lelan(Lelan *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c118;
  stopPulse(this);
  QSet<QString>::~QSet((QSet<QString> *)(this + 0x438));
  QHash<QString,QMap<QString,QVariant>>::~QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x430));
  QString::~QString((QString *)(this + 0x410));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x3f8));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x3e0));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x3c8));
  QString::~QString((QString *)(this + 0x3a8));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x380));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x378));
  QString::~QString((QString *)(this + 0x340));
  QString::~QString((QString *)(this + 0x308));
  QString::~QString((QString *)(this + 0x2f0));
  QString::~QString((QString *)(this + 0x2d8));
  QString::~QString((QString *)(this + 0x2c0));
  QString::~QString((QString *)(this + 0x2a8));
  QString::~QString((QString *)(this + 0x290));
  QString::~QString((QString *)(this + 0x278));
  QString::~QString((QString *)(this + 0x260));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x248));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x230));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x218));
  QString::~QString((QString *)(this + 0x200));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1f8));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1f0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1e8));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1e0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1d8));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1d0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x1c8));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x1b0));
  QHash<QString,unsigned_long_long>::~QHash((QHash<QString,unsigned_long_long> *)(this + 0x1a8));
  QHash<QString,QString>::~QHash((QHash<QString,QString> *)(this + 0x1a0));
  QString::~QString((QString *)(this + 0x188));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x170));
  QHash<QString,QString>::~QHash((QHash<QString,QString> *)(this + 0x168));
  QString::~QString((QString *)(this + 0x150));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x140));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x128));
  QHash<QString,QString>::~QHash((QHash<QString,QString> *)(this + 0x120));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x108));
  QString::~QString((QString *)(this + 0xe8));
  QString::~QString((QString *)(this + 0xd0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0xc0));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0xa8));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0xa0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x98));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x90));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x88));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x80));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x78));
  QQueue<std::function<void()>>::~QQueue((QQueue<std::function<void()>> *)(this + 0x50));
  QString::~QString((QString *)(this + 0x18));
  QHash<QString,Lelan::PlayerState>::~QHash((QHash<QString,Lelan::PlayerState> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 002064de  Lelan::~Lelan

/* Lelan::~Lelan() */

void __thiscall Lelan::~Lelan(Lelan *this)

{
  ~Lelan(this);
  operator_delete(this,0x458);
  return;
}



// ==== 0020650a  Lelan::setEngine(NCDEEngine*)::{lambda()#1}::operator()

/* Lelan::setEngine(NCDEEngine*)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::setEngine(NCDEEngine*)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  long in_FS_OFFSET;
  QMap local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(*(long *)this + 0x448) != 0) {
    NCDEEngine::activeFiligreePalette();
    bVar1 = ::operator==(local_28,(QMap *)(*(long *)this + 0x1d0));
    if (!bVar1) {
      QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(*(long *)this + 0x1d0),local_28);
      filigreePalettesChanged(*(Lelan **)this);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_28);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0020660e  Lelan::setEngine

/* Lelan::setEngine(NCDEEngine*) */

void __thiscall Lelan::setEngine(Lelan *this,NCDEEngine *param_1)

{
  long in_FS_OFFSET;
  Lelan *local_30;
  QMap local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(NCDEEngine **)(this + 0x448) = param_1;
  if (param_1 != (NCDEEngine *)0x0) {
    NCDEEngine::activeFiligreePalette();
    QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(this + 0x1d0),local_28);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_28);
    local_30 = this;
    QObject::connect<void(NCDEEngine::*)(),Lelan::setEngine(NCDEEngine*)::_lambda()_1_>
              (local_28,param_1,NCDEEngine::filigreePalettesChanged,0,this,&local_30,0);
    QMetaObject::Connection::~Connection((Connection *)local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002066f8  Lelan::configDir

/* Lelan::configDir() */

Lelan * __thiscall Lelan::configDir(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_78 [32];
  undefined8 local_58 [4];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,L"/.config/ncde",0xd);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  QDir::homePath();
  ::operator+((QString *)this,local_78);
  QString::~QString(local_78);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_58);
  QString::QString(local_38);
  QDir::QDir((QDir *)local_78,local_38);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_58);
  QDir::mkpath(local_78,this,local_58[0]);
  QDir::~QDir((QDir *)local_78);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 002068bc  Lelan::configPath

/* Lelan::configPath(QString const&) */

QString * Lelan::configPath(QString *param_1)

{
  long in_FS_OFFSET;
  QLatin1Char local_c3;
  undefined2 local_c2;
  wchar16 *local_c0;
  Lelan local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_c0 = L".json";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L".json",5);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  QLatin1Char::QLatin1Char(&local_c3,'/');
  QChar::QChar<QLatin1Char,true>((QChar *)&local_c2,local_c3);
  configDir(local_b8);
  ::operator+(local_98,local_b8,local_c2);
  ::operator+(local_78,local_98);
  ::operator+(param_1,local_78);
  QString::~QString(local_78);
  QString::~QString(local_98);
  QString::~QString((QString *)local_b8);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00206a8e  Lelan::readConfig

/* Lelan::readConfig(QString const&) */

QString * Lelan::readConfig(QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QByteArray local_58 [8];
  QJsonObject local_50 [8];
  QFile local_48 [16];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  configPath((QString *)local_38);
  QFile::QFile(local_48,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_48,local_38[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson(local_58,(QJsonParseError *)local_38);
    QJsonDocument::object();
    QJsonObject::toVariantMap();
    QJsonObject::~QJsonObject(local_50);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_58);
    QByteArray::~QByteArray((QByteArray *)local_38);
  }
  else {
    *(undefined8 *)param_1 = 0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)param_1);
  }
  QFile::~QFile(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00206c5a  Lelan::writeConfig

/* Lelan::writeConfig(QString const&, QMap<QString, QVariant> const&) */

undefined4 Lelan::writeConfig(QString *param_1,QMap *param_2)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QMap local_58 [8];
  QJsonDocument local_50 [8];
  QSaveFile local_48 [16];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  configDir((Lelan *)local_38);
  QString::~QString((QString *)local_38);
  configPath((QString *)local_38);
  QSaveFile::QSaveFile(local_48,(QString *)local_38,(QObject *)0x0);
  QString::~QString((QString *)local_38);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,2);
  cVar1 = QSaveFile::open(local_48,local_38[0]);
  if (cVar1 == '\x01') {
    QJsonObject::fromVariantMap(local_58);
    QJsonDocument::QJsonDocument(local_50,(QJsonObject *)local_58);
    QJsonDocument::toJson(local_38,local_50,0);
    QIODevice::write((QByteArray *)local_48);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QJsonDocument::~QJsonDocument(local_50);
    QJsonObject::~QJsonObject((QJsonObject *)local_58);
    uVar2 = QSaveFile::commit();
  }
  else {
    uVar2 = 0;
  }
  QSaveFile::~QSaveFile(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 00206e40  Lelan::setReduceMotionPref

/* Lelan::setReduceMotionPref(bool) */

void __thiscall Lelan::setReduceMotionPref(Lelan *this,bool param_1)

{
  if ((Lelan)param_1 != this[0x339]) {
    this[0x339] = (Lelan)param_1;
    recomputeAnimLevel(this);
  }
  return;
}



// ==== 00206e80  Lelan::onNameOwnerChanged

/* Lelan::onNameOwnerChanged(QString const&, QString const&, QString const&) */

void __thiscall
Lelan::onNameOwnerChanged(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  char *local_40;
  char *local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QString::isEmpty(param_3);
  if (cVar2 != '\0') {
    QString::QString((QString *)local_38,"org.mpris.MediaPlayer2.");
    cVar2 = QString::startsWith(param_1,local_38,1);
    QString::~QString((QString *)local_38);
    if (cVar2 != '\0') {
      removePlayer(this,param_1);
    }
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.UPower";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToUPower(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.portal.Desktop";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToPortalSettings(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.ncde.KickassGuard";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToKickassGuard(this);
    goto LAB_002072c7;
  }
  QString::QString((QString *)local_38,"org.mpris.MediaPlayer2.");
  cVar2 = QString::startsWith(param_1,local_38,1);
  QString::~QString((QString *)local_38);
  if (cVar2 != '\0') {
    subscribeToPlayers(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.NetworkManager";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToNetworkManager(this);
    subscribeToWifi(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.bluez";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToBlueZ(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.UDisks2";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToUDisks2(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.GeoClue2";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToGeoClue(this);
    goto LAB_002072c7;
  }
  local_38[0] = "org.freedesktop.timedate1";
  cVar2 = ::operator==(param_1,local_38);
  if (cVar2 != '\0') {
    subscribeToTimeDate(this);
    goto LAB_002072c7;
  }
  local_40 = "org.freedesktop.hostname1";
  cVar2 = ::operator==(param_1,&local_40);
  if (cVar2 == '\0') {
    local_38[0] = "org.freedesktop.locale1";
    cVar2 = ::operator==(param_1,local_38);
    if (cVar2 != '\0') goto LAB_0020714d;
    bVar1 = false;
  }
  else {
LAB_0020714d:
    bVar1 = true;
  }
  if (bVar1) {
    subscribeToHostnameLocale(this);
  }
  else {
    local_38[0] = "io.ncde.Sentinel";
    cVar2 = ::operator==(param_1,local_38);
    if (cVar2 == '\0') {
      local_38[0] = "org.freedesktop.login1";
      cVar2 = ::operator==(param_1,local_38);
      if (cVar2 == '\0') {
        local_38[0] = "org.freedesktop.ScreenSaver";
        cVar2 = ::operator==(param_1,local_38);
        if (cVar2 == '\0') {
          local_38[0] = "org.freedesktop.PackageKit";
          cVar2 = ::operator==(param_1,local_38);
          if (cVar2 == '\0') {
            local_38[0] = "net.hadess.PowerProfiles";
            cVar2 = ::operator==(param_1,local_38);
            if (cVar2 != '\0') {
              subscribeToPowerProfiles(this);
            }
          }
          else {
            subscribeToPackageKit(this);
          }
        }
        else {
          subscribeToScreenSaver(this);
        }
      }
      else {
        subscribeToLogind(this);
      }
    }
    else {
      subscribeToSentinel(this);
    }
  }
LAB_002072c7:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002072e2  Lelan::onSystemNameOwnerChanged

/* Lelan::onSystemNameOwnerChanged(QString const&, QString const&, QString const&) */

void __thiscall
Lelan::onSystemNameOwnerChanged(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
  onNameOwnerChanged(this,param_1,param_2,param_3);
  return;
}



// ==== 00207316  Lelan::onPulse

/* Lelan::onPulse() */

void __thiscall Lelan::onPulse(Lelan *this)

{
  char cVar1;
  
  *(long *)(this + 0x40) = *(long *)(this + 0x40) + 1;
  pulse(this,*(ulonglong *)(this + 0x40));
  if (*(ulong *)(this + 0x40) % 0x3c == 0) {
    onCoalescedTick(this);
  }
  cVar1 = mediaPlaying();
  if (cVar1 != '\0') {
    refreshMediaPosition(this);
    refreshActiveMediaPid(this);
  }
  return;
}



// ==== 002073b2  Lelan::onCoalescedTick

/* Lelan::onCoalescedTick() */

void __thiscall Lelan::onCoalescedTick(Lelan *this)

{
  longlong lVar1;
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QDateTime::currentSecsSinceEpoch();
  ::QVariant::QVariant(local_48,lVar1);
  QString::QString(local_68,"epoch");
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1e0),local_68);
  ::QVariant::operator=(this_00,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  clockChanged(this);
  dateTimeChanged(this);
  if (this[0x450] != (Lelan)0x0) {
    checkThermalZones(this);
    checkCpuFreq(this);
  }
  refreshDiskUsage(this);
  *(int *)(this + 0x38c) = *(int *)(this + 0x38c) + 1;
  if (*(int *)(this + 0x38c) % 0xf == 0) {
    weatherChanged(this);
  }
  recomputeAnimLevel(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0020754e  Lelan::refreshDiskUsage

/* Lelan::refreshDiskUsage() */

void __thiscall Lelan::refreshDiskUsage(Lelan *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  QVariant *pQVar10;
  long in_FS_OFFSET;
  QStorageInfo local_180 [8];
  long local_178;
  long local_170;
  long local_168;
  undefined1 *local_160;
  undefined1 *local_158;
  undefined1 *local_150;
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_160 = &LAB_002aa560_6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"/",1);
  QString::QString(local_e8,(QArrayDataPointer *)local_108);
  QStorageInfo::QStorageInfo(local_180,local_e8);
  QString::~QString(local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  cVar6 = QStorageInfo::isValid();
  if ((cVar6 == '\x01') && (cVar6 = QStorageInfo::isReady(), cVar6 == '\x01')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) || (local_178 = QStorageInfo::bytesTotal(), local_178 < 1)) goto LAB_00207b3b;
  local_170 = QStorageInfo::bytesFree();
  local_168 = local_178 - local_170;
  iVar7 = (int)(((double)local_168 / (double)local_178) * 100.0 + 0.5);
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  bVar1 = false;
  ::QVariant::QVariant(local_c8);
  local_158 = &LAB_002aa569_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_148,(QTypedArrayData *)0x0,L"usedPercent",0xb);
  QString::QString(local_128,(QArrayDataPointer *)local_148);
  QMap<QString,QVariant>::value(local_a8,(QVariant *)(this + 0x1f0));
  iVar8 = ::QVariant::toInt((bool *)local_a8);
  if (iVar7 == iVar8) {
    ::QVariant::QVariant(local_88);
    bVar4 = true;
    local_150 = &LAB_002aa582;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"totalBytes",10);
    bVar3 = true;
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    bVar2 = true;
    QMap<QString,QVariant>::value(local_68,(QVariant *)(this + 0x1f0));
    bVar1 = true;
    lVar9 = ::QVariant::toLongLong((bool *)local_68);
    if (local_178 != lVar9) goto LAB_0020787a;
    bVar5 = true;
  }
  else {
LAB_0020787a:
    bVar5 = false;
  }
  if (bVar1) {
    ::QVariant::~QVariant((QVariant *)local_68);
  }
  if (bVar2) {
    QString::~QString(local_e8);
  }
  if (bVar3) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  if (bVar4) {
    ::QVariant::~QVariant(local_88);
  }
  ::QVariant::~QVariant((QVariant *)local_a8);
  QString::~QString(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  ::QVariant::~QVariant(local_c8);
  if (!bVar5) {
    ::QVariant::QVariant((QVariant *)local_68,local_168);
    QString::QString(local_e8,"usedBytes");
    pQVar10 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1f0),local_e8);
    ::QVariant::operator=(pQVar10,(QVariant *)local_68);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QVariant::QVariant((QVariant *)local_68,local_170);
    QString::QString(local_e8,"freeBytes");
    pQVar10 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1f0),local_e8);
    ::QVariant::operator=(pQVar10,(QVariant *)local_68);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QVariant::QVariant((QVariant *)local_68,local_178);
    QString::QString(local_e8,"totalBytes");
    pQVar10 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1f0),local_e8);
    ::QVariant::operator=(pQVar10,(QVariant *)local_68);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_68);
    ::QVariant::QVariant((QVariant *)local_68,iVar7);
    QString::QString(local_e8,"usedPercent");
    pQVar10 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1f0),local_e8);
    ::QVariant::operator=(pQVar10,(QVariant *)local_68);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_68);
    diskChanged(this);
  }
LAB_00207b3b:
  QStorageInfo::~QStorageInfo(local_180);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00207d4a  Lelan::deferWhenIdle

/* Lelan::deferWhenIdle(std::function<void ()>) */

void __thiscall Lelan::deferWhenIdle(Lelan *this,function *param_2)

{
  bool bVar1;
  char cVar2;
  
  QQueue<std::function<void()>>::enqueue((QQueue<std::function<void()>> *)(this + 0x50),param_2);
  if (*(long *)(this + 0x48) != 0) {
    cVar2 = QTimer::isActive();
    if (cVar2 != '\x01') {
      bVar1 = true;
      goto LAB_00207da9;
    }
  }
  bVar1 = false;
LAB_00207da9:
  if (bVar1) {
    QTimer::start();
  }
  return;
}



// ==== 00207dc0  Lelan::drainIdleQueue

/* Lelan::drainIdleQueue() */

void __thiscall Lelan::drainIdleQueue(Lelan *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  bool bVar6;
  int iVar7;
  long in_FS_OFFSET;
  char *local_130;
  QString local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar5 = QList<std::function<void()>>::isEmpty((QList<std::function<void()>> *)(this + 0x50));
  if (cVar5 != '\0') {
    if (*(long *)(this + 0x48) != 0) {
      QTimer::stop();
    }
    goto LAB_0020830c;
  }
  if ((*(long *)(this + 0x440) == 0) ||
     ((cVar5 = AnimPolicy::screenIdle(*(AnimPolicy **)(this + 0x440)), cVar5 == '\0' &&
      (cVar5 = AnimPolicy::lowPower(*(AnimPolicy **)(this + 0x440)), cVar5 == '\0')))) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  bVar2 = false;
  bVar1 = false;
  bVar4 = false;
  local_130 = "charging";
  ::QVariant::QVariant(local_c8);
  QString::QString(local_128,"state");
  QMap<QString,QVariant>::value(local_a8,(QVariant *)(this + 0x88));
  ::QVariant::toString();
  cVar5 = ::operator==(local_108,&local_130);
  if (cVar5 == '\0') {
    ::QVariant::QVariant(local_88);
    bVar2 = true;
    QString::QString(local_e8,"charging");
    bVar1 = true;
    QMap<QString,QVariant>::value(local_68,(QVariant *)(this + 0x88));
    bVar4 = true;
    cVar5 = ::QVariant::toBool();
    if (cVar5 != '\0') goto LAB_00207fe0;
    bVar3 = false;
  }
  else {
LAB_00207fe0:
    bVar3 = true;
  }
  if (bVar4) {
    ::QVariant::~QVariant((QVariant *)local_68);
  }
  if (bVar1) {
    QString::~QString(local_e8);
  }
  if (bVar2) {
    ::QVariant::~QVariant(local_88);
  }
  QString::~QString(local_108);
  ::QVariant::~QVariant((QVariant *)local_a8);
  QString::~QString(local_128);
  ::QVariant::~QVariant(local_c8);
  ::QVariant::QVariant(local_88);
  QString::QString(local_e8,"percentage");
  QMap<QString,QVariant>::value(local_68,(QVariant *)(this + 0x88));
  iVar7 = ::QVariant::toInt((bool *)local_68);
  ::QVariant::~QVariant((QVariant *)local_68);
  QString::~QString(local_e8);
  ::QVariant::~QVariant(local_88);
  if ((!bVar6) && ((bVar3 || (0x13 < iVar7)))) {
    QQueue<std::function<void()>>::dequeue((QQueue<std::function<void()>> *)local_68);
    bVar6 = std::function::operator_cast_to_bool((function *)local_68);
    if (bVar6) {
      IdleIoScope::IdleIoScope((IdleIoScope *)local_e8,(bool)this[0x68]);
      std::function<void()>::operator()((function<void()> *)local_68);
      IdleIoScope::~IdleIoScope((IdleIoScope *)local_e8);
    }
    std::function<void()>::~function((function<void()> *)local_68);
  }
LAB_0020830c:
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00208332  Lelan::monoRawMs

/* Lelan::monoRawMs() const */

long Lelan::monoRawMs(void)

{
  long in_FS_OFFSET;
  timespec local_28;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  clock_gettime(4,&local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28.tv_sec * 1000 + local_28.tv_nsec / 1000000;
}



// ==== 002083a6  Lelan::onActionInvoked

/* Lelan::onActionInvoked(unsigned int, QString const&) */

void Lelan::onActionInvoked(uint param_1,QString *param_2)

{
  undefined4 in_register_0000003c;
  
  notificationsChanged((Lelan *)CONCAT44(in_register_0000003c,param_1));
  return;
}



// ==== 002083c8  Lelan::onLayoutUpdated

/* Lelan::onLayoutUpdated() */

void __thiscall Lelan::onLayoutUpdated(Lelan *this)

{
  trayChanged(this);
  return;
}



// ==== 00219740  Lelan::subscribeToNetworkManager()::{lambda()#1}::operator()

/* Lelan::subscribeToNetworkManager()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToNetworkManager()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  QVariant *this_00;
  QDebug *pQVar3;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_138 [8];
  QDebug local_130 [8];
  QString local_128 [32];
  QString local_108 [32];
  QMessageLogger local_e8 [32];
  QDBusError local_c8 [64];
  QString local_88 [64];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_138,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\0') {
    QMessageLogger::QMessageLogger(local_e8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar3 = (QDebug *)QDebug::operator<<(local_130,"[lelan] NetworkManager Get(State) failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar3 = (QDebug *)QDebug::operator<<(pQVar3,local_128);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar3,local_108);
    QString::~QString(local_108);
    QDBusError::~QDBusError((QDBusError *)local_88);
    QString::~QString(local_128);
    QDBusError::~QDBusError(local_c8);
    QDebug::~QDebug(local_130);
  }
  else {
    QDBusPendingReply<QVariant>::value(local_48);
    lVar1 = *(long *)this;
    QString::QString(local_88,"state");
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0x78),local_88);
    ::QVariant::operator=(this_00,(QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    networkChanged(*(Lelan **)this);
  }
  QObject::deleteLater();
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_138);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00219a3e  Lelan::subscribeToNetworkManager

/* WARNING: Removing unreachable block (ram,0x00219c2d) */
/* Lelan::subscribeToNetworkManager() */

void __thiscall Lelan::subscribeToNetworkManager(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QString local_140 [8];
  QString local_138 [8];
  QDBusPendingCallWatcher *local_130;
  QString local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  Lelan *local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_128,"org.freedesktop.NetworkManager");
  QString::QString(local_108,"/org/freedesktop/NetworkManager");
  QString::QString((QString *)&local_a8,"Get");
  QString::QString(local_c8,FDPROPS);
  QDBusMessage::createMethodCall(local_138,local_128,local_108,local_c8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  ::QVariant::QVariant(local_88,local_128);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_138,local_88);
  QString::QString((QString *)&local_a8,"State");
  ::QVariant::QVariant(local_68,(QString *)&local_a8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_a8);
  ::QVariant::~QVariant(local_88);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_140);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_130 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_130;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToNetworkManager()::_lambda()_1_>
            (local_c8,local_130,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  QString::QString((QString *)&local_a8,"StateChanged");
  QDBusConnection::connect
            (local_140,local_128,local_108,local_128,(QObject *)&local_a8,(char *)this);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"PropertiesChanged");
  QString::QString(local_c8,FDPROPS);
  QDBusConnection::connect(local_140,local_128,local_108,local_c8,(QObject *)&local_a8,(char *)this)
  ;
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"VpnStateChanged");
  QString::QString(local_c8,"org.freedesktop.NetworkManager.VPN.Connection");
  QString::QString(local_e8);
  QDBusConnection::connect(local_140,local_128,local_e8,local_c8,(QObject *)&local_a8,(char *)this);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  refreshVpnConnections(this);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_138);
  QString::~QString(local_108);
  QString::~QString(local_128);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_140);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0021a048  Lelan::onNetworkStateChanged

/* Lelan::onNetworkStateChanged(unsigned int) */

void __thiscall Lelan::onNetworkStateChanged(Lelan *this,uint param_1)

{
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_48,param_1);
  QString::QString(local_68,"state");
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x78),local_68);
  ::QVariant::operator=(this_00,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  networkChanged(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021a138  Lelan::onNmPropertiesChanged

/* Lelan::onNmPropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onNmPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  QString QVar2;
  QVariant *pQVar3;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"PrimaryConnection");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"PrimaryConnection");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QString::QString(local_a8,"primary");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(param_1 + 0x78),local_a8)
    ;
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    readActiveNetwork((Lelan *)param_1);
  }
  QString::QString(local_88,"State");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"State");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QString::QString(local_a8,"state");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(param_1 + 0x78),local_a8)
    ;
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"WirelessEnabled");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"WirelessEnabled");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QVar2 = (QString)::QVariant::toBool();
    param_1[200] = QVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    scheduleWifiChanged((Lelan *)param_1);
  }
  networkChanged((Lelan *)param_1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021a612  Lelan::onVpnStateChanged

/* Lelan::onVpnStateChanged(unsigned int, unsigned int) */

void __thiscall Lelan::onVpnStateChanged(Lelan *this,uint param_1,uint param_2)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_48,param_1);
  QString::QString(local_68,"state");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x80),local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"reason");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x80),local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  vpnStateChanged(this);
  refreshVpnConnections(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021a7c2  Lelan::subscribeToWifi()::{lambda()#1}::operator()

/* Lelan::subscribeToWifi()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToWifi()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  undefined1 uVar3;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_50 [8];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_50,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 != '\0') {
    QDBusPendingReply<QVariant>::value(local_48);
    lVar1 = *(long *)this;
    uVar3 = ::QVariant::toBool();
    *(undefined1 *)(lVar1 + 200) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    scheduleWifiChanged(*(Lelan **)this);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_50);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021ae0e  Lelan::subscribeToWifi()::{lambda()#2}::operator()

/* WARNING: Removing unreachable block (ram,0x0021b30b) */
/* Lelan::subscribeToWifi()::{lambda()#2}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToWifi()::{lambda()#2}::operator()(_lambda___2_ *this)

{
  QObject *pQVar1;
  char cVar2;
  QDebug *pQVar3;
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusPendingReply<QList<QDBusObjectPath>> local_208 [8];
  QDBusConnection local_200 [8];
  undefined8 local_1f8;
  undefined8 local_1f0;
  QString local_1e8 [8];
  QList<QDBusObjectPath> *local_1e0;
  undefined8 local_1d8;
  QDBusPendingCallWatcher *local_1d0;
  undefined *local_1c8;
  undefined *local_1c0;
  wchar16 *local_1b8;
  wchar16 *local_1b0;
  QString local_1a8 [32];
  QDebug local_188 [32];
  QString local_168 [32];
  QString local_148 [32];
  QMessageLogger local_128 [32];
  QDBusError local_108 [64];
  undefined8 local_c8;
  QDBusPendingCallWatcher *local_c0;
  QString aQStack_b8 [48];
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QList<QDBusObjectPath>>::QDBusPendingReply
            (local_208,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusConnection::systemBus();
    local_1c8 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_c8,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_1a8,(QArrayDataPointer *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_c8);
    QDBusPendingReply<QList<QDBusObjectPath>>::value
              ((QDBusPendingReply<QList<QDBusObjectPath>> *)local_188);
    local_1e0 = (QList<QDBusObjectPath> *)local_188;
    local_1f8 = QList<QDBusObjectPath>::begin(local_1e0);
    local_1f0 = QList<QDBusObjectPath>::end(local_1e0);
    while (cVar2 = QList<QDBusObjectPath>::iterator::operator!=((iterator *)&local_1f8,local_1f0),
          cVar2 != '\0') {
      local_1d8 = QList<QDBusObjectPath>::iterator::operator*((iterator *)&local_1f8);
      QDBusObjectPath::path();
      local_1c0 = &DAT_002aae2a;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"Get",3);
      QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
      QString::QString((QString *)&local_c8,FDPROPS);
      QDBusMessage::createMethodCall(local_1e8,local_1a8,local_168,(QString *)&local_c8);
      QString::~QString((QString *)&local_c8);
      QString::~QString((QString *)local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
      local_1b8 = L"org.freedesktop.NetworkManager.Device";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager.Device",0x25);
      QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
      ::QVariant::QVariant(local_88,(QString *)local_128);
      this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1e8,local_88);
      local_1b0 = L"DeviceType";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"DeviceType",10);
      QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_108);
      ::QVariant::QVariant(local_68,(QString *)&local_c8);
      QDBusMessage::operator<<(this_00,local_68);
      ::QVariant::~QVariant(local_68);
      QString::~QString((QString *)&local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant(local_88);
      QString::~QString((QString *)local_128);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      this_01 = operator_new(0x18);
      pQVar1 = *(QObject **)this;
      QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_200);
      QDBusPendingCallWatcher::QDBusPendingCallWatcher(this_01,(QDBusPendingCall *)&local_c8,pQVar1)
      ;
      local_1d0 = this_01;
      QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
      local_c8 = *(undefined8 *)this;
      local_c0 = local_1d0;
      QString::QString(aQStack_b8,local_168);
      QObject::operator()(local_108,local_1d0,QDBusPendingCallWatcher::finished,0,
                          *(undefined8 *)this,&local_c8,0);
      QMetaObject::Connection::~Connection((Connection *)local_108);
      const::{lambda()#1}::~subscribeToWifi((_lambda___1_ *)&local_c8);
      QDBusMessage::~QDBusMessage((QDBusMessage *)local_1e8);
      QString::~QString(local_168);
      QList<QDBusObjectPath>::iterator::operator++((iterator *)&local_1f8);
    }
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_188);
    QString::~QString(local_1a8);
    QDBusConnection::~QDBusConnection(local_200);
  }
  else {
    QMessageLogger::QMessageLogger(local_128,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar3 = (QDebug *)QDebug::operator<<(local_188,"[lelan] NetworkManager GetDevices failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar3 = (QDebug *)QDebug::operator<<(pQVar3,local_168);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar3,local_148);
    QString::~QString(local_148);
    QDBusError::~QDBusError((QDBusError *)&local_c8);
    QString::~QString(local_168);
    QDBusError::~QDBusError(local_108);
    QDebug::~QDebug(local_188);
  }
  QDBusPendingReply<QList<QDBusObjectPath>>::~QDBusPendingReply(local_208);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0021b64a  Lelan::subscribeToWifi

/* WARNING: Removing unreachable block (ram,0x0021bac5) */
/* WARNING: Removing unreachable block (ram,0x0021b93e) */
/* Lelan::subscribeToWifi() */

void __thiscall Lelan::subscribeToWifi(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *pQVar1;
  long in_FS_OFFSET;
  QDBusConnection local_170 [8];
  QString local_168 [8];
  QDBusPendingCallWatcher *local_160;
  QDBusPendingCallWatcher *local_158;
  undefined *local_150;
  wchar16 *local_148;
  undefined *local_140;
  wchar16 *local_138;
  wchar16 *local_130;
  QString local_128 [32];
  QString local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  Lelan *local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_140 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,
             L"org.freedesktop.NetworkManager",0x1e);
  QString::QString(local_128,(QArrayDataPointer *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  local_148 = L"/org/freedesktop/NetworkManager";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,
             L"/org/freedesktop/NetworkManager",0x1f);
  QString::QString(local_108,(QArrayDataPointer *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  local_150 = &DAT_002aae2a;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Get",3);
  QString::QString(local_c8,(QArrayDataPointer *)local_e8);
  QString::QString((QString *)&local_a8,FDPROPS);
  QDBusMessage::createMethodCall(local_168,local_128,local_108,(QString *)&local_a8);
  QString::~QString((QString *)&local_a8);
  QString::~QString(local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  ::QVariant::QVariant(local_88,local_128);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_168,local_88);
  local_138 = L"WirelessEnabled";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"WirelessEnabled",0xf);
  QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
  ::QVariant::QVariant(local_68,(QString *)&local_a8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  ::QVariant::~QVariant(local_88);
  pQVar1 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_170);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (pQVar1,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_160 = pQVar1;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_160;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToWifi()::_lambda()_1_>
            (local_c8,local_160,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  local_130 = L"GetDevices";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"GetDevices",10);
  QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
  QDBusMessage::createMethodCall((QString *)local_e8,local_128,local_108,local_128);
  QString::~QString((QString *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  pQVar1 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_170);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (pQVar1,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_158 = pQVar1;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_158;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToWifi()::_lambda()_2_>
            (local_c8,local_158,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_e8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_168);
  QString::~QString(local_108);
  QString::~QString(local_128);
  QDBusConnection::~QDBusConnection(local_170);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021bd30  Lelan::rebuildAccessPoints()::{lambda()#1}::operator()()::~ApAccum

/* ~ApAccum() */

void __thiscall
Lelan::rebuildAccessPoints()::{lambda()#1}::operator()()::~ApAccum(operator()(_ *this)

{
  QString::~QString((QString *)(this + 0x20));
  QList<QVariant>::~QList((QList<QVariant> *)this);
  return;
}



// ==== 0021ce6c  Lelan::rebuildAccessPoints()::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x0021d10f) */
/* WARNING: Removing unreachable block (ram,0x0021d0ff) */
/* WARNING: Removing unreachable block (ram,0x0021d3ad) */
/* WARNING: Removing unreachable block (ram,0x0021d495) */
/* Lelan::rebuildAccessPoints()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::rebuildAccessPoints()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QObject *pQVar1;
  char cVar2;
  undefined4 uVar3;
  QDebug *pQVar4;
  undefined1 (*pauVar5) [16];
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QList<QDBusObjectPath>> local_1f8 [8];
  QDBusConnection local_1f0 [8];
  undefined8 local_1e8;
  undefined8 local_1e0;
  QString local_1d8 [8];
  undefined1 (*local_1d0) [16];
  QList<QDBusObjectPath> *local_1c8;
  undefined8 local_1c0;
  QDBusPendingCallWatcher *local_1b8;
  wchar16 *local_1b0;
  undefined *local_1a8;
  wchar16 *local_1a0;
  QDBusPendingReply<QList<QDBusObjectPath>> local_198 [32];
  QDebug local_178 [32];
  QString local_158 [32];
  QString local_138 [32];
  QMessageLogger local_118 [32];
  QDBusError local_f8 [64];
  undefined8 local_b8;
  QDBusPendingCallWatcher *local_b0;
  QString aQStack_a8 [24];
  undefined1 (*local_90) [16];
  QString aQStack_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QList<QDBusObjectPath>>::QDBusPendingReply
            (local_1f8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QList<QDBusObjectPath>>::value(local_198);
    cVar2 = QList<QDBusObjectPath>::isEmpty((QList<QDBusObjectPath> *)local_198);
    if (cVar2 == '\0') {
      pauVar5 = operator_new(0x38);
      *pauVar5 = (undefined1  [16])0x0;
      pauVar5[1] = (undefined1  [16])0x0;
      pauVar5[2] = (undefined1  [16])0x0;
      *(undefined8 *)pauVar5[3] = 0;
      uVar3 = QList<QDBusObjectPath>::size((QList<QDBusObjectPath> *)local_198);
      *(undefined4 *)(pauVar5[1] + 8) = uVar3;
      QString::QString((QString *)(pauVar5 + 2),(QString *)(*(long *)this + 0xe8));
      local_1d0 = pauVar5;
      QDBusConnection::systemBus();
      local_1a8 = &DAT_002aace0;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_b8,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager",0x1e);
      QString::QString((QString *)local_178,(QArrayDataPointer *)&local_b8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_b8);
      local_1b0 = L"org.freedesktop.NetworkManager.AccessPoint";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_b8,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager.AccessPoint",0x2a);
      QString::QString(local_158,(QArrayDataPointer *)&local_b8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_b8);
      local_1c8 = (QList<QDBusObjectPath> *)local_198;
      local_1e8 = QList<QDBusObjectPath>::begin(local_1c8);
      local_1e0 = QList<QDBusObjectPath>::end(local_1c8);
      while (cVar2 = QList<QDBusObjectPath>::const_iterator::operator!=
                               ((const_iterator *)&local_1e8,local_1e0), cVar2 != '\0') {
        local_1c0 = QList<QDBusObjectPath>::const_iterator::operator*((const_iterator *)&local_1e8);
        QDBusObjectPath::path();
        local_1a0 = L"GetAll";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"GetAll",6);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        QString::QString((QString *)&local_b8,FDPROPS);
        QDBusMessage::createMethodCall
                  (local_1d8,(QString *)local_178,local_138,(QString *)&local_b8);
        QString::~QString((QString *)&local_b8);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::QVariant(local_68,local_158);
        QDBusMessage::operator<<((QDBusMessage *)local_1d8,local_68);
        ::QVariant::~QVariant(local_68);
        this_00 = operator_new(0x18);
        pQVar1 = *(QObject **)this;
        QDBusConnection::asyncCall((QDBusMessage *)&local_b8,(int)local_1f0);
        QDBusPendingCallWatcher::QDBusPendingCallWatcher
                  (this_00,(QDBusPendingCall *)&local_b8,pQVar1);
        local_1b8 = this_00;
        QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_b8);
        local_b8 = *(undefined8 *)this;
        local_b0 = local_1b8;
        QString::QString(aQStack_a8,local_138);
        local_90 = local_1d0;
        QString::QString(aQStack_88,(QString *)local_178);
        QObject::operator()(local_f8,local_1b8,QDBusPendingCallWatcher::finished,0,
                            *(undefined8 *)this,&local_b8,0);
        QMetaObject::Connection::~Connection((Connection *)local_f8);
        const::{lambda()#1}::~rebuildAccessPoints((_lambda___1_ *)&local_b8);
        QDBusMessage::~QDBusMessage((QDBusMessage *)local_1d8);
        QString::~QString(local_138);
        QList<QDBusObjectPath>::const_iterator::operator++((const_iterator *)&local_1e8);
      }
      QString::~QString(local_158);
      QString::~QString((QString *)local_178);
      QDBusConnection::~QDBusConnection(local_1f0);
    }
    else {
      cVar2 = QList<QVariant>::isEmpty((QList<QVariant> *)(*(long *)this + 0xa8));
      if (cVar2 != '\x01') {
        QList<QVariant>::clear((QList<QVariant> *)(*(long *)this + 0xa8));
        scheduleWifiChanged(*(Lelan **)this);
      }
    }
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_198);
  }
  else {
    QMessageLogger::QMessageLogger(local_118,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)
             QDebug::operator<<(local_178,"[lelan] NetworkManager GetAllAccessPoints failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,local_158);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar4,local_138);
    QString::~QString(local_138);
    QDBusError::~QDBusError((QDBusError *)&local_b8);
    QString::~QString(local_158);
    QDBusError::~QDBusError(local_f8);
    QDebug::~QDebug(local_178);
  }
  QDBusPendingReply<QList<QDBusObjectPath>>::~QDBusPendingReply(local_1f8);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021d726  Lelan::rebuildAccessPoints

/* WARNING: Removing unreachable block (ram,0x0021d927) */
/* Lelan::rebuildAccessPoints() */

void __thiscall Lelan::rebuildAccessPoints(Lelan *this)

{
  char cVar1;
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_108 [8];
  QString local_100 [8];
  QDBusPendingCallWatcher *local_f8;
  wchar16 *local_f0;
  wchar16 *local_e8;
  undefined *local_e0;
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  Lelan *local_58;
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0xd0));
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_e0 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_58,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_d8,(QArrayDataPointer *)&local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_58);
    local_e8 = L"GetAllAccessPoints";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_78,(QTypedArrayData *)0x0,L"GetAllAccessPoints",0x12);
    QString::QString((QString *)&local_58,(QArrayDataPointer *)local_78);
    local_f0 = L"org.freedesktop.NetworkManager.Device.Wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_b8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.Device.Wireless",
               0x2e);
    QString::QString(local_98,(QArrayDataPointer *)local_b8);
    QDBusMessage::createMethodCall(local_100,local_d8,(QString *)(this + 0xd0),local_98);
    QString::~QString(local_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
    QString::~QString((QString *)&local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
    this_00 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_108);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
    local_f8 = this_00;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
    local_50 = local_f8;
    local_58 = this;
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::rebuildAccessPoints()::_lambda()_1_>
              (local_78,local_f8,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
    QMetaObject::Connection::~Connection((Connection *)local_78);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_100);
    QString::~QString(local_d8);
    QDBusConnection::~QDBusConnection(local_108);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021e946  Lelan::readActiveNetwork()::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x0021f559) */
/* WARNING: Removing unreachable block (ram,0x0021eef7) */
/* WARNING: Removing unreachable block (ram,0x0021f239) */
/* Lelan::readActiveNetwork()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::readActiveNetwork()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  Lelan *this_00;
  QObject *pQVar1;
  bool bVar2;
  char cVar3;
  QDebug *pQVar4;
  QDBusMessage *pQVar5;
  QDBusPendingCallWatcher *pQVar6;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_1e8 [8];
  QString local_1e0 [8];
  QString local_1d8 [8];
  QDebug local_1d0 [8];
  QDBusPendingCallWatcher *local_1c8;
  QDBusPendingCallWatcher *local_1c0;
  QDBusPendingCallWatcher *local_1b8;
  undefined *local_1b0;
  wchar16 *local_1a8;
  wchar16 *local_1a0;
  undefined *local_198;
  wchar16 *local_190;
  wchar16 *local_188;
  undefined *local_180;
  wchar16 *local_178;
  wchar16 *local_170;
  QString local_168 [32];
  QString local_148 [32];
  QMessageLogger local_128 [32];
  QDBusError local_108 [64];
  undefined8 local_c8;
  QDBusPendingCallWatcher *local_c0;
  QString aQStack_b8 [48];
  QVariant local_88 [32];
  QDBusPendingReply<QVariant> local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_1e8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 != '\x01') {
    QMessageLogger::QMessageLogger(local_128,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)
             QDebug::operator<<(local_1d0,"[lelan] NetworkManager Get(ActiveAccessPoint) failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,local_168);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar4,local_148);
    QString::~QString(local_148);
    QDBusError::~QDBusError((QDBusError *)&local_c8);
    QString::~QString(local_168);
    QDBusError::~QDBusError(local_108);
    QDebug::~QDebug(local_1d0);
    goto LAB_0021f663;
  }
  QDBusPendingReply<QVariant>::value(local_68);
  qvariant_cast<QDBusObjectPath>((QVariant *)&local_c8);
  QDBusObjectPath::path();
  QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)&local_c8);
  ::QVariant::~QVariant((QVariant *)local_68);
  QString::operator=((QString *)(*(long *)this + 0xe8),local_168);
  cVar3 = QString::isEmpty(local_168);
  if (cVar3 == '\0') {
    QLatin1String::QLatin1String((QLatin1String *)&local_c8,"/");
    cVar3 = ::operator==(local_168,(QLatin1String *)&local_c8);
    if (cVar3 != '\0') goto LAB_0021ebbd;
    bVar2 = false;
  }
  else {
LAB_0021ebbd:
    bVar2 = true;
  }
  if (bVar2) {
    cVar3 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)(*(long *)this + 0xc0));
    if (cVar3 != '\x01') {
      QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)(*(long *)this + 0xc0));
      scheduleWifiChanged(*(Lelan **)this);
    }
    this_00 = *(Lelan **)this;
    QString::QString((QString *)&local_c8);
    syncWifiConnectedFlag(this_00,(QString *)&local_c8);
    QString::~QString((QString *)&local_c8);
  }
  else {
    local_1b0 = &DAT_002aae2a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"Get",3);
    QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
    QString::QString((QString *)&local_c8,FDPROPS);
    QDBusMessage::createMethodCall
              (local_1e0,(QString *)(this + 0x10),local_168,(QString *)&local_c8);
    QString::~QString((QString *)&local_c8);
    QString::~QString((QString *)local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
    local_1a8 = L"org.freedesktop.NetworkManager.AccessPoint";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager.AccessPoint",0x2a);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::QVariant::QVariant(local_88,(QString *)local_128);
    pQVar5 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1e0,local_88);
    local_1a0 = L"Ssid";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Ssid",4);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
    QDBusMessage::operator<<(pQVar5,(QVariant *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    pQVar6 = operator_new(0x18);
    pQVar1 = *(QObject **)this;
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_108);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher(pQVar6,(QDBusPendingCall *)&local_c8,pQVar1);
    local_1c8 = pQVar6;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_108);
    local_c8 = *(undefined8 *)this;
    local_c0 = local_1c8;
    QObject::operator()(local_108,local_1c8,QDBusPendingCallWatcher::finished,0,*(undefined8 *)this,
                        &local_c8,0);
    QMetaObject::Connection::~Connection((Connection *)local_108);
    local_198 = &DAT_002aae2a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"Get",3);
    QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
    QString::QString((QString *)&local_c8,FDPROPS);
    QDBusMessage::createMethodCall
              (local_1d8,(QString *)(this + 0x10),(QString *)(*(long *)this + 0xd0),
               (QString *)&local_c8);
    QString::~QString((QString *)&local_c8);
    QString::~QString((QString *)local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
    local_190 = L"org.freedesktop.NetworkManager.Device.Wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager.Device.Wireless",0x2e);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::QVariant::QVariant(local_88,(QString *)local_128);
    pQVar5 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1d8,local_88);
    local_188 = L"Bitrate";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Bitrate",7);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
    QDBusMessage::operator<<(pQVar5,(QVariant *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    pQVar6 = operator_new(0x18);
    pQVar1 = *(QObject **)this;
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_108);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher(pQVar6,(QDBusPendingCall *)&local_c8,pQVar1);
    local_1c0 = pQVar6;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_108);
    local_c8 = *(undefined8 *)this;
    local_c0 = local_1c0;
    QObject::operator()(local_108,local_1c0,QDBusPendingCallWatcher::finished,0,*(undefined8 *)this,
                        &local_c8,0);
    QMetaObject::Connection::~Connection((Connection *)local_108);
    local_180 = &DAT_002aae2a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"Get",3);
    QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
    QString::QString((QString *)&local_c8,FDPROPS);
    QDBusMessage::createMethodCall
              ((QString *)local_1d0,(QString *)(this + 0x10),(QString *)(*(long *)this + 0xd0),
               (QString *)&local_c8);
    QString::~QString((QString *)&local_c8);
    QString::~QString((QString *)local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
    local_178 = L"org.freedesktop.NetworkManager.Device";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager.Device",0x25);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::QVariant::QVariant(local_88,(QString *)local_128);
    pQVar5 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1d0,local_88);
    local_170 = L"Ip4Config";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Ip4Config",9);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
    QDBusMessage::operator<<(pQVar5,(QVariant *)local_68);
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    pQVar6 = operator_new(0x18);
    pQVar1 = *(QObject **)this;
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_108);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher(pQVar6,(QDBusPendingCall *)&local_c8,pQVar1);
    local_1b8 = pQVar6;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_108);
    local_c8 = *(undefined8 *)this;
    local_c0 = local_1b8;
    QString::QString(aQStack_b8,(QString *)(this + 0x10));
    QObject::operator()(local_108,local_1b8,QDBusPendingCallWatcher::finished,0,*(undefined8 *)this,
                        &local_c8,0);
    QMetaObject::Connection::~Connection((Connection *)local_108);
    const::{lambda()#3}::~readActiveNetwork((_lambda___3_ *)&local_c8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1d0);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1d8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1e0);
  }
  QString::~QString(local_168);
LAB_0021f663:
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_1e8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0021fa6a  Lelan::readActiveNetwork()::{lambda()#1}::~readActiveNetwork

/* ~readActiveNetwork() */

void __thiscall Lelan::readActiveNetwork()::{lambda()#1}::~readActiveNetwork(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 0021fa8a  Lelan::readActiveNetwork

/* WARNING: Removing unreachable block (ram,0x0021fda8) */
/* Lelan::readActiveNetwork() */

void __thiscall Lelan::readActiveNetwork(Lelan *this)

{
  char cVar1;
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_170 [8];
  QString local_168 [8];
  QDBusPendingCallWatcher *local_160;
  undefined *local_158;
  undefined *local_150;
  wchar16 *local_148;
  wchar16 *local_140;
  QString local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  Lelan *local_b8;
  QDBusPendingCallWatcher *local_b0;
  QString aQStack_a8 [32];
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0xd0));
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_150 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_b8,(QTypedArrayData *)0x0,
               L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_138,(QArrayDataPointer *)&local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_b8);
    local_158 = &DAT_002aae2a;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"Get",3);
    QString::QString(local_d8,(QArrayDataPointer *)local_f8);
    QString::QString((QString *)&local_b8,FDPROPS);
    QDBusMessage::createMethodCall
              (local_168,local_138,(QString *)(this + 0xd0),(QString *)&local_b8);
    QString::~QString((QString *)&local_b8);
    QString::~QString(local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
    local_148 = L"org.freedesktop.NetworkManager.Device.Wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_118,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.Device.Wireless",
               0x2e);
    QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
    ::QVariant::QVariant(local_88,(QString *)local_f8);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_168,local_88);
    local_140 = L"ActiveAccessPoint";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_d8,(QTypedArrayData *)0x0,L"ActiveAccessPoint",
               0x11);
    QString::QString((QString *)&local_b8,(QArrayDataPointer *)local_d8);
    ::QVariant::QVariant(local_68,(QString *)&local_b8);
    QDBusMessage::operator<<(this_00,local_68);
    ::QVariant::~QVariant(local_68);
    QString::~QString((QString *)&local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_d8);
    ::QVariant::~QVariant(local_88);
    QString::~QString((QString *)local_f8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
    this_01 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_b8,(int)local_170);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_01,(QDBusPendingCall *)&local_b8,(QObject *)this);
    local_160 = this_01;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_b8);
    local_b0 = local_160;
    local_b8 = this;
    QString::QString(aQStack_a8,local_138);
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::readActiveNetwork()::_lambda()_1_>
              (local_d8,local_160,QDBusPendingCallWatcher::finished,0,this,&local_b8,0);
    QMetaObject::Connection::~Connection((Connection *)local_d8);
    readActiveNetwork()::{lambda()#1}::~readActiveNetwork((_lambda___1_ *)&local_b8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_168);
    QString::~QString(local_138);
    QDBusConnection::~QDBusConnection(local_170);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0021ffd4  Lelan::scheduleWifiChanged()::{lambda()#1}::operator()

/* Lelan::scheduleWifiChanged()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::scheduleWifiChanged()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  *(undefined1 *)(*(long *)this + 0x100) = 0;
  wifiChanged(*(Lelan **)this);
  return;
}



// ==== 00220000  Lelan::scheduleWifiChanged

/* Lelan::scheduleWifiChanged() */

void __thiscall Lelan::scheduleWifiChanged(Lelan *this)

{
  long in_FS_OFFSET;
  Lelan *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x100] == (Lelan)0x0) {
    this[0x100] = (Lelan)0x1;
    local_18 = this;
    QTimer::singleShot<int,Lelan::scheduleWifiChanged()::_lambda()_1_>
              (0,(ContextType *)this,(_lambda___1_ *)&local_18);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0022006c  Lelan::syncWifiConnectedFlag

/* Lelan::syncWifiConnectedFlag(QString const&) */

void __thiscall Lelan::syncWifiConnectedFlag(Lelan *this,QString *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  bool bVar8;
  QVariant *pQVar9;
  long lVar10;
  long in_FS_OFFSET;
  int local_12c;
  QVariant local_128 [8];
  wchar16 *local_120;
  wchar16 *local_118;
  wchar16 *local_110;
  QList<QVariant> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  bVar6 = false;
  QList<QVariant>::QList(local_108,(QList *)(this + 0xa8));
  local_12c = 0;
  do {
    lVar10 = QList<QVariant>::size(local_108);
    if (lVar10 <= local_12c) {
      if (bVar6) {
        QList<QVariant>::operator=((QList<QVariant> *)(this + 0xa8),(QList *)local_108);
        scheduleWifiChanged(this);
      }
      QList<QVariant>::~QList(local_108);
      if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    QList<QVariant>::at(local_108,(long)local_12c);
    ::QVariant::toMap();
    bVar5 = false;
    bVar4 = false;
    bVar3 = false;
    bVar2 = false;
    bVar1 = false;
    cVar7 = QString::isEmpty(param_1);
    if (cVar7 == '\x01') {
LAB_00220202:
      bVar8 = false;
    }
    else {
      ::QVariant::QVariant(local_88);
      bVar5 = true;
      local_120 = L"ssid";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"ssid",4);
      bVar4 = true;
      QString::QString(local_c8,(QArrayDataPointer *)local_e8);
      bVar3 = true;
      QMap<QString,QVariant>::value(local_68,local_128);
      bVar2 = true;
      ::QVariant::toString();
      bVar1 = true;
      cVar7 = ::operator==(local_a8,param_1);
      if (cVar7 == '\0') goto LAB_00220202;
      bVar8 = true;
    }
    if (bVar1) {
      QString::~QString(local_a8);
    }
    if (bVar2) {
      ::QVariant::~QVariant((QVariant *)local_68);
    }
    if (bVar3) {
      QString::~QString(local_c8);
    }
    if (bVar4) {
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    }
    if (bVar5) {
      ::QVariant::~QVariant(local_88);
    }
    ::QVariant::QVariant(local_88);
    local_118 = L"connected";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"connected",9);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_68,local_128);
    cVar7 = ::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_68);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_88);
    if (bVar8 != (bool)cVar7) {
      ::QVariant::QVariant((QVariant *)local_68,bVar8);
      local_110 = L"connected";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"connected",9);
      QString::QString(local_a8,(QArrayDataPointer *)local_c8);
      pQVar9 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_128,local_a8);
      ::QVariant::operator=(pQVar9,(QVariant *)local_68);
      QString::~QString(local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QVariant::QVariant((QVariant *)local_68,(QMap *)local_128);
      pQVar9 = (QVariant *)QList<QVariant>::operator[](local_108,(long)local_12c);
      ::QVariant::operator=(pQVar9,(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
      bVar6 = true;
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_128);
    local_12c = local_12c + 1;
  } while( true );
}



// ==== 00220620  Lelan::onWifiPropertiesChanged

/* Lelan::onWifiPropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onWifiPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QLatin1String local_58 [24];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QLatin1String::QLatin1String(local_58,"org.freedesktop.NetworkManager.Device.Wireless");
  cVar4 = ::operator!=((QString *)param_2,local_58);
  if (cVar4 != '\0') goto LAB_00220912;
  bVar2 = false;
  bVar1 = false;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_b8,(QTypedArrayData *)0x0,L"LastScan",8);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  cVar4 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_98);
  if (cVar4 == '\0') {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_78,(QTypedArrayData *)0x0,L"AccessPoints",0xc);
    bVar2 = true;
    QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
    bVar1 = true;
    cVar4 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,(QString *)local_58);
    if (cVar4 != '\0') goto LAB_00220771;
    bVar3 = false;
  }
  else {
LAB_00220771:
    bVar3 = true;
  }
  if (bVar1) {
    QString::~QString((QString *)local_58);
  }
  if (bVar2) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  }
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  if (bVar3) {
    rebuildAccessPoints((Lelan *)param_1);
  }
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"ActiveAccessPoint",0x11);
  QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
  cVar4 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,(QString *)local_58);
  QString::~QString((QString *)local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  if (cVar4 != '\0') {
    readActiveNetwork((Lelan *)param_1);
  }
LAB_00220912:
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00220938  Lelan::setWifiEnabled

/* Lelan::setWifiEnabled(bool) */

void __thiscall Lelan::setWifiEnabled(Lelan *this,bool param_1)

{
  QDBusMessage *pQVar1;
  long in_FS_OFFSET;
  QDBusConnection local_1e0 [8];
  QString local_1d8 [8];
  undefined *local_1d0;
  undefined *local_1c8;
  wchar16 *local_1c0;
  undefined *local_1b8;
  wchar16 *local_1b0;
  QArrayDataPointer<char16_t> local_1a8 [32];
  QString local_188 [32];
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QDBusVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_1d0 = &DAT_002ab1dc;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Set",3);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QString::QString(local_e8,FDPROPS);
  local_1c0 = L"/org/freedesktop/NetworkManager";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_168,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager",0x1f);
  QString::QString(local_148,(QArrayDataPointer *)local_168);
  local_1c8 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1a8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
  QString::QString(local_188,(QArrayDataPointer *)local_1a8);
  QDBusMessage::createMethodCall(local_1d8,local_188,local_148,local_e8);
  QString::~QString(local_188);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1a8);
  QString::~QString(local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  QString::~QString(local_e8);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_1b8 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
             L"org.freedesktop.NetworkManager",0x1e);
  QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
  ::QVariant::QVariant(local_c8,(QString *)local_128);
  pQVar1 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1d8,local_c8);
  local_1b0 = L"WirelessEnabled";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"WirelessEnabled",0xf)
  ;
  QString::QString(local_e8,(QArrayDataPointer *)local_108);
  ::QVariant::QVariant(local_a8,local_e8);
  pQVar1 = (QDBusMessage *)QDBusMessage::operator<<(pQVar1,local_a8);
  ::QVariant::QVariant(local_88,param_1);
  QDBusVariant::QDBusVariant(local_68,local_88);
  ::QVariant::fromValue<QDBusVariant,true>(local_48,local_68);
  QDBusMessage::operator<<(pQVar1,local_48);
  ::QVariant::~QVariant(local_48);
  QDBusVariant::~QDBusVariant(local_68);
  ::QVariant::~QVariant(local_88);
  ::QVariant::~QVariant(local_a8);
  QString::~QString(local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
  ::QVariant::~QVariant(local_c8);
  QString::~QString((QString *)local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
  QDBusConnection::asyncCall((QDBusMessage *)local_e8,(int)local_1e0);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_e8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_1d8);
  QDBusConnection::~QDBusConnection(local_1e0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00220e68  Lelan::connectWifi(QString_const&,QString_const&)::{lambda()#1}::operator()

/* Lelan::connectWifi(QString const&, QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const */

void __thiscall
Lelan::connectWifi(QString_const&,QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  QDebug *pQVar2;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusObjectPath,QDBusObjectPath> local_118 [8];
  QDebug local_110 [8];
  QString local_108 [32];
  QString local_e8 [32];
  QMessageLogger local_c8 [32];
  QDBusError local_a8 [64];
  QDBusError local_68 [72];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusObjectPath,QDBusObjectPath>::QDBusPendingReply
            (local_118,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isError();
  if (cVar1 == '\0') {
    readActiveNetwork(*(Lelan **)this);
    scheduleWifiChanged(*(Lelan **)this);
  }
  else {
    QMessageLogger::QMessageLogger(local_c8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar2 = (QDebug *)QDebug::operator<<(local_110,"[lelan] connectWifi failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,local_108);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar2,local_e8);
    QString::~QString(local_e8);
    QDBusError::~QDBusError(local_68);
    QString::~QString(local_108);
    QDBusError::~QDBusError(local_a8);
    QDebug::~QDebug(local_110);
  }
  QDBusPendingReply<QDBusObjectPath,QDBusObjectPath>::~QDBusPendingReply(local_118);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002210e0  Lelan::connectWifi

/* WARNING: Removing unreachable block (ram,0x00221f77) */
/* Lelan::connectWifi(QString const&, QString const&) */

void __thiscall Lelan::connectWifi(Lelan *this,QString *param_1,QString *param_2)

{
  bool bVar1;
  char cVar2;
  QVariant *pQVar3;
  QMap<QString,QVariant> *pQVar4;
  QDBusMessage *pQVar5;
  QDBusPendingCallWatcher *this_00;
  QString *this_01;
  long in_FS_OFFSET;
  undefined8 local_278;
  undefined8 local_270;
  undefined8 local_268;
  QDBusConnection local_260 [8];
  QString local_258 [8];
  QDBusPendingCallWatcher *local_250;
  undefined *local_248;
  wchar16 *local_240;
  wchar16 *local_238;
  wchar16 *local_230;
  wchar16 *local_228;
  wchar16 *local_220;
  wchar16 *local_218;
  wchar16 *local_210;
  wchar16 *local_208;
  wchar16 *local_200;
  wchar16 *local_1f8;
  wchar16 *local_1f0;
  wchar16 *local_1e8;
  undefined *local_1e0;
  wchar16 *local_1d8;
  undefined *local_1d0;
  wchar16 *local_1c8;
  undefined *local_1c0;
  wchar16 *local_1b8;
  undefined *local_1b0;
  QArrayDataPointer<char16_t> local_1a8 [32];
  QArrayDataPointer<char16_t> local_188 [32];
  QString local_168 [32];
  undefined8 local_148 [4];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  Lelan *local_c8;
  QDBusPendingCallWatcher *local_c0;
  QVariant local_a8 [32];
  undefined1 local_88 [16];
  QString aQStack_70 [8];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QString::isEmpty((QString *)(this + 0xd0));
  if ((cVar2 == '\0') && (cVar2 = QString::isEmpty(param_1), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (!bVar1) {
    local_278 = 0;
    ::QVariant::QVariant(local_68,param_1);
    local_248 = &DAT_002ab202;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"id",2);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_278,(QString *)&local_c8);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant(local_68);
    local_238 = L"802-11-wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"802-11-wireless",0xf);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    ::QVariant::QVariant(local_68,(QString *)&local_c8);
    local_240 = L"type";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"type",4);
    QString::QString(local_108,(QArrayDataPointer *)local_128);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_278,local_108);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
    ::QVariant::~QVariant(local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    local_88 = QUuid::createUuid();
    QUuid::toString(&local_c8,local_88,1);
    ::QVariant::QVariant(local_68,(QString *)&local_c8);
    local_230 = L"uuid";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"uuid",4);
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_278,(QString *)local_e8);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_68);
    QString::~QString((QString *)&local_c8);
    qgetenv((char *)local_108);
    QString::fromLocal8Bit<void>((QString *)local_e8,(QByteArray *)local_108);
    local_228 = L"user:";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"user:",5);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::operator+((QString *)local_88,(QString *)local_128);
    QList<QString>::QList(&local_c8,local_88,1);
    ::QVariant::QVariant(local_68,(QList *)&local_c8);
    local_220 = L"permissions";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_188,(QTypedArrayData *)0x0,L"permissions",0xb);
    QString::QString(local_168,(QArrayDataPointer *)local_188);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_278,local_168);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString(local_168);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_188);
    ::QVariant::~QVariant(local_68);
    QList<QString>::~QList((QList<QString> *)&local_c8);
    this_01 = aQStack_70;
    while (this_01 != (QString *)local_88) {
      this_01 = this_01 + -0x18;
      QString::~QString(this_01);
    }
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    QString::~QString((QString *)local_e8);
    QByteArray::~QByteArray((QByteArray *)local_108);
    local_270 = 0;
    QString::toUtf8((QString *)&local_c8);
    ::QVariant::QVariant(local_68,(QByteArray *)&local_c8);
    local_218 = L"ssid";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"ssid",4);
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_270,(QString *)local_e8);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_68);
    QByteArray::~QByteArray((QByteArray *)&local_c8);
    local_208 = L"infrastructure";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"infrastructure",0xe);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    ::QVariant::QVariant(local_68,(QString *)&local_c8);
    local_210 = L"mode";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"mode",4);
    QString::QString(local_108,(QArrayDataPointer *)local_128);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_270,local_108);
    ::QVariant::operator=(pQVar3,local_68);
    QString::~QString(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
    ::QVariant::~QVariant(local_68);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    local_268 = 0;
    local_200 = L"connection";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"connection",10)
    ;
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    pQVar4 = (QMap<QString,QVariant> *)
             QMap<QString,QMap<QString,QVariant>>::operator[]
                       ((QMap<QString,QMap<QString,QVariant>> *)&local_268,(QString *)&local_c8);
    QMap<QString,QVariant>::operator=(pQVar4,(QMap *)&local_278);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    local_1f8 = L"802-11-wireless";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"802-11-wireless",0xf);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    pQVar4 = (QMap<QString,QVariant> *)
             QMap<QString,QMap<QString,QVariant>>::operator[]
                       ((QMap<QString,QMap<QString,QVariant>> *)&local_268,(QString *)&local_c8);
    QMap<QString,QVariant>::operator=(pQVar4,(QMap *)&local_270);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    cVar2 = QString::isEmpty(param_2);
    if (cVar2 != '\x01') {
      local_148[0] = 0;
      local_1e8 = L"wpa-psk";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"wpa-psk",7);
      QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
      ::QVariant::QVariant(local_68,(QString *)&local_c8);
      local_1f0 = L"key-mgmt";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"key-mgmt",8)
      ;
      QString::QString(local_108,(QArrayDataPointer *)local_128);
      pQVar3 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_148,local_108);
      ::QVariant::operator=(pQVar3,local_68);
      QString::~QString(local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
      ::QVariant::~QVariant(local_68);
      QString::~QString((QString *)&local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      ::QVariant::QVariant(local_68,param_2);
      local_1e0 = &DAT_002ab2c6;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"psk",3);
      QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
      pQVar3 = (QVariant *)
               QMap<QString,QVariant>::operator[]
                         ((QMap<QString,QVariant> *)local_148,(QString *)&local_c8);
      ::QVariant::operator=(pQVar3,local_68);
      QString::~QString((QString *)&local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      ::QVariant::~QVariant(local_68);
      local_1d8 = L"802-11-wireless-security";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_e8,(QTypedArrayData *)0x0,L"802-11-wireless-security",0x18);
      QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
      pQVar4 = (QMap<QString,QVariant> *)
               QMap<QString,QMap<QString,QVariant>>::operator[]
                         ((QMap<QString,QMap<QString,QVariant>> *)&local_268,(QString *)&local_c8);
      QMap<QString,QVariant>::operator=(pQVar4,(QMap *)local_148);
      QString::~QString((QString *)&local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_148);
    }
    QDBusConnection::systemBus();
    local_1b8 = L"AddAndActivateConnection";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"AddAndActivateConnection",0x18);
    QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_e8);
    local_1c0 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_128,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_108,(QArrayDataPointer *)local_128);
    local_1c8 = L"/org/freedesktop/NetworkManager";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,
               L"/org/freedesktop/NetworkManager",0x1f);
    QString::QString((QString *)local_148,(QArrayDataPointer *)local_168);
    local_1d0 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_1a8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    QString::QString((QString *)local_188,(QArrayDataPointer *)local_1a8);
    QDBusMessage::createMethodCall(local_258,(QString *)local_188,(QString *)local_148,local_108);
    QString::~QString((QString *)local_188);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1a8);
    QString::~QString((QString *)local_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
    QString::~QString(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
    QString::~QString((QString *)&local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::fromValue<QMap<QString,QMap<QString,QVariant>>>(local_a8,(QMap *)&local_268);
    pQVar5 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_258,local_a8);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_128,(QString *)(this + 0xd0));
    ::QVariant::fromValue<QDBusObjectPath,true>((QVariant *)local_88,(QDBusObjectPath *)local_128);
    pQVar5 = (QDBusMessage *)QDBusMessage::operator<<(pQVar5,(QVariant *)local_88);
    local_1b0 = &DAT_002ab33a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"/",1);
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)&local_c8,(QString *)local_e8);
    ::QVariant::fromValue<QDBusObjectPath,true>(local_68,(QDBusObjectPath *)&local_c8);
    QDBusMessage::operator<<(pQVar5,local_68);
    ::QVariant::~QVariant(local_68);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)&local_c8);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant((QVariant *)local_88);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_128);
    ::QVariant::~QVariant(local_a8);
    this_00 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_260);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_00,(QDBusPendingCall *)&local_c8,(QObject *)this);
    local_250 = this_00;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
    local_c0 = local_250;
    local_c8 = this;
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::connectWifi(QString_const&,QString_const&)::_lambda()_1_>
              (local_e8,local_250,QDBusPendingCallWatcher::finished,0,this,&local_c8,0);
    QMetaObject::Connection::~Connection((Connection *)local_e8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_258);
    QDBusConnection::~QDBusConnection(local_260);
    QMap<QString,QMap<QString,QVariant>>::~QMap((QMap<QString,QMap<QString,QVariant>> *)&local_268);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_270);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_278);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00222548  Lelan::disconnectWifi

/* Lelan::disconnectWifi() */

void __thiscall Lelan::disconnectWifi(Lelan *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_100 [8];
  QString local_f8 [8];
  undefined *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0xd0));
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_e0 = L"Disconnect";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"Disconnect",10)
    ;
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    local_e8 = L"org.freedesktop.NetworkManager.Device";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_98,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.Device",0x25);
    QString::QString(local_78,(QArrayDataPointer *)local_98);
    local_f0 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_d8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    QDBusMessage::createMethodCall(local_f8,local_b8,(QString *)(this + 0xd0),local_78);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    QString::~QString(local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    QDBusConnection::asyncCall((QDBusMessage *)local_38,(int)local_100);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_38);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_f8);
    QDBusConnection::~QDBusConnection(local_100);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002227e6  Lelan::refreshVpnConnections()::{lambda()#1}::operator()()::~VAcc

/* ~VAcc() */

void __thiscall
Lelan::refreshVpnConnections()::{lambda()#1}::operator()()::~VAcc(operator()(_ *this)

{
  QHash<QString,QString>::~QHash((QHash<QString,QString> *)(this + 0x18));
  QList<QVariant>::~QList((QList<QVariant> *)this);
  return;
}



// ==== 0022342a  Lelan::refreshVpnConnections()::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x002236cf) */
/* WARNING: Removing unreachable block (ram,0x002236ae) */
/* WARNING: Removing unreachable block (ram,0x002236bf) */
/* WARNING: Removing unreachable block (ram,0x00223919) */
/* WARNING: Removing unreachable block (ram,0x002239d2) */
/* Lelan::refreshVpnConnections()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshVpnConnections()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QObject *pQVar1;
  char cVar2;
  undefined4 uVar3;
  QDebug *pQVar4;
  undefined1 (*pauVar5) [16];
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QList<QDBusObjectPath>> local_1e8 [8];
  QDBusConnection local_1e0 [8];
  undefined8 local_1d8;
  undefined8 local_1d0;
  QString local_1c8 [8];
  undefined1 (*local_1c0) [16];
  QList<QDBusObjectPath> *local_1b8;
  undefined8 local_1b0;
  QDBusPendingCallWatcher *local_1a8;
  undefined *local_1a0;
  undefined *local_198;
  wchar16 *local_190;
  QDBusPendingReply<QList<QDBusObjectPath>> local_188 [32];
  QString local_168 [32];
  QDebug local_148 [32];
  QString local_128 [32];
  QString local_108 [32];
  QMessageLogger local_e8 [32];
  QDBusError local_c8 [64];
  undefined8 local_88;
  QDBusPendingCallWatcher *local_80;
  QString aQStack_78 [24];
  undefined1 (*local_60) [16];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QList<QDBusObjectPath>>::QDBusPendingReply
            (local_1e8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QList<QDBusObjectPath>>::value(local_188);
    cVar2 = QList<QDBusObjectPath>::isEmpty((QList<QDBusObjectPath> *)local_188);
    if (cVar2 == '\0') {
      pauVar5 = operator_new(0x28);
      *pauVar5 = (undefined1  [16])0x0;
      pauVar5[1] = (undefined1  [16])0x0;
      *(undefined8 *)pauVar5[2] = 0;
      uVar3 = QList<QDBusObjectPath>::size((QList<QDBusObjectPath> *)local_188);
      *(undefined4 *)pauVar5[2] = uVar3;
      local_1c0 = pauVar5;
      QDBusConnection::systemBus();
      local_1b8 = (QList<QDBusObjectPath> *)local_188;
      local_1d8 = QList<QDBusObjectPath>::begin(local_1b8);
      local_1d0 = QList<QDBusObjectPath>::end(local_1b8);
      while (cVar2 = QList<QDBusObjectPath>::const_iterator::operator!=
                               ((const_iterator *)&local_1d8,local_1d0), cVar2 != '\0') {
        local_1b0 = QList<QDBusObjectPath>::const_iterator::operator*((const_iterator *)&local_1d8);
        QDBusObjectPath::path();
        local_190 = L"GetSettings";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"GetSettings",0xb
                  );
        QString::QString((QString *)&local_88,(QArrayDataPointer *)local_c8);
        local_198 = &DAT_002ab3d8;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,
                   L"org.freedesktop.NetworkManager.Settings.Connection",0x32);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        local_1a0 = &DAT_002aace0;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                   L"org.freedesktop.NetworkManager",0x1e);
        QString::QString(local_128,(QArrayDataPointer *)local_148);
        QDBusMessage::createMethodCall(local_1c8,local_128,local_168,(QString *)local_e8);
        QString::~QString(local_128);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        QString::~QString((QString *)&local_88);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
        this_00 = operator_new(0x18);
        pQVar1 = *(QObject **)this;
        QDBusConnection::asyncCall((QDBusMessage *)&local_88,(int)local_1e0);
        QDBusPendingCallWatcher::QDBusPendingCallWatcher
                  (this_00,(QDBusPendingCall *)&local_88,pQVar1);
        local_1a8 = this_00;
        QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_88);
        local_88 = *(undefined8 *)this;
        local_80 = local_1a8;
        QString::QString(aQStack_78,local_168);
        local_60 = local_1c0;
        QObject::operator()(local_c8,local_1a8,QDBusPendingCallWatcher::finished,0,
                            *(undefined8 *)this,&local_88,0);
        QMetaObject::Connection::~Connection((Connection *)local_c8);
        const::{lambda()#1}::~refreshVpnConnections((_lambda___1_ *)&local_88);
        QDBusMessage::~QDBusMessage((QDBusMessage *)local_1c8);
        QString::~QString(local_168);
        QList<QDBusObjectPath>::const_iterator::operator++((const_iterator *)&local_1d8);
      }
      QDBusConnection::~QDBusConnection(local_1e0);
    }
    else {
      cVar2 = QList<QVariant>::isEmpty((QList<QVariant> *)(*(long *)this + 0x108));
      if (cVar2 != '\x01') {
        QList<QVariant>::clear((QList<QVariant> *)(*(long *)this + 0x108));
        QHash<QString,QString>::clear((QHash<QString,QString> *)(*(long *)this + 0x120));
        vpnStateChanged(*(Lelan **)this);
      }
    }
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_188);
  }
  else {
    QMessageLogger::QMessageLogger(local_e8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)
             QDebug::operator<<(local_148,"[lelan] NetworkManager ListConnections failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,local_128);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar4,local_108);
    QString::~QString(local_108);
    QDBusError::~QDBusError((QDBusError *)&local_88);
    QString::~QString(local_128);
    QDBusError::~QDBusError(local_c8);
    QDebug::~QDebug(local_148);
  }
  QDBusPendingReply<QList<QDBusObjectPath>>::~QDBusPendingReply(local_1e8);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00223c2c  Lelan::refreshVpnConnections

/* WARNING: Removing unreachable block (ram,0x00223e7e) */
/* Lelan::refreshVpnConnections() */

void __thiscall Lelan::refreshVpnConnections(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_170 [8];
  QString local_168 [8];
  QDBusPendingCallWatcher *local_160;
  undefined *local_158;
  wchar16 *local_150;
  wchar16 *local_148;
  wchar16 *local_140;
  QArrayDataPointer<char16_t> local_138 [32];
  QString local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  Lelan *local_58;
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_140 = L"ListConnections";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"ListConnections",0xf);
  QString::QString((QString *)&local_58,(QArrayDataPointer *)local_78);
  local_148 = L"org.freedesktop.NetworkManager.Settings";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager.Settings",0x27);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  local_150 = L"/org/freedesktop/NetworkManager/Settings";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_f8,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager/Settings",0x28);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  local_158 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_138,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
  QString::QString(local_118,(QArrayDataPointer *)local_138);
  QDBusMessage::createMethodCall(local_168,local_118,local_d8,local_98);
  QString::~QString(local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_138);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  QString::~QString((QString *)&local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_170);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_160 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  local_50 = local_160;
  local_58 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshVpnConnections()::_lambda()_1_>
            (local_78,local_160,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_168);
  QDBusConnection::~QDBusConnection(local_170);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002248e0  Lelan::markActiveVpns()::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x00224d81) */
/* Lelan::markActiveVpns()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::markActiveVpns()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QObject *pQVar1;
  char cVar2;
  QDebug *pQVar3;
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_1e0 [8];
  QDBusConnection local_1d8 [8];
  undefined8 local_1d0;
  undefined8 local_1c8;
  QString local_1c0 [8];
  QList<QDBusObjectPath> *local_1b8;
  undefined8 local_1b0;
  QDBusPendingCallWatcher *local_1a8;
  wchar16 *local_1a0;
  undefined *local_198;
  wchar16 *local_190;
  QVariant local_188 [32];
  QDebug local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QMessageLogger local_108 [32];
  QDBusError local_e8 [64];
  undefined8 local_a8;
  QDBusPendingCallWatcher *local_a0;
  QDBusPendingReply<QVariant> local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_1e0,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QVariant>::value(local_68);
    qdbus_cast<QList<QDBusObjectPath>>(local_188);
    ::QVariant::~QVariant((QVariant *)local_68);
    QDBusConnection::systemBus();
    local_1b8 = (QList<QDBusObjectPath> *)local_188;
    local_1d0 = QList<QDBusObjectPath>::begin(local_1b8);
    local_1c8 = QList<QDBusObjectPath>::end(local_1b8);
    while (cVar2 = QList<QDBusObjectPath>::const_iterator::operator!=
                             ((const_iterator *)&local_1d0,local_1c8), cVar2 != '\0') {
      local_1b0 = QList<QDBusObjectPath>::const_iterator::operator*((const_iterator *)&local_1d0);
      local_1a0 = L"GetAll";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"GetAll",6);
      QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
      QString::QString((QString *)&local_a8,FDPROPS);
      QDBusObjectPath::path();
      local_198 = &DAT_002aace0;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager",0x1e);
      QString::QString(local_148,(QArrayDataPointer *)local_168);
      QDBusMessage::createMethodCall(local_1c0,local_148,local_128,(QString *)&local_a8);
      QString::~QString(local_148);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
      QString::~QString(local_128);
      QString::~QString((QString *)&local_a8);
      QString::~QString((QString *)local_e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      local_190 = L"org.freedesktop.NetworkManager.Connection.Active";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager.Connection.Active",0x30);
      QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_e8);
      ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_a8);
      QDBusMessage::operator<<((QDBusMessage *)local_1c0,(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
      QString::~QString((QString *)&local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
      this_00 = operator_new(0x18);
      pQVar1 = *(QObject **)this;
      QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_1d8);
      QDBusPendingCallWatcher::QDBusPendingCallWatcher(this_00,(QDBusPendingCall *)&local_a8,pQVar1)
      ;
      local_1a8 = this_00;
      QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
      local_a8 = *(undefined8 *)this;
      local_a0 = local_1a8;
      QObject::operator()(local_e8,local_1a8,QDBusPendingCallWatcher::finished,0,*(undefined8 *)this
                          ,&local_a8,0);
      QMetaObject::Connection::~Connection((Connection *)local_e8);
      QDBusMessage::~QDBusMessage((QDBusMessage *)local_1c0);
      QList<QDBusObjectPath>::const_iterator::operator++((const_iterator *)&local_1d0);
    }
    QDBusConnection::~QDBusConnection(local_1d8);
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_188);
  }
  else {
    QMessageLogger::QMessageLogger(local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar3 = (QDebug *)
             QDebug::operator<<(local_168,
                                "[lelan] NetworkManager Get(ActiveConnections) failed (markActiveVpns):"
                               );
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar3 = (QDebug *)QDebug::operator<<(pQVar3,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar3,local_128);
    QString::~QString(local_128);
    QDBusError::~QDBusError((QDBusError *)&local_a8);
    QString::~QString(local_148);
    QDBusError::~QDBusError(local_e8);
    QDebug::~QDebug(local_168);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_1e0);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0022504e  Lelan::markActiveVpns

/* WARNING: Removing unreachable block (ram,0x002253b4) */
/* Lelan::markActiveVpns() */

void __thiscall Lelan::markActiveVpns(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_1a8 [8];
  QString local_1a0 [8];
  QDBusPendingCallWatcher *local_198;
  undefined *local_190;
  undefined *local_188;
  wchar16 *local_180;
  undefined *local_178;
  wchar16 *local_170;
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  Lelan *local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_190 = &DAT_002aae2a;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Get",3);
  QString::QString(local_c8,(QArrayDataPointer *)local_e8);
  QString::QString((QString *)&local_a8,FDPROPS);
  local_180 = L"/org/freedesktop/NetworkManager";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_128,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager",0x1f);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  local_188 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_168,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
  QString::QString(local_148,(QArrayDataPointer *)local_168);
  QDBusMessage::createMethodCall(local_1a0,local_148,local_108,(QString *)&local_a8);
  QString::~QString(local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  QString::~QString((QString *)&local_a8);
  QString::~QString(local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  local_178 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,
             L"org.freedesktop.NetworkManager",0x1e);
  QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
  ::QVariant::QVariant(local_88,(QString *)local_e8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1a0,local_88);
  local_170 = L"ActiveConnections";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"ActiveConnections",
             0x11);
  QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
  ::QVariant::QVariant(local_68,(QString *)&local_a8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  ::QVariant::~QVariant(local_88);
  QString::~QString((QString *)local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_1a8);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_198 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_198;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::markActiveVpns()::_lambda()_1_>
            (local_c8,local_198,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_1a0);
  QDBusConnection::~QDBusConnection(local_1a8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002255c2  Lelan::connectVpn

/* Lelan::connectVpn(QString const&) */

void Lelan::connectVpn(QString *param_1)

{
  char cVar1;
  QDBusMessage *pQVar2;
  long in_FS_OFFSET;
  QDBusConnection local_1e8 [8];
  QString local_1e0 [8];
  undefined *local_1d8;
  wchar16 *local_1d0;
  undefined *local_1c8;
  wchar16 *local_1c0;
  undefined *local_1b8;
  undefined *local_1b0;
  QString local_1a8 [32];
  QArrayDataPointer<char16_t> local_188 [32];
  QString local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_1a8);
  cVar1 = QString::isEmpty(local_1a8);
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_1c0 = L"ActivateConnection";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"ActivateConnection",0x12);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    local_1c8 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    local_1d0 = L"/org/freedesktop/NetworkManager";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_148,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager",0x1f);
    QString::QString(local_128,(QArrayDataPointer *)local_148);
    local_1d8 = &DAT_002aace0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_188,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
    QString::QString(local_168,(QArrayDataPointer *)local_188);
    QDBusMessage::createMethodCall(local_1e0,local_168,local_128,local_e8);
    QString::~QString(local_168);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_188);
    QString::~QString(local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_168,local_1a8);
    ::QVariant::fromValue<QDBusObjectPath,true>(local_88,(QDBusObjectPath *)local_168);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1e0,local_88);
    local_1b8 = &DAT_002ab33a;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"/",1);
    QString::QString(local_128,(QArrayDataPointer *)local_148);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_108,local_128);
    ::QVariant::fromValue<QDBusObjectPath,true>(local_68,(QDBusObjectPath *)local_108);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<(pQVar2,local_68);
    local_1b0 = &DAT_002ab33a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,L"/",1);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_a8,(QString *)local_c8);
    ::QVariant::fromValue<QDBusObjectPath,true>(local_48,(QDBusObjectPath *)local_a8);
    QDBusMessage::operator<<(pQVar2,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_a8);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
    ::QVariant::~QVariant(local_68);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_108);
    QString::~QString(local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    ::QVariant::~QVariant(local_88);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_168);
    QDBusConnection::asyncCall((QDBusMessage *)local_a8,(int)local_1e8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_a8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1e0);
    QDBusConnection::~QDBusConnection(local_1e8);
  }
  QString::~QString(local_1a8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002260de  Lelan::disconnectVpn(QString_const&)::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x00226609) */
/* WARNING: Removing unreachable block (ram,0x002266e7) */
/* Lelan::disconnectVpn(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::disconnectVpn(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QObject *pQVar1;
  char cVar2;
  QDebug *pQVar3;
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_208 [8];
  QDBusConnection local_200 [8];
  undefined8 local_1f8;
  undefined8 local_1f0;
  QString local_1e8 [8];
  QList<QDBusObjectPath> *local_1e0;
  undefined8 local_1d8;
  QDBusPendingCallWatcher *local_1d0;
  undefined *local_1c8;
  undefined *local_1c0;
  wchar16 *local_1b8;
  undefined *local_1b0;
  QVariant local_1a8 [32];
  QDebug local_188 [32];
  QString local_168 [32];
  QString local_148 [32];
  QMessageLogger local_128 [32];
  QDBusError local_108 [64];
  undefined8 local_c8;
  QDBusPendingCallWatcher *local_c0;
  QString aQStack_b8 [24];
  QString aQStack_a0 [24];
  QVariant local_88 [32];
  QDBusPendingReply<QVariant> local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_208,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QVariant>::value(local_68);
    qdbus_cast<QList<QDBusObjectPath>>(local_1a8);
    ::QVariant::~QVariant((QVariant *)local_68);
    QDBusConnection::systemBus();
    local_1e0 = (QList<QDBusObjectPath> *)local_1a8;
    local_1f8 = QList<QDBusObjectPath>::begin(local_1e0);
    local_1f0 = QList<QDBusObjectPath>::end(local_1e0);
    while (cVar2 = QList<QDBusObjectPath>::const_iterator::operator!=
                             ((const_iterator *)&local_1f8,local_1f0), cVar2 != '\0') {
      local_1d8 = QList<QDBusObjectPath>::const_iterator::operator*((const_iterator *)&local_1f8);
      QDBusObjectPath::path();
      local_1c8 = &DAT_002aae2a;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"Get",3);
      ::QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
      ::QString::QString((QString *)&local_c8,FDPROPS);
      local_1c0 = &DAT_002aace0;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager",0x1e);
      ::QString::QString(local_148,(QArrayDataPointer *)local_168);
      QDBusMessage::createMethodCall(local_1e8,local_148,(QString *)local_188,(QString *)&local_c8);
      ::QString::~QString(local_148);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
      ::QString::~QString((QString *)&local_c8);
      ::QString::~QString((QString *)local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
      local_1b8 = L"org.freedesktop.NetworkManager.Connection.Active";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                 L"org.freedesktop.NetworkManager.Connection.Active",0x30);
      ::QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
      ::QVariant::QVariant(local_88,(QString *)local_128);
      this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1e8,local_88);
      local_1b0 = &DAT_002ab50a;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Id",2);
      ::QString::QString((QString *)&local_c8,(QArrayDataPointer *)local_108);
      ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_c8);
      QDBusMessage::operator<<(this_00,(QVariant *)local_68);
      ::QVariant::~QVariant((QVariant *)local_68);
      ::QString::~QString((QString *)&local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
      ::QVariant::~QVariant(local_88);
      ::QString::~QString((QString *)local_128);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      this_01 = operator_new(0x18);
      pQVar1 = *(QObject **)this;
      QDBusConnection::asyncCall((QDBusMessage *)&local_c8,(int)local_200);
      QDBusPendingCallWatcher::QDBusPendingCallWatcher(this_01,(QDBusPendingCall *)&local_c8,pQVar1)
      ;
      local_1d0 = this_01;
      QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_c8);
      local_c8 = *(undefined8 *)this;
      local_c0 = local_1d0;
      ::QString::QString(aQStack_b8,(QString *)local_188);
      ::QString::QString(aQStack_a0,(QString *)(this + 0x10));
      QObject::operator()(local_108,local_1d0,QDBusPendingCallWatcher::finished,0,
                          *(undefined8 *)this,&local_c8,0);
      QMetaObject::Connection::~Connection((Connection *)local_108);
      const::{lambda()#1}::~QString((_lambda___1_ *)&local_c8);
      QDBusMessage::~QDBusMessage((QDBusMessage *)local_1e8);
      ::QString::~QString((QString *)local_188);
      QList<QDBusObjectPath>::const_iterator::operator++((const_iterator *)&local_1f8);
    }
    QDBusConnection::~QDBusConnection(local_200);
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_1a8);
  }
  else {
    QMessageLogger::QMessageLogger(local_128,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar3 = (QDebug *)
             QDebug::operator<<(local_188,
                                "[lelan] NetworkManager Get(ActiveConnections) failed (disconnectVpn):"
                               );
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar3 = (QDebug *)QDebug::operator<<(pQVar3,local_168);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar3,local_148);
    ::QString::~QString(local_148);
    QDBusError::~QDBusError((QDBusError *)&local_c8);
    ::QString::~QString(local_168);
    QDBusError::~QDBusError(local_108);
    QDebug::~QDebug(local_188);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_208);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002269ae  Lelan::disconnectVpn(QString_const&)::{lambda()#1}::~QString

/* ~QString() */

void __thiscall Lelan::disconnectVpn(QString_const&)::{lambda()#1}::~QString(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 0x10));
  return;
}



// ==== 002269ce  Lelan::disconnectVpn

/* WARNING: Removing unreachable block (ram,0x00226d3b) */
/* Lelan::disconnectVpn(QString const&) */

void __thiscall Lelan::disconnectVpn(Lelan *this,QString *param_1)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_1b8 [8];
  QString local_1b0 [8];
  QDBusPendingCallWatcher *local_1a8;
  undefined *local_1a0;
  undefined *local_198;
  wchar16 *local_190;
  undefined *local_188;
  wchar16 *local_180;
  QArrayDataPointer<char16_t> local_178 [32];
  QString local_158 [32];
  QArrayDataPointer<char16_t> local_138 [32];
  QString local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  Lelan *local_b8;
  QDBusPendingCallWatcher *local_b0;
  QString aQStack_a8 [32];
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_1a0 = &DAT_002aae2a;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"Get",3);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  QString::QString((QString *)&local_b8,FDPROPS);
  local_190 = L"/org/freedesktop/NetworkManager";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_138,(QTypedArrayData *)0x0,L"/org/freedesktop/NetworkManager",0x1f);
  QString::QString(local_118,(QArrayDataPointer *)local_138);
  local_198 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_178,(QTypedArrayData *)0x0,L"org.freedesktop.NetworkManager",0x1e);
  QString::QString(local_158,(QArrayDataPointer *)local_178);
  QDBusMessage::createMethodCall(local_1b0,local_158,local_118,(QString *)&local_b8);
  QString::~QString(local_158);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_178);
  QString::~QString(local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_138);
  QString::~QString((QString *)&local_b8);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  local_188 = &DAT_002aace0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,
             L"org.freedesktop.NetworkManager",0x1e);
  QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
  ::QVariant::QVariant(local_88,(QString *)local_f8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1b0,local_88);
  local_180 = L"ActiveConnections";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_d8,(QTypedArrayData *)0x0,L"ActiveConnections",
             0x11);
  QString::QString((QString *)&local_b8,(QArrayDataPointer *)local_d8);
  ::QVariant::QVariant(local_68,(QString *)&local_b8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_d8);
  ::QVariant::~QVariant(local_88);
  QString::~QString((QString *)local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_b8,(int)local_1b8);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_b8,(QObject *)this);
  local_1a8 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_b8);
  local_b0 = local_1a8;
  local_b8 = this;
  QString::QString(aQStack_a8,param_1);
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::disconnectVpn(QString_const&)::_lambda()_1_>
            (local_d8,local_1a8,QDBusPendingCallWatcher::finished,0,this,&local_b8,0);
  QMetaObject::Connection::~Connection((Connection *)local_d8);
  disconnectVpn(QString_const&)::{lambda()#1}::~QString((_lambda___1_ *)&local_b8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_1b0);
  QDBusConnection::~QDBusConnection(local_1b8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00228904  Lelan::readActiveNetwork()::{lambda()#1}::readActiveNetwork

/* readActiveNetwork({lambda()#1}&&) */

void __thiscall
Lelan::readActiveNetwork()::{lambda()#1}::readActiveNetwork
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  return;
}



// ==== 00228cb8  Lelan::disconnectVpn(QString_const&)::{lambda()#1}::QString

/* QString({lambda()#1}&&) */

void __thiscall
Lelan::disconnectVpn(QString_const&)::{lambda()#1}::QString
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
  ::QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  return;
}



// ==== 00234d70  Lelan::subscribeToAudio

/* Lelan::subscribeToAudio() */

void __thiscall Lelan::subscribeToAudio(Lelan *this)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  
  if ((*(long *)(this + 0x390) == 0) && (lVar3 = pa_threaded_mainloop_new(), lVar3 != 0)) {
    *(long *)(this + 0x390) = lVar3;
    uVar4 = pa_threaded_mainloop_get_api(lVar3);
    uVar4 = pa_context_new(uVar4,&LAB_002abb3f_1);
    *(undefined8 *)(this + 0x398) = uVar4;
    pa_context_set_state_callback(uVar4,(anonymous_namespace)::paStateCb,this);
    pa_threaded_mainloop_lock(lVar3);
    iVar2 = pa_context_connect(uVar4,0,2,0);
    if ((iVar2 < 0) || (iVar2 = pa_threaded_mainloop_start(lVar3), iVar2 < 0)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      pa_threaded_mainloop_unlock(lVar3);
      stopPulse(this);
    }
    else {
      pa_threaded_mainloop_unlock(lVar3);
    }
  }
  return;
}



// ==== 00234e7a  Lelan::applyPulseState

/* Lelan::applyPulseState(int, bool, QString const&, unsigned int, int) */

void __thiscall
Lelan::applyPulseState
          (Lelan *this,int param_1,bool param_2,QString *param_3,uint param_4,int param_5)

{
  char cVar1;
  QVariant *pQVar2;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(uint *)(this + 0x3a0) = param_4;
  if (param_5 < 1) {
    param_5 = 2;
  }
  *(int *)(this + 0x3a4) = param_5;
  cVar1 = ::operator!=(param_3,(QString *)(this + 0x3a8));
  QString::operator=((QString *)(this + 0x3a8),param_3);
  *(int *)(this + 0x328) = param_1;
  this[0x334] = (Lelan)param_2;
  ::QVariant::QVariant(local_48,param_1);
  QString::QString(local_68,"volume");
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x90),local_68);
  ::QVariant::operator=(pQVar2,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"muted");
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x90),local_68);
  ::QVariant::operator=(pQVar2,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_3);
  QString::QString(local_68,"sink");
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x90),local_68);
  ::QVariant::operator=(pQVar2,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  onAudioVolumeUpdated(this);
  onAudioMuteUpdated(this);
  audioChanged(this);
  if (cVar1 != '\0') {
    audioDeviceChanged(this);
    onFallbackSinkUpdated(this);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002351a6  Lelan::stopPulse

/* Lelan::stopPulse() */

void __thiscall Lelan::stopPulse(Lelan *this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (*(long *)(this + 0x390) != 0) {
    uVar1 = *(undefined8 *)(this + 0x390);
    pa_threaded_mainloop_stop(uVar1);
    if (*(long *)(this + 0x398) != 0) {
      uVar2 = *(undefined8 *)(this + 0x398);
      pa_context_disconnect(uVar2);
      pa_context_unref(uVar2);
      *(undefined8 *)(this + 0x398) = 0;
    }
    pa_threaded_mainloop_free(uVar1);
    *(undefined8 *)(this + 0x390) = 0;
  }
  return;
}



// ==== 00235244  Lelan::retryFallbackSink

/* Lelan::retryFallbackSink() */

void __thiscall Lelan::retryFallbackSink(Lelan *this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  if ((*(long *)(this + 0x390) == 0) || (*(long *)(this + 0x398) == 0)) {
    subscribeToAudio(this);
  }
  else {
    uVar1 = *(undefined8 *)(this + 0x390);
    uVar2 = *(undefined8 *)(this + 0x398);
    pa_threaded_mainloop_lock(uVar1);
    lVar3 = pa_context_get_server_info(uVar2,(anonymous_namespace)::paServerInfoCb,this);
    if (lVar3 != 0) {
      pa_operation_unref(lVar3);
    }
    pa_threaded_mainloop_unlock(uVar1);
  }
  return;
}



// ==== 002352e8  Lelan::applyChannelVolumes

/* Lelan::applyChannelVolumes() */

void __thiscall Lelan::applyChannelVolumes(Lelan *this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  long lVar4;
  long in_FS_OFFSET;
  double local_c0;
  double local_b8;
  undefined1 local_98 [4];
  undefined4 local_94;
  undefined4 local_90;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (((*(long *)(this + 0x390) != 0) && (*(long *)(this + 0x398) != 0)) &&
     (*(int *)(this + 0x3a0) != -1)) {
    uVar1 = *(undefined8 *)(this + 0x390);
    uVar2 = *(undefined8 *)(this + 0x398);
    uVar3 = qRound(((double)*(int *)(this + 0x328) / 100.0) * 65536.0);
    pa_cvolume_set(local_98,*(undefined4 *)(this + 0x3a4),uVar3);
    if (1 < *(int *)(this + 0x3a4)) {
      if (*(int *)(this + 0x3c0) < 0x33) {
        local_c0 = 1.0;
      }
      else {
        local_c0 = (100.0 - (double)*(int *)(this + 0x3c0)) / 50.0;
      }
      if (*(int *)(this + 0x3c0) < 0x32) {
        local_b8 = (double)*(int *)(this + 0x3c0) / 50.0;
      }
      else {
        local_b8 = 1.0;
      }
      local_94 = qRound(((double)*(int *)(this + 0x328) / 100.0) * local_c0 * 65536.0);
      local_90 = qRound(((double)*(int *)(this + 0x328) / 100.0) * local_b8 * 65536.0);
    }
    pa_threaded_mainloop_lock(uVar1);
    lVar4 = pa_context_set_sink_volume_by_index(uVar2,*(undefined4 *)(this + 0x3a0),local_98,0,0);
    if (lVar4 != 0) {
      pa_operation_unref(lVar4);
    }
    pa_threaded_mainloop_unlock(uVar1);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002355b6  Lelan::setVolume

/* Lelan::setVolume(int) */

void __thiscall Lelan::setVolume(Lelan *this,int param_1)

{
  int *piVar1;
  long in_FS_OFFSET;
  int local_24;
  Lelan *local_20;
  int local_18 [2];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18[1] = 100;
  local_18[0] = 0;
  local_24 = param_1;
  local_20 = this;
  piVar1 = qBound<int>(local_18,&local_24,local_18 + 1);
  local_24 = *piVar1;
  *(int *)(local_20 + 0x328) = local_24;
  applyChannelVolumes(local_20);
  onAudioVolumeUpdated(local_20);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023563a  Lelan::setBalance

/* Lelan::setBalance(int) */

void __thiscall Lelan::setBalance(Lelan *this,int param_1)

{
  int *piVar1;
  long in_FS_OFFSET;
  int local_24;
  Lelan *local_20;
  int local_18 [2];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18[1] = 100;
  local_18[0] = 0;
  local_24 = param_1;
  local_20 = this;
  piVar1 = qBound<int>(local_18,&local_24,local_18 + 1);
  local_24 = *piVar1;
  if (*(int *)(local_20 + 0x3c0) != local_24) {
    *(int *)(local_20 + 0x3c0) = local_24;
    applyChannelVolumes(local_20);
    audioChanged(local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002356d2  Lelan::applyOutputDevices

/* Lelan::applyOutputDevices(QList<QVariant> const&) */

void __thiscall Lelan::applyOutputDevices(Lelan *this,QList *param_1)

{
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0x3e0),param_1);
  audioDevicesChanged(this);
  return;
}



// ==== 0023570c  Lelan::applyInputDevices

/* Lelan::applyInputDevices(QList<QVariant> const&) */

void __thiscall Lelan::applyInputDevices(Lelan *this,QList *param_1)

{
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0x3f8),param_1);
  audioDevicesChanged(this);
  return;
}



// ==== 00235746  Lelan::applyDefaultSource

/* Lelan::applyDefaultSource(QString const&) */

void __thiscall Lelan::applyDefaultSource(Lelan *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator==(param_1,(QString *)(this + 0x410));
  if (cVar1 == '\0') {
    QString::operator=((QString *)(this + 0x410),param_1);
    audioDeviceChanged(this);
  }
  return;
}



// ==== 002357a0  Lelan::setOutputDevice

/* Lelan::setOutputDevice(QString const&) */

void __thiscall Lelan::setOutputDevice(Lelan *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  undefined8 local_100;
  undefined8 local_f8;
  QVariant local_f0 [8];
  undefined8 local_e8;
  undefined8 local_e0;
  long local_d8;
  QList<QVariant> *local_d0;
  long local_c8;
  undefined8 local_c0;
  long local_b8;
  undefined *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x390) != 0) && (*(long *)(this + 0x398) != 0)) {
    cVar2 = QString::isEmpty(param_1);
    if (cVar2 == '\0') {
      bVar1 = false;
      goto LAB_0023580e;
    }
  }
  bVar1 = true;
LAB_0023580e:
  if (!bVar1) {
    local_e8 = *(undefined8 *)(this + 0x390);
    local_e0 = *(undefined8 *)(this + 0x398);
    pa_threaded_mainloop_lock(local_e8);
    QString::toUtf8(local_88);
    uVar4 = QByteArray::constData((QByteArray *)local_88);
    local_d8 = pa_context_set_default_sink(local_e0,uVar4,0,0);
    QByteArray::~QByteArray((QByteArray *)local_88);
    if (local_d8 != 0) {
      pa_operation_unref(local_d8);
    }
    local_d0 = (QList<QVariant> *)(this + 0x3c8);
    local_100 = QList<QVariant>::begin(local_d0);
    local_f8 = QList<QVariant>::end(local_d0);
    while( true ) {
      cVar2 = QList<QVariant>::iterator::operator!=((iterator *)&local_100,local_f8);
      if (cVar2 == '\0') break;
      local_c0 = QList<QVariant>::iterator::operator*((iterator *)&local_100);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_68);
      local_b0 = &DAT_002abaf6;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"index",5);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,local_f0);
      uVar3 = ::QVariant::toUInt((bool *)local_48);
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f0);
      QString::toUtf8(local_88);
      uVar4 = QByteArray::constData((QByteArray *)local_88);
      local_b8 = pa_context_move_sink_input_by_name(local_e0,uVar3,uVar4,0,0);
      QByteArray::~QByteArray((QByteArray *)local_88);
      if (local_b8 != 0) {
        pa_operation_unref(local_b8);
      }
      QList<QVariant>::iterator::operator++((iterator *)&local_100);
    }
    pa_threaded_mainloop_unlock(local_e8);
    local_c8 = pa_context_get_server_info(local_e0,(anonymous_namespace)::paServerInfoCb,this);
    if (local_c8 != 0) {
      pa_operation_unref(local_c8);
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00235bca  Lelan::setInputDevice

/* Lelan::setInputDevice(QString const&) */

void __thiscall Lelan::setInputDevice(Lelan *this,QString *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  bool bVar3;
  char cVar4;
  undefined8 uVar5;
  long lVar6;
  long in_FS_OFFSET;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x390) != 0) && (*(long *)(this + 0x398) != 0)) {
    cVar4 = QString::isEmpty(param_1);
    if (cVar4 == '\0') {
      bVar3 = false;
      goto LAB_00235c26;
    }
  }
  bVar3 = true;
LAB_00235c26:
  if (!bVar3) {
    uVar1 = *(undefined8 *)(this + 0x390);
    uVar2 = *(undefined8 *)(this + 0x398);
    pa_threaded_mainloop_lock(uVar1);
    QString::toUtf8(local_38);
    uVar5 = QByteArray::constData((QByteArray *)local_38);
    lVar6 = pa_context_set_default_source(uVar2,uVar5,0,0);
    QByteArray::~QByteArray((QByteArray *)local_38);
    if (lVar6 != 0) {
      pa_operation_unref(lVar6);
    }
    pa_threaded_mainloop_unlock(uVar1);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00235d0a  Lelan::toggleMute

/* Lelan::toggleMute() */

void __thiscall Lelan::toggleMute(Lelan *this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  this[0x334] = (Lelan)((byte)this[0x334] ^ 1);
  if (((*(long *)(this + 0x390) != 0) && (*(long *)(this + 0x398) != 0)) &&
     (*(int *)(this + 0x3a0) != -1)) {
    uVar1 = *(undefined8 *)(this + 0x390);
    uVar2 = *(undefined8 *)(this + 0x398);
    pa_threaded_mainloop_lock(uVar1);
    lVar3 = pa_context_set_sink_mute_by_index
                      (uVar2,*(undefined4 *)(this + 0x3a0),this[0x334] != (Lelan)0x0,0,0);
    if (lVar3 != 0) {
      pa_operation_unref(lVar3);
    }
    pa_threaded_mainloop_unlock(uVar1);
  }
  onAudioMuteUpdated(this);
  return;
}



// ==== 00235e04  Lelan::setAppVolume

/* Lelan::setAppVolume(QString const&, int) */

void __thiscall Lelan::setAppVolume(Lelan *this,QString *param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  int local_17c;
  undefined8 local_178;
  undefined8 local_170;
  QVariant local_168 [8];
  QList<QVariant> *local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  long local_140;
  undefined1 *local_138;
  undefined *local_130;
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QString local_a8 [136];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x390) != 0) && (*(long *)(this + 0x398) != 0)) {
    local_17c = -1;
    local_160 = (QList<QVariant> *)(this + 0x3c8);
    local_178 = QList<QVariant>::begin(local_160);
    local_170 = QList<QVariant>::end(local_160);
    while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_178,local_170),
          cVar1 != '\0') {
      local_158 = QList<QVariant>::iterator::operator*((iterator *)&local_178);
      ::QVariant::toMap();
      ::QVariant::QVariant(local_c8);
      local_138 = &LAB_002abad4_4;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"name",4);
      QString::QString(local_108,(QArrayDataPointer *)local_128);
      QMap<QString,QVariant>::value(local_a8,local_168);
      ::QVariant::toString();
      cVar1 = ::operator==(local_e8,param_1);
      QString::~QString(local_e8);
      ::QVariant::~QVariant((QVariant *)local_a8);
      QString::~QString(local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
      ::QVariant::~QVariant(local_c8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_c8);
        local_130 = &DAT_002abaf6;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"index",5);
        QString::QString(local_e8,(QArrayDataPointer *)local_108);
        QMap<QString,QVariant>::value(local_a8,local_168);
        local_17c = ::QVariant::toUInt((bool *)local_a8);
        ::QVariant::~QVariant((QVariant *)local_a8);
        QString::~QString(local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        ::QVariant::~QVariant(local_c8);
      }
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
      if (cVar1 != '\0') break;
      QList<QVariant>::iterator::operator++((iterator *)&local_178);
    }
    if (local_17c != -1) {
      local_150 = *(undefined8 *)(this + 0x390);
      local_148 = *(undefined8 *)(this + 0x398);
      uVar2 = qRound(((double)param_2 / 100.0) * 65536.0);
      pa_cvolume_set(local_a8,2,uVar2);
      pa_threaded_mainloop_lock(local_150);
      local_140 = pa_context_set_sink_input_volume(local_148,local_17c,local_a8,0,0);
      if (local_140 != 0) {
        pa_operation_unref(local_140);
      }
      pa_threaded_mainloop_unlock(local_150);
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002362c4  Lelan::applyAppStreams

/* Lelan::applyAppStreams(QList<QVariant> const&) */

void __thiscall Lelan::applyAppStreams(Lelan *this,QList *param_1)

{
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0x3c8),param_1);
  appStreamsChanged(this);
  return;
}



// ==== 002362fe  Lelan::subscribeToPlayers()::{lambda()#1}::operator()

/* Lelan::subscribeToPlayers()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() */

void __thiscall Lelan::subscribeToPlayers()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  ulong uVar5;
  long in_FS_OFFSET;
  QDBusPendingReply<QList<QString>> local_160 [8];
  undefined8 local_158;
  undefined8 local_150;
  QList<QString> *local_148;
  QString *local_140;
  QDBusPendingReply<QList<QString>> local_138 [32];
  QString local_118 [32];
  QString local_f8 [32];
  QString local_d8 [16];
  undefined1 auStack_c8 [16];
  undefined1 auStack_b8 [16];
  undefined8 auStack_a8 [17];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QList<QString>>::QDBusPendingReply
            (local_160,(QDBusPendingCall *)(*(long *)(this + 0x10) + 0x10));
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 != '\0') {
    QDBusPendingReply<QList<QString>>::value(local_138);
    local_148 = (QList<QString> *)local_138;
    local_158 = QList<QString>::begin(local_148);
    local_150 = QList<QString>::end(local_148);
    while( true ) {
      cVar3 = QList<QString>::iterator::operator!=((iterator *)&local_158,local_150);
      if (cVar3 == '\0') break;
      local_140 = (QString *)QList<QString>::iterator::operator*((iterator *)&local_158);
      QString::QString(local_d8,"org.mpris.MediaPlayer2.");
      cVar3 = QString::startsWith(local_140,local_d8,1);
      QString::~QString(local_d8);
      if (cVar3 == '\x01') {
        lVar1 = *(long *)this;
        uVar4 = 0;
        do {
          uVar5 = (ulong)uVar4;
          *(undefined1 (*) [16])(local_d8 + uVar5) = (undefined1  [16])0x0;
          *(undefined1 (*) [16])(auStack_c8 + uVar5) = (undefined1  [16])0x0;
          *(undefined1 (*) [16])(auStack_b8 + uVar5) = (undefined1  [16])0x0;
          *(undefined1 (*) [16])((long)auStack_a8 + uVar5) = (undefined1  [16])0x0;
          uVar4 = uVar4 + 0x40;
        } while (uVar4 < 0x80);
        uVar5 = (ulong)uVar4;
        *(undefined1 (*) [16])(local_d8 + uVar5) = (undefined1  [16])0x0;
        *(undefined1 (*) [16])(auStack_c8 + uVar5) = (undefined1  [16])0x0;
        *(undefined1 (*) [16])(auStack_b8 + uVar5) = (undefined1  [16])0x0;
        *(undefined8 *)((long)auStack_a8 + uVar5) = 0;
        QHash<QString,Lelan::PlayerState>::insert
                  ((QHash<QString,Lelan::PlayerState> *)(lVar1 + 0x10),local_140,
                   (PlayerState *)local_d8);
        PlayerState::~PlayerState((PlayerState *)local_d8);
        cVar3 = QString::isEmpty((QString *)(*(long *)this + 0x18));
        if (cVar3 != '\0') {
          QString::operator=((QString *)(*(long *)this + 0x18),local_140);
        }
        pcVar2 = *(char **)this;
        QString::QString(local_d8,"PropertiesChanged");
        QString::QString(local_f8,FDPROPS);
        QString::QString(local_118,"/org/mpris/MediaPlayer2");
        QDBusConnection::connect
                  ((QString *)(this + 8),local_140,local_118,local_f8,(QObject *)local_d8,pcVar2);
        QString::~QString(local_118);
        QString::~QString(local_f8);
        QString::~QString(local_d8);
        pcVar2 = *(char **)this;
        QString::QString(local_d8,"Seeked");
        QString::QString(local_f8,"org.mpris.MediaPlayer2.Player");
        QString::QString(local_118,"/org/mpris/MediaPlayer2");
        QDBusConnection::connect
                  ((QString *)(this + 8),local_140,local_118,local_f8,(QObject *)local_d8,pcVar2);
        QString::~QString(local_118);
        QString::~QString(local_f8);
        QString::~QString(local_d8);
        fetchPlayer(*(Lelan **)this,local_140);
      }
      QList<QString>::iterator::operator++((iterator *)&local_158);
    }
    QList<QString>::~QList((QList<QString> *)local_138);
    mediaChanged(*(Lelan **)this);
  }
  QObject::deleteLater();
  QDBusPendingReply<QList<QString>>::~QDBusPendingReply(local_160);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023681e  Lelan::subscribeToPlayers()::{lambda()#1}::~subscribeToPlayers

/* ~subscribeToPlayers() */

void __thiscall Lelan::subscribeToPlayers()::{lambda()#1}::~subscribeToPlayers(_lambda___1_ *this)

{
  QDBusConnection::~QDBusConnection((QDBusConnection *)(this + 8));
  return;
}



// ==== 0023683e  Lelan::subscribeToPlayers

/* WARNING: Removing unreachable block (ram,0x0023699c) */
/* WARNING: Removing unreachable block (ram,0x00236a3e) */
/* Lelan::subscribeToPlayers() */

void __thiscall Lelan::subscribeToPlayers(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_d0 [8];
  QString local_c8 [8];
  QDBusPendingCallWatcher *local_c0;
  QString local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  Lelan *local_58;
  QDBusConnection aQStack_50 [8];
  QDBusPendingCallWatcher *local_48;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  QString::QString((QString *)&local_58,"ListNames");
  QString::QString(local_78,"org.freedesktop.DBus");
  QString::QString(local_98,"/org/freedesktop/DBus");
  QString::QString(local_b8,"org.freedesktop.DBus");
  QDBusMessage::createMethodCall(local_c8,local_b8,local_98,local_78);
  QString::~QString(local_b8);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString((QString *)&local_58);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_d0);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_c0 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  local_58 = this;
  QDBusConnection::QDBusConnection(aQStack_50,local_d0);
  local_48 = local_c0;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToPlayers()::_lambda()_1_>
            (local_78,local_c0,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  subscribeToPlayers()::{lambda()#1}::~subscribeToPlayers((_lambda___1_ *)&local_58);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_c8);
  QDBusConnection::~QDBusConnection(local_d0);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00236b7a  Lelan::fetchPlayer(QString_const&)::{lambda()#1}::operator()

/* Lelan::fetchPlayer(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::fetchPlayer(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  Lelan *this_00;
  char cVar1;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_30 [8];
  QDBusPendingReply<QMap<QString,QVariant>> local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_30,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 != '\0') {
    this_00 = *(Lelan **)this;
    QDBusPendingReply<QMap<QString,QVariant>>::value(local_28);
    applyPlayerProps(this_00,(QString *)(this + 8),(QMap *)local_28);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_28);
  }
  QObject::deleteLater();
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00236c7a  Lelan::fetchPlayer(QString_const&)::{lambda()#1}::~QString

/* ~QString() */

void __thiscall Lelan::fetchPlayer(QString_const&)::{lambda()#1}::~QString(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 8));
  return;
}



// ==== 00236c9a  Lelan::fetchPlayer

/* WARNING: Removing unreachable block (ram,0x00236e52) */
/* WARNING: Removing unreachable block (ram,0x00236f06) */
/* Lelan::fetchPlayer(QString const&) */

void __thiscall Lelan::fetchPlayer(Lelan *this,QString *param_1)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_f0 [8];
  QString local_e8 [8];
  QDBusPendingCallWatcher *local_e0;
  QString local_d8 [32];
  QString local_b8 [32];
  Lelan *local_98;
  QString aQStack_90 [24];
  QDBusPendingCallWatcher *local_78;
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  QString::QString((QString *)&local_98,"GetAll");
  QString::QString(local_b8,FDPROPS);
  QString::QString(local_d8,"/org/mpris/MediaPlayer2");
  QDBusMessage::createMethodCall(local_e8,param_1,local_d8,local_b8);
  QString::~QString(local_d8);
  QString::~QString(local_b8);
  QString::~QString((QString *)&local_98);
  QString::QString((QString *)&local_98,"org.mpris.MediaPlayer2.Player");
  ::QVariant::QVariant(local_68,(QString *)&local_98);
  QDBusMessage::operator<<((QDBusMessage *)local_e8,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_98);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_98,(int)local_f0);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_98,(QObject *)this);
  local_e0 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_98);
  local_98 = this;
  QString::QString(aQStack_90,param_1);
  local_78 = local_e0;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::fetchPlayer(QString_const&)::_lambda()_1_>
            (local_b8,local_e0,QDBusPendingCallWatcher::finished,0,this,&local_98,0);
  QMetaObject::Connection::~Connection((Connection *)local_b8);
  fetchPlayer(QString_const&)::{lambda()#1}::~QString((_lambda___1_ *)&local_98);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_e8);
  QDBusConnection::~QDBusConnection(local_f0);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00237064  Lelan::applyPlayerProps(QString_const&,QMap<QString,QVariant>const&)::{lambda(QString_const&)#1}::operator()

/* Lelan::applyPlayerProps(QString const&, QMap<QString, QVariant> const&)::{lambda(QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&) const */

undefined8 __thiscall
Lelan::applyPlayerProps(QString_const&,QMap<QString,QVariant>const&)::{lambda(QString_const&)#1}::
operator()(_lambda_QString_const___1_ *this,QString *param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  QString local_88 [32];
  QString local_68 [32];
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = false;
  bVar1 = false;
  QString::QString(local_88,"org.mpris.MediaPlayer2.chromium.");
  cVar3 = QString::startsWith(param_1,local_88,1);
  if (cVar3 == '\0') {
    QString::QString(local_68,"org.mpris.MediaPlayer2.firefox.");
    bVar2 = true;
    cVar3 = QString::startsWith(param_1,local_68,1);
    if (cVar3 == '\0') {
      QString::QString(local_48,"org.mpris.MediaPlayer2.plasma-browser-integration");
      bVar1 = true;
      cVar3 = QString::startsWith(param_1,local_48,1);
      if (cVar3 == '\0') {
        uVar4 = 0;
        goto LAB_0023715f;
      }
    }
  }
  uVar4 = 1;
LAB_0023715f:
  if (bVar1) {
    QString::~QString(local_48);
  }
  if (bVar2) {
    QString::~QString(local_68);
  }
  QString::~QString(local_88);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00237212  Lelan::applyPlayerProps

/* Lelan::applyPlayerProps(QString const&, QMap<QString, QVariant> const&) */

void __thiscall Lelan::applyPlayerProps(Lelan *this,QString *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  Lelan LVar3;
  undefined8 uVar4;
  QVariant *pQVar5;
  uint uVar6;
  ulong uVar7;
  long in_FS_OFFSET;
  undefined8 local_1d8;
  QString *local_1d0;
  QString local_1c8 [32];
  QList<QString> local_1a8 [32];
  char *local_188 [4];
  char *local_168 [2];
  undefined1 auStack_158 [8];
  QString local_150 [8];
  undefined1 auStack_148 [16];
  QString local_138 [24];
  QString local_120 [24];
  QString local_108 [48];
  longlong local_d8;
  longlong local_d0;
  QString local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QHash<QString,Lelan::PlayerState>::contains
                    ((QHash<QString,Lelan::PlayerState> *)(this + 0x10),param_1);
  if (cVar1 != '\x01') {
    uVar6 = 0;
    do {
      uVar7 = (ulong)uVar6;
      *(undefined1 (*) [16])((long)local_168 + uVar7) = (undefined1  [16])0x0;
      *(undefined1 (*) [16])(auStack_158 + uVar7) = (undefined1  [16])0x0;
      *(undefined1 (*) [16])(auStack_148 + uVar7) = (undefined1  [16])0x0;
      *(undefined1 (*) [16])(local_138 + uVar7) = (undefined1  [16])0x0;
      uVar6 = uVar6 + 0x40;
    } while (uVar6 < 0x80);
    uVar7 = (ulong)uVar6;
    *(undefined1 (*) [16])((long)local_168 + uVar7) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(auStack_158 + uVar7) = (undefined1  [16])0x0;
    *(undefined1 (*) [16])(auStack_148 + uVar7) = (undefined1  [16])0x0;
    *(undefined8 *)(local_138 + uVar7) = 0;
    QHash<QString,Lelan::PlayerState>::insert
              ((QHash<QString,Lelan::PlayerState> *)(this + 0x10),param_1,(PlayerState *)local_168);
    PlayerState::~PlayerState((PlayerState *)local_168);
  }
  local_1d0 = (QString *)QHash<QString,Lelan::PlayerState>::operator[]((QString *)(this + 0x10));
  QString::QString((QString *)local_168,"PlaybackStatus");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_2,(QString *)local_168);
  QString::~QString((QString *)local_168);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_188,"PlaybackStatus");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_2);
    ::QVariant::toString();
    QString::operator=(local_1d0,(QString *)local_168);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_188);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString((QString *)local_168,"Metadata");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_2,(QString *)local_168);
  QString::~QString((QString *)local_168);
  if (cVar1 != '\0') {
    local_1d8 = 0;
    ::QVariant::QVariant((QVariant *)local_48);
    QString::QString((QString *)local_168,"Metadata");
    QMap<QString,QVariant>::value(local_a8,(QVariant *)param_2);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    bVar2 = ::QVariant::canConvert<QDBusArgument>((QVariant *)local_a8);
    if (bVar2) {
      ::QVariant::value<QDBusArgument>((QVariant *)local_168);
      ::operator>>((QDBusArgument *)local_168,(QMap *)&local_1d8);
      QDBusArgument::~QDBusArgument((QDBusArgument *)local_168);
    }
    else {
      ::QVariant::toMap();
      QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)&local_1d8,(QMap *)local_168);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
    }
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_188,"xesam:title");
    QMap<QString,QVariant>::value(local_48,(QVariant *)&local_1d8);
    ::QVariant::toString();
    QString::operator=(local_1d0 + 0x18,(QString *)local_168);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_188);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_1c8,"xesam:artist");
    QMap<QString,QVariant>::value(local_48,(QVariant *)&local_1d8);
    ::QVariant::toStringList();
    QString::QString((QString *)local_188,", ");
    QListSpecialMethods<QString>::join((QString *)local_168);
    QString::operator=(local_1d0 + 0x30,(QString *)local_168);
    QString::~QString((QString *)local_168);
    QString::~QString((QString *)local_188);
    QList<QString>::~QList(local_1a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_1c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_188,"xesam:album");
    QMap<QString,QVariant>::value(local_48,(QVariant *)&local_1d8);
    ::QVariant::toString();
    QString::operator=(local_1d0 + 0x48,(QString *)local_168);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_188);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_188,"mpris:artUrl");
    QMap<QString,QVariant>::value(local_48,(QVariant *)&local_1d8);
    ::QVariant::toString();
    QString::operator=(local_1d0 + 0x60,(QString *)local_168);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_188);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant((QVariant *)local_48);
    QString::QString((QString *)local_168,"mpris:trackid");
    QMap<QString,QVariant>::value(local_88,(QVariant *)&local_1d8);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant((QVariant *)local_48);
    bVar2 = ::QVariant::canConvert<QDBusObjectPath>((QVariant *)local_88);
    if (!bVar2) {
      ::QVariant::toString();
    }
    else {
      ::QVariant::value<QDBusObjectPath>((QVariant *)local_188);
      QDBusObjectPath::path();
    }
    QString::operator=(local_1d0 + 0x78,(QString *)local_168);
    QString::~QString((QString *)local_168);
    if (bVar2) {
      QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_188);
    }
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_168,"mpris:length");
    QMap<QString,QVariant>::value(local_48,(QVariant *)&local_1d8);
    uVar4 = ::QVariant::toLongLong((bool *)local_48);
    *(undefined8 *)(local_1d0 + 0x98) = uVar4;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant(local_68);
    QString::QString((QString *)local_188,"org.mpris.MediaPlayer2.");
    cVar1 = QString::startsWith(param_1,local_188,1);
    if (cVar1 == '\0') {
      QString::QString((QString *)local_168,param_1);
    }
    else {
      QString::mid((longlong)local_168,(longlong)param_1);
    }
    QString::operator=(local_1d0 + 0xa0,(QString *)local_168);
    QString::~QString((QString *)local_168);
    QString::~QString((QString *)local_188);
    ::QVariant::~QVariant((QVariant *)local_88);
    ::QVariant::~QVariant((QVariant *)local_a8);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1d8);
  }
  QString::QString((QString *)local_168,"Position");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_2,(QString *)local_168);
  QString::~QString((QString *)local_168);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_168,"Position");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_2);
    uVar4 = ::QVariant::toLongLong((bool *)local_48);
    *(undefined8 *)(local_1d0 + 0x90) = uVar4;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_168);
    ::QVariant::~QVariant(local_68);
  }
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 != '\0') {
    QString::operator=((QString *)(this + 0x18),param_1);
    goto LAB_00237ceb;
  }
  local_168[0] = "Playing";
  cVar1 = ::operator==(local_1d0,local_168);
  if (cVar1 == '\0') goto LAB_00237ceb;
  local_188[0] = "Playing";
  QHash<QString,Lelan::PlayerState>::value((QString *)local_168);
  cVar1 = ::operator==((QString *)local_168,local_188);
  PlayerState::~PlayerState((PlayerState *)local_168);
  if (cVar1 == '\x01') {
    cVar1 = applyPlayerProps(QString_const&,QMap<QString,QVariant>const&)::
            {lambda(QString_const&)#1}::operator()
                      ((_lambda_QString_const___1_ *)local_1a8,(QString *)(this + 0x18));
    if (cVar1 != '\0') {
      cVar1 = applyPlayerProps(QString_const&,QMap<QString,QVariant>const&)::
              {lambda(QString_const&)#1}::operator()
                        ((_lambda_QString_const___1_ *)local_1a8,param_1);
      if (cVar1 != '\x01') goto LAB_00237cbe;
    }
    bVar2 = false;
  }
  else {
LAB_00237cbe:
    bVar2 = true;
  }
  if (bVar2) {
    QString::operator=((QString *)(this + 0x18),param_1);
  }
LAB_00237ceb:
  QHash<QString,Lelan::PlayerState>::value((QString *)local_168);
  local_188[0] = "Playing";
  LVar3 = (Lelan)::operator==((QString *)local_168,local_188);
  this[0x335] = LVar3;
  ::QVariant::QVariant((QVariant *)local_48,(QString *)local_168);
  QString::QString((QString *)local_188,"status");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_150);
  QString::QString((QString *)local_188,"title");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_138);
  QString::QString((QString *)local_188,"artist");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_120);
  QString::QString((QString *)local_188,"album");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_108);
  QString::QString((QString *)local_188,"artUrl");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_d0);
  QString::QString((QString *)local_188,"duration");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_d8);
  QString::QString((QString *)local_188,"position");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,local_c8);
  QString::QString((QString *)local_188,"player");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_188);
  ::QVariant::operator=(pQVar5,(QVariant *)local_48);
  QString::~QString((QString *)local_188);
  ::QVariant::~QVariant((QVariant *)local_48);
  mediaChanged(this);
  QString::QString((QString *)local_188,"Metadata");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_2,(QString *)local_188);
  QString::~QString((QString *)local_188);
  if (cVar1 != '\0') {
    appNameChanged(this);
    appIconChanged(this);
    durationChanged(this);
  }
  PlayerState::~PlayerState((PlayerState *)local_168);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00238706  Lelan::removePlayer

/* Lelan::removePlayer(QString const&) */

void __thiscall Lelan::removePlayer(Lelan *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  Lelan LVar3;
  QString *pQVar4;
  QVariant *pQVar5;
  long in_FS_OFFSET;
  undefined1 auVar6 [16];
  undefined1 local_128 [2] [16];
  undefined1 local_108 [16];
  QString local_f0 [24];
  QString local_d8 [24];
  QString local_c0 [24];
  QString local_a8 [48];
  longlong local_78;
  longlong local_70;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QHash<QString,Lelan::PlayerState>::contains
                    ((QHash<QString,Lelan::PlayerState> *)(this + 0x10),param_1);
  if (cVar2 != '\x01') goto LAB_00238f24;
  QHash<QString,Lelan::PlayerState>::remove
            ((QHash<QString,Lelan::PlayerState> *)(this + 0x10),param_1);
  cVar2 = ::operator==((QString *)(this + 0x18),param_1);
  if (cVar2 != '\0') {
    QString::clear((QString *)(this + 0x18));
    local_128[0] = QHash<QString,Lelan::PlayerState>::constBegin
                             ((QHash<QString,Lelan::PlayerState> *)(this + 0x10));
    while( true ) {
      auVar6 = QHash<QString,Lelan::PlayerState>::constEnd();
      local_108 = auVar6;
      cVar2 = QHash<QString,Lelan::PlayerState>::const_iterator::operator!=
                        ((const_iterator *)local_128,(const_iterator *)local_108);
      if (cVar2 == '\0') break;
      QLatin1String::QLatin1String((QLatin1String *)local_108,"Playing");
      pQVar4 = (QString *)
               QHash<QString,Lelan::PlayerState>::const_iterator::value((const_iterator *)local_128)
      ;
      cVar2 = ::operator==(pQVar4,(QLatin1String *)local_108);
      if (cVar2 != '\0') {
        pQVar4 = (QString *)
                 QHash<QString,Lelan::PlayerState>::const_iterator::key((const_iterator *)local_128)
        ;
        QString::operator=((QString *)(this + 0x18),pQVar4);
        break;
      }
      QHash<QString,Lelan::PlayerState>::const_iterator::operator++((const_iterator *)local_128);
    }
    cVar2 = QString::isEmpty((QString *)(this + 0x18));
    if (cVar2 == '\0') {
LAB_002388c5:
      bVar1 = false;
    }
    else {
      cVar2 = QHash<QString,Lelan::PlayerState>::isEmpty
                        ((QHash<QString,Lelan::PlayerState> *)(this + 0x10));
      if (cVar2 == '\x01') goto LAB_002388c5;
      bVar1 = true;
    }
    if (bVar1) {
      auVar6 = QHash<QString,Lelan::PlayerState>::constBegin
                         ((QHash<QString,Lelan::PlayerState> *)(this + 0x10));
      local_108 = auVar6;
      pQVar4 = (QString *)
               QHash<QString,Lelan::PlayerState>::const_iterator::key((const_iterator *)local_108);
      QString::operator=((QString *)(this + 0x18),pQVar4);
    }
  }
  QHash<QString,Lelan::PlayerState>::value((QString *)local_108);
  QLatin1String::QLatin1String((QLatin1String *)local_128,"Playing");
  LVar3 = (Lelan)::operator==((QString *)local_108,(QLatin1String *)local_128);
  this[0x335] = LVar3;
  ::QVariant::QVariant(local_48,(QString *)local_108);
  QString::QString((QString *)local_128,"status");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_f0);
  QString::QString((QString *)local_128,"title");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_d8);
  QString::QString((QString *)local_128,"artist");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_c0);
  QString::QString((QString *)local_128,"album");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_a8);
  QString::QString((QString *)local_128,"artUrl");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_70);
  QString::QString((QString *)local_128,"duration");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_78);
  QString::QString((QString *)local_128,"position");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString((QString *)local_128,"player");
  pQVar5 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)(this + 0x98),(QString *)local_128);
  ::QVariant::operator=(pQVar5,local_48);
  QString::~QString((QString *)local_128);
  ::QVariant::~QVariant(local_48);
  mediaChanged(this);
  appNameChanged(this);
  appIconChanged(this);
  durationChanged(this);
  PlayerState::~PlayerState((PlayerState *)local_108);
LAB_00238f24:
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00238f3e  Lelan::onPropertiesChanged

/* Lelan::onPropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString> const&)
    */

void Lelan::onPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  QList<QString> *local_48;
  QString *local_40;
  char *local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_38[0] = "org.mpris.MediaPlayer2.Player";
  cVar1 = ::operator!=((QString *)param_2,local_38);
  if (cVar1 == '\0') {
    QHash<QString,Lelan::PlayerState>::keys();
    local_48 = (QList<QString> *)local_38;
    local_58 = QList<QString>::begin(local_48);
    local_50 = QList<QString>::end(local_48);
    while( true ) {
      cVar1 = QList<QString>::iterator::operator!=((iterator *)&local_58,local_50);
      if (cVar1 == '\0') break;
      local_40 = (QString *)QList<QString>::iterator::operator*((iterator *)&local_58);
      fetchPlayer((Lelan *)param_1,local_40);
      QList<QString>::iterator::operator++((iterator *)&local_58);
    }
    QList<QString>::~QList((QList<QString> *)local_38);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023906a  Lelan::onMprisSeeked

/* Lelan::onMprisSeeked(long long) */

void __thiscall Lelan::onMprisSeeked(Lelan *this,longlong param_1)

{
  char cVar1;
  long lVar2;
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    lVar2 = QHash<QString,Lelan::PlayerState>::operator[]((QString *)(this + 0x10));
    *(longlong *)(lVar2 + 0x90) = param_1;
    ::QVariant::QVariant(local_48,param_1);
    QString::QString(local_68,"position");
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x98),local_68);
    ::QVariant::operator=(this_00,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
    mediaPositionChanged(this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023919e  Lelan::refreshMediaPosition()::{lambda()#1}::operator()

/* Lelan::refreshMediaPosition()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshMediaPosition()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  longlong lVar2;
  char cVar3;
  long lVar4;
  QVariant *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_78 [8];
  longlong local_70;
  QString local_68 [32];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_78,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 != '\0') {
    cVar3 = QHash<QString,Lelan::PlayerState>::contains
                      ((QHash<QString,Lelan::PlayerState> *)(*(long *)this + 0x10),
                       (QString *)(this + 8));
    if (cVar3 != '\0') {
      bVar1 = true;
      goto LAB_00239213;
    }
  }
  bVar1 = false;
LAB_00239213:
  if (bVar1) {
    QDBusPendingReply<QVariant>::value(local_48);
    local_70 = ::QVariant::toLongLong((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    lVar2 = local_70;
    lVar4 = QHash<QString,Lelan::PlayerState>::operator[]((QString *)(*(long *)this + 0x10));
    *(longlong *)(lVar4 + 0x90) = lVar2;
    cVar3 = ::operator==((QString *)(*(long *)this + 0x18),(QString *)(this + 8));
    if (cVar3 != '\0') {
      ::QVariant::QVariant((QVariant *)local_48,local_70);
      lVar4 = *(long *)this;
      QString::QString(local_68,"position");
      this_00 = (QVariant *)
                QMap<QString,QVariant>::operator[]
                          ((QMap<QString,QVariant> *)(lVar4 + 0x98),local_68);
      ::QVariant::operator=(this_00,(QVariant *)local_48);
      QString::~QString(local_68);
      ::QVariant::~QVariant((QVariant *)local_48);
      mediaPositionChanged(*(Lelan **)this);
    }
  }
  QObject::deleteLater();
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_78);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002393b4  Lelan::refreshMediaPosition()::{lambda()#1}::~refreshMediaPosition

/* ~refreshMediaPosition() */

void __thiscall
Lelan::refreshMediaPosition()::{lambda()#1}::~refreshMediaPosition(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 8));
  return;
}



// ==== 002393d4  Lelan::refreshMediaPosition

/* WARNING: Removing unreachable block (ram,0x0023961f) */
/* WARNING: Removing unreachable block (ram,0x002396d6) */
/* Lelan::refreshMediaPosition() */

void __thiscall Lelan::refreshMediaPosition(Lelan *this)

{
  char cVar1;
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_110 [8];
  QString local_108 [8];
  QDBusPendingCallWatcher *local_100;
  QString local_f8 [32];
  QString local_d8 [32];
  Lelan *local_b8;
  QString aQStack_b0 [24];
  QDBusPendingCallWatcher *local_98;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QDBusConnection::sessionBus();
    QString::QString((QString *)&local_b8,"Get");
    QString::QString(local_d8,FDPROPS);
    QString::QString(local_f8,"/org/mpris/MediaPlayer2");
    QDBusMessage::createMethodCall(local_108,(QString *)(this + 0x18),local_f8,local_d8);
    QString::~QString(local_f8);
    QString::~QString(local_d8);
    QString::~QString((QString *)&local_b8);
    QString::QString(local_d8,"org.mpris.MediaPlayer2.Player");
    ::QVariant::QVariant(local_88,local_d8);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_108,local_88);
    QString::QString((QString *)&local_b8,"Position");
    ::QVariant::QVariant(local_68,(QString *)&local_b8);
    QDBusMessage::operator<<(this_00,local_68);
    ::QVariant::~QVariant(local_68);
    QString::~QString((QString *)&local_b8);
    ::QVariant::~QVariant(local_88);
    QString::~QString(local_d8);
    QString::QString(local_d8,(QString *)(this + 0x18));
    this_01 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_b8,(int)local_110);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_01,(QDBusPendingCall *)&local_b8,(QObject *)this);
    local_100 = this_01;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_b8);
    local_b8 = this;
    QString::QString(aQStack_b0,local_d8);
    local_98 = local_100;
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshMediaPosition()::_lambda()_1_>
              (local_f8,local_100,QDBusPendingCallWatcher::finished,0,this,&local_b8,0);
    QMetaObject::Connection::~Connection((Connection *)local_f8);
    refreshMediaPosition()::{lambda()#1}::~refreshMediaPosition((_lambda___1_ *)&local_b8);
    QString::~QString(local_d8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_108);
    QDBusConnection::~QDBusConnection(local_110);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00239872  Lelan::refreshActiveMediaPid()::{lambda()#1}::operator()

/* Lelan::refreshActiveMediaPid()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshActiveMediaPid()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  long in_FS_OFFSET;
  QDBusPendingReply<unsigned_int> local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<unsigned_int>::QDBusPendingReply
            (local_28,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 != '\0') {
    cVar3 = ::operator==((QString *)(*(long *)this + 0x18),(QString *)(this + 8));
    if (cVar3 != '\0') {
      bVar2 = true;
      goto LAB_002398e7;
    }
  }
  bVar2 = false;
LAB_002398e7:
  if (bVar2) {
    lVar1 = *(long *)this;
    uVar4 = QDBusPendingReply<unsigned_int>::value();
    *(undefined4 *)(lVar1 + 0x30) = uVar4;
  }
  QObject::deleteLater();
  QDBusPendingReply<unsigned_int>::~QDBusPendingReply(local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00239968  Lelan::refreshActiveMediaPid()::{lambda()#1}::~refreshActiveMediaPid

/* ~refreshActiveMediaPid() */

void __thiscall
Lelan::refreshActiveMediaPid()::{lambda()#1}::~refreshActiveMediaPid(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 8));
  return;
}



// ==== 00239988  Lelan::refreshActiveMediaPid

/* WARNING: Removing unreachable block (ram,0x00239c78) */
/* WARNING: Removing unreachable block (ram,0x00239d2c) */
/* Lelan::refreshActiveMediaPid() */

void __thiscall Lelan::refreshActiveMediaPid(Lelan *this)

{
  char cVar1;
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_1b0 [8];
  QString local_1a8 [8];
  QDBusPendingCallWatcher *local_1a0;
  undefined *local_198;
  wchar16 *local_190;
  undefined *local_188;
  undefined *local_180;
  QArrayDataPointer<char16_t> local_178 [32];
  QString local_158 [32];
  QArrayDataPointer<char16_t> local_138 [32];
  QString local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  Lelan *local_98;
  QString aQStack_90 [24];
  QDBusPendingCallWatcher *local_78;
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QDBusConnection::sessionBus();
    local_180 = &DAT_002abd90;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_b8,(QTypedArrayData *)0x0,L"GetConnectionUnixProcessID",0x1a);
    QString::QString((QString *)&local_98,(QArrayDataPointer *)local_b8);
    local_188 = &DAT_002abdc8;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_f8,(QTypedArrayData *)0x0,L"org.freedesktop.DBus",0x14);
    QString::QString(local_d8,(QArrayDataPointer *)local_f8);
    local_190 = L"/org/freedesktop/DBus";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_138,(QTypedArrayData *)0x0,L"/org/freedesktop/DBus",0x15);
    QString::QString(local_118,(QArrayDataPointer *)local_138);
    local_198 = &DAT_002abdc8;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_178,(QTypedArrayData *)0x0,L"org.freedesktop.DBus",0x14);
    QString::QString(local_158,(QArrayDataPointer *)local_178);
    QDBusMessage::createMethodCall(local_1a8,local_158,local_118,local_d8);
    QString::~QString(local_158);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_178);
    QString::~QString(local_118);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_138);
    QString::~QString(local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
    QString::~QString((QString *)&local_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x18));
    QDBusMessage::operator<<((QDBusMessage *)local_1a8,local_68);
    ::QVariant::~QVariant(local_68);
    QString::QString((QString *)local_b8,(QString *)(this + 0x18));
    this_00 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_98,(int)local_1b0);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_00,(QDBusPendingCall *)&local_98,(QObject *)this);
    local_1a0 = this_00;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_98);
    local_98 = this;
    QString::QString(aQStack_90,(QString *)local_b8);
    local_78 = local_1a0;
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshActiveMediaPid()::_lambda()_1_>
              (local_d8,local_1a0,QDBusPendingCallWatcher::finished,0,this,&local_98,0);
    QMetaObject::Connection::~Connection((Connection *)local_d8);
    refreshActiveMediaPid()::{lambda()#1}::~refreshActiveMediaPid((_lambda___1_ *)&local_98);
    QString::~QString((QString *)local_b8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1a8);
    QDBusConnection::~QDBusConnection(local_1b0);
  }
  else {
    *(undefined4 *)(this + 0x30) = 0;
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00239ed0  Lelan::mediaPlayPause

/* Lelan::mediaPlayPause() */

void __thiscall Lelan::mediaPlayPause(Lelan *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_90 [8];
  QString local_88 [8];
  QDBusMessage local_80 [8];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QDBusConnection::sessionBus();
    QString::QString(local_38,"PlayPause");
    QString::QString(local_58,"org.mpris.MediaPlayer2.Player");
    QString::QString(local_78,"/org/mpris/MediaPlayer2");
    QDBusMessage::createMethodCall(local_88,(QString *)(this + 0x18),local_78,local_58);
    QDBusConnection::asyncCall(local_80,(int)local_90);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_80);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_88);
    QString::~QString(local_78);
    QString::~QString(local_58);
    QString::~QString(local_38);
    QDBusConnection::~QDBusConnection(local_90);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023a07e  Lelan::mediaNext

/* Lelan::mediaNext() */

void __thiscall Lelan::mediaNext(Lelan *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_90 [8];
  QString local_88 [8];
  QDBusMessage local_80 [8];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QDBusConnection::sessionBus();
    QString::QString(local_38,"Next");
    QString::QString(local_58,"org.mpris.MediaPlayer2.Player");
    QString::QString(local_78,"/org/mpris/MediaPlayer2");
    QDBusMessage::createMethodCall(local_88,(QString *)(this + 0x18),local_78,local_58);
    QDBusConnection::asyncCall(local_80,(int)local_90);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_80);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_88);
    QString::~QString(local_78);
    QString::~QString(local_58);
    QString::~QString(local_38);
    QDBusConnection::~QDBusConnection(local_90);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023a22c  Lelan::mediaPrevious

/* Lelan::mediaPrevious() */

void __thiscall Lelan::mediaPrevious(Lelan *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_90 [8];
  QString local_88 [8];
  QDBusMessage local_80 [8];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QDBusConnection::sessionBus();
    QString::QString(local_38,"Previous");
    QString::QString(local_58,"org.mpris.MediaPlayer2.Player");
    QString::QString(local_78,"/org/mpris/MediaPlayer2");
    QDBusMessage::createMethodCall(local_88,(QString *)(this + 0x18),local_78,local_58);
    QDBusConnection::asyncCall(local_80,(int)local_90);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_80);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_88);
    QString::~QString(local_78);
    QString::~QString(local_58);
    QString::~QString(local_38);
    QDBusConnection::~QDBusConnection(local_90);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023a3da  Lelan::mediaSeek

/* Lelan::mediaSeek(long long) */

void __thiscall Lelan::mediaSeek(Lelan *this,longlong param_1)

{
  char cVar1;
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  QString local_190 [8];
  QString local_188 [32];
  QString local_168 [32];
  QString local_148 [32];
  QString local_128 [120];
  QString local_b0 [72];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x18));
  if (cVar1 == '\0') {
    QHash<QString,Lelan::PlayerState>::value(local_128);
    QString::QString(local_188,local_b0);
    PlayerState::~PlayerState((PlayerState *)local_128);
    cVar1 = QString::isEmpty(local_188);
    if (cVar1 == '\0') {
      QString::QString(local_128,"SetPosition");
      QString::QString(local_148,"org.mpris.MediaPlayer2.Player");
      QString::QString(local_168,"/org/mpris/MediaPlayer2");
      QDBusMessage::createMethodCall(local_190,(QString *)(this + 0x18),local_168,local_148);
      QString::~QString(local_168);
      QString::~QString(local_148);
      QString::~QString(local_128);
      QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_128,local_188);
      ::QVariant::fromValue<QDBusObjectPath,true>(local_68,(QDBusObjectPath *)local_128);
      this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_190,local_68);
      ::QVariant::QVariant(local_48,param_1);
      QDBusMessage::operator<<(this_00,local_48);
      ::QVariant::~QVariant(local_48);
      ::QVariant::~QVariant(local_68);
      QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_128);
      QDBusConnection::sessionBus();
      QDBusConnection::asyncCall((QDBusMessage *)local_128,(int)local_148);
      QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_128);
      QDBusConnection::~QDBusConnection((QDBusConnection *)local_148);
      QDBusMessage::~QDBusMessage((QDBusMessage *)local_190);
    }
    QString::~QString(local_188);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0023a728  Lelan::subscribeTrayOwner

/* WARNING: Removing unreachable block (ram,0x0023a794) */
/* Lelan::subscribeTrayOwner() */

void __thiscall Lelan::subscribeTrayOwner(Lelan *this)

{
  SniWatcher *this_00;
  long in_FS_OFFSET;
  Connection local_60 [8];
  code *local_58;
  undefined8 local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x428) == 0) {
    this_00 = operator_new(0x48);
    SniWatcher::SniWatcher(this_00,(QObject *)this);
    *(SniWatcher **)(this + 0x428) = this_00;
    local_58 = rebuildTray;
    local_50 = 0;
    QObject::connect<void(SniWatcher::*)(),void(Lelan::*)()>
              (local_60,*(undefined8 *)(this + 0x428),SniWatcher::itemsChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
  }
  rebuildTray(this);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0023a870  Lelan::rebuildTray()::{lambda()#1}::operator()

/* Lelan::rebuildTray()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::rebuildTray()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  QVariant *pQVar2;
  QMap *pQVar3;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  QDBusPendingReply<QMap<QString,QVariant>> local_d0 [8];
  QDBusPendingReply<QMap<QString,QVariant>> local_c8 [8];
  undefined8 local_c0;
  undefined1 local_b8 [16];
  undefined1 local_a8 [2] [16];
  QString local_88 [16];
  undefined8 local_78;
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_d0,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 != '\0') {
    QDBusPendingReply<QMap<QString,QVariant>>::value(local_c8);
    local_c0 = 0;
    ::QVariant::QVariant(local_48,(QString *)(this + 8));
    QString::QString(local_88,"service");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Id");
    QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)local_c8);
    QString::QString((QString *)local_a8,"id");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_c0,(QString *)local_a8);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Title");
    QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)local_c8);
    QString::QString((QString *)local_a8,"title");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_c0,(QString *)local_a8);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Status");
    QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)local_c8);
    QString::QString((QString *)local_a8,"status");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_c0,(QString *)local_a8);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"IconName");
    QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)local_c8);
    QString::QString((QString *)local_a8,"iconName");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_c0,(QString *)local_a8);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Category");
    QMap<QString,QVariant>::value((QString *)local_48,(QVariant *)local_c8);
    QString::QString((QString *)local_a8,"category");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_c0,(QString *)local_a8);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    QHash<QString,QMap<QString,QVariant>>::insert
              ((QHash<QString,QMap<QString,QVariant>> *)(*(long *)this + 0x430),
               (QString *)(this + 8),(QMap *)&local_c0);
    local_88[0] = (QString)0x0;
    local_88[1] = (QString)0x0;
    local_88[2] = (QString)0x0;
    local_88[3] = (QString)0x0;
    local_88[4] = (QString)0x0;
    local_88[5] = (QString)0x0;
    local_88[6] = (QString)0x0;
    local_88[7] = (QString)0x0;
    local_88[8] = (QString)0x0;
    local_88[9] = (QString)0x0;
    local_88[10] = (QString)0x0;
    local_88[0xb] = (QString)0x0;
    local_88[0xc] = (QString)0x0;
    local_88[0xd] = (QString)0x0;
    local_88[0xe] = (QString)0x0;
    local_88[0xf] = (QString)0x0;
    local_78 = 0;
    local_b8 = QHash<QString,QMap<QString,QVariant>>::constBegin
                         ((QHash<QString,QMap<QString,QVariant>> *)(*(long *)this + 0x430));
    while( true ) {
      auVar4 = QHash<QString,QMap<QString,QVariant>>::constEnd();
      local_a8[0] = auVar4;
      cVar1 = QHash<QString,QMap<QString,QVariant>>::const_iterator::operator!=
                        ((const_iterator *)local_b8,(const_iterator *)local_a8);
      if (cVar1 == '\0') break;
      pQVar3 = (QMap *)QHash<QString,QMap<QString,QVariant>>::const_iterator::value
                                 ((const_iterator *)local_b8);
      ::QVariant::QVariant(local_48,pQVar3);
      QList<QVariant>::operator<<((QList<QVariant> *)local_88,local_48);
      ::QVariant::~QVariant(local_48);
      QHash<QString,QMap<QString,QVariant>>::const_iterator::operator++((const_iterator *)local_b8);
    }
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0x230),(QList *)local_88);
    trayChanged(*(Lelan **)this);
    QList<QVariant>::~QList((QList<QVariant> *)local_88);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
  }
  QObject::deleteLater();
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_d0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0023b084  Lelan::rebuildTray()::{lambda()#1}::~rebuildTray

/* ~rebuildTray() */

void __thiscall Lelan::rebuildTray()::{lambda()#1}::~rebuildTray(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 8));
  return;
}



// ==== 0023b0a4  Lelan::rebuildTray

/* WARNING: Removing unreachable block (ram,0x0023b94e) */
/* WARNING: Removing unreachable block (ram,0x0023ba02) */
/* Lelan::rebuildTray() */

void __thiscall Lelan::rebuildTray(Lelan *this)

{
  char cVar1;
  int iVar2;
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QString local_190 [8];
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  QList<QString> *local_170;
  QList<QString> *local_168;
  QString *local_160;
  QDBusPendingCallWatcher *local_158;
  QString *local_150;
  wchar16 *local_148;
  wchar16 *local_140;
  QListSpecialMethods<QString> local_138 [32];
  QList<QString> local_118 [32];
  QString local_f8 [32];
  QString local_d8 [32];
  QLatin1Char local_b8 [32];
  Lelan *local_98;
  QString aQStack_90 [24];
  QDBusPendingCallWatcher *local_78;
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x428) != 0) {
    SniWatcher::items();
    QHash<QString,QMap<QString,QVariant>>::keys();
    QDBusConnection::sessionBus();
    local_170 = local_118;
    local_180 = QList<QString>::begin(local_170);
    local_178 = QList<QString>::end(local_170);
    while (cVar1 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_180,local_178), cVar1 != '\0') {
      local_150 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)&local_180)
      ;
      cVar1 = QListSpecialMethods<QString>::contains(local_138,local_150,1);
      if (cVar1 == '\0') {
        QHash<QString,QMap<QString,QVariant>>::remove
                  ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x430),local_150);
        cVar1 = QSet<QString>::remove((QSet<QString> *)(this + 0x438),local_150);
        if (cVar1 != '\0') {
          QString::QString(local_f8,local_150);
          local_148 = L"/StatusNotifierItem";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)&local_98,(QTypedArrayData *)0x0,
                     L"/StatusNotifierItem",0x13);
          QString::QString(local_d8,(QArrayDataPointer *)&local_98);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_98);
          QLatin1Char::QLatin1Char(local_b8,'/');
          QChar::QChar<QLatin1Char,true>((QChar *)&local_98,local_b8[0]);
          iVar2 = QString::indexOf(local_150,(ulong)local_98 & 0xffff,0,1);
          if (0 < iVar2) {
            QString::left((longlong)&local_98);
            QString::operator=(local_f8,(QString *)&local_98);
            QString::~QString((QString *)&local_98);
            QString::mid((longlong)&local_98,(longlong)local_150);
            QString::operator=(local_d8,(QString *)&local_98);
            QString::~QString((QString *)&local_98);
          }
          QString::QString((QString *)&local_98,"NewIcon");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::disconnect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewStatus");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::disconnect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewTitle");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::disconnect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewToolTip");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::disconnect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::~QString(local_d8);
          QString::~QString(local_f8);
        }
      }
      QList<QString>::const_iterator::operator++((const_iterator *)&local_180);
    }
    cVar1 = QList<QString>::isEmpty((QList<QString> *)local_138);
    if (cVar1 == '\0') {
      local_168 = (QList<QString> *)local_138;
      local_188 = QList<QString>::begin(local_168);
      local_180 = QList<QString>::end(local_168);
      while (cVar1 = QList<QString>::const_iterator::operator!=
                               ((const_iterator *)&local_188,local_180), cVar1 != '\0') {
        local_160 = (QString *)
                    QList<QString>::const_iterator::operator*((const_iterator *)&local_188);
        QString::QString(local_f8,local_160);
        local_140 = L"/StatusNotifierItem";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)&local_98,(QTypedArrayData *)0x0,
                   L"/StatusNotifierItem",0x13);
        QString::QString(local_d8,(QArrayDataPointer *)&local_98);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_98);
        QLatin1Char::QLatin1Char(local_b8,'/');
        QChar::QChar<QLatin1Char,true>((QChar *)&local_98,local_b8[0]);
        iVar2 = QString::indexOf(local_160,(ulong)local_98 & 0xffff,0,1);
        if (0 < iVar2) {
          QString::left((longlong)&local_98);
          QString::operator=(local_f8,(QString *)&local_98);
          QString::~QString((QString *)&local_98);
          QString::mid((longlong)&local_98,(longlong)local_160);
          QString::operator=(local_d8,(QString *)&local_98);
          QString::~QString((QString *)&local_98);
        }
        QString::QString((QString *)&local_98,"GetAll");
        QString::QString((QString *)local_b8,FDPROPS);
        QDBusMessage::createMethodCall((QString *)&local_178,local_f8,local_d8,(QString *)local_b8);
        QString::~QString((QString *)local_b8);
        QString::~QString((QString *)&local_98);
        QString::QString((QString *)&local_98,"org.kde.StatusNotifierItem");
        ::QVariant::QVariant(local_68,(QString *)&local_98);
        QDBusMessage::operator<<((QDBusMessage *)&local_178,local_68);
        ::QVariant::~QVariant(local_68);
        QString::~QString((QString *)&local_98);
        this_00 = operator_new(0x18);
        QDBusConnection::asyncCall((QDBusMessage *)&local_98,(int)local_190);
        QDBusPendingCallWatcher::QDBusPendingCallWatcher
                  (this_00,(QDBusPendingCall *)&local_98,(QObject *)this);
        local_158 = this_00;
        QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_98);
        local_98 = this;
        QString::QString(aQStack_90,local_160);
        local_78 = local_158;
        QObject::
        connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::rebuildTray()::_lambda()_1_>
                  (local_b8,local_158,QDBusPendingCallWatcher::finished,0,this,&local_98,0);
        QMetaObject::Connection::~Connection((Connection *)local_b8);
        rebuildTray()::{lambda()#1}::~rebuildTray((_lambda___1_ *)&local_98);
        cVar1 = QSet<QString>::contains((QSet<QString> *)(this + 0x438),local_160);
        if (cVar1 != '\x01') {
          QSet<QString>::insert((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewIcon");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::connect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewStatus");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::connect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewTitle");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::connect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
          QString::QString((QString *)&local_98,"NewToolTip");
          QString::QString((QString *)local_b8,"org.kde.StatusNotifierItem");
          QDBusConnection::connect
                    (local_190,local_f8,local_d8,(QString *)local_b8,(QObject *)&local_98,
                     (char *)this);
          QString::~QString((QString *)local_b8);
          QString::~QString((QString *)&local_98);
        }
        QDBusMessage::~QDBusMessage((QDBusMessage *)&local_178);
        QString::~QString(local_d8);
        QString::~QString(local_f8);
        QList<QString>::const_iterator::operator++((const_iterator *)&local_188);
      }
    }
    else {
      QList<QVariant>::clear((QList<QVariant> *)(this + 0x230));
      trayChanged(this);
    }
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_190);
    QList<QString>::~QList(local_118);
    QList<QString>::~QList((QList<QString> *)local_138);
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0023c03e  Lelan::onTrayItemChanged

/* Lelan::onTrayItemChanged() */

void __thiscall Lelan::onTrayItemChanged(Lelan *this)

{
  rebuildTray(this);
  return;
}



// ==== 0023c642  Lelan::subscribeToPlayers()::{lambda()#1}::subscribeToPlayers

/* subscribeToPlayers({lambda()#1}&&) */

void __thiscall
Lelan::subscribeToPlayers()::{lambda()#1}::subscribeToPlayers
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QDBusConnection::QDBusConnection((QDBusConnection *)(this + 8),(QDBusConnection *)(param_1 + 8));
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  return;
}



// ==== 0023c6f2  Lelan::fetchPlayer(QString_const&)::{lambda()#1}::QString

/* QString({lambda()#1}&&) */

void __thiscall
Lelan::fetchPlayer(QString_const&)::{lambda()#1}::QString(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  ::QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0023c7a2  Lelan::refreshMediaPosition()::{lambda()#1}::refreshMediaPosition

/* refreshMediaPosition({lambda()#1}&&) */

void __thiscall
Lelan::refreshMediaPosition()::{lambda()#1}::refreshMediaPosition
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0023c852  Lelan::refreshActiveMediaPid()::{lambda()#1}::refreshActiveMediaPid

/* refreshActiveMediaPid({lambda()#1}&&) */

void __thiscall
Lelan::refreshActiveMediaPid()::{lambda()#1}::refreshActiveMediaPid
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0023c902  Lelan::rebuildTray()::{lambda()#1}::rebuildTray

/* rebuildTray({lambda()#1}&&) */

void __thiscall
Lelan::rebuildTray()::{lambda()#1}::rebuildTray(_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0023d1b1  Lelan::_GLOBAL__sub_I_subscribeToAudio

/* Lelan::subscribeToAudio() */

void Lelan::_GLOBAL__sub_I_subscribeToAudio(void)

{
  __static_initialization_and_destruction_0();
  return;
}



// ==== 0023f360  Lelan::PlayerState::PlayerState

/* Lelan::PlayerState::PlayerState(Lelan::PlayerState&&) */

void __thiscall Lelan::PlayerState::PlayerState(PlayerState *this,PlayerState *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  QString::QString((QString *)(this + 0x60),(QString *)(param_1 + 0x60));
  QString::QString((QString *)(this + 0x78),(QString *)(param_1 + 0x78));
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(param_1 + 0x90);
  *(undefined8 *)(this + 0x98) = *(undefined8 *)(param_1 + 0x98);
  QString::QString((QString *)(this + 0xa0),(QString *)(param_1 + 0xa0));
  return;
}



// ==== 002415ec  Lelan::PlayerState::operator=

/* Lelan::PlayerState::TEMPNAMEPLACEHOLDERVALUE(Lelan::PlayerState&&) */

PlayerState * __thiscall Lelan::PlayerState::operator=(PlayerState *this,PlayerState *param_1)

{
  QString::operator=((QString *)this,(QString *)param_1);
  QString::operator=((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::operator=((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::operator=((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  QString::operator=((QString *)(this + 0x60),(QString *)(param_1 + 0x60));
  QString::operator=((QString *)(this + 0x78),(QString *)(param_1 + 0x78));
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(param_1 + 0x90);
  *(undefined8 *)(this + 0x98) = *(undefined8 *)(param_1 + 0x98);
  QString::operator=((QString *)(this + 0xa0),(QString *)(param_1 + 0xa0));
  return this;
}



// ==== 00242c06  Lelan::subscribeToUPower()::{lambda()#1}::operator()

/* Lelan::subscribeToUPower()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToUPower()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  int iVar3;
  QVariant *pQVar4;
  QDebug *pQVar5;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_158 [8];
  QDebug local_150 [8];
  QString local_148 [32];
  QString local_128 [32];
  QDBusPendingReply<QMap<QString,QVariant>> local_108 [32];
  QString local_e8 [64];
  QString local_a8 [64];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_158,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\0') {
    QMessageLogger::QMessageLogger((QMessageLogger *)local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar5 = (QDebug *)QDebug::operator<<(local_150,"[lelan] UPower GetAll failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar5 = (QDebug *)QDebug::operator<<(pQVar5,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar5,local_128);
    QString::~QString(local_128);
    QDBusError::~QDBusError((QDBusError *)local_a8);
    QString::~QString(local_148);
    QDBusError::~QDBusError((QDBusError *)local_e8);
    QDebug::~QDebug(local_150);
  }
  else {
    QDBusPendingReply<QMap<QString,QVariant>>::value(local_108);
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"Percentage");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    lVar1 = *(long *)this;
    QString::QString(local_e8,"percentage");
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0x88),local_e8);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"State");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    lVar1 = *(long *)this;
    QString::QString(local_e8,"state");
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0x88),local_e8);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"TimeToEmpty");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    lVar1 = *(long *)this;
    QString::QString(local_e8,"timeToEmpty");
    pQVar4 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0x88),local_e8);
    ::QVariant::operator=(pQVar4,(QVariant *)local_48);
    QString::~QString(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"State");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    iVar3 = ::QVariant::toUInt((bool *)local_48);
    *(bool *)(*(long *)this + 0x33a) = iVar3 == 2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    batteryChanged(*(Lelan **)this);
    powerChanged(*(Lelan **)this);
    recomputeAnimLevel(*(Lelan **)this);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_108);
  }
  QObject::deleteLater();
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_158);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002432de  Lelan::subscribeToUPower

/* WARNING: Removing unreachable block (ram,0x00243478) */
/* Lelan::subscribeToUPower() */

void __thiscall Lelan::subscribeToUPower(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QString local_120 [8];
  QString local_118 [8];
  QDBusPendingCallWatcher *local_110;
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  Lelan *local_88;
  QDBusPendingCallWatcher *local_80;
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_108,"org.freedesktop.UPower");
  QString::QString(local_e8,"/org/freedesktop/UPower/devices/DisplayDevice");
  QString::QString(local_c8,"org.freedesktop.UPower.Device");
  QString::QString((QString *)&local_88,"GetAll");
  QString::QString(local_a8,FDPROPS);
  QDBusMessage::createMethodCall(local_118,local_108,local_e8,local_a8);
  QString::~QString(local_a8);
  QString::~QString((QString *)&local_88);
  ::QVariant::QVariant(local_68,local_c8);
  QDBusMessage::operator<<((QDBusMessage *)local_118,local_68);
  ::QVariant::~QVariant(local_68);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_88,(int)local_120);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_88,(QObject *)this);
  local_110 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_88);
  local_80 = local_110;
  local_88 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToUPower()::_lambda()_1_>
            (local_a8,local_110,QDBusPendingCallWatcher::finished,0,this,&local_88,0);
  QMetaObject::Connection::~Connection((Connection *)local_a8);
  QString::QString((QString *)&local_88,"PropertiesChanged");
  QString::QString(local_a8,FDPROPS);
  QDBusConnection::connect(local_120,local_108,local_e8,local_a8,(QObject *)&local_88,(char *)this);
  QString::~QString(local_a8);
  QString::~QString((QString *)&local_88);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_118);
  QString::~QString(local_c8);
  QString::~QString(local_e8);
  QString::~QString(local_108);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_120);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002436fc  Lelan::subscribeToPortalSettings()::{lambda()#1}::operator()

/* Lelan::subscribeToPortalSettings()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToPortalSettings()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  Lelan *this_00;
  char cVar1;
  QDebug *pQVar2;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusVariant> local_158 [8];
  QDebug local_150 [8];
  QString local_148 [32];
  QString local_128 [32];
  QMessageLogger local_108 [32];
  QDBusError local_e8 [64];
  QDBusError local_a8 [64];
  QDBusPendingReply<QDBusVariant> local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusVariant>::QDBusPendingReply
            (local_158,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\0') {
    QMessageLogger::QMessageLogger(local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar2 = (QDebug *)QDebug::operator<<(local_150,"[lelan] portal ReadOne failed for");
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,(QString *)(this + 8));
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,":");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar2,local_128);
    QString::~QString(local_128);
    QDBusError::~QDBusError(local_a8);
    QString::~QString(local_148);
    QDBusError::~QDBusError(local_e8);
    QDebug::~QDebug(local_150);
  }
  else {
    this_00 = *(Lelan **)this;
    QDBusPendingReply<QDBusVariant>::value(local_68);
    QDBusVariant::variant();
    applyPortalAppearance(this_00,(QString *)(this + 8),local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant((QDBusVariant *)local_68);
  }
  QObject::deleteLater();
  QDBusPendingReply<QDBusVariant>::~QDBusPendingReply(local_158);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00243a14  Lelan::subscribeToPortalSettings()::{lambda()#1}::~subscribeToPortalSettings

/* ~subscribeToPortalSettings() */

void __thiscall
Lelan::subscribeToPortalSettings()::{lambda()#1}::~subscribeToPortalSettings(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 8));
  return;
}



// ==== 00243a34  Lelan::subscribeToPortalSettings

/* WARNING: Removing unreachable block (ram,0x00243d48) */
/* WARNING: Removing unreachable block (ram,0x00243dff) */
/* Lelan::subscribeToPortalSettings() */

void __thiscall Lelan::subscribeToPortalSettings(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  QString *this_02;
  long in_FS_OFFSET;
  QString local_1c0 [8];
  QString local_1b8 [8];
  QString *local_1b0;
  initializer_list<QString> *local_1a8;
  QString *local_1a0;
  QString *local_198;
  QDBusPendingCallWatcher *local_190;
  wchar16 *local_188;
  wchar16 *local_180;
  QString *local_178;
  undefined8 local_170;
  QString local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  Lelan *local_e8;
  QString aQStack_e0 [24];
  QDBusPendingCallWatcher *local_c8;
  QVariant local_b8 [32];
  QVariant local_98 [32];
  QString local_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  QString::QString(local_168,"org.freedesktop.portal.Desktop");
  QString::QString(local_148,"/org/freedesktop/portal/desktop");
  QString::QString(local_128,"org.freedesktop.portal.Settings");
  local_178 = (QString *)0x0;
  local_170 = 2;
  local_180 = L"color-scheme";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"color-scheme",0xc);
  QString::QString(local_78,(QArrayDataPointer *)local_108);
  local_188 = L"accent-color";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_e8,(QTypedArrayData *)0x0,L"accent-color",0xc);
  QString::QString(aQStack_60,(QArrayDataPointer *)&local_e8);
  local_178 = local_78;
  local_1a8 = (initializer_list<QString> *)&local_178;
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  local_1b0 = (QString *)std::initializer_list<QString>::begin(local_1a8);
  local_1a0 = (QString *)std::initializer_list<QString>::end(local_1a8);
  for (; local_1b0 != local_1a0; local_1b0 = local_1b0 + 0x18) {
    local_198 = local_1b0;
    QString::QString((QString *)&local_e8,"ReadOne");
    QDBusMessage::createMethodCall(local_1b8,local_168,local_148,local_128);
    QString::~QString((QString *)&local_e8);
    QString::QString((QString *)&local_e8,"org.freedesktop.appearance");
    ::QVariant::QVariant(local_b8,(QString *)&local_e8);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1b8,local_b8);
    ::QVariant::QVariant(local_98,local_198);
    QDBusMessage::operator<<(this_00,local_98);
    ::QVariant::~QVariant(local_98);
    ::QVariant::~QVariant(local_b8);
    QString::~QString((QString *)&local_e8);
    this_01 = operator_new(0x18);
    QDBusConnection::asyncCall((QDBusMessage *)&local_e8,(int)local_1c0);
    QDBusPendingCallWatcher::QDBusPendingCallWatcher
              (this_01,(QDBusPendingCall *)&local_e8,(QObject *)this);
    local_190 = this_01;
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_e8);
    local_e8 = this;
    QString::QString(aQStack_e0,local_198);
    local_c8 = local_190;
    QObject::
    connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToPortalSettings()::_lambda()_1_>
              (local_108,local_190,QDBusPendingCallWatcher::finished,0,this,&local_e8,0);
    QMetaObject::Connection::~Connection((Connection *)local_108);
    subscribeToPortalSettings()::{lambda()#1}::~subscribeToPortalSettings((_lambda___1_ *)&local_e8)
    ;
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1b8);
  }
  this_02 = aQStack_48;
  while (this_02 != local_78) {
    this_02 = this_02 + -0x18;
    QString::~QString(this_02);
  }
  QString::QString((QString *)&local_e8,"SettingChanged");
  QDBusConnection::connect
            (local_1c0,local_168,local_148,local_128,(QObject *)&local_e8,(char *)this);
  QString::~QString((QString *)&local_e8);
  QString::~QString(local_128);
  QString::~QString(local_148);
  QString::~QString(local_168);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_1c0);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002440a0  Lelan::fetchAndApply(QString_const&)::{lambda()#1}::operator()

/* Lelan::fetchAndApply(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::fetchAndApply(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  Lelan *this_00;
  char cVar1;
  QDebug *pQVar2;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusVariant> local_158 [8];
  QDebug local_150 [8];
  QString local_148 [32];
  QString local_128 [32];
  QMessageLogger local_108 [32];
  QDBusError local_e8 [64];
  QDBusError local_a8 [64];
  QDBusPendingReply<QDBusVariant> local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusVariant>::QDBusPendingReply
            (local_158,(QDBusPendingCall *)(*(long *)(this + 0x20) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\0') {
    QMessageLogger::QMessageLogger(local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar2 = (QDebug *)QDebug::operator<<(local_150,"[lelan] fetchAndApply ReadOne failed for");
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,(QString *)(this + 8));
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,":");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar2,local_128);
    ::QString::~QString(local_128);
    QDBusError::~QDBusError(local_a8);
    ::QString::~QString(local_148);
    QDBusError::~QDBusError(local_e8);
    QDebug::~QDebug(local_150);
  }
  else {
    this_00 = *(Lelan **)this;
    QDBusPendingReply<QDBusVariant>::value(local_68);
    QDBusVariant::variant();
    applyPortalAppearance(this_00,(QString *)(this + 8),local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant((QDBusVariant *)local_68);
  }
  QDBusPendingReply<QDBusVariant>::~QDBusPendingReply(local_158);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002443b8  Lelan::fetchAndApply(QString_const&)::{lambda()#1}::~QString

/* ~QString() */

void __thiscall Lelan::fetchAndApply(QString_const&)::{lambda()#1}::~QString(_lambda___1_ *this)

{
  ::QString::~QString((QString *)(this + 8));
  return;
}



// ==== 002443d8  Lelan::fetchAndApply

/* WARNING: Removing unreachable block (ram,0x0024471d) */
/* WARNING: Removing unreachable block (ram,0x002447d4) */
/* Lelan::fetchAndApply(QString const&) */

void __thiscall Lelan::fetchAndApply(Lelan *this,QString *param_1)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_1d8 [8];
  QString local_1d0 [8];
  QDBusPendingCallWatcher *local_1c8;
  wchar16 *local_1c0;
  wchar16 *local_1b8;
  wchar16 *local_1b0;
  wchar16 *local_1a8;
  wchar16 *local_1a0;
  QArrayDataPointer<char16_t> local_198 [32];
  QString local_178 [32];
  QArrayDataPointer<char16_t> local_158 [32];
  QString local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  Lelan *local_b8;
  QString aQStack_b0 [24];
  QDBusPendingCallWatcher *local_98;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  local_1a8 = L"ReadOne";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"ReadOne",7);
  QString::QString((QString *)&local_b8,(QArrayDataPointer *)local_d8);
  local_1b0 = L"org.freedesktop.portal.Settings";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_118,(QTypedArrayData *)0x0,L"org.freedesktop.portal.Settings",0x1f);
  QString::QString(local_f8,(QArrayDataPointer *)local_118);
  local_1b8 = L"/org/freedesktop/portal/desktop";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_158,(QTypedArrayData *)0x0,L"/org/freedesktop/portal/desktop",0x1f);
  QString::QString(local_138,(QArrayDataPointer *)local_158);
  local_1c0 = L"org.freedesktop.portal.Desktop";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_198,(QTypedArrayData *)0x0,L"org.freedesktop.portal.Desktop",0x1e);
  QString::QString(local_178,(QArrayDataPointer *)local_198);
  QDBusMessage::createMethodCall(local_1d0,local_178,local_138,local_f8);
  QString::~QString(local_178);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_198);
  QString::~QString(local_138);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_158);
  QString::~QString(local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QString::~QString((QString *)&local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  local_1a0 = L"org.freedesktop.appearance";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_d8,(QTypedArrayData *)0x0,L"org.freedesktop.appearance",0x1a);
  QString::QString((QString *)&local_b8,(QArrayDataPointer *)local_d8);
  ::QVariant::QVariant(local_88,(QString *)&local_b8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1d0,local_88);
  ::QVariant::QVariant(local_68,param_1);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  ::QVariant::~QVariant(local_88);
  QString::~QString((QString *)&local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_b8,(int)local_1d8);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_b8,(QObject *)this);
  local_1c8 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_b8);
  local_b8 = this;
  QString::QString(aQStack_b0,param_1);
  local_98 = local_1c8;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::fetchAndApply(QString_const&)::_lambda()_1_>
            (local_d8,local_1c8,QDBusPendingCallWatcher::finished,0,this,&local_b8,0);
  QMetaObject::Connection::~Connection((Connection *)local_d8);
  fetchAndApply(QString_const&)::{lambda()#1}::~QString((_lambda___1_ *)&local_b8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_1d0);
  QDBusConnection::~QDBusConnection(local_1d8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0024498e  Lelan::applyProperties

/* Lelan::applyProperties(QMap<QString, QVariant> const&) */

void __thiscall Lelan::applyProperties(Lelan *this,QMap *param_1)

{
  Lelan LVar1;
  char cVar2;
  long in_FS_OFFSET;
  undefined8 local_38;
  QString *local_30;
  char *local_28 [3];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)param_1);
  while( true ) {
    local_28[0] = (char *)QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)param_1);
    cVar2 = ::operator!=((const_iterator *)&local_38,(const_iterator *)local_28);
    if (cVar2 == '\0') break;
    local_30 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)&local_38);
    local_28[0] = "darkMode";
    cVar2 = ::operator==(local_30,local_28);
    if (cVar2 == '\0') {
      local_28[0] = "accent";
      cVar2 = ::operator==(local_30,local_28);
      if (cVar2 == '\0') {
        local_28[0] = "font";
        cVar2 = ::operator==(local_30,local_28);
        if (cVar2 != '\0') {
          QMap<QString,QVariant>::const_iterator::value((const_iterator *)&local_38);
          ::QVariant::toString();
          QString::operator=((QString *)(this + 0x290),(QString *)local_28);
          QString::~QString((QString *)local_28);
          systemFontChanged(this);
        }
      }
      else {
        QMap<QString,QVariant>::const_iterator::value((const_iterator *)&local_38);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x278),(QString *)local_28);
        QString::~QString((QString *)local_28);
        onAccentColorChanged(this);
      }
    }
    else {
      QMap<QString,QVariant>::const_iterator::value((const_iterator *)&local_38);
      LVar1 = (Lelan)::QVariant::toBool();
      this[0x336] = LVar1;
      darkModeChanged(this);
    }
    QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)&local_38);
  }
  themeChanged(this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00244b64  Lelan::subscribeToPowerProfiles

/* Lelan::subscribeToPowerProfiles() */

void __thiscall Lelan::subscribeToPowerProfiles(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,FDPROPS);
  QString::QString(local_78,"/net/hadess/PowerProfiles");
  QString::QString(local_98,"net.hadess.PowerProfiles");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00244d04  Lelan::subscribeToPackageKit

/* Lelan::subscribeToPackageKit() */

void __thiscall Lelan::subscribeToPackageKit(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_38,"UpdatesChanged");
  QString::QString(local_58,"org.freedesktop.PackageKit");
  QString::QString(local_78,"/org/freedesktop/PackageKit");
  QString::QString(local_98,"org.freedesktop.PackageKit");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  fetchPackageKitUpdates(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00244eb2  Lelan::fetchPackageKitUpdates()::{lambda()#1}::operator()

/* Lelan::fetchPackageKitUpdates()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::fetchPackageKitUpdates()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char *pcVar1;
  long lVar2;
  char cVar3;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusObjectPath> local_c0 [8];
  QString local_b8 [8];
  QString local_b0 [8];
  QString local_a8 [32];
  QString local_88 [32];
  ulonglong local_68 [4];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QDBusObjectPath>::QDBusPendingReply
            (local_c0,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 == '\x01') {
    cVar3 = QString::isEmpty((QString *)(*(long *)this + 0x200));
    if (cVar3 != '\x01') {
      QDBusConnection::systemBus();
      pcVar1 = *(char **)this;
      QString::QString((QString *)local_68,"Package");
      QString::QString(local_88,"org.freedesktop.PackageKit.Transaction");
      lVar2 = *(long *)this;
      QString::QString(local_a8,"org.freedesktop.PackageKit");
      QDBusConnection::disconnect
                (local_b0,local_a8,(QString *)(lVar2 + 0x200),local_88,(QObject *)local_68,pcVar1);
      QString::~QString(local_a8);
      QString::~QString(local_88);
      QString::~QString((QString *)local_68);
      pcVar1 = *(char **)this;
      QString::QString((QString *)local_68,"Finished");
      QString::QString(local_88,"org.freedesktop.PackageKit.Transaction");
      lVar2 = *(long *)this;
      QString::QString(local_a8,"org.freedesktop.PackageKit");
      QDBusConnection::disconnect
                (local_b0,local_a8,(QString *)(lVar2 + 0x200),local_88,(QObject *)local_68,pcVar1);
      QString::~QString(local_a8);
      QString::~QString(local_88);
      QString::~QString((QString *)local_68);
      QDBusConnection::~QDBusConnection((QDBusConnection *)local_b0);
    }
    QDBusPendingReply<QDBusObjectPath>::value((QDBusPendingReply<QDBusObjectPath> *)local_88);
    QDBusObjectPath::path();
    QString::operator=((QString *)(*(long *)this + 0x200),(QString *)local_68);
    QString::~QString((QString *)local_68);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_88);
    QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)(*(long *)this + 0x1f8));
    QDBusConnection::systemBus();
    pcVar1 = *(char **)this;
    QString::QString((QString *)local_68,"Package");
    QString::QString(local_88,"org.freedesktop.PackageKit.Transaction");
    lVar2 = *(long *)this;
    QString::QString(local_a8,"org.freedesktop.PackageKit");
    QDBusConnection::connect
              (local_b8,local_a8,(QString *)(lVar2 + 0x200),local_88,(QObject *)local_68,pcVar1);
    QString::~QString(local_a8);
    QString::~QString(local_88);
    QString::~QString((QString *)local_68);
    pcVar1 = *(char **)this;
    QString::QString((QString *)local_68,"Finished");
    QString::QString(local_88,"org.freedesktop.PackageKit.Transaction");
    lVar2 = *(long *)this;
    QString::QString(local_a8,"org.freedesktop.PackageKit");
    QDBusConnection::connect
              (local_b8,local_a8,(QString *)(lVar2 + 0x200),local_88,(QObject *)local_68,pcVar1);
    QString::~QString(local_a8);
    QString::~QString(local_88);
    QString::~QString((QString *)local_68);
    QString::QString((QString *)local_68,"GetUpdates");
    QString::QString(local_88,"org.freedesktop.PackageKit.Transaction");
    lVar2 = *(long *)this;
    QString::QString(local_a8,"org.freedesktop.PackageKit");
    QDBusMessage::createMethodCall(local_b0,local_a8,(QString *)(lVar2 + 0x200),local_88);
    QString::~QString(local_a8);
    QString::~QString(local_88);
    QString::~QString((QString *)local_68);
    local_68[0] = 0;
    ::QVariant::fromValue<unsigned_long_long,true>(local_48,local_68);
    QDBusMessage::operator<<((QDBusMessage *)local_b0,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_b0);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_b8);
  }
  QDBusPendingReply<QDBusObjectPath>::~QDBusPendingReply(local_c0);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00245616  Lelan::fetchPackageKitUpdates

/* WARNING: Removing unreachable block (ram,0x00245774) */
/* Lelan::fetchPackageKitUpdates() */

void __thiscall Lelan::fetchPackageKitUpdates(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_d0 [8];
  QString local_c8 [8];
  QDBusPendingCallWatcher *local_c0;
  QString local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  Lelan *local_58;
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString((QString *)&local_58,"CreateTransaction");
  QString::QString(local_78,"org.freedesktop.PackageKit");
  QString::QString(local_98,"/org/freedesktop/PackageKit");
  QString::QString(local_b8,"org.freedesktop.PackageKit");
  QDBusMessage::createMethodCall(local_c8,local_b8,local_98,local_78);
  QString::~QString(local_b8);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString((QString *)&local_58);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_d0);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_c0 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  local_50 = local_c0;
  local_58 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::fetchPackageKitUpdates()::_lambda()_1_>
            (local_78,local_c0,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_c8);
  QDBusConnection::~QDBusConnection(local_d0);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002458ec  Lelan::onPackageKitUpdatesChanged

/* Lelan::onPackageKitUpdatesChanged() */

void __thiscall Lelan::onPackageKitUpdatesChanged(Lelan *this)

{
  packageStateChanged(this);
  fetchPackageKitUpdates(this);
  return;
}



// ==== 00245914  Lelan::onPackageKitUpdatesPackage

/* Lelan::onPackageKitUpdatesPackage(unsigned int, QString const&, QString const&) */

void __thiscall
Lelan::onPackageKitUpdatesPackage(Lelan *this,uint param_1,QString *param_2,QString *param_3)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_70;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_70 = 0;
  ::QVariant::QVariant(local_48,param_1);
  QString::QString(local_68,"info");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_70,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_3);
  QString::QString(local_68,"summary");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_70,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QMap *)&local_70);
  QMap<QString,QVariant>::insert((QMap<QString,QVariant> *)(this + 0x1f8),param_2,local_48);
  ::QVariant::~QVariant(local_48);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_70);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00245b04  Lelan::onPackageKitUpdatesFinished

/* Lelan::onPackageKitUpdatesFinished(unsigned int, unsigned int) */

void Lelan::onPackageKitUpdatesFinished(uint param_1,uint param_2)

{
  undefined4 in_register_0000003c;
  Lelan *this;
  
  this = (Lelan *)CONCAT44(in_register_0000003c,param_1);
  QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(this + 0x1c8),(QMap *)(this + 0x1f8))
  ;
  QString::clear((QString *)(this + 0x200));
  packageStateChanged(this);
  return;
}



// ==== 00245b58  Lelan::subscribeToMemoryMonitor

/* Lelan::subscribeToMemoryMonitor() */

void __thiscall Lelan::subscribeToMemoryMonitor(Lelan *this)

{
  long in_FS_OFFSET;
  QString aQStack_a0 [8];
  QString aQStack_98 [32];
  QString aQStack_78 [32];
  QString aQStack_58 [32];
  QString aQStack_38 [24];
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  QString::QString(aQStack_38,"LowMemoryWarning");
  QString::QString(aQStack_58,"org.freedesktop.portal.MemoryMonitor");
  QString::QString(aQStack_78,"/org/freedesktop/portal/desktop");
  QString::QString(aQStack_98,"org.freedesktop.portal.Desktop");
  QDBusConnection::connect
            (aQStack_a0,aQStack_98,aQStack_78,aQStack_58,(QObject *)aQStack_38,(char *)this);
  QString::~QString(aQStack_98);
  QString::~QString(aQStack_78);
  QString::~QString(aQStack_58);
  QString::~QString(aQStack_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_a0);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00245cf8  Lelan::subscribeToGeoClue()::{lambda()#1}::operator()

/* Lelan::subscribeToGeoClue()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() */

void __thiscall Lelan::subscribeToGeoClue()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  QDBusMessage *pQVar4;
  QDebug *pQVar5;
  long in_FS_OFFSET;
  QDBusPendingReply<QDBusObjectPath> local_1b8 [8];
  QString local_1b0 [8];
  QString local_1a8 [32];
  QString local_188 [32];
  QString local_168 [32];
  QDBusPendingReply<QDBusObjectPath> local_148 [64];
  QString local_108 [64];
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QDBusVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 00245d26 to 00346941 has its CatchHandler @ 002457c0 */
  QDBusPendingReply<QDBusObjectPath>::QDBusPendingReply
            (local_1b8,(QDBusPendingCall *)(*(long *)(this + 0x28) + 0x10));
  cVar3 = QDBusPendingCall::isValid();
  if (cVar3 == '\0') {
    QMessageLogger::QMessageLogger((QMessageLogger *)local_168,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar5 = (QDebug *)QDebug::operator<<((QDebug *)local_1b0,"[lelan] GeoClue2 GetClient failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar5 = (QDebug *)QDebug::operator<<(pQVar5,local_1a8);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar5,local_188);
    QString::~QString(local_188);
    QDBusError::~QDBusError((QDBusError *)local_108);
    QString::~QString(local_1a8);
    QDBusError::~QDBusError((QDBusError *)local_148);
    QDebug::~QDebug((QDebug *)local_1b0);
  }
  else {
    QDBusPendingReply<QDBusObjectPath>::value(local_148);
    QDBusObjectPath::path();
    QString::operator=((QString *)(*(long *)this + 0x308),local_108);
    QString::~QString(local_108);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_148);
    QString::QString(local_168,"org.freedesktop.GeoClue2.Client");
    QString::QString(local_108,"Set");
    QString::QString((QString *)local_148,FDPROPS);
    QDBusMessage::createMethodCall
              (local_1b0,(QString *)(this + 0x10),(QString *)(*(long *)this + 0x308),
               (QString *)local_148);
    QString::~QString((QString *)local_148);
    QString::~QString(local_108);
    ::QVariant::QVariant(local_c8,local_168);
    pQVar4 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1b0,local_c8);
    QString::QString((QString *)local_148,"DesktopId");
    ::QVariant::QVariant(local_a8,(QString *)local_148);
    pQVar4 = (QDBusMessage *)QDBusMessage::operator<<(pQVar4,local_a8);
    QString::QString(local_108,"org.ncde.desktop");
    ::QVariant::QVariant(local_88,local_108);
    QDBusVariant::QDBusVariant(local_68,local_88);
    ::QVariant::fromValue<QDBusVariant,true>(local_48,local_68);
    QDBusMessage::operator<<(pQVar4,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant(local_68);
    ::QVariant::~QVariant(local_88);
    QString::~QString(local_108);
    ::QVariant::~QVariant(local_a8);
    QString::~QString((QString *)local_148);
    ::QVariant::~QVariant(local_c8);
    iVar2 = (int)this;
    QDBusConnection::asyncCall((QDBusMessage *)local_108,iVar2 + 8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_108);
    QString::QString(local_108,"Set");
    QString::QString((QString *)local_148,FDPROPS);
    QDBusMessage::createMethodCall
              (local_1a8,(QString *)(this + 0x10),(QString *)(*(long *)this + 0x308),
               (QString *)local_148);
    QString::~QString((QString *)local_148);
    QString::~QString(local_108);
    ::QVariant::QVariant(local_c8,local_168);
    pQVar4 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1a8,local_c8);
    QString::QString(local_108,"RequestedAccuracyLevel");
    ::QVariant::QVariant(local_a8,local_108);
    pQVar4 = (QDBusMessage *)QDBusMessage::operator<<(pQVar4,local_a8);
    ::QVariant::QVariant(local_88,4);
    QDBusVariant::QDBusVariant(local_68,local_88);
    ::QVariant::fromValue<QDBusVariant,true>(local_48,local_68);
    QDBusMessage::operator<<(pQVar4,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant(local_68);
    ::QVariant::~QVariant(local_88);
    ::QVariant::~QVariant(local_a8);
    QString::~QString(local_108);
    ::QVariant::~QVariant(local_c8);
    QDBusConnection::asyncCall((QDBusMessage *)local_108,iVar2 + 8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_108);
    pcVar1 = *(char **)this;
    QString::QString(local_108,"LocationUpdated");
    QDBusConnection::connect
              ((QString *)(this + 8),(QString *)(this + 0x10),(QString *)(*(long *)this + 0x308),
               local_168,(QObject *)local_108,pcVar1);
    QString::~QString(local_108);
    QString::QString(local_108,"Start");
    QDBusMessage::createMethodCall
              (local_188,(QString *)(this + 0x10),(QString *)(*(long *)this + 0x308),local_168);
    QDBusConnection::asyncCall((QDBusMessage *)local_148,iVar2 + 8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_148);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_188);
    QString::~QString(local_108);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1a8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_1b0);
    QString::~QString(local_168);
  }
  QObject::deleteLater();
  QDBusPendingReply<QDBusObjectPath>::~QDBusPendingReply(local_1b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002466de  Lelan::subscribeToGeoClue()::{lambda()#1}::~subscribeToGeoClue

/* ~subscribeToGeoClue() */

void __thiscall Lelan::subscribeToGeoClue()::{lambda()#1}::~subscribeToGeoClue(_lambda___1_ *this)

{
  QString::~QString((QString *)(this + 0x10));
  QDBusConnection::~QDBusConnection((QDBusConnection *)(this + 8));
  return;
}



// ==== 0024670e  Lelan::subscribeToGeoClue

/* WARNING: Removing unreachable block (ram,0x0024692f) */
/* WARNING: Removing unreachable block (ram,0x00246866) */
/* WARNING: Removing unreachable block (ram,0x00246943) */
/* Lelan::subscribeToGeoClue() */

void __thiscall Lelan::subscribeToGeoClue(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_f0 [8];
  QString local_e8 [8];
  QDBusPendingCallWatcher *local_e0;
  QString local_d8 [32];
  QString local_b8 [32];
  QString local_98 [32];
  Lelan *local_78;
  QDBusConnection aQStack_70 [8];
  QString aQStack_68 [24];
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_d8,"org.freedesktop.GeoClue2");
  QString::QString((QString *)&local_78,"GetClient");
  QString::QString(local_98,"org.freedesktop.GeoClue2.Manager");
  QString::QString(local_b8,"/org/freedesktop/GeoClue2/Manager");
  QDBusMessage::createMethodCall(local_e8,local_d8,local_b8,local_98);
  QString::~QString(local_b8);
  QString::~QString(local_98);
  QString::~QString((QString *)&local_78);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_78,(int)local_f0);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_78,(QObject *)this);
  local_e0 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_78);
  local_78 = this;
  QDBusConnection::QDBusConnection(aQStack_70,local_f0);
  QString::QString(aQStack_68,local_d8);
  local_50 = local_e0;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToGeoClue()::_lambda()_1_>
            (local_98,local_e0,QDBusPendingCallWatcher::finished,0,this,&local_78,0);
                    /* catch() { ... } // from try @ 00245cf7 with catch @ 00246914 */
  QMetaObject::Connection::~Connection((Connection *)local_98);
  subscribeToGeoClue()::{lambda()#1}::~subscribeToGeoClue((_lambda___1_ *)&local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_e8);
  QString::~QString(local_d8);
  QDBusConnection::~QDBusConnection(local_f0);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00246aa6  Lelan::subscribeToTimeDate

/* Lelan::subscribeToTimeDate() */

void __thiscall Lelan::subscribeToTimeDate(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,FDPROPS);
  QString::QString(local_78,"/org/freedesktop/timedate1");
  QString::QString(local_98,"org.freedesktop.timedate1");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  refreshLocation(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00246c54  Lelan::subscribeToHostnameLocale

/* Lelan::subscribeToHostnameLocale() */

void __thiscall Lelan::subscribeToHostnameLocale(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,FDPROPS);
  QString::QString(local_78,"/org/freedesktop/hostname1");
  QString::QString(local_98,"org.freedesktop.hostname1");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,FDPROPS);
  QString::QString(local_78,"/org/freedesktop/locale1");
  QString::QString(local_98,"org.freedesktop.locale1");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00246f0a  Lelan::setTimezone

/* Lelan::setTimezone(QString const&) */

void __thiscall Lelan::setTimezone(Lelan *this,QString *param_1)

{
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  QString local_f0 [8];
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"SetTimezone");
  QString::QString(local_a8,"org.freedesktop.timedate1");
  QString::QString(local_c8,"/org/freedesktop/timedate1");
  QString::QString(local_e8,"org.freedesktop.timedate1");
  QDBusMessage::createMethodCall(local_f0,local_e8,local_c8,local_a8);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_a8);
  QString::~QString(local_88);
  ::QVariant::QVariant(local_68,param_1);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_f0,local_68);
  ::QVariant::QVariant(local_48,false);
  QDBusMessage::operator<<(this_00,local_48);
  ::QVariant::~QVariant(local_48);
  ::QVariant::~QVariant(local_68);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)local_88,(int)local_a8);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_88);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_f0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002471ac  Lelan::setNtp

/* Lelan::setNtp(bool) */

void __thiscall Lelan::setNtp(Lelan *this,bool param_1)

{
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  QString local_f0 [8];
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"SetNTP");
  QString::QString(local_a8,"org.freedesktop.timedate1");
  QString::QString(local_c8,"/org/freedesktop/timedate1");
  QString::QString(local_e8,"org.freedesktop.timedate1");
  QDBusMessage::createMethodCall(local_f0,local_e8,local_c8,local_a8);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString(local_a8);
  QString::~QString(local_88);
  ::QVariant::QVariant(local_68,param_1);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_f0,local_68);
  ::QVariant::QVariant(local_48,false);
  QDBusMessage::operator<<(this_00,local_48);
  ::QVariant::~QVariant(local_48);
  ::QVariant::~QVariant(local_68);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)local_88,(int)local_a8);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_88);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_f0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024744c  Lelan::refreshLocation()::{lambda()#1}::operator()

/* Lelan::refreshLocation()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshLocation()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  QDebug *pQVar2;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_138 [8];
  QDebug local_130 [8];
  QString local_128 [32];
  QString local_108 [32];
  QMessageLogger local_e8 [32];
  QDBusError local_c8 [64];
  QString local_88 [64];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_138,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\0') {
    QMessageLogger::QMessageLogger(local_e8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar2 = (QDebug *)QDebug::operator<<(local_130,"[lelan] timedate1 Get(Timezone) failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,local_128);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar2,local_108);
    QString::~QString(local_108);
    QDBusError::~QDBusError((QDBusError *)local_88);
    QString::~QString(local_128);
    QDBusError::~QDBusError(local_c8);
    QDebug::~QDebug(local_130);
  }
  else {
    QDBusPendingReply<QVariant>::value(local_48);
    ::QVariant::toString();
    QString::operator=((QString *)(*(long *)this + 0x2c0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    timezoneChanged(*(Lelan **)this);
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_138);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00247724  Lelan::refreshLocation

/* WARNING: Removing unreachable block (ram,0x00247909) */
/* Lelan::refreshLocation() */

void __thiscall Lelan::refreshLocation(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QDBusConnection local_120 [8];
  QString local_118 [8];
  QDBusPendingCallWatcher *local_110;
  QString local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  Lelan *local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString((QString *)&local_a8,"Get");
  QString::QString(local_c8,FDPROPS);
  QString::QString(local_e8,"/org/freedesktop/timedate1");
  QString::QString(local_108,"org.freedesktop.timedate1");
  QDBusMessage::createMethodCall(local_118,local_108,local_e8,local_c8);
  QString::~QString(local_108);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  ::QVariant::QVariant(local_88,"org.freedesktop.timedate1");
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_118,local_88);
  ::QVariant::QVariant(local_68,"Timezone");
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  ::QVariant::~QVariant(local_88);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_120);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_110 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_110;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshLocation()::_lambda()_1_>
            (local_c8,local_110,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_118);
  QDBusConnection::~QDBusConnection(local_120);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00247aba  Lelan::subscribeToLogind()::{lambda()#1}::operator()

/* Lelan::subscribeToLogind()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::subscribeToLogind()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  int iVar2;
  QDebug *pQVar3;
  long in_FS_OFFSET;
  QDBusPendingReply<QVariant> local_138 [8];
  QDebug local_130 [8];
  QString local_128 [32];
  QString local_108 [32];
  QMessageLogger local_e8 [32];
  QDBusError local_c8 [64];
  QDBusError local_88 [64];
  QDBusPendingReply<QVariant> local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QVariant>::QDBusPendingReply
            (local_138,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\0') {
    QMessageLogger::QMessageLogger(local_e8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar3 = (QDebug *)QDebug::operator<<(local_130,"[lelan] logind Get(VTNr) failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar3 = (QDebug *)QDebug::operator<<(pQVar3,local_128);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar3,local_108);
    QString::~QString(local_108);
    QDBusError::~QDBusError(local_88);
    QString::~QString(local_128);
    QDBusError::~QDBusError(local_c8);
    QDebug::~QDebug(local_130);
  }
  else {
    QDBusPendingReply<QVariant>::value(local_48);
    iVar2 = ::QVariant::toInt((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    if (iVar2 != *(int *)(*(long *)this + 0x32c)) {
      *(int *)(*(long *)this + 0x32c) = iVar2;
      vtActiveChanged(*(Lelan **)this);
    }
  }
  QDBusPendingReply<QVariant>::~QDBusPendingReply(local_138);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00247da0  Lelan::subscribeToLogind

/* WARNING: Removing unreachable block (ram,0x00248334) */
/* Lelan::subscribeToLogind() */

void __thiscall Lelan::subscribeToLogind(Lelan *this)

{
  QDBusMessage *this_00;
  QDBusPendingCallWatcher *this_01;
  long in_FS_OFFSET;
  QString local_150 [8];
  QString local_148 [8];
  QDBusPendingCallWatcher *local_140;
  undefined1 *local_138;
  undefined1 *local_130;
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  Lelan *local_a8;
  QDBusPendingCallWatcher *local_a0;
  QVariant local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_128,"org.freedesktop.login1");
  QString::QString((QString *)&local_a8,"PropertiesChanged");
  QString::QString(local_c8,FDPROPS);
  QString::QString(local_e8,"/org/freedesktop/login1/session/self");
  QDBusConnection::connect(local_150,local_128,local_e8,local_c8,(QObject *)&local_a8,(char *)this);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"Lock");
  QString::QString(local_c8,"org.freedesktop.login1.Session");
  QString::QString(local_e8,"/org/freedesktop/login1/session/self");
  QDBusConnection::connect(local_150,local_128,local_e8,local_c8,(QObject *)&local_a8,(char *)this);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"Unlock");
  QString::QString(local_c8,"org.freedesktop.login1.Session");
  QString::QString(local_e8,"/org/freedesktop/login1/session/self");
  QDBusConnection::connect(local_150,local_128,local_e8,local_c8,(QObject *)&local_a8,(char *)this);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"PrepareForSleep");
  QString::QString(local_c8,"org.freedesktop.login1.Manager");
  QString::QString(local_e8,"/org/freedesktop/login1");
  QDBusConnection::connect(local_150,local_128,local_e8,local_c8,(QObject *)&local_a8,(char *)this);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  QString::QString((QString *)&local_a8,"Get");
  QString::QString(local_c8,FDPROPS);
  QString::QString(local_e8,"/org/freedesktop/login1/session/self");
  QDBusMessage::createMethodCall(local_148,local_128,local_e8,local_c8);
  QString::~QString(local_e8);
  QString::~QString(local_c8);
  QString::~QString((QString *)&local_a8);
  local_138 = &LAB_002acb30;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"org.freedesktop.login1.Session",0x1e);
  QString::QString(local_e8,(QArrayDataPointer *)local_108);
  ::QVariant::QVariant(local_88,local_e8);
  this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_148,local_88);
  local_130 = &LAB_002acb6e;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"VTNr",4);
  QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
  ::QVariant::QVariant(local_68,(QString *)&local_a8);
  QDBusMessage::operator<<(this_00,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  ::QVariant::~QVariant(local_88);
  QString::~QString(local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  this_01 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)local_150);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_01,(QDBusPendingCall *)&local_a8,(QObject *)this);
  local_140 = this_01;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
  local_a0 = local_140;
  local_a8 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::subscribeToLogind()::_lambda()_1_>
            (local_c8,local_140,QDBusPendingCallWatcher::finished,0,this,&local_a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_c8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_148);
  QString::~QString(local_128);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_150);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00248630  Lelan::subscribeToScreenSaver

/* Lelan::subscribeToScreenSaver() */

void __thiscall Lelan::subscribeToScreenSaver(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::sessionBus();
  QString::QString(local_38,"ActiveChanged");
  QString::QString(local_58,"org.freedesktop.ScreenSaver");
  QString::QString(local_78,"/org/freedesktop/ScreenSaver");
  QString::QString(local_98,"org.freedesktop.ScreenSaver");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002487d0  Lelan::updatePressure

/* Lelan::updatePressure() */

void __thiscall Lelan::updatePressure(Lelan *this)

{
  int *piVar1;
  long in_FS_OFFSET;
  int local_1c;
  uint local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (uint)(this[0x388] != (Lelan)0x0);
  if (this[0x374] == (Lelan)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = 2;
  }
  piVar1 = qMax<int>(&local_1c,(int *)&local_18);
  piVar1 = qMax<int>((int *)(this + 0x370),piVar1);
  local_14 = *piVar1;
  if (local_14 != *(int *)(this + 0x324)) {
    *(int *)(this + 0x324) = local_14;
    thermalPressureChanged(this);
    recomputeAnimLevel(this);
    if (*(long *)(this + 0x440) != 0) {
      AnimPolicy::setThermalPressure(*(AnimPolicy **)(this + 0x440),0 < local_14);
    }
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002488d2  Lelan::discoverThermalThresholds

/* Lelan::discoverThermalThresholds() */

void __thiscall Lelan::discoverThermalThresholds(Lelan *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined8 uVar5;
  QString *pQVar6;
  long in_FS_OFFSET;
  QDir local_200 [8];
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  undefined8 local_1e0;
  double local_1d8;
  QList<QString> *local_1d0;
  undefined8 local_1c8;
  QList<QString> *local_1c0;
  QString *local_1b8;
  double local_1b0;
  undefined1 *local_1a8;
  undefined *local_1a0;
  undefined1 *local_198;
  undefined1 *local_190;
  QFile local_188 [16];
  QList<QString> local_178 [32];
  QString local_158 [32];
  QList<QString> local_138 [32];
  QString local_118 [32];
  QString local_f8 [32];
  undefined4 local_d8 [8];
  undefined4 local_b8 [8];
  undefined4 local_98 [8];
  QList<QString> local_78 [16];
  undefined8 local_68;
  undefined4 local_58 [6];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  this[0x35c] = (Lelan)0x1;
  local_1d8 = -1.0;
  QString::QString((QString *)local_58,"/sys/class/thermal");
  QDir::QDir(local_200,(QString *)local_58);
  QString::~QString((QString *)local_58);
  QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_98,0xffffffff);
  QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)local_b8,1);
  local_78[0] = (QList<QString>)0x0;
  local_78[1] = (QList<QString>)0x0;
  local_78[2] = (QList<QString>)0x0;
  local_78[3] = (QList<QString>)0x0;
  local_78[4] = (QList<QString>)0x0;
  local_78[5] = (QList<QString>)0x0;
  local_78[6] = (QList<QString>)0x0;
  local_78[7] = (QList<QString>)0x0;
  local_78[8] = (QList<QString>)0x0;
  local_78[9] = (QList<QString>)0x0;
  local_78[10] = (QList<QString>)0x0;
  local_78[0xb] = (QList<QString>)0x0;
  local_78[0xc] = (QList<QString>)0x0;
  local_78[0xd] = (QList<QString>)0x0;
  local_78[0xe] = (QList<QString>)0x0;
  local_78[0xf] = (QList<QString>)0x0;
  local_68 = 0;
  QList<QString>::QList(local_78);
  QString::QString((QString *)local_58,"thermal_zone*");
  uVar5 = QList<QString>::operator<<(local_78,(QString *)local_58);
  QDir::entryList(local_178,local_200,uVar5,local_b8[0],local_98[0]);
  QString::~QString((QString *)local_58);
  QList<QString>::~QList(local_78);
  local_1d0 = local_178;
  local_1f8 = QList<QString>::begin(local_1d0);
  local_1f0 = QList<QString>::end(local_1d0);
  do {
    cVar4 = QList<QString>::const_iterator::operator!=((const_iterator *)&local_1f8,local_1f0);
    if (cVar4 == '\0') {
      if (local_1d8 <= 0.0) {
        *(undefined8 *)(this + 0x360) = 0x4056400000000000;
        *(undefined8 *)(this + 0x368) = 0x4055000000000000;
      }
      else {
        *(double *)(this + 0x360) = local_1d8 * 0.85;
        *(double *)(this + 0x368) = local_1d8 * 0.8;
      }
      QList<QString>::~QList(local_178);
      QDir::~QDir(local_200);
      if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_1c8 = QList<QString>::const_iterator::operator*((const_iterator *)&local_1f8);
    QDir::filePath(local_158);
    QDir::QDir((QDir *)local_98,local_158);
    QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_b8,0xffffffff);
    QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)local_d8,2);
    local_78[0] = (QList<QString>)0x0;
    local_78[1] = (QList<QString>)0x0;
    local_78[2] = (QList<QString>)0x0;
    local_78[3] = (QList<QString>)0x0;
    local_78[4] = (QList<QString>)0x0;
    local_78[5] = (QList<QString>)0x0;
    local_78[6] = (QList<QString>)0x0;
    local_78[7] = (QList<QString>)0x0;
    local_78[8] = (QList<QString>)0x0;
    local_78[9] = (QList<QString>)0x0;
    local_78[10] = (QList<QString>)0x0;
    local_78[0xb] = (QList<QString>)0x0;
    local_78[0xc] = (QList<QString>)0x0;
    local_78[0xd] = (QList<QString>)0x0;
    local_78[0xe] = (QList<QString>)0x0;
    local_78[0xf] = (QList<QString>)0x0;
    local_68 = 0;
    QList<QString>::QList(local_78);
    QString::QString((QString *)local_58,"trip_point_*_type");
    uVar5 = QList<QString>::operator<<(local_78,(QString *)local_58);
    QDir::entryList(local_138,local_98,uVar5,local_d8[0],local_b8[0]);
    QString::~QString((QString *)local_58);
    QList<QString>::~QList(local_78);
    QDir::~QDir((QDir *)local_98);
    local_1c0 = local_138;
    local_1e8 = QList<QString>::begin(local_1c0);
    local_1e0 = QList<QString>::end(local_1c0);
    while (cVar4 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_1e8,local_1e0), cVar4 != '\0') {
      local_1b8 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)&local_1e8)
      ;
      ::operator+((QString *)local_78,(char *)local_158);
      ::operator+((QString *)local_58,(QString *)local_78);
      QFile::QFile(local_188,(QString *)local_58);
      QString::~QString((QString *)local_58);
      QString::~QString((QString *)local_78);
                    /* catch() { ... } // from try @ 002494ef with catch @ 00248c10
                       catch() { ... } // from try @ 00249e71 with catch @ 00248c10 */
      QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_58,1)
      ;
      cVar4 = QFile::open(local_188,local_58[0]);
      if (cVar4 == '\x01') {
        QIODevice::readAll();
        QString::fromUtf8<void>((QString *)local_58,(QByteArray *)local_78);
        QString::trimmed(local_118);
        QString::~QString((QString *)local_58);
        QByteArray::~QByteArray((QByteArray *)local_78);
        bVar2 = false;
        bVar1 = false;
        local_1a8 = &LAB_002acc11_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"critical",8);
        QString::QString((QString *)local_98,(QArrayDataPointer *)local_b8);
        cVar4 = ::operator!=(local_118,(QString *)local_98);
        if (cVar4 == '\0') {
LAB_00248d7b:
          bVar3 = false;
        }
        else {
          local_1a0 = &DAT_002acc24;
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"hot",3);
          bVar2 = true;
          QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
          bVar1 = true;
          cVar4 = ::operator!=(local_118,(QString *)local_58);
          if (cVar4 == '\0') goto LAB_00248d7b;
          bVar3 = true;
        }
        if (bVar1) {
          QString::~QString((QString *)local_58);
        }
        if (bVar2) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
        }
        QString::~QString((QString *)local_98);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
        if (!bVar3) {
          QString::QString((QString *)local_d8,local_1b8);
          local_190 = &LAB_002acc2b_1;
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"_temp",5);
          QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
          local_198 = &LAB_002acc38;
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"_type",5);
          QString::QString((QString *)local_98,(QArrayDataPointer *)local_b8);
          pQVar6 = (QString *)QString::replace(local_d8,local_98,local_58,1);
          QString::QString(local_f8,pQVar6);
          QString::~QString((QString *)local_98);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
          QString::~QString((QString *)local_58);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
          QString::~QString((QString *)local_d8);
          ::operator+((QString *)local_78,(char *)local_158);
          ::operator+((QString *)local_58,(QString *)local_78);
          QFile::QFile((QFile *)local_98,(QString *)local_58);
          QString::~QString((QString *)local_58);
          QString::~QString((QString *)local_78);
          QFlags<QIODeviceBase::OpenModeFlag>::QFlags
                    ((QFlags<QIODeviceBase::OpenModeFlag> *)local_58,1);
          cVar4 = QFile::open(local_98,local_58[0]);
          if (cVar4 == '\x01') {
            QIODevice::readAll();
            QByteArray::trimmed((QByteArray *)local_58);
            local_1b0 = (double)QByteArray::toDouble((bool *)local_58);
            local_1b0 = local_1b0 / 1000.0;
            QByteArray::~QByteArray((QByteArray *)local_58);
            QByteArray::~QByteArray((QByteArray *)local_78);
            if ((0.0 < local_1b0) && ((local_1d8 < 0.0 || (local_1b0 < local_1d8)))) {
              local_1d8 = local_1b0;
            }
          }
          QFile::~QFile((QFile *)local_98);
          QString::~QString(local_f8);
        }
        QString::~QString(local_118);
      }
      QFile::~QFile(local_188);
      QList<QString>::const_iterator::operator++((const_iterator *)&local_1e8);
    }
    QList<QString>::~QList(local_138);
    QString::~QString(local_158);
    QList<QString>::const_iterator::operator++((const_iterator *)&local_1f8);
  } while( true );
}



// ==== 00249418  Lelan::checkThermalZones

/* Lelan::checkThermalZones() */

void __thiscall Lelan::checkThermalZones(Lelan *this)

{
  char cVar1;
  undefined8 uVar2;
  int *piVar3;
  long in_FS_OFFSET;
  Lelan local_b9;
  int local_b8;
  int local_b4;
  QDir local_b0 [8];
  undefined8 local_a8;
  undefined8 local_a0;
  QList<QString> *local_98;
  undefined8 local_90;
  undefined4 local_88 [4];
  QList<QString> local_78 [32];
  QList<QString> local_58 [16];
  undefined8 local_48;
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x35c] != (Lelan)0x1) {
    discoverThermalThresholds(this);
  }
  local_b8 = 0;
  QString::QString((QString *)local_38,"/sys/class/thermal");
  QDir::QDir(local_b0,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_88,0xffffffff);
  QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)&local_a0,1);
  local_58[0] = (QList<QString>)0x0;
  local_58[1] = (QList<QString>)0x0;
  local_58[2] = (QList<QString>)0x0;
  local_58[3] = (QList<QString>)0x0;
  local_58[4] = (QList<QString>)0x0;
  local_58[5] = (QList<QString>)0x0;
  local_58[6] = (QList<QString>)0x0;
  local_58[7] = (QList<QString>)0x0;
  local_58[8] = (QList<QString>)0x0;
  local_58[9] = (QList<QString>)0x0;
  local_58[10] = (QList<QString>)0x0;
  local_58[0xb] = (QList<QString>)0x0;
  local_58[0xc] = (QList<QString>)0x0;
  local_58[0xd] = (QList<QString>)0x0;
  local_58[0xe] = (QList<QString>)0x0;
  local_58[0xf] = (QList<QString>)0x0;
  local_48 = 0;
  QList<QString>::QList(local_58);
                    /* try { // try from 002494ef to 00349df6 has its CatchHandler @ 00248c10 */
  QString::QString((QString *)local_38,"thermal_zone*");
  uVar2 = QList<QString>::operator<<(local_58,(QString *)local_38);
  QDir::entryList(local_78,local_b0,uVar2,(undefined4)local_a0,local_88[0]);
  QString::~QString((QString *)local_38);
  QList<QString>::~QList(local_58);
  local_98 = local_78;
  local_a8 = QList<QString>::begin(local_98);
  local_a0 = QList<QString>::end(local_98);
  while (cVar1 = QList<QString>::const_iterator::operator!=((const_iterator *)&local_a8,local_a0),
        cVar1 != '\0') {
    local_90 = QList<QString>::const_iterator::operator*((const_iterator *)&local_a8);
    QDir::filePath((QString *)local_58);
    ::operator+((QString *)local_38,(char *)local_58);
    QFile::QFile((QFile *)local_88,(QString *)local_38);
    QString::~QString((QString *)local_38);
    QString::~QString((QString *)local_58);
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
    cVar1 = QFile::open(local_88,local_38[0]);
    if (cVar1 != '\0') {
      QIODevice::readAll();
      QByteArray::trimmed((QByteArray *)local_38);
      local_b4 = QByteArray::toInt((bool *)local_38,0);
      local_b4 = local_b4 / 1000;
      piVar3 = qMax<int>(&local_b8,&local_b4);
      local_b8 = *piVar3;
      QByteArray::~QByteArray((QByteArray *)local_38);
      QByteArray::~QByteArray((QByteArray *)local_58);
    }
    QFile::~QFile((QFile *)local_88);
    QList<QString>::const_iterator::operator++((const_iterator *)&local_a8);
  }
  if (0 < local_b8) {
    local_b9 = this[0x374];
    if ((double)local_b8 < *(double *)(this + 0x360)) {
      if ((double)local_b8 <= *(double *)(this + 0x368)) {
        local_b9 = (Lelan)0x0;
      }
    }
    else {
      local_b9 = (Lelan)0x1;
    }
    if (local_b9 != this[0x374]) {
      this[0x374] = local_b9;
      updatePressure(this);
      applyThermalCap(this,(bool)local_b9);
    }
  }
  QList<QString>::~QList(local_78);
  QDir::~QDir(local_b0);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002498fc  Lelan::checkCpuFreq

/* Lelan::checkCpuFreq() */

void __thiscall Lelan::checkCpuFreq(Lelan *this)

{
  bool bVar1;
  char cVar2;
  Lelan LVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  int local_d8;
  int local_d4;
  QDir local_d0 [8];
  undefined8 local_c8;
  undefined8 local_c0;
  QList<QString> *local_b8;
  undefined8 local_b0;
  long local_a8;
  long local_a0;
  undefined4 local_98 [4];
  undefined4 local_88 [4];
  QList<QString> local_78 [32];
  undefined1 local_58 [16];
  undefined8 local_48;
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)local_38,"/sys/devices/system/cpu");
  QDir::QDir(local_d0,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_88,0xffffffff);
  QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)local_98,1);
  local_58 = (undefined1  [16])0x0;
  local_48 = 0;
  QList<QString>::QList((QList<QString> *)local_58);
  QString::QString((QString *)local_38,"cpu[0-9]*");
  uVar4 = QList<QString>::operator<<((QList<QString> *)local_58,(QString *)local_38);
  QDir::entryList(local_78,local_d0,uVar4,local_98[0],local_88[0]);
  QString::~QString((QString *)local_38);
  QList<QString>::~QList((QList<QString> *)local_58);
  local_d8 = 0;
  local_d4 = 0;
  local_b8 = local_78;
  local_c8 = QList<QString>::begin(local_b8);
  local_c0 = QList<QString>::end(local_b8);
  do {
    cVar2 = QList<QString>::const_iterator::operator!=((const_iterator *)&local_c8,local_c0);
    if (cVar2 == '\0') {
      if ((local_d8 < 1) || (local_d4 != local_d8)) {
        LVar3 = (Lelan)0x0;
      }
      else {
        LVar3 = (Lelan)0x1;
      }
      if (LVar3 != this[0x388]) {
        this[0x388] = LVar3;
        updatePressure(this);
        if (*(long *)(this + 0x440) != 0) {
          AnimPolicy::setLowPowerCpu(*(AnimPolicy **)(this + 0x440),(bool)LVar3);
        }
      }
      QList<QString>::~QList(local_78);
      QDir::~QDir(local_d0);
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    local_b0 = QList<QString>::const_iterator::operator*((const_iterator *)&local_c8);
    QDir::filePath((QString *)local_58);
    ::operator+((QString *)local_38,local_58);
    QFile::QFile((QFile *)local_98,(QString *)local_38);
    QString::~QString((QString *)local_38);
    QString::~QString((QString *)local_58);
    QDir::filePath((QString *)local_58);
    ::operator+((QString *)local_38,local_58);
    QFile::QFile((QFile *)local_88,(QString *)local_38);
    QString::~QString((QString *)local_38);
    QString::~QString((QString *)local_58);
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_58,1);
    cVar2 = QFile::open(local_98,local_58._0_4_);
    if (cVar2 == '\0') {
LAB_00249b7f:
      bVar1 = false;
    }
    else {
      QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1)
      ;
      cVar2 = QFile::open(local_88,local_38[0]);
      if (cVar2 == '\0') goto LAB_00249b7f;
      bVar1 = true;
    }
    if (bVar1) {
      QIODevice::readAll();
      QByteArray::trimmed((QByteArray *)local_38);
      local_a8 = QByteArray::toLongLong((bool *)local_38,0);
      QByteArray::~QByteArray((QByteArray *)local_38);
      QByteArray::~QByteArray((QByteArray *)local_58);
      QIODevice::readAll();
      QByteArray::trimmed((QByteArray *)local_38);
      local_a0 = QByteArray::toLongLong((bool *)local_38,0);
      QByteArray::~QByteArray((QByteArray *)local_38);
      QByteArray::~QByteArray((QByteArray *)local_58);
      if (0 < local_a0) {
        local_d8 = local_d8 + 1;
        if ((local_a0 * 0x5f) / 100 <= local_a8) {
          local_d4 = local_d4 + 1;
        }
      }
    }
    QFile::~QFile((QFile *)local_88);
    QFile::~QFile((QFile *)local_98);
    QList<QString>::const_iterator::operator++((const_iterator *)&local_c8);
  } while( true );
}



// ==== 00249ef0  Lelan::setAnimUtilClamp

/* Lelan::setAnimUtilClamp(bool) */

void __thiscall Lelan::setAnimUtilClamp(Lelan *this,bool param_1)

{
  long in_FS_OFFSET;
  undefined4 local_48 [2];
  undefined8 local_40;
  undefined4 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  memset(local_48,0,0x38);
  local_48[0] = 0x38;
  local_40 = 0x28;
  if (param_1) {
    local_18 = 200;
  }
  else {
    local_18 = 0;
  }
  syscall(0x13a,0,local_48,0);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00249f80  Lelan::applyZenStartupHints

/* Lelan::applyZenStartupHints() */

void Lelan::applyZenStartupHints(void)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  sched_param local_5c;
  QFile local_58 [16];
  undefined4 local_48 [10];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)local_48,"/proc/self/autogroup");
  QFile::QFile(local_58,(QString *)local_48);
  QString::~QString((QString *)local_48);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_48,2);
  cVar1 = QFile::open(local_58,local_48[0]);
  if (cVar1 != '\0') {
    QIODevice::write((char *)local_58);
    QFileDevice::close();
  }
  local_5c.__sched_priority = 1;
  iVar2 = sched_setscheduler(0,1,&local_5c);
  if (iVar2 != 0) {
    QMessageLogger::QMessageLogger((QMessageLogger *)local_48,(char *)0x0,0,(char *)0x0);
    QMessageLogger::info((char *)local_48,&LAB_002accc0);
  }
  QFile::~QFile(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024a0fa  Lelan::recomputeAnimLevel

/* Lelan::recomputeAnimLevel() */

void __thiscall Lelan::recomputeAnimLevel(Lelan *this)

{
  int iVar1;
  bool bVar2;
  long in_FS_OFFSET;
  int local_90;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_90 = 0;
  ::QVariant::QVariant(local_68);
  QString::QString(local_88,"percentage");
  QMap<QString,QVariant>::value(local_48,(QVariant *)(this + 0x88));
  iVar1 = ::QVariant::toInt((bool *)local_48);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_68);
  if ((this[0x33a] != (Lelan)0x0) || (0 < *(int *)(this + 0x324))) {
    local_90 = 1;
  }
  if (((this[0x339] != (Lelan)0x0) || (1 < *(int *)(this + 0x324))) ||
     ((this[0x33a] != (Lelan)0x0 && (iVar1 < 0x10)))) {
    local_90 = 2;
  }
  if (local_90 < *(int *)(this + 0x358)) {
    local_90 = *(int *)(this + 0x358);
  }
  if (local_90 != *(int *)(this + 0x330)) {
    *(int *)(this + 0x330) = local_90;
    animLevelChanged(this);
  }
  if (*(long *)(this + 0x440) != 0) {
    AnimPolicy::setReduceMotion(*(AnimPolicy **)(this + 0x440),(bool)this[0x339]);
    AnimPolicy::setLevel(*(AnimPolicy **)(this + 0x440),*(int *)(this + 0x330));
    if ((this[0x33a] == (Lelan)0x0) || (0xf < iVar1)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    AnimPolicy::setLowPowerBattery(*(AnimPolicy **)(this + 0x440),bVar2);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024a392  Lelan::scheduleNightLightEvents(double,double)::{lambda()#1}::operator()

/* Lelan::scheduleNightLightEvents(double, double)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const
    */

void __thiscall
Lelan::scheduleNightLightEvents(double,double)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  long lVar1;
  byte bVar2;
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_c8 [32];
  QString local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = *(long *)this;
  ::QVariant::QVariant(local_88);
  QString::QString(local_a8,"night");
  QMap<QString,QVariant>::value(local_68,(QVariant *)(lVar1 + 0x1d8));
  bVar2 = ::QVariant::toBool();
  ::QVariant::QVariant(local_48,(bool)(bVar2 ^ 1));
  lVar1 = *(long *)this;
  QString::QString(local_c8,"night");
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(lVar1 + 0x1d8),local_c8);
  ::QVariant::operator=(this_00,local_48);
  QString::~QString(local_c8);
  ::QVariant::~QVariant(local_48);
  ::QVariant::~QVariant((QVariant *)local_68);
  QString::~QString(local_a8);
  ::QVariant::~QVariant(local_88);
  placeNameChanged(*(Lelan **)this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024a55c  Lelan::scheduleNightLightEvents

/* Lelan::scheduleNightLightEvents(double, double) */

void __thiscall Lelan::scheduleNightLightEvents(Lelan *this,double param_1,double param_2)

{
  int iVar1;
  int iVar2;
  QVariant *pQVar3;
  long in_FS_OFFSET;
  bool local_85;
  double local_80;
  double local_78;
  Lelan *local_68 [4];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((0.0 <= param_1) && (0.0 <= param_2)) {
    ::QVariant::QVariant(local_48,param_2);
    QString::QString((QString *)local_68,"sunrise");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)(this + 0x1d8),(QString *)local_68);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,param_1);
    QString::QString((QString *)local_68,"sunset");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)(this + 0x1d8),(QString *)local_68);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::~QVariant(local_48);
    QTime::currentTime();
    iVar1 = QTime::hour();
    iVar2 = QTime::minute();
    local_78 = (double)iVar2 / 60.0 + (double)iVar1;
    if (param_1 <= param_2) {
      if ((local_78 < param_1) || (param_2 <= local_78)) {
        local_85 = false;
      }
      else {
        local_85 = true;
      }
    }
    else if ((param_1 <= local_78) || (local_78 < param_2)) {
      local_85 = true;
    }
    else {
      local_85 = false;
    }
    ::QVariant::QVariant(local_48,local_85);
    QString::QString((QString *)local_68,"night");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)(this + 0x1d8),(QString *)local_68);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::~QVariant(local_48);
    placeNameChanged(this);
    local_80 = param_1;
    if (local_85 != false) {
      local_80 = param_2;
    }
    local_78 = local_80 - local_78;
    if (local_78 <= 0.0) {
      local_78 = local_78 + 24.0;
    }
    local_68[0] = this;
    QTimer::singleShot<int,Lelan::scheduleNightLightEvents(double,double)::_lambda()_1_>
              ((int)(local_78 * 3600.0 * 1000.0),(ContextType *)this,(_lambda___1_ *)local_68);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0024a94a  Lelan::onBatteryPropertiesChanged

/* Lelan::onBatteryPropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onBatteryPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  int iVar2;
  QVariant *pQVar3;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"Percentage");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Percentage");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QString::QString(local_a8,"percentage");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(param_1 + 0x88),local_a8)
    ;
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  QString::QString(local_88,"State");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"State");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QString::QString(local_a8,"state");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(param_1 + 0x88),local_a8)
    ;
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"State");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    iVar2 = ::QVariant::toUInt((bool *)local_48);
    param_1[0x33a] = (QString)(iVar2 == 2);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  batteryChanged((Lelan *)param_1);
  powerChanged((Lelan *)param_1);
  recomputeAnimLevel((Lelan *)param_1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024adc6  Lelan::onPowerProfilesPropertiesChanged

/* Lelan::onPowerProfilesPropertiesChanged(QString const&, QMap<QString, QVariant> const&,
   QList<QString> const&) */

void Lelan::onPowerProfilesPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  AnimPolicy *this;
  char cVar1;
  bool bVar2;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"ActiveProfile");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"ActiveProfile");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    ::QVariant::toString();
    QString::operator=(param_1 + 0x260,local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    powerProfileChanged((Lelan *)param_1);
    powerChanged((Lelan *)param_1);
    if (*(long *)(param_1 + 0x440) != 0) {
      this = *(AnimPolicy **)(param_1 + 0x440);
      QLatin1String::QLatin1String((QLatin1String *)local_88,"power-saver");
      bVar2 = (bool)::operator==(param_1 + 0x260,(QLatin1String *)local_88);
      AnimPolicy::setLowPowerProfile(this,bVar2);
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024b00a  Lelan::onPortalSettingChanged

/* Lelan::onPortalSettingChanged(QString const&, QString const&, QDBusVariant const&) */

void Lelan::onPortalSettingChanged(QString *param_1,QString *param_2,QDBusVariant *param_3)

{
  char cVar1;
  long in_FS_OFFSET;
  char *local_50;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_50 = "org.freedesktop.appearance";
  cVar1 = ::operator==(param_2,&local_50);
  if (cVar1 != '\0') {
    QDBusVariant::variant();
    applyPortalAppearance((Lelan *)param_1,(QString *)param_3,local_48);
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024b0d6  Lelan::applyPortalAppearance

/* Lelan::applyPortalAppearance(QString const&, QVariant const&) */

void __thiscall Lelan::applyPortalAppearance(Lelan *this,QString *param_1,QVariant *param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  QDBusArgument *pQVar4;
  long in_FS_OFFSET;
  double local_70;
  double local_68;
  double local_60;
  char *local_58 [4];
  undefined1 local_38 [16];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_58[0] = "color-scheme";
  cVar1 = ::operator==(param_1,local_58);
  if (cVar1 == '\0') {
    local_58[0] = "accent-color";
    cVar1 = ::operator==(param_1,local_58);
    if (cVar1 != '\0') {
      local_70 = -1.0;
      local_68 = -1.0;
      local_60 = -1.0;
      bVar2 = ::QVariant::canConvert<QDBusArgument>(param_2);
      if (bVar2) {
        ::QVariant::value<QDBusArgument>((QVariant *)local_58);
        QDBusArgument::beginStructure();
        pQVar4 = (QDBusArgument *)QDBusArgument::operator>>((QDBusArgument *)local_58,&local_70);
        pQVar4 = (QDBusArgument *)QDBusArgument::operator>>(pQVar4,&local_68);
        QDBusArgument::operator>>(pQVar4,&local_60);
        QDBusArgument::endStructure();
        QDBusArgument::~QDBusArgument((QDBusArgument *)local_58);
      }
      if ((((local_70 < 0.0) || (1.0 < local_70)) || (local_68 < 0.0)) ||
         (((1.0 < local_68 || (local_60 < 0.0)) || (1.0 < local_60)))) {
        QString::clear((QString *)(this + 0x278));
      }
      else {
        local_38 = QColor::fromRgbF((float)local_70,(float)local_68,(float)local_60,1.0);
        QColor::name(local_58,local_38,0);
        QString::operator=((QString *)(this + 0x278),(QString *)local_58);
        QString::~QString((QString *)local_58);
      }
      onAccentColorChanged(this);
      themeChanged(this);
    }
  }
  else {
    iVar3 = ::QVariant::toUInt((bool *)param_2);
    this[0x336] = (Lelan)(iVar3 == 1);
    darkModeChanged(this);
    themeChanged(this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024b3ae  Lelan::onLowMemoryWarning

/* Lelan::onLowMemoryWarning(unsigned char) */

void __thiscall Lelan::onLowMemoryWarning(Lelan *this,uchar param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 200) {
    if (param_1 < 100) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 2;
  }
  *(undefined4 *)(this + 0x370) = uVar1;
  updatePressure(this);
  if (*(long *)(this + 0x440) != 0) {
    AnimPolicy::setLowPowerMemory(*(AnimPolicy **)(this + 0x440),0 < *(int *)(this + 0x370));
  }
  return;
}



// ==== 0024b42e  Lelan::onGeoClue2Location(QDBusObjectPath_const&,QDBusObjectPath_const&)::{lambda()#1}::operator()

/* Lelan::onGeoClue2Location(QDBusObjectPath const&, QDBusObjectPath
   const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Lelan::onGeoClue2Location(QDBusObjectPath_const&,QDBusObjectPath_const&)::{lambda()#1}::operator()
          (_lambda___1_ *this)

{
  long lVar1;
  char cVar2;
  QVariant *pQVar3;
  QDebug *pQVar4;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QString,QVariant>> local_168 [8];
  QDebug local_160 [8];
  double local_158;
  double local_150;
  QString local_148 [32];
  QString local_128 [32];
  QDBusPendingReply<QMap<QString,QVariant>> local_108 [32];
  double local_e8 [8];
  double local_a8 [8];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QString,QVariant>>::QDBusPendingReply
            (local_168,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\0') {
    QMessageLogger::QMessageLogger((QMessageLogger *)local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)QDebug::operator<<(local_160,"[lelan] GeoClue2 Location GetAll failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar4,local_128);
    QString::~QString(local_128);
    QDBusError::~QDBusError((QDBusError *)local_a8);
    QString::~QString(local_148);
    QDBusError::~QDBusError((QDBusError *)local_e8);
    QDebug::~QDebug(local_160);
    *(undefined1 *)(*(long *)this + 800) = 0;
    placeNameChanged(*(Lelan **)this);
  }
  else {
    QDBusPendingReply<QMap<QString,QVariant>>::value(local_108);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_a8,"Latitude");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    local_158 = (double)::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    QString::QString((QString *)local_a8,"Longitude");
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_108);
    local_150 = (double)::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant((QVariant *)local_48,local_158);
    lVar1 = *(long *)this;
    QString::QString((QString *)local_a8,"lat");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)(lVar1 + 0x1d8),(QString *)local_a8);
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    ::QVariant::QVariant((QVariant *)local_48,local_150);
    lVar1 = *(long *)this;
    QString::QString((QString *)local_a8,"lon");
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)(lVar1 + 0x1d8),(QString *)local_a8);
    ::QVariant::operator=(pQVar3,(QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    *(undefined1 *)(*(long *)this + 800) = 0;
    placeNameChanged(*(Lelan **)this);
    weatherChanged(*(Lelan **)this);
    moonPositionChanged(*(Lelan **)this);
    timezoneChanged(*(Lelan **)this);
    local_e8[0] = -1.0;
    local_a8[0] = -1.0;
    (anonymous_namespace)::computeSunTimes(local_158,local_150,local_e8,local_a8);
    scheduleNightLightEvents(*(Lelan **)this,local_a8[0],local_e8[0]);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_108);
  }
  QObject::deleteLater();
  QDBusPendingReply<QMap<QString,QVariant>>::~QDBusPendingReply(local_168);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024ba8e  Lelan::onGeoClue2Location

/* WARNING: Removing unreachable block (ram,0x0024bc5a) */
/* Lelan::onGeoClue2Location(QDBusObjectPath const&, QDBusObjectPath const&) */

void Lelan::onGeoClue2Location(QDBusObjectPath *param_1,QDBusObjectPath *param_2)

{
  QDBusPendingCallWatcher *this;
  long in_FS_OFFSET;
  QDBusConnection local_100 [8];
  QString local_f8 [8];
  QDBusPendingCallWatcher *local_f0;
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [32];
  QDBusObjectPath *local_88;
  QDBusPendingCallWatcher *local_80;
  QVariant local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString((QString *)&local_88,"GetAll");
  QString::QString(local_a8,FDPROPS);
  QDBusObjectPath::path();
  QString::QString(local_c8,"org.freedesktop.GeoClue2");
  QDBusMessage::createMethodCall(local_f8,local_c8,local_e8,local_a8);
  QString::~QString(local_c8);
  QString::~QString(local_e8);
  QString::~QString(local_a8);
  QString::~QString((QString *)&local_88);
  QString::QString((QString *)&local_88,"org.freedesktop.GeoClue2.Location");
  ::QVariant::QVariant(local_68,(QString *)&local_88);
  QDBusMessage::operator<<((QDBusMessage *)local_f8,local_68);
  ::QVariant::~QVariant(local_68);
  QString::~QString((QString *)&local_88);
  this = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_88,(int)local_100);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this,(QDBusPendingCall *)&local_88,(QObject *)param_1);
  local_f0 = this;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_88);
  local_80 = local_f0;
  local_88 = param_1;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::onGeoClue2Location(QDBusObjectPath_const&,QDBusObjectPath_const&)::_lambda()_1_>
            (local_a8,local_f0,QDBusPendingCallWatcher::finished,0,param_1,&local_88,0);
  QMetaObject::Connection::~Connection((Connection *)local_a8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_f8);
  QDBusConnection::~QDBusConnection(local_100);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0024bdf2  Lelan::onTimedate1PropertiesChanged

/* Lelan::onTimedate1PropertiesChanged(QString const&, QMap<QString, QVariant> const&,
   QList<QString> const&) */

void Lelan::onTimedate1PropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"Timezone");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"Timezone");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    ::QVariant::toString();
    QString::operator=(param_1 + 0x2c0,local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    timezoneChanged((Lelan *)param_1);
  }
  QString::QString(local_88,"TimeUSec");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    timeJumped((Lelan *)param_1);
  }
  clockChanged((Lelan *)param_1);
  dateTimeChanged((Lelan *)param_1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024c05e  Lelan::onHostname1PropertiesChanged

/* Lelan::onHostname1PropertiesChanged(QString const&, QMap<QString, QVariant> const&,
   QList<QString> const&) */

void Lelan::onHostname1PropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"Hostname");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,"Hostname");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    ::QVariant::toString();
    QString::operator=(param_1 + 0x2d8,local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
    hostnameChanged((Lelan *)param_1);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024c22e  Lelan::onLocale1PropertiesChanged

/* Lelan::onLocale1PropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onLocale1PropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_c8 [32];
  QList<QString> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"Locale");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_c8,"Locale");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    ::QVariant::toStringList();
    QList<QString>::value((QList<QString> *)local_88,(longlong)local_a8);
    QString::operator=(param_1 + 0x2f0,local_88);
    QString::~QString(local_88);
    QList<QString>::~QList(local_a8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_c8);
    ::QVariant::~QVariant(local_68);
    localeChanged((Lelan *)param_1);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024c43e  Lelan::onScreenSaverActivated

/* Lelan::onScreenSaverActivated(bool) */

void __thiscall Lelan::onScreenSaverActivated(Lelan *this,bool param_1)

{
  this[0x338] = (Lelan)param_1;
  screensaverChanged(this);
  if (*(long *)(this + 0x440) != 0) {
    AnimPolicy::onScreenSaverActivated(*(AnimPolicy **)(this + 0x440),param_1);
  }
  return;
}



// ==== 0024c494  Lelan::onSessionActiveChangedSlot

/* Lelan::onSessionActiveChangedSlot(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onSessionActiveChangedSlot(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  QString QVar2;
  long in_FS_OFFSET;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_88,"Active");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"Active");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QVar2 = (QString)::QVariant::toBool();
    param_1[0x337] = QVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    onSessionActiveChanged((Lelan *)param_1);
    if (*(long *)(param_1 + 0x440) != 0) {
      AnimPolicy::onVtActiveChanged(*(AnimPolicy **)(param_1 + 0x440),(bool)param_1[0x337]);
    }
  }
  QString::QString(local_88,"LockedHint");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_3,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"LockedHint");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_3);
    QVar2 = (QString)::QVariant::toBool();
    param_1[0x338] = QVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
    screensaverChanged((Lelan *)param_1);
    if (*(long *)(param_1 + 0x440) != 0) {
      if (param_1[0x338] == (QString)0x0) {
        AnimPolicy::onSessionUnlocked(*(AnimPolicy **)(param_1 + 0x440));
      }
      else {
        AnimPolicy::onSessionLocked(*(AnimPolicy **)(param_1 + 0x440));
      }
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024c814  Lelan::onSessionLock

/* Lelan::onSessionLock() */

void __thiscall Lelan::onSessionLock(Lelan *this)

{
  this[0x338] = (Lelan)0x1;
  screensaverChanged(this);
  if (*(long *)(this + 0x440) != 0) {
    AnimPolicy::onSessionLocked(*(AnimPolicy **)(this + 0x440));
  }
  return;
}



// ==== 0024c85e  Lelan::onSessionUnlock

/* Lelan::onSessionUnlock() */

void __thiscall Lelan::onSessionUnlock(Lelan *this)

{
  this[0x338] = (Lelan)0x0;
  screensaverChanged(this);
  if (*(long *)(this + 0x440) != 0) {
    AnimPolicy::onSessionUnlocked(*(AnimPolicy **)(this + 0x440));
  }
  return;
}



// ==== 0024c8a8  Lelan::onPrepareForSleep

/* Lelan::onPrepareForSleep(bool) */

void __thiscall Lelan::onPrepareForSleep(Lelan *this,bool param_1)

{
  if (param_1) {
    leanSleeping(this);
  }
  else {
    subscribeToNetworkManager(this);
    subscribeToAudio(this);
    subscribeToPlayers(this);
    retryFallbackSink(this);
    leanWaking(this);
  }
  return;
}



// ==== 0024d33c  Lelan::subscribeToPortalSettings()::{lambda()#1}::subscribeToPortalSettings

/* subscribeToPortalSettings({lambda()#1}&&) */

void __thiscall
Lelan::subscribeToPortalSettings()::{lambda()#1}::subscribeToPortalSettings
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0024d3ec  Lelan::fetchAndApply(QString_const&)::{lambda()#1}::QString

/* QString({lambda()#1}&&) */

void __thiscall
Lelan::fetchAndApply(QString_const&)::{lambda()#1}::QString
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  ::QString::QString((QString *)(this + 8),(QString *)(param_1 + 8));
  *(undefined8 *)(this + 0x20) = *(undefined8 *)(param_1 + 0x20);
  return;
}



// ==== 0024d4e4  Lelan::subscribeToGeoClue()::{lambda()#1}::subscribeToGeoClue

/* subscribeToGeoClue({lambda()#1}&&) */

void __thiscall
Lelan::subscribeToGeoClue()::{lambda()#1}::subscribeToGeoClue
          (_lambda___1_ *this,_lambda___1_ *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  QDBusConnection::QDBusConnection((QDBusConnection *)(this + 8),(QDBusConnection *)(param_1 + 8));
  QString::QString((QString *)(this + 0x10),(QString *)(param_1 + 0x10));
  *(undefined8 *)(this + 0x28) = *(undefined8 *)(param_1 + 0x28);
  return;
}



// ==== 0024e7b4  Lelan::subscribeToBlueZ

/* Lelan::subscribeToBlueZ() */

void __thiscall Lelan::subscribeToBlueZ(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_38,"InterfacesAdded");
  QString::QString(local_58,"org.freedesktop.DBus.ObjectManager");
  QString::QString(local_78,"/");
  QString::QString(local_98,"org.bluez");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::QString(local_38,"InterfacesRemoved");
  QString::QString(local_58,"org.freedesktop.DBus.ObjectManager");
  QString::QString(local_78,"/");
  QString::QString(local_98,"org.bluez");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,FDPROPS);
  QString::QString(local_98);
  QString::QString(local_78,"org.bluez");
  QDBusConnection::connect(local_a0,local_78,local_98,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_78);
  QString::~QString(local_98);
  QString::~QString(local_58);
  QString::~QString(local_38);
  rebuildBluetooth(this);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0024eb7e  Lelan::rebuildBluetooth()::{lambda()#1}::operator()

/* Lelan::rebuildBluetooth()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::rebuildBluetooth()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  bool bVar6;
  QDebug *pQVar7;
  QVariant *pQVar8;
  long in_FS_OFFSET;
  undefined1 local_37a;
  undefined1 local_379;
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>> local_378 [8];
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>> local_370 [8];
  undefined8 local_368;
  undefined8 local_360;
  undefined8 local_358;
  undefined8 local_350;
  QList<QVariant> *local_348;
  undefined8 local_340;
  QMap<QString,QMap<QString,QVariant>> *local_338;
  wchar16 *local_330;
  wchar16 *local_328;
  wchar16 *local_320;
  wchar16 *local_318;
  wchar16 *local_310;
  wchar16 *local_308;
  wchar16 *local_300;
  wchar16 *local_2f8;
  wchar16 *local_2f0;
  wchar16 *local_2e8;
  wchar16 *local_2e0;
  wchar16 *local_2d8;
  wchar16 *local_2d0;
  wchar16 *local_2c8;
  wchar16 *local_2c0;
  wchar16 *local_2b8;
  wchar16 *local_2b0;
  wchar16 *local_2a8;
  wchar16 *local_2a0;
  wchar16 *local_298;
  wchar16 *local_290;
  wchar16 *local_288;
  wchar16 *local_280;
  wchar16 *local_278;
  wchar16 *local_270;
  wchar16 *local_268;
  wchar16 *local_260;
  wchar16 *local_258;
  wchar16 *local_250;
  undefined8 local_248;
  undefined8 local_240;
  undefined8 local_238;
  QList<QVariant> local_228 [16];
  undefined8 local_218;
  QString local_208 [32];
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  QDebug local_1c8 [32];
  QString local_1a8 [32];
  QString local_188 [32];
  undefined8 local_168 [4];
  QDBusError local_148 [64];
  undefined8 local_108 [8];
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QString local_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::QDBusPendingReply
            (local_378,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar5 = QDBusPendingCall::isValid();
  if (cVar5 == '\x01') {
    QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::value(local_370);
    local_37a = 0;
    local_379 = 0;
    local_248 = 0;
    local_240 = 0;
    local_238 = 0;
    local_228[0] = (QList<QVariant>)0x0;
    local_228[1] = (QList<QVariant>)0x0;
    local_228[2] = (QList<QVariant>)0x0;
    local_228[3] = (QList<QVariant>)0x0;
    local_228[4] = (QList<QVariant>)0x0;
    local_228[5] = (QList<QVariant>)0x0;
    local_228[6] = (QList<QVariant>)0x0;
    local_228[7] = (QList<QVariant>)0x0;
    local_228[8] = (QList<QVariant>)0x0;
    local_228[9] = (QList<QVariant>)0x0;
    local_228[10] = (QList<QVariant>)0x0;
    local_228[0xb] = (QList<QVariant>)0x0;
    local_228[0xc] = (QList<QVariant>)0x0;
    local_228[0xd] = (QList<QVariant>)0x0;
    local_228[0xe] = (QList<QVariant>)0x0;
    local_228[0xf] = (QList<QVariant>)0x0;
    local_218 = 0;
    local_368 = 0;
    local_360 = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constBegin
                          ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)local_370);
    while( true ) {
      local_108[0] = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constEnd
                               ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)
                                local_370);
      cVar5 = ::operator!=((const_iterator *)&local_360,(const_iterator *)local_108);
      if (cVar5 == '\0') break;
      local_338 = (QMap<QString,QMap<QString,QVariant>> *)
                  QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::value
                            ((const_iterator *)&local_360);
      local_330 = L"org.bluez.Adapter1";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                 L"org.bluez.Adapter1",0x12);
      QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
      cVar5 = QMap<QString,QMap<QString,QVariant>>::contains(local_338,(QString *)local_108);
      QString::~QString((QString *)local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      if (cVar5 != '\0') {
        local_168[0] = 0;
        QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_168);
        local_328 = L"org.bluez.Adapter1";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                   L"org.bluez.Adapter1",0x12);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QMap<QString,QVariant>>::value(local_188,(QMap *)local_338);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
        ::QVariant::QVariant(local_88);
        local_320 = L"Powered";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Powered",7);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value(local_68,(QVariant *)local_188);
        local_37a = ::QVariant::toBool();
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_88);
        ::QVariant::QVariant(local_88);
        local_318 = L"Discoverable";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Discoverable",
                   0xc);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value(local_68,(QVariant *)local_188);
        local_379 = ::QVariant::toBool();
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_88);
        QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::key
                  ((const_iterator *)&local_360);
        QDBusObjectPath::path();
        QString::operator=((QString *)&local_248,(QString *)local_108);
        QString::~QString((QString *)local_108);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_188);
      }
      local_310 = L"org.bluez.Device1";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                 L"org.bluez.Device1",0x11);
      QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
      cVar5 = QMap<QString,QMap<QString,QVariant>>::contains(local_338,(QString *)local_108);
      QString::~QString((QString *)local_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      if (cVar5 != '\0') {
        local_168[0] = 0;
        QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_168);
        local_308 = L"org.bluez.Device1";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                   L"org.bluez.Device1",0x11);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QMap<QString,QVariant>>::value((QString *)&local_358,(QMap *)local_338);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
        ::QVariant::QVariant(local_88);
        local_300 = L"Icon";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Icon",4);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value(local_68,(QVariant *)&local_358);
        ::QVariant::toString();
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_88);
        local_1e8 = 0;
        local_1e0 = 0;
        local_1d8 = 0;
        bVar1 = false;
        bVar6 = false;
        local_2f8 = L"headset";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"headset",7);
        QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
        cVar5 = QString::contains(local_208,local_168,1);
        if (cVar5 == '\0') {
          local_2f0 = L"audio";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"audio",5);
          bVar1 = true;
          QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
          bVar6 = true;
          cVar5 = QString::contains(local_208,local_108,1);
          if (cVar5 != '\0') goto LAB_0024f3d3;
          bVar2 = false;
        }
        else {
LAB_0024f3d3:
          bVar2 = true;
        }
        if (bVar6) {
          QString::~QString((QString *)local_108);
        }
        if (bVar1) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        }
        QString::~QString((QString *)local_168);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
        if (bVar2) {
          local_2e8 = L"headset";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"headset",7);
          QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
          QString::operator=((QString *)&local_1e8,(QString *)local_108);
          QString::~QString((QString *)local_108);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        }
        else {
          bVar1 = false;
          bVar6 = false;
          local_2e0 = L"keyboard";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"keyboard",8);
          QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
          cVar5 = QString::contains(local_208,local_168,1);
          if (cVar5 == '\0') {
            local_2d8 = L"input";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"input",5);
            bVar1 = true;
            QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
            bVar6 = true;
            cVar5 = QString::contains(local_208,local_108,1);
            if (cVar5 != '\0') goto LAB_0024f5b0;
            bVar2 = false;
          }
          else {
LAB_0024f5b0:
            bVar2 = true;
          }
          if (bVar6) {
            QString::~QString((QString *)local_108);
          }
          if (bVar1) {
            QArrayDataPointer<char16_t>::~QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148);
          }
          QString::~QString((QString *)local_168);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
          if (bVar2) {
            local_2d0 = L"keyboard";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"keyboard",8
                      );
            QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
            QString::operator=((QString *)&local_1e8,(QString *)local_108);
            QString::~QString((QString *)local_108);
            QArrayDataPointer<char16_t>::~QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148);
          }
          else {
            local_2c8 = L"phone";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"phone",5);
            QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
            cVar5 = QString::contains(local_208,local_108,1);
            QString::~QString((QString *)local_108);
            QArrayDataPointer<char16_t>::~QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148);
            if (cVar5 != '\0') {
              local_2c0 = L"phone";
              QArrayDataPointer<char16_t>::QArrayDataPointer
                        ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"phone",5)
              ;
              QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
              QString::operator=((QString *)&local_1e8,(QString *)local_108);
              QString::~QString((QString *)local_108);
              QArrayDataPointer<char16_t>::~QArrayDataPointer
                        ((QArrayDataPointer<char16_t> *)local_148);
            }
          }
        }
        ::QVariant::QVariant(local_88);
        local_2b8 = L"Alias";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Alias",5);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value(local_68,(QVariant *)&local_358);
        ::QVariant::toString();
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_88);
        local_350 = 0;
        cVar5 = QString::isEmpty((QString *)local_1c8);
        if (cVar5 == '\0') {
          QString::QString((QString *)local_108,(QString *)local_1c8);
        }
        else {
          ::QVariant::QVariant(local_a8);
          local_2b0 = L"Name";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,L"Name",4);
          QString::QString((QString *)local_148,(QArrayDataPointer *)local_168);
          QMap<QString,QVariant>::value((QString *)local_88,(QVariant *)&local_358);
          ::QVariant::toString();
        }
        ::QVariant::QVariant((QVariant *)local_68,(QString *)local_108);
        local_2a8 = L"name";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_1a8,(QTypedArrayData *)0x0,L"name",4);
        QString::QString(local_188,(QArrayDataPointer *)local_1a8);
        pQVar8 = (QVariant *)
                 QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_350,local_188);
        ::QVariant::operator=(pQVar8,(QVariant *)local_68);
        QString::~QString(local_188);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1a8);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        if (cVar5 != '\0') {
          ::QVariant::~QVariant(local_88);
          QString::~QString((QString *)local_148);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
          ::QVariant::~QVariant(local_a8);
        }
        ::QVariant::QVariant(local_a8);
        local_2a0 = L"Address";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_168,(QTypedArrayData *)0x0,L"Address",7);
        QString::QString((QString *)local_148,(QArrayDataPointer *)local_168);
        QMap<QString,QVariant>::value((QString *)local_88,(QVariant *)&local_358);
        ::QVariant::toString();
        ::QVariant::QVariant((QVariant *)local_68,(QString *)local_108);
        local_298 = L"address";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_1a8,(QTypedArrayData *)0x0,L"address",7);
        QString::QString(local_188,(QArrayDataPointer *)local_1a8);
        pQVar8 = (QVariant *)
                 QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_350,local_188);
        ::QVariant::operator=(pQVar8,(QVariant *)local_68);
        QString::~QString(local_188);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1a8);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_108);
        ::QVariant::~QVariant(local_88);
        QString::~QString((QString *)local_148);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_168);
        ::QVariant::~QVariant(local_a8);
        ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_1e8);
        local_290 = L"type";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"type",4);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        pQVar8 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_350,(QString *)local_108);
        ::QVariant::operator=(pQVar8,(QVariant *)local_68);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant((QVariant *)local_68);
        ::QVariant::QVariant(local_a8);
        local_288 = L"Paired";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Paired",6);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value((QString *)local_88,(QVariant *)&local_358);
        bVar6 = (bool)::QVariant::toBool();
        ::QVariant::QVariant((QVariant *)local_68,bVar6);
        local_280 = L"paired";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"paired",6);
        QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
        pQVar8 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_350,(QString *)local_168);
        ::QVariant::operator=(pQVar8,(QVariant *)local_68);
        QString::~QString((QString *)local_168);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
        ::QVariant::~QVariant((QVariant *)local_68);
        ::QVariant::~QVariant(local_88);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_a8);
        ::QVariant::QVariant(local_a8);
        local_278 = L"Connected";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Connected",9);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        QMap<QString,QVariant>::value((QString *)local_88,(QVariant *)&local_358);
        bVar6 = (bool)::QVariant::toBool();
        ::QVariant::QVariant((QVariant *)local_68,bVar6);
        local_270 = L"connected";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"connected",9);
        QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
        pQVar8 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_350,(QString *)local_168);
        ::QVariant::operator=(pQVar8,(QVariant *)local_68);
        QString::~QString((QString *)local_168);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
        ::QVariant::~QVariant((QVariant *)local_68);
        ::QVariant::~QVariant(local_88);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        ::QVariant::~QVariant(local_a8);
        ::QVariant::QVariant((QVariant *)local_68,(QMap *)&local_350);
        QList<QVariant>::append(local_228,(QVariant *)local_68);
        ::QVariant::~QVariant((QVariant *)local_68);
        QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::key
                  ((const_iterator *)&local_360);
        QDBusObjectPath::path();
        ::QVariant::QVariant(local_88);
        local_268 = L"address";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"address",7);
        QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
        QMap<QString,QVariant>::value(local_68,(QVariant *)&local_350);
        ::QVariant::toString();
        QHash<QString,QString>::insert
                  ((QHash<QString,QString> *)&local_368,(QString *)local_148,(QString *)local_108);
        QString::~QString((QString *)local_148);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_168);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
        ::QVariant::~QVariant(local_88);
        QString::~QString((QString *)local_108);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_350);
        QString::~QString((QString *)local_1c8);
        QString::~QString((QString *)&local_1e8);
        QString::~QString(local_208);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_358);
      }
      QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::operator++
                ((const_iterator *)&local_360);
    }
    *(undefined1 *)(*(long *)this + 0x148) = local_37a;
    *(undefined1 *)(*(long *)this + 0x149) = local_379;
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0x128),(QList *)local_228);
    QString::operator=((QString *)(*(long *)this + 0x150),(QString *)&local_248);
    QHash<QString,QString>::operator=
              ((QHash<QString,QString> *)(*(long *)this + 0x168),(QHash *)&local_368);
    bluetoothChanged(*(Lelan **)this);
    local_360 = 0;
    local_348 = local_228;
    local_358 = QList<QVariant>::begin(local_348);
    local_350 = QList<QVariant>::end(local_348);
    while (cVar5 = QList<QVariant>::iterator::operator!=((iterator *)&local_358,local_350),
          cVar5 != '\0') {
      local_340 = QList<QVariant>::iterator::operator*((iterator *)&local_358);
      ::QVariant::toMap();
      bVar1 = false;
      bVar6 = false;
      bVar4 = false;
      bVar2 = false;
      local_258 = L"headset";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"headset",7);
      QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
      ::QVariant::QVariant(local_c8);
      local_260 = L"type";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_1e8,(QTypedArrayData *)0x0,L"type",4);
      QString::QString((QString *)local_1c8,(QArrayDataPointer *)&local_1e8);
      QMap<QString,QVariant>::value((QString *)local_a8,(QVariant *)local_208);
      ::QVariant::toString();
      cVar5 = ::operator==(local_1a8,(QString *)local_168);
      if (cVar5 == '\0') {
LAB_00250469:
        bVar3 = false;
      }
      else {
        ::QVariant::QVariant(local_88);
        bVar1 = true;
        local_250 = L"connected";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"connected",9);
        bVar6 = true;
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_148);
        bVar4 = true;
        QMap<QString,QVariant>::value(local_68,(QVariant *)local_208);
        bVar2 = true;
        cVar5 = ::QVariant::toBool();
        if (cVar5 == '\0') goto LAB_00250469;
        bVar3 = true;
      }
      if (bVar2) {
        ::QVariant::~QVariant((QVariant *)local_68);
      }
      if (bVar4) {
        QString::~QString((QString *)local_108);
      }
      if (bVar6) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      }
      if (bVar1) {
        ::QVariant::~QVariant(local_88);
      }
      QString::~QString(local_1a8);
      ::QVariant::~QVariant(local_a8);
      QString::~QString((QString *)local_1c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1e8);
      ::QVariant::~QVariant(local_c8);
      QString::~QString((QString *)local_168);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
      if (bVar3) {
        QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)&local_360,(QMap *)local_208);
      }
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_208);
      if (bVar3) break;
      QList<QVariant>::iterator::operator++((iterator *)&local_358);
    }
    bVar6 = ::operator!=((QMap *)&local_360,(QMap *)(*(long *)this + 0x140));
    if (bVar6) {
      QMap<QString,QVariant>::operator=
                ((QMap<QString,QVariant> *)(*(long *)this + 0x140),(QMap *)&local_360);
      bluetoothAudioDeviceChanged(*(Lelan **)this);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_360);
    QHash<QString,QString>::~QHash((QHash<QString,QString> *)&local_368);
    QList<QVariant>::~QList(local_228);
    QString::~QString((QString *)&local_248);
    QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::~QMap
              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)local_370);
  }
  else {
    QMessageLogger::QMessageLogger((QMessageLogger *)local_168,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar7 = (QDebug *)QDebug::operator<<(local_1c8,"[lelan] BlueZ GetManagedObjects failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar7 = (QDebug *)QDebug::operator<<(pQVar7,local_1a8);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar7,local_188);
    QString::~QString(local_188);
    QDBusError::~QDBusError((QDBusError *)local_108);
    QString::~QString(local_1a8);
    QDBusError::~QDBusError(local_148);
    QDebug::~QDebug(local_1c8);
  }
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::~QDBusPendingReply
            (local_378);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00250e60  Lelan::rebuildBluetooth

/* WARNING: Removing unreachable block (ram,0x002510b2) */
/* Lelan::rebuildBluetooth() */

void __thiscall Lelan::rebuildBluetooth(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_170 [8];
  QString local_168 [8];
  QDBusPendingCallWatcher *local_160;
  wchar16 *local_158;
  undefined *local_150;
  wchar16 *local_148;
  wchar16 *local_140;
  QArrayDataPointer<char16_t> local_138 [32];
  QString local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  Lelan *local_58;
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  local_140 = L"GetManagedObjects";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"GetManagedObjects",0x11);
  QString::QString((QString *)&local_58,(QArrayDataPointer *)local_78);
  local_148 = L"org.freedesktop.DBus.ObjectManager";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"org.freedesktop.DBus.ObjectManager",0x22);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  local_150 = &DAT_002ad44e;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"/",1);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  local_158 = L"org.bluez";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_138,(QTypedArrayData *)0x0,L"org.bluez",9);
  QString::QString(local_118,(QArrayDataPointer *)local_138);
  QDBusMessage::createMethodCall(local_168,local_118,local_d8,local_98);
  QString::~QString(local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_138);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  QString::~QString((QString *)&local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_170);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_160 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  local_50 = local_160;
  local_58 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::rebuildBluetooth()::_lambda()_1_>
            (local_78,local_160,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_168);
  QDBusConnection::~QDBusConnection(local_170);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00251252  Lelan::setBluetoothEnabled

/* Lelan::setBluetoothEnabled(bool) */

void __thiscall Lelan::setBluetoothEnabled(Lelan *this,bool param_1)

{
  char cVar1;
  QDBusMessage *pQVar2;
  long in_FS_OFFSET;
  QString local_190 [8];
  undefined *local_188;
  wchar16 *local_180;
  wchar16 *local_178;
  wchar16 *local_170;
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QDBusVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x150));
  if (cVar1 == '\0') {
    local_188 = &DAT_002ad466;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Set",3);
    QString::QString(local_108,(QArrayDataPointer *)local_128);
    QString::QString(local_e8,FDPROPS);
    local_180 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"org.bluez",9);
    QString::QString(local_148,(QArrayDataPointer *)local_168);
    QDBusMessage::createMethodCall(local_190,local_148,(QString *)(this + 0x150),local_e8);
    QString::~QString(local_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
    QString::~QString(local_e8);
    QString::~QString(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
    local_178 = L"org.bluez.Adapter1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"org.bluez.Adapter1"
               ,0x12);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::QVariant::QVariant(local_c8,(QString *)local_128);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_190,local_c8);
    local_170 = L"Powered";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Powered",7);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant(local_a8,local_e8);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<(pQVar2,local_a8);
    ::QVariant::QVariant(local_88,param_1);
    QDBusVariant::QDBusVariant(local_68,local_88);
    ::QVariant::fromValue<QDBusVariant,true>(local_48,local_68);
    QDBusMessage::operator<<(pQVar2,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant(local_68);
    ::QVariant::~QVariant(local_88);
    ::QVariant::~QVariant(local_a8);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_c8);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_e8,(int)local_108);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_e8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_108);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_190);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00251746  Lelan::setBluetoothDiscoverable

/* Lelan::setBluetoothDiscoverable(bool) */

void __thiscall Lelan::setBluetoothDiscoverable(Lelan *this,bool param_1)

{
  char cVar1;
  QDBusMessage *pQVar2;
  long in_FS_OFFSET;
  QString local_190 [8];
  undefined *local_188;
  wchar16 *local_180;
  wchar16 *local_178;
  wchar16 *local_170;
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QString local_e8 [32];
  QVariant local_c8 [32];
  QVariant local_a8 [32];
  QVariant local_88 [32];
  QDBusVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty((QString *)(this + 0x150));
  if (cVar1 == '\0') {
    local_188 = &DAT_002ad466;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"Set",3);
    QString::QString(local_108,(QArrayDataPointer *)local_128);
    QString::QString(local_e8,FDPROPS);
    local_180 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"org.bluez",9);
    QString::QString(local_148,(QArrayDataPointer *)local_168);
    QDBusMessage::createMethodCall(local_190,local_148,(QString *)(this + 0x150),local_e8);
    QString::~QString(local_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
    QString::~QString(local_e8);
    QString::~QString(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
    local_178 = L"org.bluez.Adapter1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"org.bluez.Adapter1"
               ,0x12);
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    ::QVariant::QVariant(local_c8,(QString *)local_128);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_190,local_c8);
    local_170 = L"Discoverable";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"Discoverable",0xc);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    ::QVariant::QVariant(local_a8,local_e8);
    pQVar2 = (QDBusMessage *)QDBusMessage::operator<<(pQVar2,local_a8);
    ::QVariant::QVariant(local_88,param_1);
    QDBusVariant::QDBusVariant(local_68,local_88);
    ::QVariant::fromValue<QDBusVariant,true>(local_48,local_68);
    QDBusMessage::operator<<(pQVar2,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusVariant::~QDBusVariant(local_68);
    ::QVariant::~QVariant(local_88);
    ::QVariant::~QVariant(local_a8);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_c8);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_e8,(int)local_108);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_e8);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_108);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_190);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00251c3a  Lelan::bluetoothConnect

/* Lelan::bluetoothConnect(QString const&) */

void Lelan::bluetoothConnect(QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_128 [8];
  QString local_120 [8];
  QDBusMessage local_118 [8];
  wchar16 *local_110;
  wchar16 *local_108;
  wchar16 *local_100;
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_f8);
  cVar1 = QString::isEmpty(local_f8);
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_100 = L"Connect";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"Connect",7);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    local_108 = L"org.bluez.Device1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_98,(QTypedArrayData *)0x0,L"org.bluez.Device1",0x11);
    QString::QString(local_78,(QArrayDataPointer *)local_98);
    local_110 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"org.bluez",9);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    QDBusMessage::createMethodCall(local_120,local_b8,local_f8,local_78);
    QDBusConnection::asyncCall(local_118,(int)local_128);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_118);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_120);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    QString::~QString(local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    QDBusConnection::~QDBusConnection(local_128);
  }
  QString::~QString(local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00251f2c  Lelan::bluetoothDisconnect

/* Lelan::bluetoothDisconnect(QString const&) */

void Lelan::bluetoothDisconnect(QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection aQStack_128 [8];
  QString aQStack_120 [8];
  QDBusMessage aQStack_118 [8];
  wchar16 *pwStack_110;
  wchar16 *pwStack_108;
  undefined *puStack_100;
  QString local_f8 [32];
  QArrayDataPointer<char16_t> aQStack_d8 [32];
  QString aQStack_b8 [32];
  QArrayDataPointer<char16_t> aQStack_98 [32];
  QString aQStack_78 [32];
  QArrayDataPointer<char16_t> aQStack_58 [32];
  QString aQStack_38 [24];
  long local_20;
  
                    /* try { // try from 00251f44 to 00351f48 has its CatchHandler @ 00251f6d */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_f8);
  cVar1 = QString::isEmpty(local_f8);
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    puStack_100 = &UNK_002ad47e;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_58,(QTypedArrayData *)0x0,L"Disconnect",10);
    QString::QString(aQStack_38,(QArrayDataPointer *)aQStack_58);
    pwStack_108 = L"org.bluez.Device1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_98,(QTypedArrayData *)0x0,L"org.bluez.Device1",0x11);
    QString::QString(aQStack_78,(QArrayDataPointer *)aQStack_98);
    pwStack_110 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d8,(QTypedArrayData *)0x0,L"org.bluez",9)
    ;
    QString::QString(aQStack_b8,(QArrayDataPointer *)aQStack_d8);
    QDBusMessage::createMethodCall(aQStack_120,aQStack_b8,local_f8,aQStack_78);
    QDBusConnection::asyncCall(aQStack_118,(int)aQStack_128);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)aQStack_118);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_120);
    QString::~QString(aQStack_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d8);
    QString::~QString(aQStack_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_98);
    QString::~QString(aQStack_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_58);
    QDBusConnection::~QDBusConnection(aQStack_128);
  }
  QString::~QString(local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0025221e  Lelan::bluetoothPair

/* Lelan::bluetoothPair(QString const&) */

void Lelan::bluetoothPair(QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_128 [8];
  QString local_120 [8];
  QDBusMessage local_118 [8];
  wchar16 *local_110;
  wchar16 *local_108;
  wchar16 *local_100;
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_f8);
  cVar1 = QString::isEmpty(local_f8);
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
    local_100 = L"Pair";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"Pair",4);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    local_108 = L"org.bluez.Device1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_98,(QTypedArrayData *)0x0,L"org.bluez.Device1",0x11);
    QString::QString(local_78,(QArrayDataPointer *)local_98);
    local_110 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"org.bluez",9);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    QDBusMessage::createMethodCall(local_120,local_b8,local_f8,local_78);
    QDBusConnection::asyncCall(local_118,(int)local_128);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_118);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_120);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    QString::~QString(local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    QDBusConnection::~QDBusConnection(local_128);
  }
  QString::~QString(local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00252510  Lelan::bluetoothRemove

/* Lelan::bluetoothRemove(QString const&) */

void Lelan::bluetoothRemove(QString *param_1)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  QString local_148 [8];
  wchar16 *local_140;
  wchar16 *local_138;
  wchar16 *local_130;
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_128);
  cVar2 = QString::isEmpty(local_128);
  if ((cVar2 == '\0') && (cVar2 = QString::isEmpty(param_1 + 0x150), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (!bVar1) {
    local_130 = L"RemoveDevice";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_88,(QTypedArrayData *)0x0,L"RemoveDevice",0xc);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    local_138 = L"org.bluez.Adapter1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"org.bluez.Adapter1",0x12);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    local_140 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"org.bluez",9);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QDBusMessage::createMethodCall(local_148,local_e8,param_1 + 0x150,local_a8);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)local_68,local_128);
    ::QVariant::fromValue<QDBusObjectPath,true>(local_48,(QDBusObjectPath *)local_68);
    QDBusMessage::operator<<((QDBusMessage *)local_148,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_68);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_148);
  }
  QString::~QString(local_128);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002528a6  Lelan::bluetoothScan

/* Lelan::bluetoothScan() */

void __thiscall Lelan::bluetoothScan(Lelan *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusConnection local_108 [8];
  QString local_100 [8];
  QDBusMessage local_f8 [8];
  wchar16 *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
                    /* try { // try from 002528a7 to 003528ab has its CatchHandler @ 002528cb */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* catch() { ... } // from try @ 002528a7 with catch @ 002528cb */
  cVar1 = QString::isEmpty((QString *)(this + 0x150));
  if (cVar1 == '\0') {
    QDBusConnection::systemBus();
                    /* try { // try from 002528f4 to 003528f8 has its CatchHandler @ 00252844 */
    local_e0 = L"StartDiscovery";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,L"StartDiscovery",0xe);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    local_e8 = L"org.bluez.Adapter1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_98,(QTypedArrayData *)0x0,L"org.bluez.Adapter1",0x12);
    QString::QString(local_78,(QArrayDataPointer *)local_98);
    local_f0 = L"org.bluez";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"org.bluez",9);
                    /* catch() { ... } // from try @ 00252a18 with catch @ 002529c6 */
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    QDBusMessage::createMethodCall(local_100,local_b8,(QString *)(this + 0x150),local_78);
                    /* try { // try from 002529fc to 00352a00 has its CatchHandler @ 00252a03 */
                    /* catch() { ... } // from try @ 002529fc with catch @ 00252a03 */
    QDBusConnection::asyncCall(local_f8,(int)local_108);
                    /* try { // try from 00252a18 to 00352a1c has its CatchHandler @ 002529c6 */
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_f8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_100);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    QString::~QString(local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
                    /* catch() { ... } // from try @ 00252abc with catch @ 00252a6b */
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    QDBusConnection::~QDBusConnection(local_108);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00252b48  Lelan::subscribeToUDisks2

/* Lelan::subscribeToUDisks2() */

void __thiscall Lelan::subscribeToUDisks2(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 00252b6a to 00352b6e has its CatchHandler @ 00252b80 */
  QDBusConnection::systemBus();
                    /* catch() { ... } // from try @ 00252b6a with catch @ 00252b80 */
  QString::QString(local_98,"org.freedesktop.UDisks2");
                    /* try { // try from 00252ba9 to 00352bad has its CatchHandler @ 00252b0e */
  QString::QString(local_38,"InterfacesAdded");
  QString::QString(local_58,"org.freedesktop.DBus.ObjectManager");
  QString::QString(local_78,"/org/freedesktop/UDisks2");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::QString(local_38,"InterfacesRemoved");
  QString::QString(local_58,"org.freedesktop.DBus.ObjectManager");
  QString::QString(local_78,"/org/freedesktop/UDisks2");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::QString(local_38,"PropertiesChanged");
  QString::QString(local_58,"org.freedesktop.UDisks2.Filesystem");
  QString::QString(local_78);
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_78);
  QString::~QString(local_58);
  QString::~QString(local_38);
  refreshRemovableVolumes(this);
  QString::~QString(local_98);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00252e98  Lelan::refreshRemovableVolumes()::{lambda()#1}::operator()

/* Lelan::refreshRemovableVolumes()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshRemovableVolumes()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  char cVar1;
  undefined1 uVar2;
  bool bVar3;
  byte bVar4;
  undefined8 uVar5;
  QVariant *pQVar6;
  QDebug *pQVar7;
  long in_FS_OFFSET;
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>> local_1f0 [8];
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>> local_1e8 [8];
  undefined8 local_1e0;
  undefined8 local_1d8;
  QString local_1d0 [8];
  QVariant local_1c8 [8];
  char *local_1c0;
  QMap<QString,QMap<QString,QVariant>> *local_1b8;
  QMap<QString,QMap<QString,QVariant>> *local_1b0;
  undefined1 local_1a8 [16];
  undefined8 local_198;
  undefined8 local_188 [4];
  QString local_168 [16];
  undefined8 local_158;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  ulong local_e8 [8];
  QString local_a8 [32];
  QVariant local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::QDBusPendingReply
            (local_1f0,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  cVar1 = QDBusPendingCall::isValid();
  if (cVar1 == '\0') {
    QMessageLogger::QMessageLogger((QMessageLogger *)&local_148,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar7 = (QDebug *)
             QDebug::operator<<((QDebug *)local_1a8,"[lelan] UDisks2 GetManagedObjects failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar7 = (QDebug *)QDebug::operator<<(pQVar7,(QString *)local_188);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar7,local_168);
    QString::~QString(local_168);
    QDBusError::~QDBusError((QDBusError *)local_e8);
    QString::~QString((QString *)local_188);
    QDBusError::~QDBusError((QDBusError *)&local_128);
    QDebug::~QDebug((QDebug *)local_1a8);
  }
  else {
    QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::value(local_1e8);
    local_1e0 = 0;
    uVar5 = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constBegin
                      ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)local_1e8);
    local_1a8._0_8_ = uVar5;
    while( true ) {
      local_e8[0] = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constEnd
                              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)
                               local_1e8);
      cVar1 = ::operator!=((const_iterator *)local_1a8,(const_iterator *)local_e8);
      if (cVar1 == '\0') break;
      local_1b0 = (QMap<QString,QMap<QString,QVariant>> *)
                  QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::value
                            ((const_iterator *)local_1a8);
      QString::QString((QString *)local_e8,"org.freedesktop.UDisks2.Drive");
      cVar1 = QMap<QString,QMap<QString,QVariant>>::contains(local_1b0,(QString *)local_e8);
      QString::~QString((QString *)local_e8);
      if (cVar1 != '\0') {
        local_188[0] = 0;
        QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_188);
        QString::QString((QString *)&local_128,"org.freedesktop.UDisks2.Drive");
        QMap<QString,QMap<QString,QVariant>>::value(local_168,(QMap *)local_1b0);
        ::QVariant::QVariant(local_68);
        QString::QString((QString *)local_e8,"Removable");
        QMap<QString,QVariant>::value(local_48,(QVariant *)local_168);
        uVar2 = ::QVariant::toBool();
        local_1c0 = (char *)CONCAT71(local_1c0._1_7_,uVar2);
        QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::key
                  ((const_iterator *)local_1a8);
        QDBusObjectPath::path();
        QHash<QString,bool>::insert
                  ((QHash<QString,bool> *)&local_1e0,(QString *)&local_148,(bool *)&local_1c0);
        QString::~QString((QString *)&local_148);
        ::QVariant::~QVariant((QVariant *)local_48);
        QString::~QString((QString *)local_e8);
        ::QVariant::~QVariant(local_68);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
        QString::~QString((QString *)&local_128);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_188);
      }
      QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::operator++
                ((const_iterator *)local_1a8);
    }
    local_1a8 = (undefined1  [16])0x0;
    local_198 = 0;
    local_1d8 = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constBegin
                          ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)local_1e8);
    while( true ) {
      local_e8[0] = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::constEnd
                              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)
                               local_1e8);
      cVar1 = ::operator!=((const_iterator *)&local_1d8,(const_iterator *)local_e8);
      if (cVar1 == '\0') break;
      local_1b8 = (QMap<QString,QMap<QString,QVariant>> *)
                  QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::value
                            ((const_iterator *)&local_1d8);
      QString::QString((QString *)local_e8,"org.freedesktop.UDisks2.Filesystem");
      cVar1 = QMap<QString,QMap<QString,QVariant>>::contains(local_1b8,(QString *)local_e8);
      QString::~QString((QString *)local_e8);
      if (cVar1 == '\x01') {
        local_128 = 0;
        QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)&local_128);
        QString::QString((QString *)local_e8,"org.freedesktop.UDisks2.Block");
        QMap<QString,QMap<QString,QVariant>>::value(local_1d0,(QMap *)local_1b8);
        QString::~QString((QString *)local_e8);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_128);
        ::QVariant::QVariant(local_68);
        QString::QString((QString *)&local_128,"Drive");
        QMap<QString,QVariant>::value(local_48,(QVariant *)local_1d0);
        ::QVariant::value<QDBusObjectPath>((QVariant *)local_e8);
        QDBusObjectPath::path();
        QDBusObjectPath::~QDBusObjectPath((QDBusObjectPath *)local_e8);
        ::QVariant::~QVariant((QVariant *)local_48);
        QString::~QString((QString *)&local_128);
        ::QVariant::~QVariant(local_68);
        local_e8[0] = local_e8[0] & 0xffffffffffffff00;
        cVar1 = QHash<QString,bool>::value
                          ((QHash<QString,bool> *)&local_1e0,(QString *)local_188,(bool *)local_e8);
        if (cVar1 == '\x01') {
          local_168[0] = (QString)0x0;
          local_168[1] = (QString)0x0;
          local_168[2] = (QString)0x0;
          local_168[3] = (QString)0x0;
          local_168[4] = (QString)0x0;
          local_168[5] = (QString)0x0;
          local_168[6] = (QString)0x0;
          local_168[7] = (QString)0x0;
          local_168[8] = (QString)0x0;
          local_168[9] = (QString)0x0;
          local_168[10] = (QString)0x0;
          local_168[0xb] = (QString)0x0;
          local_168[0xc] = (QString)0x0;
          local_168[0xd] = (QString)0x0;
          local_168[0xe] = (QString)0x0;
          local_168[0xf] = (QString)0x0;
          local_158 = 0;
          local_1c0 = (char *)0x0;
          QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)&local_1c0);
          QString::QString((QString *)&local_128,"org.freedesktop.UDisks2.Filesystem");
          QMap<QString,QMap<QString,QVariant>>::value((QString *)&local_148,(QMap *)local_1b8);
          ::QVariant::QVariant((QVariant *)local_48);
          QString::QString((QString *)local_e8,"MountPoints");
          QMap<QString,QVariant>::value(local_a8,(QVariant *)&local_148);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant((QVariant *)local_48);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_148);
          QString::~QString((QString *)&local_128);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1c0);
          bVar3 = ::QVariant::canConvert<QDBusArgument>((QVariant *)local_a8);
          if (bVar3) {
            ::QVariant::value<QDBusArgument>(local_1c8);
            QDBusArgument::beginArray();
            while (cVar1 = QDBusArgument::atEnd(), cVar1 != '\x01') {
              local_128 = 0;
              local_120 = 0;
              local_118 = 0;
              QDBusArgument::operator>>((QDBusArgument *)local_1c8,(QByteArray *)&local_128);
              cVar1 = QByteArray::isEmpty((QByteArray *)&local_128);
              if (cVar1 != '\x01') {
                local_1c0 = (char *)QByteArray::constData((QByteArray *)&local_128);
                QByteArrayView::QByteArrayView<char_const*,true>
                          ((QByteArrayView *)&local_148,&local_1c0);
                QString::fromLocal8Bit(local_e8,local_148,local_140);
                QList<QString>::operator<<((QList<QString> *)local_168,(QString *)local_e8);
                QString::~QString((QString *)local_e8);
              }
              QByteArray::~QByteArray((QByteArray *)&local_128);
            }
            QDBusArgument::endArray();
            QDBusArgument::~QDBusArgument((QDBusArgument *)local_1c8);
          }
          local_1c0 = (char *)0x0;
          QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::key
                    ((const_iterator *)&local_1d8);
          QDBusObjectPath::path();
                    /* catch() { ... } // from try @ 002535c8 with catch @ 00253596
                       catch() { ... } // from try @ 002536db with catch @ 00253596 */
          ::QVariant::QVariant((QVariant *)local_48,(QString *)local_e8);
          QString::QString((QString *)&local_128,"path");
                    /* try { // try from 002535c8 to 003535cc has its CatchHandler @ 00253596 */
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_128);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_128);
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::QVariant(local_88);
          QString::QString((QString *)&local_128,"Device");
          QMap<QString,QVariant>::value((QString *)local_68,(QVariant *)local_1d0);
          ay2str((QVariant *)local_e8);
          ::QVariant::QVariant((QVariant *)local_48,(QString *)local_e8);
                    /* try { // try from 0025368b to 0035368f has its CatchHandler @ 002536b2 */
          QString::QString((QString *)&local_148,"device");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_148);
                    /* catch() { ... } // from try @ 0025368b with catch @ 002536b2 */
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_148);
                    /* try { // try from 002536db to 003536df has its CatchHandler @ 00253596 */
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant(local_68);
          QString::~QString((QString *)&local_128);
          ::QVariant::~QVariant(local_88);
          ::QVariant::QVariant(local_88);
          QString::QString((QString *)&local_128,"IdLabel");
          QMap<QString,QVariant>::value((QString *)local_68,(QVariant *)local_1d0);
          ::QVariant::toString();
          ::QVariant::QVariant((QVariant *)local_48,(QString *)local_e8);
          QString::QString((QString *)&local_148,"label");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_148);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_148);
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant(local_68);
          QString::~QString((QString *)&local_128);
          ::QVariant::~QVariant(local_88);
          ::QVariant::QVariant(local_68);
          QString::QString((QString *)local_e8,"Size");
          QMap<QString,QVariant>::value(local_48,(QVariant *)local_1d0);
          QString::QString((QString *)&local_128,"size");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_128);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_128);
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant(local_68);
          ::QVariant::QVariant(local_88);
          QString::QString((QString *)&local_128,"IdType");
          QMap<QString,QVariant>::value((QString *)local_68,(QVariant *)local_1d0);
          ::QVariant::toString();
          ::QVariant::QVariant((QVariant *)local_48,(QString *)local_e8);
          QString::QString((QString *)&local_148,"fsType");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_148);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_148);
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant(local_68);
          QString::~QString((QString *)&local_128);
          ::QVariant::~QVariant(local_88);
          bVar4 = QList<QString>::isEmpty((QList<QString> *)local_168);
          ::QVariant::QVariant((QVariant *)local_48,(bool)(bVar4 ^ 1));
          QString::QString((QString *)local_e8,"mounted");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)local_e8);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant((QVariant *)local_48);
          QList<QString>::value((QList<QString> *)local_e8,(longlong)local_168);
          ::QVariant::QVariant((QVariant *)local_48,(QString *)local_e8);
          QString::QString((QString *)&local_128,"mountPoint");
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)&local_128);
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)&local_128);
                    /* catch() { ... } // from try @ 00253b5d with catch @ 00253aec */
          ::QVariant::~QVariant((QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          bVar4 = QList<QString>::isEmpty((QList<QString> *)local_168);
          ::QVariant::QVariant((QVariant *)local_48,(bool)(bVar4 ^ 1));
                    /* try { // try from 00253b29 to 00353b2d has its CatchHandler @ 00253b44 */
          QString::QString((QString *)local_e8,"canUnmount");
                    /* catch() { ... } // from try @ 00253b29 with catch @ 00253b44 */
          pQVar6 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)&local_1c0,(QString *)local_e8);
                    /* try { // try from 00253b5d to 00353b61 has its CatchHandler @ 00253aec */
          ::QVariant::operator=(pQVar6,(QVariant *)local_48);
          QString::~QString((QString *)local_e8);
          ::QVariant::~QVariant((QVariant *)local_48);
          ::QVariant::QVariant((QVariant *)local_48,(QMap *)&local_1c0);
          QList<QVariant>::operator<<((QList<QVariant> *)local_1a8,(QVariant *)local_48);
          ::QVariant::~QVariant((QVariant *)local_48);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1c0);
          ::QVariant::~QVariant((QVariant *)local_a8);
          QList<QString>::~QList((QList<QString> *)local_168);
        }
        QString::~QString((QString *)local_188);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1d0);
      }
      QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::operator++
                ((const_iterator *)&local_1d8);
    }
    QList<QVariant>::operator=((QList<QVariant> *)(*(long *)this + 0x218),(QList *)local_1a8);
    storageChanged(*(Lelan **)this);
    QList<QVariant>::~QList((QList<QVariant> *)local_1a8);
    QHash<QString,bool>::~QHash((QHash<QString,bool> *)&local_1e0);
    QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::~QMap
              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)local_1e8);
  }
  QObject::deleteLater();
  QDBusPendingReply<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::~QDBusPendingReply
            (local_1f0);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00254368  Lelan::refreshRemovableVolumes

/* WARNING: Removing unreachable block (ram,0x002544c6) */
/* Lelan::refreshRemovableVolumes() */

void __thiscall Lelan::refreshRemovableVolumes(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection local_d0 [8];
  QString local_c8 [8];
  QDBusPendingCallWatcher *local_c0;
  QString local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  Lelan *local_58;
  QDBusPendingCallWatcher *local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString((QString *)&local_58,"GetManagedObjects");
  QString::QString(local_78,"org.freedesktop.DBus.ObjectManager");
  QString::QString(local_98,"/org/freedesktop/UDisks2");
  QString::QString(local_b8,"org.freedesktop.UDisks2");
  QDBusMessage::createMethodCall(local_c8,local_b8,local_98,local_78);
  QString::~QString(local_b8);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString((QString *)&local_58);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&local_58,(int)local_d0);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&local_58,(QObject *)this);
  local_c0 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_58);
  local_50 = local_c0;
  local_58 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshRemovableVolumes()::_lambda()_1_>
            (local_78,local_c0,QDBusPendingCallWatcher::finished,0,this,&local_58,0);
                    /* catch() { ... } // from try @ 002545b8 with catch @ 00254535 */
  QMetaObject::Connection::~Connection((Connection *)local_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_c8);
  QDBusConnection::~QDBusConnection(local_d0);
                    /* try { // try from 00254558 to 0035455c has its CatchHandler @ 00254535 */
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* try { // try from 0025456b to 0035456f has its CatchHandler @ 0025458f */
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0025463e  Lelan::mountVolume(QString_const&)::{lambda()#1}::operator()

/* Lelan::mountVolume(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::mountVolume(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshRemovableVolumes(*(Lelan **)this);
  return;
}



// ==== 0025465c  Lelan::mountVolume

/* Lelan::mountVolume(QString const&) */

void __thiscall Lelan::mountVolume(Lelan *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_128 [8];
  wchar16 *local_120;
  wchar16 *local_118;
  wchar16 *local_110;
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  Lelan *local_68 [4];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty(param_1);
  if (cVar1 == '\0') {
    local_110 = L"Mount";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"Mount",5);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    local_118 = L"org.freedesktop.UDisks2.Filesystem";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"org.freedesktop.UDisks2.Filesystem",0x22);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    local_120 = L"org.freedesktop.UDisks2";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"org.freedesktop.UDisks2",0x17);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QDBusMessage::createMethodCall(local_128,local_e8,param_1,local_a8);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    local_68[0] = (Lelan *)0x0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_68);
    ::QVariant::QVariant(local_48,(QMap *)local_68);
    QDBusMessage::operator<<((QDBusMessage *)local_128,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
    QDBusConnection::systemBus();
                    /* catch() { ... } // from try @ 0025487c with catch @ 0025484e
                       catch() { ... } // from try @ 002548f7 with catch @ 0025484e */
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    local_68[0] = this;
    QTimer::singleShot<int,Lelan::mountVolume(QString_const&)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)local_68);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_128);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002549a4  Lelan::unmountVolume(QString_const&)::{lambda()#1}::operator()

/* Lelan::unmountVolume(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::unmountVolume(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshRemovableVolumes(*(Lelan **)this);
  return;
}



// ==== 002549c2  Lelan::unmountVolume

/* Lelan::unmountVolume(QString const&) */

void __thiscall Lelan::unmountVolume(Lelan *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QString aQStack_128 [8];
  wchar16 *pwStack_120;
  wchar16 *pwStack_118;
  wchar16 *local_110;
  QArrayDataPointer<char16_t> aQStack_108 [32];
  QString aQStack_e8 [32];
  QArrayDataPointer<char16_t> aQStack_c8 [32];
  QString aQStack_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  Lelan *apLStack_68 [4];
  QVariant aQStack_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QString::isEmpty(param_1);
                    /* catch() { ... } // from try @ 00254a32 with catch @ 002549fa
                       catch() { ... } // from try @ 0025508a with catch @ 002549fa */
  if (cVar1 == '\0') {
    local_110 = L"Unmount";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"Unmount",7);
    QString::QString((QString *)apLStack_68,(QArrayDataPointer *)local_88);
    pwStack_118 = L"org.freedesktop.UDisks2.Filesystem";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_c8,(QTypedArrayData *)0x0,L"org.freedesktop.UDisks2.Filesystem",0x22);
    QString::QString(aQStack_a8,(QArrayDataPointer *)aQStack_c8);
    pwStack_120 = L"org.freedesktop.UDisks2";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_108,(QTypedArrayData *)0x0,L"org.freedesktop.UDisks2",0x17);
    QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_108);
    QDBusMessage::createMethodCall(aQStack_128,aQStack_e8,param_1,aQStack_a8);
    QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_108);
    QString::~QString(aQStack_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_c8);
    QString::~QString((QString *)apLStack_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    apLStack_68[0] = (Lelan *)0x0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)apLStack_68);
    ::QVariant::QVariant(aQStack_48,(QMap *)apLStack_68);
    QDBusMessage::operator<<((QDBusMessage *)aQStack_128,aQStack_48);
    ::QVariant::~QVariant(aQStack_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)apLStack_68);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)apLStack_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)apLStack_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    apLStack_68[0] = this;
    QTimer::singleShot<int,Lelan::unmountVolume(QString_const&)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)apLStack_68);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_128);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00254d0a  Lelan::refreshPrinters()::{lambda(int,QProcess::ExitStatus)#1}::operator()

/* Lelan::refreshPrinters()::{lambda(int, QProcess::ExitStatus)#1}::TEMPNAMEPLACEHOLDERVALUE(int,
   QProcess::ExitStatus) const */

void Lelan::refreshPrinters()::{lambda(int,QProcess::ExitStatus)#1}::operator()(long *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  bool bVar5;
  int iVar6;
  QVariant *pQVar7;
  long in_FS_OFFSET;
  undefined2 uStack_316;
  undefined4 uStack_314;
  undefined8 local_310;
  undefined8 local_308;
  QRegularExpressionMatch aQStack_300 [8];
  QRegularExpressionMatch aQStack_2f8 [8];
  undefined8 uStack_2f0;
  QList<QString> *local_2e8;
  QList<QVariant> *local_2e0;
  QVariant *local_2d8;
  undefined8 uStack_2d0;
  wchar16 *local_2c8;
  wchar16 *local_2c0;
  wchar16 *pwStack_2b8;
  wchar16 *pwStack_2b0;
  wchar16 *pwStack_2a8;
  wchar16 *pwStack_2a0;
  wchar16 *pwStack_298;
  wchar16 *pwStack_290;
  wchar16 *pwStack_288;
  wchar16 *pwStack_280;
  wchar16 *local_278;
  wchar16 *local_270;
  QString local_268 [32];
  undefined8 local_248;
  undefined8 local_240;
  undefined8 local_238;
  QList<QVariant> local_228 [16];
  undefined8 local_218;
  QList<QString> local_208 [32];
  QString aQStack_1e8 [32];
  QArrayDataPointer<char16_t> aQStack_1c8 [32];
  undefined8 local_1a8 [4];
  undefined8 local_188 [4];
  QString local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  undefined4 local_108 [8];
  undefined2 local_e8 [16];
  undefined4 local_c8 [8];
  QVariant local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [40];
  long local_40;
  
                    /* try { // try from 00254d25 to 00354d74 has its CatchHandler @ 00255036 */
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QProcess::readAllStandardOutput();
  QString::fromUtf8<void>(local_268,(QByteArray *)local_c8);
  QByteArray::~QByteArray((QByteArray *)local_c8);
                    /* try { // try from 00254d90 to 00354d94 has its CatchHandler @ 00254ffa */
  QObject::deleteLater();
  if (operator()(int,QProcess::ExitStatus)::pr == '\0') {
    iVar6 = __cxa_guard_acquire(&operator()(int,QProcess::ExitStatus)::pr);
    if (iVar6 != 0) {
                    /* try { // try from 00254de0 to 00354de4 has its CatchHandler @ 00255022 */
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_108,0);
      local_2c8 = L"^printer (\\S+) (.*)$";
                    /* try { // try from 00254df9 to 00354dfd has its CatchHandler @ 0025500e */
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,
                 L"^printer (\\S+) (.*)$",0x14);
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
                    /* try { // try from 00254e2b to 00354e2f has its CatchHandler @ 00255022 */
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)&operator()(int,QProcess::ExitStatus)::pr,local_c8,
                 local_108[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,&operator()(int,QProcess::ExitStatus)::pr
                   ,&__dso_handle);
      __cxa_guard_release(&operator()(int,QProcess::ExitStatus)::pr);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
    }
  }
  if (operator()(int,QProcess::ExitStatus)::dr == '\0') {
    iVar6 = __cxa_guard_acquire(&operator()(int,QProcess::ExitStatus)::dr);
                    /* try { // try from 00254ebf to 00354ef3 has its CatchHandler @ 0025504a */
    if (iVar6 != 0) {
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_108,0);
      local_2c0 = L"default destination: (\\S+)";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,
                 L"default destination: (\\S+)",0x1a);
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
                    /* catch() { ... } // from try @ 00254aea with catch @ 00254f2a */
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)&operator()(int,QProcess::ExitStatus)::dr,local_c8,
                 local_108[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,&operator()(int,QProcess::ExitStatus)::dr
                   ,&__dso_handle);
      __cxa_guard_release(&operator()(int,QProcess::ExitStatus)::dr);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
    }
  }
                    /* catch() { ... } // from try @ 00254c4e with catch @ 00254f94 */
  local_248 = 0;
  local_240 = 0;
  local_238 = 0;
  local_228[0] = (QList<QVariant>)0x0;
  local_228[1] = (QList<QVariant>)0x0;
  local_228[2] = (QList<QVariant>)0x0;
  local_228[3] = (QList<QVariant>)0x0;
  local_228[4] = (QList<QVariant>)0x0;
  local_228[5] = (QList<QVariant>)0x0;
  local_228[6] = (QList<QVariant>)0x0;
  local_228[7] = (QList<QVariant>)0x0;
  local_228[8] = (QList<QVariant>)0x0;
  local_228[9] = (QList<QVariant>)0x0;
  local_228[10] = (QList<QVariant>)0x0;
  local_228[0xb] = (QList<QVariant>)0x0;
  local_228[0xc] = (QList<QVariant>)0x0;
  local_228[0xd] = (QList<QVariant>)0x0;
  local_228[0xe] = (QList<QVariant>)0x0;
  local_228[0xf] = (QList<QVariant>)0x0;
                    /* catch() { ... } // from try @ 00254c0e with catch @ 00254fb6 */
  local_218 = 0;
  QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_c8,0);
  QChar::QChar<char,true>((QChar *)local_e8,'\n');
                    /* catch() { ... } // from try @ 00254d90 with catch @ 00254ffa */
                    /* catch() { ... } // from try @ 00254df9 with catch @ 0025500e */
  QString::split(local_208,local_268,local_e8[0],local_c8[0],1);
  local_2e8 = local_208;
                    /* catch() { ... } // from try @ 00254e2b with catch @ 00255022 */
  local_310 = QList<QString>::begin(local_2e8);
                    /* catch() { ... } // from try @ 00254d25 with catch @ 00255036 */
  local_308 = QList<QString>::end(local_2e8);
                    /* catch() { ... } // from try @ 00254b61 with catch @ 0025504a
                       catch() { ... } // from try @ 00254ebf with catch @ 0025504a */
  while( true ) {
    cVar4 = QList<QString>::iterator::operator!=((iterator *)&local_310,local_308);
    if (cVar4 == '\0') break;
    uStack_2d0 = QList<QString>::iterator::operator*((iterator *)&local_310);
    QFlags<QRegularExpression::MatchOption>::QFlags
              ((QFlags<QRegularExpression::MatchOption> *)local_c8,0);
    QRegularExpression::match
              (aQStack_300,&operator()(int,QProcess::ExitStatus)::dr,uStack_2d0,0,0,local_c8[0]);
    cVar4 = QRegularExpressionMatch::hasMatch();
    if (cVar4 == '\0') {
      QFlags<QRegularExpression::MatchOption>::QFlags
                ((QFlags<QRegularExpression::MatchOption> *)local_c8,0);
      QRegularExpression::match
                (aQStack_2f8,&operator()(int,QProcess::ExitStatus)::pr,uStack_2d0,0,0,local_c8[0]);
      cVar4 = QRegularExpressionMatch::hasMatch();
      if (cVar4 != '\0') {
        uStack_2f0 = 0;
        QRegularExpressionMatch::captured((int)local_c8);
        ::QVariant::QVariant(local_68,(QString *)local_c8);
        pwStack_2b8 = L"name";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"name",4);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        pQVar7 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&uStack_2f0,(QString *)local_e8);
        ::QVariant::operator=(pQVar7,local_68);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        ::QVariant::~QVariant(local_68);
        QString::~QString((QString *)local_c8);
        QRegularExpressionMatch::captured((int)aQStack_1e8);
        pwStack_2b0 = L"is idle";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"is idle",7);
        QString::QString(local_168,(QArrayDataPointer *)local_188);
        cVar4 = QString::startsWith(aQStack_1e8,local_168,1);
        bVar3 = false;
        bVar2 = false;
        bVar1 = false;
        bVar5 = false;
        if (cVar4 == '\0') {
          pwStack_2a0 = L"is printing";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    (local_128,(QTypedArrayData *)0x0,L"is printing",0xb);
          bVar2 = true;
          QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
          bVar1 = true;
          cVar4 = QString::startsWith(aQStack_1e8,local_108,1);
          if (cVar4 == '\0') {
            QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)&uStack_314,0);
            QChar::QChar<char,true>((QChar *)&uStack_316,'.');
            QString::section(local_c8,aQStack_1e8,uStack_316,0,0,uStack_314);
          }
          else {
            pwStack_298 = L"Printing";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,L"Printing",8)
            ;
            bVar5 = true;
            QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
          }
        }
        else {
          pwStack_2a8 = L"Idle";
          QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"Idle",4)
          ;
          bVar3 = true;
          QString::QString((QString *)local_c8,(QArrayDataPointer *)local_148);
        }
        ::QVariant::QVariant(local_68,(QString *)local_c8);
        pwStack_290 = L"status";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  (aQStack_1c8,(QTypedArrayData *)0x0,L"status",6);
        QString::QString((QString *)local_1a8,(QArrayDataPointer *)aQStack_1c8);
        pQVar7 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&uStack_2f0,(QString *)local_1a8);
        ::QVariant::operator=(pQVar7,local_68);
        QString::~QString((QString *)local_1a8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1c8);
        ::QVariant::~QVariant(local_68);
        QString::~QString((QString *)local_c8);
        if (bVar5) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
        }
        if (bVar1) {
          QString::~QString((QString *)local_108);
        }
        if (bVar2) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
        }
        if (bVar3) {
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
        }
        QString::~QString(local_168);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
        QString::QString((QString *)local_c8);
        ::QVariant::QVariant(local_68,(QString *)local_c8);
        pwStack_288 = L"location";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"location",8);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        pQVar7 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&uStack_2f0,(QString *)local_e8);
        ::QVariant::operator=(pQVar7,local_68);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        ::QVariant::~QVariant(local_68);
        QString::~QString((QString *)local_c8);
        QString::QString((QString *)local_c8);
        ::QVariant::QVariant(local_68,(QString *)local_c8);
        pwStack_280 = L"model";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"model",5);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        pQVar7 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&uStack_2f0,(QString *)local_e8);
        ::QVariant::operator=(pQVar7,local_68);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        ::QVariant::~QVariant(local_68);
        QString::~QString((QString *)local_c8);
        ::QVariant::QVariant(local_68,(QMap *)&uStack_2f0);
        QList<QVariant>::append(local_228,local_68);
        ::QVariant::~QVariant(local_68);
        QString::~QString(aQStack_1e8);
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&uStack_2f0);
      }
      QRegularExpressionMatch::~QRegularExpressionMatch(aQStack_2f8);
    }
    else {
      QRegularExpressionMatch::captured((int)local_c8);
      QString::operator=((QString *)&local_248,(QString *)local_c8);
      QString::~QString((QString *)local_c8);
    }
    QRegularExpressionMatch::~QRegularExpressionMatch(aQStack_300);
    QList<QString>::iterator::operator++((iterator *)&local_310);
  }
  QList<QString>::~QList(local_208);
  local_2e0 = local_228;
                    /* catch() { ... } // from try @ 002553df with catch @ 0025580a */
  local_1a8[0] = QList<QVariant>::begin(local_2e0);
                    /* catch() { ... } // from try @ 002554f2 with catch @ 0025581e */
  local_188[0] = QList<QVariant>::end(local_2e0);
  while( true ) {
    cVar4 = QList<QVariant>::iterator::operator!=((iterator *)local_1a8,local_188[0]);
    if (cVar4 == '\0') break;
    local_2d8 = (QVariant *)QList<QVariant>::iterator::operator*((iterator *)local_1a8);
                    /* catch() { ... } // from try @ 002555e6 with catch @ 00255850 */
    ::QVariant::toMap();
                    /* catch() { ... } // from try @ 002555d0 with catch @ 00255861 */
    ::QVariant::QVariant(local_a8);
                    /* catch() { ... } // from try @ 00255656 with catch @ 00255872 */
    local_278 = L"name";
                    /* catch() { ... } // from try @ 00255640 with catch @ 00255883 */
                    /* catch() { ... } // from try @ 002556c6 with catch @ 00255894 */
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"name",4);
                    /* catch() { ... } // from try @ 002556b0 with catch @ 002558a5 */
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
                    /* catch() { ... } // from try @ 00255736 with catch @ 002558b6 */
                    /* catch() { ... } // from try @ 00255720 with catch @ 002558c7 */
    QMap<QString,QVariant>::value(local_88,(QVariant *)local_168);
                    /* catch() { ... } // from try @ 0025578c with catch @ 002558d8 */
    ::QVariant::toString();
    bVar5 = (bool)::operator==((QString *)local_c8,(QString *)&local_248);
                    /* catch() { ... } // from try @ 002553c9 with catch @ 00255907 */
    ::QVariant::QVariant(local_68,bVar5);
    local_270 = L"isDefault";
                    /* try { // try from 00255933 to 00355937 has its CatchHandler @ 0025536a */
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"isDefault",9);
                    /* catch() { ... } // from try @ 00256056 with catch @ 00255952 */
    QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
    pQVar7 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)local_168,(QString *)local_128);
    ::QVariant::operator=(pQVar7,local_68);
    QString::~QString((QString *)local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    ::QVariant::~QVariant(local_68);
                    /* try { // try from 002559bc to 00355a56 has its CatchHandler @ 00255f23 */
    QString::~QString((QString *)local_c8);
    ::QVariant::~QVariant((QVariant *)local_88);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
    ::QVariant::~QVariant(local_a8);
    ::QVariant::QVariant(local_68,(QMap *)local_168);
    ::QVariant::operator=(local_2d8,local_68);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_168);
    QList<QVariant>::iterator::operator++((iterator *)local_1a8);
  }
  QList<QVariant>::operator=((QList<QVariant> *)(*param_1 + 0x1b0),(QList *)local_228);
  printersChanged((Lelan *)*param_1);
  QList<QVariant>::~QList(local_228);
                    /* try { // try from 00255ab4 to 00355ad3 has its CatchHandler @ 0025602a */
  QString::~QString((QString *)&local_248);
  QString::~QString(local_268);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
                    /* try { // try from 00255e7e to 00355e9a has its CatchHandler @ 0025602a */
  return;
}



// ==== 00255e86  Lelan::refreshPrinters

/* WARNING: Removing unreachable block (ram,0x00255ee6) */
/* Lelan::refreshPrinters() */

void __thiscall Lelan::refreshPrinters(Lelan *this)

{
  QProcess *pQVar1;
  QString *this_00;
  long in_FS_OFFSET;
  undefined4 uStack_13c;
  QProcess *pQStack_138;
  undefined *puStack_130;
  undefined *puStack_128;
  wchar16 *pwStack_120;
  QArrayDataPointer<char16_t> aQStack_118 [32];
  QString aQStack_f8 [32];
  QArrayDataPointer<char16_t> aQStack_d8 [32];
  Connection aCStack_b8 [32];
  Lelan *pLStack_98;
  QProcess *pQStack_90;
  QString aQStack_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  pQVar1 = operator_new(0x10);
  QProcess::QProcess(pQVar1,(QObject *)this);
  pQStack_138 = pQVar1;
  pLStack_98 = this;
  pQStack_90 = pQVar1;
  QObject::
  connect<void(QProcess::*)(int,QProcess::ExitStatus),Lelan::refreshPrinters()::_lambda(int,QProcess::ExitStatus)_1_>
            (aCStack_b8,pQVar1,QProcess::finished,0,this,&pLStack_98,0);
  QMetaObject::Connection::~Connection(aCStack_b8);
  pQVar1 = pQStack_138;
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)&uStack_13c,3);
  puStack_128 = &DAT_002ad874;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d8,(QTypedArrayData *)0x0,L"-p",2);
  QString::QString(aQStack_78,(QArrayDataPointer *)aQStack_d8);
  puStack_130 = &DAT_002ad87a;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)aCStack_b8,(QTypedArrayData *)0x0,L"-d",2);
  QString::QString(aQStack_60,(QArrayDataPointer *)aCStack_b8);
  QList<QString>::QList(&pLStack_98,aQStack_78,2);
  pwStack_120 = L"lpstat";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_118,(QTypedArrayData *)0x0,L"lpstat",6);
  QString::QString(aQStack_f8,(QArrayDataPointer *)aQStack_118);
  QProcess::start(pQVar1,aQStack_f8,&pLStack_98,uStack_13c);
  QString::~QString(aQStack_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_118);
  QList<QString>::~QList((QList<QString> *)&pLStack_98);
  this_00 = aQStack_48;
  while (this_00 != aQStack_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aCStack_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00256266  Lelan::setDefaultPrinter(QString_const&)::{lambda()#1}::operator()

/* Lelan::setDefaultPrinter(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Lelan::setDefaultPrinter(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshPrinters(*(Lelan **)this);
  return;
}



// ==== 00256284  Lelan::setDefaultPrinter

/* Lelan::setDefaultPrinter(QString const&) */

void __thiscall Lelan::setDefaultPrinter(Lelan *this,QString *param_1)

{
  QString *this_00;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> aQStack_118 [32];
  QString aQStack_f8 [32];
  QArrayDataPointer<char16_t> aQStack_d8 [32];
  QList aQStack_b8 [32];
  Lelan *apLStack_98 [4];
  QString aQStack_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)apLStack_98);
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d8,(QTypedArrayData *)0x0,L"-d",2);
  QString::QString(aQStack_78,(QArrayDataPointer *)aQStack_d8);
  QString::QString(aQStack_60,param_1);
  QList<QString>::QList(aQStack_b8,aQStack_78,2);
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_118,(QTypedArrayData *)0x0,L"lpadmin",7);
  QString::QString(aQStack_f8,(QArrayDataPointer *)aQStack_118);
  QProcess::startDetached(aQStack_f8,aQStack_b8,(QString *)apLStack_98,(longlong *)0x0);
  QString::~QString(aQStack_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_118);
  QList<QString>::~QList((QList<QString> *)aQStack_b8);
  this_00 = aQStack_48;
  while (this_00 != aQStack_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d8);
  QString::~QString((QString *)apLStack_98);
  apLStack_98[0] = this;
  QTimer::singleShot<int,Lelan::setDefaultPrinter(QString_const&)::_lambda()_1_>
            (400,(ContextType *)this,(_lambda___1_ *)apLStack_98);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00256558  Lelan::removePrinter(QString_const&)::{lambda()#1}::operator()

/* Lelan::removePrinter(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::removePrinter(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshPrinters(*(Lelan **)this);
  return;
}



// ==== 00256576  Lelan::removePrinter

/* Lelan::removePrinter(QString const&) */

void __thiscall Lelan::removePrinter(Lelan *this,QString *param_1)

{
  QString *this_00;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QList local_b8 [32];
  Lelan *local_98 [4];
  QString local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
                    /* try { // try from 0025657a to 0035657e has its CatchHandler @ 002567fd */
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)local_98);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"-x",2);
  QString::QString(local_78,(QArrayDataPointer *)local_d8);
  QString::QString(local_60,param_1);
                    /* try { // try from 0025661f to 00356623 has its CatchHandler @ 00256858 */
                    /* try { // try from 00256635 to 00356639 has its CatchHandler @ 00256822 */
  QList<QString>::QList(local_b8,local_78,2);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L"lpadmin",7);
  QString::QString(local_f8,(QArrayDataPointer *)local_118);
  QProcess::startDetached(local_f8,local_b8,(QString *)local_98,(longlong *)0x0);
  QString::~QString(local_f8);
                    /* try { // try from 002566cb to 003566cf has its CatchHandler @ 00256858 */
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
                    /* try { // try from 002566e1 to 003566e5 has its CatchHandler @ 00256847 */
  QList<QString>::~QList((QList<QString> *)local_b8);
  this_00 = aQStack_48;
  while (this_00 != local_78) {
    this_00 = this_00 + -0x18;
                    /* try { // try from 002566fa to 003566fe has its CatchHandler @ 00256833 */
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  QString::~QString((QString *)local_98);
  local_98[0] = this;
  QTimer::singleShot<int,Lelan::removePrinter(QString_const&)::_lambda()_1_>
            (400,(ContextType *)this,(_lambda___1_ *)local_98);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
                    /* catch() { ... } // from try @ 002566fa with catch @ 00256833 */
    __stack_chk_fail();
  }
                    /* catch() { ... } // from try @ 002566e1 with catch @ 00256847 */
  return;
}



// ==== 0025684a  Lelan::refreshUsers()::{lambda()#1}::operator()()::~UAcc

/* ~UAcc() */

void __thiscall Lelan::refreshUsers()::{lambda()#1}::operator()()::~UAcc(operator()(_ *this)

{
  QHash<QString,unsigned_long_long>::~QHash((QHash<QString,unsigned_long_long> *)(this + 0x20));
  QHash<QString,QString>::~QHash((QHash<QString,QString> *)(this + 0x18));
  QList<QVariant>::~QList((QList<QVariant> *)this);
  return;
}



// ==== 00257b8a  Lelan::refreshUsers()::{lambda()#1}::operator()

/* WARNING: Removing unreachable block (ram,0x00257e5e) */
/* WARNING: Removing unreachable block (ram,0x00257e28) */
/* WARNING: Removing unreachable block (ram,0x00257e4e) */
/* WARNING: Removing unreachable block (ram,0x0025811a) */
/* WARNING: Removing unreachable block (ram,0x00257e3d) */
/* WARNING: Removing unreachable block (ram,0x002581e2) */
/* Lelan::refreshUsers()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::refreshUsers()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QObject *pQVar1;
  char cVar2;
  undefined4 uVar3;
  QDebug *pQVar4;
  undefined1 (*pauVar5) [16];
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusPendingReply<QList<QDBusObjectPath>> local_1e8 [8];
  QDBusConnection aQStack_1e0 [8];
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  QString aQStack_1c8 [8];
  undefined1 (*pauStack_1c0) [16];
  QList<QDBusObjectPath> *pQStack_1b8;
  undefined8 uStack_1b0;
  QDBusPendingCallWatcher *pQStack_1a8;
  wchar16 *pwStack_1a0;
  wchar16 *pwStack_198;
  wchar16 *pwStack_190;
  QDBusPendingReply<QList<QDBusObjectPath>> local_188 [32];
  QDebug local_168 [32];
  QString local_148 [32];
  QString aQStack_128 [32];
  QMessageLogger local_108 [32];
  QDBusError local_e8 [64];
  undefined8 local_a8;
  QDBusPendingCallWatcher *pQStack_a0;
  QString aQStack_98 [24];
  undefined1 (*pauStack_80) [16];
  QVariant aQStack_68 [40];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QList<QDBusObjectPath>>::QDBusPendingReply
            (local_1e8,(QDBusPendingCall *)(*(long *)(this + 8) + 0x10));
  QObject::deleteLater();
  cVar2 = QDBusPendingCall::isValid();
  if (cVar2 == '\x01') {
    QDBusPendingReply<QList<QDBusObjectPath>>::value(local_188);
    cVar2 = QList<QDBusObjectPath>::isEmpty((QList<QDBusObjectPath> *)local_188);
    if (cVar2 == '\0') {
      pauVar5 = operator_new(0x30);
      *pauVar5 = (undefined1  [16])0x0;
      pauVar5[1] = (undefined1  [16])0x0;
      pauVar5[2] = (undefined1  [16])0x0;
      uVar3 = QList<QDBusObjectPath>::size((QList<QDBusObjectPath> *)local_188);
      *(undefined4 *)(pauVar5[2] + 8) = uVar3;
      pauStack_1c0 = pauVar5;
                    /* try { // try from 00257e27 to 00357e2b has its CatchHandler @ 00257c18 */
      QDBusConnection::systemBus();
      pQStack_1b8 = (QList<QDBusObjectPath> *)local_188;
      uStack_1d8 = QList<QDBusObjectPath>::begin(pQStack_1b8);
                    /* catch() { ... } // from try @ 00258688 with catch @ 00257ea0 */
      uStack_1d0 = QList<QDBusObjectPath>::end(pQStack_1b8);
                    /* try { // try from 00258230 to 00358234 has its CatchHandler @ 002585ad */
      while (cVar2 = QList<QDBusObjectPath>::const_iterator::operator!=
                               ((const_iterator *)&uStack_1d8,uStack_1d0), cVar2 != '\0') {
        uStack_1b0 = QList<QDBusObjectPath>::const_iterator::operator*
                               ((const_iterator *)&uStack_1d8);
                    /* try { // try from 00257ed0 to 00357ed4 has its CatchHandler @ 00257ea0 */
        QDBusObjectPath::path();
        pwStack_1a0 = L"GetAll";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"GetAll",6);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        QString::QString((QString *)&local_a8,FDPROPS);
                    /* try { // try from 00257f48 to 00357f4c has its CatchHandler @ 0025865c */
        pwStack_198 = L"org.freedesktop.Accounts";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
                   L"org.freedesktop.Accounts",0x18);
        QString::QString(aQStack_128,(QArrayDataPointer *)local_148);
                    /* try { // try from 00257fb2 to 00357fb6 has its CatchHandler @ 0025850b */
        QDBusMessage::createMethodCall
                  (aQStack_1c8,aQStack_128,(QString *)local_168,(QString *)&local_a8);
        QString::~QString(aQStack_128);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
        QString::~QString((QString *)&local_a8);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
        pwStack_190 = L"org.freedesktop.Accounts.User";
                    /* try { // try from 00258022 to 00358026 has its CatchHandler @ 00258648 */
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_e8,(QTypedArrayData *)0x0,
                   L"org.freedesktop.Accounts.User",0x1d);
        QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_e8);
        ::QVariant::QVariant(aQStack_68,(QString *)&local_a8);
        QDBusMessage::operator<<((QDBusMessage *)aQStack_1c8,aQStack_68);
        ::QVariant::~QVariant(aQStack_68);
                    /* try { // try from 0025808f to 00358093 has its CatchHandler @ 00258537 */
        QString::~QString((QString *)&local_a8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_e8);
        this_00 = operator_new(0x18);
        pQVar1 = *(QObject **)this;
        QDBusConnection::asyncCall((QDBusMessage *)&local_a8,(int)aQStack_1e0);
        QDBusPendingCallWatcher::QDBusPendingCallWatcher
                  (this_00,(QDBusPendingCall *)&local_a8,pQVar1);
        pQStack_1a8 = this_00;
                    /* try { // try from 0025810e to 00358112 has its CatchHandler @ 00258648 */
        QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&local_a8);
        local_a8 = *(undefined8 *)this;
        pQStack_a0 = pQStack_1a8;
        QString::QString(aQStack_98,(QString *)local_168);
        pauStack_80 = pauStack_1c0;
                    /* try { // try from 0025817b to 0035817f has its CatchHandler @ 00258572 */
        QObject::operator()(local_e8,pQStack_1a8,QDBusPendingCallWatcher::finished,0,
                            *(undefined8 *)this,&local_a8,0);
        QMetaObject::Connection::~Connection((Connection *)local_e8);
        const::{lambda()#1}::~refreshUsers((_lambda___1_ *)&local_a8);
        QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_1c8);
        QString::~QString((QString *)local_168);
        QList<QDBusObjectPath>::const_iterator::operator++((const_iterator *)&uStack_1d8);
      }
      QDBusConnection::~QDBusConnection(aQStack_1e0);
    }
    else {
      QList<QVariant>::clear((QList<QVariant> *)(*(long *)this + 0x170));
      QHash<QString,QString>::clear((QHash<QString,QString> *)(*(long *)this + 0x1a0));
      QHash<QString,unsigned_long_long>::clear
                ((QHash<QString,unsigned_long_long> *)(*(long *)this + 0x1a8));
      usersChanged(*(Lelan **)this);
      updateCurrentUserName(*(Lelan **)this);
    }
    QList<QDBusObjectPath>::~QList((QList<QDBusObjectPath> *)local_188);
  }
  else {
                    /* catch() { ... } // from try @ 00257cb1 with catch @ 00257c18
                       catch() { ... } // from try @ 00257e27 with catch @ 00257c18 */
    QMessageLogger::QMessageLogger(local_108,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)QDebug::operator<<(local_168,"[lelan] Accounts ListCachedUsers failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,local_148);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar4,aQStack_128);
    QString::~QString(aQStack_128);
    QDBusError::~QDBusError((QDBusError *)&local_a8);
    QString::~QString(local_148);
    QDBusError::~QDBusError(local_e8);
    QDebug::~QDebug(local_168);
  }
  QDBusPendingReply<QList<QDBusObjectPath>>::~QDBusPendingReply(local_1e8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* try { // try from 002582a0 to 003582a4 has its CatchHandler @ 00258648 */
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00258476  Lelan::refreshUsers

/* WARNING: Removing unreachable block (ram,0x002586c8) */
/* Lelan::refreshUsers() */

void __thiscall Lelan::refreshUsers(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QDBusConnection aQStack_170 [8];
  QString aQStack_168 [8];
  QDBusPendingCallWatcher *pQStack_160;
  wchar16 *pwStack_158;
  wchar16 *pwStack_150;
  wchar16 *pwStack_148;
  wchar16 *pwStack_140;
  QArrayDataPointer<char16_t> aQStack_138 [32];
  QString aQStack_118 [32];
  QArrayDataPointer<char16_t> aQStack_f8 [32];
  QString aQStack_d8 [32];
  QArrayDataPointer<char16_t> aQStack_b8 [32];
  QString aQStack_98 [32];
  QArrayDataPointer<char16_t> aQStack_78 [32];
  Lelan *pLStack_58;
  QDBusPendingCallWatcher *pQStack_50;
  long lStack_40;
  
  lStack_40 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  pwStack_140 = L"ListCachedUsers";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_78,(QTypedArrayData *)0x0,L"ListCachedUsers",0xf);
  QString::QString((QString *)&pLStack_58,(QArrayDataPointer *)aQStack_78);
  pwStack_148 = L"org.freedesktop.Accounts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_b8,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
  QString::QString(aQStack_98,(QArrayDataPointer *)aQStack_b8);
  pwStack_150 = L"/org/freedesktop/Accounts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_f8,(QTypedArrayData *)0x0,L"/org/freedesktop/Accounts",0x19);
  QString::QString(aQStack_d8,(QArrayDataPointer *)aQStack_f8);
  pwStack_158 = L"org.freedesktop.Accounts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_138,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
  QString::QString(aQStack_118,(QArrayDataPointer *)aQStack_138);
  QDBusMessage::createMethodCall(aQStack_168,aQStack_118,aQStack_d8,aQStack_98);
  QString::~QString(aQStack_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_138);
  QString::~QString(aQStack_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f8);
  QString::~QString(aQStack_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_b8);
  QString::~QString((QString *)&pLStack_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_78);
  this_00 = operator_new(0x18);
  QDBusConnection::asyncCall((QDBusMessage *)&pLStack_58,(int)aQStack_170);
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)&pLStack_58,(QObject *)this);
  pQStack_160 = this_00;
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)&pLStack_58);
  pQStack_50 = pQStack_160;
  pLStack_58 = this;
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::refreshUsers()::_lambda()_1_>
            (aQStack_78,pQStack_160,QDBusPendingCallWatcher::finished,0,this,&pLStack_58,0);
  QMetaObject::Connection::~Connection((Connection *)aQStack_78);
  QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_168);
  QDBusConnection::~QDBusConnection(aQStack_170);
  if (lStack_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00258868  Lelan::updateCurrentUserName

/* Lelan::updateCurrentUserName() */

void __thiscall Lelan::updateCurrentUserName(Lelan *this)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  undefined8 local_140;
  undefined8 local_138;
  QVariant local_130 [8];
  QList<QVariant> *local_128;
  undefined8 local_120;
  wchar16 *local_118;
  wchar16 *local_110;
  QString local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QDir local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
                    /* try { // try from 00258874 to 00358878 has its CatchHandler @ 00258cd5 */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 0025888d to 00358891 has its CatchHandler @ 00258cc1 */
  QDir::home(local_a8);
  QDir::dirName();
                    /* try { // try from 002588c7 to 003588cb has its CatchHandler @ 00258cad */
  qEnvironmentVariable((char *)local_108,(QString *)&DAT_002adae4);
  QString::~QString(local_88);
  QDir::~QDir(local_a8);
  QString::QString(local_e8,local_108);
  local_128 = (QList<QVariant> *)(this + 0x170);
  local_140 = QList<QVariant>::begin(local_128);
  local_138 = QList<QVariant>::end(local_128);
  while( true ) {
                    /* try { // try from 00258b81 to 00358b85 has its CatchHandler @ 00258dba */
    cVar2 = QList<QVariant>::iterator::operator!=((iterator *)&local_140,local_138);
    if (cVar2 == '\0') break;
    local_120 = QList<QVariant>::iterator::operator*((iterator *)&local_140);
                    /* try { // try from 00258971 to 00358975 has its CatchHandler @ 00258d23 */
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
                    /* try { // try from 0025898a to 0035898e has its CatchHandler @ 00258d0f */
    local_118 = L"name";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"name",4);
                    /* try { // try from 002589c4 to 003589c8 has its CatchHandler @ 00258cfb */
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,local_130);
    ::QVariant::toString();
    cVar2 = ::operator==(local_88,local_108);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    if (cVar2 == '\0') {
      bVar1 = true;
    }
    else {
                    /* try { // try from 00258a64 to 00358a68 has its CatchHandler @ 00258d71 */
      ::QVariant::QVariant(local_68);
      local_110 = L"displayName";
                    /* try { // try from 00258a7d to 00358a81 has its CatchHandler @ 00258d5d */
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_a8,(QTypedArrayData *)0x0,L"displayName",0xb);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
                    /* try { // try from 00258aab to 00358aaf has its CatchHandler @ 00258d49 */
      QMap<QString,QVariant>::value(local_48,local_130);
      ::QVariant::toString();
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_a8);
      ::QVariant::~QVariant(local_68);
      cVar2 = QString::isEmpty((QString *)local_c8);
                    /* try { // try from 00258b1e to 00358b22 has its CatchHandler @ 00258e18 */
      if (cVar2 != '\x01') {
        QString::operator=(local_e8,(QString *)local_c8);
      }
      QString::~QString((QString *)local_c8);
      bVar1 = false;
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_130);
    if (!bVar1) break;
    QList<QVariant>::iterator::operator++((iterator *)&local_140);
  }
                    /* try { // try from 00258ba6 to 00358baa has its CatchHandler @ 00258d97 */
  cVar2 = ::operator!=(local_e8,(QString *)(this + 0x188));
  if (cVar2 != '\0') {
    QString::operator=((QString *)(this + 0x188),local_e8);
    userNameChanged(this);
  }
  QString::~QString(local_e8);
  QString::~QString(local_108);
                    /* try { // try from 00258c14 to 00358c18 has its CatchHandler @ 00258e29 */
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00258d40  Lelan::addUser(QString_const&,QString_const&,bool)::{lambda()#1}::operator()

/* Lelan::addUser(QString const&, QString const&, bool)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const */

void __thiscall
Lelan::addUser(QString_const&,QString_const&,bool)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshUsers(*(Lelan **)this);
  return;
}



// ==== 00258d5e  Lelan::addUser

/* Lelan::addUser(QString const&, QString const&, bool) */

void __thiscall Lelan::addUser(Lelan *this,QString *param_1,QString *param_2,bool param_3)

{
  QDBusMessage *pQVar1;
  long in_FS_OFFSET;
  QString local_1b0 [8];
  wchar16 *local_1a8;
  wchar16 *local_1a0;
  wchar16 *local_198;
  wchar16 *local_190;
  QArrayDataPointer<char16_t> local_188 [32];
  QString local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  Lelan *local_a8 [4];
  QVariant local_88 [32];
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
                    /* catch() { ... } // from try @ 00258a64 with catch @ 00258d71 */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* catch() { ... } // from try @ 00258ba6 with catch @ 00258d97 */
  local_190 = L"CreateUser";
                    /* catch() { ... } // from try @ 00258b81 with catch @ 00258dba */
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"CreateUser",10);
  QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
  local_198 = L"org.freedesktop.Accounts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
                    /* catch() { ... } // from try @ 00258b1e with catch @ 00258e18 */
  QString::QString(local_e8,(QArrayDataPointer *)local_108);
                    /* catch() { ... } // from try @ 00258c14 with catch @ 00258e29 */
  local_1a0 = L"/org/freedesktop/Accounts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_148,(QTypedArrayData *)0x0,L"/org/freedesktop/Accounts",0x19);
                    /* try { // try from 00258e64 to 00358e68 has its CatchHandler @ 002586d2 */
  QString::QString(local_128,(QArrayDataPointer *)local_148);
  local_1a8 = L"org.freedesktop.Accounts";
                    /* catch() { ... } // from try @ 0025914f with catch @ 00258e7e */
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_188,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
  QString::QString(local_168,(QArrayDataPointer *)local_188);
  QDBusMessage::createMethodCall(local_1b0,local_168,local_128,local_e8);
  QString::~QString(local_168);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_188);
                    /* try { // try from 00258f09 to 00358f0d has its CatchHandler @ 00259159 */
  QString::~QString(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  QString::~QString(local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QString::~QString((QString *)local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
  ::QVariant::QVariant(local_88,param_1);
  pQVar1 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)local_1b0,local_88);
                    /* try { // try from 00258f89 to 00358f8d has its CatchHandler @ 00259193 */
  ::QVariant::QVariant(local_68,param_2);
  pQVar1 = (QDBusMessage *)QDBusMessage::operator<<(pQVar1,local_68);
  ::QVariant::QVariant(local_48,(uint)param_3);
  QDBusMessage::operator<<(pQVar1,local_48);
  ::QVariant::~QVariant(local_48);
  ::QVariant::~QVariant(local_68);
  ::QVariant::~QVariant(local_88);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)local_a8,(int)local_c8);
                    /* try { // try from 0025903f to 00359043 has its CatchHandler @ 00259224 */
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_a8);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_c8);
  local_a8[0] = this;
  QTimer::singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::_lambda()_1_>
            (600,(ContextType *)this,(_lambda___1_ *)local_a8);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_1b0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002591c0  Lelan::removeUser(QString_const&)::{lambda()#1}::operator()

/* Lelan::removeUser(QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Lelan::removeUser(QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshUsers(*(Lelan **)this);
  return;
}



// ==== 002591de  Lelan::removeUser

/* Lelan::removeUser(QString const&) */

void __thiscall Lelan::removeUser(Lelan *this,QString *param_1)

{
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  QString aQStack_198 [8];
  long lStack_190;
  wchar16 *pwStack_188;
  wchar16 *pwStack_180;
  wchar16 *pwStack_178;
  wchar16 *pwStack_170;
  QArrayDataPointer<char16_t> aQStack_168 [32];
  QString aQStack_148 [32];
  QArrayDataPointer<char16_t> aQStack_128 [32];
  QString aQStack_108 [32];
  QArrayDataPointer<char16_t> aQStack_e8 [32];
  QString aQStack_c8 [32];
  QArrayDataPointer<char16_t> aQStack_a8 [32];
  Lelan *apLStack_88 [4];
  QVariant aQStack_68 [32];
  QVariant aQStack_48 [40];
  long lStack_20;
  
                    /* catch() { ... } // from try @ 002590c0 with catch @ 002591de */
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  apLStack_88[0] = (Lelan *)0x0;
  lStack_190 = QHash<QString,unsigned_long_long>::value
                         ((QHash<QString,unsigned_long_long> *)(this + 0x1a8),param_1,
                          (ulonglong *)apLStack_88);
  if (lStack_190 != 0) {
    pwStack_170 = L"DeleteUser";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_a8,(QTypedArrayData *)0x0,L"DeleteUser",10);
    QString::QString((QString *)apLStack_88,(QArrayDataPointer *)aQStack_a8);
    pwStack_178 = L"org.freedesktop.Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_e8,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
    QString::QString(aQStack_c8,(QArrayDataPointer *)aQStack_e8);
    pwStack_180 = L"/org/freedesktop/Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_128,(QTypedArrayData *)0x0,L"/org/freedesktop/Accounts",0x19);
    QString::QString(aQStack_108,(QArrayDataPointer *)aQStack_128);
    pwStack_188 = L"org.freedesktop.Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_168,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
    QString::QString(aQStack_148,(QArrayDataPointer *)aQStack_168);
    QDBusMessage::createMethodCall(aQStack_198,aQStack_148,aQStack_108,aQStack_c8);
    QString::~QString(aQStack_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_168);
    QString::~QString(aQStack_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
    QString::~QString(aQStack_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e8);
    QString::~QString((QString *)apLStack_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_a8);
    ::QVariant::QVariant(aQStack_68,lStack_190);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)aQStack_198,aQStack_68);
    ::QVariant::QVariant(aQStack_48,false);
    QDBusMessage::operator<<(this_00,aQStack_48);
    ::QVariant::~QVariant(aQStack_48);
    ::QVariant::~QVariant(aQStack_68);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)apLStack_88,(int)aQStack_a8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)apLStack_88);
    QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_a8);
    apLStack_88[0] = this;
    QTimer::singleShot<int,Lelan::removeUser(QString_const&)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)apLStack_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_198);
  }
  if (lStack_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00259602  Lelan::setUserAdmin(QString_const&,bool)::{lambda()#1}::operator()

/* Lelan::setUserAdmin(QString const&, bool)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Lelan::setUserAdmin(QString_const&,bool)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshUsers(*(Lelan **)this);
  return;
}



// ==== 00259620  Lelan::setUserAdmin

/* Lelan::setUserAdmin(QString const&, bool) */

void __thiscall Lelan::setUserAdmin(Lelan *this,QString *param_1,bool param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  QString aQStack_148 [8];
  wchar16 *pwStack_140;
  wchar16 *pwStack_138;
  undefined *puStack_130;
  QString aQStack_128 [32];
  QArrayDataPointer<char16_t> aQStack_108 [32];
  QString aQStack_e8 [32];
  QArrayDataPointer<char16_t> aQStack_c8 [32];
  QString aQStack_a8 [32];
  QArrayDataPointer<char16_t> aQStack_88 [32];
  Lelan *apLStack_68 [4];
  QVariant aQStack_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(aQStack_128);
  cVar1 = QString::isEmpty(aQStack_128);
  if (cVar1 == '\0') {
    puStack_130 = &UNK_002adb1a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_88,(QTypedArrayData *)0x0,L"SetAccountType",0xe);
    QString::QString((QString *)apLStack_68,(QArrayDataPointer *)aQStack_88);
    pwStack_138 = L"org.freedesktop.Accounts.User";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_c8,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts.User",0x1d);
    QString::QString(aQStack_a8,(QArrayDataPointer *)aQStack_c8);
    pwStack_140 = L"org.freedesktop.Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_108,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
    QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_108);
    QDBusMessage::createMethodCall(aQStack_148,aQStack_e8,aQStack_128,aQStack_a8);
    QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_108);
    QString::~QString(aQStack_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_c8);
    QString::~QString((QString *)apLStack_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_88);
    ::QVariant::QVariant(aQStack_48,(uint)param_2);
    QDBusMessage::operator<<((QDBusMessage *)aQStack_148,aQStack_48);
    ::QVariant::~QVariant(aQStack_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)apLStack_68,(int)aQStack_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)apLStack_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_88);
    apLStack_68[0] = this;
    QTimer::singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)apLStack_68);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_148);
  }
  QString::~QString(aQStack_128);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0025998a  Lelan::setAutoLogin(QString_const&,bool)::{lambda()#1}::operator()

/* Lelan::setAutoLogin(QString const&, bool)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Lelan::setAutoLogin(QString_const&,bool)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  refreshUsers(*(Lelan **)this);
  return;
}



// ==== 002599a8  Lelan::setAutoLogin

/* Lelan::setAutoLogin(QString const&, bool) */

void __thiscall Lelan::setAutoLogin(Lelan *this,QString *param_1,bool param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  QString aQStack_148 [8];
  wchar16 *pwStack_140;
  wchar16 *pwStack_138;
  wchar16 *local_130;
  QString local_128 [32];
  QArrayDataPointer<char16_t> aQStack_108 [32];
  QString aQStack_e8 [32];
  QArrayDataPointer<char16_t> aQStack_c8 [32];
  QString aQStack_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  Lelan *apLStack_68 [4];
  QVariant aQStack_48 [40];
  long local_20;
  
                    /* try { // try from 002599b9 to 003599bd has its CatchHandler @ 00259b52 */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(local_128);
  cVar1 = QString::isEmpty(local_128);
  if (cVar1 == '\0') {
    local_130 = L"SetAutomaticLogin";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_88,(QTypedArrayData *)0x0,L"SetAutomaticLogin",0x11);
    QString::QString((QString *)apLStack_68,(QArrayDataPointer *)local_88);
    pwStack_138 = L"org.freedesktop.Accounts.User";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_c8,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts.User",0x1d);
    QString::QString(aQStack_a8,(QArrayDataPointer *)aQStack_c8);
    pwStack_140 = L"org.freedesktop.Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_108,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
    QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_108);
    QDBusMessage::createMethodCall(aQStack_148,aQStack_e8,local_128,aQStack_a8);
    QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_108);
    QString::~QString(aQStack_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_c8);
    QString::~QString((QString *)apLStack_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::QVariant(aQStack_48,param_2);
    QDBusMessage::operator<<((QDBusMessage *)aQStack_148,aQStack_48);
    ::QVariant::~QVariant(aQStack_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)apLStack_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)apLStack_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    apLStack_68[0] = this;
    QTimer::singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)apLStack_68);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_148);
  }
  QString::~QString(local_128);
                    /* catch() { ... } // from try @ 00259e16 with catch @ 00259c38 */
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
                    /* try { // try from 00259d01 to 00359d05 has its CatchHandler @ 00259c38 */
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00259d04  Lelan::setUserAvatar(QString_const&,QString_const&)::{lambda()#1}::operator()

/* Lelan::setUserAvatar(QString const&, QString const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE()
   const */

void __thiscall
Lelan::setUserAvatar(QString_const&,QString_const&)::{lambda()#1}::operator()(_lambda___1_ *this)

{
                    /* try { // try from 00259d10 to 00359d14 has its CatchHandler @ 00259e49 */
  refreshUsers(*(Lelan **)this);
  return;
}



// ==== 00259d22  Lelan::setUserAvatar

/* Lelan::setUserAvatar(QString const&, QString const&) */

void __thiscall Lelan::setUserAvatar(Lelan *this,QString *param_1,QString *param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  QString aQStack_180 [8];
  wchar16 *pwStack_178;
  wchar16 *pwStack_170;
  wchar16 *pwStack_168;
  wchar16 *pwStack_160;
  QString local_158 [32];
  QString aQStack_138 [32];
  QArrayDataPointer<char16_t> aQStack_118 [32];
  QString aQStack_f8 [32];
  QLatin1Char aQStack_d8 [32];
  undefined2 auStack_b8 [16];
  QArrayDataPointer<char16_t> aQStack_98 [32];
  Lelan *apLStack_78 [4];
  QVariant aQStack_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 00259d68 to 00359d6c has its CatchHandler @ 00259e2c */
  QHash<QString,QString>::value(local_158);
  cVar1 = QString::isEmpty(local_158);
  if (cVar1 == '\0') {
    QLatin1Char::QLatin1Char(aQStack_d8,'/');
    QChar::QChar<QLatin1Char,true>((QChar *)auStack_b8,aQStack_d8[0]);
    cVar1 = QString::startsWith(param_2,auStack_b8[0],1);
    if (cVar1 == '\0') {
      pwStack_178 = L"/usr/share/ncde/";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_98,(QTypedArrayData *)0x0,L"/usr/share/ncde/",0x10);
      QString::QString((QString *)apLStack_78,(QArrayDataPointer *)aQStack_98);
      ::operator+(aQStack_138,(QString *)apLStack_78);
      QString::~QString((QString *)apLStack_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_98);
    }
    else {
      QString::QString(aQStack_138,param_2);
    }
    pwStack_160 = L"SetIconFile";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_98,(QTypedArrayData *)0x0,L"SetIconFile",0xb);
    QString::QString((QString *)apLStack_78,(QArrayDataPointer *)aQStack_98);
    pwStack_168 = L"org.freedesktop.Accounts.User";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)aQStack_d8,(QTypedArrayData *)0x0,
               L"org.freedesktop.Accounts.User",0x1d);
    QString::QString((QString *)auStack_b8,(QArrayDataPointer *)aQStack_d8);
    pwStack_170 = L"org.freedesktop.Accounts";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_118,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
    QString::QString(aQStack_f8,(QArrayDataPointer *)aQStack_118);
    QDBusMessage::createMethodCall(aQStack_180,aQStack_f8,local_158,(QString *)auStack_b8);
    QString::~QString(aQStack_f8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_118);
    QString::~QString((QString *)auStack_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aQStack_d8);
    QString::~QString((QString *)apLStack_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_98);
    ::QVariant::QVariant(aQStack_58,aQStack_138);
    QDBusMessage::operator<<((QDBusMessage *)aQStack_180,aQStack_58);
    ::QVariant::~QVariant(aQStack_58);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)apLStack_78,(int)aQStack_98);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)apLStack_78);
    QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_98);
    apLStack_78[0] = this;
    QTimer::singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::_lambda()_1_>
              (600,(ContextType *)this,(_lambda___1_ *)apLStack_78);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_180);
    QString::~QString(aQStack_138);
  }
  QString::~QString(local_158);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0025a1fc  Lelan::changePassword

/* Lelan::changePassword(QString const&, QString const&) */

void Lelan::changePassword(QString *param_1,QString *param_2)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  QRandomGenerator *this;
  char *__salt;
  char *__key;
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  int iStack_194;
  char *pcStack_190;
  QString aQStack_188 [8];
  wchar16 *pwStack_180;
  wchar16 *pwStack_178;
  wchar16 *pwStack_170;
  QString aQStack_168 [32];
  QByteArray aQStack_148 [32];
  QArrayDataPointer<char16_t> aQStack_128 [32];
  QString aQStack_108 [32];
  QArrayDataPointer<char16_t> aQStack_e8 [32];
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  QArrayDataPointer<char16_t> aQStack_a8 [32];
  QString aQStack_88 [32];
  QVariant aQStack_68 [32];
  QVariant aQStack_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QString>::value(aQStack_168);
  cVar2 = QString::isEmpty(aQStack_168);
  if (cVar2 == '\0') {
    QByteArray::QByteArray(aQStack_148,"$6$",-1);
    for (iStack_194 = 0; puVar1 = changePassword(QString_const&,QString_const&)::b64,
        iStack_194 < 0x10; iStack_194 = iStack_194 + 1) {
      this = (QRandomGenerator *)QRandomGenerator::system();
      iVar3 = QRandomGenerator::bounded(this,0x40);
      QByteArray::operator+=(aQStack_148,puVar1[iVar3]);
    }
    QByteArray::operator+=(aQStack_148,'$');
    __salt = (char *)QByteArray::constData(aQStack_148);
    QString::toUtf8(aQStack_88);
    __key = (char *)QByteArray::constData((QByteArray *)aQStack_88);
    pcStack_190 = crypt(__key,__salt);
    QByteArray::~QByteArray((QByteArray *)aQStack_88);
    if (pcStack_190 != (char *)0x0) {
      pwStack_170 = L"SetPassword";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_a8,(QTypedArrayData *)0x0,L"SetPassword",0xb);
      QString::QString(aQStack_88,(QArrayDataPointer *)aQStack_a8);
      pwStack_178 = L"org.freedesktop.Accounts.User";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_e8,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts.User",0x1d);
      QString::QString((QString *)&uStack_c8,(QArrayDataPointer *)aQStack_e8);
      pwStack_180 = L"org.freedesktop.Accounts";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_128,(QTypedArrayData *)0x0,L"org.freedesktop.Accounts",0x18);
      QString::QString(aQStack_108,(QArrayDataPointer *)aQStack_128);
      QDBusMessage::createMethodCall(aQStack_188,aQStack_108,aQStack_168,(QString *)&uStack_c8);
      QString::~QString(aQStack_108);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_128);
      QString::~QString((QString *)&uStack_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e8);
      QString::~QString(aQStack_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_a8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&uStack_c8,&pcStack_190);
      QString::fromUtf8(aQStack_a8,uStack_c8,uStack_c0);
      ::QVariant::QVariant(aQStack_68,(QString *)aQStack_a8);
      this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)aQStack_188,aQStack_68);
      QString::QString(aQStack_88);
      ::QVariant::QVariant(aQStack_48,aQStack_88);
      QDBusMessage::operator<<(this_00,aQStack_48);
      ::QVariant::~QVariant(aQStack_48);
      QString::~QString(aQStack_88);
      ::QVariant::~QVariant(aQStack_68);
      QString::~QString((QString *)aQStack_a8);
      QDBusConnection::systemBus();
      QDBusConnection::asyncCall((QDBusMessage *)aQStack_88,(int)aQStack_a8);
      QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)aQStack_88);
      QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_a8);
      QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_188);
    }
    QByteArray::~QByteArray(aQStack_148);
  }
  QString::~QString(aQStack_168);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0025a732  Lelan::onBlueZInterfacesAdded

/* Lelan::onBlueZInterfacesAdded(QDBusObjectPath const&, QMap<QString, QMap<QString, QVariant> >
   const&) */

void Lelan::onBlueZInterfacesAdded(QDBusObjectPath *param_1,QMap *param_2)

{
  rebuildBluetooth((Lelan *)param_1);
  return;
}



// ==== 0025a756  Lelan::onBlueZInterfacesRemoved

/* Lelan::onBlueZInterfacesRemoved(QDBusObjectPath const&, QList<QString> const&) */

void Lelan::onBlueZInterfacesRemoved(QDBusObjectPath *param_1,QList *param_2)

{
  rebuildBluetooth((Lelan *)param_1);
  return;
}



// ==== 0025a77a  Lelan::onBlueZPropertiesChanged

/* Lelan::onBlueZPropertiesChanged(QString const&, QMap<QString, QVariant> const&, QList<QString>
   const&) */

void Lelan::onBlueZPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  char cVar1;
  int iVar2;
  QString *pQVar3;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_208 [32];
  QArrayDataPointer<char16_t> local_1e8 [32];
  QArrayDataPointer<char16_t> aQStack_1c8 [32];
  QArrayDataPointer<char16_t> aQStack_1a8 [32];
  QArrayDataPointer<char16_t> aQStack_188 [32];
  QArrayDataPointer<char16_t> aQStack_168 [32];
  undefined8 local_148 [4];
  undefined8 local_128;
  undefined8 local_120;
  QString local_108 [24];
  QString aQStack_f0 [24];
  QString aQStack_d8 [24];
  QString aQStack_c0 [24];
  QString aQStack_a8 [24];
  QString aQStack_90 [24];
  QString aQStack_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QLatin1String::QLatin1String((QLatin1String *)&local_128,"org.bluez.");
  cVar1 = QString::startsWith(param_2,local_128,local_120,1);
  if (cVar1 == '\x01') {
    if ((onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
         ::kRelevant == '\0') &&
       (iVar2 = __cxa_guard_acquire(&onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
                                     ::kRelevant), iVar2 != 0)) {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_208,(QTypedArrayData *)0x0,L"Powered",7);
      QString::QString(local_108,(QArrayDataPointer *)local_208);
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_1e8,(QTypedArrayData *)0x0,L"Discoverable",0xc);
      QString::QString(aQStack_f0,(QArrayDataPointer *)local_1e8);
      QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1c8,(QTypedArrayData *)0x0,L"Name",4);
      QString::QString(aQStack_d8,(QArrayDataPointer *)aQStack_1c8);
      QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1a8,(QTypedArrayData *)0x0,L"Alias",5);
      QString::QString(aQStack_c0,(QArrayDataPointer *)aQStack_1a8);
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_188,(QTypedArrayData *)0x0,L"Address",7);
      QString::QString(aQStack_a8,(QArrayDataPointer *)aQStack_188);
      QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_168,(QTypedArrayData *)0x0,L"Icon",4);
      QString::QString(aQStack_90,(QArrayDataPointer *)aQStack_168);
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"Paired",6);
      QString::QString(aQStack_78,(QArrayDataPointer *)local_148);
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_128,(QTypedArrayData *)0x0,L"Connected",9);
      QString::QString(aQStack_60,(QArrayDataPointer *)&local_128);
      QSet<QString>::QSet(&onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
                           ::kRelevant,local_108,8);
      __cxa_atexit(QSet<QString>::~QSet,
                   &onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
                    ::kRelevant,&__dso_handle);
      __cxa_guard_release(&onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
                           ::kRelevant);
      pQVar3 = aQStack_48;
      while (pQVar3 != local_108) {
        pQVar3 = pQVar3 + -0x18;
        QString::~QString(pQVar3);
      }
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_128);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_168);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_188);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1e8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_208);
    }
    local_148[0] = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)param_3);
                    /* catch() { ... } // from try @ 0025aa01 with catch @ 0025ab91 */
    while( true ) {
                    /* catch() { ... } // from try @ 0025ab4c with catch @ 0025abed */
      local_128 = QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)param_3);
      cVar1 = ::operator!=((const_iterator *)local_148,(const_iterator *)&local_128);
      if (cVar1 == '\0') break;
      pQVar3 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_148);
                    /* catch() { ... } // from try @ 0025aa8a with catch @ 0025aba9 */
                    /* catch() { ... } // from try @ 0025aa74 with catch @ 0025abba */
      cVar1 = QSet<QString>::contains
                        ((QSet<QString> *)
                         &onBlueZPropertiesChanged(QString_const&,QMap<QString,QVariant>const&,QList<QString>const&)
                          ::kRelevant,pQVar3);
      if (cVar1 != '\0') {
                    /* catch() { ... } // from try @ 0025aaf3 with catch @ 0025abcb */
        rebuildBluetooth((Lelan *)param_1);
        break;
      }
                    /* catch() { ... } // from try @ 0025aadd with catch @ 0025abdc */
      QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_148);
    }
  }
                    /* try { // try from 0025ad36 to 0035ad3a has its CatchHandler @ 0025ae90 */
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
                    /* try { // try from 0025ad4b to 0035ad4f has its CatchHandler @ 0025ae4c */
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0025ad5a  Lelan::onUDisks2InterfacesAdded

/* Lelan::onUDisks2InterfacesAdded(QDBusObjectPath const&, QMap<QString, QMap<QString, QVariant> >
   const&) */

void Lelan::onUDisks2InterfacesAdded(QDBusObjectPath *param_1,QMap *param_2)

{
  refreshRemovableVolumes((Lelan *)param_1);
  return;
}



// ==== 0025ad7e  Lelan::onUDisks2InterfacesRemoved

/* Lelan::onUDisks2InterfacesRemoved(QDBusObjectPath const&, QList<QString> const&) */

void Lelan::onUDisks2InterfacesRemoved(QDBusObjectPath *param_1,QList *param_2)

{
                    /* try { // try from 0025ad82 to 0035ad86 has its CatchHandler @ 0025ae5d */
  refreshRemovableVolumes((Lelan *)param_1);
  return;
}



// ==== 0025ada2  Lelan::onUDisks2FilesystemPropertiesChanged

/* Lelan::onUDisks2FilesystemPropertiesChanged(QString const&, QMap<QString, QVariant> const&,
   QList<QString> const&) */

void Lelan::onUDisks2FilesystemPropertiesChanged(QString *param_1,QMap *param_2,QList *param_3)

{
  diskMountChanged((Lelan *)param_1);
  refreshRemovableVolumes((Lelan *)param_1);
  return;
}



// ==== 00261276  Lelan::subscribeToKickassGuard

/* Lelan::subscribeToKickassGuard() */

void __thiscall Lelan::subscribeToKickassGuard(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_80 [8];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
                    /* try { // try from 0026127a to 0036127e has its CatchHandler @ 002613fd */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 00261298 to 0036129c has its CatchHandler @ 002613e9 */
  QDBusConnection::sessionBus();
                    /* try { // try from 002612ab to 003612af has its CatchHandler @ 002613d8 */
  QString::QString(local_78,"org.ncde.KickassGuard");
  QString::QString(local_58,"/org/ncde/KickassGuard");
  QString::QString(local_38,"StatusChanged");
  QDBusConnection::connect(local_80,local_78,local_58,local_78,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"ThreatBlocked");
  QDBusConnection::connect(local_80,local_78,local_58,local_78,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"ThreatBehavioral");
  QDBusConnection::connect(local_80,local_78,local_58,local_78,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"SiteBlocked");
  QDBusConnection::connect(local_80,local_78,local_58,local_78,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"NetworkAlert");
  QDBusConnection::connect(local_80,local_78,local_58,local_78,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::~QString(local_58);
  QString::~QString(local_78);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_80);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00261574  Lelan::onKickassStatusChanged

/* Lelan::onKickassStatusChanged(bool, int) */

void __thiscall Lelan::onKickassStatusChanged(Lelan *this,bool param_1,int param_2)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
                    /* try { // try from 00261578 to 0036157c has its CatchHandler @ 00261703 */
                    /* try { // try from 0026158b to 0036158f has its CatchHandler @ 002616ae */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_48,param_1);
                    /* try { // try from 002615b6 to 003615d4 has its CatchHandler @ 002616f2 */
  QString::QString(local_68,"armed");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1e8),local_68);
                    /* try { // try from 002615e3 to 003615e7 has its CatchHandler @ 002616e1 */
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
                    /* try { // try from 002615fb to 003615ff has its CatchHandler @ 002616d0 */
  ::QVariant::~QVariant(local_48);
                    /* try { // try from 0026160e to 00361612 has its CatchHandler @ 002616bf */
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"level");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x1e8),local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  kickassStatusChanged(this);
  kickassChanged(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00261726  Lelan::onKickassThreatBlocked

/* Lelan::onKickassThreatBlocked(QString const&, QString const&, int) */

void Lelan::onKickassThreatBlocked(QString *param_1,QString *param_2,int param_3)

{
  int in_ECX;
  undefined4 in_register_00000014;
  
  kickassThreatBlocked
            ((Lelan *)param_1,param_2,(QString *)CONCAT44(in_register_00000014,param_3),in_ECX);
  return;
}



// ==== 00261758  Lelan::onKickassThreatBehavioral

/* Lelan::onKickassThreatBehavioral(QString const&, QString const&, QString const&) */

void __thiscall
Lelan::onKickassThreatBehavioral(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
                    /* try { // try from 00261782 to 00361786 has its CatchHandler @ 0026179d */
  kickassThreatBehavioral(this,param_1,param_2,param_3);
  return;
}



// ==== 0026178c  Lelan::onKickassSiteBlocked

/* Lelan::onKickassSiteBlocked(QString const&, QString const&) */

void Lelan::onKickassSiteBlocked(QString *param_1,QString *param_2)

{
  QString *in_RDX;
  
  kickassSiteBlocked((Lelan *)param_1,param_2,in_RDX);
  return;
}



// ==== 002617ba  Lelan::onKickassNetworkAlert

/* Lelan::onKickassNetworkAlert(QString const&, QString const&) */

void __thiscall Lelan::onKickassNetworkAlert(Lelan *this,QString *param_1,QString *param_2)

{
  kickassNetworkAlert(this,param_1,param_2);
  kickassChanged(this);
  return;
}



// ==== 002617f4  Lelan::subscribeToSentinel

/* Lelan::subscribeToSentinel() */

void __thiscall Lelan::subscribeToSentinel(Lelan *this)

{
  long in_FS_OFFSET;
  QString local_a0 [8];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusConnection::systemBus();
  QString::QString(local_98,"io.ncde.Sentinel");
  QString::QString(local_78,"/io/ncde/Sentinel");
  QString::QString(local_58,"io.ncde.Sentinel");
  QString::QString(local_38,"DisplayConnected");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"DisplayDisconnected");
                    /* catch() { ... } // from try @ 00261a46 with catch @ 002618fc
                       catch() { ... } // from try @ 00261a89 with catch @ 002618fc */
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"UsbDeviceAdded");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"UsbDeviceRemoved");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"InputDeviceAdded");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"InputDeviceRemoved");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"AudioDeviceChanged");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"BatteryStateChanged");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"NetworkStateChanged");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"ThermalChanged");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"FanChanged");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"ThermalCritical");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  QString::QString(local_38,"DriverMissing");
  QDBusConnection::connect(local_a0,local_98,local_78,local_58,(QObject *)local_38,(char *)this);
  QString::~QString(local_38);
  fetchHardwareTier(this);
  QString::~QString(local_58);
  QString::~QString(local_78);
  QString::~QString(local_98);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00261eec  Lelan::fetchHardwareTier()::{lambda(QDBusPendingCallWatcher*)#1}::operator()

/* Lelan::fetchHardwareTier()::{lambda(QDBusPendingCallWatcher*)#1}::TEMPNAMEPLACEHOLDERVALUE(QDBusPendingCallWatcher*)
   const */

void __thiscall
Lelan::fetchHardwareTier()::{lambda(QDBusPendingCallWatcher*)#1}::operator()
          (_lambda_QDBusPendingCallWatcher___1_ *this,QDBusPendingCallWatcher *param_1)

{
  Lelan *this_00;
  char cVar1;
  QDebug *pQVar2;
  long in_FS_OFFSET;
  QDBusPendingReply<QString> local_118 [8];
  QDebug local_110 [8];
  QString local_108 [32];
  QString local_e8 [32];
  QMessageLogger local_c8 [32];
  QDBusError local_a8 [64];
  QDBusPendingReply<QString> local_68 [72];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusPendingReply<QString>::QDBusPendingReply(local_118,(QDBusPendingCall *)(param_1 + 0x10));
  cVar1 = QDBusPendingCall::isError();
  if (cVar1 == '\x01') {
    QMessageLogger::QMessageLogger(local_c8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar2 = (QDebug *)QDebug::operator<<(local_110,"[lelan] Sentinel GetHardwareTier failed:");
    QDBusPendingCall::error();
    QDBusError::name();
    pQVar2 = (QDebug *)QDebug::operator<<(pQVar2,local_108);
    QDBusPendingCall::error();
    QDBusError::message();
    QDebug::operator<<(pQVar2,local_e8);
    QString::~QString(local_e8);
    QDBusError::~QDBusError((QDBusError *)local_68);
    QString::~QString(local_108);
    QDBusError::~QDBusError(local_a8);
    QDebug::~QDebug(local_110);
  }
  else {
    this_00 = *(Lelan **)this;
    QDBusPendingReply<QString>::value(local_68);
    onHardwareTierReceived(this_00,(QString *)local_68);
    QString::~QString((QString *)local_68);
  }
  QObject::deleteLater();
  QDBusPendingReply<QString>::~QDBusPendingReply(local_118);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0026218e  Lelan::fetchHardwareTier

/* WARNING: Removing unreachable block (ram,0x002623ca) */
/* Lelan::fetchHardwareTier() */

void __thiscall Lelan::fetchHardwareTier(Lelan *this)

{
  QDBusPendingCallWatcher *this_00;
  long in_FS_OFFSET;
  QString local_158 [8];
  QDBusPendingCallWatcher *local_150;
  wchar16 *local_148;
  wchar16 *local_140;
  wchar16 *local_138;
  wchar16 *local_130;
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  Lelan *local_68 [4];
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_130 = L"GetHardwareTier";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_68,(QTypedArrayData *)0x0,L"GetHardwareTier",0xf);
  QString::QString(local_48,(QArrayDataPointer *)local_68);
  local_138 = L"io.ncde.Sentinel";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  local_140 = L"/io/ncde/Sentinel";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_e8,(QTypedArrayData *)0x0,L"/io/ncde/Sentinel",0x11);
  QString::QString(local_c8,(QArrayDataPointer *)local_e8);
  local_148 = L"io.ncde.Sentinel";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_128,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
                    /* catch() { ... } // from try @ 00262404 with catch @ 002622b2 */
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QDBusMessage::createMethodCall(local_158,local_108,local_c8,local_88);
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  QString::~QString(local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  QString::~QString(local_88);
                    /* try { // try from 00262344 to 00362348 has its CatchHandler @ 002623c0 */
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  QString::~QString(local_48);
                    /* try { // try from 00262355 to 00362359 has its CatchHandler @ 002623af */
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_68);
  QDBusConnection::systemBus();
  QDBusConnection::asyncCall((QDBusMessage *)local_88,(int)local_48);
  QDBusConnection::~QDBusConnection((QDBusConnection *)local_48);
  this_00 = operator_new(0x18);
                    /* catch() { ... } // from try @ 00262355 with catch @ 002623af */
  QDBusPendingCallWatcher::QDBusPendingCallWatcher
            (this_00,(QDBusPendingCall *)local_88,(QObject *)this);
                    /* catch() { ... } // from try @ 00262344 with catch @ 002623c0 */
  local_150 = this_00;
  local_68[0] = this;
                    /* try { // try from 00262404 to 00362408 has its CatchHandler @ 002622b2 */
                    /* catch() { ... } // from try @ 0026255d with catch @ 00262414 */
  QObject::
  connect<void(QDBusPendingCallWatcher::*)(QDBusPendingCallWatcher*),Lelan::fetchHardwareTier()::_lambda(QDBusPendingCallWatcher*)_1_>
            (local_48,this_00,QDBusPendingCallWatcher::finished,0,this,local_68,0);
  QMetaObject::Connection::~Connection((Connection *)local_48);
  QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_88);
  QDBusMessage::~QDBusMessage((QDBusMessage *)local_158);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00262576  Lelan::onHardwareTierReceived

/* Lelan::onHardwareTierReceived(QString const&) */

void __thiscall Lelan::onHardwareTierReceived(Lelan *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> aQStack_48 [32];
  QString aQStack_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = ::operator==(param_1,(QString *)(this + 0x340));
  if (cVar1 == '\0') {
    QString::operator=((QString *)(this + 0x340),param_1);
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_48,(QTypedArrayData *)0x0,L"low",3);
    QString::QString(aQStack_28,(QArrayDataPointer *)aQStack_48);
    cVar1 = ::operator==(param_1,aQStack_28);
    *(uint *)(this + 0x358) = (uint)(cVar1 != '\0');
    QString::~QString(aQStack_28);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_48);
    hardwareTierChanged(this);
    recomputeAnimLevel(this);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00262680  Lelan::onSentinelDisplayConnected

/* Lelan::onSentinelDisplayConnected(QString const&) */

void Lelan::onSentinelDisplayConnected(QString *param_1)

{
  screenConfigChanged((Lelan *)param_1);
  screenGeometryChanged((Lelan *)param_1);
  return;
}



// ==== 002626ac  Lelan::onSentinelDisplayDisconnected

/* Lelan::onSentinelDisplayDisconnected(QString const&) */

void Lelan::onSentinelDisplayDisconnected(QString *param_1)

{
  screenConfigChanged((Lelan *)param_1);
  screenGeometryChanged((Lelan *)param_1);
  return;
}



// ==== 002626d8  Lelan::onSentinelUsbDeviceAdded

/* Lelan::onSentinelUsbDeviceAdded(QString const&, QString const&) */

void Lelan::onSentinelUsbDeviceAdded(QString *param_1,QString *param_2)

{
  diskDeviceChanged((Lelan *)param_1);
  storageChanged((Lelan *)param_1);
  return;
}



// ==== 00262708  Lelan::onSentinelUsbDeviceRemoved

/* Lelan::onSentinelUsbDeviceRemoved(QString const&, QString const&) */

void Lelan::onSentinelUsbDeviceRemoved(QString *param_1,QString *param_2)

{
  diskDeviceChanged((Lelan *)param_1);
  storageChanged((Lelan *)param_1);
  return;
}



// ==== 00262738  Lelan::onSentinelInputDeviceAdded

/* Lelan::onSentinelInputDeviceAdded(QString const&) */

void Lelan::onSentinelInputDeviceAdded(QString *param_1)

{
  statsChanged((Lelan *)param_1);
  return;
}



// ==== 00262758  Lelan::onSentinelInputDeviceRemoved

/* Lelan::onSentinelInputDeviceRemoved(QString const&) */

void Lelan::onSentinelInputDeviceRemoved(QString *param_1)

{
  statsChanged((Lelan *)param_1);
  return;
}



// ==== 00262778  Lelan::onSentinelAudioDeviceChanged

/* Lelan::onSentinelAudioDeviceChanged(QString const&, QString const&) */

void Lelan::onSentinelAudioDeviceChanged(QString *param_1,QString *param_2)

{
                    /* try { // try from 00262792 to 00362796 has its CatchHandler @ 002627fd */
  audioDeviceChanged((Lelan *)param_1);
  return;
}



// ==== 0026279c  Lelan::onWindowTierNeeded

/* Lelan::onWindowTierNeeded(unsigned int, QString) */

void __thiscall Lelan::onWindowTierNeeded(Lelan *this,uint param_1,QString *param_3)

{
  bool bVar1;
  char cVar2;
  QDBusMessage *this_00;
  long in_FS_OFFSET;
  QString aQStack_1b0 [8];
  wchar16 *pwStack_1a8;
  wchar16 *pwStack_1a0;
  wchar16 *pwStack_198;
  wchar16 *pwStack_190;
  wchar16 *pwStack_188;
  wchar16 *pwStack_180;
  QArrayDataPointer<char16_t> aQStack_178 [32];
  QString aQStack_158 [32];
  QArrayDataPointer<char16_t> aQStack_138 [32];
  QString aQStack_118 [32];
  QArrayDataPointer<char16_t> aQStack_f8 [32];
  QString aQStack_d8 [32];
  QArrayDataPointer<char16_t> aQStack_b8 [32];
  QString aQStack_98 [32];
  QVariant aQStack_78 [32];
  QVariant aQStack_58 [40];
  long lStack_30;
  
  lStack_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x450] == (Lelan)0x1) {
    pwStack_1a8 = L"hidden";
    QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_b8,(QTypedArrayData *)0x0,L"hidden",6);
    QString::QString(aQStack_98,(QArrayDataPointer *)aQStack_b8);
    cVar2 = ::operator==(param_3,aQStack_98);
    if ((((cVar2 == '\0') || (*(int *)(this + 0x30) == 0)) || (param_1 != *(uint *)(this + 0x30)))
       || (cVar2 = mediaPlaying(), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    QString::~QString(aQStack_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_b8);
    if (bVar1) {
      pwStack_1a0 = L"background";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_b8,(QTypedArrayData *)0x0,L"background",10);
      QString::QString(aQStack_98,(QArrayDataPointer *)aQStack_b8);
      QString::operator=(param_3,aQStack_98);
      QString::~QString(aQStack_98);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_b8);
    }
    pwStack_180 = L"SetProcessTier";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_b8,(QTypedArrayData *)0x0,L"SetProcessTier",0xe);
    QString::QString(aQStack_98,(QArrayDataPointer *)aQStack_b8);
    pwStack_188 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_f8,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(aQStack_d8,(QArrayDataPointer *)aQStack_f8);
    pwStack_190 = L"/io/ncde/Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_138,(QTypedArrayData *)0x0,L"/io/ncde/Sentinel",0x11);
    QString::QString(aQStack_118,(QArrayDataPointer *)aQStack_138);
    pwStack_198 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_178,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(aQStack_158,(QArrayDataPointer *)aQStack_178);
    QDBusMessage::createMethodCall(aQStack_1b0,aQStack_158,aQStack_118,aQStack_d8);
    QString::~QString(aQStack_158);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_178);
    QString::~QString(aQStack_118);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_138);
    QString::~QString(aQStack_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f8);
    QString::~QString(aQStack_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_b8);
    ::QVariant::QVariant(aQStack_78,param_1);
    this_00 = (QDBusMessage *)QDBusMessage::operator<<((QDBusMessage *)aQStack_1b0,aQStack_78);
    ::QVariant::QVariant(aQStack_58,param_3);
    QDBusMessage::operator<<(this_00,aQStack_58);
    ::QVariant::~QVariant(aQStack_58);
    ::QVariant::~QVariant(aQStack_78);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)aQStack_98,(int)aQStack_b8);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)aQStack_98);
    QDBusConnection::~QDBusConnection((QDBusConnection *)aQStack_b8);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_1b0);
  }
  if (lStack_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00262cf6  Lelan::onWindowClosed

/* Lelan::onWindowClosed(unsigned int) */

void __thiscall Lelan::onWindowClosed(Lelan *this,uint param_1)

{
  long in_FS_OFFSET;
  QString local_170 [8];
  wchar16 *local_168;
  wchar16 *local_160;
  wchar16 *local_158;
  wchar16 *local_150;
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((this[0x450] == (Lelan)0x1) && (param_1 != 0)) {
    local_150 = L"ClearProcessTier";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_88,(QTypedArrayData *)0x0,L"ClearProcessTier",0x10);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    local_158 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    local_160 = L"/io/ncde/Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"/io/ncde/Sentinel",0x11);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    local_168 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_148,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(local_128,(QArrayDataPointer *)local_148);
    QDBusMessage::createMethodCall(local_170,local_128,local_e8,local_a8);
    QString::~QString(local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::QVariant(local_48,param_1);
    QDBusMessage::operator<<((QDBusMessage *)local_170,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_170);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00263082  Lelan::onSentinelBatteryStateChanged

/* Lelan::onSentinelBatteryStateChanged(bool, int) */

void __thiscall Lelan::onSentinelBatteryStateChanged(Lelan *this,bool param_1,int param_2)

{
  QVariant *this_00;
  long in_FS_OFFSET;
  QString aQStack_170 [8];
  wchar16 *pwStack_168;
  wchar16 *pwStack_160;
  wchar16 *local_158;
  wchar16 *local_150;
  QArrayDataPointer<char16_t> aQStack_148 [32];
  QString aQStack_128 [32];
  QArrayDataPointer<char16_t> aQStack_108 [32];
  QString aQStack_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString aQStack_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this[0x33a] = (Lelan)param_1;
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"percentage");
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x88),local_68);
  ::QVariant::operator=(this_00,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  batteryChanged(this);
  powerChanged(this);
  recomputeAnimLevel(this);
  if (this[0x450] == (Lelan)0x1) {
    local_150 = L"SetPowerProfile";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_88,(QTypedArrayData *)0x0,L"SetPowerProfile",0xf);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    local_158 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(aQStack_a8,(QArrayDataPointer *)local_c8);
    pwStack_160 = L"/io/ncde/Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_108,(QTypedArrayData *)0x0,L"/io/ncde/Sentinel",0x11);
    QString::QString(aQStack_e8,(QArrayDataPointer *)aQStack_108);
    pwStack_168 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (aQStack_148,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(aQStack_128,(QArrayDataPointer *)aQStack_148);
    QDBusMessage::createMethodCall(aQStack_170,aQStack_128,aQStack_e8,aQStack_a8);
    QString::~QString(aQStack_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_148);
    QString::~QString(aQStack_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_108);
    QString::~QString(aQStack_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::QVariant(local_48,param_1);
    QDBusMessage::operator<<((QDBusMessage *)aQStack_170,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)aQStack_170);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 002634fa  Lelan::onSentinelNetworkStateChanged

/* Lelan::onSentinelNetworkStateChanged(QString const&, bool) */

void __thiscall Lelan::onSentinelNetworkStateChanged(Lelan *this,QString *param_1,bool param_2)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_48,param_1);
  QString::QString(local_68,"iface");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x78),local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"up");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x78),local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  networkChanged(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0026369c  Lelan::onSentinelThermalChanged

/* Lelan::onSentinelThermalChanged(QMap<QString, double> const&) */

void __thiscall Lelan::onSentinelThermalChanged(Lelan *this,QMap *param_1)

{
  char cVar1;
  double *pdVar2;
  QString *pQVar3;
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)(this + 0x378));
  local_58 = QMap<QString,double>::constBegin((QMap<QString,double> *)param_1);
  while( true ) {
    local_50 = QMap<QString,double>::constEnd((QMap<QString,double> *)param_1);
    cVar1 = ::operator!=((const_iterator *)&local_58,(const_iterator *)&local_50);
    if (cVar1 == '\0') break;
    pdVar2 = (double *)QMap<QString,double>::const_iterator::value((const_iterator *)&local_58);
    ::QVariant::QVariant(local_48,*pdVar2);
    pQVar3 = (QString *)QMap<QString,double>::const_iterator::key((const_iterator *)&local_58);
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x378),pQVar3);
    ::QVariant::operator=(this_00,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,double>::const_iterator::operator++((const_iterator *)&local_58);
  }
  sentinelTempsChanged(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002637ce  Lelan::onSentinelFanChanged

/* Lelan::onSentinelFanChanged(QMap<QString, unsigned int> const&) */

void __thiscall Lelan::onSentinelFanChanged(Lelan *this,QMap *param_1)

{
  char cVar1;
  uint *puVar2;
  QString *pQVar3;
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)(this + 0x380));
  local_58 = QMap<QString,unsigned_int>::constBegin((QMap<QString,unsigned_int> *)param_1);
  while( true ) {
    local_50 = QMap<QString,unsigned_int>::constEnd((QMap<QString,unsigned_int> *)param_1);
    cVar1 = ::operator!=((const_iterator *)&local_58,(const_iterator *)&local_50);
    if (cVar1 == '\0') break;
    puVar2 = (uint *)QMap<QString,unsigned_int>::const_iterator::value((const_iterator *)&local_58);
    ::QVariant::QVariant(local_48,*puVar2);
    pQVar3 = (QString *)QMap<QString,unsigned_int>::const_iterator::key((const_iterator *)&local_58)
    ;
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x380),pQVar3);
    ::QVariant::operator=(this_00,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,unsigned_int>::const_iterator::operator++((const_iterator *)&local_58);
  }
  sentinelFansChanged(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002638fc  Lelan::onSentinelThermalCritical

/* Lelan::onSentinelThermalCritical(QString const&, double) */

void __thiscall Lelan::onSentinelThermalCritical(Lelan *this,QString *param_1,double param_2)

{
  undefined8 uVar1;
  long in_FS_OFFSET;
  QString local_68 [32];
  QMessageLogger local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMessageLogger::QMessageLogger(local_48,(char *)0x0,0,(char *)0x0);
  QtPrivate::asString(param_1);
  QString::toUtf8(local_68);
  uVar1 = QByteArray::constData((QByteArray *)local_68);
  QMessageLogger::warning
            ((char *)local_48,param_2,"[lelan] Sentinel-reported CRITICAL: %s = %.1fC",uVar1);
  QByteArray::~QByteArray((QByteArray *)local_68);
  if (this[0x374] != (Lelan)0x1) {
    this[0x374] = (Lelan)0x1;
    updatePressure(this);
    applyThermalCap(this,true);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00263a22  Lelan::applyThermalCap

/* Lelan::applyThermalCap(bool) */

void __thiscall Lelan::applyThermalCap(Lelan *this,bool param_1)

{
  long in_FS_OFFSET;
  QString local_170 [8];
  wchar16 *local_168;
  wchar16 *local_160;
  wchar16 *local_158;
  wchar16 *local_150;
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x450] == (Lelan)0x1) {
    local_150 = L"SetThermalCap";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_88,(QTypedArrayData *)0x0,L"SetThermalCap",0xd);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    local_158 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(local_a8,(QArrayDataPointer *)local_c8);
    local_160 = L"/io/ncde/Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"/io/ncde/Sentinel",0x11);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    local_168 = L"io.ncde.Sentinel";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_148,(QTypedArrayData *)0x0,L"io.ncde.Sentinel",0x10);
    QString::QString(local_128,(QArrayDataPointer *)local_148);
    QDBusMessage::createMethodCall(local_170,local_128,local_e8,local_a8);
    QString::~QString(local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QString::~QString(local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::QVariant(local_48,param_1);
    QDBusMessage::operator<<((QDBusMessage *)local_170,local_48);
    ::QVariant::~QVariant(local_48);
    QDBusConnection::systemBus();
    QDBusConnection::asyncCall((QDBusMessage *)local_68,(int)local_88);
    QDBusPendingCall::~QDBusPendingCall((QDBusPendingCall *)local_68);
    QDBusConnection::~QDBusConnection((QDBusConnection *)local_88);
    QDBusMessage::~QDBusMessage((QDBusMessage *)local_170);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00263da2  Lelan::onSentinelDriverMissing

/* Lelan::onSentinelDriverMissing(QString const&, QString const&, QString const&) */

void __thiscall
Lelan::onSentinelDriverMissing(Lelan *this,QString *param_1,QString *param_2,QString *param_3)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char *pcVar4;
  long in_FS_OFFSET;
  QString local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  QMessageLogger local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QMessageLogger::QMessageLogger(local_58,(char *)0x0,0,(char *)0x0);
  cVar1 = QString::isEmpty(param_3);
  if (cVar1 == '\0') {
    QtPrivate::asString(param_3);
    QString::toUtf8(local_78);
    pcVar4 = (char *)QByteArray::constData((QByteArray *)local_78);
  }
  else {
    pcVar4 = "<no in-kernel module>";
  }
  QtPrivate::asString(param_2);
  QString::toUtf8(local_98);
  uVar2 = QByteArray::constData((QByteArray *)local_98);
  QtPrivate::asString(param_1);
  QString::toUtf8(local_b8);
  uVar3 = QByteArray::constData((QByteArray *)local_b8);
  QMessageLogger::info
            ((char *)local_58,"[lelan] Sentinel: driverless device %s (%s) -> %s",uVar3,uVar2,pcVar4
            );
  QByteArray::~QByteArray((QByteArray *)local_b8);
  QByteArray::~QByteArray((QByteArray *)local_98);
  if (cVar1 == '\0') {
    QByteArray::~QByteArray((QByteArray *)local_78);
  }
  driverMissing(this,param_1,param_2,param_3);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


