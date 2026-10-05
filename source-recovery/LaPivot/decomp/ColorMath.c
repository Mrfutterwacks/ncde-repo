// Ghidra decompile of LaPivot.oracle — class/namespace ColorMath (1 functions). Raw; not source.

// ==== 001642b5  ColorMath::poeticName

/* ColorMath::poeticName(double, double) */

ColorMath * __thiscall ColorMath::poeticName(ColorMath *this,double param_1,double param_2)

{
  char cVar1;
  int iVar2;
  double *pdVar3;
  pair<int,QString> *this_00;
  undefined **ppuVar4;
  QString *this_01;
  long lVar5;
  long in_FS_OFFSET;
  double dVar6;
  QString *local_2c8;
  int local_294 [11];
  undefined8 local_268;
  undefined8 local_260;
  double local_258;
  undefined1 *local_250;
  undefined1 *local_248;
  int *local_240;
  int *local_238;
  double local_230;
  double local_228 [4];
  double local_208 [4];
  pair<int,QString> local_1e8 [32];
  pair<int,QString> local_1c8 [32];
  pair<int,QString> apStack_1a8 [32];
  pair<int,QString> apStack_188 [24];
  QString aQStack_170 [8];
  pair<int,QString> apStack_168 [32];
  pair<int,QString> apStack_148 [32];
  pair<int,QString> apStack_128 [32];
  pair<int,QString> apStack_108 [32];
  pair<int,QString> apStack_e8 [32];
  pair<int,QString> apStack_c8 [32];
  pair<int,QString> apStack_a8 [32];
  pair<int,QString> apStack_88 [32];
  pair<int,QString> local_68 [32];
  pair<int,QString> apStack_48 [8];
  long local_40;
  
  local_40 = *(long *)(in_FS_OFFSET + 0x28);
  if (poeticName(double,double)::POETIC == '\0') {
    iVar2 = __cxa_guard_acquire(&poeticName(double,double)::POETIC);
    if (iVar2 != 0) {
      local_294[0] = 0;
      std::pair<int,QString>::pair<int,char_const(&)[7],true>(local_1e8,local_294,"Garnet");
      local_294[1] = 0x1e;
      std::pair<int,QString>::pair<int,char_const(&)[6],true>(local_1c8,local_294 + 1,"Amber");
      local_294[2] = 0x2d;
      std::pair<int,QString>::pair<int,char_const(&)[5],true>(apStack_1a8,local_294 + 2,"Gilt");
      local_294[3] = 0x3c;
      std::pair<int,QString>::pair<int,char_const(&)[8],true>(apStack_188,local_294 + 3,"Saffron");
      local_294[4] = 0x5a;
      std::pair<int,QString>::pair<int,char_const(&)[9],true>(apStack_168,local_294 + 4,"Absinthe");
      local_294[5] = 0x78;
      std::pair<int,QString>::pair<int,char_const(&)[10],true>
                (apStack_148,local_294 + 5,"Verdigris");
      local_294[6] = 0xa0;
      std::pair<int,QString>::pair<int,char_const(&)[11],true>
                (apStack_128,local_294 + 6,"Eau-de-Nil");
      local_294[7] = 0xb4;
      std::pair<int,QString>::pair<int,char_const(&)[9],true>(apStack_108,local_294 + 7,"Cerulean");
      local_294[8] = 0xd2;
      std::pair<int,QString>::pair<int,char_const(&)[11],true>
                (apStack_e8,local_294 + 8,"Cyan Salon");
      local_268 = CONCAT44(local_268._4_4_,0xf0);
      std::pair<int,QString>::pair<int,char_const(&)[6],true>(apStack_c8,(int *)&local_268,"Lapis");
      local_260 = CONCAT44(local_260._4_4_,0x10e);
      std::pair<int,QString>::pair<int,char_const(&)[5],true>(apStack_a8,(int *)&local_260,"Iris");
      local_228[0] = (double)CONCAT44(local_228[0]._4_4_,300);
      std::pair<int,QString>::pair<int,char_const(&)[5],true>(apStack_88,(int *)local_228,"Plum");
      local_208[0] = (double)CONCAT44(local_208[0]._4_4_,0x14a);
      std::pair<int,QString>::pair<int,char_const(&)[5],true>(local_68,(int *)local_208,"Rose");
      QList<std::pair<int,QString>>::QList(poeticName(double,double)::POETIC,local_1e8,0xd);
      __cxa_atexit(QList<std::pair<int,QString>>::~QList,poeticName(double,double)::POETIC,
                   &__dso_handle);
      __cxa_guard_release(&poeticName(double,double)::POETIC);
      this_00 = apStack_48;
      while (this_00 != local_1e8) {
        this_00 = this_00 + -0x20;
        std::pair<int,QString>::~pair(this_00);
      }
    }
  }
  if (poeticName(double,double)::MOODS == '\0') {
    iVar2 = __cxa_guard_acquire(&poeticName(double,double)::MOODS);
    if (iVar2 != 0) {
      local_2c8 = (QString *)local_1e8;
      ppuVar4 = &C_1125_2;
      for (lVar5 = 4; -1 < lVar5; lVar5 = lVar5 + -1) {
        QString::QString(local_2c8,*ppuVar4);
        local_2c8 = local_2c8 + 0x18;
        ppuVar4 = ppuVar4 + 1;
      }
      QList<QString>::QList(poeticName(double,double)::MOODS,local_1e8,5);
      __cxa_atexit(QList<QString>::~QList,poeticName(double,double)::MOODS,&__dso_handle);
      __cxa_guard_release(&poeticName(double,double)::MOODS);
      this_01 = aQStack_170;
      while (this_01 != (QString *)local_1e8) {
        this_01 = this_01 + -0x18;
        QString::~QString(this_01);
      }
    }
  }
  local_294[9] = 0;
  local_258 = 999.0;
  local_250 = poeticName(double,double)::POETIC;
  local_268 = QList<std::pair<int,QString>>::begin
                        ((QList<std::pair<int,QString>> *)poeticName(double,double)::POETIC);
  local_260 = QList<std::pair<int,QString>>::end
                        ((QList<std::pair<int,QString>> *)poeticName(double,double)::POETIC);
  while( true ) {
    cVar1 = QList<std::pair<int,QString>>::const_iterator::operator!=
                      ((const_iterator *)&local_268,local_260);
    if (cVar1 == '\0') break;
    local_238 = (int *)QList<std::pair<int,QString>>::const_iterator::operator*
                                 ((const_iterator *)&local_268);
    local_228[0] = (double)std::abs(param_1 - (double)*local_238);
    local_208[0] = 360.0 - local_228[0];
    pdVar3 = qMin<double>(local_228,local_208);
    local_230 = *pdVar3;
    if (local_230 < local_258) {
      local_294[9] = *local_238;
      local_258 = local_230;
    }
    QList<std::pair<int,QString>>::const_iterator::operator++((const_iterator *)&local_268);
  }
  local_228[0] = 0.0;
  local_228[1] = 0.0;
  local_228[2] = 0.0;
  local_248 = poeticName(double,double)::POETIC;
  local_260 = QList<std::pair<int,QString>>::begin
                        ((QList<std::pair<int,QString>> *)poeticName(double,double)::POETIC);
  local_208[0] = (double)QList<std::pair<int,QString>>::end
                                   ((QList<std::pair<int,QString>> *)
                                    poeticName(double,double)::POETIC);
  do {
    cVar1 = QList<std::pair<int,QString>>::const_iterator::operator!=
                      ((const_iterator *)&local_260,local_208[0]);
    if (cVar1 == '\0') {
LAB_0016490f:
      lVar5 = QList<QString>::size((QList<QString> *)poeticName(double,double)::MOODS);
      dVar6 = floor((double)lVar5 * param_2);
      lVar5 = QList<QString>::size((QList<QString> *)poeticName(double,double)::MOODS);
      local_294[10] = (int)((long)(int)dVar6 % lVar5);
      QList<QString>::operator[]
                ((QList<QString> *)poeticName(double,double)::MOODS,(long)local_294[10]);
      ::operator+((QString *)local_208,(char *)local_228);
      ::operator+((QString *)this,(QString *)local_208);
      QString::~QString((QString *)local_208);
      QString::~QString((QString *)local_228);
      if (local_40 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
        __stack_chk_fail();
      }
      return this;
    }
    local_240 = (int *)QList<std::pair<int,QString>>::const_iterator::operator*
                                 ((const_iterator *)&local_260);
    if (local_294[9] == *local_240) {
      QString::operator=((QString *)local_228,(QString *)(local_240 + 2));
      goto LAB_0016490f;
    }
    QList<std::pair<int,QString>>::const_iterator::operator++((const_iterator *)&local_260);
  } while( true );
}


