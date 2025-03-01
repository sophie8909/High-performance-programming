CC = gcc
LD = gcc
CFLAGS = -Wall -lpthread
LDFLAGS = 
RM = /bin/rm -f
OBJS = threaded_computation.o
EXECUTABLE = threaded_computation

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

threaded_computation.o: threaded_computation.c 
	$(CC) $(CFLAGS) -c threaded_computation.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
