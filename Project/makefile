CC = gcc
LD = gcc
CFLAGS = -Wall -O3# -fopenmp  #-ffast-math -march=native -fopt-info-vec  
LDFLAGS = #-fopenmp
RM = /bin/rm -f
OBJS = sudoku.o
EXECUTABLE = sudoku

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJS): sudoku.c
	$(CC) $(CFLAGS) -c sudoku.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
