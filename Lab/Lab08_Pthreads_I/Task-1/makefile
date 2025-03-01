CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -lpthread
LDFLAGS = 
RM = /bin/rm -f
OBJS = threadtest1.o
EXECUTABLE = threadtest1

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

threadtest1.o: threadtest1.c 
	$(CC) $(CFLAGS) -c threadtest1.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
