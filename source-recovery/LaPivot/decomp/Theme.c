// Ghidra decompile of LaPivot.oracle — class/namespace Theme (26 functions). Raw; not source.

// ==== 0014ded0  Theme::qt_static_metacall

/* Theme::qt_static_metacall(QObject*, QMetaObject::Call, int, void**) */

void Theme::qt_static_metacall(Theme *param_1,int param_2,int param_3,QtMocHelpers *param_4)

{
  QString *this;
  bool bVar1;
  QString QVar2;
  undefined4 uVar3;
  long in_FS_OFFSET;
  undefined8 uVar4;
  undefined8 local_38 [3];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (param_2 == 0) {
    if (param_3 == 0) {
      changed(param_1);
    }
    else if ((param_3 == 1) &&
            (local_38[0] = scale(param_1,**(double **)(param_4 + 8)), *(long *)param_4 != 0)) {
      **(undefined8 **)param_4 = local_38[0];
    }
  }
  if (((param_2 != 5) ||
      (bVar1 = QtMocHelpers::indexOfMethod<void(Theme::*)()>
                         (param_4,(void **)changed,(_func_void *)0x0,0), !bVar1)) && (param_2 == 1))
  {
    this = *(QString **)param_4;
    if (param_3 == 0xd) {
      uVar4 = textShadowOffsetY(param_1);
      *(undefined8 *)this = uVar4;
    }
    else if (param_3 < 0xe) {
      if (param_3 == 0xc) {
        uVar4 = textShadowOffsetX(param_1);
        *(undefined8 *)this = uVar4;
      }
      else if (param_3 < 0xd) {
        if (param_3 == 0xb) {
          uVar4 = textShadowRadius(param_1);
          *(undefined8 *)this = uVar4;
        }
        else if (param_3 < 0xc) {
          if (param_3 == 10) {
            QVar2 = (QString)textShadowEnabled(param_1);
            *this = QVar2;
          }
          else if (param_3 < 0xb) {
            if (param_3 == 9) {
              textShadowColor();
              QString::operator=(this,(QString *)local_38);
              QString::~QString((QString *)local_38);
            }
            else if (param_3 < 10) {
              if (param_3 == 8) {
                textStyleColor((Theme *)local_38);
                QString::operator=(this,(QString *)local_38);
                QString::~QString((QString *)local_38);
              }
              else if (param_3 < 9) {
                if (param_3 == 7) {
                  uVar3 = textStyle(param_1);
                  *(undefined4 *)this = uVar3;
                }
                else if (param_3 < 8) {
                  if (param_3 == 6) {
                    textColor();
                    QString::operator=(this,(QString *)local_38);
                    QString::~QString((QString *)local_38);
                  }
                  else if (param_3 < 7) {
                    if (param_3 == 5) {
                      uVar3 = fontLarge(param_1);
                      *(undefined4 *)this = uVar3;
                    }
                    else if (param_3 < 6) {
                      if (param_3 == 4) {
                        uVar3 = fontMedium(param_1);
                        *(undefined4 *)this = uVar3;
                      }
                      else if (param_3 < 5) {
                        if (param_3 == 3) {
                          uVar3 = fontSmall(param_1);
                          *(undefined4 *)this = uVar3;
                        }
                        else if (param_3 < 4) {
                          if (param_3 == 2) {
                            uVar4 = letterSpacing(param_1);
                            *(undefined8 *)this = uVar4;
                          }
                          else if (param_3 < 3) {
                            if (param_3 == 0) {
                              fontFamily();
                              QString::operator=(this,(QString *)local_38);
                              QString::~QString((QString *)local_38);
                            }
                            else if (param_3 == 1) {
                              titleFont();
                              QString::operator=(this,(QString *)local_38);
                              QString::~QString((QString *)local_38);
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014e2c0  Theme::metaObject

/* Theme::metaObject() const */

undefined1 * __thiscall Theme::metaObject(Theme *this)

{
  long lVar1;
  undefined1 *puVar2;
  
  lVar1 = QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>>::operator->
                    ((QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>> *)(this + 8));
  if (*(long *)(lVar1 + 0x38) == 0) {
    puVar2 = staticMetaObject;
  }
  else {
    QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>>::operator->
              ((QScopedPointer<QObjectData,QScopedPointerDeleter<QObjectData>> *)(this + 8));
    puVar2 = (undefined1 *)QObjectData::dynamicMetaObject();
  }
  return puVar2;
}



// ==== 0014e308  Theme::qt_metacast

/* Theme::qt_metacast(char const*) */

Theme * __thiscall Theme::qt_metacast(Theme *this,char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    this = (Theme *)0x0;
  }
  else {
    iVar1 = strcmp(param_1,"Theme");
    if (iVar1 != 0) {
      this = (Theme *)QObject::qt_metacast((char *)this);
    }
  }
  return this;
}



// ==== 0014e35c  Theme::qt_metacall

/* Theme::qt_metacall(QMetaObject::Call, int, void**) */

int __thiscall Theme::qt_metacall(Theme *this,int param_2,undefined4 param_3,undefined8 *param_4)

{
  long in_FS_OFFSET;
  int local_28;
  undefined8 local_18;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_28 = QObject::qt_metacall(this,param_2,param_3,param_4);
  if (-1 < local_28) {
    if (param_2 == 0) {
      if (local_28 < 2) {
        qt_static_metacall(this,0,local_28,param_4);
      }
      local_28 = local_28 + -2;
    }
    if (param_2 == 7) {
      if (local_28 < 2) {
        local_18 = 0;
        QMetaType::QMetaType((QMetaType *)&local_18);
        *(undefined8 *)*param_4 = local_18;
      }
      local_28 = local_28 + -2;
    }
    if ((((param_2 == 1) || (param_2 == 2)) || (param_2 == 3)) || ((param_2 == 8 || (param_2 == 6)))
       ) {
      qt_static_metacall(this,param_2,local_28,param_4);
      local_28 = local_28 + -0xe;
    }
  }
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return local_28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 0014e452  Theme::changed

/* Theme::changed() */

void __thiscall Theme::changed(Theme *this)

{
  QMetaObject::activate((QObject *)this,(QMetaObject *)staticMetaObject,0,(void **)0x0);
  return;
}



// ==== 001a0d5a  Theme::Theme

/* Theme::Theme(QObject*) */

void __thiscall Theme::Theme(Theme *this,QObject *param_1)

{
  QObject::QObject((QObject *)this,param_1);
  *(undefined ***)this = &PTR_metaObject_0032bbd0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  return;
}



// ==== 001a0da6  Theme::fontFamily

/* Theme::fontFamily() const */

QString * Theme::fontFamily(void)

{
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString(in_RDI);
  }
  else {
    QObject::property((char *)local_48);
    ::QVariant::toString();
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return in_RDI;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a0e88  Theme::titleFont

/* Theme::titleFont() const */

QString * Theme::titleFont(void)

{
  char cVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  QArrayDataPointer<char16_t> local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_68,(QTypedArrayData *)0x0,L"Cinzel",6);
    QString::QString(in_RDI,(QArrayDataPointer *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_68);
  }
  else {
    QObject::property((char *)local_48);
    ::QVariant::toString();
    ::QVariant::~QVariant(local_48);
    cVar1 = QString::isEmpty((QString *)local_68);
    if (cVar1 == '\0') {
      QString::QString(in_RDI,(QString *)local_68);
    }
    else {
      fontFamily();
    }
    QString::~QString((QString *)local_68);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return in_RDI;
}



// ==== 001a0ffe  Theme::letterSpacing

/* Theme::letterSpacing() const */

undefined8 __thiscall Theme::letterSpacing(Theme *this)

{
  long in_FS_OFFSET;
  undefined8 uVar1;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    QObject::property((char *)local_48);
    uVar1 = ::QVariant::toReal((bool *)local_48);
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a10da  Theme::fontSmall

/* Theme::fontSmall() const */

void __thiscall Theme::fontSmall(Theme *this)

{
  scaled(this,0xb);
  return;
}



// ==== 001a10fa  Theme::fontMedium

/* Theme::fontMedium() const */

void __thiscall Theme::fontMedium(Theme *this)

{
  scaled(this,0xe);
  return;
}



// ==== 001a111a  Theme::fontLarge

/* Theme::fontLarge() const */

void __thiscall Theme::fontLarge(Theme *this)

{
  scaled(this,0x14);
  return;
}



// ==== 001a113a  Theme::textColor

/* Theme::textColor() const */

QString * Theme::textColor(void)

{
  char cVar1;
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  QString local_88 [32];
  QArrayDataPointer<char16_t> local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString(local_88);
  }
  else {
    QObject::property((char *)local_48);
    ::QVariant::toString();
    ::QVariant::~QVariant(local_48);
  }
  cVar1 = QString::isEmpty(local_88);
  if (cVar1 == '\0') {
    QString::QString(in_RDI,local_88);
  }
  else {
    QArrayDataPointer<char16_t>::QArrayDataPointer(local_68,(QTypedArrayData *)0x0,L"#f4e9d2",7);
    QString::QString(in_RDI,(QArrayDataPointer *)local_68);
    QArrayDataPointer<char16_t>::~QArrayDataPointer(local_68);
  }
  QString::~QString(local_88);
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return in_RDI;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a12c0  Theme::textStyle

/* Theme::textStyle() const */

undefined8 __thiscall Theme::textStyle(Theme *this)

{
  char cVar1;
  undefined8 uVar2;
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) == 0) {
    uVar2 = 0;
  }
  else {
    QObject::property((char *)local_48);
    cVar1 = ::QVariant::toBool();
    ::QVariant::~QVariant(local_48);
    if (cVar1 == '\0') {
      QObject::property((char *)local_48);
      cVar1 = ::QVariant::toBool();
      ::QVariant::~QVariant(local_48);
      if (cVar1 == '\0') {
        uVar2 = 0;
      }
      else {
        uVar2 = 2;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar2;
}



// ==== 001a13fc  Theme::textStyleColor

/* Theme::textStyleColor() const */

Theme * __thiscall Theme::textStyleColor(Theme *this)

{
  long lVar1;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  textShadowColor();
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return this;
}



// ==== 001a1448  Theme::textShadowColor

/* Theme::textShadowColor() const */

QString * Theme::textShadowColor(void)

{
  long in_RSI;
  QString *in_RDI;
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(in_RSI + 0x10) == 0) {
    QString::QString(in_RDI);
  }
  else {
    QObject::property((char *)local_48);
    ::QVariant::toString();
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return in_RDI;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a152a  Theme::textShadowEnabled

/* Theme::textShadowEnabled() const */

undefined8 __thiscall Theme::textShadowEnabled(Theme *this)

{
  bool bVar1;
  char cVar2;
  undefined8 uVar3;
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  bVar1 = false;
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_48);
    bVar1 = true;
    cVar2 = ::QVariant::toBool();
    if (cVar2 != '\0') {
      uVar3 = 1;
      goto LAB_001a159e;
    }
  }
  uVar3 = 0;
LAB_001a159e:
  if (bVar1) {
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar3;
}



// ==== 001a1602  Theme::textShadowRadius

/* Theme::textShadowRadius() const */

void __thiscall Theme::textShadowRadius(Theme *this)

{
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_48);
    ::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a1704  Theme::textShadowOffsetX

/* Theme::textShadowOffsetX() const */

void __thiscall Theme::textShadowOffsetX(Theme *this)

{
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_48);
    ::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a1806  Theme::textShadowOffsetY

/* Theme::textShadowOffsetY() const */

void __thiscall Theme::textShadowOffsetY(Theme *this)

{
  long in_FS_OFFSET;
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_48);
    ::QVariant::toDouble((bool *)local_48);
    ::QVariant::~QVariant(local_48);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001a1908  Theme::scale

/* Theme::scale(double) const */

void __thiscall Theme::scale(Theme *this,double param_1)

{
  long in_FS_OFFSET;
  double dVar1;
  double dVar2;
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_68);
    dVar1 = (double)::QVariant::toDouble((bool *)local_68);
    QObject::property((char *)local_48);
    dVar2 = (double)::QVariant::toDouble((bool *)local_48);
    dVar2 = dVar2 * dVar1;
    ::QVariant::~QVariant(local_48);
    ::QVariant::~QVariant(local_68);
    if (dVar2 <= 0.0) {
      dVar2 = 1.0;
    }
    param_1 = dVar2 * param_1;
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_1);
}



// ==== 001a1a52  Theme::scaled

/* Theme::scaled(int) const */

int __thiscall Theme::scaled(Theme *this,int param_1)

{
  long in_FS_OFFSET;
  double dVar1;
  double dVar2;
  QVariant local_68 [32];
  QVariant local_48 [40];
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (*(long *)(this + 0x10) != 0) {
    QObject::property((char *)local_68);
    dVar1 = (double)::QVariant::toDouble((bool *)local_68);
    QObject::property((char *)local_48);
    dVar2 = (double)::QVariant::toDouble((bool *)local_48);
    dVar2 = dVar2 * dVar1;
    ::QVariant::~QVariant(local_48);
    ::QVariant::~QVariant(local_68);
    if (dVar2 <= 0.0) {
      dVar2 = 1.0;
    }
    param_1 = (int)(dVar2 * (double)param_1);
  }
  if (local_20 == *(long *)(in_FS_OFFSET + 0x28)) {
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}



// ==== 001a1c7c  Theme::~Theme

/* Theme::~Theme() */

void __thiscall Theme::~Theme(Theme *this)

{
  *(undefined ***)this = &PTR_metaObject_0032bbd0;
  QObject::~QObject((QObject *)this);
  return;
}



// ==== 001a1ca6  Theme::~Theme

/* Theme::~Theme() */

void __thiscall Theme::~Theme(Theme *this)

{
  ~Theme(this);
  operator_delete(this,0x20);
  return;
}



// ==== 001f8f6c  Theme::setSettings

/* Theme::setSettings(Settings*) */

void __thiscall Theme::setSettings(Theme *this,Settings *param_1)

{
  long in_FS_OFFSET;
  Connection local_40 [8];
  code *local_38;
  undefined8 local_30;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  *(Settings **)(this + 0x10) = param_1;
  if (param_1 != (Settings *)0x0) {
    local_38 = changed;
    local_30 = 0;
    QObject::connect<void(Settings::*)(),void(Theme::*)()>
              (local_40,param_1,Settings::fontChanged,0,this,&local_38,0);
    QMetaObject::Connection::~Connection(local_40);
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}



// ==== 001f9018  Theme::setEngine

/* Theme::setEngine(QObject*) */

void __thiscall Theme::setEngine(Theme *this,QObject *param_1)

{
  long in_FS_OFFSET;
  Connection local_18 [8];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  *(QObject **)(this + 0x18) = param_1;
  if (param_1 != (QObject *)0x0) {
    QObject::connect(local_18,param_1,"2themeChanged()",this,"2changed()",0);
    QMetaObject::Connection::~Connection(local_18);
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


