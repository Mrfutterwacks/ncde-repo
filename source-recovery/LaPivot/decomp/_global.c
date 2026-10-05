// Ghidra decompile of LaPivot.oracle — class/namespace _global (311 functions). Raw; not source.

// ==== 00137000  _init

int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = __gmon_start__();
  return iVar1;
}



// ==== 00137020  FUN_00137020

void FUN_00137020(void)

{
  (*(code *)(undefined *)0x0)();
  return;
}



// ==== 00139d30  _start

void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  __libc_start_main(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== 00139d60  deregister_tm_clones

/* WARNING: Removing unreachable block (ram,0x00139d73) */
/* WARNING: Removing unreachable block (ram,0x00139d7f) */

void deregister_tm_clones(void)

{
  return;
}



// ==== 00139d90  register_tm_clones

/* WARNING: Removing unreachable block (ram,0x00139db4) */
/* WARNING: Removing unreachable block (ram,0x00139dc0) */

void register_tm_clones(void)

{
  return;
}



// ==== 00139dd0  __do_global_dtors_aux

void __do_global_dtors_aux(void)

{
  if (completed_0 != '\0') {
    return;
  }
  __cxa_finalize(__dso_handle);
  deregister_tm_clones();
  completed_0 = 1;
  return;
}



// ==== 001507f0  operator.new

/* operator new(unsigned long, void*) */

void * operator_new(ulong param_1,void *param_2)

{
  return param_2;
}



// ==== 00150802  operator.delete

/* operator delete(void*, void*) */

void operator_delete(void *param_1,void *param_2)

{
  return;
}



// ==== 001508cb  qRound

/* qRound(double) */

void qRound(double param_1)

{
  double dVar1;
  
  dVar1 = (double)QtPrivate::QRoundImpl::qRound(param_1);
  QtPrivate::qCheckedFPConversionToInteger<int,double,true,true>(dVar1);
  return;
}



// ==== 00150ee7  qstrlen

/* qstrlen(char const*) */

size_t qstrlen(char *param_1)

{
  size_t sVar1;
  
  if (param_1 == (char *)0x0) {
    sVar1 = 0;
  }
  else {
    sVar1 = strlen(param_1);
  }
  return sVar1;
}



// ==== 00150f0f  qstrnlen

/* qstrnlen(char const*, unsigned long) */

ulong qstrnlen(char *param_1,ulong param_2)

{
  void *pvVar1;
  
  if (param_1 == (char *)0x0) {
    param_2 = 0;
  }
  else {
    pvVar1 = memchr(param_1,0,param_2);
    if (pvVar1 != (void *)0x0) {
      param_2 = (long)pvVar1 - (long)param_1;
    }
  }
  return param_2;
}



// ==== 001510b0  comparesEqual

/* comparesEqual(QByteArrayView const&, QByteArrayView const&) */

undefined8 comparesEqual(QByteArrayView *param_1,QByteArrayView *param_2)

{
  int iVar1;
  long lVar2;
  long lVar3;
  size_t __n;
  void *__s2;
  void *__s1;
  undefined8 uVar4;
  
  lVar2 = QByteArrayView::size(param_1);
  lVar3 = QByteArrayView::size(param_2);
  if (lVar2 == lVar3) {
    lVar2 = QByteArrayView::size(param_1);
    if (lVar2 != 0) {
      __n = QByteArrayView::size(param_1);
      __s2 = (void *)QByteArrayView::data(param_2);
      __s1 = (void *)QByteArrayView::data(param_1);
      iVar1 = memcmp(__s1,__s2,__n);
      if (iVar1 != 0) goto LAB_00151137;
    }
    uVar4 = 1;
  }
  else {
LAB_00151137:
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 00151145  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QByteArrayView const&, QByteArrayView const&) */

void operator==(QByteArrayView *param_1,QByteArrayView *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015146d  comparesEqual

/* comparesEqual(QByteArray const&, QByteArrayView const&) */

void comparesEqual(QByteArray *param_1,QByteArrayView *param_2)

{
  long in_FS_OFFSET;
  QByteArrayView local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QByteArrayView::QByteArrayView<QByteArray,true>(local_28,param_1);
  operator==(local_28,param_2);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001514c8  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QByteArray const&, char const* const&) */

uint operator!=(QByteArray *param_1,char **param_2)

{
  uint uVar1;
  long in_FS_OFFSET;
  QByteArrayView local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QByteArrayView::QByteArrayView<char_const*,true>(local_28,param_2);
  uVar1 = comparesEqual(param_1,local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1 ^ 1;
}



// ==== 001517fa  comparesEqual

/* comparesEqual(QStringView const&, QStringView const&) */

undefined8 comparesEqual(QStringView *param_1,QStringView *param_2)

{
  char cVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = QStringView::size(param_1);
  lVar3 = QStringView::size(param_2);
  if ((lVar2 == lVar3) &&
     (cVar1 = QtPrivate::equalStrings
                        (*(undefined8 *)param_1,*(undefined8 *)(param_1 + 8),*(undefined8 *)param_2,
                         *(undefined8 *)(param_2 + 8)), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}



// ==== 00151862  compareThreeWay

/* compareThreeWay(QStringView const&, QStringView const&) */

void compareThreeWay(QStringView *param_1,QStringView *param_2)

{
  int iVar1;
  
  iVar1 = QtPrivate::compareStrings
                    (*(undefined8 *)param_1,*(undefined8 *)(param_1 + 8),*(undefined8 *)param_2,
                     *(undefined8 *)(param_2 + 8),1);
  Qt::compareThreeWay<int,int,true,true>(iVar1,0);
  return;
}



// ==== 00152237  comparesEqual

/* comparesEqual(QString const&, QString const&) */

void comparesEqual(QString *param_1,QString *param_2)

{
  long in_FS_OFFSET;
  QStringView local_38 [16];
  QStringView local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QStringView::QStringView<QString,true>(local_28,param_2);
  QStringView::QStringView<QString,true>(local_38,param_1);
  comparesEqual(local_38,local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001522a5  compareThreeWay

/* compareThreeWay(QString const&, QString const&) */

void compareThreeWay(QString *param_1,QString *param_2)

{
  long in_FS_OFFSET;
  QStringView local_38 [16];
  QStringView local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QStringView::QStringView<QString,true>(local_28,param_2);
  QStringView::QStringView<QString,true>(local_38,param_1);
  compareThreeWay(local_38,local_28);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00152313  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) */

void operator==(QString *param_1,QString *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015235b  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) */

uint operator!=(QString *param_1,QString *param_2)

{
  uint uVar1;
  
  uVar1 = comparesEqual(param_1,param_2);
  return uVar1 ^ 1;
}



// ==== 00152383  operator<

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) */

void operator<(QString *param_1,QString *param_2)

{
  long lVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = compareThreeWay(param_1,param_2);
  Qt::is_lt(uVar2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001523d2  comparesEqual

/* comparesEqual(QString const&, QLatin1String) */

undefined8 comparesEqual(QString *param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  QString *local_40;
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_58 = param_2;
  local_50 = param_3;
  local_40 = param_1;
  lVar2 = QString::size(param_1);
  lVar3 = QLatin1String::size((QLatin1String *)&local_58);
  if (lVar2 == lVar3) {
    QStringView::QStringView<QString,true>((QStringView *)&local_38,local_40);
    cVar1 = QtPrivate::equalStrings(local_38,local_30,local_58,local_50);
    if (cVar1 != '\0') {
      uVar4 = 1;
      goto LAB_00152465;
    }
  }
  uVar4 = 0;
LAB_00152465:
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar4;
}



// ==== 0015247f  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QLatin1String const&) */

void operator==(QString *param_1,QLatin1String *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,*(undefined8 *)param_2,*(undefined8 *)(param_2 + 8));
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001524ce  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QLatin1String const&) */

uint operator!=(QString *param_1,QLatin1String *param_2)

{
  uint uVar1;
  
  uVar1 = comparesEqual(param_1,*(undefined8 *)param_2,*(undefined8 *)(param_2 + 8));
  return uVar1 ^ 1;
}



// ==== 001525bd  comparesEqual

/* comparesEqual(QString const&, QByteArrayView) */

bool comparesEqual(QString *param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 local_48;
  undefined8 local_40;
  QString *local_30;
  
  local_48 = param_2;
  local_40 = param_3;
  local_30 = param_1;
  uVar2 = QByteArrayView::size((QByteArrayView *)&local_48);
  uVar3 = QByteArrayView::constData((QByteArrayView *)&local_48);
  uVar4 = QString::size(local_30);
  uVar5 = QString::constData(local_30);
  iVar1 = QString::compare_helper(uVar5,uVar4,uVar3,uVar2,1);
  return iVar1 == 0;
}



// ==== 00152647  comparesEqual

/* comparesEqual(QString const&, char const*) */

void comparesEqual(QString *param_1,char *param_2)

{
  long in_FS_OFFSET;
  char *local_38;
  QString *local_30;
  undefined8 local_28;
  undefined8 local_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = param_2;
  local_30 = param_1;
  QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_28,&local_38);
  comparesEqual(local_30,local_28,local_20);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001526a6  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, char const* const&) */

uint operator!=(QString *param_1,char **param_2)

{
  uint uVar1;
  
  uVar1 = comparesEqual(param_1,*param_2);
  return uVar1 ^ 1;
}



// ==== 001529c6  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QString const&) */

QString * operator+(QString *param_1,QString *param_2)

{
  QString *in_RDX;
  
  QString::QString(param_1,param_2);
  QString::operator+=(param_1,in_RDX);
  return param_1;
}



// ==== 00152a27  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString&&, QString const&) */

QString * operator+(QString *param_1,QString *param_2)

{
  QString *pQVar1;
  QString *in_RDX;
  
  pQVar1 = (QString *)QString::operator+=(param_2,in_RDX);
  QString::QString(param_1,pQVar1);
  return param_1;
}



// ==== 00152a6b  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, QChar) */

QString * operator+(QString *param_1,QString *param_2,undefined2 param_3)

{
  QString::QString(param_1,param_2);
  QString::operator+=(param_1,param_3);
  return param_1;
}



// ==== 00152acb  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString&&, QChar) */

QString * operator+(QString *param_1,QString *param_2,undefined2 param_3)

{
  QString *pQVar1;
  
  pQVar1 = (QString *)QString::operator+=(param_2,param_3);
  QString::QString(param_1,pQVar1);
  return param_1;
}



// ==== 00152b0e  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, char const*) */

QString * operator+(QString *param_1,char *param_2)

{
  long in_FS_OFFSET;
  char *local_50;
  char *local_48;
  QString *local_40;
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = param_2;
  local_40 = param_1;
  QString::QString(param_1,(QString *)param_2);
  QBasicUtf8StringView<false>::QBasicUtf8StringView<char_const*,true>
            ((QBasicUtf8StringView<false> *)&local_38,&local_50);
  QString::operator+=(local_40,local_38,local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}



// ==== 00152bbd  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QString&&, char const*) */

QString * operator+(QString *param_1,char *param_2)

{
  QString *pQVar1;
  char *in_RDX;
  
  pQVar1 = (QString *)QString::operator+=((QString *)param_2,in_RDX);
  QString::QString(param_1,pQVar1);
  return param_1;
}



// ==== 00152c01  swap

/* swap(QString&, QString&) */

void swap(QString *param_1,QString *param_2)

{
  QString::swap(param_1,param_2);
  return;
}



// ==== 00152da1  qHash

/* qHash(unsigned int, unsigned long) */

void qHash(uint param_1,ulong param_2)

{
  QHashPrivate::hash((ulong)param_1,param_2);
  return;
}



// ==== 00152dc4  qHash

/* qHash(int, unsigned long) */

void qHash(int param_1,ulong param_2)

{
  QHashPrivate::hash((long)param_1,param_2);
  return;
}



// ==== 00152de9  qHash

/* qHash(unsigned long long, unsigned long) */

void qHash(ulonglong param_1,ulong param_2)

{
  QHashPrivate::hash(param_1,param_2);
  return;
}



// ==== 00152e0e  qHash

/* qHash(QString const&, unsigned long) */

void qHash(QString *param_1,ulong param_2)

{
  long in_FS_OFFSET;
  undefined8 local_28;
  undefined8 local_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QStringView::QStringView<QString,true>((QStringView *)&local_28,param_1);
  qHash(local_28,local_20,param_2);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00152e89  qCountLeadingZeroBits

/* qCountLeadingZeroBits(unsigned long) */

void qCountLeadingZeroBits(ulong param_1)

{
  q20::countl_zero<unsigned_long>(param_1);
  return;
}



// ==== 00153377  comparesEqual

/* comparesEqual(QMetaType const&, QMetaType const&) */

bool comparesEqual(QMetaType *param_1,QMetaType *param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  if (*(long *)param_1 == *(long *)param_2) {
    bVar3 = true;
  }
  else if ((*(long *)param_1 == 0) || (*(long *)param_2 == 0)) {
    bVar3 = false;
  }
  else {
    iVar1 = QMetaType::id((int)param_1);
    iVar2 = QMetaType::id((int)param_2);
    bVar3 = iVar1 == iVar2;
  }
  return bVar3;
}



// ==== 001533f3  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMetaType const&, QMetaType const&) */

void operator==(QMetaType *param_1,QMetaType *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00154208  comparesEqual

/* comparesEqual(QVariant const&, QVariant const&) */

void comparesEqual(QVariant *param_1,QVariant *param_2)

{
  QVariant::equals(param_1);
  return;
}



// ==== 0015422d  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QVariant const&, QVariant const&) */

void operator==(QVariant *param_1,QVariant *param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00154290  swap

/* swap(QVariant&, QVariant&) */

void swap(QVariant *param_1,QVariant *param_2)

{
  QVariant::swap(param_1,param_2);
  return;
}



// ==== 001542b6  operator|

/* TEMPNAMEPLACEHOLDERVALUE(QIODeviceBase::OpenModeFlag, QIODeviceBase::OpenModeFlag) */

void operator|(undefined4 param_1,undefined4 param_2)

{
  long in_FS_OFFSET;
  QFlags<QIODeviceBase::OpenModeFlag> local_14 [4];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags(local_14,param_1);
  QFlags<QIODeviceBase::OpenModeFlag>::operator|(local_14,param_2);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00154398  compareThreeWay

/* compareThreeWay(QTime const&, QTime const&) */

void compareThreeWay(QTime *param_1,QTime *param_2)

{
  Qt::compareThreeWay<int,int,true,true>(*(int *)param_1,*(int *)param_2);
  return;
}



// ==== 001543bf  operator<

/* TEMPNAMEPLACEHOLDERVALUE(QTime const&, QTime const&) */

void operator<(QTime *param_1,QTime *param_2)

{
  long lVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = compareThreeWay(param_1,param_2);
  Qt::is_lt(uVar2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0015440e  operator>

/* TEMPNAMEPLACEHOLDERVALUE(QTime const&, QTime const&) */

void operator>(QTime *param_1,QTime *param_2)

{
  undefined4 uVar1;
  
  uVar1 = compareThreeWay(param_1,param_2);
  Qt::is_gt(uVar1);
  return;
}



// ==== 0015443a  operator>=

/* TEMPNAMEPLACEHOLDERVALUE(QTime const&, QTime const&) */

void operator>=(QTime *param_1,QTime *param_2)

{
  undefined4 uVar1;
  
  uVar1 = compareThreeWay(param_1,param_2);
  Qt::is_gteq(uVar1);
  return;
}



// ==== 001544d4  operator<

/* TEMPNAMEPLACEHOLDERVALUE(QDateTime const&, QDateTime const&) */

void operator<(QDateTime *param_1,QDateTime *param_2)

{
  long lVar1;
  undefined4 uVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = compareThreeWay(param_1,param_2);
  Qt::is_lt(uVar2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001546a3  s<(char)50>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::chrono::duration<long, std::ratio<1l, 1l> > std::literals::chrono_literals::operator""
   s<(char)50>() */

void s<(char)50>(void)

{
  std::literals::chrono_literals::
  __check_overflow<std::chrono::duration<long,std::ratio<1l,1l>>,(char)50>();
  return;
}



// ==== 00156bfd  qRed

/* qRed(unsigned int) */

uint qRed(uint param_1)

{
  return param_1 >> 0x10 & 0xff;
}



// ==== 00156c0f  qGreen

/* qGreen(unsigned int) */

uint qGreen(uint param_1)

{
  return param_1 >> 8 & 0xff;
}



// ==== 00156c21  qBlue

/* qBlue(unsigned int) */

uint qBlue(uint param_1)

{
  return param_1 & 0xff;
}



// ==== 001572c9  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QDBusObjectPath const&, QDBusObjectPath const&) */

undefined4 operator==(QDBusObjectPath *param_1,QDBusObjectPath *param_2)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusObjectPath::path();
  QDBusObjectPath::path();
  uVar1 = operator==(local_58,local_38);
  QString::~QString(local_58);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 00157359  operator<

/* TEMPNAMEPLACEHOLDERVALUE(QDBusObjectPath const&, QDBusObjectPath const&) */

undefined4 operator<(QDBusObjectPath *param_1,QDBusObjectPath *param_2)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusObjectPath::path();
  QDBusObjectPath::path();
  uVar1 = operator<(local_58,local_38);
  QString::~QString(local_58);
  QString::~QString(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 0015742f  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QDBusVariant const&, QDBusVariant const&) */

undefined4 operator==(QDBusVariant *param_1,QDBusVariant *param_2)

{
  undefined4 uVar1;
  long in_FS_OFFSET;
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusVariant::variant();
  QDBusVariant::variant();
  uVar1 = operator==(local_68,local_48);
  QVariant::~QVariant(local_68);
  QVariant::~QVariant(local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar1;
}



// ==== 00157500  qRegisterNormalizedMetaType<QDBusVariant>

/* int qRegisterNormalizedMetaType<QDBusVariant>(QByteArray const&) */

int qRegisterNormalizedMetaType<QDBusVariant>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaType_QDBusVariant(param_1);
  return iVar1;
}



// ==== 001576ae  qRegisterNormalizedMetaType<QDBusObjectPath>

/* int qRegisterNormalizedMetaType<QDBusObjectPath>(QByteArray const&) */

int qRegisterNormalizedMetaType<QDBusObjectPath>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaType_QDBusObjectPath(param_1);
  return iVar1;
}



// ==== 001578a0  qRegisterNormalizedMetaType<QDBusArgument>

/* int qRegisterNormalizedMetaType<QDBusArgument>(QByteArray const&) */

int qRegisterNormalizedMetaType<QDBusArgument>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaType_QDBusArgument(param_1);
  return iVar1;
}



// ==== 0015a862  qt_getEnumMetaObject

/* qt_getEnumMetaObject(QProcess::ExitStatus) */

undefined8 * qt_getEnumMetaObject(void)

{
  return &QProcess::staticMetaObject;
}



// ==== 0015a872  qt_getEnumName

/* qt_getEnumName(QProcess::ExitStatus) */

char * qt_getEnumName(void)

{
  return "ExitStatus";
}



// ==== 00163f94  qMax<double>

/* double const& qMax<double>(double const&, double const&) */

double * qMax<double>(double *param_1,double *param_2)

{
  if (*param_1 < *param_2) {
    param_1 = param_2;
  }
  return param_1;
}



// ==== 00163fc2  qMin<double>

/* double const& qMin<double>(double const&, double const&) */

double * qMin<double>(double *param_1,double *param_2)

{
  if (*param_1 < *param_2) {
    param_2 = param_1;
  }
  return param_2;
}



// ==== 00166f5c  qAbs<int>

/* int qAbs<int>(int const&) */

int qAbs<int>(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -*param_1;
  iVar1 = *param_1;
  if (-1 < iVar2) {
    iVar1 = iVar2;
  }
  return iVar1;
}



// ==== 00168ba9  qMin<int>

/* int const& qMin<int>(int const&, int const&) */

int * qMin<int>(int *param_1,int *param_2)

{
  if (*param_1 < *param_2) {
    param_2 = param_1;
  }
  return param_2;
}



// ==== 001751dc  qMax<float>

/* float const& qMax<float>(float const&, float const&) */

float * qMax<float>(float *param_1,float *param_2)

{
  if (*param_1 < *param_2) {
    param_1 = param_2;
  }
  return param_1;
}



// ==== 00176f5b  qobject_cast<QWindow*>

/* QWindow* qobject_cast<QWindow*>(QObject*) */

QWindow * qobject_cast<QWindow*>(QObject *param_1)

{
  bool bVar1;
  char cVar2;
  
  if ((param_1 == (QObject *)0x0) || (cVar2 = QObject::isWindowType(param_1), cVar2 != '\x01')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    param_1 = (QObject *)0x0;
  }
  return (QWindow *)param_1;
}



// ==== 00182c67  comparesEqual

/* comparesEqual(QJsonArray::const_iterator const&, QJsonArray::const_iterator const&) */

void comparesEqual(const_iterator *param_1,const_iterator *param_2)

{
  QJsonArray::const_iterator::comparesEqual_helper(param_1,param_2);
  return;
}



// ==== 00182c8c  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QJsonArray::const_iterator const&, QJsonArray::const_iterator const&) */

uint operator!=(const_iterator *param_1,const_iterator *param_2)

{
  uint uVar1;
  
  uVar1 = comparesEqual(param_1,param_2);
  return uVar1 ^ 1;
}



// ==== 001a4091  qMax<long_long>

/* long long const& qMax<long long>(long long const&, long long const&) */

longlong * qMax<long_long>(longlong *param_1,longlong *param_2)

{
  if (*param_1 < *param_2) {
    param_1 = param_2;
  }
  return param_1;
}



// ==== 001a4118  qToByteArrayViewIgnoringNull<QByteArray,true>

/* QByteArrayView qToByteArrayViewIgnoringNull<QByteArray, true>(QByteArray const&) */

undefined8 qToByteArrayViewIgnoringNull<QByteArray,true>(QByteArray *param_1)

{
  longlong lVar1;
  char *pcVar2;
  long in_FS_OFFSET;
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QByteArray::size(param_1);
  pcVar2 = (char *)QByteArray::begin(param_1);
  QByteArrayView::QByteArrayView<char,true>((QByteArrayView *)local_38,pcVar2,lVar1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_38[0];
}



// ==== 001a4925  qToStringViewIgnoringNull<QString,true>

/* QStringView qToStringViewIgnoringNull<QString, true>(QString const&) */

undefined8 qToStringViewIgnoringNull<QString,true>(QString *param_1)

{
  longlong lVar1;
  QChar *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  lVar1 = QString::size(param_1);
  pQVar2 = (QChar *)QString::begin(param_1);
  QStringView::QStringView<QChar,true>((QStringView *)local_38,pQVar2,lVar1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_38[0];
}



// ==== 001a6104  qMax<int>

/* int const& qMax<int>(int const&, int const&) */

int * qMax<int>(int *param_1,int *param_2)

{
  if (*param_1 < *param_2) {
    param_1 = param_2;
  }
  return param_1;
}



// ==== 001a612c  qBound<double>

/* double const& qBound<double>(double const&, double const&, double const&) */

double * qBound<double>(double *param_1,double *param_2,double *param_3)

{
  double *pdVar1;
  
  pdVar1 = qMin<double>(param_3,param_2);
  pdVar1 = qMax<double>(param_1,pdVar1);
  return pdVar1;
}



// ==== 001a6194  qt_ptr_swap<QImageData>

/* void qt_ptr_swap<QImageData>(QImageData*&, QImageData*&) */

void qt_ptr_swap<QImageData>(QImageData **param_1,QImageData **param_2)

{
  QImageData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001a6308  qRegisterMetaType<QDBusVariant>

/* int qRegisterMetaType<QDBusVariant>(char const*) */

int qRegisterMetaType<QDBusVariant>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QDBusVariant>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001a63d8  qRegisterMetaType<QDBusObjectPath>

/* int qRegisterMetaType<QDBusObjectPath>(char const*) */

int qRegisterMetaType<QDBusObjectPath>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QDBusObjectPath>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001a64a8  qRegisterMetaType<QDBusArgument>

/* int qRegisterMetaType<QDBusArgument>(char const*) */

int qRegisterMetaType<QDBusArgument>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QDBusArgument>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001a8417  qt_ptr_swap<QCborContainerPrivate>

/* void qt_ptr_swap<QCborContainerPrivate>(QCborContainerPrivate*&, QCborContainerPrivate*&) */

void qt_ptr_swap<QCborContainerPrivate>
               (QCborContainerPrivate **param_1,QCborContainerPrivate **param_2)

{
  QCborContainerPrivate *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001a8d0a  qRegisterNormalizedMetaType<QMap<QString,QMap<QString,QVariant>>>

/* int qRegisterNormalizedMetaType<QMap<QString, QMap<QString, QVariant> > >(QByteArray const&) */

int qRegisterNormalizedMetaType<QMap<QString,QMap<QString,QVariant>>>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QMap<QString,QMap<QString,QVariant>>>(param_1);
  return iVar1;
}



// ==== 001a8d24  qRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>

/* int qRegisterMetaType<QMap<QString, QMap<QString, QVariant> > >(char const*) */

int qRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QMap<QString,QMap<QString,QVariant>>>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001a8dba  qRegisterNormalizedMetaType<QMap<QString,double>>

/* int qRegisterNormalizedMetaType<QMap<QString, double> >(QByteArray const&) */

int qRegisterNormalizedMetaType<QMap<QString,double>>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QMap<QString,double>>(param_1);
  return iVar1;
}



// ==== 001a8dd4  qRegisterMetaType<QMap<QString,double>>

/* int qRegisterMetaType<QMap<QString, double> >(char const*) */

int qRegisterMetaType<QMap<QString,double>>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QMap<QString,double>>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001a8e6a  qRegisterNormalizedMetaType<QMap<QString,unsigned_int>>

/* int qRegisterNormalizedMetaType<QMap<QString, unsigned int> >(QByteArray const&) */

int qRegisterNormalizedMetaType<QMap<QString,unsigned_int>>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QMap<QString,unsigned_int>>(param_1);
  return iVar1;
}



// ==== 001a8e84  qRegisterMetaType<QMap<QString,unsigned_int>>

/* int qRegisterMetaType<QMap<QString, unsigned int> >(char const*) */

int qRegisterMetaType<QMap<QString,unsigned_int>>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QMap<QString,unsigned_int>>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 001aac51  qBound<float>

/* float const& qBound<float>(float const&, float const&, float const&) */

float * qBound<float>(float *param_1,float *param_2,float *param_3)

{
  float *pfVar1;
  
  pfVar1 = qMin<float>(param_3,param_2);
  pfVar1 = qMax<float>(param_1,pfVar1);
  return pfVar1;
}



// ==== 001aadba  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QVariant>::const_iterator const&, QMap<QString,
   QVariant>::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001ac06e  qBound<int>

/* int const& qBound<int>(int const&, int const&, int const&) */

int * qBound<int>(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  
  piVar1 = qMin<int>(param_3,param_2);
  piVar1 = qMax<int>(param_1,piVar1);
  return piVar1;
}



// ==== 001accac  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, bool>::const_iterator const&, QMap<QString,
   bool>::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001ae7b3  qt_ptr_swap<QTypedArrayData<char>>

/* void qt_ptr_swap<QTypedArrayData<char> >(QTypedArrayData<char>*&, QTypedArrayData<char>*&) */

void qt_ptr_swap<QTypedArrayData<char>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001ae7e6  qt_ptr_swap<char>

/* void qt_ptr_swap<char>(char*&, char*&) */

void qt_ptr_swap<char>(char **param_1,char **param_2)

{
  char *pcVar1;
  
  pcVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pcVar1;
  return;
}



// ==== 001ae9f3  qt_ptr_swap<QTypedArrayData<char16_t>>

/* void qt_ptr_swap<QTypedArrayData<char16_t> >(QTypedArrayData<char16_t>*&,
   QTypedArrayData<char16_t>*&) */

void qt_ptr_swap<QTypedArrayData<char16_t>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001aea26  qt_ptr_swap<char16_t>

/* void qt_ptr_swap<char16_t>(char16_t*&, char16_t*&) */

void qt_ptr_swap<char16_t>(wchar16 **param_1,wchar16 **param_2)

{
  wchar16 *pwVar1;
  
  pwVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pwVar1;
  return;
}



// ==== 001b01b6  qAddOverflow<int>

/* std::enable_if<is_signed_v<int>, bool>::type qAddOverflow<int>(int, int, int*) */

bool qAddOverflow<int>(int param_1,int param_2,int *param_3)

{
  *param_3 = param_2 + param_1;
  return SCARRY4(param_2,param_1);
}



// ==== 001b01e7  qSubOverflow<int>

/* std::enable_if<is_signed_v<int>, bool>::type qSubOverflow<int>(int, int, int*) */

bool qSubOverflow<int>(int param_1,int param_2,int *param_3)

{
  *param_3 = param_1 - param_2;
  return SBORROW4(param_1,param_2);
}



// ==== 001b0639  qvariant_cast<QDBusArgument>

/* QDBusArgument qvariant_cast<QDBusArgument>(QVariant const&) */

QVariant * qvariant_cast<QDBusArgument>(QVariant *param_1)

{
  char cVar1;
  QDBusArgument *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusArgument>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QDBusArgument>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QDBusArgument>(in_RSI);
    QDBusArgument::QDBusArgument((QDBusArgument *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001b1bfb  qRegisterNormalizedMetaTypeImplementation<QMap<QString,QMap<QString,QVariant>>>

/* int qRegisterNormalizedMetaTypeImplementation<QMap<QString, QMap<QString, QVariant> >
   >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QMap<QString,QMap<QString,QVariant>>>
              (QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,QMap<QString,QVariant>>>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,QMap<QString,QVariant>>,false>::
  registerConverter();
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,QMap<QString,QVariant>>,false>::
  registerMutableView();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,QMap<QString,QVariant>>,true>::
  registerConverter();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,QMap<QString,QVariant>>,true>::
  registerMutableView();
  QtPrivate::IsPair<QMap<QString,QMap<QString,QVariant>>>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QMap<QString,QMap<QString,QVariant>>,void>::
  registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QMap<QString,QMap<QString,QVariant>>>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 001b1cb8  qRegisterNormalizedMetaTypeImplementation<QMap<QString,double>>

/* int qRegisterNormalizedMetaTypeImplementation<QMap<QString, double> >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QMap<QString,double>>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,double>>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,double>,false>::registerConverter
            ();
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,double>,false>::
  registerMutableView();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,double>,true>::registerConverter();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,double>,true>::registerMutableView();
  QtPrivate::IsPair<QMap<QString,double>>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QMap<QString,double>,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QMap<QString,double>>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 001b1d75  qRegisterNormalizedMetaTypeImplementation<QMap<QString,unsigned_int>>

/* int qRegisterNormalizedMetaTypeImplementation<QMap<QString, unsigned int> >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QMap<QString,unsigned_int>>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,unsigned_int>>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,unsigned_int>,false>::
  registerConverter();
  QtPrivate::SequentialContainerTransformationHelper<QMap<QString,unsigned_int>,false>::
  registerMutableView();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,unsigned_int>,true>::registerConverter();
  QtPrivate::AssociativeKeyTypeIsMetaType<QMap<QString,unsigned_int>,true>::registerMutableView();
  QtPrivate::IsPair<QMap<QString,unsigned_int>>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QMap<QString,unsigned_int>,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QMap<QString,unsigned_int>>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 001b1f88  operator==

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QMap<QString, QVariant> > const&, QMap<QString,
   QMap<QString, QVariant> > const&) */

bool operator==(QMap *param_1,QMap *param_2)

{
  long lVar1;
  bool bVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = comparesEqual<QString,QMap<QString,QVariant>,true>(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}



// ==== 001b1fd0  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QMap<QString,
   QVariant> >, QString>, QTypeTraits::has_ostream_operator<QDebug, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QMap<QString, QVariant> >, QMap<QString, QVariant>
   >, QTypeTraits::has_ostream_operator<QDebug, QMap<QString, QVariant>, void> > >, QDebug>::type
   TEMPNAMEPLACEHOLDERVALUE(QDebug, QMap<QString, QMap<QString, QVariant> > const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printAssociativeContainer<QMap<QString,QMap<QString,QVariant>>>
            (param_1,local_30,&LAB_002a3d7d_1,param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001b208c  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QMap<QString,
   QVariant> >, QString>, QTypeTraits::has_ostream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QMap<QString, QVariant> >, QMap<QString, QVariant>
   >, QTypeTraits::has_ostream_operator<QDataStream, QMap<QString, QVariant>, void> > >,
   QDataStream&>::type TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, QMap<QString, QVariant>
   > const&) */

void operator<<(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::writeAssociativeContainer<QMap<QString,QMap<QString,QVariant>>>(param_1,param_2);
  return;
}



// ==== 001b20b1  operator>>

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QMap<QString,
   QVariant> >, QString>, QTypeTraits::has_istream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QMap<QString, QVariant> >, QMap<QString, QVariant>
   >, QTypeTraits::has_istream_operator<QDataStream, QMap<QString, QVariant>, void> > >,
   QDataStream&>::type TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, QMap<QString, QVariant>
   >&) */

void operator>>(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::readAssociativeContainer<QMap<QString,QMap<QString,QVariant>>>(param_1,param_2);
  return;
}



// ==== 001b21d0  operator==

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QString, double> const&, QMap<QString, double> const&) */

bool operator==(QMap *param_1,QMap *param_2)

{
  long lVar1;
  bool bVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = comparesEqual<QString,double,true>(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}



// ==== 001b2218  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, double>, QString>,
   QTypeTraits::has_ostream_operator<QDebug, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, double>, double>,
   QTypeTraits::has_ostream_operator<QDebug, double, void> > >, QDebug>::type
   TEMPNAMEPLACEHOLDERVALUE(QDebug, QMap<QString, double> const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printAssociativeContainer<QMap<QString,double>>
            (param_1,local_30,&LAB_002a3d7d_1,param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001b22d4  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, double>, QString>,
   QTypeTraits::has_ostream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, double>, double>,
   QTypeTraits::has_ostream_operator<QDataStream, double, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, double> const&) */

void operator<<(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::writeAssociativeContainer<QMap<QString,double>>(param_1,param_2);
  return;
}



// ==== 001b22f9  operator>>

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, double>, QString>,
   QTypeTraits::has_istream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, double>, double>,
   QTypeTraits::has_istream_operator<QDataStream, double, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, double>&) */

void operator>>(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::readAssociativeContainer<QMap<QString,double>>(param_1,param_2);
  return;
}



// ==== 001b2418  operator==

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QString, unsigned int> const&, QMap<QString, unsigned int>
   const&) */

bool operator==(QMap *param_1,QMap *param_2)

{
  long lVar1;
  bool bVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = comparesEqual<QString,unsigned_int,true>(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}



// ==== 001b2460  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, unsigned int>,
   QString>, QTypeTraits::has_ostream_operator<QDebug, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, unsigned int>, unsigned int>,
   QTypeTraits::has_ostream_operator<QDebug, unsigned int, void> > >, QDebug>::type
   TEMPNAMEPLACEHOLDERVALUE(QDebug, QMap<QString, unsigned int> const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printAssociativeContainer<QMap<QString,unsigned_int>>
            (param_1,local_30,&LAB_002a3d7d_1,param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001b251c  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, unsigned int>,
   QString>, QTypeTraits::has_ostream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, unsigned int>, unsigned int>,
   QTypeTraits::has_ostream_operator<QDataStream, unsigned int, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, unsigned int> const&) */

void operator<<(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::writeAssociativeContainer<QMap<QString,unsigned_int>>(param_1,param_2);
  return;
}



// ==== 001b2541  operator>>

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, unsigned int>,
   QString>, QTypeTraits::has_istream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, unsigned int>, unsigned int>,
   QTypeTraits::has_istream_operator<QDataStream, unsigned int, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, unsigned int>&) */

void operator>>(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::readAssociativeContainer<QMap<QString,unsigned_int>>(param_1,param_2);
  return;
}



// ==== 001b3226  qMin<float>

/* float const& qMin<float>(float const&, float const&) */

float * qMin<float>(float *param_1,float *param_2)

{
  if (*param_1 < *param_2) {
    param_2 = param_1;
  }
  return param_2;
}



// ==== 001b6081  qt_ptr_swap<QTypedArrayData<AppMenuModel::AppEntry>>

/* void qt_ptr_swap<QTypedArrayData<AppMenuModel::AppEntry>
   >(QTypedArrayData<AppMenuModel::AppEntry>*&, QTypedArrayData<AppMenuModel::AppEntry>*&) */

void qt_ptr_swap<QTypedArrayData<AppMenuModel::AppEntry>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001b60b4  qt_ptr_swap<AppMenuModel::AppEntry>

/* void qt_ptr_swap<AppMenuModel::AppEntry>(AppMenuModel::AppEntry*&, AppMenuModel::AppEntry*&) */

void qt_ptr_swap<AppMenuModel::AppEntry>(AppEntry **param_1,AppEntry **param_2)

{
  AppEntry *pAVar1;
  
  pAVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pAVar1;
  return;
}



// ==== 001b788b  qt_ptr_swap<QTypedArrayData<QString>>

/* void qt_ptr_swap<QTypedArrayData<QString> >(QTypedArrayData<QString>*&,
   QTypedArrayData<QString>*&) */

void qt_ptr_swap<QTypedArrayData<QString>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001b78be  qt_ptr_swap<QString>

/* void qt_ptr_swap<QString>(QString*&, QString*&) */

void qt_ptr_swap<QString>(QString **param_1,QString **param_2)

{
  QString *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001b78f1  qt_ptr_swap<QTypedArrayData<QVariant>>

/* void qt_ptr_swap<QTypedArrayData<QVariant> >(QTypedArrayData<QVariant>*&,
   QTypedArrayData<QVariant>*&) */

void qt_ptr_swap<QTypedArrayData<QVariant>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001b7924  qt_ptr_swap<QVariant>

/* void qt_ptr_swap<QVariant>(QVariant*&, QVariant*&) */

void qt_ptr_swap<QVariant>(QVariant **param_1,QVariant **param_2)

{
  QVariant *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001b9177  comparesEqual<QString,QMap<QString,QVariant>,true>

/* bool comparesEqual<QString, QMap<QString, QVariant>, true>(QMap<QString, QMap<QString, QVariant>
   > const&, QMap<QString, QMap<QString, QVariant> > const&) */

bool comparesEqual<QString,QMap<QString,QVariant>,true>(QMap *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  cVar1 = QtPrivate::operator==
                    ((QExplicitlySharedDataPointerV2 *)param_1,
                     (QExplicitlySharedDataPointerV2 *)param_2);
  if (cVar1 == '\0') {
    bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                      ((QExplicitlySharedDataPointerV2 *)param_1);
    if (bVar2) {
      bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                        ((QExplicitlySharedDataPointerV2 *)param_2);
      if (bVar2) {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                              *)param_2);
        lVar4 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                              *)param_1);
        bVar2 = std::operator==((map *)(lVar4 + 8),(map *)(lVar3 + 8));
      }
      else {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
                              *)param_1);
        cVar1 = std::
                map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>
                ::empty((map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>
                         *)(lVar3 + 8));
        bVar2 = cVar1 != '\0';
      }
    }
    else {
      bVar2 = operator==(param_2,param_1);
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}



// ==== 001b9813  comparesEqual<QString,double,true>

/* bool comparesEqual<QString, double, true>(QMap<QString, double> const&, QMap<QString, double>
   const&) */

bool comparesEqual<QString,double,true>(QMap *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  cVar1 = QtPrivate::operator==
                    ((QExplicitlySharedDataPointerV2 *)param_1,
                     (QExplicitlySharedDataPointerV2 *)param_2);
  if (cVar1 == '\0') {
    bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                      ((QExplicitlySharedDataPointerV2 *)param_1);
    if (bVar2) {
      bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                        ((QExplicitlySharedDataPointerV2 *)param_2);
      if (bVar2) {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                              *)param_2);
        lVar4 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                              *)param_1);
        bVar2 = std::operator==((map *)(lVar4 + 8),(map *)(lVar3 + 8));
      }
      else {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
                              *)param_1);
        cVar1 = std::
                map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>
                ::empty((map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>
                         *)(lVar3 + 8));
        bVar2 = cVar1 != '\0';
      }
    }
    else {
      bVar2 = operator==(param_2,param_1);
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}



// ==== 001b9e2d  comparesEqual<QString,unsigned_int,true>

/* bool comparesEqual<QString, unsigned int, true>(QMap<QString, unsigned int> const&, QMap<QString,
   unsigned int> const&) */

bool comparesEqual<QString,unsigned_int,true>(QMap *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  cVar1 = QtPrivate::operator==
                    ((QExplicitlySharedDataPointerV2 *)param_1,
                     (QExplicitlySharedDataPointerV2 *)param_2);
  if (cVar1 == '\0') {
    bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                      ((QExplicitlySharedDataPointerV2 *)param_1);
    if (bVar2) {
      bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                        ((QExplicitlySharedDataPointerV2 *)param_2);
      if (bVar2) {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                              *)param_2);
        lVar4 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                              *)param_1);
        bVar2 = std::operator==((map *)(lVar4 + 8),(map *)(lVar3 + 8));
      }
      else {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
                              *)param_1);
        cVar1 = std::
                map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>
                ::empty((map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>
                         *)(lVar3 + 8));
        bVar2 = cVar1 != '\0';
      }
    }
    else {
      bVar2 = operator==(param_2,param_1);
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}



// ==== 001c12f4  qdbus_cast<QDBusObjectPath>

/* QDBusObjectPath qdbus_cast<QDBusObjectPath>(QVariant const&) */

QVariant * qdbus_cast<QDBusObjectPath>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QDBusObjectPath>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QDBusObjectPath>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001c2c61  qt_ptr_swap<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>

/* void qt_ptr_swap<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > > >(QMapData<std::map<QString, QVariant,
   std::less<QString>, std::allocator<std::pair<QString const, QVariant> > > >*&,
   QMapData<std::map<QString, QVariant, std::less<QString>, std::allocator<std::pair<QString const,
   QVariant> > > >*&) */

void qt_ptr_swap<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001c368c  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QMap<QString, QVariant> >::const_iterator const&,
   QMap<QString, QMap<QString, QVariant> >::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001c3708  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QVariant>, QString>,
   QTypeTraits::has_ostream_operator<QDebug, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QVariant>, QVariant>,
   QTypeTraits::has_ostream_operator<QDebug, QVariant, void> > >, QDebug>::type
   TEMPNAMEPLACEHOLDERVALUE(QDebug, QMap<QString, QVariant> const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printAssociativeContainer<QMap<QString,QVariant>>
            (param_1,local_30,&LAB_002a3d7d_1,param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001c3801  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QVariant>, QString>,
   QTypeTraits::has_ostream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QVariant>, QVariant>,
   QTypeTraits::has_ostream_operator<QDataStream, QVariant, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, QVariant> const&) */

void operator<<(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::writeAssociativeContainer<QMap<QString,QVariant>>(param_1,param_2);
  return;
}



// ==== 001c3888  operator>>

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QString, QVariant>, QString>,
   QTypeTraits::has_istream_operator<QDataStream, QString, void> >,
   std::disjunction<std::is_base_of<QMap<QString, QVariant>, QVariant>,
   QTypeTraits::has_istream_operator<QDataStream, QVariant, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QMap<QString, QVariant>&) */

void operator>>(QDataStream *param_1,QMap *param_2)

{
  QtPrivate::readAssociativeContainer<QMap<QString,QVariant>>(param_1,param_2);
  return;
}



// ==== 001c3b32  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, double>::const_iterator const&, QMap<QString,
   double>::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001c3ed2  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, unsigned int>::const_iterator const&, QMap<QString,
   unsigned int>::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001c85e7  qRegisterNormalizedMetaType<QProcess::ExitStatus>

/* int qRegisterNormalizedMetaType<QProcess::ExitStatus>(QByteArray const&) */

int qRegisterNormalizedMetaType<QProcess::ExitStatus>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QProcess::ExitStatus>(param_1);
  return iVar1;
}



// ==== 001cb9da  qAbs<long>

/* long qAbs<long>(long const&) */

long qAbs<long>(long *param_1)

{
  long lVar1;
  long lVar2;
  
  lVar2 = -*param_1;
  lVar1 = *param_1;
  if (-1 < lVar2) {
    lVar1 = lVar2;
  }
  return lVar1;
}



// ==== 001cba80  qdbus_cast<QDBusObjectPath>

/* QDBusObjectPath qdbus_cast<QDBusObjectPath>(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QDBusObjectPath>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)param_1);
  QDBusArgument::operator>>(in_RSI,(QDBusObjectPath *)param_1);
  return param_1;
}



// ==== 001cbad6  qvariant_cast<QDBusObjectPath>

/* QDBusObjectPath qvariant_cast<QDBusObjectPath>(QVariant const&) */

QVariant * qvariant_cast<QDBusObjectPath>(QVariant *param_1)

{
  char cVar1;
  QDBusObjectPath *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusObjectPath>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QDBusObjectPath>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QDBusObjectPath>(in_RSI);
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001cbb78  qRegisterNormalizedMetaType<QDBusPendingCallWatcher*>

/* int qRegisterNormalizedMetaType<QDBusPendingCallWatcher*>(QByteArray const&) */

int qRegisterNormalizedMetaType<QDBusPendingCallWatcher*>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QDBusPendingCallWatcher*>(param_1);
  return iVar1;
}



// ==== 001cd0fc  qHashEquals<unsigned_int>

/* bool qHashEquals<unsigned int>(unsigned int const&, unsigned int const&) */

bool qHashEquals<unsigned_int>(uint *param_1,uint *param_2)

{
  return *param_1 == *param_2;
}



// ==== 001d18c4  qHashEquals<QString>

/* bool qHashEquals<QString>(QString const&, QString const&) */

bool qHashEquals<QString>(QString *param_1,QString *param_2)

{
  undefined1 uVar1;
  
  uVar1 = operator==(param_1,param_2);
  return (bool)uVar1;
}



// ==== 001d4974  qRegisterNormalizedMetaTypeImplementation<QProcess::ExitStatus>

/* int qRegisterNormalizedMetaTypeImplementation<QProcess::ExitStatus>(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QProcess::ExitStatus>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QProcess::ExitStatus>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialContainerTransformationHelper<QProcess::ExitStatus,false>::registerConverter
            ();
  QtPrivate::SequentialContainerTransformationHelper<QProcess::ExitStatus,false>::
  registerMutableView();
  QtPrivate::AssociativeContainerTransformationHelper<QProcess::ExitStatus,false>::registerConverter
            ();
  QtPrivate::AssociativeContainerTransformationHelper<QProcess::ExitStatus,false>::
  registerMutableView();
  QtPrivate::IsPair<QProcess::ExitStatus>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QProcess::ExitStatus,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QProcess::ExitStatus>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 001d5e32  qMax<int,long_long>

/* QTypeTraits::detail::Promoted<int, long long,
   std::enable_if<(((((((is_arithmetic_v<int>)&&(is_arithmetic_v<long
   long>))&&((is_floating_point_v<int>)==(is_floating_point_v<long
   long>)))&&((is_signed_v<int>)==(is_signed_v<long long>)))&&(!(is_same_v<int,
   bool>)))&&(!(is_same_v<long long, bool>)))&&(!(is_same_v<int, char>)))&&(!(is_same_v<long long,
   char>)), void>::type>::type qMax<int, long long>(int const&, long long const&) */

long qMax<int,long_long>(int *param_1,longlong *param_2)

{
  long lVar1;
  
  lVar1 = (long)*param_1;
  if (lVar1 < *param_2) {
    lVar1 = *param_2;
  }
  return lVar1;
}



// ==== 001d6bfe  qRegisterNormalizedMetaTypeImplementation<QDBusPendingCallWatcher*>

/* int qRegisterNormalizedMetaTypeImplementation<QDBusPendingCallWatcher*>(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QDBusPendingCallWatcher*>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusPendingCallWatcher*>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialContainerTransformationHelper<QDBusPendingCallWatcher*,false>::
  registerConverter();
  QtPrivate::SequentialContainerTransformationHelper<QDBusPendingCallWatcher*,false>::
  registerMutableView();
  QtPrivate::AssociativeContainerTransformationHelper<QDBusPendingCallWatcher*,false>::
  registerConverter();
  QtPrivate::AssociativeContainerTransformationHelper<QDBusPendingCallWatcher*,false>::
  registerMutableView();
  QtPrivate::IsPair<QDBusPendingCallWatcher*>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QDBusPendingCallWatcher*,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QDBusPendingCallWatcher*>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 001d6f7d  qt_ptr_swap<QTypedArrayData<QFileInfo>>

/* void qt_ptr_swap<QTypedArrayData<QFileInfo> >(QTypedArrayData<QFileInfo>*&,
   QTypedArrayData<QFileInfo>*&) */

void qt_ptr_swap<QTypedArrayData<QFileInfo>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001d6fb0  qt_ptr_swap<QFileInfo>

/* void qt_ptr_swap<QFileInfo>(QFileInfo*&, QFileInfo*&) */

void qt_ptr_swap<QFileInfo>(QFileInfo **param_1,QFileInfo **param_2)

{
  QFileInfo *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001d88bf  qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QMap<QString, QMap<QString, QVariant> >,
   QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,
   QMap<QString, QVariant> >, QIterable<QMetaAssociation> >(std::function<bool (void const*,
   void*)>, QMetaType, QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QMap<QString,
   QMap<QString, QVariant> >, QIterable<QMetaAssociation> >(std::function<bool (void const*,
   void*)>, QMetaType, QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001d8a69  qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QMap<QString, QMap<QString, QVariant>
   >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,
   QMap<QString, QVariant> >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>,
   QMetaType, QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QMap<QString,
   QMap<QString, QVariant> >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>,
   QMetaType, QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,QMap<QString,QVariant>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001d98b9  qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QMap<QString, double>,
   QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,
   double>, QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QMap<QString, double>,
   QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001d9a63  qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QMap<QString, double>,
   QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,
   double>, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QMap<QString, double>,
   QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,double>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001da891  qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QMap<QString, unsigned int>,
   QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,
   unsigned int>, QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QMap<QString, unsigned int>,
   QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001daa3b  qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QMap<QString, unsigned int>,
   QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,
   unsigned int>, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QMap<QString, unsigned int>,
   QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QString,unsigned_int>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 001dadb4  operator<<

/* std::enable_if<is_same_v<QVariant, QVariant>, QDebug>::type TEMPNAMEPLACEHOLDERVALUE(QDebug
   const&, QVariant const&) */

QDebug * operator<<(QDebug *param_1,QVariant *param_2)

{
  undefined8 in_RDX;
  long in_FS_OFFSET;
  QDebug local_28 [8];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDebug::QDebug(local_28,(QDebug *)param_2);
  QVariant::qdebugHelper(param_1,in_RDX,local_28);
  QDebug::~QDebug(local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001dc38a  qMax<unsigned_long>

/* unsigned long const& qMax<unsigned long>(unsigned long const&, unsigned long const&) */

ulong * qMax<unsigned_long>(ulong *param_1,ulong *param_2)

{
  if (*param_1 < *param_2) {
    param_1 = param_2;
  }
  return param_1;
}



// ==== 001dc7aa  qt_ptr_swap<QTypedArrayData<NCDEEngine::Sample>>

/* void qt_ptr_swap<QTypedArrayData<NCDEEngine::Sample> >(QTypedArrayData<NCDEEngine::Sample>*&,
   QTypedArrayData<NCDEEngine::Sample>*&) */

void qt_ptr_swap<QTypedArrayData<NCDEEngine::Sample>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001dc7dd  qt_ptr_swap<NCDEEngine::Sample>

/* void qt_ptr_swap<NCDEEngine::Sample>(NCDEEngine::Sample*&, NCDEEngine::Sample*&) */

void qt_ptr_swap<NCDEEngine::Sample>(Sample **param_1,Sample **param_2)

{
  Sample *pSVar1;
  
  pSVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pSVar1;
  return;
}



// ==== 001dec52  qt_ptr_swap<QTypedArrayData<NCDEWindowManager::WindowEntry>>

/* void qt_ptr_swap<QTypedArrayData<NCDEWindowManager::WindowEntry>
   >(QTypedArrayData<NCDEWindowManager::WindowEntry>*&,
   QTypedArrayData<NCDEWindowManager::WindowEntry>*&) */

void qt_ptr_swap<QTypedArrayData<NCDEWindowManager::WindowEntry>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001dec85  qt_ptr_swap<NCDEWindowManager::WindowEntry>

/* void qt_ptr_swap<NCDEWindowManager::WindowEntry>(NCDEWindowManager::WindowEntry*&,
   NCDEWindowManager::WindowEntry*&) */

void qt_ptr_swap<NCDEWindowManager::WindowEntry>(WindowEntry **param_1,WindowEntry **param_2)

{
  WindowEntry *pWVar1;
  
  pWVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pWVar1;
  return;
}



// ==== 001df24f  qt_ptr_swap<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>>

/* void qt_ptr_swap<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > > >(QMapData<std::map<QString, bool,
   std::less<QString>, std::allocator<std::pair<QString const, bool> > > >*&,
   QMapData<std::map<QString, bool, std::less<QString>, std::allocator<std::pair<QString const,
   bool> > > >*&) */

void qt_ptr_swap<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001dfa34  qHash<QWindow>

/* unsigned long qHash<QWindow>(QWindow*, unsigned long) */

ulong qHash<QWindow>(QWindow *param_1,ulong param_2)

{
  ulong uVar1;
  
  uVar1 = qHash((ulonglong)param_1,0);
  return uVar1 ^ param_2;
}



// ==== 001dfafe  qHashEquals<QWindow*>

/* bool qHashEquals<QWindow*>(QWindow* const&, QWindow* const&) */

bool qHashEquals<QWindow*>(QWindow **param_1,QWindow **param_2)

{
  return *param_1 == *param_2;
}



// ==== 001e18cb  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QMap<QString, QVariant> >::iterator const&, QMap<QString,
   QMap<QString, QVariant> >::iterator const&) */

void operator==(iterator *param_1,iterator *param_2)

{
  std::operator==((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001e18f0  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QMap<QString, QVariant> >::const_iterator const&,
   QMap<QString, QMap<QString, QVariant> >::const_iterator const&) */

void operator==(const_iterator *param_1,const_iterator *param_2)

{
  std::operator==((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001e247d  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, double>::iterator const&, QMap<QString, double>::iterator
   const&) */

void operator==(iterator *param_1,iterator *param_2)

{
  std::operator==((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001e24a2  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, double>::const_iterator const&, QMap<QString,
   double>::const_iterator const&) */

void operator==(const_iterator *param_1,const_iterator *param_2)

{
  std::operator==((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001e2f2b  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, unsigned int>::iterator const&, QMap<QString, unsigned
   int>::iterator const&) */

void operator==(iterator *param_1,iterator *param_2)

{
  std::operator==((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001e2f50  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, unsigned int>::const_iterator const&, QMap<QString,
   unsigned int>::const_iterator const&) */

void operator==(const_iterator *param_1,const_iterator *param_2)

{
  std::operator==((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 001e4f76  qt_ptr_swap<QTypedArrayData<NCDEEngine::Lab>>

/* void qt_ptr_swap<QTypedArrayData<NCDEEngine::Lab> >(QTypedArrayData<NCDEEngine::Lab>*&,
   QTypedArrayData<NCDEEngine::Lab>*&) */

void qt_ptr_swap<QTypedArrayData<NCDEEngine::Lab>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001e4fa9  qt_ptr_swap<NCDEEngine::Lab>

/* void qt_ptr_swap<NCDEEngine::Lab>(NCDEEngine::Lab*&, NCDEEngine::Lab*&) */

void qt_ptr_swap<NCDEEngine::Lab>(Lab **param_1,Lab **param_2)

{
  Lab *pLVar1;
  
  pLVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pLVar1;
  return;
}



// ==== 001e514a  qt_ptr_swap<QTypedArrayData<double>>

/* void qt_ptr_swap<QTypedArrayData<double> >(QTypedArrayData<double>*&, QTypedArrayData<double>*&)
    */

void qt_ptr_swap<QTypedArrayData<double>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001e517d  qt_ptr_swap<double>

/* void qt_ptr_swap<double>(double*&, double*&) */

void qt_ptr_swap<double>(double **param_1,double **param_2)

{
  double *pdVar1;
  
  pdVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pdVar1;
  return;
}



// ==== 001e5d24  qt_ptr_swap<QTypedArrayData<unsigned_int>>

/* void qt_ptr_swap<QTypedArrayData<unsigned int> >(QTypedArrayData<unsigned int>*&,
   QTypedArrayData<unsigned int>*&) */

void qt_ptr_swap<QTypedArrayData<unsigned_int>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001e5d57  qt_ptr_swap<unsigned_int>

/* void qt_ptr_swap<unsigned int>(unsigned int*&, unsigned int*&) */

void qt_ptr_swap<unsigned_int>(uint **param_1,uint **param_2)

{
  uint *puVar1;
  
  puVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = puVar1;
  return;
}



// ==== 001e66c7  operator<<

/* std::enable_if<std::is_enum<QProcess::ExitStatus>::value, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QProcess::ExitStatus const&) */

void operator<<(QDataStream *param_1,ExitStatus *param_2)

{
  QDataStream::operator<<(param_1,*(uint *)param_2);
  return;
}



// ==== 001e66ed  operator>>

/* std::enable_if<std::is_enum<QProcess::ExitStatus>::value, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QProcess::ExitStatus&) */

QDataStream * operator>>(QDataStream *param_1,ExitStatus *param_2)

{
  long in_FS_OFFSET;
  uint local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QDataStream::operator>>(param_1,&local_14);
  *(uint *)param_2 = local_14;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 001e962e  qt_ptr_swap<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>

/* void qt_ptr_swap<QMapData<std::map<QString, QMap<QString, QVariant>, std::less<QString>,
   std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >
   >(QMapData<std::map<QString, QMap<QString, QVariant>, std::less<QString>,
   std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*&,
   QMapData<std::map<QString, QMap<QString, QVariant>, std::less<QString>,
   std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*&) */

void qt_ptr_swap<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001e9ce4  qt_ptr_swap<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>

/* void qt_ptr_swap<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > > >(QMapData<std::map<QString, double,
   std::less<QString>, std::allocator<std::pair<QString const, double> > > >*&,
   QMapData<std::map<QString, double, std::less<QString>, std::allocator<std::pair<QString const,
   double> > > >*&) */

void qt_ptr_swap<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001ea374  qt_ptr_swap<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>

/* void qt_ptr_swap<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > > >(QMapData<std::map<QString, unsigned
   int, std::less<QString>, std::allocator<std::pair<QString const, unsigned int> > > >*&,
   QMapData<std::map<QString, unsigned int, std::less<QString>, std::allocator<std::pair<QString
   const, unsigned int> > > >*&) */

void qt_ptr_swap<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 001ead02  qHashEquals<int>

/* bool qHashEquals<int>(int const&, int const&) */

bool qHashEquals<int>(int *param_1,int *param_2)

{
  return *param_1 == *param_2;
}



// ==== 001ec1d6  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QMap<QString, QVariant> >::iterator const&, QMap<QString,
   QMap<QString, QVariant> >::iterator const&) */

void operator!=(iterator *param_1,iterator *param_2)

{
  std::operator!=((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001ecb56  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, double>::iterator const&, QMap<QString, double>::iterator
   const&) */

void operator!=(iterator *param_1,iterator *param_2)

{
  std::operator!=((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001ed472  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QString, unsigned int>::iterator const&, QMap<QString, unsigned
   int>::iterator const&) */

void operator!=(iterator *param_1,iterator *param_2)

{
  std::operator!=((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 001f178c  operator==

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QVariant> const&, QMap<QString, QVariant> const&) */

bool operator==(QMap *param_1,QMap *param_2)

{
  long lVar1;
  bool bVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = comparesEqual<QString,QVariant,true>(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}



// ==== 001f1f2f  comparesEqual<QString,QVariant,true>

/* bool comparesEqual<QString, QVariant, true>(QMap<QString, QVariant> const&, QMap<QString,
   QVariant> const&) */

bool comparesEqual<QString,QVariant,true>(QMap *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  cVar1 = QtPrivate::operator==
                    ((QExplicitlySharedDataPointerV2 *)param_1,
                     (QExplicitlySharedDataPointerV2 *)param_2);
  if (cVar1 == '\0') {
    bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                      ((QExplicitlySharedDataPointerV2 *)param_1);
    if (bVar2) {
      bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                        ((QExplicitlySharedDataPointerV2 *)param_2);
      if (bVar2) {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                              *)param_2);
        lVar4 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                              *)param_1);
        bVar2 = std::operator==((map *)(lVar4 + 8),(map *)(lVar3 + 8));
      }
      else {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
                              *)param_1);
        cVar1 = std::
                map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>
                ::empty((map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>
                         *)(lVar3 + 8));
        bVar2 = cVar1 != '\0';
      }
    }
    else {
      bVar2 = operator==(param_2,param_1);
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}



// ==== 001f4190  main

/* WARNING: Removing unreachable block (ram,0x001f58d3) */

undefined4 main(int param_1,char **param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  QDebug *this;
  QList<QString> *this_00;
  IconProvider *this_01;
  QString *pQVar5;
  undefined8 *puVar6;
  long in_FS_OFFSET;
  int local_175c [2];
  int local_1754;
  QWindow *local_1750;
  wchar16 *local_1748;
  wchar16 *local_1740;
  wchar16 *local_1738;
  wchar16 *local_1730;
  wchar16 *local_1728;
  wchar16 *local_1720;
  undefined *local_1718;
  wchar16 *local_1710;
  wchar16 *local_1708;
  wchar16 *local_1700;
  wchar16 *local_16f8;
  wchar16 *local_16f0;
  wchar16 *local_16e8;
  wchar16 *local_16e0;
  QGuiApplication local_16d8 [16];
  Launcher local_16c8 [16];
  ScreenInfo local_16b8 [16];
  HudManager local_16a8 [16];
  undefined8 local_1698;
  undefined8 local_1690;
  NCDEGeo local_1688 [32];
  QString local_1668 [32];
  QArrayDataPointer<char16_t> local_1648 [32];
  QString local_1628 [32];
  QString local_1608 [32];
  QString local_15e8 [32];
  QString local_15c8 [32];
  QArrayDataPointer<char16_t> local_15a8 [32];
  QString local_1588 [32];
  QString local_1568 [32];
  int local_1548 [8];
  int local_1528 [8];
  int local_1508 [8];
  int local_14e8;
  undefined4 uStack_14e4;
  undefined8 local_14e0;
  Theme local_14c8 [32];
  AnimPolicy local_14a8 [32];
  QSurfaceFormat *local_1488;
  QSurfaceFormat *local_1480;
  AppMenuModel local_1468 [48];
  GliaSystemMenus local_1438 [48];
  WindowTyper local_1408 [48];
  NotificationManager local_13d8 [64];
  LeapFrogPond local_1398 [80];
  undefined1 local_1348 [16];
  undefined1 local_1338 [16];
  undefined1 local_1328 [16];
  undefined1 local_1318 [16];
  undefined8 local_1308;
  IdleInhibitService local_12f8 [80];
  QSurfaceFormat *local_12a8;
  NCDEWindowManager *pNStack_12a0;
  QArrayDataPointer<char16_t> *local_1298;
  NCDEWorkspace local_1258 [96];
  CalendarBackend local_11f8 [96];
  NCDEWindowManager local_1198 [352];
  WidgetData local_1038 [432];
  QArrayDataPointer<char16_t> local_e88 [1120];
  QSurfaceFormat local_a28 [1232];
  QVariant local_558 [32];
  NCDEEngine local_538 [1272];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  local_175c[0] = param_1;
  QSurfaceFormat::defaultFormat();
  QSurfaceFormat::setAlphaBufferSize((int)local_a28);
  QSurfaceFormat::setDefaultFormat(local_a28);
  QSurfaceFormat::~QSurfaceFormat(local_a28);
  local_1748 = L"qt.text.emojisegmenter.warning=false";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_e88,(QTypedArrayData *)0x0,L"qt.text.emojisegmenter.warning=false",0x24);
  QString::QString((QString *)local_a28,(QArrayDataPointer *)local_e88);
  QLoggingCategory::setFilterRules((QString *)local_a28);
  QString::~QString((QString *)local_a28);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e88);
  QGuiApplication::QGuiApplication(local_16d8,local_175c,param_2,0x60b01);
  Lelan::Lelan((Lelan *)local_e88,(QObject *)0x0,true);
  NCDEEngine::NCDEEngine(local_538,(QObject *)0x0);
  NCDEEngine::setLelan(local_538,(Lelan *)local_e88);
  Lelan::setEngine((Lelan *)local_e88,local_538);
  Settings::Settings((Settings *)local_a28,(QObject *)0x0);
  Settings::setLelan((Settings *)local_a28,(Lelan *)local_e88);
  Theme::Theme(local_14c8,(QObject *)0x0);
  Theme::setSettings(local_14c8,(Settings *)local_a28);
  Theme::setEngine(local_14c8,(QObject *)local_538);
  WidgetData::WidgetData(local_1038,(QObject *)0x0);
  WidgetData::setLelan(local_1038,(Lelan *)local_e88);
  AnimPolicy::AnimPolicy(local_14a8,(QObject *)0x0);
  Lelan::setAnimPolicy((Lelan *)local_e88,local_14a8);
  Settings::setAnimPolicy((Settings *)local_a28,(QObject *)local_14a8);
  WidgetData::setAnimPolicy(local_1038,local_14a8);
  Launcher::Launcher(local_16c8,(QObject *)0x0);
  NotificationManager::NotificationManager(local_13d8,(QObject *)0x0);
  NotificationManager::setSettings(local_13d8,(QObject *)local_a28);
  CalendarBackend::CalendarBackend(local_11f8,(QObject *)0x0);
  NCDEWorkspace::NCDEWorkspace(local_1258,(QObject *)0x0);
  AppMenuModel::AppMenuModel(local_1468,(QObject *)0x0);
  ScreenInfo::ScreenInfo(local_16b8,(QObject *)0x0);
  LeapFrogPond::LeapFrogPond(local_1398,(QObject *)0x0,local_11f8);
  GliaSystemMenus::GliaSystemMenus(local_1438,(QObject *)0x0);
  NCDEGeo::NCDEGeo(local_1688,(QObject *)0x0);
  NCDEGeo::setLelan(local_1688,(Lelan *)local_e88);
  HudManager::HudManager(local_16a8,(QObject *)0x0);
  Lelan::applyZenStartupHints();
  WindowTyper::WindowTyper(local_1408,(QObject *)0x0);
  NCDEWindowManager::NCDEWindowManager(local_1198,(QObject *)0x0);
  IdleInhibitService::IdleInhibitService(local_12f8,(QObject *)0x0);
  NCDEWindowManager::start(local_1198);
  NCDEWindowManager::setAnimPolicy(local_1198,local_14a8);
  local_12a8 = local_a28;
  pNStack_12a0 = local_1198;
  local_1298 = local_e88;
  main::{lambda()#1}::operator()((_lambda___1_ *)&local_12a8);
  QObject::connect<void(Settings::*)(),main::_lambda()_1_&>
            (local_1348,local_a28,Settings::settingsChanged,0,local_1198,&local_12a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  QObject::connect<void(Settings::*)(),main::_lambda()_1_&>
            (local_1348,local_a28,Settings::powerChanged,0,local_1198,&local_12a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  QObject::connect<void(Lelan::*)(),main::_lambda()_1_&>
            (local_1348,local_e88,Lelan::batteryChanged,0,local_1198,&local_12a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  local_1488 = local_a28;
  QObject::connect<void(NCDEWindowManager::*)(),main::_lambda()_2_>
            (local_1348,local_1198,NCDEWindowManager::screensaverIdleReached,0,local_a28,&local_1488
             ,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  local_1348._8_8_ = local_1198;
  local_1348._0_8_ = local_a28;
  QObject::connect<void(Settings::*)(int,bool),main::_lambda(int,bool)_1_>
            (&local_1488,local_a28,Settings::screensaverFinished,0,local_1198,local_1348,0);
  QMetaObject::Connection::~Connection((Connection *)&local_1488);
  local_12a8 = (QSurfaceFormat *)Lelan::onWMScreenConfig;
  pNStack_12a0 = (NCDEWindowManager *)0x0;
  QObject::connect<void(NCDEWindowManager::*)(int,int),void(Lelan::*)(int,int)>
            (local_1348,local_1198,NCDEWindowManager::screenConfigChanged,0,local_e88,&local_12a8,0)
  ;
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  local_12a8 = (QSurfaceFormat *)Lelan::onWindowTierNeeded;
  pNStack_12a0 = (NCDEWindowManager *)0x0;
  QObject::
  connect<void(NCDEWindowManager::*)(unsigned_int,QString),void(Lelan::*)(unsigned_int,QString)>
            (local_1348,local_1198,NCDEWindowManager::windowTierNeeded,0,local_e88,&local_12a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  local_12a8 = (QSurfaceFormat *)Lelan::onWindowClosed;
  pNStack_12a0 = (NCDEWindowManager *)0x0;
  QObject::connect<void(NCDEWindowManager::*)(unsigned_int),void(Lelan::*)(unsigned_int)>
            (local_1348,local_1198,NCDEWindowManager::windowClosed,0,local_e88,&local_12a8,0);
  QMetaObject::Connection::~Connection((Connection *)local_1348);
  CursorManager::CursorManager((CursorManager *)&local_12a8,(QObject *)0x0);
  local_1740 = L"Kith";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_1488,(QTypedArrayData *)0x0,L"Kith",4);
  QString::QString((QString *)local_1348,(QArrayDataPointer *)&local_1488);
  CursorManager::setTheme((QString *)&local_12a8,(int)local_1348);
  QString::~QString((QString *)local_1348);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1488);
  local_1730 = L"/ncde-cursors";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_1488,(QTypedArrayData *)0x0,L"/ncde-cursors",0xd)
  ;
  QString::QString((QString *)local_1348,(QArrayDataPointer *)&local_1488);
  local_1738 = L"/tmp";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)local_1528,(QTypedArrayData *)0x0,L"/tmp",4);
  QString::QString((QString *)local_1508,(QArrayDataPointer *)local_1528);
  qEnvironmentVariable((char *)&local_14e8,(QString *)"XDG_RUNTIME_DIR");
  operator+(local_1668,(QString *)&local_14e8);
  QString::~QString((QString *)&local_14e8);
  QString::~QString((QString *)local_1508);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1528);
  QString::~QString((QString *)local_1348);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1488);
  QList<int>::QList(local_1348,C_2_0,4);
  cVar1 = CursorManager::writeXcursorTheme
                    ((CursorManager *)&local_12a8,local_1668,(QList *)local_1348);
  QList<int>::~QList((QList<int> *)local_1348);
  if (cVar1 != '\0') {
    local_1348._0_4_ = 0x40;
    QObject::property((char *)local_558);
    uVar2 = QVariant::toInt((bool *)local_558);
    local_1488 = (QSurfaceFormat *)CONCAT44(local_1488._4_4_,uVar2);
    local_14e8 = 0x18;
    piVar4 = qBound<int>(&local_14e8,(int *)&local_1488,(int *)local_1348);
    local_1754 = *piVar4;
    QVariant::~QVariant(local_558);
    QArrayDataPointer<char>::QArrayDataPointer
              ((QArrayDataPointer<char> *)&local_1488,(QTypedArrayData *)0x0,"Kith",4);
    QByteArray::QByteArray((QByteArray *)local_1348,(QArrayDataPointer *)&local_1488);
    QByteArrayView::QByteArrayView<QByteArray,true>
              ((QByteArrayView *)&local_14e8,(QByteArray *)local_1348);
    qputenv("XCURSOR_THEME",CONCAT44(uStack_14e4,local_14e8),local_14e0);
    QByteArray::~QByteArray((QByteArray *)local_1348);
    QArrayDataPointer<char>::~QArrayDataPointer((QArrayDataPointer<char> *)&local_1488);
    QByteArray::number((int)local_1348,local_1754);
    QByteArrayView::QByteArrayView<QByteArray,true>
              ((QByteArrayView *)&local_1488,(QByteArray *)local_1348);
    qputenv("XCURSOR_SIZE",local_1488,local_1480);
    QByteArray::~QByteArray((QByteArray *)local_1348);
    local_1728 = L"/.icons:/usr/share/icons:/usr/share/pixmaps";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_1508,(QTypedArrayData *)0x0,
               L"/.icons:/usr/share/icons:/usr/share/pixmaps",0x2b);
    QString::QString((QString *)&local_14e8,(QArrayDataPointer *)local_1508);
    QDir::homePath();
    local_1720 = L"/.local/share/icons:";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_15a8,(QTypedArrayData *)0x0,L"/.local/share/icons:",0x14);
    QString::QString(local_1588,(QArrayDataPointer *)local_15a8);
    QDir::homePath();
    local_1718 = &DAT_002a82aa;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_1648,(QTypedArrayData *)0x0,L":",1);
    QString::QString(local_1628,(QArrayDataPointer *)local_1648);
    operator+(local_1608,local_1668);
    operator+(local_15c8,local_1608);
    operator+(local_1568,local_15c8);
    operator+((QString *)local_1528,local_1568);
    operator+((QString *)&local_1488,(QString *)local_1528);
    QString::toUtf8((QString *)local_1348);
    QByteArrayView::QByteArrayView<QByteArray,true>
              ((QByteArrayView *)&local_1698,(QByteArray *)local_1348);
    qputenv("XCURSOR_PATH",local_1698,local_1690);
    QByteArray::~QByteArray((QByteArray *)local_1348);
    QString::~QString((QString *)&local_1488);
    QString::~QString((QString *)local_1528);
    QString::~QString(local_1568);
    QString::~QString(local_15c8);
    QString::~QString(local_1608);
    QString::~QString(local_1628);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_1648);
    QString::~QString(local_15e8);
    QString::~QString(local_1588);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_15a8);
    QString::~QString((QString *)local_1548);
    QString::~QString((QString *)&local_14e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_1508);
    local_1710 = L"/.local/share/icons";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_1488,(QTypedArrayData *)0x0,
               L"/.local/share/icons",0x13);
    QString::QString((QString *)local_1348,(QArrayDataPointer *)&local_1488);
    QDir::homePath();
    operator+((QString *)local_1528,(QString *)&local_14e8);
    QString::~QString((QString *)&local_14e8);
    QString::~QString((QString *)local_1348);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1488);
    QString::QString((QString *)local_1348);
    QDir::QDir((QDir *)&local_14e8,(QString *)local_1348);
    std::optional<QFlags<QFileDevice::Permission>>::optional(&local_1488);
    QDir::mkpath(&local_14e8,local_1528,local_1488);
    QDir::~QDir((QDir *)&local_14e8);
    QString::~QString((QString *)local_1348);
    local_1708 = L"/Kith";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_1488,(QTypedArrayData *)0x0,L"/Kith",5);
    QString::QString((QString *)local_1348,(QArrayDataPointer *)&local_1488);
    operator+((QString *)local_1508,(QString *)local_1528);
    QString::~QString((QString *)local_1348);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1488);
    QFileInfo::QFileInfo((QFileInfo *)local_1348,(QString *)local_1508);
    cVar1 = QFileInfo::isSymLink();
    QFileInfo::~QFileInfo((QFileInfo *)local_1348);
    if (cVar1 != '\0') {
      QFile::remove((QString *)local_1508);
    }
    cVar1 = QFileInfo::exists((QString *)local_1508);
    if (cVar1 != '\x01') {
      local_1700 = L"/Kith";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)&local_14e8,(QTypedArrayData *)0x0,L"/Kith",5);
      QString::QString((QString *)&local_1488,(QArrayDataPointer *)&local_14e8);
      operator+((QString *)local_1348,local_1668);
      QFile::link((QString *)local_1348,(QString *)local_1508);
      QString::~QString((QString *)local_1348);
      QString::~QString((QString *)&local_1488);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_14e8);
    }
    QString::~QString((QString *)local_1508);
    QString::~QString((QString *)local_1528);
  }
  QString::~QString(local_1668);
  local_1348._8_8_ = local_a28;
  local_1348._0_8_ = &local_12a8;
  main::{lambda()#3}::operator()((_lambda___3_ *)local_1348);
  QObject::connect<void(Settings::*)(),main::_lambda()_3_&>
            (&local_1488,local_a28,Settings::inputChanged,0,local_a28,local_1348,0);
  QMetaObject::Connection::~Connection((Connection *)&local_1488);
  local_1348 = (undefined1  [16])0x0;
  local_1338 = (undefined1  [16])0x0;
  local_1328 = (undefined1  [16])0x0;
  local_1308 = 0;
  local_1318._0_12_ = ZEXT412(0x20) << 0x40;
  local_1318._12_4_ = 0;
  local_1508[0] = 0x40;
  QObject::property((char *)local_558);
  local_1528[0] = QVariant::toInt((bool *)local_558);
  local_1548[0] = 0x18;
  piVar4 = qBound<int>(local_1548,local_1528,local_1508);
  iVar3 = *piVar4;
  local_16f8 = L"Kith";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_14e8,(QTypedArrayData *)0x0,L"Kith",4);
  QString::QString((QString *)&local_1488,(QArrayDataPointer *)&local_14e8);
  cVar1 = XSettingsManager::start((XSettingsManager *)local_1348,(QString *)&local_1488,iVar3);
  QString::~QString((QString *)&local_1488);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_14e8);
  QVariant::~QVariant(local_558);
  if (cVar1 != '\x01') {
    QMessageLogger::QMessageLogger((QMessageLogger *)&local_1488,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    this = (QDebug *)QDebug::operator<<((QDebug *)&local_14e8,&DAT_002a82f8);
    QDebug::operator<<(this,"already-running clients unavailable this session");
    QDebug::~QDebug((QDebug *)&local_14e8);
  }
  local_1488 = (QSurfaceFormat *)local_1348;
  local_1480 = local_a28;
  QObject::connect<void(Settings::*)(),main::_lambda()_4_>
            (&local_14e8,local_a28,Settings::inputChanged,0,local_a28,&local_1488,0);
  QMetaObject::Connection::~Connection((Connection *)&local_14e8);
  QDir::homePath();
  operator+((QString *)&local_1488,(char *)&local_14e8);
  QFile::QFile((QFile *)local_1548,(QString *)&local_1488);
  QString::~QString((QString *)&local_1488);
  QString::~QString((QString *)&local_14e8);
  QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)&local_1488,1);
  cVar1 = QFile::open(local_1548,(ulong)local_1488 & 0xffffffff);
  if (cVar1 != '\0') {
    QIODevice::readAll();
    QJsonDocument::fromJson((QByteArray *)local_1588,(QJsonParseError *)local_1508);
    QJsonDocument::object();
    QString::QString((QString *)&local_14e8,"iconTheme");
    QJsonObject::value((QString *)&local_1488);
    QJsonValue::toString();
    QJsonValue::~QJsonValue((QJsonValue *)&local_1488);
    QString::~QString((QString *)&local_14e8);
    QJsonObject::~QJsonObject((QJsonObject *)local_1568);
    QJsonDocument::~QJsonDocument((QJsonDocument *)local_1588);
    QByteArray::~QByteArray((QByteArray *)local_1508);
    cVar1 = QString::isEmpty((QString *)local_1528);
    if (cVar1 != '\x01') {
      QIcon::setThemeName((QString *)local_1528);
    }
    QString::~QString((QString *)local_1528);
  }
  QIcon::themeSearchPaths();
  QDir::homePath();
  operator+((QString *)&local_14e8,(char *)local_1508);
  this_00 = (QList<QString> *)
            QList<QString>::operator<<((QList<QString> *)local_1528,(QString *)&local_14e8);
  QString::QString((QString *)&local_1488,"/usr/share/icons");
  QList<QString>::operator<<(this_00,(QString *)&local_1488);
  QString::~QString((QString *)&local_1488);
  QString::~QString((QString *)&local_14e8);
  QString::~QString((QString *)local_1508);
  QListSpecialMethods<QString>::removeDuplicates((QListSpecialMethods<QString> *)local_1528);
  QIcon::setThemeSearchPaths((QList *)local_1528);
  QList<QString>::~QList((QList<QString> *)local_1528);
  QFile::~QFile((QFile *)local_1548);
  QQmlApplicationEngine::QQmlApplicationEngine((QQmlApplicationEngine *)local_1548,(QObject *)0x0);
  this_01 = operator_new(0x18);
  IconProvider::IconProvider(this_01);
  local_16f0 = L"icon";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_14e8,(QTypedArrayData *)0x0,L"icon",4);
  QString::QString((QString *)&local_1488,(QArrayDataPointer *)&local_14e8);
  QQmlEngine::addImageProvider((QString *)local_1548,(QQmlImageProviderBase *)&local_1488);
  QString::~QString((QString *)&local_1488);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_14e8);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"lelan");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"ncde");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"settings");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"theme");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  if ((main::fontMgr == '\0') && (iVar3 = __cxa_guard_acquire(&main::fontMgr), iVar3 != 0)) {
    FontManager::FontManager((FontManager *)main::fontMgr,(QObject *)0x0);
    __cxa_atexit(FontManager::~FontManager,main::fontMgr,&__dso_handle);
    __cxa_guard_release(&main::fontMgr);
  }
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"fontMgr");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"widget_data");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"animPolicy");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"launcher");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"notifications");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"windowMgr");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"calBackend");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"ncdeWorkspace");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"appMenuModel");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"window");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"pond");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"gliaSystem");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"geo");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  pQVar5 = (QString *)QQmlEngine::rootContext();
  QString::QString((QString *)&local_1488,"hudManager");
  QQmlContext::setContextProperty(pQVar5,(QObject *)&local_1488);
  QString::~QString((QString *)&local_1488);
  QCoreApplication::applicationFilePath();
  QFileInfo::QFileInfo((QFileInfo *)&local_14e8,(QString *)&local_1488);
  QFileInfo::fileName();
  QFileInfo::~QFileInfo((QFileInfo *)&local_14e8);
  QString::~QString((QString *)&local_1488);
  QLatin1String::QLatin1String((QLatin1String *)local_1568,"ncde-test");
  cVar1 = operator==((QString *)local_1528,(QLatin1String *)local_1568);
  if (cVar1 == '\0') {
    local_16e0 = L"/usr/share/ncde";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_1488,(QTypedArrayData *)0x0,L"/usr/share/ncde",
               0xf);
    QString::QString((QString *)local_1508,(QArrayDataPointer *)&local_1488);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_1488);
  }
  else {
    local_16e8 = L"/usr/share/ncde-test";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)&local_14e8,(QTypedArrayData *)0x0,
               L"/usr/share/ncde-test",0x14);
    QString::QString((QString *)local_1508,(QArrayDataPointer *)&local_14e8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_14e8);
  }
  operator+((QString *)&local_1488,(char *)local_1508);
  cVar1 = QFile::exists((QString *)&local_1488);
  QString::~QString((QString *)&local_1488);
  if (cVar1 == '\0') {
    QString::QString((QString *)&local_1488,"qrc:/Shell.qml");
    QUrl::QUrl((QUrl *)&local_14e8,&local_1488,0);
    QQmlApplicationEngine::load((QUrl *)local_1548);
    QUrl::~QUrl((QUrl *)&local_14e8);
    QString::~QString((QString *)&local_1488);
  }
  else {
    QQmlEngine::addImportPath((QString *)local_1548);
    operator+((QString *)&local_1488,(char *)local_1508);
    QUrl::fromLocalFile((QString *)&local_14e8);
    QQmlApplicationEngine::load((QUrl *)local_1548);
    QUrl::~QUrl((QUrl *)&local_14e8);
    QString::~QString((QString *)&local_1488);
  }
  QQmlApplicationEngine::rootObjects();
  cVar1 = QList<QObject*>::isEmpty((QList<QObject*> *)&local_1488);
  QList<QObject*>::~QList((QList<QObject*> *)&local_1488);
  if (cVar1 == '\0') {
    QQmlApplicationEngine::rootObjects();
    puVar6 = (undefined8 *)QList<QObject*>::first((QList<QObject*> *)&local_1488);
    local_1750 = qobject_cast<QWindow*>((QObject *)*puVar6);
    QList<QObject*>::~QList((QList<QObject*> *)&local_1488);
    if (local_1750 != (QWindow *)0x0) {
      CursorManager::install((CursorManager *)&local_12a8,local_1750);
    }
    uVar2 = QGuiApplication::exec();
  }
  else {
    uVar2 = 0xffffffff;
  }
  QString::~QString((QString *)local_1508);
  QString::~QString((QString *)local_1528);
  QQmlApplicationEngine::~QQmlApplicationEngine((QQmlApplicationEngine *)local_1548);
  XSettingsManager::~XSettingsManager((XSettingsManager *)local_1348);
  CursorManager::~CursorManager((CursorManager *)&local_12a8);
  IdleInhibitService::~IdleInhibitService(local_12f8);
  NCDEWindowManager::~NCDEWindowManager(local_1198);
  WindowTyper::~WindowTyper(local_1408);
  HudManager::~HudManager(local_16a8);
  NCDEGeo::~NCDEGeo(local_1688);
  GliaSystemMenus::~GliaSystemMenus(local_1438);
  LeapFrogPond::~LeapFrogPond(local_1398);
  ScreenInfo::~ScreenInfo(local_16b8);
  AppMenuModel::~AppMenuModel(local_1468);
  NCDEWorkspace::~NCDEWorkspace(local_1258);
  CalendarBackend::~CalendarBackend(local_11f8);
  NotificationManager::~NotificationManager(local_13d8);
  Launcher::~Launcher(local_16c8);
  AnimPolicy::~AnimPolicy(local_14a8);
  WidgetData::~WidgetData(local_1038);
  Theme::~Theme(local_14c8);
  Settings::~Settings((Settings *)local_a28);
  NCDEEngine::~NCDEEngine(local_538);
  Lelan::~Lelan((Lelan *)local_e88);
  QGuiApplication::~QGuiApplication(local_16d8);
  if (local_40 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001f80f8  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QString const&, char const* const&) */

