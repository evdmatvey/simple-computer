#include "console.h"

static int interactive = 1;

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
