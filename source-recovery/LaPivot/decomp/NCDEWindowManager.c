// Ghidra decompile of LaPivot.oracle — class/namespace NCDEWindowManager (108 functions). Raw; not source.

// ==== 001457c0  NCDEWindowManager::qt_static_metacall

/* NCDEWindowManager::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void NCDEWindowManager::qt_static_metacall
               (NCDEWindowManager *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QString *this;
  undefined1 uVar1;
  bool bVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  undefined4 local_58 [6];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0x2b) {
      switchDesktop(param_1,**(int **)(param_4 + 8));
    }
    else if (param_3 < 0x2c) {
      if (param_3 == 0x2a) {
        destroyFrameWindow(param_1,**(uint **)(param_4 + 8));
      }
      else if (param_3 < 0x2b) {
        if (param_3 == 0x29) {
          registerFrameWindowQml
                    (param_1,**(uint **)(param_4 + 8),(QObject *)**(undefined8 **)(param_4 + 0x10));
        }
        else if (param_3 < 0x2a) {
          if (param_3 == 0x28) {
            systemCommand(param_1,*(QString **)(param_4 + 8));
          }
          else if (param_3 < 0x29) {
            if (param_3 == 0x27) {
              closeWindow(param_1,**(uint **)(param_4 + 8));
            }
            else if (param_3 < 0x28) {
              if (param_3 == 0x26) {
                setMaximized(param_1,**(uint **)(param_4 + 8),
                             *(bool *)*(undefined8 *)(param_4 + 0x10));
              }
              else if (param_3 < 0x27) {
                if (param_3 == 0x25) {
                  uVar1 = isMaximized(param_1,**(uint **)(param_4 + 8));
                  local_58[0] = CONCAT31(local_58[0]._1_3_,uVar1);
                  if (*(long *)param_4 != 0) {
                    **(undefined1 **)param_4 = uVar1;
                  }
                }
                else if (param_3 < 0x26) {
                  if (param_3 == 0x24) {
                    setTiled(param_1,**(uint **)(param_4 + 8),
                             *(bool *)*(undefined8 *)(param_4 + 0x10));
                  }
                  else if (param_3 < 0x25) {
                    if (param_3 == 0x23) {
                      moveTiledWindow(param_1,**(uint **)(param_4 + 8),**(int **)(param_4 + 0x10),
                                      **(int **)(param_4 + 0x18),**(int **)(param_4 + 0x20),
                                      **(int **)(param_4 + 0x28));
                    }
                    else if (param_3 < 0x24) {
                      if (param_3 == 0x22) {
                        resizeWindow(param_1,**(uint **)(param_4 + 8),**(int **)(param_4 + 0x10),
                                     **(int **)(param_4 + 0x18));
                      }
                      else if (param_3 < 0x23) {
                        if (param_3 == 0x21) {
                          moveWindow(param_1,**(uint **)(param_4 + 8),**(int **)(param_4 + 0x10),
                                     **(int **)(param_4 + 0x18));
                        }
                        else if (param_3 < 0x22) {
                          if (param_3 == 0x20) {
                            unminimizeWindow(param_1,**(uint **)(param_4 + 8));
                          }
                          else if (param_3 < 0x21) {
                            if (param_3 == 0x1f) {
                              minimizeWindow(param_1,**(uint **)(param_4 + 8));
                            }
                            else if (param_3 < 0x20) {
                              if (param_3 == 0x1e) {
                                activateWindow(param_1,**(uint **)(param_4 + 8));
                              }
                              else if (param_3 < 0x1f) {
                                if (param_3 == 0x1d) {
                                  uVar1 = isMaximizedForName(param_1,*(QString **)(param_4 + 8));
                                  local_58[0] = CONCAT31(local_58[0]._1_3_,uVar1);
                                  if (*(long *)param_4 != 0) {
                                    **(undefined1 **)param_4 = uVar1;
                                  }
                                }
                                else if (param_3 < 0x1e) {
                                  if (param_3 == 0x1c) {
                                    uVar1 = isActiveForName(param_1,*(QString **)(param_4 + 8));
                                    local_58[0] = CONCAT31(local_58[0]._1_3_,uVar1);
                                    if (*(long *)param_4 != 0) {
                                      **(undefined1 **)param_4 = uVar1;
                                    }
                                  }
                                  else if (param_3 < 0x1d) {
                                    if (param_3 == 0x1b) {
                                      uVar1 = isMinimizedForName(param_1,*(QString **)(param_4 + 8))
                                      ;
                                      local_58[0] = CONCAT31(local_58[0]._1_3_,uVar1);
                                      if (*(long *)param_4 != 0) {
                                        **(undefined1 **)param_4 = uVar1;
                                      }
                                    }
                                    else if (param_3 < 0x1c) {
                                      if (param_3 == 0x1a) {
                                        uVar1 = hasWindowForName(param_1,*(QString **)(param_4 + 8))
                                        ;
                                        local_58[0] = CONCAT31(local_58[0]._1_3_,uVar1);
                                        if (*(long *)param_4 != 0) {
                                          **(undefined1 **)param_4 = uVar1;
                                        }
                                      }
                                      else if (param_3 < 0x1b) {
                                        if (param_3 == 0x19) {
                                          local_58[0] = winIdForName(param_1,*(QString **)
                                                                              (param_4 + 8));
                                          if (*(long *)param_4 != 0) {
                                            **(undefined4 **)param_4 = local_58[0];
                                          }
                                        }
                                        else if (param_3 < 0x1a) {
                                          if (param_3 == 0x18) {
                                            local_58[0] = rowForClient(param_1,**(uint **)(param_4 +
                                                                                          8));
                                            if (*(long *)param_4 != 0) {
                                              **(undefined4 **)param_4 = local_58[0];
                                            }
                                          }
                                          else if (param_3 < 0x19) {
                                            if (param_3 == 0x17) {
                                              setWindowType(param_1,**(uint **)(param_4 + 8),
                                                            **(uint **)(param_4 + 0x10));
                                            }
                                            else if (param_3 < 0x18) {
                                              if (param_3 == 0x16) {
                                                local_58[0] = atomNetWmWindowTypeTooltip(param_1);
                                                if (*(long *)param_4 != 0) {
                                                  **(undefined4 **)param_4 = local_58[0];
                                                }
                                              }
                                              else if (param_3 < 0x17) {
                                                if (param_3 == 0x15) {
                                                  local_58[0] = atomNetWmWindowTypePopupMenu
                                                                          (param_1);
                                                  if (*(long *)param_4 != 0) {
                                                    **(undefined4 **)param_4 = local_58[0];
                                                  }
                                                }
                                                else if (param_3 < 0x16) {
                                                  if (param_3 == 0x14) {
                                                    local_58[0] = atomNetWmWindowTypeDock(param_1);
                                                    if (*(long *)param_4 != 0) {
                                                      **(undefined4 **)param_4 = local_58[0];
                                                    }
                                                  }
                                                  else if (param_3 < 0x15) {
                                                    if (param_3 == 0x13) {
                                                      local_58[0] = atomNetWmWindowTypeDesktop
                                                                              (param_1);
                                                      if (*(long *)param_4 != 0) {
                                                        **(undefined4 **)param_4 = local_58[0];
                                                      }
                                                    }
                                                    else if (param_3 < 0x14) {
                                                      if (param_3 == 0x12) {
                                                        local_58[0] = atomNetWmWindowType(param_1);
                                                        if (*(long *)param_4 != 0) {
                                                          **(undefined4 **)param_4 = local_58[0];
                                                        }
                                                      }
                                                      else if (param_3 < 0x13) {
                                                        if (param_3 == 0x11) {
                                                          local_58[0] = screenHeight(param_1);
                                                          if (*(long *)param_4 != 0) {
                                                            **(undefined4 **)param_4 = local_58[0];
                                                          }
                                                        }
                                                        else if (param_3 < 0x12) {
                                                          if (param_3 == 0x10) {
                                                            local_58[0] = screenWidth(param_1);
                                                            if (*(long *)param_4 != 0) {
                                                              **(undefined4 **)param_4 = local_58[0]
                                                              ;
                                                            }
                                                          }
                                                          else if (param_3 < 0x11) {
                                                            if (param_3 == 0xf) {
                                                              setSnapZone(param_1,**(int **)(param_4
                                                                                            + 8));
                                                            }
                                                            else if (param_3 < 0x10) {
                                                              if (param_3 == 0xe) {
                                                                invokeAppMenu(param_1,**(int **)(
                                                  param_4 + 8));
                                                  }
                                                  else if (param_3 < 0xf) {
                                                    if (param_3 == 0xd) {
                                                      screensaverIdleReached(param_1);
                                                    }
                                                    else if (param_3 < 0xe) {
                                                      if (param_3 == 0xc) {
                                                        windowClosed(param_1,**(uint **)(param_4 + 8
                                                                                        ));
                                                      }
                                                      else if (param_3 < 0xd) {
                                                        if (param_3 == 0xb) {
                                                          QString::QString((QString *)local_58,
                                                                           *(QString **)
                                                                            (param_4 + 0x10));
                                                          windowTierNeeded(param_1,**(undefined4 **)
                                                                                     (param_4 + 8),
                                                                           local_58);
                                                          QString::~QString((QString *)local_58);
                                                        }
                                                        else if (param_3 < 0xc) {
                                                          if (param_3 == 10) {
                                                            screenConfigChanged(param_1,**(int **)(
                                                  param_4 + 8),**(int **)(param_4 + 0x10));
                                                  }
                                                  else if (param_3 < 0xb) {
                                                    if (param_3 == 9) {
                                                      coveringCountChanged(param_1);
                                                    }
                                                    else if (param_3 < 10) {
                                                      if (param_3 == 8) {
                                                        windowStateChanged(param_1);
                                                      }
                                                      else if (param_3 < 9) {
                                                        if (param_3 == 7) {
                                                          windowRemoved(param_1,**(uint **)(param_4 
                                                  + 8));
                                                  }
                                                  else if (param_3 < 8) {
                                                    if (param_3 == 6) {
                                                      windowAdded(param_1,**(uint **)(param_4 + 8),
                                                                  **(int **)(param_4 + 0x10),
                                                                  **(int **)(param_4 + 0x18),
                                                                  **(int **)(param_4 + 0x20),
                                                                  **(int **)(param_4 + 0x28),
                                                                  *(QString **)(param_4 + 0x30),
                                                                  *(QString **)(param_4 + 0x38));
                                                    }
                                                    else if (param_3 < 7) {
                                                      if (param_3 == 5) {
                                                        anyWindowMapped(param_1);
                                                      }
                                                      else if (param_3 < 6) {
                                                        if (param_3 == 4) {
                                                          snapZoneChanged(param_1);
                                                        }
                                                        else if (param_3 < 5) {
                                                          if (param_3 == 3) {
                                                            activeAppMenusChanged(param_1);
                                                          }
                                                          else if (param_3 < 4) {
                                                            if (param_3 == 2) {
                                                              activeIndexChanged(param_1);
                                                            }
                                                            else if (param_3 < 3) {
                                                              if (param_3 == 0) {
                                                                countChanged(param_1);
                                                              }
                                                              else if (param_3 == 1) {
                                                                mousePosChanged(param_1);
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
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
     ((((((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                             (param_4,(void **)countChanged,(_func_void *)0x0,0), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                             (param_4,(void **)mousePosChanged,(_func_void *)0x0,1), !bVar2)) &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                            (param_4,(void **)activeIndexChanged,(_func_void *)0x0,2), !bVar2)) &&
        ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                            (param_4,(void **)activeAppMenusChanged,(_func_void *)0x0,3), !bVar2 &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                            (param_4,(void **)snapZoneChanged,(_func_void *)0x0,4), !bVar2)))) &&
       ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                           (param_4,(void **)anyWindowMapped,(_func_void *)0x0,5), !bVar2 &&
        ((bVar2 = QtMocHelpers::
                  indexOfMethod<void(NCDEWindowManager::*)(unsigned_int,int,int,int,int,QString_const&,QString_const&)>
                            (param_4,(void **)windowAdded,
                             (_func_void_uint_int_int_int_int_QString_ptr_QString_ptr *)0x0,6),
         !bVar2 && (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)(unsigned_int)>
                                      (param_4,(void **)windowRemoved,(_func_void_uint *)0x0,7),
                   !bVar2)))))) &&
      ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                          (param_4,(void **)windowStateChanged,(_func_void *)0x0,8), !bVar2 &&
       ((((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                             (param_4,(void **)coveringCountChanged,(_func_void *)0x0,9), !bVar2 &&
          (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)(int,int)>
                             (param_4,(void **)screenConfigChanged,(_func_void_int_int *)0x0,10),
          !bVar2)) &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)(unsigned_int,QString)>
                            (param_4,(void **)windowTierNeeded,(_func_void_uint_QString *)0x0,0xb),
         !bVar2)) &&
        ((bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)(unsigned_int)>
                            (param_4,(void **)windowClosed,(_func_void_uint *)0x0,0xc), !bVar2 &&
         (bVar2 = QtMocHelpers::indexOfMethod<void(NCDEWindowManager::*)()>
                            (param_4,(void **)screensaverIdleReached,(_func_void *)0x0,0xd), !bVar2)
         ))))))))) {
    if (param_2 == 1) {
      this = *(QString **)param_4;
      if (param_3 == 6) {
        uVar3 = snapZone(param_1);
        *(undefined4 *)this = uVar3;
      }
      else if (param_3 < 7) {
        if (param_3 == 5) {
          activeAppMenus();
          QString::operator=(this,(QString *)local_58);
          QString::~QString((QString *)local_58);
        }
        else if (param_3 < 6) {
          if (param_3 == 4) {
            uVar3 = activeIndex(param_1);
            *(undefined4 *)this = uVar3;
          }
          else if (param_3 < 5) {
            if (param_3 == 3) {
              uVar3 = mouseY(param_1);
              *(undefined4 *)this = uVar3;
            }
            else if (param_3 < 4) {
              if (param_3 == 2) {
                uVar3 = mouseX(param_1);
                *(undefined4 *)this = uVar3;
              }
              else if (param_3 < 3) {
                if (param_3 == 0) {
                  uVar3 = count(param_1);
                  *(undefined4 *)this = uVar3;
                }
                else if (param_3 == 1) {
                  uVar3 = coveringCount(param_1);
                  *(undefined4 *)this = uVar3;
                }
              }
            }
          }
        }
      }
    }
    if ((param_2 == 2) && (param_3 == 6)) {
      setSnapZone(param_1,**(int **)param_4);
    }
  }
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00146990  NCDEWindowManager::metaObject

/* NCDEWindowManager::metaObject() const */

undefined1 * __thiscall NCDEWindowManager::metaObject(NCDEWindowManager *this)

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



// ==== 001469d8  NCDEWindowManager::qt_metacast

/* NCDEWindowManager::qt_metacast(char const*) */

NCDEWindowManager * __thiscall NCDEWindowManager::qt_metacast(NCDEWindowManager *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (NCDEWindowManager *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"NCDEWindowManager");
    if (iVar1 != 0) {
      iVar1 = strcmp(param_1,"QAbstractNativeEventFilter");
      if (iVar1 == 0) {
        this = this + 0x10;
      }
      else {
        this = (NCDEWindowManager *)QAbstractListModel::qt_metacast((char *)this);
      }
    }
  }
  return this;
}



// ==== 00146a50  NCDEWindowManager::qt_metacall

/* NCDEWindowManager::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall
NCDEWindowManager::qt_metacall
          (NCDEWindowManager *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QAbstractListModel::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 0x2c) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -0x2c;
    }
    if (param_2 == 7) {
      if (local_28 < 0x2c) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -0x2c;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -7;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00146b46  NCDEWindowManager::countChanged

/* NCDEWindowManager::countChanged() */

void __thiscall NCDEWindowManager::countChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 00146b72  NCDEWindowManager::mousePosChanged

/* NCDEWindowManager::mousePosChanged() */

void __thiscall NCDEWindowManager::mousePosChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,1,(void **)0x0);
  return;
}



// ==== 00146b9e  NCDEWindowManager::activeIndexChanged

/* NCDEWindowManager::activeIndexChanged() */

void __thiscall NCDEWindowManager::activeIndexChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,2,(void **)0x0);
  return;
}



// ==== 00146bca  NCDEWindowManager::activeAppMenusChanged

/* NCDEWindowManager::activeAppMenusChanged() */

void __thiscall NCDEWindowManager::activeAppMenusChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,3,(void **)0x0);
  return;
}



// ==== 00146bf6  NCDEWindowManager::snapZoneChanged

/* NCDEWindowManager::snapZoneChanged() */

void __thiscall NCDEWindowManager::snapZoneChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,4,(void **)0x0);
  return;
}



// ==== 00146c22  NCDEWindowManager::anyWindowMapped

/* NCDEWindowManager::anyWindowMapped() */

void __thiscall NCDEWindowManager::anyWindowMapped(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,5,(void **)0x0);
  return;
}



// ==== 00146c4e  NCDEWindowManager::windowAdded

/* NCDEWindowManager::windowAdded(unsigned int, int, int, int, int, QString const&, QString const&)
    */

void __thiscall
NCDEWindowManager::windowAdded
          (NCDEWindowManager *this,uint param_1,int param_2,int param_3,int param_4,int param_5,
          QString *param_6,QString *param_7)

{
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  NCDEWindowManager *local_10;
  
  local_24 = param_5;
  local_20 = param_4;
  local_1c = param_3;
  local_18 = param_2;
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,unsigned_int,int,int,int,int,QString,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,6,(void *)0x0,&local_14,&local_18,
             &local_1c,&local_20,&local_24,param_6,param_7);
  return;
}



// ==== 00146cb6  NCDEWindowManager::windowRemoved

/* NCDEWindowManager::windowRemoved(unsigned int) */

void __thiscall NCDEWindowManager::windowRemoved(NCDEWindowManager *this,uint param_1)

{
  uint local_14;
  NCDEWindowManager *local_10;
  
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,unsigned_int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,7,(void *)0x0,&local_14);
  return;
}



// ==== 00146cec  NCDEWindowManager::windowStateChanged

/* NCDEWindowManager::windowStateChanged() */

void __thiscall NCDEWindowManager::windowStateChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,8,(void **)0x0);
  return;
}



// ==== 00146d18  NCDEWindowManager::coveringCountChanged

/* NCDEWindowManager::coveringCountChanged() */

void __thiscall NCDEWindowManager::coveringCountChanged(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,9,(void **)0x0);
  return;
}



// ==== 00146d44  NCDEWindowManager::screenConfigChanged

/* NCDEWindowManager::screenConfigChanged(int, int) */

void __thiscall
NCDEWindowManager::screenConfigChanged(NCDEWindowManager *this,int param_1,int param_2)

{
  int local_18;
  int local_14;
  NCDEWindowManager *local_10;
  
  local_18 = param_2;
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,int,int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,10,(void *)0x0,&local_14,&local_18);
  return;
}



// ==== 00146d84  NCDEWindowManager::windowTierNeeded

