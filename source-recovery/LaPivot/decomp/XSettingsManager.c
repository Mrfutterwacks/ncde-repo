// Ghidra decompile of LaPivot.oracle — class/namespace XSettingsManager (11 functions). Raw; not source.

// ==== 001fe1dc  XSettingsManager::~XSettingsManager

/* XSettingsManager::~XSettingsManager() */

void __thiscall XSettingsManager::~XSettingsManager(XSettingsManager *this)

{
  if (*(long *)this != 0) {
    xcb_disconnect(*(undefined8 *)this);
  }
  QHash<QString,unsigned_int>::~QHash((QHash<QString,unsigned_int> *)(this + 0x40));
  QString::~QString((QString *)(this + 0x20));
  return;
}



// ==== 001fe226  XSettingsManager::start

/* XSettingsManager::start(QString const&, int) */

undefined8 __thiscall XSettingsManager::start(XSettingsManager *this,QString *param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  long in_FS_OFFSET;
  undefined2 local_11a;
  int local_118;
  int local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined8 local_108;
  undefined4 *local_100;
  byte *local_f8;
  byte *local_f0;
  void *local_e8;
  wchar16 *local_e0;
  wchar16 *local_d8;
  wchar16 *local_d0;
  wchar16 *local_c8;
  wchar16 *local_c0;
  undefined1 local_b8 [16];
  uint local_a8 [8];
  QString local_88 [32];
  QString local_68 [28];
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_47;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::operator=((QString *)(this + 0x20),param_1);
  *(int *)(this + 0x38) = param_2;
  local_118 = 0;
  uVar4 = xcb_connect(0,&local_118);
  *(undefined8 *)this = uVar4;
  if (*(long *)this != 0) {
    iVar2 = xcb_connection_has_error(*(undefined8 *)this);
    if (iVar2 == 0) {
      bVar1 = false;
      goto LAB_001fe2db;
    }
  }
  bVar1 = true;
LAB_001fe2db:
  if (bVar1) {
    *(undefined8 *)this = 0;
    uVar4 = 0;
  }
  else {
    local_108 = xcb_get_setup(*(undefined8 *)this);
    local_b8 = xcb_setup_roots_iterator(local_108);
    local_114 = 0;
    while ((local_114 < local_118 && (local_b8._8_4_ != 0))) {
      xcb_screen_next(local_b8);
      local_114 = local_114 + 1;
    }
    local_100 = (undefined4 *)local_b8._0_8_;
    if ((undefined4 *)local_b8._0_8_ == (undefined4 *)0x0) {
      uVar4 = 0;
    }
    else {
      *(undefined4 *)(this + 0xc) = *(undefined4 *)local_b8._0_8_;
      local_e0 = L"_XSETTINGS_S%1";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_a8,(QTypedArrayData *)0x0,L"_XSETTINGS_S%1",
                 0xe);
      QString::QString(local_88,(QArrayDataPointer *)local_a8);
      QChar::QChar<char16_t,true>((QChar *)&local_11a,L' ');
      QString::arg<int,true>(local_68,local_88,local_118,0,10,local_11a);
      uVar3 = atom((QString *)this);
      *(undefined4 *)(this + 0x10) = uVar3;
      QString::~QString(local_68);
      QString::~QString(local_88);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_a8);
      local_d8 = L"_XSETTINGS_SETTINGS";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,
                 L"_XSETTINGS_SETTINGS",0x13);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      uVar3 = atom((QString *)this);
      *(undefined4 *)(this + 0x14) = uVar3;
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
      local_d0 = L"MANAGER";
      QArrayDataPointer<char16_t>::QArrayDataPointer
                ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,L"MANAGER",7);
      QString::QString(local_68,(QArrayDataPointer *)local_88);
      uVar3 = atom((QString *)this);
      *(undefined4 *)(this + 0x18) = uVar3;
      QString::~QString(local_68);
      QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
      if (((*(int *)(this + 0x10) == 0) || (*(int *)(this + 0x14) == 0)) ||
         (*(int *)(this + 0x18) == 0)) {
        uVar4 = 0;
      }
      else {
        uVar3 = xcb_generate_id(*(undefined8 *)this);
        *(undefined4 *)(this + 8) = uVar3;
        local_10c = 0x800;
        local_4c = 0x400000;
        xcb_create_window(*(undefined8 *)this,0,*(undefined4 *)(this + 8),
                          *(undefined4 *)(this + 0xc),0xffffffff,0xffffffff,1,1,0,1,local_100[8],
                          0x800,&local_4c);
        xcb_change_property(*(undefined8 *)this,2,*(undefined4 *)(this + 8),
                            *(undefined4 *)(this + 0x14),*(undefined4 *)(this + 0x14),8,0,0);
        xcb_flush(*(undefined8 *)this);
        local_110 = 0;
        while( true ) {
          local_f8 = (byte *)xcb_wait_for_event(*(undefined8 *)this);
          if (local_f8 == (byte *)0x0) break;
          if (((*local_f8 & 0x7f) == 0x1c) &&
             (local_f0 = local_f8, *(int *)(local_f8 + 4) == *(int *)(this + 8))) {
            local_110 = *(undefined4 *)(local_f8 + 0xc);
            free(local_f8);
            break;
          }
          free(local_f8);
        }
        xcb_set_selection_owner
                  (*(undefined8 *)this,*(undefined4 *)(this + 8),*(undefined4 *)(this + 0x10),
                   local_110);
        uVar3 = xcb_get_selection_owner(*(undefined8 *)this,*(undefined4 *)(this + 0x10));
        local_e8 = (void *)xcb_get_selection_owner_reply(*(undefined8 *)this,uVar3,0);
        if ((local_e8 == (void *)0x0) || (*(int *)((long)local_e8 + 8) != *(int *)(this + 8))) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        free(local_e8);
        if (bVar1) {
          memset(&local_48,0,0x20);
          local_48 = 0x21;
          local_47 = 0x20;
          local_44 = *(undefined4 *)(this + 0xc);
          local_40 = *(undefined4 *)(this + 0x18);
          local_3c = local_110;
          local_38 = *(undefined4 *)(this + 0x10);
          local_34 = *(undefined4 *)(this + 8);
          xcb_send_event(*(undefined8 *)this,0,*(undefined4 *)(this + 0xc),0x20000,&local_48);
          *(undefined4 *)(this + 0x1c) = 0;
          local_a8[0] = 0;
          local_c8 = L"Gtk/CursorThemeName";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,
                     L"Gtk/CursorThemeName",0x13);
          QString::QString(local_68,(QArrayDataPointer *)local_88);
          QHash<QString,unsigned_int>::insert
                    ((QHash<QString,unsigned_int> *)(this + 0x40),local_68,local_a8);
          QString::~QString(local_68);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
          local_a8[0] = 0;
          local_c0 = L"Gtk/CursorThemeSize";
          QArrayDataPointer<char16_t>::QArrayDataPointer
                    ((QArrayDataPointer<char16_t> *)local_88,(QTypedArrayData *)0x0,
                     L"Gtk/CursorThemeSize",0x13);
          QString::QString(local_68,(QArrayDataPointer *)local_88);
          QHash<QString,unsigned_int>::insert
                    ((QHash<QString,unsigned_int> *)(this + 0x40),local_68,local_a8);
          QString::~QString(local_68);
          QArrayDataPointer<char16_t>::~QArrayDataPointer((QArrayDataPointer<char16_t> *)local_88);
          publish(this);
          uVar4 = 1;
        }
        else {
          uVar4 = 0;
        }
      }
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar4;
}



