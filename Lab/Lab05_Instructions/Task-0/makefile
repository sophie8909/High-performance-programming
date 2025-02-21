CC = gcc
LD = gcc
CFLAGS = -g -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f

all: mallocycode regularcode sleepycode threadedcode

mallocycode: mallocycode.o
	$(LD) $(LDFLAGS) mallocycode.o -o mallocycode

mallocycode.o: mallocycode.c
	$(CC) $(CFLAGS) -c mallocycode.c

regularcode: regularcode.o
	$(LD) $(LDFLAGS) regularcode.o -o regularcode

regularcode.o: regularcode.c
	$(CC) $(CFLAGS) -c regularcode.c

sleepycode: sleepycode.o
	$(LD) $(LDFLAGS) sleepycode.o -o sleepycode

sleepycode.o: sleepycode.c
	$(CC) $(CFLAGS) -c sleepycode.c

threadedcode: threadedcode.o
	$(LD) $(LDFLAGS) threadedcode.o -o threadedcode

threadedcode.o: threadedcode.c
	$(CC) $(CFLAGS) -lpthread -c threadedcode.c

clean:
	$(RM) mallocycode regularcode sleepycode threadedcode *.o
