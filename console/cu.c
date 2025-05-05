#include "console.h"

void
CU ()
{
  int icounter;
  sc_icounterGet (&icounter);

  int value;
  sc_memoryGet (icounter, &value);

  int sign, command, operand;
  sc_commandDecode (value, &sign, &command, &operand);

  int isCommandValid = sc_commandValidate (command);

  if (isCommandValid == 0)
    {
      ALU (command, operand);
    }

  incrementStep ();
}
