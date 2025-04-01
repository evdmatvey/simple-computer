#include "console.h"

void
printMemoryData ()
{
  mt_gotoXY (1, 25);
  mt_setfgcolor (MT_RED);
  mt_setbgcolor (MT_BLACK);
  printf ("Оперативная память");
  fflush (stdout);
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

  sc_icounterSet (1);
  sc_accumulatorSet (39);
  sc_regSet (INVALID_COMMAND_MASK, 1);
  sc_regSet (IGNORE_CLOCK_MASK, 1);
}

void
startTerm ()
{
  mt_clrscr ();
  printMemoryData ();
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
