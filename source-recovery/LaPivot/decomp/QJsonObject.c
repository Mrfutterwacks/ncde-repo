// Ghidra decompile of LaPivot.oracle — class/namespace QJsonObject (2 functions). Raw; not source.

// ==== 0015e6a4  QJsonObject::operator=

/* QJsonObject::TEMPNAMEPLACEHOLDERVALUE(QJsonObject&&) */

QJsonObject * __thiscall QJsonObject::operator=(QJsonObject *this,QJsonObject *param_1)

{
  swap(this,param_1);
  return this;
}



// ==== 0015e6ce  QJsonObject::swap

/* QJsonObject::swap(QJsonObject&) */

void __thiscall QJsonObject::swap(QJsonObject *this,QJsonObject *param_1)

{
  QSharedDataPointerBase<QExplicitlySharedDataPointer,QCborContainerPrivate>::swap
            ((QSharedDataPointerBase<QExplicitlySharedDataPointer,QCborContainerPrivate> *)this,
             (QExplicitlySharedDataPointer *)param_1);
  return;
}


