CC = gcc
LD = gcc
CFLAGS = -Wall -lpthread 
LDFLAGS = 
RM = /bin/rm -f
TARGET = mutextest
OBJS = $(TARGET).o
EXECUTABLE = $(TARGET)

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

$(TARGET).o: $(TARGET).c 
	$(CC) $(CFLAGS) -c $(TARGET).c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
