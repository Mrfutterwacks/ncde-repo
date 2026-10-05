// Ghidra decompile of LaPivot.oracle — class/namespace QtIterablePrivate (3 functions). Raw; not source.

// ==== 001f6dd4  QtIterablePrivate::retrieveElement<QtMetaContainerPrivate::Sequence::at(long_long)const::{lambda(void*)#1}>

/* QVariant QtIterablePrivate::retrieveElement<QtMetaContainerPrivate::Sequence::at(long long)
   const::{lambda(void*)#1}>(QMetaType, QtMetaContainerPrivate::Sequence::at(long long)
   const::{lambda(void*)#1}) */

QVariant *
QtIterablePrivate::
retrieveElement<QtMetaContainerPrivate::Sequence::at(long_long)const::_lambda(void*)_1_>
          (QVariant *param_1,undefined8 param_2)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined8 local_48;
  QVariant *local_40;
  undefined8 local_30;
  QVariant *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_48 = param_2;
  local_40 = param_1;
  ::QVariant::QVariant(param_1,param_2,0);
  local_30 = QMetaType::fromType<QVariant>();
  cVar1 = ::operator==((QMetaType *)&local_48,(QMetaType *)&local_30);
  if (cVar1 == '\0') {
    local_28 = (QVariant *)::QVariant::data();
  }
  else {
    local_28 = local_40;
  }
  const::{lambda(void*)#1}::operator()((_lambda_void___1_ *)&stack0x00000008,local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}



// ==== 001f736c  QtIterablePrivate::retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialIterator>(QtMetaContainerPrivate::SequentialIterator_const&)::{lambda(void*)#1}>

/* QVariant
   QtIterablePrivate::retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialIterator>(QtMetaContainerPrivate::SequentialIterator
   const&)::{lambda(void*)#1}>(QMetaType,
   QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialIterator>(QtMetaContainerPrivate::SequentialIterator
   const&)::{lambda(void*)#1}) */

QVariant *
QtIterablePrivate::
retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialIterator>(QtMetaContainerPrivate::SequentialIterator_const&)::_lambda(void*)_1_>
          (QVariant *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  QVariant *local_40;
  undefined8 local_30;
  QVariant *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_58 = param_3;
  local_50 = param_4;
  local_48 = param_2;
  local_40 = param_1;
  ::QVariant::QVariant(param_1,param_2,0);
  local_30 = QMetaType::fromType<QVariant>();
  cVar1 = ::operator==((QMetaType *)&local_48,(QMetaType *)&local_30);
  if (cVar1 == '\0') {
    local_28 = (QVariant *)::QVariant::data();
  }
  else {
    local_28 = local_40;
  }
  QtPrivate::
  sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialIterator>(QtMetaContainerPrivate::SequentialIterator_const&)
  ::{lambda(void*)#1}::operator()((_lambda_void___1_ *)&local_58,local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}



// ==== 001f7447  QtIterablePrivate::retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialConstIterator>(QtMetaContainerPrivate::SequentialConstIterator_const&)::{lambda(void*)#1}>

/* QVariant
   QtIterablePrivate::retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialConstIterator>(QtMetaContainerPrivate::SequentialConstIterator
   const&)::{lambda(void*)#1}>(QMetaType,
   QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialConstIterator>(QtMetaContainerPrivate::SequentialConstIterator
   const&)::{lambda(void*)#1}) */

QVariant *
QtIterablePrivate::
retrieveElement<QtPrivate::sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialConstIterator>(QtMetaContainerPrivate::SequentialConstIterator_const&)::_lambda(void*)_1_>
          (QVariant *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  long in_FS_OFFSET;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  QVariant *local_40;
  undefined8 local_30;
  QVariant *local_28;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_58 = param_3;
  local_50 = param_4;
  local_48 = param_2;
  local_40 = param_1;
  ::QVariant::QVariant(param_1,param_2,0);
  local_30 = QMetaType::fromType<QVariant>();
  cVar1 = ::operator==((QMetaType *)&local_48,(QMetaType *)&local_30);
  if (cVar1 == '\0') {
    local_28 = (QVariant *)::QVariant::data();
  }
  else {
    local_28 = local_40;
  }
  QtPrivate::
  sequentialIteratorToVariant<QtMetaContainerPrivate::SequentialConstIterator>(QtMetaContainerPrivate::SequentialConstIterator_const&)
  ::{lambda(void*)#1}::operator()((_lambda_void___1_ *)&local_58,local_28);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_40;
}