void operator==(QString *param_1,char **param_2)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  comparesEqual(param_1,*param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001ff561  qt_ptr_swap<QIconPrivate>

/* void qt_ptr_swap<QIconPrivate>(QIconPrivate*&, QIconPrivate*&) */

void qt_ptr_swap<QIconPrivate>(QIconPrivate **param_1,QIconPrivate **param_2)

{
  QIconPrivate *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0020411d  qt_ptr_swap<QTypedArrayData<QObject*>>

/* void qt_ptr_swap<QTypedArrayData<QObject*> >(QTypedArrayData<QObject*>*&,
   QTypedArrayData<QObject*>*&) */

void qt_ptr_swap<QTypedArrayData<QObject*>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 00204150  qt_ptr_swap<QObject*>

/* void qt_ptr_swap<QObject*>(QObject**&, QObject**&) */

void qt_ptr_swap<QObject*>(QObject ***param_1,QObject ***param_2)

{
  QObject **ppQVar1;
  
  ppQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = ppQVar1;
  return;
}



// ==== 0020421a  detectBfqScheduler

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* detectBfqScheduler() */

undefined4 detectBfqScheduler(void)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 unaff_R13D;
  long in_FS_OFFSET;
  undefined8 local_150;
  undefined8 local_148;
  QList<QString> *local_140;
  undefined8 local_138;
  wchar16 *local_130;
  wchar16 *local_128;
  wchar16 *local_120;
  QFile local_118 [16];
  QList<QString> local_108 [32];
  QArrayDataPointer<char16_t> local_e8 [32];
  QString local_c8 [32];
  undefined4 local_a8 [8];
  undefined4 local_88 [8];
  undefined8 local_68;
  undefined8 local_60;
  QString local_48 [24];
  long local_30;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  local_130 = L"/sys/block";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)&local_68,(QTypedArrayData *)0x0,L"/sys/block",10);
  QString::QString(local_48,(QArrayDataPointer *)&local_68);
  QDir::QDir((QDir *)local_88,local_48);
  QFlags<QDir::SortFlag>::QFlags((QFlags<QDir::SortFlag> *)local_a8,0xffffffff);
  uVar4 = operator|(1,0x6000);
  QDir::entryList(local_108,local_88,uVar4,local_a8[0]);
  QDir::~QDir((QDir *)local_88);
  QString::~QString(local_48);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)&local_68);
  local_140 = local_108;
  local_150 = QList<QString>::begin(local_140);
  local_148 = QList<QString>::end(local_140);
  while (cVar3 = QList<QString>::const_iterator::operator!=((const_iterator *)&local_150,local_148),
        cVar3 != '\0') {
    local_138 = QList<QString>::const_iterator::operator*((const_iterator *)&local_150);
    local_120 = L"/queue/scheduler";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"/queue/scheduler",
               0x10);
    QString::QString((QString *)&local_68,(QArrayDataPointer *)local_88);
    local_128 = L"/sys/block/";
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_e8,(QTypedArrayData *)0x0,L"/sys/block/",0xb);
    QString::QString(local_c8,(QArrayDataPointer *)local_e8);
    operator+((QString *)local_a8,local_c8);
    operator+(local_48,(QString *)local_a8);
    QFile::QFile(local_118,local_48);
    QString::~QString(local_48);
    QString::~QString((QString *)local_a8);
    QString::~QString(local_c8);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_e8);
    QString::~QString((QString *)&local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
    bVar1 = false;
    QFlags<QIODeviceBase::OpenModeFlag>::QFlags((QFlags<QIODeviceBase::OpenModeFlag> *)local_88,1);
    cVar3 = QFile::open(local_118,local_88[0]);
    if (cVar3 == '\0') {
LAB_002044ed:
      bVar2 = false;
    }
    else {
      QIODevice::readAll();
      bVar1 = true;
      QByteArrayView::QByteArrayView<6ul>((QByteArrayView *)&local_68,"[bfq]");
      cVar3 = QByteArray::contains(local_48,local_68,local_60);
      if (cVar3 == '\0') goto LAB_002044ed;
      bVar2 = true;
    }
    if (bVar1) {
      QByteArray::~QByteArray((QByteArray *)local_48);
    }
    if (bVar2) {
      unaff_R13D = 1;
    }
    QFile::~QFile(local_118);
    if (bVar2) goto LAB_00204564;
    QList<QString>::const_iterator::operator++((const_iterator *)&local_150);
  }
  unaff_R13D = 0;
