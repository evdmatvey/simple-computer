CC = gcc
CFLAGS = -Wall -Wextra 

SRC = $(wildcard *.c)
MAIN = pr01.c

OBJ_SRC = $(SRC:.c=.o)
OBJ_MAIN = $(MAIN:.c=.o)

LIB = ../mySimpleComputer/libmysimplecomputer.a
EXEC = pr01

all: $(EXEC) 

$(EXEC): $(OBJ_SRC) $(OBJ_MAIN) 
 $(CC) $(CFLAGS) -o $@ $^ -L../mySimpleComputer -lmysimplecomputer

%.o: %.c
 $(CC) $(CFLAGS) -c $< -o $@

clean:
 rm -f $(OBJ) $(OBJ_MAIN) $(EXEC)

.PHONY: all clean
