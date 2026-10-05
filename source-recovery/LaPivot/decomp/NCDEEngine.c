// Ghidra decompile of LaPivot.oracle — class/namespace NCDEEngine (202 functions). Raw; not source.

// ==== 00141f68  NCDEEngine::qt_static_metacall

/* NCDEEngine::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NCDEEngine::qt_static_metacall
               (NCDEEngine *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QString *pQVar1;
  bool bVar2;
  QString QVar3;
  undefined4 uVar4;
  long in_FS_OFFSET;
  undefined8 uVar5;
  undefined1 auVar6 [16];
  NCDEEngine local_68 [32];
  undefined6 local_48;
  undefined2 uStack_42;
  undefined6 local_40;
  undefined2 uStack_3a;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0x4c) {
      applyPalette(param_1,*(QMap **)(param_4 + 8));
    }
    else if (param_3 < 0x4d) {
      if (param_3 == 0x4b) {
        setAppVolume(param_1,*(QString **)(param_4 + 8),**(int **)(param_4 + 0x10));
      }
      else if (param_3 < 0x4c) {
        if (param_3 == 0x4a) {
          removePrinter(param_1,*(QString **)(param_4 + 8));
        }
        else if (param_3 < 0x4b) {
          if (param_3 == 0x49) {
            setDefaultPrinter(param_1,*(QString **)(param_4 + 8));
          }
          else if (param_3 < 0x4a) {
            if (param_3 == 0x48) {
              setUserAvatar(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10));
            }
            else if (param_3 < 0x49) {
              if (param_3 == 0x47) {
                setAutoLogin(param_1,*(QString **)(param_4 + 8),true);
              }
              else if (param_3 < 0x48) {
                if (param_3 == 0x46) {
                  setAutoLogin(param_1,*(QString **)(param_4 + 8),
                               *(bool *)*(undefined8 *)(param_4 + 0x10));
                }
                else if (param_3 < 0x47) {
                  if (param_3 == 0x45) {
                    changePassword((QString *)param_1,*(QString **)(param_4 + 8));
                  }
                  else if (param_3 < 0x46) {
                    if (param_3 == 0x44) {
                      setUserAdmin(param_1,*(QString **)(param_4 + 8),
                                   *(bool *)*(undefined8 *)(param_4 + 0x10));
                    }
                    else if (param_3 < 0x45) {
                      if (param_3 == 0x43) {
                        removeUser(param_1,*(QString **)(param_4 + 8));
                      }
                      else if (param_3 < 0x44) {
                        if (param_3 == 0x42) {
                          addUser(param_1,*(QString **)(param_4 + 8),*(QString **)(param_4 + 0x10),
                                  *(bool *)*(undefined8 *)(param_4 + 0x18));
                        }
                        else if (param_3 < 0x43) {
                          if (param_3 == 0x41) {
                            setNtp(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                          }
                          else if (param_3 < 0x42) {
                            if (param_3 == 0x40) {
                              setTimezone(param_1,*(QString **)(param_4 + 8));
                            }
                            else if (param_3 < 0x41) {
                              if (param_3 == 0x3f) {
                                refreshLocation(param_1);
                              }
                              else if (param_3 < 0x40) {
                                if (param_3 == 0x3e) {
                                  bluetoothScan(param_1);
                                }
                                else if (param_3 < 0x3f) {
                                  if (param_3 == 0x3d) {
                                    bluetoothRemove((QString *)param_1);
                                  }
                                  else if (param_3 < 0x3e) {
                                    if (param_3 == 0x3c) {
                                      bluetoothPair((QString *)param_1);
                                    }
                                    else if (param_3 < 0x3d) {
                                      if (param_3 == 0x3b) {
                                        bluetoothDisconnect((QString *)param_1);
                                      }
                                      else if (param_3 < 0x3c) {
                                        if (param_3 == 0x3a) {
                                          bluetoothConnect((QString *)param_1);
                                        }
                                        else if (param_3 < 0x3b) {
                                          if (param_3 == 0x39) {
                                            setBluetoothDiscoverable
                                                      (param_1,*(bool *)*(undefined8 *)(param_4 + 8)
                                                      );
                                          }
                                          else if (param_3 < 0x3a) {
                                            if (param_3 == 0x38) {
                                              setBluetoothEnabled(param_1,*(bool *)*(undefined8 *)
                                                                                    (param_4 + 8));
                                            }
                                            else if (param_3 < 0x39) {
                                              if (param_3 == 0x37) {
                                                disconnectVpn(param_1,*(QString **)(param_4 + 8));
                                              }
                                              else if (param_3 < 0x38) {
                                                if (param_3 == 0x36) {
                                                  connectVpn((QString *)param_1);
                                                }
                                                else if (param_3 < 0x37) {
                                                  if (param_3 == 0x35) {
                                                    disconnectNetwork(param_1);
                                                  }
                                                  else if (param_3 < 0x36) {
                                                    if (param_3 == 0x34) {
                                                      connectNetwork(param_1,*(QString **)
                                                                              (param_4 + 8),
                                                                     *(QString **)(param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x35) {
                                                      if (param_3 == 0x33) {
                                                        setWifiEnabled(param_1,*(bool *)*(undefined8
                                                                                          *)(param_4
                                                                                            + 8));
                                                      }
                                                      else if (param_3 < 0x34) {
                                                        if (param_3 == 0x32) {
                                                          local_68[0] = (NCDEEngine)
                                                                        setActiveFiligreepalette
                                                                                  (param_1,*(QString
                                                                                             **)(
                                                  param_4 + 8));
                                                  if (*(long *)param_4 != 0) {
                                                    **(NCDEEngine **)param_4 = local_68[0];
                                                  }
                                                  }
                                                  else if (param_3 < 0x33) {
                                                    if (param_3 == 0x31) {
                                                      local_68[0] = (NCDEEngine)
                                                                    deleteFiligreepalette
                                                                              (param_1,*(QString **)
                                                                                        (param_4 + 8
                                                                                        ));
                                                      if (*(long *)param_4 != 0) {
                                                        **(NCDEEngine **)param_4 = local_68[0];
                                                      }
                                                    }
                                                    else if (param_3 < 0x32) {
                                                      if (param_3 == 0x30) {
                                                        local_68[0] = (NCDEEngine)
                                                                      saveFiligreepalette(param_1,*(
                                                  QString **)(param_4 + 8),
                                                  *(QMap **)(param_4 + 0x10));
                                                  if (*(long *)param_4 != 0) {
                                                    **(NCDEEngine **)param_4 = local_68[0];
                                                  }
                                                  }
                                                  else if (param_3 < 0x31) {
                                                    if (param_3 == 0x2f) {
                                                      terminalConfig(local_68);
                                                      if (*(long *)param_4 != 0) {
                                                        QMap<QString,QVariant>::operator=
                                                                  (*(QMap<QString,QVariant> **)
                                                                    param_4,(QMap *)local_68);
                                                      }
                                                      QMap<QString,QVariant>::~QMap
                                                                ((QMap<QString,QVariant> *)local_68)
                                                      ;
                                                    }
                                                    else if (param_3 < 0x30) {
                                                      if (param_3 == 0x2e) {
                                                        setTerminalGlassTint
                                                                  (param_1,**(double **)
                                                                             (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x2f) {
                                                        if (param_3 == 0x2d) {
                                                          setTerminalFont(param_1,*(QString **)
                                                                                   (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x2e) {
                                                          if (param_3 == 0x2c) {
                                                            local_68[0] = (NCDEEngine)
                                                                          loadTheme(param_1,*(
                                                  QString **)(param_4 + 8));
                                                  if (*(long *)param_4 != 0) {
                                                    **(NCDEEngine **)param_4 = local_68[0];
                                                  }
                                                  }
                                                  else if (param_3 < 0x2d) {
                                                    if (param_3 == 0x2b) {
                                                      local_68[0] = (NCDEEngine)
                                                                    saveTheme(param_1,*(QString **)
                                                                                       (param_4 + 8)
                                                                             );
                                                      if (*(long *)param_4 != 0) {
                                                        **(NCDEEngine **)param_4 = local_68[0];
                                                      }
                                                    }
                                                    else if (param_3 < 0x2c) {
                                                      if (param_3 == 0x2a) {
                                                        toJson();
                                                        if (*(long *)param_4 != 0) {
                                                          QMap<QString,QVariant>::operator=
                                                                    (*(QMap<QString,QVariant> **)
                                                                      param_4,(QMap *)local_68);
                                                        }
                                                        QMap<QString,QVariant>::~QMap
                                                                  ((QMap<QString,QVariant> *)
                                                                   local_68);
                                                      }
                                                      else if (param_3 < 0x2b) {
                                                        if (param_3 == 0x29) {
                                                          recomputeFontSizes(param_1);
                                                        }
                                                        else if (param_3 < 0x2a) {
                                                          if (param_3 == 0x28) {
                                                            setLineHeight(param_1,**(double **)
                                                                                    (param_4 + 8));
                                                          }
                                                          else if (param_3 < 0x29) {
                                                            if (param_3 == 0x27) {
                                                              setLetterSpacing(param_1,**(double **)
                                                                                         (param_4 +
                                                                                         8));
                                                            }
                                                            else if (param_3 < 0x28) {
                                                              if (param_3 == 0x26) {
                                                                setFontSizeScale(param_1,**(double *
                                                  *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x27) {
                                                    if (param_3 == 0x25) {
                                                      setUiScale(param_1,**(double **)(param_4 + 8))
                                                      ;
                                                    }
                                                    else if (param_3 < 0x26) {
                                                      if (param_3 == 0x24) {
                                                        setGarFont(param_1,*(QString **)
                                                                            (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x25) {
                                                        if (param_3 == 0x23) {
                                                          setFellFont(param_1,*(QString **)
                                                                               (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x24) {
                                                          if (param_3 == 0x22) {
                                                            setDisplayFont(param_1,*(QString **)
                                                                                    (param_4 + 8));
                                                          }
                                                          else if (param_3 < 0x23) {
                                                            if (param_3 == 0x21) {
                                                              setMonoFont(param_1,*(QString **)
                                                                                   (param_4 + 8));
                                                            }
                                                            else if (param_3 < 0x22) {
                                                              if (param_3 == 0x20) {
                                                                setTitleFont(param_1,*(QString **)
                                                                                      (param_4 + 8))
                                                                ;
                                                              }
                                                              else if (param_3 < 0x21) {
                                                                if (param_3 == 0x1f) {
                                                                  setBodyFont(param_1,*(QString **)
                                                                                       (param_4 + 8)
                                                                             );
                                                                }
                                                                else if (param_3 < 0x20) {
                                                                  if (param_3 == 0x1e) {
                                                                    setOverrideGlow(param_1,*(
                                                  QString **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x1f) {
                                                    if (param_3 == 0x1d) {
                                                      setOverrideBorder(param_1,*(QString **)
                                                                                 (param_4 + 8));
                                                    }
                                                    else if (param_3 < 0x1e) {
                                                      if (param_3 == 0x1c) {
                                                        setOverrideAccentMuted
                                                                  (param_1,*(QString **)
                                                                            (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x1d) {
                                                        if (param_3 == 0x1b) {
                                                          setOverrideAccent(param_1,*(QString **)
                                                                                     (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x1c) {
                                                          if (param_3 == 0x1a) {
                                                            resetWidgetStyle(param_1,*(QString **)
                                                                                      (param_4 + 8))
                                                            ;
                                                          }
                                                          else if (param_3 < 0x1b) {
                                                            if (param_3 == 0x19) {
                                                              widgetStyle((QString *)local_68);
                                                              if (*(long *)param_4 != 0) {
                                                                QMap<QString,QVariant>::operator=
                                                                          (*(QMap<QString,QVariant>
                                                                             **)param_4,
                                                                           (QMap *)local_68);
                                                              }
                                                              QMap<QString,QVariant>::~QMap
                                                                        ((QMap<QString,QVariant> *)
                                                                         local_68);
                                                            }
                                                            else if (param_3 < 0x1a) {
                                                              if (param_3 == 0x18) {
                                                                setWidgetStyle(param_1,*(QString **)
                                                                                        (param_4 + 8
                                                                                        ),
                                                                               *(QColor **)
                                                                                (param_4 + 0x10),
                                                                               *(QColor **)
                                                                                (param_4 + 0x18),
                                                                               *(QString **)
                                                                                (param_4 + 0x20));
                                                              }
                                                              else if (param_3 < 0x19) {
                                                                if (param_3 == 0x17) {
                                                                  setWidgetStyleMap(param_1,*(
                                                  QString **)(param_4 + 8),
                                                  *(QMap **)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0x18) {
                                                    if (param_3 == 0x16) {
                                                      surfaceGlass((QString *)local_68);
                                                      if (*(long *)param_4 != 0) {
                                                        QMap<QString,QVariant>::operator=
                                                                  (*(QMap<QString,QVariant> **)
                                                                    param_4,(QMap *)local_68);
                                                      }
                                                      QMap<QString,QVariant>::~QMap
                                                                ((QMap<QString,QVariant> *)local_68)
                                                      ;
                                                    }
                                                    else if (param_3 < 0x17) {
                                                      if (param_3 == 0x15) {
                                                        setSurfaceGlass(param_1,*(QString **)
                                                                                 (param_4 + 8),
                                                                        *(QColor **)(param_4 + 0x10)
                                                                        ,**(double **)
                                                                           (param_4 + 0x18),
                                                                        **(double **)
                                                                          (param_4 + 0x20),
                                                                        *(QColor **)(param_4 + 0x28)
                                                                        ,*(QColor **)
                                                                          (param_4 + 0x30));
                                                      }
                                                      else if (param_3 < 0x16) {
                                                        if (param_3 == 0x14) {
                                                          previewWallpaperAsync((QString *)param_1);
                                                        }
                                                        else if (param_3 < 0x15) {
                                                          if (param_3 == 0x13) {
                                                            previewWallpaper((QString *)local_68);
                                                            if (*(long *)param_4 != 0) {
                                                              QMap<QString,QVariant>::operator=
                                                                        (*(QMap<QString,QVariant> **
                                                                          )param_4,(QMap *)local_68)
                                                              ;
                                                            }
                                                            QMap<QString,QVariant>::~QMap
                                                                      ((QMap<QString,QVariant> *)
                                                                       local_68);
                                                          }
                                                          else if (param_3 < 0x14) {
                                                            if (param_3 == 0x12) {
                                                              local_68[0] = (NCDEEngine)
                                                                            sampleWallpaper(param_1,
                                                  *(QString **)(param_4 + 8));
                                                  if (*(long *)param_4 != 0) {
                                                    **(NCDEEngine **)param_4 = local_68[0];
                                                  }
                                                  }
                                                  else if (param_3 < 0x13) {
                                                    if (param_3 == 0x11) {
                                                      currentBasePalette();
                                                      if (*(long *)param_4 != 0) {
                                                        QMap<QString,QVariant>::operator=
                                                                  (*(QMap<QString,QVariant> **)
                                                                    param_4,(QMap *)local_68);
                                                      }
                                                      QMap<QString,QVariant>::~QMap
                                                                ((QMap<QString,QVariant> *)local_68)
                                                      ;
                                                    }
                                                    else if (param_3 < 0x12) {
                                                      if (param_3 == 0x10) {
                                                        applyPreset(param_1,*(QString **)
                                                                             (param_4 + 8));
                                                      }
                                                      else if (param_3 < 0x11) {
                                                        if (param_3 == 0xf) {
                                                          presets(local_68);
                                                          if (*(long *)param_4 != 0) {
                                                            QList<QVariant>::operator=
                                                                      (*(QList<QVariant> **)param_4,
                                                                       (QList *)local_68);
                                                          }
                                                          QList<QVariant>::~QList
                                                                    ((QList<QVariant> *)local_68);
                                                        }
                                                        else if (param_3 < 0x10) {
                                                          if (param_3 == 0xe) {
                                                            clearCustomBase(param_1);
                                                          }
                                                          else if (param_3 < 0xf) {
                                                            if (param_3 == 0xd) {
                                                              setBaseColor(param_1,*(QColor **)
                                                                                    (param_4 + 8),
                                                                           *(QColor **)
                                                                            (param_4 + 0x10),
                                                                           *(QColor **)
                                                                            (param_4 + 0x18));
                                                            }
                                                            else if (param_3 < 0xe) {
                                                              if (param_3 == 0xc) {
                                                                setDarkModeLock(param_1,*(QString **
                                                                                         )(param_4 +
                                                                                          8));
                                                              }
                                                              else if (param_3 < 0xd) {
                                                                if (param_3 == 0xb) {
                                                                  setAccentName(param_1,*(QString **
                                                                                         )(param_4 +
                                                                                          8));
                                                                }
                                                                else if (param_3 < 0xc) {
                                                                  if (param_3 == 10) {
                                                                    setDarkMode(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0xb) {
                                                    if (param_3 == 9) {
                                                      filigreePalettesChanged(param_1);
                                                    }
                                                    else if (param_3 < 10) {
                                                      if (param_3 == 8) {
                                                        soundChanged(param_1);
                                                      }
                                                      else if (param_3 < 9) {
                                                        if (param_3 == 7) {
                                                          printersChanged(param_1);
                                                        }
                                                        else if (param_3 < 8) {
                                                          if (param_3 == 6) {
                                                            usersChanged(param_1);
                                                          }
                                                          else if (param_3 < 7) {
                                                            if (param_3 == 5) {
                                                              dateTimeChanged(param_1);
                                                            }
                                                            else if (param_3 < 6) {
                                                              if (param_3 == 4) {
                                                                wifiChanged(param_1);
                                                              }
                                                              else if (param_3 < 5) {
                                                                if (param_3 == 3) {
                                                                  previewReady(param_1,*(QMap **)(
                                                  param_4 + 8));
                                                  }
                                                  else if (param_3 < 4) {
                                                    if (param_3 == 2) {
                                                      darkModeChanged(param_1);
                                                    }
                                                    else if (param_3 < 3) {
                                                      if (param_3 == 0) {
                                                        changed(param_1);
                                                      }
                                                      else if (param_3 == 1) {
                                                        themeChanged(param_1);
                                                      }
                                                    }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
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
     ((((((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                             (param_4,(void **)changed,(_func_void *)0x0,0), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                             (param_4,(void **)themeChanged,(_func_void *)0x0,1), !bVar2)) &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                            (param_4,(void **)darkModeChanged,(_func_void *)0x0,2), !bVar2)) &&
        ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)(QMap<QString,QVariant>const&)>
                            (param_4,(void **)previewReady,(_func_void_QMap_ptr *)0x0,3), !bVar2 &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                            (param_4,(void **)wifiChanged,(_func_void *)0x0,4), !bVar2)))) &&
       ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                           (param_4,(void **)dateTimeChanged,(_func_void *)0x0,5), !bVar2 &&
        ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                            (param_4,(void **)usersChanged,(_func_void *)0x0,6), !bVar2 &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                            (param_4,(void **)printersChanged,(_func_void *)0x0,7), !bVar2)))))) &&
      ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                          (param_4,(void **)soundChanged,(_func_void *)0x0,8), !bVar2 &&
       (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEEngine::*)()>
                          (param_4,(void **)filigreePalettesChanged,(_func_void *)0x0,9), !bVar2))))
     )) {
    if (param_2 == 1) {
      pQVar1 = *(QString **)param_4;
      if (param_3 == 0x57) {
        appStreams();
        QList<QVariant>::operator=((QList<QVariant> *)pQVar1,(QList *)local_68);
        QList<QVariant>::~QList((QList<QVariant> *)local_68);
      }
      else if (param_3 < 0x58) {
        if (param_3 == 0x56) {
          printers();
          QList<QVariant>::operator=((QList<QVariant> *)pQVar1,(QList *)local_68);
          QList<QVariant>::~QList((QList<QVariant> *)local_68);
        }
        else if (param_3 < 0x57) {
          if (param_3 == 0x55) {
            users();
            QList<QVariant>::operator=((QList<QVariant> *)pQVar1,(QList *)local_68);
            QList<QVariant>::~QList((QList<QVariant> *)local_68);
          }
          else if (param_3 < 0x56) {
            if (param_3 == 0x54) {
              QVar3 = (QString)locating(param_1);
              *pQVar1 = QVar3;
            }
            else if (param_3 < 0x55) {
              if (param_3 == 0x53) {
                localTime(local_68);
                QString::operator=(pQVar1,(QString *)local_68);
                QString::~QString((QString *)local_68);
              }
              else if (param_3 < 0x54) {
                if (param_3 == 0x52) {
                  detectedOffset();
                  QString::operator=(pQVar1,(QString *)local_68);
                  QString::~QString((QString *)local_68);
                }
                else if (param_3 < 0x53) {
                  if (param_3 == 0x51) {
                    detectedRegion();
                    QString::operator=(pQVar1,(QString *)local_68);
                    QString::~QString((QString *)local_68);
                  }
                  else if (param_3 < 0x52) {
                    if (param_3 == 0x50) {
                      detectedZone(local_68);
                      QString::operator=(pQVar1,(QString *)local_68);
                      QString::~QString((QString *)local_68);
                    }
                    else if (param_3 < 0x51) {
                      if (param_3 == 0x4f) {
                        detectedTzName();
                        QString::operator=(pQVar1,(QString *)local_68);
                        QString::~QString((QString *)local_68);
                      }
                      else if (param_3 < 0x50) {
                        if (param_3 == 0x4e) {
                          bluetoothDevices();
                          QList<QVariant>::operator=((QList<QVariant> *)pQVar1,(QList *)local_68);
                          QList<QVariant>::~QList((QList<QVariant> *)local_68);
                        }
                        else if (param_3 < 0x4f) {
                          if (param_3 == 0x4d) {
                            QVar3 = (QString)bluetoothDiscoverable(param_1);
                            *pQVar1 = QVar3;
                          }
                          else if (param_3 < 0x4e) {
                            if (param_3 == 0x4c) {
                              QVar3 = (QString)bluetoothEnabled(param_1);
                              *pQVar1 = QVar3;
                            }
                            else if (param_3 < 0x4d) {
                              if (param_3 == 0x4b) {
                                vpnConnections();
                                QList<QVariant>::operator=
                                          ((QList<QVariant> *)pQVar1,(QList *)local_68);
                                QList<QVariant>::~QList((QList<QVariant> *)local_68);
                              }
                              else if (param_3 < 0x4c) {
                                if (param_3 == 0x4a) {
                                  activeNetwork();
                                  QMap<QString,QVariant>::operator=
                                            ((QMap<QString,QVariant> *)pQVar1,(QMap *)local_68);
                                  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
                                }
                                else if (param_3 < 0x4b) {
                                  if (param_3 == 0x49) {
                                    wifiNetworks();
                                    QList<QVariant>::operator=
                                              ((QList<QVariant> *)pQVar1,(QList *)local_68);
                                    QList<QVariant>::~QList((QList<QVariant> *)local_68);
                                  }
                                  else if (param_3 < 0x4a) {
                                    if (param_3 == 0x48) {
                                      QVar3 = (QString)wifiEnabled(param_1);
                                      *pQVar1 = QVar3;
                                    }
                                    else if (param_3 < 0x49) {
                                      if (param_3 == 0x47) {
                                        version(local_68);
                                        QString::operator=(pQVar1,(QString *)local_68);
                                        QString::~QString((QString *)local_68);
                                      }
                                      else if (param_3 < 0x48) {
                                        if (param_3 == 0x46) {
                                          garFont();
                                          QString::operator=(pQVar1,(QString *)local_68);
                                          QString::~QString((QString *)local_68);
                                        }
                                        else if (param_3 < 0x47) {
                                          if (param_3 == 0x45) {
                                            fellFont();
                                            QString::operator=(pQVar1,(QString *)local_68);
                                            QString::~QString((QString *)local_68);
                                          }
                                          else if (param_3 < 0x46) {
                                            if (param_3 == 0x44) {
                                              displayFont();
                                              QString::operator=(pQVar1,(QString *)local_68);
                                              QString::~QString((QString *)local_68);
                                            }
                                            else if (param_3 < 0x45) {
                                              if (param_3 == 0x43) {
                                                monoFont();
                                                QString::operator=(pQVar1,(QString *)local_68);
                                                QString::~QString((QString *)local_68);
                                              }
                                              else if (param_3 < 0x44) {
                                                if (param_3 == 0x42) {
                                                  titleFont();
                                                  QString::operator=(pQVar1,(QString *)local_68);
                                                  QString::~QString((QString *)local_68);
                                                }
                                                else if (param_3 < 0x43) {
                                                  if (param_3 == 0x41) {
                                                    bodyFont();
                                                    QString::operator=(pQVar1,(QString *)local_68);
                                                    QString::~QString((QString *)local_68);
                                                  }
                                                  else if (param_3 < 0x42) {
                                                    if (param_3 == 0x40) {
                                                      overrideGlow();
                                                      QString::operator=(pQVar1,(QString *)local_68)
                                                      ;
                                                      QString::~QString((QString *)local_68);
                                                    }
                                                    else if (param_3 < 0x41) {
                                                      if (param_3 == 0x3f) {
                                                        overrideBorder();
                                                        QString::operator=(pQVar1,(QString *)
                                                                                  local_68);
                                                        QString::~QString((QString *)local_68);
                                                      }
                                                      else if (param_3 < 0x40) {
                                                        if (param_3 == 0x3e) {
                                                          overrideAccentMuted();
                                                          QString::operator=(pQVar1,(QString *)
                                                                                    local_68);
                                                          QString::~QString((QString *)local_68);
                                                        }
                                                        else if (param_3 < 0x3f) {
                                                          if (param_3 == 0x3d) {
                                                            overrideAccent();
                                                            QString::operator=(pQVar1,(QString *)
                                                                                      local_68);
                                                            QString::~QString((QString *)local_68);
                                                          }
                                                          else if (param_3 < 0x3e) {
                                                            if (param_3 == 0x3c) {
                                                              darkModeLock();
                                                              QString::operator=(pQVar1,(QString *)
                                                                                        local_68);
                                                              QString::~QString((QString *)local_68)
                                                              ;
                                                            }
                                                            else if (param_3 < 0x3d) {
                                                              if (param_3 == 0x3b) {
                                                                accentName();
                                                                QString::operator=(pQVar1,(QString *
                                                                                          )local_68)
                                                                ;
                                                                QString::~QString((QString *)
                                                                                  local_68);
                                                              }
                                                              else if (param_3 < 0x3c) {
                                                                if (param_3 == 0x3a) {
                                                                  themeName();
                                                                  QString::operator=(pQVar1,(QString
                                                                                             *)
                                                  local_68);
                                                  QString::~QString((QString *)local_68);
                                                  }
                                                  else if (param_3 < 0x3b) {
                                                    if (param_3 == 0x39) {
                                                      uVar5 = lineHeight(param_1);
                                                      *(undefined8 *)pQVar1 = uVar5;
                                                    }
                                                    else if (param_3 < 0x3a) {
                                                      if (param_3 == 0x38) {
                                                        uVar4 = letterSpacing(param_1);
                                                        *(undefined4 *)pQVar1 = uVar4;
                                                      }
                                                      else if (param_3 < 0x39) {
                                                        if (param_3 == 0x37) {
                                                          uVar4 = fontSize_lg(param_1);
                                                          *(undefined4 *)pQVar1 = uVar4;
                                                        }
                                                        else if (param_3 < 0x38) {
                                                          if (param_3 == 0x36) {
                                                            uVar4 = fontSize_md(param_1);
                                                            *(undefined4 *)pQVar1 = uVar4;
                                                          }
                                                          else if (param_3 < 0x37) {
                                                            if (param_3 == 0x35) {
                                                              uVar4 = fontSize_sm(param_1);
                                                              *(undefined4 *)pQVar1 = uVar4;
                                                            }
                                                            else if (param_3 < 0x36) {
                                                              if (param_3 == 0x34) {
                                                                QVar3 = (QString)usingCustomBase(
                                                  param_1);
                                                  *pQVar1 = QVar3;
                                                  }
                                                  else if (param_3 < 0x35) {
                                                    if (param_3 == 0x33) {
                                                      QVar3 = (QString)presetActive(param_1);
                                                      *pQVar1 = QVar3;
                                                    }
                                                    else if (param_3 < 0x34) {
                                                      if (param_3 == 0x32) {
                                                        filigreePalettes(local_68);
                                                        QMap<QString,QVariant>::operator=
                                                                  ((QMap<QString,QVariant> *)pQVar1,
                                                                   (QMap *)local_68);
                                                        QMap<QString,QVariant>::~QMap
                                                                  ((QMap<QString,QVariant> *)
                                                                   local_68);
                                                      }
                                                      else if (param_3 < 0x33) {
                                                        if (param_3 == 0x31) {
                                                          activeFiligreePalette();
                                                          QMap<QString,QVariant>::operator=
                                                                    ((QMap<QString,QVariant> *)
                                                                     pQVar1,(QMap *)local_68);
                                                          QMap<QString,QVariant>::~QMap
                                                                    ((QMap<QString,QVariant> *)
                                                                     local_68);
                                                        }
                                                        else if (param_3 < 0x32) {
                                                          if (param_3 == 0x30) {
                                                            activeFiligreePaletteName();
                                                            QString::operator=(pQVar1,(QString *)
                                                                                      local_68);
                                                            QString::~QString((QString *)local_68);
                                                          }
                                                          else if (param_3 < 0x31) {
                                                            if (param_3 == 0x2f) {
                                                              QVar3 = (QString)darkMode(param_1);
                                                              *pQVar1 = QVar3;
                                                            }
                                                            else if (param_3 < 0x30) {
                                                              if (param_3 == 0x2e) {
                                                                auVar6 = inactiveBs();
                                                                local_48 = auVar6._0_6_;
                                                                uStack_42 = auVar6._6_2_;
                                                                local_40 = auVar6._8_6_;
                                                                uStack_3a = auVar6._14_2_;
                                                                *(long *)pQVar1 = auVar6._0_8_;
                                                                *(long *)(pQVar1 + 6) = auVar6._6_8_
                                                                ;
                                                              }
                                                              else if (param_3 < 0x2f) {
                                                                if (param_3 == 0x2d) {
                                                                  auVar6 = inactiveTs();
                                                                  local_48 = auVar6._0_6_;
                                                                  uStack_42 = auVar6._6_2_;
                                                                  local_40 = auVar6._8_6_;
                                                                  uStack_3a = auVar6._14_2_;
                                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                                  *(long *)(pQVar1 + 6) =
                                                                       auVar6._6_8_;
                                                                }
                                                                else if (param_3 < 0x2e) {
                                                                  if (param_3 == 0x2c) {
                                                                    auVar6 = inactiveFg();
                                                                    local_48 = auVar6._0_6_;
                                                                    uStack_42 = auVar6._6_2_;
                                                                    local_40 = auVar6._8_6_;
                                                                    uStack_3a = auVar6._14_2_;
                                                                    *(long *)pQVar1 = auVar6._0_8_;
                                                                    *(long *)(pQVar1 + 6) =
                                                                         auVar6._6_8_;
                                                                  }
                                                                  else if (param_3 < 0x2d) {
                                                                    if (param_3 == 0x2b) {
                                                                      auVar6 = inactiveBg();
                                                                      local_48 = auVar6._0_6_;
                                                                      uStack_42 = auVar6._6_2_;
                                                                      local_40 = auVar6._8_6_;
                                                                      uStack_3a = auVar6._14_2_;
                                                                      *(long *)pQVar1 = auVar6._0_8_
                                                                      ;
                                                                      *(long *)(pQVar1 + 6) =
                                                                           auVar6._6_8_;
                                                                    }
                                                                    else if (param_3 < 0x2c) {
                                                                      if (param_3 == 0x2a) {
                                                                        auVar6 = activeBs();
                                                                        local_48 = auVar6._0_6_;
                                                                        uStack_42 = auVar6._6_2_;
                                                                        local_40 = auVar6._8_6_;
                                                                        uStack_3a = auVar6._14_2_;
                                                                        *(long *)pQVar1 =
                                                                             auVar6._0_8_;
                                                                        *(long *)(pQVar1 + 6) =
                                                                             auVar6._6_8_;
                                                                      }
                                                                      else if (param_3 < 0x2b) {
                                                                        if (param_3 == 0x29) {
                                                                          auVar6 = activeTs();
                                                                          local_48 = auVar6._0_6_;
                                                                          uStack_42 = auVar6._6_2_;
                                                                          local_40 = auVar6._8_6_;
                                                                          uStack_3a = auVar6._14_2_;
                                                                          *(long *)pQVar1 =
                                                                               auVar6._0_8_;
                                                                          *(long *)(pQVar1 + 6) =
                                                                               auVar6._6_8_;
                                                                        }
                                                                        else if (param_3 < 0x2a) {
                                                                          if (param_3 == 0x28) {
                                                                            auVar6 = activeFg();
                                                                            local_48 = auVar6._0_6_;
                                                                            uStack_42 = auVar6._6_2_
                                                                            ;
                                                                            local_40 = auVar6._8_6_;
                                                                            uStack_3a = auVar6.
                                                  _14_2_;
                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                  *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                  }
                                                  else if (param_3 < 0x29) {
                                                    if (param_3 == 0x27) {
                                                      auVar6 = activeBg();
                                                      local_48 = auVar6._0_6_;
                                                      uStack_42 = auVar6._6_2_;
                                                      local_40 = auVar6._8_6_;
                                                      uStack_3a = auVar6._14_2_;
                                                      *(long *)pQVar1 = auVar6._0_8_;
                                                      *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                    }
                                                    else if (param_3 < 0x28) {
                                                      if (param_3 == 0x26) {
                                                        auVar6 = selectColor();
                                                        local_48 = auVar6._0_6_;
                                                        uStack_42 = auVar6._6_2_;
                                                        local_40 = auVar6._8_6_;
                                                        uStack_3a = auVar6._14_2_;
                                                        *(long *)pQVar1 = auVar6._0_8_;
                                                        *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                      }
                                                      else if (param_3 < 0x27) {
                                                        if (param_3 == 0x25) {
                                                          auVar6 = bottomShadow();
                                                          local_48 = auVar6._0_6_;
                                                          uStack_42 = auVar6._6_2_;
                                                          local_40 = auVar6._8_6_;
                                                          uStack_3a = auVar6._14_2_;
                                                          *(long *)pQVar1 = auVar6._0_8_;
                                                          *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                        }
                                                        else if (param_3 < 0x26) {
                                                          if (param_3 == 0x24) {
                                                            auVar6 = topShadow();
                                                            local_48 = auVar6._0_6_;
                                                            uStack_42 = auVar6._6_2_;
                                                            local_40 = auVar6._8_6_;
                                                            uStack_3a = auVar6._14_2_;
                                                            *(long *)pQVar1 = auVar6._0_8_;
                                                            *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                          }
                                                          else if (param_3 < 0x25) {
                                                            if (param_3 == 0x23) {
                                                              auVar6 = foreground();
                                                              local_48 = auVar6._0_6_;
                                                              uStack_42 = auVar6._6_2_;
                                                              local_40 = auVar6._8_6_;
                                                              uStack_3a = auVar6._14_2_;
                                                              *(long *)pQVar1 = auVar6._0_8_;
                                                              *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                            }
                                                            else if (param_3 < 0x24) {
                                                              if (param_3 == 0x22) {
                                                                auVar6 = widgetC5();
                                                                local_48 = auVar6._0_6_;
                                                                uStack_42 = auVar6._6_2_;
                                                                local_40 = auVar6._8_6_;
                                                                uStack_3a = auVar6._14_2_;
                                                                *(long *)pQVar1 = auVar6._0_8_;
                                                                *(long *)(pQVar1 + 6) = auVar6._6_8_
                                                                ;
                                                              }
                                                              else if (param_3 < 0x23) {
                                                                if (param_3 == 0x21) {
                                                                  auVar6 = widgetC4();
                                                                  local_48 = auVar6._0_6_;
                                                                  uStack_42 = auVar6._6_2_;
                                                                  local_40 = auVar6._8_6_;
                                                                  uStack_3a = auVar6._14_2_;
                                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                                  *(long *)(pQVar1 + 6) =
                                                                       auVar6._6_8_;
                                                                }
                                                                else if (param_3 < 0x22) {
                                                                  if (param_3 == 0x20) {
                                                                    auVar6 = widgetC3();
                                                                    local_48 = auVar6._0_6_;
                                                                    uStack_42 = auVar6._6_2_;
                                                                    local_40 = auVar6._8_6_;
                                                                    uStack_3a = auVar6._14_2_;
                                                                    *(long *)pQVar1 = auVar6._0_8_;
                                                                    *(long *)(pQVar1 + 6) =
                                                                         auVar6._6_8_;
                                                                  }
                                                                  else if (param_3 < 0x21) {
                                                                    if (param_3 == 0x1f) {
                                                                      auVar6 = widgetC2();
                                                                      local_48 = auVar6._0_6_;
                                                                      uStack_42 = auVar6._6_2_;
                                                                      local_40 = auVar6._8_6_;
                                                                      uStack_3a = auVar6._14_2_;
                                                                      *(long *)pQVar1 = auVar6._0_8_
                                                                      ;
                                                                      *(long *)(pQVar1 + 6) =
                                                                           auVar6._6_8_;
                                                                    }
                                                                    else if (param_3 < 0x20) {
                                                                      if (param_3 == 0x1e) {
                                                                        auVar6 = widgetC1();
                                                                        local_48 = auVar6._0_6_;
                                                                        uStack_42 = auVar6._6_2_;
                                                                        local_40 = auVar6._8_6_;
                                                                        uStack_3a = auVar6._14_2_;
                                                                        *(long *)pQVar1 =
                                                                             auVar6._0_8_;
                                                                        *(long *)(pQVar1 + 6) =
                                                                             auVar6._6_8_;
                                                                      }
                                                                      else if (param_3 < 0x1f) {
                                                                        if (param_3 == 0x1d) {
                                                                          auVar6 = widgetC0();
                                                                          local_48 = auVar6._0_6_;
                                                                          uStack_42 = auVar6._6_2_;
                                                                          local_40 = auVar6._8_6_;
                                                                          uStack_3a = auVar6._14_2_;
                                                                          *(long *)pQVar1 =
                                                                               auVar6._0_8_;
                                                                          *(long *)(pQVar1 + 6) =
                                                                               auVar6._6_8_;
                                                                        }
                                                                        else if (param_3 < 0x1e) {
                                                                          if (param_3 == 0x1c) {
                                                                            auVar6 = wine4();
                                                                            local_48 = auVar6._0_6_;
                                                                            uStack_42 = auVar6._6_2_
                                                                            ;
                                                                            local_40 = auVar6._8_6_;
                                                                            uStack_3a = auVar6.
                                                  _14_2_;
                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                  *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                  }
                                                  else if (param_3 < 0x1d) {
                                                    if (param_3 == 0x1b) {
                                                      auVar6 = wine3();
                                                      local_48 = auVar6._0_6_;
                                                      uStack_42 = auVar6._6_2_;
                                                      local_40 = auVar6._8_6_;
                                                      uStack_3a = auVar6._14_2_;
                                                      *(long *)pQVar1 = auVar6._0_8_;
                                                      *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                    }
                                                    else if (param_3 < 0x1c) {
                                                      if (param_3 == 0x1a) {
                                                        auVar6 = wine2();
                                                        local_48 = auVar6._0_6_;
                                                        uStack_42 = auVar6._6_2_;
                                                        local_40 = auVar6._8_6_;
                                                        uStack_3a = auVar6._14_2_;
                                                        *(long *)pQVar1 = auVar6._0_8_;
                                                        *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                      }
                                                      else if (param_3 < 0x1b) {
                                                        if (param_3 == 0x19) {
                                                          auVar6 = wine1();
                                                          local_48 = auVar6._0_6_;
                                                          uStack_42 = auVar6._6_2_;
                                                          local_40 = auVar6._8_6_;
                                                          uStack_3a = auVar6._14_2_;
                                                          *(long *)pQVar1 = auVar6._0_8_;
                                                          *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                        }
                                                        else if (param_3 < 0x1a) {
                                                          if (param_3 == 0x18) {
                                                            auVar6 = gilt5();
                                                            local_48 = auVar6._0_6_;
                                                            uStack_42 = auVar6._6_2_;
                                                            local_40 = auVar6._8_6_;
                                                            uStack_3a = auVar6._14_2_;
                                                            *(long *)pQVar1 = auVar6._0_8_;
                                                            *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                          }
                                                          else if (param_3 < 0x19) {
                                                            if (param_3 == 0x17) {
                                                              auVar6 = gilt4();
                                                              local_48 = auVar6._0_6_;
                                                              uStack_42 = auVar6._6_2_;
                                                              local_40 = auVar6._8_6_;
                                                              uStack_3a = auVar6._14_2_;
                                                              *(long *)pQVar1 = auVar6._0_8_;
                                                              *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                            }
                                                            else if (param_3 < 0x18) {
                                                              if (param_3 == 0x16) {
                                                                auVar6 = gilt3();
                                                                local_48 = auVar6._0_6_;
                                                                uStack_42 = auVar6._6_2_;
                                                                local_40 = auVar6._8_6_;
                                                                uStack_3a = auVar6._14_2_;
                                                                *(long *)pQVar1 = auVar6._0_8_;
                                                                *(long *)(pQVar1 + 6) = auVar6._6_8_
                                                                ;
                                                              }
                                                              else if (param_3 < 0x17) {
                                                                if (param_3 == 0x15) {
                                                                  auVar6 = gilt2();
                                                                  local_48 = auVar6._0_6_;
                                                                  uStack_42 = auVar6._6_2_;
                                                                  local_40 = auVar6._8_6_;
                                                                  uStack_3a = auVar6._14_2_;
                                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                                  *(long *)(pQVar1 + 6) =
                                                                       auVar6._6_8_;
                                                                }
                                                                else if (param_3 < 0x16) {
                                                                  if (param_3 == 0x14) {
                                                                    auVar6 = gilt1();
                                                                    local_48 = auVar6._0_6_;
                                                                    uStack_42 = auVar6._6_2_;
                                                                    local_40 = auVar6._8_6_;
                                                                    uStack_3a = auVar6._14_2_;
                                                                    *(long *)pQVar1 = auVar6._0_8_;
                                                                    *(long *)(pQVar1 + 6) =
                                                                         auVar6._6_8_;
                                                                  }
                                                                  else if (param_3 < 0x15) {
                                                                    if (param_3 == 0x13) {
                                                                      auVar6 = gilt0();
                                                                      local_48 = auVar6._0_6_;
                                                                      uStack_42 = auVar6._6_2_;
                                                                      local_40 = auVar6._8_6_;
                                                                      uStack_3a = auVar6._14_2_;
                                                                      *(long *)pQVar1 = auVar6._0_8_
                                                                      ;
                                                                      *(long *)(pQVar1 + 6) =
                                                                           auVar6._6_8_;
                                                                    }
                                                                    else if (param_3 < 0x14) {
                                                                      if (param_3 == 0x12) {
                                                                        auVar6 = lamp();
                                                                        local_48 = auVar6._0_6_;
                                                                        uStack_42 = auVar6._6_2_;
                                                                        local_40 = auVar6._8_6_;
                                                                        uStack_3a = auVar6._14_2_;
                                                                        *(long *)pQVar1 =
                                                                             auVar6._0_8_;
                                                                        *(long *)(pQVar1 + 6) =
                                                                             auVar6._6_8_;
                                                                      }
                                                                      else if (param_3 < 0x13) {
                                                                        if (param_3 == 0x11) {
                                                                          auVar6 = clockColor();
                                                                          local_48 = auVar6._0_6_;
                                                                          uStack_42 = auVar6._6_2_;
                                                                          local_40 = auVar6._8_6_;
                                                                          uStack_3a = auVar6._14_2_;
                                                                          *(long *)pQVar1 =
                                                                               auVar6._0_8_;
                                                                          *(long *)(pQVar1 + 6) =
                                                                               auVar6._6_8_;
                                                                        }
                                                                        else if (param_3 < 0x12) {
                                                                          if (param_3 == 0x10) {
                                                                            auVar6 = amber();
                                                                            local_48 = auVar6._0_6_;
                                                                            uStack_42 = auVar6._6_2_
                                                                            ;
                                                                            local_40 = auVar6._8_6_;
                                                                            uStack_3a = auVar6.
                                                  _14_2_;
                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                  *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                  }
                                                  else if (param_3 < 0x11) {
                                                    if (param_3 == 0xf) {
                                                      auVar6 = rose();
                                                      local_48 = auVar6._0_6_;
                                                      uStack_42 = auVar6._6_2_;
                                                      local_40 = auVar6._8_6_;
                                                      uStack_3a = auVar6._14_2_;
                                                      *(long *)pQVar1 = auVar6._0_8_;
                                                      *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                    }
                                                    else if (param_3 < 0x10) {
                                                      if (param_3 == 0xe) {
                                                        auVar6 = cer();
                                                        local_48 = auVar6._0_6_;
                                                        uStack_42 = auVar6._6_2_;
                                                        local_40 = auVar6._8_6_;
                                                        uStack_3a = auVar6._14_2_;
                                                        *(long *)pQVar1 = auVar6._0_8_;
                                                        *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                      }
                                                      else if (param_3 < 0xf) {
                                                        if (param_3 == 0xd) {
                                                          auVar6 = verd();
                                                          local_48 = auVar6._0_6_;
                                                          uStack_42 = auVar6._6_2_;
                                                          local_40 = auVar6._8_6_;
                                                          uStack_3a = auVar6._14_2_;
                                                          *(long *)pQVar1 = auVar6._0_8_;
                                                          *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                        }
                                                        else if (param_3 < 0xe) {
                                                          if (param_3 == 0xc) {
                                                            auVar6 = inkSoft();
                                                            local_48 = auVar6._0_6_;
                                                            uStack_42 = auVar6._6_2_;
                                                            local_40 = auVar6._8_6_;
                                                            uStack_3a = auVar6._14_2_;
                                                            *(long *)pQVar1 = auVar6._0_8_;
                                                            *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                          }
                                                          else if (param_3 < 0xd) {
                                                            if (param_3 == 0xb) {
                                                              auVar6 = ink();
                                                              local_48 = auVar6._0_6_;
                                                              uStack_42 = auVar6._6_2_;
                                                              local_40 = auVar6._8_6_;
                                                              uStack_3a = auVar6._14_2_;
                                                              *(long *)pQVar1 = auVar6._0_8_;
                                                              *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                            }
                                                            else if (param_3 < 0xc) {
                                                              if (param_3 == 10) {
                                                                auVar6 = glow();
                                                                local_48 = auVar6._0_6_;
                                                                uStack_42 = auVar6._6_2_;
                                                                local_40 = auVar6._8_6_;
                                                                uStack_3a = auVar6._14_2_;
                                                                *(long *)pQVar1 = auVar6._0_8_;
                                                                *(long *)(pQVar1 + 6) = auVar6._6_8_
                                                                ;
                                                              }
                                                              else if (param_3 < 0xb) {
                                                                if (param_3 == 9) {
                                                                  auVar6 = border();
                                                                  local_48 = auVar6._0_6_;
                                                                  uStack_42 = auVar6._6_2_;
                                                                  local_40 = auVar6._8_6_;
                                                                  uStack_3a = auVar6._14_2_;
                                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                                  *(long *)(pQVar1 + 6) =
                                                                       auVar6._6_8_;
                                                                }
                                                                else if (param_3 < 10) {
                                                                  if (param_3 == 8) {
                                                                    auVar6 = popupBg();
                                                                    local_48 = auVar6._0_6_;
                                                                    uStack_42 = auVar6._6_2_;
                                                                    local_40 = auVar6._8_6_;
                                                                    uStack_3a = auVar6._14_2_;
                                                                    *(long *)pQVar1 = auVar6._0_8_;
                                                                    *(long *)(pQVar1 + 6) =
                                                                         auVar6._6_8_;
                                                                  }
                                                                  else if (param_3 < 9) {
                                                                    if (param_3 == 7) {
                                                                      auVar6 = panelText();
                                                                      local_48 = auVar6._0_6_;
                                                                      uStack_42 = auVar6._6_2_;
                                                                      local_40 = auVar6._8_6_;
                                                                      uStack_3a = auVar6._14_2_;
                                                                      *(long *)pQVar1 = auVar6._0_8_
                                                                      ;
                                                                      *(long *)(pQVar1 + 6) =
                                                                           auVar6._6_8_;
                                                                    }
                                                                    else if (param_3 < 8) {
                                                                      if (param_3 == 6) {
                                                                        auVar6 = panelBg();
                                                                        local_48 = auVar6._0_6_;
                                                                        uStack_42 = auVar6._6_2_;
                                                                        local_40 = auVar6._8_6_;
                                                                        uStack_3a = auVar6._14_2_;
                                                                        *(long *)pQVar1 =
                                                                             auVar6._0_8_;
                                                                        *(long *)(pQVar1 + 6) =
                                                                             auVar6._6_8_;
                                                                      }
                                                                      else if (param_3 < 7) {
                                                                        if (param_3 == 5) {
                                                                          auVar6 = surfaceHi();
                                                                          local_48 = auVar6._0_6_;
                                                                          uStack_42 = auVar6._6_2_;
                                                                          local_40 = auVar6._8_6_;
                                                                          uStack_3a = auVar6._14_2_;
                                                                          *(long *)pQVar1 =
                                                                               auVar6._0_8_;
                                                                          *(long *)(pQVar1 + 6) =
                                                                               auVar6._6_8_;
                                                                        }
                                                                        else if (param_3 < 6) {
                                                                          if (param_3 == 4) {
                                                                            auVar6 = surfaceAlt();
                                                                            local_48 = auVar6._0_6_;
                                                                            uStack_42 = auVar6._6_2_
                                                                            ;
                                                                            local_40 = auVar6._8_6_;
                                                                            uStack_3a = auVar6.
                                                  _14_2_;
                                                  *(long *)pQVar1 = auVar6._0_8_;
                                                  *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                  }
                                                  else if (param_3 < 5) {
                                                    if (param_3 == 3) {
                                                      auVar6 = surface();
                                                      local_48 = auVar6._0_6_;
                                                      uStack_42 = auVar6._6_2_;
                                                      local_40 = auVar6._8_6_;
                                                      uStack_3a = auVar6._14_2_;
                                                      *(long *)pQVar1 = auVar6._0_8_;
                                                      *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                    }
                                                    else if (param_3 < 4) {
                                                      if (param_3 == 2) {
                                                        auVar6 = background();
                                                        local_48 = auVar6._0_6_;
                                                        uStack_42 = auVar6._6_2_;
                                                        local_40 = auVar6._8_6_;
                                                        uStack_3a = auVar6._14_2_;
                                                        *(long *)pQVar1 = auVar6._0_8_;
                                                        *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                      }
                                                      else if (param_3 < 3) {
                                                        if (param_3 == 0) {
                                                          auVar6 = accent();
                                                          local_48 = auVar6._0_6_;
                                                          uStack_42 = auVar6._6_2_;
                                                          local_40 = auVar6._8_6_;
                                                          uStack_3a = auVar6._14_2_;
                                                          *(long *)pQVar1 = auVar6._0_8_;
                                                          *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                        }
                                                        else if (param_3 == 1) {
                                                          auVar6 = accentMuted();
                                                          local_48 = auVar6._0_6_;
                                                          uStack_42 = auVar6._6_2_;
                                                          local_40 = auVar6._8_6_;
                                                          uStack_3a = auVar6._14_2_;
                                                          *(long *)pQVar1 = auVar6._0_8_;
                                                          *(long *)(pQVar1 + 6) = auVar6._6_8_;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (param_2 == 2) {
      pQVar1 = *(QString **)param_4;
      if (param_3 == 0x3c) {
        setDarkModeLock(param_1,pQVar1);
      }
      else if (param_3 < 0x3d) {
        if (param_3 == 0x2f) {
          setDarkMode(param_1,(bool)*pQVar1);
        }
        else if (param_3 == 0x3b) {
          setAccentName(param_1,pQVar1);
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



// ==== 00145018  NCDEEngine::metaObject

/* NCDEEngine::metaObject() const */

