CC := gcc
CFLAGS := -Wall -Werror -g

CFILES := netsock.c  
HEADERS := netsock.h netdir.h

all: netserver


netserver: netserver.c $(CFILES) $(HEADERS)
	$(CC) $(CFLAGS) -o netserver netserver.c $(CFILES)

clean:
	rm netserver
