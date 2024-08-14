CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: server client

server: server.o
	@$(CC) $(CFLAGS) server.o -o server

client: client.o
	@$(CC) $(CFLAGS) client.o -o client

server.o: server.c
	@$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	@$(CC) $(CFLAGS) -c client.c -o client.o

clean:
	@rm -rf *.o server client

rebuild: clean all