LAB_00204564:
  QList<QString>::~QList(local_108);
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return unaff_R13D;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00208df2  operator|

/* TEMPNAMEPLACEHOLDERVALUE(QDir::Filter, QDir::Filter) */

void operator|(undefined4 param_1,undefined4 param_2)

{
  long in_FS_OFFSET;
  QFlags<QDir::Filter> local_14 [4];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QFlags<QDir::Filter>::QFlags(local_14,param_1);
  QFlags<QDir::Filter>::operator|(local_14,param_2);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00209379  operator<<

/* TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QMap<QString, QVariant> const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QDBusArgument *this;
  long in_FS_OFFSET;
  undefined1 auVar4 [16];
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  QKeyValueRange<QMap<QString,QVariant>const&> *local_78;
  pair *local_70;
  type *local_68;
  type *local_60;
  undefined1 local_58 [16];
  QDBusVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<QDBusVariant>();
  uVar3 = QMetaType::fromType<QString>();
  QDBusArgument::beginMap(param_1,uVar3,uVar2);
  local_90 = QMap<QString,QVariant>::asKeyValueRange((QMap<QString,QVariant> *)param_2);
  local_78 = (QKeyValueRange<QMap<QString,QVariant>const&> *)&local_90;
  local_88 = QtPrivate::QKeyValueRange<QMap<QString,QVariant>const&>::begin(local_78);
  local_80 = QtPrivate::QKeyValueRange<QMap<QString,QVariant>const&>::end(local_78);
  while( true ) {
    cVar1 = operator!=(local_88,local_80);
    if (cVar1 == '\0') break;
    auVar4 = QKeyValueIterator<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator,QtPrivate::QDefaultKeyValues<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator>>
             ::operator*((QKeyValueIterator<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator,QtPrivate::QDefaultKeyValues<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator>>
                          *)&local_88);
    local_70 = (pair *)local_58;
    local_58 = auVar4;
    local_68 = std::get<0ul,QString_const&,QVariant_const&>(local_70);
    local_60 = std::get<1ul,QString_const&,QVariant_const&>(local_70);
    QDBusArgument::beginMapEntry();
    this = (QDBusArgument *)QDBusArgument::operator<<(param_1,(QString *)local_68);
    QDBusVariant::QDBusVariant(local_48,(QVariant *)local_60);
    QDBusArgument::operator<<(this,local_48);
    QDBusVariant::~QDBusVariant(local_48);
    QDBusArgument::endMapEntry();
    QKeyValueIterator<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator,QtPrivate::QDefaultKeyValues<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator>>
    ::operator++((QKeyValueIterator<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator,QtPrivate::QDefaultKeyValues<QString_const&,QVariant_const&,QMap<QString,QVariant>::const_iterator>>
                  *)&local_88);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00209730  qRegisterNormalizedMetaType<QList<unsigned_int>>

/* int qRegisterNormalizedMetaType<QList<unsigned int> >(QByteArray const&) */

int qRegisterNormalizedMetaType<QList<unsigned_int>>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QList<unsigned_int>>(param_1);
  return iVar1;
}



