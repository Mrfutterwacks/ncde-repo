// Ghidra decompile of LaPivot.oracle — class/namespace Settings (144 functions). Raw; not source.

// ==== 00148c10  Settings::qt_static_metacall

/* Settings::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void Settings::qt_static_metacall(Settings *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QList<QVariant> *this;
  QString *pQVar1;
  bool bVar2;
  QList<QVariant> QVar3;
  undefined4 uVar4;
  long in_FS_OFFSET;
  QString local_78 [32];
  Settings local_58 [24];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0x54) {
      initWatcher(param_1);
    }
    else if (param_3 < 0x55) {
      if (param_3 == 0x53) {
        loadKickass(param_1);
      }
      else if (param_3 < 0x54) {
        if (param_3 == 0x52) {
          setKickassArmed(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
        }
        else if (param_3 < 0x53) {
          if (param_3 == 0x51) {
            saveConfig(param_1);
          }
          else if (param_3 < 0x52) {
            if (param_3 == 0x50) {
              saveSecurity(param_1);
            }
            else if (param_3 < 0x51) {
              if (param_3 == 0x4f) {
                savePrivacy(param_1);
              }
              else if (param_3 < 0x50) {
                if (param_3 == 0x4e) {
                  local_58[0] = (Settings)screensaverRunning(param_1);
                  if (*(long *)param_4 != 0) {
                    **(Settings **)param_4 = local_58[0];
                  }
                }
                else if (param_3 < 0x4f) {
                  if (param_3 == 0x4d) {
                    QArrayDataPointer<char16_t>::QArrayDataPointer
                              ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,
                               L"auto",4);
                    QString::QString(local_78,(QArrayDataPointer *)local_58);
                    previewScreensaver(param_1,local_78);
                    QString::~QString(local_78);
                    QArrayDataPointer<char16_t>::~QArrayDataPointer
                              ((QArrayDataPointer<char16_t> *)local_58);
                  }
                  else if (param_3 < 0x4e) {
                    if (param_3 == 0x4c) {
                      previewScreensaver(param_1,*(QString **)(param_4 + 8));
                    }
                    else if (param_3 < 0x4d) {
                      if (param_3 == 0x4b) {
                        loadScreensaver(param_1);
                      }
                      else if (param_3 < 0x4c) {
                        if (param_3 == 0x4a) {
                          saveScreensaver(param_1);
                        }
                        else if (param_3 < 0x4b) {
                          if (param_3 == 0x49) {
                            saveNetwork(param_1);
                          }
                          else if (param_3 < 0x4a) {
                            if (param_3 == 0x48) {
                              saveDateTime(param_1);
                            }
                            else if (param_3 < 0x49) {
                              if (param_3 == 0x47) {
                                setSlideshowPaused(param_1,*(bool *)*(undefined8 *)(param_4 + 8));
                              }
                              else if (param_3 < 0x48) {
                                if (param_3 == 0x46) {
                                  saveFiligreepalette(param_1,*(QString **)(param_4 + 8),
                                                      **(double **)(param_4 + 0x10),
                                                      **(double **)(param_4 + 0x18),
                                                      *(QList **)(param_4 + 0x20));
                                }
                                else if (param_3 < 0x47) {
                                  if (param_3 == 0x45) {
                                    saveSectionColors(param_1);
                                  }
                                  else if (param_3 < 0x46) {
                                    if (param_3 == 0x44) {
                                      saveColorOverrides(param_1);
                                    }
                                    else if (param_3 < 0x45) {
                                      if (param_3 == 0x43) {
                                        resetWidgetStyle(param_1,*(QString **)(param_4 + 8));
                                      }
                                      else if (param_3 < 0x44) {
                                        if (param_3 == 0x42) {
                                          saveWidgetStyleMap(param_1,*(QString **)(param_4 + 8),
                                                             *(QMap **)(param_4 + 0x10));
                                        }
                                        else if (param_3 < 0x43) {
                                          if (param_3 == 0x41) {
                                            saveSurfaceGlass(param_1,*(QString **)(param_4 + 8),
                                                             *(QColor **)(param_4 + 0x10),
                                                             **(double **)(param_4 + 0x18),
                                                             **(double **)(param_4 + 0x20),
                                                             *(QColor **)(param_4 + 0x28),
                                                             *(QColor **)(param_4 + 0x30));
                                          }
                                          else if (param_3 < 0x42) {
                                            if (param_3 == 0x40) {
                                              saveSound(param_1);
                                            }
                                            else if (param_3 < 0x41) {
                                              if (param_3 == 0x3f) {
                                                loadSound(param_1);
                                              }
                                              else if (param_3 < 0x40) {
                                                if (param_3 == 0x3e) {
                                                  setFitMode(param_1,*(QString **)(param_4 + 8));
                                                }
                                                else if (param_3 < 0x3f) {
                                                  if (param_3 == 0x3d) {
                                                    setSlideshowInterval
                                                              (param_1,**(int **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x3e) {
                                                    if (param_3 == 0x3c) {
                                                      setSlideshowEnabled(param_1,*(bool *)*(
                                                  undefined8 *)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x3d) {
                                                    if (param_3 == 0x3b) {
                                                      saveWallpaperPrefs(param_1);
                                                    }
                                                    else if (param_3 < 0x3c) {
                                                      if (param_3 == 0x3a) {
                                                        loadWallpaperPrefs(param_1);
                                                      }
                                                      else if (param_3 < 0x3b) {
                                                        if (param_3 == 0x39) {
                                                          setWallpaper(param_1,*(QString **)
                                                                                (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x3a) {
                                                          if (param_3 == 0x38) {
                                                            getWallpaper(local_58);
                                                            if (*(long *)param_4 != 0) {
                                                              QString::operator=(*(QString **)
                                                                                  param_4,(QString *
                                                                                          )local_58)
                                                              ;
                                                            }
                                                            QString::~QString((QString *)local_58);
                                                          }
                                                          else if (param_3 < 0x39) {
                                                            if (param_3 == 0x37) {
                                                              saveNotifications(param_1);
                                                            }
                                                            else if (param_3 < 0x38) {
                                                              if (param_3 == 0x36) {
                                                                loadNotifications(param_1);
                                                              }
                                                              else if (param_3 < 0x37) {
                                                                if (param_3 == 0x35) {
                                                                  saveAutostart((QString *)param_1);
                                                                }
                                                                else if (param_3 < 0x36) {
                                                                  if (param_3 == 0x34) {
                                                                    loadAutostart(local_58);
                                                                    if (*(long *)param_4 != 0) {
                                                                      QString::operator=(*(QString *
                                                  *)param_4,(QString *)local_58);
                                                  }
                                                  QString::~QString((QString *)local_58);
                                                  }
                                                  else if (param_3 < 0x35) {
                                                    if (param_3 == 0x33) {
                                                      saveDefaults(param_1);
                                                    }
                                                    else if (param_3 < 0x34) {
                                                      if (param_3 == 0x32) {
                                                        loadDefaults(param_1);
                                                      }
                                                      else if (param_3 < 0x33) {
                                                        if (param_3 == 0x31) {
                                                          removeKbLayout(param_1,*(QString **)
                                                                                  (param_4 + 8));
                                                        }
                                                        else if (param_3 < 0x32) {
                                                          if (param_3 == 0x30) {
                                                            addKbLayout(param_1,*(QString **)
                                                                                 (param_4 + 8));
                                                          }
                                                          else if (param_3 < 0x31) {
                                                            if (param_3 == 0x2f) {
                                                              setActiveKbLayout(param_1,*(QString **
                                                                                         )(param_4 +
                                                                                          8));
                                                            }
                                                            else if (param_3 < 0x30) {
                                                              if (param_3 == 0x2e) {
                                                                saveLocale(param_1);
                                                              }
                                                              else if (param_3 < 0x2f) {
                                                                if (param_3 == 0x2d) {
                                                                  loadLocale(param_1);
                                                                }
                                                                else if (param_3 < 0x2e) {
                                                                  if (param_3 == 0x2c) {
                                                                    installedApps(local_58);
                                                                    if (*(long *)param_4 != 0) {
                                                                      QList<QVariant>::operator=
                                                                                (*(QList<QVariant>
                                                                                   **)param_4,
                                                                                 (QList *)local_58);
                                                                    }
                                                                    QList<QVariant>::~QList
                                                                              ((QList<QVariant> *)
                                                                               local_58);
                                                                  }
                                                                  else if (param_3 < 0x2d) {
                                                                    if (param_3 == 0x2b) {
                                                                      saveDockPrefs(param_1);
                                                                    }
                                                                    else if (param_3 < 0x2c) {
                                                                      if (param_3 == 0x2a) {
                                                                        setDockApps(param_1,*(QList 
                                                  **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 0x2b) {
                                                    if (param_3 == 0x29) {
                                                      loadDock(param_1);
                                                    }
                                                    else if (param_3 < 0x2a) {
                                                      if (param_3 == 0x28) {
                                                        saveConfPrivacy(param_1);
                                                      }
                                                      else if (param_3 < 0x29) {
                                                        if (param_3 == 0x27) {
                                                          loadPrivacy(param_1);
                                                        }
                                                        else if (param_3 < 0x28) {
                                                          if (param_3 == 0x26) {
                                                            saveAccessibility(param_1);
                                                          }
                                                          else if (param_3 < 0x27) {
                                                            if (param_3 == 0x25) {
                                                              loadAccessibility(param_1);
                                                            }
                                                            else if (param_3 < 0x26) {
                                                              if (param_3 == 0x24) {
                                                                saveInput(param_1);
                                                              }
                                                              else if (param_3 < 0x25) {
                                                                if (param_3 == 0x23) {
                                                                  loadInput(param_1);
                                                                }
                                                                else if (param_3 < 0x24) {
                                                                  if (param_3 == 0x22) {
                                                                    loadFonts(param_1);
                                                                  }
                                                                  else if (param_3 < 0x23) {
                                                                    if (param_3 == 0x21) {
                                                                      saveStorage(param_1);
                                                                    }
                                                                    else if (param_3 < 0x22) {
                                                                      if (param_3 == 0x20) {
                                                                        loadStorage(param_1);
                                                                      }
                                                                      else if (param_3 < 0x21) {
                                                                        if (param_3 == 0x1f) {
                                                                          saveTextColor(param_1);
                                                                        }
                                                                        else if (param_3 < 0x20) {
                                                                          if (param_3 == 0x1e) {
                                                                            saveFontSettings(param_1
                                                  );
                                                  }
                                                  else if (param_3 < 0x1f) {
                                                    if (param_3 == 0x1d) {
                                                      applyFontSettings(param_1);
                                                    }
                                                    else if (param_3 < 0x1e) {
                                                      if (param_3 == 0x1c) {
                                                        savePower(param_1);
                                                      }
                                                      else if (param_3 < 0x1d) {
                                                        if (param_3 == 0x1b) {
                                                          applyPowerSettings(param_1);
                                                        }
                                                        else if (param_3 < 0x1c) {
                                                          if (param_3 == 0x1a) {
                                                            loadPower(param_1);
                                                          }
                                                          else if (param_3 < 0x1b) {
                                                            if (param_3 == 0x19) {
                                                              loadDisplay(param_1);
                                                            }
                                                            else if (param_3 < 0x1a) {
                                                              if (param_3 == 0x18) {
                                                                saveDisplay(param_1);
                                                              }
                                                              else if (param_3 < 0x19) {
                                                                if (param_3 == 0x17) {
                                                                  applyDisplayScale(param_1,*(
                                                  QString **)(param_4 + 8),
                                                  **(int **)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0x18) {
                                                    if (param_3 == 0x16) {
                                                      applyDisplayOrientation
                                                                (param_1,*(QString **)(param_4 + 8),
                                                                 *(QString **)(param_4 + 0x10));
                                                    }
                                                    else if (param_3 < 0x17) {
                                                      if (param_3 == 0x15) {
                                                        applyDisplayMode(param_1,*(QString **)
                                                                                  (param_4 + 8),
                                                                         *(QString **)
                                                                          (param_4 + 0x10),
                                                                         **(double **)
                                                                           (param_4 + 0x18));
                                                      }
                                                      else if (param_3 < 0x16) {
                                                        if (param_3 == 0x14) {
                                                          refreshDisplays(param_1);
                                                        }
                                                        else if (param_3 < 0x15) {
                                                          if (param_3 == 0x13) {
                                                            onScreenIdleChanged(param_1);
                                                          }
                                                          else if (param_3 < 0x14) {
                                                            if (param_3 == 0x12) {
                                                              screensaverFinished(param_1,**(int **)
                                                  (param_4 + 8),
                                                  *(bool *)*(undefined8 *)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0x13) {
                                                    if (param_3 == 0x11) {
                                                      soundChanged(param_1);
                                                    }
                                                    else if (param_3 < 0x12) {
                                                      if (param_3 == 0x10) {
                                                        wallpaperPrefsChanged(param_1);
                                                      }
                                                      else if (param_3 < 0x11) {
                                                        if (param_3 == 0xf) {
                                                          notifsChanged(param_1);
                                                        }
                                                        else if (param_3 < 0x10) {
                                                          if (param_3 == 0xe) {
                                                            sessionChanged(param_1);
                                                          }
                                                          else if (param_3 < 0xf) {
                                                            if (param_3 == 0xd) {
                                                              localeChanged(param_1);
                                                            }
                                                            else if (param_3 < 0xe) {
                                                              if (param_3 == 0xc) {
                                                                dockChanged(param_1);
                                                              }
                                                              else if (param_3 < 0xd) {
                                                                if (param_3 == 0xb) {
                                                                  securityChanged(param_1);
                                                                }
                                                                else if (param_3 < 0xc) {
                                                                  if (param_3 == 10) {
                                                                    privacyChanged(param_1);
                                                                  }
                                                                  else if (param_3 < 0xb) {
                                                                    if (param_3 == 9) {
                                                                      accessibilityChanged(param_1);
                                                                    }
                                                                    else if (param_3 < 10) {
                                                                      if (param_3 == 8) {
                                                                        inputChanged(param_1);
                                                                      }
                                                                      else if (param_3 < 9) {
                                                                        if (param_3 == 7) {
                                                                          storageChanged(param_1);
                                                                        }
                                                                        else if (param_3 < 8) {
                                                                          if (param_3 == 6) {
                                                                            fontChanged(param_1);
                                                                          }
                                                                          else if (param_3 < 7) {
                                                                            if (param_3 == 5) {
                                                                              powerChanged(param_1);
                                                                            }
                                                                            else if (param_3 < 6) {
                                                                              if (param_3 == 4) {
                                                                                slideshowAdvanced(
                                                  param_1,*(QString **)(param_4 + 8));
                                                  }
                                                  else if (param_3 < 5) {
                                                    if (param_3 == 3) {
                                                      wallpaperChanged(param_1,*(QString **)
                                                                                (param_4 + 8));
                                                    }
                                                    else if (param_3 < 4) {
                                                      if (param_3 == 2) {
                                                        dockPrefsChanged(param_1);
                                                      }
                                                      else if (param_3 < 3) {
                                                        if (param_3 == 0) {
                                                          displaysChanged(param_1);
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
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
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
     (((((((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                              (param_4,(void **)displaysChanged,(_func_void *)0x0,0), !bVar2 &&
           (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                              (param_4,(void **)settingsChanged,(_func_void *)0x0,1), !bVar2)) &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)dockPrefsChanged,(_func_void *)0x0,2), !bVar2)) &&
         ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)(QString_const&)>
                             (param_4,(void **)wallpaperChanged,(_func_void_QString_ptr *)0x0,3),
          !bVar2 && (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)(QString_const&)>
                                       (param_4,(void **)slideshowAdvanced,
                                        (_func_void_QString_ptr *)0x0,4), !bVar2)))) &&
        ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                            (param_4,(void **)powerChanged,(_func_void *)0x0,5), !bVar2 &&
         ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)fontChanged,(_func_void *)0x0,6), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)storageChanged,(_func_void *)0x0,7), !bVar2)))))) &&
       (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                          (param_4,(void **)inputChanged,(_func_void *)0x0,8), !bVar2)) &&
      (((((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)accessibilityChanged,(_func_void *)0x0,9), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)privacyChanged,(_func_void *)0x0,10), !bVar2)) &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                            (param_4,(void **)securityChanged,(_func_void *)0x0,0xb), !bVar2)) &&
        (((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)dockChanged,(_func_void *)0x0,0xc), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)localeChanged,(_func_void *)0x0,0xd), !bVar2)) &&
         ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                             (param_4,(void **)sessionChanged,(_func_void *)0x0,0xe), !bVar2 &&
          ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                              (param_4,(void **)notifsChanged,(_func_void *)0x0,0xf), !bVar2 &&
           (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                              (param_4,(void **)wallpaperPrefsChanged,(_func_void *)0x0,0x10),
           !bVar2)))))))) &&
       ((bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)()>
                           (param_4,(void **)soundChanged,(_func_void *)0x0,0x11), !bVar2 &&
        (bVar2 = QtMocHelpers::indexOfMethod<void(Settings::*)(int,bool)>
                           (param_4,(void **)screensaverFinished,(_func_void_int_bool *)0x0,0x12),
        !bVar2)))))))) {
    if (param_2 == 1) {
      this = *(QList<QVariant> **)param_4;
      if (param_3 == 0x62) {
        *(undefined8 *)this = *(undefined8 *)(param_1 + 0x2a8);
      }
      else if (param_3 < 99) {
        if (param_3 == 0x61) {
          QString::operator=((QString *)this,(QString *)(param_1 + 0x290));
        }
        else if (param_3 < 0x62) {
          if (param_3 == 0x60) {
            QString::operator=((QString *)this,(QString *)(param_1 + 0x278));
          }
          else if (param_3 < 0x61) {
            if (param_3 == 0x5f) {
              *(undefined4 *)this = *(undefined4 *)(param_1 + 0x274);
            }
            else if (param_3 < 0x60) {
              if (param_3 == 0x5e) {
                *(undefined4 *)this = *(undefined4 *)(param_1 + 0x270);
              }
              else if (param_3 < 0x5f) {
                if (param_3 == 0x5d) {
                  fitMode();
                  QString::operator=((QString *)this,(QString *)local_58);
                  QString::~QString((QString *)local_58);
                }
                else if (param_3 < 0x5e) {
                  if (param_3 == 0x5c) {
                    uVar4 = slideshowInterval(param_1);
                    *(undefined4 *)this = uVar4;
                  }
                  else if (param_3 < 0x5d) {
                    if (param_3 == 0x5b) {
                      QVar3 = (QList<QVariant>)slideshowEnabled(param_1);
                      *this = QVar3;
                    }
                    else if (param_3 < 0x5c) {
                      if (param_3 == 0x5a) {
                        customWallpapers();
                        QList<QString>::operator=((QList<QString> *)this,(QList *)local_58);
                        QList<QString>::~QList((QList<QString> *)local_58);
                      }
                      else if (param_3 < 0x5b) {
                        if (param_3 == 0x59) {
                          userName(local_58);
                          QString::operator=((QString *)this,(QString *)local_58);
                          QString::~QString((QString *)local_58);
                        }
                        else if (param_3 < 0x5a) {
                          if (param_3 == 0x58) {
                            QString::operator=((QString *)this,(QString *)(param_1 + 0x220));
                          }
                          else if (param_3 < 0x59) {
                            if (param_3 == 0x57) {
                              QString::operator=((QString *)this,(QString *)(param_1 + 0x208));
                            }
                            else if (param_3 < 0x58) {
                              if (param_3 == 0x56) {
                                *this = *(QList<QVariant> *)(param_1 + 0x200);
                              }
                              else if (param_3 < 0x57) {
                                if (param_3 == 0x55) {
                                  *(undefined4 *)this = *(undefined4 *)(param_1 + 0x1fc);
                                }
                                else if (param_3 < 0x56) {
                                  if (param_3 == 0x54) {
                                    *this = *(QList<QVariant> *)(param_1 + 0x1f8);
                                  }
                                  else if (param_3 < 0x55) {
                                    if (param_3 == 0x53) {
                                      QString::operator=((QString *)this,
                                                         (QString *)(param_1 + 0x1e0));
                                    }
                                    else if (param_3 < 0x54) {
                                      if (param_3 == 0x52) {
                                        QString::operator=((QString *)this,
                                                           (QString *)(param_1 + 0x1c8));
                                      }
                                      else if (param_3 < 0x53) {
                                        if (param_3 == 0x51) {
                                          QString::operator=((QString *)this,
                                                             (QString *)(param_1 + 0x1b0));
                                        }
                                        else if (param_3 < 0x52) {
                                          if (param_3 == 0x50) {
                                            QString::operator=((QString *)this,
                                                               (QString *)(param_1 + 0x198));
                                          }
                                          else if (param_3 < 0x51) {
                                            if (param_3 == 0x4f) {
                                              activeKbLayout();
                                              QString::operator=((QString *)this,(QString *)local_58
                                                                );
                                              QString::~QString((QString *)local_58);
                                            }
                                            else if (param_3 < 0x50) {
                                              if (param_3 == 0x4e) {
                                                kbLayouts();
                                                QList<QString>::operator=
                                                          ((QList<QString> *)this,(QList *)local_58)
                                                ;
                                                QList<QString>::~QList((QList<QString> *)local_58);
                                              }
                                              else if (param_3 < 0x4f) {
                                                if (param_3 == 0x4d) {
                                                  QString::operator=((QString *)this,
                                                                     (QString *)(param_1 + 0x150));
                                                }
                                                else if (param_3 < 0x4e) {
                                                  if (param_3 == 0x4c) {
                                                    QString::operator=((QString *)this,
                                                                       (QString *)(param_1 + 0x138))
                                                    ;
                                                  }
                                                  else if (param_3 < 0x4d) {
                                                    if (param_3 == 0x4b) {
                                                      QString::operator=((QString *)this,
                                                                         (QString *)
                                                                         (param_1 + 0x120));
                                                    }
                                                    else if (param_3 < 0x4c) {
                                                      if (param_3 == 0x4a) {
                                                        QString::operator=((QString *)this,
                                                                           (QString *)
                                                                           (param_1 + 0x108));
                                                      }
                                                      else if (param_3 < 0x4b) {
                                                        if (param_3 == 0x49) {
                                                          dockApps();
                                                          QList<QVariant>::operator=
                                                                    (this,(QList *)local_58);
                                                          QList<QVariant>::~QList
                                                                    ((QList<QVariant> *)local_58);
                                                        }
                                                        else if (param_3 < 0x4a) {
                                                          if (param_3 == 0x48) {
                                                            *(undefined8 *)this =
                                                                 *(undefined8 *)(param_1 + 0xe8);
                                                          }
                                                          else if (param_3 < 0x49) {
                                                            if (param_3 == 0x47) {
                                                              *(undefined8 *)this =
                                                                   *(undefined8 *)(param_1 + 0xe0);
                                                            }
                                                            else if (param_3 < 0x48) {
                                                              if (param_3 == 0x46) {
                                                                *(undefined8 *)this =
                                                                     *(undefined8 *)(param_1 + 0xd8)
                                                                ;
                                                              }
                                                              else if (param_3 < 0x47) {
                                                                if (param_3 == 0x45) {
                                                                  *(undefined4 *)this =
                                                                       *(undefined4 *)
                                                                        (param_1 + 0xcc);
                                                                }
                                                                else if (param_3 < 0x46) {
                                                                  if (param_3 == 0x44) {
                                                                    *(undefined4 *)this =
                                                                         *(undefined4 *)
                                                                          (param_1 + 200);
                                                                  }
                                                                  else if (param_3 < 0x45) {
                                                                    if (param_3 == 0x43) {
                                                                      *(undefined8 *)this =
                                                                           *(undefined8 *)
                                                                            (param_1 + 0xd0);
                                                                    }
                                                                    else if (param_3 < 0x44) {
                                                                      if (param_3 == 0x42) {
                                                                        *(undefined4 *)this =
                                                                             *(undefined4 *)
                                                                              (param_1 + 0xc4);
                                                                      }
                                                                      else if (param_3 < 0x43) {
                                                                        if (param_3 == 0x41) {
                                                                          *(undefined4 *)this =
                                                                               *(undefined4 *)
                                                                                (param_1 + 0xc0);
                                                                        }
                                                                        else if (param_3 < 0x42) {
                                                                          if (param_3 == 0x40) {
                                                                            *(undefined4 *)this =
                                                                                 *(undefined4 *)
                                                                                  (param_1 + 0x3f8);
                                                                          }
                                                                          else if (param_3 < 0x41) {
                                                                            if (param_3 == 0x3f) {
                                                                              QString::operator=((
                                                  QString *)this,(QString *)(param_1 + 0x3e0));
                                                  }
                                                  else if (param_3 < 0x40) {
                                                    if (param_3 == 0x3e) {
                                                      *this = *(QList<QVariant> *)(param_1 + 0x3d9);
                                                    }
                                                    else if (param_3 < 0x3f) {
                                                      if (param_3 == 0x3d) {
                                                        QString::operator=((QString *)this,
                                                                           (QString *)
                                                                           (param_1 + 0x3c0));
                                                      }
                                                      else if (param_3 < 0x3e) {
                                                        if (param_3 == 0x3c) {
                                                          *this = *(QList<QVariant> *)
                                                                   (param_1 + 0x3d8);
                                                        }
                                                        else if (param_3 < 0x3d) {
                                                          if (param_3 == 0x3b) {
                                                            *this = *(QList<QVariant> *)
                                                                     (param_1 + 0x40c);
                                                          }
                                                          else if (param_3 < 0x3c) {
                                                            if (param_3 == 0x3a) {
                                                              QString::operator=((QString *)this,
                                                                                 (QString *)
                                                                                 (param_1 + 0x390));
                                                            }
                                                            else if (param_3 < 0x3b) {
                                                              if (param_3 == 0x39) {
                                                                *this = *(QList<QVariant> *)
                                                                         (param_1 + 0x405);
                                                              }
                                                              else if (param_3 < 0x3a) {
                                                                if (param_3 == 0x38) {
                                                                  *(undefined4 *)this =
                                                                       *(undefined4 *)
                                                                        (param_1 + 0x408);
                                                                }
                                                                else if (param_3 < 0x39) {
                                                                  if (param_3 == 0x37) {
                                                                    *this = *(QList<QVariant> *)
                                                                             (param_1 + 0x404);
                                                                  }
                                                                  else if (param_3 < 0x38) {
                                                                    if (param_3 == 0x36) {
                                                                      *(undefined4 *)this =
                                                                           *(undefined4 *)
                                                                            (param_1 + 0x400);
                                                                    }
                                                                    else if (param_3 < 0x37) {
                                                                      if (param_3 == 0x35) {
                                                                        *this = *(QList<QVariant> *)
                                                                                 (param_1 + 0x3fc);
                                                                      }
                                                                      else if (param_3 < 0x36) {
                                                                        if (param_3 == 0x34) {
                                                                          QString::operator=((
                                                  QString *)this,(QString *)(param_1 + 0x3a8));
                                                  }
                                                  else if (param_3 < 0x35) {
                                                    if (param_3 == 0x33) {
                                                      *(undefined4 *)this =
                                                           *(undefined4 *)(param_1 + 0x410);
                                                    }
                                                    else if (param_3 < 0x34) {
                                                      if (param_3 == 0x32) {
                                                        *this = *(QList<QVariant> *)
                                                                 (param_1 + 0x389);
                                                      }
                                                      else if (param_3 < 0x33) {
                                                        if (param_3 == 0x31) {
                                                          *this = *(QList<QVariant> *)
                                                                   (param_1 + 0x388);
                                                        }
                                                        else if (param_3 < 0x32) {
                                                          if (param_3 == 0x30) {
                                                            *this = *(QList<QVariant> *)
                                                                     (param_1 + 0xaa);
                                                          }
                                                          else if (param_3 < 0x31) {
                                                            if (param_3 == 0x2f) {
                                                              *this = *(QList<QVariant> *)
                                                                       (param_1 + 0xa9);
                                                            }
                                                            else if (param_3 < 0x30) {
                                                              if (param_3 == 0x2e) {
                                                                *this = *(QList<QVariant> *)
                                                                         (param_1 + 0xa8);
                                                              }
                                                              else if (param_3 < 0x2f) {
                                                                if (param_3 == 0x2d) {
                                                                  *(undefined8 *)this =
                                                                       *(undefined8 *)
                                                                        (param_1 + 0xa0);
                                                                }
                                                                else if (param_3 < 0x2e) {
                                                                  if (param_3 == 0x2c) {
                                                                    *(undefined4 *)this =
                                                                         *(undefined4 *)
                                                                          (param_1 + 0x94);
                                                                  }
                                                                  else if (param_3 < 0x2d) {
                                                                    if (param_3 == 0x2b) {
                                                                      *this = *(QList<QVariant> *)
                                                                               (param_1 + 0x9a);
                                                                    }
                                                                    else if (param_3 < 0x2c) {
                                                                      if (param_3 == 0x2a) {
                                                                        *this = *(QList<QVariant> *)
                                                                                 (param_1 + 0x99);
                                                                      }
                                                                      else if (param_3 < 0x2b) {
                                                                        if (param_3 == 0x29) {
                                                                          *this = *(QList<QVariant>
                                                                                    *)(param_1 +
                                                                                      0x98);
                                                                        }
                                                                        else if (param_3 < 0x2a) {
                                                                          if (param_3 == 0x28) {
                                                                            *(undefined4 *)this =
                                                                                 *(undefined4 *)
                                                                                  (param_1 + 0x90);
                                                                          }
                                                                          else if (param_3 < 0x29) {
                                                                            if (param_3 == 0x27) {
                                                                              *(undefined4 *)this =
                                                                                   *(undefined4 *)
                                                                                    (param_1 + 0x8c)
                                                                              ;
                                                                            }
                                                                            else if (param_3 < 0x28)
                                                                            {
                                                                              if (param_3 == 0x26) {
                                                                                *(undefined4 *)this
                                                                                     = *(undefined4
                                                                                         *)(param_1 
                                                  + 0x88);
                                                  }
                                                  else if (param_3 < 0x27) {
                                                    if (param_3 == 0x25) {
                                                      *(undefined4 *)this =
                                                           *(undefined4 *)(param_1 + 0x84);
                                                    }
                                                    else if (param_3 < 0x26) {
                                                      if (param_3 == 0x24) {
                                                        *this = *(QList<QVariant> *)(param_1 + 0x81)
                                                        ;
                                                      }
                                                      else if (param_3 < 0x25) {
                                                        if (param_3 == 0x23) {
                                                          *(undefined8 *)this =
                                                               *(undefined8 *)(param_1 + 0x4c8);
                                                        }
                                                        else if (param_3 < 0x24) {
                                                          if (param_3 == 0x22) {
                                                            *(undefined8 *)this =
                                                                 *(undefined8 *)(param_1 + 0x4c0);
                                                          }
                                                          else if (param_3 < 0x23) {
                                                            if (param_3 == 0x21) {
                                                              *(undefined8 *)this =
                                                                   *(undefined8 *)(param_1 + 0x4b8);
                                                            }
                                                            else if (param_3 < 0x22) {
                                                              if (param_3 == 0x20) {
                                                                QString::operator=((QString *)this,
                                                                                   (QString *)
                                                                                   (param_1 + 0x4a0)
                                                                                  );
                                                              }
                                                              else if (param_3 < 0x21) {
                                                                if (param_3 == 0x1f) {
                                                                  *this = *(QList<QVariant> *)
                                                                           (param_1 + 0x498);
                                                                }
                                                                else if (param_3 < 0x20) {
                                                                  if (param_3 == 0x1e) {
                                                                    *(undefined8 *)this =
                                                                         *(undefined8 *)
                                                                          (param_1 + 0x490);
                                                                  }
                                                                  else if (param_3 < 0x1f) {
                                                                    if (param_3 == 0x1d) {
                                                                      QString::operator=((QString *)
                                                                                         this,(
                                                  QString *)(param_1 + 0x478));
                                                  }
                                                  else if (param_3 < 0x1e) {
                                                    if (param_3 == 0x1c) {
                                                      *this = *(QList<QVariant> *)(param_1 + 0x470);
                                                    }
                                                    else if (param_3 < 0x1d) {
                                                      if (param_3 == 0x1b) {
                                                        QString::operator=((QString *)this,
                                                                           (QString *)
                                                                           (param_1 + 0x458));
                                                      }
                                                      else if (param_3 < 0x1c) {
                                                        if (param_3 == 0x1a) {
                                                          *(undefined8 *)this =
                                                               *(undefined8 *)(param_1 + 0x450);
                                                        }
                                                        else if (param_3 < 0x1b) {
                                                          if (param_3 == 0x19) {
                                                            *(undefined8 *)this =
                                                                 *(undefined8 *)(param_1 + 0x448);
                                                          }
                                                          else if (param_3 < 0x1a) {
                                                            if (param_3 == 0x18) {
                                                              *(undefined8 *)this =
                                                                   *(undefined8 *)(param_1 + 0x440);
                                                            }
                                                            else if (param_3 < 0x19) {
                                                              if (param_3 == 0x17) {
                                                                *(undefined8 *)this =
                                                                     *(undefined8 *)
                                                                      (param_1 + 0x438);
                                                              }
                                                              else if (param_3 < 0x18) {
                                                                if (param_3 == 0x16) {
                                                                  *this = *(QList<QVariant> *)
                                                                           (param_1 + 0x430);
                                                                }
                                                                else if (param_3 < 0x17) {
                                                                  if (param_3 == 0x15) {
                                                                    *(undefined4 *)this =
                                                                         *(undefined4 *)
                                                                          (param_1 + 0x42c);
                                                                  }
                                                                  else if (param_3 < 0x16) {
                                                                    if (param_3 == 0x14) {
                                                                      *this = *(QList<QVariant> *)
                                                                               (param_1 + 0x38a);
                                                                    }
                                                                    else if (param_3 < 0x15) {
                                                                      if (param_3 == 0x13) {
                                                                        QString::operator=((QString 
                                                  *)this,(QString *)(param_1 + 0x370));
                                                  }
                                                  else if (param_3 < 0x14) {
                                                    if (param_3 == 0x12) {
                                                      QString::operator=((QString *)this,
                                                                         (QString *)
                                                                         (param_1 + 0x358));
                                                    }
                                                    else if (param_3 < 0x13) {
                                                      if (param_3 == 0x11) {
                                                        QString::operator=((QString *)this,
                                                                           (QString *)
                                                                           (param_1 + 0x340));
                                                      }
                                                      else if (param_3 < 0x12) {
                                                        if (param_3 == 0x10) {
                                                          QString::operator=((QString *)this,
                                                                             (QString *)
                                                                             (param_1 + 0x328));
                                                        }
                                                        else if (param_3 < 0x11) {
                                                          if (param_3 == 0xf) {
                                                            QString::operator=((QString *)this,
                                                                               (QString *)
                                                                               (param_1 + 0x310));
                                                          }
                                                          else if (param_3 < 0x10) {
                                                            if (param_3 == 0xe) {
                                                              QString::operator=((QString *)this,
                                                                                 (QString *)
                                                                                 (param_1 + 0x2f8));
                                                            }
                                                            else if (param_3 < 0xf) {
                                                              if (param_3 == 0xd) {
                                                                QString::operator=((QString *)this,
                                                                                   (QString *)
                                                                                   (param_1 + 0x2e0)
                                                                                  );
                                                              }
                                                              else if (param_3 < 0xe) {
                                                                if (param_3 == 0xc) {
                                                                  QString::operator=((QString *)this
                                                                                     ,(QString *)
                                                                                      (param_1 +
                                                                                      0x2c8));
                                                                }
                                                                else if (param_3 < 0xd) {
                                                                  if (param_3 == 0xb) {
                                                                    QString::operator=((QString *)
                                                                                       this,(QString
                                                                                             *)(
                                                  param_1 + 0x2b0));
                                                  }
                                                  else if (param_3 < 0xc) {
                                                    if (param_3 == 10) {
                                                      QVar3 = (QList<QVariant>)
                                                              showBatteryPct(param_1);
                                                      *this = QVar3;
                                                    }
                                                    else if (param_3 < 0xb) {
                                                      if (param_3 == 9) {
                                                        powerButtonAction();
                                                        QString::operator=((QString *)this,
                                                                           (QString *)local_58);
                                                        QString::~QString((QString *)local_58);
                                                      }
                                                      else if (param_3 < 10) {
                                                        if (param_3 == 8) {
                                                          lidAction();
                                                          QString::operator=((QString *)this,
                                                                             (QString *)local_58);
                                                          QString::~QString((QString *)local_58);
                                                        }
                                                        else if (param_3 < 9) {
                                                          if (param_3 == 7) {
                                                            uVar4 = acSuspend(param_1);
                                                            *(undefined4 *)this = uVar4;
                                                          }
                                                          else if (param_3 < 8) {
                                                            if (param_3 == 6) {
                                                              uVar4 = acBlank(param_1);
                                                              *(undefined4 *)this = uVar4;
                                                            }
                                                            else if (param_3 < 7) {
                                                              if (param_3 == 5) {
                                                                uVar4 = batSuspend(param_1);
                                                                *(undefined4 *)this = uVar4;
                                                              }
                                                              else if (param_3 < 6) {
                                                                if (param_3 == 4) {
                                                                  uVar4 = batBlank(param_1);
                                                                  *(undefined4 *)this = uVar4;
                                                                }
                                                                else if (param_3 < 5) {
                                                                  if (param_3 == 3) {
                                                                    *this = *(QList<QVariant> *)
                                                                             (param_1 + 0x39);
                                                                  }
                                                                  else if (param_3 < 4) {
                                                                    if (param_3 == 2) {
                                                                      uVar4 = nightWarmth(param_1);
                                                                      *(undefined4 *)this = uVar4;
                                                                    }
                                                                    else if (param_3 < 3) {
                                                                      if (param_3 == 0) {
                                                                        displays();
                                                                        QList<QVariant>::operator=
                                                                                  (this,(QList *)
                                                  local_58);
                                                  QList<QVariant>::~QList
                                                            ((QList<QVariant> *)local_58);
                                                  }
                                                  else if (param_3 == 1) {
                                                    QVar3 = (QList<QVariant>)nightLightOn(param_1);
                                                    *this = QVar3;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
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
      if (param_3 == 0x62) {
        bVar2 = QtMocHelpers::setProperty<double,double&>
                          ((double *)(param_1 + 0x2a8),(double *)pQVar1);
        if (bVar2) {
          soundChanged(param_1);
        }
      }
      else if (param_3 < 99) {
        if (param_3 == 0x61) {
          bVar2 = QtMocHelpers::setProperty<QString,QString&>((QString *)(param_1 + 0x290),pQVar1);
          if (bVar2) {
            soundChanged(param_1);
          }
        }
        else if (param_3 < 0x62) {
          if (param_3 == 0x60) {
            bVar2 = QtMocHelpers::setProperty<QString,QString&>((QString *)(param_1 + 0x278),pQVar1)
            ;
            if (bVar2) {
              soundChanged(param_1);
            }
          }
          else if (param_3 < 0x61) {
            if (param_3 == 0x5f) {
              bVar2 = QtMocHelpers::setProperty<int,int&>((int *)(param_1 + 0x274),(int *)pQVar1);
              if (bVar2) {
                soundChanged(param_1);
              }
            }
            else if (param_3 < 0x60) {
              if (param_3 == 0x5e) {
                bVar2 = QtMocHelpers::setProperty<int,int&>((int *)(param_1 + 0x270),(int *)pQVar1);
                if (bVar2) {
                  soundChanged(param_1);
                }
              }
              else if (param_3 < 0x5f) {
                if (param_3 == 0x5d) {
                  setFitMode(param_1,pQVar1);
                }
                else if (param_3 < 0x5e) {
                  if (param_3 == 0x5c) {
                    setSlideshowInterval(param_1,*(int *)pQVar1);
                  }
                  else if (param_3 < 0x5d) {
                    if (param_3 == 0x5b) {
                      setSlideshowEnabled(param_1,(bool)*pQVar1);
                    }
                    else if (param_3 < 0x5c) {
                      if (param_3 == 0x58) {
                        bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                          ((QString *)(param_1 + 0x220),pQVar1);
                        if (bVar2) {
                          notifsChanged(param_1);
                        }
                      }
                      else if (param_3 < 0x59) {
                        if (param_3 == 0x57) {
                          bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                            ((QString *)(param_1 + 0x208),pQVar1);
                          if (bVar2) {
                            notifsChanged(param_1);
                          }
                        }
                        else if (param_3 < 0x58) {
                          if (param_3 == 0x56) {
                            bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                              ((bool *)(param_1 + 0x200),(bool *)pQVar1);
                            if (bVar2) {
                              notifsChanged(param_1);
                            }
                          }
                          else if (param_3 < 0x57) {
                            if (param_3 == 0x55) {
                              bVar2 = QtMocHelpers::setProperty<int,int&>
                                                ((int *)(param_1 + 0x1fc),(int *)pQVar1);
                              if (bVar2) {
                                notifsChanged(param_1);
                              }
                            }
                            else if (param_3 < 0x56) {
                              if (param_3 == 0x54) {
                                bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                                  ((bool *)(param_1 + 0x1f8),(bool *)pQVar1);
                                if (bVar2) {
                                  notifsChanged(param_1);
                                }
                              }
                              else if (param_3 < 0x55) {
                                if (param_3 == 0x53) {
                                  bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                    ((QString *)(param_1 + 0x1e0),pQVar1);
                                  if (bVar2) {
                                    sessionChanged(param_1);
                                  }
                                }
                                else if (param_3 < 0x54) {
                                  if (param_3 == 0x52) {
                                    bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                      ((QString *)(param_1 + 0x1c8),pQVar1);
                                    if (bVar2) {
                                      sessionChanged(param_1);
                                    }
                                  }
                                  else if (param_3 < 0x53) {
                                    if (param_3 == 0x51) {
                                      bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                        ((QString *)(param_1 + 0x1b0),pQVar1);
                                      if (bVar2) {
                                        sessionChanged(param_1);
                                      }
                                    }
                                    else if (param_3 < 0x52) {
                                      if (param_3 == 0x50) {
                                        bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                          ((QString *)(param_1 + 0x198),pQVar1);
                                        if (bVar2) {
                                          sessionChanged(param_1);
                                        }
                                      }
                                      else if (param_3 < 0x51) {
                                        if (param_3 == 0x4f) {
                                          setActiveKbLayout(param_1,pQVar1);
                                        }
                                        else if (param_3 < 0x50) {
                                          if (param_3 == 0x4d) {
                                            bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                              ((QString *)(param_1 + 0x150),pQVar1);
                                            if (bVar2) {
                                              localeChanged(param_1);
                                            }
                                          }
                                          else if (param_3 < 0x4e) {
                                            if (param_3 == 0x4c) {
                                              bVar2 = QtMocHelpers::setProperty<QString,QString&>
                                                                ((QString *)(param_1 + 0x138),pQVar1
                                                                );
                                              if (bVar2) {
                                                localeChanged(param_1);
                                              }
                                            }
                                            else if (param_3 < 0x4d) {
                                              if (param_3 == 0x48) {
                                                bVar2 = QtMocHelpers::setProperty<double,double&>
                                                                  ((double *)(param_1 + 0xe8),
                                                                   (double *)pQVar1);
                                                if (bVar2) {
                                                  dockChanged(param_1);
                                                }
                                              }
                                              else if (param_3 < 0x49) {
                                                if (param_3 == 0x47) {
                                                  bVar2 = QtMocHelpers::setProperty<double,double&>
                                                                    ((double *)(param_1 + 0xe0),
                                                                     (double *)pQVar1);
                                                  if (bVar2) {
                                                    dockChanged(param_1);
                                                  }
                                                }
                                                else if (param_3 < 0x48) {
                                                  if (param_3 == 0x46) {
                                                    bVar2 = QtMocHelpers::
                                                            setProperty<double,double&>
                                                                      ((double *)(param_1 + 0xd8),
                                                                       (double *)pQVar1);
                                                    if (bVar2) {
                                                      dockChanged(param_1);
                                                    }
                                                  }
                                                  else if (param_3 < 0x47) {
                                                    if (param_3 == 0x45) {
                                                      bVar2 = QtMocHelpers::setProperty<int,int&>
                                                                        ((int *)(param_1 + 0xcc),
                                                                         (int *)pQVar1);
                                                      if (bVar2) {
                                                        dockChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x46) {
                                                      if (param_3 == 0x44) {
                                                        bVar2 = QtMocHelpers::setProperty<int,int&>
                                                                          ((int *)(param_1 + 200),
                                                                           (int *)pQVar1);
                                                        if (bVar2) {
                                                          dockChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x45) {
                                                        if (param_3 == 0x43) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<double,double&>
                                                                            ((double *)
                                                                             (param_1 + 0xd0),
                                                                             (double *)pQVar1);
                                                          if (bVar2) {
                                                            dockChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x44) {
                                                          if (param_3 == 0x42) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<int,int&>
                                                                              ((int *)(param_1 +
                                                                                      0xc4),
                                                                               (int *)pQVar1);
                                                            if (bVar2) {
                                                              dockChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x43) {
                                                            if (param_3 == 0x41) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<int,int&>
                                                                                ((int *)(param_1 +
                                                                                        0xc0),
                                                                                 (int *)pQVar1);
                                                              if (bVar2) {
                                                                dockChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x42) {
                                                              if (param_3 == 0x40) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<int,int&>
                                                                                  ((int *)(param_1 +
                                                                                          0x3f8),
                                                                                   (int *)pQVar1);
                                                                if (bVar2) {
                                                                  settingsChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x41) {
                                                                if (param_3 == 0x3f) {
                                                                  bVar2 = QtMocHelpers::
                                                                                                                                                    
                                                  setProperty<QString,QString&>
                                                            ((QString *)(param_1 + 0x3e0),pQVar1);
                                                  if (bVar2) {
                                                    settingsChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x40) {
                                                    if (param_3 == 0x3e) {
                                                      bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                                                        ((bool *)(param_1 + 0x3d9),
                                                                         (bool *)pQVar1);
                                                      if (bVar2) {
                                                        settingsChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x3f) {
                                                      if (param_3 == 0x3d) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<QString,QString&>
                                                                          ((QString *)
                                                                           (param_1 + 0x3c0),pQVar1)
                                                        ;
                                                        if (bVar2) {
                                                          settingsChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x3e) {
                                                        if (param_3 == 0x3c) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<bool,bool&>
                                                                            ((bool *)(param_1 +
                                                                                     0x3d8),
                                                                             (bool *)pQVar1);
                                                          if (bVar2) {
                                                            settingsChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x3d) {
                                                          if (param_3 == 0x3b) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<bool,bool&>
                                                                              ((bool *)(param_1 +
                                                                                       0x40c),
                                                                               (bool *)pQVar1);
                                                            if (bVar2) {
                                                              settingsChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x3c) {
                                                            if (param_3 == 0x3a) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<QString,QString&>
                                                                                ((QString *)
                                                                                 (param_1 + 0x390),
                                                                                 pQVar1);
                                                              if (bVar2) {
                                                                settingsChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x3b) {
                                                              if (param_3 == 0x39) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<bool,bool&>
                                                                                  ((bool *)(param_1 
                                                  + 0x405),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    securityChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x3a) {
                                                    if (param_3 == 0x38) {
                                                      bVar2 = QtMocHelpers::setProperty<int,int&>
                                                                        ((int *)(param_1 + 0x408),
                                                                         (int *)pQVar1);
                                                      if (bVar2) {
                                                        securityChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x39) {
                                                      if (param_3 == 0x37) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<bool,bool&>
                                                                          ((bool *)(param_1 + 0x404)
                                                                           ,(bool *)pQVar1);
                                                        if (bVar2) {
                                                          securityChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x38) {
                                                        if (param_3 == 0x36) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<int,int&>
                                                                            ((int *)(param_1 + 0x400
                                                                                    ),(int *)pQVar1)
                                                          ;
                                                          if (bVar2) {
                                                            settingsChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x37) {
                                                          if (param_3 == 0x35) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<bool,bool&>
                                                                              ((bool *)(param_1 +
                                                                                       0x3fc),
                                                                               (bool *)pQVar1);
                                                            if (bVar2) {
                                                              settingsChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x36) {
                                                            if (param_3 == 0x34) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<QString,QString&>
                                                                                ((QString *)
                                                                                 (param_1 + 0x3a8),
                                                                                 pQVar1);
                                                              if (bVar2) {
                                                                settingsChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x35) {
                                                              if (param_3 == 0x33) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<int,int&>
                                                                                  ((int *)(param_1 +
                                                                                          0x410),
                                                                                   (int *)pQVar1);
                                                                if (bVar2) {
                                                                  settingsChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x34) {
                                                                if (param_3 == 0x32) {
                                                                  bVar2 = QtMocHelpers::
                                                                          setProperty<bool,bool&>
                                                                                    ((bool *)(
                                                  param_1 + 0x389),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    privacyChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x33) {
                                                    if (param_3 == 0x31) {
                                                      bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                                                        ((bool *)(param_1 + 0x388),
                                                                         (bool *)pQVar1);
                                                      if (bVar2) {
                                                        privacyChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x32) {
                                                      if (param_3 == 0x30) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<bool,bool&>
                                                                          ((bool *)(param_1 + 0xaa),
                                                                           (bool *)pQVar1);
                                                        if (bVar2) {
                                                          accessibilityChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x31) {
                                                        if (param_3 == 0x2f) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<bool,bool&>
                                                                            ((bool *)(param_1 + 0xa9
                                                                                     ),
                                                                             (bool *)pQVar1);
                                                          if (bVar2) {
                                                            accessibilityChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x30) {
                                                          if (param_3 == 0x2e) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<bool,bool&>
                                                                              ((bool *)(param_1 +
                                                                                       0xa8),
                                                                               (bool *)pQVar1);
                                                            if (bVar2) {
                                                              accessibilityChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x2f) {
                                                            if (param_3 == 0x2d) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<double,double&>
                                                                                ((double *)
                                                                                 (param_1 + 0xa0),
                                                                                 (double *)pQVar1);
                                                              if (bVar2) {
                                                                accessibilityChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x2e) {
                                                              if (param_3 == 0x2c) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<int,int&>
                                                                                  ((int *)(param_1 +
                                                                                          0x94),
                                                                                   (int *)pQVar1);
                                                                if (bVar2) {
                                                                  inputChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x2d) {
                                                                if (param_3 == 0x2b) {
                                                                  bVar2 = QtMocHelpers::
                                                                          setProperty<bool,bool&>
                                                                                    ((bool *)(
                                                  param_1 + 0x9a),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    inputChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x2c) {
                                                    if (param_3 == 0x2a) {
                                                      bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                                                        ((bool *)(param_1 + 0x99),
                                                                         (bool *)pQVar1);
                                                      if (bVar2) {
                                                        inputChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x2b) {
                                                      if (param_3 == 0x29) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<bool,bool&>
                                                                          ((bool *)(param_1 + 0x98),
                                                                           (bool *)pQVar1);
                                                        if (bVar2) {
                                                          inputChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x2a) {
                                                        if (param_3 == 0x28) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<int,int&>
                                                                            ((int *)(param_1 + 0x90)
                                                                             ,(int *)pQVar1);
                                                          if (bVar2) {
                                                            inputChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x29) {
                                                          if (param_3 == 0x27) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<int,int&>
                                                                              ((int *)(param_1 +
                                                                                      0x8c),
                                                                               (int *)pQVar1);
                                                            if (bVar2) {
                                                              inputChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x28) {
                                                            if (param_3 == 0x26) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<int,int&>
                                                                                ((int *)(param_1 +
                                                                                        0x88),
                                                                                 (int *)pQVar1);
                                                              if (bVar2) {
                                                                inputChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x27) {
                                                              if (param_3 == 0x25) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<int,int&>
                                                                                  ((int *)(param_1 +
                                                                                          0x84),
                                                                                   (int *)pQVar1);
                                                                if (bVar2) {
                                                                  inputChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x26) {
                                                                if (param_3 == 0x24) {
                                                                  bVar2 = QtMocHelpers::
                                                                          setProperty<bool,bool&>
                                                                                    ((bool *)(
                                                  param_1 + 0x81),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    storageChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x25) {
                                                    if (param_3 == 0x23) {
                                                      bVar2 = QtMocHelpers::
                                                              setProperty<double,double&>
                                                                        ((double *)(param_1 + 0x4c8)
                                                                         ,(double *)pQVar1);
                                                      if (bVar2) {
                                                        fontChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x24) {
                                                      if (param_3 == 0x22) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<double,double&>
                                                                          ((double *)
                                                                           (param_1 + 0x4c0),
                                                                           (double *)pQVar1);
                                                        if (bVar2) {
                                                          fontChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x23) {
                                                        if (param_3 == 0x21) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<double,double&>
                                                                            ((double *)
                                                                             (param_1 + 0x4b8),
                                                                             (double *)pQVar1);
                                                          if (bVar2) {
                                                            fontChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x22) {
                                                          if (param_3 == 0x20) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<QString,QString&>
                                                                              ((QString *)
                                                                               (param_1 + 0x4a0),
                                                                               pQVar1);
                                                            if (bVar2) {
                                                              fontChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x21) {
                                                            if (param_3 == 0x1f) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<bool,bool&>
                                                                                ((bool *)(param_1 +
                                                                                         0x498),
                                                                                 (bool *)pQVar1);
                                                              if (bVar2) {
                                                                fontChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x20) {
                                                              if (param_3 == 0x1e) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<double,double&>
                                                                                  ((double *)
                                                                                   (param_1 + 0x490)
                                                                                   ,(double *)pQVar1
                                                                                  );
                                                                if (bVar2) {
                                                                  fontChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x1f) {
                                                                if (param_3 == 0x1d) {
                                                                  bVar2 = QtMocHelpers::
                                                                                                                                                    
                                                  setProperty<QString,QString&>
                                                            ((QString *)(param_1 + 0x478),pQVar1);
                                                  if (bVar2) {
                                                    fontChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x1e) {
                                                    if (param_3 == 0x1c) {
                                                      bVar2 = QtMocHelpers::setProperty<bool,bool&>
                                                                        ((bool *)(param_1 + 0x470),
                                                                         (bool *)pQVar1);
                                                      if (bVar2) {
                                                        fontChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x1d) {
                                                      if (param_3 == 0x1b) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<QString,QString&>
                                                                          ((QString *)
                                                                           (param_1 + 0x458),pQVar1)
                                                        ;
                                                        if (bVar2) {
                                                          fontChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x1c) {
                                                        if (param_3 == 0x1a) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<double,double&>
                                                                            ((double *)
                                                                             (param_1 + 0x450),
                                                                             (double *)pQVar1);
                                                          if (bVar2) {
                                                            fontChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x1b) {
                                                          if (param_3 == 0x19) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<double,double&>
                                                                              ((double *)
                                                                               (param_1 + 0x448),
                                                                               (double *)pQVar1);
                                                            if (bVar2) {
                                                              fontChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x1a) {
                                                            if (param_3 == 0x18) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<double,double&>
                                                                                ((double *)
                                                                                 (param_1 + 0x440),
                                                                                 (double *)pQVar1);
                                                              if (bVar2) {
                                                                fontChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x19) {
                                                              if (param_3 == 0x17) {
                                                                bVar2 = QtMocHelpers::
                                                                        setProperty<double,double&>
                                                                                  ((double *)
                                                                                   (param_1 + 0x438)
                                                                                   ,(double *)pQVar1
                                                                                  );
                                                                if (bVar2) {
                                                                  fontChanged(param_1);
                                                                }
                                                              }
                                                              else if (param_3 < 0x18) {
                                                                if (param_3 == 0x16) {
                                                                  bVar2 = QtMocHelpers::
                                                                          setProperty<bool,bool&>
                                                                                    ((bool *)(
                                                  param_1 + 0x430),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    fontChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x17) {
                                                    if (param_3 == 0x15) {
                                                      bVar2 = QtMocHelpers::setProperty<int,int&>
                                                                        ((int *)(param_1 + 0x42c),
                                                                         (int *)pQVar1);
                                                      if (bVar2) {
                                                        fontChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x16) {
                                                      if (param_3 == 0x14) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<bool,bool&>
                                                                          ((bool *)(param_1 + 0x38a)
                                                                           ,(bool *)pQVar1);
                                                        if (bVar2) {
                                                          settingsChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0x15) {
                                                        if (param_3 == 0x13) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<QString,QString&>
                                                                            ((QString *)
                                                                             (param_1 + 0x370),
                                                                             pQVar1);
                                                          if (bVar2) {
                                                            settingsChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0x14) {
                                                          if (param_3 == 0x12) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<QString,QString&>
                                                                              ((QString *)
                                                                               (param_1 + 0x358),
                                                                               pQVar1);
                                                            if (bVar2) {
                                                              settingsChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0x13) {
                                                            if (param_3 == 0x11) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<QString,QString&>
                                                                                ((QString *)
                                                                                 (param_1 + 0x340),
                                                                                 pQVar1);
                                                              if (bVar2) {
                                                                settingsChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0x12) {
                                                              if (param_3 == 0x10) {
                                                                bVar2 = QtMocHelpers::
                                                                                                                                                
                                                  setProperty<QString,QString&>
                                                            ((QString *)(param_1 + 0x328),pQVar1);
                                                  if (bVar2) {
                                                    settingsChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 0x11) {
                                                    if (param_3 == 0xf) {
                                                      bVar2 = QtMocHelpers::
                                                              setProperty<QString,QString&>
                                                                        ((QString *)
                                                                         (param_1 + 0x310),pQVar1);
                                                      if (bVar2) {
                                                        settingsChanged(param_1);
                                                      }
                                                    }
                                                    else if (param_3 < 0x10) {
                                                      if (param_3 == 0xe) {
                                                        bVar2 = QtMocHelpers::
                                                                setProperty<QString,QString&>
                                                                          ((QString *)
                                                                           (param_1 + 0x2f8),pQVar1)
                                                        ;
                                                        if (bVar2) {
                                                          settingsChanged(param_1);
                                                        }
                                                      }
                                                      else if (param_3 < 0xf) {
                                                        if (param_3 == 0xd) {
                                                          bVar2 = QtMocHelpers::
                                                                  setProperty<QString,QString&>
                                                                            ((QString *)
                                                                             (param_1 + 0x2e0),
                                                                             pQVar1);
                                                          if (bVar2) {
                                                            settingsChanged(param_1);
                                                          }
                                                        }
                                                        else if (param_3 < 0xe) {
                                                          if (param_3 == 0xc) {
                                                            bVar2 = QtMocHelpers::
                                                                    setProperty<QString,QString&>
                                                                              ((QString *)
                                                                               (param_1 + 0x2c8),
                                                                               pQVar1);
                                                            if (bVar2) {
                                                              settingsChanged(param_1);
                                                            }
                                                          }
                                                          else if (param_3 < 0xd) {
                                                            if (param_3 == 0xb) {
                                                              bVar2 = QtMocHelpers::
                                                                      setProperty<QString,QString&>
                                                                                ((QString *)
                                                                                 (param_1 + 0x2b0),
                                                                                 pQVar1);
                                                              if (bVar2) {
                                                                fontChanged(param_1);
                                                              }
                                                            }
                                                            else if (param_3 < 0xc) {
                                                              if (param_3 == 10) {
                                                                setShowBatteryPct(param_1,(bool)*
                                                  pQVar1);
                                                  }
                                                  else if (param_3 < 0xb) {
                                                    if (param_3 == 9) {
                                                      setPowerButtonAction(param_1,pQVar1);
                                                    }
                                                    else if (param_3 < 10) {
                                                      if (param_3 == 8) {
                                                        setLidAction(param_1,pQVar1);
                                                      }
                                                      else if (param_3 < 9) {
                                                        if (param_3 == 7) {
                                                          setAcSuspend(param_1,*(int *)pQVar1);
                                                        }
                                                        else if (param_3 < 8) {
                                                          if (param_3 == 6) {
                                                            setAcBlank(param_1,*(int *)pQVar1);
                                                          }
                                                          else if (param_3 < 7) {
                                                            if (param_3 == 5) {
                                                              setBatSuspend(param_1,*(int *)pQVar1);
                                                            }
                                                            else if (param_3 < 6) {
                                                              if (param_3 == 4) {
                                                                setBatBlank(param_1,*(int *)pQVar1);
                                                              }
                                                              else if (param_3 < 5) {
                                                                if (param_3 == 3) {
                                                                  bVar2 = QtMocHelpers::
                                                                          setProperty<bool,bool&>
                                                                                    ((bool *)(
                                                  param_1 + 0x39),(bool *)pQVar1);
                                                  if (bVar2) {
                                                    settingsChanged(param_1);
                                                  }
                                                  }
                                                  else if (param_3 < 4) {
                                                    if (param_3 == 1) {
                                                      setNightLightOn(param_1,(bool)*pQVar1);
                                                    }
                                                    else if (param_3 == 2) {
                                                      setNightWarmth(param_1,*(int *)pQVar1);
                                                    }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
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



// ==== 0014d9ce  Settings::metaObject

/* Settings::metaObject() const */

