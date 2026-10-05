// Ghidra decompile of LaPivot.oracle — class/namespace Qt (66 functions). Raw; not source.

// ==== 001508f7  Qt::operator<

/* Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::weak_ordering, QtPrivate::CompareAgainstLiteralZero) */

byte Qt::operator<(byte param_1)

{
  return param_1 >> 7;
}



// ==== 00150908  Qt::is_lt

/* Qt::is_lt(Qt::weak_ordering) */

void Qt::is_lt(undefined1 param_1)

{
  long in_FS_OFFSET;
  CompareAgainstLiteralZero local_11;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QtPrivate::CompareAgainstLiteralZero::CompareAgainstLiteralZero(&local_11,(_func_void *)0x0);
  operator<(param_1);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00150960  Qt::operator<

/* Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::strong_ordering, QtPrivate::CompareAgainstLiteralZero) */

byte Qt::operator<(byte param_1)

{
  return param_1 >> 7;
}



// ==== 00150971  Qt::operator>

/* Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::strong_ordering, QtPrivate::CompareAgainstLiteralZero) */

bool Qt::operator>(char param_1)

{
  return '\0' < param_1;
}



// ==== 00150984  Qt::operator>=

/* Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::strong_ordering, QtPrivate::CompareAgainstLiteralZero) */

undefined4 Qt::operator>=(byte param_1)

{
  return CONCAT31((int3)(~(uint)param_1 >> 8),(byte)~(uint)param_1 >> 7);
}



// ==== 00150997  Qt::is_lt

/* Qt::is_lt(Qt::strong_ordering) */

void Qt::is_lt(undefined1 param_1)

{
  long in_FS_OFFSET;
  CompareAgainstLiteralZero local_11;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QtPrivate::CompareAgainstLiteralZero::CompareAgainstLiteralZero(&local_11,(_func_void *)0x0);
  operator<(param_1);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001509ef  Qt::is_gt

/* Qt::is_gt(Qt::strong_ordering) */

void Qt::is_gt(undefined1 param_1)

{
  long in_FS_OFFSET;
  CompareAgainstLiteralZero local_11;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QtPrivate::CompareAgainstLiteralZero::CompareAgainstLiteralZero(&local_11,(_func_void *)0x0);
  operator>(param_1);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00150a47  Qt::is_gteq

/* Qt::is_gteq(Qt::strong_ordering) */

void Qt::is_gteq(undefined1 param_1)

{
  long in_FS_OFFSET;
  CompareAgainstLiteralZero local_11;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QtPrivate::CompareAgainstLiteralZero::CompareAgainstLiteralZero(&local_11,(_func_void *)0x0);
  operator>=(param_1);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00155310  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > >
   >*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 00155334  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001a4062  Qt::compareThreeWay<int,int,true,true>

/* Qt::strong_ordering Qt::compareThreeWay<int, int, true, true>(int, int) */

undefined8 Qt::compareThreeWay<int,int,true,true>(int param_1,int param_2)

{
  undefined8 uVar1;
  
  if (param_1 == param_2) {
    uVar1 = 0;
  }
  else if (param_1 < param_2) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 001ab6e6  Qt::totally_ordered_wrapper<QAbstractItemModel_const*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QAbstractItemModel
   const*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::totally_ordered_wrapper<QAbstractItemModel_const*>::totally_ordered_wrapper
               (_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QAbstractItemModel_const*> *)param_1,(QAbstractItemModel *)0x0
            );
  return;
}



// ==== 001ab70a  Qt::totally_ordered_wrapper<QAbstractItemModel_const*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QAbstractItemModel
   const*>::totally_ordered_wrapper(QAbstractItemModel const*) */

void __thiscall
Qt::totally_ordered_wrapper<QAbstractItemModel_const*>::totally_ordered_wrapper
          (totally_ordered_wrapper<QAbstractItemModel_const*> *this,QAbstractItemModel *param_1)

{
  *(QAbstractItemModel **)this = param_1;
  return;
}



// ==== 001afb3c  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 001afb56  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 001afb76  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 001b1a05  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QCborContainerPrivate*>&,
   Qt::totally_ordered_wrapper<QCborContainerPrivate*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QCborContainerPrivate>
            ((QCborContainerPrivate **)param_1,(QCborContainerPrivate **)param_2);
  return;
}



// ==== 001b1e8e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 001b1eb2  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 001b1ecc  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 001b1eec  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 001b20d6  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > >
   >*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 001b20fa  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 001b2114  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 001b2134  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 001b231e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > >
   >*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 001b2342  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const
    */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 001b235c  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 001b237c  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 001b4b0a  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::totally_ordered_wrapper(decltype(nullptr))
    */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 001b4b2e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 001b4b48  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 001b4b68  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 001b8d29  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant,
   std::less<QString>, std::allocator<std::pair<QString const, QVariant> > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 001b904e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001b96ea  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001b9d04  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001bb95c  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*>::reset(QMapData<std::map<QString,
   QVariant, std::less<QString>, std::allocator<std::pair<QString const, QVariant> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001bd49e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001c0894  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>::operator*

/* QMapData<std::map<QString, QVariant, std::less<QString>, std::allocator<std::pair<QString const,
   QVariant> > > >& Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant,
   std::less<QString>, std::allocator<std::pair<QString const, QVariant> > >
   >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}



// ==== 001c7ed6  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::reset(QMapData<std::map<QString, bool,
   std::less<QString>, std::allocator<std::pair<QString const, bool> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001c7ef0  Qt::totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>::operator*

/* QMapData<std::map<QString, bool, std::less<QString>, std::allocator<std::pair<QString const,
   bool> > > >& Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}



// ==== 001d476f  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, bool, std::less<QString>,
   std::allocator<std::pair<QString const, bool> > > >*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QString,bool,std::less<QString>,std::allocator<std::pair<QString_const,bool>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 001dab9e  Qt::operator==

/* bool Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QMapData<std::map<QString,
   QMap<QString, QVariant>, std::less<QString>, std::allocator<std::pair<QString const,
   QMap<QString, QVariant> > > > >*> const&, Qt::totally_ordered_wrapper<QMapData<std::map<QString,
   QMap<QString, QVariant>, std::less<QString>, std::allocator<std::pair<QString const,
   QMap<QString, QVariant> > > > >*> const&) */

bool Qt::operator==(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  undefined1 uVar1;
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QMapData *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QMapData *)
             totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
             ::get((totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
                    *)param_2);
  uVar1 = std::equal_to<void>::operator()(&local_19,(QMapData **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (bool)uVar1;
}



// ==== 001daeda  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::reset(QMapData<std::map<QString, QMap<QString, QVariant>, std::less<QString>,
   std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001db43c  Qt::operator==

/* bool Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QMapData<std::map<QString, double,
   std::less<QString>, std::allocator<std::pair<QString const, double> > > >*> const&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*> const&) */

bool Qt::operator==(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  undefined1 uVar1;
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QMapData *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QMapData *)
             totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
             ::get((totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
                    *)param_2);
  uVar1 = std::equal_to<void>::operator()(&local_19,(QMapData **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (bool)uVar1;
}



// ==== 001db690  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>::reset(QMapData<std::map<QString, double,
   std::less<QString>, std::allocator<std::pair<QString const, double> > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001dbaea  Qt::operator==

/* bool Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned
   int, std::less<QString>, std::allocator<std::pair<QString const, unsigned int> > > >*> const&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*> const&) */

bool Qt::operator==(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  undefined1 uVar1;
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QMapData *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QMapData *)
             totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
             ::get((totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
                    *)param_2);
  uVar1 = std::equal_to<void>::operator()(&local_19,(QMapData **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (bool)uVar1;
}



// ==== 001dbd3e  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*>::reset(QMapData<std::map<QString,
   unsigned int, std::less<QString>, std::allocator<std::pair<QString const, unsigned int> > > >*)
    */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 001e11f0  Qt::operator==

/* Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QDBusPendingCallPrivate*> const&,
   decltype(nullptr)) */

void Qt::operator==(totally_ordered_wrapper *param_1,_func_decltype_nullptr *param_2)

{
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QDBusPendingCallPrivate *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QDBusPendingCallPrivate *)0x0;
  std::equal_to<void>::operator()(&local_19,(QDBusPendingCallPrivate **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001e3ec1  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >*>&)
    */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 001e427d  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QString, double,
   std::less<QString>, std::allocator<std::pair<QString const, double> > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 001e4613  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int,
   std::less<QString>, std::allocator<std::pair<QString const, unsigned int> > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int, std::less<QString>,
   std::allocator<std::pair<QString const, unsigned int> > > >*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 001ef5c0  Qt::totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>::operator*

/* QMapData<std::map<QString, QMap<QString, QVariant>, std::less<QString>,
   std::allocator<std::pair<QString const, QMap<QString, QVariant> > > > >&
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, QMap<QString, QVariant>,
   std::less<QString>, std::allocator<std::pair<QString const, QMap<QString, QVariant> > > >
   >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QString,QMap<QString,QVariant>,std::less<QString>,std::allocator<std::pair<QString_const,QMap<QString,QVariant>>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}



// ==== 001ef8f0  Qt::totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>::operator*

/* QMapData<std::map<QString, double, std::less<QString>, std::allocator<std::pair<QString const,
   double> > > >& Qt::totally_ordered_wrapper<QMapData<std::map<QString, double, std::less<QString>,
   std::allocator<std::pair<QString const, double> > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QString,double,std::less<QString>,std::allocator<std::pair<QString_const,double>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}



// ==== 001efc20  Qt::totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>::operator*

/* QMapData<std::map<QString, unsigned int, std::less<QString>, std::allocator<std::pair<QString
   const, unsigned int> > > >& Qt::totally_ordered_wrapper<QMapData<std::map<QString, unsigned int,
   std::less<QString>, std::allocator<std::pair<QString const, unsigned int> > >
   >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QString,unsigned_int,std::less<QString>,std::allocator<std::pair<QString_const,unsigned_int>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}



// ==== 001f3444  Qt::operator==

/* bool Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QMapData<std::map<QString,
   QVariant, std::less<QString>, std::allocator<std::pair<QString const, QVariant> > > >*> const&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QString, QVariant, std::less<QString>,
   std::allocator<std::pair<QString const, QVariant> > > >*> const&) */

bool Qt::operator==(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  undefined1 uVar1;
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QMapData *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QMapData *)
             totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
             ::get((totally_ordered_wrapper<QMapData<std::map<QString,QVariant,std::less<QString>,std::allocator<std::pair<QString_const,QVariant>>>>*>
                    *)param_2);
  uVar1 = std::equal_to<void>::operator()(&local_19,(QMapData **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (bool)uVar1;
}



// ==== 0020ca98  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>::totally_ordered_wrapper(decltype(nullptr)) */

void Qt::
     totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
     ::totally_ordered_wrapper(_func_decltype_nullptr *param_1)

{
  totally_ordered_wrapper
            ((totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
              *)param_1,(QMapData *)0x0);
  return;
}



// ==== 0020cabc  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::operator->

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>::TEMPNAMEPLACEHOLDERVALUE() const */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
::operator->(totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
             *this)

{
  get(this);
  return;
}



// ==== 0020cad6  Qt::totally_ordered_wrapper::operator.cast.to.bool

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>::operator bool() const */

bool __thiscall Qt::totally_ordered_wrapper::operator_cast_to_bool(totally_ordered_wrapper *this)

{
  long lVar1;
  
  lVar1 = totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
          ::get((totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
                 *)this);
  return lVar1 != 0;
}



// ==== 0020caf6  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::get

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>::get() const */

undefined8 __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
::get(totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
      *this)

{
  return *(undefined8 *)this;
}



// ==== 0020e304  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::totally_ordered_wrapper

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > >
   >*>::totally_ordered_wrapper(QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*) */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
::totally_ordered_wrapper
          (totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
           *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 0020fa10  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::reset

/* Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>::reset(QMapData<std::map<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> >, std::less<QDBusObjectPath>,
   std::allocator<std::pair<QDBusObjectPath const, QMap<QString, QMap<QString, QVariant> > > > > >*)
    */

void __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
::reset(totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
        *this,QMapData *param_1)

{
  *(QMapData **)this = param_1;
  return;
}



// ==== 0021270d  Qt::qt_ptr_swap

/* Qt::qt_ptr_swap(Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath
   const, QMap<QString, QMap<QString, QVariant> > > > > >*>&,
   Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString,
   QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const,
   QMap<QString, QMap<QString, QVariant> > > > > >*>&) */

void Qt::qt_ptr_swap(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  qt_ptr_swap<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>>
            ((QMapData **)param_1,(QMapData **)param_2);
  return;
}



// ==== 00214a0a  Qt::operator==

/* bool Qt::TEMPNAMEPLACEHOLDERVALUE(Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> >, std::less<QDBusObjectPath>,
   std::allocator<std::pair<QDBusObjectPath const, QMap<QString, QMap<QString, QVariant> > > > > >*>
   const&, Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> >, std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath
   const, QMap<QString, QMap<QString, QVariant> > > > > >*> const&) */

bool Qt::operator==(totally_ordered_wrapper *param_1,totally_ordered_wrapper *param_2)

{
  undefined1 uVar1;
  long in_FS_OFFSET;
  equal_to<void> local_19;
  QMapData *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_18 = (QMapData *)
             totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
             ::get((totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
                    *)param_2);
  uVar1 = std::equal_to<void>::operator()(&local_19,(QMapData **)param_1,&local_18);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (bool)uVar1;
}



// ==== 00218592  Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>::operator*

/* QMapData<std::map<QDBusObjectPath, QMap<QString, QMap<QString, QVariant> >,
   std::less<QDBusObjectPath>, std::allocator<std::pair<QDBusObjectPath const, QMap<QString,
   QMap<QString, QVariant> > > > > >& Qt::totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,
   QMap<QString, QMap<QString, QVariant> >, std::less<QDBusObjectPath>,
   std::allocator<std::pair<QDBusObjectPath const, QMap<QString, QMap<QString, QVariant> > > > >
   >*>::TEMPNAMEPLACEHOLDERVALUE() const */

QMapData * __thiscall
Qt::
totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
::operator*(totally_ordered_wrapper<QMapData<std::map<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>,std::less<QDBusObjectPath>,std::allocator<std::pair<QDBusObjectPath_const,QMap<QString,QMap<QString,QVariant>>>>>>*>
            *this)

{
  QMapData *pQVar1;
  
  pQVar1 = (QMapData *)get(this);
  return pQVar1;
}


