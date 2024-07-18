CC=gcc
CFLAGS=-g

all: program libsource.so

program: main.o
	@$(CC) $(CFLAGS) main.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

libsource.so: source.o
	@$(CC) -shared -o libsource.so source.o -ldl

source.o: source.c header.h
	@$(CC) $(CFLAGS) -c -fPIC source.c -o source.o

clean:
	@rm -rf *.o *.so program

rebuild: clean all