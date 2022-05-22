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

main: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/poker-face.o: $(HDRS) $(SRC)/poker-face.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker-face.o $(SRC)/poker-face.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS)
