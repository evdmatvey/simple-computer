#include "console.h"

#define HISTORY_SIZE 4
#define TERM_START_ROW 20
#define TERM_START_COL 70

typedef struct BufferValue
{
  int address;
  int value;
  int type;
} BufferValue;

static BufferValue buffer[HISTORY_SIZE];
static int head = 0;
static int tail = 0;
static int count = 0;

void
addElement (BufferValue value)
{
  if (count == HISTORY_SIZE)
    {
      head = (head + 1) % HISTORY_SIZE;
      count--;
    }

  buffer[tail] = value;
  tail = (tail + 1) % HISTORY_SIZE;
  count++;
}

void
printBuffer ()
{
  mt_gotoXY (19, 71);
  mt_setbgcolor (MT_WHITE);
  mt_setfgcolor (MT_GREEN);
  printf ("IN--OUT");
  fflush (stdout);
  int current = head;
  for (int i = 0; i < count; i++)
    {
      BufferValue value = buffer[current];
      int sign = (value.value & SIGN_MASK) >> 14;
      int command = (value.value & COMMAND_MASK) >> 7;
      int operand = value.value & OPERAND_MASK;

      mt_gotoXY (TERM_START_ROW + i, TERM_START_COL);
      mt_setbgcolor (MT_BLACK);
      mt_setfgcolor (MT_WHITE);
      printf ("%03d%c %c%02X%02X", value.address, value.type == 0 ? '>' : '<',
              sign == 0 ? '+' : '-', command, operand);
      fflush (stdout);
      current = (current + 1) % HISTORY_SIZE;
    }
}

void
printTerm (int address, int input)
{
  int memValue;
  if (sc_memoryGet (address, &memValue) == -1)
    {
      return;
    }

  BufferValue newValue = { address, memValue, input };
  addElement (newValue);
  printBuffer ();
}
