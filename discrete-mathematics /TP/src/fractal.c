#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fractal.h"
#include "shared-utils.h"

void expandFractal (FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	FILE* initialFractalStageFile = mountFractalStageFile(0, "r");
	fprintf(initialFractalStageFile, "%s", axiom);
	fclose(initialFractalStageFile);

	for (int stage = 0; stage < stages; stage++) {
		FILE* lastFractalStageFile = mountFractalStageFile(stage, "r");
		FILE* currentFractalStageFile = mountFractalStageFile(stage + 1, "w");

		char axiomCharacter;

		while ((axiomCharacter = fgetc(lastFractalStageFile)) != EOF) {
			char* rule = getCharacterRule(axiomCharacter, rules);

			if (isValidString(rule)) {
				fprintf(currentFractalStageFile, "%s", rule);
			} else {
				fprintf(currentFractalStageFile, "%c", axiomCharacter);
			}
		}

		fclose(lastFractalStageFile);
		fclose(currentFractalStageFile);
	}
}

char* getCharacterRule (char character, FractalRule rules[]) {
	int i = 0;

	while (isValidCharacter(rules[i].key)) {
		char key = rules[i].key;
		char* value = rules[i].value;

		if (key == character) {
			return value;
		}

		i++;
	}

	return "";
};

FILE* mountFractalStageFile (int stage, char* fileMode) {
	FILE *fractalStageFile;

	char* fractalStageFileName = createEmptyString(100);
	sprintf(fractalStageFileName, "%d-fractal.txt", stage);

	char* fractalStageOutputFilePath = generateOutputFilePath(fractalStageFileName);
  fractalStageFile = fopen(fractalStageOutputFilePath, fileMode);

	return fractalStageFile;
}
