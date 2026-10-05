// Ghidra decompile of LaPivot.oracle — class/namespace QGuiApplication (1 functions). Raw; not source.

// ==== 001a7b78  QGuiApplication::nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>

/* QNativeInterface::QX11Application*
   QGuiApplication::nativeInterface<QNativeInterface::QX11Application,
   QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>, QGuiApplication,
   true>() const */

QX11Application * __thiscall
QGuiApplication::
nativeInterface<QNativeInterface::QX11Application,QNativeInterface::Private::NativeInterface<QNativeInterface::QX11Application>,QGuiApplication,true>
          (QGuiApplication *this)

{
  int iVar1;
  QX11Application *pQVar2;
  
  QNativeInterface::Private::TypeInfo<QNativeInterface::QX11Application>::revision();
  iVar1 = QNativeInterface::Private::TypeInfo<QNativeInterface::QX11Application>::name();
  pQVar2 = (QX11Application *)QGuiApplication::resolveInterface((char *)this,iVar1);
  return pQVar2;
}


