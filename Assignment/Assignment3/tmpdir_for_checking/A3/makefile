CC = gcc
LD = gcc
CFLAGS = -O3 -ffast-math -march=native -fopt-info-vec -Wall
LDFLAGS = 
RM = /bin/rm -f
OBJS = galsim.o
EXECUTABLE = galsim

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE) -lm

$(OBJS): galsim.c
	$(CC) $(CFLAGS) -c galsim.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
