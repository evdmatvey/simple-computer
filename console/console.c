#include "console.h"
#include <stdio.h>

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
  printMemoryData ();

  drawingBigChars ();
  printAccumulator ();
  printCounters ();
  printFlags ();
  printDecodedCommand ();
  printCommand ();
  printKeysHelper ();

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
loop ()
{

  rk_mytermsave ();
  rk_mytermregime (1, 1, 0, 0, 0);
  mt_setcursorvisible (0);

  enum keys key;
  int mode = MODE_MEMORY;

  while (1)
    {
      rk_readkey (&key);
      if (key == KEY_ESC)
        {
          break;
        }

      if (key == KEY_t)
        {
          CU ();
          startTerm ();
        }

      if (key == KEY_r)
        {
          startInteractive ();
          int interactive = getInteractive ();
          sc_regSet (IGNORE_CLOCK_MASK, 0);

          while (interactive)
            {
              CU ();
              startTerm ();
              interactive = getInteractive ();
              sleep (1);
            }

          sc_regSet (IGNORE_CLOCK_MASK, 1);
        }

      if (mode == MODE_MEMORY && key == KEY_ENTER)
        {
          int counter;
          sc_icounterGet (&counter);

          int row = MEM_START_ROW + (counter / COLS_PER_ROW);
          int col = MEM_START_COL + (counter % COLS_PER_ROW) * CELL_WIDTH;

          int newValue = editInPlace (col, row);
          int res = sc_memorySet (counter, newValue);
          startTerm ();
          if (res == 0)
            printTerm (counter, 1);
        }

      if (key == KEY_i || key == KEY_I)
        {
          mt_clrscr ();
          IRC (SIGUSR1);
          startTerm ();
        }

      int icounter;
      sc_icounterGet (&icounter);

      if (key == KEY_UP && mode == MODE_MEMORY)
        {
          int newIcounter
              = icounter - 10 < 0 ? 127 - (7 - icounter % 10) : icounter - 10;
          sc_icounterSet (newIcounter);
          startTerm ();
        }

      if (key == KEY_DOWN && mode == MODE_MEMORY)
        {
          int newIcounter
              = icounter + 10 >= 128 ? icounter % 10 : icounter + 10;
          sc_icounterSet (newIcounter);
          startTerm ();
        }

      if (key == KEY_LEFT && mode == MODE_MEMORY)
        {
          int newIcounter = icounter - 1 < 0 ? 127 : icounter - 1;
          sc_icounterSet (newIcounter);
          startTerm ();
        }

      if (key == KEY_RIGHT && mode == MODE_MEMORY)
        {
          int newIcounter = icounter + 1 >= 128 ? 0 : icounter + 1;
          sc_icounterSet (newIcounter);
          startTerm ();
        }

      if (key == KEY_F5)
        {
          if (mode == MODE_ACC)
            {
              mode = MODE_MEMORY;
            }
          else
            {
              mode = MODE_ACC;
              int newAcc = editInPlace (69, 2);
              if (newAcc < -16384 || newAcc > 32787)
                {
                  startTerm ();
                  continue;
                }

              sc_accumulatorSet (newAcc);
              startTerm ();
            }
        }

      if (key == KEY_F6)
        {
          if (mode == MODE_COUNTER)
            {
              mode = MODE_MEMORY;
            }
          else
            {
              mode = MODE_COUNTER;
              int newCounter = editInPlace (78, 5);
              if (newCounter < 0 || newCounter > 127)
                {
                  startTerm ();
                  continue;
                };
              sc_icounterSet (newCounter);
              mode = MODE_MEMORY;
              startTerm ();
            }
        }

      if (key == KEY_s)
        {
          mt_gotoXY (20, 10);
          mt_setbgcolor (MT_BLACK);
          mt_setfgcolor (MT_WHITE);
          char filename[128];

          rk_mytermregime (0, 0, 0, 1, 1);

          printf ("Введите имя файла для сохранения: ");
          if (fgets (filename, sizeof (filename), stdin) != NULL)
            {
              size_t len = strlen (filename);
              if (len > 0 && filename[len - 1] == '\n')
                {
                  filename[len - 1] = '\0';
                }

              if (sc_memorySave (filename) == 0)
                {
                  printf ("Данные успешно сохранены в файл '%s'.\n", filename);
                }
              else
                {
                  printf ("Ошибка при сохранении в файл '%s'.\n", filename);
                }
            }
          else
            {
              printf ("Ошибка ввода имени файла.\n");
            }

          rk_mytermregime (1, 1, 0, 0, 0);
        }

      if (key == KEY_l)
        {
          mt_gotoXY (20, 10);
          mt_setbgcolor (MT_BLACK);
          mt_setfgcolor (MT_WHITE);
          char filename[128];

          rk_mytermregime (0, 0, 0, 1, 1);

          printf ("Введите имя файла для сохранения: ");
          if (fgets (filename, sizeof (filename), stdin) != NULL)
            {
              size_t len = strlen (filename);
              if (len > 0 && filename[len - 1] == '\n')
                {
                  filename[len - 1] = '\0';
                }

              if (sc_memoryLoad (filename) == 0)
                {
                  printf ("Данные успешно загруженны из файла '%s'.\n",
                          filename);
                  startTerm ();
                }
              else
                {
                  printf ("Ошибка при загрузке из файла '%s'.\n", filename);
                }
            }
          else
            {
              printf ("Ошибка ввода имени файла.\n");
            }

          rk_mytermregime (1, 1, 0, 0, 0);
        }
    }

  rk_mytermrestore ();

  return 0;
}

int
main ()
{
  mt_clrscr ();
  checkTerm ();

  IRC (SIGUSR1);

  startTerm ();
  loop ();

  return 0;
}
