CC = gcc
LD = gcc
CFLAGS = -g -Wall -Werror -O3
LDFLAGS = 
RM = /bin/rm -f

all: array_loop loop_invariants string_loop

array_loop: array_loop.o
	$(LD) $(LDFLAGS) array_loop.o -o array_loop

array_loop.o: array_loop.c
	$(CC) $(CFLAGS) -c array_loop.c

loop_invariants: loop_invariants.o
	$(LD) $(LDFLAGS) loop_invariants.o -o loop_invariants

loop_invariants.o: loop_invariants.c
	$(CC) $(CFLAGS) -c loop_invariants.c

string_loop: string_loop.o
	$(LD) $(LDFLAGS) string_loop.o -o string_loop

string_loop.o: string_loop.c
	$(CC) $(CFLAGS) -c string_loop.c

clean:
	$(RM)  *.o array_loop loop_invariants string_loop
