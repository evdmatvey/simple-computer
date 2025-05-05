#include "console.h"

static int step = 0;

int
getStep ()
{
  return step;
}

void
incrementStep ()
{
  step += 10;
}

void
resetStep ()
{
  step = 0;
}
