// Ghidra decompile of LaPivot.oracle — class/namespace IconProvider (4 functions). Raw; not source.

// ==== 001f84ea  IconProvider::IconProvider

/* IconProvider::IconProvider() */

void __thiscall IconProvider::IconProvider(IconProvider *this)

{
  long in_FS_OFFSET;
  undefined4 local_24;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  local_24 = 0;
  QFlags<QQmlImageProviderBase::Flag>::QFlags((QFlags<QQmlImageProviderBase::Flag> *)&local_24);
  QQuickImageProvider::QQuickImageProvider((QQuickImageProvider *)this,2,local_24);
  *(undefined ***)this = &PTR_metaObject_0032c888;
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f8558  IconProvider::requestPixmap

/* IconProvider::requestPixmap(QString const&, QSize*, QSize const&) */

QString * IconProvider::requestPixmap(QString *param_1,QSize *param_2,QSize *param_3)

{
  char cVar1;
  int iVar2;
  undefined8 *in_RCX;
  QSize *in_R8;
  long in_FS_OFFSET;
  undefined2 local_56;
  undefined4 local_54;
  QString local_50 [8];
  QString local_48 [8];
  undefined8 local_40;
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  cVar1 = QSize::isValid(in_R8);
  if (cVar1 != '\0') {
    iVar2 = QSize::width(in_R8);
    if (0 < iVar2) {
      local_40 = *(undefined8 *)in_R8;
      goto LAB_001f85c7;
    }
  }
  QSize::QSize((QSize *)&local_40,0x40,0x40);
LAB_001f85c7:
  QIcon::fromTheme(local_50);
  cVar1 = QIcon::isNull();
  if (cVar1 != '\0') {
    QFlags<QString::SectionFlag>::QFlags((QFlags<QString::SectionFlag> *)&local_54,0);
    QChar::QChar<char,true>((QChar *)&local_56,'.');
    QString::section(local_38,param_3,local_56,0xffffffffffffffff,0xffffffffffffffff,local_54);
    QIcon::fromTheme(local_48);
    QIcon::operator=((QIcon *)local_50,(QIcon *)local_48);
    QIcon::~QIcon((QIcon *)local_48);
    QString::~QString((QString *)local_38);
  }
  cVar1 = QIcon::isNull();
  if (cVar1 == '\0') {
    QIcon::pixmap(param_1,local_50,&local_40,0,1);
  }
  else {
    QPixmap::QPixmap((QPixmap *)param_1);
  }
  if (in_RCX != (undefined8 *)0x0) {
    cVar1 = QPixmap::isNull();
    if (cVar1 == '\0') {
      local_38[0] = QPixmap::size();
    }
    else {
      local_38[0] = local_40;
    }
    *in_RCX = local_38[0];
  }
  QIcon::~QIcon((QIcon *)local_50);
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return param_1;
}



// ==== 002041c4  IconProvider::~IconProvider

/* IconProvider::~IconProvider() */

void __thiscall IconProvider::~IconProvider(IconProvider *this)

{
  *(undefined ***)this = &PTR_metaObject_0032c888;
  QQuickImageProvider::~QQuickImageProvider((QQuickImageProvider *)this);
  return;
}



// ==== 002041ee  IconProvider::~IconProvider

/* IconProvider::~IconProvider() */

void __thiscall IconProvider::~IconProvider(IconProvider *this)

{
  ~IconProvider(this);
  operator_delete(this,0x18);
  return;
}


