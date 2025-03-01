CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -lpthread
LDFLAGS = 
RM = /bin/rm -f
OBJS = thread_data.o
EXECUTABLE = thread_data

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

threadtest1.o: thread_data.c 
	$(CC) $(CFLAGS) -c thread_data.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
