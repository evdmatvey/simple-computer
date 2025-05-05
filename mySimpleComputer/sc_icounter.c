#include "sc.h"

int
sc_icounterInit (void)
{
  instuctionCounter = 0;

  return 0;
}

int
sc_icounterGet (int *value)
{
  if (value == NULL)
    {
      return -1;
    }

  *value = instuctionCounter;

  return 0;
}

int
sc_icounterSet (int value)
{
  if (value >= MAX_15_BIT_POSITIVE || value < MAX_15_BIT_NEGATIVE)
    {
      return -1;
    }

  instuctionCounter = value;

  return 0;
}
