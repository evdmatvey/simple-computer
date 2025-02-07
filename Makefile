CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: console/test

console/test: console/test.o
	$(CC) $(CFLAGS) -o $@ $<

console/test.o: console/test.c
	$(CC) -c $(CFLAGS) -o $@ $<
