#ifndef LEXICOGRAPHIC_ANALYSER_H
#define LEXICOGRAPHIC_ANALYSER_H

#include <iostream>
#include <string>

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
		ArrangementList<WordOccurence> *getResult();
		void readOrdering (std::string letter);

	private:
		ArrangementList<WordOccurence> *wordOccurences;
		ArrangementList<std::string> *ordering;
};

#endif