CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: program

program: main.o sem.o
	@$(CC) $(CFLAGS) main.o sem.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

sem.o: sem.c
	@$(CC) $(CFLAGS) -c sem.c -o sem.o

clean:
	@rm -rf *.o program

rebuild: clean all