undefined1 * __thiscall NCDEEngine::metaObject(NCDEEngine *this)

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



// ==== 00145060  NCDEEngine::qt_metacast

/* NCDEEngine::qt_metacast(char const*) */

NCDEEngine * __thiscall NCDEEngine::qt_metacast(NCDEEngine *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NCDEEngine *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NCDEEngine");
    if (iVar1 != 0) {
      this = (NCDEEngine *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 001450b4  NCDEEngine::qt_metacall

/* NCDEEngine::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NCDEEngine::qt_metacall(NCDEEngine *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x4d) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x4d;
    }
    if (param_2 == 7) {
      if (local_28 < 0x4d) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x4d;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -0x58;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001451aa  NCDEEngine::changed

/* NCDEEngine::changed() */

void __thiscall NCDEEngine::changed(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 001451d6  NCDEEngine::themeChanged

/* NCDEEngine::themeChanged() */

void __thiscall NCDEEngine::themeChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 00145202  NCDEEngine::darkModeChanged

/* NCDEEngine::darkModeChanged() */

void __thiscall NCDEEngine::darkModeChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 0014522e  NCDEEngine::previewReady

/* NCDEEngine::previewReady(QMap<QString, QVariant> const&) */

void __thiscall NCDEEngine::previewReady(NCDEEngine *this,QMap *param_1)

{
  QMetaObject::activate<void,QMap<QString,QVariant>>
            ((QObject *)this,(QMetaObject *)staticMetaObject,3,(void *)0x0,param_1);
  return;
}



// ==== 00145266  NCDEEngine::wifiChanged

/* NCDEEngine::wifiChanged() */

void __thiscall NCDEEngine::wifiChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,4,(void **)0x0);
  return;
}



// ==== 00145292  NCDEEngine::dateTimeChanged

/* NCDEEngine::dateTimeChanged() */

void __thiscall NCDEEngine::dateTimeChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 001452be  NCDEEngine::usersChanged

/* NCDEEngine::usersChanged() */

void __thiscall NCDEEngine::usersChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,6,(void **)0x0);
  return;
}



// ==== 001452ea  NCDEEngine::printersChanged

/* NCDEEngine::printersChanged() */

void __thiscall NCDEEngine::printersChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,7,(void **)0x0);
  return;
}



// ==== 00145316  NCDEEngine::soundChanged

/* NCDEEngine::soundChanged() */

void __thiscall NCDEEngine::soundChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,8,(void **)0x0);
  return;
}



// ==== 00145342  NCDEEngine::filigreePalettesChanged

/* NCDEEngine::filigreePalettesChanged() */

void __thiscall NCDEEngine::filigreePalettesChanged(NCDEEngine *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,9,(void **)0x0);
  return;
}



// ==== 00164ba4  NCDEEngine::NCDEEngine

/* NCDEEngine::NCDEEngine(QObject*) */

