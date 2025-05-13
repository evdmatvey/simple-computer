#include "sc.h"

int
key_to_index (int key)
{
  return key / STEP;
}

Node *
create_node (int key, int *value, int value_size)
{
  Node *node = (Node *)malloc (sizeof (Node));
  node->key = key;
  node->value_size = value_size;
  node->value = (int *)malloc (sizeof (int) * value_size);
  memcpy (node->value, value, sizeof (int) * value_size);
  node->prev = node->next = NULL;
  return node;
}

LRUCache *
lru_cache_create (int capacity)
{
  LRUCache *cache = (LRUCache *)malloc (sizeof (LRUCache));
  cache->head = cache->tail = NULL;
  cache->size = 0;
  cache->capacity = capacity;
  for (int i = 0; i < 13; i++)
    {
      cache->hash[i] = NULL;
    }
  return cache;
}

void
remove_node (LRUCache *cache, Node *node)
{
  if (!node)
    return;

  if (node->prev)
    node->prev->next = node->next;
  else
    cache->head = node->next;

  if (node->next)
    node->next->prev = node->prev;
  else
    cache->tail = node->prev;
}

void
add_to_head (LRUCache *cache, Node *node)
{
  node->prev = NULL;
  node->next = cache->head;
  if (cache->head)
    cache->head->prev = node;
  cache->head = node;
  if (cache->tail == NULL)
    cache->tail = node;
}

void
move_to_head (LRUCache *cache, Node *node)
{
  remove_node (cache, node);
  add_to_head (cache, node);
}

void
remove_tail (LRUCache *cache)
{
  if (cache->tail == NULL)
    return;
  Node *tail = cache->tail;
  int idx = key_to_index (tail->key);
  cache->hash[idx] = NULL;

  remove_node (cache, tail);
  free (tail->value);
  free (tail);
  cache->size--;
}

int *
lru_cache_get (LRUCache *cache, int key, int *value_size)
{
  int idx = key_to_index (key);
  Node *node = cache->hash[idx];
  if (!node)
    return NULL;

  move_to_head (cache, node);
  *value_size = node->value_size;
  return node->value;
}

void
lru_cache_put (LRUCache *cache, int key, int *value, int value_size)
{
  int idx = key_to_index (key);
  Node *node = cache->hash[idx];

  if (node)
    {
      memcpy (node->value, value, sizeof (int) * value_size);
      node->value_size = value_size;
      move_to_head (cache, node);
    }
  else
    {
      Node *new_node = create_node (key, value, value_size);
      cache->hash[idx] = new_node;
      add_to_head (cache, new_node);
      cache->size++;

      if (cache->size > cache->capacity)
        {
          remove_tail (cache);
        }
    }
}

void
lru_cache_free (LRUCache *cache)
{
  cache = lru_cache_create (5);
}
