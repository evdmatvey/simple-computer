#include "console.h"

void
printAccumulator (void)
{
  int accumulator;
  sc_accumulatorGet (&accumulator);

  int sign = (accumulator & SIGN_MASK) >> 14;
  int command = (accumulator & COMMAND_MASK) >> 7;
  int operand = accumulator & OPERAND_MASK;

  char signChar = sign == 0 ? '+' : '-';

  mt_gotoXY (1, 69);
  mt_setfgcolor (MT_RED);
  mt_setbgcolor (MT_BLACK);
  printf ("Аккумулятор");
  fflush (stdout);
  mt_gotoXY (2, 65);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("sc: %c%02X%02X hex: %04X", signChar, command, operand, accumulator);
  fflush (stdout);
}
