CC := gcc
CFLAGS := -Wall -Werror -g

HEADERS := netdir.h

NETHEADER := netsock.h
NETFILES := netsock.c  

all: netserver


netserver: netserver.c $(HEADERS)
	$(CC) $(CFLAGS) -o netserver netserver.c

clean:
	rm netserver
