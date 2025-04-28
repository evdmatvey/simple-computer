#ifndef MY_SIMPLE_COMPUTER_H

#define OVERFLOW_MASK (1 << 0)         // 00001
#define DIVISION_BY_ZERO_MASK (1 << 1) // 00010
#define MEMORY_ERROR_MASK (1 << 2)     // 00100
#define IGNORE_CLOCK_MASK (1 << 3)     // 01000
#define INVALID_COMMAND_MASK (1 << 4)  // 10000

#define SIGN_MASK 0x4000
#define COMMAND_MASK 0x3F80
#define OPERAND_MASK 0x007F

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);

int sc_regInit (void);
int sc_regSet (int flag, int value);
int sc_regGet (int flag, int *value);

int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

int sc_commandValidate (int command);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_getDecValueOfMemoryData (const int value);

#endif // !MY_SIMPLE_COMPUTER_H