undefined1 * __thiscall Settings::metaObject(Settings *this)

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



// ==== 0014da16  Settings::qt_metacast

/* Settings::qt_metacast(char const*) */

Settings * __thiscall Settings::qt_metacast(Settings *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (Settings *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"Settings");
    if (iVar1 != 0) {
      this = (Settings *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014da6a  Settings::qt_metacall

/* Settings::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
Settings::qt_metacall(Settings *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x55) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x55;
    }
    if (param_2 == 7) {
      if (local_28 < 0x55) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x55;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -99;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014db60  Settings::displaysChanged

/* Settings::displaysChanged() */

void __thiscall Settings::displaysChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 0014db8c  Settings::settingsChanged

/* Settings::settingsChanged() */

void __thiscall Settings::settingsChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 0014dbb8  Settings::dockPrefsChanged

/* Settings::dockPrefsChanged() */

void __thiscall Settings::dockPrefsChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 0014dbe4  Settings::wallpaperChanged

/* Settings::wallpaperChanged(QString const&) */

void __thiscall Settings::wallpaperChanged(Settings *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,3,(void *)0x0,param_1);
  return;
}



// ==== 0014dc1c  Settings::slideshowAdvanced

/* Settings::slideshowAdvanced(QString const&) */

void __thiscall Settings::slideshowAdvanced(Settings *this,QString *param_1)

{
  QMetaObject::activate<void,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,4,(void *)0x0,param_1);
  return;
}



// ==== 0014dc54  Settings::powerChanged

/* Settings::powerChanged() */

void __thiscall Settings::powerChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 0014dc80  Settings::fontChanged

/* Settings::fontChanged() */

void __thiscall Settings::fontChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,6,(void **)0x0);
  return;
}



// ==== 0014dcac  Settings::storageChanged

/* Settings::storageChanged() */

void __thiscall Settings::storageChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,7,(void **)0x0);
  return;
}



// ==== 0014dcd8  Settings::inputChanged

/* Settings::inputChanged() */

void __thiscall Settings::inputChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,8,(void **)0x0);
  return;
}



// ==== 0014dd04  Settings::accessibilityChanged

/* Settings::accessibilityChanged() */

void __thiscall Settings::accessibilityChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,9,(void **)0x0);
  return;
}



// ==== 0014dd30  Settings::privacyChanged

/* Settings::privacyChanged() */

void __thiscall Settings::privacyChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,10,(void **)0x0);
  return;
}



// ==== 0014dd5c  Settings::securityChanged

/* Settings::securityChanged() */

void __thiscall Settings::securityChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xb,(void **)0x0);
  return;
}



// ==== 0014dd88  Settings::dockChanged

/* Settings::dockChanged() */

void __thiscall Settings::dockChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xc,(void **)0x0);
  return;
}



// ==== 0014ddb4  Settings::localeChanged

/* Settings::localeChanged() */

void __thiscall Settings::localeChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xd,(void **)0x0);
  return;
}



// ==== 0014dde0  Settings::sessionChanged

/* Settings::sessionChanged() */

void __thiscall Settings::sessionChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xe,(void **)0x0);
  return;
}



// ==== 0014de0c  Settings::notifsChanged

/* Settings::notifsChanged() */

void __thiscall Settings::notifsChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xf,(void **)0x0);
  return;
}



