#---------------------------------------------------------------------
# File: Makefile
# Content: Compiles the Poker Face application.
# Author: Guilherme Mota Bromonschenkel Lima (guilhermebromonschenkel@gmail.com)
#---------------------------------------------------------------------
# Options: make all - compile everything
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -g -std=c++11 -I$(INC)

EXE = $(BIN)/main

all: main

build:
	$(CC) $(CFLAGS) -c src/app.cpp -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c src/poker-face.cpp -o $(OBJ)/poker-face.o
	$(CC) $(CFLAGS) -c src/arrangement-list.cpp -o $(OBJ)/arrangement-list.o

main: clean build
	$(CC) $(CFLAGS) $(OBJ)/*.o -o $(BIN)/main
	$(EXE)
	
clean:
	rm -f $(EXE) $(OBJ)/*.o
