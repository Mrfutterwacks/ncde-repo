// Ghidra decompile of LaPivot.oracle — class/namespace QPainter (7 functions). Raw; not source.

// ==== 0028a22a  QPainter::setBrush

/* QPainter::setBrush(QBrush&&) */

void __thiscall QPainter::setBrush(QPainter *this,QBrush *param_1)

{
  QPainter::doSetBrush((QBrush *)this,param_1);
  return;
}



// ==== 0028a254  QPainter::drawLine

/* QPainter::drawLine(QLineF const&) */

void __thiscall QPainter::drawLine(QPainter *this,QLineF *param_1)

{
  QPainter::drawLines((QLineF *)this,(int)param_1);
  return;
}



// ==== 0028a280  QPainter::drawLine

/* QPainter::drawLine(QPointF const&, QPointF const&) */

void __thiscall QPainter::drawLine(QPainter *this,QPointF *param_1,QPointF *param_2)

{
  long in_FS_OFFSET;
  QLineF local_38 [40];
  long local_10;
  
                    /* try { // try from 0028a283 to 0038a287 has its CatchHandler @ 0028b6d9 */
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QLineF::QLineF(local_38,param_1,param_2);
  drawLine(this,local_38);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0028a2e4  QPainter::drawPolygon

/* QPainter::drawPolygon(QPolygonF const&, Qt::FillRule) */

void __thiscall QPainter::drawPolygon(QPainter *this,QList<QPointF> *param_1,undefined4 param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar1 = QList<QPointF>::size(param_1);
                    /* try { // try from 0028a306 to 0038a30a has its CatchHandler @ 0028b392 */
  uVar2 = QList<QPointF>::constData(param_1);
  QPainter::drawPolygon(this,uVar2,uVar1,param_3);
  return;
}



// ==== 0028a330  QPainter::drawEllipse

/* QPainter::drawEllipse(QPointF const&, double, double) */

void __thiscall QPainter::drawEllipse(QPainter *this,QPointF *param_1,double param_2,double param_3)

{
  long in_FS_OFFSET;
  double dVar1;
  double dVar2;
  QRectF local_38 [40];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  dVar1 = (double)QPointF::y(param_1);
  dVar2 = (double)QPointF::x(param_1);
  QRectF::QRectF(local_38,dVar2 - param_2,dVar1 - param_3,param_2 + param_2,param_3 + param_3);
                    /* try { // try from 0028a3dd to 0038a3e1 has its CatchHandler @ 0028b425 */
  QPainter::drawEllipse((QRectF *)this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 0028a404  QPainter::setPen

/* QPainter::setPen(QPen const&) */

void __thiscall QPainter::setPen(QPainter *this,QPen *param_1)

{
                    /* try { // try from 0028a422 to 0038a426 has its CatchHandler @ 0028b411 */
  QPainter::doSetPen((QPen *)this,param_1);
  return;
}



// ==== 0028a430  QPainter::translate

/* QPainter::translate(double, double) */

void __thiscall QPainter::translate(QPainter *this,double param_1,double param_2)

{
  long in_FS_OFFSET;
  QPointF local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPointF::QPointF(local_28,param_1,param_2);
  QPainter::translate((QPointF *)this);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0028a498 to 0038a49c has its CatchHandler @ 0028b3d3 */
    __stack_chk_fail();
  }
  return;
}


