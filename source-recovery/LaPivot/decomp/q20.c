// Ghidra decompile of LaPivot.oracle — class/namespace q20 (2 functions). Raw; not source.

// ==== 00150887  q20::is_constant_evaluated

/* q20::is_constant_evaluated() */

undefined8 q20::is_constant_evaluated(void)

{
  return 0;
}



// ==== 001a4a5b  q20::countl_zero<unsigned_long>

/* std::enable_if<is_unsigned_v<unsigned long>, int>::type q20::countl_zero<unsigned long>(unsigned
   long) */

ulong q20::countl_zero<unsigned_long>(ulong param_1)

{
  ulong uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0x40;
  }
  else {
    uVar1 = 0x3f;
    if (param_1 != 0) {
      for (; param_1 >> uVar1 == 0; uVar1 = uVar1 - 1) {
      }
    }
    uVar1 = uVar1 ^ 0x3f;
  }
  return uVar1;
}


