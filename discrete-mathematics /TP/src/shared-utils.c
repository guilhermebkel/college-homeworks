#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared-utils.h"

int isValidCharacter (char character) {
	if (character != EMPTY_CHAR) {
		return 1;
	} else {
		return 0;
	}
}

int isValidString (char* string) {
	return isValidCharacter(string[0]);
}

char* createEmptyString (int size) {
	char* emptyString = (char*) malloc((size + 1) * sizeof(char));
	emptyString[0] = EMPTY_CHAR;

	return emptyString;
}

char* generateFolderFilePath (char* folderName, char* fileName) {
	char* outputFilePath = createEmptyString(100 + strlen(folderName) + strlen(fileName));

	sprintf(outputFilePath, "./%s/%s", folderName, fileName);

	return outputFilePath;
}

FILE* mountFile (char* filePath, char* fileMode) {
	FILE *file;

  file = fopen(filePath, fileMode);

	return file;
}
