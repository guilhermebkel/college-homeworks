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

all: build gprof memlog

build: clean
	$(CC) $(CFLAGS) -c $(SRC)/app.cpp -pg -o $(OBJ)/app.o
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -pg -o $(OBJ)/memlog.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -pg -o $(BIN)/main
	$(EXE)

gprof:
	$(EXE)
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof.txt

memlog:
	$(EXE)
	$(ANALISAMEM_LIB_FOLDER_PATH) -f eps -i $(DATA_FOLDER_PATH)/memory-log.out -p $(DATA_FOLDER_PATH)/memory-log
	
clean:
	rm -f $(EXE) $(OBJ)/*.o gmon.out
