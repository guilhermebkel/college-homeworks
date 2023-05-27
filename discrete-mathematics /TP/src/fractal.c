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

	processFractalStagesOnDemand(name, axiom, rules, stages);

	processFinalFractal(name, axiom, stages);
}

void processFractalStagesOnDemand (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
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

void processFinalFractal (char* name, FractalAxiom axiom, FractalStage stages) {
	FILE* finalFractalStageFile = mountFractalStageFile(name, stages - 1, "r");
	FILE* finalFractalFile = mountFinalFractalFile(name, "w");

	char axiomCharacter;

	while ((axiomCharacter = fgetc(finalFractalStageFile)) != EOF) {
		if (axiomCharacter == 'F' || axiomCharacter == '+' || axiomCharacter == '-') {
			fprintf(finalFractalFile, "%c", axiomCharacter);
		}
	}

	fclose(finalFractalStageFile);
	fclose(finalFractalFile);
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
	FILE *file;

	char* fileName = createEmptyString(120 + strlen(name));
	sprintf(fileName, "%d-%s-fractal.txt", stage, name);

	char* filePath = generateFolderFilePath("tmp", fileName);
  file = fopen(filePath, fileMode);

	return file;
}

FILE* mountFinalFractalFile (char* name, char* fileMode) {
	FILE *file;

	char* fileName = createEmptyString(120 + strlen(name));
	sprintf(fileName, "%s.txt", name);

	char* filePath = generateFolderFilePath("output", fileName);
  file = fopen(filePath, fileMode);

	return file;
}
