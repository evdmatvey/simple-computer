#include "sc.h"

LRUCache *cache = NULL;

void
sc_cacheInit (LRUCache *newCache)
{
  cache = newCache;
}

LRUCache *
sc_cacheGetCache ()
{
  return cache;
}

void
sc_cachePut (int address)
{
  int key = address - (address % 10);
  int value_size = key < 12 ? 10 : 8;
  int *values = (int *)malloc (value_size * sizeof (int));

  for (int i = 0; i < value_size; i++)
    {
      values[i] = memory[key + i];
    }

  lru_cache_put (cache, key, values, value_size);
}

int
sc_cacheGet (int address)
{
  int key = address - (address % 10);
  int value_size;

  int *values = lru_cache_get (cache, address, &value_size);

  if (values == NULL)
    {
      sc_cachePut (address);
      return 0xFFFF;
    }

  int localAddress = address % 10;

  return values[localAddress];
}

void
sc_cacheClear ()
{
  cache = lru_cache_create (5);
}