/* NCDEWindowManager::windowTierNeeded(unsigned int, QString) */

void __thiscall
NCDEWindowManager::windowTierNeeded(NCDEWindowManager *this,uint param_1,QString *param_3)

{
  uint local_14;
  NCDEWindowManager *local_10;
  
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,unsigned_int,QString>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0xb,(void *)0x0,&local_14,param_3);
  return;
}



// ==== 00146dc6  NCDEWindowManager::windowClosed

/* NCDEWindowManager::windowClosed(unsigned int) */

void __thiscall NCDEWindowManager::windowClosed(NCDEWindowManager *this,uint param_1)

{
  uint local_14;
  NCDEWindowManager *local_10;
  
  local_14 = param_1;
  local_10 = this;
  QMetaObject::activate<void,unsigned_int>
            ((QObject *)this,(QMetaObject *)staticMetaObject,0xc,(void *)0x0,&local_14);
  return;
}



// ==== 00146dfc  NCDEWindowManager::screensaverIdleReached

/* NCDEWindowManager::screensaverIdleReached() */

void __thiscall NCDEWindowManager::screensaverIdleReached(NCDEWindowManager *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0xd,(void **)0x0);
  return;
}



// ==== 001772f6  NCDEWindowManager::NCDEWindowManager

/* NCDEWindowManager::NCDEWindowManager(QObject*) */

void __thiscall NCDEWindowManager::NCDEWindowManager(NCDEWindowManager *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_60 [8];
  code *local_58;
  undefined8 local_50;
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QAbstractListModel::QAbstractListModel((QAbstractListModel *)this,param_1);
  QAbstractNativeEventFilter::QAbstractNativeEventFilter
            ((QAbstractNativeEventFilter *)(this + 0x10));
  *(undefined ***)this = &PTR_metaObject_0032be70;
  *(undefined **)(this + 0x10) = &DAT_0032c010;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 0xffffffff;
  *(undefined4 *)(this + 0x44) = 0;
  this[0x48] = (NCDEWindowManager)0x0;
  this[0x49] = (NCDEWindowManager)0x0;
  this[0x4a] = (NCDEWindowManager)0x0;
  this[0x4b] = (NCDEWindowManager)0x0;
  this[0x4c] = (NCDEWindowManager)0x0;
  this[0x4d] = (NCDEWindowManager)0x0;
  this[0x4e] = (NCDEWindowManager)0x0;
  *(undefined8 *)(this + 0x50) = 0;
  QTimer::QTimer((QTimer *)(this + 0x58),(QObject *)0x0);
  QTimer::QTimer((QTimer *)(this + 0x68),(QObject *)0x0);
  this[0x78] = (NCDEWindowManager)0x0;
  *(undefined8 *)(this + 0x80) = 0;
  this[0x88] = (NCDEWindowManager)0x0;
  QList<NCDEWindowManager::WindowEntry>::QList
            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
  *(undefined4 *)(this + 0xa8) = 0;
  this[0xac] = (NCDEWindowManager)0x0;
  QHash<unsigned_int,QObject*>::QHash((QHash<unsigned_int,QObject*> *)(this + 0xb0));
  QHash<unsigned_int,QString>::QHash((QHash<unsigned_int,QString> *)(this + 0xb8));
  QHash<unsigned_int,unsigned_int>::QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xc0));
  QHash<unsigned_int,unsigned_int>::QHash((QHash<unsigned_int,unsigned_int> *)(this + 200));
  QHash<unsigned_int,unsigned_int>::QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xd0));
  QHash<unsigned_int,unsigned_int>::QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xd8));
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe4) = 0;
  *(undefined4 *)(this + 0xe8) = 0;
  *(undefined4 *)(this + 0xec) = 0;
  *(undefined4 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0xf4) = 0;
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x10c) = 0;
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 0;
  *(undefined4 *)(this + 0x124) = 0;
  *(undefined4 *)(this + 0x128) = 0;
  *(undefined4 *)(this + 300) = 0;
  *(undefined4 *)(this + 0x130) = 0;
  *(undefined4 *)(this + 0x134) = 0;
  *(undefined4 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x13c) = 0;
  *(undefined4 *)(this + 0x140) = 0;
  *(undefined4 *)(this + 0x144) = 0;
  *(undefined4 *)(this + 0x148) = 0;
  *(undefined4 *)(this + 0x14c) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  local_58 = scheduleCoveringRecount;
  local_50 = 0;
  QObject::connect<void(NCDEWindowManager::*)(),void(NCDEWindowManager::*)()>
            (local_60,this,windowStateChanged,0,this,&local_58,0);
  QMetaObject::Connection::~Connection(local_60);
  local_58 = scheduleCoveringRecount;
  local_50 = 0;
  QObject::connect<void(NCDEWindowManager::*)(),void(NCDEWindowManager::*)()>
            (local_60,this,countChanged,0,this,&local_58,0);
  QMetaObject::Connection::~Connection(local_60);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017784c  NCDEWindowManager::count

/* NCDEWindowManager::count() const */

void __thiscall NCDEWindowManager::count(NCDEWindowManager *this)

{
  QList<NCDEWindowManager::WindowEntry>::size
            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
  return;
}



// ==== 0017786c  NCDEWindowManager::coveringCount

/* NCDEWindowManager::coveringCount() const */

undefined4 __thiscall NCDEWindowManager::coveringCount(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0xa8);
}



// ==== 00177880  NCDEWindowManager::rowCount

/* NCDEWindowManager::rowCount(QModelIndex const&) const */

void NCDEWindowManager::rowCount(QModelIndex *param_1)

{
  QList<NCDEWindowManager::WindowEntry>::size
            ((QList<NCDEWindowManager::WindowEntry> *)(param_1 + 0x90));
  return;
}



// ==== 001778a4  NCDEWindowManager::data

/* NCDEWindowManager::data(QModelIndex const&, int) const */

QModelIndex * NCDEWindowManager::data(QModelIndex *param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  uint *puVar5;
  QString *pQVar6;
  int in_ECX;
  QModelIndex *in_RDX;
  undefined4 in_register_00000034;
  
  iVar3 = QModelIndex::row(in_RDX);
  if (-1 < iVar3) {
    iVar3 = QModelIndex::row(in_RDX);
    lVar4 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)
                       (CONCAT44(in_register_00000034,param_2) + 0x90));
    if (iVar3 < lVar4) {
      bVar1 = false;
      goto LAB_001778fe;
    }
  }
  bVar1 = true;
LAB_001778fe:
  if (bVar1) {
    ::QVariant::QVariant((QVariant *)param_1);
  }
  else {
    iVar3 = QModelIndex::row(in_RDX);
    puVar5 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)
                                (CONCAT44(in_register_00000034,param_2) + 0x90),(long)iVar3);
    if (in_ECX == 0x10b) {
      ::QVariant::QVariant((QVariant *)param_1,*(bool *)((long)puVar5 + 0x62));
    }
    else {
      if (in_ECX < 0x10c) {
        if (in_ECX == 0x10a) {
          cVar2 = QString::isEmpty((QString *)(puVar5 + 6));
          if (cVar2 == '\0') {
            pQVar6 = (QString *)(puVar5 + 6);
          }
          else {
            pQVar6 = (QString *)(puVar5 + 0xc);
          }
          ::QVariant::QVariant((QVariant *)param_1,pQVar6);
          return param_1;
        }
        if (in_ECX < 0x10b) {
          if (in_ECX == 0x109) {
            ::QVariant::QVariant((QVariant *)param_1,*(bool *)((long)puVar5 + 0x61));
            return param_1;
          }
          if (in_ECX < 0x10a) {
            if (in_ECX == 0x108) {
              ::QVariant::QVariant((QVariant *)param_1,SUB41(puVar5[0x18],0));
              return param_1;
            }
            if (in_ECX < 0x109) {
              if (in_ECX == 0x107) {
                ::QVariant::QVariant((QVariant *)param_1,(QString *)(puVar5 + 0xc));
                return param_1;
              }
              if (in_ECX < 0x108) {
                if (in_ECX == 0x106) {
                  ::QVariant::QVariant((QVariant *)param_1,(QString *)(puVar5 + 6));
                  return param_1;
                }
                if (in_ECX < 0x107) {
                  if (in_ECX == 0x105) {
                    ::QVariant::QVariant((QVariant *)param_1,puVar5[5]);
                    return param_1;
                  }
                  if (in_ECX < 0x106) {
                    if (in_ECX == 0x104) {
                      ::QVariant::QVariant((QVariant *)param_1,puVar5[4]);
                      return param_1;
                    }
                    if (in_ECX < 0x105) {
                      if (in_ECX == 0x103) {
                        ::QVariant::QVariant((QVariant *)param_1,puVar5[3]);
                        return param_1;
                      }
                      if (in_ECX < 0x104) {
                        if (in_ECX == 0x101) {
                          ::QVariant::QVariant((QVariant *)param_1,*puVar5);
                          return param_1;
                        }
                        if (in_ECX == 0x102) {
                          ::QVariant::QVariant((QVariant *)param_1,puVar5[2]);
                          return param_1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      ::QVariant::QVariant((QVariant *)param_1);
    }
  }
  return param_1;
}



// ==== 00177cfc  NCDEWindowManager::roleNames

/* NCDEWindowManager::roleNames() const */

NCDEWindowManager * __thiscall NCDEWindowManager::roleNames(NCDEWindowManager *this)

{
  pair<int,QByteArray> *this_00;
  long in_FS_OFFSET;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  pair<int,QByteArray> local_1a8 [32];
  pair<int,QByteArray> local_188 [32];
  pair<int,QByteArray> apStack_168 [32];
  pair<int,QByteArray> apStack_148 [32];
  pair<int,QByteArray> apStack_128 [32];
  pair<int,QByteArray> apStack_108 [32];
  pair<int,QByteArray> apStack_e8 [32];
  pair<int,QByteArray> apStack_c8 [32];
  pair<int,QByteArray> apStack_a8 [32];
  pair<int,QByteArray> apStack_88 [32];
  pair<int,QByteArray> local_68 [32];
  pair<int,QByteArray> apStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_1d4 = 0x101;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[6],true>
            (local_1a8,(Roles *)&local_1d4,"winId");
  local_1d0 = 0x102;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[2],true>
            (local_188,(Roles *)&local_1d0,"x");
  local_1cc = 0x103;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[2],true>
            (apStack_168,(Roles *)&local_1cc,"y");
  local_1c8 = 0x104;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[2],true>
            (apStack_148,(Roles *)&local_1c8,"w");
  local_1c4 = 0x105;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[2],true>
            (apStack_128,(Roles *)&local_1c4,"h");
  local_1c0 = 0x106;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[5],true>
            (apStack_108,(Roles *)&local_1c0,"name");
  local_1bc = 0x107;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[6],true>
            (apStack_e8,(Roles *)&local_1bc,"appId");
  local_1b8 = 0x108;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[10],true>
            (apStack_c8,(Roles *)&local_1b8,"minimized");
  local_1b4 = 0x109;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[10],true>
            (apStack_a8,(Roles *)&local_1b4,"maximized");
  local_1b0 = 0x10a;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[6],true>
            (apStack_88,(Roles *)&local_1b0,"title");
  local_1ac = 0x10b;
  std::pair<int,QByteArray>::pair<NCDEWindowManager::Roles,char_const(&)[6],true>
            (local_68,(Roles *)&local_1ac,"tiled");
  QHash<int,QByteArray>::QHash(this,local_1a8,0xb);
  this_00 = apStack_48;
  while (this_00 != local_1a8) {
    this_00 = this_00 + -0x20;
    std::pair<int,QByteArray>::~pair(this_00);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00178014  NCDEWindowManager::mouseX

/* NCDEWindowManager::mouseX() const */

undefined4 __thiscall NCDEWindowManager::mouseX(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x38);
}



// ==== 00178026  NCDEWindowManager::mouseY

/* NCDEWindowManager::mouseY() const */

undefined4 __thiscall NCDEWindowManager::mouseY(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x3c);
}



// ==== 00178038  NCDEWindowManager::activeIndex

/* NCDEWindowManager::activeIndex() const */

undefined4 __thiscall NCDEWindowManager::activeIndex(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x40);
}



// ==== 0017804a  NCDEWindowManager::activeAppMenus

/* NCDEWindowManager::activeAppMenus() const */

QString * NCDEWindowManager::activeAppMenus(void)

{
  int iVar1;
  long lVar2;
  long in_RSI;
  QString *in_RDI;
  
  if ((-1 < *(int *)(in_RSI + 0x40)) &&
     (iVar1 = *(int *)(in_RSI + 0x40),
     lVar2 = QList<NCDEWindowManager::WindowEntry>::size
                       ((QList<NCDEWindowManager::WindowEntry> *)(in_RSI + 0x90)), iVar1 < lVar2)) {
    lVar2 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(in_RSI + 0x90),
                       (long)*(int *)(in_RSI + 0x40));
    QString::QString(in_RDI,(QString *)(lVar2 + 0x48));
    return in_RDI;
  }
  QString::QString(in_RDI);
  return in_RDI;
}



// ==== 001780d2  NCDEWindowManager::invokeAppMenu

/* NCDEWindowManager::invokeAppMenu(int) */

void __thiscall NCDEWindowManager::invokeAppMenu(NCDEWindowManager *this,int param_1)

{
  int iVar1;
  bool bVar2;
  long lVar3;
  uint *puVar4;
  
  if ((0 < param_1) && (-1 < *(int *)(this + 0x40))) {
    iVar1 = *(int *)(this + 0x40);
    lVar3 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (iVar1 < lVar3) {
      bVar2 = false;
      goto LAB_00178120;
    }
  }
  bVar2 = true;
LAB_00178120:
  if (!bVar2) {
    puVar4 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)*(int *)(this + 0x40));
    GliaTalkProto::sendInvoke(*(xcb_connection_t **)(this + 0x20),*puVar4,param_1);
  }
  return;
}



// ==== 00178166  NCDEWindowManager::snapZone

/* NCDEWindowManager::snapZone() const */

undefined4 __thiscall NCDEWindowManager::snapZone(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x44);
}



// ==== 00178178  NCDEWindowManager::setSnapZone

/* NCDEWindowManager::setSnapZone(int) */

void __thiscall NCDEWindowManager::setSnapZone(NCDEWindowManager *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x44)) {
    *(int *)(this + 0x44) = param_1;
    snapZoneChanged(this);
  }
  return;
}



// ==== 001781ac  NCDEWindowManager::screenWidth

/* NCDEWindowManager::screenWidth() const */

undefined4 __thiscall NCDEWindowManager::screenWidth(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x30);
}



// ==== 001781be  NCDEWindowManager::screenHeight

/* NCDEWindowManager::screenHeight() const */

undefined4 __thiscall NCDEWindowManager::screenHeight(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x34);
}



// ==== 001781d0  NCDEWindowManager::atomNetWmWindowType

/* NCDEWindowManager::atomNetWmWindowType() const */

undefined4 __thiscall NCDEWindowManager::atomNetWmWindowType(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x10c);
}



// ==== 001781e4  NCDEWindowManager::atomNetWmWindowTypeDesktop

/* NCDEWindowManager::atomNetWmWindowTypeDesktop() const */

undefined4 __thiscall NCDEWindowManager::atomNetWmWindowTypeDesktop(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x114);
}



// ==== 001781f8  NCDEWindowManager::atomNetWmWindowTypeDock

/* NCDEWindowManager::atomNetWmWindowTypeDock() const */

undefined4 __thiscall NCDEWindowManager::atomNetWmWindowTypeDock(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x118);
}



// ==== 0017820c  NCDEWindowManager::atomNetWmWindowTypePopupMenu

/* NCDEWindowManager::atomNetWmWindowTypePopupMenu() const */

undefined4 __thiscall NCDEWindowManager::atomNetWmWindowTypePopupMenu(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 300);
}



// ==== 00178220  NCDEWindowManager::atomNetWmWindowTypeTooltip

/* NCDEWindowManager::atomNetWmWindowTypeTooltip() const */

undefined4 __thiscall NCDEWindowManager::atomNetWmWindowTypeTooltip(NCDEWindowManager *this)

{
  return *(undefined4 *)(this + 0x130);
}



// ==== 00178234  NCDEWindowManager::setWindowType

/* NCDEWindowManager::setWindowType(unsigned int, unsigned int) */

void __thiscall NCDEWindowManager::setWindowType(NCDEWindowManager *this,uint param_1,uint param_2)

{
  long in_FS_OFFSET;
  uint local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((((*(long *)(this + 0x20) != 0) && (param_1 != 0)) && (param_2 != 0)) &&
     (*(int *)(this + 0x10c) != 0)) {
    local_14 = param_2;
    xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0x10c),4,0x20,
                        1,&local_14);
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001782e4  NCDEWindowManager::rowForClient

/* NCDEWindowManager::rowForClient(unsigned int) const */

int __thiscall NCDEWindowManager::rowForClient(NCDEWindowManager *this,uint param_1)

{
  uint *puVar1;
  long lVar2;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    lVar2 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar2 <= local_1c) {
      return -1;
    }
    puVar1 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)local_1c);
    if (param_1 == *puVar1) break;
    local_1c = local_1c + 1;
  }
  return local_1c;
}



// ==== 0017835a  NCDEWindowManager::winIdForName

/* NCDEWindowManager::winIdForName(QString const&) const */

undefined4 __thiscall NCDEWindowManager::winIdForName(NCDEWindowManager *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  QList<NCDEWindowManager::WindowEntry> *local_20;
  undefined4 *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
  local_30 = QList<NCDEWindowManager::WindowEntry>::begin(local_20);
  local_28 = QList<NCDEWindowManager::WindowEntry>::end(local_20);
  do {
    cVar2 = QList<NCDEWindowManager::WindowEntry>::const_iterator::operator!=
                      ((const_iterator *)&local_30,local_28);
    if (cVar2 == '\0') {
      uVar3 = 0;
LAB_00178433:
      if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return uVar3;
    }
    local_18 = (undefined4 *)
               QList<NCDEWindowManager::WindowEntry>::const_iterator::operator*
                         ((const_iterator *)&local_30);
    cVar2 = ::operator==((QString *)(local_18 + 6),param_1);
    if (cVar2 == '\0') {
      cVar2 = ::operator==((QString *)(local_18 + 0xc),param_1);
      if (cVar2 != '\0') goto LAB_001783ef;
      bVar1 = false;
    }
    else {
LAB_001783ef:
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = *local_18;
      goto LAB_00178433;
    }
    QList<NCDEWindowManager::WindowEntry>::const_iterator::operator++((const_iterator *)&local_30);
  } while( true );
}



// ==== 0017844a  NCDEWindowManager::hasWindowForName

/* NCDEWindowManager::hasWindowForName(QString const&) const */

bool __thiscall NCDEWindowManager::hasWindowForName(NCDEWindowManager *this,QString *param_1)

{
  int iVar1;
  
  iVar1 = winIdForName(this,param_1);
  return iVar1 != 0;
}



