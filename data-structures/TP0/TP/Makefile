#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)

ANALISAMEM = ../analisamem/bin/analisamem

INPUT_BASE_PATH = ../input
MEM_OUTPUT_BASE_PATH = /tmp
PERF_OUTPUT_BASE_PATH = /tmp
GPROF_OUTPUT_BASE_PATH = /tmp

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE)
	$(EXE) -s -p $(MEM_OUTPUT_BASE_PATH)/somalog.out -l -1 $(INPUT_BASE_PATH)/m1.txt -2 $(INPUT_BASE_PATH)/m2.txt -o $(MEM_OUTPUT_BASE_PATH)/soma-result.txt
	$(ANALISAMEM) -f eps -i $(MEM_OUTPUT_BASE_PATH)/somalog.out -p $(MEM_OUTPUT_BASE_PATH)/somadin
	$(EXE) -m -p $(MEM_OUTPUT_BASE_PATH)/multlog.out -l -1 $(INPUT_BASE_PATH)/m1.txt -2 $(INPUT_BASE_PATH)/m2.txt -o $(MEM_OUTPUT_BASE_PATH)/multiplicacao-result.txt
	$(ANALISAMEM) -f eps -i $(MEM_OUTPUT_BASE_PATH)/multlog.out -p $(MEM_OUTPUT_BASE_PATH)/multdin
	$(EXE) -t -p $(MEM_OUTPUT_BASE_PATH)/transplog.out -l -1 $(INPUT_BASE_PATH)/m1.txt -o $(MEM_OUTPUT_BASE_PATH)/transposicao-result.txt
	$(ANALISAMEM) -f eps -i $(MEM_OUTPUT_BASE_PATH)/transplog.out -p $(MEM_OUTPUT_BASE_PATH)/transpdin

perf: $(EXE)
	$(EXE) -s -p $(PERF_OUTPUT_BASE_PATH)/soma100.out -1 $(INPUT_BASE_PATH)/100m1.txt -2 $(INPUT_BASE_PATH)/100m2.txt -o $(PERF_OUTPUT_BASE_PATH)/soma100-result.txt
	$(EXE) -m -p $(PERF_OUTPUT_BASE_PATH)/mult100.out -1 $(INPUT_BASE_PATH)/100m1.txt -2 $(INPUT_BASE_PATH)/100m2.txt -o $(PERF_OUTPUT_BASE_PATH)/mult100-result.txt
	$(EXE) -t -p $(PERF_OUTPUT_BASE_PATH)/transp100.out -1 $(INPUT_BASE_PATH)/100m1.txt -o $(PERF_OUTPUT_BASE_PATH)/transp100-result.txt
	$(EXE) -s -p $(PERF_OUTPUT_BASE_PATH)/soma200.out -1 $(INPUT_BASE_PATH)/200m1.txt -2 $(INPUT_BASE_PATH)/200m2.txt -o $(PERF_OUTPUT_BASE_PATH)/soma200-result.txt
	$(EXE) -m -p $(PERF_OUTPUT_BASE_PATH)/mult200.out -1 $(INPUT_BASE_PATH)/200m1.txt -2 $(INPUT_BASE_PATH)/200m2.txt -o $(PERF_OUTPUT_BASE_PATH)/mult200-result.txt
	$(EXE) -t -p $(PERF_OUTPUT_BASE_PATH)/transp200.out -1 $(INPUT_BASE_PATH)/200m1.txt -o $(PERF_OUTPUT_BASE_PATH)/transp200-result.txt
	$(EXE) -s -p $(PERF_OUTPUT_BASE_PATH)/soma300.out -1 $(INPUT_BASE_PATH)/300m1.txt -2 $(INPUT_BASE_PATH)/300m2.txt -o $(PERF_OUTPUT_BASE_PATH)/soma300-result.txt
	$(EXE) -m -p $(PERF_OUTPUT_BASE_PATH)/mult300.out -1 $(INPUT_BASE_PATH)/300m1.txt -2 $(INPUT_BASE_PATH)/300m2.txt -o $(PERF_OUTPUT_BASE_PATH)/mult300-result.txt
	$(EXE) -t -p $(PERF_OUTPUT_BASE_PATH)/transp300.out -1 $(INPUT_BASE_PATH)/300m1.txt -o $(PERF_OUTPUT_BASE_PATH)/transp300-result.txt
	$(EXE) -s -p $(PERF_OUTPUT_BASE_PATH)/soma400.out -1 $(INPUT_BASE_PATH)/400m1.txt -2 $(INPUT_BASE_PATH)/400m2.txt -o $(PERF_OUTPUT_BASE_PATH)/soma400-result.txt
	$(EXE) -m -p $(PERF_OUTPUT_BASE_PATH)/mult400.out -1 $(INPUT_BASE_PATH)/400m1.txt -2 $(INPUT_BASE_PATH)/400m2.txt -o $(PERF_OUTPUT_BASE_PATH)/mult400-result.txt
	$(EXE) -t -p $(PERF_OUTPUT_BASE_PATH)/transp400.out -1 $(INPUT_BASE_PATH)/400m1.txt -o $(PERF_OUTPUT_BASE_PATH)/transp400-result.txt
	$(EXE) -s -p $(PERF_OUTPUT_BASE_PATH)/soma500.out -1 $(INPUT_BASE_PATH)/500m1.txt -2 $(INPUT_BASE_PATH)/500m2.txt -o $(PERF_OUTPUT_BASE_PATH)/soma500-result.txt
	$(EXE) -m -p $(PERF_OUTPUT_BASE_PATH)/mult500.out -1 $(INPUT_BASE_PATH)/500m1.txt -2 $(INPUT_BASE_PATH)/500m2.txt -o $(PERF_OUTPUT_BASE_PATH)/mult500-result.txt
	$(EXE) -t -p $(PERF_OUTPUT_BASE_PATH)/transp500.out -1 $(INPUT_BASE_PATH)/500m1.txt -o $(PERF_OUTPUT_BASE_PATH)/transp500-result.txt

gprof: $(BIN)/matop
	$(EXE) -s -p $(GPROF_OUTPUT_BASE_PATH)/soma500gprof.out -1 $(INPUT_BASE_PATH)/500m1.txt -2 $(INPUT_BASE_PATH)/500m2.txt -o $(GPROF_OUTPUT_BASE_PATH)/soma500-result.txt
	gprof $(EXE) gmon.out > $(GPROF_OUTPUT_BASE_PATH)/soma500gprof.txt
	$(EXE) -m -p $(GPROF_OUTPUT_BASE_PATH)/mult500gprof.out -1 $(INPUT_BASE_PATH)/500m1.txt -2 $(INPUT_BASE_PATH)/500m2.txt -o $(GPROF_OUTPUT_BASE_PATH)/mult500-result.txt
	gprof $(EXE) gmon.out > $(GPROF_OUTPUT_BASE_PATH)/mult500gprof.txt
	$(EXE) -t -p $(GPROF_OUTPUT_BASE_PATH)/transp500gprof.out -1 $(INPUT_BASE_PATH)/500m1.txt -o $(GPROF_OUTPUT_BASE_PATH)/transp500-result.txt
	gprof $(EXE) gmon.out > $(GPROF_OUTPUT_BASE_PATH)/transp500gprof.txt

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
