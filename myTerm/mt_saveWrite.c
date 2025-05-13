#include "mt.h"

int
safe_write (const char *buf, size_t len)
{
  ssize_t bytes_written = write (STDOUT_FILENO, buf, len);
  fflush (stdout);
  return (bytes_written == len) ? 0 : -1;
}
