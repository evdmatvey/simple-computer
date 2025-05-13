#include "console.h"

void
CU ()
{
  int icounter;
  sc_icounterGet (&icounter);

  int value;
  sc_memoryGet2 (icounter, &value);

  int value2;
  sc_memoryGet2 (icounter, &value2);

  int sign, command, operand;
  sc_commandDecode (value, &sign, &command, &operand);

  int isCommandValid = sc_commandValidate (command);

  ALU (command, operand);
}
