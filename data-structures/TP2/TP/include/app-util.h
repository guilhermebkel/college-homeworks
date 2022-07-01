#ifndef APP_UTILS_H
#define APP_UTILS_H

#include <iostream>
#include <string.h>

typedef struct ParsedArgs {
	char inputFilePath[100];
  char outputFilePath[100];
  int quickSortPivot;
  int quickSortMaxPartitionSize;
} ParsedArgs;

ParsedArgs parseArgs (int argc, char **argv);

#endif