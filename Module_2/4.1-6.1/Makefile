CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

all: task

task: main.o source.o
	@$(CC) $(CFLAGS) main.o source.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

source.o: source.c header.h
	@$(CC) $(CFLAGS) -c source.c -o source.o

clean:
	rm -rf *.o program

rebuild:
	clean all