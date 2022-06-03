#---------------------------------------------------------------------
# File: Makefile
# Content: Compiles the Poker Face application.
# Author: Guilherme Mota Bromonschenkel Lima (guilhermebromonschenkel@gmail.com)
#---------------------------------------------------------------------
# Options: make all - compile everything
#---------------------------------------------------------------------

CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -g -std=c++11 -I $(INC)

EXE = $(BIN)/main

all: main

build:
	$(CC) $(CFLAGS) -c $(SRC)/app.cpp -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face.cpp -o $(OBJ)/poker-face.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face-util.cpp -o $(OBJ)/poker-face-util.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face-validation.cpp -o $(OBJ)/poker-face-validation.o
	$(CC) $(CFLAGS) -c $(SRC)/arrangement-list.cpp -o $(OBJ)/arrangement-list.o
	$(CC) $(CFLAGS) -c $(SRC)/shared-util.cpp -o $(OBJ)/shared-util.o
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -o $(OBJ)/memlog.o

main: clean build
	$(CC) $(CFLAGS) $(OBJ)/*.o -o $(BIN)/main
	$(EXE)
	
clean:
	rm -f $(EXE) $(OBJ)/*.o
