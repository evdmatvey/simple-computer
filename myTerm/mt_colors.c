#include "mt.h"

int
mt_setfgcolor (colors c)
{
  const char *seq = "\033[3%dm";
  char buf[10];
  snprintf (buf, sizeof (buf), seq, c);
  return safe_write (buf, 6);
}

int
mt_setbgcolor (colors c)
{
  const char *seq = "\033[4%dm";
  char buf[10];
  snprintf (buf, sizeof (buf), seq, c);
  return safe_write (buf, 6);
}

int
mt_setdefaultcolor (void)
{
  const char *seq = "\033[0m";
  return safe_write (seq, 4);
}
