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
ANALISAMEM_LIB_FOLDER_PATH = ../analisamem/bin/analisamem

EXE = $(BIN)/main

all: build

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/app.cpp -pg -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/app-util.cpp -pg -o $(OBJ)/app-util.o
	$(CC) $(CFLAGS) -c $(SRC)/app-validation.cpp -pg -o $(OBJ)/app-validation.o
	$(CC) $(CFLAGS) -c $(SRC)/shared-util.cpp -pg -o $(OBJ)/shared-util.o
	$(CC) $(CFLAGS) -c $(SRC)/arrangement-list.cpp -pg -o $(OBJ)/arrangement-list.o
	$(CC) $(CFLAGS) -c $(SRC)/arrangement-list-sorting.cpp -pg -o $(OBJ)/arrangement-list-sorting.o
	$(CC) $(CFLAGS) -c $(SRC)/lexicographic-analyser.cpp -pg -o $(OBJ)/lexicographic-analyser.o
	$(CC) $(CFLAGS) -c $(SRC)/lexicographic-util.cpp -pg -o $(OBJ)/lexicographic-util.o
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -pg -o $(OBJ)/memlog.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -pg -o $(BIN)/main
	$(EXE) -i ../data/input.txt -o ../data/output.txt -s 2 -m 4

gprof:
	$(EXE)
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof.txt

memlog:
	$(EXE)
	$(ANALISAMEM_LIB_FOLDER_PATH) -f eps -i $(DATA_FOLDER_PATH)/memory-log.out -p $(DATA_FOLDER_PATH)/memory-log
	
clean:
	rm -f $(EXE) $(OBJ)/*.o gmon.out
