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

  int sign = (value >> 14) & 1;
  int magnitude = value & 0x3FFF;
  int abs_value;

  if (sign)
    {
      abs_value = -((~(value & 0x3FFF) + 1) & 0x3FFF);

      if (abs_value == -1)
        {
          printf ("dec: -1");
        }
      else
        {
          printf ("dec: %d", abs_value);
        }
    }
  else
    {
      abs_value = magnitude;
      printf ("dec: +%d", abs_value);
    }

  printf (" | oct: %05o | hex: %04X | bin:", value, value);

  printBinary (value);
  printf ("\n");
  fflush (stdout);

  bc_box (16, 1, 1, 60, MT_WHITE, MT_BLACK, " Редактируемая ячейчка (формат) ",
          MT_RED, MT_WHITE);
}
