#ifndef CONSOLE_H

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <stdio.h>

#define MEM_START_ROW 2
#define MEM_START_COL 3
#define COLS_PER_ROW 10
#define CELL_WIDTH 6

void printCell (int address, enum colors fg, enum colors bg);
void printDecodedCommand (void);
void printFlags (void);
void printAccumulator (void);
void printCounters (void);

#endif // !CONSOLE_H
