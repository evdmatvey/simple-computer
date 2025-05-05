#include "bc.h"
#include <stdio.h>

int
bc_strlen (char *str)
{
  if (!str)
    return 0;

  int count = 0;
  uint8_t *ptr = (uint8_t *)str;

  while (*ptr)
    {
      uint8_t first = *ptr;
      size_t len;

      if ((first & 0x80) == 0x00)
        {
          len = 1;
        }
      else if ((first & 0xE0) == 0xC0)
        {
          len = 2;
        }
      else if ((first & 0xF0) == 0xE0)
        {
          len = 3;
        }
      else if ((first & 0xF8) == 0xF0)
        {
          len = 4;
        }
      else
        {
          return 0;
        }

      for (size_t i = 1; i < len; i++)
        {
          if ((ptr[i] & 0xC0) != 0x80)
            {
              return 0;
            }
        }

      ptr += len;
      count++;
    }

  return count;
}

int
bc_printA (char *str)
{
  printf ("\033(0%s\033(B", str);
  fflush (stdout);
  return 0;
}

int
bc_box (int x1, int y1, int height, int width, enum colors box_fg,
        enum colors box_bg, char *header, enum colors header_fg,
        enum colors header_bg)
{
  if (x1 < 0 || y1 < 0 || height < 0 || width < 0)
    {
      return -1;
    }

  mt_gotoXY (x1, y1);
  bc_printA ("l");
  for (int i = y1; i < y1 + width; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("k");
  for (int i = x1; i < x1 + height; i++)
    {
      mt_gotoXY (i + 1, y1);
      bc_printA ("x");
      mt_gotoXY (i + 1, y1 + width + 1);
      bc_printA ("x");
    }
  mt_gotoXY (x1 + height + 1, y1);
  bc_printA ("m");
  for (int i = y1; i < y1 + width; i++)
    {
      bc_printA ("q");
    }
  bc_printA ("j");
  if (header)
    {
      int header_len = bc_strlen (header);
      int offset = (width - header_len) / 2;
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (x1, y1 + offset + 1);
      printf ("%s", header);
      fflush (stdout);
    }

  mt_setdefaultcolor ();

  return 0;
}
int
bc_printbigchar (int *big, int x, int y, colors fg, colors bg)
{
  if ((x < 0) || (y < 0))
    return -1;
  mt_gotoXY (x, y);
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  int position = 0;
  char row[9];
  row[8] = '\0';
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          int bit = (big[position] >> ((i % 4) * 8 + j)) & 1;
          if (bit == 0)
            row[j] = ' ';
          else
            row[j] = 'a';
        }
      mt_gotoXY (x + i, y);
      bc_printA (row);
      if (i == 3)
        {
          position = 1;
        }
    }
  mt_setbgcolor (MT_BLACK);
  mt_setfgcolor (MT_WHITE);
  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7 || value < 0 || value > 1)
    return -1;
  int position;
  if (y > 3)
    position = 1;
  else
    position = 0;
  y = y % 4;
  if (value == 0)
    big[position] &= ~(1 << (y * 8 + x));
  else
    big[position] |= 1 << (y * 8 + x);

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int position;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;
  if (y > 3)
    position = 1;
  else
    position = 0;
  y = y % 4;
  *value = (big[position] >> (y * 8 + x)) & 1;

  return 0;
}

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (write (fd, big, count * (sizeof (int)) * 2) == -1)
    return -1;
  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  *count = read (fd, big, need_count * sizeof (int) * 2);
  if (*count == -1)
    {
      *count = 0;
      return -1;
    }
  *count = *count / (sizeof (int) * 2);
  return 0;
}

int
ToBigChar (int num, int *big)
{
  big[0] = bc_symbols[num][0];
  big[1] = bc_symbols[num][1];
  return 0;
}
