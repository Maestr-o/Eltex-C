CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: first second

first: first.o source.o
	@$(CC) $(CFLAGS) first.o source.o -o first

second: second.o source.o
	@$(CC) $(CFLAGS) second.o source.o -o second

first.o: first.c
	@$(CC) $(CFLAGS) -c first.c -o first.o

second.o: second.c
	@$(CC) $(CFLAGS) -c second.c -o second.o

source.o: source.c
	@$(CC) $(CFLAGS) -c source.c -o source.o

clean:
	@rm -rf *.o first second

rebuild: clean all