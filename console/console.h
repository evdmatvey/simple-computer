#ifndef CONSOLE_H

#include "../include/myBigChars.h"
#include "../include/myReadKey.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILENAME_LEN 256

#define MEM_START_ROW 2
#define MEM_START_COL 3
#define COLS_PER_ROW 10
#define CELL_WIDTH 6

#define MODE_MEMORY 0
#define MODE_ACC 1
#define MODE_COUNTER 2

void printCell (int address, enum colors fg, enum colors bg);
void printDecodedCommand ();
void printFlags (void);
void printAccumulator ();
void printCounters (void);
void printTerm (int address, int input);
void printCommand (void);
void printKeysHelper (void);
int editInPlace (int x, int y);

#endif // !CONSOLE_H
