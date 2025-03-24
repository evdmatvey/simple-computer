#include "mt.h"

int
mt_clrscr (void)
{
  const char *seq = "\033[2J\033[H";
  return safe_write (seq, 7);
}

int
mt_gotoXY (int row, int col)
{
  char buf[100];
  snprintf (buf, sizeof (buf), "\033[%d;%dH", row, col);
  return safe_write (buf, strlen (buf));
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return -1;
  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}

int
mt_setcursorvisible (int value)
{
  const char *seq = (value) ? "\033[?25h" : "\033[?25l";
  return safe_write (seq, 6);
}

int
mt_delline (void)
{
  const char *seq = "\033[2K\r";
  return safe_write (seq, 5);
}
