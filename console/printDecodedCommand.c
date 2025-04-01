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

  mt_gotoXY (16, 15);
  mt_setfgcolor (MT_RED);
  mt_setbgcolor (MT_WHITE);
  printf ("Редактируемая ячейка (формат)");
  fflush (stdout);

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
          printf ("dec: -1 | oct: -1 | hex: -1 | bin: ");
        }
      else
        {
          printf ("dec: %d | oct: -%o | hex: -%X | bin: ", abs_value,
                  -abs_value, -abs_value);
        }
    }
  else
    {
      abs_value = magnitude;
      printf ("dec: +%d | oct: +%o | hex: +%X | bin: ", abs_value, abs_value,
              abs_value);
    }

  printBinary (value);
  printf ("\n");
  fflush (stdout);
}
