all: matmul matmul_pthread
matmul: matmul.c
	gcc -Wall -O3 -o matmul matmul.c

matmul_pthread: matmul_pthread.c
	gcc -Wall -O3 -o matmul_pthread matmul_pthread.c

clean:
	rm -f matmul matmul_pthread
