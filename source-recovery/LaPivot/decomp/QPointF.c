// Ghidra decompile of LaPivot.oracle — class/namespace QPointF (3 functions). Raw; not source.

// ==== 00289e36  QPointF::QPointF

/* QPointF::QPointF(double, double) */

void __thiscall QPointF::QPointF(QPointF *this,double param_1,double param_2)

{
  *(double *)this = param_1;
  *(double *)(this + 8) = param_2;
  return;
}



// ==== 00289e66  QPointF::x

/* QPointF::x() const */

undefined8 __thiscall QPointF::x(QPointF *this)

{
  return *(undefined8 *)this;
}



// ==== 00289e78  QPointF::y

/* QPointF::y() const */

undefined8 __thiscall QPointF::y(QPointF *this)

{
                    /* try { // try from 00289e7a to 00389e7e has its CatchHandler @ 0028b2b6 */
  return *(undefined8 *)(this + 8);
}


