#ifndef LEXICOGRAPHIC_ANALYSER_H
#define LEXICOGRAPHIC_ANALYSER_H

#include <iostream>
#include <string>

enum MemoryLogLevel {
	READ_WORD = 0,
	READ_ORDERING = 1,
	GET_RESULT = 2
};

#include "arrangement-list.h"

typedef struct WordOccurence {
	int count;
	std::string rawWord;
	std::string normalizedWord;
} WordOccurence;

class LexicographicAnalyser {
  public:
    LexicographicAnalyser();
		void readWord(std::string word);
		ArrangementList<WordOccurence> *getResult(int quickSortPivot, int quickSortMaxPartitionSize);
		void readOrdering (std::string letter);

	private:
		ArrangementList<WordOccurence> *wordOccurences;
		ArrangementList<std::string> *ordering;
};

#endif