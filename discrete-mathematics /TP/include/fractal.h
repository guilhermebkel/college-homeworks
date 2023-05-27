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

void expandFractal(char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages);
void processFractalStagesOnDemand (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages);
void processFinalFractal (char* name, FractalAxiom axiom, FractalStage stages);
char* getCharacterRule (char character, FractalRule rules[]);
FILE* mountFractalStageFile (char* name, int stage, char* fileMode);
FILE* mountFinalFractalFile (char* name, char* fileMode);

#endif
