// Ghidra decompile of LaPivot.oracle — class/namespace QPolygonF (2 functions). Raw; not source.

// ==== 00289efe  QPolygonF::~QPolygonF

/* QPolygonF::~QPolygonF() */

void __thiscall QPolygonF::~QPolygonF(QPolygonF *this)

{
  QList<QPointF>::~QList((QList<QPointF> *)this);
  return;
}



// ==== 00289f1a  QPolygonF::translate

/* QPolygonF::translate(double, double) */

void __thiscall QPolygonF::translate(QPolygonF *this,double param_1,double param_2)

{
  long in_FS_OFFSET;
  QPointF local_28 [24];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPointF::QPointF(local_28,param_1,param_2);
  QPolygonF::translate((QPointF *)this);
                    /* try { // try from 00289f77 to 00389f7b has its CatchHandler @ 0028b2f4 */
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


