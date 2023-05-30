#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fractal-file.h"
#include "shared-utils.h"

char* mountFractalStageFilePath (char* name, int stage) {
	char* fileName = createEmptyString(80 + strlen(name));
	sprintf(fileName, "%s-fractal-stage-%d.txt", name, stage);

	char* filePath = generateFolderFilePath("tmp", fileName);

	return filePath;
}

char* mountFinalFractalFilePath (char* name) {
	char* fileName = createEmptyString(25 + strlen(name));
	sprintf(fileName, "%s.txt", name);

	char* filePath = generateFolderFilePath("output", fileName);

	return filePath;
}

char* mountFractalPicturePath (char* name) {
	char* fileName = createEmptyString(25 + strlen(name));
	sprintf(fileName, "%s.png", name);

	char* filePath = generateFolderFilePath("output", fileName);

	return filePath;
}
