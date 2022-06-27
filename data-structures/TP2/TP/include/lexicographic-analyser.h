#ifndef LEXICOGRAPHIC_ANALYSER_H
#define LEXICOGRAPHIC_ANALYSER_H

#include <iostream>
#include <string>

#include "arrangement-list.h"

class LexicographicAnalyser {
  public:
    LexicographicAnalyser(std::string lexicographicalOrdering);
		void readWord(std::string word);
		ArrangementList<int> *getResult();

	private:
		ArrangementList<int> *wordOccurences;
		std::string lexicographicalOrdering;
};

#endif