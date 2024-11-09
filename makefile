CC=clang
CFLAGS=-g -Wall -std=c23
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=bin/main
BINDIR=bin

all:$(BIN)

release: CFLAGS=-Wall -02 -DNDEBUG
release: clean
release: $(BIN)

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o bin/main

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BINDIR)/* $(OBJ)/*


