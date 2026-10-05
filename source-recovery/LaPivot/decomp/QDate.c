// Ghidra decompile of LaPivot.oracle — class/namespace QDate (4 functions). Raw; not source.

// ==== 0026e946  QDate::isValid

/* QDate::isValid() const */

undefined8 __thiscall QDate::isValid(QDate *this)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)this;
  lVar2 = minJd();
  if ((lVar2 <= lVar1) && (lVar1 = *(long *)this, lVar2 = maxJd(), lVar1 <= lVar2)) {
    return 1;
  }
  return 0;
}



// ==== 0026e987  QDate::fromString

/* QDate::fromString(QString const&, QString const&, int) */

void QDate::fromString(QString *param_1,QString *param_2,int param_3)

{
  undefined1 auVar1 [12];
  
                    /* try { // try from 0026e98c to 0036e990 has its CatchHandler @ 0026eb04 */
  auVar1 = qToStringViewIgnoringNull<QString,true>(param_2);
  QDate::fromString(param_1,auVar1._0_8_,auVar1._8_4_,param_3);
  return;
}



// ==== 0026e9ba  QDate::minJd

/* QDate::minJd() */

undefined8 QDate::minJd(void)

{
  return 0xffffff49611006e1;
}



// ==== 0026e9ca  QDate::maxJd

/* QDate::maxJd() */

undefined8 QDate::maxJd(void)

{
  return 0xb69f248054;
}