// ==== 0014de38  Settings::wallpaperPrefsChanged

/* Settings::wallpaperPrefsChanged() */

void __thiscall Settings::wallpaperPrefsChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x10,(void **)0x0);
  return;
}



// ==== 0014de64  Settings::soundChanged

/* Settings::soundChanged() */

void __thiscall Settings::soundChanged(Settings *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0x11,(void **)0x0);
  return;
}



// ==== 0014de90  Settings::screensaverFinished

/* Settings::screensaverFinished(int, bool) */

void __thiscall Settings::screensaverFinished(Settings *this,int param_1,bool param_2)

{
  bool local_15;
  int local_14;
  Settings *local_10;
  
  local_15 = param_2;
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,int,bool>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0x12,(void *)0x0,&local_14,&local_15);
  return;
}



// ==== 00182d62  Settings::Settings

/* Settings::Settings(QObject*) */

void __thiscall Settings::Settings(Settings *this,QObject *param_1)

{
  QString *this_00;
  long in_FS_OFFSET;
  QString local_b8 [32];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QString local_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032bc40;
  *(undefined8 *)(this + 0x10) = 0;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0x18));
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)(this + 0x30));
  this[0x38] = (Settings)0x0;
  this[0x39] = (Settings)0x0;
  *(undefined4 *)(this + 0x3c) = 4000;
  *(undefined4 *)(this + 0x40) = 10;
  *(undefined4 *)(this + 0x44) = 0x14;
  *(undefined4 *)(this + 0x48) = 0xf;
  *(undefined4 *)(this + 0x4c) = 0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"suspend",7);
  QString::QString((QString *)(this + 0x50),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"poweroff",8);
  QString::QString((QString *)(this + 0x68),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  this[0x80] = (Settings)0x1;
  this[0x81] = (Settings)0x0;
  *(undefined4 *)(this + 0x84) = 300;
  *(undefined4 *)(this + 0x88) = 0x1e;
  *(undefined4 *)(this + 0x8c) = 0x32;
  *(undefined4 *)(this + 0x90) = 0x32;
  *(undefined4 *)(this + 0x94) = 0x20;
  this[0x98] = (Settings)0x1;
  this[0x99] = (Settings)0x1;
  this[0x9a] = (Settings)0x1;
  *(undefined8 *)(this + 0xa0) = 0x3ff0000000000000;
  this[0xa8] = (Settings)0x0;
  this[0xa9] = (Settings)0x0;
  this[0xaa] = (Settings)0x0;
  *(undefined8 *)(this + 0xb0) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xc0) = 0x30;
  *(undefined4 *)(this + 0xc4) = 1;
  *(undefined4 *)(this + 200) = 0x3b;
  *(undefined4 *)(this + 0xcc) = 0x50;
  *(undefined8 *)(this + 0xd0) = 0x3ff199999999999a;
  *(undefined8 *)(this + 0xd8) = 0x4000000000000000;
  *(undefined8 *)(this + 0xe0) = 0x3fc3333333333333;
  *(undefined8 *)(this + 0xe8) = 0x3fd999999999999a;
  QList<QVariant>::QList((QList<QVariant> *)(this + 0xf0));
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"/usr/share/ncde/",0x10);
  QString::QString((QString *)(this + 0x108),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"/.config/ncde/",0xe);
  QString::QString(local_98,(QArrayDataPointer *)local_78);
  QDir::homePath();
  ::operator+((QString *)(this + 0x120),local_b8);
  QString::~QString(local_b8);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"en_US.UTF-8",0xb)
  ;
  QString::QString((QString *)(this + 0x138),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"en_US.UTF-8",0xb)
  ;
  QString::QString((QString *)(this + 0x150),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"us",2);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  QList<QString>::QList(this + 0x168,local_58,1);
  this_00 = (QString *)local_40;
  while (this_00 != local_58) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"us",2);
  QString::QString((QString *)(this + 0x180),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"chromium",8);
  QString::QString((QString *)(this + 0x198),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"hummingbird-courier",0x13);
  QString::QString((QString *)(this + 0x1b0),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"orchidee",8);
  QString::QString((QString *)(this + 0x1c8),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"ncde-terminal",0xd);
  QString::QString((QString *)(this + 0x1e0),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  this[0x1f8] = (Settings)0x0;
  *(undefined4 *)(this + 0x1fc) = 1;
  this[0x200] = (Settings)0x1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"10:00 PM",8);
  QString::QString((QString *)(this + 0x208),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"7:00 AM",7);
  QString::QString((QString *)(this + 0x220),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QList<QString>::QList((QList<QString> *)(this + 0x238));
  this[0x250] = (Settings)0x0;
  *(undefined4 *)(this + 0x254) = 5;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"fill",4);
  QString::QString((QString *)(this + 600),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  *(undefined4 *)(this + 0x270) = 100;
  *(undefined4 *)(this + 0x274) = 0x50;
  QString::QString((QString *)(this + 0x278));
  QString::QString((QString *)(this + 0x290));
  *(undefined8 *)(this + 0x2a8) = 0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"Cormorant Garamond",0x12);
  QString::QString((QString *)(this + 0x2b0),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QString::QString((QString *)(this + 0x2c8));
  QString::QString((QString *)(this + 0x2e0));
  QString::QString((QString *)(this + 0x2f8));
  QString::QString((QString *)(this + 0x310));
  QString::QString((QString *)(this + 0x328));
  QString::QString((QString *)(this + 0x340));
  QString::QString((QString *)(this + 0x358));
  QString::QString((QString *)(this + 0x370));
  this[0x388] = (Settings)0x1;
  this[0x389] = (Settings)0x1;
  this[0x38a] = (Settings)0x0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"auto",4);
  QString::QString((QString *)(this + 0x390),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_78,(QTypedArrayData *)0x0,L"auto",4);
  QString::QString((QString *)(this + 0x3a8),(QArrayDataPointer *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  QString::QString((QString *)(this + 0x3c0));
  this[0x3d8] = (Settings)0x1;
  this[0x3d9] = (Settings)0x0;
  QString::QString((QString *)(this + 0x3e0));
  *(undefined4 *)(this + 0x3f8) = 0x1f90;
  this[0x3fc] = (Settings)0x1;
  *(undefined4 *)(this + 0x400) = 0x1e;
  this[0x404] = (Settings)0x1;
  this[0x405] = (Settings)0x1;
  *(undefined4 *)(this + 0x408) = 0;
  this[0x40c] = (Settings)0x0;
  *(undefined4 *)(this + 0x410) = 300;
  QFileSystemWatcher::QFileSystemWatcher((QFileSystemWatcher *)(this + 0x418),(QObject *)0x0);
  this[0x428] = (Settings)0x0;
  *(undefined4 *)(this + 0x42c) = 400;
  this[0x430] = (Settings)0x0;
  *(undefined8 *)(this + 0x438) = 0x3ff0000000000000;
  *(undefined8 *)(this + 0x440) = 0;
  *(undefined8 *)(this + 0x448) = 0x3ff0000000000000;
  *(undefined8 *)(this + 0x450) = 0x3ff0000000000000;
  QString::QString((QString *)(this + 0x458));
  this[0x470] = (Settings)0x0;
  QString::QString((QString *)(this + 0x478));
  *(undefined8 *)(this + 0x490) = 0;
  this[0x498] = (Settings)0x0;
  QString::QString((QString *)(this + 0x4a0));
  *(undefined8 *)(this + 0x4b8) = 0;
  *(undefined8 *)(this + 0x4c0) = 0;
  *(undefined8 *)(this + 0x4c8) = 0;
  loadDisplay(this);
  loadPower(this);
  loadFonts(this);
  loadStorage(this);
  loadInput(this);
  loadAccessibility(this);
  loadPrivacy(this);
  loadScreensaver(this);
  loadDateTime(this);
  loadNetwork(this);
  loadDock(this);
  loadLocale(this);
  loadDefaults(this);
  loadNotifications(this);
  loadWallpaperPrefs(this);
  loadSound(this);
  loadKickass(this);
  loadSectionColors(this);
  if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00183f54  Settings::onScreenIdleChanged

/* Settings::onScreenIdleChanged() */

void __thiscall Settings::onScreenIdleChanged(Settings *this)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  QString *this_00;
  long in_FS_OFFSET;
  int local_11c;
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QArrayDataPointer<char16_t> local_c8 [32];
  QList local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [24];
  QString aQStack_50 [16];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = false;
  if (*(long *)(this + 0xb8) == 0) {
LAB_00183fd2:
    bVar2 = true;
  }
  else {
    QObject::property((char *)local_68);
    bVar1 = true;
    cVar3 = ::QVariant::toBool();
    if (cVar3 != '\x01') goto LAB_00183fd2;
    bVar2 = false;
  }
  if (bVar1) {
    ::QVariant::~QVariant(local_68);
  }
  if (bVar2) goto LAB_001842d0;
  if (*(long *)(this + 0xb0) == 0) {
LAB_0018402d:
    bVar1 = false;
  }
  else {
    cVar3 = Lelan::onBattery(*(Lelan **)(this + 0xb0));
    if (cVar3 == '\0') goto LAB_0018402d;
    bVar1 = true;
  }
  if (bVar1) {
    local_11c = *(int *)(this + 0x44);
  }
  else {
    local_11c = *(int *)(this + 0x4c);
  }
  if (0 < local_11c) {
    QString::QString(local_88);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"suspend",7);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_c8);
    QList<QString>::QList(local_a8,local_68,1);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"systemctl",9);
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    QProcess::startDetached(local_e8,local_a8,local_88,(longlong *)0x0);
    QString::~QString(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QList<QString>::~QList((QList<QString> *)local_a8);
    this_00 = aQStack_50;
    while (this_00 != (QString *)local_68) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    QString::~QString(local_88);
  }
LAB_001842d0:
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001842f6  Settings::saveSurfaceGlass

/* Settings::saveSurfaceGlass(QString const&, QColor const&, double, double, QColor const&, QColor
   const&) */

void __thiscall
Settings::saveSurfaceGlass
          (Settings *this,QString *param_1,QColor *param_2,double param_3,double param_4,
          QColor *param_5,QColor *param_6)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_a8 [8];
  undefined8 local_a0;
  undefined1 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = &LAB_00299776;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"glass-surfaces",0xe);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::readConfig(local_a8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  local_a0 = 0;
  QColor::name(local_68,param_2,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString((QString *)local_88,"tint");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)&local_a0,(QString *)local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  ::QVariant::QVariant(local_48,param_3);
  QString::QString(local_68,"shine");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_4);
  QString::QString(local_68,"glow");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  QColor::name(local_68,param_5,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString((QString *)local_88,"border");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)&local_a0,(QString *)local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  QColor::name(local_68,param_6,0);
  ::QVariant::QVariant(local_48,local_68);
  QString::QString((QString *)local_88,"glowColor");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]
                     ((QMap<QString,QVariant> *)&local_a0,(QString *)local_88);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString((QString *)local_88);
  ::QVariant::~QVariant(local_48);
  QString::~QString(local_68);
  ::QVariant::QVariant(local_48,(QMap *)&local_a0);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_a8,param_1);
  ::QVariant::operator=(pQVar1,local_48);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_00299776;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"glass-surfaces",0xe);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)local_a8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_a0);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001848c0  Settings::saveWidgetStyleMap

/* Settings::saveWidgetStyleMap(QString const&, QMap<QString, QVariant> const&) */

void __thiscall Settings::saveWidgetStyleMap(Settings *this,QString *param_1,QMap *param_2)

{
  QVariant *this_00;
  long in_FS_OFFSET;
  QString local_a0 [8];
  undefined1 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = &LAB_00299794;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"widget-styles",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::readConfig(local_a0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::QVariant(local_48,param_2);
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_a0,param_1);
  ::QVariant::operator=(this_00,local_48);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_00299794;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"widget-styles",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)local_a0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00184adc  Settings::resetWidgetStyle

/* Settings::resetWidgetStyle(QString const&) */

void __thiscall Settings::resetWidgetStyle(Settings *this,QString *param_1)

{
  long in_FS_OFFSET;
  QString local_70 [8];
  undefined1 *local_68;
  undefined1 *local_60;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_68 = &LAB_00299794;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"widget-styles",0xd);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  Lelan::readConfig(local_70);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QMap<QString,QVariant>::remove((QMap<QString,QVariant> *)local_70,param_1);
  local_60 = &LAB_00299794;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"widget-styles",0xd);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  Lelan::writeConfig(local_38,(QMap *)local_70);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_70);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00184c8a  Settings::saveColorOverrides

/* Settings::saveColorOverrides() */

void __thiscall Settings::saveColorOverrides(Settings *this)

{
  char cVar1;
  QVariant *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 0;
  cVar1 = QString::isEmpty((QString *)(this + 0x328));
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_48,(QString *)(this + 0x328));
    QString::QString(local_68,"accentOverride");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
  }
  cVar1 = QString::isEmpty((QString *)(this + 0x340));
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_48,(QString *)(this + 0x340));
    QString::QString(local_68,"accentMutedOverride");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
  }
  cVar1 = QString::isEmpty((QString *)(this + 0x358));
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_48,(QString *)(this + 0x358));
    QString::QString(local_68,"glowOverride");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
  }
  cVar1 = QString::isEmpty((QString *)(this + 0x370));
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_48,(QString *)(this + 0x370));
    QString::QString(local_68,"borderOverride");
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
    ::QVariant::operator=(pQVar2,local_48);
    QString::~QString(local_68);
    ::QVariant::~QVariant(local_48);
  }
  local_90 = &LAB_0029e7af_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"color-overrides",0xf);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_98);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00185066  Settings::saveSectionColors

/* Settings::saveSectionColors() */

void __thiscall Settings::saveSectionColors(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b8;
  undefined1 *local_b0;
  undefined1 *local_a8;
  undefined1 *local_a0;
  undefined1 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = 0;
  ::QVariant::QVariant(local_48,(QString *)(this + 0x2e0));
  local_b0 = &LAB_0029e7d0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"topPanelTextColor",0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x2f8));
  local_a8 = &LAB_0029e7f4;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"gliaTextColor",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x2c8));
  local_a0 = &LAB_0029e810;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"dockHoverTextColor",0x12);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x310));
  local_98 = &LAB_0029e838;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"leapFrogTextColor",0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"section-colors";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"section-colors",0xe);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001854be  Settings::loadSectionColors

/* Settings::loadSectionColors() */

void __thiscall Settings::loadSectionColors(Settings *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_f8 [8];
  wchar16 *local_f0;
  undefined1 *local_e8;
  undefined1 *local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = L"section-colors";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"section-colors",0xe);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68);
    local_e8 = &LAB_0029e7d0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"topPanelTextColor",0x11);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x2e0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_e0 = &LAB_0029e7f4;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"gliaTextColor",0xd);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x2f8),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_d8 = &LAB_0029e810;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"dockHoverTextColor",0x12);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x2c8),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_d0 = &LAB_0029e838;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"leapFrogTextColor",0x11);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x310),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    settingsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00185abc  Settings::saveFiligreepalette

/* Settings::saveFiligreepalette(QString const&, double, double, QList<QVariant> const&) */

void __thiscall
Settings::saveFiligreepalette
          (Settings *this,QString *param_1,double param_2,double param_3,QList *param_4)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  QString local_a8 [8];
  undefined8 local_a0;
  wchar16 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = L"filigree-palettes";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"filigree-palettes",0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::readConfig(local_a8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  local_a0 = 0;
  ::QVariant::QVariant(local_48,param_2);
  QString::QString(local_68,"hue");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_3);
  QString::QString(local_68,"sat");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,param_4);
  QString::QString(local_68,"palette");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QMap *)&local_a0);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_a8,param_1);
  ::QVariant::operator=(pQVar1,local_48);
  ::QVariant::~QVariant(local_48);
  local_90 = L"filigree-palettes";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"filigree-palettes",0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)local_a8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_a0);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00185ebe  Settings::setSlideshowPaused

/* Settings::setSlideshowPaused(bool) */

void __thiscall Settings::setSlideshowPaused(Settings *this,bool param_1)

{
  if ((Settings)param_1 != this[0x38a]) {
    this[0x38a] = (Settings)param_1;
    settingsChanged(this);
  }
  return;
}



// ==== 00185efc  Settings::saveDateTime

/* Settings::saveDateTime() */

void __thiscall Settings::saveDateTime(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_98;
  undefined *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 0;
  ::QVariant::QVariant(local_48,(QString *)(this + 0x390));
  QString::QString(local_68,"hourFormat");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x40c]);
  QString::QString(local_68,"showSeconds");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x3d8]);
  QString::QString(local_68,"ntpEnabled");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x3c0));
  QString::QString(local_68,"timezoneManual");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  local_90 = &DAT_0029e8e6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"datetime",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_98);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018626c  Settings::loadDateTime

/* Settings::loadDateTime() */

void __thiscall Settings::loadDateTime(Settings *this)

{
  char cVar1;
  Settings SVar2;
  long in_FS_OFFSET;
  QString local_f8 [8];
  undefined *local_f0;
  undefined1 *local_e8;
  undefined1 *local_e0;
  undefined1 *local_d8;
  undefined *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = &DAT_0029e8e6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"datetime",8);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,(QString *)(this + 0x390));
    local_e8 = &LAB_0029e8f7_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"hourFormat",10)
    ;
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x390),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x40c]);
    local_e0 = &LAB_0029e90e;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"showSeconds",0xb);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x40c] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x3d8]);
    local_d8 = &LAB_0029e926;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"ntpEnabled",10)
    ;
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x3d8] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x3c0));
    local_d0 = &DAT_0029e93c;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"timezoneManual",0xe);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x3c0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    settingsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00186848  Settings::saveNetwork

/* Settings::saveNetwork() */

void __thiscall Settings::saveNetwork(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b0;
  wchar16 *local_a8;
  wchar16 *local_a0;
  wchar16 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b0 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x3d9]);
  local_a8 = L"proxyEnabled";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"proxyEnabled",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x3e0));
  local_a0 = L"proxyHost";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"proxyHost",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x3f8));
  local_98 = L"proxyPort";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"proxyPort",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"network";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"network",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00186bcc  Settings::loadNetwork

/* Settings::loadNetwork() */

void __thiscall Settings::loadNetwork(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_f0 [8];
  wchar16 *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_e8 = L"network";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"network",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f0);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f0);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,(bool)this[0x3d9]);
    local_e0 = L"proxyEnabled";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"proxyEnabled",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f0);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x3d9] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x3e0));
    local_d8 = L"proxyHost";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"proxyHost",9);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f0);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x3e0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x3f8));
    local_d0 = L"proxyPort";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"proxyPort",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f0);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x3f8) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    settingsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00187072  Settings::saveScreensaver

/* Settings::saveScreensaver() */

void __thiscall Settings::saveScreensaver(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 0;
  ::QVariant::QVariant(local_48,*(int *)(this + 0x410));
  QString::QString(local_68,"timeout");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x3a8));
  QString::QString(local_68,"season");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x3fc]);
  QString::QString(local_68,"clockVisible");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x400));
  QString::QString(local_68,"fps");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  local_90 = L"screensaver";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"screensaver",0xb)
  ;
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_98);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001873dc  Settings::loadScreensaver

/* Settings::loadScreensaver() */

void __thiscall Settings::loadScreensaver(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_f8 [8];
  wchar16 *local_f0;
  undefined1 *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  undefined *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = L"screensaver";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"screensaver",0xb)
  ;
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,*(int *)(this + 0x410));
    local_e8 = &LAB_0029e243_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"timeout",7);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x410) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x3a8));
    local_e0 = L"season";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"season",6);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x3a8),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x3fc]);
    local_d8 = L"clockVisible";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"clockVisible",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x3fc] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x400));
    local_d0 = &DAT_0029ea0c;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"fps",3);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x400) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    settingsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018798a  Settings::previewScreensaver(QString_const&)::{lambda(int,QProcess::ExitStatus)#1}::operator()

/* Settings::previewScreensaver(QString const&)::{lambda(int,
   QProcess::ExitStatus)#1}::TEMPNAMEPLACEHOLDERVALUE(int, QProcess::ExitStatus) const */

void __thiscall
Settings::previewScreensaver(QString_const&)::{lambda(int,QProcess::ExitStatus)#1}::operator()
          (_lambda_int_QProcess__ExitStatus__1_ *this,int param_1,int param_3)

{
  screensaverFinished(*(Settings **)this,param_1,param_3 == 1);
  return;
}



// ==== 001879be  Settings::previewScreensaver

/* WARNING: Removing unreachable block (ram,0x00187a54) */
/* Settings::previewScreensaver(QString const&) */

void __thiscall Settings::previewScreensaver(Settings *this,QString *param_1)

{
  QList *pQVar1;
  undefined8 uVar2;
  char cVar3;
  QProcess *this_00;
  QString *pQVar4;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  Settings *local_c8 [4];
  undefined4 local_a8 [8];
  QString local_88 [24];
  QString aQStack_70 [24];
  QString aQStack_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  cVar3 = screensaverRunning(this);
  if (cVar3 == '\0') {
    if (*(long *)(this + 0x10) == 0) {
      this_00 = operator_new(0x10);
      QProcess::QProcess(this_00,(QObject *)this);
      *(QProcess **)(this + 0x10) = this_00;
      local_c8[0] = this;
      QObject::
      connect<void(QProcess::*)(int,QProcess::ExitStatus),Settings::previewScreensaver(QString_const&)::_lambda(int,QProcess::ExitStatus)_1_>
                (local_a8,*(undefined8 *)(this + 0x10),QProcess::finished,0,this,local_c8,0);
      QMetaObject::Connection::~Connection((Connection *)local_a8);
    }
    pQVar4 = *(QString **)(this + 0x10);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"ncde-portal",0xb);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QProcess::setProgram(pQVar4);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    pQVar1 = *(QList **)(this + 0x10);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"--screensaver",0xd);
    QString::QString(local_88,(QArrayDataPointer *)local_108);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"--season",8);
    QString::QString(aQStack_70,(QArrayDataPointer *)local_e8);
    cVar3 = QString::isEmpty(param_1);
    if (cVar3 == '\0') {
      QString::QString(aQStack_58,param_1);
    }
    else {
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"auto",4);
      QString::QString(aQStack_58,(QArrayDataPointer *)local_c8);
    }
    QList<QString>::QList(local_a8,local_88,3);
    QProcess::setArguments(pQVar1);
    QList<QString>::~QList((QList<QString> *)local_a8);
    pQVar4 = (QString *)local_40;
    while (pQVar4 != local_88) {
      pQVar4 = pQVar4 + -0x18;
      QString::~QString(pQVar4);
    }
    if (cVar3 != '\0') {
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    uVar2 = *(undefined8 *)(this + 0x10);
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_a8,3);
    QProcess::start(uVar2,local_a8[0]);
  }
  if (local_40[0] == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00187eba  Settings::screensaverRunning

/* Settings::screensaverRunning() const */

undefined8 __thiscall Settings::screensaverRunning(Settings *this)

{
  int iVar1;
  
  if ((*(long *)(this + 0x10) != 0) && (iVar1 = QProcess::state(), iVar1 != 0)) {
    return 1;
  }
  return 0;
}



// ==== 00187ef6  Settings::savePrivacy

/* Settings::savePrivacy() */

void __thiscall Settings::savePrivacy(Settings *this)

{
  saveConfPrivacy(this);
  return;
}



// ==== 00187f12  Settings::saveSecurity

/* Settings::saveSecurity() */

void __thiscall Settings::saveSecurity(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b0;
  undefined *local_a8;
  undefined1 *local_a0;
  undefined1 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b0 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x404]);
  local_a8 = &DAT_0029ea60;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"requirePassword",0xf);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x408));
  local_a0 = &LAB_0029ea7f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"requirePasswordDelay",0x14);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x405]);
  local_98 = &LAB_0029eaaa;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"kickassArmed",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029eac3_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"security",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00188298  Settings::saveConfig

/* Settings::saveConfig() */

void __thiscall Settings::saveConfig(Settings *this)

{
  savePower(this);
  saveFontSettings(this);
  saveDockPrefs(this);
  return;
}



// ==== 001882cc  Settings::setKickassArmed

/* Settings::setKickassArmed(bool) */

void __thiscall Settings::setKickassArmed(Settings *this,bool param_1)

{
  this[0x405] = (Settings)param_1;
  saveSecurity(this);
  applyKickassArmed(this);
  return;
}



// ==== 00188306  Settings::applyKickassArmed

/* Settings::applyKickassArmed() */

void __thiscall Settings::applyKickassArmed(Settings *this)

{
  Settings SVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  QString *this_00;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_1c8 [32];
  QArrayDataPointer<char16_t> local_1a8 [32];
  QString local_188 [32];
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QString local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [24];
  QString aQStack_90 [24];
  QString aQStack_78 [24];
  QString aQStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if ((applyKickassArmed()::unitInstalled != '\0') ||
     (iVar9 = __cxa_guard_acquire(&applyKickassArmed()::unitInstalled), iVar9 == 0))
  goto LAB_001885da;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  bVar7 = false;
  bVar6 = false;
  bVar5 = false;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1a8,(QTypedArrayData *)0x0,L"/usr/lib/systemd/user/vesper-brain.service",0x2a);
  QString::QString(local_188,(QArrayDataPointer *)local_1a8);
  cVar8 = QFile::exists(local_188);
  if (cVar8 == '\0') {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_168,(QTypedArrayData *)0x0,L"/etc/systemd/user/vesper-brain.service",0x26);
    bVar4 = true;
    QString::QString(local_148,(QArrayDataPointer *)local_168);
    bVar3 = true;
    cVar8 = QFile::exists(local_148);
    if (cVar8 != '\0') goto LAB_00188506;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"/.config/systemd/user/vesper-brain.service",0x2a);
    bVar2 = true;
    QString::QString(local_e8,(QArrayDataPointer *)local_108);
    bVar7 = true;
    QDir::homePath();
    bVar6 = true;
    ::operator+(local_c8,local_128);
    bVar5 = true;
    cVar8 = QFile::exists(local_c8);
    if (cVar8 != '\0') goto LAB_00188506;
    applyKickassArmed()::unitInstalled = '\0';
  }
  else {
LAB_00188506:
    applyKickassArmed()::unitInstalled = '\x01';
  }
  __cxa_guard_release(&applyKickassArmed()::unitInstalled);
  if (bVar5) {
    QString::~QString(local_c8);
  }
  if (bVar6) {
    QString::~QString(local_128);
  }
  if (bVar7) {
    QString::~QString(local_e8);
  }
  if (bVar2) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  if (bVar3) {
    QString::~QString(local_148);
  }
  if (bVar4) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  }
  QString::~QString(local_188);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1a8);
LAB_001885da:
  if (applyKickassArmed()::unitInstalled == '\x01') {
    QString::QString(local_c8);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"--user",6);
    QString::QString(local_a8,(QArrayDataPointer *)local_188);
    SVar1 = this[0x405];
    if (SVar1 == (Settings)0x0) {
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"disable",7);
      QString::QString(aQStack_90,(QArrayDataPointer *)local_148);
    }
    else {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"enable",6);
      QString::QString(aQStack_90,(QArrayDataPointer *)local_168);
    }
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"--now",5);
    QString::QString(aQStack_78,(QArrayDataPointer *)local_128);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"vesper-brain.service",0x14);
    QString::QString(aQStack_60,(QArrayDataPointer *)local_108);
    QList<QString>::QList(local_e8,local_a8,4);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_1c8,(QTypedArrayData *)0x0,L"systemctl",9);
    QString::QString((QString *)local_1a8,(QArrayDataPointer *)local_1c8);
    QProcess::startDetached((QString *)local_1a8,(QList *)local_e8,local_c8,(longlong *)0x0);
    QString::~QString((QString *)local_1a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1c8);
    QList<QString>::~QList((QList<QString> *)local_e8);
    this_00 = aQStack_48;
    while (this_00 != local_a8) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
    if (SVar1 == (Settings)0x0) {
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
    }
    else {
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
    QString::~QString(local_c8);
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00188b38  Settings::loadKickass

/* Settings::loadKickass() */

void __thiscall Settings::loadKickass(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_d0 [8];
  undefined1 *local_c8;
  undefined *local_c0;
  undefined1 *local_b8;
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_c8 = &LAB_0029eac3_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"security",8);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_d0);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_d0);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,(bool)this[0x404]);
    local_c0 = &DAT_0029ea60;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"requirePassword",0xf);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d0);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x404] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x408));
    local_b8 = &LAB_0029ea7f_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"requirePasswordDelay",0x14);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d0);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x408) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x405]);
    local_b0 = &LAB_0029eaaa;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"kickassArmed",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d0);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x405] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
  }
  applyKickassArmed(this);
  securityChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_d0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00188fbe  Settings::initWatcher()::{lambda()#1}::operator()

/* Settings::initWatcher()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Settings::initWatcher()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  settingsChanged(*(Settings **)this);
  return;
}



// ==== 00188fdc  Settings::initWatcher

/* Settings::initWatcher() */

void __thiscall Settings::initWatcher(Settings *this)

{
  long in_FS_OFFSET;
  Settings *local_70;
  QString local_68 [32];
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x428] == (Settings)0x0) {
    this[0x428] = (Settings)0x1;
    QDir::homePath();
    ::operator+(local_68,(char *)local_48);
    QString::~QString(local_48);
    QFileSystemWatcher::addPath((QString *)(this + 0x418));
    local_70 = this;
    QObject::
    connect<void(QFileSystemWatcher::*)(QString_const&,QFileSystemWatcher::QPrivateSignal),Settings::initWatcher()::_lambda()_1_>
              (local_48,this + 0x418,QFileSystemWatcher::directoryChanged,0,this,&local_70,0);
    QMetaObject::Connection::~Connection((Connection *)local_48);
    QString::~QString(local_68);
  }
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0018914a  Settings::dockApps

/* Settings::dockApps() const */

QList<QVariant> * Settings::dockApps(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0xf0));
  return in_RDI;
}



// ==== 0018917a  Settings::kbLayouts

/* Settings::kbLayouts() const */

QList<QString> * Settings::kbLayouts(void)

{
  long in_RSI;
  QList<QString> *in_RDI;
  
  QList<QString>::QList(in_RDI,(QList *)(in_RSI + 0x168));
  return in_RDI;
}



// ==== 001891aa  Settings::activeKbLayout

/* Settings::activeKbLayout() const */

QString * Settings::activeKbLayout(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x180));
  return in_RDI;
}



// ==== 001891da  Settings::userName

/* Settings::userName() const */

Settings * __thiscall Settings::userName(Settings *this)

{
  long in_FS_OFFSET;
  QDir local_40 [8];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDir::home(local_40);
  QDir::dirName();
  qEnvironmentVariable((char *)this,(QString *)&LAB_0029ec3a);
  QString::~QString(local_38);
  QDir::~QDir(local_40);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001892ac  Settings::customWallpapers

/* Settings::customWallpapers() const */

QList<QString> * Settings::customWallpapers(void)

{
  long in_RSI;
  QList<QString> *in_RDI;
  
  QList<QString>::QList(in_RDI,(QList *)(in_RSI + 0x238));
  return in_RDI;
}



// ==== 001892dc  Settings::slideshowEnabled

/* Settings::slideshowEnabled() const */

Settings __thiscall Settings::slideshowEnabled(Settings *this)

{
  return this[0x250];
}



// ==== 001892f2  Settings::slideshowInterval

/* Settings::slideshowInterval() const */

undefined4 __thiscall Settings::slideshowInterval(Settings *this)

{
  return *(undefined4 *)(this + 0x254);
}



// ==== 00189306  Settings::fitMode

/* Settings::fitMode() const */

QString * Settings::fitMode(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 600));
  return in_RDI;
}



// ==== 00189336  Settings::displays

/* Settings::displays() const */

QList<QVariant> * Settings::displays(void)

{
  long in_RSI;
  QList<QVariant> *in_RDI;
  
  QList<QVariant>::QList(in_RDI,(QList *)(in_RSI + 0x18));
  return in_RDI;
}



// ==== 00189364  Settings::nightLightOn

/* Settings::nightLightOn() const */

Settings __thiscall Settings::nightLightOn(Settings *this)

{
  return this[0x38];
}



// ==== 00189376  Settings::nightWarmth

/* Settings::nightWarmth() const */

