// Ghidra decompile of LaPivot.oracle — class/namespace QRandomGenerator (6 functions). Raw; not source.

// ==== 0025d52c  QRandomGenerator::generate

/* QRandomGenerator::generate() */

void __thiscall QRandomGenerator::generate(QRandomGenerator *this)

{
  QRandomGenerator::_fillRange(this,0);
  return;
}



// ==== 0025d550  QRandomGenerator::bounded

/* QRandomGenerator::bounded(unsigned int) */

ulong __thiscall QRandomGenerator::bounded(QRandomGenerator *this,uint param_1)

{
  uint uVar1;
  uint uVar2;
  
                    /* try { // try from 0025d55c to 0035d560 has its CatchHandler @ 0025d82a */
  uVar1 = generate(this);
  uVar2 = max();
  return ((ulong)param_1 * (ulong)uVar1) / ((ulong)uVar2 + 1);
}



// ==== 0025d5a2  QRandomGenerator::bounded

/* QRandomGenerator::bounded(unsigned int, unsigned int) */

int __thiscall QRandomGenerator::bounded(QRandomGenerator *this,uint param_1,uint param_2)

{
  int iVar1;
  
                    /* try { // try from 0025d5b3 to 0035d5b7 has its CatchHandler @ 0025d881 */
  iVar1 = bounded(this,param_2 - param_1);
  return iVar1 + param_1;
}



// ==== 0025d5d2  QRandomGenerator::bounded

/* QRandomGenerator::bounded(int) */

void __thiscall QRandomGenerator::bounded(QRandomGenerator *this,int param_1)

{
  bounded(this,0,param_1);
  return;
}



// ==== 0025d5f7  QRandomGenerator::max

/* QRandomGenerator::max() */

void QRandomGenerator::max(void)

{
  std::numeric_limits<unsigned_int>::max();
  return;
}



// ==== 0025d602  QRandomGenerator::system

/* QRandomGenerator::system() */

void QRandomGenerator::system(void)

{
  QRandomGenerator64::system();
  return;
}


