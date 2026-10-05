// Ghidra decompile of LaPivot.oracle — class/namespace QModelIndex (2 functions). Raw; not source.

// ==== 00176eea  QModelIndex::QModelIndex

/* QModelIndex::QModelIndex() */

void __thiscall QModelIndex::QModelIndex(QModelIndex *this)

{
  *(undefined4 *)this = 0xffffffff;
  *(undefined4 *)(this + 4) = 0xffffffff;
  *(undefined8 *)(this + 8) = 0;
  Qt::totally_ordered_wrapper<QAbstractItemModel_const*>::totally_ordered_wrapper
            ((_func_decltype_nullptr *)(this + 0x10));
  return;
}



// ==== 00176f30  QModelIndex::row

/* QModelIndex::row() const */

undefined4 __thiscall QModelIndex::row(QModelIndex *this)

{
  return *(undefined4 *)this;
}


