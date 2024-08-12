CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: program

program: main.o
	@$(CC) $(CFLAGS) main.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	@rm -rf *.o program

rebuild: clean all