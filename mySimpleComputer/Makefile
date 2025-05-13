CC = gcc
CFLAGS = -Wall -Wextra 

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIB = libmysimplecomputer.a

all: $(LIB) clean 

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

.PHONY: all 
