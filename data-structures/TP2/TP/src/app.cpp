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

int main(int argc, char ** argv) {
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
			lexicographicAnalyser->readOrdering(word);
		} else if (nextReadType == NextReadType::TEXT) {
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

	ArrangementList<WordOccurence> *result = lexicographicAnalyser->getResult(parsedArgs.quickSortPivot, parsedArgs.quickSortMaxPartitionSize);

	FILE *outputFile;
  outputFile = fopen(parsedArgs.outputFilePath, "wt");
	erroAssert(outputFile != NULL, "Failed to create output file.");

	for (int i = 0; i < result->getSize(); i++) {
		Item<WordOccurence> computedWord = result->findByIndex(i);

		fprintf(outputFile, "%s %d\n", computedWord.model.normalizedWord.c_str(), computedWord.model.count);
	}

	fprintf(outputFile, "#FIM");

	return 0;
}