// ==== 0020974a  qRegisterMetaType<QList<unsigned_int>>

/* int qRegisterMetaType<QList<unsigned int> >(char const*) */

int qRegisterMetaType<QList<unsigned_int>>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QList<unsigned_int>>(local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 002097e0  qRegisterNormalizedMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* int qRegisterNormalizedMetaType<QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >
   >(QByteArray const&) */

int qRegisterNormalizedMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
              (QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
                    (param_1);
  return iVar1;
}



// ==== 002097fa  qRegisterMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* int qRegisterMetaType<QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > >(char
   const*) */

int qRegisterMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(char *param_1)

{
  int iVar1;
  long in_FS_OFFSET;
  QByteArray local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaObject::normalizedType((char *)local_38);
  iVar1 = qRegisterNormalizedMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
                    (local_38);
  QByteArray::~QByteArray(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar1;
}



// ==== 002099b1  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QKeyValueIterator<QString const&, QVariant const&, QMap<QString,
   QVariant>::const_iterator, QtPrivate::QDefaultKeyValues<QString const&, QVariant const&,
   QMap<QString, QVariant>::const_iterator> >, QKeyValueIterator<QString const&, QVariant const&,
   QMap<QString, QVariant>::const_iterator, QtPrivate::QDefaultKeyValues<QString const&, QVariant
   const&, QMap<QString, QVariant>::const_iterator> >) */

void operator!=(undefined8 param_1,undefined8 param_2)

{
  undefined8 local_18;
  undefined8 local_10;
  
  local_18 = param_2;
  local_10 = param_1;
  operator!=((const_iterator *)&local_10,(const_iterator *)&local_18);
  return;
}



// ==== 00209d0f  qDBusRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* QMetaType qDBusRegisterMetaType<QMap<QString, QMap<QString, QVariant> > >() */

undefined1 * qDBusRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>(void)