undefined4 __thiscall Settings::nightWarmth(Settings *this)

{
  return *(undefined4 *)(this + 0x3c);
}



// ==== 00189388  Settings::setNightLightOn

/* Settings::setNightLightOn(bool) */

void __thiscall Settings::setNightLightOn(Settings *this,bool param_1)

{
  if ((Settings)param_1 != this[0x38]) {
    this[0x38] = (Settings)param_1;
    applyNightLight(this);
    settingsChanged(this);
  }
  return;
}



// ==== 001893cc  Settings::setNightWarmth

/* Settings::setNightWarmth(int) */

void __thiscall Settings::setNightWarmth(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x3c)) {
    *(int *)(this + 0x3c) = param_1;
    if (this[0x38] != (Settings)0x0) {
      applyNightLight(this);
    }
    settingsChanged(this);
  }
  return;
}



// ==== 00189418  Settings::batBlank

/* Settings::batBlank() const */

undefined4 __thiscall Settings::batBlank(Settings *this)

{
  return *(undefined4 *)(this + 0x40);
}



// ==== 0018942a  Settings::setBatBlank

/* Settings::setBatBlank(int) */

void __thiscall Settings::setBatBlank(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x40)) {
    *(int *)(this + 0x40) = param_1;
    powerChanged(this);
  }
  return;
}



// ==== 0018945e  Settings::batSuspend

/* Settings::batSuspend() const */

undefined4 __thiscall Settings::batSuspend(Settings *this)

{
  return *(undefined4 *)(this + 0x44);
}



// ==== 00189470  Settings::setBatSuspend

/* Settings::setBatSuspend(int) */

void __thiscall Settings::setBatSuspend(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x44)) {
    *(int *)(this + 0x44) = param_1;
    powerChanged(this);
  }
  return;
}



// ==== 001894a4  Settings::acBlank

/* Settings::acBlank() const */

undefined4 __thiscall Settings::acBlank(Settings *this)

{
  return *(undefined4 *)(this + 0x48);
}



// ==== 001894b6  Settings::setAcBlank

/* Settings::setAcBlank(int) */

void __thiscall Settings::setAcBlank(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x48)) {
    *(int *)(this + 0x48) = param_1;
    powerChanged(this);
  }
  return;
}



// ==== 001894ea  Settings::acSuspend

/* Settings::acSuspend() const */

undefined4 __thiscall Settings::acSuspend(Settings *this)

{
  return *(undefined4 *)(this + 0x4c);
}



// ==== 001894fc  Settings::setAcSuspend

/* Settings::setAcSuspend(int) */

void __thiscall Settings::setAcSuspend(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x4c)) {
    *(int *)(this + 0x4c) = param_1;
    powerChanged(this);
  }
  return;
}



// ==== 00189530  Settings::lidAction

/* Settings::lidAction() const */

QString * Settings::lidAction(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x50));
  return in_RDI;
}



// ==== 0018955e  Settings::setLidAction

/* Settings::setLidAction(QString const&) */

void __thiscall Settings::setLidAction(Settings *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator!=(param_1,(QString *)(this + 0x50));
  if (cVar1 != '\0') {
    QString::operator=((QString *)(this + 0x50),param_1);
    powerChanged(this);
  }
  return;
}



// ==== 001895b0  Settings::powerButtonAction

/* Settings::powerButtonAction() const */

QString * Settings::powerButtonAction(void)

{
  long in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,(QString *)(in_RSI + 0x68));
  return in_RDI;
}



// ==== 001895de  Settings::setPowerButtonAction

/* Settings::setPowerButtonAction(QString const&) */

void __thiscall Settings::setPowerButtonAction(Settings *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator!=(param_1,(QString *)(this + 0x68));
  if (cVar1 != '\0') {
    QString::operator=((QString *)(this + 0x68),param_1);
    powerChanged(this);
  }
  return;
}



// ==== 00189630  Settings::showBatteryPct

/* Settings::showBatteryPct() const */

Settings __thiscall Settings::showBatteryPct(Settings *this)

{
  return this[0x80];
}



// ==== 00189646  Settings::setShowBatteryPct

/* Settings::setShowBatteryPct(bool) */

void __thiscall Settings::setShowBatteryPct(Settings *this,bool param_1)

{
  if ((Settings)param_1 != this[0x80]) {
    this[0x80] = (Settings)param_1;
    powerChanged(this);
  }
  return;
}



// ==== 00189684  Settings::refreshDisplays()::{lambda()#1}::operator()

/* Settings::refreshDisplays()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Settings::refreshDisplays()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  QMap<QString,QVariant> *pQVar1;
  QList<QVariant> *this_00;
  undefined1 auVar2 [16];
  char cVar3;
  QVariant *pQVar4;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [8];
  ulong uStack_60;
  undefined8 local_58;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar3 = QString::isEmpty(*(QString **)this);
  if (cVar3 != '\x01') {
    ::QVariant::QVariant(local_48,*(QList **)(this + 0x10));
    pQVar1 = *(QMap<QString,QVariant> **)(this + 8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"modes",5);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    pQVar4 = (QVariant *)QMap<QString,QVariant>::operator[](pQVar1,local_68);
    ::QVariant::operator=(pQVar4,local_48);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,*(QList **)(this + 0x18));
    pQVar1 = *(QMap<QString,QVariant> **)(this + 8);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"rates",5);
    QString::QString(local_68,(QArrayDataPointer *)local_88);
    pQVar4 = (QVariant *)QMap<QString,QVariant>::operator[](pQVar1,local_68);
    ::QVariant::operator=(pQVar4,local_48);
    QString::~QString(local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
    ::QVariant::~QVariant(local_48);
    this_00 = *(QList<QVariant> **)(this + 0x20);
    ::QVariant::QVariant(local_48,*(QMap **)(this + 8));
    QList<QVariant>::append(this_00,local_48);
    ::QVariant::~QVariant(local_48);
  }
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uStack_60;
  _local_68 = auVar2 << 0x40;
  QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)local_68);
  QMap<QString,QVariant>::operator=(*(QMap<QString,QVariant> **)(this + 8),(QMap *)local_68);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_68);
  _local_68 = (undefined1  [16])0x0;
  local_58 = 0;
  QList<QVariant>::QList((QList<QVariant> *)local_68);
  QList<QVariant>::operator=(*(QList<QVariant> **)(this + 0x10),(QList *)local_68);
  QList<QVariant>::~QList((QList<QVariant> *)local_68);
  _local_68 = (undefined1  [16])0x0;
  local_58 = 0;
  QList<QVariant>::QList((QList<QVariant> *)local_68);
  QList<QVariant>::operator=(*(QList<QVariant> **)(this + 0x18),(QList *)local_68);
  QList<QVariant>::~QList((QList<QVariant> *)local_68);
  QString::clear(*(QString **)this);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00189a26  Settings::refreshDisplays

/* WARNING: Removing unreachable block (ram,0x0018aeeb) */
/* WARNING: Removing unreachable block (ram,0x0018af32) */
/* WARNING: Removing unreachable block (ram,0x0018afe6) */
/* Settings::refreshDisplays() */

void __thiscall Settings::refreshDisplays(Settings *this)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  QVariant *pQVar5;
  int *piVar6;
  QString *pQVar7;
  long in_FS_OFFSET;
  undefined8 local_370;
  undefined8 local_368;
  undefined8 local_360;
  QRegularExpressionMatch local_358 [8];
  QRegularExpressionMatch local_350 [8];
  undefined8 local_348;
  ulong local_340;
  QList<QString> *local_338;
  undefined8 local_330;
  QList<QString> *local_328;
  undefined8 local_320;
  wchar16 *local_318;
  wchar16 *local_310;
  undefined *local_308;
  undefined1 *local_300;
  undefined1 *local_2f8;
  undefined1 *local_2f0;
  undefined1 *local_2e8;
  undefined1 *local_2e0;
  undefined1 *local_2d8;
  undefined *local_2d0;
  undefined *local_2c8;
  undefined *local_2c0;
  undefined *local_2b8;
  undefined1 *local_2b0;
  undefined1 *local_2a8;
  undefined1 *local_2a0;
  undefined1 *local_298;
  QProcess local_288 [16];
  QString local_278 [32];
  QList local_258 [16];
  undefined8 local_248;
  QList<QVariant> local_238 [16];
  undefined8 local_228;
  QList<QVariant> local_218 [16];
  undefined8 local_208;
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  QList<QString> local_1d8 [32];
  undefined2 local_1b8 [16];
  QArrayDataPointer<char16_t> local_198 [32];
  QString local_178 [16];
  undefined8 local_168;
  int local_158 [8];
  int local_138 [8];
  undefined2 local_118 [16];
  undefined4 local_f8 [8];
  undefined8 *local_d8;
  undefined8 *local_d0;
  QList<QVariant> *local_c8;
  QList<QVariant> *local_c0;
  QList *local_b8;
  QVariant local_a8 [32];
  QString local_88 [32];
  QString local_68 [24];
  QString aQStack_50 [16];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QProcess::QProcess(local_288,(QObject *)0x0);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_158,3);
  local_318 = L"--query";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"--query",7);
  QString::QString(local_68,(QArrayDataPointer *)local_f8);
  QList<QString>::QList(&local_d8,local_68,1);
  local_310 = L"xrandr";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,L"xrandr",6);
  QString::QString((QString *)local_118,(QArrayDataPointer *)local_138);
  QProcess::start(local_288,local_118,&local_d8,local_158[0]);
  QString::~QString((QString *)local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
  QList<QString>::~QList((QList<QString> *)&local_d8);
  pQVar7 = aQStack_50;
  while (pQVar7 != local_68) {
    pQVar7 = pQVar7 + -0x18;
    QString::~QString(pQVar7);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  cVar1 = QProcess::waitForFinished((int)local_288);
  if (cVar1 == '\x01') {
    QProcess::readAllStandardOutput();
    QString::fromUtf8<void>(local_278,(QByteArray *)&local_d8);
    QByteArray::~QByteArray((QByteArray *)&local_d8);
    local_258[0] = (QList)0x0;
    local_258[1] = (QList)0x0;
    local_258[2] = (QList)0x0;
    local_258[3] = (QList)0x0;
    local_258[4] = (QList)0x0;
    local_258[5] = (QList)0x0;
    local_258[6] = (QList)0x0;
    local_258[7] = (QList)0x0;
    local_258[8] = (QList)0x0;
    local_258[9] = (QList)0x0;
    local_258[10] = (QList)0x0;
    local_258[0xb] = (QList)0x0;
    local_258[0xc] = (QList)0x0;
    local_258[0xd] = (QList)0x0;
    local_258[0xe] = (QList)0x0;
    local_258[0xf] = (QList)0x0;
    local_248 = 0;
    local_370 = 0;
    local_238[0] = (QList<QVariant>)0x0;
    local_238[1] = (QList<QVariant>)0x0;
    local_238[2] = (QList<QVariant>)0x0;
    local_238[3] = (QList<QVariant>)0x0;
    local_238[4] = (QList<QVariant>)0x0;
    local_238[5] = (QList<QVariant>)0x0;
    local_238[6] = (QList<QVariant>)0x0;
    local_238[7] = (QList<QVariant>)0x0;
    local_238[8] = (QList<QVariant>)0x0;
    local_238[9] = (QList<QVariant>)0x0;
    local_238[10] = (QList<QVariant>)0x0;
    local_238[0xb] = (QList<QVariant>)0x0;
    local_238[0xc] = (QList<QVariant>)0x0;
    local_238[0xd] = (QList<QVariant>)0x0;
    local_238[0xe] = (QList<QVariant>)0x0;
    local_238[0xf] = (QList<QVariant>)0x0;
    local_228 = 0;
    local_218[0] = (QList<QVariant>)0x0;
    local_218[1] = (QList<QVariant>)0x0;
    local_218[2] = (QList<QVariant>)0x0;
    local_218[3] = (QList<QVariant>)0x0;
    local_218[4] = (QList<QVariant>)0x0;
    local_218[5] = (QList<QVariant>)0x0;
    local_218[6] = (QList<QVariant>)0x0;
    local_218[7] = (QList<QVariant>)0x0;
    local_218[8] = (QList<QVariant>)0x0;
    local_218[9] = (QList<QVariant>)0x0;
    local_218[10] = (QList<QVariant>)0x0;
    local_218[0xb] = (QList<QVariant>)0x0;
    local_218[0xc] = (QList<QVariant>)0x0;
    local_218[0xd] = (QList<QVariant>)0x0;
    local_218[0xe] = (QList<QVariant>)0x0;
    local_218[0xf] = (QList<QVariant>)0x0;
    local_208 = 0;
    local_1f8 = 0;
    local_1f0 = 0;
    local_1e8 = 0;
    local_d8 = &local_1f8;
    local_d0 = &local_370;
    local_c8 = local_238;
    local_c0 = local_218;
    local_b8 = local_258;
    if ((refreshDisplays()::outRe == '\0') &&
       (iVar3 = __cxa_guard_acquire(&refreshDisplays()::outRe), iVar3 != 0)) {
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_138,0);
      local_308 = &DAT_0029ec78;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,
                 L"^(\\S+) connected( primary)? (\\d+)x(\\d+)\\+",0x29);
      QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)&refreshDisplays()::outRe,local_f8,local_138[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,&refreshDisplays()::outRe,&__dso_handle);
      __cxa_guard_release(&refreshDisplays()::outRe);
      QString::~QString((QString *)local_f8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
    }
    if ((refreshDisplays()::modeRe == '\0') &&
       (iVar3 = __cxa_guard_acquire(&refreshDisplays()::modeRe), iVar3 != 0)) {
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_138,0);
      local_300 = &LAB_0029eccf_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,
                 L"^\\s+(\\d+x\\d+)\\s+(.*\\S)\\s*$",0x1a);
      QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)&refreshDisplays()::modeRe,local_f8,local_138[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,&refreshDisplays()::modeRe,&__dso_handle)
      ;
      __cxa_guard_release(&refreshDisplays()::modeRe);
      QString::~QString((QString *)local_f8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
    }
    if ((refreshDisplays()::ws == '\0') &&
       (iVar3 = __cxa_guard_acquire(&refreshDisplays()::ws), iVar3 != 0)) {
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_138,0);
      local_2f8 = &LAB_0029ed06;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"\\s+",3);
      QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)&refreshDisplays()::ws,local_f8,local_138[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,&refreshDisplays()::ws,&__dso_handle);
      __cxa_guard_release(&refreshDisplays()::ws);
      QString::~QString((QString *)local_f8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
    }
    QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_f8,0);
    QChar::QChar<char,true>((QChar *)local_118,'\n');
    QString::split(local_1d8,local_278,local_118[0],local_f8[0],1);
    local_338 = local_1d8;
    local_368 = QList<QString>::begin(local_338);
    local_360 = QList<QString>::end(local_338);
    while (cVar1 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_368,local_360), cVar1 != '\0') {
      local_330 = QList<QString>::const_iterator::operator*((const_iterator *)&local_368);
      QFlags<QRegularExpression::MatchOption>::QFlags
                ((QFlags<QRegularExpression::MatchOption> *)local_f8,0);
      QRegularExpression::match(local_358,&refreshDisplays()::outRe,local_330,0,0,local_f8[0]);
      cVar1 = QRegularExpressionMatch::hasMatch();
      if (cVar1 == '\0') {
        cVar1 = QString::isEmpty((QString *)&local_1f8);
        if (cVar1 == '\0') {
          QFlags<QRegularExpression::MatchOption>::QFlags
                    ((QFlags<QRegularExpression::MatchOption> *)local_f8,0);
          QRegularExpression::match(local_350,&refreshDisplays()::modeRe,local_330,0,0,local_f8[0]);
          cVar1 = QRegularExpressionMatch::hasMatch();
          if (cVar1 == '\x01') {
            QRegularExpressionMatch::captured((int)local_1b8);
            ::QVariant::QVariant((QVariant *)local_68,(QString *)local_1b8);
            QList<QVariant>::append(local_238,(QVariant *)local_68);
            ::QVariant::~QVariant((QVariant *)local_68);
            QRegularExpressionMatch::captured((int)local_198);
            QChar::QChar<char,true>((QChar *)local_f8,'*');
            cVar1 = QString::contains((QString *)local_198,(undefined2)local_f8[0],1);
            if (cVar1 != '\0') {
              ::QVariant::QVariant((QVariant *)local_68,(QString *)local_1b8);
              local_298 = &LAB_0029ed25_1;
              QArrayDataPointer<char16_t>::QArrayDataPointer
                        ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"sub",3);
              QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
              pQVar5 = (QVariant *)
                       QMap<QString,QVariant>::operator[]
                                 ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
              ::QVariant::operator=(pQVar5,(QVariant *)local_68);
              QString::~QString((QString *)local_f8);
              QArrayDataPointer<char16_t>::~QArrayDataPointer
                        ((QArrayDataPointer<char16_t> *)local_118);
              ::QVariant::~QVariant((QVariant *)local_68);
              local_178[0] = (QString)0x0;
              local_178[1] = (QString)0x0;
              local_178[2] = (QString)0x0;
              local_178[3] = (QString)0x0;
              local_178[4] = (QString)0x0;
              local_178[5] = (QString)0x0;
              local_178[6] = (QString)0x0;
              local_178[7] = (QString)0x0;
              local_178[8] = (QString)0x0;
              local_178[9] = (QString)0x0;
              local_178[10] = (QString)0x0;
              local_178[0xb] = (QString)0x0;
              local_178[0xc] = (QString)0x0;
              local_178[0xd] = (QString)0x0;
              local_178[0xe] = (QString)0x0;
              local_178[0xf] = (QString)0x0;
              local_168 = 0;
              QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_f8,1);
              QString::split(local_138,local_198,&refreshDisplays()::ws,local_f8[0]);
              local_328 = (QList<QString> *)local_138;
              local_348 = QList<QString>::begin(local_328);
              local_340 = QList<QString>::end(local_328);
              while (cVar1 = QList<QString>::iterator::operator!=((iterator *)&local_348,local_340),
                    cVar1 != '\0') {
                pQVar7 = (QString *)QList<QString>::iterator::operator*((iterator *)&local_348);
                QString::QString((QString *)local_158,pQVar7);
                QChar::QChar<char,true>((QChar *)local_f8,'*');
                QString::contains((QString *)local_158,(undefined2)local_f8[0],1);
                QChar::QChar<char,true>((QChar *)local_f8,'*');
                QString::remove(local_158,(undefined2)local_f8[0],1);
                QChar::QChar<char,true>((QChar *)local_f8,'+');
                QString::remove(local_158,(undefined2)local_f8[0],1);
                local_320 = QString::toDouble((bool *)local_158);
                QString::~QString((QString *)local_158);
                QList<QString>::iterator::operator++((iterator *)&local_348);
              }
              QList<QString>::~QList((QList<QString> *)local_138);
              QList<QVariant>::operator=(local_218,(QList *)local_178);
              QList<QVariant>::~QList((QList<QVariant> *)local_178);
            }
            QString::~QString((QString *)local_198);
            QString::~QString((QString *)local_1b8);
          }
          QRegularExpressionMatch::~QRegularExpressionMatch(local_350);
        }
      }
      else {
        refreshDisplays()::{lambda()#1}::operator()((_lambda___1_ *)&local_d8);
        QRegularExpressionMatch::captured((int)local_f8);
        QString::operator=((QString *)&local_1f8,(QString *)local_f8);
        QString::~QString((QString *)local_f8);
        QRegularExpressionMatch::captured((int)local_f8);
        iVar3 = QString::toInt((QString *)local_f8,(bool *)0x0,10);
        QString::~QString((QString *)local_f8);
        QRegularExpressionMatch::captured((int)local_f8);
        iVar4 = QString::toInt((QString *)local_f8,(bool *)0x0,10);
        QString::~QString((QString *)local_f8);
        ::QVariant::QVariant((QVariant *)local_68,(QString *)&local_1f8);
        local_2f0 = &LAB_0029ed0e;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"n",1);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::~QVariant((QVariant *)local_68);
        QRegularExpressionMatch::captured((int)local_f8);
        bVar2 = QString::isEmpty((QString *)local_f8);
        ::QVariant::QVariant((QVariant *)local_68,(bool)(bVar2 ^ 1));
        local_2e8 = &LAB_0029ed11_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,L"pri",3);
        QString::QString((QString *)local_118,(QArrayDataPointer *)local_138);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_118);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_118);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        local_2e0 = &LAB_0029ed16_4;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_158,(QTypedArrayData *)0x0,L"%1x%2",5);
        QString::QString((QString *)local_138,(QArrayDataPointer *)local_158);
        QChar::QChar<char16_t,true>((QChar *)&local_340,L' ');
        QString::arg<int,true>(local_118,local_138,iVar3,0,10,local_340 & 0xffff);
        QChar::QChar<char16_t,true>((QChar *)local_1b8,L' ');
        QString::arg<int,true>(local_f8,local_118,iVar4,0,10,local_1b8[0]);
        ::QVariant::QVariant((QVariant *)local_68,(QString *)local_f8);
        local_2d8 = &LAB_0029ed25_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_198,(QTypedArrayData *)0x0,L"sub",3);
        QString::QString(local_178,(QArrayDataPointer *)local_198);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_370,local_178);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString(local_178);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_198);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QString::~QString((QString *)local_118);
        QString::~QString((QString *)local_138);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_158);
        local_138[0] = iVar3 / 0xf;
        local_158[0] = 0x28;
        piVar6 = qMax<int>(local_158,local_138);
        ::QVariant::QVariant((QVariant *)local_68,*piVar6);
        local_2d0 = &DAT_0029ed2e;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"w",1);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::~QVariant((QVariant *)local_68);
        local_138[0] = iVar4 / 0xf;
        local_158[0] = 0x18;
        piVar6 = qMax<int>(local_158,local_138);
        ::QVariant::QVariant((QVariant *)local_68,*piVar6);
        local_2c8 = &DAT_0029ed32;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"h",1);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::~QVariant((QVariant *)local_68);
        ::QVariant::QVariant((QVariant *)local_68,0.0);
        local_2c0 = &DAT_0029ed36;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"hz",2);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::~QVariant((QVariant *)local_68);
        if ((refreshDisplays()::rotRe == '\0') &&
           (iVar3 = __cxa_guard_acquire(&refreshDisplays()::rotRe), iVar3 != 0)) {
          QFlags<QRegularExpression::PatternOption>::QFlags
                    ((QFlags<QRegularExpression::PatternOption> *)local_138,0);
          local_2b8 = &DAT_0029ed40;
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,
                     L"\\+\\d+\\+\\d+\\s+(normal|left|inverted|right)\\b",0x2b);
          QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
          QRegularExpression::QRegularExpression
                    ((QRegularExpression *)&refreshDisplays()::rotRe,local_f8,local_138[0]);
          __cxa_atexit(QRegularExpression::~QRegularExpression,&refreshDisplays()::rotRe,
                       &__dso_handle);
          __cxa_guard_release(&refreshDisplays()::rotRe);
          QString::~QString((QString *)local_f8);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        }
        QFlags<QRegularExpression::MatchOption>::QFlags
                  ((QFlags<QRegularExpression::MatchOption> *)local_f8,0);
        QRegularExpression::match(local_178,&refreshDisplays()::rotRe,local_330,0,0,local_f8[0]);
        cVar1 = QRegularExpressionMatch::hasMatch();
        if (cVar1 == '\0') {
          local_2b0 = &LAB_0029ed98;
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"normal",6);
          QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        }
        else {
          QRegularExpressionMatch::captured((int)local_f8);
        }
        ::QVariant::QVariant((QVariant *)local_68,(QString *)local_f8);
        local_2a8 = &LAB_0029eda5_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_158,(QTypedArrayData *)0x0,L"orient",6);
        QString::QString((QString *)local_138,(QArrayDataPointer *)local_158);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_138);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_138);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_158);
        ::QVariant::~QVariant((QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        if (cVar1 == '\0') {
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        }
        ::QVariant::QVariant(local_a8,100);
        QMap<QString,QVariant>::value(local_88,(QVariant *)(this + 0x30));
        iVar3 = ::QVariant::toInt((bool *)local_88);
        ::QVariant::QVariant((QVariant *)local_68,iVar3);
        local_2a0 = &LAB_0029edb4;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_118,(QTypedArrayData *)0x0,L"scale",5);
        QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
        pQVar5 = (QVariant *)
                 QMap<QString,QVariant>::operator[]
                           ((QMap<QString,QVariant> *)&local_370,(QString *)local_f8);
        ::QVariant::operator=(pQVar5,(QVariant *)local_68);
        QString::~QString((QString *)local_f8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_118);
        ::QVariant::~QVariant((QVariant *)local_68);
        ::QVariant::~QVariant((QVariant *)local_88);
        ::QVariant::~QVariant(local_a8);
        QRegularExpressionMatch::~QRegularExpressionMatch((QRegularExpressionMatch *)local_178);
      }
      QRegularExpressionMatch::~QRegularExpressionMatch(local_358);
      QList<QString>::const_iterator::operator++((const_iterator *)&local_368);
    }
    refreshDisplays()::{lambda()#1}::operator()((_lambda___1_ *)&local_d8);
    QList<QVariant>::operator=((QList<QVariant> *)(this + 0x18),local_258);
    displaysChanged(this);
    QList<QString>::~QList(local_1d8);
    QString::~QString((QString *)&local_1f8);
    QList<QVariant>::~QList(local_218);
    QList<QVariant>::~QList(local_238);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_370);
    QList<QVariant>::~QList((QList<QVariant> *)local_258);
    QString::~QString(local_278);
  }
  QProcess::~QProcess(local_288);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0018b7a8  Settings::applyDisplayMode(QString_const&,QString_const&,double)::{lambda()#1}::operator()

/* Settings::applyDisplayMode(QString const&, QString const&,
   double)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Settings::applyDisplayMode(QString_const&,QString_const&,double)::{lambda()#1}::operator()
          (_lambda___1_ *this)

{
  saveDisplay(*(Settings **)this);
  return;
}



// ==== 0018b7c6  Settings::applyDisplayMode

/* Settings::applyDisplayMode(QString const&, QString const&, double) */

void __thiscall
Settings::applyDisplayMode(Settings *this,QString *param_1,QString *param_2,double param_3)

{
  QList<QString> *pQVar1;
  long in_FS_OFFSET;
  QList<QString> local_b8 [16];
  undefined8 local_a8;
  QArrayDataPointer<char16_t> local_98 [32];
  QString local_78 [32];
  QArrayDataPointer<char16_t> local_58 [32];
  Settings *local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8[0] = (QList<QString>)0x0;
  local_b8[1] = (QList<QString>)0x0;
  local_b8[2] = (QList<QString>)0x0;
  local_b8[3] = (QList<QString>)0x0;
  local_b8[4] = (QList<QString>)0x0;
  local_b8[5] = (QList<QString>)0x0;
  local_b8[6] = (QList<QString>)0x0;
  local_b8[7] = (QList<QString>)0x0;
  local_b8[8] = (QList<QString>)0x0;
  local_b8[9] = (QList<QString>)0x0;
  local_b8[10] = (QList<QString>)0x0;
  local_b8[0xb] = (QList<QString>)0x0;
  local_b8[0xc] = (QList<QString>)0x0;
  local_b8[0xd] = (QList<QString>)0x0;
  local_b8[0xe] = (QList<QString>)0x0;
  local_b8[0xf] = (QList<QString>)0x0;
  local_a8 = 0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_98,(QTypedArrayData *)0x0,L"--output",8);
  QString::QString(local_78,(QArrayDataPointer *)local_98);
  pQVar1 = (QList<QString> *)QList<QString>::operator<<(local_b8,local_78);
  pQVar1 = (QList<QString> *)QList<QString>::operator<<(pQVar1,param_1);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"--mode",6);
  QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
  pQVar1 = (QList<QString> *)QList<QString>::operator<<(pQVar1,(QString *)local_38);
  QList<QString>::operator<<(pQVar1,param_2);
  QString::~QString((QString *)local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  QString::~QString(local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_98);
  if (0.0 < param_3) {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"--rate",6);
    QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
    pQVar1 = (QList<QString> *)QList<QString>::operator<<(local_b8,(QString *)local_58);
    QString::number(param_3,(char)local_38,0x66);
    QList<QString>::operator<<(pQVar1,(QString *)local_38);
    QString::~QString((QString *)local_38);
    QString::~QString((QString *)local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
  }
  QString::QString((QString *)local_38);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"xrandr",6);
  QString::QString((QString *)local_58,(QArrayDataPointer *)local_78);
  QProcess::startDetached((QString *)local_58,(QList *)local_b8,(QString *)local_38,(longlong *)0x0)
  ;
  QString::~QString((QString *)local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
  QString::~QString((QString *)local_38);
  local_38[0] = this;
  QTimer::
  singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::_lambda()_1_>
            (900,(ContextType *)this,(_lambda___1_ *)local_38);
  QList<QString>::~QList(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018bb7e  Settings::applyDisplayOrientation(QString_const&,QString_const&)::{lambda()#1}::operator()

/* Settings::applyDisplayOrientation(QString const&, QString
   const&)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Settings::applyDisplayOrientation(QString_const&,QString_const&)::{lambda()#1}::operator()
          (_lambda___1_ *this)

{
  saveDisplay(*(Settings **)this);
  return;
}



// ==== 0018bb9c  Settings::applyDisplayOrientation

/* Settings::applyDisplayOrientation(QString const&, QString const&) */

void __thiscall Settings::applyDisplayOrientation(Settings *this,QString *param_1,QString *param_2)

{
  char cVar1;
  QString *this_00;
  long in_FS_OFFSET;
  QString local_188 [32];
  QArrayDataPointer<char16_t> local_168 [32];
  QString local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  Settings *local_c8 [4];
  QString local_a8 [24];
  QString aQStack_90 [24];
  QString aQStack_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"normal",6);
  QString::QString(local_188,(QArrayDataPointer *)local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Portrait",8);
  QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
  cVar1 = QString::startsWith(param_2,local_c8,1);
  QString::~QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  if (cVar1 == '\0') {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Inverted",8);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    cVar1 = QString::startsWith(param_2,local_c8,1);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    if (cVar1 == '\0') {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"Port",4);
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
      cVar1 = QString::startsWith(param_2,local_c8,1);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      if (cVar1 != '\0') {
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"right",5);
        QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
        QString::operator=(local_188,(QString *)local_c8);
        QString::~QString((QString *)local_c8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      }
    }
    else {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"inverted",8);
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
      QString::operator=(local_188,(QString *)local_c8);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    }
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"left",4);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    QString::operator=(local_188,(QString *)local_c8);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  }
  QString::QString((QString *)local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"--output",8);
  QString::QString(local_a8,(QArrayDataPointer *)local_128);
  QString::QString(aQStack_90,param_1);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"--rotate",8);
  QString::QString(aQStack_78,(QArrayDataPointer *)local_108);
  QString::QString(local_60,local_188);
  QList<QString>::QList(local_e8,local_a8,4);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"xrandr",6);
  QString::QString(local_148,(QArrayDataPointer *)local_168);
  QProcess::startDetached(local_148,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
  QString::~QString(local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  QList<QString>::~QList((QList<QString> *)local_e8);
  this_00 = aQStack_48;
  while (this_00 != local_a8) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  QString::~QString((QString *)local_c8);
  local_c8[0] = this;
  QTimer::
  singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::_lambda()_1_>
            (900,(ContextType *)this,(_lambda___1_ *)local_c8);
  QString::~QString(local_188);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018c31a  Settings::applyDisplayScale(QString_const&,int)::{lambda()#1}::operator()

/* Settings::applyDisplayScale(QString const&, int)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const
    */

void __thiscall
Settings::applyDisplayScale(QString_const&,int)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  saveDisplay(*(Settings **)this);
  return;
}



// ==== 0018c338  Settings::applyDisplayScale

/* Settings::applyDisplayScale(QString const&, int) */

void __thiscall Settings::applyDisplayScale(Settings *this,QString *param_1,int param_2)

{
  QVariant *this_00;
  QString *this_01;
  long in_FS_OFFSET;
  undefined2 local_1d2;
  double local_1d0;
  wchar16 *local_1c8;
  wchar16 *local_1c0;
  undefined *local_1b8;
  wchar16 *local_1b0;
  QArrayDataPointer<char16_t> local_1a8 [32];
  QString local_188 [32];
  QArrayDataPointer<char16_t> local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  QArrayDataPointer<char16_t> local_128 [32];
  QString local_108 [32];
  QList local_e8 [32];
  Settings *local_c8 [4];
  QVariant local_a8 [24];
  QString local_90 [24];
  QString aQStack_78 [24];
  undefined1 auStack_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  ::QVariant::QVariant(local_a8,param_2);
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)(this + 0x30),param_1);
  ::QVariant::operator=(this_00,local_a8);
  ::QVariant::~QVariant(local_a8);
  if (param_2 < 1) {
    local_1d0 = 1.0;
  }
  else {
    local_1d0 = 100.0 / (double)param_2;
  }
  QString::QString((QString *)local_c8);
  local_1b8 = &DAT_0029edc0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"--output",8);
  QString::QString((QString *)local_a8,(QArrayDataPointer *)local_168);
  QString::QString(local_90,param_1);
  local_1c0 = L"--scale";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"--scale",7);
  QString::QString(aQStack_78,(QArrayDataPointer *)local_148);
  local_1c8 = L"%1x%1";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_128,(QTypedArrayData *)0x0,L"%1x%1",5);
  QString::QString(local_108,(QArrayDataPointer *)local_128);
  QChar::QChar<char16_t,true>((QChar *)&local_1d2,L' ');
  QString::arg<double,true>(local_1d0,auStack_60,local_108,0,0x66,4,local_1d2);
  QList<QString>::QList(local_e8,local_a8,4);
  local_1b0 = L"xrandr";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_1a8,(QTypedArrayData *)0x0,L"xrandr",6);
  QString::QString(local_188,(QArrayDataPointer *)local_1a8);
  QProcess::startDetached(local_188,local_e8,(QString *)local_c8,(longlong *)0x0);
  QString::~QString(local_188);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1a8);
  QList<QString>::~QList((QList<QString> *)local_e8);
  this_01 = aQStack_48;
  while (this_01 != (QString *)local_a8) {
    this_01 = this_01 + -0x18;
    QString::~QString(this_01);
  }
  QString::~QString(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  QString::~QString((QString *)local_c8);
  local_c8[0] = this;
  QTimer::singleShot<int,Settings::applyDisplayScale(QString_const&,int)::_lambda()_1_>
            (900,(ContextType *)this,(_lambda___1_ *)local_c8);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018c82a  Settings::saveDisplay

/* Settings::saveDisplay() */

void __thiscall Settings::saveDisplay(Settings *this)

{
  char cVar1;
  QVariant *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_1b0;
  undefined8 local_1a8;
  QVariant local_1a0 [8];
  undefined8 local_198;
  QList<QVariant> *local_190;
  undefined8 local_188;
  undefined1 *local_180;
  undefined1 *local_178;
  undefined1 *local_170;
  wchar16 *local_168;
  undefined *local_160;
  undefined *local_158;
  undefined1 *local_150;
  undefined1 *local_148;
  undefined1 *local_140;
  undefined1 *local_138;
  wchar16 *local_130;
  wchar16 *local_128;
  undefined *local_120;
  undefined1 *local_118;
  undefined1 *local_110;
  QList<QVariant> local_108 [16];
  undefined8 local_f8;
  QArrayDataPointer<char16_t> local_e8 [32];
  undefined8 local_c8 [4];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  refreshDisplays(this);
  local_108[0] = (QList<QVariant>)0x0;
  local_108[1] = (QList<QVariant>)0x0;
  local_108[2] = (QList<QVariant>)0x0;
  local_108[3] = (QList<QVariant>)0x0;
  local_108[4] = (QList<QVariant>)0x0;
  local_108[5] = (QList<QVariant>)0x0;
  local_108[6] = (QList<QVariant>)0x0;
  local_108[7] = (QList<QVariant>)0x0;
  local_108[8] = (QList<QVariant>)0x0;
  local_108[9] = (QList<QVariant>)0x0;
  local_108[10] = (QList<QVariant>)0x0;
  local_108[0xb] = (QList<QVariant>)0x0;
  local_108[0xc] = (QList<QVariant>)0x0;
  local_108[0xd] = (QList<QVariant>)0x0;
  local_108[0xe] = (QList<QVariant>)0x0;
  local_108[0xf] = (QList<QVariant>)0x0;
  local_f8 = 0;
  local_190 = (QList<QVariant> *)(this + 0x18);
  local_1b0 = QList<QVariant>::begin(local_190);
  local_1a8 = QList<QVariant>::end(local_190);
  while( true ) {
    cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_1b0,local_1a8);
    if (cVar1 == '\0') break;
    local_188 = QList<QVariant>::iterator::operator*((iterator *)&local_1b0);
    ::QVariant::toMap();
    local_198 = 0;
    ::QVariant::QVariant(local_68);
    local_180 = &LAB_0029ed0e;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"n",1);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_1a0);
    local_178 = &LAB_0029ed0e;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"n",1);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_198,(QString *)local_c8);
    ::QVariant::operator=(pQVar2,(QVariant *)local_48);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_170 = &LAB_0029ed25_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"sub",3);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_1a0);
    local_168 = L"mode";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"mode",4);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_198,(QString *)local_c8);
    ::QVariant::operator=(pQVar2,(QVariant *)local_48);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_160 = &DAT_0029ed36;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"hz",2);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_1a0);
    local_158 = &DAT_0029ed36;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"hz",2);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_198,(QString *)local_c8);
    ::QVariant::operator=(pQVar2,(QVariant *)local_48);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_150 = &LAB_0029eda5_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"orient",6);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_1a0);
    local_148 = &LAB_0029eda5_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"orient",6);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_198,(QString *)local_c8);
    ::QVariant::operator=(pQVar2,(QVariant *)local_48);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_140 = &LAB_0029edb4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"scale",5);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_1a0);
    local_138 = &LAB_0029edb4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"scale",5);
    QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
    pQVar2 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_198,(QString *)local_c8);
    ::QVariant::operator=(pQVar2,(QVariant *)local_48);
    QString::~QString((QString *)local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant((QVariant *)local_48,(QMap *)&local_198);
    QList<QVariant>::append(local_108,(QVariant *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_198);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_1a0);
    QList<QVariant>::iterator::operator++((iterator *)&local_1b0);
  }
  local_c8[0] = 0;
  ::QVariant::QVariant((QVariant *)local_48,(QList *)local_108);
  local_130 = L"outputs";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"outputs",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_c8,local_88);
  ::QVariant::operator=(pQVar2,(QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,(bool)this[0x38]);
  local_128 = L"nightLightOn";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"nightLightOn",0xc);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_c8,local_88);
  ::QVariant::operator=(pQVar2,(QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,*(int *)(this + 0x3c));
  local_120 = &DAT_0029eea6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"nightWarmth",0xb)
  ;
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_c8,local_88);
  ::QVariant::operator=(pQVar2,(QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant((QVariant *)local_48);
  ::QVariant::QVariant((QVariant *)local_48,(bool)this[0x39]);
  local_118 = &LAB_0029eebd_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"nightLightAuto",0xe);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  pQVar2 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)local_c8,local_88);
  ::QVariant::operator=(pQVar2,(QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant((QVariant *)local_48);
  local_110 = &LAB_0029eedb_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"display",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::writeConfig(local_88,(QMap *)local_c8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
  QList<QVariant>::~QList(local_108);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0018d5e0  Settings::loadDisplay

/* Settings::loadDisplay() */

void __thiscall Settings::loadDisplay(Settings *this)

{
  bool bVar1;
  char cVar2;
  Settings SVar3;
  undefined4 uVar4;
  QList<QString> *pQVar5;
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined2 local_276;
  int local_274;
  QString local_270 [8];
  undefined8 local_268;
  undefined8 local_260;
  QVariant local_258 [8];
  QList<QVariant> *local_250;
  undefined8 local_248;
  double local_240;
  double local_238;
  undefined1 *local_230;
  wchar16 *local_228;
  undefined1 *local_220;
  wchar16 *local_218;
  undefined *local_210;
  undefined *local_208;
  undefined1 *local_200;
  undefined1 *local_1f8;
  undefined1 *local_1f0;
  undefined1 *local_1e8;
  undefined1 *local_1e0;
  wchar16 *local_1d8;
  wchar16 *local_1d0;
  wchar16 *local_1c8;
  wchar16 *local_1c0;
  undefined *local_1b8;
  undefined1 *local_1b0;
  QList<QVariant> local_1a8 [32];
  QString local_188 [32];
  QString local_168 [32];
  QList<QString> local_148 [16];
  undefined8 local_138;
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  undefined2 local_88 [16];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_230 = &LAB_0029eedb_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"display",7);
  QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_270);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::QVariant(local_68);
  local_228 = L"outputs";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"outputs",7);
  QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_270);
  ::QVariant::toList();
  local_250 = local_1a8;
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  local_268 = QList<QVariant>::begin(local_250);
  local_260 = QList<QVariant>::end(local_250);
  do {
    cVar2 = QList<QVariant>::iterator::operator!=((iterator *)&local_268,local_260);
    if (cVar2 == '\0') {
      QList<QVariant>::~QList(local_1a8);
      ::QVariant::QVariant(local_68,(bool)this[0x38]);
      local_1c0 = L"nightLightOn";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_a8,(QTypedArrayData *)0x0,L"nightLightOn",0xc);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_270);
      SVar3 = (Settings)::QVariant::toBool();
      this[0x38] = SVar3;
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      ::QVariant::QVariant(local_68,*(int *)(this + 0x3c));
      local_1b8 = &DAT_0029eea6;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_a8,(QTypedArrayData *)0x0,L"nightWarmth",0xb);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_270);
      uVar4 = ::QVariant::toInt((bool *)local_48);
      *(undefined4 *)(this + 0x3c) = uVar4;
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      ::QVariant::QVariant(local_68,(bool)this[0x39]);
      local_1b0 = &LAB_0029eebd_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_a8,(QTypedArrayData *)0x0,L"nightLightAuto",0xe);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_270);
      SVar3 = (Settings)::QVariant::toBool();
      this[0x39] = SVar3;
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      if (this[0x38] != (Settings)0x0) {
        applyNightLight(this);
      }
      refreshDisplays(this);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_270);
      if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_248 = QList<QVariant>::iterator::operator*((iterator *)&local_268);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_68);
    local_220 = &LAB_0029ed0e;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"n",1);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_258);
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_218 = L"mode";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"mode",4);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_258);
    ::QVariant::toString();
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68);
    local_210 = &DAT_0029ed36;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"hz",2);
    QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_258);
    local_240 = (double)::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    cVar2 = QString::isEmpty(local_188);
    if (cVar2 == '\0') {
      QLatin1Char::QLatin1Char((QLatin1Char *)local_a8,'x');
      QChar::QChar<QLatin1Char,true>((QChar *)local_88,local_a8[0]);
      cVar2 = QString::contains(local_168,local_88[0],1);
      if (cVar2 != '\x01') goto LAB_0018da19;
      bVar1 = false;
    }
    else {
LAB_0018da19:
      bVar1 = true;
    }
    if (!bVar1) {
      local_148[0] = (QList<QString>)0x0;
      local_148[1] = (QList<QString>)0x0;
      local_148[2] = (QList<QString>)0x0;
      local_148[3] = (QList<QString>)0x0;
      local_148[4] = (QList<QString>)0x0;
      local_148[5] = (QList<QString>)0x0;
      local_148[6] = (QList<QString>)0x0;
      local_148[7] = (QList<QString>)0x0;
      local_148[8] = (QList<QString>)0x0;
      local_148[9] = (QList<QString>)0x0;
      local_148[10] = (QList<QString>)0x0;
      local_148[0xb] = (QList<QString>)0x0;
      local_148[0xc] = (QList<QString>)0x0;
      local_148[0xd] = (QList<QString>)0x0;
      local_148[0xe] = (QList<QString>)0x0;
      local_148[0xf] = (QList<QString>)0x0;
      local_138 = 0;
      local_208 = &DAT_0029edc0;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"--output",8);
      QString::QString(local_c8,(QArrayDataPointer *)local_e8);
      pQVar5 = (QList<QString> *)QList<QString>::operator<<(local_148,local_c8);
      pQVar5 = (QList<QString> *)QList<QString>::operator<<(pQVar5,local_188);
      local_200 = &LAB_0029edd2;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"--mode",6);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      pQVar5 = (QList<QString> *)QList<QString>::operator<<(pQVar5,(QString *)local_88);
      QList<QString>::operator<<(pQVar5,local_168);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      QString::~QString(local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      if (0.0 < local_240) {
        local_1f8 = &LAB_0029ede0;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"--rate",6);
        QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
        pQVar5 = (QList<QString> *)QList<QString>::operator<<(local_148,(QString *)local_a8);
        QString::number(local_240,(char)local_88,0x66);
        QList<QString>::operator<<(pQVar5,(QString *)local_88);
        QString::~QString((QString *)local_88);
        QString::~QString((QString *)local_a8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      }
      ::QVariant::QVariant(local_68);
      local_1f0 = &LAB_0029eda5_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"orient",6);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,local_258);
      ::QVariant::toString();
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      cVar2 = QString::isEmpty(local_128);
      if (cVar2 != '\x01') {
        local_1e8 = &LAB_0029ee43_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  (local_a8,(QTypedArrayData *)0x0,L"--rotate",8);
        QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
        pQVar5 = (QList<QString> *)QList<QString>::operator<<(local_148,(QString *)local_88);
        QList<QString>::operator<<(pQVar5,local_128);
        QString::~QString((QString *)local_88);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      }
      ::QVariant::QVariant(local_68,100);
      local_1e0 = &LAB_0029edb4;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"scale",5);
      QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
      QMap<QString,QVariant>::value(local_48,local_258);
      local_274 = ::QVariant::toInt((bool *)local_48);
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_68);
      if ((0 < local_274) && (local_274 != 100)) {
        ::QVariant::QVariant((QVariant *)local_48,local_274);
        this_00 = (QVariant *)
                  QMap<QString,QVariant>::operator[]
                            ((QMap<QString,QVariant> *)(this + 0x30),local_188);
        ::QVariant::operator=(this_00,(QVariant *)local_48);
        ::QVariant::~QVariant((QVariant *)local_48);
        local_238 = 100.0 / (double)local_274;
        local_1d8 = L"--scale";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  (local_108,(QTypedArrayData *)0x0,L"--scale",7);
        QString::QString((QString *)local_e8,(QArrayDataPointer *)local_108);
        pQVar5 = (QList<QString> *)QList<QString>::operator<<(local_148,(QString *)local_e8);
        local_1d0 = L"%1x%1";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"%1x%1",5);
        QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
        QChar::QChar<char16_t,true>((QChar *)&local_276,L' ');
        QString::arg<double,true>(local_238,local_88,local_a8,0,0x66,4,local_276);
        QList<QString>::operator<<(pQVar5,(QString *)local_88);
        QString::~QString((QString *)local_88);
        QString::~QString((QString *)local_a8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
        QString::~QString((QString *)local_e8);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
      }
      QString::QString((QString *)local_88);
      local_1c8 = L"xrandr";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"xrandr",6);
      QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
      QProcess::startDetached
                ((QString *)local_a8,(QList *)local_148,(QString *)local_88,(longlong *)0x0);
      QString::~QString((QString *)local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      QString::~QString((QString *)local_88);
      QString::~QString(local_128);
      QList<QString>::~QList(local_148);
    }
    QString::~QString(local_168);
    QString::~QString(local_188);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_258);
    QList<QVariant>::iterator::operator++((iterator *)&local_268);
  } while( true );
}



