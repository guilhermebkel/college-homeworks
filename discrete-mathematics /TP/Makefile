CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -Wall -c -I $(INC)

EXE = $(BIN)/main

all: build test

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/app.c -pg -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/fractal.c -pg -o $(OBJ)/fractal.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

test:
	$(EXE)

clean:
	rm -f $(EXE) $(OBJ)/*.o
