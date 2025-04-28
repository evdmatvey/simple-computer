#include "console.h"
#include <stdio.h>

int
power (int x, int a)
{
  int res = 1;

  for (int i = 0; i < a; i++)
    {
      res *= x;
    }

  return res;
}

void
gotoPlace (int x, int y)
{
  mt_gotoXY (y, x);
  mt_setbgcolor (MT_WHITE);
  mt_setfgcolor (MT_BLACK);
  printf ("     ");
  fflush (stdout);
  mt_gotoXY (y, x);
}

int
isCorrectIntKey (enum keys key)
{
  if (key < 1060 || key > 1069)
    return -1;

  return 0;
}

int
isCorrectHexKey (enum keys key)
{
  if (key < 1008 || key > 1013)
    return -1;

  return 0;
}

int
convertFromHexToInt (int hex, int position)
{
  return hex * power (16, (position + 1) % 2);
}

void
readSign (int *sign, enum keys key, int *symbolPosition)
{
  if (key == KEY_PLUS)
    {
      *sign = 1;
      *symbolPosition -= 1;
    }

  if (key == KEY_MINUS)
    {
      *sign = -1;
      *symbolPosition -= 1;
    }
}

void
readTwoHexBitToVar (int *var, enum keys key, int *symbolPosition)
{
  if (isCorrectHexKey (key) == 0)
    {
      *var += convertFromHexToInt (key - 1008 + 10, *symbolPosition);
      *symbolPosition -= 1;
    }

  if (isCorrectIntKey (key) == 0)
    {
      *var += convertFromHexToInt (key - 1060, *symbolPosition);
      *symbolPosition -= 1;
    }
}

void
printCorrectScHexBit (enum keys key, int symbolPosition)
{
  if (symbolPosition == 5)
    {
      if (key == KEY_MINUS || key == KEY_PLUS)
        {
          printf ("%s", rk_keyToString (key));
          fflush (stdout);
        }
    }

  if (symbolPosition < 5 && symbolPosition > 0)
    {
      if ((key >= 1008 && key <= 1013) || (key >= 1060 && key <= 1069))
        {
          printf ("%s", rk_keyToString (key));
          fflush (stdout);
        }
    }
}

void
readKeyLoop (int *sign, int *command, int *operand)
{
  enum keys key;
  int symbolPosition = 5;

  while (1)
    {
      if (symbolPosition == 0)
        break;

      rk_readkey (&key);
      printCorrectScHexBit (key, symbolPosition);

      if (key == KEY_ESC)
        {
          *sign = -1;
          *command = -1;
          *operand = -1;
          break;
        }

      if (symbolPosition == 5)
        {
          readSign (sign, key, &symbolPosition);
        }
      else if (symbolPosition == 4 || symbolPosition == 3)
        {
          readTwoHexBitToVar (command, key, &symbolPosition);
        }
      else if (symbolPosition == 2 || symbolPosition == 1)
        {
          readTwoHexBitToVar (operand, key, &symbolPosition);
        }
    }
}

int
convertIntToScValue (int *sign, int *command, int *operand)
{

  int first = (*command) & 0x7F;
  int second = (*operand) & 0x7F;
  mt_gotoXY (21, 20);
  printf ("%d %d", *command, *operand);
  fflush (stdout);

  int result = (first << 7) | second;
  int s = *sign == 1 ? 0 : 1;
  return (s << 14) | result;
}

int
editInPlace (int x, int y)
{
  int value = 0;
  int sign = 0, command = 0, operand = 0;

  gotoPlace (x, y);
  readKeyLoop (&sign, &command, &operand);
  mt_setfgcolor (MT_WHITE);
  mt_setbgcolor (MT_BLACK);

  if (command == -1 && sign == -1 && operand == -1)
    {
      return -1;
    }

  value = convertIntToScValue (&sign, &command, &operand);
  value = sc_getDecValueOfMemoryData (value);

  return value;
}
