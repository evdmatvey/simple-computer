#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include "../include/myTerm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int bc_symbols[18][2];
int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2, colors box_fg, colors box_bg,
            char *header, colors header_fg, colors header_bg);
int bc_printbigchar (int *symbol, int x, int y, colors fg, colors bg);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);
int ToBigChar (int num, int *big);

#endif // !MY_BIG_CHARS_H