// ==== 0018e85a  Settings::loadPower

/* Settings::loadPower() */

void __thiscall Settings::loadPower(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_110 [8];
  undefined1 *local_108;
  wchar16 *local_100;
  wchar16 *local_f8;
  wchar16 *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_108 = &LAB_0029eeec;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"power",5);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_110);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_110);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,*(int *)(this + 0x40));
    local_100 = L"batBlank";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"batBlank",8);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x40) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x44));
    local_f8 = L"batSuspend";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"batSuspend",10)
    ;
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x44) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x48));
    local_f0 = L"acBlank";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"acBlank",7);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x48) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x4c));
    local_e8 = L"acSuspend";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"acSuspend",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x4c) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x50));
    local_e0 = L"lidAction";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"lidAction",9);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x50),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x68));
    local_d8 = L"powerButtonAction";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"powerButtonAction",0x11);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x68),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x80]);
    local_d0 = L"showBatteryPct";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"showBatteryPct",0xe);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_110);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x80] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    powerChanged(this);
    applyPowerSettings(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_110);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0018f14e  Settings::applyPowerSettings

/* Settings::applyPowerSettings() */

void __thiscall Settings::applyPowerSettings(Settings *this)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  QString *pQVar4;
  long in_FS_OFFSET;
  int local_1ac;
  QArrayDataPointer<char16_t> local_168 [32];
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QList local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [24];
  QString local_90 [24];
  QString aQStack_78 [24];
  undefined1 local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0xb0) == 0) ||
     (cVar2 = Lelan::onBattery(*(Lelan **)(this + 0xb0)), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    iVar3 = *(int *)(this + 0x40);
    local_1ac = *(int *)(this + 0x44);
  }
  else {
    iVar3 = *(int *)(this + 0x48);
    local_1ac = *(int *)(this + 0x4c);
  }
  iVar3 = iVar3 * 0x3c;
  QString::QString(local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"dpms",4);
  QString::QString(local_a8,(QArrayDataPointer *)local_108);
  QString::number((int)local_90,iVar3);
  QString::number((int)aQStack_78,iVar3);
  QString::number((int)local_60,iVar3);
  QList<QString>::QList(local_e8,local_a8,4);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"xset",4);
  QString::QString(local_128,(QArrayDataPointer *)local_148);
  QProcess::startDetached(local_128,local_e8,local_c8,(longlong *)0x0);
  QString::~QString(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_48;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QString::~QString(local_c8);
  QString::QString(local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"s",1);
  QString::QString(local_a8,(QArrayDataPointer *)local_108);
  QString::number((int)local_90,local_1ac * 0x3c);
  QList<QString>::QList(local_e8,local_a8,2);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"xset",4);
  QString::QString(local_128,(QArrayDataPointer *)local_148);
  QProcess::startDetached(local_128,local_e8,local_c8,(longlong *)0x0);
  QString::~QString(local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_78;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QString::~QString(local_c8);
  QString::QString(local_c8);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"s",1);
  QString::QString(local_a8,(QArrayDataPointer *)local_128);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_108,(QTypedArrayData *)0x0,L"noblank",7);
  QString::QString(local_90,(QArrayDataPointer *)local_108);
  QList<QString>::QList(local_e8,local_a8,2);
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_168,(QTypedArrayData *)0x0,L"xset",4);
  QString::QString((QString *)local_148,(QArrayDataPointer *)local_168);
  QProcess::startDetached((QString *)local_148,local_e8,local_c8,(longlong *)0x0);
  QString::~QString((QString *)local_148);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_168);
  QList<QString>::~QList((QList<QString> *)local_e8);
  pQVar4 = aQStack_78;
  while (pQVar4 != local_a8) {
    pQVar4 = pQVar4 + -0x18;
    QString::~QString(pQVar4);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  QString::~QString(local_c8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0018fa38  Settings::savePower

/* Settings::savePower() */

void __thiscall Settings::savePower(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_d0;
  wchar16 *local_c8;
  wchar16 *local_c0;
  wchar16 *local_b8;
  wchar16 *local_b0;
  wchar16 *local_a8;
  wchar16 *local_a0;
  wchar16 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_d0 = 0;
  ::QVariant::QVariant(local_48,*(int *)(this + 0x40));
  local_c8 = L"batBlank";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"batBlank",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x44));
  local_c0 = L"batSuspend";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"batSuspend",10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x48));
  local_b8 = L"acBlank";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"acBlank",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x4c));
  local_b0 = L"acSuspend";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"acSuspend",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x50));
  local_a8 = L"lidAction";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"lidAction",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x68));
  local_a0 = L"powerButtonAction";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"powerButtonAction",0x11);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  applyPowerSettings(this);
  ::QVariant::QVariant(local_48,(bool)this[0x80]);
  local_98 = L"showBatteryPct";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"showBatteryPct",0xe);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029eeec;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"power",5);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_d0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_d0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00190104  Settings::applyFontSettings

/* Settings::applyFontSettings() */

void __thiscall Settings::applyFontSettings(Settings *this)

{
  fontChanged(this);
  return;
}



// ==== 00190120  Settings::saveFontSettings

/* Settings::saveFontSettings() */

void __thiscall Settings::saveFontSettings(Settings *this)

{
  saveFontsJson(this);
  return;
}



// ==== 0019013c  Settings::saveTextColor

/* Settings::saveTextColor() */

void __thiscall Settings::saveTextColor(Settings *this)

{
  saveFontsJson(this);
  return;
}



// ==== 00190158  Settings::loadStorage

/* Settings::loadStorage() */

void __thiscall Settings::loadStorage(Settings *this)

{
  char cVar1;
  Settings SVar2;
  long in_FS_OFFSET;
  QString local_c0 [8];
  wchar16 *local_b8;
  wchar16 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = L"storage";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"storage",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_c0);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_c0);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,(bool)this[0x81]);
    local_b0 = L"autoMountUsb";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"autoMountUsb",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_c0);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x81] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    storageChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c0);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001903ca  Settings::saveStorage

/* Settings::saveStorage() */

void __thiscall Settings::saveStorage(Settings *this)

{
  QVariant *this_00;
  long in_FS_OFFSET;
  undefined8 local_a0;
  wchar16 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a0 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x81]);
  local_98 = L"autoMountUsb";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"autoMountUsb",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  this_00 = (QVariant *)
            QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a0,local_68);
  ::QVariant::operator=(this_00,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"storage";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"storage",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_a0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_a0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001905aa  Settings::loadFonts()::{lambda(char_const*,QString&)#1}::operator()

/* Settings::loadFonts()::{lambda(char const*, QString&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*,
   QString&) const */

void __thiscall
Settings::loadFonts()::{lambda(char_const*,QString&)#1}::operator()
          (_lambda_char_const__QString___1_ *this,char *param_1,QString *param_2)

{
  QMap<QString,QVariant> *this_00;
  QVariant *pQVar1;
  char cVar2;
  long in_FS_OFFSET;
  QString local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QMap<QString,QVariant> **)this;
  QString::QString(local_88,param_1);
  cVar2 = QMap<QString,QVariant>::contains(this_00,local_88);
  QString::~QString(local_88);
  if (cVar2 != '\0') {
    pQVar1 = *(QVariant **)this;
    ::QVariant::QVariant(local_68);
    QString::QString(local_a8,param_1);
    QMap<QString,QVariant>::value(local_48,pQVar1);
    ::QVariant::toString();
    QString::operator=(param_2,local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_a8);
    ::QVariant::~QVariant(local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00190766  Settings::loadFonts()::{lambda(char_const*,int&)#1}::operator()

/* Settings::loadFonts()::{lambda(char const*, int&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*, int&)
   const */

void __thiscall
Settings::loadFonts()::{lambda(char_const*,int&)#1}::operator()
          (_lambda_char_const__int___1_ *this,char *param_1,int *param_2)

{
  QMap<QString,QVariant> *this_00;
  QVariant *pQVar1;
  char cVar2;
  int iVar3;
  long in_FS_OFFSET;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QMap<QString,QVariant> **)this;
  QString::QString(local_88,param_1);
  cVar2 = QMap<QString,QVariant>::contains(this_00,local_88);
  QString::~QString(local_88);
  if (cVar2 != '\0') {
    pQVar1 = *(QVariant **)this;
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,param_1);
    QMap<QString,QVariant>::value(local_48,pQVar1);
    iVar3 = ::QVariant::toInt((bool *)local_48);
    *param_2 = iVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001908f8  Settings::loadFonts()::{lambda(char_const*,bool&)#1}::operator()

/* Settings::loadFonts()::{lambda(char const*, bool&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*,
   bool&) const */

void __thiscall
Settings::loadFonts()::{lambda(char_const*,bool&)#1}::operator()
          (_lambda_char_const__bool___1_ *this,char *param_1,bool *param_2)

{
  QMap<QString,QVariant> *this_00;
  QVariant *pQVar1;
  char cVar2;
  bool bVar3;
  long in_FS_OFFSET;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QMap<QString,QVariant> **)this;
  QString::QString(local_88,param_1);
  cVar2 = QMap<QString,QVariant>::contains(this_00,local_88);
  QString::~QString(local_88);
  if (cVar2 != '\0') {
    pQVar1 = *(QVariant **)this;
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,param_1);
    QMap<QString,QVariant>::value(local_48,pQVar1);
    bVar3 = (bool)::QVariant::toBool();
    *param_2 = bVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00190a84  Settings::loadFonts()::{lambda(char_const*,double&)#1}::operator()

/* Settings::loadFonts()::{lambda(char const*, double&)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*,
   double&) const */

void __thiscall
Settings::loadFonts()::{lambda(char_const*,double&)#1}::operator()
          (_lambda_char_const__double___1_ *this,char *param_1,double *param_2)

{
  QMap<QString,QVariant> *this_00;
  QVariant *pQVar1;
  char cVar2;
  long in_FS_OFFSET;
  double dVar3;
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = *(QMap<QString,QVariant> **)this;
  QString::QString(local_88,param_1);
  cVar2 = QMap<QString,QVariant>::contains(this_00,local_88);
  QString::~QString(local_88);
  if (cVar2 != '\0') {
    pQVar1 = *(QVariant **)this;
    ::QVariant::QVariant(local_68);
    QString::QString(local_88,param_1);
    QMap<QString,QVariant>::value(local_48,pQVar1);
    dVar3 = (double)::QVariant::toDouble((bool *)local_48);
    *param_2 = dVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    ::QVariant::~QVariant(local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00190c1c  Settings::loadFonts

/* Settings::loadFonts() */

void __thiscall Settings::loadFonts(Settings *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_78 [8];
  QString *local_70;
  QString *local_68;
  wchar16 *local_60;
  QString *local_58 [4];
  QString *local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_60 = L"fonts";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,L"fonts",5);
  QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
  Lelan::readConfig(local_78);
  QString::~QString((QString *)local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_58);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_78);
  if (cVar1 == '\0') {
    local_70 = local_78;
    local_68 = local_78;
    local_58[0] = local_78;
    local_38[0] = local_78;
    loadFonts()::{lambda(char_const*,QString&)#1}::operator()
              ((_lambda_char_const__QString___1_ *)&local_70,"fontFamily",(QString *)(this + 0x2b0))
    ;
    loadFonts()::{lambda(char_const*,int&)#1}::operator()
              ((_lambda_char_const__int___1_ *)&local_68,"fontWeight",(int *)(this + 0x42c));
    loadFonts()::{lambda(char_const*,bool&)#1}::operator()
              ((_lambda_char_const__bool___1_ *)local_58,"fontItalic",(bool *)(this + 0x430));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"fontSizeScale",(double *)(this + 0x438))
    ;
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"letterSpacing",(double *)(this + 0x440))
    ;
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"lineHeight",(double *)(this + 0x448));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"uiScale",(double *)(this + 0x450));
    loadFonts()::{lambda(char_const*,QString&)#1}::operator()
              ((_lambda_char_const__QString___1_ *)&local_70,"textColor",(QString *)(this + 0x458));
    loadFonts()::{lambda(char_const*,bool&)#1}::operator()
              ((_lambda_char_const__bool___1_ *)local_58,"textOutlineEnabled",(bool *)(this + 0x470)
              );
    loadFonts()::{lambda(char_const*,QString&)#1}::operator()
              ((_lambda_char_const__QString___1_ *)&local_70,"textOutlineColor",
               (QString *)(this + 0x478));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"textOutlineWidth",
               (double *)(this + 0x490));
    loadFonts()::{lambda(char_const*,bool&)#1}::operator()
              ((_lambda_char_const__bool___1_ *)local_58,"textShadowEnabled",(bool *)(this + 0x498))
    ;
    loadFonts()::{lambda(char_const*,QString&)#1}::operator()
              ((_lambda_char_const__QString___1_ *)&local_70,"textShadowColor",
               (QString *)(this + 0x4a0));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"textShadowOffsetX",
               (double *)(this + 0x4b8));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"textShadowOffsetY",
               (double *)(this + 0x4c0));
    loadFonts()::{lambda(char_const*,double&)#1}::operator()
              ((_lambda_char_const__double___1_ *)local_38,"textShadowRadius",
               (double *)(this + 0x4c8));
    fontChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_78);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00190f8a  Settings::loadInput

/* Settings::loadInput() */

void __thiscall Settings::loadInput(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_f8 [8];
  undefined1 *local_f0;
  undefined1 *local_e8;
  undefined1 *local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  undefined1 *local_c8;
  wchar16 *local_c0;
  undefined *local_b8;
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = &LAB_0029f0cf_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"input",5);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,*(int *)(this + 0x84));
    local_e8 = &LAB_0029f0dc;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"kbRepeatDelay",0xd);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x84) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x88));
    local_e0 = &LAB_0029f0f8;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"kbRepeatRate",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x88) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x8c));
    local_d8 = &LAB_0029f111_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"pointerSpeed",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x8c) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x90));
    local_d0 = &LAB_0029f12b_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"touchpadSpeed",0xd);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x90) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x98]);
    local_c8 = &LAB_0029f147_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"naturalScroll",0xd);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x98] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x99]);
    local_c0 = L"tapToClick";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"tapToClick",10)
    ;
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x99] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x9a]);
    local_b8 = &DAT_0029f180;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"disableWhileTyping",0x12);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x9a] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x94));
    local_b0 = &LAB_0029f1a6;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"cursorSize",10)
    ;
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x94) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    inputChanged(this);
  }
  applyInput(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00191946  Settings::saveInput

/* Settings::saveInput() */

void __thiscall Settings::saveInput(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_d8;
  undefined1 *local_d0;
  undefined1 *local_c8;
  undefined1 *local_c0;
  undefined1 *local_b8;
  undefined1 *local_b0;
  wchar16 *local_a8;
  undefined *local_a0;
  undefined1 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_d8 = 0;
  ::QVariant::QVariant(local_48,*(int *)(this + 0x84));
  local_d0 = &LAB_0029f0dc;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"kbRepeatDelay",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x88));
  local_c8 = &LAB_0029f0f8;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"kbRepeatRate",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x8c));
  local_c0 = &LAB_0029f111_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"pointerSpeed",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x90));
  local_b8 = &LAB_0029f12b_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"touchpadSpeed",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x98]);
  local_b0 = &LAB_0029f147_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"naturalScroll",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x99]);
  local_a8 = L"tapToClick";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"tapToClick",10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x9a]);
  local_a0 = &DAT_0029f180;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"disableWhileTyping",0x12);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x94));
  local_98 = &LAB_0029f1a6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"cursorSize",10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_d8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029f0cf_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"input",5);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_d8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  applyInput(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001920fa  Settings::loadAccessibility

/* Settings::loadAccessibility() */

void __thiscall Settings::loadAccessibility(Settings *this)

{
  char cVar1;
  Settings SVar2;
  long in_FS_OFFSET;
  undefined8 uVar3;
  QString local_d8 [8];
  undefined1 *local_d0;
  wchar16 *local_c8;
  wchar16 *local_c0;
  wchar16 *local_b8;
  wchar16 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_d0 = &LAB_0029f1bb_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"accessibility",0xd);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_d8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_d8);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,*(double *)(this + 0xa0));
    local_c8 = L"accessibilityTextScale";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"accessibilityTextScale",0x16);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d8);
    uVar3 = ::QVariant::toDouble((bool *)local_48);
    *(undefined8 *)(this + 0xa0) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0xa8]);
    local_c0 = L"highContrast";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"highContrast",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0xa8] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0xa9]);
    local_b8 = L"reduceMotion";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"reduceMotion",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0xa9] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0xaa]);
    local_b0 = L"largerCursor";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"largerCursor",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_d8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0xaa] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    accessibilityChanged(this);
  }
  applyAccessibility(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00192694  Settings::saveAccessibility

/* Settings::saveAccessibility() */

void __thiscall Settings::saveAccessibility(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b8;
  wchar16 *local_b0;
  wchar16 *local_a8;
  wchar16 *local_a0;
  wchar16 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = 0;
  ::QVariant::QVariant(local_48,*(double *)(this + 0xa0));
  local_b0 = L"accessibilityTextScale";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"accessibilityTextScale",0x16);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0xa8]);
  local_a8 = L"highContrast";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"highContrast",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0xa9]);
  local_a0 = L"reduceMotion";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"reduceMotion",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0xaa]);
  local_98 = L"largerCursor";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"largerCursor",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029f1bb_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"accessibility",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  saveInput(this);
  applyAccessibility(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00192b16  Settings::loadPrivacy

/* Settings::loadPrivacy() */

void __thiscall Settings::loadPrivacy(Settings *this)

{
  char cVar1;
  Settings SVar2;
  long in_FS_OFFSET;
  QString local_c8 [8];
  wchar16 *local_c0;
  undefined *local_b8;
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_c0 = L"privacy";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"privacy",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_c8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_c8);
  if (cVar1 != '\x01') {
    ::QVariant::QVariant(local_68,(bool)this[0x388]);
    local_b8 = &DAT_0029f268;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"locationEnabled",0xf);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_c8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x388] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x389]);
    local_b0 = &LAB_0029f287_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"lockScreenNotifPreview",0x16);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_c8);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x389] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    privacyChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_c8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00192e84  Settings::saveConfPrivacy

