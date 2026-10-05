// Ghidra decompile of LaPivot.oracle — class/namespace QImage (6 functions). Raw; not source.

// ==== 00156ee2  QImage::QImage

/* QImage::QImage(QImage&&) */

void __thiscall QImage::QImage(QImage *this,QImage *param_1)

{
  QImageData *pQVar1;
  long in_FS_OFFSET;
  _func_decltype_nullptr *local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QPaintDevice::QPaintDevice((QPaintDevice *)this);
  *(code **)this = QJsonValue::fromVariant;
  local_18 = (_func_decltype_nullptr *)0x0;
  pQVar1 = std::exchange<QImageData*,decltype(nullptr)>((QImageData **)(param_1 + 0x10),&local_18);
  *(QImageData **)(this + 0x10) = pQVar1;
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 00156f5e  QImage::operator=

/* QImage::TEMPNAMEPLACEHOLDERVALUE(QImage&&) */

QImage * __thiscall QImage::operator=(QImage *this,QImage *param_1)

{
  long in_FS_OFFSET;
  QImage local_38 [24];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  QImage(local_38,param_1);
  swap(this,local_38);
  ::QImage::~QImage(local_38);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 00156fda  QImage::swap

/* QImage::swap(QImage&) */

void __thiscall QImage::swap(QImage *this,QImage *param_1)

{
  qt_ptr_swap<QImageData>((QImageData **)(this + 0x10),(QImageData **)(param_1 + 0x10));
  return;
}



// ==== 00157008  QImage::convertToFormat

/* QImage::convertToFormat(QImage::Format, QFlags<Qt::ImageConversionFlag>) const & */

undefined8
QImage::convertToFormat(undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  ::QImage::convertToFormat_helper(param_1,param_2,param_3,param_4);
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0015705e  QImage::scaled

/* QImage::scaled(int, int, Qt::AspectRatioMode, Qt::TransformationMode) const */

undefined8
QImage::scaled(undefined8 param_1,undefined8 param_2,int param_3,int param_4,undefined4 param_5,
              undefined4 param_6)

{
  long in_FS_OFFSET;
  QSize local_18 [8];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  QSize::QSize(local_18,param_3,param_4);
  ::QImage::scaled(param_1,param_2,local_18,param_5,param_6);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 0028a072  QImage::convertToFormat

/* QImage::convertToFormat(QImage::Format, QFlags<Qt::ImageConversionFlag>) && */

QImage * QImage::convertToFormat
                   (QImage *param_1,QImage *param_2,undefined4 param_3,undefined4 param_4)

{
  long lVar1;
  char cVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  cVar2 = ::QImage::convertToFormat_inplace(param_2,param_3,param_4);
  if (cVar2 == '\0') {
    ::QImage::convertToFormat_helper(param_1,param_2,param_3,param_4);
  }
  else {
                    /* try { // try from 0028a0af to 0038a0b3 has its CatchHandler @ 0028b6ed */
                    /* try { // try from 0028a0be to 0038a13d has its CatchHandler @ 0028b6d9 */
    QImage(param_1,param_2);
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}


