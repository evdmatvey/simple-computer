#include "console.h"

void
printCounters (void)
{
  int icounter;
  sc_icounterGet (&icounter);

  int sign = (icounter & SIGN_MASK) >> 14;
  int command = (icounter & COMMAND_MASK) >> 7;
  int operand = icounter & OPERAND_MASK;

  char signChar = sign == 0 ? '+' : '-';

  bc_box (4, 63, 1, 20, MT_WHITE, MT_BLACK, " Счётчик комманд ", MT_RED,
          MT_BLACK);
  mt_gotoXY (5, 65);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("T: 00    IC: %c%02X%02X", signChar, command, operand);
  fflush (stdout);
}
