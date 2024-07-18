CC=gcc
CFLAGS=-g

all: libsource.so task

task: main.o
	@$(CC) $(CFLAGS) main.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

libsource.so: source.o
	@$(CC) -shared -o libsource.so source.o

source.o: source.c header.h
	@$(CC) $(CFLAGS) -c -fPIC source.c -o source.o

clean:
	@rm -rf *.o *.so program

rebuild:
	clean all