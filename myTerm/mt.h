#ifndef MT_H
#define MT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef enum
{
  MT_BLACK,
  MT_RED,
  MT_GREEN,
  MT_YELLOW,
  MT_BLUE,
  MT_MAGENTA,
  MT_CYAN,
  MT_WHITE
} colors;

extern int safe_write (const char *buf, size_t len);

#endif // !MT_H