// ==== 00178474  NCDEWindowManager::isMinimizedForName

/* NCDEWindowManager::isMinimizedForName(QString const&) const */

undefined1 __thiscall
NCDEWindowManager::isMinimizedForName(NCDEWindowManager *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  QList<NCDEWindowManager::WindowEntry> *local_20;
  long local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
  local_30 = QList<NCDEWindowManager::WindowEntry>::begin(local_20);
  local_28 = QList<NCDEWindowManager::WindowEntry>::end(local_20);
  do {
    cVar2 = QList<NCDEWindowManager::WindowEntry>::const_iterator::operator!=
                      ((const_iterator *)&local_30,local_28);
    if (cVar2 == '\0') {
      uVar3 = 0;
LAB_0017854f:
      if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return uVar3;
    }
    local_18 = QList<NCDEWindowManager::WindowEntry>::const_iterator::operator*
                         ((const_iterator *)&local_30);
    cVar2 = ::operator==((QString *)(local_18 + 0x18),param_1);
    if (cVar2 == '\0') {
      cVar2 = ::operator==((QString *)(local_18 + 0x30),param_1);
      if (cVar2 != '\0') goto LAB_00178509;
      bVar1 = false;
    }
    else {
LAB_00178509:
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = *(undefined1 *)(local_18 + 0x60);
      goto LAB_0017854f;
    }
    QList<NCDEWindowManager::WindowEntry>::const_iterator::operator++((const_iterator *)&local_30);
  } while( true );
}



// ==== 00178566  NCDEWindowManager::isActiveForName

/* NCDEWindowManager::isActiveForName(QString const&) const */

undefined8 __thiscall NCDEWindowManager::isActiveForName(NCDEWindowManager *this,QString *param_1)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = winIdForName(this,param_1);
  if ((iVar1 == *(int *)(this + 0x2c)) && (*(int *)(this + 0x2c) != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 001785b0  NCDEWindowManager::isMaximizedForName

/* NCDEWindowManager::isMaximizedForName(QString const&) const */

undefined1 __thiscall
NCDEWindowManager::isMaximizedForName(NCDEWindowManager *this,QString *param_1)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  QList<NCDEWindowManager::WindowEntry> *local_20;
  long local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
  local_30 = QList<NCDEWindowManager::WindowEntry>::begin(local_20);
  local_28 = QList<NCDEWindowManager::WindowEntry>::end(local_20);
  do {
    cVar2 = QList<NCDEWindowManager::WindowEntry>::const_iterator::operator!=
                      ((const_iterator *)&local_30,local_28);
    if (cVar2 == '\0') {
      uVar3 = 0;
LAB_0017868b:
      if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return uVar3;
    }
    local_18 = QList<NCDEWindowManager::WindowEntry>::const_iterator::operator*
                         ((const_iterator *)&local_30);
    cVar2 = ::operator==((QString *)(local_18 + 0x18),param_1);
    if (cVar2 == '\0') {
      cVar2 = ::operator==((QString *)(local_18 + 0x30),param_1);
      if (cVar2 != '\0') goto LAB_00178645;
      bVar1 = false;
    }
    else {
LAB_00178645:
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = *(undefined1 *)(local_18 + 0x61);
      goto LAB_0017868b;
    }
    QList<NCDEWindowManager::WindowEntry>::const_iterator::operator++((const_iterator *)&local_30);
  } while( true );
}



// ==== 001786a2  NCDEWindowManager::activateWindow

/* NCDEWindowManager::activateWindow(unsigned int) */

void __thiscall NCDEWindowManager::activateWindow(NCDEWindowManager *this,uint param_1)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  QObject *pQVar4;
  long in_FS_OFFSET;
  uint local_54;
  NCDEWindowManager *local_50;
  int local_3c;
  int local_38;
  int local_34;
  uint local_30;
  int local_2c;
  QWindow *local_28;
  undefined4 local_1c;
  ulong local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_54 = param_1;
  local_50 = this;
  if ((*(long *)(this + 0x20) == 0) || (param_1 == 0)) goto LAB_001789a6;
  local_3c = rowForClient(this,param_1);
  if (local_3c < 0) {
LAB_00178720:
    bVar1 = false;
  }
  else {
    lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),(long)local_3c);
    if (*(char *)(lVar3 + 0x60) == '\0') goto LAB_00178720;
    bVar1 = true;
  }
  if (bVar1) {
    setMin(local_50,local_54,false);
    pQVar4 = (QObject *)
             QHash<unsigned_int,QObject*>::value
                       ((QHash<unsigned_int,QObject*> *)(local_50 + 0xb0),&local_54);
    local_28 = qobject_cast<QWindow*>(pQVar4);
    if (local_28 != (QWindow *)0x0) {
      QWindow::setVisible(SUB81(local_28,0));
    }
    if (*(long *)(local_50 + 0x20) != 0) {
      local_38 = QHash<unsigned_int,unsigned_int>::value
                           ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xc0),&local_54);
      if (local_38 != 0) {
        xcb_map_window(*(undefined8 *)(local_50 + 0x20),local_38);
      }
      local_34 = QHash<unsigned_int,unsigned_int>::value
                           ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xd0),&local_54);
      if (local_34 != 0) {
        xcb_map_window(*(undefined8 *)(local_50 + 0x20),local_34);
      }
      xcb_map_window(*(undefined8 *)(local_50 + 0x20),local_54);
      xcb_flush(*(undefined8 *)(local_50 + 0x20));
    }
  }
  local_30 = QHash<unsigned_int,unsigned_int>::value
                       ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xc0),&local_54);
  local_2c = QHash<unsigned_int,unsigned_int>::value
                       ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xd0),&local_54);
  if (local_30 == 0) {
    local_18 = local_18 & 0xffffffff00000000;
    xcb_configure_window(*(undefined8 *)(local_50 + 0x20),local_54,0x40,&local_18);
  }
  else {
    local_1c = 0;
    xcb_configure_window(*(undefined8 *)(local_50 + 0x20),local_30,0x40,&local_1c);
    if (local_2c != 0) {
      local_18 = (ulong)local_30;
      xcb_configure_window(*(undefined8 *)(local_50 + 0x20),local_2c,0x60,&local_18);
    }
  }
  xcb_set_input_focus(*(undefined8 *)(local_50 + 0x20),1,local_54,0);
  if (*(int *)(local_50 + 0xf0) != 0) {
    xcb_change_property(*(undefined8 *)(local_50 + 0x20),0,*(undefined4 *)(local_50 + 0x28),
                        *(undefined4 *)(local_50 + 0xf0),0x21,0x20,1,&local_54);
  }
  xcb_flush(*(undefined8 *)(local_50 + 0x20));
  *(uint *)(local_50 + 0x2c) = local_54;
  iVar2 = rowForClient(local_50,local_54);
  setActiveIndex(local_50,iVar2);
  activeIndexChanged(local_50);
  activeAppMenusChanged(local_50);
LAB_001789a6:
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001789bc  NCDEWindowManager::minimizeWindow

/* NCDEWindowManager::minimizeWindow(unsigned int) */

void __thiscall NCDEWindowManager::minimizeWindow(NCDEWindowManager *this,uint param_1)

{
  QObject *pQVar1;
  uint local_24;
  NCDEWindowManager *local_20;
  int local_18;
  int local_14;
  QWindow *local_10;
  
  local_24 = param_1;
  local_20 = this;
  setMin(this,param_1,true);
  pQVar1 = (QObject *)
           QHash<unsigned_int,QObject*>::value
                     ((QHash<unsigned_int,QObject*> *)(local_20 + 0xb0),&local_24);
  local_10 = qobject_cast<QWindow*>(pQVar1);
  if (local_10 != (QWindow *)0x0) {
    QWindow::setVisible(SUB81(local_10,0));
  }
  if (*(long *)(local_20 + 0x20) != 0) {
    local_18 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_20 + 0xc0),&local_24);
    if (local_18 != 0) {
      xcb_unmap_window(*(undefined8 *)(local_20 + 0x20),local_18);
    }
    local_14 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_20 + 0xd0),&local_24);
    if (local_14 != 0) {
      xcb_unmap_window(*(undefined8 *)(local_20 + 0x20),local_14);
    }
    xcb_unmap_window(*(undefined8 *)(local_20 + 0x20),local_24);
    xcb_flush(*(undefined8 *)(local_20 + 0x20));
  }
  return;
}



// ==== 00178aca  NCDEWindowManager::unminimizeWindow

/* NCDEWindowManager::unminimizeWindow(unsigned int) */

void __thiscall NCDEWindowManager::unminimizeWindow(NCDEWindowManager *this,uint param_1)

{
  QObject *pQVar1;
  uint local_24;
  NCDEWindowManager *local_20;
  int local_18;
  int local_14;
  QWindow *local_10;
  
  local_24 = param_1;
  local_20 = this;
  setMin(this,param_1,false,true);
  pQVar1 = (QObject *)
           QHash<unsigned_int,QObject*>::value
                     ((QHash<unsigned_int,QObject*> *)(local_20 + 0xb0),&local_24);
  local_10 = qobject_cast<QWindow*>(pQVar1);
  if (local_10 != (QWindow *)0x0) {
    QWindow::setVisible(SUB81(local_10,0));
  }
  if (*(long *)(local_20 + 0x20) != 0) {
    local_18 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_20 + 0xc0),&local_24);
    if (local_18 != 0) {
      xcb_map_window(*(undefined8 *)(local_20 + 0x20),local_18);
    }
    local_14 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_20 + 0xd0),&local_24);
    if (local_14 != 0) {
      xcb_map_window(*(undefined8 *)(local_20 + 0x20),local_14);
    }
    xcb_map_window(*(undefined8 *)(local_20 + 0x20),local_24);
    xcb_flush(*(undefined8 *)(local_20 + 0x20));
    activateWindow(local_20,local_24);
  }
  return;
}



// ==== 00178bec  NCDEWindowManager::moveWindow

/* NCDEWindowManager::moveWindow(unsigned int, int, int) */

void __thiscall
NCDEWindowManager::moveWindow(NCDEWindowManager *this,uint param_1,int param_2,int param_3)

{
  long in_FS_OFFSET;
  uint local_34;
  NCDEWindowManager *local_30;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_34 = param_1;
  local_30 = this;
  if (*(long *)(this + 0x20) != 0) {
    setGeom(this,param_1,param_2,param_3,-1,-1);
    local_28 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_30 + 0xc0),&local_34);
    if (local_28 == 0) {
      local_18 = param_2;
      local_14 = param_3;
      xcb_configure_window(*(undefined8 *)(local_30 + 0x20),local_34,3,&local_18);
    }
    else {
      local_20 = param_2 + -0xc;
      local_1c = param_3 + -0x20;
      xcb_configure_window(*(undefined8 *)(local_30 + 0x20),local_28,3,&local_20);
      local_24 = QHash<unsigned_int,unsigned_int>::value
                           ((QHash<unsigned_int,unsigned_int> *)(local_30 + 0xd0),&local_34);
      if (local_24 != 0) {
        local_18 = param_2 + -0x18;
        local_14 = param_3 + -0x2c;
        xcb_configure_window(*(undefined8 *)(local_30 + 0x20),local_24,3,&local_18);
      }
    }
    xcb_flush(*(undefined8 *)(local_30 + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00178d44  NCDEWindowManager::resizeWindow

/* NCDEWindowManager::resizeWindow(unsigned int, int, int) */

void __thiscall
NCDEWindowManager::resizeWindow(NCDEWindowManager *this,uint param_1,int param_2,int param_3)

{
  long in_FS_OFFSET;
  uint local_44;
  NCDEWindowManager *local_40;
  int local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_44 = param_1;
  local_40 = this;
  if (*(long *)(this + 0x20) != 0) {
    setGeom(this,param_1,-1,-1,param_2,param_3);
    local_28 = param_2;
    local_24 = param_3;
    xcb_configure_window(*(undefined8 *)(local_40 + 0x20),local_44,0xc,&local_28);
    local_30 = QHash<unsigned_int,unsigned_int>::value
                         ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xc0),&local_44);
    if (local_30 != 0) {
      local_20 = param_2 + 0x18;
      local_1c = param_3 + 0x3a;
      xcb_configure_window(*(undefined8 *)(local_40 + 0x20),local_30,0xc,&local_20);
      local_2c = QHash<unsigned_int,unsigned_int>::value
                           ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xd0),&local_44);
      if (local_2c != 0) {
        local_18 = param_2 + 0x30;
        local_14 = param_3 + 0x52;
        xcb_configure_window(*(undefined8 *)(local_40 + 0x20),local_2c,0xc,&local_18);
        setFrameInputRegion(local_40,local_2c,param_2 + 0x30,param_3 + 0x52);
      }
    }
    xcb_flush(*(undefined8 *)(local_40 + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00178eba  NCDEWindowManager::moveTiledWindow

/* NCDEWindowManager::moveTiledWindow(unsigned int, int, int, int, int) */

void __thiscall
NCDEWindowManager::moveTiledWindow
          (NCDEWindowManager *this,uint param_1,int param_2,int param_3,int param_4,int param_5)

{
  moveWindow(this,param_1,param_2,param_3);
  resizeWindow(this,param_1,param_4,param_5);
  return;
}



// ==== 00178f04  NCDEWindowManager::setTiled

/* NCDEWindowManager::setTiled(unsigned int, bool) */

void __thiscall NCDEWindowManager::setTiled(NCDEWindowManager *this,uint param_1,bool param_2)

{
  code *pcVar1;
  uint *puVar2;
  long lVar3;
  long in_FS_OFFSET;
  int local_cc;
  QModelIndex local_c8 [32];
  QModelIndex local_a8 [32];
  QModelIndex local_88 [32];
  QList local_68 [32];
  QList<int> local_48 [16];
  undefined8 local_38;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_cc = 0;
  do {
    lVar3 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar3 <= local_cc) {
LAB_00179115:
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    puVar2 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)local_cc);
    if (param_1 == *puVar2) {
      lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
      if (param_2 != (bool)*(char *)(lVar3 + 0x62)) {
        lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
        *(bool *)(lVar3 + 0x62) = param_2;
        local_48[0] = (QList<int>)0x0;
        local_48[1] = (QList<int>)0x0;
        local_48[2] = (QList<int>)0x0;
        local_48[3] = (QList<int>)0x0;
        local_48[4] = (QList<int>)0x0;
        local_48[5] = (QList<int>)0x0;
        local_48[6] = (QList<int>)0x0;
        local_48[7] = (QList<int>)0x0;
        local_48[8] = (QList<int>)0x0;
        local_48[9] = (QList<int>)0x0;
        local_48[10] = (QList<int>)0x0;
        local_48[0xb] = (QList<int>)0x0;
        local_48[0xc] = (QList<int>)0x0;
        local_48[0xd] = (QList<int>)0x0;
        local_48[0xe] = (QList<int>)0x0;
        local_48[0xf] = (QList<int>)0x0;
        local_38 = 0;
        QList<int>::QList(local_48);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_88);
        (*pcVar1)(local_68,this,local_cc,0,local_88);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_c8);
        (*pcVar1)(local_a8,this,local_cc,0,local_c8);
        QAbstractItemModel::dataChanged((QModelIndex *)this,local_a8,local_68);
        QList<int>::~QList(local_48);
      }
      goto LAB_00179115;
    }
    local_cc = local_cc + 1;
  } while( true );
}



// ==== 00179138  NCDEWindowManager::isMaximized

/* NCDEWindowManager::isMaximized(unsigned int) const */

undefined8 __thiscall NCDEWindowManager::isMaximized(NCDEWindowManager *this,uint param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = rowForClient(this,param_1);
  if ((-1 < iVar1) &&
     (lVar2 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar1),
     *(char *)(lVar2 + 0x61) != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 0017921a  NCDEWindowManager::setMaximized

/* NCDEWindowManager::setMaximized(unsigned int, bool) */

void __thiscall NCDEWindowManager::setMaximized(NCDEWindowManager *this,uint param_1,bool param_2)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  uint *puVar6;
  long lVar7;
  void *__ptr;
  undefined8 uVar8;
  long in_FS_OFFSET;
  int local_f4;
  int local_f0;
  QModelIndex local_d8 [32];
  QModelIndex local_b8 [32];
  QModelIndex local_98 [32];
  QList local_78 [32];
  QList<int> local_58 [16];
  undefined8 local_48;
  undefined4 local_38;
  undefined4 local_34;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x20) != 0) {
    local_f4 = 0;
    while( true ) {
      lVar7 = QList<NCDEWindowManager::WindowEntry>::size
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
      if (lVar7 <= local_f4) break;
      puVar6 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                                 ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                  (long)local_f4);
      if (param_1 == *puVar6) {
        lVar7 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_f4);
        if (param_2 == (bool)*(char *)(lVar7 + 0x61)) goto LAB_001792ce;
        bVar2 = true;
      }
      else {
LAB_001792ce:
        bVar2 = false;
      }
      if (bVar2) {
        lVar7 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_f4);
        *(bool *)(lVar7 + 0x61) = param_2;
        local_58[0] = (QList<int>)0x0;
        local_58[1] = (QList<int>)0x0;
        local_58[2] = (QList<int>)0x0;
        local_58[3] = (QList<int>)0x0;
        local_58[4] = (QList<int>)0x0;
        local_58[5] = (QList<int>)0x0;
        local_58[6] = (QList<int>)0x0;
        local_58[7] = (QList<int>)0x0;
        local_58[8] = (QList<int>)0x0;
        local_58[9] = (QList<int>)0x0;
        local_58[10] = (QList<int>)0x0;
        local_58[0xb] = (QList<int>)0x0;
        local_58[0xc] = (QList<int>)0x0;
        local_58[0xd] = (QList<int>)0x0;
        local_58[0xe] = (QList<int>)0x0;
        local_58[0xf] = (QList<int>)0x0;
        local_48 = 0;
        QList<int>::QList(local_58);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_98);
        (*pcVar1)(local_78,this,local_f4,0,local_98);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_d8);
        (*pcVar1)(local_b8,this,local_f4,0,local_d8);
        QAbstractItemModel::dataChanged((QModelIndex *)this,local_b8,local_78);
        QList<int>::~QList(local_58);
        windowStateChanged(this);
        break;
      }
      local_f4 = local_f4 + 1;
    }
    if (param_2) {
      local_38 = *(undefined4 *)(this + 0xfc);
      local_34 = *(undefined4 *)(this + 0x100);
      xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0xf8),4,0x20
                          ,2,&local_38);
    }
    else {
      uVar4 = xcb_get_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0xf8),4
                               ,0,0x20);
      __ptr = (void *)xcb_get_property_reply(*(undefined8 *)(this + 0x20),uVar4,0);
      if (__ptr == (void *)0x0) {
        xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0xf8),4,
                            0x20,0,0);
      }
      else {
        lVar7 = xcb_get_property_value(__ptr);
        iVar5 = xcb_get_property_value_length(__ptr);
        local_58[0] = (QList<int>)0x0;
        local_58[1] = (QList<int>)0x0;
        local_58[2] = (QList<int>)0x0;
        local_58[3] = (QList<int>)0x0;
        local_58[4] = (QList<int>)0x0;
        local_58[5] = (QList<int>)0x0;
        local_58[6] = (QList<int>)0x0;
        local_58[7] = (QList<int>)0x0;
        local_58[8] = (QList<int>)0x0;
        local_58[9] = (QList<int>)0x0;
        local_58[10] = (QList<int>)0x0;
        local_58[0xb] = (QList<int>)0x0;
        local_58[0xc] = (QList<int>)0x0;
        local_58[0xd] = (QList<int>)0x0;
        local_58[0xe] = (QList<int>)0x0;
        local_58[0xf] = (QList<int>)0x0;
        local_48 = 0;
        for (local_f0 = 0; local_f0 < (int)((ulong)(long)iVar5 >> 2); local_f0 = local_f0 + 1) {
          if ((*(int *)(lVar7 + (long)local_f0 * 4) != *(int *)(this + 0xfc)) &&
             (*(int *)(lVar7 + (long)local_f0 * 4) != *(int *)(this + 0x100))) {
            QList<unsigned_int>::append
                      ((QList<unsigned_int> *)local_58,*(uint *)(lVar7 + (long)local_f0 * 4));
          }
        }
        cVar3 = QList<unsigned_int>::isEmpty((QList<unsigned_int> *)local_58);
        if (cVar3 == '\0') {
          uVar8 = QList<unsigned_int>::constData((QList<unsigned_int> *)local_58);
        }
        else {
          uVar8 = 0;
        }
        uVar4 = QList<unsigned_int>::size((QList<unsigned_int> *)local_58);
        xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0xf8),4,
                            0x20,uVar4,uVar8);
        free(__ptr);
        QList<unsigned_int>::~QList((QList<unsigned_int> *)local_58);
      }
    }
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00179750  NCDEWindowManager::closeWindow

