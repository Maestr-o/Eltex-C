CC=gcc
CFLAGS=-Wall -Wextra -Werror

obj-m += netserver.o

all: netserver netclient

netserver:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

netclient: netclient.c
	$(CC) $(CFLAGS) netclient.c -o netclient

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm netclient