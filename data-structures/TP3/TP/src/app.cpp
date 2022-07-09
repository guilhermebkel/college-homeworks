#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "msgassert.h"
#include "memlog.h"
#include "app.h"
#include "app-util.h"
#include "shared-util.h"
#include "app-memlog.h"

int main(int argc, char ** argv) {
	std::string memoryLogOutputFilePath = "../data/memlog/output/log.out";

	iniciaMemLog(castChar(memoryLogOutputFilePath));
	ativaMemLog();

	ParsedArgs parsedArgs = parseArgs(argc, argv);

	finalizaMemLog();

	return 0;
}