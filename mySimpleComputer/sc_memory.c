#include "sc.h"

void
validate_memory ()
{
  int res = 0;

  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      int value = memory[i];
      int sign, command, operand;
      res = sc_commandDecode (value, &sign, &command, &operand);

      if (res == -1)
        {
          break;
        }
    }

  sc_regSet (INVALID_COMMAND_MASK, res == 0 ? 0 : 1);
}

int
sc_memoryInit ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = 0;
    }

  sc_regSet (INVALID_COMMAND_MASK, 0);
  resetStep ();
  sc_cacheClear ();

  return 0;
}

int
sc_memoryGet2 (int address, int *value)
{
  if (address < 0 || address >= MEMORY_SIZE)
    {
      return -1;
    }

  if (value == NULL)
    {
      return -1;
    }

  int isIgnore;
  sc_regGet (IGNORE_CLOCK_MASK, &isIgnore);
  int icounter;
  sc_icounterGet (&icounter);

  if (isIgnore == 0)
    {
      if (icounter == address)
        {
          int cached = sc_cacheGet (address);

          if (cached != 0xFFFF)
            {
              incrementStep (1);
              *value = cached;
              return 0;
            }

          incrementStep (0);
        }
    }

  *value = memory[address];

  return 0;
}

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= MEMORY_SIZE)
    {
      return -1;
    }

  if (value == NULL)
    {
      return -1;
    }

  *value = memory[address];

  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= MEMORY_SIZE)
    return -1;

  if (value < -16384 || value > 32788)
    return -1;

  if (value >= 0)
    {
      memory[address] = value;
    }
  else
    {
      int positive = -value;
      int inverted = (~positive) & 0x3FFF;
      memory[address] = (1 << 14) | (inverted + 1);
    }

  validate_memory ();

  sc_cachePut (address);
  incrementStep (0);

  return 0;
}

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

  validate_memory ();
  resetStep ();
  return 0;
}
