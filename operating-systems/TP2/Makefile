CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -Wall -c -I $(INC)

EXE = $(BIN)/simulador

all: build

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/tp.c -pg -o $(OBJ)/tp.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

clean:
	rm -f $(EXE) $(OBJ)/*.o

test: $(EXE)
	$(EXE) lru ./input/arquivo.log 4 128
