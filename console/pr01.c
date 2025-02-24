#include "console.h"
#include <stdatomic.h>
#include <stdio.h>

void
printMemoryData ()
{
  for (int i = 0; i < 128; i++)
    {
      printCell (i);

      if ((i + 1) % 10 == 0)
        {
          printf ("\n");
        }
      else if (i + 1 != 128)
        {
          printf (" ");
        }
    }

  printf ("\n");
}

int
main ()
{
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_regInit ();
  sc_icounterInit ();

  sc_memorySet (0, 0b000000010001101);
  sc_memorySet (20, 0b000000010001101);
  sc_memorySet (50, 0b000000010001101);
  sc_memorySet (40, 0b000000010001101);
  sc_memorySet (10, 0b000111010101001);
  sc_memorySet (30, 0b001010010101001);
  printMemoryData ();

  int incorrectMemorySet = sc_memorySet (127, 10000000);
  printf ("\n\n------ INCORRECT MEMORY SET RESULT: %d ------\n\n",
          incorrectMemorySet);

  sc_regSet (MEMORY_ERROR_MASK, 0);
  sc_regSet (IGNORE_CLOCK_MASK, 1);
  sc_regSet (OVERFLOW_MASK, 0);
  sc_regSet (DIVISION_BY_ZERO_MASK, 1);
  sc_regSet (INVALID_COMMAND_MASK, 0);
  printFlags ();
  printf ("\n");

  int incorrectFlagSet = sc_regSet (MEMORY_ERROR_MASK, -1);
  printf ("\n\n------ INCORRECT REGISTER SET RESULT: %d ------\n\n",
          incorrectFlagSet);

  sc_accumulatorSet (12);
  printAccumulator ();
  printf ("\n");

  int incorrectAccumulatorSet = sc_accumulatorSet (32939292);
  printf ("\n\n------ INCORRECT ACCUMULATOR SET RESULT: %d ------\n\n",
          incorrectAccumulatorSet);

  sc_icounterSet (2939);
  printCounters ();
  printf ("\n");

  int incorrectCounterSet = sc_icounterSet (32939292);
  printf ("\n\n------ INCORRECT COUNTER SET RESULT: %d ------\n\n",
          incorrectCounterSet);

  int accValue, memoryValue;
  sc_memoryGet (10, &memoryValue);
  sc_accumulatorGet (&accValue);

  printf ("ACCUMULATOR DECODED VALUE:\n");
  printDecodedCommand (accValue);
  printf ("MEMORY RANDOM DECODED VALUE:\n");
  printDecodedCommand (memoryValue);

  int encodedCommand;
  sc_commandEncode (0, 0x34, 12, &encodedCommand);
  printf ("ENCODED COMMAND IN DIFFERENT SYSTEMS:\n");
  printDecodedCommand (encodedCommand);

  return 0;
}
