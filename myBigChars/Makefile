CC = gcc
CFLAGS = -Wall -Wextra 

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIB = libmybigchars.a

all: $(LIB) clean 

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

.PHONY: all 
