
CC = gcc
CFLAGS = -Wall -Wextra 

SRC = $(wildcard *.c)
MAIN = console.c

OBJ_SRC = $(SRC:.c=.o)
OBJ_MAIN = $(MAIN:.c=.o)

EXEC = console.a

all: $(EXEC) 

$(EXEC): $(OBJ_SRC) $(OBJ_MAIN) 
	$(CC) $(CFLAGS) -o $@ $^ -L../mySimpleComputer -lmysimplecomputer -L../myTerm -lmyterm -L../myBigChars -lmybigchars

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SRC) $(OBJ_MAIN) $(EXEC)

.PHONY: all clean

