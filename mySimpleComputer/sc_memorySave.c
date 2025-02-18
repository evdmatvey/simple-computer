#include "sc.h"

int
sc_memorySave (char *filename)
{
  FILE *file = fopen (filename, "wb");

  if (file == NULL)
    {
      return -1;
    }

  size_t writtenItems = fwrite (memory, sizeof (int), MEMORY_SIZE, file);

  if (writtenItems < MEMORY_SIZE)
    {
      return -1;
    }

  fclose (file);
  return 0;
}
