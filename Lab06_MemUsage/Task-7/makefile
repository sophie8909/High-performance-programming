CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS = matmul.o 
EXECUTABLE = matmul

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

# func.o: func.h func.c
# 	$(CC) $(CFLAGS) -c func.c	

main.o: matmul.c
	$(CC) $(CFLAGS) -c matmul.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
