#include "console.h"

void
printDecodedCommand (int value)
{
  printf ("dec: %05d | oct: %05o | hex: %04X | bin: %015b\n", value, value,
          value, value);
}
