CC = gcc
CFLAGS = -g -Wall -Werror
RM = /bin/rm -f

# 定義最佳化級別
OPT_LEVELS = O1

# 定義要編譯的目標
TARGETS = lookup memset strength_reduction timings

# 自動生成所有優化級別的目標
all: $(foreach opt, $(OPT_LEVELS), $(foreach tgt, $(TARGETS), $(tgt)_$(opt)))

# 通用規則來編譯每個目標的不同優化版本
%_O1: %.c
	$(CC) $(CFLAGS) -O1 -o $@ $<

%_O2: %.c
	$(CC) $(CFLAGS) -O2 -o $@ $<

%_O3: %.c
	$(CC) $(CFLAGS) -O3 -o $@ $<

math_functions: math_functions.c
	gcc -g -Wall -Werror -O1 -o math_functions math_functions.c -lm

clean:
	$(RM) *.o $(foreach opt, $(OPT_LEVELS), $(foreach tgt, $(TARGETS), $(tgt)_$(opt)))