/* NCDEWindowManager::closeWindow(unsigned int) */

void __thiscall NCDEWindowManager::closeWindow(NCDEWindowManager *this,uint param_1)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  long in_FS_OFFSET;
  undefined1 local_38 [12];
  undefined4 uStack_2c;
  undefined1 local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x20) != 0) && (param_1 != 0)) {
    if ((*(int *)(this + 0xe0) == 0) || (*(int *)(this + 0xe4) == 0)) {
      xcb_kill_client(*(undefined8 *)(this + 0x20),param_1);
    }
    else {
      stack0xffffffffffffffc9 = SUB1615((undefined1  [16])0x0,1);
      auVar2._4_4_ = *(undefined4 *)(this + 0xe0);
      auVar2._0_4_ = param_1;
      auVar2._8_4_ = uStack_2c;
      auVar2._12_4_ = 0;
      _local_38 = auVar2 << 0x20;
      local_38._0_2_ = 0x2021;
      uStack_2c = *(undefined4 *)(this + 0xe4);
      local_28._4_12_ = SUB1612((undefined1  [16])0x0,4);
      auVar1._12_4_ = 0;
      auVar1._0_12_ = local_28._4_12_;
      local_28._0_16_ = auVar1 << 0x20;
      xcb_send_event(*(undefined8 *)(this + 0x20),0,param_1,0,local_38);
    }
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00179844  NCDEWindowManager::systemCommand

/* NCDEWindowManager::systemCommand(QString const&) */

void __thiscall NCDEWindowManager::systemCommand(NCDEWindowManager *this,QString *param_1)

{
  QString *this_00;
  long in_FS_OFFSET;
  QString local_d8 [32];
  QList local_b8 [32];
  QString local_98 [32];
  QString local_78 [24];
  QString local_60 [24];
  QString aQStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(local_98);
  QString::QString(local_78,"-c");
  QString::QString(local_60,param_1);
  QList<QString>::QList(local_b8,local_78,2);
  QString::QString(local_d8,"/bin/sh");
  QProcess::startDetached(local_d8,local_b8,local_98,(longlong *)0x0);
  QString::~QString(local_d8);
  QList<QString>::~QList((QList<QString> *)local_b8);
  this_00 = aQStack_48;
  while (this_00 != local_78) {
    this_00 = this_00 + -0x18;
    QString::~QString(this_00);
  }
  QString::~QString(local_98);
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00179a56  NCDEWindowManager::registerFrameWindowQml

/* NCDEWindowManager::registerFrameWindowQml(unsigned int, QObject*) */

void __thiscall
NCDEWindowManager::registerFrameWindowQml(NCDEWindowManager *this,uint param_1,QObject *param_2)

{
  char cVar1;
  QObject *local_30;
  uint local_24;
  NCDEWindowManager *local_20;
  int local_14;
  QWindow *local_10;
  
  local_30 = param_2;
  local_24 = param_1;
  local_20 = this;
  QHash<unsigned_int,QObject*>::insert
            ((QHash<unsigned_int,QObject*> *)(this + 0xb0),&local_24,&local_30);
  local_10 = qobject_cast<QWindow*>(local_30);
  if (((local_10 != (QWindow *)0x0) && (local_14 = QWindow::winId(), local_14 != 0)) &&
     (cVar1 = QHash<unsigned_int,unsigned_int>::contains
                        ((QHash<unsigned_int,unsigned_int> *)(local_20 + 0xc0),&local_24),
     cVar1 == '\0')) {
    FUN_00291390(local_20,local_24,local_14);
  }
  return;
}



// ==== 00179af0  NCDEWindowManager::destroyFrameWindow

/* NCDEWindowManager::destroyFrameWindow(unsigned int) */

void __thiscall NCDEWindowManager::destroyFrameWindow(NCDEWindowManager *this,uint param_1)

{
  undefined4 uVar1;
  long lVar2;
  long in_FS_OFFSET;
  uint local_44;
  NCDEWindowManager *local_40;
  uint local_2c;
  uint local_28;
  int local_24;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_44 = param_1;
  local_40 = this;
  QHash<unsigned_int,QObject*>::remove((QHash<unsigned_int,QObject*> *)(this + 0xb0),&local_44);
  if (*(long *)(local_40 + 0x20) != 0) {
    local_2c = QHash<unsigned_int,unsigned_int>::take
                         ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xc0),&local_44);
    if (local_2c != 0) {
      QHash<unsigned_int,unsigned_int>::remove
                ((QHash<unsigned_int,unsigned_int> *)(local_40 + 200),&local_2c);
      local_24 = rowForClient(local_40,local_44);
      if (-1 < local_24) {
        lVar2 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_24
                          );
        uVar1 = *(undefined4 *)(lVar2 + 0xc);
        lVar2 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_24
                          );
        xcb_reparent_window(*(undefined8 *)(local_40 + 0x20),local_44,
                            *(undefined4 *)(local_40 + 0x28),(int)(short)*(undefined4 *)(lVar2 + 8),
                            (int)(short)uVar1);
        xcb_change_save_set(*(undefined8 *)(local_40 + 0x20),1,local_44);
      }
      xcb_destroy_window(*(undefined8 *)(local_40 + 0x20),local_2c);
    }
    local_28 = QHash<unsigned_int,unsigned_int>::take
                         ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xd0),&local_44);
    if (local_28 != 0) {
      QHash<unsigned_int,unsigned_int>::remove
                ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xd8),&local_28);
    }
    xcb_flush(*(undefined8 *)(local_40 + 0x20));
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00179c92  NCDEWindowManager::nativeEventFilter

/* NCDEWindowManager::nativeEventFilter(QByteArray const&, void*, long long*) */

undefined8 NCDEWindowManager::nativeEventFilter(QByteArray *param_1,void *param_2,longlong *param_3)

{
  uint uVar1;
  bool bVar2;
  char cVar3;
  QByteArray QVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  long in_FS_OFFSET;
  char *local_50;
  longlong *local_48;
  longlong *local_40;
  longlong *local_38;
  longlong *local_30;
  longlong *local_28;
  longlong *local_20;
  void *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_1[0x48] == (QByteArray)0x1) {
    local_50 = "xcb_generic_event_t";
    cVar3 = ::operator!=(param_2,&local_50);
    if (cVar3 != '\0') goto LAB_00179cea;
    bVar2 = false;
  }
  else {
LAB_00179cea:
    bVar2 = true;
  }
  if (!bVar2) {
    QVar4 = (QByteArray)((byte)*param_3 & 0x7f);
    local_48 = param_3;
    if ((param_1[0x49] == (QByteArray)0x0) || (QVar4 != param_1[0x4a])) {
      if (((param_1[0x4b] == (QByteArray)0x0) || (*(long *)(param_1 + 0x50) == 0)) ||
         (QVar4 != param_1[0x4c])) {
        if (((param_1[0x4d] == (QByteArray)0x0) || (QVar4 != (QByteArray)0x23)) ||
           ((local_38 = param_3, *(QByteArray *)((long)param_3 + 1) != param_1[0x4e] ||
            ((short)param_3[1] != 0x11)))) {
          if (QVar4 == (QByteArray)0x21) {
            local_30 = param_3;
            if (((int)param_3[1] == *(int *)(param_1 + 0x13c)) &&
               (*(char *)((long)param_3 + 1) == ' ')) {
              switchDesktop((NCDEWindowManager *)param_1,*(int *)((long)param_3 + 0xc));
            }
          }
          else if ((byte)QVar4 < 0x22) {
            if (QVar4 == (QByteArray)0x1c) {
              local_28 = param_3;
              onPropertyNotify((NCDEWindowManager *)param_1,*(uint *)((long)param_3 + 4),
                               *(uint *)(param_3 + 1));
            }
            else if ((byte)QVar4 < 0x1d) {
              if (QVar4 == (QByteArray)0x17) {
                onConfigureRequest((NCDEWindowManager *)param_1,
                                   (xcb_configure_request_event_t *)param_3);
              }
              else if ((byte)QVar4 < 0x18) {
                if (QVar4 == (QByteArray)0x14) {
                  onMapRequest((NCDEWindowManager *)param_1,(xcb_map_request_event_t *)param_3);
                }
                else if ((byte)QVar4 < 0x15) {
                  if (QVar4 == (QByteArray)0x13) {
                    anyWindowMapped((NCDEWindowManager *)param_1);
                  }
                  else if ((((byte)QVar4 < 0x14) && (QVar4 != (QByteArray)0x12)) &&
                          ((byte)QVar4 < 0x13)) {
                    if (QVar4 == (QByteArray)0x9) {
                      local_20 = param_3;
                      if (*(int *)((long)param_3 + 4) != *(int *)(param_1 + 0x2c)) {
                        iVar5 = rowForClient((NCDEWindowManager *)param_1,
                                             *(uint *)((long)param_3 + 4));
                        if ((iVar5 < 0) ||
                           (lVar7 = QList<NCDEWindowManager::WindowEntry>::operator[]
                                              ((QList<NCDEWindowManager::WindowEntry> *)
                                               (param_1 + 0x90),(long)iVar5),
                           *(char *)(lVar7 + 0x60) == '\0')) {
                          bVar2 = false;
                        }
                        else {
                          bVar2 = true;
                        }
                        if (bVar2) {
                          uVar6 = xcb_get_window_attributes
                                            (*(undefined8 *)(param_1 + 0x20),
                                             *(undefined4 *)((long)local_20 + 4));
                          local_18 = (void *)xcb_get_window_attributes_reply
                                                       (*(undefined8 *)(param_1 + 0x20),uVar6,0);
                          if ((local_18 == (void *)0x0) ||
                             (*(char *)((long)local_18 + 0x1a) != '\x02')) {
                            bVar2 = false;
                          }
                          else {
                            bVar2 = true;
                          }
                          free(local_18);
                          if (!bVar2) goto LAB_0017a07b;
                        }
                        *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)((long)local_20 + 4);
                        if (-1 < iVar5) {
                          activateWindow((NCDEWindowManager *)param_1,*(uint *)((long)local_20 + 4))
                          ;
                        }
                      }
                    }
                    else if (QVar4 == (QByteArray)0x11) {
                      uVar1 = *(uint *)(param_3 + 1);
                      if (uVar1 == *(uint *)(param_1 + 0x14c)) {
                        onPicomDied((NCDEWindowManager *)param_1);
                      }
                      onDestroy((NCDEWindowManager *)param_1,uVar1);
                    }
                  }
                }
              }
            }
          }
        }
        else {
          pollPointer((NCDEWindowManager *)param_1);
        }
      }
      else {
        local_40 = param_3;
        AnimPolicy::onScreenSaverActivated
                  (*(AnimPolicy **)(param_1 + 0x50),*(char *)((long)param_3 + 1) == '\x01');
      }
    }
    else {
      onRandRScreenChange((NCDEWindowManager *)param_1,
                          (xcb_randr_screen_change_notify_event_t *)param_3);
    }
  }
LAB_0017a07b:
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017a091  NCDEWindowManager::nativeEventFilter

/* non-virtual thunk to NCDEWindowManager::nativeEventFilter(QByteArray const&, void*, long long*)
    */

void __thiscall
NCDEWindowManager::nativeEventFilter
          (NCDEWindowManager *this,QByteArray *param_1,void *param_2,longlong *param_3)

{
  nativeEventFilter((QByteArray *)(this + -0x10),param_1,param_2);
  return;
}



// ==== 0017a0aa  NCDEWindowManager::pollPointer

/* NCDEWindowManager::pollPointer() */

void __thiscall NCDEWindowManager::pollPointer(NCDEWindowManager *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = QCursor::pos();
  iVar2 = QPoint::x((QPoint *)&local_18);
  iVar3 = QPoint::y((QPoint *)&local_18);
  if ((iVar2 == *(int *)(this + 0x38)) && (iVar3 == *(int *)(this + 0x3c))) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    *(int *)(this + 0x38) = iVar2;
    *(int *)(this + 0x3c) = iVar3;
    mousePosChanged(this);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017a150  NCDEWindowManager::setActiveIndex

/* NCDEWindowManager::setActiveIndex(int) */

void __thiscall NCDEWindowManager::setActiveIndex(NCDEWindowManager *this,int param_1)

{
  if (param_1 != *(int *)(this + 0x40)) {
    *(int *)(this + 0x40) = param_1;
    activeIndexChanged(this);
    activeAppMenusChanged(this);
    emitTierUpdates(this);
  }
  return;
}



// ==== 0017a19c  NCDEWindowManager::setMin

/* NCDEWindowManager::setMin(unsigned int, bool) */

void __thiscall NCDEWindowManager::setMin(NCDEWindowManager *this,uint param_1,bool param_2)

{
  setMin(this,param_1,param_2,true);
  return;
}



// ==== 0017a1ca  NCDEWindowManager::setMin

/* NCDEWindowManager::setMin(unsigned int, bool, bool) */

void __thiscall
NCDEWindowManager::setMin(NCDEWindowManager *this,uint param_1,bool param_2,bool param_3)

{
  code *pcVar1;
  uint *puVar2;
  long lVar3;
  long in_FS_OFFSET;
  int local_cc;
  QModelIndex local_c8 [32];
  QModelIndex local_a8 [32];
  QModelIndex local_88 [32];
  QList local_68 [32];
  QList<int> local_48 [16];
  undefined8 local_38;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_cc = 0;
  do {
    lVar3 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar3 <= local_cc) {
LAB_0017a3d2:
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    puVar2 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)local_cc);
    if (param_1 == *puVar2) {
      lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
      *(bool *)(lVar3 + 0x60) = param_2;
      local_48[0] = (QList<int>)0x0;
      local_48[1] = (QList<int>)0x0;
      local_48[2] = (QList<int>)0x0;
      local_48[3] = (QList<int>)0x0;
      local_48[4] = (QList<int>)0x0;
      local_48[5] = (QList<int>)0x0;
      local_48[6] = (QList<int>)0x0;
      local_48[7] = (QList<int>)0x0;
      local_48[8] = (QList<int>)0x0;
      local_48[9] = (QList<int>)0x0;
      local_48[10] = (QList<int>)0x0;
      local_48[0xb] = (QList<int>)0x0;
      local_48[0xc] = (QList<int>)0x0;
      local_48[0xd] = (QList<int>)0x0;
      local_48[0xe] = (QList<int>)0x0;
      local_48[0xf] = (QList<int>)0x0;
      local_38 = 0;
      QList<int>::QList(local_48);
      pcVar1 = *(code **)(*(long *)this + 0x60);
      QModelIndex::QModelIndex(local_88);
      (*pcVar1)(local_68,this,local_cc,0,local_88);
      pcVar1 = *(code **)(*(long *)this + 0x60);
      QModelIndex::QModelIndex(local_c8);
      (*pcVar1)(local_a8,this,local_cc,0,local_c8);
      QAbstractItemModel::dataChanged((QModelIndex *)this,local_a8,local_68);
      QList<int>::~QList(local_48);
      windowStateChanged(this);
      if (param_3) {
        emitTierUpdates(this);
      }
      goto LAB_0017a3d2;
    }
    local_cc = local_cc + 1;
  } while( true );
}



// ==== 0017a3f4  NCDEWindowManager::emitTierUpdates

/* NCDEWindowManager::emitTierUpdates() */

void __thiscall NCDEWindowManager::emitTierUpdates(NCDEWindowManager *this)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  QString *pQVar5;
  long lVar6;
  long in_FS_OFFSET;
  undefined1 auVar7 [16];
  int local_cc;
  QString local_a8 [32];
  QArrayDataPointer<char16_t> local_88 [32];
  undefined1 local_68 [2] [16];
  undefined1 local_48 [16];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_cc = 0;
  do {
    lVar6 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar6 <= local_cc) {
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    lVar6 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
    if (*(int *)(lVar6 + 100) != 0) {
      bVar3 = false;
      bVar2 = false;
      bVar1 = false;
      if (*(char *)(lVar6 + 0x60) == '\0') {
        if (local_cc == *(int *)(this + 0x40)) {
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_68,(QTypedArrayData *)0x0,L"foreground",10
                    );
          bVar2 = true;
          QString::QString(local_a8,(QArrayDataPointer *)local_68);
        }
        else {
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_48,(QTypedArrayData *)0x0,L"background",10
                    );
          bVar1 = true;
          QString::QString(local_a8,(QArrayDataPointer *)local_48);
        }
      }
      else {
        QArrayDataPointer<char16_t>::QArrayDataPointer(local_88,(QTypedArrayData *)0x0,L"hidden",6);
        bVar3 = true;
        QString::QString(local_a8,(QArrayDataPointer *)local_88);
      }
      if (bVar1) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_48);
      }
      if (bVar2) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_68);
      }
      if (bVar3) {
        QArrayDataPointer<char16_t>::~QArrayDataPointer(local_88);
      }
      auVar7 = QHash<unsigned_int,QString>::find
                         ((QHash<unsigned_int,QString> *)(this + 0xb8),(uint *)(lVar6 + 100));
      local_68[0] = auVar7;
      auVar7 = QHash<unsigned_int,QString>::end();
      local_48 = auVar7;
      cVar4 = QHash<unsigned_int,QString>::iterator::operator!=
                        ((iterator *)local_68,(iterator *)local_48);
      if (cVar4 == '\0') {
LAB_0017a62d:
        bVar1 = false;
      }
      else {
        pQVar5 = (QString *)QHash<unsigned_int,QString>::iterator::value((iterator *)local_68);
        cVar4 = ::operator==(pQVar5,local_a8);
        if (cVar4 == '\0') goto LAB_0017a62d;
        bVar1 = true;
      }
      if (!bVar1) {
        pQVar5 = (QString *)QHash<unsigned_int,QString>::operator[]((uint *)(this + 0xb8));
        QString::operator=(pQVar5,local_a8);
        QString::QString((QString *)local_48,local_a8);
        windowTierNeeded(this,*(undefined4 *)(lVar6 + 100),local_48);
        QString::~QString((QString *)local_48);
      }
      QString::~QString(local_a8);
    }
    local_cc = local_cc + 1;
  } while( true );
}



