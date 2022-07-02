#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "msgassert.h"
#include "memlog.h"
#include "app.h"
#include "app-util.h"
#include "app-validation.h"
#include "shared-util.h"
#include "lexicographic-analyser.h"
#include "app-memlog.h"

int main(int argc, char ** argv) {
	std::string memoryLogOutputFilePath = "../data/memory-log.out";

	iniciaMemLog(castChar(memoryLogOutputFilePath));
	ativaMemLog();

	ParsedArgs parsedArgs = parseArgs(argc, argv);

	NextReadType nextReadType = NextReadType::NOTHING;

	LexicographicAnalyser *lexicographicAnalyser = new LexicographicAnalyser();

	std::ifstream inputFile(parsedArgs.inputFilePath);
	erroAssert(!inputFile.fail(), "Input file was not found.");

	while (true) {
		std::string word;

		inputFile >> word;

		if (isTextConfig(word)) {
			nextReadType = NextReadType::TEXT;
		} else if (isOrderingConfig(word)) {
			nextReadType = NextReadType::ORDERING;
		} else if (nextReadType == NextReadType::ORDERING) {
			defineFaseMemLog(MemoryLogLevel::LEXICOGRAPHIC_ANALYSER_READ_ORDERING);
			lexicographicAnalyser->readOrdering(word);
		} else if (nextReadType == NextReadType::TEXT) {
			defineFaseMemLog(MemoryLogLevel::LEXICOGRAPHIC_ANALYSER_READ_WORD);
			lexicographicAnalyser->readWord(word);
		} else {
			nextReadType = NextReadType::NOTHING;
		}

		bool finishedReadingFile = inputFile.eof();

		if (finishedReadingFile) {
			break;
		}
	}

	inputFile.close();
	erroAssert(!inputFile.fail(), "Failed to close input file.");

	defineFaseMemLog(MemoryLogLevel::LEXICOGRAPHIC_ANALYSER_GET_RESULT);
	ArrangementList<WordOccurence> *result = lexicographicAnalyser->getResult(parsedArgs.quickSortPivot, parsedArgs.quickSortMaxPartitionSize);

	FILE *outputFile;
  outputFile = fopen(parsedArgs.outputFilePath, "wt");
	erroAssert(outputFile != NULL, "Failed to create output file.");

	for (int i = 0; i < result->getSize(); i++) {
		Item<WordOccurence> computedWord = result->findByIndex(i);

		fprintf(outputFile, "%s %d\n", computedWord.model.normalizedWord.c_str(), computedWord.model.count);
	}

	fprintf(outputFile, "#FIM");

	finalizaMemLog();

	return 0;
}