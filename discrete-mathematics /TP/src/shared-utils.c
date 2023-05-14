#include <stdio.h>
#include <stdlib.h>
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
	char* emptyString = (char*) malloc(size * sizeof(char));
	emptyString[0] = EMPTY_CHAR;

	return emptyString;
}
