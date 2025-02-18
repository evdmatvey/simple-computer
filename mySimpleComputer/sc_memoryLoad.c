#include "sc.h"

int
sc_memoryLoad (char *filename)
{
  FILE *file = fopen (filename, "rb");

  if (file == NULL)
    {
      return -1;
    }

  size_t readItems = fread (memory, sizeof (int), MEMORY_SIZE, file);

  if (readItems < MEMORY_SIZE)
    {
      if (!feof (file))
        {
          fclose (file);
          return -1;
        }
    }

  fclose (file);
  return 0;
}
