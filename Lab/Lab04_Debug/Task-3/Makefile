# 定義變數
CC = gcc
LD = gcc
CFLAGS = -g -Wall
LDFLAGS =
TARGET = ex2
SRC = $(TARGET).c
OBJ = $(TARGET).o

# 目標規則
all: $(TARGET)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
