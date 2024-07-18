CC=gcc
CFLAGS=-Wall -g

all: program libsum.so libsub.so libmult.so libmin.so libmax.so libdivide.so

program: main.o
	@$(CC) $(CFLAGS) main.o -o program

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c -o main.o

libmin.so: min.o
	@$(CC) -shared -o libmin.so min.o -ldl

libmax.so: max.o
	@$(CC) -shared -o libmax.so max.o -ldl

libdivide.so: divide.o
	@$(CC) -shared -o libdivide.so divide.o -ldl

libmult.so: mult.o
	@$(CC) -shared -o libmult.so mult.o -ldl

libsub.so: sub.o
	@$(CC) -shared -o libsub.so sub.o -ldl

libsum.so: sum.o
	@$(CC) -shared -o libsum.so sum.o -ldl

min.o: min.c
	@$(CC) $(CFLAGS) -fPIC -c min.c -o min.o

max.o: max.c
	@$(CC) $(CFLAGS) -fPIC -c max.c -o max.o

divide.o: divide.c
	@$(CC) $(CFLAGS) -fPIC -c divide.c -o divide.o

mult.o: mult.c
	@$(CC) $(CFLAGS) -fPIC -c mult.c -o mult.o

sub.o: sub.c
	@$(CC) $(CFLAGS) -fPIC -c sub.c -o sub.o

sum.o: sum.c
	@$(CC) $(CFLAGS) -fPIC -c sum.c -o sum.o

clean:
	@rm -rf *.o *.so program

rebuild: clean all