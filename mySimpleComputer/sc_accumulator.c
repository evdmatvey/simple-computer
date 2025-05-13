#include "sc.h"

int
sc_accumulatorInit (void)
{
  accumulator = 0;

  return 0;
}

int
sc_accumulatorGet (int *value)
{
  if (value == NULL)
    {
      return -1;
    }

  *value = accumulator;

  return 0;
}

int
sc_accumulatorSet (int value)
{

  if (value < -16384 || value > 32788)
    {
      return -1;
    }
  if (value >= 0)
    {
      accumulator = value;
    }
  else
    {
      int positive = -value;
      int inverted = (~positive) & 0x3FFF;
      accumulator = (1 << 14) | (inverted + 1);
    }

  return 0;
}
