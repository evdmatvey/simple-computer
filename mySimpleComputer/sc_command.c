#include "sc.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if ((value & ~0xFFFF) != 0)
    {
      return -1;
    }

  if (sign == NULL || command == NULL || operand == NULL)
    {
      return -1;
    }

  *sign = (value & SIGN_MASK) >> 14;
  *command = (value & COMMAND_MASK) >> 7;
  *operand = value & OPERAND_MASK;

  if (sc_commandValidate (*command) == -1)
    {
      return -1;
    }

  return 0;
}

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign != 0 && sign != 1)
    {
      return -1;
    }

  if (sc_commandValidate (command) != 0)
    {
      return -1;
    }

  if (operand < 0 || operand > OPERAND_MASK)
    {
      return -1;
    }

  if (value == NULL)
    {
      return -1;
    }

  *value = (sign << 14) | (command << 7) | operand;

  return 0;
}

int
sc_commandValidate (int command)
{
  switch (command)
    {
    case IO_COMMAND_NOP:
    case IO_COMMAND_CPUINFO:
    case IO_COMMAND_READ:
    case IO_COMMAND_WRITE:
    case ACC_COMMAND_LOAD:
    case ACC_COMMAND_STORE:
    case MATH_COMMAND_ADD:
    case MATH_COMMAND_SUB:
    case MATH_COMMAND_DIVIDE:
    case MATH_COMMAND_MUL:
    case CONTROL_FLOW_COMMAND_JUMP:
    case CONTROL_FLOW_COMMAND_JNEG:
    case CONTROL_FLOW_COMMAND_JZ:
    case CONTROL_FLOW_COMMAND_HALT:
    case USER_COMMAND_NOT:
    case USER_COMMAND_AND:
    case USER_COMMAND_OR:
    case USER_COMMAND_XOR:
    case USER_COMMAND_JNS:
    case USER_COMMAND_JC:
    case USER_COMMAND_JNC:
    case USER_COMMAND_JP:
    case USER_COMMAND_JNP:
    case USER_COMMAND_CHL:
    case USER_COMMAND_SHR:
    case USER_COMMAND_RCL:
    case USER_COMMAND_RCR:
    case USER_COMMAND_NEG:
    case USER_COMMAND_ADDC:
    case USER_COMMAND_SUBC:
    case USER_COMMAND_LOGLC:
    case USER_COMMAND_LOGRC:
    case USER_COMMAND_RCCL:
    case USER_COMMAND_RCCR:
    case USER_COMMAND_MOVA:
    case USER_COMMAND_MOVR:
    case USER_COMMAND_MOVCA:
    case USER_COMMAND_MOVCR:
      return 0;
    default:
      return -1;
    }
}
