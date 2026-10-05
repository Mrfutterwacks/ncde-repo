// Ghidra decompile of LaPivot.oracle — class/namespace QMetaSequence (3 functions). Raw; not source.

// ==== 00208da6  QMetaSequence::QMetaSequence

/* QMetaSequence::QMetaSequence(QtMetaContainerPrivate::QMetaSequenceInterface const*) */

void __thiscall QMetaSequence::QMetaSequence(QMetaSequence *this,QMetaSequenceInterface *param_1)

{
  QMetaContainer::QMetaContainer((QMetaContainer *)this,(QMetaContainerInterface *)param_1);
  return;
}



// ==== 00211097  QMetaSequence::fromContainer<QList<unsigned_int>>

/* QMetaSequence QMetaSequence::fromContainer<QList<unsigned int> >() */

undefined8 QMetaSequence::fromContainer<QList<unsigned_int>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaSequence((QMetaSequence *)&local_18,
                (QMetaSequenceInterface *)MetaSequence<QList<unsigned_int>>::value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 002321e9  QMetaSequence::fromContainer<QList<QDBusObjectPath>>

/* QMetaSequence QMetaSequence::fromContainer<QList<QDBusObjectPath> >() */

undefined8 QMetaSequence::fromContainer<QList<QDBusObjectPath>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaSequence((QMetaSequence *)&local_18,
                (QMetaSequenceInterface *)MetaSequence<QList<QDBusObjectPath>>::value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}


