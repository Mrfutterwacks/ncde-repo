// Ghidra decompile of LaPivot.oracle — class/namespace QTimer (39 functions). Raw; not source.

// ==== 001545e7  QTimer::toDuration

/* QTimer::toDuration(int) */

undefined8 QTimer::toDuration(int param_1)

{
  long in_FS_OFFSET;
  int local_2c [3];
  duration<long,std::ratio<1l,1000l>> local_20 [8];
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_2c[0] = param_1;
  std::chrono::duration<long,std::ratio<1l,1000l>>::duration<int,void>(local_20,local_2c);
  std::chrono::duration<long,std::ratio<1l,1000000000l>>::duration<long,std::ratio<1l,1000l>,void>
            ((duration<long,std::ratio<1l,1000000000l>> *)&local_18,local_20);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 00154641  QTimer::defaultTypeFor

/* QTimer::defaultTypeFor(int) */

void QTimer::defaultTypeFor(int param_1)

{
  long in_FS_OFFSET;
  int local_2c [3];
  duration<long,std::ratio<1l,1000l>> local_20 [8];
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_2c[0] = param_1;
  std::chrono::duration<long,std::ratio<1l,1000l>>::duration<int,void>(local_20,local_2c);
  std::chrono::duration<long,std::ratio<1l,1000000000l>>::duration<long,std::ratio<1l,1000l>,void>
            ((duration<long,std::ratio<1l,1000000000l>> *)&local_18,local_20);
  defaultTypeFor(local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015479b  QTimer::defaultTypeFor

/* QTimer::defaultTypeFor(std::chrono::duration<long, std::ratio<1l, 1000000000l> >) */

bool QTimer::defaultTypeFor(undefined8 param_1)

{
  bool bVar1;
  long in_FS_OFFSET;
  undefined8 local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = param_1;
  local_18 = s<(char)50>();
  bVar1 = std::chrono::operator>=((duration *)&local_20,(duration *)&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar1;
}



// ==== 001a50b3  QTimer::singleShot<int,AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}>

/* void QTimer::singleShot<int, AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<AppMenuModel::AppMenuModel(QObject*)::{lambda()#1},
   void>::ContextType const*, AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}&&) */

void QTimer::singleShot<int,AppMenuModel::AppMenuModel(QObject*)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,AppMenuModel::AppMenuModel(QObject*)::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001a76b5  QTimer::singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}>

/* void QTimer::singleShot<int, GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1},
   void>::ContextType const*, GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}&&) */

void QTimer::singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001abfc7  QTimer::singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}>

/* void QTimer::singleShot<int, NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1},
   void>::ContextType const*, NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}&&) */

void QTimer::singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001ac129  QTimer::singleShot<int,NCDEWindowManager::onPicomDied()::{lambda()#1}>

/* void QTimer::singleShot<int, NCDEWindowManager::onPicomDied()::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<NCDEWindowManager::onPicomDied()::{lambda()#1},
   void>::ContextType const*, NCDEWindowManager::onPicomDied()::{lambda()#1}&&) */

void QTimer::singleShot<int,NCDEWindowManager::onPicomDied()::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,NCDEWindowManager::onPicomDied()::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001ad2d3  QTimer::singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayMode(QString const&, QString const&,
   double)::{lambda()#1}>(int, QtPrivate::ContextTypeForFunctor<Settings::applyDisplayMode(QString
   const&, QString const&, double)::{lambda()#1}, void>::ContextType const*,
   Settings::applyDisplayMode(QString const&, QString const&, double)::{lambda()#1}&&) */

void QTimer::
     singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001ad317  QTimer::singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayOrientation(QString const&, QString
   const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Settings::applyDisplayOrientation(QString const&, QString
   const&)::{lambda()#1}, void>::ContextType const*, Settings::applyDisplayOrientation(QString
   const&, QString const&)::{lambda()#1}&&) */

void QTimer::
     singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001ad3d2  QTimer::singleShot<int,Settings::applyDisplayScale(QString_const&,int)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayScale(QString const&, int)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Settings::applyDisplayScale(QString const&, int)::{lambda()#1},
   void>::ContextType const*, Settings::applyDisplayScale(QString const&, int)::{lambda()#1}&&) */

void QTimer::singleShot<int,Settings::applyDisplayScale(QString_const&,int)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Settings::applyDisplayScale(QString_const&,int)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 001af015  QTimer::singleShot<int,AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}>

/* void QTimer::singleShot<int, AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}>(int,
   Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<AppMenuModel::AppMenuModel(QObject*)::{lambda()#1},
   void>::ContextType const*, AppMenuModel::AppMenuModel(QObject*)::{lambda()#1}&&) */

void QTimer::singleShot<int,AppMenuModel::AppMenuModel(QObject*)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),AppMenuModel::AppMenuModel(QObject*)::_lambda()_1_>(param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b0cb7  QTimer::singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}>

/* void QTimer::singleShot<int, GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}>(int,
   Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1},
   void>::ContextType const*, GliaSystemMenus::GliaSystemMenus(QObject*)::{lambda()#1}&&) */

void QTimer::singleShot<int,GliaSystemMenus::GliaSystemMenus(QObject*)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),GliaSystemMenus::GliaSystemMenus(QObject*)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b4769  QTimer::singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}>

/* void QTimer::singleShot<int, NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}>(int,
   Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1},
   void>::ContextType const*, NCDEWindowManager::scheduleCoveringRecount()::{lambda()#1}&&) */

void QTimer::singleShot<int,NCDEWindowManager::scheduleCoveringRecount()::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),NCDEWindowManager::scheduleCoveringRecount()::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b493f  QTimer::singleShot<int,NCDEWindowManager::onPicomDied()::{lambda()#1}>

/* void QTimer::singleShot<int, NCDEWindowManager::onPicomDied()::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<NCDEWindowManager::onPicomDied()::{lambda()#1},
   void>::ContextType const*, NCDEWindowManager::onPicomDied()::{lambda()#1}&&) */

void QTimer::singleShot<int,NCDEWindowManager::onPicomDied()::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::makeCallableObject<void(*)(),NCDEWindowManager::onPicomDied()::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b5290  QTimer::singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayMode(QString const&, QString const&,
   double)::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<Settings::applyDisplayMode(QString const&, QString const&,
   double)::{lambda()#1}, void>::ContextType const*, Settings::applyDisplayMode(QString const&,
   QString const&, double)::{lambda()#1}&&) */

void QTimer::
     singleShot<int,Settings::applyDisplayMode(QString_const&,QString_const&,double)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Settings::applyDisplayMode(QString_const&,QString_const&,double)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b52e3  QTimer::singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayOrientation(QString const&, QString
   const&)::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<Settings::applyDisplayOrientation(QString const&, QString
   const&)::{lambda()#1}, void>::ContextType const*, Settings::applyDisplayOrientation(QString
   const&, QString const&)::{lambda()#1}&&) */

void QTimer::
     singleShot<int,Settings::applyDisplayOrientation(QString_const&,QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Settings::applyDisplayOrientation(QString_const&,QString_const&)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 001b5336  QTimer::singleShot<int,Settings::applyDisplayScale(QString_const&,int)::{lambda()#1}>

/* void QTimer::singleShot<int, Settings::applyDisplayScale(QString const&, int)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Settings::applyDisplayScale(QString const&,
   int)::{lambda()#1}, void>::ContextType const*, Settings::applyDisplayScale(QString const&,
   int)::{lambda()#1}&&) */

void QTimer::singleShot<int,Settings::applyDisplayScale(QString_const&,int)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Settings::applyDisplayScale(QString_const&,int)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 00227887  QTimer::singleShot<int,Lelan::scheduleWifiChanged()::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::scheduleWifiChanged()::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::scheduleWifiChanged()::{lambda()#1}, void>::ContextType
   const*, Lelan::scheduleWifiChanged()::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::scheduleWifiChanged()::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Lelan::scheduleWifiChanged()::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0022821c  QTimer::singleShot<int,Lelan::scheduleWifiChanged()::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::scheduleWifiChanged()::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<Lelan::scheduleWifiChanged()::{lambda()#1}, void>::ContextType
   const*, Lelan::scheduleWifiChanged()::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::scheduleWifiChanged()::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::makeCallableObject<void(*)(),Lelan::scheduleWifiChanged()::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0024ced9  QTimer::singleShot<int,Lelan::scheduleNightLightEvents(double,double)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::scheduleNightLightEvents(double, double)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::scheduleNightLightEvents(double, double)::{lambda()#1},
   void>::ContextType const*, Lelan::scheduleNightLightEvents(double, double)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::scheduleNightLightEvents(double,double)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Lelan::scheduleNightLightEvents(double,double)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0024d24a  QTimer::singleShot<int,Lelan::scheduleNightLightEvents(double,double)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::scheduleNightLightEvents(double, double)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::scheduleNightLightEvents(double,
   double)::{lambda()#1}, void>::ContextType const*, Lelan::scheduleNightLightEvents(double,
   double)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::scheduleNightLightEvents(double,double)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::scheduleNightLightEvents(double,double)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025afa7  QTimer::singleShot<int,Lelan::mountVolume(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::mountVolume(QString const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::mountVolume(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::mountVolume(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::mountVolume(QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* try { // try from 0025afab to 0035afaf has its CatchHandler @ 0025b35a */
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Lelan::mountVolume(QString_const&)::_lambda()_1_>(param_1,uVar1,param_2,param_3);
                    /* try { // try from 0025afe8 to 0035b00a has its CatchHandler @ 0025b468 */
  return;
}



// ==== 0025afeb  QTimer::singleShot<int,Lelan::unmountVolume(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::unmountVolume(QString const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::unmountVolume(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::unmountVolume(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::unmountVolume(QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
                    /* try { // try from 0025b01c to 0035b020 has its CatchHandler @ 0025b37f */
  singleShot<int,Lelan::unmountVolume(QString_const&)::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0025b0fb  QTimer::singleShot<int,Lelan::setDefaultPrinter(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setDefaultPrinter(QString const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::setDefaultPrinter(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::setDefaultPrinter(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setDefaultPrinter(QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
                    /* try { // try from 0025b136 to 0035b13a has its CatchHandler @ 0025b414 */
  singleShot<int,Lelan::setDefaultPrinter(QString_const&)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0025b13f  QTimer::singleShot<int,Lelan::removePrinter(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::removePrinter(QString const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::removePrinter(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::removePrinter(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::removePrinter(QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* try { // try from 0025b15f to 0035b163 has its CatchHandler @ 0025b3b8 */
  uVar1 = defaultTypeFor(param_1);
                    /* try { // try from 0025b175 to 0035b179 has its CatchHandler @ 0025b3a7 */
  singleShot<int,Lelan::removePrinter(QString_const&)::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0025b31b  QTimer::singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::addUser(QString const&, QString const&,
   bool)::{lambda()#1}>(int, QtPrivate::ContextTypeForFunctor<Lelan::addUser(QString const&, QString
   const&, bool)::{lambda()#1}, void>::ContextType const*, Lelan::addUser(QString const&, QString
   const&, bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
                    /* catch() { ... } // from try @ 0025afab with catch @ 0025b35a */
  return;
}



// ==== 0025b35f  QTimer::singleShot<int,Lelan::removeUser(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::removeUser(QString const&)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::removeUser(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::removeUser(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::removeUser(QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* catch() { ... } // from try @ 0025af95 with catch @ 0025b36b */
                    /* catch() { ... } // from try @ 0025b01c with catch @ 0025b37f */
  uVar1 = defaultTypeFor(param_1);
                    /* catch() { ... } // from try @ 0025b0cc with catch @ 0025b393 */
  singleShot<int,Lelan::removeUser(QString_const&)::_lambda()_1_>(param_1,uVar1,param_2,param_3);
  return;
}



// ==== 0025b3a3  QTimer::singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setUserAdmin(QString const&, bool)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::setUserAdmin(QString const&, bool)::{lambda()#1},
   void>::ContextType const*, Lelan::setUserAdmin(QString const&, bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* catch() { ... } // from try @ 0025b175 with catch @ 0025b3a7 */
                    /* catch() { ... } // from try @ 0025b15f with catch @ 0025b3b8 */
  uVar1 = defaultTypeFor(param_1);
                    /* catch() { ... } // from try @ 0025b200 with catch @ 0025b3d5 */
  singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
                    /* catch() { ... } // from try @ 0025b1ea with catch @ 0025b3e6 */
  return;
}



// ==== 0025b3e7  QTimer::singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setAutoLogin(QString const&, bool)::{lambda()#1}>(int,
   QtPrivate::ContextTypeForFunctor<Lelan::setAutoLogin(QString const&, bool)::{lambda()#1},
   void>::ContextType const*, Lelan::setAutoLogin(QString const&, bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* catch() { ... } // from try @ 0025b262 with catch @ 0025b403 */
  uVar1 = defaultTypeFor(param_1);
                    /* catch() { ... } // from try @ 0025b1c1 with catch @ 0025b414 */
  singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
                    /* catch() { ... } // from try @ 0025b0f3 with catch @ 0025b428 */
  return;
}



// ==== 0025b42b  QTimer::singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setUserAvatar(QString const&, QString
   const&)::{lambda()#1}>(int, QtPrivate::ContextTypeForFunctor<Lelan::setUserAvatar(QString const&,
   QString const&)::{lambda()#1}, void>::ContextType const*, Lelan::setUserAvatar(QString const&,
   QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::_lambda()_1_>
               (int param_1,ContextType *param_2,_lambda___1_ *param_3)

{
  undefined4 uVar1;
  
                    /* catch() { ... } // from try @ 0025b2b0 with catch @ 0025b43c */
                    /* catch() { ... } // from try @ 0025b0b1 with catch @ 0025b454 */
  uVar1 = defaultTypeFor(param_1);
  singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::_lambda()_1_>
            (param_1,uVar1,param_2,param_3);
                    /* catch() { ... } // from try @ 0025afe8 with catch @ 0025b468 */
  return;
}



// ==== 0025b51d  QTimer::singleShot<int,Lelan::mountVolume(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::mountVolume(QString const&)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::mountVolume(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::mountVolume(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::mountVolume(QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
                    /* try { // try from 0025b532 to 0035b536 has its CatchHandler @ 0025b728 */
  uVar1 = QtPrivate::makeCallableObject<void(*)(),Lelan::mountVolume(QString_const&)::_lambda()_1_>
                    (param_4);
                    /* try { // try from 0025b553 to 0035b557 has its CatchHandler @ 0025b714 */
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
                    /* try { // try from 0025b569 to 0035b56d has its CatchHandler @ 0025b703 */
  return;
}



// ==== 0025b570  QTimer::singleShot<int,Lelan::unmountVolume(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::unmountVolume(QString const&)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::unmountVolume(QString
   const&)::{lambda()#1}, void>::ContextType const*, Lelan::unmountVolume(QString
   const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::unmountVolume(QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
                    /* try { // try from 0025b582 to 0035b586 has its CatchHandler @ 0025b6ef */
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::unmountVolume(QString_const&)::_lambda()_1_>(param_4);
                    /* try { // try from 0025b5a7 to 0035b5ab has its CatchHandler @ 0025b6cf */
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025b61a  QTimer::singleShot<int,Lelan::setDefaultPrinter(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setDefaultPrinter(QString const&)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::setDefaultPrinter(QString
   const&)::{lambda()#1}, void>::ContextType const*, Lelan::setDefaultPrinter(QString
   const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setDefaultPrinter(QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::setDefaultPrinter(QString_const&)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025b66d  QTimer::singleShot<int,Lelan::removePrinter(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::removePrinter(QString const&)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::removePrinter(QString
   const&)::{lambda()#1}, void>::ContextType const*, Lelan::removePrinter(QString
   const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::removePrinter(QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::removePrinter(QString_const&)::_lambda()_1_>(param_4);
  uVar2 = toDuration(param_1);
                    /* catch() { ... } // from try @ 0025b5db with catch @ 0025b6aa */
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
                    /* catch() { ... } // from try @ 0025b5c5 with catch @ 0025b6bb */
  return;
}



// ==== 0025b76e  QTimer::singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::addUser(QString const&, QString const&,
   bool)::{lambda()#1}>(int, Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::addUser(QString
   const&, QString const&, bool)::{lambda()#1}, void>::ContextType const*, Lelan::addUser(QString
   const&, QString const&, bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::addUser(QString_const&,QString_const&,bool)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
                    /* catch() { ... } // from try @ 0025c973 with catch @ 0025b774 */
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::addUser(QString_const&,QString_const&,bool)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
                    /* try { // try from 0025b7ac to 0035b7c4 has its CatchHandler @ 0025b774 */
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025b7c1  QTimer::singleShot<int,Lelan::removeUser(QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::removeUser(QString const&)::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<Lelan::removeUser(QString const&)::{lambda()#1},
   void>::ContextType const*, Lelan::removeUser(QString const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::removeUser(QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
                    /* try { // try from 0025b7d9 to 0035b7dd has its CatchHandler @ 0025c947 */
  uVar1 = QtPrivate::makeCallableObject<void(*)(),Lelan::removeUser(QString_const&)::_lambda()_1_>
                    (param_4);
                    /* try { // try from 0025b7f2 to 0035b808 has its CatchHandler @ 0025c628 */
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025b814  QTimer::singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setUserAdmin(QString const&, bool)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::setUserAdmin(QString const&,
   bool)::{lambda()#1}, void>::ContextType const*, Lelan::setUserAdmin(QString const&,
   bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setUserAdmin(QString_const&,bool)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
                    /* try { // try from 0025b824 to 0035b828 has its CatchHandler @ 0025c614 */
                    /* try { // try from 0025b836 to 0035b856 has its CatchHandler @ 0025c600 */
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::setUserAdmin(QString_const&,bool)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
                    /* try { // try from 0025b864 to 0035b87a has its CatchHandler @ 0025c5ec */
  return;
}



// ==== 0025b867  QTimer::singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setAutoLogin(QString const&, bool)::{lambda()#1}>(int,
   Qt::TimerType, QtPrivate::ContextTypeForFunctor<Lelan::setAutoLogin(QString const&,
   bool)::{lambda()#1}, void>::ContextType const*, Lelan::setAutoLogin(QString const&,
   bool)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setAutoLogin(QString_const&,bool)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::setAutoLogin(QString_const&,bool)::_lambda()_1_>
                    (param_4);
                    /* try { // try from 0025b896 to 0035b89a has its CatchHandler @ 0025c5d8 */
  uVar2 = toDuration(param_1);
                    /* try { // try from 0025b8a8 to 0035b8ac has its CatchHandler @ 0025c5c4 */
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}



// ==== 0025b8ba  QTimer::singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::{lambda()#1}>

/* void QTimer::singleShot<int, Lelan::setUserAvatar(QString const&, QString
   const&)::{lambda()#1}>(int, Qt::TimerType,
   QtPrivate::ContextTypeForFunctor<Lelan::setUserAvatar(QString const&, QString
   const&)::{lambda()#1}, void>::ContextType const*, Lelan::setUserAvatar(QString const&, QString
   const&)::{lambda()#1}&&) */

void QTimer::singleShot<int,Lelan::setUserAvatar(QString_const&,QString_const&)::_lambda()_1_>
               (int param_1,undefined4 param_2,undefined8 param_3,_lambda___1_ *param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  uVar1 = QtPrivate::
          makeCallableObject<void(*)(),Lelan::setUserAvatar(QString_const&,QString_const&)::_lambda()_1_>
                    (param_4);
  uVar2 = toDuration(param_1);
  QTimer::singleShotImpl(uVar2,param_2,param_3,uVar1);
  return;
}


