#include "console.h"

void
printCell (int address)
{
  int value;
  if (sc_memoryGet (address, &value) == -1)
    {
      return;
    }

  int sign = (value & SIGN_MASK) >> 14;
  int command = (value & COMMAND_MASK) >> 7;
  int operand = value & OPERAND_MASK;

  char signSymbol = sign == 0 ? '+' : '-';

  printf ("%c%02X%02X", signSymbol, command, operand);
}