// ==== 0017a76a  NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}::operator()

/* NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  *(undefined1 *)(*(long *)this + 0xac) = 0;
  recomputeCoveringCount(*(NCDEWindowManager **)this);
  return;
}



// ==== 0017a796  NCDEWindowManager::scheduleCoveringRecount

/* NCDEWindowManager::scheduleCoveringRecount() */

void __thiscall NCDEWindowManager::scheduleCoveringRecount(NCDEWindowManager *this)

{
  long in_FS_OFFSET;
  NCDEWindowManager *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0xac] == (NCDEWindowManager)0x0) {
    this[0xac] = (NCDEWindowManager)0x1;
    local_18 = this;
    QTimer::singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::_lambda()_1_>
              (0,(ContextType *)this,(_lambda___1_ *)&local_18);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017a802  NCDEWindowManager::recomputeCoveringCount

/* NCDEWindowManager::recomputeCoveringCount() */

void __thiscall NCDEWindowManager::recomputeCoveringCount(NCDEWindowManager *this)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  int local_3c;
  undefined8 local_38;
  undefined8 local_30;
  QList<NCDEWindowManager::WindowEntry> *local_28;
  undefined4 *local_20;
  void *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_3c = 0;
  local_28 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
  local_38 = QList<NCDEWindowManager::WindowEntry>::begin(local_28);
  local_30 = QList<NCDEWindowManager::WindowEntry>::end(local_28);
  do {
    cVar2 = QList<NCDEWindowManager::WindowEntry>::iterator::operator!=
                      ((iterator *)&local_38,local_30);
    if (cVar2 == '\0') {
      if (local_3c != *(int *)(this + 0xa8)) {
        *(int *)(this + 0xa8) = local_3c;
        coveringCountChanged(this);
      }
      if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    local_20 = (undefined4 *)
               QList<NCDEWindowManager::WindowEntry>::iterator::operator*((iterator *)&local_38);
    if ((*(char *)(local_20 + 0x18) == '\0') && (*(char *)((long)local_20 + 0x61) == '\x01')) {
      if (*(long *)(this + 0x20) != 0) {
        uVar3 = xcb_get_window_attributes(*(undefined8 *)(this + 0x20),*local_20);
        local_18 = (void *)xcb_get_window_attributes_reply(*(undefined8 *)(this + 0x20),uVar3,0);
        if ((local_18 == (void *)0x0) || (*(char *)((long)local_18 + 0x1a) != '\x02')) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        free(local_18);
        if (!bVar1) goto LAB_0017a90f;
      }
      local_3c = local_3c + 1;
    }
LAB_0017a90f:
    QList<NCDEWindowManager::WindowEntry>::iterator::operator++((iterator *)&local_38);
  } while( true );
}



// ==== 0017a976  NCDEWindowManager::setGeom

/* NCDEWindowManager::setGeom(unsigned int, int, int, int, int) */

void __thiscall
NCDEWindowManager::setGeom
          (NCDEWindowManager *this,uint param_1,int param_2,int param_3,int param_4,int param_5)

{
  code *pcVar1;
  bool bVar2;
  bool bVar3;
  uint *puVar4;
  long lVar5;
  long in_FS_OFFSET;
  int local_cc;
  QModelIndex local_c8 [32];
  QModelIndex local_a8 [32];
  QModelIndex local_88 [32];
  QList local_68 [32];
  QList<int> local_48 [16];
  undefined8 local_38;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_cc = 0;
  do {
    lVar5 = QList<NCDEWindowManager::WindowEntry>::size
                      ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar5 <= local_cc) {
LAB_0017ad26:
      if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    puVar4 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)local_cc);
    if (param_1 == *puVar4) {
      if ((param_2 < 0) ||
         (lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc),
         param_2 == *(int *)(lVar5 + 8))) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      if (bVar3) {
        lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
        *(int *)(lVar5 + 8) = param_2;
      }
      if ((param_3 < 0) ||
         (lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc),
         param_3 == *(int *)(lVar5 + 0xc))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
        *(int *)(lVar5 + 0xc) = param_3;
        bVar3 = true;
      }
      if ((param_4 < 0) ||
         (lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc),
         param_4 == *(int *)(lVar5 + 0x10))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
        *(int *)(lVar5 + 0x10) = param_4;
        bVar3 = true;
      }
      if ((param_5 < 0) ||
         (lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc),
         param_5 == *(int *)(lVar5 + 0x14))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        lVar5 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_cc);
        *(int *)(lVar5 + 0x14) = param_5;
        bVar3 = true;
      }
      if (bVar3) {
        local_48[0] = (QList<int>)0x0;
        local_48[1] = (QList<int>)0x0;
        local_48[2] = (QList<int>)0x0;
        local_48[3] = (QList<int>)0x0;
        local_48[4] = (QList<int>)0x0;
        local_48[5] = (QList<int>)0x0;
        local_48[6] = (QList<int>)0x0;
        local_48[7] = (QList<int>)0x0;
        local_48[8] = (QList<int>)0x0;
        local_48[9] = (QList<int>)0x0;
        local_48[10] = (QList<int>)0x0;
        local_48[0xb] = (QList<int>)0x0;
        local_48[0xc] = (QList<int>)0x0;
        local_48[0xd] = (QList<int>)0x0;
        local_48[0xe] = (QList<int>)0x0;
        local_48[0xf] = (QList<int>)0x0;
        local_38 = 0;
        QList<int>::QList(local_48);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_88);
        (*pcVar1)(local_68,this,local_cc,0,local_88);
        pcVar1 = *(code **)(*(long *)this + 0x60);
        QModelIndex::QModelIndex(local_c8);
        (*pcVar1)(local_a8,this,local_cc,0,local_c8);
        QAbstractItemModel::dataChanged((QModelIndex *)this,local_a8,local_68);
        QList<int>::~QList(local_48);
      }
      goto LAB_0017ad26;
    }
    local_cc = local_cc + 1;
  } while( true );
}



// ==== 0017ad48  NCDEWindowManager::onMapRequest

/* NCDEWindowManager::onMapRequest(xcb_map_request_event_t*) */

void __thiscall
NCDEWindowManager::onMapRequest(NCDEWindowManager *this,xcb_map_request_event_t *param_1)

{
  manage(this,*(uint *)(param_1 + 8));
  return;
}



// ==== 0017ad70  NCDEWindowManager::onConfigureRequest

/* NCDEWindowManager::onConfigureRequest(xcb_configure_request_event_t*) */

void __thiscall
NCDEWindowManager::onConfigureRequest
          (NCDEWindowManager *this,xcb_configure_request_event_t *param_1)

{
  ushort uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  long lVar11;
  int iVar12;
  long in_FS_OFFSET;
  bool bVar13;
  byte bVar14;
  int local_12c;
  int local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  QModelIndex local_108 [32];
  QModelIndex local_e8 [32];
  QModelIndex local_c8 [32];
  QList local_a8 [32];
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined2 local_78;
  undefined2 uStack_76;
  undefined2 uStack_74;
  undefined2 uStack_72;
  undefined2 local_70;
  undefined1 local_6e;
  undefined1 uStack_6d;
  int local_60;
  int local_5c;
  uint local_58 [10];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_12c = -1;
  local_128 = 0;
  while( true ) {
    lVar11 = QList<NCDEWindowManager::WindowEntry>::size
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
    if (lVar11 <= local_128) break;
    piVar10 = (int *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                (long)local_128);
    if (*piVar10 == *(int *)(param_1 + 8)) {
      local_12c = local_128;
      break;
    }
    local_128 = local_128 + 1;
  }
  iVar8 = QHash<unsigned_int,unsigned_int>::value
                    ((QHash<unsigned_int,unsigned_int> *)(this + 0xc0),(uint *)(param_1 + 8));
  bVar13 = iVar8 != 0;
  uVar1 = *(ushort *)(param_1 + 0x1a);
  cVar7 = (char)((*(ushort *)(param_1 + 0x1a) & 2) >> 1);
  local_124 = 0;
  bVar14 = 0;
  if (!bVar13) {
    bVar14 = (uVar1 & 1) != 0;
    if ((bool)bVar14) {
      local_58[0] = (uint)*(short *)(param_1 + 0x10);
    }
    local_124 = (uint)bVar14;
    if (cVar7 != '\0') {
      bVar14 = bVar14 | 2;
      local_58[(int)local_124] = (int)*(short *)(param_1 + 0x12);
      local_124 = local_124 + 1;
    }
  }
  cVar4 = (char)((*(ushort *)(param_1 + 0x1a) & 4) >> 2);
  cVar5 = (char)((*(ushort *)(param_1 + 0x1a) & 8) >> 3);
  bVar6 = false;
  if ((-1 < local_12c) && ((cVar4 != '\0' || (cVar5 != '\0')))) {
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    if (*(char *)(lVar11 + 0x61) != '\0') {
      bVar3 = true;
      goto LAB_0017afaf;
    }
  }
  bVar3 = false;
LAB_0017afaf:
  if (bVar3) {
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    if (cVar4 == '\0') {
      local_120 = *(uint *)(lVar11 + 0x10);
    }
    else {
      local_120 = (uint)*(ushort *)(param_1 + 0x14);
    }
    if (cVar5 == '\0') {
      local_11c = *(uint *)(lVar11 + 0x14);
    }
    else {
      local_11c = (uint)*(ushort *)(param_1 + 0x16);
    }
    if ((local_120 != *(uint *)(lVar11 + 0x10)) || (local_11c != *(uint *)(lVar11 + 0x14))) {
      bVar6 = true;
    }
  }
  if (bVar6) {
    if (cVar4 != '\0') {
      bVar14 = bVar14 | 4;
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      local_58[(int)local_124] = *(uint *)(lVar11 + 0x10);
      local_124 = local_124 + 1;
    }
    if (cVar5 != '\0') {
      bVar14 = bVar14 | 8;
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      local_58[(int)local_124] = *(uint *)(lVar11 + 0x14);
      local_124 = local_124 + 1;
    }
  }
  else {
    if (cVar4 != '\0') {
      bVar14 = bVar14 | 4;
      local_58[(int)local_124] = (uint)*(ushort *)(param_1 + 0x14);
      local_124 = local_124 + 1;
    }
    if (cVar5 != '\0') {
      bVar14 = bVar14 | 8;
      local_58[(int)local_124] = (uint)*(ushort *)(param_1 + 0x16);
      local_124 = local_124 + 1;
    }
  }
  if ((*(ushort *)(param_1 + 0x1a) & 0x10) != 0) {
    bVar14 = bVar14 | 0x10;
    local_58[(int)local_124] = (uint)*(ushort *)(param_1 + 0x18);
  }
  xcb_configure_window(*(undefined8 *)(this + 0x20),*(undefined4 *)(param_1 + 8),bVar14,local_58);
  xcb_flush(*(undefined8 *)(this + 0x20));
  if (-1 < local_12c) {
    if (!bVar13) {
      if ((uVar1 & 1) == 0) {
        lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                           ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
        iVar12 = *(int *)(lVar11 + 8);
      }
      else {
        iVar12 = (int)*(short *)(param_1 + 0x10);
      }
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      *(int *)(lVar11 + 8) = iVar12;
      if (cVar7 == '\0') {
        lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                           ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
        iVar12 = *(int *)(lVar11 + 0xc);
      }
      else {
        iVar12 = (int)*(short *)(param_1 + 0x12);
      }
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      *(int *)(lVar11 + 0xc) = iVar12;
    }
    if (bVar6) {
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      uVar9 = *(uint *)(lVar11 + 0x10);
    }
    else if (cVar4 == '\0') {
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      uVar9 = *(uint *)(lVar11 + 0x10);
    }
    else {
      uVar9 = (uint)*(ushort *)(param_1 + 0x14);
    }
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    *(uint *)(lVar11 + 0x10) = uVar9;
    if (bVar6) {
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      uVar9 = *(uint *)(lVar11 + 0x14);
    }
    else if (cVar5 == '\0') {
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      uVar9 = *(uint *)(lVar11 + 0x14);
    }
    else {
      uVar9 = (uint)*(ushort *)(param_1 + 0x16);
    }
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    *(uint *)(lVar11 + 0x14) = uVar9;
    if (((cVar4 != '\0') || (cVar5 != '\0')) && (iVar8 != 0)) {
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      local_60 = *(int *)(lVar11 + 0x10) + 0x18;
      lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
      local_5c = *(int *)(lVar11 + 0x14) + 0x3a;
      xcb_configure_window(*(undefined8 *)(this + 0x20),iVar8,0xc,&local_60);
      uVar9 = QHash<unsigned_int,unsigned_int>::value
                        ((QHash<unsigned_int,unsigned_int> *)(this + 0xd0),(uint *)(param_1 + 8));
      if (uVar9 != 0) {
        lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                           ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
        iVar8 = *(int *)(lVar11 + 0x14);
        lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                           ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
        setFrameInputRegion(this,uVar9,*(int *)(lVar11 + 0x10) + 0x30,iVar8 + 0x52);
      }
      xcb_flush(*(undefined8 *)(this + 0x20));
    }
    local_88 = 0;
    uStack_84 = 0;
    uStack_80 = 0;
    uStack_7c = 0;
    local_78 = 0;
    uStack_76 = 0;
    uStack_74 = 0;
    uStack_72 = 0;
    QList<int>::QList((QList<int> *)&local_88);
    pcVar2 = *(code **)(*(long *)this + 0x60);
    QModelIndex::QModelIndex(local_c8);
    (*pcVar2)(local_a8,this,local_12c,0,local_c8);
    pcVar2 = *(code **)(*(long *)this + 0x60);
    QModelIndex::QModelIndex(local_108);
    (*pcVar2)(local_e8,this,local_12c,0,local_108);
    QAbstractItemModel::dataChanged((QModelIndex *)this,local_e8,local_a8);
    QList<int>::~QList((QList<int> *)&local_88);
  }
  if (((bVar13) && (((uVar1 & 1) != 0 || (cVar7 != '\0')))) && (-1 < local_12c)) {
    local_78 = 0;
    uStack_76 = 0;
    uStack_74 = 0;
    uStack_72 = 0;
    local_70 = 0;
    local_6e = 0;
    uStack_6d = 0;
    local_88 = 0x16;
    uStack_84 = *(undefined4 *)(param_1 + 8);
    uStack_80 = *(undefined4 *)(param_1 + 8);
    uStack_7c = 0;
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    local_78 = (undefined2)*(undefined4 *)(lVar11 + 8);
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    uStack_76 = (undefined2)*(undefined4 *)(lVar11 + 0xc);
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    uStack_74 = (undefined2)*(undefined4 *)(lVar11 + 0x10);
    lVar11 = QList<NCDEWindowManager::WindowEntry>::operator[]
                       ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_12c);
    uStack_72 = (undefined2)*(undefined4 *)(lVar11 + 0x14);
    local_70 = 0;
    local_6e = 0;
    xcb_send_event(*(undefined8 *)(this + 0x20),0,*(undefined4 *)(param_1 + 8),0x20000,&local_88);
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017b7c2  NCDEWindowManager::getWindowTitle

/* NCDEWindowManager::getWindowTitle(unsigned int) */

QString * NCDEWindowManager::getWindowTitle(uint param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvVar4;
  char *pcVar5;
  int in_EDX;
  long in_RSI;
  undefined4 in_register_0000003c;
  QString *this;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_38 [24];
  long local_20;
  
  this = (QString *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(in_RSI + 0x20) == 0) || (in_EDX == 0)) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_38,(QTypedArrayData *)0x0,L"Window",6);
    QString::QString(this,(QArrayDataPointer *)local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_38);
    goto LAB_0017ba5a;
  }
  uVar2 = xcb_get_property(*(undefined8 *)(in_RSI + 0x20),0,in_EDX,*(undefined4 *)(in_RSI + 0xe8),
                           *(undefined4 *)(in_RSI + 0xec),0,0x100);
  pvVar4 = (void *)xcb_get_property_reply(*(undefined8 *)(in_RSI + 0x20),uVar2,0);
  if (pvVar4 == (void *)0x0) {
LAB_0017b8be:
    bVar1 = false;
  }
  else {
    iVar3 = xcb_get_property_value_length(pvVar4);
    if (iVar3 < 1) goto LAB_0017b8be;
    bVar1 = true;
  }
  if (bVar1) {
    iVar3 = xcb_get_property_value_length(pvVar4);
    pcVar5 = (char *)xcb_get_property_value(pvVar4);
    QString::fromUtf8((QString *)local_38,pcVar5,(long)iVar3);
    free(pvVar4);
    QString::QString(this,(QString *)local_38);
    QString::~QString((QString *)local_38);
    goto LAB_0017ba5a;
  }
  free(pvVar4);
  uVar2 = xcb_get_property(*(undefined8 *)(in_RSI + 0x20),0,in_EDX,0x27,0x1f,0,0x100);
  pvVar4 = (void *)xcb_get_property_reply(*(undefined8 *)(in_RSI + 0x20),uVar2,0);
  if (pvVar4 == (void *)0x0) {
LAB_0017b9a4:
    bVar1 = false;
  }
  else {
    iVar3 = xcb_get_property_value_length(pvVar4);
    if (iVar3 < 1) goto LAB_0017b9a4;
    bVar1 = true;
  }
  if (bVar1) {
    iVar3 = xcb_get_property_value_length(pvVar4);
    pcVar5 = (char *)xcb_get_property_value(pvVar4);
    QString::fromLatin1((QString *)local_38,pcVar5,(long)iVar3);
    free(pvVar4);
    QString::QString(this,(QString *)local_38);
    QString::~QString((QString *)local_38);
  }
  else {
    free(pvVar4);
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_38,(QTypedArrayData *)0x0,L"Window",6);
    QString::QString(this,(QArrayDataPointer *)local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_38);
  }
LAB_0017ba5a:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017ba78  NCDEWindowManager::getWindowClass

/* NCDEWindowManager::getWindowClass(unsigned int) */

