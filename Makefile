SRC=src
OBJ=obj
BIN=bin

CFLAGS +=-W  -Wall -Wextra -g3 -Iinclude -fsanitize=address
CFLAGS2 +=-W -g3 -Iinclude

CC=gcc
TARGET=$(BIN)/bc
RM=rm -rf

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c 
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(TARGET) $(BIN)/*.dSYM $(OBJ)/*.o 
