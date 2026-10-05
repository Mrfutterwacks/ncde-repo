// Ghidra decompile of LaPivot.oracle — class/namespace QMetaAssociation (5 functions). Raw; not source.

// ==== 0015323c  QMetaAssociation::QMetaAssociation

/* QMetaAssociation::QMetaAssociation(QtMetaContainerPrivate::QMetaAssociationInterface const*) */

void __thiscall
QMetaAssociation::QMetaAssociation(QMetaAssociation *this,QMetaAssociationInterface *param_1)

{
  QMetaContainer::QMetaContainer((QMetaContainer *)this,(QMetaContainerInterface *)param_1);
  return;
}



// ==== 001d8726  QMetaAssociation::fromContainer<QMap<QString,QMap<QString,QVariant>>>

/* QMetaAssociation QMetaAssociation::fromContainer<QMap<QString, QMap<QString, QVariant> > >() */

undefined8 QMetaAssociation::fromContainer<QMap<QString,QMap<QString,QVariant>>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaAssociation((QMetaAssociation *)&local_18,
                   (QMetaAssociationInterface *)
                   MetaAssociation<QMap<QString,QMap<QString,QVariant>>>::value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 001d9720  QMetaAssociation::fromContainer<QMap<QString,double>>

/* QMetaAssociation QMetaAssociation::fromContainer<QMap<QString, double> >() */

undefined8 QMetaAssociation::fromContainer<QMap<QString,double>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaAssociation((QMetaAssociation *)&local_18,
                   (QMetaAssociationInterface *)MetaAssociation<QMap<QString,double>>::value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 001da6f8  QMetaAssociation::fromContainer<QMap<QString,unsigned_int>>

/* QMetaAssociation QMetaAssociation::fromContainer<QMap<QString, unsigned int> >() */

undefined8 QMetaAssociation::fromContainer<QMap<QString,unsigned_int>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaAssociation((QMetaAssociation *)&local_18,
                   (QMetaAssociationInterface *)MetaAssociation<QMap<QString,unsigned_int>>::value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}



// ==== 00212170  QMetaAssociation::fromContainer<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>

/* QMetaAssociation QMetaAssociation::fromContainer<QMap<QDBusObjectPath, QMap<QString,
   QMap<QString, QVariant> > > >() */

undefined8
QMetaAssociation::fromContainer<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>(void)

{
  long in_FS_OFFSET;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QMetaAssociation((QMetaAssociation *)&local_18,
                   (QMetaAssociationInterface *)
                   MetaAssociation<QMap<QDBusObjectPath,QMap<QString,QMap<QString,QVariant>>>>::
                   value);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return local_18;
}


