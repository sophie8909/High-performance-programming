CC = gcc
LD = gcc
CFLAGS = -Wall -O3 -fopenmp  #-ffast-math -march=native -fopt-info-vec  
RM = /bin/rm -f
EXECUTABLE = normal_parallel bitmask_parallel bitmask normal

all:$(EXECUTABLE)

normal_parallel: normal_parallel.c
	$(CC) $(CFLAGS) -o normal_parallel normal_parallel.c

bitmask_parallel: bitmask_parallel.c
	$(CC) $(CFLAGS) -o bitmask_parallel bitmask_parallel.c

bitmask: bitmask.c
	$(CC) $(CFLAGS) -o bitmask bitmask.c

normal: normal.c
	$(CC) $(CFLAGS) -o normal normal.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
