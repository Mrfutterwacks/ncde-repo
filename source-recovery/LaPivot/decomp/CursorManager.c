// Ghidra decompile of LaPivot.oracle — class/namespace CursorManager (32 functions). Raw; not source.

// ==== 0013a802  CursorManager::qt_static_metacall

/* CursorManager::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void CursorManager::qt_static_metacall(void)

{
  return;
}



// ==== 0013a820  CursorManager::metaObject

/* CursorManager::metaObject() const */

undefined1 * __thiscall CursorManager::metaObject(CursorManager *this)

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



// ==== 0013a868  CursorManager::qt_metacast

/* CursorManager::qt_metacast(char const*) */

CursorManager * __thiscall CursorManager::qt_metacast(CursorManager *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (CursorManager *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"CursorManager");
    if (iVar1 != 0) {
      this = (CursorManager *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0013a8bc  CursorManager::qt_metacall

/* CursorManager::qt_metacall(QMetaObject::Call, int, void**) */

undefined4 __thiscall
CursorManager::qt_metacall
          (CursorManager *this,undefined4 param_2,undefined4 param_3,undefined8 param_4)

{
  undefined4 uVar1;
  
  uVar1 = QObject::qt_metacall(this,param_2,param_3,param_4);
  return uVar1;
}



// ==== 001571d8  CursorManager::~CursorManager

/* CursorManager::~CursorManager() */

void __thiscall CursorManager::~CursorManager(CursorManager *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c428;
  QList<QWindow*>::~QList((QList<QWindow*> *)(this + 0x38));
  QString::~QString((QString *)(this + 0x20));
  QHash<Qt::CursorShape,QCursor>::~QHash((QHash<Qt::CursorShape,QCursor> *)(this + 0x10));
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 00157232  CursorManager::~CursorManager

/* CursorManager::~CursorManager() */

void __thiscall CursorManager::~CursorManager(CursorManager *this)

{
  ~CursorManager(this);
  operator_delete(this,0x50);
  return;
}



// ==== 00273cce  CursorManager::CursorManager

/* CursorManager::CursorManager(QObject*) */

void __thiscall CursorManager::CursorManager(CursorManager *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032c428;
  QHash<Qt::CursorShape,QCursor>::QHash((QHash<Qt::CursorShape,QCursor> *)(this + 0x10));
  this[0x18] = (CursorManager)0x0;
  QString::QString((QString *)(this + 0x20));
  QList<QWindow*>::QList((QList<QWindow*> *)(this + 0x38));
  return;
}



// ==== 0027a568  CursorManager::loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()

/* CursorManager::loadCursor(QString const&, int)::{lambda(QImage const&, double,
   double)#1}::TEMPNAMEPLACEHOLDERVALUE(QImage const&, double, double) const */

QImage * CursorManager::loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
         operator()(QImage *param_1,double param_2,double param_3)

{
  undefined8 in_RDX;
  int *in_RSI;
  long in_FS_OFFSET;
  undefined4 uStack_44;
  int iStack_40;
  int iStack_3c;
  QPixmap aQStack_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iStack_40 = qRound((double)*in_RSI * param_2 + 6.0);
  iStack_3c = qRound((double)*in_RSI * param_3 + 6.0);
  QFlags<Qt::ImageConversionFlag>::QFlags((QFlags<Qt::ImageConversionFlag> *)&uStack_44,0);
  QPixmap::fromImage(aQStack_38,in_RDX,uStack_44);
  QCursor::QCursor((QCursor *)param_1,aQStack_38,iStack_40,iStack_3c);
  QPixmap::~QPixmap(aQStack_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0027a69a  CursorManager::loadCursor

/* CursorManager::loadCursor(QString const&, int) */

QString * CursorManager::loadCursor(QString *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  bool in_CL;
  QString *in_RDX;
  undefined **ppuVar3;
  QString *pQVar4;
  undefined8 *puVar5;
  long lVar6;
  long in_FS_OFFSET;
  QImage aQStack_d8 [32];
  QString aQStack_b8 [48];
  QString aQStack_88 [24];
  QString aQStack_70 [24];
  QString aQStack_58 [24];
  long alStack_40 [2];
  
  alStack_40[0] = *(long *)(in_FS_OFFSET + 0x28);
  if (loadCursor(QString_const&,int)::kArrowNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kArrowNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_80_0;
      for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kArrowNames,aQStack_b8,4);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kArrowNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kArrowNames);
      pQVar4 = aQStack_58;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kPointerNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kPointerNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_84_1;
      for (lVar6 = 4; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kPointerNames,aQStack_b8,5);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kPointerNames,&__dso_handle
                  );
      __cxa_guard_release(&loadCursor(QString_const&,int)::kPointerNames);
      pQVar4 = (QString *)alStack_40;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kTextNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kTextNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_88_2;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kTextNames,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kTextNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kTextNames);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kWaitNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kWaitNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_92_3;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kWaitNames,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kWaitNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kWaitNames);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kHelpNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kHelpNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_96_4;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kHelpNames,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kHelpNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kHelpNames);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kMoveNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kMoveNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_100_5;
      for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kMoveNames,aQStack_b8,4);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kMoveNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kMoveNames);
      pQVar4 = aQStack_58;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kResizeVNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kResizeVNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_104_6;
      for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kResizeVNames,aQStack_b8,4);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kResizeVNames,&__dso_handle
                  );
      __cxa_guard_release(&loadCursor(QString_const&,int)::kResizeVNames);
      pQVar4 = aQStack_58;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kResizeHNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kResizeHNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      puVar5 = &C_108_7;
      for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,(char *)*puVar5);
        pQVar4 = pQVar4 + 0x18;
        puVar5 = puVar5 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kResizeHNames,aQStack_b8,4);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kResizeHNames,&__dso_handle
                  );
      __cxa_guard_release(&loadCursor(QString_const&,int)::kResizeHNames);
      pQVar4 = aQStack_58;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kResizeD1Names == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kResizeD1Names);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_112_8;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kResizeD1Names,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kResizeD1Names,
                   &__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kResizeD1Names);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kResizeD2Names == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kResizeD2Names);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_116_9;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kResizeD2Names,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kResizeD2Names,
                   &__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kResizeD2Names);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kCrosshairNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kCrosshairNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_120_10;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kCrosshairNames,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kCrosshairNames,
                   &__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kCrosshairNames);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kNotAllowedNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kNotAllowedNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_124_11;
      for (lVar6 = 3; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kNotAllowedNames,aQStack_b8,4);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kNotAllowedNames,
                   &__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kNotAllowedNames);
      pQVar4 = aQStack_58;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kGrabNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kGrabNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_128_12;
      for (lVar6 = 1; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kGrabNames,aQStack_b8,2);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kGrabNames,&__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kGrabNames);
      pQVar4 = aQStack_88;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  if (loadCursor(QString_const&,int)::kGrabbingNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadCursor(QString_const&,int)::kGrabbingNames);
    if (iVar2 != 0) {
      pQVar4 = aQStack_b8;
      ppuVar3 = &C_132_13;
      for (lVar6 = 2; -1 < lVar6; lVar6 = lVar6 + -1) {
        QString::QString(pQVar4,*ppuVar3);
        pQVar4 = pQVar4 + 0x18;
        ppuVar3 = ppuVar3 + 1;
      }
      QSet<QString>::QSet(&loadCursor(QString_const&,int)::kGrabbingNames,aQStack_b8,3);
      __cxa_atexit(QSet<QString>::~QSet,&loadCursor(QString_const&,int)::kGrabbingNames,
                   &__dso_handle);
      __cxa_guard_release(&loadCursor(QString_const&,int)::kGrabbingNames);
      pQVar4 = aQStack_70;
      while (pQVar4 != aQStack_b8) {
        pQVar4 = pQVar4 + -0x18;
        QString::~QString(pQVar4);
      }
    }
  }
  cVar1 = QSet<QString>::contains
                    ((QSet<QString> *)&loadCursor(QString_const&,int)::kArrowNames,in_RDX);
  if (cVar1 == '\0') {
    cVar1 = QSet<QString>::contains
                      ((QSet<QString> *)&loadCursor(QString_const&,int)::kPointerNames,in_RDX);
    if (cVar1 == '\0') {
      cVar1 = QSet<QString>::contains
                        ((QSet<QString> *)&loadCursor(QString_const&,int)::kTextNames,in_RDX);
      if (cVar1 == '\0') {
        cVar1 = QSet<QString>::contains
                          ((QSet<QString> *)&loadCursor(QString_const&,int)::kWaitNames,in_RDX);
        if (cVar1 == '\0') {
          cVar1 = QSet<QString>::contains
                            ((QSet<QString> *)&loadCursor(QString_const&,int)::kHelpNames,in_RDX);
          if (cVar1 == '\0') {
            cVar1 = QSet<QString>::contains
                              ((QSet<QString> *)&loadCursor(QString_const&,int)::kMoveNames,in_RDX);
            if (cVar1 == '\0') {
              cVar1 = QSet<QString>::contains
                                ((QSet<QString> *)&loadCursor(QString_const&,int)::kResizeVNames,
                                 in_RDX);
              if (cVar1 == '\0') {
                cVar1 = QSet<QString>::contains
                                  ((QSet<QString> *)&loadCursor(QString_const&,int)::kResizeHNames,
                                   in_RDX);
                if (cVar1 == '\0') {
                  cVar1 = QSet<QString>::contains
                                    ((QSet<QString> *)
                                     &loadCursor(QString_const&,int)::kResizeD1Names,in_RDX);
                  if (cVar1 == '\0') {
                    cVar1 = QSet<QString>::contains
                                      ((QSet<QString> *)
                                       &loadCursor(QString_const&,int)::kResizeD2Names,in_RDX);
                    if (cVar1 == '\0') {
                      cVar1 = QSet<QString>::contains
                                        ((QSet<QString> *)
                                         &loadCursor(QString_const&,int)::kCrosshairNames,in_RDX);
                      if (cVar1 == '\0') {
                        cVar1 = QSet<QString>::contains
                                          ((QSet<QString> *)
                                           &loadCursor(QString_const&,int)::kNotAllowedNames,in_RDX)
                        ;
                        if (cVar1 == '\0') {
                          cVar1 = QSet<QString>::contains
                                            ((QSet<QString> *)
                                             &loadCursor(QString_const&,int)::kGrabNames,in_RDX);
                          if (cVar1 == '\0') {
                            cVar1 = QSet<QString>::contains
                                              ((QSet<QString> *)
                                               &loadCursor(QString_const&,int)::kGrabbingNames,
                                               in_RDX);
                            if (cVar1 == '\0') {
                              QCursor::QCursor((QCursor *)param_1,0);
                            }
                            else {
                              renderKithHand((int)aQStack_d8,in_CL);
                              loadCursor(QString_const&,int)::
                              {lambda(QImage_const&,double,double)#1}::operator()
                                        ((QImage *)param_1,0.5,0.5);
                              QImage::~QImage(aQStack_d8);
                            }
                          }
                          else {
                            renderKithHand((int)aQStack_d8,in_CL);
                            loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}
                            ::operator()((QImage *)param_1,0.5,0.5);
                            QImage::~QImage(aQStack_d8);
                          }
                        }
                        else {
                          renderKithNotAllowed((int)aQStack_d8);
                          loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
                          operator()((QImage *)param_1,0.5,0.5);
                          QImage::~QImage(aQStack_d8);
                        }
                      }
                      else {
                        renderKithCrosshair((int)aQStack_d8);
                        loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
                        operator()((QImage *)param_1,0.5,0.5);
                        QImage::~QImage(aQStack_d8);
                      }
                    }
                    else {
                      renderKithResize((int)aQStack_d8,0.7853981633974483);
                      loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
                      operator()((QImage *)param_1,0.5,0.5);
                      QImage::~QImage(aQStack_d8);
                    }
                  }
                  else {
                    renderKithResize((int)aQStack_d8,-0.7853981633974483);
                    loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
                    operator()((QImage *)param_1,0.5,0.5);
                    QImage::~QImage(aQStack_d8);
                  }
                }
                else {
                  renderKithResize((int)aQStack_d8,1.5707963267948966);
                  loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::
                  operator()((QImage *)param_1,0.5,0.5);
                  QImage::~QImage(aQStack_d8);
                }
              }
              else {
                renderKithResize((int)aQStack_d8,0.0);
                loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                          ((QImage *)param_1,0.5,0.5);
                QImage::~QImage(aQStack_d8);
              }
            }
            else {
              renderKithMove((int)aQStack_d8);
              loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                        ((QImage *)param_1,0.5,0.5);
              QImage::~QImage(aQStack_d8);
            }
          }
          else {
            renderKithHelp((int)aQStack_d8);
            loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                      ((QImage *)param_1,0.16,0.06);
            QImage::~QImage(aQStack_d8);
          }
        }
        else {
          renderKithWait((int)aQStack_d8);
          loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                    ((QImage *)param_1,0.5,0.5);
          QImage::~QImage(aQStack_d8);
        }
      }
      else {
        renderKithText((int)aQStack_d8);
        loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                  ((QImage *)param_1,0.5,0.5);
        QImage::~QImage(aQStack_d8);
      }
    }
    else {
      renderKithPointer((int)aQStack_d8);
      loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
                ((QImage *)param_1,0.4,0.06);
      QImage::~QImage(aQStack_d8);
    }
  }
  else {
    renderKithArrow((int)aQStack_d8);
    loadCursor(QString_const&,int)::{lambda(QImage_const&,double,double)#1}::operator()
              ((QImage *)param_1,0.16,0.06);
    QImage::~QImage(aQStack_d8);
  }
  if (alStack_40[0] != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0027c7a8  CursorManager::loadAll

/* CursorManager::loadAll(int) */

void CursorManager::loadAll(int param_1)

{
  char cVar1;
  int iVar2;
  CursorShape *pCVar3;
  pair<Qt::CursorShape,QString> *this;
  undefined4 in_register_0000003c;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  undefined4 local_69c;
  undefined4 local_698;
  undefined4 local_694;
  undefined4 local_690;
  undefined4 local_68c;
  undefined4 local_688;
  undefined4 local_684;
  undefined4 local_680;
  undefined4 uStack_67c;
  undefined4 uStack_678;
  undefined4 uStack_674;
  undefined4 uStack_670;
  undefined4 uStack_66c;
  undefined4 uStack_668;
  undefined4 uStack_664;
  wchar16 *pwStack_660;
  wchar16 *pwStack_658;
  wchar16 *pwStack_650;
  wchar16 *pwStack_648;
  undefined *puStack_640;
  wchar16 *pwStack_638;
  wchar16 *pwStack_630;
  wchar16 *local_628;
  wchar16 *local_620;
  wchar16 *local_618;
  wchar16 *local_610;
  wchar16 *local_608;
  wchar16 *local_600;
  wchar16 *local_5f8;
  wchar16 *local_5f0;
  QArrayDataPointer<char16_t> local_5e8 [32];
  QString local_5c8 [32];
  QArrayDataPointer<char16_t> local_5a8 [32];
  QString local_588 [32];
  QArrayDataPointer<char16_t> local_568 [32];
  QString local_548 [32];
  QArrayDataPointer<char16_t> local_528 [32];
  QString local_508 [32];
  QArrayDataPointer<char16_t> local_4e8 [32];
  QString local_4c8 [32];
  QArrayDataPointer<char16_t> local_4a8 [32];
  QString local_488 [32];
  QArrayDataPointer<char16_t> local_468 [32];
  QString local_448 [32];
  QArrayDataPointer<char16_t> local_428 [32];
  QString local_408 [32];
  QArrayDataPointer<char16_t> aQStack_3e8 [32];
  QString aQStack_3c8 [32];
  QArrayDataPointer<char16_t> aQStack_3a8 [32];
  QString aQStack_388 [32];
  QArrayDataPointer<char16_t> aQStack_368 [32];
  QString aQStack_348 [32];
  QArrayDataPointer<char16_t> aQStack_328 [32];
  QString aQStack_308 [32];
  QArrayDataPointer<char16_t> aQStack_2e8 [32];
  QString aQStack_2c8 [32];
  QArrayDataPointer<char16_t> aQStack_2a8 [32];
  QString aQStack_288 [32];
  QArrayDataPointer<char16_t> local_268 [32];
  undefined1 local_248 [2] [16];
  pair<Qt::CursorShape,QString> local_228 [32];
  pair<Qt::CursorShape,QString> apStack_208 [32];
  pair<Qt::CursorShape,QString> apStack_1e8 [32];
  pair<Qt::CursorShape,QString> apStack_1c8 [32];
  pair<Qt::CursorShape,QString> apStack_1a8 [32];
  pair<Qt::CursorShape,QString> apStack_188 [32];
  pair<Qt::CursorShape,QString> apStack_168 [32];
  pair<Qt::CursorShape,QString> apStack_148 [32];
  pair<Qt::CursorShape,QString> apStack_128 [32];
  pair<Qt::CursorShape,QString> apStack_108 [32];
  pair<Qt::CursorShape,QString> apStack_e8 [32];
  pair<Qt::CursorShape,QString> apStack_c8 [32];
  pair<Qt::CursorShape,QString> apStack_a8 [32];
  pair<Qt::CursorShape,QString> apStack_88 [32];
  pair<Qt::CursorShape,QString> apStack_68 [32];
  pair<Qt::CursorShape,QString> apStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (loadAll(int)::kNames == '\0') {
    iVar2 = __cxa_guard_acquire(&loadAll(int)::kNames);
    if (iVar2 != 0) {
      local_69c = 0;
      local_5f0 = L"left_ptr";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_5e8,(QTypedArrayData *)0x0,L"left_ptr",8)
      ;
      QString::QString(local_5c8,(QArrayDataPointer *)local_5e8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (local_228,(CursorShape *)&local_69c,local_5c8);
      local_698 = 4;
      local_5f8 = L"xterm";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_5a8,(QTypedArrayData *)0x0,L"xterm",5);
      QString::QString(local_588,(QArrayDataPointer *)local_5a8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_208,(CursorShape *)&local_698,local_588);
      local_694 = 0xd;
      local_600 = L"hand2";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_568,(QTypedArrayData *)0x0,L"hand2",5);
      QString::QString(local_548,(QArrayDataPointer *)local_568);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_1e8,(CursorShape *)&local_694,local_548);
      local_690 = 3;
      local_608 = L"watch";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_528,(QTypedArrayData *)0x0,L"watch",5);
      QString::QString(local_508,(QArrayDataPointer *)local_528);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_1c8,(CursorShape *)&local_690,local_508);
      local_68c = 0x10;
      local_610 = L"watch";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_4e8,(QTypedArrayData *)0x0,L"watch",5);
      QString::QString(local_4c8,(QArrayDataPointer *)local_4e8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_1a8,(CursorShape *)&local_68c,local_4c8);
      local_688 = 9;
      local_618 = L"fleur";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_4a8,(QTypedArrayData *)0x0,L"fleur",5);
      QString::QString(local_488,(QArrayDataPointer *)local_4a8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_188,(CursorShape *)&local_688,local_488);
      local_684 = 6;
      local_620 = L"sb_h_double_arrow";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_468,(QTypedArrayData *)0x0,L"sb_h_double_arrow",0x11);
      QString::QString(local_448,(QArrayDataPointer *)local_468);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_168,(CursorShape *)&local_684,local_448);
      local_680 = 5;
      local_628 = L"sb_v_double_arrow";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_428,(QTypedArrayData *)0x0,L"sb_v_double_arrow",0x11);
      QString::QString(local_408,(QArrayDataPointer *)local_428);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_148,(CursorShape *)&local_680,local_408);
      uStack_67c = 7;
      pwStack_630 = L"nesw-resize";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_3e8,(QTypedArrayData *)0x0,L"nesw-resize",0xb);
      QString::QString(aQStack_3c8,(QArrayDataPointer *)aQStack_3e8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_128,(CursorShape *)&uStack_67c,aQStack_3c8);
      uStack_678 = 8;
      pwStack_638 = L"nwse-resize";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_3a8,(QTypedArrayData *)0x0,L"nwse-resize",0xb);
      QString::QString(aQStack_388,(QArrayDataPointer *)aQStack_3a8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_108,(CursorShape *)&uStack_678,aQStack_388);
      uStack_674 = 2;
      puStack_640 = &UNK_002af08c;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_368,(QTypedArrayData *)0x0,L"crosshair",9);
      QString::QString(aQStack_348,(QArrayDataPointer *)aQStack_368);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_e8,(CursorShape *)&uStack_674,aQStack_348);
      uStack_670 = 0xe;
      pwStack_648 = L"not-allowed";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (aQStack_328,(QTypedArrayData *)0x0,L"not-allowed",0xb);
      QString::QString(aQStack_308,(QArrayDataPointer *)aQStack_328);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_c8,(CursorShape *)&uStack_670,aQStack_308);
      uStack_66c = 0xf;
      pwStack_650 = L"help";
      QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_2e8,(QTypedArrayData *)0x0,L"help",4);
      QString::QString(aQStack_2c8,(QArrayDataPointer *)aQStack_2e8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_a8,(CursorShape *)&uStack_66c,aQStack_2c8);
      uStack_668 = 0x11;
      pwStack_658 = L"grab";
      QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_2a8,(QTypedArrayData *)0x0,L"grab",4);
      QString::QString(aQStack_288,(QArrayDataPointer *)aQStack_2a8);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_88,(CursorShape *)&uStack_668,aQStack_288);
      uStack_664 = 0x12;
      pwStack_660 = L"grabbing";
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_268,(QTypedArrayData *)0x0,L"grabbing",8)
      ;
      QString::QString((QString *)local_248,(QArrayDataPointer *)local_268);
      std::pair<Qt::CursorShape,QString>::pair<Qt::CursorShape,QString,true>
                (apStack_68,(CursorShape *)&uStack_664,(QString *)local_248);
      QHash<Qt::CursorShape,QString>::QHash(&loadAll(int)::kNames,local_228,0xf);
      __cxa_atexit(QHash<Qt::CursorShape,QString>::~QHash,&loadAll(int)::kNames,&__dso_handle);
      __cxa_guard_release(&loadAll(int)::kNames);
      this = apStack_48;
      while (this != local_228) {
        this = this + -0x20;
        std::pair<Qt::CursorShape,QString>::~pair(this);
      }
      QString::~QString((QString *)local_248);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_268);
      QString::~QString(aQStack_288);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_2a8);
      QString::~QString(aQStack_2c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_2e8);
      QString::~QString(aQStack_308);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_328);
      QString::~QString(aQStack_348);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_368);
      QString::~QString(aQStack_388);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_3a8);
      QString::~QString(aQStack_3c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_3e8);
      QString::~QString(local_408);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_428);
      QString::~QString(local_448);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_468);
      QString::~QString(local_488);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_4a8);
      QString::~QString(local_4c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_4e8);
      QString::~QString(local_508);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_528);
      QString::~QString(local_548);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_568);
      QString::~QString(local_588);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_5a8);
      QString::~QString(local_5c8);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_5e8);
    }
  }
  QHash<Qt::CursorShape,QCursor>::clear
            ((QHash<Qt::CursorShape,QCursor> *)(CONCAT44(in_register_0000003c,param_1) + 0x10));
  local_268._0_16_ =
       QHash<Qt::CursorShape,QString>::cbegin
                 ((QHash<Qt::CursorShape,QString> *)&loadAll(int)::kNames);
  while( true ) {
    auVar4 = QHash<Qt::CursorShape,QString>::cend();
    local_248[0] = auVar4;
    cVar1 = QHash<Qt::CursorShape,QString>::const_iterator::operator!=
                      ((const_iterator *)local_268,(const_iterator *)local_248);
    if (cVar1 == '\0') break;
    QHash<Qt::CursorShape,QString>::const_iterator::value((const_iterator *)local_268);
    loadCursor((QString *)local_248,param_1);
    pCVar3 = (CursorShape *)
             QHash<Qt::CursorShape,QString>::const_iterator::key((const_iterator *)local_268);
    QHash<Qt::CursorShape,QCursor>::insert
              ((QHash<Qt::CursorShape,QCursor> *)(CONCAT44(in_register_0000003c,param_1) + 0x10),
               pCVar3,(QCursor *)local_248);
    QCursor::~QCursor((QCursor *)local_248);
    QHash<Qt::CursorShape,QString>::const_iterator::operator++((const_iterator *)local_268);
  }
  if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0027d4b8  CursorManager::setTheme

