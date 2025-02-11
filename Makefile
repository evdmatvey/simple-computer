CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: console/test.a run

run:
	console/test.a

clean:
	rm console/test.o
	rm console/test.a

console/test.a: console/test.o
	$(CC) $(CFLAGS) -o $@ $<

console/test.o: console/test.c
	$(CC) -c $(CFLAGS) -o $@ $<
