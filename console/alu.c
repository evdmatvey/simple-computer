#include "console.h"
#include <math.h>
#include <stdio.h>

int
checkDivByZero (int devider)
{
  if (devider == 0)
    {
      sc_regSet (DIVISION_BY_ZERO_MASK, 1);
      return -1;
    }

  return 0;
}

int
normalizeValue (int value)
{
  if (value > 0x7FFF)
    {
      return value & 0x7FFF;
    }

  if (value < 0)
    {
      int positive = -value;
      int inverted = (~positive) & 0x3FFF;
      return (1 << 14) | (inverted + 1);
    }

  return value;
}

int
checkOverflow (int value)
{
  if (value > 0x7FFF)
    {
      sc_regSet (OVERFLOW_MASK, 1);
      return -1;
    }

  return 0;
}

void
clearIO ()
{
  mt_gotoXY (20, 0);
  printf ("                                                     ");
  fflush (stdout);

  mt_gotoXY (21, 0);
  printf ("                                                     ");
  fflush (stdout);
}

void
ioCpuinfo ()
{
  mt_gotoXY (20, 0);
  mt_setbgcolor (MT_BLACK);
  mt_setfgcolor (MT_WHITE);
  printf ("CPUINFO: ИП-312 Синицын Стаc, Евдокимов Матвей");
  fflush (stdout);
}

void
ioRead (int address)
{
  mt_gotoXY (21, 0);
  mt_setbgcolor (MT_BLACK);
  mt_setfgcolor (MT_WHITE);
  printf ("READ: ");
  fflush (stdout);

  int value = editInPlace (7, 21);
  if (value == 0xFFFF)
    {
      return;
    }

  sc_memorySet (address, value);
  printTerm (address, 1);
}

void
ioWrite (int address)
{
  int value;
  sc_memoryGet (address, &value);

  mt_gotoXY (21, 0);
  mt_setbgcolor (MT_BLACK);
  mt_setfgcolor (MT_WHITE);
  printf ("WRITE: %d", value);
  fflush (stdout);

  printTerm (address, 0);
}

void
accLoad (int address)
{
  int value;
  sc_memoryGet (address, &value);
  sc_accumulatorSet (value);
}

void
accStore (int address)
{
  int value;
  sc_accumulatorGet (&value);
  sc_memorySet (address, value);
}

void
mathAdd (int address)
{
  int value1, value2;
  sc_accumulatorGet (&value1);
  sc_memoryGet (address, &value2);
  value1 = sc_getDecValueOfMemoryData (value1);
  value2 = sc_getDecValueOfMemoryData (value2);

  int sum = value1 + value2;

  if (checkOverflow (sum) != 0)
    {
      sum = normalizeValue (sum);
    }

  sc_accumulatorSet (sum);
}

void
mathSub (int address)
{
  int value1, value2;
  sc_accumulatorGet (&value1);
  sc_memoryGet (address, &value2);
  value1 = sc_getDecValueOfMemoryData (value1);
  value2 = sc_getDecValueOfMemoryData (value2);

  int sub = value1 - value2;
  sub = normalizeValue (sub);

  if (checkOverflow (sub) != 0)
    {
      sub = normalizeValue (sub);
    }

  sc_accumulatorSet (sub);
}

void
mathMul (int address)
{
  int value1, value2;
  sc_accumulatorGet (&value1);
  sc_memoryGet (address, &value2);
  value1 = sc_getDecValueOfMemoryData (value1);
  value2 = sc_getDecValueOfMemoryData (value2);

  int mul = value1 * value2;

  if (checkOverflow (mul) != 0)
    {
      mul = normalizeValue (mul);
    }

  sc_accumulatorSet (mul);
}

void
mathDivide (int address)
{
  int value1, value2;
  sc_accumulatorGet (&value1);
  sc_memoryGet (address, &value2);
  value1 = sc_getDecValueOfMemoryData (value1);
  value2 = sc_getDecValueOfMemoryData (value2);

  if (checkDivByZero (value2) != 0)
    return;

  int div = value1 / value2;

  sc_accumulatorSet (div);
}

int
controlFlowJump (int address)
{
  return address;
}

int
controlFlowJneg (int address)
{
  int value;
  sc_accumulatorGet (&value);

  value = sc_getDecValueOfMemoryData (value);

  if (value < 0)
    return address;

  return -1;
}

int
controlFlowJz (int address)
{
  int value;
  sc_accumulatorGet (&value);

  if (value == 0)
    return address;

  return -1;
}

void
userChl (int address)
{
  int value;
  sc_memoryGet (address, &value);

  int newValue = value << 1;

  if (checkOverflow (newValue) != 0)
    {
      value = normalizeValue (newValue);
    }

  sc_accumulatorSet (newValue);
}

void
userShr (int address)
{
  int value;
  sc_memoryGet (address, &value);

  int newValue = value >> 1;

  if (checkOverflow (newValue) != 0)
    {
      value = normalizeValue (newValue);
    }

  sc_accumulatorSet (newValue);
}

void
controlFlowHalt ()
{
  stopInteractive ();
}

int
ALU (int command, int operand)
{
  clearIO ();
  int icounter;
  sc_icounterGet (&icounter);
  int t = 0;

  switch (command)
    {
    case IO_COMMAND_NOP:
      break;
    case IO_COMMAND_CPUINFO:
      ioCpuinfo ();
      break;
    case IO_COMMAND_READ:
      ioRead (operand);
      break;
    case IO_COMMAND_WRITE:
      ioWrite (operand);
      break;
    case ACC_COMMAND_LOAD:
      accLoad (operand);
      break;
    case ACC_COMMAND_STORE:
      accStore (operand);
      break;
    case MATH_COMMAND_ADD:
      mathAdd (operand);
      break;
    case MATH_COMMAND_SUB:
      mathSub (operand);
      break;
    case MATH_COMMAND_MUL:
      mathMul (operand);
      break;
    case MATH_COMMAND_DIVIDE:
      mathDivide (operand);
      break;
    case CONTROL_FLOW_COMMAND_JUMP:
      icounter = controlFlowJump (operand) - 1;
      break;
    case CONTROL_FLOW_COMMAND_JNEG:
      t = controlFlowJneg (operand);
      if (t != -1)
        icounter = t - 1;
      break;
    case CONTROL_FLOW_COMMAND_JZ:
      t = controlFlowJz (operand);
      if (t != -1)
        icounter = t - 1;
      break;

    case CONTROL_FLOW_COMMAND_HALT:
      controlFlowHalt ();
      icounter -= 1;
      break;

    case USER_COMMAND_CHL:
      userChl (operand);
      break;

    case USER_COMMAND_SHR:
      userShr (operand);
      break;
    }

  int newIcounter = icounter + 1 < 128 ? icounter + 1 : 0;
  sc_icounterSet (newIcounter);

  return 0;
}