void __thiscall NCDEEngine::NCDEEngine(NCDEEngine *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_90 [8];
  undefined1 *local_88;
  undefined1 *local_80;
  undefined *local_78;
  undefined1 *local_70;
  undefined1 *local_68;
  undefined *local_60;
  wchar16 *local_58;
  wchar16 *local_50;
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c0a8;
  QTimer::QTimer((QTimer *)(this + 0x10),(QObject *)0x0);
  *(undefined8 *)(this + 0x20) = 0;
  this[0x28] = (NCDEEngine)0x1;
  this[0x29] = (NCDEEngine)0x0;
  this[0x2a] = (NCDEEngine)0x0;
  QColor::QColor((QColor *)(this + 0x2c),"#c98a3a");
  QColor::QColor((QColor *)(this + 0x3c),"#8a5a20");
  QColor::QColor((QColor *)(this + 0x4c),"#0c0907");
  QColor::QColor((QColor *)(this + 0x5c),"#171009");
  QColor::QColor((QColor *)(this + 0x6c),"#1e1409");
  QColor::QColor((QColor *)(this + 0x7c),"#e9c97c");
  QColor::QColor((QColor *)(this + 0x8c),"#0c0907");
  QColor::QColor((QColor *)(this + 0x9c),"#0a0806");
  QColor::QColor((QColor *)(this + 0xac),"#8a5a20");
  QColor::QColor((QColor *)(this + 0xbc),"#c98a3a");
  QColor::QColor((QColor *)(this + 0xcc),"#f4e9d2");
  QColor::QColor((QColor *)(this + 0xdc),"#b8a07a");
  QColor::QColor((QColor *)(this + 0xec),"#4f9183");
  QColor::QColor((QColor *)(this + 0xfc),"#5fb4c6");
  QColor::QColor((QColor *)(this + 0x10c),"#c64b63");
  QColor::QColor((QColor *)(this + 0x11c),"#e9a23a");
  QColor::QColor((QColor *)(this + 300),"#5a3a14");
  QColor::QColor((QColor *)(this + 0x13c),"#8a5a20");
  QColor::QColor((QColor *)(this + 0x14c),"#b07a30");
  QColor::QColor((QColor *)(this + 0x15c),"#c98a3a");
  QColor::QColor((QColor *)(this + 0x16c),"#e9c97c");
  QColor::QColor((QColor *)(this + 0x17c),"#f6e3b0");
  QColor::QColor((QColor *)(this + 0x18c),"#2a0612");
  QColor::QColor((QColor *)(this + 0x19c),"#4a0e22");
  QColor::QColor((QColor *)(this + 0x1ac),"#6e1832");
  QColor::QColor((QColor *)(this + 0x1bc),"#8b1e3f");
  QColor::QColor((QColor *)(this + 0x1cc),"#171009");
  QColor::QColor((QColor *)(this + 0x1dc),"#1e1409");
  QColor::QColor((QColor *)(this + 0x1ec),"#4f9183");
  QColor::QColor((QColor *)(this + 0x1fc),"#5fb4c6");
  QColor::QColor((QColor *)(this + 0x20c),"#c98a3a");
  QColor::QColor((QColor *)(this + 0x21c),"#c64b63");
  QColor::QColor((QColor *)(this + 0x22c));
  QColor::QColor((QColor *)(this + 0x23c));
  QColor::QColor((QColor *)(this + 0x24c));
  QColor::QColor((QColor *)(this + 0x25c));
  QColor::QColor((QColor *)(this + 0x26c));
  QColor::QColor((QColor *)(this + 0x27c));
  QColor::QColor((QColor *)(this + 0x28c));
  *(undefined4 *)(this + 0x29c) = 0xb;
  *(undefined4 *)(this + 0x2a0) = 0xe;
  *(undefined4 *)(this + 0x2a4) = 0x14;
  *(undefined4 *)(this + 0x2a8) = 0;
  *(undefined8 *)(this + 0x2b0) = 0x3ff0000000000000;
  local_50 = L"NCDE Poseidon";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"NCDE Poseidon",0xd);
  QString::QString((QString *)(this + 0x2b8),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_58 = L"Gilt";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"Gilt",4);
  QString::QString((QString *)(this + 0x2d0),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  QString::QString((QString *)(this + 0x2e8));
  QColor::QColor((QColor *)(this + 0x300),"#c98a3a");
  QColor::QColor((QColor *)(this + 0x310),"#8a5a20");
  QColor::QColor((QColor *)(this + 800),"#c98a3a");
  this[0x330] = (NCDEEngine)0x0;
  QColor::QColor((QColor *)(this + 0x334));
  QColor::QColor((QColor *)(this + 0x344));
  QColor::QColor((QColor *)(this + 0x354));
  QColor::QColor((QColor *)(this + 0x364));
  QColor::QColor((QColor *)(this + 0x374));
  QColor::QColor((QColor *)(this + 900));
  QColor::QColor((QColor *)(this + 0x394));
  QColor::QColor((QColor *)(this + 0x3a4));
  this[0x3b4] = (NCDEEngine)0x0;
  QString::QString((QString *)(this + 0x3b8));
  QString::QString((QString *)(this + 0x3d0));
  QString::QString((QString *)(this + 1000));
  QString::QString((QString *)(this + 0x400));
  local_60 = &DAT_00299608;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"Cormorant Garamond",
             0x12);
  QString::QString((QString *)(this + 0x418),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_68 = &LAB_0029962d_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"Cinzel",6);
  QString::QString((QString *)(this + 0x430),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_70 = &LAB_0029963b_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"JetBrains Mono",0xe);
  QString::QString((QString *)(this + 0x448),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_78 = &DAT_00299660;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"IM Fell DW Pica",0xf)
  ;
  QString::QString((QString *)(this + 0x460),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_80 = &LAB_00299680;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"IM Fell English",0xf)
  ;
  QString::QString((QString *)(this + 0x478),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  local_88 = &LAB_0029969c_4;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_48,(QTypedArrayData *)0x0,L"EB Garamond",0xb);
  QString::QString((QString *)(this + 0x490),(QArrayDataPointer *)&local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_48);
  *(undefined8 *)(this + 0x4a8) = 0x3ff0000000000000;
  *(undefined8 *)(this + 0x4b0) = 0x3ff0000000000000;
  QHash<QString,QMap<QString,QVariant>>::QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4b8));
  QHash<QString,QMap<QString,QVariant>>::QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0));
  *(undefined8 *)(this + 0x4c8) = 0;
  *(undefined8 *)(this + 0x4d0) = 0;
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x4d8));
  QString::QString((QString *)(this + 0x4e0));
  QTimer::setSingleShot((bool)((char)this + '\x10'));
  local_48 = recompute;
  local_40 = 0;
  QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(NCDEEngine::*)()>
            (local_90,this + 0x10,QTimer::timeout,0,this,&local_48,0);
  QMetaObject::Connection::~Connection(local_90);
  recompute(this);
  loadPersistedFiligree(this);
  loadActiveFiligreepalette(this);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016582a  NCDEEngine::accent

/* NCDEEngine::accent() const */

undefined8 NCDEEngine::accent(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x34));
  }
  return *(undefined8 *)(in_RDI + 0x2c);
}



// ==== 00165878  NCDEEngine::accentMuted

/* NCDEEngine::accentMuted() const */

undefined8 NCDEEngine::accentMuted(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x44));
  }
  return *(undefined8 *)(in_RDI + 0x3c);
}



// ==== 001658c6  NCDEEngine::background

/* NCDEEngine::background() const */

undefined8 NCDEEngine::background(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x54));
  }
  return *(undefined8 *)(in_RDI + 0x4c);
}



// ==== 00165914  NCDEEngine::surface

/* NCDEEngine::surface() const */

undefined8 NCDEEngine::surface(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 100));
  }
  return *(undefined8 *)(in_RDI + 0x5c);
}



// ==== 00165962  NCDEEngine::surfaceAlt

/* NCDEEngine::surfaceAlt() const */

undefined8 NCDEEngine::surfaceAlt(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x74));
  }
  return *(undefined8 *)(in_RDI + 0x6c);
}



// ==== 001659b0  NCDEEngine::surfaceHi

/* NCDEEngine::surfaceHi() const */

undefined8 NCDEEngine::surfaceHi(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x84));
  }
  return *(undefined8 *)(in_RDI + 0x7c);
}



// ==== 00165a00  NCDEEngine::panelBg

/* NCDEEngine::panelBg() const */

undefined8 NCDEEngine::panelBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x94));
  }
  return *(undefined8 *)(in_RDI + 0x8c);
}



// ==== 00165a54  NCDEEngine::panelText

/* NCDEEngine::panelText() const */

undefined8 NCDEEngine::panelText(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xd4));
  }
  return *(undefined8 *)(in_RDI + 0xcc);
}



// ==== 00165aa8  NCDEEngine::popupBg

/* NCDEEngine::popupBg() const */

undefined8 NCDEEngine::popupBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xa4));
  }
  return *(undefined8 *)(in_RDI + 0x9c);
}



// ==== 00165afc  NCDEEngine::border

/* NCDEEngine::border() const */

undefined8 NCDEEngine::border(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xb4));
  }
  return *(undefined8 *)(in_RDI + 0xac);
}



// ==== 00165b50  NCDEEngine::glow

/* NCDEEngine::glow() const */

undefined8 NCDEEngine::glow(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xc4));
  }
  return *(undefined8 *)(in_RDI + 0xbc);
}



// ==== 00165ba4  NCDEEngine::ink

/* NCDEEngine::ink() const */

undefined8 NCDEEngine::ink(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xd4));
  }
  return *(undefined8 *)(in_RDI + 0xcc);
}



// ==== 00165bf8  NCDEEngine::inkSoft

/* NCDEEngine::inkSoft() const */

undefined8 NCDEEngine::inkSoft(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xe4));
  }
  return *(undefined8 *)(in_RDI + 0xdc);
}



// ==== 00165c4c  NCDEEngine::verd

/* NCDEEngine::verd() const */

undefined8 NCDEEngine::verd(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xf4));
  }
  return *(undefined8 *)(in_RDI + 0xec);
}



// ==== 00165ca0  NCDEEngine::cer

/* NCDEEngine::cer() const */

undefined8 NCDEEngine::cer(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x104));
  }
  return *(undefined8 *)(in_RDI + 0xfc);
}



// ==== 00165cf4  NCDEEngine::rose

/* NCDEEngine::rose() const */

undefined8 NCDEEngine::rose(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x114));
  }
  return *(undefined8 *)(in_RDI + 0x10c);
}



// ==== 00165d48  NCDEEngine::amber

/* NCDEEngine::amber() const */

undefined8 NCDEEngine::amber(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x124));
  }
  return *(undefined8 *)(in_RDI + 0x11c);
}



// ==== 00165d9c  NCDEEngine::lamp

/* NCDEEngine::lamp() const */

undefined8 NCDEEngine::lamp(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x124));
  }
  return *(undefined8 *)(in_RDI + 0x11c);
}



// ==== 00165df0  NCDEEngine::clockColor

/* NCDEEngine::clockColor() const */

undefined8 NCDEEngine::clockColor(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0xd4));
  }
  return *(undefined8 *)(in_RDI + 0xcc);
}



// ==== 00165e44  NCDEEngine::gilt0

/* NCDEEngine::gilt0() const */

undefined8 NCDEEngine::gilt0(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x134));
  }
  return *(undefined8 *)(in_RDI + 300);
}



// ==== 00165e98  NCDEEngine::gilt1

/* NCDEEngine::gilt1() const */

undefined8 NCDEEngine::gilt1(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x144));
  }
  return *(undefined8 *)(in_RDI + 0x13c);
}



// ==== 00165eec  NCDEEngine::gilt2

/* NCDEEngine::gilt2() const */

undefined8 NCDEEngine::gilt2(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x154));
  }
  return *(undefined8 *)(in_RDI + 0x14c);
}



// ==== 00165f40  NCDEEngine::gilt3

/* NCDEEngine::gilt3() const */

undefined8 NCDEEngine::gilt3(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x164));
  }
  return *(undefined8 *)(in_RDI + 0x15c);
}



// ==== 00165f94  NCDEEngine::gilt4

/* NCDEEngine::gilt4() const */

undefined8 NCDEEngine::gilt4(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x174));
  }
  return *(undefined8 *)(in_RDI + 0x16c);
}



// ==== 00165fe8  NCDEEngine::gilt5

/* NCDEEngine::gilt5() const */

undefined8 NCDEEngine::gilt5(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x184));
  }
  return *(undefined8 *)(in_RDI + 0x17c);
}



// ==== 0016603c  NCDEEngine::wine1

/* NCDEEngine::wine1() const */

undefined8 NCDEEngine::wine1(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x194));
  }
  return *(undefined8 *)(in_RDI + 0x18c);
}



// ==== 00166090  NCDEEngine::wine2

/* NCDEEngine::wine2() const */

undefined8 NCDEEngine::wine2(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x1a4));
  }
  return *(undefined8 *)(in_RDI + 0x19c);
}



// ==== 001660e4  NCDEEngine::wine3

/* NCDEEngine::wine3() const */

undefined8 NCDEEngine::wine3(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x1b4));
  }
  return *(undefined8 *)(in_RDI + 0x1ac);
}



// ==== 00166138  NCDEEngine::wine4

/* NCDEEngine::wine4() const */

undefined8 NCDEEngine::wine4(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x1c4));
  }
  return *(undefined8 *)(in_RDI + 0x1bc);
}



// ==== 0016618c  NCDEEngine::widgetC0

/* NCDEEngine::widgetC0() const */

undefined8 NCDEEngine::widgetC0(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x1d4));
  }
  return *(undefined8 *)(in_RDI + 0x1cc);
}



// ==== 001661e0  NCDEEngine::widgetC1

/* NCDEEngine::widgetC1() const */

undefined8 NCDEEngine::widgetC1(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x1e4));
  }
  return *(undefined8 *)(in_RDI + 0x1dc);
}



// ==== 00166234  NCDEEngine::widgetC2

/* NCDEEngine::widgetC2() const */

undefined8 NCDEEngine::widgetC2(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 500));
  }
  return *(undefined8 *)(in_RDI + 0x1ec);
}



// ==== 00166288  NCDEEngine::widgetC3

/* NCDEEngine::widgetC3() const */

undefined8 NCDEEngine::widgetC3(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x204));
  }
  return *(undefined8 *)(in_RDI + 0x1fc);
}



// ==== 001662dc  NCDEEngine::widgetC4

/* NCDEEngine::widgetC4() const */

undefined8 NCDEEngine::widgetC4(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x214));
  }
  return *(undefined8 *)(in_RDI + 0x20c);
}



// ==== 00166330  NCDEEngine::widgetC5

/* NCDEEngine::widgetC5() const */

undefined8 NCDEEngine::widgetC5(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x224));
  }
  return *(undefined8 *)(in_RDI + 0x21c);
}



// ==== 00166384  NCDEEngine::foreground

/* NCDEEngine::foreground() const */

undefined8 NCDEEngine::foreground(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x234));
  }
  return *(undefined8 *)(in_RDI + 0x22c);
}



// ==== 001663d8  NCDEEngine::topShadow

/* NCDEEngine::topShadow() const */

undefined8 NCDEEngine::topShadow(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x244));
  }
  return *(undefined8 *)(in_RDI + 0x23c);
}



// ==== 0016642c  NCDEEngine::bottomShadow

/* NCDEEngine::bottomShadow() const */

undefined8 NCDEEngine::bottomShadow(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x254));
  }
  return *(undefined8 *)(in_RDI + 0x24c);
}



// ==== 00166480  NCDEEngine::selectColor

/* NCDEEngine::selectColor() const */

undefined8 NCDEEngine::selectColor(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x264));
  }
  return *(undefined8 *)(in_RDI + 0x25c);
}



// ==== 001664d4  NCDEEngine::activeBg

/* NCDEEngine::activeBg() const */

undefined8 NCDEEngine::activeBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 100));
  }
  return *(undefined8 *)(in_RDI + 0x5c);
}



// ==== 00166522  NCDEEngine::activeFg

/* NCDEEngine::activeFg() const */

undefined8 NCDEEngine::activeFg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x234));
  }
  return *(undefined8 *)(in_RDI + 0x22c);
}



// ==== 00166576  NCDEEngine::activeTs

/* NCDEEngine::activeTs() const */

undefined8 NCDEEngine::activeTs(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x244));
  }
  return *(undefined8 *)(in_RDI + 0x23c);
}



// ==== 001665ca  NCDEEngine::activeBs

/* NCDEEngine::activeBs() const */

undefined8 NCDEEngine::activeBs(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x254));
  }
  return *(undefined8 *)(in_RDI + 0x24c);
}



// ==== 0016661e  NCDEEngine::inactiveBg

/* NCDEEngine::inactiveBg() const */

undefined8 NCDEEngine::inactiveBg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x94));
  }
  return *(undefined8 *)(in_RDI + 0x8c);
}



// ==== 00166672  NCDEEngine::inactiveFg

/* NCDEEngine::inactiveFg() const */

undefined8 NCDEEngine::inactiveFg(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x274));
  }
  return *(undefined8 *)(in_RDI + 0x26c);
}



// ==== 001666c6  NCDEEngine::inactiveTs

/* NCDEEngine::inactiveTs() const */

undefined8 NCDEEngine::inactiveTs(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x284));
  }
  return *(undefined8 *)(in_RDI + 0x27c);
}



// ==== 0016671a  NCDEEngine::inactiveBs

/* NCDEEngine::inactiveBs() const */

undefined8 NCDEEngine::inactiveBs(void)

{
  undefined8 in_RSI;
  long in_RDI;
  long in_FS_OFFSET;
  
  if (*(long *)(in_FS_OFFSET + 0x28) != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(in_RDI,in_RSI,*(undefined8 *)(in_RDI + 0x294));
  }
  return *(undefined8 *)(in_RDI + 0x28c);
}



// ==== 0016676e  NCDEEngine::darkMode

/* NCDEEngine::darkMode() const */

NCDEEngine __thiscall NCDEEngine::darkMode(NCDEEngine *this)

{
  return this[0x28];
}



// ==== 00166780  NCDEEngine::presetActive

/* NCDEEngine::presetActive() const */

NCDEEngine __thiscall NCDEEngine::presetActive(NCDEEngine *this)

{
  return this[0x29];
}



// ==== 00166792  NCDEEngine::usingCustomBase

/* NCDEEngine::usingCustomBase() const */

NCDEEngine __thiscall NCDEEngine::usingCustomBase(NCDEEngine *this)

{
  return this[0x2a];
}



// ==== 001667a4  NCDEEngine::fontSize_sm

/* NCDEEngine::fontSize_sm() const */

undefined4 __thiscall NCDEEngine::fontSize_sm(NCDEEngine *this)

{
  return *(undefined4 *)(this + 0x29c);
}



// ==== 001667b8  NCDEEngine::fontSize_md

/* NCDEEngine::fontSize_md() const */

undefined4 __thiscall NCDEEngine::fontSize_md(NCDEEngine *this)

{
  return *(undefined4 *)(this + 0x2a0);
}



// ==== 001667cc  NCDEEngine::fontSize_lg

/* NCDEEngine::fontSize_lg() const */

undefined4 __thiscall NCDEEngine::fontSize_lg(NCDEEngine *this)

{
  return *(undefined4 *)(this + 0x2a4);
}



// ==== 001667e0  NCDEEngine::letterSpacing

/* NCDEEngine::letterSpacing() const */

undefined4 __thiscall NCDEEngine::letterSpacing(NCDEEngine *this)

{
  return *(undefined4 *)(this + 0x2a8);
}



// ==== 001667f4  NCDEEngine::lineHeight

/* NCDEEngine::lineHeight() const */

undefined8 __thiscall NCDEEngine::lineHeight(NCDEEngine *this)

{
  return *(undefined8 *)(this + 0x2b0);
}



// ==== 0016680a  NCDEEngine::themeName

/* NCDEEngine::themeName() const */

QString * NCDEEngine::themeName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2b8));
  return in_RDI;
}



// ==== 0016683a  NCDEEngine::accentName

/* NCDEEngine::accentName() const */

QString * NCDEEngine::accentName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2d0));
  return in_RDI;
}



// ==== 0016686a  NCDEEngine::darkModeLock

/* NCDEEngine::darkModeLock() const */

QString * NCDEEngine::darkModeLock(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x2e8));
  return in_RDI;
}



// ==== 0016689a  NCDEEngine::overrideAccent

/* NCDEEngine::overrideAccent() const */

QString * NCDEEngine::overrideAccent(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x3b8));
  return in_RDI;
}



// ==== 001668ca  NCDEEngine::overrideAccentMuted

/* NCDEEngine::overrideAccentMuted() const */

QString * NCDEEngine::overrideAccentMuted(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x3d0));
  return in_RDI;
}



// ==== 001668fa  NCDEEngine::overrideBorder

/* NCDEEngine::overrideBorder() const */

QString * NCDEEngine::overrideBorder(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 1000));
  return in_RDI;
}



// ==== 0016692a  NCDEEngine::overrideGlow

/* NCDEEngine::overrideGlow() const */

QString * NCDEEngine::overrideGlow(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x400));
  return in_RDI;
}



// ==== 0016695a  NCDEEngine::bodyFont

/* NCDEEngine::bodyFont() const */

QString * NCDEEngine::bodyFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x418));
  return in_RDI;
}



// ==== 0016698a  NCDEEngine::titleFont

/* NCDEEngine::titleFont() const */

QString * NCDEEngine::titleFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x430));
  return in_RDI;
}



// ==== 001669ba  NCDEEngine::monoFont

/* NCDEEngine::monoFont() const */

QString * NCDEEngine::monoFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x448));
  return in_RDI;
}



// ==== 001669ea  NCDEEngine::displayFont

/* NCDEEngine::displayFont() const */

QString * NCDEEngine::displayFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x460));
  return in_RDI;
}



// ==== 00166a1a  NCDEEngine::fellFont

/* NCDEEngine::fellFont() const */

QString * NCDEEngine::fellFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x478));
  return in_RDI;
}



// ==== 00166a4a  NCDEEngine::garFont

/* NCDEEngine::garFont() const */

QString * NCDEEngine::garFont(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x490));
  return in_RDI;
}



// ==== 00166a7a  NCDEEngine::version

/* NCDEEngine::version() const */

NCDEEngine * __thiscall NCDEEngine::version(NCDEEngine *this)

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



// ==== 00166af8  NCDEEngine::wifiEnabled

/* NCDEEngine::wifiEnabled() const */

