CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -Wall -c -I $(INC)

EXE = $(BIN)/main

all: build

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/tp.cpp -pg -o $(OBJ)/tp.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)
	$(EXE)

clean:
	rm -f $(EXE) $(OBJ)/*.o
