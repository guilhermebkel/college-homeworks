#ifndef FRACTALH
#define FRACTALH

#include <stdio.h>
#include <time.h>

#ifndef MAX_RULE_SIZE 
#define MAX_RULE_SIZE 500
#endif

typedef struct {
	char key;
	char value[MAX_RULE_SIZE];
} FractalRule;

typedef char *FractalAxiom;

typedef int FractalStage;

void expandFractal(FractalAxiom axiom, FractalRule rules[], FractalStage stages);
char* getCharacterRule (char character, FractalRule rules[]);
FILE* mountFractalStageFile (int stage, char* fileMode);

#endif