// ==== 001fead8  XSettingsManager::started

/* XSettingsManager::started() const */

undefined8 __thiscall XSettingsManager::started(XSettingsManager *this)

{
  undefined8 uVar1;
  
  if ((*(long *)this == 0) || (*(int *)(this + 8) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 001feb06  XSettingsManager::setCursorSize

/* XSettingsManager::setCursorSize(int) */

void __thiscall XSettingsManager::setCursorSize(XSettingsManager *this,int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  char cVar3;
  undefined4 *puVar4;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar3 = started(this);
  if ((cVar3 == '\x01') && (param_1 != *(int *)(this + 0x38))) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if (!bVar2) {
    *(int *)(this + 0x38) = param_1;
    *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 1;
    uVar1 = *(undefined4 *)(this + 0x1c);
    QArrayDataPointer<char16_t>::QArrayDataPointer
              (local_58,(QTypedArrayData *)0x0,L"Gtk/CursorThemeSize",0x13);
    QString::QString(local_38,(QArrayDataPointer *)local_58);
    puVar4 = (undefined4 *)QHash<QString,unsigned_int>::operator[]((QString *)(this + 0x40));
    *puVar4 = uVar1;
    QString::~QString(local_38);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
    publish(this);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fec4c  XSettingsManager::atom

/* XSettingsManager::atom(QString const&) */

undefined4 XSettingsManager::atom(QString *param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  void *__ptr;
  long in_FS_OFFSET;
  undefined4 local_44;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::toLatin1(local_38);
  uVar3 = QByteArray::constData((QByteArray *)local_38);
  uVar1 = QByteArray::size((QByteArray *)local_38);
  uVar2 = xcb_intern_atom(*(undefined8 *)param_1,0,uVar1,uVar3);
  __ptr = (void *)xcb_intern_atom_reply(*(undefined8 *)param_1,uVar2,0);
  if (__ptr == (void *)0x0) {
    local_44 = 0;
  }
  else {
    local_44 = *(undefined4 *)((long)__ptr + 8);
  }
  free(__ptr);
  QByteArray::~QByteArray((QByteArray *)local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_44;
}



// ==== 001fed53  XSettingsManager::put32

/* XSettingsManager::put32(QByteArray&, unsigned int) */

void XSettingsManager::put32(QByteArray *param_1,uint param_2)

{
  long in_FS_OFFSET;
  char local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_14 = (char)param_2;
  local_13 = (undefined1)(param_2 >> 8);
  local_12 = (undefined1)(param_2 >> 0x10);
  local_11 = (undefined1)(param_2 >> 0x18);
  QByteArray::append(param_1,&local_14,4);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fedc1  XSettingsManager::put16

/* XSettingsManager::put16(QByteArray&, unsigned short) */

void XSettingsManager::put16(QByteArray *param_1,ushort param_2)

{
  long in_FS_OFFSET;
  ushort local_12;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_12 = param_2;
  QByteArray::append(param_1,(char *)&local_12,2);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fee21  XSettingsManager::pad4

/* XSettingsManager::pad4(QByteArray&) */

void XSettingsManager::pad4(QByteArray *param_1)

{
  uint uVar1;
  
  while( true ) {
    uVar1 = QByteArray::size(param_1);
    if ((uVar1 & 3) == 0) break;
    QByteArray::append((char)param_1);
  }
  return;
}



// ==== 001fee5e  XSettingsManager::appendString

/* XSettingsManager::appendString(QByteArray&, QString const&, QString const&) const */

void XSettingsManager::appendString(QByteArray *param_1,QString *param_2,QString *param_3)

{
  ushort uVar1;
  uint uVar2;
  long in_FS_OFFSET;
  uint local_5c;
  QString local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::toLatin1(local_58);
  QString::toUtf8(local_38);
  QByteArray::append((char)param_2);
  QByteArray::append((char)param_2);
  uVar1 = QByteArray::size((QByteArray *)local_58);
  put16((QByteArray *)param_2,uVar1);
  QByteArray::append((QByteArray *)param_2);
  pad4((QByteArray *)param_2);
  local_5c = 0;
  uVar2 = QHash<QString,unsigned_int>::value
                    ((QHash<QString,unsigned_int> *)(param_1 + 0x40),param_3,&local_5c);
  put32((QByteArray *)param_2,uVar2);
  uVar2 = QByteArray::size((QByteArray *)local_38);
  put32((QByteArray *)param_2,uVar2);
  QByteArray::append((QByteArray *)param_2);
  pad4((QByteArray *)param_2);
  QByteArray::~QByteArray((QByteArray *)local_38);
  QByteArray::~QByteArray((QByteArray *)local_58);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001fefea  XSettingsManager::appendInt

/* XSettingsManager::appendInt(QByteArray&, QString const&, int) const */

void __thiscall
XSettingsManager::appendInt(XSettingsManager *this,QByteArray *param_1,QString *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  long in_FS_OFFSET;
  uint local_3c;
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QString::toLatin1(local_38);
  QByteArray::append((char)param_1);
  QByteArray::append((char)param_1);
  uVar1 = QByteArray::size((QByteArray *)local_38);
  put16(param_1,uVar1);
  QByteArray::append(param_1);
  pad4(param_1);
  local_3c = 0;
  uVar2 = QHash<QString,unsigned_int>::value
                    ((QHash<QString,unsigned_int> *)(this + 0x40),param_2,&local_3c);
  put32(param_1,uVar2);
  put32(param_1,param_3);
  QByteArray::~QByteArray((QByteArray *)local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001ff11c  XSettingsManager::publish

/* XSettingsManager::publish() */

void __thiscall XSettingsManager::publish(XSettingsManager *this)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long in_FS_OFFSET;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  QArrayDataPointer<char16_t> local_58 [32];
  QString local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_78 = 0;
  local_70 = 0;
  local_68 = 0;
  QByteArray::append((char)&local_78);
  QByteArray::append((longlong)&local_78,'\x03');
  put32((QByteArray *)&local_78,*(uint *)(this + 0x1c));
  put32((QByteArray *)&local_78,2);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"Gtk/CursorThemeName",0x13);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  appendString((QByteArray *)this,(QString *)&local_78,local_38);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  iVar1 = *(int *)(this + 0x38);
  QArrayDataPointer<char16_t>::QArrayDataPointer
            (local_58,(QTypedArrayData *)0x0,L"Gtk/CursorThemeSize",0x13);
  QString::QString(local_38,(QArrayDataPointer *)local_58);
  appendInt(this,(QByteArray *)&local_78,local_38,iVar1);
  QString::~QString(local_38);
  QArrayDataPointer<char16_t>::~QArrayDataPointer(local_58);
  uVar3 = QByteArray::constData((QByteArray *)&local_78);
  uVar2 = QByteArray::size((QByteArray *)&local_78);
  xcb_change_property(*(undefined8 *)this,0,*(undefined4 *)(this + 8),*(undefined4 *)(this + 0x14),
                      *(undefined4 *)(this + 0x14),8,uVar2,uVar3);
  xcb_flush(*(undefined8 *)this);
  QByteArray::~QByteArray((QByteArray *)&local_78);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


