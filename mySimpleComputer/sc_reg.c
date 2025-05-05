#include "sc.h"

int
sc_regInit (void)
{
  flagsRegister = 0;

  return 0;
}

int
sc_regGet (int flag, int *value)
{
  if ((flag
       & (OVERFLOW_MASK | DIVISION_BY_ZERO_MASK | MEMORY_ERROR_MASK
          | IGNORE_CLOCK_MASK | INVALID_COMMAND_MASK))
      == 0)
    {
      return -1;
    }

  if (value == NULL)
    {
      return -1;
    }

  *value = (flagsRegister & flag) ? 1 : 0;

  return 0;
}

int
sc_regSet (int flag, int value)
{
  if ((flag
       & (OVERFLOW_MASK | DIVISION_BY_ZERO_MASK | MEMORY_ERROR_MASK
          | IGNORE_CLOCK_MASK | INVALID_COMMAND_MASK))
      == 0)
    {
      return -1;
    }

  if (value == 1)
    {
      flagsRegister |= flag;
    }
  else if (value == 0)
    {
      flagsRegister &= ~flag;
    }
  else
    {
      return -1;
    }

  return 0;
}
