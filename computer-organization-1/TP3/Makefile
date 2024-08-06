CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -Wall -c -I $(INC)

EXE = $(BIN)/main

all: build test

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/tp.cpp -pg -o $(OBJ)/tp.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

clean:
	rm -f $(EXE) $(OBJ)/*.o

test: $(EXE)
	$(EXE) 4096 1024 4 ./input/cache1.txt
