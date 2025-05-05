#include "console.h"

void
IRC (int signum)
{
  if (signum == SIGALRM)
    {
      sc_regSet (IGNORE_CLOCK_MASK, 0);
    }

  if (signum == SIGUSR1)
    {
      sc_memoryInit ();
      sc_accumulatorInit ();
      sc_icounterInit ();
      resetStep ();
      sc_regSet (IGNORE_CLOCK_MASK, 1);
    }
}
