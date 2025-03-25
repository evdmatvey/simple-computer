#include "console.h"

void
printDecodedCommand ()
{
  int addr;
  if (sc_icounterGet (&addr) == -1)
    {
      return;
    }

  int value;
  if (sc_memoryGet (addr, &value) == -1)
    {
      return;
    }

  int dec = value;
  if (value > 16383)
    {
      dec -= 16384;
      dec *= -1;
    }

  mt_gotoXY (16, 15);
  mt_setfgcolor (MT_RED);
  mt_setbgcolor (MT_WHITE);
  printf ("Редактируемая ячейка (формат)");
  fflush (stdout);
  mt_gotoXY (17, 3);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("dec: %05d | oct: %05o | hex: %04X | bin: %015b\n", dec, value,
          value, value);
  fflush (stdout);
}
