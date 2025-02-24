#include "console.h"
#include <stdio.h>

void
printCounters (void)
{
  int icounter;
  sc_icounterGet (&icounter);

  int sign = (icounter & SIGN_MASK) >> 14;
  int command = (icounter & COMMAND_MASK) >> 7;
  int operand = icounter & OPERAND_MASK;

  char signChar = sign == 0 ? '+' : '-';

  printf ("T: 00 IC: %c%02X%02X", signChar, command, operand);
}