{
  _func_void_QDBusArgument_ptr_void_ptr *p_Var1;
  _func_void_QDBusArgument_ptr_void_ptr *p_Var2;
  long in_FS_OFFSET;
  _lambda_QDBusArgument__void_const___1_ local_2a;
  _lambda_QDBusArgument_const__void___1_ local_29;
  undefined1 *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,QMap<QString,QVariant>>>::metaType;
  p_Var1 = qDBusRegisterMetaType()::{lambda(QDBusArgument_const&,void*)#1}::
           operator_cast_to_function_pointer(&local_29);
  p_Var2 = qDBusRegisterMetaType()::{lambda(QDBusArgument&,void_const*)#1}::
           operator_cast_to_function_pointer(&local_2a);
  QDBusMetaType::registerMarshallOperators(local_28,p_Var2,p_Var1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28;
}



// ==== 0020a11d  qDBusRegisterMetaType<QList<unsigned_int>>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* QMetaType qDBusRegisterMetaType<QList<unsigned int> >() */

undefined1 * qDBusRegisterMetaType<QList<unsigned_int>>(void)

{
  _func_void_QDBusArgument_ptr_void_ptr *p_Var1;
  _func_void_QDBusArgument_ptr_void_ptr *p_Var2;
  long in_FS_OFFSET;
  _lambda_QDBusArgument__void_const___1_ local_2a;
  _lambda_QDBusArgument_const__void___1_ local_29;
  undefined1 *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QtPrivate::QMetaTypeInterfaceWrapper<QList<unsigned_int>>::metaType;
  p_Var1 = qDBusRegisterMetaType()::{lambda(QDBusArgument_const&,void*)#1}::
           operator_cast_to_function_pointer(&local_29);
  p_Var2 = qDBusRegisterMetaType()::{lambda(QDBusArgument&,void_const*)#1}::
           operator_cast_to_function_pointer(&local_2a);
  QDBusMetaType::registerMarshallOperators(local_28,p_Var2,p_Var1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28;
}



// ==== 0020a541  qDBusRegisterMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* QMetaType qDBusRegisterMetaType<QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >
   >() */

undefined1 * qDBusRegisterMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(void)

{
  _func_void_QDBusArgument_ptr_void_ptr *p_Var1;
  _func_void_QDBusArgument_ptr_void_ptr *p_Var2;
  long in_FS_OFFSET;
  _lambda_QDBusArgument__void_const___1_ local_2a;
  _lambda_QDBusArgument_const__void___1_ local_29;
  undefined1 *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QtPrivate::
             QMetaTypeInterfaceWrapper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::
             metaType;
  p_Var1 = qDBusRegisterMetaType()::{lambda(QDBusArgument_const&,void*)#1}::
           operator_cast_to_function_pointer(&local_29);
  p_Var2 = qDBusRegisterMetaType()::{lambda(QDBusArgument&,void_const*)#1}::
           operator_cast_to_function_pointer(&local_2a);
  QDBusMetaType::registerMarshallOperators(local_28,p_Var2,p_Var1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28;
}



// ==== 0020a679  qDBusRegisterMetaType<QMap<QString,double>>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* QMetaType qDBusRegisterMetaType<QMap<QString, double> >() */

undefined1 * qDBusRegisterMetaType<QMap<QString,double>>(void)

{
  _func_void_QDBusArgument_ptr_void_ptr *p_Var1;
  _func_void_QDBusArgument_ptr_void_ptr *p_Var2;
  long in_FS_OFFSET;
  _lambda_QDBusArgument__void_const___1_ local_2a;
  _lambda_QDBusArgument_const__void___1_ local_29;
  undefined1 *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,double>>::metaType;
  p_Var1 = qDBusRegisterMetaType()::{lambda(QDBusArgument_const&,void*)#1}::
           operator_cast_to_function_pointer(&local_29);
  p_Var2 = qDBusRegisterMetaType()::{lambda(QDBusArgument&,void_const*)#1}::
           operator_cast_to_function_pointer(&local_2a);
  QDBusMetaType::registerMarshallOperators(local_28,p_Var2,p_Var1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28;
}



// ==== 0020a7b1  qDBusRegisterMetaType<QMap<QString,unsigned_int>>

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* QMetaType qDBusRegisterMetaType<QMap<QString, unsigned int> >() */

undefined1 * qDBusRegisterMetaType<QMap<QString,unsigned_int>>(void)

{
  _func_void_QDBusArgument_ptr_void_ptr *p_Var1;
  _func_void_QDBusArgument_ptr_void_ptr *p_Var2;
  long in_FS_OFFSET;
  _lambda_QDBusArgument__void_const___1_ local_2a;
  _lambda_QDBusArgument_const__void___1_ local_29;
  undefined1 *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,unsigned_int>>::metaType;
  p_Var1 = qDBusRegisterMetaType()::{lambda(QDBusArgument_const&,void*)#1}::
           operator_cast_to_function_pointer(&local_29);
  p_Var2 = qDBusRegisterMetaType()::{lambda(QDBusArgument&,void_const*)#1}::
           operator_cast_to_function_pointer(&local_2a);
  QDBusMetaType::registerMarshallOperators(local_28,p_Var2,p_Var1);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_28;
}



// ==== 0020a9d5  qRegisterNormalizedMetaTypeImplementation<QList<unsigned_int>>

/* int qRegisterNormalizedMetaTypeImplementation<QList<unsigned int> >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QList<unsigned_int>>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QList<unsigned_int>>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialValueTypeIsMetaType<QList<unsigned_int>,true>::registerConverter();
  QtPrivate::SequentialValueTypeIsMetaType<QList<unsigned_int>,true>::registerMutableView();
  QtPrivate::AssociativeContainerTransformationHelper<QList<unsigned_int>,false>::registerConverter
            ();
  QtPrivate::AssociativeContainerTransformationHelper<QList<unsigned_int>,false>::
  registerMutableView();
  QtPrivate::IsPair<QList<unsigned_int>>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QList<unsigned_int>,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QList<unsigned_int>>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 0020aa85  qRegisterNormalizedMetaTypeImplementation<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* int qRegisterNormalizedMetaTypeImplementation<QMap<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> > > >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
              (QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::
             QMetaTypeInterfaceWrapper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::
             metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::
  SequentialContainerTransformationHelper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,false>
  ::registerConverter();
  QtPrivate::
  SequentialContainerTransformationHelper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,false>
  ::registerMutableView();
  QtPrivate::
  AssociativeKeyTypeIsMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,true>::
  registerConverter();
  QtPrivate::
  AssociativeKeyTypeIsMetaType<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,true>::
  registerMutableView();
  QtPrivate::IsPair<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::registerConverter()
  ;
  QtPrivate::
  MetaTypeSmartPointerHelper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,void>::
  registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::
  registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 0020ae52  operator<<

/* QDBusArgument& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QMap<QString, QMap<QString, QVariant> >
   const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QString *pQVar4;
  QDBusArgument *pQVar5;
  QMap *pQVar6;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<QMap<QString,QVariant>>();
  uVar3 = QMetaType::fromType<QString>();
  QDBusArgument::beginMap(param_1,uVar3,uVar2);
  local_30 = QMap<QString,QMap<QString,QVariant>>::begin
                       ((QMap<QString,QMap<QString,QVariant>> *)param_2);
  local_28 = QMap<QString,QMap<QString,QVariant>>::end
                       ((QMap<QString,QMap<QString,QVariant>> *)param_2);
  while( true ) {
    cVar1 = operator!=((const_iterator *)&local_30,(const_iterator *)&local_28);
    if (cVar1 == '\0') break;
    QDBusArgument::beginMapEntry();
    pQVar4 = (QString *)
             QMap<QString,QMap<QString,QVariant>>::const_iterator::key((const_iterator *)&local_30);
    pQVar5 = (QDBusArgument *)QDBusArgument::operator<<(param_1,pQVar4);
    pQVar6 = (QMap *)QMap<QString,QMap<QString,QVariant>>::const_iterator::value
                               ((const_iterator *)&local_30);
    operator<<(pQVar5,pQVar6);
    QDBusArgument::endMapEntry();
    QMap<QString,QMap<QString,QVariant>>::const_iterator::operator++((const_iterator *)&local_30);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020af53  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QMap<QString, QMap<QString,
   QVariant> >&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  QDBusArgument *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginMap();
  QMap<QString,QMap<QString,QVariant>>::clear((QMap<QString,QMap<QString,QVariant>> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    local_40 = 0;
    QDBusArgument::beginMapEntry();
    pQVar2 = (QDBusArgument *)QDBusArgument::operator>>(param_1,(QString *)&local_38);
    operator>>(pQVar2,(QMap *)&local_40);
    QMap<QString,QMap<QString,QVariant>>::insert
              ((QMap<QString,QMap<QString,QVariant>> *)param_2,(QString *)&local_38,
               (QMap *)&local_40);
    QDBusArgument::endMapEntry();
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_40);
    QString::~QString((QString *)&local_38);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020b099  operator<<

/* QDBusArgument& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QList<unsigned int> const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QList *param_2)

{
  char cVar1;
  undefined8 uVar2;
  uint *puVar3;
  long in_FS_OFFSET;
  undefined8 local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<unsigned_int>();
  QDBusArgument::beginArray(param_1,uVar2);
  local_20 = QList<unsigned_int>::begin((QList<unsigned_int> *)param_2);
  local_18 = QList<unsigned_int>::end((QList<unsigned_int> *)param_2);
  while( true ) {
    cVar1 = QList<unsigned_int>::const_iterator::operator!=((const_iterator *)&local_20,local_18);
    if (cVar1 == '\0') break;
    puVar3 = (uint *)QList<unsigned_int>::const_iterator::operator*((const_iterator *)&local_20);
    QDBusArgument::operator<<(param_1,*puVar3);
    QList<unsigned_int>::const_iterator::operator++((const_iterator *)&local_20);
  }
  QDBusArgument::endArray();
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020b156  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QList<unsigned int>&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QList *param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  uint local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginArray();
  QList<unsigned_int>::clear((QList<unsigned_int> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    QDBusArgument::operator>>(param_1,&local_14);
    QList<unsigned_int>::push_back((QList<unsigned_int> *)param_2,local_14);
  }
  QDBusArgument::endArray();
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020b46f  operator<<

/* QDBusArgument& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > > const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QDBusObjectPath *pQVar4;
  QDBusArgument *pQVar5;
  QMap *pQVar6;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<QMap<QString,QMap<QString,QVariant>>>();
  uVar3 = QMetaType::fromType<QDBusObjectPath>();
  QDBusArgument::beginMap(param_1,uVar3,uVar2);
  local_30 = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::begin
                       ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)param_2);
  local_28 = QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::end
                       ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)param_2);
  while( true ) {
    cVar1 = operator!=((const_iterator *)&local_30,(const_iterator *)&local_28);
    if (cVar1 == '\0') break;
    QDBusArgument::beginMapEntry();
    pQVar4 = (QDBusObjectPath *)
             QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::key
                       ((const_iterator *)&local_30);
    pQVar5 = (QDBusArgument *)QDBusArgument::operator<<(param_1,pQVar4);
    pQVar6 = (QMap *)QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::
                     value((const_iterator *)&local_30);
    operator<<(pQVar5,pQVar6);
    QDBusArgument::endMapEntry();
    QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::const_iterator::operator++
              ((const_iterator *)&local_30);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020b570  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QMap<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> > >&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  QDBusArgument *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_40;
  QDBusObjectPath local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginMap();
  QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::clear
            ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    QDBusObjectPath::QDBusObjectPath(local_38);
    local_40 = 0;
    QDBusArgument::beginMapEntry();
    pQVar2 = (QDBusArgument *)QDBusArgument::operator>>(param_1,local_38);
    operator>>(pQVar2,(QMap *)&local_40);
    QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::insert
              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)param_2,local_38,
               (QMap *)&local_40);
    QDBusArgument::endMapEntry();
    QMap<QString,QMap<QString,QVariant>>::~QMap((QMap<QString,QMap<QString,QVariant>> *)&local_40);
    QDBusObjectPath::~QDBusObjectPath(local_38);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020b906  operator<<

/* QDBusArgument& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QMap<QString, double> const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QString *pQVar4;
  QDBusArgument *this;
  double *pdVar5;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<double>();
  uVar3 = QMetaType::fromType<QString>();
  QDBusArgument::beginMap(param_1,uVar3,uVar2);
  local_30 = QMap<QString,double>::begin((QMap<QString,double> *)param_2);
  local_28 = QMap<QString,double>::end((QMap<QString,double> *)param_2);
  while( true ) {
    cVar1 = operator!=((const_iterator *)&local_30,(const_iterator *)&local_28);
    if (cVar1 == '\0') break;
    QDBusArgument::beginMapEntry();
    pQVar4 = (QString *)QMap<QString,double>::const_iterator::key((const_iterator *)&local_30);
    this = (QDBusArgument *)QDBusArgument::operator<<(param_1,pQVar4);
    pdVar5 = (double *)QMap<QString,double>::const_iterator::value((const_iterator *)&local_30);
    QDBusArgument::operator<<(this,*pdVar5);
    QDBusArgument::endMapEntry();
    QMap<QString,double>::const_iterator::operator++((const_iterator *)&local_30);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020ba0c  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QMap<QString, double>&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  QDBusArgument *this;
  long in_FS_OFFSET;
  double local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginMap();
  QMap<QString,double>::clear((QMap<QString,double> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    QDBusArgument::beginMapEntry();
    this = (QDBusArgument *)QDBusArgument::operator>>(param_1,(QString *)&local_38);
    QDBusArgument::operator>>(this,&local_40);
    QMap<QString,double>::insert((QMap<QString,double> *)param_2,(QString *)&local_38,&local_40);
    QDBusArgument::endMapEntry();
    QString::~QString((QString *)&local_38);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020bb2f  operator<<

/* QDBusArgument& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument&, QMap<QString, unsigned int> const&) */

QDBusArgument * operator<<(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  QString *pQVar4;
  QDBusArgument *this;
  uint *puVar5;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = QMetaType::fromType<unsigned_int>();
  uVar3 = QMetaType::fromType<QString>();
  QDBusArgument::beginMap(param_1,uVar3,uVar2);
  local_30 = QMap<QString,unsigned_int>::begin((QMap<QString,unsigned_int> *)param_2);
  local_28 = QMap<QString,unsigned_int>::end((QMap<QString,unsigned_int> *)param_2);
  while( true ) {
    cVar1 = operator!=((const_iterator *)&local_30,(const_iterator *)&local_28);
    if (cVar1 == '\0') break;
    QDBusArgument::beginMapEntry();
    pQVar4 = (QString *)QMap<QString,unsigned_int>::const_iterator::key((const_iterator *)&local_30)
    ;
    this = (QDBusArgument *)QDBusArgument::operator<<(param_1,pQVar4);
    puVar5 = (uint *)QMap<QString,unsigned_int>::const_iterator::value((const_iterator *)&local_30);
    QDBusArgument::operator<<(this,*puVar5);
    QDBusArgument::endMapEntry();
    QMap<QString,unsigned_int>::const_iterator::operator++((const_iterator *)&local_30);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020bc31  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QMap<QString, unsigned int>&)
    */

QDBusArgument * operator>>(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  QDBusArgument *this;
  long in_FS_OFFSET;
  uint local_3c;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginMap();
  QMap<QString,unsigned_int>::clear((QMap<QString,unsigned_int> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    QDBusArgument::beginMapEntry();
    this = (QDBusArgument *)QDBusArgument::operator>>(param_1,(QString *)&local_38);
    QDBusArgument::operator>>(this,&local_3c);
    QMap<QString,unsigned_int>::insert
              ((QMap<QString,unsigned_int> *)param_2,(QString *)&local_38,&local_3c);
    QDBusArgument::endMapEntry();
    QString::~QString((QString *)&local_38);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020c13d  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QMap<QString, QVariant>&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QMap *param_2)

{
  char cVar1;
  QDBusArgument *pQVar2;
  long in_FS_OFFSET;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginMap();
  QMap<QString,QVariant>::clear((QMap<QString,QVariant> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    local_68 = 0;
    local_60 = 0;
    local_58 = 0;
    QVariant::QVariant(local_48);
    QDBusArgument::beginMapEntry();
    pQVar2 = (QDBusArgument *)QDBusArgument::operator>>(param_1,(QString *)&local_68);
    operator>>(pQVar2,local_48);
    QMap<QString,QVariant>::insert((QMap<QString,QVariant> *)param_2,(QString *)&local_68,local_48);
    QDBusArgument::endMapEntry();
    QVariant::~QVariant(local_48);
    QString::~QString((QString *)&local_68);
  }
  QDBusArgument::endMap();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020c6aa  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QList<unsigned int>, unsigned int>,
   QTypeTraits::has_ostream_operator<QDebug, unsigned int, void> > >, QDebug>::type
   TEMPNAMEPLACEHOLDERVALUE(QDebug, QList<unsigned int> const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printSequentialContainer<QList<unsigned_int>>(param_1,local_30,"QList",param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020c766  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QList<unsigned int>, unsigned int>,
   QTypeTraits::has_ostream_operator<QDataStream, unsigned int, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QList<unsigned int> const&) */

void operator<<(QDataStream *param_1,QList *param_2)

{
  QtPrivate::writeSequentialContainer<QList<unsigned_int>>(param_1,param_2);
  return;
}



// ==== 0020c78b  operator>>

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QList<unsigned int>, unsigned int>,
   QTypeTraits::has_istream_operator<QDataStream, unsigned int, void> > >, QDataStream&>::type
   TEMPNAMEPLACEHOLDERVALUE(QDataStream&, QList<unsigned int>&) */

void operator>>(QDataStream *param_1,QList *param_2)

{
  QtPrivate::readArrayBasedContainer<QList<unsigned_int>>(param_1,param_2);
  return;
}



// ==== 0020c8e4  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::const_iterator const&, QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::const_iterator const&) */

void operator!=(const_iterator *param_1,const_iterator *param_2)

{
  std::operator!=((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 0020cb92  operator==

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >
   const&, QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > const&) */

bool operator==(QMap *param_1,QMap *param_2)

{
  long lVar1;
  bool bVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  bVar2 = comparesEqual<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,true>(param_1,param_2);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar2;
}



// ==== 0020cbda  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QDBusObjectPath>, QTypeTraits::has_ostream_operator<QDebug,
   QDBusObjectPath, void> >, std::disjunction<std::is_base_of<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QMap<QString, QMap<QString, QVariant> > >,
   QTypeTraits::has_ostream_operator<QDebug, QMap<QString, QMap<QString, QVariant> >, void> > >,
   QDebug>::type TEMPNAMEPLACEHOLDERVALUE(QDebug, QMap<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> > > const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printAssociativeContainer<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
            (param_1,local_30,&DAT_002aa771,param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0020e42d  comparesEqual<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,true>

/* bool comparesEqual<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >,
   true>(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > const&,
   QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > const&) */

bool comparesEqual<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,true>
               (QMap *param_1,QMap *param_2)

{
  char cVar1;
  bool bVar2;
  long lVar3;
  long lVar4;
  
  cVar1 = QtPrivate::operator==
                    ((QExplicitlySharedDataPointerV2 *)param_1,
                     (QExplicitlySharedDataPointerV2 *)param_2);
  if (cVar1 == '\0') {
    bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                      ((QExplicitlySharedDataPointerV2 *)param_1);
    if (bVar2) {
      bVar2 = QtPrivate::QExplicitlySharedDataPointerV2::operator_cast_to_bool
                        ((QExplicitlySharedDataPointerV2 *)param_2);
      if (bVar2) {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                              *)param_2);
        lVar4 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                              *)param_1);
        bVar2 = std::operator==((map *)(lVar4 + 8),(map *)(lVar3 + 8));
      }
      else {
        lVar3 = QtPrivate::
                QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                ::operator->((QExplicitlySharedDataPointerV2<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
                              *)param_1);
        cVar1 = std::
                map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>
                ::empty((map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>
                         *)(lVar3 + 8));
        bVar2 = cVar1 != '\0';
      }
    }
    else {
      bVar2 = operator==(param_2,param_1);
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}



// ==== 0021122f  qScopeGuard<QMetaType::registerConverterImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QList<unsigned int>,
   QIterable<QMetaSequence> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerConverterImpl<QList<unsigned
   int>, QIterable<QMetaSequence> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QList<unsigned int>,
   QIterable<QMetaSequence> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 002113d9  qScopeGuard<QMetaType::registerMutableViewImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QList<unsigned int>,
   QIterable<QMetaSequence> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type> qScopeGuard<QMetaType::registerMutableViewImpl<QList<unsigned
   int>, QIterable<QMetaSequence> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QList<unsigned int>,
   QIterable<QMetaSequence> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QList<unsigned_int>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 00212309  qScopeGuard<QMetaType::registerConverterImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void const*,
   void*)>, QMetaType, QMetaType)::{lambda()#1}>::type>
   qScopeGuard<QMetaType::registerConverterImpl<QMap<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void const*,
   void*)>, QMetaType, QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 002124b3  qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>,
   QMetaType, QMetaType)::{lambda()#1}>::type>
   qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > >, QIterable<QMetaAssociation> >(std::function<bool (void*, void*)>,
   QMetaType, QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>,QIterable<QMetaAssociation>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 00213873  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::iterator const&, QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >::iterator
   const&) */

void operator==(iterator *param_1,iterator *param_2)

{
  std::operator==((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 00213898  operator==

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::const_iterator const&, QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::const_iterator const&) */

void operator==(const_iterator *param_1,const_iterator *param_2)

{
  std::operator==((_Rb_tree_const_iterator *)param_1,(_Rb_tree_const_iterator *)param_2);
  return;
}



// ==== 002143e6  qt_ptr_swap<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>

/* void qt_ptr_swap<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >,
   std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const, QMap<QString,
   QMap<QString, QVariant> > > > > > >(QMapData<std::map<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath
   const, QMap<QString, QMap<QString, QVariant> > > > > >*&, QMapData<std::map<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> >, std::less<QDBusObjectPath>,
   std::allocator<std::pair<QDBusObjectPath const, QMap<QString, QMap<QString, QVariant> > > > >
   >*&) */

void qt_ptr_swap<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
               (QMapData **param_1,QMapData **param_2)

{
  QMapData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 002167d4  qt_ptr_swap<QTypedArrayData<std::function<void()>>>

/* void qt_ptr_swap<QTypedArrayData<std::function<void ()> > >(QTypedArrayData<std::function<void
   ()> >*&, QTypedArrayData<std::function<void ()> >*&) */

void qt_ptr_swap<QTypedArrayData<std::function<void()>>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 00216807  qt_ptr_swap<std::function<void()>>

/* void qt_ptr_swap<std::function<void ()> >(std::function<void ()>*&, std::function<void ()>*&) */

void qt_ptr_swap<std::function<void()>>(function **param_1,function **param_2)

{
  function *pfVar1;
  
  pfVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pfVar1;
  return;
}



// ==== 00216f4a  operator!=

/* TEMPNAMEPLACEHOLDERVALUE(QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >
   >::iterator const&, QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >::iterator
   const&) */

void operator!=(iterator *param_1,iterator *param_2)

{
  std::operator!=((_Rb_tree_iterator *)param_1,(_Rb_tree_iterator *)param_2);
  return;
}



// ==== 0022aad0  qdbus_cast<QVariant>

/* QVariant qdbus_cast<QVariant>(QVariant const&) */

QVariant * qdbus_cast<QVariant>(QVariant *param_1)

{
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  qdbus_cast<QDBusVariant>(local_48);
  QDBusVariant::variant();
  QDBusVariant::~QDBusVariant((QDBusVariant *)local_48);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022ab72  ay2str

/* ay2str(QVariant const&) */

QVariant * ay2str(QVariant *param_1)

{
  bool bVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  QVariant local_58 [8];
  char *local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = QVariant::canConvert<QDBusArgument>(in_RSI);
  if (bVar1) {
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    QVariant::value<QDBusArgument>(local_58);
    QDBusArgument::operator>>((QDBusArgument *)local_58,(QByteArray *)&local_38);
    local_50 = (char *)QByteArray::constData((QByteArray *)&local_38);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_48,&local_50);
    QString::fromLocal8Bit(param_1,local_48,local_40);
    QDBusArgument::~QDBusArgument((QDBusArgument *)local_58);
    QByteArray::~QByteArray((QByteArray *)&local_38);
  }
  else {
    QVariant::toByteArray();
    local_50 = (char *)QByteArray::constData((QByteArray *)&local_38);
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_48,&local_50);
    QString::fromLocal8Bit(param_1,local_48,local_40);
    QByteArray::~QByteArray((QByteArray *)&local_38);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022aed0  qdbus_cast<QDBusVariant>

/* QDBusVariant qdbus_cast<QDBusVariant>(QVariant const&) */

QVariant * qdbus_cast<QDBusVariant>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QDBusVariant>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QDBusVariant>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022b028  qvariant_cast<QDBusVariant>

/* QDBusVariant qvariant_cast<QDBusVariant>(QVariant const&) */

QVariant * qvariant_cast<QDBusVariant>(QVariant *param_1)

{
  char cVar1;
  QDBusVariant *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusVariant>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QDBusVariant>((QtPrivate *)param_1,in_RSI,local_20)
    ;
  }
  else {
    pQVar2 = QVariant::Private::get<QDBusVariant>(in_RSI);
    QDBusVariant::QDBusVariant((QDBusVariant *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022b536  qvariant_cast<QDBusObjectPath>

/* QDBusObjectPath qvariant_cast<QDBusObjectPath>(QVariant&&) */

QVariant * qvariant_cast<QDBusObjectPath>(QVariant *param_1)

{
  char cVar1;
  int iVar2;
  QDBusObjectPath *pQVar3;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_30;
  undefined8 local_28 [2];
  QDBusObjectPath *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_30 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusObjectPath>::metaType;
  local_28[0] = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)local_28,(QMetaType *)&local_30);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QDBusObjectPath>
              ((QtPrivate *)param_1,in_RSI,local_30);
  }
  else if (((byte)in_RSI[0x18] & 1) == 0) {
    QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)param_1,(QDBusObjectPath *)in_RSI);
  }
  else {
    iVar2 = QBasicAtomicInteger<int>::loadRelaxed(*(QBasicAtomicInteger<int> **)in_RSI);
    if (iVar2 == 1) {
      local_18 = (QDBusObjectPath *)QVariant::PrivateShared::data(*(PrivateShared **)in_RSI);
      QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)param_1,local_18);
    }
    else {
      pQVar3 = QVariant::Private::get<QDBusObjectPath>(in_RSI);
      QDBusObjectPath::QDBusObjectPath((QDBusObjectPath *)param_1,pQVar3);
    }
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022ba38  qdbus_cast<QList<QDBusObjectPath>>

/* QList<QDBusObjectPath> qdbus_cast<QList<QDBusObjectPath> >(QVariant const&) */

QVariant * qdbus_cast<QList<QDBusObjectPath>>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QList<QDBusObjectPath>>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QList<QDBusObjectPath>>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022bb77  qdbus_cast<QDBusVariant>

/* QDBusVariant qdbus_cast<QDBusVariant>(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QDBusVariant>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  QDBusVariant::QDBusVariant((QDBusVariant *)param_1);
  QDBusArgument::operator>>(in_RSI,(QDBusVariant *)param_1);
  return param_1;
}



// ==== 0022c087  qvariant_cast<QDBusArgument>

/* QDBusArgument qvariant_cast<QDBusArgument>(QVariant&&) */

QVariant * qvariant_cast<QDBusArgument>(QVariant *param_1)

{
  char cVar1;
  int iVar2;
  QDBusArgument *pQVar3;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_30;
  undefined8 local_28 [2];
  QDBusArgument *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_30 = QtPrivate::QMetaTypeInterfaceWrapper<QDBusArgument>::metaType;
  local_28[0] = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)local_28,(QMetaType *)&local_30);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QDBusArgument>
              ((QtPrivate *)param_1,in_RSI,local_30);
  }
  else if (((byte)in_RSI[0x18] & 1) == 0) {
    QDBusArgument::QDBusArgument((QDBusArgument *)param_1,(QDBusArgument *)in_RSI);
  }
  else {
    iVar2 = QBasicAtomicInteger<int>::loadRelaxed(*(QBasicAtomicInteger<int> **)in_RSI);
    if (iVar2 == 1) {
      local_18 = (QDBusArgument *)QVariant::PrivateShared::data(*(PrivateShared **)in_RSI);
      QDBusArgument::QDBusArgument((QDBusArgument *)param_1,local_18);
    }
    else {
      pQVar3 = QVariant::Private::get<QDBusArgument>(in_RSI);
      QDBusArgument::QDBusArgument((QDBusArgument *)param_1,pQVar3);
    }
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022c3ea  qdbus_cast<QList<QDBusObjectPath>>

/* QList<QDBusObjectPath> qdbus_cast<QList<QDBusObjectPath> >(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QList<QDBusObjectPath>>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined1 (*) [16])param_1 = (undefined1  [16])0x0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  operator>>(in_RSI,(QList *)param_1);
  return param_1;
}



// ==== 0022c6e1  qvariant_cast<QList<QDBusObjectPath>>

/* QList<QDBusObjectPath> qvariant_cast<QList<QDBusObjectPath> >(QVariant const&) */

QVariant * qvariant_cast<QList<QDBusObjectPath>>(QVariant *param_1)

{
  char cVar1;
  QList *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QList<QDBusObjectPath>>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QList<QDBusObjectPath>>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QList<QDBusObjectPath>>(in_RSI);
    QList<QDBusObjectPath>::QList((QList<QDBusObjectPath> *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022c8f2  qdbus_cast<QMap<QString,QVariant>>

/* QMap<QString, QVariant> qdbus_cast<QMap<QString, QVariant> >(QVariant const&) */

QVariant * qdbus_cast<QMap<QString,QVariant>>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QMap<QString,QVariant>>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QMap<QString,QVariant>>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022ca3c  qdbus_cast<QMap<QString,QMap<QString,QVariant>>>

/* QMap<QString, QMap<QString, QVariant> > qdbus_cast<QMap<QString, QMap<QString, QVariant> >
   >(QVariant const&) */

QVariant * qdbus_cast<QMap<QString,QMap<QString,QVariant>>>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QMap<QString,QMap<QString,QVariant>>>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QMap<QString,QMap<QString,QVariant>>>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022ccda  operator>>

/* QDBusArgument const& TEMPNAMEPLACEHOLDERVALUE(QDBusArgument const&, QList<QDBusObjectPath>&) */

QDBusArgument * operator>>(QDBusArgument *param_1,QList *param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  QDBusObjectPath local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::beginArray();
  QList<QDBusObjectPath>::clear((QList<QDBusObjectPath> *)param_2);
  while( true ) {
    cVar1 = QDBusArgument::atEnd();
    if (cVar1 == '\x01') break;
    QDBusObjectPath::QDBusObjectPath(local_38);
    QDBusArgument::operator>>(param_1,local_38);
    QList<QDBusObjectPath>::push_back((QList<QDBusObjectPath> *)param_2,local_38);
    QDBusObjectPath::~QDBusObjectPath(local_38);
  }
  QDBusArgument::endArray();
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022d4d8  qdbus_cast<QMap<QString,QVariant>>

/* QMap<QString, QVariant> qdbus_cast<QMap<QString, QVariant> >(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QMap<QString,QVariant>>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined8 *)param_1 = 0;
  operator>>(in_RSI,(QMap *)param_1);
  return param_1;
}



// ==== 0022d52d  qvariant_cast<QMap<QString,QVariant>>

/* QMap<QString, QVariant> qvariant_cast<QMap<QString, QVariant> >(QVariant const&) */

QVariant * qvariant_cast<QMap<QString,QVariant>>(QVariant *param_1)

{
  char cVar1;
  QMap *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined8 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = &QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,QVariant>>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QMap<QString,QVariant>>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QMap<QString,QVariant>>(in_RSI);
    QMap<QString,QVariant>::QMap((QMap<QString,QVariant> *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022d69e  qdbus_cast<QMap<QString,QMap<QString,QVariant>>>

/* QMap<QString, QMap<QString, QVariant> > qdbus_cast<QMap<QString, QMap<QString, QVariant> >
   >(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QMap<QString,QMap<QString,QVariant>>>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined8 *)param_1 = 0;
  operator>>(in_RSI,(QMap *)param_1);
  return param_1;
}



// ==== 0022d6f3  qvariant_cast<QMap<QString,QMap<QString,QVariant>>>

/* QMap<QString, QMap<QString, QVariant> > qvariant_cast<QMap<QString, QMap<QString, QVariant> >
   >(QVariant const&) */

QVariant * qvariant_cast<QMap<QString,QMap<QString,QVariant>>>(QVariant *param_1)

{
  char cVar1;
  QMap *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QMap<QString,QMap<QString,QVariant>>>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QMap<QString,QMap<QString,QVariant>>>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QMap<QString,QMap<QString,QVariant>>>(in_RSI);
    QMap<QString,QMap<QString,QVariant>>::QMap
              ((QMap<QString,QMap<QString,QVariant>> *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022dd16  operator<<

/* std::enable_if<conjunction_v<std::disjunction<std::is_base_of<QList<QDBusObjectPath>,
   QDBusObjectPath>, QTypeTraits::has_ostream_operator<QDebug, QDBusObjectPath, void> > >,
   QDebug>::type TEMPNAMEPLACEHOLDERVALUE(QDebug, QList<QDBusObjectPath> const&) */

QtPrivate * operator<<(QtPrivate *param_1,QDebug *param_2,undefined8 param_3)

{
  long in_FS_OFFSET;
  QDebug local_30 [8];
  QDebug *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = param_2;
  QDebug::QDebug(local_30,param_2);
  QtPrivate::printSequentialContainer<QList<QDBusObjectPath>>(param_1,local_30,"QList",param_3);
  QDebug::~QDebug(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0022f025  qRegisterNormalizedMetaType<QList<QDBusObjectPath>>

/* int qRegisterNormalizedMetaType<QList<QDBusObjectPath> >(QByteArray const&) */

int qRegisterNormalizedMetaType<QList<QDBusObjectPath>>(QByteArray *param_1)

{
  int iVar1;
  
  iVar1 = qRegisterNormalizedMetaTypeImplementation<QList<QDBusObjectPath>>(param_1);
  return iVar1;
}



// ==== 0022f3a7  qt_ptr_swap<QTypedArrayData<QDBusObjectPath>>

/* void qt_ptr_swap<QTypedArrayData<QDBusObjectPath> >(QTypedArrayData<QDBusObjectPath>*&,
   QTypedArrayData<QDBusObjectPath>*&) */

void qt_ptr_swap<QTypedArrayData<QDBusObjectPath>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0022f3da  qt_ptr_swap<QDBusObjectPath>

/* void qt_ptr_swap<QDBusObjectPath>(QDBusObjectPath*&, QDBusObjectPath*&) */

void qt_ptr_swap<QDBusObjectPath>(QDBusObjectPath **param_1,QDBusObjectPath **param_2)

{
  QDBusObjectPath *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0022fd0a  qRegisterNormalizedMetaTypeImplementation<QList<QDBusObjectPath>>

/* int qRegisterNormalizedMetaTypeImplementation<QList<QDBusObjectPath> >(QByteArray const&) */

int qRegisterNormalizedMetaTypeImplementation<QList<QDBusObjectPath>>(QByteArray *param_1)

{
  char cVar1;
  int iVar2;
  long in_FS_OFFSET;
  undefined1 *local_20;
  char *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::QMetaTypeInterfaceWrapper<QList<QDBusObjectPath>>::metaType;
  iVar2 = QMetaType::id((int)&local_20);
  QtPrivate::SequentialValueTypeIsMetaType<QList<QDBusObjectPath>,true>::registerConverter();
  QtPrivate::SequentialValueTypeIsMetaType<QList<QDBusObjectPath>,true>::registerMutableView();
  QtPrivate::AssociativeContainerTransformationHelper<QList<QDBusObjectPath>,false>::
  registerConverter();
  QtPrivate::AssociativeContainerTransformationHelper<QList<QDBusObjectPath>,false>::
  registerMutableView();
  QtPrivate::IsPair<QList<QDBusObjectPath>>::registerConverter();
  QtPrivate::MetaTypeSmartPointerHelper<QList<QDBusObjectPath>,void>::registerConverter();
  QtPrivate::MetaTypeQFutureHelper<QList<QDBusObjectPath>>::registerConverter();
  local_18 = (char *)QMetaType::name((QMetaType *)&local_20);
  cVar1 = operator!=(param_1,&local_18);
  if (cVar1 != '\0') {
    QMetaType::registerNormalizedTypedef(param_1,local_20);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return iVar2;
}



// ==== 00232381  qScopeGuard<QMetaType::registerConverterImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerConverterImpl<QList<QDBusObjectPath>,
   QIterable<QMetaSequence> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type>
   qScopeGuard<QMetaType::registerConverterImpl<QList<QDBusObjectPath>, QIterable<QMetaSequence>
   >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerConverterImpl<QList<QDBusObjectPath>,
   QIterable<QMetaSequence> >(std::function<bool (void const*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerConverterImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerConverterImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerConverterImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void_const*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 0023252b  qScopeGuard<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>

/* QScopeGuard<std::decay<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,
   QIterable<QMetaSequence> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>::type>
   qScopeGuard<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>, QIterable<QMetaSequence>
   >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}>(QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,
   QIterable<QMetaSequence> >(std::function<bool (void*, void*)>, QMetaType,
   QMetaType)::{lambda()#1}&&) */

_lambda___1_ *
qScopeGuard<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
          (_lambda___1_ *param_1)

{
  _lambda___1_ *in_RSI;
  
  QScopeGuard<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::{lambda()#1}>
  ::QScopeGuard((QScopeGuard<QMetaType::registerMutableViewImpl<QList<QDBusObjectPath>,QIterable<QMetaSequence>>(std::function<bool(void*,void*)>,QMetaType,QMetaType)::_lambda()_1_>
                 *)param_1,in_RSI);
  return param_1;
}



// ==== 0023d14a  __static_initialization_and_destruction_0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* __static_initialization_and_destruction_0() */

void __static_initialization_and_destruction_0(void)

{
  __cxa_atexit(QList<QVariant>::~QList,(anonymous_namespace)::g_siAccum,&__dso_handle);
  __cxa_atexit(QList<QVariant>::~QList,(anonymous_namespace)::g_outAccum,&__dso_handle);
  __cxa_atexit(QList<QVariant>::~QList,(anonymous_namespace)::g_inAccum,&__dso_handle);
  return;
}



// ==== 0023f27a  qdbus_cast<QList<QString>>

/* QList<QString> qdbus_cast<QList<QString> >(QVariant const&) */

QVariant * qdbus_cast<QList<QString>>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QList<QString>>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QList<QString>>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0023ff50  qdbus_cast<unsigned_int>

/* unsigned int qdbus_cast<unsigned int>(QVariant const&) */

uint qdbus_cast<unsigned_int>(QVariant *param_1)

{
  char cVar1;
  uint uVar2;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(param_1);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    uVar2 = qvariant_cast<unsigned_int>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    uVar2 = qdbus_cast<unsigned_int>((QDBusArgument *)&local_28);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 002404f6  qdbus_cast<QList<QString>>

/* QList<QString> qdbus_cast<QList<QString> >(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QList<QString>>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined1 (*) [16])param_1 = (undefined1  [16])0x0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  QDBusArgument::operator>>(in_RSI,(QList *)param_1);
  return param_1;
}



// ==== 002405b5  qvariant_cast<QList<QString>>

/* QList<QString> qvariant_cast<QList<QString> >(QVariant const&) */

QVariant * qvariant_cast<QList<QString>>(QVariant *param_1)

{
  char cVar1;
  QList *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined8 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = &QtPrivate::QMetaTypeInterfaceWrapper<QList<QString>>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QList<QString>>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QList<QString>>(in_RSI);
    QList<QString>::QList((QList<QString> *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00241010  qdbus_cast<unsigned_int>

/* unsigned int qdbus_cast<unsigned int>(QDBusArgument const&) */

uint qdbus_cast<unsigned_int>(QDBusArgument *param_1)

{
  long in_FS_OFFSET;
  uint local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QDBusArgument::operator>>(param_1,&local_14);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_14;
}



// ==== 00241057  qvariant_cast<unsigned_int>

/* unsigned int qvariant_cast<unsigned int>(QVariant const&) */

uint qvariant_cast<unsigned_int>(QVariant *param_1)

{
  char cVar1;
  uint uVar2;
  uint *puVar3;
  long in_FS_OFFSET;
  undefined8 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = &QtPrivate::QMetaTypeInterfaceWrapper<unsigned_int>::metaType;
  local_18 = QVariant::Private::type((Private *)param_1);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    uVar2 = QtPrivate::qvariant_cast_qmetatype_converted<unsigned_int>(param_1,local_20);
  }
  else {
    puVar3 = QVariant::Private::get<unsigned_int>((Private *)param_1);
    uVar2 = *puVar3;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 0025cc7c  _ZZN9QtPrivate11FunctorCallISt16integer_sequenceImJEENS_4ListIJEEEvZZN5Lelan12refreshUsersEvENKUlvE_clEvEUlvE_E4callERS7_PPvENKUlvE_clEv

void _ZZN9QtPrivate11FunctorCallISt16integer_sequenceImJEENS_4ListIJEEEvZZN5Lelan12refreshUsersEvENKUlvE_clEvEUlvE_E4callERS7_PPvENKUlvE_clEv
               (undefined8 *param_1)

{
  const::{lambda()#1}::operator()((_lambda___1_ *)*param_1);
  return;
}



// ==== 0025d705  operator!=

/* bool TEMPNAMEPLACEHOLDERVALUE(QMap<QString, QVariant> const&, QMap<QString, QVariant> const&) */

bool operator!=(QMap *param_1,QMap *param_2)

{
  bool bVar1;
  
  bVar1 = comparesEqual<QString,QVariant,true>(param_1,param_2);
  return !bVar1;
}



// ==== 0025e138  qdbus_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > qdbus_cast<QMap<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> > > >(QVariant const&) */

QVariant * qdbus_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
                    /* try { // try from 0025e147 to 0035e14b has its CatchHandler @ 0025e1af */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
                    /* try { // try from 0025e16b to 0035e16f has its CatchHandler @ 0025e19e */
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
                    /* catch() { ... } // from try @ 0025e16b with catch @ 0025e19e */
    qdbus_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>((QDBusArgument *)param_1)
    ;
                    /* catch() { ... } // from try @ 0025e147 with catch @ 0025e1af */
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0025e744  qdbus_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > qdbus_cast<QMap<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> > > >(QDBusArgument const&) */

QDBusArgument *
qdbus_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined8 *)param_1 = 0;
  operator>>(in_RSI,(QMap *)param_1);
  return param_1;
}



// ==== 0025e799  qvariant_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > >
   qvariant_cast<QMap<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> > > >(QVariant const&)
    */

QVariant *
qvariant_cast<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(QVariant *param_1)

{
  char cVar1;
  QMap *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined1 *local_20;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = QtPrivate::
             QMetaTypeInterfaceWrapper<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::
             metaType;
                    /* catch() { ... } // from try @ 0025e8f7 with catch @ 0025e7c6 */
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::
    qvariant_cast_qmetatype_converted<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
              ((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
    pQVar2 = QVariant::Private::get<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>
                       (in_RSI);
                    /* try { // try from 0025e7fc to 0035e800 has its CatchHandler @ 0025e7c6 */
    QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>::QMap
              ((QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>> *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00264490  qdbus_cast<QString>

/* QString qdbus_cast<QString>(QVariant const&) */

QVariant * qdbus_cast<QString>(QVariant *param_1)

{
  char cVar1;
  QVariant *in_RSI;
  long in_FS_OFFSET;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QMetaType::fromType<QDBusArgument>();
  local_30 = QVariant::metaType(in_RSI);
  cVar1 = operator==((QMetaType *)&local_30,(QMetaType *)&local_28);
  if (cVar1 == '\0') {
    qvariant_cast<QString>(param_1);
  }
  else {
    qvariant_cast<QDBusArgument>((QVariant *)&local_28);
    qdbus_cast<QString>((QDBusArgument *)param_1);
    QDBusArgument::~QDBusArgument((QDBusArgument *)&local_28);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 002645d8  qdbus_cast<QString>

/* QString qdbus_cast<QString>(QDBusArgument const&) */

QDBusArgument * qdbus_cast<QString>(QDBusArgument *param_1)

{
  QDBusArgument *in_RSI;
  
  *(undefined8 *)param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  QDBusArgument::operator>>(in_RSI,(QString *)param_1);
  return param_1;
}



// ==== 00264645  qvariant_cast<QString>

/* QString qvariant_cast<QString>(QVariant const&) */

QVariant * qvariant_cast<QString>(QVariant *param_1)

{
  char cVar1;
  QString *pQVar2;
  Private *in_RSI;
  long in_FS_OFFSET;
  undefined8 *local_20;
  undefined8 local_18;
  long local_10;
  
                    /* try { // try from 0026465b to 0036465f has its CatchHandler @ 00264aba */
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_20 = &QtPrivate::QMetaTypeInterfaceWrapper<QString>::metaType;
  local_18 = QVariant::Private::type(in_RSI);
  cVar1 = operator==((QMetaType *)&local_18,(QMetaType *)&local_20);
  if (cVar1 == '\0') {
    QtPrivate::qvariant_cast_qmetatype_converted<QString>((QtPrivate *)param_1,in_RSI,local_20);
  }
  else {
                    /* try { // try from 0026469e to 003646a2 has its CatchHandler @ 00264a92 */
    pQVar2 = QVariant::Private::get<QString>(in_RSI);
    QString::QString((QString *)param_1,pQVar2);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0026479e  uid

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* uid() */

longlong uid(void)

{
  longlong in_RDI;
  long in_FS_OFFSET;
  QString local_58 [32];
  undefined1 local_38 [16];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = QUuid::createUuid();
  QUuid::toString(local_58,local_38,1);
  QString::left(in_RDI);
  QString::~QString(local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 00267895  icsEsc

/* icsEsc(QString const&) */

QString * icsEsc(QString *param_1)

{
  undefined8 uVar1;
  QString *in_RSI;
  long in_FS_OFFSET;
  QString local_118 [32];
  QString local_f8 [32];
  QString local_d8 [32];
  QString local_b8 [32];
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(param_1,in_RSI);
  QString::QString(local_f8,"\\\\");
  QString::QString(local_118,"\\");
  uVar1 = QString::replace(param_1,local_118,local_f8,1);
  QString::QString(local_b8,"\\;");
  QString::QString(local_d8,";");
  uVar1 = QString::replace(uVar1,local_d8,local_b8,1);
  QString::QString(local_78,"\\,");
  QString::QString(local_98,",");
                    /* catch() { ... } // from try @ 00267e2d with catch @ 002679b8 */
  uVar1 = QString::replace(uVar1,local_98,local_78,1);
  QString::QString(local_38,"\\n");
  QString::QString(local_58,"\n");
  QString::replace(uVar1,local_58,local_38,1);
  QString::~QString(local_58);
  QString::~QString(local_38);
  QString::~QString(local_98);
  QString::~QString(local_78);
  QString::~QString(local_d8);
  QString::~QString(local_b8);
                    /* try { // try from 00267a6d to 00367a71 has its CatchHandler @ 00267df2 */
  QString::~QString(local_118);
  QString::~QString(local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* try { // try from 00267a96 to 00367a9a has its CatchHandler @ 00267d43 */
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 00267b73  icsUnesc

/* icsUnesc(QString const&) */

QString * icsUnesc(QString *param_1)

{
  undefined8 uVar1;
  QString *in_RSI;
  long in_FS_OFFSET;
  QString aQStack_118 [32];
  QString local_f8 [32];
  QString aQStack_d8 [32];
  QString aQStack_b8 [32];
  QString aQStack_98 [32];
  QString aQStack_78 [32];
  QString aQStack_58 [32];
  QString aQStack_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::QString(param_1,in_RSI);
  QString::QString(local_f8,"\n");
  QString::QString(aQStack_118,"\\n");
  uVar1 = QString::replace(param_1,aQStack_118,local_f8,1);
  QString::QString(aQStack_b8,",");
  QString::QString(aQStack_d8,"\\,");
  uVar1 = QString::replace(uVar1,aQStack_d8,aQStack_b8,1);
  QString::QString(aQStack_78,";");
  QString::QString(aQStack_98,"\\;");
  uVar1 = QString::replace(uVar1,aQStack_98,aQStack_78,1);
  QString::QString(aQStack_38,"\\");
  QString::QString(aQStack_58,"\\\\");
  QString::replace(uVar1,aQStack_58,aQStack_38,1);
  QString::~QString(aQStack_58);
  QString::~QString(aQStack_38);
  QString::~QString(aQStack_98);
  QString::~QString(aQStack_78);
  QString::~QString(aQStack_d8);
  QString::~QString(aQStack_b8);
  QString::~QString(aQStack_118);
  QString::~QString(local_f8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0026cd33  hmFmtTime

/* hmFmtTime(int) */

undefined8 hmFmtTime(int param_1)

{
  char *pcVar1;
  int in_ESI;
  undefined4 in_register_0000003c;
  long in_FS_OFFSET;
  undefined2 local_aa;
  undefined2 local_a8;
  undefined2 local_a6;
  int local_a4;
  int local_a0;
  int local_9c;
  QString local_98 [32];
  QString local_78 [32];
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a0 = in_ESI / 0x3c;
  local_9c = in_ESI % 0x3c;
                    /* try { // try from 0026cdb1 to 0036cdb5 has its CatchHandler @ 0026db4d */
  if (local_a0 < 0xc) {
    pcVar1 = "AM";
  }
  else {
    pcVar1 = "PM";
  }
                    /* try { // try from 0026cdca to 0036cdce has its CatchHandler @ 0026d90b */
  QString::QString(local_98,pcVar1);
  local_a4 = local_a0 + ((local_a0 / 6 + (local_a0 >> 0x1f) >> 1) - (local_a0 >> 0x1f)) * -0xc;
                    /* try { // try from 0026ce08 to 0036ce0c has its CatchHandler @ 0026d947 */
  if (local_a4 == 0) {
    local_a4 = 0xc;
  }
                    /* try { // try from 0026ce26 to 0036ce2a has its CatchHandler @ 0026d933 */
  QString::QString(local_78,"%1:%2 %3");
                    /* try { // try from 0026ce3c to 0036ce40 has its CatchHandler @ 0026d922 */
  QChar::QChar<char16_t,true>((QChar *)&local_aa,L' ');
  QString::arg<int,true>(local_58,local_78,local_a4,0,10,local_aa);
  QChar::QChar<char,true>((QChar *)&local_a8,'0');
  QString::arg<int,true>(local_38,local_58,local_9c,2,10,local_a8);
                    /* try { // try from 0026cebe to 0036cec2 has its CatchHandler @ 0026db4d */
  QChar::QChar<char16_t,true>((QChar *)&local_a6,L' ');
                    /* try { // try from 0026ced7 to 0036cedb has its CatchHandler @ 0026d95b */
  QString::arg<QString,true>(CONCAT44(in_register_0000003c,param_1),local_38,local_98,0,local_a6);
  QString::~QString(local_38);
  QString::~QString(local_58);
  QString::~QString(local_78);
                    /* try { // try from 0026cf15 to 0036cf19 has its CatchHandler @ 0026d997 */
  QString::~QString(local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return CONCAT44(in_register_0000003c,param_1);
}



// ==== 0026e896  operator+

/* TEMPNAMEPLACEHOLDERVALUE(char const*, QString const&) */

QString * operator+(char *param_1,QString *param_2)

{
  QString *in_RDX;
  long in_FS_OFFSET;
  QString *local_48;
  QString *local_40;
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
                    /* try { // try from 0026e8af to 0036e8b3 has its CatchHandler @ 0026eaca */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = param_2;
  local_40 = (QString *)param_1;
                    /* try { // try from 0026e8c8 to 0036e8cc has its CatchHandler @ 0026eab9 */
  QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_38,(char **)&local_48);
  QString::fromUtf8(local_40,local_38,local_30);
  QString::operator+=(local_40,in_RDX);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}



// ==== 0026eace  _ZNSt4pairI7QString8QVariantEC2IRA12_KcbLb1EEEOT_OT0_

void _ZNSt4pairI7QString8QVariantEC2IRA12_KcbLb1EEEOT_OT0_
               (QString *param_1,char *param_2,undefined8 param_3)

{
  QString::QString(param_1,param_2);
  QVariant::QVariant((QVariant *)(param_1 + 0x18),*(bool *)param_3);
  return;
}



// ==== 00271240  qt_ptr_swap<QTypedArrayData<CalendarBackend::Snapshot>>

/* void qt_ptr_swap<QTypedArrayData<CalendarBackend::Snapshot>
   >(QTypedArrayData<CalendarBackend::Snapshot>*&, QTypedArrayData<CalendarBackend::Snapshot>*&) */

void qt_ptr_swap<QTypedArrayData<CalendarBackend::Snapshot>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 00271273  qt_ptr_swap<CalendarBackend::Snapshot>

/* void qt_ptr_swap<CalendarBackend::Snapshot>(CalendarBackend::Snapshot*&,
   CalendarBackend::Snapshot*&) */

void qt_ptr_swap<CalendarBackend::Snapshot>(Snapshot **param_1,Snapshot **param_2)

{
  Snapshot *pSVar1;
  
  pSVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pSVar1;
  return;
}



// ==== 00273d3e  kithGlassFill

/* kithGlassFill(double, double, double, double) */

QLinearGradient * kithGlassFill(double param_1,double param_2,double param_3,double param_4)

{
  QLinearGradient *in_RDI;
  long in_FS_OFFSET;
  QColor aQStack_38 [24];
  long lStack_20;
  
                    /* catch() { ... } // from try @ 00273a17 with catch @ 00273d3e */
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QLinearGradient::QLinearGradient(in_RDI,param_1,param_2,param_3,param_4);
  QColor::QColor(aQStack_38,"#7fd0f0");
  QGradient::setColorAt(0.0,(QColor *)in_RDI);
  QColor::QColor(aQStack_38,"#3a78c8");
  QGradient::setColorAt(0.5,(QColor *)in_RDI);
  QColor::QColor(aQStack_38,"#15306a");
  QGradient::setColorAt(1.0,(QColor *)in_RDI);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 00273e8b  kithRubyFill

/* kithRubyFill(double, double, double, double) */

QLinearGradient * kithRubyFill(double param_1,double param_2,double param_3,double param_4)

{
  QLinearGradient *in_RDI;
  long in_FS_OFFSET;
  QColor aQStack_38 [24];
  long lStack_20;
  
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QLinearGradient::QLinearGradient(in_RDI,param_1,param_2,param_3,param_4);
  QColor::QColor(aQStack_38,"#f08098");
  QGradient::setColorAt(0.0,(QColor *)in_RDI);
  QColor::QColor(aQStack_38,"#d33a52");
  QGradient::setColorAt(0.5,(QColor *)in_RDI);
  QColor::QColor(aQStack_38,"#7a1020");
  QGradient::setColorAt(1.0,(QColor *)in_RDI);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 00273fd8  kithCame

/* kithCame(QPainter&, QPainterPath const&, double) */

void kithCame(QPainter *param_1,QPainterPath *param_2,double param_3)

{
  long in_FS_OFFSET;
  QPen aQStack_40 [8];
  QColor local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QColor::QColor(local_38,"#0b0b14");
  QPen::QPen(aQStack_40,local_38);
  QPen::setWidthF(param_3);
  QPen::setJoinStyle(aQStack_40,0x80);
  QPen::setCapStyle(aQStack_40,0x20);
  QPainter::strokePath((QPainterPath *)param_1,(QPen *)param_2);
  QPen::~QPen(aQStack_40);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002740ca  kithSheen

/* kithSheen(QPainter&, double, double, double, double) */

void kithSheen(QPainter *param_1,double param_2,double param_3,double param_4,double param_5)

{
  long in_FS_OFFSET;
  QBrush aQStack_c0 [8];
  QRectF aQStack_b8 [32];
  QLinearGradient local_98 [96];
  QColor local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QLinearGradient::QLinearGradient(local_98,param_2,param_3,param_2,param_5 * 0.6 + param_3);
  QColor::QColor(local_38,0xff,0xff,0xff,0x80);
  QGradient::setColorAt(0.0,(QColor *)local_98);
  QColor::QColor(local_38,0xff,0xff,0xff,0);
  QGradient::setColorAt(1.0,(QColor *)local_98);
  QBrush::QBrush(aQStack_c0,(QGradient *)local_98);
  QRectF::QRectF(aQStack_b8,param_2,param_3,param_4,param_5);
  QPainter::fillRect((QRectF *)param_1,(QBrush *)aQStack_b8);
  QBrush::~QBrush(aQStack_c0);
  QLinearGradient::~QLinearGradient(local_98);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 002742e0  renderKithArrow

/* renderKithArrow(int) */

QImage * renderKithArrow(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  QPainter local_148 [8];
  QPainterPath local_140 [8];
  QPen local_138 [8];
  QPen local_130 [8];
  QBrush local_128 [8];
  double local_120;
  QPointF local_118 [32];
  QLinearGradient local_f8 [96];
  QBrush local_98 [96];
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(local_148,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(local_148,1,1);
  QPainter::translate(local_148,6.0,6.0);
  local_120 = (double)in_ESI;
  QPainterPath::QPainterPath(local_140);
  QPainterPath::moveTo(local_140,local_120 * 0.16,local_120 * 0.06);
  QPainterPath::lineTo(local_140,local_120 * 0.16,local_120 * 0.78);
  QPainterPath::lineTo(local_140,local_120 * 0.34,local_120 * 0.6);
  QPainterPath::lineTo(local_140,local_120 * 0.46,local_120 * 0.86);
  QPainterPath::lineTo(local_140,local_120 * 0.58,local_120 * 0.8);
  QPainterPath::lineTo(local_140,local_120 * 0.46,local_120 * 0.54);
  QPainterPath::lineTo(local_140,local_120 * 0.7,local_120 * 0.54);
  QPainterPath::closeSubpath();
  QLinearGradient::QLinearGradient
            (local_f8,local_120 * 0.16,local_120 * 0.06,local_120 * 0.6,local_120 * 0.86);
  QColor::QColor((QColor *)&local_38,"#7fd0f0");
  QGradient::setColorAt(0.0,(QColor *)local_f8);
  QColor::QColor((QColor *)&local_38,"#3a78c8");
  QGradient::setColorAt(0.5,(QColor *)local_f8);
  QColor::QColor((QColor *)&local_38,"#15306a");
  QGradient::setColorAt(1.0,(QColor *)local_f8);
  QBrush::QBrush(local_98,(QGradient *)local_f8);
  QPainter::fillPath((QPainterPath *)local_148,(QBrush *)local_140);
  QBrush::~QBrush(local_98);
  QColor::QColor((QColor *)&local_38,"#0b0b14");
  QPen::QPen(local_138,(QColor *)&local_38);
  QPen::setWidthF(local_120 * 0.07);
  QPen::setJoinStyle(local_138,0x80);
  QPen::setCapStyle(local_138,0x20);
  QPainter::strokePath((QPainterPath *)local_148,(QPen *)local_140);
  QPainter::save();
  QPainter::setClipPath(local_148,local_140,1);
  QColor::QColor((QColor *)&local_38,0xbf,0xe6,0xfb,0xcc);
  QPen::QPen(local_130,(QColor *)&local_38);
  QPen::setWidthF(local_120 * 0.03);
  QPainter::setPen(local_148,local_130);
  QPointF::QPointF((QPointF *)local_98,local_120 * 0.2,local_120 * 0.62);
  QPointF::QPointF(local_118,local_120 * 0.2,local_120 * 0.12);
  QPainter::drawLine(local_148,local_118,(QPointF *)local_98);
  QLinearGradient::QLinearGradient
            ((QLinearGradient *)local_98,local_120 * 0.1,local_120 * 0.04,local_120 * 0.1,
             local_120 * 0.04 + local_120 * 0.5 * 0.6);
  QColor::QColor((QColor *)&local_38,0xff,0xff,0xff,0x80);
  QGradient::setColorAt(0.0,(QColor *)local_98);
  QColor::QColor((QColor *)&local_38,0xff,0xff,0xff,0);
  QGradient::setColorAt(1.0,(QColor *)local_98);
  QBrush::QBrush(local_128,(QGradient *)local_98);
  QRectF::QRectF((QRectF *)local_118,local_120 * 0.1,local_120 * 0.04,local_120 * 0.4,
                 local_120 * 0.5);
  QPainter::fillRect((QRectF *)local_148,(QBrush *)local_118);
  QBrush::~QBrush(local_128);
  QPainter::restore();
  QPainter::setPen(local_148,0);
  QColor::QColor((QColor *)&local_38,"#fff0c0");
  QPainter::setBrush(local_148,local_38,local_30);
  dVar2 = local_120 * 0.035;
  dVar3 = local_120 * 0.035;
  QPointF::QPointF(local_118,local_120 * 0.26,local_120 * 0.2);
  QPainter::drawEllipse(local_148,local_118,dVar3,dVar2);
  QPainter::end();
  QLinearGradient::~QLinearGradient((QLinearGradient *)local_98);
  QPen::~QPen(local_130);
  QPen::~QPen(local_138);
  QLinearGradient::~QLinearGradient(local_f8);
  QPainterPath::~QPainterPath(local_140);
  QPainter::~QPainter(local_148);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 00274d8d  renderKithPointer

/* renderKithPointer(int) */

QImage * renderKithPointer(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  QPainter local_f8 [8];
  QPainterPath local_f0 [8];
  QPen aQStack_e8 [8];
  double *pdStack_e0;
  double local_d8;
  double *pdStack_d0;
  double *pdStack_c8;
  double dStack_c0;
  QBrush aQStack_b8 [16];
  QGradient aQStack_a8 [96];
  undefined8 uStack_48;
  undefined8 uStack_40;
  double adStack_38 [5];
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  adStack_38[3] = *(double *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(local_f8,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(local_f8,1,1);
  QPainter::translate(local_f8,6.0,6.0);
  local_d8 = (double)in_ESI;
  QPainterPath::QPainterPath(local_f0);
  QPainterPath::moveTo(local_f0,local_d8 * 0.36,local_d8 * 0.06);
  QPainterPath::lineTo(local_f0,local_d8 * 0.36,local_d8 * 0.46);
  QPainterPath::lineTo(local_f0,local_d8 * 0.3,local_d8 * 0.4);
  QPainterPath::lineTo(local_f0,local_d8 * 0.22,local_d8 * 0.48);
  QPainterPath::cubicTo
            (local_f0,local_d8 * 0.2,local_d8 * 0.54,local_d8 * 0.24,local_d8 * 0.62,local_d8 * 0.3,
             local_d8 * 0.72);
  QPainterPath::lineTo(local_f0,local_d8 * 0.34,local_d8 * 0.9);
  QPainterPath::lineTo(local_f0,local_d8 * 0.72,local_d8 * 0.9);
  QPainterPath::lineTo(local_f0,local_d8 * 0.78,local_d8 * 0.56);
  QPainterPath::lineTo(local_f0,local_d8 * 0.74,local_d8 * 0.4);
  QPainterPath::lineTo(local_f0,local_d8 * 0.68,local_d8 * 0.44);
  QPainterPath::lineTo(local_f0,local_d8 * 0.66,local_d8 * 0.4);
  QPainterPath::lineTo(local_f0,local_d8 * 0.6,local_d8 * 0.44);
  QPainterPath::lineTo(local_f0,local_d8 * 0.58,local_d8 * 0.4);
  QPainterPath::lineTo(local_f0,local_d8 * 0.52,local_d8 * 0.44);
  QPainterPath::lineTo(local_f0,local_d8 * 0.5,local_d8 * 0.3);
  QPainterPath::lineTo(local_f0,local_d8 * 0.44,local_d8 * 0.3);
  QPainterPath::lineTo(local_f0,local_d8 * 0.44,local_d8 * 0.06);
  QPainterPath::closeSubpath();
  kithGlassFill(local_d8 * 0.2,local_d8 * 0.06,local_d8 * 0.8,local_d8 * 0.9);
  QBrush::QBrush(aQStack_b8,aQStack_a8);
  QPainter::fillPath((QPainterPath *)local_f8,(QBrush *)local_f0);
  QBrush::~QBrush(aQStack_b8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_a8);
  kithCame(local_f8,local_f0,local_d8 * 0.065);
  QPainter::save();
  QPainter::setClipPath(local_f8,local_f0,1);
  kithSheen(local_f8,local_d8 * 0.2,local_d8 * 0.04,local_d8 * 0.6,local_d8 * 0.5);
  QPainter::restore();
  QColor::QColor((QColor *)adStack_38,0xb,0xb,0x14,0x8c);
  QPen::QPen(aQStack_e8,(QColor *)adStack_38);
  QPen::setWidthF(local_d8 * 0.025);
  QPainter::setPen(local_f8,aQStack_e8);
  adStack_38[0] = 0.52;
  adStack_38[1] = 0.6;
  adStack_38[2] = 0.68;
  pdStack_c8 = adStack_38 + 3;
  pdStack_e0 = adStack_38;
  pdStack_d0 = pdStack_e0;
  for (; pdStack_e0 != pdStack_c8; pdStack_e0 = pdStack_e0 + 1) {
    dStack_c0 = *pdStack_e0;
    QPointF::QPointF((QPointF *)aQStack_a8,dStack_c0 * local_d8,local_d8 * 0.78);
    QPointF::QPointF((QPointF *)aQStack_b8,dStack_c0 * local_d8,local_d8 * 0.5);
    QPainter::drawLine(local_f8,(QPointF *)aQStack_b8,(QPointF *)aQStack_a8);
  }
  QPainter::setPen(local_f8,0);
  QColor::QColor((QColor *)&uStack_48,"#fff0c0");
  QPainter::setBrush(local_f8,uStack_48,uStack_40);
  dVar2 = local_d8 * 0.03;
  dVar3 = local_d8 * 0.03;
  QPointF::QPointF((QPointF *)aQStack_a8,local_d8 * 0.4,local_d8 * 0.12);
  QPainter::drawEllipse(local_f8,(QPointF *)aQStack_a8,dVar3,dVar2);
  QPainter::end();
  QPen::~QPen(aQStack_e8);
  QPainterPath::~QPainterPath(local_f0);
  QPainter::~QPainter(local_f8);
  if (adStack_38[3] != (double)*(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 0027590b  renderKithText

/* renderKithText(int) */

QImage * renderKithText(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  QPainter local_b8 [8];
  QPainterPath local_b0 [8];
  QBrush aQStack_a8 [8];
  double local_a0;
  QRectF local_98 [96];
  undefined8 uStack_38;
  undefined8 uStack_30;
  long local_20;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(local_b8,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(local_b8,1,1);
  QPainter::translate(local_b8,6.0,6.0);
  local_a0 = (double)in_ESI;
  QPainterPath::QPainterPath(local_b0);
  QRectF::QRectF(local_98,local_a0 * 0.44,local_a0 * 0.12,local_a0 * 0.12,local_a0 * 0.76);
  QPainterPath::addRect((QRectF *)local_b0);
  QRectF::QRectF(local_98,local_a0 * 0.32,local_a0 * 0.12,local_a0 * 0.36,local_a0 * 0.1);
  QPainterPath::addRect((QRectF *)local_b0);
  QRectF::QRectF(local_98,local_a0 * 0.32,local_a0 * 0.78,local_a0 * 0.36,local_a0 * 0.1);
  QPainterPath::addRect((QRectF *)local_b0);
  kithGlassFill(local_a0 * 0.3,local_a0 * 0.1,local_a0 * 0.7,local_a0 * 0.9);
  QBrush::QBrush(aQStack_a8,(QGradient *)local_98);
  QPainter::fillPath((QPainterPath *)local_b8,(QBrush *)local_b0);
  QBrush::~QBrush(aQStack_a8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)local_98);
  kithCame(local_b8,local_b0,local_a0 * 0.05);
  QPainter::setPen(local_b8,0);
  QColor::QColor((QColor *)&uStack_38,"#fff0c0");
  QPainter::setBrush(local_b8,uStack_38,uStack_30);
  dVar2 = local_a0 * 0.03;
  dVar3 = local_a0 * 0.03;
  QPointF::QPointF((QPointF *)local_98,local_a0 * 0.5,local_a0 * 0.22);
  QPainter::drawEllipse(local_b8,(QPointF *)local_98,dVar3,dVar2);
  QPainter::end();
  QPainterPath::~QPainterPath(local_b0);
  QPainter::~QPainter(local_b8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 00275f5c  renderKithWait

/* renderKithWait(int) */

QImage * renderKithWait(int param_1)

{
  QList<QPointF> *pQVar1;
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar2;
  long in_FS_OFFSET;
  double dVar3;
  double dVar4;
  uint uStack_138;
  QPainter aQStack_128 [8];
  double dStack_120;
  double dStack_118;
  double dStack_110;
  double dStack_108;
  double dStack_100;
  double dStack_f8;
  double dStack_f0;
  double *pdStack_e8;
  double *pdStack_e0;
  undefined8 uStack_d8;
  double dStack_d0;
  undefined8 uStack_c8;
  double dStack_c0;
  undefined8 uStack_b8;
  double dStack_b0;
  undefined8 uStack_a8;
  double dStack_a0;
  QPointF aQStack_98 [16];
  undefined8 uStack_88;
  undefined8 uStack_38;
  undefined8 uStack_30;
  long lStack_20;
  
  pQVar2 = (QImage *)CONCAT44(in_register_0000003c,param_1);
                    /* try { // try from 00275f60 to 00375ff8 has its CatchHandler @ 00275c7e */
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar2,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar2,0x13);
  QPainter::QPainter(aQStack_128,(QPaintDevice *)pQVar2);
  QPainter::setRenderHint(aQStack_128,1,1);
  QPainter::translate(aQStack_128,6.0,6.0);
  dStack_110 = (double)in_ESI;
  dStack_120 = dStack_110 * 0.5;
  dStack_118 = dStack_110 * 0.5;
  dStack_108 = dStack_110 * 0.42;
  QPainter::setPen(aQStack_128,0);
  QColor::QColor((QColor *)&uStack_38,"#0b0b14");
  QPainter::setBrush(aQStack_128,uStack_38,uStack_30);
  QPointF::QPointF(aQStack_98,dStack_120,dStack_118);
  QPainter::drawEllipse(aQStack_128,aQStack_98,dStack_108,dStack_108);
  pdStack_e8 = &dStack_120;
  pdStack_e0 = &dStack_118;
  for (uStack_138 = 0; (int)uStack_138 < 0xc; uStack_138 = uStack_138 + 1) {
    dVar3 = ((double)(int)uStack_138 / 12.0 + (double)(int)uStack_138 / 12.0) * 3.141592653589793 +
            0.06;
    dVar4 = (double)(int)(uStack_138 + 1) / 12.0;
    dStack_f8 = (dVar4 + dVar4) * 3.141592653589793 - 0.06;
    aQStack_98[0] = (QPointF)0x0;
    aQStack_98[1] = (QPointF)0x0;
    aQStack_98[2] = (QPointF)0x0;
    aQStack_98[3] = (QPointF)0x0;
    aQStack_98[4] = (QPointF)0x0;
    aQStack_98[5] = (QPointF)0x0;
    aQStack_98[6] = (QPointF)0x0;
    aQStack_98[7] = (QPointF)0x0;
    aQStack_98[8] = (QPointF)0x0;
    aQStack_98[9] = (QPointF)0x0;
    aQStack_98[10] = (QPointF)0x0;
    aQStack_98[0xb] = (QPointF)0x0;
    aQStack_98[0xc] = (QPointF)0x0;
    aQStack_98[0xd] = (QPointF)0x0;
    aQStack_98[0xe] = (QPointF)0x0;
    aQStack_98[0xf] = (QPointF)0x0;
    uStack_88 = 0;
    dStack_100 = dVar3;
    uStack_d8 = renderKithWait(int)::{lambda(double,double)#1}::operator()
                          ((_lambda_double_double__1_ *)&pdStack_e8,dStack_108 * 0.94,dVar3);
    dStack_d0 = dVar3;
    pQVar1 = (QList<QPointF> *)
             QList<QPointF>::operator<<((QList<QPointF> *)aQStack_98,(QPointF *)&uStack_d8);
    dVar3 = dStack_f8;
    uStack_c8 = renderKithWait(int)::{lambda(double,double)#1}::operator()
                          ((_lambda_double_double__1_ *)&pdStack_e8,dStack_108 * 0.94,dStack_f8);
    dStack_c0 = dVar3;
    pQVar1 = (QList<QPointF> *)QList<QPointF>::operator<<(pQVar1,(QPointF *)&uStack_c8);
    dVar3 = dStack_f8;
    uStack_b8 = renderKithWait(int)::{lambda(double,double)#1}::operator()
                          ((_lambda_double_double__1_ *)&pdStack_e8,dStack_108 * 0.52,dStack_f8);
    dStack_b0 = dVar3;
    pQVar1 = (QList<QPointF> *)QList<QPointF>::operator<<(pQVar1,(QPointF *)&uStack_b8);
    dVar3 = dStack_100;
    uStack_a8 = renderKithWait(int)::{lambda(double,double)#1}::operator()
                          ((_lambda_double_double__1_ *)&pdStack_e8,dStack_108 * 0.52,dStack_100);
    dStack_a0 = dVar3;
    QList<QPointF>::operator<<(pQVar1,(QPointF *)&uStack_a8);
    dStack_f0 = (double)(int)uStack_138 / 12.0;
    if ((uStack_138 & 1) == 0) {
      QColor::QColor((QColor *)&uStack_38,"#3a78c8");
    }
    else {
      QColor::QColor((QColor *)&uStack_38,"#eef4f8");
    }
    dVar3 = pow(dStack_f0,1.5);
    QColor::setAlphaF((float)(dVar3 * 0.6 + 0.4));
    QPainter::setBrush(aQStack_128,uStack_38,uStack_30);
    QPainter::drawPolygon(aQStack_128,aQStack_98,0);
    QPolygonF::~QPolygonF((QPolygonF *)aQStack_98);
  }
  QColor::QColor((QColor *)&uStack_38,"#0b0b14");
  QPen::QPen((QPen *)&uStack_c8,(QColor *)&uStack_38);
  QPen::setWidthF(dStack_110 * 0.05);
  QPainter::setPen(aQStack_128,(QPen *)&uStack_c8);
  QPainter::setBrush(aQStack_128,0);
  dVar3 = dStack_108 * 0.52;
  dVar4 = dStack_108 * 0.52;
  QPointF::QPointF(aQStack_98,dStack_120,dStack_118);
  QPainter::drawEllipse(aQStack_128,aQStack_98,dVar4,dVar3);
  QPen::setWidthF(dStack_110 * 0.035);
  QPainter::setPen(aQStack_128,(QPen *)&uStack_c8);
  dVar3 = dStack_108 * 0.96;
  dVar4 = dStack_108 * 0.96;
  QPointF::QPointF(aQStack_98,dStack_120,dStack_118);
  QPainter::drawEllipse(aQStack_128,aQStack_98,dVar4,dVar3);
  QRadialGradient::QRadialGradient
            ((QRadialGradient *)aQStack_98,dStack_120,dStack_118,dStack_108 * 0.3,
             dStack_120 - dStack_108 * 0.1,dStack_118 - dStack_108 * 0.1);
  QColor::QColor((QColor *)&uStack_38,"#fff0c0");
  QGradient::setColorAt(0.0,(QColor *)aQStack_98);
  QColor::QColor((QColor *)&uStack_38,"#e6c785");
  QGradient::setColorAt(1.0,(QColor *)aQStack_98);
  QPainter::setPen(aQStack_128,0);
  QBrush::QBrush((QBrush *)&uStack_a8,(QGradient *)aQStack_98);
  QPainter::setBrush(aQStack_128,(QBrush *)&uStack_a8);
  QBrush::~QBrush((QBrush *)&uStack_a8);
  dVar3 = dStack_108 * 0.3;
  dVar4 = dStack_108 * 0.3;
  QPointF::QPointF((QPointF *)&uStack_a8,dStack_120,dStack_118);
  QPainter::drawEllipse(aQStack_128,(QPointF *)&uStack_a8,dVar4,dVar3);
  QColor::QColor((QColor *)&uStack_38,"#0b0b14");
  QPen::QPen((QPen *)&uStack_b8,(QColor *)&uStack_38);
  QPen::setWidthF(dStack_110 * 0.03);
  QPainter::setPen(aQStack_128,(QPen *)&uStack_b8);
  QPainter::setBrush(aQStack_128,0);
  dVar3 = dStack_108 * 0.3;
  dVar4 = dStack_108 * 0.3;
  QPointF::QPointF((QPointF *)&uStack_a8,dStack_120,dStack_118);
  QPainter::drawEllipse(aQStack_128,(QPointF *)&uStack_a8,dVar4,dVar3);
  QPainter::end();
  QPen::~QPen((QPen *)&uStack_b8);
  QRadialGradient::~QRadialGradient((QRadialGradient *)aQStack_98);
  QPen::~QPen((QPen *)&uStack_c8);
  QPainter::~QPainter(aQStack_128);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar2;
}



// ==== 00276a78  renderKithHelp

/* renderKithHelp(int) */

QImage * renderKithHelp(int param_1)

{
  QFont *pQVar1;
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar2;
  long in_FS_OFFSET;
  double dVar3;
  double dVar4;
  QPainter local_130 [8];
  QPainterPath local_128 [8];
  QPen aQStack_120 [8];
  QPainterPath aQStack_118 [8];
  QPen aQStack_110 [8];
  double local_108;
  double local_100;
  wchar16 *pwStack_f8;
  undefined *puStack_f0;
  QFont aQStack_e8 [16];
  QArrayDataPointer<char16_t> aQStack_d8 [32];
  QBrush aQStack_b8 [32];
  QGradient aQStack_98 [96];
  undefined8 uStack_38;
  undefined8 uStack_30;
  long local_20;
  
  pQVar2 = (QImage *)CONCAT44(in_register_0000003c,param_1);
                    /* try { // try from 00276a88 to 00376a8c has its CatchHandler @ 00276cdb */
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 00276aa3 to 00376ace has its CatchHandler @ 00276d3f */
  QImage::QImage(pQVar2,in_ESI + 0xc,in_ESI + 0xc,6);
                    /* try { // try from 00276ae0 to 00376ae4 has its CatchHandler @ 00276cec */
  QImage::fill(pQVar2,0x13);
  QPainter::QPainter(local_130,(QPaintDevice *)pQVar2);
  QPainter::setRenderHint(local_130,1,1);
  QPainter::translate(local_130,6.0,6.0);
  local_108 = (double)in_ESI;
  local_100 = local_108 * 0.78;
                    /* try { // try from 00276b83 to 00376b87 has its CatchHandler @ 00276d1f */
  QPainterPath::QPainterPath(local_128);
  QPainterPath::moveTo(local_128,local_100 * 0.16,local_100 * 0.06);
                    /* try { // try from 00276be3 to 00376be7 has its CatchHandler @ 00276d0e */
  QPainterPath::lineTo(local_128,local_100 * 0.16,local_100 * 0.78);
  QPainterPath::lineTo(local_128,local_100 * 0.34,local_100 * 0.6);
                    /* try { // try from 00276c6c to 00376c70 has its CatchHandler @ 00276cfd */
  QPainterPath::lineTo(local_128,local_100 * 0.46,local_100 * 0.86);
  QPainterPath::lineTo(local_128,local_100 * 0.58,local_100 * 0.8);
  QPainterPath::lineTo(local_128,local_100 * 0.46,local_100 * 0.54);
  QPainterPath::lineTo(local_128,local_100 * 0.7,local_100 * 0.54);
  QPainterPath::closeSubpath();
  kithGlassFill(local_100 * 0.16,local_100 * 0.06,local_100 * 0.6,local_100 * 0.86);
  QBrush::QBrush(aQStack_b8,aQStack_98);
  QPainter::fillPath((QPainterPath *)local_130,(QBrush *)local_128);
  QBrush::~QBrush(aQStack_b8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_98);
  kithCame(local_130,local_128,local_100 * 0.07);
  QPainter::save();
  QPainter::setClipPath(local_130,local_128,1);
  QColor::QColor((QColor *)&uStack_38,0xbf,0xe6,0xfb,0xcc);
  QPen::QPen(aQStack_120,(QColor *)&uStack_38);
  QPen::setWidthF(local_100 * 0.03);
  QPainter::setPen(local_130,aQStack_120);
  QPointF::QPointF((QPointF *)aQStack_98,local_100 * 0.2,local_100 * 0.62);
  QPointF::QPointF((QPointF *)aQStack_b8,local_100 * 0.2,local_100 * 0.12);
  QPainter::drawLine(local_130,(QPointF *)aQStack_b8,(QPointF *)aQStack_98);
  kithSheen(local_130,local_100 * 0.1,local_100 * 0.04,local_100 * 0.4,local_100 * 0.5);
  QPainter::restore();
  QPainter::setPen(local_130,0);
  QColor::QColor((QColor *)&uStack_38,"#fff0c0");
  QPainter::setBrush(local_130,uStack_38,uStack_30);
  dVar3 = local_100 * 0.035;
  dVar4 = local_100 * 0.035;
  QPointF::QPointF((QPointF *)aQStack_98,local_100 * 0.26,local_100 * 0.2);
  QPainter::drawEllipse(local_130,(QPointF *)aQStack_98,dVar4,dVar3);
  QPainter::save();
  QPainter::translate(local_130,local_108 * 0.52,local_108 * 0.52);
  QPainterPath::QPainterPath(aQStack_118);
  dVar3 = local_108 * 0.26;
  dVar4 = local_108 * 0.26;
  QPointF::QPointF((QPointF *)aQStack_98,0.0,0.0);
  QPainterPath::addEllipse(aQStack_118,(QPointF *)aQStack_98,dVar4,dVar3);
  kithRubyFill(-local_108 * 0.2,-local_108 * 0.2,local_108 * 0.2,local_108 * 0.2);
  QBrush::QBrush(aQStack_b8,aQStack_98);
  QPainter::fillPath((QPainterPath *)local_130,(QBrush *)aQStack_118);
  QBrush::~QBrush(aQStack_b8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_98);
  QColor::QColor((QColor *)&uStack_38,"#0b0b14");
  QPen::QPen(aQStack_110,(QColor *)&uStack_38);
  QPen::setWidthF(local_108 * 0.045);
  QPainter::setPen(local_130,aQStack_110);
  QPainter::setBrush(local_130,0);
  QPainter::drawPath((QPainterPath *)local_130);
  QColor::QColor((QColor *)&uStack_38,"#fff0c0");
  QPainter::setPen((QColor *)local_130);
  pQVar1 = (QFont *)QPainter::font();
  QFont::QFont(aQStack_e8,pQVar1);
  QFont::setBold(aQStack_e8,true);
  pwStack_f8 = L"serif";
  QArrayDataPointer<char16_t>::QArrayDataPointer
            ((QArrayDataPointer<char16_t> *)aQStack_b8,(QTypedArrayData *)0x0,L"serif",5);
  QString::QString((QString *)aQStack_98,(QArrayDataPointer *)aQStack_b8);
  QFont::setFamily((QString *)aQStack_e8);
  QString::~QString((QString *)aQStack_98);
  QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)aQStack_b8);
  qRound(local_108 * 0.34);
  QFont::setPixelSize((int)aQStack_e8);
  QPainter::setFont((QFont *)local_130);
  puStack_f0 = &DAT_002aefc4;
  QArrayDataPointer<char16_t>::QArrayDataPointer(aQStack_d8,(QTypedArrayData *)0x0,L"?",1);
  QString::QString((QString *)aQStack_b8,(QArrayDataPointer *)aQStack_d8);
  QRectF::QRectF((QRectF *)aQStack_98,-local_108 * 0.3,-local_108 * 0.3,local_108 * 0.6,
                 local_108 * 0.6);
  QPainter::drawText((QRectF *)local_130,(int)aQStack_98,(QString *)0x84,(QRectF *)aQStack_b8);
  QString::~QString((QString *)aQStack_b8);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(aQStack_d8);
  QPainter::restore();
  QPainter::end();
  QFont::~QFont(aQStack_e8);
  QPen::~QPen(aQStack_110);
  QPainterPath::~QPainterPath(aQStack_118);
  QPen::~QPen(aQStack_120);
  QPainterPath::~QPainterPath(local_128);
  QPainter::~QPainter(local_130);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar2;
}



// ==== 00277811  renderKithMove

/* renderKithMove(int) */

QImage * renderKithMove(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  undefined1 auVar4 [16];
  int iStack_1b8;
  int iStack_1b4;
  QPainter aQStack_1a8 [8];
  QPainterPath aQStack_1a0 [8];
  double dStack_198;
  double dStack_190;
  double dStack_188;
  double dStack_180;
  double dStack_178;
  double dStack_170;
  undefined1 auStack_168 [16];
  QPointF aQStack_158 [16];
  undefined1 aauStack_148 [6] [16];
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  QPointF aQStack_98 [16];
  QPointF aQStack_88 [16];
  QPointF aQStack_78 [16];
  QPointF aQStack_68 [16];
  QPointF aQStack_58 [16];
  QPointF aQStack_48 [16];
  QPointF aQStack_38 [24];
  long lStack_20;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  lStack_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(aQStack_1a8,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(aQStack_1a8,1,1);
  QPainter::translate(aQStack_1a8,6.0,6.0);
  dStack_198 = (double)in_ESI;
  dStack_190 = dStack_198 * 0.5;
  dStack_188 = dStack_198 * 0.5;
  dStack_180 = dStack_198 * 0.4;
  dStack_178 = dStack_198 * 0.1;
  dStack_170 = dStack_198 * 0.18;
  QPointF::QPointF(aQStack_98,-dStack_178,-dStack_178);
  QPointF::QPointF(aQStack_88,-dStack_178,dStack_170 - dStack_180);
  QPointF::QPointF(aQStack_78,-dStack_170,dStack_170 - dStack_180);
  QPointF::QPointF(aQStack_68,0.0,-dStack_180);
  QPointF::QPointF(aQStack_58,dStack_170,dStack_170 - dStack_180);
  QPointF::QPointF(aQStack_48,dStack_178,dStack_170 - dStack_180);
  QPointF::QPointF(aQStack_38,dStack_178,-dStack_178);
  QPainterPath::QPainterPath(aQStack_1a0);
  for (iStack_1b8 = 0; iStack_1b8 < 4; iStack_1b8 = iStack_1b8 + 1) {
    QTransform::QTransform((QTransform *)&uStack_e8);
    QTransform::rotate((double)iStack_1b8 * 90.0,&uStack_e8,2);
    QPointF::QPointF(aQStack_158,dStack_190,dStack_188);
    auVar4 = QTransform::map((QPointF *)&uStack_e8);
    auStack_168 = auVar4;
    auVar4 = operator+((QPointF *)auStack_168,aQStack_158);
    aauStack_148[0] = auVar4;
    QPainterPath::moveTo((QPointF *)aQStack_1a0);
    for (iStack_1b4 = 1; iStack_1b4 < 7; iStack_1b4 = iStack_1b4 + 1) {
      QPointF::QPointF(aQStack_158,dStack_190,dStack_188);
      auVar4 = QTransform::map((QPointF *)&uStack_e8);
      auStack_168 = auVar4;
      auVar4 = operator+((QPointF *)auStack_168,aQStack_158);
      aauStack_148[0] = auVar4;
      QPainterPath::lineTo((QPointF *)aQStack_1a0);
    }
  }
  kithGlassFill(dStack_190 - dStack_198 * 0.4,dStack_188 - dStack_198 * 0.4,
                dStack_198 * 0.4 + dStack_190,dStack_198 * 0.4 + dStack_188);
  QBrush::QBrush((QBrush *)aQStack_158,(QGradient *)aauStack_148);
  QPainter::fillPath((QPainterPath *)aQStack_1a8,(QBrush *)aQStack_1a0);
  QBrush::~QBrush((QBrush *)aQStack_158);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aauStack_148);
  kithCame(aQStack_1a8,aQStack_1a0,dStack_198 * 0.055);
  QPainter::setPen(aQStack_1a8,0);
  QColor::QColor((QColor *)&uStack_e8,"#fff0c0");
  QPainter::setBrush(aQStack_1a8,uStack_e8,uStack_e0);
  dVar2 = dStack_198 * 0.05;
  dVar3 = dStack_198 * 0.05;
  QPointF::QPointF((QPointF *)aauStack_148,dStack_190,dStack_188);
  QPainter::drawEllipse(aQStack_1a8,(QPointF *)aauStack_148,dVar3,dVar2);
  QPainter::end();
  QPainterPath::~QPainterPath(aQStack_1a0);
  QPainter::~QPainter(aQStack_1a8);
  if (lStack_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 00277fc1  renderKithResize

/* renderKithResize(int, double) */

QImage * renderKithResize(int param_1,double param_2)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  undefined8 uVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  undefined1 auVar7 [16];
  int iStack_264;
  QPainter aQStack_258 [8];
  QPainterPath aQStack_250 [8];
  double dStack_248;
  double dStack_240;
  double dStack_238;
  double dStack_230;
  double dStack_228;
  double dStack_220;
  QPointF aQStack_218 [16];
  QPointF aQStack_208 [16];
  QPointF aQStack_1f8 [16];
  QPointF aQStack_1e8 [16];
  QPointF aQStack_1d8 [96];
  undefined8 uStack_178;
  undefined8 uStack_170;
  QTransform aQStack_168 [80];
  QPointF aQStack_118 [16];
  QPointF aQStack_108 [16];
  QPointF aQStack_f8 [16];
  QPointF aQStack_e8 [16];
  QPointF aQStack_d8 [16];
  QPointF aQStack_c8 [16];
  QPointF aQStack_b8 [16];
  QPointF aQStack_a8 [16];
  QPointF aQStack_98 [16];
  QPointF aQStack_88 [16];
  QPointF aQStack_78 [16];
  QPointF aQStack_68 [16];
  QPointF aQStack_58 [16];
  QPointF aQStack_48 [24];
  long lStack_30;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  lStack_30 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(aQStack_258,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(aQStack_258,1,1);
  QPainter::translate(aQStack_258,6.0,6.0);
  dStack_248 = (double)in_ESI;
  dStack_240 = dStack_248 * 0.5;
  dStack_238 = dStack_248 * 0.5;
  dStack_230 = dStack_248 * 0.4;
  dStack_228 = dStack_248 * 0.085;
  dStack_220 = dStack_248 * 0.18;
  QPointF::QPointF(aQStack_118,-dStack_228,-dStack_228);
  QPointF::QPointF(aQStack_108,-dStack_228,dStack_220 - dStack_230);
  QPointF::QPointF(aQStack_f8,-dStack_220,dStack_220 - dStack_230);
  QPointF::QPointF(aQStack_e8,0.0,-dStack_230);
  QPointF::QPointF(aQStack_d8,dStack_220,dStack_220 - dStack_230);
  QPointF::QPointF(aQStack_c8,dStack_228,dStack_220 - dStack_230);
  QPointF::QPointF(aQStack_b8,dStack_228,-dStack_228);
  QPointF::QPointF(aQStack_a8,dStack_228,dStack_228);
  QPointF::QPointF(aQStack_98,dStack_228,dStack_230 - dStack_220);
  QPointF::QPointF(aQStack_88,dStack_220,dStack_230 - dStack_220);
  QPointF::QPointF(aQStack_78,0.0,dStack_230);
  QPointF::QPointF(aQStack_68,-dStack_220,dStack_230 - dStack_220);
  QPointF::QPointF(aQStack_58,-dStack_228,dStack_230 - dStack_220);
  QPointF::QPointF(aQStack_48,-dStack_228,dStack_228);
  QTransform::QTransform(aQStack_168);
  uVar2 = qRadiansToDegrees(param_2);
  QTransform::rotate(uVar2,aQStack_168,2);
  QPainterPath::QPainterPath(aQStack_250);
  QPointF::QPointF(aQStack_1e8,dStack_240,dStack_238);
  aQStack_1f8 = (QPointF  [16])QTransform::map((QPointF *)aQStack_168);
  aQStack_1d8._0_16_ = operator+(aQStack_1f8,aQStack_1e8);
  QPainterPath::moveTo((QPointF *)aQStack_250);
  for (iStack_264 = 1; iStack_264 < 0xe; iStack_264 = iStack_264 + 1) {
    QPointF::QPointF(aQStack_1e8,dStack_240,dStack_238);
    auVar7 = QTransform::map((QPointF *)aQStack_168);
    aQStack_1f8 = (QPointF  [16])auVar7;
    auVar7 = operator+(aQStack_1f8,aQStack_1e8);
    aQStack_1d8._0_16_ = auVar7;
    QPainterPath::lineTo((QPointF *)aQStack_250);
  }
  QPainterPath::closeSubpath();
  QPointF::QPointF(aQStack_1d8,dStack_240,dStack_238);
  QPointF::QPointF(aQStack_1f8,0.0,-dStack_230);
  aQStack_1e8 = (QPointF  [16])QTransform::map((QPointF *)aQStack_168);
  aQStack_218 = (QPointF  [16])operator+(aQStack_1e8,aQStack_1d8);
  QPointF::QPointF(aQStack_1d8,dStack_240,dStack_238);
  QPointF::QPointF(aQStack_1f8,0.0,dStack_230);
  auVar7 = QTransform::map((QPointF *)aQStack_168);
  aQStack_1e8 = (QPointF  [16])auVar7;
  aQStack_208 = (QPointF  [16])operator+(aQStack_1e8,aQStack_1d8);
  dVar3 = (double)QPointF::y(aQStack_208);
  dVar4 = (double)QPointF::x(aQStack_208);
  dVar5 = (double)QPointF::y(aQStack_218);
  dVar6 = (double)QPointF::x(aQStack_218);
  kithGlassFill(dVar6,dVar5,dVar4,dVar3);
  QBrush::QBrush((QBrush *)aQStack_1e8,(QGradient *)aQStack_1d8);
  QPainter::fillPath((QPainterPath *)aQStack_258,(QBrush *)aQStack_250);
  QBrush::~QBrush((QBrush *)aQStack_1e8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_1d8);
  kithCame(aQStack_258,aQStack_250,dStack_248 * 0.055);
  QPainter::setPen(aQStack_258,0);
  QColor::QColor((QColor *)&uStack_178,"#fff0c0");
  QPainter::setBrush(aQStack_258,uStack_178,uStack_170);
  dVar3 = dStack_248 * 0.045;
  dVar4 = dStack_248 * 0.045;
  QPointF::QPointF(aQStack_1d8,dStack_240,dStack_238);
  QPainter::drawEllipse(aQStack_258,aQStack_1d8,dVar4,dVar3);
  QPainter::end();
  QPainterPath::~QPainterPath(aQStack_250);
  QPainter::~QPainter(aQStack_258);
  if (lStack_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 002789fa  renderKithCrosshair

/* renderKithCrosshair(int) */

QImage * renderKithCrosshair(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  QPainter local_d8 [8];
  QPainterPath local_d0 [8];
  QBrush local_c8 [8];
  double local_c0;
  double local_b8;
  double local_b0;
  double local_a8;
  double local_a0;
  QRectF local_98 [96];
  undefined8 local_38;
  undefined8 local_30;
  long local_20;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(local_d8,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(local_d8,1,1);
  QPainter::translate(local_d8,6.0,6.0);
  local_c0 = (double)in_ESI;
  local_b8 = local_c0 * 0.5;
  local_b0 = local_c0 * 0.5;
  local_a8 = local_c0 * 0.42;
  local_a0 = local_c0 * 0.05;
  QPainterPath::QPainterPath(local_d0);
  QRectF::QRectF(local_98,local_b8 - local_a0,local_b0 - local_a8,local_a0 + local_a0,
                 local_a8 + local_a8);
  QPainterPath::addRect((QRectF *)local_d0);
  QRectF::QRectF(local_98,local_b8 - local_a8,local_b0 - local_a0,local_a8 + local_a8,
                 local_a0 + local_a0);
  QPainterPath::addRect((QRectF *)local_d0);
  kithGlassFill(local_b8 - local_a8,local_b0 - local_a8,local_b8 + local_a8,local_b0 + local_a8);
  QBrush::QBrush(local_c8,(QGradient *)local_98);
  QPainter::fillPath((QPainterPath *)local_d8,(QBrush *)local_d0);
  QBrush::~QBrush(local_c8);
  QLinearGradient::~QLinearGradient((QLinearGradient *)local_98);
  kithCame(local_d8,local_d0,local_c0 * 0.04);
  QPainter::setPen(local_d8,0);
  QColor::QColor((QColor *)&local_38,"#d33a52");
  QPainter::setBrush(local_d8,local_38,local_30);
  dVar2 = local_c0 * 0.05;
  dVar3 = local_c0 * 0.05;
  QPointF::QPointF((QPointF *)local_98,local_b8,local_b0);
  QPainter::drawEllipse(local_d8,(QPointF *)local_98,dVar3,dVar2);
  QColor::QColor((QColor *)&local_38,"#0b0b14");
  QPen::QPen((QPen *)local_c8,(QColor *)&local_38);
  QPen::setWidthF(local_c0 * 0.02);
  QPainter::setPen(local_d8,(QPen *)local_c8);
  QPainter::setBrush(local_d8,0);
  dVar2 = local_c0 * 0.05;
  dVar3 = local_c0 * 0.05;
  QPointF::QPointF((QPointF *)local_98,local_b8,local_b0);
  QPainter::drawEllipse(local_d8,(QPointF *)local_98,dVar3,dVar2);
  QPainter::end();
  QPen::~QPen((QPen *)local_c8);
  QPainterPath::~QPainterPath(local_d0);
  QPainter::~QPainter(local_d8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 0027900c  renderKithNotAllowed

/* renderKithNotAllowed(int) */

QImage * renderKithNotAllowed(int param_1)

{
  int in_ESI;
  undefined4 in_register_0000003c;
  QImage *pQVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  double dVar4;
  QPen *pQVar5;
  double dVar6;
  undefined1 auVar7 [16];
  QPainter local_1b8 [8];
  QPen aQStack_1b0 [8];
  QPen aQStack_1a8 [8];
  double dStack_1a0;
  double dStack_198;
  double dStack_190;
  QPointF aQStack_188 [16];
  QPointF aQStack_178 [16];
  QPointF aQStack_168 [16];
  QPolygonF aQStack_158 [32];
  QPolygonF aQStack_138 [32];
  QBrush aQStack_118 [32];
  QPointF aQStack_f8 [96];
  undefined8 uStack_98;
  undefined8 uStack_90;
  QColor aQStack_88 [88];
  long local_30;
  
  pQVar1 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 0027903a to 003790a2 has its CatchHandler @ 002790e6 */
  QImage::QImage(pQVar1,in_ESI + 0xc,in_ESI + 0xc,6);
  QImage::fill(pQVar1,0x13);
  QPainter::QPainter(local_1b8,(QPaintDevice *)pQVar1);
  QPainter::setRenderHint(local_1b8,1,1);
  QPainter::translate(local_1b8,6.0,6.0);
  dStack_1a0 = (double)in_ESI;
  dStack_198 = dStack_1a0 * 0.5;
  dStack_190 = dStack_1a0 * 0.5;
  QColor::QColor(aQStack_88,"#0b0b14");
  QPen::QPen(aQStack_1b0,aQStack_88);
  QPen::setWidthF(dStack_1a0 * 0.14);
  QPainter::setPen(local_1b8,aQStack_1b0);
  QPainter::setBrush(local_1b8,0);
  dVar4 = dStack_1a0 * 0.4;
  dVar6 = dStack_1a0 * 0.4;
  QPointF::QPointF(aQStack_f8,dStack_198,dStack_190);
  QPainter::drawEllipse(local_1b8,aQStack_f8,dVar6,dVar4);
  pQVar5 = (QPen *)(dStack_1a0 * 0.1);
  kithRubyFill(dStack_198 - dStack_1a0 * 0.4,dStack_190 - dStack_1a0 * 0.4,
               dStack_1a0 * 0.4 + dStack_198,dStack_1a0 * 0.4 + dStack_190);
  QBrush::QBrush(aQStack_118,(QGradient *)aQStack_f8);
  QPen::QPen(pQVar5,aQStack_1a8,aQStack_118,1,0x10,0x40);
  QBrush::~QBrush(aQStack_118);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_f8);
  QPainter::setPen(local_1b8,aQStack_1a8);
  dVar4 = dStack_1a0 * 0.4;
  dVar6 = dStack_1a0 * 0.4;
  QPointF::QPointF(aQStack_f8,dStack_198,dStack_190);
  QPainter::drawEllipse(local_1b8,aQStack_f8,dVar6,dVar4);
  QTransform::QTransform((QTransform *)aQStack_88);
  QTransform::rotate(0xc046800000000000,aQStack_88,2);
  QRectF::QRectF((QRectF *)aQStack_f8,dStack_1a0 * -0.4,dStack_1a0 * -0.07,dStack_1a0 * 0.8,
                 dStack_1a0 * 0.14);
  QPolygonF::QPolygonF((QPolygonF *)aQStack_118,(QRectF *)aQStack_f8);
  QTransform::map(aQStack_158);
  QPolygonF::~QPolygonF((QPolygonF *)aQStack_118);
  QPolygonF::translate(aQStack_158,dStack_198,dStack_190);
  QPainter::setPen(local_1b8,0);
  QColor::QColor((QColor *)&uStack_98,"#0b0b14");
  QPainter::setBrush(local_1b8,uStack_98,uStack_90);
  QPainter::drawPolygon(local_1b8,aQStack_158,0);
  QRectF::QRectF((QRectF *)aQStack_f8,dStack_1a0 * -0.4,dStack_1a0 * -0.05,dStack_1a0 * 0.8,
                 dStack_1a0 * 0.1);
  QPolygonF::QPolygonF((QPolygonF *)aQStack_118,(QRectF *)aQStack_f8);
  QTransform::map(aQStack_138);
  QPolygonF::~QPolygonF((QPolygonF *)aQStack_118);
  QPolygonF::translate(aQStack_138,dStack_198,dStack_190);
  QPointF::QPointF(aQStack_f8,dStack_198,dStack_190);
  QPointF::QPointF(aQStack_168,dStack_1a0 * -0.4,0.0);
  aQStack_118._0_16_ = QTransform::map((QPointF *)aQStack_88);
  aQStack_188 = (QPointF  [16])operator+((QPointF *)aQStack_118,aQStack_f8);
  QPointF::QPointF(aQStack_f8,dStack_198,dStack_190);
  QPointF::QPointF(aQStack_168,dStack_1a0 * 0.4,0.0);
  auVar7 = QTransform::map((QPointF *)aQStack_88);
  aQStack_118._0_16_ = auVar7;
  aQStack_178 = (QPointF  [16])operator+((QPointF *)aQStack_118,aQStack_f8);
  dVar4 = (double)QPointF::y(aQStack_178);
  dVar6 = (double)QPointF::x(aQStack_178);
  dVar2 = (double)QPointF::y(aQStack_188);
  dVar3 = (double)QPointF::x(aQStack_188);
  kithRubyFill(dVar3,dVar2,dVar6,dVar4);
  QBrush::QBrush(aQStack_118,(QGradient *)aQStack_f8);
  QPainter::setBrush(local_1b8,aQStack_118);
  QBrush::~QBrush(aQStack_118);
  QLinearGradient::~QLinearGradient((QLinearGradient *)aQStack_f8);
  QPainter::drawPolygon(local_1b8,aQStack_138,0);
  QPainter::end();
  QPolygonF::~QPolygonF(aQStack_138);
  QPolygonF::~QPolygonF(aQStack_158);
  QPen::~QPen(aQStack_1a8);
  QPen::~QPen(aQStack_1b0);
  QPainter::~QPainter(local_1b8);
  if (local_30 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar1;
}



// ==== 00279a3b  renderKithHand

/* renderKithHand(int, bool) */

QImage * renderKithHand(int param_1,bool param_2)

{
  int iVar1;
  char in_DL;
  int iVar2;
  undefined7 in_register_00000031;
  undefined4 in_register_0000003c;
  QImage *pQVar3;
  long in_FS_OFFSET;
  QPainter local_f0 [8];
  QPainterPath local_e8 [8];
  QPen local_e0 [8];
  double local_d8;
  double *local_d0;
  double local_c8;
  double *local_c0;
  double *local_b8;
  double local_b0;
  QBrush local_a8 [16];
  QGradient local_98 [96];
  double local_38 [5];
  
  pQVar3 = (QImage *)CONCAT44(in_register_0000003c,param_1);
  iVar2 = (int)CONCAT71(in_register_00000031,param_2);
  local_38[3] = *(double *)(in_FS_OFFSET + 0x28);
  iVar1 = iVar2 + 0xc;
  QImage::QImage(pQVar3,iVar1,iVar1,6);
  QImage::fill(pQVar3,0x13);
  QPainter::QPainter(local_f0,(QPaintDevice *)pQVar3);
  QPainter::setRenderHint(local_f0,1,1);
  QPainter::translate(local_f0,6.0,6.0);
  local_c8 = (double)iVar2;
  if (in_DL == '\0') {
    local_d8 = 0.3;
  }
  else {
    local_d8 = 0.42;
  }
  QPainterPath::QPainterPath(local_e8);
  QPainterPath::moveTo(local_e8,local_c8 * 0.24,local_c8 * 0.62);
  QPainterPath::lineTo(local_e8,local_c8 * 0.24,(local_d8 + 0.08) * local_c8);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.24,local_d8 * local_c8,local_c8 * 0.34,local_d8 * local_c8,
             local_c8 * 0.34,(local_d8 + 0.04) * local_c8);
  QPainterPath::lineTo(local_e8,local_c8 * 0.34,local_d8 * local_c8);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.34,(local_d8 - 0.06) * local_c8,local_c8 * 0.46,
             (local_d8 - 0.06) * local_c8,local_c8 * 0.46,local_d8 * local_c8);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.46,(local_d8 - 0.08) * local_c8,local_c8 * 0.58,
             (local_d8 - 0.08) * local_c8,local_c8 * 0.58,local_d8 * local_c8);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.58,(local_d8 - 0.06) * local_c8,local_c8 * 0.7,
             (local_d8 - 0.06) * local_c8,local_c8 * 0.7,(local_d8 + 0.02) * local_c8);
  QPainterPath::lineTo(local_e8,local_c8 * 0.74,local_c8 * 0.5);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.78,local_c8 * 0.66,local_c8 * 0.7,local_c8 * 0.86,local_c8 * 0.54
             ,local_c8 * 0.88);
  QPainterPath::lineTo(local_e8,local_c8 * 0.4,local_c8 * 0.88);
  QPainterPath::cubicTo
            (local_e8,local_c8 * 0.3,local_c8 * 0.86,local_c8 * 0.24,local_c8 * 0.74,local_c8 * 0.24
             ,local_c8 * 0.62);
  QPainterPath::closeSubpath();
  kithGlassFill(local_c8 * 0.2,local_d8 * local_c8,local_c8 * 0.78,local_c8 * 0.9);
  QBrush::QBrush(local_a8,local_98);
  QPainter::fillPath((QPainterPath *)local_f0,(QBrush *)local_e8);
  QBrush::~QBrush(local_a8);
                    /* catch() { ... } // from try @ 0027a22d with catch @ 0027a1ca
                       catch() { ... } // from try @ 0027a34f with catch @ 0027a1ca */
  QLinearGradient::~QLinearGradient((QLinearGradient *)local_98);
  kithCame(local_f0,local_e8,local_c8 * 0.055);
  QPainter::save();
                    /* try { // try from 0027a22d to 0037a26c has its CatchHandler @ 0027a1ca */
  QPainter::setClipPath(local_f0,local_e8,1);
  kithSheen(local_f0,local_c8 * 0.2,local_d8 * local_c8,local_c8 * 0.6,local_c8 * 0.4);
  QPainter::restore();
                    /* try { // try from 0027a2d0 to 0037a338 has its CatchHandler @ 0027a3a3 */
  QColor::QColor((QColor *)local_38,0xb,0xb,0x14,0x80);
  QPen::QPen(local_e0,(QColor *)local_38);
  QPen::setWidthF(local_c8 * 0.022);
  QPainter::setPen(local_f0,local_e0);
  local_38[0] = 0.34;
  local_38[1] = 0.46;
                    /* try { // try from 0027a34f to 0037a3d0 has its CatchHandler @ 0027a1ca */
  local_38[2] = 0.58;
  local_b8 = local_38 + 3;
  local_d0 = local_38;
  local_c0 = local_d0;
  for (; local_d0 != local_b8; local_d0 = local_d0 + 1) {
    local_b0 = *local_d0;
                    /* catch() { ... } // from try @ 0027a2d0 with catch @ 0027a3a3 */
    QPointF::QPointF((QPointF *)local_98,local_b0 * local_c8,(local_d8 + 0.16) * local_c8);
                    /* catch() { ... } // from try @ 0027a742 with catch @ 0027a3f4 */
    QPointF::QPointF((QPointF *)local_a8,local_b0 * local_c8,(local_d8 + 0.02) * local_c8);
                    /* try { // try from 0027a445 to 0037a449 has its CatchHandler @ 0027a3f4 */
    QPainter::drawLine(local_f0,(QPointF *)local_a8,(QPointF *)local_98);
  }
  QPainter::end();
  QPen::~QPen(local_e0);
  QPainterPath::~QPainterPath(local_e8);
  QPainter::~QPainter(local_f0);
  if (local_38[3] != (double)*(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return pQVar3;
}



// ==== 0027df4b  writeXcursorFile

/* WARNING: Removing unreachable block (ram,0x0027e0ef) */
/* writeXcursorFile(QString const&, QList<int> const&, std::function<QImage (int)> const&, double,
   double) */

bool writeXcursorFile(QString *param_1,QList *param_2,function *param_3,double param_4,
                     double param_5)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  QDebug *pQVar7;
  QDataStream *pQVar8;
  long in_FS_OFFSET;
  bool bVar9;
  uint uStack_108;
  int iStack_104;
  int iStack_100;
  undefined4 auStack_f0 [2];
  QList<int> *local_e8;
  QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
  *pQStack_e0;
  QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
  *pQStack_d8;
  long lStack_d0;
  long lStack_c8;
  long lStack_c0;
  undefined8 local_b8 [2];
  QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
  local_a8 [16];
  undefined8 local_98;
  undefined8 auStack_88 [4];
  QImage aQStack_68 [32];
  undefined8 auStack_48 [3];
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_a8[0] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[1] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[2] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[3] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[4] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[5] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[6] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[7] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[8] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[9] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                 )0x0;
  local_a8[10] = (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                  )0x0;
  local_a8[0xb] =
       (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
        )0x0;
  local_a8[0xc] =
       (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
        )0x0;
  local_a8[0xd] =
       (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
        )0x0;
  local_a8[0xe] =
       (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
        )0x0;
  local_a8[0xf] =
       (QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
        )0x0;
  local_98 = 0;
  local_e8 = (QList<int> *)param_2;
  local_b8[0] = QList<int>::begin((QList<int> *)param_2);
  auStack_88[0] = QList<int>::end(local_e8);
  while (cVar1 = QList<int>::const_iterator::operator!=((const_iterator *)local_b8,auStack_88[0]),
        cVar1 != '\0') {
    piVar6 = (int *)QList<int>::const_iterator::operator*((const_iterator *)local_b8);
    iVar5 = *piVar6;
    std::function<QImage(int)>::operator()((function<QImage(int)> *)auStack_48,(int)param_3);
    QFlags<Qt::ImageConversionFlag>::QFlags((QFlags<Qt::ImageConversionFlag> *)auStack_f0,0);
    QImage::convertToFormat(aQStack_68,auStack_48,6,auStack_f0[0]);
    QImage::~QImage((QImage *)auStack_48);
    QImage::QImage((QImage *)auStack_48,aQStack_68);
    iStack_30 = iVar5;
    iStack_2c = qRound((double)iVar5 * param_4);
    iStack_2c = iStack_2c + 6;
    iStack_28 = qRound((double)iVar5 * param_5);
    iStack_28 = iStack_28 + 6;
    QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
    ::append(local_a8,(Frame *)auStack_48);
    writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)
    ::Frame::~Frame((Frame *)auStack_48);
    QImage::~QImage(aQStack_68);
    QList<int>::const_iterator::operator++((const_iterator *)local_b8);
  }
  QFile::QFile((QFile *)local_b8,param_1);
  uVar2 = operator|(2,8);
  cVar1 = QFile::open(local_b8,uVar2);
  if (cVar1 == '\x01') {
    QDataStream::QDataStream((QDataStream *)aQStack_68,(QIODevice *)local_b8);
    QDataStream::setByteOrder(aQStack_68,1);
    uVar3 = QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
            ::size(local_a8);
    pQVar8 = (QDataStream *)QDataStream::operator<<((QDataStream *)aQStack_68,0x72756358);
    pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,0x10);
    pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,0x10000);
    QDataStream::operator<<(pQVar8,uVar3);
    uStack_108 = uVar3 * 0xc + 0x10;
    pQStack_e0 = local_a8;
    auStack_88[0] =
         QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
         ::begin(pQStack_e0);
    auStack_48[0] =
         QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
         ::end(pQStack_e0);
    while (cVar1 = QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                   ::iterator::operator!=((iterator *)auStack_88,auStack_48[0]), cVar1 != '\0') {
      lStack_c0 = QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                  ::iterator::operator*((iterator *)auStack_88);
      pQVar8 = (QDataStream *)QDataStream::operator<<((QDataStream *)aQStack_68,0xfffd0002);
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,*(uint *)(lStack_c0 + 0x18));
      QDataStream::operator<<(pQVar8,uStack_108);
      iVar5 = QImage::width();
      iVar4 = QImage::height();
      uStack_108 = uStack_108 + (iVar4 * iVar5 + 9) * 4;
      QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
      ::iterator::operator++((iterator *)auStack_88);
    }
    pQStack_d8 = local_a8;
    auStack_88[0] =
         QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
         ::begin(pQStack_d8);
    auStack_48[0] =
         QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
         ::end(pQStack_d8);
    while (cVar1 = QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                   ::iterator::operator!=((iterator *)auStack_88,auStack_48[0]), cVar1 != '\0') {
      lStack_d0 = QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
                  ::iterator::operator*((iterator *)auStack_88);
      pQVar8 = (QDataStream *)QDataStream::operator<<((QDataStream *)aQStack_68,0x24);
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,0xfffd0002);
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,*(uint *)(lStack_d0 + 0x18));
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,1);
      uVar3 = QImage::width();
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,uVar3);
      uVar3 = QImage::height();
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,uVar3);
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,*(uint *)(lStack_d0 + 0x1c));
      pQVar8 = (QDataStream *)QDataStream::operator<<(pQVar8,*(uint *)(lStack_d0 + 0x20));
      QDataStream::operator<<(pQVar8,0);
      for (iStack_104 = 0; iVar5 = QImage::height(), iStack_104 < iVar5; iStack_104 = iStack_104 + 1
          ) {
        lStack_c8 = QImage::constScanLine((int)lStack_d0);
        for (iStack_100 = 0; iVar5 = QImage::width(), iStack_100 < iVar5;
            iStack_100 = iStack_100 + 1) {
          QDataStream::operator<<
                    ((QDataStream *)aQStack_68,*(uint *)(lStack_c8 + (long)iStack_100 * 4));
        }
      }
      QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
      ::iterator::operator++((iterator *)auStack_88);
    }
    QFileDevice::close();
    iVar5 = QFileDevice::error();
    bVar9 = iVar5 == 0;
    if (!bVar9) {
      QMessageLogger::QMessageLogger((QMessageLogger *)auStack_48,(char *)0x0,0,(char *)0x0);
      QMessageLogger::warning();
      pQVar7 = (QDebug *)
               QDebug::operator<<((QDebug *)auStack_f0,"CursorManager: short write on cursor file");
      pQVar7 = (QDebug *)QDebug::operator<<(pQVar7,param_1);
      QIODevice::errorString();
      QDebug::operator<<(pQVar7,(QString *)auStack_88);
      QString::~QString((QString *)auStack_88);
      QDebug::~QDebug((QDebug *)auStack_f0);
    }
    QDataStream::~QDataStream((QDataStream *)aQStack_68);
  }
  else {
    QMessageLogger::QMessageLogger((QMessageLogger *)auStack_48,(char *)0x0,0,(char *)0x0);
    QMessageLogger::warning();
    pQVar7 = (QDebug *)
             QDebug::operator<<((QDebug *)auStack_88,"CursorManager: cannot write cursor file");
    pQVar7 = (QDebug *)QDebug::operator<<(pQVar7,param_1);
    QIODevice::errorString();
    QDebug::operator<<(pQVar7,(QString *)aQStack_68);
    QString::~QString((QString *)aQStack_68);
    QDebug::~QDebug((QDebug *)auStack_88);
    bVar9 = false;
  }
  QFile::~QFile((QFile *)local_b8);
  QList<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
  ::~QList(local_a8);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return bVar9;
}



// ==== 00288dc8  qt_ptr_swap<QTypedArrayData<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>>

/* void qt_ptr_swap<QTypedArrayData<writeXcursorFile(QString const&, QList<int> const&,
   std::function<QImage (int)> const&, double, double)::Frame>
   >(QTypedArrayData<writeXcursorFile(QString const&, QList<int> const&, std::function<QImage (int)>
   const&, double, double)::Frame>*&, QTypedArrayData<writeXcursorFile(QString const&, QList<int>
   const&, std::function<QImage (int)> const&, double, double)::Frame>*&) */

void qt_ptr_swap<QTypedArrayData<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>>
               (QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
                    /* try { // try from 00288df7 to 00388dfb has its CatchHandler @ 00288f55 */
  *param_2 = pQVar1;
  return;
}



// ==== 00288dfb  qt_ptr_swap<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>

/* void qt_ptr_swap<writeXcursorFile(QString const&, QList<int> const&, std::function<QImage (int)>
   const&, double, double)::Frame>(writeXcursorFile(QString const&, QList<int> const&,
   std::function<QImage (int)> const&, double, double)::Frame*&, writeXcursorFile(QString const&,
   QList<int> const&, std::function<QImage (int)> const&, double, double)::Frame*&) */

void qt_ptr_swap<writeXcursorFile(QString_const&,QList<int>const&,std::function<QImage(int)>const&,double,double)::Frame>
               (Frame **param_1,Frame **param_2)

{
  Frame *pFVar1;
  
                    /* try { // try from 00288e03 to 00388e07 has its CatchHandler @ 00288f44 */
  pFVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pFVar1;
  return;
}



// ==== 00289d8a  qRadiansToDegrees

/* qRadiansToDegrees(double) */

double qRadiansToDegrees(double param_1)

{
  return param_1 * 57.29577951308232;
}



// ==== 00289da6  operator+

/* TEMPNAMEPLACEHOLDERVALUE(QPointF const&, QPointF const&) */

undefined1  [16] operator+(QPointF *param_1,QPointF *param_2)

{
  undefined1 auVar1 [16];
  long in_FS_OFFSET;
  undefined8 local_28;
  undefined8 local_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPointF::QPointF((QPointF *)&local_28,*(double *)param_1 + *(double *)param_2,
                   *(double *)(param_1 + 8) + *(double *)(param_2 + 8));
  auVar1._8_8_ = local_20;
  auVar1._0_8_ = local_28;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return auVar1;
}



// ==== 0028a890  qt_ptr_swap<QCursorData>

/* void qt_ptr_swap<QCursorData>(QCursorData*&, QCursorData*&) */

void qt_ptr_swap<QCursorData>(QCursorData **param_1,QCursorData **param_2)

{
  QCursorData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0028bb06  qt_ptr_swap<QTypedArrayData<QPointF>>

/* void qt_ptr_swap<QTypedArrayData<QPointF> >(QTypedArrayData<QPointF>*&,
   QTypedArrayData<QPointF>*&) */

void qt_ptr_swap<QTypedArrayData<QPointF>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
                    /* catch() { ... } // from try @ 0028ba3b with catch @ 0028bb19 */
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0028bb39  qt_ptr_swap<QPointF>

/* void qt_ptr_swap<QPointF>(QPointF*&, QPointF*&) */

void qt_ptr_swap<QPointF>(QPointF **param_1,QPointF **param_2)

{
  QPointF *pQVar1;
  
                    /* catch() { ... } // from try @ 0028ba82 with catch @ 0028bb42 */
  pQVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = pQVar1;
  return;
}



// ==== 0028e046  qHash<Qt::CursorShape,true>

/* unsigned long qHash<Qt::CursorShape, true>(Qt::CursorShape, unsigned long) */

ulong qHash<Qt::CursorShape,true>(undefined4 param_1,ulong param_2)

{
  uint uVar1;
  ulong uVar2;
  
  uVar1 = qToUnderlying<Qt::CursorShape>(param_1);
  uVar2 = QHashPrivate::hash((ulong)uVar1,param_2);
  return uVar2;
}



// ==== 0028e114  qHashEquals<Qt::CursorShape>

/* bool qHashEquals<Qt::CursorShape>(Qt::CursorShape const&, Qt::CursorShape const&) */

bool qHashEquals<Qt::CursorShape>(CursorShape *param_1,CursorShape *param_2)

{
  return *(int *)param_1 == *(int *)param_2;
}



// ==== 0028f620  qToUnderlying<Qt::CursorShape>

/* std::underlying_type<Qt::CursorShape>::type qToUnderlying<Qt::CursorShape>(Qt::CursorShape) */

undefined4 qToUnderlying<Qt::CursorShape>(undefined4 param_1)

{
  return param_1;
}



// ==== 00290622  qt_ptr_swap<QTypedArrayData<QWindow*>>

/* void qt_ptr_swap<QTypedArrayData<QWindow*> >(QTypedArrayData<QWindow*>*&,
   QTypedArrayData<QWindow*>*&) */

void qt_ptr_swap<QTypedArrayData<QWindow*>>(QTypedArrayData **param_1,QTypedArrayData **param_2)

{
  QTypedArrayData *pQVar1;
  
  pQVar1 = *param_1;
  *param_1 = *param_2;
                    /* try { // try from 00290649 to 0039064d has its CatchHandler @ 0029071c */
  *param_2 = pQVar1;
  return;
}



// ==== 00290655  qt_ptr_swap<QWindow*>

/* void qt_ptr_swap<QWindow*>(QWindow**&, QWindow**&) */

void qt_ptr_swap<QWindow*>(QWindow ***param_1,QWindow ***param_2)

{
  QWindow **ppQVar1;
  
                    /* try { // try from 00290663 to 00390667 has its CatchHandler @ 00290708 */
  ppQVar1 = *param_1;
                    /* try { // try from 00290676 to 0039067a has its CatchHandler @ 002906f7 */
  *param_1 = *param_2;
  *param_2 = ppQVar1;
  return;
}



// ==== 002912a8  qInitResources_lelan

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qInitResources_lelan() */

undefined8 qInitResources_lelan(void)

{
  qRegisterResourceData(3,qt_resource_struct,qt_resource_name,"");
  return 1;
}



// ==== 002912dd  qCleanupResources_lelan

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qCleanupResources_lelan() */

undefined8 qCleanupResources_lelan(void)

{
  qUnregisterResourceData(3,qt_resource_struct,qt_resource_name,"");
                    /* try { // try from 00291311 to 00391315 has its CatchHandler @ 002917e3 */
  return 1;
}



// ==== 00291326  _ZN12_GLOBAL__N_111initializerD1Ev

void _ZN12_GLOBAL__N_111initializerD1Ev(void)

{
  qCleanupResources_lelan();
  return;
}



// ==== 0029133a  __static_initialization_and_destruction_0

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* __static_initialization_and_destruction_0() */

void __static_initialization_and_destruction_0(void)

{
  (anonymous_namespace)::initializer::initializer((initializer *)&(anonymous_namespace)::dummy);
  __cxa_atexit(_ZN12_GLOBAL__N_111initializerD1Ev,&(anonymous_namespace)::dummy,&__dso_handle);
  return;
}



// ==== 00291370  _GLOBAL__sub_I_qInitResources_lelan

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qInitResources_lelan() */

void _GLOBAL__sub_I_qInitResources_lelan(void)

{
  __static_initialization_and_destruction_0();
  return;
}



// ==== 0029137c  _fini

void _fini(void)

{
  return;
}



// ==== 00291390  FUN_00291390

void FUN_00291390(NCDEWindowManager *param_1,uint param_2,uint param_3)

{
  char cVar1;
  long extraout_RDX;
  long extraout_RDX_00;
  long extraout_RDX_01;
  long lVar2;
  uint uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  long lStack_38;
  undefined8 uStack_30;
  long local_28;
  int local_1c;
  uint local_18;
  uint local_14;
  NCDEWindowManager *local_10;
  
  local_18 = param_3;
  local_14 = param_2;
  local_10 = param_1;
  local_1c = NCDEWindowManager::rowForClient(param_1,param_2);
  if (-1 < local_1c) {
    local_28 = QList<NCDEWindowManager::WindowEntry>::operator[]
                         ((QList<NCDEWindowManager::WindowEntry> *)(local_10 + 0x90),(long)local_1c)
    ;
    uStack_30 = *(undefined8 *)(local_28 + 0x38);
    lVar2 = *(long *)(local_28 + 0x40);
    lStack_38 = lVar2;
    if (((((lVar2 == 5) &&
          (cVar1 = FUN_002915f2(&DAT_00291612,uStack_30,5,5), lVar2 = extraout_RDX, cVar1 != '\0'))
         || ((lStack_38 == 0xe &&
             (cVar1 = FUN_002915f2(&DAT_00291617,uStack_30,lVar2,0xe), lVar2 = extraout_RDX_00,
             cVar1 != '\0')))) ||
        ((lStack_38 == 9 &&
         (cVar1 = FUN_002915f2(&DAT_00291625,uStack_30,lVar2,9), lVar2 = extraout_RDX_01,
         cVar1 != '\0')))) ||
       ((9 < lStack_38 && (cVar1 = FUN_002915f2(&DAT_0029162e,uStack_30,lVar2,10), cVar1 != '\0'))))
    {
      uStack_3c = *(uint *)(local_28 + 8);
      uStack_40 = *(undefined4 *)(local_28 + 0xc);
      uStack_44 = *(undefined4 *)(local_28 + 0x10);
      uStack_48 = *(undefined4 *)(local_28 + 0x14);
      QHash<unsigned_int,unsigned_int>::insert
                ((QHash<unsigned_int,unsigned_int> *)(local_10 + 0xd0),&local_14,&local_18);
      QHash<unsigned_int,unsigned_int>::insert
                ((QHash<unsigned_int,unsigned_int> *)(local_10 + 0xd8),&local_18,&local_14);
      uStack_50 = *(undefined8 *)(local_10 + 0x20);
      xcb_map_window(uStack_50,local_14);
      uStack_68 = uStack_3c;
      uStack_64 = uStack_40;
      uStack_60 = uStack_44;
      uStack_5c = uStack_48;
      xcb_configure_window(uStack_50,local_18,0xf,&uStack_68);
      uStack_68 = local_14;
      uStack_64 = 0;
      xcb_configure_window(uStack_50,local_18,0x60,&uStack_68);
      xcb_shape_rectangles(uStack_50,0,2,0,local_18,0,0,0,0);
      xcb_shape_rectangles(uStack_50,0,0,0,local_18,0,0,0,0);
      NCDEWindowManager::setWmClass(local_10,local_18,"ncde-frame");
      xcb_flush(uStack_50);
      NCDEWindowManager::activateWindow(local_10,local_14);
      return;
    }
  }
  NCDEWindowManager::registerFrameWindow(local_10,local_14,local_18);
  return;
}



// ==== 002915f2  FUN_002915f2

undefined8 FUN_002915f2(byte *param_1,ushort *param_2,undefined8 param_3,int param_4)

{
  while( true ) {
    if (param_4 == 0) {
      return 1;
    }
    if ((ushort)*param_1 != *param_2) break;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    param_4 = param_4 + -1;
  }
  return 0;
}


