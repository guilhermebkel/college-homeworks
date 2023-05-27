#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fractal.h"
#include "shared-utils.h"

void expandFractal (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	FILE* initialFractalStageFile = mountFractalStageFile(name, 0, "w");
	fprintf(initialFractalStageFile, "%s", axiom);
	fclose(initialFractalStageFile);

	for (int stage = 0; stage < stages; stage++) {
		FILE* lastFractalStageFile = mountFractalStageFile(name, stage, "r");
		FILE* currentFractalStageFile = mountFractalStageFile(name, stage + 1, "w");

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
}

FILE* mountFractalStageFile (char* name, int stage, char* fileMode) {
	FILE *fractalStageFile;

	char* fractalStageFileName = createEmptyString(120 + strlen(name));
	sprintf(fractalStageFileName, "%d-%s-fractal.txt", stage, name);

	printf("\nALOCOU: %s\n", name);

	char* fractalStageOutputFilePath = generateOutputFilePath(fractalStageFileName);
  fractalStageFile = fopen(fractalStageOutputFilePath, fileMode);

	return fractalStageFile;
}