/* Settings::saveConfPrivacy() */

void __thiscall Settings::saveConfPrivacy(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_a8;
  undefined *local_a0;
  undefined1 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a8 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x388]);
  local_a0 = &DAT_0029f268;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"locationEnabled",0xf);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x389]);
  local_98 = &LAB_0029f287_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"lockScreenNotifPreview",0x16);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_a8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"privacy";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"privacy",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_a8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0019313c  Settings::loadDock

/* Settings::loadDock() */

void __thiscall Settings::loadDock(Settings *this)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  undefined8 uVar3;
  QString local_128 [8];
  undefined1 *local_120;
  undefined1 *local_118;
  undefined1 *local_110;
  wchar16 *local_108;
  wchar16 *local_100;
  wchar16 *local_f8;
  wchar16 *local_f0;
  undefined *local_e8;
  undefined1 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = &LAB_0029f2b6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"dock",4);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_128);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_128);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,*(int *)(this + 0xc0));
    local_118 = &LAB_0029f2bf_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"iconSize",8);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0xc0) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0xc4));
    local_110 = &LAB_0029f2d1_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"spacing",7);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0xc4) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(double *)(this + 0xd0));
    local_108 = L"zoomPercent";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"zoomPercent",0xb);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar3 = ::QVariant::toDouble((bool *)local_48);
    *(undefined8 *)(this + 0xd0) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 200));
    local_100 = L"zoomRange";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"zoomRange",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 200) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0xcc));
    local_f8 = L"animSpeed";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"animSpeed",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0xcc) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(double *)(this + 0xd8));
    local_f0 = L"magSpring";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"magSpring",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar3 = ::QVariant::toDouble((bool *)local_48);
    *(undefined8 *)(this + 0xd8) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(double *)(this + 0xe0));
    local_e8 = &DAT_0029f336;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"magDamping",10)
    ;
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar3 = ::QVariant::toDouble((bool *)local_48);
    *(undefined8 *)(this + 0xe0) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(double *)(this + 0xe8));
    local_e0 = &LAB_0029f34c;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"magMass",7);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
    uVar3 = ::QVariant::toDouble((bool *)local_48);
    *(undefined8 *)(this + 0xe8) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    local_d8 = L"apps";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"apps",4);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_128,local_88);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    if (cVar1 != '\0') {
      ::QVariant::QVariant(local_68);
      local_d0 = L"apps";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"apps",4);
      QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_128);
      ::QVariant::toList();
      QList<QVariant>::operator=((QList<QVariant> *)(this + 0xf0),(QList *)local_88);
      QList<QVariant>::~QList((QList<QVariant> *)local_88);
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString((QString *)local_a8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
      ::QVariant::~QVariant(local_68);
    }
    dockChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_128);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00193ce6  Settings::setDockApps

/* Settings::setDockApps(QList<QVariant> const&) */

void __thiscall Settings::setDockApps(Settings *this,QList *param_1)

{
  QList<QVariant>::operator=((QList<QVariant> *)(this + 0xf0),param_1);
  dockChanged(this);
  return;
}



// ==== 00193d20  Settings::saveDockPrefs

/* Settings::saveDockPrefs() */

void __thiscall Settings::saveDockPrefs(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  wchar16 *local_c8;
  wchar16 *local_c0;
  wchar16 *local_b8;
  wchar16 *local_b0;
  undefined *local_a8;
  undefined1 *local_a0;
  wchar16 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_e0 = 0;
  ::QVariant::QVariant(local_48,*(int *)(this + 0xc0));
  local_d8 = &LAB_0029f2bf_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"iconSize",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0xc4));
  local_d0 = &LAB_0029f2d1_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"spacing",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0xd0));
  local_c8 = L"zoomPercent";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"zoomPercent",0xb)
  ;
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 200));
  local_c0 = L"zoomRange";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"zoomRange",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0xcc));
  local_b8 = L"animSpeed";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"animSpeed",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0xd8));
  local_b0 = L"magSpring";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"magSpring",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0xe0));
  local_a8 = &DAT_0029f336;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"magDamping",10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0xe8));
  local_a0 = &LAB_0029f34c;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"magMass",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QList *)(this + 0xf0));
  local_98 = L"apps";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"apps",4);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029f2b6;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"dock",4);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_e0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  dockChanged(this);
  dockPrefsChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_e0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001945ba  Settings::installedApps

/* Settings::installedApps() */

Settings * __thiscall Settings::installedApps(Settings *this)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  QVariant *pQVar5;
  QString *pQVar6;
  undefined8 in_R9;
  long in_FS_OFFSET;
  bool bVar7;
  bool bVar8;
  undefined8 uVar9;
  char local_2b9;
  QSet<QString> local_2b8 [8];
  undefined8 local_2b0;
  undefined8 local_2a8;
  QDir local_2a0 [8];
  undefined8 local_298;
  undefined8 local_290;
  QList<QString> *local_288;
  QString *local_280;
  QList<QString> *local_278;
  undefined8 local_270;
  wchar16 *local_268;
  undefined *local_260;
  wchar16 *local_258;
  wchar16 *local_250;
  wchar16 *local_248;
  wchar16 *local_240;
  wchar16 *local_238;
  undefined *local_230;
  undefined1 *local_228;
  undefined1 *local_220;
  undefined1 *local_218;
  undefined1 *local_210;
  undefined1 *local_208;
  undefined1 *local_200;
  undefined1 *local_1f8;
  wchar16 *local_1f0;
  QFile local_1e8 [16];
  QTextStream local_1d8 [16];
  QList<QString> local_1c8 [32];
  QList<QString> local_1a8 [32];
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  QArrayDataPointer<char16_t> local_128 [32];
  undefined4 local_108 [8];
  ulong local_e8 [4];
  QArrayDataPointer<char16_t> local_c8 [32];
  undefined2 local_a8 [16];
  QString local_88 [24];
  QString local_70 [24];
  QString aQStack_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined1 (*) [16])this = (undefined1  [16])0x0;
  *(undefined8 *)(this + 0x10) = 0;
  QSet<QString>::QSet(local_2b8);
  if ((installedApps()::fieldCodes == '\0') &&
     (iVar3 = __cxa_guard_acquire(&installedApps()::fieldCodes), iVar3 != 0)) {
    QFlags<QRegularExpression::PatternOption>::QFlags
              ((QFlags<QRegularExpression::PatternOption> *)local_e8,0);
    local_268 = L"%[fFuUdDnNickvm]";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"%[fFuUdDnNickvm]",0x10);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QRegularExpression::QRegularExpression
              ((QRegularExpression *)&installedApps()::fieldCodes,local_a8,local_e8[0] & 0xffffffff)
    ;
    __cxa_atexit(QRegularExpression::~QRegularExpression,&installedApps()::fieldCodes,&__dso_handle)
    ;
    __cxa_guard_release(&installedApps()::fieldCodes);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
  }
  local_250 = L"/usr/share/applications";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_128,(QTypedArrayData *)0x0,L"/usr/share/applications",0x17);
  QString::QString(local_88,(QArrayDataPointer *)local_128);
  local_258 = L"/usr/local/share/applications";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,
             L"/usr/local/share/applications",0x1d);
  QString::QString(local_70,(QArrayDataPointer *)local_108);
  local_260 = &DAT_0029f400;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_c8,(QTypedArrayData *)0x0,L"/.local/share/applications",0x1a);
  QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
  QDir::homePath();
  ::operator+(aQStack_58,(QString *)local_e8);
  QList<QString>::QList(local_1c8,local_88,3);
  pQVar6 = (QString *)local_40;
  while (pQVar6 != local_88) {
    pQVar6 = pQVar6 + -0x18;
    QString::~QString(pQVar6);
  }
  QString::~QString((QString *)local_e8);
  QString::~QString((QString *)local_a8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_128);
  local_288 = local_1c8;
  local_2b0 = QList<QString>::begin(local_288);
  local_2a8 = QList<QString>::end(local_288);
  while (cVar2 = QList<QString>::const_iterator::operator!=((const_iterator *)&local_2b0,local_2a8),
        cVar2 != '\0') {
    local_280 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)&local_2b0);
    QDir::QDir(local_2a0,local_280);
    QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_e8,0xffffffff);
    QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)local_108,2);
    local_248 = L"*.desktop";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"*.desktop",9);
    QString::QString(local_88,(QArrayDataPointer *)local_c8);
    uVar9 = 0xffffffffffffffff;
    QList<QString>::QList(local_a8,local_88,1);
    QDir::entryList(local_1a8,local_2a0,local_a8,local_108[0],local_e8[0] & 0xffffffff,in_R9,uVar9);
    QList<QString>::~QList((QList<QString> *)local_a8);
    pQVar6 = local_70;
    while (pQVar6 != local_88) {
      pQVar6 = pQVar6 + -0x18;
      QString::~QString(pQVar6);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    local_278 = local_1a8;
    local_298 = QList<QString>::begin(local_278);
    local_290 = QList<QString>::end(local_278);
    while (cVar2 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_298,local_290), cVar2 != '\0') {
      local_270 = QList<QString>::const_iterator::operator*((const_iterator *)&local_298);
      QDir::filePath((QString *)local_a8);
      QFile::QFile(local_1e8,(QString *)local_a8);
      QString::~QString((QString *)local_a8);
      uVar4 = operator|(1,0x10);
      cVar2 = QFile::open(local_1e8,uVar4);
      if (cVar2 == '\x01') {
        local_188 = 0;
        local_180 = 0;
        local_178 = 0;
        local_168 = 0;
        local_160 = 0;
        local_158 = 0;
        local_148 = 0;
        local_140 = 0;
        local_138 = 0;
        bVar7 = false;
        bVar8 = false;
        local_2b9 = '\0';
        QTextStream::QTextStream(local_1d8,(QIODevice *)local_1e8);
        while (cVar2 = QTextStream::atEnd(), cVar2 != '\x01') {
          QTextStream::readLine((longlong)local_128);
          QLatin1Char::QLatin1Char((QLatin1Char *)local_c8,'[');
          QChar::QChar<QLatin1Char,true>((QChar *)local_a8,local_c8[0]);
          cVar2 = QString::startsWith(local_128,local_a8[0],1);
          if (cVar2 == '\0') {
            if (local_2b9 == '\x01') {
              local_238 = L"Name=";
              QArrayDataPointer<char16_t>::QArrayDataPointer
                        (local_c8,(QTypedArrayData *)0x0,L"Name=",5);
              QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
              cVar2 = QString::startsWith(local_128,local_a8,1);
              if ((cVar2 == '\0') ||
                 (cVar2 = QString::isEmpty((QString *)&local_188), cVar2 == '\0')) {
                bVar1 = false;
              }
              else {
                bVar1 = true;
              }
              QString::~QString((QString *)local_a8);
              QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
              if (bVar1) {
                QString::mid((longlong)local_a8,(longlong)local_128);
                QString::operator=((QString *)&local_188,(QString *)local_a8);
                QString::~QString((QString *)local_a8);
              }
              else {
                local_230 = &DAT_0029f47c;
                QArrayDataPointer<char16_t>::QArrayDataPointer
                          (local_c8,(QTypedArrayData *)0x0,L"Exec=",5);
                QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                cVar2 = QString::startsWith(local_128,local_a8,1);
                QString::~QString((QString *)local_a8);
                QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                if (cVar2 == '\0') {
                  local_228 = &LAB_0029f487_1;
                  QArrayDataPointer<char16_t>::QArrayDataPointer
                            (local_c8,(QTypedArrayData *)0x0,L"Icon=",5);
                  QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                  cVar2 = QString::startsWith(local_128,local_a8,1);
                  QString::~QString((QString *)local_a8);
                  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                  if (cVar2 == '\0') {
                    local_220 = &LAB_0029f490_4;
                    QArrayDataPointer<char16_t>::QArrayDataPointer
                              (local_c8,(QTypedArrayData *)0x0,L"NoDisplay=",10);
                    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                    cVar2 = QString::startsWith(local_128,local_a8,1);
                    QString::~QString((QString *)local_a8);
                    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                    if (cVar2 == '\0') {
                      local_210 = &LAB_0029f4a6_4;
                      QArrayDataPointer<char16_t>::QArrayDataPointer
                                (local_c8,(QTypedArrayData *)0x0,L"Hidden=",7);
                      QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                      cVar2 = QString::startsWith(local_128,local_a8,1);
                      QString::~QString((QString *)local_a8);
                      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                      if (cVar2 != '\0') {
                        QString::mid((longlong)local_108,(longlong)local_128);
                        QString::trimmed((QString *)local_e8);
                        local_208 = &LAB_00299b23_1;
                        QArrayDataPointer<char16_t>::QArrayDataPointer
                                  (local_c8,(QTypedArrayData *)0x0,L"true",4);
                        QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                        iVar3 = QString::compare(local_e8,local_a8,0);
                        bVar8 = iVar3 == 0;
                        QString::~QString((QString *)local_a8);
                        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                        QString::~QString((QString *)local_e8);
                        QString::~QString((QString *)local_108);
                      }
                    }
                    else {
                      QString::mid((longlong)local_108,(longlong)local_128);
                      QString::trimmed((QString *)local_e8);
                      local_218 = &LAB_00299b23_1;
                      QArrayDataPointer<char16_t>::QArrayDataPointer
                                (local_c8,(QTypedArrayData *)0x0,L"true",4);
                      QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
                      iVar3 = QString::compare(local_e8,local_a8,0);
                      bVar7 = iVar3 == 0;
                      QString::~QString((QString *)local_a8);
                      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
                      QString::~QString((QString *)local_e8);
                      QString::~QString((QString *)local_108);
                    }
                  }
                  else {
                    QString::mid((longlong)local_a8,(longlong)local_128);
                    QString::operator=((QString *)&local_148,(QString *)local_a8);
                    QString::~QString((QString *)local_a8);
                  }
                }
                else {
                  QString::mid((longlong)local_a8,(longlong)local_128);
                  QString::operator=((QString *)&local_168,(QString *)local_a8);
                  QString::~QString((QString *)local_a8);
                }
              }
            }
          }
          else {
            local_240 = L"[Desktop Entry]";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      (local_c8,(QTypedArrayData *)0x0,L"[Desktop Entry]",0xf);
            QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
            local_2b9 = ::operator==((QString *)local_128,(QString *)local_a8);
            QString::~QString((QString *)local_a8);
            QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
          }
          QString::~QString((QString *)local_128);
        }
        cVar2 = QString::isEmpty((QString *)&local_188);
        if ((((cVar2 != '\0') || (cVar2 = QString::isEmpty((QString *)&local_168), cVar2 != '\0'))
            || (bVar7)) ||
           ((bVar8 || (cVar2 = QSet<QString>::contains(local_2b8,(QString *)&local_188),
                      cVar2 != '\0')))) {
          bVar7 = true;
        }
        else {
          bVar7 = false;
        }
        if (!bVar7) {
          QSet<QString>::insert((QString *)local_a8);
          QString::remove((QString *)&local_168,(QRegularExpression *)&installedApps()::fieldCodes);
          QString::trimmed((QString *)local_a8);
          QString::operator=((QString *)&local_168,(QString *)local_a8);
          QString::~QString((QString *)local_a8);
          local_e8[0] = 0;
          ::QVariant::QVariant((QVariant *)local_88,(QString *)&local_188);
          local_200 = &LAB_0029e187_1;
          QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"name",4);
          QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
          pQVar5 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)local_e8,(QString *)local_a8);
          ::QVariant::operator=(pQVar5,(QVariant *)local_88);
          QString::~QString((QString *)local_a8);
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
          ::QVariant::~QVariant((QVariant *)local_88);
          ::QVariant::QVariant((QVariant *)local_88,(QString *)&local_168);
          local_1f8 = &LAB_0029f4b6_4;
          QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"exec",4);
          QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
          pQVar5 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)local_e8,(QString *)local_a8);
          ::QVariant::operator=(pQVar5,(QVariant *)local_88);
          QString::~QString((QString *)local_a8);
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
          ::QVariant::~QVariant((QVariant *)local_88);
          ::QVariant::QVariant((QVariant *)local_88,(QString *)&local_148);
          local_1f0 = L"icon";
          QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"icon",4);
          QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
          pQVar5 = (QVariant *)
                   QMap<QString,QVariant>::operator[]
                             ((QMap<QString,QVariant> *)local_e8,(QString *)local_a8);
          ::QVariant::operator=(pQVar5,(QVariant *)local_88);
          QString::~QString((QString *)local_a8);
          QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
          ::QVariant::~QVariant((QVariant *)local_88);
          ::QVariant::QVariant((QVariant *)local_88,(QMap *)local_e8);
          QList<QVariant>::append((QList<QVariant> *)this,(QVariant *)local_88);
          ::QVariant::~QVariant((QVariant *)local_88);
          QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_e8);
        }
        QTextStream::~QTextStream(local_1d8);
        QString::~QString((QString *)&local_148);
        QString::~QString((QString *)&local_168);
        QString::~QString((QString *)&local_188);
      }
      QFile::~QFile(local_1e8);
      QList<QString>::const_iterator::operator++((const_iterator *)&local_298);
    }
    QList<QString>::~QList(local_1a8);
    QDir::~QDir(local_2a0);
    QList<QString>::const_iterator::operator++((const_iterator *)&local_2b0);
  }
  QList<QString>::~QList(local_1c8);
  QSet<QString>::~QSet(local_2b8);
  if (local_40[0] == *(long *)(in_FS_OFFSET + 0x28)) {
    return this;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00195b70  Settings::loadLocale

/* Settings::loadLocale() */

void __thiscall Settings::loadLocale(Settings *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_120 [8];
  undefined8 local_118;
  QArrayDataPointer<char16_t> *local_110;
  undefined8 local_108;
  undefined1 *local_100;
  wchar16 *local_f8;
  wchar16 *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  undefined1 *local_d8;
  wchar16 *local_d0;
  undefined8 local_c8 [4];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_100 = &LAB_0029f4c4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"locale",6);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_120);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_120);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,(QString *)(this + 0x138));
    local_f8 = L"systemLanguage";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"systemLanguage",0xe)
    ;
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_120);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x138),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x150));
    local_f0 = L"systemLocale";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"systemLocale",0xc);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_120);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x150),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_68);
    local_e8 = L"kbLayouts";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"kbLayouts",9);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_120,local_88);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    if (cVar1 != '\0') {
      QList<QString>::clear((QList<QString> *)(this + 0x168));
      ::QVariant::QVariant(local_68);
      local_e0 = L"kbLayouts";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"kbLayouts",9);
      QString::QString(local_88,(QArrayDataPointer *)local_c8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_120);
      ::QVariant::toList();
      local_110 = local_a8;
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      ::QVariant::~QVariant(local_68);
      local_118 = QList<QVariant>::begin((QList<QVariant> *)local_110);
      local_c8[0] = QList<QVariant>::end((QList<QVariant> *)local_110);
      while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_118,local_c8[0]),
            cVar1 != '\0') {
        local_108 = QList<QVariant>::iterator::operator*((iterator *)&local_118);
        ::QVariant::toString();
        QList<QString>::operator<<((QList<QString> *)(this + 0x168),local_88);
        QString::~QString(local_88);
        QList<QVariant>::iterator::operator++((iterator *)&local_118);
      }
      QList<QVariant>::~QList((QList<QVariant> *)local_a8);
      cVar1 = QList<QString>::isEmpty((QList<QString> *)(this + 0x168));
      if (cVar1 != '\0') {
        local_d8 = &LAB_0029e6a7_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"us",2);
        QString::QString(local_88,(QArrayDataPointer *)local_a8);
        QList<QString>::operator<<((QList<QString> *)(this + 0x168),local_88);
        QString::~QString(local_88);
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      }
    }
    ::QVariant::QVariant(local_68,(QString *)(this + 0x180));
    local_d0 = L"activeKbLayout";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"activeKbLayout",0xe)
    ;
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_120);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x180),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_68);
    applyKbLayout(this);
    localeChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_120);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001963e2  Settings::saveLocale

/* Settings::saveLocale() */

void __thiscall Settings::saveLocale(Settings *this)

{
  QVariant *pQVar1;
  QString *this_00;
  long in_FS_OFFSET;
  undefined8 local_1a0;
  wchar16 *local_198;
  wchar16 *local_190;
  wchar16 *local_188;
  wchar16 *local_180;
  undefined1 *local_178;
  wchar16 *local_170;
  wchar16 *local_168;
  wchar16 *local_160;
  QArrayDataPointer<char16_t> local_158 [32];
  QString local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  QArrayDataPointer<char16_t> local_f8 [32];
  QString local_d8 [32];
  QArrayDataPointer<char16_t> local_b8 [32];
  QString local_98 [32];
  QVariant local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_1a0 = 0;
  ::QVariant::QVariant(local_78,(QString *)(this + 0x138));
  local_198 = L"systemLanguage";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"systemLanguage",0xe);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1a0,local_98);
  ::QVariant::operator=(pQVar1,local_78);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  ::QVariant::~QVariant(local_78);
  ::QVariant::QVariant(local_78,(QString *)(this + 0x150));
  local_190 = L"systemLocale";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"systemLocale",0xc);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1a0,local_98);
  ::QVariant::operator=(pQVar1,local_78);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  ::QVariant::~QVariant(local_78);
  ::QVariant::QVariant(local_78,(QList *)(this + 0x168));
  local_188 = L"kbLayouts";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_b8,(QTypedArrayData *)0x0,L"kbLayouts",9);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1a0,local_98);
  ::QVariant::operator=(pQVar1,local_78);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  ::QVariant::~QVariant(local_78);
  ::QVariant::QVariant(local_78,(QString *)(this + 0x180));
  local_180 = L"activeKbLayout";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_b8,(QTypedArrayData *)0x0,L"activeKbLayout",0xe);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_1a0,local_98);
  ::QVariant::operator=(pQVar1,local_78);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  ::QVariant::~QVariant(local_78);
  local_178 = &LAB_0029f4c4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_b8,(QTypedArrayData *)0x0,L"locale",6);
  QString::QString(local_98,(QArrayDataPointer *)local_b8);
  Lelan::writeConfig(local_98,(QMap *)&local_1a0);
  QString::~QString(local_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_b8);
  applyKbLayout(this);
  QString::QString(local_98);
  local_168 = L"set-locale";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L"set-locale",10);
  QString::QString((QString *)local_78,(QArrayDataPointer *)local_118);
  local_170 = L"LANG=";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_f8,(QTypedArrayData *)0x0,L"LANG=",5);
  QString::QString(local_d8,(QArrayDataPointer *)local_f8);
  ::operator+(local_60,local_d8);
  QList<QString>::QList(local_b8,local_78,2);
  local_160 = L"localectl";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_158,(QTypedArrayData *)0x0,L"localectl",9);
  QString::QString(local_138,(QArrayDataPointer *)local_158);
  QProcess::startDetached(local_138,(QList *)local_b8,local_98,(longlong *)0x0);
  QString::~QString(local_138);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_158);
  QList<QString>::~QList((QList<QString> *)local_b8);
  this_00 = aQStack_48;
  while (this_00 != (QString *)local_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QString::~QString(local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QString::~QString(local_98);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_1a0);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00196bb6  Settings::setActiveKbLayout

/* Settings::setActiveKbLayout(QString const&) */

void __thiscall Settings::setActiveKbLayout(Settings *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator==(param_1,(QString *)(this + 0x180));
  if (cVar1 == '\0') {
    QString::operator=((QString *)(this + 0x180),param_1);
    cVar1 = QListSpecialMethods<QString>::contains
                      ((QListSpecialMethods<QString> *)(this + 0x168),param_1,1);
    if (cVar1 != '\x01') {
      QList<QString>::operator<<((QList<QString> *)(this + 0x168),param_1);
    }
    applyKbLayout(this);
    localeChanged(this);
  }
  return;
}



// ==== 00196c5c  Settings::addKbLayout

/* Settings::addKbLayout(QString const&) */

void __thiscall Settings::addKbLayout(Settings *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  
  cVar2 = QString::isEmpty(param_1);
  if (cVar2 == '\0') {
    cVar2 = QListSpecialMethods<QString>::contains
                      ((QListSpecialMethods<QString> *)(this + 0x168),param_1,1);
    if (cVar2 == '\0') {
      bVar1 = false;
      goto LAB_00196cab;
    }
  }
  bVar1 = true;
LAB_00196cab:
  if (!bVar1) {
    QList<QString>::operator<<((QList<QString> *)(this + 0x168),param_1);
    applyKbLayout(this);
    localeChanged(this);
  }
  return;
}



// ==== 00196ce6  Settings::removeKbLayout

/* Settings::removeKbLayout(QString const&) */

void __thiscall Settings::removeKbLayout(Settings *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  QString *pQVar3;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = QList<QString>::removeOne<QString>((QList<QString> *)(this + 0x168),param_1);
  if (bVar1) {
    cVar2 = QList<QString>::isEmpty((QList<QString> *)(this + 0x168));
    if (cVar2 != '\0') {
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_58,(QTypedArrayData *)0x0,L"us",2);
      QString::QString(local_38,(QArrayDataPointer *)local_58);
      QList<QString>::operator<<((QList<QString> *)(this + 0x168),local_38);
      QString::~QString(local_38);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    }
    cVar2 = ::operator==((QString *)(this + 0x180),param_1);
    if (cVar2 != '\0') {
      pQVar3 = (QString *)QList<QString>::first((QList<QString> *)(this + 0x168));
      QString::operator=((QString *)(this + 0x180),pQVar3);
    }
    applyKbLayout(this);
    localeChanged(this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00196e62  Settings::loadDefaults

/* Settings::loadDefaults() */

void __thiscall Settings::loadDefaults(Settings *this)

{
  char cVar1;
  long in_FS_OFFSET;
  QString local_f8 [8];
  wchar16 *local_f0;
  undefined *local_e8;
  undefined1 *local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = L"session-defaults";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"session-defaults",0x10);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,(QString *)(this + 0x198));
    local_e8 = &DAT_0029f59a;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"browser",7);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x198),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x1b0));
    local_e0 = &LAB_0029f5aa;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"mail",4);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x1b0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x1c8));
    local_d8 = &LAB_0029f5b4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"files",5);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x1c8),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x1e0));
    local_d0 = &LAB_0029f5c0;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"terminal",8);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x1e0),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    sessionChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001974a4  Settings::saveDefaults

/* Settings::saveDefaults() */

void __thiscall Settings::saveDefaults(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b8;
  undefined *local_b0;
  undefined1 *local_a8;
  undefined1 *local_a0;
  undefined1 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = 0;
  ::QVariant::QVariant(local_48,(QString *)(this + 0x198));
  local_b0 = &DAT_0029f59a;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"browser",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x1b0));
  local_a8 = &LAB_0029f5aa;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"mail",4);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x1c8));
  local_a0 = &LAB_0029f5b4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"files",5);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x1e0));
  local_98 = &LAB_0029f5c0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"terminal",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"session-defaults";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"session-defaults",0x10);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  sessionChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00197910  Settings::loadAutostart

/* Settings::loadAutostart() */

Settings * __thiscall Settings::loadAutostart(Settings *this)

{
  long in_FS_OFFSET;
  QString local_e8 [8];
  QList local_e0 [8];
  undefined1 *local_d8;
  wchar16 *local_d0;
  QList<QVariant> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_d8 = &LAB_0029f5d1_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"autostart",9);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_e8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::QVariant(local_68);
  local_d0 = L"entries";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"entries",7);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  QMap<QString,QVariant>::value(local_48,(QVariant *)local_e8);
  ::QVariant::toList();
  ::QVariant::~QVariant((QVariant *)local_48);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_68);
  QJsonArray::fromVariantList(local_e0);
  QJsonDocument::QJsonDocument((QJsonDocument *)local_a8,(QJsonArray *)local_e0);
  QJsonDocument::toJson(local_88,local_a8,1);
  QString::fromUtf8<void>((QString *)this,(QByteArray *)local_88);
  QByteArray::~QByteArray((QByteArray *)local_88);
  QJsonDocument::~QJsonDocument((QJsonDocument *)local_a8);
  QJsonArray::~QJsonArray((QJsonArray *)local_e0);
  QList<QVariant>::~QList(local_c8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_e8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00197c2c  Settings::saveAutostart

/* Settings::saveAutostart(QString const&) */

void Settings::saveAutostart(QString *param_1)

{
  QVariant *this;
  long in_FS_OFFSET;
  QJsonArray local_c8 [8];
  undefined8 local_c0;
  wchar16 *local_b8;
  undefined1 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QByteArray local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::toUtf8(local_68);
  QJsonDocument::fromJson(local_88,(QJsonParseError *)local_68);
  QJsonDocument::array();
  QJsonDocument::~QJsonDocument((QJsonDocument *)local_88);
  QByteArray::~QByteArray((QByteArray *)local_68);
  local_c0 = 0;
  QJsonArray::toVariantList();
  ::QVariant::QVariant(local_48,(QList *)local_68);
  local_b8 = L"entries";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"entries",7);
  QString::QString((QString *)local_88,(QArrayDataPointer *)local_a8);
  this = (QVariant *)
         QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,(QString *)local_88)
  ;
  ::QVariant::operator=(this,local_48);
  QString::~QString((QString *)local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  ::QVariant::~QVariant(local_48);
  QList<QVariant>::~QList((QList<QVariant> *)local_68);
  local_b0 = &LAB_0029f5d1_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"autostart",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_c0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
  syncAutostartDesktops((Settings *)param_1,local_c8);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
  QJsonArray::~QJsonArray(local_c8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00197f1e  Settings::loadNotifications

/* Settings::loadNotifications() */

void __thiscall Settings::loadNotifications(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_100 [8];
  wchar16 *local_f8;
  undefined *local_f0;
  wchar16 *local_e8;
  undefined *local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f8 = L"notifications";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"notifications",0xd);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_100);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_100);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,(bool)this[0x1f8]);
    local_f0 = &DAT_0029f612;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"dnd",3);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x1f8] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x1fc));
    local_e8 = L"notifPosition";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"notifPosition",0xd);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x1fc) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(bool)this[0x200]);
    local_e0 = &DAT_0029f636;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"quietHoursOn",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x200] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x208));
    local_d8 = &LAB_0029f650;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"quietFrom",9);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x208),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x220));
    local_d0 = &LAB_0029f664;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_c8,(QTypedArrayData *)0x0,L"quietTo",7);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_100);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x220),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    notifsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_100);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00198610  Settings::saveNotifications

/* Settings::saveNotifications() */

void __thiscall Settings::saveNotifications(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_c0;
  undefined *local_b8;
  wchar16 *local_b0;
  undefined *local_a8;
  undefined1 *local_a0;
  undefined1 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_c0 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x1f8]);
  local_b8 = &DAT_0029f612;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"dnd",3);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x1fc));
  local_b0 = L"notifPosition";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"notifPosition",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x200]);
  local_a8 = &DAT_0029f636;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"quietHoursOn",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x208));
  local_a0 = &LAB_0029f650;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"quietFrom",9);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x220));
  local_98 = &LAB_0029f664;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"quietTo",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_c0,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"notifications";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"notifications",0xd);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_c0);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  notifsChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_c0);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00198b50  Settings::getWallpaper

