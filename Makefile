SRC=src
OBJ=obj
BIN=bin

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude -fsanitize=address
CC=gcc
TARGET=$(BIN)/my_bc
RM=rm -rf

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS} -c $< -o $@

$(OBJ):
	mkdir $@

$(BIN):
	mkdir $@

clean:
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)/*.o 
