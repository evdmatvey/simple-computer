#include "sc.h"

static int step = 0;

int
getStep ()
{
  return step;
}

void
incrementStep (int type)
{
  if (type == 0)
    step += 10;

  if (type == 1)
    step += 1;
}

void
resetStep ()
{
  step = 0;
}
