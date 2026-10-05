// Ghidra decompile of LaPivot.oracle — class/namespace QDBusObjectPath (8 functions). Raw; not source.

// ==== 00157284  QDBusObjectPath::QDBusObjectPath

/* QDBusObjectPath::QDBusObjectPath() */

void __thiscall QDBusObjectPath::QDBusObjectPath(QDBusObjectPath *this)

{
  QString::QString((QString *)this);
  return;
}



// ==== 001572a0  QDBusObjectPath::path

/* QDBusObjectPath::path() const */

QString * QDBusObjectPath::path(void)

{
  QString *in_RSI;
  QString *in_RDI;
  
  QString::QString(in_RDI,in_RSI);
  return in_RDI;
}



// ==== 001633ca  QDBusObjectPath::QDBusObjectPath

/* QDBusObjectPath::QDBusObjectPath(QDBusObjectPath const&) */

void __thiscall QDBusObjectPath::QDBusObjectPath(QDBusObjectPath *this,QDBusObjectPath *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  return;
}



// ==== 00163484  QDBusObjectPath::QDBusObjectPath

/* QDBusObjectPath::QDBusObjectPath(QDBusObjectPath&&) */

void __thiscall QDBusObjectPath::QDBusObjectPath(QDBusObjectPath *this,QDBusObjectPath *param_1)

{
  QString::QString((QString *)this,(QString *)param_1);
  return;
}



// ==== 001634fe  QDBusObjectPath::~QDBusObjectPath

/* QDBusObjectPath::~QDBusObjectPath() */

void __thiscall QDBusObjectPath::~QDBusObjectPath(QDBusObjectPath *this)

{
  QString::~QString((QString *)this);
  return;
}



// ==== 00211f22  QDBusObjectPath::operator=

/* QDBusObjectPath::TEMPNAMEPLACEHOLDERVALUE(QDBusObjectPath const&) */

QDBusObjectPath * __thiscall
QDBusObjectPath::operator=(QDBusObjectPath *this,QDBusObjectPath *param_1)

{
  QString::operator=((QString *)this,(QString *)param_1);
  return this;
}



// ==== 0022a9f6  QDBusObjectPath::QDBusObjectPath

/* QDBusObjectPath::QDBusObjectPath(QString&&) */

void __thiscall QDBusObjectPath::QDBusObjectPath(QDBusObjectPath *this,QString *param_1)

{
  QString::QString((QString *)this,param_1);
  ::QDBusObjectPath::doCheck();
  return;
}



// ==== 0022aa50  QDBusObjectPath::QDBusObjectPath

/* QDBusObjectPath::QDBusObjectPath(QString const&) */

void __thiscall QDBusObjectPath::QDBusObjectPath(QDBusObjectPath *this,QString *param_1)

{
  QString::QString((QString *)this,param_1);
  ::QDBusObjectPath::doCheck();
  return;
}


