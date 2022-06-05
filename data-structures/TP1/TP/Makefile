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
DATA_FOLDER_PATH = ../data

EXE = $(BIN)/main

all: build gprof

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/app.cpp -pg -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face.cpp -pg -o $(OBJ)/poker-face.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face-util.cpp -pg -o $(OBJ)/poker-face-util.o
	$(CC) $(CFLAGS) -c $(SRC)/poker-face-validation.cpp -pg -o $(OBJ)/poker-face-validation.o
	$(CC) $(CFLAGS) -c $(SRC)/arrangement-list.cpp -pg -o $(OBJ)/arrangement-list.o
	$(CC) $(CFLAGS) -c $(SRC)/shared-util.cpp -pg -o $(OBJ)/shared-util.o
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -pg -o $(OBJ)/memlog.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -pg -o $(BIN)/main
	$(EXE)

gprof:
	$(EXE)
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof.txt
	
clean:
	rm -f $(EXE) $(OBJ)/*.o gmon.out