undefined8 __thiscall NCDEEngine::wifiEnabled(NCDEEngine *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x4c8) != 0) &&
     (cVar1 = Lelan::wifiEnabled(*(Lelan **)(this + 0x4c8)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 00166b3c  NCDEEngine::wifiNetworks

/* NCDEEngine::wifiNetworks() const */

QList<QVariant> * NCDEEngine::wifiNetworks(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00166bbe  NCDEEngine::activeNetwork

/* NCDEEngine::activeNetwork() const */

QMap<QString,QVariant> * NCDEEngine::activeNetwork(void)

{
  long lVar1;
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00166c3c  NCDEEngine::vpnConnections

/* NCDEEngine::vpnConnections() const */

QList<QVariant> * NCDEEngine::vpnConnections(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00166cbe  NCDEEngine::bluetoothEnabled

/* NCDEEngine::bluetoothEnabled() const */

undefined8 __thiscall NCDEEngine::bluetoothEnabled(NCDEEngine *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x4c8) != 0) &&
     (cVar1 = Lelan::bluetoothEnabled(*(Lelan **)(this + 0x4c8)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 00166d02  NCDEEngine::bluetoothDiscoverable

/* NCDEEngine::bluetoothDiscoverable() const */

undefined8 __thiscall NCDEEngine::bluetoothDiscoverable(NCDEEngine *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x4c8) != 0) &&
     (cVar1 = Lelan::bluetoothDiscoverable(*(Lelan **)(this + 0x4c8)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 00166d46  NCDEEngine::bluetoothDevices

/* NCDEEngine::bluetoothDevices() const */

QList<QVariant> * NCDEEngine::bluetoothDevices(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00166dc8  NCDEEngine::detectedTzName

/* NCDEEngine::detectedTzName() const */

QString * NCDEEngine::detectedTzName(void)

{
  long lVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00166e3a  NCDEEngine::detectedZone

/* NCDEEngine::detectedZone() const */

NCDEEngine * __thiscall NCDEEngine::detectedZone(NCDEEngine *this)

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



// ==== 00166e86  NCDEEngine::detectedRegion

/* NCDEEngine::detectedRegion() const */

undefined8 NCDEEngine::detectedRegion(void)

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



// ==== 00166f74  NCDEEngine::detectedOffset

/* NCDEEngine::detectedOffset() const */

QString * NCDEEngine::detectedOffset(void)

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
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00167326  NCDEEngine::localTime

/* NCDEEngine::localTime() const */

NCDEEngine * __thiscall NCDEEngine::localTime(NCDEEngine *this)

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



// ==== 0016742e  NCDEEngine::locating

/* NCDEEngine::locating() const */

undefined8 __thiscall NCDEEngine::locating(NCDEEngine *this)

{
  char cVar1;
  
  if ((*(long *)(this + 0x4c8) != 0) &&
     (cVar1 = Lelan::locating(*(Lelan **)(this + 0x4c8)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 00167470  NCDEEngine::users

/* NCDEEngine::users() const */

QList<QVariant> * NCDEEngine::users(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 001674f2  NCDEEngine::printers

/* NCDEEngine::printers() const */

QList<QVariant> * NCDEEngine::printers(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 00167574  NCDEEngine::appStreams

/* NCDEEngine::appStreams() const */

QList<QVariant> * NCDEEngine::appStreams(void)

{
  long lVar1;
  long in_RSI;
  QList<QVariant> *in_RDI;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x4c8) == 0) {
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



// ==== 001675f6  NCDEEngine::setDarkMode

/* NCDEEngine::setDarkMode(bool) */

void __thiscall NCDEEngine::setDarkMode(NCDEEngine *this,bool param_1)

{
  if ((NCDEEngine)param_1 != this[0x28]) {
    this[0x28] = (NCDEEngine)param_1;
    recompute(this);
    applyGtkTheme(this,param_1);
    applyGtkAccent();
    darkModeChanged(this);
  }
  return;
}



// ==== 00167658  NCDEEngine::setAccentName

/* NCDEEngine::setAccentName(QString const&) */

void __thiscall NCDEEngine::setAccentName(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator!=(param_1,(QString *)(this + 0x2d0));
  if (cVar1 != '\0') {
    QString::operator=((QString *)(this + 0x2d0),param_1);
    changed(this);
  }
  return;
}



// ==== 001676b0  NCDEEngine::setDarkModeLock

/* NCDEEngine::setDarkModeLock(QString const&) */

void __thiscall NCDEEngine::setDarkModeLock(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QLatin1String local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QString::operator=((QString *)(this + 0x2e8),param_1);
  QLatin1String::QLatin1String(local_28,"light");
  cVar1 = ::operator==(param_1,local_28);
  if (cVar1 == '\0') {
    QLatin1String::QLatin1String(local_28,"dark");
    cVar1 = ::operator==(param_1,local_28);
    if (cVar1 != '\0') {
      this[0x28] = (NCDEEngine)0x1;
    }
  }
  else {
    this[0x28] = (NCDEEngine)0x0;
  }
  recompute(this);
  applyGtkTheme(this,(bool)this[0x28]);
  applyGtkAccent();
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016779e  NCDEEngine::setBaseColor

/* NCDEEngine::setBaseColor(QColor const&, QColor const&, QColor const&) */

void __thiscall
NCDEEngine::setBaseColor(NCDEEngine *this,QColor *param_1,QColor *param_2,QColor *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long in_FS_OFFSET;
  float fVar4;
  float fVar5;
  undefined1 auVar6 [16];
  ColorMath local_58 [32];
  undefined6 local_38;
  undefined2 uStack_32;
  undefined6 local_30;
  undefined2 uStack_2a;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined8 *)(this + 0x4c) = *(undefined8 *)param_1;
  *(undefined8 *)(this + 0x52) = *(undefined8 *)(param_1 + 6);
  *(undefined8 *)(this + 0x5c) = *(undefined8 *)param_1;
  *(undefined8 *)(this + 0x62) = *(undefined8 *)(param_1 + 6);
  *(undefined8 *)(this + 0x8c) = *(undefined8 *)param_1;
  *(undefined8 *)(this + 0x92) = *(undefined8 *)(param_1 + 6);
  *(undefined8 *)(this + 0x300) = *(undefined8 *)param_2;
  *(undefined8 *)(this + 0x306) = *(undefined8 *)(param_2 + 6);
  *(undefined8 *)(this + 0xcc) = *(undefined8 *)param_3;
  *(undefined8 *)(this + 0xd2) = *(undefined8 *)(param_3 + 6);
  auVar6 = liteScale(param_2,0xf);
  local_38 = auVar6._0_6_;
  uStack_32 = auVar6._6_2_;
  local_30 = auVar6._8_6_;
  uStack_2a = auVar6._14_2_;
  *(long *)(this + 0x310) = auVar6._0_8_;
  *(long *)(this + 0x316) = auVar6._6_8_;
  iVar1 = QColor::blue();
  iVar2 = QColor::green();
  iVar3 = QColor::red();
  QColor::QColor((QColor *)&local_38,iVar3,iVar2,iVar1,0x66);
  *(ulong *)(this + 800) = CONCAT26(uStack_32,local_38);
  *(ulong *)(this + 0x326) = CONCAT62(local_30,uStack_32);
  this[0x2a] = (NCDEEngine)0x1;
  this[0x29] = (NCDEEngine)0x0;
  fVar4 = (float)QColor::lightnessF();
  fVar5 = (float)QColor::hueF();
  ColorMath::poeticName(local_58,(double)fVar5 * 360.0,(double)fVar4);
  QString::operator=((QString *)(this + 0x2d0),(QString *)local_58);
  QString::~QString((QString *)local_58);
  recompute(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00167994  NCDEEngine::clearCustomBase

/* NCDEEngine::clearCustomBase() */

void __thiscall NCDEEngine::clearCustomBase(NCDEEngine *this)

{
  this[0x2a] = (NCDEEngine)0x0;
  recompute(this);
  return;
}



// ==== 001679b8  NCDEEngine::presets

/* NCDEEngine::presets() const */

NCDEEngine * __thiscall NCDEEngine::presets(NCDEEngine *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_c0;
  char **local_b8;
  undefined **local_b0;
  char **local_a8;
  char **local_a0;
  undefined8 local_98;
  undefined8 local_90;
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])this = (undefined1  [16])0x0;
  *(undefined8 *)(this + 0x10) = 0;
  local_b0 = &ncde_presets::kPresets;
  local_a8 = (char **)&DAT_00314e50;
  for (local_b8 = &ncde_presets::kPresets; local_b8 != local_a8; local_b8 = local_b8 + 9) {
    local_a0 = local_b8;
    local_c0 = 0;
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_98,local_b8);
    QString::fromUtf8(local_68,local_98,local_90);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"id");
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_98,local_a0 + 1);
    QString::fromUtf8(local_68,local_98,local_90);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"name");
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_98,local_a0 + 3);
    QString::fromUtf8(local_68,local_98,local_90);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"accent");
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_88);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    ::QVariant::QVariant(local_48,*(bool *)(local_a0 + 2));
    QString::QString(local_68,"dark");
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,(QMap *)&local_c0);
    QList<QVariant>::append((QList<QVariant> *)this,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00167e44  NCDEEngine::applyPreset

/* NCDEEngine::applyPreset(QString const&) */

void __thiscall NCDEEngine::applyPreset(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long in_FS_OFFSET;
  undefined1 auVar5 [16];
  undefined **local_f0;
  undefined8 local_c8;
  undefined8 local_c0;
  QLatin1String local_b8 [32];
  undefined6 local_98;
  undefined2 uStack_92;
  undefined6 uStack_90;
  undefined6 local_88;
  undefined2 uStack_82;
  undefined6 uStack_80;
  undefined6 local_78;
  undefined2 uStack_72;
  undefined6 uStack_70;
  undefined6 local_68;
  undefined2 uStack_62;
  undefined6 uStack_60;
  undefined6 local_58;
  undefined2 uStack_52;
  undefined6 uStack_50;
  undefined6 local_48;
  undefined2 uStack_42;
  undefined6 uStack_40;
  undefined6 local_38;
  undefined2 uStack_32;
  undefined6 local_30;
  undefined2 uStack_2a;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = &ncde_presets::kPresets;
  do {
    if (local_f0 == (undefined **)&DAT_00314e50) {
LAB_00168577:
      if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    QLatin1String::QLatin1String(local_b8,*local_f0);
    cVar1 = ::operator!=(param_1,local_b8);
    if (cVar1 == '\0') {
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 3);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_98,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 4);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_88,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 5);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_78,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 6);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_68,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 7);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_58,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 8);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QColor::QColor((QColor *)&local_48,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      if (this[0x330] != (NCDEEngine)0x0) {
        auVar5 = mixLab((QColor *)&local_98,(QColor *)(this + 0x334),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_92 = uStack_32;
        uStack_90 = local_30;
        local_98 = local_38;
        auVar5 = mixLab((QColor *)&local_88,(QColor *)(this + 0x344),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_82 = uStack_32;
        uStack_80 = local_30;
        local_88 = local_38;
        auVar5 = mixLab((QColor *)&local_78,(QColor *)(this + 0x374),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_72 = uStack_32;
        uStack_70 = local_30;
        local_78 = local_38;
        auVar5 = mixLab((QColor *)&local_68,(QColor *)(this + 0x364),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_62 = uStack_32;
        uStack_60 = local_30;
        local_68 = local_38;
        auVar5 = mixLab((QColor *)&local_58,(QColor *)(this + 0x394),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_52 = uStack_32;
        uStack_50 = local_30;
        local_58 = local_38;
        auVar5 = mixLab((QColor *)&local_48,(QColor *)(this + 0x3a4),0.25);
        local_38 = auVar5._0_6_;
        uStack_32 = auVar5._6_2_;
        local_30 = auVar5._8_6_;
        uStack_2a = auVar5._14_2_;
        uStack_42 = uStack_32;
        uStack_40 = local_30;
        local_48 = local_38;
      }
      *(ulong *)(this + 0x300) = CONCAT26(uStack_92,local_98);
      *(ulong *)(this + 0x306) = CONCAT62(uStack_90,uStack_92);
      iVar2 = QColor::blue();
      iVar3 = QColor::green();
      iVar4 = QColor::red();
      QColor::QColor((QColor *)&local_38,iVar4,iVar3,iVar2,0x66);
      *(ulong *)(this + 800) = CONCAT26(uStack_32,local_38);
      *(ulong *)(this + 0x326) = CONCAT62(local_30,uStack_32);
      *(ulong *)(this + 0x310) = CONCAT26(uStack_82,local_88);
      *(ulong *)(this + 0x316) = CONCAT62(uStack_80,uStack_82);
      *(ulong *)(this + 0x8c) = CONCAT26(uStack_72,local_78);
      *(ulong *)(this + 0x92) = CONCAT62(uStack_70,uStack_72);
      *(undefined8 *)(this + 0x4c) = *(undefined8 *)(this + 0x8c);
      *(undefined8 *)(this + 0x52) = *(undefined8 *)(this + 0x92);
      *(ulong *)(this + 0x5c) = CONCAT26(uStack_62,local_68);
      *(ulong *)(this + 0x62) = CONCAT62(uStack_60,uStack_62);
      *(ulong *)(this + 0xcc) = CONCAT26(uStack_52,local_58);
      *(ulong *)(this + 0xd2) = CONCAT62(uStack_50,uStack_52);
      *(ulong *)(this + 0xdc) = CONCAT26(uStack_42,local_48);
      *(ulong *)(this + 0xe2) = CONCAT62(uStack_40,uStack_42);
      this[0x28] = *(NCDEEngine *)(local_f0 + 2);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 1);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QString::operator=((QString *)(this + 0x2b8),(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,local_f0 + 1);
      QString::fromUtf8(local_b8,local_c8,local_c0);
      QString::operator=((QString *)(this + 0x2d0),(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      this[0x29] = (NCDEEngine)0x1;
      this[0x2a] = (NCDEEngine)0x0;
      recompute(this);
      applyGtkTheme(this,(bool)this[0x28]);
      goto LAB_00168577;
    }
    local_f0 = local_f0 + 9;
  } while( true );
}



// ==== 00168598  NCDEEngine::currentBasePalette

/* NCDEEngine::currentBasePalette() const */

QMap<QString,QVariant> * NCDEEngine::currentBasePalette(void)

{
  QVariant *pQVar1;
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  long in_FS_OFFSET;
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined8 *)in_RDI = 0;
  QColor::name(local_68,in_RSI + 0x2c,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"accent");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,in_RSI + 0xac,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"border");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,in_RSI + 0x8c,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"panelBg");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,in_RSI + 0x5c,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"surface");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,in_RSI + 0xcc,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"ink");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,in_RSI + 0xdc,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"inkSoft");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  ::QVariant::QVariant(local_48,*(bool *)(in_RSI + 0x28));
  QString::QString(local_68,"dark");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 00168b7e  NCDEEngine::sampleWallpaper(QString_const&)::{lambda(NCDEEngine::Sample_const&,NCDEEngine::Sample_const&)#1}::operator()

/* NCDEEngine::sampleWallpaper(QString const&)::{lambda(NCDEEngine::Sample const&,
   NCDEEngine::Sample const&)#1}::TEMPNAMEPLACEHOLDERVALUE(NCDEEngine::Sample const&,
   NCDEEngine::Sample const&) const */

bool __thiscall
NCDEEngine::sampleWallpaper(QString_const&)::
{lambda(NCDEEngine::Sample_const&,NCDEEngine::Sample_const&)#1}::operator()
          (_lambda_NCDEEngine__Sample_const__NCDEEngine__Sample_const___1_ *this,Sample *param_1,
          Sample *param_2)

{
  return *(double *)(param_2 + 0x18) < *(double *)(param_1 + 0x18);
}



// ==== 00168c72  NCDEEngine::sampleWallpaper

/* NCDEEngine::sampleWallpaper(QString const&) */

undefined8 __thiscall NCDEEngine::sampleWallpaper(NCDEEngine *this,QString *param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  NCDEEngine NVar6;
  char cVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  uint *puVar12;
  undefined8 uVar13;
  int *piVar14;
  undefined8 *puVar15;
  double *pdVar16;
  undefined8 *puVar17;
  double *pdVar18;
  long lVar19;
  Lab *pLVar20;
  float *pfVar21;
  undefined8 uVar22;
  long in_FS_OFFSET;
  float fVar23;
  float fVar24;
  double dVar25;
  undefined1 auVar26 [16];
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  int local_1d4;
  int local_1d0;
  int local_1cc;
  int local_1c8;
  int local_1c4;
  int local_1c0;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  int local_1ac;
  uint local_1a8;
  uint local_1a4;
  QUrl local_1a0 [8];
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  double local_180;
  double local_178;
  double local_170;
  double local_168;
  QList<NCDEEngine::Sample> *local_160;
  Lab *local_158;
  double local_150;
  long local_148;
  undefined1 *local_140;
  QString local_138 [32];
  QImage local_118 [32];
  QList<NCDEEngine::Sample> local_f8 [16];
  undefined8 local_e8;
  QList<NCDEEngine::Lab> local_d8 [32];
  undefined4 local_b8 [8];
  undefined1 local_98 [2] [16];
  undefined1 local_78 [16];
  undefined8 local_68;
  double local_60;
  undefined6 local_58;
  undefined2 uStack_52;
  undefined6 local_50;
  undefined2 uStack_4a;
  undefined6 local_48;
  undefined2 uStack_42;
  undefined6 local_40;
  undefined2 uStack_3a;
  undefined6 local_38;
  undefined2 uStack_32;
  undefined6 local_30;
  undefined2 uStack_2a;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QUrl::QUrl(local_1a0,param_1,0);
  cVar7 = QUrl::isLocalFile();
  if (cVar7 == '\0') {
    QString::QString(local_138,param_1);
  }
  else {
    QUrl::toLocalFile();
  }
  QImage::QImage(local_118,local_138,(char *)0x0);
  cVar7 = QImage::isNull();
  if (cVar7 == '\0') {
    QFlags<Qt::ImageConversionFlag>::QFlags((QFlags<Qt::ImageConversionFlag> *)local_b8,0);
    QImage::convertToFormat(local_98,local_118,4,local_b8[0]);
    QImage::scaled(local_78,local_98,0xa0,0x78,0,1);
    QImage::operator=(local_118,(QImage *)local_78);
    QImage::~QImage((QImage *)local_78);
    QImage::~QImage((QImage *)local_98);
    local_198 = 0;
    local_1d4 = 0;
    while (iVar8 = QImage::height(), local_1d4 < iVar8) {
      local_148 = QImage::constScanLine((int)local_118);
      local_1d0 = 0;
      while (iVar8 = QImage::width(), local_1d0 < iVar8) {
        local_1a4 = *(uint *)(local_148 + (long)local_1d0 * 4);
        iVar8 = qRed(local_1a4);
        iVar10 = qGreen(local_1a4);
        iVar11 = qBlue(local_1a4);
        local_78._0_4_ = iVar11 >> 3 | (iVar8 >> 3) << 10 | (iVar10 >> 3) << 5;
        piVar14 = (int *)QHash<unsigned_int,int>::operator[]((uint *)&local_198);
        *piVar14 = *piVar14 + 1;
        local_1d0 = local_1d0 + 1;
      }
      local_1d4 = local_1d4 + 1;
    }
    local_f8[0] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[1] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[2] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[3] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[4] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[5] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[6] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[7] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[8] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[9] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[10] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[0xb] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[0xc] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[0xd] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[0xe] = (QList<NCDEEngine::Sample>)0x0;
    local_f8[0xf] = (QList<NCDEEngine::Sample>)0x0;
    local_e8 = 0;
    local_98[0] = QHash<unsigned_int,int>::constBegin((QHash<unsigned_int,int> *)&local_198);
    while( true ) {
      auVar26 = QHash<unsigned_int,int>::constEnd();
      local_78 = auVar26;
      cVar7 = QHash<unsigned_int,int>::const_iterator::operator!=
                        ((const_iterator *)local_98,(const_iterator *)local_78);
      if (cVar7 == '\0') break;
      puVar12 = (uint *)QHash<unsigned_int,int>::const_iterator::key((const_iterator *)local_98);
      local_1a8 = *puVar12;
      rgbToLab((local_1a8 >> 10 & 0x1f) << 3,(local_1a8 >> 5 & 0x1f) << 3,(local_1a8 & 0x1f) << 3,
               (Lab *)local_78);
      piVar14 = (int *)QHash<unsigned_int,int>::const_iterator::value((const_iterator *)local_98);
      local_60 = (double)*piVar14;
      QList<NCDEEngine::Sample>::append(local_f8,(Sample *)local_78);
      QHash<unsigned_int,int>::const_iterator::operator++((const_iterator *)local_98);
    }
    cVar7 = QList<NCDEEngine::Sample>::isEmpty(local_f8);
    if (cVar7 == '\0') {
      uVar22 = QList<NCDEEngine::Sample>::end(local_f8);
      uVar13 = QList<NCDEEngine::Sample>::begin(local_f8);
      std::
      sort<QList<NCDEEngine::Sample>::iterator,NCDEEngine::sampleWallpaper(QString_const&)::_lambda(NCDEEngine::Sample_const&,NCDEEngine::Sample_const&)_1_>
                (uVar13,uVar22);
      uVar9 = QList<NCDEEngine::Sample>::size(local_f8);
      local_78._0_4_ = uVar9;
      local_98[0]._0_4_ = 6;
      piVar14 = qMin<int>((int *)local_98,(int *)local_78);
      local_1ac = *piVar14;
      QList<NCDEEngine::Lab>::QList(local_d8,(long)local_1ac);
      QList<double>::QList((QList<double> *)local_b8,(long)local_1ac,0.0);
      for (local_1cc = 0; local_1cc < local_1ac; local_1cc = local_1cc + 1) {
        puVar17 = (undefined8 *)QList<NCDEEngine::Sample>::operator[](local_f8,(long)local_1cc);
        puVar15 = (undefined8 *)QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1cc);
        uVar22 = puVar17[1];
        *puVar15 = *puVar17;
        puVar15[1] = uVar22;
        puVar15[2] = puVar17[2];
      }
      for (local_1c8 = 0; local_1c8 < 0xc; local_1c8 = local_1c8 + 1) {
        local_78._0_8_ = 0;
        local_78._8_8_ = 0;
        local_68 = 0;
        QList<NCDEEngine::Lab>::QList
                  ((QList<NCDEEngine::Lab> *)local_98,(long)local_1ac,(Lab *)local_78);
        QList<double>::QList((QList<double> *)local_78,(long)local_1ac,0.0);
        local_160 = local_f8;
        local_190 = QList<NCDEEngine::Sample>::begin(local_160);
        local_188 = QList<NCDEEngine::Sample>::end(local_160);
        while (cVar7 = QList<NCDEEngine::Sample>::iterator::operator!=
                                 ((iterator *)&local_190,local_188), cVar7 != '\0') {
          local_158 = (Lab *)QList<NCDEEngine::Sample>::iterator::operator*((iterator *)&local_190);
          local_1c4 = 0;
          local_180 = 1e+18;
          for (local_1c0 = 0; local_1c0 < local_1ac; local_1c0 = local_1c0 + 1) {
            pLVar20 = (Lab *)QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1c0);
            local_150 = (double)labDist2(local_158,pLVar20);
            if (local_150 < local_180) {
              local_1c4 = local_1c0;
              local_180 = local_150;
            }
          }
          pdVar18 = (double *)
                    QList<NCDEEngine::Lab>::operator[]
                              ((QList<NCDEEngine::Lab> *)local_98,(long)local_1c4);
          *pdVar18 = *(double *)(local_158 + 0x18) * *(double *)local_158 + *pdVar18;
          lVar19 = QList<NCDEEngine::Lab>::operator[]
                             ((QList<NCDEEngine::Lab> *)local_98,(long)local_1c4);
          *(double *)(lVar19 + 8) =
               *(double *)(local_158 + 0x18) * *(double *)(local_158 + 8) + *(double *)(lVar19 + 8);
          lVar19 = QList<NCDEEngine::Lab>::operator[]
                             ((QList<NCDEEngine::Lab> *)local_98,(long)local_1c4);
          *(double *)(lVar19 + 0x10) =
               *(double *)(local_158 + 0x18) * *(double *)(local_158 + 0x10) +
               *(double *)(lVar19 + 0x10);
          pdVar18 = (double *)QList<double>::operator[]((QList<double> *)local_78,(long)local_1c4);
          *pdVar18 = *(double *)(local_158 + 0x18) + *pdVar18;
          QList<NCDEEngine::Sample>::iterator::operator++((iterator *)&local_190);
        }
        for (local_1bc = 0; local_1bc < local_1ac; local_1bc = local_1bc + 1) {
          pdVar18 = (double *)QList<double>::operator[]((QList<double> *)local_78,(long)local_1bc);
          if (0.0 < *pdVar18) {
            pdVar18 = (double *)QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1bc);
            pdVar16 = (double *)
                      QList<NCDEEngine::Lab>::operator[]
                                ((QList<NCDEEngine::Lab> *)local_98,(long)local_1bc);
            dVar25 = *pdVar16;
            pdVar16 = (double *)QList<double>::operator[]((QList<double> *)local_78,(long)local_1bc)
            ;
            dVar4 = *pdVar16;
            lVar19 = QList<NCDEEngine::Lab>::operator[]
                               ((QList<NCDEEngine::Lab> *)local_98,(long)local_1bc);
            dVar5 = *(double *)(lVar19 + 8);
            pdVar16 = (double *)QList<double>::operator[]((QList<double> *)local_78,(long)local_1bc)
            ;
            dVar1 = *pdVar16;
            lVar19 = QList<NCDEEngine::Lab>::operator[]
                               ((QList<NCDEEngine::Lab> *)local_98,(long)local_1bc);
            dVar2 = *(double *)(lVar19 + 0x10);
            pdVar16 = (double *)QList<double>::operator[]((QList<double> *)local_78,(long)local_1bc)
            ;
            dVar3 = *pdVar16;
            *pdVar18 = dVar25 / dVar4;
            pdVar18[1] = dVar5 / dVar1;
            pdVar18[2] = dVar2 / dVar3;
            puVar17 = (undefined8 *)
                      QList<double>::operator[]((QList<double> *)local_78,(long)local_1bc);
            uVar22 = *puVar17;
            puVar17 = (undefined8 *)
                      QList<double>::operator[]((QList<double> *)local_b8,(long)local_1bc);
            *puVar17 = uVar22;
          }
        }
        QList<double>::~QList((QList<double> *)local_78);
        QList<NCDEEngine::Lab>::~QList((QList<NCDEEngine::Lab> *)local_98);
      }
      local_1b8 = 0;
      local_1b4 = 0;
      local_178 = -1.0;
      local_170 = -1.0;
      for (local_1b0 = 0; local_1b0 < local_1ac; local_1b0 = local_1b0 + 1) {
        pdVar18 = (double *)QList<double>::operator[]((QList<double> *)local_b8,(long)local_1b0);
        if (local_178 < *pdVar18) {
          pdVar18 = (double *)QList<double>::operator[]((QList<double> *)local_b8,(long)local_1b0);
          local_178 = *pdVar18;
          local_1b8 = local_1b0;
        }
        lVar19 = QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b0);
        dVar25 = *(double *)(lVar19 + 8);
        lVar19 = QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b0);
        dVar4 = *(double *)(lVar19 + 8);
        lVar19 = QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b0);
        dVar5 = *(double *)(lVar19 + 0x10);
        lVar19 = QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b0);
        local_168 = *(double *)(lVar19 + 0x10) * dVar5 + dVar4 * dVar25;
        pdVar18 = (double *)QList<double>::operator[]((QList<double> *)local_b8,(long)local_1b0);
        if (*pdVar18 <= 0.0) {
          dVar25 = 0.0;
        }
        else {
          dVar25 = 1.0;
        }
        if (local_170 < dVar25 * local_168) {
          local_170 = local_168;
          local_1b4 = local_1b0;
        }
      }
      pLVar20 = (Lab *)QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b8);
      auVar26 = labToColor(pLVar20);
      local_58 = auVar26._0_6_;
      uStack_52 = auVar26._6_2_;
      local_50 = auVar26._8_6_;
      uStack_4a = auVar26._14_2_;
      pLVar20 = (Lab *)QList<NCDEEngine::Lab>::operator[](local_d8,(long)local_1b4);
      auVar26 = labToColor(pLVar20);
      local_48 = auVar26._0_6_;
      uStack_42 = auVar26._6_2_;
      local_40 = auVar26._8_6_;
      uStack_3a = auVar26._14_2_;
      QColor::getHsvF((float *)&local_48,&local_1e4,&local_1e0,&local_1dc);
      if (local_1e4 < 0.0) {
        fVar23 = (float)QColor::hueF();
        if (0.0 <= fVar23) {
          local_1e4 = (float)QColor::hueF();
        }
        else {
          local_1e4 = 0.0;
        }
      }
      local_78._0_4_ = 0x3f6b851f;
      local_98[0]._0_4_ = 0x3f0ccccd;
      pfVar21 = qBound<float>((float *)local_98,&local_1dc,(float *)local_78);
      fVar23 = *pfVar21;
      local_188 = CONCAT44(local_188._4_4_,0x3f733333);
      local_190 = CONCAT44(local_190._4_4_,0x3ee66666);
      pfVar21 = qBound<float>((float *)&local_190,&local_1e0,(float *)&local_188);
      fVar24 = *pfVar21;
      local_1d8 = 0.0;
      pfVar21 = qMax<float>(&local_1d8,&local_1e4);
      auVar26 = QColor::fromHsvF(*pfVar21,fVar24,fVar23,1.0);
      local_38 = auVar26._0_6_;
      uStack_32 = auVar26._6_2_;
      local_30 = auVar26._8_6_;
      uStack_2a = auVar26._14_2_;
      uStack_42 = uStack_32;
      local_40 = local_30;
      *(long *)(this + 0x300) = auVar26._0_8_;
      *(long *)(this + 0x306) = auVar26._6_8_;
      local_48 = local_38;
      iVar8 = QColor::blue();
      iVar10 = QColor::green();
      iVar11 = QColor::red();
      QColor::QColor((QColor *)&local_38,iVar11,iVar10,iVar8,0x66);
      *(ulong *)(this + 800) = CONCAT26(uStack_32,local_38);
      *(ulong *)(this + 0x326) = CONCAT62(local_30,uStack_32);
      auVar26 = liteScale((QColor *)&local_48,0xf);
      local_38 = auVar26._0_6_;
      uStack_32 = auVar26._6_2_;
      local_30 = auVar26._8_6_;
      uStack_2a = auVar26._14_2_;
      *(long *)(this + 0x310) = auVar26._0_8_;
      *(long *)(this + 0x316) = auVar26._6_8_;
      auVar26 = darkScale((QColor *)&local_48,0xc);
      local_38 = auVar26._0_6_;
      uStack_32 = auVar26._6_2_;
      local_30 = auVar26._8_6_;
      uStack_2a = auVar26._14_2_;
      *(long *)(this + 0xdc) = auVar26._0_8_;
      *(long *)(this + 0xe2) = auVar26._6_8_;
      dVar25 = (double)brightness((QColor *)&local_58);
      NVar6 = (NCDEEngine)(dVar25 < 0.45);
      this[0x28] = NVar6;
      *(ulong *)(this + 0x5c) = CONCAT26(uStack_52,local_58);
      *(ulong *)(this + 0x62) = CONCAT62(local_50,uStack_52);
      if ((bool)NVar6) {
        auVar26 = liteScale((QColor *)&local_58,0x37);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      else {
        auVar26 = darkScale((QColor *)&local_58,0x23);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      *(ulong *)(this + 0x8c) = CONCAT26(uStack_32,local_38);
      *(ulong *)(this + 0x92) = CONCAT62(local_30,uStack_32);
      *(undefined8 *)(this + 0x4c) = *(undefined8 *)(this + 0x8c);
      *(undefined8 *)(this + 0x52) = *(undefined8 *)(this + 0x92);
      if ((bool)NVar6) {
        auVar26 = liteScale((QColor *)&local_58,0x46);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      else {
        auVar26 = darkScale((QColor *)&local_58,0x14);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      *(ulong *)(this + 0x9c) = CONCAT26(uStack_32,local_38);
      *(ulong *)(this + 0xa2) = CONCAT62(local_30,uStack_32);
      if ((bool)NVar6) {
        auVar26 = darkScale((QColor *)&local_48,0x50);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      else {
        auVar26 = liteScale((QColor *)&local_48,0x50);
        local_38 = auVar26._0_6_;
        uStack_32 = auVar26._6_2_;
        local_30 = auVar26._8_6_;
        uStack_2a = auVar26._14_2_;
      }
      *(ulong *)(this + 0xcc) = CONCAT26(uStack_32,local_38);
      *(ulong *)(this + 0xd2) = CONCAT62(local_30,uStack_32);
      this[0x2a] = (NCDEEngine)0x1;
      this[0x29] = (NCDEEngine)0x0;
      local_140 = &LAB_00299733_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"From Wallpaper",
                 0xe);
      QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
      QString::operator=((QString *)(this + 0x2b8),(QString *)local_78);
      QString::~QString((QString *)local_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
      fVar23 = (float)QColor::lightnessF();
      fVar24 = (float)QColor::hsvHueF();
      ColorMath::poeticName((ColorMath *)local_78,(double)fVar24 * 360.0,(double)fVar23);
      QString::operator=((QString *)(this + 0x2d0),(QString *)local_78);
      QString::~QString((QString *)local_78);
      *(undefined8 *)(this + 0x334) = *(undefined8 *)(this + 0x300);
      *(undefined8 *)(this + 0x33a) = *(undefined8 *)(this + 0x306);
      *(undefined8 *)(this + 0x344) = *(undefined8 *)(this + 0x310);
      *(undefined8 *)(this + 0x34a) = *(undefined8 *)(this + 0x316);
      *(undefined8 *)(this + 0x354) = *(undefined8 *)(this + 800);
      *(undefined8 *)(this + 0x35a) = *(undefined8 *)(this + 0x326);
      *(undefined8 *)(this + 0x364) = *(undefined8 *)(this + 0x5c);
      *(undefined8 *)(this + 0x36a) = *(undefined8 *)(this + 0x62);
      *(undefined8 *)(this + 0x374) = *(undefined8 *)(this + 0x4c);
      *(undefined8 *)(this + 0x37a) = *(undefined8 *)(this + 0x52);
      *(undefined8 *)(this + 900) = *(undefined8 *)(this + 0x9c);
      *(undefined8 *)(this + 0x38a) = *(undefined8 *)(this + 0xa2);
      *(undefined8 *)(this + 0x394) = *(undefined8 *)(this + 0xcc);
      *(undefined8 *)(this + 0x39a) = *(undefined8 *)(this + 0xd2);
      *(undefined8 *)(this + 0x3a4) = *(undefined8 *)(this + 0xdc);
      *(undefined8 *)(this + 0x3aa) = *(undefined8 *)(this + 0xe2);
      this[0x3b4] = this[0x28];
      this[0x330] = (NCDEEngine)0x1;
      recompute(this);
      applyGtkTheme(this,(bool)this[0x28]);
      applyGtkAccent();
      currentBasePalette();
      previewReady(this,(QMap *)local_78);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_78);
      uVar22 = 1;
      QList<double>::~QList((QList<double> *)local_b8);
      QList<NCDEEngine::Lab>::~QList(local_d8);
    }
    else {
      uVar22 = 0;
    }
    QList<NCDEEngine::Sample>::~QList(local_f8);
    QHash<unsigned_int,int>::~QHash((QHash<unsigned_int,int> *)&local_198);
  }
  else {
    uVar22 = 0;
  }
  QImage::~QImage(local_118);
  QString::~QString(local_138);
  QUrl::~QUrl(local_1a0);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar22;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0016a02e  NCDEEngine::previewWallpaper

/* NCDEEngine::previewWallpaper(QString const&) */

QString * NCDEEngine::previewWallpaper(QString *param_1)

{
  NCDEEngine NVar1;
  NCDEEngine NVar2;
  NCDEEngine NVar3;
  char cVar4;
  QString *in_RDX;
  NCDEEngine *in_RSI;
  long in_FS_OFFSET;
  QMap local_f0 [8];
  QString local_e8 [32];
  QString local_c8 [32];
  undefined6 local_a8;
  undefined2 uStack_a2;
  undefined6 local_a0;
  undefined2 uStack_9a;
  undefined6 local_98;
  undefined2 uStack_92;
  undefined6 local_90;
  undefined2 uStack_8a;
  undefined6 local_88;
  undefined2 uStack_82;
  undefined6 local_80;
  undefined2 uStack_7a;
  undefined6 local_78;
  undefined2 uStack_72;
  undefined6 local_70;
  undefined2 uStack_6a;
  undefined6 local_68;
  undefined2 uStack_62;
  undefined6 local_60;
  undefined2 uStack_5a;
  undefined6 local_58;
  undefined2 uStack_52;
  undefined6 local_50;
  undefined2 uStack_4a;
  undefined6 local_48;
  undefined2 uStack_42;
  undefined6 local_40;
  undefined2 uStack_3a;
  undefined6 local_38;
  undefined2 uStack_32;
  undefined6 local_30;
  undefined2 uStack_2a;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a8 = (undefined6)*(undefined8 *)(in_RSI + 0x300);
  uStack_a2 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x300) >> 0x30);
  local_a0 = (undefined6)*(undefined8 *)(in_RSI + 0x308);
  uStack_9a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x308) >> 0x30);
  local_98 = (undefined6)*(undefined8 *)(in_RSI + 0x310);
  uStack_92 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x310) >> 0x30);
  local_90 = (undefined6)*(undefined8 *)(in_RSI + 0x318);
  uStack_8a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x318) >> 0x30);
  local_88 = (undefined6)*(undefined8 *)(in_RSI + 800);
  uStack_82 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 800) >> 0x30);
  local_80 = (undefined6)*(undefined8 *)(in_RSI + 0x328);
  uStack_7a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x328) >> 0x30);
  local_78 = (undefined6)*(undefined8 *)(in_RSI + 0x5c);
  uStack_72 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x5c) >> 0x30);
  local_70 = (undefined6)*(undefined8 *)(in_RSI + 100);
  uStack_6a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 100) >> 0x30);
  local_68 = (undefined6)*(undefined8 *)(in_RSI + 0x4c);
  uStack_62 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x4c) >> 0x30);
  local_60 = (undefined6)*(undefined8 *)(in_RSI + 0x54);
  uStack_5a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x54) >> 0x30);
  local_58 = (undefined6)*(undefined8 *)(in_RSI + 0x9c);
  uStack_52 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0x9c) >> 0x30);
  local_50 = (undefined6)*(undefined8 *)(in_RSI + 0xa4);
  uStack_4a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0xa4) >> 0x30);
  local_48 = (undefined6)*(undefined8 *)(in_RSI + 0xcc);
  uStack_42 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0xcc) >> 0x30);
  local_40 = (undefined6)*(undefined8 *)(in_RSI + 0xd4);
  uStack_3a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0xd4) >> 0x30);
  local_38 = (undefined6)*(undefined8 *)(in_RSI + 0xdc);
  uStack_32 = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0xdc) >> 0x30);
  local_30 = (undefined6)*(undefined8 *)(in_RSI + 0xe4);
  uStack_2a = (undefined2)((ulong)*(undefined8 *)(in_RSI + 0xe4) >> 0x30);
  NVar1 = in_RSI[0x28];
  NVar2 = in_RSI[0x2a];
  NVar3 = in_RSI[0x29];
  QString::QString(local_e8,(QString *)(in_RSI + 0x2b8));
  QString::QString(local_c8,(QString *)(in_RSI + 0x2d0));
  *(undefined8 *)param_1 = 0;
  cVar4 = sampleWallpaper(in_RSI,in_RDX);
  if (cVar4 != '\0') {
    currentBasePalette();
    QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)param_1,local_f0);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f0);
  }
  *(ulong *)(in_RSI + 0x300) = CONCAT26(uStack_a2,local_a8);
  *(ulong *)(in_RSI + 0x306) = CONCAT62(local_a0,uStack_a2);
  *(ulong *)(in_RSI + 0x310) = CONCAT26(uStack_92,local_98);
  *(ulong *)(in_RSI + 0x316) = CONCAT62(local_90,uStack_92);
  *(ulong *)(in_RSI + 800) = CONCAT26(uStack_82,local_88);
  *(ulong *)(in_RSI + 0x326) = CONCAT62(local_80,uStack_82);
  *(ulong *)(in_RSI + 0x5c) = CONCAT26(uStack_72,local_78);
  *(ulong *)(in_RSI + 0x62) = CONCAT62(local_70,uStack_72);
  *(ulong *)(in_RSI + 0x8c) = CONCAT26(uStack_62,local_68);
  *(ulong *)(in_RSI + 0x92) = CONCAT62(local_60,uStack_62);
  *(undefined8 *)(in_RSI + 0x4c) = *(undefined8 *)(in_RSI + 0x8c);
  *(undefined8 *)(in_RSI + 0x52) = *(undefined8 *)(in_RSI + 0x92);
  *(ulong *)(in_RSI + 0x9c) = CONCAT26(uStack_52,local_58);
  *(ulong *)(in_RSI + 0xa2) = CONCAT62(local_50,uStack_52);
  *(ulong *)(in_RSI + 0xcc) = CONCAT26(uStack_42,local_48);
  *(ulong *)(in_RSI + 0xd2) = CONCAT62(local_40,uStack_42);
  *(ulong *)(in_RSI + 0xdc) = CONCAT26(uStack_32,local_38);
  *(ulong *)(in_RSI + 0xe2) = CONCAT62(local_30,uStack_32);
  in_RSI[0x28] = NVar1;
  in_RSI[0x2a] = NVar2;
  in_RSI[0x29] = NVar3;
  QString::operator=((QString *)(in_RSI + 0x2b8),local_e8);
  QString::operator=((QString *)(in_RSI + 0x2d0),local_c8);
  recompute(in_RSI);
  QString::~QString(local_c8);
  QString::~QString(local_e8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0016a44a  NCDEEngine::previewWallpaperAsync

/* NCDEEngine::previewWallpaperAsync(QString const&) */

void NCDEEngine::previewWallpaperAsync(QString *param_1)

{
  long in_FS_OFFSET;
  QString local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  previewWallpaper(local_28);
  previewReady((NCDEEngine *)param_1,(QMap *)local_28);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016a4ec  NCDEEngine::setSurfaceGlass

/* NCDEEngine::setSurfaceGlass(QString const&, QColor const&, double, double, QColor const&, QColor
   const&) */

void __thiscall
NCDEEngine::setSurfaceGlass
          (NCDEEngine *this,QString *param_1,QColor *param_2,double param_3,double param_4,
          QColor *param_5,QColor *param_6)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_90;
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_90 = 0;
  QColor::name(local_68,param_2,1);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"tint");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  ::QVariant::QVariant(local_48,param_3);
  QString::QString(local_68,"shine");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_4);
  QString::QString(local_68,"glow");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  QColor::name(local_68,param_5,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"border");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,param_6,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"glowColor");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QHash<QString,QMap<QString,QVariant>>::insert
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4b8),param_1,(QMap *)&local_90);
  changed(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_90);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016a93e  NCDEEngine::surfaceGlass

