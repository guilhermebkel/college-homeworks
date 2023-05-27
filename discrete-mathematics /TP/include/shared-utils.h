#ifndef SHAREDUTILSH
#define SHAREDUTILSH

#include <stdio.h>
#include <time.h>

#ifndef EMPTY_CHAR 
#define EMPTY_CHAR '\0'
#endif

int isValidCharacter (char character);
int isValidString (char* string);
char* createEmptyString (int size);
char* generateFolderFilePath (char* folderName, char* fileName);
FILE* mountFile (char* filePath, char* fileMode);

#endif
