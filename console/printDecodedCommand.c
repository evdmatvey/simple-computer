#include "console.h"

void
printBinary (int value)
{
  for (int i = 14; i >= 0; i--)
    {
      printf ("%d", (value >> i) & 1);
    }
}

void
printDecodedCommand ()
{
  int addr;
  if (sc_icounterGet (&addr) == -1)
    return;

  int value;
  if (sc_memoryGet (addr, &value) == -1)
    return;

  mt_gotoXY (17, 3);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);

  int abs_value = sc_getDecValueOfMemoryData (value);

  if (abs_value < 0)
    {

      printf ("dec: %d", abs_value);
    }
  else
    {
      printf ("dec: +%d", abs_value);
    }

  printf (" | oct: %05o | hex: %04X | bin:", value, value);

  printBinary (value);
  printf ("\n");
  fflush (stdout);

  bc_box (16, 1, 1, 60, MT_WHITE, MT_BLACK, " Редактируемая ячейчка (формат) ",
          MT_RED, MT_WHITE);
}