/* NCDEEngine::surfaceGlass(QString const&) const */

QString * NCDEEngine::surfaceGlass(QString *param_1)

{
  char cVar1;
  QVariant *pQVar2;
  QString *in_RDX;
  long in_RSI;
  long in_FS_OFFSET;
  undefined8 local_90;
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QHash<QString,QMap<QString,QVariant>>::contains
                    ((QHash<QString,QMap<QString,QVariant>> *)(in_RSI + 0x4b8),in_RDX);
  if (cVar1 == '\0') {
    local_90 = 0;
    QColor::name(local_68,in_RSI + 0x8c,1);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"tint");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    ::QVariant::QVariant(local_48,0.35);
    QString::QString(local_68,"shine");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,0.5);
    QString::QString(local_68,"glow");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
    QColor::name(local_68,in_RSI + 0xac,0);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"border");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    QColor::name(local_68,in_RSI + 0xbc,0);
    ::QVariant::QVariant(local_48,local_68);
    QString::QString(local_88,"glowColor");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_90,local_88);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_48);
    QString::~QString(local_68);
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)param_1,(QMap *)&local_90);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_90);
  }
  else {
    QHash<QString,QMap<QString,QVariant>>::value(param_1);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0016adbe  NCDEEngine::setWidgetStyleMap

/* NCDEEngine::setWidgetStyleMap(QString const&, QMap<QString, QVariant> const&) */

void __thiscall NCDEEngine::setWidgetStyleMap(NCDEEngine *this,QString *param_1,QMap *param_2)

{
  QHash<QString,QMap<QString,QVariant>>::insert
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0),param_1,param_2);
  changed(this);
  return;
}



// ==== 0016ae00  NCDEEngine::setWidgetStyle

/* NCDEEngine::setWidgetStyle(QString const&, QColor const&, QColor const&, QString const&) */

void __thiscall
NCDEEngine::setWidgetStyle
          (NCDEEngine *this,QString *param_1,QColor *param_2,QColor *param_3,QString *param_4)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_90 [8];
  QString local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QMap<QString,QVariant>>::value(local_90);
  QColor::name(local_68,param_2,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"accent");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_90,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,param_3,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString(local_88,"fill");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_90,local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  ::QVariant::QVariant(local_48,param_4);
  QString::QString(local_68,"font");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_90,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  QHash<QString,QMap<QString,QVariant>>::insert
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0),param_1,(QMap *)local_90);
  changed(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_90);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016b108  NCDEEngine::widgetStyle

/* NCDEEngine::widgetStyle(QString const&) const */

QString * NCDEEngine::widgetStyle(QString *param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  QHash<QString,QMap<QString,QVariant>>::value(param_1);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0016b164  NCDEEngine::resetWidgetStyle

/* NCDEEngine::resetWidgetStyle(QString const&) */

void __thiscall NCDEEngine::resetWidgetStyle(NCDEEngine *this,QString *param_1)

{
  QHash<QString,QMap<QString,QVariant>>::remove
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0),param_1);
  changed(this);
  return;
}



// ==== 0016b19e  NCDEEngine::loadPersistedFiligree

/* NCDEEngine::loadPersistedFiligree() */

void __thiscall NCDEEngine::loadPersistedFiligree(NCDEEngine *this)

{
  char cVar1;
  QString *pQVar2;
  long in_FS_OFFSET;
  QString local_78 [8];
  QString local_70 [8];
  undefined1 *local_68;
  undefined1 *local_60;
  undefined8 local_58 [4];
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_68 = &LAB_00299776;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,L"glass-surfaces",0xe);
  QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
  Lelan::readConfig(local_78);
  QString::~QString((QString *)local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_58);
  local_58[0] = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)local_78);
  while( true ) {
    local_38[0] = QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)local_78);
    cVar1 = ::operator!=((const_iterator *)local_58,(const_iterator *)local_38);
    if (cVar1 == '\0') break;
    QMap<QString,QVariant>::const_iterator::value((const_iterator *)local_58);
    ::QVariant::toMap();
    pQVar2 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_58);
    QHash<QString,QMap<QString,QVariant>>::insert
              ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4b8),pQVar2,(QMap *)local_38);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_38);
    QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_58);
  }
  local_60 = &LAB_00299794;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,L"widget-styles",0xd);
  QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
  Lelan::readConfig(local_70);
  QString::~QString((QString *)local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_58);
  local_58[0] = QMap<QString,QVariant>::constBegin((QMap<QString,QVariant> *)local_70);
  while( true ) {
    local_38[0] = QMap<QString,QVariant>::constEnd((QMap<QString,QVariant> *)local_70);
    cVar1 = ::operator!=((const_iterator *)local_58,(const_iterator *)local_38);
    if (cVar1 == '\0') break;
    QMap<QString,QVariant>::const_iterator::value((const_iterator *)local_58);
    ::QVariant::toMap();
    pQVar2 = (QString *)QMap<QString,QVariant>::const_iterator::key((const_iterator *)local_58);
    QHash<QString,QMap<QString,QVariant>>::insert
              ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0),pQVar2,(QMap *)local_38);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_38);
    QMap<QString,QVariant>::const_iterator::operator++((const_iterator *)local_58);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_70);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_78);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016b4b2  NCDEEngine::setOverrideAccent

/* NCDEEngine::setOverrideAccent(QString const&) */

void __thiscall NCDEEngine::setOverrideAccent(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x3b8),param_1);
  scheduleRecompute(this);
  return;
}



// ==== 0016b4ec  NCDEEngine::setOverrideAccentMuted

/* NCDEEngine::setOverrideAccentMuted(QString const&) */

void __thiscall NCDEEngine::setOverrideAccentMuted(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x3d0),param_1);
  scheduleRecompute(this);
  return;
}



// ==== 0016b526  NCDEEngine::setOverrideBorder

/* NCDEEngine::setOverrideBorder(QString const&) */

void __thiscall NCDEEngine::setOverrideBorder(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 1000),param_1);
  scheduleRecompute(this);
  return;
}



// ==== 0016b560  NCDEEngine::setOverrideGlow

/* NCDEEngine::setOverrideGlow(QString const&) */

void __thiscall NCDEEngine::setOverrideGlow(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x400),param_1);
  scheduleRecompute(this);
  return;
}



// ==== 0016b59a  NCDEEngine::setBodyFont

/* NCDEEngine::setBodyFont(QString const&) */

void __thiscall NCDEEngine::setBodyFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x418),param_1);
  changed(this);
  return;
}



// ==== 0016b5d4  NCDEEngine::setTitleFont

/* NCDEEngine::setTitleFont(QString const&) */

void __thiscall NCDEEngine::setTitleFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x430),param_1);
  changed(this);
  return;
}



// ==== 0016b60e  NCDEEngine::setMonoFont

/* NCDEEngine::setMonoFont(QString const&) */

void __thiscall NCDEEngine::setMonoFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x448),param_1);
  changed(this);
  return;
}



// ==== 0016b648  NCDEEngine::setDisplayFont

/* NCDEEngine::setDisplayFont(QString const&) */

void __thiscall NCDEEngine::setDisplayFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x460),param_1);
  changed(this);
  return;
}



// ==== 0016b682  NCDEEngine::setFellFont

/* NCDEEngine::setFellFont(QString const&) */

void __thiscall NCDEEngine::setFellFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x478),param_1);
  changed(this);
  return;
}



// ==== 0016b6bc  NCDEEngine::setGarFont

/* NCDEEngine::setGarFont(QString const&) */

void __thiscall NCDEEngine::setGarFont(NCDEEngine *this,QString *param_1)

{
  QString::operator=((QString *)(this + 0x490),param_1);
  changed(this);
  return;
}



// ==== 0016b6f6  NCDEEngine::setUiScale

/* NCDEEngine::setUiScale(double) */

void __thiscall NCDEEngine::setUiScale(NCDEEngine *this,double param_1)

{
  *(double *)(this + 0x4a8) = param_1;
  recomputeFontSizes(this);
  return;
}



// ==== 0016b728  NCDEEngine::setFontSizeScale

/* NCDEEngine::setFontSizeScale(double) */

void __thiscall NCDEEngine::setFontSizeScale(NCDEEngine *this,double param_1)

{
  *(double *)(this + 0x4b0) = param_1;
  recomputeFontSizes(this);
  return;
}



// ==== 0016b75a  NCDEEngine::setLetterSpacing

/* NCDEEngine::setLetterSpacing(double) */

void __thiscall NCDEEngine::setLetterSpacing(NCDEEngine *this,double param_1)

{
  *(int *)(this + 0x2a8) = (int)param_1;
  changed(this);
  return;
}



// ==== 0016b78e  NCDEEngine::setLineHeight

/* NCDEEngine::setLineHeight(double) */

void __thiscall NCDEEngine::setLineHeight(NCDEEngine *this,double param_1)

{
  *(double *)(this + 0x2b0) = param_1;
  changed(this);
  return;
}



// ==== 0016b7c0  NCDEEngine::recomputeFontSizes

/* NCDEEngine::recomputeFontSizes() */

void __thiscall NCDEEngine::recomputeFontSizes(NCDEEngine *this)

