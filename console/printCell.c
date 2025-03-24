#include "console.h"

void
printCell (int address, enum colors fg, enum colors bg)
{
  int value;
  if (sc_memoryGet (address, &value) == -1)
    return;

  int row = MEM_START_ROW + (address / COLS_PER_ROW);
  int col = MEM_START_COL + (address % COLS_PER_ROW) * CELL_WIDTH;

  mt_gotoXY (row, col);
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  int sign = (value & SIGN_MASK) >> 14;
  int command = (value & COMMAND_MASK) >> 7;
  int operand = value & OPERAND_MASK;
  printf ("%c%02X%02X", (sign == 0) ? '+' : '-', command, operand);
  fflush (stdout);
}
