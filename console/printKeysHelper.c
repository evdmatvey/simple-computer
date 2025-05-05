#include "console.h"
#include <stdio.h>

void
printKeysHelper ()
{
  bc_box (19, 81, 4, 27, MT_WHITE, MT_BLACK, "Клавиши", MT_GREEN, MT_WHITE);

  mt_gotoXY (20, 82);
  mt_setbgcolor (MT_BLACK);

  mt_setfgcolor (MT_GREEN);
  printf ("l");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - load ");
  fflush (stdout);

  mt_setfgcolor (MT_GREEN);
  printf ("s");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - save ");
  fflush (stdout);

  mt_setfgcolor (MT_GREEN);
  printf ("i");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - reset");
  fflush (stdout);

  mt_gotoXY (21, 82);

  mt_setfgcolor (MT_RED);
  printf ("r");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - run ");
  fflush (stdout);

  mt_setfgcolor (MT_RED);
  printf ("t");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - step");
  fflush (stdout);

  mt_gotoXY (22, 82);

  mt_setfgcolor (MT_GREEN);
  printf ("ESC");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - exit ");
  fflush (stdout);

  mt_setfgcolor (MT_GREEN);
  printf ("F5");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - accumulator");
  fflush (stdout);

  mt_gotoXY (23, 82);

  mt_setfgcolor (MT_GREEN);
  printf ("F6");
  fflush (stdout);

  mt_setfgcolor (MT_WHITE);
  printf (" - instruction counter");
  fflush (stdout);

  // Восстановим цвета
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);
}
