#include "sc.h"

int
sc_memoryInit ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = 0;
    }

  return 0;
}
