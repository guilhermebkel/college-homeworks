#---------------------------------------------------------------------
# File: Makefile
# Content: Compiles the Mailer application.
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
	$(CC) $(CFLAGS) -c $(SRC)/app-util.cpp -pg -o $(OBJ)/app-util.o
	$(CC) $(CFLAGS) -c $(SRC)/app-validation.cpp -pg -o $(OBJ)/app-validation.o
	$(CC) $(CFLAGS) -c $(SRC)/shared-util.cpp -pg -o $(OBJ)/shared-util.o
	$(CC) $(CFLAGS) -c $(SRC)/binary-tree.cpp -pg -o $(OBJ)/binary-tree.o
	$(CC) $(CFLAGS) -c $(SRC)/binary-tree-validation.cpp -pg -o $(OBJ)/binary-tree-validation.o
	$(CC) $(CFLAGS) -c $(SRC)/hash-table.cpp -pg -o $(OBJ)/hash-table.o
	$(CC) $(CFLAGS) -c $(SRC)/message.cpp -pg -o $(OBJ)/message.o
	$(CC) $(CFLAGS) -c $(SRC)/mailer.cpp -pg -o $(OBJ)/mailer.o
	$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -pg -o $(OBJ)/memlog.o
	$(CC) $(CFLAGS) $(OBJ)/*.o -pg -o $(BIN)/main

test:
	$(EXE) -i $(DATA_FOLDER_PATH)/tests/input/entrada_1.txt -o $(DATA_FOLDER_PATH)/output.txt

gprof:
	$(EXE) -i $(DATA_FOLDER_PATH)/gprof/input/input-1000.txt -o $(DATA_FOLDER_PATH)/gprof/output/output-1000.txt
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof/output/gprof-1000.out
	$(EXE) -i $(DATA_FOLDER_PATH)/gprof/input/input-2000.txt -o $(DATA_FOLDER_PATH)/gprof/output/output-2000.txt
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof/output/gprof-2000.out
	$(EXE) -i $(DATA_FOLDER_PATH)/gprof/input/input-3000.txt -o $(DATA_FOLDER_PATH)/gprof/output/output-3000.txt
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof/output/gprof-3000.out
	$(EXE) -i $(DATA_FOLDER_PATH)/gprof/input/input-4000.txt -o $(DATA_FOLDER_PATH)/gprof/output/output-4000.txt
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof/output/gprof-4000.out
	$(EXE) -i $(DATA_FOLDER_PATH)/gprof/input/input-5000.txt -o $(DATA_FOLDER_PATH)/gprof/output/output-5000.txt
	gprof $(EXE) gmon.out > $(DATA_FOLDER_PATH)/gprof/output/gprof-5000.out

memlog:
	$(EXE) -i $(DATA_FOLDER_PATH)/memlog/input/input.txt -o $(DATA_FOLDER_PATH)/memlog/output/output.txt
	$(ANALISAMEM_LIB_FOLDER_PATH) -f eps -i $(DATA_FOLDER_PATH)/memlog/output/log.out -p $(DATA_FOLDER_PATH)/memlog/output

memlog-gnuplot:
	gnuplot $(DATA_FOLDER_PATH)/memlog/*.gp
	
clean:
	rm -f $(EXE) $(OBJ)/*.o gmon.out
