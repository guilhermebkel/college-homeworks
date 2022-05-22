#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Guilherme Mota Bromonschenkel Lima (guilhermebromonschenkel@gmail.com)
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/poker-face.o $(OBJ)/memlog.o
HDRS = $(INC)/poker-face.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/main

all: main

build:
	$(CC) $(CFLAGS) -c src/main.cpp -o $(BIN)/main
	$(CC) $(CFLAGS) -c src/poker-face.cpp -o $(BIN)/poker-face

main: build
	$(CC) $(CFLAGS) $(BIN)/* -o main
	$(EXE)
	
clean:
	rm -f $(EXE) $(OBJS)
