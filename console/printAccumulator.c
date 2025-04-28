#include "console.h"

void
printAccumulator (void)
{
  int accumulator;
  sc_accumulatorGet (&accumulator);

  int sign, command, operand;
  sc_commandDecode (accumulator, &sign, &command, &operand);

  char signChar = sign == 0 ? '+' : '-';

  bc_box (1, 63, 1, 20, MT_WHITE, MT_BLACK, " Аккумулятор ", MT_RED, MT_BLACK);

  mt_gotoXY (2, 65);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("sc: %c%02X%02X hex: %04X", signChar, command, operand, accumulator);
  fflush (stdout);
}
