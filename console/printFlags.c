#include "console.h"

void
printFlags (void)
{
  int overflowFlag, memoryFlag, divisionByZeroFlag, ignoreClockFlag,
      invalidCommandFlag;

  sc_regGet (OVERFLOW_MASK, &overflowFlag);
  sc_regGet (DIVISION_BY_ZERO_MASK, &divisionByZeroFlag);
  sc_regGet (MEMORY_ERROR_MASK, &memoryFlag);
  sc_regGet (IGNORE_CLOCK_MASK, &ignoreClockFlag);
  sc_regGet (INVALID_COMMAND_MASK, &invalidCommandFlag);

  char overflow = overflowFlag == 0 ? '_' : 'P';
  char memory = memoryFlag == 0 ? '_' : 'M';
  char divisionByZero = divisionByZeroFlag == 0 ? '_' : '0';
  char ignoreClock = ignoreClockFlag == 0 ? '_' : 'T';
  char invalidCommand = invalidCommandFlag == 0 ? '_' : 'E';

  bc_box (1, 85, 1, 20, MT_WHITE, MT_BLACK, " Регистр флагов ", MT_RED,
          MT_BLACK);
  mt_gotoXY (2, 90);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
  printf ("%c  %c  %c  %c  %c", overflow, divisionByZero, memory, ignoreClock,
          invalidCommand);
  fflush (stdout);
}
