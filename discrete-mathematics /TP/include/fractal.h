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
void generateInitialFractalStageFile (char* name, FractalAxiom axiom);
char* processFractalStagesOnDemand (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages);
char* processFinalFractal (char* name, char* finalFractalStageFilePath);
void showFractal (char* name, char* fractalFilePath);
char* getCharacterRule (char character, FractalRule rules[]);

#endif
