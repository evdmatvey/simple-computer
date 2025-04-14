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
  if (value >= MAX_15_BIT_POSITIVE || value < MAX_15_BIT_NEGATIVE)
    {
      return -1;
    }

  accumulator = value;

  return 0;
}
