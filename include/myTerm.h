#ifndef MY_TERM_H
#define MY_TERM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef enum colors
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

int mt_clrscr (void);
int mt_gotoXY (int row, int col);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (colors c);
int mt_setbgcolor (colors c);
int mt_setdefaultcolor (void);
int mt_setcursorvisible (int value);
int mt_delline (void);

#endif // !MY_TERM_H
