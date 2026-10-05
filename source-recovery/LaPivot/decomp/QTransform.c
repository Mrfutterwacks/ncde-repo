// Ghidra decompile of LaPivot.oracle — class/namespace QTransform (1 functions). Raw; not source.

// ==== 00289fc8  QTransform::QTransform

/* QTransform::QTransform() */

void __thiscall QTransform::QTransform(QTransform *this)

{
  *(undefined8 *)this = 0x3ff0000000000000;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
                    /* try { // try from 0028a015 to 0038a019 has its CatchHandler @ 0028b701 */
  *(undefined8 *)(this + 0x20) = 0x3ff0000000000000;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0x3ff0000000000000;
  this[0x48] = (QTransform)((byte)this[0x48] & 0xe0);
  *(ushort *)(this + 0x48) = *(ushort *)(this + 0x48) & 0xfc1f;
  return;
}


