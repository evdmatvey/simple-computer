#ifndef CONSOLE_H

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <stdio.h>

void printCell (int address);
void printDecodedCommand (int value);
void printFlags (void);
void printAccumulator (void);
void printCounters (void);

#endif