{
  int *piVar1;
  long in_FS_OFFSET;
  int local_20;
  int local_1c;
  double local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = *(double *)(this + 0x4b0) * *(double *)(this + 0x4a8);
  local_1c = qRound(local_18 * 11.0);
  local_20 = 1;
  piVar1 = qMax<int>(&local_20,&local_1c);
  *(int *)(this + 0x29c) = *piVar1;
  local_1c = qRound(local_18 * 14.0);
  local_20 = 1;
  piVar1 = qMax<int>(&local_20,&local_1c);
  *(int *)(this + 0x2a0) = *piVar1;
  local_1c = qRound(local_18 * 20.0);
  local_20 = 1;
  piVar1 = qMax<int>(&local_20,&local_1c);
  *(int *)(this + 0x2a4) = *piVar1;
  changed(this);
  themeChanged(this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016b906  NCDEEngine::toJson

/* NCDEEngine::toJson() const */

QMap<QString,QVariant> * NCDEEngine::toJson(void)

{
  QVariant *pQVar1;
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  long in_FS_OFFSET;
  bool bVar2;
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  QVariant local_58 [40];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined8 *)in_RDI = 0;
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x2d0));
  QString::QString(local_78,"accent");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  QColor::name(local_78,in_RSI + 0x300,0);
  ::QVariant::QVariant(local_58,local_78);
  QString::QString(local_98,"customAccent");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_98);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_98);
  ::QVariant::~QVariant(local_58);
  QString::~QString(local_78);
  QColor::name(local_78,in_RSI + 0x4c,0);
  ::QVariant::QVariant(local_58,local_78);
  QString::QString(local_98,"customBase");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_98);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_98);
  ::QVariant::~QVariant(local_58);
  QString::~QString(local_78);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x2e8));
  QString::QString(local_78,"darkModeLock");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  bVar2 = *(char *)(in_RSI + 0x28) == '\0';
  if (bVar2) {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"light",5);
    QString::QString(local_78,(QArrayDataPointer *)local_98);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_b8,(QTypedArrayData *)0x0,L"dark",4);
    QString::QString(local_78,(QArrayDataPointer *)local_b8);
  }
  ::QVariant::QVariant(local_58,local_78);
  QString::QString(local_d8,"mode");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_d8);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_d8);
  ::QVariant::~QVariant(local_58);
  QString::~QString(local_78);
  if (bVar2) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  }
  QColor::name(local_78,in_RSI + 0xcc,0);
  ::QVariant::QVariant(local_58,local_78);
  QString::QString(local_98,"sampledPanelText");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_98);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_98);
  ::QVariant::~QVariant(local_58);
  QString::~QString(local_78);
  ::QVariant::QVariant(local_58,*(bool *)(in_RSI + 0x2a));
  QString::QString(local_78,"usingCustomBase");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x418));
  QString::QString(local_78,"bodyFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x430));
  QString::QString(local_78,"titleFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x448));
  QString::QString(local_78,"monoFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x460));
  QString::QString(local_78,"displayFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x478));
  QString::QString(local_78,"fellFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  ::QVariant::QVariant(local_58,(QString *)(in_RSI + 0x490));
  QString::QString(local_78,"garFont");
  pQVar1 = (QVariant *)QMap<QString,QVariant>::operator[](in_RDI,local_78);
  ::QVariant::operator=(pQVar1,local_58);
  QString::~QString(local_78);
  ::QVariant::~QVariant(local_58);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return in_RDI;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0016c31e  NCDEEngine::saveTheme

/* NCDEEngine::saveTheme(QString const&) const */

bool __thiscall NCDEEngine::saveTheme(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QMap<QString,QVariant> local_80 [8];
  QMap local_78 [8];
  QJsonDocument local_70 [8];
  QUrl local_68 [16];
  QString local_58 [32];
  QUrl local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QUrl::QUrl(local_68,param_1,0);
  cVar1 = QUrl::isLocalFile();
  if (cVar1 == '\0') {
    QString::QString(local_58,param_1);
  }
  else {
    QUrl::QUrl(local_38,param_1,0);
    QUrl::toLocalFile();
    QUrl::~QUrl(local_38);
  }
  QUrl::~QUrl(local_68);
  QFile::QFile((QFile *)local_68,local_58);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_68,uVar2);
  if (cVar1 == '\x01') {
    toJson();
    QJsonObject::fromVariantMap(local_78);
    QJsonDocument::QJsonDocument(local_70,(QJsonObject *)local_78);
    QJsonDocument::toJson(local_38,local_70,0);
    QIODevice::write((QByteArray *)local_68);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QJsonDocument::~QJsonDocument(local_70);
    QJsonObject::~QJsonObject((QJsonObject *)local_78);
    QMap<QString,QVariant>::~QMap(local_80);
    QFileDevice::close();
  }
  QFile::~QFile((QFile *)local_68);
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return cVar1 == '\x01';
}



// ==== 0016c5d2  NCDEEngine::loadTheme(QString_const&)::{lambda(QString_const&)#1}::operator()

/* NCDEEngine::loadTheme(QString const&)::{lambda(QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&) const */

void __thiscall
NCDEEngine::loadTheme(QString_const&)::{lambda(QString_const&)#1}::operator()
          (_lambda_QString_const___1_ *this,QString *param_1)

{
  char cVar1;
  long in_FS_OFFSET;
  QListSpecialMethods<QString> local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  loadTheme(*(NCDEEngine **)this,param_1);
  QFileSystemWatcher::files();
  cVar1 = QListSpecialMethods<QString>::contains(local_38,param_1,1);
  QList<QString>::~QList((QList<QString> *)local_38);
  if (cVar1 != '\x01') {
    QFileSystemWatcher::addPath(*(QString **)(*(long *)this + 0x20));
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016c684  NCDEEngine::loadTheme

/* WARNING: Removing unreachable block (ram,0x0016d5c9) */
/* NCDEEngine::loadTheme(QString const&) */

undefined8 __thiscall NCDEEngine::loadTheme(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  NCDEEngine NVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  QFileSystemWatcher *this_00;
  undefined8 uVar6;
  long in_FS_OFFSET;
  undefined1 auVar7 [16];
  QByteArray local_118 [8];
  QVariant local_110 [8];
  QFile local_108 [16];
  QLatin1String local_f8 [16];
  QString local_e8 [32];
  NCDEEngine *local_c8 [4];
  undefined4 local_a8 [8];
  undefined6 local_88;
  undefined2 uStack_82;
  undefined6 uStack_80;
  QVariant local_78 [32];
  undefined6 local_58;
  undefined2 uStack_52;
  undefined6 local_50;
  undefined2 uStack_4a;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QUrl::QUrl((QUrl *)local_c8,param_1,0);
  cVar1 = QUrl::isLocalFile();
  if (cVar1 == '\0') {
    QString::QString(local_e8,param_1);
  }
  else {
    QUrl::QUrl((QUrl *)local_a8,param_1,0);
    QUrl::toLocalFile();
    QUrl::~QUrl((QUrl *)local_a8);
  }
  QUrl::~QUrl((QUrl *)local_c8);
  QFile::QFile(local_108,local_e8);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_a8,1);
  cVar1 = QFile::open(local_108,local_a8[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson(local_118,(QJsonParseError *)local_a8);
    QByteArray::~QByteArray((QByteArray *)local_a8);
    QFileDevice::close();
    cVar1 = QJsonDocument::isObject();
    if (cVar1 == '\x01') {
      QJsonDocument::object();
      QJsonObject::toVariantMap();
      QJsonObject::~QJsonObject((QJsonObject *)local_a8);
      ::QVariant::QVariant(local_78,(QString *)(this + 0x2d0));
      QString::QString((QString *)local_c8,"accent");
      QMap<QString,QVariant>::value((QString *)&local_58,local_110);
      ::QVariant::toString();
      QString::operator=((QString *)(this + 0x2d0),(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      ::QVariant::~QVariant((QVariant *)&local_58);
      QString::~QString((QString *)local_c8);
      ::QVariant::~QVariant(local_78);
      ::QVariant::QVariant(local_78);
      QString::QString((QString *)local_c8,"darkModeLock");
      QMap<QString,QVariant>::value((QString *)&local_58,local_110);
      ::QVariant::toString();
      QString::operator=((QString *)(this + 0x2e8),(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      ::QVariant::~QVariant((QVariant *)&local_58);
      QString::~QString((QString *)local_c8);
      ::QVariant::~QVariant(local_78);
      QLatin1String::QLatin1String(local_f8,"light");
      ::QVariant::QVariant(local_78);
      QString::QString((QString *)local_c8,"mode");
      QMap<QString,QVariant>::value((QString *)&local_58,local_110);
      ::QVariant::toString();
      NVar2 = (NCDEEngine)::operator!=((QString *)local_a8,local_f8);
      this[0x28] = NVar2;
      QString::~QString((QString *)local_a8);
      ::QVariant::~QVariant((QVariant *)&local_58);
      QString::~QString((QString *)local_c8);
      ::QVariant::~QVariant(local_78);
      ::QVariant::QVariant(local_78);
      QString::QString((QString *)local_a8,"usingCustomBase");
      QMap<QString,QVariant>::value((QString *)&local_58,local_110);
      NVar2 = (NCDEEngine)::QVariant::toBool();
      this[0x2a] = NVar2;
      ::QVariant::~QVariant((QVariant *)&local_58);
      QString::~QString((QString *)local_a8);
      ::QVariant::~QVariant(local_78);
      this[0x29] = (NCDEEngine)((byte)this[0x2a] ^ 1);
      QString::QString((QString *)local_a8,"customAccent");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"customAccent");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QColor::QColor((QColor *)&local_88,(QString *)local_a8);
        *(ulong *)(this + 0x300) = CONCAT26(uStack_82,local_88);
        *(ulong *)(this + 0x306) = CONCAT62(uStack_80,uStack_82);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"customBase");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"customBase");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QColor::QColor((QColor *)&local_88,(QString *)local_a8);
        *(ulong *)(this + 0x8c) = CONCAT26(uStack_82,local_88);
        *(ulong *)(this + 0x92) = CONCAT62(uStack_80,uStack_82);
        *(undefined8 *)(this + 0x4c) = *(undefined8 *)(this + 0x8c);
        *(undefined8 *)(this + 0x52) = *(undefined8 *)(this + 0x92);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
        *(undefined8 *)(this + 0x5c) = *(undefined8 *)(this + 0x4c);
        *(undefined8 *)(this + 0x62) = *(undefined8 *)(this + 0x52);
      }
      QString::QString((QString *)local_a8,"sampledPanelText");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"sampledPanelText");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QColor::QColor((QColor *)&local_88,(QString *)local_a8);
        *(ulong *)(this + 0xcc) = CONCAT26(uStack_82,local_88);
        *(ulong *)(this + 0xd2) = CONCAT62(uStack_80,uStack_82);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"bodyFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"bodyFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x418),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"titleFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"titleFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x430),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"monoFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"monoFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x448),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"displayFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"displayFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x460),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"fellFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"fellFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x478),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      QString::QString((QString *)local_a8,"garFont");
      cVar1 = QMap<QString,QVariant>::contains
                        ((QMap<QString,QVariant> *)local_110,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      if (cVar1 != '\0') {
        ::QVariant::QVariant(local_78);
        QString::QString((QString *)local_c8,"garFont");
        QMap<QString,QVariant>::value((QString *)&local_58,local_110);
        ::QVariant::toString();
        QString::operator=((QString *)(this + 0x490),(QString *)local_a8);
        QString::~QString((QString *)local_a8);
        ::QVariant::~QVariant((QVariant *)&local_58);
        QString::~QString((QString *)local_c8);
        ::QVariant::~QVariant(local_78);
      }
      iVar3 = QColor::blue();
      iVar4 = QColor::green();
      iVar5 = QColor::red();
      QColor::QColor((QColor *)&local_58,iVar5,iVar4,iVar3,0x66);
      *(ulong *)(this + 800) = CONCAT26(uStack_52,local_58);
      *(ulong *)(this + 0x326) = CONCAT62(local_50,uStack_52);
      auVar7 = liteScale((QColor *)(this + 0x300),0xf);
      local_58 = auVar7._0_6_;
      uStack_52 = auVar7._6_2_;
      local_50 = auVar7._8_6_;
      uStack_4a = auVar7._14_2_;
      *(long *)(this + 0x310) = auVar7._0_8_;
      *(long *)(this + 0x316) = auVar7._6_8_;
      recompute(this);
      applyGtkTheme(this,(bool)this[0x28]);
      applyGtkAccent();
      if (*(long *)(this + 0x20) == 0) {
        this_00 = operator_new(0x10);
        QFileSystemWatcher::QFileSystemWatcher(this_00,(QObject *)this);
        *(QFileSystemWatcher **)(this + 0x20) = this_00;
        local_c8[0] = this;
        QObject::
        connect<void(QFileSystemWatcher::*)(QString_const&,QFileSystemWatcher::QPrivateSignal),NCDEEngine::loadTheme(QString_const&)::_lambda(QString_const&)_1_>
                  (local_a8,*(undefined8 *)(this + 0x20),QFileSystemWatcher::fileChanged,0,this,
                   local_c8,0);
        QMetaObject::Connection::~Connection((Connection *)local_a8);
      }
      QFileSystemWatcher::files();
      cVar1 = QListSpecialMethods<QString>::contains
                        ((QListSpecialMethods<QString> *)local_a8,local_e8,1);
      QList<QString>::~QList((QList<QString> *)local_a8);
      if (cVar1 != '\x01') {
        QFileSystemWatcher::addPath(*(QString **)(this + 0x20));
      }
      uVar6 = 1;
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_110);
    }
    else {
      uVar6 = 0;
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_118);
  }
  else {
    uVar6 = 0;
  }
  QFile::~QFile(local_108);
  QString::~QString(local_e8);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0016dbcc  NCDEEngine::seedGtkUserConfig

/* NCDEEngine::seedGtkUserConfig() */

void NCDEEngine::seedGtkUserConfig(void)

{
  char cVar1;
  QString *pQVar2;
  long in_FS_OFFSET;
  QLatin1Char local_203;
  undefined2 local_202;
  long local_200;
  long local_1f8;
  initializer_list<QString> *local_1f0;
  long local_1e8;
  initializer_list<QString> *local_1e0;
  long local_1d8;
  long local_1d0;
  long local_1c8;
  undefined1 *local_1c0;
  undefined1 *local_1b8;
  undefined *local_1b0;
  undefined1 *local_1a8;
  undefined1 *local_1a0;
  undefined1 *local_198;
  undefined1 *local_190;
  undefined1 *local_188;
  undefined1 *local_180;
  undefined *local_178;
  undefined *local_170;
  QString local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QString local_108 [32];
  QString *local_e8;
  undefined8 local_e0;
  QString local_c8 [32];
  undefined2 local_a8;
  undefined6 uStack_a6;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [24];
  QString aQStack_50 [24];
  QString aQStack_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_1b0 = &DAT_00299850;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"/usr/share/themes/NCDE/gtk-3.0",0x1e);
  QString::QString(local_168,(QArrayDataPointer *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  local_1b8 = &LAB_0029988f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"/usr/share/themes/NCDE/gtk-4.0",0x1e);
  QString::QString(local_148,(QArrayDataPointer *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  local_1c0 = &LAB_002998cf_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,
             L"/.themes/NCDE/gtk-3.0",0x15);
  QString::QString((QString *)local_88,(QArrayDataPointer *)&local_a8);
  QDir::homePath();
  ::operator+(local_128,local_c8);
  QString::~QString(local_c8);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  local_1a8 = &LAB_002998ff_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"/.config/gtk-4.0",
             0x10);
  QString::QString((QString *)local_88,(QArrayDataPointer *)&local_a8);
  QDir::homePath();
  ::operator+(local_108,local_c8);
  QString::~QString(local_c8);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  QString::QString((QString *)local_88);
  QDir::QDir((QDir *)local_c8,(QString *)local_88);
  std::optional<QFlags<QFileDevice::Permission>>::optional(&local_a8);
  QDir::mkpath(local_c8,local_128,CONCAT62(uStack_a6,local_a8));
  QDir::~QDir((QDir *)local_c8);
  QString::~QString((QString *)local_88);
  QString::QString((QString *)local_88);
  QDir::QDir((QDir *)local_c8,(QString *)local_88);
  std::optional<QFlags<QFileDevice::Permission>>::optional(&local_a8);
  QDir::mkpath(local_c8,local_108,CONCAT62(uStack_a6,local_a8));
  QDir::~QDir((QDir *)local_c8);
  QString::~QString((QString *)local_88);
  local_e8 = (QString *)0x0;
  local_e0 = 3;
  local_190 = &LAB_00299927_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"_palette-dark.css",
             0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_c8);
  local_198 = &LAB_0029994f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"_palette-light.css",
             0x12);
  QString::QString(aQStack_50,(QArrayDataPointer *)&local_a8);
  local_1a0 = &LAB_00299976;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"_rules.css",10);
  QString::QString(aQStack_38,(QArrayDataPointer *)local_88);
  local_e8 = local_68;
  local_1f0 = (initializer_list<QString> *)&local_e8;
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  local_200 = std::initializer_list<QString>::begin(local_1f0);
  local_1e8 = std::initializer_list<QString>::end(local_1f0);
  for (; local_200 != local_1e8; local_200 = local_200 + 0x18) {
    local_1c8 = local_200;
    QLatin1Char::QLatin1Char((QLatin1Char *)&local_202,'/');
    QChar::QChar<QLatin1Char,true>((QChar *)&local_a8,local_202._0_1_);
    ::operator+(local_88,local_128,local_a8);
    ::operator+(local_c8,(QString *)local_88);
    QString::~QString((QString *)local_88);
    cVar1 = QFile::exists(local_c8);
    if (cVar1 != '\x01') {
      QLatin1Char::QLatin1Char(&local_203,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)&local_202,local_203);
      ::operator+(&local_a8,local_168,local_202);
      ::operator+((QString *)local_88,(QString *)&local_a8);
      QFile::copy((QString *)local_88,local_c8);
      QString::~QString((QString *)local_88);
      QString::~QString((QString *)&local_a8);
    }
    QString::~QString(local_c8);
  }
  pQVar2 = (QString *)&local_20;
  while (pQVar2 != local_68) {
    pQVar2 = pQVar2 + -0x18;
    QString::~QString(pQVar2);
  }
  local_e8 = (QString *)0x0;
  local_e0 = 2;
  local_180 = &LAB_00299927_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"_palette-dark.css",
             0x11);
  QString::QString(local_68,(QArrayDataPointer *)&local_a8);
  local_188 = &LAB_0029994f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"_palette-light.css",0x12);
  QString::QString(aQStack_50,(QArrayDataPointer *)local_88);
  local_e8 = local_68;
  local_1e0 = (initializer_list<QString> *)&local_e8;
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  local_1f8 = std::initializer_list<QString>::begin(local_1e0);
  local_1d8 = std::initializer_list<QString>::end(local_1e0);
  for (; local_1f8 != local_1d8; local_1f8 = local_1f8 + 0x18) {
    local_1d0 = local_1f8;
    QLatin1Char::QLatin1Char((QLatin1Char *)&local_202,'/');
    QChar::QChar<QLatin1Char,true>((QChar *)&local_a8,local_202._0_1_);
    ::operator+(local_88,local_108,local_a8);
    ::operator+(local_c8,(QString *)local_88);
    QString::~QString((QString *)local_88);
    cVar1 = QFile::exists(local_c8);
    if (cVar1 != '\x01') {
      QLatin1Char::QLatin1Char(&local_203,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)&local_202,local_203);
      ::operator+(&local_a8,local_148,local_202);
      ::operator+((QString *)local_88,(QString *)&local_a8);
      QFile::copy((QString *)local_88,local_c8);
      QString::~QString((QString *)local_88);
      QString::~QString((QString *)&local_a8);
    }
    QString::~QString(local_c8);
  }
  pQVar2 = aQStack_38;
  while (pQVar2 != local_68) {
    pQVar2 = pQVar2 + -0x18;
    QString::~QString(pQVar2);
  }
  local_178 = &DAT_0029998c;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_a8,(QTypedArrayData *)0x0,L"/gtk.css",8);
  QString::QString((QString *)local_88,(QArrayDataPointer *)&local_a8);
  ::operator+((QString *)&local_e8,local_108);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_a8);
  cVar1 = QFile::exists((QString *)&local_e8);
  if (cVar1 != '\x01') {
    local_170 = &DAT_0029998c;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"/gtk.css",8);
    QString::QString((QString *)&local_a8,(QArrayDataPointer *)local_c8);
    ::operator+((QString *)local_88,local_148);
    QFile::copy((QString *)local_88,(QString *)&local_e8);
    QString::~QString((QString *)local_88);
    QString::~QString((QString *)&local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  }
  QString::~QString((QString *)&local_e8);
  QString::~QString(local_108);
  QString::~QString(local_128);
  QString::~QString(local_148);
  QString::~QString(local_168);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016e81e  NCDEEngine::applyGtkTheme(bool)::{lambda(QString_const&,QString_const&)#1}::operator()

/* NCDEEngine::applyGtkTheme(bool)::{lambda(QString const&, QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) const */

void NCDEEngine::applyGtkTheme(bool)::{lambda(QString_const&,QString_const&)#1}::operator()
               (QString *param_1,QString *param_2)

{
  QRegularExpression *pQVar1;
  char cVar2;
  long in_FS_OFFSET;
  QLatin1Char local_90;
  QLatin1Char local_8f;
  undefined2 local_8e;
  undefined4 local_8c;
  QRegularExpression local_88 [8];
  undefined1 *local_80;
  undefined2 local_78 [16];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QFlags<QRegularExpression::PatternOption>::QFlags
            ((QFlags<QRegularExpression::PatternOption> *)&local_8c,0);
  local_80 = &LAB_0029999e;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"=.*",3);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  ::operator+(local_38,param_2);
  QRegularExpression::QRegularExpression(local_88,local_38,local_8c);
  QString::~QString(local_38);
  QString::~QString(local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
  cVar2 = QString::contains(*(QRegularExpression **)param_1,(QRegularExpressionMatch *)local_88);
  if (cVar2 == '\0') {
    QLatin1Char::QLatin1Char(&local_8f,'\n');
    QChar::QChar<QLatin1Char,true>((QChar *)&local_8c,local_8f);
    QLatin1Char::QLatin1Char(&local_90,'=');
    QChar::QChar<QLatin1Char,true>((QChar *)&local_8e,local_90);
    ::operator+(local_78,param_2,local_8e);
    ::operator+(local_58,(QString *)local_78);
    ::operator+(local_38,local_58,(undefined2)local_8c);
    QString::operator+=(*(QString **)param_1,local_38);
    QString::~QString(local_38);
    QString::~QString(local_58);
    QString::~QString((QString *)local_78);
  }
  else {
    pQVar1 = *(QRegularExpression **)param_1;
    QLatin1Char::QLatin1Char((QLatin1Char *)&local_8c,'=');
    QChar::QChar<QLatin1Char,true>((QChar *)local_78,local_8c._0_1_);
    ::operator+(local_58,param_2,local_78[0]);
    ::operator+(local_38,local_58);
    QString::replace(pQVar1,(QString *)local_88);
    QString::~QString(local_38);
    QString::~QString(local_58);
  }
  QRegularExpression::~QRegularExpression(local_88);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0016eb92  NCDEEngine::applyGtkTheme

/* NCDEEngine::applyGtkTheme(bool) */

void __thiscall NCDEEngine::applyGtkTheme(NCDEEngine *this,bool param_1)

{
  char cVar1;
  undefined4 uVar2;
  QTextStream *pQVar3;
  QString *pQVar4;
  long in_FS_OFFSET;
  QFile local_298 [16];
  QString local_288 [32];
  QString local_268 [32];
  QString local_248 [32];
  QArrayDataPointer<char16_t> local_228 [32];
  QString local_208 [32];
  QString local_1e8 [32];
  undefined8 *local_1c8 [4];
  QString local_1a8 [32];
  QString local_188 [32];
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  QFile local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [24];
  QString aQStack_90 [24];
  QString aQStack_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  seedGtkUserConfig();
  if (param_1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"_palette-dark.css",0x11);
    QString::QString(local_288,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"_palette-light.css",0x12);
    QString::QString(local_268,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"_palette-light.css",0x12);
    QString::QString(local_288,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"_palette-dark.css",0x11);
    QString::QString(local_268,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
  }
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"/.themes/NCDE/gtk-3.0/gtk.css",0x1d);
  QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
  QDir::homePath();
  ::operator+((QString *)local_c8,local_128);
  QFile::QFile(local_148,(QString *)local_c8);
  QString::~QString((QString *)local_c8);
  QString::~QString(local_128);
  QString::~QString((QString *)local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  uVar2 = operator|(2,0x10);
  cVar1 = QFile::open(local_148,uVar2);
  if (cVar1 != '\0') {
    QTextStream::QTextStream((QTextStream *)local_c8,(QIODevice *)local_148);
    pQVar3 = (QTextStream *)QTextStream::operator<<((QTextStream *)local_c8,&DAT_002999e8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"@import url(\"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,local_288);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\");\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"@import url(\"_accent.css\");\n");
    QTextStream::operator<<(pQVar3,"@import url(\"_rules.css\");\n");
    QTextStream::~QTextStream((QTextStream *)local_c8);
  }
  QFile::~QFile(local_148);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"/.config/gtk-4.0/gtk.css",0x18);
  QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
  QDir::homePath();
  ::operator+((QString *)local_c8,local_128);
  QFile::QFile(local_298,(QString *)local_c8);
  QString::~QString((QString *)local_c8);
  QString::~QString(local_128);
  QString::~QString((QString *)local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  uVar2 = operator|(1,0x10);
  cVar1 = QFile::open(local_298,uVar2);
  if (cVar1 != '\0') {
    QIODevice::readAll();
    QString::fromUtf8<void>(local_248,(QByteArray *)local_c8);
    QByteArray::~QByteArray((QByteArray *)local_c8);
    QFileDevice::close();
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"\")",2);
    QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_168,(QTypedArrayData *)0x0,L"@import url(\"",
               0xd);
    QString::QString((QString *)local_148,(QArrayDataPointer *)&local_168);
    ::operator+(local_128,(QString *)local_148);
    ::operator+((QString *)local_c8,local_128);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_1c8,(QTypedArrayData *)0x0,L"\")",2);
    QString::QString(local_1a8,(QArrayDataPointer *)local_1c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_228,(QTypedArrayData *)0x0,L"@import url(\"",0xd);
    QString::QString(local_208,(QArrayDataPointer *)local_228);
    ::operator+(local_1e8,local_208);
    ::operator+(local_188,local_1e8);
    QString::replace(local_248,local_188,local_c8,1);
    QString::~QString(local_188);
    QString::~QString(local_1e8);
    QString::~QString(local_208);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_228);
    QString::~QString(local_1a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1c8);
    QString::~QString((QString *)local_c8);
    QString::~QString(local_128);
    QString::~QString((QString *)local_148);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_168);
    QString::~QString((QString *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    uVar2 = operator|(2,0x10);
    cVar1 = QFile::open(local_298,uVar2);
    if (cVar1 != '\0') {
      QTextStream::QTextStream((QTextStream *)local_c8,(QIODevice *)local_298);
      QTextStream::operator<<((QTextStream *)local_c8,local_248);
      QTextStream::~QTextStream((QTextStream *)local_c8);
    }
    QString::~QString(local_248);
  }
  QFile::~QFile(local_298);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_e8,(QTypedArrayData *)0x0,L"/.config/gtk-4.0/settings.ini",0x1d);
  QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
  QDir::homePath();
  ::operator+(local_188,(QString *)local_108);
  QString::~QString((QString *)local_108);
  QString::~QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  QFile::QFile((QFile *)local_1a8,local_188);
  local_168 = 0;
  local_160 = 0;
  local_158 = 0;
  uVar2 = operator|(1,0x10);
  cVar1 = QFile::open(local_1a8,uVar2);
  if (cVar1 != '\0') {
    QIODevice::readAll();
    QString::fromUtf8<void>((QString *)local_c8,(QByteArray *)local_e8);
    QString::operator=((QString *)&local_168,(QString *)local_c8);
    QString::~QString((QString *)local_c8);
    QByteArray::~QByteArray((QByteArray *)local_e8);
    QFileDevice::close();
  }
  local_1c8[0] = &local_168;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"NCDE",4);
  QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"gtk-theme-name",0xe);
  QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
  applyGtkTheme(bool)::{lambda(QString_const&,QString_const&)#1}::operator()
            ((QString *)local_1c8,(QString *)local_108);
  QString::~QString((QString *)local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  QString::~QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  if (!param_1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"false",5);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"true",4);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_108);
  }
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
             L"gtk-application-prefer-dark-theme",0x21);
  QString::QString(local_128,(QArrayDataPointer *)local_148);
  applyGtkTheme(bool)::{lambda(QString_const&,QString_const&)#1}::operator()
            ((QString *)local_1c8,local_128);
  QString::~QString(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
  QString::~QString((QString *)local_c8);
  if (!param_1) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  uVar2 = operator|(2,0x10);
  cVar1 = QFile::open(local_1a8,uVar2);
  if (cVar1 != '\0') {
    QTextStream::QTextStream((QTextStream *)local_c8,(QIODevice *)local_1a8);
    QTextStream::operator<<((QTextStream *)local_c8,(QString *)&local_168);
    QTextStream::~QTextStream((QTextStream *)local_c8);
  }
  QString::~QString((QString *)&local_168);
  QFile::~QFile((QFile *)local_1a8);
  QString::~QString(local_188);
  QString::QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"set",3);
  QString::QString(local_a8,(QArrayDataPointer *)local_188);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_168,(QTypedArrayData *)0x0,
             L"org.gnome.desktop.interface",0x1b);
  QString::QString(aQStack_90,(QArrayDataPointer *)&local_168);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"color-scheme",0xc);
  QString::QString(aQStack_78,(QArrayDataPointer *)local_148);
  if (!param_1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"default",7);
    QString::QString(aQStack_60,(QArrayDataPointer *)local_108);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"prefer-dark",0xb);
    QString::QString(aQStack_60,(QArrayDataPointer *)local_128);
  }
  QList<QString>::QList(local_e8,local_a8,4);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_1c8,(QTypedArrayData *)0x0,L"gsettings",9);
  QString::QString(local_1a8,(QArrayDataPointer *)local_1c8);
  QProcess::startDetached(local_1a8,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
  QString::~QString(local_1a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1c8);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_48;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  if (!param_1) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_168);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
  QString::~QString((QString *)local_c8);
  QString::QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_168,(QTypedArrayData *)0x0,L"set",3);
  QString::QString(local_a8,(QArrayDataPointer *)&local_168);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,
             L"org.gnome.desktop.interface",0x1b);
  QString::QString(aQStack_90,(QArrayDataPointer *)local_148);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"gtk-theme",9);
  QString::QString(aQStack_78,(QArrayDataPointer *)local_128);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"NCDE",4);
  QString::QString(aQStack_60,(QArrayDataPointer *)local_108);
  QList<QString>::QList(local_e8,local_a8,4);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_1a8,(QTypedArrayData *)0x0,L"gsettings",9);
  QString::QString(local_188,(QArrayDataPointer *)local_1a8);
  QProcess::startDetached(local_188,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
  QString::~QString(local_188);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1a8);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_48;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_168);
  QString::~QString((QString *)local_c8);
  QString::QString((QString *)local_c8);
  if (!param_1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"light",5);
    QString::QString(local_a8,(QArrayDataPointer *)local_108);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"dark",4);
    QString::QString(local_a8,(QArrayDataPointer *)local_128);
  }
  QList<QString>::QList(local_e8,local_a8,1);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_168,(QTypedArrayData *)0x0,
             L"/usr/local/bin/ncde-chromium-sync.sh",0x24);
  QString::QString((QString *)local_148,(QArrayDataPointer *)&local_168);
  QProcess::startDetached
            ((QString *)local_148,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
  QString::~QString((QString *)local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_168);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_90;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  if (!param_1) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  }
  QString::~QString((QString *)local_c8);
  if (param_1) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"#263033",7);
    QString::QString((QString *)local_1c8,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"#E6F1F2",7);
    QString::QString(local_1a8,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"#1E2527",7);
    QString::QString(local_188,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"#5A6670",7);
    QString::QString((QString *)&local_168,(QArrayDataPointer *)local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"#E7E1D8",7);
    QString::QString((QString *)local_1c8,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"#2B2621",7);
    QString::QString(local_1a8,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"#F4F1EC",7);
    QString::QString(local_188,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"#9A9088",7);
    QString::QString((QString *)&local_168,(QArrayDataPointer *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
  }
  local_a8._0_16_ = accent();
  QColor::name(local_148,local_a8,0);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_108,(QTypedArrayData *)0x0,L"/.gtkrc-2.0",0xb);
  QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
  QDir::homePath();
  ::operator+((QString *)local_c8,local_128);
  QFile::QFile((QFile *)local_1e8,(QString *)local_c8);
  QString::~QString((QString *)local_c8);
  QString::~QString(local_128);
  QString::~QString((QString *)local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  uVar2 = operator|(2,0x10);
  cVar1 = QFile::open(local_1e8,uVar2);
  if (cVar1 != '\0') {
    QTextStream::QTextStream((QTextStream *)local_c8,(QIODevice *)local_1e8);
    pQVar3 = (QTextStream *)QTextStream::operator<<((QTextStream *)local_c8,&DAT_00299d20);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"gtk-theme-name=\"NCDE\"\n");
    pQVar3 = (QTextStream *)
             QTextStream::operator<<(pQVar3,"gtk-font-name=\"IM Fell English 11\"\n\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"style \"ncde\" {\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  bg[NORMAL]      = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_1c8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  fg[NORMAL]      = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,local_1a8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  base[NORMAL]    = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,local_188);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  text[NORMAL]    = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,local_1a8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  bg[ACTIVE]      = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_1c8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  fg[ACTIVE]      = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)&local_168);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  bg[PRELIGHT]    = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_148);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  fg[PRELIGHT]    = \"#FFFFFF\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  bg[SELECTED]    = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_148);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  fg[SELECTED]    = \"#FFFFFF\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  base[SELECTED]  = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_148);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  text[SELECTED]  = \"#FFFFFF\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  bg[INSENSITIVE] = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)local_1c8);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"  fg[INSENSITIVE] = \"");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,(QString *)&local_168);
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"\"\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"}\n");
    pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"widget_class \"*\" style \"ncde\"\n");
    QTextStream::operator<<(pQVar3,"class \"*\" style \"ncde\"\n");
    QTextStream::~QTextStream((QTextStream *)local_c8);
  }
  QFile::~QFile((QFile *)local_1e8);
  QString::~QString((QString *)local_148);
  QString::~QString((QString *)&local_168);
  QString::~QString(local_188);
  QString::~QString(local_1a8);
  QString::~QString((QString *)local_1c8);
  QString::~QString(local_268);
  QString::~QString(local_288);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00170f3a  NCDEEngine::applyGtkAccent

/* NCDEEngine::applyGtkAccent() */

void NCDEEngine::applyGtkAccent(void)

{
  char cVar1;
  undefined4 uVar2;
  QTextStream *pQVar3;
  QString *pQVar4;
  long in_FS_OFFSET;
  QString local_178 [32];
  QList<QString> local_158 [32];
  QString local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  undefined8 local_f8 [4];
  undefined8 local_d8 [4];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QString local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  seedGtkUserConfig();
  local_78._0_16_ = accent();
  QColor::name(local_178,local_78,0);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_118,(QTypedArrayData *)0x0,L"/.themes/NCDE/gtk-3.0/_accent.css",0x21);
  QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
  QDir::homePath();
  ::operator+(local_78,local_138);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"/.config/gtk-4.0/_accent.css",0x1c);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  QDir::homePath();
  ::operator+(local_60,(QString *)local_d8);
  QList<QString>::QList(local_158,local_78,2);
  pQVar4 = aQStack_48;
  while (pQVar4 != local_78) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  QString::~QString((QString *)local_d8);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  QString::~QString(local_138);
  QString::~QString((QString *)local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  local_f8[0] = QList<QString>::begin(local_158);
  local_d8[0] = QList<QString>::end(local_158);
  while( true ) {
    cVar1 = QList<QString>::const_iterator::operator!=((const_iterator *)local_f8,local_d8[0]);
    if (cVar1 == '\0') break;
    pQVar4 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)local_f8);
    QFile::QFile((QFile *)local_b8,pQVar4);
    uVar2 = operator|(2,0x10);
    cVar1 = QFile::open(local_b8,uVar2);
    if (cVar1 != '\0') {
      QTextStream::QTextStream((QTextStream *)local_98,(QIODevice *)local_b8);
      pQVar3 = (QTextStream *)QTextStream::operator<<((QTextStream *)local_98,&DAT_00299fc8);
      pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,"@define-color ncde_accent ");
      pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,local_178);
      pQVar3 = (QTextStream *)QTextStream::operator<<(pQVar3,";\n");
      QTextStream::operator<<(pQVar3,"@define-color theme_selected_bg_color @ncde_accent;\n");
      QTextStream::~QTextStream((QTextStream *)local_98);
    }
    QFile::~QFile((QFile *)local_b8);
    QList<QString>::const_iterator::operator++((const_iterator *)local_f8);
  }
  QList<QString>::~QList(local_158);
  QString::~QString(local_178);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017142c  NCDEEngine::setTerminalFont

/* NCDEEngine::setTerminalFont(QString const&) */

void __thiscall NCDEEngine::setTerminalFont(NCDEEngine *this,QString *param_1)

{
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_48,param_1);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"fontFamily",10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  setTerminalConfigField(local_68,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00171544  NCDEEngine::setTerminalGlassTint

/* NCDEEngine::setTerminalGlassTint(double) */

void __thiscall NCDEEngine::setTerminalGlassTint(NCDEEngine *this,double param_1)

{
  double *pdVar1;
  long in_FS_OFFSET;
  double local_b8;
  NCDEEngine *local_b0;
  double local_a0;
  double local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 1.0;
  local_a0 = 0.0;
  local_b8 = param_1;
  local_b0 = this;
  pdVar1 = qBound<double>(&local_a0,&local_b8,&local_98);
  ::QVariant::QVariant(local_48,*pdVar1);
  local_90 = &LAB_0029a06c;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"glassTint",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  setTerminalConfigField(local_68,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00171696  NCDEEngine::terminalConfig

/* NCDEEngine::terminalConfig() const */

NCDEEngine * __thiscall NCDEEngine::terminalConfig(NCDEEngine *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QFile local_a8 [16];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QString local_58 [32];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"/.config/ncde-terminal/config.json",0x22);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  QDir::homePath();
  ::operator+((QString *)local_38,local_98);
  QFile::QFile(local_a8,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QString::~QString(local_98);
  QString::~QString(local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_a8,local_38[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_58,(QJsonParseError *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    cVar1 = QJsonDocument::isObject();
    if (cVar1 == '\0') {
      *(undefined8 *)this = 0;
      QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)this);
    }
    else {
      QJsonDocument::object();
      QJsonObject::toVariantMap();
      QJsonObject::~QJsonObject((QJsonObject *)local_38);
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_58);
  }
  else {
    *(undefined8 *)this = 0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)this);
  }
  QFile::~QFile(local_a8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001719aa  NCDEEngine::saveFiligreepalette

/* NCDEEngine::saveFiligreepalette(QString const&, QMap<QString, QVariant> const&) */

bool __thiscall NCDEEngine::saveFiligreepalette(NCDEEngine *this,QString *param_1,QMap *param_2)

{
  char cVar1;
  QVariant *this_00;
  long in_FS_OFFSET;
  bool bVar2;
  NCDEEngine local_70 [8];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::trimmed(local_68);
  cVar1 = QString::isEmpty(local_68);
  if ((cVar1 == '\0') &&
     (cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)param_2), cVar1 == '\0')) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    bVar2 = false;
  }
  else {
    filigreePalettesRaw(local_70);
    ::QVariant::QVariant(local_48,param_2);
    this_00 = (QVariant *)
              QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_70,local_68);
    ::QVariant::operator=(this_00,local_48);
    ::QVariant::~QVariant(local_48);
    QString::operator=((QString *)(this + 0x4e0),local_68);
    QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(this + 0x4d8),param_2);
    cVar1 = writeFiligreePalettes((QMap *)local_70);
    bVar2 = cVar1 == '\x01';
    if (bVar2) {
      writeActiveFiligreepaletteName(this);
      filigreePalettesChanged(this);
    }
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_70);
  }
  QString::~QString(local_68);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return bVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00171b6c  NCDEEngine::deleteFiligreepalette

