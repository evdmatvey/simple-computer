#include "console.h"
#include <stdio.h>

void
printCommand (void)
{
  int addr;
  if (sc_icounterGet (&addr) == -1)
    return;

  int value;
  if (sc_memoryGet (addr, &value) == -1)
    return;

  int sign = (value >> 14) & 1;
  int command = (value >> 7) & 0x7F;
  int operand = value & 0x7F;
  int res = sc_commandValidate (command);

  bc_box (4, 85, 1, 20, MT_WHITE, MT_BLACK, " Команда ", MT_RED, MT_BLACK);

  mt_gotoXY (5, 88);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("  %c %c%02X : %02X   ", res == -1 ? '!' : ' ', sign ? '-' : '+',
          command, operand);
  fflush (stdout);
}
