CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lrt

all: first second

first: first.o source.o
	@$(CC) $(CFLAGS) $(LDFLAGS) first.o source.o -o first

first.o: first.c
	@$(CC) $(CFLAGS) -c first.c -o first.o

second: second.o source.o
	@$(CC) $(CFLAGS) $(LDFLAGS) second.o source.o -o second

second.o: second.c
	@$(CC) $(CFLAGS) -c second.c -o second.o

source.o: source.c header.h
	@$(CC) $(CFLAGS) -c source.c -o source.o

clean:
	@rm -rf *.o first second

rebuild: clean all