/* Settings::getWallpaper() */

Settings * __thiscall Settings::getWallpaper(Settings *this)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QFile local_a8 [16];
  QString local_98 [32];
  QArrayDataPointer<char16_t> local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_78,(QTypedArrayData *)0x0,L"/.config/ncde/wallpaper.conf",0x1c);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  QDir::homePath();
  ::operator+(local_38,local_98);
  QFile::QFile(local_a8,local_38);
  QString::~QString(local_38);
  QString::~QString(local_98);
  QString::~QString(local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_78);
  uVar2 = operator|(1,0x10);
  cVar1 = QFile::open(local_a8,uVar2);
  if (cVar1 == '\x01') {
    QIODevice::readLine((longlong)local_58);
    QString::fromUtf8<void>(local_38,(QByteArray *)local_58);
    QString::trimmed((QString *)this);
    QString::~QString(local_38);
    QByteArray::~QByteArray((QByteArray *)local_58);
  }
  else {
    QString::QString((QString *)this);
  }
  QFile::~QFile(local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00198dac  Settings::setWallpaper

/* Settings::setWallpaper(QString const&) */

void __thiscall Settings::setWallpaper(Settings *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  long in_FS_OFFSET;
  QSaveFile local_108 [16];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QString local_b8 [32];
  QString local_98 [32];
  undefined2 local_78 [16];
  QString local_58 [32];
  undefined4 local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = QString::isEmpty(param_1);
  if (cVar2 == '\0') {
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,
               L"/.config/ncde/wallpaper.conf",0x1c);
    QString::QString(local_58,(QArrayDataPointer *)local_78);
    QDir::homePath();
    ::operator+((QString *)local_38,local_98);
    QSaveFile::QSaveFile(local_108,(QString *)local_38,(QObject *)0x0);
    QString::~QString((QString *)local_38);
    QString::~QString(local_98);
    QString::~QString(local_58);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_38,2);
    cVar2 = QSaveFile::open(local_108,local_38[0]);
    if (cVar2 != '\0') {
      QLatin1Char::QLatin1Char((QLatin1Char *)local_98,'\n');
      QChar::QChar<QLatin1Char,true>((QChar *)local_78,local_98[0]);
      ::operator+(local_58,param_1,local_78[0]);
      QString::toUtf8((QString *)local_38);
      QIODevice::write((QByteArray *)local_108);
      QByteArray::~QByteArray((QByteArray *)local_38);
      QString::~QString(local_58);
      QSaveFile::commit();
    }
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_58,(QTypedArrayData *)0x0,
               L"/Pictures/wallpapers",0x14);
    QString::QString((QString *)local_38,(QArrayDataPointer *)local_58);
    userName((Settings *)local_98);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"/home/",6);
    QString::QString(local_b8,(QArrayDataPointer *)local_d8);
    ::operator+((QString *)local_78,local_b8);
    ::operator+(local_f8,(QString *)local_78);
    QString::~QString((QString *)local_78);
    QString::~QString(local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
    QString::~QString(local_98);
    QString::~QString((QString *)local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_58);
    cVar2 = QString::startsWith(param_1,local_f8,1);
    if ((cVar2 == '\x01') ||
       (cVar2 = QListSpecialMethods<QString>::contains
                          ((QListSpecialMethods<QString> *)(this + 0x238),param_1,1),
       cVar2 == '\x01')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      QList<QString>::operator<<((QList<QString> *)(this + 0x238),param_1);
      saveWallpaperPrefs(this);
    }
    wallpaperChanged(this,param_1);
    QString::~QString(local_f8);
    QSaveFile::~QSaveFile(local_108);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00199296  Settings::loadWallpaperPrefs

/* Settings::loadWallpaperPrefs() */

void __thiscall Settings::loadWallpaperPrefs(Settings *this)

{
  char cVar1;
  Settings SVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  QString local_118 [8];
  undefined8 local_110;
  QArrayDataPointer<char16_t> *local_108;
  undefined8 local_100;
  undefined1 *local_f8;
  undefined1 *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  undefined8 local_c8 [4];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f8 = &LAB_0029f6ef_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_a8,(QTypedArrayData *)0x0,L"wallpaper-slideshow",0x13);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_118);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_118);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,(bool)this[0x250]);
    local_f0 = &LAB_0029f717_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"enabled",7);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_118);
    SVar2 = (Settings)::QVariant::toBool();
    this[0x250] = SVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x254));
    local_e8 = L"interval";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"interval",8);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_118);
    uVar3 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x254) = uVar3;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 600));
    local_e0 = L"fitMode";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"fitMode",7);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_118);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 600),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
    ::QVariant::~QVariant(local_68);
    local_d8 = L"custom";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"custom",6);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    cVar1 = QMap<QString,QVariant>::contains((QMap<QString,QVariant> *)local_118,local_88);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    if (cVar1 != '\0') {
      QList<QString>::clear((QList<QString> *)(this + 0x238));
      ::QVariant::QVariant(local_68);
      local_d0 = L"custom";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_c8,(QTypedArrayData *)0x0,L"custom",6);
      QString::QString(local_88,(QArrayDataPointer *)local_c8);
      QMap<QString,QVariant>::value(local_48,(QVariant *)local_118);
      ::QVariant::toList();
      local_108 = local_a8;
      ::QVariant::~QVariant((QVariant *)local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_c8);
      ::QVariant::~QVariant(local_68);
      local_110 = QList<QVariant>::begin((QList<QVariant> *)local_108);
      local_c8[0] = QList<QVariant>::end((QList<QVariant> *)local_108);
      while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_110,local_c8[0]),
            cVar1 != '\0') {
        local_100 = QList<QVariant>::iterator::operator*((iterator *)&local_110);
        ::QVariant::toString();
        QList<QString>::operator<<((QList<QString> *)(this + 0x238),local_88);
        QString::~QString(local_88);
        QList<QVariant>::iterator::operator++((iterator *)&local_110);
      }
      QList<QVariant>::~QList((QList<QVariant> *)local_a8);
    }
    wallpaperPrefsChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_118);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001999e8  Settings::saveWallpaperPrefs

/* Settings::saveWallpaperPrefs() */

void __thiscall Settings::saveWallpaperPrefs(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b8;
  undefined1 *local_b0;
  wchar16 *local_a8;
  wchar16 *local_a0;
  wchar16 *local_98;
  undefined1 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = 0;
  ::QVariant::QVariant(local_48,(bool)this[0x250]);
  local_b0 = &LAB_0029f717_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"enabled",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x254));
  local_a8 = L"interval";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"interval",8);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 600));
  local_a0 = L"fitMode";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"fitMode",7);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QList *)(this + 0x238));
  local_98 = L"custom";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"custom",6);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = &LAB_0029f6ef_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"wallpaper-slideshow",0x13);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  wallpaperPrefsChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00199e54  Settings::setSlideshowEnabled

/* Settings::setSlideshowEnabled(bool) */

void __thiscall Settings::setSlideshowEnabled(Settings *this,bool param_1)

{
  if ((Settings)param_1 != this[0x250]) {
    this[0x250] = (Settings)param_1;
    saveWallpaperPrefs(this);
  }
  return;
}



// ==== 00199e94  Settings::setSlideshowInterval

/* Settings::setSlideshowInterval(int) */

void __thiscall Settings::setSlideshowInterval(Settings *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x254)) {
    *(int *)(this + 0x254) = param_1;
    saveWallpaperPrefs(this);
  }
  return;
}



// ==== 00199ed0  Settings::setFitMode

/* Settings::setFitMode(QString const&) */

void __thiscall Settings::setFitMode(Settings *this,QString *param_1)

{
  char cVar1;
  
  cVar1 = ::operator==(param_1,(QString *)(this + 600));
  if (cVar1 == '\0') {
    QString::operator=((QString *)(this + 600),param_1);
    saveWallpaperPrefs(this);
  }
  return;
}



// ==== 00199f2a  Settings::loadSound

/* Settings::loadSound() */

void __thiscall Settings::loadSound(Settings *this)

{
  char cVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  QString local_f8 [8];
  wchar16 *local_f0;
  wchar16 *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  QArrayDataPointer<char16_t> local_c8 [32];
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_f0 = L"sound";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"sound",5);
  QString::QString(local_88,(QArrayDataPointer *)local_a8);
  Lelan::readConfig(local_f8);
  QString::~QString(local_88);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
  cVar1 = QMap<QString,QVariant>::isEmpty((QMap<QString,QVariant> *)local_f8);
  if (cVar1 == '\0') {
    ::QVariant::QVariant(local_68,*(int *)(this + 0x270));
    local_e8 = L"outputVolume";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"outputVolume",0xc);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x270) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,*(int *)(this + 0x274));
    local_e0 = L"inputVolume";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"inputVolume",0xb);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    uVar2 = ::QVariant::toInt((bool *)local_48);
    *(undefined4 *)(this + 0x274) = uVar2;
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x278));
    local_d8 = L"outputDevice";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"outputDevice",0xc);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x278),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    ::QVariant::QVariant(local_68,(QString *)(this + 0x290));
    local_d0 = L"inputDevice";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_c8,(QTypedArrayData *)0x0,L"inputDevice",0xb);
    QString::QString((QString *)local_a8,(QArrayDataPointer *)local_c8);
    QMap<QString,QVariant>::value(local_48,(QVariant *)local_f8);
    ::QVariant::toString();
    QString::operator=((QString *)(this + 0x290),local_88);
    QString::~QString(local_88);
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString((QString *)local_a8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_c8);
    ::QVariant::~QVariant(local_68);
    soundChanged(this);
  }
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_f8);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0019a514  Settings::saveSound

/* Settings::saveSound() */

void __thiscall Settings::saveSound(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_b8;
  wchar16 *local_b0;
  wchar16 *local_a8;
  wchar16 *local_a0;
  wchar16 *local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_b8 = 0;
  ::QVariant::QVariant(local_48,*(int *)(this + 0x270));
  local_b0 = L"outputVolume";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"outputVolume",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x274));
  local_a8 = L"inputVolume";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"inputVolume",0xb)
  ;
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x278));
  local_a0 = L"outputDevice";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_88,(QTypedArrayData *)0x0,L"outputDevice",0xc);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x290));
  local_98 = L"inputDevice";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"inputDevice",0xb)
  ;
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_b8,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  ::QVariant::~QVariant(local_48);
  local_90 = L"sound";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"sound",5);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_b8);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  soundChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0019a97c  Settings::applyNightLight

/* Settings::applyNightLight() */

void __thiscall Settings::applyNightLight(Settings *this)

{
  char cVar1;
  int *piVar2;
  QString *this_00;
  long in_FS_OFFSET;
  undefined8 local_260;
  undefined8 local_258;
  QVariant local_250 [8];
  QList<QVariant> *local_248;
  undefined8 local_240;
  wchar16 *local_238;
  wchar16 *local_230;
  undefined *local_228;
  undefined1 *local_220;
  undefined *local_218;
  wchar16 *local_210;
  QString local_208 [32];
  QArrayDataPointer<char16_t> local_1e8 [32];
  QString local_1c8 [32];
  undefined2 local_1a8 [16];
  int local_188 [8];
  int local_168 [8];
  QArrayDataPointer<char16_t> local_148 [32];
  QString local_128 [32];
  QArrayDataPointer<char16_t> local_108 [32];
  QVariant local_e8 [32];
  QString local_c8 [32];
  QString local_a8 [48];
  QString aQStack_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x38] == (Settings)0x0) {
    local_230 = L"1.0:1.0:1.0";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_108,(QTypedArrayData *)0x0,L"1.0:1.0:1.0",0xb);
    QString::QString(local_208,(QArrayDataPointer *)local_108);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_108);
  }
  else {
    local_238 = L"1.0:1.0:%1";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_148,(QTypedArrayData *)0x0,L"1.0:1.0:%1",10);
    QString::QString(local_128,(QArrayDataPointer *)local_148);
    QChar::QChar<char16_t,true>((QChar *)local_1a8,L' ');
    local_168[0] = 0x1964;
    local_188[0] = 1000;
    piVar2 = qBound<int>(local_188,(int *)(this + 0x3c),local_168);
    QString::arg<double,true>
              ((((double)*piVar2 - 1000.0) * 0.5) / 5500.0 + 0.5,local_208,local_128,0,0x66,2,
               local_1a8[0]);
    QString::~QString(local_128);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
  }
  local_248 = (QList<QVariant> *)(this + 0x18);
  local_260 = QList<QVariant>::begin(local_248);
  local_258 = QList<QVariant>::end(local_248);
  while (cVar1 = QList<QVariant>::iterator::operator!=((iterator *)&local_260,local_258),
        cVar1 != '\0') {
    local_240 = QList<QVariant>::iterator::operator*((iterator *)&local_260);
    QString::QString((QString *)local_108);
    local_228 = &DAT_0029edc0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_1a8,(QTypedArrayData *)0x0,L"--output",8);
    QString::QString(local_a8,(QArrayDataPointer *)local_1a8);
    ::QVariant::toMap();
    ::QVariant::QVariant(local_e8);
    local_220 = &LAB_0029ed0e;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_188,(QTypedArrayData *)0x0,L"n",1);
    QString::QString((QString *)local_168,(QArrayDataPointer *)local_188);
    QMap<QString,QVariant>::value(local_c8,local_250);
    ::QVariant::toString();
    local_218 = &DAT_0029f7f6;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_148,(QTypedArrayData *)0x0,L"--gamma",7);
    QString::QString(aQStack_78,(QArrayDataPointer *)local_148);
    QString::QString(local_60,local_208);
    QList<QString>::QList(local_128,local_a8,4);
    local_210 = L"xrandr";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_1e8,(QTypedArrayData *)0x0,L"xrandr",6);
    QString::QString(local_1c8,(QArrayDataPointer *)local_1e8);
    QProcess::startDetached(local_1c8,(QList *)local_128,(QString *)local_108,(longlong *)0x0);
    QString::~QString(local_1c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1e8);
    QList<QString>::~QList((QList<QString> *)local_128);
    this_00 = aQStack_48;
    while (this_00 != local_a8) {
      this_00 = this_00 + -0x18;
      QString::~QString(this_00);
    }
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_148);
    ::QVariant::~QVariant((QVariant *)local_c8);
    QString::~QString((QString *)local_168);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_188);
    ::QVariant::~QVariant(local_e8);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_250);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1a8);
    QString::~QString((QString *)local_108);
    QList<QVariant>::iterator::operator++((iterator *)&local_260);
  }
  QString::~QString(local_208);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0019b0c2  Settings::applyLibinput

/* Settings::applyLibinput(QString const&, QString const&) */

void __thiscall Settings::applyLibinput(Settings *this,QString *param_1,QString *param_2)

{
  char cVar1;
  QString *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_200;
  undefined8 local_1f8;
  QList<QString> *local_1f0;
  undefined8 local_1e8;
  wchar16 *local_1e0;
  wchar16 *local_1d8;
  wchar16 *local_1d0;
  wchar16 *local_1c8;
  wchar16 *local_1c0;
  wchar16 *local_1b8;
  wchar16 *local_1b0;
  QProcess local_1a8 [16];
  QProcess local_198 [16];
  QList<QString> local_188 [32];
  undefined4 local_168 [8];
  undefined4 local_148 [8];
  undefined2 local_128 [16];
  undefined4 local_108 [8];
  QArrayDataPointer<char16_t> local_e8 [32];
  QList<QString> local_c8 [32];
  QString local_a8 [24];
  QString local_90 [24];
  QString aQStack_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QProcess::QProcess(local_1a8,(QObject *)0x0);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_168,3);
  local_1d8 = L"--list";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"--list",6);
  QString::QString(local_a8,(QArrayDataPointer *)local_108);
  local_1e0 = L"--id-only";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"--id-only",9);
  QString::QString(local_90,(QArrayDataPointer *)local_e8);
  QList<QString>::QList(local_c8,local_a8,2);
  local_1d0 = L"xinput";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"xinput",6);
  QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
  QProcess::start(local_1a8,local_128,local_c8,local_168[0]);
  QString::~QString((QString *)local_128);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
  QList<QString>::~QList(local_c8);
  pQVar2 = aQStack_78;
  while (pQVar2 != local_a8) {
    pQVar2 = pQVar2 + -0x18;
    QString::~QString(pQVar2);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
  cVar1 = QProcess::waitForFinished((int)local_1a8);
  if (cVar1 == '\x01') {
    QProcess::readAllStandardOutput();
    QString::fromUtf8<void>((QString *)local_c8,(QByteArray *)local_e8);
    QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_108,1);
    QChar::QChar<char,true>((QChar *)local_128,'\n');
    QString::split(local_188,local_c8,local_128[0],local_108[0],1);
    QString::~QString((QString *)local_c8);
    QByteArray::~QByteArray((QByteArray *)local_e8);
    local_1f0 = local_188;
    local_200 = QList<QString>::begin(local_1f0);
    local_1f8 = QList<QString>::end(local_1f0);
    while (cVar1 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_200,local_1f8), cVar1 != '\0') {
      local_1e8 = QList<QString>::const_iterator::operator*((const_iterator *)&local_200);
      QString::trimmed((QString *)local_168);
      cVar1 = QString::isEmpty((QString *)local_168);
      if (cVar1 == '\0') {
        QProcess::QProcess(local_198,(QObject *)0x0);
        QFlags<QIODeviceBase::OpenModeFlag>::QFlags
                  ((QFlags<QIODeviceBase::OpenModeFlag> *)local_148,3);
        local_1c8 = L"list-props";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  (local_e8,(QTypedArrayData *)0x0,L"list-props",10);
        QString::QString(local_a8,(QArrayDataPointer *)local_e8);
        QString::QString(local_90,(QString *)local_168);
        QList<QString>::QList(local_c8,local_a8,2);
        local_1c0 = L"xinput";
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"xinput",6);
        QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
        QProcess::start(local_198,local_108,local_c8,local_148[0]);
        QString::~QString((QString *)local_108);
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
        QList<QString>::~QList(local_c8);
        pQVar2 = aQStack_78;
        while (pQVar2 != local_a8) {
          pQVar2 = pQVar2 + -0x18;
          QString::~QString(pQVar2);
        }
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
        cVar1 = QProcess::waitForFinished((int)local_198);
        if (cVar1 == '\x01') {
          QProcess::readAllStandardOutput();
          QString::fromUtf8<void>((QString *)local_c8,(QByteArray *)local_e8);
          cVar1 = QString::contains((QString *)local_c8,param_1,1);
          QString::~QString((QString *)local_c8);
          QByteArray::~QByteArray((QByteArray *)local_e8);
          if (cVar1 == '\x01') {
            QString::QString((QString *)local_c8);
            local_1b8 = L"set-prop";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"set-prop",8
                      );
            QString::QString(local_a8,(QArrayDataPointer *)local_108);
            QString::QString(local_90,(QString *)local_168);
            QString::QString(aQStack_78,param_1);
            QString::QString(local_60,param_2);
            QList<QString>::QList(local_e8,local_a8,4);
            local_1b0 = L"xinput";
            QArrayDataPointer<char16_t>::QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"xinput",6);
            QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
            QProcess::startDetached
                      ((QString *)local_128,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
            QString::~QString((QString *)local_128);
            QArrayDataPointer<char16_t>::~QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_148);
            QList<QString>::~QList((QList<QString> *)local_e8);
            pQVar2 = aQStack_48;
            while (pQVar2 != local_a8) {
              pQVar2 = pQVar2 + -0x18;
              QString::~QString(pQVar2);
            }
            QArrayDataPointer<char16_t>::~QArrayDataPointer
                      ((QArrayDataPointer<char16_t> *)local_108);
            QString::~QString((QString *)local_c8);
          }
        }
        QProcess::~QProcess(local_198);
      }
      QString::~QString((QString *)local_168);
      QList<QString>::const_iterator::operator++((const_iterator *)&local_200);
    }
    QList<QString>::~QList(local_188);
  }
  QProcess::~QProcess(local_1a8);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0019bbd2  Settings::applyLibinputFiltered

/* Settings::applyLibinputFiltered(QString const&, QString const&, bool) */

void __thiscall
Settings::applyLibinputFiltered(Settings *this,QString *param_1,QString *param_2,bool param_3)

