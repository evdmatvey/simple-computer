#include "console.h"

void
printMemoryData ()
{
  bc_box (1, 1, 13, 60, MT_WHITE, MT_BLACK, " Оперативная память ", MT_RED,
          MT_BLACK);

  int current_cell;
  if (sc_icounterGet (&current_cell) == -1)
    {
      return;
    };

  for (int i = 0; i < 128; i++)
    {
      if (i == current_cell)
        {
          printCell (i, MT_BLACK, MT_WHITE);
        }
      else
        {
          printCell (i, MT_WHITE, MT_BLACK);
        }
    }
  printf ("\n");
}

void
init ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  sc_memorySet (2, 0x3912);
  sc_memorySet (3, 0x2312);
  sc_memorySet (4, 0x1355);
  sc_memorySet (5, 0x1312);
  sc_memorySet (6, 0x1210);
  sc_memorySet (10, 0x2323);
  sc_memorySet (29, 0x3912);
  sc_memorySet (0, 16383);
  sc_memorySet (1, -2);

  sc_memoryInit ();

  sc_icounterSet (6);
  sc_accumulatorSet (39);
  sc_regSet (IGNORE_CLOCK_MASK, 1);
}

int
drawingBigChars ()
{
  int addr;
  sc_icounterGet (&addr);

  int value;
  sc_memoryGet (addr, &value);

  int sign = (value >> 14) & 1;
  int command = (value >> 7) & 0x7F;
  int operand = value & 0x7F;

  char hex_1[3];
  sprintf (hex_1, "%02X", command);

  int hex_array_1[2];

  for (int i = 0; i < 3; i++)
    {
      if (hex_1[i] >= '0' && hex_1[i] <= '9')
        {
          hex_array_1[i] = hex_1[i] - '0';
        }
      else if (hex_1[i] >= 'A' && hex_1[i] <= 'F')
        {
          hex_array_1[i] = hex_1[i] - 'A' + 10;
        }
    }

  char hex_2[3];
  sprintf (hex_2, "%02X", operand);

  int hex_array_2[2];

  for (int i = 0; i < 3; i++)
    {
      if (hex_2[i] >= '0' && hex_2[i] <= '9')
        {
          hex_array_2[i] = hex_2[i] - '0';
        }
      else if (hex_2[i] >= 'A' && hex_2[i] <= 'F')
        {
          hex_array_2[i] = hex_2[i] - 'A' + 10;
        }
    }

  int row = 8;
  int startColumn = 64;

  if (sign)
    {
      bc_printbigchar (bc_symbols[17], row, startColumn, MT_GREEN, MT_BLACK);
    }
  else
    {
      bc_printbigchar (bc_symbols[16], row, startColumn, MT_GREEN, MT_BLACK);
    }

  for (int i = 0; i < 2; i++)
    {
      bc_printbigchar (bc_symbols[hex_array_1[i]], row,
                       startColumn + 8 * (i + 1), MT_GREEN, MT_BLACK);
    }

  for (int i = 0; i < 2; i++)
    {
      bc_printbigchar (bc_symbols[hex_array_2[i]], row,
                       startColumn + 16 + 8 * (i + 1), MT_GREEN, MT_BLACK);
    }

  bc_box (7, 63, 8, 42, MT_WHITE, MT_BLACK,
          " Редактируемая ячейка (увеличенно) ", MT_RED, MT_BLACK);

  return 0;
}

void
startTerm ()
{
  mt_clrscr ();
  printMemoryData ();

  drawingBigChars ();
  printAccumulator ();
  printCounters ();
  printFlags ();
  printDecodedCommand ();
  printCommand ();

  printTerm (0, 0);
  printTerm (1, 0);
  printTerm (2, 0);
  printTerm (3, 0);
  printTerm (4, 0);
  printTerm (5, 0);
  printTerm (6, 0);

  mt_gotoXY (25, 1);
  mt_setdefaultcolor ();
}

void
checkTerm ()
{
  if (!isatty (fileno (stdout)))
    {
      fprintf (stderr, "Ошибка: Приложение требует терминал\n");
      exit (EXIT_FAILURE);
    }

  int cols, rows;
  if (mt_getscreensize (&rows, &cols) != 0)
    {
      fprintf (stderr, "Ошибка: Не удалось получить размер экрана\n");
      exit (EXIT_FAILURE);
    }

  if (cols < 110 || rows < 25)
    {
      fprintf (stderr, "Ошибка: Размер экрана недостаточен\n");
      exit (EXIT_FAILURE);
    }
}

int
main ()
{
  checkTerm ();
  init ();
  startTerm ();

  return 0;
}
