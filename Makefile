CC := gcc
CFLAGS := -Wall -Werror -g

HEADERS := netdir.h

NETHEADER := netsock.h
NETFILES := netsock.c  

all: netserver netclient


netserver: netserver.c $(HEADERS)
	$(CC) $(CFLAGS) -o netserver netserver.c

netclient: netclient.c $(NETHEADER) $(NETFILES)
	$(CC) $(CFLAGS) -o netclient netclient.c $(NETFILES)
clean:
	rm netserver netclient
