#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "msgassert.h"
#include "memlog.h"
#include "app-util.h"
#include "shared-util.h"

using namespace std;
 
int main(int argc, char ** argv) {
	ParsedArgs parsedArgs = parseArgs(argc, argv);

	bool readOrdering = false;
	bool readText = false;

	FILE *inputFile;
  inputFile = fopen(parsedArgs.inputFilePath, "r");
	erroAssert(inputFile != NULL, "Input file was not found.");

	fscanf(inputFile, "%s ");

	return 0;
}