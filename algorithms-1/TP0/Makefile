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
	$(CC) $(CFLAGS) -c $(SRC)/recursive-quick-sort.cpp -pg -o $(OBJ)/recursive-quick-sort.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

test:
	$(EXE)

clean:
	rm -f $(EXE) $(OBJ)/*.o