/* CursorManager::setTheme(QString const&, int) */

void CursorManager::setTheme(QString *param_1,int param_2)

{
  QCursor *pQVar1;
  char cVar2;
  undefined8 *puVar3;
  undefined4 in_register_00000034;
  long in_FS_OFFSET;
  undefined8 local_48;
  undefined8 local_40;
  CursorShape local_38 [8];
  QList<QWindow*> *local_30;
  QCursor *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::operator=(param_1 + 0x20,(QString *)CONCAT44(in_register_00000034,param_2));
  loadAll((int)param_1);
  param_1[0x18] = (QString)0x1;
  local_30 = (QList<QWindow*> *)std::as_const<QList<QWindow*>>((QList *)(param_1 + 0x38));
  local_48 = QList<QWindow*>::begin(local_30);
  local_40 = QList<QWindow*>::end(local_30);
  while( true ) {
    cVar2 = QList<QWindow*>::const_iterator::operator!=((const_iterator *)&local_48,local_40);
    if (cVar2 == '\0') break;
    puVar3 = (undefined8 *)QList<QWindow*>::const_iterator::operator*((const_iterator *)&local_48);
    pQVar1 = (QCursor *)*puVar3;
    local_28 = pQVar1;
    if (pQVar1 != (QCursor *)0x0) {
      QHash<Qt::CursorShape,QCursor>::value(local_38);
      QWindow::setCursor(pQVar1);
      QCursor::~QCursor((QCursor *)local_38);
    }
    QList<QWindow*>::const_iterator::operator++((const_iterator *)&local_48);
  }
  param_1[0x18] = (QString)0x0;
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0027d612  CursorManager::reload

/* CursorManager::reload(int) */

void CursorManager::reload(int param_1)

{
  loadAll(param_1);
  return;
}



// ==== 0027d636  CursorManager::install

/* CursorManager::install(QWindow*) */

void __thiscall CursorManager::install(CursorManager *this,QWindow *param_1)

{
  QWindow *pQVar1;
  bool bVar2;
  char cVar3;
  long in_FS_OFFSET;
  QWindow *local_48;
  CursorManager *local_40;
  undefined4 local_2c;
  CursorShape local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = param_1;
  local_40 = this;
  if (param_1 != (QWindow *)0x0) {
    bVar2 = QListSpecialMethodsBase<QWindow*>::contains<QWindow*>
                      ((QListSpecialMethodsBase<QWindow*> *)(this + 0x38),&local_48);
    if (!bVar2) {
      bVar2 = false;
      goto LAB_0027d686;
    }
  }
  bVar2 = true;
LAB_0027d686:
  if (!bVar2) {
    QList<QWindow*>::append((QList<QWindow*> *)(local_40 + 0x38),local_48);
    QObject::installEventFilter((QObject *)local_48);
    cVar3 = QHash<Qt::CursorShape,QCursor>::isEmpty
                      ((QHash<Qt::CursorShape,QCursor> *)(local_40 + 0x10));
    pQVar1 = local_48;
    if (cVar3 != '\x01') {
      local_2c = 0;
      QHash<Qt::CursorShape,QCursor>::value(local_28);
      QWindow::setCursor((QCursor *)pQVar1);
      QCursor::~QCursor((QCursor *)local_28);
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0027d75e  CursorManager::eventFilter

/* CursorManager::eventFilter(QObject*, QEvent*) */

void __thiscall CursorManager::eventFilter(CursorManager *this,QObject *param_1,QEvent *param_2)

{
  bool bVar1;
  QWindow *pQVar2;
  char cVar3;
  int iVar4;
  long in_FS_OFFSET;
  QCursor local_30 [8];
  QWindow *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (this[0x18] != (CursorManager)0x0) {
    QObject::eventFilter((QObject *)this,(QEvent *)param_1);
    goto LAB_0027d8a4;
  }
  iVar4 = QEvent::type(param_2);
  if (iVar4 == 0xb7) {
    local_28 = qobject_cast<QWindow*>(param_1);
    if (local_28 != (QWindow *)0x0) {
      QWindow::cursor();
      iVar4 = QCursor::shape();
      QCursor::~QCursor(local_30);
      if (iVar4 == 0x18) {
LAB_0027d839:
        bVar1 = false;
      }
      else {
        cVar3 = QHash<Qt::CursorShape,QCursor>::contains((CursorShape *)(this + 0x10));
        if (cVar3 == '\0') goto LAB_0027d839;
        bVar1 = true;
      }
      pQVar2 = local_28;
      if (bVar1) {
        this[0x18] = (CursorManager)0x1;
        QHash<Qt::CursorShape,QCursor>::value((CursorShape *)local_30);
        QWindow::setCursor((QCursor *)pQVar2);
        QCursor::~QCursor(local_30);
        this[0x18] = (CursorManager)0x0;
      }
    }
  }
  QObject::eventFilter((QObject *)this,(QEvent *)param_1);
LAB_0027d8a4:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0027d91c  CursorManager::installAsRootCursor

/* CursorManager::installAsRootCursor(xcb_connection_t*, unsigned int, int) */

void __thiscall
CursorManager::installAsRootCursor
          (CursorManager *this,xcb_connection_t *param_1,uint param_2,int param_3)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  long lVar6;
  void *__src;
  size_t __n;
  long in_FS_OFFSET;
  undefined4 uStack_a0;
  int iStack_9c;
  undefined4 uStack_98;
  int iStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined8 uStack_80;
  long local_78;
  undefined4 *puStack_70;
  QImage aQStack_68 [32];
  undefined8 local_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_1 == (xcb_connection_t *)0x0) {
    QMessageLogger::QMessageLogger((QMessageLogger *)&local_48,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning
              ((char *)&local_48,"CursorManager::installAsRootCursor: no xcb connection");
  }
  else {
    local_78 = xcb_render_util_query_formats(param_1);
    if (local_78 == 0) {
      QMessageLogger::QMessageLogger((QMessageLogger *)&local_48,(char *)0x0,0,(char *)0x0);
      QMessageLogger::warning
                ((char *)&local_48,
                 "CursorManager::installAsRootCursor: xcb-render not available on this display; windows will keep showing the X11 default cursor"
                );
    }
    else {
      puStack_70 = (undefined4 *)xcb_render_util_find_standard_format(local_78,0);
      if (puStack_70 == (undefined4 *)0x0) {
        QMessageLogger::QMessageLogger((QMessageLogger *)&local_48,(char *)0x0,0,(char *)0x0);
        QMessageLogger::warning
                  ((char *)&local_48,
                   "CursorManager::installAsRootCursor: no ARGB32 PictFormat advertised; windows will keep showing the X11 default cursor"
                  );
      }
      else {
                    /* catch() { ... } // from try @ 0027da29 with catch @ 0027da44 */
        uStack_98 = 6;
                    /* try { // try from 0027da5d to 0037da61 has its CatchHandler @ 0027d9ec */
        renderKithArrow((int)&local_48);
        QFlags<Qt::ImageConversionFlag>::QFlags((QFlags<Qt::ImageConversionFlag> *)&uStack_a0,0);
        QImage::convertToFormat(aQStack_68,&local_48,6,uStack_a0);
        QImage::~QImage((QImage *)&local_48);
        sVar1 = qRound((double)param_3 * 0.16);
        sVar2 = qRound((double)param_3 * 0.06);
        iStack_94 = QImage::width();
        iStack_94 = iStack_94 << 2;
        local_48 = 0;
        uStack_40 = 0;
        uStack_38 = 0;
        lVar6 = QImage::bytesPerLine();
        if (lVar6 == iStack_94) {
          uStack_80 = QImage::constBits();
        }
        else {
          QImage::height();
          QByteArray::resize((longlong)&local_48);
          iStack_9c = 0;
          while( true ) {
            iVar5 = QImage::height();
            if (iVar5 <= iStack_9c) break;
            __n = (size_t)iStack_94;
            __src = (void *)QImage::constScanLine((int)aQStack_68);
            lVar6 = QByteArray::data((QByteArray *)&local_48);
            memcpy((void *)(lVar6 + iStack_9c * iStack_94),__src,__n);
            iStack_9c = iStack_9c + 1;
          }
                    /* catch() { ... } // from try @ 0027de5a with catch @ 0027dc0c */
          uStack_80 = QByteArray::constData((QByteArray *)&local_48);
        }
        uStack_90 = xcb_generate_id(param_1);
        uVar3 = QImage::height();
                    /* try { // try from 0027dc3e to 0037dc42 has its CatchHandler @ 0027dc0c */
        uVar4 = QImage::width();
        xcb_create_pixmap(param_1,0x20,uStack_90,param_2,uVar4,uVar3);
        uStack_8c = xcb_generate_id(param_1);
        xcb_create_gc(param_1,uStack_8c,uStack_90,0,0);
        iVar5 = QImage::height();
                    /* try { // try from 0027dcb4 to 0037dcb8 has its CatchHandler @ 0027de21 */
        iVar5 = iVar5 * iStack_94;
                    /* try { // try from 0027dcc1 to 0037de09 has its CatchHandler @ 0027de0c */
        uVar3 = QImage::height();
        uVar4 = QImage::width();
        xcb_put_image(param_1,2,uStack_90,uStack_8c,uVar4,uVar3,0,0,0,0x20,iVar5,uStack_80);
        xcb_free_gc(param_1,uStack_8c);
        uStack_88 = xcb_generate_id(param_1);
        xcb_render_create_picture(param_1,uStack_88,uStack_90,*puStack_70,0,0);
        xcb_free_pixmap(param_1,uStack_90);
        uStack_84 = xcb_generate_id(param_1);
        xcb_render_create_cursor(param_1,uStack_84,uStack_88,sVar1 + 6,sVar2 + 6);
        xcb_render_free_picture(param_1,uStack_88);
        uStack_a0 = uStack_84;
        xcb_change_window_attributes(param_1,param_2,0x4000,&uStack_a0);
        xcb_flush(param_1);
                    /* catch() { ... } // from try @ 0027dcc1 with catch @ 0027de0c */
        QByteArray::~QByteArray((QByteArray *)&local_48);
        QImage::~QImage(aQStack_68);
      }
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
                    /* catch() { ... } // from try @ 0027e054 with catch @ 0027dea4 */
  return;
}



// ==== 0027e772  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#1}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#1}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__1_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#1}::operator()
          (_lambda_int__1_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithArrow((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e7c0  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#2}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#2}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__2_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#2}::operator()
          (_lambda_int__2_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithPointer((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e80e  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#3}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#3}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__3_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#3}::operator()
          (_lambda_int__3_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithText((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e85c  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#4}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#4}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__4_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#4}::operator()
          (_lambda_int__4_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithWait((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e8aa  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#5}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#5}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__5_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#5}::operator()
          (_lambda_int__5_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithHelp((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e8f8  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#6}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#6}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__6_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#6}::operator()
          (_lambda_int__6_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithMove((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e946  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#7}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#7}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__7_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#7}::operator()
          (_lambda_int__7_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithResize((int)this,0.0);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e9a0  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#8}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#8}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__8_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#8}::operator()
          (_lambda_int__8_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithResize((int)this,1.5707963267948966);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027e9fa  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#9}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#9}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__9_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#9}::operator()
          (_lambda_int__9_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithResize((int)this,-0.7853981633974483);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027ea54  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#10}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#10}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__10_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#10}::operator()
          (_lambda_int__10_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithResize((int)this,0.7853981633974483);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027eaae  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#11}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#11}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__11_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#11}::operator()
          (_lambda_int__11_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithCrosshair((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027eafc  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#12}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#12}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__12_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#12}::operator()
          (_lambda_int__12_ *this,int param_1)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithNotAllowed((int)this);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027eb4a  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#13}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#13}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__13_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#13}::operator()
          (_lambda_int__13_ *this,int param_1)

{
  long lVar1;
  bool in_DL;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithHand((int)this,in_DL);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027eb9c  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#14}::operator()

/* CursorManager::writeXcursorTheme(QString const&, QList<int>
   const&)::{lambda(int)#14}::TEMPNAMEPLACEHOLDERVALUE(int) const */

_lambda_int__14_ * __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::{lambda(int)#14}::operator()
          (_lambda_int__14_ *this,int param_1)

{
  long lVar1;
  bool in_DL;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  renderKithHand((int)this,in_DL);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 0027ebee  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry::~Entry

/* ~Entry() */

void __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry::~Entry(Entry *this)

{
  QList<QString>::~QList((QList<QString> *)(this + 0x38));
  std::function<QImage(int)>::~function((function<QImage(int)> *)(this + 0x18));
  return;
}



// ==== 0027ec3a  CursorManager::writeXcursorTheme

/* WARNING: Removing unreachable block (ram,0x00281488) */
/* WARNING: Removing unreachable block (ram,0x0028132d) */
/* WARNING: Removing unreachable block (ram,0x00281220) */
/* WARNING: Removing unreachable block (ram,0x00281152) */
/* WARNING: Removing unreachable block (ram,0x00280fbb) */
/* WARNING: Removing unreachable block (ram,0x00280e6f) */
/* WARNING: Removing unreachable block (ram,0x00280da1) */
/* WARNING: Removing unreachable block (ram,0x00280d58) */
/* WARNING: Removing unreachable block (ram,0x00280e17) */
/* WARNING: Removing unreachable block (ram,0x00280f15) */
/* WARNING: Removing unreachable block (ram,0x0028107f) */
/* WARNING: Removing unreachable block (ram,0x002811b9) */
/* WARNING: Removing unreachable block (ram,0x002812b7) */
/* WARNING: Removing unreachable block (ram,0x002813c4) */
/* CursorManager::writeXcursorTheme(QString const&, QList<int> const&) */

undefined1 __thiscall
CursorManager::writeXcursorTheme(CursorManager *this,QString *param_1,QList *param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  QDebug *pQVar4;
  long lVar5;
  long lVar6;
  undefined1 uVar7;
  Entry *this_00;
  QString *pQVar8;
  pair<QString,QByteArray> *this_01;
  long in_FS_OFFSET;
  _lambda_int__1_ local_17bf;
  _lambda_int__2_ local_17be;
  _lambda_int__3_ _Stack_17bd;
  _lambda_int__4_ _Stack_17bc;
  _lambda_int__5_ _Stack_17bb;
  _lambda_int__6_ _Stack_17ba;
  _lambda_int__7_ _Stack_17b9;
  _lambda_int__8_ _Stack_17b8;
  _lambda_int__9_ _Stack_17b7;
  _lambda_int__10_ _Stack_17b6;
  _lambda_int__11_ _Stack_17b5;
  _lambda_int__12_ _Stack_17b4;
  _lambda_int__13_ _Stack_17b3;
  _lambda_int__14_ _Stack_17b2;
  undefined1 uStack_17b1;
  pair *ppStack_17b0;
  QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry> *pQStack_17a8;
  initializer_list<std::pair<QString,QByteArray>> *piStack_17a0;
  pair *ppStack_1798;
  pair *ppStack_1790;
  type *ptStack_1788;
  type *ptStack_1780;
  undefined8 *puStack_1778;
  QList<QString> *pQStack_1770;
  undefined8 uStack_1768;
  wchar16 *local_1760;
  wchar16 *local_1758;
  wchar16 *local_1750;
  wchar16 *local_1748;
  wchar16 *local_1740;
  wchar16 *local_1738;
  wchar16 *local_1730;
  wchar16 *local_1728;
  wchar16 *local_1720;
  wchar16 *pwStack_1718;
  wchar16 *pwStack_1710;
  wchar16 *pwStack_1708;
  undefined *puStack_1700;
  wchar16 *pwStack_16f8;
  wchar16 *pwStack_16f0;
  wchar16 *pwStack_16e8;
  wchar16 *pwStack_16e0;
  wchar16 *pwStack_16d8;
  wchar16 *pwStack_16d0;
  wchar16 *pwStack_16c8;
  wchar16 *pwStack_16c0;
  wchar16 *pwStack_16b8;
  wchar16 *pwStack_16b0;
  wchar16 *pwStack_16a8;
  wchar16 *pwStack_16a0;
  wchar16 *pwStack_1698;
  wchar16 *pwStack_1690;
  wchar16 *pwStack_1688;
  wchar16 *pwStack_1680;
  wchar16 *pwStack_1678;
  wchar16 *pwStack_1670;
  undefined *puStack_1668;
  undefined1 *puStack_1660;
  undefined1 *puStack_1658;
  undefined *puStack_1650;
  wchar16 *pwStack_1648;
  wchar16 *pwStack_1640;
  wchar16 *pwStack_1638;
  wchar16 *pwStack_1630;
  wchar16 *pwStack_1628;
  wchar16 *pwStack_1620;
  undefined1 *puStack_1618;
  undefined1 *puStack_1610;
  undefined1 *puStack_1608;
  undefined1 *puStack_1600;
  undefined1 *puStack_15f8;
  undefined1 *puStack_15f0;
  undefined *puStack_15e8;
  wchar16 *pwStack_15e0;
  wchar16 *pwStack_15d8;
  wchar16 *pwStack_15d0;
  wchar16 *pwStack_15c8;
  wchar16 *pwStack_15c0;
  wchar16 *pwStack_15b8;
  wchar16 *pwStack_15b0;
  wchar16 *pwStack_15a8;
  wchar16 *pwStack_15a0;
  wchar16 *pwStack_1598;
  wchar16 *pwStack_1590;
  wchar16 *pwStack_1588;
  wchar16 *pwStack_1580;
  wchar16 *pwStack_1578;
  wchar16 *pwStack_1570;
  wchar16 *pwStack_1568;
  wchar16 *pwStack_1560;
  wchar16 *pwStack_1558;
  wchar16 *pwStack_1550;
  wchar16 *pwStack_1548;
  wchar16 *pwStack_1540;
  wchar16 *pwStack_1538;
  wchar16 *pwStack_1530;
  wchar16 *pwStack_1528;
  wchar16 *pwStack_1520;
  wchar16 *pwStack_1518;
  wchar16 *pwStack_1510;
  wchar16 *pwStack_1508;
  wchar16 *pwStack_1500;
  QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry> aQStack_14f8 [32];
  QArrayDataPointer<char16_t> local_14d8 [32];
  QArrayDataPointer<char16_t> local_14b8 [32];
  QArrayDataPointer<char16_t> local_1498 [32];
  QArrayDataPointer<char16_t> local_1478 [32];
  QArrayDataPointer<char16_t> local_1458 [32];
  QArrayDataPointer<char16_t> local_1438 [32];
  QArrayDataPointer<char16_t> local_1418 [32];
  QArrayDataPointer<char16_t> local_13f8 [32];
  QArrayDataPointer<char16_t> local_13d8 [32];
  QArrayDataPointer<char16_t> aQStack_13b8 [32];
  QArrayDataPointer<char16_t> aQStack_1398 [32];
  QArrayDataPointer<char16_t> aQStack_1378 [32];
  QArrayDataPointer<char16_t> aQStack_1358 [32];
  QArrayDataPointer<char16_t> aQStack_1338 [32];
  QArrayDataPointer<char16_t> aQStack_1318 [32];
  QArrayDataPointer<char16_t> aQStack_12f8 [32];
  QArrayDataPointer<char16_t> aQStack_12d8 [32];
  QArrayDataPointer<char16_t> aQStack_12b8 [32];
  QArrayDataPointer<char16_t> aQStack_1298 [32];
  QArrayDataPointer<char16_t> aQStack_1278 [32];
  QArrayDataPointer<char16_t> aQStack_1258 [32];
  QArrayDataPointer<char16_t> aQStack_1238 [32];
  QArrayDataPointer<char16_t> aQStack_1218 [32];
  QArrayDataPointer<char16_t> aQStack_11f8 [32];
  QArrayDataPointer<char16_t> aQStack_11d8 [32];
  QArrayDataPointer<char16_t> aQStack_11b8 [32];
  QArrayDataPointer<char16_t> aQStack_1198 [32];
  QArrayDataPointer<char16_t> aQStack_1178 [32];
  QArrayDataPointer<char16_t> aQStack_1158 [32];
  QArrayDataPointer<char16_t> aQStack_1138 [32];
  QArrayDataPointer<char16_t> aQStack_1118 [32];
  QArrayDataPointer<char16_t> aQStack_10f8 [32];
  QArrayDataPointer<char16_t> aQStack_10d8 [32];
  QArrayDataPointer<char16_t> aQStack_10b8 [32];
  QArrayDataPointer<char16_t> aQStack_1098 [32];
  QArrayDataPointer<char16_t> aQStack_1078 [32];
  QArrayDataPointer<char16_t> aQStack_1058 [32];
  QArrayDataPointer<char16_t> aQStack_1038 [32];
  QArrayDataPointer<char16_t> aQStack_1018 [32];
  QArrayDataPointer<char16_t> aQStack_ff8 [32];
  QArrayDataPointer<char16_t> aQStack_fd8 [32];
  QArrayDataPointer<char16_t> aQStack_fb8 [32];
  QArrayDataPointer<char16_t> aQStack_f98 [32];
  QArrayDataPointer<char16_t> aQStack_f78 [32];
  QArrayDataPointer<char16_t> aQStack_f58 [32];
  QArrayDataPointer<char16_t> aQStack_f38 [32];
  QArrayDataPointer<char16_t> aQStack_f18 [32];
  QArrayDataPointer<char16_t> aQStack_ef8 [32];
  QArrayDataPointer<char16_t> aQStack_ed8 [32];
  QArrayDataPointer<char16_t> aQStack_eb8 [32];
  QArrayDataPointer<char16_t> aQStack_e98 [32];
  QArrayDataPointer<char16_t> aQStack_e78 [32];
  QArrayDataPointer<char16_t> aQStack_e58 [32];
  QArrayDataPointer<char16_t> aQStack_e38 [32];
  QArrayDataPointer<char16_t> aQStack_e18 [32];
  QArrayDataPointer<char16_t> aQStack_df8 [32];
  QArrayDataPointer<char16_t> aQStack_dd8 [32];
  QArrayDataPointer<char16_t> aQStack_db8 [32];
  QArrayDataPointer<char16_t> aQStack_d98 [32];
  QArrayDataPointer<char16_t> aQStack_d78 [32];
  QArrayDataPointer<char16_t> aQStack_d58 [32];
  QArrayDataPointer<char16_t> aQStack_d38 [32];
  char **ppcStack_d18;
  undefined8 uStack_d10;
  QArrayDataPointer<char16_t> aQStack_cf8 [32];
  QArrayDataPointer<char16_t> aQStack_cd8 [32];
  undefined8 auStack_cb8 [4];
  undefined8 auStack_c98 [4];
  ulong auStack_c78 [4];
  ulong auStack_c58 [4];
  undefined2 uStack_c38;
  undefined6 uStack_c36;
  undefined8 uStack_c30;
  undefined2 auStack_c18 [16];
  undefined8 auStack_bf8 [4];
  QArrayDataPointer<char16_t> aQStack_bd8 [32];
  QString aQStack_bb8 [24];
  QString aQStack_ba0 [8];
  QString aQStack_b98 [24];
  QString aQStack_b80 [24];
  QString aQStack_b68 [24];
  QString aQStack_b50 [24];
  QString aQStack_b38 [24];
  QString aQStack_b20 [24];
  QString aQStack_b08 [24];
  QString aQStack_af0 [8];
  QString aQStack_ae8 [24];
  QString aQStack_ad0 [24];
  QString aQStack_ab8 [24];
  QString aQStack_aa0 [8];
  QString aQStack_a98 [24];
  QString aQStack_a80 [24];
  QString aQStack_a68 [24];
  QString aQStack_a50 [24];
  QString aQStack_a38 [24];
  QString aQStack_a20 [24];
  QString aQStack_a08 [24];
  QString aQStack_9f0 [24];
  QString aQStack_9d8 [24];
  QString aQStack_9c0 [24];
  QString aQStack_9a8 [24];
  QString aQStack_990 [24];
  QString aQStack_978 [24];
  QString aQStack_960 [24];
  QString aQStack_948 [24];
  QString aQStack_930 [24];
  QString aQStack_918 [24];
  QString aQStack_900 [24];
  QString aQStack_8e8 [24];
  QString aQStack_8d0 [24];
  QString aQStack_8b8 [24];
  QString aQStack_8a0 [24];
  QString aQStack_888 [24];
  QString aQStack_870 [24];
  QString aQStack_858 [24];
  QString aQStack_840 [24];
  QString aQStack_828 [24];
  QString aQStack_810 [8];
  QString aQStack_808 [24];
  QString aQStack_7f0 [24];
  QString aQStack_7d8 [24];
  QString aQStack_7c0 [24];
  QString aQStack_7a8 [24];
  QString aQStack_790 [24];
  QString aQStack_778 [24];
  QString aQStack_760 [8];
  QString local_758 [24];
  QString aQStack_740 [24];
  QString aQStack_728 [24];
  QString aQStack_710 [24];
  QString aQStack_6f8 [24];
  QString aQStack_6e0 [24];
  QString aQStack_6c8 [24];
  QString aQStack_6b0 [24];
  QString aQStack_698 [24];
  QString aQStack_680 [8];
  QString aQStack_678 [24];
  QString aQStack_660 [24];
  QString aQStack_648 [24];
  QString aQStack_630 [24];
  QString aQStack_618 [24];
  QString aQStack_600 [24];
  QString aQStack_5e8 [24];
  QString aQStack_5d0 [24];
  QString aQStack_5b8 [24];
  QString aQStack_5a0 [8];
  QString aQStack_598 [24];
  QString aQStack_580 [24];
  QString aQStack_568 [24];
  QString aQStack_550 [24];
  QString aQStack_538 [24];
  QString aQStack_520 [24];
  QString aQStack_508 [24];
  QString aQStack_4f0 [24];
  QString aQStack_4d8 [24];
  QString aQStack_4c0 [24];
  char *local_4a8;
  undefined8 uStack_4a0;
  undefined1 local_498 [16];
  undefined1 local_488 [16];
  pair<QString,QByteArray> local_478 [16];
  undefined1 local_468 [16];
  char *local_458;
  undefined8 uStack_450;
  pair<QString,QByteArray> local_448 [8];
  function<QImage(int)> afStack_440 [8];
  undefined1 local_438 [16];
  undefined1 local_428 [16];
  undefined1 local_418 [16];
  char *pcStack_408;
  undefined8 uStack_400;
  undefined1 auStack_3f8 [16];
  undefined1 auStack_3e8 [16];
  undefined1 auStack_3d8 [16];
  undefined1 auStack_3c8 [16];
  char *pcStack_3b8;
  undefined8 uStack_3b0;
  undefined1 auStack_3a8 [16];
  undefined1 auStack_398 [16];
  undefined1 auStack_388 [16];
  undefined1 auStack_378 [16];
  char *pcStack_368;
  undefined8 uStack_360;
  undefined1 auStack_358 [16];
  undefined1 auStack_348 [16];
  undefined1 auStack_338 [16];
  undefined1 auStack_328 [16];
  char *pcStack_318;
  undefined8 uStack_310;
  undefined1 auStack_308 [16];
  undefined1 auStack_2f8 [16];
  undefined1 auStack_2e8 [16];
  undefined1 auStack_2d8 [16];
  char *pcStack_2c8;
  undefined8 uStack_2c0;
  undefined1 auStack_2b8 [16];
  undefined1 auStack_2a8 [16];
  undefined1 auStack_298 [16];
  undefined1 auStack_288 [16];
  undefined1 *puStack_278;
  undefined8 uStack_270;
  undefined1 auStack_268 [16];
  undefined1 auStack_258 [16];
  undefined1 auStack_248 [16];
  undefined1 auStack_238 [16];
  char *pcStack_228;
  undefined8 uStack_220;
  undefined1 auStack_218 [16];
  undefined1 auStack_208 [16];
  undefined1 auStack_1f8 [16];
  undefined1 auStack_1e8 [16];
  char *pcStack_1d8;
  undefined8 uStack_1d0;
  undefined1 auStack_1c8 [16];
  undefined1 auStack_1b8 [16];
  undefined1 auStack_1a8 [16];
  undefined1 auStack_198 [16];
  char *pcStack_188;
  undefined8 uStack_180;
  undefined1 auStack_178 [16];
  undefined1 auStack_168 [16];
  undefined1 auStack_158 [16];
  undefined1 auStack_148 [16];
  char *pcStack_138;
  undefined8 uStack_130;
  undefined1 auStack_128 [16];
  undefined1 auStack_118 [16];
  undefined1 auStack_108 [16];
  undefined1 auStack_f8 [16];
  undefined *puStack_e8;
  undefined8 uStack_e0;
  undefined1 auStack_d8 [16];
  undefined1 auStack_c8 [16];
  undefined1 auStack_b8 [16];
  undefined1 auStack_a8 [16];
  char *pcStack_98;
  undefined8 uStack_90;
  undefined1 auStack_88 [16];
  undefined1 auStack_78 [16];
  undefined1 auStack_68 [16];
  undefined1 auStack_58 [16];
  Entry aEStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_488 = (undefined1  [16])0x0;
  local_478[0] = (pair<QString,QByteArray>)0x0;
  local_478[1] = (pair<QString,QByteArray>)0x0;
  local_478[2] = (pair<QString,QByteArray>)0x0;
  local_478[3] = (pair<QString,QByteArray>)0x0;
  local_478[4] = (pair<QString,QByteArray>)0x0;
  local_478[5] = (pair<QString,QByteArray>)0x0;
  local_478[6] = (pair<QString,QByteArray>)0x0;
  local_478[7] = (pair<QString,QByteArray>)0x0;
  local_478[8] = (pair<QString,QByteArray>)0x0;
  local_478[9] = (pair<QString,QByteArray>)0x0;
  local_478[10] = (pair<QString,QByteArray>)0x0;
  local_478[0xb] = (pair<QString,QByteArray>)0x0;
  local_478[0xc] = (pair<QString,QByteArray>)0x0;
  local_478[0xd] = (pair<QString,QByteArray>)0x0;
  local_478[0xe] = (pair<QString,QByteArray>)0x0;
  local_478[0xf] = (pair<QString,QByteArray>)0x0;
  local_468 = (undefined1  [16])0x0;
  uStack_4a0 = 0x3fc47ae147ae147b;
  local_4a8 = "left_ptr";
  local_498 = ZEXT816(0x3faeb851eb851eb8);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_1_,void>
            ((function<QImage(int)> *)(local_498 + 8),&local_17bf);
  local_1720 = L"default";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_14d8,(QTypedArrayData *)0x0,L"default",7);
  QString::QString(local_758,(QArrayDataPointer *)local_14d8);
  local_1728 = L"arrow";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_14b8,(QTypedArrayData *)0x0,L"arrow",5);
  QString::QString(aQStack_740,(QArrayDataPointer *)local_14b8);
  local_1730 = L"top_left_arrow";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1498,(QTypedArrayData *)0x0,L"top_left_arrow",0xe);
  QString::QString(aQStack_728,(QArrayDataPointer *)local_1498);
  local_1738 = L"left_arrow";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_1478,(QTypedArrayData *)0x0,L"left_arrow",10)
  ;
  QString::QString(aQStack_710,(QArrayDataPointer *)local_1478);
  local_1740 = L"draft_large";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1458,(QTypedArrayData *)0x0,L"draft_large",0xb);
  QString::QString(aQStack_6f8,(QArrayDataPointer *)local_1458);
  local_1748 = L"draft_small";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1438,(QTypedArrayData *)0x0,L"draft_small",0xb);
  QString::QString(aQStack_6e0,(QArrayDataPointer *)local_1438);
  local_1750 = L"context-menu";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_1418,(QTypedArrayData *)0x0,L"context-menu",0xc);
  QString::QString(aQStack_6c8,(QArrayDataPointer *)local_1418);
  local_1758 = L"copy";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_13f8,(QTypedArrayData *)0x0,L"copy",4);
  QString::QString(aQStack_6b0,(QArrayDataPointer *)local_13f8);
  local_1760 = L"alias";
  QArrayDataPointer<char16_t>::QArrayDataPointer(local_13d8,(QTypedArrayData *)0x0,L"alias",5);
  QString::QString(aQStack_698,(QArrayDataPointer *)local_13d8);
  QList<QString>::QList(local_478 + 8,local_758,9);
  local_438 = (undefined1  [16])0x0;
  local_428 = (undefined1  [16])0x0;
  local_418 = (undefined1  [16])0x0;
  uStack_450 = 0x3fd999999999999a;
  local_458 = "hand2";
  _local_448 = ZEXT816(0x3faeb851eb851eb8);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_2_,void>
            ((function<QImage(int)> *)(local_448 + 8),&local_17be);
  pwStack_16f0 = L"pointer";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_13b8,(QTypedArrayData *)0x0,L"pointer",7);
  QString::QString(aQStack_9d8,(QArrayDataPointer *)aQStack_13b8);
  pwStack_16f8 = L"hand";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1398,(QTypedArrayData *)0x0,L"hand",4);
  QString::QString(aQStack_9c0,(QArrayDataPointer *)aQStack_1398);
  puStack_1700 = &UNK_002af33c;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1378,(QTypedArrayData *)0x0,L"hand1",5);
  QString::QString(aQStack_9a8,(QArrayDataPointer *)aQStack_1378);
  pwStack_1708 = L"pointing_hand";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1358,(QTypedArrayData *)0x0,L"pointing_hand",0xd);
  QString::QString(aQStack_990,(QArrayDataPointer *)aQStack_1358);
  pwStack_1710 = L"9d800788f1b08800ae810202380a0822";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1338,(QTypedArrayData *)0x0,L"9d800788f1b08800ae810202380a0822",0x20);
  QString::QString(aQStack_978,(QArrayDataPointer *)aQStack_1338);
  pwStack_1718 = L"e29285e634086352946a0e7090d73106";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1318,(QTypedArrayData *)0x0,L"e29285e634086352946a0e7090d73106",0x20);
  QString::QString(aQStack_960,(QArrayDataPointer *)aQStack_1318);
  QList<QString>::QList(local_428 + 8,aQStack_9d8,6);
  auStack_3e8 = (undefined1  [16])0x0;
  auStack_3d8 = (undefined1  [16])0x0;
  auStack_3c8 = (undefined1  [16])0x0;
  uStack_400 = 0x3fe0000000000000;
  pcStack_408 = "xterm";
  auStack_3f8 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_3_,void>
            ((function<QImage(int)> *)(auStack_3f8 + 8),&_Stack_17bd);
  pwStack_16d0 = L"text";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_12f8,(QTypedArrayData *)0x0,L"text",4);
  QString::QString(aQStack_a98,(QArrayDataPointer *)aQStack_12f8);
  pwStack_16d8 = L"ibeam";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_12d8,(QTypedArrayData *)0x0,L"ibeam",5);
  QString::QString(aQStack_a80,(QArrayDataPointer *)aQStack_12d8);
  pwStack_16e0 = L"vertical-text";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_12b8,(QTypedArrayData *)0x0,L"vertical-text",0xd);
  QString::QString(aQStack_a68,(QArrayDataPointer *)aQStack_12b8);
  pwStack_16e8 = L"xterm_i";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1298,(QTypedArrayData *)0x0,L"xterm_i",7);
  QString::QString(aQStack_a50,(QArrayDataPointer *)aQStack_1298);
  QList<QString>::QList(auStack_3d8 + 8,aQStack_a98,4);
  auStack_398 = (undefined1  [16])0x0;
  auStack_388 = (undefined1  [16])0x0;
  auStack_378 = (undefined1  [16])0x0;
  uStack_3b0 = 0x3fe0000000000000;
  pcStack_3b8 = "watch";
  auStack_3a8 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_4_,void>
            ((function<QImage(int)> *)(auStack_3a8 + 8),&_Stack_17bc);
  pwStack_16a0 = L"wait";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1278,(QTypedArrayData *)0x0,L"wait",4);
  QString::QString(aQStack_948,(QArrayDataPointer *)aQStack_1278);
  pwStack_16a8 = L"progress";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1258,(QTypedArrayData *)0x0,L"progress",8);
  QString::QString(aQStack_930,(QArrayDataPointer *)aQStack_1258);
  pwStack_16b0 = L"half-busy";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1238,(QTypedArrayData *)0x0,L"half-busy",9)
  ;
  QString::QString(aQStack_918,(QArrayDataPointer *)aQStack_1238);
  pwStack_16b8 = L"clock";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1218,(QTypedArrayData *)0x0,L"clock",5);
  QString::QString(aQStack_900,(QArrayDataPointer *)aQStack_1218);
  pwStack_16c0 = L"left_ptr_watch";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_11f8,(QTypedArrayData *)0x0,L"left_ptr_watch",0xe);
  QString::QString(aQStack_8e8,(QArrayDataPointer *)aQStack_11f8);
  pwStack_16c8 = L"08e8e1c95fe2fc01f976f1e063a24ccd";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_11d8,(QTypedArrayData *)0x0,L"08e8e1c95fe2fc01f976f1e063a24ccd",0x20);
  QString::QString(aQStack_8d0,(QArrayDataPointer *)aQStack_11d8);
  QList<QString>::QList(auStack_388 + 8,aQStack_948,6);
  auStack_348 = (undefined1  [16])0x0;
  auStack_338 = (undefined1  [16])0x0;
  auStack_328 = (undefined1  [16])0x0;
  uStack_360 = 0x3fc47ae147ae147b;
  pcStack_368 = "question_arrow";
  auStack_358 = ZEXT816(0x3faeb851eb851eb8);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_5_,void>
            ((function<QImage(int)> *)(auStack_358 + 8),&_Stack_17bb);
  pwStack_1688 = L"help";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_11b8,(QTypedArrayData *)0x0,L"help",4);
  QString::QString(aQStack_b38,(QArrayDataPointer *)aQStack_11b8);
  pwStack_1690 = L"whats_this";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1198,(QTypedArrayData *)0x0,L"whats_this",10);
  QString::QString(aQStack_b20,(QArrayDataPointer *)aQStack_1198);
  pwStack_1698 = L"dnd-ask";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1178,(QTypedArrayData *)0x0,L"dnd-ask",7);
  QString::QString(aQStack_b08,(QArrayDataPointer *)aQStack_1178);
  QList<QString>::QList(auStack_338 + 8,aQStack_b38,3);
  auStack_2f8 = (undefined1  [16])0x0;
  auStack_2e8 = (undefined1  [16])0x0;
  auStack_2d8 = (undefined1  [16])0x0;
  uStack_310 = 0x3fe0000000000000;
  pcStack_318 = "fleur";
  auStack_308 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_6_,void>
            ((function<QImage(int)> *)(auStack_308 + 8),&_Stack_17ba);
  pwStack_1670 = L"move";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1158,(QTypedArrayData *)0x0,L"move",4);
  QString::QString(aQStack_ae8,(QArrayDataPointer *)aQStack_1158);
  pwStack_1678 = L"all-scroll";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1138,(QTypedArrayData *)0x0,L"all-scroll",10);
  QString::QString(aQStack_ad0,(QArrayDataPointer *)aQStack_1138);
  pwStack_1680 = L"size_all";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1118,(QTypedArrayData *)0x0,L"size_all",8);
  QString::QString(aQStack_ab8,(QArrayDataPointer *)aQStack_1118);
  QList<QString>::QList(auStack_2e8 + 8,aQStack_ae8,3);
  auStack_2a8 = (undefined1  [16])0x0;
  auStack_298 = (undefined1  [16])0x0;
  auStack_288 = (undefined1  [16])0x0;
  uStack_2c0 = 0x3fe0000000000000;
  pcStack_2c8 = "sb_v_double_arrow";
  auStack_2b8 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_7_,void>
            ((function<QImage(int)> *)(auStack_2b8 + 8),&_Stack_17b9);
  pwStack_1620 = L"ns-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_10f8,(QTypedArrayData *)0x0,L"ns-resize",9)
  ;
  QString::QString(aQStack_598,(QArrayDataPointer *)aQStack_10f8);
  pwStack_1628 = L"size_ver";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_10d8,(QTypedArrayData *)0x0,L"size_ver",8);
  QString::QString(aQStack_580,(QArrayDataPointer *)aQStack_10d8);
  pwStack_1630 = L"v_double_arrow";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_10b8,(QTypedArrayData *)0x0,L"v_double_arrow",0xe);
  QString::QString(aQStack_568,(QArrayDataPointer *)aQStack_10b8);
  pwStack_1638 = L"n-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1098,(QTypedArrayData *)0x0,L"n-resize",8);
  QString::QString(aQStack_550,(QArrayDataPointer *)aQStack_1098);
  pwStack_1640 = L"s-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1078,(QTypedArrayData *)0x0,L"s-resize",8);
  QString::QString(aQStack_538,(QArrayDataPointer *)aQStack_1078);
  pwStack_1648 = L"top_side";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_1058,(QTypedArrayData *)0x0,L"top_side",8);
  QString::QString(aQStack_520,(QArrayDataPointer *)aQStack_1058);
  puStack_1650 = &DAT_002af5dc;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1038,(QTypedArrayData *)0x0,L"bottom_side",0xb);
  QString::QString(aQStack_508,(QArrayDataPointer *)aQStack_1038);
  puStack_1658 = &LAB_002af5f4;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_1018,(QTypedArrayData *)0x0,L"row-resize",10);
  QString::QString(aQStack_4f0,(QArrayDataPointer *)aQStack_1018);
  puStack_1660 = &LAB_002af60a;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_ff8,(QTypedArrayData *)0x0,L"double_arrow",0xc);
  QString::QString(aQStack_4d8,(QArrayDataPointer *)aQStack_ff8);
  puStack_1668 = &DAT_002af628;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_fd8,(QTypedArrayData *)0x0,L"00008160000006810000408080010102",0x20);
  QString::QString(aQStack_4c0,(QArrayDataPointer *)aQStack_fd8);
  QList<QString>::QList(auStack_298 + 8,aQStack_598,10);
  auStack_258 = (undefined1  [16])0x0;
  auStack_248 = (undefined1  [16])0x0;
  auStack_238 = (undefined1  [16])0x0;
  uStack_270 = 0x3fe0000000000000;
  puStack_278 = &LAB_002af669_1;
  auStack_268 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_8_,void>
            ((function<QImage(int)> *)(auStack_268 + 8),&_Stack_17b8);
  pwStack_15d8 = L"ew-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_fb8,(QTypedArrayData *)0x0,L"ew-resize",9);
  QString::QString(aQStack_678,(QArrayDataPointer *)aQStack_fb8);
  pwStack_15e0 = L"size_hor";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_f98,(QTypedArrayData *)0x0,L"size_hor",8);
  QString::QString(aQStack_660,(QArrayDataPointer *)aQStack_f98);
  puStack_15e8 = &DAT_002af6a2;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_f78,(QTypedArrayData *)0x0,L"h_double_arrow",0xe);
  QString::QString(aQStack_648,(QArrayDataPointer *)aQStack_f78);
  puStack_15f0 = &LAB_002af6c0;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_f58,(QTypedArrayData *)0x0,L"e-resize",8);
  QString::QString(aQStack_630,(QArrayDataPointer *)aQStack_f58);
  puStack_15f8 = &LAB_002af6d2;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_f38,(QTypedArrayData *)0x0,L"w-resize",8);
  QString::QString(aQStack_618,(QArrayDataPointer *)aQStack_f38);
  puStack_1600 = &LAB_002af6e4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_f18,(QTypedArrayData *)0x0,L"left_side",9);
  QString::QString(aQStack_600,(QArrayDataPointer *)aQStack_f18);
  puStack_1608 = &LAB_002af6f8;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_ef8,(QTypedArrayData *)0x0,L"right_side",10);
  QString::QString(aQStack_5e8,(QArrayDataPointer *)aQStack_ef8);
  puStack_1610 = &LAB_002af70e;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_ed8,(QTypedArrayData *)0x0,L"col-resize",10);
  QString::QString(aQStack_5d0,(QArrayDataPointer *)aQStack_ed8);
  puStack_1618 = &LAB_002af728;
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_eb8,(QTypedArrayData *)0x0,L"028006030e0e7ebffc7f7070c0600140",0x20);
  QString::QString(aQStack_5b8,(QArrayDataPointer *)aQStack_eb8);
  QList<QString>::QList(auStack_248 + 8,aQStack_678,9);
  auStack_208 = (undefined1  [16])0x0;
  auStack_1f8 = (undefined1  [16])0x0;
  auStack_1e8 = (undefined1  [16])0x0;
  uStack_220 = 0x3fe0000000000000;
  pcStack_228 = "fd_double_arrow";
  auStack_218 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_9_,void>
            ((function<QImage(int)> *)(auStack_218 + 8),&_Stack_17b7);
  pwStack_15a0 = L"nesw-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_e98,(QTypedArrayData *)0x0,L"nesw-resize",0xb);
  QString::QString(aQStack_8b8,(QArrayDataPointer *)aQStack_e98);
  pwStack_15a8 = L"size_bdiag";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_e78,(QTypedArrayData *)0x0,L"size_bdiag",10);
  QString::QString(aQStack_8a0,(QArrayDataPointer *)aQStack_e78);
  pwStack_15b0 = L"ne-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_e58,(QTypedArrayData *)0x0,L"ne-resize",9);
  QString::QString(aQStack_888,(QArrayDataPointer *)aQStack_e58);
  pwStack_15b8 = L"sw-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_e38,(QTypedArrayData *)0x0,L"sw-resize",9);
  QString::QString(aQStack_870,(QArrayDataPointer *)aQStack_e38);
  pwStack_15c0 = L"top_right_corner";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_e18,(QTypedArrayData *)0x0,L"top_right_corner",0x10);
  QString::QString(aQStack_858,(QArrayDataPointer *)aQStack_e18);
  pwStack_15c8 = L"bottom_left_corner";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_df8,(QTypedArrayData *)0x0,L"bottom_left_corner",0x12);
  QString::QString(aQStack_840,(QArrayDataPointer *)aQStack_df8);
  pwStack_15d0 = L"fcf1c3c7cd4491d801f1e1c78f100000";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_dd8,(QTypedArrayData *)0x0,L"fcf1c3c7cd4491d801f1e1c78f100000",0x20);
  QString::QString(aQStack_828,(QArrayDataPointer *)aQStack_dd8);
  QList<QString>::QList(auStack_1f8 + 8,aQStack_8b8,7);
  auStack_1b8 = (undefined1  [16])0x0;
  auStack_1a8 = (undefined1  [16])0x0;
  auStack_198 = (undefined1  [16])0x0;
  uStack_1d0 = 0x3fe0000000000000;
  pcStack_1d8 = "bd_double_arrow";
  auStack_1c8 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_10_,void>
            ((function<QImage(int)> *)(auStack_1c8 + 8),&_Stack_17b6);
  pwStack_1568 = L"nwse-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_db8,(QTypedArrayData *)0x0,L"nwse-resize",0xb);
  QString::QString(aQStack_808,(QArrayDataPointer *)aQStack_db8);
  pwStack_1570 = L"size_fdiag";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_d98,(QTypedArrayData *)0x0,L"size_fdiag",10);
  QString::QString(aQStack_7f0,(QArrayDataPointer *)aQStack_d98);
  pwStack_1578 = L"nw-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d78,(QTypedArrayData *)0x0,L"nw-resize",9);
  QString::QString(aQStack_7d8,(QArrayDataPointer *)aQStack_d78);
  pwStack_1580 = L"se-resize";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d58,(QTypedArrayData *)0x0,L"se-resize",9);
  QString::QString(aQStack_7c0,(QArrayDataPointer *)aQStack_d58);
  pwStack_1588 = L"top_left_corner";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_d38,(QTypedArrayData *)0x0,L"top_left_corner",0xf);
  QString::QString(aQStack_7a8,(QArrayDataPointer *)aQStack_d38);
  pwStack_1590 = L"bottom_right_corner";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&ppcStack_d18,(QTypedArrayData *)0x0,
             L"bottom_right_corner",0x13);
  QString::QString(aQStack_790,(QArrayDataPointer *)&ppcStack_d18);
  pwStack_1598 = L"c7088f0f3e6c8088236ef8e1e3e70000";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (aQStack_cf8,(QTypedArrayData *)0x0,L"c7088f0f3e6c8088236ef8e1e3e70000",0x20);
  QString::QString(aQStack_778,(QArrayDataPointer *)aQStack_cf8);
  QList<QString>::QList(auStack_1a8 + 8,aQStack_808,7);
  auStack_168 = (undefined1  [16])0x0;
  auStack_158 = (undefined1  [16])0x0;
  auStack_148 = (undefined1  [16])0x0;
  uStack_180 = 0x3fe0000000000000;
  pcStack_188 = "crosshair";
  auStack_178 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_11_,void>
            ((function<QImage(int)> *)(auStack_178 + 8),&_Stack_17b5);
  pwStack_1558 = L"cross";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_cd8,(QTypedArrayData *)0x0,L"cross",5);
  QString::QString(aQStack_b98,(QArrayDataPointer *)aQStack_cd8);
  pwStack_1560 = L"tcross";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_cb8,(QTypedArrayData *)0x0,L"tcross",6);
  QString::QString(aQStack_b80,(QArrayDataPointer *)auStack_cb8);
  QList<QString>::QList(auStack_158 + 8,aQStack_b98,2);
  auStack_118 = (undefined1  [16])0x0;
  auStack_108 = (undefined1  [16])0x0;
  auStack_f8 = (undefined1  [16])0x0;
  uStack_130 = 0x3fe0000000000000;
  pcStack_138 = "not-allowed";
  auStack_128 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_12_,void>
            ((function<QImage(int)> *)(auStack_128 + 8),&_Stack_17b4);
  pwStack_1538 = L"forbidden";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_c98,(QTypedArrayData *)0x0,L"forbidden",9);
  QString::QString(aQStack_a38,(QArrayDataPointer *)auStack_c98);
  pwStack_1540 = L"no-drop";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_c78,(QTypedArrayData *)0x0,L"no-drop",7);
  QString::QString(aQStack_a20,(QArrayDataPointer *)auStack_c78);
  pwStack_1548 = L"circle";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_c58,(QTypedArrayData *)0x0,L"circle",6);
  QString::QString(aQStack_a08,(QArrayDataPointer *)auStack_c58);
  pwStack_1550 = L"crossed_circle";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&uStack_c38,(QTypedArrayData *)0x0,L"crossed_circle",0xe
            );
  QString::QString(aQStack_9f0,(QArrayDataPointer *)&uStack_c38);
  QList<QString>::QList(auStack_108 + 8,aQStack_a38,4);
  auStack_c8 = (undefined1  [16])0x0;
  auStack_b8 = (undefined1  [16])0x0;
  auStack_a8 = (undefined1  [16])0x0;
  uStack_e0 = 0x3fe0000000000000;
  puStack_e8 = &DAT_002af9a2;
  auStack_d8 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_13_,void>
            ((function<QImage(int)> *)(auStack_d8 + 8),&_Stack_17b3);
  pwStack_1530 = L"openhand";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_c18,(QTypedArrayData *)0x0,L"openhand",8);
  QString::QString(aQStack_bb8,(QArrayDataPointer *)auStack_c18);
  QList<QString>::QList(auStack_b8 + 8,aQStack_bb8,1);
  auStack_78 = (undefined1  [16])0x0;
  auStack_68 = (undefined1  [16])0x0;
  auStack_58 = (undefined1  [16])0x0;
  uStack_90 = 0x3fe0000000000000;
  pcStack_98 = "grabbing";
  auStack_88 = ZEXT816(0x3fe0000000000000);
  std::function<QImage(int)>::
  function<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::_lambda(int)_14_,void>
            ((function<QImage(int)> *)(auStack_88 + 8),&_Stack_17b2);
  pwStack_1520 = L"closedhand";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_bf8,(QTypedArrayData *)0x0,L"closedhand",10);
  QString::QString(aQStack_b68,(QArrayDataPointer *)auStack_bf8);
  pwStack_1528 = L"dnd-move";
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_bd8,(QTypedArrayData *)0x0,L"dnd-move",8);
  QString::QString(aQStack_b50,(QArrayDataPointer *)aQStack_bd8);
  QList<QString>::QList(auStack_68 + 8,aQStack_b68,2);
  QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::QList
            (aQStack_14f8,&local_4a8,0xe);
  this_00 = aEStack_48;
  while (this_00 != (Entry *)&local_4a8) {
    this_00 = this_00 + -0x50;
    writeXcursorTheme(QString_const&,QList<int>const&)::Entry::~Entry(this_00);
  }
  pQVar8 = aQStack_b38;
  while (pQVar8 != aQStack_b68) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_bd8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_bf8);
  pQVar8 = aQStack_ba0;
  while (pQVar8 != aQStack_bb8) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_c18);
  pQVar8 = aQStack_9d8;
  while (pQVar8 != aQStack_a38) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&uStack_c38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_c58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_c78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_c98);
  pQVar8 = aQStack_b68;
  while (pQVar8 != aQStack_b98) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_cb8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_cd8);
  pQVar8 = aQStack_760;
  while (pQVar8 != aQStack_808) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_cf8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&ppcStack_d18);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_db8);
  pQVar8 = aQStack_810;
  while (pQVar8 != aQStack_8b8) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_dd8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_df8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e18);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_e98);
  pQVar8 = aQStack_5a0;
  while (pQVar8 != aQStack_678) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_eb8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_ed8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_ef8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f18);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f58);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f78);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_f98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_fb8);
  pQVar8 = (QString *)&local_4a8;
  while (pQVar8 != aQStack_598) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_fd8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_ff8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1018);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1038);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1058);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1078);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1098);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_10b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_10d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_10f8);
  pQVar8 = aQStack_aa0;
  while (pQVar8 != aQStack_ae8) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1118);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1138);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1158);
  pQVar8 = aQStack_af0;
  while (pQVar8 != aQStack_b38) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1178);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1198);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_11b8);
  pQVar8 = aQStack_8b8;
  while (pQVar8 != aQStack_948) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_11d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_11f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1218);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1238);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1258);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1278);
  pQVar8 = aQStack_a38;
  while (pQVar8 != aQStack_a98) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1298);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_12b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_12d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_12f8);
  pQVar8 = aQStack_948;
  while (pQVar8 != aQStack_9d8) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1318);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1338);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1358);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1378);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_1398);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_13b8);
  pQVar8 = aQStack_680;
  while (pQVar8 != local_758) {
    pQVar8 = pQVar8 + -0x18;
    QString::~QString(pQVar8);
  }
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_13d8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_13f8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1418);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1438);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1458);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1478);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1498);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_14b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_14d8);
  pwStack_1518 = L"/Kith";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_bf8,(QTypedArrayData *)0x0,L"/Kith",5);
  QString::QString((QString *)aQStack_bd8,(QArrayDataPointer *)auStack_bf8);
  ::operator+((QString *)aQStack_cf8,param_1);
  QString::~QString((QString *)aQStack_bd8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_bf8);
  pwStack_1510 = L"/cursors";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)auStack_bf8,(QTypedArrayData *)0x0,L"/cursors",8);
  QString::QString((QString *)aQStack_bd8,(QArrayDataPointer *)auStack_bf8);
  ::operator+((QString *)aQStack_cd8,(QString *)aQStack_cf8);
  QString::~QString((QString *)aQStack_bd8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_bf8);
  QString::QString((QString *)aQStack_bd8);
  QDir::QDir((QDir *)auStack_c18,(QString *)aQStack_bd8);
  std::optional<QFlags<QFileDevice::Permission>>::optional(auStack_bf8);
  cVar2 = QDir::mkpath(auStack_c18,aQStack_cd8,auStack_bf8[0]);
  QDir::~QDir((QDir *)auStack_c18);
  QString::~QString((QString *)aQStack_bd8);
  if (cVar2 == '\x01') {
    uStack_17b1 = 1;
    pQStack_17a8 = aQStack_14f8;
    auStack_cb8[0] =
         QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::begin
                   (pQStack_17a8);
    auStack_c98[0] =
         QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::end
                   (pQStack_17a8);
    while (cVar2 = QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::
                   const_iterator::operator!=((const_iterator *)auStack_cb8,auStack_c98[0]),
          cVar2 != '\0') {
      puStack_1778 = (undefined8 *)
                     QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>
                     ::const_iterator::operator*((const_iterator *)auStack_cb8);
      QLatin1String::QLatin1String((QLatin1String *)&uStack_c38,(char *)*puStack_1778);
      QString::QString((QString *)aQStack_bd8,CONCAT62(uStack_c36,uStack_c38),uStack_c30);
      QLatin1Char::QLatin1Char((QLatin1Char *)auStack_c78,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)auStack_c58,auStack_c78[0] & 0xff);
      ::operator+(auStack_bf8,aQStack_cd8,auStack_c58[0] & 0xffff);
      ::operator+((QString *)auStack_c18,(QString *)auStack_bf8);
      QString::~QString((QString *)auStack_bf8);
      QString::~QString((QString *)aQStack_bd8);
      cVar2 = writeXcursorFile((QString *)auStack_c18,param_2,(function *)(puStack_1778 + 3),
                               (double)puStack_1778[1],(double)puStack_1778[2]);
      if (cVar2 == '\x01') {
        pQStack_1770 = (QList<QString> *)(puStack_1778 + 7);
        auStack_c78[0] = QList<QString>::begin(pQStack_1770);
        auStack_c58[0] = QList<QString>::end(pQStack_1770);
        while (cVar2 = QList<QString>::const_iterator::operator!=
                                 ((const_iterator *)auStack_c78,auStack_c58[0]), cVar2 != '\0') {
          uStack_1768 = QList<QString>::const_iterator::operator*((const_iterator *)auStack_c78);
          QLatin1Char::QLatin1Char((QLatin1Char *)&ppcStack_d18,'/');
          QChar::QChar<QLatin1Char,true>((QChar *)&uStack_c38,(ulong)ppcStack_d18 & 0xff);
          ::operator+(aQStack_bd8,aQStack_cd8,uStack_c38);
          ::operator+((QString *)auStack_bf8,(QString *)aQStack_bd8);
          QString::~QString((QString *)aQStack_bd8);
          QFile::remove((QString *)auStack_bf8);
          QFile::QFile((QFile *)aQStack_bd8,(QString *)auStack_c18);
          cVar2 = QFile::link((QString *)aQStack_bd8);
          QFile::~QFile((QFile *)aQStack_bd8);
          if (cVar2 != '\x01') {
            QMessageLogger::QMessageLogger((QMessageLogger *)aQStack_bd8,(char *)0x0,0,(char *)0x0);
            QMessageLogger::warning();
            pQVar4 = (QDebug *)
                     QDebug::operator<<((QDebug *)&uStack_c38,
                                        "CursorManager: cannot link cursor alias");
            QDebug::operator<<(pQVar4,(QString *)auStack_bf8);
            QDebug::~QDebug((QDebug *)&uStack_c38);
            uStack_17b1 = 0;
          }
          QString::~QString((QString *)auStack_bf8);
          QList<QString>::const_iterator::operator++((const_iterator *)auStack_c78);
        }
      }
      else {
        uStack_17b1 = 0;
      }
      QString::~QString((QString *)auStack_c18);
      QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::
      const_iterator::operator++((const_iterator *)auStack_cb8);
    }
    ppcStack_d18 = (char **)0x0;
    uStack_d10 = 2;
    pwStack_1500 = L"index.theme";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)auStack_cb8,(QTypedArrayData *)0x0,L"index.theme",0xb)
    ;
    QString::QString((QString *)auStack_c98,(QArrayDataPointer *)auStack_cb8);
    QArrayDataPointer<char>::QArrayDataPointer
              ((QArrayDataPointer<char> *)auStack_c78,(QTypedArrayData *)0x0,
               "[Icon Theme]\nName=Kith\nComment=NCDE stained-glass cursors, generated per-session from procedural art\n"
               ,0x65);
    QByteArray::QByteArray((QByteArray *)auStack_c58,(QArrayDataPointer *)auStack_c78);
    std::pair<QString,QByteArray>::pair<QString,QByteArray,true>
              ((pair<QString,QByteArray> *)&local_4a8,(QString *)auStack_c98,
               (QByteArray *)auStack_c58);
    pwStack_1508 = L"cursor.theme";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&uStack_c38,(QTypedArrayData *)0x0,L"cursor.theme",0xc
              );
    QString::QString((QString *)auStack_c18,(QArrayDataPointer *)&uStack_c38);
    QArrayDataPointer<char>::QArrayDataPointer
              ((QArrayDataPointer<char> *)auStack_bf8,(QTypedArrayData *)0x0,
               "[Icon Theme]\nInherits=Kith\n",0x1b);
    QByteArray::QByteArray((QByteArray *)aQStack_bd8,(QArrayDataPointer *)auStack_bf8);
    std::pair<QString,QByteArray>::pair<QString,QByteArray,true>
              (local_478,(QString *)auStack_c18,(QByteArray *)aQStack_bd8);
    ppcStack_d18 = &local_4a8;
    piStack_17a0 = (initializer_list<std::pair<QString,QByteArray>> *)&ppcStack_d18;
    QByteArray::~QByteArray((QByteArray *)aQStack_bd8);
    QArrayDataPointer<char>::~QArrayDataPointer((QArrayDataPointer<char> *)auStack_bf8);
    QString::~QString((QString *)auStack_c18);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&uStack_c38);
    QByteArray::~QByteArray((QByteArray *)auStack_c58);
    QArrayDataPointer<char>::~QArrayDataPointer((QArrayDataPointer<char> *)auStack_c78);
    QString::~QString((QString *)auStack_c98);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)auStack_cb8);
    ppStack_17b0 = (pair *)std::initializer_list<std::pair<QString,QByteArray>>::begin(piStack_17a0)
    ;
    ppStack_1798 = (pair *)std::initializer_list<std::pair<QString,QByteArray>>::end(piStack_17a0);
    for (; ppStack_17b0 != ppStack_1798; ppStack_17b0 = ppStack_17b0 + 0x30) {
      ppStack_1790 = ppStack_17b0;
      ptStack_1788 = std::get<0ul,QString,QByteArray>(ppStack_17b0);
      ptStack_1780 = std::get<1ul,QString,QByteArray>(ppStack_1790);
      QLatin1Char::QLatin1Char((QLatin1Char *)auStack_c58,'/');
      QChar::QChar<QLatin1Char,true>((QChar *)auStack_c18,auStack_c58[0] & 0xff);
      ::operator+(auStack_bf8,aQStack_cf8,auStack_c18[0]);
      ::operator+((QString *)aQStack_bd8,(QString *)auStack_bf8);
      QFile::QFile((QFile *)&uStack_c38,(QString *)aQStack_bd8);
      QString::~QString((QString *)aQStack_bd8);
      QString::~QString((QString *)auStack_bf8);
      uVar3 = operator|(2,8);
      cVar2 = QFile::open(&uStack_c38,uVar3);
      if (cVar2 == '\x01') {
        lVar5 = QIODevice::write((QByteArray *)&uStack_c38);
        lVar6 = QByteArray::size((QByteArray *)ptStack_1780);
        if (lVar5 != lVar6) goto LAB_00281da5;
        bVar1 = false;
      }
      else {
LAB_00281da5:
        bVar1 = true;
      }
      if (bVar1) {
        QMessageLogger::QMessageLogger((QMessageLogger *)aQStack_bd8,(char *)0x0,0,(char *)0x0);
        QMessageLogger::warning();
        pQVar4 = (QDebug *)QDebug::operator<<((QDebug *)auStack_c58,"CursorManager: cannot write");
        QFile::fileName();
        pQVar4 = (QDebug *)QDebug::operator<<(pQVar4,(QString *)auStack_c18);
        QIODevice::errorString();
        QDebug::operator<<(pQVar4,(QString *)auStack_bf8);
        QString::~QString((QString *)auStack_bf8);
        QString::~QString((QString *)auStack_c18);
        QDebug::~QDebug((QDebug *)auStack_c58);
        uStack_17b1 = 0;
      }
      QFile::~QFile((QFile *)&uStack_c38);
    }
    this_01 = local_448;
    while (uVar7 = uStack_17b1, this_01 != (pair<QString,QByteArray> *)&local_4a8) {
      this_01 = this_01 + -0x30;
      std::pair<QString,QByteArray>::~pair(this_01);
    }
  }
  else {
    QMessageLogger::QMessageLogger((QMessageLogger *)aQStack_bd8,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar4 = (QDebug *)
             QDebug::operator<<((QDebug *)auStack_bf8,
                                "CursorManager: cannot create cursor theme dir");
    QDebug::operator<<(pQVar4,(QString *)aQStack_cd8);
    QDebug::~QDebug((QDebug *)auStack_bf8);
    uVar7 = 0;
  }
  QString::~QString((QString *)aQStack_cd8);
  QString::~QString((QString *)aQStack_cf8);
  QList<CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry>::~QList
            (aQStack_14f8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar7;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00284c58  CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry::Entry

/* Entry(Entry const&) */

void __thiscall
CursorManager::writeXcursorTheme(QString_const&,QList<int>const&)::Entry::Entry
          (Entry *this,Entry *param_1)

{
  *(undefined8 *)this = *(undefined8 *)param_1;
  *(undefined8 *)(this + 8) = *(undefined8 *)(param_1 + 8);
                    /* catch() { ... } // from try @ 00285055 with catch @ 00284c8a */
  *(undefined8 *)(this + 0x10) = *(undefined8 *)(param_1 + 0x10);
  std::function<QImage(int)>::function((function<QImage(int)> *)(this + 0x18),param_1 + 0x18);
  QList<QString>::QList((QList<QString> *)(this + 0x38),(QList *)(param_1 + 0x38));
  return;
}


