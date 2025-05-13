#ifndef MY_SIMPLE_COMPUTER_H

#define OVERFLOW_MASK (1 << 0)         // 00001
#define DIVISION_BY_ZERO_MASK (1 << 1) // 00010
#define MEMORY_ERROR_MASK (1 << 2)     // 00100
#define IGNORE_CLOCK_MASK (1 << 3)     // 01000
#define INVALID_COMMAND_MASK (1 << 4)  // 10000

#define SIGN_MASK 0x4000
#define COMMAND_MASK 0x3F80
#define OPERAND_MASK 0x007F

typedef struct Node
{
  int key;
  int *value;
  int value_size;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct
{
  Node *head;
  Node *tail;
  int size;
  int capacity;
  Node *hash[13];
} LRUCache;

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memoryGet2 (int address, int *value);
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

LRUCache *lru_cache_create (int capacity);
int *lru_cache_get (LRUCache *cache, int key, int *value_size);
void lru_cache_put (LRUCache *cache, int key, int *value, int value_size);
void lru_cache_free (LRUCache *cache);

int getStep ();
void incrementStep (int type);
void resetStep ();

void sc_cacheInit (LRUCache *newCache);
void sc_cachePut (int address);
int sc_cacheGet (int address);
void sc_cacheClear ();
LRUCache *sc_cacheGetCache ();

#define IO_COMMAND_NOP 0x00
#define IO_COMMAND_CPUINFO 0x01
#define IO_COMMAND_READ 0x0A
#define IO_COMMAND_WRITE 0x0B
#define ACC_COMMAND_LOAD 0x14
#define ACC_COMMAND_STORE 0x15
#define MATH_COMMAND_ADD 0x1E
#define MATH_COMMAND_SUB 0x1F
#define MATH_COMMAND_DIVIDE 0x20
#define MATH_COMMAND_MUL 0x21
#define CONTROL_FLOW_COMMAND_JUMP 0x28
#define CONTROL_FLOW_COMMAND_JNEG 0x29
#define CONTROL_FLOW_COMMAND_JZ 0x2A
#define CONTROL_FLOW_COMMAND_HALT 0x2B
#define USER_COMMAND_NOT 0x33
#define USER_COMMAND_AND 0x34
#define USER_COMMAND_OR 0x35
#define USER_COMMAND_XOR 0x36
#define USER_COMMAND_JNS 0x37
#define USER_COMMAND_JC 0x38
#define USER_COMMAND_JNC 0x39
#define USER_COMMAND_JP 0x3A
#define USER_COMMAND_JNP 0x3B
#define USER_COMMAND_CHL 0x3C
#define USER_COMMAND_SHR 0x3D
#define USER_COMMAND_RCL 0x3E
#define USER_COMMAND_RCR 0x3F
#define USER_COMMAND_NEG 0x40
#define USER_COMMAND_ADDC 0x41
#define USER_COMMAND_SUBC 0x42
#define USER_COMMAND_LOGLC 0x43
#define USER_COMMAND_LOGRC 0x44
#define USER_COMMAND_RCCL 0x45
#define USER_COMMAND_RCCR 0x46
#define USER_COMMAND_MOVA 0x47
#define USER_COMMAND_MOVR 0x48
#define USER_COMMAND_MOVCA 0x49
#define USER_COMMAND_MOVCR 0x4A

#endif // !MY_SIMPLE_COMPUTER_H
