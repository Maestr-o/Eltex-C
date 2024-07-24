CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: program sum mult max strcat

program: main.o
	@$(CC) $(CFLAGS) main.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

sum: sum.o
	@$(CC) $(CFLAGS) sum.o -o sum

sum.o: sum.c
	@$(CC) $(CFLAGS) -c sum.c -o sum.o

mult: mult.o
	@$(CC) $(CFLAGS) mult.o -o mult

mult.o: mult.c
	@$(CC) $(CFLAGS) -c mult.c -o mult.o

max: max.o
	@$(CC) $(CFLAGS) max.o -o max

max.o: max.c
	@$(CC) $(CFLAGS) -c max.c -o max.o

strcat: strcat.o
	@$(CC) $(CFLAGS) strcat.o -o strcat

strcat.o: strcat.c
	@$(CC) $(CFLAGS) -c strcat.c -o strcat.o

clean:
	@rm -rf *.o program max sum mult strcat

rebuild: clean all