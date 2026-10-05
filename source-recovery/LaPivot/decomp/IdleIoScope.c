// Ghidra decompile of LaPivot.oracle — class/namespace IdleIoScope (2 functions). Raw; not source.

// ==== 00209536  IdleIoScope::IdleIoScope

/* IdleIoScope::IdleIoScope(bool) */

void __thiscall IdleIoScope::IdleIoScope(IdleIoScope *this,bool param_1)

{
  *this = (IdleIoScope)param_1;
  if (*this != (IdleIoScope)0x0) {
    syscall(0xfb,1,0,0x6007);
  }
  return;
}



// ==== 0020957c  IdleIoScope::~IdleIoScope

/* IdleIoScope::~IdleIoScope() */

void __thiscall IdleIoScope::~IdleIoScope(IdleIoScope *this)

{
  if (*this != (IdleIoScope)0x0) {
    syscall(0xfb,1,0,0x4004);
  }
  return;
}


