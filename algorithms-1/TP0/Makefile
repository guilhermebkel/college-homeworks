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
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-test.cpp -pg -o $(OBJ)/quick-sort-test.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-utils.cpp -pg -o $(OBJ)/quick-sort-utils.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-non-recursive.cpp -pg -o $(OBJ)/quick-sort-non-recursive.o
	$(CC) $(CFLAGS) -c $(SRC)/quick-sort-recursive.cpp -pg -o $(OBJ)/quick-sort-recursive.o
	$(CC) $(CFLAGS) -c $(SRC)/fibonacci-test.cpp -pg -o $(OBJ)/fibonacci-test.o
	$(CC) $(CFLAGS) -c $(SRC)/fibonacci-non-recursive.cpp -pg -o $(OBJ)/fibonacci-non-recursive.o
	$(CC) $(CFLAGS) -c $(SRC)/fibonacci-recursive.cpp -pg -o $(OBJ)/fibonacci-recursive.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)

build-tp: clean
	$(CC) $(CFLAGS) -c $(SRC)/tp.cpp -pg -o $(OBJ)/tp.o
	$(CC) $(OBJ)/*.o -pg -o $(EXE) $(LIBS)
	$(EXE)

test:
	$(EXE)

clean:
	rm -f $(EXE) $(OBJ)/*.o