QString * NCDEWindowManager::getWindowClass(uint param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  long lVar5;
  int in_EDX;
  long in_RSI;
  undefined4 in_register_0000003c;
  QString *this;
  long in_FS_OFFSET;
  char *local_98;
  void *local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  QByteArray local_58 [32];
  QString local_38 [24];
  long local_20;
  
  this = (QString *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(in_RSI + 0x20) == 0) || (in_EDX == 0)) {
    QString::QString(this);
    goto LAB_0017bcf6;
  }
  uVar2 = xcb_get_property(*(undefined8 *)(in_RSI + 0x20),0,in_EDX,0x43,0x1f,0,0x100);
  local_90 = (void *)xcb_get_property_reply(*(undefined8 *)(in_RSI + 0x20),uVar2,0);
  local_78 = 0;
  local_70 = 0;
  local_68 = 0;
  if (local_90 == (void *)0x0) {
LAB_0017bb6f:
    bVar1 = false;
  }
  else {
    iVar3 = xcb_get_property_value_length(local_90);
    if (iVar3 < 1) goto LAB_0017bb6f;
    bVar1 = true;
  }
  if (bVar1) {
    iVar3 = xcb_get_property_value_length(local_90);
    pcVar4 = (char *)xcb_get_property_value(local_90);
    QByteArray::QByteArray(local_58,pcVar4,(long)iVar3);
    iVar3 = QByteArray::indexOf(local_58,'\0',0);
    if (iVar3 < 0) {
LAB_0017bc46:
      QString::fromLatin1<void>(local_38,local_58);
    }
    else {
      lVar5 = QByteArray::size(local_58);
      if (lVar5 <= iVar3 + 1) goto LAB_0017bc46;
      lVar5 = QByteArray::constData(local_58);
      local_98 = (char *)(lVar5 + (long)iVar3 + 1);
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_88,&local_98);
      QString::fromLatin1(local_38,local_88,local_80);
    }
    QString::operator=((QString *)&local_78,local_38);
    QString::~QString(local_38);
    QByteArray::~QByteArray(local_58);
  }
  free(local_90);
  QString::QString(this,(QString *)&local_78);
  QString::~QString((QString *)&local_78);
LAB_0017bcf6:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0017bd18  NCDEWindowManager::getWindowPid

/* NCDEWindowManager::getWindowPid(unsigned int) */

undefined4 __thiscall NCDEWindowManager::getWindowPid(NCDEWindowManager *this,uint param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  void *__ptr;
  undefined4 *puVar4;
  undefined4 local_14;
  
  if ((*(long *)(this + 0x20) != 0) && (param_1 != 0)) {
    uVar2 = xcb_get_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0x108),6,
                             0,1);
    __ptr = (void *)xcb_get_property_reply(*(undefined8 *)(this + 0x20),uVar2,0);
    local_14 = 0;
    if ((__ptr == (void *)0x0) || (iVar3 = xcb_get_property_value_length(__ptr), iVar3 < 4)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      puVar4 = (undefined4 *)xcb_get_property_value(__ptr);
      local_14 = *puVar4;
    }
    free(__ptr);
    return local_14;
  }
  return 0;
}



// ==== 0017bdea  NCDEWindowManager::onPropertyNotify

/* NCDEWindowManager::onPropertyNotify(unsigned int, unsigned int) */

void __thiscall
NCDEWindowManager::onPropertyNotify(NCDEWindowManager *this,uint param_1,uint param_2)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  long in_FS_OFFSET;
  bool bVar5;
  QModelIndex local_c8 [32];
  QModelIndex local_a8 [32];
  QModelIndex local_88 [32];
  QList local_68 [32];
  QString local_48 [16];
  undefined8 local_38;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  iVar3 = rowForClient(this,param_1);
  if (-1 < iVar3) {
    bVar5 = false;
    if ((param_2 == *(uint *)(this + 0xe8)) || (param_2 == 0x27)) {
      getWindowTitle((uint)local_48);
      lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
      cVar2 = ::operator!=(local_48,(QString *)(lVar4 + 0x18));
      bVar5 = cVar2 != '\0';
      if (bVar5) {
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
        QString::operator=((QString *)(lVar4 + 0x18),local_48);
      }
      QString::~QString(local_48);
    }
    else if (param_2 == 0x43) {
      getWindowClass((uint)local_48);
      lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
      cVar2 = ::operator!=(local_48,(QString *)(lVar4 + 0x30));
      bVar5 = cVar2 != '\0';
      if (bVar5) {
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
        QString::operator=((QString *)(lVar4 + 0x30),local_48);
      }
      QString::~QString(local_48);
    }
    else if (param_2 == *(uint *)(this + 0x144)) {
      GliaTalkProto::readMenus
                ((GliaTalkProto *)local_48,*(xcb_connection_t **)(this + 0x20),param_1);
      lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
      cVar2 = ::operator!=(local_48,(QString *)(lVar4 + 0x48));
      if (cVar2 != '\0') {
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)iVar3);
        QString::operator=((QString *)(lVar4 + 0x48),local_48);
        if (iVar3 == *(int *)(this + 0x40)) {
          activeAppMenusChanged(this);
        }
      }
      QString::~QString(local_48);
    }
    if (bVar5) {
      local_48[0] = (QString)0x0;
      local_48[1] = (QString)0x0;
      local_48[2] = (QString)0x0;
      local_48[3] = (QString)0x0;
      local_48[4] = (QString)0x0;
      local_48[5] = (QString)0x0;
      local_48[6] = (QString)0x0;
      local_48[7] = (QString)0x0;
      local_48[8] = (QString)0x0;
      local_48[9] = (QString)0x0;
      local_48[10] = (QString)0x0;
      local_48[0xb] = (QString)0x0;
      local_48[0xc] = (QString)0x0;
      local_48[0xd] = (QString)0x0;
      local_48[0xe] = (QString)0x0;
      local_48[0xf] = (QString)0x0;
      local_38 = 0;
      QList<int>::QList((QList<int> *)local_48);
      pcVar1 = *(code **)(*(long *)this + 0x60);
      QModelIndex::QModelIndex(local_88);
      (*pcVar1)(local_68,this,iVar3,0,local_88);
      pcVar1 = *(code **)(*(long *)this + 0x60);
      QModelIndex::QModelIndex(local_c8);
      (*pcVar1)(local_a8,this,iVar3,0,local_c8);
      QAbstractItemModel::dataChanged((QModelIndex *)this,local_a8,local_68);
      QList<int>::~QList((QList<int> *)local_48);
      windowStateChanged(this);
    }
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017c260  NCDEWindowManager::onRandRScreenChange

/* NCDEWindowManager::onRandRScreenChange(xcb_randr_screen_change_notify_event_t*) */

void __thiscall
NCDEWindowManager::onRandRScreenChange
          (NCDEWindowManager *this,xcb_randr_screen_change_notify_event_t *param_1)

{
  bool bVar1;
  int *piVar2;
  uint *puVar3;
  long lVar4;
  long lVar5;
  long in_FS_OFFSET;
  int local_48 [5];
  uint local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48[4] = (int)*(ushort *)(param_1 + 0x18);
  local_34 = (uint)*(ushort *)(param_1 + 0x1a);
  if (((local_48[4] != 0) && (local_34 != 0)) &&
     ((local_48[4] != *(uint *)(this + 0x30) || (local_34 != *(uint *)(this + 0x34))))) {
    *(int *)(this + 0x30) = local_48[4];
    *(uint *)(this + 0x34) = local_34;
    for (local_48[3] = 0; lVar5 = (long)local_48[3],
        lVar4 = QList<NCDEWindowManager::WindowEntry>::size
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90)), lVar5 < lVar4;
        local_48[3] = local_48[3] + 1) {
      lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3]);
      if (*(char *)(lVar4 + 0x60) == '\0') {
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3])
        ;
        local_30 = *(int *)(lVar4 + 0x10);
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3])
        ;
        local_2c = *(int *)(lVar4 + 0x14);
        local_48[1] = 0;
        local_48[0] = local_48[4] - local_30;
        piVar2 = qMax<int>(local_48,local_48 + 1);
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3])
        ;
        local_48[2] = 0;
        piVar2 = qBound<int>(local_48 + 2,(int *)(lVar4 + 8),piVar2);
        local_28 = *piVar2;
        local_48[1] = 0x20;
        local_48[0] = local_34 - local_2c;
        piVar2 = qMax<int>(local_48,local_48 + 1);
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3])
        ;
        local_48[2] = 0x20;
        piVar2 = qBound<int>(local_48 + 2,(int *)(lVar4 + 0xc),piVar2);
        local_24 = *piVar2;
        lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                          ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(long)local_48[3])
        ;
        if ((local_28 == *(int *)(lVar4 + 8)) &&
           (lVar4 = QList<NCDEWindowManager::WindowEntry>::operator[]
                              ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                               (long)local_48[3]), local_24 == *(int *)(lVar4 + 0xc))) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (bVar1) {
          puVar3 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                                     ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),
                                      (long)local_48[3]);
          moveWindow(this,*puVar3,local_28,local_24);
        }
      }
    }
    screenConfigChanged(this,local_48[4],local_34);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017c502  NCDEWindowManager::WindowEntry::~WindowEntry

/* NCDEWindowManager::WindowEntry::~WindowEntry() */

void __thiscall NCDEWindowManager::WindowEntry::~WindowEntry(WindowEntry *this)

{
  QString::~QString((QString *)(this + 0x48));
  QString::~QString((QString *)(this + 0x30));
  QString::~QString((QString *)(this + 0x18));
  return;
}



// ==== 0017c542  NCDEWindowManager::manage

/* NCDEWindowManager::manage(unsigned int) */

void __thiscall NCDEWindowManager::manage(NCDEWindowManager *this,uint param_1)

{
  undefined1 auVar1 [16];
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  long in_FS_OFFSET;
  bool bVar6;
  undefined4 local_134;
  QList<NCDEWindowManager::WindowEntry> *local_130;
  void *local_128;
  uint *local_120;
  undefined4 local_118 [8];
  ulong local_f8 [3];
  int local_dc;
  int local_d8;
  undefined1 local_a8 [8];
  int iStack_a0;
  int iStack_9c;
  undefined1 local_98 [8];
  QString aQStack_90 [8];
  undefined1 local_88 [16];
  QString local_78 [16];
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined1 local_48 [16];
  undefined4 local_38;
  undefined4 local_34;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_130 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
  local_f8[0] = QList<NCDEWindowManager::WindowEntry>::begin(local_130);
  uVar5 = QList<NCDEWindowManager::WindowEntry>::end(local_130);
  local_a8 = (undefined1  [8])uVar5;
  while( true ) {
    cVar2 = QList<NCDEWindowManager::WindowEntry>::iterator::operator!=
                      ((iterator *)local_f8,local_a8);
    if (cVar2 == '\0') break;
    local_120 = (uint *)QList<NCDEWindowManager::WindowEntry>::iterator::operator*
                                  ((iterator *)local_f8);
    if (param_1 == *local_120) goto LAB_0017cbd2;
    QList<NCDEWindowManager::WindowEntry>::iterator::operator++((iterator *)local_f8);
  }
  uVar3 = xcb_get_geometry(*(undefined8 *)(this + 0x20),param_1);
  local_128 = (void *)xcb_get_geometry_reply(*(undefined8 *)(this + 0x20),uVar3,0);
  _local_98 = (undefined1  [16])0x0;
  local_88 = (undefined1  [16])0x0;
  local_78[0] = (QString)0x0;
  local_78[1] = (QString)0x0;
  local_78[2] = (QString)0x0;
  local_78[3] = (QString)0x0;
  local_78[4] = (QString)0x0;
  local_78[5] = (QString)0x0;
  local_78[6] = (QString)0x0;
  local_78[7] = (QString)0x0;
  local_78[8] = (QString)0x0;
  local_78[9] = (QString)0x0;
  local_78[10] = (QString)0x0;
  local_78[0xb] = (QString)0x0;
  local_78[0xc] = (QString)0x0;
  local_78[0xd] = (QString)0x0;
  local_78[0xe] = (QString)0x0;
  local_78[0xf] = (QString)0x0;
  local_68 = (undefined1  [16])0x0;
  local_58 = (undefined1  [16])0x0;
  local_48 = (undefined1  [16])0x0;
  stack0xffffffffffffff5c = SUB1612((undefined1  [16])0x0,4);
  local_a8._0_4_ = param_1;
  if (local_128 != (void *)0x0) {
    iStack_a0 = (int)*(short *)((long)local_128 + 0xc);
    iStack_9c = (int)*(short *)((long)local_128 + 0xe);
    local_98._2_2_ = 0;
    local_98._0_2_ = *(ushort *)((long)local_128 + 0x10);
    stack0xffffffffffffff6c = SUB1612((undefined1  [16])0x0,4);
    local_98._4_2_ = *(undefined2 *)((long)local_128 + 0x12);
    local_98._6_2_ = 0;
    free(local_128);
  }
  if ((iStack_a0 < 1) && (iStack_9c < 1)) {
    iStack_a0 = 100;
    iStack_9c = 0x50;
  }
  if (iStack_a0 < 0x18) {
    iStack_a0 = 0x18;
  }
  if (iStack_9c < 0x2c) {
    iStack_9c = 0x2c;
  }
  if (((int)local_98._0_4_ < 2) || ((int)local_98._4_4_ < 2)) {
    local_98 = (undefined1  [8])0x23000000320;
  }
  if ((int)local_98._0_4_ < 200) {
    local_98._0_4_ = 200;
  }
  if ((int)local_98._4_4_ < 100) {
    local_98._4_4_ = 100;
  }
  bVar6 = false;
  uVar3 = xcb_icccm_get_wm_normal_hints(*(undefined8 *)(this + 0x20),param_1);
  cVar2 = xcb_icccm_get_wm_normal_hints_reply(*(undefined8 *)(this + 0x20),uVar3,local_f8,0);
  if ((((cVar2 != '\0') && ((local_f8[0] & 0x20) != 0)) && (0 < local_dc)) &&
     (((0 < local_d8 && (local_dc < *(int *)(this + 0x30))) && (local_d8 < *(int *)(this + 0x34)))))
  {
    bVar6 = true;
  }
  if (bVar6) {
    local_48[1] = 0;
  }
  else {
    local_98._4_4_ = *(int *)(this + 0x34) + -0x3a;
    local_98._0_4_ = *(int *)(this + 0x30) + -0x18;
    local_48[1] = 1;
  }
  iStack_a0 = 0xc;
  auVar1 = local_48;
  iStack_9c = 0x20;
  local_48[1] = (char)((ushort)local_48._0_2_ >> 8);
  bVar6 = local_48[1] != '\0';
  local_48 = auVar1;
  if (bVar6) {
    local_38 = *(undefined4 *)(this + 0xfc);
    local_34 = *(undefined4 *)(this + 0x100);
    xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0xf8),4,0x20,2
                        ,&local_38);
  }
  local_134 = 0x620000;
  xcb_change_window_attributes(*(undefined8 *)(this + 0x20),param_1,0x800,&local_134);
  getWindowTitle((uint)local_118);
  QString::operator=(aQStack_90,(QString *)local_118);
  QString::~QString((QString *)local_118);
  getWindowClass((uint)local_118);
  QString::operator=(local_78,(QString *)local_118);
  QString::~QString((QString *)local_118);
  uVar3 = getWindowPid(this,param_1);
  local_48._4_4_ = uVar3;
  GliaTalkProto::readMenus((GliaTalkProto *)local_118,*(xcb_connection_t **)(this + 0x20),param_1);
  QString::operator=((QString *)(local_68 + 8),(QString *)local_118);
  QString::~QString((QString *)local_118);
  local_48._8_4_ = *(undefined4 *)(this + 0x150);
  if (*(int *)(this + 0x140) != 0) {
    local_118[0] = *(undefined4 *)(this + 0x150);
    xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,*(undefined4 *)(this + 0x140),6,0x20,
                        1,local_118);
  }
  QList<NCDEWindowManager::WindowEntry>::size
            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
  iVar4 = QList<NCDEWindowManager::WindowEntry>::size
                    ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
  QModelIndex::QModelIndex((QModelIndex *)local_118);
  QAbstractItemModel::beginInsertRows((QModelIndex *)this,(int)local_118,iVar4);
  QList<NCDEWindowManager::WindowEntry>::append
            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90),(WindowEntry *)local_a8);
  QAbstractItemModel::endInsertRows();
  countChanged(this);
  windowAdded(this,local_a8._0_4_,iStack_a0,iStack_9c,local_98._0_4_,local_98._4_4_,aQStack_90,
              local_78);
  anyWindowMapped(this);
  emitTierUpdates(this);
  WindowEntry::~WindowEntry((WindowEntry *)local_a8);
LAB_0017cbd2:
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017cbf2  NCDEWindowManager::findArgbVisual

/* NCDEWindowManager::findArgbVisual() const */

undefined4 __thiscall NCDEWindowManager::findArgbVisual(NCDEWindowManager *this)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  undefined1 local_38 [16];
  undefined1 local_28 [16];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = xcb_get_setup(*(undefined8 *)(this + 0x20));
  lVar3 = xcb_setup_roots_iterator(uVar2);
  if (lVar3 == 0) {
    uVar1 = 0;
  }
  else {
    local_38 = xcb_screen_allowed_depths_iterator(lVar3);
    while( true ) {
      if (local_38._8_4_ == 0) break;
      if (*(char *)local_38._0_8_ == ' ') {
        auVar4 = xcb_depth_visuals_iterator(local_38._0_8_);
        local_28 = auVar4;
        while( true ) {
          if (local_28._8_4_ == 0) break;
          if (*(char *)(local_28._0_8_ + 4) == '\x04') {
            uVar1 = *(undefined4 *)local_28._0_8_;
            goto LAB_0017ccb0;
          }
          xcb_visualtype_next(local_28);
        }
      }
      xcb_depth_next(local_38);
    }
    uVar1 = 0;
  }
LAB_0017ccb0:
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017ccc6  NCDEWindowManager::setWmClass

/* NCDEWindowManager::setWmClass(unsigned int, char const*) */

