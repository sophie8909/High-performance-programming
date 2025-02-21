CC = gcc
LD = gcc
CFLAGS = -g -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS = matmul.o
SRC = matmul.c
EXECUTABLE = matmul
all:$(EXECUTABLE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXE)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS)

clean:
	$(RM) $(EXECUTABLE) $(OBJS)