/* NCDEEngine::deleteFiligreepalette(QString const&) */

undefined8 __thiscall NCDEEngine::deleteFiligreepalette(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  NCDEEngine local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesRaw(local_28);
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_28,param_1);
  if (cVar1 == '\x01') {
    QMap<QString,QVariant>::remove((QMap<QString,QVariant> *)local_28,param_1);
    cVar1 = writeFiligreePalettes((QMap *)local_28);
    if (cVar1 == '\x01') {
      cVar1 = ::operator==((QString *)(this + 0x4e0),param_1);
      if (cVar1 != '\0') {
        QString::clear((QString *)(this + 0x4e0));
        QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)(this + 0x4d8));
        writeActiveFiligreepaletteName(this);
      }
      filigreePalettesChanged(this);
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 00171ca0  NCDEEngine::setActiveFiligreepalette

/* NCDEEngine::setActiveFiligreepalette(QString const&) */

undefined8 __thiscall NCDEEngine::setActiveFiligreepalette(NCDEEngine *this,QString *param_1)

{
  char cVar1;
  bool bVar2;
  undefined8 uVar3;
  long in_FS_OFFSET;
  NCDEEngine local_130 [8];
  QMap local_128 [8];
  undefined1 *local_120;
  wchar16 *local_118;
  undefined *local_110;
  wchar16 *local_108;
  wchar16 *local_100;
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QString local_b8 [32];
  QColor local_98 [16];
  QColor local_88 [16];
  QColor local_78 [16];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesRaw(local_130);
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_130,param_1);
  if (cVar1 != '\x01') {
    uVar3 = 0;
    goto LAB_00172225;
  }
  ::QVariant::QVariant(local_68);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_130);
  ::QVariant::toMap();
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::~QVariant(local_68);
  QString::operator=((QString *)(this + 0x4e0),param_1);
  QMap<QString,QVariant>::operator=((QMap<QString,QVariant> *)(this + 0x4d8),local_128);
  writeActiveFiligreepaletteName(this);
  ::QVariant::QVariant(local_68);
  local_120 = &LAB_0029a0c6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"panelBg",7);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
  ::QVariant::toString();
  QColor::QColor(local_98,local_b8);
  QString::~QString(local_b8);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  ::QVariant::~QVariant(local_68);
  ::QVariant::QVariant(local_68);
  local_118 = L"accent";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"accent",6);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
  ::QVariant::toString();
  QColor::QColor(local_88,local_b8);
  QString::~QString(local_b8);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  ::QVariant::~QVariant(local_68);
  ::QVariant::QVariant(local_68);
  local_110 = &DAT_0029a0e4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"ink",3);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
  ::QVariant::toString();
  QColor::QColor(local_78,local_b8);
  QString::~QString(local_b8);
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  ::QVariant::~QVariant(local_68);
  cVar1 = QColor::isValid(local_98);
  if (cVar1 == '\0') {
LAB_0017208c:
    bVar2 = false;
  }
  else {
    cVar1 = QColor::isValid(local_88);
    if (cVar1 == '\0') goto LAB_0017208c;
    cVar1 = QColor::isValid(local_78);
    if (cVar1 == '\0') goto LAB_0017208c;
    bVar2 = true;
  }
  if (bVar2) {
    setBaseColor(this,local_98,local_88,local_78);
  }
  local_108 = L"dark";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_d8,(QTypedArrayData *)0x0,L"dark",4);
  QString::QString(local_b8,(QArrayDataPointer *)local_d8);
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_128,local_b8);
  QString::~QString(local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_d8);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    local_100 = L"dark";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_d8,(QTypedArrayData *)0x0,L"dark",4);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    bVar2 = (bool)::QVariant::toBool();
    setDarkMode(this,bVar2);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_d8);
    ::QVariant::~QVariant(local_68);
  }
  filigreePalettesChanged(this);
  uVar3 = 1;
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_128);
LAB_00172225:
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_130);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar3;
}



// ==== 001723ec  NCDEEngine::filigreePalettes

/* NCDEEngine::filigreePalettes() const */

NCDEEngine * __thiscall NCDEEngine::filigreePalettes(NCDEEngine *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesRaw(this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00172432  NCDEEngine::activeFiligreePalette

/* NCDEEngine::activeFiligreePalette() const */

QMap<QString,QVariant> * NCDEEngine::activeFiligreePalette(void)

{
  long in_RSI;
  QMap<QString,QVariant> *in_RDI;
  
  QMap<QString,QVariant>::QMap(in_RDI,(QMap *)(in_RSI + 0x4d8));
  return in_RDI;
}



// ==== 00172462  NCDEEngine::activeFiligreePaletteName

/* NCDEEngine::activeFiligreePaletteName() const */

QString * NCDEEngine::activeFiligreePaletteName(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x4e0));
  return in_RDI;
}



// ==== 00172492  NCDEEngine::setWifiEnabled

/* NCDEEngine::setWifiEnabled(bool) */

void __thiscall NCDEEngine::setWifiEnabled(NCDEEngine *this,bool param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setWifiEnabled(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 001724ce  NCDEEngine::connectNetwork

/* NCDEEngine::connectNetwork(QString const&, QString const&) */

void __thiscall NCDEEngine::connectNetwork(NCDEEngine *this,QString *param_1,QString *param_2)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::connectWifi(*(Lelan **)(this + 0x4c8),param_1,param_2);
  }
  return;
}



// ==== 00172514  NCDEEngine::disconnectNetwork

/* NCDEEngine::disconnectNetwork() */

void __thiscall NCDEEngine::disconnectNetwork(NCDEEngine *this)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::disconnectWifi(*(Lelan **)(this + 0x4c8));
  }
  return;
}



// ==== 00172546  NCDEEngine::connectVpn

/* NCDEEngine::connectVpn(QString const&) */

void NCDEEngine::connectVpn(QString *param_1)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::connectVpn(*(QString **)(param_1 + 0x4c8));
  }
  return;
}



// ==== 00172584  NCDEEngine::disconnectVpn

/* NCDEEngine::disconnectVpn(QString const&) */

void __thiscall NCDEEngine::disconnectVpn(NCDEEngine *this,QString *param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::disconnectVpn(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 001725c2  NCDEEngine::setBluetoothEnabled

/* NCDEEngine::setBluetoothEnabled(bool) */

void __thiscall NCDEEngine::setBluetoothEnabled(NCDEEngine *this,bool param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setBluetoothEnabled(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 001725fe  NCDEEngine::setBluetoothDiscoverable

/* NCDEEngine::setBluetoothDiscoverable(bool) */

void __thiscall NCDEEngine::setBluetoothDiscoverable(NCDEEngine *this,bool param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setBluetoothDiscoverable(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 0017263a  NCDEEngine::bluetoothConnect

/* NCDEEngine::bluetoothConnect(QString const&) */

void NCDEEngine::bluetoothConnect(QString *param_1)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::bluetoothConnect(*(QString **)(param_1 + 0x4c8));
  }
  return;
}



// ==== 00172678  NCDEEngine::bluetoothDisconnect

/* NCDEEngine::bluetoothDisconnect(QString const&) */

void NCDEEngine::bluetoothDisconnect(QString *param_1)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::bluetoothDisconnect(*(QString **)(param_1 + 0x4c8));
  }
  return;
}



// ==== 001726b6  NCDEEngine::bluetoothPair

/* NCDEEngine::bluetoothPair(QString const&) */

void NCDEEngine::bluetoothPair(QString *param_1)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::bluetoothPair(*(QString **)(param_1 + 0x4c8));
  }
  return;
}



// ==== 001726f4  NCDEEngine::bluetoothRemove

/* NCDEEngine::bluetoothRemove(QString const&) */

void NCDEEngine::bluetoothRemove(QString *param_1)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::bluetoothRemove(*(QString **)(param_1 + 0x4c8));
  }
  return;
}



// ==== 00172732  NCDEEngine::bluetoothScan

/* NCDEEngine::bluetoothScan() */

void __thiscall NCDEEngine::bluetoothScan(NCDEEngine *this)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::bluetoothScan(*(Lelan **)(this + 0x4c8));
  }
  return;
}



// ==== 00172764  NCDEEngine::refreshLocation

/* NCDEEngine::refreshLocation() */

void __thiscall NCDEEngine::refreshLocation(NCDEEngine *this)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::refreshLocation(*(Lelan **)(this + 0x4c8));
  }
  return;
}



// ==== 00172796  NCDEEngine::setTimezone

/* NCDEEngine::setTimezone(QString const&) */

void __thiscall NCDEEngine::setTimezone(NCDEEngine *this,QString *param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setTimezone(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 001727d4  NCDEEngine::setNtp

/* NCDEEngine::setNtp(bool) */

void __thiscall NCDEEngine::setNtp(NCDEEngine *this,bool param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setNtp(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 00172810  NCDEEngine::addUser

/* NCDEEngine::addUser(QString const&, QString const&, bool) */

void __thiscall NCDEEngine::addUser(NCDEEngine *this,QString *param_1,QString *param_2,bool param_3)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::addUser(*(Lelan **)(this + 0x4c8),param_1,param_2,param_3);
  }
  return;
}



// ==== 0017285a  NCDEEngine::removeUser

/* NCDEEngine::removeUser(QString const&) */

void __thiscall NCDEEngine::removeUser(NCDEEngine *this,QString *param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::removeUser(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 00172898  NCDEEngine::setUserAdmin

/* NCDEEngine::setUserAdmin(QString const&, bool) */

void __thiscall NCDEEngine::setUserAdmin(NCDEEngine *this,QString *param_1,bool param_2)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setUserAdmin(*(Lelan **)(this + 0x4c8),param_1,param_2);
  }
  return;
}



// ==== 001728dc  NCDEEngine::changePassword

/* NCDEEngine::changePassword(QString const&, QString const&) */

void NCDEEngine::changePassword(QString *param_1,QString *param_2)

{
  if (*(long *)(param_1 + 0x4c8) != 0) {
    Lelan::changePassword(*(QString **)(param_1 + 0x4c8),param_2);
  }
  return;
}



// ==== 00172922  NCDEEngine::setAutoLogin

/* NCDEEngine::setAutoLogin(QString const&, bool) */

void __thiscall NCDEEngine::setAutoLogin(NCDEEngine *this,QString *param_1,bool param_2)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setAutoLogin(*(Lelan **)(this + 0x4c8),param_1,param_2);
  }
  return;
}



// ==== 00172966  NCDEEngine::setUserAvatar

/* NCDEEngine::setUserAvatar(QString const&, QString const&) */

void __thiscall NCDEEngine::setUserAvatar(NCDEEngine *this,QString *param_1,QString *param_2)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setUserAvatar(*(Lelan **)(this + 0x4c8),param_1,param_2);
  }
  return;
}



// ==== 001729ac  NCDEEngine::setDefaultPrinter

/* NCDEEngine::setDefaultPrinter(QString const&) */

void __thiscall NCDEEngine::setDefaultPrinter(NCDEEngine *this,QString *param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setDefaultPrinter(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 001729ea  NCDEEngine::removePrinter

/* NCDEEngine::removePrinter(QString const&) */

void __thiscall NCDEEngine::removePrinter(NCDEEngine *this,QString *param_1)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::removePrinter(*(Lelan **)(this + 0x4c8),param_1);
  }
  return;
}



// ==== 00172a28  NCDEEngine::setAppVolume

/* NCDEEngine::setAppVolume(QString const&, int) */

void __thiscall NCDEEngine::setAppVolume(NCDEEngine *this,QString *param_1,int param_2)

{
  if (*(long *)(this + 0x4c8) != 0) {
    Lelan::setAppVolume(*(Lelan **)(this + 0x4c8),param_1,param_2);
  }
  return;
}



// ==== 00172a6b  NCDEEngine::setTerminalConfigField

/* NCDEEngine::setTerminalConfigField(QString const&, QVariant const&) */

void NCDEEngine::setTerminalConfigField(QString *param_1,QVariant *param_2)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QDir local_b0 [8];
  QFileInfo local_a8 [8];
  undefined1 *local_a0;
  QString local_98 [32];
  undefined8 local_78 [4];
  QArrayDataPointer<char16_t> local_58 [32];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a0 = &LAB_0029a07f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"/.config/ncde-terminal/config.json",0x22);
  QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
  QDir::homePath();
  ::operator+(local_98,(QString *)local_78);
  QString::~QString((QString *)local_78);
  QString::~QString((QString *)local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QString::QString((QString *)local_58);
  QDir::QDir(local_b0,(QString *)local_58);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_78);
  QFileInfo::QFileInfo(local_a8,local_98);
  QFileInfo::absolutePath();
  QDir::mkpath(local_b0,local_38,local_78[0]);
  QString::~QString((QString *)local_38);
  QFileInfo::~QFileInfo(local_a8);
  QDir::~QDir(local_b0);
  QString::~QString((QString *)local_58);
  QJsonObject::QJsonObject((QJsonObject *)local_b0);
  QFile::QFile((QFile *)local_78,local_98);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_78,local_38[0]);
  if (cVar1 != '\0') {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_58,(QJsonParseError *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QFileDevice::close();
    cVar1 = QJsonDocument::isObject();
    if (cVar1 != '\0') {
      QJsonDocument::object();
      QJsonObject::operator=((QJsonObject *)local_b0,(QJsonObject *)local_38);
      QJsonObject::~QJsonObject((QJsonObject *)local_38);
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_58);
  }
  QJsonValue::fromVariant((QVariant *)local_38);
  local_58._0_16_ = QJsonObject::operator[]((QString *)local_b0);
  QJsonValueRef::operator=((QJsonValueRef *)local_58,(QJsonValue *)local_38);
  QJsonValue::~QJsonValue((QJsonValue *)local_38);
  QFile::QFile((QFile *)local_58,local_98);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_58,uVar2);
  if (cVar1 != '\0') {
    QJsonDocument::QJsonDocument((QJsonDocument *)local_a8,(QJsonObject *)local_b0);
    QJsonDocument::toJson(local_38,local_a8,0);
    QIODevice::write((QByteArray *)local_58);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_a8);
    QFileDevice::close();
  }
  QFile::~QFile((QFile *)local_58);
  QFile::~QFile((QFile *)local_78);
  QJsonObject::~QJsonObject((QJsonObject *)local_b0);
  QString::~QString(local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00172f59  NCDEEngine::filigreePalettesPath

/* NCDEEngine::filigreePalettesPath() */

NCDEEngine * __thiscall NCDEEngine::filigreePalettesPath(NCDEEngine *this)

{
  long in_FS_OFFSET;
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"/.config/ncde/filigree-palettes.json",0x24);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  QDir::homePath();
  ::operator+((QString *)this,local_78);
  QString::~QString(local_78);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017306c  NCDEEngine::filigreePalettesRaw

/* NCDEEngine::filigreePalettesRaw() */

NCDEEngine * __thiscall NCDEEngine::filigreePalettesRaw(NCDEEngine *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QByteArray local_80 [8];
  QMap<QString,QVariant> local_78 [8];
  undefined1 *local_70;
  QFile local_68 [16];
  QArrayDataPointer<char16_t> local_58 [32];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesPath((NCDEEngine *)local_38);
  QFile::QFile(local_68,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_68,local_38[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson(local_80,(QJsonParseError *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    cVar1 = QJsonDocument::isObject();
    if (cVar1 == '\x01') {
      QJsonDocument::object();
      QJsonObject::toVariantMap();
      QJsonObject::~QJsonObject((QJsonObject *)local_38);
      local_70 = &LAB_0029a13a;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"_active",7);
      QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
      QMap<QString,QVariant>::remove(local_78,(QString *)local_38);
      QString::~QString((QString *)local_38);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
      QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)this,(QMap *)local_78);
      QMap<QString,QVariant>::~QMap(local_78);
    }
    else {
      *(undefined8 *)this = 0;
      QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)this);
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_80);
  }
  else {
    *(undefined8 *)this = 0;
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)this);
  }
  QFile::~QFile(local_68);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00173321  NCDEEngine::writeFiligreePalettes

/* NCDEEngine::writeFiligreePalettes(QMap<QString, QVariant> const&) */

bool NCDEEngine::writeFiligreePalettes(QMap *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  undefined4 uVar6;
  long in_FS_OFFSET;
  QMap local_138 [8];
  QByteArray local_130 [8];
  QJsonObject local_128 [8];
  undefined1 *local_120;
  undefined1 *local_118;
  undefined1 *local_110;
  QFile local_108 [16];
  undefined1 local_f8 [16];
  NCDEEngine local_e8 [32];
  QDir local_c8 [32];
  QFileInfo local_a8 [32];
  undefined8 local_88 [4];
  QString local_68 [32];
  undefined4 local_48 [6];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesPath(local_e8);
  QString::QString(local_68);
  QDir::QDir(local_c8,local_68);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_88);
  QFileInfo::QFileInfo(local_a8,(QString *)local_e8);
  QFileInfo::absolutePath();
  QDir::mkpath(local_c8,local_48,local_88[0]);
  QString::~QString((QString *)local_48);
  QFileInfo::~QFileInfo(local_a8);
  QDir::~QDir(local_c8);
  QString::~QString(local_68);
  QJsonObject::fromVariantMap(local_138);
  QFile::QFile(local_108,(QString *)local_e8);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_48,1);
  cVar5 = QFile::open(local_108,local_48[0]);
  if (cVar5 == '\0') goto LAB_001736f2;
  QIODevice::readAll();
  QJsonDocument::fromJson(local_130,(QJsonParseError *)local_48);
  QByteArray::~QByteArray((QByteArray *)local_48);
  QFileDevice::close();
  bVar3 = false;
  bVar2 = false;
  bVar1 = false;
  cVar5 = QJsonDocument::isObject();
  if (cVar5 == '\0') {
LAB_0017355c:
    bVar4 = false;
  }
  else {
    QJsonDocument::object();
    bVar3 = true;
    local_120 = &LAB_0029a13a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_68,(QTypedArrayData *)0x0,L"_active",7);
    bVar2 = true;
    QString::QString((QString *)local_48,(QArrayDataPointer *)local_68);
    bVar1 = true;
    cVar5 = QJsonObject::contains((QString *)local_88);
    if (cVar5 == '\0') goto LAB_0017355c;
    bVar4 = true;
  }
  if (bVar1) {
    QString::~QString((QString *)local_48);
  }
  if (bVar2) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_68);
  }
  if (bVar3) {
    QJsonObject::~QJsonObject((QJsonObject *)local_88);
  }
  if (bVar4) {
    QJsonDocument::object();
    local_118 = &LAB_0029a13a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"_active",7);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    QJsonObject::value((QString *)local_48);
    local_110 = &LAB_0029a13a;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"_active",7);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    local_f8 = QJsonObject::operator[]((QString *)local_138);
    QJsonValueRef::operator=((QJsonValueRef *)local_f8,(QJsonValue *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    QJsonValue::~QJsonValue((QJsonValue *)local_48);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
    QJsonObject::~QJsonObject(local_128);
  }
  QJsonDocument::~QJsonDocument((QJsonDocument *)local_130);
LAB_001736f2:
  QFile::QFile((QFile *)local_68,(QString *)local_e8);
  uVar6 = operator|(2,8);
  cVar5 = QFile::open(local_68,uVar6);
  if (cVar5 == '\x01') {
    QJsonDocument::QJsonDocument((QJsonDocument *)local_88,(QJsonObject *)local_138);
    QJsonDocument::toJson(local_48,local_88,0);
    QIODevice::write((QByteArray *)local_68);
    QByteArray::~QByteArray((QByteArray *)local_48);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_88);
    QFileDevice::close();
  }
  QFile::~QFile((QFile *)local_68);
  QFile::~QFile(local_108);
  QJsonObject::~QJsonObject((QJsonObject *)local_138);
  QString::~QString((QString *)local_e8);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return cVar5 == '\x01';
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001739a4  NCDEEngine::writeActiveFiligreepaletteName

/* NCDEEngine::writeActiveFiligreepaletteName() const */