void __thiscall NCDEWindowManager::setWmClass(NCDEWindowManager *this,uint param_1,char *param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = 0;
  local_30 = 0;
  local_28 = 0;
  QByteArray::append((QByteArray *)&local_38,param_2);
  QByteArray::append((char)&local_38);
  QByteArray::append((QByteArray *)&local_38,param_2);
  QByteArray::append((char)&local_38);
  uVar2 = QByteArray::constData((QByteArray *)&local_38);
  uVar1 = QByteArray::size((QByteArray *)&local_38);
  xcb_change_property(*(undefined8 *)(this + 0x20),0,param_1,0x43,0x1f,8,uVar1,uVar2);
  QByteArray::~QByteArray((QByteArray *)&local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017cdec  NCDEWindowManager::createContainer

/* NCDEWindowManager::createContainer(int, int, int, int, bool) */

uint __thiscall
NCDEWindowManager::createContainer
          (NCDEWindowManager *this,int param_1,int param_2,int param_3,int param_4,bool param_5)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long lVar5;
  long in_FS_OFFSET;
  undefined1 local_49;
  int local_48;
  undefined4 local_44;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar1 = xcb_generate_id(*(undefined8 *)(this + 0x20));
  uVar4 = xcb_get_setup(*(undefined8 *)(this + 0x20));
  lVar5 = xcb_setup_roots_iterator(uVar4);
  if (lVar5 == 0) {
    local_48 = 0;
  }
  else {
    local_48 = *(int *)(lVar5 + 0x20);
  }
  local_49 = 0;
  local_44 = 0x80a;
  local_28 = 0;
  uStack_24 = 0;
  uStack_20 = 0x180000;
  if (param_5) {
    iVar2 = findArgbVisual(this);
    if (iVar2 != 0) {
      local_49 = 0x20;
      uVar3 = xcb_generate_id(*(undefined8 *)(this + 0x20));
      xcb_create_colormap(*(undefined8 *)(this + 0x20),0,uVar3,*(undefined4 *)(this + 0x28),iVar2);
      local_44 = 0x280a;
      local_48 = iVar2;
      uStack_1c = uVar3;
    }
  }
  xcb_create_window(*(undefined8 *)(this + 0x20),local_49,uVar1,*(undefined4 *)(this + 0x28),
                    (int)(short)param_1,(int)(short)param_2,param_3 & 0xffff,param_4 & 0xffff,0,1,
                    local_48,local_44,&local_28);
  setWmClass(this,uVar1,"ncde-container");
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 0017cfb2  NCDEWindowManager::setFrameInputRegion

/* NCDEWindowManager::setFrameInputRegion(unsigned int, int, int) */

void __thiscall
NCDEWindowManager::setFrameInputRegion(NCDEWindowManager *this,uint param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  undefined1 auVar3 [14];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [12];
  long in_FS_OFFSET;
  undefined1 local_38 [4];
  short sStack_34;
  undefined2 uStack_30;
  undefined2 uStack_2e;
  undefined2 uStack_2c;
  unkbyte10 Stack_32;
  short sStack_2a;
  undefined1 local_28 [6];
  short sStack_22;
  undefined2 uStack_20;
  short sStack_1e;
  short sStack_1c;
  undefined2 uStack_1a;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  stack0xffffffffffffffca = SUB1614((undefined1  [16])0x0,2);
  auVar3 = stack0xffffffffffffffca;
  uStack_30 = 0xc;
  _local_38 = 0x20000000000000;
  uStack_2e = 0x2c;
  sStack_2a = auVar3._12_2_;
  uStack_2c = 0xc;
  stack0xffffffffffffffdc = SUB1612((undefined1  [16])0x0,4);
  auVar6 = stack0xffffffffffffffdc;
  local_28 = (undefined1  [6])0xc002c0000;
  auVar4 = _local_28;
  _sStack_1e = auVar6._6_6_;
  _local_28 = auVar4._0_8_;
  uStack_20 = 0xc;
  uStack_1a = 0x1a;
  auVar4 = _local_28;
  sVar1 = (short)param_2;
  sStack_34 = sVar1 + -0x18;
  local_38 = (undefined1  [4])0xc000c;
  sVar2 = (short)param_3;
  sStack_2a = sVar2 + -0x52;
  local_28._0_2_ = sVar1 + -0x18;
  auVar5 = _local_28;
  _uStack_20 = auVar4._8_8_;
  local_28 = auVar5._0_6_;
  sStack_22 = sVar2 + -0x52;
  sStack_1e = sVar2 + -0x26;
  sStack_1c = sVar1 + -0x18;
  uStack_1a = 0x1a;
  xcb_shape_rectangles(*(undefined8 *)(this + 0x20),0,2,0,param_1,0,0,4,local_38);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017d0ae  NCDEWindowManager::registerFrameWindow

/* NCDEWindowManager::registerFrameWindow(unsigned int, unsigned int) */

void __thiscall
NCDEWindowManager::registerFrameWindow(NCDEWindowManager *this,uint param_1,uint param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  uint local_48;
  uint local_44;
  NCDEWindowManager *local_40;
  uint local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = param_2;
  local_44 = param_1;
  local_40 = this;
  if ((((this[0x48] == (NCDEWindowManager)0x1) && (*(long *)(this + 0x20) != 0)) && (param_1 != 0))
     && ((param_2 != 0 && (local_2c = rowForClient(this,param_1), -1 < local_2c)))) {
    lVar1 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_2c);
    local_28 = *(int *)(lVar1 + 8);
    lVar1 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_2c);
    local_24 = *(int *)(lVar1 + 0xc);
    lVar1 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_2c);
    local_20 = *(int *)(lVar1 + 0x10);
    lVar1 = QList<NCDEWindowManager::WindowEntry>::operator[]
                      ((QList<NCDEWindowManager::WindowEntry> *)(local_40 + 0x90),(long)local_2c);
    local_1c = *(int *)(lVar1 + 0x14);
    QHash<unsigned_int,unsigned_int>::insert
              ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xd0),&local_44,&local_48);
    QHash<unsigned_int,unsigned_int>::insert
              ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xd8),&local_48,&local_44);
    local_30 = createContainer(local_40,local_28 + -0xc,local_24 + -0x20,local_20 + 0x18,
                               local_1c + 0x3a,false);
    QHash<unsigned_int,unsigned_int>::insert
              ((QHash<unsigned_int,unsigned_int> *)(local_40 + 0xc0),&local_44,&local_30);
    QHash<unsigned_int,unsigned_int>::insert
              ((QHash<unsigned_int,unsigned_int> *)(local_40 + 200),&local_30,&local_44);
    xcb_change_save_set(*(undefined8 *)(local_40 + 0x20),0,local_44);
    xcb_reparent_window(*(undefined8 *)(local_40 + 0x20),local_44,local_30,0xc,0x20);
    local_18 = CONCAT44(local_1c,local_20);
    xcb_configure_window(*(undefined8 *)(local_40 + 0x20),local_44,0xc,&local_18);
    xcb_map_window(*(undefined8 *)(local_40 + 0x20),local_44);
    xcb_map_window(*(undefined8 *)(local_40 + 0x20),local_30);
    local_18 = (ulong)local_30;
    xcb_configure_window(*(undefined8 *)(local_40 + 0x20),local_48,0x60,&local_18);
    setFrameInputRegion(local_40,local_48,local_20 + 0x30,local_1c + 0x52);
    setWmClass(local_40,local_48,"ncde-frame");
    xcb_flush(*(undefined8 *)(local_40 + 0x20));
    activateWindow(local_40,local_44);
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017d37e  NCDEWindowManager::switchDesktop

/* NCDEWindowManager::switchDesktop(int) */

void __thiscall NCDEWindowManager::switchDesktop(NCDEWindowManager *this,int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  QList<NCDEWindowManager::WindowEntry> *local_20;
  uint *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((((*(long *)(this + 0x20) != 0) && (-1 < param_1)) && (param_1 < 4)) &&
     (param_1 != *(int *)(this + 0x150))) {
    *(int *)(this + 0x150) = param_1;
    if (*(int *)(this + 0x13c) != 0) {
      local_28 = CONCAT44(local_28._4_4_,param_1);
      xcb_change_property(*(undefined8 *)(this + 0x20),0,*(undefined4 *)(this + 0x28),
                          *(undefined4 *)(this + 0x13c),6,0x20,1,&local_28);
    }
    local_20 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
    local_30 = QList<NCDEWindowManager::WindowEntry>::begin(local_20);
    local_28 = QList<NCDEWindowManager::WindowEntry>::end(local_20);
    while( true ) {
      cVar1 = QList<NCDEWindowManager::WindowEntry>::iterator::operator!=
                        ((iterator *)&local_30,local_28);
      if (cVar1 == '\0') break;
      local_18 = (uint *)QList<NCDEWindowManager::WindowEntry>::iterator::operator*
                                   ((iterator *)&local_30);
      if ((char)local_18[0x18] == '\0') {
        iVar2 = QHash<unsigned_int,unsigned_int>::value
                          ((QHash<unsigned_int,unsigned_int> *)(this + 0xc0),local_18);
        iVar3 = QHash<unsigned_int,unsigned_int>::value
                          ((QHash<unsigned_int,unsigned_int> *)(this + 0xd0),local_18);
        if (param_1 == local_18[0x1a]) {
          if (iVar2 != 0) {
            xcb_map_window(*(undefined8 *)(this + 0x20),iVar2);
          }
          if (iVar3 != 0) {
            xcb_map_window(*(undefined8 *)(this + 0x20),iVar3);
          }
          xcb_map_window(*(undefined8 *)(this + 0x20),*local_18);
        }
        else {
          if (iVar2 != 0) {
            xcb_unmap_window(*(undefined8 *)(this + 0x20),iVar2);
          }
          if (iVar3 != 0) {
            xcb_unmap_window(*(undefined8 *)(this + 0x20),iVar3);
          }
          xcb_unmap_window(*(undefined8 *)(this + 0x20),*local_18);
        }
      }
      QList<NCDEWindowManager::WindowEntry>::iterator::operator++((iterator *)&local_30);
    }
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017d5bc  NCDEWindowManager::onDestroy

/* NCDEWindowManager::onDestroy(unsigned int) */

void __thiscall NCDEWindowManager::onDestroy(NCDEWindowManager *this,uint param_1)

{
  NCDEWindowManager *pNVar1;
  uint *puVar2;
  long lVar3;
  long lVar4;
  long in_FS_OFFSET;
  uint local_54;
  NCDEWindowManager *local_50;
  int local_44;
  int local_40;
  uint local_3c;
  uint local_38 [6];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_54 = param_1;
  local_50 = this;
  for (local_44 = 0; lVar4 = (long)local_44,
      lVar3 = QList<NCDEWindowManager::WindowEntry>::size
                        ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90)), lVar4 < lVar3;
      local_44 = local_44 + 1) {
    puVar2 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                               ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),
                                (long)local_44);
    if (*puVar2 == local_54) {
      if (*(long *)(local_50 + 0x20) != 0) {
        local_38[0] = QHash<unsigned_int,unsigned_int>::take
                                ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xd0),&local_54);
        if (local_38[0] != 0) {
          QHash<unsigned_int,unsigned_int>::remove
                    ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xd8),local_38);
          xcb_unmap_window(*(undefined8 *)(local_50 + 0x20),local_38[0]);
        }
        local_38[0] = QHash<unsigned_int,unsigned_int>::take
                                ((QHash<unsigned_int,unsigned_int> *)(local_50 + 0xc0),&local_54);
        if (local_38[0] != 0) {
          QHash<unsigned_int,unsigned_int>::remove
                    ((QHash<unsigned_int,unsigned_int> *)(local_50 + 200),local_38);
          xcb_unmap_window(*(undefined8 *)(local_50 + 0x20),local_38[0]);
          xcb_destroy_window(*(undefined8 *)(local_50 + 0x20),local_38[0]);
        }
        xcb_flush(*(undefined8 *)(local_50 + 0x20));
      }
      QHash<unsigned_int,QObject*>::remove
                ((QHash<unsigned_int,QObject*> *)(local_50 + 0xb0),&local_54);
      lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                        ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),(long)local_44);
      pNVar1 = local_50;
      local_3c = *(uint *)(lVar3 + 100);
      QModelIndex::QModelIndex((QModelIndex *)local_38);
      QAbstractItemModel::beginRemoveRows((QModelIndex *)pNVar1,(int)local_38,local_44);
      QList<NCDEWindowManager::WindowEntry>::removeAt
                ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),(long)local_44);
      QAbstractItemModel::endRemoveRows();
      countChanged(local_50);
      windowRemoved(local_50,local_54);
      if (local_3c != 0) {
        windowClosed(local_50,local_3c);
      }
      local_40 = QList<NCDEWindowManager::WindowEntry>::size
                           ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90));
      goto LAB_0017d81d;
    }
  }
  goto LAB_0017d84f;
  while (lVar3 = QList<NCDEWindowManager::WindowEntry>::operator[]
                           ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),
                            (long)local_40), *(char *)(lVar3 + 0x60) == '\x01') {
LAB_0017d81d:
    local_40 = local_40 + -1;
    if (local_40 < 0) goto LAB_0017d84f;
  }
  puVar2 = (uint *)QList<NCDEWindowManager::WindowEntry>::operator[]
                             ((QList<NCDEWindowManager::WindowEntry> *)(local_50 + 0x90),
                              (long)local_40);
  activateWindow(local_50,*puVar2);
LAB_0017d84f:
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0017d86a  NCDEWindowManager::watchPicomOwner

/* NCDEWindowManager::watchPicomOwner() */

void __thiscall NCDEWindowManager::watchPicomOwner(NCDEWindowManager *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  undefined4 local_1c;
  void *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x20) != 0) && (*(int *)(this + 0x104) != 0)) {
    uVar1 = xcb_get_selection_owner(*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x104));
    local_18 = (void *)xcb_get_selection_owner_reply(*(undefined8 *)(this + 0x20),uVar1,0);
    if (local_18 == (void *)0x0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(undefined4 *)((long)local_18 + 8);
    }
    *(undefined4 *)(this + 0x14c) = uVar1;
    free(local_18);
    if (*(int *)(this + 0x14c) != 0) {
      local_1c = 0x20000;
      xcb_change_window_attributes
                (*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x14c),0x800,&local_1c);
      xcb_flush(*(undefined8 *)(this + 0x20));
    }
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017d970  NCDEWindowManager::onPicomDied()::{lambda()#1}::operator()

/* NCDEWindowManager::onPicomDied()::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall NCDEWindowManager::onPicomDied()::{lambda()#1}::operator()(_lambda___1_ *this)

{
  watchPicomOwner(*(NCDEWindowManager **)this);
  return;
}



// ==== 0017d98e  NCDEWindowManager::onPicomDied

/* NCDEWindowManager::onPicomDied() */

void __thiscall NCDEWindowManager::onPicomDied(NCDEWindowManager *this)

{
  long in_FS_OFFSET;
  NCDEWindowManager *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  *(undefined4 *)(this + 0x14c) = 0;
  local_18 = this;
  QTimer::singleShot<int,NCDEWindowManager::onPicomDied()::_lambda()_1_>
            (800,(ContextType *)this,(_lambda___1_ *)&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0017dac4  NCDEWindowManager::~NCDEWindowManager

/* NCDEWindowManager::~NCDEWindowManager() */

void __thiscall NCDEWindowManager::~NCDEWindowManager(NCDEWindowManager *this)

{
  *(undefined ***)this = &PTR_metaObject_0032be70;
  *(undefined **)(this + 0x10) = &DAT_0032c010;
  QHash<unsigned_int,unsigned_int>::~QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xd8));
  QHash<unsigned_int,unsigned_int>::~QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xd0));
  QHash<unsigned_int,unsigned_int>::~QHash((QHash<unsigned_int,unsigned_int> *)(this + 200));
  QHash<unsigned_int,unsigned_int>::~QHash((QHash<unsigned_int,unsigned_int> *)(this + 0xc0));
  QHash<unsigned_int,QString>::~QHash((QHash<unsigned_int,QString> *)(this + 0xb8));
  QHash<unsigned_int,QObject*>::~QHash((QHash<unsigned_int,QObject*> *)(this + 0xb0));
  QList<NCDEWindowManager::WindowEntry>::~QList
            ((QList<NCDEWindowManager::WindowEntry> *)(this + 0x90));
  QTimer::~QTimer((QTimer *)(this + 0x68));
  QTimer::~QTimer((QTimer *)(this + 0x58));
  QAbstractNativeEventFilter::~QAbstractNativeEventFilter
            ((QAbstractNativeEventFilter *)(this + 0x10));
  QAbstractListModel::~QAbstractListModel((QAbstractListModel *)this);
  return;
}



// ==== 0017dbaa  NCDEWindowManager::~NCDEWindowManager

/* non-virtual thunk to NCDEWindowManager::~NCDEWindowManager() */

void __thiscall NCDEWindowManager::~NCDEWindowManager(NCDEWindowManager *this)

{
  ~NCDEWindowManager(this + -0x10);
  return;
}



// ==== 0017dbb4  NCDEWindowManager::~NCDEWindowManager

/* NCDEWindowManager::~NCDEWindowManager() */

void __thiscall NCDEWindowManager::~NCDEWindowManager(NCDEWindowManager *this)

{
  ~NCDEWindowManager(this);
  operator_delete(this,0x158);
  return;
}



// ==== 0017dbdf  NCDEWindowManager::~NCDEWindowManager

/* non-virtual thunk to NCDEWindowManager::~NCDEWindowManager() */

void __thiscall NCDEWindowManager::~NCDEWindowManager(NCDEWindowManager *this)

{
  ~NCDEWindowManager(this + -0x10);
  return;
}



// ==== 001bca8c  NCDEWindowManager::WindowEntry::WindowEntry

/* NCDEWindowManager::WindowEntry::WindowEntry(NCDEWindowManager::WindowEntry const&) */

void __thiscall NCDEWindowManager::WindowEntry::WindowEntry(WindowEntry *this,WindowEntry *param_1)