{
  char cVar1;
  int iVar2;
  QString *pQVar3;
  long in_FS_OFFSET;
  undefined8 local_1d0;
  undefined8 local_1c8;
  QRegularExpressionMatch local_1c0 [8];
  QList<QString> *local_1b8;
  QString *local_1b0;
  wchar16 *local_1a8;
  wchar16 *local_1a0;
  wchar16 *local_198;
  wchar16 *local_190;
  wchar16 *local_188;
  wchar16 *local_180;
  QProcess local_178 [16];
  QList<QString> local_168 [32];
  undefined4 local_148 [8];
  undefined2 local_128 [16];
  undefined4 local_108 [8];
  QArrayDataPointer<char16_t> local_e8 [32];
  undefined4 local_c8 [8];
  QString local_a8 [24];
  QString local_90 [24];
  QString aQStack_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QProcess::QProcess(local_178,(QObject *)0x0);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_148,3);
  local_1a8 = L"list";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"list",4);
  QString::QString(local_a8,(QArrayDataPointer *)local_e8);
  QList<QString>::QList(local_c8,local_a8,1);
  local_1a0 = L"xinput";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_128,(QTypedArrayData *)0x0,L"xinput",6);
  QString::QString((QString *)local_108,(QArrayDataPointer *)local_128);
  QProcess::start(local_178,local_108,local_c8,local_148[0]);
  QString::~QString((QString *)local_108);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_128);
  QList<QString>::~QList((QList<QString> *)local_c8);
  pQVar3 = local_90;
  while (pQVar3 != local_a8) {
    pQVar3 = pQVar3 + -0x18;
    QString::~QString(pQVar3);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
  cVar1 = QProcess::waitForFinished((int)local_178);
  if (cVar1 == '\x01') {
    QProcess::readAllStandardOutput();
    QString::fromUtf8<void>((QString *)local_c8,(QByteArray *)local_e8);
    QFlags<Qt::SplitBehaviorFlags>::QFlags((QFlags<Qt::SplitBehaviorFlags> *)local_108,1);
    QChar::QChar<char,true>((QChar *)local_128,'\n');
    QString::split(local_168,local_c8,local_128[0],local_108[0],1);
    QString::~QString((QString *)local_c8);
    QByteArray::~QByteArray((QByteArray *)local_e8);
    if ((applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe == '\0') &&
       (iVar2 = __cxa_guard_acquire(&applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe
                                   ), iVar2 != 0)) {
      QFlags<QRegularExpression::PatternOption>::QFlags
                ((QFlags<QRegularExpression::PatternOption> *)local_108,0);
      local_198 = L"id=(\\d+)";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"id=(\\d+)",8)
      ;
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
      QRegularExpression::QRegularExpression
                ((QRegularExpression *)
                 &applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe,local_c8,
                 local_108[0]);
      __cxa_atexit(QRegularExpression::~QRegularExpression,
                   &applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe,&__dso_handle);
      __cxa_guard_release(&applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    }
    local_1b8 = local_168;
    local_1d0 = QList<QString>::begin(local_1b8);
    local_1c8 = QList<QString>::end(local_1b8);
    while (cVar1 = QList<QString>::const_iterator::operator!=
                             ((const_iterator *)&local_1d0,local_1c8), cVar1 != '\0') {
      local_1b0 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)&local_1d0)
      ;
      local_190 = L"touchpad";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_e8,(QTypedArrayData *)0x0,L"touchpad",8);
      QString::QString((QString *)local_c8,(QArrayDataPointer *)local_e8);
      cVar1 = QString::contains(local_1b0,local_c8,0);
      QString::~QString((QString *)local_c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
      if (param_3 == (bool)cVar1) {
        QFlags<QRegularExpression::MatchOption>::QFlags
                  ((QFlags<QRegularExpression::MatchOption> *)local_c8,0);
        QRegularExpression::match
                  (local_1c0,&applyLibinputFiltered(QString_const&,QString_const&,bool)::idRe,
                   local_1b0,0,0,local_c8[0]);
        cVar1 = QRegularExpressionMatch::hasMatch();
        if (cVar1 == '\x01') {
          QString::QString((QString *)local_c8);
          local_188 = L"set-prop";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_108,(QTypedArrayData *)0x0,L"set-prop",8);
          QString::QString(local_a8,(QArrayDataPointer *)local_108);
          QRegularExpressionMatch::captured((int)local_90);
          QString::QString(aQStack_78,param_1);
          QString::QString(local_60,param_2);
          QList<QString>::QList(local_e8,local_a8,4);
          local_180 = L"xinput";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_148,(QTypedArrayData *)0x0,L"xinput",6);
          QString::QString((QString *)local_128,(QArrayDataPointer *)local_148);
          QProcess::startDetached
                    ((QString *)local_128,(QList *)local_e8,(QString *)local_c8,(longlong *)0x0);
          QString::~QString((QString *)local_128);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_148);
          QList<QString>::~QList((QList<QString> *)local_e8);
          pQVar3 = aQStack_48;
          while (pQVar3 != local_a8) {
            pQVar3 = pQVar3 + -0x18;
            QString::~QString(pQVar3);
          }
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_108);
          QString::~QString((QString *)local_c8);
        }
        QRegularExpressionMatch::~QRegularExpressionMatch(local_1c0);
      }
      QList<QString>::const_iterator::operator++((const_iterator *)&local_1d0);
    }
    QList<QString>::~QList(local_168);
  }
  QProcess::~QProcess(local_178);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0019c562  Settings::applyInput()::{lambda(QString_const&,QString_const&)#1}::operator()

/* Settings::applyInput()::{lambda(QString const&, QString
   const&)#1}::TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) const */

void Settings::applyInput()::{lambda(QString_const&,QString_const&)#1}::operator()
               (QString *param_1,QString *param_2)

{
  QRegularExpression *pQVar1;
  undefined8 uVar2;
  bool bVar3;
  char cVar4;
  long in_FS_OFFSET;
  QLatin1Char local_90;
  QLatin1Char local_8f;
  undefined2 local_8e;
  undefined4 local_8c;
  QRegularExpression local_88 [8];
  undefined1 *local_80;
  undefined2 local_78 [16];
  QString local_58 [32];
  undefined2 local_38 [12];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QFlags<QRegularExpression::PatternOption>::QFlags
            ((QFlags<QRegularExpression::PatternOption> *)&local_8c,0);
  local_80 = &LAB_0029999e;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_78,(QTypedArrayData *)0x0,L"=.*",3);
  QString::QString(local_58,(QArrayDataPointer *)local_78);
  ::operator+((QString *)local_38,param_2);
  QRegularExpression::QRegularExpression(local_88,local_38,local_8c);
  QString::~QString((QString *)local_38);
  QString::~QString(local_58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_78);
  cVar4 = QString::contains(*(QRegularExpression **)param_1,(QRegularExpressionMatch *)local_88);
  if (cVar4 != '\0') {
    pQVar1 = *(QRegularExpression **)param_1;
    QLatin1Char::QLatin1Char((QLatin1Char *)&local_8c,'=');
    QChar::QChar<QLatin1Char,true>((QChar *)local_78,local_8c._0_1_);
    ::operator+(local_58,param_2,local_78[0]);
    ::operator+((QString *)local_38,local_58);
    QString::replace(pQVar1,(QString *)local_88);
    QString::~QString((QString *)local_38);
    QString::~QString(local_58);
    goto LAB_0019c883;
  }
  cVar4 = QString::isEmpty(*(QString **)param_1);
  if (cVar4 == '\x01') {
LAB_0019c759:
    bVar3 = false;
  }
  else {
    uVar2 = *(undefined8 *)param_1;
    QLatin1Char::QLatin1Char((QLatin1Char *)local_58,'\n');
    QChar::QChar<QLatin1Char,true>((QChar *)local_38,local_58[0]);
    cVar4 = QString::endsWith(uVar2,local_38[0],1);
    if (cVar4 == '\x01') goto LAB_0019c759;
    bVar3 = true;
  }
  if (bVar3) {
    QLatin1Char::QLatin1Char((QLatin1Char *)local_58,'\n');
    QChar::QChar<QLatin1Char,true>((QChar *)local_38,local_58[0]);
    QString::operator+=(*(QString **)param_1,local_38[0]);
  }
  QLatin1Char::QLatin1Char(&local_8f,'\n');
  QChar::QChar<QLatin1Char,true>((QChar *)&local_8c,local_8f);
  QLatin1Char::QLatin1Char(&local_90,'=');
  QChar::QChar<QLatin1Char,true>((QChar *)&local_8e,local_90);
  ::operator+(local_78,param_2,local_8e);
  ::operator+(local_58,(QString *)local_78);
  ::operator+(local_38,local_58,(undefined2)local_8c);
  QString::operator+=(*(QString **)param_1,(QString *)local_38);
  QString::~QString((QString *)local_38);
  QString::~QString(local_58);
  QString::~QString((QString *)local_78);
LAB_0019c883:
  QRegularExpression::~QRegularExpression(local_88);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0019c982  Settings::applyInput

/* Settings::applyInput() */

void __thiscall Settings::applyInput(Settings *this)

{
  Settings SVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  undefined4 uVar6;
  double *pdVar7;
  QString *pQVar8;
  long in_FS_OFFSET;
  ulong *local_2f0;
  QString *local_2e8;
  double local_2e0;
  double local_2d8;
  initializer_list<QString> *local_2d0;
  QString *local_2c8;
  QString *local_2c0;
  wchar16 *local_2b8;
  undefined *local_2b0;
  undefined1 *local_2a8;
  undefined *local_2a0;
  undefined *local_298;
  undefined1 *local_290;
  undefined1 *local_288;
  undefined1 *local_280;
  undefined1 *local_278;
  undefined1 *local_270;
  wchar16 *local_268;
  undefined1 *local_260;
  undefined1 *local_258;
  wchar16 *local_250;
  wchar16 *local_248;
  wchar16 *local_240;
  undefined *local_238;
  wchar16 *local_230;
  undefined1 *local_228;
  wchar16 *local_220;
  wchar16 *local_218;
  undefined *local_210;
  undefined1 *local_208;
  undefined1 *local_200;
  undefined1 *local_1f8;
  undefined1 *local_1f0;
  undefined1 *local_1e8;
  wchar16 *local_1e0;
  undefined *local_1d8;
  wchar16 *local_1d0;
  undefined1 *local_1c8;
  wchar16 *local_1c0;
  undefined *local_1b8;
  wchar16 *local_1b0;
  QProcess local_1a8 [16];
  QString *local_198;
  undefined8 local_190;
  QFile local_178 [32];
  QArrayDataPointer<char16_t> local_158 [32];
  ulong local_138 [4];
  QArrayDataPointer<char16_t> local_118 [32];
  double local_f8 [4];
  double local_d8;
  undefined8 local_d0;
  double local_b8 [4];
  QString local_98 [24];
  QString local_80 [24];
  QString aQStack_68 [24];
  QString local_50 [24];
  QString aQStack_38 [8];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString((QString *)local_b8);
  local_2b0 = &DAT_0029f88c;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L"r",1);
  QString::QString(local_98,(QArrayDataPointer *)local_118);
  local_2b8 = L"rate";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"rate",4);
  QString::QString(local_80,(QArrayDataPointer *)local_f8);
  QString::number((int)aQStack_68,*(int *)(this + 0x84));
  QString::number((int)local_50,*(int *)(this + 0x88));
  QList<QString>::QList(&local_d8,local_98,4);
  local_2a8 = &LAB_0029efa4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_158,(QTypedArrayData *)0x0,L"xset",4);
  QString::QString((QString *)local_138,(QArrayDataPointer *)local_158);
  QProcess::startDetached
            ((QString *)local_138,(QList *)&local_d8,(QString *)local_b8,(longlong *)0x0);
  QString::~QString((QString *)local_138);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_158);
  QList<QString>::~QList((QList<QString> *)&local_d8);
  pQVar8 = aQStack_38;
  while (pQVar8 != local_98) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QString::~QString((QString *)local_b8);
  local_b8[0] = 1.0;
  local_d8 = (double)(*(int *)(this + 0x8c) + -0x32) / 50.0;
  local_f8[0] = -1.0;
  pdVar7 = qBound<double>(local_f8,&local_d8,local_b8);
  local_2e0 = *pdVar7;
  local_b8[0] = 1.0;
  local_d8 = (double)(*(int *)(this + 0x90) + -0x32) / 50.0;
  local_f8[0] = -1.0;
  pdVar7 = qBound<double>(local_f8,&local_d8,local_b8);
  local_2d8 = *pdVar7;
  QString::number(local_2e0,(char)local_b8,0x66);
  local_2a0 = &DAT_0029f8a0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"libinput Accel Speed",
             0x14);
  QString::QString((QString *)&local_d8,(QArrayDataPointer *)local_f8);
  applyLibinputFiltered(this,(QString *)&local_d8,(QString *)local_b8,false);
  QString::~QString((QString *)&local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  QString::~QString((QString *)local_b8);
  QString::number(local_2d8,(char)local_b8,0x66);
  local_298 = &DAT_0029f8a0;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"libinput Accel Speed",
             0x14);
  QString::QString((QString *)&local_d8,(QArrayDataPointer *)local_f8);
  applyLibinputFiltered(this,(QString *)&local_d8,(QString *)local_b8,true);
  QString::~QString((QString *)&local_d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  QString::~QString((QString *)local_b8);
  SVar1 = this[0x98];
  if (SVar1 == (Settings)0x0) {
    local_288 = &LAB_0029f8cd_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"0",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
  }
  else {
    local_290 = &LAB_0029f8c9_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"1",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)local_f8);
  }
  local_280 = &LAB_0029f8d7_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,
             L"libinput Natural Scrolling Enabled",0x22);
  QString::QString((QString *)local_118,(QArrayDataPointer *)local_138);
  applyLibinput(this,(QString *)local_118,(QString *)local_b8);
  QString::~QString((QString *)local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
  QString::~QString((QString *)local_b8);
  if (SVar1 == (Settings)0x0) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  }
  SVar1 = this[0x99];
  if (SVar1 == (Settings)0x0) {
    local_270 = &LAB_0029f8cd_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"0",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
  }
  else {
    local_278 = &LAB_0029f8c9_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"1",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)local_f8);
  }
  local_268 = L"libinput Tapping Enabled";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,
             L"libinput Tapping Enabled",0x18);
  QString::QString((QString *)local_118,(QArrayDataPointer *)local_138);
  applyLibinput(this,(QString *)local_118,(QString *)local_b8);
  QString::~QString((QString *)local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
  QString::~QString((QString *)local_b8);
  if (SVar1 == (Settings)0x0) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  }
  SVar1 = this[0x9a];
  if (SVar1 == (Settings)0x0) {
    local_258 = &LAB_0029f8cd_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"0",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
  }
  else {
    local_260 = &LAB_0029f8c9_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"1",1);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)local_f8);
  }
  local_250 = L"libinput Disable While Typing Enabled";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,
             L"libinput Disable While Typing Enabled",0x25);
  QString::QString((QString *)local_118,(QArrayDataPointer *)local_138);
  applyLibinput(this,(QString *)local_118,(QString *)local_b8);
  QString::~QString((QString *)local_118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
  QString::~QString((QString *)local_b8);
  if (SVar1 == (Settings)0x0) {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
  }
  else {
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
  }
  QProcess::QProcess(local_1a8,(QObject *)0x0);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_138,3);
  local_248 = L"-merge";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"-merge",6);
  QString::QString(local_98,(QArrayDataPointer *)&local_d8);
  QList<QString>::QList(local_b8,local_98,1);
  local_240 = L"xrdb";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L"xrdb",4);
  QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
  QProcess::start(local_1a8,local_f8,local_b8,local_138[0] & 0xffffffff);
  QString::~QString((QString *)local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QList<QString>::~QList((QList<QString> *)local_b8);
  pQVar8 = local_80;
  while (pQVar8 != local_98) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
  cVar5 = QProcess::waitForStarted((int)local_1a8);
  if (cVar5 != '\0') {
    local_238 = &DAT_0029f9c0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_118,(QTypedArrayData *)0x0,L"Xcursor.theme: Kith\nXcursor.size: %1\n",0x25);
    QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
    QChar::QChar<char16_t,true>((QChar *)local_138,L' ');
    QString::arg<int,true>
              (&local_d8,local_f8,*(undefined4 *)(this + 0x94),0,10,local_138[0] & 0xffff);
    QString::toUtf8((QString *)local_b8);
    QIODevice::write((QByteArray *)local_1a8);
    QByteArray::~QByteArray((QByteArray *)local_b8);
    QString::~QString((QString *)&local_d8);
    QString::~QString((QString *)local_f8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
    QProcess::closeWriteChannel();
    QProcess::waitForFinished((int)local_1a8);
  }
  local_198 = (QString *)0x0;
  local_190 = 2;
  local_228 = &LAB_0029fa0f_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,
             L"/gtk-3.0/settings.ini",0x15);
  QString::QString(local_98,(QArrayDataPointer *)&local_d8);
  local_230 = L"/gtk-4.0/settings.ini";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"/gtk-4.0/settings.ini"
             ,0x15);
  QString::QString(local_80,(QArrayDataPointer *)local_b8);
  local_198 = local_98;
  local_2d0 = (initializer_list<QString> *)&local_198;
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
  local_2e8 = (QString *)std::initializer_list<QString>::begin(local_2d0);
  local_2c8 = (QString *)std::initializer_list<QString>::end(local_2d0);
  do {
    if (local_2e8 == local_2c8) {
      pQVar8 = aQStack_68;
      while (pQVar8 != local_98) {
        pQVar8 = pQVar8 + -0x18;
        QString::~QString(pQVar8);
      }
      QByteArray::number((int)local_b8,*(int *)(this + 0x94));
      QByteArrayView::QByteArrayView<QByteArray,true>
                ((QByteArrayView *)&local_d8,(QByteArray *)local_b8);
      qputenv(&LAB_0029fb0b_1,local_d8,local_d0);
      QByteArray::~QByteArray((QByteArray *)local_b8);
      QString::QString((QString *)local_b8);
      local_1d8 = &DAT_00299b84;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_158,(QTypedArrayData *)0x0,L"set",3);
      QString::QString(local_98,(QArrayDataPointer *)local_158);
      local_1e0 = L"org.gnome.desktop.interface";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,
                 L"org.gnome.desktop.interface",0x1b);
      QString::QString(local_80,(QArrayDataPointer *)local_138);
      local_1e8 = &LAB_0029fb1a;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_118,(QTypedArrayData *)0x0,L"cursor-theme",0xc);
      QString::QString(aQStack_68,(QArrayDataPointer *)local_118);
      local_1f0 = &LAB_0029faa5_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"Kith",4);
      QString::QString(local_50,(QArrayDataPointer *)local_f8);
      QList<QString>::QList(&local_d8,local_98,4);
      local_1d0 = L"gsettings";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_198,(QTypedArrayData *)0x0,L"gsettings",9);
      QString::QString((QString *)local_178,(QArrayDataPointer *)&local_198);
      QProcess::startDetached
                ((QString *)local_178,(QList *)&local_d8,(QString *)local_b8,(longlong *)0x0);
      QString::~QString((QString *)local_178);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_198);
      QList<QString>::~QList((QList<QString> *)&local_d8);
      pQVar8 = aQStack_38;
      while (pQVar8 != local_98) {
        pQVar8 = pQVar8 + -0x18;
        QString::~QString(pQVar8);
      }
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_158);
      QString::~QString((QString *)local_b8);
      QString::QString((QString *)local_b8);
      local_1b8 = &DAT_00299b84;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_138,(QTypedArrayData *)0x0,L"set",3);
      QString::QString(local_98,(QArrayDataPointer *)local_138);
      local_1c0 = L"org.gnome.desktop.interface";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_118,(QTypedArrayData *)0x0,L"org.gnome.desktop.interface",0x1b);
      QString::QString(local_80,(QArrayDataPointer *)local_118);
      local_1c8 = &LAB_0029fb34;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"cursor-size",0xb);
      QString::QString(aQStack_68,(QArrayDataPointer *)local_f8);
      QString::number((int)local_50,*(int *)(this + 0x94));
      QList<QString>::QList(&local_d8,local_98,4);
      local_1b0 = L"gsettings";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_178,(QTypedArrayData *)0x0,L"gsettings",9);
      QString::QString((QString *)local_158,(QArrayDataPointer *)local_178);
      QProcess::startDetached
                ((QString *)local_158,(QList *)&local_d8,(QString *)local_b8,(longlong *)0x0);
      QString::~QString((QString *)local_158);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_178);
      QList<QString>::~QList((QList<QString> *)&local_d8);
      pQVar8 = aQStack_38;
      while (pQVar8 != local_98) {
        pQVar8 = pQVar8 + -0x18;
        QString::~QString(pQVar8);
      }
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_138);
      QString::~QString((QString *)local_b8);
      QProcess::~QProcess(local_1a8);
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_2c0 = local_2e8;
    local_220 = L"/.config";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"/.config",8);
    QString::QString((QString *)&local_d8,(QArrayDataPointer *)local_f8);
    QDir::homePath();
    ::operator+((QString *)local_b8,(QString *)local_118);
    ::operator+((QString *)local_158,(QString *)local_b8);
    QString::~QString((QString *)local_b8);
    QString::~QString((QString *)local_118);
    QString::~QString((QString *)&local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
    QString::QString((QString *)&local_d8);
    QDir::QDir((QDir *)local_138,(QString *)&local_d8);
    std::optional<QFlags<QFileDevice::Permission>>::optional(local_f8);
    QFileInfo::QFileInfo((QFileInfo *)local_118,(QString *)local_158);
    QFileInfo::absolutePath();
    QDir::mkpath(local_138,local_b8,local_f8[0]);
    QString::~QString((QString *)local_b8);
    QFileInfo::~QFileInfo((QFileInfo *)local_118);
    QDir::~QDir((QDir *)local_138);
    QString::~QString((QString *)&local_d8);
    QFile::QFile(local_178,(QString *)local_158);
    local_138[0] = 0;
    local_138[1] = 0;
    local_138[2] = 0;
    uVar6 = operator|(1,0x10);
    cVar5 = QFile::open(local_178,uVar6);
    if (cVar5 != '\0') {
      QIODevice::readAll();
      QString::fromUtf8<void>((QString *)local_b8,(QByteArray *)&local_d8);
      QString::operator=((QString *)local_138,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QByteArray::~QByteArray((QByteArray *)&local_d8);
      QFileDevice::close();
    }
    bVar3 = false;
    bVar2 = false;
    cVar5 = QString::isEmpty((QString *)local_138);
    if (cVar5 == '\0') {
LAB_0019d981:
      bVar4 = false;
    }
    else {
      local_218 = L"gtk-3.0";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"gtk-3.0",7);
      bVar3 = true;
      QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
      bVar2 = true;
      cVar5 = QString::contains(local_2c0,local_b8,1);
      if (cVar5 == '\0') goto LAB_0019d981;
      bVar4 = true;
    }
    if (bVar2) {
      QString::~QString((QString *)local_b8);
    }
    if (bVar3) {
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
    }
    if (bVar4) {
      local_210 = &DAT_0029fa8e;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"[Settings]\n",0xb
                );
      QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
      QString::operator=((QString *)local_138,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
    }
    local_2f0 = local_138;
    local_200 = &LAB_0029faa5_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_d8,(QTypedArrayData *)0x0,L"Kith",4);
    QString::QString((QString *)local_b8,(QArrayDataPointer *)&local_d8);
    local_208 = &LAB_0029fab0;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_118,(QTypedArrayData *)0x0,L"gtk-cursor-theme-name",0x15);
    QString::QString((QString *)local_f8,(QArrayDataPointer *)local_118);
    applyInput()::{lambda(QString_const&,QString_const&)#1}::operator()
              ((QString *)&local_2f0,(QString *)local_f8);
    QString::~QString((QString *)local_f8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
    QString::~QString((QString *)local_b8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_d8);
    QString::number((int)local_b8,*(int *)(this + 0x94));
    local_1f8 = &LAB_0029fadf_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,
               L"gtk-cursor-theme-size",0x15);
    QString::QString((QString *)&local_d8,(QArrayDataPointer *)local_f8);
    applyInput()::{lambda(QString_const&,QString_const&)#1}::operator()
              ((QString *)&local_2f0,(QString *)&local_d8);
    QString::~QString((QString *)&local_d8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
    QString::~QString((QString *)local_b8);
    uVar6 = operator|(2,0x10);
    cVar5 = QFile::open(local_178,uVar6);
    if (cVar5 != '\0') {
      QTextStream::QTextStream((QTextStream *)local_b8,(QIODevice *)local_178);
      QTextStream::operator<<((QTextStream *)local_b8,(QString *)local_138);
      QTextStream::~QTextStream((QTextStream *)local_b8);
    }
    QString::~QString((QString *)local_138);
    QFile::~QFile(local_178);
    QString::~QString((QString *)local_158);
    local_2e8 = local_2e8 + 0x18;
  } while( true );
}



// ==== 0019ea0a  Settings::applyAccessibility

/* Settings::applyAccessibility() */

void __thiscall Settings::applyAccessibility(Settings *this)

{
  if (*(long *)(this + 0xb0) != 0) {
    Lelan::setReduceMotionPref(*(Lelan **)(this + 0xb0),(bool)this[0xa9]);
  }
  accessibilityChanged(this);
  fontChanged(this);
  return;
}



// ==== 0019ea64  Settings::applyKbLayout

/* Settings::applyKbLayout() */

void __thiscall Settings::applyKbLayout(Settings *this)

{
  QString *this_00;
  long in_FS_OFFSET;
  QLatin1Char local_14b;
  undefined2 local_14a;
  undefined1 *local_148;
  undefined1 *local_140;
  QList<QString> local_138 [32];
  QArrayDataPointer<char16_t> local_118 [32];
  QString local_f8 [32];
  QArrayDataPointer<char16_t> local_d8 [32];
  QList local_b8 [32];
  QString local_98 [32];
  QString local_78 [24];
  undefined1 local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QList<QString>::QList(local_138,(QList *)(this + 0x168));
  QList<QString>::removeAll<QString>(local_138,(QString *)(this + 0x180));
  QList<QString>::prepend(local_138,(QString *)(this + 0x180));
  QString::QString(local_98);
  local_148 = &LAB_0029fb4b_1;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_d8,(QTypedArrayData *)0x0,L"-layout",7);
  QString::QString(local_78,(QArrayDataPointer *)local_d8);
  QLatin1Char::QLatin1Char(&local_14b,',');
  QChar::QChar<QLatin1Char,true>((QChar *)&local_14a,local_14b);
  QListSpecialMethods<QString>::join(local_60,local_138,local_14a);
  QList<QString>::QList(local_b8,local_78,2);
  local_140 = &LAB_0029fb5c;
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_118,(QTypedArrayData *)0x0,L"setxkbmap",9);
  QString::QString(local_f8,(QArrayDataPointer *)local_118);
  QProcess::startDetached(local_f8,local_b8,local_98,(longlong *)0x0);
  QString::~QString(local_f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_118);
  QList<QString>::~QList((QList<QString> *)local_b8);
  this_00 = aQStack_48;
  while (this_00 != local_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_d8);
  QString::~QString(local_98);
  QList<QString>::~QList(local_138);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0019edc2  Settings::syncAutostartDesktops

/* Settings::syncAutostartDesktops(QJsonArray const&) */

void __thiscall Settings::syncAutostartDesktops(Settings *this,QJsonArray *param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  QString *this_00;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  QSet<QString> local_288 [8];
  QJsonObject local_280 [8];
  QJsonArray *local_278;
  QList<QString> *local_270;
  QString *local_268;
  QJsonValueConstRef *local_260;
  undefined *local_258;
  undefined *local_250;
  undefined1 *local_248;
  undefined1 *local_240;
  undefined1 *local_238;
  undefined1 *local_230;
  undefined1 *local_228;
  undefined1 *local_220;
  undefined1 *local_218;
  undefined1 *local_210;
  undefined1 *local_208;
  wchar16 *local_200;
  const_iterator local_1f8 [16];
  const_iterator local_1e8 [16];
  QString local_1d8 [32];
  QJsonValueConstRef local_1b8 [32];
  QString local_198 [32];
  QString local_178 [32];
  QString local_158 [32];
  QString local_138 [32];
  undefined4 local_118 [8];
  ulong local_f8 [4];
  ulong local_d8 [4];
  undefined4 local_b8 [8];
  undefined8 local_98 [4];
  undefined1 local_78 [2] [16];
  QString local_58 [24];
  long local_40 [2];
  
  local_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  local_258 = &DAT_0029fb70;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"/.config/autostart",
             0x12);
  QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
  QDir::homePath();
  ::operator+(local_1d8,(QString *)local_b8);
  QString::~QString((QString *)local_b8);
  QString::~QString((QString *)local_78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
  QString::QString((QString *)local_78);
  QDir::QDir((QDir *)local_b8,(QString *)local_78);
  std::optional<QFlags<QFileDevice::Permission>>::optional(local_98);
  QDir::mkpath(local_b8,local_1d8,local_98[0]);
  QDir::~QDir((QDir *)local_b8);
  QString::~QString((QString *)local_78);
  if ((syncAutostartDesktops(QJsonArray_const&)::nonword == '\0') &&
     (iVar3 = __cxa_guard_acquire(&syncAutostartDesktops(QJsonArray_const&)::nonword), iVar3 != 0))
  {
    QFlags<QRegularExpression::PatternOption>::QFlags
              ((QFlags<QRegularExpression::PatternOption> *)local_b8,0);
    local_250 = &DAT_0029fb96;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"[^A-Za-z0-9]+",0xd);
    QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
    QRegularExpression::QRegularExpression
              ((QRegularExpression *)&syncAutostartDesktops(QJsonArray_const&)::nonword,local_78,
               local_b8[0]);
    __cxa_atexit(QRegularExpression::~QRegularExpression,
                 &syncAutostartDesktops(QJsonArray_const&)::nonword,&__dso_handle);
    __cxa_guard_release(&syncAutostartDesktops(QJsonArray_const&)::nonword);
    QString::~QString((QString *)local_78);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
  }
  QSet<QString>::QSet(local_288);
  local_278 = param_1;
  local_1f8 = (const_iterator  [16])QJsonArray::begin(param_1);
  local_1e8 = (const_iterator  [16])QJsonArray::end(local_278);
  do {
    cVar2 = ::operator!=(local_1f8,local_1e8);
    if (cVar2 == '\0') {
      QDir::QDir((QDir *)local_d8,local_1d8);
      QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_f8,0xffffffff);
      QFlags<QDir::Filter>::QFlags((QFlags<QDir::Filter> *)local_118,2);
      local_200 = L"ncde-auto-*.desktop";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,
                 L"ncde-auto-*.desktop",0x13);
      QString::QString(local_58,(QArrayDataPointer *)local_98);
      QList<QString>::QList(local_78,local_58,1);
      QDir::entryList(local_b8,local_d8,local_78,local_118[0],(undefined4)local_f8[0]);
      QList<QString>::~QList((QList<QString> *)local_78);
      this_00 = (QString *)local_40;
      while (this_00 != local_58) {
        this_00 = this_00 + -0x18;
        QString::~QString(this_00);
      }
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
      QDir::~QDir((QDir *)local_d8);
      local_270 = (QList<QString> *)local_b8;
      local_f8[0] = QList<QString>::begin(local_270);
      local_d8[0] = QList<QString>::end(local_270);
      while( true ) {
        cVar2 = QList<QString>::const_iterator::operator!=((const_iterator *)local_f8,local_d8[0]);
        if (cVar2 == '\0') break;
        local_268 = (QString *)QList<QString>::const_iterator::operator*((const_iterator *)local_f8)
        ;
        cVar2 = QSet<QString>::contains(local_288,local_268);
        if (cVar2 != '\x01') {
          QLatin1Char::QLatin1Char((QLatin1Char *)local_138,'/');
          QChar::QChar<QLatin1Char,true>((QChar *)local_118,local_138[0]);
          ::operator+(local_98,local_1d8,(undefined2)local_118[0]);
          ::operator+((QString *)local_78,(QString *)local_98);
          QFile::remove((QString *)local_78);
          QString::~QString((QString *)local_78);
          QString::~QString((QString *)local_98);
        }
        QList<QString>::const_iterator::operator++((const_iterator *)local_f8);
      }
      QList<QString>::~QList((QList<QString> *)local_b8);
      QSet<QString>::~QSet(local_288);
      QString::~QString(local_1d8);
      if (local_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return;
    }
    auVar4 = QJsonArray::const_iterator::operator*(local_1f8);
    local_78[0] = auVar4;
    QJsonValueConstRef::operator_cast_to_QJsonValue(local_1b8);
    local_260 = local_1b8;
    QJsonValue::toObject();
    local_248 = &LAB_0029e187_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"name",4);
    QString::QString((QString *)local_98,(QArrayDataPointer *)local_b8);
    QJsonObject::value((QString *)local_78);
    QJsonValue::toString();
    QJsonValue::~QJsonValue((QJsonValue *)local_78);
    QString::~QString((QString *)local_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
    local_240 = &LAB_0029fbb1_1;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"command",7);
    QString::QString((QString *)local_98,(QArrayDataPointer *)local_b8);
    QJsonObject::value((QString *)local_78);
    QJsonValue::toString();
    QJsonValue::~QJsonValue((QJsonValue *)local_78);
    QString::~QString((QString *)local_98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
    cVar2 = QString::isEmpty(local_198);
    if (cVar2 == '\0') {
      cVar2 = QString::isEmpty(local_178);
      if (cVar2 != '\0') goto LAB_0019f20b;
      bVar1 = false;
    }
    else {
LAB_0019f20b:
      bVar1 = true;
    }
    if (!bVar1) {
      local_238 = &LAB_0029f717_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"enabled",7);
      QString::QString((QString *)local_98,(QArrayDataPointer *)local_b8);
      QJsonObject::value((QString *)local_78);
      cVar2 = QJsonValue::toBool(SUB81(local_78,0));
      QJsonValue::~QJsonValue((QJsonValue *)local_78);
      QString::~QString((QString *)local_98);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
      QString::QString(local_158,local_198);
      local_230 = &LAB_0029fbc1_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"-",1);
      QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
      QString::replace((QRegularExpression *)local_158,
                       (QString *)&syncAutostartDesktops(QJsonArray_const&)::nonword);
      QString::~QString((QString *)local_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
      local_220 = &LAB_0029fbc1_5;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L".desktop",8);
      QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
      local_228 = &LAB_0029fbd8;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,L"ncde-auto-",10);
      QString::QString((QString *)local_d8,(QArrayDataPointer *)local_f8);
      ::operator+((QString *)local_b8,(QString *)local_d8);
      ::operator+(local_138,(QString *)local_b8);
      QString::~QString((QString *)local_b8);
      QString::~QString((QString *)local_d8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
      QString::~QString((QString *)local_78);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
      QSet<QString>::insert((QString *)local_78);
      local_218 = &LAB_0029fbef_1;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_f8,(QTypedArrayData *)0x0,
                 L"[Desktop Entry]\nType=Application\nName=%1\nExec=%2\nX-GNOME-Autostart-enabled=%3\n"
                 ,0x4e);
      QString::QString((QString *)local_d8,(QArrayDataPointer *)local_f8);
      if (cVar2 == '\0') {
        local_208 = &LAB_00299b2d_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_98,(QTypedArrayData *)0x0,L"false",5);
        QString::QString((QString *)local_78,(QArrayDataPointer *)local_98);
      }
      else {
        local_210 = &LAB_00299b23_1;
        QArrayDataPointer<char16_t>::QArrayDataPointer
                  ((QArrayDataPointer<char16_t> *)local_b8,(QTypedArrayData *)0x0,L"true",4);
        QString::QString((QString *)local_78,(QArrayDataPointer *)local_b8);
      }
      QString::arg<QString_const&,QString_const&,QString>
                ((QString *)local_118,(QString *)local_d8,local_198);
      QString::~QString((QString *)local_78);
      if (cVar2 == '\0') {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_98);
      }
      else {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_b8);
      }
      QString::~QString((QString *)local_d8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_f8);
      QLatin1Char::QLatin1Char((QLatin1Char *)local_f8,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)local_d8,local_f8[0] & 0xff);
      ::operator+(local_98,local_1d8,local_d8[0] & 0xffff);
      ::operator+((QString *)local_78,(QString *)local_98);
      QSaveFile::QSaveFile((QSaveFile *)local_b8,(QString *)local_78,(QObject *)0x0);
      QString::~QString((QString *)local_78);
      QString::~QString((QString *)local_98);
      QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_78,2)
      ;
      cVar2 = QSaveFile::open(local_b8,local_78[0]._0_8_ & 0xffffffff);
      if (cVar2 != '\0') {
        QString::toUtf8((QString *)local_78);
        QIODevice::write((QByteArray *)local_b8);
        QByteArray::~QByteArray((QByteArray *)local_78);
        QSaveFile::commit();
      }
      QSaveFile::~QSaveFile((QSaveFile *)local_b8);
      QString::~QString((QString *)local_118);
      QString::~QString(local_138);
      QString::~QString(local_158);
    }
    QString::~QString(local_178);
    QString::~QString(local_198);
    QJsonObject::~QJsonObject(local_280);
    QJsonValue::~QJsonValue((QJsonValue *)local_1b8);
    QJsonArray::const_iterator::operator++(local_1f8);
  } while( true );
}



// ==== 0019feae  Settings::saveFontsJson

/* Settings::saveFontsJson() */

void __thiscall Settings::saveFontsJson(Settings *this)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_98;
  wchar16 *local_90;
  QArrayDataPointer<char16_t> local_88 [32];
  QString local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_98 = 0;
  ::QVariant::QVariant(local_48,(QString *)(this + 0x2b0));
  QString::QString(local_68,"fontFamily");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(int *)(this + 0x42c));
  QString::QString(local_68,"fontWeight");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x430]);
  QString::QString(local_68,"fontItalic");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x438));
  QString::QString(local_68,"fontSizeScale");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x440));
  QString::QString(local_68,"letterSpacing");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x448));
  QString::QString(local_68,"lineHeight");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x450));
  QString::QString(local_68,"uiScale");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x458));
  QString::QString(local_68,"textColor");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x470]);
  QString::QString(local_68,"textOutlineEnabled");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x478));
  QString::QString(local_68,"textOutlineColor");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x490));
  QString::QString(local_68,"textOutlineWidth");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(bool)this[0x498]);
  QString::QString(local_68,"textShadowEnabled");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,(QString *)(this + 0x4a0));
  QString::QString(local_68,"textShadowColor");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x4b8));
  QString::QString(local_68,"textShadowOffsetX");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x4c0));
  QString::QString(local_68,"textShadowOffsetY");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  ::QVariant::QVariant(local_48,*(double *)(this + 0x4c8));
  QString::QString(local_68,"textShadowRadius");
  pQVar1 = (QVariant *)
           QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_98,local_68);
  ::QVariant::operator=(pQVar1,local_48);
  QString::~QString(local_68);
  ::QVariant::~QVariant(local_48);
  local_90 = L"fonts";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"fonts",5);
  QString::QString(local_68,(QArrayDataPointer *)local_88);
  Lelan::writeConfig(local_68,(QMap *)&local_98);
  QString::~QString(local_68);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
  fontChanged(this);
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a0a3a  Settings::~Settings

/* Settings::~Settings() */

void __thiscall Settings::~Settings(Settings *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bc40;
  QString::~QString((QString *)(this + 0x4a0));
  QString::~QString((QString *)(this + 0x478));
  QString::~QString((QString *)(this + 0x458));
  QFileSystemWatcher::~QFileSystemWatcher((QFileSystemWatcher *)(this + 0x418));
  QString::~QString((QString *)(this + 0x3e0));
  QString::~QString((QString *)(this + 0x3c0));
  QString::~QString((QString *)(this + 0x3a8));
  QString::~QString((QString *)(this + 0x390));
  QString::~QString((QString *)(this + 0x370));
  QString::~QString((QString *)(this + 0x358));
  QString::~QString((QString *)(this + 0x340));
  QString::~QString((QString *)(this + 0x328));
  QString::~QString((QString *)(this + 0x310));
  QString::~QString((QString *)(this + 0x2f8));
  QString::~QString((QString *)(this + 0x2e0));
  QString::~QString((QString *)(this + 0x2c8));
  QString::~QString((QString *)(this + 0x2b0));
  QString::~QString((QString *)(this + 0x290));
  QString::~QString((QString *)(this + 0x278));
  QString::~QString((QString *)(this + 600));
  QList<QString>::~QList((QList<QString> *)(this + 0x238));
  QString::~QString((QString *)(this + 0x220));
  QString::~QString((QString *)(this + 0x208));
  QString::~QString((QString *)(this + 0x1e0));
  QString::~QString((QString *)(this + 0x1c8));
  QString::~QString((QString *)(this + 0x1b0));
  QString::~QString((QString *)(this + 0x198));
  QString::~QString((QString *)(this + 0x180));
  QList<QString>::~QList((QList<QString> *)(this + 0x168));
  QString::~QString((QString *)(this + 0x150));
  QString::~QString((QString *)(this + 0x138));
  QString::~QString((QString *)(this + 0x120));
  QString::~QString((QString *)(this + 0x108));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0xf0));
  QString::~QString((QString *)(this + 0x68));
  QString::~QString((QString *)(this + 0x50));
  QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)(this + 0x30));
  QList<QVariant>::~QList((QList<QVariant> *)(this + 0x18));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a0d08  Settings::~Settings

/* Settings::~Settings() */

void __thiscall Settings::~Settings(Settings *this)

{
  ~Settings(this);
  operator_delete(this,0x4d0);
  return;
}



// ==== 001f8bbc  Settings::setLelan(Lelan*)::{lambda()#1}::operator()

/* Settings::setLelan(Lelan*)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall Settings::setLelan(Lelan*)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  long in_FS_OFFSET;
  QVariant local_b8 [8];
  wchar16 *local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  QVariant local_68 [32];
  QString local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(char *)(*(long *)this + 0x39) == '\x01') && (*(long *)(*(long *)this + 0xb0) != 0)) {
    Lelan::location();
    ::QVariant::QVariant(local_68);
    local_b0 = L"night";
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"night",5);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    QMap<QString,QVariant>::value(local_48,local_b8);
    bVar1 = (bool)::QVariant::toBool();
    ::QVariant::~QVariant((QVariant *)local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_68);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)local_b8);
    if (bVar1 != (bool)*(char *)(*(long *)this + 0x38)) {
      setNightLightOn(*(Settings **)this,bVar1);
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f8dae  Settings::setLelan

/* Settings::setLelan(Lelan*) */

void __thiscall Settings::setLelan(Settings *this,Lelan *param_1)

{
  long in_FS_OFFSET;
  Settings *local_50;
  code *local_48;
  undefined8 local_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  *(Lelan **)(this + 0xb0) = param_1;
  if (*(long *)(this + 0xb0) != 0) {
    local_50 = this;
    QObject::connect<void(Lelan::*)(),Settings::setLelan(Lelan*)::_lambda()_1_>
              (&local_48,*(undefined8 *)(this + 0xb0),Lelan::placeNameChanged,0,this,&local_50,0);
    QMetaObject::Connection::~Connection((Connection *)&local_48);
  }
  if (*(long *)(this + 0xb0) != 0) {
    local_48 = applyPowerSettings;
    local_40 = 0;
    QObject::connect<void(Lelan::*)(),void(Settings::*)()>
              (&local_50,*(undefined8 *)(this + 0xb0),Lelan::batteryChanged,0,this,&local_48,0);
    QMetaObject::Connection::~Connection((Connection *)&local_50);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f8ee0  Settings::setAnimPolicy

/* Settings::setAnimPolicy(QObject*) */

void __thiscall Settings::setAnimPolicy(Settings *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_18 [8];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  *(QObject **)(this + 0xb8) = param_1;
  if (param_1 != (QObject *)0x0) {
    QObject::connect(local_18,param_1,"2changed()",this,"1onScreenIdleChanged()",0);
    QMetaObject::Connection::~Connection(local_18);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


