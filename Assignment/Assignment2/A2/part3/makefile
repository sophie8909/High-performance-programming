CC = gcc
LD = gcc
CFLAGS = -g -Wall
LDFLAGS = 
RM = /bin/rm -f
TARGET = main
OBJS = $(TARGET).o
SRC = $(TARGET).c
EXE = january

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXE)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS)

clean:
	$(RM) $(EXE) $(OBJS)