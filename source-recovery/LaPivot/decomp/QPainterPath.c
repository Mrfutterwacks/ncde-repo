// Ghidra decompile of LaPivot.oracle — class/namespace QPainterPath (4 functions). Raw; not source.

// ==== 0028a49e  QPainterPath::moveTo

/* QPainterPath::moveTo(double, double) */

void __thiscall QPainterPath::moveTo(QPainterPath *this,double param_1,double param_2)

{
  long in_FS_OFFSET;
  QPointF local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPointF::QPointF(local_28,param_1,param_2);
  QPainterPath::moveTo((QPointF *)this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0028a50c  QPainterPath::lineTo

/* QPainterPath::lineTo(double, double) */

void __thiscall QPainterPath::lineTo(QPainterPath *this,double param_1,double param_2)

{
  long in_FS_OFFSET;
  QPointF local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPointF::QPointF(local_28,param_1,param_2);
  QPainterPath::lineTo((QPointF *)this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0028a57a  QPainterPath::cubicTo

/* QPainterPath::cubicTo(double, double, double, double, double, double) */

void __thiscall
QPainterPath::cubicTo
          (QPainterPath *this,double param_1,double param_2,double param_3,double param_4,
          double param_5,double param_6)

{
  long in_FS_OFFSET;
  QPointF local_48 [16];
  QPointF local_38 [16];
  QPointF local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
                    /* try { // try from 0028a5c9 to 0038a5cd has its CatchHandler @ 0028b44b */
  QPointF::QPointF(local_28,param_5,param_6);
  QPointF::QPointF(local_38,param_3,param_4);
  QPointF::QPointF(local_48,param_1,param_2);
  QPainterPath::cubicTo((QPointF *)this,local_48,local_38);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0028a63c  QPainterPath::addEllipse

/* QPainterPath::addEllipse(QPointF const&, double, double) */

void __thiscall
QPainterPath::addEllipse(QPainterPath *this,QPointF *param_1,double param_2,double param_3)

{
  long in_FS_OFFSET;
  double dVar1;
  double dVar2;
  QRectF local_38 [40];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  dVar1 = (double)QPointF::y(param_1);
  dVar2 = (double)QPointF::x(param_1);
                    /* try { // try from 0028a6be to 0038a6c2 has its CatchHandler @ 0028b47d */
  QRectF::QRectF(local_38,dVar2 - param_2,dVar1 - param_3,param_2 + param_2,param_3 + param_3);
  QPainterPath::addEllipse((QRectF *)this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


