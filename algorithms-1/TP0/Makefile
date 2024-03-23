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
	$(CC) $(CFLAGS) -c $(SRC)/app.cpp -pg -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-utils.cpp -pg -o $(OBJ)/quick-sort-utils.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-recursive.cpp -pg -o $(OBJ)/quick-sort-recursive.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-non-recursive.cpp -pg -o $(OBJ)/quick-sort-non-recursive.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

test:
	$(EXE)

clean:
	rm -f $(EXE) $(OBJ)/*.o
