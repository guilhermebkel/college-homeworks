#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Guilherme Mota Bromonschenkel Lima (guilhermebromonschenkel@gmail.com)
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
CFLAGS = -g -O3 -std=c++11 -I$(INC) -I third_party/ -I src/

EXE = $(BIN)/main

all: main

build:
	$(CC) $(CFLAGS) -c src/poker-face-app.cpp -o $(OBJ)/poker-face-app.o
	$(CC) $(CFLAGS) -c src/poker-face.cpp -o $(OBJ)/poker-face.o

main: clean build
	$(CC) $(CFLAGS) $(OBJ)/*.o -o $(BIN)/main
	$(EXE)
	
clean:
	rm -f $(EXE) $(OBJ)/*.o
