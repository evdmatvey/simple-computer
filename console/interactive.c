#include "console.h"

static int interactive = 0;

void
startInteractive ()
{
  interactive = 1;
}

void
stopInteractive ()
{
  interactive = 0;
}

int
getInteractive ()
{
  return interactive;
}
