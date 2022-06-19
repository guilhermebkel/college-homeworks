#ifndef LEXICOGRAPHIC_ANALYSER_H
#define LEXICOGRAPHIC_ANALYSER_H

#include <iostream>
#include <string>

class LexicographicAnalyser {
  public:
    LexicographicAnalyser(std::string lexicographicalOrdering);
		void readText(std::string text);

	private:
		std::string *words;
};

#endif