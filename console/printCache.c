#include "console.h"
#include <stdio.h>

void
lru_cache_print (LRUCache *cache)
{
  Node *curr = cache->head;
  int row = 0;
  while (curr)
    {
      mt_gotoXY (20 + row, 2);
      printf ("%03d : ", curr->key);
      fflush (stdout);
      for (int i = 0; i < curr->value_size; i++)
        {
          int value = curr->value[i];
          int sign, command, operand;
          sc_commandDecode (value, &sign, &command, &operand);
          printf ("%c%02X%02X ", sign == 0 ? '+' : '-', command, operand);
          fflush (stdout);
        }
      curr = curr->next;
      row++;
    }

  if (row < 4)
    {
      int emptyRows = 5 - row;

      for (int i = 0; i < emptyRows; i++)
        {
          mt_gotoXY (20 + row + i, 2);
          printf (" -1");
          fflush (stdout);
        }
    }
}

void
printCache ()
{
  bc_box (19, 1, 5, 66, MT_WHITE, MT_BLACK, " КЕШ ПРОЦЕССОРА ", MT_GREEN,
          MT_WHITE);

  LRUCache *cache = sc_cacheGetCache ();

  lru_cache_print (cache);
}
