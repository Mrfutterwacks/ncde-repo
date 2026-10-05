// Ghidra decompile of LaPivot.oracle — class/namespace QColor (7 functions). Raw; not source.

// ==== 00156c30  QColor::QColor

/* QColor::QColor() */

void __thiscall QColor::QColor(QColor *this)

{
  *(undefined4 *)this = 0;
  CT::CT((CT *)(this + 4),0xffff,0,0,0,0);
  return;
}



// ==== 00156c74  QColor::QColor

/* QColor::QColor(int, int, int, int) */

void __thiscall QColor::QColor(QColor *this,int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  cVar1 = isRgbaValid(param_1,param_2,param_3,param_4);
  *(uint *)this = (uint)(cVar1 != '\0');
  if (*(int *)this == 1) {
    uVar5 = (short)(param_3 << 8) + (short)param_3;
  }
  else {
    uVar5 = 0;
  }
  if (*(int *)this == 1) {
    uVar3 = (short)(param_2 << 8) + (short)param_2;
  }
  else {
    uVar3 = 0;
  }
  if (*(int *)this == 1) {
    uVar4 = (short)param_1 * 0x101;
  }
  else {
    uVar4 = 0;
  }
  if (*(int *)this == 1) {
    uVar2 = (short)param_4 * 0x101;
  }
  else {
    uVar2 = 0;
  }
  CT::CT((CT *)(this + 4),uVar2,uVar4,uVar3,uVar5,0);
  return;
}



// ==== 00156d5a  QColor::isRgbaValid

/* QColor::isRgbaValid(int, int, int, int) */

undefined8 QColor::isRgbaValid(int param_1,int param_2,int param_3,int param_4)

{
  undefined8 uVar1;
  
  if (((((uint)param_1 < 0x100) && ((uint)param_2 < 0x100)) && ((uint)param_3 < 0x100)) &&
     ((uint)param_4 < 0x100)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 00156da0  QColor::CT::CT

/* QColor::CT::CT(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short) */

void __thiscall
QColor::CT::CT(CT *this,ushort param_1,ushort param_2,ushort param_3,ushort param_4,ushort param_5)

{
  *(ushort *)this = param_1;
  *(ushort *)(this + 2) = param_2;
  *(ushort *)(this + 4) = param_3;
  *(ushort *)(this + 6) = param_4;
  *(ushort *)(this + 8) = param_5;
  return;
}



// ==== 00156dfc  QColor::QColor

/* QColor::QColor(QString const&) */

void __thiscall QColor::QColor(QColor *this,QString *param_1)

{
  long in_FS_OFFSET;
  undefined1 auVar1 [16];
  undefined8 local_28;
  undefined8 local_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QAnyStringView::QAnyStringView((QAnyStringView *)&local_28,param_1);
  auVar1 = ::QColor::fromString(local_28,local_20);
  *(undefined1 (*) [16])this = auVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00156e64  QColor::QColor

/* QColor::QColor(char const*) */

void __thiscall QColor::QColor(QColor *this,char *param_1)

{
  long in_FS_OFFSET;
  undefined1 auVar1 [16];
  char *local_38;
  QColor *local_30;
  undefined8 local_28;
  undefined8 local_20;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_38 = param_1;
  local_30 = this;
  QAnyStringView::QAnyStringView<char_const*,true>((QAnyStringView *)&local_28,&local_38);
  auVar1 = ::QColor::fromString(local_28,local_20);
  *(undefined1 (*) [16])local_30 = auVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00156ecc  QColor::isValid

/* QColor::isValid() const */

undefined4 __thiscall QColor::isValid(QColor *this)

{
  return CONCAT31((int3)((uint)*(int *)this >> 8),*(int *)this != 0);
}


