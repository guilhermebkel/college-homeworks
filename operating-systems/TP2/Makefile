CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/dense-page-table.o $(OBJ)/hier-2-page-table.o $(OBJ)/hier-3-page-table.o $(OBJ)/inverted-page-table.o $(OBJ)/page-replacement-algorithm.o $(OBJ)/utils.o $(OBJ)/app.o
HDRS = $(INC)/dense-page-table.h $(INC)/hier-2-page-table.h $(INC)/hier-3-page-table.h $(INC)/inverted-page-table.h $(INC)/page-replacement-algorithm.h $(INC)/utils.h $(INC)/app.h
CFLAGS = -pg -Wall -I$(INC) -c

EXE = $(BIN)/simulador

all: clean $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $@ $^ $(LIBS)

$(OBJ)/dense-page-table.o: $(SRC)/dense-page-table.c $(INC)/dense-page-table.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/hier-2-page-table.o: $(SRC)/hier-2-page-table.c $(INC)/hier-2-page-table.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/hier-3-page-table.o: $(SRC)/hier-3-page-table.c $(INC)/hier-3-page-table.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/inverted-page-table.o: $(SRC)/inverted-page-table.c $(INC)/inverted-page-table.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/page-replacement-algorithm.o: $(SRC)/page-replacement-algorithm.c $(INC)/page-replacement-algorithm.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/utils.o: $(SRC)/utils.c $(INC)/utils.h
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ)/app.o: $(SRC)/app.c $(INC)/app.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJS) gmon.out

test1: $(EXE)
	$(EXE) lru ./input/arquivo.log 4 128 densa
	$(EXE) lru ./input/compilador.log 4 128 densa
	$(EXE) lru ./input/compressor.log 4 128 densa
	$(EXE) lru ./input/matriz.log 4 128 densa
	$(EXE) lru ./input/simulador.log 4 128 densa

test2: $(EXE)
	$(EXE) lru ./input/simulador.log 4 128 densa
	$(EXE) lru ./input/simulador.log 4 128 hier2
	$(EXE) lru ./input/simulador.log 4 128 hier3
	$(EXE) lru ./input/simulador.log 4 128 invertida