void __thiscall NCDEEngine::writeActiveFiligreepaletteName(NCDEEngine *this)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QJsonObject local_c8 [8];
  undefined1 *local_c0;
  QDir local_b8 [16];
  QFileInfo local_a8 [16];
  NCDEEngine local_98 [32];
  undefined8 local_78 [4];
  QString local_58 [32];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesPath(local_98);
  QString::QString(local_58);
  QDir::QDir(local_b8,local_58);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_78);
  QFileInfo::QFileInfo(local_a8,(QString *)local_98);
  QFileInfo::absolutePath();
  QDir::mkpath(local_b8,local_38,local_78[0]);
  QString::~QString((QString *)local_38);
  QFileInfo::~QFileInfo(local_a8);
  QDir::~QDir(local_b8);
  QString::~QString(local_58);
  QJsonObject::QJsonObject(local_c8);
  QFile::QFile((QFile *)local_b8,(QString *)local_98);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,1);
  cVar1 = QFile::open(local_b8,local_38[0]);
  if (cVar1 != '\0') {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_58,(QJsonParseError *)local_38);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QFileDevice::close();
    cVar1 = QJsonDocument::isObject();
    if (cVar1 != '\0') {
      QJsonDocument::object();
      QJsonObject::operator=(local_c8,(QJsonObject *)local_38);
      QJsonObject::~QJsonObject((QJsonObject *)local_38);
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_58);
  }
  QJsonValue::QJsonValue((QJsonValue *)local_38,(QString *)(this + 0x4e0));
  local_c0 = &LAB_0029a13a;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"_active",7);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  local_a8 = (QFileInfo  [16])QJsonObject::operator[]((QString *)local_c8);
  QJsonValueRef::operator=((QJsonValueRef *)local_a8,(QJsonValue *)local_38);
  QString::~QString(local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
  QJsonValue::~QJsonValue((QJsonValue *)local_38);
  QFile::QFile((QFile *)local_58,(QString *)local_98);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_58,uVar2);
  if (cVar1 != '\0') {
    QJsonDocument::QJsonDocument((QJsonDocument *)local_78,local_c8);
    QJsonDocument::toJson(local_38,local_78,0);
    QIODevice::write((QByteArray *)local_58);
    QByteArray::~QByteArray((QByteArray *)local_38);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_78);
    QFileDevice::close();
  }
  QFile::~QFile((QFile *)local_58);
  QFile::~QFile((QFile *)local_b8);
  QJsonObject::~QJsonObject(local_c8);
  QString::~QString((QString *)local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00173e48  NCDEEngine::loadActiveFiligreepalette

/* NCDEEngine::loadActiveFiligreepalette() */

void __thiscall NCDEEngine::loadActiveFiligreepalette(NCDEEngine *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QByteArray local_110 [8];
  QJsonObject local_108 [8];
  undefined1 *local_100;
  QFile local_f8 [16];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QString local_a8 [32];
  undefined4 local_88 [8];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  filigreePalettesPath((NCDEEngine *)local_88);
  QFile::QFile(local_f8,(QString *)local_88);
  QString::~QString((QString *)local_88);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_88,1);
  cVar1 = QFile::open(local_f8,local_88[0]);
  if (cVar1 == '\x01') {
    QIODevice::readAll();
    QJsonDocument::fromJson(local_110,(QJsonParseError *)local_88);
    QByteArray::~QByteArray((QByteArray *)local_88);
    cVar1 = QJsonDocument::isObject();
    if (cVar1 == '\x01') {
      QJsonDocument::object();
      local_100 = &LAB_0029a13a;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"_active",7);
      QString::QString(local_a8,(QArrayDataPointer *)local_c8);
      QJsonObject::value((QString *)local_88);
      QJsonValue::toString();
      QJsonValue::~QJsonValue((QJsonValue *)local_88);
      QString::~QString(local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
      cVar1 = QString::isEmpty(local_e8);
      if (cVar1 == '\0') {
        filigreePalettesRaw((NCDEEngine *)local_a8);
        cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_a8,local_e8);
        if (cVar1 == '\x01') {
          QString::operator=((QString *)(this + 0x4e0),local_e8);
          ::QVariant::QVariant(local_68);
          QMap<QString,QVariant>::value(local_48,(QVariant *)local_a8);
          ::QVariant::toMap();
          QMap<QString,QVariant>::operator=
                    ((QMap<QString,QVariant> *)(this + 0x4d8),(QMap *)local_88);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_88);
          ::QVariant::~QVariant((QVariant *)local_48);
          ::QVariant::~QVariant(local_68);
        }
        QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_a8);
      }
      QString::~QString(local_e8);
      QJsonObject::~QJsonObject(local_108);
    }
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_110);
  }
  QFile::~QFile(local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001742aa  NCDEEngine::brightness

/* NCDEEngine::brightness(QColor const&) */

double NCDEEngine::brightness(QColor *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (float)QColor::redF();
  fVar2 = (float)QColor::greenF();
  fVar3 = (float)QColor::blueF();
  return (((double)fVar3 * 0.11 + (double)fVar1 * 0.3 + (double)fVar2 * 0.59) * 25.0 +
         (((double)fVar1 + (double)fVar2 + (double)fVar3) / 3.0) * 75.0) / 100.0;
}



// ==== 00174389  NCDEEngine::clamp01

/* NCDEEngine::clamp01(double) */

double NCDEEngine::clamp01(double param_1)

{
  if (0.0 <= param_1) {
    if (1.0 < param_1) {
      param_1 = 1.0;
    }
  }
  else {
    param_1 = 0.0;
  }
  return param_1;
}



// ==== 001743c7  NCDEEngine::liteScale

/* NCDEEngine::liteScale(QColor const&, int) */

undefined8 NCDEEngine::liteScale(QColor *param_1,int param_2)

{
  long lVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  float fVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  dVar4 = 1.0 - (double)param_2 / 100.0;
  fVar3 = (float)QColor::blueF();
  dVar5 = (double)clamp01((double)fVar3 * dVar4);
  fVar3 = (float)QColor::greenF();
  dVar6 = (double)clamp01((double)fVar3 * dVar4);
  fVar3 = (float)QColor::redF();
  dVar4 = (double)clamp01((double)fVar3 * dVar4);
  uVar2 = QColor::fromRgbF((float)dVar4,(float)dVar6,(float)dVar5,1.0);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 001744e2  NCDEEngine::darkScale

/* NCDEEngine::darkScale(QColor const&, int) */

undefined8 NCDEEngine::darkScale(QColor *param_1,int param_2)

{
  long lVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  dVar5 = (double)param_2 / 100.0;
  fVar3 = (float)QColor::blueF();
  fVar4 = (float)QColor::blueF();
  dVar6 = (double)clamp01((double)(1.0 - fVar4) * dVar5 + (double)fVar3);
  fVar3 = (float)QColor::greenF();
  fVar4 = (float)QColor::greenF();
  dVar7 = (double)clamp01((double)(1.0 - fVar4) * dVar5 + (double)fVar3);
  fVar3 = (float)QColor::redF();
  fVar4 = (float)QColor::redF();
  dVar5 = (double)clamp01((double)(1.0 - fVar4) * dVar5 + (double)fVar3);
  uVar2 = QColor::fromRgbF((float)dVar5,(float)dVar7,(float)dVar6,1.0);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 00174677  NCDEEngine::labF

/* NCDEEngine::labF(double) */

double NCDEEngine::labF(double param_1)

{
  double dVar1;
  
  if (param_1 <= 0.008856) {
    dVar1 = param_1 * 7.787 + 0.13793103448275862;
  }
  else {
    dVar1 = cbrt(param_1);
  }
  return dVar1;
}



// ==== 001746c2  NCDEEngine::rgbToLab(int,int,int,NCDEEngine::Lab&)::{lambda(double)#1}::operator()

/* NCDEEngine::rgbToLab(int, int, int,
   NCDEEngine::Lab&)::{lambda(double)#1}::TEMPNAMEPLACEHOLDERVALUE(double) const */

double __thiscall
NCDEEngine::rgbToLab(int,int,int,NCDEEngine::Lab&)::{lambda(double)#1}::operator()
          (_lambda_double__1_ *this,double param_1)

{
  double dVar1;
  
  dVar1 = param_1 / 255.0;
  if (0.04045 < dVar1) {
    dVar1 = pow((dVar1 + 0.055) / 1.055,2.4);
  }
  else {
    dVar1 = dVar1 / 12.92;
  }
  return dVar1;
}



// ==== 00174745  NCDEEngine::rgbToLab

/* NCDEEngine::rgbToLab(int, int, int, NCDEEngine::Lab&) */

void NCDEEngine::rgbToLab(int param_1,int param_2,int param_3,Lab *param_4)

{
  long in_FS_OFFSET;
  _lambda_double__1_ local_41;
  double local_40;
  double local_38;
  double local_30;
  double local_28;
  double local_20;
  double local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_40 = (double)rgbToLab(int,int,int,NCDEEngine::Lab&)::{lambda(double)#1}::operator()
                               (&local_41,(double)param_1);
  local_38 = (double)rgbToLab(int,int,int,NCDEEngine::Lab&)::{lambda(double)#1}::operator()
                               (&local_41,(double)param_2);
  local_30 = (double)rgbToLab(int,int,int,NCDEEngine::Lab&)::{lambda(double)#1}::operator()
                               (&local_41,(double)param_3);
  local_28 = (local_30 * 0.1805 + local_40 * 0.4124 + local_38 * 0.3576) / 0.95047;
  local_20 = local_30 * 0.0722 + local_40 * 0.2126 + local_38 * 0.7152;
  local_18 = (local_30 * 0.9505 + local_40 * 0.0193 + local_38 * 0.1192) / 1.08883;
  local_28 = (double)labF(local_28);
  local_20 = (double)labF(local_20);
  local_18 = (double)labF(local_18);
  *(double *)param_4 = local_20 * 116.0 - 16.0;
  *(double *)(param_4 + 8) = (local_28 - local_20) * 500.0;
  *(double *)(param_4 + 0x10) = (local_20 - local_18) * 200.0;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00174980  NCDEEngine::labDist2

/* NCDEEngine::labDist2(NCDEEngine::Lab const&, NCDEEngine::Lab const&) */

double NCDEEngine::labDist2(Lab *param_1,Lab *param_2)

{
  return (*(double *)(param_1 + 0x10) - *(double *)(param_2 + 0x10)) *
         (*(double *)(param_1 + 0x10) - *(double *)(param_2 + 0x10)) +
         (*(double *)param_1 - *(double *)param_2) * (*(double *)param_1 - *(double *)param_2) +
         (*(double *)(param_1 + 8) - *(double *)(param_2 + 8)) *
         (*(double *)(param_1 + 8) - *(double *)(param_2 + 8));
}



// ==== 00174a04  NCDEEngine::labToColor(NCDEEngine::Lab_const&)::{lambda(double)#1}::operator()

/* NCDEEngine::labToColor(NCDEEngine::Lab
   const&)::{lambda(double)#1}::TEMPNAMEPLACEHOLDERVALUE(double) const */

double __thiscall
NCDEEngine::labToColor(NCDEEngine::Lab_const&)::{lambda(double)#1}::operator()
          (_lambda_double__1_ *this,double param_1)

{
  double dVar1;
  
  dVar1 = param_1 * param_1 * param_1;
  if (dVar1 <= 0.008856) {
    dVar1 = (param_1 - 0.13793103448275862) / 7.787;
  }
  return dVar1;
}



// ==== 00174a5e  NCDEEngine::labToColor(NCDEEngine::Lab_const&)::{lambda(double)#2}::operator()

/* NCDEEngine::labToColor(NCDEEngine::Lab
   const&)::{lambda(double)#2}::TEMPNAMEPLACEHOLDERVALUE(double) const */

double __thiscall
NCDEEngine::labToColor(NCDEEngine::Lab_const&)::{lambda(double)#2}::operator()
          (_lambda_double__2_ *this,double param_1)

{
  double dVar1;
  undefined8 local_18;
  
  if (0.0 <= param_1) {
    local_18 = param_1;
    if (1.0 < param_1) {
      local_18 = 1.0;
    }
  }
  else {
    local_18 = 0.0;
  }
  if (0.0031308 < local_18) {
    dVar1 = pow(local_18,0.4166666666666667);
    local_18 = dVar1 * 1.055 - 0.055;
  }
  else {
    local_18 = local_18 * 12.92;
  }
  return local_18;
}



// ==== 00174afb  NCDEEngine::labToColor

/* NCDEEngine::labToColor(NCDEEngine::Lab const&) */

undefined8 NCDEEngine::labToColor(Lab *param_1)

{
  long in_FS_OFFSET;
  double dVar1;
  double dVar2;
  double dVar3;
  _lambda_double__1_ local_72;
  _lambda_double__2_ local_71;
  double local_70;
  double local_68;
  double local_60;
  double local_58;
  double local_50;
  double local_48;
  double local_40;
  double local_38;
  double local_30;
  undefined1 local_28 [16];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_70 = (*(double *)param_1 + 16.0) / 116.0;
  local_68 = *(double *)(param_1 + 8) / 500.0 + local_70;
  local_60 = local_70 - *(double *)(param_1 + 0x10) / 200.0;
  local_58 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#1}::operator()
                               (&local_72,local_68);
  local_58 = local_58 * 0.95047;
  local_50 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#1}::operator()
                               (&local_72,local_70);
  local_48 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#1}::operator()
                               (&local_72,local_60);
  local_48 = local_48 * 1.08883;
  local_40 = local_48 * -0.4986 + local_58 * 3.2406 + local_50 * -1.5372;
  local_38 = local_48 * 0.0415 + local_58 * -0.9689 + local_50 * 1.8758;
  local_30 = local_48 * 1.057 + local_58 * 0.0557 + local_50 * -0.204;
  dVar1 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#2}::operator()
                            (&local_71,local_30);
  dVar2 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#2}::operator()
                            (&local_71,local_38);
  dVar3 = (double)labToColor(NCDEEngine::Lab_const&)::{lambda(double)#2}::operator()
                            (&local_71,local_40);
  local_28 = QColor::fromRgbF((float)dVar3,(float)dVar2,(float)dVar1,1.0);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28._0_8_;
}



// ==== 00174d64  NCDEEngine::mixLab

/* NCDEEngine::mixLab(QColor const&, QColor const&, double) */

undefined8 NCDEEngine::mixLab(QColor *param_1,QColor *param_2,double param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long in_FS_OFFSET;
  double local_a8;
  double local_a0;
  double local_98;
  double local_88;
  double local_80;
  double local_78;
  double local_68;
  double local_60;
  double local_58;
  undefined1 local_48 [16];
  undefined1 local_38 [16];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iVar1 = QColor::blue();
  iVar2 = QColor::green();
  iVar3 = QColor::red();
  rgbToLab(iVar3,iVar2,iVar1,(Lab *)&local_a8);
  iVar1 = QColor::blue();
  iVar2 = QColor::green();
  iVar3 = QColor::red();
  rgbToLab(iVar3,iVar2,iVar1,(Lab *)&local_88);
  local_68 = (local_88 - local_a8) * param_3 + local_a8;
  local_60 = (local_80 - local_a0) * param_3 + local_a0;
  local_58 = (local_78 - local_98) * param_3 + local_98;
  local_48 = labToColor((Lab *)&local_68);
  QColor::alpha();
  QColor::setAlpha((int)local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
    local_38 = local_48;
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_48._0_8_;
}



// ==== 00174f0e  NCDEEngine::calcColors

/* NCDEEngine::calcColors(QColor const&, QColor&, QColor&, QColor&, QColor&) const */

void __thiscall
NCDEEngine::calcColors
          (NCDEEngine *this,QColor *param_1,QColor *param_2,QColor *param_3,QColor *param_4,
          QColor *param_5)

{
  long in_FS_OFFSET;
  double dVar1;
  undefined1 auVar2 [16];
  undefined6 local_28;
  undefined2 uStack_22;
  undefined6 local_20;
  undefined2 uStack_1a;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  dVar1 = (double)brightness(param_1);
  if (dVar1 <= 0.7) {
    QColor::QColor((QColor *)&local_28,3);
  }
  else {
    QColor::QColor((QColor *)&local_28,2);
  }
  *(ulong *)param_2 = CONCAT26(uStack_22,local_28);
  *(ulong *)(param_2 + 6) = CONCAT62(local_20,uStack_22);
  if (0.2 <= dVar1) {
    if (dVar1 < 0.46) {
      dVar1 = (dVar1 - 0.2) / 0.26;
      auVar2 = darkScale(param_1,(int)(dVar1 * 30.0 + 20.0));
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_3 = auVar2._0_8_;
      *(long *)(param_3 + 6) = auVar2._6_8_;
      auVar2 = liteScale(param_1,0x28);
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_4 = auVar2._0_8_;
      *(long *)(param_4 + 6) = auVar2._6_8_;
      auVar2 = liteScale(param_1,(int)(dVar1 * 25.0 + 15.0));
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_5 = auVar2._0_8_;
      *(long *)(param_5 + 6) = auVar2._6_8_;
    }
    else {
      auVar2 = liteScale(param_1,0x14);
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_3 = auVar2._0_8_;
      *(long *)(param_3 + 6) = auVar2._6_8_;
      auVar2 = liteScale(param_1,0x28);
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_4 = auVar2._0_8_;
      *(long *)(param_4 + 6) = auVar2._6_8_;
      auVar2 = liteScale(param_1,0xf);
      local_28 = auVar2._0_6_;
      uStack_22 = auVar2._6_2_;
      local_20 = auVar2._8_6_;
      uStack_1a = auVar2._14_2_;
      *(long *)param_5 = auVar2._0_8_;
      *(long *)(param_5 + 6) = auVar2._6_8_;
    }
  }
  else {
    auVar2 = darkScale(param_1,0x32);
    local_28 = auVar2._0_6_;
    uStack_22 = auVar2._6_2_;
    local_20 = auVar2._8_6_;
    uStack_1a = auVar2._14_2_;
    *(long *)param_3 = auVar2._0_8_;
    *(long *)(param_3 + 6) = auVar2._6_8_;
    auVar2 = darkScale(param_1,0x1e);
    local_28 = auVar2._0_6_;
    uStack_22 = auVar2._6_2_;
    local_20 = auVar2._8_6_;
    uStack_1a = auVar2._14_2_;
    *(long *)param_4 = auVar2._0_8_;
    *(long *)(param_4 + 6) = auVar2._6_8_;
    auVar2 = darkScale(param_1,0xf);
    local_28 = auVar2._0_6_;
    uStack_22 = auVar2._6_2_;
    local_20 = auVar2._8_6_;
    uStack_1a = auVar2._14_2_;
    *(long *)param_5 = auVar2._0_8_;
    *(long *)(param_5 + 6) = auVar2._6_8_;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017520a  NCDEEngine::deriveAccentSurface

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* NCDEEngine::deriveAccentSurface() */

void __thiscall NCDEEngine::deriveAccentSurface(NCDEEngine *this)

{
  int iVar1;
  float *pfVar2;
  long in_FS_OFFSET;
  undefined1 auVar3 [16];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  int local_40;
  float local_3c;
  undefined6 local_38;
  undefined2 uStack_32;
  undefined6 local_30;
  undefined2 uStack_2a;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QColor::getHsvF((float *)(this + 0x2c),&local_50,&local_4c,&local_48);
  if (local_50 < 0.0) {
    local_50 = 0.0;
  }
  local_44 = 0.35;
  pfVar2 = qMax<float>(&local_44,&local_4c);
  local_3c = *pfVar2;
  for (local_40 = 0; local_40 < 6; local_40 = local_40 + 1) {
    auVar3 = QColor::fromHsvF(local_50,local_3c,
                              *(float *)(&deriveAccentSurface()::V + (long)local_40 * 4),1.0);
    local_38 = auVar3._0_6_;
    uStack_32 = auVar3._6_2_;
    local_30 = auVar3._8_6_;
    uStack_2a = auVar3._14_2_;
    *(long *)(this + ((long)local_40 + 0x12) * 0x10 + 0xc) = auVar3._0_8_;
    *(long *)(this + ((long)local_40 + 0x12) * 0x10 + 0x12) = auVar3._6_8_;
  }
  if (deriveAccentSurface()::kVerd == '\0') {
    iVar1 = __cxa_guard_acquire(&deriveAccentSurface()::kVerd);
    if (iVar1 != 0) {
      auVar3 = QColor::fromHsvF(0.39,0.55,0.65,1.0);
      deriveAccentSurface()::kVerd._0_6_ = auVar3._0_6_;
      deriveAccentSurface()::kVerd._6_2_ = auVar3._6_2_;
      _DAT_0032f9c8 = auVar3._8_6_;
      uRam000000000032f9ce = auVar3._14_2_;
      __cxa_guard_release(&deriveAccentSurface()::kVerd);
    }
  }
  if (deriveAccentSurface()::kCer == '\0') {
    iVar1 = __cxa_guard_acquire(&deriveAccentSurface()::kCer);
    if (iVar1 != 0) {
      auVar3 = QColor::fromHsvF(0.65,0.55,0.65,1.0);
      deriveAccentSurface()::kCer._0_6_ = auVar3._0_6_;
      deriveAccentSurface()::kCer._6_2_ = auVar3._6_2_;
      _DAT_0032f9e8 = auVar3._8_6_;
      uRam000000000032f9ee = auVar3._14_2_;
      __cxa_guard_release(&deriveAccentSurface()::kCer);
    }
  }
  if (deriveAccentSurface()::kRose == '\0') {
    iVar1 = __cxa_guard_acquire(&deriveAccentSurface()::kRose);
    if (iVar1 != 0) {
      auVar3 = QColor::fromHsvF(0.92,0.6,0.78,1.0);
      deriveAccentSurface()::kRose._0_6_ = auVar3._0_6_;
      deriveAccentSurface()::kRose._6_2_ = auVar3._6_2_;
      _DAT_0032fa08 = auVar3._8_6_;
      uRam000000000032fa0e = auVar3._14_2_;
      __cxa_guard_release(&deriveAccentSurface()::kRose);
    }
  }
  if (deriveAccentSurface()::kAmber == '\0') {
    iVar1 = __cxa_guard_acquire(&deriveAccentSurface()::kAmber);
    if (iVar1 != 0) {
      auVar3 = QColor::fromHsvF(0.11,0.75,0.91,1.0);
      deriveAccentSurface()::kAmber._0_6_ = auVar3._0_6_;
      deriveAccentSurface()::kAmber._6_2_ = auVar3._6_2_;
      _DAT_0032fa28 = auVar3._8_6_;
      uRam000000000032fa2e = auVar3._14_2_;
      __cxa_guard_release(&deriveAccentSurface()::kAmber);
    }
  }
  *(ulong *)(this + 0xec) =
       CONCAT26(deriveAccentSurface()::kVerd._6_2_,(undefined6)deriveAccentSurface()::kVerd);
  *(ulong *)(this + 0xf2) = CONCAT62(_DAT_0032f9c8,deriveAccentSurface()::kVerd._6_2_);
  *(ulong *)(this + 0xfc) =
       CONCAT26(deriveAccentSurface()::kCer._6_2_,(undefined6)deriveAccentSurface()::kCer);
  *(ulong *)(this + 0x102) = CONCAT62(_DAT_0032f9e8,deriveAccentSurface()::kCer._6_2_);
  *(ulong *)(this + 0x10c) =
       CONCAT26(deriveAccentSurface()::kRose._6_2_,(undefined6)deriveAccentSurface()::kRose);
  *(ulong *)(this + 0x112) = CONCAT62(_DAT_0032fa08,deriveAccentSurface()::kRose._6_2_);
  *(ulong *)(this + 0x11c) =
       CONCAT26(deriveAccentSurface()::kAmber._6_2_,(undefined6)deriveAccentSurface()::kAmber);
  *(ulong *)(this + 0x122) = CONCAT62(_DAT_0032fa28,deriveAccentSurface()::kAmber._6_2_);
  auVar3 = QColor::fromHsvF(local_50,local_3c * 0.7,local_48 * 0.7,1.0);
  local_38 = auVar3._0_6_;
  uStack_32 = auVar3._6_2_;
  local_30 = auVar3._8_6_;
  uStack_2a = auVar3._14_2_;
  *(long *)(this + 0x3c) = auVar3._0_8_;
  *(long *)(this + 0x42) = auVar3._6_8_;
  *(undefined8 *)(this + 0x7c) = *(undefined8 *)(this + 0x16c);
  *(undefined8 *)(this + 0x82) = *(undefined8 *)(this + 0x172);
  *(undefined8 *)(this + 0x1cc) = *(undefined8 *)(this + 0x5c);
  *(undefined8 *)(this + 0x1d2) = *(undefined8 *)(this + 0x62);
  *(undefined8 *)(this + 0x1dc) = *(undefined8 *)(this + 0x6c);
  *(undefined8 *)(this + 0x1e2) = *(undefined8 *)(this + 0x72);
  *(undefined8 *)(this + 0x1ec) = *(undefined8 *)(this + 0xec);
  *(undefined8 *)(this + 0x1f2) = *(undefined8 *)(this + 0xf2);
  *(undefined8 *)(this + 0x1fc) = *(undefined8 *)(this + 0xfc);
  *(undefined8 *)(this + 0x202) = *(undefined8 *)(this + 0x102);
  *(undefined8 *)(this + 0x20c) = *(undefined8 *)(this + 0x2c);
  *(undefined8 *)(this + 0x212) = *(undefined8 *)(this + 0x32);
  *(undefined8 *)(this + 0x21c) = *(undefined8 *)(this + 0x10c);
  *(undefined8 *)(this + 0x222) = *(undefined8 *)(this + 0x112);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017578e  NCDEEngine::recompute

/* NCDEEngine::recompute() */

void __thiscall NCDEEngine::recompute(NCDEEngine *this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  char cVar3;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  undefined4 local_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  undefined2 local_20;
  undefined2 uStack_1e;
  undefined2 uStack_1c;
  undefined2 uStack_1a;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  cVar3 = QString::isEmpty((QString *)(this + 0x3b8));
  if (cVar3 == '\0') {
    QColor::QColor((QColor *)&local_28,(QString *)(this + 0x3b8));
  }
  else {
    uVar1 = *(undefined8 *)(this + 0x308);
    uVar2 = *(undefined8 *)(this + 0x300);
    local_28 = (undefined4)uVar2;
    uStack_24 = (undefined2)((ulong)uVar2 >> 0x20);
    uStack_22 = (undefined2)((ulong)uVar2 >> 0x30);
    local_20 = (undefined2)uVar1;
    uStack_1e = (undefined2)((ulong)uVar1 >> 0x10);
    uStack_1c = (undefined2)((ulong)uVar1 >> 0x20);
    uStack_1a = (undefined2)((ulong)uVar1 >> 0x30);
  }
  *(ulong *)(this + 0x2c) = CONCAT26(uStack_22,CONCAT24(uStack_24,local_28));
  *(ulong *)(this + 0x32) = CONCAT26(uStack_1c,CONCAT24(uStack_1e,CONCAT22(local_20,uStack_22)));
  cVar3 = QString::isEmpty((QString *)(this + 1000));
  if (cVar3 == '\0') {
    QColor::QColor((QColor *)&local_28,(QString *)(this + 1000));
  }
  else {
    uVar1 = *(undefined8 *)(this + 0x318);
    uVar2 = *(undefined8 *)(this + 0x310);
    local_28 = (undefined4)uVar2;
    uStack_24 = (undefined2)((ulong)uVar2 >> 0x20);
    uStack_22 = (undefined2)((ulong)uVar2 >> 0x30);
    local_20 = (undefined2)uVar1;
    uStack_1e = (undefined2)((ulong)uVar1 >> 0x10);
    uStack_1c = (undefined2)((ulong)uVar1 >> 0x20);
    uStack_1a = (undefined2)((ulong)uVar1 >> 0x30);
  }
  *(ulong *)(this + 0xac) = CONCAT26(uStack_22,CONCAT24(uStack_24,local_28));
  *(ulong *)(this + 0xb2) = CONCAT26(uStack_1c,CONCAT24(uStack_1e,CONCAT22(local_20,uStack_22)));
  cVar3 = QString::isEmpty((QString *)(this + 0x400));
  if (cVar3 == '\0') {
    QColor::QColor((QColor *)&local_28,(QString *)(this + 0x400));
  }
  else {
    uVar1 = *(undefined8 *)(this + 0x328);
    uVar2 = *(undefined8 *)(this + 800);
    local_28 = (undefined4)uVar2;
    uStack_24 = (undefined2)((ulong)uVar2 >> 0x20);
    uStack_22 = (undefined2)((ulong)uVar2 >> 0x30);
    local_20 = (undefined2)uVar1;
    uStack_1e = (undefined2)((ulong)uVar1 >> 0x10);
    uStack_1c = (undefined2)((ulong)uVar1 >> 0x20);
    uStack_1a = (undefined2)((ulong)uVar1 >> 0x30);
  }
  *(ulong *)(this + 0xbc) = CONCAT26(uStack_22,CONCAT24(uStack_24,local_28));
  *(ulong *)(this + 0xc2) = CONCAT26(uStack_1c,CONCAT24(uStack_1e,CONCAT22(local_20,uStack_22)));
  if (this[0x28] == (NCDEEngine)0x0) {
    auVar4 = liteScale((QColor *)(this + 0x5c),10);
    local_28 = auVar4._0_4_;
    uStack_24 = auVar4._4_2_;
    uStack_22 = auVar4._6_2_;
    local_20 = auVar4._8_2_;
    uStack_1e = auVar4._10_2_;
    uStack_1c = auVar4._12_2_;
    uStack_1a = auVar4._14_2_;
  }
  else {
    auVar4 = darkScale((QColor *)(this + 0x5c),8);
    local_28 = auVar4._0_4_;
    uStack_24 = auVar4._4_2_;
    uStack_22 = auVar4._6_2_;
    local_20 = auVar4._8_2_;
    uStack_1e = auVar4._10_2_;
    uStack_1c = auVar4._12_2_;
    uStack_1a = auVar4._14_2_;
  }
  *(ulong *)(this + 0x6c) = CONCAT26(uStack_22,CONCAT24(uStack_24,local_28));
  *(ulong *)(this + 0x72) = CONCAT26(uStack_1c,CONCAT24(uStack_1e,CONCAT22(local_20,uStack_22)));
  deriveAccentSurface(this);
  cVar3 = QString::isEmpty((QString *)(this + 0x3d0));
  if (cVar3 != '\x01') {
    QColor::QColor((QColor *)&local_28,(QString *)(this + 0x3d0));
    *(ulong *)(this + 0x3c) = CONCAT26(uStack_22,CONCAT24(uStack_24,local_28));
    *(ulong *)(this + 0x42) = CONCAT26(uStack_1c,CONCAT24(uStack_1e,CONCAT22(local_20,uStack_22)));
  }
  local_28 = 0;
  uStack_24 = 0xffff;
  uStack_22 = 0;
  local_20 = 0;
  uStack_1e = 0;
  uStack_1c = 0;
  calcColors(this,(QColor *)(this + 0x5c),(QColor *)(this + 0x22c),(QColor *)(this + 0x23c),
             (QColor *)(this + 0x24c),(QColor *)(this + 0x25c));
  calcColors(this,(QColor *)(this + 0x8c),(QColor *)(this + 0x26c),(QColor *)(this + 0x27c),
             (QColor *)(this + 0x28c),(QColor *)&local_28);
  changed(this);
  themeChanged(this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00175a5e  NCDEEngine::scheduleRecompute

/* NCDEEngine::scheduleRecompute() */

void __thiscall NCDEEngine::scheduleRecompute(NCDEEngine *this)

{
  char cVar1;
  
  cVar1 = QTimer::isActive();
  if (cVar1 != '\x01') {
    QTimer::start((int)this + 0x10);
  }
  return;
}



// ==== 00175a9a  NCDEEngine::applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()

/* NCDEEngine::applyPalette(QMap<QString, QVariant> const&)::{lambda(char const*,
   QColor&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*, QColor&) const */

void __thiscall
NCDEEngine::applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
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



// ==== 00175c7e  NCDEEngine::applyPalette

/* NCDEEngine::applyPalette(QMap<QString, QVariant> const&) */

void __thiscall NCDEEngine::applyPalette(NCDEEngine *this,QMap *param_1)

{
  char cVar1;
  NCDEEngine NVar2;
  long in_FS_OFFSET;
  QMap *local_90;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_90 = param_1;
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"accent",(QColor *)(this + 0x2c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"accentMuted",(QColor *)(this + 0x3c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"background",(QColor *)(this + 0x4c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"surface",(QColor *)(this + 0x5c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"surfaceAlt",(QColor *)(this + 0x6c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"panelBg",(QColor *)(this + 0x8c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"popupBg",(QColor *)(this + 0x9c));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"border",(QColor *)(this + 0xac));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"glow",(QColor *)(this + 0xbc));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"ink",(QColor *)(this + 0xcc));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"verd",(QColor *)(this + 0xec));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"cer",(QColor *)(this + 0xfc));
  applyPalette(QMap<QString,QVariant>const&)::{lambda(char_const*,QColor&)#1}::operator()
            ((_lambda_char_const__QColor___1_ *)&local_90,"rose",(QColor *)(this + 0x10c));
  QString::QString(local_88,"darkMode");
  cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)param_1,local_88);
  QString::~QString(local_88);
  if (cVar1 != '\0') {
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,"darkMode");
    QMap<QString,QVariant>::value(local_48,(QVariant *)param_1);
    NVar2 = (NCDEEngine)::QVariant::toBool();
    this[0x28] = NVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  recompute(this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00176154  NCDEEngine::~NCDEEngine

/* NCDEEngine::~NCDEEngine() */

void __thiscall NCDEEngine::~NCDEEngine(NCDEEngine *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c0a8;
  QString::~QString((QString *)(this + 0x4e0));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x4d8));
  QHash<QString,QMap<QString,QVariant>>::~QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4c0));
  QHash<QString,QMap<QString,QVariant>>::~QHash
            ((QHash<QString,QMap<QString,QVariant>> *)(this + 0x4b8));
  QString::~QString((QString *)(this + 0x490));
  QString::~QString((QString *)(this + 0x478));
  QString::~QString((QString *)(this + 0x460));
  QString::~QString((QString *)(this + 0x448));
  QString::~QString((QString *)(this + 0x430));
  QString::~QString((QString *)(this + 0x418));
  QString::~QString((QString *)(this + 0x400));
  QString::~QString((QString *)(this + 1000));
  QString::~QString((QString *)(this + 0x3d0));
  QString::~QString((QString *)(this + 0x3b8));
  QString::~QString((QString *)(this + 0x2e8));
  QString::~QString((QString *)(this + 0x2d0));
  QString::~QString((QString *)(this + 0x2b8));
  QTimer::~QTimer((QTimer *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001762c0  NCDEEngine::~NCDEEngine

/* NCDEEngine::~NCDEEngine() */

void __thiscall NCDEEngine::~NCDEEngine(NCDEEngine *this)

{
  ~NCDEEngine(this);
  operator_delete(this,0x4f8);
  return;
}



// ==== 001f879a  NCDEEngine::setLelan

/* NCDEEngine::setLelan(Lelan*) */

void __thiscall NCDEEngine::setLelan(NCDEEngine *this,Lelan *param_1)

{
  long in_FS_OFFSET;
  Connection local_60 [8];
  code *local_58;
  undefined8 uStack_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  *(Lelan **)(this + 0x4c8) = param_1;
  if (param_1 != (Lelan *)0x0) {
    local_58 = wifiChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::wifiChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = wifiChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::vpnStateChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = wifiChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::bluetoothChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = dateTimeChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::timezoneChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = dateTimeChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::clockChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = usersChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::usersChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = printersChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::printersChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
    local_58 = soundChanged;
    uStack_50 = 0;
    QObject::connect<void(Lelan::*)(),void(NCDEEngine::*)()>
              (local_60,param_1,Lelan::appStreamsChanged,0,this,&local_58,0);
    QMetaObject::Connection::~Connection(local_60);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