{
  *(undefined4 *)this = *(undefined4 *)param_1;
  *(undefined4 *)(this + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(param_1 + 0x14);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  this[0x60] = param_1[0x60];
  this[0x61] = param_1[0x61];
  this[0x62] = param_1[0x62];
  *(undefined4 *)(this + 100) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(this + 0x68) = *(undefined4 *)(param_1 + 0x68);
  return;
}



// ==== 001bcb8c  NCDEWindowManager::WindowEntry::WindowEntry

/* NCDEWindowManager::WindowEntry::WindowEntry(NCDEWindowManager::WindowEntry&&) */

void __thiscall NCDEWindowManager::WindowEntry::WindowEntry(WindowEntry *this,WindowEntry *param_1)

{
  *(undefined4 *)this = *(undefined4 *)param_1;
  *(undefined4 *)(this + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(param_1 + 0x14);
  QString::QString((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::QString((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::QString((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  this[0x60] = param_1[0x60];
  this[0x61] = param_1[0x61];
  this[0x62] = param_1[0x62];
  *(undefined4 *)(this + 100) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(this + 0x68) = *(undefined4 *)(param_1 + 0x68);
  return;
}



// ==== 001bd1f4  NCDEWindowManager::WindowEntry::operator=

/* NCDEWindowManager::WindowEntry::TEMPNAMEPLACEHOLDERVALUE(NCDEWindowManager::WindowEntry&&) */

WindowEntry * __thiscall
NCDEWindowManager::WindowEntry::operator=(WindowEntry *this,WindowEntry *param_1)

{
  *(undefined4 *)this = *(undefined4 *)param_1;
  *(undefined4 *)(this + 4) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 8) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(this + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(this + 0x14) = *(undefined4 *)(param_1 + 0x14);
  QString::operator=((QString *)(this + 0x18),(QString *)(param_1 + 0x18));
  QString::operator=((QString *)(this + 0x30),(QString *)(param_1 + 0x30));
  QString::operator=((QString *)(this + 0x48),(QString *)(param_1 + 0x48));
  this[0x60] = param_1[0x60];
  this[0x61] = param_1[0x61];
  this[0x62] = param_1[0x62];
  *(undefined4 *)(this + 100) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(this + 0x68) = *(undefined4 *)(param_1 + 0x68);
  return this;
}



// ==== 001fcdd6  NCDEWindowManager::start

/* NCDEWindowManager::start() */

undefined8 __thiscall NCDEWindowManager::start(NCDEWindowManager *this)

{
  undefined4 uVar1;
  QGuiApplication *this_00;
  undefined8 uVar2;
  void *__ptr;
  QAbstractNativeEventFilter *pQVar3;
  long in_FS_OFFSET;
  undefined4 local_98;
  undefined4 local_94;
  void *local_90;
  QX11Application *local_88;
  undefined8 local_80;
  undefined4 *local_78;
  void *local_70;
  long local_68;
  long local_60;
  long local_58;
  void *local_50;
  code *local_48;
  undefined8 uStack_40;
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  this_00 = (QGuiApplication *)QCoreApplication::instance();
  local_88 = QGuiApplication::
             nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
                       (this_00);
  if (local_88 != (QX11Application *)0x0) {
    uVar2 = (**(code **)(*(long *)local_88 + 0x18))(local_88);
    *(undefined8 *)(this + 0x20) = uVar2;
  }
  if (*(long *)(this + 0x20) == 0) {
    uVar2 = 0;
  }
  else {
    local_80 = xcb_get_setup(*(undefined8 *)(this + 0x20));
    local_78 = (undefined4 *)xcb_setup_roots_iterator(local_80);
    if (local_78 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      *(undefined4 *)(this + 0x28) = *local_78;
      *(uint *)(this + 0x30) = (uint)*(ushort *)(local_78 + 5);
      *(uint *)(this + 0x34) = (uint)*(ushort *)((long)local_78 + 0x16);
      local_98 = 0x780000;
      local_94 = xcb_change_window_attributes_checked
                           (*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28),0x800,
                            &local_98);
      local_70 = (void *)xcb_request_check(*(undefined8 *)(this + 0x20),local_94);
      if (local_70 == (void *)0x0) {
        internAtoms(this);
        scanExisting(this);
        local_68 = xcb_get_extension_data(*(undefined8 *)(this + 0x20),&xcb_randr_id);
        if ((local_68 != 0) && (*(char *)(local_68 + 8) != '\0')) {
          this[0x49] = (NCDEWindowManager)0x1;
          this[0x4a] = *(NCDEWindowManager *)(local_68 + 10);
          xcb_randr_select_input(*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28),1);
        }
        local_60 = xcb_get_extension_data(*(undefined8 *)(this + 0x20),&xcb_screensaver_id);
        if ((local_60 != 0) && (*(char *)(local_60 + 8) != '\0')) {
          this[0x4b] = (NCDEWindowManager)0x1;
          this[0x4c] = *(NCDEWindowManager *)(local_60 + 10);
          uVar1 = xcb_screensaver_query_version(*(undefined8 *)(this + 0x20),1,1);
          __ptr = (void *)xcb_screensaver_query_version_reply(*(undefined8 *)(this + 0x20),uVar1,0);
          free(__ptr);
          xcb_screensaver_select_input(*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28),1);
        }
        local_58 = xcb_get_extension_data(*(undefined8 *)(this + 0x20),&xcb_input_id);
        if ((local_58 != 0) && (*(char *)(local_58 + 8) != '\0')) {
          local_90 = (void *)0x0;
          uVar1 = xcb_input_xi_query_version(*(undefined8 *)(this + 0x20),2,0);
          local_50 = (void *)xcb_input_xi_query_version_reply
                                       (*(undefined8 *)(this + 0x20),uVar1,&local_90);
          if ((local_50 != (void *)0x0) && (local_90 == (void *)0x0)) {
            local_48 = (code *)0x2000000010001;
            xcb_input_xi_select_events
                      (*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28),1,&local_48);
            this[0x4d] = (NCDEWindowManager)0x1;
            this[0x4e] = *(NCDEWindowManager *)(local_58 + 9);
          }
          free(local_50);
          free(local_90);
        }
        watchPicomOwner(this);
        pQVar3 = (QAbstractNativeEventFilter *)QCoreApplication::instance();
        QCoreApplication::installNativeEventFilter(pQVar3);
        xcb_flush(*(undefined8 *)(this + 0x20));
        QTimer::setInterval((int)this + 0x58);
        local_48 = pollPointer;
        uStack_40 = 0;
        QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(NCDEWindowManager::*)()>
                  (&local_90,this + 0x58,QTimer::timeout,0,this,&local_48,0);
        QMetaObject::Connection::~Connection((Connection *)&local_90);
        if (this[0x4d] != (NCDEWindowManager)0x1) {
          QTimer::start();
        }
        pollPointer(this);
        QTimer::setInterval((int)this + 0x68);
        local_48 = pollUserIdle;
        uStack_40 = 0;
        QObject::connect<void(QTimer::*)(QTimer::QPrivateSignal),void(NCDEWindowManager::*)()>
                  (&local_90,this + 0x68,QTimer::timeout,0,this,&local_48,0);
        QMetaObject::Connection::~Connection((Connection *)&local_90);
        if (this[0x4b] != (NCDEWindowManager)0x0) {
          QTimer::start();
        }
        this[0x48] = (NCDEWindowManager)0x1;
        uVar2 = 1;
      }
      else {
        free(local_70);
        this[0x48] = (NCDEWindowManager)0x0;
        uVar2 = 0;
      }
    }
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 001fd39e  NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#1}::operator()

/* NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#1}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#1}::operator()(_lambda___1_ *this)

{
  bool bVar1;
  char cVar2;
  
  if ((*(char *)(*(long *)this + 0x48) == '\x01') && (*(char *)(*(long *)this + 0x4d) == '\0')) {
    if ((*(long *)(*(long *)this + 0x50) == 0) ||
       (cVar2 = AnimPolicy::screenIdle(*(AnimPolicy **)(*(long *)this + 0x50)), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      QTimer::stop();
    }
    else {
      cVar2 = QTimer::isActive();
      if (cVar2 != '\x01') {
        QTimer::start();
      }
    }
  }
  return;
}



// ==== 001fd45a  NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#2}::operator()

/* NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#2}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#2}::operator()(_lambda___2_ *this)

{
  recomputeDesktopObscured(*(NCDEWindowManager **)this);
  return;
}



// ==== 001fd478  NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#3}::operator()

/* NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#3}::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
NCDEWindowManager::setAnimPolicy(AnimPolicy*)::{lambda()#3}::operator()(_lambda___3_ *this)

{
  recomputeDesktopObscured(*(NCDEWindowManager **)this);
  return;
}



// ==== 001fd496  NCDEWindowManager::setAnimPolicy

/* NCDEWindowManager::setAnimPolicy(AnimPolicy*) */

void __thiscall NCDEWindowManager::setAnimPolicy(NCDEWindowManager *this,AnimPolicy *param_1)

{
  long in_FS_OFFSET;
  NCDEWindowManager *local_40;
  Connection local_38 [8];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  *(AnimPolicy **)(this + 0x50) = param_1;
  if (param_1 != (AnimPolicy *)0x0) {
    local_40 = this;
    QObject::
    connect<void(AnimPolicy::*)(),NCDEWindowManager::setAnimPolicy(AnimPolicy*)::_lambda()_1_>
              (local_38,param_1,AnimPolicy::policyChanged,0,this,&local_40,0);
    QMetaObject::Connection::~Connection(local_38);
    local_40 = this;
    QObject::
    connect<void(NCDEWindowManager::*)(),NCDEWindowManager::setAnimPolicy(AnimPolicy*)::_lambda()_2_>
              (local_38,this,windowStateChanged,0,this,&local_40,0);
    QMetaObject::Connection::~Connection(local_38);
    local_40 = this;
    QObject::
    connect<void(NCDEWindowManager::*)(),NCDEWindowManager::setAnimPolicy(AnimPolicy*)::_lambda()_3_>
              (local_38,this,countChanged,0,this,&local_40,0);
    QMetaObject::Connection::~Connection(local_38);
    recomputeDesktopObscured(this);
  }
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fd5f8  NCDEWindowManager::setScreensaverTimeoutMs

/* NCDEWindowManager::setScreensaverTimeoutMs(long long) */

void __thiscall NCDEWindowManager::setScreensaverTimeoutMs(NCDEWindowManager *this,longlong param_1)

{
  if (param_1 != *(long *)(this + 0x80)) {
    *(longlong *)(this + 0x80) = param_1;
    this[0x88] = (NCDEWindowManager)0x0;
  }
  return;
}



// ==== 001fd634  NCDEWindowManager::screensaverIdleActive

/* NCDEWindowManager::screensaverIdleActive() const */

NCDEWindowManager __thiscall NCDEWindowManager::screensaverIdleActive(NCDEWindowManager *this)

{
  return this[0x88];
}



// ==== 001fd64a  NCDEWindowManager::pollUserIdle

/* NCDEWindowManager::pollUserIdle() */

void __thiscall NCDEWindowManager::pollUserIdle(NCDEWindowManager *this)

{
  uint uVar1;
  NCDEWindowManager NVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  void *local_20;
  void *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((this[0x4b] == (NCDEWindowManager)0x1) && (*(long *)(this + 0x50) != 0)) {
    local_20 = (void *)0x0;
    uVar3 = xcb_screensaver_query_info(*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28));
    local_18 = (void *)xcb_screensaver_query_info_reply
                                 (*(undefined8 *)(this + 0x20),uVar3,&local_20);
    if (local_20 != (void *)0x0) {
      free(local_20);
    }
    if (local_18 != (void *)0x0) {
      uVar1 = *(uint *)((long)local_18 + 0x10);
      free(local_18);
      NVar2 = (NCDEWindowManager)(29999 < uVar1);
      if (NVar2 != this[0x78]) {
        this[0x78] = NVar2;
        AnimPolicy::onUserInputIdle(*(AnimPolicy **)(this + 0x50),(bool)NVar2);
      }
      if ((*(long *)(this + 0x80) < 1) || (uVar1 < (uint)*(undefined8 *)(this + 0x80))) {
        this[0x88] = (NCDEWindowManager)0x0;
      }
      else if (this[0x88] != (NCDEWindowManager)0x1) {
        this[0x88] = (NCDEWindowManager)0x1;
        screensaverIdleReached(this);
      }
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001fd7aa  NCDEWindowManager::recomputeDesktopObscured

/* NCDEWindowManager::recomputeDesktopObscured() */

void __thiscall NCDEWindowManager::recomputeDesktopObscured(NCDEWindowManager *this)

{
  char cVar1;
  long in_FS_OFFSET;
  bool local_31;
  undefined8 local_30;
  undefined8 local_28;
  QList<NCDEWindowManager::WindowEntry> *local_20;
  long local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x50) != 0) {
    local_31 = false;
    local_20 = (QList<NCDEWindowManager::WindowEntry> *)(this + 0x90);
    local_30 = QList<NCDEWindowManager::WindowEntry>::begin(local_20);
    local_28 = QList<NCDEWindowManager::WindowEntry>::end(local_20);
    while( true ) {
      cVar1 = QList<NCDEWindowManager::WindowEntry>::iterator::operator!=
                        ((iterator *)&local_30,local_28);
      if (cVar1 == '\0') break;
      local_18 = QList<NCDEWindowManager::WindowEntry>::iterator::operator*((iterator *)&local_30);
      if ((*(char *)(local_18 + 0x61) != '\0') && (*(char *)(local_18 + 0x60) != '\x01')) {
        local_31 = true;
        break;
      }
      QList<NCDEWindowManager::WindowEntry>::iterator::operator++((iterator *)&local_30);
    }
    AnimPolicy::setDesktopObscured(*(AnimPolicy **)(this + 0x50),local_31);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fd88e  NCDEWindowManager::internAtoms()::{lambda(char_const*)#1}::operator()

/* NCDEWindowManager::internAtoms()::{lambda(char const*)#1}::TEMPNAMEPLACEHOLDERVALUE(char const*)
   const */

undefined4 __thiscall
NCDEWindowManager::internAtoms()::{lambda(char_const*)#1}::operator()
          (_lambda_char_const___1_ *this,char *param_1)

{
  long lVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  void *__ptr;
  long in_FS_OFFSET;
  undefined4 local_1c;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = qstrlen(param_1);
  uVar3 = xcb_intern_atom(*(undefined8 *)(*(long *)this + 0x20),0,uVar2,param_1);
  __ptr = (void *)xcb_intern_atom_reply(*(undefined8 *)(*(long *)this + 0x20),uVar3,0);
  if (__ptr == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = *(undefined4 *)((long)__ptr + 8);
  }
  free(__ptr);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_1c;
}



// ==== 001fd93e  NCDEWindowManager::internAtoms

/* NCDEWindowManager::internAtoms() */

void __thiscall NCDEWindowManager::internAtoms(NCDEWindowManager *this)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  NCDEWindowManager *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = this;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"WM_PROTOCOLS");
  *(undefined4 *)(this + 0xe0) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"WM_DELETE_WINDOW");
  *(undefined4 *)(this + 0xe4) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_NAME");
  *(undefined4 *)(this + 0xe8) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_ACTIVE_WINDOW");
  *(undefined4 *)(this + 0xf0) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"UTF8_STRING");
  *(undefined4 *)(this + 0xec) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_SUPPORTED");
  *(undefined4 *)(this + 0xf4) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_STATE");
  *(undefined4 *)(this + 0xf8) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_PID");
  *(undefined4 *)(this + 0x108) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_STATE_MAXIMIZED_VERT");
  *(undefined4 *)(this + 0xfc) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_STATE_MAXIMIZED_HORZ");
  *(undefined4 *)(this + 0x100) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_CM_S0");
  *(undefined4 *)(this + 0x104) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE");
  *(undefined4 *)(this + 0x10c) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_NORMAL");
  *(undefined4 *)(this + 0x110) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_DESKTOP");
  *(undefined4 *)(this + 0x114) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_DOCK");
  *(undefined4 *)(this + 0x118) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_DIALOG");
  *(undefined4 *)(this + 0x11c) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_UTILITY");
  *(undefined4 *)(this + 0x120) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_TOOLBAR");
  *(undefined4 *)(this + 0x124) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_SPLASH");
  *(undefined4 *)(this + 0x128) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_POPUP_MENU");
  *(undefined4 *)(this + 300) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_TOOLTIP");
  *(undefined4 *)(this + 0x130) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_WINDOW_TYPE_NOTIFICATION");
  *(undefined4 *)(this + 0x134) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_NUMBER_OF_DESKTOPS");
  *(undefined4 *)(this + 0x138) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_CURRENT_DESKTOP");
  *(undefined4 *)(this + 0x13c) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NET_WM_DESKTOP");
  *(undefined4 *)(this + 0x140) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NCDE_MENUS");
  *(undefined4 *)(this + 0x144) = uVar1;
  uVar1 = internAtoms()::{lambda(char_const*)#1}::operator()
                    ((_lambda_char_const___1_ *)&local_18,"_NCDE_MENU_INVOKE");
  *(undefined4 *)(this + 0x148) = uVar1;
  setupEwmh(this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fdce4  NCDEWindowManager::setupEwmh

/* NCDEWindowManager::setupEwmh() */

void __thiscall NCDEWindowManager::setupEwmh(NCDEWindowManager *this)

{
  long in_FS_OFFSET;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  if ((*(long *)(this + 0x20) != 0) && (*(int *)(this + 0xf4) != 0)) {
    local_68 = *(undefined4 *)(this + 0xf4);
    local_64 = *(undefined4 *)(this + 0xf0);
    local_60 = *(undefined4 *)(this + 0xe8);
    local_5c = *(undefined4 *)(this + 0xf8);
    local_58 = *(undefined4 *)(this + 0xfc);
    local_54 = *(undefined4 *)(this + 0x100);
    local_50 = *(undefined4 *)(this + 0x10c);
    local_4c = *(undefined4 *)(this + 0x110);
    local_48 = *(undefined4 *)(this + 0x114);
    local_44 = *(undefined4 *)(this + 0x118);
    local_40 = *(undefined4 *)(this + 0x11c);
    local_3c = *(undefined4 *)(this + 0x120);
    local_38 = *(undefined4 *)(this + 0x124);
    local_34 = *(undefined4 *)(this + 0x128);
    local_30 = *(undefined4 *)(this + 300);
    local_2c = *(undefined4 *)(this + 0x130);
    local_28 = *(undefined4 *)(this + 0x134);
    local_24 = *(undefined4 *)(this + 0x138);
    local_20 = *(undefined4 *)(this + 0x13c);
    local_1c = *(undefined4 *)(this + 0x140);
    xcb_change_property(*(undefined8 *)(this + 0x20),0,*(undefined4 *)(this + 0x28),
                        *(undefined4 *)(this + 0xf4),4,0x20,0x14,&local_68);
    local_70 = 4;
    xcb_change_property(*(undefined8 *)(this + 0x20),0,*(undefined4 *)(this + 0x28),
                        *(undefined4 *)(this + 0x138),6,0x20,1,&local_70);
    local_6c = *(undefined4 *)(this + 0x150);
    xcb_change_property(*(undefined8 *)(this + 0x20),0,*(undefined4 *)(this + 0x28),
                        *(undefined4 *)(this + 0x13c),6,0x20,1,&local_6c);
    xcb_flush(*(undefined8 *)(this + 0x20));
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fdf1a  NCDEWindowManager::scanExisting

/* NCDEWindowManager::scanExisting() */

void __thiscall NCDEWindowManager::scanExisting(NCDEWindowManager *this)

{
  undefined4 uVar1;
  int iVar2;
  void *__ptr;
  long lVar3;
  void *__ptr_00;
  int local_24;
  
  uVar1 = xcb_query_tree(*(undefined8 *)(this + 0x20),*(undefined4 *)(this + 0x28));
  __ptr = (void *)xcb_query_tree_reply(*(undefined8 *)(this + 0x20),uVar1,0);
  if (__ptr != (void *)0x0) {
    lVar3 = xcb_query_tree_children(__ptr);
    local_24 = 0;
    while( true ) {
      iVar2 = xcb_query_tree_children_length(__ptr);
      if (iVar2 <= local_24) break;
      uVar1 = xcb_get_window_attributes
                        (*(undefined8 *)(this + 0x20),*(undefined4 *)(lVar3 + (long)local_24 * 4));
      __ptr_00 = (void *)xcb_get_window_attributes_reply(*(undefined8 *)(this + 0x20),uVar1,0);
      if (__ptr_00 != (void *)0x0) {
        if ((*(char *)((long)__ptr_00 + 0x1a) == '\x02') &&
           (*(char *)((long)__ptr_00 + 0x1b) == '\0')) {
          manage(this,*(uint *)(lVar3 + (long)local_24 * 4));
        }
        free(__ptr_00);
      }
      local_24 = local_24 + 1;
    }
    free(__ptr);
  }
  return;
}


