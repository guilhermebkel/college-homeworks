#ifndef LEXICOGRAPHIC_ANALYSER_H
#define LEXICOGRAPHIC_ANALYSER_H

#include <iostream>
#include <string>

#include "arrangement-list.h"

class LexicographicAnalyser {
  public:
    LexicographicAnalyser();
		void readWord(std::string word);
		ArrangementList<int> *getResult();
		void readOrdering (std::string letter);

	private:
		ArrangementList<int> *wordOccurences;
		ArrangementList<std::string> *ordering;
};

#endif