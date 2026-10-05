// Ghidra decompile of LaPivot.oracle — class/namespace GliaTalkProto (3 functions). Raw; not source.

// ==== 00176f9e  GliaTalkProto::internAtom

/* GliaTalkProto::internAtom(xcb_connection_t*, char const*) */

undefined4 GliaTalkProto::internAtom(xcb_connection_t *param_1,char *param_2)

{
  long lVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  void *__ptr;
  long in_FS_OFFSET;
  undefined4 local_1c;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  uVar2 = qstrlen(param_2);
  uVar3 = xcb_intern_atom(param_1,0,uVar2,param_2);
  __ptr = (void *)xcb_intern_atom_reply(param_1,uVar3,0);
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



// ==== 0017703d  GliaTalkProto::readMenus

/* GliaTalkProto::readMenus(xcb_connection_t*, unsigned int) */

GliaTalkProto * __thiscall
GliaTalkProto::readMenus(GliaTalkProto *this,xcb_connection_t *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  void *__ptr;
  char *pcVar5;
  long in_FS_OFFSET;
  uint local_50;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  iVar2 = internAtom(param_1,"_NCDE_MENUS");
  if (iVar2 == 0) {
    QString::QString((QString *)this);
  }
  else {
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    local_50 = 0;
    while( true ) {
      uVar3 = xcb_get_property(param_1,0,param_2,iVar2,0,local_50 >> 2,0x10000);
      __ptr = (void *)xcb_get_property_reply(param_1,uVar3,0);
      if (__ptr == (void *)0x0) break;
      iVar4 = xcb_get_property_value_length(__ptr);
      if (0 < iVar4) {
        pcVar5 = (char *)xcb_get_property_value(__ptr);
        QByteArray::append((QByteArray *)&local_38,pcVar5,(long)iVar4);
      }
      iVar1 = *(int *)((long)__ptr + 0xc);
      free(__ptr);
      if (iVar1 == 0) {
        QString::fromUtf8<void>((QString *)this,(QByteArray *)&local_38);
        goto LAB_0017718d;
      }
      local_50 = local_50 + iVar4;
    }
    QString::QString((QString *)this);
LAB_0017718d:
    QByteArray::~QByteArray((QByteArray *)&local_38);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001771e7  GliaTalkProto::sendInvoke

/* GliaTalkProto::sendInvoke(xcb_connection_t*, unsigned int, unsigned int) */

void GliaTalkProto::sendInvoke(xcb_connection_t *param_1,uint param_2,uint param_3)

{
  int iVar1;
  long in_FS_OFFSET;
  undefined1 local_38 [4];
  uint uStack_34;
  int iStack_30;
  uint uStack_2c;
  undefined1 local_28 [16];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  iVar1 = internAtom(param_1,"_NCDE_MENU_INVOKE");
  if (iVar1 != 0) {
    local_28 = (undefined1  [16])0x0;
    stack0xffffffffffffffc9 = SUB1615((undefined1  [16])0x0,1);
    local_38._0_2_ = 0x2021;
    uStack_34 = param_2;
    iStack_30 = iVar1;
    uStack_2c = param_3;
    xcb_send_event(param_1,0,param_2,0,local_38);
    xcb_flush(param_1);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


