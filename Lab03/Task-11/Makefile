# 定義變數
CC = gcc
TARGET = bubble_sort
SRC = $(TARGET).c
OBJ = $(TARGET).o

# 目標規則
all: $(TARGET)

$(OBJ): $(SRC)
	$(CC) -c $(SRC)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
