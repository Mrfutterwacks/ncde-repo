// Ghidra decompile of LaPivot.oracle — class/namespace _anonymous_namespace_ (10 functions). Raw; not source.

// ==== 00233900  (anonymous_namespace)::paSinkInfoCb

/* WARNING: Removing unreachable block (ram,0x00233988) */
/* (anonymous namespace)::paSinkInfoCb(pa_context*, pa_sink_info const*, int, void*) */

void (anonymous_namespace)::paSinkInfoCb
               (pa_context *param_1,pa_sink_info *param_2,int param_3,void *param_4)

{
  uint uVar1;
  long in_FS_OFFSET;
  bool local_f9;
  int local_f8;
  uint local_f4;
  void *local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  Invoke local_d8 [32];
  Invoke local_b8 [32];
  QString local_98 [32];
  Invoke local_78 [32];
  Invoke local_58 [32];
  Invoke local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if ((param_3 == 0) && (param_2 != (pa_sink_info *)0x0)) {
    local_f0 = param_4;
    uVar1 = pa_cvolume_avg(param_2 + 0xac);
    local_f8 = qRound(((double)uVar1 * 100.0) / 65536.0);
    local_f9 = *(int *)(param_2 + 0x130) != 0;
    local_f4 = (uint)(byte)param_2[0xac];
    QtPrivate::Invoke::argument<int>(local_38,"int",(int *)&local_f4);
    QtPrivate::Invoke::argument<unsigned_int>(local_58,"uint",(uint *)(param_2 + 8));
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_e8,(char **)param_2);
    QString::fromUtf8(local_98,local_e8,local_e0);
    QtPrivate::Invoke::argument<QString>(local_78,"QString",local_98);
    QtPrivate::Invoke::argument<bool>(local_b8,"bool",&local_f9);
    QtPrivate::Invoke::argument<int>(local_d8,"int",&local_f8);
    QMetaObject::
    invokeMethod<QMetaMethodArgument,QMetaMethodArgument,QMetaMethodArgument,QMetaMethodArgument,QMetaMethodArgument>
              (local_f0,&LAB_002aba65_1,2,local_d8,local_b8,local_78,local_58,local_38);
    QString::~QString(local_98);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00233b72  (anonymous_namespace)::paServerInfoCb

/* (anonymous namespace)::paServerInfoCb(pa_context*, pa_server_info const*, void*) */

void (anonymous_namespace)::paServerInfoCb
               (pa_context *param_1,pa_server_info *param_2,void *param_3)

{
  long lVar1;
  long in_FS_OFFSET;
  undefined8 local_68;
  undefined8 local_60;
  QString local_58 [32];
  Invoke local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 != (pa_server_info *)0x0) {
    if (*(long *)(param_2 + 0x38) != 0) {
      QByteArrayView::QByteArrayView<char_const*,true>
                ((QByteArrayView *)&local_68,(char **)(param_2 + 0x38));
      QString::fromUtf8(local_58,local_68,local_60);
      QtPrivate::Invoke::argument<QString>(local_38,"QString",local_58);
      QMetaObject::invokeMethod<QMetaMethodArgument>(param_3,&LAB_002aba75_1,2,local_38);
      QString::~QString(local_58);
    }
    if ((*(long *)(param_2 + 0x30) != 0) &&
       (lVar1 = pa_context_get_sink_info_by_name
                          (param_1,*(undefined8 *)(param_2 + 0x30),paSinkInfoCb,param_3), lVar1 != 0
       )) {
      pa_operation_unref(lVar1);
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00233cc4  (anonymous_namespace)::paSinkInputInfoCb

/* WARNING: Removing unreachable block (ram,0x00233dcb) */
/* (anonymous namespace)::paSinkInputInfoCb(pa_context*, pa_sink_input_info const*, int, void*) */

void (anonymous_namespace)::paSinkInputInfoCb
               (pa_context *param_1,pa_sink_input_info *param_2,int param_3,void *param_4)

{
  uint uVar1;
  int iVar2;
  QVariant *pQVar3;
  long in_FS_OFFSET;
  char *local_108;
  char *local_100;
  undefined8 local_f8;
  char *local_f0;
  undefined1 *local_e8;
  undefined1 *local_e0;
  undefined *local_d8;
  undefined *local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  Invoke local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_3 == 0) {
    local_108 = (char *)pa_proplist_gets(*(undefined8 *)(param_2 + 0x158),&DAT_002abaa6);
    local_100 = (char *)pa_proplist_gets(*(undefined8 *)(param_2 + 0x158),&LAB_002abab6_1);
    uVar1 = pa_cvolume_avg(param_2 + 0xac);
    iVar2 = qRound(((double)uVar1 * 100.0) / 65536.0);
    local_f8 = 0;
    if (local_108 == (char *)0x0) {
      if (*(long *)(param_2 + 8) == 0) {
        local_f0 = "Audio";
      }
      else {
        local_f0 = *(char **)(param_2 + 8);
      }
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_b8,&local_f0);
      QString::fromUtf8(local_68,local_b8,local_b0);
    }
    else {
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,&local_108);
      QString::fromUtf8(local_68,local_c8,local_c0);
    }
    ::QVariant::QVariant(local_48,(QString *)local_68);
    local_e8 = &LAB_002abad4_4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"name",4);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_f8,local_88);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    if (local_100 == (char *)0x0) {
      if (*(long *)(param_2 + 8) == 0) {
        local_f0 = "";
      }
      else {
        local_f0 = *(char **)(param_2 + 8);
      }
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_b8,&local_f0);
      QString::fromUtf8(local_68,local_b8,local_b0);
    }
    else {
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_c8,&local_100);
      QString::fromUtf8(local_68,local_c8,local_c0);
    }
    ::QVariant::QVariant(local_48,(QString *)local_68);
    local_e0 = &LAB_002abae4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"meta",4);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_f8,local_88);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::QVariant(local_48,iVar2);
    local_d8 = &DAT_002abaee;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"vol",3);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_f8,(QString *)local_68);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,*(uint *)param_2);
    local_d0 = &DAT_002abaf6;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"index",5);
    QString::QString((QString *)local_68,(QArrayDataPointer *)local_88);
    pQVar3 = (QVariant *)
             QMap<QString,QVariant>::operator[]
                       ((QMap<QString,QVariant> *)&local_f8,(QString *)local_68);
    ::QVariant::operator=(pQVar3,local_48);
    QString::~QString((QString *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
    ::QVariant::~QVariant(local_48);
    ::QVariant::QVariant(local_48,(QMap *)&local_f8);
    QList<QVariant>::append((QList<QVariant> *)g_siAccum,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_f8);
  }
  else {
    QtPrivate::Invoke::argument<QList<QVariant>>(local_68,"QVariantList",(QList *)g_siAccum);
    QMetaObject::invokeMethod<QMetaMethodArgument>(param_4,&DAT_002aba96,2,local_68);
    QList<QVariant>::clear((QList<QVariant> *)g_siAccum);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 00234376  (anonymous_namespace)::paSinkListCb

/* (anonymous namespace)::paSinkListCb(pa_context*, pa_sink_info const*, int, void*) */

void (anonymous_namespace)::paSinkListCb
               (pa_context *param_1,pa_sink_info *param_2,int param_3,void *param_4)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  Invoke local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_3 == 0) {
    local_e0 = 0;
    QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_b8,(char **)param_2);
    QString::fromUtf8(local_68,local_b8,local_b0);
    ::QVariant::QVariant(local_48,(QString *)local_68);
    local_d8 = &LAB_002abad4_4;
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"name",4);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_88);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    if (*(long *)(param_2 + 0x10) == 0) {
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_b8,(char **)param_2)
      ;
      QString::fromUtf8(local_68,local_b8,local_b0);
    }
    else {
      QByteArrayView::QByteArrayView<char_const*,true>
                ((QByteArrayView *)&local_c8,(char **)(param_2 + 0x10));
      QString::fromUtf8(local_68,local_c8,local_c0);
    }
    ::QVariant::QVariant(local_48,(QString *)local_68);
    local_d0 = &LAB_002abb16;
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_a8,(QTypedArrayData *)0x0,L"description",0xb);
    QString::QString(local_88,(QArrayDataPointer *)local_a8);
    pQVar1 = (QVariant *)
             QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_88);
    ::QVariant::operator=(pQVar1,local_48);
    QString::~QString(local_88);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
    ::QVariant::~QVariant(local_48);
    QString::~QString((QString *)local_68);
    ::QVariant::QVariant(local_48,(QMap *)&local_e0);
    QList<QVariant>::append((QList<QVariant> *)g_outAccum,local_48);
    ::QVariant::~QVariant(local_48);
    QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_e0);
  }
  else {
    QtPrivate::Invoke::argument<QList<QVariant>>(local_68,"QVariantList",(QList *)g_outAccum);
    QMetaObject::invokeMethod<QMetaMethodArgument>(param_4,&DAT_002abb02,2,local_68);
    QList<QVariant>::clear((QList<QVariant> *)g_outAccum);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00234747  (anonymous_namespace)::paSourceListCb

/* (anonymous namespace)::paSourceListCb(pa_context*, pa_source_info const*, int, void*) */

void (anonymous_namespace)::paSourceListCb
               (pa_context *param_1,pa_source_info *param_2,int param_3,void *param_4)

{
  QVariant *pQVar1;
  long in_FS_OFFSET;
  undefined8 local_e0;
  undefined1 *local_d8;
  undefined1 *local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  QArrayDataPointer<char16_t> local_a8 [32];
  QString local_88 [32];
  Invoke local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_3 == 0) {
    if (*(int *)(param_2 + 0x134) == -1) {
      local_e0 = 0;
      QByteArrayView::QByteArrayView<char_const*,true>((QByteArrayView *)&local_b8,(char **)param_2)
      ;
      QString::fromUtf8(local_68,local_b8,local_b0);
      ::QVariant::QVariant(local_48,(QString *)local_68);
      local_d8 = &LAB_002abad4_4;
      QArrayDataPointer<char16_t>::QArrayDataPointer(local_a8,(QTypedArrayData *)0x0,L"name",4);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
      pQVar1 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_88);
      ::QVariant::operator=(pQVar1,local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_48);
      QString::~QString((QString *)local_68);
      if (*(long *)(param_2 + 0x10) == 0) {
        QByteArrayView::QByteArrayView<char_const*,true>
                  ((QByteArrayView *)&local_b8,(char **)param_2);
        QString::fromUtf8(local_68,local_b8,local_b0);
      }
      else {
        QByteArrayView::QByteArrayView<char_const*,true>
                  ((QByteArrayView *)&local_c8,(char **)(param_2 + 0x10));
        QString::fromUtf8(local_68,local_c8,local_c0);
      }
      ::QVariant::QVariant(local_48,(QString *)local_68);
      local_d0 = &LAB_002abb16;
      QArrayDataPointer<char16_t>::QArrayDataPointer
                (local_a8,(QTypedArrayData *)0x0,L"description",0xb);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
      pQVar1 = (QVariant *)
               QMap<QString,QVariant>::operator[]((QMap<QString,QVariant> *)&local_e0,local_88);
      ::QVariant::operator=(pQVar1,local_48);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer(local_a8);
      ::QVariant::~QVariant(local_48);
      QString::~QString((QString *)local_68);
      ::QVariant::QVariant(local_48,(QMap *)&local_e0);
      QList<QVariant>::append((QList<QVariant> *)g_inAccum,local_48);
      ::QVariant::~QVariant(local_48);
      QMap<QString,QVariant>::~QMap((QMap<QString,QVariant> *)&local_e0);
    }
  }
  else {
    QtPrivate::Invoke::argument<QList<QVariant>>(local_68,"QVariantList",(QList *)g_inAccum);
    QMetaObject::invokeMethod<QMetaMethodArgument>(param_4,&DAT_002abb2e,2,local_68);
    QList<QVariant>::clear((QList<QVariant> *)g_inAccum);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00234b2f  (anonymous_namespace)::paSubscribeCb

/* (anonymous namespace)::paSubscribeCb(pa_context*, pa_subscription_event_type, unsigned int,
   void*) */

void (anonymous_namespace)::paSubscribeCb
               (undefined8 param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  long lVar1;
  
  param_2 = param_2 & 0xf;
  if ((param_2 == 0) || (param_2 == 7)) {
    lVar1 = pa_context_get_server_info(param_1,paServerInfoCb,param_4);
    if (lVar1 != 0) {
      pa_operation_unref(lVar1);
    }
  }
  if (param_2 == 2) {
    lVar1 = pa_context_get_sink_input_info_list(param_1,paSinkInputInfoCb,param_4);
    if (lVar1 != 0) {
      pa_operation_unref(lVar1);
    }
  }
  if (param_2 == 0) {
    lVar1 = pa_context_get_sink_info_list(param_1,paSinkListCb,param_4);
    if (lVar1 != 0) {
      pa_operation_unref(lVar1);
    }
  }
  if (param_2 == 1) {
    lVar1 = pa_context_get_source_info_list(param_1,paSourceListCb,param_4);
    if (lVar1 != 0) {
      pa_operation_unref(lVar1);
    }
  }
  return;
}



// ==== 00234c33  (anonymous_namespace)::paStateCb

/* (anonymous namespace)::paStateCb(pa_context*, void*) */

void (anonymous_namespace)::paStateCb(pa_context *param_1,void *param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = pa_context_get_state(param_1);
  if (iVar1 == 4) {
    pa_context_set_subscribe_callback(param_1,paSubscribeCb,param_2);
    lVar2 = pa_context_subscribe(param_1,0x87,0,0);
    if (lVar2 != 0) {
      pa_operation_unref(lVar2);
    }
    lVar2 = pa_context_get_server_info(param_1,paServerInfoCb,param_2);
    if (lVar2 != 0) {
      pa_operation_unref(lVar2);
    }
    lVar2 = pa_context_get_sink_input_info_list(param_1,paSinkInputInfoCb,param_2);
    if (lVar2 != 0) {
      pa_operation_unref(lVar2);
    }
    lVar2 = pa_context_get_sink_info_list(param_1,paSinkListCb,param_2);
    if (lVar2 != 0) {
      pa_operation_unref(lVar2);
    }
    lVar2 = pa_context_get_source_info_list(param_1,paSourceListCb,param_2);
    if (lVar2 != 0) {
      pa_operation_unref(lVar2);
    }
  }
  return;
}



// ==== 00242654  (anonymous_namespace)::computeSunTimes(double,double,double&,double&)::{lambda(double)#1}::operator()

/* (anonymous namespace)::computeSunTimes(double, double, double&,
   double&)::{lambda(double)#1}::TEMPNAMEPLACEHOLDERVALUE(double) const */

double __thiscall
(anonymous_namespace)::computeSunTimes(double,double,double&,double&)::{lambda(double)#1}::
operator()(_lambda_double__1_ *this,double param_1)

{
  int iVar1;
  int iVar2;
  long in_FS_OFFSET;
  QDateTime local_30 [8];
  long local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = (long)((param_1 - 2440587.5) * 86400.0);
  QDateTime::fromSecsSinceEpoch((longlong)local_30);
  QDateTime::time();
  iVar1 = QTime::hour();
  QDateTime::time();
  iVar2 = QTime::minute();
  QDateTime::~QDateTime(local_30);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (double)iVar2 / 60.0 + (double)iVar1;
}



// ==== 0024276e  (anonymous_namespace)::computeSunTimes

/* (anonymous namespace)::computeSunTimes(double, double, double&, double&) */

void (anonymous_namespace)::computeSunTimes
               (double param_1,double param_2,double *param_3,double *param_4)

{
  long lVar1;
  long in_FS_OFFSET;
  double dVar2;
  double dVar3;
  double dVar4;
  _lambda_double__1_ local_71;
  undefined8 local_70;
  double local_68;
  double local_60;
  double local_58;
  double local_50;
  double local_48;
  double local_40;
  double local_38;
  double local_30;
  double local_28;
  double local_20;
  double local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_70 = 0x3f91df46a2529d39;
  lVar1 = QDateTime::currentSecsSinceEpoch();
  local_68 = (double)lVar1 / 86400.0 + 2440587.5;
  local_60 = floor((local_68 - 2451545.0) + 0.0008);
  local_58 = local_60 - param_2 / 360.0;
  local_50 = fmod(local_58 * 0.98560028 + 357.5291,360.0);
  dVar2 = sin(local_50 * 0.017453292519943295);
  dVar3 = sin((local_50 + local_50) * 0.017453292519943295);
  dVar4 = sin(local_50 * 3.0 * 0.017453292519943295);
  local_48 = dVar4 * 0.0003 + dVar3 * 0.02 + dVar2 * 1.9148;
  local_40 = fmod(local_50 + local_48 + 180.0 + 102.9372,360.0);
  dVar4 = local_58 + 2451545.0;
  dVar2 = sin(local_50 * 0.017453292519943295);
  dVar3 = sin((local_40 + local_40) * 0.017453292519943295);
  local_38 = (dVar2 * 0.0053 + dVar4) - dVar3 * 0.0069;
  local_30 = sin(local_40 * 0.017453292519943295);
  local_30 = local_30 * 0.39778850739794974;
  dVar2 = asin(local_30);
  local_28 = cos(dVar2);
  dVar2 = sin(param_1 * 0.017453292519943295);
  dVar2 = dVar2 * local_30;
  dVar3 = cos(param_1 * 0.017453292519943295);
  local_20 = (-0.014485726138606464 - dVar2) / (dVar3 * local_28);
  if ((local_20 < -1.0) || (1.0 < local_20)) {
    *param_3 = -1.0;
    *param_4 = -1.0;
  }
  else {
    local_18 = acos(local_20);
    local_18 = local_18 / 0.017453292519943295;
    dVar2 = (double)computeSunTimes(double,double,double&,double&)::{lambda(double)#1}::operator()
                              (&local_71,local_38 - local_18 / 360.0);
    *param_3 = dVar2;
    dVar2 = (double)computeSunTimes(double,double,double&,double&)::{lambda(double)#1}::operator()
                              (&local_71,local_18 / 360.0 + local_38);
    *param_4 = dVar2;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00291312  (anonymous_namespace)::initializer::initializer

/* (anonymous namespace)::initializer::initializer() */

void __thiscall (anonymous_namespace)::initializer::initializer(initializer *this)

{
  qInitResources_lelan();
  return;
}


